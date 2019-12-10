#ifndef alignController_h
#define alignController_h

#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

#include "alignConfig.h"
#include "constants.h"

#define ALIGN_CALC_INTERVAL 330

class AlignController : public AsyncWebHandler
{
private:
  struct Config
  {
    float latitude;
    float magDeclination;
    float azError;
    float altError;
    float xOffset;
    float yOffset;
    float zOffset;
    float minAltitude;
    float maxAltitude;
    float targetAltitude;
    float minAzimuth;
    float maxAzimuth;
    float targetAzimuth;
  };

  Config _config;
  LSM9DS1 imu;

  unsigned long _currentMillis = 0;
  unsigned long _previousCalcMillis = 0;
  float _currentAltitude = 0;
  float _currentAzimuth = 0;
  bool _altAligned = false;
  bool _azAligned = false;

  // declination corrected heading
  float _calculateAltitude(
      float mx, float my,
      float ox, float oy,
      float declination);

  // pitch up/down
  float _calculateAzimuth(
      float ax, float ay, float az,
      float ox, float oy, float oz);

  bool _calculateIsAltitudeAligned(
      float currentHeading,
      float targetHeading,
      float minHeading,
      float maxHeading);

  void _handleStatusRequest(AsyncWebServerRequest *request, AsyncResponseStream *response);

public:
  AlignController();

  void setup();
  void loop(unsigned long currentMillis);

  // NOTE: remove 'const' if it appears unable to update settings!
  void loadSettings(const AlignConfig &alignConfig);

  bool isAligned();

  bool canHandle(AsyncWebServerRequest *request);
  void handleRequest(AsyncWebServerRequest *request);
};

#endif
