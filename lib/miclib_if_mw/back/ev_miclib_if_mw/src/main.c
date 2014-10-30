#include <conio.h>
#include <stdio.h>
//#include <windows.h>	//$$$$ KSH 140408 : "miclib_type.h"¿Í Ãæµ¹...
#include "main.h"

#include "SerialPort.h"

#include "miclib_type.h"
#include "miclib_if_mw.h"
#include "if_user_mw.h"

#define SCRINIT	0x20
#define SCRH	20
#define SCRW	45

char scr[SCRH][SCRW];
char gOsd_Update_Flg;
uint08 sendbuf[128];
uint16 sendbuf_size = 0;

uint08 eep[128]		={0x10,0x11,0x12,0x13,0x14,};
uint32 isp[128]		={0x7020,0x7021,0x7022,0x7023,0x7024,};
uint32 motor[128]	={0x0003,0x0004,0x0005,0x0006,};
uint32 sensor[128]	={0x0400,0x0401,0x0402,0x0403,};
uint32 video1[128]	={0x2005,0x2006,0x2007,0x2008,0x2009,};
uint32 video2[128]	={0x1006,0x1007,0x1009,0x1108,};
uint32 video3[128]	={0x0117,0x0117,0x0117,0x0117,0x0117,0x0117,0x0117};
uint08 ViscaStt[VISCA_STT_MAX] = {0,0,0,0,0,0};

uint08 GetFcsDrt();
uint08 GetZmDrt();
uint08 GetZmFcsDrt();
uint08 GetReset();
uint08 Getset();
uint08 GetRecall();

//CNB TECH TEST FUCNTIONS
uint32 Read_Eep(uint32 Addr);
void Write_Eep(uint32 Addr,uint32 Dat);
uint32 Read_Isp(uint32 Addr);
void Write_Isp(uint32 Addr,uint32 Dat);
uint32 Read_motor(uint32 Addr);
void Write_motor(uint32 Addr,uint32 Dat);
uint32 Read_sensor(uint32 Addr);
void Write_sensor(uint32 Addr,uint32 Dat);
uint32 Read_video1(uint32 Addr);
void Write_video1(uint32 Addr,uint32 Dat);
uint32 Read_video2(uint32 Addr);
void Write_video2(uint32 Addr,uint32 Dat);
uint32 Read_video3(uint32 Addr);
void Write_video3(uint32 Addr,uint32 Dat);
void Write_Eep_Protect(uint32 Addr,uint32 Dat);
void Read_Eep_Protect(uint32 Addr,uint32 Dat);

void Win32PrintCall(uint08 x, uint08 y, uint32 ch)
{
	scr[y][x] = (char)ch;

//	Osd_Update();
}

void Osd_Update_Flg(uint08 flg)
{
	gOsd_Update_Flg = flg;
}
void Osd_Update()
{
	int i = 0, j = 0;

	printf("-----------------------------------------------\n");
	for(i = 0; i < SCRH; i++)
	{
		printf("|");
		for(j = 0; j < SCRW; j++)
		{
			putchar(scr[i][j]);
		}
		printf("|\n");
	}
	printf("-----------------------------------------------\n");
}

int32 SerialRead(uint08 *pBuf, uint32 nMaxBuf)
{
	return Read(pBuf, nMaxBuf);
}

void SerialSend(uint08 txdat)
{
	sendbuf[sendbuf_size] = txdat;
	sendbuf_size++;
}
/*
void _Write(int08 *pBuf, int32 nSize)
{
	int i = 0;

	for(i = 0; i < nSize; i++)
	{
		putchar(pBuf[i]);

		Write(&pBuf[i], 1);
	}
}*/

int main( void )
{
	int i = 0, j = 0;
	int run = 1;
	int cmd;
	int temp = 400;

	uint08 serialbuf[128];
	uint32 recvsize = 0;
	IF_Initial();
	IF_EventCallbackRegister(IFU_Event_Callback);
	IF_OsdPrintCallbackRegister(Win32PrintCall);
	IF_OsdMapRegister(OSD_gMap, OSD_gHiddenMap);
	IF_UEepUpdateCallbackRegister(User_Update);
	//CNB TECHNICAL
	IF_CNBT_Regist_Callbeck(CNBT_ISP		,Read_Isp	,Write_Isp		);
	IF_CNBT_Regist_Callbeck(CNBT_EEP		,Read_Eep	,Write_Eep		);
	IF_CNBT_Regist_Callbeck(CNBT_MOTOR_IC	,Read_motor	,Write_motor	);
	IF_CNBT_Regist_Callbeck(CNBT_SENSOR_IC	,Read_sensor,Write_sensor	);
	IF_CNBT_Regist_Callbeck(CNBT_VIDEO_IC	,Read_video1,Write_video1	);
	IF_CNBT_Regist_Callbeck(CNBT_VIDEO_IC2	,Read_video2,Write_video2	);
	IF_CNBT_Regist_Callbeck(CNBT_VIDEO_IC3	,Read_video3,Write_video3	);
	IF_CNBT_Regist_Callbeck(CNBT_EEP_SKIP	,Read_Eep_Protect,Write_Eep_Protect );

	//VISCA CMD STATE
	IF_VISCA_Regist_CamState(VISCA_STT_ZOOM_DIRCT	,GetZmDrt	);
	IF_VISCA_Regist_CamState(VISCA_STT_FOCUS_DIRCT	,GetFcsDrt	);
	IF_VISCA_Regist_CamState(VISCA_STT_ZMFCS_DIRCT	,GetZmFcsDrt);
	IF_VISCA_Regist_CamState(VISCA_STT_RESET		,GetReset	);
	IF_VISCA_Regist_CamState(VISCA_STT_SET			,Getset		);
	IF_VISCA_Regist_CamState(VISCA_STT_RECALL		,GetRecall	);

	IFU_OSD_User_Init();
	
	IF_OsdWindowSize(SCRW, SCRH);
//	IF_PtcSendBufCallbackRegister(SerialSend);
//	Prtc_Init(_Read, _Write);
#ifdef WIN32
	g_OsdData.FLD.VOUT_FORMAT = 4;
	printf("%02X %02X %02X %02X\n", g_OsdData.Data[EEP_OSD_MAX-4], g_OsdData.Data[EEP_OSD_MAX-3], g_OsdData.Data[EEP_OSD_MAX-2], g_OsdData.Data[EEP_OSD_MAX-1]);
	g_CamData.FLD.ADKEY17 = 1;
	printf("%02X %02X %02X %02X\n", g_CamData.Data[EEP_CAM_OP_MAX-4], g_CamData.Data[EEP_CAM_OP_MAX-3], g_CamData.Data[EEP_CAM_OP_MAX-2], g_CamData.Data[EEP_CAM_OP_MAX-1]);
	g_ViscaData.FLD.EX_EXPC_ON = 0;
	printf("%02X %02X %02X %02X\n", g_ViscaData.Data[EEP_VISCA_MAX-4], g_ViscaData.Data[EEP_VISCA_MAX-3], g_ViscaData.Data[EEP_VISCA_MAX-2], g_ViscaData.Data[EEP_VISCA_MAX-1]);

	g_ViscaData.FLD.MONITORING_MODE = 1;
	g_ViscaData.FLD.FOCUS_POS = 0x1000;
	g_ViscaData.FLD.NEAR_LIMIT = 0xF000;
	g_ViscaData.FLD.WD_MODE = 3;//off
	g_ViscaData.FLD.PWR_ON = 0;//on
	g_ViscaData.FLD.AF_INTERVAL_TIME = 5;
	g_ViscaData.FLD.AF_MOVE_TIME = 5;
	g_ViscaData.FLD.GAIN_LIMIT = 0x0F;
	g_ViscaData.FLD.CE_THRS_VAL = 0x01;
	g_OsdData.FLD.PROTOCOL = 3;

	g_ViscaData.FLD.BRIGHT_STEP = 1;
	g_ViscaData.FLD.GAIN_STEP = 1;
#endif

	while(1)
	{
		printf("MENU\n");
		printf("1. OSD TEST\n");
		printf("2. PROTOCOL TEST\n");
		printf("3. EEPROM PRINT\n");
		printf("INPUT : ");

		cmd = _getch();

		putchar(cmd);
		printf("\n");

		run = 1;

		if(cmd == '1')	// OSD
		{
			for(i = 0; i < SCRH; i++)
			{
				for(j = 0; j < SCRW; j++)
				{
					scr[i][j] = 0x20;
				}
			}

			while(run)
			{
				temp = 400;

				if(_kbhit())
				{
					switch(_getch())
					{
						case 'q':	run = 0;	break;
						case 13:	IFU_Osd_KeyInput(OSD_CKEYDOWN); break;
						case 't':
							{
								IF_Trace(0, 0, "%%c use = %c", 'a');
								IF_Trace(0, 1, "%%s use = %s", "IF_Trace TEST");
								IF_Trace(0, 2, "%%d use = %d", 400);
								IF_Trace(0, 3, "%%x & %%X use = %x %X", 255, 255);
							}break;
						case 'r':	IF_OsdRefresh();		break;
						case 'h':	IF_OsdHiddenMenuOn();	break;
						case 's':	IF_OsdShow();			break;
						case 'd':	IF_OsdHide();			break;
						case 'x':	IF_OsdOff();			break;
						case 'p':
							{
								//printf("Privacy ON:%d CR:%d TRANS:%d MOSAIC:%d XYWH:%d %d %d %d data:%x\n", g_PriData.FLD.PRI1_ON, g_PriData.FLD.PRI1_CR, g_PriData.FLD.PRI1_TRANS, g_PriData.FLD.PRI1_MOSAIC, g_PriData.FLD.PRI1_X, g_PriData.FLD.PRI1_Y, g_PriData.FLD.PRI1_W, g_PriData.FLD.PRI1_H, g_PriData.Data[1]);
							}break;
						case 224:
							{
								switch(_getch())
								{
									case 75:	IFU_Osd_KeyInput(OSD_LKEYDOWN);	break;//IF_Task(OSD_LKEYDOWN); break;
									case 77:	IFU_Osd_KeyInput(OSD_RKEYDOWN);	break;//IF_Task(OSD_RKEYDOWN); break;
									case 72:	IFU_Osd_KeyInput(OSD_UKEYDOWN); break;//IF_Task(OSD_UKEYDOWN); break;
									case 80:	IFU_Osd_KeyInput(OSD_DKEYDOWN); break;//IF_Task(OSD_DKEYDOWN); break;
								}
							}
							break;
					}

//					OSD_KeyProc(_getch());
//					printf( "\nKey struck was '%d'\n", _getch() );
				}
				IFU_Osd_TASK();

				if(gOsd_Update_Flg)
				{
					Osd_Update();
					gOsd_Update_Flg = 0;
				}
				Sleep(50);

			}
		}
		else if(cmd == '2')
		{
			Open(3, 9600, 8, 0, 0);
			SetTimeout(10, 10, 1);

			memset(serialbuf, 0x00, 128);

			while(run)
			{
				if(_kbhit())
				{
					switch(_getch())
					{
						case 'q':	run = 0;				break;
						case '1':	IF_Send_Reply_Packet(VSC_REPLY_ICR,0);	break;
						case '2':	IF_Send_Reply_Packet(VSC_REPLY_ICR,1);	break;
						case '3':	IF_Send_Reply_Packet(VSC_REPLY_MD,0);	break;
						case '4':	IF_Send_Reply_Packet(VSC_REPLY_MD,1);	break;
						case '5':	IF_Send_Reply_Packet(VSC_REPLY_MD,2);	break;
						case '6':	IF_Send_Reply_Packet(VSC_REPLY_MD,4);	break;
						case '7':	IF_Send_Reply_Packet(VSC_REPLY_FOCUS,0x1321);	break;
						case '8':	IF_Send_Reply_Packet(VSC_REPLY_ZOOM,0x6120);	break;
						case '9':	IF_Send_Reply_Packet(VSC_REPLY_WD,0);	break;
						case '0':	IF_Send_Reply_Packet(VSC_REPLY_WD,1);	break;
						case 'a':	ViscaStt[0] = (ViscaStt[0] ? 0:1);		break;
						case 's':	ViscaStt[1] = (ViscaStt[1] ? 0:1);		break;
						case 'd':	ViscaStt[2] = (ViscaStt[2] ? 0:1);		break;
						case 'z':	ViscaStt[3] = (ViscaStt[3] ? 0:1);		break;
						case 'x':	ViscaStt[4] = (ViscaStt[4] ? 0:1);		break;
						case 'c':	ViscaStt[5] = (ViscaStt[5] ? 0:1);		break;
						case 'v':	Visca_Socket_Clear(0);
									Visca_Socket_Clear(1);
							break;
					}
					printf("(Z F ZF RS S RC)\n");
					printf("(%d %d %d  %d  %d %d )\n",ViscaStt[0],ViscaStt[1],ViscaStt[2],ViscaStt[3],ViscaStt[4],ViscaStt[5]);
				}
				i=0;
				recvsize = SerialRead(serialbuf, 128);

				while(recvsize != i)
				{
					IF_PTC_SetRxQue(serialbuf[i++]);
				}

				IF_PtcRecvBuf(recvsize);
				recvsize = 0;
				IF_Task_Ptc();

				sendbuf_size = IF_PTC_TxQueSize();
				for(i=0;i < sendbuf_size;i++)
				{
					sendbuf[i] = IF_PTC_GetTxQue();
				}

				Write(sendbuf,sendbuf_size);
				sendbuf_size = 0;
			}
		}
	}
}



uint32 Read_Eep(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return eep[Addr];
}

void Write_Eep(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	eep[Addr] = Dat;
}

uint32 Read_Isp(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return isp[Addr];
}

void Write_Isp(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	isp[Addr] = Dat;
}
uint32 Read_motor(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return motor[Addr];
}

void Write_motor(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	motor[Addr] = Dat;
}
uint32 Read_sensor(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return sensor[Addr];
}

void Write_sensor(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	sensor[Addr] = Dat;
}
uint32 Read_video1(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return video1[Addr];
}

void Write_video1(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	video1[Addr] = Dat;
}
uint32 Read_video2(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return video2[Addr];
}

void Write_video2(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	video2[Addr] = Dat;
}
uint32 Read_video3(uint32 Addr)
{
	if(Addr > 127)	return -1;
	return video3[Addr];
}

void Write_video3(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return;
	video3[Addr] = Dat;
}

void Write_Eep_Protect(uint32 Addr,uint32 Dat)
{
	if(Addr > 10 && Addr < 20)	return;
	else if(Addr > 127)	return;

	eep[Addr] = Dat;
}

void Read_Eep_Protect(uint32 Addr,uint32 Dat)
{
	if(Addr > 127)	return -1;
	return eep[Addr];
}

uint08 GetFcsDrt()
{
	return ViscaStt[VISCA_STT_FOCUS_DIRCT];
}

uint08 GetZmDrt()
{
	return ViscaStt[VISCA_STT_ZOOM_DIRCT];
}

uint08 GetZmFcsDrt()
{
	return ViscaStt[VISCA_STT_ZMFCS_DIRCT];
}
uint08 GetReset()
{
	return ViscaStt[VISCA_STT_RESET];
}

uint08 Getset()
{
	return ViscaStt[VISCA_STT_SET];
}

