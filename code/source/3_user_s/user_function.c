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
#include "sys_state_machine.h"
#include "sys_mcu_header.h"

/***************************************************************************/

/*************************************************
Description: User_DelayTime_ms
Input      : 
Return     : 
Others     : ms��ʱ����
*************************************************/
void User_DelayTime_ms(uint32_t delay)
{
	uint32_t i,j;
	
	for(i=0; i<delay; i++)
	{
		for(j=0; j<10000; j++) //1ms,64M
		{
			;
		}
	}
}


/*************************************************
Description: User_DelayTime_us
Input      : 
Return     : 
Others     : us��ʱ����
*************************************************/
void User_DelayTime_us(uint32_t delay)
{
	uint32_t i,j;
	
	for(i=0; i<delay; i++)
	{
		for(j=0; j<12; j++) //1ms,64M
		{
			;
		}
	}
}


/*************************************************
Description: DC_CloseDrive
Input      : 
Return     : 
Others     : ����ʱ�ر�����
*************************************************/
void DC_CloseDrive(void)
{	  
    if ( E_FALSE != System_ProtectFlag_Info.all )
    {
        #if OPERATING_MODE == NORMAL_MODE
            COM_PWM_Disable();	//�ر�PWM��� 
            State_Context.flag.bit.fault_Occur = E_TRUE;
        #endif
    }
    else 
    {
        State_Context.flag.bit.fault_Occur = E_FALSE;	
    }        
}


/*************************************************
Description: User_FAN_Deal
Input      : 
Return     : 
Others     : ɢ�ȷ��ȿ���
*************************************************/
int16_t i16FAN_Close_Cnt,i16FAN_Open_Cnt = 0;
void User_FAN_Deal(void)
{
    if(SysClockBase_ms.sys_Mode_1ms == 1)    
    {       
        /*------------------------------------------------------------------------------------*/
        /*---------------------ɢ�ȷ��ȿ���---------------------------------------------------*/
        if( COM_AD_Data_Info.temp_NTC_Val_Fir < COM_OPEN_FAN_TEMP_VALUE ||\
            COM_AD_Data_Info.iBat_CHG_Val_Fir >= COM_OPEN_FAN_CHG_IBAT_VALUE ||\
            COM_AD_Data_Info.iBat_DISC_Val_Fir >= COM_OPEN_FAN_DISC_IBAT_VALUE )  //�������ѹ����һ������45�棬��������
        {
            i16FAN_Close_Cnt = 0;
            if(i16FAN_Open_Cnt <= 200)  i16FAN_Open_Cnt ++;
            if(i16FAN_Open_Cnt >= 200)  FAN_ENABLE;                
        }
         if( COM_AD_Data_Info.temp_NTC_Val_Fir > COM_CLOSE_FAN_TEMP_VALUE &&\
             COM_AD_Data_Info.iBat_CHG_Val_Fir <= COM_CLOSE_FAN_CHG_IBAT_VALUE&&\
             COM_AD_Data_Info.iBat_DISC_Val_Fir <= COM_CLOSE_FAN_DISC_IBAT_VALUE)//�������ѹ�඼����35�棬�رշ���
        {
            i16FAN_Open_Cnt = 0;
            if(i16FAN_Close_Cnt <= 50)  i16FAN_Close_Cnt ++;
            if(i16FAN_Close_Cnt >= 50)  FAN_DISABLE;                      
        }  
    }
    //FAN_ENABLE;
}

/*************************************************
Description: User_LED_Deal
Input      : 
Return     : 
Others     : LEDָʾ���߼�
*************************************************/
void User_LED_ms(LED_Ctr_Var_t *LED_Info)
{

    if ( 1 == LED_Info->flag_1ms )   
    {
        LED_Info->period_Cnt ++;
    }
    
    if(LED_Info->cycle_Cnt <LED_Info->cycle_Val||LED_Info->cycle_Val==0)
    {
        if( LED_Info->period_Cnt < LED_Info->on_Val )   
            LED_GREEN_ON;
        else if( LED_Info->period_Cnt < LED_Info->period_Val)   
            LED_GREEN_OFF;
        else                                  
        {
            LED_Info->period_Cnt = 0;	
            if(LED_Info->cycle_Val>0)
                LED_Info->cycle_Cnt ++;
        }	
    }   
    else if(LED_Info->cycle_Cnt >=LED_Info->cycle_Val)
    {
        if( LED_Info->period_Cnt < (LED_Info->period_Val<<2))   
            LED_GREEN_OFF;
        else                                  
        {
            LED_Info->period_Cnt = 0;	
            LED_Info->cycle_Cnt = 0;
        }	      
    }
}

