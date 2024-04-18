/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ��
*****************************************************************************/

/****************************************************************************/
/*----include files---------------------------------------------------------*/
#include "user_communication.h"
#include "sys_mcu_header.h"
#include "sys_state_machine.h"
#include "sys_define_param.h"
#include "string.h"
/***************************************************************************/

uint8_t u8_SendDataDebug[9] = {0};	
/*************************************************
Description: COM_TxSendDebug
Input      : 
Return     : 
Others     : ���Դ������ݴ���
*************************************************/
uint8_t txBuf[24] = {0};
uint8_t u8txBuf1,u8txBuf2,u8txBuf3,u8txBuf4 ;
float num[5] = {0};
uint8_t u8_senddebug = 0;
void Function_TxSendDebug(int32_t data1,int32_t data2,int32_t data3,int32_t data4,int32_t data5)
{
    num[0] = data1;
    num[1] = data2;
    num[2] = data3;
    num[3] = data4; 
		num[4] = data5; 
    memcpy(txBuf,(uint8_t *)num,20);
	
    txBuf[20] = 0x00;
    txBuf[21] = 0x00;
    txBuf[22] = 0x80;
    txBuf[23] = 0x7f;
		
    DMAVEC->CTRL[2].DMSAR = (uint32_t)(void *)&txBuf[1];
    DMAVEC->CTRL[2].DMACT = 23;                                      //����8������
    DMA->DMAEN0 |= 1<<DMA_VECTOR_2;   
    SCI2->TXD = u8_SendDataDebug[0]; 		
}


/*************************************************
Description: COM_Uartx_HeartCheck
Input      : 
Return     : 
Others     : UARTx�������
*************************************************/
void COM_Uartx_HeartCheck(UARTx_Var_t *uart_Info)
{
    int Heart_Value = uart_Info->heart_Val;
    
    /*------------------------------------------------------------------------------------*/
    /*---------------------UARTx��������ͨ��״̬λ����------------------------------------*/			
    if(uart_Info->heart_Status == 1)//����λΪ1ʱ����ֵ
    {
        uart_Info->heart0_Cnt = 0;				
        if(uart_Info->heart1_Cnt <= Heart_Value)					
        {
            uart_Info->heart1_Cnt ++;
        }
    }
    else if(uart_Info->heart_Status == 0 )//����λΪ0ʱ����ֵ
    {
        uart_Info->heart1_Cnt = 0;				
        if(uart_Info->heart0_Cnt <= Heart_Value)					
        {
            uart_Info->heart0_Cnt ++;
        }
    }		
        
    /*------------------------------------------------------------------------------------*/				
    /*---------------------UARTxͨ������λ�߼��жϴ���------------------------------------*/	
    if(uart_Info->heart0_Cnt >= Heart_Value || uart_Info->heart1_Cnt >= Heart_Value)  //
    {
        uart_Info->heart_OK_Status =0; //��������ͨ���쳣ʱStatus_Heart_OK״̬Ϊ 0
    }
    else 
    {
        uart_Info->heart_OK_Status = 1;//��������ͨ������ʱStatus_Heart_OK״̬Ϊ 1
    }
}


/*************************************************
Description: crc16_modbus CRCУ�� 
Poly        : 0x8005
Init        : 0xFFFF
Refin       : True
Refout      : True
Xorout      : 0x0000
Others      : CRC-16/MODBUS       x16+x15+x2+1
*************************************************/
uint16_t crc16_modbus(uint8_t *data, uint16_t length, uint16_t CRC_Init)
{
    uint8_t i;

    while(length--)
    {
        CRC_Init ^= *data++;            // crc ^= *data; data++;
        for (i = 0; i < 8; ++i)
        {
            if (CRC_Init & 1)
                CRC_Init = (CRC_Init >> 1) ^ 0xA001;        // 0xA001 = reverse 0x8005
            else
                CRC_Init = (CRC_Init >> 1);
        }
    }
    return CRC_Init;
}


