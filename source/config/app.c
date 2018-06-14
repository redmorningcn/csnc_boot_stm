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
* Description  :  ָʾ���������ٶ��ź����������ٶ��źſ��������ڵ��ã�100ms��
* Author       : 2018/4/13 ������, by redmorningcn
*******************************************************************************/
void    led_task(void)
{
    static  uint8   blinkcnt= 0;
    
    blinkcnt++;
    
    blinkcnt %= 2;                              //����ͨ�����źţ�����
    
    if(blinkcnt == 0){                          //�������
        BSP_LED_On(1);
    } else {
        BSP_LED_Off(1);
    }
}

/**************************************************************
* Description  : ��ʼ��ϵͳ����
* Author       : 2018/5/30 ������, by redmorningcn
*/
void    InitCtrl(void)
{
//    Ctrl.sys.paraflg.sysflg    = 0;        //����ϵͳ������sys��
//    Ctrl.sys.paraflg.califlg   = 0;        //��������������cali��
//    Ctrl.sys.sys_outtime       = 10;       //Ĭ��10��������λ�˳��� 
    
    for(u8 i = 0;i <sizeof(Ctrl.ComCtrl)/sizeof(StrCOMCtrl);i++ )
    {
        Ctrl.ComCtrl[i].ConnectFlag             = 0;                    //���ӱ�ʶ��0���ô��������ӣ�1�������ӡ�
        Ctrl.ComCtrl[i].ConnCtrl.TimeOut        = 5;                    //���ӳ�ʱʱ�䡣��������ʱ�䣬��Ϊ���ӶϿ���
        
        Ctrl.ComCtrl[i].ConnCtrl.Baud           = 57600;
        Ctrl.ComCtrl[i].ConnCtrl.Bits           = USART_WordLength_8b;
        Ctrl.ComCtrl[i].ConnCtrl.COM_Num        = 0x01;
        Ctrl.ComCtrl[i].ConnCtrl.Connflg        = 1;                    //Ĭ��������
        Ctrl.ComCtrl[i].ConnCtrl.ConnType       = RECORD_SEND_COMM;     //Ĭ��Ϊ���ݷ���
        Ctrl.ComCtrl[i].ConnCtrl.DataCode       = 0;
        Ctrl.ComCtrl[i].ConnCtrl.datalen        = 0;
        Ctrl.ComCtrl[i].ConnCtrl.DestAddr       = DTU_ADDR;             //DTUģ��
        Ctrl.ComCtrl[i].ConnCtrl.EnableConnFlg  = 1;                    //����������
        Ctrl.ComCtrl[i].ConnCtrl.ErrFlg         = 0;                    //��������
        Ctrl.ComCtrl[i].ConnCtrl.FrameCode      = RECORD_FRAME_CODE;    //����ͨѶ
        Ctrl.ComCtrl[i].ConnCtrl.FramNum        = 1;                    //��Ŵ�1��ʼ
        Ctrl.ComCtrl[i].ConnCtrl.MB_Node        = 1;
        Ctrl.ComCtrl[i].ConnCtrl.Parity         = USART_Parity_No;      //��У��
        Ctrl.ComCtrl[i].ConnCtrl.protocol       = CSNC_PROTOCOL;        //CSNCЭ�� 
        //Ctrl.ComCtrl[i].ConnCtrl.rec             
        Ctrl.ComCtrl[i].ConnCtrl.RecordSendFlg  = 0;                    //���޼�¼����
        Ctrl.ComCtrl[i].ConnCtrl.RecvEndFlg     = 0;                    //�����ݽ���
        Ctrl.ComCtrl[i].ConnCtrl.SendRecordNum  = 1;                    //��¼ ͬ���ã�ȷ�ϣ�
        Ctrl.ComCtrl[i].ConnCtrl.SourceAddr     = LKJ_MAINBOARD_ADDR;   //������ַ
        Ctrl.ComCtrl[i].ConnCtrl.Stops          = USART_StopBits_1;
        Ctrl.ComCtrl[i].ConnectTimeOut          = 5;                    //��ʱʱ�䣺5���ڣ��ô��������ӣ����ݽ��գ����򴮿ڶϿ���
        Ctrl.ComCtrl[i].TimeoutEn               = 0;                    //��ʱ����ֹͣ������������ʱ������

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
        Ctrl.ComCtrl[i].RxCtrl.RecvFlg          = 0;                    //�����ݽ���

        Ctrl.ComCtrl[i].RxCtrl.protocol         =  CSNC_PROTOCOL;
    }
}
 
