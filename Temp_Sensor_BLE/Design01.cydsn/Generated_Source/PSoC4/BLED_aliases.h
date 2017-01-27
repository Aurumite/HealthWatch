/*******************************************************************************
* File Name: BLED.h  
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

#if !defined(CY_PINS_BLED_ALIASES_H) /* Pins BLED_ALIASES_H */
#define CY_PINS_BLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BLED_0			(BLED__0__PC)
#define BLED_0_PS		(BLED__0__PS)
#define BLED_0_PC		(BLED__0__PC)
#define BLED_0_DR		(BLED__0__DR)
#define BLED_0_SHIFT	(BLED__0__SHIFT)
#define BLED_0_INTR	((uint16)((uint16)0x0003u << (BLED__0__SHIFT*2u)))

#define BLED_INTR_ALL	 ((uint16)(BLED_0_INTR))


#endif /* End Pins BLED_ALIASES_H */


/* [] END OF FILE */
