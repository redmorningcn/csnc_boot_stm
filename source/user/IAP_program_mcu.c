/**************************************************************
* Description  : ��������Э��
* Author       : 2018/5/25 ������, by redmorningcn
*/

/*******************************************************************************
 * INCLUDES
 */
#include  <includes.h>
#include  <IAP_program_mcu.h>
#include  <bsp_flash.h>
#include  <string.h>

/*******************************************************************************
 * CONSTANTS
 */


/*******************************************************************************
 * TYPEDEFS
 */

u16     BSP_FlashWriteBytes_Fast     (u32 addr, u8 *pbuf, u16 len);

/**************************************************************
* Description  : app_iap_deal  ���Զ�̻򴮿�����
* Author       : 2018/5/25 ������, by redmorningcn
*/
void    app_iap_deal(StrCOMCtrl  * DtuCom){
    static          stcIAPPara      sLocalIap;                              //�洢��iap����
    static          u32             softver;
    static          u32             time = 0;
    stcIAPPara      *sServerIap =   (stcIAPPara *)&DtuCom->Rd.dtu.iap.para;  //�������·���iap���� 

    u8      code = DtuCom->Rd.dtu.iap.code;             //IAPָ��λ
    u8      sta  = DtuCom->Rd.dtu.iap.sta;              //IAP״̬λ
    u16     crc16;
    u16     idx;                                        //���ݱ��
    u16     datalen;
    u16     Chklen;
    u32     softsize;
    u16     storeCrc;
    
    switch(code)
    {
        
    case IAP_START:                                     //IAP����,

        //���Ѵ��iappara��Ϣ
        //memcpy((uint8 *)&sLocalIap,(uint8 *)IAP_PARA_START_ADDR,sizeof(stcIAPPara));
        BSP_FlashReadBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
       
        Chklen  = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
        crc16   = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
        
        storeCrc= GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap) -2);
        
        //�ԱȽ��յ���iappara��Ϣ���汾����С���ѷ�֡��š�У�顢֡�ţ�
        if ( ( sta == 1 )                           ||      // ��������
            ( sLocalIap.Idx    == 0xffffffff )      ||      // �洢���Ϊ-1
            ( sLocalIap.Idx    == 0 )               ||      // �洢���Ϊ��
            ( sServerIap->Idx  == 0 )               ||      // �������������Ϊ��
            ( sLocalIap.Chk    != crc16)            ||      // У���벻��ȷ
            ( sServerIap->Size != sLocalIap.Size )  ||      // �����С����
                                //( IapServer.Crc32 != IapInfo.Crc32 ) 
            ( sServerIap->SwVer!= sLocalIap.SwVer ) ||      // �汾����
            ( storeCrc         != sLocalIap.storeCrc)        // У���벻��ȷ
            )
        {
            /**************************************************************
            * Description  : ���ط���������
            * Author       : 2018/5/28 ����һ, by redmorningcn
            */
            
            if(     (sLocalIap.Chk    != crc16)
               ||   (sLocalIap.storeCrc != storeCrc )){
                    sLocalIap.Addr      = USER_BACK_START_ADDR;         //��ʼ����ַ
                    sLocalIap.BackAddr  = USER_BACK_START_ADDR;
               }else{
                    sLocalIap.Addr   = sLocalIap.BackAddr;
                    if(sLocalIap.BackAddr < USER_APP_START_ADDR || sLocalIap.BackAddr > 0x08060000) //����400k
                        sLocalIap.Addr  = USER_BACK_START_ADDR;     //��ʼ����ַ
               }
            sLocalIap.Idx         = 0;
            
            sLocalIap.HwVer       = Ctrl.sProductInfo.HwVer;        //����װ�ð汾��Ϣ
            sLocalIap.SwVer       = Ctrl.sProductInfo.SwVer;
            sLocalIap.Size        = sServerIap->Size;           
            sLocalIap.Crc32       = sServerIap->Crc32;
            
            softver               = sServerIap->SwVer;              //����汾��Ϣ������ʱУ��ʹ��
        }else{
            /**************************************************************
            * Description  : ���������洢�ĵ�ַ����
            * Author       : 2018/5/28 ����һ, by redmorningcn
            */
            //sLocalIap.HwVer       = Ctrl.sProductInfo.HwVer;  //���������İ汾��Ϣ
            //sLocalIap.SwVer       = Ctrl.sProductInfo.SwVer;  
            sLocalIap.Addr        = sLocalIap.BackAddr + sLocalIap.Idx * 128;
            softver               = sLocalIap.SwVer;
        }
        
        //��������Ϣ���ظ�����������Ӳ���汾������汾�������С����ǰ��ַ����ǰ֡��
        memcpy((u8 *)&DtuCom->Rd.dtu.iap.para,(u8 *)&sLocalIap,sizeof(stcIAPPara)); 
        //δ���͸�д���򣬲��洢���ĺ��sLocalIapֵ��
        sLocalIap.SwVer = softver;
        
        
        Chklen = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
        crc16 = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
        sLocalIap.Chk = crc16;
        
        sLocalIap.storeCrc = GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap)-2);  //����洢У��

        BSP_FlashWriteBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
        
        time = Ctrl.sys.time;
        break;
    case IAP_DATA:                                          //IAP���ݴ���Ӧ��
        /**************************************************************
        * Description  : ���볬ʱ�жϡ���ʱ��δ����(5s)�������쳣��
        * Author       : 2018/6/8 ������, by redmorningcn
        */
