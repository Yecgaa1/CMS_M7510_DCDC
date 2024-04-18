2023/03/28
1.充放电状态切换时，要保证变化周期值时，低压侧和高压侧的周期寄存器值一起更新，否则计数四路PWM起始计数点偏移，存在相位差；
优化interrupt.c中的放电和充电子程序都得同步更新低压侧和高压侧四路PWM周期值；sys_hardware_init.c中的CHG_PWM_Enable(void)和DISC_PWM_Enable(void)函数中需同时更新四路PWM周期值
【 GPT1->GTPBR10 = DC_Ctrl_Info.EPWM_Period; GPT1->GTPBR11 = DC_Ctrl_Info.EPWM_Period; GPT1->GTPBR12 = DC_Ctrl_Info.EPWM_Period; GPT1->GTPBR14 = DC_Ctrl_Info.EPWM_Period;】；


2023/04/04
1.优化通信程序，加入DMA传输，关闭串口接收中断【sys_hardware_init.c---void Sys_IE_Init(void)】，前后级单片机通信波特率修改为38400；
具体更改点：①DMA初始化【sys_hardware_init.c---void Sys_HardConfigInit(void)】；②串口接收逻辑处理优化【user_function.c---void COM_UART0_Deal(void)】；③串口发送逻辑处理优化【user_communication.c---void UART0_INV_DataSend(int32_t *tx_buf)】；
2.硬件更改：R12:0Ω；R16:510Ω


2023/04/06
1.优化interrupt.c中void gpt1_elcovf0_interrupt(void) 函数的同步整流驱动使能逻辑，只允许使能一次，即COM_Ctr_Info.PWM_Enable == 2表示SR模式驱动使能完成(第141和226行)；
2.优化interrupt.c中void SysTick_Handler(void)函数的【BOSOC_STATUS】信号监测逻辑，在任何状态时都受监测(第359行)；
3.优化user_function.c 中void DC_CloseDrive(void)函数的故障关断逻辑(第350行)，现为在任何状态时都会因故障代码进入故障态；

2023/05/04
1.部分程序放入RAM中运行，加快执行速度，节省时间；

2023/05/05
1.CHG_VBAT_OUT_MIN的值由0更改为-100，保证电流环反馈为0时能稳住电池电压；


2023/05/06
1.充电完成时，清理状态机相关的OK标志【void CHG_State_Deal(void)】；
2.中断执行时间缩短，提高了充电时的最高工作频率，即140K更改为160K；

2023/05/08
1.充电时启机电流ref步进值减小，匹配母线电压给定步进值；
2.母线电压给定参考低于COM_CHG_VBUS_REF_INIT时，防止CHG_Info.vBUS_Ref_Sum一直累加到很大的负值，否则环路调节不过来，进而环路输出达到最大值，影响控制效果【void VBUS_Calc(void)】；
3.充电状态时，启机涓流时，充电电流的ref步进缓一点，更平稳的控制启机充电电流【lib】；

2023/05/10
1.加入主控修改充电电流和充电电压逻辑程序，验证完成，lib同步优化验证【void COM_UART1_Deal(void)】；
2.CHG_Info.out_AVG_Fir计算放入充电中断中执行；

2023/05/12
1.优化充电电流纹波，工作点尽量在谐振点附近，；

2023/05/19
1.在给充电模式前需把变量CHG_Info.vBUS_Set清零；

2023/05/24
1.35-50V输入电压，充电DC侧的死区时间由0.6us修改为0.75us，可实现开通ZVS；
2.比较器滤波优化，CMP_FILTER_FCLK_32，比较器有滤波器，通过FCLK/32进行采样，硬件RC滤波由C由102uf更改为103uf；

2023/05/30
1.比较器0和1的中断使能放在开管子的时候，解决上电会误触发比较器保护问题；
2.验证看门狗功能；

2023/06/01
1.加入比较器3判断LLC过流触发硬件关闭GPT波形；

2023/06/6
1.DC和INV侧通信数据增加；DC与MC主控通信数据处理优化；
2.INV通信传输的VBUS数据为真实值的10倍；

2023/06/07
1.整理软件平台，优化部分宏定义；
2.充电电流环ref最大值限幅；

2023/06/15
1.优化放电时DC低压侧死区时间，实现ZVS；
2.优化充电时DC高压侧死区时间，实现ZVS；

2023/06/29
1.立起来的变压器和不立变压器时，充电有差异，不立变压器状态时，充电电流振荡，更改工作点至更高充电电流波形得到优化【CHG_OUT_MIN】、【CHG_OUT_MAX】，充电电流环增益降低。



