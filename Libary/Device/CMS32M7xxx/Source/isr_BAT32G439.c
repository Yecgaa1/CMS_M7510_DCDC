/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    isr.c
* @brief   This file implements device driver for interrupt module.
* @version 1.0.0
* @date    2021/06/03
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G439.h"


/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void IRQ0_Handler(void);
void IRQ1_Handler(void);
void IRQ2_Handler(void);
void IRQ3_Handler(void);
void IRQ4_Handler(void);
void IRQ5_Handler(void);
void IRQ6_Handler(void);
void IRQ7_Handler(void);
void IRQ8_Handler(void);
void IRQ9_Handler(void);
void IRQ10_Handler(void);
void IRQ11_Handler(void);
void IRQ12_Handler(void);
void IRQ13_Handler(void);
void IRQ14_Handler(void);
void IRQ15_Handler(void);
void IRQ16_Handler(void);
void IRQ17_Handler(void);
void IRQ18_Handler(void);
void IRQ19_Handler(void);
void IRQ20_Handler(void);
void IRQ21_Handler(void);
void IRQ22_Handler(void);
void IRQ23_Handler(void);
void IRQ24_Handler(void);
void IRQ25_Handler(void);
void IRQ26_Handler(void);
void IRQ27_Handler(void);
void IRQ28_Handler(void);
void IRQ29_Handler(void);
void IRQ30_Handler(void);
void IRQ31_Handler(void);
void IRQ32_Handler(void);
void IRQ33_Handler(void);
void IRQ34_Handler(void);
void IRQ35_Handler(void);
void IRQ36_Handler(void);
void IRQ37_Handler(void);
void IRQ38_Handler(void);
void IRQ39_Handler(void);
void IRQ40_Handler(void);
void IRQ41_Handler(void);
void IRQ42_Handler(void);
void IRQ43_Handler(void);
void IRQ44_Handler(void);
void IRQ45_Handler(void);
void IRQ46_Handler(void);
void IRQ47_Handler(void);
void IRQ48_Handler(void);
void IRQ49_Handler(void);
void IRQ50_Handler(void);
void IRQ51_Handler(void);
void IRQ52_Handler(void);
void IRQ53_Handler(void);
void IRQ54_Handler(void);
void IRQ55_Handler(void);
void IRQ56_Handler(void);
void IRQ57_Handler(void);
void IRQ58_Handler(void);
void IRQ59_Handler(void);
void IRQ60_Handler(void);
void IRQ61_Handler(void);
void IRQ62_Handler(void);
void IRQ63_Handler(void);
void IRQ64_Handler(void);
void IRQ65_Handler(void);
void IRQ66_Handler(void);
void IRQ67_Handler(void);
void IRQ68_Handler(void);
void IRQ69_Handler(void);
void IRQ70_Handler(void);
void IRQ71_Handler(void);
void IRQ72_Handler(void);
void IRQ73_Handler(void);
void IRQ74_Handler(void);
void IRQ75_Handler(void);
void IRQ76_Handler(void);
void IRQ77_Handler(void);
void IRQ78_Handler(void);
void IRQ79_Handler(void);
void IRQ80_Handler(void);
void IRQ81_Handler(void);
void IRQ82_Handler(void);
void IRQ83_Handler(void);
void IRQ84_Handler(void);
void IRQ85_Handler(void);
void IRQ86_Handler(void);
void IRQ87_Handler(void);
void IRQ88_Handler(void);
void IRQ89_Handler(void);
void IRQ90_Handler(void);
void IRQ91_Handler(void);
void IRQ92_Handler(void);
void IRQ93_Handler(void);
void IRQ94_Handler(void);
void IRQ95_Handler(void);
void IRQ96_Handler(void);
void IRQ97_Handler(void);
void IRQ98_Handler(void);
void IRQ99_Handler(void);
void IRQ100_Handler(void);
void IRQ101_Handler(void);
void IRQ102_Handler(void);
void IRQ103_Handler(void);
void IRQ104_Handler(void);
void IRQ105_Handler(void);
void IRQ106_Handler(void);
void IRQ107_Handler(void);
void IRQ108_Handler(void);
void IRQ109_Handler(void);
void IRQ110_Handler(void);
void IRQ111_Handler(void);
void IRQ112_Handler(void);
void IRQ113_Handler(void);
void IRQ114_Handler(void);
void IRQ115_Handler(void);
void IRQ116_Handler(void);
void IRQ117_Handler(void);
void IRQ118_Handler(void);
void IRQ119_Handler(void);
void IRQ120_Handler(void);
void IRQ121_Handler(void);
void IRQ122_Handler(void);
void IRQ123_Handler(void);
void IRQ124_Handler(void);
void IRQ125_Handler(void);
void IRQ126_Handler(void);
void IRQ127_Handler(void);
void IRQ128_Handler(void);
void IRQ129_Handler(void);
void IRQ130_Handler(void);
void IRQ131_Handler(void);
void IRQ132_Handler(void);
void IRQ133_Handler(void);
void IRQ134_Handler(void);
void IRQ135_Handler(void);
void IRQ136_Handler(void);
void IRQ137_Handler(void);
void IRQ138_Handler(void);
void IRQ139_Handler(void);
void IRQ140_Handler(void);
void IRQ141_Handler(void);
void IRQ142_Handler(void);
void IRQ143_Handler(void);
void IRQ144_Handler(void);
void IRQ145_Handler(void);
void IRQ146_Handler(void);
void IRQ147_Handler(void);
void IRQ148_Handler(void);
void IRQ149_Handler(void);
void IRQ150_Handler(void);
void IRQ151_Handler(void);
void IRQ152_Handler(void);
void IRQ153_Handler(void);
void IRQ154_Handler(void);
void IRQ155_Handler(void);
void IRQ156_Handler(void);
void IRQ157_Handler(void);
void IRQ158_Handler(void);
void IRQ159_Handler(void);
void IRQ160_Handler(void);
void IRQ161_Handler(void);
void IRQ162_Handler(void);
void IRQ163_Handler(void);
void IRQ164_Handler(void);
void IRQ165_Handler(void);
void IRQ166_Handler(void);
void IRQ167_Handler(void);
void IRQ168_Handler(void);
void IRQ169_Handler(void);
void IRQ170_Handler(void);
void IRQ171_Handler(void);
void IRQ172_Handler(void);
void IRQ173_Handler(void);
void IRQ174_Handler(void);
void IRQ175_Handler(void);
void IRQ176_Handler(void);
void IRQ177_Handler(void);
void IRQ178_Handler(void);
void IRQ179_Handler(void);
void IRQ180_Handler(void);
void IRQ181_Handler(void);
void IRQ182_Handler(void);
void IRQ183_Handler(void);
void IRQ184_Handler(void);
void IRQ185_Handler(void);
void IRQ186_Handler(void);
void IRQ187_Handler(void);
void IRQ188_Handler(void);
void IRQ189_Handler(void);
void IRQ190_Handler(void);
void IRQ191_Handler(void);
void IRQ192_Handler(void);
void IRQ193_Handler(void);
void IRQ194_Handler(void);
void IRQ195_Handler(void);
void IRQ196_Handler(void);
void IRQ197_Handler(void);
void IRQ198_Handler(void);
void IRQ199_Handler(void);
void IRQ200_Handler(void);
void IRQ201_Handler(void);


