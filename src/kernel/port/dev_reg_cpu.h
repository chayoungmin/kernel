/* **************************************************************************
 File Name	: 	dev_reg_cpu.h
 Description:	EN777 - CPU Reg macro define
 Designer	:	Lee, Hoon
 Date		:	12.  1. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
		 1. UART
		 2. TWI
		 3. TIMER
		 4. SPI
		 5. IRQ
		 6. GPIO
		 7. FLASH
		 8. WDT
*/


//*************************************************************************************************
// UART
//-------------------------------------------------------------------------------------------------

#define	UART_BASE0				0x30003400
#define	UART_BASE1 				0x30003420

//..............................................................
// Ch 1
#define U0RBr						(ValSft_R00(_rd32(UART_BASE0+0x00))&BitMask_08)
#define U0THw(val)					_wr32(UART_BASE0+0x00,(val&BitMask_08))

#define U0IEr						(ValSft_R00(_rd32(UART_BASE0+0x04))&BitMask_32)
#define U0IEw(val)					_wr32(UART_BASE0+0x04,((_rd32(UART_BASE0+0x04)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U0IE_RDAIENr				(ValSft_R00(_rd32(UART_BASE0+0x04))&BitMask_01)
#define U0IE_RDAIENw(val)			_wr32(UART_BASE0+0x04,((_rd32(UART_BASE0+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define U0IE_THEIENr				(ValSft_R01(_rd32(UART_BASE0+0x04))&BitMask_01)
#define U0IE_THEIENw(val)			_wr32(UART_BASE0+0x04,((_rd32(UART_BASE0+0x04)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define U0IE_RLSIENr				(ValSft_R02(_rd32(UART_BASE0+0x04))&BitMask_01)
#define U0IE_RLSIENw(val)			_wr32(UART_BASE0+0x04,((_rd32(UART_BASE0+0x04)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define U0IIr						(ValSft_R00(_rd32(UART_BASE0+0x08))&BitMask_32)
#define U0II_INTIDr					(ValSft_R00(_rd32(UART_BASE0+0x08))&BitMask_04)
#define U0II_FIFOSTr				(ValSft_R06(_rd32(UART_BASE0+0x08))&BitMask_02)

#define U0FCr						(ValSft_R00(_rd32(UART_BASE0+0x08))&BitMask_32)
#define U0FCw(val)					_wr32(UART_BASE0+0x08,((_rd32(UART_BASE0+0x08)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U0FC_FIFOENr				(ValSft_R00(_rd32(UART_BASE0+0x08))&BitMask_01)
#define U0FC_FIFOENw(val)			_wr32(UART_BASE0+0x08,((_rd32(UART_BASE0+0x08)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define U0FC_RFRr					(ValSft_R01(_rd32(UART_BASE0+0x08))&BitMask_01)
#define U0FC_RFRw(val)				_wr32(UART_BASE0+0x08,((_rd32(UART_BASE0+0x08)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define U0FC_XFRr					(ValSft_R02(_rd32(UART_BASE0+0x08))&BitMask_01)
#define U0FC_XFRw(val)				_wr32(UART_BASE0+0x08,((_rd32(UART_BASE0+0x08)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define U0FC_RFTLr					(ValSft_R06(_rd32(UART_BASE0+0x08))&BitMask_02)
#define U0FC_RFTLw(val)				_wr32(UART_BASE0+0x08,((_rd32(UART_BASE0+0x08)&(~ValSft_L06(BitMask_02)))|ValSft_L06((val)&BitMask_02)))

#define U0LCr						(ValSft_R00(_rd32(UART_BASE0+0x0C))&BitMask_32)
#define U0LCw(val)					_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U0LC_WLSr					(ValSft_R00(_rd32(UART_BASE0+0x0C))&BitMask_02)
#define U0LC_WLSw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))
#define U0LC_STBr					(ValSft_R02(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_STBw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define U0LC_PENr					(ValSft_R03(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_PENw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define U0LC_EPSr					(ValSft_R04(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_EPSw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define U0LC_SPr					(ValSft_R05(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_SPw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define U0LC_SBr					(ValSft_R06(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_SBw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define U0LC_DLABr					(ValSft_R07(_rd32(UART_BASE0+0x0C))&BitMask_01)
#define U0LC_DLABw(val)				_wr32(UART_BASE0+0x0C,((_rd32(UART_BASE0+0x0C)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define U0LSr						(ValSft_R00(_rd32(UART_BASE0+0x14))&BitMask_32)
#define U0LS_DRDYr					(ValSft_R00(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_OERRr					(ValSft_R01(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_PERRr					(ValSft_R02(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_FERRr					(ValSft_R03(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_BINTr					(ValSft_R04(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_THREr					(ValSft_R05(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_TEMPr					(ValSft_R06(_rd32(UART_BASE0+0x14))&BitMask_01)
#define U0LS_EIRFr					(ValSft_R07(_rd32(UART_BASE0+0x14))&BitMask_01)

#define U0DLLr						(ValSft_R00(_rd32(UART_BASE0+0x00))&BitMask_08)
#define U0DLLw(val)					_wr32(UART_BASE0+0x00,((_rd32(UART_BASE0+0x00)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define U0DLMr						(ValSft_R00(_rd32(UART_BASE0+0x04))&BitMask_08)
#define U0DLMw(val)					_wr32(UART_BASE0+0x04,((_rd32(UART_BASE0+0x04)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

//..............................................................
// Ch 2
#define U1RBr						(ValSft_R00(_rd32(UART_BASE1+0x00))&BitMask_08)
#define U1THw(val)					_wr32(UART_BASE1+0x00,(val&BitMask_08))

