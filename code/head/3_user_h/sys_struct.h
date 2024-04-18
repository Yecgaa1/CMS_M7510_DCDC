    
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

#ifndef __SYS_STRUCT_H
#define __SYS_STRUCT_H

#include "stdint.h"

/***************************************************************************/
/*-----------------------------������ѧ���ߺ궨��--------------------------*/
/***************************************************************************/
#define ABSFUN(Value)			(Value)>=0?(Value):-(Value)

#define MAXFUN(varone,vartwo)    (varone)>(vartwo)?(varone):(vartwo)

#define UPDNLMTFUN(Var,Max,Min)	{(Var)=((Var)>=(Max))?(Max):(Var);(Var)=((Var)<=(Min))?(Min):(Var);}

//�ж��е���
#define DFILTER(filnum,newinputval,oldoutputval)	(((((int32_t)(newinputval)<<16)-(oldoutputval))>>((filnum)+1))+(oldoutputval)) 

//���ж��е���
#define DFILTER_N(filnum1,newinputval1,oldoutputval1)	(((((int32_t)(newinputval1)<<16)-(oldoutputval1))>>((filnum1)+1))+(oldoutputval1)) 

//******************ϵͳ���õ���ö�ٳ���**********************************
typedef enum
{
  	E_FALSE = 0,
	E_TRUE  = 1,
	E_FAIL  = 2
}
Logic_Value_e;

typedef enum
{
  	E_DISABLE,	
	E_ENABLE
}
Sys_Enable_e;

typedef enum
{
    E_KEY_CLOSE = 0  ,//�����պ�
    E_KEY_RELEASE	= 1//�����ͷ�
}
KEY_STATE_e;//��/������״̬

typedef enum
{
	E_MIN = 0,	   //���뱣��ʱ����ֵΪ��Сֵ�����ڴ�ֵʱ��Ч
  	E_MAX = 1,	   //���뱣��ʱ����ֵΪ���ֵ��С�ڴ�ֵʱ��Ч
  	E_EQUAL
}
Protect_Limit_Type_e;

typedef struct 
{
    uint8_t	        sys_PWM_Base:1;			    //PWM�ж�ʱ��
    uint8_t	        sys_1ms:1;					//1msʱ����Чλ
    uint8_t	        sys_LED_1ms:1;				//LED1msʱ��
    uint8_t	        sys_Mode_1ms:1;				//����ģʽ1msʱ��
    uint8_t         sys_Check_1ms:1;		    //����1msʱ����Чλ	
    uint8_t         Resbits:4;				    //Ԥ��λ
}SysClockBase_t;
extern SysClockBase_t  SysClockBase_ms;

