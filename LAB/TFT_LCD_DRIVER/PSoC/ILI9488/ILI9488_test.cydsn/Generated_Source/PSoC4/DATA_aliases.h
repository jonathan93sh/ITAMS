/*******************************************************************************
* File Name: DATA.h  
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

#if !defined(CY_PINS_DATA_ALIASES_H) /* Pins DATA_ALIASES_H */
#define CY_PINS_DATA_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DATA_0			(DATA__0__PC)
#define DATA_0_PS		(DATA__0__PS)
#define DATA_0_PC		(DATA__0__PC)
#define DATA_0_DR		(DATA__0__DR)
#define DATA_0_SHIFT	(DATA__0__SHIFT)
#define DATA_0_INTR	((uint16)((uint16)0x0003u << (DATA__0__SHIFT*2u)))

#define DATA_1			(DATA__1__PC)
#define DATA_1_PS		(DATA__1__PS)
#define DATA_1_PC		(DATA__1__PC)
#define DATA_1_DR		(DATA__1__DR)
#define DATA_1_SHIFT	(DATA__1__SHIFT)
#define DATA_1_INTR	((uint16)((uint16)0x0003u << (DATA__1__SHIFT*2u)))

#define DATA_2			(DATA__2__PC)
#define DATA_2_PS		(DATA__2__PS)
#define DATA_2_PC		(DATA__2__PC)
#define DATA_2_DR		(DATA__2__DR)
#define DATA_2_SHIFT	(DATA__2__SHIFT)
#define DATA_2_INTR	((uint16)((uint16)0x0003u << (DATA__2__SHIFT*2u)))

#define DATA_3			(DATA__3__PC)
#define DATA_3_PS		(DATA__3__PS)
#define DATA_3_PC		(DATA__3__PC)
#define DATA_3_DR		(DATA__3__DR)
#define DATA_3_SHIFT	(DATA__3__SHIFT)
#define DATA_3_INTR	((uint16)((uint16)0x0003u << (DATA__3__SHIFT*2u)))

#define DATA_4			(DATA__4__PC)
#define DATA_4_PS		(DATA__4__PS)
#define DATA_4_PC		(DATA__4__PC)
#define DATA_4_DR		(DATA__4__DR)
#define DATA_4_SHIFT	(DATA__4__SHIFT)
#define DATA_4_INTR	((uint16)((uint16)0x0003u << (DATA__4__SHIFT*2u)))

#define DATA_5			(DATA__5__PC)
#define DATA_5_PS		(DATA__5__PS)
#define DATA_5_PC		(DATA__5__PC)
#define DATA_5_DR		(DATA__5__DR)
#define DATA_5_SHIFT	(DATA__5__SHIFT)
#define DATA_5_INTR	((uint16)((uint16)0x0003u << (DATA__5__SHIFT*2u)))

#define DATA_6			(DATA__6__PC)
#define DATA_6_PS		(DATA__6__PS)
#define DATA_6_PC		(DATA__6__PC)
#define DATA_6_DR		(DATA__6__DR)
#define DATA_6_SHIFT	(DATA__6__SHIFT)
#define DATA_6_INTR	((uint16)((uint16)0x0003u << (DATA__6__SHIFT*2u)))

#define DATA_7			(DATA__7__PC)
#define DATA_7_PS		(DATA__7__PS)
#define DATA_7_PC		(DATA__7__PC)
#define DATA_7_DR		(DATA__7__DR)
#define DATA_7_SHIFT	(DATA__7__SHIFT)
#define DATA_7_INTR	((uint16)((uint16)0x0003u << (DATA__7__SHIFT*2u)))

#define DATA_INTR_ALL	 ((uint16)(DATA_0_INTR| DATA_1_INTR| DATA_2_INTR| DATA_3_INTR| DATA_4_INTR| DATA_5_INTR| DATA_6_INTR| DATA_7_INTR))


#endif /* End Pins DATA_ALIASES_H */


/* [] END OF FILE */
