/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef GAMESUBJECT_H_
#define GAMESUBJECT_H_

#include "project.h"
#include "GFX.h"

struct GameSubject;
/**
 * Denne funktion bliver brugt for at initialiser et GameSubject.
 */   
void GameSubject_init(struct GameSubject * this, const uint8 * graph_tex, const uint16 sizeX, const uint16 sizeY, struct GFXColor color, struct GFXColor BgColor, uint16 X, uint16 Y, int8 lives, int16 killPoints,  uint8 ID, int8 TeamID);
/**
 * Denne struct indeholder en række informationer omkring et Subjekt. Som antallet af liv og position. Den indeholder og klassen(struct) GFXObject som er et grafisk objekt.
 */
struct GameSubject
{
    struct GFXObject graph_;
    int8 lives_;
    int16 killPoints_;
    uint8 ID_;
    int8 TeamID_;
    int16 X_;
    int16 Y_;
    //void (*move)(struct GameSubject * this, uint16 X, uint16 Y);
    //void (*shoot)(struct GameSubject * this, struct GFXObject * shell, enum Gdir dir);
    //void (*damage)(struct GameSubject * this, uint8 hitDamage);
    //void (*hit)(struct GameSubject * this, struct GameSubject * other);
};

#endif
/* [] END OF FILE */
