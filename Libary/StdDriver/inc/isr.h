/***********************************************************************************************************************
* @file    isr.h
* @brief   header file for interrupt server routine.
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
 
#ifndef _ISR_H__
#define _ISR_H__
#include <stdbool.h>
#include <stdio.h>
#include "BAT32G439.h"


#define	ISR_SUCC   0
#define	ISR_ERR    1

typedef void(*isrFun_t)(void *msg);




typedef enum
{
	INT_IDLE = 0,
	INT_RX = 1,
	INT_TX = 2,
	INT_DMA =3,
}DATA_DIR_t;

typedef struct 
{
	DATA_DIR_t flag;
	uint32_t len;
	volatile uint8_t *data;
}ATE_FRAME_t;



/** @defgroup ISR_t 
  * @{
  */ 
typedef struct
{	
	bool IRQ_Flag;
	isrFun_t intHandle;
}ISR_t;


typedef struct
{
  IRQn_Type IRQ_Channel;  /*!< This member configures the IRQ channel. */
	
  ISR_t  IRQ[IIR1WFIFOFUL_IRQn+1];     /*!< This member configures the IRQ interrupt route and whether irq channel is used. 
							  This parameter can be a value of @ref ISR_t*/						
}ISR_InitTypeDef_t;

extern ATE_FRAME_t pData;
extern ISR_InitTypeDef_t IRQ_Fun;

int ISR_Register(IRQn_Type irq_num, void *interrupt);


#endif
