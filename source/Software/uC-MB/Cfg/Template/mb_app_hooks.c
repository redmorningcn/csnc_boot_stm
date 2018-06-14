/*
************************************************************************************************************************
*                                                     uC/MB-III
*                                                The Real-Time Kernel
*
*                                  (c) Copyright 2009-2010; Micrium, Inc.; Weston, FL
*                          All rights reserved.  Protected by international copyright laws.
*
*                                                  APPLICATION HOOKS
*
* File    : MB_APP_HOOKS.C
* By      : JJL
* Version : V3.01.2
*
* LICENSING TERMS:
* ---------------
*               uC/MB-III is provided in source form to reg_baseistered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
************************************************************************************************************************
*/

#include <includes.h>


/*$PAGE*/
/*
************************************************************************************************************************
*                                              SET ALL APPLICATION HOOKS
*
* Description: Set ALL application hooks.
*
* Arguments  : none.
*
* Note(s)    : none
************************************************************************************************************************
*/

void  App_MB_SetAllHooks (void)
{
#if MB_CFG_APP_HOOKS_EN > 0u

#endif
}

/*$PAGE*/
/*
************************************************************************************************************************
*                                             CLEAR ALL APPLICATION HOOKS
*
* Description: Clear ALL application hooks.
*
* Arguments  : none.
*
* Note(s)    : none
************************************************************************************************************************
*/
CPU_INT08U  App_MB_RdNRegsHook    ( CPU_INT16U  reg_base,
                                    CPU_INT16U *prx_data,
                                    CPU_INT16U  reg_nbr,
                                    CPU_INT16U *perr)
{
#if MB_CFG_APP_HOOKS_EN > 0u
    /***********************************************
    * ������ ����ȷ�ϣ�ͨѶǰ�Ƚ�MB_DATA_ACC_PASSWORDд��reg0
    */
    if ( Ctrl.Para.dat.Password != MB_DATA_ACC_PASSWORD ) {
        *perr = MODBUS_ERR_ILLEGAL_DATA_ADDR;
        return 1;
    }
    
    /***********************************************
    * ������ �Ǹ���Ĵ���
    */
    if (reg_base < MODBUS_CFG_FP_START_IX) { 
        CPU_INT16U *preg        = (CPU_INT16U *)&Ctrl.Para.buf2[0];
        CPU_INT16U  reg         = reg_base + reg_nbr;
        CPU_INT16U  reg_max     = sizeof(Ctrl) / 2;
        /***********************************************
        * ������ ��ȡֵ
        */
        if ( reg < reg_max ) {
            preg    += reg_base;
            
            CPU_SR_ALLOC();
            CPU_CRITICAL_ENTER();
            
            for ( int i = 0; i < reg_nbr; i++,preg++ ) {
                prx_data[i]   = SW_INT16U(*preg);
            }
            CPU_CRITICAL_EXIT();
            *perr = MODBUS_ERR_NONE;
            return TRUE;
        } else {
        }
    /***********************************************
    * ������ ����Ĵ���
    */
    } else {
        CPU_INT16U  *preg       = (CPU_INT16U *)&Ctrl.Sen.Para.buf2[0];
        CPU_INT16U  reg         = reg_base + reg_nbr - MODBUS_CFG_FP_START_IX;
        CPU_INT16U  reg_max     = sizeof(UnionSenPara) / 2;
        /***********************************************
        * ������ ��ȡֵ
        */
        if ( reg < reg_max ) {
            preg    += reg_base - MODBUS_CFG_FP_START_IX;
            CPU_SR_ALLOC();
            CPU_CRITICAL_ENTER();
            
            for ( int i = 0; i < reg_nbr; i++,preg++ ) {
                prx_data[i]   = SW_INT16U(*preg);
            }
            
            CPU_CRITICAL_EXIT();
            *perr = MODBUS_ERR_NONE;
            return TRUE;
        } else {
        }
    }
    #endif
    return 0;
}

