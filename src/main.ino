#include <Arduino.h>

#define REPORT_INTEVAL 5000

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

void notFoundHandler(AsyncWebServerRequest *request){
  if (request->method() == HTTP_OPTIONS) {
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
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  // Runnable::setupAll();
  server.onNotFound(notFoundHandler);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.addHandler(&settingsController);
  server.begin();
  Serial.println("end setup!");
}

unsigned long prevReport = 0;

void loop() {
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - prevReport) >= (int)REPORT_INTEVAL) {
    Serial.println("alive!");
    prevReport = currentMillis;
  }
  dnsServer.processNextRequest();
  settingsController.loop(currentMillis);
  // Runnable::loopAll();
}
