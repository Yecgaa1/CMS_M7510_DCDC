/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    elc.c
* @brief   This file implements device driver for ELC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "elc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: ELC_Start
* @brief  This function initializes the ELC module.
* @param  event_src - event resources number to be start (Set value for ELSR00-32)
* @param  event_dst - event destination number to be start (register of ELSR00-32)
* @return None
***********************************************************************************************************************/
void ELC_Start(elc_event_link_destination_t event_dst, elc_event_source_t event_src)
{
    ELC->ELCR = ELC_ELCR_ELCON_EN;
    // ELSRn(n=00~32) = Link Destination Number
    *(&ELC->ELSR00 + event_dst) = event_src;
}

/***********************************************************************************************************************
* Function Name: ELC_Stop
* @brief  This function stops the ELC event resources.
* @param  event_dst - event destination number to be start (register of ELSR00-32)
* @return None
***********************************************************************************************************************/
void ELC_Stop(elc_event_link_destination_t event_dst)
{
    // ELSRn(n=00~32) = Link Destination Number
    *(&ELC->ELSR00 + event_dst) = ELC_EVENT_LINK_OFF;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
