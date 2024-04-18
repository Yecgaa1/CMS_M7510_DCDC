/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    hal_rng.c
* @brief   This file implements device driver for TRNG module.
* @version 1.0.0
* @date    2022/09/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "trng.h"

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
* Function Name: TRNG_Init
* @brief  Initializes the RNG module.
* @param  None
* @return None
***********************************************************************************************************************/
void TRNG_Init(trng_div_t div_cnt)
{
    /* Make sure TRNG Operation Clock under 4MHz! */
    MISC->TRNGCKS &= MISC_TRNGCKS_CKS_Msk;
    MISC->TRNGCKS = div_cnt;

    CGC->PERA |= CGC_PERA_TRNGEN_Msk; //TRNG CLK EN

    /* Enable the RNG generator */
    TRNG->SCR = TRNG_SCR_TRNGEN_Msk;
}

/***********************************************************************************************************************
* Function Name: TRNG_DeInit
* @brief  DeInitializes the RNG module.
* @param  None
* @return None
***********************************************************************************************************************/
void TRNG_DeInit(void)
{
    /* Disable the RNG generator */
    TRNG->SCR &= ~TRNG_SCR_TRNGEN_Msk;
    
    CGC->PERA &= ~CGC_PERA_TRNGEN_Msk; //TRNG CLK EN
}

/***********************************************************************************************************************
* Function Name: TRNG_GetRandomNumber
* @brief  Get RandomNumber.
* @param  None
* @return 32 bits RandomNumber
* @note   Generating a 32-bit random number seed takes approximately 112 µs.
***********************************************************************************************************************/
uint32_t TRNG_GetRandomNumber(void)
{
    uint32_t i, val;

    TRNG->SCR |= TRNG_SCR_TRNGST_Msk; 
    while((TRNG->SCR & TRNG_SCR_TRNGRDY_Msk) == 0) {}

    val = 0x00000000U;
    for (i=0; i<4; i++)
    {
        val = val << 8 | TRNG->SDR;
    }

    return val;
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
