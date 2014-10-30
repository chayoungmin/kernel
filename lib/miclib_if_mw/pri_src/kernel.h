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

// Included device driver
#include "gpio_drv.h"
#include "uart_drv.h"
#include "timer_drv.h"
#include "isp_drv.h"
#include "mot_drv.h"
#include "spi_drv.h"
#include "twi_drv.h"
#include "sens_drv.h"
#include "eeprom_drv.h"
#include "adc_drv.h"
#include "mdin3xx_drv.h"
#include "ad7393.h"
#include "Mot_drv.h"
#ifdef SUNNY_X20
#include "lvds_drv.h"
#endif

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
#define USE_TICK_FLAG_C_FUNC   	           1          /**< Tick관련 flag상태를 0보다 크면 C 함수를 0이면 매크로를 이용 */
#define USE_TICK_TOGGLE_LED                0

// watchdog timer
#define USE_WATCHDOG                       0          

// Terminal debug option
#define USE_KERNEL_DEBUG                   1

// ISR Service function
#define USE_VSYNC_ISR                      1
#define USE_VSYNC_SUB_ISR                  1
#define USE_HSYNC_ISR                      1
#define USE_FLD_ISR                        1
#define USE_EXT_SYNC_ISR                   0
#define USE_TICK_ISR                       1

// Kernel configuration
#define MAX_USER_TASKS                     2          /**< 사용자가 스케줄할 최대 Task 수 */

/*************************************************************************************************************
* DEFINES
*************************************************************************************************************/
// Only EN773
#define CPU_MEM_ISPM                       __attribute__((section(".ispmtext")))

/*************************************************************************************************************
* MACRO'S
*************************************************************************************************************/
#define CPU_INTERRUPT_DISABLE()            DI()                    
#define CPU_INTERRUPT_ENABLE()             EI()   

#define CPU_WDT_ENABLE()					WdtEna
#define CPU_WDT_DISABLE()					WdtDis
#define CPU_WDT_CLEAR()						WdtCfg(2000)

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

// Kernel debug service function (Declared by kern_debug.c)
KERNEL_EXT void DebugPrintf(const char *format, ...);
KERNEL_EXT void DebugScrPrintf(uint08 y,uint08 x,const char *format, ...);

#if USE_TICK_FLAG_C_FUNC > 0
KERNEL_EXT bool CPU_MEM_ISPM GetTick4msFlag(void);
KERNEL_EXT void ClearTick4msFlag(void);
KERNEL_EXT bool CPU_MEM_ISPM GetTick10msFlag(void);
KERNEL_EXT void ClearTick10msFlag(void);
KERNEL_EXT bool CPU_MEM_ISPM GetTick100msFlag(void);
KERNEL_EXT void ClearTick100msFlag(void);
KERNEL_EXT bool CPU_MEM_ISPM GetTick1secFlag(void);
KERNEL_EXT void ClearTick1secFlag(void);
#endif

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _MODULE_NAME_H_ */
/********************************************* END OF FILE **************************************************/