#define U1IEr						(ValSft_R00(_rd32(UART_BASE1+0x04))&BitMask_32)
#define U1IEw(val)					_wr32(UART_BASE1+0x04,((_rd32(UART_BASE1+0x04)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U1IE_RDAIENr				(ValSft_R00(_rd32(UART_BASE1+0x04))&BitMask_01)
#define U1IE_RDAIENw(val)			_wr32(UART_BASE1+0x04,((_rd32(UART_BASE1+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define U1IE_THEIENr				(ValSft_R01(_rd32(UART_BASE1+0x04))&BitMask_01)
#define U1IE_THEIENw(val)			_wr32(UART_BASE1+0x04,((_rd32(UART_BASE1+0x04)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define U1IE_RLSIENr				(ValSft_R02(_rd32(UART_BASE1+0x04))&BitMask_01)
#define U1IE_RLSIENw(val)			_wr32(UART_BASE1+0x04,((_rd32(UART_BASE1+0x04)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define U1IIr						(ValSft_R00(_rd32(UART_BASE1+0x08))&BitMask_32)
#define U1II_INTIDr					(ValSft_R00(_rd32(UART_BASE1+0x08))&BitMask_04)
#define U1II_FIFOSTr				(ValSft_R06(_rd32(UART_BASE1+0x08))&BitMask_02)

#define U1FCr						(ValSft_R00(_rd32(UART_BASE1+0x08))&BitMask_32)
#define U1FCw(val)					_wr32(UART_BASE1+0x08,((_rd32(UART_BASE1+0x08)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U1FC_FIFOENr				(ValSft_R00(_rd32(UART_BASE1+0x08))&BitMask_01)
#define U1FC_FIFOENw(val)			_wr32(UART_BASE1+0x08,((_rd32(UART_BASE1+0x08)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define U1FC_RFRr					(ValSft_R01(_rd32(UART_BASE1+0x08))&BitMask_01)
#define U1FC_RFRw(val)				_wr32(UART_BASE1+0x08,((_rd32(UART_BASE1+0x08)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define U1FC_XFRr					(ValSft_R02(_rd32(UART_BASE1+0x08))&BitMask_01)
#define U1FC_XFRw(val)				_wr32(UART_BASE1+0x08,((_rd32(UART_BASE1+0x08)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define U1FC_RFTLr					(ValSft_R06(_rd32(UART_BASE1+0x08))&BitMask_02)
#define U1FC_RFTLw(val)				_wr32(UART_BASE1+0x08,((_rd32(UART_BASE1+0x08)&(~ValSft_L06(BitMask_02)))|ValSft_L06((val)&BitMask_02)))

#define U1LCr						(ValSft_R00(_rd32(UART_BASE1+0x0C))&BitMask_32)
#define U1LCw(val)					_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
#define U1LC_WLSr					(ValSft_R00(_rd32(UART_BASE1+0x0C))&BitMask_02)
#define U1LC_WLSw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))
#define U1LC_STBr					(ValSft_R02(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_STBw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define U1LC_PENr					(ValSft_R03(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_PENw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define U1LC_EPSr					(ValSft_R04(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_EPSw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define U1LC_SPr					(ValSft_R05(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_SPw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define U1LC_SBr					(ValSft_R06(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_SBw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define U1LC_DLABr					(ValSft_R07(_rd32(UART_BASE1+0x0C))&BitMask_01)
#define U1LC_DLABw(val)				_wr32(UART_BASE1+0x0C,((_rd32(UART_BASE1+0x0C)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define U1LSr						(ValSft_R00(_rd32(UART_BASE1+0x14))&BitMask_32)
#define U1LS_DRDYr					(ValSft_R00(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_OERRr					(ValSft_R01(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_PERRr					(ValSft_R02(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_FERRr					(ValSft_R03(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_BINTr					(ValSft_R04(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_THREr					(ValSft_R05(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_TEMPr					(ValSft_R06(_rd32(UART_BASE1+0x14))&BitMask_01)
#define U1LS_EIRFr					(ValSft_R07(_rd32(UART_BASE1+0x14))&BitMask_01)

#define U1DLLr						(ValSft_R00(_rd32(UART_BASE1+0x00))&BitMask_08)
#define U1DLLw(val)					_wr32(UART_BASE1+0x00,((_rd32(UART_BASE1+0x00)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define U1DLMr						(ValSft_R00(_rd32(UART_BASE1+0x04))&BitMask_08)
#define U1DLMw(val)					_wr32(UART_BASE1+0x04,((_rd32(UART_BASE1+0x04)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))


//*************************************************************************************************
// TWI
//-------------------------------------------------------------------------------------------------

#define	TWI_BASE 					0x30003000
                                	
#define	TWICONr						_rd32(TWI_BASE+0x00)
#define	TWICONw(val)				_wr32(TWI_BASE+0x00,val)
#define	TWICON_LAIEr				(ValSft_R00(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_LAIEw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TWICON_TCIEr				(ValSft_R01(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_TCIEw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define	TWICON_REPSTr				(ValSft_R02(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_REPSTw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define	TWICON_TWIAKr				(ValSft_R03(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_TWIAKw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	TWICON_TWITRr				(ValSft_R04(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_TWITRw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	TWICON_TWIMODr				(ValSft_R05(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_TWIMODw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TWICON_TWIENr				(ValSft_R07(_rd32(TWI_BASE+0x00))&BitMask_01)
#define	TWICON_TWIENw(val)			_wr32(TWI_BASE+0x00,((_rd32(TWI_BASE+0x00)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))
                                	
