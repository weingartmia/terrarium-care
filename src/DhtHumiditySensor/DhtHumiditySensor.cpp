
#include <Arduino.h>
#include "DhtHumiditySensor.h"





DhtHumiditySensor::DhtHumiditySensor(uint8_t sensorPin, const int thresholdValue, const int topThresholdValue, uint8_t sensorType)
:
Sensor(sensorPin,thresholdValue), topThresholdValue(topThresholdValue),sensorType(sensorType), dht(sensorPin,sensorType)
 {}

void DhtHumiditySensor::init(){

    Serial.println("~dht sensor init");
    dht.begin();
    
}

void DhtHumiditySensor::read(){
    Serial.println("reading from dht sensor...");

    valueHumidity= dht.readHumidity();
    valueTemperature= dht.readTemperature();
    // valueHumidity=0;
    // valueTemperature=0;




}

bool DhtHumiditySensor::isValid(){
    Serial.println("-checking if data from dht dht are valid...");

    if ((isnan(valueHumidity) || isnan(valueTemperature)) || valueHumidity>100) {

        Serial.println("-x Error failed to read from DHT dht");
        return false;

    }
    else return true;

}

char DhtHumiditySensor::checkThreshold(){
    Serial.println("-- checking if data from dht dht are inside target values...");

    if(valueHumidity <= thresholdValue  ){
        Serial.println("--x data from dht are smaller");
        return 's';

    }
    else if (valueHumidity >= topThresholdValue){
        Serial.println("--x data from dht are bigger");
        return 'b';
    }
    else return 'm';

}