/*******************************************************************************
* Description  : ��������ʱ�䲻���ȵĹ����ڴ�����
* Author       : 2018/4/16 ����һ, by redmorningcn
*******************************************************************************/
void    idle_task(void)      
{
    static  uint32  tick;
    if(Ctrl.sys.time > tick+100 ||  Ctrl.sys.time < tick) //100ms
    {
        tick = Ctrl.sys.time;                  //ʱ��
        
        led_task();                             //ָʾ�ƿ���
    }
}


typedef void (*pFunction)(void); 
pFunction Jump_To_Application; 
u32 JumpAddress;


/*******************************************************************************
 * ��    �ƣ� IAP_JumpTo()
 * ��    �ܣ� ��ת��Ӧ�ó����
 * ��ڲ�����
 * ���ڲ����� ��
 * ���� ���ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
void IAP_JumpTo(u32 appAddr)
{    

    BSP_IntDisAll();        //���ж�
    NVIC_DeInit();
    
    u32 ApplicationAddress = appAddr;
    if (((*( u32*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    {
        JumpAddress = *( u32*) (ApplicationAddress + 4);
        Jump_To_Application = (pFunction) JumpAddress;
        
        //__set_CONTROL(0);
        
        __set_MSP(*( u32*) ApplicationAddress);             
        __set_PSP(*( u32*) ApplicationAddress);                 //���ö�ջ
        
        Jump_To_Application();
    }
}

extern  void    back_to_app(void);
/**************************************************************
* Description  : boot�˳�����
��flash
* Author       : 2018/6/7 ������, by redmorningcn
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
            
            back_to_app();                                  //��back������copy��APP��
            
            /**************************************************************
            * Description  : �������Ź���׼����ת
            * Author       : 2018/6/7 ������, by redmorningcn
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
	* ������ ��ʼ���δ�ʱ��������ʼ��ϵͳ����ʱ�ӡ�
	*/
	//sCtrl.sys.cpu_freq = 
    BSP_CPU_ClkFreq();  //ʱ��Ƶ��                              /* Determine SysTick reference freq.                    */
    //OS_CPU_SysTickInit(1000);                                   /*                                                      */
    
    /**************************************************************
    * Description  : ���Ѵ������������
    * Author       : 2018/5/29 ���ڶ�, by redmorningcn
    */
    InitCtrl();
    

    while(1){
        /*******************************************************************************
        * Description  : ��������ʱ�䲻���еĵĹ����ڴ����У�ÿ100ms����һ��
        * Author       : 2018/4/16 ����һ, by redmorningcn
        *******************************************************************************/
        idle_task();
        
        /*******************************************************************************
        * Description  : ͨѶ����
        * Author       : 2018/5/7 ����һ, by redmorningcn
        *******************************************************************************/
        mod_bus_rx_task();
        
        /**************************************************************
        * Description  : ִ���շ�����
        * Author       : 2018/6/7 ������, by redmorningcn
        */
        void  AppTaskComm (void);
        AppTaskComm();
        
        /**************************************************************
        * Description  : bootout,�����˳�����
        * Author       : 2018/6/7 ������, by redmorningcn
        */
        //boot_out();
        IAP_JumpTo(USER_APP_START_ADDR);

    }
}