/*************************************************
Description: User_LED_Deal
Input      : 
Return     : 
Others     : LEDָʾ���߼�
*************************************************/
void User_LED_Deal(void)
{
    LED_Ctr_Info.flag_1ms = SysClockBase_ms.sys_LED_1ms;
    
/*---------------------------��ʼ׼��״̬�̵���˸0.5HZ-------------------------------------------*/
	if ( System_ProtectFlag_Info.all == 0 &&
	     State_Context.state_Value <= COM_READY_STATE )
    {		

        LED_Ctr_Info.on_Val = 250;
        LED_Ctr_Info.period_Val = 1500;
        User_LED_ms(&LED_Ctr_Info);        

    }
/*----------------------------����״̬�̵Ƴ���---------------------------------------------*/
    else if ( COM_RUN_STATE == State_Context.state_Value )
    {
        LED_Ctr_Info.on_Val =1000;
        LED_Ctr_Info.period_Val = 1500;
        User_LED_ms(&LED_Ctr_Info);          
    }
               
/*-------------------------------����״̬�̵��� 1HZ-------------------------------------*/
    else 
    {
        LED_Ctr_Info.on_Val =200;
        LED_Ctr_Info.period_Val = 400;
        switch( System_ProtectFlag_Info.all )
        {               
            case 1:  //����  LED��˸2��  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 2;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 2:  //ĸ�߹�Ƿѹ  LED��˸3��                  
            case 4:  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 3;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 64:  //������Դ��Ƿѹ  LED��˸4��                  
            case 128:  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 4;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 256:  //����  LED��˸5��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 5;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 512:  //
            case 1024:  //����  LED��˸6��                
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 6;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 2048:  //��ص�ѹ��Ƿѹ  LED��˸7��
            case 4096:  //��ص�ѹ��Ƿѹ  LED��˸7��                
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 7;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 8192:  //��ʼ��ʧ��  LED��˸8��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 8;
                User_LED_ms(&LED_Ctr_Info);
                break;                
            case 16384:  //�������  LED��˸9��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 9;
                User_LED_ms(&LED_Ctr_Info);
                break;   
            case 32768:  //ͨ�Ź���  LED��˸10��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 10;
                User_LED_ms(&LED_Ctr_Info);
                break; 
            case 32:  //VREF����  LED��˸11��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 11;
                User_LED_ms(&LED_Ctr_Info);
                break;                
            default: //  �̵���10��
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 12;
                User_LED_ms(&LED_Ctr_Info);
                break;
        } 	
    }
    SysClockBase_ms.sys_LED_1ms = 0;
    LED_Ctr_Info.flag_1ms = 0;
}


/*************************************************
Description: Key_Calc
Input      : 
Return     : 
Others     : �������ܳ����߼�����
*************************************************/
void Key_Calc( Key_Var_t *key )
{
    /*------------------------------------------------------------------------------------*/
    if( key->in == key->ref_Active_Level )	//�����ƽ���趨��Ч��ƽһ��
    {
        if ( key->release_Cnt > 0 )                   
        {
            key->release_Cnt--;			  
        }
        if ( key->close_Cnt < key->c_Delay_Val )  //�����պϼ����Ƚ�
        {
            key->close_Cnt++;
        }
        else
        {
              key->close_Cnt = 0;
              key->out_State = E_KEY_CLOSE;  //��ʾ��������
        }
    }
    else  //�����ƽ���趨��Ч��ƽ��һ��
    {
        if ( key->close_Cnt > 0 )                    
        {
            key->close_Cnt--;			
        }
        if ( key->release_Cnt < key->r_Delay_Val )  //�����ɿ������Ƚ�
        {
            key->release_Cnt++;
        }
        else
        {
              key->release_Cnt = 0;
              key->out_State = E_KEY_RELEASE;   //��ʾ�����ɿ� 
        }
    }
}


/*************************************************
Description: User_Key_Deal
Input      : 
Return     : 
Others     : ����״̬����
*************************************************/
uint8_t u8_Key_SW_ShutDown_Flag = 0;
uint16_t u16_ShutDown_Start_count,u16_ShutDown_Start_count1 = 0; 
void User_Key_Deal(void)
{
  	if (SysClockBase_ms.sys_1ms == 1 )
    {  				
        //δ���ܿ���ʱ�������е��Զ���ס��Դ�������г������
        if( COM_AD_Data_Info.auxPower_Val_Fir <= COM_START_CHECK_AUX_POWER_UP &&\
            COM_AD_Data_Info.auxPower_Val_Fir >= COM_START_CHECK_AUX_POWER_DOWN &&\
            COM_AD_Data_Info.vBat_Val_Fir <= COM_START_CHECK_VBAT_UP &&\
            COM_AD_Data_Info.vBat_Val_Fir >= COM_START_CHECK_VBAT_DOWN &&\
            POWER_LOCK_STATUS == 0 && u8_Key_SW_ShutDown_Flag == 0)
        { 
            if((++u16_ShutDown_Start_count1) >= COM_POWER_LOCK_TIME) //������ʱʱ��
            {
                POWER_LOCK_ENABLE;// P21�����Դ�����ź� :����Ϊ�ߵ�ƽ��ʾ���ڿ���״̬
                u16_ShutDown_Start_count1 = 0;                                         
            }            
        }
        else
        {
            u16_ShutDown_Start_count1 = 0;
        }


        
        //���ػ���ť	
        Key_SW_ShutDown.in = SHUT_DOWN_SWITCH;
        Key_SW_ShutDown.Calc( &Key_SW_ShutDown );
					
        //��Դ�����ź��߼�����					
        if ( Key_SW_ShutDown.out_State == E_KEY_CLOSE &&  POWER_LOCK_STATUS == 0 && u8_Key_SW_ShutDown_Flag == 0 )   //&&  State_Context.State_Identifier > 2 )  	//׼��״̬��ɺ�ʼ��Ч	
        {
            if((++u16_ShutDown_Start_count) >= COM_POWER_LOCK_TIME) //������ʱʱ��
            {
                POWER_LOCK_ENABLE;// // P21�����Դ�����ź� :����Ϊ�ߵ�ƽ��ʾ���ڿ���״̬
                u16_ShutDown_Start_count = 0;                            
                u8_Key_SW_ShutDown_Flag = 1; //��0����ʾ�����ɿ�����1����ʾ����δ�ɿ� 
                COM_Ctr_Info.Power_OnOff_Flag =1;                
            }
        }
        else  if( Key_SW_ShutDown.out_State == E_KEY_CLOSE &&  POWER_LOCK_STATUS == 1 && u8_Key_SW_ShutDown_Flag == 0)  	                                  		
        {
            //�ر�����

            COM_PWM_Disable(); 
            System_ProtectFlag_Info.all |= E_SYS_INIT_FAIL;
            POWER_LOCK_DISABLE; // P21�����Դ�����ź� :����Ϊ�͵�ƽ��ʾ���ڹػ�״̬
            u8_Key_SW_ShutDown_Flag = 1; //��0����ʾ�����ɿ�����1����ʾ����δ�ɿ�
            COM_Ctr_Info.Power_OnOff_Flag = 0;
        }

        //���ػ���ť�ɿ���־λ
        if ( Key_SW_ShutDown.out_State == E_KEY_RELEASE) 	
        {
            u8_Key_SW_ShutDown_Flag = 0;   //��0����ʾ�����ɿ�����1����ʾ����δ�ɿ�			
        }
        
    }
}



