
#pragma once
#include "../Sensor/Sensor.h"

#ifndef SoilHumiditySensor_h
#define SoilHumiditySensor_h

class SoilHumiditySensor : public Sensor{

    public:
        SoilHumiditySensor(uint8_t sensorPin,const int powerPin, const int  thresholdValue);


        void init() override;
        void read() override;
        bool isValid() override;
        char checkThreshold() override;

        int readData(int samples);
        int value;
       

        
    private:
        int powerPin;


};

#endif