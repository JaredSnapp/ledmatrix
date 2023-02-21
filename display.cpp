#include "display.h"
//#include <stdio.h>
//#include "RGBmatrixPanel.h"

int purple[3] = {5,1,7};
int green[3] = {0,3,0};
int blue[3] = {0,2,2};
int yellow[3] = {2,2,0};
int black[3] = {0,0,0};
int white[3] = {2,2,2};
int red[3] = {2,0,0};


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

  memcpy(this->line1color, green, sizeof(green));
  memcpy(this->line2color, blue, sizeof(green));
  memcpy(this->line3color, yellow, sizeof(green));
  memcpy(this->line4color, purple, sizeof(green));
};

  
void Display::update(String temp, String hum, String status, String sunrise, String sunset) {
//  memcpy(this->line1color, green, sizeof(green));
//  memcpy(this->line2color, blue, sizeof(green));
//  memcpy(this->line3color, yellow, sizeof(green));
//  memcpy(this->line4color, purple, sizeof(green));
//  this->line2color = blue;
//  this->line3color = yellow;
//  this->line4color = purple;

  // fill the screen with 'black'
  this->matrix.fillScreen(this->matrix.Color444(0, 0, 0));

  this->matrix.setCursor(0,0);

  this->matrix.setTextColor(this->matrix.Color444(this->line1color[0],this->line1color[1],this->line1color[2]));

  // Temp and Humidity
  this->matrix.print("Temp ");
  this->matrix.println(temp);
  
  this->matrix.setTextColor(this->matrix.Color444(this->line2color[0],this->line2color[1],this->line2color[2]));
  this->matrix.print("Hum ");
  this->matrix.print(hum);
  this->matrix.println("%");


  this->matrix.setTextColor(this->matrix.Color444(this->line3color[0],this->line3color[1],this->line3color[2]));
  this->matrix.println(status);
  this->matrix.setTextColor(this->matrix.Color444(this->line4color[0],this->line4color[1],this->line4color[2]));
  this->matrix.print(sunrise+"  ");
  this->matrix.print(sunset);
  
}

void Display::clear() {
  this->matrix.fillScreen(this->matrix.Color444(0, 0, 0));
}
  
