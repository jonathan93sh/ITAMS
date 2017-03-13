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
#include "StartScreen.h"
#include "graph/graph_startScreen.h"
#include <stdio.h>
#include <stdlib.h>

void SS_delete(struct StartScreen * this);

void init_StartScreen(struct StartScreen * this)
{
    struct GFXPos pos;
    struct GFXColor col, bgcol;
    
    this->delete = SS_delete;
    
    this->GFX_ = calloc(graph_startScreen_GRAPH_length, sizeof(struct GFXObject));
    if(this->GFX_ == NULL)
    {
        this->length_ = 0;
        return;
    }
    this->length_ = graph_startScreen_GRAPH_length;
    // Place space big space invader.
    col.R = 0;
    col.G = 255;
    col.B = 255;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X = invader_front_big_X;
    pos.size_Y = invader_front_big_Y;
    
    pos.pos_X = 50;
    pos.pos_Y = (320/2) - (pos.size_Y/2);
    
    GFXObject_init(&this->GFX_[0], pos, col, bgcol, invader_front_big_GRAPH);
    // Place "SPACE"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X = space_X;
    pos.size_Y = space_Y;
    
    pos.pos_X = 200;
    pos.pos_Y = (320/2) - (pos.size_Y/2);
    
    GFXObject_init(&this->GFX_[1], pos, col, bgcol, space_GRAPH);
    // Place "INVADERS"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X = invaders_X;
    pos.size_Y = invaders_Y;
    
    pos.pos_X = 260;
    pos.pos_Y = (320/2) - (pos.size_Y/2);
    
    GFXObject_init(&this->GFX_[2], pos, col, bgcol, invaders_GRAPH);
    // Place "TAP TO PLAY"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X = tap_to_play_X;
    pos.size_Y = tap_to_play_Y;
    
    pos.pos_X = 425;
    pos.pos_Y = (320/2) - (pos.size_Y/2);
    
    GFXObject_init(&this->GFX_[3], pos, col, bgcol, tap_to_play_GRAPH);
}

void SS_delete(struct StartScreen * this)
{
    uint8 i;
    
    if(this->GFX_ == NULL || this->length_ == 0)
        return;
    
    for(i = 0; i < this->length_; i++)
    {
        this->GFX_[i].delete(&this->GFX_[i]);   
    }
    
    free(this->GFX_);
}

/* [] END OF FILE */
