#include "project.h"

#define PORT_TOUCH LCD_Read_Touch_Control

CY_ISR_PROTO(touch_isr);

struct Coordinates
{
    uint16 x_;
    uint16 y_;
    uint8 pressure_;
};

void Touch_init();
uint8 TouchStatus();
uint8 StartTouch();
struct Coordinates ReadTouch();
