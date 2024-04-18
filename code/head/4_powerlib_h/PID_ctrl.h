/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

#ifndef __PID_CTRL_H
#define __PID_CTRL_H

#include "stdint.h"
#include "sys_define_config.h"

/*-------------------VBAT电流环参数------------------------------------------*/
//CHG_VBAT电压环参数
#define     CHG_VBAT_KP                                 (4096)//累加输出值（增量式PID）
#define     CHG_VBAT_KI                                 (2145*5>>2)//注意：KI和KD参数需同比例
#define     CHG_VBAT_KD                                 (-1553*5>>2)
#define     CHG_VBAT_ERR_MAX						    (5000)
#define     CHG_VBAT_ERR_MIN						    (-5000)
#define     CHG_VBAT_ERR_INTEGRAL_MAX                   (31550)    
#define     CHG_VBAT_ERR_INTEGRAL_MIN                   (-31550)
#define     CHG_VBAT_OUT_MAX                            (1)    
#define     CHG_VBAT_OUT_MIN                            (-100)
#define     CHG_VBAT_PERIOD_VALUE                       (0)//防止

/*-------------------IBAT电流环参数------------------------------------------*/
//CHG_IBAT电流环参数
#define     CHG_IBAT_KP                                 (4096)
#if 0
    //27V~37V
    #define     CHG_IBAT_KI                                 (20972*4>>5) //16.666倍  
    #define     CHG_IBAT_KD                                 (-19348*4>>5)//16.666倍 
#else
    //37V~50V
    #define     CHG_IBAT_KI                                 (20972*4>>5) //16.666倍  
    #define     CHG_IBAT_KD                                 (-19348*4>>5)//16.666倍 
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
    int32_t  ref;                   // 输入: 给定输入
    int16_t  fdb;                   // 输入: 反馈输入
    int32_t  err;                   // 变量: 当前误差
    int32_t  err_n;                 // 变量: 上次误差
    int32_t  err_n2;  			    // 变量: 上上次误差
    int32_t  err_Integral;		    // 变量: 积分累计误差	
    int32_t  kp;                    // 参数: 比例系数          
    int32_t  ki;                    // 参数: 积分系数        
    int32_t  kd; 	                // 参数: 微分系数
    int32_t  err_Max;               // 参数: 当前误差上限幅          
    int32_t  err_Min;               // 参数: 当前误差下限幅 
    int32_t  err_Integral_Max;           // 参数: 积分输出上限幅
    int32_t  err_Integral_Min;           // 参数: 积分输出下限幅
    int32_t  out_Max;          // 参数: PID输出上限幅          
    int32_t  out_Min;     	   // 参数: PID输出下限幅 
    int32_t  up;                   // 变量: 比例输出
    int32_t  ui;                   // 变量: 积分输出	
    int32_t  ud;                   // 变量: 积分输出		
    int32_t  out;                  // 变量: PID输出             
    uint16_t  ctrl_Period_Cnt;
    uint16_t  ctrl_Period_Val;    // 参数: 控制周期   
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
