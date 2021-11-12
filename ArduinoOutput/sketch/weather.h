#ifndef WEATHER_H
#define WEATHER_H
#include "Arduino.h"

class Weather {
  public:
    Weather();
    void init();
    void update();
    String temp;
    String humidity;
    String main;
    String sunset;
    String sunrise;
  private:
    String extractTemp(String);
    String extractHumidity(String);
    String extractMain(String);
    String extractSunrise(String);
    String extractSunset(String);
    const char* ssid;
    const char* password;
 
    String endpoint;
    String key;

};





#endif