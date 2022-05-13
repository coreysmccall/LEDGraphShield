/*
  DisplayBar
 This example displays the value of analog pin 0
 on the long LED bar graph using a single segment
 at a time. Notice that with a single segment, the
 display does not need to be constantly refreshed.
 
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
  //scale input value to 100 segment display
  int value=map(analogRead(IN_PIN),0,1023,0,99);
  L.set_bar(value);

  //update display
  L.update_bar();
  
  
  //other code can be run here without refreshing the display.
}
