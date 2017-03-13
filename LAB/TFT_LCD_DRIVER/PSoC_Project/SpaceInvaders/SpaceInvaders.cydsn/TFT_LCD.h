/*
 * TFT_LCD.h
 *
 * Created: 19-02-2017 20:21:42
 *  Author: Group 11 (Laimonas, Jonathan)
 */ 

#ifndef TFT_LCD_H_
#define TFT_LCD_H_

#include "project.h"    
    
#define SCREEN_SIZE_X 480
#define SCREEN_SIZE_Y 320
    
#define PORT_DATA PORT_DATA_Control
#define DDR_DATA DDR_DATA_Control
#define PIN_DATA PIN_DATA_Status
#define PORT_WR LCD_WR_AND_WR_RS_OE_Control

/**
 * Klargøre skærmen
**/
void TFT_init();

/**
 * Denne funktion skal bruges før man kan skrive til TFT Displayet.
 */
void TFT_start_print();
/** 
 * Denne Funktion bruges til at tilskrive pixel værdier, og antallet af pixel der skal tilskrives.
 */ 
void TFT_write_print(uint8 R, uint8 G, uint8 B, unsigned N);
/**
 * Denne funktion afslutter en tilskrivning.
 */ 
void TFT_end_print();

/**
 * Sætter et vindue som der kan skrives til med TFT_*_print funktionerne.
 */
void TFT_setWindow(unsigned x_start, unsigned x_end, unsigned y_start, unsigned y_end);
/**
 * en hjælpe funktion der overskriver hele displayet med en farve.
 */
void TFT_clear_screen(uint8 R, uint8 G, uint8 B);
/**
 * en funktion til at teste TFT Displayet. Note denne funktion er bygget på den funktion Henning har lavet i hans test program til TFT Displayet.
 */
void TFT_test();

//////////////////////////////////////////////////////////////////////////
//----------------------- Private funktioner ---------------------------//

/**
 * sætter positionen på en bestemt pixel.
 * x = vandret
 * y = lodret
**/
//void TFT_setPos(unsigned x, unsigned y);
/**
 * Bruges til at tænde eller slukke skærmen.
 * 0 => off
 * 1 => on
**/
//void TFT_Screen(uint8 on);
/**
 * renser alt hukommelse på skærm kontrolleren.
 * reset værdi er 255:255:255 rgb
**/
//void TFT_clear(); 
/**
 * sætter en enkel pixel.
**/
//void setPixel(uint8 red, uint8 green, uint8 blue); 
/**
 * sætter et array af pixels.
**/
//void setPixels(uint8 * red, uint8 * green, uint8 * blue, size_t len);

/**
 * Bruges til at styre de pins der bruges som kommando pins.
 * |7    -  |--4|--3|--2|--1|--0|
 * |--------|RST|CSX|DCX|RDX|WRX|
**/
//void TFT_write_com(uint8 com);
/**
 * Brugest til at styre den port der bruges til data.
 * | 7-0|
 * |data|
**/
//void TFT_write_data(uint8 data);
/**
 * Brugest til at aflæse data fra data porten.
 * | 7-0|
 * |data|
**/

//void TFT_read_data(uint8 *dataPtr);
/**
 * Tilskrive til skærmen, ved først at sende kommando og eventuelt data efterfølgende.
 * datasize = er længden af data.
**/
//void TFT_write_data(uint8 cmd, uint8 *data, size_t datasize);
/**
 * Bruges til at aflæse fra skærmen eventuelt status beskeder.
 * return er længden af hvor data der er hentet.
**/
//size_t TFT_read_data(uint8 cmd, uint8 *dataOut, size_t bufSize);
/**
 * sætter Column adresse.
**/
//void TFT_setColumnAddress(unsigned addr); 
/**
 * sætter page adresse.
**/
//void TFT_setPageAddress(unsigned addr); 

/*
void execute_cmd(uint8 cmd);
void send_data(uint8 data);
void receive_data(uint8 *dataPtr);
*/

#endif /* TFT_LCD_H_ */