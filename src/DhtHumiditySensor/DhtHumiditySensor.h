#pragma once 
#include "../Sensor/Sensor.h"
#include <DHT.h>



#ifndef DhtHumiditySensor_h
#define DhtHumiditySensor_h

class DhtHumiditySensor : public Sensor{

    private:
        DHT dht;// make instance of dht inside class to encaplsulate
        uint8_t sensorType;

    public:
        DhtHumiditySensor(uint8_t sensorPin,const int thresholdValue,const int topThresholdValue,uint8_t sensorType);

        void init() override;
        void read() override;
        bool isValid() override;
        char checkThreshold() override;
       

        int valueTemperature;
        int valueHumidity;
    
        

        
        



};

#endif