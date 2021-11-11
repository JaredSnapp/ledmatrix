#include "weather.h"

#include <WiFi.h>
#include "HTTPClient.h"
#include "time.h"


Weather::Weather() {
  this->ssid = "Flux";
  this->password =  "ElectromagneticMagic";
 
  this->endpoint = "http://api.openweathermap.org/data/2.5/weather?q=New York City&units=imperial&APPID=";
  this->key = "52b647c576e7ebf2cfa8e8e9df4ec9ca";
}

void Weather::init() {
 
  //Serial.begin(115200);
 
  WiFi.begin(this->ssid, this->password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}

void Weather::update() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(this->endpoint + this->key); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);

        //String temp = this->extractTemp(payload);
        this->temp = this->extractTemp(payload);
        this->humidity = this->extractHumidity(payload);
        this->main = this->extractMain(payload);
        String sunrise = this->extractSunrise(payload);
        String sunset = this->extractSunset(payload);

        Serial.println("temp: "+ this->temp +", hum: " +this->humidity);
        Serial.println("sunrise: "+ sunrise +", sunset: " +sunset);


      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
}


String Weather::extractTemp(String json) {
  int index = json.indexOf("\"temp\"");
  String temp1 = json.substring(index, index+15);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf(",");
  String temperature = temp1.substring(start+1, end);

  return temperature;
}

String Weather::extractHumidity(String json) {
  int index = json.indexOf("\"humidity\"");
  String temp1 = json.substring(index, index+15);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf("}");
  String humidity = temp1.substring(start+1, end);

  return humidity;
}

String Weather::extractMain(String json) {
  int index = json.indexOf("\"main\":\"");
  String temp1 = json.substring(index, index+30);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf(",");
  String main = temp1.substring(start+1, end);

  return main;
}



String Weather::extractSunrise(String json) {
  int index = json.indexOf("\"sunrise\"");
  String temp1 = json.substring(index, index+25);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf(",");
  String sunrise = temp1.substring(start+1, end);

  //time_t epch = sunrise.toInt;
  //sunrise = String(asctime(gmtime(epch)));

  return sunrise;
}

String Weather::extractSunset(String json) {
  int index = json.indexOf("\"sunset\"");
  String temp1 = json.substring(index, index+25);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf("}");
  String sunset = temp1.substring(start+1, end);

  // Todo need to convert data types
  //time_t epch = sunset.toInt;
  //sunset = String(asctime(gmtime(epch)));

  return sunset;
}