/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.c
* @brief   This file implements device driver for GPIO module.
* @version V1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G439.h"
#include "gpio.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/**
  * @brief  Initializes the PORTx
  * @param  PORTx: where x can be 0~14
  * @param  PINx: where x can be 0~7
  * @param  MODEx: such as INPUT,PULLUP_INPUT,TTL_INPUT,ANALOG_INPUT,OUTPUT,OPENDRAIN_OUTPUT      
	*
  * @retval None
  */
void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx)
{
  uint8_t mode = MODEx;
	uint16_t pos = 1<<PINx;
	
	switch(mode)
	{
		case INPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PMA+2*PORTx)) |= pos;
			*((volatile uint16_t*)(&PORT->POMA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PUA+2*PORTx)) &= ~pos;
			break;
		case PULLUP_INPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PMA+2*PORTx)) |= pos;
			*((volatile uint16_t*)(&PORT->POMA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PUA+2*PORTx)) |= pos;
			*((volatile uint16_t*)(&PORT->PDA+2*PORTx)) &= ~pos;
			break;
		case PULLDOWN_INPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PMA+2*PORTx)) |= pos;
			*((volatile uint16_t*)(&PORT->POMA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PUA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PDA+2*PORTx)) |= pos;
			break;
		case ANALOG_INPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) |= pos;
			break;
		case OUTPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PMA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->POMA+2*PORTx)) &= ~pos;
			break;
		case OPENDRAIN_OUTPUT:
			*((volatile uint16_t*)(&PORT->PMCA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->PMA+2*PORTx)) &= ~pos;
			*((volatile uint16_t*)(&PORT->POMA+2*PORTx)) |= pos;
			break;
	}
}


/**
  * @brief  Set the PORTx bit
  * @param  PORTx: where x can be 0~14
  * @param  PINx: where x can be 0~7    
	*
  * @retval None
  */
//void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
//{
//	uint8_t pos = 1<<PINx;
//	*((volatile uint8_t*)(&PORT->P0+PORTx)) |= pos;
//}

/**
  * @brief  Clear the PORTx bit
  * @param  PORTx: where x can be 0~14
  * @param  PINx: where x can be 0~7    
	*
  * @retval None
  */
//void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
//{
//	uint8_t pos = 1<<PINx;
//	*((volatile uint8_t*)(&PORT->P0+PORTx)) &= ~pos;
//}

/**
  * @brief  Toggle the PORTx bit
  * @param  PORTx: where x can be 0~14
  * @param  PINx: where x can be 0~7    
	*
  * @retval None
  */
//void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
//{
//	uint8_t pos = 1<<PINx;
//	*((volatile uint8_t*)(&PORT->P0+PORTx)) ^= pos;
//}

/**
  * @brief  Get the PORTx bit
  * @param  PORTx: where x can be 0~14
  * @param  PINx: where x can be 0~7    
	*
  * @retval None
  */
//uint8_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
//{
//	uint8_t pos = 1<<PINx;
//	//PORT->PMS = 0x01;        /*!< Digital output level of the pin is read */
//	return *((volatile uint8_t*)(&PORT->P0+PORTx))&pos;
//}




