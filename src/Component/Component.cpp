#include "Component.h"
#include <Arduino.h>

Component::Component(uint8_t pin): 
pin(pin){
    isWorking=true;
}

void Component ::init(){
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);

}
void Component:: activate(){
    Serial.println("          ..component action..          ");
    digitalWrite(pin,HIGH);

}

void Component::turnOff(){
    digitalWrite(pin,LOW);
}