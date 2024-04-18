;/**************************************************************************//**
; * @file     startup_BAT32G439.s
; * @brief    CMSIS Cortex-M ARMv6-M based Core Device Startup File for
; *           Device BAT32G439
; * @version  V1.00
; * @date     2019/04/24
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */
;/*

;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  Stack_Mem
Stack_Mem       SPACE   Stack_Size
__initial_sp

;MSP_STACK_SIZE  EQU     0x00000400
;                AREA    STACK, NOINIT, READWRITE, ALIGN=7
;                EXPORT  Stack_Mem
;Stack_Mem       SPACE   Stack_Size
;__initial_msp
;__initial_sp    EQU     __initial_msp - MSP_STACK_SIZE
;                EXPORT  Stack_top
;Stack_top       EQU     __initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       ;Core Interrupts
                DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     MemManage_Handler              ; MPU Fault Handler
                DCD     BusFault_Handler               ; Bus Fault Handler
                DCD     UsageFault_Handler             ; Usage Fault Handler
                DCD     SecureFault_Handler            ; Secure Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     DebugMon_Handler               ; Debug Monitor Handler
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
; ToDo:  Add here the vectors for the device specific external interrupts handler
                DCD     IRQ0_Handler             ;  IRQLVI
                DCD     IRQ1_Handler             ;  IRQWDT0
                DCD     IRQ2_Handler             ;  IRQWDT1
                DCD     IRQ3_Handler             ;  IRQINTP0
                DCD     IRQ4_Handler             ;  IRQINTP1
                DCD     IRQ5_Handler             ;  IRQINTP2
                DCD     IRQ6_Handler             ;  IRQINTP3
                DCD     IRQ7_Handler             ;  IRQINTP4
                DCD     IRQ8_Handler             ;  IRQINTP5
                DCD     IRQ9_Handler             ;  IRQINTP6
                DCD     IRQ10_Handler            ;  IRQINTP7
                DCD     IRQ11_Handler            ;  IRQST0
                DCD     IRQ12_Handler            ;  IRQSR0
                DCD     IRQ13_Handler            ;  IRQSRE0
                DCD     IRQ14_Handler            ;  IRQST1
                DCD     IRQ15_Handler            ;  IRQSR1
                DCD     IRQ16_Handler            ;  IRQSRE1
                DCD     IRQ17_Handler            ;  IRQST2
                DCD     IRQ18_Handler            ;  IRQSR2
                DCD     IRQ19_Handler            ;  IRQSRE2
                DCD     IRQ20_Handler            ;  IRQST3
                DCD     IRQ21_Handler            ;  IRQSR3
                DCD     IRQ22_Handler            ;  IRQSRE3
                DCD     IRQ23_Handler            ;  IRQIICA0
                DCD     IRQ24_Handler            ;  IRQIICA1
                DCD     IRQ25_Handler            ;  IRQSPI0
                DCD     IRQ26_Handler            ;  IRQSPI1
                DCD     IRQ27_Handler            ;  IRQTM00
                DCD     IRQ28_Handler            ;  IRQTM01
                DCD     IRQ29_Handler            ;  IRQTM02
                DCD     IRQ30_Handler            ;  IRQTM03
                DCD     IRQ31_Handler            ;  IRQTM04
                DCD     IRQ32_Handler            ;  IRQTM05
                DCD     IRQ33_Handler            ;  IRQTM06
                DCD     IRQ34_Handler            ;  IRQTM07
                DCD     IRQ35_Handler            ;  IRQTM01H
                DCD     IRQ36_Handler            ;  IRQTM03H
                DCD     IRQ37_Handler            ;  IRQTM10
                DCD     IRQ38_Handler            ;  IRQTM11
                DCD     IRQ39_Handler            ;  IRQTM12
                DCD     IRQ40_Handler            ;  IRQTM13
                DCD     IRQ41_Handler            ;  IRQTM14
                DCD     IRQ42_Handler            ;  IRQTM15
                DCD     IRQ43_Handler            ;  IRQTM16
                DCD     IRQ44_Handler            ;  IRQTM17
                DCD     IRQ45_Handler            ;  IRQTM11H
                DCD     IRQ46_Handler            ;  IRQTM13H
                DCD     IRQ47_Handler            ;  IRQADC0_ADIREQ_N
                DCD     IRQ48_Handler            ;  IRQADC1_ADIREQ_N
                DCD     IRQ49_Handler            ;  IRQADC2_ADIREQ_N
                DCD     IRQ50_Handler            ;  IRQADC0_GBADIREQ_N
                DCD     IRQ51_Handler            ;  IRQADC1_GBADIREQ_N
                DCD     IRQ52_Handler            ;  IRQADC2_GBADIREQ_N
                DCD     IRQ53_Handler            ;  IRQADC0_GCADIREQ_N
                DCD     IRQ54_Handler            ;  IRQADC1_GCADIREQ_N
                DCD     IRQ55_Handler            ;  IRQADC2_GCADIREQ_N
                DCD     IRQ56_Handler            ;  IRQRTC
                DCD     IRQ57_Handler            ;  IRQIT
                DCD     IRQ58_Handler            ;  IRQKR
                DCD     IRQ59_Handler            ;  IRQCMP0
                DCD     IRQ60_Handler            ;  IRQCMP1
                DCD     IRQ61_Handler            ;  IRQCMP2
                DCD     IRQ62_Handler            ;  IRQCMP3
                DCD     IRQ63_Handler            ;  IRQC0ERR
                DCD     IRQ64_Handler            ;  IRQC0REC
                DCD     IRQ65_Handler            ;  IRQC0WUP
                DCD     IRQ66_Handler            ;  IRQC0TRX
                DCD     IRQ67_Handler            ;  IRQLCDB
                DCD     IRQ68_Handler            ;  IRQQSPI
                DCD     IRQ69_Handler            ;  IRQQSPI_DMAREQ
                DCD     IRQ70_Handler            ;  IRQFL
                DCD     IRQ71_Handler            ;  IRQOSDC
                DCD     IRQ72_Handler            ;  IRQPGI0
                DCD     IRQ73_Handler            ;  IRQPGI1
                DCD     IRQ74_Handler            ;  IRQPGI2
                DCD     IRQ75_Handler            ;  IRQPGI3
                DCD     IRQ76_Handler            ;  IRQGPT0_ELCCMPA0
                DCD     IRQ77_Handler            ;  IRQGPT0_ELCCMPB0
                DCD     IRQ78_Handler            ;  IRQGPT0_ELCCMPC0
                DCD     IRQ79_Handler            ;  IRQGPT0_ELCCMPD0
                DCD     IRQ80_Handler            ;  IRQGPT0_ELCCMPE0
                DCD     IRQ81_Handler            ;  IRQGPT0_ELCCMPF0
                DCD     IRQ82_Handler            ;  IRQGPT0_ELCOVF0
                DCD     IRQ83_Handler            ;  IRQGPT0_ELCUDF0
                DCD     IRQ84_Handler            ;  IRQGPT0_ELCCMPA1
                DCD     IRQ85_Handler            ;  IRQGPT0_ELCCMPB1
                DCD     IRQ86_Handler            ;  IRQGPT0_ELCCMPC1
                DCD     IRQ87_Handler            ;  IRQGPT0_ELCCMPD1
                DCD     IRQ88_Handler            ;  IRQGPT0_ELCCMPE1
                DCD     IRQ89_Handler            ;  IRQGPT0_ELCCMPF1
                DCD     IRQ90_Handler            ;  IRQGPT0_ELCOVF1
                DCD     IRQ91_Handler            ;  IRQGPT0_ELCUDF1
                DCD     IRQ92_Handler            ;  IRQGPT0_ELCCMPA2
                DCD     IRQ93_Handler            ;  IRQGPT0_ELCCMPB2
                DCD     IRQ94_Handler            ;  IRQGPT0_ELCCMPC2
                DCD     IRQ95_Handler            ;  IRQGPT0_ELCCMPD2
                DCD     IRQ96_Handler            ;  IRQGPT0_ELCCMPE2
                DCD     IRQ97_Handler            ;  IRQGPT0_ELCCMPF2
                DCD     IRQ98_Handler            ;  IRQGPT0_ELCOVF2
                DCD     IRQ99_Handler            ;  IRQGPT0_ELCUDF2
                DCD     IRQ100_Handler           ;  IRQGPT0_ELCCMPA3
                DCD     IRQ101_Handler           ;  IRQGPT0_ELCCMPB3
                DCD     IRQ102_Handler           ;  IRQGPT0_ELCCMPC3
                DCD     IRQ103_Handler           ;  IRQGPT0_ELCCMPD3
                DCD     IRQ104_Handler           ;  IRQGPT0_ELCCMPE3
                DCD     IRQ105_Handler           ;  IRQGPT0_ELCCMPF3
                DCD     IRQ106_Handler           ;  IRQGPT0_ELCOVF3
                DCD     IRQ107_Handler           ;  IRQGPT0_ELCUDF3
                DCD     IRQ108_Handler           ;  IRQGPT1_ELCCMPA0
                DCD     IRQ109_Handler           ;  IRQGPT1_ELCCMPB0
                DCD     IRQ110_Handler           ;  IRQGPT1_ELCCMPC0
                DCD     IRQ111_Handler           ;  IRQGPT1_ELCCMPD0
                DCD     IRQ112_Handler           ;  IRQGPT1_ELCCMPE0
                DCD     IRQ113_Handler           ;  IRQGPT1_ELCCMPF0
                DCD     IRQ114_Handler           ;  IRQGPT1_ELCOVF0
                DCD     IRQ115_Handler           ;  IRQGPT1_ELCUDF0
                DCD     IRQ116_Handler           ;  IRQGPT1_ELCCMPA1
                DCD     IRQ117_Handler           ;  IRQGPT1_ELCCMPB1
                DCD     IRQ118_Handler           ;  IRQGPT1_ELCCMPC1
                DCD     IRQ119_Handler           ;  IRQGPT1_ELCCMPD1
                DCD     IRQ120_Handler           ;  IRQGPT1_ELCCMPE1
                DCD     IRQ121_Handler           ;  IRQGPT1_ELCCMPF1
                DCD     IRQ122_Handler           ;  IRQGPT1_ELCOVF1
                DCD     IRQ123_Handler           ;  IRQGPT1_ELCUDF1
                DCD     IRQ124_Handler           ;  IRQGPT1_ELCCMPA2
                DCD     IRQ125_Handler           ;  IRQGPT1_ELCCMPB2
                DCD     IRQ126_Handler           ;  IRQGPT1_ELCCMPC2
                DCD     IRQ127_Handler           ;  IRQGPT1_ELCCMPD2
                DCD     IRQ128_Handler           ;  IRQGPT1_ELCCMPE2
                DCD     IRQ129_Handler           ;  IRQGPT1_ELCCMPF2
                DCD     IRQ130_Handler           ;  IRQGPT1_ELCOVF2
                DCD     IRQ131_Handler           ;  IRQGPT1_ELCUDF2
                DCD     IRQ132_Handler           ;  IRQGPT1_ELCCMPA3
                DCD     IRQ133_Handler           ;  IRQGPT1_ELCCMPB3
                DCD     IRQ134_Handler           ;  IRQGPT1_ELCCMPC3
                DCD     IRQ135_Handler           ;  IRQGPT1_ELCCMPD3
                DCD     IRQ136_Handler           ;  IRQGPT1_ELCCMPE3
                DCD     IRQ137_Handler           ;  IRQGPT1_ELCCMPF3
                DCD     IRQ138_Handler           ;  IRQGPT1_ELCOVF3
                DCD     IRQ139_Handler           ;  IRQGPT1_ELCUDF3
                DCD     IRQ140_Handler           ;  IRQGPT1_ELCCMPA4
                DCD     IRQ141_Handler           ;  IRQGPT1_ELCCMPB4
                DCD     IRQ142_Handler           ;  IRQGPT1_ELCCMPC4
                DCD     IRQ143_Handler           ;  IRQGPT1_ELCCMPD4
                DCD     IRQ144_Handler           ;  IRQGPT1_ELCCMPE4
                DCD     IRQ145_Handler           ;  IRQGPT1_ELCCMPF4
                DCD     IRQ146_Handler           ;  IRQGPT1_ELCOVF4
                DCD     IRQ147_Handler           ;  IRQGPT1_ELCUDF4
                DCD     IRQ148_Handler           ;  IRQGPT1_ELCCMPA5
                DCD     IRQ149_Handler           ;  IRQGPT1_ELCCMPB5
                DCD     IRQ150_Handler           ;  IRQGPT1_ELCCMPC5
                DCD     IRQ151_Handler           ;  IRQGPT1_ELCCMPD5
                DCD     IRQ152_Handler           ;  IRQGPT1_ELCCMPE5
                DCD     IRQ153_Handler           ;  IRQGPT1_ELCCMPF5
                DCD     IRQ154_Handler           ;  IRQGPT1_ELCOVF5
                DCD     IRQ155_Handler           ;  IRQGPT1_ELCUDF5
                DCD     IRQ156_Handler           ;  IRQGPT1_ELCCMPA6
                DCD     IRQ157_Handler           ;  IRQGPT1_ELCCMPB6
                DCD     IRQ158_Handler           ;  IRQGPT1_ELCCMPC6
                DCD     IRQ159_Handler           ;  IRQGPT1_ELCCMPD6
                DCD     IRQ160_Handler           ;  IRQGPT1_ELCCMPE6
                DCD     IRQ161_Handler           ;  IRQGPT1_ELCCMPF6
                DCD     IRQ162_Handler           ;  IRQGPT1_ELCOVF6
                DCD     IRQ163_Handler           ;  IRQGPT1_ELCUDF6
                DCD     IRQ164_Handler           ;  IRQGPT1_ELCCMPA7
                DCD     IRQ165_Handler           ;  IRQGPT1_ELCCMPB7
                DCD     IRQ166_Handler           ;  IRQGPT1_ELCCMPC7
                DCD     IRQ167_Handler           ;  IRQGPT1_ELCCMPD7
                DCD     IRQ168_Handler           ;  IRQGPT1_ELCCMPE7
                DCD     IRQ169_Handler           ;  IRQGPT1_ELCCMPF7
                DCD     IRQ170_Handler           ;  IRQGPT1_ELCOVF7
                DCD     IRQ171_Handler           ;  IRQGPT1_ELCUDF7
                DCD     IRQ172_Handler           ;  IRQGPT1_ELCEDGUVW
                DCD     IRQ173_Handler           ;  IRQAES_WRREQ
                DCD     IRQ174_Handler           ;  IRQAES_RDREQ
                DCD     IRQ175_Handler           ;  IRQRNG_RDREQ
                DCD     IRQ176_Handler           ;  IRQDMA0
                DCD     IRQ177_Handler           ;  IRQDMA1
                DCD     IRQ178_Handler           ;  IRQDMA2
                DCD     IRQ179_Handler           ;  IRQDMA3
                DCD     IRQ180_Handler           ;  IRQDMA4
                DCD     IRQ181_Handler           ;  IRQDMA5
                DCD     IRQ182_Handler           ;  IRQDMA6
                DCD     IRQ183_Handler           ;  IRQDMA7
                DCD     IRQ184_Handler           ;  IRQDMA8
                DCD     IRQ185_Handler           ;  IRQDMA9
                DCD     IRQ186_Handler           ;  IRQDMA10
                DCD     IRQ187_Handler           ;  IRQDMA11
                DCD     IRQ188_Handler           ;  IRQDMA12
                DCD     IRQ189_Handler           ;  IRQDMA13
                DCD     IRQ190_Handler           ;  IRQDMA14
                DCD     IRQ191_Handler           ;  IRQDMA15
                DCD     IRQ192_Handler           ;  IRQOCRV
                DCD     IRQ193_Handler           ;  IRQRAMPARITY
                DCD     IRQ194_Handler           ;  IRQC1ERR
                DCD     IRQ195_Handler           ;  IRQC1REC
                DCD     IRQ196_Handler           ;  IRQC1WUP
                DCD     IRQ197_Handler           ;  IRQC1TRX
                DCD     IRQ198_Handler           ;  IRQIIR0WFIFOEMP
                DCD     IRQ199_Handler           ;  IRQIIR0WFIFOFUL
                DCD     IRQ200_Handler           ;  IRQIIR1WFIFOEMP
                DCD     IRQ201_Handler           ;  IRQIIR1WFIFOFUL__Vectors_End
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors


; Reset Handler
                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                ;CPSID   i              ; Disable IRQs
                LDR     R0, =SystemInit
                BLX     R0
                ;MRS     R0, control    ; Get control value
                ;ORR     R0, R0, #2     ; Select switch to PSP, which will be set by __user_initial_stackheap
                ;MSR     control, R0
                LDR     R0, =__main
                BX      R0
                ENDP
End_Of_Main
                B       .


; Dummy Exception Handlers (infinite loops which can be modified)
                MACRO
                Default_Handler $handler_name
$handler_name   PROC
                EXPORT  $handler_name             [WEAK]
                B       .
                ENDP
                MEND

                Default_Handler NMI_Handler
                Default_Handler HardFault_Handler
                Default_Handler MemManage_Handler
                Default_Handler BusFault_Handler
                Default_Handler UsageFault_Handler
                Default_Handler SecureFault_Handler
                Default_Handler SVC_Handler
                Default_Handler DebugMon_Handler
                Default_Handler PendSV_Handler
                Default_Handler SysTick_Handler

                Default_Handler IRQ0_Handler
                Default_Handler IRQ1_Handler
                Default_Handler IRQ2_Handler
                Default_Handler IRQ3_Handler
                Default_Handler IRQ4_Handler
                Default_Handler IRQ5_Handler
                Default_Handler IRQ6_Handler
                Default_Handler IRQ7_Handler
                Default_Handler IRQ8_Handler
                Default_Handler IRQ9_Handler
                Default_Handler IRQ10_Handler
                Default_Handler IRQ11_Handler
                Default_Handler IRQ12_Handler
                Default_Handler IRQ13_Handler
                Default_Handler IRQ14_Handler
                Default_Handler IRQ15_Handler
                Default_Handler IRQ16_Handler
                Default_Handler IRQ17_Handler
                Default_Handler IRQ18_Handler
                Default_Handler IRQ19_Handler
                Default_Handler IRQ20_Handler
                Default_Handler IRQ21_Handler
                Default_Handler IRQ22_Handler
                Default_Handler IRQ23_Handler
                Default_Handler IRQ24_Handler
                Default_Handler IRQ25_Handler
                Default_Handler IRQ26_Handler
                Default_Handler IRQ27_Handler
                Default_Handler IRQ28_Handler
                Default_Handler IRQ29_Handler
                Default_Handler IRQ30_Handler
                Default_Handler IRQ31_Handler
                Default_Handler IRQ32_Handler
                Default_Handler IRQ33_Handler
                Default_Handler IRQ34_Handler
                Default_Handler IRQ35_Handler
                Default_Handler IRQ36_Handler
                Default_Handler IRQ37_Handler
                Default_Handler IRQ38_Handler
                Default_Handler IRQ39_Handler
                Default_Handler IRQ40_Handler
                Default_Handler IRQ41_Handler
                Default_Handler IRQ42_Handler
                Default_Handler IRQ43_Handler
                Default_Handler IRQ44_Handler
                Default_Handler IRQ45_Handler
                Default_Handler IRQ46_Handler
                Default_Handler IRQ47_Handler
                Default_Handler IRQ48_Handler
                Default_Handler IRQ49_Handler
                Default_Handler IRQ50_Handler
                Default_Handler IRQ51_Handler
                Default_Handler IRQ52_Handler
                Default_Handler IRQ53_Handler
                Default_Handler IRQ54_Handler
                Default_Handler IRQ55_Handler
                Default_Handler IRQ56_Handler
                Default_Handler IRQ57_Handler
                Default_Handler IRQ58_Handler
                Default_Handler IRQ59_Handler
                Default_Handler IRQ60_Handler
                Default_Handler IRQ61_Handler
                Default_Handler IRQ62_Handler
                Default_Handler IRQ63_Handler
                Default_Handler IRQ64_Handler
                Default_Handler IRQ65_Handler
                Default_Handler IRQ66_Handler
                Default_Handler IRQ67_Handler
                Default_Handler IRQ68_Handler
                Default_Handler IRQ69_Handler
                Default_Handler IRQ70_Handler
                Default_Handler IRQ71_Handler
                Default_Handler IRQ72_Handler
                Default_Handler IRQ73_Handler
                Default_Handler IRQ74_Handler
                Default_Handler IRQ75_Handler
                Default_Handler IRQ76_Handler
                Default_Handler IRQ77_Handler
                Default_Handler IRQ78_Handler
                Default_Handler IRQ79_Handler
                Default_Handler IRQ80_Handler
                Default_Handler IRQ81_Handler
                Default_Handler IRQ82_Handler
                Default_Handler IRQ83_Handler
                Default_Handler IRQ84_Handler
                Default_Handler IRQ85_Handler
                Default_Handler IRQ86_Handler
                Default_Handler IRQ87_Handler
                Default_Handler IRQ88_Handler
                Default_Handler IRQ89_Handler
                Default_Handler IRQ90_Handler
                Default_Handler IRQ91_Handler
                Default_Handler IRQ92_Handler
                Default_Handler IRQ93_Handler
                Default_Handler IRQ94_Handler
                Default_Handler IRQ95_Handler
                Default_Handler IRQ96_Handler
                Default_Handler IRQ97_Handler
                Default_Handler IRQ98_Handler
                Default_Handler IRQ99_Handler
                Default_Handler IRQ100_Handler
                Default_Handler IRQ101_Handler
                Default_Handler IRQ102_Handler
                Default_Handler IRQ103_Handler
                Default_Handler IRQ104_Handler
                Default_Handler IRQ105_Handler
                Default_Handler IRQ106_Handler
                Default_Handler IRQ107_Handler
                Default_Handler IRQ108_Handler
                Default_Handler IRQ109_Handler
                Default_Handler IRQ110_Handler
                Default_Handler IRQ111_Handler
                Default_Handler IRQ112_Handler
                Default_Handler IRQ113_Handler
                Default_Handler IRQ114_Handler
                Default_Handler IRQ115_Handler
                Default_Handler IRQ116_Handler
                Default_Handler IRQ117_Handler
                Default_Handler IRQ118_Handler
                Default_Handler IRQ119_Handler
                Default_Handler IRQ120_Handler
                Default_Handler IRQ121_Handler
                Default_Handler IRQ122_Handler
                Default_Handler IRQ123_Handler
                Default_Handler IRQ124_Handler
                Default_Handler IRQ125_Handler
                Default_Handler IRQ126_Handler
                Default_Handler IRQ127_Handler
                Default_Handler IRQ128_Handler
                Default_Handler IRQ129_Handler
                Default_Handler IRQ130_Handler
                Default_Handler IRQ131_Handler
                Default_Handler IRQ132_Handler
                Default_Handler IRQ133_Handler
                Default_Handler IRQ134_Handler
                Default_Handler IRQ135_Handler
                Default_Handler IRQ136_Handler
                Default_Handler IRQ137_Handler
                Default_Handler IRQ138_Handler
                Default_Handler IRQ139_Handler
                Default_Handler IRQ140_Handler
                Default_Handler IRQ141_Handler
                Default_Handler IRQ142_Handler
                Default_Handler IRQ143_Handler
                Default_Handler IRQ144_Handler
                Default_Handler IRQ145_Handler
                Default_Handler IRQ146_Handler
                Default_Handler IRQ147_Handler
                Default_Handler IRQ148_Handler
                Default_Handler IRQ149_Handler
                Default_Handler IRQ150_Handler
                Default_Handler IRQ151_Handler
                Default_Handler IRQ152_Handler
                Default_Handler IRQ153_Handler
                Default_Handler IRQ154_Handler
                Default_Handler IRQ155_Handler
                Default_Handler IRQ156_Handler
                Default_Handler IRQ157_Handler
                Default_Handler IRQ158_Handler
                Default_Handler IRQ159_Handler
                Default_Handler IRQ160_Handler
                Default_Handler IRQ161_Handler
                Default_Handler IRQ162_Handler
                Default_Handler IRQ163_Handler
                Default_Handler IRQ164_Handler
                Default_Handler IRQ165_Handler
                Default_Handler IRQ166_Handler
                Default_Handler IRQ167_Handler
                Default_Handler IRQ168_Handler
                Default_Handler IRQ169_Handler
                Default_Handler IRQ170_Handler
                Default_Handler IRQ171_Handler
                Default_Handler IRQ172_Handler
                Default_Handler IRQ173_Handler
                Default_Handler IRQ174_Handler
                Default_Handler IRQ175_Handler
                Default_Handler IRQ176_Handler
                Default_Handler IRQ177_Handler
                Default_Handler IRQ178_Handler
                Default_Handler IRQ179_Handler
                Default_Handler IRQ180_Handler
                Default_Handler IRQ181_Handler
                Default_Handler IRQ182_Handler
                Default_Handler IRQ183_Handler
                Default_Handler IRQ184_Handler
                Default_Handler IRQ185_Handler
                Default_Handler IRQ186_Handler
                Default_Handler IRQ187_Handler
                Default_Handler IRQ188_Handler
                Default_Handler IRQ189_Handler
                Default_Handler IRQ190_Handler
                Default_Handler IRQ191_Handler
                Default_Handler IRQ192_Handler
                Default_Handler IRQ193_Handler
                Default_Handler IRQ194_Handler
                Default_Handler IRQ195_Handler
                Default_Handler IRQ196_Handler
                Default_Handler IRQ197_Handler
                Default_Handler IRQ198_Handler
                Default_Handler IRQ199_Handler
                Default_Handler IRQ200_Handler
                Default_Handler IRQ201_Handler

                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem  +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
