#ifndef runnable_h
#define runnable_h

#include "Arduino.h"

class Runnable {
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable();

    virtual void setup() = 0;
    virtual void loop() = 0;

    static void setupAll() {
        for (Runnable *r = headRunnable; r; r = r->nextRunnable)
            r->setup();
    }

    static void loopAll() {
        for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->loop();
    }

};

#endif
