/* **************************************************************************
 File Name	: 	dev.h
 Description:	EN777 - Device Driver
 Designer	:	Lee, Hoon
 Date		:	12. 9. 20
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
		 1. System
		 2. GPIO
		 3. ADC
		 4. DEV
		 5. UART
		 6. TWI
		 7. TIMER
		 8. SPI
		 9. IRQ
		10. FLASH
		11. WDT
		12. ISP
		13. SENSOR

*/

//*************************************************************************************************
// Software version info & fixed define
//-------------------------------------------------------------------------------------------------

	#define 	model_ver			0x7705		// Eyenix base code version

	#define 	SENS_MN34031			0		// Panasonic 1.3M
	#define 	SENS_MN34041			10		// Panasonic 2M
	#define 	SENS_MN34220			11		// Panasonic 2M
	#define 	SENS_IMX136				13		// Sony 2M

//*************************************************************************************************
// System Mode user define
//-------------------------------------------------------------------------------------------------

	#define 	model_Sens		SENS_MN34041		// Sensor selection

//	#define		model_TgtBd				2		// Target board
												// 0: Enx Socket Bd, 1: Enx EV4242 Bd, 2: customer

//	#define		model_Dout				3		/* Digital Output mode selection */

												// 0: internal HD-SDI only (not use)
												// 1: internal HD-SDI + Parallel (not use)
												// 2: Parallel (use External HD-SDI TX (ex.GENNUM) )
												// 3: Parallel (use External other device)

//	#define		model_Cvbs				0		// 0: 720H target
												// 1: 960H target (need supplying 36MHz clk source to pad K14, ECK_SEL=0x1h)

//	#define		model_CvbsOn			0		// 0 : Manual On/Off
												// 1 : Auto On/Off (need AD circuit)

//	#define		model_Lens				0		// Lens type
												// 0 : normal, 1 : 2Motor, 2 : AF

//	#define		model_Iris				1		// IRIS control by
												// 0: (not use), 1: KIWI driver(DC),  2: MPWM(DC), 3: Step motor(pIris) 4: AF drvIC (PID) 5: no IRIS

//	#define		model_Tdn				0		// 0 : TDN control by 1 port 2 state (H, L)
												// 1 : TDN control by 1 port 3 state (H, L, Hi-z)
												// 2 : TDN control by 2 ports

//	#define		model_Cds				1		// 0 : CDS input by ADC
												// 1 : CDS input by GPIO

//	#define		model_Led				1		// 0 : LED control by LPWM
												// 1 : LED control by GPIO

//	#define 	model_Shade				0		// 0 : Shading table by Storage dumpping
												// 1 : Shading table by defined array

//	#define 	model_Save				0		// 0 : User data save to External EEPROM by IIC(TWI) (default)
												// 1 : User data save to internal Flash

//	#define 	model_Flash				0		// 0 : Flash - Eon Quad
												// 1 : Flash - Winbond Quad

//	#define		model_Protect			0		// 0 : not use Flash Protection
												// 1 : use Flash Protection (default)

//	#define		model_Par				0		// 0 : not use user parameter (use define function arg.)
												// 1 : use user parameter (use variable function arg.)

//	#define 	model_Uart2				1		// 0 : not use UART CH2
												// 1 : use UART CH2

//	#define 	model_Key				0		// 0 : KEY input by ADC
												// 1 : KEY input by GPIO

//	#define 	model_CharMax			0		// 0 : Font char max ea - 256 (BYTE)
												// 1 : Font char max ea - ISP_FONT_CHAR_EA (WORD)

//	#define 	model_Test				0		// 0 : Test mode off (normal operation)
												// 1 : Test mode on (test without sensor. Sensor have to drive to slave(HW))
												// 2 : Test mode on (test without mode change function - 30p only)


	// Special Functions ------------------------------------------------------

//	#define 	model_spc_Af			0		// Auto Focus

//	#define		model_spc_SmtIr			0		// Smart IR Led

//	#define		model_spc_Dis			0		// Digital Image Stabillizer

//	#define		model_spc_ItlTrk		0		// Intelligent Motion Tracking


#include "Miclib_type.h"
#include "dev_misc.h"
#include "dev_reg_cpu.h"
#include "dev_reg_isp.h"

//*************************************************************************************************
// GPIO
// -----------------------------------------------------------------------------------------------
// assign GPIO Pin no. (0 ~ 31)
#if 0
enum{
	GPIO_BOOT = 0,
	GPIO_RMC_DATA,
	GPIO_IR_ON,
	GPIO_SEN_CS,
	GPIO_RXD2,
	GPIO_TXD2,  //5
	GPIO_M_CS,
	GPIO_M_SO,
	GPIO_M_SCK,
	GPIO_SEN_SI,
	GPIO_SEN_SO,   //10
	GPIO_SEN_SCK,
	GPIO_DENO,
	GPIO_M_SI,
	GPIO_SEN_RST,

