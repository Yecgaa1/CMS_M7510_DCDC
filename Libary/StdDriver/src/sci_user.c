/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    sci_user.c
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2022/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G439.h"
#include "sci.h"
#include <stdint.h>

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wcomment"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
extern void IRQ11_Handler(void);
extern void IRQ12_Handler(void);
extern void IRQ13_Handler(void);
extern void IRQ14_Handler(void);
extern void IRQ15_Handler(void);
extern void IRQ16_Handler(void);
extern void IRQ17_Handler(void);
extern void IRQ18_Handler(void);
extern void IRQ19_Handler(void);
extern void IRQ20_Handler(void);
extern void IRQ21_Handler(void);
extern void IRQ22_Handler(void);

#if defined USE_SCI_UART0_TX
void uart0_interrupt_send(void);
void IRQ11_Handler(void) __attribute__((alias("uart0_interrupt_send")));
#elif defined USE_SCI_SPI00
void spi00_interrupt (void);
void IRQ11_Handler(void) __attribute__((alias("spi00_interrupt")));
#elif defined USE_SCI_IIC00
void iic00_interrupt (void);
void IRQ11_Handler(void) __attribute__((alias("iic00_interrupt")));
#endif

#if defined USE_SCI_UART0_RX
void uart0_interrupt_receive(void);
void IRQ12_Handler(void) __attribute__((alias("uart0_interrupt_receive")));
#elif defined USE_SCI_SPI01
void spi01_interrupt (void);
void IRQ12_Handler(void) __attribute__((alias("spi01_interrupt")));
#elif defined USE_SCI_IIC01
void iic01_interrupt (void);
void IRQ12_Handler(void) __attribute__((alias("iic01_interrupt")));
#endif

#if defined USE_SCI_UART1_TX
void uart1_interrupt_send(void);
void IRQ14_Handler(void) __attribute__((alias("uart1_interrupt_send")));
#elif defined USE_SCI_SPI10
void spi10_interrupt (void);
void IRQ14_Handler(void) __attribute__((alias("spi10_interrupt")));
#elif defined USE_SCI_IIC10
void iic10_interrupt (void);
void IRQ14_Handler(void) __attribute__((alias("iic10_interrupt")));
#endif

#if defined USE_SCI_UART1_RX
void uart1_interrupt_receive(void);
void IRQ15_Handler(void) __attribute__((alias("uart1_interrupt_receive")));
#elif defined USE_SCI_SPI11
void spi11_interrupt (void);
void IRQ15_Handler(void) __attribute__((alias("spi11_interrupt")));
#elif defined USE_SCI_IIC11
void iic11_interrupt (void);
void IRQ15_Handler(void) __attribute__((alias("iic11_interrupt")));
#endif

#if defined USE_SCI_UART2_TX 
void uart2_interrupt_send(void);
void IRQ17_Handler(void) __attribute__((alias("uart2_interrupt_send")));
#elif defined USE_SCI_SPI20
void spi20_interrupt (void);
void IRQ17_Handler(void) __attribute__((alias("spi20_interrupt")));
#elif defined USE_SCI_IIC20
void iic20_interrupt (void);
void IRQ17_Handler(void) __attribute__((alias("iic20_interrupt")));
#endif

#if defined USE_SCI_UART2_RX
void uart2_interrupt_receive(void);
void IRQ18_Handler(void) __attribute__((alias("uart2_interrupt_receive")));
#elif defined USE_SCI_SPI21
void spi21_interrupt (void);
void IRQ18_Handler(void) __attribute__((alias("spi21_interrupt")));
#elif defined USE_SCI_IIC21
void iic21_interrupt (void);
void IRQ18_Handler(void) __attribute__((alias("iic21_interrupt")));
#endif

#if defined USE_SCI_UART3_TX 
void uart3_interrupt_send(void);
void IRQ20_Handler(void) __attribute__((alias("uart3_interrupt_send")));
#elif defined USE_SCI_SPI30
void spi30_interrupt (void);
void IRQ20_Handler(void) __attribute__((alias("spi30_interrupt")));
#elif defined USE_SCI_IIC30
void iic30_interrupt (void);
void IRQ20_Handler(void) __attribute__((alias("iic30_interrupt")));
#endif

#if defined USE_SCI_UART3_RX
void uart3_interrupt_receive(void);
void IRQ21_Handler(void) __attribute__((alias("uart3_interrupt_receive")));
#elif defined USE_SCI_SPI31
void spi31_interrupt (void);
void IRQ21_Handler(void) __attribute__((alias("spi31_interrupt")));
#elif defined USE_SCI_IIC31
void iic31_interrupt (void);
void IRQ21_Handler(void) __attribute__((alias("iic31_interrupt")));
#endif

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

