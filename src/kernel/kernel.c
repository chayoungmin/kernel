/*********************************************************************************************************//**
* @mainpage 
*  MiCam Firmware Platform
* @section 소개
*  카메라 펌웨어 기본 플랫폼
* @section 작성일
*  2012.9.11 ~ 2012.11.16\n
*  2014.4.2 - update release
* @section 저작권
*  Copyright(c) 2012 by CNBTec co.ltd, All right reserved
*************************************************************************************************************/
/*********************************************************************************************************//**
* @file 
*  kernel.c
* @author
*  JangHo,Yoo (YJH)
* @date
*  2012.09.07
* @brief
*  이 파일은 마이컴팀 카메라 펌웨어 기본 플랫폼중 Kernel Layer를 기술한다.
*************************************************************************************************************/
/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include <stdlib.h>
#include "kernel.h"

// Add your header files


/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL CONSTANTS
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL DATA TYPES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL TABLES
*************************************************************************************************************/
// Scheduling task table
static void (*UserTaskSchdTbl[MAX_USER_TASKS])(void) = { NULL,
                                                         NULL };
                                   
/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/
static uint08 gCurTaskId;                                    /**< 현재 실행중인 Task ID                */

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/
// Callback functions for interrupt service routine
static void (*VsyncIsrCbk)(void);
static void (*VsyncSubIsrCbk)(void);
static void (*HsyncIsrCbk)(void);
static void (*FldSigIsrCbk)(void);
static void (*ExtSyncIsrCbk)(void);
static void (*TickTmrIsrCbk)(void);

// None schedule task functions
static void (*UserTaskStart)(void);
static void (*TickTmrPeriodeTask)(void);

// Schedule task function
static void (*UserSchdTask[MAX_USER_TASKS])(void);

// Local functions
static void InitKernelLayer(void);
static void InitMiddleLayer(void);
static void InitAppLayer(void);
static void KernelRegister( void (*task_start)(void), 
		                    void (*tick_tmr_periode)(void),
                            void (*vsync_isr)(void),
                            void (*vsync_sub_isr)(void),
                            void (*hsync_isr)(void),
                            void (*fld_isr)(void),
                            void (*ext_sync_isr)(void),
                            void (*tick_tmr_isr)(void));
static void DummyTask(void);
static void PreDeviceEnable(void);
static void PostDeviceEnable(void);

/*************************************************************************************************************
* LOCAL CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  Kernel layer에 대한 초기화\n
*  1. Task 초기화\n
*  2. Callback 함수 초기화\n
*  3. Kernel 변수 초기화\n
*  4. Tick Timer 초기화\n
*  5. Device Driver 초기화\n
*************************************************************************************************************/
static void InitKernelLayer(void)
{
	uint08 i;

	// Initialization none scheduling task
	UserTaskStart      = DummyTask;
	TickTmrPeriodeTask = DummyTask;

	// Initialization scheduling task
	for (i = 0; i < MAX_USER_TASKS; i++)
	{
		UserSchdTask[i] = DummyTask;
	}

	// Initialization callback function
	VsyncIsrCbk    = NULL;
	VsyncSubIsrCbk = NULL;
	HsyncIsrCbk    = NULL;
	FldSigIsrCbk   = NULL;
	ExtSyncIsrCbk  = NULL;
	TickTmrIsrCbk  = NULL;

	// Initialization kernel variables
	gCurTaskId     = 0;

	// TODO : Add your system tick timer initialization code
	
	// TODO : Add your device driver

	// TODO : Add your peripheral device driver

} /* InitKernelLayer */

/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  Middleware layer에 대한 초기화
*************************************************************************************************************/
static void InitMiddleLayer(void)
{
	//TODO : Add your initialization code
} /* InitMiddleLayer */

