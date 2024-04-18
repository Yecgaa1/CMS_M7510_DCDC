
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  £º
*****************************************************************************/

#ifndef __SYS_MCU_HEADER_H
#define	__SYS_MCU_HEADER_H

#include <math.h>
#include <stdint.h>
#include "BAT32G439.h"
#include "userdefine.h"

/************driver***************/
//#include "adc.h"
//#include "cmp.h"
//#include "gpio.h"
//#include "pga.h"
//#include "tim4.h"
//#include "timm.h"
#include "sci.h"
#include "dma.h"
#include "elc.h"
//#include "div.h"
//#include "wdt.h"
#include "app_gpt.h"
#include "app_adc.h"
#include "app_cmp.h"

/***************app****************/
#include "DC_ctrl.h"
#include "PID_ctrl.h"
#include "user_communication.h"
#include "sys_hardware_init.h"
#include "user_sample.h"
#include "sys_struct.h"
#include "sys_define_param.h"
#include "sys_define_config.h"

#endif 
