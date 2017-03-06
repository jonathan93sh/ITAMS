#include "touch.h"
#include "TFT_LCD.h"
#include <math.h>

#define ADC_MAX_INPUT 3300
#define x_max 480
#define y_max 320

static uint16 Xm_; //A3 /p2-1
static uint16 Yp_; //A2 /p2-2
static float ScaleFactor = (255/ADC_MAX_INPUT);
static float XScaleFactor = 320.0f/(2200.0f);
static float YScaleFactor = y_max/(ADC_MAX_INPUT);

uint16 R_xplate = 300; //Rxm + Rxp ... hmmm##########

#define WR_AND_WR_RS_OE LCD_WR_AND_WR_RS_OE_Control




/*
CY_ISR(touch_isr)
{
    //sampling done isr
    //Xm_ = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    //Yp_ = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    PORT_TOUCH = 0;
    //ADC_TOUCH_IRQ_Disable();
    LCD_lock_ = 0;
}

CY_ISR(isr_EOC)
{
    //samples are done converting isr
    //Xm_ = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    //Yp_ = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
}
*/

//For at læse X coord, skal følgende sættes op:
// Xp=HIGH, Xm=LOW, Ym=LOW, Yp=LOW.
// Xp=OUTPUT, Xm=OUTPUT, Ym=INPUT, Yp=INPUT
// Aflæse Yp med ADCen. 
uint16 ReadTouchX()
{
    //LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    //DATA_1_SetDriveMode(DATA_1_DM_DIG_HIZ);
    
    DDR_DATA = 0b01000000; //input D1 (ym), output D0 (xp)
    //DATA_0_Write(1); //xp
    //DATA_1_Write(0); //ym
    PORT_DATA = 0b01000000;
    
    //LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(0); //Yp => 0
    WR_AND_WR_RS_OE = 0b011;
    CyDelay(1);
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 yp_temp = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    
    //DATA_1_SetDriveMode(DATA_1_DM_STRONG); //xp
    //LCD_RS_SetDriveMode(LCD_RS_DM_STRONG); //xm
    DDR_DATA = 0;
    PORT_DATA = 0;
    WR_AND_WR_RS_OE = 0b001;
    return (ADC_MAX_INPUT-yp_temp);
}


//For at læse Y coord, skal følgende sættes op:
// Xp=LOW, Xm=LOW, Ym=LOW, Yp=HIGH.
// Xp=INPUT, Xm=INPUT, Ym=OUTPUT, Yp=OUTPUT
// Aflæse Xm med ADCen. 
uint16 ReadTouchY()
{
    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    //DATA_0_SetDriveMode(DATA_0_DM_DIG_HIZ);
    
    DDR_DATA = 0b10000000; //output D1 (ym), input D0 (xp)
    //DATA_0_Write(0); //xp
    //DATA_1_Write(0); //ym
    PORT_DATA = 0b00000000;
    
    //LCD_RS_Write(1); //Yp => 1
    
    WR_AND_WR_RS_OE = 0b101;
    CyDelay(1);
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 xm_temp = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    
    //DATA_0_SetDriveMode(DATA_0_DM_STRONG); //xp
    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG); //xm
    DDR_DATA = 0;
    PORT_DATA = 0;
    WR_AND_WR_RS_OE = 0b001;
    return (xm_temp);
}


//For at læse Modstanden, skal følgende sættes op:
// Xp=LOW, Xm=LOW, Ym=HIGH, Yp=LOW.
// Xp=OUTPUT, Xm=INPUT, Ym=OUTPUT, Yp=INPUT 
// Aflæse Xm og Yp med ADCen for at få Z1 og Z2 impedanserne.
uint8 getPressure()
{
    float R_TOUCH;
    
    //Først D0 (xp) og D1(ym) til outputs..
    DDR_DATA = 0b11000000;
    //DATA_0_Write(0); //xp 0
    //DATA_1_Write(1); //ym 1
    PORT_DATA = 0b01000000;
    
    //Gøre dem høj impedans til aflæsning
    WR_AND_WR_RS_OE = 0b111;
    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    //LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    
    //LCD_WR_Analog_Write(0); //Xm => 0
    //LCD_RS_Write(0); //Yp => 1
    
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 Z1 = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    uint16 Z2 = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));

    R_TOUCH = ((R_xplate*ReadTouchX())*((Z2/Z1)-1))/(1024);
    R_TOUCH = (ScaleFactor*R_TOUCH);
    if(R_TOUCH > 255)
        R_TOUCH = 255;

    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG);
    //LCD_RS_SetDriveMode(LCD_RS_DM_STRONG);
    DDR_DATA = 0;
    PORT_DATA = 0;
    WR_AND_WR_RS_OE = 0b001;
    return ((uint8)R_TOUCH);
}

uint8 TouchStatus()
{
    //return ADC_TOUCH_IsEndConversion(ADC_TOUCH_RETURN_STATUS); //returnerer 0 hvis ikke i brug/færdig, ellers nonzero value.
    return 1;
}
uint8 StartTouch()
{
    //PORT_WR = 2;
    return 1;
}

struct Coordinates ReadTouch()
{
    struct Coordinates Coords;
    
    uint16 tempY = ReadTouchY();
    uint16 tempX = ReadTouchX();

       
    uint16 XMeasured = (uint16)((XScaleFactor*(ADC_MAX_INPUT-tempX)));
    uint16 YMeasured = (uint16)(YScaleFactor*(ADC_MAX_INPUT-tempY));
    
    if(XMeasured > x_max)
        XMeasured = x_max;
    
    if(YMeasured > y_max)
        YMeasured = y_max;
    
    Coords.X_ = XMeasured;
    Coords.Y_ = YMeasured;
    Coords.pressure_ = getPressure();
    
    //WR_AND_WR_RS_OE = 1;
    
    return Coords;
};

void Touch_init()
{
    ADC_TOUCH_Start();
    StartTouch();
    //hmm##
}

static uint16 X_pre = 0;
static uint8 press_pre = 0;

void readTouch_better(uint16 * X, uint8 * press)
{
    int16 X_calc;
    
    uint16 pressCheck = (ReadTouchY() > 2600 ? 1 : 0);
    uint16 tempX = ReadTouchX();
    
    //uint16 XMeasured = (uint16)((XScaleFactor*(ADC_MAX_INPUT-tempX)));
    X_calc = (int16)((float)(tempX-600)*XScaleFactor);
    if(X_calc > 320)
        X_calc = 320;
    else if(X_calc < 0)
        X_calc = 0;
    
    *press = 0;
    
    if(pressCheck)
    {
        if(press_pre == 0)
        {
            *press = 1;
        }
        *X = X_calc;
        X_pre = X_calc;
    }
    else
    {
        *X = X_pre;
        
    }
    
    press_pre = pressCheck;
    
}
