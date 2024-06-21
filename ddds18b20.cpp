/* 1.0.0 VERSION */

#include "ddds18b20.h"

DDDS18B20::DDDS18B20(int led, int pin){
    this-> _led = led;
    this-> _oneWire = OneWire(pin);
    this-> _ds18b20 = DallasTemperature(&this-> _oneWire);
}

void DDDS18B20::beginSensor(){
    this-> _ds18b20.begin();
}

DDDS18B20Val DDDS18B20::getValue(){
    float tempC;
    float tempF;
    DDDS18B20Val ret;
    int max = 50;
    int count = 0;

    do {
        this-> _ds18b20.requestTemperatures(); 
        tempC = this-> _ds18b20.getTempCByIndex(0);
        tempF =  this-> _ds18b20.getTempFByIndex(0);
        delay(100);
    } while (count++ < 50 && (tempC == 85.0 || tempC == (-127.0)));

    if(tempC == 85.0 || tempC == (-127.0)){
        ret.success = false;
        ret.errorMsg = "Failed to read from DS18B20 sensor!";
    }
    else{
        ret.tempC = tempC;
        ret.tempF = tempF;
        ret.success = true;
        ret.errorMsg = "";
    }

    return ret;
}

void DDDS18B20::setResolution(DeviceAddress probe, int res){
    this-> _ds18b20.setResolution(probe, res);
}

DDDS18B20Val DDDS18B20::getValueBus(DeviceAddress probe, bool first){
    float tempC;
    float tempF;
    DDDS18B20Val ret;
    int max = 50;
    int count = 0;

    do {
        if(first)
            this-> _ds18b20.requestTemperatures(); 

        tempC = this-> _ds18b20.getTempC(probe);
        tempF =  DallasTemperature::toFahrenheit(tempC);
        delay(100);
    } while (count++ < 50 && (tempC == 85.0 || tempC == (-127.0)));

    if(tempC == 85.0 || tempC == (-127.0)){
        ret.success = false;
        ret.errorMsg = "Failed to read from DS18B20 sensor!";
    }
    else{
        ret.tempC = tempC;
        ret.tempF = tempF;
        ret.success = true;
        ret.errorMsg = "";
    }

    return ret;
}