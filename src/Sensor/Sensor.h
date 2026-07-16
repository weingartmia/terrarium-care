#pragma once
#include <Arduino.h>

#ifndef Sensor_h
#define Sensor_h
class Sensor {
    public:
        Sensor( uint8_t sensorPin,const int thresholdValue);

        virtual void init()=0;
        virtual void read()=0;
        virtual bool isValid()=0;
        virtual char checkThreshold()=0;

        
        const int thresholdValue;
        uint8_t sensorPin;
       
};
#endif

