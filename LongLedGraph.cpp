/*
  LongLedGraph - Library long LED bar graph matrix.
  Created by Corey McCall, November 9, 2011.
  Released into the public domain.
 
  
  Version: 1.0 (December 19, 2011), Original Code.
  Version: 1.1 (August 21, 2013), Arduino 1.0 Compatibility
*/


#include "LongLedGraph.h"

/*
  Constructor
 
  _module values:
   1 -> R _module
   0 -> RY _module
*/
LongLedGraph::LongLedGraph(int module)
{
  //set pins for input (_DTA), shift reg clock (_SCK) and output latch clock (_RCK)
  _DTA=2; 
  pinMode(_DTA, OUTPUT);
  _SCK=3; 
  pinMode(_SCK, OUTPUT);
  _RCK=4; 
  pinMode(_RCK, OUTPUT);
  
  //set global module select varable
  _module=module;
 
  //clear output buffers
  for (int i=0;i<100;i++)
    _bufferR[i]=0;
  for (int i=0;i<10;i++)
    _bufferY[i]=0;

  //maps socket number to shift register pins for each module according to 
  //reference sheet
  _pin_map[0]=_module?  9:31;
  _pin_map[1]=_module?  5:8;
  _pin_map[2]=_module? 25:27;
  _pin_map[3]=_module? 20:24;
  _pin_map[4]=_module?  1:5;
  _pin_map[5]=_module?  2:3;
  _pin_map[6]=_module? 29:9;
  _pin_map[7]=_module? 13:12;
  _pin_map[8]=_module? 16:0;
  _pin_map[9]=_module? 26:1;
  _pin_map[10]=_module? 0:4;
  _pin_map[11]=_module? 3:7;
  _pin_map[12]=_module? 7:11;
  _pin_map[13]=_module?11:13;
  _pin_map[14]=_module?15:15;
  _pin_map[15]=_module?18:19;
  _pin_map[16]=_module?21:21;
  _pin_map[17]=_module?24:23;
  _pin_map[18]=_module?27:26;
  _pin_map[19]=_module?30:28;
  _pin_map[20]=_module? 4:30;
  _pin_map[21]=_module? 4:2;
  _pin_map[22]=_module? 4:6;
  _pin_map[23]=_module? 4:10;
  _pin_map[24]=_module? 4:14;
  _pin_map[25]=_module? 4:17;
  _pin_map[26]=_module? 4:20;
  _pin_map[27]=_module? 4:22;
  _pin_map[28]=_module? 4:25;
  _pin_map[29]=_module? 4:29;
  _pin_map[30]=_module? 4:18;
  _pin_map[31]=_module? 4:16;
}  

/*
  sets the red graph buffer to show a single bar at location (loc)
*/
void LongLedGraph::set_bar(int loc)
{
  _position=loc;
}

/*
  sets the yellow graph buffer to show a single bar at location (loc)
*/
void LongLedGraph::set_ybar(int loc){
  for (int i=0;i<10;i++)
    _bufferY[i]=(loc==i);
}

/*
  sets a single bar in the red graph buffer according to the (loc,value) pair
*/
void LongLedGraph::set_bars(int loc, boolean value){
  _bufferR[loc]=value;
}

/*
  sets a single bar in the yellow graph buffer according to the (loc,value) pair
*/
void LongLedGraph::set_ybars(int loc, boolean value){
  _bufferY[loc]=value;
}

/*
  sets the red graph buffer to show a single bar at location (loc)
*/
void LongLedGraph::set_bars_cum(int loc){
  for(int i=0;i<100;i++)
    _bufferR[i]=(i<=loc); 
}

/*
  Updates the display to show a single bar value
*/
void LongLedGraph::update_bar() {
  
  //fill first buffer bits with red anode
  for (int i=0;i<(_module?10:8);i++)
    _first_shift[i]=(i==(_position+(_module?0:4))%(_module?10:8));
  
  //fill second buffer bits with red cathode
  for (int i=0;i<(_module?10:13);i++)
    _first_shift[(_module?10:8)+i]=(i!=(_position+(_module?0:4))/(_module?10:8));

  //fill next buffer bits with yellow anode
  for (int i=0;i<(_module?0:10);i++)
    _first_shift[21+i]=_bufferY[i];

  //fill last buffer bit with yellow cathode
  if(!_module)
    _first_shift[31]=LOW;

  //refresh display from buffer
  update();
}

/*
  Updates the display to show multiple bar values
  This function must be constantly run to refresh the display.
*/
void LongLedGraph::update_bars(){

  //for each common cathode set
  for (int i=0;i<(_module?10:13);i++){

    //fill first buffer bits with red anode
    for (int j=0;j<(_module?10:8);j++)
      _first_shift[j]=_bufferR[i*(_module?10:8)+j-(_module?0:4)];

    //fill second buffer bits with red cathode
    for (int j=0;j<(_module?10:13);j++)
      _first_shift[(_module?10:8)+j]= (j!=i);

    //fill next buffer bits with yellow anode
    for (int j=0;j<(_module?0:10);j++)
      _first_shift[21+j]=_bufferY[j];

    //fill last buffer bit with yellow cathode
    if(!_module)
      _first_shift[31]=LOW;
    update();
  }
}

/*
  writes data to shift register chain and refreshes display
*/
void LongLedGraph::update(){
  //clear register output buffer
  for (int i=0;i<32;i++)
    _out_shift[i]=false;
    
  //fill register output buffer
  for (int i=0;i<32;i++)
    _out_shift[_pin_map[i]]=_first_shift[i];
  
  //pulse register output buffer into shift registers
  for (int i=31;i>=0;i--)
    pulse_data(_out_shift[i]);

  //refresh display by pulsing output latch.
  digitalWrite(_RCK,HIGH);
  digitalWrite(_RCK,LOW); 
}

/*
  inserts a single value into the shift register chain
  */
void LongLedGraph::pulse_data(boolean value){
  digitalWrite(_DTA,value);
  digitalWrite(_SCK,HIGH);
  digitalWrite(_SCK,LOW); 
}