	GPIO_EEP_SCL, //15
	GPIO_EEP_SDA,

	GPIO_TELE,
	GPIO_WIDE,
	GPIO_NEAR,
	GPIO_FAR,		//20

	GPIO_MENU,
	GPIO_DN_IN1,
	GPIO_DN_IN2,
	GPIO_C_REBOOT,
	GPIO_25,		//25
	GPIO_M_RST,
	GPIO_325_RST,
	GPIO_ADC_CS,
	GPIO_29,
	GPIO_H_SO,
	GPIO_F_SO,
};

#define	GPIO_ADC_SCK GPIO_SEN_SCK
#define	GPIO_ADC_SI GPIO_SEN_SI
#define	GPIO_ADC_SO GPIO_SEN_SO

#endif


//-------------------------------------------------------------------------------------------------
// Macro
#define GpioDiv(p)			(p/8)
#define GpioRem(p)			(p%8)

//-------------------------------------------------------------------------------------------------
// Extern
#if 0
#define	GpioFuncPin(aiIn)	PMUXw(PMUXr & ~(1<<aiIn))											// PinMux Function : GPIO, FUNC

																								// Direction : Gpio direction set to output
#define	GpioOutDir(aiIn)	{\
							PODIRw(GpioDiv(aiIn), PDIRr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) );\
							PIDIRw(GpioDiv(aiIn), ~PDIRr(GpioDiv(aiIn)) );\
							}

#define	GpioInDir(aiIn)		PIDIRw(GpioDiv(aiIn), ~PDIRr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) )	// Direction : Gpio direction set to input

#define GpioSetHi(aiIn)		POHIGHw(GpioDiv(aiIn), POLEVr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) )	// Output Pin Setting : HIGH

#define	GpioSetLo(aiIn)		POLOWw(GpioDiv(aiIn), ~POLEVr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) )	// Output Pin Setting : LOW

#define GpioGetPin(aiIn)	((PILEVr(GpioDiv(aiIn)) & (1<<GpioRem(aiIn))) >> GpioRem(aiIn))		// Input level : PILEV

#define GpioPullUpEn(aiIn)	PPUENw(GpioDiv(aiIn), PPUSr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) )	// Pull up enable

#define GpioPullUpDis(aiIn)	PUDISw(GpioDiv(aiIn), ~PPUSr(GpioDiv(aiIn)) | (1<<GpioRem(aiIn)) )	// Pull up disable
#endif

//*************************************************************************************************
// ADC (in ISP function)
//-------------------------------------------------------------------------------------------------

#if (model_TgtBd==0) // reserved ----------
	#define ADC_KEY		ADC3_RDATr
	#define ADC_CDS		ADC0_RDATr
#elif (model_TgtBd==1) // reserved --------
	#define ADC_KEY		ADC0_RDATr
	#define ADC_CDS		ADC3_RDATr
	#if (model_Lens==2)
		#define ADC_AF1
		#define	ADC_AF2
	#else
		#define	ADC_CVBS	ADC1_RDATr
	#endif
#else
	#define ADC_KEY		ADC0_RDATr
	#define ADC_CDS		ADC3_RDATr
	#if (model_Lens==2)
		#define ADC_AF1
		#define	ADC_AF2
	#endif
#endif


//*************************************************************************************************
// DEV
//-------------------------------------------------------------------------------------------------
// Extern
extern const UINT gnTblIspInit0[];
//extern const UINT gnTblIspMode[][9]; // YMCA
extern const UINT gnTblIspMode[][3]; // YMCA
extern const WORD gwTblSens0[][2];
extern const WORD gwTblSensClk[][3];
extern const UINT gnTblIspCvbs[][3];

extern const UINT gTblIspInitEa;
extern const UINT gTblIspModeEa;
extern const UINT gTblSensEa;
extern const UINT gTblSensClkEa;
extern const UINT gnTblIspCvbsEa;


extern void EnCache (void);
extern void InitCache (void);

extern void IspReg_Set(uint32 Addr,uint32 Dat);
extern uint32 IspReg_Get(uint32 Addr);


//*************************************************************************************************
// UART
//-------------------------------------------------------------------------------------------------
// Misc
#define UART_BUF_SIZE		128			// User buffer size

