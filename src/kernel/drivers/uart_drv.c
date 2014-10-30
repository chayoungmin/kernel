/*********************************************************************************************************//**
* @file uart_drv.c
* @author 
*  JangHo,Yoo(YJH)
* @date 2012.10.18 
* @brief 
*  Source file of UART device driver
*************************************************************************************************************/

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "kernel.h"
#include "miclib_if_mw.h"

/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/
#define UART_BUFF_SZ                      128
#define UART_BUFF_MASK                    (UART_BUFF_SZ - 1)

/*************************************************************************************************************
* LOCAL CONSTANTS
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL DATA TYPES
*************************************************************************************************************/
typedef enum{
	DATABITS_5=5-5,
	DATABITS_6=6-5,
	DATABITS_7=7-5,
	DATABITS_8=8-5,
}UART_DATABITS;

typedef enum{
	STOPBITS_1=1-1,
	STOPBITS_2=2-1,
}UART_STOPBITS;

enum _UII_INTID {
	INTID_NONE = 0x01,
	INTID_RXLS = 0x06,
	INTID_RXDA = 0x04,
	INTID_TOUT = 0x0C,
	INTID_TXE  = 0x02
};


/*************************************************************************************************************
* LOCAL TABLES
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/
//static uint08 gRxQueue[UART_BUFF_SZ];
//static uint08 gRxHead;
//static uint08 gRxTail;
//static uint08 gTxQueue[UART_BUFF_SZ];
//static uint08 gTxHead;
//static uint08 gTxTail;


static UART_PUT_BYTE_APP_FN PutRxQByte;
static UART_GET_BYTE_APP_FN GetTxQByte;

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
* @param[in] baud : UART Baudrate (UBR_2400, UBR_4800, UBR_9600, UBR_14400, UBR_19200, UBR_38400, UBR_57600, UBR_115200)
* @param[out] none
* @retval none
* @brief 
*  UART CH0을 초기화 한다.
*  UART CH0 : USER I/F
*************************************************************************************************************/
void InitUartDriverComm(UBAUD_N baud,UART_PUT_BYTE_APP_FN PutRx,UART_GET_BYTE_APP_FN GetTx)
{
	//DebugPrintf("Comm UART Initialize...\n\r");
	
	WORD awBaud = UART_BAUD(baud);
	BYTE bDataBits = DATABITS_8;
	BYTE abStopBit = STOPBITS_1;
	UINT anParity = 0;
		
	U0LC_STBw(abStopBit);							// Stop bit
	U0LC_WLSw(bDataBits);							// Data bit

	U0LC_PENw(0);										// Parity disable
	if(anParity!=UART_PARNONE){							// Odd,Even parity ?
		U0LC_PENw(1);									// Parity enable or not
		if(anParity == UART_PARODD)	U0LC_EPSw(0);		// Odd
		else						U0LC_EPSw(1);		// Even
	}

	U0LC_DLABw(1);										// Enable access
	U0DLLw(awBaud&0x00ff)    ;							// Divisor latch registers
	U0DLMw((awBaud&0xff00)>>8);							//			"
	U0LC_DLABw(0);										// Disable access


	U0FC_RFTLw(0);
	U0FC_FIFOENw(0); // FIFO Enable X
	
	U0IE_RDAIENw(1); // Received Data AvailaReceived Interruptble bitEnable bit
	U0IE_RLSIENw(1); // InterruptReceiver Line Status Interruptble bitEnable bit
	U0IE_THEIENw(1);
	
	//Enable UART0 Interrupt 
	InitIntConfig(IRQ_UART0, ENABLE);
	PutRxQByte = PutRx;
	GetTxQByte = GetTx;

#ifdef EYENIX_COMM
	UartRstQue();
#endif
} /* InitUartDriver */

#ifdef EYENIX_COMM

TUartQue	gtUartQue;

void ISPM UartRstQue(void)
{
	UartRstRxQue();
	UartRstTxQue();
}

void ISPM UartRstRxQue(void)
{
	gtUartQue.wRxLen = 0;
	gtUartQue.pbRxHead = &gtUartQue.bRxQue[0];
	gtUartQue.pbRxTail = &gtUartQue.bRxQue[0];
}

void ISPM UartRstTxQue(void)
{
	gtUartQue.wTxLen = 0;
	gtUartQue.pbTxHead = &gtUartQue.bTxQue[0];
	gtUartQue.pbTxTail = &gtUartQue.bTxQue[0];
}

