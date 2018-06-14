/*******************************************************************************
 *   Filename:       app_chk.h
 *   Revised:        $Date: 2017-07-26$
 *   Revision:       $
 *	 Writer:		 Wuming Shen.
 *
 *   Description:
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *   All copyrights reserved to Wuming Shen.
 *
 *******************************************************************************/
#ifndef	_CRCCHK_H
#define	_CRCCHK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef   APP_GLOBALS
#define  APP_EXT
#else
#define  APP_EXT  extern
#endif
    
/*******************************************************************************
 * INCLUDES
 */
#include <includes.h>

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
 
/*******************************************************************************
 * LOCAL FUNCTIONS
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 *
 * 返回类型         函数名称                入口参数
 */
 u16    GetCrc16Chk             (u8 *buf, u16 len);
 u16    GetCrc16Chk2            (u8 *buf, u16 len);
 u16    GetMBCrc16Chk           (u8 *buf, u16 len);
 u16    GetMBCrc16Up            (u8 *buf, u16 len);
 u8     GetSumChk               (u8 *buf, u16 len);
 u8     GetSumXorChk            (u8 *buf, u16 len);
 u16    GetSum16Chk             (u8 *buf, u16 len);
 u16    GetSum16XorChk          (u8 *buf, u16 len);
 u8     GetCheckSumNR           (u8  Buf[], u32 Len);
 u64    GetCrc32Chk             (u64 m_CRC, u8  *buf, u16 len);
/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif



