/*
 * TFT_LCD_delay.h
 *
 * Created: 20-02-2017 09:30:40
 *  Author: jonathan
 */ 

#ifndef TFT_LCD_DELAY_H_
#define TFT_LCD_DELAY_H_

#define _NOP() asm("NOP")
    
#define TFT_DELAY_tcsf do {_NOP();} while (0)
#define TFT_DELAY_tcs do {_NOP();} while (0)
#define TFT_DELAY_trcs do {_NOP();_NOP();_NOP();} while (0) //min 45ns => 3 cycles
#define TFT_DELAY_wcl do {_NOP();} while (0) //min 30ns => 2 cycles
#define TFT_DELAY_wch do {_NOP();} while (0)

#define TFT_DELAY_trcsfm do {_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();} while (0) //min 355=> 18 cycles
#define TFT_DELAY_trdhfm do {_NOP();_NOP();_NOP();_NOP();_NOP();} while (0) //min 90 => 5 cycles

#endif /* TFT_LCD_DELAY_H_ */