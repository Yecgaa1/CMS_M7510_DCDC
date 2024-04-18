/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc.c
* @brief   This file implements device driver for ADC module.
* @version 1.0.0  
* @date    2022/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions 
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "userdefine.h"
#include "adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static void adc_systrg_exttrg_enable(ADC_Type * ADCx);
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: ADC_Init
* @brief  This function initializes the AD converter.
* @param  None
* @return None
***********************************************************************************************************************/
MD_STATUS adc_initial(ADC_Type * ADCx, uint16_t ch)
{
    MD_STATUS status;
    uint8_t i;

    if(ADCx == ADC0){
        NVIC_DisableIRQ(ADC0_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC0_GBADIREQ_N_IRQn);          /* disable interrupt */
        NVIC_DisableIRQ(ADC0_GCADIREQ_N_IRQn);          /* disable interrupt */
        CGC->PERA |= CGC_PERA_ADC0EN_Msk;
        ADC0_PORT_SETTING();
    }
    else if(ADCx == ADC1){
        NVIC_DisableIRQ(ADC1_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC1_GBADIREQ_N_IRQn);          /* disable interrupt */
        NVIC_DisableIRQ(ADC1_GCADIREQ_N_IRQn);          /* disable interrupt */
        CGC->PERA |= CGC_PERA_ADC1EN_Msk;
        ADC1_PORT_SETTING();
    }
    else if(ADCx == ADC2){
        NVIC_DisableIRQ(ADC2_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC2_GBADIREQ_N_IRQn);          /* disable interrupt */
        NVIC_DisableIRQ(ADC2_GCADIREQ_N_IRQn);          /* disable interrupt */
        CGC->PERA |= CGC_PERA_ADC2EN_Msk;
        ADC2_PORT_SETTING();
    }
    else{
        return status = MD_ERROR;
    }

    ADCx->ADCLKDIV = ADC_ADCLKDIV_FCLK_DIV1;            /* Fadc = Fclk/1 */
    //adc_clock_setting(ADCx, CLOCK_DIV1);

    ADCx->ADCSR = ADC_ADCSR_ADCS_DIS|AD_SINGLE_SCAN_MODE|ADC_ADCSR_ADIE_EN|ADC_ADCSR_TRGE_DIS
                 |ADC_ADCSR_EXTRG_DIS|ADC_ADCSR_DBLE_DIS|ADC_ADCSR_GBADIE_DIS;
    for(i=0;i<16;i++){
        if((ch>>i)&0x01){
            *(&ADCx->ADSSTR0+i) = 27;//ADC_DEFAULT_SAMPLING_TIME;                 // ADCx CHx set to default sample time
        }
    }
    ADCx->ADANSA = ch;
    ADCx->ADCER = ADC_ADCER_ADRFMT_RIGHT|ADC_ADCER_DIAGM_DIS|ADC_ADCER_ACE_CLREN|0x80;
    ADCx->ADSTRGR = (GP_NOUSE<<ADC_ADSTRGR_TRSA_Pos)+(GP_NOUSE<<ADC_ADSTRGR_TRSB_Pos);

    // Enable average mode with accumulate 4 times
    #if 0
    ADCx->ADADS = ch;
    ADCx->ADADC = 0x83;
    #endif

    if(ADCx == ADC0){
        NVIC_EnableIRQ(ADC0_ADIREQ_N_IRQn);             /* disable INTAD interrupt */
    }
    else if(ADCx == ADC1){
        NVIC_EnableIRQ(ADC1_ADIREQ_N_IRQn);             /* disable INTAD interrupt */
    }
    else if(ADCx == ADC2){
        NVIC_EnableIRQ(ADC2_ADIREQ_N_IRQn);             /* disable INTAD interrupt */
    }
    //ADCx->ADCSR |= ADC_ADCSR_ADCS_EN;
    status = MD_OK; 
    return (status);
}
static void adc_systrg_exttrg_enable(ADC_Type * ADCx){
    ADCx->ADCSR |= ADC_ADCSR_TRGE_EN;
}
/***********************************************************************************************************************
* Function Name: adc_operation_mode
* @brief  This function change operation mode.
* @param  ch - specify the conversion channel
* @return None
***********************************************************************************************************************/
void adc_operation_mode(ADC_Type * ADCx, adc_mode_t operation_mode)
{
    ADCx->ADCSR &= ~0x6000;
    ADCx->ADCSR |= operation_mode;
    if (operation_mode==AD_GROUP_SCAN_MODE){
        adc_systrg_exttrg_enable(ADCx);
    }
}
/***********************************************************************************************************************
* Function Name: adc_grp_ch_enable_setting
* @brief  This function change operation mode.
* @param  ADCx - specify the adc module, adc_gpx - group, ch - specify the conversion channel
* @return None
***********************************************************************************************************************/
void adc_gp_scan_ch_setting(ADC_Type * ADCx,adc_group_t group, uint16_t ch)
{
    switch (group){
        case AD_GROUP_A:
            ADCx->ADANSA = ch;
            break;
        case AD_GROUP_B:
            ADCx->ADANSB = ch;
            break;
        case AD_GROUP_C:
            ADCx->ADANSC = ch;
            break;
    }
}
/***********************************************************************************************************************
* Function Name: adc_syn_trigger_setting
* @brief  This function change operation mode.
* @param  ADCx - specify the adc module, adc_gpx - group, trigger_type - specify the trigger type of group
* @return None
***********************************************************************************************************************/
void adc_syn_trigger_setting(ADC_Type * ADCx, adc_group_t group, adc_syn_trigger_source_t trigger_type)
{
    switch (group){
        case AD_GROUP_A:
            ADCx->ADSTRGR |= ADC_ADSTRGR_TRSA_Msk;
            ADCx->ADSTRGR &= (uint16_t)(trigger_type<<ADC_ADSTRGR_TRSA_Pos)|(~ADC_ADSTRGR_TRSA_Msk);
            ADCx->ADCSR |= ADC_ADCSR_ADIE_EN;
            if(ADCx == ADC0){
                NVIC_EnableIRQ(ADC0_ADIREQ_N_IRQn);             /* enable interrupt */
            }
            else if(ADCx == ADC1){
                NVIC_EnableIRQ(ADC1_ADIREQ_N_IRQn);             /* ensable interrupt */
            }
            else if(ADCx == ADC2){
                NVIC_EnableIRQ(ADC2_ADIREQ_N_IRQn);             /* ensable interrupt */
            }
            break;
        case AD_GROUP_B:
            ADCx->ADSTRGR |= ADC_ADSTRGR_TRSB_Msk;
            ADCx->ADSTRGR &=  (uint16_t)(trigger_type<<ADC_ADSTRGR_TRSB_Pos)|(~ADC_ADSTRGR_TRSB_Msk);
            ADCx->ADCSR |= ADC_ADCSR_GBADIE_EN;
            if(ADCx == ADC0){
                NVIC_EnableIRQ(ADC0_GBADIREQ_N_IRQn);
            }
            else if(ADCx == ADC1){
                NVIC_EnableIRQ(ADC1_GBADIREQ_N_IRQn);
            }
            else if(ADCx == ADC2){
                NVIC_EnableIRQ(ADC2_GBADIREQ_N_IRQn);
            }
            break;
        case AD_GROUP_C:
            ADCx->ADGCTRGR = ADC_ADGCTRGR_GRCE_EN|ADC_ADGCTRGR_GCADIE_EN|trigger_type;
            if(ADCx == ADC0){
                NVIC_EnableIRQ(ADC0_GCADIREQ_N_IRQn);
            }
            else if(ADCx == ADC1){
                NVIC_EnableIRQ(ADC1_GCADIREQ_N_IRQn);
            }
            else if(ADCx == ADC2){
                NVIC_EnableIRQ(ADC2_GCADIREQ_N_IRQn);
            }
            break;
    }
}
/***********************************************************************************************************************
* Function Name: adc_software_start
* @brief  This function starts the AD converter.
* @param  ADCx - specify the adc module
* @return None
***********************************************************************************************************************/
void adc_clock_setting(ADC_Type * ADCx, adc_clock_t div)
{
    ADCx->ADCLKDIV = div;
}
/***********************************************************************************************************************
* Function Name: adc_software_start
* @brief  This function starts the AD converter.
* @param  ADCx - specify the adc module
* @return None
***********************************************************************************************************************/
void adc_software_start(ADC_Type * ADCx)
{
    ADCx->ADCSR &= ~ADC_ADCSR_TRGE_EN;
    ADCx->ADCSR |= ADC_ADCSR_ADCS_EN;
}
/***********************************************************************************************************************
* Function Name: adc_software_stop
* @brief  This function stops the AD converter.
* @param  ADCx - specify the adc module
* @return None
***********************************************************************************************************************/
void adc_software_stop(ADC_Type * ADCx)
{
    ADCx->ADCSR &= ~ADC_ADCSR_ADCS_EN;
}
/***********************************************************************************************************************
* Function Name: adc_close
* @brief  This function stops the AD converter.
* @param  ADCx - specify the adc module
* @return None
***********************************************************************************************************************/
MD_STATUS adc_close(ADC_Type * ADCx)
{
    MD_STATUS status;
    ADCx->ADCSR &= ~0x8000;

    if(ADCx == ADC0){
        CGC->PERA &= ~CGC_PERA_ADC0EN_Msk;              /* close ad0 clock */
        NVIC_DisableIRQ(ADC0_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC0_GBADIREQ_N_IRQn);
        NVIC_DisableIRQ(ADC0_GCADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC0_ADIREQ_N_IRQn);       /* clear interrupt require */
        NVIC_ClearPendingIRQ(ADC0_GBADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC0_GCADIREQ_N_IRQn);
    }
    else if(ADCx == ADC1){
        CGC->PERA &= ~CGC_PERA_ADC1EN_Msk;              /* close ad1 clock */
        NVIC_DisableIRQ(ADC1_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC1_GBADIREQ_N_IRQn);
        NVIC_DisableIRQ(ADC1_GCADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC1_ADIREQ_N_IRQn);       /* clear interrupt require */
        NVIC_ClearPendingIRQ(ADC1_GBADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC1_GCADIREQ_N_IRQn);
    }
    else if(ADCx == ADC2){
        CGC->PERA &= ~CGC_PERA_ADC2EN_Msk;              /* close ad2 clock */
        NVIC_DisableIRQ(ADC2_ADIREQ_N_IRQn);            /* disable interrupt */
        NVIC_DisableIRQ(ADC2_GBADIREQ_N_IRQn);
        NVIC_DisableIRQ(ADC2_GCADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC2_ADIREQ_N_IRQn);       /* clear interrupt require */
        NVIC_ClearPendingIRQ(ADC2_GBADIREQ_N_IRQn);
        NVIC_ClearPendingIRQ(ADC2_GCADIREQ_N_IRQn);
    }
    else{
        return status = MD_ERROR;
    }
    status = MD_OK; 
    return (status);
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

