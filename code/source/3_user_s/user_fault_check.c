/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: ���ϴ���
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
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
Others     : ���ϱ����ж��߼�
*************************************************/
void COM_Get_Protect_Flag( int Check_Value, Protect_Check_Var_t * Check_Info,unsigned short int* protect_code )
{
    if (( *protect_code & Check_Info->status_Val ) != E_FALSE )//����˱�����־�Ѿ���λ�����˳����
    {
        return;
    }

    if ( Check_Info->compare_Type == E_MAX )//��ֵΪ��Сֵ
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
    else if ( Check_Info->compare_Type == E_MIN )//��ֵΪ���ֵ
    {
        if ( Check_Value < Check_Info->ref_Val )//�ﵽ������ֵҪ��
        {
            Check_Info->period_Cnt++;
            if ( Check_Info->period_Cnt >= 0x0FFFFFFF ) 
            {
                Check_Info->period_Cnt = 0x0FFFFFFF;
            }
            if ( Check_Info->period_Cnt >= Check_Info->period_Val )
            {
                Check_Info->period_Cnt  = 0;        //ʱ�����ֵ����
                *protect_code |= Check_Info->status_Val;	
            }
        }
        else if ( Check_Value > Check_Info->hysteretic_Val )//���û�����㷧ֵ����
        {
            Check_Info->period_Cnt = 0;//ʱ�����ֵ����
        }
    }
    else
    {
         return;//������
    }
}

/*************************************************
Description: Fault_State_Check
Input      : 
Return     : 
Others     : ���ϱ�����������
*************************************************/
void Fault_State_Check(void)
{
    
    #if OPERATING_MODE != NORMAL_MODE
        return;
    #endif
    
    if (SysClockBase_ms.sys_Check_1ms != E_TRUE || System_ProtectFlag_Info.all != 0) return;
    
    /*-------------------------���ر���-----------------------------------------------------*/
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_CHG_OLP1_Info   , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_CHG_OLP2_Info   , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_DISC_OLP1_Info  , &System_ProtectFlag_Info.all );
//    COM_Get_Protect_Flag( RMS_PQ_Info.out_P , &COM_DISC_OLP2_Info  , &System_ProtectFlag_Info.all );

    
    /*-------------------------��ŵ��������-------------------------------------------------*/    
    if(DC_Ctrl_Info.mode == DC_CHARGE)//���ģʽ
    {
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_CHG_Val_Fir , &CHG_IBAT_OCP1_Info , &System_ProtectFlag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_CHG_Val_Fir , &CHG_IBAT_OCP2_Info , &System_ProtectFlag_Info.all );
    }
    else  //�ŵ�ģʽ   
    {
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_DISC_Val_Fir , &DISC_IBAT_OCP1_Info , &System_ProtectFlag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.iBat_DISC_Val_Fir , &DISC_IBAT_OCP2_Info , &System_ProtectFlag_Info.all );
    } 

    /*---------------------��ص�ѹ��ѹ����---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_OVP_Info , &System_ProtectFlag_Info.all );	  		
    /*---------------------��ص�ѹǷѹ����---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_LVP1_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir , &COM_VBat_LVP2_Info , &System_ProtectFlag_Info.all );


    /*---------------------������Դ��ѹ����---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_AuxPower_OVP_Info , &System_ProtectFlag_Info.all );	  		
    /*---------------------������ԴǷѹ����---------------------------------------------------------------------*/		
    COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_AuxPower_LVP_Info , &System_ProtectFlag_Info.all );


    /*-------------------------���±���-------------------------------------------------------*/
    COM_Get_Protect_Flag( COM_AD_Data_Info.temp_NTC_Val_Fir , &COM_OTP1_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.temp_NTC_Val_Fir , &COM_OTP2_Info , &System_ProtectFlag_Info.all );	

    /*-------------------------VREF����-------------------------------------------------------*/
    COM_Get_Protect_Flag( COM_AD_Data_Info.vRef_Val_Fir , &COM_Vref_OVP_Info , &System_ProtectFlag_Info.all );
    COM_Get_Protect_Flag( COM_AD_Data_Info.vRef_Val_Fir , &COM_Vref_LVP_Info , &System_ProtectFlag_Info.all );	

    SysClockBase_ms.sys_Check_1ms = 0;	    //���ϼ��1ms ʱ�ӱ������		
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
Others     : �������ʱ��ʼ����ر���
*************************************************/
void Protect_Release(void)
{
}


