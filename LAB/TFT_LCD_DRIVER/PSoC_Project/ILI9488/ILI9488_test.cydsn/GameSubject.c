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

#include "GameSubject.h"

void GameSubject_init(struct GameSubject * this, uint8 * graph_tex, uint16 sizeX, uint16 sizeY, struct Color color, struct Color BgColor, uint16 X, uint16 Y, int8 lives, int16 killPoints,  uint8 ID, int8 TeamID)
{
    
    struct GFX_Pos pos;
    
    pos.pos_X_ = X;
    pos.pos_Y_ = Y;
    pos.size_X_ = sizeX;
    pos.size_Y_ = sizeY;
    
    GFX_init(&this->graph_, pos, color, BgColor, graph_tex);
    
    this->X_ = X;
    this->Y_ = Y;
    this->ID_ = ID;
    this->TeamID_ = TeamID;
    this->killPoints_ = killPoints;
    this->lives_ = lives;
}

/* [] END OF FILE */
