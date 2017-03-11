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
#include "SubjectFactory.h"
#include "numberPrint.h"    

#define subjectLimit 20
#define shootsInAirLimit 15
enum teamID{Player, Enemies};
enum Gdir{UP, DOWN, LEFT, RIGTH};
struct GameEngine;

void GameEngine_init(struct GameEngine * this, struct SubjectFactory * factory, char nextLevel);

struct coord
{
    int16 X;
    int16 Y;
};

struct GameEngine
{
    uint32 points;
    struct GameSubject * subjects_[subjectLimit];
    struct GameSubject * shoots_[shootsInAirLimit];
    uint8 shootSpeed_[shootsInAirLimit];
    uint8 shootDir_[shootsInAirLimit];
    
    struct SubjectFactory * factory_;
    struct NumberGFX finalScore;
    struct NumberGFX HighScore;
    
    
    int16 (*spawn)(struct GameEngine * this, char * name, int8 teamID, int16 killpoints, int16 X, int16 Y, int8 lives); //return subject ID if -1 wrong name, -2 subject limit.
    int8 (*move)(struct GameEngine * this, uint8 ID, int16 X, int16 Y, char relativ);
    struct coord (*getPos)(struct GameEngine * this, uint8 ID);
    int8 (*shoot)(struct GameEngine * this, uint8 ID, int8 dir, char * type, uint8 speed);
    uint8 (*isDead)(struct GameEngine * this, uint8 ID);
    int8 (*tick)(struct GameEngine * this);
    int8 (*lifeLeft)(struct GameEngine * this, uint8 ID);
    //new functions
    
    void (*endGame)(struct GameEngine * this);
    void (*nextLevel)(struct GameEngine * this);
};

#endif
/* [] END OF FILE */
