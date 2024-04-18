/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp_user.c
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G439.h"
#include "intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma clang diagnostic ignored "-Wunused-parameter"
void IRQ3_Handler(void) __attribute__((alias("intp0_interrupt")));
void IRQ4_Handler(void) __attribute__((alias("intp1_interrupt")));
void IRQ5_Handler(void) __attribute__((alias("intp2_interrupt")));
void IRQ6_Handler(void) __attribute__((alias("intp3_interrupt")));
void IRQ7_Handler(void) __attribute__((alias("intp4_interrupt")));
void IRQ8_Handler(void) __attribute__((alias("intp5_interrupt")));
void IRQ9_Handler(void) __attribute__((alias("intp6_interrupt")));
void IRQ10_Handler(void) __attribute__((alias("intp7_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint32_t g_intp0Taken;  	/* INTP0 taken */
volatile uint32_t g_intp1Taken;  	/* INTP1 taken */
volatile uint32_t g_intp2Taken;  	/* INTP2 taken */
volatile uint32_t g_intp3Taken;  	/* INTP3 taken */
volatile uint32_t g_intp4Taken;  	/* INTP4 taken */
volatile uint32_t g_intp5Taken;  	/* INTP5 taken */
volatile uint32_t g_intp6Taken;  	/* INTP6 taken */
volatile uint32_t g_intp7Taken;  	/* INTP7 taken */
void intp0_interrupt(void);
void intp1_interrupt(void);
void intp2_interrupt(void);
void intp3_interrupt(void);
void intp4_interrupt(void);
void intp5_interrupt(void);
void intp6_interrupt(void);
void intp7_interrupt(void);


/***********************************************************************************************************************
* Function Name: intp0_interrupt
* @brief  INTP0 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp0_interrupt(void)
{
   
    PORT->PCLRC = 0x0800;   // PC11 output "L"
    NVIC_ClearPendingIRQ(INTP0_IRQn);
    g_intp0Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    PORT->PSETC = 0x0800;   // PC11 output "H"
}
/***********************************************************************************************************************
* Function Name: intp1_interrupt
* @brief  INTP1 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp1_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP1_IRQn);
    g_intp1Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp2_interrupt
* @brief  INTP2 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp2_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP2_IRQn);
    g_intp2Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp3_interrupt
* @brief  INTP3 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp3_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP3_IRQn);
    g_intp3Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp4_interrupt
* @brief  INTP4 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp4_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP4_IRQn);
    g_intp4Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp5_interrupt
* @brief  INTP5 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp5_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP5_IRQn);
    g_intp5Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp6_interrupt
* @brief  INTP6 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp6_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP6_IRQn);
    g_intp6Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp7_interrupt
* @brief  INTP7 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp7_interrupt(void)
{
    
    NVIC_ClearPendingIRQ(INTP7_IRQn);
    g_intp7Taken++;
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
