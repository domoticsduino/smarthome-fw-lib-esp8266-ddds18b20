/* 1.0.0 VERSION */

#ifndef ddds18b20_h
#define ddds18b20_h

#include "OneWire.h"
#include "DallasTemperature.h"

struct DDDS18B20Val{

    float tempC = 0.0;
    float tempF = 0.0;
    bool success;
    const char* errorMsg;

};

class DDDS18B20{

    private:
        OneWire _oneWire = OneWire(0);
        DallasTemperature _ds18b20 = DallasTemperature(&_oneWire);
        int _led;

    public:
        DDDS18B20(int, int);
        void beginSensor();
        void setResolution(DeviceAddress, int);
        DDDS18B20Val getValueBus(DeviceAddress, bool);
        DDDS18B20Val getValue();

};

#endif