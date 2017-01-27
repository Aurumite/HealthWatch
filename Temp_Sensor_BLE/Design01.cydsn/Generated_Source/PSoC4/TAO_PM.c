/*******************************************************************************
* File Name: TAO.c  
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
#include "TAO.h"

static TAO_BACKUP_STRUCT  TAO_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: TAO_Sleep
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
*  \snippet TAO_SUT.c usage_TAO_Sleep_Wakeup
*******************************************************************************/
void TAO_Sleep(void)
{
    #if defined(TAO__PC)
        TAO_backup.pcState = TAO_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            TAO_backup.usbState = TAO_CR1_REG;
            TAO_USB_POWER_REG |= TAO_USBIO_ENTER_SLEEP;
            TAO_CR1_REG &= TAO_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TAO__SIO)
        TAO_backup.sioState = TAO_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        TAO_SIO_REG &= (uint32)(~TAO_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: TAO_Wakeup
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
*  Refer to TAO_Sleep() for an example usage.
*******************************************************************************/
void TAO_Wakeup(void)
{
    #if defined(TAO__PC)
        TAO_PC = TAO_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            TAO_USB_POWER_REG &= TAO_USBIO_EXIT_SLEEP_PH1;
            TAO_CR1_REG = TAO_backup.usbState;
            TAO_USB_POWER_REG &= TAO_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TAO__SIO)
        TAO_SIO_REG = TAO_backup.sioState;
    #endif
}


/* [] END OF FILE */
