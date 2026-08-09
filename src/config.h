#include <Arduino.h>
// global config

#define SENSOR_PIN  A0 // Analog input pin for sensor
#define BORDER_SOIL 50// Min soil moisture in percent
#define AIR_HUMIDITY 4000 // reading from soil sensor when is in air - absolute minimun
#define WATER_HUMIDITY 1150 // rading from soil sensor in water - absolute maximum

#define DHTPIN 4 // pin for dht
#define DHTTYPE DHT11 // type for dht
#define BOTTOM_BORDER_HUMIDITY 70 // minimal threshold humidity for air
#define TOP_BORDER_HUMIDITY 95 // maximal threshold humidity for air

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

#define WATER_PIN  3//water pump pin
#define VENT_PIN 2 // vent pin


#define MAX_FALILURE_READING 5
// #define WATERING_TIME 10000 // in miliseconds
// #define VENTING_TIME 10000

#define WIFI_SSID "TOITOI"
#define WIFI_PASSWORD  "iotnetwork"

#define INTERVAL_BETWEEN_READINGS 18000 // in seconds
#define WATERING_TIME 30 // time for PUMP to water in seconds
#define WATERING_TIME_IN_ERROR 3
#define VENTING_TIME 30
// const char* SSID= "T-KVL1ES";
// const char* PASSWORD= "558sv41t31rx";

#define NTP_SERVER  "pool.ntp.org"
const long  GMT_OFF_SET_SEC=  3600;    // GMT+1 (adjust as needed)
#define DAY_LIGHT_OFF_SET_SEC   3600 // Daylight saving time offset


