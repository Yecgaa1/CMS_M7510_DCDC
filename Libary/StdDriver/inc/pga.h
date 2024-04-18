/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    pga.h
* @brief   This file implements device driver for PGA module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef PGA_H
#define PGA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    PGA control register (ADPGACR) 
*/
/* PGA to ADC enable (PGASW) */
#define _00_PGA2ADC_DISABLE                           (0x00U) /* PGAOUT to ADC input disabled */
#define _02_PGA2ADC_ENABLE                            (0x02U) /* PGAOUT to ADC input enabled */
/* PGA operation selection (PGAEN) */
#define _00_PGA_STOP                                  (0x00U) /* PGA operation stopped */
#define _04_PGA_START                                 (0x04U) /* PGA operation enabled */
/* differential input mode (PGAMODE)*/
#define _00_PGA_DIFF_FULL                             (0x00U) /* Full differential input mode*/
#define _08_PGA_DIFF_PSEUDO                           (0x08U) /* Pseudo differential input mode */

/*
    PGA control register (ADPGADCR) 
*/
/* GND selection of feedback resistance of the programmable gain amplifier (PGAGNDSEL) */
#define _00_PGA_VSS_SELECTED                          (0x00U) /* selects VSS */
#define _08_PGA_PGAGND_SELECTED                       (0x08U) /* selects PGAGND */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    PGA00 = 0U,  // PGA00
    PGA10 = 1U,  // PGA10
    PGA11 = 2U,  // PGA11
    PGA12 = 3U   // PGA12
} pga_channel_t;

typedef enum 
{
    PGA_GAIN_2P000   = 0x0U,  // pseudo differential gain
    PGA_GAIN_2P500   = 0x1U,  // pseudo differential gain
    PGA_GAIN_2P667   = 0x2U,  // pseudo differential gain
    PGA_GAIN_2P857   = 0x3U,  // pseudo differential gain
    PGA_GAIN_3P077   = 0x4U,  // pseudo differential gain
    PGA_GAIN_3P333   = 0x5U,  // pseudo differential gain
    PGA_GAIN_3P636   = 0x6U,  // pseudo differential gain
    PGA_GAIN_4P000   = 0x7U,  // pseudo differential gain
    PGA_GAIN_4P444   = 0x8U,  // pseudo differential gain
    PGA_GAIN_5P000   = 0x9U,  // pseudo differential gain
    PGA_GAIN_5P714   = 0xAU,  // pseudo differential gain
    PGA_GAIN_6P667   = 0xBU,  // pseudo differential gain
    PGA_GAIN_8P000   = 0xCU,  // pseudo differential gain
    PGA_GAIN_10P000  = 0xDU,  // pseudo differential gain
    PGA_GAIN_16P000  = 0xEU,  // pseudo differential gain
    PGA_GAIN_1P000   = 0xFU,  // pseudo differential gain
    PGA_GAIN_X5      = 0x0U,  // full differential gain
    PGA_GAIN_X8      = 0x1U,  // full differential gain
    PGA_GAIN_X10     = 0x2U,  // full differential gain
    PGA_GAIN_X16     = 0x3U   // full differential gain
} pga_gain_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void PGA_Init(pga_channel_t ch, pga_gain_t gain);
void PGA_DeInit(pga_channel_t ch);
void PGA_SetGain(pga_channel_t ch, pga_gain_t gain);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

