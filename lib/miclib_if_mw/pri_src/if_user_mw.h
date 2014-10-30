/*************************************************************************************************************
*										Interface Library Description
*						Copyright(c) 2013 by CNBTec co .ltd, All right reserved
**************************************************************************************************************
* File Name		: if_user_mw.c
* Programmer(s)	: KWNAM, SHKIM
* Data			: 
* Version		: 0.1
* Compiler		: VS9.0 & GCC
* Debugger		: VS9.0
**************************************************************************************************************
* File Description	: 
**************************************************************************************************************
* 이 파일은 EEPRom, OSD, Protocl 인터페이스를 위한 라이브러리 파일입니다.
* 
* !!!!!!!!!!!!!!!!!! // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*
**************************************************************************************************************
* Revision History
**************************************************************************************************************
* 
*************************************************************************************************************/
#ifndef _IF_USER_MW_H_
#define _IF_USER_MW_H_

#ifndef IF_USER_MW_EXT
#define IF_USER_MW_EXT	extern
#endif

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "miclib_type.h"
#ifdef WIN32
#include "miclib_if_mw.h"
#else
#include "miclib_if_mw.h"
#endif

/*************************************************************************************************************
* TYPE DEFINE
*************************************************************************************************************/
/************************************************************************************************************/
/* Event */

/************************************************************************************************************/
/* EEPRom */
/* User Eeprom 데이터의 인덱스 */

#define UIDX_MD_SENSITIVITY 		(IDX_USER + 7  )
#define UIDX_OSD_DEBUG_STATE 		(IDX_USER + 8  )
#define UIDX_IRIS_JUMP 		      	(IDX_USER + 9  )
#define UIDX_AUTO_MIN_SHUTTER	  	(IDX_USER + 10 )
#define UIDX_AUTO_MAX_SHUTTER     	(IDX_USER + 11 )
#define UIDX_SPOT_AE      			(IDX_USER + 12 )
#define UIDX_AE_RESPONS            	(IDX_USER + 13 )
#define UIDX_SPOT_AE_POS_X         	(IDX_USER + 14 )
#define UIDX_SPOT_AE_POS_Y         	(IDX_USER + 15 )
#define UIDX_AGING_STATE		  	(IDX_USER + 22 )
#define UIDX_AGING_MODE			  	(IDX_USER + 23 )
#define UIDX_DBDR_MODE			  	(IDX_USER + 24 )
#define UIDX_WINDOW_START_X		  	(IDX_USER + 25 )
#define UIDX_WINDOW_WIDE		  	(IDX_USER + 26 )
#define UIDX_WINDOW_START_Y		  	(IDX_USER + 27 )
#define UIDX_WINDOW_HEIGHT		  	(IDX_USER + 28 )
#define UIDX_B_GAIN_P			  	(IDX_USER + 29 )
#define UIDX_B_GAIN_N		      	(IDX_USER + 30 )
#define UIDX_R_GAIN_P		      	(IDX_USER + 31 )
#define UIDX_R_GAIN_N		      	(IDX_USER + 32 )
#define UIDX_B_HUE_P 		      	(IDX_USER + 33 )
#define UIDX_B_HUE_N 		      	(IDX_USER + 34 )
#define UIDX_R_HUE_P 		      	(IDX_USER + 35 )
#define UIDX_R_HUE_N 		      	(IDX_USER + 36 )
#define UIDX_H_SIZE				  	(IDX_USER + 37 )
#define UIDX_H_START			  	(IDX_USER + 38 )
#define UIDX_H_END				  	(IDX_USER + 39 )
#define UIDX_V_TOTAL_SIZE		  	(IDX_USER + 40 )
#define UIDX_V_ACT_START		  	(IDX_USER + 41 )
#define UIDX_V_ACT_END			  	(IDX_USER + 42 )
#define UIDX_V_ACT_START_BOT	  	(IDX_USER + 43 )
#define UIDX_V_ACT_END_BOT		  	(IDX_USER + 44 )
#define	UIDX_COLOR_BAR			  	(IDX_USER + 45 )
#define	UIDX_MAIN_IN			  	(IDX_USER + 46 )
#define	UIDX_MAIN_OUT			  	(IDX_USER + 47 )
#define	UIDX_AUX_OUT			  	(IDX_USER + 48 )
#define	UIDX_VIDEO_ENCODER		  	(IDX_USER + 49 )
#define	UIDX_CVBS_MODE				(IDX_USER + 50 )
#define	UIDX_CBCR_SWAP				(IDX_USER + 51 )
#define	UIDX_FIRMWARE_UPDATEMODE_1	(IDX_USER + 52 )
#define	UIDX_FIRMWARE_UPDATEMODE_2	(IDX_USER + 53 )
#define	UIDX_FIRMWARE_UPDATEMODE_3	(IDX_USER + 54 )
#define	UIDX_TEMP_1					(IDX_USER + 55 )
#define	UIDX_PRTCL_TYPE				(IDX_USER + 56 )
#define	UIDX_PRTCL_BAUD				(IDX_USER + 57 )
#define	UIDX_CAM_RES				(IDX_USER + 58 )
#define	UIDX_MD_DISP				(IDX_USER + 59 )
#define UIDX_WB_PUSH		   	    (IDX_USER + 60 )
#define UIDX_WB_COLOR_TEMP	   	    (IDX_USER + 61)
#define UIDX_AE_ACE					(IDX_USER + 67 )	//**01 : 아이디값 등록
#define UIDX_WB_MODE				(IDX_USER + 68 )	//**01 : 아이디값 등록
#define UIDX_PRI_ADJ_X				(IDX_USER + 69 )	//KSH 131230 추가
#define UIDX_PRI_ADJ_Y				(IDX_USER + 70 )	//KSH 131230 추가
#define UIDX_VISCA_OSD_MENU			(IDX_USER + 71 )	//KSH 140109 추가
#define UIDX_GAMMA1					(IDX_USER + 72 )	//KSH 140402 추가
#define UIDX_GAMMA2					(IDX_USER + 73 )	//KSH 140402 추가
#define UIDX_LAST_YGAIN				(IDX_USER + 74 )	//KSH 140402 추가
#define UIDX_LAST_CGAIN				(IDX_USER + 75 )	//KSH 140402 추가