#define	TWISTATr					_rd32(TWI_BASE+0x04)
#define	TWISTATw(val)				_wr32(TWI_BASE+0x04,val)
#define	TWISTAT_TWIRAKr				(ValSft_R00(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_REPSFr				(ValSft_R01(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_REPSFw(val)			_wr32(TWI_BASE+0x04,((_rd32(TWI_BASE+0x04)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define	TWISTAT_TWISRWr				(ValSft_R03(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_TWILOSTr			(ValSft_R04(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_TWILOSTw(val)		_wr32(TWI_BASE+0x04,((_rd32(TWI_BASE+0x04)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	TWISTAT_TWIBUSYr			(ValSft_R05(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_TWIASr				(ValSft_R06(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_TWIDTr				(ValSft_R07(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_RX_FULLr			(ValSft_R08(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_RX_FULLw(val)		_wr32(TWI_BASE+0x04,((_rd32(TWI_BASE+0x04)&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))
#define	TWISTAT_TX_EMPTYr			(ValSft_R09(_rd32(TWI_BASE+0x04))&BitMask_01)
#define	TWISTAT_TX_EMPTYw(val)		_wr32(TWI_BASE+0x04,((_rd32(TWI_BASE+0x04)&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))
                                	
#define	TWIADRr						_rd32(TWI_BASE+0x08)
#define	TWIADRw(val)				_wr32(TWI_BASE+0x08,val)
#define	TWIDATAr					_rd32(TWI_BASE+0x0C)
#define	TWIDATAw(val)				_wr32(TWI_BASE+0x0C,val)
#define	TWIBR0r						_rd32(TWI_BASE+0x10)
#define	TWIBR0w(val)				_wr32(TWI_BASE+0x10,val)
#define	TWIBR1r						_rd32(TWI_BASE+0x14)
#define	TWIBR1w(val)				_wr32(TWI_BASE+0x14,val)


//*************************************************************************************************
// TIMER
//-------------------------------------------------------------------------------------------------

#define	TIMER_BASE0					0x30002000
#define	TIMER_BASE1					0x30002020
#define	TIMER_BASE2					0x30002040
#define	TIMER_BASE3					0x30002060
#define	TIMER_BASE4					0x30002080
#define	TIMER_BASE5					0x300020a0
#define	TIMER_BASE6					0x300020c0
#define	TIMER_BASE7					0x300020e0

//..............................................................
// Ch 0
#define	TP0CON_CLKSELr				(ValSft_R00(_rd32(TIMER_BASE0+0x00))&BitMask_01)
#define	TP0CON_CLKSELw(val)			_wr32(TIMER_BASE0+0x00,((_rd32(TIMER_BASE0+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TP0CON_CNTCLRr				(ValSft_R01(_rd32(TIMER_BASE0+0x00))&BitMask_01)
#define	TP0CON_CNTCLRw(val)			_wr32(TIMER_BASE0+0x00,((_rd32(TIMER_BASE0+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
                                	
#define	TM0CON_TMENr				(ValSft_R00(_rd32(TIMER_BASE0+0x04))&BitMask_01)
#define	TM0CON_TMENw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TM0CON_PFSELr				(ValSft_R01(_rd32(TIMER_BASE0+0x04))&BitMask_03)
#define	TM0CON_PFSELw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L01(BitMask_03)))|ValSft_L01((val)&BitMask_03)))
#define	TM0CON_PWMLr				(ValSft_R05(_rd32(TIMER_BASE0+0x04))&BitMask_01)
#define	TM0CON_PWMLw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TM0CON_PWMOr				(ValSft_R06(_rd32(TIMER_BASE0+0x04))&BitMask_01)
#define	TM0CON_PWMOw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	TM0CON_CAPMODr				(ValSft_R08(_rd32(TIMER_BASE0+0x04))&BitMask_03)
#define	TM0CON_CAPMODw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))
#define	TM0CON_OVSTr				(ValSft_R11(_rd32(TIMER_BASE0+0x04))&BitMask_01)
#define	TM0CON_OVSTw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))
#define	TM0CON_OCENr				(ValSft_R13(_rd32(TIMER_BASE0+0x04))&BitMask_01)
#define	TM0CON_OCENw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))
#define	TM0CON_TMODr				(ValSft_R14(_rd32(TIMER_BASE0+0x04))&BitMask_02)
#define	TM0CON_TMODw(val)			_wr32(TIMER_BASE0+0x04,((_rd32(TIMER_BASE0+0x04)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))
                                	
#define	TM0CNTr						_rd32(TIMER_BASE0+0x08)
#define	TM0CNTw(val)				_wr32(TIMER_BASE0+0x08,val)
                                	
#define	TM0DUTr						_rd32(TIMER_BASE0+0x0C)
#define	TM0DUTw(val)				_wr32(TIMER_BASE0+0x0C,val)
                                	
#define	TM0PULr						_rd32(TIMER_BASE0+0x10)
#define	TM0PULw(val)				_wr32(TIMER_BASE0+0x10,val)

//..............................................................
// Ch 1
#define	TP1CON_CLKSELr				(ValSft_R00(_rd32(TIMER_BASE1+0x00))&BitMask_01)
#define	TP1CON_CLKSELw(val)			_wr32(TIMER_BASE1+0x00,((_rd32(TIMER_BASE1+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TP1CON_CNTCLRr				(ValSft_R01(_rd32(TIMER_BASE1+0x00))&BitMask_01)
#define	TP1CON_CNTCLRw(val)			_wr32(TIMER_BASE1+0x00,((_rd32(TIMER_BASE1+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
                                	
#define	TM1CON_TMENr				(ValSft_R00(_rd32(TIMER_BASE1+0x04))&BitMask_01)
#define	TM1CON_TMENw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TM1CON_PFSELr				(ValSft_R01(_rd32(TIMER_BASE1+0x04))&BitMask_03)
#define	TM1CON_PFSELw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L01(BitMask_03)))|ValSft_L01((val)&BitMask_03)))
                                	
