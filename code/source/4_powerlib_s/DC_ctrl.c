/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: �жϺ������ܴ���
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
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
Others     : ������ʱ����ռ�ձȻ�����
*************************************************/
void CHG_PWM_SS(void)//������ʱ����ռ�ձȻ�����
{
    if (DC_Ctrl_Info.mode_Starting == PWM_MODE)//��ռ�ձ�ģʽ  
    { 
        //��ռ�ձ�ʱ���߼�
        if( DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_NOK) //����δ��ɣ���ѹ����̬ռ�ձ��߼�����
        {                   
            if( DC_Ctrl_Info.EPWM_Duty <  ((DC_Ctrl_Info.EPWM_Period>>1) - DC_Ctrl_Info.CHG_DTime) )//
            {
                DC_Ctrl_Info.EPWM_Duty_Hold += DC_Ctrl_Info.PWM_Duty_Step_Value;
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;
            }
            else
            {
                DC_Ctrl_Info.EPWM_Duty_Hold       = 0;
                DC_Ctrl_Info.start_Finish_State   = COM_START_FINISH_STATE_OK; //��ʾ��������ѹ���

            }
        }
        
    }
}

/*************************************************
Description: CHG_IBAT_SS
Input      : 
Return     : 
Others     : IBAT�������ƻ�·����������
*************************************************/
void CHG_IBAT_SS(void)
{
  	if (SysClockBase_ms.sys_1ms == 1 )
    { 
        CHG_Info.iBat_Ref_Cnt++;
    }        
    /***************************************************************************/
    /*-------------------��ѹ���ƻ�·�޷�ֵ����������--------------------------------*/ 
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
    CHG_PID_VBat.out_Max = CHG_Info.iBat_Ref_Hold >> CHG_Info.iBat_Ref_Shift_Val;//��ѹ���������޷� 
    //���Ƶ������������ֵ
    if(CHG_PID_VBat.out_Max > CHG_Info.iBat_CC_MaxVal)  
    {
        CHG_PID_VBat.out_Max = CHG_Info.iBat_CC_MaxVal;
    }
        
}


