/*
  Display Driver for Graphic Display Module DEM128064A.
   
  Author: Henning Hargaard
  Date: 2.2.2014
*/  

#include <avr/io.h> 
#include <avr/cpufunc.h>
//#define F_CPU 16000000
#define F_CPU 3686400
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

#define _NOP8 do{_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();}while(0)
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
/*

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
	*/
	#endif
}



// Writes a byte to the display
// "Chip" = LEFT or RIGHT
// "Data" = 8 bit data to be written
// "Type" = CONTROL" or "DATA"
void DisplayWrite(unsigned char Chip, unsigned char Data, unsigned char Type)
{
	//_delay_us(500);
	//waitBusy();
	//PORTC = ~Data;
	DATA_OUT = (Data);
	DATA_DDR = OUTPUT;
	CONTROL_PORT |= (Type<<RS)|(1<<(Chip == 1 ? CS1 : CS2));
	CONTROL_PORT &= ~(((!Type)<<RS)|(1<<RW));
	//PORTC = ~CONTROL_PORT;
	
	_NOP3; 
	CONTROL_PORT |= (1<<E);
	_NOP8;
	
	CONTROL_PORT &= ~(1<<E);
	_NOP();
	CONTROL_PORT &= ~((1<<CS1)|(1<<CS2));
	CONTROL_PORT |= (1<<RW);
	DATA_DDR = INPUT;
}

// Reads a byte from the display
// "Chip" = LEFT or RIGHT
// "Type" = CONTROL" or "DATA"
unsigned char DisplayRead(unsigned char Chip, unsigned char Type)
{
	//_delay_us(1500);
	uint8_t Data;
	waitBusy();
	DATA_DDR = INPUT;
	
	CONTROL_PORT |= (Type<<RS)|(1<<RW)|(1<<(Chip == 1 ? CS1 : CS2));
	CONTROL_PORT &= ~((!Type)<<RS);
	
	_NOP3;
	CONTROL_PORT |= (1<<E);
	_NOP8;
	Data = DATA_IN;
	_NOP();
	CONTROL_PORT &= ~((1<<CS1)|(1<<CS2));
	CONTROL_PORT &= ~(1<<E);
	
	return Data;
}

// Set the display Y address counter (left or right chip)
// "Chip" = LEFT or RIGHT
// "Y" = 0-63
void SetY(unsigned char Chip, unsigned char Y)
{
	uint8_t tmp = (0b111111 & Y) | (1<<6);
	PORTC = ~(tmp);
	DisplayWrite(Chip, tmp, CONTROL);
	//_delay_us(500);
	DisplayRead(Chip,CONTROL);
	//_delay_us(500);
}

// Set the display page number (left or right chip)
// "Chip" = LEFT or RIGHT
// "Page" = 0-7
void SetPage(unsigned char Chip, unsigned char Page)
{
	uint8_t tmp = (0b111 & Page) | (0b10111000);
	DisplayWrite(Chip, tmp, CONTROL);
	//_delay_us(500);
	DisplayRead(Chip,CONTROL);
	//_delay_us(500);
}

// Sets the display start line (only used for display scroling)
// "Chip" = LEFT or RIGHT
// "StartLinePage = 0-63
void SetStartLine(unsigned char Chip, unsigned char StartLine)
{
	uint8_t tmp = (0b111111 & StartLine) | (1<<7) | (1<<6);
	DisplayWrite(Chip, tmp, CONTROL);
	DisplayRead(Chip,CONTROL);
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
	SetStartLine(Chip,0);
	
	for(uint8_t page = 0; page < 8; page++)
	{
		SetPage(Chip, page);
		SetY(Chip,0);
		for (uint8_t y = 0; y < 64; y++)
		{
			DisplayWrite(Chip,0x00,DATA);	
		}
		DisplayRead(Chip, CONTROL);
	}
	
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
	//E_LOW();
	//DATA_OUT = 0x00;
	CONTROL_PORT = 0x00;
	DATA_DDR = INPUT;
	CONTROL_DDR = OUTPUT;
	_delay_ms(1);
	CONTROL_PORT |= (1<<RSTB);//|(1<<CS1)|(1<<CS2);
	
	uint8_t status_test = 0;
	
	while(1)
	{
		status_test = Status(1) | Status(2);
		PORTC = ~status_test;
		if(((status_test>>4)&0b1) == 0)
			break;
		
		_NOP8;
	}
	
	PORTC = ~(status_test | 1);
	
	SetStartLine(1,0);
	SetStartLine(2,0);
	
/*	
	
	while(1);
	_delay_ms(200);
	PORTC = ~(uint8_t)Status(1);
	while(1);
	CONTROL_PORT = (1<<RSTB);//|(1<<CS1)|(1<<CS2);
	//_delay_ms(1000);
	//CONTROL_PORT = 0x00;//(0<<CS1)|(0<<CS2);
	_delay_ms(1000);
	PORTC = ~(uint8_t)Status(1);
	while(1);
	*/
}

// Turns the display (both left and right side) ON
void DisplayOn()
{
	uint8_t tmp = (0b111111); 
	DisplayWrite(1, tmp,CONTROL);
	DisplayWrite(2, tmp,CONTROL);
	PORTC = ~Status(1);
}

// Turns the display (both left and right side) OFF
void DisplayOff()
{
	uint8_t tmp = (0b111110);
	DisplayWrite(1, tmp,CONTROL);
	DisplayWrite(2, tmp,CONTROL);
	PORTC = ~(Status(1)|Status(2));
}

// Clears all pixels at the whole screen (left and right)
void ClearScreen()
{
	ClearHalfScreen(1);
	ClearHalfScreen(2);
}

// Displays a graphical image (whole screen)
// The parameter is a pointer to the bit array defining the image
void DisplayPic(const char *picArray)
{
	for (uint8_t chip = 1; chip < 2+1; chip++)
	{
		SetStartLine(chip,0);
		
		for(uint8_t page = 0; page < 8; page++)
		{
			SetPage(chip, page);
			SetY(chip,0);
			for (uint8_t y = 0; y < 64; y++)
			{
				DisplayWrite(chip, picArray[page*128 + y + (chip == 1 ? 0 : 64)], DATA);
			}
			DisplayRead(chip, CONTROL);
		}
	}
	//DisplayRead(chip, CONTROL);
}

// Sets one pixel at x,y
// Notice: x = Horizontal (0-127), y = Vertical (0-63)
// This correspons to the "logical" x and y terms
// in contrast to the display internal definitions
void SetPixel(unsigned char x, unsigned char y)
{
	//SetStartLine(chip,0);
	uint8_t chip = (x < 64 ? 1 : 2);
	SetPage(chip,(y>>3));
	SetY(chip,x);
	
	DisplayRead(chip,DATA);
	uint8_t tmp = DisplayRead(chip,DATA);
	DisplayRead(chip, CONTROL);
	
	
	SetPage(chip,(y>>3));
	SetY(chip,x);
	
	DisplayWrite(chip,tmp|(1u<<(0b111&y)),DATA);
	DisplayRead(chip, CONTROL);
}

// Draws one horizontal line
// "StartX, StartY" is the (logical) start position of the line
// "Length" is the line length in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length)
{
	for (uint8_t i = 0; i < Length; i++)
	{
		SetPixel(StartX+i,StartY);
	}
}
