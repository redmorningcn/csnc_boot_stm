/*******************************************************************************
 *   Filename:       bsp_flash.c
 *   Revised:        $Date: 2014-04-23
 *   Revision:       $
 *	 Writer:		 Wuming Shen.
 *
 *   Description:    
 *
 *   Notes:        
 *					   
 *			
 *   All copyrights reserved to Wuming Shen.
 *
 *******************************************************************************/

#define BSP_FLASH_MODULE_EN 1
#if BSP_FLASH_MODULE_EN > 0
/*******************************************************************************
 * INCLUDES
 */
#include "bsp_flash.h"
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>

UnionFlashBuf   FlashBuf;
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
/***********************************************
* ������
*/    

/*******************************************************************************
 * GLOBAL VARIABLES
 */

/*******************************************************************************
 * LOCAL FUNCTIONS
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */

 /*******************************************************************************
 * EXTERN FUNCTIONS
 */
 
/*******************************************************************************/


/*******************************************************************************
 * ��    �ƣ� FlashReadHalfWord()
 * ��    �ܣ� ��ȡָ����ַ��16λ����
 * ��ڲ�����
 * ���ڲ����� ��
 * ������ �ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
u16  FlashReadHalfWord(u32 addr)
{
	return *(vu16 *)addr;
}

/*******************************************************************************
 * ��    �ƣ� BSP_FlashRead()
 * ��    �ܣ� �ⲿ����
 * ��ڲ�����
 * ���ڲ����� ��
 * ������ �ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
void  BSP_FlashRead(u32 addr,u16 *pbuffer,u16 num)   	
{
	u16 i;
    
    FLASH_Unlock();                             // ����
	for(i = 0;i < num;i++) {
		*pbuffer++ = FlashReadHalfWord(addr);   //��ȡ2���ֽ�.
		addr += 2;                              //ƫ��2���ֽ�.	
	}
	FLASH_Lock();             				    // ����
}

/*******************************************************************************
 * ��    �ƣ� FlashRead()
 * ��    �ܣ� 
 * ��ڲ�����
 * ���ڲ����� ��
 * ������ �ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
void  FlashRead(u32 addr,u16 *pbuffer,u16 num)   	
{
	u16 i;
    
	for(i = 0;i < num;i++) {
		*pbuffer++ = FlashReadHalfWord(addr);   //��ȡ2���ֽ�.
		addr += 2;                              //ƫ��2���ֽ�.	
	}
}
/*******************************************************************************
 * ��    �ƣ� FlashWriteNoCheck()
 * ��    �ܣ� 
 * ��ڲ�����
 * ���ڲ����� ��
 * ������ �ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
u8  FlashWriteNoCheck(u32 addr,u16 *pbuffer,u16 num)
{
	u16 i;
    
	for(i = 0;i < num;i++) {
		//if ( FLASH_COMPLETE != FLASH_ProgramHalfWord (addr,pbuffer[i]) ) {
        //    return 0;
        //}
        FLASH_ProgramHalfWord (addr,pbuffer[i]);
		addr += 2;
	}
    return 1;
}

/*******************************************************************************
 * ��    �ƣ� FlashWrite()
 * ��    �ܣ� ��������д
 * ��ڲ�����
 * ���ڲ����� ��
 * ������ �ߣ� ������
 * �������ڣ� 2014-04-23
 * ��    �ģ� 
 * �޸����ڣ� 
 *******************************************************************************/
