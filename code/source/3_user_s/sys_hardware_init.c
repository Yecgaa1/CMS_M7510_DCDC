/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 对相应硬件外设功能进行配置初始化
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/
#include "sys_mcu_header.h"
#include "sys_hardware_init.h"
#include "user_function.h"
#include "base_type.h"
/***************************************************************************/

/*************************************************
Description: SystemClock_Init
Input      : 
Return     : 
Others     : EPWM配置 
*************************************************/
void SystemClock_Init(void)
{   
    CGC->CMC  |= (1<<6);//X1振荡模式
    CGC->OSTS |= 0x07;//振荡稳定时间的选择
    CGC->CSC &= ~(0x80);//将 CSC 寄存器的 MSTOP 位清“0”，使 X1 振荡电路开始振荡
    CGC->PLLCR = 0x83; //外部8MHZ PLL16倍频 128M主频
    CGC->MCKC |= 0x01;	

    while((CGC->OSTC & 0xff) != 0xff);

    //CGC->CKC |= (1<<4);//使用外部晶振（PLL倍频时bit4清零）
    
    SystemCoreClockUpdate();      
}


/*************************************************
Description: WDT_ConfigInit
Input      : 
Return     : 
Others     : 看门狗配置
*************************************************/
void WDT_ConfigInit(void)
{	
	
}


/*************************************************
Description: SysTick_ConfigInit
Input      : 
Return     : 
Others     : 系统定时器配置
*************************************************/
void SysTick_ConfigInit(void)
{
    
    //注意：使用内部时钟时可启用；使用晶振自行设置
    //SystemCoreClockUpdate();	//更新时钟状态，获取系统时钟
    
	uint32_t reload;
    
	reload         = SystemCoreClock/1000;
    SysTick->LOAD  =    (uint32_t)(reload - 1UL);                         /* set reload register */
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
    SysTick->VAL   =    0UL;                                             /* Load the SysTick Counter Value */
    SysTick->CTRL  =    SysTick_CTRL_CLKSOURCE_Msk |
                        SysTick_CTRL_TICKINT_Msk   |
                        SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */                                                    /* Function successful */

    
}


/*************************************************
Description: GPIO_Init
Input      : 
Return     : 
Others     : GPIO初始化配置
*************************************************/

void GPIO_Init(void)
{				
    /*LED控制配置 ，“0“表示点亮*/ 
	PORT->PMCD  &= ~(1<<7);//端口模式：数字输入/输出
	PORT->PMD   &= ~(1<<7);//输出模式
	PORT->POMD  &= ~(1<<7);//普通输出模式
    PORT->PSETD |=  (1<<7);//设置为高电平/* PD07 LED控制 */
  
    /* 发送BAT工作信号ToINV侧，“1“为ON*/ 
	PORT->PMCC  &= ~(1<<0);//端口模式：数字输入/输出
	PORT->PMC   &= ~(1<<0);//输出模式,
	PORT->POMC  &= ~(1<<0);//普通输出模式
    PORT->PCLRC |=  (1<<0);//设置为低电平/* PC00 发送BAT工作信号To逆变器侧 */

    
    /* 电源保持信号输出配置 ，“1“ON锁定*/
    //端口模式：数字输入/输出
	PORT->PME   &= ~(1<<7);//输出模式,
	PORT->POME  &= ~(1<<7);//普通输出模式
    PORT->PCLRE |=  (1<<7);//设置为低电平/* PE07 电源保持信号输出 */
  
    /* P140风扇启动信号输出配置 ，“1“表示ON*/  
	PORT->PMCD  &= ~(1<<2);//端口模式：数字输入/输出
	PORT->PMD   &= ~(1<<2);//输出模式
	PORT->POMD  &= ~(1<<2);//普通输出模式
    PORT->PCLRD |=  (1<<2);//设置为低电平/* PD02 风扇启动信号输出 */
       

    /* 按键关机信号输入配置，默认上拉输入(低电平有效)  */	
	PORT->PME   |= (1<<8);//输入模式
	PORT->POME  &= ~(1<<8);
	PORT->PUE   |= (1<<8);//PE08设置为上拉输入端口
    
    /* 接收INV侧逆变器工作信号，默认上拉输入(低电平有效) */	
	PORT->PMCC  &= ~(1<<1);//端口模式：数字输入/输出
	PORT->PMC   |= (1<<1);//输入模式
	PORT->POMC  &= ~(1<<1);
	PORT->PUC   |= (1<<1);//PC01设置为上拉输入端口

    /* 接收INV侧母线电压过压信号，默认上拉输入(低电平有效) */	
	PORT->PME   |= (1<<9);//输入模式
	PORT->POME  &= ~(1<<9);
	PORT->PUE   |= (1<<9);//PE09设置为上拉输入端口


}

