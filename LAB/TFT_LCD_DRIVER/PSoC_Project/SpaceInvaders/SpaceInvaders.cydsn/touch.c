#include "touch.h"
#include "TFT_LCD.h"
#include <math.h>

#define ADC_MAX_INPUT 3300
#define x_max 480
#define y_max 320

static uint16 Xm_; //A3 /p2-1
static uint16 Yp_; //A2 /p2-2
static float ScaleFactor = (255.0f)/2.2f;
static float XScaleFactor = 320.0f/(2200.0f);
static float YScaleFactor = y_max/(ADC_MAX_INPUT);

uint16 R_xplate = 300; //Rxm + Rxp ... normalt 300ohm

#define WR_AND_WR_RS_OE LCD_WR_AND_WR_RS_OE_Control

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
    //CyDelay(1);
    CyDelay(1);
    //CyDelayUs
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 yp_temp = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    
    //DATA_1_SetDriveMode(DATA_1_DM_STRONG); //xp
    //LCD_RS_SetDriveMode(LCD_RS_DM_STRONG); //xm
    DDR_DATA = 0;
    PORT_DATA = 0;
    WR_AND_WR_RS_OE = 0b001;
    LCD_RS_Write(1);
    return (yp_temp);
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
    volatile float Z1 = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1))-4020.0f;
    volatile float Z2 = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(0))-4020.0f;

    static const float XScale = 320.0f/(4258.0f - 1616.0f);
    
    R_TOUCH = ((float)(R_xplate*((ReadTouchX()*XScale)))*((Z1/Z2)-1))/(1024.0f);
    

    R_TOUCH = (ScaleFactor*R_TOUCH);
    if(R_TOUCH > 255)
        R_TOUCH = 255;
    else if(R_TOUCH < 0)
        R_TOUCH = 0;

    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG);
    //LCD_RS_SetDriveMode(LCD_RS_DM_STRONG);
    DDR_DATA = 0;
    PORT_DATA = 0;
    WR_AND_WR_RS_OE = 0b001;
    return ((uint8)R_TOUCH);
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
    volatile uint16 result0, result1;
    ADC_TOUCH_Start();
    
    LCD_RS_Write(0);
    WR_AND_WR_RS_OE = 0b000;
    
    CyDelay(10);
    
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    ADC_TOUCH_GetResult16(0);
    ADC_TOUCH_GetResult16(1);
    CyDelay(10);
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    ADC_TOUCH_GetResult16(0);
    ADC_TOUCH_GetResult16(1);
    CyDelay(10);
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    
    
    
    result0 =  ADC_TOUCH_GetResult16(0);
    result1 = ADC_TOUCH_GetResult16(1);
    
    ADC_TOUCH_SetOffset(0u,result0);
    ADC_TOUCH_SetOffset(1u,result1);
    
    if(ADC_TOUCH_CountsTo_mVolts(0,result0) != 0 || ADC_TOUCH_CountsTo_mVolts(1,result1) != 0)
        while(1);
    
    LCD_RS_Write(1);
    WR_AND_WR_RS_OE = 0b001;
}


static int16 X_pre = 0;
    static int16 Y_pre = 0;
    static uint8 press_pre = 0;

void readTouch_better(uint16 * X, uint16 * Y, uint8 * press, uint8 * trig)
{
    static const float XScale = 320.0f/(3379.0f - 620.0f);
    static const int16 XOffset = 620;//mv
    static const float YScale = 480.0f/(4102.0f-4082.0f);
    static const int16 YOffset = 4082;//mv

    static const int16 Y_noPress_min = 3804 + 150;//mv
    static const int16 X_noPress_min = 3188 + 150;//mv
    
    int16 X_calc;
    int16 Y_calc;
    uint8 pressCheck;
    
    int16 tempY = (ReadTouchY());
    int16 tempX = (ReadTouchX());// - (2500+230);
    
    pressCheck = (tempY > Y_noPress_min && tempX < X_noPress_min ? 1 : 0);
    
    //uint16 XMeasured = (uint16)((XScaleFactor*(ADC_MAX_INPUT-tempX)));
    X_calc = 320 - (int16)((float)(tempX-XOffset)*XScale);
    if(X_calc > 320)
        X_calc = 320;
    else if(X_calc < 0)
        X_calc = 0;
    
    Y_calc = 480 - (int16)((float)(tempY-YOffset)*YScale);
    if(Y_calc > 480)
        Y_calc = 480;
    else if(Y_calc < 0)
        Y_calc = 0;
    
    
    if(pressCheck)
    {
        if(press_pre == 0)
        {
            *trig = 1;
        }
        else
        {
            *trig = 0;   
        }
        *X = X_calc;
        *Y = Y_calc;
        X_pre = X_calc;
        Y_pre = Y_calc;
    }
    else
    {
        *X = X_pre;
        *Y = Y_pre;
        *trig = 0;
    }
    
    *press = pressCheck;
    press_pre = pressCheck;
    
}
