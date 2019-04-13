#ifndef runnable_h
#define runnable_h

#include <Arduino.h>

class Runnable {
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable();

    virtual void setup() = 0;
    virtual void loop() = 0;

    static void setupAll() {
        Serial.println("Runnable::setupAll");
        for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        {
            Serial.println("Runnable::setupAll: calling subsetup");
            r->setup();
            Serial.println("Runnable::setupAll: runnable after subsetup");
        }
    }

    static void loopAll() {
        for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->loop();
    }

};

#endif
