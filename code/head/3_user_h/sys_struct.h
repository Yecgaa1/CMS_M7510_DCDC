    
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

#ifndef __SYS_STRUCT_H
#define __SYS_STRUCT_H

#include "stdint.h"

/***************************************************************************/
/*-----------------------------常用数学工具宏定义--------------------------*/
/***************************************************************************/
#define ABSFUN(Value)			(Value)>=0?(Value):-(Value)

#define MAXFUN(varone,vartwo)    (varone)>(vartwo)?(varone):(vartwo)

#define UPDNLMTFUN(Var,Max,Min)	{(Var)=((Var)>=(Max))?(Max):(Var);(Var)=((Var)<=(Min))?(Min):(Var);}

//中断中调用
#define DFILTER(filnum,newinputval,oldoutputval)	(((((int32_t)(newinputval)<<16)-(oldoutputval))>>((filnum)+1))+(oldoutputval)) 

//非中断中调用
#define DFILTER_N(filnum1,newinputval1,oldoutputval1)	(((((int32_t)(newinputval1)<<16)-(oldoutputval1))>>((filnum1)+1))+(oldoutputval1)) 

//******************系统中用到的枚举常量**********************************
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
    E_KEY_CLOSE = 0  ,//按键闭合
    E_KEY_RELEASE	= 1//按键释放
}
KEY_STATE_e;//开/关两种状态

typedef enum
{
	E_MIN = 0,	   //进入保护时极限值为最小值，大于此值时有效
  	E_MAX = 1,	   //进入保护时极限值为最大值，小于此值时有效
  	E_EQUAL
}
Protect_Limit_Type_e;

typedef struct 
{
    uint8_t	        sys_PWM_Base:1;			    //PWM中断时基
    uint8_t	        sys_1ms:1;					//1ms时基有效位
    uint8_t	        sys_LED_1ms:1;				//LED1ms时基
    uint8_t	        sys_Mode_1ms:1;				//工作模式1ms时基
    uint8_t         sys_Check_1ms:1;		    //故障1ms时基有效位	
    uint8_t         Resbits:4;				    //预留位
}SysClockBase_t;
extern SysClockBase_t  SysClockBase_ms;

