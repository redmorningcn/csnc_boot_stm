
/*******************************************************************************
* Description  : modbus��ʼ��
* Author       : 2018/5/11 ������, by redmorningcn
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
* ������ ������ƿ飨TCB��
*/

/***********************************************
* ������ �����ջ��STACKS��
*/

void         BSP_OS_TimeDlyMs          (CPU_INT32U      dly_ms);


/*******************************************************************************
* LOCAL FUNCTIONS
*/
/*******************************************************************************
* ��    �ƣ� APP_ModbusInit
* ��    �ܣ� MODBUS��ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
* ��    �ߣ� ������
* �������ڣ� 2015-03-28
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �ó�ʼ���ᴴ��Modbus����
*******************************************************************************/
void App_ModbusInit(void)
{
    MODBUS_CH   *pch;
    u8          comnum = 0;
    u32         boud   = 0;

    /***********************************************
    * ������ uCModBus��ʼ����RTUʱ��Ƶ��Ϊ1000HZ
    *        ʹ���˶�ʱ��2��TIM2��
    */
    MB_Init(1000);
    
    /***********************************************
    * ������ UART1��������ģ��
    *        �����ӻ���
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 0;                                    //���ô���
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

    Ctrl.ComCtrl[DTU].ConnCtrl.MB_Node      = DTU_NODE;     //modbus��� 
    Ctrl.ComCtrl[DTU].ConnCtrl.COM_Num      = comnum;       //���ں�
    Ctrl.ComCtrl[DTU].ConnCtrl.SourceAddr   = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ
    Ctrl.ComCtrl[DTU].ConnCtrl.DestAddr     = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ
    Ctrl.ComCtrl[DTU].ConnCtrl.Baud         = boud;

    //Ctrl.ComCtrl[DTU].RxCtrl.EvtFlag       = COMM_EVT_FLAG_DTU_RX; //os�¼���ʶ 

    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // �����ź���
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // �����ź���
    Ctrl.ComCtrl[DTU].pch  = pch;                      // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
#endif
    
    /***********************************************
    * ������ UART2���ӹ������弰�ٶ��źż��塣modbusͨѶ
    *        ����������
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 1;                                    //���ô���
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

    Ctrl.ComCtrl[MTR].ConnCtrl.MB_Node     = MTR_NODE;             //modbus��� 
    Ctrl.ComCtrl[MTR].ConnCtrl.COM_Num     = comnum;               //���ں�
    Ctrl.ComCtrl[MTR].ConnCtrl.SourceAddr  = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ����MTR��Ч��
    Ctrl.ComCtrl[MTR].ConnCtrl.DestAddr    = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ����MTR��Ч��
    Ctrl.ComCtrl[MTR].ConnCtrl.Baud        = boud;
    
    //Ctrl.ComCtrl[MTR].RxCtrl.EvtFlag       = COMM_EVT_FLAG_MTR_RX; //os�¼���ʶ 

    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // �����ź���
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // �����ź���
    Ctrl.ComCtrl[MTR].pch  = pch;                       // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
#endif    


    /***********************************************
    * ������ UART4���ӱ���ͨ���ӿ�
    *        ����������
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 3;                                    //���ô���
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

    Ctrl.ComCtrl[TAX].ConnCtrl.MB_Node     = TAX_NODE;             //modbus��� 
    Ctrl.ComCtrl[TAX].ConnCtrl.COM_Num     = comnum;               //���ں�
    Ctrl.ComCtrl[TAX].ConnCtrl.SourceAddr  = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ����MTR��Ч��
    Ctrl.ComCtrl[TAX].ConnCtrl.DestAddr    = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ����MTR��Ч��
    Ctrl.ComCtrl[TAX].ConnCtrl.Baud        = boud;
    //Ctrl.ComCtrl[TAX].RxCtrl.EvtFlag       = COMM_EVT_FLAG_TAX_RX; //os�¼���ʶ 
    
    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // �����ź���
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // �����ź���
    Ctrl.ComCtrl[TAX].pch  = pch;                       // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
#endif    
}   


#if (MODBUS_CFG_NOMODBUS_EN == DEF_ENABLED)

/**************************************************************
* Description  : ��modbus��������
* Author       : 2018/5/21 ����һ, by redmorningcn
*/
CPU_BOOLEAN  MBN_FCxx_Handler (MODBUS_CH  *pch)
{
    //���ݴ����� pch->RxFrameData������crcУ�飩�У��������ݳ���
    //��CRCҲ��ŵ�pch->RxFrameData������pch->RxFrameNDataBytes+2+2
    int len = pch->RxFrameNDataBytes+2+2;
    memcpy(&pch->RxFrameData[pch->RxFrameNDataBytes+2],(u8 *)&pch->RxFrameCRC,sizeof(pch->RxFrameCRC));
    
    u8  i;
    u8  reply;
    for(i = 0;i <sizeof(Ctrl.ComCtrl)/sizeof(StrCOMCtrl);i++ )
    {
        if(Ctrl.ComCtrl[i].pch == pch && pch !=null)    //���Ҷ�Ӧ�Ĵ��ڿ��ƿ�
            {
            /**************************************************************
            * Description  : csncЭ��
            * Author       : 2018/5/21 ����һ, by redmorningcn
            */            
            //�ж������Ƿ�����֡ͷ֡βҪ��
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
                if(reply == 1)  //�����ɹ�
                {
                    //������ַ
                    if(Ctrl.ComCtrl[i].RxCtrl.sCsnc.sourceaddr    == DTU_ADDR ){
                        
                        Ctrl.ComCtrl[i].RxCtrl.Len          = Ctrl.ComCtrl[i].RxCtrl.sCsnc.datalen;
                        Ctrl.ComCtrl[i].RxCtrl.protocol     = CSNC_PROTOCOL;
                        Ctrl.ComCtrl[i].ConnCtrl.RecvEndFlg = 1;                        //���յ�������ʶ(ͬһ�����У��շ�Э��)
                        Ctrl.ComCtrl[i].RxCtrl.RecvFlg      = 1;                        //���յ�������ʶ()
                        
#if (UCOS_EN == DEF_ENABLED )
                        OS_ERR      err;
                        OSFlagPost( ( OS_FLAG_GRP  *)&Ctrl.Os.CommEvtFlagGrp,           //
                                   ( OS_FLAGS      )Ctrl.ComCtrl[i].RxCtrl.EvtFlag,     //����ָ�����¼���ʶ�顣
                                   ( OS_OPT        )OS_OPT_POST_FLAG_SET,   
                                   ( OS_ERR       *)&err);
#endif
                        
                        return DEF_TRUE; 
                    }
                }
            }
            
            /**************************************************************
            * Description  : ����Э���ڴ˼���ӿ�
            * Author       : 2018/5/21 ����һ, by redmorningcn
            */
        }
    }
    
    return DEF_FALSE;
}
  
