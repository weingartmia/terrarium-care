#include "States.h"
#include "SoilHumiditySensor/SoilHumiditySensor.h"

#include <Arduino.h>
using namespace std;




State::State(){};

IdleState::IdleState(){
};

ReadingState::ReadingState(){

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

    SoilHumiditySensor* sensor;
    sensor->read();


}

void ReadingState::handleTimeOut(){
    Serial.println("error timout from resding dtate");
    
}