//-------------------------------------------------------------------------------------------------
// Que <-> Phy
BYTE ISPM UartPutRx(BYTE abChar)
{	// Phy -> Rx Que
    BYTE		bErr;

	if(gtUartQue.wRxLen < UART_BUF_SIZE){								// Not full ?
		 gtUartQue.wRxLen++;											// Length++
		*gtUartQue.pbRxHead++ = abChar;									// Phy -> Rx Que
		if( gtUartQue.pbRxHead == &gtUartQue.bRxQue[UART_BUF_SIZE]){	// Return to 0
			gtUartQue.pbRxHead  = &gtUartQue.bRxQue[0];					//		"
		}																//		"
		bErr = UART_NO_ERR;
	}
	else{
		bErr = UART_RX_FULL;
	}

	return (bErr);
}

BYTE ISPM UartGetTx(BYTE* apbErr)
{	// Tx Que -> Phy
	BYTE		bChar;

	if(gtUartQue.wTxLen > 0){											// Not empty ?
		gtUartQue.wTxLen--;												// Length--
		bChar = *gtUartQue.pbTxTail++;									// Tx Que -> Phy
		if(	gtUartQue.pbTxTail == &gtUartQue.bTxQue[UART_BUF_SIZE]){	// Return to 0
			gtUartQue.pbTxTail  = &gtUartQue.bTxQue[0];					//		"
		}																//		"
		*apbErr = UART_NO_ERR;
    }
	else{
		bChar = 0;
		*apbErr = UART_TX_EMPTY;
	}
    return (bChar);
}

//-------------------------------------------------------------------------------------------------
// App <-> Que
BYTE ISPM UartPutByte(BYTE abChar)
{	// App -> Tx Que 
    BYTE		bErr;

	DI();
    if(gtUartQue.wTxLen < UART_BUF_SIZE){								// Not full ?
		gtUartQue.wTxLen++;												// Length++
		*gtUartQue.pbTxHead++ = abChar;									// App -> Tx Que
		if( gtUartQue.pbTxHead == &gtUartQue.bTxQue[UART_BUF_SIZE]){	// Return to 0
			gtUartQue.pbTxHead  = &gtUartQue.bTxQue[0];					//		"
		}																//		"
		if(gtUartQue.wTxLen == 1)	{
//			GpioSetHi(GPIO_RS485_DIR);									// 485 dir	(12.9.28)
//			WaitXus(200);												// "
			
			UartEiTx;													// Kind of software irq(Invoke Tx empty irq)
		}
		bErr = UART_NO_ERR;
	}
	else{
		bErr = UART_TX_FULL;
	}
	EI();

	return (bErr);
}

BYTE ISPM UartGetByte(BYTE* apbErr)
{	// Rx Que -> App
	BYTE		bChar;

	DI();
	if(gtUartQue.wRxLen > 0){											// Not empty ?
		gtUartQue.wRxLen--;												// Length--
		bChar = *gtUartQue.pbRxTail++;									// Rx Que -> App
		if( gtUartQue.pbRxTail == &gtUartQue.bRxQue[UART_BUF_SIZE]){	// Return to 0
			gtUartQue.pbRxTail  = &gtUartQue.bRxQue[0];					//		"
		}																//		"
		*apbErr = UART_NO_ERR;
	}
	else{
		bChar = 0;
		*apbErr = UART_RX_EMPTY;
	}
	EI();

	return (bChar);
}

//-------------------------------------------------------------------------------------------------
// Check if que is empty or full
int ISPM UartIsFull(void)
{	// Check if Tx buffer is full
//	volatile int			iFull;
	int			iFull;	//!
	DI();
	if(gtUartQue.wTxLen < UART_BUF_SIZE)    iFull = 0;
	else									iFull = 1;
	EI();

    return (iFull);
}

int ISPM UartIsEmpty(void)
{	// Check if Rx buffer is empty
	int			iEmpty;

	DI();
	if(gtUartQue.wRxLen > 0)	iEmpty = 0;
	else						iEmpty = 1;
	EI();

	return (iEmpty);
}

//-------------------------------------------------------------------------------------------------
// Utility
void ISPM UartTxByte(BYTE abByte)
{	// Character out (Guarantee Tx)
	volatile UINT vUartTxByte;
	while(1){
		vUartTxByte	= UartIsFull();
		if(!vUartTxByte) break;
	}

//	while(UartIsFull());								// Wait if full
	UartPutByte(abByte);								// Put 1 byte
}

