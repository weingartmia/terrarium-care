#include "Context.h"
#include <Arduino.h>
#include "config.h"



Context::Context(): 
    sensorSoil(SENSOR_PIN,POWER_PIN,BORDER_SOIL), 
    sensorDht(DHTPIN,BOTTOM_BORDER_HUMIDITY,TOP_BORDER_HUMIDITY,DHTTYPE), 
    display(SCREEN_WIDTH, SCREEN_HEIGHT,
    OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS),
    pump(WATER_PIN),
    vent(VENT_PIN)
{
   
}

void Context::init(){
    
    Serial.println("~context init");
    setState(new InitState());
    action();
}
void Context:: setState(State* state){
    Serial.println("///state transition///");
    this->state= state;
    this->state->setContext(this);
};

void Context::action(){
    if (this->state != nullptr){
            this->state->handleAction();
    }
    else{
        Serial.println(" -Error state is nullptr- undefined from Context.cpp action ()");
    }
    
    
};
void Context:: getLocalTime() {
    struct tm timeinfo;
    if (&timeinfo) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
}


// void Context::timeOut(){

//     long unsigned Time = millis() ;
//     int interval = Time /60000;// set milliseconds to minutes
//     int timer; 

//   if (interval - timer >= 2 ){
//       timer = interval;
//       state-> handleTimeOut();
//   }

// }