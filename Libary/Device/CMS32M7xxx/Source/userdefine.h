/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    userdefine.h
* @brief   This file includes user definition.
* @version 1.0.0
* @date    2022/10/24
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__

typedef unsigned short 	MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)  /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)  /* error 5 */
#endif

#define TRMW   *((volatile uint8_t *)(0x40021C10))
#define TRMR   *((volatile uint8_t *)(0x40021C14))
#define TRMT   *((volatile uint8_t *)(0x40021C18))

/***********************************************************************************************************************
Macro definitions for Clock
***********************************************************************************************************************/
#define CPU_CLOCK_FREQ 64000000UL
#define PLL_CLOCK

/***********************************************************************************************************************
Macro definitions for CAN
***********************************************************************************************************************/
#define CAN0_USE
#define CAN1_USE

#define CAN_REC_MASK1 0x1fffffffU
#define CAN_REC_MASK2 0x1fffffffU
#define CAN_REC_MASK3 0x1fffffffU
#define CAN_REC_MASK4 0x1fffffffU

/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_TX      /*! Using CH0 of SCI0 as UART Transmitter */
//#define USE_SCI_SPI00         /*! Using CH0 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC00         /*! Using CH0 of SCI0 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART0_TX) & defined(USE_SCI_SPI00))|\
     (defined(USE_SCI_UART0_TX) & defined(USE_SCI_IIC00))|\
     (defined(USE_SCI_SPI00)    & defined(USE_SCI_IIC00)))
    #error "Multi-functions declared of SCI00."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_RX      /*! Using CH1 of SCI0 as UART Receiver */
//#define USE_SCI_SPI01         /*! Using CH1 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC01         /*! Using CH1 of SCI0 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART0_RX) & defined(USE_SCI_SPI01))|\
     (defined(USE_SCI_UART0_RX) & defined(USE_SCI_IIC01))|\
     (defined(USE_SCI_SPI01)    & defined(USE_SCI_IIC01)))
    #error "Multi-functions declared of SCI01."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_TX      /*! Using CH0 of SCI1 as UART Transmitter */
//#define USE_SCI_SPI10         /*! Using CH0 of SCI1 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC10         /*! Using CH0 of SCI1 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART1_TX) & defined(USE_SCI_SPI10))|\
     (defined(USE_SCI_UART1_TX) & defined(USE_SCI_IIC10))|\
     (defined(USE_SCI_SPI10)    & defined(USE_SCI_IIC10)))
    #error "Multi-functions declared of SCI10."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_RX      /*! Using CH1 of SCI1 as UART Receiver */
//#define USE_SCI_SPI11         /*! Using CH1 of SCI1 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC11         /*! Using CH1 of SCI1 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART1_RX) & defined(USE_SCI_SPI11))|\
     (defined(USE_SCI_UART1_RX) & defined(USE_SCI_IIC11))|\
     (defined(USE_SCI_SPI11)    & defined(USE_SCI_IIC11)))
    #error "Multi-functions declared of SCI11."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_TX      /*! Using CH0 of SCI2 as UART Transmitter */
//#define USE_SCI_SPI20         /*! Using CH0 of SCI2 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC20         /*! Using CH0 of SCI2 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART2_TX) & defined(USE_SCI_SPI20))|\
     (defined(USE_SCI_UART2_TX) & defined(USE_SCI_IIC20))|\
     (defined(USE_SCI_SPI20)    & defined(USE_SCI_IIC20)))
    #error "Multi-functions declared of SCI20."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_RX      /*! Using CH1 of SCI3 as UART Receiver */
//#define USE_SCI_SPI21         /*! Using CH1 of SCI3 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC21         /*! Using CH1 of SCI3 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART2_RX) & defined(USE_SCI_SPI21))|\
     (defined(USE_SCI_UART2_RX) & defined(USE_SCI_IIC21))|\
     (defined(USE_SCI_SPI21)    & defined(USE_SCI_IIC21)))
    #error "Multi-functions declared of SCI21."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART3_TX      /*! Using CH0 of SCI3 as UART Transmitter */
//#define USE_SCI_SPI30         /*! Using CH0 of SCI3 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC30         /*! Using CH0 of SCI3 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART3_TX) & defined(USE_SCI_SPI30))|\
     (defined(USE_SCI_UART3_TX) & defined(USE_SCI_IIC30))|\
     (defined(USE_SCI_SPI30)    & defined(USE_SCI_IIC30)))
    #error "Multi-functions declared of SCI20."
#endif

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART3_RX      /*! Using CH1 of SCI2 as UART Receiver */
//#define USE_SCI_SPI31         /*! Using CH1 of SCI2 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC31         /*! Using CH1 of SCI2 as IIC Transmitter or Receiver */
#if ((defined(USE_SCI_UART3_RX) & defined(USE_SCI_SPI31))|\
     (defined(USE_SCI_UART3_RX) & defined(USE_SCI_IIC31))|\
     (defined(USE_SCI_SPI31)    & defined(USE_SCI_IIC31)))
    #error "Multi-functions declared of SCI21."
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    SPI_MODE_0 = 0,  // Mode 0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1 
    SPI_MODE_1 = 1,  // Mode 1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0 
    SPI_MODE_2 = 2,  // Mode 2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1 
    SPI_MODE_3 = 3  // Mode 3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0 
} spi_mode_t;

/***********************************************************************************************************************
DMA Control Data Set definitions
***********************************************************************************************************************/

/** @addtogroup Peripherals_Port_Setting_Definations
  * @{
  */

/* ================================================================================================================== */
/* ================                                       TM80                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM80 TI00~7 and TO00~7 Port Setting
  */

/* ToDo: You can allocate the TI00 to PD00 and PD07 pins */
#define TI00_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x03;	    /* allocate TI00 to PD00 */ \
        PORT->PMD  |=  (1 << 0);    /* PD00 is used as TI00 input */ \
}while(0)

/* ToDo: You can allocate the TI01 to PD12 and PE12 pins */
#define TI01_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x04;	    /* allocate TI01 to PD12 */ \
        PORT->PMD  |=  (1 <<12);    /* PD12 is used as TI01 input */ \
}while(0)

/* ToDo: You can allocate the TI02 to PB02 (Alternative to fixed port) */
#define TI02_PORT_SETTING() do{ \
        PORT->PB02CFG = 0x00;	    /* allocate TI02 to PB02 */ \
        PORT->PMCB &= ~(1 << 2);    /* PB02 digital function */ \
        PORT->PMB  |=  (1 << 2);    /* PB02 is used as TI02 input */ \
}while(0)

/* ToDo: You can allocate the TI03 to PD10 (Alternative to fixed port) */
#define TI03_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x00;	    /* allocate TI03 to PD10 */ \
        PORT->PMD  |=  (1 <<10);    /* PD10 is used as TI03 input */ \
}while(0)

/* ToDo: You can allocate the TI04 to PB05 and PB14 pins */
#define TI04_PORT_SETTING() do{ \
        PORT->PB05CFG = 0x00;	    /* allocate TI04 to PB05 */ \
        PORT->PMCB &= ~(1 << 5);    /* PB05 digital function */ \
        PORT->PMB  |=  (1 << 5);    /* PB05 is used as TI04 input */ \
}while(0)

/* ToDo: You can allocate the TI05 to PE12 (Alternative to fixed port) */
#define TI05_PORT_SETTING() do{ \
        PORT->PE12CFG = 0x04;	    /* allocate TI05 to PE12 */ \
        PORT->PME  |=  (1 <<12);    /* PE12 is used as TI05 input */ \
}while(0)

/* ToDo: You can allocate the TI06 to PB01 and PD07 pins */
#define TI06_PORT_SETTING() do{ \
        PORT->PB01CFG = 0x00;	    /* allocate TI06 to PB01 */ \
        PORT->PMCB &= ~(1 << 1);    /* PB01 digital function */ \
        PORT->PMB  |=  (1 << 1);    /* PB01 is used as TI06 input */ \
}while(0)

/* ToDo: You can allocate the TI07 to PC15 (Alternative to fixed port) */
#define TI07_PORT_SETTING() do{ \
        PORT->PC15CFG = 0x00;	    /* allocate TI07 to PC15 */ \
        PORT->PMC  |=  (1 <<15);    /* PC15 is used as TI07 input */ \
}while(0)

/* ToDo: You can allocate the TO00 to PD06, PD11 and PE10 pins */
#define TO00_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x03;	    /* allocate TO00 to PD06 */ \
        PORT->PMD  &= ~(1 << 6);    /* PD06 is used as TO00 output */ \
        PORT->POMD &= ~(1 << 6);    /* PD06 is push-pull output mode */ \
        PORT->PCLRD =  (1 << 6);    /* PD06 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO01 to PD09 (Alternative to fixed port) */
#define TO01_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	    /* allocate TO01 to PD09 */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as TO01 output */ \
        PORT->POMD &= ~(1 << 9);    /* PD09 is push-pull output mode */ \
        PORT->PCLRD =  (1 << 9);    /* PD09 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO02 to PB03, PC12 and PD15 pins */
#define TO02_PORT_SETTING() do{ \
        PORT->PB03CFG = 0x03;	    /* allocate TO02 to PB03 */ \
        PORT->PMCB &= ~(1 << 3);    /* PB03 digital function */ \
        PORT->PMB  &= ~(1 << 3);    /* PB03 is used as TO02 output */ \
        PORT->POMB &= ~(1 << 3);    /* PB03 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 3);    /* PB03 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO03 to PB06 (Alternative to fixed port) */
