/*
 * TFT_LCD_delay.h
 *
 * Created: 20-02-2017 09:30:40
 *  Author: jonathan
 */ 
#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
//#define F_CPU 3686400
#include <util/delay.h>

#ifndef TFT_LCD_DELAY_H_
#define TFT_LCD_DELAY_H_

#define TFT_DELAY_tcsf do {_NOP();} while (0)
#define TFT_DELAY_tcs do {_NOP();} while (0)
#define TFT_DELAY_wcl do {_NOP();} while (0)
#define TFT_DELAY_wch do {_NOP();} while (0)

#define TFT_DELAY_trcsfm do {_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();} while (0) //min 355=> 9 cycles
#define TFT_DELAY_trdhfm do {_NOP();_NOP();_NOP();} while (0) //min 90 => 3 cycles

#endif /* TFT_LCD_DELAY_H_ */