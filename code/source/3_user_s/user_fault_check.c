/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 故障处理
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/
#include "sys_state_machine.h"
#include "sys_mcu_header.h"
/***************************************************************************/

/*************************************************
Description: COM_Get_Protect_Flag
Input      : 
Return     : 
Others     : 故障保护判断逻辑
*************************************************/
void COM_Get_Protect_Flag( int Check_Value, Protect_Check_Var_t * Check_Info,unsigned short int* protect_code )
{
    if (( *protect_code & Check_Info->status_Val ) != E_FALSE )//如果此保护标志已经置位，则退出检查
    {
        return;
    }

    if ( Check_Info->compare_Type == E_MAX )//阀值为最小值
    {
        if ( Check_Value > Check_Info->ref_Val)
        {	

            Check_Info->period_Cnt++;
            if ( Check_Info->period_Cnt >= 0x0FFFFFFF ) 
            {
                Check_Info->period_Cnt = 0x0FFFFFFF;
            }
            if ( Check_Info->period_Cnt >= Check_Info->period_Val )
            {
                Check_Info->period_Cnt = 0;
                *protect_code |= Check_Info->status_Val;
            }
        }
        else if ( Check_Value < Check_Info->hysteretic_Val )
        {
            Check_Info->period_Cnt = 0;
        }
    }
    /*------------------------------------------------------------------------------------*/
    else if ( Check_Info->compare_Type == E_MIN )//阀值为最大值
    {
        if ( Check_Value < Check_Info->ref_Val )//达到保护阀值要求
        {
            Check_Info->period_Cnt++;
            if ( Check_Info->period_Cnt >= 0x0FFFFFFF ) 
            {
                Check_Info->period_Cnt = 0x0FFFFFFF;
            }
            if ( Check_Info->period_Cnt >= Check_Info->period_Val )
            {
                Check_Info->period_Cnt  = 0;        //时间计数值清零
                *protect_code |= Check_Info->status_Val;	
            }
        }
        else if ( Check_Value > Check_Info->hysteretic_Val )//如果没有满足阀值条件
        {
            Check_Info->period_Cnt = 0;//时间计数值清零
        }
    }
    else
    {
         return;//错误处理
    }
}

/*************************************************
Description: Fault_State_Check
Input      : 
Return     : 
Others     : 故障保护功能启用
*************************************************/
void Fault_State_Check(void)
{
    
    #if OPERATING_MODE != NORMAL_MODE
        return;
    #endif
    
    if (SysClockBase_ms.sys_Check_1ms != E_TRUE || System_ProtectFlag_Info.all != 0) return;
    
    /*-------------------------过载保护-----------------------------------------------------*/
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_CHG_OLP1_Info   , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_CHG_OLP2_Info   , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_DISC_OLP1_Info  , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_DISC_OLP2_Info  , &System_ProtectFlag_Info.all );

    
    /*-------------------------充放电过流保护-------------------------------------------------*/    
    if(DC_Ctrl_Info.mode == DC_CHARGE)//充电模式
    {
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_CHG_Val_Fir , &CHG_IBAT_OCP1_Info , &System_ProtectFlag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_CHG_Val_Fir , &CHG_IBAT_OCP2_Info , &System_ProtectFlag_Info.all );
    }
    else  //放电模式   
    {
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_DISC_Val_Fir , &DISC_IBAT_OCP1_Info , &System_ProtectFlag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_DISC_Val_Fir , &DISC_IBAT_OCP2_Info , &System_ProtectFlag_Info.all );
    } 

    /*---------------------电池电压过压保护---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_OVP_Info , &System_ProtectFlag_Info.all );	  		
    /*---------------------电池电压欠压保护---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_LVP1_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_LVP2_Info , &System_ProtectFlag_Info.all );


    /*---------------------辅助电源过压保护---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_AuxPower_OVP_Info , &System_ProtectFlag_Info.all );	  		
    /*---------------------辅助电源欠压保护---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_AuxPower_LVP_Info , &System_ProtectFlag_Info.all );


    /*-------------------------过温保护-------------------------------------------------------*/
    COM_Get_Protect_Flag( COM_AD_Data_Info.temp_NTC_Val_Fir , &COM_OTP1_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.temp_NTC_Val_Fir , &COM_OTP2_Info , &System_ProtectFlag_Info.all );	

    /*-------------------------VREF保护-------------------------------------------------------*/
    COM_Get_Protect_Flag( COM_AD_Data_Info.vRef_Val_Fir , &COM_Vref_OVP_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.vRef_Val_Fir , &COM_Vref_LVP_Info , &System_ProtectFlag_Info.all );	

    SysClockBase_ms.sys_Check_1ms = 0;	    //故障检测1ms 时钟标记清零		
}

/*************************************************
Description: Fault_State_Deal
Input      : 
Return     : 
Others     : 
*************************************************/
void Fault_State_Deal(void)
{
}

/*************************************************
Description: Protect_Release
Input      : 
Return     : 
Others     : 解除保护时初始化相关变量
*************************************************/
void Protect_Release(void)
{
}