#define TO03_PORT_SETTING() do{ \
        PORT->PB06CFG = 0x00;	    /* allocate TO03 to PB06 */ \
        PORT->PMCB &= ~(1 << 6);    /* PB06 digital function */ \
        PORT->PMB  &= ~(1 << 6);    /* PB06 is used as TO03 output */ \
        PORT->POMB &= ~(1 << 6);    /* PB06 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 6);    /* PB06 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO04 to PB04, PB13, PC13 and PD12 pins */
#define TO04_PORT_SETTING() do{ \
        PORT->PB04CFG = 0x03;	    /* allocate TO04 to PB04 */ \
        PORT->PMCB &= ~(1 << 4);    /* PB04 digital function */ \
        PORT->PMB  &= ~(1 << 4);    /* PB04 is used as TO04 output */ \
        PORT->POMB &= ~(1 << 4);    /* PB04 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 4);    /* PB04 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO05 to PE13 (Alternative to fixed port) */
#define TO05_PORT_SETTING() do{ \
        PORT->PE13CFG = 0x00;	    /* allocate TO05 to PE13 */ \
        PORT->PME  &= ~(1 <<13);    /* PE13 is used as TO05 output */ \
        PORT->POME &= ~(1 <<13);    /* PE13 is push-pull output mode */ \
        PORT->PCLRE =  (1 <<13);    /* PE13 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO06 to PB02, PD14 and PE11 pins */
#define TO06_PORT_SETTING() do{ \
        PORT->PB02CFG = 0x03;	    /* allocate TO06 to PB02 */ \
        PORT->PMCB &= ~(1 << 2);    /* PB02 digital function */ \
        PORT->PMB  &= ~(1 << 2);    /* PB02 is used as TO06 output */ \
        PORT->POMB &= ~(1 << 2);    /* PB02 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 2);    /* PB02 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO07 to PC14 (Alternative to fixed port) */
#define TO07_PORT_SETTING() do{ \
        PORT->PC14CFG = 0x00;	    /* allocate TO07 to PC14 */ \
        PORT->PMC  &= ~(1 <<14);    /* PC14 is used as TO07 output */ \
        PORT->POMC &= ~(1 <<14);    /* PC14 is push-pull output mode */ \
        PORT->PCLRC =  (1 <<14);    /* PC14 output "L" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       TM81                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM81 TI10~3 and TO10~3 Port Setting (Alternative to fixed ports)
  */

/* ToDo: You can allocate the TI10 to PB00 and PD02 pins */
#define TI10_PORT_SETTING() do{ \
        PORT->PB00CFG = 0x01;	    /* allocate TI10 to PB00 */ \
        PORT->PMCB &= ~(1 << 0);    /* PB00 digital function */ \
        PORT->PMB  |=  (1 << 0);    /* PB00 is used as TI10 input */ \
}while(0)

/* ToDo: You can allocate the TI11 to PB01 and PD01 pins */
#define TI11_PORT_SETTING() do{ \
        PORT->PB01CFG = 0x01;	    /* allocate TI11 to PB01 */ \
        PORT->PMCB &= ~(1 << 1);    /* PB01 digital function */ \
        PORT->PMB  |=  (1 << 1);    /* PB01 is used as TI11 input */ \
}while(0)

/* ToDo: You can allocate the TI12 to PD00 (Alternative to fixed port) */
#define TI12_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x00;	    /* allocate TI12 to PD00 */ \
        PORT->PMD  |=  (1 << 0);    /* PD00 is used as TI12 input */ \
}while(0)

/* ToDo: You can allocate the TI13 to PD11 (Alternative to fixed port) */
#define TI13_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x00;	    /* allocate TI13 to PD11 */ \
        PORT->PMD  |=  (1 <<11);    /* PD11 is used as TI13 input */ \
}while(0)

/* ToDo: You can allocate the TI14 to PB08, PD09 and PD10 pins */
#define TI14_PORT_SETTING() do{ \
        PORT->PB08CFG = 0x01;	    /* allocate TI14 to PB08 */ \
        PORT->PMCB &= ~(1 << 8);    /* PB08 digital function */ \
        PORT->PMB  |=  (1 << 8);    /* PB08 is used as TI14 input */ \
}while(0)

/* ToDo: You can allocate the TI15 to PB05, PC15 and PE00 pins */
#define TI15_PORT_SETTING() do{ \
        PORT->PB05CFG = 0x01;	    /* allocate TI15 to PB05 */ \
        PORT->PMCB &= ~(1 << 5);    /* PB05 digital function */ \
        PORT->PMB  |=  (1 << 5);    /* PB05 is used as TI15 input */ \
}while(0)

/* ToDo: You can allocate the TI16 to PB07, PC11 and PE12 pins */
#define TI16_PORT_SETTING() do{ \
        PORT->PB07CFG = 0x01;	    /* allocate TI16 to PB07 */ \
        PORT->PMCB &= ~(1 << 7);    /* PB07 digital function */ \
        PORT->PMB  |=  (1 << 7);    /* PB07 is used as TI16 input */ \
}while(0)

/* ToDo: You can allocate the TI17 to PC14, PE06 and PE13 pins */
#define TI17_PORT_SETTING() do{ \
        PORT->PC14CFG = 0x01;	    /* allocate TI17 to PC14 */ \
        PORT->PMC  |=  (1 <<14);    /* PC14 is used as TI16 input */ \
}while(0)

/* ToDo: You can allocate the TO10 to PB00 and PD02 pins */
#define TO10_PORT_SETTING() do{ \
        PORT->PB00CFG = 0x01;	    /* allocate TO10 to PB00 */ \
        PORT->PMCB &= ~(1 << 0);    /* PB00 digital function */ \
        PORT->PMB  &= ~(1 << 0);    /* PB00 is used as TI10 input */ \
        PORT->POMB &= ~(1 << 0);    /* PB00 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 0);    /* PB00 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO11 to PB01 and PD01 pins */
#define TO11_PORT_SETTING() do{ \
        PORT->PB01CFG = 0x01;	    /* allocate TO11 to PB01 */ \
        PORT->PMCB &= ~(1 << 1);    /* PB01 digital function */ \
        PORT->PMB  &= ~(1 << 1);    /* PB01 is used as TO11 output */ \
        PORT->POMB &= ~(1 << 1);    /* PB01 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 1);    /* PB01 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO12 to PD00 (Alternative to fixed port) */
#define TO12_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x00;	    /* allocate TO12 to PD00 */ \
        PORT->PMD  &= ~(1 << 0);    /* PD00 is used as TO12 output */ \
        PORT->POMD &= ~(1 << 0);    /* PD00 is push-pull output mode */ \
        PORT->PCLRD =  (1 << 0);    /* PD00 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO13 to PD11 (Alternative to fixed port) */
#define TO13_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x00;	    /* allocate TO13 to PD11 */ \
        PORT->PMD  &= ~(1 <<11);    /* PD11 is used as TO13 output */ \
        PORT->POMD &= ~(1 <<11);    /* PD11 is push-pull output mode */ \
        PORT->PCLRD =  (1 <<11);    /* PD11 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO14 to PB08, PD09 and PD10 pins */
#define TO14_PORT_SETTING() do{ \
        PORT->PB08CFG = 0x01;	    /* allocate TO14 to PB08 */ \
        PORT->PMCB &= ~(1 << 8);    /* PB08 digital function */ \
        PORT->PMB  &= ~(1 << 8);    /* PB08 is used as TO14 output */ \
        PORT->POMB &= ~(1 << 8);    /* PB08 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 8);    /* PB08 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO15 to PB05, PC15 and PE00 pins */
#define TO15_PORT_SETTING() do{ \
        PORT->PB05CFG = 0x01;	    /* allocate TO15 to PB05 */ \
        PORT->PMCB &= ~(1 << 5);    /* PB05 digital function */ \
        PORT->PMB  &= ~(1 << 5);    /* PB05 is used as TO15 output */ \
        PORT->POMB &= ~(1 << 5);    /* PB05 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 5);    /* PB05 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO16 to PB07, PC11 and PE12 pins */
#define TO16_PORT_SETTING() do{ \
        PORT->PB07CFG = 0x01;	    /* allocate TO16 to PB07 */ \
        PORT->PMCB &= ~(1 << 7);    /* PB07 digital function */ \
        PORT->PMB  &= ~(1 << 7);    /* PB07 is used as TO16 output */ \
        PORT->POMB &= ~(1 << 7);    /* PB07 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 7);    /* PB07 output "L" */ \
}while(0)

/* ToDo: You can allocate the TO17 to PC14, PE06 and PE13 pins */
#define TO17_PORT_SETTING() do{ \
        PORT->PC14CFG = 0x01;	    /* allocate TO17 to PC14 */ \
        PORT->PMC  &= ~(1 <<14);    /* PC14 is used as TO16 output */ \
        PORT->POMC &= ~(1 <<14);    /* PC14 is push-pull output mode */ \
        PORT->PCLRC =  (1 <<14);    /* PC14 output "L" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      RTC1HZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief RTC1HZ Port Setting (Alternative to fixed port)
  */

#define RTC1HZ_PORT_SETTING() do{ \
        PORT->PE00CFG = 0x03;	    /* allocate RTC1HZ to PE00 */ \
        PORT->PME  &= ~(1 << 0);    /* PE00 is used as RTC1HZ output */ \
        PORT->POME &= ~(1 << 0);    /* PE00 is push-pull output mode */ \
        PORT->PCLRE =  (1 << 0);    /* PE00 output "L" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      CLKBUZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief CLKBUZ Port Setting
  */

/* ToDo: You can allocate the CLKBUZ0 to PE05 pin ONLY */
#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->PE05CFG = 0x03;	    /* allocate CLKBUZ0 to PE05 */ \
        PORT->PME  &= ~(1 << 5);    /* PE05 is used as CLKBUZ0 output */ \
        PORT->POME &= ~(1 << 5);    /* PE05 is push-pull output mode */ \
        PORT->PCLRE =  (1 << 5);    /* PE05 output "L" */ \
}while(0)

