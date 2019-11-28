#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <FS.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
// #include "runnable.h"
#include "settingsController.h"

DNSServer dnsServer;
AsyncWebServer server(80);
SettingsController settingsController;

// Runnable *Runnable::headRunnable = NULL;

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal</title></head><body>");
    response->print("<p>This is out captive portal front page.</p>");
    response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
  }
};

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
  SPIFFS.begin(true);
  settingsController.setup();

  if (settingsController.getKey() == "") {
    // Open AP mode
    WiFi.softAP(settingsController.getSSID());
  } else {
    WiFi.softAP(settingsController.getSSID(), settingsController.getKey());
  }

  dnsServer.start(53, "*", WiFi.softAPIP());
  // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  // ADD ALL CUSTOM HANDLERS HERE!!
  settingsController.attachHandlers(&server);
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  // Runnable::setupAll();
  server.onNotFound(notFoundHandler);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  Serial.println("end setup!");
}

void loop() {
  unsigned long currentMillis = millis();
  // Serial.println("alive!");
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  settingsController.loop(currentMillis);
  // Runnable::loopAll();
}