/*************************************************
Description: COM_CHG_INV_Select
Input      : 
Return     : 
Others     : �����߷ŵ繦��ѡ��
*************************************************/
void COM_CHG_INV_Select(void)
{ 
    if(SysClockBase_ms.sys_Mode_1ms == 1)    
    {                        
        //COM_Ctr_Info.INV_PFC_Mode_Select = 2;
        //�е�����жϣ��趨����ģʽΪPFC״̬
        if( System_ProtectFlag_Info.all == 0 && \
            State_Context.state_Value <= COM_RUN_STATE && \
            (DC_Ctrl_Info.mode == 1 || DC_Ctrl_Info.mode == 0)    &&\
            INV_WORK_STATE          == 1         &&\
            CHG_Info.finish_State   == COM_CHG_FINISH_NOK &&\
            COM_Ctr_Info.INV_PFC_Mode_Select == 2) //              
        {       
            if(COM_Ctr_Info.PFC_Mode_OK_Cnt < COM_Ctr_Info.PFC_Mode_OK_TimeVal)
                COM_Ctr_Info.PFC_Mode_OK_Cnt++;

            if(COM_Ctr_Info.PFC_Mode_OK_Cnt >= COM_Ctr_Info.PFC_Mode_OK_TimeVal)
            { 
                //���½����ʼ���׶�    
              
                COM_PWM_Disable();	//�ر�PWM������̵���            

                Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                
                State_Context.flag.bit.initial_Ok       = E_FALSE;
                State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                State_Context.flag.bit.ready_Ok         = E_FALSE;                
                State_Context.state_Value               = COM_WAITING_STATE;

                DC_Ctrl_Info.INV_Ready_State = COM_INV_READY_STATE_NOK;    
                COM_Ctr_Info.PFC_Mode_OK_Cnt = 0;
                DC_Ctrl_Info.mode = 2;//����е���������ģʽΪPFCģʽ
            }
        }
        else
        {
            COM_Ctr_Info.PFC_Mode_OK_Cnt = 0; 
        }
        
        if( System_ProtectFlag_Info.all == 0 && \
            State_Context.state_Value <= COM_RUN_STATE && \
            (DC_Ctrl_Info.mode == 2 || DC_Ctrl_Info.mode == 0) &&\
            INV_WORK_STATE == 0 )
        {
            if(COM_Ctr_Info.INV_Mode_OK_Cnt < COM_Ctr_Info.INV_Mode_OK_TimeVal)
                COM_Ctr_Info.INV_Mode_OK_Cnt++;
            if(COM_Ctr_Info.INV_Mode_OK_Cnt >= COM_Ctr_Info.INV_Mode_OK_TimeVal)
            {    
                COM_Ctr_Info.INV_Mode_OK_Cnt = 0;
               
                //���½����ʼ���׶�                     
                COM_PWM_Disable();	//�ر�PWM������̵���            
                
                Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                
                State_Context.flag.bit.initial_Ok       = E_FALSE;
                State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                State_Context.flag.bit.ready_Ok         = E_FALSE;
                State_Context.state_Value               = COM_WAITING_STATE;
                CHG_Info.vBUS_Set              = 0;   //����ɾ��             
                DC_Ctrl_Info.INV_Ready_State = COM_INV_READY_STATE_NOK;
                COM_Ctr_Info.INV_Mode_OK_Cnt = 0;                    
                DC_Ctrl_Info.mode = 1;//Ĭ�����ģʽ  
                DC_Ctrl_Info.start_Finish_State = COM_START_FINISH_STATE_NOK;

            }
        }
        else
        {
            COM_Ctr_Info.INV_Mode_OK_Cnt = 0; 
        }  


        //COM_Ctr_Info.INV_PFC_Mode_Select = 0;
        //�趨����ģʽΪ����״̬
        if( System_ProtectFlag_Info.all == 0 && \
            State_Context.state_Value <= COM_RUN_STATE && \
            (DC_Ctrl_Info.mode == 1 || DC_Ctrl_Info.mode == 2)    &&\
            INV_WORK_STATE == 1         &&\
            COM_Ctr_Info.INV_PFC_Mode_Select == 0) //              
        {       
            if(COM_Ctr_Info.NO_Mode_OK_Cnt < COM_Ctr_Info.NO_Mode_OK_TimeVal)
                COM_Ctr_Info.NO_Mode_OK_Cnt++;

            if(COM_Ctr_Info.NO_Mode_OK_Cnt >= COM_Ctr_Info.NO_Mode_OK_TimeVal)
            { 
                //���½����ʼ���׶�                     
                COM_PWM_Disable();	//�ر�PWM������̵���            

                Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                
                State_Context.flag.bit.initial_Ok       = E_FALSE;
                State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                State_Context.flag.bit.ready_Ok         = E_FALSE;                
                State_Context.state_Value               = COM_WAITING_STATE;
                
                CHG_Info.vBUS_Set              = 0;   //����ɾ��             
               
                COM_Ctr_Info.NO_Mode_OK_Cnt = 0;
                DC_Ctrl_Info.mode = 0;//����ģʽ����ģʽ
            }
        }
        else
        {
            COM_Ctr_Info.NO_Mode_OK_Cnt = 0; 
        }   
    }
    SysClockBase_ms.sys_Mode_1ms = 0;    
}