/***************************************************************************/
/***************************************************************************/
typedef enum
{
    E_OLP                       = ( 1 << 0  ),//0位       
    E_VBUS_OVP                  = ( 1 << 1  ),//1位
    E_VBUS_LVP                  = ( 1 << 2  ),//2位
    E_RES_OVP                   = ( 1 << 3  ),//3位
    E_RES_LVP                   = ( 1 << 4  ),//4位
    E_VREF_ERR                  = ( 1 << 5  ),//5位    
    E_AUX_POWER_OVP             = ( 1 << 6  ),//6位
    E_AUX_POWER_LVP             = ( 1 << 7  ),//7位    
    E_OTP                       = ( 1 << 8  ),//8位
    E_IBAT_CHG_OCP              = ( 1 << 9  ),//9位
    E_IBAT_DISC_OCP             = ( 1 << 10 ),//10位
    E_VBAT_OVP                  = ( 1 << 11 ),//11位
    E_VBAT_LVP                  = ( 1 << 12 ),//12位    
    E_SYS_INIT_FAIL             = ( 1 << 13 ),//13位
    E_INV_ERR                   = ( 1 << 14 ),//14位
    E_COMMUNICA_ERR             = ( 1 << 15 ),//15位
}
ProtectFlag_Position_e;
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
struct System_Protect_Flag_BITS
{
    unsigned short int OLP:            1;//0位  
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
    E_START_CHECK_VBUS_HIGH             = ( 1 << 0  ),//0位
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
    unsigned short int vBus_High_OK:        1;//0位 1
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
typedef struct _Protect_Check_Info//保护的进入/处理、和恢复的数据结构
{
    unsigned int short  status_Val;//保护对应的状态标志值
    unsigned int short  compare_Type;//比较类型：最大or最小
    unsigned int        period_Val;//计数多少次保护设定值
    unsigned int        period_Cnt;//计数值，唯一的一个变量，其它的都是初始化后不再改变
             int        ref_Val;//比较的参考值
             int        hysteretic_Val;//迟滞值
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
    int  vBat_AD_FIR; //电池电压
    int  vBusFB_AD;
    int  vBusFB_AD_FIR; //母线电压控制量(经硬件PI计算后的反馈值)
    int  iBat_CHG_AD;
    int  iBat_CHG_AD_FIR; //电池充电电流 
    int  iBat_DISC_AD;
    int  iBat_DISC_AD_FIR;//电池放电电流       
    int  auxPower_AD;
    int  auxPower_AD_FIR;
    int  temp_NTC_AD;
    int  temp_NTC_AD_FIR;
    int  ref_AD;
    int  ref_AD_FIR;        
   } ADSample_Var_t;
extern ADSample_Var_t    ADSample_Info;
   

/***************************************************************************/
/*----UARTx心跳监测结构体定义-----------------------------------------------------*/
/***************************************************************************/
typedef struct UARTx_Info
{
     uint8_t  heart_Status;
     uint8_t  heart_OK_Status;
    uint16_t  heart0_Cnt;     //心跳为0时计数值
    uint16_t  heart1_Cnt;     //心跳为1时计数值
    uint16_t  heart_Val;      //心跳正常阈值
     uint8_t  RXD_B[60];//接收的字节数组 (Byte)
     int32_t  RXD_W[30];//接收的字数组 (Word)
    uint8_t   TXD_B[30];//发送的字节数组 (Byte)
    int32_t   TXD_W[15];//发送的字数组 (Word)  
    uint16_t  TXD_Period_Cnt;
    uint16_t  TXD_Period_Val;//发送控制周期 
    uint16_t  TXD_CRC_Init;//发送时CRC初始值
    uint16_t  RXD_CRC_Init;//接收时CRC初始值     
    uint16_t  TXD_CRC_Calc;//Tx计算的CRC校验码    
    uint16_t  RXD_CRC_Calc;//Rx计算的CRC校验码
     uint8_t  RXD_CRC_Cnt;//接收时CRC处理计数
    uint16_t  RXD_CRC_CkCd;//接收的CRC校验码：Check Code
    uint8_t   TXD_Len;//发送字节长度
    uint8_t   RXD_Len;//接收字节长度
    uint8_t   RXD_Flag; //接收完成标志   
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
    unsigned short int in;//电平输入状态
    unsigned short int close_Cnt;//按键按下计数
    unsigned short int release_Cnt;//按键松开计数
    unsigned short int out_State;//闭合或者断开
    unsigned short int ref_Active_Level;//按键有效电平设置
    unsigned short int c_Delay_Val;//按下防抖设定值
    unsigned short int r_Delay_Val;//松开防抖设定值
    void  (*Calc)();
} Key_Var_t;               

typedef Key_Var_t *KeyInfo_handle;

/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void Key_Calc(KeyInfo_handle);
extern Key_Var_t	            Key_SW_ShutDown	;

               
/*------------------------------------------------------------------------------------*/
/*--------------------------------COM结构体定义--------------------------------------*/
typedef struct 
{ 
    int                                     INV_ERR_CODE;//INV开关使能标记；1：开逆变器；0：关逆变器

    uint8_t                                 Power_OnOff_Flag;

    uint8_t                                 operate_Mode;//开环工作：无保护功能；闭环工作：启用保护功能
    uint8_t                                 CHG_DISC_Mode_Select;//工作模式为充电模式或者放电模式

    uint16_t                                INV_VBus_AD;//后级逆变侧母线电压值   

    uint8_t                                 INTP3_Start_OK;//打开放电电流保护中断完成标志  
    uint16_t                                INTP3_Start_Cnt;//打开放电电流保护中断计数值
    uint16_t                                INTP3_Start_TimeVal;//打开放电电流保护中断延时时间
    
    uint16_t                                NO_Mode_OK_Cnt;//后级模式为空状态检测计数
    uint16_t                                NO_Mode_OK_TimeVal;//后级模式为空状态设定时间
    
    uint16_t                                PFC_Mode_OK_Cnt;//后级模式为PFC检测计数
    uint16_t                                PFC_Mode_OK_TimeVal;//后级模式为PFC设定时间
    uint16_t                                INV_Mode_OK_Cnt;//后级模式为INV检测计数
    uint16_t                                INV_Mode_OK_TimeVal;//后级模式为INV设定时间    
    uint8_t                                 INV_PFC_Mode_Select;//后级工作模式:2-PFC模式; 1-INV模式 ; 0-空闲状态
    uint8_t                                 INV_PFC_Ready_Status;//通信传输逆变侧准备好状态    

    uint8_t                                 PWM_Enable;//使能驱动标志



int test1_cnt;     
//int test_cnt; 
//int test_cnt1;
int intuerrupt_test_flag; 
int intuerrupt_test_flag1;     
}COM_Ctr_Var_t;
extern  COM_Ctr_Var_t		COM_Ctr_Info;                

 
/*------------------------------------------------------------------------------------*/
/*--------------------------------LED结构体定义--------------------------------------*/
typedef struct 
{ 
    uint8_t                                  flag_1ms;  
    uint16_t                                 period_Cnt;// 周期时间计数
    uint16_t                                 on_Val;//点亮时间设定
    uint16_t                                 period_Val;//闪烁周期设定
    
    uint8_t                                 cycle_Cnt;// 循环次数计数
    uint8_t                                 cycle_Val;//循环次数设定    
    
}LED_Ctr_Var_t;
extern  LED_Ctr_Var_t		LED_Ctr_Info; 



/*------------------------------------------------------------------------------------*/
/*--------------------------------INV侧ToDC侧数据结构体定义--------------------------------------*/
typedef struct 
{ 
    uint8_t                                 mode_State;//工作模式：放电或者充电 
    uint8_t                                 ready_State;//准备状态
    uint16_t                                err_Code;//故障码
    uint16_t                                VBusAD_Val;//母线电压值
    uint16_t                                VACOUT_RMS;//逆变输出电压值（RMS） 
    uint16_t                                VACOUT_Freq;//逆变输出电压频率（Hz）
    uint16_t                                VACOUT_Power;//逆变输出功率（W）
    uint16_t                                VACIN_RMS;//市电输入电压值（RMS）    
    uint16_t                                VACIN_Freq;//市电输入电压频率（Hz）
    uint16_t                                VACIN_PFC_Power;//市电输入PFC功率（W）
    uint16_t                                VACIN_BypassPower;//市电输入旁路功率（W）   
}InvToDC_Data_Var_t;
extern  InvToDC_Data_Var_t		InvToDC_Data_Info; 


/*------------------------------------------------------------------------------------*/
/*--------------------------------DC侧ToMC主控侧数据结构体定义------------------------*/
struct MC_Protect_Flag
{
    uint32_t INV_OLP:           1;//0位 输出过载  
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

