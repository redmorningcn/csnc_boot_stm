#ifndef	__GLOBLES_H__
#define	__GLOBLES_H__
/*********************************************************************
*   Filename:       Globles.h
*   Revised:        $Date: 2009-01-08	20:15 (Fri) $
*   Revision:       $
*   Writer:         $wumingshen
*
*
*   Notes:
*					QQ:261313062
*
*
*********************************************************************/

/*********************************************************************
* INCLUDES
*/

/*********************************************************************
* CONSTANTS
*/
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ON
#define ON  1
#endif

#ifndef OFF
#define OFF 0
#endif


/*********************************************************************
* TYPEDEFS
*/
/***********************************************
* �������������Ͷ���
*/
typedef  unsigned char		    BOOL;
typedef  unsigned char		    BYTE;
typedef  unsigned char          uint8;        	// �޷���8λ���ͱ���
typedef  signed   char  		int8;           // �з���8λ���ͱ���
typedef  unsigned short		    WORD;
typedef  unsigned short 		uint16;         // �޷���16λ���ͱ���
typedef  signed   short 		int16;          // �з���16λ���ͱ���
typedef  unsigned long   		uint32;         // �޷���32λ���ͱ���
typedef  signed   long   		int32;          // �з���32λ���ͱ���
typedef  float          		fp32;           // �����ȸ�������32λ���ȣ�
typedef  double         		fp64;           // ˫���ȸ�������64λ���ȣ�

#define	    null	            ((void *)0)

#define     CHAR                char
#define     PCHAR               char*
#define     CONST               const

#define	    INT8S		        int8
#define	    INT08S		        int8
#define     pINT8S		        INT8S*
#define	    INT8U		        uint8
#define	    INT08U		        uint8
#define     pINT8U		        INT8U*
#define	    INT16S		        int16
#define     pINT16S		        INT16S*
#define	    INT16U		        uint16
#define	    pINT16U		        INT16U*
#define	    INT32S		        int32
#define	    pINT32S		        INT32S*
#define	    INT32U		        uint32
#define	    pINT32U		        INT32U*
#define     fp32                FP32
#define     fp64                FP64

/* ------------------------------------------------------------------------------------------------
 *                                             Macros
 * ------------------------------------------------------------------------------------------------
 */
/***********************************************
* ���������ú궨��
*/
#ifndef BV
#define BV(n)      (1 << (n))
#endif

#ifndef BF
#define BF(x,b,s)  (((x) & (b)) >> (s))
#endif

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif


 /***********************************************
 * ������������ϲ��
 */
 #define    BUILD_RGB(R, G, B)              \
                                            ((INT32U)((INT32U)(((INT08U)B) & 0x00FF) + \
                                            ((INT32U)(((INT08U)G) & 0x00FF) << 8) + \
                                            ((INT32U)(((INT08U)R) & 0x00FF) << 16)))
                                                
 #define    BUILD_INT32U(Byte0, Byte1, Byte2, Byte3) \
                                            ((INT32U)((INT32U)((Byte0) & 0x00FF) + \
                                            ((INT32U)((Byte1) & 0x00FF) << 8) + \
                                            ((INT32U)((Byte2) & 0x00FF) << 16) + \
                                            ((INT32U)((Byte3) & 0x00FF) << 24)))                                                

 #define    BUILD_INT32U16(loByte, hiByte) \
                                            ((INT32U)(((loByte) & 0xFFFF) + \
                                            (((hiByte) & 0xFFFF) << 16)))
                                                
 #define    BUILD_INT16U(loByte, hiByte) \
                                            ((INT16U)(((loByte) & 0x00FF) + \
                                            (((hiByte) & 0x00FF) << 8)))
                                                

 #define    B3_INT32U(a)		            (((a) >> 24) & 0xFF)
 #define    B2_INT32U(a)                    (((a) >> 16) & 0xFF)
 #define    B1_INT32U(a)                    (((a) >> 8) & 0xFF)
 #define    B0_INT32U(a)                    ((a) & 0xFF)

 #define    HI_INT32U(a)                    (((a) >> 16) & 0xFFFF)
 #define    LO_INT32U(a)                    ((a) & 0xFFFF)
                                                
 #define    HI_INT16U(a)                    (((a) >> 8) & 0xFF)
 #define    LO_INT16U(a)                    ((a) & 0xFF)
                                                


 #define    BUILD_INT8U(hiByte, loByte) \
                                            ((INT8U)(((loByte) & 0x0F) + \
                                            (((hiByte) & 0x0F) << 4)))

 #define    HI_INT8U(a)			            (((a) >> 4) & 0x0F)
 #define    LO_INT8U(a)			            ((a) & 0x0F)
 #define    SW_INT16U(a)                    (HI_INT16U(a) + (LO_INT16U(a)<<8))

 #define    FloatToINT16U(a)	            (INT16U)(((INT16U)a << 2) + \
					                        (((INT16U)(a*100) % 100 )/ 25))
 #define    INT16UToFloat(a)	            (float)(( a >> 2 ) + \
					                        ((float)( a & 0x0003 ) * 0.25) )