typedef struct _UART_QUE{				// Queue structure define
	WORD	wRxLen;						// Number of characters in the Rx ring buffer
	BYTE*	pbRxHead;					// Pointer to where next character will be inserted
	BYTE*	pbRxTail;					// Pointer from where next character will be extracted
	BYTE	bRxQue[UART_BUF_SIZE];		// Ring buffer character storage (Rx)

	WORD	wTxLen;						// Number of characters in the Tx ring buffer
	BYTE*	pbTxHead;					// Pointer to where next character will be inserted
	BYTE*	pbTxTail;					// Pointer from where next character will be extracted
	BYTE	bTxQue[UART_BUF_SIZE];		// Ring buffer character storage (Tx)
} TUartQue;

#define	UART_PARNONE		0			// Parity
#define	UART_PARODD			1			//	"
#define	UART_PAREVEN		2			//	"

#define	UART_NO_ERR			0			// No error
#define	UART_RX_FULL		1			// RX buffer full
#define	UART_RX_EMPTY		2			// Rx buffer empty
#define	UART_TX_FULL		3			// Tx buffer full
#define	UART_TX_EMPTY		4			// Tx buffer empty

#define	UART_BAUD(baud)		(PCLK/(baud*16))					// Baud rate calculation
	#define	UB2400			(UART_BAUD(  2400)  )				//		"
	#define	UB4800			(UART_BAUD(  4800)  )
	#define	UB9600			(UART_BAUD(  9600)  )				//		"
	#define	UB19200			(UART_BAUD( 19200)  )				//		"
	#define	UB38400			(UART_BAUD( 38400)+1)				//		"
	#define	UB57600			(UART_BAUD( 57600)  )				//		"
	#define	UB115200		(UART_BAUD(115200)  )				//		"				Caution! care from brt error
//	#define	UB115200		(UART_BAUD(115200)+1)				//		"				Caution! care from brt error

//-------------------------------------------------------------------------------------------------
// Extern

#define	UartEiRx	U0IE_RDAIENw(1)
#define	UartDiRx	U0IE_RDAIENw(0)
#define	UartEiTx	U0IE_THEIENw(1)
#define	UartDiTx	U0IE_THEIENw(0)
#define	UartEiSts	U0IE_RLSIENw(1)
#define	UartDiSts	U0IE_RLSIENw(0)

extern void UartCfg(WORD awBaud, UINT anBit, UINT anPrty, UINT anStop);

extern void UartRstQue(void);
extern void UartRstRxQue(void);
extern void UartRstTxQue(void);

extern BYTE UartPutRx(BYTE abChar);
extern BYTE UartGetTx(BYTE* apbErr);
extern BYTE UartPutByte(BYTE abChar);
extern BYTE UartGetByte(BYTE* apbErr);

extern int  UartIsFull(void);
extern int  UartIsEmpty(void);

extern void UartTxByte(BYTE abByte);
extern void UartTxStr(BYTE* apbStr);
extern void UartPrintf(BYTE* apbStr0, UINT anVal, BYTE* apbStr1);


#define	UartEiRx1	U1IE_RDAIENw(1)
#define	UartDiRx1	U1IE_RDAIENw(0)
#define	UartEiTx1	U1IE_THEIENw(1)
#define	UartDiTx1	U1IE_THEIENw(0)
#define	UartEiSts1	U1IE_RLSIENw(1)
#define	UartDiSts1	U1IE_RLSIENw(0)

extern void UartCfg1(WORD awBaud, UINT anBit, UINT anPrty, UINT anStop);

extern void UartRstQue1(void);
extern void UartRstRxQue1(void);
extern void UartRstTxQue1(void);

extern BYTE UartPutRx1(BYTE abChar);
extern BYTE UartGetTx1(BYTE* apbErr);
extern BYTE UartPutByte1(BYTE abChar);
extern BYTE UartGetByte1(BYTE* apbErr);

extern int  UartIsFull1(void);
extern int  UartIsEmpty1(void);

extern void UartTxByte1(BYTE abByte);
extern void UartTxStr1(BYTE* apbStr);
extern void UartPrintf1(BYTE* apbStr0, UINT anVal, BYTE* apbStr1);

//*************************************************************************************************
// TWI
//-------------------------------------------------------------------------------------------------
// Misc
#define TWI_DEFAULT_SCALE       4
//#define TWI_DEFAULT_MAX_FREQ    1000000
//#define TWI_DEFAULT_MIN_FREQ    16000

#define	TWI_EEP_DEV_ADDR		0xA2									// 24C64 DEV Addr.
#define	TWI_EEP_PAGE_EA			256										// 24C64 PAGE No.
#define	TWI_EEP_BYTE_EA			32										// 24C64 BYTE No. each Page

