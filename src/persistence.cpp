#include "persistence.h"

#include <Arduino.h>
#include <EEPROM.h>

Persistence::Persistence() {
    if (!EEPROM.begin(EEPROM.length())) {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
}

void Persistence::checkSchema() {
    int ver = EEPROM.readInt(SCHEMA_ADDRESS);

    if (ver != SCHEMA_VER) {
        Serial.print("Persistence schema version mismatch");
        Serial.print(ver);
        Serial.print(" != ");
        Serial.println(SCHEMA_VER);
        Persistence::setDefaults();
    }
}

void Persistence::setDefaults() {
    Serial.println("Setting defaults");
    EEPROM.writeInt(SCHEMA_ADDRESS, SCHEMA_VER);
    EEPROM.writeBool(LATITUDE_SET_ADDRESS, false);
    EEPROM.writeInt(LATITUDE_ADDRESS, -3691);  // LAT of Heathcote, Victoria
}

bool Persistence::isLatitudeSet() {
    return EEPROM.readBool(LATITUDE_SET_ADDRESS);
}

int Persistence::getLatitude() {
    return EEPROM.readInt(LATITUDE_ADDRESS);
}

void Persistence::setLatitude(int val) {
    EEPROM.writeInt(LATITUDE_ADDRESS, val);
}