/* takes a byte out of a uint32 : var - uint32,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32( var, ByteNum ) \
                                            (uint8)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
                                              ((uint32)((uint32)((Byte0) & 0x00FF)   \
                                            + ((uint32)((Byte1) & 0x00FF) << 8)      \
                                            + ((uint32)((Byte2) & 0x00FF) << 16)     \
                                            + ((uint32)((Byte3) & 0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte) \
                                            ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a)                        (((a) >> 8) & 0xFF)
#define LO_UINT16(a)                        ((a) & 0xFF)


#define BUILD_UINT8(hiByte, loByte) \
                                            ((uint8)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a)                         (((a) >> 4) & 0x0F)
#define LO_UINT8(a)                         ((a) & 0x0F)
              
// Write the 32bit value of 'val' in little endian format to the buffer pointed
// to by pBuf, and increment pBuf by 4
#define UINT32_TO_BUF_LITTLE_ENDIAN(pBuf,val) \
	do { \
		*(pBuf)++ = (((val) >>  0) & 0xFF); \
		*(pBuf)++ = (((val) >>  8) & 0xFF); \
		*(pBuf)++ = (((val) >> 16) & 0xFF); \
		*(pBuf)++ = (((val) >> 24) & 0xFF); \
	} while (0)

// Return the 32bit little-endian formatted value pointed to by pBuf, and increment pBuf by 4
#define BUF_TO_UINT32_LITTLE_ENDIAN(pBuf) (((pBuf) += 4), BUILD_UINT32((pBuf)[-4], (pBuf)[-3], (pBuf)[-2], (pBuf)[-1]))


/*
 *  This macro is for use by other macros to form a fully valid C statement.
 *  Without this, the if/else conditionals could show unexpected behavior.
 *
 *  For example, use...
 *    #define SET_REGS()  st( ioreg1 = 0; ioreg2 = 0; )
 *  instead of ...
 *    #define SET_REGS()  { ioreg1 = 0; ioreg2 = 0; }
 *  or
 *    #define  SET_REGS()    ioreg1 = 0; ioreg2 = 0;
 *  The last macro would not behave as expected in the if/else construct.
 *  The second to last macro will cause a compiler error in certain uses
 *  of if/else construct
 *
 *  It is not necessary, or recommended, to use this macro where there is
 *  already a valid C statement.  For example, the following is redundant...
 *    #define CALL_FUNC()   st(  func();  )
 *  This should simply be...
 *    #define CALL_FUNC()   func()
 *
 * (The while condition below evaluates false without generating a
 *  constant-controlling-loop type of warning on most compilers.)
 */
#define st(x)      do { x } while (__LINE__ == -1)

/*********************************************************************
* MACROS
*/
/***********************************************
* ������
*/
#define    SetMCUPowerDown()		       { _nop_(); _nop_(); PCON = 0X02; _nop_(); _nop_(); }

#define    DIR_OUT                         1
#define    DIR_IN                          0

#define    DirBit( byte, bits, dir )       ( ( dir > 0 ) ? ( byte |= bits ) : ( byte &= ~bits ) )
#define    DirPort( port,bits, dir )       ( ( dir > 0 ) ? ( port |= bits ) : ( port &= ~bits ) )

