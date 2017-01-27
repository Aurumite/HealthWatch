/*******************************************************************************
* File Name: BLED.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BLED_H) /* Pins BLED_H */
#define CY_PINS_BLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BLED_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} BLED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BLED_Read(void);
void    BLED_Write(uint8 value);
uint8   BLED_ReadDataReg(void);
#if defined(BLED__PC) || (CY_PSOC4_4200L) 
    void    BLED_SetDriveMode(uint8 mode);
#endif
void    BLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   BLED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BLED_Sleep(void); 
void BLED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BLED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BLED_DRIVE_MODE_BITS        (3)
    #define BLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BLED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BLED_SetDriveMode() function.
         *  @{
         */
        #define BLED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BLED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BLED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BLED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BLED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BLED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BLED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BLED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BLED_MASK               BLED__MASK
#define BLED_SHIFT              BLED__SHIFT
#define BLED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BLED_SetInterruptMode() function.
     *  @{
     */
        #define BLED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BLED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BLED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BLED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BLED__SIO)
    #define BLED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BLED__PC) && (CY_PSOC4_4200L)
    #define BLED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BLED_USBIO_DISABLE              ((uint32)(~BLED_USBIO_ENABLE))
    #define BLED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BLED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BLED_USBIO_ENTER_SLEEP          ((uint32)((1u << BLED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define BLED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BLED_USBIO_SUSPEND_SHIFT)))
    #define BLED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define BLED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BLED__PC)
    /* Port Configuration */
    #define BLED_PC                 (* (reg32 *) BLED__PC)
#endif
/* Pin State */
#define BLED_PS                     (* (reg32 *) BLED__PS)
/* Data Register */
#define BLED_DR                     (* (reg32 *) BLED__DR)
/* Input Buffer Disable Override */
#define BLED_INP_DIS                (* (reg32 *) BLED__PC2)

/* Interrupt configuration Registers */
#define BLED_INTCFG                 (* (reg32 *) BLED__INTCFG)
#define BLED_INTSTAT                (* (reg32 *) BLED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BLED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BLED__SIO)
    #define BLED_SIO_REG            (* (reg32 *) BLED__SIO)
#endif /* (BLED__SIO_CFG) */

/* USBIO registers */
#if !defined(BLED__PC) && (CY_PSOC4_4200L)
    #define BLED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BLED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BLED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BLED_DRIVE_MODE_SHIFT       (0x00u)
#define BLED_DRIVE_MODE_MASK        (0x07u << BLED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BLED_H */


/* [] END OF FILE */
