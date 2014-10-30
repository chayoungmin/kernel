/*********************************************************************************************************//**
* @file 
*  cpu_i.c
* @author
*  JangHo, Yoo (YJH)
* @date
*  2012.09.27
* @brief
*  이 파일은 타켓팅된 CPU의 인터럽드 항목과 에외처리에 대해 기술한다.
*************************************************************************************************************/
/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "kernel.h"
#include "cpu_d.h"

/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/
static void SetIrqEnable(uint32 in, var_stat en);
static void SetIrqMask(uint32 in, var_stat en);
static void SetIrqEdgeMode(uint32 in, var_stat en);

static void DummyIsr(void);
static void DoubleFaultIsr(void);
static void BusErrorException(void);
static void CP0Exception(void);
static void UndefInst(void);
static void UnimpltedInst(void);
/*************************************************************************************************************
* LOCAL CONSTANTS
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL DATA TYPES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL TABLES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/

/*************************************************************************************************************
* GLOBAL FUNCTION PROTOTYPES
*************************************************************************************************************/
extern void Reset_Start(void);

/*************************************************************************************************************
* LOCAL CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* VECTOR TABLE
*************************************************************************************************************/
void (*vector_table[])(void) __attribute__((section (".vects")))= {            
        // CPU Exception vector
		Reset_Start,			 /* 00 : 0x00 : Reset Vector              */
		DummyIsr,        		 /* 01 : 0x04 : NMI Vector                */
		DummyIsr,        		 /* 02 : 0x08 : Interrupt Auto Vector     */
		DoubleFaultIsr,    		 /* 03 : 0x0C : Double fault Vector       */
		BusErrorException,       /* 04 : 0x10 : Bus Error Exception       */
		DummyIsr,                /* 05 : 0x14 : Reserved                  */
		DummyIsr,                /* 06 : 0x18 : Reserved                  */
		DummyIsr,                /* 07 : 0x1C : Reserved                  */
		CP0Exception,            /* 08 : 0x20 : Coprocessor0 Exception    */
		DummyIsr,                /* 09 : 0x24 : Coprocessor1 Exception    */
		DummyIsr,                /* 10 : 0x28 : Coprocessor2 Exception    */
		DummyIsr,                /* 11 : 0x2C : Coprocessor3 Exception    */
		DummyIsr,        		 /* 12 : 0x30 : OSI reset vector          */
		DummyIsr,        		 /* 13 : 0x34 : OSI break exception       */
		UndefInst,        		 /* 14 : 0x38 : Undefined Instruction     */
		UnimpltedInst,        	 /* 15 : 0x3C : Unimplemented Instruction */
		DummyIsr,        		 /* 16 : 0x40 : SWI 00 Vector             */
		DummyIsr,        		 /* 17 : 0x44 : SWI 01 Vector             */
		DummyIsr,		 		 /* 18 : 0x48 : SWI 02 Vector             */
		DummyIsr,        		 /* 19 : 0x4C : SWI 03 Vector             */
		DummyIsr,        		 /* 20 : 0x50 : SWI 04 Vector             */
		DummyIsr,        		 /* 21 : 0x54 : SWI 05 Vector             */
		DummyIsr,        		 /* 22 : 0x58 : SWI 06 Vector             */
		DummyIsr,        		 /* 23 : 0x5C : SWI 07 Vector             */
		DummyIsr,        		 /* 24 : 0x60 : SWI 08 Vector             */
		DummyIsr,        		 /* 25 : 0x64 : SWI 09 Vector             */
		DummyIsr,        		 /* 26 : 0x68 : SWI 0A Vector             */
		DummyIsr,        		 /* 27 : 0x6C : SWI 0B Vector             */
		DummyIsr,        		 /* 28 : 0x70 : SWI 0C Vector             */
		DummyIsr,        		 /* 29 : 0x74 : SWI 0D Vector             */
		DummyIsr,        		 /* 30 : 0x78 : SWI 0E Vector             */
		DummyIsr,        		 /* 31 : 0x7C : SWI 0F Vector             */
		
		// CPU User Interrupt vector 
        DummyIsr,		         /* 32 : 0x80 : USER0 , EXT 0			  */
	    TickTmrIsr,		         /* 33 : 0x84 : USER1 , TIMER 0	          */  
	    VsyncIsr,		         /* 34 : 0x88 : USER2 , DCP 0			  */
	    VsyncSubIsr,		     /* 35 : 0x8C : USER3 , DCP 1			  */
	    DummyIsr,		         /* 36 : 0x90 : USER4 , 				  */
	    DummyIsr,		         /* 37 : 0x94 : USER5 , TIMER 1		      */
	    HsyncIsr,		         /* 38 : 0x98 : USER6 , DCP 2			  */
	    FldSigIsr,		         /* 39 : 0x9C : USER7 , DCP 3			  */
	    DummyIsr,		         /* 40 : 0xA0 : USER8 , EXT 1			  */
	    Spi0Isr	,		/* 41 : USER9 , SPI				*/
	    Spi1Isr ,		         /* 42 : 0xA8 : USER10, 				  */
#ifdef EYENIX_COMM
		IsrUart0,		         /* 43 : 0xAC : USER11, UART 0		      */
#else
		UartIsrComm,		     /* 43 : 0xAC : USER11, UART 0		      */
#endif
	    DummyIsr,		         /* 44 : 0xB0 : USER12, 				  */
	    DummyIsr,		         /* 45 : 0xB4 : USER13, TIMER 2		      */
	    DummyIsr,		         /* 46 : 0xB8 : USER14, DCP 4			  */
	    DummyIsr,		         /* 47 : 0xBC : USER15, DCP 5			  */
	    DummyIsr,		         /* 48 : 0xC0 : USER16, EXT 2			  */
	    DummyIsr,		         /* 49 : 0xC4 : USER17, TIMER 3		      */
	    DummyIsr,		         /* 50 : 0xC8 : USER18, DCP 6			  */
	    DummyIsr,		         /* 51 : 0xCC : USER19, DCP 7			  */
	    DummyIsr,		         /* 52 : 0xD0 : USER20, 				  */
	    DummyIsr,		         /* 53 : 0xD4 : USER21, TIMER 4		      */
	    DummyIsr,		         /* 54 : 0xD8 : USER22, TIMER 5		      */
	    DummyIsr,		         /* 55 : 0xDC : USER23, 				  */
	    DummyIsr,		         /* 56 : 0xE0 : USER24, 				  */
	    DummyIsr,		         /* 57 : 0xE4 : USER25, TIMER 6		      */
	    DummyIsr,		         /* 58 : 0xE8 : USER26, TWI			      */
	    CoreAdcIsr, 	         /* 59 : 0xEC : USER27, ADC			      */
	    DummyIsr,		         /* 60 : 0xF0 : USER28, 				  */
	    DummyIsr,		         /* 61 : 0xF4 : USER29, TIMER 7		      */
	    UartIsrDbg,		         /* 62 : 0xF8 : USER30, UART 1		      */
	    DummyIsr 		         /* 63 : 0xFC : USER31, 				  */
};

