/***********************************************************************************************************************
* @file    gpt.c
* @brief   This file implements device driver for GPT module.
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
 
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "userdefine.h"
#include "gpt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
//----------------------------------------------------------------------------------------------------------------------


/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/


/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: GPT0_Open
* @brief  This function initializes the GPT.
* @param  pGPT Pointer to a GPT
* @param  pGPTInit Pointer to a GPT_InitTypeDef structure
* @return None
***********************************************************************************************************************/

void GPT0_Open(GPT_Type* pGPT, GPT_InitTypeDef* pGPTInit)
{
	CGC->PERA |= CGC_PERA_GPT0EN_Msk;
	
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	pGPT->GTCR = (pGPTInit->timermode<<GPT0_GTCR00_MD_Pos) | (pGPTInit->clockprescaler<<GPT0_GTCR00_TPCS_Pos);
	
	pGPT->GTUDDTYC = pGPTInit->direction<<GPT0_GTUDDTYC00_UD_Pos;
	
	pGPT->GTPR = pGPTInit->period-1;
	pGPT->GTPBR = pGPTInit->period-1;
	
	if(TIMER_DIRECTION_UP == pGPTInit->direction)
	{
		pGPT->GTCNT = 0;
	}
	else
	{
		pGPT->GTCNT = pGPTInit->period-1;
	}
	
	pGPT->GTIOR = pGPTInit->channelA_output_func<<GPT0_GTIOR00_GTIOA_Pos | pGPTInit->channelB_output_func<<GPT0_GTIOR00_GTIOB_Pos | \
								pGPTInit->channelA_output_enable<<GPT0_GTIOR00_OAE_Pos | pGPTInit->channelB_output_enable<<GPT0_GTIOR00_OBE_Pos;
	pGPT->GTBER = pGPTInit->channelA_buffer<<GPT0_GTBER00_CCRA_Pos | pGPTInit->channelB_buffer<<GPT0_GTBER00_CCRB_Pos | pGPTInit->period_buffer<<GPT0_GTBER00_PR_Pos;
	
	pGPT->GTCCRA = pGPTInit->dutyA-1;
	pGPT->GTCCRB = pGPTInit->dutyB-1;
	pGPT->GTCCRC = pGPTInit->dutyA-1;
	pGPT->GTCCRD = pGPTInit->dutyA-1;
	pGPT->GTCCRE = pGPTInit->dutyB-1;
	pGPT->GTCCRF = pGPTInit->dutyB-1;
	
	if(pGPTInit->deadtime)
	{
		pGPT->GTDTCR = 1<<GPT0_GTDTCR00_TDE_Pos;
		pGPT->GTDVU = pGPTInit->deadtime;
	}
	else
	{
		pGPT->GTDTCR = 0;
	}
	
//	pGPT->GTCR |= 1<<GPT0_GTCR00_CST_Pos;
	pGPT->GTSSR |= 1<<GPT0_GTSSR00_CSTRT_Pos;
	pGPT->GTPSR |= 1<<GPT0_GTPSR00_CSTOP_Pos;
	pGPT->GTCSR |= 1<<GPT0_GTCSR00_CCLR_Pos;
	
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT_Start
* @brief  This function starts the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT0_Start(uint32_t chan)
{
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	GPT00->GTSTR = chan;
	
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT_Stop
* @brief  This function stops the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT0_Stop(uint32_t chan)
{
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	GPT00->GTSTP = chan;
	
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT_ClearCounter
* @brief  This function stops the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT0_ClearCounter(uint32_t chan)
{
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	GPT00->GTCLR = chan;
	
	GPT00->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT1_Open
* @brief  This function initializes the GPT.
* @param  pGPT Pointer to a GPT
* @param  pGPTInit Pointer to a GPT_InitTypeDef structure
* @return None
***********************************************************************************************************************/

void GPT1_Open(GPT_Type* pGPT, GPT_InitTypeDef* pGPTInit)
{
	CGC->PERA |= CGC_PERA_GPT1EN_Msk;
	
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	pGPT->GTCR = (pGPTInit->timermode<<GPT0_GTCR00_MD_Pos) | (pGPTInit->clockprescaler<<GPT0_GTCR00_TPCS_Pos);
	
	pGPT->GTUDDTYC = pGPTInit->direction<<GPT0_GTUDDTYC00_UD_Pos;
	
	pGPT->GTPR = pGPTInit->period-1;
	pGPT->GTPBR = pGPTInit->period-1;
	
	if(TIMER_DIRECTION_UP == pGPTInit->direction)
	{
		pGPT->GTCNT = 0;
	}
	else
	{
		pGPT->GTCNT = pGPTInit->period-1;
	}
	
	pGPT->GTIOR = pGPTInit->channelA_output_func<<GPT0_GTIOR00_GTIOA_Pos | pGPTInit->channelB_output_func<<GPT0_GTIOR00_GTIOB_Pos | \
								pGPTInit->channelA_output_enable<<GPT0_GTIOR00_OAE_Pos | pGPTInit->channelB_output_enable<<GPT0_GTIOR00_OBE_Pos;
	pGPT->GTBER = pGPTInit->channelA_buffer<<GPT0_GTBER00_CCRA_Pos | pGPTInit->channelB_buffer<<GPT0_GTBER00_CCRB_Pos | pGPTInit->period_buffer<<GPT0_GTBER00_PR_Pos;
	
	pGPT->GTCCRA = pGPTInit->dutyA-1;
	pGPT->GTCCRB = pGPTInit->dutyB-1;
	pGPT->GTCCRC = pGPTInit->dutyA-1;
	pGPT->GTCCRD = pGPTInit->dutyA-1;
	pGPT->GTCCRE = pGPTInit->dutyB-1;
	pGPT->GTCCRF = pGPTInit->dutyB-1;
	
	if(pGPTInit->deadtime)
	{
		pGPT->GTDTCR = 1<<GPT0_GTDTCR00_TDE_Pos;
		pGPT->GTDVU = pGPTInit->deadtime;
	}
	else
	{
		pGPT->GTDTCR = 0;
	}
	
//	pGPT->GTCR |= 1<<GPT0_GTCR00_CST_Pos;
	pGPT->GTSSR |= 1<<GPT0_GTSSR00_CSTRT_Pos;
	pGPT->GTPSR |= 1<<GPT0_GTPSR00_CSTOP_Pos;
	pGPT->GTCSR |= 1<<GPT0_GTCSR00_CCLR_Pos;
	

	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}
/***********************************************************************************************************************
* Function Name: GPT_Start
* @brief  This function starts the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT1_Start(uint32_t chan)
{
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);

	GPT10->GTSTR = chan;
	
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT_Stop
* @brief  This function stops the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT1_Stop(uint32_t chan)
{
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);

	GPT10->GTSTP = chan;
	
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}


/***********************************************************************************************************************
* Function Name: GPT_ClearCounter
* @brief  This function stops the GPT.
* @param  chan: GPT channel
*								GPT_CHANNEL00 ~ GPT_CHANNEL17
* @return None
***********************************************************************************************************************/
void GPT1_ClearCounter(uint32_t chan)
{
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);
	
	GPT10->GTCLR = chan;
	
	GPT10->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;
}

/***********************************************************************************************************************
* Function Name: GPT_EnableInt
* @brief  This function enable the GPT interrupt.
* @param  pGPT Pointer to a GPT
* @param  Intflag: interrupt enable flag
*										GPT_GTINTAD_INTAEN_BIT ~ GPT_GTINTAD_INTPUEN_BIT
* @return None
***********************************************************************************************************************/

void GPT_EnableInt(GPT_Type* pGPT, uint32_t Intflag)
{
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);

	pGPT->GTINTAD |= Intflag;
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;

}
/***********************************************************************************************************************
* Function Name: GPT_DisableInt
* @brief  This function disable the GPT interrupt.
* @param  pGPT Pointer to a GPT
* @param  Intflag: interrupt enable flag
*										GPT_GTINTAD_INTAEN_BIT ~ GPT_GTINTAD_INTPUEN_BIT
* @return None
***********************************************************************************************************************/

void GPT_DisableInt(GPT_Type* pGPT, uint32_t Intflag)
{
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);

	pGPT->GTINTAD &= ~Intflag;
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;

}
/***********************************************************************************************************************
* Function Name: GPT_ClearIntFlag
* @brief  This function clear the GPT interrupt flag.
* @param  pGPT Pointer to a GPT
* @param  Intflag: interrupt flag
*										GPT_GTST_TCFA_BIT ~ GPT_GTST_TCFPU_BIT
* @return None
***********************************************************************************************************************/

void GPT_ClearIntFlag(GPT_Type* pGPT, uint32_t Intflag)
{
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos);

	pGPT->GTST &= ~Intflag;
	pGPT->GTWP = (0xA5<<GPT0_GTWP00_PRKEY_Pos)|GPT0_GTWP00_WP_Msk;

}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
