
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/


#ifndef __SYS_DEFINE_PARAR_H
#define	__SYS_DEFINE_PARAR_H

/****************************************************************************/
/*	include files
*****************************************************************************/
#include "sys_define_config.h"
/****************************************************************************/
/*-------------------ͨ�Ų�������-------------------------------------------*/
#define UART0_HEART_VAL                                 (300)  
#define UART0_SEND_PERIOD_VAL                           (20)//���ͼ��ʱ���趨(ms)  1/(19200)Baud*10*30
#define UART0_SEND_NUM                                  (30)//2�ֽ�֡ͷ+12�ֽ�����λ+2�ֽ�У��λ
#define UART0_RECE_NUM                                  (UART0_SEND_NUM*2)//


#define COM_START_FINISH_STATE_NOK                      (0)//����δ��ɣ�����������ѹ״̬
#define COM_START_FINISH_STATE_OK                       (1)//������ɣ�������������״̬
#define COM_INV_READY_STATE_NOK                         (0)//����δ׼����
#define COM_INV_READY_STATE_OK                          (1)//����׼����


/*-------------------�ŵ���ѹ������������-----------------------------------*/
#define PFM_AD_VBUS_FB_VAL_SET                          (1990)//�趨ĸ�ߵ�ѹ���Ʒ�����ֵ�����ڸ�ֵ�������
//ע�⣺INV�ഫ�����ʵĸ�ߵ�ѹֵ���Ŵ�10��
#if 1  //���230V
    #define PFM_INV_VBUS_VOL_VAL_SET2                   (360*10)//���ڸ�ĸ�ߵ�ѹֵ���軺������ѹ
    #define PFM_INV_VBUS_VOL_VAL_SET_SS                 (150*10)//��Ƶ��ģʽʹ��
    #if OPERATING_MODE == TEST_MODE
        #define PFM_INV_VBUS_VOL_VAL_SET                (0*10)//С�ڸ�ĸ�ߵ�ѹֵ�Գ�ʼռ�ձ�������ѹ
    #else
        #define PFM_INV_VBUS_VOL_VAL_SET                (250*10)//С�ڸ�ĸ�ߵ�ѹֵ�Գ�ʼռ�ձ�������ѹ
    #endif
#else   //���110V
    #define PFM_INV_VBUS_VOL_VAL_SET2                   (150*10)//���ڸ�ĸ�ߵ�ѹֵ���軺������ѹ
    #define PFM_INV_VBUS_VOL_VAL_SET_SS                 (150*10)//��Ƶ��ģʽʹ��
    #if OPERATING_MODE == TEST_MODE
        #define PFM_INV_VBUS_VOL_VAL_SET                (0*10)//С�ڸ�ĸ�ߵ�ѹֵ�Գ�ʼռ�ձ�������ѹ
    #else
        #define PFM_INV_VBUS_VOL_VAL_SET                (140*10)//С�ڸ�ĸ�ߵ�ѹֵ�Գ�ʼռ�ձ�������ѹ
    #endif    
#endif


/***************************************************************************
* ﮵��˵��
* Ǧ���ص�ѹ��Χ����Ƶ�ѹ12V��ÿ�������ߵ�ѹ14.4V������絽10.5V��
* �������(LFP)��ص�ѹ��Χ����Ƶ�ѹ3.2V��ÿ�������ߵ�ѹ3.6V������絽2.5V��
* ��Ԫ﮵��ص�ѹ��Χ����Ƶ�ѹ3.6V��ÿ�������ߵ�ѹ4.1V������絽2.8V��
* ��Ԫ������Ϊ��������Ԫ�أ������̣�NCM��������������NCA����Ϊ��������
***************************************************************************/
#define COM_LFP_VBAT_S_MIN                              (2.50)//����������﮵����͵�ѹ    
#define COM_LFP_VBAT_S_MAX                              (3.65)//����������﮵����ߵ�ѹ 
#define COM_NCM_VBAT_S_MIN                              (3.29)//������Ԫ��﮵����͵�ѹ    3.15
#define COM_NCM_VBAT_S_MAX                              (3.78)//������Ԫ��﮵����ߵ�ѹ    4.15

