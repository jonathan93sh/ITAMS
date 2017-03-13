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
#include "GFXNumber.h"
#include "graph/graph_num_fonts.h"
#include <stdio.h>
#include <stdlib.h>

void NumberGFX_delete(struct GFXNumber * this);

void init_NumberGFX(struct GFXNumber * this, uint16 Number, uint8 Ncharater, uint16 X, uint16 Y, struct GFXColor * col, struct GFXColor * bgCol)
{
    const uint8 Y_offset = number_0_Y;
    uint16 i, decimal, factor;
    struct GFXPos pos;
    
    pos.pos_X = X;
    pos.pos_Y = Y;
    pos.size_X = number_0_X;
    pos.size_Y = number_0_Y;
    
    this->delete = NumberGFX_delete;
    this->length_ = Ncharater;
    if(Ncharater == 0)
    {
        this->length_ = 0;
        this->GFX_number_objects_ = NULL;
    }
    
    
    
    this->GFX_number_objects_ = calloc(Ncharater, sizeof(struct GFXObject));
    
    if(this->GFX_number_objects_ == NULL)
        return;
    
    
    factor = 1;
    
    for(i = 0;i<Ncharater;i++)
    {
        decimal = (Number % (factor*10)) / factor;
        factor *= 10;
        
        GFXObject_init(&this->GFX_number_objects_[i], pos, *col, *bgCol, graph_num_fonts_GRAPHS[ decimal ]);
        
        pos.pos_Y+=Y_offset;
    }
    
}

void NumberGFX_delete(struct GFXNumber * this)
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
