#include "project.h"

//#define PORT_TOUCH LCD_WR_AND_WR_RS_OE_SOC_Control

CY_ISR_PROTO(touch_isr);
CY_ISR_PROTO(isr_EOC);

struct Coordinates
{
    uint16 X_;
    uint16 Y_;
    uint8 pressure_;
};

void Touch_init();
uint8 TouchStatus();
uint8 StartTouch();
struct Coordinates ReadTouch();


//void CalibrateTouch();
