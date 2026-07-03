#pragma once 
#include "../Component/Component.h"




#ifndef DhtHumiditySensor_h
#define DhtHumiditySensor_h

class DhtHumiditySensor : public Component{
    public:
        DhtHumiditySensor(const int sensorPin,const int thresholdValue,const int topThresholdValue);

        void init() override;
        void read() override;
        bool isValid() override;
        char checkThreshold() override;


        int valueTemperature;
        int valueHumidity;
        const int topThresholdValue;

        
        



};

#endif