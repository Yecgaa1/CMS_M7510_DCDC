/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/*****************************************************************************/
/** \file app_adc.h
**
** History:
** 
*****************************************************************************/
#ifndef __APP_ADC_H__
#define __APP_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Include files */
/*****************************************************************************/

#include "BAT32G439.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
#define  ADC_TRS_TRGA0N         (1)      /* ESSR04  */
#define  ADC_TRS_TRGA1N         (2)      /* ESSR05  */
#define  ADC_TRS_TRGA2N         (3)      /* ESSR06  */
#define  ADC_TRS_TRGA3N         (4)      /* ESSR07  */
#define  ADC_TRS_TRGA4N         (5)      /* ESSR08  */
#define  ADC_TRS_TRGA5N         (6)      /* ESSR09  */
#define  ADC_TRS_TRGA6N         (7)      /* ESSR10  */
#define  ADC_TRS_TRGA7N         (8)      /* ESSR11  */
#define  ADC_TRS_TRGA8N         (9)      /* ESSR12  */
#define  ADC_TRS_TRGA25N        (25)     /* ESSR04 or ELSR05  */
#define  ADC_TRS_TRGA26N        (26)     /* ESSR06 or ELSR07  */
#define  ADC_TRS_TRGA27N        (27)     /* ESSR08 or ELSR09  */
#define  ADC_TRS_TRGA28N        (28)     /* ESSR10 or ELSR11  */


#define  ADCSR_DBLANS_Pos             (0UL)                     /*!< DBLANS (Bit 0)                                        */
#define  ADCSR_DBLANS_Msk             (0x1fUL)                  /*!< DBLANS (Bitfield-Mask: 0x1f)                          */
#define  ADCSR_GBADIE_Pos             (6UL)                     /*!< GBADIE (Bit 6)                                        */
#define  ADCSR_GBADIE_Msk             (0x40UL)                  /*!< GBADIE (Bitfield-Mask: 0x01)                          */
#define  ADCSR_DBLE_Pos               (7UL)                     /*!< DBLE (Bit 7)                                          */
#define  ADCSR_DBLE_Msk               (0x80UL)                  /*!< DBLE (Bitfield-Mask: 0x01)                            */
#define  ADCSR_EXTRG_Pos              (8UL)                     /*!< EXTRG (Bit 8)                                         */
#define  ADCSR_EXTRG_Msk              (0x100UL)                 /*!< EXTRG (Bitfield-Mask: 0x01)                           */
#define  ADCSR_TRGE_Pos               (9UL)                     /*!< TRGE (Bit 9)                                          */
#define  ADCSR_TRGE_Msk               (0x200UL)                 /*!< TRGE (Bitfield-Mask: 0x01)                            */
#define  ADCSR_ADIE_Pos               (12UL)                    /*!< ADIE (Bit 12)                                         */
#define  ADCSR_ADIE_Msk               (0x1000UL)                /*!< ADIE (Bitfield-Mask: 0x01)                            */
#define  ADCSR_ADCS_Pos               (13UL)                    /*!< ADCS (Bit 13)                                         */
#define  ADCSR_ADCS_Msk               (0x6000UL)                /*!< ADCS (Bitfield-Mask: 0x03)                            */
#define  ADCSR_ADST_Pos               (15UL)                    /*!< ADST (Bit 15)                                         */
#define  ADCSR_ADST_Msk               (0x8000UL)                /*!< ADST (Bitfield-Mask: 0x01                             */



#define  ADSTRGR_TRSB_Pos             (0UL)                     /*!< TRSB (Bit 0)                                          */
#define  ADSTRGR_TRSB_Msk             (0x3fUL)                  /*!< TRSB (Bitfield-Mask: 0x3f)                            */
#define  ADSTRGR_TRSA_Pos             (8UL)                     /*!< TRSA (Bit 8)                                          */
#define  ADSTRGR_TRSA_Msk             (0x3f00UL)                /*!< TRSA (Bitfield-Mask: 0x3f)                            */

#define ADC_CHANNEL_0                 (0UL)
#define ADC_CHANNEL_1                 (1UL)
#define ADC_CHANNEL_2                 (2UL)
#define ADC_CHANNEL_3                 (3UL)
#define ADC_CHANNEL_4                 (4UL)
#define ADC_CHANNEL_5                 (5UL)
#define ADC_CHANNEL_6                 (6UL)
#define ADC_CHANNEL_7                 (7UL)
#define ADC_CHANNEL_8                 (8UL)
#define ADC_CHANNEL_9                 (9UL)
#define ADC_CHANNEL_10                (10UL)
#define ADC_CHANNEL_11                (11UL)
#define ADC_CHANNEL_12                (12UL)
#define ADC_CHANNEL_13                (13UL)
#define ADC_CHANNEL_14                (14UL)
#define ADC_CHANNEL_15                (15UL)
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/
extern void ADC_Config(void);
/*****************************************************************************/
/* local inline function declarations */
/*****************************************************************************/
extern uint16_t Get_AD_Value(uint8_t unit,uint8_t ch);


#ifdef __cplusplus
}
#endif

#endif /* __APP_GPT_H__ */

