/*
  Display Driver for Graphic Display Module DEM128064A.
   
  Author: Henning Hargaard
  Date: 2.2.2014
*/  

#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "DEM128064A.h"

#define waitBusy_enable off

// Control port pin definitions:
#define CS2  7
#define CS1  6
#define RSTB 5
#define RW   2
#define E    1
#define RS   0
#define BUSY 7

#define LEFT  0
#define RIGHT 1

#define CONTROL 0
#define DATA    1

#define INPUT 0x00
#define OUTPUT 0xFF
// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

#define _NOP8 do{_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP()}while(0)
#define _NOP3 do{_NOP();_NOP();_NOP();}while(0)


void E_HIGH();
void E_LOW();
void waitBusy();

void E_HIGH()
{
	CONTROL_PORT |= (1<<E);
	_NOP8;
}

void E_LOW()
{
	CONTROL_PORT &= ~(1<<E);
	
	_NOP8;
}



void waitBusy()
{
	#if waitBusy_enable == ON


	DATA_DDR = INPUT;
	CONTROL_PORT = (0<<RS)|(1<<RW);
	
	uint8_t Busy;
	
	do 
	{
		E_LOW();
		E_HIGH();
		
		Busy = !!(DATA_IN>>BUSY);
		E_LOW();
		E_HIGH();
	} while (Busy);
	
	E_LOW();
	DATA_DDR = OUTPUT;
	#endif
}

void sendInstruction(unsigned char Chip, unsigned char data )
{
	waitBusy();
	
	CONTROL_PORT = (0<<RS)|(0<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	DATA_OUT = (data);
	E_HIGH();
	E_LOW();
}

void sendData(unsigned char Chip, unsigned char data )
{
	//waitBusy();
	CONTROL_PORT = (1<<RS)|(0<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	DATA_OUT = (data);
	
	E_HIGH();
	E_LOW();
}

// Writes a byte to the display
// "Chip" = LEFT or RIGHT
// "Data" = 8 bit data to be written
// "Type" = CONTROL" or "DATA"
void DisplayWrite(unsigned char Chip, unsigned char Data, unsigned char Type)
{
	waitBusy();
	CONTROL_PORT = (!!Type<<RS)|(0<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	DATA_OUT = (Data);
	E_HIGH();
	E_LOW();
	
}

// Reads a byte from the display
// "Chip" = LEFT or RIGHT
// "Type" = CONTROL" or "DATA"
unsigned char DisplayRead(unsigned char Chip, unsigned char Type)
{
	uint8_t Data;
	waitBusy();
	DATA_DDR = INPUT;
	CONTROL_PORT = (!!Type<<RS)|(1<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	_NOP3; // address look up
	E_HIGH();
	Data = DATA_IN;
	E_LOW();
	CONTROL_PORT = (!!Type<<RS)|(0<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	DATA_DDR = OUTPUT;
}

// Set the display Y address counter (left or right chip)
// "Chip" = LEFT or RIGHT
// "Y" = 0-63
void SetY(unsigned char Chip, unsigned char Y)
{
	uint8_t tmp = (0b111111 & Y) | (0<<7) | (1<<6);
	DisplayWrite(Chip, tmp, CONTROL);
}

// Set the display page number (left or right chip)
// "Chip" = LEFT or RIGHT
// "Page" = 0-7
void SetPage(unsigned char Chip, unsigned char Page)
{
	uint8_t tmp = (0b111 & Page) | (0b10111<<3);
	DisplayWrite(Chip, tmp, CONTROL);
}

// Sets the display start line (only used for display scroling)
// "Chip" = LEFT or RIGHT
// "StartLinePage = 0-63
void SetStartLine(unsigned char Chip, unsigned char StartLine)
{
	uint8_t tmp = (0b111111 & StartLine) | (1<<7) | (1<<6);
	DisplayWrite(Chip, tmp, CONTROL);
}

// Reads and returns the display status byte (left or right chip)
// "Chip" = LEFT or RIGHT
unsigned char Status(unsigned char Chip)
{
	return DisplayRead(Chip, CONTROL);
}


// Clears all pixels at one of the screens halfes (left or right)
// "Chip" = LEFT or RIGHT
void ClearHalfScreen(unsigned char Chip)
{
	for()
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
}

// Turns the display (both left and right side) ON
void DisplayOn()
{
}

// Turns the display (both left and right side) OFF
void DisplayOff()
{
}

// Clears all pixels at the whole screen (left and right)
void ClearScreen()
{
}

// Displays a graphical image (whole screen)
// The parameter is a pointer to the bit array defining the image
void DisplayPic(const char *picArray)
{
}

// Sets one pixel at x,y
// Notice: x = Horizontal (0-127), y = Vertical (0-63)
// This correspons to the "logical" x and y terms
// in contrast to the display internal definitions
void SetPixel(unsigned char x, unsigned char y)
{
}

// Draws one horizontal line
// "StartX, StartY" is the (logical) start position of the line
// "Length" is the line length in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length)
{
}
