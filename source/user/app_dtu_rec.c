/**************************************************************
* Description  : ������dtuͨѶ�����ղ���
* Author       : 2018/5/24 ������, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include    <includes.h>
#include    <app_com_type.h>
#include    <app_dtu_rec.h>
#include    <string.h>

extern  void app_iap_deal(StrCOMCtrl  * DtuCom);
/**************************************************************
* Description  : ��DTUͨѶ�����ղ���
* Author       : 2018/5/24 ������, by redmorningcn
*/
void    app_dtu_rec(StrCOMCtrl  * DtuCom)
{
    u8  conntype;                                               //����ͨ���������á�IAP
    u8  enablesend = 0;                                         //���ݷ��ͱ�ʶ
    
    /**************************************************************
    * Description  : ȷ��ͨѶ���͡�
    ����ǳ������أ����߲�����д�������Ϊ��Ӧ��ͨѶ���͡�
    * Author       : 2018/5/24 ������, by redmorningcn
    */
    if(DtuCom->RxCtrl.protocol == CSNC_PROTOCOL)                //csnc�첽����ͨѶЭ��
    {
        switch(DtuCom->RxCtrl.FrameCode)
        {
        case IAP_FRAME_CODE:
            DtuCom->ConnCtrl.ConnType = IAP_COMM;               //IAPͨѶ
            break;
       
        default:
            DtuCom->ConnCtrl.ConnType= RECORD_SEND_COMM; //Ĭ��Ϊ���ݷ���

            if(DtuCom->RxCtrl.sCsnc.sourceaddr == SET_ADDR){
                DtuCom->ConnCtrl.ConnType   = SET_COMM;         //������ȡ
            }
            
            break;
        }
    }
    
    //����ͨѶ���ʹ���
    conntype = DtuCom->ConnCtrl.ConnType;
    
    switch(conntype){
        
        /**************************************************************
        * Description  : ����������Ӧ������������
        * Author       : 2018/5/23 ������, by redmorningcn
        */
    case IAP_COMM:
        
        Ctrl.sys.sys_outtime = 30;      //������ܵ������������ݺ󣬶�ʱ3s
        
        app_iap_deal(DtuCom);                 //iap��������
        
        enablesend = 1;                 //�������ݷ���
        break;
        
        
        /**************************************************************
        * Description  : GPSģ��ͨѶ,�ɹ����յ�����
        * Author       : 2018/6/4 ����һ, by redmorningcn
        */
    case GPS_COMM:
        
        enablesend = 0;                 
        break;
    default:
        break;
    }
    
    //�÷��ͱ�ʶ����������
    if( enablesend == 1 ){
        DtuCom->ConnCtrl.RecordSendFlg = 1;
    }
}