/*************************************************
Description: COM_UART0_Deal
Input      : 
Return     : 
Others     : ����0���ݴ���
*************************************************/
int init_crc = 0;
uint8_t *UART0_RXD_B_Temp;
int32_t CHG_vBat_AD_Hold,CHG_vBat_AD_Fir = 0;
void COM_UART0_Deal(void)
{
    //��ص�ѹADֵ�˲����������ʱʹ��
    CHG_vBat_AD_Hold = DFILTER_N(6,CHG_Info.vBat_AD,CHG_vBat_AD_Hold);
    CHG_vBat_AD_Fir = CHG_vBat_AD_Hold >> 16;   

    
    /*------------------------ͨ�����ݽ���-----------------------------------------------------*/	
    /*---------------------8λ����ת��Ϊ16λ��ʽ------------------------------------------*/
    if( DMAVEC->CTRL[1].DMACT ==0)
    {        
        for(int i=0;i<=UART0_SEND_NUM;i++)
        {
            if(UART0_Info.RXD_B[i] == 0XAA && UART0_Info.RXD_B[i+1] == 0X55)
            {
                UART0_RXD_B_Temp = &(UART0_Info.RXD_B[i]);
                break;
            }
        }
          
        //CRCУ�����ô���
        for(int i=0;i<(UART0_SEND_NUM-2);i++)
        {
            UART0_Info.RXD_CRC_Calc = crc16_modbus(&UART0_RXD_B_Temp[i],1,UART0_Info.RXD_CRC_Init ); 
            UART0_Info.RXD_CRC_Init = UART0_Info.RXD_CRC_Calc;          	 
        }  
        UART0_Info.RXD_CRC_Init = 0xffff;//��ʼ��CRC�Ĵ�����ʼֵ    
            
        //���յ�CRCУ���봦��
        UART0_Info.RXD_CRC_CkCd =   (UART0_RXD_B_Temp[UART0_SEND_NUM-2])+\
                                    (UART0_RXD_B_Temp[UART0_SEND_NUM-1]<<8);
    
        //�����CRCУ��������յ�CRCУ�������ȽϺ�֡ͷ�ж�(0X55AA)
        if( UART0_Info.RXD_CRC_Calc == UART0_Info.RXD_CRC_CkCd  &&\
            UART0_RXD_B_Temp[0] == 0XAA && UART0_RXD_B_Temp[1] == 0X55)
        {
            for(int i=0; i < (UART0_SEND_NUM>>1); i++)
            {
                UART0_Info.RXD_W[i] = UART0_RXD_B_Temp[2 * i] + (UART0_RXD_B_Temp[2 * i+1] << 8);			
            }
            
            /*------------------------------------------------------------------------------------*/			
            /*---------------------UART1ͨ������λ�߼�--------------------------------------------*/					
            if(UART0_Info.heart_Status == 0)				
            {
                UART0_Info.heart_Status = 1;
            }
            else 																
            {
                UART0_Info.heart_Status = 0;
            }             
        }
        
        
        DMAVEC->CTRL[1].DMACT = UART0_RECE_NUM;
        DMAVEC->CTRL[1].DMDAR = (uint32_t)(void *)&UART0_Info.RXD_B[0];
        DMA->DMAEN0 |= 1<<DMA_VECTOR_1; 
    }

    if(SysClockBase_ms.sys_1ms == 1)    
    {
        /*------------------------------------------------------------------------------------*/				
        /*---------------------UART1ͨ���������----------------------------------------------*/        
        COM_Uartx_HeartCheck(&UART0_Info);
    }    
    
    /*------------------------------------------------------------------------------------*/				
    /*---------------------UART1ͨ���쳣������--------------------------------------------*/	
    if(UART0_Info.heart_OK_Status == 0)  ////UART2��������ͨ���쳣ʱ RXD0_Status_Heart_OK����״̬Ϊ 0
    {
        if(System_ProtectFlag_Info.all == 0 && OPERATING_MODE == NORMAL_MODE)
            System_ProtectFlag_Info.all |= E_COMMUNICA_ERR;//ͨ�Ź���
        
        UART0_Info.RXD_W[0] = 0;   //2�ֽ�֡ͷ���� ��			
        UART0_Info.RXD_W[1] = 0;   //2����ѡ��PFC����ģʽ��  1����ѡ��INV����ģʽ
        UART0_Info.RXD_W[2] = 0;	//�󼶹��ϴ���
        UART0_Info.RXD_W[3] = 0;	//��������ѹֵ��RMS�� --ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10��
        UART0_Info.RXD_W[4] = 0;	//���������ʣ�W��  
        UART0_Info.RXD_W[5] = 0;	//ע�⣺��ʵĸ�ߵ�ѹֵ�Ŵ�10��
        UART0_Info.RXD_W[6] = 0;	//��乤����Դ״̬OKΪ1��״̬������Ϊ0
        UART0_Info.RXD_W[7] = 0;	//ע�⣺��������ѹƵ����������ʵƵ�ʷŴ�10��
        UART0_Info.RXD_W[8] = 0;	//�е������ѹֵ��RMS��--ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10��
        UART0_Info.RXD_W[9] = 0;	//�е�����PFC���ʣ�W��----��е���*�����ѹ
        UART0_Info.RXD_W[10] = 0;	//�е�������·���ʣ�W��--���ص�����Чֵ*�����ѹ��Чֵ
        UART0_Info.RXD_W[11] = 0;	//ע�⣺�е������ѹƵ����������ʵƵ�ʷŴ�10��         
    }
        
    COM_Ctr_Info.INV_VBus_AD            = UART0_Info.RXD_W[5];
    COM_Ctr_Info.INV_PFC_Mode_Select    = UART0_Info.RXD_W[1];
    COM_Ctr_Info.INV_PFC_Ready_Status   = UART0_Info.RXD_W[6]; 
    
    
    //������DC��ĵ�ѹ/����/Ƶ�����ݴ���
    InvToDC_Data_Info.err_Code = UART0_Info.RXD_W[2];//������
    InvToDC_Data_Info.mode_State = UART0_Info.RXD_W[1];//����ģʽ���ŵ���߳�� 
    
    //ע�⣺��DC�෢�͵�VBUSĸ�ߵ�ѹ���ݣ���ʵĸ�ߵ�ѹֵ�Ŵ�10�� 
    InvToDC_Data_Info.VBusAD_Val = UART0_Info.RXD_W[5];//ע�⣺��ʵĸ�ߵ�ѹֵ�Ŵ�10��
    
    //ע�⣺��DC�෢�͵���������ѹ��Чֵ��������ʵ��Чֵ�Ŵ�10�� 
    InvToDC_Data_Info.VACOUT_RMS = UART0_Info.RXD_W[3];//��������ѹֵ��RMS�� --ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10��
    
    //ע�⣺��DC�෢�͵���������ѹƵ����������ʵƵ�ʷŴ�10�� 
    InvToDC_Data_Info.VACOUT_Freq = UART0_Info.RXD_W[7];//��������ѹƵ�ʣ�Hz��
    InvToDC_Data_Info.VACOUT_Power = UART0_Info.RXD_W[4];//���������ʣ�W��
    
    //ע�⣺��DC�෢�͵��е������ѹ��Чֵ��������ʵ��Чֵ�Ŵ�10�� 
    InvToDC_Data_Info.VACIN_RMS = UART0_Info.RXD_W[8];//�е������ѹֵ��RMS��--ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10��  
    
    //ע�⣺��DC�෢�͵��е������ѹƵ����������ʵƵ�ʷŴ�10��
    InvToDC_Data_Info.VACIN_Freq = UART0_Info.RXD_W[11];//�е������ѹƵ�ʣ�Hz��
    InvToDC_Data_Info.VACIN_PFC_Power = UART0_Info.RXD_W[9];//�е�����PFC���ʣ�W��----��е���*�����ѹ
    InvToDC_Data_Info.VACIN_BypassPower = UART0_Info.RXD_W[10];//�е�������·���ʣ�W��--���ص�����Чֵ*�����ѹ��Чֵ


    //����ͨ��,DC�����ݷ�����INV��
    if(UART0_Info.TXD_Period_Cnt >= UART0_Info.TXD_Period_Val)
    {               
        DC_DataSend();
        UART0_Info.TXD_Period_Cnt = 0;
    }    
    
}


