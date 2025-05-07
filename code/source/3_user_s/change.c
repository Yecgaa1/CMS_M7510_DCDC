#include "change.h"
#include "stdio.h"
#include "string.h"
#include "sys_mcu_header.h"
char txCharL[40] = {0};
void Function_TxSendDebug_INT(int32_t data)
{
    // sprintf((char *)txCharL, "%d", data);
    sprintf((char *)txCharL, "%d,%d\r\n", data, data + 1);

    DMAVEC->CTRL[2].DMSAR = (uint32_t)(void *)&txCharL[1];
    DMAVEC->CTRL[2].DMACT = strlen(txCharL) - 1;
    DMA->DMAEN0 |= 1 << DMA_VECTOR_2;
    SCI2->TXD = (uint8_t)txCharL[0];
}
void Function_TxSendDebug_TWO_INT(int32_t data1, int32_t data2)
{
    // sprintf((char *)txCharL, "%d", data);
    sprintf((char *)txCharL, "%d,%d,%d\r\n", data1, data2, data1 + data2);

    DMAVEC->CTRL[2].DMSAR = (uint32_t)(void *)&txCharL[1];
    DMAVEC->CTRL[2].DMACT = strlen(txCharL) - 1;
    DMA->DMAEN0 |= 1 << DMA_VECTOR_2;
    SCI2->TXD = (uint8_t)txCharL[0];
}
