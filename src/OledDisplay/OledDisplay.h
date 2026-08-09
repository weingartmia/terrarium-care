
#pragma once
#include <Arduino.h>
// #include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <string>

#ifndef OledDisplay_h
#define OledDisplay_h

class OledDisplay{
    
    private:
        int screenWidth;
        int screenHeight;
        // int mosi;
        // int clk;
        // int dc;
        int reset;
        // Wire *wire;
        TwoWire* wire;
        // int cs;


        Adafruit_SSD1306 display;


    public:
        OledDisplay(int screenWidth, int screenHeight,TwoWire* wire,int reset);

        void showOledValues(int interval, int timer);
        void showDhtData(float humidity, float temperature);
        void showSoilData(int soilHumidity);

        void showDhtFail();
        void showSoilFail();
        void showWaterPumpFail();
        void showHumidityIncreased();

        void showTimeOnOled(int hours, int minutes );
        void showTimeCount(int interval, int timer);

        void showReading();
        void showChecking();
        void showRereading(int count);
        void showWatering();

        void showMessage(String message);

        void init();



};
#endif