/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    cmp_user.c
* @brief   This file implements device driver for CMP module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "cmp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma clang diagnostic ignored "-Wunused-parameter"
extern void IRQ59_Handler(void);
extern void IRQ60_Handler(void);
extern void IRQ61_Handler(void);
extern void IRQ62_Handler(void);
void cmp0_interrupt(void);
void cmp1_interrupt(void);
void cmp2_interrupt(void);
void cmp3_interrupt(void);
void IRQ59_Handler(void) __attribute__((alias("cmp0_interrupt")));
void IRQ60_Handler(void) __attribute__((alias("cmp1_interrupt")));
void IRQ61_Handler(void) __attribute__((alias("cmp2_interrupt")));
void IRQ62_Handler(void) __attribute__((alias("cmp3_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint32_t g_Cmp0IntTaken;
volatile uint32_t g_Cmp1IntTaken;
volatile uint32_t g_Cmp2IntTaken;
volatile uint32_t g_Cmp3IntTaken;


/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: cmp0_interrupt
* @brief  CMP0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void cmp0_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP0_IRQn);     /* clear INTCMP0 interrupt flag */
    /* Start user code. Do not edit comment generated here */
    g_Cmp0IntTaken++;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: cmp1_interrupt
* @brief  CMP1 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void cmp1_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP1_IRQn);     /* clear INTCMP1 interrupt flag */
    /* Start user code. Do not edit comment generated here */
    g_Cmp1IntTaken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: cmp2_interrupt
* @brief  CMP2 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void cmp2_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP2_IRQn);     /* clear INTCMP2 interrupt flag */
    /* Start user code. Do not edit comment generated here */
    g_Cmp2IntTaken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: cmp3_interrupt
* @brief  CMP3 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void cmp3_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP3_IRQn);     /* clear INTCMP3 interrupt flag */
    /* Start user code. Do not edit comment generated here */
    g_Cmp3IntTaken++;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
