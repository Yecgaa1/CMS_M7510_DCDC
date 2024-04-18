/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

#ifndef __DC_CTRL_H
#define __DC_CTRL_H

#include "stdint.h"

//----------------------------------------------------------------------------------------------
typedef struct
{
        int8_t      mode; //0：放电模式；1：充电模式   
        int16_t     EPWM_Period_Max;    //限制最大周期值，即限制最小开关频率
        int16_t     EPWM_Period_Min;    //限制最小周期值，即限制最大开关频率
        int32_t     EPWM_Period;        //实时更新的频率

    
        int32_t     EPWM_Period_Work;   //设定的工作频率     
        int32_t     EPWM_Period_Hold;  
        int16_t     EPWM_Duty_Max_Start;//启机时最大占空比限制阈值
        int16_t     EPWM_Duty_Max;  //正常工作时最大占空比限制阈值
        int16_t     EPWM_Duty_Min;  //最小占空比限制阈值   
        int32_t     EPWM_Duty;      //实时更新占空比
        int32_t     EPWM_Duty_temp;            
        int32_t     EPWM_DutyB;      //实时更新占空比    
        int32_t     EPWM_Duty_Calc;
        int32_t     EPWM_Duty_Hold; 
        int16_t     CHG_PFM_Fk;
        int16_t     CHG_PFM_Fb;
        int16_t     CHG_DTime;//充电死区时间
        int16_t     DISC_DTime;
        int16_t     vBus_Check_Val;     //逆变器MOS自检时限制的母线电压设定值 
        int8_t      INV_Ready_State;    //0：逆变器未准备好;1：逆变器准备好
        int8_t      INV_Ready_OK_Cnt;    //逆变器准备好延时计数
        int8_t      INV_Ready_NOK_Cnt;    //逆变器未准备好延时计数
    
        int8_t      start_Finish_State; //0-处于启机升压状态；1-处于正常工作状态
        int8_t      ZIF_PIF_State;  //1-处于周期点中断；0-处于过零点中断
        int8_t      mode_Operate;   //开环or闭环
        int8_t      mode_Starting;  //启动方式：PWM或者PFM
        int16_t     FRE_Switch_Cnt;   //CHG频率切换计数
        int16_t     AD_VBusFB_Val_Set;//设定母线电压反馈控制阈值：低于该值将vBusFB_AD清零，大于设定值正常使用采样值0~4095    
        int16_t     INV_vBus_Vol_VAL_Set;//(与逆变侧传输的母线电压值比较)大于该母线电压值切换开关频率
        int16_t     INV_vBus_Vol_VAL_Set2;
        int16_t     PFM_Period_Step_Value;//变频率启机时，每次步进值       
        int8_t      PFM_Period_Shift_Value; //变频率启动时缩放移位值      
        int16_t     PWM_Duty_Step_Value;//变频率启机时，每次步进值       
        int8_t      PWM_Duty_Shift_Value; //变频率启动时缩放移位值         
        int16_t     SR_ON_LTime;//滞后x时间开通(lag time)
        int16_t     SR_OFF_ATime;//提前x时间关断(ahead time)
        
        uint8_t     CHG_SR_State;//充电同步整流状态是否开启
        uint8_t     DISC_SR_State;//放电同步整流状态是否开启        
}DC_Ctrl_Var_t;


typedef struct
{        
        int32_t     Sec_Val;//PWM中断秒时间生成的设定值
        int32_t     Sec_Cnt;//PWM中断秒时间生成的计数值

        int32_t     out_Sum;//
  
        int32_t     out_Sum_Cnt;//
        int32_t     out_AVG;//
        int32_t     out_AVG_Hold;//    
        int32_t     out_AVG_Fir;//  
    
        int32_t     vBat_AD;
        int32_t     iBat_CHG_AD;    
        int32_t     TC_Time;//涓流充电时间设置
        int32_t     TC_Cnt;//涓流充电计时 
        int32_t     vBat_TC_Val;//涓流充电电池电压设定(低于该电压启用涓流充电)
        int32_t     iBat_TC_Val;//涓流充电电池电流设定(过放电使用)
        int32_t     allow_VBat_Val;//低于该电压清除充电完成标志
        int32_t     vBat_CC_CV_Val;//恒流恒压充电模式切换的电池电压阈值设定    
        int32_t     vBat_CV_Val;//恒压充电电池电压设定(低于该电压启用恒流或涓流，高于该值启用恒压) 
        int16_t     iBat_CC_MaxVal;//恒流充电最大值限制     
        int16_t     iBat_CC1_Val;//大恒流充电电池电流设定 
        int16_t     iBat_CC2_Val;//小恒流充电电池电流设定 
        int8_t      CC1_Flag;//大恒流充电时标记为1,0状态为涓流充电状态
        int8_t      CC2_Flag;//小恒流充电时标记为1    
        uint16_t    CC1_Cnt;//大恒流延时计数
        uint16_t    CC2_Cnt;//小恒流延时计数    
        int16_t     vBat_FC_Val;//浮充充电电池电压设定 
        int32_t     iBat_FC_Val;//浮充充电电池电流设定(低于该电流启用浮充)
        int32_t     CV_FC_Time;//CV转FC充电时间设置
        int32_t     CV_FC_Cnt;//CV转FC充电计时 
        
        int8_t      FC_Flag;//浮充电时标记为1  

        int16_t     vBat_Ref_Step_Val;//电压环软启动时，每次步进值       
        int8_t      vBat_Ref_Shift_Val; //电压环软启动时缩放移位值 
        int32_t     vBat_Ref_Hold;//电压环软启动时初始值  
        int32_t     vBat_Ref_SS;   

        int16_t     iBat_Ref_Period;//电流环软启动时，每次步进周期值（ms）
        int16_t     iBat_Ref_Cnt;//电流环软启动时，计数器（ms）
        int16_t     iBat_Ref_Step_Val;//电流环软启动时，每次步进值       
        int8_t      iBat_Ref_Shift_Val; //电流环软启动时缩放移位值 
        int32_t     iBat_Ref_Hold;//电流环软启动时初始值  
        int32_t     iBat_Ref_SS;  
        int8_t      iBat_Ref_SS_Flag;//电流缓启标志
        
        int16_t     vBUS_Ref_Step_Val;//VBUS给定缓启动时，每次步进值       
        int8_t      vBUS_Ref_Shift_Val; //VBUS给定缓启动时缩放移位值 
        int32_t     vBUS_Ref_Hold;//VBUS给定缓启动时初始值 
        int32_t     vBUS_Ref_VBAT_Hold_First;//保存上电时的电池电压值        
        int32_t     vBUS_Ref_SS;    
        int32_t     vBUS_Set; 
        int32_t     vBUS_Ref_Sum;
        int16_t     out;//充电控制输出，传输给PFC侧控制母线电压
        
        int32_t     finish_IBat_Val;//判断充电结束时电流值 
        uint32_t    finish_OK_Cnt;//充电结束延时计数
        uint32_t    finish_NOK_Cnt;//充电结束延时计数        
        int8_t      finish_State; //充电状态：充电是否完成  
}CHG_Var_t;

void CHG_State_Select(void);
void DC_DISC_Ctrl(void);
void DC_CHG_Ctrl(void);

void CHG_PWM_SS(void);//充电控制时启机占空比缓启动
void CHG_IBAT_SS(void);//IBAT电流控制环路缓启动处理


extern DC_Ctrl_Var_t DC_Ctrl_Info;
extern CHG_Var_t CHG_Info;


#endif
/*-------------------------------------------------------------------------------------
*  No more.
*------------------------------------------------------------------------------------*/
