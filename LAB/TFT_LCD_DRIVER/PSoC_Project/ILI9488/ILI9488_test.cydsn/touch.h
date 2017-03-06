#include "project.h"

#ifndef TOUCH_H_
#define TOUCH_H_

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
void readTouch_better(uint16 * X, uint16 * Y, uint8 * press, uint8 * trig);
//void CalibrateTouch();
#endif