#if defined USE_SCI_UART0_TX | defined USE_SCI_UART0_RX
static void uart0_callback_receiveend(void);
static void uart0_callback_softwareoverrun(uint16_t rx_data);
static void uart0_callback_sendend(void);
static void uart0_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI00
static void spi00_callback_receiveend(void);
static void spi00_callback_sendend(void);
static void spi00_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI01
static void spi01_callback_receiveend(void);
static void spi01_callback_sendend(void);
static void spi01_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_IIC00
static void iic00_callback_master_receiveend(void);
static void iic00_callback_master_sendend(void);
static void iic00_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_IIC01
static void iic01_callback_master_receiveend(void);
static void iic01_callback_master_sendend(void);
static void iic01_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_UART1_TX | defined USE_SCI_UART1_RX
static void uart1_callback_receiveend(void);
static void uart1_callback_softwareoverrun(uint16_t rx_data);
static void uart1_callback_sendend(void);
static void uart1_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI10
static void spi10_callback_receiveend(void);
static void spi10_callback_sendend(void);
static void spi10_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI11
static void spi11_callback_receiveend(void);
static void spi11_callback_sendend(void);
static void spi11_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_IIC10
static void iic10_callback_master_receiveend(void);
static void iic10_callback_master_sendend(void);
static void iic10_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_IIC11
static void iic11_callback_master_receiveend(void);
static void iic11_callback_master_sendend(void);
static void iic11_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_UART2_TX | defined USE_SCI_UART2_RX
static void uart2_callback_receiveend(void);
static void uart2_callback_softwareoverrun(uint16_t rx_data);
static void uart2_callback_sendend(void);
static void uart2_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI20
static void spi20_callback_receiveend(void);
static void spi20_callback_sendend(void);
static void spi20_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI21
static void spi21_callback_receiveend(void);
static void spi21_callback_sendend(void);
static void spi21_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_IIC20
static void iic20_callback_master_receiveend(void);
static void iic20_callback_master_sendend(void);
static void iic20_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_IIC21
static void iic21_callback_master_receiveend(void);
static void iic21_callback_master_sendend(void);
static void iic21_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_UART3_TX | defined USE_SCI_UART3_RX
static void uart3_callback_receiveend(void);
static void uart3_callback_softwareoverrun(uint16_t rx_data);
static void uart3_callback_sendend(void);
static void uart3_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI30
static void spi30_callback_receiveend(void);
static void spi30_callback_sendend(void);
static void spi30_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_SPI31
static void spi31_callback_receiveend(void);
static void spi31_callback_sendend(void);
static void spi31_callback_error(uint8_t err_type);
#endif
#if defined USE_SCI_IIC30
static void iic30_callback_master_receiveend(void);
static void iic30_callback_master_sendend(void);
static void iic30_callback_master_error(MD_STATUS flag);
#endif
#if defined USE_SCI_IIC31
static void iic31_callback_master_receiveend(void);
static void iic31_callback_master_sendend(void);
static void iic31_callback_master_error(MD_STATUS flag);
#endif

volatile uint8_t g_iic00_tx_end;                /* iic00 send data end */
volatile uint8_t g_iic00_rx_end;                /* iic00 receive data end */
volatile uint8_t g_iic01_tx_end;                /* iic01 send data end */
volatile uint8_t g_iic01_rx_end;                /* iic01 receive data end */
volatile uint8_t g_iic10_tx_end;                /* iic10 send data end */
volatile uint8_t g_iic10_rx_end;                /* iic10 receive data end */
volatile uint8_t g_iic11_tx_end;                /* iic11 send data end */
volatile uint8_t g_iic11_rx_end;                /* iic11 receive data end */
volatile uint8_t g_iic20_tx_end;                /* iic20 send data end */
volatile uint8_t g_iic20_rx_end;                /* iic20 receive data end */
volatile uint8_t g_iic21_tx_end;                /* iic21 send data end */
volatile uint8_t g_iic21_rx_end;                /* iic21 receive data end */
volatile uint8_t g_iic30_tx_end;                /* iic30 send data end */
volatile uint8_t g_iic30_rx_end;                /* iic30 receive data end */
volatile uint8_t g_iic31_tx_end;                /* iic31 send data end */
volatile uint8_t g_iic31_rx_end;                /* iic31 receive data end */


/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