/*************************************************
Description: COM_UART1_Deal
Input      : 
Return     : 
Others     : ����1���ݴ���
*************************************************/
uint8_t BMS_flagtest = 0;
void COM_UART1_Deal(void)
{
    //���ϴ��룬����������
////    if(System_ProtectFlag_Info.bit.OTP == 1)
////    {
////        DcToMC_Data_Info.Flag.u32ErrCode = 0x10;//
////    }
////    else if(System_ProtectFlag_Info.bit.iBAT_CHG_OCP == 1||System_ProtectFlag_Info.bit.iBAT_DISC_OCP)
////    {
////        DcToMC_Data_Info.Flag.u32ErrCode = 0x04;
////    }
////    else if(System_ProtectFlag_Info.bit.vBAT_LVP == 1||System_ProtectFlag_Info.bit.vBAT_OVP == 1)
////    {
////        DcToMC_Data_Info.Flag.u32ErrCode = 0x08;//
////    } 
////    else if(System_ProtectFlag_Info.bit.INV_ERR == 1&&InvToDC_Data_Info.err_Code==1)
////    {
////        DcToMC_Data_Info.Flag.u32ErrCode = 0x02;//
////    } 
////    else if(System_ProtectFlag_Info.bit.INV_ERR == 1&&InvToDC_Data_Info.err_Code==32)
////    {
////        DcToMC_Data_Info.Flag.u32ErrCode = 0x01;//
////    } 

    //DC�෢����MC���ص�����
    //��16λΪ������ϴ��룬��16λΪDC����ϴ���;�������޸�
    DcToMC_Data_Info.Flag.u32ErrCode= InvToDC_Data_Info.err_Code + (System_ProtectFlag_Info.all<<16);
    DcToMC_Data_Info.mode_State     = DC_Ctrl_Info.mode;//����ģʽ���ŵ���߳�� 
    DcToMC_Data_Info.VACOUT_RMS     = InvToDC_Data_Info.VACOUT_RMS;//��������ѹֵ��RMS�� --ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10�� 
    DcToMC_Data_Info.VACOUT_Freq    = InvToDC_Data_Info.VACOUT_Freq;//ע�⣺��DC�෢�͵���������ѹƵ����������ʵƵ�ʷŴ�10�� 
    DcToMC_Data_Info.VACOUT_Power   = InvToDC_Data_Info.VACOUT_Power;//���������ʣ�W��
    DcToMC_Data_Info.VACIN_RMS      = InvToDC_Data_Info.VACIN_RMS;//�е������ѹֵ��RMS��--ע�⣺��ʵ��ѹ��Чֵ�Ŵ�10��    
    DcToMC_Data_Info.VACIN_Freq     = InvToDC_Data_Info.VACIN_Freq;//ע�⣺��DC�෢�͵��е������ѹƵ����������ʵƵ�ʷŴ�10��
    DcToMC_Data_Info.VACIN_PFC_Power    = InvToDC_Data_Info.VACIN_PFC_Power;//�е�����PFC���ʣ�W��----��е���*�����ѹ
    DcToMC_Data_Info.VACIN_BypassPower  = InvToDC_Data_Info.VACIN_BypassPower;//�е�������·���ʣ�W��--���ص�����Чֵ*�����ѹ��Чֵ
    
    DcToMC_Data_Info.vBat       = COM_AD_Data_Info.vBat_Val_Fir;//��ص�ѹ��ʵֵ�Ŵ�����COM_REAL_VBAT_SCAL��
    DcToMC_Data_Info.iBat_CHG   = COM_AD_Data_Info.iBat_CHG_Val_Fir;//��س������Ŵ�����COM_REAL_IBAT_CHG_SCAL��
    DcToMC_Data_Info.temp_NTC   = ADSample_Info.temp_NTC_AD_FIR;//�����¶�   
    DcToMC_Data_Info.iBat_DISC  = COM_AD_Data_Info.iBat_DISC_Val_Fir;//��طŵ�����Ŵ�����COM_REAL_IBAT_DISC_SCAL��
    DcToMC_Data_Info.vBat_CHG_Power     = COM_AD_Data_Info.vBat_CHG_Power;//��س�繦�ʣ�W��
    DcToMC_Data_Info.vBat_DISC_Power    = COM_AD_Data_Info.vBat_DISC_Power;//��طŵ繦�ʣ�W��

    if( COM_RUN_STATE == State_Context.state_Value && \
        Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE  && \
        DC_Ctrl_Info.mode == DC_CHARGE&&SysClockBase_ms.sys_1ms == 1)
    {
       ////���ñ仯����������  BMS_Order_Info.cnt1++;
        if(BMS_Order_Info.cnt1 >=15000&&BMS_flagtest==0)
        {
            BMS_flagtest = 1;
            BMS_Order_Info.cnt1 = 0;
            BMS_Order_Info.Flag.bit.Set_CC_Flag = 1;
            BMS_Order_Info.set_CC_Val = COM_CHG_IBAT_MAX_VAL*10 - (COM_CHG_IBAT_MAX_VAL/2)*10;
            
            BMS_Order_Info.Flag.bit.Set_CV_Flag = 1;
            BMS_Order_Info.set_CV_Val = (COM_CHG_VBAT_MAX_VAL*10-1.7*10) ;
        }
        else if(BMS_Order_Info.cnt1 >=15000&&BMS_flagtest==1)
        {
            
            BMS_flagtest = 0;
            BMS_Order_Info.cnt1 = 0;
            BMS_Order_Info.Flag.bit.Set_CC_Flag = 1;
            BMS_Order_Info.set_CC_Val = COM_CHG_IBAT_MAX_VAL*10 + (COM_CHG_IBAT_MAX_VAL/2)*10;  

            BMS_Order_Info.Flag.bit.Set_CV_Flag = 1;
            BMS_Order_Info.set_CV_Val = (COM_CHG_VBAT_MAX_VAL*10-1.7*10) ;//(COM_CHG_VBAT_MAX_VAL*10) ;            
        }
            
    }    
    
    //�趨��ѹֵ
    if(0&&BMS_Order_Info.Flag.bit.Set_CV_Flag == 1)
    {
        CHG_Info.allow_VBat_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -1.8*10) *   4096 / COM_VBAT_BASE /10;;
        CHG_Info.vBat_CV_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.3*10) *   4096 / COM_VBAT_BASE /10;//�����ⲿ�����ѹֵ,�Ŵ�10��
        CHG_Info.vBat_CC_CV_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.8*10) *   4096 / COM_VBAT_BASE /10;
        CHG_Info.vBat_FC_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.3*10) *   4096 / COM_VBAT_BASE /10;
        CHG_Info.CC2_Flag = 0;  
        BMS_Order_Info.Flag.bit.Set_CV_Flag = 0;

    }
    
    //BMS�·��趨������ֵ
    if(1&&BMS_Order_Info.Flag.bit.Set_CC_Flag == 1)   
    {
     
        CHG_Info.iBat_CC1_Val = (uint32_t)BMS_Order_Info.set_CC_Val *COM_IBAT_CHG_SCAL/10;//�����ⲿ�������ֵ,�Ŵ�10��
        CHG_Info.iBat_CC2_Val = (uint32_t)(BMS_Order_Info.set_CC_Val - 0.5*10) *COM_IBAT_CHG_SCAL/10;
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_CC1_Val;
//        CHG_Info.CC2_Flag = 0;
        BMS_Order_Info.Flag.bit.Set_CC_Flag = 0;
        
        //������������
        if(CHG_Info.iBat_CC1_Val > COM_CHG_IBAT_CC1_VAL)   CHG_Info.iBat_CC1_Val = COM_CHG_IBAT_CC1_VAL; 
        if(CHG_Info.iBat_CC2_Val > COM_CHG_IBAT_CC1_VAL)   CHG_Info.iBat_CC2_Val = COM_CHG_IBAT_CC1_VAL; 
        //������С������
        if(CHG_Info.iBat_CC1_Val < COM_CHG_IBAT_TC_VAL)   CHG_Info.iBat_CC1_Val = COM_CHG_IBAT_TC_VAL; 
        if(CHG_Info.iBat_CC2_Val < COM_CHG_IBAT_TC_VAL)   CHG_Info.iBat_CC2_Val = COM_CHG_IBAT_TC_VAL;         
    }
  
}

