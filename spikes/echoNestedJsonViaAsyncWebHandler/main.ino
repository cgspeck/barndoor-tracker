#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <ArduinoJson.h>
#include <AsyncJson.h>

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

DNSServer dnsServer;
AsyncWebServer server(80);

/*
Endpoints:

* GET /debug

{
  "debug": {
    "currentMillis": 1234657987
  },
  "settings": {
    "message":"foo message",
    "value": 123456,
  }
}

* GET | POST /settings

{
  "message":"foo message",
  "value": 123456,
}

*/



class SettingsRequestHandler : public AsyncWebHandler {
private:
  unsigned long _currentMillis = 0;
  String _message = "hello world";
  int _value = 42;

  void _handleDebugGet(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    const size_t capacity = JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 70;
    DynamicJsonDocument doc(capacity);

    JsonObject debug = doc.createNestedObject("debug");
    debug["currentMillis"] = _currentMillis;

    JsonObject settings = doc.createNestedObject("settings");
    _constructSettingsDoc(&settings);

    serializeJson(doc, *response);
    request->send(response);
  };

  void _handleSettingsGet(AsyncWebServerRequest *request, AsyncResponseStream *response) {
    const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
    DynamicJsonDocument doc(capacity);
    JsonObject root = doc.to<JsonObject>();
    _constructSettingsDoc(&root);
    serializeJson(doc, *response);
    request->send(response);
  };

  void _handleSettingsPost(AsyncWebServerRequest * request, AsyncResponseStream *response) {

  };

  void _constructSettingsDoc(JsonObject *settingsObj) {
    settingsObj->operator[]("message") = _message;
    Serial.println(_value);
    settingsObj->operator[]("value") = _value;
  }

public:
  SettingsRequestHandler() {}
  virtual ~SettingsRequestHandler() {}

  void loop(unsigned long currentMillis) {
    _currentMillis = currentMillis;
  }

  bool canHandle(AsyncWebServerRequest *request) {
    bool _canHandle = false;
    if (request->url() == "/debug" && request->method() == HTTP_GET) {
      _canHandle = true;
    } else if (request->url() == "/settings" && ((request->method() == HTTP_GET) || (request->method() == HTTP_POST))) {
      _canHandle = true;
    }

    return _canHandle;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    // create a response with content-type header set
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    if (request->url() == "/debug") {
      _handleDebugGet(request, response);
    } else if (request->url() == "/settings") {
      if (request->method() == HTTP_GET) {
        _handleSettingsGet(request, response);
      } else {
        _handleSettingsPost(request, response);
      }
    }
  }
};

SettingsRequestHandler settingsRequestHandler;

void notFoundHandler(AsyncWebServerRequest *request){
  if (request->method() == HTTP_OPTIONS) {
    Serial.println("process options request");
    AsyncWebServerResponse *response = request->beginResponse(204);
    response->addHeader("Allow", "OPTIONS, GET, POST");
    request->send(response);
  } else {
    Serial.println("not found");
    request->send(404);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("start setup!");
  // wifi and DNS
  WiFi.softAP("iot_spike");
  dnsServer.start(53, "*", WiFi.softAPIP());
  // web server
  server.onNotFound(notFoundHandler);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.addHandler(&settingsRequestHandler);
  server.begin();
  //
  Serial.println("end setup!");
}

unsigned long prevReport = 0;

void loop() {
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - prevReport) >= (int)REPORT_INTEVAL) {
    Serial.print("loop current millis: ");
    Serial.println(currentMillis);
    settingsRequestHandler.loop(currentMillis);
    prevReport = currentMillis;
  }
  dnsServer.processNextRequest();
}
