/*
  DisplayAnyBars
 This example displays the value of analog pin 0 as 
 a row of LEDs that extend in both directions from
 the center of the display. Using the same strategy,
 arbitrary segments of the display can be controlled
 individually. Notice that when multiple LEDs are lit,
 the display needs to be constantly refreshed.
 
 Created by Corey McCall, November 9, 2011.
 Released into the public domain.
 
 Updated: December 19, 2011.
 Version: 1.0
 */ 

#include <LEDGraphShield.h>

//use RY_MODULE for red/yellow module
//use R_MODULE for red module
LEDGraphShield L = LEDGraphShield(RY_MODULE);
const int IN_PIN = A0;

void setup(){
  ; 
}

void loop()
{
  //scale input value to half of 100 segment display
  int value=map(analogRead(IN_PIN),0,1023,0,49);

  //set which segments to display
  for(int i=0;i<100;i++)
    //display cumulative value from the center
    L.set_bars(i,i>=(50-value)&&i<=(50+value));

  //update display (run this constantly to refresh display)
  L.update_bars();
}
