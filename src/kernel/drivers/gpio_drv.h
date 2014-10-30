/*********************************************************************************************************//**
* @file gpio_drv.h
* @author 
*  JangHo,Yoo(YJH)
* @date 2012.10.17 
* @brief 
*  GPIO Device Driver
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _GPIO_DRV_H_
#define _GPIO_DRV_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef MODULE_NAME_EXTERN 
#define GPIO_DRV_EXT
#else 
#define GPIO_DRV_EXT                          extern
#endif

/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/

/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
enum _GPDIR {
	GPDIR_INPUT,
	GPDIR_OUTPUT
};

enum _GP_IOLEV {
	GPLEV_LOW,
	GPLEV_HIGH
};

enum _GPMUX {
	GPMUX_FUNC,
	GPMUX_IO
};

enum _GPPU {
	GPPUS_DISABLE,
	GPPUS_ENABLE
};

enum _GPRFED {
	GPED_DISABLE,
	GPED_ENABLE
};

enum _GPODM {
	GPOD_CMOSO,
	GPOD_OD
};

#if 0
// GPIO Pin Mapping
enum _GPIO_PIN_MAP {
	GPIO_BOOT = 0,	//EIRQ[0]	/	GPIO00 = 0,			// BOOT Highest priority
	GPIO_ADC_SCK, 	//EIRQ[1]	/	GPIO01    ,			// ADC_SCK
	GPIO_ADC_SI,	//PWM2		/	GPIO02    ,			// ADC_SI
	GPIO_ADC_SO,	//PWM3		/	GPIO03    ,			// ADC_SO
	GPIO_RXD2,		//RXD1		/	GPIO04    ,			// RXD2
	GPIO_TXD2,		//TXD1		/	GPIO05    ,			// TXD2
	GPIO_SEN_CS,	//SPI_CS1	/	GPIO06    ,			// SEN_CS
	GPIO_SEN_SO,	//SPI_DI1	/	GPIO07    ,			// SEN_SO
	GPIO_SEN_SCK,	//SPI_CK1	/	GPIO08    ,			// SEN_SCK
	GPIO_M_CS,		//SPI_CS2	/	GPIO09    ,			// M_CS
	GPIO_M_SO,		//SPI_DI2	/	GPIO10    ,			// M_SO
	GPIO_M_SCK,		//SPI_CK2	/	GPIO11    ,			// M_SCK
	GPIO_M_SI,		//SPI_DO2	/	GPIO12    ,			// M_SI
	GPIO_SEN_SI,	//SPI_DO1	/	GPIO13    ,			// SEN_SI
	GPIO_MOTION,	//RESERVED	/	GPIO14    ,			// MOTION
	GPIO_EEP_SCL,	//TWI_SCL	/	GPIO15    ,			// EEP_SCL
	GPIO_EEP_SDA,	//TWI_SDA	/	GPIO16    ,			// EEP_SDA
#if 1	//OLD VERSION 111027
	GPIO_TELE,		//EIRQ[2]	/	GPIO17    ,			// TELE
	GPIO_WIDE,		//PWM4		/	GPIO18    ,			// WIDE
	GPIO_MENU,		//PWM5		/	GPIO19    ,			// MENU
	GPIO_NEAR,		//PWM6		/	GPIO20    ,			// NEAR
	GPIO_FAR,		//PWM7		/	GPIO21    ,			// FAR
#else	// NEW VERSION
	GPIO_TELE,		//EIRQ[2]	/	GPIO17    ,			// TELE
	GPIO_FAR,		//PWM4		/	GPIO18    ,			// WIDE
	GPIO_MENU,		//PWM5		/	GPIO19    ,			// MENU
	GPIO_NEAR,		//PWM6		/	GPIO20    ,			// NEAR
	GPIO_WIDE,		//PWM7		/	GPIO21    ,			// FAR
#endif
	GPIO_DN_IN1,	//CAP4		/	GPIO22    ,			// DN_IN1
	GPIO_DN_IN2,	//CAP5		/	GPIO23    ,			// DN_IN2
	GPIO_M_RST,		//CAP6		/	GPIO24    ,			// M_RST
	GPIO_RMC_DATA,	//CAP7		/	GPIO25    ,			// RMC_DATA
	GPIO_IR_ON,		//ISP_RESET	/	GPIO26    ,			// IR_ON
	GPIO_ADC_CS,	//ISP_SYNC	/	GPIO27    ,			// ADC_CS
	GPIO_SEN_RST,	//ISP_CS	/	GPIO28    ,			// SEN_RST
	GPIO_325_RST,	//ISP_CK	/	GPIO29
	GPIO_TEST_LED,	//ISP_DI	/	GPIO30
	GPIO_D_LED,		//ISP_DO	/	GPIO31				// D_LED
};
#else


enum{	
	GPIO_00 = 0,		//00 				//EIRQ[0]		/	GPIO00 = 0,			// BOOT Highest priority
	GPIO_RMC_DATA,	//01 				//EIRQ[1]		/	GPIO01    ,			// RMC_DATA 
	GPIO_IR_ON,		//02 				//PWM2		/	GPIO02    ,			// IR_ON_OFF
	GPIO_MOTION,		//03 				//PWM3		/	GPIO03    ,				//MOTION 
	GPIO_RXD2,			//04					//RXD1		/	GPIO04    ,			// RXD2
	GPIO_TXD2,  		//05					//TXD1		/	GPIO05    ,			// TXD2
	GPIO_M_CS,			//06					//SPI_CS1	/	GPIO06    ,			// M_CS 	//AN1908 DRIVER
	GPIO_M_SO,			//07					//SPI_DI1 	/	GPIO07    ,			// M_SO 	//AN1908 DRIVER
	GPIO_M_SCK,		//08					//SPI_CK1	/	GPIO08    ,			// M_SCK	//AN1908 DRIVER	
	GPIO_SEN_CS,		//09					//SPI_CS2	/	GPIO09    ,			 // SEN_CS  //SENSOR_CS 
	GPIO_SPI2_SO,		//10			   		//SPI_D02		/	GPIO10    ,		// SPI2_SO
	GPIO_SPI2_SCK,		//11					//SPI_CK2	/	GPIO11    ,			// SPI2_SCK 
	GPIO_SPI2_SI,		//12					//SPI_DI2		/	GPIO12    ,			// SPI2_SI 
	GPIO_M_SI,			//13					//SPI_DO1	/	GPIO13    ,			// M_SI
	GPIO_SEN_RST,		//14					//RESERVED	/	GPIO14    ,			// SEN_RST
	GPIO_EEP_SCL, 		//15					//TWI_SCL	/	GPIO15    ,			// EEP_SCL					
	GPIO_EEP_SDA,		//16					//TWI_SDA	/	GPIO16    ,			// EEP_SDA
	GPIO_17,			//17					//EIRQ2		/	GPIO17	,			//NOT USE
	GPIO_18,			//18					//PWM4		/	GPIO18	,			//NOT USE
	GPIO_MODE,			//19					//PWM5		/	GPIO19	,			//NOT USE
	GPIO_MAP,			//20					//PWM6		/	GPIO20	,			//NOT USE
	GPIO_6B_8B,		//21					//PWM7		/	GPIO21	,			//NOT USE
	GPIO_DN_IN1,		//22					//CAP4		/	GPIO22	,			//DN_IN1
	GPIO_DN_IN2,		//23					//CAP5		/	GPIO23	,			//DN_IN2
	GPIO_C_REBOOT,		//24					//CAP6		/	GPIO24	,			//NOT USE
	GPIO_25,			//25					//CAP7		/	GPIO25	,			//NOT USE	
	GPIO_M_RST,		//26					//ISP_RESET	/	GPIO26	,			//M_RST
	GPIO_LD_RST,		//27					//ISP_SYNC	/	GPIO27	,			//NOT USE
	GPIO_ADC_CS,		//28					//ISP_CS		/	GPIO28	,			//NOT USE
	GPIO_29,			//29					//ISP_CK		/	GPIO29	,			//NOT USE
	GPIO_YC_HD,		//30					//ISP_DI		/	GPIO30	,			//NOT USE
	GPIO_YC_VD,		//31					//ISP_DO		/	GPIO31	,			//NOT USE 
};

#define	GPIO_325_RST	GPIO_LD_RST

#define	GPIO_SEN_SCK	GPIO_SPI2_SCK
#define	GPIO_SEN_SI	GPIO_SPI2_SI
#define	GPIO_SEN_SO	GPIO_SPI2_SO

/*
#define	GPIO_ADC_SCK 	GPIO_SEN_SCK	//NOT USE	
#define	GPIO_ADC_SI 	GPIO_SEN_SI
#define	GPIO_ADC_SO 	GPIO_SEN_SO  	//NOT USE
*/

#define GPIO_M2S_SCL	GPIO_EEP_SCL
#define GPIO_M2S_SDA	GPIO_EEP_SDA

#endif

/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/
typedef enum _EIRQ_EDGE_N {
	EIRQ_LOWLEVEL,
	ERIQ_HIGHLEVEL,
	EIRQ_FALLING,
	EIRQ_RISING
} EIRQ_EDGE_N;	

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
void InitGpioDriver(void);
void GpioFuncPin(uint32 aiIn);
void GpioOutDir(uint32 aiIn);
void GpioInDir(uint32 aiIn);
void GpioSetHi(uint32 aiIn);
void GpioSetLo(uint32 aiIn);
uint08 GpioGetPin(uint32 aiIn);
void Ext0Isr(void);
void Ext1Isr(void);
void Ext2Isr(void);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _MODULE_NAME_H_ */
/********************************************** END OF FILE *************************************************/
