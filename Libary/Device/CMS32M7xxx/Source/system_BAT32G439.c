/**************************************************************************//**
 * @file     system_BAT32G439.c
 * @brief    CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
 *           Device BAT32G439
 * @version  V1.00
 * @date     2022/09/24
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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
 */

#include <stdint.h>
#include "BAT32G439.h"


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies             */
#define __HSI             (64000000UL)
#define __XTAL            (8000000UL)    /* Oscillator frequency              */
#define __SYS_OSC_CLK     (    ___HSI)    /* Main oscillator frequency        */

#define __SYSTEM_CLOCK    (64000000UL)

/** @addtogroup Configuration_of_User_Option_Byte
  * @{
  */

typedef enum {
  HOCO_FREQ_64MHZ = 0xE8, 	/*!< fHOCO = 64MHz, fIH = 64MHz  	*/
  HOCO_FREQ_48MHZ = 0xE0, 	/*!< fHOCO = 48MHz, fIH = 48MHz  	*/
  HOCO_FREQ_32MHZ = 0xE9, 	/*!< fHOCO = 64MHz, fIH = 32MHz  	*/
  HOCO_FREQ_24MHZ = 0xE1, 	/*!< fHOCO = 48MHz, fIH = 24MHz  	*/
  HOCO_FREQ_16MHZ = 0xEA, 	/*!< fHOCO = 64MHz, fIH = 16MHz  	*/
  HOCO_FREQ_12MHZ = 0xE2, 	/*!< fHOCO = 48MHz, fIH = 12MHz  	*/
  HOCO_FREQ_8MHZ  = 0xEB, 	/*!< fHOCO = 64MHz, fIH =  8MHz  	*/
  HOCO_FREQ_6MHZ  = 0xE3, 	/*!< fHOCO = 48MHz, fIH =  6MHz  	*/
  HOCO_FREQ_4MHZ  = 0xEC, 	/*!< fHOCO = 64MHz, fIH =  4MHz  	*/
  HOCO_FREQ_3MHZ  = 0xE4, 	/*!< fHOCO = 48MHz, fIH =  3MHz  	*/
  HOCO_FREQ_2MHZ  = 0xED, 	/*!< fHOCO = 64MHz, fIH =  2MHz  	*/
  } hoco_freq_t;

/*----------------------------------------------------------------------------
  User Option Byte 
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies */

