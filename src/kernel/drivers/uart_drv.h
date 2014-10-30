/*********************************************************************************************************//**
* @file uart_drv.h
* @author 
*  JangHo,Yoo(YJH) 
* @date 2012.10.18 
* @brief 
*  Header file of UART device driver.
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _UART_DRV_H_
#define _UART_DRV_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef MODULE_NAME_EXTERN 
#define UART_DRV_EXT 
#else 
#define UART_DRV_EXT                      extern
#endif

/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/

/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
/*enum _UIE {
	UIE_DISABLE,
	UIE_ENABLE
};

enum _UII_FIFOST {
	FIFOST_ENABLE,
	FIFOST_DISABLE
};	

enum _UII_INTID {
	INTID_NONE = 0x01,
	INTID_RXLS = 0x06,
	INTID_RXDA = 0x04,
	INTID_TOUT = 0x0C,
	INTID_TXE  = 0x02
};

enum _UFC_RFTL {
	RFTL_1BYTE,
	RFTL_4BYTE,
	RFTL_8BYTE,
	RFTL_14BYTE
};

enum _UFC_XFR {
	XFR_CLEAR,
	XFR_SET
};

enum _UFC_RFR {
	RFR_CLEAR,
	RFR_SET
};

enum _UFC_FIFOEN {
	FIFOEN_16450UART,
	FIFOEN_ENABLE
};

enum _ULC_DLAB {
	DLAB_CLEAR,
	DLAB_SET
};

enum _ULC_SB {
	SB_CLEAR,
	SB_SET
};

enum _ULC_SP {
	SP_DISABLE,
	SP_ENABLE
};

enum _ULC_EPS {
	EPS_ODDPARITY,
	EPS_EVENPARITY
};

enum _ULC_PEN {
	PEN_DISABLE,
	PEN_ENABLE
};

enum _ULC_STB {
	STB_1STOPBIT,
	STB_2STOPBIT
};

enum _ULC_WLS {
	WLS_5BITS,
	WLS_6BITS,
	WLS_7BITS,
	WLS_8BITS
};	*/

/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/
/*typedef enum _UART_N {
	UART_CH0,
	UART_CH1
} UART_N;
*/

typedef enum _UBAUD_N {
	UBR_2400   = 2400,
	UBR_4800   = 4800,
	UBR_9600   = 9600,
	UBR_14400  = 14400,
	UBR_19200  = 19200,
	UBR_38400  = 38400,
	UBR_57600  = 57600,
	UBR_115200 = 115200
} UBAUD_N;

typedef void (*UART_PUT_BYTE_APP_FN)(uint08);
typedef uint08 (*UART_GET_BYTE_APP_FN)(void);

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
// Service functions
/*void InitUartDriver(UART_N uart_n, UBAUD_N baud, uint32 pen, uint32 eps, uint32 stb, uint32 wls);
void Uart0RxEnable(void);
void Uart0RxDisable(void);
void Uart0TxEnable(void);
void Uart0TxDisable(void);
void Uart0RxLineStatEnable(void);
void Uart0RxLineStatDisable(void);
void Uart1RxEnable(void);
void Uart1RxDisable(void);
void Uart1TxEnable(void);
void Uart1TxDisable(void);
void Uart1RxLineStatEnable(void);
void Uart1RxLineStatDisable(void);
void ResetTxQueue(void);
uint08 GetTxQSize(void);
uint08 GetTxQByte(void);
void PutTxQByte(uint08 abyte);
void ResetRxQueue(void);
uint08 GetRxQSize(void);
uint08 GetRxQByte(void);
void PutRxQByte(uint08 abyte);


// Uart Interrupt service functions
void Uart0Isr(void);
void Uart1Isr(void);
*/

extern void InitUartDriverComm(UBAUD_N baud,UART_PUT_BYTE_APP_FN PutRx,UART_GET_BYTE_APP_FN GetRx);

#ifdef EYENIX_COMM

extern void UartRstQue(void);
extern void UartRstRxQue(void);
extern void UartRstTxQue(void);
extern BYTE UartPutRx(BYTE abChar);
extern BYTE UartGetTx(BYTE* apbErr);
extern BYTE UartPutByte(BYTE abChar);
extern BYTE UartGetByte(BYTE* apbErr);
extern int UartIsFull(void);
extern int UartIsEmpty(void);
extern void UartTxByte(BYTE abByte);
extern void UartTxStr(BYTE* apbStr);
extern void UartPrintf(BYTE* apbStr0, UINT anVal, BYTE* apbStr1);
extern void IsrUart0(void);

#else

extern char UartPutCh(char ch);
extern char UartGetCh(char* ch);
extern void UartIsrComm(void);

#endif

extern void InitUartDriverDebug();//only 115200,8N1
extern char UartDebugString(const char* str);
extern char UartDebugGetCh(char* ch);
extern void UartIsrDbg(void);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _UART_DRV_H_ */
/********************************************** END OF FILE *************************************************/

