#pragma once



#ifndef State_h
#define State_h
class Context;


class State{
    
    protected:

        Context* context = nullptr;


    
    public:
  
       void setContext(Context* con);
      
       
       virtual void handleAction() =0;
       virtual ~State()= default;
    //    char name[0];
};

#endif
class TimeHandleState : public State{
    public:
        TimeHandleState();
        virtual void handleTimeOut()=0;
        void handleInterval();
        int interval;
        unsigned long Time;
        int timer;
        ~TimeHandleState( 
        ) override= default;

};

class ReadingCheckingState : public State{

    public:
        void readData();

        bool getBothSensorsValidity();
        bool getBothSensorsInvalidity();
        bool getSoilValidity();
        bool getDhtValidity();


};

class IdleState : public TimeHandleState{

    public:

        void handleAction() override;
        void handleTimeOut() override;
        
        ~IdleState(){};

        // char name[10] = "idleState";
        
        

};

class ReadingState : public ReadingCheckingState{

    public:

        void handleAction() override;


        // char name[13]="readingState";

};

class CheckingState : public ReadingCheckingState{

    public:

        void handleAction() override;
        void checkSensorsThresholds();
        void checkSensorSoilThreshold();
        void checkSensorDhtThreshold();
        void handleCount (int caller);


        // char name[14]="checkingState";

};

class InitState : public State{

    public:
        void handleAction() override;
        void handleWifi();

        // char name[10]="InitState";

};

class ErrorState : public TimeHandleState{

    public:
        void handleAction() override;
        void handleTimeOut() override;
        ~ErrorState() override= default;
};

class WateringState : public State{

    public:
        void handleAction() override;


};

class VentingState : public State{

    public:
        void handleAction() override;


};

class HumidityControlState : public ReadingCheckingState{
    public:
        void handleAction() override;
        bool checkChangedSoilHumidity(int hum);
        bool checkChangedAirHumidity(float hum);
        void setErrorPump();

};
