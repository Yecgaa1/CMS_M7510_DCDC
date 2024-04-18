/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    wdt_user.c
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
#pragma clang diagnostic ignored "-Wunused-parameter"
extern void IRQ1_Handler(void);
void  wdt_interrupt(void);
void IRQ1_Handler(void) __attribute__((alias("wdt_interrupt")));
extern void IRQ2_Handler(void);
void  iwdt_interrupt(void);
void IRQ2_Handler(void) __attribute__((alias("iwdt_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_WdtIntTaken;   	/* WDT interrupt flag */
volatile uint32_t g_IWdtIntTaken;   	/* WDT interrupt flag */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: wdt_interrupt
* @brief  WDT interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void  wdt_interrupt(void)
{
	WDT_Restart();
    /* Start user code. Do not edit comment generated here */
    g_WdtIntTaken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iwdt_interrupt
* @brief  IWDT interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void  iwdt_interrupt(void)
{
    IWDT_Restart();
    /* Start user code. Do not edit comment generated here */
    g_IWdtIntTaken++;
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
