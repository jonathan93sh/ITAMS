/*
 * TFT_LCD.c
 *
 * Created: 19-02-2017 20:22:43
 *  Author: jonathan
 */ 
#include "TFT_LCD.h"
#include "TFT_LCD_cmd.h"
#include "TFT_LCD_delay.h"

void execute_cmd(uint8_t cmd)
{
	DATA_PORT = cmd;
	//TFT_write_data(cmd);
	//TFT_write_com(0b0011);
	CONTROL_PORT = 0b10011;
	TFT_DELAY_tcsf;
	//TFT_write_com(0b0010);
	CONTROL_PORT = 0b10010;
	TFT_DELAY_tcs;
	//TFT_write_com(0b0011);
	CONTROL_PORT = 0b10011;
	TFT_DELAY_wch;
	
}

void send_data(uint8_t data)
{
	//TFT_write_data(data);
	DATA_PORT = data;
	//TFT_write_com(0b0010);
	CONTROL_PORT = 0b10010;
	TFT_DELAY_wcl;
	//TFT_write_com(0b0011);
	CONTROL_PORT = 0b10011;
	TFT_DELAY_wch;
}

void receive_data(uint8_t *dataPtr)
{
	
	//TFT_write_com(0b0001);
	CONTROL_PORT = 0b10001;
	TFT_DELAY_trcsfm;
	*dataPtr = DATA_PIN;
	//TFT_write_com(0b0011);
	CONTROL_PORT = 0b10011;
	TFT_DELAY_trdhfm;
	TFT_DELAY_tcsf;
}

/**
 * Tilskrive til skærmen, ved først at sende kommando og eventuelt data efterfølgende.
 * datasize = er længden af data.
**/
void TFT_write_data(uint8_t cmd, uint8_t *data, size_t datasize)
{
	CONTROL_PORT = 0b11011;

	execute_cmd(cmd);
	
	for (size_t i = 0; i < datasize; i++)
	{
		send_data(data[i]);
	}
	CONTROL_PORT = 0b11011;
}
/**
 * Bruges til at aflæse fra skærmen eventuelt status beskeder.
 * return er længden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8_t cmd, uint8_t *dataOut, size_t bufSize)
{
	CONTROL_PORT = 0b11011;
	execute_cmd(cmd);
	DATA_DDR = INPUT;
	DATA_PORT = 0x00;
	uint8_t dummy;
	receive_data(&dummy);
	for (size_t i = 0; i < bufSize; i++)
	{
		receive_data(dataOut + i);
	}
	DATA_DDR = OUTPUT;
	CONTROL_PORT = 0b11011;
	return bufSize; //todo fix
}

void TFT_init()
{
	DDRA = OUTPUT;
	PORTA = ~(0b01);
	_delay_ms(500);
	DATA_DDR = OUTPUT;
	CONTROL_DDR = OUTPUT;
	CONTROL_PORT = 0b11011;
	_delay_ms(2000);
	//TFT_write_data(TFT_SW_RESET, NULL, 0);
	PORTA = ~(2u);
	_delay_ms(500);
	
	uint8_t tmp = (0b110<<TFT_DPI)|(0b110<<TFT_DBI); // RGB = 18bit, MCU = 18bit
	TFT_write_data(TFT_INTERFACE_PIXEL_FORMAT, &tmp, 1);
	
	while(1)
	{
		TFT_write_data(TFT_DISPLAY_ON, NULL, 0);
		PORTA = ~(1u);
		_delay_ms(500);
		TFT_write_data(TFT_DISPLAY_OFF, NULL, 0);
		PORTA = ~(0u);
		_delay_ms(500);
		
		uint8_t test = 0;
		TFT_read_data(TFT_READ_PIXEL_FORMAT, &test,1);
		PORTA = ~test;
		_delay_ms(500);
	}
	
	
	
	
	PORTA = ~(3);_delay_ms(500);
	
	tmp = (0<<5);
	TFT_write_data(TFT_MEMORY_ACCESS_CONTROL, &tmp,1);
	PORTA = ~(4);_delay_ms(500);
	TFT_write_data(TFT_SLEEP_OUT, NULL, 0);
	PORTA = ~(5);_delay_ms(500);
	//TFT_write_data(TFT_NORMAL_DISPLAY_MODE_ON, NULL, 0);
	
	//TFT_write_data(TFT_ALL_PIXEL_OFF, NULL, 0);
	PORTA = ~(0xff);_delay_ms(500);
	//while(1);
	//TFT_write_data(TFT_DISPLAY_ON, NULL, 0);
	
	uint8_t test_data[1000];
	
	for(unsigned i = 0; i < 1000; i++)
	{
		test_data[i] = (uint8_t)i;
	}
	
	TFT_write_data(TFT_MEMORY_WRITE, test_data, 1000);
	
	
}