#include "SoilHumiditySensor.h"


SoilHumiditySensor::SoilHumiditySensor(const int sensorPin, const int powerPin, const int thresholdValue)
:
Component(sensorPin, thresholdValue), powerPin(powerPin){
}

void  SoilHumiditySensor::init(){

      digitalWrite(powerPin, LOW); // Ensure sensor is off at start

}

int SoilHumiditySensor::readData(int samples){

 
  long total = 0;

  digitalWrite(powerPin, HIGH); // Power ON sensor
  delay(500); // Wait for sensor to stabilize

  for (int i = 0; i < samples; i++) {                    
 total += analogRead(sensorPin);
    delay(10); // Short gap between cycles
 }
 Serial.print(total);

  digitalWrite(powerPin, LOW); // Power OFF sensor
  return total / samples;



}

void SoilHumiditySensor::read(){

    const int data= readData(10);
    this->value = data;
}


