/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/

#include "sys_define_param.h"
#include "sys_struct.h"
#include "sys_define_config.h"
#include "sys_mcu_header.h"
/***************************************************************************/



/*------------------------------------------------------------------------------------*/
//过载变量定义
/*------------------------------------------------------------------------------------*/
Protect_Check_Var_t      COM_CHG_OLP1_Info 		        = { E_OLP,E_MAX,COM_CHG_OLP1_TIME,0,\
                                                            COM_CHG_OLP1_VAL ,COM_CHG_OLP1_VAL_BACK };

Protect_Check_Var_t      COM_CHG_OLP2_Info 		        = { E_OLP,E_MAX,COM_CHG_OLP2_TIME,0, \
                                                            COM_CHG_OLP2_VAL ,COM_CHG_OLP2_VAL_BACK };

Protect_Check_Var_t      COM_DISC_OLP1_Info 		    = { E_OLP,E_MAX,COM_DISC_OLP1_TIME,0,\
                                                            COM_DISC_OLP1_VAL ,COM_DISC_OLP1_VAL_BACK };

Protect_Check_Var_t      COM_DISC_OLP2_Info 		    = { E_OLP,E_MAX,COM_DISC_OLP2_TIME,0, \
                                                            COM_DISC_OLP2_VAL ,COM_DISC_OLP2_VAL_BACK };
/*------------------------------------------------------------------------------------*/
	
/*------------------------------------------------------------------------------------*/
//过载变量定义
/*------------------------------------------------------------------------------------*/
Protect_Check_Var_t      CHG_IBAT_OCP1_Info 		    = { E_IBAT_CHG_OCP,E_MAX,CHG_IBAT_OCP1_TIME,0,\
                                                            CHG_IBAT_OCP1_VAL ,CHG_IBAT_OCP1_VAL_BACK };

Protect_Check_Var_t      CHG_IBAT_OCP2_Info 		    = { E_IBAT_CHG_OCP,E_MAX,CHG_IBAT_OCP2_TIME,0, \
                                                            CHG_IBAT_OCP2_VAL ,CHG_IBAT_OCP2_VAL_BACK };

Protect_Check_Var_t      DISC_IBAT_OCP1_Info 		    = { E_IBAT_DISC_OCP,E_MAX,DISC_IBAT_OCP1_TIME,0,\
                                                            DISC_IBAT_OCP1_VAL ,DISC_IBAT_OCP1_VAL_BACK };

Protect_Check_Var_t      DISC_IBAT_OCP2_Info 		    = { E_IBAT_DISC_OCP,E_MAX,DISC_IBAT_OCP2_TIME,0, \
                                                            DISC_IBAT_OCP2_VAL ,DISC_IBAT_OCP2_VAL_BACK };
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//VREF参考电压异常变量定义
/*------------------------------------------------------------------------------------*/                                                            
Protect_Check_Var_t      COM_Vref_OVP_Info              = { E_VREF_ERR,E_MAX,COM_VREF_OVP_TIME,0,\
                                                            COM_VREF_OVP_VAL,COM_VREF_OVP_VAL_BACK };

Protect_Check_Var_t      COM_Vref_LVP_Info              = { E_VREF_ERR,E_MIN,COM_VREF_LVP_TIME,0,\
                                                            COM_VREF_LVP_VAL,COM_VREF_LVP_VAL_BACK };

/*------------------------------------------------------------------------------------*/
//辅助电源过欠压变量定义
/*------------------------------------------------------------------------------------*/	
Protect_Check_Var_t      COM_AuxPower_OVP_Info 	        = { E_AUX_POWER_OVP,E_MAX,COM_AUX_POWER_OVP_TIME,0,\
                                                            COM_AUX_POWER_OVP_VAL,COM_AUX_POWER_OVP_VAL_BACK };

Protect_Check_Var_t      COM_AuxPower_LVP_Info 	        = { E_AUX_POWER_LVP,E_MIN,COM_AUX_POWER_LVP_TIME,0,\
                                                            COM_AUX_POWER_LVP_VAL,COM_AUX_POWER_LVP_VAL_BACK };

                                                            
/*------------------------------------------------------------------------------------*/
//电池电压过欠压变量定义
/*------------------------------------------------------------------------------------*/	
Protect_Check_Var_t      COM_VBat_OVP_Info 	            = { E_VBAT_OVP,E_MAX,COM_VBAT_OVP_TIME,0,\
                                                            COM_VBAT_OVP_VAL,COM_VBAT_OVP_VAL_BACK };

Protect_Check_Var_t      COM_VBat_LVP1_Info 	        = { E_VBAT_LVP,E_MIN,COM_VBAT_LVP1_TIME,0,\
                                                            COM_VBAT_LVP1_VAL,COM_VBAT_LVP1_VAL_BACK };

Protect_Check_Var_t      COM_VBat_LVP2_Info 	        = { E_VBAT_LVP,E_MIN,COM_VBAT_LVP2_TIME,0,\
                                                            COM_VBAT_LVP2_VAL,COM_VBAT_LVP2_VAL_BACK };                                                            
/*------------------------------------------------------------------------------------*/
//过温变量定义
/*------------------------------------------------------------------------------------*/	
Protect_Check_Var_t      COM_OTP1_Info 	                = { E_OTP,E_MIN,COM_OTP1_TIME,0,\
                                                            COM_OTP1_VAL,COM_OTP1_VAL_BACK };		

Protect_Check_Var_t      COM_OTP2_Info 	                = { E_OTP,E_MIN,COM_OTP2_TIME,0,\
                                                            COM_OTP2_VAL,COM_OTP2_VAL_BACK };

