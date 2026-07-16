#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor( uint8_t sensorPin,const int thresholdValue)
:
 sensorPin(sensorPin),thresholdValue(thresholdValue)
{
 
}