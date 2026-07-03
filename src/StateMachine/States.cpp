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
        Serial.println("entering idle state from chacking state-> values are ok");
        State* this_state = new IdleState();
    }



}