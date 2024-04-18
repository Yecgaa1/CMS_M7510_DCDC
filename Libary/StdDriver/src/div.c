/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    div.c
* @brief   This file implements device driver for hardware divider module.
* @version V1.0.0
* @date: 2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "div.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: DIV_Operation
* @brief  Perform Hardware division operation
* @param  dividend - the dividend of a division operation
* @param  divisor - the divisor of a division operation
* @param  p_quotient  - the quotient of a division operation
* @param  p_remainder - the remainder of a division operation
* @return None
***********************************************************************************************************************/
void DIV_Operation(uint32_t dividend, uint32_t divisor, uint32_t *p_quotient, uint32_t *p_remainder)
{
    DIV->DIVIDEND = dividend;
    DIV->DIVISOR  = divisor;
    while(DIV->STATUS & (1<<8));
    (*p_quotient)  = DIV->QUOTIENT;
    (*p_remainder) = DIV->REMAINDER;
}
