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


class App : public WifiCallback 
{
    private:
        bool stopRequested = false;
        
        WifiConnection wifiConn;
        ImageLoader imageLoader;

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
    
    clearScreen();

    Update();
    Render();
    
    drawScreen();

    if(stopRequested){
        Exit();
    }

    delay(50); // optional

}

// Methods
void App::Init(){
    
    initMatrix();

    //wifiConn.Setup("xerazen", "ViennaCalling2308");
    wifiConn.Setup("FRITZ!Box 6660 Cable RK", "88667528509661295011");

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
    
    imageLoader.LoadImageFromURL("http://developer.lametric.com/content/apps/icon_thumbs/28585.gif");
    imageLoader.Update();

}

void App::Update(){
    wifiConn.waitForConnection();
}

void App::Render(){
    imageLoader.Render();
}

void App::Exit(){
}


#endif