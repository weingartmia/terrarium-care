#pragma once
#include "States.h"
#include "SoilHumiditySensor/SoilHumiditySensor.h"
#include "DhtHumiditySensor/DhtHumiditySensor.h"
#include "OledDisplay/OledDisplay.h"
#include "Component/Component.h"

#include "BasicOTA.hpp"
#include <ArduinoOTA.h>
#include <WiFi.h>
        
#ifndef Context_h
#define Context_h

class Context{

    private:
        State* state = nullptr;
        

    public:
        Context();

        BasicOTA ota; // 
        SoilHumiditySensor sensorSoil; // soil sensor object
        DhtHumiditySensor sensorDht; // sensor dht object
        OledDisplay display; //display object

        Component pump; // water pump object
        Component vent; // vent object

        void setState(State* state); // set new state
        void action(); // handle current state logic
        void init();// start state machine context
        void getLocalTime();

        int count = 0;// this isnt encaplsulated

       // char *name = this->state->name;
        
        

};
#endif