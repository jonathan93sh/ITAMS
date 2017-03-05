#include "touch.h"
#include "TFT_LCD.h"
#include "math.h"

#define ADC_MAX_INPUT 3300
#define x_max 480
#define y_max 320

static uint16 Xm_; //A3 /p2-1
static uint16 Yp_; //A2 /p2-2

uint16 R_xplate = 1; //Rxm + Rxp ... hmmm##########

static uint8 LCD_lock_;

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

uint16 ReadTouchX()
{
    //For at læse X coord, skal følgende sættes op:
    // Xp=HIGH, Xm=LOW, Ym=LOW, Yp=LOW.
    // Xp=OUTPUT, Xm=OUTPUT, Ym=INPUT, Yp=INPUT
    // Aflæse Yp med ADCen. 
    
    LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    DATA_1_SetDriveMode(DATA_1_DM_DIG_HIZ);
    
    DDR_DATA = 0b11111101; //input D1 (ym), output D0 (xp)
    DATA_0_Write(1); //xp
    DATA_1_Write(0); //ym
    //PORT_DATA = 0x00;
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(0); //Yp => 0
    
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 yp_temp = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    
    DATA_1_SetDriveMode(DATA_1_DM_STRONG); //xp
    LCD_RS_SetDriveMode(LCD_RS_DM_STRONG); //xm

    return (ADC_MAX_INPUT-yp_temp);
}

uint16 ReadTouchY()
{
    //For at læse Y coord, skal følgende sættes op:
    // Xp=LOW, Xm=LOW, Ym=LOW, Yp=HIGH.
    // Xp=INPUT, Xm=INPUT, Ym=OUTPUT, Yp=OUTPUT
    // Aflæse Xm med ADCen. 
    
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    DATA_0_SetDriveMode(DATA_0_DM_DIG_HIZ);
    
    DDR_DATA = 0b11111110; //output D1 (ym), input D0 (xp)
    DATA_0_Write(0); //xp
    DATA_1_Write(0); //ym
    //PORT_DATA = 0x00;
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(1); //Yp => 1
    
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 xm_temp = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    
    DATA_0_SetDriveMode(DATA_0_DM_STRONG); //xp
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG); //xm
    
    return (ADC_MAX_INPUT-xm_temp);
}
uint8 getPressure()
{
    //halvbro til at måle resistancen - korrekt setup før der kan måles på impedancen for x og y. 
    //For at læse Modstanden, skal følgende sættes op:
    // Xp=LOW, Xm=LOW, Ym=HIGH, Yp=LOW.
    // Xp=OUTPUT, Xm=INPUT, Ym=OUTPUT, Yp=INPUT 
    // Aflæse Xm og Yp med ADCen for at få Z1 og Z2 impedanserne.
    
    //Først D0 (xp) og D1(ym) til outputs..
    DDR_DATA = 0xFF;
    DATA_0_Write(0); //xp 0
    DATA_1_Write(1); //ym 1
    //PORT_DATA = 0b10;
    
    //Gøre dem høj impedans til aflæsning
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_ALG_HIZ);
    LCD_RS_SetDriveMode(LCD_RS_DM_ALG_HIZ);
    
    LCD_WR_Analog_Write(0); //Xm => 0
    LCD_RS_Write(0); //Yp => 1
    
    ADC_TOUCH_IsEndConversion(ADC_TOUCH_WAIT_FOR_RESULT);
    uint16 Z1 = ADC_TOUCH_CountsTo_mVolts(0u, ADC_TOUCH_GetResult16(0));
    uint16 Z2 = ADC_TOUCH_CountsTo_mVolts(1u, ADC_TOUCH_GetResult16(1));
    double R_TOUCH;
    
    if (R_xplate != 0)
    {
        R_TOUCH = ((R_xplate*ReadTouchX())*((Z2/Z1)-1))/(1024);
    }
    else
        return ((ADC_MAX_INPUT-(Z2-Z1))%255);
        
    //mmmmmmmmmh######
        
    LCD_WR_Analog_SetDriveMode(LCD_WR_Analog_DM_STRONG);
    LCD_RS_SetDriveMode(LCD_RS_DM_STRONG);
    
    
    return ((uint8)R_TOUCH);
}

uint8 TouchStatus()
{
    //return ADC_TOUCH_IsEndConversion(ADC_TOUCH_RETURN_STATUS); //returnerer 0 hvis ikke i brug/færdig, ellers nonzero value.
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
    //ADC_TOUCH_IRQ_Enable();
    PORT_TOUCH = 1;
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
    
    Coords.Xm_ = (uint16)XMeasured;
    Coords.Yp_ = (uint16)YMeasured;
    Coords.pressure_ = getPressure();
    
    return Coords;
};

void Touch_init()
{
    ADC_TOUCH_Start();
    ADC_TOUCH_IRQ_Enable();
    StartTouch();
    
}

