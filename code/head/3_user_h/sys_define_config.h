
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

#ifndef __SYS_DEFINE_CONFIG_H
#define	__SYS_DEFINE_CONFIG_H

#include "BAT32G439.h"
/***************************************************************************/
/*-------------------EPWM开关周期设置--------------------------------------*/
/***************************************************************************/
#define MCU_CLK 	                    (128000000L)//MCU主频
#define DEADTIME			            ((int32_t)((0 * MCU_CLK)) / 1000000L)

/***************************************************************************/
/*-------------------CHG模式：工作、启机频率、死区时间设置-----------------*/
/***************************************************************************/
//注意：需扫频确定充电时变频率范围，确保该频率范围内的单调性
//充电死区时间设定
#define CHG_DEADTIME                    (int32_t)(0.95*(MCU_CLK/1000000))//死区时间dead time [us]

//充电最大工作频率   5.1us(实测)+dead(实测)
#define CHG_EPWM_FREQ_MAX               (160000)// PWM frequency[Hz]
#define CHG_EPWM_FREQ_MAX_PERIOD        ((int32_t)(MCU_CLK  / CHG_EPWM_FREQ_MAX - 1))   

//充电最小工作频率
#define CHG_EPWM_FREQ_MIN               (70000)// PWM frequency[Hz] 
#define CHG_EPWM_FREQ_MIN_PERIOD        ((int32_t)(MCU_CLK  / CHG_EPWM_FREQ_MIN - 1))   

/***************************************************************************/
/*-------------------DISC模式：工作、启机频率、死区时间设置----------------*/
/***************************************************************************/
//工作频率
#define DISC_EPWM_FREQ_WORK             (80000)// PWM frequency[Hz]
#define DISC_EPWM_PERIOD_WORK           ((int32_t)(MCU_CLK  / DISC_EPWM_FREQ_WORK - 1))   
#define DISC_DEADTIME_WORK              (int32_t)(0.4*(MCU_CLK/1000000))//死区时间dead time [us]

//启机频率
#define DISC_EPWM_FREQ_START            (26000)//   /* PWM frequency[Hz]  */
#define DISC_EPWM_PERIOD_START          ((int32_t)(MCU_CLK  / DISC_EPWM_FREQ_START - 1))   
#define DISC_DEADTIME_START             (int32_t)(2.0*(MCU_CLK/1000000))//死区时间dead time [us]
/***************************************************************************/

/***************************************************************************
* 谐振参数说明
* 谐振电容Cr：44nF
* 谐振电感Lr：45uH
* 励磁感量Lm：700uH
* 漏感感量Lkr：6uH
***************************************************************************/
//Fr谐振频率；注意：PWM计数方式为锯齿波时需取周期值的一半作为最大占空比
#define CHG_FR_FREQ                     (90000)//谐振频率  
#define CHG_FR_PERIOD                   ((int32_t)(MCU_CLK  / CHG_FR_FREQ - 1))//谐振周期 
#define CHG_FR_PERIOD_HALF              (CHG_FR_PERIOD>>1)//半谐振周期 

//同步整流(SR)synchronous rectification延时时间设定
#define SR_ON_LTIME                     (int32_t)(0.1*(MCU_CLK/1000000))//滞后x时间开通(lag time)
#define SR_OFF_ATIME                    (int32_t)(0.35*(MCU_CLK/1000000))//提前x时间关断(ahead time)
#define SR_MIN_TIME                     (SR_ON_LTIME+SR_OFF_ATIME+10)//SR最小导通时间限制


/***************************************************************************/
/*-------------------CHG模式：占空比、周期变量值设置-----------------------*/
/***************************************************************************/
//注意：PWM计数方式为锯齿波时需取周期值的一半作为最大占空比
#define CHG_EPWM_DUTY_MAX               ((CHG_EPWM_FREQ_MAX_PERIOD>>1) - CHG_DEADTIME)//工作周期值的一半减去死区时间
#define CHG_EPWM_DUTY_MIN               ((int32_t)((0.05 * MCU_CLK)) / 1000000L)

//根据充电环路输出计算PFM频率,确定计算系数
#define CHG_PFM_K                       (CHG_EPWM_FREQ_MIN_PERIOD-CHG_EPWM_FREQ_MAX_PERIOD)
#define CHG_PFM_b                       (CHG_EPWM_FREQ_MAX_PERIOD)

//充电启机时占空比缓启
#define CHG_PWM_DUTY_STEP_VALUE         (20)//变占空比启机时，每次步进值
#define CHG_PWM_DUTY_SHIFT_VALUE        (12)//变占空比启动时缩放移位值
#define CHG_PWM_DUTY_HOLD_INIT          (10 << CHG_PWM_DUTY_SHIFT_VALUE)//放大后的变占空比初始值
#define CHG_PWM_PERIOD_INIT             (CHG_EPWM_FREQ_MAX_PERIOD)//设置启机时的初始周期值，即启机开关频率
/***************************************************************************/

