/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc.h
* @brief   This file implements device driver for ADC module.
* @version 1.0.0  
* @date    2022/12/24
***********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H
#include "stdint.h"
#include "BAT32G439.h"
#include "userdefine.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    A/D control register (ADCSR) 
*/
#define ADC_ADCSR_ADCS_EN                  (0x8000U)
#define ADC_ADCSR_ADCS_DIS                 (0x0000U)
#define ADC_ADCSR_ADIE_EN                  (0x1000U)
#define ADC_ADCSR_ADIE_DIS                 (0x0000U)
#define ADC_ADCSR_TRGE_EN                  (0x0200U)
#define ADC_ADCSR_TRGE_DIS                 (0x0000U)
#define ADC_ADCSR_EXTRG_EN                 (0x0100U)
#define ADC_ADCSR_EXTRG_DIS                (0x0000U)
#define ADC_ADCSR_DBLE_EN                  (0x0080U)
#define ADC_ADCSR_DBLE_DIS                 (0x0000U)
#define ADC_ADCSR_GBADIE_EN                (0x0040U)
#define ADC_ADCSR_GBADIE_DIS               (0x0000U)
/*
    A/D control expand register (ADCER) 
*/
#define ADC_ADCER_ADRFMT_LEFT              (0x8000U)
#define ADC_ADCER_ADRFMT_RIGHT             (0x0000U)
#define ADC_ADCER_DIAGM_EN                 (0x0800U)
#define ADC_ADCER_DIAGM_DIS                (0x0000U)
#define ADC_ADCER_DIAGLD_FIX               (0x0400U)
#define ADC_ADCER_DIAGLD_ALT               (0x0000U)
#define ADC_ADCER_DIAGVAL_GND              (0x0100U)
#define ADC_ADCER_DIAGVAL_HALFVREF         (0x0200U)
#define ADC_ADCER_DIAGVAL_VREF             (0x0300U)
#define ADC_ADCER_ACE_CLREN                (0x0040U)
#define ADC_ADCER_ACE_CLRDIS               (0x0000U)

#define ADC_ADSTRGR_TRSB_Msk               (0x003FU)
#define ADC_ADSTRGR_TRSB_Pos               (0x00U)
#define ADC_ADSTRGR_TRSA_Msk               (0x3F00U)
#define ADC_ADSTRGR_TRSA_Pos               (0x08U)

#define ADC_ADGCTRGR_GRCE_EN               (0x80U)
#define ADC_ADGCTRGR_GRCE_DIS              (0x00U)
#define ADC_ADGCTRGR_GCADIE_EN             (0x40U)
#define ADC_ADGCTRGR_GCADIE_DIS            (0x00U)

#define ADC_DEFAULT_SAMPLING_TIME          (0x0DU)

#define ADC_ADCLKDIV_FCLK_DIV1             (0x0000U)
#define ADC_ADCLKDIV_FCLK_DIV2             (0x0001U)
#define ADC_ADCLKDIV_FCLK_DIV4             (0x0002U)
#define ADC_ADCLKDIV_FCLK_DIV8             (0x0003U)


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef union
{
    uint16_t halfword;
    struct{
        uint16_t req_adc0:1;
        uint16_t req_adc0_b:1;
        uint16_t req_adc0_c:1;
        uint16_t b3:1;
        uint16_t req_adc1:1;
        uint16_t req_adc1_b:1;
        uint16_t req_adc1_c:1;
        uint16_t b7:1;
        uint16_t req_adc2:1;
        uint16_t req_adc2_b:1;
        uint16_t req_adc2_c:1;
        uint16_t b11:1;
        uint16_t b12:1;
        uint16_t b13:1;
        uint16_t b14:1;
        uint16_t b15:1;
    }bit;
} adc_refresh_flag_t;

typedef enum
{
    ADCx_CH0         = 0x0001U,             /* ANIx_0 */
    ADCx_CH1         = 0x0002U,             /* ANIx_1 */
    ADCx_CH2         = 0x0004U,             /* ANIx_2 */
    ADCx_CH3         = 0x0008U,             /* ANIx_3 */
    ADCx_CH4         = 0x0010U,             /* ANIx_4 */
    ADCx_CH5         = 0x0020U,             /* ANIx_5 */
    ADCx_CH6         = 0x0040U,             /* ANIx_6 */
    ADCx_CH7         = 0x0080U,             /* ANIx_7 */
    ADCx_CH8         = 0x0100U,             /* ANIx_8 */
    ADCx_CH9         = 0x0200U,             /* ANIx_9 */
    ADCx_CH10        = 0x0400U,             /* ANIx_10 */
    ADCx_CH11        = 0x0800U,             /* ANIx_11 */
    ADCx_CH12        = 0x1000U,             /* ANIx_12 */
    ADCx_CH13        = 0x2000U,             /* ANIx_13 */
    ADCx_CH14        = 0x4000U,             /* ANIx_14 */
    ADCx_CH15        = 0x8000U,             /* ANIx_15 */
} adc_channel_t;

