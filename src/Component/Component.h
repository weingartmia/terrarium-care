#pragma once
#include <Arduino.h>
#ifndef Component_h

#define  Component_h

class Component {
    private:
       uint8_t pin;
    public:
        Component(uint8_t pin);
        void activate();
        void init();
        void turnOff();
        bool isWorking;

};
#endif