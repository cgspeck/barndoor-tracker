#include <Arduino.h>
#include <EEPROM.h>

#include "runnable.h"
#include "state_machine.h"

Runnable *Runnable::headRunnable = NULL;
StateMachine stateMachine;

const int SERIAL_REPORT_INTERVAL = 1000;
unsigned long previousSerialReportMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Runnable::setupAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  Runnable::loopAll();
}
