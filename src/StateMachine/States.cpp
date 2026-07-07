#include "States.h"
#include "SoilHumiditySensor/SoilHumiditySensor.h"

#include <Arduino.h>
using namespace std;




State::State(){};

IdleState::IdleState(){
};

ReadingState::ReadingState(){
};
CheckingState::CheckingState(){
};

void IdleState::handleAction(){
    
    Serial.println("Currently in idlestate");
    
    

}

void IdleState::handleTimeOut(){
    Serial.println("Entering reading state from idlestate");
    
    
    State* this_state = new ReadingState();


    
}

void ReadingState::handleAction(){
  
    Serial.println("reading from sensors");

    SoilHumiditySensor* sensorSoil;
    sensorSoil->read();


}

void ReadingState::handleTimeOut(){
    Serial.println("error timout from reading state");
    
}

void CheckingState:: handleAction(){
    Serial.println("checking values from sensors");

    SoilHumiditySensor* sensorSoil;
    if(sensorSoil->isValid()){
        Serial.println("values from soil sensor are valid");

        if (sensorSoil->checkThreshold()=='m'){
            Serial.println("values from soil sensor are inside threshold-> entering from checking state to idle state");

            State* this_state = new IdleState();
        }
        
    }



}