/*************************************************
Description: CHG_State_Select
Input      : 
Return     : 
Others     : ���״̬ѡ�����������ѹ������������
*************************************************/
void CHG_State_Select(void)
{
    //��������߼�
    if( (CHG_Info.vBat_AD < CHG_Info.vBat_TC_Val|| CHG_Info.TC_Cnt < CHG_Info.TC_Time) &&\
        CHG_Info.CC1_Flag == 0)//������
    {
        if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//�����ֵ�ж�
        {
            if(CHG_Info.TC_Cnt <= CHG_Info.TC_Time)
                CHG_Info.TC_Cnt++;
        }
        
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_TC_Val ;  //����������趨ֵ      
    }
    else if( CHG_Info.vBat_AD < CHG_Info.vBat_FC_Val  && CHG_Info.CC2_Flag == 0)//�������
    { 
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_CC1_Val;
        CHG_Info.CC1_Flag = 1;      
    }
    else if( CHG_Info.vBat_AD >= (CHG_Info.vBat_FC_Val-4)&&\
        CHG_PID_VBat.out < CHG_Info.iBat_CC1_Val)//��ѹ���
    {
        CHG_Info.CC2_Cnt++;//С������ʱ����
        
        if( CHG_Info.CC2_Cnt >=25)
        {            
            CHG_Info.CC2_Cnt = 0; 
            CHG_Info.CC2_Flag = 1;
            //�ﵽ�����ѹʱ�ݼ��������趨ֵ����֤�����ڵ�������
            CHG_Info.iBat_Ref_SS -=  COM_CHG_IBAT_STEP_VAL;  
            
            if(CHG_Info.iBat_Ref_SS < COM_CHG_IBAT_MIN_VAL)
               CHG_Info.iBat_Ref_SS = COM_CHG_IBAT_MIN_VAL; 
            
        }        
    }
    
    
    //��ѹ����л�������״̬
    if( CHG_Info.vBat_AD >= CHG_Info.vBat_CC_CV_Val&&\
        CHG_Info.iBat_CHG_AD < CHG_Info.iBat_FC_Val)//����
    {
       if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//�����ֵ�ж�
       {
            CHG_Info.CV_FC_Cnt++; //CVתFC����ʱ 
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
    
    if(CHG_Info.FC_Flag == 0)//��ѹ���״̬
    {
        CHG_Info.vBat_Ref_SS = CHG_Info.vBat_CV_Val;                
    }    
    
    //���Ƴ���ѹ���ο����ֵ
    if(CHG_Info.vBat_Ref_SS > CHG_Info.vBat_CV_Val)
    {
        CHG_Info.vBat_Ref_SS    = CHG_Info.vBat_CV_Val; 
    } 
}


/*************************************************
Description: DC_CHG_Ctrl
Input      : 
Return     : 
Others     : ������
*************************************************/
void DC_CHG_Ctrl(void)
{    
    /***************************************************************************/
    /*-------------------VBAT��ѹ������--------------------------------------------*/  
    PID_NEW_Ctrl(&CHG_PID_VBat);    
    
    /***************************************************************************/
    /*-------------------IBAT����������--------------------------------------------*/  
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
            DC_Ctrl_Info.EPWM_DutyB = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;//ͬ������ռ�ձ� 
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
Others     : �ŵ����
*************************************************/
int32_t DISC_SS_Cnt = 0;
int32_t EPWM_Duty_Calc = 0;
int8_t AD_SS_Cnt = 0;
void DC_DISC_Ctrl(void)
{
    if (1)//(DC_Ctrl_Info.mode_Starting == PWM_MODE)//��ռ�ձ�ģʽ  
    {
        //����ĸ�ߵ�ѹ����ռ�ձ� 
        EPWM_Duty_Calc = ((DC_Ctrl_Info.EPWM_Period>>1) * ADSample_Info.vBusFB_AD);   

        //��ռ�ձ�ʱ���߼�
        if( DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_OK)//������ɣ���������״̬ռ�ձ��߼�����
        {
            DC_Ctrl_Info.EPWM_Duty = EPWM_Duty_Calc >> DC_Ctrl_Info.PWM_Duty_Shift_Value;  
        }                               
        else //����δ��ɣ���ѹ����̬ռ�ձ��߼�����
        {                   
            if(DC_Ctrl_Info.EPWM_Duty < (EPWM_Duty_Calc >> DC_Ctrl_Info.PWM_Duty_Shift_Value) )//С�ڼ����ռ�ձȵİٷֱ�(31/32)
            {
                if(COM_Ctr_Info.INV_VBus_AD <DC_Ctrl_Info.INV_vBus_Vol_VAL_Set)
                {
                    DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Hold >> DC_Ctrl_Info.PWM_Duty_Shift_Value;//�̶�Сռ�ձ��������������VDS���
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
                DC_Ctrl_Info.start_Finish_State = COM_START_FINISH_STATE_OK; //��ʾ��������ѹ���                                                          
            }
        }    
    }            
    else   //��Ƶ��ģʽ
    {                             
        //����ĸ�ߵ�ѹ����ռ�ձ�    
        DC_Ctrl_Info.EPWM_Duty = (DC_Ctrl_Info.EPWM_Period * ADSample_Info.vBusFB_AD)>>12;
                  
        //Ƶ���л�ʱ���߼�
        if((DC_Ctrl_Info.FRE_Switch_Cnt > 19000||COM_Ctr_Info.INV_VBus_AD >=DC_Ctrl_Info.INV_vBus_Vol_VAL_Set)&&\
           (DC_Ctrl_Info.EPWM_Period    >= DC_Ctrl_Info.EPWM_Period_Work)&&\
           (DC_Ctrl_Info.start_Finish_State  == COM_START_FINISH_STATE_NOK)&&\
           (DC_Ctrl_Info.ZIF_PIF_State  == 1))//ֻ���������ж���ִ��Ƶ���л�                
        {
            DC_Ctrl_Info.start_Finish_State  = COM_START_FINISH_STATE_OK;//������ɣ�����Ϊ��������״̬
            DC_Ctrl_Info.EPWM_Period         = DC_Ctrl_Info.EPWM_Period_Work;//����Ϊ����������Ƶ��
            BAT_START_ENABLE;
            DISC_SS_Cnt = 0;
        } 
        
        //1����������Ƶ��Сռ�ձ�������ѹ���趨ĸ�ߵ�ѹֵ��
        //2������Ϊ��������Ƶ�ʴ�ռ�ձ���������ѹ���趨ĸ��ֵ����Ϊ��������Ƶ�ʣ���ʱ���������
        if(DC_Ctrl_Info.start_Finish_State  == COM_START_FINISH_STATE_NOK)
        {
            if(COM_Ctr_Info.INV_VBus_AD <=PFM_INV_VBUS_VOL_VAL_SET_SS && DISC_SS_Cnt<100000 )
            {
                DC_Ctrl_Info.EPWM_Duty = 15;  //�̶�Сռ�ձ��������������VDS���  
                DISC_SS_Cnt ++;
                DC_Ctrl_Info.EPWM_Period      = DC_Ctrl_Info.EPWM_Period_Work;//����Ϊ����������Ƶ��
            }
            else if(COM_Ctr_Info.INV_VBus_AD <= DC_Ctrl_Info.INV_vBus_Vol_VAL_Set&&DISC_SS_Cnt<200000)
            {
                DISC_SS_Cnt = 200000;
                DC_Ctrl_Info.EPWM_Period      = DISC_EPWM_PERIOD_START;//����Ϊ����������Ƶ��            
            }
        }
        
        if(DC_Ctrl_Info.EPWM_Period > DC_Ctrl_Info.EPWM_Period_Work )  
        {
            DC_Ctrl_Info.FRE_Switch_Cnt ++;
        }              
        
        //������С��������ֵ������󿪹�Ƶ��
        if(DC_Ctrl_Info.EPWM_Period < DC_Ctrl_Info.EPWM_Period_Min )  
        {
            DC_Ctrl_Info.EPWM_Period =  DC_Ctrl_Info.EPWM_Period_Min; 
        }
        //�������������ֵ������С����Ƶ��
        if(DC_Ctrl_Info.EPWM_Period > DC_Ctrl_Info.EPWM_Period_Max )  
        {
            DC_Ctrl_Info.EPWM_Period =  DC_Ctrl_Info.EPWM_Period_Max; 
        }    
        
        //��������ʱ���ռ�ձ�
        if(DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_NOK)//��������״̬
        {
            if(DC_Ctrl_Info.EPWM_Duty > DC_Ctrl_Info.EPWM_Duty_Max_Start)//����ʱ�������ռ�ձ�
            {
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Max_Start;  
            }        
        }
    }
}

//#pragma arm section
