/*
 * TFT_LCD.c
 *
 * Created: 19-02-2017 20:22:43
 *  Author: jonathan
 */ 
#include "TFT_LCD.h"
#include "TFT_LCD_cmd.h"
#include "TFT_LCD_delay.h"


/**
 * Tilskrive til skærmen, ved først at sende kommando og eventuelt data efterfølgende.
 * datasize = er længden af data.
**/
void TFT_write_data(uint8 cmd, uint8 *data, size_t datasize)
{
	execute_cmd(cmd);
	
	for (size_t i = 0; i < datasize; i++)
	{
		send_data(data[i]);
	}
}
/**
 * Bruges til at aflæse fra skærmen eventuelt status beskeder.
 * return er længden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8 cmd, uint8 *dataOut, size_t bufSize)
{

	execute_cmd(cmd);

	uint8 dummy;
	receive_data(&dummy);
	for (size_t i = 0; i < bufSize; i++)
	{
		receive_data(dataOut + i);
	}
	return bufSize; //todo fix
}

void TFT_init()
{
    uint8 status = 0;
    
    DDR_DATA_Write(0x00);
    LCD_RST_Write(1);
    LCD_CS_Write(1);
    LCD_RS_Write(1);
    LCD_WR_Write(1);
    LCD_RS_Write(1);
    CyDelay(500);
    LCD_CS_Write(0);
    CyDelayUs(10);
    LCD_RST_Write(0);
    CyDelay(500);
    LCD_RST_Write(1);
    CyDelay(500);
    LCD_CS_Write(1);

	
	uint8 tmp = (0b110<<TFT_DPI)|(0b110<<TFT_DBI); // RGB = 18bit, MCU = 18bit
	TFT_write_data(TFT_INTERFACE_PIXEL_FORMAT, &tmp, 1);
	
    TFT_read_data(TFT_READ_PIXEL_FORMAT, &status,1);
    
    if(tmp != status)
    {
        while(1);
    }

    while(1);
	
	
}