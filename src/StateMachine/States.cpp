#include "States.h"
#include "Context.h"
#include <Arduino.h>
#include "config.h"

#include <WiFi.h>






void State::setContext(Context* con){
    Serial.println("--setting new instance of context--");
    this->context=con;
}
TimeHandleState::TimeHandleState():Time(millis()),interval(Time/60000),timer(Time/60000) {
    // Time= millis();
    // interval = Time /60000;
    // timer= interval;
};

void TimeHandleState::handleInterval(){
    Serial.println(Time);
    Time = millis() ;
    interval = Time /60000;// set milliseconds to minutes
     


    if (interval - timer >= 2 ){
        Serial.println("here");
        timer = interval;
        handleTimeOut();
      
    }


}
void ReadingCheckingState::readData(){
    
    this->context->display.showReading();
    this->context->sensorSoil.read();
    Serial.println(this->context->sensorSoil.value);

    this->context->sensorDht.read();
    Serial.println(this->context->sensorDht.valueHumidity);
    Serial.println(this->context->sensorDht.valueTemperature);

}
bool ReadingCheckingState :: getBothSensorsValidity(){
    if(this->context->sensorSoil.isValid() && this->context->sensorDht.isValid()){ //returns true if both sensors are working
       
        return true;
    }
    else return false;

}

bool ReadingCheckingState :: getBothSensorsInvalidity(){
    if(!this->context->sensorSoil.isValid() && !this->context->sensorDht.isValid()){ //returns true if both sensors arent workign
        return true;
    }
    else return false;

}
bool ReadingCheckingState :: getSoilValidity(){
    if(this->context->sensorSoil.isValid() && !this->context->sensorDht.isValid()){ //returns true if only soil sensors is working
        return true;
    }
    else return false;

}
bool ReadingCheckingState :: getDhtValidity(){
    if(!this->context->sensorSoil.isValid() && this->context->sensorDht.isValid()){ //returns true if only dht is working
        return true;
    }
    else return false;

}

void IdleState::handleAction(){
    
    
    Serial.println("      Currently in idlestate...");
    handleInterval();

    this->context->display.showDhtData(this->context->sensorDht.valueHumidity,this->context->sensorDht.valueTemperature);
    this->context->display.showSoilData(this->context->sensorSoil.value);   
    this->context->display.showOledValues(interval,timer);

}

void IdleState::handleTimeOut(){

     Serial.println("->Entering reading state from Init State");
     this->context->setState(new ReadingState());
 
    
}

void ReadingState::handleAction(){
  
    Serial.println("      Currently in reading state reading from sensors...");
    readData();

    Serial.println("->Entering checking state from reading state");

    this->context->setState(new CheckingState());



}


void CheckingState:: handleCount(int caller){
    
    this->context->count++;
    this->context->setState(new ReadingState());
    this->context->display.showRereading(this->context->count);

    if (this->context->count >=MAX_FALILURE_READING){

        Serial.println("    -==count is bigger/equal to MAX_FAILURE_READING ");

        this->context->count =0;

        if (caller==0) {
            Serial.println("                          failure caller is  dht sensor");
            checkSensorSoilThreshold();
        }

        else if (caller==1){
             Serial.println("                          failure caller are both sensors");
            Serial.println("->Entering error state from checking state");
            this->context->setState(new ErrorState());

        }
        else if (caller ==2) {
            Serial.println("                          failure caller is  soil sensor");
            checkSensorDhtThreshold();}
               
    }
}
void CheckingState :: checkSensorsThresholds(){

            if (this->context->sensorSoil.checkThreshold()=='m' && this->context->sensorDht.checkThreshold()=='m' ){

                Serial.println("==data from sensors are inside threshold void checkSensorsThreshold()");
                Serial.println("-> entering from checking state to idle state");
                this->context->setState(new IdleState());    
            }
            else if(this->context->sensorSoil.checkThreshold()=='s' || this->context->sensorDht.checkThreshold()=='s'){
                Serial.println("==one of sensors humidity is smaller void checkSensorsThreshold()");
                Serial.println("-> entering from checking state to watering state");
                this->context->setState(new WateringState()); 
                
                
            }
            else if(this->context->sensorDht.checkThreshold()=='b'){
                Serial.println("==dht humidity is bigger void checkSensorsThreshold()");
                Serial.println("-> entering from checking state to venting state");
                this->context->setState(new VentingState()); 
                
            }

}

void CheckingState :: checkSensorDhtThreshold(){

            if (this->context->sensorDht.checkThreshold()=='m' ){

                Serial.println("==data from dht sensor is inside threshold void checkSensorDhtThreshold()");
                Serial.println("-> entering from checking state to error state");
                this->context->setState(new ErrorState());    
            }
            else if(this->context->sensorDht.checkThreshold()=='s'){
                Serial.println("==dht sensor  humidity is smaller void checkSensorDhtThreshold()");
                Serial.println("-> entering from checking state to watering state");
                this->context->setState(new WateringState()); 
                
                
            }
            else if(this->context->sensorDht.checkThreshold()=='b'){
                Serial.println("==dht humidity is bigger void checkSensorDhtThreshold()");
                Serial.println("-> entering from checking state to venting state");
                this->context->setState(new VentingState()); 
                
            }

}
void CheckingState :: checkSensorSoilThreshold(){

            if (this->context->sensorSoil.checkThreshold()=='m' ){

                Serial.println("==data from soil sensor is inside threshold void checkSensorSoilThreshold()");
                Serial.println("-> entering from checking state to error state");
                this->context->setState(new ErrorState());    
            }
            else if(this->context->sensorSoil.checkThreshold()=='s'){
                Serial.println("==soil sensors humidity is smaller void checkSensorSoilThreshold()");
                Serial.println("-> entering from checking state to watering state");
                this->context->setState(new WateringState());  
                
                
            }
            else {
                Serial.println( "Error trying to analyse soil sensor data");
            }


}