#define TWI_EEP_MENU_STT		0										// Menu par save pos
#define TWI_EEP_SHADE_STT		(TWI_EEP_MENU_STT+MN_PAR_EA)			// Shading tbl save pos	(each 10bit)
#define TWI_EEP_DEFECT_STT		(TWI_EEP_SHADE_STT+(ISP_SHADING_EA<<1)) // Defect tbl save pos	(each 23bit)
#define TWI_EEP_AWBPRST_STT		(TWI_EEP_DEFECT_STT+(ISP_DEFECT_EA<<2))	// Parameter save pos
#define TWI_EEP_IRIS_STT		(TWI_EEP_AWBPRST_STT+16)

#define TWI_EEP_END				(TWI_EEP_IRIS_STT+16)

#define	TWI_EEP_PAR_STT			TWI_EEP_END		// tmp !!

//-------------------------------------------------------------------------------------------------
// Macro
//#define	TWI_FREQ(freq)		(((PCLK)/freq-(TWI_DEFAULT_SCALE+7))>>1)
//	#define TB50000			TWI_FREQ(50000)								// Scale count
//	#define TB200000		TWI_FREQ(200000)							// Scale count
//
//#define	TWI_SCL(scale,cnt)	((PCLK)/((scale<<1)+cnt+7))					// SCL

#define TWI_SCALE			(((PCLK*7)/10000000) + 3)
#define TWI_FREQ(freq)      ((PCLK/freq-(TWI_SCALE+7))>>1)

//-------------------------------------------------------------------------------------------------
// Extern
#if 0
extern void TwiCfg(UINT anBaud);
extern void TwiStart(BYTE abDevaddr, BYTE* apbWaddr, BYTE abLen, BYTE abRxMode);
extern void TwiWrite(BYTE abDevaddr, BYTE* apbWaddr, BYTE abLen, BYTE* apbBuf, UINT anBufEa);
extern void TwiRead(BYTE abDevaddr, BYTE* apbWaddr,BYTE abLen, BYTE* apbBuf, UINT anBufEa);
extern void TwiWrEep(WORD awWaddr, BYTE* apbBuf, UINT anBufEa);
extern void TwiRdEep(WORD awWaddr,BYTE* apbBuf, UINT anBufEa);
extern BYTE TwiWrEep2(WORD awWaddr, BYTE* apbBuf, UINT anBufEa);
	#define	TwiWrEep2_repeat	TwiWrEep2(0, 0, 0);
extern void TwiIsp2Eep( WORD awEEPaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte);
extern void TwiEep2Isp( WORD awEEPaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte);

