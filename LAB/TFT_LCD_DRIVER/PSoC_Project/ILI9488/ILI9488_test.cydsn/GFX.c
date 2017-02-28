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
#include "GFX.h"
#include "TFT_LCD.h"
enum color_enum {fg, bg};

void GFX_print(struct graph_object * this);
void GFX_remove(struct graph_object * this, char lastPos);

void GFX_init(struct graph_object * this, struct GFX_Pos pos, struct Color color, struct Color Bgcolor, uint8 * graph_tex)
{
	this->pos_ = pos;
    this->last_pos_ = pos;
    this->color_ = color;
    this->BgColor_ = Bgcolor;
    this->graph_tex_ = graph_tex;
    
    GFX_print(this);
}

void GFX_delete(struct graph_object * this)
{
    GFX_remove(this, 0);
}

void GFX_setPos(struct graph_object * this, uint16 pos_X, uint16 pos_Y)
{
    this->last_pos_ = this->pos_;
	this->pos_.pos_X_ = pos_X;
    this->pos_.pos_Y_ = pos_Y;
    GFX_remove(this, 1);
    GFX_print(this);
}

void GFX_rmove_shadow(struct graph_object * this)
{

}

void GFX_remove(struct graph_object * this, char lastPos)
{
    
    if(lastPos)
    {
        TFT_setWindow(this->last_pos_.pos_X_, 
            this->last_pos_.pos_X_ + this->last_pos_.size_X_-1, 
            this->last_pos_.pos_Y_, 
            this->last_pos_.pos_Y_ + this->last_pos_.size_Y_-1);
    }
    else
    {
        TFT_setWindow(this->pos_.pos_X_, 
            this->pos_.pos_X_ + this->pos_.size_X_-1, 
            this->pos_.pos_Y_, 
            this->pos_.pos_Y_ + this->pos_.size_Y_-1);
    }

    TFT_start_print();
    TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, this->pos_.size_X_ * this->pos_.size_Y_); 
    TFT_end_print();    
}

void GFX_print(struct graph_object * this)
{
    uint8 color_value = bg;
    uint8 last_N = 1;
    uint8 * Graph = this->graph_tex_;
    TFT_setWindow(this->pos_.pos_X_, 
        this->pos_.pos_X_ + this->pos_.size_X_-1, 
        this->pos_.pos_Y_, 
        this->pos_.pos_Y_ + this->pos_.size_Y_-1);
    

    TFT_start_print();
    
    while(1)
    {
        if(last_N == 0 && *Graph == 0)
        {
            break;    
        }
        switch (color_value)
        {
            case fg:
                TFT_write_print(this->color_.R, this->color_.G, this->color_.B, *Graph);
                color_value = bg;
            break;
            case bg:
                TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, *Graph);
                color_value = fg;
            break;
            default:
                color_value = bg;
            break;
        }
        
        last_N = *Graph;
        Graph++;
    }
    
    TFT_end_print();
}

/* [] END OF FILE */
