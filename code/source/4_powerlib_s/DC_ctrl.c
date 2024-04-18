/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 中断函数功能处理
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/

#include "DC_ctrl.h"
#include "sys_mcu_header.h"
#include "sys_define_param.h"
#include "sys_state_machine.h"
#include "sys_define_config.h"
/***************************************************************************/ 


/*************************************************
Description: CHG_PWM_SS
Input      : 
Return     : 
Others     : 充电控制时启机占空比缓启动
*************************************************/
void CHG_PWM_SS(void)//充电控制时启机占空比缓启动
{
    if (DC_Ctrl_Info.mode_Starting == PWM_MODE)//变占空比模式  
    { 
        //变占空比时序逻辑
        if( DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_NOK) //启机未完成，升压启动态占空比逻辑处理
        {                   
            if( DC_Ctrl_Info.EPWM_Duty <  ((DC_Ctrl_Info.EPWM_Period>>1) - DC_Ctrl_Info.CHG_DTime) )//
            {
                DC_Ctrl_Info.EPWM_Duty_Hold += DC_Ctrl_Info.PWM_Duty_Step_Value;
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;
            }
            else
            {
                DC_Ctrl_Info.EPWM_Duty_Hold       = 0;
                DC_Ctrl_Info.start_Finish_State   = COM_START_FINISH_STATE_OK; //表示缓启动升压完成

            }
        }
        
    }
}

/*************************************************
Description: CHG_IBAT_SS
Input      : 
Return     : 
Others     : IBAT电流控制环路缓启动处理
*************************************************/
void CHG_IBAT_SS(void)
{
  	if (SysClockBase_ms.sys_1ms == 1 )
    { 
        CHG_Info.iBat_Ref_Cnt++;
    }        
    /***************************************************************************/
    /*-------------------电压控制环路限幅值缓启动处理--------------------------------*/ 
    if(CHG_Info.iBat_Ref_Cnt > CHG_Info.iBat_Ref_Period)    
    {
        CHG_Info.iBat_Ref_Cnt = 0;
        if(CHG_PID_VBat.out_Max <= CHG_Info.iBat_Ref_SS && CHG_PID_VBat.out_Max < CHG_Info.iBat_CC_MaxVal)
        {
            if(CHG_PID_VBat.out_Max <= (CHG_Info.iBat_TC_Val*2))
                CHG_Info.iBat_Ref_Hold  +=(CHG_Info.iBat_Ref_Step_Val>>3);
            else
                CHG_Info.iBat_Ref_Hold  +=(CHG_Info.iBat_Ref_Step_Val);
        }
    }   
    
    CHG_Info.CC1_Cnt++;
    if( CHG_Info.CC1_Cnt >=22)
    {
        CHG_Info.CC1_Cnt = 0;
        if(CHG_PID_VBat.out_Max > CHG_Info.iBat_Ref_SS)
        {
            CHG_Info.iBat_Ref_Hold  -=(CHG_Info.iBat_Ref_Step_Val<<0);                
        }
    }
    CHG_PID_VBat.out_Max = CHG_Info.iBat_Ref_Hold >> CHG_Info.iBat_Ref_Shift_Val;//电压环最大输出限幅 
    //限制电流环给定最大值
    if(CHG_PID_VBat.out_Max > CHG_Info.iBat_CC_MaxVal)  
    {
        CHG_PID_VBat.out_Max = CHG_Info.iBat_CC_MaxVal;
    }
        
}