#define	TM1CON_PWMLr				(ValSft_R05(_rd32(TIMER_BASE1+0x04))&BitMask_01)
#define	TM1CON_PWMLw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TM1CON_PWMOr				(ValSft_R06(_rd32(TIMER_BASE1+0x04))&BitMask_01)
#define	TM1CON_PWMOw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	TM1CON_CAPMODr				(ValSft_R08(_rd32(TIMER_BASE1+0x04))&BitMask_03)
#define	TM1CON_CAPMODw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))
#define	TM1CON_OVSTr				(ValSft_R11(_rd32(TIMER_BASE1+0x04))&BitMask_01)
#define	TM1CON_OVSTw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))
#define	TM1CON_OCENr				(ValSft_R13(_rd32(TIMER_BASE1+0x04))&BitMask_01)
#define	TM1CON_OCENw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))
#define	TM1CON_TMODr				(ValSft_R14(_rd32(TIMER_BASE1+0x04))&BitMask_02)
#define	TM1CON_TMODw(val)			_wr32(TIMER_BASE1+0x04,((_rd32(TIMER_BASE1+0x04)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))
                                	
#define	TM1CNTr						_rd32(TIMER_BASE1+0x08)
#define	TM1CNTw(val)				_wr32(TIMER_BASE1+0x08,val)
                                	
#define	TM1DUTr						_rd32(TIMER_BASE1+0x0C)
#define	TM1DUTw(val)				_wr32(TIMER_BASE1+0x0C,val)
                                	
#define	TM1PULr						_rd32(TIMER_BASE1+0x10)
#define	TM1PULw(val)				_wr32(TIMER_BASE1+0x10,val)

//..............................................................
// Ch 2 (pwm)
#define	TP2CON_CLKSELr				(ValSft_R00(_rd32(TIMER_BASE2+0x00))&BitMask_01)
#define	TP2CON_CLKSELw(val)			_wr32(TIMER_BASE2+0x00,((_rd32(TIMER_BASE2+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TP2CON_CNTCLRr				(ValSft_R01(_rd32(TIMER_BASE2+0x00))&BitMask_01)
#define	TP2CON_CNTCLRw(val)			_wr32(TIMER_BASE2+0x00,((_rd32(TIMER_BASE2+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
                                	
#define	TM2CON_TMENr				(ValSft_R00(_rd32(TIMER_BASE2+0x04))&BitMask_01)
#define	TM2CON_TMENw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TM2CON_PFSELr				(ValSft_R01(_rd32(TIMER_BASE2+0x04))&BitMask_03)
#define	TM2CON_PFSELw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L01(BitMask_03)))|ValSft_L01((val)&BitMask_03)))
#define	TM2CON_PWMLr				(ValSft_R05(_rd32(TIMER_BASE2+0x04))&BitMask_01)
#define	TM2CON_PWMLw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TM2CON_PWMOr				(ValSft_R06(_rd32(TIMER_BASE2+0x04))&BitMask_01)
#define	TM2CON_PWMOw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	TM2CON_CAPMODr				(ValSft_R08(_rd32(TIMER_BASE2+0x04))&BitMask_03)
#define	TM2CON_CAPMODw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))
#define	TM2CON_OVSTr				(ValSft_R11(_rd32(TIMER_BASE2+0x04))&BitMask_01)
#define	TM2CON_OVSTw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))
#define	TM2CON_OCENr				(ValSft_R13(_rd32(TIMER_BASE2+0x04))&BitMask_01)
#define	TM2CON_OCENw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))
#define	TM2CON_TMODr				(ValSft_R14(_rd32(TIMER_BASE2+0x04))&BitMask_02)
#define	TM2CON_TMODw(val)			_wr32(TIMER_BASE2+0x04,((_rd32(TIMER_BASE2+0x04)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))
                                	
#define	TM2CNTr						_rd32(TIMER_BASE2+0x08)
#define	TM2CNTw(val)				_wr32(TIMER_BASE2+0x08,val)
                                	
#define	TM2DUTr						_rd32(TIMER_BASE2+0x0C)
#define	TM2DUTw(val)				_wr32(TIMER_BASE2+0x0C,val)
                                	
#define	TM2PULr						_rd32(TIMER_BASE2+0x10)
#define	TM2PULw(val)				_wr32(TIMER_BASE2+0x10,val)

//..............................................................
// Ch 3
#define	TP3CON_CLKSELr				(ValSft_R00(_rd32(TIMER_BASE3+0x00))&BitMask_01)
#define	TP3CON_CLKSELw(val)			_wr32(TIMER_BASE3+0x00,((_rd32(TIMER_BASE3+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TP3CON_CNTCLRr				(ValSft_R01(_rd32(TIMER_BASE3+0x00))&BitMask_01)
#define	TP3CON_CNTCLRw(val)			_wr32(TIMER_BASE3+0x00,((_rd32(TIMER_BASE3+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
                                	
#define	TM3CON_TMENr				(ValSft_R00(_rd32(TIMER_BASE3+0x04))&BitMask_01)
#define	TM3CON_TMENw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TM3CON_PFSELr				(ValSft_R01(_rd32(TIMER_BASE3+0x04))&BitMask_03)
#define	TM3CON_PFSELw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L01(BitMask_03)))|ValSft_L01((val)&BitMask_03)))
#define	TM3CON_PWMLr				(ValSft_R05(_rd32(TIMER_BASE3+0x04))&BitMask_01)
#define	TM3CON_PWMLw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TM3CON_PWMOr				(ValSft_R06(_rd32(TIMER_BASE3+0x04))&BitMask_01)
#define	TM3CON_PWMOw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	TM3CON_CAPMODr				(ValSft_R08(_rd32(TIMER_BASE3+0x04))&BitMask_03)
#define	TM3CON_CAPMODw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))
#define	TM3CON_OVSTr				(ValSft_R11(_rd32(TIMER_BASE3+0x04))&BitMask_01)
#define	TM3CON_OVSTw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))
#define	TM3CON_OCENr				(ValSft_R13(_rd32(TIMER_BASE3+0x04))&BitMask_01)
#define	TM3CON_OCENw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))
#define	TM3CON_TMODr				(ValSft_R14(_rd32(TIMER_BASE3+0x04))&BitMask_02)
#define	TM3CON_TMODw(val)			_wr32(TIMER_BASE3+0x04,((_rd32(TIMER_BASE3+0x04)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))
                                	
