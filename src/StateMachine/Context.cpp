#include "Context.h"
#include <Arduino.h>
#include "config.h"
#include "time.h"
#include <Wire.h>



Context::Context(): 
    sensorSoil(SENSOR_PIN,BORDER_SOIL,WATER_HUMIDITY,AIR_HUMIDITY), 
    sensorDht(DHTPIN,BOTTOM_BORDER_HUMIDITY,TOP_BORDER_HUMIDITY,DHTTYPE), 
    display(SCREEN_WIDTH, SCREEN_HEIGHT,&Wire, OLED_RESET),
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
    ota.handle();
    Serial.println("/////handling ota///////");
    if (this->state != nullptr){
            this->state->handleAction();
    }
    else{
        Serial.println(" -Error state is nullptr- undefined from Context.cpp action ()");
    }
    
    
};
void Context:: getLocalTime() {
    struct tm timeinfo;
    if (!&timeinfo) {
        Serial.println("Failed to obtain time");
        return;
    }
    
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        
//   Serial.println(&timeinfo, "%A");
//   Serial.print("Month: ");
//   Serial.println(&timeinfo, "%B");
//   Serial.print("Day of Month: ");
//   Serial.println(&timeinfo, "%d");
//   Serial.print("Year: ");
//   Serial.println(&timeinfo, "%Y");
//   Serial.print("Hour: ");
//   Serial.println(&timeinfo, "%H");
//   Serial.print("Hour (12 hour format): ");
//   Serial.println(&timeinfo, "%I");
//   Serial.print("Minute: ");
//   Serial.println(&timeinfo, "%M");
//   Serial.print("Second: ");
//   Serial.println(&timeinfo, "%S");

//   Serial.println("Time variables");
//   char timeHour[3];
//   strftime(timeHour,3, "%H", &timeinfo);
//   Serial.println(timeHour);
//   char timeWeekDay[10];
//   strftime(timeWeekDay,10, "%A", &timeinfo);
//   Serial.println(timeWeekDay);
//   Serial.println();
         

         
    
   
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