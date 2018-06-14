/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                           (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : JJL
*                 EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

#define  APP_CFG_SERIAL_EN                          DEF_ENABLED
#define  APP_CFG_MODBUS_EN                          DEF_ENABLED                 /* uc/modbus 模块 启动或禁止*/
#define  APP_CFG_OSAL_EN                            DEF_ENABLED                 /* OSAL 模块 启动或禁止*/



/*
*********************************************************************************************************
*                                            TASK PRIORITIES（任务优先级）保证文档整洁，请清除无效任务定义
*********************************************************************************************************
*/
#define  MB_OS_CFG_RX_TASK_PRIO     (OS_CFG_PRIO_MAX - 14)  /* ModBus任务的优先级（没有用到ModBus则不需要关注）   */
#define  APP_TASK_START_PRIO        (OS_CFG_PRIO_MAX - 13)  /* start的任务优先级                                  */ 
#define  APP_TASK_COMM_PRIO         (OS_CFG_PRIO_MAX - 12 )  /* COM任务优先级                                     */

#define  APP_TASK_OSAL_PRIO         (OS_CFG_PRIO_MAX -  3)  /* OSAL任务优先级                                     */




/*
*********************************************************************************************************
*                                           配置任务堆栈的大小
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*                      堆栈的字节大小 = CPU数据宽度 * 8 * size = 4 * 8 * size(字节)
*                           如：APP_TASK_SAMPLE_STK_SIZE = 128u，实际为 128u * 4 = 512（字节）
*                             可以在IAR仿真中查看堆栈大小分配是否充足。
*********************************************************************************************************
*/
#define  MB_OS_CFG_RX_TASK_STK_SIZE                 512u        // ModBus任务堆栈的大小
#define  APP_TASK_START_STK_SIZE                    128u        // 给起始任务分配堆栈
#define  APP_TASK_OSAL_STK_SIZE                     512u        //OSAL任务堆栈
#define  APP_TASK_COMM_STK_SIZE                     512u        //COMM任务堆栈




/*
*********************************************************************************************************
*                                    BSP CONFIGURATION: RS-232
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL             			BSP_SER_COMM_UART_02
#define  BSP_CFG_TS_TMR_SEL                         2


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/
#if 0
#define  TRACE_LEVEL_OFF                            0
#define  TRACE_LEVEL_INFO                           1
#define  TRACE_LEVEL_DEBUG                          2
#endif

#define  APP_TRACE_LEVEL                            TRACE_LEVEL_INFO
#define  APP_TRACE                                  BSP_Ser_Printf

#define  APP_TRACE_INFO(x)            ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DEBUG(x)           ((APP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG) ? (void)(APP_TRACE x) : (void)0)




/*
*********************************************************************************************************
*                                    APP
*********************************************************************************************************
*/
/*******************************************************************************
 * 				            OSAL相关定义                                       *
 *******************************************************************************/
/*******************************************************************************
* 描述： OSAL任务优先级定义
*/
#define	OS_TASK_PRO_TMR                 OS_TASK_PRIO_HIGHEST - 0

/***************************************************
* 描述： OSAL任务ID定义
*/
#define OS_TASK_ID_TMR                  0x00

/*******************************************************************************
* 描述： OSAL事件定义
*/
/***************************************************
* 描述： OSAL事件定义：TMR任务事件(20170930 定时器会不时停止发送，控制数据量8个)
*/
//#define OS_EVT_TMR_TICKS                0X00000001
//#define OS_EVT_TMR_MTR                  0X00000002
#define OS_EVT_TMR_MSEC                 0X00000004

/*******************************************************************************
* Description  : 串口任务事件标识组
* Author       : 2018/5/18 星期五, by redmorningcn
*/
#define COMM_EVT_FLAG_MTR_RX            (0x1 << 0)	/* MTR 接收事件                 */
#define COMM_EVT_FLAG_DTU_RX            (0x1 << 1)	/* DTU 接收事件                 */
#define COMM_EVT_FLAG_TAX_RX            (0x1 << 2)	/* TAX 接收事件                 */
#define COMM_EVT_FLAG_MTR_TX            (0x1 << 3)	/* MTR 发送事件                 */
#define COMM_EVT_FLAG_DTU_TX            (0x1 << 4)	/* DTU 发送事件                 */
#define COMM_EVT_FLAG_TAX_TX            (0x1 << 5)	/* TAX 发送事件                 */

#endif
