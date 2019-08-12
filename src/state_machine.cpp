#include "state_machine.h"
#include "persistence.h"
#include "latitude_config.h"

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

    m_persistence = Persistence();
    m_persistence.checkSchema();

    m_latitude_config = LatitudeConfig(SERIAL_REPORT_INTERVAL);
}

void StateMachine::loop()
{
    unsigned long currentMillis = millis();

    switch(state) {
        case STARTING_UP:
            if(! m_persistence.isLatitudeSet()){
                m_latitude_config.setup();
                state = FIRST_CONFIG_LATITUDE;
            } else if (! m_persistence.isMagneticDeclinationSet()) {
                /* code */
            }
            break;
        case FIRST_CONFIG_LATITUDE:
            m_latitude_config.loop();
            state = m_latitude_config.finished() ? STARTING_UP : FIRST_CONFIG_LATITUDE;
            break;
    }

    if((unsigned long)(currentMillis - previousSerialReportMillis) >= SERIAL_REPORT_INTERVAL) {
        Serial.print("StateMachine::loop: time=");
        Serial.println(currentMillis);
        Serial.print("StateMachine::loop: state=");
        Serial.println(state);
        previousSerialReportMillis = currentMillis;
    }
}
