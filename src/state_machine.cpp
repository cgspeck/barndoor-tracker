#include "state_machine.h"

#include <Arduino.h>

StateMachine::StateMachine(/* args */)
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::setup()
{
    Serial.println("StateMachine::setup");
}

void StateMachine::loop()
{
    unsigned long currentMillis = millis();
    if((unsigned long)(currentMillis - previousSerialReportMillis) >= SERIAL_REPORT_INTERVAL) {
        Serial.print("StateMachine::setup: time=");
        Serial.println(currentMillis);
        previousSerialReportMillis = currentMillis;
    }
}