/**************************************************************
* Description  : ��modbusЭ�鷢��(��ѯ����״̬����������˳�)
* Author       : 2018/5/21 ����һ, by redmorningcn
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
    * Description  : ���ͳ���Ϊ0���˳�
    * Author       : 2018/5/21 ����һ, by redmorningcn
    */
    if(nbr_bytes == 0)
        return;
    
    /**************************************************************
    * Description  : �ȷ������
    * Author       : 2018/5/21 ����һ, by redmorningcn
    */
    retry = 100;           //����ѭ��
    while (pch->TxBufByteCtr != 0 && retry--){
        u8  dly = (CPU_INT32U)((float)pch->TxBufByteCtr * 1000.0 * 10.0 / (float)pch->BaudRate);
        if(dly == 0)
            dly = 1;
        
        #if (UCOS_EN == DEF_ENABLED )
        BSP_OS_TimeDlyMs( dly );
        #endif
    }
    
    /***********************************************
    * ������ 2018/1/16,�����򣺽�����д�뷢�ͻ����� 
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
    * ������ 2018/1/16,�����򣺵ȴ����ݽ������ ��485������Ҫ��
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
    * ������ 2018/1/16,������ ��������
    */
    MB_Tx(pch);
    
    //�ȴ�������ɡ�
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




