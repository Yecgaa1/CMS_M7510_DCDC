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
#include "sys_mcu_header.h"

/***************************************************************************/

/*************************************************
Description: Sys_VariableInit
Input      : 
Return     : 
Others     : 系统开机初始化
*************************************************/
void Sys_VariableInit(void)
{    
    UART0_Info.RXD_CRC_Init = 0xffff;//初始化CRC寄存器初始值
    UART0_Info.TXD_CRC_Init = 0xffff;//初始化CRC寄存器初始值

    CHG_PID_VBat.out_Max = 2;
    COM_Ctr_Info.PWM_Enable = 0;//开驱动使能信号
    
    COM_Ctr_Info.INTP3_Start_TimeVal    = 500;  //ms             
    COM_Ctr_Info.INTP3_Start_OK         = 0;    
    COM_Ctr_Info.INTP3_Start_Cnt        = 0;
                 
    COM_Ctr_Info.NO_Mode_OK_Cnt         = 0; 
    COM_Ctr_Info.NO_Mode_OK_TimeVal     = 40;    
    COM_Ctr_Info.PFC_Mode_OK_Cnt        = 0;
    COM_Ctr_Info.PFC_Mode_OK_TimeVal    = 150;
    COM_Ctr_Info.INV_Mode_OK_Cnt        = 0;
    COM_Ctr_Info.INV_Mode_OK_TimeVal    = 3;    
    DC_Ctrl_Info.mode                   = 0;//默认空闲模式
    
    DC_Ctrl_Info.SR_ON_LTime            = SR_ON_LTIME;//滞后x时间开通(lag time)
    DC_Ctrl_Info.SR_OFF_ATime           = SR_OFF_ATIME;//提前x时间关断(ahead time)    

    DC_Ctrl_Info.EPWM_Period            = DISC_PWM_PERIOD_INIT;
    
    DC_Ctrl_Info.EPWM_Duty_Max          = DISC_EPWM_DUTY_MAX;//工作周期值减去死区时间
    DC_Ctrl_Info.EPWM_Duty_Min          = DISC_EPWM_DUTY_MIN;//计算的占空比低于该阈值时，直接把占空比给定为0
    
    DC_Ctrl_Info.CHG_PFM_Fk             = CHG_PFM_K;
    DC_Ctrl_Info.CHG_PFM_Fb             = CHG_PFM_b;
    DC_Ctrl_Info.CHG_DTime              = CHG_DEADTIME;//充电死区时间
    DC_Ctrl_Info.DISC_DTime             = DISC_DEADTIME_WORK;
    AD_Correct_CHG_IBat.Flag.all        = 0;
    AD_Correct_DISC_IBat.Flag.all       = 0;    
    
    StartCheck_Flag_Info.all            = 0;
    System_ProtectFlag_Info.all         = 0;
    
    DC_Ctrl_Info.mode_Operate           = OPERATING_MODE;//开环or闭环   
    DC_Ctrl_Info.start_Finish_State     = COM_START_FINISH_STATE_NOK;//0-处于启机升压状态；1-处于正常工作状态
    DC_Ctrl_Info.INV_Ready_State        = COM_INV_READY_STATE_NOK;//0：逆变器未准备好;1：逆变器准备好
    

    DC_Ctrl_Info.AD_VBusFB_Val_Set      = PFM_AD_VBUS_FB_VAL_SET;//设定母线电压反馈控制阈值：低于该值时缓启完成，大于设定值正常使用采样值0~4095    
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set   = PFM_INV_VBUS_VOL_VAL_SET;//(与逆变侧传输的母线电压值比较)大于该母线电压值切换开关频率
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set2  = PFM_INV_VBUS_VOL_VAL_SET2;
    DC_Ctrl_Info.FRE_Switch_Cnt         = 0;//CHG频率切换计数
     
    CHG_Info.allow_VBat_Val             = COM_CHG_ALLOW_VBAT_VAL;//低于该电压清除充电完成标志

    CHG_Info.vBat_TC_Val        = COM_CHG_VBAT_TC_VAL;//涓流充电电池电压设定(低于该电压启用涓流充电)
    CHG_Info.iBat_TC_Val        = COM_CHG_IBAT_TC_VAL;//涓流充电电池电流设定(过放电使用) 
    CHG_Info.vBat_CC_CV_Val     = COM_CHG_VBAT_CC_CV_VAL;//恒流恒压充电模式切换的电池电压阈值设定 
    CHG_Info.vBat_CV_Val        = COM_CHG_VBAT_CV_VAL;//恒压充电电池电压设定(低于该电压启用恒流或涓流，高于该值启用恒压)  
    CHG_Info.iBat_CC_MaxVal     = COM_CHG_IBAT_CC_MAXVAL;//恒流充电电池电流最大值限制
    CHG_Info.iBat_CC1_Val       = COM_CHG_IBAT_CC1_VAL;//大恒流充电电池电流设定 
    CHG_Info.iBat_CC2_Val       = COM_CHG_IBAT_CC2_VAL;//小恒流充电电池电流设定 
    CHG_Info.vBat_FC_Val        = COM_CHG_VBAT_FC_VAL;//浮充充电电池电压设定 
    CHG_Info.iBat_FC_Val        = COM_CHG_IBAT_FC_VAL;//浮充充电电池电流设定(低于该电流启用浮充)   
    CHG_Info.finish_IBat_Val    = COM_CHG_FINISH_IBAT_VAL;//判断充电结束时电流值   

    CHG_Info.CC1_Flag           = 0;//大恒流充电时标记为1,0状态为涓流充电状态
    CHG_Info.CC2_Flag           = 0;//小恒流充电时标记为1
    CHG_Info.FC_Flag            = 0;//浮充电时标记为1    
    CHG_Info.CC1_Cnt            = 0;//大恒流延时计数
    CHG_Info.CC2_Cnt            = 0;//小恒流延时计数
    CHG_Info.finish_OK_Cnt      = 0;//充电结束延时计数      
    CHG_Info.finish_NOK_Cnt     = 0;//充电未完成延时计数    
    
    CHG_PID_IBat.out            = 0;
    CHG_PID_VBat.out            = 0;
    CHG_PID_VBat.ref            = 0;
    CHG_PID_IBat.ref            = 0;
    CHG_Info.vBat_Ref_Hold      = 0;
    CHG_Info.iBat_Ref_Hold      = 0;
    
    CHG_Info.finish_State       = COM_CHG_FINISH_NOK;
    CHG_Info.CV_FC_Cnt          = 0;//CV转FC充电计时 
    CHG_Info.CV_FC_Time         = COM_CHG_CV_FC_TIME;//CV转FC充电时间设置    
    CHG_Info.TC_Cnt             = 0;
    CHG_Info.TC_Time            = COM_CHG_TC_TIME;
    CHG_Info.Sec_Val            = CHG_EPWM_FREQ_MAX;//PWM中断秒时间生成的设定值
    CHG_Info.Sec_Cnt            = 0;//PWM中断秒时间生成的计数值
    
    //电压环开始充电时缓启动   
    CHG_Info.vBat_Ref_Step_Val      = COM_CHG_VBAT_REF_STEP_VALUE;//电压环软启动时，每次步进值       
    CHG_Info.vBat_Ref_Shift_Val     = COM_CHG_VBAT_REF_SHIFT_VALUE; //电压环软启动时缩放移位值 
    CHG_Info.vBat_Ref_Hold          = COM_CHG_VBAT_REF_HOLD_INIT;//电压环软启动时初始值  
    CHG_Info.vBat_Ref_SS            = 0;   

    //电流环开始充电时缓启动  
    CHG_Info.iBat_Ref_Period        = COM_CHG_IBAT_REF_PEIROD;//变占空比启机时，每次步进周期值(ms)
    CHG_Info.iBat_Ref_Step_Val      = COM_CHG_IBAT_REF_STEP_VALUE;//电流环软启动时，每次步进值       
    CHG_Info.iBat_Ref_Shift_Val     = COM_CHG_IBAT_REF_SHIFT_VALUE; //电流环软启动时缩放移位值 
    CHG_Info.iBat_Ref_Hold          = COM_CHG_IBAT_REF_HOLD_INIT;//电流环软启动时初始值  
    CHG_Info.iBat_Ref_SS            = CHG_Info.iBat_TC_Val;       
    CHG_Info.iBat_Ref_SS_Flag       = 0;//电流环缓启动标志
    
    //VBUS给定缓启动 
    CHG_Info.vBUS_Ref_Step_Val      = COM_CHG_VBUS_REF_STEP_VALUE;//VBUS给定缓启动时，每次步进值       
    CHG_Info.vBUS_Ref_Shift_Val     = COM_CHG_VBUS_REF_SHIFT_VALUE; //VBUS给定缓启动时缩放移位值 
    CHG_Info.vBUS_Ref_Hold          = COM_CHG_VBUS_REF_HOLD_INIT;//VBUS给定缓启动时初始值  
    CHG_Info.vBUS_Ref_SS            = CHG_Info.vBUS_Ref_Hold >> CHG_Info.vBUS_Ref_Shift_Val;   
    CHG_Info.out                    = 0;
    CHG_Info.vBUS_Set               = 0;
    
    CHG_Info.vBUS_Ref_Sum           = 0000;
}


