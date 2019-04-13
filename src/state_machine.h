#ifndef state_machine_h
#define state_machine_h

#include "runnable.h"

class StateMachine: public Runnable {
private:
    const int SERIAL_REPORT_INTERVAL = 1000;
    unsigned long previousSerialReportMillis = 0;

public:
    StateMachine(/* args */);
    ~StateMachine();

    void setup();
    void loop();
};

#endif
