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
#define UIDX_AF_OSD			 		(IDX_USER + 76 )
#define UIDX_BLC_AREA				(IDX_USER + 77 )

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
#define UIDX_WB_LEVLE_UP		   (IDX_USER + 1019)
#define UIDX_WB_LEVLE_DOWN		   (IDX_USER + 1020)


#define OSD_KEYLONG					0x400
#define IFU_OSD_KEYDSS				0x800
#define IFU_OSD_KEY1				0x1000
#define IFU_OSD_KEY2				0x2000
#define IFU_OSD_KEY3				0x4000
#define IFU_OSD_KEY4				0x8000

#ifndef PARAM_MW_H_

/*************************************************************************************************************
* DEFINES FOR INITIALIZE
*************************************************************************************************************/
// EEP RW MODES
#define EP_FULL_AREA (EP_OSD_AREA|EP_OSD_AREA|EP_CAM_AREA|EP_USER_AREA)
#define EP_OSD_AREA		0x1
#define EP_CAM_AREA		0x2
#define EP_VISCA_AREA	0x4
#define EP_USER_AREA	0x8


// EEPROM DEFAULT VALUE DEFINES
#define EEPROM_STATUS_NEW			3
#define EEPROM_STATUS_INITIALIZED	2
#define EEPROM_STATUS_NORMAL		1
#define EEPROM_STATUS_FACTORY_RESET	0

#define ADJUST_STATUS_OK			0x0
#define ADJUST_STATUS_NG			0x1
#define ADJUST_STATUS_BUSY			0x2
#define ADJUST_STATUS_NOT_YET		0xF

#define DEFAULT_HALL_TGT_MAX	DEF_HALL_MAX
#define DEFAULT_HALL_TGT_MIN	DEF_HALL_MIN
#define DEFAULT_HALL_MAX		DEF_HALL_MAX
#define DEFAULT_HALL_MIN		DEF_HALL_MIN

#define DEFAULT_HALL_OFFSET		HALL_OFFSET_ZERO
#define DEFAULT_HALL_GAIN		HALL_GAIN_ZERO
#define DEFAULT_HALL_DAC		HALL_BIAS_DAC_ZERO
#define DEFAULT_HADJ_DIFF_OFF	0
#define DEFAULT_HADJ_MEAN_OFF	0

#define DEFAULT_OADJ_ZADD		0
#define DEFAULT_OADJ_FADD		0
#define DEFAULT_OADJ_ZOFF		0
#define DEFAULT_OADJ_FOFF		0
#define DEFAULT_OADJ_PD_SRT		0
#define DEFAULT_OADJ_ZD_SRT		0
#define DEFAULT_OADJ_FD_SRT		0
#define DEFAULT_OADJ_P2DEC_R	0
#define DEFAULT_OADJ_T2DEC_R	0
#define DEFAULT_PEAK_DIFF		DEF_PEAK_DIFF
#define DEFAULT_FOCUS_DIFF		DEF_FOCUS_DIFF
#define DEFAULT_ZOOM_DIFF		DEF_ZOOM_DIFF
#define DEFAULT_OADJ_WEND_S		0
#define DEFAULT_OADJ_TEND_S		0

#define DEFAULT_DADJ_THRESHOLD	0
#define DEFAULT_SADJ_GAIN		0
#define DEFAULT_SADJ_OFFSET		0

#define DEFAULT_ADKEY00		KC_TELE
#define DEFAULT_ADKEY01		KC_WIDE
#define DEFAULT_ADKEY02		KC_NEAR
#define DEFAULT_ADKEY03		KC_FAR
#define DEFAULT_ADKEY04		KC_1SHOT_AF
#define DEFAULT_ADKEY05		KC_NKEY
#define DEFAULT_ADKEY06		KC_NKEY
#define DEFAULT_ADKEY07		KC_NKEY

#define DEFAULT_ADKEY10		KC_AUTOZOOM
#define DEFAULT_ADKEY11		KC_1SHOT_AF
#define DEFAULT_ADKEY12		KC_TELE
#define DEFAULT_ADKEY13		KC_WIDE
#define DEFAULT_ADKEY14		KC_BL
#define DEFAULT_ADKEY15		KC_LED
#define DEFAULT_ADKEY16		KC_MAXFLDUP
#define DEFAULT_ADKEY17		KC_NKEY