#define    SetBit( byte, bits )		       ( byte |= bits )
#define    ClrBit( byte, bits )		       ( byte &= ~bits )
#define    GetBit( byte, bits )		       ( byte & bits )

#define    SetBits                          SetBit
#define    ClrBits                          ClrBit
#define    GetBits                          GetBit

#define    SetLedOnNms( led, msec )	        { BSP_LED_On(led); OSTimeDly( msec ); BSP_LED_Off(led);}
#define    SetLedOnNs(  led, sec )	        { BSP_LED_On(led); OSTimeDlyHMSM( 0,0,sec,0 );BSP_LED_Off(led); }

#define    SetBitOnNms( port, bits, msec )	{ GPIO_SetBits(port,bits); OSTimeDly( msec );  GPIO_SetBits(port,bits); }
#define    SetBitOnNs( port, bits, sec )	{ GPIO_SetBits(port,bits); OSTimeDlyHMSM( 0,0,sec,0 );  GPIO_SetBits(port,bits); }

#define    SetBitOffNms( port, bits, msec ) { GPIO_SetBits(port,bits); OSTimeDly( msec ); GPIO_ResetBits(port,bits);  }
#define    SetBitOffNs( port, bits, sec )	{ GPIO_SetBits(port,bits); OSTimeDlyHMSM( 0,0,sec,0 );  GPIO_ResetBits(port,bits); }

#define    SystemReset			            BSP_RST_SystemRst
#define    ResetWdt                         BSP_WDT_Rst
#define    WdtReset			                ResetWdt


/***********************************************
* ������ IAR�����Ż��ȼ�ָ���ָ���������߱������Ż��ȼ�
*/
#ifndef __IAR_OPTIMIZE_H__
#define __IAR_OPTIMIZE_H__

#define OPTIMIZE_SIZE_NONE      _Pragma("optimize=z 2")
#define OPTIMIZE_SIZE_LOW       _Pragma("optimize=z 3")
#define OPTIMIZE_SIZE_MEDIUM    _Pragma("optimize=z 6")
#define OPTIMIZE_SIZE_HIGH      _Pragma("optimize=z 9")

#define OPTIMIZE_SPEED_NONE     _Pragma("optimize=s 2")
#define OPTIMIZE_SPEED_LOW      _Pragma("optimize=s 3")
#define OPTIMIZE_SPEED_MEDIUM   _Pragma("optimize=s 6")
#define OPTIMIZE_SPEED_HIGH     _Pragma("optimize=s 9")

#define OZ_2                    OPTIMIZE_SIZE_NONE
#define OZ_3                    OPTIMIZE_SIZE_LOW
#define OZ_6                    OPTIMIZE_SIZE_MEDIUM
#define OZ_9                    OPTIMIZE_SIZE_HIGH

#define OS_2                    OPTIMIZE_SPEED_NONE
#define OS_3                    OPTIMIZE_SPEED_LOW
#define OS_6                    OPTIMIZE_SPEED_MEDIUM
#define OS_9                    OPTIMIZE_SPEED_HIGH

#define OPTIMIZE_NONE           _Pragma("optimize=none")
#define OPTIMIZE_LOW            _Pragma("optimize=low")
#define OPTIMIZE_MEDIUM         _Pragma("optimize=medium")
#define OPTIMIZE_HIGH           _Pragma("optimize=high")

#endif
/*********************************************************************
* GLOBAL FUNCTIONS
*/

/*********************************************************************
* EXTERN VARIABLES
*/
/***********************************************
* ������
*/
void        Delay_Nus               (INT32U  dly);
void        Delay_Nms               (INT32U  dly);
void        Delay_Ns                (INT32U  dly);
/*********************************************************************
* EXTERN FUNCTIONS
*/
void        BSP_RST_SystemRst	    (void);
void        Beep                    (INT32U flag);

INT16U      SWAP_INT16U             (INT16U value);
void        uprintf                 (const char *fmt, ...);
int         usprintf                (char *buf, const char *fmt, ...);
/*********************************************************************
* 				end of file
*********************************************************************/
#endif	/* GLOBLES_H */
