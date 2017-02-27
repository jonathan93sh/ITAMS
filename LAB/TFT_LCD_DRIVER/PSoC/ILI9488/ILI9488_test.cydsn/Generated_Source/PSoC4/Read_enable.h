/*******************************************************************************
* File Name: Read_enable.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Read_enable_H) /* CY_CONTROL_REG_Read_enable_H */
#define CY_CONTROL_REG_Read_enable_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Read_enable_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Read_enable_Write(uint8 control) ;
uint8   Read_enable_Read(void) ;

void Read_enable_SaveConfig(void) ;
void Read_enable_RestoreConfig(void) ;
void Read_enable_Sleep(void) ; 
void Read_enable_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Read_enable_Control        (* (reg8 *) Read_enable_Sync_ctrl_reg__CONTROL_REG )
#define Read_enable_Control_PTR    (  (reg8 *) Read_enable_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Read_enable_H */


/* [] END OF FILE */