/*************************************************
Description: CHG_State_Select
Input      : 
Return     : 
Others     : 充电状态选择处理：涓流、恒压、恒流、浮充
*************************************************/
void CHG_State_Select(void)
{
    //充电曲线逻辑
    if( (CHG_Info.vBat_AD < CHG_Info.vBat_TC_Val|| CHG_Info.TC_Cnt < CHG_Info.TC_Time) &&\
        CHG_Info.CC1_Flag == 0)//涓流充电
    {
        if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//秒计数值判断
        {
            if(CHG_Info.TC_Cnt <= CHG_Info.TC_Time)
                CHG_Info.TC_Cnt++;
        }
        
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_TC_Val ;  //涓流充电电流设定值      
    }
    else if( CHG_Info.vBat_AD < CHG_Info.vBat_FC_Val  && CHG_Info.CC2_Flag == 0)//恒流充电
    { 
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_CC1_Val;
        CHG_Info.CC1_Flag = 1;      
    }
    else if( CHG_Info.vBat_AD >= (CHG_Info.vBat_FC_Val-4)&&\
        CHG_PID_VBat.out < CHG_Info.iBat_CC1_Val)//恒压充电
    {
        CHG_Info.CC2_Cnt++;//小恒流延时计数
        
        if( CHG_Info.CC2_Cnt >=25)
        {            
            CHG_Info.CC2_Cnt = 0; 
            CHG_Info.CC2_Flag = 1;
            //达到浮充电压时递减充电电流设定值，保证工作在电流环中
            CHG_Info.iBat_Ref_SS -=  COM_CHG_IBAT_STEP_VAL;  
            
            if(CHG_Info.iBat_Ref_SS < COM_CHG_IBAT_MIN_VAL)
               CHG_Info.iBat_Ref_SS = COM_CHG_IBAT_MIN_VAL; 
            
        }        
    }
    
    
    //恒压充电切换至浮充状态
    if( CHG_Info.vBat_AD >= CHG_Info.vBat_CC_CV_Val&&\
        CHG_Info.iBat_CHG_AD < CHG_Info.iBat_FC_Val)//浮充
    {
       if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//秒计数值判断
       {
            CHG_Info.CV_FC_Cnt++; //CV转FC充电计时 
            if(CHG_Info.CV_FC_Cnt>=CHG_Info.CV_FC_Time)
            {
                CHG_Info.vBat_Ref_SS = CHG_Info.vBat_FC_Val;
                CHG_Info.FC_Flag = 1;                
            }
       } 
    }
    else
    {
        CHG_Info.CV_FC_Cnt = 0;
    }
    
    if(CHG_Info.FC_Flag == 0)//恒压充电状态
    {
        CHG_Info.vBat_Ref_SS = CHG_Info.vBat_CV_Val;                
    }    
    
    //限制充电电压环参考最大值
    if(CHG_Info.vBat_Ref_SS > CHG_Info.vBat_CV_Val)
    {
        CHG_Info.vBat_Ref_SS    = CHG_Info.vBat_CV_Val; 
    } 
}