#define DEFAULT_CAM_TYPE		0	// 0:NTSC 1:PAL
#define DEFAULT_CAM_CLASS		CAM_CLASS_ZOOM_MODULE	// 0:BOARD 1:ZOOM(SET) 2:ZOOM(MODULE) 3:ZOOM(POLICE)
#define DEFAULT_EEP_VER			1	// 1
#define DEFAULT_CCD_TYPE		0x1	// cmos mn34041 2.0mp
#define DEFAULT_CLIENT_OPT		0

#define DEFAULT_COMM_SET		STATE_OFF
#define DEFAULT_MENU_USE		STATE_OFF
#define DEFAULT_LENS_INIT_TYPE	0
#define DEFAULT_HOME_USE		STATE_OFF

#define DEFAULT_FOCUS_MODE		0		// auto focus mode (AUTO/MANUAL)
#define DEFAULT_AF_MODE			0
#define DEFAULT_AF_MOVE_TIME	5;	//sec
#define DEFAULT_AF_INTERVAL		5	//sec
#define DEFAULT_FOCUS_DIST		3	// 1M
#define DEFAULT_DZOOM_COMBINE	0	//0:COMBINE 1:SEPARATE
#define DEFAULT_DZOOM_MODE		STATE_ON

#define DEFAULT_TRACK_MODE		0	// auto track mode (AUTO/MANUAL)
#define DEFAULT_ZOOM_SPEED		4		// 0~7
#define DEFAULT_LENS_INIT_MODE	STATE_OFF				// off (OFF/ON)
#define DEFAULT_LENS_INIT_DAY	1

#define DEFAULT_ZOOM_POS		0		// x1
#define DEFAULT_FOCUS_POS		0x1000	// INF
#define DEFAULT_ZOOM_START_MAG		0		// x1
#define DEFAULT_ZOOM_END_MAG		10		// x10
#define DEFAULT_DZOOM_MAG		0

#define DEFAULT_HOME_MODE		0
#define DEFAULT_HOME_TIME		0
#define DEFAULT_HOME_ZPOS		0
#define DEFAULT_HOME_FPOS		0
#define DEFAULT_HOME_DZPOS		0

#define DEFAULT_AE_TGT_BRIGHT	50

#define DEFAULT_AE_MODE			0	// FULL AUTO (FA/FM/IP/SP/BRT)
#define DEFAULT_AGC_LIMIT		1	// (18dB)

#define DEFAULT_BRIGHT_STEP		50
#define DEFAULT_FLK_MODE		STATE_OFF
#define DEFAULT_GAIN_STEP		50

#define DEFAULT_WB_MODE			0	// ATW
#define DEFAULT_WB_ENV			0
#define DEFAULT_WB_RED_GAIN		50
#define DEFAULT_WB_BLUE_GAIN	50
#define DEFAULT_WB_COLOR_TEMP	0

#define DEFAULT_ATW_SPEED		0
#define DEFAULT_ATW_FRAME		0
#define DEFAULT_ATW_DELAY		0

#define DEFAULT_USR1_RGAIN		0
#define DEFAULT_USR1_BGAIN		0
#define DEFAULT_USR2_RGAIN		0
#define DEFAULT_USR2_BGAIN		0

#define DEFAULT_DN_MODE			1
#define DEFAULT_DN_ALARM_ON		STATE_OFF
#define DEFAULT_DN_CHG_STEP		5
#define DEFAULT_DN_CDS_STEP		5
#define DEFAULT_DN_CHG_TIME		2

#define DEFAULT_DN_MIN			0
#define DEFAULT_DN_CDS_CHG_TIME	0
#define DEFAULT_DN_CDS_MIN		0

#define DEFAULT_IMG_BRIGHT_LEVEL	50
#define DEFAULT_IMG_CONTRAST_LEVEL	50
#define DEFAULT_IMG_SHARPNESS_LEVEL	50
#define DEFAULT_IMG_CHROMA_LEVEL	50
#define DEFAULT_IMG_HUE_LEVEL		50

