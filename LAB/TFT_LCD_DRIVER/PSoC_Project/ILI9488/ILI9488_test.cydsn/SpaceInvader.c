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
#include <stdlib.h>
#include "gameEngine.h"
#include "graph/graph.h"
#include "touch.h"

#define NORMALSTATE 0
#define GAMEOVER -1
#define WON 1

#define COLSIZE 4
#define ROWSIZE 4
#define HERO_LIFE 5

struct spaceInvaders_dataBase
{
    uint8 invaderIDs[COLSIZE][ROWSIZE];
    uint8 colSize; 
    uint8 rowSize;
    uint8 rowIndex;
    uint8 nextCmd;
    uint8 step;
    uint8 count;
    
    int8 lastSteps;
    uint8 lastdir;
    int16 X_win_line;
};

struct Player_dataBase
{
    uint8 PlayerID;
    int16 X_lock;
    int16 Y_min;
    int16 Y_max;
    uint8 reloadCountDown;
};

int8 spaceInvaders_init(struct GameEngine * engine, struct spaceInvaders_dataBase * db, uint16 level);
int8 spaceInvaders_algoritme(struct GameEngine * engine, struct spaceInvaders_dataBase * db);
int8 Player_init(struct GameEngine * engine, struct Player_dataBase * db, uint8 lifes);
int8 Player_algoritme(struct GameEngine * engine, struct Player_dataBase * db, int16 Ypos, uint8 fire);
int8 gameStatus(struct GameEngine * engine, int8 spaceInvadersStatus, int8 PlayerStatus);

void spaceInavader_start()
{
    int16 YposAVG[8] = {0};
    int16 YposAVGSUM;
    uint8 YposAVG_ptr = 0, SUM_i;
    int8 status;
    uint8 HeroLifes = HERO_LIFE;
    uint16 level = 0;
    
    srand(322);
    uint8 i,i2, statusSI, statusP;
    
    uint16 Y_controller, X_controller;
    //int16 Y_sim_controller_delta = 0, count_sim = 0;
    uint8 press, trig;
    
    struct Player_dataBase player_db;
    struct spaceInvaders_dataBase spaceInvaders_db;
    
    struct Color col[5];
    struct Color Bgcol[5];
    struct SubjectFactory factory;
    struct GameEngine engine;
    int delta = 5;
    int yPos = 320/2;
    int heroID;
    struct coord pos;
    
    int Invaders_col1[4][4];
    
    for(i = 0; i < 5; i++)
    {
        col[i].R = 0;
        col[i].G = 255;
        col[i].B = 0;
        Bgcol[i].R = 0;
        Bgcol[i].G = 0;
        Bgcol[i].B = 0;
    }
    
    Touch_init();
    
    Timer_1_Start();
    while(1)
    {
    SubjectFactory_init(&factory, GRAPHS, GRAPH_SIZEXS, GRAPH_SIZEYS, GRAPH_NAMES, col, Bgcol, GRAPH_length);
    
    GameEngine_init(&engine, &factory, (level == 0? 0u : 1u));
    
    spaceInvaders_init(&engine, &spaceInvaders_db, level);
    
    Player_init(&engine, &player_db, HeroLifes);
    
    
    
        do
        {
            readTouch_better(&Y_controller,&X_controller, &press, &trig);
         
            YposAVG[YposAVG_ptr] = Y_controller;
            YposAVG_ptr = (YposAVG_ptr + 1) % 8;
            
            YposAVGSUM = 0;
            
            for(SUM_i = 0; SUM_i < 8; SUM_i++)
                YposAVGSUM += YposAVG[SUM_i];
                
            YposAVGSUM >>= 3;  
            
            statusP = Player_algoritme(&engine, &player_db,YposAVGSUM, trig);
            statusSI = spaceInvaders_algoritme(&engine, &spaceInvaders_db);
            status = gameStatus(&engine, statusSI, statusP);
            
            //CyDelay(16);
            engine.tick(&engine);
            while(TickControl_Read() == 0);
            
        }while(status == NORMALSTATE);
        
        if(status == WON)
        {
            HeroLifes = engine.lifeLeft(&engine, player_db.PlayerID);
            level++;
            engine.nextLevel(&engine);
        }
        else
        {
            engine.endGame(&engine);
            HeroLifes = HERO_LIFE;
            level = 0;
            
        }

    }
}