//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
static const uint8_t user_opt_data[8] __attribute__((used)) __attribute__((section(".ARM.__AT_0x00000400"))) =
{

/**
 * @brief WDT Control BYTE
 * Please refer to the user manual for details.
 *     7   |    6    |    5    |   4   |   3   |   2   |   1   |   0
 * --------|---------|---------|-------|-------|-------|-------|----------
 *  WDTINT | WINDOW1 | WINDOW0 | WDTON | WDCS2 | WDCS1 | WDCS0 | WDSTBYON
 * --------|---------|---------|-------|-------|-------|-------|----------
 */
// <h> WDT Control Option Byte (400H)
//   <e.4> Enable WDT (WDTON)
//     <o.5..6> Watchdog timer window open period setting      <2=> 75%        <3=> 100%
//     <o.1..3> Watchdog timer overflow time setting           <0=> 2^6/fIL    <1=> 2^7/fIL
//                                                             <2=> 2^8/fIL    <3=> 2^9/fIL
//                                                             <4=> 2^11/fIL   <5=> 2^13/fIL
//                                                             <6=> 2^14/fIL   <7=> 2^16/fIL
//     <e.0>    Operation in Standby mode setting (WDSTBYON)
//              <i> WDT Operaton in SLEEP/DEEPSLEEP mode.
//     </e>
//     <e.7>    interrupt enable
//              <i> interval interrupt is generated when 75% + 1/2 fIL of the overflow time is reached.
//     </e>
//   </e>
// </h>
    //0xEF,
    0x7B,
/**
 * @brief LVD Control BYTE (401H)
 * Please refer to the user manual for details.
 *    7   |   6   |   5   |   4   |   3   |   2   |    1    |    0     
 * -------|-------|-------|-------|-------|-------|---------|----------
 *  VPOC2 | VPOC1 | VPOC0 |   1   | LVIS1 | LVIS0 | LVIMDS1 | LVIMDS0
 * -------|-------|-------|-------|-------|-------|---------|----------
 */
// <h> LVD Control Option Byte (401H)
//     <o.0..7> Voltage detection setting (VLVD)              <0xFF=> ( LVD OFF )
//                                                            <0x3D=> VLVD = 1.88V/1.84V    ( interrupt mode )         
//                                                            <0x39=> VLVD = 1.98V/1.94V    ( interrupt mode )         
//                                                            <0x35=> VLVD = 2.09V/2.04V    ( interrupt mode )         
//                                                            <0x5D=> VLVD = 2.50V/2.45V    ( interrupt mode )         
//                                                            <0x59=> VLVD = 2.61V/2.55V    ( interrupt mode )         
//                                                            <0x55=> VLVD = 2.71V/2.65V    ( interrupt mode )         
//                                                            <0x7D=> VLVD = 2.81V/2.75V    ( interrupt mode )         
//                                                            <0x79=> VLVD = 2.92V/2.86V    ( interrupt mode )         
//                                                            <0x75=> VLVD = 3.02V/2.96V    ( interrupt mode )         
//                                                            <0x3F=> VLVD = 1.88V/1.84V    ( reset mode )             
//                                                            <0x3B=> VLVD = 1.98V/1.94V    ( reset mode )             
//                                                            <0x37=> VLVD = 2.09V/2.04V    ( reset mode )             
//                                                            <0x5F=> VLVD = 2.50V/2.45V    ( reset mode )             
//                                                            <0x5B=> VLVD = 2.61V/2.55V    ( reset mode )             
//                                                            <0x57=> VLVD = 2.71V/2.65V    ( reset mode )             
//                                                            <0x7F=> VLVD = 2.81V/2.75V    ( reset mode )             
//                                                            <0x7B=> VLVD = 2.92V/2.86V    ( reset mode )             
//                                                            <0x77=> VLVD = 3.02V/2.96V    ( reset mode )             
//                                                            <0x3A=> VLVDH = 1.98V/1.94V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x36=> VLVDH = 2.09V/2.04V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x32=> VLVDH = 3.13V/3.06V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x5A=> VLVDH = 2.61V/2.55V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x56=> VLVDH = 2.71V/2.65V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x52=> VLVDH = 3.75V/3.67V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x7A=> VLVDH = 2.92V/2.86V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//                                                            <0x76=> VLVDH = 3.02V/2.96V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//                                                            <0x72=> VLVDH = 4.06V/3.98V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//              <i> Please setting the item for interrupt & reset mode
// </h>
    0x3F,

/**
 * @brief HOCO Control BYTE (FRQSEL)
 * Please refer to the user manual for details.
 *    7   |   6   |   5   |    4    |    3    |    2    |    1    |    0    
 * -------|-------|-------|---------|---------|---------|---------|---------
 *    1   |   1   |   1   | FRQSEL4 | FRQSEL3 | FRQSEL2 | FRQSEL1 | FRQSEL0 
 * -------|-------|-------|---------|---------|---------|---------|---------
 */
// <h> HOCO Control Option Byte (402H)
//   <o.0..4> High-speed OCO clock setting                  <0xE8=> fHOCO = 64MHz, fIH = 64MHz
//                                                          <0xE0=> fHOCO = 48MHz, fIH = 48MHz
//                                                          <0xE9=> fHOCO = 64MHz, fIH = 32MHz
//                                                          <0xE1=> fHOCO = 48MHz, fIH = 24MHz
//                                                          <0xEA=> fHOCO = 64MHz, fIH = 16MHz
//                                                          <0xE2=> fHOCO = 48MHz, fIH = 12MHz
//                                                          <0xEB=> fHOCO = 64MHz, fIH =  8MHz
//                                                          <0xE3=> fHOCO = 48MHz, fIH =  6MHz
//                                                          <0xEC=> fHOCO = 64MHz, fIH =  4MHz
//                                                          <0xE4=> fHOCO = 48MHz, fIH =  3MHz
//                                                          <0xED=> fHOCO = 64MHz, fIH =  2MHz
// </h>
    //0xE8,
      0xEB,    

/**
 * @brief Flash Protect Control BYTE
 * Please refer to the user manual for details.
 */
// <h> OCD Control Option Byte (403H)
//   <o.0..7> On-chip debug setting (OCDEN)                 <0xFF=> Enable  <0xC3=> Disable
//            <i> OCDM(500004H) == 0x3C && OCDEN == 0xC3: Debugger can not erease/write/read Flash.
//            <i> OCDM(500004H) != 0x3C && OCDEN == 0xC3: Debugger can only chip erease Flash but cannot write/read Flash.
// </h>
    0xFF,


/**
 * @brief IWDT Control BYTE
 * Please refer to the user manual for details.
 *     7    |    6     |    5     |   4    |   3    |   2    |   1    |   0
 * ---------|----------|----------|--------|--------|--------|--------|----------
 *  IWDTINT | IWINDOW1 | IWINDOW0 | IWDTON | IWDCS2 | IWDCS1 | IWDCS0 | IWDSTBYON
 * ---------|----------|----------|--------|--------|--------|--------|----------
 */
// <h> IWDT Control Option Byte (404H)
//   <e.4> Enable IWDT (IWDTON)
//     <o.5..6> Watchdog timer window open period setting      <2=> 75%        <3=> 100%
//     <o.1..3> Watchdog timer overflow time setting           <0=> 2^6/fIL    <1=> 2^7/fIL
//                                                             <2=> 2^8/fIL    <3=> 2^9/fIL
//                                                             <4=> 2^11/fIL   <5=> 2^13/fIL
//                                                             <6=> 2^14/fIL   <7=> 2^16/fIL
//     <e.0>    Operation in Standby mode setting (IWDSTBYON)
//              <i> IWDT Operaton in SLEEP/DEEPSLEEP mode.
//     </e>
//     <e.7>    interrupt enable
//              <i> interval interrupt is generated when 75% + 1/2 fIL of the overflow time is reached.
//     </e>
//   </e>
// </h>
    0xEF,

/**
 * @brief QSPI flash protect option BYTE
 * Please refer to the user manual for details.
 */
// <h> Extern Flash Decrypt Control Byte (C5H)
//   <o.0..7> Extern flash protect control (CRYPEN)          <0x5A=> Decrypt Enalbe  <0xFF=> Decrypt Disable
// </h>
    0xFF,

/**
 * @brief QSPI flash protect option BYTE0
 * Please refer to the user manual for details.
 */
// <h> Extern Flash Encrypt Byte0 (C6H)
// </h>
    0xFF, 
	
/**
 * @brief QSPI flash protect option BYTE1
 * Please refer to the user manual for details.
 */
// <h> Extern Flash Encrypt Byte1 (C7H)
// </h>
	  0xFF

};