#define	TM3CNTr						_rd32(TIMER_BASE3+0x08)
#define	TM3CNTw(val)				_wr32(TIMER_BASE3+0x08,val)
                                	
#define	TM3DUTr						_rd32(TIMER_BASE3+0x0C)
#define	TM3DUTw(val)				_wr32(TIMER_BASE3+0x0C,val)
                                	
#define	TM3PULr						_rd32(TIMER_BASE3+0x10)
#define	TM3PULw(val)				_wr32(TIMER_BASE3+0x10,val)

//..............................................................
// Ch 5 (pwm)
#define	TP5CON_CLKSELr				(ValSft_R00(_rd32(TIMER_BASE5+0x00))&BitMask_01)
#define	TP5CON_CLKSELw(val)			_wr32(TIMER_BASE5+0x00,((_rd32(TIMER_BASE5+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TP5CON_CNTCLRr				(ValSft_R01(_rd32(TIMER_BASE5+0x00))&BitMask_01)
#define	TP5CON_CNTCLRw(val)			_wr32(TIMER_BASE5+0x00,((_rd32(TIMER_BASE5+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define	TM5CON_TMENr				(ValSft_R00(_rd32(TIMER_BASE5+0x04))&BitMask_01)
#define	TM5CON_TMENw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	TM5CON_PFSELr				(ValSft_R01(_rd32(TIMER_BASE5+0x04))&BitMask_03)
#define	TM5CON_PFSELw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L01(BitMask_03)))|ValSft_L01((val)&BitMask_03)))
#define	TM5CON_PWMLr				(ValSft_R05(_rd32(TIMER_BASE5+0x04))&BitMask_01)
#define	TM5CON_PWMLw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	TM5CON_PWMOr				(ValSft_R06(_rd32(TIMER_BASE5+0x04))&BitMask_01)
#define	TM5CON_PWMOw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	TM5CON_CAPMODr				(ValSft_R08(_rd32(TIMER_BASE5+0x04))&BitMask_03)
#define	TM5CON_CAPMODw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))
#define	TM5CON_OVSTr				(ValSft_R11(_rd32(TIMER_BASE5+0x04))&BitMask_01)
#define	TM5CON_OVSTw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))
#define	TM5CON_OCENr				(ValSft_R13(_rd32(TIMER_BASE5+0x04))&BitMask_01)
#define	TM5CON_OCENw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))
#define	TM5CON_TMODr				(ValSft_R14(_rd32(TIMER_BASE5+0x04))&BitMask_02)
#define	TM5CON_TMODw(val)			_wr32(TIMER_BASE5+0x04,((_rd32(TIMER_BASE5+0x04)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define	TM5CNTr						_rd32(TIMER_BASE5+0x08)
#define	TM5CNTw(val)				_wr32(TIMER_BASE5+0x08,val)

#define	TM5DUTr						_rd32(TIMER_BASE5+0x0C)
#define	TM5DUTw(val)				_wr32(TIMER_BASE5+0x0C,val)

#define	TM5PULr						_rd32(TIMER_BASE5+0x10)
#define	TM5PULw(val)				_wr32(TIMER_BASE5+0x10,val)


//*************************************************************************************************
// SPI
//-------------------------------------------------------------------------------------------------

#define SPI_BASE					0x30002400	// CH1

#define	SPICON_SPISIZEr			(ValSft_R00(_rd32(SPI_BASE+0x00))&BitMask_02)
#define	SPICON_SPISIZEw(val)	_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))
#define	SPICON_LSBFr			(ValSft_R02(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_LSBFw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define	SPICON_CPHAr			(ValSft_R03(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_CPHAw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	SPICON_CPOLr			(ValSft_R04(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_CPOLw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	SPICON_MSTRr			(ValSft_R05(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_MSTRw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	SPICON_WOMPr			(ValSft_R06(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_WOMPw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	SPICON_SPIENr			(ValSft_R07(_rd32(SPI_BASE+0x00))&BitMask_01)
#define	SPICON_SPIENw(val)		_wr32(SPI_BASE+0x00,((_rd32(SPI_BASE+0x00)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define	SPIBAUDr				_rd32(SPI_BASE+0x04)
#define	SPIBAUDw(val)			_wr32(SPI_BASE+0x04,val)

#define	SPISTAT_SRXEr			(ValSft_R00(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_SRXFr			(ValSft_R01(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_STXEr			(ValSft_R02(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_STXFr			(ValSft_R03(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_SSXr			(ValSft_R04(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_MODFr			(ValSft_R05(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_WCOLr			(ValSft_R06(_rd32(SPI_BASE+0x08))&BitMask_01)
#define	SPISTAT_SPIFr			(ValSft_R07(_rd32(SPI_BASE+0x08))&BitMask_01)

#define	SPIDATAr				_rd32(SPI_BASE+0x0C)
#define	SPIDATAw(val)			_wr32(SPI_BASE+0x0C,val)

#define	SSXCONr					_rd32(SPI_BASE+0x10)
#define	SSXCONw(val)			_wr32(SPI_BASE+0x10,val)

