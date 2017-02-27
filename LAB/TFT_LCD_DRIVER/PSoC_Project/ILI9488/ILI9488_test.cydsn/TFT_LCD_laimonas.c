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
    DDR_DATA_Write(0xFF); //make to output
    PORT_DATA_Write(cmd);	
    
    LCD_CS_Write(0);
    //LCD_RD_Write(1);
    //CyDelayUs(1);
    LCD_RS_Write(0);//RS 0 => command, DCX 1 = parameter/data
	TFT_DELAY_tcs;
	//CyDelayUs(1);
    LCD_WR_Write(0);//command sent
	TFT_DELAY_wcl;
    //CyDelayUs(1);
    LCD_WR_Write(1);
	TFT_DELAY_wch;
    //CyDelayUs(1);
	LCD_RS_Write(1);
    //CyDelayUs(1);
    LCD_CS_Write(1);
    
	TFT_DELAY_tcs;
	
    DDR_DATA_Write(0x00); //make input again
}

void send_data(uint8 data)
{
    DDR_DATA_Write(0xFF); //make to output
    PORT_DATA_Write(data);	
    
    LCD_CS_Write(0);
    //LCD_RD_Write(1);
    //LCD_RS_Write(1);//RS 0 => command, DCX 1 => data
	TFT_DELAY_tcs;
	//CyDelayUs(1);
    LCD_WR_Write(0);//command sent
	TFT_DELAY_wcl;
    //CyDelayUs(1);
    LCD_WR_Write(1);
	TFT_DELAY_wch;
	//CyDelayUs(1);
    LCD_CS_Write(1);
	TFT_DELAY_tcs;
	
    DDR_DATA_Write(0x00); //make input again
}


/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/
void receive_data(uint8 *dataPtr) //Remember to do a dummy read first!
{
    //Read_enable_Write(1);
    
    PORT_DATA_Write(0x00);

    LCD_CS_Write(0);
    //LCD_WR_Write(1);
    //LCD_RS_Write(1);
	TFT_DELAY_tcs;
	//CyDelayUs(1);
    LCD_RD_Write(0); //t_rdlfm<=>trcsfm, min 355ns
	TFT_DELAY_trcsfm;
	//CyDelayUs(1);
	*dataPtr = PIN_DATA_Read();
	
    LCD_RD_Write(1);
	TFT_DELAY_trdhfm;
    //CyDelayUs(1);
    LCD_CS_Write(1);
	TFT_DELAY_tcsf;
}


/**
 * sætter Column adresse.
**/
/*void TFT_setColumnAddress(unsigned addr)
{
	
}*/


/**
 * sætter page adresse.
**/
/*void TFT_setPageAddress(unsigned addr)
{
	
}*/


/**
 * sætter en enkel pixel.
**/
void setPixel(uint8 red, uint8 green, uint8 blue)
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