//        if(Ctrl.sys.time > time + 5000 && Ctrl.sys.time > time)
//        {
//            DtuCom->Rd.dtu.iap.sta  = IAP_TIME_ERR;         //��ʱ�쳣
//            break;
//        }
        
        sLocalIap.End   =   0;                              //End=1������������ɣ�End=0��δ��
        if(DtuCom->RxCtrl.Len < 4){
            DtuCom->Rd.dtu.iap.sta  = IAP_IDX_ERR;
            break;
        }
        datalen = DtuCom->RxCtrl.Len - 4;                   //��֡���򳤶ȡ���code��1����sta��1����idx��2��
        idx = DtuCom->Rd.dtu.iap.idx;                       //���
        
        DtuCom->Rd.dtu.iap.sta = IAP_NO_ERR;               //Ӧ��Ĭ������
        
        /**************************************************************
        * Description  : �����䣬����idxЭ������ͬ����
        ���յ�idx������յ�idx��ͬ��������ȷ��
        * Author       : 2018/5/28 ����һ, by redmorningcn
        */
         if(idx == sLocalIap.Idx)                        //�����ȣ��������͡�
        {
            BSP_FlashWriteBytes_Fast(sLocalIap.Addr,DtuCom->Rd.dtu.iap.buf,datalen); //������д��ָ����ַ
            
            sLocalIap.Addr +=  datalen;
            
            u32 size = sLocalIap.Addr - sLocalIap.BackAddr;         //�����س����С
            if(     size > sLocalIap.Size                           //�ѷ��͵ĳ����С�Ѿ����ڳ����С��
               //||   sLocalIap.Size > USER_BACK_PRO_SIZE
                   )            //������ڴ洢����
            {
                DtuCom->Rd.dtu.iap.sta = IAP_SIZE_ERR;              //�����С���� 
            }
            //�����
            Chklen = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
            crc16 = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
            sLocalIap.Chk = crc16;
            
            sLocalIap.storeCrc = GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap)-2);  //����洢У��

            BSP_FlashWriteBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
            
            DtuCom->Rd.dtu.iap.replyIdx = sLocalIap.Idx;                //Ӧ��ǰ��š�    
            sLocalIap.Idx++;                                            //���++���������½��С�

        }else if(idx == sLocalIap.Idx -1){                          //�ظ�֡����������һ֡�ظ����ͣ�

        }else{                                                      //֡��Ŵ���
            DtuCom->Rd.dtu.iap.sta  = IAP_IDX_ERR;
        }
        
        
        time = Ctrl.sys.time;

        break;
    case IAP_END:
        /**************************************************************
        * Description  : ���볬ʱ�жϡ���ʱ��δ����(5s)�������쳣��
        * Author       : 2018/6/8 ������, by redmorningcn
        */
