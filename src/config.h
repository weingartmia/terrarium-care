#include <Arduino.h>
// global config

#define SENSOR_PIN  A0 // Analog input pin for sensor
#define POWER_PIN  7// Digital pin to power the sensor
#define BORDER_SOIL 400// Min soil moisture.

#define DHTPIN 4 // pin for dht
#define DHTTYPE DHT22 // type for dht
#define BOTTOM_BORDER_HUMIDITY 85 // minimal threshold humidity for air
#define TOP_BORDER_HUMIDITY 95 // maximal threshold humidity for air

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   11 // also sda on some spi displays
#define OLED_CLK   13 //also scl on some spi displays
#define OLED_DC    10 // dc
#define OLED_CS    12 // cs
#define OLED_RESET 9 //res

#define WATER_PIN  3//water pump pin
#define VENT_PIN 2 // vent pin


#define MAX_FALILURE_READING 5
#define WATERING_TIME 10000 // in miliseconds
#define VENTING_TIME 10000

#define WIFI_SSID "T-KVL1ES"
#define WIFI_PASSWORD  "558sv41t31rx"
// const char* SSID= "T-KVL1ES";
// const char* PASSWORD= "558sv41t31rx";

#define NTP_SERVER  "pool.ntp.org"
#define  GMT_OFF_SET_SEC  3600    // GMT+1 (adjust as needed)
#define DAY_LIGHT_OFF_SET_SEC   3600 // Daylight saving time offset

