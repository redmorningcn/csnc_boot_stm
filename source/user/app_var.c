/*******************************************************************************
* Description  : 定义及初始化全局变量
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/

#include <app_type.h>

/*******************************************************************************
* Description  : 定义全局变量  sCtrl
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/
Unnctrl     Ctrl;              //
    
/*******************************************************************************
* Description  : 无线发送模块控制指针
* Author       : 2018/5/14 星期一, by redmorningcn
*******************************************************************************/
StrCOMCtrl  * DtuCom;

/*******************************************************************************
* Description  : 和检测板串口控制指针
* Author       : 2018/5/14 星期一, by redmorningcn
*******************************************************************************/
StrCOMCtrl  * MtrCom;

/*******************************************************************************
* Description  : 和检测板串口控制指针
* Author       : 2018/5/14 星期一, by redmorningcn
*******************************************************************************/
StrCOMCtrl  * TaxCom;



/*******************************************************************************
* Description  : 全局变量初始化
* Author       : 2018/5/18 星期五, by redmorningcn
*/
void app_init_sctrl(void)
{ 
//    WdtReset();
    /*******************************************************************************
    * Description  : 初始化串口连接参数默认值
    * Author       : 2018/5/18 星期五, by redmorningcn
    */    
    u8  i;
    for(i = 0;i <sizeof(Ctrl.ComCtrl)/sizeof(StrCOMCtrl);i++ )
    {
        Ctrl.ComCtrl[i].ConnectFlag             = 0;        //连接标识：0，该串口无连接；1，有连接。
        Ctrl.ComCtrl[i].ConnCtrl.TimeOut        = 5;        //连接超时时间。（超过该时间，认为连接断开）
        
        Ctrl.ComCtrl[i].ConnCtrl.Baud           = 57600;
        Ctrl.ComCtrl[i].ConnCtrl.Bits           = USART_WordLength_8b;
        Ctrl.ComCtrl[i].ConnCtrl.COM_Num        = 0x01;
        Ctrl.ComCtrl[i].ConnCtrl.Connflg        = 1;        //默认有连接
//        Ctrl.ComCtrl[i].ConnCtrl.ConnType       = RECORD_SEND_COMM;//默认为数据发送
        Ctrl.ComCtrl[i].ConnCtrl.DataCode       = 0;
        Ctrl.ComCtrl[i].ConnCtrl.datalen        = 0;
        Ctrl.ComCtrl[i].ConnCtrl.DestAddr       = DTU_ADDR; //DTU模块
        Ctrl.ComCtrl[i].ConnCtrl.EnableConnFlg  = 1;        //该连接允许
        Ctrl.ComCtrl[i].ConnCtrl.ErrFlg         = 0;        //连接正常
//        Ctrl.ComCtrl[i].ConnCtrl.FrameCode      = RECORD_FRAME_CODE;//数据通讯
        Ctrl.ComCtrl[i].ConnCtrl.FramNum        = 1;        //序号从1开始
        Ctrl.ComCtrl[i].ConnCtrl.MB_Node        = 1;
        Ctrl.ComCtrl[i].ConnCtrl.Parity         = USART_Parity_No;//无校验
        Ctrl.ComCtrl[i].ConnCtrl.protocol       = CSNC_PROTOCOL;  //CSNC协议 
        //Ctrl.ComCtrl[i].ConnCtrl.rec             
        Ctrl.ComCtrl[i].ConnCtrl.RecordSendFlg  = 0;        //暂无记录发送
        Ctrl.ComCtrl[i].ConnCtrl.RecvEndFlg     = 0;        //无数据接收
        Ctrl.ComCtrl[i].ConnCtrl.SendRecordNum  = 1;        //记录 同步用（确认）
        Ctrl.ComCtrl[i].ConnCtrl.SourceAddr     = LKJ_MAINBOARD_ADDR;     //本机地址
        Ctrl.ComCtrl[i].ConnCtrl.Stops          = USART_StopBits_1;
        Ctrl.ComCtrl[i].ConnectTimeOut          = 5;            //超时时间：5秒内，该串口无连接（数据接收），则串口断开。
        Ctrl.ComCtrl[i].TimeoutEn               = 0;            //超时计数停止。（发送数据时启动）

//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.databuf  = (u8 *)&Ctrl.ComCtrl[i].Wr;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.datalen  = 0;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.destaddr = Ctrl.ComCtrl[i].ConnCtrl.DestAddr;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.framcode = Ctrl.ComCtrl[i].ConnCtrl.FrameCode;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.framnum  = Ctrl.ComCtrl[i].ConnCtrl.FramNum;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.rxtxbuf  = Ctrl.ComCtrl[i].pch->TxBuf;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.rxtxlen  = 0;
//        Ctrl.ComCtrl[i].ConnCtrl.sCsnc.sourceaddr = Ctrl.ComCtrl[i].ConnCtrl.SourceAddr;
        //Ctrl.ComCtrl[i].ConnCtrl.sCsnc.tmp      =

//        Ctrl.ComCtrl[i].RxCtrl.sCsnc.databuf    = (u8 *)&Ctrl.ComCtrl[i].Rd;    
//        Ctrl.ComCtrl[i].RxCtrl.sCsnc.rxtxbuf    = (u8 *)&Ctrl.ComCtrl[i].pch->RxBuf;  
        Ctrl.ComCtrl[i].RxCtrl.protocol         =  CSNC_PROTOCOL;
    }

    /*****************************************************************
    * Description  : 从FRAM中分别读出head、NumMgr、Porduct、RunPara
    * Author       : 2018/5/17 星期四, by redmorningcn
    */
//    Ctrl.sRunPara.FramFlg.RdHead    = 1;
//    Ctrl.sRunPara.FramFlg.RdNumMgr  = 1;
//    Ctrl.sRunPara.FramFlg.RdProduct = 1;
//    Ctrl.sRunPara.FramFlg.RdRunPara = 1;
//    App_FramPara();
//    
//    Ctrl.sRunPara.Err.Errors        = 0;                //清零故障代码
//    
//    if(Ctrl.sHeadInfo.Password != MODBUS_PASSWORD){     //通讯密码
//        Ctrl.sHeadInfo.Password = MODBUS_PASSWORD;
//        Ctrl.sRunPara.Err.FramErr = 1;                  //铁电故障（指定地址读出的值错误）
//    }
//   
//    Ctrl.sRunPara.SysSts.StartFlg   = 1;                //开始标示 
//    
//    if ( ( Ctrl.sRunPara.StoreTime < 5 ) ||             //数据存储周期
//         ( Ctrl.sRunPara.StoreTime > 10*60 ) ) {
//        Ctrl.sRunPara.StoreTime    = 60;
//    }
}