/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] in : shift value (bit position)
* @param[in] en : ENABLE or DISABLE
* @retval none
* @brief
*  Set interrupt enable register.
*************************************************************************************************************/
static void SetIrqEnable(uint32 in, var_stat en)
{
	(en == ENABLE) ? (IENw(IENr | (1<<in))) : (IENw(IENr & ~(1<<in)));
} /* SetIrqEnable */

/*********************************************************************************************************//**
* @param[in] in : shift value (bit position)
* @param[in] en : ENABLE or DISABLE
* @retval none
* @brief
*  Set interrupt mask register
*************************************************************************************************************/
static void SetIrqMask(uint32 in, var_stat en)
{
	(en == ENABLE) ? (IMKSTw(IMKSTr | (1<<in))) : (IMKSTw(IMKSTr & ~(1<<in)));
} /* SetIrqMask */

/*********************************************************************************************************//**
* @param[in] in : shift value (bit position)
* @param[in] en : ENABLE or DISABLE
* @retval none
* @brief
*  Set interrupt edge type register
*************************************************************************************************************/
static void SetIrqEdgeMode(uint32 in, var_stat en)
{
	(en == ENABLE) ? (IIMw(IIMr | (1<<in))) : (IIMw(IIMr & ~(1<<in)));
} /* SetIrqEdgeMode */


/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] irq_n : Number of IRQ
* @param[in] en : ENABLE or DISABLE (Interrupt Enable or Disable)
* @retval none
* @brief
*  Configuration of IRQ
*************************************************************************************************************/
void CPU_MEM_ISPM InitIntConfig(uint32 irq_n, var_stat en)
{
	SetIrqEnable(irq_n, en);
	SetIrqMask(irq_n, en);
	SetIrqEdgeMode(irq_n, en);
} /* InitIntConfig */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Set interrupt priority
*************************************************************************************************************/
void SetIrqPriority(void)
{
	return;
} /* SetIrqPriority */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Interrupt service routine for dummy interrupt.
*  불필요한 인터럽트 발생시 클리어한다.
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
static void DummyIsr(void)
{
	//TODO : Add your interrupt service routine.
#if 0
	uint32 dummy_irq;
	uint32 irqn;

	dummy_irq = IPr ^ IENr;
	irqn      = 0;
	
	while (dummy_irq != 0)
	{
		if (dummy_irq & 0x01)
		{
			IRQ_CLR(irqn);
		}
		dummy_irq = dummy_irq >> 1;

		irqn++;
	}
#endif
} /* DummyIsr */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Exception handler for Coprocessor 0
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
static void CP0Exception(void)
{
	__HALT0;
} /* CP0_Exception */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Exception handler for bus error
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
static void BusErrorException(void)
{
	__HALT0;
} /* BusErrorException */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Exception handler for interrupt fetch or status push error
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
static void DoubleFaultIsr(void)
{
	__HALT0;
} /* DoubleFaultIsr */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Exception handler for undefine instruction
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
static void UndefInst(void)
{
	__HALT0;
} /* UndefInst */

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*  Exception handler for unimplemented instruction
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
static void UnimpltedInst(void)
{
	__HALT0;
} /* UnimpltedInst */			
/********************************************* END OF FILE **************************************************/
