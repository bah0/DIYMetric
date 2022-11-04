// File: App.hpp
// Description: Entry Class after DiyMetric.ino
// Responsible for controlling the workflow of the App
//
//

#ifndef _APP_H_
#define _APP_H_

#include <stdio.h>
#include "WifiConnection.hpp"
#include "ImageLoader.hpp"
#include "Time.hpp"


class App : public WifiCallback{
    private:
        bool stopRequested = false;

    public:
        App();
        virtual ~App();
        void Setup();
        void Init();
        void Update();
        void Render();
        void Loop();
        void Exit();

        // Wifi related methods - WifiConnection needs to be implemented here
         void onWifiConnectedCallback();
         void onWifiConnectingCallback();
         void onWifiActiveCallback();
};

// Default Constructor
App::App(){}
App::~App(){}

void App::Setup(){
    Serial.begin(9600);
    Init();

    Time::setupDeltaTimeCalculation();
}

void App::Loop(){
    Time::calculateDeltaTime();
    
    //Update();
    //Render();

    if(stopRequested){
        Exit();
    }

    delay(50); // optional

}

// Variables
WifiConnection wifiConn;
ImageLoader imageLoader;

// Methods
void App::Init(){
    
    initMatrix();

    wifiConn.Setup("xerazen", "ViennaCalling2308");
    wifiConn.Connect();
    wifiConn.setWifiCallback(this);

}

void App::onWifiConnectingCallback(){
    ledMatrix.setCursor(0,6);
    ledMatrix.print("Connecting");
}

void App::onWifiConnectedCallback(){
    Serial.println("WIFI Connected in callback");
}

void App::onWifiActiveCallback(){
    //Serial.println("WIFI is active.");
    
    imageLoader.LoadImageFromURL("a");
    imageLoader.Update();

}


void App::Update(){
    wifiConn.waitForConnection();
}

void App::Render(){
    clearScreen();
    imageLoader.Render();
    drawScreen();
}

void App::Exit(){

}


#endif