#include "touch.h"
#include "TFT_LCD.h"
#include "math.h"

#define ADC_MAX_INPUT 3300
#define x_max 480
#define y_max 320

static uint16 Xm_; //A3 /p2-1
static uint16 Yp_; //A2 /p2-2

uint16 R_xplate = 300; //Rxm + Rxp ... hmmm##########

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
    LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    DATA_1_SetDriveMode(DATA_1_DM_DIG_HIZ);
    
    DDR_DATA = 0b11111101; //input D1 (ym), output D0 (xp)
    DATA_0_Write(1); //xp
    DATA_1_Write(0); //ym
    //PORT_DATA = 0x00;
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(0); //Yp => 0
    
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 yp_temp = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    
    DATA_1_SetDriveMode(DATA_1_DM_STRONG); //xp
    LCD_RS_SetDriveMode(LCD_RS_DM_STRONG); //xm

    return (ADC_MAX_INPUT-yp_temp);
}


//For at læse Y coord, skal følgende sættes op:
// Xp=LOW, Xm=LOW, Ym=LOW, Yp=HIGH.
// Xp=INPUT, Xm=INPUT, Ym=OUTPUT, Yp=OUTPUT
// Aflæse Xm med ADCen. 
uint16 ReadTouchY()
{
    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    DATA_0_SetDriveMode(DATA_0_DM_DIG_HIZ);
    
    DDR_DATA = 0b10; //output D1 (ym), input D0 (xp)
    //DATA_0_Write(0); //xp
    //DATA_1_Write(0); //ym
    PORT_DATA = 0b00;
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(1); //Yp => 1
    
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 xm_temp = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    
    DATA_0_SetDriveMode(DATA_0_DM_STRONG); //xp
    //LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG); //xm
    
    return (ADC_MAX_INPUT-xm_temp);
}


//For at læse Modstanden, skal følgende sættes op:
// Xp=LOW, Xm=LOW, Ym=HIGH, Yp=LOW.
// Xp=OUTPUT, Xm=INPUT, Ym=OUTPUT, Yp=INPUT 
// Aflæse Xm og Yp med ADCen for at få Z1 og Z2 impedanserne.
uint8 getPressure()
{
    double R_TOUCH, tempTouch, ScaleFactor = 255/ADC_MAX_INPUT;
    
    //Først D0 (xp) og D1(ym) til outputs..
    DDR_DATA = 0b11;
    //DATA_0_Write(0); //xp 0
    //DATA_1_Write(1); //ym 1
    PORT_DATA = 0b10;
    
    //Gøre dem høj impedans til aflæsning
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(0); //Yp => 1
    
    ADC_TOUCH_StartConvert();
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 Z1 = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    uint16 Z2 = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));

    if (R_xplate != 0)
    {
        tempTouch = ((R_xplate*ReadTouchX())*((Z2/Z1)-1))/(1024);
        R_TOUCH = round(ScaleFactor*tempTouch);
        if(R_TOUCH > 255)
            R_TOUCH = 255;
    }
    else
    {
        tempTouch = round(ScaleFactor*((double)(ADC_MAX_INPUT-(Z2-Z1))));
        if(tempTouch > 255)
            tempTouch = 255;
        
        return (uint8)tempTouch;
    }
            
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG);
    LCD_RS_SetDriveMode(LCD_RS_DM_STRONG);
    
    return ((uint8)R_TOUCH);
}

uint8 TouchStatus()
{
    //return ADC_TOUCH_IsEndConversion(ADC_TOUCH_RETURN_STATUS); //returnerer 0 hvis ikke i brug/færdig, ellers nonzero value.
    return 1;
}
uint8 StartTouch()
{
    PORT_WR = 2;
    return 1;
}

struct Coordinates ReadTouch()
{
    struct Coordinates Coords;
    
    uint16 tempX = ReadTouchX();
    uint16 tempY = ReadTouchY();
       
    double XScaleFactor = x_max/(ADC_MAX_INPUT);
    double YScaleFactor = y_max/(ADC_MAX_INPUT);
        
    double XMeasured = round((double)(XScaleFactor*(ADC_MAX_INPUT-tempX)));
    double YMeasured = round((double)(YScaleFactor*(ADC_MAX_INPUT-tempY)));
    
    if(XMeasured > x_max)
        XMeasured = x_max;
    
    if(YMeasured > y_max)
        YMeasured = y_max;
    
    Coords.X_ = (uint16)XMeasured;
    Coords.Y_ = (uint16)YMeasured;
    Coords.pressure_ = getPressure();
    
    PORT_WR = 0;
    
    return Coords;
};

void Touch_init()
{
    ADC_TOUCH_Start();
    ADC_TOUCH_IRQ_Enable();
    StartTouch();
    //hmm##
}

