/*
 * TFT_LCD_laimonas.c
 *
 * Created: 26-02-2017 14:44:20
 *  Author: Laimonas 
 */ 

#include "TFT_LCD.h"
#include "TFT_LCD_cmd.h"
#include "TFT_LCD_delay.h"
#include "avr/delay.h"
#include "avr/cpufunc.h"


#define INPUT 0x00
#define OUTPUT 0xFF
#define DATA_IN PINA

#define _NOP8 do{_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();}while(0)
#define _NOP3 do{_NOP();_NOP();_NOP();}while(0)


/**
 * renser alt hukommelse på skærm kontrolleren.
 * reset værdi er 255:255:255 rgb
**/
void TFT_clear()
{
	TFT_write_data(TFT_SW_RESET);
	_delay_ms(6); //wait MIN 5 ms
}


/**
 * Bruges til at styre de pins der bruges som kommando pins.
 * |7    -  |--4|--3|--2|--1|--0|
 * |--------|RST|CSX|DCX|RDX|WRX|
**/
void TFT_write_com(uint8_t com)
{
	DATA_PORT = com;
	DATA_DDR = OUTPUT;
	
	CONTROL_PORT |= (1<<RDX);
	CONTROL_PORT &= ~(1<<CSX);
	CONTROL_PORT &= ~(1<<DCX); //DCX 0 => command, DCX 1 = parameter/data
	
	CONTROL_PORT &= ~(1<<WRX);
	_NOP();
	CONTROL_PORT |= (1<<WRX);
	_NOP();
	
	CONTROL_PORT |= (1<<CSX)|(1<<DCX);

	DATA_DDR = INPUT;
}


/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/
uint8_t TFT_read_data(uint8_t data)
{
	/*
	RDX FM H duration MIN 90ns    
	RDX FM L duration MIN 355ns 
	RDX ID H duration MIN 90ns
	RDX ID L duration min 45ns
	RDX FM read min 450ns
	RDX ID read min 160ns
	*/
	
	uint8_t ReceivedData;
	
	DATA_DDR = INPUT;
	
	CONTROL_PORT &= ~(1<<CSX);
	CONTROL_PORT |= (1<<WRX)|(1<<DCX);
	
	CONTROL_PORT &= ~(1<<RDX); //t_rdlfm min 355ns, 6 cycles ved 16MHz = 375ns
	_NOP3;
	_NOP3;
	CONTROL_PORT |= (1<<RDX); //dummy read;
	_NOP();
	_NOP();
	
	CONTROL_PORT &= ~(1<<RDX); //prepare for actual read
	_NOP3;
	_NOP3;
	CONTROL_PORT = (1<<RDX);
	//maybe read here
	_NOP();
	_NOP();
	
	ReceivedData = DATA_IN; //DATA_IN
	_NOP();
	
	CONTROL_PORT |= (1<<CSX);
	
	return ReceivedData;
}


/**
 * sætter Column adresse.
**/
void TFT_setColumnAddress(unsigned addr)
{
	
}


/**
 * sætter page adresse.
**/
void TFT_setPageAddress(unsigned addr)
{
	
}


/**
 * sætter en enkel pixel.
**/
void setPixel(uint8_t red, uint8_t green, uint8_t blue)
{
	
}


/**
 * sætter positionen på en bestemt pixel.
 * x = vandret
 * y = lodret
**/
void TFT_setPos(unsigned x, unsigned y)
{

}
