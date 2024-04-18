
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  £º
*****************************************************************************/

#ifndef  __USER_FUNCTION_H
#define  __USER_FUNCTION_H

#include "BAT32G439.h"


void User_LED_Deal(void);
void User_Key_Deal(void);
void DC_CloseDrive(void);
void COM_Function(void);
void User_DelayTime_us(uint32_t delay);
void User_DelayTime_ms(uint32_t delay);

#endif

