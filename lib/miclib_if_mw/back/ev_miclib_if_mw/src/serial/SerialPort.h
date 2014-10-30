
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include <windows.h>


extern int Open(int portNo, long baudRate, char dataBits, char parity, char stopBits);
extern void Close();

extern int Read(char *data, int maxDataLength);
extern int Write(const char *data, int dataLength);
extern int SetTimeout(int readTimeout, int writeTimeout, int readIntervalTimeout);
/*
void Flush();


int CountReadBuff();
*/
char * GetLastErrorString();

#endif