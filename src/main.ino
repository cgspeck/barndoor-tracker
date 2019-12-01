#include <Arduino.h>

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <FS.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
// #include "runnable.h"
#include "settingsController.h"

#include "esp_wifi.h"

#define REPORT_INTEVAL 5000

// FEATURE SWITCHES
//
// CAUTION: ESP32 ASYNCWEBSERVER / ASYNCTCP appears too fragile to support this :-<
// #define BD_ENABLE_CAPTURED_PORTAL
//
// Preact Router only works once bundle is loaded by client.
// The next switch sends a user to /index.html if they happen to be on
// a known route when they connect.
#define BD_REWRITE_KNOWN_PAGES

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
    Serial.print("not found: ");
    Serial.print(request->methodToString());
    Serial.print(" ");
    Serial.println(request->url());

#ifdef BD_ENABLE_CAPTURED_PORTAL
    request->redirect("/index.html");
#else
    request->send(404);
#endif
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("start setup!");
  SPIFFS.begin(true);
  settingsController.setup();
  esp_wifi_set_ps(WIFI_PS_NONE);

  if (settingsController.getKey() == "") {
    // Open AP mode
    WiFi.softAP(settingsController.getSSID());
  } else {
    WiFi.softAP(settingsController.getSSID(), settingsController.getKey());
  }
  dnsServer.start(53, "*", WiFi.softAPIP());
  // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  // ADD ALL CUSTOM HANDLERS HERE!!

#ifdef BD_REWRITE_KNOWN_PAGES
  // these urls are here incase client reconnects with a view already open
  server.rewrite("/ap_settings", "/index.html");
  server.rewrite("/debug", "/index.html");
  server.rewrite("/location_settings", "/index.html");
  server.rewrite("/track", "/index.html");
#endif
  // set up default & serve static content
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setCacheControl("max-age=600");
  // Runnable::setupAll();
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.addHandler(&settingsController);
  server.onNotFound(notFoundHandler);
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
