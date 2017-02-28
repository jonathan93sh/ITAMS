/*
 * TFT_LCD.h
 *
 * Created: 19-02-2017 20:21:42
 *  Author: jonathan
 */ 

#include "project.h"



#ifndef TFT_LCD_H_
#define TFT_LCD_H_
    
#define PORT_DATA PORT_DATA_Control
#define DDR_DATA DDR_DATA_Control
#define PIN_DATA PIN_DATA_Status
#define PORT_WR LCD_WR_Control


    
/*

#define PORT_RS LCD_RS_Control
#define PORT_CS LCD_CS_Control
#define PORT_RD LCD_RD_Control
#define PORT_RST LCD_RST_Control   
*/    
    
    
/*
#define DATA_PORT	PORTC	
#define CONTROL_PORT PORTB

#define DATA_PIN PINC;

#define DATA_DDR DDRC
#define CONTROL_DDR DDRB

#define INPUT 0x00
#define OUTPUT 0xFF

#define WRX 0
#define RDX 1
#define DCX 2//eller RS
#define CSX 3
#define RST 4
*/
/**
 * Klarg�re sk�rmen
**/
void TFT_init(); // j
void TFT_start_print();
void TFT_write_print(uint8 R, uint8 G, uint8 B, unsigned N);
void TFT_end_print();
void TFT_setWindow(unsigned x_start, unsigned x_end, unsigned y_start, unsigned y_end);
/**
 * s�tter positionen p� en bestemt pixel.
 * x = vandret
 * y = lodret
**/
//void TFT_setPos(unsigned x, unsigned y); // L
/**
 * Bruges til at t�nde eller slukke sk�rmen.
 * 0 => off
 * 1 => on
**/
//void TFT_Screen(uint8 on); // J
/**
 * renser alt hukommelse p� sk�rm kontrolleren.
 * reset v�rdi er 255:255:255 rgb
**/
//void TFT_clear(); // L
/**
 * s�tter en enkel pixel.
**/
//void setPixel(uint8 red, uint8 green, uint8 blue); // L
/**
 * s�tter et array af pixels.
**/
//void setPixels(uint8 * red, uint8 * green, uint8 * blue, size_t len); // J


//////////////////////////////////////////////////////////////////////////
// Private funktioner

/**
 * Bruges til at styre de pins der bruges som kommando pins.
 * |7    -  |--4|--3|--2|--1|--0|
 * |--------|RST|CSX|DCX|RDX|WRX|
**/
//void TFT_write_com(uint8 com); //L
/**
 * Brugest til at styre den port der bruges til data.
 * | 7-0|
 * |data|
**/
//void TFT_write_data(uint8 data); //J
/**
 * Brugest til at afl�se data fra data porten.
 * | 7-0|
 * |data|
**/

//void TFT_read_data(uint8 *dataPtr); // L
/**
 * Tilskrive til sk�rmen, ved f�rst at sende kommando og eventuelt data efterf�lgende.
 * datasize = er l�ngden af data.
**/
void TFT_write_data(uint8 cmd, uint8 *data, size_t datasize); //J
/**
 * Bruges til at afl�se fra sk�rmen eventuelt status beskeder.
 * return er l�ngden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8 cmd, uint8 *dataOut, size_t bufSize); //J
/**
 * s�tter Column adresse.
**/
//void TFT_setColumnAddress(unsigned addr); // L
/**
 * s�tter page adresse.
**/
//void TFT_setPageAddress(unsigned addr); // L

void execute_cmd(uint8 cmd);
void send_data(uint8 data);
void receive_data(uint8 *dataPtr);
void TFT_test();


#endif /* TFT_LCD_H_ */