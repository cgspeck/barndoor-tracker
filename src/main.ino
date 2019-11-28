#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <FS.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>

#include "ArduinoJson-v6.13.0.h"
// #include "runnable.h"

DNSServer dnsServer;
AsyncWebServer server(80);

// Runnable *Runnable::headRunnable = NULL;

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
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
  //Handle Unknown Request
  Serial.println("not found");
  request->send(404);
}

void setup() {
  Serial.begin(115200);
  Serial.println("start setup!");
  SPIFFS.begin(true);
  // put your setup code here, to run once:
  WiFi.softAP("bd-tracker");
  dnsServer.start(53, "*", WiFi.softAPIP());
  // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  // Runnable::setupAll();
  server.onNotFound(notFoundHandler);
  server.begin();
  Serial.println("end setup!");
}

void loop() {
  // Serial.println("alive!");
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  // Runnable::loopAll();
}