//void UartTxStr(volatile BYTE* apbStr)
void ISPM UartTxStr(BYTE* apbStr) //!
{	// String out (Guarantee Tx)
    while(*apbStr){										// Check 'NULL' character
		if(*apbStr == '\n')		UartTxByte('\r');		// Move cursor to left
		UartTxByte(*apbStr++);							// Put 1 byte
	}
}

void ISPM UartPrintf(BYTE* apbStr0, UINT anVal, BYTE* apbStr1)
{	// String + Value + String
/*	BYTE	bStr[9];

	Sprint(bStr, anVal, 8);
	if(apbStr0)		UartTxStr(apbStr0);
					UartTxStr(bStr	 );
	if(apbStr1)		UartTxStr(apbStr1);*/
}

/*
void debugprintf(const char * const fmt, ...)
{
	va_list args;
	int n;
	char buf[128];

	if(fmt)
	{
		va_start(args, fmt);
		n = vsprintf(buf, fmt, args);
		va_end(args);
		UartTxStr(buf);
	}
}
*/


//-------------------------------------------------------------------------------------------------
// Isr
#pragma interrupt
void ISPM IsrUart0(void)
{	// Uart0 interrupt service routine
	BYTE	bIrqId, bErr, bBuf;

//	DI();
	IRQ_CLR(IRQ_UART0);

	bIrqId = U0IIr & 0xf;									// ID register must be read simultaneously. CAUTION

	while(bIrqId!=1){										// Read until interrupt pending bit is cleared
		switch(bIrqId){
			case 0x2 :										// Tx irq
				bBuf = UartGetTx(&bErr);
				if(bErr==UART_TX_EMPTY) {
					UartDiTx;								// Disable Tx irq
					
//					WaitXus(200);							// 485 read dir (12. 8. 28)
//					GpioSetLo(GPIO_RS485_DIR);				// "
				}
				else	U0THw(bBuf);
				break;

			case 0x4 :										// Rx irq
				bErr = UartPutRx(U0RBr);
				break;

			case 0x6 :										// Line status irq
				bBuf = U0LSr;
				break;

			default :
				break;
		}
		bIrqId = U0IIr & 0xf;
	}

//	EI();
}

