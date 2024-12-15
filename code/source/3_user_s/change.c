#include "change.h"
#include "stdio.h"
#include "string.h"
#include "sys_mcu_header.h"
char txCharL[40] = {0};
void Function_TxSendDebug_INT(int32_t data)
{
    sprintf((char *)txCharL, "%d\r\n", data);

    DMAVEC->CTRL[2].DMSAR = (uint32_t)(void *)&txCharL[1];
    DMAVEC->CTRL[2].DMACT = strlen(txCharL) - 1;
    DMA->DMAEN0 |= 1 << DMA_VECTOR_2;
    SCI2->TXD = (uint8_t)txCharL[0];
}
