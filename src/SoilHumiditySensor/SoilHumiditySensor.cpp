#include "SoilHumiditySensor.h"
#include <Arduino.h>


SoilHumiditySensor::SoilHumiditySensor(uint8_t sensorPin, const int thresholdValue,const int topThresholdValue, int max, int min)
:
Sensor(sensorPin, thresholdValue,topThresholdValue), powerPin(powerPin), max(max), min(min){
}

void  SoilHumiditySensor::init(){
    Serial.println("~init of soil sensor from SoilHumiditySensor init()");

    analogReadResolution(12);
    analogSetPinAttenuation(sensorPin, ADC_11db);


}

int SoilHumiditySensor::readData(int samples){


  long total = 0;

  
  delay(500); // Wait for sensor to stabilize

  for (int i = 0; i < samples; i++) {                    
 total += analogRead(sensorPin);
    delay(10); // Short gap between cycles
 }
 

  return total / samples;



}

void SoilHumiditySensor::read(){

    const int data= readData(10);
    
    
    value=data;
    Serial.println(value);
    percent= map(value,min,max,0,100);
    
}

bool SoilHumiditySensor::isValid(){
    Serial.println("-checking if data from soil sensor are valid...");

    if (value==4095) {

        Serial.println("-x soil humidity sensor is most likely not working or the humidity is 0% ");
        return false;

    }
    else return true;

}

char SoilHumiditySensor::checkThreshold(){
    Serial.println("--checking if data from soil humidity sensor are inside target values...");

    if(percent <= thresholdValue  ){
        Serial.println("--x data from soil humidity is smaller)");
        return 's';

    }
    else if(percent >= topThresholdValue){
        Serial.println("--x data from soil humidity are bigger");
        return 'b';
    }

    else return 'm';

}