/*------------------------------------------------------------------------------------*/
//开机启动条件检测变量定义
/*------------------------------------------------------------------------------------*/
Protect_Check_Var_t      COM_StartCheck_AuxPower_Up     = { E_START_CHECK_AUX_POWER_HIGH,E_MIN,COM_START_CHECK_AUX_POWER_UP_TIME,0,\
                                                            COM_START_CHECK_AUX_POWER_UP,COM_START_CHECK_AUX_POWER_UP_BACK };

Protect_Check_Var_t      COM_StartCheck_AuxPower_Down   = { E_START_CHECK_AUX_POWER_LOW,E_MAX,COM_START_CHECK_AUX_POWER_DOWN_TIME,0,\
                                                            COM_START_CHECK_AUX_POWER_DOWN,COM_START_CHECK_AUX_POWER_DOWN_BACK };	

Protect_Check_Var_t      COM_StartCheck_VBAT_Up         = { E_START_CHECK_VBAT_HIGH,E_MIN,COM_START_CHECK_VBAT_UP_TIME,0,\
                                                            COM_START_CHECK_VBAT_UP,COM_START_CHECK_VBAT_UP_BACK };

Protect_Check_Var_t      COM_StartCheck_VBAT_Down       = { E_START_CHECK_VBAT_LOW,E_MAX,COM_START_CHECK_VBAT_DOWN_TIME,0,\
                                                            COM_START_CHECK_VBAT_DOWN,COM_START_CHECK_VBAT_DOWN_BACK };	

Protect_Check_Var_t      COM_StartCheck_Temp_Up         = { E_START_CHECK_TEMP_HIGH,E_MAX,COM_START_CHECK_TEMP_UP_TIME,0,\
                                                            COM_START_CHECK_TEMP_UP,COM_START_CHECK_TEMP_UP_BACK };

/*------------------------------------------------------------------------------------*/
//AD采样校准定义
/*------------------------------------------------------------------------------------*/
AD_Correct_Var_t            AD_Correct_CHG_IBat         = {0,0,0,COM_CHG_IBat_AD_CORRECT_UP,COM_CHG_IBat_AD_CORRECT_MID,\
                                                            COM_CHG_IBat_AD_CORRECT_DN,COM_CHG_IBat_AD_CORRECT_MID};

AD_Correct_Var_t            AD_Correct_DISC_IBat        = {0,0,0,COM_DISC_IBat_AD_CORRECT_UP,COM_DISC_IBat_AD_CORRECT_MID,\
                                                            COM_DISC_IBat_AD_CORRECT_DN,COM_DISC_IBat_AD_CORRECT_MID};

AD_Correct_Var_t            AD_Correct_Vref             = {0,0,0,COM_VREF_AD_CORRECT_UP,COM_VREF_AD_CORRECT_MID,\
                                                            COM_VREF_AD_CORRECT_DN,COM_VREF_AD_CORRECT_MID};
                                                                                              
/*------------------------------------------------------------------------------------*/
//功率、AD采样变量定义
/*------------------------------------------------------------------------------------*/																												                                            
ADSample_Var_t              ADSample_Info               = {0}; 


/*------------------------------------------------------------------------------------*/
//按键检测变量定义
/*------------------------------------------------------------------------------------*/
Key_Var_t          	        Key_SW_ShutDown		        = {0,0,0,0,COM_KEY_SHUT_DOWN_ACTIVE_LEVEL,COM_KEY_SHUT_DOWN_C_DELAY_COUNT,COM_KEY_SHUT_DOWN_R_DELAY_COUNT,(void (*)( unsigned int ))Key_Calc};
Key_Var_t	                Key_Pro_Reset  			    = {0,0,0,0,COM_KEY_RESET_ACTIVE_LEVEL,COM_KEY_RESET_C_DELAY_COUNT,COM_KEY_RESET_R_DELAY_COUNT,(void (*)( unsigned int ))Key_Calc};


/*------------------------------------------------------------------------------------*/
//系统MS时基变量定义
/*------------------------------------------------------------------------------------*/
SysClockBase_t              SysClockBase_ms;


/*------------------------------------------------------------------------------------*/
//系统保护、自检变量定义
/*------------------------------------------------------------------------------------*/																												
StartCheck_Flag_u           StartCheck_Flag_Info    = {0};
System_Protect_Flag_u       System_ProtectFlag_Info = {0};		


/*------------------------------------------------------------------------------------*/
//控制变量定义
/*------------------------------------------------------------------------------------*/
CHG_Var_t               CHG_Info;
DC_Ctrl_Var_t           DC_Ctrl_Info;
PID_Ctrl_Var_t          CHG_PID_VBat                = CHG_VBAT_LOOP_DEFAULTS; 
PID_Ctrl_Var_t          CHG_PID_IBat                = CHG_IBAT_LOOP_DEFAULTS; 

/*------------------------------------------------------------------------------------*/
//UARTx心跳监测变量定义
/*------------------------------------------------------------------------------------*/
UARTx_Var_t             UART0_Info                  = {0,1,0,0,UART0_HEART_VAL,{0},{0},{0},{0},0,UART0_SEND_PERIOD_VAL,0xffff,0xffff,0,0,0,0,0,0,0};


/*------------------------------------------------------------------------------------*/
//COM控制变量定义
/*------------------------------------------------------------------------------------*/
COM_Ctr_Var_t		    COM_Ctr_Info        = {0}; 

LED_Ctr_Var_t		    LED_Ctr_Info        = {0}; 

InvToDC_Data_Var_t		InvToDC_Data_Info   = {0};

DcToMC_Data_Var_t		DcToMC_Data_Info    = {0};

COM_AD_Data_Var_t		COM_AD_Data_Info    = {0}; 

BMS_Order_Var_t		    BMS_Order_Info      = {0};
/*------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
