/**********************************************************************************************************//**
* @file kernel.h
* @author 
*  JangHo, Yoo (YJH)
* @date
*  2012.09.07
* @brief
**************************************************************************************************************/
/*************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _KERNEL_H_
#define _KERNEL_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"
#include "miclib_misc.h"
#include "cpu_d.h" 

//-----------------------------------------------------------------------------------------------------------//
// INCLUDE DEVICE DRIVER
//-----------------------------------------------------------------------------------------------------------//
#include "gpio_drv.h"
#include "spi_drv.h"
#include "uart_drv.h"
#include "adc_drv.h"

/*************************************************************************************************************
* EXTERNS
*************************************************************************************************************/
#ifdef KERNEL_EXTERN
#define KERNEL_EXT
#else
#define KERNEL_EXT                   extern
#endif

/*************************************************************************************************************
* CONFIGURATION
*************************************************************************************************************/
// tick time management
#define USE_TICK_FLAG_C_FUNC   	           1          /**< C function for tick flag : Unused = 0  */

// Watchdog timer
#define USE_WATCHDOG                       1          /**< Watchdog timer : Unused = 0            */

// Terminal debug option
#define USE_KERNEL_DEBUG                   1          /**< Kernel debug function : Unused = 0     */

// ISR Service function
#define USE_VSYNC_ISR                      1          /**< Vsync ISR : Unused = 0                 */
#define USE_VSYNC_SUB_ISR                  1          /**< Reverse Vsync ISR : Unused = 0         */
#define USE_HSYNC_ISR                      1          /**< Horizontal Sync ISR : Unused = 0       */
#define USE_FLD_ISR                        1          /**< Field or Frame signal ISR : Unused = 0 */
#define USE_EXT_SYNC_ISR                   1          /**< External sync ISR : Unused = 0         */
#define USE_TICK_ISR                       1          /**< Tick ISR : Unused = 0                  */

// Kernel configuration
#define MAX_USER_TASKS                     2          /**< Maximum task number by the user        */

/*************************************************************************************************************
* DEFINES
*************************************************************************************************************/
// Only EN773
#define CPU_MEM_ISPM                       __attribute__((section(".ispmtext")))

/*************************************************************************************************************
* MACRO'S
*************************************************************************************************************/
#define	CPU_INTERRUPT_DISABLE()			   DI()
#define CPU_INTERRUPT_ENABLE()			   EI()

#define CPU_WDT_ENABLE()				   WdtEna
#define CPU_WDT_DISABLE()				   WdtDis
#define CPU_WDT_CLEAR()					   WdtCfg(2000)

// Time tick flag service
#if USE_TICK_FLAG_C_FUNC == 0
#define GET_TICK_4MS_FLAG()                Tick4msFlag
#define CLEAR_TICK_4MS_FLAG()              (Tick4msFlag = FALSE)
#define GET_TICK_10MS_FLAG()               Tick10msFlag
#define CLEAR_TICK_10MS_FLAG()             (Tick10msFlag = FALSE)
#define GET_TICK_100MS_FLAG()              Tick100msFlag
#define CLEAR_TICK_100MS_FLAG()            (Tick100msFlag = FALSE)
#define GET_TICK_1SEC_FLAG()               Tick1secFlag
#define CLEAR_TICK_1SEC_FLAG()             (Tick1secFlag = FALSE)
#endif

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* FUNCTION PROTOTYPES
*************************************************************************************************************/
// Kernel Interrupt Service Function
void VsyncIsr(void);
void VsyncSubIsr(void);
void HsyncIsr(void);
void FldSigIsr(void);
void ExtSyncIsr(void);
void TickTmrIsr(void);

// Tick service Function (Declared by kern_time.c)
void InitTickTimerConfig(void);
void StartTickTimer(void);
void StopTickTimer(void);
void WaitTickCount(uint32 n_tick);
void TickIsr(void);

#if USE_KERNEL_DEBUG > 0
// Kernel debug service function (Declared by kern_debug.c)
void DebugPrintf(const char *format, ...);
#endif

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _MODULE_NAME_H_ */
/********************************************* END OF FILE **************************************************/