void spaceInavader_test()
{
    
    
    srand(321);
    unsigned i,i2;
    struct Color col[5];
    struct Color Bgcol[5];
    struct SubjectFactory factory;
    struct GameEngine engine;
    int delta = 5;
    int yPos = 320/2;
    int heroID;
    struct coord pos;
    
    int Invaders_col1[4][4];
    
    for(i = 0; i < 5; i++)
    {
        col[i].R = 0;
        col[i].G = 255;
        col[i].B = 0;
        Bgcol[i].R = 0;
        Bgcol[i].G = 0;
        Bgcol[i].B = 0;
    }
    
    SubjectFactory_init(&factory, GRAPHS, GRAPH_SIZEXS, GRAPH_SIZEYS, GRAPH_NAMES, col, Bgcol, GRAPH_length);
    
    GameEngine_init(&engine, &factory, 0);
    
    heroID = engine.spawn(&engine, "Hero", Player, 0, 450, yPos, 3);
    for(i = 0; i < 4; i++)
    {
        for(i2 = 0; i2 < 4; i2++)
        {
            Invaders_col1[i][i2] = engine.spawn(&engine, "space_invader", Enemies, 10, 50 + i*40, 20 + i2*50, 1);
        }
    }
    
    engine.shoot(&engine, heroID, UP, "shoot", 5);
    
    while(1)
    {
        
        for(i = 0; i < 4; i++)
        {
            for(i2 = 0; i2 < 4; i2++)
            {
                engine.move(&engine, Invaders_col1[i][i2], 1, 0, 1);
                if(rand() % 1000 > 998)
                {
                    engine.shoot(&engine, Invaders_col1[i][i2], DOWN, "invader_shoot", 2);
                }
            }
        }
        
        pos = engine.getPos(&engine, heroID);
        if(pos.Y >= 250)
            delta = -5;
        
        if(pos.Y <= 50)
            delta = 5;
        
        
        engine.move(&engine, heroID, 0, delta, 1);
        
        if(rand() % 100 > 95)
        {
            engine.shoot(&engine, heroID, UP, "shoot", 5);
        }
        
        //CyDelay(16);
        engine.tick(&engine);
    }
}



int8 spaceInvaders_init(struct GameEngine * engine, struct spaceInvaders_dataBase * db, uint16 level)
{
    const uint8 colSize = COLSIZE;
    const uint8 rowSize = ROWSIZE;
    uint8 i, i2;
    
    //db->invaderIDs = (uint8 **)malloc(sizeof(uint8[colSize*rowSize][rowSize]));
    
    for(i = 0; i < colSize; i++)
    {
        for(i2 = 0; i2 < rowSize; i2++)
        {
            db->invaderIDs[i][i2] = (uint8)engine->spawn(engine, "space_invader", Enemies, 10, 50 + i*40, 20 + i2*50, 1 + (level>>1));
        }
    }
    
    db->colSize = colSize;
    db->rowSize = rowSize;
    db->count = 0;
    db->step = 0;
    db->X_win_line = 440;
    db->nextCmd = 0;
    db->rowIndex = 0;
    db->lastSteps = -1;
    db->lastdir = 0;
    return NORMALSTATE;
}

void spaceInvaders_normal(struct GameEngine * engine, struct spaceInvaders_dataBase * db)
{
    uint8 i = 0;
    
    for(i = 0; i < db->rowSize; i++)
    {
        if(db->step < 10)
        {
            engine->move(engine, db->invaderIDs[db->rowIndex][i], 0, 10, 1);
            db->lastdir = 0;
        }
        else if(db->step < 15)
        {
            engine->move(engine, db->invaderIDs[db->rowIndex][i], 10, 0, 1);
            db->lastdir = 1;
        }
        else if(db->step < 25)
        {
            engine->move(engine, db->invaderIDs[db->rowIndex][i], 0, -10, 1);
            db->lastdir = 1;
        }
        else if(db->step < 30)
        {
            engine->move(engine, db->invaderIDs[db->rowIndex][i], 10, 0, 1);
            db->lastdir = 0;
        }
    }
}

void spaceInvaders_LastOne(struct GameEngine * engine, struct spaceInvaders_dataBase * db, uint8 lastRowIndex, uint8 lastColIndex)
{
    int16 Y;
    uint8 ID = db->invaderIDs[lastRowIndex][lastColIndex];
    
    if(engine->isDead(engine, ID))
        return;
    
    if(db->lastSteps == -1)
    {
        Y = engine->getPos(engine, ID).Y;
        
        if(0 <= Y && Y <= 50 && db->lastdir == 1)
        {
            db->lastSteps = 1;
             db->lastdir = 0;
        }
        else if(320-50 <= Y && Y <= 320 && db->lastdir == 0)
        {
            db->lastSteps = 1;
            db->lastdir = 1;
        }
        else
        {
            if(db->lastdir == 0)
                engine->move(engine, ID, 0, 10, 1);
            else
                engine->move(engine, ID, 0, -10, 1);
        }
        
        
    }
    else
    {
        engine->move(engine, ID, 10, 0, 1);
        db->lastSteps -= 1;
    }
    
    
}

