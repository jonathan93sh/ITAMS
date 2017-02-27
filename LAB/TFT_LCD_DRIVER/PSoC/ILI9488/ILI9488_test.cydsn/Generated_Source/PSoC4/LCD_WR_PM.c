/*******************************************************************************
* File Name: LCD_WR.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LCD_WR.h"

static LCD_WR_BACKUP_STRUCT  LCD_WR_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LCD_WR_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LCD_WR_SUT.c usage_LCD_WR_Sleep_Wakeup
*******************************************************************************/
void LCD_WR_Sleep(void)
{
    #if defined(LCD_WR__PC)
        LCD_WR_backup.pcState = LCD_WR_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LCD_WR_backup.usbState = LCD_WR_CR1_REG;
            LCD_WR_USB_POWER_REG |= LCD_WR_USBIO_ENTER_SLEEP;
            LCD_WR_CR1_REG &= LCD_WR_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LCD_WR__SIO)
        LCD_WR_backup.sioState = LCD_WR_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LCD_WR_SIO_REG &= (uint32)(~LCD_WR_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LCD_WR_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LCD_WR_Sleep() for an example usage.
*******************************************************************************/
void LCD_WR_Wakeup(void)
{
    #if defined(LCD_WR__PC)
        LCD_WR_PC = LCD_WR_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LCD_WR_USB_POWER_REG &= LCD_WR_USBIO_EXIT_SLEEP_PH1;
            LCD_WR_CR1_REG = LCD_WR_backup.usbState;
            LCD_WR_USB_POWER_REG &= LCD_WR_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LCD_WR__SIO)
        LCD_WR_SIO_REG = LCD_WR_backup.sioState;
    #endif
}


/* [] END OF FILE */
