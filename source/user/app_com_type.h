/*******************************************************************************
* Description  : ����ͨѶ���ƽṹ�嶨�壨APP�㣩
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

#ifndef	__APP_COM_TYPE_H__
#define	__APP_COM_TYPE_H__
#include <includes.h>
#include <csnr_package_deal.h>
#include <IAP_program_mcu.h>


/*********************************************************************
* INCLUDES
*/
#define COMM_RECV_DATA_MAX_LEN   512
#define COMM_SEND_DATA_MAX_LEN   512    /* Լ���� 128*2+10*2  */
#define COM_CONN_NUM             4     

//���ڵ�ַ����    
#define     DTU                 0               /* DTU���ÿ��ƽṹ�����         ComCtrl[]*/
#define     DTU_C0              0               /* DTU_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     DTU_NODE            1               /* DTU modebus���*/

//���ڵ�ַ����    
#define     MTR                 1               /* MTR���ÿ��ƽṹ�����         ComCtrl[]*/
#define     MTR_C0              0               /* MTR_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     MTR_NODE            1               /* MTR modebus���*/

//���ڵ�ַ����    
#define     TAX                 2               /* TAX���ÿ��ƽṹ�����         ComCtrl[]*/
#define     TAX_C0              0               /* TAX_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     TAX_NODE            1               /* TAX modebus���*/

//csnc��ַ����
#define     LKJ_MAINBOARD_ADDR  (0x80)          /* LKJ�ӿ����ߴ������ CSNC Э���ַ*/
#define     DTU_ADDR            (0xCA)          /* ���߷���ģ�� CSNC Э���ַ */
#define     SET_ADDR            (0xC2)          /* ���߷���ģ�� CSNC Э���ַ */

//ͨѶ��������
#define     RECORD_SEND_COMM    0               /* ���ݼ�¼����          */
#define     SET_COMM            1               /* ��������              */
#define     IAP_COMM            2               /* ������������          */  
#define     RECORD_GET_COMM     3               /* ��ѯ���ݼ�¼          */
#define     GPS_COMM            4

//ͨѶЭ������
#define     MODBUS_PROTOCOL     0
#define     CSNC_PROTOCOL       1
#define     Q560_PROTOCOL       2               /* ���߷���ģ��ATָ��   */


//����ͨѶ��ʱʱ��
#define     DTU_TIMEOUT         60
#define     MTR_TIMEOUT         5
#define     TAX_TIMEOUT         5

//MTR ͨѶ���Ͷ��壨conntype��
#define     MTR_RD_DETECT       0 /* ��������ݲ��� */
#define     MTR_RD_SYS          1 /* ����Ʒ��Ϣ     */
#define     MTR_RD_CALI         2 /* ������У׼��Ϣ */
#define     MTR_WR_SYS          3 /* д��Ʒ��Ϣ     */
#define     MTR_WR_CALI         4 /* д����У׼��Ϣ */
//MTR ���ݵ�ַ����

/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/
__packed
typedef struct {     
 	u16     Type;       //��������	2	�μ��������ʹ����
 	u16     Nbr;        //������		2	
} stcLocoId;

typedef struct {
    u8      buf[8];
    u8      ack;
} stcParaReply;

/**************************************************************
* Description  : dtu��������
* Author       : 2018/5/25 ������, by redmorningcn
*/
__packed
typedef struct{
    union{
        struct{
            u32     code;
            union{
                stcLocoId       loco;
                stcParaReply    reply;
                u32             recordnum;      //��¼��
                struct{                         //ָ����ַ��ȡ
                    u16         paraaddr;
                    u16         paralen;
                    u16         parabuf[64];       
                };
            };
        };
        strIapdata      iap;
    };
}strDtuRecData;