#if defined USE_SCI_UART0_RX
void uart0_interrupt_receive(void);
/***********************************************************************************************************************
* Function Name: uart0_interrupt_receive
* @brief  UART0 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart0_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    NVIC_ClearPendingIRQ(SR0_IRQn);
    err_type = (uint8_t)(SCI0->SSRm1 & 0x0007U);
    SCI0->SIRm1 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart0_callback_error(err_type);
    }
    
    rx_data = SCI0->RXD;

    if (g_uart0_rx_length > g_uart0_rx_count)
    {
        *gp_uart0_rx_address = rx_data;
        gp_uart0_rx_address++;
        g_uart0_rx_count++;

        if (g_uart0_rx_length == g_uart0_rx_count)
        {
            uart0_callback_receiveend();
        }
    }
    else
    {
        uart0_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: uart0_callback_receiveend
* @brief  This function is a callback function when UART0 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart0_callback_softwareoverrun
* @brief  This function is a callback function when UART0 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart0_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart0_callback_error
* @brief  This function is a callback function when UART0 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart0_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART0_TX
void uart0_interrupt_send(void);
/***********************************************************************************************************************
* Function Name: uart0_interrupt_send
* @brief  UART0 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart0_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST0_IRQn);
    if (g_uart0_tx_count > 0U)
    {
        SCI0->TXD = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
    }
    else
    {
        uart0_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: uart0_callback_sendend
* @brief  This function is a callback function when UART0 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI00
/***********************************************************************************************************************
* Function Name: spi00_interrupt
* @brief  SPI00 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi00_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    NVIC_ClearPendingIRQ(SPI00_IRQn);
    err_type = (uint8_t)(SCI0->SSRm0 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIRm0 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi00_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi00_tx_count > 0U || g_spi00_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi00_rx_address)
            {
                *gp_spi00_rx_address = SCI0->SIOm0;
                gp_spi00_rx_address++;
                g_spi00_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIOm0;
            }

            /* send data */
            if (0U != gp_spi00_tx_address)
            {
                SCI0->SIOm0 = *gp_spi00_tx_address;
                gp_spi00_tx_address++;
                g_spi00_tx_count--;
            }
            else if((SCI0->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIOm0 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi00_rx_count)
            {
                while ((SCI0->SSRm0 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi00_rx_address)
                {
                    *gp_spi00_rx_address = SCI0->SIOm0;
                     g_spi00_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIOm0;
                }
                spi00_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi00_tx_address)
            {
                if (((SCI0->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCRm0 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSRm0 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi00_callback_sendend();    /* complete send */
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: spi00_callback_receiveend
* @brief  This function is a callback function when spi00 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi00_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI0_SPI00);
    gp_spi00_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi00_callback_error
* @brief  This function is a callback function when spi00 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi00_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi00_callback_sendend
* @brief  This function is a callback function when spi00 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI0_SPI00);
    gp_spi00_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI01
/***********************************************************************************************************************
* Function Name: spi01_interrupt
* @brief  SPI01 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi01_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI0->SSRm1 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIRm1 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi01_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi01_tx_count > 0U || g_spi01_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi01_rx_address)
            {
                *gp_spi01_rx_address = SCI0->SIOm1;
                gp_spi01_rx_address++;
                g_spi01_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIOm1;
            }

            /* send data */
            if (0U != gp_spi01_tx_address)
            {
                SCI0->SIOm1 = *gp_spi01_tx_address;
                gp_spi01_tx_address++;
                g_spi01_tx_count--;
            }
            else if((SCI0->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIOm1 = 0xFFU;   // dummy write in master reception mode
            }

        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi01_rx_count)
            {
                while ((SCI0->SSRm1 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi01_rx_address)
                {
                    *gp_spi01_rx_address = SCI0->SIOm1;
                     g_spi01_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIOm1;
                }
                spi01_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi01_tx_address)
            {
                if (((SCI0->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCRm1 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSRm1 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi01_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI01_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi01_callback_receiveend
* @brief  This function is a callback function when spi01 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi01_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI0_SPI01);
    gp_spi01_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi01_callback_error
* @brief  This function is a callback function when spi01 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi01_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi01_callback_sendend
* @brief  This function is a callback function when spi01 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi01_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI0_SPI01);
    gp_spi01_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC00
/***********************************************************************************************************************
* Function Name: iic00_interrupt
* @brief  IIC00 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iic00_interrupt(void)
{
    if (((SCI0->SSRm0 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic00_tx_count != 0U))
    {
        iic00_callback_master_error(MD_NACK);
    }
    else if(((SCI0->SSRm0 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic00_tx_count != 0U))
    {
        iic00_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic00_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic00_tx_count > 0U)
            {
                SCI0->SIOm0 = *gp_iic00_tx_address;
                gp_iic00_tx_address++;
                g_iic00_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI0_IIC00);
                iic00_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic00_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI0->ST |= _0001_SCI_CH0_STOP_TRG_ON;
                SCI0->SCRm0 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI0->SCRm0 |= _4000_SCI_RECEPTION;
                SCI0->SS |= _0001_SCI_CH0_START_TRG_ON;
                g_iic00_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic00_rx_length == 1U)
                {
                    SCI0->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI0->SIOm0 = 0xFFU;
            }
            else
            {
                if (g_iic00_rx_count < g_iic00_rx_length)
                {
                    *gp_iic00_rx_address = SCI0->SIOm0;
                    gp_iic00_rx_address++;
                    g_iic00_rx_count++;
                    
                    if (g_iic00_rx_count == (g_iic00_rx_length - 1U))
                    {
                        SCI0->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI0->SIOm0 = 0xFFU;
                    }
                    else if (g_iic00_rx_count == g_iic00_rx_length)
                    {
                        IIC_StopCondition(SCI0_IIC00);
                        iic00_callback_master_receiveend();
                    }
                    else
                    {
                        SCI0->SIOm0 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC00_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_error
* @brief  This function is a callback function when IIC00 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic00_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_receiveend
* @brief  This function is a callback function when IIC00 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic00_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic00_rx_end = 1;
    IIC_Stop(SCI0_IIC00);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_sendend
* @brief  This function is a callback function when IIC00 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic00_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic00_tx_end = 1;
    IIC_Stop(SCI0_IIC00);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC01
/***********************************************************************************************************************
* Function Name: iic01_interrupt
* @brief  IIC01 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
void iic01_interrupt(void)
{
    if (((SCI0->SSRm1 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic01_tx_count != 0U))
    {
        iic01_callback_master_error(MD_NACK);
    }
    else if(((SCI0->SSRm1 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic01_tx_count != 0U))
    {
        iic01_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic01_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic01_tx_count > 0U)
            {
                SCI0->SIOm1 = *gp_iic01_tx_address;
                gp_iic01_tx_address++;
                g_iic01_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI0_IIC01);
                iic01_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic01_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI0->ST |= _0002_SCI_CH1_STOP_TRG_ON;
                SCI0->SCRm1 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI0->SCRm1 |= _4000_SCI_RECEPTION;
                SCI0->SS |= _0002_SCI_CH1_START_TRG_ON;
                g_iic01_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic01_rx_length == 1U)
                {
                    SCI0->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI0->SIOm1 = 0xFFU;
            }
            else
            {
                if (g_iic01_rx_count < g_iic01_rx_length)
                {
                    *gp_iic01_rx_address = SCI0->SIOm1;
                    gp_iic01_rx_address++;
                    g_iic01_rx_count++;
                    
                    if (g_iic01_rx_count == (g_iic01_rx_length - 1U))
                    {
                        SCI0->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI0->SIOm1 = 0xFFU;
                    }
                    else if (g_iic01_rx_count == g_iic01_rx_length)
                    {
                        IIC_StopCondition(SCI0_IIC01);
                        iic01_callback_master_receiveend();
                    }
                    else
                    {
                        SCI0->SIOm1 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC01_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_error
* @brief  This function is a callback function when IIC01 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_receiveend
* @brief  This function is a callback function when IIC01 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic01_rx_end = 1;
    IIC_Stop(SCI0_IIC01);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_sendend
* @brief  This function is a callback function when IIC01 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic01_tx_end = 1;
    IIC_Stop(SCI0_IIC01);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART1_RX
/***********************************************************************************************************************
* Function Name: uart1_interrupt_receive
* @brief  UART1 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart1_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    NVIC_ClearPendingIRQ(SR1_IRQn);
    err_type = (uint8_t)(SCI1->SSRm1 & 0x0007U);
    SCI1->SIRm1 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart1_callback_error(err_type);
    }
    
    rx_data = SCI0->RXD1;

    if (g_uart1_rx_length > g_uart1_rx_count)
    {
        *gp_uart1_rx_address = rx_data;
        gp_uart1_rx_address++;
        g_uart1_rx_count++;

        if (g_uart1_rx_length == g_uart1_rx_count)
        {
            uart1_callback_receiveend();
        }
    }
    else
    {
        uart1_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: uart1_callback_receiveend
* @brief  This function is a callback function when UART1 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart1_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_callback_softwareoverrun
* @brief  This function is a callback function when UART1 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart1_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_callback_error
* @brief  This function is a callback function when UART1 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart1_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART1_TX
static void uart1_callback_sendend(void);
/***********************************************************************************************************************
* Function Name: uart1_interrupt_send
* @brief  UART1 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart1_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST1_IRQn);
    if (g_uart1_tx_count > 0U)
    {
        SCI1->TXD = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    }
    else
    {
        uart1_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: uart1_callback_sendend
* @brief  This function is a callback function when UART1 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart1_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI10
/***********************************************************************************************************************
* Function Name: spi10_interrupt
* @brief  SPI10 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi10_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    NVIC_ClearPendingIRQ(SPI10_IRQn);
    err_type = (uint8_t)(SCI1->SSRm0 & _0001_SCI_OVERRUN_ERROR);
    SCI1->SIRm0 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi10_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi10_tx_count > 0U || g_spi10_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi10_rx_address)
            {
                *gp_spi10_rx_address = SCI1->SIOm0;
                gp_spi10_rx_address++;
                g_spi10_rx_count--;
            }
            else
            {
                sio_dummy = SCI1->SIOm0;
            }

            /* send data */
            if (0U != gp_spi10_tx_address)
            {
                SCI1->SIOm0 = *gp_spi10_tx_address;
                gp_spi10_tx_address++;
                g_spi10_tx_count--;
            }
            else if((SCI1->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI1->SIOm0 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi10_rx_count)
            {
                while ((SCI1->SSRm0 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi10_rx_address)
                {
                    *gp_spi10_rx_address = SCI1->SIOm0;
                     g_spi10_rx_count--;
                }
                else
                {
                    sio_dummy = SCI1->SIOm0;
                }
                spi10_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi10_tx_address)
            {
                if (((SCI1->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI1->SCRm0 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI1->SSRm0 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi10_callback_sendend();    /* complete send */
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: spi10_callback_receiveend
* @brief  This function is a callback function when spi10 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi10_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI1_SPI10);
    gp_spi10_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi10_callback_error
* @brief  This function is a callback function when spi10 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi10_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi10_callback_sendend
* @brief  This function is a callback function when spi10 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi10_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI1_SPI10);
    gp_spi10_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI11
/***********************************************************************************************************************
* Function Name: spi11_interrupt
* @brief  SPI11 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi11_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI1->SSRm1 & _0001_SCI_OVERRUN_ERROR);
    SCI1->SIRm1 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi11_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi11_tx_count > 0U || g_spi11_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi11_rx_address)
            {
                *gp_spi11_rx_address = SCI1->SIOm1;
                gp_spi11_rx_address++;
                g_spi11_rx_count--;
            }
            else
            {
                sio_dummy = SCI1->SIOm1;
            }

            /* send data */
            if (0U != gp_spi11_tx_address)
            {
                SCI1->SIOm1 = *gp_spi11_tx_address;
                gp_spi11_tx_address++;
                g_spi11_tx_count--;
            }
            else if((SCI1->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI1->SIOm1 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi11_rx_count)
            {
                while ((SCI1->SSRm1 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi11_rx_address)
                {
                    *gp_spi11_rx_address = SCI1->SIOm1;
                     g_spi11_rx_count--;
                }
                else
                {
                    sio_dummy = SCI1->SIOm1;
                }
                spi11_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi11_tx_address)
            {
                if (((SCI1->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI1->SCRm1 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI1->SSRm1 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi11_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI11_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi11_callback_receiveend
* @brief  This function is a callback function when spi11 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi11_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI1_SPI11);
    gp_spi11_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi11_callback_error
* @brief  This function is a callback function when spi11 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi11_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi11_callback_sendend
* @brief  This function is a callback function when spi11 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi11_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI1_SPI11);
    gp_spi11_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC10
/***********************************************************************************************************************
* Function Name: iic10_interrupt
* @brief  IIC10 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iic10_interrupt(void)
{
    if (((SCI1->SSRm0 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic10_tx_count != 0U))
    {
        iic10_callback_master_error(MD_NACK);
    }
    else if(((SCI1->SSRm0 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic10_tx_count != 0U))
    {
        iic10_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic10_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic10_tx_count > 0U)
            {
                SCI1->SIOm0 = *gp_iic10_tx_address;
                gp_iic10_tx_address++;
                g_iic10_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI1_IIC10);
                iic10_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic10_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI1->ST = _0001_SCI_CH0_STOP_TRG_ON;
                SCI1->SCRm0 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI1->SCRm0 |= _4000_SCI_RECEPTION;
                SCI1->SS = _0001_SCI_CH0_START_TRG_ON;
                g_iic10_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic10_rx_length == 1U)
                {
                    SCI1->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI1->SIOm0 = 0xFFU;
            }
            else
            {
                if (g_iic10_rx_count < g_iic10_rx_length)
                {
                    *gp_iic10_rx_address = SCI1->SIOm0;
                    gp_iic10_rx_address++;
                    g_iic10_rx_count++;
                    
                    if (g_iic10_rx_count == (g_iic10_rx_length - 1U))
                    {
                        SCI1->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI1->SIOm0 = 0xFFU;
                    }
                    else if (g_iic10_rx_count == g_iic10_rx_length)
                    {
                        IIC_StopCondition(SCI1_IIC10);
                        iic10_callback_master_receiveend();
                    }
                    else
                    {
                        SCI1->SIOm0 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC10_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic10_callback_master_error
* @brief  This function is a callback function when IIC10 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic10_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic10_callback_master_receiveend
* @brief  This function is a callback function when IIC10 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic10_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic10_rx_end = 1;
    IIC_Stop(SCI1_IIC10);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic10_callback_master_sendend
* @brief  This function is a callback function when IIC10 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic10_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic10_tx_end = 1;
    IIC_Stop(SCI1_IIC10);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC11
/***********************************************************************************************************************
* Function Name: iic11_interrupt
* @brief  IIC11 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
void iic11_interrupt(void)
{
    if (((SCI1->SSRm1 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic11_tx_count != 0U))
    {
        iic11_callback_master_error(MD_NACK);
    }
    else if(((SCI1->SSRm1 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic11_tx_count != 0U))
    {
        iic11_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic11_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic11_tx_count > 0U)
            {
                SCI1->SIOm1 = *gp_iic11_tx_address;
                gp_iic11_tx_address++;
                g_iic11_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI1_IIC11);
                iic11_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic11_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI1->ST     = _0002_SCI_CH1_STOP_TRG_ON;
                SCI1->SCRm1 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI1->SCRm1 |= _4000_SCI_RECEPTION;
                SCI1->SS     = _0002_SCI_CH1_START_TRG_ON;
                g_iic11_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic11_rx_length == 1U)
                {
                    SCI1->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI1->SIOm1 = 0xFFU;
            }
            else
            {
                if (g_iic11_rx_count < g_iic11_rx_length)
                {
                    *gp_iic11_rx_address = SCI1->SIOm1;
                    gp_iic11_rx_address++;
                    g_iic11_rx_count++;
                    
                    if (g_iic11_rx_count == (g_iic11_rx_length - 1U))
                    {
                        SCI1->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI1->SIOm1 = 0xFFU;
                    }
                    else if (g_iic11_rx_count == g_iic11_rx_length)
                    {
                        IIC_StopCondition(SCI1_IIC11);
                        iic11_callback_master_receiveend();
                    }
                    else
                    {
                        SCI1->SIOm1 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC11_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic11_callback_master_error
* @brief  This function is a callback function when IIC11 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic11_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic11_callback_master_receiveend
* @brief  This function is a callback function when IIC11 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic11_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic11_rx_end = 1;
    IIC_Stop(SCI1_IIC11);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic11_callback_master_sendend
* @brief  This function is a callback function when IIC11 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic11_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic11_tx_end = 1;
    IIC_Stop(SCI1_IIC11);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART2_RX
/***********************************************************************************************************************
* Function Name: uart2_interrupt_receive
* @brief  UART2 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart2_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;

    err_type = (uint8_t)(SCI1->SSR11 & 0x0007U);
    SCI1->SIR11 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart2_callback_error(err_type);
    }
    
    rx_data = SCI1->RXD2;

    if (g_uart2_rx_length > g_uart2_rx_count)
    {
        *gp_uart2_rx_address = rx_data;
        gp_uart2_rx_address++;
        g_uart2_rx_count++;

        if (g_uart2_rx_length == g_uart2_rx_count)
        {
            uart2_callback_receiveend();
        }
    }
    else
    {
        uart2_callback_softwareoverrun(rx_data);
    }
    NVIC_ClearPendingIRQ(SR2_IRQn);     /* clear INTSR2 interrupt flag */
    NVIC_ClearPendingIRQ(SR2_IRQn);     /* clear INTSR2 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_receiveend
* @brief  This function is a callback function when UART2 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_softwareoverrun
* @brief  This function is a callback function when UART2 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart2_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_error
* @brief  This function is a callback function when UART2 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart2_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART2_TX
/***********************************************************************************************************************
* Function Name: uart2_interrupt_send
* @brief  UART2 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart2_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST2_IRQn);
    if (g_uart2_tx_count > 0U)
    {
        SCI1->TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }
    else
    {
        uart2_callback_sendend();
    }
    NVIC_ClearPendingIRQ(ST2_IRQn);     /* clear INTST2 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_sendend
* @brief  This function is a callback function when UART2 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI20
/***********************************************************************************************************************
* Function Name: spi20_interrupt
* @brief  SPI20 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi20_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI2->SSRm0 & _0001_SCI_OVERRUN_ERROR);
    SCI2->SIRm0 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi20_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi20_tx_count > 0U || g_spi20_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi20_rx_address)
            {
                *gp_spi20_rx_address = SCI2->SIOm0;
                gp_spi20_rx_address++;
                g_spi20_rx_count--;
            }
            else
            {
                sio_dummy = SCI2->SIOm0;
            }

            /* send data */
            if (0U != gp_spi20_tx_address)
            {
                SCI2->SIOm0 = *gp_spi20_tx_address;
                gp_spi20_tx_address++;
                g_spi20_tx_count--;
            }
            else if((SCI2->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI2->SIOm0 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi20_rx_count)
            {
                while ((SCI2->SSRm0 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi20_rx_address)
                {
                    *gp_spi20_rx_address = SCI2->SIOm0;
                     g_spi20_rx_count--;
                }
                else
                {
                    sio_dummy = SCI2->SIOm0;
                }
                spi20_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi20_tx_address)
            {
                if (((SCI2->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI2->SCRm0 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI2->SSRm0 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi20_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI20_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi20_callback_receiveend
* @brief  This function is a callback function when spi20 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi20_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI2_SPI20);
    gp_spi20_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi20_callback_error
* @brief  This function is a callback function when spi20 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi20_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi20_callback_sendend
* @brief  This function is a callback function when spi20 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi20_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI2_SPI20);
    gp_spi20_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI21
/***********************************************************************************************************************
* Function Name: spi21_interrupt
* @brief  SPI21 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi21_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI2->SSRm1 & _0001_SCI_OVERRUN_ERROR);
    SCI2->SIRm1 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi21_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi21_tx_count > 0U || g_spi21_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi21_rx_address)
            {
                *gp_spi21_rx_address = SCI2->SIOm1;
                gp_spi21_rx_address++;
                g_spi21_rx_count--;
            }
            else
            {
                sio_dummy = SCI2->SIOm1;
            }

            /* send data */
            if (0U != gp_spi21_tx_address)
            {
                SCI2->SIOm1 = *gp_spi21_tx_address;
                gp_spi21_tx_address++;
                g_spi21_tx_count--;
            }
            else if((SCI2->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI2->SIOm1 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi21_rx_count)
            {
                while ((SCI2->SSRm1 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi21_rx_address)
                {
                    *gp_spi21_rx_address = SCI2->SIOm1;
                     g_spi21_rx_count--;
                }
                else
                {
                    sio_dummy = SCI2->SIOm1;
                }
                spi21_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi21_tx_address)
            {
                if (((SCI2->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI2->SCRm1 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI2->SSRm1 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi21_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI21_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi21_callback_receiveend
* @brief  This function is a callback function when spi21 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi21_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI2_SPI21);
    gp_spi21_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi21_callback_error
* @brief  This function is a callback function when spi21 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi21_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi21_callback_sendend
* @brief  This function is a callback function when spi21 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi21_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI2_SPI21);
    gp_spi21_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC20
/***********************************************************************************************************************
* Function Name: iic20_interrupt
* @brief  IIC20 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iic20_interrupt(void)
{
    if (((SCI2->SSRm0 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic20_tx_count != 0U))
    {
        iic20_callback_master_error(MD_NACK);
    }
    else if(((SCI2->SSRm0 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic20_tx_count != 0U))
    {
        iic20_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic20_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic20_tx_count > 0U)
            {
                SCI2->SIOm0 = *gp_iic20_tx_address;
                gp_iic20_tx_address++;
                g_iic20_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI2_IIC20);
                iic20_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic20_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI2->ST = _0001_SCI_CH0_STOP_TRG_ON;
                SCI2->SCRm0 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI2->SCRm0 |= _4000_SCI_RECEPTION;
                SCI2->SS = _0001_SCI_CH0_START_TRG_ON;
                g_iic20_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic20_rx_length == 1U)
                {
                    SCI2->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI2->SIOm0 = 0xFFU;
            }
            else
            {
                if (g_iic20_rx_count < g_iic20_rx_length)
                {
                    *gp_iic20_rx_address = SCI2->SIOm0;
                    gp_iic20_rx_address++;
                    g_iic20_rx_count++;
                    
                    if (g_iic20_rx_count == (g_iic20_rx_length - 1U))
                    {
                        SCI2->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI2->SIOm0 = 0xFFU;
                    }
                    else if (g_iic20_rx_count == g_iic20_rx_length)
                    {
                        IIC_StopCondition(SCI2_IIC20);
                        iic20_callback_master_receiveend();
                    }
                    else
                    {
                        SCI2->SIOm0 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC20_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_error
* @brief  This function is a callback function when IIC20 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic20_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_receiveend
* @brief  This function is a callback function when IIC20 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic20_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic20_rx_end = 1;
    IIC_Stop(SCI2_IIC20);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_sendend
* @brief  This function is a callback function when IIC20 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic20_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic20_tx_end = 1;
    IIC_Stop(SCI2_IIC20);
    /* End user code. Do not edit comment generated here */
}
#endif
#if defined USE_SCI_IIC21
/***********************************************************************************************************************
* Function Name: iic21_interrupt
* @brief  IIC21 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
void iic21_interrupt(void)
{
    if (((SCI2->SSRm1 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic21_tx_count != 0U))
    {
        iic21_callback_master_error(MD_NACK);
    }
    else if(((SCI2->SSRm1 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic21_tx_count != 0U))
    {
        iic21_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic21_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic21_tx_count > 0U)
            {
                SCI2->SIOm1 = *gp_iic21_tx_address;
                gp_iic21_tx_address++;
                g_iic21_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI2_IIC21);
                iic21_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic21_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI2->ST     = _0002_SCI_CH1_STOP_TRG_ON;
                SCI2->SCRm1 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI2->SCRm1 |= _4000_SCI_RECEPTION;
                SCI2->SS     = _0002_SCI_CH1_START_TRG_ON;
                g_iic21_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic21_rx_length == 1U)
                {
                    SCI2->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI2->SIOm1 = 0xFFU;
            }
            else
            {
                if (g_iic21_rx_count < g_iic21_rx_length)
                {
                    *gp_iic21_rx_address = SCI2->SIOm1;
                    gp_iic21_rx_address++;
                    g_iic21_rx_count++;
                    
                    if (g_iic21_rx_count == (g_iic21_rx_length - 1U))
                    {
                        SCI2->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI2->SIOm1 = 0xFFU;
                    }
                    else if (g_iic21_rx_count == g_iic21_rx_length)
                    {
                        IIC_StopCondition(SCI2_IIC21);
                        iic21_callback_master_receiveend();
                    }
                    else
                    {
                        SCI2->SIOm1 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC21_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_error
* @brief  This function is a callback function when IIC21 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_receiveend
* @brief  This function is a callback function when IIC21 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic21_rx_end = 1;
    IIC_Stop(SCI2_IIC21);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_sendend
* @brief  This function is a callback function when IIC21 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic21_tx_end = 1;
    IIC_Stop(SCI2_IIC21);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART3_RX
/***********************************************************************************************************************
* Function Name: uart3_interrupt_receive
* @brief  UART3 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart3_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    NVIC_ClearPendingIRQ(SR3_IRQn);
    err_type = (uint8_t)(SCI2->SSR21 & 0x0007U);
    SCI2->SIR21 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart3_callback_error(err_type);
    }
    
    rx_data = SCI2->RXD3;

    if (g_uart3_rx_length > g_uart3_rx_count)
    {
        *gp_uart3_rx_address = rx_data;
        gp_uart3_rx_address++;
        g_uart3_rx_count++;

        if (g_uart3_rx_length == g_uart3_rx_count)
        {
            uart3_callback_receiveend();
        }
    }
    else
    {
        uart3_callback_softwareoverrun(rx_data);
    }
    NVIC_ClearPendingIRQ(SR3_IRQn);     /* clear INTSR3 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart3_callback_receiveend
* @brief  This function is a callback function when UART3 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart3_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart3_callback_softwareoverrun
* @brief  This function is a callback function when UART3 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart3_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart3_callback_error
* @brief  This function is a callback function when UART3 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart3_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_UART3_TX
/***********************************************************************************************************************
* Function Name: uart3_interrupt_send
* @brief  UART3 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart3_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST3_IRQn);
    if (g_uart3_tx_count > 0U)
    {
        SCI2->TXD3 = *gp_uart3_tx_address;
        gp_uart3_tx_address++;
        g_uart3_tx_count--;
    }
    else
    {
        uart3_callback_sendend();
    }
    NVIC_ClearPendingIRQ(ST3_IRQn);     /* clear INTST3 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart3_callback_sendend
* @brief  This function is a callback function when UART3 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart3_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI30
/***********************************************************************************************************************
* Function Name: spi30_interrupt
* @brief  SPI30 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi30_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI3->SSRm0 & _0001_SCI_OVERRUN_ERROR);
    SCI3->SIRm0 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi30_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi30_tx_count > 0U || g_spi30_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi30_rx_address)
            {
                *gp_spi30_rx_address = SCI3->SIOm0;
                gp_spi30_rx_address++;
                g_spi30_rx_count--;
            }
            else
            {
                sio_dummy = SCI3->SIOm0;
            }

            /* send data */
            if (0U != gp_spi30_tx_address)
            {
                SCI3->SIOm0 = *gp_spi30_tx_address;
                gp_spi30_tx_address++;
                g_spi30_tx_count--;
            }
            else if((SCI3->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI3->SIOm0 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi30_rx_count)
            {
                while ((SCI3->SSRm0 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi30_rx_address)
                {
                    *gp_spi30_rx_address = SCI3->SIOm0;
                     g_spi30_rx_count--;
                }
                else
                {
                    sio_dummy = SCI3->SIOm0;
                }
                spi30_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi30_tx_address)
            {
                if (((SCI3->SMRm0 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI3->SCRm0 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI3->SSRm0 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi30_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI30_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi30_callback_receiveend
* @brief  This function is a callback function when spi30 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi30_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI3_SPI30);
    gp_spi30_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi30_callback_error
* @brief  This function is a callback function when spi30 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi30_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi30_callback_sendend
* @brief  This function is a callback function when spi30 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi30_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI3_SPI30);
    gp_spi30_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_SPI31
/***********************************************************************************************************************
* Function Name: spi31_interrupt
* @brief  SPI31 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi31_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI3->SSRm1 & _0001_SCI_OVERRUN_ERROR);
    SCI3->SIRm1 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi31_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi31_tx_count > 0U || g_spi31_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi31_rx_address)
            {
                *gp_spi31_rx_address = SCI3->SIOm1;
                gp_spi31_rx_address++;
                g_spi31_rx_count--;
            }
            else
            {
                sio_dummy = SCI3->SIOm1;
            }

            /* send data */
            if (0U != gp_spi31_tx_address)
            {
                SCI3->SIOm1 = *gp_spi31_tx_address;
                gp_spi31_tx_address++;
                g_spi31_tx_count--;
            }
            else if((SCI3->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI3->SIOm1 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi31_rx_count)
            {
                while ((SCI3->SSRm1 & _0020_SCI_VALID_STORED) == 0)
                {
                }
                if (0U != gp_spi31_rx_address)
                {
                    *gp_spi31_rx_address = SCI3->SIOm1;
                     g_spi31_rx_count--;
                }
                else
                {
                    sio_dummy = SCI3->SIOm1;
                }
                spi31_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi31_tx_address)
            {
                if (((SCI3->SMRm1 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI3->SCRm1 & _4000_SCI_RECEPTION) != 0))
                {
                    /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI3->SSRm1 & _0040_SCI_UNDER_EXECUTE)
                    {
                    }
                }
                spi31_callback_sendend();    /* complete send */
            }
        }
    }
    NVIC_ClearPendingIRQ(SPI31_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi31_callback_receiveend
* @brief  This function is a callback function when spi31 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi31_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI3_SPI31);
    gp_spi31_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi31_callback_error
* @brief  This function is a callback function when spi31 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi31_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi31_callback_sendend
* @brief  This function is a callback function when spi31 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi31_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI_Stop(SCI3_SPI31);
    gp_spi31_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC30
/***********************************************************************************************************************
* Function Name: iic30_interrupt
* @brief  IIC30 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iic30_interrupt(void)
{
    if (((SCI3->SSRm0 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic30_tx_count != 0U))
    {
        iic30_callback_master_error(MD_NACK);
    }
    else if(((SCI3->SSRm0 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic30_tx_count != 0U))
    {
        iic30_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic30_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic30_tx_count > 0U)
            {
                SCI3->SIOm0 = *gp_iic30_tx_address;
                gp_iic30_tx_address++;
                g_iic30_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI3_IIC30);
                iic30_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic30_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI3->ST = _0001_SCI_CH0_STOP_TRG_ON;
                SCI3->SCRm0 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI3->SCRm0 |= _4000_SCI_RECEPTION;
                SCI3->SS = _0001_SCI_CH0_START_TRG_ON;
                g_iic30_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic30_rx_length == 1U)
                {
                    SCI3->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI3->SIOm0 = 0xFFU;
            }
            else
            {
                if (g_iic30_rx_count < g_iic30_rx_length)
                {
                    *gp_iic30_rx_address = SCI3->SIOm0;
                    gp_iic30_rx_address++;
                    g_iic30_rx_count++;
                    
                    if (g_iic30_rx_count == (g_iic30_rx_length - 1U))
                    {
                        SCI3->SOE &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI3->SIOm0 = 0xFFU;
                    }
                    else if (g_iic30_rx_count == g_iic30_rx_length)
                    {
                        IIC_StopCondition(SCI3_IIC30);
                        iic30_callback_master_receiveend();
                    }
                    else
                    {
                        SCI3->SIOm0 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC30_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic30_callback_master_error
* @brief  This function is a callback function when IIC30 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic30_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic30_callback_master_receiveend
* @brief  This function is a callback function when IIC30 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic30_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic30_rx_end = 1;
    IIC_Stop(SCI3_IIC30);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic30_callback_master_sendend
* @brief  This function is a callback function when IIC30 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic30_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic30_tx_end = 1;
    IIC_Stop(SCI3_IIC30);
    /* End user code. Do not edit comment generated here */
}
#endif

#if defined USE_SCI_IIC31
/***********************************************************************************************************************
* Function Name: iic31_interrupt
* @brief  IIC31 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
void iic31_interrupt(void)
{
    if (((SCI3->SSRm1 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic31_tx_count != 0U))
    {
        iic31_callback_master_error(MD_NACK);
    }
    else if(((SCI3->SSRm1 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic31_tx_count != 0U))
    {
        iic31_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic31_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic31_tx_count > 0U)
            {
                SCI3->SIOm1 = *gp_iic31_tx_address;
                gp_iic31_tx_address++;
                g_iic31_tx_count--;
            }
            else
            {
                IIC_StopCondition(SCI3_IIC31);
                iic31_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic31_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI3->ST     = _0002_SCI_CH1_STOP_TRG_ON;
                SCI3->SCRm1 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI3->SCRm1 |= _4000_SCI_RECEPTION;
                SCI3->SS     = _0002_SCI_CH1_START_TRG_ON;
                g_iic31_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic31_rx_length == 1U)
                {
                    SCI3->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI3->SIOm1 = 0xFFU;
            }
            else
            {
                if (g_iic31_rx_count < g_iic31_rx_length)
                {
                    *gp_iic31_rx_address = SCI3->SIOm1;
                    gp_iic31_rx_address++;
                    g_iic31_rx_count++;
                    
                    if (g_iic31_rx_count == (g_iic31_rx_length - 1U))
                    {
                        SCI3->SOE &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI3->SIOm1 = 0xFFU;
                    }
                    else if (g_iic31_rx_count == g_iic31_rx_length)
                    {
                        IIC_StopCondition(SCI3_IIC31);
                        iic31_callback_master_receiveend();
                    }
                    else
                    {
                        SCI3->SIOm1 = 0xFFU;
                    }
                }
            }
        }
    }
    NVIC_ClearPendingIRQ(IIC31_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic31_callback_master_error
* @brief  This function is a callback function when IIC31 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic31_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic31_callback_master_receiveend
* @brief  This function is a callback function when IIC31 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic31_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic31_rx_end = 1;
    IIC_Stop(SCI3_IIC31);
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic31_callback_master_sendend
* @brief  This function is a callback function when IIC31 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic31_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic31_tx_end = 1;
    IIC_Stop(SCI3_IIC31);
    /* End user code. Do not edit comment generated here */
}
#endif

