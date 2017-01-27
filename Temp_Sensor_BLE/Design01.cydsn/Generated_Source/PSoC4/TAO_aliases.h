/*******************************************************************************
* File Name: TAO.h  
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

#if !defined(CY_PINS_TAO_ALIASES_H) /* Pins TAO_ALIASES_H */
#define CY_PINS_TAO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TAO_0			(TAO__0__PC)
#define TAO_0_PS		(TAO__0__PS)
#define TAO_0_PC		(TAO__0__PC)
#define TAO_0_DR		(TAO__0__DR)
#define TAO_0_SHIFT	(TAO__0__SHIFT)
#define TAO_0_INTR	((uint16)((uint16)0x0003u << (TAO__0__SHIFT*2u)))

#define TAO_INTR_ALL	 ((uint16)(TAO_0_INTR))


#endif /* End Pins TAO_ALIASES_H */


/* [] END OF FILE */
