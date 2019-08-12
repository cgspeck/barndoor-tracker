#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include "runnable.h"
#include "state_machine.h"

Runnable *Runnable::headRunnable = NULL;
StateMachine stateMachine;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Runnable::setupAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  Runnable::loopAll();
}