/* ToDo: You can allocate the CLKBUZ1 to PD03 (Alternative to fixed port) */
#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->PD03CFG = 0x00;	    /* allocate CLKBUZ1 to PD03 */ \
        PORT->PMD  &= ~(1 << 3);    /* PD03 is used as CLKBUZ1 output */ \
        PORT->POMD &= ~(1 << 3);    /* PD03 is push-pull output mode */ \
        PORT->PCLRD =  (1 << 3);    /* PD03 output "L" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        ADC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief ADC Port Setting (Alternate to fixed ports)
  */

/* ToDo: Please comment out the following unused ANIx setting according to your application needs. */
#define ADC0_PORT_SETTING() do{ \
        PORT->PMCA |= (1 << 0);     /* Set ANI000(PA00) pin */ \
        PORT->PMCA |= (1 << 1);     /* Set ANI001(PA01) pin */ \
        PORT->PMCA |= (1 << 2);     /* Set ANI002(PA02) pin */ \
        PORT->PMCA |= (1 <<11);     /* Set ANI003(PA11) pin */ \
        PORT->PMCB |= (1 <<13);     /* Set ANI004(PB13) pin */ \
        PORT->PMCB |= (1 <<14);     /* Set ANI005(PB14) pin */ \
        PORT->PMCB |= (1 <<15);     /* Set ANI006(PB15) pin */ \
        PORT->PMCB |= (1 << 8);     /* Set ANI007(PB08) pin */ \
}while(0)
#define ADC1_PORT_SETTING() do{ \
        PORT->PMCA |= (1 << 3);     /* Set ANI100(PA03) pin */ \
        PORT->PMCA |= (1 << 4);     /* Set ANI101(PA04) pin */ \
        PORT->PMCA |= (1 << 5);     /* Set ANI102(PA05) pin */ \
        PORT->PMCA |= (1 <<12);     /* Set ANI103(PA12) pin */ \
        PORT->PMCB |= (1 << 6);     /* Set ANI104(PB06) pin */ \
        PORT->PMCB |= (1 << 7);     /* Set ANI105(PB07) pin */ \
        PORT->PMCB |= (1 << 0);     /* Set ANI106(PB00) pin */ \
        PORT->PMCB |= (1 << 5);     /* Set ANI107(PB05) pin */ \
}while(0)
#define ADC2_PORT_SETTING() do{ \
        PORT->PMCA |= (1 << 6);     /* Set ANI200(PA06) pin */ \
        PORT->PMCA |= (1 << 7);     /* Set ANI201(PA07) pin */ \
        PORT->PMCA |= (1 << 8);     /* Set ANI202(PA08) pin */ \
        PORT->PMCA |= (1 << 9);     /* Set ANI203(PA09) pin */ \
        PORT->PMCA |= (1 <<10);     /* Set ANI204(PA10) pin */ \
        PORT->PMCA |= (1 <<13);     /* Set ANI205(PA13) pin */ \
        PORT->PMCA |= (1 <<14);     /* Set ANI206(PA14) pin */ \
        PORT->PMCA |= (1 <<15);     /* Set ANI207(PA15) pin */ \
        PORT->PMCB |= (1 << 9);     /* Set ANI208(PB09) pin */ \
        PORT->PMCB |= (1 <<12);     /* Set ANI209(PB12) pin */ \
        PORT->PMCB |= (1 <<11);     /* Set ANI210(PB11) pin */ \
        PORT->PMCB |= (1 <<10);     /* Set ANI211(PB10) pin */ \
        PORT->PMCB |= (1 << 1);     /* Set ANI212(PB01) pin */ \
        PORT->PMCB |= (1 << 2);     /* Set ANI213(PB02) pin */ \
        PORT->PMCB |= (1 << 3);     /* Set ANI214(PB03) pin */ \
        PORT->PMCB |= (1 << 4);     /* Set ANI215(PB04) pin */ \
}while(0)

/* ToDo: You can allocate the ADTRG0 to PB08, PC13 and PC15 pins */
#define ADTRG0_PORT_SETTING() do{ \
        PORT->PC13CFG = 0x04;	    /* allocate ADTRG0 to PC13 */ \
        PORT->PMC  |= (1 <<13);     /* PC13 is used as ADTRG0 input */ \
}while(0)

/* ToDo: You can allocate the ADTRG1 to PB05 and PD10 pins */
#define ADTRG1_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x04;	    /* allocate ADTRG1 to PD10 */ \
        PORT->PMD  |= (1 <<10);     /* PD10 is used as ADTRG1 input */ \
}while(0)

/* ToDo: You can allocate the ADTRG2 to PB04 and PD11 pins */
#define ADTRG2_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x04;	    /* allocate ADTRG2 to PD11 */ \
        PORT->PMD  |= (1 <<11);     /* PD11 is used as ADTRG2 input */ \
}while(0)

/* ToDo: You can allocate the ADST0 to PD09 and PE06 pins */
#define ADST0_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x04;	    /* allocate ADST0 to PD09 */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as ADST0 output */ \
        PORT->POMD &= ~(1 << 9);    /* PD09 is push-pull output mode */ \
        PORT->PCLRD =  (1 << 9);    /* PD09 output "L" */ \
}while(0)

/* ToDo: You can allocate the ADST1 to PD09 and PE06 pins */
#define ADST1_PORT_SETTING() do{ \
        PORT->PE06CFG = 0x04;	    /* allocate ADST1 to PE06 */ \
        PORT->PME  &= ~(1 << 6);    /* PE06 is used as ADST1 output */ \
        PORT->POME &= ~(1 << 6);    /* PE06 is push-pull output mode */ \
        PORT->PCLRE =  (1 << 6);    /* PE06 output "L" */ \
}while(0)

/* ToDo: You can allocate the ADST2 to PE02 pins */
#define ADST2_PORT_SETTING() do{ \
        PORT->PE02CFG = 0x04;	    /* allocate ADST2 to PE02 */ \
        PORT->PME  &= ~(1 << 2);    /* PE02 is used as ADST2 output */ \
        PORT->POME &= ~(1 << 2);    /* PE02 is push-pull output mode */ \
        PORT->PCLRE =  (1 << 2);    /* PE02 output "L" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        DAC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief DAC Port Setting (Alternate to fixed ports)
  */

#define DAC0_PORT_SETTING() do{ \
        PORT->PMCB |= (1 << 2);   /* Set ANO0(PB02) pin */ \
}while(0)

#define DAC1_PORT_SETTING() do{ \
        PORT->PMCB |= (1 << 3);   /* Set ANO1(PB03) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        CMP                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CMP Port Setting (Alternate to fixed ports)
  */

/* ToDo: You can allocate the VCOUT0 to PB02 pin */
#define VCOUT0_PORT_SETTING() do { \
        PORT->PB02CFG = 0x04;	    /* allocate VCOUT0 to PB02 */ \
        PORT->PMB  &= ~(1 << 2);    /* PB02 is used as VCOUT0 output */ \
        PORT->POMB &= ~(1 << 2);    /* PB02 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 2);    /* PB02 output "L" */ \
}while(0)

/* ToDo: You can allocate the VCOUT1 to PB03 pin */
#define VCOUT1_PORT_SETTING() do { \
        PORT->PB03CFG = 0x04;	    /* allocate VCOUT1 to PB03 */ \
        PORT->PMB  &= ~(1 << 3);    /* PB03 is used as VCOUT1 output */ \
        PORT->POMB &= ~(1 << 3);    /* PB03 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 3);    /* PB03 output "L" */ \
}while(0)

/* ToDo: You can allocate the VCOUT2 to PB04 pin */
#define VCOUT2_PORT_SETTING() do { \
        PORT->PB04CFG = 0x04;	    /* allocate VCOUT2 to PB04 */ \
        PORT->PMB  &= ~(1 << 4);    /* PB04 is used as VCOUT2 output */ \
        PORT->POMB &= ~(1 << 4);    /* PB04 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 4);    /* PB04 output "L" */ \
}while(0)

/* ToDo: You can allocate the VCOUT3 to PB01 pin */
#define VCOUT3_PORT_SETTING() do { \
        PORT->PB01CFG = 0x04;	    /* allocate VCOUT3 to PB01 */ \
        PORT->PMB  &= ~(1 << 1);    /* PB01 is used as VCOUT3 output */ \
        PORT->POMB &= ~(1 << 1);    /* PB01 is push-pull output mode */ \
        PORT->PCLRB =  (1 << 1);    /* PB01 output "L" */ \
}while(0)

/* ToDo: Please comment out the VCIN0x/VREFx setting if these pins UNUSED */
#define CMP0_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 0);  /* Set VCIN0(PA00) pin */ \
        PORT->PMCB  |= (1 << 8);  /* Set VREF0(PB08) pin */ \
        PORT->PMCB  |= (1 << 5);  /* Set VREF1(PB05) pin */ \
        VCOUT0_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT0 signal to port */ \
}while(0)

/* ToDo: Please comment out the VCIN1x/VREFx setting if these pins UNUSED */
#define CMP1_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 3);  /* Set VCIN10(PA03) pin */ \
        PORT->PMCA  |= (1 << 5);  /* Set VCIN12(PA05) pin */ \
        PORT->PMCB  |= (1 << 8);  /* Set VREF0(PB08) pin */ \
        PORT->PMCB  |= (1 << 5);  /* Set VREF1(PB05) pin */ \
        VCOUT1_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT1 signal to port */ \
}while(0)