#define	SPIINT_SRXEEr			(ValSft_R00(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_SRXEEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	SPIINT_SRXFEr			(ValSft_R01(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_SRXFEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define	SPIINT_STXEEr			(ValSft_R02(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_STXEEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define	SPIINT_STXFEr			(ValSft_R03(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_STXFEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	SPIINT_SSENr			(ValSft_R04(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_SSENw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	SPIINT_MODFEr			(ValSft_R06(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_MODFEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	SPIINT_SPIFEr			(ValSft_R07(_rd32(SPI_BASE+0x14))&BitMask_01)
#define	SPIINT_SPIFEw(val)		_wr32(SPI_BASE+0x14,((_rd32(SPI_BASE+0x14)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))


#define SPI2_BASE					0x30002440	// CH2


#define	SPI2CON_SPISIZEr			(ValSft_R00(_rd32(SPI2_BASE+0x00))&BitMask_02)
#define	SPI2CON_SPISIZEw(val)	_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))
#define	SPI2CON_LSBFr			(ValSft_R02(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_LSBFw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define	SPI2CON_CPHAr			(ValSft_R03(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_CPHAw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	SPI2CON_CPOLr			(ValSft_R04(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_CPOLw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	SPI2CON_MSTRr			(ValSft_R05(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_MSTRw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))
#define	SPI2CON_WOMPr			(ValSft_R06(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_WOMPw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	SPI2CON_SPIENr			(ValSft_R07(_rd32(SPI2_BASE+0x00))&BitMask_01)
#define	SPI2CON_SPIENw(val)		_wr32(SPI2_BASE+0x00,((_rd32(SPI2_BASE+0x00)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define	SPI2BAUDr				_rd32(SPI2_BASE+0x04)
#define	SPI2BAUDw(val)			_wr32(SPI2_BASE+0x04,val)

#define	SPI2STAT_SRXEr			(ValSft_R00(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_SRXFr			(ValSft_R01(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_STXEr			(ValSft_R02(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_STXFr			(ValSft_R03(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_SSXr			(ValSft_R04(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_MODFr			(ValSft_R05(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_WCOLr			(ValSft_R06(_rd32(SPI2_BASE+0x08))&BitMask_01)
#define	SPI2STAT_SPIFr			(ValSft_R07(_rd32(SPI2_BASE+0x08))&BitMask_01)

#define	SPI2DATAr				_rd32(SPI2_BASE+0x0C)
#define	SPI2DATAw(val)			_wr32(SPI2_BASE+0x0C,val)

#define	SSX2CONr					_rd32(SPI2_BASE+0x10)
#define	SSX2CONw(val)			_wr32(SPI2_BASE+0x10,val)

#define	SPI2INT_SRXEEr			(ValSft_R00(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_SRXEEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	SPI2INT_SRXFEr			(ValSft_R01(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_SRXFEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define	SPI2INT_STXEEr			(ValSft_R02(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_STXEEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))
#define	SPI2INT_STXFEr			(ValSft_R03(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_STXFEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	SPI2INT_SSENr			(ValSft_R04(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_SSENw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))
#define	SPI2INT_MODFEr			(ValSft_R06(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_MODFEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))
#define	SPI2INT_SPIFEr			(ValSft_R07(_rd32(SPI2_BASE+0x14))&BitMask_01)
#define	SPI2INT_SPIFEw(val)		_wr32(SPI2_BASE+0x14,((_rd32(SPI2_BASE+0x14)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

//*************************************************************************************************
// IRQ
//-------------------------------------------------------------------------------------------------

//#define	INTP_BASE				0x30001C00            //  EN773
#define	INTP_BASE					0xFFFF0000              //  EN777


#define	IPCw(val)					_wr32(INTP_BASE+0x00,val)
                        			
#define	EIMr						_rd32(INTP_BASE+0x04)
#define	EIMw(val)					_wr32(INTP_BASE+0x04,val)
                        			
#define	IIMr						_rd32(INTP_BASE+0x08)
#define	IIMw(val)					_wr32(INTP_BASE+0x08,val)
                        			
#define	IPr							_rd32(INTP_BASE+0x0C)
                        			
#define	IENr						_rd32(INTP_BASE+0x10)
#define	IENw(val)					_wr32(INTP_BASE+0x10,val)
                        			
#define	IMKSTr						_rd32(INTP_BASE+0x14)
#define	IMKSTw(val)					_wr32(INTP_BASE+0x14,val)
                        			
#define	IMKCLw(val)					_wr32(INTP_BASE+0x18,val)
                        			
#define	PPENr						_rd32(INTP_BASE+0x1C)
#define	PPENw(val)					_wr32(INTP_BASE+0x1C,val)
                            		
