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
#include <project.h>
#include "GFX.h"

struct StartScreen
{
    struct graph_object * GFX_;
    uint8 length_;
    void (*delete)(struct StartScreen * this);  
};

void init_StartScreen(struct StartScreen * this);


/* [] END OF FILE */
