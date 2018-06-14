/*******************************************************************************
* Description  : 备注：没有使用操作系统，采用全局变量指示是否接收完成。
* Author       : 2018/5/7 星期一, by redmorningcn
*******************************************************************************/

/*
*********************************************************************************************************
*                                               uC/MODBUS
*                                         Embedded Modbus Stack
*
*                          (c) Copyright 2004-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/Modbus is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/Modbus in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/Modbus.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     MODBUS uC/OS-II LAYER INTERFACE
*
* Filename      : mb_os.c
* Version       : V2.12
* Programmer(s) : JJL
*********************************************************************************************************
* Note(s)       :
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

//#include <mb_os.h>
#include "includes.h"
#include <app_cfg.h>
//#include <os_cfg_app.h>
#if OS_VERSION > 30000U
#include <bsp_os.h>
#endif
/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void                 MB_OS_InitMaster  (void);
static  void                 MB_OS_ExitMaster  (void);
#endif

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void                 MB_OS_InitSlave   (void);
static  void                 MB_OS_ExitSlave   (void);
static  void                 MB_OS_RxTask      (void *p_arg);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_Init()
*
* Description : This function initializes the RTOS interface.  This function creates the following:
*
*               1) A message queue to signal the reception of a packet.
*
*               2) A task that waits for packets to be received.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_OS_Init (void)
{
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
    MB_OS_InitMaster();
#endif

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
    MB_OS_InitSlave();
#endif
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          MB_OS_InitMaster()
*
* Description : This function initializes and creates the kernel objectes needed for Modbus Master
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void  MB_OS_InitMaster (void)
{

}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                          MB_OS_InitSlave()
*
* Description : This function initializes and creates the kernel objectes needed for Modbus Salve
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void  MB_OS_InitSlave (void)
{

}
#endif

/*
*********************************************************************************************************
*                                             MB_OS_Exit()
*
* Description : This function is called to terminate the RTOS interface for Modbus channels.  We delete
*               the following uC/OS-II objects:
*
*               1) An event flag group to signal the reception of a packet.
*               2) A task that waits for packets to be received.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_OS_Exit (void)
{
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
    MB_OS_ExitMaster();
#endif

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
    MB_OS_ExitSlave();
#endif
}

/*
*********************************************************************************************************
*                                          MB_OS_ExitMaster()
*
* Description : This function is called to terminate the RTOS interface for Modbus Master channels.  The
*               Following objects are deleted.
*
*               (1) An event flag group to signal the reception of a packet.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void  MB_OS_ExitMaster (void)
{
 
}
#endif

/*
*********************************************************************************************************
*                                          MB_OS_ExitSlave()
*
* Description : This function is called to terminate the RTOS interface for Modbus Salve channels.
*               The following objects are deleted.
*
*               (1) A task that waits for packets to be received.
*               (2) A message queue to signal the reception of a packet.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
void  MB_OS_ExitSlave (void)
{

}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_RxSignal()
*
* Description : This function signals the reception of a packet either from the Rx ISR(s) or the RTU timeout
*               timer(s) to indicate that a received packet needs to be processed.
*
* Argument(s) : pch     specifies the Modbus channel data structure in which a packet was received.
*
* Return(s)   : none.
*
* Caller(s)   : MB_ASCII_RxByte()
*               MB_RTU_TmrUpdate()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  MB_OS_RxSignal (MODBUS_CH *pch)
{
    /**************************************************************
    * Description  : 无操作系统。模拟产生信号量
    * Author       : 2018/6/7 星期四, by redmorningcn
    */
    for(u8 i=0;i<4;i++){
        if(Ctrl.ComCtrl[i].pch   == pch){
            Ctrl.ComCtrl[i].RxCtrl.RxSignalFlg  = 1;
        }
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_RxWait()
*
* Description : This function waits for a response from a slave.
*
* Argument(s) : pch     specifies the Modbus channel data structure to wait on.
*
*               perr    is a pointer to a variable that will receive an error code.  Possible errors are:
*
*                       MODBUS_ERR_NONE        the call was successful and a packet was received
*                       MODBUS_ERR_TIMED_OUT   a packet was not received within the specified timeout
*                       MODBUS_ERR_NOT_MASTER  the channel is not a Master
*                       MODBUS_ERR_INVALID     an invalid error was detected
*
* Caller(s)    : MBM_FCxx()  Modbus Master Functions
*
* Return(s)   : none
*********************************************************************************************************
*/

void  MB_OS_RxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr)
{

}

void  MB_OS_TxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr)
{

}

void  MB_OS_TxOver (MODBUS_CH   *pch )
{


}
/*$PAGE*/
/*
*********************************************************************************************************
*                                            MB_OS_RxTask()
*
* Description : This task is created by MB_OS_Init() and waits for signals from either the Rx ISR(s) or
*               the RTU timeout timer(s) to indicate that a packet needs to be processed.
*
* Argument(s) : p_arg       is a pointer to an optional argument that is passed by uC/OS-II to the task.
*                           This argument is not used.
*
* Caller(s)   : This is a Task.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void  MB_OS_RxTask (void *p_arg)
{
    /**************************************************************
    * Description  : 无操作系统，模拟信号操作
    * Author       : 2018/6/7 星期四, by redmorningcn
    */
    for(u8 i=0;i<4;i++){
        if(Ctrl.ComCtrl[i].RxCtrl.RxSignalFlg   == 1){
            Ctrl.ComCtrl[i].RxCtrl.RxSignalFlg  = 0;
            
            MB_RxTask(Ctrl.ComCtrl[i].pch); 
        }
    }
}
#endif

void mod_bus_rx_task(void)
{
	MB_OS_RxTask(NULL);
}