extern void SetSensTwi(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern void SetSensTwi2(BYTE abDevaddr, WORD awAddr, WORD abData);
extern BYTE GetSensTwi(BYTE abDevaddr, WORD awAddr);
#endif

//*************************************************************************************************
// TIMER
//-------------------------------------------------------------------------------------------------
// Misc
#define PF_CLKDIV2		0												// Clock selection
#define PF_CLKDIV8		1												//		"
#define PF_CLKDIV32		2												//		"
#define PF_CLKDIV128	3												//		"
#define PF_CLKDIV512	4												//		"
#define PF_CLKDIV2048	5												//		"
#define PF_CLKDIV8192	6												//		"
#define PF_CLKDIV32768	7												//		"

#define PWM_STARTHIGH	1												// Pwm start level r1
#define PWM_STARTLOW	0												//		"

//-------------------------------------------------------------------------------------------------
// Extern
#define		Tm0En				TM0CON_TMENw(1)							// Enable
#define		Tm0Cnt(awIn)		TM0CNTw(awIn)							// count value
extern void Tm0Cfg(UINT anTime, BYTE abPF);

#define		Tm1En				TM1CON_TMENw(1)							// Enable
#define		Tm1Cnt(awIn)		TM1CNTw(awIn)							// count value
extern void Tm1Cfg(BYTE abPF);
extern void TimeChkStt();												// time check start
extern UINT TimeChkEnd();												// time check end

#define		PwmEna				DFSEL_TgtBd(TM5CON_TMENw(1)    , TM2CON_TMENw(1)    , TM2CON_TMENw(1))			// enable
#define		PwmDis				DFSEL_TgtBd(TM5CON_TMENw(0)    , TM2CON_TMENw(0)    , TM2CON_TMENw(0))			// disable
#define		PwmSetPrd(anIn)		DFSEL_TgtBd(TM5CNTw((UINT)anIn), TM2CNTw((UINT)anIn), TM2CNTw((UINT)anIn))		// PWM period
#define		PwmSetDty(anIn)		DFSEL_TgtBd(TM5DUTw((UINT)anIn), TM2DUTw((UINT)anIn), TM2DUTw((UINT)anIn))		// PWM duty (Must be shorter than "TM2CNT_PWMW")
#define		PwmSetNum(anIn)		DFSEL_TgtBd(TM5PULw((UINT)anIn), TM2PULw((UINT)anIn), TM2PULw((UINT)anIn))		// PWM pulse number value
extern void PwmCfg(BYTE abPreFact, BYTE abPol);

#define		Tm3En(void)			TM3CON_TMENw(1)
#define		Tm3Cnt(awIn)		TM3CNTw(awIn)
extern void Tm3Cfg(UINT anTime, BYTE abPF);

//-------------------------------------------------------------------------------------------------
// Variables
extern BYTE gbTm0Out;


//*************************************************************************************************
// SPI
//-------------------------------------------------------------------------------------------------
// Misc
#define	SPI_SIZE8		0								// Data size
#define	SPI_SIZE16		1								//		"
#define	SPI_SIZE32		2								//		"

//-------------------------------------------------------------------------------------------------
// Macro
#define	SPI_BAUD(freq)		((PCLK/(2*freq)) - 1)		// SPI frequency calculation
	#define SB4000000		(SPI_BAUD(4000000))			// 4.0MHz
	#define SB2000000		(SPI_BAUD(2000000))			// 2.0MHz
	#define SB1000000		(SPI_BAUD(1000000))			// 1.0MHz
	#define SB500000		(SPI_BAUD( 500000))			// 0.5MHz

//-------------------------------------------------------------------------------------------------
// Extern
#define		 SpiEna			SPICON_SPIENw(1)			// Enable
#define		 SpiDis			SPICON_SPIENw(0)			// Disable
extern 	void SpiCfg(UINT anBaud, BYTE anSize);

extern 	void SetSensSpi(WORD awAddr, WORD awData);
extern 	void SetSensSpi2(WORD awID, WORD awAddr, WORD awData);
extern	WORD GetSensSpi(WORD awAddr);
//extern	WORD GetSensSpi2(WORD awID, WORD awAddr);

#define		 Spi2Ena		SPI2CON_SPIENw(1)			// Enable
#define		 Spi2Dis		SPI2CON_SPIENw(0)			// Disable
extern 	void Spi2Cfg(UINT anBaud, BYTE anSize);

//*************************************************************************************************
// IRQ
//-------------------------------------------------------------------------------------------------
// Misc
#define	IRQ_EXT0		0x00
#define	IRQ_TIMER0      	0x01
#define	IRQ_DCP0        	0x02							// VLOCKI interrupt
#define	IRQ_DCP1        	0x03							// VLOCKO interrupt
//							0x04
#define	IRQ_TIMER1      	0x05
#define	IRQ_DCP2        	0x06							// ISP USER interrupt0
#define	IRQ_DCP3        	0x07							// ISP USER interrupt1
#define	IRQ_EXT1        	0x08
#define	IRQ_SPI	        	0x09							// SPI0 interrupt
#define 	IRQ_SPI1 		0x0a							// SPI1 interrupt
#define	IRQ_UART0       	0x0b							// UART0 interrupt
//							0x0c
#define	IRQ_TIMER2      	0x0d
#define	IRQ_DCP4        	0x0e							// ISP USER interrupt2
#define	IRQ_DCP5        	0x0f							// ISP USER interrupt3
#define	IRQ_EXT2        	0x10
#define	IRQ_TIMER3      	0x11
#define	IRQ_DCP6        	0x12							// ISP Motion Detection End interrupt
#define	IRQ_DCP7        	0x13							// ISP STACK interrupt
//							0x14
#define	IRQ_TIMER4      	0x15
#define	IRQ_TIMER5      	0x16
//							0x17							// SPI2 interrupt
//							0x18
#define	IRQ_TIMER6      	0x19
#define	IRQ_TWI         	0x1a
#define IRQ_ADC				0x1b							// ADC interrupt
//							0x1c
#define	IRQ_TIMER7      	0x1d
#define	IRQ_UART1       	0x1e
//							0x1f							// DMA interrupt
//-------------------------------------------------------------------------------------------------
// Priority
enum{
	PRI_EXT0 = 0,			// Highest priority
	PRI_TIMER0  ,
	PRI_ISP0	,
	PRI_ISP1    ,
	PRI_RES0    ,
	PRI_TIMER1  ,
	PRI_ISP2    ,
	PRI_ISP3    ,
	PRI_EXT1    ,
	PRI_SPI	    ,
	PRI_RES1    ,
	PRI_UART0   ,
	PRI_RES2    ,
	PRI_TIMER2  ,
	PRI_ISP4    ,
	PRI_ISP5    ,
	PRI_EXT2    ,
	PRI_TIMER3  ,
	PRI_ISP6    ,
	PRI_ISP7    ,
	PRI_RES3    ,
	PRI_TIMER4  ,
	PRI_TIMER5  ,
	PRI_RES4    ,
	PRI_RES5    ,
	PRI_TIMER6  ,
	PRI_TWI     ,
	PRI_RES6    ,
	PRI_RES7    ,
	PRI_TIMER7  ,
	PRI_UART1   ,
	PRI_RES8
};


//-------------------------------------------------------------------------------------------------
// Macro
#define SET_VECTORED()  asm("set 12")
#define EI()			asm("set 13")  // Global interrupt enable
#define DI()			asm("clr 13")  //		"		   disable
#define EI_NMI()		asm("set 14")
#define DI_NMI()		asm("clr 14")

#define VEC_BASE		0x20
#define IRQ_CLR(n)		IPCw(VEC_BASE+n)

#define	__HALT0	__asm__ __volatile__(" halt    0 ");
#define	__HALT1	__asm__ __volatile__(" halt    1 ");
#define	__HALT2	__asm__ __volatile__(" halt    2 ");
#define	__HALT3	__asm__ __volatile__(" halt    3 ");

#define	__SYNC	__asm__ __volatile__(" sync ");

//-------------------------------------------------------------------------------------------------
// Extern
#define		IrqEna(aiIn)			IENw(IENr | (1<<aiIn));			// Enable IRQ
#define		IrqFree(aiIn)			IMKSTw(IMKSTr | (1<<aiIn));		// Unmasking
#define		IrqIim(aiIn)			IIMw(IIMr | (1<<aiIn));			// Internal interrupt edge mode set
extern void IrqPri(void);


//*************************************************************************************************
// FLASH
//-------------------------------------------------------------------------------------------------
// Extern
#if (model_Flash==0)
	#define	Sf_Protect			EON_Protect();
	#define	Sf_UnProtect		EON_Unprotect();
#else
	#define	Sf_Protect			Winbond_Protect();
	#define	Sf_UnProtect		Winbond_Unprotect();
#endif

#if (model_Protect==0)
#define		SfWrEn			{SFMOD_BEEw(0); asm("nop"); asm("nop"); asm("nop"); asm("nop");}
#define		SfWrDis			{SFMOD_BEEw(1); asm("nop"); asm("nop"); asm("nop"); asm("nop");}
#else
#define		SfWrEn			{SFMOD_BEEw(0); asm("nop"); asm("nop"); asm("nop"); asm("nop"); Sf_UnProtect WaitXus(500);}
#define		SfWrDis			{SFMOD_BEEw(1); asm("nop"); asm("nop"); asm("nop"); asm("nop"); Sf_Protect 	 WaitXus(500);}
#endif

extern BYTE SfWrite(UINT anAddr, BYTE* apbData, UINT anNum);
extern BYTE SfRead(UINT anAddr, BYTE* apbData, UINT anNum);
extern BYTE SfWrite2(BYTE* apbData, UINT anNum, BYTE abMode);
extern BYTE SfRead2(BYTE* apbData, UINT anNum, BYTE abMode);
extern BYTE Isp2Sf( UINT anSfaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte);
extern BYTE Sf2Isp( UINT anSfaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte);
extern void EON_Protect(void);
extern void EON_Unprotect(void);
extern void Winbond_Protect(void);
extern void Winbond_Unprotect(void);



//-------------------------------------------------------------------------------------------------
// Misc
#define FLASH_TOTAL_SIZE		(512*1024)		// 512KB	(4Mbit quad)
#define FLASH_SECT_SIZE			(4*1024)		// 4KB
#define FLASH_SECT_TOTAL_EA		128

#define FLASH_SECT_BOOT_STT		0				// sect no. of BootLoader
#define FLASH_SECT_APP_STT		4				// sect no. of App
#define FLASH_SECT_DFT_STT		123				// sect no. of Defect table
#define FLASH_SECT_SHD_STT		124				// sect no. of Shading table
#define FLASH_SECT_USR_STT		125				// sect no. of Menu Parameter (Roll1)
#define FLASH_SECT_PAR_STT 		127 			// sect no. of User parameter

#define FLASH_SECT_USR_EA		1
#define FLASH_SECT_USR_BKUP		(FLASH_SECT_USR_STT+FLASH_SECT_USR_EA)	// sect no. of Menu Parameter (Roll2)

enum {
	FLASH_USR_MODE = 0,
	FLASH_PAR_MODE
};



//*************************************************************************************************
// WDT
//-------------------------------------------------------------------------------------------------
// Misc

#define		WDT_TIME			2000				// limit time (msec)
//-------------------------------------------------------------------------------------------------
// Extern

#define 	WdtEna				WDTCON_WDTENw(1)											// Enable watchdog
#define 	WdtDis				WDTCON_WDTENw(0)											// Disable watchdog
#define 	WdtGetSts			WDTCON_WDTSTr												// Check if watchdog reset occured
#define 	WdtCfg(anTime)		WDTCNTw( (UINT)(((u64)anTime * (u64)PCLK) / (u64)1000) );	// Configurate reset time (msec)

//*************************************************************************************************
// ISP (EN777)
//-------------------------------------------------------------------------------------------------
// Misc
#define	ISP_BASE_READ			0x300			// (fix) Read data start addr.
#define ISP_BASE_SHADING		0x400			// (fix) Shading table start addr			(0x400 ~ 4ff)
#define	ISP_BASE_DEFECT			0x500			// (fix) Defect table start addr.			(0x500 ~ 8ff)
#define	ISP_BASE_IMD			0x900			// (fix) Motion detector pos start addr.	(0x900 ~ 95f)
#define	ISP_BASE_FONT_ID		0x1000			// (fix) Font
#define	ISP_BASE_FONT_ATTR		0x1800			// (fix) "
#define	ISP_BASE_FONT_CHAR		0x2000			// (fix) "

#define ISP_SHADING_EA			256				// (fix) number of Shading table
#define ISP_DEFECT_EA			1024			// (fix) number of Defect pos
#define ISP_IMD_EA				64				// (fix) number of IMD pos

#define ISP_BOX_EA				32				// (fix) number of Box

#define ISP_FONT_ID_EA			2048			// (fix) number of Font id
#define ISP_FONT_ATTR_EA		2048			// (fix) number of Font attr
#define	ISP_FONT_CHAR_EA		341				// (fix) number of font character

#define	ISP_FONT_CHAR_INIT		94				// (fix) number of font character
#define	ISP_FONT_CHAR_CCHN		145				// Common Chinese
#define	ISP_FONT_CHAR_SCHN		87				// Simplified Chinese
#define	ISP_FONT_CHAR_TCHN		85				// Traditional character

#define	ISP_FONT_INDEX_CHN		94
#define	ISP_FONT_INDEX_CHN_SP	ISP_FONT_CHAR_CCHN + ISP_FONT_INDEX_CHN

#define ISP_FONT_EAX			46				// (var) number of Horizontal Font
#define SPACE_CHAR_ID			' '

// Power Config.
#define POWER_ON_ADC	ADC_EN_EN773Aw(1); //YMCA
//#define POWER_ON_ADC	AD_ENw(0); //YMCA
#define POWER_OFF_ADC	ADC_EN_EN773Aw(0); //YMCA
//#define POWER_OFF_ADC	AD_ENw(1); //YMCA

#define	POWER_ON_CVBS	{DAC_PD_EN773Aw(0); DS_ON_EN773Aw(1); YCOUT_POL_EN773Aw(1); /*ECK_SELw(2);*/} //YMCA
//#define	POWER_ON_CVBS	{DAC_PDw(0); DS_ONw(1); ENC_ONw(1); /*ECK_SELw(2);*/} //YMCA
#define	POWER_OFF_CVBS	{DAC_PD_EN773Aw(1); DS_ON_EN773Aw(0); YCOUT_POL_EN773Aw(0); /*ECK_SELw(3);*/} //YMCA
//#define	POWER_OFF_CVBS	{DAC_PDw(1); DS_ONw(0); ENC_ONw(0); /*ECK_SELw(3);*/} //YMCA

#define POWER_ON_LVDS	//LVDS_PDw( );	// each ch
#define POWER_OFF_LVDS	//LVDS_PDw(0);	// "

#define	POWER_ON_PARLL	//{BT_OYPDw(0); BT_OCPDw(0); /*PPCKO_SELw();	 */	} //YMCA
#define	POWER_OFF_PARLL	//{BT_OYPDw(1); BT_OCPDw(1); /*PPCKO_SELw(0x7);*/	} //YMCA

#define POWER_ON_SDI	HDSDI_PD_EN773Aw(1);
#define POWER_OFF_SDI	HDSDI_PD_EN773Aw(0);

#if 1

#define DOUT_MODE	{	\
	ITU_SCON_EN773Aw(0);		\
	ITU_ORDR_EN773Aw(0);		\
	POWER_OFF_SDI		\
	POWER_ON_PARLL		\
}

