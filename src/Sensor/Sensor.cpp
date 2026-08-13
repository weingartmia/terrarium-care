#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor( uint8_t sensorPin,const int thresholdValue,const int topThresholdValue)
:
 sensorPin(sensorPin),thresholdValue(thresholdValue), topThresholdValue(topThresholdValue)
{
 
}