//-------- <<< end of configuration section >>> ------------------
/** @} */ /* End of group Configuration_of_User_Option_Byte */

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit() */
uint32_t SystemCoreClock;       /* System Clock Frequency (Core Clock)*/

uint32_t SystemAPBClock = 128000000;


static uint32_t CLK_GetfIHFreq(void);
static uint32_t CLK_GetCoreFreq(void);

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
static uint32_t CLK_GetfIHFreq(void)
{
  uint32_t freq;
  //uint8_t  frqsel   = (*(uint8_t *)& user_opt_data[2]);   // warning..
  uint8_t  frqsel   = (*(uint8_t *) 0x00000402U);
  frqsel &= 0xF8;          /* Mask the lower 3 bits */
  frqsel |= CGC->HOCODIV;  /* Refer the value of HOCODIV */
  switch(frqsel)
  {
	  case HOCO_FREQ_64MHZ:
		  freq = 64000000U;     /* fIH = 64MHz  */
		  break;
	  case HOCO_FREQ_48MHZ:
		  freq = 48000000U;     /* fIH = 48MHz  */
		  break;
	  case HOCO_FREQ_32MHZ:
		  freq = 32000000U;     /* fIH = 32MHz  */
		  break;
	  case HOCO_FREQ_24MHZ:
		  freq = 24000000U;     /* fIH = 24MHz  */
		  break;
	  case HOCO_FREQ_16MHZ:
		  freq = 16000000U;     /* fIH = 16MHz  */
		  break;
	  case HOCO_FREQ_12MHZ:
		  freq = 12000000U;     /* fIH = 12MHz  */
		  break;
	  case HOCO_FREQ_8MHZ:
		  freq = 8000000U;      /* fIH = 8MHz   */
		  break;
	  case HOCO_FREQ_6MHZ:
		  freq = 6000000U;      /* fIH = 6MHz   */
		  break;
	  case HOCO_FREQ_4MHZ:
		  freq = 4000000U;      /* fIH = 4MHz   */
		  break;
	  case HOCO_FREQ_3MHZ:
		  freq = 3000000U;      /* fIH = 3MHz   */
		  break;
	  case HOCO_FREQ_2MHZ:
		  freq = 2000000U;      /* fIH = 2MHz   */
		  break;
	  default:
		  freq = 2000000U;      /* fIH = 2MHz   */
		  break;
  }

  return(freq);
}

