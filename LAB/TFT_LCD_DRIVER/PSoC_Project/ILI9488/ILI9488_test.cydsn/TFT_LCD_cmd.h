/*
 * TFT_LCD_cmd.h
 *
 * Created: 20-02-2017 09:12:32
 *  Author: jonathan
 */ 


#ifndef TFT_LCD_CMD_H_
#define TFT_LCD_CMD_H_

#define TFT_NOP 0x00
#define TFT_SW_RESET 0x01
#define TFT_DISPLAY_STATUS 0x09
#define TFT_READ_PIXEL_FORMAT 0x0C
#define TFT_READ_DISPLAY_IMAGE_MODE 0x0D
#define TFT_READ_DISPLAY_SIGNAL_MODE 0x0E
#define TFT_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT 0x0F
#define TFT_SLEEP_IN 0x10
#define TFT_SLEEP_OUT 0x11
#define TFT_PARRTIAL_MODE_ON 0x12
#define TFT_NORMAL_DISPLAY_MODE_ON 0x13
#define TFT_ALL_PIXEL_OFF 0x22
#define TFT_ALL_PIXEL_ON 0x23
#define TFT_DISPLAY_OFF 0x28
#define TFT_DISPLAY_ON 0x29
#define TFT_COLUMN_ADDRESS_SET 0x2A
#define TFT_PAGE_ADDRESS_SET 0x2B
#define TFT_MEMORY_WRITE 0x2C
#define TFT_MEMORY_READ 0x2E
#define TFT_MEMORY_ACCESS_CONTROL 0x36
#define TFT_VERTICAL_SCROLLING_START_ADDRESS 0x37
#define TFT_IDLE_MODE_OFF 0x38
#define TFT_IDLE_MODE_ON 0x39
#define TFT_INTERFACE_PIXEL_FORMAT 0x3A
#define TFT_MEMORY_WRITE_CONTINUE 0x3C
#define TFT_MEMORY_READ_CONTINUE 0x3E

#define TFT_DPI 4
#define TFT_DBI 0

#endif /* TFT_LCD_CMD_H_ */