/* ToDo: Please comment out the VCIN2x/VREFx setting if these pins UNUSED */
#define CMP2_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 4);  /* Set VCIN20(PA04) pin */ \
        PORT->PMCA  |= (1 << 0);  /* Set VCIN22(PA00) pin */ \
        PORT->PMCB  |= (1 << 8);  /* Set VREF0(PB08) pin */ \
        PORT->PMCB  |= (1 << 5);  /* Set VREF1(PB05) pin */ \
        VCOUT2_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT2 signal to port */ \
}while(0)

/* ToDo: Please comment out the VCIN3x/VREFx setting if these pins UNUSED */
#define CMP3_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 5);  /* Set VCIN30(PA05) pin */ \
        PORT->PMCA  |= (1 << 3);  /* Set VCIN32(PA03) pin */ \
        PORT->PMCB  |= (1 << 8);  /* Set VREF0(PB08) pin */ \
        PORT->PMCB  |= (1 << 5);  /* Set VREF1(PB05) pin */ \
        VCOUT3_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT3 signal to port */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        PGA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief PGA Port Setting (Alternate to fixed ports)
  */

#define PGA00IN_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 0);  /* PGA00IN input from PA00 */ \
}while(0)

#define PGA00GND_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 1);  /* PGA00GND input from PA01 */ \
}while(0)

#define PGA10IN_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 3);  /* PGA10IN input from PA03 */ \
}while(0)

#define PGA10GND_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 2);  /* PGA10GND input from PA02 */ \
}while(0)

#define PGA11IN_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 4);  /* PGA11IN input from PA04 */ \
}while(0)

#define PGA11GND_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 7);  /* PGA11GND input from PA07 */ \
}while(0)

#define PGA12IN_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 5);  /* PGA12IN input from PA05 */ \
}while(0)

#define PGA12GND_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 6);  /* PGA12GND input from PA06 */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI0                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART0 Port Setting
  */

/* ToDo: You can allocate the TXD0 to PD06 pin */
#define TXD0_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x00;	    /* allocate TXD0 to PD06 */ \
        PORT->PMD  &= ~(1 << 6);    /* PD06 is used as TXD0 output */ \
        PORT->POMD &= ~(1 << 6);    /* PD06 is push-pull output mode */ \
        PORT->PSETD =  (1 << 6);    /* PD06 output "H" */ \
}while(0)

/* ToDo: You can allocate the RXD0 to PD08 pin */
#define RXD0_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x00;	    /* allocate RXD0 to PD08 */ \
        PORT->PMD  |=  (1 << 8);    /* PD06 is used as RXD0 input */ \
}while(0)

/**
  * @brief SPI00 Port Setting
  */
//#define SPI00_SLAVE
#define SPI00_MASTER

#ifdef SPI00_MASTER
/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	    /* allocate SS00 to PD09 */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as SS00 output */ \
        PORT->POMD &= ~(1 << 9);    /* PD09 is push-pull output mode */ \
        PORT->PSETD =  (1 << 9);    /* PD09 output "H" */ \
}while(0)
#else
/* ToDo: You can allocate the SS00 to PD09 and PE06 pins */
#define SS00_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x05;	    /* allocate SS00 to PD09 */ \
        PORT->PMD  |=  (1 << 9);    /* PD09 is used as SS00 input */ \
}while(0)
#endif

#define SS00_PORT_SET() do{ \
        PORT->PSETD =  (1 << 9);     /* PD09 output "high" level */ \
}while(0)

#define SS00_PORT_CLR() do{ \
        PORT->PCLRD =  (1 << 9);     /* PD09 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK00 to PD07 pin */
#define SCLKI00_PORT_SETTING() do{ \
        PORT->PD07CFG = 0x00;	      /* allocate SCLK00 to PD07 */ \
        PORT->PMD   |=  (1 << 7);     /* PD07 is used as SCLK00 input */ \
}while(0)

/* ToDo: You can allocate the SCLK00 to PD07 pin */
#define SCLKO00_PORT_SETTING() do{ \
        PORT->PD07CFG = 0x00;	      /* allocate SCLK00 to PD07 */ \
        PORT->PMD  &= ~(1 << 7);      /* PD07 is used as SCLK00 output */ \
        PORT->POMD &= ~(1 << 7);      /* PD07 is push-pull output mode */ \
        PORT->PSETD =  (1 << 7);      /* PD07 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO00 to PD06 pin */
#define SDO00_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x00;	      /* allocate SDO00 to PD06 */ \
        PORT->PMD  &= ~(1 << 6);      /* PD06 is used as SCLK00 output */ \
        PORT->POMD &= ~(1 << 6);      /* PD06 is push-pull output mode */ \
        PORT->PSETD =  (1 << 6);      /* PD06 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI00 to PD08 pin */
#define SDI00_PORT_SETTING() do{ \
        PORT->PD08CFG = 0x00;	      /* allocate SDI00 to PD08 */ \
        PORT->PMD  |=  (1 << 8);      /* PD08 is used as SDI00 input */ \
}while(0)

/**
  * @brief IIC00 Port Setting
  */

/* ToDo: You can allocate the SCL00 to PD07 pin (Alternative to fixed port) */
#define SCL00_PORT_SETTING() do{ \
        PORT->PD07CFG = 0x00;	     /* allocate SCL00 to PD07 */ \
        PORT->PMD   &= ~(1 << 7);    /* PD07 is used as SCL00 output */ \
        PORT->POMD  |=  (1 << 7);    /* PD07 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 7);    /* PD07 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDA00 to PD08 pin (Alternative to fixed port) */
#define SDA00_PORT_SETTING() do{ \
        PORT->PD08CFG = 0x00;	     /* allocate SDA00 to PD08 */ \
        PORT->PMD   &= ~(1 << 8);    /* PD08 is used as SDA00 inout */ \
        PORT->POMD  |=  (1 << 8);    /* PD08 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 8);    /* PD08 output "H" */ \
}while(0)

/**
  * @brief SPI01 Port Setting (Alternative to fixed port)
  */
//#define SPI01_SLAVE
#define SPI01_MASTER

#ifdef SPI01_MASTER
/* ToDo: You can allocate the SS10 to any desired pins */
#define SS01_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	    /* allocate SS01 to PD09 */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as SS01 output */ \
}while(0)
#else
#define SS01_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	    /* allocate SS01 to PD09 */ \
        PORT->PMD  |=  (1 << 9);    /* PD09 is used as SS01 input */ \
}while(0)
#endif

#define SS01_PORT_SET() do{ \
        PORT->PSETD =  (1 << 9);     /* PD09 output "high" level */ \
}while(0)

#define SS01_PORT_CLR() do{ \
        PORT->PCLRD =  (1 << 9);     /* PD09 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK01 to PD08 pin */
#define SCLKI01_PORT_SETTING() do{ \
        PORT->PD08CFG = 0x06;	      /* allocate SCLK01 to PD08 */ \
        PORT->PMD   |=  (1 << 8);     /* PD08 is used as SCLK01 input */ \
}while(0)

/* ToDo: You can allocate the SCLK01 to PD08 pin */
#define SCLKO01_PORT_SETTING() do{ \
        PORT->PD08CFG = 0x06;	      /* allocate SCLK01 to PD08 */ \
        PORT->PMD  &= ~(1 << 8);      /* PD08 is used as SCLK01 output */ \
        PORT->POMD &= ~(1 << 8);      /* PD08 is push-pull output mode */ \
        PORT->PSETD =  (1 << 8);      /* PD08 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO01 to PD07 pin */
#define SDO01_PORT_SETTING() do{ \
        PORT->PD07CFG = 0x06;	      /* allocate SDO01 to PD07 */ \
        PORT->PMD  &= ~(1 << 7);      /* PD07 is used as SCLK01 output */ \
        PORT->POMD &= ~(1 << 7);      /* PD07 is push-pull output mode */ \
        PORT->PSETD =  (1 << 7);      /* PD07 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI01 to PD06 pin */
#define SDI01_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x06;	      /* allocate SDI01 to PD06 */ \
        PORT->PMD  |=  (1 << 6);      /* PD06 is used as SDI01 input */ \
}while(0)

/**
  * @brief IIC01 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL01 to PD08 pin */
#define SCL01_PORT_SETTING() do{ \
        PORT->PD08CFG = 0x06;	     /* allocate SCL01 to PD08 */ \
        PORT->PMD   &= ~(1 << 8);    /* PD08 is used as SCL01 output */ \
        PORT->POMD  |=  (1 << 8);    /* PD08 is N-ch open-drain output mode */ \
        PORT->PSETD |=  (1 << 8);    /* PD08 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA01 to PD06 pin */
#define SDA01_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x06;	     /* allocate SDA01 to PD06 */ \
        PORT->PMD   &= ~(1 << 6);    /* PD06 is used as SDA01 inout */ \
        PORT->POMD  |=  (1 << 6);    /* PD06 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 6);    /* PD06 output high level */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI1                                       ================ */
/* ================================================================================================================== */
/**
  * @brief UART1 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the TXD1 to PD04 and PE00 pin */
#define TXD1_PORT_SETTING() do{ \
        PORT->PD04CFG = 0x05;	    /* allocate TXD1 to PD04 */ \
        PORT->PMD  &= ~(1 << 4);    /* PD04 is used as TXD1 output */ \
        PORT->POMD &= ~(1 << 4);    /* PD04 is push-pull output mode */ \
        PORT->PSETD =  (1 << 4);    /* PD04 output "H" */ \
}while(0)

/* ToDo: You can allocate the RXD1 to PD05 and PE12 pin */
#define RXD1_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x05;	    /* allocate RXD1 to PD05 */ \
        PORT->PMD  |=  (1 << 5);    /* PD05 is used as RXD1 input */ \
}while(0)

/**
  * @brief SPI10 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS10 to any desired pins */

//#define SPI10_SLAVE
#define SPI10_MASTER