/*************************************************
Description: COM_UART2_Deal
Input      : 
Return     : 
Others     : ����2���ݴ���
*************************************************/
void COM_UART2_Deal(void)
{
    static uint16_t u8UartDebug_Cnt1 = 0;
    
    u8UartDebug_Cnt1 ++;
    /*------------------------------------------------------------------------------------*/			
    /*---------------------UART0���ڵ���--------------------------------------------------*/	
    if(u8UartDebug_Cnt1 > 4096)        
    {
        u8UartDebug_Cnt1 = 0;
        User_UART_View();
    }
 
}


/*************************************************
Description: COM_AD_Data_Deal
Input      : 
Return     : 
Others     : AD������ʵ���ݴ���
*************************************************/
void COM_AD_Data_Deal(void)
{
    //��ȡ����AD����
    ADSample_Info.ref_AD_FIR        = ADC2->ADDR3;  //VREF_2.5V����  
    ADSample_Info.temp_NTC_AD_FIR   = ADC2->ADDR15;//�¶Ȳ���
    ADSample_Info.auxPower_AD_FIR   = ADC2->ADDR12;//������Դ��ѹ����   
    
    //AD������ʵ���ݴ���,����ʵֵ�����ϷŴ��趨����
    COM_AD_Data_Info.Sum_Cnt++;
    COM_AD_Data_Info.vRef_Sum       += ADSample_Info.ref_AD_FIR ;//��׼VREF
    COM_AD_Data_Info.temp_NTC_Sum   += ADSample_Info.temp_NTC_AD_FIR;//�¶�     
    COM_AD_Data_Info.vBat_Sum       += ADSample_Info.vBat_AD_FIR * COM_REAL_VBAT_SCAL * COM_VBAT_BASE>>12;//��ص�ѹ     
    COM_AD_Data_Info.iBat_CHG_Sum   += ADSample_Info.iBat_CHG_AD_FIR * COM_REAL_IBAT_CHG_SCAL * COM_IBAT_CHG_BASE>>12;//��س�����
    COM_AD_Data_Info.iBat_DISC_Sum  += ADSample_Info.iBat_DISC_AD_FIR * COM_REAL_IBAT_DISC_SCAL * COM_IBAT_DISC_BASE>>12;//��طŵ����
    COM_AD_Data_Info.auxPower_Sum   += ADSample_Info.auxPower_AD_FIR * COM_REAL_AUXPOWER_SCAL * COM_AUX_POWER_BASE>>12;//������Դ��ѹ     
    if(COM_AD_Data_Info.Sum_Cnt>=1024)
    {  
        COM_AD_Data_Info.vRef_Val       = COM_AD_Data_Info.vRef_Sum>>10;
        COM_AD_Data_Info.temp_NTC_Val   = COM_AD_Data_Info.temp_NTC_Sum>>10;           
        COM_AD_Data_Info.vBat_Val       = COM_AD_Data_Info.vBat_Sum>>10;
        COM_AD_Data_Info.iBat_CHG_Val   = COM_AD_Data_Info.iBat_CHG_Sum>>10;       
        COM_AD_Data_Info.auxPower_Val   = COM_AD_Data_Info.auxPower_Sum>>10;
        COM_AD_Data_Info.iBat_DISC_Val  = COM_AD_Data_Info.iBat_DISC_Sum>>10;
        
        COM_AD_Data_Info.vRef_Hold      = DFILTER_N(4,(COM_AD_Data_Info.vRef_Val),COM_AD_Data_Info.vRef_Hold);
        COM_AD_Data_Info.vRef_Val_Fir   = COM_AD_Data_Info.vRef_Hold >> 16;//������Դ��ѹ          

        COM_AD_Data_Info.temp_NTC_Hold      = DFILTER_N(4,(COM_AD_Data_Info.temp_NTC_Val),COM_AD_Data_Info.temp_NTC_Hold);
        COM_AD_Data_Info.temp_NTC_Val_Fir   = COM_AD_Data_Info.temp_NTC_Hold >> 16;//������Դ��ѹ          
               
        COM_AD_Data_Info.auxPower_Hold      = DFILTER_N(4,(COM_AD_Data_Info.auxPower_Val),COM_AD_Data_Info.auxPower_Hold);
        COM_AD_Data_Info.auxPower_Val_Fir   = COM_AD_Data_Info.auxPower_Hold >> 16;//������Դ��ѹ          
        
        COM_AD_Data_Info.vBat_Hold          = DFILTER_N(4,COM_AD_Data_Info.vBat_Val,COM_AD_Data_Info.vBat_Hold);
        COM_AD_Data_Info.vBat_Val_Fir       = COM_AD_Data_Info.vBat_Hold >> 16;//��ص�ѹ  

        COM_AD_Data_Info.iBat_CHG_Hold      = DFILTER_N(5,(COM_AD_Data_Info.iBat_CHG_Val),COM_AD_Data_Info.iBat_CHG_Hold);
        COM_AD_Data_Info.iBat_CHG_Val_Fir   = COM_AD_Data_Info.iBat_CHG_Hold >> 16;//��س�����    

        COM_AD_Data_Info.iBat_DISC_Hold     = DFILTER_N(5,(COM_AD_Data_Info.iBat_DISC_Val),COM_AD_Data_Info.iBat_DISC_Hold);
        COM_AD_Data_Info.iBat_DISC_Val_Fir  = COM_AD_Data_Info.iBat_DISC_Hold >> 16;//��طŵ����  
      
        
        COM_AD_Data_Info.Sum_Cnt        = 0;
        COM_AD_Data_Info.vRef_Sum       = 0;
        COM_AD_Data_Info.temp_NTC_Sum   = 0;            
        COM_AD_Data_Info.vBat_Sum       = 0;        
        COM_AD_Data_Info.iBat_CHG_Sum   = 0;  
        COM_AD_Data_Info.auxPower_Sum   = 0;
        COM_AD_Data_Info.iBat_DISC_Sum  = 0;                
    }  

    COM_AD_Data_Info.vBat_CHG_Power     = COM_AD_Data_Info.vBat_Val_Fir * COM_AD_Data_Info.iBat_CHG_Val_Fir/ \
                                        (COM_REAL_VBAT_SCAL*COM_REAL_IBAT_CHG_SCAL);//��س�繦�ʣ�W��
    COM_AD_Data_Info.vBat_DISC_Power    = COM_AD_Data_Info.vBat_Val_Fir * COM_AD_Data_Info.iBat_DISC_Val_Fir/ \
                                        (COM_REAL_VBAT_SCAL*COM_REAL_IBAT_DISC_SCAL);;//��طŵ繦�ʣ�W��
    
}


