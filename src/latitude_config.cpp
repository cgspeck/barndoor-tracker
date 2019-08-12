#include "latitude_config.h"
#include "persistence.h"

#include <Arduino.h>

LatitudeConfig::LatitudeConfig()
{
    SERIAL_REPORT_INTERVAL = 1000;
}

LatitudeConfig::LatitudeConfig(int serial_report_interval)
{
    SERIAL_REPORT_INTERVAL = serial_report_interval;
}

LatitudeConfig::~LatitudeConfig()
{
}

void LatitudeConfig::setup()
{
    Serial.println("LatitudeConfig::setup");
    persistence = Persistence();
}

void LatitudeConfig::loop()
{
    unsigned long currentMillis = millis();

    if((unsigned long)(currentMillis - previousSerialReportMillis) >= SERIAL_REPORT_INTERVAL) {
        Serial.print("LatitudeConfig::setup: time=");
        Serial.println(currentMillis);
        previousSerialReportMillis = currentMillis;
    }
}

bool LatitudeConfig::finished() { return m_finished; }