#ifdef SPI10_MASTER
/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SETTING() do{ \
        PORT->PD03CFG = 0x00;	    /* allocate SS10 to PD03 */ \
        PORT->PMD  &= ~(1 << 3);    /* PD03 is used as SS10 output */ \
        PORT->POMD &= ~(1 << 3);    /* PD03 is push-pull output mode */ \
        PORT->PSETD =  (1 << 3);    /* PD03 output "H" */ \
}while(0)
#else
/* ToDo: You can allocate the SS10 to PD03 and PE13 pins */
#define SS10_PORT_SETTING() do{ \
        PORT->PD03CFG = 0x05;	    /* allocate SS10 to PD03 */ \
        PORT->PMD  |=  (1 << 3);    /* PD03 is used as SS10 input */ \
}while(0)
#endif

#define SS10_PORT_SET() do{ \
        PORT->PSETD =  (1 << 3);     /* PD03 output "high" level */ \
}while(0)

#define SS10_PORT_CLR() do{ \
        PORT->PCLRD =  (1 << 3);     /* PD03 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK10 to PD12 and PD13 pin */
#define SCLKI10_PORT_SETTING() do{ \
        PORT->PD13CFG = 0x05;	      /* allocate SCLK10 to PD13 */ \
        PORT->PMD   |=  (1 <<13);     /* PD13 is used as SCLK10 input */ \
}while(0)

/* ToDo: You can allocate the SCLK10 to PD12 and PD13 pin */
#define SCLKO10_PORT_SETTING() do{ \
        PORT->PD13CFG = 0x05;	      /* allocate SCLK10 to PD13 */ \
        PORT->PMD  &= ~(1 <<13);      /* PD13 is used as SCLK10 output */ \
        PORT->POMD &= ~(1 <<13);      /* PD13 is push-pull output mode */ \
        PORT->PSETD =  (1 <<13);      /* PD13 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO10 to PD04 and PE00 pin */
#define SDO10_PORT_SETTING() do{ \
        PORT->PD04CFG = 0x05;	      /* allocate SDO10 to PD04 */ \
        PORT->PMD  &= ~(1 << 4);      /* PD04 is used as SDO10 output */ \
        PORT->POMD &= ~(1 << 4);      /* PD04 is push-pull output mode */ \
        PORT->PSETD =  (1 << 4);      /* PD04 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI10 to PD05 and PE12 pin */
#define SDI10_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x05;	      /* allocate SDI10 to PD05 */ \
        PORT->PMD  |=  (1 << 5);      /* PD05 is used as SDI10 input */ \
}while(0)

/**
  * @brief IIC10 Port Setting
  */

/* ToDo: You can allocate the SCL10 to PD12 and PD13 pin */
#define SCL10_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x05;	     /* allocate SCL10 to PD12 */ \
        PORT->PMD   &= ~(1 <<12);    /* PD12 is used as SCL10 output */ \
        PORT->POMD  |=  (1 <<12);    /* PD12 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 <<12);    /* PD12 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA10 to PD05 and PE12 pin */
#define SDA10_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x05;	     /* allocate SDA10 to PD05 */ \
        PORT->PMD   &= ~(1 << 5);    /* PD05 is used as SDA10 inout */ \
        PORT->POMD  |=  (1 << 5);    /* PD05 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 5);    /* PD05 output high level */ \
}while(0)

/**
  * @brief SPI11 Port Setting
  */

//#define SPI11_SLAVE
#define SPI11_MASTER

#ifdef SPI11_MASTER
/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x00;	    /* allocate SS11 to PD06 */ \
        PORT->PMD  &= ~(1 << 6);    /* PD06 is used as SS11 output */ \
}while(0)
#else
/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() do{ \
        PORT->PD06CFG = 0x00;	    /* allocate SS11 to PD06 */ \
        PORT->PMD  |=  (1 << 6);    /* PD06 is used as SS11 input */ \
}while(0)
#endif

#define SS11_PORT_SET() do{ \
        PORT->PSETD =  (1 << 6);     /* PD06 output "high" level */ \
}while(0)

#define SS11_PORT_CLR() do{ \
        PORT->PCLRD =  (1 << 6);     /* PD06 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK11 to PD05 and PE12 pin */
#define SCLKI11_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x06;	      /* allocate SCLK11 to PD05 */ \
        PORT->PMD   |=  (1 << 5);     /* PD05 is used as SCLK11 input */ \
}while(0)

/* ToDo: You can allocate the SCLK11 to PD05 and PE12 pin */
#define SCLKO11_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x06;	      /* allocate SCLK11 to PD05 */ \
        PORT->PMD  &= ~(1 << 5);      /* PD05 is used as SCLK11 output */ \
        PORT->POMD &= ~(1 << 5);      /* PD05 is push-pull output mode */ \
        PORT->PSETD =  (1 << 5);      /* PD05 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO11 to PD03 and PD06 pin */
#define SDO11_PORT_SETTING() do{ \
        PORT->PD03CFG = 0x06;	      /* allocate SDO11 to PD03 */ \
        PORT->PMD  &= ~(1 << 3);      /* PD03 is used as SCLK11 output */ \
        PORT->POMD &= ~(1 << 3);      /* PD03 is push-pull output mode */ \
        PORT->PSETD =  (1 << 3);      /* PD03 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI11 to PD04 and PE00 pin */
#define SDI11_PORT_SETTING() do{ \
        PORT->PD04CFG = 0x06;	      /* allocate SDI11 to PD04 */ \
        PORT->PMD  |=  (1 << 4);      /* PD04 is used as SDI11 input */ \
}while(0)

/**
  * @brief IIC11 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL11 to PD05 and PE12 pin */
#define SCL11_PORT_SETTING() do{ \
        PORT->PD05CFG = 0x06;	     /* allocate SCL11 to PD05 */ \
        PORT->PMD   &= ~(1 << 5);    /* PD05 is used as SCL11 output */ \
        PORT->POMD  |=  (1 << 5);    /* PD05 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 5);    /* PD05 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA11 to PD04 and PE00 pin */
#define SDA11_PORT_SETTING() do{ \
        PORT->PD04CFG = 0x06;	     /* allocate SDA11 to PD04 */ \
        PORT->PMD   &= ~(1 << 4);    /* PD04 is used as SDA11 inout */ \
        PORT->POMD  |=  (1 << 4);    /* PD04 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 4);    /* PD04 output high level */ \
}while(0)


/* ================================================================================================================== */
/* ================                                       SCI2                                       ================ */
/* ================================================================================================================== */
/**
  * @brief UART2 Port Setting
  */

/* ToDo: You can allocate the TXD2 to PD01 and PD11 pin */
#define TXD2_PORT_SETTING() do{ \
        PORT->PD01CFG = 0x05;	    /* allocate TXD2 to PD01 */ \
        PORT->PMD  &= ~(1 << 1);    /* PD01 is used as TXD2 output */ \
        PORT->POMD &= ~(1 << 1);    /* PD01 is push-pull output mode */ \
        PORT->PSETD =  (1 << 1);    /* PD01 output "H" */ \
}while(0)

/* ToDo: You can allocate the RXD2 to PD00 and PD10 pin */
#define RXD2_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x05;	    /* allocate RXD2 to PD00 */ \
        PORT->PMD  |=  (1 << 0);    /* PD00 is used as RXD2 input */ \
}while(0)

/**
  * @brief SPI20 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS20 to any desired pins */

//#define SPI20_SLAVE
#define SPI20_MASTER

#ifdef SPI20_MASTER
/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SETTING() do{ \
        PORT->PC14CFG = 0x00;	    /* allocate SS20 to PC14 */ \
        PORT->PMC  &= ~(1 << 14);    /* PC14 is used as SS20 output */ \
        PORT->POMC &= ~(1 << 14);    /* PC14 is push-pull output mode */ \
        PORT->PSETC =  (1 << 14);    /* PC14 output "H" */ \
}while(0)
#else
/* ToDo: You can allocate the SS20 to PC14 pins */
#define SS20_PORT_SETTING() do{ \
        PORT->PC14CFG = 0x00;	    /* allocate SS20 to PC14 */ \
        PORT->PMC  |=  (1 << 14);    /* PC14 is used as SS20 input */ \
}while(0)
#endif

#define SS20_PORT_SET() do{ \
        PORT->PSETC =  (1 << 14);     /* PC14 output "high" level */ \
}while(0)

#define SS20_PORT_CLR() do{ \
        PORT->PCLRC =  (1 << 14);     /* PC14 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK20 to PC15 and PD02 pin */
#define SCLKI20_PORT_SETTING() do{ \
        PORT->PD02CFG = 0x05;	      /* allocate SCLK20 to PD02 */ \
        PORT->PMD   |=  (1 << 2);     /* PD02 is used as SCLK20 input */ \
}while(0)

/* ToDo: You can allocate the SCLK20 to PC15 and PD02 pin */
#define SCLKO20_PORT_SETTING() do{ \
        PORT->PD02CFG = 0x05;	      /* allocate SCLK20 to PD02 */ \
        PORT->PMD  &= ~(1 << 2);      /* PD02 is used as SCLK20 output */ \
        PORT->POMD &= ~(1 << 2);      /* PD02 is push-pull output mode */ \
        PORT->PSETD =  (1 << 2);      /* PD02 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO20 to PD01 and PD11 pin */
#define SDO20_PORT_SETTING() do{ \
        PORT->PD01CFG = 0x05;	      /* allocate SDO20 to PD01 */ \
        PORT->PMD  &= ~(1 << 1);      /* PD01 is used as SDO20 output */ \
        PORT->POMD &= ~(1 << 1);      /* PD01 is push-pull output mode */ \
        PORT->PSETD =  (1 << 1);      /* PD01 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI20 to PD00 and PD10 pin */