void  BSP_FlashWrite(u32 addr,u16 *pbuffer,u16 num)
{
//	u16  num_sector;  						        // �ڵڼ�ҳ
//	u16  offset_sector;  					        // ��һҳ��ƫ����
//	u16  num_last;    						        // ʣ�µİ���
//	u16  i;
//	/***********************************************
//    * ������
//    */
//    num_sector      = (addr - STM32_FLASH_BASE) / STM_SECTOR_SIZE;	   			// ��ȡ�ڼ�ҳ
//	offset_sector   = ((addr - STM32_FLASH_BASE) % STM_SECTOR_SIZE) / 2;  	    // ��ȡƫ������16���ֽ�Ϊ��λ
//	num_last        = STM_SECTOR_SIZE / 2 - offset_sector;                     	// ���ʣ�µİ���
//	
//    FLASH_Unlock();                                 // ����
//	/***********************************************
//    * ������
//    */
//    if(num <= num_last)  
//      num_last      = num;		                    // ����һ��д��
//    /***********************************************
//    * ������
//    */
//	for(;;)	{									        // ��ʼ��ͣ��д
//		FlashRead(num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE,FlashBuf.buf2,STM_SECTOR_SIZE / 2);  // ����һҳ
//		for(i = 0;i < num_last;i++) {
//			if(FlashBuf.buf2[offset_sector + i] != 0xffff) break;	
//		}
//		if(i < num_last) {						        // ��Ҫ����
//			FLASH_ErasePage (num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE);  // ����
//			for(i = 0;i < num_last;i++) {
//				FlashBuf.buf2[offset_sector + i] = pbuffer[i];	                // ��Ҫд���������������
//			}
//			FlashWriteNoCheck(num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE,FlashBuf.buf2,STM_SECTOR_SIZE / 2);               //д��������		
//		} else {								        // ����Ҫ����
//			FlashWriteNoCheck(addr,pbuffer,num_last);	// ֱ�ӽ�Ҫд�������д��flash
//		}
//        /***********************************************
//        * ������
//        */
//		if(num_last == num) { 
//            break;                                      // д��������
//		} else {                                        // û��д�����
//			num_sector     += 1;    				    // ҳ��һ
//			offset_sector   = 0;  				        // ƫ��Ϊ0
//			pbuffer        += num_last;
//			addr           += num_last * 2;
//			num            -= num_last;    				// ����Ҫд�������
//            
//			if(num > (STM_SECTOR_SIZE / 2))  
//                num_last = STM_SECTOR_SIZE / 2;
//			else  
//              num_last = num;   			            // ����num_last		
//		}		
//	}
//    
//	FLASH_Lock();             					        // ����
    
	u16  num_sector;                                    //�ڵڼ�ҳ
	u16  offset_sector;                                 //��һҳ��ƫ����
	u16  num_last;                                      //ʣ�µİ���
	u16  i;
	num_sector      =  (addr - STM32_FLASH_BASE) / STM_SECTOR_SIZE;	        //��ȡ�ڼ�ҳ
	offset_sector   =  ((addr - STM32_FLASH_BASE) % STM_SECTOR_SIZE) / 2;   //��ȡƫ������16���ֽ�Ϊ��λ
	num_last        = 	STM_SECTOR_SIZE / 2 - offset_sector;                //���ʣ�µİ���
	FLASH_Unlock();                                     //����
	if(num <= num_last)  num_last = num;		        //����һ��д��
	
    for(;;)	{									        //��ʼ��ͣ��д
		FlashRead(num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE,FlashBuf.buf2,STM_SECTOR_SIZE / 2);  //����һҳ
		for(i = 0;i < num_last;i++) {
			if(FlashBuf.buf2[offset_sector + i] != 0xffff) break;	
		}
		if(i < num_last) { 					//��Ҫ����
			FLASH_ErasePage (num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE);                      //����
			for(i = 0;i < num_last;i++) {
				FlashBuf.buf2[offset_sector + i] = pbuffer[i];	               //��Ҫд���������������
			}
			FlashWriteNoCheck(num_sector * STM_SECTOR_SIZE + STM32_FLASH_BASE,FlashBuf.buf2,STM_SECTOR_SIZE / 2);               //д��������		
		} else {								    //����Ҫ����
		
			FlashWriteNoCheck(addr,pbuffer,num_last);	//ֱ�ӽ�Ҫд�������д��flash
		}
		if(num_last == num)  
            break;                                  //д��������
		else  {                                     //û��д�����
			num_sector += 1;    //ҳ��һ
			offset_sector = 0;  //ƫ��Ϊ0
			pbuffer += num_last;
			addr += num_last * 2;
			num -= num_last;    //����Ҫд�������
			if(num > (STM_SECTOR_SIZE / 2))  num_last = STM_SECTOR_SIZE / 2;
			else  num_last = num;   //����num_last		
		}		
	}
    
	FLASH_Lock();             //����
}

