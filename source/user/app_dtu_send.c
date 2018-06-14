/**************************************************************
* Description  : 处理板和DTU通讯，数据发送部分
* Author       : 2018/5/23 星期三, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include    <includes.h>
#include    <app_com_type.h>
#include    <app_dtu_send.h>




/**************************************************************
* Description  : 和DTU通讯，发送部分
* Author       : 2018/5/23 星期三, by redmorningcn
*/
void    app_dtu_send(StrCOMCtrl  * DtuCom)
{
    u8  conntype;               //数据通许、参数设置、IAP
    u8  enablesend = 0;         //数据发送标识
    u8  iapcode;
    //地址设置
    DtuCom->ConnCtrl.sCsnc.sourceaddr   = LKJ_MAINBOARD_ADDR;
    DtuCom->ConnCtrl.sCsnc.destaddr     = DTU_ADDR;
    DtuCom->ConnCtrl.sCsnc.framcode     = DtuCom->RxCtrl.sCsnc.framcode;
    DtuCom->ConnCtrl.sCsnc.framnum      = DtuCom->RxCtrl.sCsnc.framnum;     //将接收到数据发送
    
    conntype = DtuCom->ConnCtrl.ConnType;
    
    switch(conntype){
        
        /**************************************************************
        * Description  : 程序升级。应答升级的内容
        * Author       : 2018/5/23 星期三, by redmorningcn
        */
    case IAP_COMM:
        iapcode = DtuCom->Rd.dtu.iap.code;  //IAP指令位
        
        switch(iapcode)
        {
        case IAP_DATA:                      //IAP数据传输应答
            DtuCom->ConnCtrl.sCsnc.datalen  = IAP_REPLY_DATA_LEN;
            break;
        case IAP_START:                     //IAP启动及结束应答
        case IAP_END:
        default:
            DtuCom->ConnCtrl.sCsnc.datalen  = DtuCom->RxCtrl.sCsnc.datalen;
            break;
        }
        
        DtuCom->ConnCtrl.sCsnc.databuf      = (u8 *)&DtuCom->Rd;                //数据内容
        DtuCom->ConnCtrl.sCsnc.rxtxbuf      = DtuCom->pch->TxBuf;               //打包后的数据直接存入发送缓存
        
        DataPackage_CSNC((strCsnrProtocolPara *)&DtuCom->ConnCtrl.sCsnc);       //数据打包
        DtuCom->pch->TxBufByteCtr = DtuCom->ConnCtrl.sCsnc.rxtxlen;             //数据长度准备
        enablesend = 1;                     //数据发送标识1
        if(iapcode == IAP_END)
            DtuCom->ConnCtrl.ConnType = RECORD_SEND_COMM;                       //默认状态位数据发送
        
        break;
        
    default:
        DtuCom->ConnCtrl.ConnType = RECORD_SEND_COMM;                           //默认状态位数据发送
        break;
    }
    
    if( enablesend == 1 )                   //有数据发送
    {
        //数据发送状态准备
        if(DtuCom->pch->TxBufByteCtr == 0)                                      //如果数据异常，发送20字节
            DtuCom->pch->TxBufByteCtr = 20;
        
        DtuCom->ConnCtrl.protocol   = CSNC_PROTOCOL;    
        DtuCom->ConnCtrl.RecvEndFlg = 0;                                        //如需要在规定时间内接收到应答是，协调处理。                                         
        DtuCom->RxCtrl.RecvFlg      = 0;
        //DtuCom->ConnCtrl.sCsnc
        
        //数据发送
        NMB_Tx(DtuCom->pch,DtuCom->pch->TxBuf,DtuCom->pch->TxBufByteCtr);
    }
}




