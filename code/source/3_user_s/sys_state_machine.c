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
#include "user_function.h"
/***************************************************************************/


_State_Context_t       State_Context = STATE_CONTEXT_DEFAULTS;
_Initial_Deal_t        Initial_Deal  = INITIAL_DEAL_DEFAULTS;
_Waiting_Deal_t        Waiting_Deal  = WAITING_DEAL_DEFAULTS;
_Ready_Deal_t          Ready_Deal    = READY_DEAL_DEFAULTS;
_Run_Deal_t            Run_Deal      = RUN_DEAL_DEFAULTS;
_Fault_Deal_t          Fault_Deal    = FAULT_DEAL_DEFAULTS;
_Stop_Deal_t           Stop_Deal     = STOP_DEAL_DEFAULTS;


/*************************************************
Description: Initial_Deal_Func
Input      : 
Return     : 
Others     : 初始态功能函数
*************************************************/
void Initial_Deal_Func(_Initial_Deal_t *Initial_Handle)
{
	//Initial_Handle->SwInit_FuncPtr(&Initial_Handle);
	Waiting_Deal.delay_Count            = 0;
	Ready_Deal.delay_Count              = 0;
	Initial_Handle->flag.bit.Initial_Ok = E_TRUE;
}


/*************************************************
Description: Waiting_Deal_Func
Input      : 
Return     : 
Others     : 等待态功能函数
*************************************************/
void Waiting_Deal_Func( _Waiting_Deal_t *Waiting_Handle )
{
    if ( 1 == SysClockBase_ms.sys_1ms )	 
    {
        Waiting_Handle->delay_Count++;
        if ( Waiting_Handle->delay_Count > Waiting_Handle->delay_Value )
        {
            Waiting_Handle->delay_Count = Waiting_Handle->delay_Value;
        }
    }

    if ( Waiting_Handle->delay_Count >= Waiting_Handle->delay_Value )
    {
        Ready_Deal.delay_Count = 0;
        Waiting_Handle->flag.bit.Waiting_Ok = E_TRUE;
    }
}


/*************************************************
Description: Ready_Deal_Func
Input      : 
Return     : 
Others     : 准备态功能函数
*************************************************/
void Ready_Deal_Func(_Ready_Deal_t *Ready_Handle)
{
    Ready_Handle->Rdy_Check_FuncPtr(&Ready_Handle);
}

/*************************************************
Description: Ready_State_Check
Input      : 
Return     : 
Others     : 准备态自检功能函数
*************************************************/
void Ready_State_Check(void)
{
    if ( SysClockBase_ms.sys_1ms == 1 )	 
    {
        Ready_Deal.delay_Count++;
        if( Ready_Deal.delay_Count > Ready_Deal.delay_Value_Max )
        {
            Ready_Deal.delay_Count = Ready_Deal.delay_Value_Max;
        }
        COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_StartCheck_AuxPower_Up   , &StartCheck_Flag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.auxPower_Val_Fir , &COM_StartCheck_AuxPower_Down , &StartCheck_Flag_Info.all );			  	
        COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir     , &COM_StartCheck_VBAT_Up       , &StartCheck_Flag_Info.all );
        COM_Get_Protect_Flag( COM_AD_Data_Info.vBat_Val_Fir     , &COM_StartCheck_VBAT_Down     , &StartCheck_Flag_Info.all );			  	
        COM_Get_Protect_Flag( COM_AD_Data_Info.temp_NTC_Val_Fir , &COM_StartCheck_Temp_Up       , &StartCheck_Flag_Info.all );

    }
    //---------------------------------------------------------------------------------------------

    
    if (( E_TRUE == StartCheck_Flag_Info.bit.auxPower_High_OK       ) && \
        ( E_TRUE == StartCheck_Flag_Info.bit.auxPower_Low_OK        ) && \
        ( E_TRUE == StartCheck_Flag_Info.bit.vBAT_High_OK           ) && \
        ( E_TRUE == StartCheck_Flag_Info.bit.temp_High_OK           ) && \
        ( E_TRUE == StartCheck_Flag_Info.bit.vBAT_Low_OK            ) &&\
        ( E_TRUE == AD_Correct_Vref.Flag.bit.ADRef_Correct_Ok) )
    {        
        //放电模式
        if( ( E_TRUE == AD_Correct_DISC_IBat.Flag.bit.ADRef_Correct_Ok  ) &&\
            ( DC_Ctrl_Info.mode   == DC_DISCHARGE ) &&\
            ( INV_WORK_STATE        == 0) )
        {
            System_ProtectFlag_Info.all                 &= ~E_SYS_INIT_FAIL;            
            Ready_Deal.flag.bit.Ready_Ok                = E_TRUE;
            Ready_Deal.delay_Count                      = 0;          
        }
        
        //充电模式
        if( ( E_TRUE == AD_Correct_CHG_IBat.Flag.bit.ADRef_Correct_Ok ) &&\
            ( DC_Ctrl_Info.mode   == DC_CHARGE ) &&\
            ( INV_WORK_STATE        == 1) &&\
            ( CHG_Info.finish_State == COM_CHG_FINISH_NOK) &&\
            ( COM_Ctr_Info.INV_PFC_Mode_Select == 2))
        {
            System_ProtectFlag_Info.all                 &= ~E_SYS_INIT_FAIL;            
            Ready_Deal.flag.bit.Ready_Ok                = E_TRUE;
            Ready_Deal.delay_Count                      = 0;	            
        }
    }
    else
    {
        if ( Ready_Deal.delay_Count >= Ready_Deal.delay_Value_Max )//判断是否自检不通过
        {
            Ready_Deal.flag.bit.Ready_Ok                = E_FAIL;//准备态自检失败
            Ready_Deal.delay_Count       = 0;
            
            if(System_ProtectFlag_Info.all == 0)
                System_ProtectFlag_Info.all             |= E_SYS_INIT_FAIL;//初始化失败标记
        }
    }
}

