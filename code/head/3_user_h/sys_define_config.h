
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

#ifndef __SYS_DEFINE_CONFIG_H
#define	__SYS_DEFINE_CONFIG_H

#include "BAT32G439.h"
/***************************************************************************/
/*-------------------EPWM������������--------------------------------------*/
/***************************************************************************/
#define MCU_CLK 	                    (128000000L)//MCU��Ƶ
#define DEADTIME			            ((int32_t)((0 * MCU_CLK)) / 1000000L)

/***************************************************************************/
/*-------------------CHGģʽ������������Ƶ�ʡ�����ʱ������-----------------*/
/***************************************************************************/
//ע�⣺��ɨƵȷ�����ʱ��Ƶ�ʷ�Χ��ȷ����Ƶ�ʷ�Χ�ڵĵ�����
//�������ʱ���趨
#define CHG_DEADTIME                    (int32_t)(0.95*(MCU_CLK/1000000))//����ʱ��dead time [us]

//��������Ƶ��   5.1us(ʵ��)+dead(ʵ��)
#define CHG_EPWM_FREQ_MAX               (160000)// PWM frequency[Hz]
#define CHG_EPWM_FREQ_MAX_PERIOD        ((int32_t)(MCU_CLK  / CHG_EPWM_FREQ_MAX - 1))   

//�����С����Ƶ��
#define CHG_EPWM_FREQ_MIN               (70000)// PWM frequency[Hz] 
#define CHG_EPWM_FREQ_MIN_PERIOD        ((int32_t)(MCU_CLK  / CHG_EPWM_FREQ_MIN - 1))   

/***************************************************************************/
/*-------------------DISCģʽ������������Ƶ�ʡ�����ʱ������----------------*/
/***************************************************************************/
//����Ƶ��
#define DISC_EPWM_FREQ_WORK             (80000)// PWM frequency[Hz]
#define DISC_EPWM_PERIOD_WORK           ((int32_t)(MCU_CLK  / DISC_EPWM_FREQ_WORK - 1))   
#define DISC_DEADTIME_WORK              (int32_t)(0.4*(MCU_CLK/1000000))//����ʱ��dead time [us]

//����Ƶ��
#define DISC_EPWM_FREQ_START            (26000)//   /* PWM frequency[Hz]  */
#define DISC_EPWM_PERIOD_START          ((int32_t)(MCU_CLK  / DISC_EPWM_FREQ_START - 1))   
#define DISC_DEADTIME_START             (int32_t)(2.0*(MCU_CLK/1000000))//����ʱ��dead time [us]
/***************************************************************************/

/***************************************************************************
* г�����˵��
* г�����Cr��44nF
* г����Lr��45uH
* ���Ÿ���Lm��700uH
* ©�и���Lkr��6uH
***************************************************************************/
//Frг��Ƶ�ʣ�ע�⣺PWM������ʽΪ��ݲ�ʱ��ȡ����ֵ��һ����Ϊ���ռ�ձ�
#define CHG_FR_FREQ                     (90000)//г��Ƶ��  
#define CHG_FR_PERIOD                   ((int32_t)(MCU_CLK  / CHG_FR_FREQ - 1))//г������ 
#define CHG_FR_PERIOD_HALF              (CHG_FR_PERIOD>>1)//��г������ 

//ͬ������(SR)synchronous rectification��ʱʱ���趨
#define SR_ON_LTIME                     (int32_t)(0.1*(MCU_CLK/1000000))//�ͺ�xʱ�俪ͨ(lag time)
#define SR_OFF_ATIME                    (int32_t)(0.35*(MCU_CLK/1000000))//��ǰxʱ��ض�(ahead time)
#define SR_MIN_TIME                     (SR_ON_LTIME+SR_OFF_ATIME+10)//SR��С��ͨʱ������


/***************************************************************************/
/*-------------------CHGģʽ��ռ�ձȡ����ڱ���ֵ����-----------------------*/
/***************************************************************************/
//ע�⣺PWM������ʽΪ��ݲ�ʱ��ȡ����ֵ��һ����Ϊ���ռ�ձ�
#define CHG_EPWM_DUTY_MAX               ((CHG_EPWM_FREQ_MAX_PERIOD>>1) - CHG_DEADTIME)//��������ֵ��һ���ȥ����ʱ��
#define CHG_EPWM_DUTY_MIN               ((int32_t)((0.05 * MCU_CLK)) / 1000000L)

//���ݳ�绷·�������PFMƵ��,ȷ������ϵ��
#define CHG_PFM_K                       (CHG_EPWM_FREQ_MIN_PERIOD-CHG_EPWM_FREQ_MAX_PERIOD)
#define CHG_PFM_b                       (CHG_EPWM_FREQ_MAX_PERIOD)

//�������ʱռ�ձȻ���
#define CHG_PWM_DUTY_STEP_VALUE         (20)//��ռ�ձ�����ʱ��ÿ�β���ֵ
#define CHG_PWM_DUTY_SHIFT_VALUE        (12)//��ռ�ձ�����ʱ������λֵ
#define CHG_PWM_DUTY_HOLD_INIT          (10 << CHG_PWM_DUTY_SHIFT_VALUE)//�Ŵ��ı�ռ�ձȳ�ʼֵ
#define CHG_PWM_PERIOD_INIT             (CHG_EPWM_FREQ_MAX_PERIOD)//��������ʱ�ĳ�ʼ����ֵ������������Ƶ��
/***************************************************************************/

/***************************************************************************/
/*-------------------DISCģʽ��ռ�ձȡ����ڱ���ֵ����----------------------*/
/***************************************************************************/
//ע�⣺PWM������ʽΪ��ݲ�ʱ��ȡ����ֵ��һ����Ϊ���ռ�ձ�
#define DISC_EPWM_DUTY_MAX              ((DISC_EPWM_PERIOD_WORK>>1) - DISC_DEADTIME_WORK)//��������ֵ��ȥ����ʱ��
#define DISC_EPWM_DUTY_MIN              ((int32_t)((0.1 * MCU_CLK)) / 1000000L)

//�ŵ�����ʱռ�ձȻ���
#define DISC_PWM_DUTY_STEP_VALUE        (140)//��ռ�ձ�����ʱ��ÿ�β���ֵ
#define DISC_PWM_DUTY_SHIFT_VALUE       (12)//��ռ�ձ�����ʱ������λֵ
#define DISC_PWM_DUTY_HOLD_INIT         (45 << DISC_PWM_DUTY_SHIFT_VALUE)//��ʼֵ�̶�Сռ�ձ��趨
#define DISC_PWM_PERIOD_INIT            (DISC_EPWM_PERIOD_WORK)//��������ʱ�ĳ�ʼ����ֵ������������Ƶ��

#define DISC_PFM_DUTY_MAX_START         (DISC_EPWM_PERIOD_WORK - DISC_DEADTIME_START)//����ʱ���ռ�ձ����ƣ���������ֵ��ȥ����ʱ��
#define DISC_PFM_PERIOD_MAX             (DISC_EPWM_PERIOD_START)//�����������ֵ����������С����Ƶ��
#define DISC_PFM_PERIOD_MIN             (DISC_EPWM_PERIOD_WORK)//������С����ֵ����������󿪹�Ƶ��
#define DISC_PFM_PERIOD_INIT            (DISC_EPWM_PERIOD_START)//��������ʱ�ĳ�ʼ����ֵ������������Ƶ��
#define DISC_PFM_PERIOD_WORK            (DISC_EPWM_PERIOD_WORK)//������������ʱ������ֵ��������Ƶ��  
#define DISC_PFM_PERIOD_STEP_VALUE      (0)//��Ƶ������ʱ��ÿ�β���ֵ
#define DISC_PFM_PERIOD_SHIFT_VALUE     (12)//��Ƶ������ʱ������λֵ
#define DISC_PFM_PERIOD_HOLD_INIT       (DISC_PFM_PERIOD_INIT << DISC_PFM_PERIOD_SHIFT_VALUE)//�Ŵ��ı�Ƶ�ʳ�ʼֵ
/***************************************************************************/