/*$PAGE*/
/*
************************************************************************************************************************
*                                             CLEAR ALL APPLICATION HOOKS
*
* Description: Clear ALL application hooks.
*
* Arguments  : none.
*
* Note(s)    : none
************************************************************************************************************************
*/
CPU_INT08U  App_MB_WrNRegsHook    ( CPU_INT16U reg_base,
                                    CPU_INT16U *prx_data,
                                    CPU_INT16U reg_nbr,
                                    CPU_INT16U  *perr)
{
#if MB_CFG_APP_HOOKS_EN > 0u

    /***********************************************
    * ������ ����ȷ�ϣ�ͨѶǰ�Ƚ�MB_DATA_ACC_PASSWORDд��reg0
    */
    if ( ( Ctrl.Para.dat.Password == MB_DATA_ACC_PASSWORD ) ||
         ( ( reg_base == 0 ) && ( *prx_data == MB_DATA_ACC_PASSWORD ) ) ) {
    } else {
        *perr = MODBUS_ERR_ILLEGAL_DATA_ADDR;
        return 1;
    }
    
    /***********************************************
    * ������ �Ǹ���Ĵ���
    */
    if (reg_base < MODBUS_CFG_FP_START_IX) { 
        CPU_INT16U *preg        = (CPU_INT16U *)&Ctrl.Para.buf2[0];
        CPU_INT16U  reg         = reg_base + reg_nbr;
        /***********************************************
        * ������ д��ֵ
        */
        if ( reg < sizeof(Ctrl) / 2 ) {
            preg    += reg_base;
            CPU_SR_ALLOC();
            CPU_CRITICAL_ENTER();
            for ( int i = 0; i < reg_nbr; i++,preg++ ) {
                *preg = SW_INT16U(prx_data[i]);
            }
            CPU_CRITICAL_EXIT();
            
            /***********************************************
            * ������ д����ʾģ��У׼����
            */
            CPU_INT16U __packed *pe     = &Ctrl.Para.buf2[127];
            CPU_INT16U __packed *pe2    = &Ctrl.Sen.Para.buf2[127];
            //CPU_INT16U __packed *pe3    = (CPU_INT16U *)&Ctrl.Tab.buf2;
            
            // ������ģ�����
            if ( ( preg >= Ctrl.Sen.Para.buf2 ) &&
               ( ( preg <= ( pe2 - reg_nbr * 2 ) ) ) ) {
                CPU_INT16U addr = 2 * ( preg - Ctrl.Sen.Para.buf2 );
                //CPU_INT08U *pb  = (CPU_INT08U *)&Ctrl.Sen.Para.buf2 + addr;
                
                //if ( !App_SetParaToSensor(1, 0, NULL, 256) ) {
                if ( !App_SetParaToSensor(1, addr, NULL, addr + reg_nbr<<1) ) {
                    *perr = MODBUS_ERR_ILLEGAL_DATA_VAL;
                    return TRUE;
                }
            // ����ģ�����
            } else if ( ( preg >= Ctrl.Para.buf2 ) &&
               ( ( preg <= ( pe - reg_nbr * 2 ) ) ) ) {
                CPU_INT16U addr = 2 * ( preg - Ctrl.Para.buf2 );
                //CPU_INT08U *pb  = (CPU_INT08U *)&Ctrl.Para.buf2 + addr;
                //if ( !App_SetParaToSensor(2, 0, NULL, 256) ) {
                if ( !App_SetParaToSensor(2, addr, NULL, addr + reg_nbr<<1) ) {
                    *perr = MODBUS_ERR_ILLEGAL_DATA_VAL;
                    return TRUE;
                }
            // �ݻ���
            }// else if ( ( preg > (CPU_INT16U *)&Ctrl.Tab ) &&
            //    ( ( preg <= ( pe3 - reg_nbr * 2 ) ) ) ) {
            //    
            //    CPU_INT16U addr = (preg - (CPU_INT16U *)&Ctrl.Tab)*2;
            //    CPU_INT08U *pb  = (CPU_INT08U *)&Ctrl.Tab + addr;
            //    //addr    += 256;
            //    
            //    if ( !App_SetParaToSensor(2, 256 + addr, NULL, addr + reg_nbr<<1) ) {
            //        *perr = MODBUS_ERR_ILLEGAL_DATA_VAL;
            //        return TRUE;
            //    }
            //}
            
            /***********************************************
            * ������ 
            */
            *perr = MODBUS_ERR_NONE;
            return TRUE;
        } else {
            //reg_val = 0;
            //*perr = MODBUS_ERR_ILLEGAL_DATA_ADDR;
        }
    /***********************************************
    * ������ ����Ĵ���
    */
    } else {
        CPU_INT16U  *preg       = (CPU_INT16U *)&Ctrl.Sen.Para.buf2[0];
        CPU_INT16U  reg         = reg_base + reg_nbr - MODBUS_CFG_FP_START_IX;
        
        /***********************************************
        * ������ ��ȡֵ
        */
        if ( reg < sizeof(UnionSenPara) / 2 ) {
            preg    += reg_base - MODBUS_CFG_FP_START_IX;
            CPU_SR_ALLOC();
            CPU_CRITICAL_ENTER();
            memcpy((CPU_INT16U *)&preg[reg_base], (CPU_INT16U *)&prx_data[0], reg_nbr);
            CPU_CRITICAL_EXIT();
            *perr = MODBUS_ERR_NONE;
            return TRUE;
        } else {
            //reg_val = 0;
            //*perr = MODBUS_ERR_ILLEGAL_DATA_ADDR;
        }
    }
#endif    
    return 0;
}

/*$PAGE*/
/*
************************************************************************************************************************
*                                                APPLICATION TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) This function is assumed to be called from the Tick ISR.
************************************************************************************************************************
*/

void  App_MB_TimeTickHook (void)
{

}