__WEAK void lvi_interrupt(void);
__WEAK void wdt0_interrupt(void);
__WEAK void wdt1_interrupt(void);
__WEAK void intp0_interrupt(void);
__WEAK void intp1_interrupt(void);
__WEAK void intp2_interrupt(void);
__WEAK void intp3_interrupt(void);
__WEAK void intp4_interrupt(void);
__WEAK void intp5_interrupt(void);
__WEAK void intp6_interrupt(void);
__WEAK void intp7_interrupt(void);
__WEAK void uart0_interrupt_send(void);
__WEAK void spi00_interrupt(void);
__WEAK void iic00_interrupt(void);
__WEAK void uart0_interrupt_receive(void);
__WEAK void spi01_interrupt(void);
__WEAK void iic01_interrupt(void);
__WEAK void sre0_interrupt(void);
__WEAK void uart1_interrupt_send(void);
__WEAK void spi10_interrupt(void);
__WEAK void iic10_interrupt(void);
__WEAK void uart1_interrupt_receive(void);
__WEAK void spi11_interrupt(void);
__WEAK void iic11_interrupt(void);
__WEAK void sre1_interrupt(void);
__WEAK void uart2_interrupt_send(void);
__WEAK void spi20_interrupt(void);
__WEAK void iic20_interrupt(void);
__WEAK void uart2_interrupt_receive(void);
__WEAK void spi21_interrupt(void);
__WEAK void iic21_interrupt(void);
__WEAK void sre2_interrupt(void);
__WEAK void uart3_interrupt_send(void);
__WEAK void spi30_interrupt(void);
__WEAK void iic30_interrupt(void);
__WEAK void uart3_interrupt_receive(void);
__WEAK void spi31_interrupt(void);
__WEAK void iic31_interrupt(void);
__WEAK void sre3_interrupt(void);
__WEAK void iica0_interrupt(void);
__WEAK void iica1_interrupt(void);
__WEAK void spi0_interrupt(void);
__WEAK void spi1_interrupt(void);
__WEAK void tm00_interrupt(void);
__WEAK void tm01_interrupt(void);
__WEAK void tm02_interrupt(void);
__WEAK void tm03_interrupt(void);
__WEAK void tm04_interrupt(void);
__WEAK void tm05_interrupt(void);
__WEAK void tm06_interrupt(void);
__WEAK void tm07_interrupt(void);
__WEAK void tm01h_interrupt(void);
__WEAK void tm03h_interrupt(void);
__WEAK void tm10_interrupt(void);
__WEAK void tm11_interrupt(void);
__WEAK void tm12_interrupt(void);
__WEAK void tm13_interrupt(void);
__WEAK void tm14_interrupt(void);
__WEAK void tm15_interrupt(void);
__WEAK void tm16_interrupt(void);
__WEAK void tm17_interrupt(void);
__WEAK void tm11h_interrupt(void);
__WEAK void tm13h_interrupt(void);
__WEAK void adc0_adireq_n_interrupt(void);
__WEAK void adc1_adireq_n_interrupt(void);
__WEAK void adc2_adireq_n_interrupt(void);
__WEAK void adc0_gbadireq_n_interrupt(void);
__WEAK void adc1_gbadireq_n_interrupt(void);
__WEAK void adc2_gbadireq_n_interrupt(void);
__WEAK void adc0_gcadireq_n_interrupt(void);
__WEAK void adc1_gcadireq_n_interrupt(void);
__WEAK void adc2_gcadireq_n_interrupt(void);
__WEAK void rtc_interrupt(void);
__WEAK void it_interrupt(void);
__WEAK void kr_interrupt(void);
__WEAK void cmp0_interrupt(void);
__WEAK void cmp1_interrupt(void);
__WEAK void cmp2_interrupt(void);
__WEAK void cmp3_interrupt(void);
__WEAK void c0err_interrupt(void);
__WEAK void c0rec_interrupt(void);
__WEAK void c0wup_interrupt(void);
__WEAK void c0trx_interrupt(void);
__WEAK void lcdb_interrupt(void);
__WEAK void qspi_interrupt(void);
__WEAK void qspi_dmareq_interrupt(void);
__WEAK void fl_interrupt(void);
__WEAK void osdc_interrupt(void);
__WEAK void pgi0_interrupt(void);
__WEAK void pgi1_interrupt(void);
__WEAK void pgi2_interrupt(void);
__WEAK void pgi3_interrupt(void);
__WEAK void gpt0_elccmpa0_interrupt(void);
__WEAK void gpt0_elccmpb0_interrupt(void);
__WEAK void gpt0_elccmpc0_interrupt(void);
__WEAK void gpt0_elccmpd0_interrupt(void);
__WEAK void gpt0_elccmpe0_interrupt(void);
__WEAK void gpt0_elccmpf0_interrupt(void);
__WEAK void gpt0_elcovf0_interrupt(void);
__WEAK void gpt0_elcudf0_interrupt(void);
__WEAK void gpt0_elccmpa1_interrupt(void);
__WEAK void gpt0_elccmpb1_interrupt(void);
__WEAK void gpt0_elccmpc1_interrupt(void);
__WEAK void gpt0_elccmpd1_interrupt(void);
__WEAK void gpt0_elccmpe1_interrupt(void);
__WEAK void gpt0_elccmpf1_interrupt(void);
__WEAK void gpt0_elcovf1_interrupt(void);
__WEAK void gpt0_elcudf1_interrupt(void);
__WEAK void gpt0_elccmpa2_interrupt(void);
__WEAK void gpt0_elccmpb2_interrupt(void);
__WEAK void gpt0_elccmpc2_interrupt(void);
__WEAK void gpt0_elccmpd2_interrupt(void);
__WEAK void gpt0_elccmpe2_interrupt(void);
__WEAK void gpt0_elccmpf2_interrupt(void);
__WEAK void gpt0_elcovf2_interrupt(void);
__WEAK void gpt0_elcudf2_interrupt(void);
__WEAK void gpt0_elccmpa3_interrupt(void);
__WEAK void gpt0_elccmpb3_interrupt(void);
__WEAK void gpt0_elccmpc3_interrupt(void);
__WEAK void gpt0_elccmpd3_interrupt(void);
__WEAK void gpt0_elccmpe3_interrupt(void);
__WEAK void gpt0_elccmpf3_interrupt(void);
__WEAK void gpt0_elcovf3_interrupt(void);
__WEAK void gpt0_elcudf3_interrupt(void);
__WEAK void gpt1_elccmpa0_interrupt(void);
__WEAK void gpt1_elccmpb0_interrupt(void);
__WEAK void gpt1_elccmpc0_interrupt(void);
__WEAK void gpt1_elccmpd0_interrupt(void);
__WEAK void gpt1_elccmpe0_interrupt(void);
__WEAK void gpt1_elccmpf0_interrupt(void);
__WEAK void gpt1_elcovf0_interrupt(void);
__WEAK void gpt1_elcudf0_interrupt(void);
__WEAK void gpt1_elccmpa1_interrupt(void);
__WEAK void gpt1_elccmpb1_interrupt(void);
__WEAK void gpt1_elccmpc1_interrupt(void);
__WEAK void gpt1_elccmpd1_interrupt(void);
__WEAK void gpt1_elccmpe1_interrupt(void);
__WEAK void gpt1_elccmpf1_interrupt(void);
__WEAK void gpt1_elcovf1_interrupt(void);
__WEAK void gpt1_elcudf1_interrupt(void);
__WEAK void gpt1_elccmpa2_interrupt(void);
__WEAK void gpt1_elccmpb2_interrupt(void);
__WEAK void gpt1_elccmpc2_interrupt(void);
__WEAK void gpt1_elccmpd2_interrupt(void);
__WEAK void gpt1_elccmpe2_interrupt(void);
__WEAK void gpt1_elccmpf2_interrupt(void);
__WEAK void gpt1_elcovf2_interrupt(void);
__WEAK void gpt1_elcudf2_interrupt(void);
__WEAK void gpt1_elccmpa3_interrupt(void);
__WEAK void gpt1_elccmpb3_interrupt(void);
__WEAK void gpt1_elccmpc3_interrupt(void);
__WEAK void gpt1_elccmpd3_interrupt(void);
__WEAK void gpt1_elccmpe3_interrupt(void);
__WEAK void gpt1_elccmpf3_interrupt(void);
__WEAK void gpt1_elcovf3_interrupt(void);
__WEAK void gpt1_elcudf3_interrupt(void);
__WEAK void gpt1_elccmpa4_interrupt(void);
__WEAK void gpt1_elccmpb4_interrupt(void);
__WEAK void gpt1_elccmpc4_interrupt(void);
__WEAK void gpt1_elccmpd4_interrupt(void);
__WEAK void gpt1_elccmpe4_interrupt(void);
__WEAK void gpt1_elccmpf4_interrupt(void);
__WEAK void gpt1_elcovf4_interrupt(void);
__WEAK void gpt1_elcudf4_interrupt(void);
__WEAK void gpt1_elccmpa5_interrupt(void);
__WEAK void gpt1_elccmpb5_interrupt(void);
__WEAK void gpt1_elccmpc5_interrupt(void);
__WEAK void gpt1_elccmpd5_interrupt(void);
__WEAK void gpt1_elccmpe5_interrupt(void);
__WEAK void gpt1_elccmpf5_interrupt(void);
__WEAK void gpt1_elcovf5_interrupt(void);
__WEAK void gpt1_elcudf5_interrupt(void);
__WEAK void gpt1_elccmpa6_interrupt(void);
__WEAK void gpt1_elccmpb6_interrupt(void);
__WEAK void gpt1_elccmpc6_interrupt(void);
__WEAK void gpt1_elccmpd6_interrupt(void);
__WEAK void gpt1_elccmpe6_interrupt(void);
__WEAK void gpt1_elccmpf6_interrupt(void);
__WEAK void gpt1_elcovf6_interrupt(void);
__WEAK void gpt1_elcudf6_interrupt(void);
__WEAK void gpt1_elccmpa7_interrupt(void);
__WEAK void gpt1_elccmpb7_interrupt(void);
__WEAK void gpt1_elccmpc7_interrupt(void);
__WEAK void gpt1_elccmpd7_interrupt(void);
__WEAK void gpt1_elccmpe7_interrupt(void);
__WEAK void gpt1_elccmpf7_interrupt(void);
__WEAK void gpt1_elcovf7_interrupt(void);
__WEAK void gpt1_elcudf7_interrupt(void);
__WEAK void gpt1_elcedguvw_interrupt(void);
__WEAK void aes_wrreq_interrupt(void);
__WEAK void aes_rdreq_interrupt(void);
__WEAK void rng_rdreq_interrupt(void);
__WEAK void dma0_interrupt(void);
__WEAK void dma1_interrupt(void);
__WEAK void dma2_interrupt(void);
__WEAK void dma3_interrupt(void);
__WEAK void dma4_interrupt(void);
__WEAK void dma5_interrupt(void);
__WEAK void dma6_interrupt(void);
__WEAK void dma7_interrupt(void);
__WEAK void dma8_interrupt(void);
__WEAK void dma9_interrupt(void);
__WEAK void dma10_interrupt(void);
__WEAK void dma11_interrupt(void);
__WEAK void dma12_interrupt(void);
__WEAK void dma13_interrupt(void);
__WEAK void dma14_interrupt(void);
__WEAK void dma15_interrupt(void);
__WEAK void ocrv_interrupt(void);
__WEAK void ramparity_interrupt(void);
__WEAK void c1err_interrupt(void);
__WEAK void c1rec_interrupt(void);
__WEAK void c1wup_interrupt(void);
__WEAK void c1trx_interrupt(void);
__WEAK void iir0wfifoemp_interrupt(void);
__WEAK void iir0wfifoful_interrupt(void);
__WEAK void iir1wfifoemp_interrupt(void);
__WEAK void iir1wfifoful_interrupt(void);



