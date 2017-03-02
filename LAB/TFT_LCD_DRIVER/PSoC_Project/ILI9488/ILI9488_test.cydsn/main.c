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
#include "project.h"
#include "TFT_LCD.h"
#include "GFX.h"

uint8 test_[] = {5, 5, 5, 5, 5, 5, 1, 2, 3, 100, 23, 0, 23,34,20,100,12,32,34, 0, 0};

uint8 space[] = {
192, 1, 0, 7, 128, 3, 0, 14, 0, 7, 0, 28, 0, 112, 0, 7, 0, 224, 0, 14, 0, 192, 1, 28, 0, 240, 255, 255, 1, 224, 255, 255, 3, 192, 255, 255, 7, 240, 227, 63, 126, 224, 199, 127, 252, 192, 143, 255, 248, 241, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 31, 255, 255, 31, 63, 254, 255, 63, 126, 252, 255, 127, 252, 56, 0, 224, 248, 113, 0, 192, 241, 227, 0, 128, 227, 0, 126, 252, 0, 0, 252, 248, 1, 0, 248, 241, 3, 0, 0
};

int main(void)
{
    uint16 X=50;
    uint16 Y=50;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    
    struct graph_object test;
    struct GFX_Pos pos;
    
    pos.pos_X_ = 50;
    pos.pos_Y_ = 50;
    pos.size_X_ = 27;
    pos.size_Y_ = 33;
    
    struct Color col;
    
    col.R = 255;
    col.G = 0;
    col.B = 255;
    
    struct Color Bgcol;
    
    Bgcol.R = 0;
    Bgcol.G = 0;
    Bgcol.B = 0;
    
    
    
    TFT_init();
    
    TFT_clear_screen(0, 0, 0);
    
    //TFT_test();
    
    GFX_init(&test, pos, col, Bgcol, space);
    
    
    
    for(;;)
    {
        
        
        for(Y=50; Y<320-50; Y++)
        {
            //CyDelay(10);
            test.setPos(&test, (test.getX(&test)), Y);
        }
        for(X=0; X<50; X++)
        {
            //CyDelay(10);
            test.setPos(&test, (test.getX(&test) + 1) % (480-50), test.getY(&test));
        }
        
        for(; Y>50; Y--)
        {
            //CyDelay(10);
            test.setPos(&test, (test.getX(&test)), Y);
        }
        for(X=0; X<50; X++)
        {
            //CyDelay(10);
            test.setPos(&test, (test.getX(&test) + 1) % (480-50), test.getY(&test));
        }
        
        
        

        /* Place your application code here. */
    }
}

/* [] END OF FILE */
