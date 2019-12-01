#include "settingsController.h"

// for help with ArduinoJson: https://arduinojson.org/v6/assistant/

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

SettingsController::SettingsController() {};

void SettingsController::setup() {
    _loadConfiguration(filename, config);
};

/*
{
"ssid": "1234567890123456789012345678901234567890123456789012345678901234",
"key": "1234567890123456789012345678901234567890123456789012345678901234",
"latitude": -37.74,
"magDeclination": 11.64,
"x_offset": -1.03,
"y_offset": 0.54,
"z_offset": -8.79,
"locationSet": true
}
*/

void SettingsController::_loadConfiguration(const char *filename, Config &config) {
    // Open file for reading
    File file = SPIFFS.open(filename);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(8) + 230;
    DynamicJsonDocument doc(capacity);
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    bool writeDefaults = false;

    if (error) {
        Serial.println(F("Failed to read file, using default configuration"));
        writeDefaults = true;
    }

    // Copy strings from the JsonDocument to the Config
    const char* ssid = doc["ssid"] | "barndoor_tracker";
    strlcpy(
        config.ssid,
        ssid,
        sizeof(config.ssid)
    );
    const char* key = doc["key"] | "";
    strlcpy(
        config.key,
        key,
        sizeof(config.key)
    );

    // AP settings
    config.latitude = doc["latitude"] | -37.74;
    config.magDeclination = doc["magDeclination"] | 11.64;
    config.x_offset = doc["x_offset"] | 0;
    config.y_offset = doc["y_offset"] | 0;
    config.z_offset = doc["z_offset"] | 0;
    config.locationSet = doc["locationSet"] | false;

    file.close();
    if (writeDefaults) {
    _saveConfiguration(filename, config);
    }
};


void SettingsController::_saveConfiguration(const char *filename, Config &config) {
    Serial.print("Saving ");
    Serial.println(filename);
    SPIFFS.remove(filename);

    // Open file for writing
    File file = SPIFFS.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println(F("Failed to create file"));
        return;
    }

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(8);
    DynamicJsonDocument doc(capacity);

    // Set the values in the document

    // AP Settings
    doc["ssid"] = config.ssid;
    doc["key"] = config.key;

    // Location
    doc["latitude"] = config.latitude;
    doc["magDeclination"] = config.magDeclination;
    doc["x_offset"] = config.x_offset;
    doc["y_offset"] = config.y_offset;
    doc["z_offset"] = config.z_offset;
    doc["locationSet"] = config.locationSet;

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0) {
        Serial.println(F("Failed to write to file"));
    }

    // Close the file
    file.close();
}

void SettingsController::loop(unsigned long currentMillis) {
    _currentMillis = currentMillis;
    if (REBOOT_REQUESTED && (unsigned long)(currentMillis - REBOOT_REQUESTED_AT) >= (int)REBOOT_DELAY_MILLIS) {
        Serial.println("Rebooting");
        ESP.restart();
    }
};

void SettingsController::setDefaults() {
    // delete the config.json file
    Serial.print("Deleting ");
    Serial.println(filename);
    SPIFFS.remove(filename);

    // set flag to call for delay restart
    Serial.print("Scheduling reboot in ");
    Serial.print(REBOOT_DELAY_MILLIS / 5000);
    Serial.println(" seconds.");
    REBOOT_REQUESTED_AT = _currentMillis;
    REBOOT_REQUESTED = true;
};

void SettingsController::_handleFlagRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    Serial.println("SettingsController::_handleFlagRequest start");
    const size_t capacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);
    doc["needsAPSettings"] = (strlen(config.key)  == 0);
    doc["needsLocationSettings"] = !config.locationSet;
    serializeJson(doc, *response);
    request->send(response);
    Serial.println("SettingsController::_handleFlagRequest end");
}

bool SettingsController::canHandle(AsyncWebServerRequest *request) {
    bool _canHandle = false;
    if (request->url() == "/settings/debug" && request->method() == HTTP_GET) {
        _canHandle = true;
    } else if (request->url() == "/settings/ap" && ((request->method() == HTTP_GET) || (request->method() == HTTP_POST))) {
        _canHandle = true;
    } else if (request->url() == "/flags" && request->method() == HTTP_GET) {
        _canHandle = true;
    } else if (request->url() == "/settings/location" && ((request->method() == HTTP_GET) || (request->method() == HTTP_POST))) {
        _canHandle = true;
    }

    return _canHandle;
}

void SettingsController::handleRequest(AsyncWebServerRequest *request) {
    // create a response with content-type header set
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    if (request->url() == "/flags") {
        _handleFlagRequest(request, response);
    } else if (request->url() == "/settings/debug") {
        _handleDebugRequest(request, response);
    } else if (request->url() == "/settings/ap") {
        _handleAPSettingsRequest(request, response);
    }  else if (request->url() == "/settings/location") {
        _handleLocationSettingsRequest(request, response);
    }
}

void SettingsController::handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    if (request->url() == "/settings/ap" && request->method() == HTTP_POST) {
        _handleAPSettingsPost(request, data, total);
    } else if (request->url() == "/settings/location" && request->method() == HTTP_POST) {
        _handleLocationSettingsPost(request, data, total);
    }
}

/*
{
   "debug": {
       "currentMillis": 4294967295

   },
   "apSettings": {
     "ssid": "1234567980123456798012345679801234567980123456798012345679801234",
       "key": "1234567980123456798012345679801234567980123456798012345679801234"
   },
   "location": {
       "latitude": -37.74,
        "magDeclination": 11.64,
        "x_offset": -1.03,
        "y_offset": 0.54,
        "z_offset": -8.79,
        "locationSet": true
    }
}
*/
void SettingsController::_handleDebugRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    Serial.println("SettingsController::_handleDebugRequest start");
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6);
    DynamicJsonDocument doc(capacity);

    JsonObject debug = doc.createNestedObject("debug");
    debug["currentMillis"] = _currentMillis;

    JsonObject ap_settings = doc.createNestedObject("apSettings");
    _constructAPSettingsDoc(&ap_settings);

    JsonObject location = doc.createNestedObject("location");
    _constructLocationSettingsDoc(&location);

    serializeJson(doc, *response);
    request->send(response);
    Serial.println("SettingsController::_handleDebugRequest end");
}

