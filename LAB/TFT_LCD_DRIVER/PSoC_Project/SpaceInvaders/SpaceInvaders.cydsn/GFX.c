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

enum color_enum {fg, bg};


void GFX_setPos(struct GFXObject * this, uint16 pos_X, uint16 pos_Y);
void GFX_refresh(struct GFXObject * this);
struct GFXPos GFX_getPos(struct GFXObject * this);
uint16 GFX_getPos_X(struct GFXObject * this);
uint16 GFX_getPos_Y(struct GFXObject * this);
void GFX_delete(struct GFXObject * this);


void GFX_print(struct GFXObject * this);
void GFX_remove(struct GFXObject * this, char lastPos);
void GFX_rmove_shadow(struct GFXObject * this);

void GFXObject_init(struct GFXObject * this, struct GFXPos pos, struct GFXColor color, struct GFXColor Bgcolor, const uint8 * graph_tex)
{
	this->pos_ = pos;
    this->last_pos_ = pos;
    this->color_ = color;
    this->BgColor_ = Bgcolor;
    this->graph_tex_ = graph_tex;
    
    this->delete = GFX_delete;
    this->getPos = GFX_getPos;
    this->getX = GFX_getPos_X;
    this->getY = GFX_getPos_Y;
    this->setPos = GFX_setPos;
    this->refresh = GFX_refresh;
    
    GFX_print(this);
}

void GFX_delete(struct GFXObject * this)
{
    GFX_remove(this, 0);
}

struct GFXPos GFX_getPos(struct GFXObject * this)
{
    return this->pos_;
}

uint16 GFX_getPos_X(struct GFXObject * this)
{
    return this->pos_.pos_X;
}

uint16 GFX_getPos_Y(struct GFXObject * this)
{
    return this->pos_.pos_Y;   
}


void GFX_setPos(struct GFXObject * this, uint16 pos_X, uint16 pos_Y)
{
    
    if(pos_X > SCREEN_SIZE_X || pos_Y > SCREEN_SIZE_Y)
        return;
    
    this->last_pos_ = this->pos_;
	this->pos_.pos_X = pos_X;
    this->pos_.pos_Y = pos_Y;
    GFX_print(this);
    GFX_rmove_shadow(this);
}

void GFX_refresh(struct GFXObject * this)
{
    GFX_print(this);
}

void GFX_rmove_shadow(struct GFXObject * this)
{
    uint16 xl,yl, x1l, y1l, x2l, y2l, x,y,x1,y1 ;
    int8 sector = -1; 
    xl = this->last_pos_.pos_X;
    yl = this->last_pos_.pos_Y;
    x1l = xl + this->last_pos_.size_X;
    y1l = yl + this->last_pos_.size_Y;
    
    x = this->pos_.pos_X;
    y = this->pos_.pos_Y;
    x1 = x + this->pos_.size_X;
    y1 = y + this->pos_.size_Y;
    
    y2l = yl;
    x2l = xl;
    if(yl <= y1 && y1 <= y1l)
    {
        y2l = y1;
        
        if(xl <= x1 && x1 <= x1l)
        {
            x2l = x1;
            sector = 0;
        }
        else if(xl <= x && x <= x1l)
        {
            x2l = x;
            sector = 1;
        }
    }
    else if(yl <= y && y <= y1l)
    {
        y2l = y;
        if(xl <= x1 && x1 <= x1l)
        {
            x2l = x1;
            sector = 2;
        }
        else if(xl <= x && x <= x1l)
        {
            x2l = x;
            sector = 3;
        }
    }
    
    if(sector != 0)
    {
        TFT_setWindow(xl, x2l, yl, y2l);
        TFT_start_print();
        TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, (x2l-xl+1)*(y2l-yl+1));
        TFT_end_print();
    }
    
    if(sector != 1)
    {
        TFT_setWindow(x2l, x1l, yl, y2l);
        TFT_start_print();
        TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, (x1l-x2l+1)*(y2l-yl+1));
        TFT_end_print();
    }
    
    if(sector != 2)
    {
        TFT_setWindow(xl, x2l, y2l, y1l);
        TFT_start_print();
        TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, (x2l-xl+1)*(y1l-y2l+1));
        TFT_end_print();
    }
    
    if(sector != 3)
    {
        TFT_setWindow(x2l, x1l, y2l, y1l);
        TFT_start_print();
        TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, (x1l-x2l+1)*(y1l-y2l+1));
        TFT_end_print();
    }
    
}

void GFX_remove(struct GFXObject * this, char lastPos)
{
    
    if(lastPos)
    {
        TFT_setWindow(this->last_pos_.pos_X, 
            this->last_pos_.pos_X + this->last_pos_.size_X-1, 
            this->last_pos_.pos_Y, 
            this->last_pos_.pos_Y + this->last_pos_.size_Y-1);
    }
    else
    {
        TFT_setWindow(this->pos_.pos_X, 
            this->pos_.pos_X + this->pos_.size_X-1, 
            this->pos_.pos_Y, 
            this->pos_.pos_Y + this->pos_.size_Y-1);
    }

    TFT_start_print();
    TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, this->pos_.size_X * this->pos_.size_Y); 
    TFT_end_print();    
}

void GFX_print(struct GFXObject * this)
{
    
    uint32 bitPos, size;
    const uint8 * Graph = this->graph_tex_;
    TFT_setWindow(this->pos_.pos_X, 
        this->pos_.pos_X + this->pos_.size_X-1, 
        this->pos_.pos_Y, 
        this->pos_.pos_Y + this->pos_.size_Y-1);
    
    size = this->pos_.size_X * this->pos_.size_Y;
    
    TFT_start_print();
    
    for(bitPos = 0;bitPos < size; bitPos++)
    {
        switch((Graph[bitPos/8]>>(bitPos % 8))&0b1)
        {
            case 0:
                TFT_write_print(this->BgColor_.R, this->BgColor_.G, this->BgColor_.B, 1);
                break;
            case 1:
                TFT_write_print(this->color_.R, this->color_.G, this->color_.B, 1);
                break;
            default:
            break;
        }
    }
    TFT_end_print();
    
}

/*
void GFX_print(struct GFXObject * this)
{
    uint8 color_value = bg;
    uint8 last_N = 1;
    uint8 * Graph = this->graph_tex_;
    TFT_setWindow(this->pos_.pos_X, 
        this->pos_.pos_X + this->pos_.size_X-1, 
        this->pos_.pos_Y, 
        this->pos_.pos_Y + this->pos_.size_Y-1);
    

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
*/
/* [] END OF FILE */
