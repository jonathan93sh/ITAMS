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
#include "SpaceInvader.h"
#include "touch.h"

int main(void)
{

    //CyGlobalIntEnable; /* Enable global interrupts. */

    TFT_init();
    
    TFT_clear_screen(0, 0, 0);
    
    Touch_init();
        
    Timer_1_Start();
    
    spaceInavader_start();

    return 1;
}

/* [] END OF FILE */
