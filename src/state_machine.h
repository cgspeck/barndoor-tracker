#ifndef state_machine_h
#define state_machine_h

#include "runnable.h"
#include "persistence.h"
#include "latitude_config.h"

class StateMachine: public Runnable {
private:
    const int SERIAL_REPORT_INTERVAL = 1000;
    unsigned long previousSerialReportMillis = 0;

    enum State {
      STARTING_UP = 0,
      IDLE = 100,
      FIRST_CONFIG_LATITUDE = 200,
      CONFIG_LATITUDE = 300
    } state;

    Persistence m_persistence;
    LatitudeConfig m_latitude_config;

public:
    StateMachine(/* args */);
    ~StateMachine();

    void setup();
    void loop();
};

#endif