#define SDI20_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x05;	      /* allocate SDI20 to PD00 */ \
        PORT->PMD  |=  (1 << 0);      /* PD00 is used as SDI20 input */ \
}while(0)

/**
  * @brief IIC20 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL20 to PC15 and PD02 pin */
#define SCL20_PORT_SETTING() do{ \
        PORT->PD02CFG = 0x05;	     /* allocate SCL20 to PD02 */ \
        PORT->PMD   &= ~(1 << 2);    /* PD02 is used as SCL20 output */ \
        PORT->POMD  |=  (1 << 2);    /* PD02 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 2);    /* PD02 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA20 to PD00 and PD10 pin */
#define SDA20_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x05;	     /* allocate SDA20 to PD00 */ \
        PORT->PMD   &= ~(1 << 0);    /* PD00 is used as SDA20 inout */ \
        PORT->POMD  |=  (1 << 0);    /* PD00 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 0);    /* PD00 output high level */ \
}while(0)

/**
  * @brief SPI21 Port Setting (Alternative to fixed port)
  */

//#define SPI21_SLAVE
#define SPI21_MASTER

#ifdef SPI21_MASTER
/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SETTING() do{ \
        PORT->PB12CFG = 0x00;	     /* allocate SS21 to PB12 */ \
        PORT->PMCB &= ~(1 <<12);     /* PB12 digital function  */ \
        PORT->PMB  &= ~(1 <<12);     /* PB12 is used as SS21 output */ \
}while(0)
#else
/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SETTING() do{ \
        PORT->PB12CFG = 0x00;	     /* allocate SS21 to PB12 */ \
        PORT->PMCB &= ~(1 <<12);     /* PB12 digital function  */ \
        PORT->PMB  |=  (1 <<12);     /* PB12 is used as SS21 input */ \
}while(0)
#endif

#define SS21_PORT_SET() do{ \
        PORT->PSETB =  (1 <<12);     /* PB12 output "high" level */ \
}while(0)

#define SS21_PORT_CLR() do{ \
        PORT->PCLRB =  (1 <<12);     /* PB12 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK21 to PB15 and PD00 pin */
#define SCLKI21_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x06;	      /* allocate SCLK21 to PB15 */ \
        PORT->PMCB &= ~(1 <<15);      /* PB15 digital function  */ \
        PORT->PMB  |=  (1 <<15);      /* PB15 is used as SCLK21 input */ \
}while(0)

/* ToDo: You can allocate the SCLK21 to PB15 and PD00 pin */
#define SCLKO21_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x06;	      /* allocate SCLK21 to PB15 */ \
        PORT->PMCB &= ~(1 <<15);      /* PB15 digital function  */ \
        PORT->PMB  &= ~(1 <<15);      /* PB15 is used as SCLK21 output */ \
        PORT->POMB &= ~(1 <<15);      /* PB15 is push-pull output mode */ \
        PORT->PSETB =  (1 <<15);      /* PB15 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO21 to PB13 and PD02 pin */
#define SDO21_PORT_SETTING() do{ \
        PORT->PB13CFG = 0x06;	      /* allocate SDO21 to PB13 */ \
        PORT->PMCB &= ~(1 <<13);      /* PB13 digital function  */ \
        PORT->PMB  &= ~(1 <<13);      /* PB13 is used as SCLK21 output */ \
        PORT->POMB &= ~(1 <<13);      /* PB13 is push-pull output mode */ \
        PORT->PSETB =  (1 <<13);      /* PB13 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI21 to PB14 and PD01 pin */
#define SDI21_PORT_SETTING() do{ \
        PORT->PB14CFG = 0x06;	      /* allocate SDI21 to PB14 */ \
        PORT->PMCB |=  (1 <<14);      /* PB14 digital function */ \
        PORT->PMB  |=  (1 <<14);      /* PB14 is used as SDI21 input */ \
}while(0)

/**
  * @brief IIC21 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL21 to PB15 and PD00 pin */
#define SCL21_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x06;	     /* allocate SCL21 to PB15 */ \
        PORT->PMCB  &= ~(1 <<15);    /* PB15 digital function */ \
        PORT->PMB   &= ~(1 <<15);    /* PB15 is used as SCL21 output */ \
        PORT->POMB  |=  (1 <<15);    /* PB15 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<15);    /* PB15 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA21 to PB14 and PD01 pin */
#define SDA21_PORT_SETTING() do{ \
        PORT->PB14CFG = 0x06;	     /* allocate SDA21 to PB14 */ \
        PORT->PMCB  &= ~(1 <<14);    /* PB14 digital function */ \
        PORT->PMB   &= ~(1 <<14);    /* PB14 is used as SDA21 inout */ \
        PORT->POMB  |=  (1 <<14);    /* PB14 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<14);    /* PB14 output high level */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI3                                       ================ */
/* ================================================================================================================== */
/* 
 */

/**
  * @brief UART3 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the TXD3 to PB14 pin (Alternative to fixed port) */
#define TXD3_PORT_SETTING() do{ \
        PORT->PB14CFG = 0x05;	     /* allocate TXD3 to PB14 */ \
        PORT->PMCB &= ~(1 <<14);     /* PB14 digital function */ \
        PORT->PMB  &= ~(1 <<14);     /* PB14 is used as TXD3 output */ \
        PORT->POMB &= ~(1 <<14);     /* PB14 is push-pull output mode */ \
        PORT->PSETB =  (1 <<14);     /* PB14 output "H" */ \
}while(0)

/* ToDo: You can allocate the RXD3 to PB15 pin (Alternative to fixed port) */
#define RXD3_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x05;	     /* allocate RXD3 to PB15 */ \
        PORT->PMCB  &= ~(1 <<15);    /* PB15 digital function */ \
        PORT->PMB   |=  (1 <<15);    /* PB15 is used as RXD3 input */ \
}while(0)

/**
  * @brief SPI30 Port Setting (Alternative to fixed port)
  */

//#define SPI30_SLAVE
#define SPI30_MASTER

#ifdef SPI30_MASTER
/* ToDo: You can allocate the SS30 to any desired pins */
#define SS30_PORT_SETTING() do{ \
        PORT->PB12CFG = 0x00;	     /* allocate SS30 to PB12 */ \
        PORT->PMCB &= ~(1 <<12);     /* PB12 digital function */ \
        PORT->PMB  &= ~(1 <<12);     /* PB12 is used as SS30 output */ \
        PORT->POMB &= ~(1 <<12);     /* PB12 is push-pull output mode */ \
        PORT->PSETB =  (1 <<12);     /* PB12 output "H" */ \
}while(0)
#else
/* ToDo: You can allocate the SS30 to PB12 pins */
#define SS30_PORT_SETTING() do{ \
        PORT->PB12CFG = 0x00;	     /* allocate SS30 to PB12 */ \
        PORT->PMCB &= ~(1 <<12);     /* PB12 digital function */ \
        PORT->PMB  |=  (1 <<12);     /* PB12 is used as SS30 input */ \
}while(0)
#endif

#define SS30_PORT_SET() do{ \
        PORT->PSETB =  (1 <<12);     /* PB12 output "high" level */ \
}while(0)

#define SS30_PORT_CLR() do{ \
        PORT->PCLRB =  (1 <<12);     /* PB12 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK30 to PB13 pin (Alternative to fixed port) */
#define SCLKI30_PORT_SETTING() do{ \
        PORT->PB13CFG = 0x00;	     /* allocate SCLK30 to PB13 */ \
        PORT->PMCB &= ~(1 <<13);     /* PB13 digital function */ \
        PORT->PMB  |=  (1 <<13);     /* PB13 is used as SCLK30 input */ \
}while(0)

/* ToDo: You can allocate the SCLK30 to PB13 pin (Alternative to fixed port) */
#define SCLKO30_PORT_SETTING() do{ \
        PORT->PB13CFG = 0x00;	     /* allocate SCLK30 to PB13 */ \
        PORT->PMCB &= ~(1 <<13);     /* PB13 digital function */ \
        PORT->PMB  &= ~(1 <<13);     /* PB13 is used as SCLK30 output */ \
        PORT->POMB &= ~(1 <<13);     /* PB13 is push-pull output mode */ \
        PORT->PSETB =  (1 <<13);     /* PB13 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO30 to PB14 pin (Alternative to fixed port) */
#define SDO30_PORT_SETTING() do{ \
        PORT->PB14CFG = 0x00;	     /* allocate SDO30 to PB14 */ \
        PORT->PMCB &= ~(1 <<14);     /* PB14 digital function */ \
        PORT->PMB  &= ~(1 <<14);     /* PB14 is used as SDO30 output */ \
        PORT->POMB &= ~(1 <<14);     /* PB14 is push-pull output mode */ \
        PORT->PSETB =  (1 <<14);     /* PB14 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI30 to PB15 pin (Alternative to fixed port) */
#define SDI30_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x00;	      /* allocate SDI30 to PB15 */ \
        PORT->PMCB &= ~(1 <<15);      /* PB15 digital function */ \
        PORT->PMB  |=  (1 <<15);      /* PB15 is used as SDI30 input */ \
}while(0)

/**
  * @brief IIC30 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL30 to PB13 pin (Alternative to fixed port) */
#define SCL30_PORT_SETTING() do{ \
        PORT->PB13CFG = 0x00;	     /* allocate SCL30 to PB13 */ \
        PORT->PMCB  &= ~(1 <<13);    /* PB13 digital function */ \
        PORT->PMB   &= ~(1 <<13);    /* PB13 is used as SCL30 output */ \
        PORT->POMB  |=  (1 <<13);    /* PB13 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<13);    /* PB13 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDA30 to PB15 pin (Alternative to fixed port) */
