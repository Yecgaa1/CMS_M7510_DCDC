/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc_user.c
* @brief   This file implements device driver for ADC module.
* @version 1.0.0 
* @date    2022/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
extern void IRQ47_Handler(void) __attribute__((alias("adc0_interrupt")));
extern void IRQ48_Handler(void) __attribute__((alias("adc1_interrupt")));
extern void IRQ49_Handler(void) __attribute__((alias("adc2_interrupt")));
extern void IRQ50_Handler(void) __attribute__((alias("adc0_gpb_interrupt")));
extern void IRQ51_Handler(void) __attribute__((alias("adc1_gpb_interrupt")));
extern void IRQ52_Handler(void) __attribute__((alias("adc2_gpb_interrupt")));
extern void IRQ53_Handler(void) __attribute__((alias("adc0_gpc_interrupt")));
extern void IRQ54_Handler(void) __attribute__((alias("adc1_gpc_interrupt")));
extern void IRQ55_Handler(void) __attribute__((alias("adc2_gpc_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static double voltage=5.0;
static void adcx_read(ADC_Type * ADCx, uint16_t * pBuf, uint16_t ch);

// Adc data refresh flag
adc_refresh_flag_t g_adc_refresh_flag;
// Adc data buffer
uint16_t adc0_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc0_b_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc0_c_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc1_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc1_b_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc1_c_buf[8]={0,0,0,0,0,0,0,0};
uint16_t adc2_buf[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t adc2_b_buf[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t adc2_c_buf[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: adcx_read
* @brief  ADC transfer result read
* @param  ADCx: ADC0,ADC1,ADC2; pBuf: data buffer for read out; ch: "1" of b15-b0 indicated CH15-CH0 read out
* @return None
***********************************************************************************************************************/
static void adcx_read(ADC_Type * ADCx, uint16_t * pBuf, uint16_t ch){
    for(uint8_t i=0;i<16;i++){
        if((ch>>i)&0x01){       // ch=0xFF: adc0/1->ch0-7; ch=0xFFFF: adc2->ch0-15
            *(pBuf+i) = *(&ADCx->ADDR0+i);
        }
    }
}
/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC0, adc0_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc0 = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC1, adc1_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc1 = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC2, adc2_buf,0xFFFF);
    g_adc_refresh_flag.bit.req_adc2 = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc0_gpb_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC0, adc0_b_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc0_b = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc1_gpb_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC1, adc1_b_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc1_b = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc2_gpb_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC2, adc2_b_buf,0xFFFF);
    g_adc_refresh_flag.bit.req_adc2_b = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc0_gpc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC0, adc0_c_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc0_c = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc1_gpc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC1, adc1_c_buf,0xFF);
    g_adc_refresh_flag.bit.req_adc1_c = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc2_gpc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adcx_read(ADC2, adc2_c_buf,0xFFFF);
    g_adc_refresh_flag.bit.req_adc2_c = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_get_temperature
* @brief  ADC Get temperature
* @param  dat - the adc conversion value of ADC_TEMPERSENSOR0 channel
* @return temperature
***********************************************************************************************************************/
#if 1
double adc_get_temperature(int16_t dat)
{
    double temp;    /* temperature value */

    temp = (double)(TSN->TSN25 - dat) * 60 / (TSN->TSN25 - TSN->TSN85) + 25; /* 12bit dat */

    return (temp);
}
#else
//int16_t adc_get_temperature(int16_t dat)
//{
//    int16_t temp;   /* temperature value */

//    temp = (int16_t)(TSN->TSN25 - dat) * 60 / (TSN->TSN25 - TSN->TSN85) + 25; /* 12bit dat */

//    return (temp);
//}
#endif

double adc_internal_refvol(void){
    uint16_t temp;
    double vol;
    CGC->PERA |= CGC_PERA_ADC2EN_Msk;
    ADC2 -> ADCSR = ADC_ADCSR_ADCS_DIS|AD_SINGLE_SCAN_MODE|ADC_ADCSR_ADIE_EN|ADC_ADCSR_TRGE_DIS
                 |ADC_ADCSR_EXTRG_DIS|ADC_ADCSR_DBLE_DIS|ADC_ADCSR_GBADIE_DIS;
    ADC2-> ADCLKDIV = ADC_ADCLKDIV_FCLK_DIV1;            /* Fadc = Fclk/1 */
    ADC2-> ADEXICR |= ADC2_ADEXICR_OCSA_Msk;//|ADC2_ADEXICR_OCSAD_Msk;
    //ADC2-> ADADC = 0x83;        // add 4 times
    //ADC2->ADANSA = ch;
    ADC2->ADCER = ADC_ADCER_ADRFMT_RIGHT|ADC_ADCER_DIAGM_DIS|ADC_ADCER_ACE_CLREN;

    //for(uint32_t i=0;i<10;i++)
    {
        ADC2->ADCSR = 0x8000;
        while(ADC2->ADCSR&0x8000){}
        temp = ADC2->ADOCDR;
        vol = temp*voltage/4096;
        //printf("BGR=\t%d\n",ADC2->ADOCDR);
        //printf("BGR=\t%d\tVoltage=\t%2.4f\n",temp,vol);
    }
    return vol;
}

double adc_temperature(void){
    uint16_t temp;
    CGC->PERA |= CGC_PERA_ADC2EN_Msk;
    ADC2 -> ADCSR = ADC_ADCSR_ADCS_DIS|AD_SINGLE_SCAN_MODE|ADC_ADCSR_ADIE_EN|ADC_ADCSR_TRGE_DIS
                 |ADC_ADCSR_EXTRG_DIS|ADC_ADCSR_DBLE_DIS|ADC_ADCSR_GBADIE_DIS;
    ADC2-> ADCLKDIV = ADC_ADCLKDIV_FCLK_DIV1;            /* Fadc = Fclk/1 */
    ADC2-> ADEXICR |= ADC2_ADEXICR_TSSA_Msk;//|ADC2_ADEXICR_TSSAD_Msk;
    //ADC2-> ADADC = 0x83;        // add 4 times
    //ADC2->ADANSA = ch;
    ADC2->ADCER = ADC_ADCER_ADRFMT_RIGHT|ADC_ADCER_DIAGM_DIS|ADC_ADCER_ACE_CLREN;
    //for(uint32_t i=0;i<10;i++)
    {
        ADC2->ADCSR = 0x8000;
        while(ADC2->ADCSR&0x8000){}
        temp = ADC2->ADTSDR;
        //printf("AdcValueTemp=\t%d\n",temp);
    }
    return adc_get_temperature(temp);
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