/*-------------------﮵������ѡ��-----------------------------------------*/
#define COM_LFP_BAT                                     (0)//﮵������Ϊ�������
#define COM_NCM_BAT                                     (1)//﮵������Ϊ��Ԫ﮵�
#define COM_BAT_TYPE_SELECT                             (COM_NCM_BAT)//﮵������ѡ��

/*-------------------﮵�ش���/�����ѱ�ѡ��--------------------------------*/
#if 0
    #define N2_N1_RATIO                                 (39/3)//����ѹ��������
    #define COM_BAT_NUM_SET                             (10)//﮵�ش���
#else
	#define N2_N1_RATIO                                 (25/3)//����ѹ��������
    #define COM_BAT_NUM_SET                             (14)//﮵�ش���
#endif

#if (COM_BAT_TYPE_SELECT == COM_LFP_BAT)//������﮵��
    #define COM_VBAT_MAX_VAL                            (COM_BAT_NUM_SET * COM_LFP_VBAT_S_MAX )//��ߵ�ص�ѹ�趨(V)  
    #define COM_VBAT_MIN_VAL                            (COM_BAT_NUM_SET * COM_LFP_VBAT_S_MIN )//��͵�ص�ѹ�趨(V) 
    #define COM_VBAT_VALBACK                            ( 0.3)//����ʹ�õĻز�ֵ    
#else   //��Ԫ﮵��
    #define COM_VBAT_MAX_VAL                            (COM_BAT_NUM_SET * COM_NCM_VBAT_S_MAX )//��ߵ�ص�ѹ�趨(V)  
    #define COM_VBAT_MIN_VAL                            (COM_BAT_NUM_SET * COM_NCM_VBAT_S_MIN )//��͵�ص�ѹ�趨(V)
    #define COM_VBAT_VALBACK                            ( 0.3)//����ʹ�õĻز�ֵ        
#endif


/*-------------------�������͵�ѹ�����趨---------------------------------*/
#define COM_CHG_IBAT_MAX_VAL                            (10.0)//����������������趨(A)
#define COM_CHG_VBAT_MAX_VAL                            (COM_VBAT_MAX_VAL - 0.3 )//��ѹ�����ߵ�ص�ѹ�趨(V) 
#define COM_CHG_VBAT_MIN_VAL                            (COM_VBAT_MIN_VAL - 0.0 )//��ѹ�����͵�ص�ѹ�趨(V)  

#define COM_CHG_TC_TIME                                 (5)//������ʱ������(s)
#define COM_CHG_CV_FC_TIME                              (10)//CVתFC�����ʱʱ������ (s)

#define COM_CHG_ALLOW_VBAT_VAL                          (int32_t)(((COM_CHG_VBAT_MAX_VAL-1.8) * 4096) / COM_VBAT_BASE)//���ڸõ�ѹ��������ɱ�־
#define COM_CHG_VBAT_TC_VAL                             (int32_t)(((COM_CHG_VBAT_MIN_VAL+1.0) * 4096) / COM_VBAT_BASE)//�������ص�ѹ�趨(���ڸõ�ѹ����������)
#define COM_CHG_VBAT_CC_CV_VAL                          (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.8) * 4096) / COM_VBAT_BASE)//�жϺ�����ѹ���ĵ�ص�ѹ��ֵ�趨
#define COM_CHG_VBAT_FC_VAL                             (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.3) * 4096) / COM_VBAT_BASE)//�������ص�ѹ�趨 
#define COM_CHG_VBAT_CV_VAL                             (int32_t)(((COM_CHG_VBAT_MAX_VAL-0.3) * 4096) / COM_VBAT_BASE)//��ѹ����ص�ѹ�趨  

#define COM_CHG_IBAT_STEP_VAL                           (int32_t)(0.04  * COM_IBAT_CHG_SCAL)//�������ʱ��������ֵ����ѹ������ʱ��
#define COM_CHG_IBAT_MIN_VAL                            (int32_t)(1.2 * COM_IBAT_CHG_SCAL)//�������ʱ��С������

#define COM_CHG_IBAT_CC1_VAL                            (int32_t)((COM_CHG_IBAT_MAX_VAL-0.0 ) * COM_IBAT_CHG_SCAL)//��������ص����趨
#define COM_CHG_IBAT_CC_MAXVAL                          (int32_t)(COM_CHG_IBAT_CC1_VAL)//��������ص������ֵ����
#define COM_CHG_IBAT_CC2_VAL                            (int32_t)((COM_CHG_IBAT_MAX_VAL-0.5 ) * COM_IBAT_CHG_SCAL)//���ڸó����������𽥽��ͺ���ֵ
#define COM_CHG_IBAT_TC_VAL                             (int32_t)((COM_CHG_IBAT_MAX_VAL*0.06) * COM_IBAT_CHG_SCAL)//�������ص����趨(���ŵ�ʹ��) 
#define COM_CHG_IBAT_FC_VAL                             (int32_t)((COM_CHG_IBAT_MAX_VAL*0.05) * COM_IBAT_CHG_SCAL)//�������ص����趨(���ڸõ������ø���)  
#define COM_CHG_FINISH_IBAT_VAL                         (int32_t)((COM_CHG_IBAT_MAX_VAL*0.045) * COM_IBAT_CHG_SCAL)//�жϳ�����ʱ����ֵ  

#define COM_CHG_FINISH_OK                               (1)//����Ѿ���ɣ�����״̬
#define COM_CHG_FINISH_NOK                              (0)//���δ��ɣ�δ����״̬
#define COM_CHG_FINISH_OK_TIME                          (20000)//��������ʱʱ��(ms)
#define COM_CHG_FINISH_NOK_TIME                         (10000)//���δ�����ʱʱ��

//��ѹ����ʼ���ʱ������   
#define COM_CHG_VBAT_REF_INIT                           (int32_t)((40.0 * 4096) / COM_VBAT_BASE)
#define COM_CHG_VBAT_REF_STEP_VALUE                     (10)//ÿ�β���ֵ
#define COM_CHG_VBAT_REF_SHIFT_VALUE                    (12)//����ʱ������λֵ
#define COM_CHG_VBAT_REF_HOLD_INIT                      (COM_CHG_VBAT_REF_INIT << COM_CHG_VBAT_REF_SHIFT_VALUE)//�Ŵ��ı�ռ�ձȳ�ʼֵ

//��������ʼ���ʱ����ref������   
#define COM_CHG_IBAT_REF_PEIROD                         (32)//ÿ�β�������ֵ(ms)
#define COM_CHG_IBAT_REF_STEP_VALUE                     (600)//ÿ�β���ֵ
#define COM_CHG_IBAT_REF_SHIFT_VALUE                    (7)//������λֵ
#define COM_CHG_IBAT_REF_HOLD_INIT                      (51 << COM_CHG_IBAT_REF_SHIFT_VALUE)//�Ŵ��ĳ�ʼֵ

//V_PFC����������
#define COM_CHG_VBUS_REF_STEP_VALUE                     (4000)//��ռ�ձ�����ʱ��ÿ�β���ֵ
#define COM_CHG_VBUS_REF_SHIFT_VALUE                    (12)//��ռ�ձ�����ʱ������λֵ
#define COM_CHG_VBUS_REF_INIT                           (385*4)//ĸ�ߵ�ѹ��ʼ����ֵΪ385V
#define COM_CHG_VBUS_REF_HOLD_INIT                      (COM_CHG_VBUS_REF_INIT << COM_CHG_VBUS_REF_SHIFT_VALUE)//�Ŵ��ı�ռ�ձȳ�ʼֵ
#define COM_CHG_VBUS_REF_MAX                            (485*4)//ĸ�ߵ�ѹ�������ֵΪ485V
#define COM_CHG_VBUS_REF_HOLD_MAX                       (COM_CHG_VBUS_REF_MAX << COM_CHG_VBUS_REF_SHIFT_VALUE)//�Ŵ��ı�ռ�ձȳ�ʼֵ
//����PFC��ĸ�ߵ�ѹ��ز������� 
#define CHG_OUT_MIN                                     (2200)//����ʵ���������,��֤������г���
#define CHG_OUT_MAX                                     (2260)//����ʵ���������,��֤������г��� 


