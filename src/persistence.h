#ifndef persistence_h
#define persistence_h

#include <EEPROM.h>

class Persistence {
    static const int SCHEMA_VER = 1;

    // I think these addresses refer to byte positions within the EEPROM
    static const int SCHEMA_ADDRESS = 0;  // int, 4 bytes
    static const int LATITUDE_SET_ADDRESS = 4;  // bool, 1 byte
    static const int LATITUDE_ADDRESS = 5;  // int, 4 bytes


  public:
    Persistence();

    void setup();
    void loop();

    void setDefaults();
    void checkSchema();

    bool isLatitudeSet();
    void setLatitude(int);
    int getLatitude();
};

#endif