/***************************************************************************/
/*-------------------DISC模式：占空比、周期变量值设置----------------------*/
/***************************************************************************/
//注意：PWM计数方式为锯齿波时需取周期值的一半作为最大占空比
#define DISC_EPWM_DUTY_MAX              ((DISC_EPWM_PERIOD_WORK>>1) - DISC_DEADTIME_WORK)//工作周期值减去死区时间
#define DISC_EPWM_DUTY_MIN              ((int32_t)((0.1 * MCU_CLK)) / 1000000L)

//放电启机时占空比缓启
#define DISC_PWM_DUTY_STEP_VALUE        (140)//变占空比启机时，每次步进值
#define DISC_PWM_DUTY_SHIFT_VALUE       (12)//变占空比启动时缩放移位值
#define DISC_PWM_DUTY_HOLD_INIT         (45 << DISC_PWM_DUTY_SHIFT_VALUE)//初始值固定小占空比设定
#define DISC_PWM_PERIOD_INIT            (DISC_EPWM_PERIOD_WORK)//设置启机时的初始周期值，即启机开关频率

#define DISC_PFM_DUTY_MAX_START         (DISC_EPWM_PERIOD_WORK - DISC_DEADTIME_START)//启机时最大占空比限制：工作周期值减去死区时间
#define DISC_PFM_PERIOD_MAX             (DISC_EPWM_PERIOD_START)//限制最大周期值，即限制最小开关频率
#define DISC_PFM_PERIOD_MIN             (DISC_EPWM_PERIOD_WORK)//限制最小周期值，即限制最大开关频率
#define DISC_PFM_PERIOD_INIT            (DISC_EPWM_PERIOD_START)//设置启机时的初始周期值，即启机开关频率
#define DISC_PFM_PERIOD_WORK            (DISC_EPWM_PERIOD_WORK)//设置正常工作时的周期值，即开关频率  
#define DISC_PFM_PERIOD_STEP_VALUE      (0)//变频率启机时，每次步进值
#define DISC_PFM_PERIOD_SHIFT_VALUE     (12)//变频率启动时缩放移位值
#define DISC_PFM_PERIOD_HOLD_INIT       (DISC_PFM_PERIOD_INIT << DISC_PFM_PERIOD_SHIFT_VALUE)//放大后的变频率初始值
/***************************************************************************/


/***************************************************************************/
/*-------------------工作模式设置------------------------------------------*/
/***************************************************************************/
#define  NORMAL_MODE                    (0)//启用故障保护
#define  DEBUG_MODE                     (1)//屏蔽故障保护
#define  TEST_MODE                      (2)//测试模式，需断开主变压器 确认驱高低压侧驱动波形是否正常
#define  OPERATING_MODE                 (NORMAL_MODE)
/***************************************************************************/

/***************************************************************************/
/*-------------------CHG、DISC同步整流功能使能-----------------------------*/
/***************************************************************************/
#define  SR_DISABLE                     (0)//
#define  SR_ENABLE                      (1)//
#define  CHG_SR_STATE                   (SR_DISABLE)
#if OPERATING_MODE == TEST_MODE
    #define  DISC_SR_STATE              (SR_ENABLE)//放电同步整流功能未验证，在变压器断开的情况下可开启，查看驱动波形
#else
    #define  DISC_SR_STATE              (SR_DISABLE)//放电同步整流功能未验证，不可启用
#endif

/***************************************************************************/
/*-------------------CHG、DISC启动模式设置（PWM/PFM）----------------------*/
/***************************************************************************/
#define  PWM_MODE                       (0)//变占空比启动
#define  PFM_MODE                       (1)//变频率启动
#define  CHG_STARTING_MODE              (PWM_MODE)//充电时只能选择PWM_MODE，不可更改
#define  DISC_STARTING_MODE             (PWM_MODE)//放电默认选择PWM_MODE，不可更改
/***************************************************************************/


/***************************************************************************/
/*-------------------充放电模式设置----------------------------------------*/
/***************************************************************************/
#define  FREE_MODE                      (0)//充电模式
#define  DC_DISCHARGE                   (1)//放电模式    
#define  DC_CHARGE                      (2)//充电模式
/***************************************************************************/

/***************************************************************************/
/*-------------------硬件参数配置------------------------------------------*/
/***************************************************************************/
#define HW_ADC_REF                      (5.0)           // AD参考工作电压      
#define HW_VBAT_GAIN                    (33.33)       	// 电池电压倍数                      
#define HW_IBAT_CHG_GAIN                (40.00)       	// 充电电池电流倍数
#define HW_IBAT_DISC_GAIN               (80.01)       	// 放电电池倍数
#define HW_AUX_POWER_GAIN               (6.0)       	// 辅助电源电压倍数  
#define HW_TEMP_DIVIDE_RES              (10.00)         // 温度采样分压电阻值(KΩ)

