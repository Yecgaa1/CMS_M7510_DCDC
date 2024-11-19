
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/


#ifndef __SYS_DEFINE_PARAR_H
#define	__SYS_DEFINE_PARAR_H

/****************************************************************************/
/*	include files
*****************************************************************************/
#include "sys_define_config.h"
/****************************************************************************/
/*-------------------通信参数设置-------------------------------------------*/
#define UART0_HEART_VAL                                 (300)  
#define UART0_SEND_PERIOD_VAL                           (20)//发送间隔时间设定(ms)  1/(19200)Baud*10*30
#define UART0_SEND_NUM                                  (30)//2字节帧头+12字节数据位+2字节校验位
#define UART0_RECE_NUM                                  (UART0_SEND_NUM*2)//


#define COM_START_FINISH_STATE_NOK                      (0)//启机未完成，处于启机升压状态
#define COM_START_FINISH_STATE_OK                       (1)//启机完成，处于正常工作状态
#define COM_INV_READY_STATE_NOK                         (0)//逆变侧未准备好
#define COM_INV_READY_STATE_OK                          (1)//逆变侧准备好


/*-------------------放电升压启机参数设置-----------------------------------*/
#define PFM_AD_VBUS_FB_VAL_SET                          (1990)//设定母线电压控制反馈阈值：低于该值缓启完成
//注意：INV侧传输的真实母线电压值：放大10倍
#if 1  //输出230V
    #define PFM_INV_VBUS_VOL_VAL_SET2                   (360*10)//大于该母线电压值无需缓启动升压
    #define PFM_INV_VBUS_VOL_VAL_SET_SS                 (150*10)//变频率模式使用
    #if OPERATING_MODE == TEST_MODE
        #define PFM_INV_VBUS_VOL_VAL_SET                (0*10)//小于该母线电压值以初始占空比运行升压
    #else
        #define PFM_INV_VBUS_VOL_VAL_SET                (250*10)//小于该母线电压值以初始占空比运行升压
    #endif
#else   //输出110V
    #define PFM_INV_VBUS_VOL_VAL_SET2                   (150*10)//大于该母线电压值无需缓启动升压
    #define PFM_INV_VBUS_VOL_VAL_SET_SS                 (150*10)//变频率模式使用
    #if OPERATING_MODE == TEST_MODE
        #define PFM_INV_VBUS_VOL_VAL_SET                (0*10)//小于该母线电压值以初始占空比运行升压
    #else
        #define PFM_INV_VBUS_VOL_VAL_SET                (140*10)//小于该母线电压值以初始占空比运行升压
    #endif    
#endif


/***************************************************************************
* 锂电池说明
* 铅酸电池电压范围：标称电压12V，每块充满最高电压14.4V，放完电到10.5V；
* 磷酸铁锂(LFP)电池电压范围：标称电压3.2V，每块充满最高电压3.6V，放完电到2.5V；
* 三元锂电电池电压范围：标称电压3.6V，每块充满最高电压4.1V，放完电到2.8V；
* 三元，是因为采用三种元素：镍钴锰（NCM）或是镍钴铝（NCA）作为正极材料
***************************************************************************/
#define COM_LFP_VBAT_S_MIN                              (2.50)//单节磷酸铁锂电池最低电压    
#define COM_LFP_VBAT_S_MAX                              (3.65)//单节磷酸铁锂电池最高电压 
#define COM_NCM_VBAT_S_MIN                              (3.29)//单节三元铁锂电池最低电压    3.15
#define COM_NCM_VBAT_S_MAX                              (3.78)//单节三元铁锂电池最高电压    4.15

/*-------------------锂电池类型选择-----------------------------------------*/
#define COM_LFP_BAT                                     (0)//锂电池类型为磷酸铁锂
#define COM_NCM_BAT                                     (1)//锂电池类型为三元锂电
#define COM_BAT_TYPE_SELECT                             (COM_NCM_BAT)//锂电池类型选择

