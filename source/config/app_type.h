/*******************************************************************************
* Description  : 定义通用结构体
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include    "stm32f10x_type.h"
#include    <app_com_type.h>


/*******************************************************************************
 * TYPEDEFS
 */
/*******************************************************************************
* Description  : 系统运行参数
* Author       : 2018/3/14 星期三, by redmorningcn
*******************************************************************************/
__packed
typedef struct  
{
    uint32  id;             // 产品id       0
    uint32  num;            // 产品编号     4
    
    union{
        struct{
            u8  sysflg      :1; // 存系统参数 
            u8  califlg     :1; // 存校准参数
            u8  rev         :6; // 预留
        };
        u8  flags;
    }paraflg;
    
    u32     sys_outtime;
    u8      loadflg;        //下载完成
    uint8   buf[58];        // 预留         8
    uint32  cpu_freq;       // cpu频率      72
    uint32  time;           // 系统全局时间(系统时钟(1/72Mhz) *65536)=约1ms   76
}strSysPara;    
    
/*******************************************************************************
* Description  : 控制结构体头部（程序识别）
* Author       : 2018/5/16 星期三, by redmorningcn
*/
typedef struct { 
    u16                 Password;                       // 	2  	用于MODEBUS通讯确认密钥，默认为6237，防止非法改数据
    u32                 systime;                        //  4   系统时间
    u16   		        Rsv[5];				            //	2  	软件版本
} StrRecHeadInfo;


//产品信息:型号 + 编号
//12 bytes
__packed
typedef struct _StrProductInfo {
	u32   		        Type;			            //产品类别
	u32   		        Id;				            //产品编号	16110002
	stcLocoId		    LocoId;		                //机车信息	104(DF4B) - 1000
    u16                 HwVer;                      //硬件版本
    u16                 SwVer;                      //软件版本
    u16                 LoadingTime;                //装车时间
    u16                 LoadingStaff;               //装车人员
    u16                 RepairTime;                 //维修时间
    u16                 RepairStaff;                //维修人员
    u8                  Rsv[12];                    //预留12个
}StrProductInfo;


__packed
typedef union _Unnctrl_ {
    struct{
        
        /***************************************************
        * 描述： 系统参数：起始地址 = 000   通讯密码，软件版本，记录号，产品信息
        */ 
        StrRecHeadInfo      sHeadInfo;                      // 16
        
        /***************************************************
        * 描述：产品信息：起始地址 = 032
        */
        StrProductInfo	    sProductInfo;			        // 32
        
        strSysPara          sys;        //公共参数
        /*******************************************************************************
        * Description  : 串口控制字
        * Author       : 2018/5/16 星期三, by redmorningcn
        */
        StrCOMCtrl          ComCtrl[4];                         //串控制字
        
    };
    uint16   buf[1024];
        
}Unnctrl;

extern  Unnctrl Ctrl;      
//变量声明
extern    Unnctrl     Ctrl;


#endif                                                          /* End of  include.                       */