/*************************************************
Description: UART0_DC_DataSend
Input      : 
Return     : 
Others     : ��ѹ�����ݷ��ʹ���
*************************************************/  
void UART0_DC_DataSend(int32_t *tx_buf)
{
    //��������
    for(int i=0;i<((UART0_SEND_NUM>>1)-1);i++)
    {
        UART0_Info.TXD_B[i*2    ] = (uint8_t)( tx_buf[i] );  
        UART0_Info.TXD_B[i*2 + 1] = (uint8_t)( tx_buf[i] >> 8 );	 
    }

    //CRCУ�����ô���
    for(int i=0;i<(UART0_SEND_NUM-2);i++)
    {
        UART0_Info.TXD_CRC_Calc = crc16_modbus(&UART0_Info.TXD_B[i],1,UART0_Info.TXD_CRC_Init ); 
        UART0_Info.TXD_CRC_Init = UART0_Info.TXD_CRC_Calc;          	 
    }    
    UART0_Info.TXD_B[ UART0_SEND_NUM-2 ]   = (uint8_t)( UART0_Info.TXD_CRC_Calc );
    UART0_Info.TXD_B[ UART0_SEND_NUM-1 ]   = (uint8_t)( UART0_Info.TXD_CRC_Calc >> 8 );    
    UART0_Info.TXD_CRC_Init                 = 0xffff;//CRC��ʼֵ����
        
 
	//if((SCI0->SSRm0 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED)) == 0)
	{
        DMAVEC->CTRL[0].DMSAR = (uint32_t)(void *)&UART0_Info.TXD_B[1];
        DMAVEC->CTRL[0].DMACT = UART0_SEND_NUM-1;                                      //����15������
        DMA->DMAEN0 |= 1<<DMA_VECTOR_0;   //uart1_TXD                                 //ʹ�ܴ���(UART1)
		SCI0->TXD = UART0_Info.TXD_B[0];  //����UART1�����ݷ��ͼĴ��������������η������
	}
}


/*************************************************
Description: VBUS_Calc
Input      : 
Return     : 
Others     : ����PFC��ĸ�ߵ�ѹ����ֵ
*************************************************/ 
extern int32_t CHG_vBat_AD_Hold,CHG_vBat_AD_Fir;
void VBUS_Calc(void)
{
    //����PFC��ĸ�ߵ�ѹ����ֵ             
    if(CHG_Info.out_AVG_Fir >= CHG_OUT_MAX)
    {
        CHG_Info.vBUS_Ref_Sum +=195;
    }   
    else if(CHG_Info.out_AVG_Fir <= CHG_OUT_MIN)
    {      
        CHG_Info.vBUS_Ref_Sum -=195;
    } 

        
    CHG_Info.vBUS_Ref_SS =(CHG_Info.vBUS_Ref_Sum>>10)+ (CHG_vBat_AD_Fir*COM_VBAT_BASE*N2_N1_RATIO*4>>12);//��*4����ʾĸ�ߵ�ѹ�Ŵ�4��
    if(CHG_Info.vBUS_Ref_SS<=COM_CHG_VBUS_REF_INIT)//270AC * 1.414 * 4
    {
        CHG_Info.vBUS_Ref_SS = COM_CHG_VBUS_REF_INIT;
    }
    if(CHG_Info.vBUS_Ref_SS>=COM_CHG_VBUS_REF_MAX)//
    {
        CHG_Info.vBUS_Ref_SS = COM_CHG_VBUS_REF_MAX;
    }  
    
    //
    /*ĸ�ߵ�ѹ�����ο�����COM_CHG_VBUS_REF_INITʱ����ֹCHG_Info.vBUS_Ref_Sumһֱ�ۼӵ��ܴ�ĸ�ֵ��
    ����·���ڲ�������������·����ﵽ���ֵ
    */
    if(CHG_Info.vBUS_Ref_Sum<0 && CHG_Info.vBUS_Ref_SS <= COM_CHG_VBUS_REF_INIT)   
    {
        CHG_Info.vBUS_Ref_Sum = (CHG_Info.vBUS_Ref_SS-(CHG_vBat_AD_Fir*COM_VBAT_BASE*N2_N1_RATIO*4>>12))<<10;//��*4����ʾĸ�ߵ�ѹ�Ŵ�4��
    }
    //
    /*ĸ�ߵ�ѹ�����ο�����COM_CHG_VBUS_REF_MAXʱ����ֹCHG_Info.vBUS_Ref_Sumһֱ�ۼӵ��ܴ��ֵ��
    ����·���ڲ�����
    */    
    if(CHG_Info.vBUS_Ref_Sum>0 && CHG_Info.vBUS_Ref_SS >= COM_CHG_VBUS_REF_MAX)   
    {
        CHG_Info.vBUS_Ref_Sum = (CHG_Info.vBUS_Ref_SS-(CHG_vBat_AD_Fir*COM_VBAT_BASE*N2_N1_RATIO*4>>12))<<10;//��*4����ʾĸ�ߵ�ѹ�Ŵ�4��
    }   
    
    /***************************************************************************/
    /*-------------------VBUS��������������------------------------------------*/    
    if(CHG_Info.vBUS_Set < CHG_Info.vBUS_Ref_SS)
    {
        CHG_Info.vBUS_Ref_Hold  +=CHG_Info.vBUS_Ref_Step_Val;
    }
    else
    {
        CHG_Info.vBUS_Ref_Hold   = CHG_Info.vBUS_Ref_SS << CHG_Info.vBUS_Ref_Shift_Val;
    }  
    CHG_Info.vBUS_Set = CHG_Info.vBUS_Ref_Hold >> CHG_Info.vBUS_Ref_Shift_Val;    
}