void CheckingState:: handleAction(){

    Serial.println("      Currently in checking state and checking values from sensors...");
    Serial.println(this->context->sensorSoil.value);
    this->context->display.showChecking();
       
    if(getBothSensorsValidity()){ //ckeck data validity
        checkSensorsThresholds(); 
    }

    else if(getBothSensorsInvalidity()){

        Serial.println("===========both sensor data arent valid void handleAction() CheckingState");
        Serial.print("increasing count...");
        Serial.print(this->context->count);
        handleCount(1);
    }
    else if (getSoilValidity()) {

        Serial.println("========= dht sensor isnt valid void handleAction() CheckingState");
        Serial.print("increasing count...");
        Serial.print(this->context->count);
        handleCount(0);
    }
    else if(getDhtValidity()){
        Serial.println("========== soil sensor isnt valid void handleAction() CheckingState");
        Serial.print("increasing count...");
        Serial.print(this->context->count);
        handleCount(2);        
    }
}
void InitState::handleWifi(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        this->context->display.showMessage("failed to connect to wifi");
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
        
    }

    this->context->ota.begin(); // Setup settings
    Serial.println(".............Ready ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    configTime(GMT_OFF_SET_SEC, DAY_LIGHT_OFF_SET_SEC, NTP_SERVER);

}
void InitState::handleAction(){
  
  if (this->context != nullptr){
    Serial.println("~setting everything up... from init state");

    this->context->sensorSoil.init();
    this->context->sensorDht.init();
    this->context->display.init();
    this->context->pump.init();

    handleWifi();
    Serial.println("->leaving init state entering idle state ");
    this->context->setState(new ReadingState());
  }
  else Serial.println("-Error context is undefined from init state");
}


void ErrorState ::handleAction(){
    Serial.println("    Currently in Error state failed....");
    handleInterval();

    if (this->context->sensorDht.isValid()) this->context->display.showDhtData(this->context->sensorDht.valueHumidity,this->context->sensorDht.valueTemperature);
    else this->context->display.showDhtFail();

    if (this->context->sensorSoil.isValid()) this->context->display.showSoilData(this->context->sensorSoil.value);
    else this->context->display.showSoilFail();

    if(!this->context->pump.isWorking) this->context->display.showWaterPumpFail();

        
    this->context->display.showOledValues(interval,timer);

}

void ErrorState::handleTimeOut(){
    Serial.println("timeout from error state...");

    // this->context->pump.water(WATERING_TIME);
    this->context->setState(new WateringState());
    
}

void WateringState :: handleAction(){

    Serial.println("        Curently in watering state and watering....");
    this->context->display.showWatering();
    this->context->pump.activate(WATERING_TIME);
    Serial.println("->Entering HumidityControlState from WAtering State");
    this->context->setState(new HumidityControlState()); 
}

void VentingState :: handleAction(){

    Serial.println("        Curently in venting state and venting....");
    this->context->display.showWatering();
    this->context->vent.activate(VENTING_TIME);
    Serial.println("->Entering HumidityControlState from WAtering State");
    this->context->setState(new ReadingState()); 
}

bool HumidityControlState :: checkChangedAirHumidity(float hum){
    if(hum< this->context->sensorDht.valueHumidity ) return true;
    else return false;

}
bool HumidityControlState :: checkChangedSoilHumidity(int hum){
    if(hum > this->context->sensorSoil.value ) return true;
    else return false;

}
void HumidityControlState :: setErrorPump(){
    Serial.println(" Error humidity hasnt increased");
    this->context->pump.isWorking= false;
    this->context->setState(new ErrorState());
}
void HumidityControlState :: handleAction(){

  
    float hum = this->context->sensorDht.valueHumidity;
    int humS= this->context->sensorSoil.value;
    

    Serial.println("        Curently in humidity control state and  controlling humidity after vent/pump action....");
    readData();

    if(getBothSensorsValidity()){
        if (checkChangedAirHumidity(hum) || checkChangedSoilHumidity(humS)) {

            Serial.println("******both sesnors are returning valid");
    
            Serial.println("humidity has ncreased");
            Serial.println("->Entering Idle state from humidity control state");
            this->context->pump.isWorking = true;

            this->context->display.showHumidityIncreased();
            this->context->setState(new IdleState());
        }
        else setErrorPump();
        
    }
    else if(getSoilValidity()){
        if (checkChangedSoilHumidity(humS)) {
            Serial.println("******only soil humidity sensor is valid");
            Serial.println("humidity has increased");
            Serial.println("->Entering Error state from humidity control state");
            this->context->pump.isWorking = true;
            
            this->context->display.showHumidityIncreased();
            this->context->setState(new ErrorState());
        }
        else setErrorPump();


    }
    else if(getDhtValidity()){
        if (checkChangedAirHumidity(hum)) {
            Serial.println("******only dht humidity sensor is valid");
            Serial.println("humidity has increased");
            Serial.println("->Entering Error state from humidity control state");
            this->context->pump.isWorking = true;

            this->context->display.showHumidityIncreased();
            this->context->setState(new ErrorState());
        }
        else setErrorPump();

    }
    else if(getBothSensorsInvalidity()){
        Serial.println("->Entering Error state from humidity control state");
        this->context->setState(new ErrorState());

    }

}