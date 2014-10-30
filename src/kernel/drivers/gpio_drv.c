/*********************************************************************************************************//**
* @file gpio_drv.c
* @author 
*  JangHo,Yoo (YJH)
* @date 2012.10.17 
* @brief 
*  GPIO DEVICE DRIVER
*  1. GPIO 초기화
*  2. GPIO 인터럽트 구성
*  3. GPIO 인터럽트 서비스 루틴
*************************************************************************************************************/

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "kernel.h"

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

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  GPIO 초기화 구성을 한다.
*************************************************************************************************************/
void InitGpioDriver(void)
{
#if USE_KERNEL_DEBUG > 0
//	DebugPrintf("GPIO Initialize...\n\r"); //YMCA
#endif
	/*
	 * ADC IC
	 */

/* 
	GpioOutDir(GPIO_ADC_SCK);	//NOT USE YMCA
	GpioInDir(GPIO_ADC_SI);
	GpioOutDir(GPIO_ADC_SO);
	GpioOutDir(GPIO_ADC_CS);		
	GpioSetHi(GPIO_ADC_SCK);
//	GpioSetHi(GPIO_ADC_SI);
	GpioSetHi(GPIO_ADC_SO);
	GpioSetHi(GPIO_ADC_CS);		//NOT USE YMCA
*/
		
	/*
	 * DEBUG UART
	 */
	GpioFuncPin(GPIO_RXD2);
	GpioFuncPin(GPIO_TXD2);
	
	
	/*
	 * CMOS SENSOR
	 */
	
	GpioOutDir(GPIO_SEN_RST); 	//GPIO SETTING
	GpioFuncPin(GPIO_SEN_CS);    	//SPI CS SETTING
	GpioFuncPin(GPIO_SEN_SO);    	//SPI SO SETTING
	GpioFuncPin(GPIO_SEN_SCK);  	//SPI SCK SETTING
	GpioFuncPin(GPIO_SEN_SI);		//SPI SI SETTING	

	GpioSetHi(GPIO_SEN_RST);		//RESET 	
	
	//GpioOutDir(GPIO_SEN_SO);
	//GpioOutDir(GPIO_SEN_SCK);
	//GpioInDir(GPIO_SEN_SI);
	//GpioOutDir(GPIO_SEN_RST);

	//GpioSetHi(GPIO_SEN_CS);
	//GpioSetHi(GPIO_SEN_SO);
	//GpioSetHi(GPIO_SEN_SCK);
	//GpioSetHi(GPIO_SEN_SI);
	//GpioSetHi(GPIO_SEN_RST);

#if 0
//	GpioFuncPin(GPIO_SEN_CS);		// SPI nCS
	GpioFuncPin(GPIO_SEN_SI);		// SPI MOSI
	GpioFuncPin(GPIO_SEN_SO);		// SPI MOSI
	GpioFuncPin(GPIO_SEN_SCK);		// SPI CLK
#endif

	/*
	 * MOTOR CONTROLLER IC
	 */

//	GpioFuncPin(GPIO_M_CS);
	//GpioOutDir(GPIO_M_CS);
//	GpioFuncPin(GPIO_M_SO);
//	GpioFuncPin(GPIO_M_SCK);
//	GpioFuncPin(GPIO_M_SI);
//	GpioOutDir(GPIO_M_RST);
//	GpioSetHi(GPIO_M_RST);

	GpioOutDir(GPIO_M_CS);
	GpioOutDir(GPIO_M_SO);
	GpioOutDir(GPIO_M_SCK);
	GpioInDir(GPIO_M_SI);
	GpioOutDir(GPIO_M_RST);

	GpioSetHi(GPIO_M_CS);
	GpioSetHi(GPIO_M_SO);
	GpioSetHi(GPIO_M_SCK);
//	GpioSetHi(GPIO_M_SI);
	GpioSetHi(GPIO_M_RST);

#if 0
	GpioFuncPin(GPIO_M_CS);		// SPI nCS
	GpioFuncPin(GPIO_M_SI);		// SPI MOSI
	GpioFuncPin(GPIO_M_SO);		// SPI MOSI
	GpioFuncPin(GPIO_M_SCK);		// SPI CLK
#endif

	 /*
	 * TWI (I2C)
	 */
//	GpioFuncPin(GPIO_EEP_SCL);
//	GpioFuncPin(GPIO_EEP_SDA);	
	
	GpioOutDir(GPIO_EEP_SCL);
	GpioOutDir(GPIO_EEP_SDA);

	GpioSetHi(GPIO_EEP_SCL);
	GpioSetHi(GPIO_EEP_SDA);

	GpioOutDir(GPIO_RMC_DATA); //YMCA REV187
	GpioSetLo(GPIO_RMC_DATA); //YMCA REV187

	

//	GpioOutDir(GPIO_325_RST);
//	GpioSetLo(GPIO_325_RST);

	
	/*
	 * MOTION INDICATOR PORT
	 */
	//GpioOutDir(GPIO_MOTION);
	//GpioSetLo(GPIO_MOTION);
	
	 
	 /*
	 * DAY & NIGHT FILTER
	 */
	GpioOutDir(GPIO_DN_IN1);
	GpioOutDir(GPIO_DN_IN2);

	GpioSetLo(GPIO_DN_IN1);
	GpioSetLo(GPIO_DN_IN2);

	/*
	 * IR LED ON/OFF
	 */
//	GpioFuncPin(GPIO_IR_ON);
	GpioOutDir(GPIO_IR_ON);
	GpioSetLo(GPIO_IR_ON);
	
	//GPIO_H_SO,
	//GPIO_F_SO,
//	GpioFuncPin(GPIO_YC_HD);
//	GpioFuncPin(GPIO_YC_VD);

//	GpioInDir(GPIO_MODE_CHG);
//	HSO_MUX_ONw(1);					// HSO
//	VSO_MUX_ONw(1);					// VSO
//	DENO_MUX_ONw(1);				// DENO

//	GpioOutDir(GPIO_MODE);
#ifdef SUNNY_X20
//	GpioOutDir(GPIO_DDRN);  //YMCA
#endif
//	GpioOutDir(GPIO_MAP);
	
//	GpioOutDir(GPIO_6B_8B);
	

} /* InitGpioConfig */

