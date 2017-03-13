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

void GameSubject_init(struct GameSubject * this, const uint8 * graph_tex, const uint16 sizeX, const uint16 sizeY, struct GFXColor color, struct GFXColor BgColor, uint16 X, uint16 Y, int8 lives, int16 killPoints,  uint8 ID, int8 TeamID)
{
    
    struct GFXPos pos;
    
    pos.pos_X = X;
    pos.pos_Y = Y;
    pos.size_X = sizeX;
    pos.size_Y = sizeY;
    
    GFXObject_init(&this->graph_, pos, color, BgColor, graph_tex);
    
    this->X_ = X;
    this->Y_ = Y;
    this->ID_ = ID;
    this->TeamID_ = TeamID;
    this->killPoints_ = killPoints;
    this->lives_ = lives;
}

/* [] END OF FILE */
