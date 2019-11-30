#include "settingsController.h"

// for help with ArduinoJson: https://arduinojson.org/v6/assistant/

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

SettingsController::SettingsController() {};

void SettingsController::setup() {
    _loadConfiguration(filename, config);
};

void SettingsController::_loadConfiguration(const char *filename, Config &config) {
    // Open file for reading
    File file = SPIFFS.open(filename);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(2) + 160;
    StaticJsonDocument<capacity> doc;
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    bool writeDefaults = false;

    if (error) {
        Serial.println(F("Failed to read file, using default configuration"));
        writeDefaults = true;
    }

    // Copy values from the JsonDocument to the Config
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
    const size_t capacity = JSON_OBJECT_SIZE(2) + 160;
    StaticJsonDocument<256> doc;

    // Set the values in the document
    doc["ssid"] = config.ssid;
    doc["key"] = config.key;

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
    Serial.println(filename);
    // set flag to call for delay restart
    Serial.print("Scheduling reboot in ");
    Serial.print(REBOOT_DELAY_MILLIS / 5000);
    Serial.println(" seconds.");
    REBOOT_REQUESTED_AT = _currentMillis;
    REBOOT_REQUESTED = true;
};

void SettingsController::_handleFlagRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    const size_t capacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);
    doc["needsAPSettings"] = (strlen(config.key)  == 0);
    doc["needsLocationSettings"] = true;
    serializeJson(doc, *response);
    request->send(response);
}

bool SettingsController::canHandle(AsyncWebServerRequest *request) {
    bool _canHandle = false;
    if (request->url() == "/settings/debug" && request->method() == HTTP_GET) {
        _canHandle = true;
    } else if (request->url() == "/settings/ap" && ((request->method() == HTTP_GET) || (request->method() == HTTP_POST))) {
        _canHandle = true;
    } else if (request->url() == "/flags" && request->method() == HTTP_GET) {
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
    }
  }

/*
   {
   "debug": {
       "currentMillis": 4294967295

   },
   "ap_settings": {
     "ssid": "1234567980123456798012345679801234567980123456798012345679801234",
       "key": "1234567980123456798012345679801234567980123456798012345679801234"
   }
}
*/
void SettingsController::_handleDebugRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    const size_t capacity = JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 160;
    DynamicJsonDocument doc(capacity);

    JsonObject debug = doc.createNestedObject("debug");
    debug["currentMillis"] = _currentMillis;

    JsonObject ap_settings = doc.createNestedObject("apSettings");
    _constructAPSettingsDoc(&ap_settings);

    serializeJson(doc, *response);
    request->send(response);
}

/*
{
    "ssid": "1234567980123456798012345679801234567980123456798012345679801234",
    "key": "1234567980123456798012345679801234567980123456798012345679801234"
}
*/
void SettingsController::_handleAPSettingsRequest(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    const size_t capacity = JSON_OBJECT_SIZE(2) + 160;
    DynamicJsonDocument doc(capacity);
    JsonObject root = doc.to<JsonObject>();
    _constructAPSettingsDoc(&root);
    serializeJson(doc, *response);
    request->send(response);
};

void SettingsController::_constructAPSettingsDoc(JsonObject *settingsObj) {
    settingsObj->operator[]("ssid") = config.ssid;
    settingsObj->operator[]("key") = config.key;
}


void SettingsController::handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    if (request->url() == "/settings/ap" && request->method() == HTTP_POST) {
        _handleAPSettingsPost(request, data, total);
    }
}
/*
{
    "ssid": "1234567980123456798012345679801234567980123456798012345679801234",
    "key": "1234567980123456798012345679801234567980123456798012345679801234"
}
*/
void SettingsController::_handleAPSettingsPost(AsyncWebServerRequest *request, uint8_t *data, size_t total) {
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