#else

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief none
*************************************************************************************************************/	
char UartPutCh(char ch)
{
	//uint08 timeout = 0;

	while(!U0LS_TEMPr);

	U0THw(ch);

	return NO_ERROR;

}
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief none
*************************************************************************************************************/	
char UartGetCh(char* ch)
{
	if(U0LS_DRDYr)
	{
		*ch = U0RBr;
		return NO_ERROR;
	}
	return ERR;
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  UART0 Interrupt service routine.
*  INTID_NONE = 0x01 : -       : None 
*  INTID_RXLS = 0x06 : Highest : Receiver Line Status : Overrun, Parity, Framing Error, Break Interrupt
*  INTID_RXDA = 0x04 : Second  : Received Data Available
*  INTID_TOUT = 0x0C : Second  : Charater Timeout Indication
*  INTID_TXE  = 0x02 : Lowest  : Transmitter Holding Registers Empty
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM UartIsrComm(void)
{
	volatile uint08 id;
	volatile uint08 abyte = 0;
	IRQ_CLR(IRQ_UART0);
	//TODO : Add your interrupt service code
	id = U0IIr & 0x0F;

	while (id != INTID_NONE)
	{
		switch (id) 
		{
			case INTID_RXLS:
				abyte = U0LSr;
				if(PutRxQByte)
					PutRxQByte(0xff);
				break;
			case INTID_RXDA:
				abyte = U0RBr;
				if(PutRxQByte)
					PutRxQByte(abyte);
				break;
			case INTID_TOUT:
				if(PutRxQByte)
					PutRxQByte(0xff);
				break;
				
			case INTID_TXE:
				if (IF_PTC_TxQueSize() == 0)
				{
					UartDiTx;
				}
				else
				{
					abyte = GetTxQByte();
					U0THw(abyte);
				}
				break;
		}
		
		id = U0IIr & 0x0F;
	}

} /* Uart0Isr */

#endif



void InitUartDriverDebug()//only 115200,8N1
{
	//DebugPrintf("Debug UART Initialize...\n\r");
	
	WORD awBaud = UB115200;
	BYTE bDataBits = DATABITS_8;
	BYTE abStopBit = STOPBITS_1;
	UINT anParity = UART_PARNONE;

	GpioFuncPin(GPIO_RXD2);
	GpioFuncPin(GPIO_TXD2);
		
	U1LC_STBw(abStopBit);							// Stop bit
	U1LC_WLSw(bDataBits);							// Data bit

	U1LC_PENw(0);										// Parity disable
	if(anParity!=UART_PARNONE){							// Odd,Even parity ?
		U1LC_PENw(1);									// Parity enable or not
		if(anParity==UART_PARODD)	U1LC_EPSw(0);		// Odd
		else						U1LC_EPSw(1);		// Even
	}

	U1LC_DLABw(1);										// Enable access
	U1DLLw(awBaud&0x00ff)    ;							// Divisor latch registers
	U1DLMw((awBaud&0xff00)>>8);							//			"
	U1LC_DLABw(0);										// Disable access
	

	

	//Enable UART1 Interrupt 
	//nitIntConfig(IRQ_UART1, ENABLE);
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief none
*************************************************************************************************************/	
char UartDebugString(const char* str)
{
	while(*str)
	{
		while(!U1LS_TEMPr);

		U1THw(*str);
		
		str++;
	}
	return NO_ERROR;
}
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief none
*************************************************************************************************************/	
char UartDebugGetCh(char* ch)
{
	if(U1LS_DRDYr)
	{
		*ch = U1RBr;
		return NO_ERROR;
	}
	return ERR;
}
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  UART0 Interrupt service routine.
*  INTID_NONE = 0x01 : -       : None 
*  INTID_RXLS = 0x06 : Highest : Receiver Line Status : Overrun, Parity, Framing Error, Break Interrupt
*  INTID_RXDA = 0x04 : Second  : Received Data Available
*  INTID_TOUT = 0x0C : Second  : Charater Timeout Indication
*  INTID_TXE  = 0x02 : Lowest  : Transmitter Holding Registers Empty
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM UartIsrDbg(void)
{
	uint08 id;
	uint08 abyte;
	
	IRQ_CLR(IRQ_UART1);

	//TODO : Add your interrupt service code
	id = U1IIr & 0x0F;
	while (id != INTID_NONE)
	{
		switch (id) 
		{
			case INTID_RXLS:
				abyte = U1LSr;
				break;
			case INTID_RXDA:
				abyte = U1RBr;
				//if (gConsolRxDone == 0)
				//{
				//	gConsolRxByte = abyte;
				//	gConsolRxDone = 1;
				//}
				break;
			case INTID_TOUT:
				break;
			case INTID_TXE:
				break;
		}
		id = U1IIr & 0x0F;
	}
} /* Uart1Isr */





















#if 0

/*********************************************************************************************************//**
* @param[in] uart_n : UART Port Number(UART_CH0, UART_CH1)
* @param[in] baud : UART Baudrate (UBR_2400, UBR_4800, UBR_9600, UBR_14400, UBR_19200, UBR_38400, UBR_57600, UBR_115200)
* @param[in] pen : Parity Enable or Disable(PEN_ENABLE, PEN_DISABLE)
* @param[in] eps : Parity type Odd or Even Parity (EPS_ODDPARITY, EPS_EVENPARITY)
* @param[in] stb : Length of stop bit(STB_1STOPBIT, STB_1STOPBIT)
* @param[in] wls : Character length (WLS_5BITS, WLS_6BITS, WLS_7BITS, WLS_8BITS)
* @param[out] none
* @retval none
* @brief 
*  UART CH0,1을 초기화 한다.
*  UART CH0 : USER I/F
*  UART CH1 : Debug Port
*************************************************************************************************************/
void InitUartDriver(UART_N uart_n, UBAUD_N baud, uint32 pen, uint32 eps, uint32 stb, uint32 wls)
{
	uint16 udl;

	switch (uart_n)
	{
		case UART_CH0:
			U0LC_STBw(stb);
			U0LC_WLSw(wls);

			U0LC_PENw(pen);
			U0LC_EPSw(eps);

			udl = UART_BAUD(baud) & 0xFFFF;
			U0LC_DLABw(DLAB_SET);
			U0DLLw(udl & 0x00FF);
			U0DLMw((udl & 0xFF00) >> 8);
			U0LC_DLABw(DLAB_CLEAR);

			Uart0RxDisable();
			Uart0TxDisable();
			Uart0RxLineStatDisable();

			// Queue Clear - Only UART0
			ResetRxQueue();
			ResetTxQueue();

			//Enable UART0 Interrupt 
			InitIntConfig(IRQ_UART0, ENABLE);
			break;
		case UART_CH1:
			U1LC_STBw(stb);
			U1LC_WLSw(wls);

			U1LC_PENw(pen);
			U1LC_EPSw(eps);

			udl = UART_BAUD(baud) & 0xFFFF;
			U1LC_DLABw(DLAB_SET);
			U1DLLw(udl & 0x00FF);
			U1DLMw((udl & 0xFF00) >> 8);
			U1LC_DLABw(DLAB_CLEAR);

			Uart1RxDisable();
			Uart1TxEnable();                		
			Uart1RxLineStatDisable();

			//Enable UART1 Interrupt 
			InitIntConfig(IRQ_UART1, DISABLE);
			break;
		default:
			break;
	}
} /* InitUartDriver */

#if 0 //121022-YJH : Further use
/*********************************************************************************************************//**
* @param[in] uart_n : channel of UART
* @param[in] en : ENABLE or DISABLE (UART interrupt enable or disable)
* @param[out] none
* @retval none
* @brief 
*  Configuration of uart interrupt
*************************************************************************************************************/
void InitUartIntConfig(UART_N uart_n, var_stat en)
{
	return;
} /* InitUartIntConfig */
#endif

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Received Data Available Interrupt Enable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0RxEnable(void)
{
	U0IE_RDAIENw(UIE_ENABLE);
} /* UartRxEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Received Data Available Interrupt Disable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0RxDisable(void)
{
	U0IE_RDAIENw(UIE_DISABLE);
} /* Uart0RxDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Transmitter Holding Empty Interrupt Enable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0TxEnable(void)
{
	U0IE_THEIENw(UIE_ENABLE);
} /* Uart0TxEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Transmitter Holding Empty Interrupt Disable  
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0TxDisable(void)
{
	U0IE_THEIENw(UIE_DISABLE);
} /* Uart0TxDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Receiver Line Status Interrupt Enable  
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0RxLineStatEnable(void)
{
	U0IE_RLSIENw(UIE_ENABLE);
} /* Uart0RxLineStatEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART0 Receiver Line Status Interrupt Disable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart0RxLineStatDisable(void)
{
	U0IE_RLSIENw(UIE_DISABLE);
} /* Uart0RxLineStatDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Received Data Available Interrupt Enable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1RxEnable(void)
{
	U1IE_RDAIENw(UIE_ENABLE);
} /* Uart1RxEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Received Data Available Interrupt Disable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1RxDisable(void)
{
	U1IE_RDAIENw(UIE_DISABLE);
} /* Uart1RxDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Transmitter Holding Empty Interrupt Enable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1TxEnable(void)
{
	U1IE_THEIENw(UIE_ENABLE);
} /* Uart1TxEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Transmitter Holding Empty Interrupt Disable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1TxDisable(void)
{
	U1IE_THEIENw(UIE_DISABLE);
} /* Uart1TxDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Receiver Line Status Interrupt Enable  
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1RxLineStatEnable(void)
{
	U1IE_RLSIENw(UIE_ENABLE);
} /* Uart1RxLineStatEnable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none 
* @brief 
*  UART1 Receiver Line Status Interrupt Disable
*************************************************************************************************************/
void CPU_MEM_ISPM Uart1RxLineStatDisable(void)
{
	U1IE_RLSIENw(UIE_DISABLE);
} /* Uart1RxLineStatDisable */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  송신큐를 초기화한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
void CPU_MEM_ISPM ResetTxQueue(void)
{
	uint32 i;

	gTxHead = 0;
	gTxTail = 0;

	for (i =0; i < UART_BUFF_SZ; i++) 
	{
		gTxQueue[i] = 0xFF;
	}
} /* ResetTxQueue */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval 
*  송신큐의 남은 바이트수.
* @brief 
*  송신큐의 전송되지 않은 바이트수를 연산한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
uint08 CPU_MEM_ISPM GetTxQSize(void)
{
	return ((gTxHead - gTxTail + UART_BUFF_SZ) % UART_BUFF_SZ);
} /* GetTxQSize */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval 
*  송신데이터
* @brief 
*  송신큐로부터 한바이트의 데이터를 읽어온다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
uint08 CPU_MEM_ISPM GetTxQByte(void)
{
	uint08 abyte;

	abyte = gTxQueue[gTxTail++];
	gTxTail &= UART_BUFF_MASK;

	return abyte;
} /* GetTxQByte */

/*********************************************************************************************************//**
* @param[in] abyte : transmit data
* @param[out] none
* @retval none
* @brief 
*  송신큐에 전송할 한바이트의 데이터를 저장한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
void CPU_MEM_ISPM PutTxQByte(uint08 abyte)
{
	gTxQueue[gTxHead++] = abyte;
	gTxHead &= UART_BUFF_MASK;
} /* PutTxQByte */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  수신큐를 초기화 한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
void CPU_MEM_ISPM ResetRxQueue(void)
{
	uint32 i;

	gRxHead = 0;
	gRxTail = 0;

	for (i =0; i < UART_BUFF_SZ; i++) 
	{
		gRxQueue[i] = 0xFF;
	}
} /* ResetRxQueue */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval 
*  수신된 바이트 수
* @brief 
*  수신큐에 저장된 바이트수를 연산한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
uint08 CPU_MEM_ISPM GetRxQSize(void)
{
	return ((gRxHead - gRxTail + UART_BUFF_SZ) % UART_BUFF_SZ);
} /* GetRxQSize */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval 
*  수신 데이터
* @brief 
*  수신큐로부터 한바이트의 데이터를 읽는다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
uint08 CPU_MEM_ISPM GetRxQByte(void)
{
	uint08 abyte;

	abyte = gRxQueue[gRxTail++];
	gRxTail &= UART_BUFF_MASK;

	return abyte;
} /* GetRxQByte */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  수신큐에 한바이트의 데이터를 저장한다.
* @attention
*  UART0에 한하여 구현됨.
*************************************************************************************************************/
void CPU_MEM_ISPM PutRxQByte(uint08 abyte)
{
	gRxQueue[gRxHead++] = abyte;
	gRxHead &= UART_BUFF_MASK;
} /* PutTxQByte */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  UART0 Interrupt service routine.
*  INTID_NONE = 0x01 : -       : None 
*  INTID_RXLS = 0x06 : Highest : Receiver Line Status : Overrun, Parity, Framing Error, Break Interrupt
*  INTID_RXDA = 0x04 : Second  : Received Data Available
*  INTID_TOUT = 0x0C : Second  : Charater Timeout Indication
*  INTID_TXE  = 0x02 : Lowest  : Transmitter Holding Registers Empty
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Uart0Isr(void)
{	
	uint08 id;
	uint08 abyte;

	IRQ_CLR(IRQ_UART0);

	//TODO : Add your interrupt service code
	id = U0IIr & 0x0F;
	while (id != INTID_NONE)
	{
		switch (id) 
		{
			case INTID_RXLS:
				abyte = U0LSr;
				break;
			case INTID_RXDA:
				abyte = U0RBr;
				PutRxQByte(abyte);
				break;
			case INTID_TOUT:
				break;
			case INTID_TXE:
				if (GetTxQSize() == 0)
				{
					Uart0TxDisable();
					break;						
				}

				abyte = GetTxQByte();
				U0THw(abyte);
				break;
		}
		id = U0IIr & 0x0F;
	}			
} /* Uart0Isr */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief 
*  UART0 Interrupt service routine.
*  INTID_NONE = 0x01 : -       : None 
*  INTID_RXLS = 0x06 : Highest : Receiver Line Status : Overrun, Parity, Framing Error, Break Interrupt
*  INTID_RXDA = 0x04 : Second  : Received Data Available
*  INTID_TOUT = 0x0C : Second  : Charater Timeout Indication
*  INTID_TXE  = 0x02 : Lowest  : Transmitter Holding Registers Empty
* @attention
*  Call by exception handler. check your vector table.
*************************************************************************************************************/
#pragma interrupt
void CPU_MEM_ISPM Uart1Isr(void)
{
	IRQ_CLR(IRQ_UART1);

	//TODO : Add your interrupt service code
#if 0
	id = U1IIr & 0x0F;
	while (id != INTID_NONE)
	{
		switch (id) 
		{
			case INTID_RXLS:
				break;
			case INTID_RXDA:
				break;
			case INTID_TOUT:
				break;
			case INTID_TXE:
				break;
		}
		id = U1IIr & 0x0F;
	}
#endif
} /* Uart1Isr */
#endif //1
/********************************************** END OF FILE *************************************************/

