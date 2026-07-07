
#include "OledDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


OledDisplay::OledDisplay(){};

void OledDisplay::init(){

    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    
    display.clearDisplay();
  
}

void OledDisplay::showOledValues(int soilHumidity, float humidity, float temperature){

    display.clearDisplay();
    display.setTextSize(1); // text size

    display.setCursor(0,1);  
    display.print("Temperature C ");
    display.println(temperature);

    display.setCursor(0,15);  
    display.print("Humidity %");
    display.println(humidity);

    display.setCursor(0, 25);
    display.print("Soil humidity  ");
    display.println(soilHumidity);

    display.setCursor(0, 40);
    display.println("Last fogged ");
    showTimeCount();

    display.println(" ago");

    display.display();

}

void OledDisplay::showTimeCount(){
    
}

void OledDisplay::showTimeOnOled(int hours, int minutes){
    display.print(hours);
    display.print(" hour/s ");
    display.print(minutes);
    display.print(" min");
}
