#pragma once
#include "States.h"

class Context{

    private:
        State* state;

    public:
        Context();
        void setState(State* state);
        void action();
        void timeOut();
        char *name = this->state->name;
        
        

};