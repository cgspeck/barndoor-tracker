#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <DNSServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ArduinoJson-v6.13.0.h"
#include "runnable.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Runnable *Runnable::headRunnable = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.softAP("bd-tracker");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.serveStatic("/", SPIFFS, "/");
  Runnable::setupAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  Runnable::loopAll();
}
