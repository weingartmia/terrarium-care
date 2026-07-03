#pragma once
#include <Arduino.h>

#ifndef Component_h
#define Component_h
class Component {
    public:
        Component(const int thresholdValue, const int sensorPin);

        virtual void init()=0;
        virtual void read()=0;
        virtual bool isValid()=0;
        virtual char checkThreshold()=0;

        int value;
        const int thresholdValue;
        const int sensorPin;
};
#endif