/*******************************************************************************
* ��    �ƣ� BSP_FLASH_ReadPage
* ��    �ܣ� ��һҳ���ݣ���ʼ��ַ��ҳ��
* ��ڲ����� addr FLASH��ַ  pbuf �� ��ȡ�ֽڵ����� len : ����Ĵ�С
* ���ڲ����� 0���������󣩣�1�������ɹ���
* ���� ���ߣ� wumingshen
* �������ڣ� 2015-10-20
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
u8 BSP_FLASH_ReadPage( u32 addr , u8 *pbuf, u16 len )
{
    u16    size   = 0;

    if ( len > STM_SECTOR_SIZE )
      return 0;

    u16 *p      = (u16 *)pbuf;
    
    for ( ; size < len ; size += 2 ) {
		*p++     = *(vu16 *)addr;
		addr    += 2;	
	}
    
    return size;
}

/*******************************************************************************
* ��    �ƣ� BSP_FLASH_WritePage
* ��    �ܣ� дһҳ���ݣ���ʼ��ַ��ҳ��
* ��ڲ����� addr:  FLASH��ַ  pbuf: д���ֽڵ����� len: ����Ĵ�С
* ���ڲ����� 0���������󣩣�1�������ɹ���
* ���� ���ߣ� wumingshen
* �������ڣ� 2015-10-20
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
u8 BSP_FLASH_WritePage( u32 addr , u8 *pbuf, u16 len )
{
    u16    size   = 0;

    if ( len > STM_SECTOR_SIZE )
      return 0;

    u16 *p      = (u16 *)pbuf;
    s8  retrys;
    
    for ( ; size < len ; size += 2 ) {
        retrys  = 5;
        do {
            FLASH_ProgramHalfWord(addr,*(u16 *)p);
            if (*(u16 *)addr == *(u16 *)p) {
                break;
            } else if ( 1 == retrys ) {
                return size;
            } 
        } while ( --retrys );
        
		addr    += 2;
        p++;
	}
            
    return size;
}

/*******************************************************************************
* ��    �ƣ� BSP_FlashWriteBytes
* ��    �ܣ� д����ֽ�
* ��ڲ����� addr�� FLASH��ַ  pbuf ��д���ֽڵ����� len : ����Ĵ�С
* ���ڲ����� 0���������󣩣�1�������ɹ���
* ���� ���ߣ� wumingshen
* �������ڣ� 2015-10-20
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
u16     BSP_FlashWriteBytes     (u32 addr, u8 *pbuf, u16 len)
{
    u16      bytes   = 0;
    /***********************************************
    * ������ ����ַ�Ƿ���������������ֱ�ӷ���
    */
    if ( (addr + len) > (FLASH_SIZE_EEP) )
        return 0;

    u16    copyLen;                                     // Ҫ���Ƶĳ���
    u32    pageAddr;
    u16    size    = 0;                                 // һ��д�볤��
    u32 page    =   addr / STM_SECTOR_SIZE;             // д���ַ����ҳ����ԣ�
                    addr    += PARAM_START_ADDR;        // ת���ɾ��Ե�ַ
    
	FLASH_Unlock();             				        // ����
    /***********************************************
    * ������ ��ҳ�׿�ʼ����ȡ֮ǰ���ݽ������
    */
    if ( ( addr % STM_SECTOR_SIZE ) != 0 ) {
        size        = STM_SECTOR_SIZE - ( addr % STM_SECTOR_SIZE );
        copyLen     = STM_SECTOR_SIZE - size;
        pageAddr    = PARAM_START_ADDR + page * STM_SECTOR_SIZE;
        // ��ȡ��ǰҳ����
        BSP_FLASH_ReadPage(pageAddr, FlashBuf.buf1, STM_SECTOR_SIZE);

        if ( size > len )
            size = len;
        // �������ڵ�ǰҳ�����ݵ���������
        memcpy(&FlashBuf.buf1[copyLen], pbuf, size);
        // ��ҳ̽�յ�ǰҳ
		FLASH_ErasePage ( pageAddr );
        // ��������������д�뵱ǰҳ
        BSP_FLASH_WritePage( pageAddr , FlashBuf.buf1 , STM_SECTOR_SIZE );
        // Դ���ݵ�ַ��д���ַ��д���ֽ�������size��δд���ݳ��ȼ���size
        addr    += size;
        pbuf    += size;
        bytes   += size;
        len     -= size;
    }

    /***********************************************
    * ������ ҳ�׿�ʼ����ҳ
    */
    size = len / STM_SECTOR_SIZE;
    while ( size > 0 ) {
        // ̽�յ�ǰҳ
		FLASH_ErasePage (addr);
        // д�뵱ǰ����ҳ
        BSP_FLASH_WritePage( addr , (u8 *)pbuf, STM_SECTOR_SIZE );
        // Դ���ݵ�ַ��д���ַ��д���ֽ�������STM_SECTOR_SIZE��δд���ݳ��ȼ���STM_SECTOR_SIZE
        addr    += STM_SECTOR_SIZE;
        pbuf    += STM_SECTOR_SIZE;
        bytes   += STM_SECTOR_SIZE;
        len     -= STM_SECTOR_SIZE;
        // ҳ����1
        size    -= 1;
    }

    /***********************************************
    * ������ ҳ�׿�ʼ������һҳ
    */
    if ( len > 0 ) {
        size        = STM_SECTOR_SIZE - ( addr % STM_SECTOR_SIZE );
        copyLen     = STM_SECTOR_SIZE - size;
        pageAddr    = addr - copyLen;
        
        BSP_FLASH_ReadPage(pageAddr, FlashBuf.buf1, STM_SECTOR_SIZE);

        if ( size > len )
            size = len;
        // �������ڵ�ǰҳ�����ݵ���������
        memcpy(&FlashBuf.buf1[copyLen],pbuf,size);

        // ��ҳ̽�յ�ǰҳ
		FLASH_ErasePage (pageAddr);
        // ��������������д�뵱ǰҳ
        BSP_FLASH_WritePage( pageAddr , (u8 *)FlashBuf.buf1 , STM_SECTOR_SIZE );
        bytes   += len;
    }

	FLASH_Lock();             				    // ����
    return(bytes);
}

/*******************************************************************************
* ��    �ƣ� BSP_FlashReadBytes
* ��    �ܣ� ������ֽڣ�������2�ı�����
* ��ڲ����� addr�� FLASH��ַ  pbuf ��д���ֽڵ����� len : ����Ĵ�С��2�ı�����
* ���ڲ����� 0���������󣩣�1�������ɹ���
* ���� ���ߣ� wumingshen
* �������ڣ� 2015-10-20
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
u16     BSP_FlashReadBytes      (u32 addr, u8 *pbuf, u16 len)
{ 
    addr         = (PARAM_START_ADDR + addr);
    
	FLASH_Unlock();             					        // ����

    u16 *p      = (u16 *)pbuf;
    u16 size    = 0;
    
    for ( ; size < len ; size += 2 ) {
		*p++     = *(vu16 *)addr;
		addr    += 2;	
	}
    
	FLASH_Lock();             					            // ����
    
    return len;
} 

/*******************************************************************************
 * 				end of file
 *******************************************************************************/ 
#endif