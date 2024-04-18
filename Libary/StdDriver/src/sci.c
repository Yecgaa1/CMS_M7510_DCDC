/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    sci.c
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2022/12/24
***********************************************************************************************************************/
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "stdlib.h"
#include "stdint.h"
#include "BAT32G439.h"
#include "userdefine.h"
#include "sci.h"
#include "dma.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
const uint16_t sps_tbl[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
#if defined USE_SCI_UART0_TX
volatile uint8_t *gp_uart0_tx_address;       /* uart0 transmit buffer address */
volatile uint16_t g_uart0_tx_count;          /* uart0 transmit data number */
#endif
#if defined USE_SCI_UART0_RX
volatile uint8_t *gp_uart0_rx_address;       /* uart0 receive buffer address */
volatile uint16_t g_uart0_rx_count;          /* uart0 receive data number */
volatile uint16_t g_uart0_rx_length;         /* uart0 receive data length */
#endif
#if defined USE_SCI_SPI00
volatile uint8_t *gp_spi00_rx_address;       /* spi00 receive buffer address */
volatile uint16_t g_spi00_rx_length;         /* spi00 receive data length */
volatile uint16_t g_spi00_rx_count;          /* spi00 receive data count */
volatile uint8_t *gp_spi00_tx_address;       /* spi00 send buffer address */
volatile uint16_t g_spi00_tx_length;         /* spi00 send data length */
volatile uint16_t g_spi00_tx_count;          /* spi00 send data count */
#endif
#if defined USE_SCI_SPI01
volatile uint8_t *gp_spi01_rx_address;       /* spi01 receive buffer address */
volatile uint16_t g_spi01_rx_length;         /* spi01 receive data length */
volatile uint16_t g_spi01_rx_count;          /* spi01 receive data count */
volatile uint8_t *gp_spi01_tx_address;       /* spi01 send buffer address */
volatile uint16_t g_spi01_tx_length;         /* spi01 send data length */
volatile uint16_t g_spi01_tx_count;          /* spi01 send data count */
#endif
#if defined USE_SCI_IIC00
volatile uint8_t g_iic00_master_status_flag; /* iic00 start flag for send address check by master mode */
volatile uint8_t *gp_iic00_tx_address;       /* iic00 send data pointer by master mode */
volatile uint16_t g_iic00_tx_count;          /* iic00 send data size by master mode */
volatile uint8_t *gp_iic00_rx_address;       /* iic00 receive data pointer by master mode */
volatile uint16_t g_iic00_rx_count;          /* iic00 receive data size by master mode */
volatile uint16_t g_iic00_rx_length;         /* iic00 receive data length by master mode */
#endif
#if defined USE_SCI_IIC01
volatile uint8_t g_iic01_master_status_flag; /* iic01 start flag for send address check by master mode */
volatile uint8_t *gp_iic01_tx_address;       /* iic01 send data pointer by master mode */
volatile uint16_t g_iic01_tx_count;          /* iic01 send data size by master mode */
volatile uint8_t *gp_iic01_rx_address;       /* iic01 receive data pointer by master mode */
volatile uint16_t g_iic01_rx_count;          /* iic01 receive data size by master mode */
volatile uint16_t g_iic01_rx_length;         /* iic01 receive data length by master mode */
#endif
#if defined USE_SCI_UART1_TX
volatile uint8_t *gp_uart1_tx_address;       /* uart1 transmit buffer address */
volatile uint16_t g_uart1_tx_count;          /* uart1 transmit data number */
#endif
#if defined USE_SCI_UART1_RX
volatile uint8_t *gp_uart1_rx_address;       /* uart1 receive buffer address */
volatile uint16_t g_uart1_rx_count;          /* uart1 receive data number */
volatile uint16_t g_uart1_rx_length;         /* uart1 receive data length */
#endif
#if defined USE_SCI_SPI10
volatile uint8_t *gp_spi10_rx_address;       /* spi10 receive buffer address */
volatile uint16_t g_spi10_rx_length;         /* spi10 receive data length */
volatile uint16_t g_spi10_rx_count;          /* spi10 receive data count */
volatile uint8_t *gp_spi10_tx_address;       /* spi10 send buffer address */
volatile uint16_t g_spi10_tx_length;         /* spi10 send data length */
volatile uint16_t g_spi10_tx_count;          /* spi10 send data count */
#endif
#if defined USE_SCI_SPI11
volatile uint8_t *gp_spi11_rx_address;       /* spi11 receive buffer address */
volatile uint16_t g_spi11_rx_length;         /* spi11 receive data length */
volatile uint16_t g_spi11_rx_count;          /* spi11 receive data count */
volatile uint8_t *gp_spi11_tx_address;       /* spi11 send buffer address */
volatile uint16_t g_spi11_tx_length;         /* spi11 send data length */
volatile uint16_t g_spi11_tx_count;          /* spi11 send data count */
#endif
#if defined USE_SCI_IIC10
volatile uint8_t g_iic10_master_status_flag; /* iic10 start flag for send address check by master mode */
volatile uint8_t *gp_iic10_tx_address;       /* iic10 send data pointer by master mode */
volatile uint16_t g_iic10_tx_count;          /* iic10 send data size by master mode */
volatile uint8_t *gp_iic10_rx_address;       /* iic10 receive data pointer by master mode */
volatile uint16_t g_iic10_rx_count;          /* iic10 receive data size by master mode */
volatile uint16_t g_iic10_rx_length;         /* iic10 receive data length by master mode */
#endif
#if defined USE_SCI_IIC11
volatile uint8_t g_iic11_master_status_flag; /* iic11 start flag for send address check by master mode */
volatile uint8_t *gp_iic11_tx_address;       /* iic11 send data pointer by master mode */
volatile uint16_t g_iic11_tx_count;          /* iic11 send data size by master mode */
volatile uint8_t *gp_iic11_rx_address;       /* iic11 receive data pointer by master mode */
volatile uint16_t g_iic11_rx_count;          /* iic11 receive data size by master mode */
volatile uint16_t g_iic11_rx_length;         /* iic11 receive data length by master mode */
#endif
#if defined USE_SCI_UART2_TX
volatile uint8_t *gp_uart2_tx_address;       /* uart2 transmit buffer address */
volatile uint16_t g_uart2_tx_count;          /* uart2 transmit data number */
#endif
#if defined USE_SCI_UART2_RX
volatile uint8_t *gp_uart2_rx_address;       /* uart2 receive buffer address */
volatile uint16_t g_uart2_rx_count;          /* uart2 receive data number */
volatile uint16_t g_uart2_rx_length;         /* uart2 receive data length */
#endif
#if defined USE_SCI_SPI20
volatile uint8_t *gp_spi20_rx_address;       /* spi20 receive buffer address */
volatile uint16_t g_spi20_rx_length;         /* spi20 receive data length */
volatile uint16_t g_spi20_rx_count;          /* spi20 receive data count */
volatile uint8_t *gp_spi20_tx_address;       /* spi20 send buffer address */
volatile uint16_t g_spi20_tx_length;         /* spi20 send data length */
volatile uint16_t g_spi20_tx_count;          /* spi20 send data count */
#endif
#if defined USE_SCI_SPI21
volatile uint8_t *gp_spi21_rx_address;       /* spi21 receive buffer address */
volatile uint16_t g_spi21_rx_length;         /* spi21 receive data length */
volatile uint16_t g_spi21_rx_count;          /* spi21 receive data count */
volatile uint8_t *gp_spi21_tx_address;       /* spi21 send buffer address */
volatile uint16_t g_spi21_tx_length;         /* spi21 send data length */
volatile uint16_t g_spi21_tx_count;          /* spi21 send data count */
#endif
#if defined USE_SCI_IIC20
volatile uint8_t g_iic20_master_status_flag; /* iic20 start flag for send address check by master mode */
volatile uint8_t *gp_iic20_tx_address;       /* iic20 send data pointer by master mode */
volatile uint16_t g_iic20_tx_count;          /* iic20 send data size by master mode */
volatile uint8_t *gp_iic20_rx_address;       /* iic20 receive data pointer by master mode */
volatile uint16_t g_iic20_rx_count;          /* iic20 receive data size by master mode */
volatile uint16_t g_iic20_rx_length;         /* iic20 receive data length by master mode */
#endif
#if defined USE_SCI_IIC21
volatile uint8_t g_iic21_master_status_flag; /* iic21 start flag for send address check by master mode */
volatile uint8_t *gp_iic21_tx_address;       /* iic21 send data pointer by master mode */
volatile uint16_t g_iic21_tx_count;          /* iic21 send data size by master mode */
volatile uint8_t *gp_iic21_rx_address;       /* iic21 receive data pointer by master mode */
volatile uint16_t g_iic21_rx_count;          /* iic21 receive data size by master mode */
volatile uint16_t g_iic21_rx_length;         /* iic21 receive data length by master mode */
#endif
#if defined USE_SCI_UART3_TX
volatile uint8_t * gp_uart3_tx_address;      /* uart3 send buffer address */
volatile uint16_t  g_uart3_tx_count;         /* uart3 send data number */
#endif
#if defined USE_SCI_UART3_RX
volatile uint8_t * gp_uart3_rx_address;      /* uart3 receive buffer address */
volatile uint16_t  g_uart3_rx_count;         /* uart3 receive data number */
volatile uint16_t  g_uart3_rx_length;        /* uart3 receive data length */
#endif
#if defined USE_SCI_SPI30
volatile uint8_t * gp_spi30_rx_address;      /* spi30 receive buffer address */
volatile uint16_t  g_spi30_rx_length;        /* spi30 receive data length */
volatile uint16_t  g_spi30_rx_count;         /* spi30 receive data count */
volatile uint8_t * gp_spi30_tx_address;      /* spi30 send buffer address */
volatile uint16_t  g_spi30_tx_length;      /* spi30 send data length */
volatile uint16_t  g_spi30_tx_count;         /* spi30 send data count */
#endif
#if defined USE_SCI_SPI31
volatile uint8_t * gp_spi31_rx_address;      /* spi31 receive buffer address */
volatile uint16_t  g_spi31_rx_length;        /* spi31 receive data length */
volatile uint16_t  g_spi31_rx_count;         /* spi31 receive data count */
volatile uint8_t * gp_spi31_tx_address;      /* spi31 send buffer address */
volatile uint16_t  g_spi31_tx_length;      /* spi31 send data length */
volatile uint16_t  g_spi31_tx_count;         /* spi31 send data count */
#endif
#if defined USE_SCI_IIC30
volatile uint8_t g_iic30_master_status_flag; /* iic30 start flag for send address check by master mode */
volatile uint8_t * gp_iic30_tx_address;      /* iic30 send data pointer by master mode */
volatile uint16_t  g_iic30_tx_count;         /* iic30 send data size by master mode */
volatile uint8_t * gp_iic30_rx_address;      /* iic30 receive data pointer by master mode */
volatile uint16_t  g_iic30_rx_count;         /* iic30 receive data size by master mode */
volatile uint16_t  g_iic30_rx_length;        /* iic30 receive data length by master mode */
#endif
#if defined USE_SCI_IIC30
volatile uint8_t g_iic31_master_status_flag; /* iic31 start flag for send address check by master mode */
volatile uint8_t * gp_iic31_tx_address;      /* iic31 send data pointer by master mode */
volatile uint16_t  g_iic31_tx_count;         /* iic31 send data size by master mode */
volatile uint8_t * gp_iic31_rx_address;      /* iic31 receive data pointer by master mode */
volatile uint16_t  g_iic31_rx_count;         /* iic31 receive data size by master mode */
volatile uint16_t  g_iic31_rx_length;        /* iic31 receive data length by master mode *//* Start user code for global. Do not edit comment generated here */
#endif

/* End user code. Do not edit comment generated here */

static MD_STATUS UART_BaudRateCal(uint32_t fclk_freq, uint32_t baud, uart_baud_t *pvalue);

#if 1
/***********************************************************************************************************************
* Function Name: UART0_Init
* @brief  This function initializes the UART0 module.
*         Date Length: 8 bit; Parity: none; Stop: 1 bit              
* @param  SCIx - SCI0(UART0), SCI1(UART1), SCI2(UART2), SCI3(UART3)
* @param  freq - the frequency of fCLK
* @param  baud - the expected baud rate
* @return MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART_Init(SCI_Type *SCIx, uint32_t freq, uint32_t baud)
{
    MD_STATUS status;

    if (SCIx==SCI0){
        CGC->PERA  |= CGC_PERA_SCI0EN_Msk;
    }
    else if(SCIx==SCI1){
        CGC->PERA  |= CGC_PERA_SCI1EN_Msk;
    }
    else if(SCIx==SCI2){
        CGC->PERA  |= CGC_PERA_SCI2EN_Msk;
    }
    else if(SCIx==SCI3){
        CGC->PERA  |= CGC_PERA_SCI3EN_Msk;
    }
    SCIx->SPS = (3 << SCI0_SPS0_PRS01_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    /* transmission channel */
    SCIx->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCIx->SCRm0 = _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCIx->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _01_SCI_RXD0_FILTER_ON;
    SCIx->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCIx->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCIx->SCRm1 = _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
    SCIx->SDRm1 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* output enable */
    SCIx->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;
    SCIx->SOL &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
    SCIx->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set TxD, RxD pin */
    if (SCIx==SCI0){
        TXD0_PORT_SETTING();
        RXD0_PORT_SETTING();
    }
    else if(SCIx==SCI1){
        TXD1_PORT_SETTING();
        RXD1_PORT_SETTING();
    }
    else if(SCIx==SCI2){
        TXD2_PORT_SETTING();
        RXD2_PORT_SETTING();
    }
    else if(SCIx==SCI3){
        TXD3_PORT_SETTING();
        RXD3_PORT_SETTING();
    }

    /* UARTx Stop, Setting baud rate */
    SCIx->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
    status = UART_BaudRate(SCIx, freq, baud);
    /* UARTx Start */
    SCIx->SS = _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;
    return (status);
}