#define	PRM_HALL_MAX				(IDX_USER + 500)
#define	PRM_HALL_MIN				(IDX_USER + 501)
#define	PRM_IRIS_LV					(IDX_USER + 502)

#define	UIDX_IRIS_ADJ_ON			(IDX_USER + 503)
#define	UIDX_IRIS_ADJ_AE_DISBLE		(IDX_USER + 504)
#define	UIDX_IRIS_ADJ_SUM			(IDX_USER + 505)
#define	UIDX_IRIS_ADJ_SUM2			(IDX_USER + 506)
#define	UIDX_IRIS_ADJ_IRIS_VAL		(IDX_USER + 507)
#define	UIDX_IRIS_ADJ_SHUT_VAL		(IDX_USER + 508)
#define	UIDX_IRIS_ADJ_GAIN_VAL		(IDX_USER + 509)
#define	UIDX_IRIS_ADJ_RESET			(IDX_USER + 510)
#define	UIDX_IRIS_ADJ_SW2			(IDX_USER + 511)
#define	UIDX_IRIS_ADJ_DSS_VAL		(IDX_USER + 512)
#define	UIDX_EEP_ADDRESS			(IDX_USER + 513)	// EEP ADDR
#define UIDX_EEP_TEST_START			(IDX_USER + 514)	// 시작 종류


/* User Event */
#define UIDX_HALLADJ			   (IDX_USER + 1000)	// Hall Adjust
#define UIDX_LENSADJ			   (IDX_USER + 1001)	// Lens Adjust
#define UIDX_DEFECTADJ			   (IDX_USER + 1002)	// Defect Detection
#define UIDX_SHADEADJ			   (IDX_USER + 1003)	// Shade Adjust
#define UIDX_DEFECTLOAD			   (IDX_USER + 1004)
#define UIDX_SHADELOAD			   (IDX_USER + 1005)
#define UIDX_PASS			   	   (IDX_USER + 1006)
#define UIDX_PRI_RESETZONE		   (IDX_USER + 1007)
#define UIDX_MD_RESETZONE		   (IDX_USER + 1008)
#define UIDX_PRI_CENTER		   	   (IDX_USER + 1009)
#define UIDX_3DPRI_ZOOM		   	   (IDX_USER + 1010)
#define UIDX_3DPRI_ADJ			   (IDX_USER + 1011)	
#define UIDX_DEFEC_IN			   (IDX_USER + 1012)	
#define UIDX_SHADE_IN			   (IDX_USER + 1013)	
#define UIDX_TNN_EXPOSURE		   (IDX_USER + 1014)
#define UIDX_TNN_EXPOSURE		   (IDX_USER + 1014)
#define UIDX_EEP_TEST_REFRESH	   (IDX_USER + 1015)
#define UIDX_TNN_EEP			   (IDX_USER + 1016)
#define UIDX_TUNE_ADJ_COLOR		   (IDX_USER + 1017)
#define UIDX_LENS_AF_AGING		   (IDX_USER + 1018)	// NAM 140327


