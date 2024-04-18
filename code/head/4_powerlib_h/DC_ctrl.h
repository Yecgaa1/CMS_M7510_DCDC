/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

#ifndef __DC_CTRL_H
#define __DC_CTRL_H

#include "stdint.h"

//----------------------------------------------------------------------------------------------
typedef struct
{
        int8_t      mode; //0���ŵ�ģʽ��1�����ģʽ   
        int16_t     EPWM_Period_Max;    //�����������ֵ����������С����Ƶ��
        int16_t     EPWM_Period_Min;    //������С����ֵ����������󿪹�Ƶ��
        int32_t     EPWM_Period;        //ʵʱ���µ�Ƶ��

    
        int32_t     EPWM_Period_Work;   //�趨�Ĺ���Ƶ��     
        int32_t     EPWM_Period_Hold;  
        int16_t     EPWM_Duty_Max_Start;//����ʱ���ռ�ձ�������ֵ
        int16_t     EPWM_Duty_Max;  //��������ʱ���ռ�ձ�������ֵ
        int16_t     EPWM_Duty_Min;  //��Сռ�ձ�������ֵ   
        int32_t     EPWM_Duty;      //ʵʱ����ռ�ձ�
        int32_t     EPWM_Duty_temp;            
        int32_t     EPWM_DutyB;      //ʵʱ����ռ�ձ�    
        int32_t     EPWM_Duty_Calc;
        int32_t     EPWM_Duty_Hold; 
        int16_t     CHG_PFM_Fk;
        int16_t     CHG_PFM_Fb;
        int16_t     CHG_DTime;//�������ʱ��
        int16_t     DISC_DTime;
        int16_t     vBus_Check_Val;     //�����MOS�Լ�ʱ���Ƶ�ĸ�ߵ�ѹ�趨ֵ 
        int8_t      INV_Ready_State;    //0�������δ׼����;1�������׼����
        int8_t      INV_Ready_OK_Cnt;    //�����׼������ʱ����
        int8_t      INV_Ready_NOK_Cnt;    //�����δ׼������ʱ����
    
        int8_t      start_Finish_State; //0-����������ѹ״̬��1-������������״̬
        int8_t      ZIF_PIF_State;  //1-�������ڵ��жϣ�0-���ڹ�����ж�
        int8_t      mode_Operate;   //����or�ջ�
        int8_t      mode_Starting;  //������ʽ��PWM����PFM
        int16_t     FRE_Switch_Cnt;   //CHGƵ���л�����
        int16_t     AD_VBusFB_Val_Set;//�趨ĸ�ߵ�ѹ����������ֵ�����ڸ�ֵ��vBusFB_AD���㣬�����趨ֵ����ʹ�ò���ֵ0~4095    
        int16_t     INV_vBus_Vol_VAL_Set;//(�����ഫ���ĸ�ߵ�ѹֵ�Ƚ�)���ڸ�ĸ�ߵ�ѹֵ�л�����Ƶ��
        int16_t     INV_vBus_Vol_VAL_Set2;
        int16_t     PFM_Period_Step_Value;//��Ƶ������ʱ��ÿ�β���ֵ       
        int8_t      PFM_Period_Shift_Value; //��Ƶ������ʱ������λֵ      
        int16_t     PWM_Duty_Step_Value;//��Ƶ������ʱ��ÿ�β���ֵ       
        int8_t      PWM_Duty_Shift_Value; //��Ƶ������ʱ������λֵ         
        int16_t     SR_ON_LTime;//�ͺ�xʱ�俪ͨ(lag time)
        int16_t     SR_OFF_ATime;//��ǰxʱ��ض�(ahead time)
        
        uint8_t     CHG_SR_State;//���ͬ������״̬�Ƿ���
        uint8_t     DISC_SR_State;//�ŵ�ͬ������״̬�Ƿ���        
}DC_Ctrl_Var_t;