//        if(Ctrl.sys.time > time + 5000 && Ctrl.sys.time > time)
//        {
//            DtuCom->Rd.dtu.iap.sta  = IAP_TIME_ERR;         //��ʱ�쳣
//            break;
//        }
        //����ʾ������ʾ��ͣ2����
        //App_DispDelay(2000); 
        //�����С�����ж�
        softsize = (u32)sLocalIap.Addr - (u32)sLocalIap.BackAddr;
        if((softsize > USER_BACK_PRO_SIZE) || (softsize > USER_APP_PRO_SIZE)){
            DtuCom->Rd.dtu.iap.sta  = IAP_END_ERR;                  //����ʱ����Ϣ����
            //uprintf("iap err.5");
            break;
        }
        
        //������������жϡ����Ѵ��С�ͳ����С�����
        if(     sLocalIap.SwVer == DtuCom->Rd.dtu.iap.para.SwVer    //����汾���
           ||   softsize  == DtuCom->Rd.dtu.iap.para.Size           //��д���ݴ�С���ڳ����С
           )    
        {
            sLocalIap.End       = 1;                                //�Ѿ��������
            Ctrl.sys.loadflg    = 1;                                //�������

            /**************************************************************
            * Description  : ���ݳ����С��ȷ���Ƿ�����Ϊboot��
            �������С��USER_BOOT_PRO_SIZE����Ϊ��boot����д��boot����
            * Author       : 2018/5/28 ����һ, by redmorningcn
            */
//            if(sLocalIap.Size +  2048 < USER_BOOT_PRO_SIZE )
//            {
//                u32 framnum     = (sLocalIap.Size + IAP_DATA_BUF_LEN -1)/ IAP_DATA_BUF_LEN;
//                u32 bootaddr    = USER_BOOT_START_ADDR;     //boot��ʼ��ַ
//                u32 backupaddr  = USER_BACK_START_ADDR;
//                for(u32 i= 0;i< framnum ;i++){
//                    BSP_FlashReadBytes(backupaddr,DtuCom->Rd.dtu.iap.buf,IAP_DATA_BUF_LEN);
//                    BSP_FlashWriteBytes(bootaddr,DtuCom->Rd.dtu.iap.buf,IAP_DATA_BUF_LEN);
//                    bootaddr    += IAP_DATA_BUF_LEN;
//                    backupaddr  += IAP_DATA_BUF_LEN;
//                }
//                sLocalIap.End = 0;                          //дboot�������ʶ   
//                //uprintf("boot ok");
//            }else{
//                //uprintf("app ok");
//            }
            
            /**************************************************************
            * Description  : �������
            * Author       : 2018/5/28 ����һ, by redmorningcn
            */
            sLocalIap.Idx = 0;          //�������
            //�����
            Chklen = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
            crc16 = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
            sLocalIap.Chk = crc16;
            
            sLocalIap.BackAddr = (u32)sLocalIap.BackAddr;                                //back����ַ
            sLocalIap.storeCrc = GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap)-2);  //����洢У��
            
            BSP_FlashWriteBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
        }else{
            DtuCom->Rd.dtu.iap.sta  = IAP_END_ERR;      //����ʱ����Ϣ����
            //uprintf("iap err.5");
        }
        
        break;
    default:
        DtuCom->Rd.dtu.iap.sta  = IAP_CODE_ERR;         //ָ�����
        break;
    }
}

/**************************************************************
* Description  : ��back�����ݴ���app��
* Author       : 2018/6/7 ������, by redmorningcn
*/
void    back_to_app(void)
{
    stcIAPPara      sLocalIap;
    u16             Chk;
    u16             storeCrc;
    u16             Chklen;
    u16             crc16;
        
    BSP_FlashReadBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
        
    Chklen      = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
    Chk         = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
    
    storeCrc    = GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap)-2);  //����洢У��
    
    /**************************************************************
    * Description  : �ж��Ƿ���Ҫת��
    * Author       : 2018/6/7 ������, by redmorningcn
    */
    if(     sLocalIap.End       == 1                //��������Ҫ����
       &&   sLocalIap.Chk       == Chk
       &&   sLocalIap.storeCrc  == storeCrc         //����ͨ��
       &&   sLocalIap.Size      != 0                //�������0
       ){                          
        u32 framnum     = (sLocalIap.Size + IAP_DATA_BUF_LEN -1)/ IAP_DATA_BUF_LEN;
        
        u32 appaddr     = USER_APP_START_ADDR;      //boot��ʼ��ַ
        u32 backupaddr  = sLocalIap.BackAddr;       //backup��ַ�ɳ���ȷ�� 
        
        for(u32 i= 0;i< framnum ;i++){
            BSP_FlashReadBytes(backupaddr,Ctrl.ComCtrl[0].Rd.dtu.iap.buf,IAP_DATA_BUF_LEN);
            BSP_FlashWriteBytes_Fast(appaddr,Ctrl.ComCtrl[0].Rd.dtu.iap.buf,IAP_DATA_BUF_LEN);
            appaddr     += IAP_DATA_BUF_LEN;
            backupaddr  += IAP_DATA_BUF_LEN;
        }
        
        sLocalIap.End = 0;                          //���������ת                                                  //��ʶ����
                                                                                    //�����
        Chklen = (u32)&sLocalIap.Chk - (u32)&sLocalIap;
        crc16 = GetCrc16Chk((uint8 *)&sLocalIap,Chklen);
        sLocalIap.Chk = crc16;
        
        sLocalIap.storeCrc = GetCrc16Chk((uint8 *)&sLocalIap,sizeof(sLocalIap)-2);  //����洢У��
        
        BSP_FlashWriteBytes(IAP_PARA_START_ADDR,(uint8 *)&sLocalIap,sizeof(stcIAPPara));
        
    }
}

/*******************************************************************************
 * 				end of file                                                    *
 *******************************************************************************/