#else

// Mode Config.
#if (model_Dout==0)
#define DOUT_MODE	{	\
	ITU_SCONw(1);		\
	ITU_ORDRw(1);		\
	POWER_ON_SDI		\
	POWER_OFF_PARLL		\
}
#elif (model_Dout==1)
#define DOUT_MODE	{	\
	ITU_SCONw(0);		\
	ITU_ORDRw(1);		\
	POWER_ON_SDI		\
	POWER_ON_PARLL		\
}
#elif (model_Dout==2)
#define DOUT_MODE	{	\
	ITU_SCONw(1);		\
	ITU_ORDRw(0);		\
	POWER_OFF_SDI		\
	POWER_ON_PARLL		\
}
#elif (model_Dout==3)
#define DOUT_MODE	{	\
	ITU_SCONw(0);		\
	ITU_ORDRw(0);		\
	POWER_OFF_SDI		\
	POWER_ON_PARLL		\
}
#endif

#endif
//-------------------------------------------------------------------------------------------------
// Macro
#define SetIsp(anAddr, anData)		_wr32(ISP_BASE+((UINT)(anAddr)<<2), (UINT)(anData))
#define GetIsp(anAddr)				_rd32(ISP_BASE+((UINT)(anAddr)<<2))

extern UINT gnFontdummy;
#define SetFontChar(anAddr,anData)	{_wr32(ISP_BASE+((ISP_BASE_FONT_CHAR +(UINT)(anAddr))<<2),  (UINT)(anData));\
									gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_CHAR +(UINT)(anAddr))<<2)); }

