#ifndef DISPLAY_H
#define DISPLAY_H

#include "RGBmatrixPanel.h"

// Metro ESP32-S2
#define CLK  13
#define OE   14
#define LAT 15
#define A   17
#define B   18
#define C   1
#define D   2


class Display{
  public:
    Display(): matrix(A, B, C, D, CLK, LAT, OE, false, 64) {};
    void init();
    void update(String, String, String, String, String);
    void clear();
  private:
    RGBmatrixPanel matrix;
};


#endif