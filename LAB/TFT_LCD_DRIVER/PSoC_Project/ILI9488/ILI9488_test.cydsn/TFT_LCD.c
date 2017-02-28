/*
 * TFT_LCD.c
 *
 * Created: 28-02-2017 12:05:42
 *  Author: Group 11 (Laimonas, Jonathan)
 */ 

#include "TFT_LCD.h"
#include "TFT_LCD_cmd.h"
#include "TFT_LCD_delay.h"

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
 * sætter positionen på en bestemt pixel.
 * x_start = vandret start position
 * x_end = vandret slut position
 * y_start = lodret start
 * y_slut = lodret slut
**/
void TFT_setWindow(unsigned x_start, unsigned x_end, unsigned y_start, unsigned y_end)
{
  TFT_setColumnAddress(y_start,y_end);
  TFT_setPageAddress(x_start,x_end);
}

/* [] END OF FILE */

