/*******************************************************************************
* Description  : ����ͨ�ýṹ��
* Author       : 2018/5/10 ������, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include    "stm32f10x_type.h"
#include    <app_com_type.h>


/*******************************************************************************
 * TYPEDEFS
 */
/*******************************************************************************
* Description  : ϵͳ���в���
* Author       : 2018/3/14 ������, by redmorningcn
*******************************************************************************/
__packed
typedef struct  
{
    uint32  id;             // ��Ʒid       0
    uint32  num;            // ��Ʒ���     4
    
    union{
        struct{
            u8  sysflg      :1; // ��ϵͳ���� 
            u8  califlg     :1; // ��У׼����
            u8  rev         :6; // Ԥ��
        };
        u8  flags;
    }paraflg;
    
    u32     sys_outtime;
    u8      loadflg;        //�������
    uint8   buf[58];        // Ԥ��         8
    uint32  cpu_freq;       // cpuƵ��      72
    uint32  time;           // ϵͳȫ��ʱ��(ϵͳʱ��(1/72Mhz) *65536)=Լ1ms   76
}strSysPara;    
    
/*******************************************************************************
* Description  : ���ƽṹ��ͷ��������ʶ��
* Author       : 2018/5/16 ������, by redmorningcn
*/
typedef struct { 
    u16                 Password;                       // 	2  	����MODEBUSͨѶȷ����Կ��Ĭ��Ϊ6237����ֹ�Ƿ�������
    u32                 systime;                        //  4   ϵͳʱ��
    u16   		        Rsv[5];				            //	2  	����汾
} StrRecHeadInfo;


//��Ʒ��Ϣ:�ͺ� + ���
//12 bytes
__packed
typedef struct _StrProductInfo {
	u32   		        Type;			            //��Ʒ���
	u32   		        Id;				            //��Ʒ���	16110002
	stcLocoId		    LocoId;		                //������Ϣ	104(DF4B) - 1000
    u16                 HwVer;                      //Ӳ���汾
    u16                 SwVer;                      //����汾
    u16                 LoadingTime;                //װ��ʱ��
    u16                 LoadingStaff;               //װ����Ա
    u16                 RepairTime;                 //ά��ʱ��
    u16                 RepairStaff;                //ά����Ա
    u8                  Rsv[12];                    //Ԥ��12��
}StrProductInfo;


__packed
typedef union _Unnctrl_ {
    struct{
        
        /***************************************************
        * ������ ϵͳ��������ʼ��ַ = 000   ͨѶ���룬����汾����¼�ţ���Ʒ��Ϣ
        */ 
        StrRecHeadInfo      sHeadInfo;                      // 16
        
        /***************************************************
        * ��������Ʒ��Ϣ����ʼ��ַ = 032
        */
        StrProductInfo	    sProductInfo;			        // 32
        
        strSysPara          sys;        //��������
        /*******************************************************************************
        * Description  : ���ڿ�����
        * Author       : 2018/5/16 ������, by redmorningcn
        */
        StrCOMCtrl          ComCtrl[4];                         //��������
        
    };
    uint16   buf[1024];
        
}Unnctrl;

extern  Unnctrl Ctrl;      
//��������
extern    Unnctrl     Ctrl;


#endif                                                          /* End of  include.                       */

