/*******************************************************************************
* Description  : �����ͷ�ļ�,���к�������
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

#ifndef  TASKS_H_
#define  TASKS_H_

#include <includes.h>


//osal
void  App_TaskOsalCreate(void);
void TaskInitTmr(void);
osalEvt  TaskTmrEvtProcess(osalTid task_id, osalEvt task_event);

#endif

