/*******************************************************************************
* Description  : OSAL任务，有ucOS调用
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/


/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <includes.h>


#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_osal__c = "$Id: $";
#endif

#define APP_TASK_OSAL_EN     DEF_ENABLED
#if APP_TASK_OSAL_EN == DEF_ENABLED
/*******************************************************************************
 * CONSTANTS
 */

/*******************************************************************************
 * MACROS
 */
#define  OSAL_CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ / 1u)
#define  OSAL_TASK_IDLE_SEM_EN      DEF_DISABLED                // 不使用信号量做为空闲退出

/*******************************************************************************
 * TYPEDEFS
 */
#if ( OSAL_EN == DEF_ENABLED )
/***********************************************
* 描述： 任务控制块（TCB）
*/
static  OS_TCB   AppTaskOsalTCB;

/***********************************************
* 描述： 任务堆栈（STACKS）
*/
static  CPU_STK  AppTaskOsalStk[ APP_TASK_OSAL_STK_SIZE ];
#endif
/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
/*******************************************************************************
 * LOCAL FUNCTIONS
 */
static  void    AppTaskOsal             (void *p_arg);
static  void    APP_OsalInit            (void);

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */


 /*******************************************************************************
 * EXTERN FUNCTIONS
 */

/*******************************************************************************/

/*******************************************************************************
 * 名    称： App_TaskOsalCreate
 * 功    能： **任务创建
 * 入口参数： 无
 * 出口参数： 无
 * 作　　者： wumingshen.
 * 创建日期： 2015-02-05
 * 修    改：
 * 修改日期：
 * 备    注： 任务创建函数需要在app.h文件中声明
 *******************************************************************************/
void  App_TaskOsalCreate(void)
{
#if ( OSAL_EN == DEF_ENABLED )
    OS_ERR  err;

    /***********************************************
    * 描述： 任务创建
    */
    OSTaskCreate((OS_TCB     *)&AppTaskOsalTCB,                 // 任务控制块  （当前文件中定义）
                 (CPU_CHAR   *)"App Task Osal",                 // 任务名称
                 (OS_TASK_PTR ) AppTaskOsal,                    // 任务函数指针（当前文件中定义）
                 (void       *) 0,                              // 任务函数参数
                 (OS_PRIO     ) APP_TASK_OSAL_PRIO,             // 任务优先级，不同任务优先级可以相同，0 < 优先级 < OS_CFG_PRIO_MAX - 2（app_cfg.h中定义）
                 (CPU_STK    *)&AppTaskOsalStk[0],              // 任务栈顶
                 (CPU_STK_SIZE) APP_TASK_OSAL_STK_SIZE / 10,    // 任务栈溢出报警值
                 (CPU_STK_SIZE) APP_TASK_OSAL_STK_SIZE,         // 任务栈大小（CPU数据宽度 * 8 * size = 4 * 8 * size(字节)）（app_cfg.h中定义）
                 (OS_MSG_QTY  ) 5u,                             // 可以发送给任务的最大消息队列数量
                 (OS_TICK     ) 0u,                             // 相同优先级任务的轮循时间（ms），0为默认
                 (void       *) 0,                              // 是一个指向它被用作一个TCB扩展用户提供的存储器位置
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK |           // 允许堆栈检查该任务
                                OS_OPT_TASK_STK_CLR),           // 创建任务时堆栈清零
                 (OS_ERR     *)&err);                           // 指向错误代码的指针，用于创建结果处理
#else
#endif
}

/*******************************************************************************
 * 名    称： osalEventInit
 * 功    能： 
 * 入口参数： 无
 * 出口参数： 无
 * 作    者： 无名沈
 * 创建日期： 2017/12/7
 * 修    改： 
 * 修改日期： 
 * 备    注： 
 *******************************************************************************/
void osalEventInit(void)
{
    /***********************************************
    * 描述： 任务初始化
    */
    APP_OsalInit();
    
    /***********************************************
    * 描述：OSAL系统初始化
    */
    osal_init_system();
    
    /***********************************************
    * 描述： OSAL创建任务
    */
    OSAL_TaskCreateHook();
    
    /***********************************************
    * 描述：OSAL任务初始化
    */
    osal_Task_init();
}