/*************************************************
Description: COM_CHG_Data_Deal
Input      : 
Return     : 
Others     : ���ռ�ձȻ�����������·���������״̬�������������ѹ������������
*************************************************/
void COM_CHG_Data_Deal(void)
{
     if( COM_RUN_STATE == State_Context.state_Value && \
        Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE  && \
        DC_Ctrl_Info.mode == DC_CHARGE)
    {   
        if( CHG_Info.finish_State == COM_CHG_FINISH_NOK&&\
            (DC_Ctrl_Info.INV_Ready_State == COM_INV_READY_STATE_OK||\
            DC_Ctrl_Info.mode_Operate == DEBUG_MODE))
        {                 
            CHG_PWM_SS();//������ʱ����ռ�ձȻ�����
            CHG_IBAT_SS();//IBAT�������ƻ�·����������
            
            //���״̬�������������ѹ������������
            CHG_State_Select();
                
            if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//
            {
                CHG_Info.Sec_Cnt = 0;//��ʱ������ֵ����
            }              
        }                       
    } 
}
    
    
/*************************************************
Description: COM_Function
Input      : 
Return     : 
Others     : �û�����ִ��
*************************************************/
uint8_t u8System1ms_Cnt = 0;
void COM_Function(void)
{
    //��ȡ״̬����״̬            
    State_Context.ContextPtr( &State_Context );                
    
    //ִ��״̬����Ӧ������
    State_Context_Task();    
    
    //����ʱ�ر���� 
    DC_CloseDrive(); 
    
    //LED��ʾ����    
    User_LED_Deal();	
    
    //�����߼�����
    User_Key_Deal();
    
    //���ȿ��ƴ���
    User_FAN_Deal();
       
    //����0���ݴ���(��INV��ͨ��)
    COM_UART0_Deal();

    //����1���ݴ���(�����ز�ͨ��)
    COM_UART1_Deal();
    
    //����2���ݴ���(����)
    COM_UART2_Deal();
    
    //�����߷ŵ繦��ѡ��
    COM_CHG_INV_Select();  
              
    //���״̬�߼�����(�����ɺ����ó��)
    CHG_State_Deal();    
    
    //AD������ʵ���ݴ���
    COM_AD_Data_Deal(); 
 
     //���ռ�ձȻ�����������·���������״̬�������������ѹ������������
    COM_CHG_Data_Deal(); 
    
              
    if(SysClockBase_ms.sys_1ms == 1)    
    {          
        u8System1ms_Cnt ++;//
    }        
    if(u8System1ms_Cnt>=2)
    {
        SysClockBase_ms.sys_1ms = 0;//1ms ʱ�ӱ������
        u8System1ms_Cnt =0;//1msʱ��������Main�������ڵ����ڼ���ֵ����
    }
           
    //���ഫ������߼�����
    if( BOSOC_STATUS == 0&&\
        E_TRUE == StartCheck_Flag_Info.bit.auxPower_Low_OK &&\
        System_ProtectFlag_Info.all == 0 &&\
        OPERATING_MODE == NORMAL_MODE  )
    {
        if(COM_Ctr_Info.INV_ERR_CODE ==0)
            COM_Ctr_Info.INV_ERR_CODE = UART0_Info.RXD_W[2];       
        System_ProtectFlag_Info.all |= E_INV_ERR;
    }
}
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/