typedef enum
{
    AD_GROUP_A,
    AD_GROUP_B,
    AD_GROUP_C,
} adc_group_t;

typedef enum
{
    AD_SINGLE_SCAN_MODE    = 0x0000,    // ADANSA single scan
    AD_GROUP_SCAN_MODE     = 0x2000,    // Group A,B,C
    AD_CONTINUAL_SCAN_MODE = 0x4000,    // Continual scan specify by ADANSA
} adc_mode_t;

// TRSA[5:0], TRSB[5:0], TRSC[5:0]
typedef enum
{
    GP_NOUSE        =0x3F,              // No trigger source
    TRGA0N          =0x01,              // ELSR04
    TRGA1N          =0x02,              // ELSR05
    TRGA2N          =0x03,              // ELSR06
    TRGA3N          =0x04,              // ELSR07
    TRGA4N          =0x05,              // ELSR08
    TRGA5N          =0x06,              // ELSR09
    TRGA6N          =0x07,              // ELSR10
    TRGA7N          =0x08,              // ELSR11
    TRGA8N          =0x09,              // ELSR12
    TRGA25N         =0x19,              // TRGA0N+TRGA1N
    TRGA26N         =0x1A,              // TRGA2N+TRGA3N
    TRGA27N         =0x1B,              // TRGA4N+TRGA5N
    TRGA28N         =0x1C,              // TRGA6N+TRGA7N
} adc_syn_trigger_source_t;

typedef enum
{
    ACC_AVR_NORMAL  =0x00,              // Normal transfer result 
    ADC_ACC_2       =0x01,              // Output the accumulation of 2 result 
    ADC_ACC_3       =0x02,              // Output the accumulation of 2 result 
    ADC_ACC_4       =0x03,              // Output the accumulation of 4 result 
    ADC_ACC_16      =0x05,              // Output the accumulation of 16 result 
    ADC_AVR_2       =0x81,              // Output the average of 2 result 
    ADC_AVR_4       =0x83,              // Output the average of 4 result 
} adc_add_avr_t;

typedef enum
{
    CLOCK_DIV1=0,    // fCLK/1
    CLOCK_DIV2=1,    // fCLK/2
    CLOCK_DIV4=2,    // fCLK/4
    CLOCK_DIV8=3,    // fCLK/8
} adc_clock_t;


//typedef enum
//{
//    ADTES_NORMAL = 0U,      /* normal */
//    ADTES_ZERO_CODE = 1U,   /* zero code test */
//    ADTES_HALF_CODE = 3U,   /* half code test */
//    ADTES_FULL_CODE = 5U,   /* full code test */
//    ADTES_FREE_CODE = 6U    /* free code test */
//} adc_tes_t;

 /***********************************************************************************************************************
 Global variables
 ***********************************************************************************************************************/
// Adc data refresh flag
extern adc_refresh_flag_t g_adc_refresh_flag;
// Adc data buffer
extern uint16_t adc0_buf[8];        // ADC0 data buffer
extern uint16_t adc0_b_buf[8];
extern uint16_t adc0_c_buf[8];
extern uint16_t adc1_buf[8];
extern uint16_t adc1_b_buf[8];
extern uint16_t adc1_c_buf[8];
extern uint16_t adc2_buf[16];
extern uint16_t adc2_b_buf[16];
extern uint16_t adc2_c_buf[16];


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
MD_STATUS adc_initial(ADC_Type * ADCx, uint16_t ch);
void adc_software_start(ADC_Type * ADCx);
void adc_software_stop(ADC_Type * ADCx);
MD_STATUS adc_close(ADC_Type * ADCx);
MD_STATUS adc_sample_time_setting(ADC_Type * ADCx, uint16_t ch, uint8_t sample_time);
void adc_clock_setting(ADC_Type * ADCx, adc_clock_t div);

void adc_gp_scan_ch_setting(ADC_Type * ADCx, adc_group_t group, uint16_t ch);
void adc_syn_trigger_setting(ADC_Type * ADCx, adc_group_t group, adc_syn_trigger_source_t trigger_type);
MD_STATUS adc_asyn_trigger_setting(ADC_Type * ADCx);

void adc_operation_mode(ADC_Type * ADCx, adc_mode_t operation_mode);

int16_t adc_get_tempSensor(int16_t dat);
int16_t adc_get_refVoltageSensor(int16_t dat);

double adc_internal_refvol(void);
double adc_temperature(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