/*-------------------锂电池串数/主变匝比选择--------------------------------*/
#if 0
    #define N2_N1_RATIO                                 (39/3)//主变压器匝数比
    #define COM_BAT_NUM_SET                             (10)//锂电池串数
#else
	#define N2_N1_RATIO                                 (25/3)//主变压器匝数比
    #define COM_BAT_NUM_SET                             (14)//锂电池串数
#endif

#if (COM_BAT_TYPE_SELECT == COM_LFP_BAT)//磷酸铁锂电池
    #define COM_VBAT_MAX_VAL                            (COM_BAT_NUM_SET * COM_LFP_VBAT_S_MAX )//最高电池电压设定(V)  
    #define COM_VBAT_MIN_VAL                            (COM_BAT_NUM_SET * COM_LFP_VBAT_S_MIN )//最低电池电压设定(V) 
    #define COM_VBAT_VALBACK                            ( 0.3)//保护使用的回差值    
#else   //三元锂电池
    #define COM_VBAT_MAX_VAL                            (COM_BAT_NUM_SET * COM_NCM_VBAT_S_MAX )//最高电池电压设定(V)  
    #define COM_VBAT_MIN_VAL                            (COM_BAT_NUM_SET * COM_NCM_VBAT_S_MIN )//最低电池电压设定(V)
    #define COM_VBAT_VALBACK                            ( 0.3)//保护使用的回差值        
#endif


/*-------------------充电电流和电压参数设定---------------------------------*/
#define COM_CHG_IBAT_MAX_VAL                            (10.0)//恒流充电最大充电电流设定(A)
#define COM_CHG_VBAT_MAX_VAL                            (COM_VBAT_MAX_VAL - 0.3 )//恒压充电最高电池电压设定(V) 
#define COM_CHG_VBAT_MIN_VAL                            (COM_VBAT_MIN_VAL - 0.0 )//恒压充电最低电池电压设定(V)  

#define COM_CHG_TC_TIME                                 (5)//涓流充电时间设置(s)
#define COM_CHG_CV_FC_TIME                              (10)//CV转FC充电延时时间设置 (s)

#define COM_CHG_ALLOW_VBAT_VAL                          (int32_t)(((COM_CHG_VBAT_MAX_VAL-1.8) * 4096) / COM_VBAT_BASE)//低于该电压清除充电完成标志
#define COM_CHG_VBAT_TC_VAL                             (int32_t)(((COM_CHG_VBAT_MIN_VAL+1.0) * 4096) / COM_VBAT_BASE)//涓流充电电池电压设定(低于该电压启用涓流充电)
#define COM_CHG_VBAT_CC_CV_VAL                          (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.8) * 4096) / COM_VBAT_BASE)//判断恒流恒压充电的电池电压阈值设定
#define COM_CHG_VBAT_FC_VAL                             (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.3) * 4096) / COM_VBAT_BASE)//浮充充电电池电压设定 
#define COM_CHG_VBAT_CV_VAL                             (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.3) * 4096) / COM_VBAT_BASE)//恒压充电电池电压设定  

#define COM_CHG_IBAT_STEP_VAL                           (int32_t)(0.04  * COM_IBAT_CHG_SCAL)//恒流充电时电流步进值（恒压降电流时）
#define COM_CHG_IBAT_MIN_VAL                            (int32_t)(1.2 * COM_IBAT_CHG_SCAL)//恒流充电时最小电流点

