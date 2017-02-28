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
    size_t i;
    LCD_CS_Write(0);
	execute_cmd(cmd);
	DDR_DATA = 0xFF;
	for (i = 0; i < datasize; i++)
	{
		send_data(data[i]);
	}
    DDR_DATA = 0x00;
    LCD_CS_Write(1);
}
/**
 * Bruges til at aflæse fra skærmen eventuelt status beskeder.
 * return er længden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8 cmd, uint8 *dataOut, size_t bufSize)
{
    size_t i;
    LCD_CS_Write(0);
	execute_cmd(cmd);

	uint8 dummy;
	receive_data(&dummy);
	for (i = 0; i < bufSize; i++)
	{
		receive_data(dataOut + i);
	}
    LCD_CS_Write(1);
	return bufSize; //todo fix
}


void TFT_setColumnAddress(uint16 start, uint16 end)
{
    uint8 data[4];
    
    data[0] = (uint8)(start>>8);
    data[1] = (uint8)(start);
    data[2] = (uint8)(end>>8);
    data[3] = (uint8)(end);
    
    TFT_write_data(TFT_COLUMN_ADDRESS_SET, data, 4);
    
}

void TFT_setPageAddress(uint16 start, uint16 end)
{
    uint8 data[4];
    
    data[0] = (uint8)(start>>8);
    data[1] = (uint8)(start);
    data[2] = (uint8)((uint16)(end)>>8);
    data[3] = (uint8)(end);
    
    TFT_write_data(TFT_PAGE_ADDRESS_SET, data, 4); 
}

void TFT_test()
{
    unsigned char R = 0, G = 2, B = 1;	   
    uint8 tmp;
    unsigned long i;
    while(1)
    {
        TFT_setColumnAddress(0,320u-(1u));
        TFT_setPageAddress(0,((uint16)480u)-(1u));
        //TFT_write_data(TFT_ALL_PIXEL_OFF, NULL,0);
        LCD_CS_Write(0);
        execute_cmd(TFT_MEMORY_WRITE);
        
        
        DDR_DATA = 0xFF;
    	for (i=0; i<153600lu*1; i++)	
        {
            
            send_data((R<<3)|(G>>3));
            send_data((G<<5)|(B));

        }
        DDR_DATA = 0x00;
        LCD_CS_Write(1);
        //TFT_write_data(TFT_ALL_PIXEL_ON, NULL,0);
        
    	R = (R+7)%32;
    	G = (R+9)%64;
    	B = (R+13)%32;
    }
    
    
}

void TFT_init()
{
    uint8 status[5] = {0};
    unsigned i;
    uint8 testData[300] = {0};
    
    
    
    for(i = 0; i < 300; i++)
    {
         testData[i] = (uint8)i;  
    }
    
    DDR_DATA_Write(0x00);
    LCD_RST_Write(1);
    LCD_CS_Write(1);
    LCD_RS_Write(1);
    LCD_WR_Write(1);
    LCD_RD_Write(1);
    CyDelay(500);
    CyDelayUs(10);
    LCD_RST_Write(0);
    CyDelay(500);
    LCD_RST_Write(1);
    CyDelay(500);
    TFT_write_data(TFT_SLEEP_OUT, NULL, 0);
    
    TFT_write_data(TFT_NORMAL_DISPLAY_MODE_ON, NULL, 0);
    
    TFT_write_data(TFT_DISPLAY_ON, NULL, 0);
    status[0] = 0b00001000;
    TFT_write_data(TFT_MEMORY_ACCESS_CONTROL, status, 0);
    status[0] = 0b101;
    TFT_write_data(TFT_INTERFACE_PIXEL_FORMAT, status, 1);
    
    
    /*
	//TFT_write_data(TFT_PARRTIAL_MODE_ON, NULL, 0);
	uint8 tmp = (0b110<<TFT_DPI)|(0b110<<TFT_DBI); // RGB = 18bit, MCU = 18bit
	//TFT_write_data(TFT_INTERFACE_PIXEL_FORMAT, &tmp, 1);
	
    
    //TFT_read_data(TFT_READ_PIXEL_FORMAT, status, 1);
    //TFT_write_data(TFT_ALL_PIXEL_ON, NULL, 0);
    if(status[0] != tmp&0b101)
    {
        while(1);   
    }
    
    
    TFT_read_data(TFT_DISPLAY_STATUS, status,5);
    
    TFT_write_data(TFT_MEMORY_WRITE, testData, 300);
    
    TFT_write_data(TFT_DISPLAY_ON, NULL, 0);
    while(1);
    for(i = 0; i < 512; i++)
    {
        TFT_write_data(TFT_MEMORY_WRITE_CONTINUE, testData, 300);    
    }
    
    while(1);
*/
}