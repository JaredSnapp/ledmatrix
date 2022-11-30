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

    this->getTime();
 
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
        this->sunrise = this->extractSunrise(payload);
        this->sunset = this->extractSunset(payload);

        //Serial.println("temp: "+ this->temp +", hum: " +this->humidity);
        //Serial.println("sunrise: "+sunrise);
        //Serial.println("sunset: "+sunset);

      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
}

void Weather::getTime() {
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
        HTTPClient http;
    
        http.begin("http://worldtimeapi.org/api/timezone/America/New_York"); //Specify the URL
        int httpCode = http.GET();  //Make the request
    
        if (httpCode > 0) { //Check for the returning code
    
            String payload = http.getString();
            Serial.println(httpCode);
            Serial.println(payload);

            //String temp = this->extractTemp(payload);
            //this->time = this->extractTemp(payload);
            // if (this->time > 11 || this->time < 8) {
                //this->lateNight = true;
            //}
            //else {
                //this->lateNight = false;
            //}

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

  int start = temp1.indexOf(":\"");
  int end = temp1.indexOf("\",");
  String main = temp1.substring(start+2, end);

  return main;
}



String Weather::extractSunrise(String json) {
  int index = json.indexOf("\"sunrise\"");
  String temp1 = json.substring(index, index+25);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf(",");
  String sunrise = temp1.substring(start+1, end);

  time_t epch = long(sunrise.toInt());
  sunrise = String(asctime(gmtime(&epch)));
  start = sunrise.indexOf(":")-2;
  sunrise = sunrise.substring(start, start+5);

  // convert to est time
  int hour = sunrise.substring(0,2).toInt()-5;
  sunrise = String(hour)+sunrise.substring(2);

  return sunrise;
}

String Weather::extractSunset(String json) {
  int index = json.indexOf("\"sunset\"");
  String temp1 = json.substring(index, index+25);

  int start = temp1.indexOf(":");
  int end = temp1.indexOf("}");
  String sunset = temp1.substring(start+1, end);

  time_t epch = long(sunset.toInt());
  sunset = String(asctime(gmtime(&epch)));
  start = sunset.indexOf(":")-2;
  sunset = sunset.substring(start, start+5);

  // convert to est time
  int hour = sunset.substring(0,2).toInt()-17;
  sunset = String(hour)+sunset.substring(2);

  return sunset;
}