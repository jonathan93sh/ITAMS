/*******************************************************************************
* File Name: Read_enable_PM.c
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

#include "Read_enable.h"

/* Check for removal by optimization */
#if !defined(Read_enable_Sync_ctrl_reg__REMOVED)

static Read_enable_BACKUP_STRUCT  Read_enable_backup = {0u};

    
/*******************************************************************************
* Function Name: Read_enable_SaveConfig
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
void Read_enable_SaveConfig(void) 
{
    Read_enable_backup.controlState = Read_enable_Control;
}


/*******************************************************************************
* Function Name: Read_enable_RestoreConfig
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
void Read_enable_RestoreConfig(void) 
{
     Read_enable_Control = Read_enable_backup.controlState;
}


/*******************************************************************************
* Function Name: Read_enable_Sleep
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
void Read_enable_Sleep(void) 
{
    Read_enable_SaveConfig();
}


/*******************************************************************************
* Function Name: Read_enable_Wakeup
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
void Read_enable_Wakeup(void)  
{
    Read_enable_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
