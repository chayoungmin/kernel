
#include <stdio.h>
#include "SerialPort.h"

#ifndef false
#define false					0
#endif

#ifndef true
#define true					1
#endif

// CSerialPort::CSerialPort()
// {
// 	_hSerial = INVALID_HANDLE_VALUE;
// }
// 
// CSerialPort::~CSerialPort()
// {
// 	Close ();
// }

HANDLE g_hSerial = INVALID_HANDLE_VALUE; 

int Open (int portNo, long baudRate, char dataBits, char parity, char stopBits)
{
	char szPort[32] = {0, };
	DCB dcb;

	sprintf(szPort, "\\\\.\\COM%d", portNo);

	if(g_hSerial != INVALID_HANDLE_VALUE)
	{
		printf("ERROR: Open(): %s, %d, Port is already opened\n", szPort, baudRate);
		return false;
	}

	g_hSerial = CreateFileA (szPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

	if(g_hSerial == INVALID_HANDLE_VALUE)
	{
		printf("ERROR: CreateFile(): %s, %d, %s", szPort, baudRate, GetLastErrorString());
		return false;
	}

//	SetCommMask(g_hSerial, EV_RXCHAR);
//	SetupComm (g_hSerial, 8192, 8192);
	PurgeComm (g_hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	if(!GetCommState(g_hSerial, &dcb))
	{
		printf("ERROR: GetCommState (): %s", GetLastErrorString());
		return false;
	}

	dcb.DCBlength = sizeof(DCB);

	dcb.BaudRate = baudRate;
	dcb.ByteSize = dataBits;
	dcb.Parity = parity;
	dcb.StopBits = stopBits;
	dcb.fBinary = true;
	dcb.fDsrSensitivity = false;
	dcb.fParity = 0;
	dcb.fOutX = false;
	dcb.fInX = false;
	dcb.fNull = false;
	dcb.fAbortOnError = false;
	dcb.fOutxCtsFlow = false;
	dcb.fOutxDsrFlow = false;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = false;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fOutxCtsFlow = false;
	dcb.fOutxCtsFlow = false;
	
	if(!SetCommState(g_hSerial, &dcb))
	{
		printf("ERROR: SetCommState(): %s", GetLastErrorString());
		return false;
	}

	printf("SUCCESS: Open(): %s, %d, open serial port\n", szPort, baudRate);

	return true;
}

void Close()
{
	if(g_hSerial != INVALID_HANDLE_VALUE)
	{
		CloseHandle (g_hSerial);

		g_hSerial = INVALID_HANDLE_VALUE;
		printf("SUCCESS: Close(): close serial port\n");
	}
}

int Read(char *data, int maxDataLength)
{
	DWORD readBytes = 0;

	if(!ReadFile(g_hSerial, data, maxDataLength, &readBytes, NULL))
	{
		printf("ERROR: ReadFile(): %s", GetLastErrorString());
		return -1;
	}

	return readBytes;
}

int Write(const char *data, int dataLength)
{
	DWORD writtenBytes = 0;

	if(!WriteFile(g_hSerial, data, dataLength, &writtenBytes, NULL))
	{
		printf("ERROR: WriteFile(): %s", GetLastErrorString());
		return -1;
	}

	return writtenBytes;
}
/*
void Flush()
{
	DWORD comError = 0;
	COMSTAT comStat;

	if (!ClearCommError (_hSerial, &comError, &comStat)) {
		printf("ERROR: ClearCommError(): %s", GetLastErrorString());
		return;
	}
	if (!PurgeComm (_hSerial, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR)) {
		printf("ERROR: PurgeComm(): %s", GetLastErrorString());
		return;
	}
}
*/
int SetTimeout(int readTimeout, int writeTimeout, int readIntervalTimeout)
{
	COMMTIMEOUTS commTimeout;

	if(!GetCommTimeouts(g_hSerial, &commTimeout))
	{
		printf("ERROR: GetCommTimeouts(): %s", GetLastErrorString());
		return -1;
	}

	commTimeout.ReadIntervalTimeout = readIntervalTimeout;
	commTimeout.ReadTotalTimeoutMultiplier = 0;
	commTimeout.ReadTotalTimeoutConstant = readTimeout;
	commTimeout.WriteTotalTimeoutMultiplier = 0;
	commTimeout.WriteTotalTimeoutConstant = writeTimeout;

	if(!SetCommTimeouts (g_hSerial, &commTimeout))
	{
		printf("ERROR: SetCommTimeouts(): %s", GetLastErrorString());
		return -1;
	}

	return 1;
}
/*
int CountReadBuff()
{
	DWORD comError = 0;
	COMSTAT comStat;

	if (!ClearCommError(_hSerial, &comError, &comStat)) {
		printf("ERROR: ClearCommError(): %s", GetLastErrorString());
		return -1;
	}
	return comStat.cbInQue;
}
*/
char* GetLastErrorString()
{
	static char lastError[1024];
	
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);

	return lastError;
}
