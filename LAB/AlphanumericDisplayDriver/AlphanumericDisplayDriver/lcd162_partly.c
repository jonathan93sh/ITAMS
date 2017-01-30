/*-----------------------------------------------------------------------
  File name: "lcd162.c"

  Description: Driver for the PowerTip PC1602-F alphanumeric display.
  Display controller = HD44780U (LCD-II).
  
  Max. Mega32 CPU clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connection : PORTx (4 bit mode) :
  [LCD]             [Portx]
  RS (pin4)  ------  bit 0
  RW (pin 5) ------  bit 1
  E  (pin 6) ------  bit 2
  DB4 (pin 11) ---   bit 4
  DB5 (pin 12) ---   bit 5
  DB6 (pin 13) ---   bit 6
  DB7 (pin 14) ---   bit 7

  Henning Hargaard, January 25, 2017
-----------------------------------------------------------------------*/



#include <avr/io.h>
#define F_CPU 3686400
#include <avr/delay.h>
// Enabling us to use macro _NOP() to insert the NOP instruction
#include <avr/cpufunc.h>
#include "lcd162.h"

// Library function itoa() is needed
#include <stdlib.h>

// Defining the used port pin numbers
// (the used port is defined in "lcd.h")
#define RS   0
#define RW   1
#define E    2
#define BUSY 7
#define LSB 3
//*********************** PRIVATE (static) operations *********************
static void E_High()
{
  // Set the E pin high
  PORT_lcd |= 1<<E;
  // Min 230 ns E-pulse-width : PWEH
  _NOP();
  _NOP();
  _NOP();
  _NOP();
}

static void E_Low()
{
  // Set the E pin low
  PORT_lcd &= ~(1<<E);
  // Enable cycle time : Min 500 ns
  _NOP();
  _NOP();
}

static void waitBusy()
{
unsigned int counter = 0;
unsigned char BusyStatus;
                                                            
  // DB7-DB4 = input
  DDR_lcd &= 0b00001111;
  // RW = 1, RS = 0
  PORT_lcd |= 1<<RW;
  PORT_lcd &= ~(1<<RS);
  do
  { 
    // Set pin E high (tAS > 40 ns gained via the call of E_High() )
    // - and wait tDDR (min. 160 ns)
    E_High();
    // Read BUSY flag (DB7)  
    BusyStatus = PIN_lcd & 1<<BUSY;
    // Min 230 ns E-pulse-width : (PWEH > 230 ns is gained)
    E_Low();
    // Dummy "reading" AC3-AC0		              
    E_High();
    E_Low();
    // "Counter" used for implementing timeout:
    // If the Busy flag is not reset within (appr.) 100 ms, the loop is broken
    counter++;
  } while( BusyStatus && counter );  
  // DB7-DB4 = output
  DDR_lcd |= 0b11110000;
}  

static void sendInstruction( unsigned char data )
{      
  // Wait for display controller ready
  waitBusy();
  // Write high nibble ::
  // RW = 0, RS = 0, E = 0, DB7-DB4 = Data high nibble
  PORT_lcd = (data & 0b11110000);
  // Set pin E high (tAS > 40 ns gained via calling E_High() )
  E_High();
  // Set pin E low (PWEH > 230 ns is gained)
  E_Low();

  // Write low nibble ::
  // RS = 0, RW = 0, E = 0, DB7-DB4 = Data low nibble
  PORT_lcd = (data & 0x0F)<<4;
  // Set pin E high (tAS > 40 ns is gained via calling E_High() )
  E_High();
  // Set pin E low (PWEH > 230 ns is gained)
  E_Low();
}

static void sendData( unsigned char data )
{   
	waitBusy();
	
	PORT_lcd = (data & 0b11110000) | (1 << RS);
	
	E_High();
	
	E_Low();
	
	PORT_lcd = ((data & 0b01111)<<4) | (1<<RS);
	
	E_High();
	
	E_Low();
	   
  // To be implemented
}

//*********************** PUBLIC operations *****************************