typedef struct
{        
        int32_t     Sec_Val;//PWM�ж���ʱ�����ɵ��趨ֵ
        int32_t     Sec_Cnt;//PWM�ж���ʱ�����ɵļ���ֵ

        int32_t     out_Sum;//
  
        int32_t     out_Sum_Cnt;//
        int32_t     out_AVG;//
        int32_t     out_AVG_Hold;//    
        int32_t     out_AVG_Fir;//  
    
        int32_t     vBat_AD;
        int32_t     iBat_CHG_AD;    
        int32_t     TC_Time;//������ʱ������
        int32_t     TC_Cnt;//�������ʱ 
        int32_t     vBat_TC_Val;//�������ص�ѹ�趨(���ڸõ�ѹ����������)
        int32_t     iBat_TC_Val;//�������ص����趨(���ŵ�ʹ��)
        int32_t     allow_VBat_Val;//���ڸõ�ѹ��������ɱ�־
        int32_t     vBat_CC_CV_Val;//������ѹ���ģʽ�л��ĵ�ص�ѹ��ֵ�趨    
        int32_t     vBat_CV_Val;//��ѹ����ص�ѹ�趨(���ڸõ�ѹ���ú�������������ڸ�ֵ���ú�ѹ) 
        int16_t     iBat_CC_MaxVal;//����������ֵ����     
        int16_t     iBat_CC1_Val;//���������ص����趨 
        int16_t     iBat_CC2_Val;//С��������ص����趨 
        int8_t      CC1_Flag;//��������ʱ���Ϊ1,0״̬Ϊ������״̬
        int8_t      CC2_Flag;//С�������ʱ���Ϊ1    
        uint16_t    CC1_Cnt;//�������ʱ����
        uint16_t    CC2_Cnt;//С������ʱ����    
        int16_t     vBat_FC_Val;//�������ص�ѹ�趨 
        int32_t     iBat_FC_Val;//�������ص����趨(���ڸõ������ø���)
        int32_t     CV_FC_Time;//CVתFC���ʱ������
        int32_t     CV_FC_Cnt;//CVתFC����ʱ 
        
        int8_t      FC_Flag;//�����ʱ���Ϊ1  

        int16_t     vBat_Ref_Step_Val;//��ѹ��������ʱ��ÿ�β���ֵ       
        int8_t      vBat_Ref_Shift_Val; //��ѹ��������ʱ������λֵ 
        int32_t     vBat_Ref_Hold;//��ѹ��������ʱ��ʼֵ  
        int32_t     vBat_Ref_SS;   

        int16_t     iBat_Ref_Period;//������������ʱ��ÿ�β�������ֵ��ms��
        int16_t     iBat_Ref_Cnt;//������������ʱ����������ms��
        int16_t     iBat_Ref_Step_Val;//������������ʱ��ÿ�β���ֵ       
        int8_t      iBat_Ref_Shift_Val; //������������ʱ������λֵ 
        int32_t     iBat_Ref_Hold;//������������ʱ��ʼֵ  
        int32_t     iBat_Ref_SS;  
        int8_t      iBat_Ref_SS_Flag;//����������־
        
        int16_t     vBUS_Ref_Step_Val;//VBUS����������ʱ��ÿ�β���ֵ       
        int8_t      vBUS_Ref_Shift_Val; //VBUS����������ʱ������λֵ 
        int32_t     vBUS_Ref_Hold;//VBUS����������ʱ��ʼֵ 
        int32_t     vBUS_Ref_VBAT_Hold_First;//�����ϵ�ʱ�ĵ�ص�ѹֵ        
        int32_t     vBUS_Ref_SS;    
        int32_t     vBUS_Set; 
        int32_t     vBUS_Ref_Sum;
        int16_t     out;//����������������PFC�����ĸ�ߵ�ѹ
        
        int32_t     finish_IBat_Val;//�жϳ�����ʱ����ֵ 
        uint32_t    finish_OK_Cnt;//��������ʱ����
        uint32_t    finish_NOK_Cnt;//��������ʱ����        
        int8_t      finish_State; //���״̬������Ƿ����  
}CHG_Var_t;

void CHG_State_Select(void);
void DC_DISC_Ctrl(void);
void DC_CHG_Ctrl(void);

void CHG_PWM_SS(void);//������ʱ����ռ�ձȻ�����
void CHG_IBAT_SS(void);//IBAT�������ƻ�·����������


extern DC_Ctrl_Var_t DC_Ctrl_Info;
extern CHG_Var_t CHG_Info;


#endif
/*-------------------------------------------------------------------------------------
*  No more.
*------------------------------------------------------------------------------------*/
