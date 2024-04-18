/***********************************************************************************************************************
* @file    gpt.h
* @brief   device driver header file for GPT module.
* @version 1.0.0
* @author	 Chenzongfu
* @date    2023/1/30
***********************************************************************************************************************/
/*
 * Copyright (c) 2023 Cmsemicon Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef __GPT_H__
#define __GPT_H__

//#include "core_cm0plus.h"                       /*!< ARM Cortex-M33 processor and core peripherals                             */
//#include "system_BAT32G439.h"                   /*!< BAT32G439 System                                                          */


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/** timer pin function */
typedef enum e_timer_pin_func
{
    OUTPUT_LOW_INIT_RETAIN_END_RETAIN_COMP = 0,       ///< Timer pin function select
    OUTPUT_LOW_INIT_RETAIN_END_LOW_COMP,
		OUTPUT_LOW_INIT_RETAIN_END_HIGH_COMP,
		OUTPUT_LOW_INIT_RETAIN_END_TOGGLE_COMP,
		OUTPUT_LOW_INIT_LOW_END_RETAIN_COMP,
    OUTPUT_LOW_INIT_LOW_END_LOW_COMP,
		OUTPUT_LOW_INIT_LOW_END_HIGH_COMP,
		OUTPUT_LOW_INIT_LOW_END_TOGGLE_COMP,
		OUTPUT_LOW_INIT_HIGH_END_RETAIN_COMP,
    OUTPUT_LOW_INIT_HIGH_END_LOW_COMP,
		OUTPUT_LOW_INIT_HIGH_END_HIGH_COMP,
		OUTPUT_LOW_INIT_HIGH_END_TOGGLE_COMP,
		OUTPUT_LOW_INIT_TOGGLE_END_RETAIN_COMP,
    OUTPUT_LOW_INIT_TOGGLE_END_LOW_COMP,
		OUTPUT_LOW_INIT_TOGGLE_END_HIGH_COMP,
		OUTPUT_LOW_INIT_TOGGLE_END_TOGGLE_COMP,
		
		OUTPUT_HIGH_INIT_RETAIN_END_RETAIN_COMP,          ///< Timer pin function select
    OUTPUT_HIGH_INIT_RETAIN_END_LOW_COMP,
		OUTPUT_HIGH_INIT_RETAIN_END_HIGH_COMP,
		OUTPUT_HIGH_INIT_RETAIN_END_TOGGLE_COMP,
		OUTPUT_HIGH_INIT_LOW_END_RETAIN_COMP,
    OUTPUT_HIGH_INIT_LOW_END_LOW_COMP,
		OUTPUT_HIGH_INIT_LOW_END_HIGH_COMP,
		OUTPUT_HIGH_INIT_LOW_END_TOGGLE_COMP,
		OUTPUT_HIGH_INIT_HIGH_END_RETAIN_COMP,
    OUTPUT_HIGH_INIT_HIGH_END_LOW_COMP,
		OUTPUT_HIGH_INIT_HIGH_END_HIGH_COMP,
		OUTPUT_HIGH_INIT_HIGH_END_TOGGLE_COMP,
		OUTPUT_HIGH_INIT_TOGGLE_END_RETAIN_COMP,
    OUTPUT_HIGH_INIT_TOGGLE_END_LOW_COMP,
		OUTPUT_HIGH_INIT_TOGGLE_END_HIGH_COMP,
		OUTPUT_HIGH_INIT_TOGGLE_END_TOGGLE_COMP,
		
} timer_pin_func_t;

/** timer function */
typedef enum e_timer_func
{
    FUNC_DISABLE = 0,          ///< Timer function disable
    FUNC_ENABLE = 1,           ///< Timer function enable
		
} timer_func_t;

/** Direction of timer count */
typedef enum e_timer_direction
{
    TIMER_DIRECTION_DOWN = 0,          ///< Timer count goes up
    TIMER_DIRECTION_UP   = 1           ///< Timer count goes down
} timer_direction_t;
/** Buffer of timer output */
typedef enum e_timer_buffer
{
    TIMER_NO_BUFFER = 0,          ///< Timer no buffer
    TIMER_SINGLE_BUFFER = 1,      ///< Timer single buffer
		TIMER_DOUBLE_BUFFER = 2				///< Timer double buffer
} timer_buffer_t;

/** PCLK divisors */
typedef enum e_timer_source_div
{
    TIMER_SOURCE_DIV_1    = 0,         ///< Timer clock source divided by 1
    TIMER_SOURCE_DIV_4    = 1,         ///< Timer clock source divided by 4
    TIMER_SOURCE_DIV_16   = 2,         ///< Timer clock source divided by 16
    TIMER_SOURCE_DIV_64   = 3,         ///< Timer clock source divided by 64
    TIMER_SOURCE_DIV_256  = 4,         ///< Timer clock source divided by 256
    TIMER_SOURCE_DIV_1024 = 5,        ///< Timer clock source divided by 1024
} timer_source_div_t;

