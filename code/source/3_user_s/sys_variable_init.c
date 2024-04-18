/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/
#include "sys_mcu_header.h"

/***************************************************************************/

/*************************************************
Description: Sys_VariableInit
Input      : 
Return     : 
Others     : ϵͳ������ʼ��
*************************************************/
void Sys_VariableInit(void)
{    
    UART0_Info.RXD_CRC_Init = 0xffff;//��ʼ��CRC�Ĵ�����ʼֵ
    UART0_Info.TXD_CRC_Init = 0xffff;//��ʼ��CRC�Ĵ�����ʼֵ

    CHG_PID_VBat.out_Max = 2;
    COM_Ctr_Info.PWM_Enable = 0;//������ʹ���ź�
    
    COM_Ctr_Info.INTP3_Start_TimeVal    = 500;  //ms             
    COM_Ctr_Info.INTP3_Start_OK         = 0;    
    COM_Ctr_Info.INTP3_Start_Cnt        = 0;
                 
    COM_Ctr_Info.NO_Mode_OK_Cnt         = 0; 
    COM_Ctr_Info.NO_Mode_OK_TimeVal     = 40;    
    COM_Ctr_Info.PFC_Mode_OK_Cnt        = 0;
    COM_Ctr_Info.PFC_Mode_OK_TimeVal    = 150;
    COM_Ctr_Info.INV_Mode_OK_Cnt        = 0;
    COM_Ctr_Info.INV_Mode_OK_TimeVal    = 3;    
    DC_Ctrl_Info.mode                   = 0;//Ĭ�Ͽ���ģʽ
    
    DC_Ctrl_Info.SR_ON_LTime            = SR_ON_LTIME;//�ͺ�xʱ�俪ͨ(lag time)
    DC_Ctrl_Info.SR_OFF_ATime           = SR_OFF_ATIME;//��ǰxʱ��ض�(ahead time)    

    DC_Ctrl_Info.EPWM_Period            = DISC_PWM_PERIOD_INIT;
    
    DC_Ctrl_Info.EPWM_Duty_Max          = DISC_EPWM_DUTY_MAX;//��������ֵ��ȥ����ʱ��
    DC_Ctrl_Info.EPWM_Duty_Min          = DISC_EPWM_DUTY_MIN;//�����ռ�ձȵ��ڸ���ֵʱ��ֱ�Ӱ�ռ�ձȸ���Ϊ0
    
    DC_Ctrl_Info.CHG_PFM_Fk             = CHG_PFM_K;
    DC_Ctrl_Info.CHG_PFM_Fb             = CHG_PFM_b;
    DC_Ctrl_Info.CHG_DTime              = CHG_DEADTIME;//�������ʱ��
    DC_Ctrl_Info.DISC_DTime             = DISC_DEADTIME_WORK;
    AD_Correct_CHG_IBat.Flag.all        = 0;
    AD_Correct_DISC_IBat.Flag.all       = 0;    
    
    StartCheck_Flag_Info.all            = 0;
    System_ProtectFlag_Info.all         = 0;
    
    DC_Ctrl_Info.mode_Operate           = OPERATING_MODE;//����or�ջ�   
    DC_Ctrl_Info.start_Finish_State     = COM_START_FINISH_STATE_NOK;//0-����������ѹ״̬��1-������������״̬
    DC_Ctrl_Info.INV_Ready_State        = COM_INV_READY_STATE_NOK;//0�������δ׼����;1�������׼����
    

    DC_Ctrl_Info.AD_VBusFB_Val_Set      = PFM_AD_VBUS_FB_VAL_SET;//�趨ĸ�ߵ�ѹ����������ֵ�����ڸ�ֵʱ������ɣ������趨ֵ����ʹ�ò���ֵ0~4095    
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set   = PFM_INV_VBUS_VOL_VAL_SET;//(�����ഫ���ĸ�ߵ�ѹֵ�Ƚ�)���ڸ�ĸ�ߵ�ѹֵ�л�����Ƶ��
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set2  = PFM_INV_VBUS_VOL_VAL_SET2;
    DC_Ctrl_Info.FRE_Switch_Cnt         = 0;//CHGƵ���л�����
     
    CHG_Info.allow_VBat_Val             = COM_CHG_ALLOW_VBAT_VAL;//���ڸõ�ѹ��������ɱ�־

    CHG_Info.vBat_TC_Val        = COM_CHG_VBAT_TC_VAL;//�������ص�ѹ�趨(���ڸõ�ѹ����������)
    CHG_Info.iBat_TC_Val        = COM_CHG_IBAT_TC_VAL;//�������ص����趨(���ŵ�ʹ��) 
    CHG_Info.vBat_CC_CV_Val     = COM_CHG_VBAT_CC_CV_VAL;//������ѹ���ģʽ�л��ĵ�ص�ѹ��ֵ�趨 
    CHG_Info.vBat_CV_Val        = COM_CHG_VBAT_CV_VAL;//��ѹ����ص�ѹ�趨(���ڸõ�ѹ���ú�������������ڸ�ֵ���ú�ѹ)  
    CHG_Info.iBat_CC_MaxVal     = COM_CHG_IBAT_CC_MAXVAL;//��������ص������ֵ����
    CHG_Info.iBat_CC1_Val       = COM_CHG_IBAT_CC1_VAL;//���������ص����趨 
    CHG_Info.iBat_CC2_Val       = COM_CHG_IBAT_CC2_VAL;//С��������ص����趨 
    CHG_Info.vBat_FC_Val        = COM_CHG_VBAT_FC_VAL;//�������ص�ѹ�趨 
    CHG_Info.iBat_FC_Val        = COM_CHG_IBAT_FC_VAL;//�������ص����趨(���ڸõ������ø���)   
    CHG_Info.finish_IBat_Val    = COM_CHG_FINISH_IBAT_VAL;//�жϳ�����ʱ����ֵ   

    CHG_Info.CC1_Flag           = 0;//��������ʱ���Ϊ1,0״̬Ϊ������״̬
    CHG_Info.CC2_Flag           = 0;//С�������ʱ���Ϊ1
    CHG_Info.FC_Flag            = 0;//�����ʱ���Ϊ1    
    CHG_Info.CC1_Cnt            = 0;//�������ʱ����
    CHG_Info.CC2_Cnt            = 0;//С������ʱ����
    CHG_Info.finish_OK_Cnt      = 0;//��������ʱ����      
    CHG_Info.finish_NOK_Cnt     = 0;//���δ�����ʱ����    
    
    CHG_PID_IBat.out            = 0;
    CHG_PID_VBat.out            = 0;
    CHG_PID_VBat.ref            = 0;
    CHG_PID_IBat.ref            = 0;
    CHG_Info.vBat_Ref_Hold      = 0;
    CHG_Info.iBat_Ref_Hold      = 0;
    
    CHG_Info.finish_State       = COM_CHG_FINISH_NOK;
    CHG_Info.CV_FC_Cnt          = 0;//CVתFC����ʱ 
    CHG_Info.CV_FC_Time         = COM_CHG_CV_FC_TIME;//CVתFC���ʱ������    
    CHG_Info.TC_Cnt             = 0;
    CHG_Info.TC_Time            = COM_CHG_TC_TIME;
    CHG_Info.Sec_Val            = CHG_EPWM_FREQ_MAX;//PWM�ж���ʱ�����ɵ��趨ֵ
    CHG_Info.Sec_Cnt            = 0;//PWM�ж���ʱ�����ɵļ���ֵ
    
    //��ѹ����ʼ���ʱ������   
    CHG_Info.vBat_Ref_Step_Val      = COM_CHG_VBAT_REF_STEP_VALUE;//��ѹ��������ʱ��ÿ�β���ֵ       
    CHG_Info.vBat_Ref_Shift_Val     = COM_CHG_VBAT_REF_SHIFT_VALUE; //��ѹ��������ʱ������λֵ 
    CHG_Info.vBat_Ref_Hold          = COM_CHG_VBAT_REF_HOLD_INIT;//��ѹ��������ʱ��ʼֵ  
    CHG_Info.vBat_Ref_SS            = 0;   

    //��������ʼ���ʱ������  
    CHG_Info.iBat_Ref_Period        = COM_CHG_IBAT_REF_PEIROD;//��ռ�ձ�����ʱ��ÿ�β�������ֵ(ms)
    CHG_Info.iBat_Ref_Step_Val      = COM_CHG_IBAT_REF_STEP_VALUE;//������������ʱ��ÿ�β���ֵ       
    CHG_Info.iBat_Ref_Shift_Val     = COM_CHG_IBAT_REF_SHIFT_VALUE; //������������ʱ������λֵ 
    CHG_Info.iBat_Ref_Hold          = COM_CHG_IBAT_REF_HOLD_INIT;//������������ʱ��ʼֵ  
    CHG_Info.iBat_Ref_SS            = CHG_Info.iBat_TC_Val;       
    CHG_Info.iBat_Ref_SS_Flag       = 0;//��������������־
    
    //VBUS���������� 
    CHG_Info.vBUS_Ref_Step_Val      = COM_CHG_VBUS_REF_STEP_VALUE;//VBUS����������ʱ��ÿ�β���ֵ       
    CHG_Info.vBUS_Ref_Shift_Val     = COM_CHG_VBUS_REF_SHIFT_VALUE; //VBUS����������ʱ������λֵ 
    CHG_Info.vBUS_Ref_Hold          = COM_CHG_VBUS_REF_HOLD_INIT;//VBUS����������ʱ��ʼֵ  
    CHG_Info.vBUS_Ref_SS            = CHG_Info.vBUS_Ref_Hold >> CHG_Info.vBUS_Ref_Shift_Val;   
    CHG_Info.out                    = 0;
    CHG_Info.vBUS_Set               = 0;
    
    CHG_Info.vBUS_Ref_Sum           = 0000;
}


