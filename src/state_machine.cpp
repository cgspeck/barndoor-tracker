#include "state_machine.h"
#include "persistence.h"

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
    state = STARTING_UP;

    Persistence p = Persistence();
    p.checkSchema();
}

void StateMachine::loop()
{
    unsigned long currentMillis = millis();

    if (state == STARTING_UP) {

    }
    if((unsigned long)(currentMillis - previousSerialReportMillis) >= SERIAL_REPORT_INTERVAL) {
        Serial.print("StateMachine::setup: time=");
        Serial.println(currentMillis);
        previousSerialReportMillis = currentMillis;
    }
}
