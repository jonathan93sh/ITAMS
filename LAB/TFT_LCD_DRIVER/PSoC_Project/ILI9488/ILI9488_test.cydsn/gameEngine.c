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
#include "gameEngine.h"

void GE_Game_add(struct Game * this, struct GameSubject* subject)
{
    if(this->subjectsSize_ > subjectLimit)
        return;
    
    this->subjects_[this->subjectsSize_] = subject;
    this->subjectsSize_++;
}


void GE_Game_tick(struct Game * this)
{
    
}


void GE_Game_shootFire(struct Game * this, struct GameSubject * shooter, struct graph_object * shell, enum Gdir dir);



void GE_Game_init(struct Game * game, void(*)(struct Game * this));
void GE_GameSubject_init(struct GameSubject * subject);
void GE_GamePlayer_init(struct GamePlayer * player);






/* [] END OF FILE */
