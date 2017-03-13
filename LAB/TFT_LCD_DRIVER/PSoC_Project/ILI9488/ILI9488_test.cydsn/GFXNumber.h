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

struct GFXNumber
{
    struct GFXObject * GFX_number_objects_;
    uint8 length_;  
    void (*delete)(struct GFXNumber * this);
};

void init_NumberGFX(struct GFXNumber * this, uint16 Number, uint8 Ncharater, uint16 X, uint16 Y, struct GFXColor * col, struct GFXColor * bgCol);

#endif

/* [] END OF FILE */
