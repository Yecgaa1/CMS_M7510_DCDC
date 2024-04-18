/**************************************************************************//**
 * @file     startup_BAT32G439.c
 * @brief    CMSIS Cortex-M ARMv7-M based Core Device Startup File for
 *           Device <Device>
 * @version  V1.00
 * @date     2019/04/24
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
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
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include "BAT32G439.h"


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
void __NO_RETURN Reset_Handler  (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void IRQ0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQLVI
void IRQ1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQWDT0
void IRQ2_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQWDT1
void IRQ3_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP0
void IRQ4_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP1
void IRQ5_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP2
void IRQ6_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP3
void IRQ7_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP4
void IRQ8_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP5
void IRQ9_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP6
void IRQ10_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQINTP7
void IRQ11_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQST0
void IRQ12_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSR0
void IRQ13_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSRE0
void IRQ14_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQST1
void IRQ15_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSR1
void IRQ16_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSRE1
void IRQ17_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQST2
void IRQ18_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSR2
void IRQ19_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSRE2
void IRQ20_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQST3
void IRQ21_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSR3
void IRQ22_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSRE3
void IRQ23_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIICA0
void IRQ24_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIICA1
void IRQ25_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSPI0
void IRQ26_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQSPI1
void IRQ27_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM00
void IRQ28_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM01
void IRQ29_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM02
void IRQ30_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM03
void IRQ31_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM04
void IRQ32_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM05
void IRQ33_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM06
void IRQ34_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM07
void IRQ35_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM01H
void IRQ36_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM03H
void IRQ37_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM10
void IRQ38_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM11
void IRQ39_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM12
void IRQ40_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM13
void IRQ41_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM14
void IRQ42_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM15
void IRQ43_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM16
void IRQ44_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM17
void IRQ45_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM11H
void IRQ46_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQTM13H
void IRQ47_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC0_ADIREQ_N
void IRQ48_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC1_ADIREQ_N
void IRQ49_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC2_ADIREQ_N
void IRQ50_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC0_GBADIREQ_N
void IRQ51_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC1_GBADIREQ_N
void IRQ52_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC2_GBADIREQ_N
void IRQ53_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC0_GCADIREQ_N
void IRQ54_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC1_GCADIREQ_N
void IRQ55_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQADC2_GCADIREQ_N
void IRQ56_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQRTC
void IRQ57_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIT
void IRQ58_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQKR
void IRQ59_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQCMP0
void IRQ60_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQCMP1
void IRQ61_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQCMP2
void IRQ62_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQCMP3
void IRQ63_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC0ERR
void IRQ64_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC0REC
void IRQ65_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC0WUP
void IRQ66_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC0TRX
void IRQ67_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQLCDB
void IRQ68_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQQSPI
void IRQ69_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQQSPI_DMAREQ
void IRQ70_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQFL
void IRQ71_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQOSDC
void IRQ72_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQPGI0
void IRQ73_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQPGI1
void IRQ74_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQPGI2
void IRQ75_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQPGI3
void IRQ76_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPA0
void IRQ77_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPB0
void IRQ78_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPC0
void IRQ79_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPD0
void IRQ80_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPE0
void IRQ81_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPF0
void IRQ82_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCOVF0
void IRQ83_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCUDF0
void IRQ84_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPA1
void IRQ85_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPB1
void IRQ86_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPC1
void IRQ87_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPD1
void IRQ88_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPE1
void IRQ89_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPF1
void IRQ90_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCOVF1
void IRQ91_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCUDF1
void IRQ92_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPA2
void IRQ93_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPB2
void IRQ94_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPC2
void IRQ95_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPD2
void IRQ96_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPE2
void IRQ97_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPF2
void IRQ98_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCOVF2
void IRQ99_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCUDF2
void IRQ100_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPA3
void IRQ101_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPB3
void IRQ102_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPC3
void IRQ103_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPD3
void IRQ104_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPE3
void IRQ105_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCCMPF3
void IRQ106_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCOVF3
void IRQ107_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT0_ELCUDF3
void IRQ108_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA0
void IRQ109_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB0
void IRQ110_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC0
void IRQ111_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD0
void IRQ112_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE0
void IRQ113_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF0
void IRQ114_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF0
void IRQ115_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF0
void IRQ116_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA1
void IRQ117_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB1
void IRQ118_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC1
void IRQ119_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD1
void IRQ120_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE1
void IRQ121_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF1
void IRQ122_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF1
void IRQ123_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF1
void IRQ124_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA2
void IRQ125_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB2
void IRQ126_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC2
void IRQ127_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD2
void IRQ128_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE2
void IRQ129_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF2
void IRQ130_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF2
void IRQ131_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF2
void IRQ132_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA3
void IRQ133_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB3
void IRQ134_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC3
void IRQ135_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD3
void IRQ136_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE3
void IRQ137_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF3
void IRQ138_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF3
void IRQ139_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF3
void IRQ140_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA4
void IRQ141_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB4
void IRQ142_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC4
void IRQ143_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD4
void IRQ144_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE4
void IRQ145_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF4
void IRQ146_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF4
void IRQ147_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF4
void IRQ148_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA5
void IRQ149_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB5
void IRQ150_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC5
void IRQ151_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD5
void IRQ152_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE5
void IRQ153_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF5
void IRQ154_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF5
void IRQ155_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF5
void IRQ156_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA6
void IRQ157_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB6
void IRQ158_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC6
void IRQ159_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD6
void IRQ160_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE6
void IRQ161_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF6
void IRQ162_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF6
void IRQ163_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF6
void IRQ164_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPA7
void IRQ165_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPB7
void IRQ166_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPC7
void IRQ167_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPD7
void IRQ168_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPE7
void IRQ169_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCCMPF7
void IRQ170_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCOVF7
void IRQ171_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCUDF7
void IRQ172_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQGPT1_ELCEDGUVW
void IRQ173_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQAES_WRREQ
void IRQ174_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQAES_RDREQ
void IRQ175_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQRNG_RDREQ
void IRQ176_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA0
void IRQ177_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA1
void IRQ178_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA2
void IRQ179_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA3
void IRQ180_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA4
void IRQ181_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA5
void IRQ182_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA6
void IRQ183_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA7
void IRQ184_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA8
void IRQ185_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA9
void IRQ186_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA10
void IRQ187_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA11
void IRQ188_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA12
void IRQ189_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA13
void IRQ190_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA14
void IRQ191_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQDMA15
void IRQ192_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQOCRV
void IRQ193_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQRAMPARITY
void IRQ194_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC1ERR
void IRQ195_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC1REC
void IRQ196_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC1WUP
void IRQ197_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQC1TRX
void IRQ198_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIIR0WFIFOEMP
void IRQ199_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIIR0WFIFOFUL
void IRQ200_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIIR1WFIFOEMP
void IRQ201_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));		// IRQIIR1WFIFOFUL


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const pFunc __VECTOR_TABLE[256];
       const pFunc __VECTOR_TABLE[256] __VECTOR_TABLE_ATTRIBUTE = {
  (pFunc)(&__INITIAL_SP),                   /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  MemManage_Handler,                        /* -12 MPU Fault Handler */
  BusFault_Handler,                         /* -11 Bus Fault Handler */
  UsageFault_Handler,                       /* -10 Usage Fault Handler */
  SecureFault_Handler,                      /*  -9 Secure Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  DebugMon_Handler,                         /*  -4 Debug Monitor Handler */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
  IRQ0_Handler, 				 /* 0 IRQLVI  0 */
  IRQ1_Handler, 				 /* 1 IRQWDT0  1 */
  IRQ2_Handler, 				 /* 2 IRQWDT1  2 */
  IRQ3_Handler, 				 /* 3 IRQINTP0  3 */
  IRQ4_Handler, 				 /* 4 IRQINTP1  4 */
  IRQ5_Handler, 				 /* 5 IRQINTP2  5 */
  IRQ6_Handler, 				 /* 6 IRQINTP3  6 */
  IRQ7_Handler, 				 /* 7 IRQINTP4  7 */
  IRQ8_Handler, 				 /* 8 IRQINTP5  8 */
  IRQ9_Handler, 				 /* 9 IRQINTP6  9 */
  IRQ10_Handler, 				 /* 10 IRQINTP7  10 */
  IRQ11_Handler, 				 /* 11 IRQST0  11 */
  IRQ12_Handler, 				 /* 12 IRQSR0  12 */
  IRQ13_Handler, 				 /* 13 IRQSRE0  13 */
  IRQ14_Handler, 				 /* 14 IRQST1  14 */
  IRQ15_Handler, 				 /* 15 IRQSR1  15 */
  IRQ16_Handler, 				 /* 16 IRQSRE1  16 */
  IRQ17_Handler, 				 /* 17 IRQST2  17 */
  IRQ18_Handler, 				 /* 18 IRQSR2  18 */
  IRQ19_Handler, 				 /* 19 IRQSRE2  19 */
  IRQ20_Handler, 				 /* 20 IRQST3  20 */
  IRQ21_Handler, 				 /* 21 IRQSR3  21 */
  IRQ22_Handler, 				 /* 22 IRQSRE3  22 */
  IRQ23_Handler, 				 /* 23 IRQIICA0  23 */
  IRQ24_Handler, 				 /* 24 IRQIICA1  24 */
  IRQ25_Handler, 				 /* 25 IRQSPI0  25 */
  IRQ26_Handler, 				 /* 26 IRQSPI1  26 */
  IRQ27_Handler, 				 /* 27 IRQTM00  27 */
  IRQ28_Handler, 				 /* 28 IRQTM01  28 */
  IRQ29_Handler, 				 /* 29 IRQTM02  29 */
  IRQ30_Handler, 				 /* 30 IRQTM03  30 */
  IRQ31_Handler, 				 /* 31 IRQTM04  31 */
  IRQ32_Handler, 				 /* 32 IRQTM05  32 */
  IRQ33_Handler, 				 /* 33 IRQTM06  33 */
  IRQ34_Handler, 				 /* 34 IRQTM07  34 */
  IRQ35_Handler, 				 /* 35 IRQTM01H  35 */
  IRQ36_Handler, 				 /* 36 IRQTM03H  36 */
  IRQ37_Handler, 				 /* 37 IRQTM10  37 */
  IRQ38_Handler, 				 /* 38 IRQTM11  38 */
  IRQ39_Handler, 				 /* 39 IRQTM12  39 */
  IRQ40_Handler, 				 /* 40 IRQTM13  40 */
  IRQ41_Handler, 				 /* 41 IRQTM14  41 */
  IRQ42_Handler, 				 /* 42 IRQTM15  42 */
  IRQ43_Handler, 				 /* 43 IRQTM16  43 */
  IRQ44_Handler, 				 /* 44 IRQTM17  44 */
  IRQ45_Handler, 				 /* 45 IRQTM11H  45 */
  IRQ46_Handler, 				 /* 46 IRQTM13H  46 */
  IRQ47_Handler, 				 /* 47 IRQADC0_ADIREQ_N  47 */
  IRQ48_Handler, 				 /* 48 IRQADC1_ADIREQ_N  48 */
  IRQ49_Handler, 				 /* 49 IRQADC2_ADIREQ_N  49 */
  IRQ50_Handler, 				 /* 50 IRQADC0_GBADIREQ_N  50 */
  IRQ51_Handler, 				 /* 51 IRQADC1_GBADIREQ_N  51 */
  IRQ52_Handler, 				 /* 52 IRQADC2_GBADIREQ_N  52 */
  IRQ53_Handler, 				 /* 53 IRQADC0_GCADIREQ_N  53 */
  IRQ54_Handler, 				 /* 54 IRQADC1_GCADIREQ_N  54 */
  IRQ55_Handler, 				 /* 55 IRQADC2_GCADIREQ_N  55 */
  IRQ56_Handler, 				 /* 56 IRQRTC  56 */
  IRQ57_Handler, 				 /* 57 IRQIT  57 */
  IRQ58_Handler, 				 /* 58 IRQKR  58 */
  IRQ59_Handler, 				 /* 59 IRQCMP0  59 */
  IRQ60_Handler, 				 /* 60 IRQCMP1  60 */
  IRQ61_Handler, 				 /* 61 IRQCMP2  61 */
  IRQ62_Handler, 				 /* 62 IRQCMP3  62 */
  IRQ63_Handler, 				 /* 63 IRQC0ERR  63 */
  IRQ64_Handler, 				 /* 64 IRQC0REC  64 */
  IRQ65_Handler, 				 /* 65 IRQC0WUP  65 */
  IRQ66_Handler, 				 /* 66 IRQC0TRX  66 */
  IRQ67_Handler, 				 /* 67 IRQLCDB  67 */
  IRQ68_Handler, 				 /* 68 IRQQSPI  68 */
  IRQ69_Handler, 				 /* 69 IRQQSPI_DMAREQ  69 */
  IRQ70_Handler, 				 /* 70 IRQFL  70 */
  IRQ71_Handler, 				 /* 71 IRQOSDC  71 */
  IRQ72_Handler, 				 /* 72 IRQPGI0  72 */
  IRQ73_Handler, 				 /* 73 IRQPGI1  73 */
  IRQ74_Handler, 				 /* 74 IRQPGI2  74 */
  IRQ75_Handler, 				 /* 75 IRQPGI3  75 */
  IRQ76_Handler, 				 /* 76 IRQGPT0_ELCCMPA0  76 */
  IRQ77_Handler, 				 /* 77 IRQGPT0_ELCCMPB0  77 */
  IRQ78_Handler, 				 /* 78 IRQGPT0_ELCCMPC0  78 */
  IRQ79_Handler, 				 /* 79 IRQGPT0_ELCCMPD0  79 */
  IRQ80_Handler, 				 /* 80 IRQGPT0_ELCCMPE0  80 */
  IRQ81_Handler, 				 /* 81 IRQGPT0_ELCCMPF0  81 */
  IRQ82_Handler, 				 /* 82 IRQGPT0_ELCOVF0  82 */
  IRQ83_Handler, 				 /* 83 IRQGPT0_ELCUDF0  83 */
  IRQ84_Handler, 				 /* 84 IRQGPT0_ELCCMPA1  84 */
  IRQ85_Handler, 				 /* 85 IRQGPT0_ELCCMPB1  85 */
  IRQ86_Handler, 				 /* 86 IRQGPT0_ELCCMPC1  86 */
  IRQ87_Handler, 				 /* 87 IRQGPT0_ELCCMPD1  87 */
  IRQ88_Handler, 				 /* 88 IRQGPT0_ELCCMPE1  88 */
  IRQ89_Handler, 				 /* 89 IRQGPT0_ELCCMPF1  89 */
  IRQ90_Handler, 				 /* 90 IRQGPT0_ELCOVF1  90 */
  IRQ91_Handler, 				 /* 91 IRQGPT0_ELCUDF1  91 */
  IRQ92_Handler, 				 /* 92 IRQGPT0_ELCCMPA2  92 */
  IRQ93_Handler, 				 /* 93 IRQGPT0_ELCCMPB2  93 */
  IRQ94_Handler, 				 /* 94 IRQGPT0_ELCCMPC2  94 */
  IRQ95_Handler, 				 /* 95 IRQGPT0_ELCCMPD2  95 */
  IRQ96_Handler, 				 /* 96 IRQGPT0_ELCCMPE2  96 */
  IRQ97_Handler, 				 /* 97 IRQGPT0_ELCCMPF2  97 */
  IRQ98_Handler, 				 /* 98 IRQGPT0_ELCOVF2  98 */
  IRQ99_Handler, 				 /* 99 IRQGPT0_ELCUDF2  99 */
  IRQ100_Handler, 				 /* 100 IRQGPT0_ELCCMPA3  100 */
  IRQ101_Handler, 				 /* 101 IRQGPT0_ELCCMPB3  101 */
  IRQ102_Handler, 				 /* 102 IRQGPT0_ELCCMPC3  102 */
  IRQ103_Handler, 				 /* 103 IRQGPT0_ELCCMPD3  103 */
  IRQ104_Handler, 				 /* 104 IRQGPT0_ELCCMPE3  104 */
  IRQ105_Handler, 				 /* 105 IRQGPT0_ELCCMPF3  105 */
  IRQ106_Handler, 				 /* 106 IRQGPT0_ELCOVF3  106 */
  IRQ107_Handler, 				 /* 107 IRQGPT0_ELCUDF3  107 */
  IRQ108_Handler, 				 /* 108 IRQGPT1_ELCCMPA0  108 */
  IRQ109_Handler, 				 /* 109 IRQGPT1_ELCCMPB0  109 */
  IRQ110_Handler, 				 /* 110 IRQGPT1_ELCCMPC0  110 */
  IRQ111_Handler, 				 /* 111 IRQGPT1_ELCCMPD0  111 */
  IRQ112_Handler, 				 /* 112 IRQGPT1_ELCCMPE0  112 */
  IRQ113_Handler, 				 /* 113 IRQGPT1_ELCCMPF0  113 */
  IRQ114_Handler, 				 /* 114 IRQGPT1_ELCOVF0  114 */
  IRQ115_Handler, 				 /* 115 IRQGPT1_ELCUDF0  115 */
  IRQ116_Handler, 				 /* 116 IRQGPT1_ELCCMPA1  116 */
  IRQ117_Handler, 				 /* 117 IRQGPT1_ELCCMPB1  117 */
  IRQ118_Handler, 				 /* 118 IRQGPT1_ELCCMPC1  118 */
  IRQ119_Handler, 				 /* 119 IRQGPT1_ELCCMPD1  119 */
  IRQ120_Handler, 				 /* 120 IRQGPT1_ELCCMPE1  120 */
  IRQ121_Handler, 				 /* 121 IRQGPT1_ELCCMPF1  121 */
  IRQ122_Handler, 				 /* 122 IRQGPT1_ELCOVF1  122 */
  IRQ123_Handler, 				 /* 123 IRQGPT1_ELCUDF1  123 */
  IRQ124_Handler, 				 /* 124 IRQGPT1_ELCCMPA2  124 */
  IRQ125_Handler, 				 /* 125 IRQGPT1_ELCCMPB2  125 */
  IRQ126_Handler, 				 /* 126 IRQGPT1_ELCCMPC2  126 */
  IRQ127_Handler, 				 /* 127 IRQGPT1_ELCCMPD2  127 */
  IRQ128_Handler, 				 /* 128 IRQGPT1_ELCCMPE2  128 */
  IRQ129_Handler, 				 /* 129 IRQGPT1_ELCCMPF2  129 */
  IRQ130_Handler, 				 /* 130 IRQGPT1_ELCOVF2  130 */
  IRQ131_Handler, 				 /* 131 IRQGPT1_ELCUDF2  131 */
  IRQ132_Handler, 				 /* 132 IRQGPT1_ELCCMPA3  132 */
  IRQ133_Handler, 				 /* 133 IRQGPT1_ELCCMPB3  133 */
  IRQ134_Handler, 				 /* 134 IRQGPT1_ELCCMPC3  134 */
  IRQ135_Handler, 				 /* 135 IRQGPT1_ELCCMPD3  135 */
  IRQ136_Handler, 				 /* 136 IRQGPT1_ELCCMPE3  136 */
  IRQ137_Handler, 				 /* 137 IRQGPT1_ELCCMPF3  137 */
  IRQ138_Handler, 				 /* 138 IRQGPT1_ELCOVF3  138 */
  IRQ139_Handler, 				 /* 139 IRQGPT1_ELCUDF3  139 */
  IRQ140_Handler, 				 /* 140 IRQGPT1_ELCCMPA4  140 */
  IRQ141_Handler, 				 /* 141 IRQGPT1_ELCCMPB4  141 */
  IRQ142_Handler, 				 /* 142 IRQGPT1_ELCCMPC4  142 */
  IRQ143_Handler, 				 /* 143 IRQGPT1_ELCCMPD4  143 */
  IRQ144_Handler, 				 /* 144 IRQGPT1_ELCCMPE4  144 */
  IRQ145_Handler, 				 /* 145 IRQGPT1_ELCCMPF4  145 */
  IRQ146_Handler, 				 /* 146 IRQGPT1_ELCOVF4  146 */
  IRQ147_Handler, 				 /* 147 IRQGPT1_ELCUDF4  147 */
  IRQ148_Handler, 				 /* 148 IRQGPT1_ELCCMPA5  148 */
  IRQ149_Handler, 				 /* 149 IRQGPT1_ELCCMPB5  149 */
  IRQ150_Handler, 				 /* 150 IRQGPT1_ELCCMPC5  150 */
  IRQ151_Handler, 				 /* 151 IRQGPT1_ELCCMPD5  151 */
  IRQ152_Handler, 				 /* 152 IRQGPT1_ELCCMPE5  152 */
  IRQ153_Handler, 				 /* 153 IRQGPT1_ELCCMPF5  153 */
  IRQ154_Handler, 				 /* 154 IRQGPT1_ELCOVF5  154 */
  IRQ155_Handler, 				 /* 155 IRQGPT1_ELCUDF5  155 */
  IRQ156_Handler, 				 /* 156 IRQGPT1_ELCCMPA6  156 */
  IRQ157_Handler, 				 /* 157 IRQGPT1_ELCCMPB6  157 */
  IRQ158_Handler, 				 /* 158 IRQGPT1_ELCCMPC6  158 */
  IRQ159_Handler, 				 /* 159 IRQGPT1_ELCCMPD6  159 */
  IRQ160_Handler, 				 /* 160 IRQGPT1_ELCCMPE6  160 */
  IRQ161_Handler, 				 /* 161 IRQGPT1_ELCCMPF6  161 */
  IRQ162_Handler, 				 /* 162 IRQGPT1_ELCOVF6  162 */
  IRQ163_Handler, 				 /* 163 IRQGPT1_ELCUDF6  163 */
  IRQ164_Handler, 				 /* 164 IRQGPT1_ELCCMPA7  164 */
  IRQ165_Handler, 				 /* 165 IRQGPT1_ELCCMPB7  165 */
  IRQ166_Handler, 				 /* 166 IRQGPT1_ELCCMPC7  166 */
  IRQ167_Handler, 				 /* 167 IRQGPT1_ELCCMPD7  167 */
  IRQ168_Handler, 				 /* 168 IRQGPT1_ELCCMPE7  168 */
  IRQ169_Handler, 				 /* 169 IRQGPT1_ELCCMPF7  169 */
  IRQ170_Handler, 				 /* 170 IRQGPT1_ELCOVF7  170 */
  IRQ171_Handler, 				 /* 171 IRQGPT1_ELCUDF7  171 */
  IRQ172_Handler, 				 /* 172 IRQGPT1_ELCEDGUVW  172 */
  IRQ173_Handler, 				 /* 173 IRQAES_WRREQ  173 */
  IRQ174_Handler, 				 /* 174 IRQAES_RDREQ  174 */
  IRQ175_Handler, 				 /* 175 IRQRNG_RDREQ  175 */
  IRQ176_Handler, 				 /* 176 IRQDMA0  176 */
  IRQ177_Handler, 				 /* 177 IRQDMA1  177 */
  IRQ178_Handler, 				 /* 178 IRQDMA2  178 */
  IRQ179_Handler, 				 /* 179 IRQDMA3  179 */
  IRQ180_Handler, 				 /* 180 IRQDMA4  180 */
  IRQ181_Handler, 				 /* 181 IRQDMA5  181 */
  IRQ182_Handler, 				 /* 182 IRQDMA6  182 */
  IRQ183_Handler, 				 /* 183 IRQDMA7  183 */
  IRQ184_Handler, 				 /* 184 IRQDMA8  184 */
  IRQ185_Handler, 				 /* 185 IRQDMA9  185 */
  IRQ186_Handler, 				 /* 186 IRQDMA10  186 */
  IRQ187_Handler, 				 /* 187 IRQDMA11  187 */
  IRQ188_Handler, 				 /* 188 IRQDMA12  188 */
  IRQ189_Handler, 				 /* 189 IRQDMA13  189 */
  IRQ190_Handler, 				 /* 190 IRQDMA14  190 */
  IRQ191_Handler, 				 /* 191 IRQDMA15  191 */
  IRQ192_Handler, 				 /* 192 IRQOCRV  192 */
  IRQ193_Handler, 				 /* 193 IRQRAMPARITY  193 */
  IRQ194_Handler, 				 /* 194 IRQC1ERR  194 */
  IRQ195_Handler, 				 /* 195 IRQC1REC  195 */
  IRQ196_Handler, 				 /* 196 IRQC1WUP  196 */
  IRQ197_Handler, 				 /* 197 IRQC1TRX  197 */
  IRQ198_Handler, 				 /* 198 IRQIIR0WFIFOEMP  198 */
  IRQ199_Handler, 				 /* 199 IRQIIR0WFIFOFUL  199 */
  IRQ200_Handler, 				 /* 200 IRQIIR1WFIFOEMP  200 */
  IRQ201_Handler  				 /* 201 IRQIIR1WFIFOFUL  201 */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  __set_MSPLIM((uint32_t)(&__STACK_LIMIT));

  SystemInit();                             /* CMSIS System Initialization */
  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}


/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
