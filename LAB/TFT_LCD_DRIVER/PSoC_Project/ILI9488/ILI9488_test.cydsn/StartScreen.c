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
    struct GFX_Pos pos;
    struct Color col, bgcol;
    
    this->delete = SS_delete;
    
    this->GFX_ = calloc(graph_startScreen_GRAPH_length, sizeof(struct graph_object));
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

    pos.size_X_ = invader_front_big_X;
    pos.size_Y_ = invader_front_big_Y;
    
    pos.pos_X_ = 50;
    pos.pos_Y_ = (320/2) - (pos.size_Y_/2);
    
    GFX_init(&this->GFX_[0], pos, col, bgcol, invader_front_big_GRAPH);
    // Place "SPACE"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X_ = space_X;
    pos.size_Y_ = space_Y;
    
    pos.pos_X_ = 200;
    pos.pos_Y_ = (320/2) - (pos.size_Y_/2);
    
    GFX_init(&this->GFX_[1], pos, col, bgcol, space_GRAPH);
    // Place "INVADERS"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X_ = invaders_X;
    pos.size_Y_ = invaders_Y;
    
    pos.pos_X_ = 260;
    pos.pos_Y_ = (320/2) - (pos.size_Y_/2);
    
    GFX_init(&this->GFX_[2], pos, col, bgcol, invaders_GRAPH);
    // Place "TAP TO PLAY"
    col.R = 255;
    col.G = 255;
    col.B = 0;

    bgcol.R = 0;
    bgcol.G = 0;
    bgcol.B = 0;

    pos.size_X_ = tap_to_play_X;
    pos.size_Y_ = tap_to_play_Y;
    
    pos.pos_X_ = 425;
    pos.pos_Y_ = (320/2) - (pos.size_Y_/2);
    
    GFX_init(&this->GFX_[3], pos, col, bgcol, tap_to_play_GRAPH);
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
