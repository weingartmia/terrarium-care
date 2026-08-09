
#pragma once
#include "../Sensor/Sensor.h"

#ifndef SoilHumiditySensor_h
#define SoilHumiditySensor_h

class SoilHumiditySensor : public Sensor{

    public:
        SoilHumiditySensor(uint8_t sensorPin, const int  thresholdValue, int max,int min);


        void init() override;
        void read() override;
        bool isValid() override;
        char checkThreshold() override;

        int readData(int samples);
        
        int percent;
       

        
    private:
        int max;
        int min;
        int powerPin;
        int value;


};

#endif