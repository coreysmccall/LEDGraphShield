/*
  DisplayBars
 This example displays a row of LEDs according to 
 the value of analog pin 0. Notice that when multiple
 LEDs are lit, the display needs to be constantly
 refreshed. For the RY module, the peaks are also 
 shown in yellow.
 
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

//map each yellow bar to a position on the red bar graph
const int ymap[10]={ 
  10, 20, 30, 40, 50, 60, 70, 80, 90, 99};

//current peak
int max_val=0;

//timeout timer
long timer=0;

void setup(){
  ;
}

void loop()
{
  //scale input value to 100 segment display
  int value=map(analogRead(IN_PIN),0,1023,0,99);

  //refresh peak
  if(millis()-timer > 1000){
    max_val=0;
    timer=millis();
  }
  if(value>max_val)
    max_val=value;
  set_peak(max_val);


  //update display (run this constantly to refresh display)
  L.set_bars_cum(value);
  L.update_bars();
}

//This function sets the 
void set_peak(int peak){
  for (int i=0;i<10;i++)
    if(peak >= ymap[i])
      L.set_ybar(i);
  if(peak<ymap[0])
    L.set_ybar(-1);
}
