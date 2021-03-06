/*
  LEDGraphShield - Library long LED bar graph matrix.
  Created by Corey McCall, November 9, 2011.
  Released into the public domain.
  
  Version: 1.0 (December 19, 2011), Original Code.
  Version: 1.1 (August 21, 2013), Arduino 1.0 Compatibility
*/ 

#ifndef LEDGraphShield_h
#define LEDGraphShield_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define R_MODULE 1
#define RY_MODULE 0

class LEDGraphShield
{
  public:
    LEDGraphShield(int module);
    void set_bar(int loc);
    void set_ybar(int loc);
    void set_bars(int loc, boolean value);
    void set_ybars(int loc, boolean value);
    void set_bars_cum(int loc);
    void update_bar();
    void update_bars();
    
  private:
    int _DTA;                      //shift register input
    int _RCK;                      //shift reguster output latch clock
    int _SCK;                      //shift register clock
    boolean _module;               //module selector
    boolean _bufferR[100];         //red graph buffer
    int _position;                 //position for single red bar display
    boolean _bufferY[10];          //yellow graph buffer
    boolean _first_shift[32];      //generic shift register output buffer
    int _pin_map[32];              //map of shift register ports to socket pin numbers
    boolean _out_shift[32];        //pin aligned shift register output buffer              
    
    void update();
    void pulse_data(boolean value);
};

#endif
