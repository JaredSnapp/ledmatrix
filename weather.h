#ifndef WEATHER_H
#define WEATHER_H
#include "Arduino.h"

// typedef struct {
//   int year;
//   int month;
//   int day;
//   int hour;
//   int minute;
//   int second;
// } Timetype

class Weather {
  public:
    Weather();
    void init();
    void update();
    void getTime();
    bool lateNight;
    String temp;
    String metricTemp;
    String humidity;
    String main;
    String sunset;
    String sunrise;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    String time;
    //Timetype time;
  private:
    String extractTime(String);
    String extractTemp(String);
    String extractHumidity(String);
    String extractMain(String);
    String extractSunrise(String);
    String extractSunset(String);
    const char* ssid;
    const char* password;
 
    String endpoint;
    String metricEndpoint;
    String key;

};





#endif