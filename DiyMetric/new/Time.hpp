#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <Arduino.h>

namespace Time{
        uint8_t deltaTime;
        unsigned long initFrameTime, lastFrameTime, currentFrameTime;

        void setDeltaTime(uint8_t newDeltaTime){ deltaTime = newDeltaTime; }
        uint8_t& getDeltaTime() {return deltaTime;}
        void setupDeltaTimeCalculation();
        void calculateDeltaTime();
};


// Delta Time calculations
void Time::setupDeltaTimeCalculation(){
    lastFrameTime = 0;
    currentFrameTime = millis();
}

void Time::calculateDeltaTime(){
    lastFrameTime = currentFrameTime;
    currentFrameTime = millis();
    deltaTime = currentFrameTime - lastFrameTime;
}

#endif
