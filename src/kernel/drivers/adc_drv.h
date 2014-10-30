/*********************************************************************************************************//**
* @file adc_drv.h
* @author 
*  JangHo,Yoo(YJH)
* @date 2012.10.30 
* @brief 
*  Header file of ADC(AD7904) and ADC(CPU Core) device drvier
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef ADC_DRV_EXTERN 
#define ADC_DRV_EXT 
#else 
#define ADC_DRV_EXT extern
#endif

/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/

/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
#if 0	
// AD7393
#define AD7904_WRITE_CH0	0x83B0
#define AD7904_WRITE_CH1	0x87B0
#define AD7904_WRITE_CH2	0x8BB0
#define AD7904_WRITE_CH3	0x8FB0
#elif 0 //YMCA
// MDIN325A
#define AD7904_WRITE_CH0	0x8390
#define AD7904_WRITE_CH1	0x8790
#define AD7904_WRITE_CH2	0x8B90
#define AD7904_WRITE_CH3	0x8F90
#endif
/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/
typedef enum _CORE_ADC_CH_N {
	CORE_ADC_CH0,
	CORE_ADC_CH1,
	CORE_ADC_CH2,
	CORE_ADC_CH3,
	CORE_ADC_CH4,
	CORE_ADC_CH5,
	CORE_ADC_CH6,
	CORE_ADC_CH7
} CORE_ADC_CH_N;

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
extern void InitCoreAdcDriver(void);
extern uint16 GetCoreAdcResult(CORE_ADC_CH_N adc_ch);
extern void CoreAdcIsr(void);

extern uint16 AD7904(uint16 data);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _ADC_DRV_H_ */
/********************************************** END OF FILE *************************************************/


