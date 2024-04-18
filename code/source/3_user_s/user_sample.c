/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/
#include "sys_state_machine.h"
#include "sys_mcu_header.h"
/***************************************************************************/

/*************************************************
Description: AD_Vref_Correct
Input      : 
Return     : 
Others     : ��׼��ѹ2.5VУ׼
*************************************************/
int AD_temp = 0;
void AD_Vref_Correct(void)
{   
    ADC2->ADANSA = (0x08); //AN203 PA09  Bit3
    PORT->PMCA |= (1 << 9); /* Set ANI203(PA09) pin */
       
    if ( E_FALSE == AD_Correct_Vref.Flag.bit.ADRef_Correct_Ok )
    {     
        for(uint16_t i=0;i<15000;i++)
        {          
            ADC2->ADCSR = 0x8000; //ADCSR Bit15 ����ת��
            while(ADC2->ADCSR&0x8000){}; 
            AD_temp = ADC2->ADDR3;
        }        
        for(uint16_t i=0;i<1024;i++)
        {      
            ADC2->ADCSR = 0x8000; //ADCSR Bit15 ����ת��
            while(ADC2->ADCSR&0x8000){}; 
            AD_temp = ADC2->ADDR3;
            AD_Correct_Vref.sum  += AD_temp;  //VREF2.5V 
        }
        AD_Correct_Vref.out_Val = (AD_Correct_Vref.sum>>10); 
        AD_Correct_Vref.sum     = 0;
        
        if (( AD_Correct_Vref.out_Val < AD_Correct_Vref.up_Limit   ) &&\
            ( AD_Correct_Vref.out_Val > AD_Correct_Vref.down_Limit ))
        {
            AD_Correct_Vref.Flag.bit.ADRef_Correct_Ok = E_TRUE;
        }    
    } 
}

/*************************************************
Description: AD_CHG_IBat_Correct
Input      : 
Return     : 
Others     : ������У׼
*************************************************/
void AD_CHG_IBat_Correct(void)
{  
    ADC0->ADANSA = (1<<1); //AN001  PA01 
    PORT->PMCA |= (1 <<1);     /* Set ANI001(PA01) pin */
    
    //ADƫ��ֵУ��
    if ( E_FALSE == AD_Correct_CHG_IBat.Flag.bit.ADRef_Correct_Ok )
    {
        for(uint16_t i=0;i<1024;i++)
        {
            ADC0->ADCSR = 0x8000; //ADCSR Bit15 ����ת��
            while(ADC0->ADCSR&0x8000){};
            AD_temp= ADC0->ADDR1;
            AD_Correct_CHG_IBat.sum  += AD_temp; //������  
        }
        AD_Correct_CHG_IBat.out_Val = AD_Correct_CHG_IBat.sum >> 10;
        AD_Correct_CHG_IBat.sum     = 0;  
        
        if (( AD_Correct_CHG_IBat.out_Val < AD_Correct_CHG_IBat.up_Limit   ) && \
            ( AD_Correct_CHG_IBat.out_Val > AD_Correct_CHG_IBat.down_Limit ))
        {
            AD_Correct_CHG_IBat.Flag.bit.ADRef_Correct_Ok = E_TRUE;
        }	                       
    } 
}


/*************************************************
Description: AD_DISC_IBat_Correct
Input      : 
Return     : 
Others     : �ŵ�ʱ��ص���У׼
*************************************************/
void AD_DISC_IBat_Correct(void)
{    
    ADC2->ADANSA = (0x01<<4);    //AN204 PA10
    PORT->PMCA |= (1 << 10);     /* Set ANI203(PA09) pin */
        
    //ADƫ��ֵУ��
    if ( E_FALSE == AD_Correct_DISC_IBat.Flag.bit.ADRef_Correct_Ok )
    {
        for(uint16_t i=0;i<1024;i++)
        {
            ADC2->ADCSR = 0x8000; //ADCSR Bit15 ����ת��
            while(ADC2->ADCSR&0x8000){};
            AD_Correct_DISC_IBat.sum += ADC2->ADDR4; //�ŵ����  
        }
        AD_Correct_DISC_IBat.out_Val   = AD_Correct_DISC_IBat.sum >> 10; 
        AD_Correct_DISC_IBat.sum     = 0;        

        if (( AD_Correct_DISC_IBat.out_Val < AD_Correct_DISC_IBat.up_Limit   ) && \
            ( AD_Correct_DISC_IBat.out_Val > AD_Correct_DISC_IBat.down_Limit ))
        {
            AD_Correct_DISC_IBat.Flag.bit.ADRef_Correct_Ok = E_TRUE;
        }	                       
    }
 
}