/*************************************************
Description: Run_VariableInit
Input      : 
Return     : 
Others     : �Ӵ���״̬�л�����̬������ʼ��
*************************************************/
extern int32_t DISC_SS_Cnt;
void Run_VariableInit(void)
{        

    CHG_PID_VBat.out_Max    = 2;

    COM_Ctr_Info.PWM_Enable = 0;//������ʹ���ź�
    DISC_SS_Cnt = 0;
    
    BAT_START_DISABLE;
    COM_Ctr_Info.INTP3_Start_TimeVal    = 500;  //ms             
    COM_Ctr_Info.INTP3_Start_OK         = 0;    
    COM_Ctr_Info.INTP3_Start_Cnt        = 0;
    
    DC_Ctrl_Info.EPWM_DutyB             = SR_MIN_TIME;
    DC_Ctrl_Info.EPWM_Duty              = SR_MIN_TIME;
    DC_Ctrl_Info.start_Finish_State     = COM_START_FINISH_STATE_NOK;//0-����������ѹ״̬��1-������������״̬
    DC_Ctrl_Info.INV_Ready_State        = COM_INV_READY_STATE_NOK;//0�������δ׼����;1�������׼����

    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set2  = PFM_INV_VBUS_VOL_VAL_SET2;    
    DC_Ctrl_Info.AD_VBusFB_Val_Set      = PFM_AD_VBUS_FB_VAL_SET;//�趨ĸ�ߵ�ѹ����������ֵ�����ڸ�ֵ��vBusFB_AD���㣬�����趨ֵ����ʹ�ò���ֵ0~4095    
    DC_Ctrl_Info.INV_vBus_Vol_VAL_Set   = PFM_INV_VBUS_VOL_VAL_SET;//(�����ഫ���ĸ�ߵ�ѹֵ�Ƚ�)���ڸ�ĸ�ߵ�ѹֵ�л�����Ƶ��
    DC_Ctrl_Info.FRE_Switch_Cnt         = 0;//CHGƵ���л�����
    
    DC_Ctrl_Info.SR_ON_LTime          = SR_ON_LTIME;//�ͺ�xʱ�俪ͨ(lag time)
    DC_Ctrl_Info.SR_OFF_ATime         = SR_OFF_ATIME;//��ǰxʱ��ض�(ahead time)  
    DC_Ctrl_Info.DISC_SR_State        = DISC_SR_STATE;
    DC_Ctrl_Info.CHG_SR_State         = CHG_SR_STATE;
    
    DC_Ctrl_Info.CHG_PFM_Fk           = CHG_PFM_K;
    DC_Ctrl_Info.CHG_PFM_Fb           = CHG_PFM_b;
    DC_Ctrl_Info.CHG_DTime            = CHG_DEADTIME;//�������ʱ��
    DC_Ctrl_Info.DISC_DTime           = DISC_DEADTIME_WORK;
    CHG_Info.out_AVG 				  = 0;
    CHG_Info.out_AVG_Hold 			  = 0;    
    if (DC_Ctrl_Info.mode == DC_DISCHARGE)//�ŵ�ģʽ
    {

        DC_Ctrl_Info.mode_Starting        = DISC_STARTING_MODE;//������ʽ��PWM����PFM 

        DC_Ctrl_Info.EPWM_Duty_Max        = DISC_EPWM_DUTY_MAX;//��������ֵ��ȥ����ʱ��
        DC_Ctrl_Info.EPWM_Duty_Min        = DISC_EPWM_DUTY_MIN;//�����ռ�ձȵ��ڸ���ֵʱ��ֱ�Ӱ�ռ�ձȸ���Ϊ0

        
        #if (DISC_STARTING_MODE == PWM_MODE)  //��ռ�ձ�������ʼ�� 
            DC_Ctrl_Info.PWM_Duty_Step_Value      = DISC_PWM_DUTY_STEP_VALUE;//��Ƶ������ʱ��ÿ�β���ֵ       
            DC_Ctrl_Info.PWM_Duty_Shift_Value     = DISC_PWM_DUTY_SHIFT_VALUE; //��Ƶ������ʱ������λֵ    
            DC_Ctrl_Info.EPWM_Duty_Hold           = DISC_PWM_DUTY_HOLD_INIT;//ռ�ձȳ�ʼֵ����
            DC_Ctrl_Info.EPWM_Period              = DISC_PWM_PERIOD_INIT; 

        
            DC_Ctrl_Info.EPWM_Duty                = 0;    
        #else       //��Ƶ��������ʼ�� 
            DC_Ctrl_Info.PFM_Period_Step_Value   = DISC_PFM_PERIOD_STEP_VALUE;//��Ƶ������ʱ��ÿ�β���ֵ       
            DC_Ctrl_Info.PFM_Period_Shift_Value  = DISC_PFM_PERIOD_SHIFT_VALUE; //��Ƶ������ʱ������λֵ
            DC_Ctrl_Info.EPWM_Period_Max     = DISC_PFM_PERIOD_MAX;//�����������ֵ����������С����Ƶ��
            DC_Ctrl_Info.EPWM_Period_Min     = DISC_PFM_PERIOD_MIN;//������С����ֵ����������󿪹�Ƶ��
            DC_Ctrl_Info.EPWM_Period         = DISC_PFM_PERIOD_INIT;//��������ʱ������ֵ������������Ƶ��
            DC_Ctrl_Info.EPWM_Period_Work    = DISC_PFM_PERIOD_WORK;//������������ʱ������ֵ��������Ƶ��  
            DC_Ctrl_Info.EPWM_Period_Hold    = DISC_PFM_PERIOD_HOLD_INIT;//����ֵ 
            DC_Ctrl_Info.EPWM_Duty_Max_Start = DISC_PFM_DUTY_MAX_START;//����ʱ���ռ�ձ����ƣ���������ֵ��ȥ����ʱ��    
            DC_Ctrl_Info.EPWM_Duty           = 0;        
        #endif 
    }        
    else if(DC_Ctrl_Info.mode == DC_CHARGE)//���ģʽ
    {         
        DC_Ctrl_Info.mode_Starting        = CHG_STARTING_MODE;//������ʽ��PWM����PFM  
        DC_Ctrl_Info.EPWM_Duty_Max        = CHG_EPWM_DUTY_MAX;//��������ֵ��ȥ����ʱ��
        DC_Ctrl_Info.EPWM_Duty_Min        = CHG_EPWM_DUTY_MIN;//�����ռ�ձȵ��ڸ���ֵʱ��ֱ�Ӱ�ռ�ձȸ���Ϊ0
        
        #if (CHG_STARTING_MODE == PWM_MODE)  //��ռ�ձ�������ʼ�� 
            DC_Ctrl_Info.PWM_Duty_Step_Value      = CHG_PWM_DUTY_STEP_VALUE;//��Ƶ������ʱ��ÿ�β���ֵ       
            DC_Ctrl_Info.PWM_Duty_Shift_Value     = CHG_PWM_DUTY_SHIFT_VALUE; //��Ƶ������ʱ������λֵ    
            DC_Ctrl_Info.EPWM_Duty_Hold           = CHG_PWM_DUTY_HOLD_INIT;//ռ�ձȳ�ʼֵ����
            DC_Ctrl_Info.EPWM_Period              = CHG_PWM_PERIOD_INIT;          
            DC_Ctrl_Info.EPWM_Duty                = 0;      
        #endif        
    } 

    CHG_Info.allow_VBat_Val     = COM_CHG_ALLOW_VBAT_VAL;//���ڸõ�ѹ��������ɱ�־

    CHG_Info.vBat_TC_Val        = COM_CHG_VBAT_TC_VAL;//�������ص�ѹ�趨(���ڸõ�ѹ����������)
    CHG_Info.iBat_TC_Val        = COM_CHG_IBAT_TC_VAL;//�������ص����趨(���ŵ�ʹ��) 
    CHG_Info.vBat_CC_CV_Val     = COM_CHG_VBAT_CC_CV_VAL;//������ѹ���ģʽ�л��ĵ�ص�ѹ��ֵ�趨 
    CHG_Info.vBat_CV_Val        = COM_CHG_VBAT_CV_VAL;//��ѹ����ص�ѹ�趨(���ڸõ�ѹ���ú�������������ڸ�ֵ���ú�ѹ)  

    CHG_Info.iBat_CC_MaxVal     = COM_CHG_IBAT_CC_MAXVAL;//��������ص������ֵ����    
    CHG_Info.iBat_CC1_Val       = COM_CHG_IBAT_CC1_VAL;//���������ص����趨 
    CHG_Info.iBat_CC2_Val       = COM_CHG_IBAT_CC2_VAL;//С��������ص����趨     
    CHG_Info.vBat_FC_Val        = COM_CHG_VBAT_FC_VAL;//�������ص�ѹ�趨 
    CHG_Info.iBat_FC_Val        = COM_CHG_IBAT_FC_VAL;//�������ص����趨(���ڸõ������ø���)   
    CHG_Info.finish_IBat_Val    = COM_CHG_FINISH_IBAT_VAL;//�жϳ�����ʱ����ֵ   


    CHG_Info.CV_FC_Cnt          = 0;//CVתFC����ʱ 
    CHG_Info.CV_FC_Time         = COM_CHG_CV_FC_TIME;//CVתFC���ʱ������
    CHG_Info.TC_Cnt             = 0;
    CHG_Info.TC_Time            = COM_CHG_TC_TIME;
    CHG_Info.Sec_Val            = CHG_EPWM_FREQ_MAX;//PWM�ж���ʱ�����ɵ��趨ֵ
    CHG_Info.Sec_Cnt            = 0;//PWM�ж���ʱ�����ɵļ���ֵ
    
    CHG_Info.CC1_Flag           = 0;//��������ʱ���Ϊ1,0״̬Ϊ������״̬
    CHG_Info.CC2_Flag           = 0;//С�������ʱ���Ϊ1
    CHG_Info.FC_Flag            = 0;//�����ʱ���Ϊ1 
    CHG_Info.CC1_Cnt            = 0;//�������ʱ����
    CHG_Info.CC2_Cnt            = 0;//С������ʱ����
    CHG_Info.finish_OK_Cnt      = 0;//��������ʱ����      
    CHG_Info.finish_NOK_Cnt     = 0;//���δ�����ʱ����      
    
    CHG_PID_IBat.out            = 0;
    CHG_PID_VBat.out            = 0;
    CHG_PID_VBat.ref            = 0;
    CHG_PID_IBat.ref            = 0;
    CHG_Info.vBat_Ref_Hold      = 0;
    CHG_Info.iBat_Ref_Hold      = 0;
    
    //��ѹ����ʼ���ʱ������   
    CHG_Info.vBat_Ref_Step_Val  = COM_CHG_VBAT_REF_STEP_VALUE;//��ѹ��������ʱ��ÿ�β���ֵ       
    CHG_Info.vBat_Ref_Shift_Val = COM_CHG_VBAT_REF_SHIFT_VALUE; //��ѹ��������ʱ������λֵ 
    CHG_Info.vBat_Ref_Hold      = COM_CHG_VBAT_REF_HOLD_INIT;//��ѹ��������ʱ��ʼֵ  
    CHG_Info.vBat_Ref_SS        = 0;   

    //��������ʼ���ʱ������  
    CHG_Info.iBat_Ref_Step_Val  = COM_CHG_IBAT_REF_STEP_VALUE;//������������ʱ��ÿ�β���ֵ       
    CHG_Info.iBat_Ref_Shift_Val = COM_CHG_IBAT_REF_SHIFT_VALUE; //������������ʱ������λֵ 
    CHG_Info.iBat_Ref_Hold      = COM_CHG_IBAT_REF_HOLD_INIT;//������������ʱ��ʼֵ  
    CHG_Info.iBat_Ref_SS        = CHG_Info.iBat_TC_Val; 
    CHG_Info.iBat_Ref_SS_Flag   = 0;//��������������־
    
    //VBUS���������� 
    CHG_Info.vBUS_Ref_Step_Val  = COM_CHG_VBUS_REF_STEP_VALUE;//VBUS����������ʱ��ÿ�β���ֵ       
    CHG_Info.vBUS_Ref_Shift_Val = COM_CHG_VBUS_REF_SHIFT_VALUE; //VBUS����������ʱ������λֵ 
    
    CHG_Info.vBUS_Ref_Hold      = COM_CHG_VBUS_REF_HOLD_INIT;//VBUS����������ʱ��ʼֵ
    CHG_Info.vBUS_Ref_SS        = CHG_Info.vBUS_Ref_Hold >> CHG_Info.vBUS_Ref_Shift_Val;   
    CHG_Info.out                = 0; 
    CHG_Info.vBUS_Set           = 0;
    
    CHG_Info.vBUS_Ref_Sum       = 0;
}

/*-------------------------------------------------------------------------------------
 *  No more.
 *------------------------------------------------------------------------------------*/


