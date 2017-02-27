/*******************************************************************************
* File Name: LCD_protected_RS.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LCD_protected_RS_ALIASES_H) /* Pins LCD_protected_RS_ALIASES_H */
#define CY_PINS_LCD_protected_RS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LCD_protected_RS_0			(LCD_protected_RS__0__PC)
#define LCD_protected_RS_0_PS		(LCD_protected_RS__0__PS)
#define LCD_protected_RS_0_PC		(LCD_protected_RS__0__PC)
#define LCD_protected_RS_0_DR		(LCD_protected_RS__0__DR)
#define LCD_protected_RS_0_SHIFT	(LCD_protected_RS__0__SHIFT)
#define LCD_protected_RS_0_INTR	((uint16)((uint16)0x0003u << (LCD_protected_RS__0__SHIFT*2u)))

#define LCD_protected_RS_INTR_ALL	 ((uint16)(LCD_protected_RS_0_INTR))


#endif /* End Pins LCD_protected_RS_ALIASES_H */


/* [] END OF FILE */
