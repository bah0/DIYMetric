#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const bool dayLightSaving = true;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

struct utime {
  int hours;
  int minutes;
  int seconds;
  int week_day;
};



void ntp_client_setup(){
  timeClient.begin();
}

bool blinkState = true;

String formatUtime(utime& time, bool includeSeconds = false, bool blinkSymbol = true){
  String temp ="0" + String(time.hours); 
  String h = (time.hours   < 10)? temp : String(time.hours);
  temp ="0" + String(time.minutes); 
  String m = (time.minutes < 10)? temp : String(time.minutes);
  temp ="0" + String(time.seconds); 
  String s = (time.seconds < 10)? temp : String(time.seconds);

  String retStr = (includeSeconds)? h+":"+m+":"+s : h+":"+m ;
  if(blinkSymbol){
    if(blinkState) retStr.replace(":"," ");
    blinkState = !blinkState;
  }
  return retStr;
}

String ntp_get_time() {
  
  timeClient.update();
  String da = daysOfTheWeek[timeClient.getDay()];
  /*int h = timeClient.getHours();
  int m = timeClient.getMinutes();*/
  /*int s = timeClient.getSeconds();*/
  String h;
  String m;
  if (timeClient.getHours() < 10)
  {
    h = "0" + String(timeClient.getHours());
  }
  else
  {
    h = String(timeClient.getHours());
  }
  if (timeClient.getMinutes() < 10)
  {
    m = "0" + String(timeClient.getMinutes());
  }
  else
  {
    m = String(timeClient.getMinutes());
  }
  String ts = h + ":" + m; 
  Serial.println("Day: " + da);
  Serial.println(ts); /*+ ":" + m + ":" + s);*/
  return ts;
}

void ntp_get_time(utime* time) {
  timeClient.update();
  time->week_day  = timeClient.getDay();
  time->hours     = timeClient.getHours();
  time->minutes   = timeClient.getMinutes();
  time->seconds   = timeClient.getSeconds();
  
  if(dayLightSaving) time->hours     = timeClient.getHours() + 1;
  //String day = daysOfTheWeek[timeClient.getDay()];
}
