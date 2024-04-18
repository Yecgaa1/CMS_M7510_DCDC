/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

#ifndef __PID_CTRL_H
#define __PID_CTRL_H

#include "stdint.h"
#include "sys_define_config.h"

/*-------------------VBAT����������------------------------------------------*/
//CHG_VBAT��ѹ������
#define     CHG_VBAT_KP                                 (4096)//�ۼ����ֵ������ʽPID��
#define     CHG_VBAT_KI                                 (2145*5>>2)//ע�⣺KI��KD������ͬ����
#define     CHG_VBAT_KD                                 (-1553*5>>2)
#define     CHG_VBAT_ERR_MAX						    (5000)
#define     CHG_VBAT_ERR_MIN						    (-5000)
#define     CHG_VBAT_ERR_INTEGRAL_MAX                   (31550)    
#define     CHG_VBAT_ERR_INTEGRAL_MIN                   (-31550)
#define     CHG_VBAT_OUT_MAX                            (1)    
#define     CHG_VBAT_OUT_MIN                            (-100)
#define     CHG_VBAT_PERIOD_VALUE                       (0)//��ֹ

/*-------------------IBAT����������------------------------------------------*/
//CHG_IBAT����������
#define     CHG_IBAT_KP                                 (4096)
#if 0
    //27V~37V
    #define     CHG_IBAT_KI                                 (20972*4>>5) //16.666��  
    #define     CHG_IBAT_KD                                 (-19348*4>>5)//16.666�� 
#else
    //37V~50V
    #define     CHG_IBAT_KI                                 (20972*4>>5) //16.666��  
    #define     CHG_IBAT_KD                                 (-19348*4>>5)//16.666�� 
#endif

#define     CHG_IBAT_ERR_MAX						    (5000)
#define     CHG_IBAT_ERR_MIN						    (-5000)
#define     CHG_IBAT_ERR_INTEGRAL_MAX                   (31550)    
#define     CHG_IBAT_ERR_INTEGRAL_MIN                   (0)
#define     CHG_IBAT_OUT_MAX                            (4096)   
#define     CHG_IBAT_OUT_MIN                            (0)
#define     CHG_IBAT_PERIOD_VALUE                       (0)


/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
typedef struct 
{ 
    int32_t  ref;                   // ����: ��������
    int16_t  fdb;                   // ����: ��������
    int32_t  err;                   // ����: ��ǰ���
    int32_t  err_n;                 // ����: �ϴ����
    int32_t  err_n2;  			    // ����: ���ϴ����
    int32_t  err_Integral;		    // ����: �����ۼ����	
    int32_t  kp;                    // ����: ����ϵ��          
    int32_t  ki;                    // ����: ����ϵ��        
    int32_t  kd; 	                // ����: ΢��ϵ��
    int32_t  err_Max;               // ����: ��ǰ������޷�          
    int32_t  err_Min;               // ����: ��ǰ������޷� 
    int32_t  err_Integral_Max;           // ����: ����������޷�
    int32_t  err_Integral_Min;           // ����: ����������޷�
    int32_t  out_Max;          // ����: PID������޷�          
    int32_t  out_Min;     	   // ����: PID������޷� 
    int32_t  up;                   // ����: �������
    int32_t  ui;                   // ����: �������	
    int32_t  ud;                   // ����: �������		
    int32_t  out;                  // ����: PID���             
    uint16_t  ctrl_Period_Cnt;
    uint16_t  ctrl_Period_Val;    // ����: ��������   
   void  (*Calc)();	/* Pointer to calculation function */                          
} PID_Ctrl_Var_t;

               
#define CHG_VBAT_LOOP_DEFAULTS {0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                CHG_VBAT_KP,         \
                                CHG_VBAT_KI,         \
                                CHG_VBAT_KD,         \
                                CHG_VBAT_ERR_MAX,     \
                                CHG_VBAT_ERR_MIN,     \
                                CHG_VBAT_ERR_INTEGRAL_MAX,  \
                                CHG_VBAT_ERR_INTEGRAL_MIN,  \
                                CHG_VBAT_OUT_MAX,     \
                                CHG_VBAT_OUT_MIN,     \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                CHG_VBAT_PERIOD_VALUE,    \
                                (void (*)( unsigned int ))PID_Ctrl}

                                                                
#define CHG_IBAT_LOOP_DEFAULTS {0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                CHG_IBAT_KP,         \
                                CHG_IBAT_KI,         \
                                CHG_IBAT_KD,         \
                                CHG_IBAT_ERR_MAX,     \
                                CHG_IBAT_ERR_MIN,     \
                                CHG_IBAT_ERR_INTEGRAL_MAX,  \
                                CHG_IBAT_ERR_INTEGRAL_MIN,  \
                                CHG_IBAT_OUT_MAX,     \
                                CHG_IBAT_OUT_MIN,     \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                0,                            \
                                CHG_IBAT_PERIOD_VALUE,    \
                                (void (*)( unsigned int ))PID_Ctrl}

                                                                
extern PID_Ctrl_Var_t CHG_PID_VBat; 
extern PID_Ctrl_Var_t CHG_PID_IBat;                                  
void PID_Ctrl(PID_Ctrl_Var_t *PID_Info);
void PID_NEW_Ctrl(PID_Ctrl_Var_t *PID_Info);                           
                                  
                            
#endif 
/*-------------------------------------------------------------------------------------
 *  No more.
 *------------------------------------------------------------------------------------*/