#define DEFAULT_IMG_FLIP	0
#define DEFAULT_IMG_FREEZE	STATE_OFF
#define DEFAULT_IMG_EFFECT	STATE_OFF
#define DEFAULT_IMG_COLOR 	STATE_ON
#define DEFAULT_IMG_SHADING	STATE_OFF
#define DEFAULT_IMG_DEFFECT	STATE_OFF
#define DEFAULT_IMG_GAMMA_STEP	0
#define DEFAULT_IMG_GAM_MODE	1
#define DEFAULT_IMG_RGAIN	50
#define DEFAULT_IMG_BGAIN	50

#define DEFAULT_HR_MODE			STATE_OFF
#define DEFAULT_BL_MODE			STATE_OFF
#define DEFAULT_BLC_MODE		STATE_OFF
#define DEFAULT_BLC_DISP		0
#define DEFAULT_BLC_LEVEL		0

#define DEFAULT_BLC_AREA_X_SRT	0
#define DEFAULT_BLC_AREA_Y_SRT	0
#define DEFAULT_BLC_AREA_WIDTH	0
#define DEFAULT_BLC_AREA_HEIGHT	0

#define DEFAULT_WDR_MODE		STATE_OFF
#define DEFAULT_WDR_LEVEL		0



#define DEFAULT_HLC_MODE		STATE_OFF
#define DEFAULT_HLC_CR			0		// color (black:0)

#define DEFAULT_DNR_MODE		2	// 0:OFF 1:2D 2:3D 3:2D&3D
#define DEFAULT_G_MOTION		STATE_OFF
#define DEFAULT_HLC_LEVEL		0
#define DEFAULT_HLC_SCALE		0
#define DEFAULT_DNR_LEVEL		1	//LOW

#define DEFAULT_3DNR_LEVEL		0
#define DEFAULT_2DNR_LEVEL		0

#define DEFAULT_MD_ON			STATE_OFF
#define DEFAULT_MD_STATE		STATE_OFF
#define DEFAULT_MD_DISP			STATE_OFF
#define DEFAULT_MD_ALARM		STATE_OFF
#define DEFAULT_MD_SENS			50


#define DEFAULT_MD_1_X			10
#define DEFAULT_MD_1_Y			10
#define DEFAULT_MD_1_W			25
#define DEFAULT_MD_1_H			25

#define DEFAULT_MD_2_X			60
#define DEFAULT_MD_2_Y			10
#define DEFAULT_MD_2_W			25
#define DEFAULT_MD_2_H			25

#define DEFAULT_MD_3_X			10
#define DEFAULT_MD_3_Y			60
#define DEFAULT_MD_3_W			25
#define DEFAULT_MD_3_H			25

#define DEFAULT_MD_4_X			60
#define DEFAULT_MD_4_Y			60
#define DEFAULT_MD_4_W			25
#define DEFAULT_MD_4_H			25

#define DEFAULT_DEFOG_ON		STATE_OFF
#define DEFAULT_DIS_ON			STATE_OFF
#define DEFAULT_SYNC			0
#define DEFAULT_SHADE_ON		STATE_OFF
#define DEFAULT_SYNC_PHASE		0

#define DEFAULT_CAMID_X_POS		0
#define DEFALUT_CAMID_Y_POS		0

#define DEFAULT_OSD_LANGUAGE	0
#define DEFAULT_ID_ON			STATE_OFF
#define DEFAULT_TITLE_ON		STATE_OFF
#define DEFAULT_ZMAG_ON			STATE_OFF
#define DEFAULT_FUNC_ON			STATE_OFF
#define DEFAULT_ALL_ON			STATE_OFF

#define DEFAULT_TITLE_BLK		0
#define DEFAULT_TITLE_COLOR		0
#define DEFAULT_TITLE_X_POS		0
#define DEFAULT_TITLE_Y_POS		0

#define DEFAULT_VOUT_FORMAT		4
#define DEFAULT_LVDS_D			STATE_OFF
#define DEFAULT_DOUT_FULL		STATE_OFF
#define DEFAULT_DOUT_ON			STATE_ON
#define DEFAULT_CVBS_ON			STATE_ON