/*******************************************************************************
* Description  : ���ڽ������ݽṹ������
��ͬЭ�飬��ָͬ������ݿɸ��á�
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef union {
    
//  ���ݽṹ1
//  ���ݽṹ2��
    union{
        strDtuRecData   dtu;    //dtu�������õ�����
    };
    u16             Buf16[COMM_RECV_DATA_MAX_LEN/2];		            //	
    u8              Buf[COMM_RECV_DATA_MAX_LEN];		            //	
} uRecvData;


/*******************************************************************************
* Description  : ���ڷ�������������
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef union {
//	stcFlshRecNdp02A        sRecA;				    //���ݼ�¼     128 	
//  ���ݽṹ1
//  ���ݽṹ2

    u16             Buf16[COMM_SEND_DATA_MAX_LEN/2];		            //	
    u8              Buf[COMM_SEND_DATA_MAX_LEN];	
} uSendData;

/*******************************************************************************
* Description  : ���ӿ�����
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef struct {     
    u32     EnableConnFlg:1;     //���ӿ��ƣ�1���������ӣ�0������������
    u32     RecvEndFlg  :1;     //���ձ�ʾ��1�����ݽ�����ɣ�0�������ݽ��ա�
    u32     RecordSendFlg:1;     //���ͱ�ʾ�������ݷ��ͣ�1�������ݷ��ͣ�0
    u32     ErrFlg      :1;     //�����ʾ������������0�����Ӵ���1
    u32     Connflg     :1;     //����״̬��1�������ӣ�0�������ӡ�
    u32     ConnType    :3;     //�������ͣ�0�����ݴ��䣻1���������ã�2��IAP���䣻
            
    u32     protocol    :2;     //ͨ��Э�顣0��modbus��1��csnc��
    u32     TimeOutEn   :1;     //��ʱ�����������ʶ��
    u32     TimeOut     :5;     //��ʱʱ�䣬��λ1s��
    
    u32     MB_Node     :5;     //modbus���ӱ��
    u32     COM_Num     :3;     //���ڱ��
        
    u32     Bits        :4;
    u32     Parity      :2;
    u32     Stops       :2;
   
    u32     Baud;
    u32     DataCode;           //�����֣��������ڲ���
    
    u8      SendRecordNum;      //���ͼ�¼��
    u8      rec[3];
    union {
        struct{
            u8  DestAddr;       //Դ��ַ        master = 0x80	   
            u8  SourceAddr;     //���յ�ַ      slave  = 0xCA	   
            u8  FramNum;        //֡���   
            u8  FrameCode;      //֡������
            u8  datalen;        //���ݳ���     
        };
        
        strCsnrProtocolPara sCsnc;  //CSNCЭ��ṹ��
    };
}sCOMConnCtrl;		


//���տ�����
typedef struct {     
    union {
        struct{
            u8      SourceAddr;     //Դ��ַ        master = 0x80	   
            u8      DestAddr;       //���յ�ַ      slave  = 0xCA	   
            u8      FramNum;        //֡���   
            u8      FrameCode;      //֡������
        };
        
        strCsnrProtocolPara sCsnc;  //CSNCЭ��ṹ��
    };
    u8      Len;                    //������Ч���ݳ���
    u8      protocol;               //ͨ��Э�顣0��modbus��1��csnc��
    u8      EvtFlag;                //ʱ���ʶ��
    u8      RecvFlg     :1;         //���ݽ������
    u8      RxSignalFlg :1;         //���յ��ź���
    u8      Tmp         :6;
    u32     DataCode;               //���տ�����
    
} sCOMRecvCtrl;

/*******************************************************************************
* Description  : ���ڿ��ƽṹ�壨app�㣩
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef struct {  
	uRecvData	        Rd;			                    //����������
	uSendData	        Wr;			                    //����������
    
    MODBUS_CH           *pch;                   		// MODBUS���
    
    u16                 ConnectTimeOut  : 14;     	    // ���ӳ�ʱ����������Ϊ��λ
    u16                 TimeoutEn       : 1;         	// ����������
    u16                 ConnectFlag     : 1;         	// ���ӱ�־

    /***************************************************
    * ������ ���ڿ�����
    */
	sCOMRecvCtrl    	RxCtrl;				            //���տ��ƣ�������ǰ���յ��Ŀ�����Ϣ 
	sCOMConnCtrl		ConnCtrl;                       //���ӿ��ƣ���ÿ����ַ��Ϊ�������������ӣ���APP���ö˴���
	
} StrCOMCtrl;


#endif	
