/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>
#include <bsp.h>
#include <bsp_flash.h>
#include <app_dtu_send.h>
#include <stdint.h>


/*******************************************************************************
* Description  :  指示灯任务，无速度信号慢闪，有速度信号快闪，定期调用（100ms）
* Author       : 2018/4/13 星期五, by redmorningcn
*******************************************************************************/
void    led_task(void)
{
    static  uint8   blinkcnt= 0;
    
    blinkcnt++;
    
    blinkcnt %= 2;                              //任意通道有信号，快闪
    
    if(blinkcnt == 0){                          //亮、灭灯
        BSP_LED_On(1);
    } else {
        BSP_LED_Off(1);
    }
}

/**************************************************************
* Description  : 初始化系统参数
* Author       : 2018/5/30 星期三, by redmorningcn
*/
void    InitCtrl(void)
{
//    Ctrl.sys.paraflg.sysflg    = 0;        //不存系统参数（sys）
//    Ctrl.sys.paraflg.califlg   = 0;        //不存修正参数（cali）
//    Ctrl.sys.sys_outtime       = 10;       //默认10个基本单位退出。 
    
    for(u8 i = 0;i <sizeof(Ctrl.ComCtrl)/sizeof(StrCOMCtrl);i++ )
    {
        Ctrl.ComCtrl[i].ConnectFlag             = 0;                    //连接标识：0，该串口无连接；1，有连接。
        Ctrl.ComCtrl[i].ConnCtrl.TimeOut        = 5;                    //连接超时时间。（超过该时间，认为连接断开）
        
        Ctrl.ComCtrl[i].ConnCtrl.Baud           = 57600;
        Ctrl.ComCtrl[i].ConnCtrl.Bits           = USART_WordLength_8b;
        Ctrl.ComCtrl[i].ConnCtrl.COM_Num        = 0x01;
        Ctrl.ComCtrl[i].ConnCtrl.Connflg        = 1;                    //默认有连接
        Ctrl.ComCtrl[i].ConnCtrl.ConnType       = RECORD_SEND_COMM;     //默认为数据发送
        Ctrl.ComCtrl[i].ConnCtrl.DataCode       = 0;
        Ctrl.ComCtrl[i].ConnCtrl.datalen        = 0;
        Ctrl.ComCtrl[i].ConnCtrl.DestAddr       = DTU_ADDR;             //DTU模块
        Ctrl.ComCtrl[i].ConnCtrl.EnableConnFlg  = 1;                    //该连接允许
        Ctrl.ComCtrl[i].ConnCtrl.ErrFlg         = 0;                    //连接正常
        Ctrl.ComCtrl[i].ConnCtrl.FrameCode      = RECORD_FRAME_CODE;    //数据通讯
        Ctrl.ComCtrl[i].ConnCtrl.FramNum        = 1;                    //序号从1开始
        Ctrl.ComCtrl[i].ConnCtrl.MB_Node        = 1;
        Ctrl.ComCtrl[i].ConnCtrl.Parity         = USART_Parity_No;      //无校验
        Ctrl.ComCtrl[i].ConnCtrl.protocol       = CSNC_PROTOCOL;        //CSNC协议 
        //Ctrl.ComCtrl[i].ConnCtrl.rec             
        Ctrl.ComCtrl[i].ConnCtrl.RecordSendFlg  = 0;                    //暂无记录发送
        Ctrl.ComCtrl[i].ConnCtrl.RecvEndFlg     = 0;                    //无数据接收
        Ctrl.ComCtrl[i].ConnCtrl.SendRecordNum  = 1;                    //记录 同步用（确认）
        Ctrl.ComCtrl[i].ConnCtrl.SourceAddr     = LKJ_MAINBOARD_ADDR;   //本机地址
        Ctrl.ComCtrl[i].ConnCtrl.Stops          = USART_StopBits_1;
        Ctrl.ComCtrl[i].ConnectTimeOut          = 5;                    //超时时间：5秒内，该串口无连接（数据接收），则串口断开。
        Ctrl.ComCtrl[i].TimeoutEn               = 0;                    //超时计数停止。（发送数据时启动）

        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.databuf  = (u8 *)&Ctrl.ComCtrl[i].Wr;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.datalen  = 0;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.destaddr = Ctrl.ComCtrl[i].ConnCtrl.DestAddr;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.framcode = Ctrl.ComCtrl[i].ConnCtrl.FrameCode;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.framnum  = Ctrl.ComCtrl[i].ConnCtrl.FramNum;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.rxtxbuf  = Ctrl.ComCtrl[i].pch->TxBuf;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.rxtxlen  = 0;
        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.sourceaddr = Ctrl.ComCtrl[i].ConnCtrl.SourceAddr;
        //Ctrl.ComCtrl[i].ConnCtrl.sCsnc.tmp      =

        Ctrl.ComCtrl[i].RxCtrl.sCsnc.databuf    = (u8 *)&Ctrl.ComCtrl[i].Rd;    
        Ctrl.ComCtrl[i].RxCtrl.sCsnc.rxtxbuf    = (u8 *)&Ctrl.ComCtrl[i].pch->RxBuf;  
        Ctrl.ComCtrl[i].RxCtrl.RecvFlg          = 0;                    //无数据接收

        Ctrl.ComCtrl[i].RxCtrl.protocol         =  CSNC_PROTOCOL;
    }
}
 
