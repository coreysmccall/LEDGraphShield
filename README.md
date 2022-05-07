# LEDGraphShield

The Long LED Graph Shield is useful for visualizing a high-resolution numerical value or any other data that can be described by a single row of 100 LEDs. The included Arduino software library with code examples makes it easy to get started with either the red or red/yellow bar graph module.

![Shield Image](/img/shield.jpg)
<center>The Long LED Graph Shield after assembly with the red (top) and red/yellow (bottom) modules. The center pin of the blue potentiometer is connected to analog input pin A0 for the example code.</center>

## Assembling the Shield
Assemble the shield by first soldering male headers to the bottom of the outside I/O pins and female headers to top of the inside I/O pins. It may be easiest to solder the male headers first while they are mounted into the I/O headers of an Arduino. Next, solder 220Ω resistors into the third and fourth rows of resistor marks, and 0.1µF capacitors into the capacitor marks. Next, solder the four 74HC595 shift registers into the IC marks. And finally, solder the bar graph module or a long female header into the 38-pin mark. The module should be set such that the end with the group of 3 pins is on the right, and the left most pin is in the left most mounting hole.

The Long LED Graph Shield is compatible with both the red (Siemens RBG-8820) and red/yellow (Siemens RBG-112) bar graph modules. To configure the shield for either module, follow the instructions printed on the face of the board. For the red module, wire resistors to the marks in the first row of resistor marks, short the resistor marks in the second row, and short the square jumper mark at the bottom of the board. For the red/yellow module, just wire resistors to the marks in the second row, and short the resistor marks in the first row. 

## Loading the Software Library
Copy the LongLedGraph folder to the libraries folder in your Arduino install directory. Once the library is installed, the examples can be run from the File->Examples->LongLedGraph menu within the Arduino IDE.

To use the library, include LongLedGraph.h, and instantiate a LongLedGraph object by calling LongLedGraph(module_code). For the red module, set module_code to “R_MODULE”, and for the red/yellow module, set module_code to “RY_MODULE.” The following table gives summary of the functions available to each LongLedGraph instance.

| Name 	      					  | Inputs	    													| Description  																|
| :-----------------------------  | :----------- 													| :-----------  															|
|set_bar(int loc)  			 	  |loc: location of bar to activate       							|Sets which single bar to display on red segments			   			 	|
|set_ybar(int loc) 			 	  |loc: location of bar to activate   							    |Sets which single bar to display on yellow segments			    		|
|set_bars(int loc, boolean value) |loc: location of bar to select, value: value to set selected bar |Sets values in output buffer for red segments			    				|
|set_ybars(int loc, boolean value)|loc: location of bar to select, value: value to set selected bar |Sets values in output buffer for yellow segments			    			|
|set_bars_cum(int loc)			  |loc: maximum value on bar       								 	|Sets all bars up to a certain value in the output buffer for red segments  |
|update_bar()					  |        													 	|Refreshes single bar display			    								|
|update_bars()					  |        													 	|Refreshes multibar display from buffer			    						|

Description of functions in the software library.

## Examples
### DisplayBar: Single Bar Display
To display a single bar, first run set_bar() with the corresponding bar location, and then update_bar() to update the display. When only a single bar is displayed, the display does not need to be constantly refreshed. 

The DisplayBar example displays the relative value read on the analog input pin A0 with a single bar segment.

### DisplayBars: Bar Graph Style Display
To display the output as a filled in bar instead of a single segment, set_bars_cum() and update_bars() must be used instead of set_bar() and update_bar(). These functions allow more than one bar to be set at a time, however they require that update_bars() be constantly run in the main loop in order to keep the display refreshed.

The DisplayBars example displays the relative value read on the analog input pin A0 with a filled in bar of segments. If the red/yellow module is being used, the most recent peak of the input signal within the last second is shown using the yellow segments. 

### DisplayAnyBars: Arbitrary Bar Display
To display an arbitrary pattern on the module, use set_bars() to either turn on or off a particular segment. Once the segments have been set, remember to run update_bars() to refresh the display.

The DisplayAnyBars example displays the relative value read on the analog input pin A0 as a filled in bar that extends from the center. Before each call to update_bars(), a 100-iteration loop is run to set the value of each segment in order to create the correct shape.
