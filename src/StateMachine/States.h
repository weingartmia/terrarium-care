#pragma once
#include "../SoilHumiditySensor/SoilHumiditySensor.h"

class State{
    public:
       State();
       virtual void handleAction() =0;
       virtual void handleTimeOut() =0;
       char name[0];
};

class IdleState : public State{

    public:
        IdleState();
        void handleAction() override;
        void handleTimeOut() override;
        char name[10] = "idleState";
        
        

};

class ReadingState : public State{

    public:
        ReadingState();
        void handleAction() override;
        void handleTimeOut() override;
        char name[13]="readingState";

};

class CheckingState : public State{

    public:
        CheckingState();
        void handleAction() override;
        void handleTimeOut() override;
        char name[14]="checkingState";

};