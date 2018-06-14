/**************************************************************
* Description  : ������DTUͨѶ�����ݷ��Ͳ���
* Author       : 2018/5/23 ������, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include    <includes.h>
#include    <app_com_type.h>
#include    <app_dtu_send.h>




/**************************************************************
* Description  : ��DTUͨѶ�����Ͳ���
* Author       : 2018/5/23 ������, by redmorningcn
*/
void    app_dtu_send(StrCOMCtrl  * DtuCom)
{
    u8  conntype;               //����ͨ���������á�IAP
    u8  enablesend = 0;         //���ݷ��ͱ�ʶ
    u8  iapcode;
    //��ַ����
    DtuCom->ConnCtrl.sCsnc.sourceaddr   = LKJ_MAINBOARD_ADDR;
    DtuCom->ConnCtrl.sCsnc.destaddr     = DTU_ADDR;
    DtuCom->ConnCtrl.sCsnc.framcode     = DtuCom->RxCtrl.sCsnc.framcode;
    DtuCom->ConnCtrl.sCsnc.framnum      = DtuCom->RxCtrl.sCsnc.framnum;     //�����յ����ݷ���
    
    conntype = DtuCom->ConnCtrl.ConnType;
    
    switch(conntype){
        
        /**************************************************************
        * Description  : ����������Ӧ������������
        * Author       : 2018/5/23 ������, by redmorningcn
        */
    case IAP_COMM:
        iapcode = DtuCom->Rd.dtu.iap.code;  //IAPָ��λ
        
        switch(iapcode)
        {
        case IAP_DATA:                      //IAP���ݴ���Ӧ��
            DtuCom->ConnCtrl.sCsnc.datalen  = IAP_REPLY_DATA_LEN;
            break;
        case IAP_START:                     //IAP����������Ӧ��
        case IAP_END:
        default:
            DtuCom->ConnCtrl.sCsnc.datalen  = DtuCom->RxCtrl.sCsnc.datalen;
            break;
        }
        
        DtuCom->ConnCtrl.sCsnc.databuf      = (u8 *)&DtuCom->Rd;                //��������
        DtuCom->ConnCtrl.sCsnc.rxtxbuf      = DtuCom->pch->TxBuf;               //����������ֱ�Ӵ��뷢�ͻ���
        
        DataPackage_CSNC((strCsnrProtocolPara *)&DtuCom->ConnCtrl.sCsnc);       //���ݴ��
        DtuCom->pch->TxBufByteCtr = DtuCom->ConnCtrl.sCsnc.rxtxlen;             //���ݳ���׼��
        enablesend = 1;                     //���ݷ��ͱ�ʶ1
        if(iapcode == IAP_END)
            DtuCom->ConnCtrl.ConnType = RECORD_SEND_COMM;                       //Ĭ��״̬λ���ݷ���
        
        break;
        
    default:
        DtuCom->ConnCtrl.ConnType = RECORD_SEND_COMM;                           //Ĭ��״̬λ���ݷ���
        break;
    }
    
    if( enablesend == 1 )                   //�����ݷ���
    {
        //���ݷ���״̬׼��
        if(DtuCom->pch->TxBufByteCtr == 0)                                      //��������쳣������20�ֽ�
            DtuCom->pch->TxBufByteCtr = 20;
        
        DtuCom->ConnCtrl.protocol   = CSNC_PROTOCOL;    
        DtuCom->ConnCtrl.RecvEndFlg = 0;                                        //����Ҫ�ڹ涨ʱ���ڽ��յ�Ӧ���ǣ�Э������                                         
        DtuCom->RxCtrl.RecvFlg      = 0;
        //DtuCom->ConnCtrl.sCsnc
        
        //���ݷ���
        NMB_Tx(DtuCom->pch,DtuCom->pch->TxBuf,DtuCom->pch->TxBufByteCtr);
    }
}