#define COM_CHG_IBAT_CC1_VAL                            (int32_t)((COM_CHG_IBAT_MAX_VAL-0.0 ) * COM_IBAT_CHG_SCAL)//恒流充电电池电流设定
#define COM_CHG_IBAT_CC_MAXVAL                          (int32_t)(COM_CHG_IBAT_CC1_VAL)//恒流充电电池电流最大值限制
#define COM_CHG_IBAT_CC2_VAL                            (int32_t)((COM_CHG_IBAT_MAX_VAL-0.5 ) * COM_IBAT_CHG_SCAL)//低于该充电电流进入逐渐降低恒流值
#define COM_CHG_IBAT_TC_VAL                             (int32_t)((COM_CHG_IBAT_MAX_VAL*0.06) * COM_IBAT_CHG_SCAL)//涓流充电电池电流设定(过放电使用) 
#define COM_CHG_IBAT_FC_VAL                             (int32_t)((COM_CHG_IBAT_MAX_VAL*0.05) * COM_IBAT_CHG_SCAL)//浮充充电电池电流设定(低于该电流启用浮充)  
#define COM_CHG_FINISH_IBAT_VAL                         (int32_t)((COM_CHG_IBAT_MAX_VAL*0.045) * COM_IBAT_CHG_SCAL)//判断充电结束时电流值  

#define COM_CHG_FINISH_OK                               (1)//充电已经完成，充满状态
#define COM_CHG_FINISH_NOK                              (0)//充电未完成，未充满状态
#define COM_CHG_FINISH_OK_TIME                          (20000)//充电完成延时时间(ms)
#define COM_CHG_FINISH_NOK_TIME                         (10000)//充电未完成延时时间

//电压环开始充电时缓启动   
#define COM_CHG_VBAT_REF_INIT                           (int32_t)((40.0 * 4096) / COM_VBAT_BASE)
#define COM_CHG_VBAT_REF_STEP_VALUE                     (10)//每次步进值
#define COM_CHG_VBAT_REF_SHIFT_VALUE                    (12)//启动时缩放移位值
#define COM_CHG_VBAT_REF_HOLD_INIT                      (COM_CHG_VBAT_REF_INIT << COM_CHG_VBAT_REF_SHIFT_VALUE)//放大后的变占空比初始值

//电流环开始充电时给定ref缓启动   
#define COM_CHG_IBAT_REF_PEIROD                         (32)//每次步进周期值(ms)
#define COM_CHG_IBAT_REF_STEP_VALUE                     (600)//每次步进值
#define COM_CHG_IBAT_REF_SHIFT_VALUE                    (7)//缩放移位值
#define COM_CHG_IBAT_REF_HOLD_INIT                      (51 << COM_CHG_IBAT_REF_SHIFT_VALUE)//放大后的初始值

//V_PFC给定缓启动
#define COM_CHG_VBUS_REF_STEP_VALUE                     (4000)//变占空比启机时，每次步进值
#define COM_CHG_VBUS_REF_SHIFT_VALUE                    (12)//变占空比启动时缩放移位值
#define COM_CHG_VBUS_REF_INIT                           (385*4)//母线电压初始给定值为385V
#define COM_CHG_VBUS_REF_HOLD_INIT                      (COM_CHG_VBUS_REF_INIT << COM_CHG_VBUS_REF_SHIFT_VALUE)//放大后的变占空比初始值
#define COM_CHG_VBUS_REF_MAX                            (485*4)//母线电压给定最大值为485V
#define COM_CHG_VBUS_REF_HOLD_MAX                       (COM_CHG_VBUS_REF_MAX << COM_CHG_VBUS_REF_SHIFT_VALUE)//放大后的变占空比初始值
//给定PFC侧母线电压相关参数设置 
#define CHG_OUT_MIN                                     (2200)//根据实际情况调整,保证工作在谐振点
#define CHG_OUT_MAX                                     (2260)//根据实际情况调整,保证工作在谐振点 


/*------------------------------------------------------------------------------------*/
//辅助电源上下限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_AUX_POWER_MAX                               ( 9.0)
#define COM_AUX_POWER_MIN                               ( 5.2)
#define COM_AUX_POWER_VALBACK                           ( 0.3)//保护使用的回差值
/*------------------------------------------------------------------------------------*/
//开机检测辅助电源参数设置
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_AUX_POWER_UP                    (int32_t)( COM_AUX_POWER_MAX * COM_REAL_AUXPOWER_SCAL)//转换为与AD采样值统一单位进行比较   
#define COM_START_CHECK_AUX_POWER_UP_BACK               (int32_t)((COM_AUX_POWER_MAX + COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)
#define COM_START_CHECK_AUX_POWER_UP_TIME		        (700)//延时时间(ms)