#if 0 //121022-YJH : Further use
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  외부인터럽트를 구성한다.
*************************************************************************************************************/
void InitGpioIntConfig(uint32 int_n, uint32 edge, var_stat en)
{
	return;
} /* InitGpioIntConfig */
#endif

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] none
* @retval none
* @brief 
*  Set GPIO pin mux register
*************************************************************************************************************/
void GpioFuncPin(uint32 aiIn)
{	// PinMux Function : GPIO, FUNC
	// 0 : Special Function
	// 1 : GPIO
	PMUXw(PMUXr & ~(1<<aiIn));
} /* GpioFuncPin */

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] none
* @retval none
* @brief 
*  GPIO pin set to output direction 
*************************************************************************************************************/
void GpioOutDir(uint32 aiIn)
{	// Direction : Gpio direction set to output
	PODIRw(GpioDiv(aiIn), PDIRr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) );
	PIDIRw(GpioDiv(aiIn), ~PDIRr(GpioDiv(aiIn)) );
} /* GpioOutDir */

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] 
* @retval 
* @brief 
*  GPIO pin set to input direction 
*************************************************************************************************************/
void GpioInDir(uint32 aiIn)
{	// Direction : Gpio direction set to input
	PIDIRw(GpioDiv(aiIn), PDIRr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) );
	PODIRw(GpioDiv(aiIn), ~PDIRr(GpioDiv(aiIn)) );
} /* GpioInDir */

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] none
* @retval none
* @brief 
*  GPIO pin output is set to high.
*************************************************************************************************************/
void __attribute__((section(".ispmtext"))) GpioSetHi(uint32 aiIn)
{	// Output Pin Setting : HIGH
	POHIGHw(GpioDiv(aiIn), POLEVr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) );
} /* GpioSetHi */

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] none
* @retval none
* @brief 
*  GPIO pin output is set to low.
*************************************************************************************************************/
void __attribute__((section(".ispmtext"))) GpioSetLo(uint32 aiIn)
{	// Output Pin Setting : LOW
	POLOWw(GpioDiv(aiIn), ~POLEVr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) );
} /* GpioSetLo */

/*********************************************************************************************************//**
* @param[in] aiIn : GPX.X Gpio pin
* @param[out] none
* @retval 
*  Pin login level (HIGH or LOW)
* @brief
*  Read the GPIO pin state.
*************************************************************************************************************/
uint08 __attribute__((section(".ispmtext"))) GpioGetPin(uint32 aiIn)
{	// Input level : PILEV
	uint08 bData;
	
	bData = (uint08)((PILEVr(GpioDiv(aiIn)) & (1<<GpioRem(aiIn))) >> GpioRem(aiIn));

	return (bData);
} /* GpioGetPin */
 
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  EIRQ0 Interrupt service function
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Ext0Isr(void)
{
	IRQ_CLR(IRQ_EXT0);
	
	//TODO : Add your interrupt service code
	
} /* Ext0Isr */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  EIRQ1 Interrupt service function
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Ext1Isr(void)
{
	IRQ_CLR(IRQ_EXT1);

	//TODO : Add your interrupt service code
	
} /* Ext1Isr */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  EIRQ2 Interrupt service function
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Ext2Isr(void)
{
	IRQ_CLR(IRQ_EXT2);

	//TODO : Add your interrupt service code
	
} /* Ext2Isr */

/********************************************** END OF FILE *************************************************/