/***************************************************************************/
/***************************************************************************/
typedef enum
{
    E_OLP                       = ( 1 << 0  ),//0λ       
    E_VBUS_OVP                  = ( 1 << 1  ),//1λ
    E_VBUS_LVP                  = ( 1 << 2  ),//2λ
    E_RES_OVP                   = ( 1 << 3  ),//3λ
    E_RES_LVP                   = ( 1 << 4  ),//4λ
    E_VREF_ERR                  = ( 1 << 5  ),//5λ    
    E_AUX_POWER_OVP             = ( 1 << 6  ),//6λ
    E_AUX_POWER_LVP             = ( 1 << 7  ),//7λ    
    E_OTP                       = ( 1 << 8  ),//8λ
    E_IBAT_CHG_OCP              = ( 1 << 9  ),//9λ
    E_IBAT_DISC_OCP             = ( 1 << 10 ),//10λ
    E_VBAT_OVP                  = ( 1 << 11 ),//11λ
    E_VBAT_LVP                  = ( 1 << 12 ),//12λ    
    E_SYS_INIT_FAIL             = ( 1 << 13 ),//13λ
    E_INV_ERR                   = ( 1 << 14 ),//14λ
    E_COMMUNICA_ERR             = ( 1 << 15 ),//15λ
}
ProtectFlag_Position_e;
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
struct System_Protect_Flag_BITS
{
    unsigned short int OLP:            1;//0λ  
    unsigned short int vBus_OVP:           1;//2
    unsigned short int vBus_LVP:            1;//4
    unsigned short int RES_OVP:         1;//8
    unsigned short int RES_LVP:          1;//16
    unsigned short int vref_ERR:          1;//32
    unsigned short int auxPower_OVP:       1;//64
    unsigned short int auxPower_LVP:        1;//128
    unsigned short int OTP:           1;//256
    unsigned short int iBAT_CHG_OCP:        1;//512
    unsigned short int iBAT_DISC_OCP:       1;//1024
    unsigned short int vBAT_OVP:           1;//2048
    unsigned short int vBAT_LVP:            1;//4096
    unsigned short int sys_Init_Fail:       1;//8192
    unsigned short int INV_ERR:           1;
    unsigned short int communica_ERR:     1;//

};
typedef union _System_Protect_Flag
{
	unsigned short int                   all;
	struct System_Protect_Flag_BITS      bit;
}System_Protect_Flag_u;
extern System_Protect_Flag_u System_ProtectFlag_Info;

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
typedef enum
{
    E_START_CHECK_VBUS_HIGH             = ( 1 << 0  ),//0λ
    E_START_CHECK_VBUS_LOW              = ( 1 << 1  ),
    E_START_CHECK_AUX_POWER_HIGH        = ( 1 << 2  ),
    E_START_CHECK_AUX_POWER_LOW         = ( 1 << 3  ),
    E_START_CHECK_AC_VOL_HIGH           = ( 1 << 4  ),
    E_START_CHECK_AC_VOL_LOW            = ( 1 << 5  ),
    E_START_CHECK_VBAT_HIGH             = ( 1 << 6  ),
    E_START_CHECK_VBAT_LOW              = ( 1 << 7  ),
    E_START_CHECK_TEMP_HIGH             = ( 1 << 8  )
}StartCheckFlag_Position_e;
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
struct StartCheck_Flag_BITS
{
    unsigned short int vBus_High_OK:        1;//0λ 1
    unsigned short int vBus_Low_OK:         1;//2
    unsigned short int auxPower_High_OK:    1;//4
    unsigned short int auxPower_Low_OK:     1;//8
    unsigned short int AC_Vol_High_OK:      1;//16
    unsigned short int AC_Vol_Low_OK:       1;//32
    unsigned short int vBAT_High_OK:        1;//64
    unsigned short int vBAT_Low_OK:         1;//128
    unsigned short int temp_High_OK:        1;//256
    unsigned short int rsvd:                7;
};
typedef union _StartCheck_Flag
{
    unsigned short int                   all;
    struct StartCheck_Flag_BITS          bit;
}StartCheck_Flag_u;
extern StartCheck_Flag_u StartCheck_Flag_Info;
/***************************************************************************/


/***************************************************************************/
/*--Protect flag information-----------------------------------------------*/
/***************************************************************************/
typedef struct _Protect_Check_Info//�����Ľ���/�����ͻָ������ݽṹ
{
    unsigned int short  status_Val;//������Ӧ��״̬��־ֵ
    unsigned int short  compare_Type;//�Ƚ����ͣ����or��С
    unsigned int        period_Val;//�������ٴα����趨ֵ
    unsigned int        period_Cnt;//����ֵ��Ψһ��һ�������������Ķ��ǳ�ʼ�����ٸı�
             int        ref_Val;//�ȽϵĲο�ֵ
             int        hysteretic_Val;//����ֵ
}
Protect_Check_Var_t;

extern Protect_Check_Var_t      COM_CHG_OLP1_Info;
extern Protect_Check_Var_t      COM_CHG_OLP2_Info;
extern Protect_Check_Var_t      COM_DISC_OLP1_Info;
extern Protect_Check_Var_t      COM_DISC_OLP2_Info;


extern Protect_Check_Var_t      CHG_IBAT_OCP1_Info;
extern Protect_Check_Var_t      CHG_IBAT_OCP2_Info;
extern Protect_Check_Var_t      DISC_IBAT_OCP1_Info;
extern Protect_Check_Var_t      DISC_IBAT_OCP2_Info;


extern Protect_Check_Var_t      COM_AuxPower_OVP_Info;
extern Protect_Check_Var_t      COM_AuxPower_LVP_Info;


