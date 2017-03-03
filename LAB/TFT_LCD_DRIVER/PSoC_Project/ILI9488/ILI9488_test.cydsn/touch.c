#include "touch.h"

// TODO:
// CalcTouchX() - Finde ud af hvilke værdier der forekommer fra X / Y => derfra udarbejde bruge dem til at udregne en gyldig
// getPressure() - Hvilke værdier aflæser ADCen? Omregn til et threshhold fra 0-255 hvor 255 er max nedtryk på skærmen / størst modstand.
//  dertil finde ud af hvordan den praktisk talt omregner signalet i source.


static uint16 X_;
static uint16 Y_;
static uint8 pressure_;

static uint8 LCD_lock_;

CY_ISR(touch_isr)
{
    X_ = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    Y_ = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    PORT_TOUCH = 0;
    ADC_TOUCH_IRQ_Disable();
    LCD_lock_ = 0;
}

uint16 calcTouchX()
{
    uint16 tempX = X_;
    //function threshhold --> x=> 0->320, y=> 0->480;

    uint16 calcX = tempX; //CALC / CONVERT
    
    return (calcX%320); // temp
}

uint16 calcTouchY()
{
    uint16 calcY;
    
    //stuff
    
    return (calcY%480);
}
uint8 getPressure()
{
    uint8 tempPress;
    
    return (tempPress%255);
}

uint8 TouchStatus()
{
    return LCD_lock_;
}
uint8 StartTouch()
{
    /*
    Note The soc signal must be applied after eoc; otherwise, it implies that the channels were
    sampled later than was intended (jitter). So the data in the result register interprets it as incorrect
    and the component will be stalled
    ^hmm
    */
    LCD_lock_ = 1;
    ADC_TOUCH_IRQ_Enable();
    PORT_TOUCH = 1;
    return 1;
}

struct Coordinates ReadTouch()
{
    struct Coordinates Coords;
    
    Coords.x_ = calcTouchX();
    Coords.y_ = calcTouchY();
    Coords.pressure_ = getPressure();
    
    return Coords;
};

void Touch_init()
{
    ADC_TOUCH_Start();
    StartTouch();
    
}

