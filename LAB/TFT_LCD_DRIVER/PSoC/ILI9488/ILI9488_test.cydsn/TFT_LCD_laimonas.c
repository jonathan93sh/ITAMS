/*
 * TFT_LCD_laimonas.c
 *
 * Created: 26-02-2017 14:44:20
 *  Author: Laimonas 
 */ 

#include "TFT_LCD.h"
#include "TFT_LCD_cmd.h"
#include "TFT_LCD_delay.h"

/**
 * renser alt hukommelse på skærm kontrolleren.
 * reset værdi er 255:255:255 rgb
**/
void TFT_clear()
{
	TFT_write_com(TFT_SW_RESET);
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
	TFT_DELAY_tcs;
	
	CONTROL_PORT &= ~(1<<WRX); //command sent
	TFT_DELAY_wcl;
	CONTROL_PORT |= (1<<WRX);
	TFT_DELAY_wch;
	
	CONTROL_PORT |= (1<<CSX)|(1<<DCX);
	TFT_DELAY_tcs;
	
	DATA_DDR = INPUT;
}


/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/
void TFT_read_data(uint8_t *dataPtr) //Remember to do a dummy read first!
{
	DATA_DDR = INPUT;
	
	CONTROL_PORT &= ~(1<<CSX);
	CONTROL_PORT |= (1<<WRX)|(1<<DCX);
	TFT_DELAY_tcs;
	
	CONTROL_PORT &= ~(1<<RDX); //t_rdlfm<=>trcsfm, min 355ns
	TFT_DELAY_trcsfm;
	
	*dataPtr = DATA_PIN;
	
	CONTROL_PORT = (1<<RDX);
	TFT_DELAY_trdhfm;
	CONTROL_PORT |= (1<<CSX);
	TFT_DELAY_tcsf;
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