/*************************************************
Description: Run_VariableInit
Input      : 
Return     : 
Others     : 从待机状态切换工作态变量初始化
*************************************************/
extern int32_t DISC_SS_Cnt;
void Run_VariableInit(void)
{        

    CHG_PID_VBat.out_Max    = 2;

    COM_Ctr_Info.PWM_Enable = 0;//开驱动使能信号
    DISC_SS_Cnt = 0;
    
    BAT_START_DISABLE;
    COM_Ctr_Info.INTP3_Start_TimeVal    = 500;  //ms             
    COM_Ctr_Info.INTP3_Start_OK         = 0;    
    COM_Ctr_Info.INTP3_Start_Cnt        = 0;
    
    DC_Ctrl_Info.EPWM_DutyB             = SR_MIN_TIME;
    DC_Ctrl_Info.EPWM_Duty              = SR_MIN_TIME;
    DC_Ctrl_Info.start_Finish_State     = COM_START_FINISH_STATE_NOK;//0-处于启机升压状态；1-处于正常工作状态
    DC_Ctrl_Info.INV_Ready_State        = COM_INV_READY_STATE_NOK;//0：逆变器未准备好;1：逆变器准备好

    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set2  = PFM_INV_VBUS_VOL_VAL_SET2;    
    DC_Ctrl_Info.AD_VBusFB_Val_Set      = PFM_AD_VBUS_FB_VAL_SET;//设定母线电压反馈控制阈值：低于该值将vBusFB_AD清零，大于设定值正常使用采样值0~4095    
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set   = PFM_INV_VBUS_VOL_VAL_SET;//(与逆变侧传输的母线电压值比较)大于该母线电压值切换开关频率
    DC_Ctrl_Info.FRE_Switch_Cnt         = 0;//CHG频率切换计数
    
    DC_Ctrl_Info.SR_ON_LTime          = SR_ON_LTIME;//滞后x时间开通(lag time)
    DC_Ctrl_Info.SR_OFF_ATime         = SR_OFF_ATIME;//提前x时间关断(ahead time)  
    DC_Ctrl_Info.DISC_SR_State        = DISC_SR_STATE;
    DC_Ctrl_Info.CHG_SR_State         = CHG_SR_STATE;
    
    DC_Ctrl_Info.CHG_PFM_Fk           = CHG_PFM_K;
    DC_Ctrl_Info.CHG_PFM_Fb           = CHG_PFM_b;
    DC_Ctrl_Info.CHG_DTime            = CHG_DEADTIME;//充电死区时间
    DC_Ctrl_Info.DISC_DTime           = DISC_DEADTIME_WORK;
    CHG_Info.out_AVG 				  = 0;
    CHG_Info.out_AVG_Hold 			  = 0;    
    if (DC_Ctrl_Info.mode == DC_DISCHARGE)//放电模式
    {

        DC_Ctrl_Info.mode_Starting        = DISC_STARTING_MODE;//启动方式：PWM或者PFM 

        DC_Ctrl_Info.EPWM_Duty_Max        = DISC_EPWM_DUTY_MAX;//工作周期值减去死区时间
        DC_Ctrl_Info.EPWM_Duty_Min        = DISC_EPWM_DUTY_MIN;//计算的占空比低于该阈值时，直接把占空比给定为0

        
        #if (DISC_STARTING_MODE == PWM_MODE)  //变占空比启动初始化 
            DC_Ctrl_Info.PWM_Duty_Step_Value      = DISC_PWM_DUTY_STEP_VALUE;//变频率启机时，每次步进值       
            DC_Ctrl_Info.PWM_Duty_Shift_Value     = DISC_PWM_DUTY_SHIFT_VALUE; //变频率启动时缩放移位值    
            DC_Ctrl_Info.EPWM_Duty_Hold           = DISC_PWM_DUTY_HOLD_INIT;//占空比初始值给定
            DC_Ctrl_Info.EPWM_Period              = DISC_PWM_PERIOD_INIT; 

        
            DC_Ctrl_Info.EPWM_Duty                = 0;    
        #else       //变频率启动初始化 
            DC_Ctrl_Info.PFM_Period_Step_Value   = DISC_PFM_PERIOD_STEP_VALUE;//变频率启机时，每次步进值       
            DC_Ctrl_Info.PFM_Period_Shift_Value  = DISC_PFM_PERIOD_SHIFT_VALUE; //变频率启动时缩放移位值
            DC_Ctrl_Info.EPWM_Period_Max     = DISC_PFM_PERIOD_MAX;//限制最大周期值，即限制最小开关频率
            DC_Ctrl_Info.EPWM_Period_Min     = DISC_PFM_PERIOD_MIN;//限制最小周期值，即限制最大开关频率
            DC_Ctrl_Info.EPWM_Period         = DISC_PFM_PERIOD_INIT;//设置启机时的周期值，即启机开关频率
            DC_Ctrl_Info.EPWM_Period_Work    = DISC_PFM_PERIOD_WORK;//设置正常工作时的周期值，即开关频率  
            DC_Ctrl_Info.EPWM_Period_Hold    = DISC_PFM_PERIOD_HOLD_INIT;//过程值 
            DC_Ctrl_Info.EPWM_Duty_Max_Start = DISC_PFM_DUTY_MAX_START;//启机时最大占空比限制：工作周期值减去死区时间    
            DC_Ctrl_Info.EPWM_Duty           = 0;        
        #endif 
    }        
    else if(DC_Ctrl_Info.mode == DC_CHARGE)//充电模式
    {         
        DC_Ctrl_Info.mode_Starting        = CHG_STARTING_MODE;//启动方式：PWM或者PFM  
        DC_Ctrl_Info.EPWM_Duty_Max        = CHG_EPWM_DUTY_MAX;//工作周期值减去死区时间
        DC_Ctrl_Info.EPWM_Duty_Min        = CHG_EPWM_DUTY_MIN;//计算的占空比低于该阈值时，直接把占空比给定为0
        
        #if (CHG_STARTING_MODE == PWM_MODE)  //变占空比启动初始化 
            DC_Ctrl_Info.PWM_Duty_Step_Value      = CHG_PWM_DUTY_STEP_VALUE;//变频率启机时，每次步进值       
            DC_Ctrl_Info.PWM_Duty_Shift_Value     = CHG_PWM_DUTY_SHIFT_VALUE; //变频率启动时缩放移位值    
            DC_Ctrl_Info.EPWM_Duty_Hold           = CHG_PWM_DUTY_HOLD_INIT;//占空比初始值给定
            DC_Ctrl_Info.EPWM_Period              = CHG_PWM_PERIOD_INIT;          
            DC_Ctrl_Info.EPWM_Duty                = 0;      
        #endif        
    } 

    CHG_Info.allow_VBat_Val     = COM_CHG_ALLOW_VBAT_VAL;//低于该电压清除充电完成标志

    CHG_Info.vBat_TC_Val        = COM_CHG_VBAT_TC_VAL;//涓流充电电池电压设定(低于该电压启用涓流充电)
    CHG_Info.iBat_TC_Val        = COM_CHG_IBAT_TC_VAL;//涓流充电电池电流设定(过放电使用) 
    CHG_Info.vBat_CC_CV_Val     = COM_CHG_VBAT_CC_CV_VAL;//恒流恒压充电模式切换的电池电压阈值设定 
    CHG_Info.vBat_CV_Val        = COM_CHG_VBAT_CV_VAL;//恒压充电电池电压设定(低于该电压启用恒流或涓流，高于该值启用恒压)  

    CHG_Info.iBat_CC_MaxVal     = COM_CHG_IBAT_CC_MAXVAL;//恒流充电电池电流最大值限制    
    CHG_Info.iBat_CC1_Val       = COM_CHG_IBAT_CC1_VAL;//大恒流充电电池电流设定 
    CHG_Info.iBat_CC2_Val       = COM_CHG_IBAT_CC2_VAL;//小恒流充电电池电流设定     
    CHG_Info.vBat_FC_Val        = COM_CHG_VBAT_FC_VAL;//浮充充电电池电压设定 
    CHG_Info.iBat_FC_Val        = COM_CHG_IBAT_FC_VAL;//浮充充电电池电流设定(低于该电流启用浮充)   
    CHG_Info.finish_IBat_Val    = COM_CHG_FINISH_IBAT_VAL;//判断充电结束时电流值   


    CHG_Info.CV_FC_Cnt          = 0;//CV转FC充电计时 
    CHG_Info.CV_FC_Time         = COM_CHG_CV_FC_TIME;//CV转FC充电时间设置
    CHG_Info.TC_Cnt             = 0;
    CHG_Info.TC_Time            = COM_CHG_TC_TIME;
    CHG_Info.Sec_Val            = CHG_EPWM_FREQ_MAX;//PWM中断秒时间生成的设定值
    CHG_Info.Sec_Cnt            = 0;//PWM中断秒时间生成的计数值
    
    CHG_Info.CC1_Flag           = 0;//大恒流充电时标记为1,0状态为涓流充电状态
    CHG_Info.CC2_Flag           = 0;//小恒流充电时标记为1
    CHG_Info.FC_Flag            = 0;//浮充电时标记为1 
    CHG_Info.CC1_Cnt            = 0;//大恒流延时计数
    CHG_Info.CC2_Cnt            = 0;//小恒流延时计数
    CHG_Info.finish_OK_Cnt      = 0;//充电结束延时计数      
    CHG_Info.finish_NOK_Cnt     = 0;//充电未完成延时计数      
    
    CHG_PID_IBat.out            = 0;
    CHG_PID_VBat.out            = 0;
    CHG_PID_VBat.ref            = 0;
    CHG_PID_IBat.ref            = 0;
    CHG_Info.vBat_Ref_Hold      = 0;
    CHG_Info.iBat_Ref_Hold      = 0;
    
    //电压环开始充电时缓启动   
    CHG_Info.vBat_Ref_Step_Val  = COM_CHG_VBAT_REF_STEP_VALUE;//电压环软启动时，每次步进值       
    CHG_Info.vBat_Ref_Shift_Val = COM_CHG_VBAT_REF_SHIFT_VALUE; //电压环软启动时缩放移位值 
    CHG_Info.vBat_Ref_Hold      = COM_CHG_VBAT_REF_HOLD_INIT;//电压环软启动时初始值  
    CHG_Info.vBat_Ref_SS        = 0;   

    //电流环开始充电时缓启动  
    CHG_Info.iBat_Ref_Step_Val  = COM_CHG_IBAT_REF_STEP_VALUE;//电流环软启动时，每次步进值       
    CHG_Info.iBat_Ref_Shift_Val = COM_CHG_IBAT_REF_SHIFT_VALUE; //电流环软启动时缩放移位值 
    CHG_Info.iBat_Ref_Hold      = COM_CHG_IBAT_REF_HOLD_INIT;//电流环软启动时初始值  
    CHG_Info.iBat_Ref_SS        = CHG_Info.iBat_TC_Val; 
    CHG_Info.iBat_Ref_SS_Flag   = 0;//电流环缓启动标志
    
    //VBUS给定缓启动 
    CHG_Info.vBUS_Ref_Step_Val  = COM_CHG_VBUS_REF_STEP_VALUE;//VBUS给定缓启动时，每次步进值       
    CHG_Info.vBUS_Ref_Shift_Val = COM_CHG_VBUS_REF_SHIFT_VALUE; //VBUS给定缓启动时缩放移位值 
    
    CHG_Info.vBUS_Ref_Hold      = COM_CHG_VBUS_REF_HOLD_INIT;//VBUS给定缓启动时初始值
    CHG_Info.vBUS_Ref_SS        = CHG_Info.vBUS_Ref_Hold >> CHG_Info.vBUS_Ref_Shift_Val;   
    CHG_Info.out                = 0; 
    CHG_Info.vBUS_Set           = 0;
    
    CHG_Info.vBUS_Ref_Sum       = 0;
}

/*-------------------------------------------------------------------------------------
 *  No more.
 *------------------------------------------------------------------------------------*/


