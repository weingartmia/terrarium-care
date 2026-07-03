
#pragma once
#include "../Component/Component.h"

#ifndef SoilHumiditySensor_h
#define SoilHumiditySensor_h

class SoilHumiditySensor : public Component{

    public:
        SoilHumiditySensor(const int sensorPin,const int powerPin, const int  thresholdValue);


        void init() override;
        void read() override;

        int readData(int samples);
        int powerPin;
        int value;


};

#endif