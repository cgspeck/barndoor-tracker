#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "runnable.h"

Runnable *Runnable::headRunnable = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Runnable::setupAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  Runnable::loopAll();
}
