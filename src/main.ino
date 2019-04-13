#include <Arduino.h>
#include <EEPROM.h>

#include "runnable.h"
#include "state_machine.h"

Runnable *Runnable::headRunnable = NULL;

void setup() {
  // put your setup code here, to run once:
  Runnable::setupAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  Runnable::loopAll();
}
