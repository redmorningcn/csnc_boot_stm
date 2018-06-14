/**************************************************************
* Description  : 处理板和DTU通讯
* Author       : 2018/5/23 星期三, by redmorningcn
*/
#ifndef  _APP_DTU_SEND_H_
#define  _APP_DTU_SEND_H_

#include <includes.h>
#include <app_dtu_rec.h>

#define IAP_FRAME_CODE              0x0a      /* IAP 下载帧控制字     */
#define SET_FRAME_CODE              0x02      /* SET 设置控制字       */
#define RECORD_FRAME_CODE           0x00      /* 数据记录csnc控制字    */     

#define SET_REPLY_DATA_LEN          (4+4+1)   /* 查询或设置参数，应答数据长度*/
#define IAP_REPLY_DATA_LEN          (4)       /* IAP数据升级，数据帧应答长度 */


extern  void    NMB_Tx( MODBUS_CH    *pch,
                    CPU_INT08U   *p_reg_tbl,
                    CPU_INT16U   nbr_bytes);
#endif

