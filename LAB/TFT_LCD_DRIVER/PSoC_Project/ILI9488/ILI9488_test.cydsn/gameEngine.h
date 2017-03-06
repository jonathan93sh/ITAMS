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
#include "project.h"
#include "GFX.h"

#define subjectLimit 20
#define shootsInAirLimit 8
enum teamID{Player, Enemies};
enum Gdir{UP, DOWN, LEFT, RIGTH};
struct GameEngine;
struct GameSubject;
//struct GamePlayer;
struct SubjectFactory;

void GE_Game_init(struct GameEngine * this, struct SubjectFactory * factory);
void GE_GameSubject_init(struct GameSubject * this, uint8 * graph_tex, uint16 sizeX, uint16 sizeY, struct Color color, struct Color BgColor, uint16 X, uint16 Y, int8 lives, int killPoints,  uint8 ID, int8 TeamID);

//void GE_GamePlayer_init(struct GamePlayer * player);

void GE_SubjectFactory_init(struct SubjectFactory * this, uint8 ** graph_texs, uint16 * sizeXs, uint16 * sizeYs, char ** names, struct Color * colors, struct Color * Bgcolors, size_t length);

struct coord
{
    int16 X;
    int16 Y;
};

struct GameEngine
{
    uint32 points;
    struct GameSubject * subjects_[subjectLimit];
    //uint8 subjectsSize_;
    struct GameSubject * shoots_[shootsInAirLimit];
    uint8 shootSpeed_[shootsInAirLimit];
    uint8 shootDir_[shootsInAirLimit];
    
    
    //int nextPlayerID_;
    //int nextSubjectID_;
    
    struct SubjectFactory * factory_;
    
    
    int (*spawn)(struct GameEngine * this, char * name, int8 teamID, int killpoints, int16 X, int16 Y, int8 lives); //return subject ID if -1 wrong name, -2 subject limit.
    int (*move)(struct GameEngine * this, int ID, int16 X, int16 Y, char relativ);
    struct coord (*getPos)(struct GameEngine * this, int ID);
    int (*shoot)(struct GameEngine * this, int ID, int dir, char * type, uint8 speed);
    uint8 (*isDead)(struct GameEngine * this, int ID);
    int (*tick)(struct GameEngine * this);
};

struct SubjectFactory
{
    uint8 ** graph_texs_;
    uint16 * sizeXs_; 
    uint16 * sizeYs_; 
    char ** names_;
    struct Color * colors_; 
    struct Color * Bgcolors_;
    size_t length_;

    struct GameSubject * (*creat)(struct SubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID);
    void (*delete)(struct SubjectFactory * this, struct GameSubject * object);
};

struct GameSubject
{
    struct graph_object graph_;
    int8 lives_;
    int killPoints_;
    uint8 ID_;
    int8 TeamID_;
    int16 X_;
    int16 Y_;
    //void (*move)(struct GameSubject * this, uint16 X, uint16 Y);
    //void (*shoot)(struct GameSubject * this, struct graph_object * shell, enum Gdir dir);
    //void (*damage)(struct GameSubject * this, uint8 hitDamage);
    //void (*hit)(struct GameSubject * this, struct GameSubject * other);
};



/* [] END OF FILE */
