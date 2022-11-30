#include "display.h"
//#include "RGBmatrixPanel.h"

void Display::init() {
  // this->matrix(A, B, C, D, CLK, LAT, OE, false, 64);
  this->matrix.begin();

  // draw a pixel in solid white
  this->matrix.drawPixel(0, 0, this->matrix.Color444(4, 4, 4));
  delay(500);

  // fix the screen with green
  this->matrix.fillRect(0, 0, this->matrix.width(), this->matrix.height(), this->matrix.Color444(0, 5, 0));
  delay(500);
  
  // fill the screen with 'black'
  this->matrix.fillScreen(this->matrix.Color444(0, 0, 0));

  // draw some text!
  this->matrix.setTextSize(1);     // size 1 == 8 pixels high
  this->matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
};

  
void Display::update(String temp, String hum, String status, String sunrise, String sunset) {
  // fill the screen with 'black'
  this->matrix.fillScreen(this->matrix.Color444(0, 0, 0));

  this->matrix.setCursor(0,0);
  this->matrix.setTextColor(this->matrix.Color444(0,3,0));

  // Temp and Humidity
  this->matrix.print("Temp ");
  this->matrix.println(temp);
  
  this->matrix.setTextColor(this->matrix.Color444(0,2,2));
  this->matrix.print("Hum ");
  this->matrix.print(hum);
  this->matrix.println("%");


  this->matrix.setTextColor(this->matrix.Color444(2,2,2));
  this->matrix.println(status);
  this->matrix.setTextColor(this->matrix.Color444(2,2,0));
  this->matrix.print(sunrise+"  ");
  this->matrix.print(sunset);
  
}

void Display::clear() {
  this->matrix.fillScreen(this->matrix.Color444(0, 0, 0));
}
  
