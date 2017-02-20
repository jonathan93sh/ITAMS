/*
 * TFT_LCD.h
 *
 * Created: 19-02-2017 20:21:42
 *  Author: jonathan
 */ 


#ifndef TFT_LCD_H_
#define TFT_LCD_H_

#define DATA_PORT	PORTA	
#define CONTROL_PORT PORTB

#define DATA_DDR DDRA
#define CONTROL_DDR DDRB

#define WRX 0
#define RDX 1
#define DCX 2//eller RS
#define CSX 3
#define RST 4

/**
 * Klargøre skærmen
**/
void TFT_init(); // j

/**
 * sætter positionen på en bestemt pixel.
 * x = vandret
 * y = lodret
**/
void TFT_setPos(unsigned x, unsigned y); // L
/**
 * Bruges til at tænde eller slukke skærmen.
 * 0 => off
 * 1 => on
**/
void TFT_Screen(uint8_t on); // J
/**
 * renser alt hukommelse på skærm kontrolleren.
 * reset værdi er 255:255:255 rgb
**/
void TFT_clear(); // L
/**
 * sætter en enkel pixel.
**/
void setPixel(uint8_t red, uint8_t green, uint8_t blue); // L
/**
 * sætter et array af pixels.
**/
void setPixels(uint8_t * red, uint8_t * green, uint8_t * blue, size_t len); // J


//////////////////////////////////////////////////////////////////////////
// Private funktioner

/**
 * Bruges til at styre de pins der bruges som kommando pins.
 * |7    -  |--4|--3|--2|--1|--0|
 * |--------|RST|CSX|DCX|RDX|WRX|
**/
void TFT_write_com(uint8_t com); //L
/**
 * Brugest til at styre den port der bruges til data.
 * | 7-0|
 * |data|
**/
void TFT_write_data(uint8_t data); //J
/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/
void TFT_read_data(uint8_t data); // L
/**
 * Tilskrive til skærmen, ved først at sende kommando og eventuelt data efterfølgende.
 * datasize = er længden af data.
**/
void TFT_write_data(uint8_t cmd, uint8_t *data, size_t datasize); //J
/**
 * Bruges til at aflæse fra skærmen eventuelt status beskeder.
 * return er længden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8_t cmd, uint8_t *dataOut, size_t bufSize); //J
/**
 * sætter Column adresse.
**/
void TFT_setColumnAddress(unsigned addr); // L
/**
 * sætter page adresse.
**/
void TFT_setPageAddress(unsigned addr); // L


#endif /* TFT_LCD_H_ */