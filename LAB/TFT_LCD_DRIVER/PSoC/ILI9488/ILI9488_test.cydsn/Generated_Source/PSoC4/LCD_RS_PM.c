/*******************************************************************************
* File Name: LCD_RS_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_RS.h"

/* Check for removal by optimization */
#if !defined(LCD_RS_Sync_ctrl_reg__REMOVED)

static LCD_RS_BACKUP_STRUCT  LCD_RS_backup = {0u};

    
/*******************************************************************************
* Function Name: LCD_RS_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_RS_SaveConfig(void) 
{
    LCD_RS_backup.controlState = LCD_RS_Control;
}


/*******************************************************************************
* Function Name: LCD_RS_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void LCD_RS_RestoreConfig(void) 
{
     LCD_RS_Control = LCD_RS_backup.controlState;
}


/*******************************************************************************
* Function Name: LCD_RS_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_RS_Sleep(void) 
{
    LCD_RS_SaveConfig();
}


/*******************************************************************************
* Function Name: LCD_RS_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_RS_Wakeup(void)  
{
    LCD_RS_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
