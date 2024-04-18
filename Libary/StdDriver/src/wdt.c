/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    wdt.c
* @brief   This file implements device driver for WDT module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

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
* Function Name: WDT_INT_Init
* @brief  This function restarts the watchdog timer.
* @param  None
* @return None
***********************************************************************************************************************/
void WDT_INT_Init(void)
{
	NVIC_ClearPendingIRQ(WDT0_IRQn);
	NVIC_EnableIRQ(WDT0_IRQn);
}

/***********************************************************************************************************************
* Function Name: IWDT_INT_Init
* @brief  This function restarts the independent watchdog timer.
* @param  None
* @return None
***********************************************************************************************************************/
void IWDT_INT_Init(void)
{
	NVIC_ClearPendingIRQ(WDT1_IRQn);
	NVIC_EnableIRQ(WDT1_IRQn);
}

/***********************************************************************************************************************
* Function Name: WDT_Restart
* @brief  This function restarts the watchdog timer.
* @param  None
* @return None
***********************************************************************************************************************/
void WDT_Restart(void)
{
    WDT->WDTE = 0xACU;     /* restart watchdog timer */
}
/***********************************************************************************************************************
* Function Name: IWDT_Restart
* @brief  This function restarts the independent watchdog timer.
* @param  None
* @return None
***********************************************************************************************************************/
void IWDT_Restart(void)
{
    IWDT->WDTE = 0xACU;     /* restart watchdog timer */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