extern Protect_Check_Var_t      COM_VBat_OVP_Info;
extern Protect_Check_Var_t      COM_VBat_LVP1_Info;
extern Protect_Check_Var_t      COM_VBat_LVP2_Info;


extern Protect_Check_Var_t      COM_OTP1_Info;
extern Protect_Check_Var_t      COM_OTP2_Info;

extern Protect_Check_Var_t      COM_Vref_OVP_Info;
extern Protect_Check_Var_t      COM_Vref_LVP_Info;


extern Protect_Check_Var_t      COM_StartCheck_AuxPower_Up;
extern Protect_Check_Var_t      COM_StartCheck_AuxPower_Down;

extern Protect_Check_Var_t      COM_StartCheck_VBAT_Up;
extern Protect_Check_Var_t      COM_StartCheck_VBAT_Down;

extern Protect_Check_Var_t      COM_StartCheck_Temp_Up;
/***************************************************************************/



/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
struct _ADSample_RefCorrect_Flag
{
    unsigned short int ADRef_Correct_Ok:  1;
    unsigned short int Rsvd:              15;
};
union ADSample_RefCorrect_Flag
{
    unsigned short int                    all;
    struct _ADSample_RefCorrect_Flag      bit; 
};
typedef struct _ADSample_RefCorrect
{
    union ADSample_RefCorrect_Flag        Flag; 
    int                                   sum;
    int                                   sum_Cnt;
    int                                   up_Limit;
    int                                   mid_Limit;
    int                                   down_Limit;
    int                                   out_Val;
}AD_Correct_Var_t;
extern AD_Correct_Var_t   AD_Correct_CHG_IBat;
extern AD_Correct_Var_t   AD_Correct_DISC_IBat;
extern AD_Correct_Var_t   AD_Correct_Vref;

/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
typedef struct 
{             
    int  vBat_AD;
    int  vBat_AD_FIR; //��ص�ѹ
    int  vBusFB_AD;
    int  vBusFB_AD_FIR; //ĸ�ߵ�ѹ������(��Ӳ��PI�����ķ���ֵ)
    int  iBat_CHG_AD;
    int  iBat_CHG_AD_FIR; //��س����� 
    int  iBat_DISC_AD;
    int  iBat_DISC_AD_FIR;//��طŵ����       
    int  auxPower_AD;
    int  auxPower_AD_FIR;
    int  temp_NTC_AD;
    int  temp_NTC_AD_FIR;
    int  ref_AD;
    int  ref_AD_FIR;        
   } ADSample_Var_t;
extern ADSample_Var_t    ADSample_Info;
   

/***************************************************************************/
/*----UARTx�������ṹ�嶨��-----------------------------------------------------*/
/***************************************************************************/
typedef struct UARTx_Info
{
     uint8_t  heart_Status;
     uint8_t  heart_OK_Status;
    uint16_t  heart0_Cnt;     //����Ϊ0ʱ����ֵ
    uint16_t  heart1_Cnt;     //����Ϊ1ʱ����ֵ
    uint16_t  heart_Val;      //����������ֵ
     uint8_t  RXD_B[60];//���յ��ֽ����� (Byte)
     int32_t  RXD_W[30];//���յ������� (Word)
    uint8_t   TXD_B[30];//���͵��ֽ����� (Byte)
    int32_t   TXD_W[15];//���͵������� (Word)  
    uint16_t  TXD_Period_Cnt;
    uint16_t  TXD_Period_Val;//���Ϳ������� 
    uint16_t  TXD_CRC_Init;//����ʱCRC��ʼֵ
    uint16_t  RXD_CRC_Init;//����ʱCRC��ʼֵ     
    uint16_t  TXD_CRC_Calc;//Tx�����CRCУ����    
    uint16_t  RXD_CRC_Calc;//Rx�����CRCУ����
     uint8_t  RXD_CRC_Cnt;//����ʱCRC�������
    uint16_t  RXD_CRC_CkCd;//���յ�CRCУ���룺Check Code
    uint8_t   TXD_Len;//�����ֽڳ���
    uint8_t   RXD_Len;//�����ֽڳ���
    uint8_t   RXD_Flag; //������ɱ�־   
}UARTx_Var_t;
extern UARTx_Var_t    UART0_Info;
//extern UARTx_Var_t    UART1_Info;