/***********************************************************************************************************************
* Function Name: UART_BaudRateCal
* @brief  This function search the setting value for specified freq and baud of UART
* @param  fclk_freq
*             - the frequency of fCLK clock. unit Hz.
* @param  baud
*             - the target baud rate, unit bps.
* @param  pvalue
*             - the pointer of calculated result
* @return MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART_BaudRateCal(uint32_t fclk_freq, uint32_t baud, uart_baud_t *pvalue)
{
    MD_STATUS status ;
    int32_t baud_err,baud_err_temp = 100;
    uint32_t baud_cal;
    uint32_t fmck_freq;
    uint32_t least_freq;
    uint32_t i, j,m,k=0;
    uint32_t i_record=0,j_record=0;

    least_freq = baud*2*128;
    m = fclk_freq/least_freq + 1 ;

    while((1<<k) < m)
    {
        k++;
    }
    for (i = k; i < 16; i++)
    {
        fmck_freq = fclk_freq / sps_tbl[i];
        for (j = 2; j < 128; j++)
        {
            baud_cal = fmck_freq / (j + 1) / 2;
            baud_err = (int32_t)(1000 * baud_cal / baud - 1000) * 10;  // n ten thousandths
            if(abs(baud_err_temp) > abs(baud_err))
            {
                baud_err_temp = baud_err;
                j_record = j;
                i_record = i;
            }
            if (abs(baud_err_temp) < 20)  /* 0.2% */
            {
                pvalue->prs = (uint8_t)i;
                pvalue->sdr = (uint8_t)j;
                //printf("fclk_freq = %10dHz, baud = %6dbps, prs = %2d, sdr = %3d, errors = %3d\n", fclk_freq, baud, pvalue->prs, pvalue->sdr, baud_err);
                status = MD_OK;
                return (status);
            }       
        }
    }
    if(abs(baud_err_temp) >= 20)
    {
        pvalue->prs = (uint8_t)i_record;
        pvalue->sdr = (uint8_t)j_record;
    } 

    status = MD_OK; 

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART0_BaudRate
* @brief  This function sets the baud rate of UART0.
* @param  fclk_freq
*             - the frequency of fCLK clock. unit Hz.
* @param  baud
*             - the target baud rate, unit bps.
* @return None
***********************************************************************************************************************/
MD_STATUS UART_BaudRate(SCI_Type *SCIx, uint32_t fclk_freq, uint32_t baud)
{
    MD_STATUS status;
    uart_baud_t pvalue;

#ifndef RTL_SIMULATION
    status = UART_BaudRateCal(fclk_freq, baud, &pvalue);
#else
    pvalue.prs = 0x4;
    pvalue.sdr = 0x4D;
    status = MD_OK;
#endif

    if (status == MD_OK)
    {
        SCIx->SPS &= ~SCI0_SPS0_PRS00_Msk;
        SCIx->SPS |= pvalue.prs;
        SCIx->SDRm0 = (uint16_t)(pvalue.sdr << 9);
        SCIx->SDRm1 = (uint16_t)(pvalue.sdr << 9);
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART0_Send
* @brief  This function sends UART0 data.
* @param  ch - transfer char
* @return None
***********************************************************************************************************************/
void UART_Send(SCI_Type *SCIx, uint8_t ch)
{
    SCIx->TXD = ch;
    while (SCIx->SSRm0 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
    {
    }
    return;
}
MD_STATUS UART_Send_Int(SCI_Type *SCIx, uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        if (SCIx==SCI0){
            #if defined USE_SCI_UART0_TX
            gp_uart0_tx_address = tx_buf;
            g_uart0_tx_count = tx_num;
            SCIx->TXD = *gp_uart0_tx_address;
            gp_uart0_tx_address++;
            g_uart0_tx_count--;
            #endif
        }
        else if(SCIx==SCI1){
            #if defined USE_SCI_UART1_TX
            gp_uart1_tx_address = tx_buf;
            g_uart1_tx_count = tx_num;
            SCIx->TXD = *gp_uart1_tx_address;
            gp_uart1_tx_address++;
            g_uart1_tx_count--;
            #endif
        }
        else if(SCIx==SCI2){
            #if defined USE_SCI_UART2_TX
            gp_uart2_tx_address = tx_buf;
            g_uart2_tx_count = tx_num;
            SCIx->TXD = *gp_uart2_tx_address;
            gp_uart2_tx_address++;
            g_uart2_tx_count--;
            #endif
        }
        else if(SCIx==SCI3){
            #if defined USE_SCI_UART3_TX
            gp_uart3_tx_address = tx_buf;
            g_uart3_tx_count = tx_num;
            SCIx->TXD = *gp_uart3_tx_address;
            gp_uart3_tx_address++;
            g_uart3_tx_count--;
            #endif
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART0_Receive
* @brief  This function receives UART0 data.
* @param  None
* @return char
***********************************************************************************************************************/
char UART_Receive(SCI_Type *SCIx)
{
    while ((SCIx->SSRm1 & _0020_SCI_VALID_STORED) == 0)
    {
    }
    return SCIx->RXD;
}

/***********************************************************************************************************************
* Function Name: UART0_Receive_Int
* @brief  This function receives UART0 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS UART_Receive_Int(SCI_Type *SCIx, uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        if (SCIx==SCI0){
            #if defined USE_SCI_UART0_RX
            g_uart0_rx_count = 0U;
            g_uart0_rx_length = rx_num;
            gp_uart0_rx_address = rx_buf;
            #endif
        }
        else if(SCIx==SCI1){
            #if defined USE_SCI_UART1_RX
            g_uart1_rx_count = 0U;
            g_uart1_rx_length = rx_num;
            gp_uart1_rx_address = rx_buf;
            #endif
        }
        else if(SCIx==SCI2){
            #if defined USE_SCI_UART2_RX
            g_uart2_rx_count = 0U;
            g_uart2_rx_length = rx_num;
            gp_uart2_rx_address = rx_buf;
            #endif
        }
        else if(SCIx==SCI3){
            #if defined USE_SCI_UART3_RX
            g_uart3_rx_count = 0U;
            g_uart3_rx_length = rx_num;
            gp_uart3_rx_address = rx_buf;
            #endif
        }
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: UART_Start
* @brief  This function starts the UART1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART_Start(SCI_Type *SCIx)
{
    SCIx->SO |= _0001_SCI_CH0_DATA_OUTPUT_1;
    SCIx->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCIx->SS = _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;
    NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    NVIC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
    NVIC_EnableIRQ(ST1_IRQn);       /* enable INTST1 interrupt */
    NVIC_EnableIRQ(SR1_IRQn);       /* enable INTSR1 interrupt */
}
/***********************************************************************************************************************
* Function Name: UART_Stop
* @brief  This function stops the UART1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART_Stop(SCI_Type *SCIx)
{
    NVIC_DisableIRQ(ST1_IRQn); /* disable INTST1 interrupt */
    NVIC_DisableIRQ(SR1_IRQn); /* disable INTSR1 interrupt */
    SCIx->ST = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
    SCIx->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
    NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    NVIC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
}
#endif

#if 1
/***********************************************************************************************************************
* Function Name: SPI00_Start
* @brief  This function starts the SPI00 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI_Start(sci_spi_chmn spimn)
{
    switch (spimn){
        case SCI0_SPI00:
            #ifdef USE_SCI_SPI00
            /* SSn Active */
            SS00_PORT_CLR();
            SCI0->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI0->SS   = _0001_SCI_CH0_START_TRG_ON;
            /* clear INTSPI00 interrupt flag */
            NVIC_ClearPendingIRQ(SPI00_IRQn);
            /* enable INTSPI00 interrupt */
            NVIC_EnableIRQ(SPI00_IRQn);
            #endif
            break;
        case SCI0_SPI01:
            #ifdef USE_SCI_SPI01
            /* SSn Active */
            SS01_PORT_CLR();
            SCI0->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI0->SS   = _0002_SCI_CH1_START_TRG_ON;
            /* clear INTSPI01 interrupt flag */
            NVIC_ClearPendingIRQ(SPI01_IRQn);
            /* enable INTSPI01 interrupt */
            NVIC_EnableIRQ(SPI01_IRQn);
            #endif
            break;
        case SCI1_SPI10:
            #ifdef USE_SCI_SPI10
            /* SSn Active */
            SS10_PORT_CLR();
            SCI1->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI1->SS   = _0001_SCI_CH0_START_TRG_ON;
            /* clear INTSPI10 interrupt flag */
            NVIC_ClearPendingIRQ(SPI10_IRQn);
            /* enable INTSPI10 interrupt */
            NVIC_EnableIRQ(SPI10_IRQn);
            #endif
            break;
        case SCI1_SPI11:
            #ifdef USE_SCI_SPI11
            /* SSn Active */
            SS11_PORT_CLR();
            SCI1->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI1->SS   = _0002_SCI_CH1_START_TRG_ON;
            /* clear INTSPI11 interrupt flag */
            NVIC_ClearPendingIRQ(SPI11_IRQn);
            /* enable INTSPI11 interrupt */
            NVIC_EnableIRQ(SPI11_IRQn);
            #endif
            break;
        case SCI2_SPI20:
            #ifdef USE_SCI_SPI20
            /* SSn Active */
            SS20_PORT_CLR();
            SCI2->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI2->SS   = _0001_SCI_CH0_START_TRG_ON;
            /* clear INTSPI20 interrupt flag */
            NVIC_ClearPendingIRQ(SPI20_IRQn);
            /* enable INTSPI20 interrupt */
            NVIC_EnableIRQ(SPI20_IRQn);
            #endif
            break;
        case SCI2_SPI21:
            #ifdef USE_SCI_SPI21
            /* SSn Active */
            SS21_PORT_CLR();
            SCI2->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI2->SS   = _0002_SCI_CH1_START_TRG_ON;
            /* clear INTSPI21 interrupt flag */
            NVIC_ClearPendingIRQ(SPI21_IRQn);
            /* enable INTSPI21 interrupt */
            NVIC_EnableIRQ(SPI21_IRQn);
            #endif
            break;
        case SCI3_SPI30:
            #ifdef USE_SCI_SPI30
            /* SSn Active */
            SS20_PORT_CLR();
            SCI2->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI2->SS   = _0001_SCI_CH0_START_TRG_ON;
            /* clear INTSPI20 interrupt flag */
            NVIC_ClearPendingIRQ(SPI20_IRQn);
            /* enable INTSPI20 interrupt */
            NVIC_EnableIRQ(SPI20_IRQn);
            #endif
            break;
        case SCI3_SPI31:
            #ifdef USE_SCI_SPI31
            /* SSn Active */
            SS21_PORT_CLR();
            SCI2->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI2->SS   = _0002_SCI_CH1_START_TRG_ON;
            /* clear INTSPI21 interrupt flag */
            NVIC_ClearPendingIRQ(SPI21_IRQn);
            /* enable INTSPI21 interrupt */
            NVIC_EnableIRQ(SPI21_IRQn);
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: SPI00_Stop
* @brief  This function stops the SPI00 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI_Stop(sci_spi_chmn spimn)
{
    switch (spimn){
        case SCI0_SPI00:
            #ifdef USE_SCI_SPI00
            /* disable INTSPI00 interrupt */
            NVIC_DisableIRQ(SPI00_IRQn);
            SCI0->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI0->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            /* clear INTSPI00 interrupt flag */
            NVIC_ClearPendingIRQ(SPI00_IRQn);
            /* SSn Inactive */
            SS00_PORT_SET();
            #endif
            break;
        case SCI0_SPI01:
            #ifdef USE_SCI_SPI01
            /* disable INTSPI01 interrupt */
            NVIC_DisableIRQ(SPI01_IRQn);
            SCI0->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI0->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            /* clear INTSPI01 interrupt flag */
            NVIC_ClearPendingIRQ(SPI01_IRQn);
            /* SSn Inactive */
            SS01_PORT_SET();
            #endif
            break;
        case SCI1_SPI10:
            #ifdef USE_SCI_SPI10
            /* disable INTSPI10 interrupt */
            NVIC_DisableIRQ(SPI10_IRQn);
            SCI1->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI1->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            /* clear INTSPI10 interrupt flag */
            NVIC_ClearPendingIRQ(SPI10_IRQn);
            /* SSn Inactive */
            SS10_PORT_SET();
            #endif
            break;
        case SCI1_SPI11:
            #ifdef USE_SCI_SPI11
            /* disable INTSPI11 interrupt */
            NVIC_DisableIRQ(SPI11_IRQn);
            SCI1->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI1->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            /* clear INTSPI11 interrupt flag */
            NVIC_ClearPendingIRQ(SPI11_IRQn);
            /* SSn Inactive */
            SS11_PORT_SET();
            #endif
            break;
        case SCI2_SPI20:
            #ifdef USE_SCI_SPI20
            /* disable INTSPI20 interrupt */
            NVIC_DisableIRQ(SPI20_IRQn);
            SCI2->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI2->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            /* clear INTSPI20 interrupt flag */
            NVIC_ClearPendingIRQ(SPI20_IRQn);
            /* SSn Inactive */
            SS20_PORT_SET();
            #endif
            break;
        case SCI2_SPI21:
            #ifdef USE_SCI_SPI21
            /* disable INTSPI21 interrupt */
            NVIC_DisableIRQ(SPI21_IRQn);
            SCI2->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI2->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            /* clear INTSPI21 interrupt flag */
            NVIC_ClearPendingIRQ(SPI21_IRQn);
            /* SSn Inactive */
            SS21_PORT_SET();
            #endif
            break;
        case SCI3_SPI30:
            #ifdef USE_SCI_SPI30
            /* disable INTSPI30 interrupt */
            NVIC_DisableIRQ(SPI30_IRQn);
            SCI3->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI3->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            /* clear INTSPI30 interrupt flag */
            NVIC_ClearPendingIRQ(SPI30_IRQn);
            /* SSn Inactive */
            SS30_PORT_SET();
            #endif
            break;
        case SCI3_SPI31:
            #ifdef USE_SCI_SPI31
            /* disable INTSPI31 interrupt */
            NVIC_DisableIRQ(SPI31_IRQn);
            SCI3->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI3->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            /* clear INTSPI31 interrupt flag */
            NVIC_ClearPendingIRQ(SPI31_IRQn);
            /* SSn Inactive */
            SS31_PORT_SET();
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: SPI00_MasterInit
* @brief  This function initializes the SPI00 module as Master.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
MD_STATUS SPI_MasterInit(sci_spi_chmn spimn, spi_mode_t mode)
{
    MD_STATUS status;
    SCI_Type *SCIx;

    if ((spimn==SCI0_SPI00)|(spimn==SCI0_SPI01)){
        CGC->PERA  |= CGC_PERA_SCI0EN_Msk;
        SCIx = SCI0;
    }
    else if ((spimn==SCI1_SPI10)|(spimn==SCI1_SPI11)){
        CGC->PERA  |= CGC_PERA_SCI1EN_Msk;
        SCIx = SCI1;
    }
    else if ((spimn==SCI2_SPI20)|(spimn==SCI2_SPI21)){
        CGC->PERA  |= CGC_PERA_SCI2EN_Msk;
        SCIx = SCI2;
    }
    else if ((spimn==SCI3_SPI30)|(spimn==SCI3_SPI31)){
        CGC->PERA  |= CGC_PERA_SCI3EN_Msk;
        SCIx = SCI3;
    }
    else{
        return MD_ERROR;
    }
    // SCIx->ch0
    if ((spimn==SCI0_SPI00)|(spimn==SCI1_SPI10)|(spimn==SCI2_SPI20)|(spimn==SCI3_SPI30)){
        SCIx->ST = _0001_SCI_CH0_STOP_TRG_ON;
        SCIx->SPS &= ~SCI0_SPS0_PRS01_Msk;
        SCIx->SPS |= (0 << SCI0_SPS0_PRS00_Pos);
        SCIx->SIRm0 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
        SCIx->SCRm0 = _C000_SCI_RECEPTION_TRANSMISSION | mode | _0000_SCI_INTSRE_MASK |
                      _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0007_SCI_LENGTH_8;
        SCIx->SDRm0 = _CE00_SCI_BAUDRATE_DIVISOR;
        /* Set output enable */
        if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
        {
            SCIx->SO &= ~_0100_SCI_CH0_CLOCK_OUTPUT_1;
        }
        if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
        {
            SCIx->SO |= _0100_SCI_CH0_CLOCK_OUTPUT_1;
        }
        SCIx->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
    }
    // SCIx->ch1
    else{
        SCIx->ST = _0002_SCI_CH1_STOP_TRG_ON;
        SCIx->SPS &= ~SCI0_SPS0_PRS01_Msk;
        SCIx->SPS |= (0 << SCI0_SPS0_PRS01_Pos);
        SCIx->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
        SCIx->SCRm1 = _C000_SCI_RECEPTION_TRANSMISSION | mode | _0000_SCI_INTSRE_MASK |
                      _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0007_SCI_LENGTH_8;
        SCIx->SDRm1 = _CE00_SCI_BAUDRATE_DIVISOR;
        /* Set output enable */
        if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
        {
            SCIx->SO &= ~_0200_SCI_CH1_CLOCK_OUTPUT_1;
        }
        if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
        {
            SCIx->SO |= _0200_SCI_CH1_CLOCK_OUTPUT_1;
        }
        SCIx->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
    }
    switch (spimn){
        case SCI0_SPI00:
            #ifdef USE_SCI_SPI00
            /* Set SSn pin */
            SS00_PORT_SETTING();
            /* Set SCLK00 pin */
            SCLKO00_PORT_SETTING();
            /* Set SDI00 pin */
            SDI00_PORT_SETTING();
            /* Set SDO00 pin */
            SDO00_PORT_SETTING();
            #endif
            break;
        case SCI0_SPI01:
            #ifdef USE_SCI_SPI01
            /* Set SSn pin */
            SS01_PORT_SETTING();
            /* Set SCLK01 pin */
            SCLKO01_PORT_SETTING();
            /* Set SDI01 pin */
            SDI01_PORT_SETTING();
            /* Set SDO01 pin */
            SDO01_PORT_SETTING();
            #endif
            break;
        case SCI1_SPI10:
            #ifdef USE_SCI_SPI10
            /* Set SSn pin */
            SS10_PORT_SETTING();
            /* Set SCLK10 pin */
            SCLKO10_PORT_SETTING();
            /* Set SDI10 pin */
            SDI10_PORT_SETTING();
            /* Set SDO10 pin */
            SDO10_PORT_SETTING();
            #endif
            break;
        case SCI1_SPI11:
            #ifdef USE_SCI_SPI11
            /* Set SSn pin */
            SS11_PORT_SETTING();
            /* Set SCLK11 pin */
            SCLKO11_PORT_SETTING();
            /* Set SDI11 pin */
            SDI11_PORT_SETTING();
            /* Set SDO11 pin */
            SDO11_PORT_SETTING();
            #endif
            break;
        case SCI2_SPI20:
            #ifdef USE_SCI_SPI20
            /* Set SSn pin */
            SS20_PORT_SETTING();
            /* Set SCLK20 pin */
            SCLKO20_PORT_SETTING();
            /* Set SDI20 pin */
            SDI20_PORT_SETTING();
            /* Set SDO20 pin */
            SDO20_PORT_SETTING();
            #endif
            break;
        case SCI2_SPI21:
            #ifdef USE_SCI_SPI21
            /* Set SSn pin */
            SS21_PORT_SETTING();
            /* Set SCLK21 pin */
            SCLKO21_PORT_SETTING();
            /* Set SDI21 pin */
            SDI21_PORT_SETTING();
            /* Set SDO21 pin */
            SDO21_PORT_SETTING();
            #endif
            break;
        case SCI3_SPI30:
            #ifdef USE_SCI_SPI30
            /* Set SSn pin */
            SS30_PORT_SETTING();
            /* Set SCLK30 pin */
            SCLKO30_PORT_SETTING();
            /* Set SDI30 pin */
            SDI30_PORT_SETTING();
            /* Set SDO30 pin */
            SDO30_PORT_SETTING();
            #endif
            break;
        case SCI3_SPI31:
            #ifdef USE_SCI_SPI31
            /* Set SSn pin */
            SS31_PORT_SETTING();
            /* Set SCLK31 pin */
            SCLKO31_PORT_SETTING();
            /* Set SDI31 pin */
            SDI31_PORT_SETTING();
            /* Set SDO31 pin */
            SDO31_PORT_SETTING();
            #endif
            break;
    }

    status = MD_OK; 
    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI00_MasterSendReceive
* @brief  This function sends and receives SPI00 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_MasterSendReceive(sci_spi_chmn spimn, uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi00_rx_count = tx_num;    /* receive data count */
                g_spi00_tx_count = tx_num;    /* send data count */
                gp_spi00_tx_address = tx_buf; /* send buffer pointer */
                gp_spi00_rx_address = rx_buf; /* receive buffer pointer */

                g_spi00_tx_count--;
                SPI_Start(spimn);
                SCI0->SIOm0 = *gp_spi00_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi00_tx_address++;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi01_rx_count = tx_num;    /* receive data count */
                g_spi01_tx_count = tx_num;    /* send data count */
                gp_spi01_tx_address = tx_buf; /* send buffer pointer */
                gp_spi01_rx_address = rx_buf; /* receive buffer pointer */

                g_spi01_tx_count--;
                SPI_Start(spimn);
                SCI0->SIOm1 = *gp_spi01_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi01_tx_address++;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi10_rx_count = tx_num;    /* receive data count */
                g_spi10_tx_count = tx_num;    /* send data count */
                gp_spi10_tx_address = tx_buf; /* send buffer pointer */
                gp_spi10_rx_address = rx_buf; /* receive buffer pointer */

                g_spi10_tx_count--;
                SPI_Start(spimn);
                SCI1->SIOm0 = *gp_spi10_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi10_tx_address++;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi11_rx_count = tx_num;    /* receive data count */
                g_spi11_tx_count = tx_num;    /* send data count */
                gp_spi11_tx_address = tx_buf; /* send buffer pointer */
                gp_spi11_rx_address = rx_buf; /* receive buffer pointer */

                g_spi11_tx_count--;
                SPI_Start(spimn);
                SCI1->SIOm1 = *gp_spi11_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi11_tx_address++;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi20_rx_count = tx_num;    /* receive data count */
                g_spi20_tx_count = tx_num;    /* send data count */
                gp_spi20_tx_address = tx_buf; /* send buffer pointer */
                gp_spi20_rx_address = rx_buf; /* receive buffer pointer */

                g_spi20_tx_count--;
                SPI_Start(spimn);
                SCI2->SIOm0 = *gp_spi20_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi20_tx_address++;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi21_rx_count = tx_num;    /* receive data count */
                g_spi21_tx_count = tx_num;    /* send data count */
                gp_spi21_tx_address = tx_buf; /* send buffer pointer */
                gp_spi21_rx_address = rx_buf; /* receive buffer pointer */

                g_spi21_tx_count--;
                SPI_Start(spimn);
                SCI2->SIOm1 = *gp_spi21_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi21_tx_address++;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi30_rx_count = tx_num;    /* receive data count */
                g_spi30_tx_count = tx_num;    /* send data count */
                gp_spi30_tx_address = tx_buf; /* send buffer pointer */
                gp_spi30_rx_address = rx_buf; /* receive buffer pointer */

                g_spi30_tx_count--;
                SPI_Start(spimn);
                SCI3->SIOm0 = *gp_spi30_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi30_tx_address++;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;
                g_spi31_rx_count = tx_num;    /* receive data count */
                g_spi31_tx_count = tx_num;    /* send data count */
                gp_spi31_tx_address = tx_buf; /* send buffer pointer */
                gp_spi31_rx_address = rx_buf; /* receive buffer pointer */

                g_spi31_tx_count--;
                SPI_Start(spimn);
                SCI3->SIOm1 = *gp_spi31_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi31_tx_address++;
                #endif
                break;
        }
    }
    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_MasterSend
* @brief  This function sends SPI10 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_MasterSend(sci_spi_chmn spimn, uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi00_tx_count = tx_num;    /* send data count */
                gp_spi00_tx_address = tx_buf; /* send buffer pointer */

                g_spi00_tx_count--;
                SPI_Start(spimn);
                SCI0->SIOm0 = *gp_spi00_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi00_tx_address++;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi01_tx_count = tx_num;    /* send data count */
                gp_spi01_tx_address = tx_buf; /* send buffer pointer */

                g_spi01_tx_count--;
                SPI_Start(spimn);
                SCI0->SIOm1 = *gp_spi01_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi01_tx_address++;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi10_tx_count = tx_num;    /* send data count */
                gp_spi10_tx_address = tx_buf; /* send buffer pointer */

                g_spi10_tx_count--;
                SPI_Start(spimn);
                SCI1->SIOm0 = *gp_spi10_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi10_tx_address++;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi11_tx_count = tx_num;    /* send data count */
                gp_spi11_tx_address = tx_buf; /* send buffer pointer */

                g_spi11_tx_count--;
                SPI_Start(spimn);
                SCI1->SIOm1 = *gp_spi11_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi11_tx_address++;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi20_tx_count = tx_num;    /* send data count */
                gp_spi20_tx_address = tx_buf; /* send buffer pointer */

                g_spi20_tx_count--;
                SPI_Start(spimn);
                SCI2->SIOm0 = *gp_spi20_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi20_tx_address++;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi21_tx_count = tx_num;    /* send data count */
                gp_spi21_tx_address = tx_buf; /* send buffer pointer */

                g_spi21_tx_count--;
                SPI_Start(spimn);
                SCI2->SIOm1 = *gp_spi21_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi21_tx_address++;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi30_tx_count = tx_num;    /* send data count */
                gp_spi30_tx_address = tx_buf; /* send buffer pointer */

                g_spi30_tx_count--;
                SPI_Start(spimn);
                SCI3->SIOm0 = *gp_spi30_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi30_tx_address++;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi31_tx_count = tx_num;    /* send data count */
                gp_spi31_tx_address = tx_buf; /* send buffer pointer */

                g_spi31_tx_count--;
                SPI_Start(spimn);
                SCI3->SIOm1 = *gp_spi31_tx_address; /* started by writing data to SDR[7:0] */
                gp_spi31_tx_address++;
                #endif
                break;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_MasterReceive
* @brief  This function receives SPI00 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_MasterReceive(sci_spi_chmn spimn, uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio00 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi00_rx_count = rx_num;    /* receive data count */
                gp_spi00_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI0->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi01_rx_count = rx_num;    /* receive data count */
                gp_spi01_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI0->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi10_rx_count = rx_num;    /* receive data count */
                gp_spi10_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI1->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi11_rx_count = rx_num;    /* receive data count */
                gp_spi11_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI1->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi20_rx_count = rx_num;    /* receive data count */
                gp_spi20_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI2->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi21_rx_count = rx_num;    /* receive data count */
                gp_spi21_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI2->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi30_rx_count = rx_num;    /* receive data count */
                gp_spi30_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI3->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi31_rx_count = rx_num;    /* receive data count */
                gp_spi31_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(spimn);
                SCI3->SIOm1 = dummy_sio00;
                #endif
                break;
        }
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI00_SlaveInit
* @brief  This function initializes the SPI00 module. Slave transmission/reception operation.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
MD_STATUS SPI_SlaveInit(sci_spi_chmn spimn, spi_mode_t mode)
{
    MD_STATUS status;
    SCI_Type *SCIx;

    if ((spimn==SCI0_SPI00)|(spimn==SCI0_SPI01)){
        CGC->PERA  |= CGC_PERA_SCI0EN_Msk;
        SCIx = SCI0;
    }
    else if ((spimn==SCI1_SPI10)|(spimn==SCI1_SPI11)){
        CGC->PERA  |= CGC_PERA_SCI1EN_Msk;
        SCIx = SCI1;
    }
    else if ((spimn==SCI2_SPI20)|(spimn==SCI2_SPI21)){
        CGC->PERA  |= CGC_PERA_SCI2EN_Msk;
        SCIx = SCI2;
    }
    else if ((spimn==SCI3_SPI30)|(spimn==SCI3_SPI31)){
        CGC->PERA  |= CGC_PERA_SCI3EN_Msk;
        SCIx = SCI3;
    }
    else{
        return MD_ERROR;
    }

    // SCIx->ch0
    if ((spimn==SCI0_SPI00)|(spimn==SCI1_SPI10)|(spimn==SCI2_SPI20)|(spimn==SCI3_SPI30)){
        SCIx->ST    = _0001_SCI_CH0_STOP_TRG_ON;
        SCIx->SIRm0 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm0 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
        SCIx->SCRm0 = _C000_SCI_RECEPTION_TRANSMISSION | mode |  _0000_SCI_INTSRE_MASK |
                      _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0007_SCI_LENGTH_8;
        SCIx->SDRm0 = 0x0000;
        /* Set output enable */
        SCIx->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
    }
    // SCIx->ch1
    else{
        SCIx->ST = _0002_SCI_CH1_STOP_TRG_ON;
        SCIx->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
        SCIx->SCRm1 = _C000_SCI_RECEPTION_TRANSMISSION | mode | _0000_SCI_INTSRE_MASK |
                      _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0007_SCI_LENGTH_8;
        SCIx->SDRm1 = 0x0000;
        SCIx->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
    }
    switch (spimn){
        case SCI0_SPI00:
            #ifdef USE_SCI_SPI00
            /* Set SSn pin */
            SS00_PORT_SETTING();
            /* SS00 chip selection enable */
            MISC->ISC |= MISC_ISC_SSIE00_Msk;
            /* Set SCLK00 pin */
            SCLKI00_PORT_SETTING();
            /* Set SDI00 pin */
            SDI00_PORT_SETTING();
            /* Set SDO00 pin */
            SDO00_PORT_SETTING();
            #endif
            break;
        case SCI0_SPI01:
            #ifdef USE_SCI_SPI01
            /* Set SSn pin */
            SS01_PORT_SETTING();
            /* Set SCLK01 pin */
            SCLKI01_PORT_SETTING();
            /* Set SDI01 pin */
            SDI01_PORT_SETTING();
            /* Set SDO01 pin */
            SDO01_PORT_SETTING();
            #endif
            break;
        case SCI1_SPI10:
            #ifdef USE_SCI_SPI10
            /* Set SSn pin */
            SS10_PORT_SETTING();
            /* SS10 chip selection enable */
            MISC->ISC |= MISC_ISC_SSIE10_Msk;
            /* Set SCLK10 pin */
            SCLKI10_PORT_SETTING();
            /* Set SDI10 pin */
            SDI10_PORT_SETTING();
            /* Set SDO10 pin */
            SDO10_PORT_SETTING();
            #endif
            break;
        case SCI1_SPI11:
            #ifdef USE_SCI_SPI11
            /* Set SSn pin */
            SS11_PORT_SETTING();
            /* Set SCLK11 pin */
            SCLKI11_PORT_SETTING();
            /* Set SDI11 pin */
            SDI11_PORT_SETTING();
            /* Set SDO11 pin */
            SDO11_PORT_SETTING();
            #endif
            break;
        case SCI2_SPI20:
            #ifdef USE_SCI_SPI20
            /* Set SSn pin */
            SS20_PORT_SETTING();
            /* SS20 chip selection enable */
            MISC->ISC |= MISC_ISC_SSIE20_Msk;
            /* Set SCLK20 pin */
            SCLKI20_PORT_SETTING();
            /* Set SDI20 pin */
            SDI20_PORT_SETTING();
            /* Set SDO20 pin */
            SDO20_PORT_SETTING();
            #endif
            break;
        case SCI2_SPI21:
            #ifdef USE_SCI_SPI21
            /* Set SSn pin */
            SS21_PORT_SETTING();
            /* Set SCLK21 pin */
            SCLKI21_PORT_SETTING();
            /* Set SDI21 pin */
            SDI21_PORT_SETTING();
            /* Set SDO21 pin */
            SDO21_PORT_SETTING();
            #endif
            break;
        case SCI3_SPI30:
            #ifdef USE_SCI_SPI30
            /* Set SSn pin */
            SS30_PORT_SETTING();
            /* SS30 chip selection enable */
            MISC->ISC |= MISC_ISC_SSIE30_Msk;
            /* Set SCLK30 pin */
            SCLKI30_PORT_SETTING();
            /* Set SDI30 pin */
            SDI30_PORT_SETTING();
            /* Set SDO30 pin */
            SDO30_PORT_SETTING();
            #endif
            break;
        case SCI3_SPI31:
            #ifdef USE_SCI_SPI31
            /* Set SSn pin */
            SS31_PORT_SETTING();
            /* Set SCLK31 pin */
            SCLKI31_PORT_SETTING();
            /* Set SDI31 pin */
            SDI31_PORT_SETTING();
            /* Set SDO31 pin */
            SDO31_PORT_SETTING();
            #endif
            break;
    }

    status = MD_OK; 
    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI11_SlaveSendReceive
* @brief  This function sends and receives SPI11 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_SlaveSendReceive(sci_spi_chmn spimn, uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi00_rx_count = tx_num;    /* receive data count */
                g_spi00_tx_count = tx_num;    /* send data count */
                gp_spi00_tx_address = tx_buf; /* send buffer pointer */
                gp_spi00_rx_address = rx_buf; /* receive buffer pointer */

                g_spi00_tx_count--;
                SPI_Start(SCI0_SPI00);
                SCI0->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi00_tx_address++;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi01_rx_count = tx_num;    /* receive data count */
                g_spi01_tx_count = tx_num;    /* send data count */
                gp_spi01_tx_address = tx_buf; /* send buffer pointer */
                gp_spi01_rx_address = rx_buf; /* receive buffer pointer */

                g_spi01_tx_count--;
                SPI_Start(SCI0_SPI01);
                SCI0->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi01_tx_address++;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi10_rx_count = tx_num;    /* receive data count */
                g_spi10_tx_count = tx_num;    /* send data count */
                gp_spi10_tx_address = tx_buf; /* send buffer pointer */
                gp_spi10_rx_address = rx_buf; /* receive buffer pointer */

                g_spi10_tx_count--;
                SPI_Start(SCI1_SPI10);
                SCI1->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi10_tx_address++;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi11_rx_count = tx_num;    /* receive data count */
                g_spi11_tx_count = tx_num;    /* send data count */
                gp_spi11_tx_address = tx_buf; /* send buffer pointer */
                gp_spi11_rx_address = rx_buf; /* receive buffer pointer */

                g_spi11_tx_count--;
                SPI_Start(SCI1_SPI11);
                SCI1->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi11_tx_address++;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi20_rx_count = tx_num;    /* receive data count */
                g_spi20_tx_count = tx_num;    /* send data count */
                gp_spi20_tx_address = tx_buf; /* send buffer pointer */
                gp_spi20_rx_address = rx_buf; /* receive buffer pointer */

                g_spi20_tx_count--;
                SPI_Start(SCI2_SPI20);
                SCI2->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi20_tx_address++;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi21_rx_count = tx_num;    /* receive data count */
                g_spi21_tx_count = tx_num;    /* send data count */
                gp_spi21_tx_address = tx_buf; /* send buffer pointer */
                gp_spi21_rx_address = rx_buf; /* receive buffer pointer */

                g_spi21_tx_count--;
                SPI_Start(SCI2_SPI21);
                SCI2->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi21_tx_address++;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi30_rx_count = tx_num;    /* receive data count */
                g_spi30_tx_count = tx_num;    /* send data count */
                gp_spi30_tx_address = tx_buf; /* send buffer pointer */
                gp_spi30_rx_address = rx_buf; /* receive buffer pointer */

                g_spi30_tx_count--;
                SPI_Start(SCI3_SPI30);
                SCI3->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi30_tx_address++;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 |= _C000_SCI_RECEPTION_TRANSMISSION;

                g_spi31_rx_count = tx_num;    /* receive data count */
                g_spi31_tx_count = tx_num;    /* send data count */
                gp_spi31_tx_address = tx_buf; /* send buffer pointer */
                gp_spi31_rx_address = rx_buf; /* receive buffer pointer */

                g_spi31_tx_count--;
                SPI_Start(SCI3_SPI31);
                SCI3->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi31_tx_address++;
                #endif
                break;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_SlaveSend
* @brief  This function sends SPI00 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_SlaveSend(sci_spi_chmn spimn, uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi00_tx_count = tx_num;    /* send data count */

                gp_spi00_tx_address = tx_buf; /* send buffer pointer */

                g_spi00_tx_count--;
                SPI_Start(SCI0_SPI00);
                SCI0->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi00_tx_address++;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi01_tx_count = tx_num;    /* send data count */

                gp_spi01_tx_address = tx_buf; /* send buffer pointer */

                g_spi01_tx_count--;
                SPI_Start(SCI0_SPI01);
                SCI0->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi01_tx_address++;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi10_tx_count = tx_num;    /* send data count */

                gp_spi10_tx_address = tx_buf; /* send buffer pointer */

                g_spi10_tx_count--;
                SPI_Start(SCI1_SPI10);
                SCI1->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi10_tx_address++;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi11_tx_count = tx_num;    /* send data count */

                gp_spi11_tx_address = tx_buf; /* send buffer pointer */

                g_spi11_tx_count--;
                SPI_Start(SCI1_SPI11);
                SCI1->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi11_tx_address++;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi20_tx_count = tx_num;    /* send data count */

                gp_spi20_tx_address = tx_buf; /* send buffer pointer */

                g_spi20_tx_count--;
                SPI_Start(SCI2_SPI20);
                SCI2->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi20_tx_address++;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi21_tx_count = tx_num;    /* send data count */

                gp_spi21_tx_address = tx_buf; /* send buffer pointer */

                g_spi21_tx_count--;
                SPI_Start(SCI2_SPI21);
                SCI2->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi21_tx_address++;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm0 |= _8000_SCI_TRANSMISSION;

                g_spi30_tx_count = tx_num;    /* send data count */

                gp_spi30_tx_address = tx_buf; /* send buffer pointer */

                g_spi30_tx_count--;
                SPI_Start(SCI3_SPI30);
                SCI3->SIOm0 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi30_tx_address++;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm1 |= _8000_SCI_TRANSMISSION;

                g_spi31_tx_count = tx_num;    /* send data count */

                gp_spi31_tx_address = tx_buf; /* send buffer pointer */

                g_spi31_tx_count--;
                SPI_Start(SCI3_SPI31);
                SCI3->SIOm1 = tx_buf[0]; /* started by writing data to SDR[7:0] */
                gp_spi31_tx_address++;
                #endif
                break;
        }

    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_SlaveReceive
* @brief  This function receives SPI00 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_SlaveReceive(sci_spi_chmn spimn, uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio00 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        switch (spimn){
            case SCI0_SPI00:
                #ifdef USE_SCI_SPI00
                SCI0->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi00_rx_count = rx_num;    /* receive data count */

                gp_spi00_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI0_SPI00);
                SCI0->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI0_SPI01:
                #ifdef USE_SCI_SPI01
                SCI0->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI0->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi01_rx_count = rx_num;    /* receive data count */

                gp_spi01_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI0_SPI01);
                SCI0->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI1_SPI10:
                #ifdef USE_SCI_SPI10
                SCI1->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi10_rx_count = rx_num;    /* receive data count */

                gp_spi10_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI1_SPI10);
                SCI1->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI1_SPI11:
                #ifdef USE_SCI_SPI11
                SCI1->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI1->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi11_rx_count = rx_num;    /* receive data count */

                gp_spi11_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI1_SPI11);
                SCI1->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI2_SPI20:
                #ifdef USE_SCI_SPI20
                SCI2->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi20_rx_count = rx_num;    /* receive data count */

                gp_spi20_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI2_SPI20);
                SCI2->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI2_SPI21:
                #ifdef USE_SCI_SPI21
                SCI2->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI2->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi21_rx_count = rx_num;    /* receive data count */

                gp_spi21_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI2_SPI21);
                SCI2->SIOm1 = dummy_sio00;
                #endif
                break;
            case SCI3_SPI30:
                #ifdef USE_SCI_SPI30
                SCI3->SCRm0 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm0 |= _4000_SCI_RECEPTION;

                g_spi30_rx_count = rx_num;    /* receive data count */

                gp_spi30_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI3_SPI30);
                SCI3->SIOm0 = dummy_sio00;
                #endif
                break;
            case SCI3_SPI31:
                #ifdef USE_SCI_SPI31
                SCI3->SCRm1 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
                SCI3->SCRm1 |= _4000_SCI_RECEPTION;

                g_spi31_rx_count = rx_num;    /* receive data count */

                gp_spi31_rx_address = rx_buf; /* receive buffer pointer */

                SPI_Start(SCI3_SPI31);
                SCI3->SIOm1 = dummy_sio00;
                #endif
                break;
        }
    }

    return (status);
}

