/**************************************************************
* Description  : 程序升级协议
* Author       : 2018/5/25 星期五, by redmorningcn
*/
#ifndef	_IAP_PROGRAM_MCU_H
#define	_IAP_PROGRAM_MCU_H

#include <includes.h>

/**************************************************************
* Description  : 宏定义
* Author       : 2018/5/25 星期五, by redmorningcn
*/
#define IAP_START              1
#define IAP_DATA               2
#define IAP_END                3
#define IAP_ABORT              4

/**************************************************************
* Description  : IAP通讯异常信息
* Author       : 2018/5/28 星期一, by redmorningcn
*/
#define IAP_NO_ERR              0x00
#define IAP_IDX_ERR             0x01
#define IAP_CODE_ERR            0x02
#define IAP_SIZE_ERR            0x03               
#define IAP_STORE_ERR           0x04
#define IAP_END_ERR             0x05
#define IAP_TIME_ERR            0x06


//地址信息                          
#define	USER_BOOT_START_ADDR		0x08000000	
#define	USER_BOOT_PRO_SIZE			0X0800AFFF

#define	USER_APP_START_ADDR			0x08010000
#define	USER_APP_PRO_SIZE			0x08017FFE	

#define	USER_BACK_START_ADDR		0x08028000
#define	USER_BACK_PRO_SIZE			0x08017FFF	

//存放IAP参数地址
#define	IAP_PARA_START_ADDR     	0X0800D000	
#define	IAP_PARA_PRO_SIZE			0x00002FFF	


#define	IAP_DATA_BUF_LEN            (128)
#define SEC_DIV_TIMENS              (IAP_WRITE_1024/IAP_DATA_BUF_LEN)


/**************************************************************
* Description  : IAP升级参数
* Author       : 2018/5/25 星期五, by redmorningcn
*/
__packed
typedef  struct   _stcIAPPara_
{
    uint16          HwVer;          //硬件版本
    uint16          SwVer;          //软件版本
    uint32          Size;           //软件大小
    uint32          Addr;           //当前地址
    uint32          Idx;            //帧序号
    uint16          End;            //指令码 01，标示有正确的可用
    uint16          Chk;            //校验
    uint32          Crc32;          //程序校验码
    uint32          BackAddr;       //备份区地址
    uint16          IdxNbr;         //帧数
    uint16          Rec;            //预留1
    uint16          Rec1;           //预留2
    uint16          storeCrc;       //保存校验16
}stcIAPPara;

/**************************************************************
* Description  : IAP数据结构（程序升级）
* Author       : 2018/5/25 星期五, by redmorningcn
*/
typedef  struct{
    u8  code;                       //指令
    u8  sta;                        //状态
    union {
        stcIAPPara  para;           //控制参数
        struct{
            u16 idx;                //数据序号
            u8  buf[128];           //程序内容
        };
        u16         replyIdx;       //应答的帧序号
    };
}strIapdata;

#endif	/* _IAP_PROGRAM_MCU_H */