    uint32_t DC_OLP:            1;//0位  
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
    union _MC_Protect_Flag                  Flag;//故障码
    uint8_t                                 mode_State;//工作模式：放电或者充电 
    uint16_t                                VACOUT_RMS;//逆变输出电压值（RMS） 
    uint16_t                                VACOUT_Freq;//逆变输出电压频率（Hz）
    uint16_t                                VACOUT_Power;//逆变输出功率（W）
    uint16_t                                VACIN_RMS;//市电输入电压值（RMS）    
    uint16_t                                VACIN_Freq;//市电输入电压频率（Hz）
    uint16_t                                VACIN_PFC_Power;//市电输入PFC功率（W）
    uint16_t                                VACIN_BypassPower;//市电输入旁路功率（W）
    uint16_t                                iBat_CHG;//电池充电电流     
    uint16_t                                iBat_DISC;//电池放电电流
    uint16_t                                vBat;//电池电压    
    uint16_t                                temp_NTC;//器件温度
    uint16_t                                vBat_CHG_Power;//电池充电功率（W）
    uint16_t                                vBat_DISC_Power;//电池放电功率（W）
    
}DcToMC_Data_Var_t;
extern  DcToMC_Data_Var_t		DcToMC_Data_Info; 

/*------------------------------------------------------------------------------------*/
/*---------------------------------BMS结构体定义--------------------------------------*/
struct _BMS_Order_Flag
{
    uint8_t Set_CC_Flag:  1; //中控发送指令设置恒流电流  
    uint8_t Set_CV_Flag:  1; //中控发送指令设置恒压电压 
    uint8_t Resbits:6;				    //预留位
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
	
}	BMS_Order_Var_t;//包含中控发送指令开关机，休眠唤醒，自主控制，

extern  BMS_Order_Var_t		BMS_Order_Info; 

/*------------------------------------------------------------------------------------*/
/*---------------------------------AD采样真实值处理定义-----------------------------*/
typedef struct 
{ 
    uint16_t                               vBat_CHG_Power;//电池充电功率（W）
    uint16_t                               vBat_DISC_Power;//电池放电功率（W）
    
    int32_t                                vRef_Val;//基准VRef电压
    int32_t                                vRef_Sum;//基准VRef电压
    int32_t                                vRef_Hold;//  
    int32_t                                vRef_Val_Fir;//基准VRef电压 
    
    int32_t                                auxPower_Val;//辅助电源电压
    int32_t                                auxPower_Sum;//辅助电源电压
    int32_t                                auxPower_Hold;//  
    int32_t                                auxPower_Val_Fir;//辅助电源电压     

    int32_t                                iBat_CHG_Val;//电池充电电流
    int32_t                                iBat_CHG_Sum;//电池充电电流
    int32_t                                iBat_CHG_Hold;//  
    int32_t                                iBat_CHG_Val_Fir;//电池充电电流 
    
    int32_t                                iBat_DISC_Val;//电池放电电流
    int32_t                                iBat_DISC_Sum;//电池放电电流    
    int32_t                                iBat_DISC_Hold;//  
    int32_t                                iBat_DISC_Val_Fir;//电池放电电流 
    
    int32_t                                vBat_Val;//电池电压
    int32_t                                vBat_Sum;//电池电压
    int32_t                                vBat_Hold;//  
    int32_t                                vBat_Val_Fir;//电池电压 
    
    int32_t                                temp_NTC_Val;//器件温度
    int32_t                                temp_NTC_Sum;//器件温度
    int32_t                                temp_NTC_Hold;//器件温度
    int32_t                                temp_NTC_Val_Fir;//器件温度    
    uint16_t                               Sum_Cnt;
    
}COM_AD_Data_Var_t;
extern  COM_AD_Data_Var_t		COM_AD_Data_Info; 

#endif
/***************************************************************************/

