/*******************************************************************************
* File Name: Read_enable.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Read_enable.h"

/* Check for removal by optimization */
#if !defined(Read_enable_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: Read_enable_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void Read_enable_Write(uint8 control) 
{
    Read_enable_Control = control;
}


/*******************************************************************************
* Function Name: Read_enable_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 Read_enable_Read(void) 
{
    return Read_enable_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