static uint32_t CLK_GetCoreFreq(void)
{
  uint32_t freq;
  uint8_t  pllsel = 0;

  if(CGC->CKC&0x20){			// Main Osc
	freq = __XTAL;      					/* Get XTAL frequency   */
  }
  else{							// fIH
	freq = CLK_GetfIHFreq();      		/* Get fIH frequency   */

	if(CGC->MCKC&0x80){			/* CGC->MCKC&0x80 = 0x80: PLL On */
	  if (CGC->PLLCR&0x80){ 	// XTAL + PLL
		  freq = __XTAL;      					/* Get XTAL frequency   */
	  }
	  else{						// fIH + PLL
		  freq = CLK_GetfIHFreq();      		/* Get fIH frequency   */
	  }

	  pllsel = (CGC->PLLCR >> 2)&0x03;			// PLL div in PLLCR
	  if(pllsel>=2){		// PLL Div=4
		  freq = freq/4;
	  }
	  else if(pllsel==1){	// PLL Div=2
		  freq = freq/2;
	  }
	  else{					// PLL Div=1
		  freq = freq/1;
	  }

	  if((CGC->PLLCR >> 1)&0x01){				// PLL Mul in PLLCR
		  freq = freq*16;	// PLL Mul=16
	  }
	  else{
		  freq = freq*12;	// PLL Mul=12
	  }
	  pllsel = (CGC->MCKC>>1)&0x03;				// PLL div in MCKC
	  if (pllsel==0){
		  pllsel = pllsel + 1; // 00b: Div=1
	  }
	  else if(pllsel==3){
		  pllsel = (pllsel+1) * 2; // 11b: (Div+1)*2=8
	  }
	  else{
		  pllsel = pllsel * 2; // 01~10b: (Div*2)=2or4
	  }
	  freq = freq/pllsel;
	}
	//else{						/* CGC->MCKC&0x80 = 0: PLL Off */
		//freq = CLK_GetfIHFreq();      		/* Get fIH frequency   */
	//}
  }

  return(freq);
}

void SystemCoreClockUpdate (void)  /* Get Core Clock Frequency */
{
/* ToDo: add code to calculate the system frequency based upon the current
         register settings.
         This function can be used to retrieve the system core clock frequeny
         after user changed register sittings. */
  SystemCoreClock = CLK_GetCoreFreq();
}

void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards. */

  uint32_t i;
  /* RAM Parity Error Reset Disable */
  SAF->RPECTL = 0x80U;
    
  CGC->PLLCR |= 0x03;
  CGC->MCKC |= 0x01; 
    
  CGC->IWDTCTL = 0x0100;
  CGC->WDTCFG = 0x1A2B3C4D;
  DBG->DBGSTOPCR = 0;
  for(i=0; i<1000000; i++){ }  			// delay 60ms

// #if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
//   SCB->VTOR = (uint32_t) &__VECTOR_TABLE;
// #endif

 #if defined (__FPU_USED) && (__FPU_USED == 1U)
   SCB->CPACR |= ((3U << 10U*2U) |           /* enable CP10 Full Access */
                  (3U << 11U*2U)  );         /* enable CP11 Full Access */
 #endif

// #ifdef UNALIGNED_SUPPORT_DISABLE
//   SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
// #endif

// #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
//   TZ_SAU_Setup();
// #endif

//   SystemCoreClock = SYSTEM_CLOCK;

// #if defined __EN_ICACHE
//   if (SCB->CLIDR & SCB_CLIDR_IC_Msk)
//     SCB_EnableICache();
//   //else
//   	//_sys_exit("no ICache included");/*implement your __exit code to pass the error message to the user.*/
// #endif
// #if defined __EN_DCACHE
//   if (SCB->CLIDR & SCB_CLIDR_IC_Msk)
//     SCB_EnableDCache();
//   //else
//   	//_sys_exit("no DCache included");
// #endif 

#if 0
 //#if defined __EN_ICACHE
   if (SCB->CLIDR & SCB_CLIDR_IC_Msk)
     SCB_EnableICache();
   //else
   	//_sys_exit("no ICache included");/*implement your __exit code to pass the error message to the user.*/
 //#endif
// #if defined __EN_DCACHE
   if (SCB->CLIDR & SCB_CLIDR_IC_Msk)
     SCB_EnableDCache();
   //else
   	//_sys_exit("no DCache included");
// #endif 

#endif

}