#define COM_START_CHECK_AUX_POWER_DOWN                  (int32_t)( COM_AUX_POWER_MIN * COM_REAL_AUXPOWER_SCAL)//转换为与AD采样值统一单位进行比较	
#define COM_START_CHECK_AUX_POWER_DOWN_BACK             (int32_t)((COM_AUX_POWER_MIN - COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)
#define COM_START_CHECK_AUX_POWER_DOWN_TIME			    (700)//延时时间(ms)


/*------------------------------------------------------------------------------------*/
//开机检测电池电压参数设置
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_VBAT_UP                         (int32_t)((COM_VBAT_MAX_VAL) * COM_REAL_VBAT_SCAL)//转换为与AD采样值统一单位进行比较   
#define COM_START_CHECK_VBAT_UP_BACK                    (int32_t)((COM_VBAT_MAX_VAL+COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)
#define COM_START_CHECK_VBAT_UP_TIME		            (700)//延时时间(ms)

#define COM_START_CHECK_VBAT_DOWN                       (int32_t)((COM_VBAT_MIN_VAL) * COM_REAL_VBAT_SCAL)//转换为与AD采样值统一单位进行比较	
#define COM_START_CHECK_VBAT_DOWN_BACK                  (int32_t)((COM_VBAT_MIN_VAL-COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)
#define COM_START_CHECK_VBAT_DOWN_TIME			        (700)//延时时间(ms)

/*------------------------------------------------------------------------------------*/
//开机检测温度参数设置
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_TEMP_UP_RES                     (2.240)//设定温度70℃对应NTC电阻值(KΩ)
#define COM_START_CHECK_TEMP_UP_BACK_RES                (1.678)//设定温度80℃对应NTC电阻值(KΩ)
#define COM_START_CHECK_TEMP_UP                         (int32_t)((COM_START_CHECK_TEMP_UP_RES/(COM_START_CHECK_TEMP_UP_RES+HW_TEMP_DIVIDE_RES)*4096))  
#define COM_START_CHECK_TEMP_UP_BACK                    (int32_t)((COM_START_CHECK_TEMP_UP_BACK_RES/(COM_START_CHECK_TEMP_UP_BACK_RES+HW_TEMP_DIVIDE_RES)*4096)) 
#define COM_START_CHECK_TEMP_UP_TIME		            (700)//延时时间(ms)


/*------------------------------------------------------------------------------------*/
//充电过载上限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_CHG_POWER_MAX1                              (1500)//(W)
#define COM_CHG_POWER_MAX2                              (1500)//(W)
#define COM_CHG_POWER_VALBACK                           ( 30)//保护使用的回差值(W)
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
//充电过载参数设置
/*------------------------------------------------------------------------------------*/
#define COM_CHG_OLP1_TIME                               (5000)//延时时间(ms)   
#define COM_CHG_OLP2_TIME                               (5000)//延时时间(ms)    
#define COM_CHG_OLP1_VAL                                (COM_CHG_POWER_MAX1)//(W)      
#define COM_CHG_OLP2_VAL                                (COM_CHG_POWER_MAX2)//(W)      
#define COM_CHG_OLP1_VAL_BACK                           (COM_CHG_POWER_MAX1 - COM_CHG_POWER_VALBACK)//(W)
#define COM_CHG_OLP2_VAL_BACK                           (COM_CHG_POWER_MAX2 - COM_CHG_POWER_VALBACK)//(W)

