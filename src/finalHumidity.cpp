
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "BasicOTA.hpp"
#include <ArduinoOTA.h>
#include <WiFi.h>
// #include <dht.h>
#define dhtPIN 4
#define dhtTYPE DHT11
#define gnd 3

#define gndhumid 6 // arduino nano doesn't have enough ground and 5V pins. Current is lower but it's safe
#define vcc 5
#define humidpin 2 

#define SCREEN_WIDTH 128 // width,  in pixels
#define SCREEN_HEIGHT 64//  height, in pixels

#define THRESHOLD_HUMIDITY 94 //minimal humisity
#define ERROR_INTERVAL 60
#define WATERING_INTERVAL 1
#define READING_INTERVAL 10

#define WIFI_SSID "TOITOI"
#define WIFI_PASSWORD  "iotnetwork"

float oldhum;
float temperature;
float humidity;

int mainTimer;
int timer;
unsigned long Time;
int interval;

BasicOTA ota;
DHT dht(dhtPIN,dhtTYPE) ;
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void foggerCheck(){
  
  if (humidity < THRESHOLD_HUMIDITY-1){
    if ((interval - timer) ==0 and humidity <= oldhum){
      
      oled.println("fogger isn't working");
 
  }}
 oldhum = humidity;
      
}

void setDisplay(){

  oled.clearDisplay();
  oled.setTextSize(1);          
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);

}

void showWatering(){

  setDisplay();

  oled.println("fogging..");
  oled.display();
}

void showDisplayError(){

  setDisplay();

  oled.println("No data");
  oled.setCursor(0, 20); 
  oled.print("Fogger turns on in ");
  oled.print(60 - (interval - timer));
  oled.print(" min");
  oled.display();

}

void timeCount(){

  int hoursCount = (interval-timer) / 60;
  int minutesCount = (interval-timer) % 60;

  if (hoursCount >=1) {

    oled.print(hoursCount);
    oled.print(" hour/s ");
    oled.print(minutesCount);
    oled.print(" min");
  }

  else {
  
    oled.print(interval - timer);
    oled.print(" min");
  }
  }

void showDisplayValues(){

  setDisplay();

 oled.print("Temperature C ");// text to display
 oled.println(temperature);

 oled.setCursor(0, 15);
 oled.print("Humidity % ");
 oled.println(humidity);

 oled.setCursor(0, 30);

 oled.println("Last fogged ");
 timeCount();
 oled.println(" ago");
 foggerCheck();
 oled.display();  // show on OLED
  }

void doIdleAction(){

  showDisplayValues();
  digitalWrite(humidpin, LOW);

}

bool handleTimeOut(int timeout){

  if (interval - timer >= timeout) {
    timer= interval;
    return true;
  }
  else return false;
}

void doWatering(int typeInterval){

  if (!handleTimeOut(typeInterval))  digitalWrite(humidpin, HIGH);
 
  else digitalWrite(humidpin, LOW);
  

}

void handleErrorAction(){

  doWatering(ERROR_INTERVAL);
  showDisplayError();
}

void handleWatering(){

  doWatering(READING_INTERVAL);
  showWatering();

}

bool checkValidValue(){
  if(humidity > 100||isnan(humidity) ) return false;

  else return true;
}

bool checkHumidityThreshold(){
  if(humidity < THRESHOLD_HUMIDITY) return true;
  else return false;
}

void setPinModes(){
  pinMode(humidpin, OUTPUT); 
  pinMode(gnd, OUTPUT);
  pinMode(gndhumid, OUTPUT);
  pinMode(vcc, OUTPUT);

}

void writePins(){

  digitalWrite(gndhumid, LOW);
  digitalWrite(vcc, HIGH); // using digital pin as 5V
  digitalWrite(gnd, LOW); // using digital pin as ground

}

void handleMainInterval(){

  if (interval - mainTimer >= READING_INTERVAL){
    
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    mainTimer = interval;

    delay(2000);

  }
}

void setup() {

  Serial.begin(115200);
  dht.begin();
  setPinModes();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
   
    Serial.println("Connection Failed! Rebooting...");
    Serial.print('.');
    delay(5000);       
    ESP.restart();
       
    }

    ota.begin(); // Setup settings
    Serial.println(".............Ready ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay();

}



void loop(){

  ota.handle();
  Time = millis() ;
  interval = Time /60000;

  

  writePins();
  handleMainInterval();

    if(!checkHumidityThreshold() && checkValidValue()) doIdleAction();
  
    else if (!checkValidValue()) handleErrorAction();

    else if (checkHumidityThreshold() && checkValidValue()) handleWatering();

}