/***********************************************************IRQ0Handler************************************************************/
__WEAK void lvi_interrupt(void)
{
    NVIC_ClearPendingIRQ(LVI_IRQn);
}

void IRQ0_Handler(void)
{
    lvi_interrupt();
}

/***********************************************************IRQ1Handler************************************************************/
__WEAK void wdt0_interrupt(void)
{
    NVIC_ClearPendingIRQ(WDT0_IRQn);
}

void IRQ1_Handler(void)
{
    wdt0_interrupt();
}

/***********************************************************IRQ2Handler************************************************************/
__WEAK void wdt1_interrupt(void)
{
    NVIC_ClearPendingIRQ(WDT1_IRQn);
}

void IRQ2_Handler(void)
{
    wdt1_interrupt();
}

/***********************************************************IRQ3Handler************************************************************/
__WEAK void intp0_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP0_IRQn);
}

void IRQ3_Handler(void)
{
    intp0_interrupt();
}

/***********************************************************IRQ4Handler************************************************************/
__WEAK void intp1_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP1_IRQn);
}

void IRQ4_Handler(void)
{
    intp1_interrupt();
}

/***********************************************************IRQ5Handler************************************************************/
__WEAK void intp2_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP2_IRQn);
}

void IRQ5_Handler(void)
{
    intp2_interrupt();
}

/***********************************************************IRQ6Handler************************************************************/
__WEAK void intp3_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP3_IRQn);
}

void IRQ6_Handler(void)
{
    intp3_interrupt();
}

/***********************************************************IRQ7Handler************************************************************/
__WEAK void intp4_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP4_IRQn);
}

void IRQ7_Handler(void)
{
    intp4_interrupt();
}

/***********************************************************IRQ8Handler************************************************************/
__WEAK void intp5_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP5_IRQn);
}

void IRQ8_Handler(void)
{
    intp5_interrupt();
}

/***********************************************************IRQ9Handler************************************************************/
__WEAK void intp6_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP6_IRQn);
}

void IRQ9_Handler(void)
{
    intp6_interrupt();
}

/***********************************************************IRQ10Handler************************************************************/
__WEAK void intp7_interrupt(void)
{
    NVIC_ClearPendingIRQ(INTP7_IRQn);
}

void IRQ10_Handler(void)
{
    intp7_interrupt();
}

/***********************************************************IRQ11Handler************************************************************/
__WEAK void uart0_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST0_IRQn);
}
__WEAK void spi00_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI00_IRQn);
}
__WEAK void iic00_interrupt(void)
{
	NVIC_ClearPendingIRQ(IIC00_IRQn);
}

void IRQ11_Handler(void)
{
#if defined(USE_SCI_UART0_TX)
    uart0_interrupt_send();
#elif defined(USE_SCI_SPI00)		
    spi00_interrupt();
#elif defined(USE_SCI_IIC00)		
    iic00_interrupt();
#endif
}

/***********************************************************IRQ12Handler************************************************************/
__WEAK void uart0_interrupt_receive(void)
{
    NVIC_ClearPendingIRQ(SR0_IRQn);
}
__WEAK void spi01_interrupt(void)
{
	NVIC_ClearPendingIRQ(SPI01_IRQn);
}
__WEAK void iic01_interrupt(void)
{
	NVIC_ClearPendingIRQ(IIC01_IRQn);
}

void IRQ12_Handler(void)
{
#if defined(USE_SCI_UART0_RX)
    uart0_interrupt_receive();
#elif defined(USE_SCI_SPI01)		
    spi01_interrupt();
#elif defined(USE_SCI_IIC01)		
    iic01_interrupt();
#endif
}

/***********************************************************IRQ13Handler************************************************************/
__WEAK void sre0_interrupt(void)
{
    NVIC_ClearPendingIRQ(SRE0_IRQn);
}

void IRQ13_Handler(void)
{
    sre0_interrupt();
}

/***********************************************************IRQ14Handler************************************************************/
__WEAK void uart1_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST1_IRQn);
}
__WEAK void spi10_interrupt(void)
{
	NVIC_ClearPendingIRQ(SPI10_IRQn);
}
__WEAK void iic10_interrupt(void)
{
	NVIC_ClearPendingIRQ(IIC10_IRQn);
}

void IRQ14_Handler(void)
{
#if defined(USE_SCI_UART1_TX)
    uart1_interrupt_send();
#elif defined(USE_SCI_SPI10)		
    spi10_interrupt();
#elif defined(USE_SCI_IIC10)		
    iic10_interrupt();
#endif
}

/***********************************************************IRQ15Handler************************************************************/
__WEAK void uart1_interrupt_receive(void)
{
	NVIC_ClearPendingIRQ(SR1_IRQn);
}
__WEAK void spi11_interrupt(void)
{
	NVIC_ClearPendingIRQ(SPI11_IRQn);
}
__WEAK void iic11_interrupt(void)
{
	NVIC_ClearPendingIRQ(IIC11_IRQn);
}

void IRQ15_Handler(void)
{
#if defined(USE_SCI_UART1_RX)	
    uart1_interrupt_receive();
#elif defined(USE_SCI_SPI11)		
    spi11_interrupt();
#elif defined(USE_SCI_IIC11)		
    iic11_interrupt();
#endif
}

/***********************************************************IRQ16Handler************************************************************/
__WEAK void sre1_interrupt(void)
{
    NVIC_ClearPendingIRQ(SRE1_IRQn);
}

void IRQ16_Handler(void)
{
    sre1_interrupt();
}

/***********************************************************IRQ17Handler************************************************************/
__WEAK void uart2_interrupt_send(void)
{
	NVIC_ClearPendingIRQ(ST2_IRQn);
}
__WEAK void spi20_interrupt(void)
{
	NVIC_ClearPendingIRQ(SPI20_IRQn);
}
__WEAK void iic20_interrupt(void)
{
	NVIC_ClearPendingIRQ(IIC20_IRQn);
}

