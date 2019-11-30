#ifndef settingsController_h
#define settingsController_h

// #include <EEPROM.h>  - use "Preferences" instead

#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

#define REBOOT_DELAY_MILLIS 5000

class SettingsController : public AsyncWebHandler {
  private:
    struct Config {
      char ssid[63];
      char key[63];
    };
    Config config;
    const char *filename = "/config.json";

    unsigned long REBOOT_REQUESTED_AT;
    bool REBOOT_REQUESTED = false;

    unsigned long _currentMillis;

    void _loadConfiguration(const char *filename, Config &config);
    void _saveConfiguration(const char *filename, Config &config);

    const char * _validateSSID(char* val);
    const char * _validateKey(char* val);

    // general flags and debug
    void _handleFlagRequest(AsyncWebServerRequest *request, AsyncResponseStream * response);
    void _handleDebugRequest(AsyncWebServerRequest *request, AsyncResponseStream * response);

    // AP settings
    void _handleAPSettingsRequest(AsyncWebServerRequest *request, AsyncResponseStream * response);
    void _handleAPSettingsPost(AsyncWebServerRequest *request, AsyncResponseStream * response, uint8_t *data, size_t total);

    // internal document construction
    void _constructAPSettingsDoc(JsonObject *settingsObj);

  public:
    SettingsController();

    void setup();
    void loop(unsigned long currentMilLis);

    void setDefaults();
    bool needsReboot();

    bool canHandle(AsyncWebServerRequest *request);
    void handleRequest(AsyncWebServerRequest *request);

    const char * getSSID();
    const char * getKey();
    bool setSSID(char* ssid);
    bool setKey(char* password);
};

#endif