/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  User application layer에 대한 초기화
*************************************************************************************************************/
static void InitAppLayer(void)
{
	KernelRegister(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	
	//TODO : Add your initialization code
	KernelRegister(NULL,         /* task_start       */           
	               NULL,         /* tick_tmr_periode */
	               NULL,         /* vsync_isr        */
	               NULL,         /* vsync_sub_isr    */
	               NULL,         /* hsync_isr        */
	               NULL,         /* fld_isr          */
	               NULL,         /* ext_sync_isr     */
	               TickIsr );    /* tick_tmr_isr     */
} /* InitAppLayer */

/*********************************************************************************************************//**
* @param[in] task_start : user application의 시작 함수
* @param[in] tick_tmr_periode : tick에 대해 주기적으로 동작할 함수
* @param[in] vsync_isr : vertical sync 신호에 대한 인터럽트 서비스 함수
* @param[in] vsync_sub_isr : vertical sync 신호에 대한 여분의 인터럽트 서비스 함수
* @param[in] hsync_isr : horizontal sync 신호에 대한 인터럽트 서비스 함수
* @param[in] fld_isr : Field 혹은 Frame 신호에  대한 인터럽트 서비스 함수
* @param[in] ext_sync_isr : 외부 동기신호에 대한 인터럽트 서비스 함수
* @param[in] tick_tmr_isr : tick 에 대한 인터럽트 서비스 함수
* @retval none
* @brief
*   사용자에 의해 정의된 함수를 kernel에 등록한다.
*************************************************************************************************************/
static void KernelRegister( void (*task_start)(void),
                            void (*tick_tmr_periode)(void),
                            void (*vsync_isr)(void),
                            void (*vsync_sub_isr)(void),
                            void (*hsync_isr)(void),
                            void (*fld_isr)(void),
                            void (*ext_sync_isr)(void),
                            void (*tick_tmr_isr)(void))
{
	uint08 i;
	
	// Set callback function for user application tasks (none schedule task)
	UserTaskStart = task_start;
	if (UserTaskStart == NULL) 
	{
		UserTaskStart = DummyTask;
	}

	TickTmrPeriodeTask = tick_tmr_periode;
	if (TickTmrPeriodeTask == NULL)
	{
		TickTmrPeriodeTask = DummyTask;
	}

	// Set callback function for user application tasks (schedule task)
	for (i = 0; i < MAX_USER_TASKS; i++)
	{
		UserSchdTask[i] = UserTaskSchdTbl[i];
		
		if (UserSchdTask[i] == NULL)
		{
			UserSchdTask[i] = DummyTask;
		}
	}	
		
	// Set callback function for interrupt service routine
	VsyncIsrCbk    = vsync_isr;
	VsyncSubIsrCbk = vsync_sub_isr;
	HsyncIsrCbk    = hsync_isr;
	FldSigIsrCbk   = fld_isr;
	ExtSyncIsrCbk  = ext_sync_isr;
	TickTmrIsrCbk  = tick_tmr_isr;
} /* KernelRegister */

/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  Dummy task
*************************************************************************************************************/
static void DummyTask(void)
{
	//TODO : Add your dummy task code

	return;
} /* DummyTask */

/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief 
*  사용자 부트코드가 시작하기 전에 필요한 디바이스를 활성화 한다.
*************************************************************************************************************/
static void PreDeviceEnable(void)
{
	//TODO : Add your code

} /* PreDeviceEnable */

/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief 
*  사용자 부트코드가 완료된 후 디바이스를 활성화 한다.
*************************************************************************************************************/
static void PostDeviceEnable(void)
{
	//TODO : Add your code
} /* PostDeviceEnable */

/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  System kernel main function.
*************************************************************************************************************/
int main(void)
{
	CPU_INTERRUPT_DISABLE();                                 /* Disable global interrupt                       */

	// TODO : Add your device dependent initialization code

	InitKernelLayer();                                       /* Init kernel layer                              */
	InitMiddleLayer();                                       /* Init middleware layer                          */
	InitAppLayer();                                          /* Init application layer                         */

	CPU_INTERRUPT_ENABLE();                                	 /* Enable global interrupt                        */

#if USE_KERNEL_DEBUG > 0
	// TODO : Add your message
#endif
	PreDeviceEnable();                                       /* Enable device for user boot code               */
	UserTaskStart();                                         /* Start of user task <-- User Boot Code          */
	PostDeviceEnable();                                      /* Enable device for end user boot code           */
	
	while (1) 
	{
#if USE_WATCHDOG > 0
		//TODO : Add your watchdog code
		CPU_WDT_CLEAR();                                     /* Clear watchdog timer                           */
#endif

		TickTmrPeriodeTask();                                /* Periodic task execution base on the tick time  */

		(UserSchdTask[gCurTaskId])();                     /* User schedule task execution                   */
		if (++gCurTaskId >= MAX_USER_TASKS)                /* Task scheduling                                */
		{
			gCurTaskId = 0;
		}			
	} /* Endless main loop */
	
	return 0;
} /* main */

#if USE_VSYNC_ISR > 0
/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  Vsync interrupt service routine
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM  VsyncIsr(void)
{
	//TODO : Add your interrupt service routine

	if (VsyncIsrCbk != NULL)
	{
		VsyncIsrCbk();
	}
} /* VsyncIsr */
#endif

#if USE_VSYNC_SUB_ISR > 0
/*********************************************************************************************************//**
* @param[in]
* @retval none
* @brief
*  Vsync sub interrupt service routine (VsyncIsr과는 다른 edge type의 인터럽트)
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM VsyncSubIsr(void)
{
	//TODO : Add your interrupt service routine

	if (VsyncSubIsrCbk != NULL)
	{
		VsyncSubIsrCbk();
	}
} /* VsyncSubIsr */
#endif

#if USE_HSYNC_ISR > 0
/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Line interrupt service routine.
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM HsyncIsr(void)
{
	//TODO : Add your interrupt service routine

	if (HsyncIsrCbk != NULL)
	{
		HsyncIsrCbk();
	}
} /* HsyncIsr */
#endif

#if USE_FLD_ISR > 0
/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Field signal interrupt service routine. (Odd or Even)
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM FldSigIsr(void)
{
	//TODO : Add your interrupt service routine
	
	if (HsyncIsrCbk != NULL)
	{
		HsyncIsrCbk();
	}
} /* FldSigIsr */
#endif

#if USE_EXT_SYNC_ISR > 0
/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Interrupt service routine for external vertical drive signal.
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM ExtSyncIsr(void)
{
	//TODO : Added your interrupt service routine

	if (ExtSyncIsrCbk != NULL) 
	{
		ExtSyncIsrCbk();
	}
} /* ExtSyncIsr */
#endif

#if USE_TICK_ISR > 0
/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Interrupt service routine for tick timer.
* @attention
*  Call by exception handler. check your vector table.\n
*  You must check the compiler(linker).\n
*  if you required declaration, you need to declare the "#pragma comment" at the beginning of the function.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM TickTmrIsr(void)
{
	//TODO : Add your interrupt service routine

	if (TickTmrIsrCbk != NULL)
	{
		TickTmrIsrCbk();
	}
} /* TickTmrIsr */
#endif
/********************************************* END OF FILE **************************************************/