void IRQ17_Handler(void)
{
#if defined(USE_SCI_UART2_TX)
    uart2_interrupt_send();
#elif defined(USE_SCI_SPI20)		
    spi20_interrupt();
#elif defined(USE_SCI_IIC20)		
    iic20_interrupt();
#endif
}

/***********************************************************IRQ18Handler************************************************************/
__WEAK void uart2_interrupt_receive(void)
{
    NVIC_ClearPendingIRQ(SR2_IRQn);
}
__WEAK void spi21_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI21_IRQn);
}
__WEAK void iic21_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIC21_IRQn);
}

void IRQ18_Handler(void)
{
#if defined(USE_SCI_UART2_RX)	
    uart2_interrupt_receive();
#elif defined(USE_SCI_SPI21)		
    spi21_interrupt();
#elif defined(USE_SCI_IIC21)		
    iic21_interrupt();
#endif
}

/***********************************************************IRQ19Handler************************************************************/
__WEAK void sre2_interrupt(void)
{
    NVIC_ClearPendingIRQ(SRE2_IRQn);
}

void IRQ19_Handler(void)
{
    sre2_interrupt();
}

/***********************************************************IRQ20Handler************************************************************/
__WEAK void uart3_interrupt_send(void)
{
    NVIC_ClearPendingIRQ(ST3_IRQn);
}
__WEAK void spi30_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI30_IRQn);
}
__WEAK void iic30_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIC30_IRQn);
}

void IRQ20_Handler(void)
{
#if defined(USE_SCI_UART3_TX)		
    uart3_interrupt_send();
#elif defined(USE_SCI_SPI30)		
    spi30_interrupt();
#elif defined(USE_SCI_IIC30)		
    iic30_interrupt();
#endif
}

/***********************************************************IRQ21Handler************************************************************/
__WEAK void uart3_interrupt_receive(void)
{
    NVIC_ClearPendingIRQ(SR3_IRQn);
}
__WEAK void spi31_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI31_IRQn);
}
__WEAK void iic31_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIC31_IRQn);
}

void IRQ21_Handler(void)
{
#if defined(USE_SCI_UART3_RX)		
    uart3_interrupt_receive();
#elif defined(USE_SCI_SPI31)			
    spi31_interrupt();
#elif defined(USE_SCI_IIC31)		
    iic31_interrupt();
#endif
}

/***********************************************************IRQ22Handler************************************************************/
__WEAK void sre3_interrupt(void)
{
    NVIC_ClearPendingIRQ(SRE3_IRQn);
}

void IRQ22_Handler(void)
{
    sre3_interrupt();
}

/***********************************************************IRQ23Handler************************************************************/
__WEAK void iica0_interrupt(void)
{
    NVIC_ClearPendingIRQ(IICA0_IRQn);
}

void IRQ23_Handler(void)
{
    iica0_interrupt();
}

/***********************************************************IRQ24Handler************************************************************/
__WEAK void iica1_interrupt(void)
{
    NVIC_ClearPendingIRQ(IICA1_IRQn);
}

void IRQ24_Handler(void)
{
    iica1_interrupt();
}

/***********************************************************IRQ25Handler************************************************************/
__WEAK void spi0_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI0_IRQn);
}

void IRQ25_Handler(void)
{
    spi0_interrupt();
}

/***********************************************************IRQ26Handler************************************************************/
__WEAK void spi1_interrupt(void)
{
    NVIC_ClearPendingIRQ(SPI1_IRQn);
}

void IRQ26_Handler(void)
{
    spi1_interrupt();
}

/***********************************************************IRQ27Handler************************************************************/
__WEAK void tm00_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM00_IRQn);
}

void IRQ27_Handler(void)
{
    tm00_interrupt();
}

/***********************************************************IRQ28Handler************************************************************/
__WEAK void tm01_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM01_IRQn);
}

void IRQ28_Handler(void)
{
    tm01_interrupt();
}

/***********************************************************IRQ29Handler************************************************************/
__WEAK void tm02_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM02_IRQn);
}

void IRQ29_Handler(void)
{
    tm02_interrupt();
}

/***********************************************************IRQ30Handler************************************************************/
__WEAK void tm03_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM03_IRQn);
}

void IRQ30_Handler(void)
{
    tm03_interrupt();
}

/***********************************************************IRQ31Handler************************************************************/
__WEAK void tm04_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM04_IRQn);
}

void IRQ31_Handler(void)
{
    tm04_interrupt();
}

/***********************************************************IRQ32Handler************************************************************/
__WEAK void tm05_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM05_IRQn);
}

void IRQ32_Handler(void)
{
    tm05_interrupt();
}

/***********************************************************IRQ33Handler************************************************************/
__WEAK void tm06_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM06_IRQn);
}

void IRQ33_Handler(void)
{
    tm06_interrupt();
}

/***********************************************************IRQ34Handler************************************************************/
__WEAK void tm07_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM07_IRQn);
}

void IRQ34_Handler(void)
{
    tm07_interrupt();
}

/***********************************************************IRQ35Handler************************************************************/
__WEAK void tm01h_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM01H_IRQn);
}

void IRQ35_Handler(void)
{
    tm01h_interrupt();
}

/***********************************************************IRQ36Handler************************************************************/
__WEAK void tm03h_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM03H_IRQn);
}

void IRQ36_Handler(void)
{
    tm03h_interrupt();
}

/***********************************************************IRQ37Handler************************************************************/
__WEAK void tm10_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM10_IRQn);
}

void IRQ37_Handler(void)
{
    tm10_interrupt();
}

/***********************************************************IRQ38Handler************************************************************/
__WEAK void tm11_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM11_IRQn);
}

void IRQ38_Handler(void)
{
    tm11_interrupt();
}

/***********************************************************IRQ39Handler************************************************************/
__WEAK void tm12_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM12_IRQn);
}

void IRQ39_Handler(void)
{
    tm12_interrupt();
}

/***********************************************************IRQ40Handler************************************************************/
__WEAK void tm13_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM13_IRQn);
}

void IRQ40_Handler(void)
{
    tm13_interrupt();
}

/***********************************************************IRQ41Handler************************************************************/
__WEAK void tm14_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM14_IRQn);
}

void IRQ41_Handler(void)
{
    tm14_interrupt();
}

/***********************************************************IRQ42Handler************************************************************/
__WEAK void tm15_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM15_IRQn);
}

void IRQ42_Handler(void)
{
    tm15_interrupt();
}

/***********************************************************IRQ43Handler************************************************************/
__WEAK void tm16_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM16_IRQn);
}

void IRQ43_Handler(void)
{
    tm16_interrupt();
}

/***********************************************************IRQ44Handler************************************************************/
__WEAK void tm17_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM17_IRQn);
}

void IRQ44_Handler(void)
{
    tm17_interrupt();
}

/***********************************************************IRQ45Handler************************************************************/
__WEAK void tm11h_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM11H_IRQn);
}

void IRQ45_Handler(void)
{
    tm11h_interrupt();
}

/***********************************************************IRQ46Handler************************************************************/
__WEAK void tm13h_interrupt(void)
{
    NVIC_ClearPendingIRQ(TM13H_IRQn);
}

void IRQ46_Handler(void)
{
    tm13h_interrupt();
}

/***********************************************************IRQ47Handler************************************************************/
__WEAK void adc0_adireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC0_ADIREQ_N_IRQn);
}

void IRQ47_Handler(void)
{
    adc0_adireq_n_interrupt();
}

/***********************************************************IRQ48Handler************************************************************/
__WEAK void adc1_adireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC1_ADIREQ_N_IRQn);
}

void IRQ48_Handler(void)
{
    adc1_adireq_n_interrupt();
}

/***********************************************************IRQ49Handler************************************************************/
__WEAK void adc2_adireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC2_ADIREQ_N_IRQn);
}

void IRQ49_Handler(void)
{
    adc2_adireq_n_interrupt();
}

/***********************************************************IRQ50Handler************************************************************/
__WEAK void adc0_gbadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC0_GBADIREQ_N_IRQn);
}

void IRQ50_Handler(void)
{
    adc0_gbadireq_n_interrupt();
}

/***********************************************************IRQ51Handler************************************************************/
__WEAK void adc1_gbadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC1_GBADIREQ_N_IRQn);
}

void IRQ51_Handler(void)
{
    adc1_gbadireq_n_interrupt();
}

