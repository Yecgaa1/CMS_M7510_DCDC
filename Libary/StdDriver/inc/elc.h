/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    elc.h
* @brief   This file implements device driver for ELC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef ELC_H
#define ELC_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/*
    EVENTC control register (ELCR) 
*/
#define ELC_ELCR_ELCON_EN                  (0x8000U)

#define ELC_DESTINATION_COUNT              (33U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
  ELC_EVENT_INTP0_IRQn                 =   0,
  ELC_EVENT_INTP1_IRQn                 =   1,
  ELC_EVENT_INTP2_IRQn                 =   2,
  ELC_EVENT_INTP3_IRQn                 =   3,
  ELC_EVENT_INTP4_IRQn                 =   4,
  ELC_EVENT_INTP5_IRQn                 =   5,
  ELC_EVENT_INTP6_IRQn                 =   6,
  ELC_EVENT_INTP7_IRQn                 =   7,
  ELC_EVENT_ST0_IRQn                   =   8,
  ELC_EVENT_SR0_IRQn                   =   9,
  ELC_EVENT_ST1_IRQn                   =  10,
  ELC_EVENT_SR1_IRQn                   =  11,
  ELC_EVENT_ST2_IRQn                   =  12,
  ELC_EVENT_SR2_IRQn                   =  13,
  ELC_EVENT_ST3_IRQn                   =  14,
  ELC_EVENT_SR3_IRQn                   =  15,
  ELC_EVENT_IICA0_IRQn                 =  16,
  ELC_EVENT_IICA1_IRQn                 =  17,
  ELC_EVENT_SPI0_IRQn                  =  18,
  ELC_EVENT_SPI1_IRQn                  =  19,
  ELC_EVENT_TM00_IRQn                  =  20,
  ELC_EVENT_TM01_IRQn                  =  21,
  ELC_EVENT_TM02_IRQn                  =  22,
  ELC_EVENT_TM03_IRQn                  =  23,
  ELC_EVENT_TM04_IRQn                  =  24,
  ELC_EVENT_TM05_IRQn                  =  25,
  ELC_EVENT_TM06_IRQn                  =  26,
  ELC_EVENT_TM07_IRQn                  =  27,
  ELC_EVENT_TM10_IRQn                  =  28,
  ELC_EVENT_TM11_IRQn                  =  29,
  ELC_EVENT_TM12_IRQn                  =  30,
  ELC_EVENT_TM13_IRQn                  =  31,
  ELC_EVENT_TM14_IRQn                  =  32,
  ELC_EVENT_TM15_IRQn                  =  33,
  ELC_EVENT_TM16_IRQn                  =  34,
  ELC_EVENT_TM17_IRQn                  =  35,
  ELC_EVENT_ADC0_ADIREQ_N_IRQn         =  36,
  ELC_EVENT_ADC1_ADIREQ_N_IRQn         =  37,
  ELC_EVENT_ADC2_ADIREQ_N_IRQn         =  38,
  ELC_EVENT_RTC_IRQn                   =  39,
  ELC_EVENT_IT_IRQn                    =  40,
  ELC_EVENT_KR_IRQn                    =  41,
  ELC_EVENT_CMP0_IRQn                  =  42,
  ELC_EVENT_CMP1_IRQn                  =  43,
  ELC_EVENT_CMP2_IRQn                  =  44,
  ELC_EVENT_CMP3_IRQn                  =  45,
  ELC_EVENT_C0ERR_IRQn                 =  46,
  ELC_EVENT_C0REC_IRQn                 =  47,
  ELC_EVENT_C0WUP_IRQn                 =  48,
  ELC_EVENT_C0TRX_IRQn                 =  49,
  ELC_EVENT_LCDB_IRQn                  =  50,
  ELC_EVENT_QSPI_DMAREQ_IRQn           =  51,
  ELC_EVENT_FL_IRQn                    =  52,
  ELC_EVENT_OSDC_IRQn                  =  53,
  ELC_EVENT_PGI0_IRQn                  =  54,
  ELC_EVENT_PGI1_IRQn                  =  55,
  ELC_EVENT_PGI2_IRQn                  =  56,
  ELC_EVENT_PGI3_IRQn                  =  57,
  ELC_EVENT_GPT0_ELCCMPA0_IRQn         =  58,
  ELC_EVENT_GPT0_ELCCMPB0_IRQn         =  59,
  ELC_EVENT_GPT0_ELCCMPC0_IRQn         =  60,
  ELC_EVENT_GPT0_ELCCMPD0_IRQn         =  61,
  ELC_EVENT_GPT0_ELCCMPE0_IRQn         =  62,
  ELC_EVENT_GPT0_ELCCMPF0_IRQn         =  63,
  ELC_EVENT_GPT0_ELCOVF0_IRQn          =  64,
  ELC_EVENT_GPT0_ELCUDF0_IRQn          =  65,
  ELC_EVENT_GPT0_ELCCMPA1_IRQn         =  66,
  ELC_EVENT_GPT0_ELCCMPB1_IRQn         =  67,
  ELC_EVENT_GPT0_ELCCMPC1_IRQn         =  68,
  ELC_EVENT_GPT0_ELCCMPD1_IRQn         =  69,
  ELC_EVENT_GPT0_ELCCMPE1_IRQn         =  70,
  ELC_EVENT_GPT0_ELCCMPF1_IRQn         =  71,
  ELC_EVENT_GPT0_ELCOVF1_IRQn          =  72,
  ELC_EVENT_GPT0_ELCUDF1_IRQn          =  73,
  ELC_EVENT_GPT0_ELCCMPA2_IRQn         =  74,
  ELC_EVENT_GPT0_ELCCMPB2_IRQn         =  75,
  ELC_EVENT_GPT0_ELCCMPC2_IRQn         =  76,
  ELC_EVENT_GPT0_ELCCMPD2_IRQn         =  77,
  ELC_EVENT_GPT0_ELCCMPE2_IRQn         =  78,
  ELC_EVENT_GPT0_ELCCMPF2_IRQn         =  79,
  ELC_EVENT_GPT0_ELCOVF2_IRQn          =  80,
  ELC_EVENT_GPT0_ELCUDF2_IRQn          =  81,
  ELC_EVENT_GPT0_ELCCMPA3_IRQn         =  82,
  ELC_EVENT_GPT0_ELCCMPB3_IRQn         =  83,
  ELC_EVENT_GPT0_ELCCMPC3_IRQn         =  84,
  ELC_EVENT_GPT0_ELCCMPD3_IRQn         =  85,
  ELC_EVENT_GPT0_ELCCMPE3_IRQn         =  86,
  ELC_EVENT_GPT0_ELCCMPF3_IRQn         =  87,
  ELC_EVENT_GPT0_ELCOVF3_IRQn          =  88,
  ELC_EVENT_GPT0_ELCUDF3_IRQn          =  89,
  ELC_EVENT_GPT1_ELCCMPA0_IRQn         =  90,
  ELC_EVENT_GPT1_ELCCMPB0_IRQn         =  91,
  ELC_EVENT_GPT1_ELCCMPC0_IRQn         =  92,
  ELC_EVENT_GPT1_ELCCMPD0_IRQn         =  93,
  ELC_EVENT_GPT1_ELCCMPE0_IRQn         =  94,
  ELC_EVENT_GPT1_ELCCMPF0_IRQn         =  95,
  ELC_EVENT_GPT1_ELCOVF0_IRQn          =  96,
  ELC_EVENT_GPT1_ELCUDF0_IRQn          =  97,
  ELC_EVENT_GPT1_ELCCMPA1_IRQn         =  98,
  ELC_EVENT_GPT1_ELCCMPB1_IRQn         =  99,
  ELC_EVENT_GPT1_ELCCMPC1_IRQn         = 100,
  ELC_EVENT_GPT1_ELCCMPD1_IRQn         = 101,
  ELC_EVENT_GPT1_ELCCMPE1_IRQn         = 102,
  ELC_EVENT_GPT1_ELCCMPF1_IRQn         = 103,
  ELC_EVENT_GPT1_ELCOVF1_IRQn          = 104,
  ELC_EVENT_GPT1_ELCUDF1_IRQn          = 105,
  ELC_EVENT_GPT1_ELCCMPA2_IRQn         = 106,
  ELC_EVENT_GPT1_ELCCMPB2_IRQn         = 107,
  ELC_EVENT_GPT1_ELCCMPC2_IRQn         = 108,
  ELC_EVENT_GPT1_ELCCMPD2_IRQn         = 109,
  ELC_EVENT_GPT1_ELCCMPE2_IRQn         = 110,
  ELC_EVENT_GPT1_ELCCMPF2_IRQn         = 111,
  ELC_EVENT_GPT1_ELCOVF2_IRQn          = 112,
  ELC_EVENT_GPT1_ELCUDF2_IRQn          = 113,
  ELC_EVENT_GPT1_ELCCMPA3_IRQn         = 114,
  ELC_EVENT_GPT1_ELCCMPB3_IRQn         = 115,
  ELC_EVENT_GPT1_ELCCMPC3_IRQn         = 116,
  ELC_EVENT_GPT1_ELCCMPD3_IRQn         = 117,
  ELC_EVENT_GPT1_ELCCMPE3_IRQn         = 118,
  ELC_EVENT_GPT1_ELCCMPF3_IRQn         = 119,
  ELC_EVENT_GPT1_ELCOVF3_IRQn          = 120,
  ELC_EVENT_GPT1_ELCUDF3_IRQn          = 121,
  ELC_EVENT_GPT1_ELCCMPA4_IRQn         = 122,
  ELC_EVENT_GPT1_ELCCMPB4_IRQn         = 123,
  ELC_EVENT_GPT1_ELCCMPC4_IRQn         = 124,
  ELC_EVENT_GPT1_ELCCMPD4_IRQn         = 125,
  ELC_EVENT_GPT1_ELCCMPE4_IRQn         = 126,
  ELC_EVENT_GPT1_ELCCMPF4_IRQn         = 127,
  ELC_EVENT_GPT1_ELCOVF4_IRQn          = 128,
  ELC_EVENT_GPT1_ELCUDF4_IRQn          = 129,
  ELC_EVENT_GPT1_ELCCMPA5_IRQn         = 130,
  ELC_EVENT_GPT1_ELCCMPB5_IRQn         = 131,
  ELC_EVENT_GPT1_ELCCMPC5_IRQn         = 132,
  ELC_EVENT_GPT1_ELCCMPD5_IRQn         = 133,
  ELC_EVENT_GPT1_ELCCMPE5_IRQn         = 134,
  ELC_EVENT_GPT1_ELCCMPF5_IRQn         = 135,
  ELC_EVENT_GPT1_ELCOVF5_IRQn          = 136,
  ELC_EVENT_GPT1_ELCUDF5_IRQn          = 137,
  ELC_EVENT_GPT1_ELCCMPA6_IRQn         = 138,
  ELC_EVENT_GPT1_ELCCMPB6_IRQn         = 139,
  ELC_EVENT_GPT1_ELCCMPC6_IRQn         = 140,
  ELC_EVENT_GPT1_ELCCMPD6_IRQn         = 141,
  ELC_EVENT_GPT1_ELCCMPE6_IRQn         = 142,
  ELC_EVENT_GPT1_ELCCMPF6_IRQn         = 143,
  ELC_EVENT_GPT1_ELCOVF6_IRQn          = 144,
  ELC_EVENT_GPT1_ELCUDF6_IRQn          = 145,
  ELC_EVENT_GPT1_ELCCMPA7_IRQn         = 146,
  ELC_EVENT_GPT1_ELCCMPB7_IRQn         = 147,
  ELC_EVENT_GPT1_ELCCMPC7_IRQn         = 148,
  ELC_EVENT_GPT1_ELCCMPD7_IRQn         = 149,
  ELC_EVENT_GPT1_ELCCMPE7_IRQn         = 150,
  ELC_EVENT_GPT1_ELCCMPF7_IRQn         = 151,
  ELC_EVENT_GPT1_ELCOVF7_IRQn          = 152,
  ELC_EVENT_GPT1_ELCUDF7_IRQn          = 153,
  ELC_EVENT_GPT1_ELCEDGUVW_IRQn        = 154,
  ELC_EVENT_C1ERR_IRQn                 = 155,
  ELC_EVENT_C1REC_IRQn                 = 156,
  ELC_EVENT_C1WUP_IRQn                 = 157,
  ELC_EVENT_C1TRX_IRQn                 = 158,
  ELC_EVENT_IIR0WFIFOEMP_IRQn          = 159,
  ELC_EVENT_IIR0WFIFOFUL_IRQn          = 160,
  ELC_EVENT_IIR1WFIFOEMP_IRQn          = 161,
  ELC_EVENT_IIR1WFIFOFUL_IRQn          = 162,
  ELC_EVENT_LINK_OFF                   = 255
} elc_event_source_t;

