
#include "OledDisplay.h"
#include "config.h"
#include <Arduino.h>
#include <Wire.h>

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

OledDisplay::OledDisplay(int screenWidth, int screenHeight,TwoWire *wire, int reset)
:screenWidth(screenWidth), screenHeight(screenHeight),  reset(reset), wire(wire), display(screenWidth,screenHeight,wire,reset){};

void OledDisplay::init(){
    Serial.println("~init of oled");

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    
    display.clearDisplay();
    display.setTextSize(1); // text size
    display.setTextColor(SSD1306_WHITE);  
    display.setCursor(0,1);
  
}

void OledDisplay::showDhtFail(){
    Serial.println("------showing dht fail on oled------");
   
    display.clearDisplay();
    display.setTextSize(1); // text size

    display.setCursor(0,1);  
    display.print("Unable to read from  dht ");


}
void OledDisplay :: showDhtData( float humidity, float temperature){
    Serial.println("------showing dht values on oled------");
   
    display.clearDisplay();
    display.setTextSize(1); // text size


    display.setCursor(0,1);  
    display.print("Temperature C ");
    display.println(temperature);

    display.setCursor(0,15);  
    display.print("Humidity % ");
    display.println(humidity);

}
void OledDisplay ::showSoilData(int soilHumidity){
    
        display.setCursor(0, 25);
        display.print("Soil humidity % ");
        display.println(soilHumidity);

}
void OledDisplay ::showSoilFail(){
    
        display.setCursor(0, 25);
        display.print("Unable to read from soil sensor");


}
void OledDisplay ::showWaterPumpFail(){
        Serial.println("-------showing water pupm fail in oled---------");
        display.setCursor(0, 53);
        display.print("Pump isn't working");


}
void OledDisplay::showOledValues(int interval, int timer){

    display.setCursor(0, 35);
    display.print("Last watered ");
    showTimeCount(interval, timer);

    display.print("   ago");

    display.display();

}

void OledDisplay::showTimeCount(int interval, int timer){
    int hoursCount = (interval-timer) / 60;
    int minutesCount = (interval-timer) % 60;

    if (hoursCount >=1) {

        showTimeOnOled(hoursCount,minutesCount);

    }
    else if (hoursCount >=24){

        int daysCount = hoursCount /24;
        int hoursDaysCount= hoursCount % 24;

        display.print(daysCount);
        display.print("day/s and ");
        showTimeOnOled(hoursDaysCount,minutesCount);

    }
    else{
        display.print(interval - timer);
        display.print(" min");
    }
  
    
}

void OledDisplay::showTimeOnOled(int hours, int minutes){
    Serial.println("------showing time on oled------");
    display.print(hours);
    display.print(" hour/s ");
    display.print(minutes);
    display.print(" min");
}

void OledDisplay::showReading(){
    Serial.println("------showing reading on oled------");
    display.clearDisplay();
    display.setCursor(0,1);
    display.setTextSize(1); // text size
    display.println("reading sensor data..");
    display.display();
    // delay(1000);
}

void OledDisplay::showChecking(){
    Serial.println("------showing checking on oled------");
    display.clearDisplay();
    display.setCursor(0,25);
    display.setTextSize(1); // text size
    display.println("processing sensor    data");
    display.display();
    // delay(50);

}

void OledDisplay::showRereading(int count){
     Serial.println("------showing re reading on oled------");
    display.clearDisplay();
    display.setCursor(0,1);
    display.setTextSize(1); // text size
    display.println("error failed to read from sensor data! ");
    display.print("retrying : ");
    display.print(count);
    display.print("/");
    display.print(MAX_FALILURE_READING);

    display.display();
    // delay(500);

}

void OledDisplay::showWatering(){
    Serial.println("------showing watering on oled------");
    display.clearDisplay();
    display.setCursor(0,1);
    display.setTextSize(1); // text size
    display.println("currently watering...");
    display.println("water pump is on ");
    display.display();

}

void OledDisplay::showHumidityIncreased(){
    display.println("humdity has increased");

    display.display();

}

void OledDisplay ::showMessage(String message){
    Serial.println("------showing message on oled------");
    display.clearDisplay();
    display.setCursor(0,25);
    display.setTextSize(1); // text size
    display.println(message);
    display.display();
    // delay(500);

}