/*************************************************
Description: Run_State_OpenDriver
Input      : 
Return     : 
Others     : 运行态开驱动功能函数
*************************************************/
void Run_State_OpenDriver(void)
{
    //等待模式确认
    if( DC_Ctrl_Info.mode == DC_CHARGE && \
        CHG_Info.finish_State == COM_CHG_FINISH_NOK&&\
        DC_Ctrl_Info.INV_Ready_State == COM_INV_READY_STATE_OK)//充电模式
    {   
        //工作变量初始化
        Run_VariableInit();        
        CHG_PWM_Enable();
        Run_Deal.flag.bit.OpenDriver_Ok = E_TRUE;                 
    }
    else if(DC_Ctrl_Info.mode == DC_DISCHARGE)//放电模式
    {       
        //工作变量初始化
        Run_VariableInit();
        DISC_PWM_Enable();

        
        Run_Deal.flag.bit.OpenDriver_Ok = E_TRUE; 
    } 
}

/*************************************************
Description: Run_Deal_Func
Input      : 
Return     : 
Others     : 运行态功能函数
*************************************************/
void Run_Deal_Func( _Run_Deal_t *Run_Handle )
{

	  if ( E_FALSE == Run_Handle->flag.bit.OpenDriver_Ok )
	  {
		    Run_Handle->OpenDriver_FuncPtr(&Run_Handle);

	  }

	  Run_Handle->FaultStateCheck_FuncPtr(&Run_Handle);
	  Run_Handle->FaultStateDeal_FuncPtr(&Run_Handle);
}
/*************************************************
Description: Fault_Deal_Func
Input      : 
Return     : 
Others     : 故障态功能函数
*************************************************/
void Fault_Deal_Func(_Fault_Deal_t *Fault_Handle)
{
	Fault_Handle->FaultStateCheck_FuncPtr(&Fault_Handle);
	Fault_Handle->FaultRelease_FuncPtr(&Fault_Handle);
}


/*************************************************
Description: Stop_Deal_Func
Input      : 
Return     : 
Others     : 停止态功能函数
*************************************************/
void Stop_Deal_Func(_Stop_Deal_t *Stop_Handle)
{
}


