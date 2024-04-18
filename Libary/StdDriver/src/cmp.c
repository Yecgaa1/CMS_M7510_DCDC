/***********************************************************************************************************************
* Copyright (C)  All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    cmp.c
* @brief   This file implements device driver for COMP module.
* @version V1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "userdefine.h"
#include "cmp.h"
#include "isr.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

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
extern void cmp0_interrupt(void);
extern void cmp1_interrupt(void);
extern void cmp2_interrupt(void);
extern void cmp3_interrupt(void);

/***********************************************************************************************************************
* Function Name: CMP_Init
* @brief  This function initilize the CMP. 
* @param  ch - specify the comp channel number
* @param  positive_side - specify the input signal of positive side of comparator 
* @param  negative_side - specify the input signal of negative side of comparator 
* @return None
***********************************************************************************************************************/
void CMP_Init(CMP_Type* pCMP, CMP_InitTypeDef* pCMPInit)
{
    CGC->PERA |= CGC_PERA_CMPPGAEN_Msk;    /* enables input clock supply */
		
    pCMP->COMPFIR = pCMPInit->filter_select<<CMP0_COMP0FIR_C0FCK_Pos;
	
		if(CMP_EDGE_BOTH == pCMPInit->edge_select)
		{
			pCMP->COMPFIR |= 1UL<<CMP0_COMP0FIR_C0EDG_Pos;
		}
		else
		{
			pCMP->COMPFIR |= pCMPInit->edge_select<<CMP0_COMP0FIR_C0EPO_Pos;
		}
		
		pCMP->COMPOCR = pCMPInit->interrupt_enable<<CMP0_COMP0OCR_C0IE_Pos;
		pCMP->COMPOCR |= pCMPInit->vcout_enable<<CMP0_COMP0OCR_C0OE_Pos;
		pCMP->COMPOCR |= pCMPInit->vcout_reverse_enable<<CMP0_COMP0OCR_C0OP_Pos;
		
		pCMP->COMPSEL = pCMPInit->pside_select<<CMP0_COMP0SEL_CMPSEL_Pos;
		pCMP->COMPSEL |= pCMPInit->nside_select<<CMP0_COMP0SEL_C0REFS_Pos;
		
		pCMP->COMPHY = pCMPInit->hysteresis_select<<CMP0_COMP0HY_C0HYSLS_Pos;
		pCMP->COMPHY |= pCMPInit->hysteresis_voltage<<CMP0_COMP0HY_C0HYSVS_Pos;
		
    if(CMP0 == pCMP)
		{
			CMP0_PORT_SETTING();
		}
		else if(CMP1 == pCMP)
		{
			CMP1_PORT_SETTING();
		}
		else if(CMP2 == pCMP)
		{
			CMP2_PORT_SETTING();
		}
		else if(CMP3 == pCMP)
		{
			CMP3_PORT_SETTING();
		}
		
}

///***********************************************************************************************************************
//* Function Name: CMP_Start
//* @brief  This function starts the Comparator.
//* @param  ch - specify the channel
//* @return None
//***********************************************************************************************************************/
void CMP_Start(CMP_Type* pCMP)
{
   
    pCMP->COMPMDR = 1UL<<CMP0_COMP0MDR_C0ENB_Pos;
    
		if(CMP0 == pCMP)
		{
            NVIC_ClearPendingIRQ(CMP0_IRQn);    /* clear INTCMP0 interrupt flag */
            NVIC_EnableIRQ(CMP0_IRQn);          /* enable INTCMP0 interrupt */
		}
		else if(CMP1 == pCMP)
		{
            NVIC_ClearPendingIRQ(CMP1_IRQn);    /* clear INTCMP1 interrupt flag */
            NVIC_EnableIRQ(CMP1_IRQn);          /* enable INTCMP1 interrupt */
		}
		else if(CMP2 == pCMP)
		{
            NVIC_ClearPendingIRQ(CMP2_IRQn);    /* clear INTCMP2 interrupt flag */
            NVIC_EnableIRQ(CMP2_IRQn);          /* enable INTCMP2 interrupt */
		}
		else if(CMP3 == pCMP)
		{
            NVIC_ClearPendingIRQ(CMP3_IRQn);    /* clear INTCMP3 interrupt flag */
            NVIC_EnableIRQ(CMP3_IRQn);          /* enable INTCMP3 interrupt */
		}
}
///***********************************************************************************************************************
//* Function Name: CMP_Stop
//* @brief  This function stops the Comparator.
//* @param  ch - specify the channel
//* @return None
//***********************************************************************************************************************/
void CMP_Stop(CMP_Type* pCMP)
{
   
    pCMP->COMPMDR &= ~(1UL<<CMP0_COMP0MDR_C0ENB_Pos);
    
		if(CMP0 == pCMP)
		{
            NVIC_DisableIRQ(CMP0_IRQn);         /* disable INTCMP0 interrupt */
            NVIC_ClearPendingIRQ(CMP0_IRQn);    /* clear INTCMP0 interrupt flag */
		}
		else if(CMP1 == pCMP)
		{
            NVIC_DisableIRQ(CMP1_IRQn);         /* disable INTCMP1 interrupt */
            NVIC_ClearPendingIRQ(CMP1_IRQn);    /* clear INTCMP1 interrupt flag */
		}
		else if(CMP2 == pCMP)
		{
            NVIC_DisableIRQ(CMP2_IRQn);         /* disable INTCMP2 interrupt */
            NVIC_ClearPendingIRQ(CMP2_IRQn);    /* clear INTCMP2 interrupt flag */
		}
		else if(CMP3 == pCMP)
		{
            NVIC_DisableIRQ(CMP3_IRQn);         /* disable INTCMP3 interrupt */
            NVIC_ClearPendingIRQ(CMP3_IRQn);    /* clear INTCMP3 interrupt flag */
		}
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
