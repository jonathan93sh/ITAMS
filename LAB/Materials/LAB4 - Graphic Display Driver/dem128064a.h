/*----------------------------------------------------------------------
File name: "DEM128064A.h"

Description: Driver for Graphic Display LCD Module DEM128064A.

Author: Henning Hargaard
Date: 2.2.2014
-----------------------------------------------------------------------*/
#ifndef GRAPHICdefine
#define GRAPHICdefine

#define DATA_OUT     PORTD
#define DATA_IN      PIND
#define DATA_DDR     DDRD

#define CONTROL_PORT PORTA
#define CONTROL_DDR  DDRA

// Initialized the display module
void DisplayInit();
// Turns on the display module (both left and right halfes)
void DisplayOn();
// Turns off the display module (both left and right halfes)
void DisplayOff();
// Blanks the display (both left and right halfes)
void ClearScreen();
// Sets one pixel at (x,y)
// "x" is the horizontal coordinate (starting at the LCD left side)
// "y" is the vertical coordinate (starting at the LCD bottom side)
void SetPixel(unsigned char x, unsigned char y);
// Fills the (whole) display with a predefined bit pattern
// "picArray" is a pointer to the bit pattern array prestored in flash memory
void DisplayPic(const char *picArray);
// Draws a horizontal line at the display
// "StartX" and "StartY" is the leftmost start point for the line
// "Length" is the line length measured in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length);
#endif 
//----------------------------------------------------------------------