// Initializes the display, blanks it and sets "current display position"
// at the upper line, leftmost character (cursor invisible)
void LCDInit()
{
  // Initializing the used port
  DDR_lcd = 0xFF;  // bits 0-7 output
  PORT_lcd = 0x00; // bits 0-7 low 
	 
  // Wait 50 ms (min.15 ms demanded according to the data sheet)
  _delay_ms(50);
  // Function set (still 8 bit interface)
  PORT_lcd = 0b00110000;
  E_High();
  E_Low();

  // Wait 10 ms (min.4,1 ms demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  PORT_lcd = 0b00110000;
  E_High();
  E_Low();

  // Wait 10 ms (min.100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  PORT_lcd = 0b00110000;
  E_High();
  E_Low();

  // Wait 10 ms (min.100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (now selecting 4 bit interface !)
  // - and polling the busy flag will now be possible
  PORT_lcd = 0b00100000;
  E_High();
  E_Low();

  // Function Set : 4 bit interface, 2 line display, 5x8 dots
  sendInstruction( 0b00101000 );
  // Display, cursor and blinking OFF
  sendInstruction( 0b00001000 );
  // Clear display and set DDRAM adr = 0	
  sendInstruction( 0b00000001 );
  // By display writes : Increment cursor / no shift
  sendInstruction( 0b00000110 );
  // Display ON, cursor and blinking OFF
  sendInstruction( 0b00001100 );
}

// Blanks the display and sets "current display position" to
// the upper line, leftmost character
void LCDClear()
{
	sendInstruction(0b1);
}

// Sets DDRAM address to character position x and line number y
void LCDGotoXY( unsigned char x, unsigned char y )
{
	
	uint8_t tmp = ((0b1111111) & ((x <= 0x27 ? x : 0x27) + (y >= 1 ? (0x40) : (0x0)))) | (1<<7);
	
	sendInstruction(tmp);
	
}

// Display "ch" at "current display position"
void LCDDispChar( char ch )
{
	uint8_t tmp = (0b11111111) & ((uint8_t)ch);
	sendData(tmp);
}

// Displays the string "str" starting at "current display position"
void LCDDispString( char *str )
{
	//sendInstruction(0b110);
	
	while(*str != NULL)
	{
		LCDDispChar(*str);
		
		str++;
	}
	//sendInstruction()
}

// Displays the value of integer "i" at "current display position"
void LCDDispInteger( int i )
{
	
	char string[16];
	string[16-1] = 0;
	
	itoa(i, string, 10);
	
	LCDDispString(string);
}

// Loads one of the 8 user definable characters (UDC) with a dot-pattern,
// pre-defined in an 8 byte const array
/**
 * \brief 
 * 
 * \param UDCNo
 * \param UDCTab
 * 
 * \return void
 */
void LCDLoadUDC( unsigned char UDCNo, const unsigned char *UDCTab )
{
	uint8_t No = (0b0111) & UDCNo;
	uint8_t tmp;

	
	for(uint8_t i = 0; i < 8; i++)
	{
		tmp = (No<<3) | (i);
		sendInstruction(tmp | (1<<6));
		
		sendData(UDCTab[i]);
		
	}
}

// Selects, if the cursor has to be visible, and if the character at
// the cursor position has to blink.
// "cursor" not 0 => visible cursor.
// "blink" not 0 => the character at the cursor position blinks.
void LCDOnOffControl( unsigned char cursor, unsigned char blink )
{
	uint8_t tmp = (0b1100) | ((!!cursor)<<1) | ((!!blink)<<0);
	sendInstruction(tmp);
}

// Moves the cursor to the left
void LCDCursorLeft()
{
	sendInstruction(0b10000);
}

// Moves the cursor to the right
void LCDCursorRight()
{
	sendInstruction(0b10100);
}

// Moves the display text one position to the left
void LCDShiftLeft()
{
	sendInstruction(0b11000);
}

// Moves the display text one position to the right
void LCDShiftRight()
{
	sendInstruction(0b11100);
}

//----------------------------------------------------------------------