typedef struct {  
    unsigned short int        periodDot_Val;
    unsigned short int        periodDot_Val_4;
    unsigned short int        periodDot_Cnt;
                int        dot_Reciprocal;
                int        AC_Vol_Peak;
                int        curLoad_Peak;
                int        curInduc_Peak;
                int        sum_P;
                int        sum_Q;   
                int        sum_AC_Vol; 
                int        sum_CurLoad;  
                int        sum_CurInduc;  
                int        out_P;
                int        out_Q;
                int        out_S;    
                int        out_RMS_AC_Vol;
                int        out_RMS_CurLoad;
                int        out_RMS_CurInduc;
                void       (*Calc)();	 // Pointer to calculation function
}RMS_PQ_Var_t;

/*-----------------------------------------------------------------------------
Default initalizer for the PQ_Calc object.
-----------------------------------------------------------------------------*/
#define RMS_PQ_INFO_DEFAULTS { 0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         0,                        \
	                         (void*)0 }
/*------------------------------------------------------------------------------
Prototypes for the functions in PQ_Calc.C
------------------------------------------------------------------------------*/
extern RMS_PQ_Var_t    RMS_PQ_Info;  
void RMS_PQ_Calc(RMS_PQ_Var_t *rms_PQ);
void RMS_PQ_Update(RMS_PQ_Var_t *rms_PQ);
                             

/***************************************************************************/
typedef struct 
{
    unsigned short int in;//��ƽ����״̬
    unsigned short int close_Cnt;//�������¼���
    unsigned short int release_Cnt;//�����ɿ�����
    unsigned short int out_State;//�պϻ��߶Ͽ�
    unsigned short int ref_Active_Level;//������Ч��ƽ����
    unsigned short int c_Delay_Val;//���·����趨ֵ
    unsigned short int r_Delay_Val;//�ɿ������趨ֵ
    void  (*Calc)();
} Key_Var_t;               

typedef Key_Var_t *KeyInfo_handle;

/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void Key_Calc(KeyInfo_handle);
extern Key_Var_t	            Key_SW_ShutDown	;

               
/*------------------------------------------------------------------------------------*/
/*--------------------------------COM�ṹ�嶨��--------------------------------------*/
typedef struct 
{ 
    int                                     INV_ERR_CODE;//INV����ʹ�ܱ�ǣ�1�����������0���������

    uint8_t                                 Power_OnOff_Flag;

    uint8_t                                 operate_Mode;//�����������ޱ������ܣ��ջ����������ñ�������
    uint8_t                                 CHG_DISC_Mode_Select;//����ģʽΪ���ģʽ���߷ŵ�ģʽ

    uint16_t                                INV_VBus_AD;//������ĸ�ߵ�ѹֵ   

    uint8_t                                 INTP3_Start_OK;//�򿪷ŵ���������ж���ɱ�־  
    uint16_t                                INTP3_Start_Cnt;//�򿪷ŵ���������жϼ���ֵ
    uint16_t                                INTP3_Start_TimeVal;//�򿪷ŵ���������ж���ʱʱ��
    
    uint16_t                                NO_Mode_OK_Cnt;//��ģʽΪ��״̬������
    uint16_t                                NO_Mode_OK_TimeVal;//��ģʽΪ��״̬�趨ʱ��
    
    uint16_t                                PFC_Mode_OK_Cnt;//��ģʽΪPFC������
    uint16_t                                PFC_Mode_OK_TimeVal;//��ģʽΪPFC�趨ʱ��
    uint16_t                                INV_Mode_OK_Cnt;//��ģʽΪINV������
    uint16_t                                INV_Mode_OK_TimeVal;//��ģʽΪINV�趨ʱ��    
    uint8_t                                 INV_PFC_Mode_Select;//�󼶹���ģʽ:2-PFCģʽ; 1-INVģʽ ; 0-����״̬
    uint8_t                                 INV_PFC_Ready_Status;//ͨ�Ŵ�������׼����״̬    

    uint8_t                                 PWM_Enable;//ʹ��������־



int test1_cnt;     
//int test_cnt; 
//int test_cnt1;
int intuerrupt_test_flag; 
int intuerrupt_test_flag1;     
}COM_Ctr_Var_t;
extern  COM_Ctr_Var_t		COM_Ctr_Info;                

 
/*------------------------------------------------------------------------------------*/
/*--------------------------------LED�ṹ�嶨��--------------------------------------*/
typedef struct 
{ 
    uint8_t                                  flag_1ms;  
    uint16_t                                 period_Cnt;// ����ʱ�����
    uint16_t                                 on_Val;//����ʱ���趨
    uint16_t                                 period_Val;//��˸�����趨
    
    uint8_t                                 cycle_Cnt;// ѭ����������
    uint8_t                                 cycle_Val;//ѭ�������趨    
    
}LED_Ctr_Var_t;
extern  LED_Ctr_Var_t		LED_Ctr_Info; 



