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
#define playerLimit 1

enum Gdir{UP, DOWN, LEFT, RIGTH};
struct Game;
struct GameSubject;
struct GamePlayer;

void GE_Game_init(struct Game * game, void(*)(struct Game * this));
void GE_GameSubject_init(struct GameSubject * subject);
void GE_GamePlayer_init(struct GamePlayer * player);

struct Game
{
    uint32 points;
    struct GameSubject * subjects_[subjectLimit];
    uint8 subjectsSize_;
    struct GamePlayer * player_[playerLimit];
    uint8 playerSize_;
    void (*add)(struct Game * this, struct GameSubject* subject);
    void (*tick)(struct Game * this);
    void (*shootFire)(struct Game * this, struct GameSubject * shooter, struct graph_object * shell, enum Gdir dir);
    // pure virtual;
    void (*control)(struct Game * this); 
};

struct GameSubject
{
    struct Game * theGame_;
    struct graph_object graph_;
    int8 lives_;
    uint8 ID_;
    uint16 X_;
    uint16 Y_;
    void (*move)(struct GameSubject * this, uint16 X, uint16 Y);
    void (*shoot)(struct GameSubject * this, struct graph_object * shell, enum Gdir dir);
    void (*damage)(struct GameSubject * this, uint8 hitDamage);
    void (*hit)(struct GameSubject * this, struct GameSubject * other);
};

struct GamePlayer
{
    struct GameSubject subject_;
};


/* [] END OF FILE */
