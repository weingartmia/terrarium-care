
#pragma once


#ifndef OledDisplay_h
#define OledDisplay_h

class OledDisplay{

    public:
        OledDisplay();
        void showOledValues(int soilHumidity, float humidity, float temperature);
        void showTimeOnOled(int hours, int minutes );
        void showTimeCount();
        void init();


};
#endif