/*------------------------------------------------------------------------------------*/
/*--------------------------------INV��ToDC�����ݽṹ�嶨��--------------------------------------*/
typedef struct 
{ 
    uint8_t                                 mode_State;//����ģʽ���ŵ���߳�� 
    uint8_t                                 ready_State;//׼��״̬
    uint16_t                                err_Code;//������
    uint16_t                                VBusAD_Val;//ĸ�ߵ�ѹֵ
    uint16_t                                VACOUT_RMS;//��������ѹֵ��RMS�� 
    uint16_t                                VACOUT_Freq;//��������ѹƵ�ʣ�Hz��
    uint16_t                                VACOUT_Power;//���������ʣ�W��
    uint16_t                                VACIN_RMS;//�е������ѹֵ��RMS��    
    uint16_t                                VACIN_Freq;//�е������ѹƵ�ʣ�Hz��
    uint16_t                                VACIN_PFC_Power;//�е�����PFC���ʣ�W��
    uint16_t                                VACIN_BypassPower;//�е�������·���ʣ�W��   
}InvToDC_Data_Var_t;
extern  InvToDC_Data_Var_t		InvToDC_Data_Info; 


/*------------------------------------------------------------------------------------*/
/*--------------------------------DC��ToMC���ز����ݽṹ�嶨��------------------------*/
struct MC_Protect_Flag
{
    uint32_t INV_OLP:           1;//0λ �������  
    uint32_t INV_VBus_OVP:      1;//2
    uint32_t INV_VBus_LVP:      1;//4
    uint32_t VACOUT_OVP:        1;//8
    uint32_t VACOUT_LVP:        1;//16
    uint32_t VACOUT_SCP:        1;//32
    uint32_t INV_auxPower_OVP:  1;//64
    uint32_t INV_auxPower_LVP:  1;//128
    uint32_t INV_OTP:           1;//256
    uint32_t INV_iLoad_OCP:     1;//512
    uint32_t INV_iInduc_OCP:    1;//1024
    uint32_t INV_Init_Fail:     1;//2048
    uint32_t INV_DcErr:         1;//4096
    uint32_t INV_communica_Err: 1;//8192
    uint32_t INV_Vref_Err:      1;//16384
    uint32_t INV_RES:           1;//32768

    uint32_t DC_OLP:            1;//0λ  
    uint32_t DC_VBus_OVP:       1;//2
    uint32_t DC_VBus_LVP:       1;//4
    uint32_t RES_OVP:           1;//8
    uint32_t RES_LVP:           1;//16
    uint32_t DC_Vref_Err:       1;//32
    uint32_t DC_auxPower_OVP:   1;//64
    uint32_t DC_auxPower_LVP:   1;//128
    uint32_t DC_OTP:            1;//256
    uint32_t iBAT_CHG_OCP:      1;//512
    uint32_t iBAT_DISC_OCP:     1;//1024
    uint32_t vBAT_OVP:          1;//2048
    uint32_t vBAT_LVP:          1;//4096
    uint32_t DC_Init_Fail:      1;//8192
    uint32_t DC_InvErr:         1;//16384
    uint32_t DC_communica_Err:  1;//32768
};
union _MC_Protect_Flag
{
	uint32_t                    u32ErrCode;
	struct MC_Protect_Flag      bit;
};