#endif

#if 1
/***********************************************************************************************************************
* Function Name: IIC00_Init
* @brief  This function initializes the IIC00 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC_Init(sci_iic_chmn iicmn)
{
    SCI_Type *SCIx;

    if ((iicmn==SCI0_IIC00)|(iicmn==SCI0_IIC01)){
        CGC->PERA  |= CGC_PERA_SCI0EN_Msk;
        SCIx = SCI0;
    }
    else if ((iicmn==SCI1_IIC10)|(iicmn==SCI1_IIC11)){
        CGC->PERA  |= CGC_PERA_SCI1EN_Msk;
        SCIx = SCI1;
    }
    else if ((iicmn==SCI2_IIC20)|(iicmn==SCI2_IIC21)){
        CGC->PERA  |= CGC_PERA_SCI2EN_Msk;
        SCIx = SCI2;
    }
    else if ((iicmn==SCI3_IIC30)|(iicmn==SCI3_IIC31)){
        CGC->PERA  |= CGC_PERA_SCI3EN_Msk;
        SCIx = SCI3;
    }
    else{
        return;
    }

    //SCIx->SPS = _0000_SCI_CK01_fCLK_0 | _0000_SCI_CK00_fCLK_0;
    //SCIx->SPS = _0040_SCI_CK01_fCLK_4 | _0004_SCI_CK00_fCLK_4;

    // SCIx->ch0
    if ((iicmn==SCI0_IIC00)|(iicmn==SCI1_IIC10)|(iicmn==SCI2_IIC20)|(iicmn==SCI3_IIC30)){
        SCIx->SPS &= (uint16_t)(~SCI0_SPS0_PRS00_Msk);
        SCIx->SPS |= _0001_SCI_CK00_fCLK_1;

        SCIx->ST    = _0001_SCI_CH0_STOP_TRG_ON;
        SCIx->SIRm0 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm0 = (uint16_t)(_0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END);
        SCIx->SCRm0 = _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                      _0000_SCI_MSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
        SCIx->SDRm0 = _3000_SCI_BAUDRATE_DIVISOR;
        SCIx->SO   |= _0100_SCI_CH0_CLOCK_OUTPUT_1 | _0001_SCI_CH0_DATA_OUTPUT_1;
    }
    // SCIx->ch1
    else{
        SCIx->SPS &= (uint16_t)(~SCI0_SPS0_PRS01_Msk);
        SCIx->SPS |= _0010_SCI_CK01_fCLK_1;

        SCIx->ST    = _0002_SCI_CH1_STOP_TRG_ON;
        SCIx->SIRm1 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
        SCIx->SMRm1 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                      _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
        SCIx->SCRm1 = _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                      _0000_SCI_MSB | _0010_SCI_STOP_1 | _0007_SCI_LENGTH_8;
        SCIx->SDRm1 = _3000_SCI_BAUDRATE_DIVISOR;//_CE00_SCI_BAUDRATE_DIVISOR;
        SCIx->SO   |= _0200_SCI_CH1_CLOCK_OUTPUT_1 | _0002_SCI_CH1_DATA_OUTPUT_1;
    }

    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            /* Set SCL00 pin */
            SCL00_PORT_SETTING();
            /* Set SDA00 pin */
            SDA00_PORT_SETTING();
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            /* Set SCL01 pin */
            SCL01_PORT_SETTING();
            /* Set SDA01 pin */
            SDA01_PORT_SETTING();
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            /* Set SCL10 pin */
            SCL10_PORT_SETTING();
            /* Set SDA10 pin */
            SDA10_PORT_SETTING();
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            /* Set SCL11 pin */
            SCL11_PORT_SETTING();
            /* Set SDA11 pin */
            SDA11_PORT_SETTING();
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            /* Set SCL20 pin */
            SCL20_PORT_SETTING();
            /* Set SDA20 pin */
            SDA20_PORT_SETTING();
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            /* Set SCL21 pin */
            SCL21_PORT_SETTING();
            /* Set SDA21 pin */
            SDA21_PORT_SETTING();
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            /* Set SCL30 pin */
            SCL30_PORT_SETTING();
            /* Set SDA30 pin */
            SDA30_PORT_SETTING();
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            /* Set SCL31 pin */
            SCL31_PORT_SETTING();
            /* Set SDA31 pin */
            SDA31_PORT_SETTING();
            #endif
            break;
    }

}
/***********************************************************************************************************************
* Function Name: IIC00_MasterSend
* @brief  This function starts transferring data for IIC00 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC_MasterSend(sci_iic_chmn iicmn, uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC00 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic00_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI0->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI0->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic00_tx_count = tx_num;
            gp_iic00_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
            NVIC_EnableIRQ(IIC00_IRQn);       /* enable INTIIC00 interrupt flag */
            NVIC_SetPriority(IIC00_IRQn, 3);  /* low priority */
            SCI0->SIOm0 = adr;
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            g_iic01_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC01 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic01_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI0->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI0->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic01_tx_count = tx_num;
            gp_iic01_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
            NVIC_EnableIRQ(IIC01_IRQn);       /* enable INTIIC01 interrupt flag */
            NVIC_SetPriority(IIC01_IRQn, 3);  /* low priority */
            SCI0->SIOm1 = adr;
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC10 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic10_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI1->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI1->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic10_tx_count = tx_num;
            gp_iic10_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
            NVIC_EnableIRQ(IIC10_IRQn);       /* enable INTIIC10 interrupt flag */
            NVIC_SetPriority(IIC10_IRQn, 3);  /* low priority */
            SCI1->SIOm0 = adr;
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            g_iic11_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC11 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic11_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI1->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI1->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic11_tx_count = tx_num;
            gp_iic11_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
            NVIC_EnableIRQ(IIC11_IRQn);       /* enable INTIIC11 interrupt flag */
            NVIC_SetPriority(IIC11_IRQn, 3);  /* low priority */
            SCI1->SIOm1 = adr;
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC20 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic20_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI2->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI2->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic20_tx_count = tx_num;
            gp_iic20_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
            NVIC_EnableIRQ(IIC20_IRQn);       /* enable INTIIC20 interrupt flag */
            NVIC_SetPriority(IIC20_IRQn, 3);  /* low priority */
            SCI2->SIOm0 = adr;
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            g_iic21_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC21 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic21_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI2->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI2->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic21_tx_count = tx_num;
            gp_iic21_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
            NVIC_EnableIRQ(IIC21_IRQn);       /* enable INTIIC21 interrupt flag */
            NVIC_SetPriority(IIC21_IRQn, 3);  /* low priority */
            SCI2->SIOm1 = adr;
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            g_iic30_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC30 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic30_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI3->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI3->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic30_tx_count = tx_num;
            gp_iic30_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC30_IRQn); /* clear INTIIC30 interrupt flag */
            NVIC_EnableIRQ(IIC30_IRQn);       /* enable INTIIC30 interrupt flag */
            NVIC_SetPriority(IIC30_IRQn, 3);  /* low priority */
            SCI3->SIOm0 = adr;
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            g_iic31_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC31 master status flag */
            adr &= 0xFEU;                                         /* send mode */
            g_iic31_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
            SCI3->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI3->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set paramater */
            g_iic31_tx_count = tx_num;
            gp_iic31_tx_address = tx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC31_IRQn); /* clear INTIIC31 interrupt flag */
            NVIC_EnableIRQ(IIC31_IRQn);       /* enable INTIIC31 interrupt flag */
            NVIC_SetPriority(IIC31_IRQn, 3);  /* low priority */
            SCI3->SIOm1 = adr;
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: IIC00_MasterReceive
* @brief  This function starts receiving data for IIC00 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC_MasterReceive(sci_iic_chmn iicmn, uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic00_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI0->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI0->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic00_rx_length = rx_num;
            g_iic00_rx_count = 0U;
            gp_iic00_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
            NVIC_EnableIRQ(IIC00_IRQn);       /* enable INTIIC00 interrupt flag */
            NVIC_SetPriority(IIC00_IRQn, 3);  /* low priority */
            SCI0->SIOm0 = adr;
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            g_iic01_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic01_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI0->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI0->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic01_rx_length = rx_num;
            g_iic01_rx_count = 0U;
            gp_iic01_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
            NVIC_EnableIRQ(IIC01_IRQn);       /* enable INTIIC01 interrupt flag */
            NVIC_SetPriority(IIC01_IRQn, 3);  /* low priority */
            SCI0->SIOm1 = adr;
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic10_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI1->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI1->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic10_rx_length = rx_num;
            g_iic10_rx_count = 0U;
            gp_iic10_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
            NVIC_EnableIRQ(IIC10_IRQn);       /* enable INTIIC10 interrupt flag */
            NVIC_SetPriority(IIC10_IRQn, 3);  /* low priority */
            SCI1->SIOm0 = adr;
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            g_iic11_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic11_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI1->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI1->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic11_rx_length = rx_num;
            g_iic11_rx_count = 0U;
            gp_iic11_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
            NVIC_EnableIRQ(IIC11_IRQn);       /* enable INTIIC11 interrupt flag */
            NVIC_SetPriority(IIC11_IRQn, 3);  /* low priority */
            SCI1->SIOm1 = adr;
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic20_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI2->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI2->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic20_rx_length = rx_num;
            g_iic20_rx_count = 0U;
            gp_iic20_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
            NVIC_EnableIRQ(IIC20_IRQn);       /* enable INTIIC20 interrupt flag */
            NVIC_SetPriority(IIC20_IRQn, 3);  /* low priority */
            SCI2->SIOm0 = adr;
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            g_iic21_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic21_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI2->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI2->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic21_rx_length = rx_num;
            g_iic21_rx_count = 0U;
            gp_iic21_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
            NVIC_EnableIRQ(IIC21_IRQn);       /* enable INTIIC21 interrupt flag */
            NVIC_SetPriority(IIC21_IRQn, 3);  /* low priority */
            SCI2->SIOm1 = adr;
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            g_iic30_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic30_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI3->SCRm0 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI3->SCRm0 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic30_rx_length = rx_num;
            g_iic30_rx_count = 0U;
            gp_iic30_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC30_IRQn); /* clear INTIIC30 interrupt flag */
            NVIC_EnableIRQ(IIC30_IRQn);       /* enable INTIIC30 interrupt flag */
            NVIC_SetPriority(IIC30_IRQn, 3);  /* low priority */
            SCI3->SIOm0 = adr;
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            g_iic31_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
            adr |= 0x01U;                                          /* receive mode */
            g_iic31_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
            SCI3->SCRm1 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
            SCI3->SCRm1 |= _8000_SCI_TRANSMISSION;
            /* Set parameter */
            g_iic31_rx_length = rx_num;
            g_iic31_rx_count = 0U;
            gp_iic31_rx_address = rx_buf;
            /* Start condition */
            IIC_StartCondition(iicmn);
            NVIC_ClearPendingIRQ(IIC31_IRQn); /* clear INTIIC31 interrupt flag */
            NVIC_EnableIRQ(IIC31_IRQn);       /* enable INTIIC31 interrupt flag */
            NVIC_SetPriority(IIC31_IRQn, 3);  /* low priority */
            SCI3->SIOm1 = adr;
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: IIC00_Stop
* @brief  This function stops the IIC00 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC_Stop(sci_iic_chmn iicmn)
{
    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            NVIC_DisableIRQ(IIC00_IRQn); /* disable INTIIC00 interrupt flag */
            SCI0->ST  = _0001_SCI_CH0_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            NVIC_DisableIRQ(IIC01_IRQn); /* disable INTIIC00 interrupt flag */
            SCI0->ST  = _0002_SCI_CH1_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC00 interrupt flag */
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            NVIC_DisableIRQ(IIC10_IRQn); /* disable INTIIC10 interrupt flag */
            SCI1->ST  = _0001_SCI_CH0_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            NVIC_DisableIRQ(IIC11_IRQn); /* disable INTIIC11 interrupt flag */
            SCI1->ST  = _0002_SCI_CH1_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            NVIC_DisableIRQ(IIC20_IRQn); /* disable INTIIC20 interrupt flag */
            SCI2->ST  = _0001_SCI_CH0_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            NVIC_DisableIRQ(IIC21_IRQn); /* disable INTIIC21 interrupt flag */
            SCI2->ST  = _0002_SCI_CH1_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            NVIC_DisableIRQ(IIC30_IRQn); /* disable INTIIC30 interrupt flag */
            SCI3->ST  = _0001_SCI_CH0_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC30_IRQn); /* clear INTIIC30 interrupt flag */
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            NVIC_DisableIRQ(IIC31_IRQn); /* disable INTIIC31 interrupt flag */
            SCI3->ST  = _0002_SCI_CH1_STOP_TRG_ON;
            NVIC_ClearPendingIRQ(IIC31_IRQn); /* clear INTIIC31 interrupt flag */
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: IIC00_StartCondition
* @brief  This function starts IIC00 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC_StartCondition(sci_iic_chmn iicmn)
{
    volatile uint8_t w_count;

    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            SCI0->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI0->SO  &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
            SCI0->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI0->SS   = _0001_SCI_CH0_START_TRG_ON;
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            SCI0->SO &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI0->SO &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
            SCI0->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI0->SS   = _0002_SCI_CH1_START_TRG_ON;
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            SCI1->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI1->SO  &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
            SCI1->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI1->SS   = _0001_SCI_CH0_START_TRG_ON;
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            SCI1->SO &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI1->SO &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
            SCI1->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI1->SS   = _0002_SCI_CH1_START_TRG_ON;
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            SCI2->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI2->SO  &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
            SCI2->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI2->SS   = _0001_SCI_CH0_START_TRG_ON;
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            SCI2->SO &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI2->SO &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
            SCI2->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI2->SS   = _0002_SCI_CH1_START_TRG_ON;
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            SCI3->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI3->SO  &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
            SCI3->SOE |= _0001_SCI_CH0_OUTPUT_ENABLE;
            SCI3->SS   = _0001_SCI_CH0_START_TRG_ON;
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            SCI2->SO &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI2->SO &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
            SCI2->SOE |= _0002_SCI_CH1_OUTPUT_ENABLE;
            SCI2->SS   = _0002_SCI_CH1_START_TRG_ON;
            #endif
            break;
    }
}
/***********************************************************************************************************************
* Function Name: IIC00_StopCondition
* @brief  This function stops IIC00 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC_StopCondition(sci_iic_chmn iicmn)
{
    volatile uint8_t w_count;

    switch (iicmn){
        case SCI0_IIC00:
            #ifdef USE_SCI_IIC00
            g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC00 master status flag */
            SCI0->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI0->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            SCI0->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
            SCI0->SO  |= (uint16_t) _0100_SCI_CH0_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI0->SO  |= _0001_SCI_CH0_DATA_OUTPUT_1;
            #endif
            break;
        case SCI0_IIC01:
            #ifdef USE_SCI_IIC01
            g_iic01_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC01 master status flag */
            SCI0->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI0->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            SCI0->SO  &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
            SCI0->SO  |= (uint16_t) _0200_SCI_CH1_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI0->SO |= _0002_SCI_CH1_DATA_OUTPUT_1;
            #endif
            break;
        case SCI1_IIC10:
            #ifdef USE_SCI_IIC10
            g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC10 master status flag */
            SCI1->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI1->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            SCI1->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
            SCI1->SO  |= (uint16_t) _0100_SCI_CH0_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI1->SO  |= _0001_SCI_CH0_DATA_OUTPUT_1;
            #endif
            break;
        case SCI1_IIC11:
            #ifdef USE_SCI_IIC11
            g_iic11_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC11 master status flag */
            SCI1->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI1->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            SCI1->SO  &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
            SCI1->SO  |= (uint16_t) _0200_SCI_CH1_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI1->SO |= _0002_SCI_CH1_DATA_OUTPUT_1;
            #endif
            break;
        case SCI2_IIC20:
            #ifdef USE_SCI_IIC20
            g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC20 master status flag */
            SCI2->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI2->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            SCI2->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
            SCI2->SO  |= (uint16_t) _0100_SCI_CH0_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI2->SO  |= _0001_SCI_CH0_DATA_OUTPUT_1;
            #endif
            break;
        case SCI2_IIC21:
            #ifdef USE_SCI_IIC21
            g_iic21_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC21 master status flag */
            SCI2->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI2->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            SCI2->SO  &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
            SCI2->SO  |= (uint16_t) _0200_SCI_CH1_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI2->SO |= _0002_SCI_CH1_DATA_OUTPUT_1;
            #endif
            break;
        case SCI3_IIC30:
            #ifdef USE_SCI_IIC30
            g_iic30_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC30 master status flag */
            SCI3->ST   = _0001_SCI_CH0_STOP_TRG_ON;
            SCI3->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
            SCI3->SO  &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
            SCI3->SO  |= (uint16_t) _0100_SCI_CH0_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI3->SO  |= _0001_SCI_CH0_DATA_OUTPUT_1;
            #endif
            break;
        case SCI3_IIC31:
            #ifdef USE_SCI_IIC31
            g_iic31_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC31 master status flag */
            SCI3->ST   = _0002_SCI_CH1_STOP_TRG_ON;
            SCI3->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
            SCI3->SO  &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
            SCI3->SO  |= (uint16_t) _0200_SCI_CH1_CLOCK_OUTPUT_1;

            /* Change the waiting time according to the system */
            for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
            {
                __NOP();
            }

            SCI3->SO |= _0002_SCI_CH1_DATA_OUTPUT_1;
            #endif
            break;
    }
}
#endif

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