/*************************************************
Description: State_Context_Func
Input      : 
Return     : 
Others     : 状态机逻辑判断函数
*************************************************/
void State_Context_Func( _State_Context_t *State_Context_Handle )
{
    switch( State_Context_Handle->state_Value )
    {
       case COM_INITIAL_STATE:
    	   if ( E_TRUE == State_Context_Handle->flag.bit.initial_Ok )
       	   {
       	      State_Context_Handle->state_Value = COM_WAITING_STATE;
       	   }
       break;
/*----------------------------------------------------------------------------------*/
       case COM_WAITING_STATE:
           State_Context_Handle->flag.bit.initial_Ok = E_FALSE;
           if ( E_TRUE == State_Context_Handle->flag.bit.waiting_Ok )
       	   {
           	  State_Context_Handle->state_Value = COM_READY_STATE;
           	  State_Context_Handle->flag.bit.waiting_Ok = E_FALSE;
       	   }
       break;
/*----------------------------------------------------------------------------------*/
       case COM_READY_STATE:
           State_Context_Handle->flag.bit.waiting_Ok = E_FALSE;
           if ( E_TRUE == State_Context_Handle->flag.bit.stop_Instruction )
           {
              State_Context_Handle->state_Value = COM_STOP_STATE;
           }
       	   else if ( E_TRUE == State_Context_Handle->flag.bit.ready_Ok )
       	   {
       	      State_Context_Handle->state_Value = COM_RUN_STATE;
       	   }
       	   else  if ( E_FAIL == State_Context_Handle->flag.bit.ready_Ok )
       	   {
       	      State_Context_Handle->state_Value = COM_FAULT_STATE;
       	   }
       break;
/*----------------------------------------------------------------------------------*/
       case COM_RUN_STATE:
    	   State_Context_Handle->flag.bit.ready_Ok = E_FALSE;
    	   if ( E_TRUE == State_Context_Handle->flag.bit.stop_Instruction )
           {
              State_Context_Handle->state_Value = COM_STOP_STATE;
           }
     	   else if ( E_TRUE == State_Context_Handle->flag.bit.fault_Occur )
     	   {
     	      State_Context_Handle->state_Value = COM_FAULT_STATE;
     	   }
       break;
/*----------------------------------------------------------------------------------*/
       case COM_FAULT_STATE:
    	   State_Context_Handle->flag.bit.ready_Ok = E_FALSE;
    	   if ( E_TRUE == State_Context_Handle->flag.bit.stop_Instruction )
           {
              State_Context_Handle->state_Value = COM_STOP_STATE;
           }
   	       else if ( E_TRUE == State_Context_Handle->flag.bit.fault_Release )
   	       {
   	          State_Context_Handle->state_Value = COM_WAITING_STATE;
   	          State_Context_Handle->flag.bit.fault_Occur = E_FALSE;
   	          State_Context_Handle->flag.bit.fault_Release = E_FALSE;
   	       }
       break;
/*----------------------------------------------------------------------------------*/
       case COM_STOP_STATE:
    	   State_Context_Handle->flag.bit.ready_Ok = E_FALSE;
    	   State_Context_Handle->flag.bit.waiting_Ok = E_FALSE;
       break;
/*----------------------------------------------------------------------------------*/
       default:
       break;

    }
}  


/*************************************************
Description: State_Context_Task
Input      : 
Return     : 
Others     : 执行系统状态机对应的任务
*************************************************/
void State_Context_Task(void)
{
    switch( State_Context.state_Value )
    {     
        /*---------------------------------------初始态-----------------------------------*/ 
        case COM_INITIAL_STATE:
            //Initial_Deal.SwInit_FuncPtr = &Sys_VariableInit;
            
            State_Context.FuncPtr[COM_INITIAL_STATE]( &Initial_Deal );
            State_Context.flag.bit.initial_Ok = Initial_Deal.flag.bit.Initial_Ok;
        break;
        /*---------------------------------------等待态-----------------------------------*/
        case COM_WAITING_STATE:
            if(POWER_LOCK_STATUS == 1)//电源锁住后开始等待态的状态机执行
            {
                State_Context.FuncPtr[COM_WAITING_STATE]( &Waiting_Deal );
                State_Context.flag.bit.waiting_Ok = Waiting_Deal.flag.bit.Waiting_Ok;
            }
        break;
        /*---------------------------------------准备态-----------------------------------*/
        case COM_READY_STATE:
            Waiting_Deal.flag.bit.Waiting_Ok = E_FALSE;
            if(DC_Ctrl_Info.mode == DC_CHARGE)//充电模式
            {
                #if OPERATING_MODE == NORMAL_MODE
                        State_Context.FuncPtr[COM_READY_STATE]( &Ready_Deal );
                        State_Context.flag.bit.ready_Ok = Ready_Deal.flag.bit.Ready_Ok;						        
                #else
                        State_Context.flag.bit.ready_Ok = E_TRUE;
                #endif
                
            }
            else            //放电模式   
            {
                #if OPERATING_MODE == NORMAL_MODE
                        State_Context.FuncPtr[COM_READY_STATE]( &Ready_Deal );
                        State_Context.flag.bit.ready_Ok = Ready_Deal.flag.bit.Ready_Ok;						        
                #else
                        State_Context.flag.bit.ready_Ok = E_TRUE;
                #endif              
            }

        break;
        /*---------------------------------------运行态-----------------------------------*/
        case COM_RUN_STATE:
            State_Context.FuncPtr[COM_RUN_STATE]( &Run_Deal );
        break;
        /*---------------------------------------故障态-----------------------------------*/
        case COM_FAULT_STATE:
            State_Context.FuncPtr[COM_FAULT_STATE]( &Fault_Deal );
            Run_Deal.flag.bit.OpenDriver_Ok    = E_FALSE;
        break;
        /*---------------------------------------停止态-----------------------------------*/
        case COM_STOP_STATE:
            COM_PWM_Disable();   
      
            State_Context.FuncPtr[COM_STOP_STATE]( &Stop_Deal );
        break;
        /*--------------------------------------------------------------------------------*/
        default:  
            COM_PWM_Disable();   
        
        break;

    }

}