#define SDA30_PORT_SETTING() do{ \
        PORT->PB15CFG = 0x00;	     /* allocate SDA30 to PB15 */ \
        PORT->PMCB  &= ~(1 <<15);    /* PB15 digital function */ \
        PORT->PMB   &= ~(1 <<15);    /* PB15 is used as SDA30 inout */ \
        PORT->POMB  |=  (1 <<15);    /* PB15 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<15);    /* PB15 output "H" */ \
}while(0)

/**
  * @brief SPI31 Port Setting (Alternative to fixed port)
  */

//#define SPI31_SLAVE
#define SPI31_MASTER

#ifdef SPI31_MASTER
/* ToDo: You can allocate the SS31 to any desired pins */
#define SS31_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x00;	     /* allocate SS31 to PD12 */ \
        PORT->PMD  &= ~(1 <<12);     /* PD12 is used as SS31 output */ \
}while(0)
#else
/* ToDo: You can allocate the SS31 to any desired pins */
#define SS31_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x00;	     /* allocate SS31 to PD12 */ \
        PORT->PMD  |=  (1 <<12);     /* PD12 is used as SS31 input */ \
}while(0)
#endif

#define SS31_PORT_SET() do{ \
        PORT->PSETD =  (1 <<12);     /* PD12 output "high" level */ \
}while(0)

#define SS31_PORT_CLR() do{ \
        PORT->PCLRD =  (1 <<12);     /* PD12 output "low" level */ \
}while(0)

/* ToDo: You can allocate the SCLK21 to PD10 pin (Alternative to fixed port) */
#define SCLKI31_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x00;	      /* allocate SCLK21 to PD10 */ \
        PORT->PMD  |=  (1 <<10);      /* PD10 is used as SCLK21 input */ \
}while(0)

/* ToDo: You can allocate the SCLK21 to PD10 pin (Alternative to fixed port) */
#define SCLKO31_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x00;	      /* allocate SCLK21 to PD10 */ \
        PORT->PMD  &= ~(1 <<10);      /* PD10 is used as SCLK21 output */ \
        PORT->POMD &= ~(1 <<10);      /* PD10 is push-pull output mode */ \
        PORT->PSETD =  (1 <<10);      /* PD10 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDO31 to PC15 pin (Alternative to fixed port) */
#define SDO31_PORT_SETTING() do{ \
        PORT->PC15CFG = 0x00;	      /* allocate SDO31 to PC15 */ \
        PORT->PMC  &= ~(1 <<15);      /* PC15 is used as SCLK21 output */ \
        PORT->POMC &= ~(1 <<15);      /* PC15 is push-pull output mode */ \
        PORT->PSETC =  (1 <<15);      /* PC15 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDI31 to PD11 pin (Alternative to fixed port) */
#define SDI31_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x00;	      /* allocate SDI31 to PD11 */ \
        PORT->PMD  |=  (1 <<11);      /* PD11 is used as SDI31 input */ \
}while(0)

/**
  * @brief IIC31 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCL31 to PD10 pin (Alternative to fixed port) */
#define SCL31_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x06;	     /* allocate SCL31 to PD10 */ \
        PORT->PMD   &= ~(1 <<10);    /* PD10 is used as SCL31 output */ \
        PORT->POMD  |=  (1 <<10);    /* PD10 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 <<10);    /* PD10 output high level */ \
}while(0)

/* ToDo: You can allocate the SDA31 to PD11 pin (Alternative to fixed port) */
#define SDA31_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x06;	     /* allocate SDA31 to PD11 */ \
        PORT->PMD   &= ~(1 <<11);    /* PD11 is used as SDA31 inout */ \
        PORT->POMD  |=  (1 <<11);    /* PD11 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 <<11);    /* PD11 output high level */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       IICA0                                      ================ */
/* ================================================================================================================== */

/**
  * @brief IICA0 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCLA0 to PD00 pin (Alternative to fixed port) */
#define SCLA0_PORT_SETTING() do{ \
        PORT->PD00CFG = 0x00;	     /* allocate SCLA0 to PD00 */ \
        PORT->PMD   &= ~(1 << 0);    /* PD00 is used as SCLA0 output */ \
        PORT->POMD  |=  (1 << 0);    /* PD00 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 0);    /* PD00 output high level */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to PD01 pin (Alternative to fixed port) */
#define SDAA0_PORT_SETTING() do{ \
        PORT->PD01CFG = 0x00;	     /* allocate SDAA0 to PD01 */ \
        PORT->PMD   &= ~(1 << 1);    /* PD01 is used as SDAA0 inout */ \
        PORT->POMD  |=  (1 << 1);    /* PD01 is N-ch open-drain output mode */ \
        PORT->PSETD  =  (1 << 1);    /* PD01 output high level */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       IICA1                                      ================ */
/* ================================================================================================================== */

/**
  * @brief IICA1 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SCLA1 to PB11 pin (Alternative to fixed port) */
#define SCLA1_PORT_SETTING() do{ \
        PORT->PB11CFG = 0x00;	     /* allocate SCLA1 to PB11 */ \
        PORT->PMCB  &= ~(1 <<11);    /* PB11 digital function */ \
        PORT->PMB   &= ~(1 <<11);    /* PB11 is used as SCLA1 output */ \
        PORT->POMB  |=  (1 <<11);    /* PB11 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<11);    /* PB11 output "H" */ \
}while(0)

/* ToDo: You can allocate the SDAA1 to PD10 pin (Alternative to fixed port) */
#define SDAA1_PORT_SETTING() do{ \
        PORT->PB10CFG = 0x00;	     /* allocate SDAA1 to PB10 */ \
        PORT->PMCB  &= ~(1 <<10);    /* PB10 digital function */ \
        PORT->PMB   &= ~(1 <<10);    /* PB10 is used as SDAA1 inout */ \
        PORT->POMB  |=  (1 <<10);    /* PB10 is N-ch open-drain output mode */ \
        PORT->PSETB  =  (1 <<10);    /* PB10 output "H" */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       CAN0                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CAN0 Port Setting (Alternative to 2 group ports)
  */

/* ToDo: You can allocate the CTXD0 to PC12 pin (Alternative to fixed port) */
#define CTXD0_PORT_SETTING() do{ \
        PORT->PC12CFG = 0x00;	     /* allocate CTXD0 to PC12 */ \
        PORT->PMC  &= ~(1 <<12);     /* PC12 is used as TXD3 output */ \
        PORT->POMC &= ~(1 <<12);     /* PC12 is push-pull output mode */ \
        PORT->PSETC =  (1 <<12);     /* PC12 output "H" */ \
}while(0)

/* ToDo: You can allocate the CRXD0 to PC13 pin (Alternative to fixed port) */
#define CRXD0_PORT_SETTING() do{ \
        PORT->PC13CFG = 0x00;	     /* allocate CRXD0 to PC13 */ \
        PORT->PMC  |=  (1 <<13);     /* PC13 is used as RXD3 input */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       CAN1                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CAN1 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the CTXD1 to PA09 pin (Alternative to fixed port) */
#define CTXD1_PORT_SETTING() do{ \
        PORT->PA09CFG = 0x00;	     /* allocate CTXD1 to PA09 */ \
        PORT->PMCA &= ~(1 << 9);     /* PA09 digital function */ \
        PORT->PMA  &= ~(1 << 9);     /* PA09 is used as CTXD1 output */ \
        PORT->POMA &= ~(1 << 9);     /* PA09 is push-pull output mode */ \
        PORT->PSETA =  (1 << 9);     /* PA09 output "H" */ \
}while(0)

/* ToDo: You can allocate the CRXD1 to PA10 pin (Alternative to fixed port) */
#define CRXD1_PORT_SETTING() do{ \
        PORT->PA10CFG = 0x00;	     /* allocate CRXD1 to PA10 */ \
        PORT->PMCA &= ~(1 <<10);     /* PA10 digital function */ \
        PORT->PMA  |=  (1 <<10);     /* PA10 is used as CRXD1 input */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SPI                                        ================ */
/* ================================================================================================================== */
/**
  * @brief SPI Port Setting
  */

/* ToDo: Please define one of the following macro and comment out others accroding to your application */
#define SPIHS0_SLAVE_PORT
//#define SPIHS0_MASTER_PORT
//#define SPIHS1_SLAVE_PORT
#define SPIHS1_MASTER_PORT

#ifdef SPIHS0_SLAVE_PORT
#define NSS0_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	     /* allocate NSS0 to PD09 */ \
        PORT->PMD   |=  (1 << 9);    /* PD09 is used as NSS0 input */ \
}while(0)

#define NSS0_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS0_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK0_PORT_SETTING() do{ \
        PORT->PD14CFG = 0x00;	     /* allocate SCK0 to PD14 */ \
        PORT->PMD   |=  (1 <<14);    /* PD14 is used as SCK0 input */ \
}while(0)

#define MOSI0_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x00;	     /* allocate MOSI to PD12 */ \
        PORT->PMD   |=  (1 <<12);    /* PD12 is used as MOSI input */ \
}while(0)

#define MISO0_PORT_SETTING() do{ \
        PORT->PD15CFG = 0x00;	     /* allocate MISO to PD15 */ \
        PORT->PMD   &= ~(1 <<15);    /* PD15 is used as MISO output */ \
        PORT->POMD  &= ~(1 <<15);    /* PD15 is push-pull output mode */ \
        PORT->PCLRD  =  (1 <<15);    /* PD15 output low level */ \
}while(0)
#endif

#ifdef SPIHS0_MASTER_PORT
#define NSS0_PORT_SETTING() do{ \
        PORT->PD09CFG = 0x00;	     /* allocate NSS0 to PD09 */ \
        PORT->PMD   &= ~(1 << 9);    /* PD09 is used as NSS0 output */ \
        PORT->PSETD  =  (1 << 9);    /* PD09 output high level */ \
}while(0)

