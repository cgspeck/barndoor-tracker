#include "alignController.h"

#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

#include "alignConfig.h"

AlignController::AlignController(){};

void AlignController::setup()
{
    // imu.beginSPI(), which verifies communication with the IMU
    // and turns it on.
    if (imu.beginSPI(LSM9DS1_AG_CS, LSM9DS1_M_CS) == false) // note, we need to sent this our CS pins (defined above)
    {
        Serial.println("Failed to communicate with LSM9DS1.");
        Serial.println("Double-check wiring.");
        Serial.println("Default settings in this sketch will "
                       "work for an out of the box LSM9DS1 "
                       "Breakout, but may need to be modified "
                       "if the board jumpers are.");
    }
}

float AlignController::_calculateAzimuth(
    float ax, float ay, float az,
    float ox, float oy, float oz)
{
    // original forumla: float pitch = atan2(-ax, sqrt(ay * ay + az * az))
    float o_ax = ax + ox;
    float o_ay = ay + oy;
    float o_az = az + oz;

    float pitch = atan2(-o_ax, sqrt(o_ay * o_ay + o_az * o_az));
    pitch *= 180.0 / PI;
    return pitch;
}

float AlignController::_calculateAltitude(
    float mx, float my,
    float ox, float oy,
    float declination)
{
    float o_mx = mx + ox;
    float o_my = my + oy;

    float heading;
    if (o_my == 0)
        heading = (o_mx < 0) ? PI : 0;
    else
        heading = atan2(o_mx, o_my);

    heading -= declination * PI / 180;

    if (heading > PI)
        heading -= (2 * PI);
    else if (heading < -PI)
        heading += (2 * PI);

    heading *= 180.0 / PI;

    return heading;
}

void AlignController::loadSettings(const AlignConfig &alignConfig)
{
    Serial.println("AlignController::loadSettings: start");
    _config.latitude = alignConfig.latitude;
    _config.magDeclination = alignConfig.magDeclination;
    _config.azError = alignConfig.azError;
    _config.altError = alignConfig.altError;
    _config.xOffset = alignConfig.xOffset;
    _config.yOffset = alignConfig.yOffset;
    _config.zOffset = alignConfig.zOffset;

    if (alignConfig.latitude <= 0)
    {
        _config.targetAltitude = 180;
        _config.minAltitude = 180 - alignConfig.altError;
        _config.maxAltitude = 180 + alignConfig.altError;
    }
    else
    {
        _config.targetAltitude = 0;
        _config.minAltitude = 360 - alignConfig.altError;
        _config.maxAltitude = alignConfig.altError;
    }

    _config.targetAzimuth = abs(alignConfig.latitude);
    _config.minAzimuth = _config.targetAzimuth - alignConfig.azError;
    _config.maxAzimuth = _config.targetAzimuth + alignConfig.azError;

    Serial.print("AlignController::loadSettings: latitude ");
    Serial.print(_config.latitude);
    Serial.print(" magDeclination ");
    Serial.print(_config.magDeclination);
    Serial.print(" targetAltitude ");
    Serial.print(_config.targetAltitude);
    Serial.print(" minAltitude ");
    Serial.print(_config.minAltitude);
    Serial.print(" maxAltitude ");
    Serial.print(_config.maxAltitude);
    Serial.print(" targetAzimuth ");
    Serial.print(_config.targetAzimuth);
    Serial.print(" minAzimuth ");
    Serial.print(_config.minAzimuth);
    Serial.print(" maxAzimuth ");
    Serial.println(_config.maxAzimuth);
    Serial.println("AlignController::loadSettings: end");
}

void AlignController::loop(unsigned long currentMillis)
{
    if (imu.accelAvailable())
    {
        imu.readAccel();
    }

    if (imu.magAvailable())
    {
        imu.readMag();
    }

    if ((currentMillis - _previousCalcMillis) >= (int)ALIGN_CALC_INTERVAL)
    {
        Serial.println("AlignController::loop: start recalc");
        // pitch up/down
        _currentAzimuth = _calculateAzimuth(
            imu.ax, imu.ay, imu.az,
            _config.xOffset, _config.yOffset, _config.zOffset);

        _azAligned = (_currentAzimuth >= _config.minAzimuth &&
                      _currentAzimuth <= _config.maxAzimuth);

        // heading
        _currentAltitude = _calculateAltitude(
            imu.mx, imu.my,
            _config.xOffset, _config.yOffset,
            _config.magDeclination);

        _altAligned = _calculateIsAltitudeAligned(
            _currentAltitude, _config.targetAzimuth,
            _config.minAltitude, _config.maxAltitude);

        _previousCalcMillis = currentMillis;
        Serial.print("AlignController::loop: _currentAltitude=");
        Serial.print(_currentAltitude);
        Serial.print(" _currentAzimuth=");
        Serial.println(_currentAzimuth);
        Serial.println("AlignController::loop: start recalc");
    }
}

bool AlignController::_calculateIsAltitudeAligned(
    float currentHeading,
    float targetHeading,
    float minHeading,
    float maxHeading)
{
    if (targetHeading == 180)
    {
        return currentHeading >= minHeading && currentHeading <= maxHeading;
    }
    else
    {
        if (currentHeading > 0 && currentHeading >= minHeading)
        {
            return true;
        }
        else if (currentHeading <= maxHeading && currentHeading >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool AlignController::isAligned()
{
    return _azAligned && _altAligned;
}

bool AlignController::canHandle(AsyncWebServerRequest *request)
{
    bool _canHandle = false;
    if (request->url() == "/status/align" && request->method() == HTTP_GET)
    {
        _canHandle = true;
    }
    return _canHandle;
}

void AlignController::handleRequest(AsyncWebServerRequest *request)
{
    // create a response with content-type header set
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    if (request->url() == "/status/align")
    {
        _handleStatusRequest(request, response);
    }
}

void AlignController::_handleStatusRequest(AsyncWebServerRequest *request, AsyncResponseStream *response)
{
    Serial.println("AlignController::_handleStatusRequest: start");
    const size_t capacity = JSON_OBJECT_SIZE(4) + 106;
    DynamicJsonDocument doc(capacity);

    doc["azAligned"] = _azAligned;
    doc["altAligned"] = _altAligned;
    doc["currentAz"] = _currentAzimuth;
    doc["currentAlt"] = _currentAltitude;
    serializeJson(doc, *response);
    request->send(response);
    Serial.println("AlignController::_handleStatusRequest: end");
}
