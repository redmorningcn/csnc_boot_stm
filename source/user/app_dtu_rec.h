/**************************************************************
* Description  : ������DTUͨѶ�����ݽ��ղ���
* Author       : 2018/5/24 ������, by redmorningcn
*/

#ifndef  _APP_DTU_REC_H_
#define  _APP_DTU_REC_H_


#include <includes.h>
#include <app_dtu_send.h>

#define		CMD_TIME_SET        0x00000100			//ʱ�俨��IC/���ߣ�
#define		CMD_LOCO_SET        0x00002000			//װ������IC/���ߣ�
#define		CMD_REC_CLR			0x00080000			//��¼���㣨���ߣ�
#define		CMD_SYS_RST	        0x00100000		    //ϵͳ��λ�����ߣ�
#define		CMD_PARA_SET        0x00800000		    //д���������ߣ�
#define		CMD_PARA_GET        0x00800001		    //�����������ߣ�
#define		CMD_RECORD_GET      0x01000001		    //�����ݼ�¼�����ߣ�
#define		CMD_DETECT_SET      0x02000000		    //��������������ߣ�
#define		CMD_DETECT_GET      0x02000001		    //д������������ߣ�

#endif

