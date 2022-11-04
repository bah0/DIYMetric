// This file is responsible for Wifi Connection.
// It is loosely coupled and can be integrated by defined callbacks to any class. 
//
// Callback class must be inherited and following methods have to be called in order:
// WifiConnection wifiConn;
// 
// wifiConn.Setup("xerazen", "ViennaCalling2308");
// wifiConn.Connect();
// 
// wifiConn.setWifiCallback(this);
// 
// inside loop function: wifiConn.waitForConnection();
//
//
// void App::onWifiConnectingCallback(){
//     Serial.println("WIFI is connecting in callback");
// }
// void App::onWifiConnectedCallback(){
//     Serial.println("WIFI Connected in callback");
// }
//
// 
//
//
// Reference: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#diagnostics

#ifndef _WIFICONNECTION_H_
#define _WIFICONNECTION_H_

#define WIFI_LED 2 /*D4 GPIO2*/
#undef NW_DEBUG

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino.h>

class WifiCallback {
    public:
        virtual void onWifiConnectedCallback() = 0;
        virtual void onWifiConnectingCallback() = 0;
        virtual void onWifiActiveCallback() = 0;
        
};

class WifiConnection
{
private:
    String ssid;
    String password;
    const String hostname = "DIYMetric"; // TODO: maybe not const -> so we dont have to modify this class
    bool connectInitiated = false;
    int wifiBlink;
    int prevState;
    WifiCallback* wifiCallback;

public:
    int isConnected();
    void Connect();
    virtual void Disconnect();
    void Setup(String ssid, String password);
    int getStatus();
    
    void waitForConnection();
    void setWifiCallback(WifiCallback* wifiCallback);
};

void WifiConnection::Setup(String nssid, String npassword)
{
    ssid = nssid;
    password = npassword;
    wifiBlink = 0;

    pinMode(WIFI_LED, OUTPUT);
    
    /*Disable WIFI AP*/
    WiFi.softAPdisconnect(true);
    WiFi.hostname(hostname);
}

void WifiConnection::setWifiCallback(WifiCallback* callback){
    wifiCallback = callback;
}

void WifiConnection::waitForConnection() //Wifi Event handling and calling the callbacks
{
    #ifdef NW_DEBUG
    Serial.printf("Connection status: %d\n", WiFi.status());
    #endif 

    switch (isConnected()) // TODO: offload every outcome into seperate private methods to make this code readable
    {
        case WL_IDLE_STATUS: // is this triggered while connecting?
            break;

        case WL_NO_SSID_AVAIL:
            break;
        
        case WL_CONNECTED:
            if(prevState != WL_CONNECTED) {
                digitalWrite(WIFI_LED, LOW);
                if (wifiCallback) wifiCallback->onWifiConnectedCallback();
            }
            if (wifiCallback) wifiCallback->onWifiActiveCallback();
            break;

        case WL_CONNECT_FAILED:
            break;

        case WL_WRONG_PASSWORD:
            break;

        case WL_DISCONNECTED: // still disconnected while connecting

            digitalWrite(WIFI_LED, wifiBlink++ & 1 == 0 ? HIGH : LOW);

            if (wifiCallback) wifiCallback->onWifiConnectingCallback();

            break;

        case -1: // Connect not initiated e.g. connectInitialized = false
            break;
        
        default: // Other issues
            break;
    }

    prevState = WiFi.status();
}

void WifiConnection::Connect()
{
    prevState = WiFi.status();
    WiFi.begin(ssid, password);
    connectInitiated = true;
}

void WifiConnection::Disconnect()
{
}

int WifiConnection::isConnected()
{
    return connectInitiated ? WiFi.status() : -1;
}

int WifiConnection::getStatus()
{
    return WiFi.status();
}

#endif