/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#ifndef  _csnr_package_deal_h_h_
#define  _csnr_package_deal_h_h_

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include  "CrcCheck.h"
#include  "app_com_type.h"

/********************************************************************************************/
// Constants
/********************************************************************************************/
#define     FRAM_HERD0     		0x10        //����ͷ
#define     FRAM_HERD1     		0x28       	//����ͷ				

#define    	FRAM_END0     		0x10        //����β
#define     FRAM_END1     		0x2C       	//����β	
	   
#define		RS485_CHK_SUM		0x02		//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define		RS485_CHK_CRC		0x01		//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define		RS485_CHK_RESUM		0x03		//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 

/********************************************************************************************/
// struct���첽����ͨѶЭ��ṹ�壩
/********************************************************************************************/
typedef struct {     
	unsigned char	    sourceaddr;
	unsigned char 	    destaddr;
	unsigned char 	    framnum;
	unsigned char 	    framcode;
	unsigned char       *databuf;	  	//������
	unsigned char       *rxtxbuf;		//�շ�������
	unsigned char 	    datalen;
	unsigned char 	    rxtxlen;
	unsigned char 	    tmp[2];
}strCsnrProtocolPara;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
//���ݴ��������stcCsnrProtocolPara��Ϣ�������ݴ����CNSR����
//
extern	void                DataPackage_CSNC(strCsnrProtocolPara * sprotocolpara);

//���ݽ���������ܵ������ݽ������stcCsnrProtocolPara��Ϣ
//������ȷ������1�����򣬷���0
extern unsigned char     DataUnpack_CSNC(strCsnrProtocolPara *sprotocolpara);

#endif