/***********************************************************IRQ52Handler************************************************************/
__WEAK void adc2_gbadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC2_GBADIREQ_N_IRQn);
}

void IRQ52_Handler(void)
{
    adc2_gbadireq_n_interrupt();
}

/***********************************************************IRQ53Handler************************************************************/
__WEAK void adc0_gcadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC0_GCADIREQ_N_IRQn);
}

void IRQ53_Handler(void)
{
    adc0_gcadireq_n_interrupt();
}

/***********************************************************IRQ54Handler************************************************************/
__WEAK void adc1_gcadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC1_GCADIREQ_N_IRQn);
}

void IRQ54_Handler(void)
{
    adc1_gcadireq_n_interrupt();
}

/***********************************************************IRQ55Handler************************************************************/
__WEAK void adc2_gcadireq_n_interrupt(void)
{
    NVIC_ClearPendingIRQ(ADC2_GCADIREQ_N_IRQn);
}

void IRQ55_Handler(void)
{
    adc2_gcadireq_n_interrupt();
}

/***********************************************************IRQ56Handler************************************************************/
__WEAK void rtc_interrupt(void)
{
    NVIC_ClearPendingIRQ(RTC_IRQn);
}

void IRQ56_Handler(void)
{
    rtc_interrupt();
}

/***********************************************************IRQ57Handler************************************************************/
__WEAK void it_interrupt(void)
{
    NVIC_ClearPendingIRQ(IT_IRQn);
}

void IRQ57_Handler(void)
{
    it_interrupt();
}

/***********************************************************IRQ58Handler************************************************************/
__WEAK void kr_interrupt(void)
{
    NVIC_ClearPendingIRQ(KR_IRQn);
}

void IRQ58_Handler(void)
{
    kr_interrupt();
}

/***********************************************************IRQ59Handler************************************************************/
__WEAK void cmp0_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP0_IRQn);
}

void IRQ59_Handler(void)
{
    cmp0_interrupt();
}

/***********************************************************IRQ60Handler************************************************************/
__WEAK void cmp1_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP1_IRQn);
}

void IRQ60_Handler(void)
{
    cmp1_interrupt();
}

/***********************************************************IRQ61Handler************************************************************/
__WEAK void cmp2_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP2_IRQn);
}

void IRQ61_Handler(void)
{
    cmp2_interrupt();
}

/***********************************************************IRQ62Handler************************************************************/
__WEAK void cmp3_interrupt(void)
{
    NVIC_ClearPendingIRQ(CMP3_IRQn);
}

void IRQ62_Handler(void)
{
    cmp3_interrupt();
}

/***********************************************************IRQ63Handler************************************************************/
__WEAK void c0err_interrupt(void)
{
    NVIC_ClearPendingIRQ(C0ERR_IRQn);
}

void IRQ63_Handler(void)
{
    c0err_interrupt();
}

/***********************************************************IRQ64Handler************************************************************/
__WEAK void c0rec_interrupt(void)
{
    NVIC_ClearPendingIRQ(C0REC_IRQn);
}

void IRQ64_Handler(void)
{
    c0rec_interrupt();
}

/***********************************************************IRQ65Handler************************************************************/
__WEAK void c0wup_interrupt(void)
{
    NVIC_ClearPendingIRQ(C0WUP_IRQn);
}

void IRQ65_Handler(void)
{
    c0wup_interrupt();
}

/***********************************************************IRQ66Handler************************************************************/
__WEAK void c0trx_interrupt(void)
{
    NVIC_ClearPendingIRQ(C0TRX_IRQn);
}

void IRQ66_Handler(void)
{
    c0trx_interrupt();
}

/***********************************************************IRQ67Handler************************************************************/
__WEAK void lcdb_interrupt(void)
{
    NVIC_ClearPendingIRQ(LCDB_IRQn);
}

void IRQ67_Handler(void)
{
    lcdb_interrupt();
}

/***********************************************************IRQ68Handler************************************************************/
__WEAK void qspi_interrupt(void)
{
    NVIC_ClearPendingIRQ(QSPI_IRQn);
}

void IRQ68_Handler(void)
{
    qspi_interrupt();
}

/***********************************************************IRQ69Handler************************************************************/
__WEAK void qspi_dmareq_interrupt(void)
{
    NVIC_ClearPendingIRQ(QSPI_DMAREQ_IRQn);
}

void IRQ69_Handler(void)
{
    qspi_dmareq_interrupt();
}

/***********************************************************IRQ70Handler************************************************************/
__WEAK void fl_interrupt(void)
{
    NVIC_ClearPendingIRQ(FL_IRQn);
}

void IRQ70_Handler(void)
{
    fl_interrupt();
}

/***********************************************************IRQ71Handler************************************************************/
__WEAK void osdc_interrupt(void)
{
    NVIC_ClearPendingIRQ(OSDC_IRQn);
}

void IRQ71_Handler(void)
{
    osdc_interrupt();
}

/***********************************************************IRQ72Handler************************************************************/
__WEAK void pgi0_interrupt(void)
{
    NVIC_ClearPendingIRQ(PGI0_IRQn);
}

void IRQ72_Handler(void)
{
    pgi0_interrupt();
}

/***********************************************************IRQ73Handler************************************************************/
__WEAK void pgi1_interrupt(void)
{
    NVIC_ClearPendingIRQ(PGI1_IRQn);
}

void IRQ73_Handler(void)
{
    pgi1_interrupt();
}

/***********************************************************IRQ74Handler************************************************************/
__WEAK void pgi2_interrupt(void)
{
    NVIC_ClearPendingIRQ(PGI2_IRQn);
}

void IRQ74_Handler(void)
{
    pgi2_interrupt();
}

/***********************************************************IRQ75Handler************************************************************/
__WEAK void pgi3_interrupt(void)
{
    NVIC_ClearPendingIRQ(PGI3_IRQn);
}

void IRQ75_Handler(void)
{
    pgi3_interrupt();
}

/***********************************************************IRQ76Handler************************************************************/
__WEAK void gpt0_elccmpa0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPA0_IRQn);
}

void IRQ76_Handler(void)
{
    gpt0_elccmpa0_interrupt();
}

/***********************************************************IRQ77Handler************************************************************/
__WEAK void gpt0_elccmpb0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPB0_IRQn);
}

void IRQ77_Handler(void)
{
    gpt0_elccmpb0_interrupt();
}

/***********************************************************IRQ78Handler************************************************************/
__WEAK void gpt0_elccmpc0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPC0_IRQn);
}

void IRQ78_Handler(void)
{
    gpt0_elccmpc0_interrupt();
}

/***********************************************************IRQ79Handler************************************************************/
__WEAK void gpt0_elccmpd0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPD0_IRQn);
}

void IRQ79_Handler(void)
{
    gpt0_elccmpd0_interrupt();
}

/***********************************************************IRQ80Handler************************************************************/
__WEAK void gpt0_elccmpe0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPE0_IRQn);
}

void IRQ80_Handler(void)
{
    gpt0_elccmpe0_interrupt();
}

/***********************************************************IRQ81Handler************************************************************/
__WEAK void gpt0_elccmpf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPF0_IRQn);
}

void IRQ81_Handler(void)
{
    gpt0_elccmpf0_interrupt();
}

/***********************************************************IRQ82Handler************************************************************/
__WEAK void gpt0_elcovf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCOVF0_IRQn);
}

void IRQ82_Handler(void)
{
    gpt0_elcovf0_interrupt();
}

/***********************************************************IRQ83Handler************************************************************/
__WEAK void gpt0_elcudf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCUDF0_IRQn);
}

void IRQ83_Handler(void)
{
    gpt0_elcudf0_interrupt();
}

/***********************************************************IRQ84Handler************************************************************/
__WEAK void gpt0_elccmpa1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPA1_IRQn);
}

void IRQ84_Handler(void)
{
    gpt0_elccmpa1_interrupt();
}

/***********************************************************IRQ85Handler************************************************************/
__WEAK void gpt0_elccmpb1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPB1_IRQn);
}

void IRQ85_Handler(void)
{
    gpt0_elccmpb1_interrupt();
}

/***********************************************************IRQ86Handler************************************************************/
__WEAK void gpt0_elccmpc1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPC1_IRQn);
}

void IRQ86_Handler(void)
{
    gpt0_elccmpc1_interrupt();
}

/***********************************************************IRQ87Handler************************************************************/
__WEAK void gpt0_elccmpd1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPD1_IRQn);
}