#define DEFAULT_IRIS_STEP		50
#define DEFAULT_SHUT_STEP		8	//(1/60)
#define DEFAULT_AGC_LIMIT		1	// (18dB)
#define DEFAULT_DSS_STEP		1	// (1 SEC = X30) 0:OFF


//////////////////////////////////////////////////////////
#define DEFAULT_ATW_MODE		0		// 0:indoor 1:outdoor
#define DEFAULT_HLC_CLIP		50		//KSH 131013 Default 50->10	jsk_EEPRom_TB 참조
#define DEFAULT_MIRROR_MODE		STATE_OFF
#define DEFAULT_DZOOM_LEVEL		0
#define DEFAULT_IMG_COLOR_ON	STATE_ON
#define DEFAULT_SHADE_LEVEL		0		//KSH 131014 Default 50->0	Shade : Off/On
#define DEFAULT_GAMMA_BRIGHT_LEVEL	50
#define DEFAULT_CAM_ID			0
#define DEFAULT_PROTOCOL_TYPE	0	// CNB-HEX
#define DEFAULT_BAUDRATE		2	// 9600
#define DEFAULT_DN_LEVEL		5
#define DEFAULT_TRACE_MODE		0

#define DEFAULT_CAM_TITLE00		0
#define DEFAULT_CAM_TITLE01		0
#define DEFAULT_CAM_TITLE02		0
#define DEFAULT_CAM_TITLE03		0
#define DEFAULT_CAM_TITLE04		0
#define DEFAULT_CAM_TITLE05		0
#define DEFAULT_CAM_TITLE06		0
#define DEFAULT_CAM_TITLE07		0
#define DEFAULT_CAM_TITLE08		0
#define DEFAULT_CAM_TITLE09		0
#define DEFAULT_CAM_TITLE10		0
#define DEFAULT_CAM_TITLE11		0
#define DEFAULT_CAM_TITLE12		0
#define DEFAULT_CAM_TITLE13		0
#define DEFAULT_CAM_TITLE14		0
#define DEFAULT_CAM_TITLE15		0
#define DEFAULT_CAM_TITLE16		0
#define DEFAULT_CAM_TITLE17		0
#define DEFAULT_CAM_TITLE18		0
#define DEFAULT_CAM_TITLE19		0
#define DEFAULT_CAM_TITLE20		0
#define DEFAULT_CAM_TITLE21		0
#define DEFAULT_CAM_TITLE22		0
#define DEFAULT_CAM_TITLE23		0


#define DEFAULT_MD_ALARM		STATE_OFF
#define DEFAULT_MD_ALL			0

#define DEFAULT_CAM_LOGO_1		0
#define DEFAULT_CAM_LOGO_2		0
#define DEFAULT_CAM_LOGO_3		0
#define DEFAULT_CAM_LOGO_4		0
#define DEFAULT_CAM_LOGO_5		0
#define DEFAULT_CAM_LOGO_6		0
#define DEFAULT_CAM_LOGO_7		0
#define DEFAULT_CAM_LOGO_8		0
#define DEFAULT_CAM_LOGO_9		0
#define DEFAULT_CAM_LOGO_10		0
#define DEFAULT_CAM_LOGO_11		0
#define DEFAULT_CAM_LOGO_12		0
#define DEFAULT_CAM_LOGO_13		0
#define DEFAULT_CAM_LOGO_14		0
#define DEFAULT_CAM_LOGO_15		0
#define DEFAULT_CAM_LOGO_16		0
#define DEFAULT_CAM_LOGO_17		0
#define DEFAULT_CAM_LOGO_18		0
#define DEFAULT_CAM_LOGO_19		0
#define DEFAULT_CAM_LOGO_20		0
#define DEFAULT_CAM_LOGO_21		0
#define DEFAULT_CAM_LOGO_22		0
#define DEFAULT_CAM_LOGO_23		0
#define DEFAULT_CAM_LOGO_24		0
#define DEFAULT_CAM_LOGO_25		0
#define DEFAULT_CAM_LOGO_26		0
#define DEFAULT_CAM_LOGO_27		0
#define DEFAULT_CAM_LOGO_28		0
#define DEFAULT_CAM_LOGO_29		0
#define DEFAULT_CAM_LOGO_30		0
#define DEFAULT_CAM_LOGO_31		0
#define DEFAULT_CAM_LOGO_32		0

