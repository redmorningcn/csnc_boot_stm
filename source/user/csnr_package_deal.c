/**************************************************************
* Description  : ��ɳ�ϳ������첽ͨѶЭ��
* Author       : 2018/5/21 ����һ, by redmorningcn
*/

//#include    "csnr_package_deal.h"
#include    <includes.h>
#include    "string.h"

/**************************************************************
* Description  : ��д���ݵ�ַ��飬��ֹ�������
* Author       : 2018/6/1 ������, by redmorningcn
*/
#define     CSCN_MAX_BUF_LEN   (254)

//���ݴ��������stcCsnrProtocolPara��Ϣ�������ݴ����CNSR����
//
void	DataPackage_CSNC(strCsnrProtocolPara *sprotocolpara)
{
	unsigned char	SumCheck8;
	unsigned short	Crc16;
	unsigned short	AddHeadNum;
	unsigned short	i,j;
	unsigned char	ByteStation;
	unsigned char	DataLen = 0;

    /**************************************************************
    * Description  : �����ݳ����жϣ���ֹ���
    * Author       : 2018/6/1 ������, by redmorningcn
    */
    if(sprotocolpara->datalen > CSCN_MAX_BUF_LEN -12){
        sprotocolpara->rxtxlen = 0 ;
        return ;
    }

	//////////////////////////////////////////////׼������
	ByteStation = 0;
	sprotocolpara->rxtxbuf[ByteStation++] = FRAM_HERD0;
	sprotocolpara->rxtxbuf[ByteStation++] = FRAM_HERD1;
	sprotocolpara->rxtxbuf[ByteStation++] = sprotocolpara->sourceaddr;
	sprotocolpara->rxtxbuf[ByteStation++] = sprotocolpara->destaddr;    //��ַ
	sprotocolpara->rxtxbuf[ByteStation++] = sprotocolpara->framnum;
	sprotocolpara->rxtxbuf[ByteStation++] = (RS485_CHK_CRC<<4) + sprotocolpara->framcode;
	sprotocolpara->rxtxbuf[ByteStation++] = sprotocolpara->datalen;

	DataLen = sprotocolpara->datalen;

	SumCheck8 = GetCheckSumNR(&sprotocolpara->rxtxbuf[2],5);		   	//������У��

	sprotocolpara->rxtxbuf[ByteStation++] = SumCheck8;

	memcpy(&sprotocolpara->rxtxbuf[8],sprotocolpara->databuf,DataLen);
	ByteStation += DataLen;

	Crc16 = GetCrc16Chk(&sprotocolpara->rxtxbuf[2],6+sprotocolpara->datalen);

	sprotocolpara->rxtxbuf[ByteStation+1] = (unsigned char)Crc16;
	sprotocolpara->rxtxbuf[ByteStation]   = (unsigned char)(Crc16>>8);
	ByteStation += sizeof(Crc16);

	////////////////////////////////////////////////			    ����Э�鲹λ
	AddHeadNum = 0;
	for(i = 2; i< ByteStation + AddHeadNum;i++ )                    //	���ݣ�����λ FRAM_HERD0
	{
		if(sprotocolpara->rxtxbuf[i] == FRAM_HERD0)
		{
			for(j = ByteStation + AddHeadNum; j >i; j-- ) 	        //	��λ
			{
				sprotocolpara->rxtxbuf[j] = sprotocolpara->rxtxbuf[j-1];
			}

			i++;											        //������λ�ֽ�
			AddHeadNum++;
            /**************************************************************
            * Description  : �޶���Χ����ֹ���
            * Author       : 2018/6/1 ������, by redmorningcn
            */
            if(ByteStation + AddHeadNum > CSCN_MAX_BUF_LEN)
            {
                ByteStation = CSCN_MAX_BUF_LEN;
                AddHeadNum  = 0;
                break;
            }
		}
	}

	sprotocolpara->rxtxbuf[ByteStation +AddHeadNum] 	= FRAM_END0;
	sprotocolpara->rxtxbuf[ByteStation +AddHeadNum+1] 	= FRAM_END1;

	sprotocolpara->rxtxlen = (unsigned char)(ByteStation + AddHeadNum + 2);
}