void IRQ87_Handler(void)
{
    gpt0_elccmpd1_interrupt();
}

/***********************************************************IRQ88Handler************************************************************/
__WEAK void gpt0_elccmpe1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPE1_IRQn);
}

void IRQ88_Handler(void)
{
    gpt0_elccmpe1_interrupt();
}

/***********************************************************IRQ89Handler************************************************************/
__WEAK void gpt0_elccmpf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPF1_IRQn);
}

void IRQ89_Handler(void)
{
    gpt0_elccmpf1_interrupt();
}

/***********************************************************IRQ90Handler************************************************************/
__WEAK void gpt0_elcovf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCOVF1_IRQn);
}

void IRQ90_Handler(void)
{
    gpt0_elcovf1_interrupt();
}

/***********************************************************IRQ91Handler************************************************************/
__WEAK void gpt0_elcudf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCUDF1_IRQn);
}

void IRQ91_Handler(void)
{
    gpt0_elcudf1_interrupt();
}

/***********************************************************IRQ92Handler************************************************************/
__WEAK void gpt0_elccmpa2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPA2_IRQn);
}

void IRQ92_Handler(void)
{
    gpt0_elccmpa2_interrupt();
}

/***********************************************************IRQ93Handler************************************************************/
__WEAK void gpt0_elccmpb2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPB2_IRQn);
}

void IRQ93_Handler(void)
{
    gpt0_elccmpb2_interrupt();
}

/***********************************************************IRQ94Handler************************************************************/
__WEAK void gpt0_elccmpc2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPC2_IRQn);
}

void IRQ94_Handler(void)
{
    gpt0_elccmpc2_interrupt();
}

/***********************************************************IRQ95Handler************************************************************/
__WEAK void gpt0_elccmpd2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPD2_IRQn);
}

void IRQ95_Handler(void)
{
    gpt0_elccmpd2_interrupt();
}

/***********************************************************IRQ96Handler************************************************************/
__WEAK void gpt0_elccmpe2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPE2_IRQn);
}

void IRQ96_Handler(void)
{
    gpt0_elccmpe2_interrupt();
}

/***********************************************************IRQ97Handler************************************************************/
__WEAK void gpt0_elccmpf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPF2_IRQn);
}

void IRQ97_Handler(void)
{
    gpt0_elccmpf2_interrupt();
}

/***********************************************************IRQ98Handler************************************************************/
__WEAK void gpt0_elcovf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCOVF2_IRQn);
}

void IRQ98_Handler(void)
{
    gpt0_elcovf2_interrupt();
}

/***********************************************************IRQ99Handler************************************************************/
__WEAK void gpt0_elcudf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCUDF2_IRQn);
}

void IRQ99_Handler(void)
{
    gpt0_elcudf2_interrupt();
}

/***********************************************************IRQ100Handler************************************************************/
__WEAK void gpt0_elccmpa3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPA3_IRQn);
}

void IRQ100_Handler(void)
{
    gpt0_elccmpa3_interrupt();
}

/***********************************************************IRQ101Handler************************************************************/
__WEAK void gpt0_elccmpb3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPB3_IRQn);
}

void IRQ101_Handler(void)
{
    gpt0_elccmpb3_interrupt();
}

/***********************************************************IRQ102Handler************************************************************/
__WEAK void gpt0_elccmpc3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPC3_IRQn);
}

void IRQ102_Handler(void)
{
    gpt0_elccmpc3_interrupt();
}

/***********************************************************IRQ103Handler************************************************************/
__WEAK void gpt0_elccmpd3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPD3_IRQn);
}

void IRQ103_Handler(void)
{
    gpt0_elccmpd3_interrupt();
}

/***********************************************************IRQ104Handler************************************************************/
__WEAK void gpt0_elccmpe3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPE3_IRQn);
}

void IRQ104_Handler(void)
{
    gpt0_elccmpe3_interrupt();
}

/***********************************************************IRQ105Handler************************************************************/
__WEAK void gpt0_elccmpf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCCMPF3_IRQn);
}

void IRQ105_Handler(void)
{
    gpt0_elccmpf3_interrupt();
}

/***********************************************************IRQ106Handler************************************************************/
__WEAK void gpt0_elcovf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCOVF3_IRQn);
}

void IRQ106_Handler(void)
{
    gpt0_elcovf3_interrupt();
}

/***********************************************************IRQ107Handler************************************************************/
__WEAK void gpt0_elcudf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT0_ELCUDF3_IRQn);
}

void IRQ107_Handler(void)
{
    gpt0_elcudf3_interrupt();
}

/***********************************************************IRQ108Handler************************************************************/
__WEAK void gpt1_elccmpa0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA0_IRQn);
}

void IRQ108_Handler(void)
{
    gpt1_elccmpa0_interrupt();
}

/***********************************************************IRQ109Handler************************************************************/
__WEAK void gpt1_elccmpb0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB0_IRQn);
}

void IRQ109_Handler(void)
{
    gpt1_elccmpb0_interrupt();
}

/***********************************************************IRQ110Handler************************************************************/
__WEAK void gpt1_elccmpc0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC0_IRQn);
}

void IRQ110_Handler(void)
{
    gpt1_elccmpc0_interrupt();
}

/***********************************************************IRQ111Handler************************************************************/
__WEAK void gpt1_elccmpd0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD0_IRQn);
}

void IRQ111_Handler(void)
{
    gpt1_elccmpd0_interrupt();
}

/***********************************************************IRQ112Handler************************************************************/
__WEAK void gpt1_elccmpe0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE0_IRQn);
}

void IRQ112_Handler(void)
{
    gpt1_elccmpe0_interrupt();
}

/***********************************************************IRQ113Handler************************************************************/
__WEAK void gpt1_elccmpf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF0_IRQn);
}

void IRQ113_Handler(void)
{
    gpt1_elccmpf0_interrupt();
}

/***********************************************************IRQ114Handler************************************************************/
__WEAK void gpt1_elcovf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF0_IRQn);
}

void IRQ114_Handler(void)
{
    gpt1_elcovf0_interrupt();
}

/***********************************************************IRQ115Handler************************************************************/
__WEAK void gpt1_elcudf0_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF0_IRQn);
}

void IRQ115_Handler(void)
{
    gpt1_elcudf0_interrupt();
}

/***********************************************************IRQ116Handler************************************************************/
__WEAK void gpt1_elccmpa1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA1_IRQn);
}

void IRQ116_Handler(void)
{
    gpt1_elccmpa1_interrupt();
}

/***********************************************************IRQ117Handler************************************************************/
__WEAK void gpt1_elccmpb1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB1_IRQn);
}

void IRQ117_Handler(void)
{
    gpt1_elccmpb1_interrupt();
}

/***********************************************************IRQ118Handler************************************************************/
__WEAK void gpt1_elccmpc1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC1_IRQn);
}

void IRQ118_Handler(void)
{
    gpt1_elccmpc1_interrupt();
}

/***********************************************************IRQ119Handler************************************************************/
__WEAK void gpt1_elccmpd1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD1_IRQn);
}

void IRQ119_Handler(void)
{
    gpt1_elccmpd1_interrupt();
}

/***********************************************************IRQ120Handler************************************************************/
__WEAK void gpt1_elccmpe1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE1_IRQn);
}

void IRQ120_Handler(void)
{
    gpt1_elccmpe1_interrupt();
}

/***********************************************************IRQ121Handler************************************************************/
__WEAK void gpt1_elccmpf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF1_IRQn);
}

void IRQ121_Handler(void)
{
    gpt1_elccmpf1_interrupt();
}

/***********************************************************IRQ122Handler************************************************************/
__WEAK void gpt1_elcovf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF1_IRQn);
}

void IRQ122_Handler(void)
{
    gpt1_elcovf1_interrupt();
}

/***********************************************************IRQ123Handler************************************************************/
__WEAK void gpt1_elcudf1_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF1_IRQn);
}

void IRQ123_Handler(void)
{
    gpt1_elcudf1_interrupt();
}

/***********************************************************IRQ124Handler************************************************************/
__WEAK void gpt1_elccmpa2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA2_IRQn);
}

void IRQ124_Handler(void)
{
    gpt1_elccmpa2_interrupt();
}

/***********************************************************IRQ125Handler************************************************************/
__WEAK void gpt1_elccmpb2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB2_IRQn);
}