/*******************************************************************************
* Description  : 闲置任务，时间不紧迫的工作在此运行
* Author       : 2018/4/16 星期一, by redmorningcn
*******************************************************************************/
void    idle_task(void)      
{
    static  uint32  tick;
    if(Ctrl.sys.time > tick+100 ||  Ctrl.sys.time < tick) //100ms
    {
        tick = Ctrl.sys.time;                  //时间
        
        led_task();                             //指示灯控制
    }
}


typedef void (*pFunction)(void); 
pFunction Jump_To_Application; 
u32 JumpAddress;


/*******************************************************************************
 * 名    称： IAP_JumpTo()
 * 功    能： 跳转到应用程序段
 * 入口参数：
 * 出口参数： 无
 * 作　 　者： 无名沈
 * 创建日期： 2014-04-23
 * 修    改： 
 * 修改日期： 
 *******************************************************************************/
void IAP_JumpTo(u32 appAddr)
{    

    BSP_IntDisAll();        //关中断
    NVIC_DeInit();
    
    u32 ApplicationAddress = appAddr;
    if (((*( u32*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    {
        JumpAddress = *( u32*) (ApplicationAddress + 4);
        Jump_To_Application = (pFunction) JumpAddress;
        
        //__set_CONTROL(0);
        
        __set_MSP(*( u32*) ApplicationAddress);             
        __set_PSP(*( u32*) ApplicationAddress);                 //设置堆栈
        
        Jump_To_Application();
    }
}

extern  void    back_to_app(void);
/**************************************************************
* Description  : boot退出程序
将flash
* Author       : 2018/6/7 星期四, by redmorningcn
*/
void    boot_out(void)
{
    IAP_JumpTo(USER_APP_START_ADDR);

    static  u32 time;
    if(Ctrl.sys.time > time+1000 ||  Ctrl.sys.time < time)  //100ms
    {
        time = Ctrl.sys.time;
        Ctrl.sys.sys_outtime--;
        if(Ctrl.sys.sys_outtime == 0){
            
            back_to_app();                                  //将back区数据copy到APP区
            
            /**************************************************************
            * Description  : 启动看门狗，准备跳转
            * Author       : 2018/6/7 星期四, by redmorningcn
            */
            IAP_JumpTo(USER_APP_START_ADDR);
        }
    }
}



extern  void mod_bus_rx_task(void);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{

	BSP_Init();                                                 /* Initialize BSP functions                             */
    
    //IAP_JumpTo(USER_APP_START_ADDR);

	CPU_TS_TmrInit();

	/***********************************************
	* 描述： 初始化滴答定时器，即初始化系统节拍时钟。
	*/
	//sCtrl.sys.cpu_freq = 
    BSP_CPU_ClkFreq();  //时钟频率                              /* Determine SysTick reference freq.                    */
    //OS_CPU_SysTickInit(1000);                                   /*                                                      */
    
    /**************************************************************
    * Description  : 读已存修正计算参数
    * Author       : 2018/5/29 星期二, by redmorningcn
    */
    InitCtrl();
    

    while(1){
        /*******************************************************************************
        * Description  : 空闲任务，时间不敏感的的工作在此运行，每100ms运行一次
        * Author       : 2018/4/16 星期一, by redmorningcn
        *******************************************************************************/
        idle_task();
        
        /*******************************************************************************
        * Description  : 通讯任务
        * Author       : 2018/5/7 星期一, by redmorningcn
        *******************************************************************************/
        mod_bus_rx_task();
        
        /**************************************************************
        * Description  : 执行收发任务
        * Author       : 2018/6/7 星期四, by redmorningcn
        */
        void  AppTaskComm (void);
        AppTaskComm();
        
        /**************************************************************
        * Description  : bootout,下载退出程序
        * Author       : 2018/6/7 星期四, by redmorningcn
        */
        //boot_out();
        IAP_JumpTo(USER_APP_START_ADDR);

    }
}
