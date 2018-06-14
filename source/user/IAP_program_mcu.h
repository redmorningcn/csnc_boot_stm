/**************************************************************
* Description  : ��������Э��
* Author       : 2018/5/25 ������, by redmorningcn
*/
#ifndef	_IAP_PROGRAM_MCU_H
#define	_IAP_PROGRAM_MCU_H

#include <includes.h>

/**************************************************************
* Description  : �궨��
* Author       : 2018/5/25 ������, by redmorningcn
*/
#define IAP_START              1
#define IAP_DATA               2
#define IAP_END                3
#define IAP_ABORT              4

/**************************************************************
* Description  : IAPͨѶ�쳣��Ϣ
* Author       : 2018/5/28 ����һ, by redmorningcn
*/
#define IAP_NO_ERR              0x00
#define IAP_IDX_ERR             0x01
#define IAP_CODE_ERR            0x02
#define IAP_SIZE_ERR            0x03               
#define IAP_STORE_ERR           0x04
#define IAP_END_ERR             0x05
#define IAP_TIME_ERR            0x06


//��ַ��Ϣ                          
#define	USER_BOOT_START_ADDR		0x08000000	
#define	USER_BOOT_PRO_SIZE			0X0800AFFF

#define	USER_APP_START_ADDR			0x08010000
#define	USER_APP_PRO_SIZE			0x08017FFE	

#define	USER_BACK_START_ADDR		0x08028000
#define	USER_BACK_PRO_SIZE			0x08017FFF	

//���IAP������ַ
#define	IAP_PARA_START_ADDR     	0X0800D000	
#define	IAP_PARA_PRO_SIZE			0x00002FFF	


#define	IAP_DATA_BUF_LEN            (128)
#define SEC_DIV_TIMENS              (IAP_WRITE_1024/IAP_DATA_BUF_LEN)


/**************************************************************
* Description  : IAP��������
* Author       : 2018/5/25 ������, by redmorningcn
*/
__packed
typedef  struct   _stcIAPPara_
{
    uint16          HwVer;          //Ӳ���汾
    uint16          SwVer;          //����汾
    uint32          Size;           //�����С
    uint32          Addr;           //��ǰ��ַ
    uint32          Idx;            //֡���
    uint16          End;            //ָ���� 01����ʾ����ȷ�Ŀ���
    uint16          Chk;            //У��
    uint32          Crc32;          //����У����
    uint32          BackAddr;       //��������ַ
    uint16          IdxNbr;         //֡��
    uint16          Rec;            //Ԥ��1
    uint16          Rec1;           //Ԥ��2
    uint16          storeCrc;       //����У��16
}stcIAPPara;

/**************************************************************
* Description  : IAP���ݽṹ������������
* Author       : 2018/5/25 ������, by redmorningcn
*/
typedef  struct{
    u8  code;                       //ָ��
    u8  sta;                        //״̬
    union {
        stcIAPPara  para;           //���Ʋ���
        struct{
            u16 idx;                //�������
            u8  buf[128];           //��������
        };
        u16         replyIdx;       //Ӧ���֡���
    };
}strIapdata;

#endif	/* _IAP_PROGRAM_MCU_H */
