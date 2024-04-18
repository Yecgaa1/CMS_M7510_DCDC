/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    pga.c
* @brief   This file implements device driver for PGA module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "pga.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

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
* Function Name: PGA_Init
* @brief  This function initializes the Programmable Gain Amplifier module.
* @param  ch - specify the pga channel number
* @param  gain - Programmable gain amplifier amplification factor selection
* @return None
***********************************************************************************************************************/
void PGA_Init(pga_channel_t ch, pga_gain_t gain)
{
    if(ch == PGA00) 
    {
        CGC->PERA |= CGC_PERA_ADC0EN_Msk;    /* enables input clock supply */
    #if 0 /* full differenial input mode */
        ADC0->ADPGACR = _00_PGA_DIFF_FULL | _04_PGA_START | _02_PGA2ADC_ENABLE;
    #else /* pseudo differenial input mode */
        ADC0->ADPGACR = _08_PGA_DIFF_PSEUDO | _04_PGA_START | _02_PGA2ADC_ENABLE;
        ADC0->ADPGADCR = _00_PGA_VSS_SELECTED;
    #endif
        ADC0->ADPGAGS = gain;
		
		PGA00IN_PORT_SETTING();
		if(ADC0->ADPGADCR & _08_PGA_PGAGND_SELECTED )
			PGA00GND_PORT_SETTING();
    }
    else
    {
        CGC->PERA |= CGC_PERA_ADC1EN_Msk;    /* enables input clock supply */
    #if 0 /* full differenial input mode */
        ADC1->ADPGACR = (_00_PGA_DIFF_FULL | _04_PGA_START | _02_PGA2ADC_ENABLE) << 4*(ch - 1);
    #else /* pseudo differenial input mode */
        ADC1->ADPGACR = (_08_PGA_DIFF_PSEUDO | _04_PGA_START | _02_PGA2ADC_ENABLE) << 4*(ch - 1);
        ADC1->ADPGADCR = _00_PGA_VSS_SELECTED << 4*(ch - 1);
    #endif
        ADC1->ADPGAGS = gain << 4*(ch - 1);
		
		if(ch == PGA10)
		{
			PGA10IN_PORT_SETTING();
			if(ADC1->ADPGADCR & _08_PGA_PGAGND_SELECTED )
				PGA10GND_PORT_SETTING();			
		}
		if(ch == PGA11)
		{
			PGA11IN_PORT_SETTING();
			if(ADC1->ADPGADCR & _08_PGA_PGAGND_SELECTED << 4)
				PGA11GND_PORT_SETTING();			
		}
		if(ch == PGA12)
		{
			PGA12IN_PORT_SETTING();
			if(ADC1->ADPGADCR & _08_PGA_PGAGND_SELECTED << 8 )
				PGA12GND_PORT_SETTING();			
		}
    }
 }

/***********************************************************************************************************************
* Function Name: PGA_DeInit
* @brief  This function DeInitialize the programmable gain amplifier.
* @param  ch - specify the pga channel number
* @return None
***********************************************************************************************************************/
void PGA_DeInit(pga_channel_t ch)
{     
    if(ch == PGA00) 
    {
        ADC0->ADPGACR = _00_PGA_STOP;
    }
    else
    {
        ADC1->ADPGACR = _00_PGA_STOP << 4*(ch - 1);
    }
}

/***********************************************************************************************************************
* Function Name: PGA_SetGain
* @brief  This function DeInitialize the programmable gain amplifier.
* @param  ch - specify the pga channel number
* @param  gain - specify the gain of pga
* @return None
***********************************************************************************************************************/
void PGA_SetGain(pga_channel_t ch, pga_gain_t gain)
{
    if(ch == PGA00) 
    {
        ADC0->ADPGAGS = gain;
    }
    else 
    {
        ADC1->ADPGAGS = gain << 4*(ch - 1);
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
