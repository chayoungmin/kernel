/*********************************************************************************************************//**
* @file spi_drv.c
* @author
*  JangHo,Yoo(YJH)
* @date 2012.10.23
* @brief
*  Source file of CPU SPI device driver
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
* @param[in] mstr : Master or Slave
* @param[in] msbf : Serial data transfer start bit
* @param[in] cpha : Clock phase
* @param[in] cpol : Clock Polarity
* @param[in] size : Transfer data size
* @param[in] baud : Serial clock speed
* @param[out] none
* @retval none
* @brief
*  SPI Driver를 초기화 한다.
*************************************************************************************************************/
void InitSpiDriver(uint08 ch, uint32 mstr, uint32 msbf, uint32 cpha, uint32 cpol, uint32 size, uint32 baud)
{
#if USE_KERNEL_DEBUG > 0
//	DebugPrintf("SPI Driver Initialize...\n\r"); //YMCA Rev173
#endif
	if(ch == 0)
	{
		SPICON_MSTRw(mstr);
		SPICON_LSBFw(msbf);
		SPICON_CPHAw(cpha);
		SPICON_CPOLw(cpol);
		SPICON_SPISIZEw(size);
		SPIBAUDw(SPI_BAUD(baud));

		//SpiDisable(0);
		InitIntConfig(IRQ_SPI, ENABLE);
		SpiEnable(0);

	}

	if(ch == 1)
	{
		SPI2CON_MSTRw(mstr);
		SPI2CON_LSBFw(msbf);
		SPI2CON_CPHAw(cpha);
		SPI2CON_CPOLw(cpol);
		SPI2CON_SPISIZEw(size);
		SPI2BAUDw(SPI_BAUD(baud));

		//SpiDisable(1);
		InitIntConfig(IRQ_SPI1, ENABLE);
		SpiEnable(1);
	}


} /* InitSpiDriver */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Enable the SPI Communication.
*************************************************************************************************************/
void CPU_MEM_ISPM SpiEnable(uint08 ch)
{
	if(ch == 0)
	{
		SPICON_SPIENw(SPIEN_ENABLE);
	}
	if(ch == 1)
	{
		SPI2CON_SPIENw(SPIEN_ENABLE);
	}
} /* SpiEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Disable the SPI communication.
*************************************************************************************************************/
void CPU_MEM_ISPM SpiDisable(uint08 ch)
{
	if(ch == 0)
	{
		SPICON_SPIENw(SPIEN_DISABLE);
	}

	if(ch == 1)
	{
		SPI2CON_SPIENw(SPIEN_DISABLE);
	}
} /* SpiDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*
*************************************************************************************************************/
void CPU_MEM_ISPM SpiCsHi(uint08 ch)
{
	// Cs Hi

	if(ch == 0)
	{
		SSXCONw(1);
	}

	if(ch == 1)
	{
		SSX2CONw(1);
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*
*************************************************************************************************************/
void CPU_MEM_ISPM SpiCsLo(uint08 ch)
{
	// Cs Low

	if(ch == 0)
	{
		SSXCONw(0);
	}

	if(ch == 1)
	{
		SSX2CONw(0);
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*
*************************************************************************************************************/
void CPU_MEM_ISPM SpiMsbFst(uint08 ch)
{
	// data MSB first

	if(ch == 0)
	{
		SPICON_LSBFw(1);
	}

	if(ch == 1)
	{
		SPI2CON_LSBFw(1);
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*
*************************************************************************************************************/
void CPU_MEM_ISPM SpiLsbFst(uint08 ch)
{
	// data LSB first
	if(ch == 0)
	{
		SPICON_LSBFw(0);
	}

	if(ch == 1)
	{
		SPI2CON_LSBFw(0);
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Send data to the SPI bus.
*************************************************************************************************************/
void CPU_MEM_ISPM SpiTx(uint08 ch, uint32 sdata)
{
	uint16 time_out = 0xFFF;

	if(ch == 0)
	{
		SPIDATAw(sdata);
		while(!SPISTAT_SPIFr)
		{
			time_out--;

			if(time_out == 0)
				break;
		}
	}
	if(ch == 1)
	{
		SPI2DATAw(sdata);
		while(!SPI2STAT_SPIFr)
		{
			time_out--;

			if(time_out == 0)
				break;
		}

	}
} /* SpiPutc */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Receive data from the SPI bus.
*************************************************************************************************************/
uint32 CPU_MEM_ISPM SpiRx(uint08 ch)
{
	uint32 sdata = 0;

	if(ch == 0)
	{
		SpiTx(ch,0xAA);

		do {
			sdata = SPIDATAr & 0xFF;
		} while (!SPISTAT_SRXEr);
	}

	if(ch == 1)
	{
		SpiTx(ch,0xAA);

		do {
			sdata = SPI2DATAr & 0xFF;
		} while (!SPI2STAT_SRXEr);
	}

	return sdata;
} /* SpiGetc */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  SPI0 Interrupt service function
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Spi0Isr(void)
{
	IRQ_CLR(IRQ_SPI);

	//TODO : Add your interrupt service code

} /* Spi0Isr */



/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  SPI0 Interrupt service function
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Spi1Isr(void)
{
	IRQ_CLR(IRQ_SPI1);

	//TODO : Add your interrupt service code

} /* Spi1Isr */




/********************************************** END OF FILE *************************************************/