#define OSD_KEYLONG					0x400
#define IFU_OSD_KEYDSS				0x800
#define IFU_OSD_KEY1				0x1000
#define IFU_OSD_KEY2				0x2000
#define IFU_OSD_KEY3				0x4000
#define IFU_OSD_KEY4				0x8000

#define EEP_USER_LEN			0x60
#define DECODE_SIZE 			133
typedef union _EEPROM_USER 
{
	uint08 Data[EEP_USER_LEN];

	struct
	{
		unsigned 	WB_MODE				:8;	//0x400
		unsigned 	TEST_IMAGE			:8;
		unsigned 	OSD_DEBUG_STATE  	:7;
		unsigned 						:1;
		unsigned 	AUTO_MAX_SHUTTER	:8;		

		unsigned 	AUTO_MIN_SHUTTER	:8;
		unsigned 	ZOOM_MODE			:1;
		unsigned 	GAMMA_BRIGHT		:7;
		unsigned 	MD_SENSITIVITY		:8;
		/*********************************/
		unsigned 	IRIS_JUMP			:16;
		unsigned	AGING_STATE 		:8;		
		unsigned	AGING_MODE			:8;
		
		unsigned	DBDR_MODE			:8;
		unsigned	WINDOW_START_X		:8;
		unsigned	WINDOW_WIDE 		:8;		
		unsigned	WINDOW_START_Y		:8;
		/*********************************/		
		unsigned	WINDOW_HEIGHT		:8;//0x410
		unsigned	B_GAIN_P			:8;
		unsigned	B_GAIN_N			:8;		
		unsigned	R_GAIN_P			:8;

		unsigned	R_GAIN_N			:8;
		unsigned	B_HUE_P 			:8;
		unsigned	B_HUE_N 			:8;		
		unsigned	R_HUE_P 			:8;
		/*********************************/
		unsigned	R_HUE_N 			:8;
		unsigned	H_SIZE				:8;
		unsigned	H_START 			:8;
		unsigned	H_END				:8;

		unsigned	V_TOTAL_SIZE		:8;
		unsigned	V_ACT_START 		:8;
		unsigned	V_ACT_END			:8;
		unsigned	V_ACT_START_BOT 	:8;
		/*********************************/
		unsigned	V_ACT_END_BOT		:8;//0x420
		unsigned	MAIN_IN 			:8;
		unsigned	MAIN_OUT			:8;
		unsigned	AUX_OUT 			:8;
		
		unsigned	VIDEO_ENCODER		:8;
		unsigned	CVBS_MODE			:8;
		unsigned	CBCR_SWAP			:8;
		unsigned	FIRMWARE_UPDATEMODE_1	:1;
		unsigned	FIRMWARE_UPDATEMODE_2	:1;
		unsigned	FIRMWARE_UPDATEMODE_3	:1;
		unsigned	TEMP_1				:1;
		unsigned	PRTCL_TYPE			:4;
		/*********************************/
		unsigned	PRTCL_BAUD			:4;
		unsigned	CAM_RES			 	:4;
		unsigned	MD_DISP				:2;
		unsigned	COLOR_TEMP		 	:6;
		unsigned	_3DPRI_ZOOM		 	:1;
		unsigned	WB_PUSH			 	:1;
		unsigned						:6;
		unsigned	AE_RESPONSE      	:5; 
		unsigned	VISCA_OSD_MENU		:1; 
		unsigned						:1; 
		unsigned	SPOT_AE         	:1;
		
		unsigned	FCS_LMT				:16;
		unsigned	SPOT_AE_POS_X   	:4; 
		unsigned	SPOT_AE_POS_Y   	:4; 
		unsigned	EXTEND_DZOOM_LV		:8;
		/*********************************/
		unsigned	AE_ACE				:8;//0x430
		unsigned	PRI_ADJ_X			:8;
		unsigned	PRI_ADJ_Y			:8;
		unsigned	COLOR_BAR			:8;
		/*********************************/
		unsigned	IMG_NEGA			:8;
		unsigned	INITIAL_CAM_RES		:8;
		unsigned	EEP_ADDR 			:16;
		/*********************************/
		unsigned	EEP_TEST 			:8;
		unsigned	GAMMA1				:4;
		unsigned	GAMMA2				:4;
		unsigned	LAST_YGAIN 			:8;
		unsigned	LAST_CGAIN 			:8;
	} FLD;
} EEPROM_USER;

