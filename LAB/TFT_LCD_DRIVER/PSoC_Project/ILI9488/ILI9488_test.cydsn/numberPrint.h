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

#ifndef NUMBERPRINT_H_
    #define NUMBERPRINT_H_
#include <project.h>
#include "GFX.h"

struct NumberGFX
{
    struct graph_object * GFX_number_objects_;
    uint8 length_;  
    void (*delete)(struct NumberGFX * this);
};

void init_NumberGFX(struct NumberGFX * this, uint16 Number, uint8 Ncharater, uint16 X, uint16 Y, struct Color * col, struct Color * bgCol);

#endif

/* [] END OF FILE */
