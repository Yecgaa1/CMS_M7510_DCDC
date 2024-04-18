
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  £º
*****************************************************************************/

#ifndef  __USER_SAMPLE_H
#define  __USER_SAMPLE_H

#include "BAT32G439.h"
#include "sys_hardware_init.h"
#include "sys_struct.h"

void AD_CorrectInit(void); 
void COM_SampleAD_Deal(void);
void COM_Vref_Sample(void);
void DISC_Altern_Sample(void);
void CHG_Altern_Sample(void);
void COM_VBat_Sample(void);
void CHG_IBat_Sample(void);
void DISC_IBat_Sample(void);
void COM_TempNTC_Sample(void);
void COM_AuxPowerSample(void);
void DISC_VBusFB_Sample(void);					
void COM_Get_Protect_Flag( int Check_Value, Protect_Check_Var_t * Check_Info,unsigned short int* protect_code );
#endif


