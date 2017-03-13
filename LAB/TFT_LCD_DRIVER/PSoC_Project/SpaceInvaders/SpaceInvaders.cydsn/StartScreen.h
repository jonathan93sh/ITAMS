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
/** 
 * Denne klasse bruges til at udskrive start skærmen for Space Invader.
 */
struct StartScreen
{
    struct GFXObject * GFX_;
    uint8 length_;
	/** Denne metode vil fjerne start skærmen igen. */
    void (*delete)(struct StartScreen * this);  
};
/** Bruges til at initialiser StartScreen */
void init_StartScreen(struct StartScreen * this);


/* [] END OF FILE */