#define DEFAULT_PRI_STATE	0
#define DEFAULT_PRI_COLOR	0
#define DEFAULT_PRI_TRANS	3
#define DEFAULT_PRI_MOSAIC	0
#define DEFAULT_PRI_W		10
#define DEFAULT_PRI_H		10

#define DEFAULT_PRI1_X		20
#define DEFAULT_PRI2_X		40
#define DEFAULT_PRI3_X		60
#define DEFAULT_PRI4_X		80
#define DEFAULT_PRI5_X		20
#define DEFAULT_PRI6_X		40
#define DEFAULT_PRI7_X		60
#define DEFAULT_PRI8_X		80

#define DEFAULT_PRI1_Y		34
#define DEFAULT_PRI2_Y		34
#define DEFAULT_PRI3_Y		34
#define DEFAULT_PRI4_Y		34
#define DEFAULT_PRI5_Y		65
#define DEFAULT_PRI6_Y		65
#define DEFAULT_PRI7_Y		65
#define DEFAULT_PRI8_Y		65

#define DEFAULT_3DPRI_ADJ_X	100
#define DEFAULT_3DPRI_ADJ_Y	100

///////////////////////////////////////////////////////////////////////////////
// VISCA DEFAULT VALUE
///////////////////////////////////////////////////////////////////////////////
#define	DEFAULT_VISCA_POWER_ON			0		//0:ON 1:OFF
#define	DEFAULT_VISCA_ZOOM_POS			0		//0x0000 ~ 0x7AC0
#define	DEFAULT_VISCA_DZOOM_ON			1		//0:OFF 1:ON
#define	DEFAULT_VISCA_DZOOM_MODE		0		//0:COMB 1:SEP
#define	DEFAULT_VISCA_DZOOM_POS			0		//0x0~0xEB
#define	DEFAULT_VISCA_FOCUS_POS			0x1000	//0x1000~0xF000
#define	DEFAULT_VISCA_F_MODE			0		//0:AUTO 1:MANUAL 2:AUTO/MANUAL 3:ONE PUSH TRIGGER
#define	DEFAULT_VISCA_NEAR_LIMIT		0x7000	//0x1000~0xC000
#define	DEFAULT_VISCA_AF_SENS			0		//0:NORMAL 1:LOW
#define	DEFAULT_VISCA_AF_MODE			0		//0:NORMAL 1:INTERVAL 2:ZOOM-TRG
#define	DEFAULT_VISCA_AF_MOVE_TIME		5		//SECOND
#define	DEFAULT_VISCA_AF_INTERVAL_TIME	5		//SECOND
#define	DEFAULT_VISCA_IR_COR			0		//0:STANDARD 1:IR LIGHT
#define	DEFAULT_VISCA_WB_MODE			0		//0:AUTO 1:INDOOR 2:OUTDOOR 3:ONE PUSH 4:ATW 5:MANUAL 6:ONE PUSH TRG 7:OUT DOOR AUTO
#define	DEFAULT_VISCA_PUSH_WB_RGAIN		0		//0~255
#define	DEFAULT_VISCA_PUSH_WB_BGAIN		0		//0~255
#define	DEFAULT_VISCA_R_GAIN			0		//0~255
#define	DEFAULT_VISCA_B_GAIN			0		//0~255
#define	DEFAULT_VISCA_AE_MODE			0		//0:FA 1:MAN 2:SP 3:IP 4:BRIGHT
#define	DEFAULT_VISCA_ASS_ON			0		//0:OFF 1:ON
#define	DEFAULT_VISCA_SHUTTER_STEP		0		//0~0x15
#define	DEFAULT_VISCA_IRIS_STEP			0		//0~0x11
#define	DEFAULT_VISCA_GAIN_STEP			1		//1~0xF
#define	DEFAULT_VISCA_BRIGHT_STEP		0		//0~0x1F
#define	DEFAULT_VISCA_COMP_ON			0		//0:OFF 1:ON
#define	DEFAULT_VISCA_EXP_COMP_VAL		7		//0~0XE
#define	DEFAULT_VISCA_BLC_ON			0		//0:OFF 1:ON
#define	DEFAULT_VISCA_SPOT_AE_ON		0		//0:OFF 1:ON
#define	DEFAULT_VISCA_SPOT_AE_X_POS		8		//0~0xF
#define	DEFAULT_VISCA_SPOT_AE_Y_POS		8		//0~0xF
#define	DEFAULT_VISCA_AE_RESPONSE		1		//0x1~0x30
#define	DEFAULT_VISCA_WD_MODE			0		//0:off 1:on
#define	DEFAULT_VISCA_WD_BRT_L			0		
#define	DEFAULT_VISCA_WD_BRT_COMP		0
#define	DEFAULT_VISCA_WD_COMP_L			0
#define	DEFAULT_VISCA_DEFOG_ON			0		//0:off 1:on
#define	DEFAULT_VISCA_APER_GAIN			0xA		//0x0~0xF
#define	DEFAULT_VISCA_HR_ON				0			//0:off 1:on
#define	DEFAULT_VISCA_NR_SET			3		//0~5
#define	DEFAULT_VISCA_GAM_SET			0		//0:standard 1:straight
#define	DEFAULT_VISCA_HIGH_SENS_ON		0		//0:off 1:on
#define	DEFAULT_VISCA_LR_ON				0		//0:off 1:on
#define	DEFAULT_VISCA_FREEZE_ON			0		//0:off 1:on
#define	DEFAULT_VISCA_P_EFFECT			0		//0:off 2:nega 4:B/W
#define	DEFAULT_VISCA_FLIP_ON			0		//0:off 1:on
#define	DEFAULT_VISCA_ICR_ON			0		//0:icr on,day 1:icr off,night
#define	DEFAULT_VISCA_AICR_ON			0		//0:off 1:on
#define	DEFAULT_VISCA_AICR_THRS_L		0xE		//0x0~0x1C
#define	DEFAULT_VISCA_AICR_ALARM_ON		0		//0:off 1:on
#define	DEFAULT_VISCA_DISP_ON			0		//0:off 1:on

