/***********************************************************************************************************************
* @file    isr.c
* @brief   This file implements interrupt server routine.
* @version 1.0.0
* @author	 Chenzongfu
* @date    2023/1/30
***********************************************************************************************************************/
/*
 * Copyright (c) 2023 Cmsemicon Limited. All rights reserved.
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
 
#include "isr.h"

ATE_FRAME_t pData = {0};
ISR_InitTypeDef_t IRQ_Fun;

/**
  * @brief  IRQ_Handler
  * @param  None
  * @retval None
  */

#define IRQ_Handler(number) void IRQ##number##_Handler(void) \
{\
	IRQ_Fun.IRQ[number].intHandle(&pData);	\
}\


IRQ_Handler(0)
IRQ_Handler(1)
IRQ_Handler(2)
IRQ_Handler(3)
IRQ_Handler(4)
IRQ_Handler(5)
IRQ_Handler(6)
IRQ_Handler(7)
IRQ_Handler(8)
IRQ_Handler(9)
IRQ_Handler(10)
IRQ_Handler(11)
IRQ_Handler(12)
IRQ_Handler(13)
IRQ_Handler(14)
IRQ_Handler(15)
IRQ_Handler(16)
IRQ_Handler(17)
IRQ_Handler(18)
IRQ_Handler(19)
IRQ_Handler(20)
IRQ_Handler(21)
IRQ_Handler(22)
IRQ_Handler(23)
IRQ_Handler(24)
IRQ_Handler(25)
IRQ_Handler(26)
IRQ_Handler(27)
IRQ_Handler(28)
IRQ_Handler(29)
IRQ_Handler(30)
IRQ_Handler(31)
IRQ_Handler(32)
IRQ_Handler(33)
IRQ_Handler(34)
IRQ_Handler(35)
IRQ_Handler(36)
IRQ_Handler(37)
IRQ_Handler(38)
IRQ_Handler(39)
IRQ_Handler(40)
IRQ_Handler(41)
IRQ_Handler(42)
IRQ_Handler(43)
IRQ_Handler(44)
IRQ_Handler(45)
IRQ_Handler(46)
IRQ_Handler(47)
IRQ_Handler(48)
IRQ_Handler(49)
IRQ_Handler(50)
IRQ_Handler(51)
IRQ_Handler(52)
IRQ_Handler(53)
IRQ_Handler(54)
IRQ_Handler(55)
IRQ_Handler(56)
IRQ_Handler(57)
IRQ_Handler(58)
IRQ_Handler(59)
IRQ_Handler(60)
IRQ_Handler(61)
IRQ_Handler(62)
IRQ_Handler(63)
IRQ_Handler(64)
IRQ_Handler(65)
IRQ_Handler(66)
IRQ_Handler(67)
IRQ_Handler(68)
IRQ_Handler(69)
IRQ_Handler(70)
IRQ_Handler(71)
IRQ_Handler(72)
IRQ_Handler(73)
IRQ_Handler(74)
IRQ_Handler(75)
IRQ_Handler(76)
IRQ_Handler(77)
IRQ_Handler(78)
IRQ_Handler(79)
IRQ_Handler(80)
IRQ_Handler(81)
IRQ_Handler(82)
IRQ_Handler(83)
IRQ_Handler(84)
IRQ_Handler(85)
IRQ_Handler(86)
IRQ_Handler(87)
IRQ_Handler(88)
IRQ_Handler(89)
IRQ_Handler(90)
IRQ_Handler(91)
IRQ_Handler(92)
IRQ_Handler(93)
IRQ_Handler(94)
IRQ_Handler(95)
IRQ_Handler(96)
IRQ_Handler(97)
IRQ_Handler(98)
IRQ_Handler(99)
IRQ_Handler(100)
IRQ_Handler(101)
IRQ_Handler(102)
IRQ_Handler(103)
IRQ_Handler(104)
IRQ_Handler(105)
IRQ_Handler(106)
IRQ_Handler(107)
IRQ_Handler(108)
IRQ_Handler(109)
IRQ_Handler(110)
IRQ_Handler(111)
IRQ_Handler(112)
IRQ_Handler(113)
IRQ_Handler(114)
IRQ_Handler(115)
IRQ_Handler(116)
IRQ_Handler(117)
IRQ_Handler(118)
IRQ_Handler(119)
IRQ_Handler(120)
IRQ_Handler(121)
IRQ_Handler(122)
IRQ_Handler(123)
IRQ_Handler(124)
IRQ_Handler(125)
IRQ_Handler(126)
IRQ_Handler(127)
IRQ_Handler(128)
IRQ_Handler(129)
IRQ_Handler(130)
IRQ_Handler(131)
IRQ_Handler(132)
IRQ_Handler(133)
IRQ_Handler(134)
IRQ_Handler(135)
IRQ_Handler(136)
IRQ_Handler(137)
IRQ_Handler(138)
IRQ_Handler(139)
IRQ_Handler(140)
IRQ_Handler(141)
IRQ_Handler(142)
IRQ_Handler(143)
IRQ_Handler(144)
IRQ_Handler(145)
IRQ_Handler(146)
IRQ_Handler(147)
IRQ_Handler(148)
IRQ_Handler(149)
IRQ_Handler(150)
IRQ_Handler(151)
IRQ_Handler(152)
IRQ_Handler(153)
IRQ_Handler(154)
IRQ_Handler(155)
IRQ_Handler(156)
IRQ_Handler(157)
IRQ_Handler(158)
IRQ_Handler(159)
IRQ_Handler(160)
IRQ_Handler(161)
IRQ_Handler(162)
IRQ_Handler(163)
IRQ_Handler(164)
IRQ_Handler(165)
IRQ_Handler(166)
IRQ_Handler(167)
IRQ_Handler(168)
IRQ_Handler(169)
IRQ_Handler(170)
IRQ_Handler(171)
IRQ_Handler(172)
IRQ_Handler(173)
IRQ_Handler(174)
IRQ_Handler(175)
IRQ_Handler(176)
IRQ_Handler(177)
IRQ_Handler(178)
IRQ_Handler(179)
IRQ_Handler(180)
IRQ_Handler(181)
IRQ_Handler(182)
IRQ_Handler(183)
IRQ_Handler(184)
IRQ_Handler(185)
IRQ_Handler(186)
IRQ_Handler(187)
IRQ_Handler(188)
IRQ_Handler(189)
IRQ_Handler(190)
IRQ_Handler(191)
IRQ_Handler(192)
IRQ_Handler(193)
IRQ_Handler(194)
IRQ_Handler(195)
IRQ_Handler(196)
IRQ_Handler(197)
IRQ_Handler(198)
IRQ_Handler(199)
IRQ_Handler(200)
IRQ_Handler(201)


/**
  * @brief  register interrupt function according to  IRQn num.
  * @param  irq_num: it relates to irq handler 
  * @param	interrupt:interrupt server function
  * @retval regiseter status 
  */
int ISR_Register(IRQn_Type irq_num, void *interrupt)
{
	int res = ISR_SUCC;
	
	if(irq_num > IIR1WFIFOFUL_IRQn) return ISR_ERR;
	
	if(IRQ_Fun.IRQ[irq_num].IRQ_Flag)
	{
		return ISR_ERR;
	}
	else
	{		
		
		IRQ_Fun.IRQ[irq_num].IRQ_Flag = 1;
		IRQ_Fun.IRQ[irq_num].intHandle = (isrFun_t)interrupt;
		 
		NVIC_ClearPendingIRQ(irq_num); // clear  interrupt flag 
		NVIC_EnableIRQ(irq_num); // enable  interrupt
	}

	return res;
}