/*************************************************
Description: DC_CHG_Ctrl
Input      : 
Return     : 
Others     : 充电控制
*************************************************/
void DC_CHG_Ctrl(void)
{    
    /***************************************************************************/
    /*-------------------VBAT电压环控制--------------------------------------------*/  
    PID_NEW_Ctrl(&CHG_PID_VBat);    
    
    /***************************************************************************/
    /*-------------------IBAT电流环控制--------------------------------------------*/  
    CHG_PID_IBat.ref = CHG_PID_VBat.out;          
    PID_NEW_Ctrl(&CHG_PID_IBat);  
        
    CHG_Info.out = CHG_PID_IBat.out; 
    DC_Ctrl_Info.EPWM_Period = (DC_Ctrl_Info.CHG_PFM_Fk * CHG_Info.out >> 12) + DC_Ctrl_Info.CHG_PFM_Fb;       
    DC_Ctrl_Info.EPWM_Duty_temp = (DC_Ctrl_Info.EPWM_Period>>1) - DC_Ctrl_Info.CHG_DTime;
    if( DC_Ctrl_Info.EPWM_Duty >= DC_Ctrl_Info.EPWM_Duty_temp &&\
        DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_NOK )//
    {
        DC_Ctrl_Info.EPWM_Duty_Hold       = 0;
        DC_Ctrl_Info.start_Finish_State = COM_START_FINISH_STATE_OK;
    }
   
    if( DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_OK)
    {
         DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_temp;
        
        if(DC_Ctrl_Info.EPWM_Duty_Hold < (DC_Ctrl_Info.EPWM_Duty<<DC_Ctrl_Info.PWM_Duty_Shift_Value))
        {
            DC_Ctrl_Info.EPWM_Duty_Hold += DC_Ctrl_Info.PWM_Duty_Step_Value;
            DC_Ctrl_Info.EPWM_DutyB = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;//同步整流占空比 
        }
        else
        {
            DC_Ctrl_Info.EPWM_DutyB = DC_Ctrl_Info.EPWM_Duty;
        }    
    }
            
}
/*************************************************
Description: DC_DISC_Ctrl
Input      : 
Return     : 
Others     : 放电控制
*************************************************/
int32_t DISC_SS_Cnt = 0;
int32_t EPWM_Duty_Calc = 0;
int8_t AD_SS_Cnt = 0;
void DC_DISC_Ctrl(void)
{
    if (1)//(DC_Ctrl_Info.mode_Starting == PWM_MODE)//变占空比模式  
    {
        //依据母线电压换算占空比 
        EPWM_Duty_Calc = ((DC_Ctrl_Info.EPWM_Period>>1) * ADSample_Info.vBusFB_AD);   

        //变占空比时序逻辑
        if( DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_OK)//启机完成，正常工作状态占空比逻辑处理
        {
            DC_Ctrl_Info.EPWM_Duty = EPWM_Duty_Calc >> DC_Ctrl_Info.PWM_Duty_Shift_Value;  
        }                               
        else //启机未完成，升压启动态占空比逻辑处理
        {                   
            if(DC_Ctrl_Info.EPWM_Duty < (EPWM_Duty_Calc >> DC_Ctrl_Info.PWM_Duty_Shift_Value) )//小于计算的占空比的百分比(31/32)
            {
                if(COM_Ctr_Info.INV_VBus_AD <DC_Ctrl_Info.INV_vBus_Vol_VAL_Set)
                {
                    DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;//固定小占空比启动，规避启机VDS尖峰
                }
                else
                {
                    DC_Ctrl_Info.EPWM_Duty_Hold += DC_Ctrl_Info.PWM_Duty_Step_Value;
                    DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;               
                }                                 
            }

            if( (ADSample_Info.vBusFB_AD < DC_Ctrl_Info.AD_VBusFB_Val_Set )|| \
                COM_Ctr_Info.INV_VBus_AD >=DC_Ctrl_Info.INV_vBus_Vol_VAL_Set2||
                DC_Ctrl_Info.EPWM_Duty >= (EPWM_Duty_Calc >> DC_Ctrl_Info.PWM_Duty_Shift_Value) )
            {       
                DC_Ctrl_Info.EPWM_Duty = EPWM_Duty_Calc>> DC_Ctrl_Info.PWM_Duty_Shift_Value;
                DC_Ctrl_Info.start_Finish_State = COM_START_FINISH_STATE_OK; //表示缓启动升压完成                                                          
            }
        }    
    }            
    else   //变频率模式
    {                             
        //依据母线电压换算占空比    
        DC_Ctrl_Info.EPWM_Duty = (DC_Ctrl_Info.EPWM_Period * ADSample_Info.vBusFB_AD)>>12;
                  
        //频率切换时序逻辑
        if((DC_Ctrl_Info.FRE_Switch_Cnt > 19000||COM_Ctr_Info.INV_VBus_AD >=DC_Ctrl_Info.INV_vBus_Vol_VAL_Set)&&\
           (DC_Ctrl_Info.EPWM_Period    >= DC_Ctrl_Info.EPWM_Period_Work)&&\
           (DC_Ctrl_Info.start_Finish_State  == COM_START_FINISH_STATE_NOK)&&\
           (DC_Ctrl_Info.ZIF_PIF_State  == 1))//只能在周期中断里执行频率切换                
        {
            DC_Ctrl_Info.start_Finish_State  = COM_START_FINISH_STATE_OK;//启机完成，设置为正常工作状态
            DC_Ctrl_Info.EPWM_Period         = DC_Ctrl_Info.EPWM_Period_Work;//设置为正常工作的频率
            BAT_START_ENABLE;
            DISC_SS_Cnt = 0;
        } 
        
        //1、正常工作频率小占空比启动升压到设定母线电压值后；
        //2、更改为启机工作频率大占空比启动，升压到设定母线值更改为正常工作频率，此时软启动完成
        if(DC_Ctrl_Info.start_Finish_State  == COM_START_FINISH_STATE_NOK)
        {
            if(COM_Ctr_Info.INV_VBus_AD <=PFM_INV_VBUS_VOL_VAL_SET_SS && DISC_SS_Cnt<100000 )
            {
                DC_Ctrl_Info.EPWM_Duty = 15;  //固定小占空比启动，规避启机VDS尖峰  
                DISC_SS_Cnt ++;
                DC_Ctrl_Info.EPWM_Period      = DC_Ctrl_Info.EPWM_Period_Work;//设置为正常工作的频率
            }
            else if(COM_Ctr_Info.INV_VBus_AD <= DC_Ctrl_Info.INV_vBus_Vol_VAL_Set&&DISC_SS_Cnt<200000)
            {
                DISC_SS_Cnt = 200000;
                DC_Ctrl_Info.EPWM_Period      = DISC_EPWM_PERIOD_START;//设置为启机工作的频率            
            }
        }
        
        if(DC_Ctrl_Info.EPWM_Period > DC_Ctrl_Info.EPWM_Period_Work )  
        {
            DC_Ctrl_Info.FRE_Switch_Cnt ++;
        }              
        
        //限制最小工作周期值，即最大开关频率
        if(DC_Ctrl_Info.EPWM_Period < DC_Ctrl_Info.EPWM_Period_Min )  
        {
            DC_Ctrl_Info.EPWM_Period =  DC_Ctrl_Info.EPWM_Period_Min; 
        }
        //限制最大工作周期值，即最小开关频率
        if(DC_Ctrl_Info.EPWM_Period > DC_Ctrl_Info.EPWM_Period_Max )  
        {
            DC_Ctrl_Info.EPWM_Period =  DC_Ctrl_Info.EPWM_Period_Max; 
        }    
        
        //限制启机时最大占空比
        if(DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_NOK)//处于启机状态
        {
            if(DC_Ctrl_Info.EPWM_Duty > DC_Ctrl_Info.EPWM_Duty_Max_Start)//启机时限制最大占空比
            {
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Max_Start;  
            }        
        }
    }
}

//#pragma arm section