/*------------------------------------------------------------------------------------*/
//������Դ�����޲�������
/*------------------------------------------------------------------------------------*/
#define COM_AUX_POWER_MAX                               ( 9.0)
#define COM_AUX_POWER_MIN                               ( 5.2)
#define COM_AUX_POWER_VALBACK                           ( 0.3)//����ʹ�õĻز�ֵ
/*------------------------------------------------------------------------------------*/
//������⸨����Դ��������
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_AUX_POWER_UP                    (int32_t)( COM_AUX_POWER_MAX * COM_REAL_AUXPOWER_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�   
#define COM_START_CHECK_AUX_POWER_UP_BACK               (int32_t)((COM_AUX_POWER_MAX + COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)
#define COM_START_CHECK_AUX_POWER_UP_TIME		        (700)//��ʱʱ��(ms)

#define COM_START_CHECK_AUX_POWER_DOWN                  (int32_t)( COM_AUX_POWER_MIN * COM_REAL_AUXPOWER_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�	
#define COM_START_CHECK_AUX_POWER_DOWN_BACK             (int32_t)((COM_AUX_POWER_MIN - COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)
#define COM_START_CHECK_AUX_POWER_DOWN_TIME			    (700)//��ʱʱ��(ms)


/*------------------------------------------------------------------------------------*/
//��������ص�ѹ��������
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_VBAT_UP                         (int32_t)((COM_VBAT_MAX_VAL) * COM_REAL_VBAT_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�   
#define COM_START_CHECK_VBAT_UP_BACK                    (int32_t)((COM_VBAT_MAX_VAL+COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)
#define COM_START_CHECK_VBAT_UP_TIME		            (700)//��ʱʱ��(ms)

#define COM_START_CHECK_VBAT_DOWN                       (int32_t)((COM_VBAT_MIN_VAL) * COM_REAL_VBAT_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�	
#define COM_START_CHECK_VBAT_DOWN_BACK                  (int32_t)((COM_VBAT_MIN_VAL-COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)
#define COM_START_CHECK_VBAT_DOWN_TIME			        (700)//��ʱʱ��(ms)

/*------------------------------------------------------------------------------------*/
//��������¶Ȳ�������
/*------------------------------------------------------------------------------------*/
#define COM_START_CHECK_TEMP_UP_RES                     (2.240)//�趨�¶�70���ӦNTC����ֵ(K��)
#define COM_START_CHECK_TEMP_UP_BACK_RES                (1.678)//�趨�¶�80���ӦNTC����ֵ(K��)
#define COM_START_CHECK_TEMP_UP                         (int32_t)((COM_START_CHECK_TEMP_UP_RES/(COM_START_CHECK_TEMP_UP_RES+HW_TEMP_DIVIDE_RES)*4096))  
#define COM_START_CHECK_TEMP_UP_BACK                    (int32_t)((COM_START_CHECK_TEMP_UP_BACK_RES/(COM_START_CHECK_TEMP_UP_BACK_RES+HW_TEMP_DIVIDE_RES)*4096)) 
#define COM_START_CHECK_TEMP_UP_TIME		            (700)//��ʱʱ��(ms)


/*------------------------------------------------------------------------------------*/
//���������޲�������
/*------------------------------------------------------------------------------------*/
#define COM_CHG_POWER_MAX1                              (1500)//(W)
#define COM_CHG_POWER_MAX2                              (1500)//(W)
#define COM_CHG_POWER_VALBACK                           ( 30)//����ʹ�õĻز�ֵ(W)
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
//�����ز�������
/*------------------------------------------------------------------------------------*/
#define COM_CHG_OLP1_TIME                               (5000)//��ʱʱ��(ms)   
#define COM_CHG_OLP2_TIME                               (5000)//��ʱʱ��(ms)    
#define COM_CHG_OLP1_VAL                                (COM_CHG_POWER_MAX1)//(W)      
#define COM_CHG_OLP2_VAL                                (COM_CHG_POWER_MAX2)//(W)      
#define COM_CHG_OLP1_VAL_BACK                           (COM_CHG_POWER_MAX1 - COM_CHG_POWER_VALBACK)//(W)
#define COM_CHG_OLP2_VAL_BACK                           (COM_CHG_POWER_MAX2 - COM_CHG_POWER_VALBACK)//(W)

/*------------------------------------------------------------------------------------*/
//�ŵ�������޲�������
/*------------------------------------------------------------------------------------*/
#define COM_DISC_POWER_MAX1                             (3500)//(W)
#define COM_DISC_POWER_MAX2                             (3500)//(W)
#define COM_DISC_POWER_VALBACK                          ( 30)//����ʹ�õĻز�ֵ(W)
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
//�ŵ���ز�������
/*------------------------------------------------------------------------------------*/
#define COM_DISC_OLP1_TIME	                            (5000)//��ʱʱ��(ms)     
#define COM_DISC_OLP2_TIME	                            (5000)//��ʱʱ��(ms)  
#define COM_DISC_OLP1_VAL	                            (COM_DISC_POWER_MAX1)//(W)      
#define COM_DISC_OLP2_VAL	                            (COM_DISC_POWER_MAX2)//(W) 
#define COM_DISC_OLP1_VAL_BACK	                        (COM_DISC_POWER_MAX1 - COM_DISC_POWER_VALBACK)//(W)
#define COM_DISC_OLP2_VAL_BACK	                        (COM_DISC_POWER_MAX2 - COM_DISC_POWER_VALBACK)//(W)

/***************************************************************************/
//������Դ��ѹ/Ƿѹ����
/***************************************************************************/
#define COM_AUX_POWER_OVP_TIME                          (100)//��ʱʱ��(ms))
#define COM_AUX_POWER_OVP_VAL                           (int32_t)( COM_AUX_POWER_MAX * COM_REAL_AUXPOWER_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�   
#define COM_AUX_POWER_OVP_VAL_BACK                      (int32_t)((COM_AUX_POWER_MAX - COM_AUX_POWER_VALBACK)* COM_REAL_AUXPOWER_SCAL)   

#define COM_AUX_POWER_LVP_TIME                          (200)//��ʱʱ��(ms) 
#define COM_AUX_POWER_LVP_VAL                           (int32_t)( COM_AUX_POWER_MIN * COM_REAL_AUXPOWER_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�    
#define COM_AUX_POWER_LVP_VAL_BACK                      (int32_t)((COM_AUX_POWER_MIN + COM_AUX_POWER_VALBACK) * COM_REAL_AUXPOWER_SCAL)

/***************************************************************************/
//��ص�ѹ��ѹ/Ƿѹ����
/***************************************************************************/
#define COM_VBAT_OVP_TIME                               (500)//��ʱʱ��(ms))
#define COM_VBAT_OVP_VAL                                (int32_t)((COM_VBAT_MAX_VAL) * COM_REAL_VBAT_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�   
#define COM_VBAT_OVP_VAL_BACK                           (int32_t)((COM_VBAT_MAX_VAL-COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)   

#define COM_VBAT_LVP1_TIME                              (100)//��ʱʱ��(ms) 
#define COM_VBAT_LVP1_VAL                               (int32_t)((COM_VBAT_MIN_VAL) * COM_REAL_VBAT_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�    
#define COM_VBAT_LVP1_VAL_BACK                          (int32_t)((COM_VBAT_MIN_VAL+COM_VBAT_VALBACK) * COM_REAL_VBAT_SCAL)

#define COM_VBAT_LVP2_TIME                              (10)//��ʱʱ��(ms) 
#define COM_VBAT_LVP2_VAL                               (int32_t)((COM_VBAT_MIN_VAL-4.0) * COM_REAL_VBAT_SCAL)//ת��Ϊ��AD����ֵͳһ��λ���бȽ�    
#define COM_VBAT_LVP2_VAL_BACK                          (int32_t)((COM_VBAT_MIN_VAL-3.7) * COM_REAL_VBAT_SCAL)


/***************************************************************************/
//��������
/***************************************************************************/	
#define COM_OTP1_TIME                                   (500)//��ʱʱ��(ms)
#define COM_OTP2_TIME                                   (500)//��ʱʱ��(ms)
#define COM_OTP1_RES                                    (1.678)//�趨�¶�80���ӦNTC����ֵ(K��)
#define COM_OTP2_RES                                    (1.275)//�趨�¶�90���ӦNTC����ֵ(K��)
#define COM_OTP1_BACK_RES                               (2.240)//�趨�¶�70���ӦNTC����ֵ(K��)
#define COM_OTP2_BACK_RES                               (2.240)//�趨�¶�70���ӦNTC����ֵ(K��)                          
#define COM_OTP1_VAL                                    (int32_t)((COM_OTP1_RES/(COM_OTP1_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP2_VAL                                    (int32_t)((COM_OTP2_RES/(COM_OTP2_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP1_VAL_BACK                               (int32_t)((COM_OTP1_BACK_RES/(COM_OTP1_BACK_RES+HW_TEMP_DIVIDE_RES)*4096))
#define COM_OTP2_VAL_BACK                               (int32_t)((COM_OTP2_BACK_RES/(COM_OTP2_BACK_RES+HW_TEMP_DIVIDE_RES)*4096))	
/***************************************************************************/
/***************************************************************************/

/*------------------------------------------------------------------------------------*/
//VREF�ο���ѹ�����޲�������
/*------------------------------------------------------------------------------------*/
#define COM_VREF_MAX                                    (2248)
#define COM_VREF_MIN                                    (1848)
#define COM_VREF_VALBACK                                ( 80)//����ʹ�õĻز�ֵ
/*------------------------------------------------------------------------------------*/
/***************************************************************************/
//VREF�ο���ѹ����������
/***************************************************************************/	
#define COM_VREF_OVP_TIME                               (10)//��ʱʱ��(ms)
#define COM_VREF_OVP_VAL                                (COM_VREF_MAX)//
#define COM_VREF_OVP_VAL_BACK                           (COM_VREF_MAX - COM_VREF_VALBACK)

#define COM_VREF_LVP_TIME                               (10)//��ʱʱ��(ms)
#define COM_VREF_LVP_VAL                                (COM_VREF_MIN)//
#define COM_VREF_LVP_VAL_BACK                           (COM_VREF_MIN + COM_VREF_VALBACK)	
/***************************************************************************/
/***************************************************************************/


/*------------------------------------------------------------------------------------*/
//��س������������޲�������
/*------------------------------------------------------------------------------------*/
#define COM_CHG_IBAT_OCP1                               (45.0)//(A)
#define COM_CHG_IBAT_OCP2                               (45.0)//(A)
#define COM_CHG_IBAT_CP_VALBACK                         ( 1.0)//����ʹ�õĻز�ֵ(A)
/*------------------------------------------------------------------------------------*/
//��������������
/*------------------------------------------------------------------------------------*/
#define CHG_IBAT_OCP1_TIME                              (50)//��ʱʱ��(ms)
#define CHG_IBAT_OCP2_TIME                              (50)//��ʱʱ��(ms)
#define CHG_IBAT_OCP1_VAL                               (COM_CHG_IBAT_OCP1 * COM_REAL_IBAT_CHG_SCAL)//��ʵ�����Ŵ�COM_REAL_IBAT_CHG_SCAL
#define CHG_IBAT_OCP2_VAL                               (COM_CHG_IBAT_OCP2 * COM_REAL_IBAT_CHG_SCAL)   
#define CHG_IBAT_OCP1_VAL_BACK                          ((COM_CHG_IBAT_OCP1 - COM_CHG_IBAT_CP_VALBACK) * COM_REAL_IBAT_CHG_SCAL)//
#define CHG_IBAT_OCP2_VAL_BACK                          ((COM_CHG_IBAT_OCP2 - COM_CHG_IBAT_CP_VALBACK) * COM_REAL_IBAT_CHG_SCAL) 

/*------------------------------------------------------------------------------------*/
//��طŵ�����������޲�������
/*------------------------------------------------------------------------------------*/
#define COM_DISC_IBAT_OCP1                              (100.0)//(A)
#define COM_DISC_IBAT_OCP2                              (100.0)//(A)
#define COM_DISC_IBAT_CP_VALBACK                        (  1.0)//����ʹ�õĻز�ֵ(A)
/*------------------------------------------------------------------------------------*/
//�ŵ������������
/*------------------------------------------------------------------------------------*/
#define DISC_IBAT_OCP1_TIME                             (50)//��ʱʱ��(ms)
#define DISC_IBAT_OCP2_TIME                             (50)//��ʱʱ��(ms)
#define DISC_IBAT_OCP1_VAL                              (COM_DISC_IBAT_OCP1 * COM_REAL_IBAT_DISC_SCAL)//��ʵ�����Ŵ�COM_REAL_IBAT_DISC_SCAL
#define DISC_IBAT_OCP2_VAL                              (COM_DISC_IBAT_OCP2 * COM_REAL_IBAT_DISC_SCAL) 
#define DISC_IBAT_OCP1_VAL_BACK                         ((COM_DISC_IBAT_OCP1 - COM_DISC_IBAT_CP_VALBACK) * COM_REAL_IBAT_DISC_SCAL)   
#define DISC_IBAT_OCP2_VAL_BACK                         ((COM_DISC_IBAT_OCP2 - COM_DISC_IBAT_CP_VALBACK) * COM_REAL_IBAT_DISC_SCAL)   


/*------------------------------------------------------------------------------------*/
//AD�ο�У׼ֵ��������
/*------------------------------------------------------------------------------------*/
#define COM_BASE_AD_CORRECT_VAL                         (2048)//Ԥ���׼ֵ
#define COM_BASE_AD_CORRECT_VALBACK                     ( 100)
//--------------------------------------------------------------------
/*VREF_ADУ��ֵ*/
//--------------------------------------------------------------------
#define COM_VREF_AD_CORRECT_UP                          (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_VREF_AD_CORRECT_MID                         (COM_BASE_AD_CORRECT_VAL)
#define COM_VREF_AD_CORRECT_DN                          (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------
/*��س���������ADУ��ֵ*/
//--------------------------------------------------------------------
#define COM_CHG_IBat_AD_CORRECT_UP                      (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_CHG_IBat_AD_CORRECT_MID                     (COM_BASE_AD_CORRECT_VAL)
#define COM_CHG_IBat_AD_CORRECT_DN                      (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------
/*��طŵ��������ADУ��ֵ*/
//--------------------------------------------------------------------
#define COM_DISC_IBat_AD_CORRECT_UP                     (COM_BASE_AD_CORRECT_VAL + COM_BASE_AD_CORRECT_VALBACK)
#define COM_DISC_IBat_AD_CORRECT_MID                    (COM_BASE_AD_CORRECT_VAL)
#define COM_DISC_IBat_AD_CORRECT_DN                     (COM_BASE_AD_CORRECT_VAL - COM_BASE_AD_CORRECT_VALBACK)
//--------------------------------------------------------------------


/*-------------------������ʱʱ���趨ֵ����Դ����--------------------------*/
#define COM_POWER_LOCK_TIME                             (1000)//ms

/***************************************************************************/
//������������ 
/***************************************************************************/ 
#define COM_KEY_SHUT_DOWN_ACTIVE_LEVEL                  (0)//��Ч��ƽ����0����1
#define COM_KEY_SHUT_DOWN_C_DELAY_COUNT                 (1000)//����������ʱʱ��(ms)
#define COM_KEY_SHUT_DOWN_R_DELAY_COUNT                 (100)//�ɿ�������ʱʱ��(ms)

#define COM_KEY_RESET_ACTIVE_LEVEL                      (0)//��Ч��ƽ����0����1
#define COM_KEY_RESET_C_DELAY_COUNT                     (200)//����������ʱʱ��(ms)
#define COM_KEY_RESET_R_DELAY_COUNT                     (200)//�ɿ�������ʱʱ��(ms)


/***************************************************************************/
//�������رշ����¶���ֵ����
/***************************************************************************/
#define COM_OPEN_FAN_TEMP_VALUE                         (1565)//����45�棬��������
#define COM_CLOSE_FAN_TEMP_VALUE                        (1786)//����35�棬�رշ���

/***************************************************************************/
//���ݳ�ŵ�����򿪷���
/***************************************************************************/
#define COM_OPEN_FAN_CHG_IBAT_VALUE                     (1.5 * COM_REAL_IBAT_CHG_SCAL)//����������
#define COM_OPEN_FAN_DISC_IBAT_VALUE                    (1.5 * COM_REAL_IBAT_DISC_SCAL)//��������
#define COM_CLOSE_FAN_CHG_IBAT_VALUE                    (1.4 * COM_REAL_IBAT_CHG_SCAL)//���رշ���
#define COM_CLOSE_FAN_DISC_IBAT_VALUE                   (1.4 * COM_REAL_IBAT_DISC_SCAL)//�رշ���

#endif 