/*******************************************************************************
* 名    称： osalEventHandle
* 功    能： 
* 入口参数： 无
* 出口参数： 无
* 作    者： 无名沈
* 创建日期： 2017/12/7
* 修    改： 
* 修改日期： 
* 备    注： 
*******************************************************************************/
void osalEventHandle(void)
{
    halIntState_t   cpu_sr;
    
    do {
        static osalEvt  events;
        /***********************************************
        * 描述：用于需要系统总是查询的的事件，如：
        *       串口接收事件，按钮扫描事件等
        */
        //HAL_ProcessPoll();
        
        /***********************************************
        * 描述：查找是否有任务产生事件
        */
        TaskActive = osalNextActiveTask();
        
        /***********************************************
        * 描述：如果当前任务有事件发生
        */
        if ( TaskActive ) {
            CPU_CRITICAL_ENTER();
            events = TaskActive->events;
            
            /***********************************************
            * 描述：清除当前任务事件
            */
            TaskActive->events = 0;
            CPU_CRITICAL_EXIT();
            
            /***********************************************
            * 描述：再次检查事件是否存在
            */
            if ( events != 0 ) {
                /***********************************************
                * 描述：判断任务函数是否存在
                */
                if ( TaskActive->pfnEventProcessor ) {
                    /***********************************************
                    * 描述：执行任务处理高优先级事件并返回未处理完的事件
                    *       事件值越小，优先级越高
                    */
                    events = (TaskActive->pfnEventProcessor)( TaskActive->taskID, events );
                    
                    /***********************************************
                    * 描述：添加返回未处理完的事件到当前任务，等待下次执行
                    */
                    CPU_CRITICAL_ENTER();
                    TaskActive->events |= events;
                    CPU_CRITICAL_EXIT();
                }
            }
        }
    } while (TaskActive);                           // 等待所有任务执行完
}

/*******************************************************************************
 * 名    称： AppTaskOsal
 * 功    能： 控制任务
 * 入口参数： p_arg - 由任务创建函数传入
 * 出口参数： 无
 * 作　　者： wumingshen.
 * 创建日期： 2015-02-05
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 static void  AppTaskOsal (void *p_arg)
{    
#if ( OSAL_EN == DEF_ENABLED )
#if ( OSAL_TASK_IDLE_SEM_EN == DEF_ENABLED )
    OS_ERR          err;
    INT32U          ticks;
    static INT32S   dly     = 1;
#endif
    /***********************************************
    * 描述： 2017/12/16,无名沈：osal事件初始化
    */
    osalEventInit();
    /***********************************************
    * 描述： Task body, always written as an infinite loop.
    *        OSAL任务查询和执行
    */
    while (DEF_TRUE) {
        /***********************************************
        * 描述： 得到系统当前时间,不使用信号量，此任务将占用空闲任务
        */
#if ( OSAL_TASK_IDLE_SEM_EN == DEF_ENABLED )
        ticks = OSTimeGet(&err);        
#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
        BOOL    ret = BSP_OS_SemWait(&Osal_EvtSem, dly);
#endif
#endif
        /***********************************************
        * 描述： 2017/12/7,无名沈：osal事件处理
        */
        osalEventHandle();
        
#if ( OSAL_TASK_IDLE_SEM_EN == DEF_ENABLED )
        /***********************************************
        * 描述： 去除任务运行的时间，等到一个控制周期里剩余需要延时的时间
        */
        dly   = OSAL_CYCLE_TIME_TICKS - ( OSTimeGet(&err) - ticks );
        if ( dly  <= 0 ) {
            dly   = 1;
        }
#else 
        /***********************************************
        * 描述： 2017/12/16,无名沈：使用空闲任务
        */
#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
        void  OSIdleTaskHook (void);
        OSIdleTaskHook ();
#endif
#endif
    }
#else
#endif
}

/*******************************************************************************
 * 名    称： APP_OsalInit
 * 功    能： 任务初始化
 * 入口参数： 无
 * 出口参数： 无
 * 作　　者： wumingshen.
 * 创建日期： 2015-03-28
 * 修    改：
 * 修改日期：
 *******************************************************************************/
static void APP_OsalInit(void)
{
    /***********************************************
    * 描述： 在看门狗标志组注册本任务的看门狗标志
    */
    #if (UCOS_EN     == DEF_ENABLED)
#if OS_VERSION > 30000U
    //BSP_OS_SemCreate(&Osal_EvtSem,0, "Osal_EvtSem");     // 创建信号量
#else
    Osal_EvtSem     = OSSemCreate(0);                    // 创建信号量
#endif
#endif
}

/*******************************************************************************
 * 				end of file
 *******************************************************************************/
#endif