#define SetFontAttr(anAddr,anData)  {_wr32(ISP_BASE+((ISP_BASE_FONT_ATTR +(UINT)(anAddr))<<2), ((UINT)(anData)&0x3));\
									gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_ATTR +(UINT)(anAddr))<<2)); }

#define SetFontId(anAddr,anData)	{_wr32(ISP_BASE+((ISP_BASE_FONT_ID	 +(UINT)(anAddr))<<2), ((UINT)(anData)&0x1ff));\
									gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_ID +(UINT)(anAddr))<<2)); }


#define SETFONTCHAR(Y,X,A)			{ SetFontChar((((Y)*ISP_FONT_EAX)+(X)), A); }
#define SETFONTATTR(Y,X,A)			{ SetFontAttr((((Y)*ISP_FONT_EAX)+(X)), A); }
#define SETFONTID(Y,X,A)			{ SetFontId((((Y)*ISP_FONT_EAX)+(X)), A); }

#define SetShading(anAddr,anData)	{_wr32(ISP_BASE+((ISP_BASE_SHADING +(UINT)(anAddr))<<2),  (UINT)(anData));	asm("nop"); asm("nop");}
#define GetShading(anAddr)			(_rd32(ISP_BASE+((ISP_BASE_SHADING +(UINT)(anAddr))<<2)))


