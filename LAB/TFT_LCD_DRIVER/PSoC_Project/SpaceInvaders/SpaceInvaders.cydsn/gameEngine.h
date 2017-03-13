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
#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <project.h>
#include "GameSubjectFactory.h"
#include "GFXNumber.h"    

#define subjectLimit 40
#define shootsInAirLimit 20
enum teamID{Player, Enemies};
enum Gdir{UP, DOWN, LEFT, RIGTH};
struct GameEngine;

void GameEngine_init(struct GameEngine * this, struct GameSubjectFactory * factory, char nextLevel);

struct coord
{
    int16 X;
    int16 Y;
};

struct GameEngine
{
    uint32 points_;
    struct GameSubject * subjects_[subjectLimit];
    struct GameSubject * shoots_[shootsInAirLimit];
    uint8 shootSpeed_[shootsInAirLimit];
    uint8 shootDir_[shootsInAirLimit];
    
    struct GameSubjectFactory * factory_;
    struct GFXNumber finalScore_;
    struct GFXNumber HighScore_;
    
    
    int16 (*spawn)(struct GameEngine * this, char * name, int8 teamID, int16 killpoints, int16 X, int16 Y, int8 lives); //return subject ID if -1 wrong name, -2 subject limit.
    int8 (*move)(struct GameEngine * this, uint8 ID, int16 X, int16 Y, char relativ);
    struct coord (*getPos)(struct GameEngine * this, uint8 ID);
    int8 (*shoot)(struct GameEngine * this, uint8 ID, int8 dir, char * type, uint8 speed);
    int8 (*isDead)(struct GameEngine * this, uint8 ID);
    void (*tick)(struct GameEngine * this);
    int8 (*lifeLeft)(struct GameEngine * this, uint8 ID);
    //new functions
    
    void (*endGame)(struct GameEngine * this);
    void (*nextLevel)(struct GameEngine * this);
};

#endif
/* [] END OF FILE */
