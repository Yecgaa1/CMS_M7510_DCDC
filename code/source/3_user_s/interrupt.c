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
#include "sys_mcu_header.h"
#include "sys_define_param.h"
#include "user_function.h"
#include "sys_state_machine.h"
#include "base_type.h"


/*************************************************
Description: tmm1_interrupt
Input      : 
Return     : 
Others     : 
*************************************************/
uint8_t u8UartDebug_Cnt2 = 0;
void gpt1_elcovf0_interrupt(void)  
{   
    //发生来自 GPT 的输出禁用请求
    if(PGI->POEGGA &(1<<1)||PGI->POEGGA &(1<<0)||PGI->POEGGA &(1<<2))
    {
        System_ProtectFlag_Info.bit.iBAT_CHG_OCP = 1; 
        COM_PWM_Disable();
        State_Context.state_Value = COM_FAULT_STATE;          
    }

    
    //AD采样处理（参与环路控制的采样放在中断读取）
    COM_SampleAD_Deal();
    
    /*------------------------------------------------------------------------------------*/				
    /*---------------------控制算法执行及占空比更新---------------------------------------*/	
    if( COM_RUN_STATE == State_Context.state_Value && Run_Deal.flag.bit.OpenDriver_Ok == E_TRUE)
    {          
        CHG_PID_VBat.ref = CHG_Info.vBat_Ref_SS;         
        CHG_PID_VBat.fdb = CHG_Info.vBat_AD;
        CHG_PID_IBat.fdb = CHG_Info.iBat_CHG_AD;
               
        if(DC_Ctrl_Info.mode == DC_CHARGE)//充电模式
        {  

            CHG_Info.out_Sum_Cnt++;
            CHG_Info.out_Sum+=CHG_Info.out;
            
            if(CHG_Info.out_Sum_Cnt>=2048)
            {            
                CHG_Info.out_Sum_Cnt=0;
                CHG_Info.out_AVG = CHG_Info.out_Sum>>11;
                CHG_Info.out_AVG_Hold = DFILTER(4,CHG_Info.out_AVG,CHG_Info.out_AVG_Hold);
                CHG_Info.out_AVG_Fir = CHG_Info.out_AVG_Hold >> 16;              
                CHG_Info.out_Sum = 0;
            }
            
            CHG_Info.Sec_Cnt++;//秒时基计数值             
            
            #if OPERATING_MODE == TEST_MODE//测试发波波形
            
            #else
                //充电控制
                if( CHG_Info.finish_State == COM_CHG_FINISH_NOK&&\
                    (DC_Ctrl_Info.INV_Ready_State == COM_INV_READY_STATE_OK||\
                    DC_Ctrl_Info.mode_Operate == DEBUG_MODE))
                {        
                    DC_CHG_Ctrl();
                }  
            #endif

            if(DC_Ctrl_Info.EPWM_Duty <= DC_Ctrl_Info.EPWM_Duty_Min)//运行时限制最小占空比
            {
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Min;   
            }

            
            if(DC_Ctrl_Info.EPWM_DutyB < SR_MIN_TIME)//运行时限制最小占空比
            {
                DC_Ctrl_Info.EPWM_DutyB = SR_MIN_TIME;   
            }   
            if(DC_Ctrl_Info.EPWM_DutyB > CHG_FR_PERIOD_HALF)//运行时限制最大占空比为谐振频率周期值
            {
                DC_Ctrl_Info.EPWM_DutyB = CHG_FR_PERIOD_HALF;   
            }            
      
            //周期值更新
            GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
            
            GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//采样触发点设定    
            
            //占空比更新,Duty不能小于1
            GPT1->GTCCRC12 = 0;	
            GPT1->GTCCRD12 = DC_Ctrl_Info.EPWM_Duty;
            GPT1->GTCCRE12 = (DC_Ctrl_Info.EPWM_Period>>1);	
            GPT1->GTCCRF12 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
                
            GPT1->GTCCRC14 = 0;	
            GPT1->GTCCRD14 = DC_Ctrl_Info.EPWM_Duty;
            GPT1->GTCCRE14 = (DC_Ctrl_Info.EPWM_Period>>1);	
            GPT1->GTCCRF14 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
            
            GPT1->GTCCRC10 = DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRD10 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            GPT1->GTCCRE10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRF10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
                
            GPT1->GTCCRC11 = DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRD11 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            GPT1->GTCCRE11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRF11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            
            if(COM_Ctr_Info.PWM_Enable == 0)
            {
                //打开充电状态时PWM口(高压侧管子使能)                
                GPT1->GTUDDTYC12 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比 
                GPT1->GTUDDTYC14 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比
                
                COM_Ctr_Info.PWM_Enable = 1;
                
                /* Enable ACMP1_INT (0：优先级最高; 7:优先级最低)*/
                NVIC_ClearPendingIRQ(CMP1_IRQn);     /* clear INTCMP1 interrupt flag */     
                #if 1
                    CMP1->COMPOCR |=CMP_INT_Enable;//允许中断		 //允许比较器1的中断请求	
                    NVIC_SetPriority(CMP1_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
                    NVIC_EnableIRQ(CMP1_IRQn);          /* enable INTCMP1 interrupt */    
                #else
                    NVIC_DisableIRQ(CMP1_IRQn);    /* clear INTCMP1 interrupt flag */       
                #endif                 
            }
            if(DC_Ctrl_Info.CHG_SR_State==SR_ENABLE)//低压侧管子使能，做同步整流管
            {               
                if( DC_Ctrl_Info.EPWM_Duty>SR_MIN_TIME && COM_Ctr_Info.PWM_Enable==1)
                {
                    COM_Ctr_Info.PWM_Enable = 2;
                    GPT1->GTUDDTYC10 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比 
                    GPT1->GTUDDTYC11 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比                   
                }
                else if( DC_Ctrl_Info.EPWM_Duty<=SR_MIN_TIME )
                {
                    GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空                                
                }     
            } 
            else    
            {
                GPT1->GTUDDTYC10 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC11 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC10 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC11 |= 0x02020000;//GTIOCA、B 引脚输出占空                             
            }           
        }
        else//放电模式
        {    
            //放电控制
            DC_DISC_Ctrl();  
            if(DC_Ctrl_Info.start_Finish_State == COM_START_FINISH_STATE_OK) //表示缓启动升压完成                  
            {
                BAT_START_ENABLE;   
            }                    
            //限制上下限占空比
            if(DC_Ctrl_Info.EPWM_Duty > DC_Ctrl_Info.EPWM_Duty_Max)//限制最大占空比
            {
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Max;  
            }        
            if(DC_Ctrl_Info.EPWM_Duty <= DC_Ctrl_Info.EPWM_Duty_Min)//运行时限制最小占空比
            {
                DC_Ctrl_Info.EPWM_Duty = DC_Ctrl_Info.EPWM_Duty_Min;   
            }    
            
            DC_Ctrl_Info.EPWM_DutyB = DC_Ctrl_Info.EPWM_Duty;//同步整流占空比
            if(DC_Ctrl_Info.EPWM_DutyB <= SR_MIN_TIME)//运行时限制最小占空比
            {
                DC_Ctrl_Info.EPWM_DutyB = SR_MIN_TIME;   
            }  
            
            if(DC_Ctrl_Info.EPWM_DutyB > CHG_FR_PERIOD_HALF)//运行时限制最大占空比为谐振频率周期值一半
            {
                DC_Ctrl_Info.EPWM_DutyB = CHG_FR_PERIOD_HALF;   
            }              
              
            
            //周期值更新
            GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;
            GPT1->GTPBR13 = DC_Ctrl_Info.EPWM_Period;
            
            GPT1->GTCCRC13 = DC_Ctrl_Info.EPWM_Period>>1;//采样触发点设定
            //占空比更新,Duty不能小于1
            GPT1->GTCCRC10 = 0;	
            GPT1->GTCCRD10 = DC_Ctrl_Info.EPWM_Duty;
            GPT1->GTCCRE10 = (DC_Ctrl_Info.EPWM_Period>>1);	
            GPT1->GTCCRF10 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;
            
            GPT1->GTCCRC11 = 0;	
            GPT1->GTCCRD11 = DC_Ctrl_Info.EPWM_Duty;
            GPT1->GTCCRE11 = (DC_Ctrl_Info.EPWM_Period>>1);	
            GPT1->GTCCRF11 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_Duty;

            GPT1->GTCCRC12 = DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRD12 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            GPT1->GTCCRE12 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRF12 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
                
            GPT1->GTCCRC14 = DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRD14 = DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;
            GPT1->GTCCRE14 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.SR_ON_LTime;	
            GPT1->GTCCRF14 = (DC_Ctrl_Info.EPWM_Period>>1)+DC_Ctrl_Info.EPWM_DutyB-DC_Ctrl_Info.SR_OFF_ATime;


            if(COM_Ctr_Info.PWM_Enable == 0)
            { 
                GPT1->GTUDDTYC10 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比 
                GPT1->GTUDDTYC11 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比
                COM_Ctr_Info.PWM_Enable = 1;     

                /* Enable ACMP0_INT (0：优先级最高; 7:优先级最低)*/
                NVIC_ClearPendingIRQ(CMP0_IRQn);     /* clear INTCMP0 interrupt flag */ 
                #if 1
                    CMP0->COMPOCR |=CMP_INT_Enable;//允许中断		 //允许比较器0的中断请求	
                    NVIC_EnableIRQ(CMP0_IRQn);      /* enable INTCMP0 interrupt */    
                    NVIC_SetPriority(CMP0_IRQn, 2); /* Set higher priority to execute slave ISR firstly */
                #else
                    NVIC_DisableIRQ(CMP0_IRQn);    /* clear INTCMP0 interrupt flag */       
                #endif                
            }
            
            if (DC_Ctrl_Info.DISC_SR_State==SR_ENABLE)  //高压侧管子使能，做同步整流管
            {
                if( DC_Ctrl_Info.EPWM_Duty>SR_MIN_TIME&&COM_Ctr_Info.PWM_Enable==1)
                {
                    GPT1->GTUDDTYC12 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比 
                    GPT1->GTUDDTYC14 &= ~0x02020000; // 比较匹配确定GTIOCA、B引脚输出的占空比                    
                    COM_Ctr_Info.PWM_Enable = 2;
                }
                else if(DC_Ctrl_Info.EPWM_Duty<=SR_MIN_TIME)
                {
                    GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
                    GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空                    
                }           
            }
            else   
            {
                GPT1->GTUDDTYC12 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC14 &= ~0x01010000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC12 |= 0x02020000;//GTIOCA、B 引脚输出占空比 0%
                GPT1->GTUDDTYC14 |= 0x02020000;//GTIOCA、B 引脚输出占空                                                    
            }
            
        }            
    }
    
//      u8UartDebug_Cnt2++;
//        if(u8UartDebug_Cnt2 > 13)        
//        {
//            u8UartDebug_Cnt2 = 0;
//            User_UART_View();
//        }    
}

/*************************************************
Description: cmp0_interrupt
Input      : 
Return     : 
Others     : 比较器0中断服务函数（放电过流时进中断关闭PWM引脚）
*************************************************/
void cmp0_interrupt(void)
{
    System_ProtectFlag_Info.all = 1111; 
    System_ProtectFlag_Info.bit.iBAT_DISC_OCP = 1;     
    COM_PWM_Disable();

    State_Context.state_Value = COM_FAULT_STATE;     
}

/*************************************************
Description: cmp1_interrupt
Input      : 
Return     : 
Others     : 比较器1中断服务函数（充电过流时进中断关闭PWM引脚）
*************************************************/
void cmp1_interrupt(void)
{
    System_ProtectFlag_Info.all = 2222; 
    System_ProtectFlag_Info.bit.iBAT_CHG_OCP = 1;     
    COM_PWM_Disable();

    State_Context.state_Value = COM_FAULT_STATE;   
}


/*************************************************
Description: SysTick_Handler
Input      : 
Return     : 
Others     : 系统定时器中断服务函数
*************************************************/
int count_err = 0;
void SysTick_Handler(void)
{
    if(UART0_Info.TXD_Period_Cnt<=UART0_SEND_PERIOD_VAL)
        UART0_Info.TXD_Period_Cnt++;

    //逆变侧传输故障逻辑处理
    if( UART0_Info.RXD_W[2] <= 32768 &&UART0_Info.RXD_W[2] > 0 &&\
        System_ProtectFlag_Info.all == 0 &&\
        OPERATING_MODE == NORMAL_MODE  )
    {
        count_err++;
    }  
    else if(count_err > 0 )
    {
        count_err --;
    }
    //逆变侧传输故障逻辑处理
    if( ((BOSOC_STATUS == 0&&E_TRUE == StartCheck_Flag_Info.bit.auxPower_Low_OK) || count_err > 20)&&\
        System_ProtectFlag_Info.all == 0 &&\
        OPERATING_MODE == NORMAL_MODE  )
    {
        if(COM_Ctr_Info.INV_ERR_CODE ==0)
            COM_Ctr_Info.INV_ERR_CODE = UART0_Info.RXD_W[2];       
        System_ProtectFlag_Info.all |= E_INV_ERR;
    }

    
    SysClockBase_ms.sys_1ms         = 1;  
    SysClockBase_ms.sys_LED_1ms     = 1;
    SysClockBase_ms.sys_Mode_1ms    = 1;    
    SysClockBase_ms.sys_Check_1ms   = 1;	        
        
}


/*************************************************
Description: uart0_interrupt_receive
Input      : 
Return     : 
Others     : uart0接收中断：逆变器数据接收
*************************************************/
void uart0_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;


    NVIC_ClearPendingIRQ(SR0_IRQn);    
}



/*************************************************
Description: uart2_interrupt_receive
Input      : 
Return     : 
Others     : 上位机通信：uart1接收中断
*************************************************/
void uart2_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
}
