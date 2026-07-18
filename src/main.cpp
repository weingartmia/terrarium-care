#include <Arduino.h>
// #include "SoilHumiditySensor/SoilHumiditySensor.h"

#include "StateMachine/Context.h"
// #include "StateMachine/States.h"

// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <DHT.h>

// Define the pin connected to the DATA pin of DHT22
// #define DHTPIN 4
// #define DHTTYPE DHT22

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
// #define OLED_MOSI   9
// #define OLED_CLK   10
// #define OLED_DC    11
// #define OLED_CS    12
// #define OLED_RESET 13

// #define SENSOR_PIN  A0 // Analog input pin for sensor
// #define POWER_PIN  7// Digital pin to power the sensor
// #define BORDER_SOIL 400// Min soil moisture.
// #define WATER_PIN  2//water pump pin



// #define DHTPIN 4
// #define DHTTYPE DHT22

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//   OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// DHT dht(DHTPIN, DHTTYPE);

Context context;
// SoilHumiditySensor soilSensor(SENSOR_PIN ,POWER_PIN,BORDER_SOIL);




// int timer;
// unsigned long Time;
// int interval;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("context is getting ready.... - from void setup main.cpp");
    context.init();
    
    Serial.println("setup finished - from void setup main.cpp");
  // Serial.begin(9600);// i must create new state init state
  // soilSensor.init();
 

  // context.setState(new IdleState());
  // Serial.print("setting up...");

  

  //   if(!display.begin(SSD1306_SWITCHCAPVCC)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
    
  //   display.clearDisplay();
  // }

  // // pinMode()
  // // pinMode(powerPin, OUTPUT);
  // dht.begin();
  // digitalWrite(POWER_PIN, LOW); // Ensure sensor is off at start

}


void loop() {
  // Serial.printf("%s\n",context.name);
  // Serial.println(soilSensor.value);
  
  
  // context.timeOut();

  context.action();
  // context.getLocalTime();
  delay(1000);
  // Time = millis() ;
  // interval = Time /60000; // set milliseconds to minutes

  // if (interval - timer >= 60 ){
  //     contex
  // }

  // int avgReading = getAverageReading(SENSOR_PIN, POWER_PIN, 20); // Take 20 averaged samples
  
  // float humidity= dht.readHumidity();
  // float temperature= dht.readTemperature();

  // Serial.print("Average analog reading: ");
  // Serial.println(avgReading);

  // if ( avgReading > borderSoil){

  //   timer=interval;
  //   digitalWrite(WATER_PIN,HIGH);

  // }
  
  // if (isnan(humidity) || isnan(temperature)) {

  //   Serial.println("Failed to read from DHT22 sensor!");

  // }

  // showOledValues(avgReading,humidity,temperature);


  // delay(2000); // Update every 2 seconds
}


// int getAverageReading(int analogPin, int powerPin, int samples = 10) {
//   long total = 0;

//   digitalWrite(powerPin, HIGH); // Power ON sensor
//   delay(500); // Wait for sensor to stabilize

//   for (int i = 0; i < samples; i++) {                    
//  total += analogRead(analogPin);
//     delay(10); // Short gap between cycles
//  }
//  Serial.print(total);

//   digitalWrite(powerPin, LOW); // Power OFF sensor
//   return total / samples;
// }

// void showOledValues(int soilHumidity, float humidity, float temperature){

//  display.clearDisplay();
//  display.setTextSize(1); // text size

//  display.setCursor(0,1);  
//  display.print("Temperature C ");
//  display.println(temperature);

//  display.setCursor(0,15);  
//  display.print("Humidity %");
//  display.println(humidity);

//  display.setCursor(0, 25);
//  display.print("Soil humidity  ");
//  display.println(soilHumidity);

//  display.setCursor(0, 40);
//  display.println("Last fogged ");
//  showTimeCount();

//  display.println(" ago");

//  display.display();
// }

// void showTimeOnOled(int hours, int minutes ){

//     display.print(hours);
//     display.print(" hour/s ");
//     display.print(minutes);
//     display.print(" min");

// }
// void showTimeCount(){

//   int hoursCount = (interval-timer) / 60;
//   int minutesCount = (interval-timer) % 60;

//   if (hoursCount >=1) {

//     showTimeOnOled(hoursCount,minutesCount);

//   }
//   else if (hoursCount >=24){

//     int daysCount = hoursCount /24;
//     int hoursDaysCount= hoursCount % 24;

//     display.print(daysCount);
//     display.print("day/s and ");
//     showTimeOnOled(hoursDaysCount,minutesCount);

//   }
//   else{
//     display.print(interval - timer);
//     display.print(" min");}
//   }