/*************************************************
Description: CHG_State_Deal
Input      : 
Return     : 
Others     : ���״̬�߼�����
*************************************************/  
void CHG_State_Deal(void)
{     
    if(SysClockBase_ms.sys_1ms == 1)
    {     
        if( DC_Ctrl_Info.mode == DC_CHARGE &&\
            COM_RUN_STATE == State_Context.state_Value && \
            Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE)//
        {
            //�������߼�����
            if( CHG_Info.finish_State == COM_CHG_FINISH_NOK &&\
                CHG_Info.vBat_AD >= CHG_Info.vBat_CC_CV_Val&&\
                CHG_Info.iBat_CHG_AD < CHG_Info.finish_IBat_Val)  
            {
                CHG_Info.finish_OK_Cnt ++;        
                if(CHG_Info.finish_OK_Cnt >= COM_CHG_FINISH_OK_TIME)
                {       
                    CHG_Info.finish_OK_Cnt = 0;
                    COM_PWM_Disable();  
                                      
                    Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                    Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                    Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                    Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                    
                    State_Context.flag.bit.initial_Ok       = E_FALSE;
                    State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                    State_Context.flag.bit.ready_Ok         = E_FALSE;                
                    State_Context.state_Value               = COM_INITIAL_STATE;
                    
                    DC_Ctrl_Info.FRE_Switch_Cnt = 0;            
                    CHG_Info.finish_State = COM_CHG_FINISH_OK; 
                    DC_Ctrl_Info.mode = 0;// 
                }            
            }
            else
            {
                //CHG_Info.finish_OK_Cnt = 0;
            }  
        } 
        
        //���ڸõ�ص�ѹ����������ɱ�־
        if( CHG_Info.vBat_AD <= CHG_Info.allow_VBat_Val &&\
            CHG_Info.finish_State == COM_CHG_FINISH_OK)
        {
            CHG_Info.finish_NOK_Cnt ++;
            if( CHG_Info.finish_NOK_Cnt >= COM_CHG_FINISH_NOK_TIME)
            {
                CHG_Info.finish_NOK_Cnt = 0;
                CHG_Info.finish_State = COM_CHG_FINISH_NOK;
            }
        } 
        else
        {
            CHG_Info.finish_NOK_Cnt = 0;
        } 
    } 
   
}
/*************************************************
Description: DC_DataSend
Input      : 
Return     : 
Others     : DC�����ݷ��͸���ѹ��
*************************************************/  
void DC_DataSend(void)
{ 
    //PFC��׼�����߼�����	
    if(DC_Ctrl_Info.mode == DC_CHARGE)//���״̬
    {     
        if(COM_Ctr_Info.INV_PFC_Ready_Status == 1 )     
        {
            if(DC_Ctrl_Info.INV_Ready_NOK_Cnt > 0)
                DC_Ctrl_Info.INV_Ready_NOK_Cnt --;
            if(DC_Ctrl_Info.INV_Ready_OK_Cnt < 20)
                DC_Ctrl_Info.INV_Ready_OK_Cnt ++;
            if(DC_Ctrl_Info.INV_Ready_OK_Cnt >= 20)
                DC_Ctrl_Info.INV_Ready_State = COM_INV_READY_STATE_OK; 
        }
        else 
        {
            if(DC_Ctrl_Info.INV_Ready_OK_Cnt > 0)
                DC_Ctrl_Info.INV_Ready_OK_Cnt --;
            if(DC_Ctrl_Info.INV_Ready_NOK_Cnt < 10)
                DC_Ctrl_Info.INV_Ready_NOK_Cnt ++;
            if(DC_Ctrl_Info.INV_Ready_NOK_Cnt >= 10 && DC_Ctrl_Info.INV_Ready_State == COM_INV_READY_STATE_OK)
            {
                COM_PWM_Disable(); 
                COM_Ctr_Info.test1_cnt+=3;
                State_Context.state_Value = COM_WAITING_STATE; 
                Run_Deal.flag.bit.OpenDriver_Ok = E_FALSE;              
                DC_Ctrl_Info.INV_Ready_State = COM_INV_READY_STATE_NOK;    
            }            
        }
    }
    
    
    /*------------------------------------------------------------------------------------*/			
    /*------------------�������ݸ�INV���ư�----------------------------------------*/     
    if(DC_Ctrl_Info.mode == DC_CHARGE)//���״̬
    {        
        if( COM_RUN_STATE == State_Context.state_Value && \
            Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE)//���״̬
        {             
            //����PFC��ĸ�ߵ�ѹ����ֵ
            VBUS_Calc();
        }
        
        if((COM_AD_Data_Info.auxPower_Val_Fir > COM_AUX_POWER_LVP_VAL &&  \
            COM_AD_Data_Info.auxPower_Val_Fir < COM_AUX_POWER_OVP_VAL)&& \
            (System_ProtectFlag_Info.all == 0) ) //�ж���乤����Դ�ڿ�����ⷶΧ�� 
        {         
            UART0_Info.TXD_W[6] = 1;//ǰ��׼��OK�źţ�1-��Դ׼��OK��0-׼�� NOK
        }
        else 
        {            
            UART0_Info.TXD_W[6] = 0; //ǰ��׼��OK�źţ�1-��Դ׼��OK��0-׼�� NOK
        }               
        UART0_Info.TXD_W[0] = 0X55AA;//2�ֽ�֡ͷ
        UART0_Info.TXD_W[1] = DC_Ctrl_Info.mode; //����ģʽ��1-�ŵ磻2-���    
        UART0_Info.TXD_W[2] = System_ProtectFlag_Info.all;//���͹��ϴ����PFC��
        
        UART0_Info.TXD_W[3] = CHG_Info.vBUS_Set;	//
        UART0_Info.TXD_W[4] = CHG_Info.finish_State;	//  
        UART0_Info.TXD_W[5] = 0;
      
        
    }    
    else if(DC_Ctrl_Info.mode == DC_DISCHARGE)//�ŵ�״̬
    {
        if((COM_AD_Data_Info.auxPower_Val_Fir > COM_AUX_POWER_LVP_VAL &&  \
            COM_AD_Data_Info.auxPower_Val_Fir < COM_AUX_POWER_OVP_VAL)&& \
            (System_ProtectFlag_Info.all == 0) ) //�ж���乤����Դ�ڿ�����ⷶΧ�� 
        {         
            UART0_Info.TXD_W[6] = 1;//ǰ��׼��OK�źţ�1-��Դ׼��OK��0-׼�� NOK
        }
        else 
        {            
            UART0_Info.TXD_W[6] = 0; //ǰ��׼��OK�źţ�1-��Դ׼��OK��0-׼�� NOK           
        }     
        UART0_Info.TXD_W[0] = 0X55AA;//2�ֽ�֡ͷ
        UART0_Info.TXD_W[1] = DC_Ctrl_Info.mode; //����ģʽ��1-�ŵ磻2-���    
        UART0_Info.TXD_W[2] = System_ProtectFlag_Info.all;//���͹��ϴ����PFC��
        UART0_Info.TXD_W[3] = 0;	//
        UART0_Info.TXD_W[4] = CHG_Info.finish_State;	//   
        UART0_Info.TXD_W[5] = 0;	  
    }  
    else if(DC_Ctrl_Info.mode == FREE_MODE)//����״̬
    {
          
        UART0_Info.TXD_W[0] = 0X55AA;//2�ֽ�֡ͷ                
        UART0_Info.TXD_W[1] = DC_Ctrl_Info.mode; //����ģʽ��1-�ŵ磻2-���    
        UART0_Info.TXD_W[2] = System_ProtectFlag_Info.all;//���͹��ϴ����PFC��
        UART0_Info.TXD_W[3] = 0;	//
        UART0_Info.TXD_W[4] = CHG_Info.finish_State;	//   
        UART0_Info.TXD_W[5] = 0;	
        UART0_Info.TXD_W[6] = 0;	//ǰ��׼��OK�źţ�1-��Դ׼��OK��0-׼�� NOK
    } 
     
    //����UART1�ķ������ݸ�ʽ        
    UART0_DC_DataSend(UART0_Info.TXD_W);       
    
}