typedef struct 
{ 
    union _MC_Protect_Flag                  Flag;//������
    uint8_t                                 mode_State;//����ģʽ���ŵ���߳�� 
    uint16_t                                VACOUT_RMS;//��������ѹֵ��RMS�� 
    uint16_t                                VACOUT_Freq;//��������ѹƵ�ʣ�Hz��
    uint16_t                                VACOUT_Power;//���������ʣ�W��
    uint16_t                                VACIN_RMS;//�е������ѹֵ��RMS��    
    uint16_t                                VACIN_Freq;//�е������ѹƵ�ʣ�Hz��
    uint16_t                                VACIN_PFC_Power;//�е�����PFC���ʣ�W��
    uint16_t                                VACIN_BypassPower;//�е�������·���ʣ�W��
    uint16_t                                iBat_CHG;//��س�����     
    uint16_t                                iBat_DISC;//��طŵ����
    uint16_t                                vBat;//��ص�ѹ    
    uint16_t                                temp_NTC;//�����¶�
    uint16_t                                vBat_CHG_Power;//��س�繦�ʣ�W��
    uint16_t                                vBat_DISC_Power;//��طŵ繦�ʣ�W��
    
}DcToMC_Data_Var_t;
extern  DcToMC_Data_Var_t		DcToMC_Data_Info; 

/*------------------------------------------------------------------------------------*/
/*---------------------------------BMS�ṹ�嶨��--------------------------------------*/
struct _BMS_Order_Flag
{
    uint8_t Set_CC_Flag:  1; //�пط���ָ�����ú�������  
    uint8_t Set_CV_Flag:  1; //�пط���ָ�����ú�ѹ��ѹ 
    uint8_t Resbits:6;				    //Ԥ��λ
};
union BMS_Order_Flag
{
    uint8_t     		 			    all;
    struct _BMS_Order_Flag              bit; 
};


typedef struct {

	union	BMS_Order_Flag	Flag;
	uint16_t	set_CC_Val;
	uint16_t	set_CV_Val;
	uint32_t	cnt1;
	
}	BMS_Order_Var_t;//�����пط���ָ��ػ������߻��ѣ��������ƣ�

extern  BMS_Order_Var_t		BMS_Order_Info; 

/*------------------------------------------------------------------------------------*/
/*---------------------------------AD������ʵֵ������-----------------------------*/
typedef struct 
{ 
    uint16_t                               vBat_CHG_Power;//��س�繦�ʣ�W��
    uint16_t                               vBat_DISC_Power;//��طŵ繦�ʣ�W��
    
    int32_t                                vRef_Val;//��׼VRef��ѹ
    int32_t                                vRef_Sum;//��׼VRef��ѹ
    int32_t                                vRef_Hold;//  
    int32_t                                vRef_Val_Fir;//��׼VRef��ѹ 
    
    int32_t                                auxPower_Val;//������Դ��ѹ
    int32_t                                auxPower_Sum;//������Դ��ѹ
    int32_t                                auxPower_Hold;//  
    int32_t                                auxPower_Val_Fir;//������Դ��ѹ     

    int32_t                                iBat_CHG_Val;//��س�����
    int32_t                                iBat_CHG_Sum;//��س�����
    int32_t                                iBat_CHG_Hold;//  
    int32_t                                iBat_CHG_Val_Fir;//��س����� 
    
    int32_t                                iBat_DISC_Val;//��طŵ����
    int32_t                                iBat_DISC_Sum;//��طŵ����    
    int32_t                                iBat_DISC_Hold;//  
    int32_t                                iBat_DISC_Val_Fir;//��طŵ���� 
    
    int32_t                                vBat_Val;//��ص�ѹ
    int32_t                                vBat_Sum;//��ص�ѹ
    int32_t                                vBat_Hold;//  
    int32_t                                vBat_Val_Fir;//��ص�ѹ 
    
    int32_t                                temp_NTC_Val;//�����¶�
    int32_t                                temp_NTC_Sum;//�����¶�
    int32_t                                temp_NTC_Hold;//�����¶�
    int32_t                                temp_NTC_Val_Fir;//�����¶�    
    uint16_t                               Sum_Cnt;
    
}COM_AD_Data_Var_t;
extern  COM_AD_Data_Var_t		COM_AD_Data_Info; 

#endif
/***************************************************************************/