/** Timer operational modes */
typedef enum e_timer_mode
{
    
    TIMER_MODE_PWM,                               ///< Timer generates saw-wave PWM output.
    TIMER_MODE_ONE_SHOT_PULSE,                    ///< Saw-wave one-shot pulse mode (fixed buffer operation).
    TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM  = 4U, ///< Timer generates symmetric triangle-wave PWM output.
    TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM = 5U, ///< Timer generates asymmetric triangle-wave PWM output.

    /**
     * Timer generates Asymmetric Triangle-wave PWM output. In PWM mode 3, the duty cycle does
     * not need to be updated at each tough/crest interrupt. Instead, the trough and crest duty cycle values can be
     * set once and only need to be updated when the application needs to change the duty cycle.
     */
    TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3 = 6U,
} timer_mode_t;

typedef struct {
	timer_source_div_t clockprescaler;//timer clock prescaler
	timer_mode_t timermode;//timer operational mode
	timer_direction_t direction;//timer count direction
	uint32_t period;//period
	uint32_t dutyA;//duty A
	uint32_t dutyB;//duty B
	uint32_t deadtime;//dead time
	timer_pin_func_t channelA_output_func;//pin A output function select
	timer_pin_func_t channelB_output_func;//pin B output function select
	timer_func_t channelA_output_enable;//pin A output enable
	timer_func_t channelB_output_enable;//pin B output enable
	timer_buffer_t period_buffer;//period buffer mode select
	timer_buffer_t channelA_buffer;//A buffer mode select
	timer_buffer_t channelB_buffer;//B buffer mode select
	
}GPT_InitTypeDef;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
//===================================================GPT Channel=======================================================

#define GPT_CHANNEL00 ((uint32_t)(1<<0))
#define GPT_CHANNEL01 ((uint32_t)(1<<1))
#define GPT_CHANNEL02 ((uint32_t)(1<<2))
#define GPT_CHANNEL03 ((uint32_t)(1<<3))
#define GPT_CHANNEL10 ((uint32_t)(1<<4))
#define GPT_CHANNEL11 ((uint32_t)(1<<5))
#define GPT_CHANNEL12 ((uint32_t)(1<<6))
#define GPT_CHANNEL13 ((uint32_t)(1<<7))
#define GPT_CHANNEL14 ((uint32_t)(1<<8))
#define GPT_CHANNEL15 ((uint32_t)(1<<9))
#define GPT_CHANNEL16 ((uint32_t)(1<<10))
#define GPT_CHANNEL17 ((uint32_t)(1<<11))

//================================================GTINTAD==========================================================

#define GPT_GTINTAD_INTAEN_BIT ((uint32_t)(1<<0))
#define GPT_GTINTAD_INTBEN_BIT ((uint32_t)(1<<1))
#define GPT_GTINTAD_INTCEN_BIT ((uint32_t)(1<<2))
#define GPT_GTINTAD_INTDEN_BIT ((uint32_t)(1<<3))
#define GPT_GTINTAD_INTEEN_BIT ((uint32_t)(1<<4))
#define GPT_GTINTAD_INTFEN_BIT ((uint32_t)(1<<5))
#define GPT_GTINTAD_INTPOEN_BIT ((uint32_t)(1<<6))
#define GPT_GTINTAD_INTPUEN_BIT ((uint32_t)(1<<7))

//===================================================GTST=======================================================

#define GPT_GTST_TCFA_BIT ((uint32_t)(1<<0))
#define GPT_GTST_TCFB_BIT ((uint32_t)(1<<1))
#define GPT_GTST_TCFC_BIT ((uint32_t)(1<<2))
#define GPT_GTST_TCFD_BIT ((uint32_t)(1<<3))
#define GPT_GTST_TCFE_BIT ((uint32_t)(1<<4))
#define GPT_GTST_TCFF_BIT ((uint32_t)(1<<5))
#define GPT_GTST_TCFPO_BIT ((uint32_t)(1<<6))
#define GPT_GTST_TCFPU_BIT ((uint32_t)(1<<7))

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
//=================================================================================================================
void GPT0_Open(GPT_Type* pGPT, GPT_InitTypeDef* pGPTInit);
void GPT0_Start(uint32_t chan);
void GPT0_Stop(uint32_t chan);
void GPT0_ClearCounter(uint32_t chan);

void GPT1_Open(GPT_Type* pGPT, GPT_InitTypeDef* pGPTInit);
void GPT1_Start(uint32_t chan);
void GPT1_Stop(uint32_t chan);
void GPT1_ClearCounter(uint32_t chan);

void GPT_EnableInt(GPT_Type* pGPT, uint32_t Intflag);
void GPT_DisableInt(GPT_Type* pGPT, uint32_t Intflag);
void GPT_ClearIntFlag(GPT_Type* pGPT, uint32_t Intflag);


#endif