int8 spaceInvaders_algoritme(struct GameEngine * engine, struct spaceInvaders_dataBase * db)
{
    uint8 alife, isdeadTmp, i, i2, hasWon;
    uint8 lastRowIndex = 0, lastColIndex = 0;
    uint8 alife_row[ROWSIZE] = {0};
    
    alife = 0;
    
    for(i = 0; i < db->rowSize; i++)
    {
        for(i2 = 0; i2 < db->colSize; i2++)
        {
            isdeadTmp = engine->isDead(engine, db->invaderIDs[i][i2]);
            alife += !isdeadTmp;
            alife_row[i] += !isdeadTmp;
            
            if(!isdeadTmp)
            {
                lastRowIndex = i;
                lastColIndex = i2;
            }
            
            if(engine->getPos(engine, db->invaderIDs[i][i2]).X >= db->X_win_line)
                return GAMEOVER;
            
            if(rand() % 1000 > 998)
            {
                engine->shoot(engine, db->invaderIDs[i][i2], DOWN, "invader_shoot", 3);
            }
        }
    }
    
    if(alife == 0)
    {
        return WON;
    }
    
    if(db->count == 0)
    {
        if(alife == 0)
        {
            return WON;
        }
        else if(alife == 1) //1
        {
            spaceInvaders_LastOne(engine, db, lastRowIndex, lastColIndex);
        }
        else
        {
            
            
            spaceInvaders_normal(engine, db); 
            
            do
            {
                db->rowIndex = (db->rowIndex + 1) % db->colSize;  
            }while(alife_row[db->rowIndex] == 0);
            if(db->rowIndex == 0)
            {
                db->step = (db->step + 1) % 30;   
            }
        }
    }
    
    db->count = (db->count + 1) % ((alife>>0) + 1);
    
    return NORMALSTATE;
}

int8 Player_init(struct GameEngine * engine, struct Player_dataBase * db, uint8 lifes)
{
    const int16 X_pos = 450;
    const int16 Y_min = 0+1;
    const int16 Y_max = 320-39-6;
    
    const int16 Y_start = (320/2) - (39/2);

    db->PlayerID = engine->spawn(engine, "Hero", Player, 0, X_pos, Y_start, lifes);
    
    db->reloadCountDown = 0;
    db->X_lock = X_pos;
    db->Y_max = Y_max;
    db->Y_min = Y_min;
    
    return NORMALSTATE;
}

int8 Player_algoritme(struct GameEngine * engine, struct Player_dataBase * db, int16 Ypos, uint8 fire)
{
    int Y_set;
    const int16 Y_off = -(39/2);
    
    if(engine->isDead(engine, db->PlayerID))
    {
        return GAMEOVER;   
    }
    
    if(db->reloadCountDown == 0 && fire)
    {
        engine->shoot(engine, db->PlayerID, UP, "shoot", 5);
        db->reloadCountDown = 40;
    }
    else if(db->reloadCountDown != 0)
    {
        db->reloadCountDown--;
    }

    
    if(Ypos + Y_off < db->Y_min)
    {
        Y_set = db->Y_min + Y_off;
    }
    else if(Ypos + Y_off > db->Y_max)
    {
        Y_set = db->Y_max + Y_off;   
    }
    else
    {
        Y_set = Ypos + Y_off;
    }
    
    engine->move(engine, db->PlayerID, db->X_lock, Y_set, 0);
    
    return NORMALSTATE;
}

int8 gameStatus(struct GameEngine * engine, int8 spaceInvadersStatus, int8 PlayerStatus)
{
    switch(spaceInvadersStatus)
    {
        case GAMEOVER:
        return GAMEOVER;
        case WON:
        return WON;
        
     case NORMALSTATE:   
        default:
        break;
    }
    
    switch(PlayerStatus)
    {
        case GAMEOVER:
        return GAMEOVER;
        case WON:
        return WON;
     case NORMALSTATE:   
        default:
        break;
    }
    return NORMALSTATE;
}

/* [] END OF FILE */