/***************************************************************************/
/*-------------------����ģʽ����------------------------------------------*/
/***************************************************************************/
#define  NORMAL_MODE                    (0)//���ù��ϱ���
#define  DEBUG_MODE                     (1)//���ι��ϱ���
#define  TEST_MODE                      (2)//����ģʽ����Ͽ�����ѹ�� ȷ�����ߵ�ѹ�����������Ƿ�����
#define  OPERATING_MODE                 (NORMAL_MODE)
/***************************************************************************/

/***************************************************************************/
/*-------------------CHG��DISCͬ����������ʹ��-----------------------------*/
/***************************************************************************/
#define  SR_DISABLE                     (0)//
#define  SR_ENABLE                      (1)//
#define  CHG_SR_STATE                   (SR_DISABLE)
#if OPERATING_MODE == TEST_MODE
    #define  DISC_SR_STATE              (SR_ENABLE)//�ŵ�ͬ����������δ��֤���ڱ�ѹ���Ͽ�������¿ɿ������鿴��������
#else
    #define  DISC_SR_STATE              (SR_DISABLE)//�ŵ�ͬ����������δ��֤����������
#endif

/***************************************************************************/
/*-------------------CHG��DISC����ģʽ���ã�PWM/PFM��----------------------*/
/***************************************************************************/
#define  PWM_MODE                       (0)//��ռ�ձ�����
#define  PFM_MODE                       (1)//��Ƶ������
#define  CHG_STARTING_MODE              (PWM_MODE)//���ʱֻ��ѡ��PWM_MODE�����ɸ���
#define  DISC_STARTING_MODE             (PWM_MODE)//�ŵ�Ĭ��ѡ��PWM_MODE�����ɸ���
/***************************************************************************/


/***************************************************************************/
/*-------------------��ŵ�ģʽ����----------------------------------------*/
/***************************************************************************/
#define  FREE_MODE                      (0)//���ģʽ
#define  DC_DISCHARGE                   (1)//�ŵ�ģʽ    
#define  DC_CHARGE                      (2)//���ģʽ
/***************************************************************************/

/***************************************************************************/
/*-------------------Ӳ����������------------------------------------------*/
/***************************************************************************/
#define HW_ADC_REF                      (5.0)           // AD�ο�������ѹ      
#define HW_VBAT_GAIN                    (33.33)       	// ��ص�ѹ����                      
#define HW_IBAT_CHG_GAIN                (40.00)       	// ����ص�������
#define HW_IBAT_DISC_GAIN               (80.01)       	// �ŵ��ر���
#define HW_AUX_POWER_GAIN               (6.0)       	// ������Դ��ѹ����  
#define HW_TEMP_DIVIDE_RES              (10.00)         // �¶Ȳ�����ѹ����ֵ(K��)

/*-------------------������ֵ����------------------------------------------*/
#define COM_VBAT_BASE                   ((int32_t)(HW_ADC_REF * HW_VBAT_GAIN))
#define COM_IBAT_CHG_BASE               ((int32_t)(HW_ADC_REF * HW_IBAT_CHG_GAIN))
#define COM_IBAT_DISC_BASE              ((int32_t)(HW_ADC_REF * HW_IBAT_DISC_GAIN))
#define COM_AUX_POWER_BASE              ((int32_t)(HW_ADC_REF * HW_AUX_POWER_GAIN))

