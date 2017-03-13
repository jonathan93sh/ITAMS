#include "project.h"

#ifndef TOUCH_H_
#define TOUCH_H_

//Initierer ADCen og laver nogle dummy reads, så vi ikke kan få nogle fejl aflæsninger.
void Touch_init();

//Aflæser touch værdier, skalerer dem og finder ud af om der er blevet trykket på skærmen.
void readTouch_better(uint16 * X, uint16 * Y, uint8 * press, uint8 * trig);
#endif