#define NSS0_PORT_SET() do{ \
        PORT->PSETD  =  (1 << 9);    /* PD09 output high level */ \
}while(0)

#define NSS0_PORT_CLR() do{ \
        PORT->PCLRD  =  (1 << 9);    /* PD09 output low level */ \
}while(0)

#define SCK0_PORT_SETTING() do{ \
        PORT->PD14CFG = 0x00;	     /* allocate SCK0 to PD14 */ \
        PORT->PMD   |=  (1 <<14);    /* PD14 is used as SCK0 input */ \
        PORT->POMD  &= ~(1 <<14);    /* PD14 is push-pull output mode */ \
        PORT->PCLRD  =  (1 <<14);    /* PD14 output low level */ \
}while(0)

#define MOSI0_PORT_SETTING() do{ \
        PORT->PD12CFG = 0x00;	     /* allocate MOSI to PD12 */ \
        PORT->PMD   &= ~(1 <<12);    /* PD12 is used as MOSI output */ \
        PORT->POMD  &= ~(1 <<12);    /* PD12 is push-pull output mode */ \
        PORT->PCLRD  =  (1 <<12);    /* PD12 output low level */ \
}while(0)

#define MISO0_PORT_SETTING() do{ \
        PORT->PD15CFG = 0x00;	     /* allocate MISO to PD15 */ \
        PORT->PMD   |=  (1 <<15);    /* PD12 is used as MISO input */ \
}while(0)
#endif

#ifdef SPIHS1_SLAVE_PORT
/* ToDo: You can allocate the NSS1 to PB01 and PC11 pin */
#define NSS1_PORT_SETTING() do{ \
        PORT->PC11CFG = 0x06;	      /* allocate NSS1 to PC11 */ \
        PORT->PMC   |=  (1 << 11);    /* PC11 is used as NSS1 input */ \
}while(0)

#define NSS1_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS1_PORT_CLR() do{ \
        __NOP(); \
}while(0)

/* ToDo: You can allocate the SCK1 to PB02, PC15 and PD02 pin */
#define SCK1_PORT_SETTING() do{ \
        PORT->PC15CFG = 0x00;	     /* allocate SCK1 to PC15 */ \
        PORT->PMC   |=  (1 <<14);    /* PC15 is used as SCK1 input */ \
}while(0)

/* ToDo: You can allocate the MOSI1 to PB03 and PD11 pin */
#define MOSI1_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x00;	     /* allocate MOSI to PD11 */ \
        PORT->PMD   |=  (1 <<11);    /* PD11 is used as MOSI input */ \
}while(0)

/* ToDo: You can allocate the MISO1 to PB04 and PD10 pin */
#define MISO1_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x00;	     /* allocate MISO to PD10 */ \
        PORT->PMD   &= ~(1 <<15);    /* PD10 is used as MISO output */ \
        PORT->POMD  &= ~(1 <<15);    /* PD10 is push-pull output mode */ \
        PORT->PCLRD  =  (1 <<15);    /* PD10 output low level */ \
}while(0)
#endif

#ifdef SPIHS1_MASTER_PORT
/* ToDo: You can allocate the NSS1 to PB01 and PC11 pin */
#define NSS1_PORT_SETTING() do{ \
        PORT->PC11CFG = 0x06;	     /* allocate NSS1 to PC11 */ \
        PORT->PMD   &= ~(1 <<11);    /* PC11 is used as NSS1 output */ \
        PORT->PSETD  =  (1 <<11);    /* PC11 output high level */ \
}while(0)

#define NSS1_PORT_SET() do{ \
        PORT->PSETD  =  (1 <<11);    /* PC11 output high level */ \
}while(0)

#define NSS1_PORT_CLR() do{ \
        PORT->PCLRD  =  (1 <<11);    /* PC11 output low level */ \
}while(0)

/* ToDo: You can allocate the SCK1 to PB02, PC15 and PD02 pin */
#define SCK1_PORT_SETTING() do{ \
        PORT->PC15CFG = 0x00;	     /* allocate SCK1 to PC15 */ \
        PORT->PMC   |=  (1 <<15);    /* PC15 is used as SCK1 input */ \
        PORT->POMC  &= ~(1 <<15);    /* PC15 is push-pull output mode */ \
        PORT->PCLRC  =  (1 <<15);    /* PC15 output low level */ \
}while(0)

/* ToDo: You can allocate the MOSI1 to PB03 and PD11 pin */
#define MOSI1_PORT_SETTING() do{ \
        PORT->PD11CFG = 0x00;	     /* allocate MOSI to PD11 */ \
        PORT->PMD   &= ~(1 <<11);    /* PD11 is used as MOSI output */ \
        PORT->POMD  &= ~(1 <<11);    /* PD11 is push-pull output mode */ \
        PORT->PCLRD  =  (1 <<11);    /* PD11 output low level */ \
}while(0)

/* ToDo: You can allocate the MISO1 to PB04 and PD10 pin */
#define MISO1_PORT_SETTING() do{ \
        PORT->PD10CFG = 0x00;	     /* allocate MISO to PD10 */ \
        PORT->PMD   |=  (1 <<10);    /* PD10 is used as MISO input */ \
}while(0)
#endif

/* ================================================================================================================== */
/* ================                                       GPT                                       ================ */
/* ================================================================================================================== */
/**
  * @brief GPT Port Setting 
  */


/* ================================================================================================================== */
/* ================                                      KEY-IN                                      ================ */
/* ================================================================================================================== */
/**
  * @brief KEY-IN Port Setting 
  */


/* ================================================================================================================== */
/* ================                                       INTP                                       ================ */
/* ================================================================================================================== */
/**
  * @brief INTP Port Setting 
  */

/**
  * @brief SPI Port Setting
  */

/* ToDo: Please define one of the following macro and comment out others accroding to your application */
//#define SPIHS1_SLAVE_PORT
#define SPIHS1_MASTER_PORT

/* ToDo: You can allocate the INTP0 to PA08, PB07 and PE04 with INTP0PCFG register */
#define INTP0_PORT_SETTING() do{ \
        PORT->INTP0PCFG = 0x00;     /* allocate INTP0 to PA08 */ \
        PORT->PA08CFG = 0x00;       /* PA08 default Alternate function */ \
        PORT->PMA  |=  (1 << 8);    /* PA08 is used as INTP0 input */ \
        PORT->PMCA &= ~(1 << 8);    /* PA08 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP1 to PA09, PB06, PD10 and PH04 with INTP1PCFG register */
#define INTP1_PORT_SETTING() do{ \
        PORT->INTP1PCFG = 0x00;     /* allocate INTP1 to PA09 */ \
        PORT->PA09CFG = 0x00;       /* PA09 default Alternate function */ \
        PORT->PMA  |=  (1 << 9);    /* PA09 is used as INTP1 input */ \
        PORT->PMCA &= ~(1 << 9);    /* PA09 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP2 to PA10, PB07, PE05 and PH03 with INTP2PCFG register */
#define INTP2_PORT_SETTING() do{ \
        PORT->INTP2PCFG = 0x00;     /* allocate INTP2 to PA10 */ \
        PORT->PA10CFG = 0x00;       /* PA10 default Alternate function */ \
        PORT->PMA  |=  (1 <<10);    /* PA10 is used as INTP2 input */ \
        PORT->PMCA &= ~(1 <<10);    /* PA10 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP3 to PD03, PD08 and PA13 with INTP3PCFG register */
#define INTP3_PORT_SETTING() do{ \
        PORT->INTP3PCFG = 0x00;     /* allocate INTP3 to PD03 */ \
        PORT->PD03CFG = 0x00;       /* PD03 default Alternate function */ \
        PORT->PMD  |=  (1 << 3);    /* PD03 is used as INTP3 input */ \
}while(0)

/* ToDo: You can allocate the INTP4 to PC10, PD09, PE02 and PA14 with INTP4PCFG register */
#define INTP4_PORT_SETTING() do{ \
        PORT->INTP4PCFG = 0x00;     /* allocate INTP4 to PC10 */ \
        PORT->PC10CFG = 0x00;       /* PC10 default Alternate function */ \
        PORT->PMC  |=  (1 <<10);    /* PC10 is used as INTP4 input */ \
}while(0)

/* ToDo: You can allocate the INTP5 to PE09, PD05, PE06 and PA15 with INTP5PCFG register */
#define INTP5_PORT_SETTING() do{ \
        PORT->INTP5PCFG = 0x00;     /* allocate INTP3 to PE09 */ \
        PORT->PE09CFG = 0x00;       /* PE09 default Alternate function */ \
        PORT->PME  |=  (1 << 9);    /* PE09 is used as INTP5 input */ \
}while(0)

/* ToDo: You can allocate the INTP6 to PB00, PB05 and PB09 with INTP3PCFG register */
#define INTP6_PORT_SETTING() do{ \
        PORT->INTP6PCFG = 0x00;     /* allocate INTP6 to PB00 */ \
        PORT->PB00CFG = 0x00;       /* PB00 default Alternate function */ \
        PORT->PMB  |=  (1 << 0);    /* PB00 is used as INTP6 input */ \
        PORT->PMCB &= ~(1 << 0);    /* PB00 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP7 to PB01, PB08 and PB12 with INTP4PCFG register */
#define INTP7_PORT_SETTING() do{ \
        PORT->INTP7PCFG = 0x00;     /* allocate INTP7 to PB01 */ \
        PORT->PB01CFG = 0x00;       /* PB01 default Alternate function */ \
        PORT->PMB  |=  (1 << 1);    /* PB01 is used as INTP7 input */ \
        PORT->PMCB &= ~(1 << 1);    /* PB01 digital function */ \
}while(0)

/** @} */ /* End of group Peripherals_Port_Setting_Definations */

#endif
