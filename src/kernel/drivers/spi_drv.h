/*********************************************************************************************************//**
* @file spi_drv.h
* @author 
*  JangHo,Yoo(YJH)
* @date 2012.10.23 
* @brief 
*  Header file of CPU SPI device driver
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef MODULE_NAME_EXTERN 
#define SPI_DRV_EXT 
#else 
#define SPI_DRV_EXT extern
#endif

/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/

/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
enum _SPICTRL_SPIEN {
	SPIEN_DISABLE,
	SPIEN_ENABLE
};

enum _SPICTRL_WOMP {
	WOMP_CMOS,
	WOMP_OPEND
};

enum _SPICTRL_MSTR {
	MSTR_SLAVE,
	MSTR_MASTER
};

enum _SPICTRL_CPOL {
	CPOL_LOW,
	CPOL_HIGH
};

enum _SPICTRL_CPHA {
	CPHA_CAP_SCK,
	CPHA_CHG_SCK
};

enum _SPICTRL_MSBF {
	MSBF_LSB,
	MSBF_MSB
};

enum _SPICTRL_SPISIZE {
	SPISIZE_8,
	SPISIZE_16,
	SPISIZE_32
};

enum _SPISTAT_SPIF {
	SPIF_BUSY,
	SPIF_IDLE
};

enum _SPISTAT_WCOL {
	WCOL_NO,
	WCOL_YES
};

enum _SPISTAT_MODF {
	MODF_NORMAL,
	MODF_MODE_FALUT
};

enum _SPISTAT_NSS {
	NSS_LOW,
	NSS_HIGH
};

enum _SPISTAT_STXF {
	STXF_NFULL,
	STXF_FULL
};

enum _SPISTAT_STXE {
	STXE_NEMPTY,
	STXE_EMPTY
};

enum _SPISTAT_SRXF {
	SRXF_NFULL,
	SRXF_FULL
};

enum _SPISTAT_SRXE {
	SRXE_NEMPTY,
	SRXE_EMPRY
};

enum _SPIIINT_SPIFE {
	SPIFE_DISABLE,
	SPIFE_ENABLE
};

enum _SPIINT_MODFE {
	MODFE_DISABLE,
	MODFE_ENABLE
};

enum _SPIINT_NSSEN {
	NSSEN_DISABLE,
	NSSEN_ENABLE
};

enum _SPIINT_STXFE {
	STXFE_DISABLE,
	STXFE_ENABLE
};

enum _SPIINT_STXEE {
	
	STXEE_DISABLE,
	STXEE_ENABLE
};

enum _SPIINT_SRXFE {
	SRXFE_DISABLE,
	SRXFE_ENABLE
};

enum _SPIINT_SRXEE {
	SRXEE_DISABLE,
	SRXEE_ENABLE
};

enum _SPIBR_BAUD {
	SPI_CLK_5M = 5000000,
	SPI_CLK_4M = 4000000,
	SPI_CLK_3M = 3000000,
	SPI_CLK_2M = 2000000,
	SPI_CLK_1M = 1000000
};

/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/
#define SPI_MSBF()                                      SPICON_LSBFw(MSBF_MSB)
#define SPI_LSBF()                                      SPICON_LSBFw(MSBF_LSB)
#define SPI_CS_LOW()                                    SSXCONw(0)
#define SPI_CS_HIGH()                                   SSXCONw(1)

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
void InitSpiDriver(uint08 ch, uint32 mstr, uint32 msbf, uint32 cpha, uint32 cpol, uint32 size, uint32 baud);

void SpiEnable(uint08 ch);
void SpiDisable(uint08 ch);

void SpiCsHi(uint08 ch);
void SpiCsLo(uint08 ch);

void SpiMsbFst(uint08 ch);
void SpiLsbFst(uint08 ch);

void SpiTx(uint08 ch, uint32 sdata);
uint32 SpiRx(uint08 ch);

void Spi0Isr(void);
void Spi1Isr(void);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _SPI_DRV_H_ */
/********************************************** END OF FILE *************************************************/