/*************************************************
Description: AD_CorrectInit
Input      : 
Return     : 
Others     : ����У׼
*************************************************/
void AD_CorrectInit(void) 
{ 
    CGC->PERA |= CGC_PERA_ADC2EN_Msk + CGC_PERA_ADC0EN_Msk; //��Χ����Ĵ��� PERA
    ADC0->ADANSA   = 0;//A��ͨ����(AN000 �� AN007)��ѡ������A/Dת����ģ��ͨ��
    ADC0->ADANSB   = 0;
    ADC0->ADANSC   = 0;
    ADC0->ADCLKDIV  = 0x01u;  //ADCLKΪϵͳʱ�ӵ�2��Ƶ
    ADC0->ADCER = (1 << 5);//�����Զ������

    ADC2->ADANSA = 0;
    ADC2->ADANSB = 0;
    ADC2->ADANSC = 0;
    ADC2->ADCLKDIV = 0x01u;
    ADC2->ADCER = (1 << 5);

    //User_DelayTime_ms(200);

    AD_Vref_Correct();//��׼��ѹ2.5VУ׼
    
    AD_DISC_IBat_Correct();//�ŵ����У׼

    AD_CHG_IBat_Correct();//������У׼
}

/*************************************************
Description: COM_SampleAD_Deal
Input      : 
Return     : 
Others     : AD�����������뻷·���ƵĲ��������ж϶�ȡ��
*************************************************/
void COM_SampleAD_Deal(void)
{
    //
    ADSample_Info.vBat_AD       =  ADC0->ADDR2;  //��ص�ѹ����
    ADSample_Info.vBat_AD_FIR   = ( ADSample_Info.vBat_AD_FIR * 596  + ADSample_Info.vBat_AD * 3500 )>> 12;	
    CHG_Info.vBat_AD            = ADSample_Info.vBat_AD_FIR;
    
    //��������
    if(DC_Ctrl_Info.mode == DC_CHARGE)//���ģʽ
    {       
        ADSample_Info.iBat_CHG_AD   = ADC0->ADDR1;  // ����������    
        ADSample_Info.iBat_CHG_AD_FIR = ADSample_Info.iBat_CHG_AD - AD_Correct_CHG_IBat.out_Val;	

        CHG_Info.iBat_CHG_AD        = ADSample_Info.iBat_CHG_AD_FIR * COM_IBAT_CHG_BASE * COM_IBAT_CHG_SCAL>>12;//���Ϊ:��ʵ������ * COM_IBAT_CHG_SCAL         
    }
    else//�ŵ�ģʽ   
    {             
        ADSample_Info.iBat_DISC_AD= ADC2->ADDR4 ; //�ŵ����
        ADSample_Info.iBat_DISC_AD_FIR = ADSample_Info.iBat_DISC_AD - AD_Correct_Vref.out_Val;//
   
        ADSample_Info.vBusFB_AD     = ADC2->ADDR2;//ĸ�ߵ�ѹ���Ʒ�������    
        #if 0
            ADSample_Info.iBat_CHG_AD   = ADC0->ADDR1;  // ����������    
            ADSample_Info.iBat_CHG_AD_FIR = ADSample_Info.iBat_CHG_AD - AD_Correct_CHG_IBat.out_Val;	
        #endif  
    }     
}

/*************************************************
Description: COM_Vref_Sample
Input      : 
Return     : 
Others     : ��׼��ѹ2.5V����
*************************************************/
void COM_Vref_Sample(void)
{
}


/*************************************************
Description: COM_TempNTC_Sample
Input      : 
Return     : 
Others     : NTC�¶Ȳ���
*************************************************/
void COM_TempNTC_Sample(void)
{
}


/*************************************************
Description: COM_AuxPowerSample
Input      : 
Return     : 
Others     : ������Դ��ѹ����
*************************************************/
void COM_AuxPowerSample(void)
{	

}


/*************************************************
Description: COM_VBat_Sample
Input      : 
Return     : 
Others     : ��ص�ѹ����
*************************************************/
void COM_VBat_Sample(void)
{    

}


/*************************************************
Description: CHG_iBat_Sample
Input      : 
Return     : 
Others     : ���ʱ��ص�������
*************************************************/
void CHG_IBat_Sample(void)
{
}


/*************************************************
Description: DISC_iBat_Sample
Input      : 
Return     : 
Others     : �ŵ�ʱ��ص�������
*************************************************/
void DISC_IBat_Sample(void)
{    
}


/*************************************************
Description: DISC_VBusFB_Sample
Input      : 
Return     : 
Others     : �ŵ�ʱĸ�ߵ�ѹ��������ֵ����
*************************************************/
void DISC_VBusFB_Sample(void)
{
}


