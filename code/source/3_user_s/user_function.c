/*****************************************************************************
Copyright (C) 2021 China Micro Semiconductor Limited Company. All Rights Reserved.
@Description: 
@Author     : 
@Version    : 0.0.1  
@History    : 
@Attention  ：
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
Others     : ms延时函数
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
Others     : us延时函数
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
Others     : 保护时关闭驱动
*************************************************/
void DC_CloseDrive(void)
{	  
    if ( E_FALSE != System_ProtectFlag_Info.all )
    {
        #if OPERATING_MODE == NORMAL_MODE
            COM_PWM_Disable();	//关闭PWM输出 
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
Others     : 散热风扇控制
*************************************************/
int16_t i16FAN_Close_Cnt,i16FAN_Open_Cnt = 0;
void User_FAN_Deal(void)
{
    if(SysClockBase_ms.sys_Mode_1ms == 1)    
    {       
        /*------------------------------------------------------------------------------------*/
        /*---------------------散热风扇控制---------------------------------------------------*/
        if( COM_AD_Data_Info.temp_NTC_Val_Fir < COM_OPEN_FAN_TEMP_VALUE ||\
            COM_AD_Data_Info.iBat_CHG_Val_Fir >= COM_OPEN_FAN_CHG_IBAT_VALUE ||\
            COM_AD_Data_Info.iBat_DISC_Val_Fir >= COM_OPEN_FAN_DISC_IBAT_VALUE )  //逆变侧或升压侧任一个高于45℃，开启风扇
        {
            i16FAN_Close_Cnt = 0;
            if(i16FAN_Open_Cnt <= 200)  i16FAN_Open_Cnt ++;
            if(i16FAN_Open_Cnt >= 200)  FAN_ENABLE;                
        }
         if( COM_AD_Data_Info.temp_NTC_Val_Fir > COM_CLOSE_FAN_TEMP_VALUE &&\
             COM_AD_Data_Info.iBat_CHG_Val_Fir <= COM_CLOSE_FAN_CHG_IBAT_VALUE&&\
             COM_AD_Data_Info.iBat_DISC_Val_Fir <= COM_CLOSE_FAN_DISC_IBAT_VALUE)//逆变侧和升压侧都低于35℃，关闭风扇
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
Others     : LED指示灯逻辑
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
Others     : LED指示灯逻辑
*************************************************/
void User_LED_Deal(void)
{
    LED_Ctr_Info.flag_1ms = SysClockBase_ms.sys_LED_1ms;
    
/*---------------------------初始准备状态绿灯闪烁0.5HZ-------------------------------------------*/
	if ( System_ProtectFlag_Info.all == 0 &&
	     State_Context.state_Value <= COM_READY_STATE )
    {		

        LED_Ctr_Info.on_Val = 250;
        LED_Ctr_Info.period_Val = 1500;
        User_LED_ms(&LED_Ctr_Info);        

    }
/*----------------------------运行状态绿灯常亮---------------------------------------------*/
    else if ( COM_RUN_STATE == State_Context.state_Value )
    {
        LED_Ctr_Info.on_Val =1000;
        LED_Ctr_Info.period_Val = 1500;
        User_LED_ms(&LED_Ctr_Info);          
    }
               
/*-------------------------------故障状态绿灯灭 1HZ-------------------------------------*/
    else 
    {
        LED_Ctr_Info.on_Val =200;
        LED_Ctr_Info.period_Val = 400;
        switch( System_ProtectFlag_Info.all )
        {               
            case 1:  //过载  LED闪烁2次  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 2;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 2:  //母线过欠压  LED闪烁3次                  
            case 4:  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 3;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 64:  //辅助电源过欠压  LED闪烁4次                  
            case 128:  
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 4;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 256:  //过温  LED闪烁5次
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 5;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 512:  //
            case 1024:  //过流  LED闪烁6次                
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 6;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 2048:  //电池电压过欠压  LED闪烁7次
            case 4096:  //电池电压过欠压  LED闪烁7次                
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 7;
                User_LED_ms(&LED_Ctr_Info);
                break;
            case 8192:  //初始化失败  LED闪烁8次
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 8;
                User_LED_ms(&LED_Ctr_Info);
                break;                
            case 16384:  //逆变侧故障  LED闪烁9次
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 9;
                User_LED_ms(&LED_Ctr_Info);
                break;   
            case 32768:  //通信故障  LED闪烁10次
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 10;
                User_LED_ms(&LED_Ctr_Info);
                break; 
            case 32:  //VREF故障  LED闪烁11次
                if(LED_Ctr_Info.cycle_Cnt == 0)
                    LED_Ctr_Info.cycle_Val = 11;
                User_LED_ms(&LED_Ctr_Info);
                break;                
            default: //  绿灯闪10次
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
Others     : 按键功能程序逻辑处理
*************************************************/
void Key_Calc( Key_Var_t *key )
{
    /*------------------------------------------------------------------------------------*/
    if( key->in == key->ref_Active_Level )	//输入电平与设定有效电平一致
    {
        if ( key->release_Cnt > 0 )                   
        {
            key->release_Cnt--;			  
        }
        if ( key->close_Cnt < key->c_Delay_Val )  //按键闭合计数比较
        {
            key->close_Cnt++;
        }
        else
        {
              key->close_Cnt = 0;
              key->out_State = E_KEY_CLOSE;  //表示按键按下
        }
    }
    else  //输入电平与设定有效电平不一致
    {
        if ( key->close_Cnt > 0 )                    
        {
            key->close_Cnt--;			
        }
        if ( key->release_Cnt < key->r_Delay_Val )  //按键松开计数比较
        {
            key->release_Cnt++;
        }
        else
        {
              key->release_Cnt = 0;
              key->out_State = E_KEY_RELEASE;   //表示按键松开 
        }
    }
}


/*************************************************
Description: User_Key_Deal
Input      : 
Return     : 
Others     : 按键状态处理
*************************************************/
uint8_t u8_Key_SW_ShutDown_Flag = 0;
uint16_t u16_ShutDown_Start_count,u16_ShutDown_Start_count1 = 0; 
void User_Key_Deal(void)
{
  	if (SysClockBase_ms.sys_1ms == 1 )
    {  				
        //未开总开关时，插上市电自动锁住电源锁，进行充电运行
        if( COM_AD_Data_Info.auxPower_Val_Fir <= COM_START_CHECK_AUX_POWER_UP &&\
            COM_AD_Data_Info.auxPower_Val_Fir >= COM_START_CHECK_AUX_POWER_DOWN &&\
            COM_AD_Data_Info.vBat_Val_Fir <= COM_START_CHECK_VBAT_UP &&\
            COM_AD_Data_Info.vBat_Val_Fir >= COM_START_CHECK_VBAT_DOWN &&\
            POWER_LOCK_STATUS == 0 && u8_Key_SW_ShutDown_Flag == 0)
        { 
            if((++u16_ShutDown_Start_count1) >= COM_POWER_LOCK_TIME) //开机延时时间
            {
                POWER_LOCK_ENABLE;// P21输入电源保持信号 :设置为高电平表示处于开机状态
                u16_ShutDown_Start_count1 = 0;                                         
            }            
        }
        else
        {
            u16_ShutDown_Start_count1 = 0;
        }


        
        //开关机按钮	
        Key_SW_ShutDown.in = SHUT_DOWN_SWITCH;
        Key_SW_ShutDown.Calc( &Key_SW_ShutDown );
					
        //电源保持信号逻辑处理					
        if ( Key_SW_ShutDown.out_State == E_KEY_CLOSE &&  POWER_LOCK_STATUS == 0 && u8_Key_SW_ShutDown_Flag == 0 )   //&&  State_Context.State_Identifier > 2 )  	//准备状态完成后开始生效	
        {
            if((++u16_ShutDown_Start_count) >= COM_POWER_LOCK_TIME) //开机延时时间
            {
                POWER_LOCK_ENABLE;// // P21输入电源保持信号 :设置为高电平表示处于开机状态
                u16_ShutDown_Start_count = 0;                            
                u8_Key_SW_ShutDown_Flag = 1; //“0”表示按键松开，“1”表示按键未松开 
                COM_Ctr_Info.Power_OnOff_Flag =1;                
            }
        }
        else  if( Key_SW_ShutDown.out_State == E_KEY_CLOSE &&  POWER_LOCK_STATUS == 1 && u8_Key_SW_ShutDown_Flag == 0)  	                                  		
        {
            //关闭驱动

            COM_PWM_Disable(); 
            System_ProtectFlag_Info.all |= E_SYS_INIT_FAIL;
            POWER_LOCK_DISABLE; // P21输入电源保持信号 :设置为低电平表示处于关机状态
            u8_Key_SW_ShutDown_Flag = 1; //“0”表示按键松开，“1”表示按键未松开
            COM_Ctr_Info.Power_OnOff_Flag = 0;
        }

        //开关机按钮松开标志位
        if ( Key_SW_ShutDown.out_State == E_KEY_RELEASE) 	
        {
            u8_Key_SW_ShutDown_Flag = 0;   //“0”表示按键松开，“1”表示按键未松开			
        }
        
    }
}



/*************************************************
Description: COM_CHG_INV_Select
Input      : 
Return     : 
Others     : 充电或者放电功能选择
*************************************************/
void COM_CHG_INV_Select(void)
{ 
    if(SysClockBase_ms.sys_Mode_1ms == 1)    
    {                        
        //COM_Ctr_Info.INV_PFC_Mode_Select = 2;
        //市电接入判断，设定工作模式为PFC状态
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
                //重新进入初始化阶段    
              
                COM_PWM_Disable();	//关闭PWM输出、继电器            

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
                DC_Ctrl_Info.mode = 2;//检测市电正常工作模式为PFC模式
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
               
                //重新进入初始化阶段                     
                COM_PWM_Disable();	//关闭PWM输出、继电器            
                
                Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                
                State_Context.flag.bit.initial_Ok       = E_FALSE;
                State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                State_Context.flag.bit.ready_Ok         = E_FALSE;
                State_Context.state_Value               = COM_WAITING_STATE;
                CHG_Info.vBUS_Set              = 0;   //不可删除             
                DC_Ctrl_Info.INV_Ready_State = COM_INV_READY_STATE_NOK;
                COM_Ctr_Info.INV_Mode_OK_Cnt = 0;                    
                DC_Ctrl_Info.mode = 1;//默认逆变模式  
                DC_Ctrl_Info.start_Finish_State = COM_START_FINISH_STATE_NOK;

            }
        }
        else
        {
            COM_Ctr_Info.INV_Mode_OK_Cnt = 0; 
        }  


        //COM_Ctr_Info.INV_PFC_Mode_Select = 0;
        //设定工作模式为空闲状态
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
                //重新进入初始化阶段                     
                COM_PWM_Disable();	//关闭PWM输出、继电器            

                Initial_Deal.flag.bit.Initial_Ok        = E_FALSE;
                Waiting_Deal.flag.bit.Waiting_Ok        = E_FALSE;
                Ready_Deal.flag.bit.Ready_Ok            = E_FALSE;                    
                Run_Deal.flag.bit.OpenDriver_Ok         = E_FALSE;
                
                State_Context.flag.bit.initial_Ok       = E_FALSE;
                State_Context.flag.bit.waiting_Ok       = E_FALSE;                    
                State_Context.flag.bit.ready_Ok         = E_FALSE;                
                State_Context.state_Value               = COM_WAITING_STATE;
                
                CHG_Info.vBUS_Set              = 0;   //不可删除             
               
                COM_Ctr_Info.NO_Mode_OK_Cnt = 0;
                DC_Ctrl_Info.mode = 0;//工作模式空闲模式
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
Others     : 串口0数据处理
*************************************************/
int init_crc = 0;
uint8_t *UART0_RXD_B_Temp;
int32_t CHG_vBat_AD_Hold,CHG_vBat_AD_Fir = 0;
void COM_UART0_Deal(void)
{
    //电池电压AD值滤波处理，充电时使用
    CHG_vBat_AD_Hold = DFILTER_N(6,CHG_Info.vBat_AD,CHG_vBat_AD_Hold);
    CHG_vBat_AD_Fir = CHG_vBat_AD_Hold >> 16;   

    
    /*------------------------通信数据接收-----------------------------------------------------*/	
    /*---------------------8位数据转换为16位格式------------------------------------------*/
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
          
        //CRC校验码获得处理
        for(int i=0;i<(UART0_SEND_NUM-2);i++)
        {
            UART0_Info.RXD_CRC_Calc = crc16_modbus(&UART0_RXD_B_Temp[i],1,UART0_Info.RXD_CRC_Init ); 
            UART0_Info.RXD_CRC_Init = UART0_Info.RXD_CRC_Calc;          	 
        }  
        UART0_Info.RXD_CRC_Init = 0xffff;//初始化CRC寄存器初始值    
            
        //接收的CRC校验码处理
        UART0_Info.RXD_CRC_CkCd =   (UART0_RXD_B_Temp[UART0_SEND_NUM-2])+\
                                    (UART0_RXD_B_Temp[UART0_SEND_NUM-1]<<8);
    
        //计算的CRC校验码与接收的CRC校验码作比较和帧头判断(0X55AA)
        if( UART0_Info.RXD_CRC_Calc == UART0_Info.RXD_CRC_CkCd  &&\
            UART0_RXD_B_Temp[0] == 0XAA && UART0_RXD_B_Temp[1] == 0X55)
        {
            for(int i=0; i < (UART0_SEND_NUM>>1); i++)
            {
                UART0_Info.RXD_W[i] = UART0_RXD_B_Temp[2 * i] + (UART0_RXD_B_Temp[2 * i+1] << 8);			
            }
            
            /*------------------------------------------------------------------------------------*/			
            /*---------------------UART1通信心跳位逻辑--------------------------------------------*/					
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
        /*---------------------UART1通信心跳监测----------------------------------------------*/        
        COM_Uartx_HeartCheck(&UART0_Info);
    }    
    
    /*------------------------------------------------------------------------------------*/				
    /*---------------------UART1通信异常清数据--------------------------------------------*/	
    if(UART0_Info.heart_OK_Status == 0)  ////UART2接收数据通信异常时 RXD0_Status_Heart_OK心跳状态为 0
    {
        if(System_ProtectFlag_Info.all == 0 && OPERATING_MODE == NORMAL_MODE)
            System_ProtectFlag_Info.all |= E_COMMUNICA_ERR;//通信故障
        
        UART0_Info.RXD_W[0] = 0;   //2字节帧头数据 ；			
        UART0_Info.RXD_W[1] = 0;   //2：后级选择PFC工作模式；  1：后极选择INV工作模式
        UART0_Info.RXD_W[2] = 0;	//后级故障代码
        UART0_Info.RXD_W[3] = 0;	//逆变输出电压值（RMS） --注意：真实电压有效值放大10倍
        UART0_Info.RXD_W[4] = 0;	//逆变输出功率（W）  
        UART0_Info.RXD_W[5] = 0;	//注意：真实母线电压值放大10倍
        UART0_Info.RXD_W[6] = 0;	//逆变工作电源状态OK为1，状态不正常为0
        UART0_Info.RXD_W[7] = 0;	//注意：逆变输出电压频率数据是真实频率放大10倍
        UART0_Info.RXD_W[8] = 0;	//市电输入电压值（RMS）--注意：真实电压有效值放大10倍
        UART0_Info.RXD_W[9] = 0;	//市电输入PFC功率（W）----电感电流*输入电压
        UART0_Info.RXD_W[10] = 0;	//市电输入旁路功率（W）--负载电流有效值*输入电压有效值
        UART0_Info.RXD_W[11] = 0;	//注意：市电输入电压频率数据是真实频率放大10倍         
    }
        
    COM_Ctr_Info.INV_VBus_AD            = UART0_Info.RXD_W[5];
    COM_Ctr_Info.INV_PFC_Mode_Select    = UART0_Info.RXD_W[1];
    COM_Ctr_Info.INV_PFC_Ready_Status   = UART0_Info.RXD_W[6]; 
    
    
    //发送至DC侧的电压/功率/频率数据处理
    InvToDC_Data_Info.err_Code = UART0_Info.RXD_W[2];//故障码
    InvToDC_Data_Info.mode_State = UART0_Info.RXD_W[1];//工作模式：放电或者充电 
    
    //注意：向DC侧发送的VBUS母线电压数据，真实母线电压值放大10倍 
    InvToDC_Data_Info.VBusAD_Val = UART0_Info.RXD_W[5];//注意：真实母线电压值放大10倍
    
    //注意：向DC侧发送的逆变输出电压有效值数据是真实有效值放大10倍 
    InvToDC_Data_Info.VACOUT_RMS = UART0_Info.RXD_W[3];//逆变输出电压值（RMS） --注意：真实电压有效值放大10倍
    
    //注意：向DC侧发送的逆变输出电压频率数据是真实频率放大10倍 
    InvToDC_Data_Info.VACOUT_Freq = UART0_Info.RXD_W[7];//逆变输出电压频率（Hz）
    InvToDC_Data_Info.VACOUT_Power = UART0_Info.RXD_W[4];//逆变输出功率（W）
    
    //注意：向DC侧发送的市电输入电压有效值数据是真实有效值放大10倍 
    InvToDC_Data_Info.VACIN_RMS = UART0_Info.RXD_W[8];//市电输入电压值（RMS）--注意：真实电压有效值放大10倍  
    
    //注意：向DC侧发送的市电输入电压频率数据是真实频率放大10倍
    InvToDC_Data_Info.VACIN_Freq = UART0_Info.RXD_W[11];//市电输入电压频率（Hz）
    InvToDC_Data_Info.VACIN_PFC_Power = UART0_Info.RXD_W[9];//市电输入PFC功率（W）----电感电流*输入电压
    InvToDC_Data_Info.VACIN_BypassPower = UART0_Info.RXD_W[10];//市电输入旁路功率（W）--负载电流有效值*输入电压有效值


    //串口通信,DC侧数据发送至INV侧
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
Others     : 串口1数据处理
*************************************************/
uint8_t BMS_flagtest = 0;
void COM_UART1_Deal(void)
{
    //故障代码，需自行完善
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

    //DC侧发送至MC主控的数据
    //低16位为逆变侧故障代码，高16位为DC侧故障代码;可自行修改
    DcToMC_Data_Info.Flag.u32ErrCode= InvToDC_Data_Info.err_Code + (System_ProtectFlag_Info.all<<16);
    DcToMC_Data_Info.mode_State     = DC_Ctrl_Info.mode;//工作模式：放电或者充电 
    DcToMC_Data_Info.VACOUT_RMS     = InvToDC_Data_Info.VACOUT_RMS;//逆变输出电压值（RMS） --注意：真实电压有效值放大10倍 
    DcToMC_Data_Info.VACOUT_Freq    = InvToDC_Data_Info.VACOUT_Freq;//注意：向DC侧发送的逆变输出电压频率数据是真实频率放大10倍 
    DcToMC_Data_Info.VACOUT_Power   = InvToDC_Data_Info.VACOUT_Power;//逆变输出功率（W）
    DcToMC_Data_Info.VACIN_RMS      = InvToDC_Data_Info.VACIN_RMS;//市电输入电压值（RMS）--注意：真实电压有效值放大10倍    
    DcToMC_Data_Info.VACIN_Freq     = InvToDC_Data_Info.VACIN_Freq;//注意：向DC侧发送的市电输入电压频率数据是真实频率放大10倍
    DcToMC_Data_Info.VACIN_PFC_Power    = InvToDC_Data_Info.VACIN_PFC_Power;//市电输入PFC功率（W）----电感电流*输入电压
    DcToMC_Data_Info.VACIN_BypassPower  = InvToDC_Data_Info.VACIN_BypassPower;//市电输入旁路功率（W）--负载电流有效值*输入电压有效值
    
    DcToMC_Data_Info.vBat       = COM_AD_Data_Info.vBat_Val_Fir;//电池电压真实值放大倍数【COM_REAL_VBAT_SCAL】
    DcToMC_Data_Info.iBat_CHG   = COM_AD_Data_Info.iBat_CHG_Val_Fir;//电池充电电流放大倍数【COM_REAL_IBAT_CHG_SCAL】
    DcToMC_Data_Info.temp_NTC   = ADSample_Info.temp_NTC_AD_FIR;//器件温度   
    DcToMC_Data_Info.iBat_DISC  = COM_AD_Data_Info.iBat_DISC_Val_Fir;//电池放电电流放大倍数【COM_REAL_IBAT_DISC_SCAL】
    DcToMC_Data_Info.vBat_CHG_Power     = COM_AD_Data_Info.vBat_CHG_Power;//电池充电功率（W）
    DcToMC_Data_Info.vBat_DISC_Power    = COM_AD_Data_Info.vBat_DISC_Power;//电池放电功率（W）

    if( COM_RUN_STATE == State_Context.state_Value && \
        Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE  && \
        DC_Ctrl_Info.mode == DC_CHARGE&&SysClockBase_ms.sys_1ms == 1)
    {
       ////启用变化充电电流测试  BMS_Order_Info.cnt1++;
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
    
    //设定恒压值
    if(0&&BMS_Order_Info.Flag.bit.Set_CV_Flag == 1)
    {
        CHG_Info.allow_VBat_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -1.8*10) *   4096 / COM_VBAT_BASE /10;;
        CHG_Info.vBat_CV_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.3*10) *   4096 / COM_VBAT_BASE /10;//启用外部传输恒压值,放大10倍
        CHG_Info.vBat_CC_CV_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.8*10) *   4096 / COM_VBAT_BASE /10;
        CHG_Info.vBat_FC_Val = (uint32_t)(BMS_Order_Info.set_CV_Val -0.3*10) *   4096 / COM_VBAT_BASE /10;
        CHG_Info.CC2_Flag = 0;  
        BMS_Order_Info.Flag.bit.Set_CV_Flag = 0;

    }
    
    //BMS下发设定充电恒流值
    if(1&&BMS_Order_Info.Flag.bit.Set_CC_Flag == 1)   
    {
     
        CHG_Info.iBat_CC1_Val = (uint32_t)BMS_Order_Info.set_CC_Val *COM_IBAT_CHG_SCAL/10;//启用外部传输恒流值,放大10倍
        CHG_Info.iBat_CC2_Val = (uint32_t)(BMS_Order_Info.set_CC_Val - 0.5*10) *COM_IBAT_CHG_SCAL/10;
        CHG_Info.iBat_Ref_SS = CHG_Info.iBat_CC1_Val;
//        CHG_Info.CC2_Flag = 0;
        BMS_Order_Info.Flag.bit.Set_CC_Flag = 0;
        
        //限制最大充电电流
        if(CHG_Info.iBat_CC1_Val > COM_CHG_IBAT_CC1_VAL)   CHG_Info.iBat_CC1_Val = COM_CHG_IBAT_CC1_VAL; 
        if(CHG_Info.iBat_CC2_Val > COM_CHG_IBAT_CC1_VAL)   CHG_Info.iBat_CC2_Val = COM_CHG_IBAT_CC1_VAL; 
        //限制最小充电电流
        if(CHG_Info.iBat_CC1_Val < COM_CHG_IBAT_TC_VAL)   CHG_Info.iBat_CC1_Val = COM_CHG_IBAT_TC_VAL; 
        if(CHG_Info.iBat_CC2_Val < COM_CHG_IBAT_TC_VAL)   CHG_Info.iBat_CC2_Val = COM_CHG_IBAT_TC_VAL;         
    }
  
}

/*************************************************
Description: COM_UART2_Deal
Input      : 
Return     : 
Others     : 串口2数据处理
*************************************************/
void COM_UART2_Deal(void)
{
    static uint16_t u8UartDebug_Cnt1 = 0;
    
    u8UartDebug_Cnt1 ++;
    /*------------------------------------------------------------------------------------*/			
    /*---------------------UART0串口调试--------------------------------------------------*/	
    if(u8UartDebug_Cnt1 > 213)        
    {
        u8UartDebug_Cnt1 = 0;
        User_UART_View();
    }
 
}


/*************************************************
Description: COM_AD_Data_Deal
Input      : 
Return     : 
Others     : AD采样真实数据处理
*************************************************/
void COM_AD_Data_Deal(void)
{
    //读取部分AD数据
    ADSample_Info.ref_AD_FIR        = ADC2->ADDR3;  //VREF_2.5V采样  
    ADSample_Info.temp_NTC_AD_FIR   = ADC2->ADDR15;//温度采样
    ADSample_Info.auxPower_AD_FIR   = ADC2->ADDR12;//辅助电源电压采样   
    
    //AD采样真实数据处理,在真实值基础上放大设定倍数
    COM_AD_Data_Info.Sum_Cnt++;
    COM_AD_Data_Info.vRef_Sum       += ADSample_Info.ref_AD_FIR ;//基准VREF
    COM_AD_Data_Info.temp_NTC_Sum   += ADSample_Info.temp_NTC_AD_FIR;//温度     
    COM_AD_Data_Info.vBat_Sum       += ADSample_Info.vBat_AD_FIR * COM_REAL_VBAT_SCAL * COM_VBAT_BASE>>12;//电池电压     
    COM_AD_Data_Info.iBat_CHG_Sum   += ADSample_Info.iBat_CHG_AD_FIR * COM_REAL_IBAT_CHG_SCAL * COM_IBAT_CHG_BASE>>12;//电池充电电流
    COM_AD_Data_Info.iBat_DISC_Sum  += ADSample_Info.iBat_DISC_AD_FIR * COM_REAL_IBAT_DISC_SCAL * COM_IBAT_DISC_BASE>>12;//电池放电电流
    COM_AD_Data_Info.auxPower_Sum   += ADSample_Info.auxPower_AD_FIR * COM_REAL_AUXPOWER_SCAL * COM_AUX_POWER_BASE>>12;//辅助电源电压     
    if(COM_AD_Data_Info.Sum_Cnt>=1024)
    {  
        COM_AD_Data_Info.vRef_Val       = COM_AD_Data_Info.vRef_Sum>>10;
        COM_AD_Data_Info.temp_NTC_Val   = COM_AD_Data_Info.temp_NTC_Sum>>10;           
        COM_AD_Data_Info.vBat_Val       = COM_AD_Data_Info.vBat_Sum>>10;
        COM_AD_Data_Info.iBat_CHG_Val   = COM_AD_Data_Info.iBat_CHG_Sum>>10;       
        COM_AD_Data_Info.auxPower_Val   = COM_AD_Data_Info.auxPower_Sum>>10;
        COM_AD_Data_Info.iBat_DISC_Val  = COM_AD_Data_Info.iBat_DISC_Sum>>10;
        
        COM_AD_Data_Info.vRef_Hold      = DFILTER_N(4,(COM_AD_Data_Info.vRef_Val),COM_AD_Data_Info.vRef_Hold);
        COM_AD_Data_Info.vRef_Val_Fir   = COM_AD_Data_Info.vRef_Hold >> 16;//辅助电源电压          

        COM_AD_Data_Info.temp_NTC_Hold      = DFILTER_N(4,(COM_AD_Data_Info.temp_NTC_Val),COM_AD_Data_Info.temp_NTC_Hold);
        COM_AD_Data_Info.temp_NTC_Val_Fir   = COM_AD_Data_Info.temp_NTC_Hold >> 16;//辅助电源电压          
               
        COM_AD_Data_Info.auxPower_Hold      = DFILTER_N(4,(COM_AD_Data_Info.auxPower_Val),COM_AD_Data_Info.auxPower_Hold);
        COM_AD_Data_Info.auxPower_Val_Fir   = COM_AD_Data_Info.auxPower_Hold >> 16;//辅助电源电压          
        
        COM_AD_Data_Info.vBat_Hold          = DFILTER_N(4,COM_AD_Data_Info.vBat_Val,COM_AD_Data_Info.vBat_Hold);
        COM_AD_Data_Info.vBat_Val_Fir       = COM_AD_Data_Info.vBat_Hold >> 16;//电池电压  

        COM_AD_Data_Info.iBat_CHG_Hold      = DFILTER_N(5,(COM_AD_Data_Info.iBat_CHG_Val),COM_AD_Data_Info.iBat_CHG_Hold);
        COM_AD_Data_Info.iBat_CHG_Val_Fir   = COM_AD_Data_Info.iBat_CHG_Hold >> 16;//电池充电电流    

        COM_AD_Data_Info.iBat_DISC_Hold     = DFILTER_N(5,(COM_AD_Data_Info.iBat_DISC_Val),COM_AD_Data_Info.iBat_DISC_Hold);
        COM_AD_Data_Info.iBat_DISC_Val_Fir  = COM_AD_Data_Info.iBat_DISC_Hold >> 16;//电池放电电流  
      
        
        COM_AD_Data_Info.Sum_Cnt        = 0;
        COM_AD_Data_Info.vRef_Sum       = 0;
        COM_AD_Data_Info.temp_NTC_Sum   = 0;            
        COM_AD_Data_Info.vBat_Sum       = 0;        
        COM_AD_Data_Info.iBat_CHG_Sum   = 0;  
        COM_AD_Data_Info.auxPower_Sum   = 0;
        COM_AD_Data_Info.iBat_DISC_Sum  = 0;                
    }  

    COM_AD_Data_Info.vBat_CHG_Power     = COM_AD_Data_Info.vBat_Val_Fir * COM_AD_Data_Info.iBat_CHG_Val_Fir/ \
                                        (COM_REAL_VBAT_SCAL*COM_REAL_IBAT_CHG_SCAL);//电池充电功率（W）
    COM_AD_Data_Info.vBat_DISC_Power    = COM_AD_Data_Info.vBat_Val_Fir * COM_AD_Data_Info.iBat_DISC_Val_Fir/ \
                                        (COM_REAL_VBAT_SCAL*COM_REAL_IBAT_DISC_SCAL);;//电池放电功率（W）
    
}


/*************************************************
Description: COM_CHG_Data_Deal
Input      : 
Return     : 
Others     : 充电占空比缓启、电流环路缓启、充电状态处理：涓流、恒压、恒流、浮充
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
            CHG_PWM_SS();//充电控制时启机占空比缓启动
            CHG_IBAT_SS();//IBAT电流控制环路缓启动处理
            
            //充电状态处理：涓流、恒压、恒流、浮充
            CHG_State_Select();
                
            if(CHG_Info.Sec_Cnt>=CHG_Info.Sec_Val)//
            {
                CHG_Info.Sec_Cnt = 0;//秒时基计数值清零
            }              
        }                       
    } 
}
    
    
/*************************************************
Description: COM_Function
Input      : 
Return     : 
Others     : 用户任务执行
*************************************************/
uint8_t u8System1ms_Cnt = 0;
void COM_Function(void)
{
    //获取状态机的状态            
    State_Context.ContextPtr( &State_Context );                
    
    //执行状态机对应的任务
    State_Context_Task();    
    
    //故障时关闭输出 
    DC_CloseDrive(); 
    
    //LED显示处理    
    User_LED_Deal();	
    
    //按键逻辑处理
    User_Key_Deal();
    
    //风扇控制处理
    User_FAN_Deal();
       
    //串口0数据处理(与INV侧通信)
    COM_UART0_Deal();

    //串口1数据处理(与主控侧通信)
    COM_UART1_Deal();
    
    //串口2数据处理(调试)
    COM_UART2_Deal();
    
    //充电或者放电功能选择
    COM_CHG_INV_Select();  
              
    //充电状态逻辑处理(充电完成和启用充电)
    CHG_State_Deal();    
    
    //AD采样真实数据处理
    COM_AD_Data_Deal(); 
 
     //充电占空比缓启、电流环路缓启、充电状态处理：涓流、恒压、恒流、浮充
    COM_CHG_Data_Deal(); 
    
              
    if(SysClockBase_ms.sys_1ms == 1)    
    {          
        u8System1ms_Cnt ++;//
    }        
    if(u8System1ms_Cnt>=2)
    {
        SysClockBase_ms.sys_1ms = 0;//1ms 时钟标记清零
        u8System1ms_Cnt =0;//1ms时钟周期在Main函数存在的周期计数值清零
    }
           
    //逆变侧传输故障逻辑处理
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