#define DEFAULT_VISCA_TITLE_H_POS		0		//0~0x1F
#define DEFAULT_VISCA_TITLE_ON			0		//0:OFF 1:ON
#define DEFAULT_VISCA_TITLE_LINE		0		//0~0xA
#define DEFAULT_VISCA_TITLE_BLINK		0		//0:OFF 1:ON
#define DEFAULT_VISCA_TITLE_COLOR		0		//0~06 0:WHITE
#define DEFAULT_VISCA_TITLE_CHAR		0x44

#define	DEFAULT_VISCA_MUTE_ON			0		//0:off 1:on

#define DEFAULT_VISCA_MASK_CL_ON		0		//0:off 1:on CENTER LINE
#define DEFAULT_VISCA_MASK_ON			0		//0:off 1:on MASK ON/OFF
#define DEFAULT_VISCA_MASK_DISP_ON		0		//0:off 1:on DISPLAY
#define DEFAULT_VISCA_MASK_I			0		//0:interlock 1:nonInterlock
#define DEFAULT_VISCA_MASK_TRANS		0		//0:off 1:on
#define DEFAULT_VISCA_MASK_MOSAIC		0		//0:off 1:on
#define DEFAULT_VISCA_MASK_COLOR_ON		0		//0~0xF
#define DEFAULT_VISCA_MASK_COLOR_OFF	0		//0~0xF

#define	DEFAULT_VISCA_CAM_ID_H			0		//0x0~0xFFFF camera id
#define	DEFAULT_VISCA_CAM_ID_L			0

#define DEFAULT_VISCA_MD_ON				0		//0:off 1:on
#define DEFAULT_VISCA_MD_DISP			0		//0:off 1:on
#define DEFAULT_VISCA_MD_THRS_VAL		0		//0x00~0xFF
#define DEFAULT_VISCA_MD_INTERVAL_TIME	0		//0x00~0xFF
#define DEFAULT_VISCA_MD_SRT_H_POS		0		//0x0~0x10
#define DEFAULT_VISCA_MD_SRT_V_POS		0		//0x0~0x8
#define DEFAULT_VISCA_MD_END_H_POS		0		//0x0~0x10
#define DEFAULT_VISCA_MD_END_V_POS		0		//0x0~0x8