#define	IPV0_VCT00r					(ValSft_R00(_rd32(INTP_BASE+0x20))&BitMask_05)
#define	IPV0_VCT01r					(ValSft_R08(_rd32(INTP_BASE+0x20))&BitMask_05)
#define	IPV0_VCT02r					(ValSft_R16(_rd32(INTP_BASE+0x20))&BitMask_05)
#define	IPV0_VCT03r					(ValSft_R24(_rd32(INTP_BASE+0x20))&BitMask_05)
#define	IPV0_VCT00w(val)			_wr32(INTP_BASE+0x20,((_rd32(INTP_BASE+0x20)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV0_VCT01w(val)			_wr32(INTP_BASE+0x20,((_rd32(INTP_BASE+0x20)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV0_VCT02w(val)			_wr32(INTP_BASE+0x20,((_rd32(INTP_BASE+0x20)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV0_VCT03w(val)			_wr32(INTP_BASE+0x20,((_rd32(INTP_BASE+0x20)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV1_VCT04r					(ValSft_R00(_rd32(INTP_BASE+0x24))&BitMask_05)
#define	IPV1_VCT05r					(ValSft_R08(_rd32(INTP_BASE+0x24))&BitMask_05)
#define	IPV1_VCT06r					(ValSft_R16(_rd32(INTP_BASE+0x24))&BitMask_05)
#define	IPV1_VCT07r					(ValSft_R24(_rd32(INTP_BASE+0x24))&BitMask_05)
#define	IPV1_VCT04w(val)			_wr32(INTP_BASE+0x24,((_rd32(INTP_BASE+0x24)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV1_VCT05w(val)			_wr32(INTP_BASE+0x24,((_rd32(INTP_BASE+0x24)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV1_VCT06w(val)			_wr32(INTP_BASE+0x24,((_rd32(INTP_BASE+0x24)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV1_VCT07w(val)			_wr32(INTP_BASE+0x24,((_rd32(INTP_BASE+0x24)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV2_VCT08r					(ValSft_R00(_rd32(INTP_BASE+0x28))&BitMask_05)
#define	IPV2_VCT09r					(ValSft_R08(_rd32(INTP_BASE+0x28))&BitMask_05)
#define	IPV2_VCT10r					(ValSft_R16(_rd32(INTP_BASE+0x28))&BitMask_05)
#define	IPV2_VCT11r					(ValSft_R24(_rd32(INTP_BASE+0x28))&BitMask_05)
#define	IPV2_VCT08w(val)			_wr32(INTP_BASE+0x28,((_rd32(INTP_BASE+0x28)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV2_VCT09w(val)			_wr32(INTP_BASE+0x28,((_rd32(INTP_BASE+0x28)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV2_VCT10w(val)			_wr32(INTP_BASE+0x28,((_rd32(INTP_BASE+0x28)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV2_VCT11w(val)			_wr32(INTP_BASE+0x28,((_rd32(INTP_BASE+0x28)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV3_VCT12r					(ValSft_R00(_rd32(INTP_BASE+0x2C))&BitMask_05)
#define	IPV3_VCT13r					(ValSft_R08(_rd32(INTP_BASE+0x2C))&BitMask_05)
#define	IPV3_VCT14r					(ValSft_R16(_rd32(INTP_BASE+0x2C))&BitMask_05)
#define	IPV3_VCT15r					(ValSft_R24(_rd32(INTP_BASE+0x2C))&BitMask_05)
#define	IPV3_VCT12w(val)			_wr32(INTP_BASE+0x2C,((_rd32(INTP_BASE+0x2C)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV3_VCT13w(val)			_wr32(INTP_BASE+0x2C,((_rd32(INTP_BASE+0x2C)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV3_VCT14w(val)			_wr32(INTP_BASE+0x2C,((_rd32(INTP_BASE+0x2C)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV3_VCT15w(val)			_wr32(INTP_BASE+0x2C,((_rd32(INTP_BASE+0x2C)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV4_VCT16r					(ValSft_R00(_rd32(INTP_BASE+0x30))&BitMask_05)
#define	IPV4_VCT17r					(ValSft_R08(_rd32(INTP_BASE+0x30))&BitMask_05)
#define	IPV4_VCT18r					(ValSft_R16(_rd32(INTP_BASE+0x30))&BitMask_05)
#define	IPV4_VCT19r					(ValSft_R24(_rd32(INTP_BASE+0x30))&BitMask_05)
#define	IPV4_VCT16w(val)			_wr32(INTP_BASE+0x30,((_rd32(INTP_BASE+0x30)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV4_VCT17w(val)			_wr32(INTP_BASE+0x30,((_rd32(INTP_BASE+0x30)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV4_VCT18w(val)			_wr32(INTP_BASE+0x30,((_rd32(INTP_BASE+0x30)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV4_VCT19w(val)			_wr32(INTP_BASE+0x30,((_rd32(INTP_BASE+0x30)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV5_VCT20r					(ValSft_R00(_rd32(INTP_BASE+0x34))&BitMask_05)
#define	IPV5_VCT21r					(ValSft_R08(_rd32(INTP_BASE+0x34))&BitMask_05)
#define	IPV5_VCT22r					(ValSft_R16(_rd32(INTP_BASE+0x34))&BitMask_05)
#define	IPV5_VCT23r					(ValSft_R24(_rd32(INTP_BASE+0x34))&BitMask_05)
#define	IPV5_VCT20w(val)			_wr32(INTP_BASE+0x34,((_rd32(INTP_BASE+0x34)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV5_VCT21w(val)			_wr32(INTP_BASE+0x34,((_rd32(INTP_BASE+0x34)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV5_VCT22w(val)			_wr32(INTP_BASE+0x34,((_rd32(INTP_BASE+0x34)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV5_VCT23w(val)			_wr32(INTP_BASE+0x34,((_rd32(INTP_BASE+0x34)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV6_VCT24r					(ValSft_R00(_rd32(INTP_BASE+0x38))&BitMask_05)
#define	IPV6_VCT25r					(ValSft_R08(_rd32(INTP_BASE+0x38))&BitMask_05)
#define	IPV6_VCT26r					(ValSft_R16(_rd32(INTP_BASE+0x38))&BitMask_05)
#define	IPV6_VCT27r					(ValSft_R24(_rd32(INTP_BASE+0x38))&BitMask_05)
#define	IPV6_VCT24w(val)			_wr32(INTP_BASE+0x38,((_rd32(INTP_BASE+0x38)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV6_VCT25w(val)			_wr32(INTP_BASE+0x38,((_rd32(INTP_BASE+0x38)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV6_VCT26w(val)			_wr32(INTP_BASE+0x38,((_rd32(INTP_BASE+0x38)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV6_VCT27w(val)			_wr32(INTP_BASE+0x38,((_rd32(INTP_BASE+0x38)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))
                            		
