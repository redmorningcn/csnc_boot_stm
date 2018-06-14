/*******************************************************************************
* Description  : 串口通讯任务
* Author       : 2018/5/18 星期五, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include <includes.h>
#include <app_com_type.h>
#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_comm__c = "$Id: $";
#endif

#define APP_TASK_COMM_EN     DEF_ENABLED
#if APP_TASK_COMM_EN == DEF_ENABLED
/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* MACROS
*/
#define CYCLE_TIME_TICKS            (OS_TICKS_PER_SEC * 1)

/*******************************************************************************
* TYPEDEFS
*/

/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
* GLOBAL VARIABLES
*/
/***********************************************
* 描述： 任务控制块（TCB）
*/

/***********************************************
* 描述： 任务堆栈（STACKS）
*/

/*******************************************************************************
* LOCAL FUNCTIONS
*/

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


void    NMB_Tx( MODBUS_CH    *pch,
                CPU_INT08U   *p_reg_tbl,
                CPU_INT16U   nbr_bytes);
void    app_dtu_send(StrCOMCtrl  * DtuCom);
void    app_dtu_rec(StrCOMCtrl  * DtuCom);

/**************************************************************
* Description  : 串口收发任务
* Author       : 2018/6/7 星期四, by redmorningcn
*/
void  AppTaskComm (void)
{
    /**************************************************************
    * Description  : DTU通讯 收发
    * Author       : 2018/5/18 星期五, by redmorningcn
    */
    for(u8 i = 0; i< 4;i++){
        if(Ctrl.ComCtrl[i].RxCtrl.RecvFlg){             //接收到数据，根据接处理
            Ctrl.ComCtrl[i].RxCtrl.RecvFlg = 0;
            app_dtu_rec(&Ctrl.ComCtrl[i]);              //和DTU模块，接收部分。
        }
        
        if(Ctrl.ComCtrl[i].ConnCtrl.RecordSendFlg){     //需要发送数据。按发送处理
            Ctrl.ComCtrl[i].ConnCtrl.RecordSendFlg = 0;
            app_dtu_send(&Ctrl.ComCtrl[i]);             //和DTU模块，发送部分
        }
    }
}

/*******************************************************************************
* 				end of file
*******************************************************************************/
#endif