/*------------------------------------------------------------------------------------*/
//放电过载上限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_DISC_POWER_MAX1                             (3500)//(W)
#define COM_DISC_POWER_MAX2                             (3500)//(W)
#define COM_DISC_POWER_VALBACK                          ( 30)//保护使用的回差值(W)
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
//放电过载参数设置
/*------------------------------------------------------------------------------------*/
#define COM_DISC_OLP1_TIME	                            (5000)//延时时间(ms)     
#define COM_DISC_OLP2_TIME	                            (5000)//延时时间(ms)  
#define COM_DISC_OLP1_VAL	                            (COM_DISC_POWER_MAX1)//(W)      
#define COM_DISC_OLP2_VAL	                            (COM_DISC_POWER_MAX2)//(W) 
#define COM_DISC_OLP1_VAL_BACK	                        (COM_DISC_POWER_MAX1 - COM_DISC_POWER_VALBACK)//(W)
#define COM_DISC_OLP2_VAL_BACK	                        (COM_DISC_POWER_MAX2 - COM_DISC_POWER_VALBACK)//(W)

/***************************************************************************/
//辅助电源过压/欠压设置
/***************************************************************************/
#define COM_AUX_POWER_OVP_TIME                          (100)//保时时间(ms))
#define COM_AUX_POWER_OVP_VAL                           (int32_t)( COM_AUX_POWER_MAX * COM_REAL_AUXPOWER_SCAL)//转换为与AD采样值统一单位进行比较   
#define COM_AUX_POWER_OVP_VAL_BACK                      (int32_t)((COM_AUX_POWER_MAX - COM_AUX_POWER_VALBACK)* COM_REAL_AUXPOWER_SCAL)   

#define COM_AUX_POWER_LVP_TIME                          (200)//延时时间(ms) 
#define COM_AUX_POWER_LVP_VAL                           (int32_t)( COM_AUX_POWER_MIN * COM_REAL_AUXPOWER_SCAL)//转换为与AD采样值统一单位进行比较    
#define COM_AUX_POWER_LVP_VAL_BACK                      (int32_t)((COM_AUX_POWER_MIN + COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)

/***************************************************************************/
//电池电压过压/欠压设置
/***************************************************************************/
#define COM_VBAT_OVP_TIME                               (500)//保时时间(ms))
#define COM_VBAT_OVP_VAL                                (int32_t)((COM_VBAT_MAX_VAL) * COM_REAL_VBAT_SCAL)//转换为与AD采样值统一单位进行比较   
#define COM_VBAT_OVP_VAL_BACK                           (int32_t)((COM_VBAT_MAX_VAL-COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)   

#define COM_VBAT_LVP1_TIME                              (100)//延时时间(ms) 
#define COM_VBAT_LVP1_VAL                               (int32_t)((COM_VBAT_MIN_VAL) * COM_REAL_VBAT_SCAL)//转换为与AD采样值统一单位进行比较    
#define COM_VBAT_LVP1_VAL_BACK                          (int32_t)((COM_VBAT_MIN_VAL+COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)

#define COM_VBAT_LVP2_TIME                              (10)//延时时间(ms) 
#define COM_VBAT_LVP2_VAL                               (int32_t)((COM_VBAT_MIN_VAL-4.0) * COM_REAL_VBAT_SCAL)//转换为与AD采样值统一单位进行比较    
#define COM_VBAT_LVP2_VAL_BACK                          (int32_t)((COM_VBAT_MIN_VAL-3.7) * COM_REAL_VBAT_SCAL)


/***************************************************************************/
//过温设置
/***************************************************************************/	
#define COM_OTP1_TIME                                   (500)//延时时间(ms)
#define COM_OTP2_TIME                                   (500)//延时时间(ms)
#define COM_OTP1_RES                                    (1.678)//设定温度80℃对应NTC电阻值(KΩ)
#define COM_OTP2_RES                                    (1.275)//设定温度90℃对应NTC电阻值(KΩ)
#define COM_OTP1_BACK_RES                               (2.240)//设定温度70℃对应NTC电阻值(KΩ)
#define COM_OTP2_BACK_RES                               (2.240)//设定温度70℃对应NTC电阻值(KΩ)                          
#define COM_OTP1_VAL                                    (int32_t)((COM_OTP1_RES/(COM_OTP1_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP2_VAL                                    (int32_t)((COM_OTP2_RES/(COM_OTP2_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP1_VAL_BACK                               (int32_t)((COM_OTP1_BACK_RES/(COM_OTP1_BACK_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP2_VAL_BACK                               (int32_t)((COM_OTP2_BACK_RES/(COM_OTP2_BACK_RES+HW_TEMP_DIVIDE_RES)*4096))	
/***************************************************************************/
/***************************************************************************/

