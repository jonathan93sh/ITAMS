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
	execute_cmd(TFT_SW_RESET);
    CyDelay(6);//wait MIN 5 ms
}


/**
 * Bruges til at styre de pins der bruges som kommando pins.
 * |7    -  |--4|--3|--2|--1|--0|
 * |--------|RST|CSX|DCX|RDX|WRX|
**/
void execute_cmd(uint8 cmd)
{
    DDR_DATA = 0xFF; //make to output
    PORT_DATA = cmd;
    
    LCD_RS_Write(0);//RS 0 => command, DCX 1 = parameter/data

    PORT_WR = 0; //command sent
    _NOP();

    PORT_WR = 1;

	LCD_RS_Write(1);
	
    DDR_DATA = 0x00; //make input again
}

void send_data(uint8 data)
{
    PORT_DATA = data;

    PORT_WR = 0; //data sent
    _NOP();
    
    PORT_WR = 1; 
}


/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/
void receive_data(uint8 *dataPtr) //Remember to do a dummy read first!
{
    //Read_enable_Write(1);
    PORT_DATA = 0x00; 

    LCD_RD_Write(0);
	TFT_DELAY_trcsfm;//trdlfm<=>trcsfm, min 355ns
    
	*dataPtr = PIN_DATA_Read();
	
    LCD_RD_Write(1);
	TFT_DELAY_trdhfm;
}


/**
 * sætter positionen på en bestemt pixel.
 * x_start = lodret start position
 * x_end = lodret slut position
 * y_start = vandret start
 * y_slut = vandret slut
**/
void TFT_setWindow(unsigned x_start, unsigned x_end, unsigned y_start, unsigned y_end)
{
  TFT_setColumnAddress(x_start,x_end);
  TFT_setPageAddress(y_start,y_end);
}