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
#include "PID_ctrl.h"
/***************************************************************************/


/*************************************************
Description: PID_Ctrl
Input      : 
Return     : 
Others     : λ��ʽPID�����߼�
*************************************************/
void PID_Ctrl(PID_Ctrl_Var_t *PID_Info)
{   
    PID_Info->err_n = PID_Info->err; 
    PID_Info->err = PID_Info->ref - PID_Info->fdb;
    
    PID_Info->ctrl_Period_Cnt ++;//���������ۼ� 
    if(PID_Info->ctrl_Period_Cnt >= PID_Info->ctrl_Period_Val)    
    {
        PID_Info->ctrl_Period_Cnt = 0;//�������ڼ���ֵ��0       

        //�������
//        if ( PID_Info->err > PID_Info->err_Max ) PID_Info->err = PID_Info->err_Max;
//        if ( PID_Info->err < PID_Info->err_Min ) PID_Info->err = PID_Info->err_Min;

        //��������ۼ�
        PID_Info->err_Integral += PID_Info->err;    
        //�����޷�
        if(PID_Info->err_Integral >= PID_Info->err_Integral_Max)
        {
            PID_Info->err_Integral = PID_Info->err_Integral_Max;
        }
        if(PID_Info->err_Integral < PID_Info->err_Integral_Min)
        {
            PID_Info->err_Integral = PID_Info->err_Integral_Min;
        }

        PID_Info->up = (PID_Info->kp  * PID_Info->err) >> 12; //������������
        PID_Info->ui = (PID_Info->ki  * PID_Info->err_Integral) >> 12;//���ֲ�������  
        PID_Info->ud =  PID_Info->kd  * (PID_Info->err - PID_Info->err_n )>>12;//΢�ֲ�������
        /*------------------------------------------------------------------------------------*/
        PID_Info->out = (PID_Info->up + PID_Info->ui + PID_Info->ud);
        

        /*----------------------------------PID����޷�--------------------------------------------*/
        if ( PID_Info->out > PID_Info->out_Max ) PID_Info->out = PID_Info->out_Max;
        if ( PID_Info->out < PID_Info->out_Min ) PID_Info->out = PID_Info->out_Min;
    }    
}

/*************************************************
Description: PID_Increase_Ctrl
Input      : 
Return     : 
Others     : ����ʽPID�����߼�
*************************************************/
void PID_Increase_Ctrl(PID_Ctrl_Var_t *PID_Info)
{    
    PID_Info->ctrl_Period_Cnt ++;//���������ۼ� 
    if(PID_Info->ctrl_Period_Cnt >= PID_Info->ctrl_Period_Val)    
    {
        PID_Info->ctrl_Period_Cnt = 0;//�������ڼ���ֵ��0
            
        PID_Info->err_n2    = PID_Info->err_n;
        PID_Info->err_n     = PID_Info->err; 
        PID_Info->err       = PID_Info->ref - PID_Info->fdb;

        //�������
        if ( PID_Info->err > PID_Info->err_Max ) PID_Info->err = PID_Info->err_Max;
        if ( PID_Info->err < PID_Info->err_Min ) PID_Info->err = PID_Info->err_Min;

        PID_Info->up = PID_Info->kp *(PID_Info->err - PID_Info->err_n) >> 15; //������������
        PID_Info->ui = PID_Info->ki * PID_Info->err >> 15;//���ֲ�������  
        PID_Info->ud = PID_Info->kd *(PID_Info->err - 2* PID_Info->err_n + PID_Info->err_n2)>>15;//΢�ֲ�������
        /*------------------------------------------------------------------------------------*/
        PID_Info->out = (PID_Info->up + PID_Info->ui + PID_Info->ud);
        
        /*----------------------------------PID����޷�--------------------------------------------*/
        if ( PID_Info->out > PID_Info->out_Max ) PID_Info->out = PID_Info->out_Max;
        if ( PID_Info->out < PID_Info->out_Min ) PID_Info->out = PID_Info->out_Min; 
    }      
    

}

/*************************************************
Description: 
Input      : 
Return     : 
Others     : 
*************************************************/
void PID_NEW_Ctrl(PID_Ctrl_Var_t *PID_Info)
{    
    PID_Info->err_n = PID_Info->err; 
    PID_Info->err = PID_Info->ref - PID_Info->fdb;
    
    PID_Info->ctrl_Period_Cnt ++;//���������ۼ� 
    if(PID_Info->ctrl_Period_Cnt >= PID_Info->ctrl_Period_Val)    
    {
        PID_Info->ctrl_Period_Cnt = 0;//�������ڼ���ֵ��0            

        //�������
//        if ( PID_Info->err > PID_Info->err_Max ) PID_Info->err = PID_Info->err_Max;
//        if ( PID_Info->err < PID_Info->err_Min ) PID_Info->err = PID_Info->err_Min;

        PID_Info->up = PID_Info->kp *(PID_Info->out) ;//
        PID_Info->ui = PID_Info->ki * PID_Info->err ;//  
        PID_Info->ud = PID_Info->kd *(PID_Info->err_n);
        /*------------------------------------------------------------------------------------*/
        PID_Info->out = (PID_Info->up + PID_Info->ui + PID_Info->ud)>>12;
        
        /*----------------------------------PID����޷�--------------------------------------------*/
        if ( PID_Info->out > PID_Info->out_Max ) PID_Info->out = PID_Info->out_Max;
        if ( PID_Info->out < PID_Info->out_Min ) PID_Info->out = PID_Info->out_Min; 
    }            
      
}



//#pragma arm section
