/**************************************************************
* Description  : 处理板和DTU通讯，数据接收部分
* Author       : 2018/5/24 星期四, by redmorningcn
*/

#ifndef  _APP_DTU_REC_H_
#define  _APP_DTU_REC_H_


#include <includes.h>
#include <app_dtu_send.h>

#define		CMD_TIME_SET        0x00000100			//时间卡（IC/无线）
#define		CMD_LOCO_SET        0x00002000			//装车卡（IC/无线）
#define		CMD_REC_CLR			0x00080000			//记录清零（无线）
#define		CMD_SYS_RST	        0x00100000		    //系统复位（无线）
#define		CMD_PARA_SET        0x00800000		    //写参数（无线）
#define		CMD_PARA_GET        0x00800001		    //读参数（无线）
#define		CMD_RECORD_GET      0x01000001		    //读数据记录（无线）
#define		CMD_DETECT_SET      0x02000000		    //读检测板参数（无线）
#define		CMD_DETECT_GET      0x02000001		    //写检测板参数（无线）

#endif

