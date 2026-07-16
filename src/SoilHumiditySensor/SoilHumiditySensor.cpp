#include "SoilHumiditySensor.h"
#include <Arduino.h>

SoilHumiditySensor::SoilHumiditySensor(uint8_t sensorPin, const int powerPin, const int thresholdValue)
:
Sensor(sensorPin, thresholdValue), powerPin(powerPin){
}

void  SoilHumiditySensor::init(){
      Serial.println("~init of soil sensor from SoilHumiditySensor init()");
      pinMode(powerPin, OUTPUT);
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
 

  digitalWrite(powerPin, LOW); // Power OFF sensor
  return total / samples;



}

void SoilHumiditySensor::read(){

    const int data= readData(10);
    
    value=data;
    
}

bool SoilHumiditySensor::isValid(){
    Serial.println("-checking if data from soil sensor are valid...");

    if (value==0) {

        Serial.println("-x soil humidity sensor is most likely not working or the humidity is 100% ");
        return false;

    }
    else return true;

}

char SoilHumiditySensor::checkThreshold(){
    Serial.println("--checking if data from soil humidity sensor are inside target values...");

    if(value >= thresholdValue  ){
        Serial.println("--x data from soil humidity are bigger(humidity is smaller)");
        return 's';

    }

    else return 'm';

}


