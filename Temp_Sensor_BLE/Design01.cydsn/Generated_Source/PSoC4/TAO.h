/*******************************************************************************
* File Name: TAO.h  
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

#if !defined(CY_PINS_TAO_H) /* Pins TAO_H */
#define CY_PINS_TAO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TAO_aliases.h"


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
} TAO_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TAO_Read(void);
void    TAO_Write(uint8 value);
uint8   TAO_ReadDataReg(void);
#if defined(TAO__PC) || (CY_PSOC4_4200L) 
    void    TAO_SetDriveMode(uint8 mode);
#endif
void    TAO_SetInterruptMode(uint16 position, uint16 mode);
uint8   TAO_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TAO_Sleep(void); 
void TAO_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TAO__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TAO_DRIVE_MODE_BITS        (3)
    #define TAO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TAO_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TAO_SetDriveMode() function.
         *  @{
         */
        #define TAO_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TAO_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TAO_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TAO_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TAO_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TAO_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TAO_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TAO_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TAO_MASK               TAO__MASK
#define TAO_SHIFT              TAO__SHIFT
#define TAO_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TAO_SetInterruptMode() function.
     *  @{
     */
        #define TAO_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TAO_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TAO_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TAO_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TAO__SIO)
    #define TAO_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TAO__PC) && (CY_PSOC4_4200L)
    #define TAO_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TAO_USBIO_DISABLE              ((uint32)(~TAO_USBIO_ENABLE))
    #define TAO_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TAO_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TAO_USBIO_ENTER_SLEEP          ((uint32)((1u << TAO_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TAO_USBIO_SUSPEND_DEL_SHIFT)))
    #define TAO_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TAO_USBIO_SUSPEND_SHIFT)))
    #define TAO_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TAO_USBIO_SUSPEND_DEL_SHIFT)))
    #define TAO_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TAO__PC)
    /* Port Configuration */
    #define TAO_PC                 (* (reg32 *) TAO__PC)
#endif
/* Pin State */
#define TAO_PS                     (* (reg32 *) TAO__PS)
/* Data Register */
#define TAO_DR                     (* (reg32 *) TAO__DR)
/* Input Buffer Disable Override */
#define TAO_INP_DIS                (* (reg32 *) TAO__PC2)

/* Interrupt configuration Registers */
#define TAO_INTCFG                 (* (reg32 *) TAO__INTCFG)
#define TAO_INTSTAT                (* (reg32 *) TAO__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TAO_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TAO__SIO)
    #define TAO_SIO_REG            (* (reg32 *) TAO__SIO)
#endif /* (TAO__SIO_CFG) */

/* USBIO registers */
#if !defined(TAO__PC) && (CY_PSOC4_4200L)
    #define TAO_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TAO_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TAO_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TAO_DRIVE_MODE_SHIFT       (0x00u)
#define TAO_DRIVE_MODE_MASK        (0x07u << TAO_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TAO_H */


/* [] END OF FILE */
