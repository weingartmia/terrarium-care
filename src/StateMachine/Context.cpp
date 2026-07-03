#include "Context.h"

Context::Context()
{
   
}


void Context:: setState(State* state){
    this->state= state;
};

void Context::action(){
    state->handleAction();
};



void Context::timeOut(){

    long unsigned Time = millis() ;
    int interval = Time /60000;// set milliseconds to minutes
    int timer; 

  if (interval - timer >= 2 ){
      timer = interval;
      state-> handleTimeOut();
  }

}