void SettingsController::_handleAPSettingsRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    Serial.println("SettingsController::_handleAPSettingsRequest start");
    const size_t capacity = JSON_OBJECT_SIZE(2) + 160;
    DynamicJsonDocument doc(capacity);
    JsonObject root = doc.to<JsonObject>();
    _constructAPSettingsDoc(&root);
    serializeJson(doc, *response);
    request->send(response);
    Serial.println("SettingsController::_handleAPSettingsRequest end");
};

/*
{
    "ssid": "1234567980123456798012345679801234567980123456798012345679801234",
    "key": "1234567980123456798012345679801234567980123456798012345679801234"
}
*/

void SettingsController::_constructAPSettingsDoc(JsonObject *settingsObj) {
    settingsObj->operator[]("ssid") = config.ssid;
    settingsObj->operator[]("key") = config.key;
}

void SettingsController::_handleAPSettingsPost(AsyncWebServerRequest *request, uint8_t *data, size_t total) {
    Serial.println("SettingsController::_handleAPSettingsPost start");
    const size_t capacity = JSON_OBJECT_SIZE(2) + 160;
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, data);

    if(error) {
      Serial.print("bad json: ");
      Serial.println(error.c_str());
      request->send(total > capacity ? 413 : 400);
      return;
    }
    bool settingsChanged = false;

    const char* ssid = doc["ssid"];
    if (ssid && (strcmp(ssid, config.ssid) != 0)) {
        Serial.print("rcd ssid:");
        Serial.println(ssid);

        strlcpy(
            config.ssid,
            ssid,
            sizeof(config.ssid)
        );
        settingsChanged = true;
    }

    const char* key = doc["key"];
    if (key && (strcmp(key, config.key) != 0)) {
        Serial.print("rcd key:");
        Serial.println(key);
        strlcpy(
            config.key,
            key,
            sizeof(config.key)
        );
        settingsChanged = true;
    }

    if (settingsChanged) {
        _saveConfiguration(filename, config);
        REBOOT_REQUESTED = true;
        REBOOT_REQUESTED_AT = _currentMillis;
    }
    Serial.println("SettingsController::_handleAPSettingsPost end");
};

void SettingsController::_handleLocationSettingsRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    Serial.println("SettingsController::_handleLocationSettingsRequest start");
    const size_t capacity = JSON_OBJECT_SIZE(6);
    DynamicJsonDocument doc(capacity);
    JsonObject root = doc.to<JsonObject>();
    _constructLocationSettingsDoc(&root);
    serializeJson(doc, *response);
    request->send(response);
    Serial.println("SettingsController::_handleLocationSettingsRequest end");
};

/*
{
    "latitude": -37.74,
    "magDeclination": 11.64,
    "x_offset": -1.03,
    "y_offset": 0.54,
    "z_offset": -8.79,
    "locationSet": true
}
*/
void SettingsController::_constructLocationSettingsDoc(JsonObject *settingsObj) {
    settingsObj->operator[]("latitude") = config.latitude;
    settingsObj->operator[]("magDeclination") = config.magDeclination;
    settingsObj->operator[]("x_offset") = config.x_offset;
    settingsObj->operator[]("y_offset") = config.y_offset;
    settingsObj->operator[]("z_offset") = config.z_offset;
    settingsObj->operator[]("locationSet") = config.locationSet;
}

void SettingsController::_handleLocationSettingsPost(AsyncWebServerRequest *request, uint8_t *data, size_t total) {
    Serial.println("SettingsController::_handleLocationSettingsPost start");
    const size_t capacity = JSON_OBJECT_SIZE(6) + 70;
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, data);

    if(error) {
      Serial.print("bad json: ");
      Serial.println(error.c_str());
      request->send(total > capacity ? 413 : 400);
      return;
    }
    bool settingsChanged = false;

    if (doc.containsKey("latitude")) {
        config.latitude = doc["latitude"];
        settingsChanged = true;
    }

    if (doc.containsKey("magDeclination")) {
        config.latitude = doc["magDeclination"];
        settingsChanged = true;
    }

    if (doc.containsKey("x_offset")) {
        config.latitude = doc["x_offset"];
        settingsChanged = true;
    }

    if (doc.containsKey("y_offset")) {
        config.latitude = doc["y_offset"];
        settingsChanged = true;
    }

    if (doc.containsKey("z_offset")) {
        config.latitude = doc["z_offset"];
        settingsChanged = true;
    }

    if (settingsChanged) {
        config.locationSet = true;
        _saveConfiguration(filename, config);
    }

    Serial.println("SettingsController::_handleLocationSettingsPost end");
};

const char * SettingsController::getSSID() {
    return config.ssid;
};

const char * SettingsController::getKey() {
    return config.key;
};

/* rules for SSID & key

 * @param ssid              Pointer to the SSID (max 63 char).
 * @param passphrase        (for WPA2 min 8 char, for open use NULL)
 * @param channel           WiFi channel number, 1 - 13.
 * @param ssid_hidden       Network cloaking (0 = broadcast SSID, 1 = hide SSID)
 * @param max_connection    Max simultaneous connected clients, 1 - 4.

 */
const char * _validateSSID(char* val) {
    return "";
}

const char * _validateKey(char* val) {
    return "";
}