void IRQ125_Handler(void)
{
    gpt1_elccmpb2_interrupt();
}

/***********************************************************IRQ126Handler************************************************************/
__WEAK void gpt1_elccmpc2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC2_IRQn);
}

void IRQ126_Handler(void)
{
    gpt1_elccmpc2_interrupt();
}

/***********************************************************IRQ127Handler************************************************************/
__WEAK void gpt1_elccmpd2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD2_IRQn);
}

void IRQ127_Handler(void)
{
    gpt1_elccmpd2_interrupt();
}

/***********************************************************IRQ128Handler************************************************************/
__WEAK void gpt1_elccmpe2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE2_IRQn);
}

void IRQ128_Handler(void)
{
    gpt1_elccmpe2_interrupt();
}

/***********************************************************IRQ129Handler************************************************************/
__WEAK void gpt1_elccmpf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF2_IRQn);
}

void IRQ129_Handler(void)
{
    gpt1_elccmpf2_interrupt();
}

/***********************************************************IRQ130Handler************************************************************/
__WEAK void gpt1_elcovf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF2_IRQn);
}

void IRQ130_Handler(void)
{
    gpt1_elcovf2_interrupt();
}

/***********************************************************IRQ131Handler************************************************************/
__WEAK void gpt1_elcudf2_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF2_IRQn);
}

void IRQ131_Handler(void)
{
    gpt1_elcudf2_interrupt();
}

/***********************************************************IRQ132Handler************************************************************/
__WEAK void gpt1_elccmpa3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA3_IRQn);
}

void IRQ132_Handler(void)
{
    gpt1_elccmpa3_interrupt();
}

/***********************************************************IRQ133Handler************************************************************/
__WEAK void gpt1_elccmpb3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB3_IRQn);
}

void IRQ133_Handler(void)
{
    gpt1_elccmpb3_interrupt();
}

/***********************************************************IRQ134Handler************************************************************/
__WEAK void gpt1_elccmpc3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC3_IRQn);
}

void IRQ134_Handler(void)
{
    gpt1_elccmpc3_interrupt();
}

/***********************************************************IRQ135Handler************************************************************/
__WEAK void gpt1_elccmpd3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD3_IRQn);
}

void IRQ135_Handler(void)
{
    gpt1_elccmpd3_interrupt();
}

/***********************************************************IRQ136Handler************************************************************/
__WEAK void gpt1_elccmpe3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE3_IRQn);
}

void IRQ136_Handler(void)
{
    gpt1_elccmpe3_interrupt();
}

/***********************************************************IRQ137Handler************************************************************/
__WEAK void gpt1_elccmpf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF3_IRQn);
}

void IRQ137_Handler(void)
{
    gpt1_elccmpf3_interrupt();
}

/***********************************************************IRQ138Handler************************************************************/
__WEAK void gpt1_elcovf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF3_IRQn);
}

void IRQ138_Handler(void)
{
    gpt1_elcovf3_interrupt();
}

/***********************************************************IRQ139Handler************************************************************/
__WEAK void gpt1_elcudf3_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF3_IRQn);
}

void IRQ139_Handler(void)
{
    gpt1_elcudf3_interrupt();
}

/***********************************************************IRQ140Handler************************************************************/
__WEAK void gpt1_elccmpa4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA4_IRQn);
}

void IRQ140_Handler(void)
{
    gpt1_elccmpa4_interrupt();
}

/***********************************************************IRQ141Handler************************************************************/
__WEAK void gpt1_elccmpb4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB4_IRQn);
}

void IRQ141_Handler(void)
{
    gpt1_elccmpb4_interrupt();
}

/***********************************************************IRQ142Handler************************************************************/
__WEAK void gpt1_elccmpc4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC4_IRQn);
}

void IRQ142_Handler(void)
{
    gpt1_elccmpc4_interrupt();
}

/***********************************************************IRQ143Handler************************************************************/
__WEAK void gpt1_elccmpd4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD4_IRQn);
}

void IRQ143_Handler(void)
{
    gpt1_elccmpd4_interrupt();
}

/***********************************************************IRQ144Handler************************************************************/
__WEAK void gpt1_elccmpe4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE4_IRQn);
}

void IRQ144_Handler(void)
{
    gpt1_elccmpe4_interrupt();
}

/***********************************************************IRQ145Handler************************************************************/
__WEAK void gpt1_elccmpf4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF4_IRQn);
}

void IRQ145_Handler(void)
{
    gpt1_elccmpf4_interrupt();
}

/***********************************************************IRQ146Handler************************************************************/
__WEAK void gpt1_elcovf4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF4_IRQn);
}

void IRQ146_Handler(void)
{
    gpt1_elcovf4_interrupt();
}

/***********************************************************IRQ147Handler************************************************************/
__WEAK void gpt1_elcudf4_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF4_IRQn);
}

void IRQ147_Handler(void)
{
    gpt1_elcudf4_interrupt();
}

/***********************************************************IRQ148Handler************************************************************/
__WEAK void gpt1_elccmpa5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA5_IRQn);
}

void IRQ148_Handler(void)
{
    gpt1_elccmpa5_interrupt();
}

/***********************************************************IRQ149Handler************************************************************/
__WEAK void gpt1_elccmpb5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB5_IRQn);
}

void IRQ149_Handler(void)
{
    gpt1_elccmpb5_interrupt();
}

/***********************************************************IRQ150Handler************************************************************/
__WEAK void gpt1_elccmpc5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC5_IRQn);
}

void IRQ150_Handler(void)
{
    gpt1_elccmpc5_interrupt();
}

/***********************************************************IRQ151Handler************************************************************/
__WEAK void gpt1_elccmpd5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD5_IRQn);
}

void IRQ151_Handler(void)
{
    gpt1_elccmpd5_interrupt();
}

/***********************************************************IRQ152Handler************************************************************/
__WEAK void gpt1_elccmpe5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE5_IRQn);
}

void IRQ152_Handler(void)
{
    gpt1_elccmpe5_interrupt();
}

/***********************************************************IRQ153Handler************************************************************/
__WEAK void gpt1_elccmpf5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF5_IRQn);
}

void IRQ153_Handler(void)
{
    gpt1_elccmpf5_interrupt();
}

/***********************************************************IRQ154Handler************************************************************/
__WEAK void gpt1_elcovf5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF5_IRQn);
}

void IRQ154_Handler(void)
{
    gpt1_elcovf5_interrupt();
}

/***********************************************************IRQ155Handler************************************************************/
__WEAK void gpt1_elcudf5_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF5_IRQn);
}

void IRQ155_Handler(void)
{
    gpt1_elcudf5_interrupt();
}

/***********************************************************IRQ156Handler************************************************************/
__WEAK void gpt1_elccmpa6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA6_IRQn);
}

void IRQ156_Handler(void)
{
    gpt1_elccmpa6_interrupt();
}

/***********************************************************IRQ157Handler************************************************************/
__WEAK void gpt1_elccmpb6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB6_IRQn);
}

void IRQ157_Handler(void)
{
    gpt1_elccmpb6_interrupt();
}

/***********************************************************IRQ158Handler************************************************************/
__WEAK void gpt1_elccmpc6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC6_IRQn);
}

void IRQ158_Handler(void)
{
    gpt1_elccmpc6_interrupt();
}

/***********************************************************IRQ159Handler************************************************************/
__WEAK void gpt1_elccmpd6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD6_IRQn);
}

void IRQ159_Handler(void)
{
    gpt1_elccmpd6_interrupt();
}

/***********************************************************IRQ160Handler************************************************************/
__WEAK void gpt1_elccmpe6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE6_IRQn);
}

void IRQ160_Handler(void)
{
    gpt1_elccmpe6_interrupt();
}

/***********************************************************IRQ161Handler************************************************************/
__WEAK void gpt1_elccmpf6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF6_IRQn);
}

void IRQ161_Handler(void)
{
    gpt1_elccmpf6_interrupt();
}

/***********************************************************IRQ162Handler************************************************************/
__WEAK void gpt1_elcovf6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF6_IRQn);
}

void IRQ162_Handler(void)
{
    gpt1_elcovf6_interrupt();
}

/***********************************************************IRQ163Handler************************************************************/
__WEAK void gpt1_elcudf6_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF6_IRQn);
}

void IRQ163_Handler(void)
{
    gpt1_elcudf6_interrupt();
}

