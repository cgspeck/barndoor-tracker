#include "settingsController.h"

// for help with ArduinoJson: https://arduinojson.org/v6/assistant/

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

SettingsController::SettingsController() {};

void SettingsController::setup() {
    // TODO: check flash ram and load defaults if schema is not up to date or missing
};

void SettingsController::loop(unsigned long currentMillis) {};

void SettingsController::attachHandlers(AsyncWebServer *server) {
    server->on("/settings/debug", HTTP_GET, std::bind(&SettingsController::handleDebugRequest, this, std::placeholders::_1));
    server->on("/flags", HTTP_GET, std::bind(&SettingsController::handleFlagRequest, this, std::placeholders::_1));

    // AP Settings
    server->on("/settings/ap", HTTP_GET, std::bind(&SettingsController::handleAPSettingsRequest, this, std::placeholders::_1));

    server->on("/settings/ap", HTTP_POST, std::bind(&SettingsController::handleAPSettingsPost, this, std::placeholders::_1));
};

void SettingsController::setDefaults() {};

bool SettingsController::needsReboot() { return false; };

DynamicJsonDocument SettingsController::_createAPSettingsDoc() {
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);
    JsonObject apSettings = doc.createNestedObject("apSettings");
    apSettings["ssid"] = getSSID();
    apSettings["key"] = getKey();
    return apSettings;
}

AsyncCallbackJsonWebHandler SettingsController::handleFlagRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    const size_t capacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);
    doc["needsAPSettings"] = true;
    doc["needsLocationSettings"] = true;
    serializeJson(doc, *response);
    request->send(response);
}

AsyncCallbackJsonWebHandler SettingsController::handleDebugRequest(AsyncWebServerRequest *request) {}

AsyncCallbackJsonWebHandler SettingsController::handleAPSettingsRequest(AsyncWebServerRequest *request) {};

AsyncCallbackJsonWebHandler SettingsController::handleAPSettingsPost(AsyncWebServerRequest *request) {
    // JsonObject& jsonObj = json.as<JsonObject>();
};


const char * SettingsController::getSSID() {
    return "bd_tracker";
};

const char * SettingsController::getKey() {
    return "";
};


bool SettingsController::setSSID(char* ssid) {
    return true;
}

bool SettingsController::setKey(char* key) {
    return true;
}

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