//���ݽ���������ܵ������ݽ������stcCsnrProtocolPara��Ϣ
//�ܼ���������1�����򣬷���0
unsigned char   DataUnpack_CSNC(strCsnrProtocolPara *sprotocolpara)
{
    unsigned short        i,j,k;
    unsigned char			SumCheck8;
    unsigned char			Tmp;
    unsigned short			RecCRC16,Check16 = 0;
	int						DataLen = 0;

	if(sprotocolpara->rxtxlen< 2+6+2+2)
		return 0;
    /**************************************************************
    * Description  : �޶�����Χ����ֹ���
    * Author       : 2018/6/1 ������, by redmorningcn
    */
    if(sprotocolpara->rxtxlen > CSCN_MAX_BUF_LEN)
        sprotocolpara->rxtxlen = CSCN_MAX_BUF_LEN;
    
    
	for(j = 0;j < sprotocolpara->rxtxlen;j++ )						//ȥ�ظ�ͨѶ���ֽ�
	{
		if(
				sprotocolpara->rxtxbuf[j] 	== FRAM_HERD0
			&& 	sprotocolpara->rxtxbuf[j+1] == FRAM_HERD0
		   )
		{
			for(k = j;k < sprotocolpara->rxtxlen; k++)
			{
				Tmp	 = sprotocolpara->rxtxbuf[k+1];

				sprotocolpara->rxtxbuf[k] = Tmp;
			}
		}
	}

    for(i = 0; i < sprotocolpara->rxtxlen- 10;i++)					//ѭ������
    {
		if(		((sprotocolpara->rxtxbuf[i+0]) == FRAM_HERD0)
			&& 	((sprotocolpara->rxtxbuf[i+1]) == FRAM_HERD1)
		  )															//��ͷ
		{
			DataLen = sprotocolpara->rxtxbuf[i+6];

			if(
			 		(sprotocolpara->rxtxbuf[i+10+DataLen] 	!= FRAM_END0)	||
			 	 	(sprotocolpara->rxtxbuf[i+11+DataLen] 	!= FRAM_END1)
			 )
			 {


			 	i = (unsigned short)(i + 10 + DataLen);         //��ַ���Ի�֡β����������֡
			 	continue;
			 }
            
			DataLen = sprotocolpara->rxtxbuf[i+6];

			SumCheck8 = GetCheckSumNR((unsigned char *)&sprotocolpara->rxtxbuf[i+2],5);		   				//������У��

			RecCRC16 = ((unsigned short)sprotocolpara->rxtxbuf[i+8+DataLen]) *256 + sprotocolpara->rxtxbuf[i+9+DataLen];	//У��

			switch(sprotocolpara->rxtxbuf[i+5]>>4)              //У����㷨�ж�
			{
					case	RS485_CHK_SUM:
									//Check16 = GetCheckSum16(&sprotocolpara->rxtxbuf[i+2],6+DataLen);
									////PrintfCOM0(("\r\n 16λУ��ͣ�");
									break;
					case	RS485_CHK_CRC:
									Check16 = GetCrc16Chk(&sprotocolpara->rxtxbuf[i+2],(unsigned char )(6+DataLen));
									////PrintfCOM0(("\r\n CRCУ�飡");
									break;
					case	RS485_CHK_RESUM:
									break;
			}

			if(
						SumCheck8 == 	sprotocolpara->rxtxbuf[i+7]
					&& 	RecCRC16  ==	Check16
			  )
			{
				sprotocolpara->sourceaddr 	= sprotocolpara->rxtxbuf[i+2];
				sprotocolpara->destaddr 	= sprotocolpara->rxtxbuf[i+3];
				sprotocolpara->framnum   	= sprotocolpara->rxtxbuf[i+4];
				sprotocolpara->framcode  	= sprotocolpara->rxtxbuf[i+5]&0x0f;
				sprotocolpara->datalen     	= (unsigned char )DataLen;
                
                /**************************************************************
                * Description  : ��ֹ���
                * Author       : 2018/6/1 ������, by redmorningcn
                */
                if(DataLen < CSCN_MAX_BUF_LEN ){
                    memcpy(sprotocolpara->databuf,&sprotocolpara->rxtxbuf[i+8],DataLen);				//���ݿ���
                    return	1;
                }
			}
		}
	}

    return	0;
}