typedef enum
{
  ELC_EVENT00_LINK_GPTEVENTA           =   0,           /* ELSR00 */
  ELC_EVENT01_LINK_GPTEVENTB           =   1,           /* ELSR01 */
  ELC_EVENT02_LINK_GPTEVENTC           =   2,           /* ELSR02 */
  ELC_EVENT03_LINK_GPTEVENTD           =   3,           /* ELSR03 */
  ELC_EVENT04_LINK_ADCEVENT0           =   4,           /* ELSR04 */
  ELC_EVENT05_LINK_ADCEVENT1           =   5,           /* ELSR05 */
  ELC_EVENT06_LINK_ADCEVENT2           =   6,           /* ELSR06 */
  ELC_EVENT07_LINK_ADCEVENT3           =   7,           /* ELSR07 */
  ELC_EVENT08_LINK_ADCEVENT4           =   8,           /* ELSR08 */
  ELC_EVENT09_LINK_ADCEVENT5           =   9,           /* ELSR09 */
  ELC_EVENT10_LINK_ADCEVENT6           =  10,           /* ELSR10 */
  ELC_EVENT11_LINK_ADCEVENT7           =  11,           /* ELSR11 */
  ELC_EVENT12_LINK_ADCEVENT8           =  12,           /* ELSR12 */
  ELC_EVENT13_LINK_TI00                =  13,           /* ELSR13 */
  ELC_EVENT14_LINK_TI10                =  14,           /* ELSR14 */
  ELC_EVENT15_LINK_DA0                 =  15,           /* ELSR15 */
  ELC_EVENT16_LINK_DA1                 =  16,           /* ELSR16 */
  ELC_EVENT17_LINK_DMA0                =  17,           /* ELSR17 */
  ELC_EVENT18_LINK_DMA1                =  18,           /* ELSR18 */
  ELC_EVENT19_LINK_DMA2                =  19,           /* ELSR19 */
  ELC_EVENT20_LINK_DMA3                =  20,           /* ELSR20 */
  ELC_EVENT21_LINK_DMA4                =  21,           /* ELSR21 */
  ELC_EVENT22_LINK_DMA5                =  22,           /* ELSR22 */
  ELC_EVENT23_LINK_DMA6                =  23,           /* ELSR23 */
  ELC_EVENT24_LINK_DMA7                =  24,           /* ELSR24 */
  ELC_EVENT25_LINK_DMA8                =  25,           /* ELSR25 */
  ELC_EVENT26_LINK_DMA9                =  26,           /* ELSR26 */
  ELC_EVENT27_LINK_DMA10               =  27,           /* ELSR27 */
  ELC_EVENT28_LINK_DMA11               =  28,           /* ELSR28 */
  ELC_EVENT29_LINK_DMA12               =  29,           /* ELSR29 */
  ELC_EVENT30_LINK_DMA13               =  30,           /* ELSR30 */
  ELC_EVENT31_LINK_DMA14               =  31,           /* ELSR31 */
  ELC_EVENT32_LINK_DMA15               =  32            /* ELSR32 */
} elc_event_link_destination_t;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void ELC_Start(elc_event_link_destination_t event_dst, elc_event_source_t event_src);
void ELC_Stop(elc_event_link_destination_t event_dst);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

