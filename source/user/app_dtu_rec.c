/**************************************************************
* Description  : 处理板和dtu通讯，接收部分
* Author       : 2018/5/24 星期四, by redmorningcn
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
* Description  : 和DTU通讯，接收部分
* Author       : 2018/5/24 星期三, by redmorningcn
*/
void    app_dtu_rec(StrCOMCtrl  * DtuCom)
{
    u8  conntype;                                               //数据通许、参数设置、IAP
    u8  enablesend = 0;                                         //数据发送标识
    
    /**************************************************************
    * Description  : 确定通讯类型。
    如果是程序下载，或者参数读写，则更改为对应的通讯类型。
    * Author       : 2018/5/24 星期四, by redmorningcn
    */
    if(DtuCom->RxCtrl.protocol == CSNC_PROTOCOL)                //csnc异步串口通讯协议
    {
        switch(DtuCom->RxCtrl.FrameCode)
        {
        case IAP_FRAME_CODE:
            DtuCom->ConnCtrl.ConnType = IAP_COMM;               //IAP通讯
            break;
       
        default:
            DtuCom->ConnCtrl.ConnType= RECORD_SEND_COMM; //默认为数据发送

            if(DtuCom->RxCtrl.sCsnc.sourceaddr == SET_ADDR){
                DtuCom->ConnCtrl.ConnType   = SET_COMM;         //参数读取
            }
            
            break;
        }
    }
    
    //根据通讯类型处理
    conntype = DtuCom->ConnCtrl.ConnType;
    
    switch(conntype){
        
        /**************************************************************
        * Description  : 程序升级。应答升级的内容
        * Author       : 2018/5/23 星期三, by redmorningcn
        */
    case IAP_COMM:
        
        Ctrl.sys.sys_outtime = 30;      //如果接受到启动下载数据后，定时3s
        
        app_iap_deal(DtuCom);                 //iap升级处理
        
        enablesend = 1;                 //启动数据发送
        break;
        
        
        /**************************************************************
        * Description  : GPS模块通讯,成功接收到数据
        * Author       : 2018/6/4 星期一, by redmorningcn
        */
    case GPS_COMM:
        
        enablesend = 0;                 
        break;
    default:
        break;
    }
    
    //置发送标识，启动发送
    if( enablesend == 1 ){
        DtuCom->ConnCtrl.RecordSendFlg = 1;
    }
}