uint08 GetRecall()
{
	return ViscaStt[VISCA_STT_RECALL];
}
void id_Print(uint16 id)
{
	switch(id)
	{
		case IDX_MEM_STATUS :				printf("IDX_MEM_STATUS");				break; 
		case IDX_CAM_TYPE :                 printf("IDX_CAM_TYPE");                 break; 
		case IDX_CAM_CLASS :                printf("IDX_CAM_CLASS");                break; 
		case IDX_MEM_VER :                  printf("IDX_MEM_VER");                  break; 
		case IDX_CCD_TYPE :                 printf("IDX_CCD_TYPE");                 break; 
		case IDX_CLIENT_OPT :               printf("IDX_CLIENT_OPT");               break; 
		case IDX_HALL_ADJ :                 printf("IDX_HALL_ADJ");                 break; 
		case IDX_LENS_ADJ :                 printf("IDX_LENS_ADJ");                 break; 
		case IDX_MASK_ADJ :                 printf("IDX_MASK_ADJ");                 break; 
		case IDX_DEFECT_ADJ :               printf("IDX_DEFECT_ADJ");               break; 
		case IDX_SHADE_ADJ :                printf("IDX_SHADE_ADJ");                break; 
		case IDX_COLOR_ADJ :                printf("IDX_COLOR_ADJ");                break; 
		case IDX_COMM_SET :                 printf("IDX_COMM_SET");                 break; 
		case IDX_MENU_USE :                 printf("IDX_MENU_USE");                 break; 
		case IDX_LENS_INIT_TYPE :           printf("IDX_LENS_INIT_TYPE");           break; 
		case IDX_HOME_USE :                 printf("IDX_HOME_USE");                 break; 
		case IDX_FOCUS_MODE :               printf("IDX_FOCUS_MODE");               break; 
		case IDX_AF_MODE :                  printf("IDX_AF_MODE");                  break; 
		case IDX_AF_MOVE_TIME :             printf("IDX_AF_MOVE_TIME");             break; 
		case IDX_AF_INTERVAL_TIME :         printf("IDX_AF_INTERVAL_TIME");         break; 
		case IDX_FOCUS_DIST :               printf("IDX_FOCUS_DIST");               break; 
		case IDX_ZOOM_MODE :                printf("IDX_ZOOM_MODE");                break; 
		case IDX_DZOOM_MODE :               printf("IDX_DZOOM_MODE");               break; 
		case IDX_ZTRK_MODE :                printf("IDX_ZTRK_MODE");                break; 
		case IDX_ZOOM_SPEED :               printf("IDX_ZOOM_SPEED");               break; 
		case IDX_LENS_REFRESH_MODE :        printf("IDX_LENS_REFRESH_MODE");        break; 
		case IDX_LENS_REFRESH_DAYS :        printf("IDX_LENS_REFRESH_DAYS");        break; 
		case IDX_ZSRT_MAG :                 printf("IDX_ZSRT_MAG");                 break; 
		case IDX_ZEND_MAG :                 printf("IDX_ZEND_MAG");                 break; 
		case IDX_Z_HOME_POS :               printf("IDX_Z_HOME_POS");               break; 
		case IDX_F_HOME_POS :               printf("IDX_F_HOME_POS");               break; 
		case IDX_DZ_HOME_POS :              printf("IDX_DZ_HOME_POS");              break; 
		case IDX_DZOOM_MAG :                printf("IDX_DZOOM_MAG");                break; 
		case IDX_HOME_MODE :                printf("IDX_HOME_MODE");                break; 
		case IDX_HOME_TIME :                printf("IDX_HOME_TIME");                break; 
		case IDX_AE_TGT_BRIGHT :            printf("IDX_AE_TGT_BRIGHT");            break; 
		case IDX_AE_MODE :                  printf("IDX_AE_MODE");                  break; 
		case IDX_AE_AGC_LIMIT :             printf("IDX_AE_AGC_LIMIT");             break; 
		case IDX_AEM_IRIS_STEP :            printf("IDX_AEM_IRIS_STEP");            break; 
		case IDX_AEM_SHUT_STEP :            printf("IDX_AEM_SHUT_STEP");            break; 
		case IDX_AEM_BRIGHT_STEP :          printf("IDX_AEM_BRIGHT_STEP");          break; 
		case IDX_AE_DSS_STEP :              printf("IDX_AE_DSS_STEP");              break; 
		case IDX_AEM_GAIN_STEP :            printf("IDX_AEM_GAIN_STEP");            break; 
		case IDX_AE_FLK_MODE :              printf("IDX_AE_FLK_MODE");              break; 
		case IDX_WB_MODE :                  printf("IDX_WB_MODE");                  break; 
		case IDX_WB_ENV :                   printf("IDX_WB_ENV");                   break; 
		case IDX_WB_RED_GAIN :              printf("IDX_WB_RED_GAIN");              break; 
		case IDX_WB_BLUE_GAIN :             printf("IDX_WB_BLUE_GAIN");             break; 
		case IDX_WB_COLOR_TEMP :            printf("IDX_WB_COLOR_TEMP");            break; 
		case IDX_ATW_SPEED :                printf("IDX_ATW_SPEED");                break; 
		case IDX_ATW_FRAME :                printf("IDX_ATW_FRAME");                break; 
		case IDX_ATW_DELAY :                printf("IDX_ATW_DELAY");                break; 
		case IDX_USER1_RGAIN :              printf("IDX_USER1_RGAIN");              break; 
		case IDX_USER1_BGAIN :              printf("IDX_USER1_BGAIN");              break; 
		case IDX_USER2_RGAIN :              printf("IDX_USER2_RGAIN");              break; 
		case IDX_USER2_BGAIN :              printf("IDX_USER2_BGAIN");              break; 
		case IDX_DN_MODE :                  printf("IDX_DN_MODE");                  break; 
		case IDX_DN_ALARM_ON :              printf("IDX_DN_ALARM_ON");              break; 
		case IDX_DN_CHG_STEP :              printf("IDX_DN_CHG_STEP");              break; 
		case IDX_DN_CDS_STEP :              printf("IDX_DN_CDS_STEP");              break; 
		case IDX_DN_CHG_TIME :              printf("IDX_DN_CHG_TIME");              break; 
		case IDX_DN_MIN :                   printf("IDX_DN_MIN");                   break; 
		case IDX_DN_CDS_CHG_TIME :          printf("IDX_DN_CDS_CHG_TIME");          break; 
		case IDX_DN_CDS_MIN :               printf("IDX_DN_CDS_MIN");               break; 
		case IDX_IMG_BRIGHT :               printf("IDX_IMG_BRIGHT");               break; 
		case IDX_IMG_CONTRAST :             printf("IDX_IMG_CONTRAST");             break; 
		case IDX_IMG_SHARPNESS :            printf("IDX_IMG_SHARPNESS");            break; 
		case IDX_IMG_CHROMA :               printf("IDX_IMG_CHROMA");               break; 
		case IDX_IMG_HUE :                  printf("IDX_IMG_HUE");                  break; 
		case IDX_IMG_FLIP :                 printf("IDX_IMG_FLIP");                 break; 
		case IDX_IMG_FREEZE :               printf("IDX_IMG_FREEZE");               break; 
		case IDX_IMG_EFFECT :               printf("IDX_IMG_EFFECT");               break; 
		case IDX_IMG_COLOR :                printf("IDX_IMG_COLOR");                break; 
		case IDX_IMG_SHADING :              printf("IDX_IMG_SHADING");              break; 
		case IDX_IMG_DEFECT :               printf("IDX_IMG_DEFECT");               break; 
		case IDX_IMG_GAMMA_STEP :           printf("IDX_IMG_GAMMA_STEP");           break; 
		case IDX_IMG_GAM_MODE :             printf("IDX_IMG_GAM_MODE");             break; 
		case IDX_IMG_RGAIN :                printf("IDX_IMG_RGAIN");                break; 
		case IDX_IMG_BGAIN :                printf("IDX_IMG_BGAIN");                break; 
		case IDX_HR_MODE :                  printf("IDX_HR_MODE");                  break; 
		case IDX_BL_MODE :                  printf("IDX_BL_MODE");                  break; 
		case IDX_BLC_MODE :                 printf("IDX_BLC_MODE");                 break; 
		case IDX_BLC_DISP :                 printf("IDX_BLC_DISP");                 break; 
		case IDX_BLC_LEVEL :                printf("IDX_BLC_LEVEL");                break; 
		case IDX_BLC_AREA_X_SRT :           printf("IDX_BLC_AREA_X_SRT");           break; 
		case IDX_BLC_AREA_Y_SRT :           printf("IDX_BLC_AREA_Y_SRT");           break; 
		case IDX_BLC_AREA_WIDTH :           printf("IDX_BLC_AREA_WIDTH");           break; 
		case IDX_BLC_AREA_HEIGHT :          printf("IDX_BLC_AREA_HEIGHT");          break; 
		case IDX_WDR_MODE :                 printf("IDX_WDR_MODE");                 break; 
		case IDX_WDR_LEVEL :                printf("IDX_WDR_LEVEL");                break; 
		case IDX_HLC_MODE :                 printf("IDX_HLC_MODE");                 break; 
		case IDX_HLC_MASK_COLOR :           printf("IDX_HLC_MASK_COLOR");           break; 
		case IDX_HLC_LEVEL :                printf("IDX_HLC_LEVEL");                break; 
		case IDX_HLC_SCALE :                printf("IDX_HLC_SCALE");                break; 
		case IDX_DNR_MODE :                 printf("IDX_DNR_MODE");                 break; 
		case IDX_DNR_GLB_MOT :              printf("IDX_DNR_GLB_MOT");              break; 
		case IDX_DNR_LEVEL :                printf("IDX_DNR_LEVEL");                break; 
		case IDX_3DNR_LEVEL :               printf("IDX_3DNR_LEVEL");               break; 
		case IDX_2DNR_LEVEL :               printf("IDX_2DNR_LEVEL");               break; 
		case IDX_MD_ON :                    printf("IDX_MD_ON");                    break; 
		case IDX_MD1_STATE :                printf("IDX_MD1_STATE");                break; 
		case IDX_MD1_DISP :                 printf("IDX_MD1_DISP");                 break; 
		case IDX_MD1_ALARM :                printf("IDX_MD1_ALARM");                break; 
		case IDX_MD1_SENS :                 printf("IDX_MD1_SENS");                 break; 
		case IDX_MD1_X_SRT :                printf("IDX_MD1_X_SRT");                break; 
		case IDX_MD1_Y_SRT :                printf("IDX_MD1_Y_SRT");                break; 
		case IDX_MD1_WIDTH :                printf("IDX_MD1_WIDTH");                break; 
		case IDX_MD1_HEIGHT :               printf("IDX_MD1_HEIGHT");               break; 
		case IDX_MD2_STATE :                printf("IDX_MD2_STATE");                break; 
		case IDX_MD2_DISP :                 printf("IDX_MD2_DISP");                 break; 
		case IDX_MD2_ALARM :                printf("IDX_MD2_ALARM");                break; 
		case IDX_MD2_SENS :                 printf("IDX_MD2_SENS");                 break; 
		case IDX_MD2_X_SRT :                printf("IDX_MD2_X_SRT");                break; 
		case IDX_MD2_Y_SRT :                printf("IDX_MD2_Y_SRT");                break; 
		case IDX_MD2_WIDTH :                printf("IDX_MD2_WIDTH");                break; 
		case IDX_MD2_HEIGHT :               printf("IDX_MD2_HEIGHT");               break; 
		case IDX_MD3_STATE :                printf("IDX_MD3_STATE");                break; 
		case IDX_MD3_DISP :                 printf("IDX_MD3_DISP");                 break; 
		case IDX_MD3_ALARM :                printf("IDX_MD3_ALARM");                break; 
		case IDX_MD3_SENS :                 printf("IDX_MD3_SENS");                 break; 
		case IDX_MD3_X_SRT :                printf("IDX_MD3_X_SRT");                break; 
		case IDX_MD3_Y_SRT :                printf("IDX_MD3_Y_SRT");                break; 
		case IDX_MD3_WIDTH :                printf("IDX_MD3_WIDTH");                break; 
		case IDX_MD3_HEIGHT :               printf("IDX_MD3_HEIGHT");               break; 
		case IDX_MD4_STATE :                printf("IDX_MD4_STATE");                break; 
		case IDX_MD4_DISP :                 printf("IDX_MD4_DISP");                 break; 
		case IDX_MD4_ALARM :                printf("IDX_MD4_ALARM");                break; 
		case IDX_MD4_SENS :                 printf("IDX_MD4_SENS");                 break; 
		case IDX_MD4_X_SRT :                printf("IDX_MD4_X_SRT");                break; 
		case IDX_MD4_Y_SRT :                printf("IDX_MD4_Y_SRT");                break; 
		case IDX_MD4_WIDTH :                printf("IDX_MD4_WIDTH");                break; 
		case IDX_MD4_HEIGHT :               printf("IDX_MD4_HEIGHT");               break; 
		case IDX_MASK_ON :                  printf("IDX_MASK_ON");                  break; 
		case IDX_MASK_I :                   printf("IDX_MASK_I");                   break; 
		case IDX_MASK1_STATE :              printf("IDX_MASK1_STATE");              break; 
		case IDX_MASK1_TRANS :              printf("IDX_MASK1_TRANS");              break; 
		case IDX_MASK1_COLOR :              printf("IDX_MASK1_COLOR");              break; 
		case IDX_MASK1_MOSAIC :             printf("IDX_MASK1_MOSAIC");             break; 
		case IDX_MASK1_X_SRT :              printf("IDX_MASK1_X_SRT");              break; 
		case IDX_MASK1_Y_SRT :              printf("IDX_MASK1_Y_SRT");              break; 
		case IDX_MASK1_WIDTH :              printf("IDX_MASK1_WIDTH");              break; 
		case IDX_MASK1_HEIGHT :             printf("IDX_MASK1_HEIGHT");             break; 
		case IDX_MASK1_PAN :                printf("IDX_MASK1_PAN");                break; 
		case IDX_MASK1_TILT :               printf("IDX_MASK1_TILT");               break; 
		case IDX_MASK1_ZOOM :               printf("IDX_MASK1_ZOOM");               break; 
		case IDX_MASK2_STATE :              printf("IDX_MASK2_STATE");              break; 
		case IDX_MASK2_TRANS :              printf("IDX_MASK2_TRANS");              break; 
		case IDX_MASK2_COLOR :              printf("IDX_MASK2_COLOR");              break; 
		case IDX_MASK2_MOSAIC :             printf("IDX_MASK2_MOSAIC");             break; 
		case IDX_MASK2_X_SRT :              printf("IDX_MASK2_X_SRT");              break; 
		case IDX_MASK2_Y_SRT :              printf("IDX_MASK2_Y_SRT");              break; 
		case IDX_MASK2_WIDTH :              printf("IDX_MASK2_WIDTH");              break; 
		case IDX_MASK2_HEIGHT :             printf("IDX_MASK2_HEIGHT");             break; 
		case IDX_MASK2_PAN :                printf("IDX_MASK2_PAN");                break; 
		case IDX_MASK2_TILT :               printf("IDX_MASK2_TILT");               break; 
		case IDX_MASK2_ZOOM :               printf("IDX_MASK2_ZOOM");               break; 
		case IDX_MASK3_STATE :              printf("IDX_MASK3_STATE");              break; 
		case IDX_MASK3_TRANS :              printf("IDX_MASK3_TRANS");              break; 
		case IDX_MASK3_COLOR :              printf("IDX_MASK3_COLOR");              break; 
		case IDX_MASK3_MOSAIC :             printf("IDX_MASK3_MOSAIC");             break; 
		case IDX_MASK3_X_SRT :              printf("IDX_MASK3_X_SRT");              break; 
		case IDX_MASK3_Y_SRT :              printf("IDX_MASK3_Y_SRT");              break; 
		case IDX_MASK3_WIDTH :              printf("IDX_MASK3_WIDTH");              break; 
		case IDX_MASK3_HEIGHT :             printf("IDX_MASK3_HEIGHT");             break; 
		case IDX_MASK3_PAN :                printf("IDX_MASK3_PAN");                break; 
		case IDX_MASK3_TILT :               printf("IDX_MASK3_TILT");               break; 
		case IDX_MASK3_ZOOM :               printf("IDX_MASK3_ZOOM");               break; 
		case IDX_MASK4_STATE :              printf("IDX_MASK4_STATE");              break; 
		case IDX_MASK4_TRANS :              printf("IDX_MASK4_TRANS");              break; 
		case IDX_MASK4_COLOR :              printf("IDX_MASK4_COLOR");              break; 
		case IDX_MASK4_MOSAIC :             printf("IDX_MASK4_MOSAIC");             break; 
		case IDX_MASK4_X_SRT :              printf("IDX_MASK4_X_SRT");              break; 
		case IDX_MASK4_Y_SRT :              printf("IDX_MASK4_Y_SRT");              break; 
		case IDX_MASK4_WIDTH :              printf("IDX_MASK4_WIDTH");              break; 
		case IDX_MASK4_HEIGHT :             printf("IDX_MASK4_HEIGHT");             break; 
		case IDX_MASK4_PAN :                printf("IDX_MASK4_PAN");                break; 
		case IDX_MASK4_TILT :               printf("IDX_MASK4_TILT");               break; 
		case IDX_MASK4_ZOOM :               printf("IDX_MASK4_ZOOM");               break; 
		case IDX_MASK5_STATE :              printf("IDX_MASK5_STATE");              break; 
		case IDX_MASK5_TRANS :              printf("IDX_MASK5_TRANS");              break; 
		case IDX_MASK5_COLOR :              printf("IDX_MASK5_COLOR");              break; 
		case IDX_MASK5_MOSAIC :             printf("IDX_MASK5_MOSAIC");             break; 
		case IDX_MASK5_X_SRT :              printf("IDX_MASK5_X_SRT");              break; 
		case IDX_MASK5_Y_SRT :              printf("IDX_MASK5_Y_SRT");              break; 
		case IDX_MASK5_WIDTH :              printf("IDX_MASK5_WIDTH");              break; 
		case IDX_MASK5_HEIGHT :             printf("IDX_MASK5_HEIGHT");             break; 
		case IDX_MASK5_PAN :                printf("IDX_MASK5_PAN");                break; 
		case IDX_MASK5_TILT :               printf("IDX_MASK5_TILT");               break; 
		case IDX_MASK5_ZOOM :               printf("IDX_MASK5_ZOOM");               break; 
		case IDX_MASK6_STATE :              printf("IDX_MASK6_STATE");              break; 
		case IDX_MASK6_TRANS :              printf("IDX_MASK6_TRANS");              break; 
		case IDX_MASK6_COLOR :              printf("IDX_MASK6_COLOR");              break; 
		case IDX_MASK6_MOSAIC :             printf("IDX_MASK6_MOSAIC");             break; 
		case IDX_MASK6_X_SRT :              printf("IDX_MASK6_X_SRT");              break; 
		case IDX_MASK6_Y_SRT :              printf("IDX_MASK6_Y_SRT");              break; 
		case IDX_MASK6_WIDTH :              printf("IDX_MASK6_WIDTH");              break; 
		case IDX_MASK6_HEIGHT :             printf("IDX_MASK6_HEIGHT");             break; 
		case IDX_MASK6_PAN :                printf("IDX_MASK6_PAN");                break; 
		case IDX_MASK6_TILT :               printf("IDX_MASK6_TILT");               break; 
		case IDX_MASK6_ZOOM :               printf("IDX_MASK6_ZOOM");               break; 
		case IDX_MASK7_STATE :              printf("IDX_MASK7_STATE");              break; 
		case IDX_MASK7_TRANS :              printf("IDX_MASK7_TRANS");              break; 
		case IDX_MASK7_COLOR :              printf("IDX_MASK7_COLOR");              break; 
		case IDX_MASK7_MOSAIC :             printf("IDX_MASK7_MOSAIC");             break; 
		case IDX_MASK7_X_SRT :              printf("IDX_MASK7_X_SRT");              break; 
		case IDX_MASK7_Y_SRT :              printf("IDX_MASK7_Y_SRT");              break; 
		case IDX_MASK7_WIDTH :              printf("IDX_MASK7_WIDTH");              break; 
		case IDX_MASK7_HEIGHT :             printf("IDX_MASK7_HEIGHT");             break; 
		case IDX_MASK7_PAN :                printf("IDX_MASK7_PAN");                break; 
		case IDX_MASK7_TILT :               printf("IDX_MASK7_TILT");               break; 
		case IDX_MASK7_ZOOM :               printf("IDX_MASK7_ZOOM");               break; 
		case IDX_MASK8_STATE :              printf("IDX_MASK8_STATE");              break; 
		case IDX_MASK8_TRANS :              printf("IDX_MASK8_TRANS");              break; 
		case IDX_MASK8_COLOR :              printf("IDX_MASK8_COLOR");              break; 
		case IDX_MASK8_MOSAIC :             printf("IDX_MASK8_MOSAIC");             break; 
		case IDX_MASK8_X_SRT :              printf("IDX_MASK8_X_SRT");              break; 
		case IDX_MASK8_Y_SRT :              printf("IDX_MASK8_Y_SRT");              break; 
		case IDX_MASK8_WIDTH :              printf("IDX_MASK8_WIDTH");              break; 
		case IDX_MASK8_HEIGHT :             printf("IDX_MASK8_HEIGHT");             break; 
		case IDX_MASK8_PAN :                printf("IDX_MASK8_PAN");                break; 
		case IDX_MASK8_TILT :               printf("IDX_MASK8_TILT");               break; 
		case IDX_MASK8_ZOOM :               printf("IDX_MASK8_ZOOM");               break; 
		case IDX_DEFOG_ON :                 printf("IDX_DEFOG_ON");                 break; 
		case IDX_DIS_ON :                   printf("IDX_DIS_ON");                   break; 
		case IDX_SYNC :                     printf("IDX_SYNC");                     break; 
		case IDX_SHADE_ON :                 printf("IDX_SHADE_ON");                 break; 
		case IDX_SYNC_PHASE :               printf("IDX_SYNC_PHASE");               break; 
		case IDX_CAM_ID :                   printf("IDX_CAM_ID");                   break; 
		case IDX_CAMID_X_POS :              printf("IDX_CAMID_X_POS");              break; 
		case IDX_CAMID_Y_POS :              printf("IDX_CAMID_Y_POS");              break; 
		case IDX_BAUDRATE :                 printf("IDX_BAUDRATE");                 break; 
		case IDX_PROTOCOL :                 printf("IDX_PROTOCOL");                 break; 
		case IDX_OSD_LANGUAGE :             printf("IDX_OSD_LANGUAGE");             break; 
		case IDX_ID_ON :                    printf("IDX_ID_ON");                    break; 
		case IDX_TITLE_ON :                 printf("IDX_TITLE_ON");                 break; 
		case IDX_ZMAG_ON :                  printf("IDX_ZMAG_ON");                  break; 
		case IDX_FUNC_ON :                  printf("IDX_FUNC_ON");                  break; 
		case IDX_ALL_ON :                   printf("IDX_ALL_ON");                   break; 
		case IDX_TITLE_BLK :                printf("IDX_TITLE_BLK");                break; 
		case IDX_TITLE_COLOR :              printf("IDX_TITLE_COLOR");              break; 
		case IDX_TITLE_X_POS :              printf("IDX_TITLE_X_POS");              break; 
		case IDX_TITLE_Y_POS :              printf("IDX_TITLE_Y_POS");              break; 
		case IDX_CAM_TITLE_CH1 :            printf("IDX_CAM_TITLE_CH1");            break; 
		case IDX_CAM_TITLE_CH2 :            printf("IDX_CAM_TITLE_CH2");            break; 
		case IDX_CAM_TITLE_CH3 :            printf("IDX_CAM_TITLE_CH3");            break; 
		case IDX_CAM_TITLE_CH4 :            printf("IDX_CAM_TITLE_CH4");            break; 
		case IDX_CAM_TITLE_CH5 :            printf("IDX_CAM_TITLE_CH5");            break; 
		case IDX_CAM_TITLE_CH6 :            printf("IDX_CAM_TITLE_CH6");            break; 
		case IDX_CAM_TITLE_CH7 :            printf("IDX_CAM_TITLE_CH7");            break; 
		case IDX_CAM_TITLE_CH8 :            printf("IDX_CAM_TITLE_CH8");            break; 
		case IDX_CAM_TITLE_CH9 :            printf("IDX_CAM_TITLE_CH9");            break; 
		case IDX_CAM_TITLE_CH10 :           printf("IDX_CAM_TITLE_CH10");           break; 
		case IDX_CAM_TITLE_CH11 :           printf("IDX_CAM_TITLE_CH11");           break; 
		case IDX_CAM_TITLE_CH12 :           printf("IDX_CAM_TITLE_CH12");           break; 
		case IDX_CAM_TITLE_CH13 :           printf("IDX_CAM_TITLE_CH13");           break; 
		case IDX_CAM_TITLE_CH14 :           printf("IDX_CAM_TITLE_CH14");           break; 
		case IDX_CAM_TITLE_CH15 :           printf("IDX_CAM_TITLE_CH15");           break; 
		case IDX_CAM_TITLE_CH16 :           printf("IDX_CAM_TITLE_CH16");           break; 
		case IDX_CAM_TITLE_CH17 :           printf("IDX_CAM_TITLE_CH17");           break; 
		case IDX_CAM_TITLE_CH18 :           printf("IDX_CAM_TITLE_CH18");           break; 
		case IDX_CAM_TITLE_CH19 :           printf("IDX_CAM_TITLE_CH19");           break; 
		case IDX_CAM_TITLE_CH20 :           printf("IDX_CAM_TITLE_CH20");           break; 
		case IDX_CAM_TITLE_CH21 :           printf("IDX_CAM_TITLE_CH21");           break; 
		case IDX_CAM_TITLE_CH22 :           printf("IDX_CAM_TITLE_CH22");           break; 
		case IDX_CAM_TITLE_CH23 :           printf("IDX_CAM_TITLE_CH23");           break; 
		case IDX_CAM_TITLE_CH24 :           printf("IDX_CAM_TITLE_CH24");           break; 
		case IDX_VOUT_FORMAT :              printf("IDX_VOUT_FORMAT");              break; 
		case IDX_LVDS_D :                   printf("IDX_LVDS_D");                   break; 
		case IDX_DOUT_FULL :                printf("IDX_DOUT_FULL");                break; 
		case IDX_DOUT_ON :                  printf("IDX_DOUT_ON");                  break; 
		case IDX_CVBS_ON :                  printf("IDX_CVBS_ON");                  break; 
		case IDX_TGT_HALL_MAX :             printf("IDX_TGT_HALL_MAX");             break; 
		case IDX_TGT_HALL_MIN :             printf("IDX_TGT_HALL_MIN");             break; 
		case IDX_HADJ_MAX :                 printf("IDX_HADJ_MAX");                 break; 
		case IDX_HADJ_MIN :                 printf("IDX_HADJ_MIN");                 break; 
		case IDX_HO_ZERO :                  printf("IDX_HO_ZERO");                  break; 
		case IDX_HG_ZERO :                  printf("IDX_HG_ZERO");                  break; 
		case IDX_HB_ZERO :                  printf("IDX_HB_ZERO");                  break; 
		case IDX_HADJ_DIFF_OFF :            printf("IDX_HADJ_DIFF_OFF");            break; 
		case IDX_HADJ_MEAN_OFF :            printf("IDX_HADJ_MEAN_OFF");            break; 
		case IDX_HADJ_HG :                  printf("IDX_HADJ_HG");                  break; 
		case IDX_HADJ_HO :                  printf("IDX_HADJ_HO");                  break; 
		case IDX_HADJ_HB :                  printf("IDX_HADJ_HB");                  break; 
		case IDX_OADJ_ZADD :                printf("IDX_OADJ_ZADD");                break; 
		case IDX_OADJ_FADD :                printf("IDX_OADJ_FADD");                break; 
		case IDX_OADJ_ZOFF :                printf("IDX_OADJ_ZOFF");                break; 
		case IDX_OADJ_FOFF :                printf("IDX_OADJ_FOFF");                break; 
		case IDX_OADJ_PD_SRT :              printf("IDX_OADJ_PD_SRT");              break; 
		case IDX_OADJ_ZD_SRT :              printf("IDX_OADJ_ZD_SRT");              break; 
		case IDX_OADJ_FD_SRT :              printf("IDX_OADJ_FD_SRT");              break; 
		case IDX_OADJ_P2DEC_R :             printf("IDX_OADJ_P2DEC_R");             break; 
		case IDX_OADJ_T2DEC_R :             printf("IDX_OADJ_T2DEC_R");             break; 
		case IDX_OADJ_PD :                  printf("IDX_OADJ_PD");                  break; 
		case IDX_OADJ_ZD :                  printf("IDX_OADJ_ZD");                  break; 
		case IDX_OADJ_FD :                  printf("IDX_OADJ_FD");                  break; 
		case IDX_OADJ_WEND_S :              printf("IDX_OADJ_WEND_S");              break; 
		case IDX_OADJ_TEND_S :              printf("IDX_OADJ_TEND_S");              break; 
		case IDX_MADJ_3D_PAN_NT :           printf("IDX_MADJ_3D_PAN_NT");           break; 
		case IDX_MADJ_3D_TILT_NT :          printf("IDX_MADJ_3D_TILT_NT");          break; 
		case IDX_MADJ_3D_PAN_PA :           printf("IDX_MADJ_3D_PAN_PA");           break; 
		case IDX_MADJ_3D_TILT_PA :          printf("IDX_MADJ_3D_TILT_PA");          break; 
		case IDX_DADJ_THRESHOLD :           printf("IDX_DADJ_THRESHOLD");           break; 
		case IDX_SADJ_GAIN :                printf("IDX_SADJ_GAIN");                break; 
		case IDX_SADJ_OFFSET :              printf("IDX_SADJ_OFFSET");              break; 
		case IDX_LOGO_CH1 :                 printf("IDX_LOGO_CH1");                 break; 
		case IDX_LOGO_CH2 :                 printf("IDX_LOGO_CH2");                 break; 
		case IDX_LOGO_CH3 :                 printf("IDX_LOGO_CH3");                 break; 
		case IDX_LOGO_CH4 :                 printf("IDX_LOGO_CH4");                 break; 
		case IDX_LOGO_CH5 :                 printf("IDX_LOGO_CH5");                 break; 
		case IDX_LOGO_CH6 :                 printf("IDX_LOGO_CH6");                 break; 
		case IDX_LOGO_CH7 :                 printf("IDX_LOGO_CH7");                 break; 
		case IDX_LOGO_CH8 :                 printf("IDX_LOGO_CH8");                 break; 
		case IDX_LOGO_CH9 :                 printf("IDX_LOGO_CH9");                 break; 
		case IDX_LOGO_CH10 :                printf("IDX_LOGO_CH10");                break; 
		case IDX_LOGO_CH11 :                printf("IDX_LOGO_CH11");                break; 
		case IDX_LOGO_CH12 :                printf("IDX_LOGO_CH12");                break; 
		case IDX_LOGO_CH13 :                printf("IDX_LOGO_CH13");                break; 
		case IDX_LOGO_CH14 :                printf("IDX_LOGO_CH14");                break; 
		case IDX_LOGO_CH15 :                printf("IDX_LOGO_CH15");                break; 
		case IDX_LOGO_CH16 :                printf("IDX_LOGO_CH16");                break; 
		case IDX_LOGO_CH17 :                printf("IDX_LOGO_CH17");                break; 
		case IDX_LOGO_CH18 :                printf("IDX_LOGO_CH18");                break; 
		case IDX_LOGO_CH19 :                printf("IDX_LOGO_CH19");                break; 
		case IDX_LOGO_CH20 :                printf("IDX_LOGO_CH20");                break; 
		case IDX_LOGO_CH21 :                printf("IDX_LOGO_CH21");                break; 
		case IDX_LOGO_CH22 :                printf("IDX_LOGO_CH22");                break; 
		case IDX_LOGO_CH23 :                printf("IDX_LOGO_CH23");                break; 
		case IDX_LOGO_CH24 :                printf("IDX_LOGO_CH24");                break; 
		case IDX_LOGO_CH25 :                printf("IDX_LOGO_CH25");                break; 
		case IDX_LOGO_CH26 :                printf("IDX_LOGO_CH26");                break; 
		case IDX_LOGO_CH27 :                printf("IDX_LOGO_CH27");                break; 
		case IDX_LOGO_CH28 :                printf("IDX_LOGO_CH28");                break; 
		case IDX_LOGO_CH29 :                printf("IDX_LOGO_CH29");                break; 
		case IDX_LOGO_CH30 :                printf("IDX_LOGO_CH30");                break; 
		case IDX_LOGO_CH31 :                printf("IDX_LOGO_CH31");                break; 
		case IDX_LOGO_CH32 :                printf("IDX_LOGO_CH32");                break; 
		case IDX_ADKEY00 :                  printf("IDX_ADKEY00");                  break; 
		case IDX_ADKEY01 :                  printf("IDX_ADKEY01");                  break; 
		case IDX_ADKEY02 :                  printf("IDX_ADKEY02");                  break; 
		case IDX_ADKEY03 :                  printf("IDX_ADKEY03");                  break; 
		case IDX_ADKEY04 :                  printf("IDX_ADKEY04");                  break; 
		case IDX_ADKEY05 :                  printf("IDX_ADKEY05");                  break; 
		case IDX_ADKEY06 :                  printf("IDX_ADKEY06");                  break; 
		case IDX_ADKEY07 :                  printf("IDX_ADKEY07");                  break; 
		case IDX_ADKEY10 :                  printf("IDX_ADKEY10");                  break; 
		case IDX_ADKEY11 :                  printf("IDX_ADKEY11");                  break; 
		case IDX_ADKEY12 :                  printf("IDX_ADKEY12");                  break; 
		case IDX_ADKEY13 :                  printf("IDX_ADKEY13");                  break; 
		case IDX_ADKEY14 :                  printf("IDX_ADKEY14");                  break; 
		case IDX_ADKEY15 :                  printf("IDX_ADKEY15");                  break; 
		case IDX_ADKEY16 :                  printf("IDX_ADKEY16");                  break; 
		case IDX_ADKEY17 :                  printf("IDX_ADKEY17");                  break; 
		case VDX_PWR_ON :                   printf("VDX_PWR_ON");                   break; 
		case VDX_ZOOM_POS :                 printf("VDX_ZOOM_POS");                 break; 
		case VDX_DZOOM_ON :                 printf("VDX_DZOOM_ON");                 break; 
		case VDX_DZOOM_MODE :               printf("VDX_DZOOM_MODE");               break; 
		case VDX_DZOOM_POS :                printf("VDX_DZOOM_POS");                break; 
		case VDX_FOCUS_POS :                printf("VDX_FOCUS_POS");                break; 
		case VDX_F_MODE :                   printf("VDX_F_MODE");                   break; 
		case VDX_NEAR_LIMIT :               printf("VDX_NEAR_LIMIT");               break; 
		case VDX_AF_SENS :                  printf("VDX_AF_SENS");                  break; 
		case VDX_AF_MODE :                  printf("VDX_AF_MODE");                  break; 
		case VDX_AF_MOVE_TIME :             printf("VDX_AF_MOVE_TIME");             break; 
		case VDX_AF_INTERVAL_TIME :         printf("VDX_AF_INTERVAL_TIME");         break; 
		case VDX_IR_COR :                   printf("VDX_IR_COR");                   break; 
		case VDX_WB_MODE :                  printf("VDX_WB_MODE");                  break; 
		case VDX_PUSH_WB_RGAIN :            printf("VDX_PUSH_WB_RGAIN");            break; 
		case VDX_PUSH_WB_BGAIN :            printf("VDX_PUSH_WB_BGAIN");            break; 
		case VDX_R_GAIN :                   printf("VDX_R_GAIN");                   break; 
		case VDX_B_GAIN :                   printf("VDX_B_GAIN");                   break; 
		case VDX_AE_MODE :                  printf("VDX_AE_MODE");                  break; 
		case VDX_ASS_ON :                   printf("VDX_ASS_ON");                   break; 
		case VDX_SHUTTER_STEP :             printf("VDX_SHUTTER_STEP");             break; 
		case VDX_IRIS_STEP :                printf("VDX_IRIS_STEP");                break; 
		case VDX_GAIN_STEP :                printf("VDX_GAIN_STEP");                break; 
		case VDX_BRIGHT_STEP :              printf("VDX_BRIGHT_STEP");              break; 
		case VDX_COMP_ON :                  printf("VDX_COMP_ON");                  break; 
		case VDX_EXP_COMP_VAL :             printf("VDX_EXP_COMP_VAL");             break; 
		case VDX_BLC_ON :                   printf("VDX_BLC_ON");                   break; 
		case VDX_SPOT_AE_ON :               printf("VDX_SPOT_AE_ON");               break; 
		case VDX_SPOT_AE_X_POS :            printf("VDX_SPOT_AE_X_POS");            break; 
		case VDX_SPOT_AE_Y_POS :            printf("VDX_SPOT_AE_Y_POS");            break; 
		case VDX_AE_RESPONSE :              printf("VDX_AE_RESPONSE");              break; 
		case VDX_WD_MODE :                  printf("VDX_WD_MODE");                  break; 
		case VDX_WD_BRT_L :                 printf("VDX_WD_BRT_L");                 break; 
		case VDX_WD_BRT_COMP :              printf("VDX_WD_BRT_COMP");              break; 
		case VDX_WD_COMP_L :                printf("VDX_WD_COMP_L");                break; 
		case VDX_DEFOG_ON :                 printf("VDX_DEFOG_ON");                 break; 
		case VDX_APER_GAIN :                printf("VDX_APER_GAIN");                break; 
		case VDX_HR_ON :                    printf("VDX_HR_ON");                    break; 
		case VDX_NR_SET :                   printf("VDX_NR_SET");                   break; 
		case VDX_GAM_SET :                  printf("VDX_GAM_SET");                  break; 
		case VDX_HIGH_SENS_ON :             printf("VDX_HIGH_SENS_ON");             break; 
		case VDX_LR_ON :                    printf("VDX_LR_ON");                    break; 
		case VDX_FREEZE_ON :                printf("VDX_FREEZE_ON");                break; 
		case VDX_P_EFFECT :                 printf("VDX_P_EFFECT");                 break; 
		case VDX_FLIP_ON :                  printf("VDX_FLIP_ON");                  break; 
		case VDX_ICR_ON :                   printf("VDX_ICR_ON");                   break; 
		case VDX_AICR_ON :                  printf("VDX_AICR_ON");                  break; 
		case VDX_AICR_THRS_L :              printf("VDX_AICR_THRS_L");              break; 
		case VDX_AICR_ALARM_ON :            printf("VDX_AICR_ALARM_ON");            break; 
		case VDX_DISP_ON :                  printf("VDX_DISP_ON");                  break; 
		case VDX_TITLE_H_POS0 :             printf("VDX_TITLE_H_POS0");             break; 
		case VDX_TITLE_ON0 :                printf("VDX_TITLE_ON0");                break; 
		case VDX_TITLE_LINE0 :              printf("VDX_TITLE_LINE0");              break; 
		case VDX_TITLE_BLINK0 :             printf("VDX_TITLE_BLINK0");             break; 
		case VDX_TITLE_COLOR0 :             printf("VDX_TITLE_COLOR0");             break; 
		case VDX_TITLE_LINE0_CH1 :          printf("VDX_TITLE_LINE0_CH1");          break; 
		case VDX_TITLE_LINE0_CH2 :          printf("VDX_TITLE_LINE0_CH2");          break; 
		case VDX_TITLE_LINE0_CH3 :          printf("VDX_TITLE_LINE0_CH3");          break; 
		case VDX_TITLE_LINE0_CH4 :          printf("VDX_TITLE_LINE0_CH4");          break; 
		case VDX_TITLE_LINE0_CH5 :          printf("VDX_TITLE_LINE0_CH5");          break; 
		case VDX_TITLE_LINE0_CH6 :          printf("VDX_TITLE_LINE0_CH6");          break; 
		case VDX_TITLE_LINE0_CH7 :          printf("VDX_TITLE_LINE0_CH7");          break; 
		case VDX_TITLE_LINE0_CH8 :          printf("VDX_TITLE_LINE0_CH8");          break; 
		case VDX_TITLE_LINE0_CH9 :          printf("VDX_TITLE_LINE0_CH9");          break; 
		case VDX_TITLE_LINE0_CH10 :         printf("VDX_TITLE_LINE0_CH10");         break; 
		case VDX_TITLE_LINE0_CH11 :         printf("VDX_TITLE_LINE0_CH11");         break; 
		case VDX_TITLE_LINE0_CH12 :         printf("VDX_TITLE_LINE0_CH12");         break; 
		case VDX_TITLE_LINE0_CH13 :         printf("VDX_TITLE_LINE0_CH13");         break; 
		case VDX_TITLE_LINE0_CH14 :         printf("VDX_TITLE_LINE0_CH14");         break; 
		case VDX_TITLE_LINE0_CH15 :         printf("VDX_TITLE_LINE0_CH15");         break; 
		case VDX_TITLE_LINE0_CH16 :         printf("VDX_TITLE_LINE0_CH16");         break; 
		case VDX_TITLE_LINE0_CH17 :         printf("VDX_TITLE_LINE0_CH17");         break; 
		case VDX_TITLE_LINE0_CH18 :         printf("VDX_TITLE_LINE0_CH18");         break; 
		case VDX_TITLE_LINE0_CH19 :         printf("VDX_TITLE_LINE0_CH19");         break; 
		case VDX_TITLE_LINE0_CH20 :         printf("VDX_TITLE_LINE0_CH20");         break; 
		case VDX_TITLE_H_POS1 :             printf("VDX_TITLE_H_POS1");             break; 
		case VDX_TITLE_ON1 :                printf("VDX_TITLE_ON1");                break; 
		case VDX_TITLE_LINE1 :              printf("VDX_TITLE_LINE1");              break; 
		case VDX_TITLE_BLINK1 :             printf("VDX_TITLE_BLINK1");             break; 
		case VDX_TITLE_COLOR1 :             printf("VDX_TITLE_COLOR1");             break; 
		case VDX_TITLE_LINE1_CH1 :          printf("VDX_TITLE_LINE1_CH1");          break; 
		case VDX_TITLE_LINE1_CH2 :          printf("VDX_TITLE_LINE1_CH2");          break; 
		case VDX_TITLE_LINE1_CH3 :          printf("VDX_TITLE_LINE1_CH3");          break; 
		case VDX_TITLE_LINE1_CH4 :          printf("VDX_TITLE_LINE1_CH4");          break; 
		case VDX_TITLE_LINE1_CH5 :          printf("VDX_TITLE_LINE1_CH5");          break; 
		case VDX_TITLE_LINE1_CH6 :          printf("VDX_TITLE_LINE1_CH6");          break; 
		case VDX_TITLE_LINE1_CH7 :          printf("VDX_TITLE_LINE1_CH7");          break; 
		case VDX_TITLE_LINE1_CH8 :          printf("VDX_TITLE_LINE1_CH8");          break; 
		case VDX_TITLE_LINE1_CH9 :          printf("VDX_TITLE_LINE1_CH9");          break; 
		case VDX_TITLE_LINE1_CH10 :         printf("VDX_TITLE_LINE1_CH10");         break; 
		case VDX_TITLE_LINE1_CH11 :         printf("VDX_TITLE_LINE1_CH11");         break; 
		case VDX_TITLE_LINE1_CH12 :         printf("VDX_TITLE_LINE1_CH12");         break; 
		case VDX_TITLE_LINE1_CH13 :         printf("VDX_TITLE_LINE1_CH13");         break; 
		case VDX_TITLE_LINE1_CH14 :         printf("VDX_TITLE_LINE1_CH14");         break; 
		case VDX_TITLE_LINE1_CH15 :         printf("VDX_TITLE_LINE1_CH15");         break; 
		case VDX_TITLE_LINE1_CH16 :         printf("VDX_TITLE_LINE1_CH16");         break; 
		case VDX_TITLE_LINE1_CH17 :         printf("VDX_TITLE_LINE1_CH17");         break; 
		case VDX_TITLE_LINE1_CH18 :         printf("VDX_TITLE_LINE1_CH18");         break; 
		case VDX_TITLE_LINE1_CH19 :         printf("VDX_TITLE_LINE1_CH19");         break; 
		case VDX_TITLE_LINE1_CH20 :         printf("VDX_TITLE_LINE1_CH20");         break; 
		case VDX_TITLE_H_POS2 :             printf("VDX_TITLE_H_POS2");             break; 
		case VDX_TITLE_ON2 :                printf("VDX_TITLE_ON2");                break; 
		case VDX_TITLE_LINE2 :              printf("VDX_TITLE_LINE2");              break; 
		case VDX_TITLE_BLINK2 :             printf("VDX_TITLE_BLINK2");             break; 
		case VDX_TITLE_COLOR2 :             printf("VDX_TITLE_COLOR2");             break; 
		case VDX_TITLE_LINE2_CH1 :          printf("VDX_TITLE_LINE2_CH1");          break; 
		case VDX_TITLE_LINE2_CH2 :          printf("VDX_TITLE_LINE2_CH2");          break; 
		case VDX_TITLE_LINE2_CH3 :          printf("VDX_TITLE_LINE2_CH3");          break; 
		case VDX_TITLE_LINE2_CH4 :          printf("VDX_TITLE_LINE2_CH4");          break; 
		case VDX_TITLE_LINE2_CH5 :          printf("VDX_TITLE_LINE2_CH5");          break; 
		case VDX_TITLE_LINE2_CH6 :          printf("VDX_TITLE_LINE2_CH6");          break; 
		case VDX_TITLE_LINE2_CH7 :          printf("VDX_TITLE_LINE2_CH7");          break; 
		case VDX_TITLE_LINE2_CH8 :          printf("VDX_TITLE_LINE2_CH8");          break; 
		case VDX_TITLE_LINE2_CH9 :          printf("VDX_TITLE_LINE2_CH9");          break; 
		case VDX_TITLE_LINE2_CH10 :         printf("VDX_TITLE_LINE2_CH10");         break; 
		case VDX_TITLE_LINE2_CH11 :         printf("VDX_TITLE_LINE2_CH11");         break; 
		case VDX_TITLE_LINE2_CH12 :         printf("VDX_TITLE_LINE2_CH12");         break; 
		case VDX_TITLE_LINE2_CH13 :         printf("VDX_TITLE_LINE2_CH13");         break; 
		case VDX_TITLE_LINE2_CH14 :         printf("VDX_TITLE_LINE2_CH14");         break; 
		case VDX_TITLE_LINE2_CH15 :         printf("VDX_TITLE_LINE2_CH15");         break; 
		case VDX_TITLE_LINE2_CH16 :         printf("VDX_TITLE_LINE2_CH16");         break; 
		case VDX_TITLE_LINE2_CH17 :         printf("VDX_TITLE_LINE2_CH17");         break; 
		case VDX_TITLE_LINE2_CH18 :         printf("VDX_TITLE_LINE2_CH18");         break; 
		case VDX_TITLE_LINE2_CH19 :         printf("VDX_TITLE_LINE2_CH19");         break; 
		case VDX_TITLE_LINE2_CH20 :         printf("VDX_TITLE_LINE2_CH20");         break; 
		case VDX_TITLE_H_POS3 :             printf("VDX_TITLE_H_POS3");             break; 
		case VDX_TITLE_ON3 :                printf("VDX_TITLE_ON3");                break; 
		case VDX_TITLE_LINE3 :              printf("VDX_TITLE_LINE3");              break; 
		case VDX_TITLE_BLINK3 :             printf("VDX_TITLE_BLINK3");             break; 
		case VDX_TITLE_COLOR3 :             printf("VDX_TITLE_COLOR3");             break; 
		case VDX_TITLE_LINE3_CH1 :          printf("VDX_TITLE_LINE3_CH1");          break; 
		case VDX_TITLE_LINE3_CH2 :          printf("VDX_TITLE_LINE3_CH2");          break; 
		case VDX_TITLE_LINE3_CH3 :          printf("VDX_TITLE_LINE3_CH3");          break; 
		case VDX_TITLE_LINE3_CH4 :          printf("VDX_TITLE_LINE3_CH4");          break; 
		case VDX_TITLE_LINE3_CH5 :          printf("VDX_TITLE_LINE3_CH5");          break; 
		case VDX_TITLE_LINE3_CH6 :          printf("VDX_TITLE_LINE3_CH6");          break; 
		case VDX_TITLE_LINE3_CH7 :          printf("VDX_TITLE_LINE3_CH7");          break; 
		case VDX_TITLE_LINE3_CH8 :          printf("VDX_TITLE_LINE3_CH8");          break; 
		case VDX_TITLE_LINE3_CH9 :          printf("VDX_TITLE_LINE3_CH9");          break; 
		case VDX_TITLE_LINE3_CH10 :         printf("VDX_TITLE_LINE3_CH10");         break; 
		case VDX_TITLE_LINE3_CH11 :         printf("VDX_TITLE_LINE3_CH11");         break; 
		case VDX_TITLE_LINE3_CH12 :         printf("VDX_TITLE_LINE3_CH12");         break; 
		case VDX_TITLE_LINE3_CH13 :         printf("VDX_TITLE_LINE3_CH13");         break; 
		case VDX_TITLE_LINE3_CH14 :         printf("VDX_TITLE_LINE3_CH14");         break; 
		case VDX_TITLE_LINE3_CH15 :         printf("VDX_TITLE_LINE3_CH15");         break; 
		case VDX_TITLE_LINE3_CH16 :         printf("VDX_TITLE_LINE3_CH16");         break; 
		case VDX_TITLE_LINE3_CH17 :         printf("VDX_TITLE_LINE3_CH17");         break; 
		case VDX_TITLE_LINE3_CH18 :         printf("VDX_TITLE_LINE3_CH18");         break; 
		case VDX_TITLE_LINE3_CH19 :         printf("VDX_TITLE_LINE3_CH19");         break; 
		case VDX_TITLE_LINE3_CH20 :         printf("VDX_TITLE_LINE3_CH20");         break; 
		case VDX_TITLE_H_POS4 :             printf("VDX_TITLE_H_POS4");             break; 
		case VDX_TITLE_ON4 :                printf("VDX_TITLE_ON4");                break; 
		case VDX_TITLE_LINE4 :              printf("VDX_TITLE_LINE4");              break; 
		case VDX_TITLE_BLINK4 :             printf("VDX_TITLE_BLINK4");             break; 
		case VDX_TITLE_COLOR4 :             printf("VDX_TITLE_COLOR4");             break; 
		case VDX_TITLE_LINE4_CH1 :          printf("VDX_TITLE_LINE4_CH1");          break; 
		case VDX_TITLE_LINE4_CH2 :          printf("VDX_TITLE_LINE4_CH2");          break; 
		case VDX_TITLE_LINE4_CH3 :          printf("VDX_TITLE_LINE4_CH3");          break; 
		case VDX_TITLE_LINE4_CH4 :          printf("VDX_TITLE_LINE4_CH4");          break; 
		case VDX_TITLE_LINE4_CH5 :          printf("VDX_TITLE_LINE4_CH5");          break; 
		case VDX_TITLE_LINE4_CH6 :          printf("VDX_TITLE_LINE4_CH6");          break; 
		case VDX_TITLE_LINE4_CH7 :          printf("VDX_TITLE_LINE4_CH7");          break; 
		case VDX_TITLE_LINE4_CH8 :          printf("VDX_TITLE_LINE4_CH8");          break; 
		case VDX_TITLE_LINE4_CH9 :          printf("VDX_TITLE_LINE4_CH9");          break; 
		case VDX_TITLE_LINE4_CH10 :         printf("VDX_TITLE_LINE4_CH10");         break; 
		case VDX_TITLE_LINE4_CH11 :         printf("VDX_TITLE_LINE4_CH11");         break; 
		case VDX_TITLE_LINE4_CH12 :         printf("VDX_TITLE_LINE4_CH12");         break; 
		case VDX_TITLE_LINE4_CH13 :         printf("VDX_TITLE_LINE4_CH13");         break; 
		case VDX_TITLE_LINE4_CH14 :         printf("VDX_TITLE_LINE4_CH14");         break; 
		case VDX_TITLE_LINE4_CH15 :         printf("VDX_TITLE_LINE4_CH15");         break; 
		case VDX_TITLE_LINE4_CH16 :         printf("VDX_TITLE_LINE4_CH16");         break; 
		case VDX_TITLE_LINE4_CH17 :         printf("VDX_TITLE_LINE4_CH17");         break; 
		case VDX_TITLE_LINE4_CH18 :         printf("VDX_TITLE_LINE4_CH18");         break; 
		case VDX_TITLE_LINE4_CH19 :         printf("VDX_TITLE_LINE4_CH19");         break; 
		case VDX_TITLE_LINE4_CH20 :         printf("VDX_TITLE_LINE4_CH20");         break; 
		case VDX_TITLE_H_POS5 :             printf("VDX_TITLE_H_POS5");             break; 
		case VDX_TITLE_ON5 :                printf("VDX_TITLE_ON5");                break; 
		case VDX_TITLE_LINE5 :              printf("VDX_TITLE_LINE5");              break; 
		case VDX_TITLE_BLINK5 :             printf("VDX_TITLE_BLINK5");             break; 
		case VDX_TITLE_COLOR5 :             printf("VDX_TITLE_COLOR5");             break; 
		case VDX_TITLE_LINE5_CH1 :          printf("VDX_TITLE_LINE5_CH1");          break; 
		case VDX_TITLE_LINE5_CH2 :          printf("VDX_TITLE_LINE5_CH2");          break; 
		case VDX_TITLE_LINE5_CH3 :          printf("VDX_TITLE_LINE5_CH3");          break; 
		case VDX_TITLE_LINE5_CH4 :          printf("VDX_TITLE_LINE5_CH4");          break; 
		case VDX_TITLE_LINE5_CH5 :          printf("VDX_TITLE_LINE5_CH5");          break; 
		case VDX_TITLE_LINE5_CH6 :          printf("VDX_TITLE_LINE5_CH6");          break; 
		case VDX_TITLE_LINE5_CH7 :          printf("VDX_TITLE_LINE5_CH7");          break; 
		case VDX_TITLE_LINE5_CH8 :          printf("VDX_TITLE_LINE5_CH8");          break; 
		case VDX_TITLE_LINE5_CH9 :          printf("VDX_TITLE_LINE5_CH9");          break; 
		case VDX_TITLE_LINE5_CH10 :         printf("VDX_TITLE_LINE5_CH10");         break; 
		case VDX_TITLE_LINE5_CH11 :         printf("VDX_TITLE_LINE5_CH11");         break; 
		case VDX_TITLE_LINE5_CH12 :         printf("VDX_TITLE_LINE5_CH12");         break; 
		case VDX_TITLE_LINE5_CH13 :         printf("VDX_TITLE_LINE5_CH13");         break; 
		case VDX_TITLE_LINE5_CH14 :         printf("VDX_TITLE_LINE5_CH14");         break; 
		case VDX_TITLE_LINE5_CH15 :         printf("VDX_TITLE_LINE5_CH15");         break; 
		case VDX_TITLE_LINE5_CH16 :         printf("VDX_TITLE_LINE5_CH16");         break; 
		case VDX_TITLE_LINE5_CH17 :         printf("VDX_TITLE_LINE5_CH17");         break; 
		case VDX_TITLE_LINE5_CH18 :         printf("VDX_TITLE_LINE5_CH18");         break; 
		case VDX_TITLE_LINE5_CH19 :         printf("VDX_TITLE_LINE5_CH19");         break; 
		case VDX_TITLE_LINE5_CH20 :         printf("VDX_TITLE_LINE5_CH20");         break; 
		case VDX_TITLE_H_POS6 :             printf("VDX_TITLE_H_POS6");             break; 
		case VDX_TITLE_ON6 :                printf("VDX_TITLE_ON6");                break; 
		case VDX_TITLE_LINE6 :              printf("VDX_TITLE_LINE6");              break; 
		case VDX_TITLE_BLINK6 :             printf("VDX_TITLE_BLINK6");             break; 
		case VDX_TITLE_COLOR6 :             printf("VDX_TITLE_COLOR6");             break; 
		case VDX_TITLE_LINE6_CH1 :          printf("VDX_TITLE_LINE6_CH1");          break; 
		case VDX_TITLE_LINE6_CH2 :          printf("VDX_TITLE_LINE6_CH2");          break; 
		case VDX_TITLE_LINE6_CH3 :          printf("VDX_TITLE_LINE6_CH3");          break; 
		case VDX_TITLE_LINE6_CH4 :          printf("VDX_TITLE_LINE6_CH4");          break; 
		case VDX_TITLE_LINE6_CH5 :          printf("VDX_TITLE_LINE6_CH5");          break; 
		case VDX_TITLE_LINE6_CH6 :          printf("VDX_TITLE_LINE6_CH6");          break; 
		case VDX_TITLE_LINE6_CH7 :          printf("VDX_TITLE_LINE6_CH7");          break; 
		case VDX_TITLE_LINE6_CH8 :          printf("VDX_TITLE_LINE6_CH8");          break; 
		case VDX_TITLE_LINE6_CH9 :          printf("VDX_TITLE_LINE6_CH9");          break; 
		case VDX_TITLE_LINE6_CH10 :         printf("VDX_TITLE_LINE6_CH10");         break; 
		case VDX_TITLE_LINE6_CH11 :         printf("VDX_TITLE_LINE6_CH11");         break; 
		case VDX_TITLE_LINE6_CH12 :         printf("VDX_TITLE_LINE6_CH12");         break; 
		case VDX_TITLE_LINE6_CH13 :         printf("VDX_TITLE_LINE6_CH13");         break; 
		case VDX_TITLE_LINE6_CH14 :         printf("VDX_TITLE_LINE6_CH14");         break; 
		case VDX_TITLE_LINE6_CH15 :         printf("VDX_TITLE_LINE6_CH15");         break; 
		case VDX_TITLE_LINE6_CH16 :         printf("VDX_TITLE_LINE6_CH16");         break; 
		case VDX_TITLE_LINE6_CH17 :         printf("VDX_TITLE_LINE6_CH17");         break; 
		case VDX_TITLE_LINE6_CH18 :         printf("VDX_TITLE_LINE6_CH18");         break; 
		case VDX_TITLE_LINE6_CH19 :         printf("VDX_TITLE_LINE6_CH19");         break; 
		case VDX_TITLE_LINE6_CH20 :         printf("VDX_TITLE_LINE6_CH20");         break; 
		case VDX_TITLE_H_POS7 :             printf("VDX_TITLE_H_POS7");             break; 
		case VDX_TITLE_ON7 :                printf("VDX_TITLE_ON7");                break; 
		case VDX_TITLE_LINE7 :              printf("VDX_TITLE_LINE7");              break; 
		case VDX_TITLE_BLINK7 :             printf("VDX_TITLE_BLINK7");             break; 
		case VDX_TITLE_COLOR7 :             printf("VDX_TITLE_COLOR7");             break; 
		case VDX_TITLE_LINE7_CH1 :          printf("VDX_TITLE_LINE7_CH1");          break; 
		case VDX_TITLE_LINE7_CH2 :          printf("VDX_TITLE_LINE7_CH2");          break; 
		case VDX_TITLE_LINE7_CH3 :          printf("VDX_TITLE_LINE7_CH3");          break; 
		case VDX_TITLE_LINE7_CH4 :          printf("VDX_TITLE_LINE7_CH4");          break; 
		case VDX_TITLE_LINE7_CH5 :          printf("VDX_TITLE_LINE7_CH5");          break; 
		case VDX_TITLE_LINE7_CH6 :          printf("VDX_TITLE_LINE7_CH6");          break; 
		case VDX_TITLE_LINE7_CH7 :          printf("VDX_TITLE_LINE7_CH7");          break; 
		case VDX_TITLE_LINE7_CH8 :          printf("VDX_TITLE_LINE7_CH8");          break; 
		case VDX_TITLE_LINE7_CH9 :          printf("VDX_TITLE_LINE7_CH9");          break; 
		case VDX_TITLE_LINE7_CH10 :         printf("VDX_TITLE_LINE7_CH10");         break; 
		case VDX_TITLE_LINE7_CH11 :         printf("VDX_TITLE_LINE7_CH11");         break; 
		case VDX_TITLE_LINE7_CH12 :         printf("VDX_TITLE_LINE7_CH12");         break; 
		case VDX_TITLE_LINE7_CH13 :         printf("VDX_TITLE_LINE7_CH13");         break; 
		case VDX_TITLE_LINE7_CH14 :         printf("VDX_TITLE_LINE7_CH14");         break; 
		case VDX_TITLE_LINE7_CH15 :         printf("VDX_TITLE_LINE7_CH15");         break; 
		case VDX_TITLE_LINE7_CH16 :         printf("VDX_TITLE_LINE7_CH16");         break; 
		case VDX_TITLE_LINE7_CH17 :         printf("VDX_TITLE_LINE7_CH17");         break; 
		case VDX_TITLE_LINE7_CH18 :         printf("VDX_TITLE_LINE7_CH18");         break; 
		case VDX_TITLE_LINE7_CH19 :         printf("VDX_TITLE_LINE7_CH19");         break; 
		case VDX_TITLE_LINE7_CH20 :         printf("VDX_TITLE_LINE7_CH20");         break; 
		case VDX_TITLE_H_POS8 :             printf("VDX_TITLE_H_POS8");             break; 
		case VDX_TITLE_ON8 :                printf("VDX_TITLE_ON8");                break; 
		case VDX_TITLE_LINE8 :              printf("VDX_TITLE_LINE8");              break; 
		case VDX_TITLE_BLINK8 :             printf("VDX_TITLE_BLINK8");             break; 
		case VDX_TITLE_COLOR8 :             printf("VDX_TITLE_COLOR8");             break; 
		case VDX_TITLE_LINE8_CH1 :          printf("VDX_TITLE_LINE8_CH1");          break; 
		case VDX_TITLE_LINE8_CH2 :          printf("VDX_TITLE_LINE8_CH2");          break; 
		case VDX_TITLE_LINE8_CH3 :          printf("VDX_TITLE_LINE8_CH3");          break; 
		case VDX_TITLE_LINE8_CH4 :          printf("VDX_TITLE_LINE8_CH4");          break; 
		case VDX_TITLE_LINE8_CH5 :          printf("VDX_TITLE_LINE8_CH5");          break; 
		case VDX_TITLE_LINE8_CH6 :          printf("VDX_TITLE_LINE8_CH6");          break; 
		case VDX_TITLE_LINE8_CH7 :          printf("VDX_TITLE_LINE8_CH7");          break; 
		case VDX_TITLE_LINE8_CH8 :          printf("VDX_TITLE_LINE8_CH8");          break; 
		case VDX_TITLE_LINE8_CH9 :          printf("VDX_TITLE_LINE8_CH9");          break; 
		case VDX_TITLE_LINE8_CH10 :         printf("VDX_TITLE_LINE8_CH10");         break; 
		case VDX_TITLE_LINE8_CH11 :         printf("VDX_TITLE_LINE8_CH11");         break; 
		case VDX_TITLE_LINE8_CH12 :         printf("VDX_TITLE_LINE8_CH12");         break; 
		case VDX_TITLE_LINE8_CH13 :         printf("VDX_TITLE_LINE8_CH13");         break; 
		case VDX_TITLE_LINE8_CH14 :         printf("VDX_TITLE_LINE8_CH14");         break; 
		case VDX_TITLE_LINE8_CH15 :         printf("VDX_TITLE_LINE8_CH15");         break; 
		case VDX_TITLE_LINE8_CH16 :         printf("VDX_TITLE_LINE8_CH16");         break; 
		case VDX_TITLE_LINE8_CH17 :         printf("VDX_TITLE_LINE8_CH17");         break; 
		case VDX_TITLE_LINE8_CH18 :         printf("VDX_TITLE_LINE8_CH18");         break; 
		case VDX_TITLE_LINE8_CH19 :         printf("VDX_TITLE_LINE8_CH19");         break; 
		case VDX_TITLE_LINE8_CH20 :         printf("VDX_TITLE_LINE8_CH20");         break; 
		case VDX_TITLE_H_POS9 :             printf("VDX_TITLE_H_POS9");             break; 
		case VDX_TITLE_ON9 :                printf("VDX_TITLE_ON9");                break; 
		case VDX_TITLE_LINE9 :              printf("VDX_TITLE_LINE9");              break; 
		case VDX_TITLE_BLINK9 :             printf("VDX_TITLE_BLINK9");             break; 
		case VDX_TITLE_COLOR9 :             printf("VDX_TITLE_COLOR9");             break; 
		case VDX_TITLE_LINE9_CH1 :          printf("VDX_TITLE_LINE9_CH1");          break; 
		case VDX_TITLE_LINE9_CH2 :          printf("VDX_TITLE_LINE9_CH2");          break; 
		case VDX_TITLE_LINE9_CH3 :          printf("VDX_TITLE_LINE9_CH3");          break; 
		case VDX_TITLE_LINE9_CH4 :          printf("VDX_TITLE_LINE9_CH4");          break; 
		case VDX_TITLE_LINE9_CH5 :          printf("VDX_TITLE_LINE9_CH5");          break; 
		case VDX_TITLE_LINE9_CH6 :          printf("VDX_TITLE_LINE9_CH6");          break; 
		case VDX_TITLE_LINE9_CH7 :          printf("VDX_TITLE_LINE9_CH7");          break; 
		case VDX_TITLE_LINE9_CH8 :          printf("VDX_TITLE_LINE9_CH8");          break; 
		case VDX_TITLE_LINE9_CH9 :          printf("VDX_TITLE_LINE9_CH9");          break; 
		case VDX_TITLE_LINE9_CH10 :         printf("VDX_TITLE_LINE9_CH10");         break; 
		case VDX_TITLE_LINE9_CH11 :         printf("VDX_TITLE_LINE9_CH11");         break; 
		case VDX_TITLE_LINE9_CH12 :         printf("VDX_TITLE_LINE9_CH12");         break; 
		case VDX_TITLE_LINE9_CH13 :         printf("VDX_TITLE_LINE9_CH13");         break; 
		case VDX_TITLE_LINE9_CH14 :         printf("VDX_TITLE_LINE9_CH14");         break; 
		case VDX_TITLE_LINE9_CH15 :         printf("VDX_TITLE_LINE9_CH15");         break; 
		case VDX_TITLE_LINE9_CH16 :         printf("VDX_TITLE_LINE9_CH16");         break; 
		case VDX_TITLE_LINE9_CH17 :         printf("VDX_TITLE_LINE9_CH17");         break; 
		case VDX_TITLE_LINE9_CH18 :         printf("VDX_TITLE_LINE9_CH18");         break; 
		case VDX_TITLE_LINE9_CH19 :         printf("VDX_TITLE_LINE9_CH19");         break; 
		case VDX_TITLE_LINE9_CH20 :         printf("VDX_TITLE_LINE9_CH20");         break; 
		case VDX_TITLE_H_POS10 :            printf("VDX_TITLE_H_POS10");            break; 
		case VDX_TITLE_ON10 :               printf("VDX_TITLE_ON10");               break; 
		case VDX_TITLE_LINE10 :             printf("VDX_TITLE_LINE10");             break; 
		case VDX_TITLE_BLINK10 :            printf("VDX_TITLE_BLINK10");            break; 
		case VDX_TITLE_COLOR10 :            printf("VDX_TITLE_COLOR10");            break; 
		case VDX_TITLE_LINE10_CH1 :         printf("VDX_TITLE_LINE10_CH1");         break; 
		case VDX_TITLE_LINE10_CH2 :         printf("VDX_TITLE_LINE10_CH2");         break; 
		case VDX_TITLE_LINE10_CH3 :         printf("VDX_TITLE_LINE10_CH3");         break; 
		case VDX_TITLE_LINE10_CH4 :         printf("VDX_TITLE_LINE10_CH4");         break; 
		case VDX_TITLE_LINE10_CH5 :         printf("VDX_TITLE_LINE10_CH5");         break; 
		case VDX_TITLE_LINE10_CH6 :         printf("VDX_TITLE_LINE10_CH6");         break; 
		case VDX_TITLE_LINE10_CH7 :         printf("VDX_TITLE_LINE10_CH7");         break; 
		case VDX_TITLE_LINE10_CH8 :         printf("VDX_TITLE_LINE10_CH8");         break; 
		case VDX_TITLE_LINE10_CH9 :         printf("VDX_TITLE_LINE10_CH9");         break; 
		case VDX_TITLE_LINE10_CH10 :        printf("VDX_TITLE_LINE10_CH10");        break; 
		case VDX_TITLE_LINE10_CH11 :        printf("VDX_TITLE_LINE10_CH11");        break; 
		case VDX_TITLE_LINE10_CH12 :        printf("VDX_TITLE_LINE10_CH12");        break; 
		case VDX_TITLE_LINE10_CH13 :        printf("VDX_TITLE_LINE10_CH13");        break; 
		case VDX_TITLE_LINE10_CH14 :        printf("VDX_TITLE_LINE10_CH14");        break; 
		case VDX_TITLE_LINE10_CH15 :        printf("VDX_TITLE_LINE10_CH15");        break; 
		case VDX_TITLE_LINE10_CH16 :        printf("VDX_TITLE_LINE10_CH16");        break; 
		case VDX_TITLE_LINE10_CH17 :        printf("VDX_TITLE_LINE10_CH17");        break; 
		case VDX_TITLE_LINE10_CH18 :        printf("VDX_TITLE_LINE10_CH18");        break; 
		case VDX_TITLE_LINE10_CH19 :        printf("VDX_TITLE_LINE10_CH19");        break; 
		case VDX_TITLE_LINE10_CH20 :        printf("VDX_TITLE_LINE10_CH20");        break; 
		case VDX_MUTE_ON :                  printf("VDX_MUTE_ON");                  break; 
		case VDX_MASK_CL_ON :               printf("VDX_MASK_CL_ON");               break; 
		case VDX_MASK_ON01 :                printf("VDX_MASK_ON01");                break; 
		case VDX_MASK_DISP_ON01 :           printf("VDX_MASK_DISP_ON01");           break; 
		case VDX_MASK_I01 :                 printf("VDX_MASK_I01");                 break; 
		case VDX_MASK_TRANS01 :             printf("VDX_MASK_TRANS01");             break; 
		case VDX_MASK_MOSAIC01 :            printf("VDX_MASK_MOSAIC01");            break; 
		case VDX_MASK_COLOR_ON01 :          printf("VDX_MASK_COLOR_ON01");          break; 
		case VDX_MASK_COLOR_OFF01 :         printf("VDX_MASK_COLOR_OFF01");         break; 
		case VDX_MASK_X_POS01 :             printf("VDX_MASK_X_POS01");             break; 
		case VDX_MASK_Y_POS01 :             printf("VDX_MASK_Y_POS01");             break; 
		case VDX_MASK_WIDTH01 :             printf("VDX_MASK_WIDTH01");             break; 
		case VDX_MASK_HEIGHT01 :            printf("VDX_MASK_HEIGHT01");            break; 
		case VDX_MASK_PAN_ANGLE01 :         printf("VDX_MASK_PAN_ANGLE01");         break; 
		case VDX_MASK_TILT_ANGLE01 :        printf("VDX_MASK_TILT_ANGLE01");        break; 
		case VDX_MASK_ZOOM01 :              printf("VDX_MASK_ZOOM01");              break; 
		case VDX_MASK_ON02 :                printf("VDX_MASK_ON02");                break; 
		case VDX_MASK_DISP_ON02 :           printf("VDX_MASK_DISP_ON02");           break; 
		case VDX_MASK_I02 :                 printf("VDX_MASK_I02");                 break; 
		case VDX_MASK_TRANS02 :             printf("VDX_MASK_TRANS02");             break; 
		case VDX_MASK_MOSAIC02 :            printf("VDX_MASK_MOSAIC02");            break; 
		case VDX_MASK_COLOR_ON02 :          printf("VDX_MASK_COLOR_ON02");          break; 
		case VDX_MASK_COLOR_OFF02 :         printf("VDX_MASK_COLOR_OFF02");         break; 
		case VDX_MASK_X_POS02 :             printf("VDX_MASK_X_POS02");             break; 
		case VDX_MASK_Y_POS02 :             printf("VDX_MASK_Y_POS02");             break; 
		case VDX_MASK_WIDTH02 :             printf("VDX_MASK_WIDTH02");             break; 
		case VDX_MASK_HEIGHT02 :            printf("VDX_MASK_HEIGHT02");            break; 
		case VDX_MASK_PAN_ANGLE02 :         printf("VDX_MASK_PAN_ANGLE02");         break; 
		case VDX_MASK_TILT_ANGLE02 :        printf("VDX_MASK_TILT_ANGLE02");        break; 
		case VDX_MASK_ZOOM02 :              printf("VDX_MASK_ZOOM02");              break; 
		case VDX_MASK_ON03 :                printf("VDX_MASK_ON03");                break; 
		case VDX_MASK_DISP_ON03 :           printf("VDX_MASK_DISP_ON03");           break; 
		case VDX_MASK_I03 :                 printf("VDX_MASK_I03");                 break; 
		case VDX_MASK_TRANS03 :             printf("VDX_MASK_TRANS03");             break; 
		case VDX_MASK_MOSAIC03 :            printf("VDX_MASK_MOSAIC03");            break; 
		case VDX_MASK_COLOR_ON03 :          printf("VDX_MASK_COLOR_ON03");          break; 
		case VDX_MASK_COLOR_OFF03 :         printf("VDX_MASK_COLOR_OFF03");         break; 
		case VDX_MASK_X_POS03 :             printf("VDX_MASK_X_POS03");             break; 
		case VDX_MASK_Y_POS03 :             printf("VDX_MASK_Y_POS03");             break; 
		case VDX_MASK_WIDTH03 :             printf("VDX_MASK_WIDTH03");             break; 
		case VDX_MASK_HEIGHT03 :            printf("VDX_MASK_HEIGHT03");            break; 
		case VDX_MASK_PAN_ANGLE03 :         printf("VDX_MASK_PAN_ANGLE03");         break; 
		case VDX_MASK_TILT_ANGLE03 :        printf("VDX_MASK_TILT_ANGLE03");        break; 
		case VDX_MASK_ZOOM03 :              printf("VDX_MASK_ZOOM03");              break; 
		case VDX_MASK_ON04 :                printf("VDX_MASK_ON04");                break; 
		case VDX_MASK_DISP_ON04 :           printf("VDX_MASK_DISP_ON04");           break; 
		case VDX_MASK_I04 :                 printf("VDX_MASK_I04");                 break; 
		case VDX_MASK_TRANS04 :             printf("VDX_MASK_TRANS04");             break; 
		case VDX_MASK_MOSAIC04 :            printf("VDX_MASK_MOSAIC04");            break; 
		case VDX_MASK_COLOR_ON04 :          printf("VDX_MASK_COLOR_ON04");          break; 
		case VDX_MASK_COLOR_OFF04 :         printf("VDX_MASK_COLOR_OFF04");         break; 
		case VDX_MASK_X_POS04 :             printf("VDX_MASK_X_POS04");             break; 
		case VDX_MASK_Y_POS04 :             printf("VDX_MASK_Y_POS04");             break; 
		case VDX_MASK_WIDTH04 :             printf("VDX_MASK_WIDTH04");             break; 
		case VDX_MASK_HEIGHT04 :            printf("VDX_MASK_HEIGHT04");            break; 
		case VDX_MASK_PAN_ANGLE04 :         printf("VDX_MASK_PAN_ANGLE04");         break; 
		case VDX_MASK_TILT_ANGLE04 :        printf("VDX_MASK_TILT_ANGLE04");        break; 
		case VDX_MASK_ZOOM04 :              printf("VDX_MASK_ZOOM04");              break; 
		case VDX_MASK_ON05 :                printf("VDX_MASK_ON05");                break; 
		case VDX_MASK_DISP_ON05 :           printf("VDX_MASK_DISP_ON05");           break; 
		case VDX_MASK_I05 :                 printf("VDX_MASK_I05");                 break; 
		case VDX_MASK_TRANS05 :             printf("VDX_MASK_TRANS05");             break; 
		case VDX_MASK_MOSAIC05 :            printf("VDX_MASK_MOSAIC05");            break; 
		case VDX_MASK_COLOR_ON05 :          printf("VDX_MASK_COLOR_ON05");          break; 
		case VDX_MASK_COLOR_OFF05 :         printf("VDX_MASK_COLOR_OFF05");         break; 
		case VDX_MASK_X_POS05 :             printf("VDX_MASK_X_POS05");             break; 
		case VDX_MASK_Y_POS05 :             printf("VDX_MASK_Y_POS05");             break; 
		case VDX_MASK_WIDTH05 :             printf("VDX_MASK_WIDTH05");             break; 
		case VDX_MASK_HEIGHT05 :            printf("VDX_MASK_HEIGHT05");            break; 
		case VDX_MASK_PAN_ANGLE05 :         printf("VDX_MASK_PAN_ANGLE05");         break; 
		case VDX_MASK_TILT_ANGLE05 :        printf("VDX_MASK_TILT_ANGLE05");        break; 
		case VDX_MASK_ZOOM05 :              printf("VDX_MASK_ZOOM05");              break; 
		case VDX_MASK_ON06 :                printf("VDX_MASK_ON06");                break; 
		case VDX_MASK_DISP_ON06 :           printf("VDX_MASK_DISP_ON06");           break; 
		case VDX_MASK_I06 :                 printf("VDX_MASK_I06");                 break; 
		case VDX_MASK_TRANS06 :             printf("VDX_MASK_TRANS06");             break; 
		case VDX_MASK_MOSAIC06 :            printf("VDX_MASK_MOSAIC06");            break; 
		case VDX_MASK_COLOR_ON06 :          printf("VDX_MASK_COLOR_ON06");          break; 
		case VDX_MASK_COLOR_OFF06 :         printf("VDX_MASK_COLOR_OFF06");         break; 
		case VDX_MASK_X_POS06 :             printf("VDX_MASK_X_POS06");             break; 
		case VDX_MASK_Y_POS06 :             printf("VDX_MASK_Y_POS06");             break; 
		case VDX_MASK_WIDTH06 :             printf("VDX_MASK_WIDTH06");             break; 
		case VDX_MASK_HEIGHT06 :            printf("VDX_MASK_HEIGHT06");            break; 
		case VDX_MASK_PAN_ANGLE06 :         printf("VDX_MASK_PAN_ANGLE06");         break; 
		case VDX_MASK_TILT_ANGLE06 :        printf("VDX_MASK_TILT_ANGLE06");        break; 
		case VDX_MASK_ZOOM06 :              printf("VDX_MASK_ZOOM06");              break; 
		case VDX_MASK_ON07 :                printf("VDX_MASK_ON07");                break; 
		case VDX_MASK_DISP_ON07 :           printf("VDX_MASK_DISP_ON07");           break; 
		case VDX_MASK_I07 :                 printf("VDX_MASK_I07");                 break; 
		case VDX_MASK_TRANS07 :             printf("VDX_MASK_TRANS07");             break; 
		case VDX_MASK_MOSAIC07 :            printf("VDX_MASK_MOSAIC07");            break; 
		case VDX_MASK_COLOR_ON07 :          printf("VDX_MASK_COLOR_ON07");          break; 
		case VDX_MASK_COLOR_OFF07 :         printf("VDX_MASK_COLOR_OFF07");         break; 
		case VDX_MASK_X_POS07 :             printf("VDX_MASK_X_POS07");             break; 
		case VDX_MASK_Y_POS07 :             printf("VDX_MASK_Y_POS07");             break; 
		case VDX_MASK_WIDTH07 :             printf("VDX_MASK_WIDTH07");             break; 
		case VDX_MASK_HEIGHT07 :            printf("VDX_MASK_HEIGHT07");            break; 
		case VDX_MASK_PAN_ANGLE07 :         printf("VDX_MASK_PAN_ANGLE07");         break; 
		case VDX_MASK_TILT_ANGLE07 :        printf("VDX_MASK_TILT_ANGLE07");        break; 
		case VDX_MASK_ZOOM07 :              printf("VDX_MASK_ZOOM07");              break; 
		case VDX_MASK_ON08 :                printf("VDX_MASK_ON08");                break; 
		case VDX_MASK_DISP_ON08 :           printf("VDX_MASK_DISP_ON08");           break; 
		case VDX_MASK_I08 :                 printf("VDX_MASK_I08");                 break; 
		case VDX_MASK_TRANS08 :             printf("VDX_MASK_TRANS08");             break; 
		case VDX_MASK_MOSAIC08 :            printf("VDX_MASK_MOSAIC08");            break; 
		case VDX_MASK_COLOR_ON08 :          printf("VDX_MASK_COLOR_ON08");          break; 
		case VDX_MASK_COLOR_OFF08 :         printf("VDX_MASK_COLOR_OFF08");         break; 
		case VDX_MASK_X_POS08 :             printf("VDX_MASK_X_POS08");             break; 
		case VDX_MASK_Y_POS08 :             printf("VDX_MASK_Y_POS08");             break; 
		case VDX_MASK_WIDTH08 :             printf("VDX_MASK_WIDTH08");             break; 
		case VDX_MASK_HEIGHT08 :            printf("VDX_MASK_HEIGHT08");            break; 
		case VDX_MASK_PAN_ANGLE08 :         printf("VDX_MASK_PAN_ANGLE08");         break; 
		case VDX_MASK_TILT_ANGLE08 :        printf("VDX_MASK_TILT_ANGLE08");        break; 
		case VDX_MASK_ZOOM08 :              printf("VDX_MASK_ZOOM08");              break; 
		case VDX_MASK_ON11 :                printf("VDX_MASK_ON11");                break; 
		case VDX_MASK_DISP_ON11 :           printf("VDX_MASK_DISP_ON11");           break; 
		case VDX_MASK_I11 :                 printf("VDX_MASK_I11");                 break; 
		case VDX_MASK_TRANS11 :             printf("VDX_MASK_TRANS11");             break; 
		case VDX_MASK_MOSAIC11 :            printf("VDX_MASK_MOSAIC11");            break; 
		case VDX_MASK_COLOR_ON11 :          printf("VDX_MASK_COLOR_ON11");          break; 
		case VDX_MASK_COLOR_OFF11 :         printf("VDX_MASK_COLOR_OFF11");         break; 
		case VDX_MASK_X_POS11 :             printf("VDX_MASK_X_POS11");             break; 
		case VDX_MASK_Y_POS11 :             printf("VDX_MASK_Y_POS11");             break; 
		case VDX_MASK_WIDTH11 :             printf("VDX_MASK_WIDTH11");             break; 
		case VDX_MASK_HEIGHT11 :            printf("VDX_MASK_HEIGHT11");            break; 
		case VDX_MASK_PAN_ANGLE11 :         printf("VDX_MASK_PAN_ANGLE11");         break; 
		case VDX_MASK_TILT_ANGLE11 :        printf("VDX_MASK_TILT_ANGLE11");        break; 
		case VDX_MASK_ZOOM11 :              printf("VDX_MASK_ZOOM11");              break; 
		case VDX_MASK_ON12 :                printf("VDX_MASK_ON12");                break; 
		case VDX_MASK_DISP_ON12 :           printf("VDX_MASK_DISP_ON12");           break; 
		case VDX_MASK_I12 :                 printf("VDX_MASK_I12");                 break; 
		case VDX_MASK_TRANS12 :             printf("VDX_MASK_TRANS12");             break; 
		case VDX_MASK_MOSAIC12 :            printf("VDX_MASK_MOSAIC12");            break; 
		case VDX_MASK_COLOR_ON12 :          printf("VDX_MASK_COLOR_ON12");          break; 
		case VDX_MASK_COLOR_OFF12 :         printf("VDX_MASK_COLOR_OFF12");         break; 
		case VDX_MASK_X_POS12 :             printf("VDX_MASK_X_POS12");             break; 
		case VDX_MASK_Y_POS12 :             printf("VDX_MASK_Y_POS12");             break; 
		case VDX_MASK_WIDTH12 :             printf("VDX_MASK_WIDTH12");             break; 
		case VDX_MASK_HEIGHT12 :            printf("VDX_MASK_HEIGHT12");            break; 
		case VDX_MASK_PAN_ANGLE12 :         printf("VDX_MASK_PAN_ANGLE12");         break; 
		case VDX_MASK_TILT_ANGLE12 :        printf("VDX_MASK_TILT_ANGLE12");        break; 
		case VDX_MASK_ZOOM12 :              printf("VDX_MASK_ZOOM12");              break; 
		case VDX_MASK_ON13 :                printf("VDX_MASK_ON13");                break; 
		case VDX_MASK_DISP_ON13 :           printf("VDX_MASK_DISP_ON13");           break; 
		case VDX_MASK_I13 :                 printf("VDX_MASK_I13");                 break; 
		case VDX_MASK_TRANS13 :             printf("VDX_MASK_TRANS13");             break; 
		case VDX_MASK_MOSAIC13 :            printf("VDX_MASK_MOSAIC13");            break; 
		case VDX_MASK_COLOR_ON13 :          printf("VDX_MASK_COLOR_ON13");          break; 
		case VDX_MASK_COLOR_OFF13 :         printf("VDX_MASK_COLOR_OFF13");         break; 
		case VDX_MASK_X_POS13 :             printf("VDX_MASK_X_POS13");             break; 
		case VDX_MASK_Y_POS13 :             printf("VDX_MASK_Y_POS13");             break; 
		case VDX_MASK_WIDTH13 :             printf("VDX_MASK_WIDTH13");             break; 
		case VDX_MASK_HEIGHT13 :            printf("VDX_MASK_HEIGHT13");            break; 
		case VDX_MASK_PAN_ANGLE13 :         printf("VDX_MASK_PAN_ANGLE13");         break; 
		case VDX_MASK_TILT_ANGLE13 :        printf("VDX_MASK_TILT_ANGLE13");        break; 
		case VDX_MASK_ZOOM13 :              printf("VDX_MASK_ZOOM13");              break; 
		case VDX_MASK_ON14 :                printf("VDX_MASK_ON14");                break; 
		case VDX_MASK_DISP_ON14 :           printf("VDX_MASK_DISP_ON14");           break; 
		case VDX_MASK_I14 :                 printf("VDX_MASK_I14");                 break; 
		case VDX_MASK_TRANS14 :             printf("VDX_MASK_TRANS14");             break; 
		case VDX_MASK_MOSAIC14 :            printf("VDX_MASK_MOSAIC14");            break; 
		case VDX_MASK_COLOR_ON14 :          printf("VDX_MASK_COLOR_ON14");          break; 
		case VDX_MASK_COLOR_OFF14 :         printf("VDX_MASK_COLOR_OFF14");         break; 
		case VDX_MASK_X_POS14 :             printf("VDX_MASK_X_POS14");             break; 
		case VDX_MASK_Y_POS14 :             printf("VDX_MASK_Y_POS14");             break; 
		case VDX_MASK_WIDTH14 :             printf("VDX_MASK_WIDTH14");             break; 
		case VDX_MASK_HEIGHT14 :            printf("VDX_MASK_HEIGHT14");            break; 
		case VDX_MASK_PAN_ANGLE14 :         printf("VDX_MASK_PAN_ANGLE14");         break; 
		case VDX_MASK_TILT_ANGLE14 :        printf("VDX_MASK_TILT_ANGLE14");        break; 
		case VDX_MASK_ZOOM14 :              printf("VDX_MASK_ZOOM14");              break; 
		case VDX_MASK_ON15 :                printf("VDX_MASK_ON15");                break; 
		case VDX_MASK_DISP_ON15 :           printf("VDX_MASK_DISP_ON15");           break; 
		case VDX_MASK_I15 :                 printf("VDX_MASK_I15");                 break; 
		case VDX_MASK_TRANS15 :             printf("VDX_MASK_TRANS15");             break; 
		case VDX_MASK_MOSAIC15 :            printf("VDX_MASK_MOSAIC15");            break; 
		case VDX_MASK_COLOR_ON15 :          printf("VDX_MASK_COLOR_ON15");          break; 
		case VDX_MASK_COLOR_OFF15 :         printf("VDX_MASK_COLOR_OFF15");         break; 
		case VDX_MASK_X_POS15 :             printf("VDX_MASK_X_POS15");             break; 
		case VDX_MASK_Y_POS15 :             printf("VDX_MASK_Y_POS15");             break; 
		case VDX_MASK_WIDTH15 :             printf("VDX_MASK_WIDTH15");             break; 
		case VDX_MASK_HEIGHT15 :            printf("VDX_MASK_HEIGHT15");            break; 
		case VDX_MASK_PAN_ANGLE15 :         printf("VDX_MASK_PAN_ANGLE15");         break; 
		case VDX_MASK_TILT_ANGLE15 :        printf("VDX_MASK_TILT_ANGLE15");        break; 
		case VDX_MASK_ZOOM15 :              printf("VDX_MASK_ZOOM15");              break; 
		case VDX_MASK_ON16 :                printf("VDX_MASK_ON16");                break; 
		case VDX_MASK_DISP_ON16 :           printf("VDX_MASK_DISP_ON16");           break; 
		case VDX_MASK_I16 :                 printf("VDX_MASK_I16");                 break; 
		case VDX_MASK_TRANS16 :             printf("VDX_MASK_TRANS16");             break; 
		case VDX_MASK_MOSAIC16 :            printf("VDX_MASK_MOSAIC16");            break; 
		case VDX_MASK_COLOR_ON16 :          printf("VDX_MASK_COLOR_ON16");          break; 
		case VDX_MASK_COLOR_OFF16 :         printf("VDX_MASK_COLOR_OFF16");         break; 
		case VDX_MASK_X_POS16 :             printf("VDX_MASK_X_POS16");             break; 
		case VDX_MASK_Y_POS16 :             printf("VDX_MASK_Y_POS16");             break; 
		case VDX_MASK_WIDTH16 :             printf("VDX_MASK_WIDTH16");             break; 
		case VDX_MASK_HEIGHT16 :            printf("VDX_MASK_HEIGHT16");            break; 
		case VDX_MASK_PAN_ANGLE16 :         printf("VDX_MASK_PAN_ANGLE16");         break; 
		case VDX_MASK_TILT_ANGLE16 :        printf("VDX_MASK_TILT_ANGLE16");        break; 
		case VDX_MASK_ZOOM16 :              printf("VDX_MASK_ZOOM16");              break; 
		case VDX_MASK_ON17 :                printf("VDX_MASK_ON17");                break; 
		case VDX_MASK_DISP_ON17 :           printf("VDX_MASK_DISP_ON17");           break; 
		case VDX_MASK_I17 :                 printf("VDX_MASK_I17");                 break; 
		case VDX_MASK_TRANS17 :             printf("VDX_MASK_TRANS17");             break; 
		case VDX_MASK_MOSAIC17 :            printf("VDX_MASK_MOSAIC17");            break; 
		case VDX_MASK_COLOR_ON17 :          printf("VDX_MASK_COLOR_ON17");          break; 
		case VDX_MASK_COLOR_OFF17 :         printf("VDX_MASK_COLOR_OFF17");         break; 
		case VDX_MASK_X_POS17 :             printf("VDX_MASK_X_POS17");             break; 
		case VDX_MASK_Y_POS17 :             printf("VDX_MASK_Y_POS17");             break; 
		case VDX_MASK_WIDTH17 :             printf("VDX_MASK_WIDTH17");             break; 
		case VDX_MASK_HEIGHT17 :            printf("VDX_MASK_HEIGHT17");            break; 
		case VDX_MASK_PAN_ANGLE17 :         printf("VDX_MASK_PAN_ANGLE17");         break; 
		case VDX_MASK_TILT_ANGLE17 :        printf("VDX_MASK_TILT_ANGLE17");        break; 
		case VDX_MASK_ZOOM17 :              printf("VDX_MASK_ZOOM17");              break; 
		case VDX_MASK_ON18 :                printf("VDX_MASK_ON18");                break; 
		case VDX_MASK_DISP_ON18 :           printf("VDX_MASK_DISP_ON18");           break; 
		case VDX_MASK_I18 :                 printf("VDX_MASK_I18");                 break; 
		case VDX_MASK_TRANS18 :             printf("VDX_MASK_TRANS18");             break; 
		case VDX_MASK_MOSAIC18 :            printf("VDX_MASK_MOSAIC18");            break; 
		case VDX_MASK_COLOR_ON18 :          printf("VDX_MASK_COLOR_ON18");          break; 
		case VDX_MASK_COLOR_OFF18 :         printf("VDX_MASK_COLOR_OFF18");         break; 
		case VDX_MASK_X_POS18 :             printf("VDX_MASK_X_POS18");             break; 
		case VDX_MASK_Y_POS18 :             printf("VDX_MASK_Y_POS18");             break; 
		case VDX_MASK_WIDTH18 :             printf("VDX_MASK_WIDTH18");             break; 
		case VDX_MASK_HEIGHT18 :            printf("VDX_MASK_HEIGHT18");            break; 
		case VDX_MASK_PAN_ANGLE18 :         printf("VDX_MASK_PAN_ANGLE18");         break; 
		case VDX_MASK_TILT_ANGLE18 :        printf("VDX_MASK_TILT_ANGLE18");        break; 
		case VDX_MASK_ZOOM18 :              printf("VDX_MASK_ZOOM18");              break; 
		case VDX_MASK_ON21 :                printf("VDX_MASK_ON21");                break; 
		case VDX_MASK_DISP_ON21 :           printf("VDX_MASK_DISP_ON21");           break; 
		case VDX_MASK_I21 :                 printf("VDX_MASK_I21");                 break; 
		case VDX_MASK_TRANS21 :             printf("VDX_MASK_TRANS21");             break; 
		case VDX_MASK_MOSAIC21 :            printf("VDX_MASK_MOSAIC21");            break; 
		case VDX_MASK_COLOR_ON21 :          printf("VDX_MASK_COLOR_ON21");          break; 
		case VDX_MASK_COLOR_OFF21 :         printf("VDX_MASK_COLOR_OFF21");         break; 
		case VDX_MASK_X_POS21 :             printf("VDX_MASK_X_POS21");             break; 
		case VDX_MASK_Y_POS21 :             printf("VDX_MASK_Y_POS21");             break; 
		case VDX_MASK_WIDTH21 :             printf("VDX_MASK_WIDTH21");             break; 
		case VDX_MASK_HEIGHT21 :            printf("VDX_MASK_HEIGHT21");            break; 
		case VDX_MASK_PAN_ANGLE21 :         printf("VDX_MASK_PAN_ANGLE21");         break; 
		case VDX_MASK_TILT_ANGLE21 :        printf("VDX_MASK_TILT_ANGLE21");        break; 
		case VDX_MASK_ZOOM21 :              printf("VDX_MASK_ZOOM21");              break; 
		case VDX_MASK_ON22 :                printf("VDX_MASK_ON22");                break; 
		case VDX_MASK_DISP_ON22 :           printf("VDX_MASK_DISP_ON22");           break; 
		case VDX_MASK_I22 :                 printf("VDX_MASK_I22");                 break; 
		case VDX_MASK_TRANS22 :             printf("VDX_MASK_TRANS22");             break; 
		case VDX_MASK_MOSAIC22 :            printf("VDX_MASK_MOSAIC22");            break; 
		case VDX_MASK_COLOR_ON22 :          printf("VDX_MASK_COLOR_ON22");          break; 
		case VDX_MASK_COLOR_OFF22 :         printf("VDX_MASK_COLOR_OFF22");         break; 
		case VDX_MASK_X_POS22 :             printf("VDX_MASK_X_POS22");             break; 
		case VDX_MASK_Y_POS22 :             printf("VDX_MASK_Y_POS22");             break; 
		case VDX_MASK_WIDTH22 :             printf("VDX_MASK_WIDTH22");             break; 
		case VDX_MASK_HEIGHT22 :            printf("VDX_MASK_HEIGHT22");            break; 
		case VDX_MASK_PAN_ANGLE22 :         printf("VDX_MASK_PAN_ANGLE22");         break; 
		case VDX_MASK_TILT_ANGLE22 :        printf("VDX_MASK_TILT_ANGLE22");        break; 
		case VDX_MASK_ZOOM22 :              printf("VDX_MASK_ZOOM22");              break; 
		case VDX_MASK_ON23 :                printf("VDX_MASK_ON23");                break; 
		case VDX_MASK_DISP_ON23 :           printf("VDX_MASK_DISP_ON23");           break; 
		case VDX_MASK_I23 :                 printf("VDX_MASK_I23");                 break; 
		case VDX_MASK_TRANS23 :             printf("VDX_MASK_TRANS23");             break; 
		case VDX_MASK_MOSAIC23 :            printf("VDX_MASK_MOSAIC23");            break; 
		case VDX_MASK_COLOR_ON23 :          printf("VDX_MASK_COLOR_ON23");          break; 
		case VDX_MASK_COLOR_OFF23 :         printf("VDX_MASK_COLOR_OFF23");         break; 
		case VDX_MASK_X_POS23 :             printf("VDX_MASK_X_POS23");             break; 
		case VDX_MASK_Y_POS23 :             printf("VDX_MASK_Y_POS23");             break; 
		case VDX_MASK_WIDTH23 :             printf("VDX_MASK_WIDTH23");             break; 
		case VDX_MASK_HEIGHT23 :            printf("VDX_MASK_HEIGHT23");            break; 
		case VDX_MASK_PAN_ANGLE23 :         printf("VDX_MASK_PAN_ANGLE23");         break; 
		case VDX_MASK_TILT_ANGLE23 :        printf("VDX_MASK_TILT_ANGLE23");        break; 
		case VDX_MASK_ZOOM23 :              printf("VDX_MASK_ZOOM23");              break; 
		case VDX_MASK_ON24 :                printf("VDX_MASK_ON24");                break; 
		case VDX_MASK_DISP_ON24 :           printf("VDX_MASK_DISP_ON24");           break; 
		case VDX_MASK_I24 :                 printf("VDX_MASK_I24");                 break; 
		case VDX_MASK_TRANS24 :             printf("VDX_MASK_TRANS24");             break; 
		case VDX_MASK_MOSAIC24 :            printf("VDX_MASK_MOSAIC24");            break; 
		case VDX_MASK_COLOR_ON24 :          printf("VDX_MASK_COLOR_ON24");          break; 
		case VDX_MASK_COLOR_OFF24 :         printf("VDX_MASK_COLOR_OFF24");         break; 
		case VDX_MASK_X_POS24 :             printf("VDX_MASK_X_POS24");             break; 
		case VDX_MASK_Y_POS24 :             printf("VDX_MASK_Y_POS24");             break; 
		case VDX_MASK_WIDTH24 :             printf("VDX_MASK_WIDTH24");             break; 
		case VDX_MASK_HEIGHT24 :            printf("VDX_MASK_HEIGHT24");            break; 
		case VDX_MASK_PAN_ANGLE24 :         printf("VDX_MASK_PAN_ANGLE24");         break; 
		case VDX_MASK_TILT_ANGLE24 :        printf("VDX_MASK_TILT_ANGLE24");        break; 
		case VDX_MASK_ZOOM24 :              printf("VDX_MASK_ZOOM24");              break; 
		case VDX_MASK_ON25 :                printf("VDX_MASK_ON25");                break; 
		case VDX_MASK_DISP_ON25 :           printf("VDX_MASK_DISP_ON25");           break; 
		case VDX_MASK_I25 :                 printf("VDX_MASK_I25");                 break; 
		case VDX_MASK_TRANS25 :             printf("VDX_MASK_TRANS25");             break; 
		case VDX_MASK_MOSAIC25 :            printf("VDX_MASK_MOSAIC25");            break; 
		case VDX_MASK_COLOR_ON25 :          printf("VDX_MASK_COLOR_ON25");          break; 
		case VDX_MASK_COLOR_OFF25 :         printf("VDX_MASK_COLOR_OFF25");         break; 
		case VDX_MASK_X_POS25 :             printf("VDX_MASK_X_POS25");             break; 
		case VDX_MASK_Y_POS25 :             printf("VDX_MASK_Y_POS25");             break; 
		case VDX_MASK_WIDTH25 :             printf("VDX_MASK_WIDTH25");             break; 
		case VDX_MASK_HEIGHT25 :            printf("VDX_MASK_HEIGHT25");            break; 
		case VDX_MASK_PAN_ANGLE25 :         printf("VDX_MASK_PAN_ANGLE25");         break; 
		case VDX_MASK_TILT_ANGLE25 :        printf("VDX_MASK_TILT_ANGLE25");        break; 
		case VDX_MASK_ZOOM25 :              printf("VDX_MASK_ZOOM25");              break; 
		case VDX_MASK_ON26 :                printf("VDX_MASK_ON26");                break; 
		case VDX_MASK_DISP_ON26 :           printf("VDX_MASK_DISP_ON26");           break; 
		case VDX_MASK_I26 :                 printf("VDX_MASK_I26");                 break; 
		case VDX_MASK_TRANS26 :             printf("VDX_MASK_TRANS26");             break; 
		case VDX_MASK_MOSAIC26 :            printf("VDX_MASK_MOSAIC26");            break; 
		case VDX_MASK_COLOR_ON26 :          printf("VDX_MASK_COLOR_ON26");          break; 
		case VDX_MASK_COLOR_OFF26 :         printf("VDX_MASK_COLOR_OFF26");         break; 
		case VDX_MASK_X_POS26 :             printf("VDX_MASK_X_POS26");             break; 
		case VDX_MASK_Y_POS26 :             printf("VDX_MASK_Y_POS26");             break; 
		case VDX_MASK_WIDTH26 :             printf("VDX_MASK_WIDTH26");             break; 
		case VDX_MASK_HEIGHT26 :            printf("VDX_MASK_HEIGHT26");            break; 
		case VDX_MASK_PAN_ANGLE26 :         printf("VDX_MASK_PAN_ANGLE26");         break; 
		case VDX_MASK_TILT_ANGLE26 :        printf("VDX_MASK_TILT_ANGLE26");        break; 
		case VDX_MASK_ZOOM26 :              printf("VDX_MASK_ZOOM26");              break; 
		case VDX_MASK_ON27 :                printf("VDX_MASK_ON27");                break; 
		case VDX_MASK_DISP_ON27 :           printf("VDX_MASK_DISP_ON27");           break; 
		case VDX_MASK_I27 :                 printf("VDX_MASK_I27");                 break; 
		case VDX_MASK_TRANS27 :             printf("VDX_MASK_TRANS27");             break; 
		case VDX_MASK_MOSAIC27 :            printf("VDX_MASK_MOSAIC27");            break; 
		case VDX_MASK_COLOR_ON27 :          printf("VDX_MASK_COLOR_ON27");          break; 
		case VDX_MASK_COLOR_OFF27 :         printf("VDX_MASK_COLOR_OFF27");         break; 
		case VDX_MASK_X_POS27 :             printf("VDX_MASK_X_POS27");             break; 
		case VDX_MASK_Y_POS27 :             printf("VDX_MASK_Y_POS27");             break; 
		case VDX_MASK_WIDTH27 :             printf("VDX_MASK_WIDTH27");             break; 
		case VDX_MASK_HEIGHT27 :            printf("VDX_MASK_HEIGHT27");            break; 
		case VDX_MASK_PAN_ANGLE27 :         printf("VDX_MASK_PAN_ANGLE27");         break; 
		case VDX_MASK_TILT_ANGLE27 :        printf("VDX_MASK_TILT_ANGLE27");        break; 
		case VDX_MASK_ZOOM27 :              printf("VDX_MASK_ZOOM27");              break; 
		case VDX_MASK_ON28 :                printf("VDX_MASK_ON28");                break; 
		case VDX_MASK_DISP_ON28 :           printf("VDX_MASK_DISP_ON28");           break; 
		case VDX_MASK_I28 :                 printf("VDX_MASK_I28");                 break; 
		case VDX_MASK_TRANS28 :             printf("VDX_MASK_TRANS28");             break; 
		case VDX_MASK_MOSAIC28 :            printf("VDX_MASK_MOSAIC28");            break; 
		case VDX_MASK_COLOR_ON28 :          printf("VDX_MASK_COLOR_ON28");          break; 
		case VDX_MASK_COLOR_OFF28 :         printf("VDX_MASK_COLOR_OFF28");         break; 
		case VDX_MASK_X_POS28 :             printf("VDX_MASK_X_POS28");             break; 
		case VDX_MASK_Y_POS28 :             printf("VDX_MASK_Y_POS28");             break; 
		case VDX_MASK_WIDTH28 :             printf("VDX_MASK_WIDTH28");             break; 
		case VDX_MASK_HEIGHT28 :            printf("VDX_MASK_HEIGHT28");            break; 
		case VDX_MASK_PAN_ANGLE28 :         printf("VDX_MASK_PAN_ANGLE28");         break; 
		case VDX_MASK_TILT_ANGLE28 :        printf("VDX_MASK_TILT_ANGLE28");        break; 
		case VDX_MASK_ZOOM28 :              printf("VDX_MASK_ZOOM28");              break; 
		case VDX_CAM_ID_H :                 printf("VDX_CAM_ID_H");                 break; 
		case VDX_CAM_ID_L :                 printf("VDX_CAM_ID_L");                 break; 
		case VDX_MD_ON :                    printf("VDX_MD_ON");                    break; 
		case VDX_MD_DISP :                  printf("VDX_MD_DISP");                  break; 
		case VDX_MD_FRAME :                 printf("VDX_MD_FRAME");                 break; 
		case VDX_MD_THRS_VAL :              printf("VDX_MD_THRS_VAL");              break; 
		case VDX_MD_INTERVAL_TIME :         printf("VDX_MD_INTERVAL_TIME");         break; 
		case VDX_MD_SRT_H_POS1 :            printf("VDX_MD_SRT_H_POS1");            break; 
		case VDX_MD_SRT_V_POS1 :            printf("VDX_MD_SRT_V_POS1");            break; 
		case VDX_MD_END_H_POS1 :            printf("VDX_MD_END_H_POS1");            break; 
		case VDX_MD_END_V_POS1 :            printf("VDX_MD_END_V_POS1");            break; 
		case VDX_MD_SRT_H_POS2 :            printf("VDX_MD_SRT_H_POS2");            break; 
		case VDX_MD_SRT_V_POS2 :            printf("VDX_MD_SRT_V_POS2");            break; 
		case VDX_MD_STP_H_POS2 :            printf("VDX_MD_STP_H_POS2");            break; 
		case VDX_MD_STP_V_POS2 :            printf("VDX_MD_STP_V_POS2");            break; 
		case VDX_MD_SRT_H_POS3 :            printf("VDX_MD_SRT_H_POS3");            break; 
		case VDX_MD_SRT_V_POS3 :            printf("VDX_MD_SRT_V_POS3");            break; 
		case VDX_MD_STP_H_POS3 :            printf("VDX_MD_STP_H_POS3");            break; 
		case VDX_MD_STP_V_POS3 :            printf("VDX_MD_STP_V_POS3");            break; 
		case VDX_MD_SRT_H_POS4 :            printf("VDX_MD_SRT_H_POS4");            break; 
		case VDX_MD_SRT_V_POS4 :            printf("VDX_MD_SRT_V_POS4");            break; 
		case VDX_MD_STP_H_POS4 :            printf("VDX_MD_STP_H_POS4");            break; 
		case VDX_MD_STP_V_POS4 :            printf("VDX_MD_STP_V_POS4");            break; 
		case VDX_CZP_ON :                   printf("VDX_CZP_ON");                   break; 
		case VDX_CZP_INTERVAL_TIME :        printf("VDX_CZP_INTERVAL_TIME");        break; 
		case VDX_CFP_ON :                   printf("VDX_CFP_ON");                   break; 
		case VDX_CFP_INTERVAL_TIME :        printf("VDX_CFP_INTERVAL_TIME		"); break; 
		case VDX_CE_ON :                    printf("VDX_CE_ON");                    break; 
		case VDX_CE_THRS_VAL :              printf("VDX_CE_THRS_VAL");              break; 
		case VDX_CE_Y_HI :                  printf("VDX_CE_Y_HI");                  break; 
		case VDX_CE_CR_HI :                 printf("VDX_CE_CR_HI");                 break; 
		case VDX_CE_CB_HI :                 printf("VDX_CE_CB_HI");                 break; 
		case VDX_CE_Y_LI :                  printf("VDX_CE_Y_LI");                  break; 
		case VDX_CE_CR_LI :                 printf("VDX_CE_CR_LI");                 break; 
		case VDX_CE_CB_LI :                 printf("VDX_CE_CB_LI");                 break; 
		case VDX_CS_LEVEL :                 printf("VDX_CS_LEVEL");                 break; 
		case VDX_CS_SET_VAL :               printf("VDX_CS_SET_VAL");               break; 
		case VDX_COLOR_GAIN :               printf("VDX_COLOR_GAIN");               break; 
		case VDX_COLOR_HUE :                printf("VDX_COLOR_HUE");                break; 
		case VDX_GAM_OFFSET :               printf("VDX_GAM_OFFSET");               break; 
		case VDX_GAM_OFFSET_S :             printf("VDX_GAM_OFFSET_S");             break; 
		case VDX_EX_EXPCOMP_RESET :         printf("VDX_EX_EXPCOMP_RESET");         break; 
		case VDX_EX_EXPCOMP_DIRECT :        printf("VDX_EX_EXPCOMP_DIRECT");        break; 
		case VDX_EX_EXPAP_RESET :           printf("VDX_EX_EXPAP_RESET");           break; 
		case VDX_EX_EXPAP_DIRECT :          printf("VDX_EX_EXPAP_DIRECT");          break; 
		case VDX_EX_AICR_ON2OFF :           printf("VDX_EX_AICR_ON2OFF");           break; 
		case VDX_EX_AICR_OFF2ON :           printf("VDX_EX_AICR_OFF2ON");           break; 
		case VDX_EX_COLOR_GAIN :            printf("VDX_EX_COLOR_GAIN");            break; 
		case VDX_EX_COLOR_HUE :             printf("VDX_EX_COLOR_HUE");             break; 
		case VDX_ZOOM_POS01 :               printf("VDX_ZOOM_POS01");               break; 
		case VDX_DZOOM_ON01 :               printf("VDX_DZOOM_ON01");               break; 
		case VDX_F_MODE01 :                 printf("VDX_F_MODE01");                 break; 
		case VDX_AF_MODE01 :                printf("VDX_AF_MODE01");                break; 
		case VDX_COMP_ON01 :                printf("VDX_COMP_ON01");                break; 
		case VDX_BLC_ON01 :                 printf("VDX_BLC_ON01");                 break; 
		case VDX_ASS_ON01 :                 printf("VDX_ASS_ON01");                 break; 
		case VDX_FOCUS_POS01 :              printf("VDX_FOCUS_POS01");              break; 
		case VDX_SHUTTER_STEP01 :           printf("VDX_SHUTTER_STEP01");           break; 
		case VDX_BRIGHT_STEP01 :            printf("VDX_BRIGHT_STEP01");            break; 
		case VDX_IRIS_STEP01 :              printf("VDX_IRIS_STEP01");              break; 
		case VDX_GAIN_STEP01 :              printf("VDX_GAIN_STEP01");              break; 
		case VDX_EXP_COMP_VAL01 :           printf("VDX_EXP_COMP_VAL01");           break; 
		case VDX_WB_MODE01 :                printf("VDX_WB_MODE01");                break; 
		case VDX_ICR_ON01 :                 printf("VDX_ICR_ON01");                 break; 
		case VDX_WD_MODE01 :                printf("VDX_WD_MODE01");                break; 
		case VDX_DEFOG_ON01 :               printf("VDX_DEFOG_ON01");               break; 
		case VDX_R_GAIN01 :                 printf("VDX_R_GAIN01");                 break; 
		case VDX_B_GAIN01 :                 printf("VDX_B_GAIN01");                 break; 
		case VDX_APER_GAIN01 :              printf("VDX_APER_GAIN01");              break; 
		case VDX_WD_BRT_L01 :               printf("VDX_WD_BRT_L01");               break; 
		case VDX_WD_BRT_COMP01 :            printf("VDX_WD_BRT_COMP01");            break; 
		case VDX_WD_COMP_L01 :              printf("VDX_WD_COMP_L01");              break; 
		case VDX_AE_MODE01 :                printf("VDX_AE_MODE01");                break; 
		case VDX_ZOOM_POS02 :               printf("VDX_ZOOM_POS02");               break; 
		case VDX_DZOOM_ON02 :               printf("VDX_DZOOM_ON02");               break; 
		case VDX_F_MODE02 :                 printf("VDX_F_MODE02");                 break; 
		case VDX_AF_MODE02 :                printf("VDX_AF_MODE02");                break; 
		case VDX_COMP_ON02 :                printf("VDX_COMP_ON02");                break; 
		case VDX_BLC_ON02 :                 printf("VDX_BLC_ON02");                 break; 
		case VDX_ASS_ON02 :                 printf("VDX_ASS_ON02");                 break; 
		case VDX_FOCUS_POS02 :              printf("VDX_FOCUS_POS02");              break; 
		case VDX_SHUTTER_STEP02 :           printf("VDX_SHUTTER_STEP02");           break; 
		case VDX_BRIGHT_STEP02 :            printf("VDX_BRIGHT_STEP02");            break; 
		case VDX_IRIS_STEP02 :              printf("VDX_IRIS_STEP02");              break; 
		case VDX_GAIN_STEP02 :              printf("VDX_GAIN_STEP02");              break; 
		case VDX_EXP_COMP_VAL02 :           printf("VDX_EXP_COMP_VAL02");           break; 
		case VDX_WB_MODE02 :                printf("VDX_WB_MODE02");                break; 
		case VDX_ICR_ON02 :                 printf("VDX_ICR_ON02");                 break; 
		case VDX_WD_MODE02 :                printf("VDX_WD_MODE02");                break; 
		case VDX_DEFOG_ON02 :               printf("VDX_DEFOG_ON02");               break; 
		case VDX_R_GAIN02 :                 printf("VDX_R_GAIN02");                 break; 
		case VDX_B_GAIN02 :                 printf("VDX_B_GAIN02");                 break; 
		case VDX_APER_GAIN02 :              printf("VDX_APER_GAIN02");              break; 
		case VDX_WD_BRT_L02 :               printf("VDX_WD_BRT_L02");               break; 
		case VDX_WD_BRT_COMP02 :            printf("VDX_WD_BRT_COMP02");            break; 
		case VDX_WD_COMP_L02 :              printf("VDX_WD_COMP_L02");              break; 
		case VDX_AE_MODE02 :                printf("VDX_AE_MODE02");                break; 
		case VDX_ZOOM_POS03 :               printf("VDX_ZOOM_POS03");               break; 
		case VDX_DZOOM_ON03 :               printf("VDX_DZOOM_ON03");               break; 
		case VDX_F_MODE03 :                 printf("VDX_F_MODE03");                 break; 
		case VDX_AF_MODE03 :                printf("VDX_AF_MODE03");                break; 
		case VDX_COMP_ON03 :                printf("VDX_COMP_ON03");                break; 
		case VDX_BLC_ON03 :                 printf("VDX_BLC_ON03");                 break; 
		case VDX_ASS_ON03 :                 printf("VDX_ASS_ON03");                 break; 
		case VDX_FOCUS_POS03 :              printf("VDX_FOCUS_POS03");              break; 
		case VDX_SHUTTER_STEP03 :           printf("VDX_SHUTTER_STEP03");           break; 
		case VDX_BRIGHT_STEP03 :            printf("VDX_BRIGHT_STEP03");            break; 
		case VDX_IRIS_STEP03 :              printf("VDX_IRIS_STEP03");              break; 
		case VDX_GAIN_STEP03 :              printf("VDX_GAIN_STEP03");              break; 
		case VDX_EXP_COMP_VAL03 :           printf("VDX_EXP_COMP_VAL03");           break; 
		case VDX_WB_MODE03 :                printf("VDX_WB_MODE03");                break; 
		case VDX_ICR_ON03 :                 printf("VDX_ICR_ON03");                 break; 
		case VDX_WD_MODE03 :                printf("VDX_WD_MODE03");                break; 
		case VDX_DEFOG_ON03 :               printf("VDX_DEFOG_ON03");               break; 
		case VDX_R_GAIN03 :                 printf("VDX_R_GAIN03");                 break; 
		case VDX_B_GAIN03 :                 printf("VDX_B_GAIN03");                 break; 
		case VDX_APER_GAIN03 :              printf("VDX_APER_GAIN03");              break; 
		case VDX_WD_BRT_L03 :               printf("VDX_WD_BRT_L03");               break; 
		case VDX_WD_BRT_COMP03 :            printf("VDX_WD_BRT_COMP03");            break; 
		case VDX_WD_COMP_L03 :              printf("VDX_WD_COMP_L03");              break; 
		case VDX_AE_MODE03 :                printf("VDX_AE_MODE03");                break; 
		case VDX_ZOOM_POS04 :               printf("VDX_ZOOM_POS04");               break; 
		case VDX_DZOOM_ON04 :               printf("VDX_DZOOM_ON04");               break; 
		case VDX_F_MODE04 :                 printf("VDX_F_MODE04");                 break; 
		case VDX_AF_MODE04 :                printf("VDX_AF_MODE04");                break; 
		case VDX_COMP_ON04 :                printf("VDX_COMP_ON04");                break; 
		case VDX_BLC_ON04 :                 printf("VDX_BLC_ON04");                 break; 
		case VDX_ASS_ON04 :                 printf("VDX_ASS_ON04");                 break; 
		case VDX_FOCUS_POS04 :              printf("VDX_FOCUS_POS04");              break; 
		case VDX_SHUTTER_STEP04 :           printf("VDX_SHUTTER_STEP04");           break; 
		case VDX_BRIGHT_STEP04 :            printf("VDX_BRIGHT_STEP04");            break; 
		case VDX_IRIS_STEP04 :              printf("VDX_IRIS_STEP04");              break; 
		case VDX_GAIN_STEP04 :              printf("VDX_GAIN_STEP04");              break; 
		case VDX_EXP_COMP_VAL04 :           printf("VDX_EXP_COMP_VAL04");           break; 
		case VDX_WB_MODE04 :                printf("VDX_WB_MODE04");                break; 
		case VDX_ICR_ON04 :                 printf("VDX_ICR_ON04");                 break; 
		case VDX_WD_MODE04 :                printf("VDX_WD_MODE04");                break; 
		case VDX_DEFOG_ON04 :               printf("VDX_DEFOG_ON04");               break; 
		case VDX_R_GAIN04 :                 printf("VDX_R_GAIN04");                 break; 
		case VDX_B_GAIN04 :                 printf("VDX_B_GAIN04");                 break; 
		case VDX_APER_GAIN04 :              printf("VDX_APER_GAIN04");              break; 
		case VDX_WD_BRT_L04 :               printf("VDX_WD_BRT_L04");               break; 
		case VDX_WD_BRT_COMP04 :            printf("VDX_WD_BRT_COMP04");            break; 
		case VDX_WD_COMP_L04 :              printf("VDX_WD_COMP_L04");              break; 
		case VDX_AE_MODE04 :                printf("VDX_AE_MODE04");                break; 
		case VDX_ZOOM_POS05 :               printf("VDX_ZOOM_POS05");               break; 
		case VDX_DZOOM_ON05 :               printf("VDX_DZOOM_ON05");               break; 
		case VDX_F_MODE05 :                 printf("VDX_F_MODE05");                 break; 
		case VDX_AF_MODE05 :                printf("VDX_AF_MODE05");                break; 
		case VDX_COMP_ON05 :                printf("VDX_COMP_ON05");                break; 
		case VDX_BLC_ON05 :                 printf("VDX_BLC_ON05");                 break; 
		case VDX_ASS_ON05 :                 printf("VDX_ASS_ON05");                 break; 
		case VDX_FOCUS_POS05 :              printf("VDX_FOCUS_POS05");              break; 
		case VDX_SHUTTER_STEP05 :           printf("VDX_SHUTTER_STEP05");           break; 
		case VDX_BRIGHT_STEP05 :            printf("VDX_BRIGHT_STEP05");            break; 
		case VDX_IRIS_STEP05 :              printf("VDX_IRIS_STEP05");              break; 
		case VDX_GAIN_STEP05 :              printf("VDX_GAIN_STEP05");              break; 
		case VDX_EXP_COMP_VAL05 :           printf("VDX_EXP_COMP_VAL05");           break; 
		case VDX_WB_MODE05 :                printf("VDX_WB_MODE05");                break; 
		case VDX_ICR_ON05 :                 printf("VDX_ICR_ON05");                 break; 
		case VDX_WD_MODE05 :                printf("VDX_WD_MODE05");                break; 
		case VDX_DEFOG_ON05 :               printf("VDX_DEFOG_ON05");               break; 
		case VDX_R_GAIN05 :                 printf("VDX_R_GAIN05");                 break; 
		case VDX_B_GAIN05 :                 printf("VDX_B_GAIN05");                 break; 
		case VDX_APER_GAIN05 :              printf("VDX_APER_GAIN05");              break; 
		case VDX_WD_BRT_L05 :               printf("VDX_WD_BRT_L05");               break; 
		case VDX_WD_BRT_COMP05 :            printf("VDX_WD_BRT_COMP05");            break; 
		case VDX_WD_COMP_L05 :              printf("VDX_WD_COMP_L05");              break; 
		case VDX_AE_MODE05 :                printf("VDX_AE_MODE05");                break; 
		case VDX_ZOOM_POS06 :               printf("VDX_ZOOM_POS06");               break; 
		case VDX_DZOOM_ON06 :               printf("VDX_DZOOM_ON06");               break; 
		case VDX_F_MODE06 :                 printf("VDX_F_MODE06");                 break; 
		case VDX_AF_MODE06 :                printf("VDX_AF_MODE06");                break; 
		case VDX_COMP_ON06 :                printf("VDX_COMP_ON06");                break; 
		case VDX_BLC_ON06 :                 printf("VDX_BLC_ON06");                 break; 
		case VDX_ASS_ON06 :                 printf("VDX_ASS_ON06");                 break; 
		case VDX_FOCUS_POS06 :              printf("VDX_FOCUS_POS06");              break; 
		case VDX_SHUTTER_STEP06 :           printf("VDX_SHUTTER_STEP06");           break; 
		case VDX_BRIGHT_STEP06 :            printf("VDX_BRIGHT_STEP06");            break; 
		case VDX_IRIS_STEP06 :              printf("VDX_IRIS_STEP06");              break; 
		case VDX_GAIN_STEP06 :              printf("VDX_GAIN_STEP06");              break; 
		case VDX_EXP_COMP_VAL06 :           printf("VDX_EXP_COMP_VAL06");           break; 
		case VDX_WB_MODE06 :                printf("VDX_WB_MODE06");                break; 
		case VDX_ICR_ON06 :                 printf("VDX_ICR_ON06");                 break; 
		case VDX_WD_MODE06 :                printf("VDX_WD_MODE06");                break; 
		case VDX_DEFOG_ON06 :               printf("VDX_DEFOG_ON06");               break; 
		case VDX_R_GAIN06 :                 printf("VDX_R_GAIN06");                 break; 
		case VDX_B_GAIN06 :                 printf("VDX_B_GAIN06");                 break; 
		case VDX_APER_GAIN06 :              printf("VDX_APER_GAIN06");              break; 
		case VDX_WD_BRT_L06 :               printf("VDX_WD_BRT_L06");               break; 
		case VDX_WD_BRT_COMP06 :            printf("VDX_WD_BRT_COMP06");            break; 
		case VDX_WD_COMP_L06 :              printf("VDX_WD_COMP_L06");              break; 
		case VDX_AE_MODE06 :                printf("VDX_AE_MODE06");                break; 
		case VDX_ZOOM_POS07 :               printf("VDX_ZOOM_POS07");               break; 
		case VDX_DZOOM_ON07 :               printf("VDX_DZOOM_ON07");               break; 
		case VDX_F_MODE07 :                 printf("VDX_F_MODE07");                 break; 
		case VDX_AF_MODE07 :                printf("VDX_AF_MODE07");                break; 
		case VDX_COMP_ON07 :                printf("VDX_COMP_ON07");                break; 
		case VDX_BLC_ON07 :                 printf("VDX_BLC_ON07");                 break; 
		case VDX_ASS_ON07 :                 printf("VDX_ASS_ON07");                 break; 
		case VDX_FOCUS_POS07 :              printf("VDX_FOCUS_POS07");              break; 
		case VDX_SHUTTER_STEP07 :           printf("VDX_SHUTTER_STEP07");           break; 
		case VDX_BRIGHT_STEP07 :            printf("VDX_BRIGHT_STEP07");            break; 
		case VDX_IRIS_STEP07 :              printf("VDX_IRIS_STEP07");              break; 
		case VDX_GAIN_STEP07 :              printf("VDX_GAIN_STEP07");              break; 
		case VDX_EXP_COMP_VAL07 :           printf("VDX_EXP_COMP_VAL07");           break; 
		case VDX_WB_MODE07 :                printf("VDX_WB_MODE07");                break; 
		case VDX_ICR_ON07 :                 printf("VDX_ICR_ON07");                 break; 
		case VDX_WD_MODE07 :                printf("VDX_WD_MODE07");                break; 
		case VDX_DEFOG_ON07 :               printf("VDX_DEFOG_ON07");               break; 
		case VDX_R_GAIN07 :                 printf("VDX_R_GAIN07");                 break; 
		case VDX_B_GAIN07 :                 printf("VDX_B_GAIN07");                 break; 
		case VDX_APER_GAIN07 :              printf("VDX_APER_GAIN07");              break; 
		case VDX_WD_BRT_L07 :               printf("VDX_WD_BRT_L07");               break; 
		case VDX_WD_BRT_COMP07 :            printf("VDX_WD_BRT_COMP07");            break; 
		case VDX_WD_COMP_L07 :              printf("VDX_WD_COMP_L07");              break; 
		case VDX_AE_MODE07 :                printf("VDX_AE_MODE07");                break; 
		case VDX_ZOOM_POS08 :               printf("VDX_ZOOM_POS08");               break; 
		case VDX_DZOOM_ON08 :               printf("VDX_DZOOM_ON08");               break; 
		case VDX_F_MODE08 :                 printf("VDX_F_MODE08");                 break; 
		case VDX_AF_MODE08 :                printf("VDX_AF_MODE08");                break; 
		case VDX_COMP_ON08 :                printf("VDX_COMP_ON08");                break; 
		case VDX_BLC_ON08 :                 printf("VDX_BLC_ON08");                 break; 
		case VDX_ASS_ON08 :                 printf("VDX_ASS_ON08");                 break; 
		case VDX_FOCUS_POS08 :              printf("VDX_FOCUS_POS08");              break; 
		case VDX_SHUTTER_STEP08 :           printf("VDX_SHUTTER_STEP08");           break; 
		case VDX_BRIGHT_STEP08 :            printf("VDX_BRIGHT_STEP08");            break; 
		case VDX_IRIS_STEP08 :              printf("VDX_IRIS_STEP08");              break; 
		case VDX_GAIN_STEP08 :              printf("VDX_GAIN_STEP08");              break; 
		case VDX_EXP_COMP_VAL08 :           printf("VDX_EXP_COMP_VAL08");           break; 
		case VDX_WB_MODE08 :                printf("VDX_WB_MODE08");                break; 
		case VDX_ICR_ON08 :                 printf("VDX_ICR_ON08");                 break; 
		case VDX_WD_MODE08 :                printf("VDX_WD_MODE08");                break; 
		case VDX_DEFOG_ON08 :               printf("VDX_DEFOG_ON08");               break; 
		case VDX_R_GAIN08 :                 printf("VDX_R_GAIN08");                 break; 
		case VDX_B_GAIN08 :                 printf("VDX_B_GAIN08");                 break; 
		case VDX_APER_GAIN08 :              printf("VDX_APER_GAIN08");              break; 
		case VDX_WD_BRT_L08 :               printf("VDX_WD_BRT_L08");               break; 
		case VDX_WD_BRT_COMP08 :            printf("VDX_WD_BRT_COMP08");            break; 
		case VDX_WD_COMP_L08 :              printf("VDX_WD_COMP_L08");              break; 
		case VDX_AE_MODE08 :                printf("VDX_AE_MODE08");                break; 
		case VDX_ZOOM_POS09 :               printf("VDX_ZOOM_POS09");               break; 
		case VDX_DZOOM_ON09 :               printf("VDX_DZOOM_ON09");               break; 
		case VDX_F_MODE09 :                 printf("VDX_F_MODE09");                 break; 
		case VDX_AF_MODE09 :                printf("VDX_AF_MODE09");                break; 
		case VDX_COMP_ON09 :                printf("VDX_COMP_ON09");                break; 
		case VDX_BLC_ON09 :                 printf("VDX_BLC_ON09");                 break; 
		case VDX_ASS_ON09 :                 printf("VDX_ASS_ON09");                 break; 
		case VDX_FOCUS_POS09 :              printf("VDX_FOCUS_POS09");              break; 
		case VDX_SHUTTER_STEP09 :           printf("VDX_SHUTTER_STEP09");           break; 
		case VDX_BRIGHT_STEP09 :            printf("VDX_BRIGHT_STEP09");            break; 
		case VDX_IRIS_STEP09 :              printf("VDX_IRIS_STEP09");              break; 
		case VDX_GAIN_STEP09 :              printf("VDX_GAIN_STEP09");              break; 
		case VDX_EXP_COMP_VAL09 :           printf("VDX_EXP_COMP_VAL09");           break; 
		case VDX_WB_MODE09 :                printf("VDX_WB_MODE09");                break; 
		case VDX_ICR_ON09 :                 printf("VDX_ICR_ON09");                 break; 
		case VDX_WD_MODE09 :                printf("VDX_WD_MODE09");                break; 
		case VDX_DEFOG_ON09 :               printf("VDX_DEFOG_ON09");               break; 
		case VDX_R_GAIN09 :                 printf("VDX_R_GAIN09");                 break; 
		case VDX_B_GAIN09 :                 printf("VDX_B_GAIN09");                 break; 
		case VDX_APER_GAIN09 :              printf("VDX_APER_GAIN09");              break; 
		case VDX_WD_BRT_L09 :               printf("VDX_WD_BRT_L09");               break; 
		case VDX_WD_BRT_COMP09 :            printf("VDX_WD_BRT_COMP09");            break; 
		case VDX_WD_COMP_L09 :              printf("VDX_WD_COMP_L09");              break; 
		case VDX_AE_MODE09 :                printf("VDX_AE_MODE09");                break; 
		case VDX_ZOOM_POS10 :               printf("VDX_ZOOM_POS10");               break; 
		case VDX_DZOOM_ON10 :               printf("VDX_DZOOM_ON10");               break; 
		case VDX_F_MODE10 :                 printf("VDX_F_MODE10");                 break; 
		case VDX_AF_MODE10 :                printf("VDX_AF_MODE10");                break; 
		case VDX_COMP_ON10 :                printf("VDX_COMP_ON10");                break; 
		case VDX_BLC_ON10 :                 printf("VDX_BLC_ON10");                 break; 
		case VDX_ASS_ON10 :                 printf("VDX_ASS_ON10");                 break; 
		case VDX_FOCUS_POS10 :              printf("VDX_FOCUS_POS10");              break; 
		case VDX_SHUTTER_STEP10 :           printf("VDX_SHUTTER_STEP10");           break; 
		case VDX_BRIGHT_STEP10 :            printf("VDX_BRIGHT_STEP10");            break; 
		case VDX_IRIS_STEP10 :              printf("VDX_IRIS_STEP10");              break; 
		case VDX_GAIN_STEP10 :              printf("VDX_GAIN_STEP10");              break; 
		case VDX_EXP_COMP_VAL10 :           printf("VDX_EXP_COMP_VAL10");           break; 
		case VDX_WB_MODE10 :                printf("VDX_WB_MODE10");                break; 
		case VDX_ICR_ON10 :                 printf("VDX_ICR_ON10");                 break; 
		case VDX_WD_MODE10 :                printf("VDX_WD_MODE10");                break; 
		case VDX_DEFOG_ON10 :               printf("VDX_DEFOG_ON10");               break; 
		case VDX_R_GAIN10 :                 printf("VDX_R_GAIN10");                 break; 
		case VDX_B_GAIN10 :                 printf("VDX_B_GAIN10");                 break; 
		case VDX_APER_GAIN10 :              printf("VDX_APER_GAIN10");              break; 
		case VDX_WD_BRT_L10 :               printf("VDX_WD_BRT_L10");               break; 
		case VDX_WD_BRT_COMP10 :            printf("VDX_WD_BRT_COMP10");            break; 
		case VDX_WD_COMP_L10 :              printf("VDX_WD_COMP_L10");              break; 
		case VDX_AE_MODE10 :                printf("VDX_AE_MODE10");                break; 
		case VDX_ZOOM_POS11 :               printf("VDX_ZOOM_POS11");               break; 
		case VDX_DZOOM_ON11 :               printf("VDX_DZOOM_ON11");               break; 
		case VDX_F_MODE11 :                 printf("VDX_F_MODE11");                 break; 
		case VDX_AF_MODE11 :                printf("VDX_AF_MODE11");                break; 
		case VDX_COMP_ON11 :                printf("VDX_COMP_ON11");                break; 
		case VDX_BLC_ON11 :                 printf("VDX_BLC_ON11");                 break; 
		case VDX_ASS_ON11 :                 printf("VDX_ASS_ON11");                 break; 
		case VDX_FOCUS_POS11 :              printf("VDX_FOCUS_POS11");              break; 
		case VDX_SHUTTER_STEP11 :           printf("VDX_SHUTTER_STEP11");           break; 
		case VDX_BRIGHT_STEP11 :            printf("VDX_BRIGHT_STEP11");            break; 
		case VDX_IRIS_STEP11 :              printf("VDX_IRIS_STEP11");              break; 
		case VDX_GAIN_STEP11 :              printf("VDX_GAIN_STEP11");              break; 
		case VDX_EXP_COMP_VAL11 :           printf("VDX_EXP_COMP_VAL11");           break; 
		case VDX_WB_MODE11 :                printf("VDX_WB_MODE11");                break; 
		case VDX_ICR_ON11 :                 printf("VDX_ICR_ON11");                 break; 
		case VDX_WD_MODE11 :                printf("VDX_WD_MODE11");                break; 
		case VDX_DEFOG_ON11 :               printf("VDX_DEFOG_ON11");               break; 
		case VDX_R_GAIN11 :                 printf("VDX_R_GAIN11");                 break; 
		case VDX_B_GAIN11 :                 printf("VDX_B_GAIN11");                 break; 
		case VDX_APER_GAIN11 :              printf("VDX_APER_GAIN11");              break; 
		case VDX_WD_BRT_L11 :               printf("VDX_WD_BRT_L11");               break; 
		case VDX_WD_BRT_COMP11 :            printf("VDX_WD_BRT_COMP11");            break; 
		case VDX_WD_COMP_L11 :              printf("VDX_WD_COMP_L11");              break; 
		case VDX_AE_MODE11 :                printf("VDX_AE_MODE11");                break; 
		case VDX_ZOOM_POS12 :               printf("VDX_ZOOM_POS12");               break; 
		case VDX_DZOOM_ON12 :               printf("VDX_DZOOM_ON12");               break; 
		case VDX_F_MODE12 :                 printf("VDX_F_MODE12");                 break; 
		case VDX_AF_MODE12 :                printf("VDX_AF_MODE12");                break; 
		case VDX_COMP_ON12 :                printf("VDX_COMP_ON12");                break; 
		case VDX_BLC_ON12 :                 printf("VDX_BLC_ON12");                 break; 
		case VDX_ASS_ON12 :                 printf("VDX_ASS_ON12");                 break; 
		case VDX_FOCUS_POS12 :              printf("VDX_FOCUS_POS12");              break; 
		case VDX_SHUTTER_STEP12 :           printf("VDX_SHUTTER_STEP12");           break; 
		case VDX_BRIGHT_STEP12 :            printf("VDX_BRIGHT_STEP12");            break; 
		case VDX_IRIS_STEP12 :              printf("VDX_IRIS_STEP12");              break; 
		case VDX_GAIN_STEP12 :              printf("VDX_GAIN_STEP12");              break; 
		case VDX_EXP_COMP_VAL12 :           printf("VDX_EXP_COMP_VAL12");           break; 
		case VDX_WB_MODE12 :                printf("VDX_WB_MODE12");                break; 
		case VDX_ICR_ON12 :                 printf("VDX_ICR_ON12");                 break; 
		case VDX_WD_MODE12 :                printf("VDX_WD_MODE12");                break; 
		case VDX_DEFOG_ON12 :               printf("VDX_DEFOG_ON12");               break; 
		case VDX_R_GAIN12 :                 printf("VDX_R_GAIN12");                 break; 
		case VDX_B_GAIN12 :                 printf("VDX_B_GAIN12");                 break; 
		case VDX_APER_GAIN12 :              printf("VDX_APER_GAIN12");              break; 
		case VDX_WD_BRT_L12 :               printf("VDX_WD_BRT_L12");               break; 
		case VDX_WD_BRT_COMP12 :            printf("VDX_WD_BRT_COMP12");            break; 
		case VDX_WD_COMP_L12 :              printf("VDX_WD_COMP_L12");              break; 
		case VDX_AE_MODE12 :                printf("VDX_AE_MODE12");                break; 
		case VDX_ZOOM_POS13 :               printf("VDX_ZOOM_POS13");               break; 
		case VDX_DZOOM_ON13 :               printf("VDX_DZOOM_ON13");               break; 
		case VDX_F_MODE13 :                 printf("VDX_F_MODE13");                 break; 
		case VDX_AF_MODE13 :                printf("VDX_AF_MODE13");                break; 
		case VDX_COMP_ON13 :                printf("VDX_COMP_ON13");                break; 
		case VDX_BLC_ON13 :                 printf("VDX_BLC_ON13");                 break; 
		case VDX_ASS_ON13 :                 printf("VDX_ASS_ON13");                 break; 
		case VDX_FOCUS_POS13 :              printf("VDX_FOCUS_POS13");              break; 
		case VDX_SHUTTER_STEP13 :           printf("VDX_SHUTTER_STEP13");           break; 
		case VDX_BRIGHT_STEP13 :            printf("VDX_BRIGHT_STEP13");            break; 
		case VDX_IRIS_STEP13 :              printf("VDX_IRIS_STEP13");              break; 
		case VDX_GAIN_STEP13 :              printf("VDX_GAIN_STEP13");              break; 
		case VDX_EXP_COMP_VAL13 :           printf("VDX_EXP_COMP_VAL13");           break; 
		case VDX_WB_MODE13 :                printf("VDX_WB_MODE13");                break; 
		case VDX_ICR_ON13 :                 printf("VDX_ICR_ON13");                 break; 
		case VDX_WD_MODE13 :                printf("VDX_WD_MODE13");                break; 
		case VDX_DEFOG_ON13 :               printf("VDX_DEFOG_ON13");               break; 
		case VDX_R_GAIN13 :                 printf("VDX_R_GAIN13");                 break; 
		case VDX_B_GAIN13 :                 printf("VDX_B_GAIN13");                 break; 
		case VDX_APER_GAIN13 :              printf("VDX_APER_GAIN13");              break; 
		case VDX_WD_BRT_L13 :               printf("VDX_WD_BRT_L13");               break; 
		case VDX_WD_BRT_COMP13 :            printf("VDX_WD_BRT_COMP13");            break; 
		case VDX_WD_COMP_L13 :              printf("VDX_WD_COMP_L13");              break; 
		case VDX_AE_MODE13 :                printf("VDX_AE_MODE13");                break; 
		case VDX_ZOOM_POS14 :               printf("VDX_ZOOM_POS14");               break; 
		case VDX_DZOOM_ON14 :               printf("VDX_DZOOM_ON14");               break; 
		case VDX_F_MODE14 :                 printf("VDX_F_MODE14");                 break; 
		case VDX_AF_MODE14 :                printf("VDX_AF_MODE14");                break; 
		case VDX_COMP_ON14 :                printf("VDX_COMP_ON14");                break; 
		case VDX_BLC_ON14 :                 printf("VDX_BLC_ON14");                 break; 
		case VDX_ASS_ON14 :                 printf("VDX_ASS_ON14");                 break; 
		case VDX_FOCUS_POS14 :              printf("VDX_FOCUS_POS14");              break; 
		case VDX_SHUTTER_STEP14 :           printf("VDX_SHUTTER_STEP14");           break; 
		case VDX_BRIGHT_STEP14 :            printf("VDX_BRIGHT_STEP14");            break; 
		case VDX_IRIS_STEP14 :              printf("VDX_IRIS_STEP14");              break; 
		case VDX_GAIN_STEP14 :              printf("VDX_GAIN_STEP14");              break; 
		case VDX_EXP_COMP_VAL14 :           printf("VDX_EXP_COMP_VAL14");           break; 
		case VDX_WB_MODE14 :                printf("VDX_WB_MODE14");                break; 
		case VDX_ICR_ON14 :                 printf("VDX_ICR_ON14");                 break; 
		case VDX_WD_MODE14 :                printf("VDX_WD_MODE14");                break; 
		case VDX_DEFOG_ON14 :               printf("VDX_DEFOG_ON14");               break; 
		case VDX_R_GAIN14 :                 printf("VDX_R_GAIN14");                 break; 
		case VDX_B_GAIN14 :                 printf("VDX_B_GAIN14");                 break; 
		case VDX_APER_GAIN14 :              printf("VDX_APER_GAIN14");              break; 
		case VDX_WD_BRT_L14 :               printf("VDX_WD_BRT_L14");               break; 
		case VDX_WD_BRT_COMP14 :            printf("VDX_WD_BRT_COMP14");            break; 
		case VDX_WD_COMP_L14 :              printf("VDX_WD_COMP_L14");              break; 
		case VDX_AE_MODE14 :                printf("VDX_AE_MODE14");                break; 
		case VDX_ZOOM_POS15 :               printf("VDX_ZOOM_POS15");               break; 
		case VDX_DZOOM_ON15 :               printf("VDX_DZOOM_ON15");               break; 
		case VDX_F_MODE15 :                 printf("VDX_F_MODE15");                 break; 
		case VDX_AF_MODE15 :                printf("VDX_AF_MODE15");                break; 
		case VDX_COMP_ON15 :                printf("VDX_COMP_ON15");                break; 
		case VDX_BLC_ON15 :                 printf("VDX_BLC_ON15");                 break; 
		case VDX_ASS_ON15 :                 printf("VDX_ASS_ON15");                 break; 
		case VDX_FOCUS_POS15 :              printf("VDX_FOCUS_POS15");              break; 
		case VDX_SHUTTER_STEP15 :           printf("VDX_SHUTTER_STEP15");           break; 
		case VDX_BRIGHT_STEP15 :            printf("VDX_BRIGHT_STEP15");            break; 
		case VDX_IRIS_STEP15 :              printf("VDX_IRIS_STEP15");              break; 
		case VDX_GAIN_STEP15 :              printf("VDX_GAIN_STEP15");              break; 
		case VDX_EXP_COMP_VAL15 :           printf("VDX_EXP_COMP_VAL15");           break; 
		case VDX_WB_MODE15 :                printf("VDX_WB_MODE15");                break; 
		case VDX_ICR_ON15 :                 printf("VDX_ICR_ON15");                 break; 
		case VDX_WD_MODE15 :                printf("VDX_WD_MODE15");                break; 
		case VDX_DEFOG_ON15 :               printf("VDX_DEFOG_ON15");               break; 
		case VDX_R_GAIN15 :                 printf("VDX_R_GAIN15");                 break; 
		case VDX_B_GAIN15 :                 printf("VDX_B_GAIN15");                 break; 
		case VDX_APER_GAIN15 :              printf("VDX_APER_GAIN15");              break; 
		case VDX_WD_BRT_L15 :               printf("VDX_WD_BRT_L15");               break; 
		case VDX_WD_BRT_COMP15 :            printf("VDX_WD_BRT_COMP15");            break; 
		case VDX_WD_COMP_L15 :              printf("VDX_WD_COMP_L15");              break; 
		case VDX_AE_MODE15 :                printf("VDX_AE_MODE15");                break; 
		case VDX_ZOOM_POS16 :               printf("VDX_ZOOM_POS16");               break; 
		case VDX_DZOOM_ON16 :               printf("VDX_DZOOM_ON16");               break; 
		case VDX_F_MODE16 :                 printf("VDX_F_MODE16");                 break; 
		case VDX_AF_MODE16 :                printf("VDX_AF_MODE16");                break; 
		case VDX_COMP_ON16 :                printf("VDX_COMP_ON16");                break; 
		case VDX_BLC_ON16 :                 printf("VDX_BLC_ON16");                 break; 
		case VDX_ASS_ON16 :                 printf("VDX_ASS_ON16");                 break; 
		case VDX_FOCUS_POS16 :              printf("VDX_FOCUS_POS16");              break; 
		case VDX_SHUTTER_STEP16 :           printf("VDX_SHUTTER_STEP16");           break; 
		case VDX_BRIGHT_STEP16 :            printf("VDX_BRIGHT_STEP16");            break; 
		case VDX_IRIS_STEP16 :              printf("VDX_IRIS_STEP16");              break; 
		case VDX_GAIN_STEP16 :              printf("VDX_GAIN_STEP16");              break; 
		case VDX_EXP_COMP_VAL16 :           printf("VDX_EXP_COMP_VAL16");           break; 
		case VDX_WB_MODE16 :                printf("VDX_WB_MODE16");                break; 
		case VDX_ICR_ON16 :                 printf("VDX_ICR_ON16");                 break; 
		case VDX_WD_MODE16 :                printf("VDX_WD_MODE16");                break; 
		case VDX_DEFOG_ON16 :               printf("VDX_DEFOG_ON16");               break; 
		case VDX_R_GAIN16 :                 printf("VDX_R_GAIN16");                 break; 
		case VDX_B_GAIN16 :                 printf("VDX_B_GAIN16");                 break; 
		case VDX_APER_GAIN16 :              printf("VDX_APER_GAIN16");              break; 
		case VDX_WD_BRT_L16 :               printf("VDX_WD_BRT_L16");               break; 
		case VDX_WD_BRT_COMP16 :            printf("VDX_WD_BRT_COMP16");            break; 
		case VDX_WD_COMP_L16 :              printf("VDX_WD_COMP_L16");              break; 
		case VDX_AE_MODE16 :                printf("VDX_AE_MODE16");                break; 
		case VDX_COMM_BAUDRATE :            printf("VDX_COMM_BAUDRATE");            break; 
		case VDX_MONITORING_MODE :          printf("VDX_MONITORING_MODE");          break; 
		case VDX_AO_ON :                    printf("VDX_AO_ON");                    break; 
		case VDX_DO_ON :                    printf("VDX_DO_ON");                    break; 
		case VDX_LVDS_OUT :                 printf("VDX_LVDS_OUT");                 break; 
		case VDX_ZWIDE_LIMIT :              printf("VDX_ZWIDE_LIMIT");              break; 
		case VDX_ZTELE_LIMIT :              printf("VDX_ZTELE_LIMIT");              break; 
		case VDX_DZ_MAX :                   printf("VDX_DZ_MAX");                   break; 
		case VDX_SZOOM_ON :                 printf("VDX_SZOOM_ON");                 break; 
		case VDX_FTRACE_ON :                printf("VDX_FTRACE_ON");                break; 
		case VDX_FCS_OFFSET_DOME :          printf("VDX_FCS_OFFSET_DOME");          break; 
		case VDX_EX_EXPC_ON :               printf("VDX_EX_EXPC_ON");               break; 
		case VDX_EX_EXPAP_ON :              printf("VDX_EX_EXPAP_ON");              break; 
		case VDX_EX_CGCH_ON :               printf("VDX_EX_CGCH_ON");               break; 
		case VDX_EX_AICR_F2O_ON :           printf("VDX_EX_AICR_F2O_ON");           break; 
		case VDX_GAIN_LIMIT :               printf("VDX_GAIN_LIMIT");               break; 
		case VDX_STB_ON :                   printf("VDX_STB_ON");                   break; 
		case VDX_STB_HOLD :                 printf("VDX_STB_HOLD");                 break; 
		case VDX_CAM_USERMEMORYSET01 :      printf("VDX_CAM_USERMEMORYSET01");      break; 
		case VDX_CAM_USERMEMORYSET02 :      printf("VDX_CAM_USERMEMORYSET02");      break; 
		case VDX_CAM_USERMEMORYSET03 :      printf("VDX_CAM_USERMEMORYSET03");      break; 
		case VDX_CAM_USERMEMORYSET04 :      printf("VDX_CAM_USERMEMORYSET04");      break; 
		case VDX_CAM_USERMEMORYSET05 :      printf("VDX_CAM_USERMEMORYSET05");      break; 
		case VDX_CAM_USERMEMORYSET06 :      printf("VDX_CAM_USERMEMORYSET06");      break; 
		case VDX_CAM_USERMEMORYSET07 :      printf("VDX_CAM_USERMEMORYSET07");      break; 
		case VDX_CAM_USERMEMORYSET08 :      printf("VDX_CAM_USERMEMORYSET08");      break; 
		case VDX_CAM_USERMEMORYSET09 :      printf("VDX_CAM_USERMEMORYSET09");      break; 
		case VDX_CAM_USERMEMORYSET10 :      printf("VDX_CAM_USERMEMORYSET10");      break; 
		case VDX_CAM_USERMEMORYSET11 :      printf("VDX_CAM_USERMEMORYSET11");      break; 
		case VDX_CAM_USERMEMORYSET12 :      printf("VDX_CAM_USERMEMORYSET12");      break; 
		case VDX_CAM_USERMEMORYSET13 :      printf("VDX_CAM_USERMEMORYSET13");      break; 
		case VDX_CAM_USERMEMORYSET14 :      printf("VDX_CAM_USERMEMORYSET14");      break; 
		case VDX_CAM_USERMEMORYSET15 :      printf("VDX_CAM_USERMEMORYSET15");      break; 
		case VDX_CAM_USERMEMORYSET16 :      printf("VDX_CAM_USERMEMORYSET16");      break; 
		case VDX_WD_SCR_DISP :              printf("VDX_WD_SCR_DISP");              break; 
		case VDX_WD_DET_SENS :              printf("VDX_WD_DET_SENS");              break; 
		case VDX_WD_BUCORR_LV :             printf("VDX_WD_BUCORR_LV");             break; 
		case VDX_WD_BOCORR_LV :             printf("VDX_WD_BOCORR_LV");             break; 
		case VDX_WD_SHORT_EXPR :            printf("VDX_WD_SHORT_EXPR");            break; 
		case VDX_WD_ALARM :                 printf("VDX_WD_ALARM");                 break; 
		case IDX_OSDON :                    printf("IDX_OSDON");                    break; 
		case IDX_OSDOFF :                   printf("IDX_OSDOFF");                   break; 
		case IDX_OSDHIDDENON :              printf("IDX_OSDHIDDENON");              break; 
		case IDX_OSDEXITSAVE :              printf("IDX_OSDEXITSAVE");              break; 
		case IDX_OSDEXITNOTSAVE :           printf("IDX_OSDEXITNOTSAVE");           break; 
		case IDX_CAMREBOOTSAVE :            printf("IDX_CAMREBOOTSAVE");            break; 
		case IDX_CAMREBOOTNOTSAVE :         printf("IDX_CAMREBOOTNOTSAVE");         break; 
		case IDX_NOT_USE :                  printf("IDX_NOT_USE");                  break; 
		case IDX_EXIT :                     printf("IDX_EXIT");                     break; 
		case IDX_RETURN :                   printf("IDX_RETURN");                   break; 
		case IDX_INITIAL :                  printf("IDX_INITIAL");                  break; 
		case IDX_TITLE :                    printf("IDX_TITLE");                    break; 
		case IDX_FRESET :                   printf("IDX_FRESET");                   break; 
		case IDX_REBOOT :                   printf("IDX_REBOOT");                   break; 
		case IDX_MD_STT :                   printf("IDX_MD_STT");                   break; 
		case IDX_MD_ZONE :                  printf("IDX_MD_ZONE");                  break; 
		case IDX_MD_STATE :                 printf("IDX_MD_STATE");                 break; 
		case IDX_MD_DISP :                  printf("IDX_MD_DISP");                  break; 
		case IDX_MD_ALARM :                 printf("IDX_MD_ALARM");                 break; 
		case IDX_MD_SENS :                  printf("IDX_MD_SENS");                  break; 
		case IDX_MD_X :                     printf("IDX_MD_X");                     break; 
		case IDX_MD_Y :                     printf("IDX_MD_Y");                     break; 
		case IDX_MD_W :                     printf("IDX_MD_W");                     break; 
		case IDX_MD_H :                     printf("IDX_MD_H");                     break; 
		case IDX_MD_END :                   printf("IDX_MD_END");                   break; 
		case IDX_PRI_STT :                  printf("IDX_PRI_STT");                  break; 
		case IDX_PRI_ZONE :                 printf("IDX_PRI_ZONE");                 break; 
		case IDX_PRI_STATE :                printf("IDX_PRI_STATE");                break; 
		case IDX_PRI_TRANS :                printf("IDX_PRI_TRANS");                break; 
		case IDX_PRI_COLOR :                printf("IDX_PRI_COLOR");                break; 
		case IDX_PRI_MOSAIC :               printf("IDX_PRI_MOSAIC");               break; 
		case IDX_PRI_X :                    printf("IDX_PRI_X");                    break; 
		case IDX_PRI_Y :                    printf("IDX_PRI_Y");                    break; 
		case IDX_PRI_W :                    printf("IDX_PRI_W");                    break; 
		case IDX_PRI_H :                    printf("IDX_PRI_H");                    break; 
		case IDX_PRI_P :                    printf("IDX_PRI_P");                    break; 
		case IDX_PRI_T :                    printf("IDX_PRI_T");                    break; 
		case IDX_PRI_Z :                    printf("IDX_PRI_Z");                    break; 
		case IDX_PRI_END :                  printf("IDX_PRI_END");                  break; 
		case VDX_MASK_STT :                 printf("VDX_MASK_STT");                 break; 
		case VDX_MASK_ON :                  printf("VDX_MASK_ON");                  break; 
		case VDX_MASK_DISP :                printf("VDX_MASK_DISP");                break; 
		case VDX_MASK_I :                   printf("VDX_MASK_I");                   break; 
		case VDX_MASK_ZONE :                printf("VDX_MASK_ZONE");                break; 
		case VDX_MASK_MODIFY :              printf("VDX_MASK_MODIFY");              break; 
		case VDX_MASK_TRANS :               printf("VDX_MASK_TRANS");               break; 
		case VDX_MASK_MOSAIC :              printf("VDX_MASK_MOSAIC");              break; 
		case VDX_MASK_COLOR_ON :            printf("VDX_MASK_COLOR_ON");            break; 
		case VDX_MASK_COLOR_OFF :           printf("VDX_MASK_COLOR_OFF");           break; 
		case VDX_MASK_X_POS :               printf("VDX_MASK_X_POS");               break; 
		case VDX_MASK_Y_POS :               printf("VDX_MASK_Y_POS");               break; 
		case VDX_MASK_WIDTH :               printf("VDX_MASK_WIDTH");               break; 
		case VDX_MASK_HEIGHT :              printf("VDX_MASK_HEIGHT");              break; 
		case VDX_MASK_P :                   printf("VDX_MASK_P");                   break; 
		case VDX_MASK_T :                   printf("VDX_MASK_T");                   break; 
		case VDX_MASK_Z :                   printf("VDX_MASK_Z");                   break; 
		case VDX_MASK_END :                 printf("VDX_MASK_END");                 break; 
		case VDX_MD_STT :                   printf("VDX_MD_STT");                   break; 
		case VDX_MD_ZONE :                  printf("VDX_MD_ZONE");                  break; 
		case VDX_MD_SRT_H_POS :             printf("VDX_MD_SRT_H_POS");             break; 
		case VDX_MD_SRT_V_POS :             printf("VDX_MD_SRT_V_POS");             break; 
		case VDX_MD_STP_H_POS :             printf("VDX_MD_STP_H_POS");             break; 
		case VDX_MD_STP_V_POS :             printf("VDX_MD_STP_V_POS");             break; 
		case VDX_MD_END :                   printf("VDX_MD_END");                   break; 
		case VDX_TITLE_STT :                printf("VDX_TITLE_STT");                break; 
		case VDX_TITLE_H_POS :              printf("VDX_TITLE_H_POS");              break; 
		case VDX_TITLE_ON :                 printf("VDX_TITLE_ON");                 break; 
		case VDX_TITLE_LINE :               printf("VDX_TITLE_LINE");               break; 
		case VDX_TITLE_BLINK :              printf("VDX_TITLE_BLINK");              break; 
		case VDX_TITLE_COLOR :              printf("VDX_TITLE_COLOR");              break; 
		case VDX_TITLE_LINE_CH1 :           printf("VDX_TITLE_LINE_CH1");           break; 
		case VDX_TITLE_LINE_CH2 :           printf("VDX_TITLE_LINE_CH2");           break; 
		case VDX_TITLE_LINE_CH3 :           printf("VDX_TITLE_LINE_CH3");           break; 
		case VDX_TITLE_LINE_CH4 :           printf("VDX_TITLE_LINE_CH4");           break; 
		case VDX_TITLE_LINE_CH5 :           printf("VDX_TITLE_LINE_CH5");           break; 
		case VDX_TITLE_LINE_CH6 :           printf("VDX_TITLE_LINE_CH6");           break; 
		case VDX_TITLE_LINE_CH7 :           printf("VDX_TITLE_LINE_CH7");           break; 
		case VDX_TITLE_LINE_CH8 :           printf("VDX_TITLE_LINE_CH8");           break; 
		case VDX_TITLE_LINE_CH9 :           printf("VDX_TITLE_LINE_CH9");           break; 
		case VDX_TITLE_LINE_CH10 :          printf("VDX_TITLE_LINE_CH10");          break; 
		case VDX_TITLE_LINE_CH11 :          printf("VDX_TITLE_LINE_CH11");          break; 
		case VDX_TITLE_LINE_CH12 :          printf("VDX_TITLE_LINE_CH12");          break; 
		case VDX_TITLE_LINE_CH13 :          printf("VDX_TITLE_LINE_CH13");          break; 
		case VDX_TITLE_LINE_CH14 :          printf("VDX_TITLE_LINE_CH14");          break; 
		case VDX_TITLE_LINE_CH15 :          printf("VDX_TITLE_LINE_CH15");          break; 
		case VDX_TITLE_LINE_CH16 :          printf("VDX_TITLE_LINE_CH16");          break; 
		case VDX_TITLE_LINE_CH17 :          printf("VDX_TITLE_LINE_CH17");          break; 
		case VDX_TITLE_LINE_CH18 :          printf("VDX_TITLE_LINE_CH18");          break; 
		case VDX_TITLE_LINE_CH19 :          printf("VDX_TITLE_LINE_CH19");          break; 
		case VDX_TITLE_LINE_CH20 :          printf("VDX_TITLE_LINE_CH20");          break; 
		case VDX_TITLE_END :                printf("VDX_TITLE_END");                break; 
		case VDX_MOVE_RGAIN :               printf("VDX_MOVE_RGAIN");               break; 
		case VDX_MOVE_BGAIN :               printf("VDX_MOVE_BGAIN");               break; 
		case VDX_MOVE_DZOOM :               printf("VDX_MOVE_DZOOM");               break; 
		case VDX_MOVE_ZOOM :                printf("VDX_MOVE_ZOOM");                break; 
		case VDX_MOVE_FOCUS :               printf("VDX_MOVE_FOCUS");               break; 
		case VDX_MOVE_SHUT :                printf("VDX_MOVE_SHUT");                break; 
		case VDX_MOVE_IRIS :                printf("VDX_MOVE_IRIS");                break; 
		case VDX_MOVE_GAIN :                printf("VDX_MOVE_GAIN");                break; 
		case VDX_MOVE_BRIGHT :              printf("VDX_MOVE_BRIGHT");              break; 
		case VDX_MOVE_EXPCOMP :             printf("VDX_MOVE_EXPCOMP");             break; 
		case VDX_MOVE_APERTURE :            printf("VDX_MOVE_APERTURE");            break; 
		case VDX_PUSH_WB :                  printf("VDX_PUSH_WB");                  break; 
		case VDX_INIT_CAM :                 printf("VDX_INIT_CAM");                 break; 
		case VDX_CAM_MEMCUS :               printf("VDX_CAM_MEMCUS");               break; 
		case VDX_FCS_PUSH :                 printf("VDX_FCS_PUSH");                 break; 
		case VDX_TITLE_SET :                printf("VDX_TITLE_SET");                break; 
		case VDX_MODEL_CODE :               printf("VDX_MODEL_CODE");               break; 
		case VDX_ROM_VERSION :              printf("VDX_ROM_VERSION");              break; 
		case VDX_SOCKET_NUM :               printf("VDX_SOCKET_NUM");               break; 
		case VDX_CAM_PAN :                  printf("VDX_CAM_PAN");                  break; 
		case VDX_CAM_TILT :                 printf("VDX_CAM_TILT");                 break; 
		case VDX_TEMPERATURE :              printf("VDX_TEMPERATURE");              break; 
		case VDX_VSC_REG_ADDR :             printf("VDX_VSC_REG_ADDR");             break; 
		case VDX_VSC_REG_DAT :              printf("VDX_VSC_REG_DAT");              break; 
		case VDX_MEM_SAVE_ADDR :            printf("VDX_MEM_SAVE_ADDR");            break; 
		case VDX_MEM_SAVE_DAT :             printf("VDX_MEM_SAVE_DAT");             break; 
		case VDX_EXTEND :                   printf("VDX_EXTEND");                   break; 
		case VDX_REGITER_SET :              printf("VDX_REGITER_SET");              break; 
		case VDX_RECIEVE_DATA :             printf("VDX_RECIEVE_DATA");             break; 
		case VDX_ZM_FCS_POS :               printf("VDX_ZM_FCS_POS");               break; 
		case VDX_CAM_ACTIV :                printf("VDX_CAM_ACTIV");                break; 
		case VDX_TITLE_DISP :               printf("VDX_TITLE_DISP");               break; 
		case VDX_PRI_ON :                   printf("VDX_PRI_ON");                   break; 
		case VDX_MEM_PROVIDED :             printf("VDX_MEM_PROVIDED");             break; 
		case VDX_ICR_PROVIDED :             printf("VDX_ICR_PROVIDED");             break; 
		case VDX_SYS_PROVIDED :             printf("VDX_SYS_PROVIDED");             break; 
		case VDX_EFLP_PROVIDED :            printf("VDX_EFLP_PROVIDED");            break; 
		case VDX_AMASK_PROVIDED :           printf("VDX_AMASK_PROVIDED");           break; 
		case VDX_STAB_PROVIDED :            printf("VDX_STAB_PROVIDED");            break; 
		case VDX_LOW_CONT_DETECTED :        printf("VDX_LOW_CONT_DETECTED");        break; 
		case VDX_FOCUS_COMMAND :            printf("VDX_FOCUS_COMMAND");            break; 
		case VDX_ZOOM_COMMAND :             printf("VDX_ZOOM_COMMAND");             break; 
		case VDX_ZMFCS_COMMAND :            printf("VDX_ZMFCS_COMMAND");            break; 
		case VDX_CAMERA_SET :               printf("VDX_CAMERA_SET");               break; 
		case VDX_CAMERA_RESET :             printf("VDX_CAMERA_RESET");             break; 
		case VDX_CAMERA_RECALL :            printf("VDX_CAMERA_RECALL");            break; 
		case CHDX_DSP_REG_READ :            printf("CHDX_DSP_REG_READ");            break; 
		case CHDX_DSP_REG_WRITE :           printf("CHDX_DSP_REG_WRITE");           break; 
		case CHDX_EEPROM_READ :             printf("CHDX_EEPROM_READ");             break; 
		case CHDX_EEPROM_WRITE :            printf("CHDX_EEPROM_WRITE");            break; 
		case CHDX_MOTOR_DRV_ACCESS :        printf("CHDX_MOTOR_DRV_ACCESS");        break; 
		case CHDX_VIDEO_ENC_ACCESS :        printf("CHDX_VIDEO_ENC_ACCESS");        break; 
		case CHDX_SENSOR_IC_ACCESS :        printf("CHDX_SENSOR_IC_ACCESS");        break; 
		case CHDX_FREE_BUF_READ :           printf("CHDX_FREE_BUF_READ");           break; 
		case CHDX_STATISTICS_DAT_READ :     printf("CHDX_STATISTICS_DAT_REA");      break; 
		case CHDX_AUTO_ADJ :                printf("CHDX_AUTO_ADJ");                break; 
		case CHDX_ALGORISM_RUN :            printf("CHDX_ALGORISM_RUN");            break; 
		case CHDX_VIDEO_ENC_ACCESS2 :       printf("CHDX_VIDEO_ENC_ACCESS2");       break; 
		case CHDX_SKIP_EEP_WRITE :          printf("CHDX_SKIP_EEP_WRITE");          break; 
	}
}
