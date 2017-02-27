/*******************************************************************************
* File Name: DDR_DATA.h  
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

#if !defined(CY_CONTROL_REG_DDR_DATA_H) /* CY_CONTROL_REG_DDR_DATA_H */
#define CY_CONTROL_REG_DDR_DATA_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} DDR_DATA_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    DDR_DATA_Write(uint8 control) ;
uint8   DDR_DATA_Read(void) ;

void DDR_DATA_SaveConfig(void) ;
void DDR_DATA_RestoreConfig(void) ;
void DDR_DATA_Sleep(void) ; 
void DDR_DATA_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define DDR_DATA_Control        (* (reg8 *) DDR_DATA_Sync_ctrl_reg__CONTROL_REG )
#define DDR_DATA_Control_PTR    (  (reg8 *) DDR_DATA_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_DDR_DATA_H */


/* [] END OF FILE */