#define	IPV7_VCT28r					(ValSft_R00(_rd32(INTP_BASE+0x3C))&BitMask_05)
#define	IPV7_VCT29r					(ValSft_R08(_rd32(INTP_BASE+0x3C))&BitMask_05)
#define	IPV7_VCT30r					(ValSft_R16(_rd32(INTP_BASE+0x3C))&BitMask_05)
#define	IPV7_VCT31r					(ValSft_R24(_rd32(INTP_BASE+0x3C))&BitMask_05)
#define	IPV7_VCT28w(val)			_wr32(INTP_BASE+0x3C,((_rd32(INTP_BASE+0x3C)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))
#define	IPV7_VCT29w(val)			_wr32(INTP_BASE+0x3C,((_rd32(INTP_BASE+0x3C)&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))
#define	IPV7_VCT30w(val)			_wr32(INTP_BASE+0x3C,((_rd32(INTP_BASE+0x3C)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))
#define	IPV7_VCT31w(val)			_wr32(INTP_BASE+0x3C,((_rd32(INTP_BASE+0x3C)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))


//*************************************************************************************************
// GPIO
//-------------------------------------------------------------------------------------------------
// Reg bit macro
#define	PMUX_BASE					0x30001400
#define	GPIO_BASE					0x30001800

#define PMUXr						(ValSft_R00(_rd32(PMUX_BASE+0x04))&BitMask_32)
#define	PMUXw(val)					_wr32(PMUX_BASE+0x04,((_rd32(PMUX_BASE+0x04)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))
                            		
#define	PDIRr(p)					_rd32(GPIO_BASE+(0x40*p)+0x00)
                            		
#define	PODIRw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x00,val)
                            		
#define	PIDIRw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x04,val)
                            		
#define	POLEVr(p)					_rd32(GPIO_BASE+(0x40*p)+0x08)
                            		
#define	POHIGHw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x08,val)
                            		
#define	POLOWw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x0C,val)
                            		
#define	PILEVr(p)					_rd32(GPIO_BASE+(0x40*p)+0x10)
                            		
#define	PPUSr(p)					_rd32(GPIO_BASE+(0x40*p)+0x18)
                            		
#define	PPUENw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x18,val)
                            		
#define	PUDISw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x1C,val)
                            		
#define	PREDr(p)					_rd32(GPIO_BASE+(0x40*p)+0x20)
#define	PREDw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x20,val)
                            		
#define	PFEDr(p)					_rd32(GPIO_BASE+(0x40*p)+0x24)
#define	PFEDw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x24,val)
                            		
#define	PEDSr(p)					_rd32(GPIO_BASE+(0x40*p)+0x28)
#define	PEDSw(p,val)				_wr32(GPIO_BASE+(0x40*p)+0x28,val)
                            		
#define	PODMr(p)					_rd32(GPIO_BASE+(0x40*p)+0x2c)


//*************************************************************************************************
// FLASH
//-------------------------------------------------------------------------------------------------

#define	SF_BASE						0x30000000
                                	
#define SFMODr						_rd32(SF_BASE+0x00)
#define SFMODw(val)					_wr32(SF_BASE+0x00,val)
#define	SFMOD_BRCr					(ValSft_R03(_rd32(SF_BASE+0x00))&BitMask_01)
#define	SFMOD_BRCw(val)				_wr32(SF_BASE+0x00,((_rd32(SF_BASE+0x00)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))
#define	SFMOD_BEEr					(ValSft_R07(_rd32(SF_BASE+0x00))&BitMask_01)
#define	SFMOD_BEEw(val)				_wr32(SF_BASE+0x00,((_rd32(SF_BASE+0x00)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))
#define SRBRTr						_rd32(SF_BASE+0x04)
#define SRBRTw(val)					_wr32(SF_BASE+0x04,val)
#define SFCHSr						_rd32(SF_BASE+0x08)
#define SFCHSw(val)					_wr32(SF_BASE+0x08,val)
#define SFPEMr						_rd32(SF_BASE+0x0c)
#define SFPEMw(val)					_wr32(SF_BASE+0x0c,val)
#define SFCMDr						_rd32(SF_BASE+0x10)
#define SFCMDw(val)					_wr32(SF_BASE+0x10,val)
#define SFSTSr						_rd32(SF_BASE+0x14)
#define SFSTSw(val)					_wr32(SF_BASE+0x14,val)
#define SFSEAr						_rd32(SF_BASE+0x18)
#define SFSEAw(val)					_wr32(SF_BASE+0x18,val)
#define SFBEAr						_rd32(SF_BASE+0x1c)
#define SFBEAw(val)					_wr32(SF_BASE+0x1c,val)
#define SFDATr						_rd32(SF_BASE+0x20)
#define SFDATw(val)					_wr32(SF_BASE+0x20,val)
#define SFWCPr						_rd32(SF_BASE+0x24)
#define SFWCPw(val)					_wr32(SF_BASE+0x24,val)


//*************************************************************************************************
// WDT
//-------------------------------------------------------------------------------------------------

#define	WDT_BASE					0x30001000
                                	
#define	WDTCONr						_rd32(WDT_BASE+0x00)
#define	WDTCONw(val)				_wr32(WDT_BASE+0x00,val)
#define	WDTCON_WDTENr				(ValSft_R00(_rd32(WDT_BASE+0x00))&BitMask_01)
#define	WDTCON_WDTENw(val)			_wr32(WDT_BASE+0x00,((_rd32(WDT_BASE+0x00)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))
#define	WDTCON_WDTMODEr				(ValSft_R01(_rd32(WDT_BASE+0x00))&BitMask_01)
#define	WDTCON_WDTMODEw(val)		_wr32(WDT_BASE+0x00,((_rd32(WDT_BASE+0x00)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))
#define	WDTCON_WDTSTr				(ValSft_R04(_rd32(WDT_BASE+0x00))&BitMask_01)
                                	
#define	WDTCNTr						_rd32(WDT_BASE+0x04)
#define	WDTCNTw(val)				_wr32(WDT_BASE+0x04,val)

