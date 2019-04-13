#ifndef state_machine_h
#define state_machine_h

#include "runnable.h"

class StateMachine: public Runnable {
private:
    /* data */
public:
    StateMachine(/* args */);
    ~StateMachine();

    void setup();
    void loop();
};

#endif
