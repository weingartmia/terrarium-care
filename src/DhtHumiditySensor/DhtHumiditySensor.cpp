
#include <Arduino.h>
#include "DhtHumiditySensor.h"
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT sensor(DHTPIN,DHTTYPE);

DhtHumiditySensor::DhtHumiditySensor(const int sensorPin, const int thresholdValue, const int topThresholdValue)
:
Component(sensorPin,thresholdValue), topThresholdValue(topThresholdValue)
 {}

void DhtHumiditySensor::init(){

    Serial.println("dht sensor init");
    sensor.begin();
    
}

void DhtHumiditySensor::read(){
    Serial.println("reading from dht sensor...");

    this->valueHumidity= sensor.readHumidity();
    this->valueTemperature= sensor.readTemperature();

    Serial.println("humidity%");
    Serial.printf("%s\n",this->valueHumidity);


}

bool DhtHumiditySensor::isValid(){
    Serial.println("checking if data from dht sensor are valid...");

    if (isnan(this->valueHumidity) || isnan(this->valueTemperature)) {

        Serial.println("failed to read from DHT sensor");
        return false;

    }
    else return true;

}

char DhtHumiditySensor::checkThreshold(){
    Serial.println("checking if data from dht sensor are inside target values...");

    if(this->valueHumidity <= thresholdValue  ){
        Serial.println("data from dht are smaller");
        return 's';

    }
    else if (this->valueHumidity >= topThresholdValue){
        Serial.println("data from dht are bigger");
        return 'b';
    }
    else return 'm';
    


}
