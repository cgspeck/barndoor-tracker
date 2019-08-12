#ifndef latitude_config_h
#define latitude_config_h

#include "runnable.h"
#include "persistence.h"

class LatitudeConfig: public Runnable {
private:
    int SERIAL_REPORT_INTERVAL;
    unsigned long previousSerialReportMillis = 0;

    Persistence persistence;

    bool m_finished = false;

public:
    LatitudeConfig();
    LatitudeConfig(int serial_report_interval);
    ~LatitudeConfig();

    void setup();
    void loop();

    bool finished();
};

#endif
