/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: ����ӦӲ�����蹦�ܽ������ó�ʼ��
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
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
Others     : EPWM���� 
*************************************************/
void SystemClock_Init(void)
{   
    CGC->CMC  |= (1<<6);//X1��ģʽ
    CGC->OSTS |= 0x07;//���ȶ�ʱ���ѡ��
    CGC->CSC &= ~(0x80);//�� CSC �Ĵ����� MSTOP λ�塰0����ʹ X1 �񵴵�·��ʼ��
    CGC->PLLCR = 0x83; //�ⲿ8MHZ PLL16��Ƶ 128M��Ƶ
    CGC->MCKC |= 0x01;	

    while((CGC->OSTC & 0xff) != 0xff);

    //CGC->CKC |= (1<<4);//ʹ���ⲿ����PLL��Ƶʱbit4���㣩
    
    SystemCoreClockUpdate();      
}


/*************************************************
Description: WDT_ConfigInit
Input      : 
Return     : 
Others     : ���Ź�����
*************************************************/
void WDT_ConfigInit(void)
{	
	
}


/*************************************************
Description: SysTick_ConfigInit
Input      : 
Return     : 
Others     : ϵͳ��ʱ������
*************************************************/
void SysTick_ConfigInit(void)
{
    
    //ע�⣺ʹ���ڲ�ʱ��ʱ�����ã�ʹ�þ�����������
    //SystemCoreClockUpdate();	//����ʱ��״̬����ȡϵͳʱ��
    
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
Others     : GPIO��ʼ������
*************************************************/

void GPIO_Init(void)
{				
    /*LED�������� ����0����ʾ����*/ 
	PORT->PMCD  &= ~(1<<7);//�˿�ģʽ����������/���
	PORT->PMD   &= ~(1<<7);//���ģʽ
	PORT->POMD  &= ~(1<<7);//��ͨ���ģʽ
    PORT->PSETD |=  (1<<7);//����Ϊ�ߵ�ƽ/* PD07 LED���� */
  
    /* ����BAT�����ź�ToINV�࣬��1��ΪON*/ 
	PORT->PMCC  &= ~(1<<0);//�˿�ģʽ����������/���
	PORT->PMC   &= ~(1<<0);//���ģʽ,
	PORT->POMC  &= ~(1<<0);//��ͨ���ģʽ
    PORT->PCLRC |=  (1<<0);//����Ϊ�͵�ƽ/* PC00 ����BAT�����ź�To������� */

    
    /* ��Դ�����ź�������� ����1��ON����*/
    //�˿�ģʽ����������/���
	PORT->PME   &= ~(1<<7);//���ģʽ,
	PORT->POME  &= ~(1<<7);//��ͨ���ģʽ
    PORT->PCLRE |=  (1<<7);//����Ϊ�͵�ƽ/* PE07 ��Դ�����ź���� */
  
    /* P140���������ź�������� ����1����ʾON*/  
	PORT->PMCD  &= ~(1<<2);//�˿�ģʽ����������/���
	PORT->PMD   &= ~(1<<2);//���ģʽ
	PORT->POMD  &= ~(1<<2);//��ͨ���ģʽ
    PORT->PCLRD |=  (1<<2);//����Ϊ�͵�ƽ/* PD02 ���������ź���� */
       

    /* �����ػ��ź��������ã�Ĭ����������(�͵�ƽ��Ч)  */	
	PORT->PME   |= (1<<8);//����ģʽ
	PORT->POME  &= ~(1<<8);
	PORT->PUE   |= (1<<8);//PE08����Ϊ��������˿�
    
    /* ����INV������������źţ�Ĭ����������(�͵�ƽ��Ч) */	
	PORT->PMCC  &= ~(1<<1);//�˿�ģʽ����������/���
	PORT->PMC   |= (1<<1);//����ģʽ
	PORT->POMC  &= ~(1<<1);
	PORT->PUC   |= (1<<1);//PC01����Ϊ��������˿�

    /* ����INV��ĸ�ߵ�ѹ��ѹ�źţ�Ĭ����������(�͵�ƽ��Ч) */	
	PORT->PME   |= (1<<9);//����ģʽ
	PORT->POME  &= ~(1<<9);
	PORT->PUE   |= (1<<9);//PE09����Ϊ��������˿�


}

/*************************************************
Description: EPWM_ConfigInit
Input      : 
Return     : 
Others     : EPWM���� - M��ʱ��
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
    
    GPT1->GTCR10 = GPT_MD_S_WAVE_ONE_SHOOT;//���ξ�ݲ����̶�����
    GPT1->GTCR11 = GPT_MD_S_WAVE_ONE_SHOOT;//���ξ�ݲ����̶�����
    GPT1->GTCR12 = GPT_MD_S_WAVE_ONE_SHOOT;//���ξ�ݲ����̶�����
    GPT1->GTCR14 = GPT_MD_S_WAVE_ONE_SHOOT;//���ξ�ݲ����̶�����    
    GPT1->GTCR13 = GPT_MD_S_WAVE_ONE_SHOOT;//���ξ�ݲ����̶����� 
    
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

//    //�Ƚ����ر�GPT����
//    PGI->POEGGC = (POEG_CMP3_ENABLE|POEG_OSC_STOP_ENABLE);
//    PGI->POEGGD = (POEG_CMP3_ENABLE|POEG_OSC_STOP_ENABLE);
//    PORT->PE01CFG = 0x07;//GTETRGA
//    PORT->PME |= (1 << 1);
    PGI->POEGGA = (POEG_OSC_STOP_ENABLE);

    GPT1->GTINTAD10 = 0x200000C0 ;  //C��ɲ��
    GPT1->GTINTAD11 = 0x200000C0 ;  //C��ɲ��
    GPT1->GTINTAD12 = 0x200000C0 ;  //D��ɲ��
    GPT1->GTINTAD14 = 0x200000C0 ;  //D��ɲ��
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
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//����GTCNT��������ֵ
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR13  = DC_Ctrl_Info.EPWM_Period;
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//���� GTPR �Ļ������Ĵ���
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//�����������趨   
    
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
    
    //���
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%


    //�� GTCLR �Ĵ���ĳ����λд1ʱ�������֮���Ӧͨ����GTCNT������
    GPT1->GTSTR10 = ((1 << 0) | (1 << 1) | (1 << 2)| (1 << 3) | (1 << 4) )<<4;
    //GPT1->GTSTR10 = ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) )<<4;
}


/*************************************************
Description: CHG_PWM_Enable
Input      : 
Return     : 
Others     : ���ģʽʱ�������PWM����
*************************************************/
void CHG_PWM_Enable(void)
{    
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    
    /* initialize period register  */
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//����GTCNT��������ֵ
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR13  = DC_Ctrl_Info.EPWM_Period;
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//���� GTPR �Ļ������Ĵ���
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;  
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//�����������趨 

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
Others     : �ŵ�ģʽʱ�������PWM����
*************************************************/
void DISC_PWM_Enable(void)
{
    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    
    /* initialize period register  */
    GPT1->GTPR10  = DC_Ctrl_Info.EPWM_Period;//����GTCNT��������ֵ
    GPT1->GTPR11  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR12  = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPR14  = DC_Ctrl_Info.EPWM_Period;
    //GPT1->GTPR13 = DC_Ctrl_Info.EPWM_Period;//�����������趨
    
    /* initialize period buffer register   */
    GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;//���� GTPR �Ļ������Ĵ���
    GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
    GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//�����������趨 

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
Others     : �ر�PWM���
*************************************************/

void COM_PWM_Disable(void)
{
    DC_Ctrl_Info.EPWM_DutyB             = SR_MIN_TIME;
    DC_Ctrl_Info.EPWM_Duty              = SR_MIN_TIME;

    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC13 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%
    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA��B �������ռ�ձ� 0%

    BAT_START_DISABLE;
}


/*************************************************
Description: ADC_ConfigInit
Input      : 
Return     : 
Others     : ����ADC����
*************************************************/
void ADC_ConfigInit(void)
{
    ADC_Type *padc;

    CGC->PERA |= CGC_PERA_ADC0EN_Msk|CGC_PERA_ADC1EN_Msk|CGC_PERA_ADC2EN_Msk;
    
    padc = ADC0;
    padc->ADANSA   = 0;//A��ͨ����(AN000 �� AN007)��ѡ������A/Dת����ģ��ͨ��
    padc->ADANSB   = 0;
    padc->ADANSC   = 0;
    padc->ADCLKDIV  = 0x01u;  //ADCLKΪϵͳʱ�ӵ�2��Ƶ
//    padc->ADCER = (1 << 5);//�����Զ������
    padc->ADCER = 0;

    padc = (ADC_Type *)ADC2;
    padc->ADANSA = 0;
    padc->ADANSB = 0;
    padc->ADANSC = 0;
    padc->ADCLKDIV = 0x01u;
//    padc->ADCER = (1 << 5);
    padc->ADCER = 0;

    // A/D ����ѡ��Ĵ���(ADSTRGR)
    /* ��ֹA����B�鸳ֵ�໥���� */
    //TRGA4N:��������������ELSR08�Ĵ���; 
    ADC0->ADSTRGR =  (ADC_TRS_TRGA4N <<ADSTRGR_TRSA_Pos)|(0x3F <<ADSTRGR_TRSB_Pos);//
    // A/D ���ƼĴ���(ADCSR)
    //��ɨ��ģʽ;ɨ�����ʱ��������ж�;ʹ��ͬ�����첽�������� A/D ת��;��ֹ˫����ģʽ;B ��ɨ�����ʱ��������ж�
    ADC0->ADCSR = (1<<ADCSR_ADCS_Pos) | (1<<ADCSR_ADIE_Pos) | (1<<ADCSR_TRGE_Pos) | (0<<ADCSR_DBLE_Pos) | (0<<ADCSR_GBADIE_Pos);
	
    ADC0->ADANSA |= (1<<ADC_CHANNEL_1);//������    
    ADC0->ADANSA |= (1<<ADC_CHANNEL_2); //��ص�ѹ
    		
	PORT->PMCA |= (1<<1); //����Ϊģ��ͨ��  PA01	ANI001	VCHG_AD
    PORT->PMCA |= (1<<2); //����Ϊģ��ͨ��  PA02	ANI002	VBAT_AD
		

    // A/D ����ѡ��Ĵ���(ADSTRGR)
    /* ��ֹA����B�鸳ֵ�໥���� */
    //TRGA4N:��������������ELSR08�Ĵ���;
    ADC2->ADSTRGR =  (ADC_TRS_TRGA5N <<ADSTRGR_TRSA_Pos)|(0x3F <<ADSTRGR_TRSB_Pos);//
    // A/D ���ƼĴ���(ADCSR)
    //��ɨ��ģʽ;ɨ�����ʱ��������ж�;ʹ��ͬ�����첽�������� A/D ת��;��ֹ˫����ģʽ;B ��ɨ�����ʱ��������ж�
    ADC2->ADCSR = (1<<ADCSR_ADCS_Pos) | (1<<ADCSR_ADIE_Pos) | (1<<ADCSR_TRGE_Pos) | (0<<ADCSR_DBLE_Pos) | (0<<ADCSR_GBADIE_Pos);
	
    ADC2->ADANSA |= (1<<ADC_CHANNEL_2);//ĸ�ߵ�ѹ���Ʒ���    
    ADC2->ADANSA |= (1<<ADC_CHANNEL_3); //VREF
    ADC2->ADANSA |= (1<<ADC_CHANNEL_4);//�ŵ����    
    ADC2->ADANSA |= (1<<ADC_CHANNEL_12); //������Դ
    ADC2->ADANSA |= (1<<ADC_CHANNEL_15);//�����¶�    
    
	PORT->PMCA |= (1<<8); //����Ϊģ��ͨ��  PA08	ANI202	
    PORT->PMCA |= (1<<9); //����Ϊģ��ͨ��  PA09	ANI203	
	PORT->PMCA |= (1<<10);//����Ϊģ��ͨ��  PA10	ANI204	
    PORT->PMCB |= (1<<1); //����Ϊģ��ͨ��  PB01	ANI212	
	PORT->PMCB |= (1<<4); //����Ϊģ��ͨ��  PB04	ANI215	

//    ELC->ELSR09 = 96;   /* GPT1CH0GTCNT����, TRGA5N */  // 
//    ELC->ELSR08 = 96;   /* GPT1CH0GTCNT����, TRGA4N */  // 

    ELC->ELSR09 = 114;   /* GPT1CH3GTCCRA�Ƚ�, TRGA5N */  // 
    ELC->ELSR08 = 114;   /* GPT1CH3GTCCRA�Ƚ�, TRGA4N */  // 
    ELC->ELCR = (1<<15); // ELCR �Ĵ����� EVENTC ��ʹ�ܿ��ƼĴ�����ʹ�� EVENTC ����ǰ���뽫 ELCR �Ĵ����� bit15 ����Ϊ 1

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

    //ע�⣺DAC������˿�ʱ��IO�ڱ�������ģ��˿�
    DAC->DAM |= 0x40;//D/Aת�����ANOi��������˿�
    
//    PORT->PMB |= (1 << 2);   
//    PORT->PMCB |= (1 << 2);    
    DAC->DACS0 = vol;
    DAC->DAM |= (1 << 4);//����D/Aת��
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
    //ע�⣺DAC������˿�ʱ��IO�ڱ�������ģ��˿�
    DAC->DAM |= 0x80;//D/Aת�����ANOi��������˿�
//    PORT->PMB |= (1 << 3);
//    PORT->PMCB |= (1 << 3);    
    DAC->DACS1 = vol;   //VANOi=VDD *(DACSi)/256
    DAC->DAM |= (1u << 5);//����D/Aת��
}
/*************************************************
Description: ACMP0_ConfigInit
Input      : 
Return     : 
Others     : ACMP0���ã�
*************************************************/
void ACMP0_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //ʹ�ܱȽ���ʱ��
	CMP0->COMPMDR = CMP_STOP; //��ֹ�Ƚ���������
	CMP0->COMPSEL = CMP0_CMPSEL_PA04|CMP0_CREFS0_DAC0;//����PA04������DAC0
	CMP0->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //��ͨ���ģʽ����������ࣻ
	CMP0->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//�����ز����ж�����;ͨ��FCLK���в����˲�;�����ؼ������ж�����
	NVIC_ClearPendingIRQ(CMP0_IRQn);
	CMP0->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//������20mv
    
    //PA04 �Ƚ���0��������IO��
	PORT->PMA |= 1<<4;//PA04 ����ģʽ
	PORT->PMCA |= 1<<4;//����Ϊģ��ͨ��

//    //PB02 �Ƚ���1���IO��
//	PORT->PMB &= ~(0x04);//PB02 ���ģʽ
//	PORT->PMCB &= ~(0x04);//�������ͨ��
    
	CMP0->COMPMDR = CMP_START; //�����Ƚ���
    
	//CMP0->COMP0OCR |= CMP_OUT_PIN_Enable;//����VCOUT���������
     	

}


/*************************************************
Description: ACMP1_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void ACMP1_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //ʹ�ܱȽ���ʱ��
	CMP1->COMPMDR = CMP_STOP; //��ֹ�Ƚ���������
	CMP1->COMPSEL = CMP1_CMPSEL_PA05|CMP1_CREFS0_DAC1;//����PA03������DAC1
	CMP1->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //��ͨ���ģʽ����������ࣻ
	CMP1->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//�����ز����ж�����;ͨ��FCLK���в����˲�;�����ؼ������ж�����
	NVIC_ClearPendingIRQ(CMP1_IRQn);
	CMP1->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//������20mv
    
    //PA05 �Ƚ���1��������IO�� 
	PORT->PMA |= 1<<5;//PA05  ����ģʽ
	PORT->PMCA |= 1<<5;//����Ϊģ��ͨ��

//    //PB03 �Ƚ���1���IO��
//	PORT->PMB &= ~(0x08);//PB03 ���ģʽ
//	PORT->PMCB &= ~(0x08);//�������ͨ��
	
	CMP1->COMPMDR = CMP_START; //�����Ƚ���
	//CMP1->COMP1OCR |= CMP_OUT_PIN_Enable;//����VCOUT���������
      
}


/*************************************************
Description: ACMP3_ConfigInit
Input      : 
Return     : 
Others     : 
*************************************************/
void ACMP3_ConfigInit(void)
{
	CGC->PERA |= (CGC_PERA_CMPPGAEN_Msk); //ʹ�ܱȽ���ʱ��
	CMP3->COMPMDR = CMP_STOP; //��ֹ�Ƚ���������
	CMP3->COMPSEL = CMP3_CMPSEL_PA03|CMP3_CREFS0_PB05;//����PA03������CVREF1
	CMP3->COMPOCR |= (CMP1_C0OTWMD_Dis|CMP_OUT_PHASE_Normal); //��ͨ���ģʽ����������ࣻ
	CMP3->COMPFIR |= (CMP_EDGE_UP|CMP_FILTER_FCLK_32);//�����ز����ж�����;ͨ��FCLK���в����˲�;�����ؼ������ж�����
	NVIC_ClearPendingIRQ(CMP3_IRQn);
	CMP3->COMPHY = (CMP_HY_Positive|CMP_HY_VALUE_20);//������20mv

    //PA03 �Ƚ���3��������IO�� 
	PORT->PMCA |= 1<<3;//����Ϊģ��ͨ��

    //PB05 �Ƚ���3��������IO�� 
	PORT->PMCB |= 1<<5;//����Ϊģ��ͨ��
    
	CMP3->COMPMDR = CMP_START; //�����Ƚ���
//	CMP3->COMPOCR |= CMP_OUT_PIN_Enable;//����VCOUT���������

}


/*************************************************
Description: UART0_ConfigInit
Input      : 
Return     : 
Others     : UART0���ã��������ݷ��� ��������9600��
*************************************************/
void UART0_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI0EN_Msk;//�����ṩ����ʱ��
    SCI0->SPS = (0 << SCI0_SPS0_PRS00_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    /* transmission channel */
    SCI0->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI0->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _01_SCI_RXD0_FILTER_ON;//RxD0���ŵ������˲���ʹ��
    SCI0->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//�����־    
    //���½��ؼ��Ϊ��ʼλ,���������ͨ�����ݽ��з���;UARTģʽ;RxDq���ŵ���Ч���أ���UART����ʱѡ��
    SCI0->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //ֻ���н���;8λ���ݳ���;����LSB���ȵ�����/���;ֹͣλ����=1λ
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
    //�����ʼ��㣺128M/(2^6)/((103+1)*2) = 2M/208 = 9615 �� 9600 ������
    //�����ʼ��㣺128M/(2^6)/((0+1)*2) = 2M/2 = 1M ������
    SCI0->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//ֹͣͨ������
    SCI0->SPS &= ~SCI0_SPS0_PRS00_Msk;
    SCI0->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//����ʱ�ӣ�CKmk����ѡ��
  
    SCI0->SDRm0 = 51 << 9;//����ʱ�ӣ�F MCK ���ķ�Ƶ
    SCI0->SDRm1 = 51 << 9;

	/*
	(5)����UARTx���
	*/	    
    /* output enable */
    SCI0->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//�������ݵ����ֵΪ��1��
    SCI0->SOL = _0000_SCI_CHANNEL0_NORMAL;//��ͨ������ֱ�����
    SCI0->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//������ͨ�ŵ����        
    SCI0->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//�����ͨ����ͨ��/��ʼ�����Ĵ����Ĵ���
}


/*************************************************
Description: UART1_ConfigInit
Input      : 
Return     : 
Others     : UART1���ã� 
*************************************************/
void UART1_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI1EN_Msk;//�����ṩ����ʱ��
    SCI1->SPS = (0 << SCI1_SPS1_PRS10_Pos) | (3 << SCI1_SPS1_PRS10_Pos);
    /* transmission channel */
    SCI1->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI1->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI1->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _04_SCI_RXD1_FILTER_ON;//RxD1���ŵ������˲���ʹ��
    SCI1->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//�����־    
    //���½��ؼ��Ϊ��ʼλ,���������ͨ�����ݽ��з���;UARTģʽ;RxDq���ŵ���Ч���أ���UART����ʱѡ��
    SCI1->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //ֻ���н���;8λ���ݳ���;����LSB���ȵ�����/���;ֹͣλ����=1λ
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
    //�����ʼ��㣺128M/(2^6)/((103+1)*2) = 2M/208 = 9615 �� 9600 ������
    //�����ʼ��㣺128M/(2^6)/((0+1)*2) = 2M/2 = 1M ������
    SCI1->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//ֹͣͨ������
    SCI1->SPS &= ~SCI1_SPS1_PRS10_Msk;
    SCI1->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//����ʱ�ӣ�CKmk����ѡ��
  
    SCI1->SDRm0 = 0 << 9;//����ʱ�ӣ�F MCK ���ķ�Ƶ
    SCI1->SDRm1 = 0 << 9;

	/*
	(5)����UARTx���
	*/	    
    /* output enable */
    SCI1->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//�������ݵ����ֵΪ��1��
    SCI1->SOL = _0000_SCI_CHANNEL0_NORMAL;//��ͨ������ֱ�����
    SCI1->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//������ͨ�ŵ����        
    SCI1->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//�����ͨ����ͨ��/��ʼ�����Ĵ����Ĵ���
}


/*************************************************
Description: UART2_ConfigInit
Input      : 
Return     : 
Others     : UART2���ã�
*************************************************/
void UART2_ConfigInit(void)
{
    CGC->PERA  |= CGC_PERA_SCI2EN_Msk;//�����ṩ����ʱ��
    SCI2->SPS = (0 << SCI2_SPS2_PRS20_Pos) | (3 << SCI2_SPS2_PRS20_Pos);
    /* transmission channel */
    SCI2->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI2->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCI2->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _10_SCI_RXD2_FILTER_ON;//RxD2���ŵ������˲���ʹ��
    SCI2->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;//�����־    
    //���½��ؼ��Ϊ��ʼλ,���������ͨ�����ݽ��з���;UARTģʽ;RxDq���ŵ���Ч���أ���UART����ʱѡ��
    SCI2->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    //ֻ���н���;8λ���ݳ���;����LSB���ȵ�����/���;ֹͣλ����=1λ
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
    //�����ʼ��㣺128M/(2^6)/((103+1)*2) = 2M/208 = 9615 �� 9600 ������
    //�����ʼ��㣺128M/(2^6)/((0+1)*2) = 2M/2 = 1M ������
    SCI2->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;//ֹͣͨ������
    SCI2->SPS &= ~SCI2_SPS2_PRS20_Msk;
    SCI2->SPS |= _0000_SCI_CK00_fCLK_0 | 6;//����ʱ�ӣ�CKmk����ѡ��
    
    SCI2->SDRm0 = 0 << 9;//����ʱ�ӣ�F MCK ���ķ�Ƶ
    SCI2->SDRm1 = 0 << 9;   
//    SCI2->SDR20 = 103 << 9;//����ʱ�ӣ�F MCK ���ķ�Ƶ
//    SCI2->SDR21 = 103 << 9;

	/*
	(5)����UARTx���
	*/	    
    /* output enable */
    SCI2->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;//�������ݵ����ֵΪ��1��
    SCI2->SOL = _0000_SCI_CHANNEL0_NORMAL;//��ͨ������ֱ�����
    SCI2->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;//������ͨ�ŵ����        
    SCI2->SS |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;//�����ͨ����ͨ��/��ʼ�����Ĵ����Ĵ���
 
    
}


/*************************************************
Description: Sys_IE_Init
Input      : 
Return     : 
Others     : �ж�ʹ�ܳ�ʼ��
*************************************************/
void Sys_IE_Init(void)
{
    //NVIC_SetPriorityGrouping(0x03); 
    
    CGC->IWDTCTL = 0x0000;
    IWDT->WDTE  = 0xAC;//
    
//    NVIC_SetPriority(WDT1_IRQn,7);  /* Set higher priority to execute slave ISR firstly */

//    NVIC_EnableIRQ(WDT1_IRQn);
    
    
	/* Enable GPT0_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(GPT0_ELCOVF0_IRQn);    /* clear GPT0 interrupt flag */ 
    #if 0
        NVIC_SetPriority(GPT0_ELCOVF0_IRQn,4);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(GPT0_ELCOVF0_IRQn);
    #else
        NVIC_DisableIRQ(GPT0_ELCOVF0_IRQn);     /* disable GPT0 interrupt */     
    #endif
    
    
	/* Enable GPT1_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(GPT1_ELCOVF0_IRQn);    /* clear GPT1 interrupt flag */ 
    #if 1
        NVIC_SetPriority(GPT1_ELCOVF0_IRQn,4);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(GPT1_ELCOVF0_IRQn);
    #else
        NVIC_DisableIRQ(GPT1_ELCOVF0_IRQn);     /* disable GPT1_ELCOVF0 interrupt */     
    #endif
    
    
    /* Enable ADC0_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(ADC0_ADIREQ_N_IRQn);    /* clear ADC0 interrupt flag */ 
    #if 0
        NVIC_SetPriority(ADC0_ADIREQ_N_IRQn,3);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(ADC0_ADIREQ_N_IRQn);
    #else
        NVIC_DisableIRQ(ADC0_ADIREQ_N_IRQn);     /* disable ADC0_ADIREQ interrupt */     
    #endif
    
    
    /* Enable ADC2_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(ADC2_ADIREQ_N_IRQn);    /* clear ADC2 interrupt flag */ 
    #if 0
        NVIC_SetPriority(ADC2_ADIREQ_N_IRQn,3);  /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(ADC2_ADIREQ_N_IRQn);
    #else
        NVIC_DisableIRQ(ADC2_ADIREQ_N_IRQn);     /* disable ADC2_ADIREQ interrupt */     
    #endif
    

	/* Enable ACMP0_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(CMP0_IRQn);     /* clear INTCMP0 interrupt flag */ 
    #if 0 //PASS 
        CMP0->COMPOCR |=CMP_INT_Enable;//�����ж�		 //����Ƚ���0���ж�����	
        NVIC_EnableIRQ(CMP0_IRQn);      /* enable INTCMP0 interrupt */    
        NVIC_SetPriority(CMP0_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
    #else
        NVIC_DisableIRQ(CMP0_IRQn);    /* clear INTCMP0 interrupt flag */       
    #endif
	
	
	/* Enable ACMP1_INT (0�����ȼ����; 7:���ȼ����)*/
    NVIC_ClearPendingIRQ(CMP1_IRQn);     /* clear INTCMP1 interrupt flag */     
    #if 0  //PASS
        CMP1->COMPOCR |=CMP_INT_Enable;//�����ж�		 //����Ƚ���1���ж�����	
        NVIC_SetPriority(CMP1_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
        NVIC_EnableIRQ(CMP1_IRQn);          /* enable INTCMP1 interrupt */    
    #else
        NVIC_DisableIRQ(CMP1_IRQn);    /* clear INTCMP1 interrupt flag */       
    #endif


	/* Enable UART0_INT (0�����ȼ����; 8:���ȼ����)*/
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
    
    
	/* Enable UART1_INT (0�����ȼ����; 3:���ȼ����)*/
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
    //DMA_UART_TXD0��ʼ������
    DMA_Start(DMA_VECTOR_0, 0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, UART0_SEND_NUM, (void *)&UART0_Info.TXD_B[1], (void *)&SCI0->TXD);
	ELC_Start(ELC_EVENT17_LINK_DMA0, ELC_EVENT_ST0_IRQn);
    DMA->DMAEN0 |= 1<<DMA_VECTOR_0;   

    //DMA_UART_RXD0��ʼ������
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
    
    //DMA_UART_TXD2��ʼ������
    DMA_Start(DMA_VECTOR_2, 2, DMA_MODE_NORMAL, DMA_SIZE_BYTE, 23, (void *)&txBuf[1], (void *)&SCI2->TXD);
	ELC_Start(ELC_EVENT19_LINK_DMA2, ELC_EVENT_ST2_IRQn);
    DMA->DMAEN0 |= 1<<DMA_VECTOR_2; 
}
  
/*************************************************
Description: Sys_HardConfigInit
Input      : 
Return     : 
Others     : ϵͳӲ�����ó�ʼ��
*************************************************/
void Sys_HardConfigInit(void)
{
    
    //ϵͳʱ�ӳ�ʼ�� 	
    SystemClock_Init();
    
    // IO�˿ڳ�ʼ������
    GPIO_Init();
    
    //�δ�ʱ����ʼ��
    SysTick_ConfigInit();	

    //User_DelayTime_ms(200); 
    
    //����У׼��ʼ��
    AD_CorrectInit(); 
    
    //DAC0��ʼ��
    DAC0_ConfigInit(COM_DAC0_VREF);
    
    //DAC1��ʼ��
    DAC1_ConfigInit(COM_DAC1_VREF);
    
    //�Ƚ���0��ʼ��    
    ACMP0_ConfigInit();
    
    //�Ƚ���1��ʼ��
    ACMP1_ConfigInit();

    //�Ƚ���3��ʼ��
    ACMP3_ConfigInit();
    
    //DMA��ʼ��
    DMA_ConfigInit();  
    
    //UART0��ʼ�� 
//    UART0_ConfigInit();
    UART_Init(SCI0, SystemCoreClock, COM_UART0_BAUDRATE);
    
    
//    //UART1��ʼ�� 
//    UART1_ConfigInit();
    UART_Init(SCI1, SystemCoreClock, COM_UART1_BAUDRATE);
    
    //UART2��ʼ�� 
    //UART2_ConfigInit();
    UART_Init(SCI2, SystemCoreClock, COM_UART2_BAUDRATE);
    
    //ADC��ʼ��
    ADC_ConfigInit();
       
    //EPWM��ʼ��    
    EPWM_ConfigInit();  
    
    User_DelayTime_ms(20); 
    
    //�ж�ʹ�ܳ�ʼ��
    Sys_IE_Init();

    BAT_START_DISABLE;

}