/***********************************************************IRQ164Handler************************************************************/
__WEAK void gpt1_elccmpa7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPA7_IRQn);
}

void IRQ164_Handler(void)
{
    gpt1_elccmpa7_interrupt();
}

/***********************************************************IRQ165Handler************************************************************/
__WEAK void gpt1_elccmpb7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPB7_IRQn);
}

void IRQ165_Handler(void)
{
    gpt1_elccmpb7_interrupt();
}

/***********************************************************IRQ166Handler************************************************************/
__WEAK void gpt1_elccmpc7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPC7_IRQn);
}

void IRQ166_Handler(void)
{
    gpt1_elccmpc7_interrupt();
}

/***********************************************************IRQ167Handler************************************************************/
__WEAK void gpt1_elccmpd7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPD7_IRQn);
}

void IRQ167_Handler(void)
{
    gpt1_elccmpd7_interrupt();
}

/***********************************************************IRQ168Handler************************************************************/
__WEAK void gpt1_elccmpe7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPE7_IRQn);
}

void IRQ168_Handler(void)
{
    gpt1_elccmpe7_interrupt();
}

/***********************************************************IRQ169Handler************************************************************/
__WEAK void gpt1_elccmpf7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCCMPF7_IRQn);
}

void IRQ169_Handler(void)
{
    gpt1_elccmpf7_interrupt();
}

/***********************************************************IRQ170Handler************************************************************/
__WEAK void gpt1_elcovf7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCOVF7_IRQn);
}

void IRQ170_Handler(void)
{
    gpt1_elcovf7_interrupt();
}

/***********************************************************IRQ171Handler************************************************************/
__WEAK void gpt1_elcudf7_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCUDF7_IRQn);
}

void IRQ171_Handler(void)
{
    gpt1_elcudf7_interrupt();
}

/***********************************************************IRQ172Handler************************************************************/
__WEAK void gpt1_elcedguvw_interrupt(void)
{
    NVIC_ClearPendingIRQ(GPT1_ELCEDGUVW_IRQn);
}

void IRQ172_Handler(void)
{
    gpt1_elcedguvw_interrupt();
}

/***********************************************************IRQ173Handler************************************************************/
__WEAK void aes_wrreq_interrupt(void)
{
    NVIC_ClearPendingIRQ(AES_WRREQ_IRQn);
}

void IRQ173_Handler(void)
{
    aes_wrreq_interrupt();
}

/***********************************************************IRQ174Handler************************************************************/
__WEAK void aes_rdreq_interrupt(void)
{
    NVIC_ClearPendingIRQ(AES_RDREQ_IRQn);
}

void IRQ174_Handler(void)
{
    aes_rdreq_interrupt();
}

/***********************************************************IRQ175Handler************************************************************/
__WEAK void rng_rdreq_interrupt(void)
{
    NVIC_ClearPendingIRQ(RNG_RDREQ_IRQn);
}

void IRQ175_Handler(void)
{
    rng_rdreq_interrupt();
}

/***********************************************************IRQ176Handler************************************************************/
__WEAK void dma0_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA0_IRQn);
}

void IRQ176_Handler(void)
{
    dma0_interrupt();
}

/***********************************************************IRQ177Handler************************************************************/
__WEAK void dma1_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA1_IRQn);
}

void IRQ177_Handler(void)
{
    dma1_interrupt();
}

/***********************************************************IRQ178Handler************************************************************/
__WEAK void dma2_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA2_IRQn);
}

void IRQ178_Handler(void)
{
    dma2_interrupt();
}

/***********************************************************IRQ179Handler************************************************************/
__WEAK void dma3_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA3_IRQn);
}

void IRQ179_Handler(void)
{
    dma3_interrupt();
}

/***********************************************************IRQ180Handler************************************************************/
__WEAK void dma4_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA4_IRQn);
}

void IRQ180_Handler(void)
{
    dma4_interrupt();
}

/***********************************************************IRQ181Handler************************************************************/
__WEAK void dma5_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA5_IRQn);
}

void IRQ181_Handler(void)
{
    dma5_interrupt();
}

/***********************************************************IRQ182Handler************************************************************/
__WEAK void dma6_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA6_IRQn);
}

void IRQ182_Handler(void)
{
    dma6_interrupt();
}

/***********************************************************IRQ183Handler************************************************************/
__WEAK void dma7_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA7_IRQn);
}

void IRQ183_Handler(void)
{
    dma7_interrupt();
}

/***********************************************************IRQ184Handler************************************************************/
__WEAK void dma8_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA8_IRQn);
}

void IRQ184_Handler(void)
{
    dma8_interrupt();
}

/***********************************************************IRQ185Handler************************************************************/
__WEAK void dma9_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA9_IRQn);
}

void IRQ185_Handler(void)
{
    dma9_interrupt();
}

/***********************************************************IRQ186Handler************************************************************/
__WEAK void dma10_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA10_IRQn);
}

void IRQ186_Handler(void)
{
    dma10_interrupt();
}

/***********************************************************IRQ187Handler************************************************************/
__WEAK void dma11_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA11_IRQn);
}

void IRQ187_Handler(void)
{
    dma11_interrupt();
}

/***********************************************************IRQ188Handler************************************************************/
__WEAK void dma12_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA12_IRQn);
}

void IRQ188_Handler(void)
{
    dma12_interrupt();
}

/***********************************************************IRQ189Handler************************************************************/
__WEAK void dma13_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA13_IRQn);
}

void IRQ189_Handler(void)
{
    dma13_interrupt();
}

/***********************************************************IRQ190Handler************************************************************/
__WEAK void dma14_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA14_IRQn);
}

void IRQ190_Handler(void)
{
    dma14_interrupt();
}

/***********************************************************IRQ191Handler************************************************************/
__WEAK void dma15_interrupt(void)
{
    NVIC_ClearPendingIRQ(DMA15_IRQn);
}

void IRQ191_Handler(void)
{
    dma15_interrupt();
}

/***********************************************************IRQ192Handler************************************************************/
__WEAK void ocrv_interrupt(void)
{
    NVIC_ClearPendingIRQ(OCRV_IRQn);
}

void IRQ192_Handler(void)
{
    ocrv_interrupt();
}

/***********************************************************IRQ193Handler************************************************************/
__WEAK void ramparity_interrupt(void)
{
    NVIC_ClearPendingIRQ(RAMPARITY_IRQn);
}

void IRQ193_Handler(void)
{
    ramparity_interrupt();
}

/***********************************************************IRQ194Handler************************************************************/
__WEAK void c1err_interrupt(void)
{
    NVIC_ClearPendingIRQ(C1ERR_IRQn);
}

void IRQ194_Handler(void)
{
    c1err_interrupt();
}

/***********************************************************IRQ195Handler************************************************************/
__WEAK void c1rec_interrupt(void)
{
    NVIC_ClearPendingIRQ(C1REC_IRQn);
}

void IRQ195_Handler(void)
{
    c1rec_interrupt();
}

/***********************************************************IRQ196Handler************************************************************/
__WEAK void c1wup_interrupt(void)
{
    NVIC_ClearPendingIRQ(C1WUP_IRQn);
}

void IRQ196_Handler(void)
{
    c1wup_interrupt();
}

/***********************************************************IRQ197Handler************************************************************/
__WEAK void c1trx_interrupt(void)
{
    NVIC_ClearPendingIRQ(C1TRX_IRQn);
}

void IRQ197_Handler(void)
{
    c1trx_interrupt();
}

/***********************************************************IRQ198Handler************************************************************/
__WEAK void iir0wfifoemp_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIR0WFIFOEMP_IRQn);
}

void IRQ198_Handler(void)
{
    iir0wfifoemp_interrupt();
}

/***********************************************************IRQ199Handler************************************************************/
__WEAK void iir0wfifoful_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIR0WFIFOFUL_IRQn);
}

void IRQ199_Handler(void)
{
    iir0wfifoful_interrupt();
}

/***********************************************************IRQ200Handler************************************************************/
__WEAK void iir1wfifoemp_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIR1WFIFOEMP_IRQn);
}

void IRQ200_Handler(void)
{
    iir1wfifoemp_interrupt();
}

/***********************************************************IRQ201Handler************************************************************/
__WEAK void iir1wfifoful_interrupt(void)
{
    NVIC_ClearPendingIRQ(IIR1WFIFOFUL_IRQn);
}

void IRQ201_Handler(void)
{
    iir1wfifoful_interrupt();
}