/*-------------------采样基值设置------------------------------------------*/
#define COM_VBAT_BASE                   ((int32_t)(HW_ADC_REF * HW_VBAT_GAIN))
#define COM_IBAT_CHG_BASE               ((int32_t)(HW_ADC_REF * HW_IBAT_CHG_GAIN))
#define COM_IBAT_DISC_BASE              ((int32_t)(HW_ADC_REF * HW_IBAT_DISC_GAIN))
#define COM_AUX_POWER_BASE              ((int32_t)(HW_ADC_REF * HW_AUX_POWER_GAIN))

/*-------------------缩放倍数设置------------------------------------------*/
#define COM_IBAT_CHG_SCAL               (64)//电池充电电流控制缩放系数
#define COM_REAL_AUXPOWER_SCAL          (100)//辅助电源电压真实值缩放系数       8.5V*100 = 850
#define COM_REAL_VBAT_SCAL              (100)//电池电压真实值缩放系数         42.5V*100 = 4250
#define COM_REAL_IBAT_CHG_SCAL          ( 10)//电池充电电流缩放系数             12.5A*10 = 125 
#define COM_REAL_IBAT_DISC_SCAL         ( 10)//电池电压缩放系数
/***************************************************************************/

/***************************************************************************/
/*-------------------串口波特率设置----------------------------------------*/
/***************************************************************************/
#define COM_UART0_BAUDRATE              (19200  )//UART0波特率设定值    DC侧与INV侧通信
#define COM_UART1_BAUDRATE              (19200  )//UART1波特率设定值    DC侧与主控侧通信
#define COM_UART2_BAUDRATE              (1000000)  //UART2波特率设定值    调试口
/***************************************************************************/


/***************************************************************************/
/*-----------------DAC转换器输出电压设定(做比较器负端的参考值)-------------*/
/***************************************************************************/
#define COM_DISC_ILIMIT_A               ( 150.0) // 放电电流过流设定值(A)  
#define COM_CHG_ILIMIT_A                ( 45.0 ) // 充电电流过流设定值(A)  

#define COM_DISC_ILIMIT                 ( COM_DISC_ILIMIT_A/HW_IBAT_DISC_GAIN+2.5) // 放电电流过流设定值(A) <5V 
#define COM_CHG_ILIMIT                  ( COM_CHG_ILIMIT_A /HW_IBAT_CHG_GAIN +2.5 ) // 充电电流过流设定值(A) <5V 

#define COM_DAC0_VREF                   ((int)(COM_DISC_ILIMIT*256.0/5.0))//DAC0转换输出电压  / 256 * 128 = 2.5V 
#define COM_DAC1_VREF                   ((int)(COM_CHG_ILIMIT*256.0/5.0))// DAC1转换输出电压  / 256 * 128 = 2.5V 
/***************************************************************************/

/***************************************************************************/
/*-------------------IO端口宏定义------------------------------------------*/
/***************************************************************************/
//LED指示灯
#define LED_GREEN_ON                    ( PORT->PCLRD |=  (1<<7))//PD07
#define LED_GREEN_OFF                   ( PORT->PSETD |=  (1<<7))//

//发送BAT工作信号ToINV侧
#define BAT_START_ENABLE			    ( PORT->PSETC |= (1<<0))//PC00
#define BAT_START_DISABLE  			    ( PORT->PCLRC |= (1<<0))//
#define BAT_START_STATUS	    	    ((PORT->PREADC &(1<<0))>>0)//

//风扇控制启动信号
#define FAN_ENABLE			            ( PORT->PSETD |=  (1<<2))//PD02
#define FAN_DISABLE  	                ( PORT->PCLRD |=  (1<<2))

//电源锁:保持信号,“1“表示锁定
#define POWER_LOCK_ENABLE		        ( PORT->PSETE |=  (1<<7))//PE07
#define POWER_LOCK_DISABLE  		    ( PORT->PCLRE |=  (1<<7))
#define POWER_LOCK_STATUS	    	    ((PORT->PREADE &(1<<7))>>7)//电源保持信号状态值

//接收INV侧发送的母线电压过压信号
#define BOSOC_STATUS	    	        ((PORT->PREADE &(1<<9))>>9)//PE09

//接收INV侧逆变器工作信号
#define INV_WORK_STATE   	            ((PORT->PREADC &(1<<1))>>1)//PC01

//电源按键输入信号
#define SHUT_DOWN_SWITCH	            ((PORT->PREADE &(1<<8))>>8)//PE08按键关机信号输入配置，默认上拉输入(低电平有效)，“1”正常	
/***************************************************************************/

#endif 

