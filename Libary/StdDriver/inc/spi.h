/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    spi.h
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef SPI_H
#define SPI_H

#include "userdefine.h"
#include "stdint.h"
#pragma clang diagnostic ignored "-Wunused-function"
/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    The SPSm register is a 16-bit register that is used to select two types of operation clocks (CKm0, CKm1) that are
commonly supplied to each channel. (SPSm) 
*/
/*
    SPI control register (SPIC) 
*/
/* Section of operation clock (SCK) (CKS0,CKS1,CKS2) */
#define _0000_SPI_SCK_fCLK_0                   (0x0000U) /* SCK-fCLK */
#define _0001_SPI_SCK_fCLK_1                   (0x0001U) /* SCK-fCLK/2^1 */
#define _0002_SPI_SCK_fCLK_2                   (0x0002U) /* SCK-fCLK/2^2 */
#define _0003_SPI_SCK_fCLK_3                   (0x0003U) /* SCK-fCLK/2^3 */
#define _0004_SPI_SCK_fCLK_4                   (0x0004U) /* SCK-fCLK/2^4 */
#define _0005_SPI_SCK_fCLK_5                   (0x0005U) /* SCK-fCLK/2^5 */
#define _0006_SPI_SCK_fCLK_6                   (0x0006U) /* SCK-fCLK/2^6 */
#define _0007_SPI_SLAVE_MODE                   (0x0007U) /* SCK-SCK Pin */
/* Selection of data and clock phase in SPI mode (CPOL,CPHA) */
#define _0000_SPI_TIMING_0                     (0x0000U) /* type 1 */
#define _0080_SPI_TIMING_1                     (0x0080U) /* type 2 */
#define _0100_SPI_TIMING_2                     (0x0100U) /* type 3 */
#define _0180_SPI_TIMING_3                     (0x0180U) /* type 4 */

/*
    SPI mode register (SPIM) 
*/
/* Operation start trigger of channel (SPIE) */
#define _0000_SPI_START_TRG_OFF                 (0x0000U) /* no trigger operation */
#define _0080_SPI_START_TRG_ON                  (0x0080U) /* sets the SPIE bit to 1 and enters the communication wait status */
/* Setting of operation mode (TRMD) */
#define _0000_SPI_RECEPTION                     (0x0000U) /* reception only */
#define _0040_SPI_TRANSMISSION                  (0x0040U) /* transmission only */
#define _0040_SPI_RECEPTION_TRANSMISSION        (0x0040U) /* transmission/reception */
/* Setting of NSS chip select enable for Slave mode(NSSE) */
#define _0000_SPI_NSS_DISABLE                   (0x0000U) /* NSS disable for Slave mode */
#define _0020_SPI_NSS_ENABLE                    (0x0020U) /* NSS enable for Slave mode */
/* Selection of data transfer sequence (DIR) */
#define _0000_SPI_MSB                           (0x0000U) /* inputs/outputs data with MSB first */
#define _0010_SPI_LSB                           (0x0010U) /* inputs/outputs data with LSB first */
/* Selection of interrupt source (INTMD) */
#define _0000_SPI_TRANSFER_END                  (0x0000U) /* transfer end interrupt */
#define _0008_SPI_BUFFER_EMPTY                  (0x0008U) /* buffer empty interrupt */
/* Setting of data length (DLS) */
#define _0000_SPI_LENGTH_8                      (0x0000U) /* 8-bit data length */
#define _0004_SPI_LENGTH_16                     (0x0004U) /* 16-bit data length */
/* Setting of data length (RECMD) */
#define _0000_SPI_SINGLE_RECEPTION              (0x0000U) /* single reception mode */
#define _0002_SPI_CONTINOUS_RECEPTION           (0x0002U) /* single reception mode */


/*
    SPI mode register (SPIT) 
*/
/* Buffer register status indication flag (SDRIF) */
#define _0002_SPI_VALID_STORED                  (0x0002U) /* valid data is stored in the SDRI register */
/* Communication status indication flag (SPTF) */
#define _0001_SPI_UNDER_EXECUTE                 (0x0001U) /* communication is in progress */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_spi0_rx_address;         /* spi receive buffer address */
extern volatile uint16_t  g_spi0_rx_length;           /* spi receive data length */
extern volatile uint16_t  g_spi0_rx_count;            /* spi receive data count */
extern volatile uint8_t * gp_spi0_tx_address;         /* spi send buffer address */
extern volatile uint16_t  g_spi0_tx_length;           /* spi send data length */
extern volatile uint16_t  g_spi0_tx_count;            /* spi send data count */
extern volatile uint8_t * gp_spi1_rx_address;         /* spi receive buffer address */
extern volatile uint16_t  g_spi1_rx_length;           /* spi receive data length */
extern volatile uint16_t  g_spi1_rx_count;            /* spi receive data count */
extern volatile uint8_t * gp_spi1_tx_address;         /* spi send buffer address */
extern volatile uint16_t  g_spi1_tx_length;           /* spi send data length */
extern volatile uint16_t  g_spi1_tx_count;            /* spi send data count */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void SPI0_Start(void);
void SPI0_Stop(void);
void SPI0_MasterInit(spi_mode_t mode);
MD_STATUS SPI0_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI0_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI0_SlaveInit(spi_mode_t mode);
MD_STATUS SPI0_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI0_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
static void spi0_callback_receiveend(void);
static void spi0_callback_sendend(void);
void SPI1_Start(void);
void SPI1_Stop(void);
void SPI1_MasterInit(spi_mode_t mode);
MD_STATUS SPI1_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI1_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI1_SlaveInit(spi_mode_t mode);
MD_STATUS SPI1_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI1_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
static void spi1_callback_receiveend(void);
static void spi1_callback_sendend(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