/*------------------------------------------------------------------------------------*/
//VREF参考电压上下限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_VREF_MAX                                    (2248)
#define COM_VREF_MIN                                    (1848)
#define COM_VREF_VALBACK                                ( 80)//保护使用的回差值
/*------------------------------------------------------------------------------------*/
/***************************************************************************/
//VREF参考电压保护点设置
/***************************************************************************/	
#define COM_VREF_OVP_TIME                               (10)//延时时间(ms)
#define COM_VREF_OVP_VAL                                (COM_VREF_MAX)//
#define COM_VREF_OVP_VAL_BACK                           (COM_VREF_MAX - COM_VREF_VALBACK)

#define COM_VREF_LVP_TIME                               (10)//延时时间(ms)
#define COM_VREF_LVP_VAL                                (COM_VREF_MIN)//
#define COM_VREF_LVP_VAL_BACK                           (COM_VREF_MIN + COM_VREF_VALBACK)	
/***************************************************************************/
/***************************************************************************/


/*------------------------------------------------------------------------------------*/
//电池充电电流保护上限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_CHG_IBAT_OCP1                               (45.0)//(A)
#define COM_CHG_IBAT_OCP2                               (45.0)//(A)
#define COM_CHG_IBAT_CP_VALBACK                         ( 1.0)//保护使用的回差值(A)
/*------------------------------------------------------------------------------------*/
//充电过流参数设置
/*------------------------------------------------------------------------------------*/
#define CHG_IBAT_OCP1_TIME                              (50)//延时时间(ms)
#define CHG_IBAT_OCP2_TIME                              (50)//延时时间(ms)
#define CHG_IBAT_OCP1_VAL                               (COM_CHG_IBAT_OCP1 * COM_REAL_IBAT_CHG_SCAL)//真实电流放大：COM_REAL_IBAT_CHG_SCAL
#define CHG_IBAT_OCP2_VAL                               (COM_CHG_IBAT_OCP2 * COM_REAL_IBAT_CHG_SCAL)   
#define CHG_IBAT_OCP1_VAL_BACK                          ((COM_CHG_IBAT_OCP1 - COM_CHG_IBAT_CP_VALBACK) * COM_REAL_IBAT_CHG_SCAL)//
#define CHG_IBAT_OCP2_VAL_BACK                          ((COM_CHG_IBAT_OCP2 - COM_CHG_IBAT_CP_VALBACK) * COM_REAL_IBAT_CHG_SCAL) 

/*------------------------------------------------------------------------------------*/
//电池放电电流保护上限参数设置
/*------------------------------------------------------------------------------------*/
#define COM_DISC_IBAT_OCP1                              (100.0)//(A)
#define COM_DISC_IBAT_OCP2                              (100.0)//(A)
#define COM_DISC_IBAT_CP_VALBACK                        (  1.0)//保护使用的回差值(A)
/*------------------------------------------------------------------------------------*/
//放电过流参数设置
/*------------------------------------------------------------------------------------*/
#define DISC_IBAT_OCP1_TIME                             (50)//延时时间(ms)
#define DISC_IBAT_OCP2_TIME                             (50)//延时时间(ms)
#define DISC_IBAT_OCP1_VAL                              (COM_DISC_IBAT_OCP1 * COM_REAL_IBAT_DISC_SCAL)//真实电流放大：COM_REAL_IBAT_DISC_SCAL
#define DISC_IBAT_OCP2_VAL                              (COM_DISC_IBAT_OCP2 * COM_REAL_IBAT_DISC_SCAL) 
#define DISC_IBAT_OCP1_VAL_BACK                         ((COM_DISC_IBAT_OCP1 - COM_DISC_IBAT_CP_VALBACK) * COM_REAL_IBAT_DISC_SCAL)   
#define DISC_IBAT_OCP2_VAL_BACK                         ((COM_DISC_IBAT_OCP2 - COM_DISC_IBAT_CP_VALBACK) * COM_REAL_IBAT_DISC_SCAL)   