/*-------------------���ű�������------------------------------------------*/
#define COM_IBAT_CHG_SCAL               (64)//��س�������������ϵ��
#define COM_REAL_AUXPOWER_SCAL          (100)//������Դ��ѹ��ʵֵ����ϵ��       8.5V*100 = 850
#define COM_REAL_VBAT_SCAL              (100)//��ص�ѹ��ʵֵ����ϵ��         42.5V*100 = 4250
#define COM_REAL_IBAT_CHG_SCAL          ( 10)//��س���������ϵ��             12.5A*10 = 125 
#define COM_REAL_IBAT_DISC_SCAL         ( 10)//��ص�ѹ����ϵ��
/***************************************************************************/

/***************************************************************************/
/*-------------------���ڲ���������----------------------------------------*/
/***************************************************************************/
#define COM_UART0_BAUDRATE              (19200  )//UART0�������趨ֵ    DC����INV��ͨ��
#define COM_UART1_BAUDRATE              (19200  )//UART1�������趨ֵ    DC�������ز�ͨ��
#define COM_UART2_BAUDRATE              (1000000)  //UART2�������趨ֵ    ���Կ�
/***************************************************************************/


/***************************************************************************/
/*-----------------DACת���������ѹ�趨(���Ƚ������˵Ĳο�ֵ)-------------*/
/***************************************************************************/
#define COM_DISC_ILIMIT_A               ( 150.0) // �ŵ���������趨ֵ(A)  
#define COM_CHG_ILIMIT_A                ( 45.0 ) // �����������趨ֵ(A)  

#define COM_DISC_ILIMIT                 ( COM_DISC_ILIMIT_A/HW_IBAT_DISC_GAIN+2.5) // �ŵ���������趨ֵ(A) <5V 
#define COM_CHG_ILIMIT                  ( COM_CHG_ILIMIT_A /HW_IBAT_CHG_GAIN +2.5 ) // �����������趨ֵ(A) <5V 

#define COM_DAC0_VREF                   ((int)(COM_DISC_ILIMIT*256.0/5.0))//DAC0ת�������ѹ  / 256 * 128 = 2.5V 
#define COM_DAC1_VREF                   ((int)(COM_CHG_ILIMIT*256.0/5.0))// DAC1ת�������ѹ  / 256 * 128 = 2.5V 
/***************************************************************************/

/***************************************************************************/
/*-------------------IO�˿ں궨��------------------------------------------*/
/***************************************************************************/
//LEDָʾ��
#define LED_GREEN_ON                    ( PORT->PCLRD |=  (1<<7))//PD07
#define LED_GREEN_OFF                   ( PORT->PSETD |=  (1<<7))//

//����BAT�����ź�ToINV��
#define BAT_START_ENABLE			    ( PORT->PSETC |= (1<<0))//PC00
#define BAT_START_DISABLE  			    ( PORT->PCLRC |= (1<<0))//
#define BAT_START_STATUS	    	    ((PORT->PREADC &(1<<0))>>0)//

//���ȿ��������ź�
#define FAN_ENABLE			            ( PORT->PSETD |=  (1<<2))//PD02
#define FAN_DISABLE  	                ( PORT->PCLRD |=  (1<<2))

//��Դ��:�����ź�,��1����ʾ����
#define POWER_LOCK_ENABLE		        ( PORT->PSETE |=  (1<<7))//PE07
#define POWER_LOCK_DISABLE  		    ( PORT->PCLRE |=  (1<<7))
#define POWER_LOCK_STATUS	    	    ((PORT->PREADE &(1<<7))>>7)//��Դ�����ź�״ֵ̬

//����INV�෢�͵�ĸ�ߵ�ѹ��ѹ�ź�
#define BOSOC_STATUS	    	        ((PORT->PREADE &(1<<9))>>9)//PE09

//����INV������������ź�
#define INV_WORK_STATE   	            ((PORT->PREADC &(1<<1))>>1)//PC01

//��Դ���������ź�
#define SHUT_DOWN_SWITCH	            ((PORT->PREADE &(1<<8))>>8)//PE08�����ػ��ź��������ã�Ĭ����������(�͵�ƽ��Ч)����1������	
/***************************************************************************/

#endif 

