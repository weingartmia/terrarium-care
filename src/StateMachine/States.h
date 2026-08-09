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
        void handleInterval(int diff); // interval in minutes

        int interval;
        unsigned long Time;
        int timer;

        int wateredTimer;
        

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
        ~ ReadingCheckingState(
            )override
             = default;


};

class IdleState : public TimeHandleState{

    public:

        void handleAction() override;
        void handleTimeOut() override;
        
        ~IdleState()override=default;

        // char name[10] = "idleState";
        
        

};

class ReadingState : public ReadingCheckingState{

    public:

        void handleAction() override;
        ~ReadingState()override=default;


        // char name[13]="readingState";

};

class CheckingState : public ReadingCheckingState{

    public:

        void handleAction() override;
        void checkSensorsThresholds();
        void checkSensorSoilThreshold();
        void checkSensorDhtThreshold();
        void handleCount (int caller);
        ~CheckingState()override=default;


        // char name[14]="checkingState";

};

class InitState : public State{

    public:
        void handleAction() override;
        void handleWifi();
        ~InitState()override=default;

        // char name[10]="InitState";

};

class ErrorState : public TimeHandleState{

    public:
        void handleAction() override;
        void handleTimeOut() override;
        ~ErrorState() override= default;
};

class WateringState : public TimeHandleState{

    public:
        WateringState(int time);
        void handleAction() override;
        void handleTimeOut() override;
        ~WateringState() override=default;
    private:
        int time;



};

class VentingState : public TimeHandleState{

    public:
        void handleAction() override;
        void handleTimeOut() override;
        ~VentingState() override=default;


};

class HumidityControlState : public ReadingCheckingState{
    public:
        void handleAction() override;
        bool checkChangedSoilHumidity(int hum);
        bool checkChangedAirHumidity(float hum);
        void setErrorPump();
        ~HumidityControlState() override=default;

};
