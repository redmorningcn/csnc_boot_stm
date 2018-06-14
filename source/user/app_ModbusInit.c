
/*******************************************************************************
* Description  : modbus初始化
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*/

#include <includes.h>
#include <string.h>
#include <bsp_os.h>

#include <app_com_type.h>


/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* MACROS
*/

/*******************************************************************************
* TYPEDEFS
*/

/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
* GLOBAL VARIABLES
*/

/***********************************************
* 描述： 任务控制块（TCB）
*/

/***********************************************
* 描述： 任务堆栈（STACKS）
*/

void         BSP_OS_TimeDlyMs          (CPU_INT32U      dly_ms);


/*******************************************************************************
* LOCAL FUNCTIONS
*/
/*******************************************************************************
* 名    称： APP_ModbusInit
* 功    能： MODBUS初始化
* 入口参数： 无
* 出口参数： 无
* 作    者： 无名沈
* 创建日期： 2015-03-28
* 修    改：
* 修改日期：
* 备    注： 该初始化会创建Modbus任务。
*******************************************************************************/
void App_ModbusInit(void)
{
    MODBUS_CH   *pch;
    u8          comnum = 0;
    u32         boud   = 0;

    /***********************************************
    * 描述： uCModBus初始化，RTU时钟频率为1000HZ
    *        使用了定时器2（TIM2）
    */
    MB_Init(1000);
    
    /***********************************************
    * 描述： UART1连接无线模块
    *        用作从机。
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 0;                                    //所用串号
    boud        = 57600;
    pch         = MB_CfgCh( DTU_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            boud,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    Ctrl.ComCtrl[DTU].ConnCtrl.MB_Node      = DTU_NODE;     //modbus编号 
    Ctrl.ComCtrl[DTU].ConnCtrl.COM_Num      = comnum;       //串口号
    Ctrl.ComCtrl[DTU].ConnCtrl.SourceAddr   = LKJ_MAINBOARD_ADDR;   //无线发送模块地址
    Ctrl.ComCtrl[DTU].ConnCtrl.DestAddr     = DTU_ADDR;             //LKJ接口板csnc地址
    Ctrl.ComCtrl[DTU].ConnCtrl.Baud         = boud;

    //Ctrl.ComCtrl[DTU].RxCtrl.EvtFlag       = COMM_EVT_FLAG_DTU_RX; //os事件标识 

    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // 接收信号量
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // 发送信号量
    Ctrl.ComCtrl[DTU].pch  = pch;                      // ... modbus控制块和全局结构体建立连接
    
#endif
    
    /***********************************************
    * 描述： UART2连接工况检测板及速度信号检测板。modbus通讯
    *        用作主机。
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 1;                                    //所用串号
    boud        = 57600;
    
    pch         = MB_CfgCh( MTR_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_MASTER,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            boud,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    Ctrl.ComCtrl[MTR].ConnCtrl.MB_Node     = MTR_NODE;             //modbus编号 
    Ctrl.ComCtrl[MTR].ConnCtrl.COM_Num     = comnum;               //串口号
    Ctrl.ComCtrl[MTR].ConnCtrl.SourceAddr  = LKJ_MAINBOARD_ADDR;   //无线发送模块地址（对MTR无效）
    Ctrl.ComCtrl[MTR].ConnCtrl.DestAddr    = DTU_ADDR;             //LKJ接口板csnc地址（对MTR无效）
    Ctrl.ComCtrl[MTR].ConnCtrl.Baud        = boud;
    
    //Ctrl.ComCtrl[MTR].RxCtrl.EvtFlag       = COMM_EVT_FLAG_MTR_RX; //os事件标识 

    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // 接收信号量
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // 发送信号量
    Ctrl.ComCtrl[MTR].pch  = pch;                       // ... modbus控制块和全局结构体建立连接
    
#endif    


    /***********************************************
    * 描述： UART4连接备用通道接口
    *        用作主机。
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 3;                                    //所用串号
    boud        = 57600;
    
    pch         = MB_CfgCh( TAX_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            boud,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    Ctrl.ComCtrl[TAX].ConnCtrl.MB_Node     = TAX_NODE;             //modbus编号 
    Ctrl.ComCtrl[TAX].ConnCtrl.COM_Num     = comnum;               //串口号
    Ctrl.ComCtrl[TAX].ConnCtrl.SourceAddr  = LKJ_MAINBOARD_ADDR;   //无线发送模块地址（对MTR无效）
    Ctrl.ComCtrl[TAX].ConnCtrl.DestAddr    = DTU_ADDR;             //LKJ接口板csnc地址（对MTR无效）
    Ctrl.ComCtrl[TAX].ConnCtrl.Baud        = boud;
    //Ctrl.ComCtrl[TAX].RxCtrl.EvtFlag       = COMM_EVT_FLAG_TAX_RX; //os事件标识 
    
    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // 接收信号量
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // 发送信号量
    Ctrl.ComCtrl[TAX].pch  = pch;                       // ... modbus控制块和全局结构体建立连接
    
#endif    
}   


#if (MODBUS_CFG_NOMODBUS_EN == DEF_ENABLED)

/**************************************************************
* Description  : 非modbus接收任务
* Author       : 2018/5/21 星期一, by redmorningcn
*/
CPU_BOOLEAN  MBN_FCxx_Handler (MODBUS_CH  *pch)
{
    //数据存在于 pch->RxFrameData（不含crc校验）中，数据数据长度
    //将CRC也存放到pch->RxFrameData，长度pch->RxFrameNDataBytes+2+2
    int len = pch->RxFrameNDataBytes+2+2;
    memcpy(&pch->RxFrameData[pch->RxFrameNDataBytes+2],(u8 *)&pch->RxFrameCRC,sizeof(pch->RxFrameCRC));
    
    u8  i;
    u8  reply;
    for(i = 0;i <sizeof(Ctrl.ComCtrl)/sizeof(StrCOMCtrl);i++ )
    {
        if(Ctrl.ComCtrl[i].pch == pch && pch !=null)    //查找对应的串口控制块
            {
            /**************************************************************
            * Description  : csnc协议
            * Author       : 2018/5/21 星期一, by redmorningcn
            */            
            //判断数据是否满足帧头帧尾要求
            if(     pch->RxFrameData[0]     == FRAM_HERD0
                &&  pch->RxFrameData[1]     == FRAM_HERD1
                &&  pch->RxFrameData[len-2] == FRAM_END0
                &&  pch->RxFrameData[len-1] == FRAM_END1
               )
            {
                Ctrl.ComCtrl[i].RxCtrl.sCsnc.databuf = (u8 *)&Ctrl.ComCtrl[i].Rd;
                Ctrl.ComCtrl[i].RxCtrl.sCsnc.rxtxbuf = pch->RxFrameData;
                Ctrl.ComCtrl[i].RxCtrl.sCsnc.rxtxlen = len;
                

                reply = DataUnpack_CSNC((strCsnrProtocolPara *)&Ctrl.ComCtrl[i].RxCtrl.sCsnc);
                if(reply == 1)  //解析成功
                {
                    //解析地址
                    if(Ctrl.ComCtrl[i].RxCtrl.sCsnc.sourceaddr    == DTU_ADDR ){
                        
                        Ctrl.ComCtrl[i].RxCtrl.Len          = Ctrl.ComCtrl[i].RxCtrl.sCsnc.datalen;
                        Ctrl.ComCtrl[i].RxCtrl.protocol     = CSNC_PROTOCOL;
                        Ctrl.ComCtrl[i].ConnCtrl.RecvEndFlg = 1;                        //接收到结束标识(同一任务中，收发协调)
                        Ctrl.ComCtrl[i].RxCtrl.RecvFlg      = 1;                        //接收到结束标识()
                        
#if (UCOS_EN == DEF_ENABLED )
                        OS_ERR      err;
                        OSFlagPost( ( OS_FLAG_GRP  *)&Ctrl.Os.CommEvtFlagGrp,           //
                                   ( OS_FLAGS      )Ctrl.ComCtrl[i].RxCtrl.EvtFlag,     //发送指定的事件标识组。
                                   ( OS_OPT        )OS_OPT_POST_FLAG_SET,   
                                   ( OS_ERR       *)&err);
#endif
                        
                        return DEF_TRUE; 
                    }
                }
            }
            
            /**************************************************************
            * Description  : 其他协议在此加入接口
            * Author       : 2018/5/21 星期一, by redmorningcn
            */
        }
    }
    
    return DEF_FALSE;
}
  
/**************************************************************
* Description  : 非modbus协议发送(查询发送状态，发送完后退出)
* Author       : 2018/5/21 星期一, by redmorningcn
*/
void NMB_Tx(MODBUS_CH    *pch,
            CPU_INT08U   *p_reg_tbl,
            CPU_INT16U   nbr_bytes)
{
    CPU_INT08U  *ptx_data;
    CPU_INT08U  *pbuf;
    CPU_INT08U   i;
    int         retry = 100;
    
    /**************************************************************
    * Description  : 发送长度为0，退出
    * Author       : 2018/5/21 星期一, by redmorningcn
    */
    if(nbr_bytes == 0)
        return;
    
    /**************************************************************
    * Description  : 等发送完成
    * Author       : 2018/5/21 星期一, by redmorningcn
    */
    retry = 100;           //防死循环
    while (pch->TxBufByteCtr != 0 && retry--){
        u8  dly = (CPU_INT32U)((float)pch->TxBufByteCtr * 1000.0 * 10.0 / (float)pch->BaudRate);
        if(dly == 0)
            dly = 1;
        
        #if (UCOS_EN == DEF_ENABLED )
        BSP_OS_TimeDlyMs( dly );
        #endif
    }
    
    /***********************************************
    * 描述： 2018/1/16,无名沈：将数据写入发送缓冲区 
    */
    if ( p_reg_tbl != &pch->TxBuf[0] ) {
        pbuf      = &pch->TxBuf[0];                                     /* Point to the beginning of the output buffer.             */
        ptx_data  = p_reg_tbl;
        i         = nbr_bytes;                                          /* Include the actual data in the buffer                    */
        
        while (i > 0) {
            *pbuf++ = *ptx_data++;
            i--;
        }
    }
    pch->TxBufByteCtr = nbr_bytes;

    /***********************************************
    * 描述： 2018/1/16,无名沈：等待数据接收完成 （485总线需要）
    */
    CPU_INT16U  lastCtr;
    do {
        lastCtr  = pch->RxBufByteCtr;
        if ( lastCtr ) {
            #if (UCOS_EN == DEF_ENABLED )
            BSP_OS_TimeDlyMs(5);
            #endif
        } else {
            break;
        }
    } while ( ( pch->RxBufByteCtr != lastCtr ) );
    
    /***********************************************
    * 描述： 2018/1/16,无名沈： 发送数据
    */
    MB_Tx(pch);
    
    //等待发送完成。
    while (pch->TxBufByteCtr != 0){
        u8  dly = (CPU_INT32U)((float)pch->TxBufByteCtr * 1000.0 * 10.0 / (float)pch->BaudRate);
        if(dly == 0)
            dly = 1;
        
        #if (UCOS_EN == DEF_ENABLED )
        BSP_OS_TimeDlyMs( dly );
        #endif

    }
    #if (UCOS_EN == DEF_ENABLED )
    BSP_OS_TimeDlyMs( 1 );
    #endif
}

#endif




