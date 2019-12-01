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

class DebugRequestHandler : public AsyncWebHandler {
private:
  unsigned long _currentMillis = 0;

public:
  DebugRequestHandler() {}
  virtual ~DebugRequestHandler() {}

  void loop(unsigned long currentMillis) {
    Serial.print("currentMillis updated to:");
    Serial.println(currentMillis);
    _currentMillis = currentMillis;
  }

  bool canHandle(AsyncWebServerRequest *request) {
    Serial.print("URL:");
    Serial.println(request->url());
    if (request->url() == "/endpoint") {
      Serial.println("can handle");
      return true;
    } else {
      Serial.println("no can handle");
      return false;
    }
  }

  void handleRequest(AsyncWebServerRequest *request) {
    // create a response with content-type header set
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    // create our JSON document
    const size_t capacity = 2*JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);
    doc["name"] = "nestedJsonWithFuncViaSerial";

    // call our func and pass in doc to add a nested object
    addDebugReport(&doc);

    // this is where the magic happens!
    serializeJson(doc, *response);

    // transmit the request
    Serial.println("sending response!");
    request->send(response);
  }

  void addDebugReport(DynamicJsonDocument *doc) {
    JsonObject debug = doc->createNestedObject("debug");
    Serial.print("addDebugReport::_currentMillis is:");
    Serial.println(_currentMillis);
    debug["currentMillis"] = _currentMillis;
    debug["state"] = "allGood";
  }
};

DebugRequestHandler debugRequestHandler;

void notFoundHandler(AsyncWebServerRequest *request){
  if (request->method() == HTTP_OPTIONS) {
    AsyncWebServerResponse *response = request->beginResponse(204);
    response->addHeader("Allow", "OPTIONS, GET, POST");
    request->send(response);
  } else {
    request->send(404);
  }
  //Handle Unknown Request
  Serial.println("not found");
  request->send(404);
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
  server.addHandler(&debugRequestHandler);
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
    debugRequestHandler.loop(currentMillis);
    prevReport = currentMillis;
  }
  dnsServer.processNextRequest();
}
