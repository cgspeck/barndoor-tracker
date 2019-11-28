#ifndef settingsController_h
#define settingsController_h

// #include <EEPROM.h>  - use "Preferences" instead

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

class SettingsController {
    static const int SCHEMA_VER = 1;

    // I think these addresses refer to byte positions within the EEPROM
    static const int SCHEMA_ADDRESS = 0;  // int, 4 bytes
    static const int AP_SET = 4; // bool, 1 byte
    static const int AP_SSID = 5; // char? str?
    // static const int LATITUDE_ADDRESS = 4;  // int, 4 bytes
    // static const int MAGNETIC_DECLINATION_ADDRESS = 8;  // int, 4 bytes
    DynamicJsonDocument _createAPSettingsDoc();
    const char * _validateSSID(char* val);
    const char * _validateKey(char* val);

  public:
    SettingsController();

    void setup();
    void loop(unsigned long currentMilLis);

    void attachHandlers(AsyncWebServer *server);

    void setDefaults();
    bool needsReboot();

    // general flags and debug
    AsyncCallbackJsonWebHandler handleFlagRequest(AsyncWebServerRequest *request);
    AsyncCallbackJsonWebHandler handleDebugRequest(AsyncWebServerRequest *request);

    // AP settings
    AsyncCallbackJsonWebHandler handleAPSettingsRequest(AsyncWebServerRequest *request);
    AsyncCallbackJsonWebHandler handleAPSettingsPost(AsyncWebServerRequest *request);
    const char * getSSID();
    const char * getKey();
    bool setSSID(char* ssid);
    bool setKey(char* password);
};

#endif