#define	DEFAULT_VISCA_CZP_ON			0		//0:off 1:on
#define	DEFAULT_VISCA_CZP_INTERVAL_TIME	0		
#define	DEFAULT_VISCA_CFP_ON			0
#define	DEFAULT_VISCA_CFP_INTERVAL_TIME	0
#define	DEFAULT_VISCA_CE_ON				0		//0:on 1:off
#define	DEFAULT_VISCA_CE_THRS_VAL		0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_Y_HI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_CR_HI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_CB_HI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_Y_LI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_CR_LI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CE_CB_LI			0		//0x00~0x7F
#define	DEFAULT_VISCA_CS_LEVEL			0		//0x0~0x3
#define	DEFAULT_VISCA_CS_SET_VAL		0		//?????????????????????????
#define	DEFAULT_VISCA_COLOR_GAIN		0		//0x0~0xE
#define	DEFAULT_VISCA_COLOR_HUE			0		//0x0~0xE
#define	DEFAULT_VISCA_GAM_OFFSET_P		0
#define	DEFAULT_VISCA_GAM_OFFSET_M		0
#define	DEFAULT_VISCA_EX_EXPCOMP_RESET	0
#define	DEFAULT_VISCA_EX_EXPCOMP_DIRECT	0
#define	DEFAULT_VISCA_EX_EXPAP_RESET	0
#define	DEFAULT_VISCA_EX_EXPAP_DIRECT	0
#define	DEFAULT_VISCA_EX_AICR_ON2OFF	0		//
#define	DEFAULT_VISCA_EX_AICR_OFF2ON	0		//
#define	DEFAULT_VISCA_EX_COLOR_GAIN		0		//0x00~0xFF
#define	DEFAULT_VISCA_EX_COLOR_HUE		0		//0x00~0xFF

#define	DEFAULT_VISCA_COMM_BAUDRATE		0		//9600
#define	DEFAULT_VISCA_MONITORING_MODE	0		//1080/60i
#define	DEFAULT_VISCA_AO_ON				1		//0:off 1:on
#define	DEFAULT_VISCA_DO_ON				1		//0:off 1:on
#define	DEFAULT_VISCA_LVDS_OUT			0		//0:single 1:double
#define	DEFAULT_VISCA_ZWIDE_LIMIT		0		//0x00~0xFF
#define	DEFAULT_VISCA_ZTELE_LIMIT		0		//0x00~0xFF
#define	DEFAULT_VISCA_DZ_MAX			0xEB	//0x00~0xEB
#define	DEFAULT_VISCA_SZOOM_ON			0		//0:off 1:on stable zoom
#define	DEFAULT_VISCA_FTRACE_ON			1		//0:off 1:on
#define	DEFAULT_VISCA_FCS_OFFSET_DOME	0		//
#define	DEFAULT_VISCA_EX_EXPC_ON		0		//0:off 1:on
#define	DEFAULT_VISCA_EX_EXPAP_ON		0		//0:off 1:on
#define	DEFAULT_VISCA_EX_CGCH_ON		0		//0:off 1:on
#define	DEFAULT_VISCA_EX_AICR_F2O_ON	0		//0:off 1:on	//0:off 1:on

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
extern uint08 Preset_memory_set(uint08 number);
extern uint08 Preset_memory_recall(uint08 number);
extern uint08 Preset_memory_reset(uint08 number);

#endif

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
		unsigned						:6;
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
		unsigned	EEP_TEST 			:8;//0x440
		unsigned	GAMMA1				:4;
		unsigned	GAMMA2				:4;
		unsigned	LAST_YGAIN 			:8;
		unsigned	LAST_CGAIN 			:8;
		/*********************************/
		unsigned	AF_OSD 				:8;
		unsigned	BLC_AREA			:8;
		unsigned	COLOR_TEMP			:16;
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
IF_USER_MW_EXT int Interp1D_RoundOff(int32 aiXCur,int32 aiXPos1,int32 aiXPos2,int32 aiYPos1,int32 aiYPos2);
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
