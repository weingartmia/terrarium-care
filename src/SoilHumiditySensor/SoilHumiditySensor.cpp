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

bool SoilHumiditySensor::isValid(){
    Serial.println("checking if data from dht sensor are valid...");

    if (this->value==0) {

        Serial.println("soil humidity sensor is most likely not working or the humidity is 100% ");
        return false;

    }
    else return true;

}

char SoilHumiditySensor::checkThreshold(){
    Serial.println("checking if data from soil humidity sensor are inside target values...");

    if(this->value <= thresholdValue  ){
        Serial.println("data from soil humidity are smaller");
        return 's';

    }

    else return 'm';

}


