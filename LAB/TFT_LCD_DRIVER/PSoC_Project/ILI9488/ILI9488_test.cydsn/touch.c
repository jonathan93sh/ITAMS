#include "touch.h"





static uint16 X_;
static uint16 Y_;
static uint8 pressure_;

static uint8 LCD_lock_;

CY_ISR(touch_isr)
{
    X_ = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    Y_ = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(1));
    PORT_TOUCH = 0;
    LCD_lock_ = 0;
}

uint16 calcTouchX()
{
    uint16 tempX = X_;
    //function threshhold --> x=> 0->320, y=> 0->480;
    uint16 calcX = tempX; //CALC / CONVERT
    
    return calcX;
}

uint16 calcTouchY();
uint8 getPressure();


uint8 TouchStatus();
uint8 StartTouch()
{
    LCD_lock_ = 1;
    PORT_TOUCH = 1;
    return 1;
}

struct Coordinates ReadTouch(struct Coordinates Coords)
{
    
    Coords.x_ = calcTouchX();
    Coords.y_ = calcTouchY();
    Coords.pressure_ = getPressure();
    
    return Coords;
};

