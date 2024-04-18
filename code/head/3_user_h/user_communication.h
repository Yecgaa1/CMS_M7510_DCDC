
/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  £º
*****************************************************************************/

#ifndef  __USER_COMMUNICATION_H
#define  __USER_COMMUNICATION_H


#include "BAT32G439.h"
#include "sys_struct.h"

extern uint8_t  u8_SendDataDebug[9];

void CHG_State_Deal(void);
void Function_TxSendDebug(int32_t data1,int32_t data2,int32_t data3,int32_t data4,int32_t data5);
void User_UART_View(void);
void DC_DataSend(void);
void COM_Uartx_HeartCheck(UARTx_Var_t *uart_Info);
uint16_t crc16_modbus(uint8_t *data, uint16_t length, uint16_t CRC_Init);
void VBUS_Calc(void);
#endif