/*------------------------------------------------------------------------------------*/
//AD参考校准值参数设置
/*------------------------------------------------------------------------------------*/
#define COM_BASE_AD_CORRECT_VAL                         (2048)//预设基准值
#define COM_BASE_AD_CORRECT_VALBACK                     ( 100)
//--------------------------------------------------------------------
/*VREF_AD校正值*/
//--------------------------------------------------------------------
#define COM_VREF_AD_CORRECT_UP                          (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_VREF_AD_CORRECT_MID                         (COM_BASE_AD_CORRECT_VAL)
#define COM_VREF_AD_CORRECT_DN                          (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------
/*电池充电电流开机AD校正值*/
//--------------------------------------------------------------------
#define COM_CHG_IBat_AD_CORRECT_UP                      (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_CHG_IBat_AD_CORRECT_MID                     (COM_BASE_AD_CORRECT_VAL)
#define COM_CHG_IBat_AD_CORRECT_DN                      (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------
/*电池放电电流开机AD校正值*/
//--------------------------------------------------------------------
#define COM_DISC_IBat_AD_CORRECT_UP                     (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_DISC_IBat_AD_CORRECT_MID                    (COM_BASE_AD_CORRECT_VAL)
#define COM_DISC_IBat_AD_CORRECT_DN                     (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------


/*-------------------开机延时时间设定值（电源锁）--------------------------*/
#define COM_POWER_LOCK_TIME                             (1000)//ms

/***************************************************************************/
//按键定义设置 
/***************************************************************************/ 
#define COM_KEY_SHUT_DOWN_ACTIVE_LEVEL                  (0)//有效电平设置0或者1
#define COM_KEY_SHUT_DOWN_C_DELAY_COUNT                 (1000)//按下消抖延时时间(ms)
#define COM_KEY_SHUT_DOWN_R_DELAY_COUNT                 (100)//松开消抖延时时间(ms)

#define COM_KEY_RESET_ACTIVE_LEVEL                      (0)//有效电平设置0或者1
#define COM_KEY_RESET_C_DELAY_COUNT                     (200)//按下消抖延时时间(ms)
#define COM_KEY_RESET_R_DELAY_COUNT                     (200)//松开消抖延时时间(ms)


/***************************************************************************/
//开启、关闭风扇温度阈值设置
/***************************************************************************/
#define COM_OPEN_FAN_TEMP_VALUE                         (1565)//高于45℃，开启风扇
#define COM_CLOSE_FAN_TEMP_VALUE                        (1786)//低于35℃，关闭风扇

/***************************************************************************/
//根据充放电电流打开风扇
/***************************************************************************/
#define COM_OPEN_FAN_CHG_IBAT_VALUE                     (1.5 * COM_REAL_IBAT_CHG_SCAL)//，开启风扇
#define COM_OPEN_FAN_DISC_IBAT_VALUE                    (1.5 * COM_REAL_IBAT_DISC_SCAL)//开启风扇
#define COM_CLOSE_FAN_CHG_IBAT_VALUE                    (1.4 * COM_REAL_IBAT_CHG_SCAL)//，关闭风扇
#define COM_CLOSE_FAN_DISC_IBAT_VALUE                   (1.4 * COM_REAL_IBAT_DISC_SCAL)//关闭风扇

#endif 
