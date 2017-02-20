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
 * Klarg�re sk�rmen
**/
void TFT_init(); // j

/**
 * s�tter positionen p� en bestemt pixel.
 * x = vandret
 * y = lodret
**/
void TFT_setPos(unsigned x, unsigned y); // L
/**
 * Bruges til at t�nde eller slukke sk�rmen.
 * 0 => off
 * 1 => on
**/
void TFT_Screen(uint8_t on); // J
/**
 * renser alt hukommelse p� sk�rm kontrolleren.
 * reset v�rdi er 255:255:255 rgb
**/
void TFT_clear(); // L
/**
 * s�tter en enkel pixel.
**/
void setPixel(uint8_t red, uint8_t green, uint8_t blue); // L
/**
 * s�tter et array af pixels.
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
 * Brugest til at afl�se data fra data porten.
 * | 7-0|
 * |data|
**/
void TFT_read_data(uint8_t data); // L
/**
 * Tilskrive til sk�rmen, ved f�rst at sende kommando og eventuelt data efterf�lgende.
 * datasize = er l�ngden af data.
**/
void TFT_write_data(uint8_t cmd, uint8_t *data, size_t datasize); //J
/**
 * Bruges til at afl�se fra sk�rmen eventuelt status beskeder.
 * return er l�ngden af hvor data der er hentet.
**/
size_t TFT_read_data(uint8_t cmd, uint8_t *dataOut, size_t bufSize); //J
/**
 * s�tter Column adresse.
**/
void TFT_setColumnAddress(unsigned addr); // L
/**
 * s�tter page adresse.
**/
void TFT_setPageAddress(unsigned addr); // L


#endif /* TFT_LCD_H_ */