//-------------------------------------------------------------------------------------------------
// Extern
extern void WaitVdi(void);
extern void WaitVdw(void);
extern void WaitVdo(void);
extern void WaitVdiCnt(uint08 cnt);

extern volatile BYTE	gbVdiIrq;
extern volatile BYTE	gbVdwIrq;
extern volatile BYTE	gbVdoIrq;

extern void SetFontAttrs(UINT anPosY, UINT anPosX, UINT anLen, UINT anAttr);
extern void DispFont(char* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispFontEx(EXCH* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClr(UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClrStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen);
#if model_CharMax == 1
extern void DispStrEx(const PEXCH* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClrStrEx(const PEXCH* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen);
#else
	#define DispStrEx		DispStr
	#define DispClrStrEx	DispClrStr
#endif

extern BYTE	gbUpsIrq;

extern volatile BYTE	gVdDlyCnt;
extern volatile BYTE	gVdwDlyCnt;




//*************************************************************************************************
// SENSOR
//-------------------------------------------------------------------------------------------------
// Misc
#define SENS_SONY_ID2		0x2
#define SENS_SONY_ID3		0x3
#define SENS_SONY_ID4		0x4

#define SENS_OV2715_DEV		0x6c
#define SENS_AR0331_DEV   	0x20

//-------------------------------------------------------------------------------------------------
// Macro
#if 1
#define SetSens(dummy, ADDR, VAL)	SetSensSpi(ADDR, VAL)
#define GetSens(ADDR)				GetSensSpi(ADDR)
#else
#define SetSens(dummy, ADDR, VAL)	SensRegWrite(ADDR, VAL)
#define GetSens(ADDR)				SensRegRead(ADDR)
#endif

#if 0
void ISPM OutMode(void);
#endif

void InitFontChar(const UINT anFont[][12]);
void InitFontAttr(void);
void InitFontID(void);





/* EOF */