/*************************************************
Description: User_UART_View
Input      : 
Return     : 
Others     : ���ڴ��ڵ���
*************************************************/
void User_UART_View(void)
{
    /*------------------------------------------------------------------------------------*/			
    /*---------------------UART0���ڵ���--------------------------------------------------*/	//1.2us			

    //COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_VBat.out,CHG_Info.vBUS_Ref_Sum>>10,CHG_Info.vBUS_Set);//
    //COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_VBat.out,CHG_PID_VBat.ref,CHG_Info.vBUS_Set);//
    //COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_IBat.ref ,CHG_Info.vBUS_Set ,ADSample_Info.iBat_CHG_AD_FIR+State_Context.state_Value*1000);//
    //COM_TxSendDebug(ADSample_Info.auxPower_AD_FIR,ADSample_Info.temp_NTC_AD_FIR ,ADSample_Info.ref_AD_FIR,ADSample_Info.iBat_CHG_AD_FIR+State_Context.state_Value*1000);//

    //COM_TxSendDebug(COM_Ctr_Info.INV_VBus_AD,DC_Ctrl_Info.EPWM_Duty ,ADSample_Info.vBusFB_AD,System_ProtectFlag_Info.all+COM_Ctr_Info.INV_PFC_Mode_Select*1000);//
    //COM_TxSendDebug(CHG_PID_IBat.out+System_ProtectFlag_Info.all,CHG_PID_IBat.ref+ CHG_Info.finish_State*500,ADSample_Info.iBat_DISC_AD_FIR ,CHG_Info.finish_OK_Cnt+State_Context.state_Value*1000);//
    //COM_TxSendDebug(CHG_PID_IBat.out+System_ProtectFlag_Info.all,CHG_PID_IBat.ref+ CHG_Info.finish_State*500,ADSample_Info.iBat_DISC_AD_FIR ,CHG_Info.finish_OK_Cnt+State_Context.state_Value*1000);//
   
//    COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_IBat.ref ,CHG_PID_IBat.fdb,CHG_Info.finish_OK_Cnt);//
//    COM_TxSendDebug(StartCheck_Flag_Info.all,AD_Correct_Vref.Flag.bit.ADRef_Correct_Ok ,COM_AD_Data_Info.vBat_Val_Fir,CHG_Info.finish_OK_Cnt);//

    Function_TxSendDebug(State_Context.state_Value*1000+DC_Ctrl_Info.mode*100+DC_Ctrl_Info.start_Finish_State*10,\
													CHG_Info.vBUS_Set*10>>2,CHG_PID_IBat.out,COM_Ctr_Info.INV_VBus_AD,CHG_PID_IBat.out);
	
//     Function_TxSendDebug(StartCheck_Flag_Info.bit.auxPower_High_OK*1000+StartCheck_Flag_Info.bit.auxPower_Low_OK*100+StartCheck_Flag_Info.bit.vBAT_High_OK*10+StartCheck_Flag_Info.bit.temp_High_OK,\
//													StartCheck_Flag_Info.bit.vBAT_Low_OK,AD_Correct_Vref.Flag.bit.ADRef_Correct_Ok,COM_Ctr_Info.INV_VBus_AD,State_Context.state_Value*1000+DC_Ctrl_Info.mode*100);   
    

//    COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_IBat.ref ,ADSample_Info.iBat_CHG_AD_FIR,CHG_Info.vBUS_Set);//
//     COM_TxSendDebug(CHG_PID_VBat.ref,CHG_PID_IBat.ref ,CHG_Info.iBat_CHG_AD,CHG_PID_VBat.fdb );//
    
//     COM_TxSendDebug(UART0_Info.RXD_W[2],DMAVEC->CTRL[1].DMACT ,UART0_Info.heart0_Cnt,UART0_Info.RXD_W[0]);//

//         COM_TxSendDebug(State_Context.state_Value*1000+DC_Ctrl_Info.mode*100,CHG_Info.iBat_CHG_AD,CHG_PID_IBat.out,DC_Ctrl_Info.EPWM_Period);//
////         COM_TxSendDebug(State_Context.state_Value*1000+DC_Ctrl_Info.mode*100,CHG_Info.iBat_CHG_AD,CHG_PID_IBat.out,PGI->POEGGA);//

////    COM_TxSendDebug(InvToDC_Data_Info.VACOUT_RMS,InvToDC_Data_Info.VACOUT_Freq ,InvToDC_Data_Info.VACOUT_Power,InvToDC_Data_Info.VBusAD_Val);//
    
//    COM_TxSendDebug(InvToDC_Data_Info.VACIN_RMS,InvToDC_Data_Info.VACIN_Freq,InvToDC_Data_Info.VACIN_PFC_Power,InvToDC_Data_Info.VACIN_BypassPower);//
////    COM_TxSendDebug(DcToMC_Data_Info.iBat_CHG_Fir,DcToMC_Data_Info.iBat_DISC_Fir ,DcToMC_Data_Info.vBat_Fir, DcToMC_Data_Info.temp_NTC);//
//    COM_TxSendDebug(COM_AD_Data_Info.vBat_Val_Fir,COM_AD_Data_Info.iBat_CHG_Val_Fir ,COM_AD_Data_Info.iBat_DISC_Val_Fir, COM_AD_Data_Info.auxPower_Val_Fir);//
//    COM_TxSendDebug(COM_AD_Data_Info.vBat_Val_Fir,COM_AD_Data_Info.vRef_Val_Fir ,COM_AD_Data_Info.temp_NTC_Val_Fir, COM_AD_Data_Info.auxPower_Val_Fir);//
 
//     COM_TxSendDebug(DcToMC_Data_Info.vBat_CHG_Power,DcToMC_Data_Info.VACIN_PFC_Power ,DcToMC_Data_Info.vBat_DISC_Power, DcToMC_Data_Info.VACOUT_Power);//

//    COM_TxSendDebug(CHG_PID_IBat.out+cnt_test,CHG_PID_IBat.ref ,ADSample_Info.iBat_CHG_AD_FIR +CHG_Info.finish_State*1000,CHG_Info.vBUS_Set);
    ////COM_TxSendDebug(CHG_Info.out,CHG_PID_IBat.ref ,State_Context.state_Value*1000+DC_Ctrl_Info.INV_Ready_State*500 ,CHG_Info.vBUS_Set);//
    //COM_TxSendDebug(CHG_PID_IBat.out,ADSample_Info.vBat_AD_FIR,ADSample_Info.auxPower_AD_FIR ,u16_ShutDown_Start_count);//

    //COM_TxSendDebug(State_Context.state_Value*1000,DC_Ctrl_Info.mode*1000+INV_WORK_STATE*500 ,ADSample_Info.vBat_AD_FIR,COM_Ctr_Info.INV_PFC_Mode_Select*1000);//
    //COM_TxSendDebug(State_Context.state_Value*1000,DC_Ctrl_Info.mode*1000 ,DC_Ctrl_Info.EPWM_Duty,COM_Ctr_Info.INV_PFC_Mode_Select*1000);//
    //COM_TxSendDebug(COM_Ctr_Info.INV_PFC_Mode_Select*1000+INV_WORK_STATE*500 ,State_Context.state_Value*1000 ,COM_Ctr_Info.INV_Mode_OK_Cnt*1000,DC_Ctrl_Info.mode*1000);//
    //COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_IBat.ref ,State_Context.state_Value*1000+COM_Ctr_Info.INV_PFC_Mode_Select*300 ,CHG_Info.vBUS_Set);//

            
    //COM_TxSendDebug(UART1_Info.dataBuffer[0]>>4 ,UART1_Info.dataBuffer[1] ,UART1_Info.dataBuffer[2],UART1_Info.dataBuffer[5]);//

    //COM_TxSendDebug(CHG_PID_IBat.out,CHG_PID_IBat.fdb ,State_Context.state_Value*1000+BAT_START_STATUS*300 ,DC_Ctrl_Info.EPWM_Duty);//

}
