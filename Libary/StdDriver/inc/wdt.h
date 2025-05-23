/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    wdt.h
* @brief   This file implements device driver for WDT module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef WDT_H
#define WDT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern volatile uint32_t g_WdtIntTaken;   	/* WDT interrupt flag */
extern volatile uint32_t g_IWdtIntTaken;   	/* IWDT interrupt flag */
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void WDT_Restart(void);
void IWDT_Restart(void);
void WDT_INT_Init(void);
void IWDT_INT_Init(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