/*************************************************
Description: EPWM_ConfigInit
Input      : 
Return     : 
Others     : EPWM配置 - M定时器
*************************************************/
void EPWM_ConfigInit(void)
{   
    /* pin config */
    PORT->PMC |= 0x3FCu<<0;
    PORT->POMC &= ~(0x3FCu<<0);
    
    
    PORT->PC02CFG = 0;  //GPT14-B
    PORT->PC03CFG = 0;  //GPT14-A
    PORT->PC04CFG = 0;  //GPT12-B
    PORT->PC05CFG = 0;  //GPT12-A
    PORT->PC06CFG = 0;  //GPT11-B
    PORT->PC07CFG = 0;  //GPT11-A
    PORT->PC08CFG = 0;  //GPT10-B
    PORT->PC09CFG = 0;  //GPT10-A


    CGC->PERA |= CGC_PERA_GPT1EN_Msk|CGC_PERA_PGIEN_Msk;
	  
    GPT1->GTWP10 = 0xA500;
    GPT1->GTSSR10 = (1UL<<31);
    GPT1->GTSSR11 = (1UL<<31);
    GPT1->GTSSR12 = (1UL<<31);
    GPT1->GTSSR14 = (1UL<<31);
    GPT1->GTSSR13 = (1UL<<31);
    
    GPT1->GTPSR10 = (1UL<<31);
    GPT1->GTPSR11 = (1UL<<31);
    GPT1->GTPSR12 = (1UL<<31);
    GPT1->GTPSR14 = (1UL<<31);
    GPT1->GTPSR13 = (1UL<<31);
    
    GPT1->GTCSR10 = (1UL<<31);
    GPT1->GTCSR11 = (1UL<<31);
    GPT1->GTCSR12 = (1UL<<31);
    GPT1->GTCSR14 = (1UL<<31);
    GPT1->GTCSR13 = (1UL<<31);
    
    GPT1->GTCLR10 = ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3)| (1 << 4) | (1 << 5))<<4;

    GPT1->GTUPSR10 = 0x00;
    GPT1->GTUPSR11 = 0x00;
    GPT1->GTUPSR12 = 0x00;
    GPT1->GTUPSR14 = 0x00;
    GPT1->GTUPSR13 = 0x00;
    
    GPT1->GTDNSR10 = 0x00;
    GPT1->GTDNSR11 = 0x00;
    GPT1->GTDNSR12 = 0x00;
    GPT1->GTDNSR14 = 0x00;
    GPT1->GTDNSR13 = 0x00;
    
    GPT1->GTICASR10 = 0x00;
    GPT1->GTICASR11 = 0x00;
    GPT1->GTICASR12 = 0x00;
    GPT1->GTICASR14 = 0x00;
    GPT1->GTICASR13 = 0x00;
    
    GPT1->GTICBSR10 = 0x00;
    GPT1->GTICBSR11 = 0x00;
    GPT1->GTICBSR12 = 0x00;
    GPT1->GTICBSR14 = 0x00;
    GPT1->GTICBSR13 = 0x00;
    
    GPT1->GTCR10 = GPT_MD_S_WAVE_ONE_SHOOT;//单次锯齿波，固定缓冲
    GPT1->GTCR11 = GPT_MD_S_WAVE_ONE_SHOOT;//单次锯齿波，固定缓冲
    GPT1->GTCR12 = GPT_MD_S_WAVE_ONE_SHOOT;//单次锯齿波，固定缓冲
    GPT1->GTCR14 = GPT_MD_S_WAVE_ONE_SHOOT;//单次锯齿波，固定缓冲    
    GPT1->GTCR13 = GPT_MD_S_WAVE_ONE_SHOOT;//单次锯齿波，固定缓冲 
    
    GPT1->GTUDDTYC10 = 0x08080000|GPT_CNT_UP;    
    GPT1->GTUDDTYC11 = 0x08080000|GPT_CNT_UP;   
    GPT1->GTUDDTYC12 = 0x08080000|GPT_CNT_UP;
    GPT1->GTUDDTYC14 = 0x08080000|GPT_CNT_UP;
    GPT1->GTUDDTYC13 = 0x08080000|GPT_CNT_UP;
    /* IO operation config */

    GPT1->GTIOR10 = ((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOA_OUT_MD_Pos)\
                    |((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOB_OUT_MD_Pos)\
                    |(GTIO_OADF_OUTPUT_0|GTIO_OBDF_OUTPUT_0|GPT_GTIOA_OUT_ENABLE|GPT_GTIOB_OUT_ENABLE);   
																				
    GPT1->GTIOR11 = ((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOA_OUT_MD_Pos)\
                    |((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOB_OUT_MD_Pos)\
                    |(GTIO_OADF_OUTPUT_0|GTIO_OBDF_OUTPUT_0|GPT_GTIOA_OUT_ENABLE|GPT_GTIOB_OUT_ENABLE);   
                                                            
    GPT1->GTIOR12 = ((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOA_OUT_MD_Pos)\
                    |((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOB_OUT_MD_Pos)\
                    |(GTIO_OADF_OUTPUT_0|GTIO_OBDF_OUTPUT_0|GPT_GTIOA_OUT_ENABLE|GPT_GTIOB_OUT_ENABLE); 
																				
    GPT1->GTIOR14 = ((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOA_OUT_MD_Pos)\
                    |((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOB_OUT_MD_Pos)\
                    |(GTIO_OADF_OUTPUT_0|GTIO_OBDF_OUTPUT_0|GPT_GTIOA_OUT_ENABLE|GPT_GTIOB_OUT_ENABLE);  
																				
    GPT1->GTIOR13 = ((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOA_OUT_MD_Pos)\
                    |((GTIO_OUT_INIT_LOW|GTIO_OUT_0_PERIOD|GTIO_OUT_SW_COMPARE)<<CPT_GTIOB_OUT_MD_Pos)\
                    |(GTIO_OADF_OUTPUT_0|GTIO_OBDF_OUTPUT_0); 
#if 0
    PORT->PB05CFG = 0x07;//GTETRGA
    PORT->PMB |= (1 << 5);
    PGI->POEGGC = (POEG_FILTER_CLK_8|POEG_NFEN_ENABLE|POEG_GTETRG_ENABLE|POEG_OSC_STOP_ENABLE);
    PGI->POEGGD = (POEG_FILTER_CLK_8|POEG_NFEN_ENABLE|POEG_GTETRG_ENABLE|POEG_OSC_STOP_ENABLE);
#endif

//    //比较器关闭GPT波形
//    PGI->POEGGC = (POEG_CMP3_ENABLE|POEG_OSC_STOP_ENABLE);
//    PGI->POEGGD = (POEG_CMP3_ENABLE|POEG_OSC_STOP_ENABLE);
//    PORT->PE01CFG = 0x07;//GTETRGA
//    PORT->PME |= (1 << 1);
    PGI->POEGGA = (POEG_OSC_STOP_ENABLE);

    GPT1->GTINTAD10 = 0x200000C0 ;  //C组刹车
    GPT1->GTINTAD11 = 0x200000C0 ;  //C组刹车
    GPT1->GTINTAD12 = 0x200000C0 ;  //D组刹车
    GPT1->GTINTAD14 = 0x200000C0 ;  //D组刹车
    GPT1->GTINTAD13 = 0x200000C0 ;
    
    /* clear status register */
    GPT1->GTST10 = 0x00000000;  
    GPT1->GTST11 = 0x00000000;   
    GPT1->GTST12 = 0x00000000; 
    GPT1->GTST14 = 0x00000000;
    GPT1->GTST13 = 0x00000000;
    
    /* clear counter register */
    GPT1->GTCNT10 = 0x00000000;
    GPT1->GTCNT11 = 0x00000000; 
    GPT1->GTCNT12 = 0x00000000;
    GPT1->GTCNT14 = 0x00000000;
    GPT1->GTCNT13 = 0x00000000;

    /* initialize period register  */
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//设置GTCNT的最大计数值
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR13  = DC_Ctrl_Info.EPWM_Period;
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//用作 GTPR 的缓冲区寄存器
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//采样触发点设定   
    
    /* initialize dead time control register    */
    GPT1->GTDTCR10 = 0x00000000;//GTDCTR_DEADTIME_ENABLE;
    GPT1->GTDTCR11 = 0x00000000;//GTDCTR_DEADTIME_ENABLE;
    GPT1->GTDTCR12 = 0x00000000;//GTDCTR_DEADTIME_ENABLE;
    GPT1->GTDTCR14 = 0x00000000;
    GPT1->GTDTCR13 = 0x00000000;
    
    /* initialize dead register for ADC trigger  */
    GPT1->GTDVU10 = 0x00000000;
    GPT1->GTDVU11 = 0x00000000;
    GPT1->GTDVU12 = 0x00000000;
    GPT1->GTDVU14 = 0x00000000;
    GPT1->GTDVU13 = 0x00000000;



    /* config buffer operation */
    GPT1->GTBER10 = (GBER_BUF_A_SINGLE|GBER_BUF_B_SINGLE|GBER_BUF_PERIOD_SIGNLE|GBER_BUF_AB_FORCE|GBER_BUF_GTCCR_ENABLE|GBER_BUF_PR_ENABLE);  
    GPT1->GTBER11 = (GBER_BUF_A_SINGLE|GBER_BUF_B_SINGLE|GBER_BUF_PERIOD_SIGNLE|GBER_BUF_AB_FORCE|GBER_BUF_GTCCR_ENABLE|GBER_BUF_PR_ENABLE);   
    GPT1->GTBER12 = (GBER_BUF_A_SINGLE|GBER_BUF_B_SINGLE|GBER_BUF_PERIOD_SIGNLE|GBER_BUF_AB_FORCE|GBER_BUF_GTCCR_ENABLE|GBER_BUF_PR_ENABLE);
    GPT1->GTBER14 = (GBER_BUF_A_SINGLE|GBER_BUF_B_SINGLE|GBER_BUF_PERIOD_SIGNLE|GBER_BUF_AB_FORCE|GBER_BUF_GTCCR_ENABLE|GBER_BUF_PR_ENABLE);
    GPT1->GTBER13 = (GBER_BUF_A_SINGLE|GBER_BUF_B_SINGLE|GBER_BUF_PERIOD_SIGNLE|GBER_BUF_AB_FORCE|GBER_BUF_GTCCR_ENABLE|GBER_BUF_PR_ENABLE);
   
    GPT1->OPSCR = 0x00000000;
    
    //封管
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%


    //对 GTCLR 寄存器某比特位写1时，清除与之相对应通道的GTCNT计数器
    GPT1->GTSTR10 = ((1 << 0) | (1 << 1) | (1 << 2)| (1 << 3) | (1 << 4) )<<4;
    //GPT1->GTSTR10 = ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) )<<4;
}


/*************************************************
Description: CHG_PWM_Enable
Input      : 
Return     : 
Others     : 充电模式时开启相关PWM引脚
*************************************************/
void CHG_PWM_Enable(void)
{    
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    
    /* initialize period register  */
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//设置GTCNT的最大计数值
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR13  = DC_Ctrl_Info.EPWM_Period;
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//用作 GTPR 的缓冲区寄存器
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;  
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//采样触发点设定 

    GPT1->GTCCRC12 = 0;	
    GPT1->GTCCRD12 = DC_Ctrl_Info.EPWM_Duty;
    GPT1->GTCCRE12 = (DC_Ctrl_Info.EPWM_Period>>1);	
    GPT1->GTCCRF12 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
        
    GPT1->GTCCRC14 = 0;	
    GPT1->GTCCRD14 = DC_Ctrl_Info.EPWM_Duty;
    GPT1->GTCCRE14 = (DC_Ctrl_Info.EPWM_Period>>1);	
    GPT1->GTCCRF14 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
    
    GPT1->GTCCRC10 = DC_Ctrl_Info.SR_ON_LTime;	
    GPT1->GTCCRD10 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
    GPT1->GTCCRE10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
    GPT1->GTCCRF10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
        
    GPT1->GTCCRC11 = DC_Ctrl_Info.SR_ON_LTime;	
    GPT1->GTCCRD11 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
    GPT1->GTCCRE11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
    GPT1->GTCCRF11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            
}


/*************************************************
Description: DISC_PWM_Enable
Input      : 
Return     : 
Others     : 放电模式时开启相关PWM引脚
*************************************************/
void DISC_PWM_Enable(void)
{
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    
    /* initialize period register  */
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//设置GTCNT的最大计数值
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    //GPT1->GTPR13 = DC_Ctrl_Info.EPWM_Period;//采样触发点设定
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//用作 GTPR 的缓冲区寄存器
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//采样触发点设定 

    GPT1->GTCCRC10 = 0;	
    GPT1->GTCCRD10 = DC_Ctrl_Info.EPWM_Duty;
    GPT1->GTCCRE10 = (DC_Ctrl_Info.EPWM_Period>>1);	
    GPT1->GTCCRF10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
        
    GPT1->GTCCRC11 = 0;	
    GPT1->GTCCRD11 = DC_Ctrl_Info.EPWM_Duty;
    GPT1->GTCCRE11 = (DC_Ctrl_Info.EPWM_Period>>1);	
    GPT1->GTCCRF11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
    
}


/*************************************************
Description: COM_PWM_Disable
Input      : 
Return     : 
Others     : 关闭PWM输出
*************************************************/

void COM_PWM_Disable(void)
{
    DC_Ctrl_Info.EPWM_DutyB             = SR_MIN_TIME;
    DC_Ctrl_Info.EPWM_Duty              = SR_MIN_TIME;

    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%

    BAT_START_DISABLE;
}


/*************************************************
Description: ADC_ConfigInit
Input      : 
Return     : 
Others     : 高速ADC配置
*************************************************/
void ADC_ConfigInit(void)
{
    ADC_Type *padc;

    CGC->PERA |= CGC_PERA_ADC0EN_Msk|CGC_PERA_ADC1EN_Msk|CGC_PERA_ADC2EN_Msk;
    
    padc = ADC0;
    padc->ADANSA   = 0;//A组通道从(AN000 到 AN007)中选择用于A/D转换的模拟通道
    padc->ADANSB   = 0;
    padc->ADANSC   = 0;
    padc->ADCLKDIV  = 0x01u;  //ADCLK为系统时钟的2分频
//    padc->ADCER = (1 << 5);//启用自动清除。
    padc->ADCER = 0;

    padc = (ADC_Type *)ADC2;
    padc->ADANSA = 0;
    padc->ADANSB = 0;
    padc->ADANSC = 0;
    padc->ADCLKDIV = 0x01u;
//    padc->ADCER = (1 << 5);
    padc->ADCER = 0;

    // A/D 触发选择寄存器(ADSTRGR)
    /* 防止A组与B组赋值相互覆盖 */
    //TRGA4N:来自联动控制器ELSR08的触发; 
    ADC0->ADSTRGR =  (ADC_TRS_TRGA4N <<ADSTRGR_TRSA_Pos)|(0x3F <<ADSTRGR_TRSB_Pos);//
    // A/D 控制寄存器(ADCSR)
    //组扫描模式;扫描完成时允许产生中断;使能同步或异步触发启动 A/D 转换;禁止双触发模式;B 组扫描完成时允许产生中断
    ADC0->ADCSR = (1<<ADCSR_ADCS_Pos) | (1<<ADCSR_ADIE_Pos) | (1<<ADCSR_TRGE_Pos) | (0<<ADCSR_DBLE_Pos) | (0<<ADCSR_GBADIE_Pos);
	
    ADC0->ADANSA |= (1<<ADC_CHANNEL_1);//充电电流    
    ADC0->ADANSA |= (1<<ADC_CHANNEL_2); //电池电压
    		
	PORT->PMCA |= (1<<1); //设置为模拟通道  PA01	ANI001	VCHG_AD
    PORT->PMCA |= (1<<2); //设置为模拟通道  PA02	ANI002	VBAT_AD
		

    // A/D 触发选择寄存器(ADSTRGR)
    /* 防止A组与B组赋值相互覆盖 */
    //TRGA4N:来自联动控制器ELSR08的触发;
    ADC2->ADSTRGR =  (ADC_TRS_TRGA5N <<ADSTRGR_TRSA_Pos)|(0x3F <<ADSTRGR_TRSB_Pos);//
    // A/D 控制寄存器(ADCSR)
    //组扫描模式;扫描完成时允许产生中断;使能同步或异步触发启动 A/D 转换;禁止双触发模式;B 组扫描完成时允许产生中断
    ADC2->ADCSR = (1<<ADCSR_ADCS_Pos) | (1<<ADCSR_ADIE_Pos) | (1<<ADCSR_TRGE_Pos) | (0<<ADCSR_DBLE_Pos) | (0<<ADCSR_GBADIE_Pos);
	
    ADC2->ADANSA |= (1<<ADC_CHANNEL_2);//母线电压控制反馈    
    ADC2->ADANSA |= (1<<ADC_CHANNEL_3); //VREF
    ADC2->ADANSA |= (1<<ADC_CHANNEL_4);//放电电流    
    ADC2->ADANSA |= (1<<ADC_CHANNEL_12); //辅助电源
    ADC2->ADANSA |= (1<<ADC_CHANNEL_15);//器件温度    
    
	PORT->PMCA |= (1<<8); //设置为模拟通道  PA08	ANI202	
    PORT->PMCA |= (1<<9); //设置为模拟通道  PA09	ANI203	
	PORT->PMCA |= (1<<10);//设置为模拟通道  PA10	ANI204	
    PORT->PMCB |= (1<<1); //设置为模拟通道  PB01	ANI212	
	PORT->PMCB |= (1<<4); //设置为模拟通道  PB04	ANI215	

//    ELC->ELSR09 = 96;   /* GPT1CH0GTCNT上溢, TRGA5N */  // 
//    ELC->ELSR08 = 96;   /* GPT1CH0GTCNT上溢, TRGA4N */  // 

    ELC->ELSR09 = 114;   /* GPT1CH3GTCCRA比较, TRGA5N */  // 
    ELC->ELSR08 = 114;   /* GPT1CH3GTCCRA比较, TRGA4N */  // 
    ELC->ELCR = (1<<15); // ELCR 寄存器是 EVENTC 的使能控制寄存器，使用 EVENTC 功能前必须将 ELCR 寄存器的 bit15 设置为 1

}


/*************************************************
Description: DAC0_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void DAC0_ConfigInit(uint16_t vol)
{
    CGC->PERA |= CGC_PERA_DACEN_Msk;

    //注意：DAC输出到端口时，IO口必须配置模拟端口
    DAC->DAM |= 0x40;//D/A转换结果ANOi不输出到端口
    
//    PORT->PMB |= (1 << 2);   
//    PORT->PMCB |= (1 << 2);    
    DAC->DACS0 = vol;
    DAC->DAM |= (1 << 4);//允许D/A转换
}
/*************************************************
Description: DAC1_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void DAC1_ConfigInit(uint16_t vol)
{
    CGC->PERA |= CGC_PERA_DACEN_Msk;
    //注意：DAC输出到端口时，IO口必须配置模拟端口
    DAC->DAM |= 0x80;//D/A转换结果ANOi不输出到端口
//    PORT->PMB |= (1 << 3);
//    PORT->PMCB |= (1 << 3);    
    DAC->DACS1 = vol;   //VANOi=VDD *(DACSi)/256
    DAC->DAM |= (1u << 5);//允许D/A转换
}
/*************************************************
Description: ACMP0_ConfigInit
Input      : 
Return     : 
Others     : ACMP0配置：
*************************************************/
void ACMP0_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //使能比较器时钟
	CMP0->COMPMDR = CMP_STOP; //禁止比较器的运行
	CMP0->COMPSEL = CMP0_CMPSEL_PA04|CMP0_CREFS0_DAC0;//正端PA04，负端DAC0
	CMP0->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //普通输出模式；输出不反相；
	CMP0->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//上升沿产生中断请求;通过FCLK进行采样滤波;单边沿检测产生中断请求
	NVIC_ClearPendingIRQ(CMP0_IRQn);
	CMP0->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//正迟滞20mv
    
    //PA04 比较器0正端输入IO口
	PORT->PMA |= 1<<4;//PA04 输入模式
	PORT->PMCA |= 1<<4;//配置为模拟通道

//    //PB02 比较器1输出IO口
//	PORT->PMB &= ~(0x04);//PB02 输出模式
//	PORT->PMCB &= ~(0x04);//输入输出通道
    
	CMP0->COMPMDR = CMP_START; //启动比较器
    
	//CMP0->COMP0OCR |= CMP_OUT_PIN_Enable;//允许VCOUT输出到引脚
     	

}


/*************************************************
Description: ACMP1_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void ACMP1_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //使能比较器时钟
	CMP1->COMPMDR = CMP_STOP; //禁止比较器的运行
	CMP1->COMPSEL = CMP1_CMPSEL_PA05|CMP1_CREFS0_DAC1;//正端PA03，负端DAC1
	CMP1->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //普通输出模式；输出不反相；
	CMP1->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//上升沿产生中断请求;通过FCLK进行采样滤波;单边沿检测产生中断请求
	NVIC_ClearPendingIRQ(CMP1_IRQn);
	CMP1->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//正迟滞20mv
    
    //PA05 比较器1正端输入IO口 
	PORT->PMA |= 1<<5;//PA05  输入模式
	PORT->PMCA |= 1<<5;//配置为模拟通道

//    //PB03 比较器1输出IO口
//	PORT->PMB &= ~(0x08);//PB03 输出模式
//	PORT->PMCB &= ~(0x08);//输入输出通道
	
	CMP1->COMPMDR = CMP_START; //启动比较器
	//CMP1->COMP1OCR |= CMP_OUT_PIN_Enable;//允许VCOUT输出到引脚
      
}


/*************************************************
Description: ACMP3_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void ACMP3_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //使能比较器时钟
	CMP3->COMPMDR = CMP_STOP; //禁止比较器的运行
	CMP3->COMPSEL = CMP3_CMPSEL_PA03|CMP3_CREFS0_PB05;//正端PA03，负端CVREF1
	CMP3->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //普通输出模式；输出不反相；
	CMP3->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//上升沿产生中断请求;通过FCLK进行采样滤波;单边沿检测产生中断请求
	NVIC_ClearPendingIRQ(CMP3_IRQn);
	CMP3->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//正迟滞20mv

    //PA03 比较器3正端输入IO口 
	PORT->PMCA |= 1<<3;//配置为模拟通道

    //PB05 比较器3负端输入IO口 
	PORT->PMCB |= 1<<5;//配置为模拟通道
    
	CMP3->COMPMDR = CMP_START; //启动比较器
//	CMP3->COMPOCR |= CMP_OUT_PIN_Enable;//允许VCOUT输出到引脚

}


/*************************************************
Description: UART0_ConfigInit
Input      : 
Return     : 
Others     : UART0配置：逆变侧数据发送 （波特率9600）
*************************************************/
void UART0_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI0EN_Msk;//允许提供输入时钟
    SCI0->SPS = (0 << SCI0_SPS0_PRS00_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    /* transmission channel */
    SCI0->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI0->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _01_SCI_RXD0_FILTER_ON;//RxD0引脚的噪声滤波器使能
    SCI0->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//清除标志    
    //将下降沿检测为起始位,不将输入的通信数据进行反相;UART模式;RxDq引脚的有效边沿（在UART接收时选择）
    SCI0->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //只进行接收;8位数据长度;进行LSB优先的输入/输出;停止位长度=1位
    SCI0->SCRm1 = _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI0->SDRm1 = _CE00_SCI_BAUDRATE_DIVISOR;


    /* Set TxD0 pin */
    /* ToDo: You can allocate the TXD0 to PD06 pin */
    PORT->PD06CFG = 0x00;	    /* allocate TXD0 to PD06 */ 
    PORT->PMCD &=  ~(1 << 6);   // PD06
    PORT->PMD  &= ~(1 << 6);    /* PD06 is used as TXD0 output */ 
    PORT->POMD &= ~(1 << 6);    /* PD06 is push-pull output mode */ 
    PORT->PSETD =  (1 << 6);    /* PD06 output "H" */ 

    /* Set RxD0 pin */
    /* ToDo: You can allocate the RXD0 to PD08 pin */
    PORT->PD08CFG = 0x00;	    /* allocate RXD0 to PD08 */ 
    PORT->PMCD &=  ~(1 << 8);   // PD06 
    PORT->PMD  |=  (1 << 8);    /* PD06 is used as RXD0 input */ 
    

    /* UARTx Start, Setting baud rate */
    //波特率计算：128M/(2^6)/((103+1)*2) = 2M/208 = 9615 ≈ 9600 波特率
    //波特率计算：128M/(2^6)/((0+1)*2) = 2M/2 = 1M 波特率
    SCI0->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//停止通信运行
    SCI0->SPS &= ~SCI0_SPS0_PRS00_Msk;
    SCI0->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//运行时钟（CKmk）的选择
  
    SCI0->SDRm0 = 51 << 9;//运行时钟（F MCK ）的分频
    SCI0->SDRm1 = 51 << 9;

	/*
	(5)开启UARTx输出
	*/	    
    /* output enable */
    SCI0->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//串行数据的输出值为“1”
    SCI0->SOL = _0000_SCI_CHANNEL0_NORMAL;//将通信数据直接输出
    SCI0->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//允许串行通信的输出        
    SCI0->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//允许各通道的通信/开始计数的触发寄存器
}


/*************************************************
Description: UART1_ConfigInit
Input      : 
Return     : 
Others     : UART1配置： 
*************************************************/
void UART1_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI1EN_Msk;//允许提供输入时钟
    SCI1->SPS = (0 << SCI1_SPS1_PRS10_Pos) | (3 << SCI1_SPS1_PRS10_Pos);
    /* transmission channel */
    SCI1->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI1->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI1->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _04_SCI_RXD1_FILTER_ON;//RxD1引脚的噪声滤波器使能
    SCI1->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//清除标志    
    //将下降沿检测为起始位,不将输入的通信数据进行反相;UART模式;RxDq引脚的有效边沿（在UART接收时选择）
    SCI1->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //只进行接收;8位数据长度;进行LSB优先的输入/输出;停止位长度=1位
    SCI1->SCRm1 = _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI1->SDRm1 = _CE00_SCI_BAUDRATE_DIVISOR;
    
    /* Set TxD1 pin */
    /* ToDo: You can allocate the TXD1 to PD04 pin */
    PORT->PD04CFG = 0x05;	    /* allocate TXD1 to PD04 */ 
    PORT->PMCD &=  ~(1 << 4);   // PD04
    PORT->PMD  &= ~(1 << 4);    /* PD04 is used as TXD1 output */ 
    PORT->POMD &= ~(1 << 4);    /* PD04 is push-pull output mode */ 
    PORT->PSETD =  (1 << 4);    /* PD04 output "H" */ 

    /* Set RxD0 pin */
    /* ToDo: You can allocate the RXD1 to PD05 pin */
    PORT->PD05CFG = 0x05;	    /* allocate RXD1 to PD05 */ 
    PORT->PMCD &=  ~(1 << 5);   // PD05 
    PORT->PMD  |=  (1 << 5);    /* PD05 is used as RXD1 input */ 
    

    /* UARTx Start, Setting baud rate */
    //波特率计算：128M/(2^6)/((103+1)*2) = 2M/208 = 9615 ≈ 9600 波特率
    //波特率计算：128M/(2^6)/((0+1)*2) = 2M/2 = 1M 波特率
    SCI1->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//停止通信运行
    SCI1->SPS &= ~SCI1_SPS1_PRS10_Msk;
    SCI1->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//运行时钟（CKmk）的选择
  
    SCI1->SDRm0 = 0 << 9;//运行时钟（F MCK ）的分频
    SCI1->SDRm1 = 0 << 9;

	/*
	(5)开启UARTx输出
	*/	    
    /* output enable */
    SCI1->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//串行数据的输出值为“1”
    SCI1->SOL = _0000_SCI_CHANNEL0_NORMAL;//将通信数据直接输出
    SCI1->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//允许串行通信的输出        
    SCI1->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//允许各通道的通信/开始计数的触发寄存器
}


/*************************************************
Description: UART2_ConfigInit
Input      : 
Return     : 
Others     : UART2配置：
*************************************************/
void UART2_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI2EN_Msk;//允许提供输入时钟
    SCI2->SPS = (0 << SCI2_SPS2_PRS20_Pos) | (3 << SCI2_SPS2_PRS20_Pos);
    /* transmission channel */
    SCI2->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI2->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI2->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _10_SCI_RXD2_FILTER_ON;//RxD2引脚的噪声滤波器使能
    SCI2->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//清除标志    
    //将下降沿检测为起始位,不将输入的通信数据进行反相;UART模式;RxDq引脚的有效边沿（在UART接收时选择）
    SCI2->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //只进行接收;8位数据长度;进行LSB优先的输入/输出;停止位长度=1位
    SCI2->SCRm1 = _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI2->SDRm1 = _CE00_SCI_BAUDRATE_DIVISOR;
    
    /* Set TxD2 pin */
    /* ToDo: You can allocate the TXD2 to PD01 pin */
    PORT->PD01CFG = 0x05;	    /* allocate TXD2 to PD01 */ 
    PORT->PMCD &=  ~(1 << 1);   // PD01
    PORT->PMD  &= ~(1 << 1);    /* PD01 is used as TXD2 output */ 
    PORT->POMD &= ~(1 << 1);    /* PD01 is push-pull output mode */ 
    PORT->PSETD =  (1 << 1);    /* PD01 output "H" */ 

    /* Set RxD2 pin */
    /* ToDo: You can allocate the RXD2 to PD00 pin */
    PORT->PD00CFG = 0x05;	    /* allocate RXD2 to PD00 */ 
    PORT->PMCD &=  ~(1 << 0);   // PD00 
    PORT->PMD  |=  (1 << 0);    /* PD00 is used as RXD2 input */ 
    

    /* UARTx Start, Setting baud rate */
    //波特率计算：128M/(2^6)/((103+1)*2) = 2M/208 = 9615 ≈ 9600 波特率
    //波特率计算：128M/(2^6)/((0+1)*2) = 2M/2 = 1M 波特率
    SCI2->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//停止通信运行
    SCI2->SPS &= ~SCI2_SPS2_PRS20_Msk;
    SCI2->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//运行时钟（CKmk）的选择
    
    SCI2->SDRm0 = 0 << 9;//运行时钟（F MCK ）的分频
    SCI2->SDRm1 = 0 << 9;   
//    SCI2->SDR20 = 103 << 9;//运行时钟（F MCK ）的分频
//    SCI2->SDR21 = 103 << 9;

	/*
	(5)开启UARTx输出
	*/	    
    /* output enable */
    SCI2->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//串行数据的输出值为“1”
    SCI2->SOL = _0000_SCI_CHANNEL0_NORMAL;//将通信数据直接输出
    SCI2->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//允许串行通信的输出        
    SCI2->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//允许各通道的通信/开始计数的触发寄存器
 
    
}


/*************************************************
Description: Sys_IE_Init
Input      : 
Return     : 
Others     : 中断使能初始化
*************************************************/
void Sys_IE_Init(void)
{
    //NVIC_SetPriorityGrouping(0x03); 
    
    CGC->IWDTCTL = 0x0000;
    IWDT->WDTE  = 0xAC;//
    
//    NVIC_SetPriority(WDT1_IRQn,7);  /* Set higher priority to execute slave ISR firstly */

//    NVIC_EnableIRQ(WDT1_IRQn);
    
    
	/* Enable GPT0_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(GPT0_ELCOVF0_IRQn);    /* clear GPT0 interrupt flag */ 
    #if 0
        NVIC_SetPriority(GPT0_ELCOVF0_IRQn,4);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(GPT0_ELCOVF0_IRQn);
    #else
        NVIC_DisableIRQ(GPT0_ELCOVF0_IRQn);     /* disable GPT0 interrupt */     
    #endif
    
    
	/* Enable GPT1_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(GPT1_ELCOVF0_IRQn);    /* clear GPT1 interrupt flag */ 
    #if 1
        NVIC_SetPriority(GPT1_ELCOVF0_IRQn,4);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(GPT1_ELCOVF0_IRQn);
    #else
        NVIC_DisableIRQ(GPT1_ELCOVF0_IRQn);     /* disable GPT1_ELCOVF0 interrupt */     
    #endif
    
    
    /* Enable ADC0_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(ADC0_ADIREQ_N_IRQn);    /* clear ADC0 interrupt flag */ 
    #if 0
        NVIC_SetPriority(ADC0_ADIREQ_N_IRQn,3);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(ADC0_ADIREQ_N_IRQn);
    #else
        NVIC_DisableIRQ(ADC0_ADIREQ_N_IRQn);     /* disable ADC0_ADIREQ interrupt */     
    #endif
    
    
    /* Enable ADC2_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(ADC2_ADIREQ_N_IRQn);    /* clear ADC2 interrupt flag */ 
    #if 0
        NVIC_SetPriority(ADC2_ADIREQ_N_IRQn,3);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(ADC2_ADIREQ_N_IRQn);
    #else
        NVIC_DisableIRQ(ADC2_ADIREQ_N_IRQn);     /* disable ADC2_ADIREQ interrupt */     
    #endif
    

	/* Enable ACMP0_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(CMP0_IRQn);     /* clear INTCMP0 interrupt flag */ 
    #if 0 //PASS 
        CMP0->COMPOCR |=CMP_INT_Enable;//允许中断		 //允许比较器0的中断请求	
        NVIC_EnableIRQ(CMP0_IRQn);      /* enable INTCMP0 interrupt */    
        NVIC_SetPriority(CMP0_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
    #else
        NVIC_DisableIRQ(CMP0_IRQn);    /* clear INTCMP0 interrupt flag */       
    #endif
	
	
	/* Enable ACMP1_INT (0：优先级最高; 7:优先级最低)*/
    NVIC_ClearPendingIRQ(CMP1_IRQn);     /* clear INTCMP1 interrupt flag */     
    #if 0  //PASS
        CMP1->COMPOCR |=CMP_INT_Enable;//允许中断		 //允许比较器1的中断请求	
        NVIC_SetPriority(CMP1_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(CMP1_IRQn);          /* enable INTCMP1 interrupt */    
    #else
        NVIC_DisableIRQ(CMP1_IRQn);    /* clear INTCMP1 interrupt flag */       
    #endif


	/* Enable UART0_INT (0：优先级最高; 8:优先级最低)*/
    NVIC_ClearPendingIRQ(ST0_IRQn); /* clear INTST0 interrupt flag */
    NVIC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR0 interrupt flag */
    #if 0
        //NVIC_EnableIRQ(ST0_IRQn);       /* enable INTST0 interrupt */
        NVIC_EnableIRQ(SR0_IRQn);       /* enable INTSR0 interrupt */
        NVIC_SetPriority(SR0_IRQn,5);  /* Set higher priority to execute slave ISR firstly */        
    #else
        NVIC_DisableIRQ(ST0_IRQn);      /* disable INTST0 interrupt */
        NVIC_DisableIRQ(SR0_IRQn);      /* disable INTSR0 interrupt */
    #endif
    
    
	/* Enable UART1_INT (0：优先级最高; 3:优先级最低)*/
    NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    NVIC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
    #if 0
        //INTC_EnableIRQ(ST1_IRQn);       /* enable INTST1 interrupt */
        NVIC_EnableIRQ(SR1_IRQn);       /* enable INTSR1 interrupt */   
        NVIC_SetPriority(SR1_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
    #else
        NVIC_DisableIRQ(ST1_IRQn);      /* disable INTST1 interrupt */
        NVIC_DisableIRQ(SR1_IRQn);      /* disable INTSR1 interrupt */
    #endif    
   
    
    
}
extern uint8_t txBuf[24];
/*************************************************
Description: DMA_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void DMA_ConfigInit(void)
{
    //DMA_UART_TXD0初始化配置
    DMA_Start(DMA_VECTOR_0, 0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, UART0_SEND_NUM, (void *)&UART0_Info.TXD_B[1], (void *)&SCI0->TXD);
	ELC_Start(ELC_EVENT17_LINK_DMA0, ELC_EVENT_ST0_IRQn);
    DMA->DMAEN0 |= 1<<DMA_VECTOR_0;   

    //DMA_UART_RXD0初始化配置
    DMA_Start(DMA_VECTOR_1, 1, DMA_MODE_NORMAL, DMA_SIZE_BYTE, UART0_RECE_NUM, (void *)&SCI0->RXD ,(void *)&UART0_Info.RXD_B[0]);
        
//    DMAVEC->VEC[DMA_VECTOR_1] = 1;
//    DMAVEC->CTRL[1].DMACR = (DMA_SIZE_BYTE << DMAVEC_CTRL_DMACR_SZ_Pos)    | (0 << DMAVEC_CTRL_DMACR_RPTINT_Pos)|
//                                        (0 << DMAVEC_CTRL_DMACR_DAMOD_Pos) | (0 << DMAVEC_CTRL_DMACR_SAMOD_Pos) |
//                                        (0 << DMAVEC_CTRL_DMACR_RPTSEL_Pos)| (DMA_MODE_REPEAT << DMAVEC_CTRL_DMACR_MODE_Pos);
//    DMAVEC->CTRL[1].DMBLS = 1;
//    DMAVEC->CTRL[1].DMACT = UART0_RECE_NUM;
//    DMAVEC->CTRL[1].DMRLD = UART0_RECE_NUM;
//    DMAVEC->CTRL[1].DMSAR = (uint32_t)(void *)&SCI0->RXD;
//    DMAVEC->CTRL[1].DMDAR = (uint32_t)(void *)&UART0_Info.RXD_B[0];
    

    ELC_Start(ELC_EVENT18_LINK_DMA1, ELC_EVENT_SR0_IRQn);
    DMA->DMAEN0 |= 1<<DMA_VECTOR_1;  
    
    //DMA_UART_TXD2初始化配置
    DMA_Start(DMA_VECTOR_2, 2, DMA_MODE_NORMAL, DMA_SIZE_BYTE, 23, (void *)&txBuf[1], (void *)&SCI2->TXD);
	ELC_Start(ELC_EVENT19_LINK_DMA2, ELC_EVENT_ST2_IRQn);
    DMA->DMAEN0 |= 1<<DMA_VECTOR_2; 
}
  
/*************************************************
Description: Sys_HardConfigInit
Input      : 
Return     : 
Others     : 系统硬件配置初始化
*************************************************/
void Sys_HardConfigInit(void)
{
    
    //系统时钟初始化 	
    SystemClock_Init();
    
    // IO端口初始化配置
    GPIO_Init();
    
    //滴答定时器初始化
    SysTick_ConfigInit();	

    //User_DelayTime_ms(200); 
    
    //采样校准初始化
    AD_CorrectInit(); 
    
    //DAC0初始化
    DAC0_ConfigInit(COM_DAC0_VREF);
    
    //DAC1初始化
    DAC1_ConfigInit(COM_DAC1_VREF);
    
    //比较器0初始化    
    ACMP0_ConfigInit();
    
    //比较器1初始化
    ACMP1_ConfigInit();

    //比较器3初始化
    ACMP3_ConfigInit();
    
    //DMA初始化
    DMA_ConfigInit();  
    
    //UART0初始化 
//    UART0_ConfigInit();
    UART_Init(SCI0, SystemCoreClock, COM_UART0_BAUDRATE);
    
    
//    //UART1初始化 
//    UART1_ConfigInit();
    UART_Init(SCI1, SystemCoreClock, COM_UART1_BAUDRATE);
    
    //UART2初始化 
    //UART2_ConfigInit();
    UART_Init(SCI2, SystemCoreClock, COM_UART2_BAUDRATE);
    
    //ADC初始化
    ADC_ConfigInit();
       
    //EPWM初始化    
    EPWM_ConfigInit();  
    
    User_DelayTime_ms(20); 
    
    //中断使能初始化
    Sys_IE_Init();

    BAT_START_DISABLE;

}




