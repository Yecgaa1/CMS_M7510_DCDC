/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.h
* @brief   This file implements device driver for GPIO module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H
#ifndef __CORE_CM0PLUS_H_GENERIC
//#include "core_cm0plus.h"
#endif

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
	PORTA = 0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
	
}PORT_TypeDef;

typedef enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
}PIN_TypeDef;

typedef enum {
	INPUT = 0,
	PULLUP_INPUT,
	PULLDOWN_INPUT,
	TTL_INPUT,
	ANALOG_INPUT,
	OUTPUT,
	OPENDRAIN_OUTPUT,
	
}PIN_ModeDef;

#define PIN_MASK_0                 ((uint16_t)(0x01))  /*!< Pin 0 selected    */
#define PIN_MASK_1                 ((uint16_t)(0x02))  /*!< Pin 1 selected    */
#define PIN_MASK_2                 ((uint16_t)(0x04))  /*!< Pin 2 selected    */
#define PIN_MASK_3                 ((uint16_t)(0x08))  /*!< Pin 3 selected    */
#define PIN_MASK_4                 ((uint16_t)(0x10))  /*!< Pin 4 selected    */
#define PIN_MASK_5                 ((uint16_t)(0x20))  /*!< Pin 5 selected    */
#define PIN_MASK_6                 ((uint16_t)(0x40))  /*!< Pin 6 selected    */
#define PIN_MASK_7                 ((uint16_t)(0x80))  /*!< Pin 7 selected    */
#define PIN_MASK_8                 ((uint16_t)(0x0100))  /*!< Pin 0 selected    */
#define PIN_MASK_9                 ((uint16_t)(0x0200))  /*!< Pin 1 selected    */
#define PIN_MASK_10                 ((uint16_t)(0x0400))  /*!< Pin 2 selected    */
#define PIN_MASK_11                 ((uint16_t)(0x0800))  /*!< Pin 3 selected    */
#define PIN_MASK_12                 ((uint16_t)(0x1000))  /*!< Pin 4 selected    */
#define PIN_MASK_13                 ((uint16_t)(0x2000))  /*!< Pin 5 selected    */
#define PIN_MASK_14                 ((uint16_t)(0x4000))  /*!< Pin 6 selected    */
#define PIN_MASK_15                 ((uint16_t)(0x8000))  /*!< Pin 7 selected    */


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/

void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx);
//void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//uint8_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);

/*****************************************************************************
 ** \brief	 PORT_SetBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_SetBit(PORTx,PINx)  do{\
											*((uint16_t*)((uint16_t*)&PORT->PSETA+2*PORTx)) = (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ClrBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ClrBit(PORTx,PINx)  do{\
											*((uint16_t*)((uint16_t*)&PORT->PCLRA+2*PORTx)) = (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ToggleBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ToggleBit(PORTx,PINx)  do{\
											*((uint16_t*)((uint16_t*)&PORT->PA+2*PORTx)) ^= (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_GetBit
 **	
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  PORT Bit
 ** \note	 
*****************************************************************************/
#define   PORT_GetBit(PORTx,PINx)  (*((uint16_t*)((uint16_t*)&PORT->PREADA+2*PORTx)) & (1<<PINx))
											 
											 
#endif