extern EEPROM_USER			g_UserEepData;		// EEPRom ADDRESS 0x0400 ~ 0x05FF


/************************************************************************************************************/
/* OSD */

/************************************************************************************************************/
/* Protocl */

typedef struct _IFU_INITIAL{
	const EEP_IDX 	eepidx;
	const uint32	def;
}IFU_INITIAL;
/*
typedef enum _DECODE_TYPE {
	DECODE_MAPING,
	DECODE_DIRECT,
	DECODE_PLURAL,
	DECODE_EXCEPTION,
	DECODE_MAX,
} DECODE_TYPE;
*/

/*************************************************************************************************************
* GLOBAL VARIABLE EXTERNS
*************************************************************************************************************/
/************************************************************************************************************/
/* Event */

/************************************************************************************************************/
/* EEPRom */
IF_USER_MW_EXT uint08		g_UserData[0x40];

/************************************************************************************************************/
/* OSD */
IF_USER_MW_EXT const OSD_MAP		OSD_gMap[];			// OSD Map
IF_USER_MW_EXT const OSD_MAP		OSD_gHiddenMap[];	// OSD Hidden Map

/************************************************************************************************************/
/* Protocl */

/*************************************************************************************************************
* GLOBAL FUNCTION EXTERNS
*************************************************************************************************************/
IF_USER_MW_EXT int Interp1D_RoundOff(int aiXCur,int aiXPos1,int aiXPos2,int aiYPos1,int aiYPos2);
/************************************************************************************************************/
/* Event */
IF_USER_MW_EXT IFER IFU_Event_Callback(IFEVT evt, IFEVT_PARAM *param);

/************************************************************************************************************/
/* EEPRom */
IF_USER_MW_EXT int32 User_Update(IFEVT evt, EEP_IDX idx, int32 val);
IF_USER_MW_EXT void IFU_OSD_MD_OUT(uint16 Val);


/************************************************************************************************************/
/* OSD */
IF_USER_MW_EXT void IFU_OSD_User_Init();
IF_USER_MW_EXT void IFU_Osd_KeyInput(uint32 key);
IF_USER_MW_EXT void IFU_Osd_TASK();
IF_USER_MW_EXT void IFU_BOOTING_MSG(int08 bootflg);

IF_USER_MW_EXT uint08 IFU_Osd_PriOn();
IF_USER_MW_EXT uint08 IFU_Osd_MDOn();
IF_USER_MW_EXT void IFU_Osd_ItemRefresh(uint08 cursor);
/************************************************************************************************************/
/* Protocl */
typedef enum _VISCA_AFTER_MEM {
	VISCA_AFTER_EVT_SAVE_NONE,
	VISCA_AFTER_EVT_SAVE_MEM,
	VISCA_AFTER_EVT_SAVE_REG,
	VISCA_AFTER_EVT_MAX
}VISCA_AFTER_MEM;

typedef struct _KEY_QUE{
	uint08 head;
	uint08 tail;
	uint32 code[32];
} KEY_QUE;




//IF_USER_MW_EXT uint08 wtmp[100];	//For EEP_MW TEST ,KSH 140317
//IF_USER_MW_EXT uint08 rtmp[100];	//For EEP_MW TEST ,KSH 140317

#endif // _IF_USER_MW_H_
