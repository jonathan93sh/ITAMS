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
#include "numberPrint.h"
#include "graph/graph_numFont.h"
#include <stdio.h>
#include <stdlib.h>

void NumberGFX_delete(struct NumberGFX * this);

void init_NumberGFX(struct NumberGFX * this, uint16 Number, uint8 Ncharater, uint16 X, uint16 Y, struct Color * col, struct Color * bgCol)
{
    const uint8 Y_offset = number_0_Y;
    uint8 i, decimal, factor;
    struct GFX_Pos pos;
    
    pos.pos_X_ = X;
    pos.pos_Y_ = Y;
    pos.size_X_ = number_0_X;
    pos.size_Y_ = number_0_Y;
    
    this->delete = NumberGFX_delete;
    
    if(Number == 0)
    {
        this->length_ = 0;
        this->GFX_number_objects_ = NULL;
    }
    
    this->GFX_number_objects_ = calloc(Number, sizeof(struct graph_object));
    
    factor = 1;
    
    for(i = 0;i<Ncharater;i++)
    {
        decimal = (Number % (factor*10)) / factor;
        factor *= 10;
        
        GFX_init(&this->GFX_number_objects_[i], pos, *col, *bgCol, NUM_GRAPHS[ decimal ]);
        
        pos.pos_Y_+=Y_offset;
    }
    
}

void NumberGFX_delete(struct NumberGFX * this)
{
    uint8 i;
    
    if(this->length_ == 0 || this->GFX_number_objects_ == NULL)
        return;
    
    for(i = 0; i < this->length_; i++)
    {
        this->GFX_number_objects_[i].delete(&this->GFX_number_objects_[i]);
    }
    
    free(this->GFX_number_objects_); 
    
    this->GFX_number_objects_ = NULL;
    this->length_ = 0;
    
}

/* [] END OF FILE */
