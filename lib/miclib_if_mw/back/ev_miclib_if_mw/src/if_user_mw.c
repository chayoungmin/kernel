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
* 이 파일은 EEPRom, OSD, Protocl 인터페이스를 위한 구성 파일입니다.
*
* !!!!!!!!!!!!!!!!!! 모델별 개발자에 의한 재구성을 원칙으로 합니다. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* 구성
* === 1. VISCA CONDITION	===
* === 2. OSD MENU DEFINE	===
* === 3. INITIAL DEFINE		===
* === 4. LOCAL FUNCTION	: FUNTION OSD	===
* === 5. LOCAL FUNCTION	: VISCA DISPLAY	===
* === 6. LOCAL FUNCTION	: VIACA TITLE	===
* === 7. LOCAL FUNCTION	: KEY CONTROL	===
* === 8. GLOBAL FUNCTION : INITIAL		  ===
* === 9. GLOBAL FUNCTION : MAIN TASK	  ===
* === 10. GLOBAL FUNCTION : EVENT CALLBACK ===
*
**************************************************************************************************************
* Revision History
**************************************************************************************************************
*
*
*
*
*
*************************************************************************************************************/
/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#ifdef WIN32	// for VS9.0
#include <stdio.h>
#include "main.h"
#endif

#ifdef WIN32	// for VS9.0
#include "miclib_type.h"
#include "miclib_if_mw.h"
#include "if_user_mw.h"

#else			// for gcc

#include "miclib_type.h"
#include "miclib_if_mw.h"
#include "if_user_mw.h"
#include "kernel.h"
#include "Param_mw.h"
#include "Osd_drv.h"
#include "Lens_mw.h"
#include "DZoom_mw.h"
#include "Color_mw.h"
#include "Color_mw.h"
#include "app_ae.h"
#include "app_awb.h"
#include "App_af.h"
#include "Uart_drv.h"
#include "prtcl.h"
#include "Exposure_mw.h"
#include "App_privacy.h"
#include "App_zoom_track.h"
#include "image_mw.h"
#include "App_preset.h"
#include "Eep_mw.h"
#endif

#define IF_PROCESS_TICK_MS 100
//디버깅
#define EVENT_TRACE			0	//일어나는 이벤트를 트레이스 합니다.
// 0 : None
// 1 : OSD OUT
// 2 : Debug port OUT
#define COMMAND_CHECK		0	//특수 이벤트가 일어나면 OSD에 메세지를 띄워 줍니다.

#define EVENT_LINE			6	//16~21 -> 총 6LINE 표현 넘어갈시 OSD 침범

/* POSITION */
#define MD_POS_X			26
#define MD_POS_Y			18

//uint08 wtmp[100];			//For EEP_MW TEST ,KSH 140317
//uint08 rtmp[100];			//For EEP_MW TEST ,KSH 140317
#define IF_PROCESS_TICK_3S 30

/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/
typedef enum   {
	OSD_TRACE_NONE,

	OSD_TRACE_COMM,
	//OSD_TRACE_COLORSTAT,
	//OSD_TRACE_MOTION,
	//OSD_TRACE_DNR,
	//OSD_TRACE_WDR,

	//OSD_TRACE_PGAGAIN,
	OSD_TRACE_AESTAT,
	//OSD_TRACE_FOCUSSTAT,
	//OSD_TRACE_HALLADJUST,
	OSD_TRACE_FOCUS1,

	//OSD_TRACE_FOCUS2,
	//OSD_TRACE_ZOOMTRACK,
	//OSD_TRACE_DZOOM,
	//OSD_TRACE_KEYCONTROL,
	//OSD_TRACE_PARE3,

} OSD_DEBUG_PAGE_NUM;
typedef enum _DISPLAY_OSD {
	DISPLAY_ACT,
	DISPLAY_ON,
	DISPLAY_CAMRES,
	DISPLAY_BRIGHT,
	DISPLAY_APERTURE,
	DISPLAY_ZOOM,
	DISPLAY_ICR,
	DISPLAY_P_EFFECT,
	DISPLAY_EXP_COMP,
	DISPLAY_IRIS,
	DISPLAY_GAIN,
	DISPLAY_SHUTTER,
	DISPLAY_BACKLIGHT,
	DISPLAY_MANUAL_FOCUS,
	DISPLAY_FOCUS_MOVE,
	DISPLAY_WB_MODE,
	DISPLAY_LR,
	DISPLAY_FLIP,
	DISPLAY_CAPTURE,
	DISPLAY_ALARM,
	DISPLAY_MEMCUS,
	DISPLAY_MEMCUS_CNT,
	DISPLAY_MAX,
} DISPLAY_OSD;

typedef enum   {
	OSD_HIDE_NONE,
	OSD_HIDE_HALL_ADJ,
	OSD_HIDE_LENS_ADJ,
	OSD_HIDE_DEFECT_ADJ,
	OSD_HIDE_SHADE_ADJ,
	OSD_HIDE_DEFECTLOAD,
	OSD_HIDE_SHADELOAD
} OSD_HIDE_STATE;


KEY_QUE Key_Que;
uint08 mem_addr;
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
* === 2. OSD MENU DEFINE	===
*************************************************************************************************************/
/*************************************************************************************************************
* Hidden Map 정의
*************************************************************************************************************/
/*Trace mode*/
//Sutter Speed
const OSD_ITEM OSD_ShutItem_1080_30p[] = {
	{OSD_STR_1_1, 0},{OSD_STR_1_2, 0},{OSD_STR_1_4, 0},{OSD_STR_1_8, 0},{OSD_STR_1_15, 0},
	{OSD_STR_1_30, 0}, {OSD_STR_1_60, 0}, {OSD_STR_1_90, 0}, {OSD_STR_1_100, 0}, {OSD_STR_1_125, 0},
	{OSD_STR_1_180, 0}, {OSD_STR_1_250, 0}, {OSD_STR_1_350, 0}, {OSD_STR_1_500, 0}, {OSD_STR_1_725, 0},
	{OSD_STR_1_1000, 0}, {OSD_STR_1_1500, 0},	{OSD_STR_1_2000, 0}, {OSD_STR_1_3000, 0}, {OSD_STR_1_4000, 0},
	{OSD_STR_1_6000, 0}, {OSD_STR_1_10000, 0},
	{OSD_STR_FINISH, 0}
};

const OSD_ITEM OSD_ShutItem_1080_25p[] = {
	{OSD_STR_1_1, 0},{OSD_STR_1_2, 0},{OSD_STR_1_3, 0},{OSD_STR_1_6, 0},{OSD_STR_1_12, 0},
	{OSD_STR_1_25, 0}, {OSD_STR_1_50, 0}, {OSD_STR_1_75, 0}, {OSD_STR_1_100, 0}, {OSD_STR_1_120, 0},
	{OSD_STR_1_150, 0}, {OSD_STR_1_215, 0}, {OSD_STR_1_215, 0}, {OSD_STR_1_425, 0}, {OSD_STR_1_600, 0},
	{OSD_STR_1_1000, 0}, {OSD_STR_1_1250, 0}, {OSD_STR_1_1750, 0}, {OSD_STR_1_2500, 0}, {OSD_STR_1_3500, 0},
	{OSD_STR_1_6000, 0}, {OSD_STR_1_10000, 0},
	{OSD_STR_FINISH, 0}
};

const OSD_ITEM OSD_ShutItem_720_60p[] = {
	{OSD_STR_1_1, 0},{OSD_STR_1_2, 0},{OSD_STR_1_4, 0},{OSD_STR_1_8, 0},{OSD_STR_1_15, 0},
	{OSD_STR_1_30, 0}, {OSD_STR_1_60, 0}, {OSD_STR_1_90, 0}, {OSD_STR_1_100, 0}, {OSD_STR_1_125, 0},
	{OSD_STR_1_180, 0}, {OSD_STR_1_250, 0}, {OSD_STR_1_350, 0}, {OSD_STR_1_500, 0}, {OSD_STR_1_725, 0},
	{OSD_STR_1_1000, 0}, {OSD_STR_1_1500, 0},	{OSD_STR_1_2000, 0}, {OSD_STR_1_3000, 0}, {OSD_STR_1_4000, 0},
	{OSD_STR_1_6000, 0}, {OSD_STR_1_10000, 0},
	{OSD_STR_FINISH, 0}
};

const OSD_ITEM OSD_ShutItem_720_50p[] = {
	{OSD_STR_1_1, 0},{OSD_STR_1_2, 0},{OSD_STR_1_3, 0},{OSD_STR_1_6, 0},{OSD_STR_1_12, 0},
	{OSD_STR_1_25, 0}, {OSD_STR_1_50, 0}, {OSD_STR_1_75, 0}, {OSD_STR_1_100, 0}, {OSD_STR_1_120, 0},
	{OSD_STR_1_150, 0}, {OSD_STR_1_215, 0}, {OSD_STR_1_215, 0}, {OSD_STR_1_425, 0}, {OSD_STR_1_600, 0},
	{OSD_STR_1_1000, 0}, {OSD_STR_1_1250, 0}, {OSD_STR_1_1750, 0}, {OSD_STR_1_2500, 0}, {OSD_STR_1_3500, 0},
	{OSD_STR_1_6000, 0}, {OSD_STR_1_10000, 0},
	{OSD_STR_FINISH, 0}
};

const OSD_ITEM OSD_TraceItem[]	  = {{OSD_STR_TR_NONE, 0}, {OSD_STR_TR_COMM, 0}, {OSD_STR_TR_AESTAT, 0}, {OSD_STR_TR_FOCUS1, 0},
									/* {OSD_STR_TR_COLOR_STATE, 0}, {OSD_STR_TR_MOTION, 0}, {OSD_STR_TR_DNR, 0},
									 {OSD_STR_TR_WDR, 0}, {OSD_STR_TR_PGAGAIN, 0},  {OSD_STR_TR_FOCUSSTAT, 0}, {OSD_STR_TR_HALLADJUST, 0},
									  {OSD_STR_TR_FOCUS2, 0}, {OSD_STR_TR_ZOOMTRACK, 0}, {OSD_STR_TR_DZOOM, 0}, {OSD_STR_TR_KEYCONTROL, 0},
									 {OSD_STR_TR_PARE3, 0},*/ {OSD_STR_FINISH, 0}
};

const OSD_MAP OSD_TraceMap[] = {
	{OSD_STR_TR_CHOISE	,UIDX_OSD_DEBUG_STATE	,0	,0	,(OSD_ITEM *)OSD_TraceItem},
	{OSD_STR_INITIAL	,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL				,0	,0	,0	}
};

/* Defect Adj */
const OSD_MAP OSD_SysDefectAdjMap[] = {
	{OSD_STR_THRESHOLD		,IDX_DADJ_THRESHOLD	,255,0	,0},
	{OSD_STR_RUN			,UIDX_DEFECTADJ		,0	,0	,0}, // IFEVT_DEFECTADJ
	{OSD_STR_LOAD			,UIDX_DEFECTLOAD	,0	,0	,0}, // 데이터 복구
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0}
};

/* Shade Adj */
const OSD_MAP OSD_SysShadeAdjMap[] = {
	{OSD_STR_GAIN_LEVEL		,IDX_SADJ_GAIN		,100,0	,0	},
//	{OSD_STR_OFFSET			,IDX_SADJ_GAIN		,255,0	,0	},
	{OSD_STR_RUN			,UIDX_SHADEADJ		,0	,0	,0	},	// IFEVT_SHADEADJ
	{OSD_STR_LOAD			,UIDX_SHADELOAD		,0	,0	,0	},	// 데이터 복구
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* Privacy Adj */
const OSD_ITEM OSD_3DZoomItem[]	  = {{OSD_STR_ZOOM_IN_OUT, 0},{OSD_STR_FINISH, 0}};

OSD_MAP OSD_SysPrivacyAdjMap[] = {
	{OSD_STR_X_AXIS			,UIDX_PRI_ADJ_X			,200,0	,0							},
	{OSD_STR_Y_AXIS			,UIDX_PRI_ADJ_Y			,200,0	,0							},
	{OSD_STR_ZOOM			,UIDX_3DPRI_ZOOM		,0	,0	,(OSD_ITEM *)OSD_3DZoomItem},
	{OSD_STR_INITIAL		,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL				,0	,0	,0	}
};

/* System adj */
const OSD_MAP OSD_SystemAdjMap[] = {
	{OSD_STR_HALL_ADJ		,UIDX_HALLADJ	,0	,0								,0	},
	{OSD_STR_LENS_ADJ		,UIDX_LENSADJ	,0	,0								,0	},
	{OSD_STR_DEFECT_ADJ		,UIDX_DEFEC_IN	,0	,(OSD_MAP *)OSD_SysDefectAdjMap	,0	},
	{OSD_STR_SHADE_ADJ		,UIDX_SHADE_IN	,0	,(OSD_MAP *)OSD_SysShadeAdjMap	,0	},
	{OSD_STR_PRIVACY_ADJ	,UIDX_3DPRI_ADJ	,0	,(OSD_MAP *)OSD_SysPrivacyAdjMap,0	},
	{OSD_STR_RETURN			,IDX_RETURN		,0	,0								,0	},
	{OSD_STR_FINISH			,IDX_NULL		,0	,0								,0	}
};

/* Aging */
const OSD_ITEM OSD_AgingItem[]	 = {{OSD_STR_STOP, 0}, {OSD_STR_START, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_AgTraveItem[] = {{OSD_STR_TR_PARE3, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_AgingMap[] = {
	{OSD_STR_AGING		,UIDX_AGING_STATE	,0	,0	,(OSD_ITEM *)OSD_AgingItem},
	{OSD_STR_MODE		,UIDX_AGING_MODE	,3	,0	,0	},
	{OSD_STR_GO_TRACE	,UIDX_TEMP_1		,0	,0	,(OSD_ITEM *)OSD_AgTraveItem},	// 트레이스 3번으로 진입한다.
	{OSD_STR_RETURN		,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL			,0	,0	,0	}
};


/*
//Tunning Detect DBDR
const OSD_ITEM OSD_DBDRModeItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};


const OSD_MAP OSD_DeteckDBDRMap[] = {
	{OSD_STR_DISPLAY	,UIDX_DBDR_MODE			,0	,0	,(OSD_ITEM *)OSD_DBDRModeItem},
	{OSD_STR_X_POS		,UIDX_WINDOW_START_X	,100,0	,0	},
	{OSD_STR_Y_POS		,UIDX_WINDOW_WIDE		,100,0	,0	},
	{OSD_STR_WIDTH		,UIDX_WINDOW_START_Y	,100,0	,0	},
	{OSD_STR_HEIGHT		,UIDX_WINDOW_HEIGHT		,100,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL				,0	,0	,0	}
};
*/
const OSD_ITEM OSD_GammaTune[] = {{OSD_STR_0_30, 0}, {OSD_STR_0_35, 0},
							 	 {OSD_STR_0_40, 0}, {OSD_STR_0_45, 0},
							  	 {OSD_STR_0_50, 0}, {OSD_STR_0_55, 0},
							 	 {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_DeteckDBDRMap[] = {
	{OSD_STR_GAMMA1		,UIDX_GAMMA1			,0		,0	,(OSD_ITEM *)OSD_GammaTune},
	{OSD_STR_GAMMA2		,UIDX_GAMMA2			,0		,0	,(OSD_ITEM *)OSD_GammaTune},
	{OSD_STR_LAST_YGAIN	,UIDX_LAST_YGAIN		,0xff	,0	,0	},
	{OSD_STR_LAST_CGAIN	,UIDX_LAST_CGAIN		,0xff	,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL			,0		,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN				,0		,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL				,0		,0	,0	}
};

/* Tunning Adj Color*/
const OSD_MAP OSD_AdjColor[] = {
	{OSD_STR_B_GAIN_P	,UIDX_B_GAIN_P		,255,0	,0	},
	{OSD_STR_B_GAIN_N	,UIDX_B_GAIN_N		,255,0	,0	},
	{OSD_STR_R_GAIN_P	,UIDX_R_GAIN_P		,255,0	,0	},
	{OSD_STR_R_GAIN_N	,UIDX_R_GAIN_N		,255,0	,0	},
	{OSD_STR_B_HUE_P	,UIDX_B_HUE_P		,255,0	,0	},
	{OSD_STR_B_HUE_N	,UIDX_B_HUE_N		,255,0	,0	},
	{OSD_STR_R_HUE_P	,UIDX_R_HUE_P		,255,0	,0	},
	{OSD_STR_R_HUE_N	,UIDX_R_HUE_N		,255,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL			,0	,0	,0	}
};

/* Tunning Detect DBDR*/

OSD_MAP OSD_AdjAEAFMap[] = {
	{OSD_STR_AF_SENS		,IDX_NULL				,100,0	,0	},
	{OSD_STR_IRIS_JUMP		,UIDX_IRIS_JUMP			,200,0	,0	},	// 550-750
	{OSD_STR_MAX_SHUTTER	,UIDX_AUTO_MIN_SHUTTER	,0	,0	,(OSD_ITEM *)OSD_ShutItem_720_60p},
	{OSD_STR_MIN_SHUTTER	,UIDX_AUTO_MAX_SHUTTER	,0	,0	,(OSD_ITEM *)OSD_ShutItem_720_60p},
	{OSD_STR_INITIAL		,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL				,0	,0	,0	}
};


/* Tunning Video Position*/
const OSD_MAP OSD_VideoPosMap[] = {
	{OSD_STR_H_SIZE				,UIDX_H_SIZE			,255,0	,0	},	// 2640-2700
	{OSD_STR_H_START			,UIDX_H_START			,255,0	,0	}, // 300
	{OSD_STR_H_END				,UIDX_H_END				,255,0	,0	}, // 1900-2200
	{OSD_STR_V_TOTAL_SIZE		,UIDX_V_TOTAL_SIZE		,255,0	,0	}, // 0x645 +- 100
	{OSD_STR_V_ACT_START		,UIDX_V_ACT_START		,255,0	,0	}, // 0x17 ~+ 100
	{OSD_STR_V_ACT_END			,UIDX_V_ACT_END			,255,0	,0	}, // 0x44f +- 100
	{OSD_STR_V_ACT_START_BOT	,UIDX_V_ACT_START_BOT	,255,0	,0	}, // 600
	{OSD_STR_V_ACT_END_BOT		,UIDX_V_ACT_END_BOT		,255,0	,0	}, // 1200
	{OSD_STR_INITIAL			,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN				,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH				,IDX_NULL				,0	,0	,0	}
};

/* Tunning Color Bar*/
const OSD_ITEM OSD_OnOff[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_ITEM OSD_ColorBarItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_MAP OSD_ColorBarMap[] = {
	{OSD_STR_COLOR_BAR			,UIDX_COLOR_BAR		,0	,0	,(OSD_ITEM *)OSD_ColorBarItem},
	{OSD_STR_MAIN_IN			,UIDX_MAIN_IN		,0	,0	,(OSD_ITEM *)OSD_ColorBarItem},
	{OSD_STR_MAIN_OUT			,UIDX_MAIN_OUT		,0	,0	,(OSD_ITEM *)OSD_ColorBarItem},
	{OSD_STR_AUX_OUT			,UIDX_AUX_OUT		,0	,0	,(OSD_ITEM *)OSD_ColorBarItem},
	{OSD_STR_VIDEO_ENCODER		,UIDX_VIDEO_ENCODER	,0	,0	,(OSD_ITEM *)OSD_ColorBarItem},
	{OSD_STR_INITIAL			,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN				,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH				,IDX_NULL			,0	,0	,0	}
};
/* Tunning */
const OSD_MAP OSD_DeteckExp[] = {
	//{OSD_STR_IRIS_LEVEL			,PRM_IRIS_LV	,1000	,0	,0	},
	//{OSD_STR_HALL_MAX			,PRM_HALL_MAX	,1000	,0	,0	},
	//{OSD_STR_HALL_MIN			,PRM_HALL_MIN	,1000	,0	,0	},
	//{OSD_STR_INITIAL			,IDX_INITIAL	,0		,0	,0	},


	//{OSD_STR_IRIS_ADJ_ON			,UIDX_IRIS_ADJ_ON			,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	//{OSD_STR_IRIS_ADJ_AE_DISBLE 	,UIDX_IRIS_ADJ_AE_DISBLE	,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	//{OSD_STR_NULL 				,IDX_NULL					,0	,0	,0	},
	//{OSD_STR_IRIS_ADJ_SUM 		,UIDX_IRIS_ADJ_SUM			,0xFFFF	,0	,0	},
	//{OSD_STR_IRIS_ADJ_SUM 		,UIDX_IRIS_ADJ_SUM2			,0x3FF	,0	,0	},
	//{OSD_STR_NULL 				,IDX_NULL					,0	,0	,0	},
	//{OSD_STR_IRIS_ADJ_IRIS_VAL		,UIDX_IRIS_ADJ_IRIS_VAL 	,0x3FF	,0	,0	},
	//{OSD_STR_IRIS_ADJ_SHUT_VAL		,UIDX_IRIS_ADJ_SHUT_VAL 	,0x5FF	,0	,0	},
	//{OSD_STR_IRIS_ADJ_GAIN_VAL		,UIDX_IRIS_ADJ_GAIN_VAL 	,0x3FF	,0	,0	},
	//{OSD_STR_NULL 				,IDX_NULL					,0	,0		,0	},
	//{OSD_STR_IRIS_ADJ_RESET			,UIDX_IRIS_ADJ_RESET		,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	//{OSD_STR_IRIS_ADJ_SW2 		,UIDX_IRIS_ADJ_SW2			,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	//{OSD_STR_NULL 				,IDX_NULL					,0	,0	,0	},

	{OSD_STR_ADJUST			,UIDX_IRIS_ADJ_ON			,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	{OSD_STR_STATE 			,UIDX_IRIS_ADJ_AE_DISBLE	,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	{OSD_STR_NULL 			,IDX_NULL					,0	,0	,0	},
	{OSD_STR_LEVEL 			,UIDX_IRIS_ADJ_SUM			,0xFFFFFFFF	,0	,0	},
	{OSD_STR_LEVEL 			,UIDX_IRIS_ADJ_SUM2			,0x3FF	,0	,0	},
	{OSD_STR_NULL 			,IDX_NULL					,0	,0	,0	},
	{OSD_STR_IRIS_LEVEL		,UIDX_IRIS_ADJ_IRIS_VAL 	,0x3FF	,0	,0	},
	{OSD_STR_SHUT_SPEED		,UIDX_IRIS_ADJ_SHUT_VAL 	,0x5FF	,0	,0	},
	{OSD_STR_DSS			,UIDX_IRIS_ADJ_DSS_VAL 		,0x100	,0	,0	},
	{OSD_STR_GAIN_LEVEL		,UIDX_IRIS_ADJ_GAIN_VAL 	,0x3FF	,0	,0	},
	{OSD_STR_NULL 			,IDX_NULL					,0	,0		,0	},
	{OSD_STR_RESET_ZONE		,UIDX_IRIS_ADJ_RESET		,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	{OSD_STR_POS 			,UIDX_IRIS_ADJ_SW2			,0	,0	,(OSD_ITEM *)OSD_OnOff	},
	{OSD_STR_NULL 			,IDX_NULL					,0	,0	,0	},

	{OSD_STR_RETURN				,IDX_RETURN		,0		,0	,0	},
	{OSD_STR_FINISH				,IDX_NULL		,0		,0	,0	}
};

/* Tunning */
const OSD_MAP OSD_EEP_TEST[] = {
	{OSD_STR_START			,UIDX_EEP_ADDRESS			,0xFFFF	,0	,0	},
	{OSD_STR_SAVE_YES		,UIDX_EEP_TEST_START		,16		,0	,0	},
	{OSD_STR_NULL 			,IDX_NULL					,0		,0	,0	},
	{OSD_STR_RESET_ZONE		,UIDX_EEP_TEST_REFRESH		,0		,0	,0	},
	{OSD_STR_NULL 			,IDX_NULL					,0		,0	,0	},

	{OSD_STR_RETURN			,IDX_RETURN					,0		,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL					,0		,0	,0	}
};

/* Tunning */
const OSD_MAP OSD_TunningMap[] = {
	{OSD_STR_EXPOSURE			,UIDX_TNN_EXPOSURE 	,0	,(OSD_MAP *)OSD_DeteckExp		,0	},
	//{OSD_STR_TUNNIG			,UIDX_TNN_EEP		,0	,(OSD_MAP *)OSD_EEP_TEST		,0	},	//For EEP_MW TEST ,KSH 140317
	//{OSD_STR_DETECT_DBDR		,IDX_NULL			,0	,(OSD_MAP *)OSD_DeteckDBDRMap	,0	},
	{OSD_STR_LOW_ILLUMINATION	,IDX_NULL			,0	,(OSD_MAP *)OSD_DeteckDBDRMap	,0	},
	{OSD_STR_ADJUST_COLOR		,IDX_NULL			,0	,(OSD_MAP *)OSD_AdjColor		,0	},
	{OSD_STR_ADJUST_AE_AF		,IDX_NULL			,0	,(OSD_MAP *)OSD_AdjAEAFMap		,0	},
	{OSD_STR_VIDEO_POSITION		,IDX_NULL			,0	,(OSD_MAP *)OSD_VideoPosMap		,0	},
	{OSD_STR_COLOR_BAR			,IDX_NULL			,0	,(OSD_MAP *)OSD_ColorBarMap		,0	},
	{OSD_STR_RETURN				,IDX_RETURN			,0	,0								,0	},
	{OSD_STR_FINISH				,IDX_NULL			,0	,0								,0	}
};

/* Product Config */
const OSD_ITEM OSD_CfgPrtclItem[] = {{OSD_STR_CNB_H, 0}, {OSD_STR_PELCO_D, 0}, {OSD_STR_PELCO_P, 0}, {OSD_STR_VISCA, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_CfgBaudItem[] = {{OSD_STR_2400, 0}, {OSD_STR_4800, 0}, {OSD_STR_9600, 0}, {OSD_STR_19200, 0}, {OSD_STR_38400, 0}, {OSD_STR_57600, 0}, {OSD_STR_115200, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_CfgSVBSItem[] = {{OSD_STR_SDTV, 0}, {OSD_STR_HDTV, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_CfgCBCRItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_CfgOSDTypeItem[] = {{OSD_STR_SYSTEM, 0}, {OSD_STR_NORMAL, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_CfgCamClassItem[] = {{OSD_STR_SET, 0}, {OSD_STR_MODULE, 0}, {OSD_STR_POLICE, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_ProductCfgMap[] = {
	{OSD_STR_PROTOCOL		,UIDX_PRTCL_TYPE	,0	,0	,(OSD_ITEM *)OSD_CfgPrtclItem	},
	{OSD_STR_VISCA_OSD_TYPE	,UIDX_VISCA_OSD_MENU,0	,0	,(OSD_ITEM *)OSD_CfgOSDTypeItem },
	{OSD_STR_CAMERA_ID		,IDX_CAM_ID			,255,0	,0	},
	{OSD_STR_BAUDRATE		,IDX_BAUDRATE		,0	,0	,(OSD_ITEM *)OSD_CfgBaudItem	},
	//{OSD_STR_CAM_CLASS		,IDX_CAM_CLASS		,0	,0	,(OSD_ITEM *)OSD_CfgCamClassItem},
	{OSD_STR_CVBS_MODE		,UIDX_CVBS_MODE		,0	,0	,(OSD_ITEM *)OSD_CfgSVBSItem	},
	{OSD_STR_CBCR_SWAP		,UIDX_CBCR_SWAP		,0	,0	,(OSD_ITEM *)OSD_CfgCBCRItem	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* System Info */
const OSD_ITEM OSD_FupdateItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_FwareUpdateMap[] = {
	{OSD_STR_UPDATE_MODE1	,UIDX_FIRMWARE_UPDATEMODE_1	,0	,0	,(OSD_ITEM *)OSD_FupdateItem},
	{OSD_STR_UPDATE_MODE2	,UIDX_FIRMWARE_UPDATEMODE_2	,0	,0	,(OSD_ITEM *)OSD_FupdateItem},
	{OSD_STR_UPDATE_MODE3	,UIDX_FIRMWARE_UPDATEMODE_3	,0	,0	,(OSD_ITEM *)OSD_FupdateItem},
	{OSD_STR_UPDATE_START	,IDX_NULL					,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN					,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL					,0	,0	,0	}
};

/* System Info */
const OSD_MAP OSD_SysInfoMap[] = {
	{OSD_STR_VERSION,			IDX_NULL,	0, 0,					0},
	{OSD_STR_DATE,				IDX_NULL,	0, 0,					0},
	{OSD_STR_TIME,				IDX_NULL,	0, 0,					0},
	{OSD_STR_FIRMWARE_UPDATE,	IDX_NULL,	0, (OSD_MAP *)OSD_FwareUpdateMap,	0},
	{OSD_STR_RETURN,			IDX_RETURN, 0, 0,					0},
	{OSD_STR_FINISH, IDX_NULL, 0, 0, 0}
};

/* Hidden MENU */
const OSD_MAP OSD_gHiddenMap[] = {
	{OSD_STR_TRACE,			IDX_NULL,	0,	(OSD_MAP *)OSD_TraceMap,		0},
	{OSD_STR_SYSTEM_ADJ,	IDX_NULL,	0,	(OSD_MAP *)OSD_SystemAdjMap,	0},
	{OSD_STR_AGING,			IDX_NULL,	0,	(OSD_MAP *)OSD_AgingMap,		0},
	{OSD_STR_TUNNIG,		IDX_NULL,	0,	(OSD_MAP *)OSD_TunningMap,		0},
	{OSD_STR_PRODUCT_CFG,	IDX_NULL,	0,	(OSD_MAP *)OSD_ProductCfgMap,	0},
	{OSD_STR_SYSTEM_INFO,	IDX_NULL,	0,	(OSD_MAP *)OSD_SysInfoMap,		0},
	{OSD_STR_REBOOT,		IDX_REBOOT,	0,	0,					0},
	{OSD_STR_EXIT,			IDX_EXIT,	0,	0,					0},
	{OSD_STR_FINISH, IDX_NULL, 0, 0, 0}
};

/*************************************************************************************************************
* OSD Map 정의
*************************************************************************************************************/
/* DZoom */
const OSD_MAP OSD_DZoomMap [] = {
	{OSD_STR_DZOOM,		IDX_DZOOM_MAG,	110,0, 0},
	{OSD_STR_NULL,		IDX_NULL,		0,	0, 0},
	{OSD_STR_INITIAL,	IDX_INITIAL,	0,	0, 0},
	{OSD_STR_RETURN,	IDX_RETURN,		0,	0, 0},
	{OSD_STR_FINISH,	IDX_NULL,		0,	0, 0}
};

/* LensReflesh */
const OSD_ITEM OSD_days[] = {	{OSD_STR_DAY1, 0},	{OSD_STR_DAY2, 0},	{OSD_STR_DAY3, 0},	{OSD_STR_DAY4, 0},	{OSD_STR_DAY5, 0},
								{OSD_STR_DAY6, 0},	{OSD_STR_DAY7, 0},	{OSD_STR_FINISH, 0}	};

const OSD_MAP OSD_DLensRefMap [] = {
	{OSD_STR_DAY,		IDX_LENS_REFRESH_DAYS,	0, 0, (OSD_ITEM *)OSD_days},
	{OSD_STR_NULL,		IDX_NULL,				0, 0, 0},
	{OSD_STR_INITIAL,	IDX_INITIAL, 			0, 0, 0},
	{OSD_STR_RETURN,	IDX_RETURN,				0, 0, 0},
	{OSD_STR_FINISH,	IDX_NULL, 				0, 0, 0}
};
/* FOCUS AUTO MODE*/
const OSD_ITEM OSD_FcsAutoItem[] = {{OSD_STR_NORMAL, 0},{OSD_STR_INTERVAL, 0},{OSD_STR_TRIGER, 0},{OSD_STR_FINISH, 0}};

const OSD_MAP OSD_FcsAutoMap[] = {
	{OSD_STR_AF_MODE,			IDX_AF_MODE	,0	,0	,(OSD_ITEM *)OSD_FcsAutoItem},
	{OSD_STR_INITIAL,			IDX_INITIAL	,0	,0	,0},
	{OSD_STR_RETURN,			IDX_RETURN	,0	,0	,0},
	{OSD_STR_FINISH,			IDX_NULL	,0	,0	,0	}
};


/* FOCUS */
const OSD_ITEM OSD_FocusItem[] = {{OSD_STR_AUTO, (OSD_MAP *)OSD_FcsAutoMap}, {OSD_STR_MANUAL_PUSH, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DistItem[] = {{OSD_STR_1CM, 0}, {OSD_STR_10CM, 0}, {OSD_STR_50CM, 0}, {OSD_STR_1M, 0},{OSD_STR_3M, 0},
								 {OSD_STR_5M, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ZModeItem[] = {{OSD_STR_COMBINE, 0}, {OSD_STR_SEPARATE, 0}, {OSD_STR_FINISH, 0}};
OSD_ITEM OSD_DZModeItem[] = { {OSD_STR_OFF, 0},{OSD_STR_ON, (OSD_MAP *)OSD_DZoomMap}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ZTrkModeItem[] = {{OSD_STR_AUTO, 0}, {OSD_STR_MANUAL, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_LensRefreshItem[] = {	{OSD_STR_OFF, 0},	{OSD_STR_AUTO, (OSD_MAP *)OSD_DLensRefMap},	{OSD_STR_PUSH, 0},	{OSD_STR_FINISH, 0}};

const OSD_MAP OSD_FocusMap[] = {
	{OSD_STR_FOCUS_MODE		,IDX_FOCUS_MODE			,0	,0	,(OSD_ITEM *)OSD_FocusItem},
	{OSD_STR_DIST			,IDX_FOCUS_DIST			,0	,0	,(OSD_ITEM *)OSD_DistItem},
	{OSD_STR_ZOOM_MODE		,IDX_ZOOM_MODE			,0	,0	,(OSD_ITEM *)OSD_ZModeItem},
	{OSD_STR_DZOOM_MODE		,IDX_DZOOM_MODE			,0	,0	,(OSD_ITEM *)OSD_DZModeItem},
	{OSD_STR_ZOOM_TRK_MODE	,IDX_ZTRK_MODE			,0	,0	,(OSD_ITEM *)OSD_ZTrkModeItem},
	{OSD_STR_ZOOM_SPEED		,IDX_ZOOM_SPEED			,7	,0	,0	},
	{OSD_STR_LENS_REFRESH	,IDX_LENS_REFRESH_MODE	,0	,0	,(OSD_ITEM *)OSD_LensRefreshItem},
	{OSD_STR_NULL			,IDX_NULL				,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN				,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL				,0	,0	,0	}
};

/* Exposure */
const OSD_MAP OSD_ExposureBrightMap[] = {
	{OSD_STR_LEVEL		,IDX_AEM_BRIGHT_STEP ,25,0 	,0	},
	{OSD_STR_NULL		,IDX_NULL			 ,0	,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL		 ,0	,0 	,0	},
	{OSD_STR_RETURN		,IDX_RETURN			 ,0	,0 	,0	},
	{OSD_STR_FINISH		,IDX_NULL			 ,0	,0 	,0	}
};

const OSD_MAP OSD_ExposureIrisMap[] = {
	{OSD_STR_IRIS_LEVEL,	IDX_AEM_IRIS_STEP ,100	,0	,0 },
	{OSD_STR_NULL,			IDX_NULL		  ,0	,0	,0 },
	{OSD_STR_INITIAL,		IDX_INITIAL		  ,0	,0	,0 },
	{OSD_STR_RETURN,		IDX_RETURN		  ,0	,0	,0 },
	{OSD_STR_FINISH, IDX_NULL, 0, 0, 0}
};


OSD_MAP OSD_ExposureShutMap[] = {
	{OSD_STR_SHUT_SPEED,	IDX_AEM_SHUT_STEP	,0	,0	,(OSD_ITEM *)OSD_ShutItem_720_60p},
	{OSD_STR_NULL,			IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL,		IDX_INITIAL			,0	,0	,0	},
	{OSD_STR_RETURN,		IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH,		IDX_NULL			,0	,0	,0	}
};

OSD_MAP OSD_ExposureManualMap[] = {
	{OSD_STR_IRIS_LEVEL,	IDX_AEM_IRIS_STEP	,100	,0	, 0},
	{OSD_STR_SHUT_SPEED,	IDX_AEM_SHUT_STEP	,0		,0	, (OSD_ITEM *)OSD_ShutItem_720_60p},
	{OSD_STR_GAIN_LEVEL,	IDX_AEM_GAIN_STEP	,100	,0	, 0}, //Exposure에 Gain Lv이 없다.
	{OSD_STR_NULL,			IDX_NULL			,0		,0	, 0},
	{OSD_STR_INITIAL,		IDX_INITIAL			,0		,0	, 0},
	{OSD_STR_RETURN,		IDX_RETURN			,0		,0	, 0},
	{OSD_STR_FINISH,		IDX_NULL			,0		,0	, 0}
};

const OSD_ITEM OSD_AEModeItem[] ={	{OSD_STR_AUTO, 0}, {OSD_STR_MANUAL, (OSD_MAP *)OSD_ExposureManualMap}, {OSD_STR_SHUT_PRIORITY, (OSD_MAP *)OSD_ExposureShutMap}, {OSD_STR_IRIS_PRIORITY, (OSD_MAP *)OSD_ExposureIrisMap},
									{OSD_STR_BRIGHT, (OSD_MAP *)OSD_ExposureBrightMap}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_AgcLimitItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_LOW, 0}, {OSD_STR_MIDDLE, 0}, {OSD_STR_HIGH, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DssItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_X2, 0}, {OSD_STR_X4, 0}, {OSD_STR_X8, 0}, {OSD_STR_X16, 0}, {OSD_STR_X32, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_AflkItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_ExposureMap[] = {
	{OSD_STR_BRIGHTNESS,	IDX_AE_TGT_BRIGHT	,100	,0	,0},
	{OSD_STR_AE_MODE,		IDX_AE_MODE			,0		,0	,(OSD_ITEM *)OSD_AEModeItem},
	{OSD_STR_AGC_LIMIT,		IDX_AE_AGC_LIMIT	,0		,0	,(OSD_ITEM *)OSD_AgcLimitItem},
	{OSD_STR_DSS,			IDX_AE_DSS_STEP		,0		,0	,(OSD_ITEM *)OSD_DssItem},
	{OSD_STR_AFLK,			IDX_AE_FLK_MODE		,0		,0	,(OSD_ITEM *)OSD_AflkItem},
	//{OSD_STR_NULL,			IDX_NULL			,0		,0	,0	},
	//{OSD_STR_AE_SPOT_MODE		,UIDX_SPOT_AE		,1		,0	,0	},
	//{OSD_STR_AE_SPOT_X			,UIDX_SPOT_AE_POS_X	,15		,0	,0	},
	//{OSD_STR_AE_SPOT_Y			,UIDX_SPOT_AE_POS_Y	,15		,0	,0	},
	//{OSD_STR_AE_RESPONSE_SPEED	,UIDX_AE_RESPONS		,0x2F	,0	,0	},
	{OSD_STR_NULL,			IDX_NULL			,0		,0	,0	},
	{OSD_STR_INITIAL,		IDX_INITIAL			,0		,0	,0	},
	{OSD_STR_RETURN,		IDX_RETURN			,0		,0	,0	},
	{OSD_STR_FINISH,		IDX_NULL			,0		,0	,0	}
};

/* WB */
const OSD_ITEM OSD_WbAtwItem[] = {{OSD_STR_INDOOR, 0}, {OSD_STR_OUTDOOR, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_WbAtwMap[] = {
	{OSD_STR_MODE		,IDX_WB_ENV		,0	,0	,(OSD_ITEM *)OSD_WbAtwItem},
	{OSD_STR_NULL		,IDX_NULL		,0	,0	,0},
	{OSD_STR_INITIAL	,IDX_INITIAL	,0	,0	,0},
	{OSD_STR_RETURN		,IDX_RETURN		,0	,0	,0},
	{OSD_STR_FINISH		,IDX_NULL		,0	,0	,0}
};
const OSD_ITEM OSD_WbPush[] = {{OSD_STR__PUSH, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_WbManualMap[] = {
	{OSD_STR_RED_GAIN		,IDX_WB_RED_GAIN	,100 ,0	,0	},
	{OSD_STR_BLUE_GAIN		,IDX_WB_BLUE_GAIN	,100 ,0	,0	},
	//{OSD_STR_PUSH			,UIDX_WB_PUSH		,0	 ,0	,(OSD_ITEM *)OSD_WbPush},
	//{OSD_STR_COLOR_TEMP		,UIDX_WB_COLOR_TEMP	,40	 ,0	,0	},
	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* DAY/NIGHT */
const OSD_ITEM OSD_DBDlyItem[] = {	{OSD_STR_1SEC, 0},	{OSD_STR_5SEC, 0},	{OSD_STR_10SEC, 0},	{OSD_STR_20SEC, 0},	{OSD_STR_30SEC, 0}, {OSD_STR_60SEC, 0},	{OSD_STR_10MIN, 0},	{OSD_STR_FINISH, 0}	};

const OSD_MAP OSD_DNMAP[] = {
	{OSD_STR_CHANGE_LEVEL	,IDX_DN_CHG_STEP	,10	,0	,0	},
	{OSD_STR_DELAY_TIME		,IDX_DN_CHG_TIME	,0	,0	,(OSD_ITEM *)OSD_DBDlyItem},

	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* IMAGE Adjust */
const OSD_MAP OSD_ImgAdjustMap[] = {
	{OSD_STR_BRIGHT			,IDX_IMG_BRIGHT		,100,0	,0	},
	{OSD_STR_CONTRAST		,IDX_IMG_CONTRAST	,100,0	,0	},
	{OSD_STR_SHARPNESS		,IDX_IMG_SHARPNESS	,100,0	,0	},
	{OSD_STR_CHROMA			,IDX_IMG_CHROMA		,100,0	,0	},
	{OSD_STR_HUE			,IDX_IMG_HUE		,100,0	,0	},
	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* GAMMA USER */
const OSD_ITEM OSD_GammaItem[] = {	{OSD_STR_0_30, 0},	{OSD_STR_0_35, 0},	{OSD_STR_0_40, 0}, {OSD_STR_0_45, 0}, {OSD_STR_0_50, 0},
								  	{OSD_STR_0_55, 0},	{OSD_STR_0_60, 0},	{OSD_STR_0_65, 0}, {OSD_STR_0_70, 0}, {OSD_STR_0_75, 0},
								  	{OSD_STR_0_80, 0},	{OSD_STR_0_85, 0},	{OSD_STR_FINISH, 0}	};

const OSD_MAP OSD_GammaUserMap[] = {
	{OSD_STR_USER			,IDX_IMG_GAMMA_STEP	,0	,0	,(OSD_ITEM *)OSD_GammaItem},
	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0}
};

/* IMAGE */
const OSD_ITEM OSD_ImgFlipItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_H_FLIP, 0}, {OSD_STR_V_FLIP, 0}, {OSD_STR_VH_FLIP, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ImgFreezItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ImgColorItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ImgShadingItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_ImgGammaItem[] = {{OSD_STR_CRT, 0}, {OSD_STR_LCD, 0}, {OSD_STR_USER, (OSD_MAP *)OSD_GammaUserMap}, {OSD_STR_FINISH, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_ImageMap[] = {
	{OSD_STR_ADJUST			,IDX_NULL			,0	,(OSD_MAP *)OSD_ImgAdjustMap	,0	},
	{OSD_STR_FLIP			,IDX_IMG_FLIP		,0	,0								,(OSD_ITEM *)OSD_ImgFlipItem},
	{OSD_STR_FREEZE			,IDX_IMG_FREEZE		,0	,0								,(OSD_ITEM *)OSD_ImgFreezItem},
	{OSD_STR_COLOR			,IDX_IMG_COLOR		,0	,0								,(OSD_ITEM *)OSD_ImgColorItem},
	{OSD_STR_SHADING		,IDX_IMG_SHADING	,0	,0								,(OSD_ITEM *)OSD_ImgShadingItem},
	{OSD_STR_GAMMA			,IDX_IMG_GAM_MODE	,0	,0								,(OSD_ITEM *)OSD_ImgGammaItem},

	{OSD_STR_NULL			,IDX_NULL			,0	,0								,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0								,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0								,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0								,0	}
};

/* BLC */
const OSD_ITEM OSD_BLCLvItem[] = {{OSD_STR_LOW, 0}, {OSD_STR_MIDDLE, 0}, {OSD_STR_HIGH, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_BLCMap[] = {
	{OSD_STR_LEVEL		,IDX_BLC_LEVEL	,0	,0	,(OSD_ITEM *)OSD_BLCLvItem	},
	{OSD_STR_NULL		,IDX_NULL		,0	,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL	,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN		,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL		,0	,0	,0	}
};

/* WDR */
const OSD_ITEM OSD_WDRLvItem[] = {{OSD_STR_LOW, 0}, {OSD_STR_MIDDLE, 0}, {OSD_STR_HIGH, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_AeAceItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_LOW, 0}, {OSD_STR_MIDDLE, 0}, {OSD_STR_HIGH, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_WDRMap[] = {
	{OSD_STR_LEVEL		,IDX_WDR_LEVEL	,0	,0	,(OSD_ITEM *)OSD_WDRLvItem},
	{OSD_STR_ACE		,UIDX_AE_ACE	,0	,0	,(OSD_ITEM *)OSD_AeAceItem},
	{OSD_STR_NULL		,IDX_NULL		,0	,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL	,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN		,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL		,0	,0	,0	}
};

/* HLC */
const OSD_ITEM OSD_HLCColorItem[] = {{OSD_STR_BLACK, 0}, {OSD_STR_GRAY, 0},{OSD_STR_FINISH, 0}};
//{{OSD_STR_WHITE, 0}, {OSD_STR_YELLOW, 0}, {OSD_STR_CYAN, 0}, {OSD_STR_GREEN, 0}, {OSD_STR_MAGENTA, 0}, {OSD_STR_RED, 0}, {OSD_STR_BLUE, 0}, {OSD_STR_BLACK, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_HLCMap[] = {
	{OSD_STR_LEVEL		,IDX_HLC_LEVEL		,100,0	,0	},
	{OSD_STR_COLOR		,IDX_HLC_MASK_COLOR	,0	,0	,(OSD_ITEM *)OSD_HLCColorItem	},
	{OSD_STR_NULL		,IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL	,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN		,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH		,IDX_NULL			,0	,0	,0	}
};

/* DNR */
const OSD_ITEM OSD_DNRLvItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_LOW, 0}, {OSD_STR_MIDDLE, 0}, {OSD_STR_HIGH, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DNRGMtnItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_DNRMap[] = {
	{OSD_STR_LEVEL			,IDX_DNR_MODE		,0	,0	,(OSD_ITEM *)OSD_DNRLvItem	},
	{OSD_STR_GLOBAL_MOTION	,IDX_DNR_GLB_MOT	,0	,0	,(OSD_ITEM *)OSD_DNRGMtnItem},
	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

/* Spacial */
const OSD_ITEM OSD_MdStateItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON 	, 0}, {OSD_STR_FINISH, 0}	};
const OSD_ITEM OSD_MdBlockItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_TEXT , 0}, {OSD_STR_IMG	 , 0}, {OSD_STR_ALL_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_MdAlarmItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON 	, 0}, {OSD_STR_FINISH, 0}	};//{OSD_STR_PORT_ON , 0},{OSD_STR_COMM_ON, 0}, {OSD_STR_ALL_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_MotionMap[] = {
	{OSD_STR_ZONE			,IDX_MD_ZONE		,3	,0	,0	},
	{OSD_STR_STATE			,IDX_MD_STATE		,0	,0	,(OSD_ITEM *)OSD_MdStateItem},
	{OSD_STR_X_POS			,IDX_MD_X			,100,0	,0	},
	{OSD_STR_Y_POS			,IDX_MD_Y			,100,0	,0	},
	{OSD_STR_WIDTH			,IDX_MD_W			,100,0	,0	},
	{OSD_STR_HEIGHT			,IDX_MD_H			,100,0	,0	},
	{OSD_STR_DISPLAY		,IDX_MD_DISP		,3	,0	,(OSD_ITEM *)OSD_MdBlockItem},
	{OSD_STR_ALARM			,IDX_MD_ALARM		,0	,0	,(OSD_ITEM *)OSD_MdAlarmItem},
	{OSD_STR_SENSITIVITY	,IDX_MD_SENS		,20	,0	,0	},
	{OSD_STR_NULL			,IDX_NULL			,0	,0	,0	},
	{OSD_STR_RESET_ZONE		,UIDX_MD_RESETZONE	,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0	,0	}
};

const OSD_ITEM OSD_PriStateItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON , 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_PriColorItem[] = {{OSD_STR_WHITE, 0}, {OSD_STR_YELLOW, 0}, {OSD_STR_CYAN, 0}, {OSD_STR_GREEN, 0}, {OSD_STR_MAGENTA, 0}, {OSD_STR_RED, 0}, {OSD_STR_BLUE, 0}, {OSD_STR_BLACK, 0},/* {OSD_STR_GRAY, 0}, */{OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_PriTransItem[] = {{OSD_STR_25PER, 0}, {OSD_STR_50PER, 0}, {OSD_STR_75PER, 0},  {OSD_STR_100PER, 0} ,{OSD_STR_FINISH, 0}};

const OSD_MAP OSD_PrivacyMap[] = {
	{OSD_STR_ZONE			,IDX_PRI_ZONE		,7		,0	,0	},
	{OSD_STR_STATE			,IDX_PRI_STATE		,0		,0	,(OSD_ITEM *)OSD_PriStateItem	},
	{OSD_STR_X_POS			,IDX_PRI_X			,100	,0	,0	},
	{OSD_STR_Y_POS			,IDX_PRI_Y			,100	,0	,0	},
	{OSD_STR_WIDTH			,IDX_PRI_W			,100	,0	,0	},
	{OSD_STR_HEIGHT			,IDX_PRI_H			,100	,0	,0	},
	{OSD_STR_COLOR			,IDX_PRI_COLOR		,0		,0	,(OSD_ITEM *)OSD_PriColorItem	},
	{OSD_STR_TRANS			,IDX_PRI_TRANS		,0		,0	,(OSD_ITEM *)OSD_PriTransItem	},
	{OSD_STR_NULL			,IDX_NULL			,0		,0	,0	},
	{OSD_STR_MASK_CENTER	,UIDX_PRI_CENTER	,0		,0	,0	},
	{OSD_STR_RESET_ZONE		,UIDX_PRI_RESETZONE	,0		,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL		,0		,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0		,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0		,0	,0	}
};

const OSD_ITEM OSD_MdOnOffItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, (OSD_MAP *)OSD_MotionMap}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_PrivacyOnOffItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, (OSD_MAP *)OSD_PrivacyMap}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_SpecialOnOffItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_SpecialMap[] = {
	{OSD_STR_MOTION			,IDX_MD_ON		,0	,0	,(OSD_ITEM *)OSD_MdOnOffItem		},
	{OSD_STR_PRIVACY		,IDX_MASK_ON	,0	,0	,(OSD_ITEM *)OSD_PrivacyOnOffItem	},
	{OSD_STR_DEFOG			,IDX_DEFOG_ON	,0	,0	,(OSD_ITEM *)OSD_SpecialOnOffItem	},
	{OSD_STR_DIS			,IDX_DIS_ON		,0	,0	,(OSD_ITEM *)OSD_SpecialOnOffItem	},
	{OSD_STR_NULL			,IDX_NULL		,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL	,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN		,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL		,0	,0	,0	}
};

/* DISPLAY */
const OSD_ITEM OSD_DspIDItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DspTitleItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DspZmMagItem[] = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};
const OSD_ITEM OSD_DspfncItem[]  = {{OSD_STR_OFF, 0}, {OSD_STR_ON, 0}, {OSD_STR_FINISH, 0}};

const OSD_MAP OSD_DisplayMap[] = {
	{OSD_STR_CAMERA_ID		,IDX_ID_ON		,0	,0	,(OSD_ITEM *)OSD_DspIDItem		},
	{OSD_STR_CAMERA_TITLE	,IDX_TITLE_ON	,0	,0	,(OSD_ITEM *)OSD_DspTitleItem	},
	{OSD_STR_ZOOM_MAG		,IDX_ZMAG_ON	,0	,0	,(OSD_ITEM *)OSD_DspZmMagItem	},
	{OSD_STR_FUNCTION		,IDX_FUNC_ON	,0	,0	,(OSD_ITEM *)OSD_DspfncItem		},

	{OSD_STR_NULL			,IDX_NULL		,0	,0	,0	},
	{OSD_STR_INITIAL		,IDX_INITIAL	,0	,0	,0	},
	{OSD_STR_RETURN			,IDX_RETURN		,0	,0	,0	},
	{OSD_STR_FINISH			,IDX_NULL		,0	,0	,0	}
};

/* SYSTEM */ /*{OSD_STR_PELCO_D, 0}, {OSD_STR_PELCO_P, 0}, {OSD_STR_VISCA, 0},*/
const OSD_ITEM OSD_SysPrtclItem[] = {{OSD_STR_PELCO_D, 0}, {OSD_STR_PELCO_P, 0}, {OSD_STR_CNB_H, 0}, {OSD_STR_VISCA, 0}, {OSD_STR_FINISH, 0}	};
const OSD_ITEM OSD_SysBaudItem[] = {	{OSD_STR_2400, 0},	{OSD_STR_4800, 0},	{OSD_STR_9600, 0},	{OSD_STR_19200, 0},
										{OSD_STR_38400, 0},	{OSD_STR_57600, 0},	{OSD_STR_115200, 0},	{OSD_STR_FINISH, 0}	};
const OSD_ITEM OSD_SysLngItem[] = {	{OSD_STR_ENG, 0},	{OSD_STR_FINISH, 0}	};
const OSD_ITEM OSD_SysCamResItem[] = {	{OSD_STR_1080_30P, 0},	{OSD_STR_1080_25P, 0},{OSD_STR_720_60P, 0}, {OSD_STR_720_50P, 0},{OSD_STR_1080_60I, 0}, {OSD_STR_1080_50I, 0},{OSD_STR_1080_60P, 0}, {OSD_STR_1080_50P, 0},  {OSD_STR_FINISH, 0}	};

/*const OSD_ITEM OSD_SysFactoryRstItem[] = {{OSD_STR_SAVE_NO, 0}, {OSD_STR_SAVE_YES, 0}};
const OSD_ITEM OSD_SysRebootItem[] = {{OSD_STR_NO, 0}, {OSD_STR_YES, 0}};
 *EXIT, RETURN, REBOOT, FRESET OSD 아이템는 정의하지 않습니다. */

const OSD_MAP OSD_SystemMap[] = {
	{OSD_STR_PROTOCOL		,UIDX_PRTCL_TYPE	,0	,0							,(OSD_ITEM *)OSD_SysPrtclItem},
	{OSD_STR_CAMERA_ID		,IDX_CAM_ID			,255,0							,0	},
	{OSD_STR_CAMERA_TITLE	,IDX_TITLE			,0	,0							,0	},
	{OSD_STR_BAUDRATE		,UIDX_PRTCL_BAUD	,0	,0							,(OSD_ITEM *)OSD_SysBaudItem},
	{OSD_STR_LANGUAGE		,IDX_OSD_LANGUAGE	,0	,0							,(OSD_ITEM *)OSD_SysLngItem},
	{OSD_STR_OUTPUT_FORMAT	,UIDX_CAM_RES		,0	,0							,(OSD_ITEM *)OSD_SysCamResItem},
#ifdef WIN32
	{OSD_STR_VERSION		,IDX_NULL			,0	,(OSD_MAP *)OSD_gHiddenMap	,0	},
#else
	{OSD_STR_VERSION		,UIDX_PASS			,0	,0},//(OSD_MAP *)OSD_gHiddenMap,	0},
#endif
	{OSD_STR_DISPLAY		,IDX_NULL			,0	,(OSD_MAP *)OSD_DisplayMap	,0	},
	{OSD_STR_NULL			,IDX_NULL			,0	,0							,0	},
	{OSD_STR_FACTORY_RESET	,IDX_FRESET			,0	,0							,0	},
	{OSD_STR_REBOOT			,IDX_REBOOT			,0	,0							,0	},
	{OSD_STR_RETURN			,IDX_RETURN			,0	,0							,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0							,0	}
};

/* MAIN MENU */
const OSD_ITEM OSD_WbItem[] = { {OSD_STR_AUTO		,0	},					// 0
								{OSD_STR_ATW		,0	}, 					// 1
								{OSD_STR_INDOOR		,0	},					// 2
								{OSD_STR_OUTDOOR	,0	},					// 3
								{OSD_STR_ONEPUSH	,0	},					// 4
								{OSD_STR_MANUAL,(OSD_MAP *)OSD_WbManualMap},// 5
								//{OSD_STR_OUTDOORAUTO,0},					// 6
								//{OSD_STR_SODIUMVAPORLAMPAUTO,0},			// 7
								//{OSD_STR_SODIUMVAPORLAMP,0},				// 8
								//{OSD_STR_SODIUMVAPORLAMPOUTDOORAUTO,0},	// 9
								{OSD_STR_FINISH		,0}
};

const OSD_ITEM OSD_DnItem[] = {	{OSD_STR_AUTO,(OSD_MAP *)OSD_DNMAP},	{OSD_STR_DAY, 0},	{OSD_STR_NIGHT, 0},	{OSD_STR_EXT_L, 0},	{OSD_STR_EXT_H, 0},	{OSD_STR_CDS, (OSD_MAP *)OSD_DNMAP},	{OSD_STR_FINISH, 0}	};
const OSD_ITEM OSD_BackLightItem[] = {	{OSD_STR_OFF, 0},	{OSD_STR_BLC, (OSD_MAP *)OSD_BLCMap},	{OSD_STR_WDR, (OSD_MAP *)OSD_WDRMap},	{OSD_STR_HLC, (OSD_MAP *)OSD_HLCMap},	{OSD_STR_FINISH, 0}};

/*const OSD_ITEM OSD_ExitItem[] = {{OSD_STR_SAVE_YES, 0}, {OSD_STR_SAVE_NO, 0}};
 *EXIT, RETURN, REBOOT, FRESET OSD 아이템는 정의하지 않습니다. */

const OSD_MAP OSD_gMap[] = {
	{OSD_STR_FOCUS			,IDX_NULL		,0	,(OSD_MAP *)OSD_FocusMap	,0	},
	{OSD_STR_EXPOSURE		,IDX_NULL		,0	,(OSD_MAP *)OSD_ExposureMap	,0	},
	{OSD_STR_WHITE_BALANCE	,IDX_WB_MODE	,0	,0							,(OSD_ITEM *)OSD_WbItem	},
	{OSD_STR_DAY_NIGHT		,IDX_DN_MODE	,0	,0							,(OSD_ITEM *)OSD_DnItem	},
	{OSD_STR_IMAGE			,IDX_NULL		,0	,(OSD_MAP *)OSD_ImageMap	,0	},
	{OSD_STR_BACKLIGHT		,IDX_BL_MODE	,0	,0							,(OSD_ITEM *)OSD_BackLightItem},
	{OSD_STR_DNR			,IDX_NULL		,0	,(OSD_MAP *)OSD_DNRMap		,0	},
	{OSD_STR_SPECIAL		,IDX_NULL		,0	,(OSD_MAP *)OSD_SpecialMap	,0	},
	{OSD_STR_SYSTEM			,IDX_NULL		,0	,(OSD_MAP *)OSD_SystemMap	,0	},
	{OSD_STR_NULL			,IDX_NULL		,0	,0							,0	},
	{OSD_STR_EXIT			,IDX_EXIT		,0	,0							,0	},
	{OSD_STR_FINISH			,IDX_NULL		,0	,0							,0	}
};

const OSD_MAP OSD_gMap_Visca[] = {
	{OSD_STR_PROTOCOL		,UIDX_PRTCL_TYPE	,0	,0							,(OSD_ITEM *)OSD_SysPrtclItem	},
	{OSD_STR_BAUDRATE		,UIDX_PRTCL_BAUD	,0	,0							,(OSD_ITEM *)OSD_SysBaudItem	},
	{OSD_STR_LANGUAGE		,IDX_OSD_LANGUAGE	,0	,0							,(OSD_ITEM *)OSD_SysLngItem		},
	{OSD_STR_OUTPUT_FORMAT	,UIDX_CAM_RES		,0	,0							,(OSD_ITEM *)OSD_SysCamResItem	},
#ifdef WIN32
	{OSD_STR_VERSION		,IDX_NULL			,0	,(OSD_MAP *)OSD_gHiddenMap	,0	},
#else
	{OSD_STR_VERSION		,UIDX_PASS			,0	,0},//(OSD_MAP *)OSD_gHiddenMap,	0},
#endif
	{OSD_STR_NULL			,IDX_NULL			,0	,0							,0	},
	{OSD_STR_FACTORY_RESET	,IDX_FRESET			,0	,0							,0	},
	{OSD_STR_REBOOT			,IDX_REBOOT			,0	,0							,0	},
	{OSD_STR_EXIT			,IDX_EXIT			,0	,0							,0	},
	{OSD_STR_FINISH			,IDX_NULL			,0	,0							,0	}
};
/*************************************************************************************************************
* === 3. INITIAL DEFINE		===
*************************************************************************************************************/
const IFU_INITIAL IFU_EepData[] = {
	{IDX_FOCUS_MODE			,DEFAULT_FOCUS_MODE},
	{IDX_FOCUS_DIST			,DEFAULT_FOCUS_DIST},
	{IDX_ZOOM_MODE			,DEFAULT_DZOOM_COMBINE},
	{IDX_DZOOM_MODE			,DEFAULT_DZOOM_MODE},
	{IDX_ZTRK_MODE			,DEFAULT_TRACK_MODE},
	{IDX_ZOOM_SPEED			,DEFAULT_ZOOM_SPEED},
	{IDX_LENS_REFRESH_MODE	,DEFAULT_LENS_INIT_MODE},
	{IDX_DZOOM_MAG			,DEFAULT_DZOOM_LEVEL},
	{IDX_LENS_REFRESH_DAYS	,DEFAULT_LENS_INIT_DAY},
	{IDX_AE_TGT_BRIGHT		,DEFAULT_AE_TGT_BRIGHT},
	{IDX_AE_MODE			,DEFAULT_AE_MODE},
	{IDX_AE_AGC_LIMIT		,DEFAULT_AGC_LIMIT},
	{IDX_AE_DSS_STEP		,DEFAULT_DSS_STEP},
	{IDX_AE_FLK_MODE		,DEFAULT_FLK_MODE},
	{IDX_AEM_IRIS_STEP		,DEFAULT_IRIS_STEP},
	{IDX_AEM_SHUT_STEP		,DEFAULT_SHUT_STEP},
	{IDX_AEM_BRIGHT_STEP	,DEFAULT_BRIGHT_STEP},
	{IDX_WB_ENV				,DEFAULT_ATW_MODE},
	{IDX_WB_RED_GAIN		,DEFAULT_USR1_RGAIN},
	{IDX_WB_BLUE_GAIN		,DEFAULT_USR1_BGAIN},
	{IDX_DN_CHG_STEP		,DEFAULT_DN_LEVEL},
	{IDX_DN_CHG_TIME		,DEFAULT_DN_CHG_TIME},
	{IDX_IMG_FLIP			,DEFAULT_MIRROR_MODE},
	{IDX_IMG_FREEZE			,DEFAULT_IMG_FREEZE},
	{IDX_IMG_COLOR			,DEFAULT_IMG_COLOR_ON},
	{IDX_SHADE_ON			,DEFAULT_SHADE_LEVEL},
	{IDX_IMG_GAM_MODE		,DEFAULT_IMG_GAM_MODE},
	{IDX_IMG_GAMMA_STEP		,DEFAULT_IMG_GAMMA_STEP},
	{IDX_IMG_CONTRAST		,DEFAULT_IMG_CONTRAST_LEVEL},
	{IDX_IMG_SHARPNESS		,DEFAULT_IMG_SHARPNESS_LEVEL},
	{IDX_IMG_CHROMA			,DEFAULT_IMG_CHROMA_LEVEL},
	{IDX_IMG_HUE			,DEFAULT_IMG_HUE_LEVEL},
	{IDX_IMG_BRIGHT			,DEFAULT_GAMMA_BRIGHT_LEVEL},
	{IDX_BLC_LEVEL			,DEFAULT_BLC_LEVEL},
	{IDX_WDR_LEVEL			,DEFAULT_WDR_LEVEL},
	{IDX_HLC_MASK_COLOR		,DEFAULT_HLC_CR},
	{IDX_HLC_LEVEL			,DEFAULT_HLC_CLIP},
	{IDX_DNR_MODE			,DEFAULT_DNR_MODE},
	{IDX_DNR_GLB_MOT		,DEFAULT_G_MOTION},
	{IDX_MD_ON				,DEFAULT_MD_ALL},
	{IDX_MASK_ON			,0},
	{IDX_DEFOG_ON			,DEFAULT_DEFOG_ON},
	{IDX_PROTOCOL			,DEFAULT_PROTOCOL_TYPE},
	{IDX_CAM_ID				,DEFAULT_CAM_ID},
	{IDX_BAUDRATE			,DEFAULT_BAUDRATE},
	{IDX_OSD_LANGUAGE		,DEFAULT_OSD_LANGUAGE},
	{IDX_ID_ON				,DEFAULT_ID_ON		},
	{IDX_TITLE_ON			,DEFAULT_TITLE_ON	},
	{IDX_ZMAG_ON			,DEFAULT_ZMAG_ON	},
	{IDX_FUNC_ON			,DEFAULT_FUNC_ON	},
	{IDX_ALL_ON				,DEFAULT_ALL_ON		},
	{IDX_MD_SENS			,DEFAULT_MD_SENS	},
	{UIDX_OSD_DEBUG_STATE	,0},
	{UIDX_IRIS_JUMP 		,0},
	{UIDX_SPOT_AE			,0},
	{UIDX_AE_RESPONS		,0},
	{UIDX_SPOT_AE_POS_X		,0},
	{UIDX_SPOT_AE_POS_Y		,0},
	{UIDX_DBDR_MODE			,0},
	{UIDX_B_GAIN_P			,85},
	{UIDX_B_GAIN_N			,145},
	{UIDX_R_GAIN_P			,78},
	{UIDX_R_GAIN_N			,86},
	{UIDX_B_HUE_P			,93},
	{UIDX_B_HUE_N			,34},
	{UIDX_R_HUE_P			,48},
	{UIDX_R_HUE_N			,5},
	{UIDX_AUTO_MIN_SHUTTER	,0},
	{UIDX_AUTO_MAX_SHUTTER	,0},
	{UIDX_H_SIZE			,0},
	{UIDX_H_START			,0},
	{UIDX_H_END				,0},
	{UIDX_V_TOTAL_SIZE		,0},
	{UIDX_V_ACT_START		,0},
	{UIDX_V_ACT_END			,0},
	{UIDX_V_ACT_START_BOT	,0},
	{UIDX_V_ACT_END_BOT		,0},
	{UIDX_COLOR_BAR			,0},
	{UIDX_MAIN_IN			,0},
	{UIDX_MAIN_OUT			,0},
	{UIDX_AUX_OUT			,0},
	{UIDX_VIDEO_ENCODER		,0},
	{UIDX_WB_COLOR_TEMP		,0},
	{UIDX_PRI_ADJ_X			,100},
	{UIDX_PRI_ADJ_Y			,100},
	{UIDX_GAMMA1			,1},
	{UIDX_GAMMA2			,1},
	{UIDX_LAST_YGAIN		,0x80},
	{UIDX_LAST_CGAIN		,0x80},
	{UIDX_VISCA_OSD_MENU	,0},//Default를 어떻게 정하나?
	{IDX_DIS_ON				,0},
	{IDX_AF_MODE			,DEFAULT_AF_MODE},
	{UIDX_MD_DISP			,0},
	{IDX_NULL				,0},
};

/*************************************************************************************************************
* GLOBAL VARIABLE
*************************************************************************************************************/
/* 사용자 EEPRom 데이터 */
EEPROM_USER	g_UserEepData;

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/
/*처리를 Task로 넘기기 위한 flg*/
static uint08 dzoom_osd_flg = 0;	 // OSD : DZoom Magnitude
static uint08 wb_manual_osd_flg = 0; // OSD : WB Color Temperate
static uint08 _3d_adj_zm_flg = 0;	 //
static uint08 osd_off_flg = 0;		 // OSD : OSD MENU OFF FLG

static uint08 title_change = 0;		 // VISCA : TITLE DISPLAY ,OSD MENU OFF / SYSTEM INIT
/*Osd Map에 진입해 있음을 알리는 flg*/
static uint08 Osd_md_flg = 0;			// OSD : MD Map 진입
static uint08 Osd_pri_flg = 0;			// OSD : PRIVACY Map 진입
static uint08 Osd_pri_adj_flg = 0;		// OSD : Privacy ADJ Map 진입
static uint08 osd_defect_adj_flg = 0; 	// OSD : defect adj에 진입
static uint08 osd_tune_exp_flg = 0;
static uint08 osd_tune_color_adj = 0;
static uint16 display_flg[DISPLAY_MAX];

/*Motion Detection을 위한 변수*/
static uint08 motion_detect = 0;
static uint08 osd_hide_mode = 0;
static uint32 gOsd_key_code = 0;
static uint08 gOsd_key_flg  = 0;

/* Reset깂 for VISCA */
static uint08 Reset_r_gain;
static uint08 Reset_b_gain;
static uint08 Reset_bright;

/* Hidden Menu을 위한 변수 */
static uint08 pass_cnt = 0;

/*************************************************************************************************************
* FUNCTION
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/
static void User_EepInitial(EEP_IDX idx);
static IFER Visca_Evt_Proc_Cmd(IFEVT_PARAM *param);
static IFER Visca_Evt_Proc_Move(IFEVT_PARAM *param);
static void Trace_Func_OSD(uint32 key);
static void IFU_Init_Motion_mask(int08 zone);
static void IFU_Init_Privavy_mask(int08 zone);
static void IFU_After_Load();
static void IFU_After_Save();
static void IFU_Swap_Osd_Struct();
static void IFU_Camres_Chg(uint32 Camres);

/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/*********************************************************************************************************//**
* @retval none
* @brief
*	Osd Claer All
*************************************************************************************************************/
static void User_Clear_Osd(void)
{
	uint08 i,j;
	for(j=0;j < 22;j++)
		for(i=0;i < 55;i++)
		{
			IF_Trace(i,j," ");
#ifndef WIN32
			SetFontAttribute(j,i,FONT_ATTR_WHITE);
#endif
		}

}

/*********************************************************************************************************//**
* @param[in] x : Osd의 x ,가로값
* @param[in] y : Osd의 y ,세로값
* @param[in] l : (x,y)에서부터 (x + l,y) 까지의 색을 바꾼다.(x + l < OSD_MAX_COL)
* @param[in] c : Color ID
* @retval none
* @brief
*	VISCA Funtion OSD (DISPLAY)
*	색을 바꾼다.
*************************************************************************************************************/
static void User_Color_Set(uint08 x,uint08 y,uint08 l,uint08 c)
{
	uint08 j;
	for(j=0;j < l;j++)
#ifndef WIN32
		SetFontAttribute(y,x+j,c);
#else
		;
#endif
}
/*********************************************************************************************************//**
* @param[in] key : 입력된 키값
* @retval none
* @brief
* === 4. LOCAL FUNCTION	: FUNTION OSD(CNB)	===
*	Funtion Osd를 처리해주는 부분
*************************************************************************************************************/
static void Trace_Func_OSD(uint32 key)
{
	static uint16 nw_stay = 5000/IF_PROCESS_TICK_MS;
	static uint16 push_stay = 16000/IF_PROCESS_TICK_MS;
	static uint16 md_stay  = 1;
	static uint16 md_stay1 = 1;
	static uint16 md_stay2 = 1;
	static uint16 md_stay3 = 1;
	static uint16 md_stay4 = 1;
	uint08 _dss = 0;
	static uint08 temp_Hall_adj;
	static uint08 temp_Lens_adj;
	static uint08 temp_Def_adj;
	static uint08 temp_Push_flg;

	if(key == 0x800)		nw_stay   = 5000/IF_PROCESS_TICK_MS;//2초
	if(key != OSD_KEYNULL)  push_stay = 16000/IF_PROCESS_TICK_MS;//1초

	PrintIdTitle();//ID하고 Title 표시

	if(temp_Hall_adj != g_OsdData.FLD.HALL_ADJ || osd_off_flg)
	{
		if(g_OsdData.FLD.HALL_ADJ == 2)		 IF_Trace(3,7,"HALL ADJ (NG)     ");
		else if(g_OsdData.FLD.HALL_ADJ == 3) IF_Trace(3,7,"HALL ADJ (NOT-ADJ)");
		else 								 IF_Trace(3,7,"                  ");
		temp_Hall_adj = g_OsdData.FLD.HALL_ADJ;
	}
	if(temp_Lens_adj != g_OsdData.FLD.LENS_ADJ || osd_off_flg)
	{
		if(g_OsdData.FLD.LENS_ADJ == 2)		 IF_Trace(3,8,"LENS ADJ (NG)     ");
		else if(g_OsdData.FLD.LENS_ADJ == 3) IF_Trace(3,8,"LENS ADJ (NOT-ADJ)");
		else 								 IF_Trace(3,8,"                  ");
		temp_Lens_adj = g_OsdData.FLD.LENS_ADJ;
	}
	if(temp_Def_adj != g_OsdData.FLD.DEFECT_ADJ || osd_off_flg)
	{
		if(g_OsdData.FLD.DEFECT_ADJ == 2)		IF_Trace(3,9,"DEFECT ADJ (NG)     ");
		else if(g_OsdData.FLD.DEFECT_ADJ == 3) 	IF_Trace(3,9,"DEFECT ADJ (NOT-ADJ)");
		else 								 	IF_Trace(3,9,"                    ");
		temp_Def_adj = g_OsdData.FLD.DEFECT_ADJ;
	}

	if(g_OsdData.FLD.FUNC_ON)
	{
		if(nw_stay)
		{
			nw_stay--;//Max 비율
			switch(g_OsdData.FLD.AE_DSS_STEP)
			{
				case 0: IF_Trace(9,19,"    "); break;
				case 1: IF_Trace(9,19,"NW02"); break;
				case 2: IF_Trace(9,19,"NW04"); break;
				case 3: IF_Trace(9,19,"NW08"); break;
				case 4: IF_Trace(9,19,"NW16"); break;
				case 5: IF_Trace(9,19,"NW32"); break;
				default : break;
			}
		}
		else
		{
#ifndef WIN32
			_dss = GetCurDss();
#endif
			if(g_OsdData.FLD.AE_DSS_STEP != 0)
			{
				if(_dss < 10)		IF_Trace(9,19,"NW0%d",_dss);
				else				IF_Trace(9,19,"NW%d",_dss);
			}
		}

		if(push_stay)
		{
			IF_Trace(19,19,"%c",20);//손가락
			if(g_OsdData.FLD.BL_MODE)
			{
				IF_Trace(29,19,"%c",12);//Only Day
				IF_Trace(30,19,"%c",13);
			}
			else IF_Trace(29,19,"  ");
			push_stay--;
#ifndef WIN32
			if(g_OsdData.FLD.ZMAG_ON)	IF_Trace(46,20,"X %d  ",Lens_get_opt_zoom_magitude() * Dzoom_get_magnitude() / 100);
#else
			if(g_OsdData.FLD.ZMAG_ON)	IF_Trace(46,20,"X %d  ",0);
#endif
			temp_Push_flg = 1;
		}
		else
		{
			if(temp_Push_flg)
			{
				IF_Trace(19,19,"   ");
				IF_Trace(29,19,"  ");
				IF_Trace(46,20,"      ");
				temp_Push_flg = 0;
			}
		}
	}
	if(g_OsdData.FLD.MD_ON)//!수정점! : MD_ALARM값을 받아야한다.
	{
		if(motion_detect&0x1)	md_stay1 = 2000/IF_PROCESS_TICK_MS;
		if(motion_detect&0x2)	md_stay2 = 2000/IF_PROCESS_TICK_MS;
		if(motion_detect&0x4)	md_stay3 = 2000/IF_PROCESS_TICK_MS;
		if(motion_detect&0x8)	md_stay4 = 2000/IF_PROCESS_TICK_MS;
		if(motion_detect)		md_stay  = 2000/IF_PROCESS_TICK_MS;

		if(md_stay>1)
		{
			md_stay--;
			IF_Trace(MD_POS_X,MD_POS_Y,"MD");
		}
		else if(md_stay == 1)
		{
			IF_Trace(MD_POS_X,MD_POS_Y,"  ");
			md_stay--;
		}

		if(md_stay1>1)
		{
			md_stay1--;
			IF_Trace(MD_POS_X+2,MD_POS_Y,"1");
		}
		else if(md_stay1 == 1)
		{
			IF_Trace(MD_POS_X+2,MD_POS_Y," ");
			md_stay1--;
		}

		if(md_stay2>1)
		{
			md_stay2--;
			IF_Trace(MD_POS_X+3,MD_POS_Y,"2");
		}
		else if(md_stay2 == 1)
		{
			IF_Trace(MD_POS_X+3,MD_POS_Y," ");
			md_stay2--;
		}

		if(md_stay3>1)
		{
			md_stay3--;
			IF_Trace(MD_POS_X+4,MD_POS_Y,"3");
		}
		else if(md_stay3 == 1)
		{
			IF_Trace(MD_POS_X+4,MD_POS_Y," ");
			md_stay3--;
		}

		if(md_stay4>1)
		{
			md_stay4--;
			IF_Trace(MD_POS_X+5,MD_POS_Y,"4");
		}
		else if(md_stay4 == 1)
		{
			IF_Trace(MD_POS_X+5,MD_POS_Y," ");
			md_stay4--;
		}

		motion_detect = 0;
	}
	osd_off_flg = 0;
}



/*********************************************************************************************************//**
* @retval none
* @brief
* === 5. LOCAL FUNCTION	: VISCA DISPLAY	===
*	display_flg[] 초기화
*************************************************************************************************************/
static void Init_Display_Print(void)
{
	display_flg[DISPLAY_CAMRES] 	= STATE_ON;
	display_flg[DISPLAY_BRIGHT] 	= STATE_ON;
	display_flg[DISPLAY_SHUTTER] 	= STATE_ON;
	display_flg[DISPLAY_P_EFFECT] 	= STATE_ON;
	display_flg[DISPLAY_EXP_COMP] 	= STATE_ON;
	display_flg[DISPLAY_IRIS] 		= STATE_ON;
	display_flg[DISPLAY_GAIN] 		= STATE_ON;
	display_flg[DISPLAY_BACKLIGHT] 	= STATE_ON;
	display_flg[DISPLAY_WB_MODE] 	= STATE_ON;
	display_flg[DISPLAY_LR] 		= STATE_ON;
	display_flg[DISPLAY_FLIP] 		= STATE_ON;
	display_flg[DISPLAY_CAPTURE] 	= STATE_ON;
}

/*********************************************************************************************************//**
* @retval none
* @brief
* === 5. LOCAL FUNCTION	: VISCA DISPLAY	===
*	Display를 Print한다.
*************************************************************************************************************/
static void User_Display_Print(void)
{
	uint08 tmp = 0;
	static uint08 stay_fcs;
	static uint08 stay_wb;
	if(display_flg[DISPLAY_CAMRES])
	{
		switch(g_UserEepData.FLD.INITIAL_CAM_RES)
		{
		#ifdef SUNNY_X20
			case 0x01 : IF_Trace(1,1,"1080i/60   ");	break;
			case 0x02 : IF_Trace(1,1,"1080i/59.94");	break;
			case 0x03 : IF_Trace(1,1,"NTSC ANALOG");	break;
			case 0x04 : IF_Trace(1,1,"1080i/50   ");	break;
			case 0x05 : IF_Trace(1,1,"PAL ANALOG ");	break;
			case 0x06 : IF_Trace(1,1,"1080p/30   ");	break;
			case 0x07 : IF_Trace(1,1,"1080p/29.97");	break;
			case 0x08 : IF_Trace(1,1,"1080p/25   ");	break;
			case 0x09 : IF_Trace(1,1,"720p/60    ");	break;
			case 0x0A : IF_Trace(1,1,"720p/59.94 ");	break;
			case 0x0B : IF_Trace(1,1,"NTSC ANALOG");	break;
			case 0x0C : IF_Trace(1,1,"720p/50    ");	break;
			case 0x0D : IF_Trace(1,1,"PAL ANALOG ");	break;
			case 0x0E : IF_Trace(1,1,"720p/30    ");	break;
			case 0x0F : IF_Trace(1,1,"720p/29.97 ");	break;
			case 0x10 : IF_Trace(1,1,"NTSC ANALOG");	break;
			case 0x11 : IF_Trace(1,1,"720p/25    ");	break;
			case 0x12 : IF_Trace(1,1,"PAL ANALOG ");	break;
			case 0x13 : IF_Trace(1,1,"1080p/59.94");	break;
			case 0x14 : IF_Trace(1,1,"1080p/50   ");	break;
			default :   IF_Trace(1,1,"           ");	break;
		#else
			case 0x01 : IF_Trace(1,1,"1080i/59.94");	break;
			case 0x03 : IF_Trace(1,1,"NTSC ANALOG");	break;
			case 0x04 : IF_Trace(1,1,"1080i/50   ");	break;
			case 0x05 : IF_Trace(1,1,"PAL ANALOG ");	break;
			case 0x06 : IF_Trace(1,1,"1080p/29.97");	break;
			case 0x08 : IF_Trace(1,1,"1080p/25   ");	break;
			case 0x09 : IF_Trace(1,1,"720p/59.94 ");	break;
			case 0x0C : IF_Trace(1,1,"720p/50    ");	break;
			case 0x0E : IF_Trace(1,1,"720p/29.97 ");	break;
			case 0x11 : IF_Trace(1,1,"720p/25    ");	break;
			case 0x13 : IF_Trace(1,1,"1080p/59.94");	break;
			case 0x14 : IF_Trace(1,1,"1080p/50   ");	break;
			default :   IF_Trace(1,1,"           ");	break;
		#endif
		}
		display_flg[DISPLAY_CAMRES] = STATE_OFF;
	}

	if(display_flg[DISPLAY_MEMCUS_CNT] == IF_PROCESS_TICK_3S)
	{
		switch(display_flg[DISPLAY_MEMCUS]>>8)
		{
			case 0 : IF_Trace(40,20,"RESET  ");		break;
			case 1 : IF_Trace(40,20,"SET    ");		break;
			case 2 : IF_Trace(40,20,"RECALL ");		break;
		}

		if((display_flg[DISPLAY_MEMCUS]&0xFF) != 0x7F)
		{
			IF_Trace(47,20,"MEMORY %X ",display_flg[DISPLAY_MEMCUS]&0xFF);
		}
		else
		{
			IF_Trace(47,20,"CUSTOM    ");
		}

		display_flg[DISPLAY_MEMCUS_CNT]--;
	}
	else if(display_flg[DISPLAY_MEMCUS_CNT] == 0);
	else if(display_flg[DISPLAY_MEMCUS_CNT] == 1)
	{
		IF_Trace(40,20,"                 ");
		display_flg[DISPLAY_MEMCUS_CNT]--;
	}
	else
		display_flg[DISPLAY_MEMCUS_CNT]--;
#ifndef WIN32
	if(EEP_Management_Warking())	return;
#endif
	if(display_flg[DISPLAY_BRIGHT] &&(!display_flg[DISPLAY_APERTURE])&&!(display_flg[DISPLAY_ZOOM]))
	{
		if(g_ViscaData.FLD.AE_MODE == 4)
		{
			if(g_ViscaData.FLD.BRIGHT_STEP < 0x10)
				IF_Trace(1,3,"BRIGHT 0%X    ",g_ViscaData.FLD.BRIGHT_STEP);
			else
				IF_Trace(1,3,"BRIGHT %X    ",g_ViscaData.FLD.BRIGHT_STEP);
			IF_Trace(1,4,"          ");
		}
		else
		{
			IF_Trace(1,3,"            ");
			IF_Trace(1,4,"          ");
		}
		display_flg[DISPLAY_BRIGHT] = STATE_OFF;
	}

	if(display_flg[DISPLAY_APERTURE] == IF_PROCESS_TICK_3S)
	{
		if(g_ViscaData.FLD.APER_GAIN < 0x10)
			IF_Trace(1,3,"APERTURE 0%X ",g_ViscaData.FLD.APER_GAIN);
		else
			IF_Trace(1,3,"APERTURE %X ",g_ViscaData.FLD.APER_GAIN);
		IF_Trace(1,4,"          ");
		display_flg[DISPLAY_APERTURE]--;
	}
	else if(display_flg[DISPLAY_APERTURE] == 0);
	else
		display_flg[DISPLAY_APERTURE]--;

#ifndef WIN32
	if(display_flg[DISPLAY_ZOOM])
	{
		if(g_ViscaData.FLD.DZOOM_MODE == 0)//Combine
		{
			if(g_ViscaData.FLD.ZOOM_POS < 0x10)
				IF_Trace(1,3,"ZOOM(C) 000%X",g_ViscaData.FLD.ZOOM_POS);
			else if(g_ViscaData.FLD.ZOOM_POS < 0x100)
				IF_Trace(1,3,"ZOOM(C) 00%X",g_ViscaData.FLD.ZOOM_POS);
			else if(g_ViscaData.FLD.ZOOM_POS < 0x1000)
				IF_Trace(1,3,"ZOOM(C) 0%X",g_ViscaData.FLD.ZOOM_POS);
			else
				IF_Trace(1,3,"ZOOM(C) %X",g_ViscaData.FLD.ZOOM_POS);
			IF_Trace(1,4,"          ");
		}
		else
		{
			if(g_ViscaData.FLD.ZOOM_POS < 0x10)
				IF_Trace(1,3,"ZOOM 000%X   ",g_ViscaData.FLD.ZOOM_POS);
			else if(g_ViscaData.FLD.ZOOM_POS < 0x100)
				IF_Trace(1,3,"ZOOM 00%X   ",g_ViscaData.FLD.ZOOM_POS);
			else if(g_ViscaData.FLD.ZOOM_POS < 0x1000)
				IF_Trace(1,3,"ZOOM 0%X   ",g_ViscaData.FLD.ZOOM_POS);
			else
				IF_Trace(1,3,"ZOOM %X   ",g_ViscaData.FLD.ZOOM_POS);

			if(g_ViscaData.FLD.DZOOM_POS < 0x10)
				IF_Trace(1,4,"DZOOM 0%X",g_ViscaData.FLD.DZOOM_POS);
			else if(g_ViscaData.FLD.DZOOM_POS < 0x100)
				IF_Trace(1,4,"DZOOM %X",g_ViscaData.FLD.DZOOM_POS);
		}
		if(Zoom_get_busy_state() == 0)
			display_flg[DISPLAY_ZOOM]--;
	}
#endif
	if(g_ViscaData.FLD.ICR_ON)
		IF_Trace(9,7,"ICR");
	else
		IF_Trace(9,7,"   ");

	if(display_flg[DISPLAY_P_EFFECT])
	{
		if(g_ViscaData.FLD.P_EFFECT == 2)
			IF_Trace(1,7,"NEG ART");
		else if(g_ViscaData.FLD.P_EFFECT == 4)
			IF_Trace(1,7,"BW     ");
		else
			IF_Trace(1,7,"       ");
		display_flg[DISPLAY_P_EFFECT] = STATE_OFF;
	}

	if(display_flg[DISPLAY_EXP_COMP])
	{
		if(g_ViscaData.FLD.COMP_ON)
		{
			if(g_ViscaData.FLD.EXP_COMP_VAL == 7)
				IF_Trace(1,9,"AS  0 ");
			else if(g_ViscaData.FLD.EXP_COMP_VAL < 7)
				IF_Trace(1,9,"AS -%d ",7-g_ViscaData.FLD.EXP_COMP_VAL);
			else
				IF_Trace(1,9,"AS +%d ",g_ViscaData.FLD.EXP_COMP_VAL-7);
		}
		else
		{
			IF_Trace(1,9,"      ");
		}
		display_flg[DISPLAY_EXP_COMP] = STATE_OFF;
	}

	if(display_flg[DISPLAY_IRIS])
	{
	#ifndef WIN32
		if(g_ViscaData.FLD.AE_MODE == 3)

			User_Color_Set(1,10,5,FONT_ATTR_GRAY);

		else if(g_ViscaData.FLD.AE_MODE == 1)
			User_Color_Set(1,10,5,FONT_ATTR_WHITE);
	#endif
		if(g_ViscaData.FLD.AE_MODE == 3||g_ViscaData.FLD.AE_MODE == 1)
		{
			switch(g_ViscaData.FLD.IRIS_STEP)
			{
				case 0x00:	IF_Trace(1,10,"CLOSE");		break;
				case 0x05:	IF_Trace(1,10,"F14  ");		break;
				case 0x06:	IF_Trace(1,10,"F11  ");		break;
				case 0x07:	IF_Trace(1,10,"F9.6 ");		break;
				case 0x08:	IF_Trace(1,10,"F8   ");		break;
				case 0x09:	IF_Trace(1,10,"F6.8 ");		break;
				case 0x0A:	IF_Trace(1,10,"F5.6 ");		break;
				case 0x0B:	IF_Trace(1,10,"F4.8 ");		break;
				case 0x0C:	IF_Trace(1,10,"F4   ");		break;
				case 0x0D:	IF_Trace(1,10,"F3.4 ");		break;
				case 0x0E:	IF_Trace(1,10,"F2.8 ");		break;
				case 0x0F:	IF_Trace(1,10,"F2.4 ");		break;
				case 0x10:	IF_Trace(1,10,"F2   ");		break;
#ifdef SUNNY_X20
				case 0x11:	IF_Trace(1,10,"F1.6 "); 	break;
#else
				case 0x11:	IF_Trace(1,10,"F1.8 "); 	break;
#endif
				default : 	IF_Trace(1,10,"F    ");		break;
			}
		}
		else
			IF_Trace(1,10,"     ");

		display_flg[DISPLAY_IRIS] = STATE_OFF;
	}

	if(display_flg[DISPLAY_GAIN])
	{
		if(g_ViscaData.FLD.AE_MODE == 1)
		{
			if(g_ViscaData.FLD.GAIN_STEP == 0)
				IF_Trace(10,10,"-3dB ");
			else
				IF_Trace(10,10,"%ddB ",(g_ViscaData.FLD.GAIN_STEP-1)<<1);
		}
		else
			IF_Trace(10,10,"     ");

		display_flg[DISPLAY_GAIN] = STATE_OFF;
	}

	if(display_flg[DISPLAY_SHUTTER])
	{
#ifndef WIN32
		if(g_ViscaData.FLD.AE_MODE == 2)
			User_Color_Set(1,11,7,FONT_ATTR_GRAY);
		else if(g_ViscaData.FLD.AE_MODE == 1)
			User_Color_Set(1,11,7,FONT_ATTR_WHITE);
#endif
		if(g_ViscaData.FLD.AE_MODE == 2||g_ViscaData.FLD.AE_MODE == 1)
		{
#ifndef WIN32
			tmp = Param_get_cam_system();
#endif
			if(tmp)//System PAL
			{
				switch(g_ViscaData.FLD.SHUTTER_STEP)
				{
					case 0x00:	IF_Trace(1,11,"1/1    ");		break;
					case 0x01:	IF_Trace(1,11,"1/2    ");		break;
					case 0x02:	IF_Trace(1,11,"1/3    ");		break;
					case 0x03:	IF_Trace(1,11,"1/6    ");		break;
					case 0x04:	IF_Trace(1,11,"1/12   ");		break;
					case 0x05:	IF_Trace(1,11,"1/25   ");		break;
					case 0x06:	IF_Trace(1,11,"1/50   ");		break;
					case 0x07:	IF_Trace(1,11,"1/75   ");		break;
					case 0x08:	IF_Trace(1,11,"1/100  ");		break;
					case 0x09:	IF_Trace(1,11,"1/120  ");		break;
					case 0x0A:	IF_Trace(1,11,"1/150  ");		break;
					case 0x0B:	IF_Trace(1,11,"1/215  ");		break;
					case 0x0C:	IF_Trace(1,11,"1/300  ");		break;
					case 0x0D:	IF_Trace(1,11,"1/425  ");		break;
					case 0x0E:	IF_Trace(1,11,"1/600  ");		break;
					case 0x0F:	IF_Trace(1,11,"1/1000 ");		break;
					case 0x10:	IF_Trace(1,11,"1/1250 ");		break;
					case 0x11:	IF_Trace(1,11,"1/1750 ");		break;
					case 0x12:	IF_Trace(1,11,"1/2500 ");		break;
					case 0x13:	IF_Trace(1,11,"1/3500 ");		break;
					case 0x14:	IF_Trace(1,11,"1/6000 ");		break;
					case 0x15:	IF_Trace(1,11,"1/10000");		break;
					default : 	IF_Trace(1,11,"       ");		break;
				}
			}
			else
			{
				switch(g_ViscaData.FLD.SHUTTER_STEP)
				{
					case 0x00:	IF_Trace(1,11,"1/1    ");		break;
					case 0x01:	IF_Trace(1,11,"1/2    ");		break;
					case 0x02:	IF_Trace(1,11,"1/4    ");		break;
					case 0x03:	IF_Trace(1,11,"1/8    ");		break;
					case 0x04:	IF_Trace(1,11,"1/15   ");		break;
					case 0x05:	IF_Trace(1,11,"1/30   ");		break;
					case 0x06:	IF_Trace(1,11,"1/60   ");		break;
					case 0x07:	IF_Trace(1,11,"1/90   ");		break;
					case 0x08:	IF_Trace(1,11,"1/100  ");		break;
					case 0x09:	IF_Trace(1,11,"1/125  ");		break;
					case 0x0A:	IF_Trace(1,11,"1/180  ");		break;
					case 0x0B:	IF_Trace(1,11,"1/250  ");		break;
					case 0x0C:	IF_Trace(1,11,"1/350  ");		break;
					case 0x0D:	IF_Trace(1,11,"1/500  ");		break;
					case 0x0E:	IF_Trace(1,11,"1/725  ");		break;
					case 0x0F:	IF_Trace(1,11,"1/1000 ");		break;
					case 0x10:	IF_Trace(1,11,"1/1500 ");		break;
					case 0x11:	IF_Trace(1,11,"1/2000 ");		break;
					case 0x12:	IF_Trace(1,11,"1/3000 ");		break;
					case 0x13:	IF_Trace(1,11,"1/4000 ");		break;
					case 0x14:	IF_Trace(1,11,"1/6000 ");		break;
					case 0x15:	IF_Trace(1,11,"1/10000");		break;
					default : 	IF_Trace(1,11,"       ");		break;
				}
			}
		}
		else
			IF_Trace(1,11,"       ");

		display_flg[DISPLAY_GAIN] = STATE_OFF;
	}

	if(display_flg[DISPLAY_BACKLIGHT])
	{
		if(g_ViscaData.FLD.BLC_ON)
			IF_Trace(1,13,"BL");
		else
			IF_Trace(1,13,"  ");

		display_flg[DISPLAY_BACKLIGHT] = STATE_OFF;
	}
#ifndef WIN32
	if(g_ViscaData.FLD.F_MODE)
	{
		if(g_ViscaData.FLD.FOCUS_POS <= Focus_get_far_limit_pos())
		{
			if(stay_fcs > 1)	IF_Trace(5,13,"    ");
			else				IF_Trace(5,13,"FAR ");
		}
		else if(g_ViscaData.FLD.FOCUS_POS >= Focus_get_near_limit_pos())
		{
			if(stay_fcs > 1)	IF_Trace(5,13,"    ");
			else				IF_Trace(5,13,"NEAR");
		}
		else
		{
			if(stay_fcs > 1)	IF_Trace(5,13,"    ");
			else				IF_Trace(5,13,"MF  ");
		}

		if(AF_get_oneshot_af_status())
		{
			stay_fcs++;
			stay_fcs = stay_fcs%4;
		}
		else
			stay_fcs = 0;
	}
	else
		IF_Trace(5,13,"    ");


	User_Color_Set(12,13,8,FONT_ATTR_WHITE);
#endif
	switch(g_ViscaData.FLD.WB_MODE)
	{
		case 0x00:		IF_Trace(12,13,"        ");		break;
		case 0x01:		IF_Trace(12,13,"INDOOR  ");		break;
		case 0x02:		IF_Trace(12,13,"OUTDOOR ");		break;
		case 0x03:
		#ifndef WIN32
			User_Color_Set(12,13,8,FONT_ATTR_YELLOW);
		#endif
			if(stay_wb)		IF_Trace(12,13,"        ");
			else 			IF_Trace(12,13,"ONE PUSH");
		#ifndef WIN32
			if(Awb_GetPushIng())
			{
				stay_wb++;
				stay_wb = stay_wb%2;
			}
			else
				stay_wb = 0;
			break;
		#endif
		case 0x04:		IF_Trace(12,13,"ATW     ");		break;
		case 0x05:		IF_Trace(12,13,"MANUAL  ");		break;
		case 0x06:		IF_Trace(12,13,"        ");		break;
		default :		IF_Trace(12,13,"SVL     ");		break;
	}

	if(display_flg[DISPLAY_LR])
	{
		if(g_ViscaData.FLD.LR_ON)
			IF_Trace(30,1,"LR");
		else
			IF_Trace(30,1,"  ");
		display_flg[DISPLAY_LR] = STATE_OFF;
	}

	if(display_flg[DISPLAY_FLIP])
	{
		if(g_ViscaData.FLD.FLIP_ON)
			IF_Trace(34,1,"FLIP");
		else
			IF_Trace(34,1,"    ");
		display_flg[DISPLAY_FLIP] = STATE_OFF;
	}

	if(display_flg[DISPLAY_CAPTURE])
	{
		if(g_ViscaData.FLD.FREEZE_ON)
		{
			IF_Trace(40,1,"CAPTURE");
		#ifndef WIN32
			User_Color_Set(40,1,7,FONT_ATTR_YELLOW);
		#endif
		}
		else
		{
			IF_Trace(40,1,"       ");
		}

		display_flg[DISPLAY_FLIP] = STATE_OFF;
	}

	if(display_flg[DISPLAY_ALARM] == IF_PROCESS_TICK_3S)
	{
		IF_Trace(40,1,"ALARM");
		display_flg[DISPLAY_ALARM]--;
	}
	else if(display_flg[DISPLAY_ALARM] == 0);
	else if(display_flg[DISPLAY_ALARM] == 1)
	{
		IF_Trace(40,1,"       ");
		display_flg[DISPLAY_ALARM]--;
	}
	else
		display_flg[DISPLAY_ALARM]--;
}
/*********************************************************************************************************//**
* @param[in] param : id값과 입력값
* @retval
*	Result 에러출력
*	IF_ERNO			: 컨디션 통과
*	IF_ERNOPROC		: 조건이 잘못됨
* @brief
* === 5. LOCAL FUNCTION	: VISCA DISPLAY	===
*   VISCA Display Check
*************************************************************************************************************/
static void Visca_Display_Check(IFEVT_PARAM *param)
{
	switch(param->eepidx)
	{
		case VDX_ZOOM_POS:
		case VDX_DZOOM_MODE:
		case VDX_DZOOM_POS:
			display_flg[DISPLAY_ZOOM] = IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_APERTURE] = STATE_OFF;
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
		break;
		case VDX_WB_MODE:		display_flg[DISPLAY_WB_MODE] = STATE_ON;			break;
		case VDX_AE_MODE:
			display_flg[DISPLAY_BRIGHT]  = STATE_ON;
			display_flg[DISPLAY_SHUTTER] = STATE_ON;
			display_flg[DISPLAY_IRIS]    = STATE_ON;
			display_flg[DISPLAY_GAIN]    = STATE_ON;		break;
		case VDX_SHUTTER_STEP:	display_flg[DISPLAY_SHUTTER] = STATE_ON;			break;
		case VDX_IRIS_STEP:		display_flg[DISPLAY_IRIS] = STATE_ON;				break;
		case VDX_GAIN_STEP:		display_flg[DISPLAY_GAIN] = STATE_ON;				break;
		case VDX_BRIGHT_STEP:
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
			display_flg[DISPLAY_APERTURE] = STATE_OFF;
			display_flg[DISPLAY_ZOOM] = STATE_OFF;
			break;
		case VDX_COMP_ON:		display_flg[DISPLAY_EXP_COMP] = STATE_ON;			break;
		case VDX_EXP_COMP_VAL:	display_flg[DISPLAY_EXP_COMP] = STATE_ON;			break;
		case VDX_BLC_ON:		display_flg[DISPLAY_BACKLIGHT] = STATE_ON;			break;
		case VDX_APER_GAIN:
			display_flg[DISPLAY_APERTURE] = IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_ZOOM] = STATE_OFF;
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
			break;
		case VDX_LR_ON:			display_flg[DISPLAY_LR] = STATE_ON;					break;
		case VDX_FREEZE_ON:		display_flg[DISPLAY_CAPTURE] = STATE_ON;			break;
		case VDX_P_EFFECT :		display_flg[DISPLAY_P_EFFECT] = STATE_ON;			break;
		case VDX_FLIP_ON:		display_flg[DISPLAY_FLIP] = STATE_ON;				break;
		case VDX_DISP_ON:		display_flg[DISPLAY_ON] = STATE_ON;				break;
		case VDX_MOVE_DZOOM :
		case VDX_MOVE_ZOOM :
		case VDX_ZM_FCS_POS :
			display_flg[DISPLAY_ZOOM] = IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_APERTURE] = STATE_OFF;
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
			break;
		case VDX_MOVE_SHUT :	display_flg[DISPLAY_SHUTTER] = STATE_ON;			break;
		case VDX_MOVE_IRIS :	display_flg[DISPLAY_IRIS] = STATE_ON;				break;
		case VDX_MOVE_GAIN :	display_flg[DISPLAY_GAIN] = STATE_ON;				break;
		case VDX_MOVE_BRIGHT :
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
			display_flg[DISPLAY_APERTURE] = STATE_OFF;
			display_flg[DISPLAY_ZOOM] = STATE_OFF;
			break;
		case VDX_MOVE_EXPCOMP :	display_flg[DISPLAY_EXP_COMP] = STATE_ON;			break;
		case VDX_MOVE_APERTURE:
			display_flg[DISPLAY_APERTURE] = IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_ZOOM] = STATE_OFF;
			display_flg[DISPLAY_BRIGHT] = STATE_ON;
			break;
		case VDX_CAM_MEMCUS :
			Init_Display_Print();
			display_flg[DISPLAY_ZOOM] 		= IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_MEMCUS_CNT] = IF_PROCESS_TICK_3S;
			display_flg[DISPLAY_MEMCUS] 	= param->key;
		case VDX_REGITER_SET :
			display_flg[DISPLAY_CAMRES] = STATE_ON;
			break;
	}
}

/*********************************************************************************************************//**
* @retval none
* @brief
* === 6. LOCAL FUNCTION	: VIACA TITLE	===
*	Title을 초기화 한다.
*************************************************************************************************************/
static void Init_Title_Print(void)
{
	uint08 i;
	display_flg[DISPLAY_ACT] = 0;
	for(i = 0;i<0x0B;i++)
	{
		display_flg[DISPLAY_ACT] |= IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_ON,0);
	}
}
/*********************************************************************************************************//**
* @retval none
* @brief
* === 6. LOCAL FUNCTION	: VIACA TITLE	===
*	Title을 Print한다.
*************************************************************************************************************/
static void User_Title_Print(void)
{
	uint08 line_x,line_y;
	uint08 tmp;
	uint08 i,j;
	uint08 color;
	for(i = 0;i<0x0B;i++)
	{
		line_x = IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_H_POS,0);
		line_y = 1;
		color = IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_COLOR,0);
		switch(color)
		{
			case 0 : color = 1; break;
			case 1 : color = 3; break;
			case 2 : color = 0; break;
			case 3 : color = 2; break;
			case 4 : color = 1; break;
			case 5 : color = 1; break;
			case 6 : color = 1; break;
			case 7 : color = 1; break;
			default: color = 1; break;

		}
		if(IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_ON,0))
		{
			for(j=0 ; j < 44 ; j++)
			{
				IF_Trace(j , line_y+i,"%c",' ');
			}
			for(j=0;j<20;j++)
			{
				tmp = IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_LINE_CH1+j,0);
				if(tmp < 0x1A)//A~Z
				{
					tmp = 0x41+tmp;//0x41('A') ~ 0x5A('Z')
				}
				else
				{
					switch(tmp)
					{
						case 0x1A : tmp = '&';	break;
						case 0x1B : tmp = ' ';	break;
						case 0x1C : tmp = '?';	break;
						case 0x1D : tmp = '!';	break;
						case 0x1E : tmp = '1';	break;
						case 0x1F : tmp = '2';	break;
						case 0x20 : tmp = '3';	break;
						case 0x21 : tmp = '4';	break;
						case 0x22 : tmp = '5';	break;
						case 0x23 : tmp = '6';	break;
						case 0x24 : tmp = '7';	break;
						case 0x25 : tmp = '8';	break;
						case 0x26 : tmp = '9';	break;
						case 0x27 : tmp = '0';	break;
						case 0x41 : tmp = '$';	break;
						case 0x49 : tmp = '"';	break;
						case 0x4A : tmp = ':';	break;
						case 0x4B : tmp = '\'';	break;
						case 0x4C : tmp = '.';	break;
						case 0x4D : tmp = ',';	break;
						case 0x4E : tmp = '/';	break;
						case 0x4F : tmp = '-';	break;
						default : 	tmp = ' ';	break;
					}
				}
			#ifndef WIN32
				SetFontAttribute(line_y+i,line_x+j,color);
			#endif
				IF_Trace(line_x+j,line_y+i,"%c",tmp);
			}
		}
		else
		{
			for(j=0 ; j < 44 ; j++)
			{
				IF_Trace(j , line_y+i,"%c",' ');
			}
		}
	}
}

/*********************************************************************************************************//**
* @param[in] idx : 리셋할 idx 값
* @retval none
* @brief
*   OSD 초기화
*   IDX_값에 할당된 EEP값을 초기화 한다. (OSD에서 사용된다.)
*************************************************************************************************************/
static void User_EepInitial(EEP_IDX idx)
{
	int32 ret = -1;
	uint16 cnt = 0;

	if((idx > IDX_MD_STT && idx < IDX_MD_END) || (idx > IDX_PRI_STT && idx < IDX_PRI_END))
	{
		uint08 i;
		switch(idx)
		{
			case IDX_PRI_STATE:		 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_STATE ,0);			break;
			case IDX_PRI_TRANS: 	 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_TRANS	,3);		break;
			case IDX_PRI_COLOR: 	 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_COLOR	,0);		break;
			case IDX_PRI_MOSAIC:	 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_MOSAIC	,0);		break;
			case IDX_PRI_X :		 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_X		,20*((i&0x3)+1));	break;
			case IDX_PRI_Y :		 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_Y		,34+31*(i/4));	break;
			case IDX_PRI_W :		 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_W		,10);			break;
			case IDX_PRI_H :		 for(i=0;i<8;i++)	IF_EEPPrivacyUpdate(IFEVT_SETVAL,i,IDX_PRI_H		,10);			break;
			case IDX_MD_STATE :		 for(i=0;i<4;i++)	IF_EEPMotionUpdate(IFEVT_SETVAL,i,IDX_MD_ON,0); 			break;
			case IDX_MD_X : 		 for(i=0;i<4;i++)	IF_EEPMotionUpdate(IFEVT_SETVAL,i,IDX_MD_X,10+50*(i&0x01)); break;
			case IDX_MD_Y : 		 for(i=0;i<4;i++)	IF_EEPMotionUpdate(IFEVT_SETVAL,i,IDX_MD_Y,10+50*(i/2));	break;
			case IDX_MD_W : 		 for(i=0;i<4;i++)	IF_EEPMotionUpdate(IFEVT_SETVAL,i,IDX_MD_W,25); 			break;
			case IDX_MD_H : 		 for(i=0;i<4;i++)	IF_EEPMotionUpdate(IFEVT_SETVAL,i,IDX_MD_H,25); 			break;
			default:			     ret = -1;					break;
		}
	}
	else if(idx > IDX_NULL)
	{
		while(IFU_EepData[cnt].eepidx != IDX_NULL)
		{
			if(IFU_EepData[cnt].eepidx == idx)
			{
				IF_EEPUpdate(IFEVT_SETVAL, idx, IFU_EepData[cnt].def);
				break;
			}
			cnt++;
		}
	}
	else
	{
		switch(idx)
		{
		#ifndef WIN32
			case PRM_HALL_MAX:		 (HallParam.FLD.HallMax = DEF_HALL_MAX);				break;
			case PRM_HALL_MIN:		 (HallParam.FLD.HallMin = DEF_HALL_MIN);				break;
			case PRM_IRIS_LV:		 (ExposureParam.IrisTgt = 0);	break;

		#endif
			default:			     ret = -1;					break;
		}
	}

	if(idx == UIDX_WB_COLOR_TEMP)	wb_manual_osd_flg = 2;	//색온도가 초기화 될 때, 색온도값을 표시해줘야한다.
	else if(idx == IDX_DZOOM_MAG)	dzoom_osd_flg = 2;		//DZOOM이 초기화 될 때, DZOOM값을 표시해줘야한다.
	else if(idx == UIDX_PRI_ADJ_X)
	{
		Osd_pri_adj_flg= 1;		//Privacy가 초기화 될 때
		g_CamData.FLD.MADJ_3D_PAN_NT  = g_UserEepData.FLD.PRI_ADJ_X - 100;
	}
	else if(idx == UIDX_PRI_ADJ_Y)
	{
		Osd_pri_adj_flg= 1;
		g_CamData.FLD.MADJ_3D_TILT_NT = g_UserEepData.FLD.PRI_ADJ_Y - 100;
	}
	else if(idx == UIDX_R_HUE_N)
	{
#ifndef WIN32
		BYGAINNw(g_UserEepData.FLD.B_GAIN_N);
		BYGAINPw(g_UserEepData.FLD.B_GAIN_P);
		RYGAINNw(g_UserEepData.FLD.R_GAIN_N);
		RYGAINPw(g_UserEepData.FLD.R_GAIN_P);

		BYHUENw(g_UserEepData.FLD.R_HUE_N);
		BYHUEPw(g_UserEepData.FLD.R_HUE_P);
		RYHUENw(g_UserEepData.FLD.B_HUE_N);
		RYHUEPw(g_UserEepData.FLD.B_HUE_P);
#endif
	}
	else if(idx == UIDX_LAST_CGAIN)
	{
//		ExMw_GammaCtrl();
#ifndef WIN32
		LAST_CGAINw(g_UserEepData.FLD.LAST_CGAIN);
		LAST_YGAINw(g_UserEepData.FLD.LAST_YGAIN);
#endif
	}
}


/*********************************************************************************************************//**
* @param[in] param : id값과 입력값
* @retval
*	Result 에러출력
*	IF_ERNO			: 처리됨			해당함수에서 처리했다.
*	IF_ERNOPROC		: 처리하지 않음		해당함수에서는 처리하지 않았다.
*	IF_INVALIDVAL	: 처리할수 없음		잘못된 값을 입력했다.
* @brief
*	VISCA INQURY
*   알고리즘상에서 처리해야 되는 이벤트값들을 처리해준다.
*	리턴되는 결과값은 위와 같다.
*************************************************************************************************************/
static IFER Visca_Evt_Proc_Inq(IFEVT_PARAM *param)
{
	uint08 i;
	IFER err = IF_ERNO;
	switch(param->eepidx)
	{
		//case VDX_MODEL_CODE:
		//	param->key = 0x045f;
		//break;
		case VDX_CAM_MEMCUS:
			param->key = mem_addr;
		break;
		case VDX_TEMPERATURE:
		#ifndef WIN32
			param->key = etcFunc_get_temperature();
		#endif
		break;
		case VDX_CAM_ACTIV :
			param->key = 0;
		break;
		case VDX_TITLE_DISP :
			param->key = 0;
			for(i=0;i<0x0b;i++)
				param->key |= IF_EEPViscaTitleUpdate(IFEVT_GETVAL,i,VDX_TITLE_ON,0);
		break;
		case VDX_PRI_ON :
			param->key = 0;
			for(i=0;i<0x18;i++)
				param->key |= IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_ON,0);
		break;
		case VDX_MEM_PROVIDED :
		#ifndef WIN32
			param->key = Param_get_memory_provided();//Provide
		#endif
		break;
		case VDX_ICR_PROVIDED :
		#ifndef WIN32
			param->key = Param_get_icr_provided();//Provide
		#endif
		break;
		case VDX_SYS_PROVIDED :
		#ifndef WIN32
			param->key = Param_get_cam_system();//Provide
		#endif
		break;
		case VDX_EFLP_PROVIDED :
		#ifndef WIN32
			param->key = Param_get_e_flip_provided();//Provide
		#endif
		break;
		case VDX_AMASK_PROVIDED :
		#ifndef WIN32
			param->key = Param_get_adv_privacy_provided();//Provide
		#endif
		break;
		case VDX_STAB_PROVIDED :
		#ifndef WIN32
			param->key = 1;//Provide
		#endif
		break;
		case VDX_LOW_CONT_DETECTED :
#ifndef WIN32
			param->key = IsLowIllumination();
#endif
		break;
		case VDX_CAMERA_RECALL :
#ifndef WIN32
			param->key = 0;
#endif
		break;
		case VDX_FOCUS_COMMAND:
#ifndef WIN32
			param->key = Focus_get_busy_state();
#endif
		break;
		case VDX_ZOOM_COMMAND :
#ifndef WIN32
			param->key = Zoom_get_busy_state();
#endif
		break;

		default :
			err = IF_ERNOPROC;
		break;
	}
	return err;
}

/*********************************************************************************************************//**
* @param[in] param : id값과 입력값
* @retval
*	Result 에러출력
*	IF_ERNO : 처리됨				해당함수에서 처리했다.			-> 더이상 처리하지 마라
*	IF_ERNOPROC : 처리하지 않음		해당함수에서는 처리하지 않았다.
*	IF_INVALIDVAL : 처리할수 없음	잘못된 값을 입력했다.			-> 에러처리
* @brief
*   VISCA COMAND 처리
*	VDX 명령어 처리 : 3001 ~ 4800
*************************************************************************************************************/
static IFER Visca_Evt_Proc_Cmd(IFEVT_PARAM *param)
{
	IFER err = IF_ERNO;
	uint32 zoom_pos;
	//printf("IF_User_IFEVT [%d][%X]\n",param->eepidx,param->key);
	switch(param->eepidx)
	{
		case VDX_ZOOM_POS:
			if((g_ViscaData.FLD.DZOOM_ON == 1) && (g_ViscaData.FLD.DZOOM_MODE == 0))
			{	//DZOOM_ON, COMBINE
				if(param->key > 0x7AC0)
					param->key = 0x7AC0;
			}
			else
			{
				if(param->key > 0x4000)
					param->key = 0x4000;
			}
			zoom_pos = param->key;	//Zoom Move directly;
		#ifndef WIN32
			Preset_set_zoom_position(zoom_pos,10);
		#endif
		break;
		case VDX_DZOOM_POS:
		#ifndef WIN32
			g_ViscaData.FLD.DZOOM_POS = param->key;
			Dzoom_set_separate_position(g_ViscaData.FLD.DZOOM_POS);
		#endif
		break;

		case VDX_FOCUS_POS:
			/*if(g_ViscaData.FLD.F_MODE == 0)
			{
				// Focus Mode Auto에서는 실행 불가 함.
				return IF_INVALIDVAL;
			}*/
			if(param->key < 0x1000)
				param->key = 0x1000;
			else if(param->key > 0xF000 )
				param->key = 0xF000;
			if(param->key > g_ViscaData.FLD.NEAR_LIMIT)
				param->key = g_ViscaData.FLD.NEAR_LIMIT;
		#ifndef WIN32	//Focus Move directly;
#if 0
			Focus_set_direct_position(param->key);
#else
			Preset_set_focus_position(param->key,10);
#endif
		#endif
		break;

		case VDX_WB_MODE :
			if(param->key == 0x05 && g_ViscaData.FLD.WB_MODE != 5)
			{
				Reset_r_gain = g_ViscaData.FLD.R_GAIN;
				Reset_b_gain = g_ViscaData.FLD.B_GAIN;
			}
			err = IF_ERNOPROC;
		break;

		case VDX_AE_MODE :
			if(param->key == 0x0D && g_ViscaData.FLD.AE_MODE != 4)
			{
				Reset_bright = g_ViscaData.FLD.BRIGHT_STEP;
			}
			err = IF_ERNOPROC;
		break;

		case VDX_LR_ON:
		case VDX_FLIP_ON:
		case VDX_STB_ON :
		case VDX_STB_HOLD :
#ifndef WIN32
			PRV_Redraw();
#endif
			err = IF_ERNOPROC;
		break;

		default:
			err = IF_ERNOPROC;
		break;
	}

	return err;
}

/*********************************************************************************************************//**
* @param[in] param : id값과 입력값
* @retval
*	Result 에러출력
*	IF_ERNO			: 처리됨			해당함수에서 처리했다.
*	IF_ERNOPROC		: 처리하지 않음		해당함수에서는 처리하지 않았다.
*	IF_INVALIDVAL	: 처리할수 없음		잘못된 값을 입력했다.
* @brief
*   알고리즘상에서 처리해야 되는 이벤트값들을 처리해준다.
*	리턴되는 결과값은 위와 같다.
*	4801 ~ 5000
*************************************************************************************************************/
static IFER Visca_Evt_Proc_Move(IFEVT_PARAM *param)
{
	uint32 tmp;
	IFER err = IF_ERNO;
	uint32 zoom_pos,focus_pos;

	switch(param->eepidx)
	{
		case VDX_MOVE_RGAIN:
			if(param->key == 0x00)
			{
				g_ViscaData.FLD.R_GAIN = Reset_r_gain;
			}
			else
			{
				err = IF_ERNOPROC;
			}
		break;
		case VDX_MOVE_BGAIN:
			if(param->key == 0x00)
			{
				g_ViscaData.FLD.B_GAIN = Reset_b_gain;
			}
			else
			{
				err = IF_ERNOPROC;
			}
		break;
		case VDX_MOVE_DZOOM:
			tmp = (param->key & 0xf0);
			if(param->key == 0x00)
			{
			#ifndef WIN32	//Dzoom x1/Max switching
				Dzoom_set_direction(DZOOM_DIRECTION_TYPE_STOP);
			#endif
			}
			else if(tmp == 0x10)
			{
			#ifndef WIN32	//Dzoom x1/Max switching
				if(Dzoom_get_separate_position() == 0)
					Dzoom_set_separate_position(0xEB);
				else
					Dzoom_set_separate_position(0);
			#endif
			}
			else if(tmp == 0x20)
			{
				tmp = param->key&0xf;
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef	WIN32
				//Dzoom Variable Tele
				g_OsdData.FLD.ZOOM_SPEED = tmp;
				Dzoom_set_direction(DZOOM_DIRECTION_TYPE_TELE);
			#endif
			}
			else if(tmp == 0x30)
			{
				tmp = param->key&0xf;
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef	WIN32	//Dzoom Variable Wide
				g_OsdData.FLD.ZOOM_SPEED = tmp;
				Dzoom_set_direction(DZOOM_DIRECTION_TYPE_WIDE);
			#endif
			}
			else
				err = IF_ERNOPROC;
		break;
		case VDX_MOVE_ZOOM:
			tmp = (param->key & 0xf0);
			if(param->key == 0)
			{
			#ifndef	WIN32	//Stop
				ZT_set_tw_mode(ZOOM_TRK_DRV_STOP);
			#endif
			}
			else if(param->key == 2)
			{
			#ifndef	WIN32	//Tele
				g_OsdData.FLD.ZOOM_SPEED = 4;
				ZT_set_tw_mode(ZOOM_TRK_DRV_TELE);
			#endif
			}
			else if(param->key == 3)
			{
			#ifndef	WIN32	//Wide
				g_OsdData.FLD.ZOOM_SPEED = 4;
				ZT_set_tw_mode(ZOOM_TRK_DRV_WIDE);
			#endif
			}
			else if(tmp == 0x20)
			{
				tmp = param->key&0xf;
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef	WIN32	//Variable Tele
				g_OsdData.FLD.ZOOM_SPEED = tmp;
				ZT_set_tw_mode(ZOOM_TRK_DRV_TELE);
			#endif
			}
			else if(tmp == 0x30)
			{
				tmp = param->key&0xf;
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef	WIN32	//Variable Wide
				g_OsdData.FLD.ZOOM_SPEED = tmp;
				ZT_set_tw_mode(ZOOM_TRK_DRV_WIDE);
			#endif
			}
			else
				err = IF_ERNOPROC;
		break;
		case VDX_MOVE_FOCUS:
			if(g_ViscaData.FLD.F_MODE == 0)
			{
				// Focus Mode Auto에서는 실행 불가 함.
				return IF_INVALIDVAL;
			}

			tmp = (param->key & 0xf0);
			if(param->key == 0)
			{
			#ifndef WIN32	//Stop
				Focus_set_direction(FOCUS_DIRECTION_TYPE_NEUTRAL);
			#endif
			}
			else if(param->key == 2)
			{
			#ifndef WIN32	//Stop
				Focus_set_focus_speed(4);
				Focus_set_direction(FOCUS_DIRECTION_TYPE_FAR);
			#endif
			}
			else if(param->key == 3)
			{
			#ifndef WIN32	//Near
				Focus_set_focus_speed(4);
				Focus_set_direction(FOCUS_DIRECTION_TYPE_NEAR);
			#endif
			}
			else if(tmp == 0x20)
			{
				tmp = param->key&0xf;//speed
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef WIN32	//Variable Far
				Focus_set_focus_speed(tmp);
				Focus_set_direction(FOCUS_DIRECTION_TYPE_FAR);
			#endif
			}
			else if(tmp == 0x30)
			{
				tmp = param->key&0xf;
				if(tmp>7)	return IF_INVALIDVAL;
			#ifndef WIN32	//Variable Naer
				Focus_set_focus_speed(tmp);
				Focus_set_direction(FOCUS_DIRECTION_TYPE_NEAR);
			#endif
			}
			else
				err = IF_ERNOPROC;
		break;

		case VDX_ZM_FCS_POS:
			zoom_pos = (param->key>>16);
			focus_pos = (param->key&0xffff);

			if(param->key < 0x1000)
			{
				param->key = 0x1000;
			}
			else if(param->key > 0xF000 )
			{
				param->key = 0xF000;
			}

 			if(param->key > g_ViscaData.FLD.NEAR_LIMIT)
			{
				param->key = g_ViscaData.FLD.NEAR_LIMIT;
			}

			if((g_ViscaData.FLD.DZOOM_ON == 1) && (g_ViscaData.FLD.DZOOM_MODE == 0))
			{
				if(zoom_pos > 0x7AC0)
					zoom_pos = 0x7AC0;
			}
			else
			{
				if(zoom_pos > 0x4000)
					zoom_pos = 0x4000;
			}

		#ifndef WIN32
			Preset_set_zoom_position(zoom_pos,10);

#if 0
			Focus_set_direct_position(focus_pos);
#else
			Preset_set_focus_position(focus_pos,10);
#endif
		#endif
		break;
		case VDX_PUSH_WB:
			#ifndef WIN32
				Awb_OnePush();
			#endif
		break;
		case VDX_INIT_CAM:
			if(param->key == 1)		//Lens Init
			{
			#ifndef WIN32
				Lens_start_end_sensing();
			#endif
			}
			else if(param->key == 3)//Cam Reset
			{
			#ifndef WIN32
				Param_system_reboot(SYSTEM_REBOOT_DO_NOT_SAVE);
			#endif
			}
			else	err = IF_INVALIDVAL;
		break;
		case VDX_CAM_MEMCUS :
			tmp = param->key>>8;
			//param->key = param->key & 0xFF;
			//printf("tmp[%d],dat[%d]\n",tmp,param->key);
		#ifndef WIN32
			PRV_Redraw();
			if((param->key&0xff) == 0x7F)
			{
				switch(tmp)
				{
					case 0 :	Preset_custom_reset();		break;
					case 1 :	Preset_custom_set();		break;
					case 2 :
						Preset_custom_recall();
						mem_addr = param->key&0xff;
					break;
					default:	err = IF_INVALIDVAL;		break;
				}
			}
			else if((param->key&0xff) > 0x0F)
			{
				err = IF_INVALIDVAL;		break;
			}
			else
			{
				switch(tmp)
				{
					case 0 :	Preset_memory_reset(param->key);	break;
					case 1 :	Preset_memory_set(param->key);		break;
					case 2 :
						Preset_memory_recall(param->key);
						mem_addr = param->key&0xff;
						break;
					default:	err = IF_INVALIDVAL;				break;
				}
			}
		#endif
		break;
		case VDX_FCS_PUSH:
			if(param->key == 1)//PUSH AF
			{
			#ifndef WIN32
				/*if(g_ViscaData.FLD.F_MODE == 0)
				{
					// Focus Mode Auto에서는 실행 불가 함.
					return IF_INVALIDVAL;
				}*/
				AF_OneShotAf(AF_TRIGGER_ONE_SHOT);
			#endif
			}
			else if(param->key == 2)//INF
			{
				g_ViscaData.FLD.NEAR_LIMIT = 0x1000;
			}
			else	err = IF_INVALIDVAL;
		break;

		case VDX_MEM_SAVE_DAT :
		#ifndef WIN32
			Param_store_visca_area(VISCA_MEMORY_SAVE_AREA);
		#endif
			err = IF_ERNOPROC;
		break;
		case VDX_REGITER_SET:
		#ifndef WIN32
			Param_store_visca_area(VISCA_REG_AREA);
			err = IF_ERNOPROC;
		#endif
		break;
		default:
			err = IF_ERNOPROC;
		break;
	}

	return err;
}

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*	Osd에서 특정 값에 따라서 OSD하부 항목이 바뀌어야 할경우가 있다
*	EEP값이 LOAD되거나 값이 초기화 될 때, 다음 함수를 이용해서 아이템이나 하위항목을 Swap해준다.
*	예)		Dzoom Sperate에서 DZoom ON의 하위 메뉴가 활성화 되는지.
*************************************************************************************************************/
static void IFU_Swap_Osd_Struct()
{
	if(g_OsdData.FLD.VOUT_FORMAT == 0 )
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_1080_30p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_1080_30p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_1080_30p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_1080_30p;

	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 1)
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_1080_25p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_1080_25p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_1080_25p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_1080_25p;

	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 2)
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 3)//720/50p
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 4)//1080/60i
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 5)//1080/50i
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
	}
	else if(g_OsdData.FLD.VOUT_FORMAT == 6)//1080/60p
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_60p;
	}
	else
	{
		OSD_AdjAEAFMap[2].pitem = (OSD_ITEM *)OSD_ShutItem_720_50p;
		OSD_AdjAEAFMap[3].pitem = (OSD_ITEM *)OSD_ShutItem_720_50p;
		OSD_ExposureShutMap[0].pitem = (OSD_ITEM *)OSD_ShutItem_720_50p;
		OSD_ExposureManualMap[1].pitem = (OSD_ITEM *)OSD_ShutItem_720_50p;
	}

	g_UserEepData.FLD.CAM_RES = g_OsdData.FLD.VOUT_FORMAT;
}

/*********************************************************************************************************//**
* @param[in] key : 입력된 키값
* @retval none
* @brief
*	EEP WRITE 동작이 일어난 이후에, 한번 콜해준다.
*	EEP값에 따라서 바뀌는 OSD나 통신속도, 통신타입 등을 바꿔준다.
*************************************************************************************************************/
static void IFU_After_Save()
{
	const uint32 mltply[7] = {1,2,4,8,16,24,48};
	IFU_Swap_Osd_Struct(); // 해상도/주파수에 따라 OSD메뉴를 바꿔준다.
	g_OsdData.FLD.PROTOCOL = g_UserEepData.FLD.PRTCL_TYPE;
	g_OsdData.FLD.BAUDRATE = g_UserEepData.FLD.PRTCL_BAUD;
	switch(g_OsdData.FLD.BAUDRATE)
	{
		case 2: 	g_ViscaData.FLD.COMM_BAUDRATE = 0; 	break;	//9600
		case 3: 	g_ViscaData.FLD.COMM_BAUDRATE = 1; 	break;	//19200
		case 4: 	g_ViscaData.FLD.COMM_BAUDRATE = 2; 	break;	//38400
		case 6: 	g_ViscaData.FLD.COMM_BAUDRATE = 3; 	break;	//115200
		default : 	break;//일단 적용,
	}
#ifndef WIN32
	if(g_OsdData.FLD.BAUDRATE > 6)
		g_OsdData.FLD.BAUDRATE = 6;

	InitUartDriverComm(2400*mltply[g_OsdData.FLD.BAUDRATE],IF_PTC_SetRxQue,IF_PTC_GetTxQue);
#endif
	if(g_OsdData.FLD.DZOOM_MODE == 0)
	{
		OSD_DZModeItem[1].pdep = 0; //DZoom Combine
	}
	else if(g_OsdData.FLD.DZOOM_MODE == 1)
	{
		OSD_DZModeItem[1].pdep = (OSD_MAP *)OSD_DZoomMap;
	}

	if(g_UserEepData.FLD.VISCA_OSD_MENU == 0)
	{
		IF_OsdMapRegister(OSD_gMap_Visca,OSD_gHiddenMap);
		g_OsdData.FLD.PROTOCOL = 3;
	}
	else
	{
		IF_OsdMapRegister(OSD_gMap,OSD_gHiddenMap);
	}
}

/*********************************************************************************************************//**
* @param[in] key : 입력된 키값
* @retval none
* @brief
*	EEP READ 동작이 일어난 이후에, 한번 콜해준다.
*	EEP값에 따라서 바뀌는 OSD나 통신속도, 통신타입 등을 바꿔준다.
*************************************************************************************************************/
static void IFU_After_Load()
{
	const uint32 mltply[7] = {1,2,4,8,16,24,48};
	IFU_Swap_Osd_Struct();

	switch(g_ViscaData.FLD.COMM_BAUDRATE)
	{
		default:
		case 0: 	g_OsdData.FLD.BAUDRATE = 2; 	break;	//9600
		case 1: 	g_OsdData.FLD.BAUDRATE = 3; 	break;	//19200
		case 2: 	g_OsdData.FLD.BAUDRATE = 4; 	break;	//38400
		case 3: 	g_OsdData.FLD.BAUDRATE = 6; 	break;	//115200
	}

	g_UserEepData.FLD.PRTCL_TYPE = g_OsdData.FLD.PROTOCOL;
	g_UserEepData.FLD.PRTCL_BAUD = g_OsdData.FLD.BAUDRATE;

	if(g_UserEepData.FLD.VISCA_OSD_MENU == 0)
	{
		IF_OsdMapRegister(OSD_gMap_Visca,OSD_gHiddenMap);
		g_OsdData.FLD.PROTOCOL = 3;
	}
	else
	{
		IF_OsdMapRegister(OSD_gMap,OSD_gHiddenMap);
	}
#ifndef WIN32
	if(g_OsdData.FLD.BAUDRATE > 6)
		g_OsdData.FLD.BAUDRATE = 6;

	InitUartDriverComm(2400*mltply[g_OsdData.FLD.BAUDRATE],IF_PTC_SetRxQue,IF_PTC_GetTxQue);
#endif
	if(g_OsdData.FLD.DZOOM_MODE == 0)
		OSD_DZModeItem[1].pdep = 0; //DZoom Combine
	else if(g_OsdData.FLD.DZOOM_MODE == 1)
		OSD_DZModeItem[1].pdep = (OSD_MAP *)OSD_DZoomMap;
#ifndef WIN32
	// Color Adjust
	BYGAINNw(g_UserEepData.FLD.B_GAIN_N);
	BYGAINPw(g_UserEepData.FLD.B_GAIN_P);
	RYGAINNw(g_UserEepData.FLD.R_GAIN_N);
	RYGAINPw(g_UserEepData.FLD.R_GAIN_P);

	BYHUENw(g_UserEepData.FLD.R_HUE_N);
	BYHUEPw(g_UserEepData.FLD.R_HUE_P);
	RYHUENw(g_UserEepData.FLD.B_HUE_N);
	RYHUEPw(g_UserEepData.FLD.B_HUE_P);
#endif
}
/*********************************************************************************************************//**
* @param[in] zone : Select Privacy Mask Num
* @retval none
* @brief
*	Init a privacy mask
*************************************************************************************************************/
static void IFU_Init_Privavy_mask(int08 zone)
{
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_STATE,0);
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_X,20*((zone&0x3)+1));
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_Y,34+31*(zone/4));
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_W,10);
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_H,10);
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_COLOR,0);//black
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_TRANS,3);
	IF_EEPPrivacyUpdate(IFEVT_SETVAL,zone,IDX_PRI_MOSAIC,0);//0ff
}

/*********************************************************************************************************//**
* @param[in] zone : Select MD Num
* @retval none
* @brief
*	Init a motion detector
*************************************************************************************************************/
static void IFU_Init_Motion_mask(int08 zone)
{
	IF_EEPMotionUpdate(IFEVT_SETVAL,zone,IDX_MD_STATE,0);
	IF_EEPMotionUpdate(IFEVT_SETVAL,zone,IDX_MD_X,10+50*(zone&0x01));
	IF_EEPMotionUpdate(IFEVT_SETVAL,zone,IDX_MD_Y,10+50*(zone/2));
	IF_EEPMotionUpdate(IFEVT_SETVAL,zone,IDX_MD_W,25);
	IF_EEPMotionUpdate(IFEVT_SETVAL,zone,IDX_MD_H,25);
}



/*********************************************************************************************************//**
* @param[in] evt	: OSD EVT를 처리해준다.
* @param[in] *param : IDX값과 Value값
* @retval none
* @brief
*	User 이벤트를 처리해준다.
*	6000 ~ 6013
*************************************************************************************************************/
void IFU_UEvent_Call(IFEVT evt, IFEVT_PARAM *param)
{
//	uint08 i;
	switch(param->eepidx)
	{
		case UIDX_HALLADJ :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				IF_Trace(16,17,"Osd Hide for Hall Adj ");
			#ifndef WIN32
				//Write Code here for Handling '' Message
				Lens_HallAdjust();
			#endif
				osd_hide_mode = OSD_HIDE_HALL_ADJ;
			}
		break;
		case UIDX_LENSADJ :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				IF_Trace(16,17,"Osd Hide for Lens Adj");
			#ifndef WIN32
				//Write Code here for Handling 'UIDX_LENSADJ' Message
				Lens_OffsetAdjust();
			#endif
				osd_hide_mode = OSD_HIDE_LENS_ADJ;
			}
		break;
		case UIDX_DEFECTADJ :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				//IF_Trace(16,17,"Osd Hide for Defect Adj");
				osd_hide_mode = OSD_HIDE_DEFECT_ADJ;
			#ifndef WIN32
				//Write Code here for Handling '' Message
				gDefect_State = DEFECT_STATE_RUN;
			#endif
			}
		break;
		case UIDX_SHADEADJ :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				IF_Trace(16,17,"Osd Hide for Shade Adj");
				osd_hide_mode = OSD_HIDE_SHADE_ADJ;
			#ifndef WIN32
				//Write Code here for Handling '' Message
				gShade_State = SHADE_STATE_RUN;
			#endif
			}
		break;
		/*Load Event*/
		case UIDX_DEFECTLOAD :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				IF_Trace(16,17,"Osd Hide for Defect Load");
				osd_hide_mode = OSD_HIDE_DEFECTLOAD;
			#ifndef WIN32
				//Write Code here for Handling '' Message
				gDefect_State = DEFECT_STATE_LOAD_EEPROM;
			#endif
			}
		break;
		case UIDX_SHADELOAD :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_OsdHide();
				IF_Trace(16,17,"Osd Hide for Shade Load");
				osd_hide_mode = OSD_HIDE_SHADELOAD;
			#ifndef WIN32
				//Write Code here for Handling '' Message
				gShade_State = SHADE_STATE_LOAD_EEPROM;
			#endif
			}
		break;
		case UIDX_PRI_RESETZONE :
			if(param->key == OSD_CKEYDOWN)
			{
				IFU_Init_Privavy_mask((uint08)IF_EEPGetPrivZone());
				IF_OsdRefresh();
			#ifndef WIN32
				//Write Code here for Handling '' Message
				PRV_Redraw();
			#endif
			}
		break;
		case UIDX_MD_RESETZONE :
			if(param->key == OSD_CKEYDOWN)
			{
				IFU_Init_Motion_mask((uint08)IF_EEPGetMotionZone());
				IF_OsdRefresh();
			#ifndef WIN32
				//Write Code here for Handling '' Message
			#endif
			}
		break;
		case UIDX_PRI_CENTER :
			if(param->key == OSD_CKEYDOWN)
			{
				IF_EEPPrivacyUpdate(IFEVT_SETVAL,(uint08)IF_EEPGetPrivZone(),IDX_PRI_X,50);
				IF_EEPPrivacyUpdate(IFEVT_SETVAL,(uint08)IF_EEPGetPrivZone(),IDX_PRI_Y,50);
				IF_OsdRefresh();
			#ifndef WIN32
				//Write Code here for Handling '' Message
				PRV_Redraw();
			#endif
			}
		break;
		case UIDX_3DPRI_ZOOM :
			IF_Trace(16,17,"Zoom : %d             ",_3d_adj_zm_flg);
			#ifndef WIN32
				//Write Code here for Handling '' Message
				if(param->key == OSD_LKEYDOWN)		_3d_adj_zm_flg = 1;
				else if(param->key == OSD_RKEYDOWN)	_3d_adj_zm_flg = 2;
			#endif
		break;
		case UIDX_3DPRI_ADJ :
			#ifndef WIN32
				//Write Code here for Handling '' Message
				Set_Mask_Debug();
			#endif
				Osd_pri_adj_flg = 1;
		break;
		case UIDX_DEFEC_IN :
#ifndef WIN32
			//Write Code here for Handling '' Message
			if(param->key == OSD_CKEYDOWN)
			{
				osd_defect_adj_flg = 1;

				gDefect_State = DEFECT_STATE_MENU_IN1;
			}
#endif
			break;
		case UIDX_SHADE_IN :
#ifndef WIN32
			//Write Code here for Handling '' Message
			if(param->key == OSD_CKEYDOWN)
			{
				gShade_State = SHADE_STATE_MENU_IN;
			}
#endif
	break;
		case UIDX_TNN_EXPOSURE :
			osd_tune_exp_flg = 1;
		break;
		case UIDX_TUNE_ADJ_COLOR :
			osd_tune_color_adj = 1;
		break;
		/*//For EEP_MW TEST ,KSH 140317
		case UIDX_EEP_TEST_REFRESH :
			for(i=0;i<100;i++)
			{
				wtmp[i] = 0;
			}
			DebugPrintf("\n===========0========= %X\n",&rtmp[g_UserEepData.FLD.EEP_ADDR]);
			EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
			EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
		break;
		*/
		default :		break;
	}
}
/*********************************************************************************************************//**
* @param[in] evt	: OSD EVT를 처리해준다.
* @param[in] *param : IDX값과 Value값
* @retval none
* @brief
*	이벤트를 처리해준다.
*	2001 ~ 4514
*************************************************************************************************************/
static void IFU_Event_Call(IFEVT evt, IFEVT_PARAM *param)
{
	uint32 tmp;
#ifndef WIN32
	tmp = FALSE;
#endif
	switch(param->eepidx)
	{
		case IDX_MADJ_3D_PAN_NT:
#ifndef WIN32
			//Write Code here for Handling '' Message
			PRV_Redraw();
#endif
			Osd_pri_adj_flg = 1;
		break;

		case IDX_MADJ_3D_TILT_NT:
#ifndef WIN32
			//Write Code here for Handling '' Message
			PRV_Redraw();
#endif
			Osd_pri_adj_flg = 1;
		break;

		case IDX_OSDOFF:
			if(Osd_pri_flg)			Osd_pri_flg = 0;
			if(Osd_md_flg)			Osd_md_flg = 0;
			if(Osd_pri_adj_flg)		Osd_pri_adj_flg = 0;
			if(osd_defect_adj_flg){
				osd_defect_adj_flg = 0;
#ifndef WIN32
				//Write Code here for Handling '' Message
				gDefect_State = DEFECT_STATE_MENU_OUT;
#endif
			}
			osd_tune_exp_flg = 0;
			title_change = 1;
			osd_off_flg = 1;
		break;
		/*Eep Save/Load Event*/
		case IDX_OSDEXITSAVE:
#ifndef COMMAND_CHECK
			IF_Trace(16,17,"Osd Exit Save        ");
#endif
			IFU_After_Save();
#ifndef WIN32
			//Code here for Handling '' Message
			Param_write_eep_struct(EP_IMMEDIATELY|EP_FULL_AREA);
#endif
		break;
		case IDX_OSDEXITNOTSAVE:
#ifndef COMMAND_CHECK
			IF_Trace(16,17,"Osd Exit None Save	 ");
#endif
			tmp = g_OsdData.FLD.VOUT_FORMAT;

#ifndef WIN32
			Param_read_eep_struct(EP_IMMEDIATELY|EP_FULL_AREA);
#endif
			if(tmp != g_OsdData.FLD.VOUT_FORMAT)
				IFU_Camres_Chg(g_OsdData.FLD.VOUT_FORMAT);
			IFU_After_Load();
		break;
		case IDX_CAMREBOOTSAVE:
#ifndef COMMAND_CHECK
			IF_Trace(16,17,"Reboot Save          ");
#endif
			IFU_After_Save();
#ifndef WIN32
			Param_system_reboot(SYSTEM_REBOOT_SAVE);
#endif
		break;
		case IDX_CAMREBOOTNOTSAVE:
#ifndef COMMAND_CHECK
			IF_Trace(16,17,"Reboot Not Save      ");
#endif
#ifndef WIN32
			//Code here for Handling '' Message
			Param_system_reboot(SYSTEM_REBOOT_DO_NOT_SAVE);
			IFU_After_Load();
#endif
		break;

		case IDX_RETURN:
			if(param->key == OSD_CKEYDOWN)
			{
				if(Osd_pri_flg) 		Osd_pri_flg = 0;
				if(Osd_md_flg)			Osd_md_flg = 0;
				if(Osd_pri_adj_flg)		Osd_pri_adj_flg = 0;
				if(osd_defect_adj_flg){
					osd_defect_adj_flg = 0;
#ifndef WIN32
					//Write Code here for Handling '' Message
					gDefect_State = DEFECT_STATE_MENU_OUT;
#endif
				}
				else if(osd_tune_color_adj) osd_tune_color_adj = 0;
				osd_tune_exp_flg = 0;
			}
#ifndef WIN32
			Set_Mask_Normal();
#endif
		break;

		case IDX_INITIAL:
			if(param->key == OSD_CKEYDOWN)
			{
				if(IFU_Osd_PriOn())
				{
#ifndef WIN32
					//Write Code here for Handling '' Message
					PRV_Redraw();
#endif
				}
				else if(IFU_Osd_MDOn());
				if(osd_tune_color_adj)
				{
#ifndef WIN32
					BYGAINNw(g_UserEepData.FLD.B_GAIN_N);
					BYGAINPw(g_UserEepData.FLD.B_GAIN_P);
					RYGAINNw(g_UserEepData.FLD.R_GAIN_N);
					RYGAINPw(g_UserEepData.FLD.R_GAIN_P);

					BYHUENw(g_UserEepData.FLD.R_HUE_N);
					BYHUEPw(g_UserEepData.FLD.R_HUE_P);
					RYHUENw(g_UserEepData.FLD.B_HUE_N);
					RYHUEPw(g_UserEepData.FLD.B_HUE_P);
#endif
				}
			}
		break;
		case IDX_FRESET :
#ifndef WIN32
			//Write Code here for Handling '' Message
			if(param->key == OSD_KEYNULL)
			{
			#ifndef COMMAND_CHECK
				IF_Trace(16,17,"Factory Reset        ");
			#endif
				Param_sys_config(SYSTEM_PARAM_CONFIG_FACTORY);
				IFU_After_Load();
				IF_OsdRefresh();
			}
#endif
		break;
	}
}
/*********************************************************************************************************//**
* @param[in] evt	: OSD EVT를 처리해준다.
* @param[in] *param : IDX값과 Value값
* @retval none
* @brief
*	User EEP값에 대한 이벤트를 처리해준다.
*	5001 ~ 5502
*************************************************************************************************************/
void IFU_UEep_Call(IFEVT evt, IFEVT_PARAM *param)
{
//	uint08 i;
	switch(param->eepidx)
	{
		case UIDX_B_GAIN_P:
		case UIDX_B_GAIN_N:
		case UIDX_R_GAIN_P:
		case UIDX_R_GAIN_N:
		case UIDX_B_HUE_P:
		case UIDX_B_HUE_N:
		case UIDX_R_HUE_P:
		case UIDX_R_HUE_N:
#ifndef WIN32
			BYGAINNw(g_UserEepData.FLD.B_GAIN_N);
			BYGAINPw(g_UserEepData.FLD.B_GAIN_P);
			RYGAINNw(g_UserEepData.FLD.R_GAIN_N);
			RYGAINPw(g_UserEepData.FLD.R_GAIN_P);

			BYHUENw(g_UserEepData.FLD.R_HUE_N);
			BYHUEPw(g_UserEepData.FLD.R_HUE_P);
			RYHUENw(g_UserEepData.FLD.B_HUE_N);
			RYHUEPw(g_UserEepData.FLD.B_HUE_P);
#endif
		break;
		case UIDX_TEMP_1 :
			if(param->key == OSD_CKEYDOWN)
			{
				//g_UserEepData.FLD.OSD_DEBUG_STATE = OSD_TRACE_PARE3;
				IF_OsdOff();
				param->key = 0;
			}
#ifndef WIN32
			//Write Code here for Handling '' Message
#endif
		break;
		case UIDX_PRTCL_TYPE:
			if(g_UserEepData.FLD.VISCA_OSD_MENU == 0)
			{
				g_UserEepData.FLD.PRTCL_TYPE = 3;
				IF_OsdItemRefresh(0);
			}
		break;
		/*output format 결정*/
		case UIDX_CAM_RES:
			//Write Code here for Handling '' Message
			if(param->key == OSD_CKEYDOWN)
			{
#ifndef WIN32
				g_OsdData.FLD.VOUT_FORMAT = g_UserEepData.FLD.CAM_RES;
				IFU_Camres_Chg(g_OsdData.FLD.VOUT_FORMAT);

				IFU_Swap_Osd_Struct();
				//IFU_After_Load();
#endif
			}
		break;
		case UIDX_WB_PUSH:
			if(param->key == OSD_CKEYDOWN)
			{
			#ifndef COMMAND_CHECK
				IF_Trace(16,17,"PUSH WHITE BAL      ");
			#endif
#ifndef WIN32
				//Write Code here for Handling '' Message
				Awb_PushAlgo();
#endif
			}
		break;
		case UIDX_WB_COLOR_TEMP:
			wb_manual_osd_flg = 2;
#ifndef WIN32
			//Write Code here for Handling '' Message
			Awb_colorTemp();
#endif
		break;
		case UIDX_PRI_ADJ_X:
#ifndef WIN32
			//Write Code here for Handling 'Change Privacy mask Adj X Value' Message
			PRV_Redraw();
#endif
			g_CamData.FLD.MADJ_3D_PAN_NT = (int08)g_UserEepData.FLD.PRI_ADJ_X - 100;
			Osd_pri_adj_flg = 1;
		break;

		case UIDX_PRI_ADJ_Y:
#ifndef WIN32
			//Write Code here for Handling 'Change Privacy mask Adj Y Value' Message
			PRV_Redraw();
#endif
			g_CamData.FLD.MADJ_3D_TILT_NT = (int08)g_UserEepData.FLD.PRI_ADJ_Y - 100;
			Osd_pri_adj_flg = 1;
		break;
		case UIDX_GAMMA1:
			//Set Tunning GAMMA !!!!
//			ExMw_GammaCtrl();
			//g_UserEepData.FLD.GAMMA
		break;
		case UIDX_GAMMA2:
			//Set Tunning GAMMA !!!!
//			ExMw_GammaCtrl();
			//g_UserEepData.FLD.GAMMA
		break;
		case UIDX_LAST_YGAIN:
		case UIDX_LAST_CGAIN:
#ifndef WIN32
			LAST_YGAINw(g_UserEepData.FLD.LAST_YGAIN);
			LAST_CGAINw(g_UserEepData.FLD.LAST_CGAIN);
#endif
		break;

		/*//For EEP_MW TEST ,KSH 140317
		case UIDX_EEP_TEST_START :
			if(param->key == OSD_CKEYDOWN)
			{
				switch(g_UserEepData.FLD.EEP_TEST)
				{
					case 0:
						for(i=0;i<100;i++)
						{
							wtmp[i] = i;
						}
						DebugPrintf("\n===========0========= %X\n",&rtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
					break;
					case 1:
						DebugPrintf("\n===========1=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+1;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x20 ,0x10 ,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x20]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x20 ,0x10 ,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x20]);
						DebugPrintf("\n===========1=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x10 ,0x10 ,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x10]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x10 ,0x10 ,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x10]);
						DebugPrintf("\n===========1=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x30 ,0x20 ,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x30]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x30 ,0x20 ,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x30]);
					break;
					case 2:
						DebugPrintf("\n===========2=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+2;
						}
						DebugPrintf("\n===========2=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x27 ,0x20,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x27]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x27 ,0x20,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x27]);
						DebugPrintf("\n===========2=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x08 ,0x20,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x08]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x08 ,0x20,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x08]);
						DebugPrintf("\n===========2=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x46 ,0x10,&wtmp[g_UserEepData.FLD.EEP_ADDR +0x46]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x46 ,0x10,&rtmp[g_UserEepData.FLD.EEP_ADDR +0x46]);
					break;
					case 3:
						DebugPrintf("\n===========3=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+3;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x0B ,0x0A ,&wtmp[g_UserEepData.FLD.EEP_ADDR + 0x0B]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x0B ,0x0A ,&rtmp[g_UserEepData.FLD.EEP_ADDR + 0x0B]);
						DebugPrintf("\n===========3=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x00 ,0x0A ,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x00 ,0x0A ,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
						DebugPrintf("\n===========3=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x16 ,0x0A ,&wtmp[g_UserEepData.FLD.EEP_ADDR + 0x16]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 0x16 ,0x0A ,&rtmp[g_UserEepData.FLD.EEP_ADDR + 0x16]);
					break;
					case 4:
						DebugPrintf("\n===========4=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+4;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 25 ,52,&wtmp[g_UserEepData.FLD.EEP_ADDR+25]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 25 ,52,&rtmp[g_UserEepData.FLD.EEP_ADDR+25]);
						DebugPrintf("\n===========4=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 10 ,30,&wtmp[g_UserEepData.FLD.EEP_ADDR+10]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 10 ,30,&rtmp[g_UserEepData.FLD.EEP_ADDR+10]);
						DebugPrintf("\n===========4=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 35 ,48,&wtmp[g_UserEepData.FLD.EEP_ADDR+35]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600 + g_UserEepData.FLD.EEP_ADDR + 35 ,48,&rtmp[g_UserEepData.FLD.EEP_ADDR+35]);
					break;
					case 5:
						DebugPrintf("\n===========5=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+5;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,50,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,50,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
						DebugPrintf("\n===========5=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,60,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,60,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
					break;
					case 6:
						DebugPrintf("\n===========6=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+6;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR+8,50,&wtmp[g_UserEepData.FLD.EEP_ADDR+8]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR+8,50,&rtmp[g_UserEepData.FLD.EEP_ADDR+8]);
						DebugPrintf("\n===========6=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,58,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,58,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
					break;
					case 7:
						DebugPrintf("\n===========7=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+7;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR + 25,50,&wtmp[g_UserEepData.FLD.EEP_ADDR + 25]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR + 25,50,&rtmp[g_UserEepData.FLD.EEP_ADDR + 25]);
						DebugPrintf("\n===========7=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR + 10 ,80,&wtmp[g_UserEepData.FLD.EEP_ADDR + 10]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR + 10 ,80,&rtmp[g_UserEepData.FLD.EEP_ADDR + 10]);
					break;
					case 8:
						DebugPrintf("\n===========8=========\n");
						for(i=0;i<100;i++)
						{
							wtmp[i] = i+8;
						}
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&wtmp[g_UserEepData.FLD.EEP_ADDR]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR,100,&rtmp[g_UserEepData.FLD.EEP_ADDR]);
						DebugPrintf("\n===========8=========\n");
						EEP_MW_Manager(EEP_ACCESS_WRITE ,0x0600+g_UserEepData.FLD.EEP_ADDR+10,80,&wtmp[g_UserEepData.FLD.EEP_ADDR+10]);
						EEP_MW_Manager(EEP_ACCESS_READ  ,0x0600+g_UserEepData.FLD.EEP_ADDR+10,80,&rtmp[g_UserEepData.FLD.EEP_ADDR+10]);
					break;
					case 9:

					break;
					case 10:

					break;
				}
			}
		break;
		*/

	}
}
/*********************************************************************************************************//**
* @param[in] evt	: OSD EVT를 처리해준다.
* @param[in] *param : IDX값과 Value값
* @retval none
* @brief
*	User EEP값에 대한 이벤트를 처리해준다.
*	0 ~ 1144
*************************************************************************************************************/
void IFU_Eep_Call(IFEVT evt, IFEVT_PARAM *param)
{
	switch(param->eepidx)
	{

		/*Push Event*/
		case IDX_FOCUS_MODE:	//101
			if(param->key == OSD_CKEYDOWN)
			{
				if(g_OsdData.FLD.FOCUS_MODE == 1)
				{
				#ifndef WIN32
					//Write Code here for Handling '' Message
					AF_OneShotAf(AF_TRIGGER_ONE_SHOT);
				#endif

				#ifndef COMMAND_CHECK
					IF_Trace(16,17,"Push Fcs Md         ");
				#endif
				}
			}
		break;

		case IDX_FOCUS_DIST:	//105
		#ifndef WIN32
/*
			switch(g_OsdData.FLD.FOCUS_DIST)
			{
				case 0: 	Focus_set_near_limit(FOCUS_NEAR_LIMIT_1CM); 	break;
				case 1: 	Focus_set_near_limit(FOCUS_NEAR_LIMIT_10CM);	break;
				case 2: 	Focus_set_near_limit(FOCUS_NEAR_LIMIT_50CM);	break;
				case 3: 	Focus_set_near_limit(FOCUS_NEAR_LIMIT_1M);		break;
				case 4: 	Focus_set_near_limit(FOCUS_NEAR_LIMIT_2M);		break;
				case 5:
				default:	Focus_set_near_limit(FOCUS_NEAR_LIMIT_INF); 	break;
			}
*/
		#endif
		break;
		/*Swap Event*/
		case IDX_ZOOM_MODE: 		//106
			if(g_OsdData.FLD.DZOOM_MODE == 0)
				OSD_DZModeItem[1].pdep = 0; //DZoom Combine
			else if(g_OsdData.FLD.DZOOM_MODE == 1)
				OSD_DZModeItem[1].pdep = (OSD_MAP *)OSD_DZoomMap;
			IF_OsdRefresh();
		break;

		//Dzoom Lv 표시
		case IDX_DZOOM_MODE:	//107
			if(param->key == OSD_CKEYDOWN && g_OsdData.FLD.ZOOM_MODE == 1 && g_OsdData.FLD.DZOOM_MODE == 1)
			{
				dzoom_osd_flg = 2;
			}
		break;
		case IDX_LENS_REFRESH_MODE: //110
			if(param->key == OSD_CKEYDOWN)
			{
				if(g_OsdData.FLD.LENS_REFRESH_MODE == 2)
				{
				#ifndef COMMAND_CHECK
					IF_Trace(16,17,"Push Lens init Md	 ");
				#endif
				#ifndef WIN32
					Lens_start_end_sensing();
#endif
				}
			}
		break;

		case IDX_DZOOM_MAG:		//114
				dzoom_osd_flg = 2;
			if(param->key == -1)//by protocol
			{
				g_OsdData.FLD.DZOOM_MAG = Interp1D_RoundOff(g_UserEepData.FLD.EXTEND_DZOOM_LV,0x0,0xEB,0,110);
				#ifndef	WIN32
					IF_OsdItemRefresh(0);
					IF_Trace(43,4,"X%d.%d  ",Dzoom_get_magnitude() / 10,Dzoom_get_magnitude() % 10);
				#endif
			}
			else
			{
				g_UserEepData.FLD.EXTEND_DZOOM_LV = Interp1D_RoundOff(g_OsdData.FLD.DZOOM_MAG,0,110,0x0,0xEB);
			}
#ifndef WIN32
			Dzoom_set_separate_position(g_UserEepData.FLD.EXTEND_DZOOM_LV);
#endif
		break;

		case IDX_WB_MODE:		//301
			if(param->key == OSD_CKEYDOWN && (g_OsdData.FLD.WB_MODE == 4 || g_OsdData.FLD.WB_MODE == 5))
			{
				wb_manual_osd_flg = 2;
			}
		break;
		case IDX_MD_ON: 		//801
			if(param->key == OSD_CKEYDOWN && g_OsdData.FLD.MD_ON == 1)
			{
				Osd_md_flg = 1;
			}
		break;
		case IDX_MASK_ON:
			if(param->key == OSD_CKEYDOWN && g_OsdData.FLD.MASK_ON == 1)
			{
				Osd_pri_flg = 1;
			}
		break;
	}
}

/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/*********************************************************************************************************//**
* @param[in] evt : R/W를 결정한다.
* @param[in] idx : 바꿀 UIDX_에 할당된 EEP값
* @param[in] val : 적용할 값
* @retval
*	Result Read할 때, 값을 리턴한다.
* @brief
*   UIDX_값에 할당 된 EEP값을 R/W
*************************************************************************************************************/
int32 User_Update(IFEVT evt, EEP_IDX idx, int32 val)
{
	int32 ret = -1;
	switch(idx)
	{
		case UIDX_MD_SENSITIVITY:		ret = VAL_TUNE(g_UserEepData.FLD.MD_SENSITIVITY);	break;
		case UIDX_OSD_DEBUG_STATE:		ret = VAL_TUNE(g_UserEepData.FLD.OSD_DEBUG_STATE);	break;
		case UIDX_IRIS_JUMP:			ret = VAL_TUNE(g_UserEepData.FLD.IRIS_JUMP);		break;
		case UIDX_AUTO_MIN_SHUTTER:		ret = VAL_TUNE(g_UserEepData.FLD.AUTO_MIN_SHUTTER);	break;
		case UIDX_AUTO_MAX_SHUTTER:		ret = VAL_TUNE(g_UserEepData.FLD.AUTO_MAX_SHUTTER);	break;
		case UIDX_SPOT_AE :				ret=VAL_TUNE(g_UserEepData.FLD.SPOT_AE);			break;
		case UIDX_AE_RESPONS :          ret=VAL_TUNE(g_UserEepData.FLD.AE_RESPONSE);         break;
		case UIDX_SPOT_AE_POS_X :       ret=VAL_TUNE(g_UserEepData.FLD.SPOT_AE_POS_X);      break;
		case UIDX_SPOT_AE_POS_Y :       ret=VAL_TUNE(g_UserEepData.FLD.SPOT_AE_POS_Y);      break;
		case UIDX_AGING_STATE:			ret = VAL_TUNE(g_UserEepData.FLD.AGING_STATE );		break;
		case UIDX_AGING_MODE:			ret = VAL_TUNE(g_UserEepData.FLD.AGING_MODE );		break;
		case UIDX_DBDR_MODE:			ret = VAL_TUNE(g_UserEepData.FLD.DBDR_MODE );		break;
		case UIDX_WINDOW_START_X:		ret = VAL_TUNE(g_UserEepData.FLD.WINDOW_START_X );	break;
		case UIDX_WINDOW_WIDE:			ret = VAL_TUNE(g_UserEepData.FLD.WINDOW_WIDE );		break;
		case UIDX_WINDOW_START_Y:		ret = VAL_TUNE(g_UserEepData.FLD.WINDOW_START_Y );	break;
		case UIDX_WINDOW_HEIGHT:		ret = VAL_TUNE(g_UserEepData.FLD.WINDOW_HEIGHT );	break;
		case UIDX_B_GAIN_P:				ret = VAL_TUNE(g_UserEepData.FLD.B_GAIN_P );		break;
		case UIDX_B_GAIN_N:				ret = VAL_TUNE(g_UserEepData.FLD.B_GAIN_N );		break;
		case UIDX_R_GAIN_P:				ret = VAL_TUNE(g_UserEepData.FLD.R_GAIN_P );		break;
		case UIDX_R_GAIN_N:				ret = VAL_TUNE(g_UserEepData.FLD.R_GAIN_N );		break;
		case UIDX_B_HUE_P:				ret = VAL_TUNE(g_UserEepData.FLD.B_HUE_P );			break;
		case UIDX_B_HUE_N:				ret = VAL_TUNE(g_UserEepData.FLD.B_HUE_N );			break;
		case UIDX_R_HUE_P :				ret = VAL_TUNE(g_UserEepData.FLD.R_HUE_P );			break;
		case UIDX_R_HUE_N :				ret = VAL_TUNE(g_UserEepData.FLD.R_HUE_N );			break;
		case UIDX_H_SIZE :				ret = VAL_TUNE(g_UserEepData.FLD.H_SIZE );			break;
		case UIDX_H_START :				ret = VAL_TUNE(g_UserEepData.FLD.H_START );			break;
		case UIDX_H_END	:				ret = VAL_TUNE(g_UserEepData.FLD.H_END );			break;
		case UIDX_V_TOTAL_SIZE :		ret = VAL_TUNE(g_UserEepData.FLD.V_TOTAL_SIZE );	break;
		case UIDX_V_ACT_START :			ret = VAL_TUNE(g_UserEepData.FLD.V_ACT_START );		break;
		case UIDX_V_ACT_END	:			ret = VAL_TUNE(g_UserEepData.FLD.V_ACT_END );		break;
		case UIDX_V_ACT_START_BOT :		ret = VAL_TUNE(g_UserEepData.FLD.V_ACT_START_BOT );	break;
		case UIDX_V_ACT_END_BOT	:		ret = VAL_TUNE(g_UserEepData.FLD.V_ACT_END_BOT );	break;
		case UIDX_COLOR_BAR :			ret = VAL_TUNE(g_UserEepData.FLD.COLOR_BAR );		break;
		case UIDX_MAIN_IN :				ret = VAL_TUNE(g_UserEepData.FLD.MAIN_IN );			break;
		case UIDX_MAIN_OUT :			ret = VAL_TUNE(g_UserEepData.FLD.MAIN_OUT );		break;
		case UIDX_AUX_OUT :				ret = VAL_TUNE(g_UserEepData.FLD.AUX_OUT );			break;
		case UIDX_VIDEO_ENCODER :		ret = VAL_TUNE(g_UserEepData.FLD.VIDEO_ENCODER);	break;
		case UIDX_CVBS_MODE	:			ret = VAL_TUNE(g_UserEepData.FLD.CVBS_MODE );		break;
		case UIDX_CBCR_SWAP	:			ret = VAL_TUNE(g_UserEepData.FLD.CBCR_SWAP );		break;
		case UIDX_FIRMWARE_UPDATEMODE_1 : ret = VAL_TUNE(g_UserEepData.FLD.FIRMWARE_UPDATEMODE_1 );	break;
		case UIDX_FIRMWARE_UPDATEMODE_2 : ret = VAL_TUNE(g_UserEepData.FLD.FIRMWARE_UPDATEMODE_2 );	break;
		case UIDX_FIRMWARE_UPDATEMODE_3 : ret = VAL_TUNE(g_UserEepData.FLD.FIRMWARE_UPDATEMODE_3 );	break;
		case UIDX_TEMP_1:				ret = VAL_TUNE(g_UserEepData.FLD.TEMP_1 );			break;
		case UIDX_PRTCL_TYPE:			ret = VAL_TUNE(g_UserEepData.FLD.PRTCL_TYPE );		break;
		case UIDX_PRTCL_BAUD:			ret = VAL_TUNE(g_UserEepData.FLD.PRTCL_BAUD );		break;
		case UIDX_CAM_RES:				ret = VAL_TUNE(g_UserEepData.FLD.CAM_RES	);		break;
		case UIDX_MD_DISP:				ret = VAL_TUNE(g_UserEepData.FLD.MD_DISP);			break;
		case UIDX_WB_PUSH:				ret = VAL_TUNE(g_UserEepData.FLD.WB_PUSH);			break;
		case UIDX_AE_ACE:				ret = VAL_TUNE(g_UserEepData.FLD.AE_ACE);			break;	//**03 실재 값이 R/W되는 공간.
		case UIDX_WB_COLOR_TEMP:		ret = VAL_TUNE(g_UserEepData.FLD.COLOR_TEMP);		break;
		case UIDX_WB_MODE:				ret = VAL_TUNE(g_UserEepData.FLD.WB_MODE);			break;	//**03 실재 값이 R/W되는 공간.
		case UIDX_PRI_ADJ_X:			ret = VAL_TUNE(g_UserEepData.FLD.PRI_ADJ_X);		break;
		case UIDX_PRI_ADJ_Y:			ret = VAL_TUNE(g_UserEepData.FLD.PRI_ADJ_Y);		break;
		case UIDX_VISCA_OSD_MENU:		ret = VAL_TUNE(g_UserEepData.FLD.VISCA_OSD_MENU);	break;
#ifndef WIN32
		case UIDX_GAMMA1 :				ret = VAL_TUNE(g_UserEepData.FLD.GAMMA1);	break;
		case UIDX_GAMMA2 :				ret = VAL_TUNE(g_UserEepData.FLD.GAMMA2);	break;
		case UIDX_LAST_YGAIN :			ret = VAL_TUNE(g_UserEepData.FLD.LAST_YGAIN);	break;
		case UIDX_LAST_CGAIN :			ret = VAL_TUNE(g_UserEepData.FLD.LAST_CGAIN);	break;

		case PRM_HALL_MAX: 				ret = VAL_TUNE(HallParam.FLD.HallMax);				break;
		case PRM_HALL_MIN: 				ret = VAL_TUNE(HallParam.FLD.HallMin);				break;
		case PRM_IRIS_LV: 				ret = VAL_TUNE(HallParam.FLD.IrisLvl);				break;

		case UIDX_IRIS_ADJ_ON :			ret = VAL_TUNE(AeParam.IrisAdjOn);					break;
		case UIDX_IRIS_ADJ_AE_DISBLE :	ret = VAL_TUNE(AeParam.AlgoDisable);				break;
		case UIDX_IRIS_ADJ_SUM :		ret = ExMw_GetExposureSum();						break;
		case UIDX_IRIS_ADJ_SUM2 :		ret = ExMw_GetExposure();							break;
		case UIDX_IRIS_ADJ_IRIS_VAL	:	ret = VAL_TUNE(AeParam.IrisAdjIrisVal);				break;
		case UIDX_IRIS_ADJ_SHUT_VAL	:	ret = VAL_TUNE(AeParam.IrisAdjShutVal);				break;
		case UIDX_IRIS_ADJ_GAIN_VAL	:	ret = VAL_TUNE(AeParam.IrisAdjGainVal);				break;
		case UIDX_IRIS_ADJ_RESET :		ret = VAL_TUNE(AeParam.IrisAdjSW1);					break;
		case UIDX_IRIS_ADJ_SW2 :		ret = VAL_TUNE(AeParam.IrisAdjSW2);					break;
		case UIDX_IRIS_ADJ_DSS_VAL	:	ret = VAL_TUNE(AeParam.IrisAdjDssVal);				break;
#endif
		case UIDX_EEP_ADDRESS :			ret = VAL_TUNE(g_UserEepData.FLD.EEP_ADDR);			break;
		case UIDX_EEP_TEST_START :		ret = VAL_TUNE(g_UserEepData.FLD.EEP_TEST);			break;
		case UIDX_3DPRI_ZOOM:			ret = VAL_TUNE(g_UserEepData.FLD._3DPRI_ZOOM);		break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

/*********************************************************************************************************//**
* @param[in] aiXCur : 입력 값
* @param[in] aiXPos1 : 입력 값의 MIN
* @param[in] aiXPos2 : 입력 값의 MAX
* @param[in] aiYPos1 : 출력 값의 MIN
* @param[in] aiYPos2 : 출력 값의 MAX
* @retval
*	Result 출력값
* @brief
*   나눌값의 반을 더한뒤에 나눠줘서(0.5를 더해서) 반올림되는 인터폴레이션 한다.
*************************************************************************************************************/
int Interp1D_RoundOff(int aiXCur,int aiXPos1,int aiXPos2,int aiYPos1,int aiYPos2)
{
	int	iResult=0;

	if (aiXPos1==aiXPos2)			return 0;										// Divide by 0 " error "
	else if (aiYPos1==aiYPos2)		return aiYPos1;									// Position equal
	else if (aiYPos1<aiYPos2)
	{
		iResult  = (aiYPos2-aiYPos1) * (aiXCur-aiXPos1);
		iResult += (aiXPos2-aiXPos1)>>1;
		iResult /= (aiXPos2-aiXPos1) ;
		iResult +=  aiYPos1;
	}
	else if (aiYPos1>aiYPos2)
	{
		iResult  = (aiYPos1-aiYPos2) * (aiXPos2 - aiXCur);
		iResult += (aiXPos2-aiXPos1)>>1;
		iResult /= (aiXPos2-aiXPos1);
		iResult += aiYPos2;
	}

	return iResult;
}

/*********************************************************************************************************//**
* @param[in] val	: MD Detect의 결과를 받아온다.
* @retval none
* @brief
*	MD Detect의 결과를 받아온다.
*************************************************************************************************************/
void IFU_OSD_MD_OUT(uint16 Val)
{
	motion_detect = (uint08)Val;
}

/*********************************************************************************************************//**
* @param[in] bootflg : 1 - 부팅중, 0 - 부팅종료
* @retval none
* @brief
*	부팅시 OSD를 띄워준다.
*	g_CamData.FLD.LOGO_CH1 ~ g_CamData.FLD.LOGO_CH32
*************************************************************************************************************/
void IFU_BOOTING_MSG(int08 bootflg){
#ifndef WIN32
	uint08 i;
	if(bootflg)
	{
		SetFontSize(FONT_SIZE_BOOT_H,FONT_SIZE_BOOT_V);
		SetFontOffset(FONT_OFFSET_BOOT_H,FONT_OFFSET_BOOT_V);

		for(i=0;i<10;i++)
		{
			SetFont(10+i,2,g_CamData.Data[0x40+i]);
		}
		for(i=0;i<10;i++)
		{
			SetFont(45+i,2,g_CamData.Data[0x4A+i]);
		}
		for(i=0;i<10;i++)
		{
			SetFont(10+i,3,g_CamData.Data[0x54+i]);
		}
	}
	else
	{
		switch(g_OsdData.FLD.VOUT_FORMAT)
		{
			case 0:	//1080 30p
			case 1:	//1080 25p
			case 4:
			case 5:
				SetFontSize(FONT_SIZE_NORMAL_H,FONT_SIZE_NORMAL_V);
				SetFontOffset(FONT_OFFSET_NORMAL_H,FONT_OFFSET_NORMAL_V);
				break;
			#if (USE_MDIN325A == 0)
			case 3:	//720 50p
			case 2:	//720 60p
			default:
				SetFontSize(FONT_SIZE_SMALL_H,FONT_SIZE_SMALL_V);
				SetFontOffset(FONT_OFFSET_SMALL_H,FONT_OFFSET_SMALL_V);
				break;
			#else
			default:
				SetFontSize(FONT_SIZE_NORMAL_H,FONT_SIZE_NORMAL_V);
				SetFontOffset(FONT_OFFSET_NORMAL_H,FONT_OFFSET_NORMAL_V);
				break;
			#endif
		}
		for(i=0;i<10;i++)
		{
			SetFont(10+i,2,' ');
		}
		for(i=0;i<10;i++)
		{
			SetFont(45+i,2,' ');
		}
		for(i=0;i<10;i++)
		{
			SetFont(10+i,3,' ');
		}
	}
#endif
}

/*************************************************************************************************************
* GLOBAL FUNCTION - User Code 작성
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] key : Ket값
* @retval none
* @brief
* === 7. LOCAL FUNCTION	: KEY CONTROL	===
*	Que에 Ket값을 채운다.
*************************************************************************************************************/
void IFU_Osd_KeyInput(uint32 key)
{
	uint08 tmp = (Key_Que.head -1)&0x1f;
#ifndef WIN32
	if(Key_Que.code[tmp] == key)
	{
		if(key != OSD_CKEYDOWN && key != IFU_OSD_KEY1)
			Key_Que.code[Key_Que.head] = OSD_KEYLONG;
		else
		{
			Key_Que.code[Key_Que.head] = key;
			Key_Que.head++;
			Key_Que.head &= 0x1f;
		}
	}
	else
#endif
	{
		Key_Que.code[Key_Que.head] = key;
		Key_Que.head++;
		Key_Que.head &= 0x1f;
	}
}

/*********************************************************************************************************//**
* @retval
*	return	key 값
* @brief
* === 7. LOCAL FUNCTION	: KEY CONTROL	===
*	Que에 채워진 1개의 key값을 빼온다.
*************************************************************************************************************/
static uint32 IFU_Osd_KeyOut()
{
	uint32 val;
	uint08 tmp = (Key_Que.tail -1)&0x1f;
	gOsd_key_flg = 0;
	if(Key_Que.code[Key_Que.tail] == OSD_KEYLONG) //long key입력
	{
		val = Key_Que.code[tmp];
		gOsd_key_flg = 1;
	}
	else if(Key_Que.tail == Key_Que.head)
	{
		val = OSD_KEYNULL;
		gOsd_key_flg = 0;
	}
	else
	{
		val = Key_Que.code[Key_Que.tail];
		Key_Que.tail++;
		Key_Que.tail &= 0x1f;
		gOsd_key_flg = 1;
	}
	return val;
}

/*********************************************************************************************************//**
* @param[in] Camres : 해상도
* @retval none
* @brief
*	해상도를 변경한다.
*************************************************************************************************************/
static void IFU_Camres_Chg(uint32 Camres)
{
	if(Camres == 0)//1080/30
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/30p      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_30p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x06;
	}
	else if(Camres == 1)//1080/25
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/25p      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_25p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x08;
	}
	else if(Camres == 2)//720/60
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 720/60p       ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_720_60p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x09;
	}
	else if(Camres == 3)//720/50
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 720/50p       ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_720_50p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x0C;
	}
	else if(Camres == 4)//1080/60i
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/60i      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_60i);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x01;
	}
	else if(Camres == 5)//1080/50i
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/50i      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_50i);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x04;
	}
	else if(Camres == 6)//1080/60p
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/60p      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_60p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x13;
	}
	else if(Camres == 7)//1080/50p
	{
	#ifndef COMMAND_CHECK
		IF_Trace(16,17,"Set : 1080/50p      ");
	#endif
	#ifndef WIN32
		Param_set_output_format(CAM_OUTPUT_1080_50p);
	#endif
		g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE = 0x14;
	}
}

/*********************************************************************************************************//**
* @retval
*	return 1 - On / 0 - Off
* @brief
*	Osd상에 Privacy Menu가 떠있는지를 확인한다.
*************************************************************************************************************/
uint08 IFU_Osd_PriOn()
{
	return Osd_pri_flg;
}
/*********************************************************************************************************//**
* @retval
*	return 1 - On / 0 - Off
* @brief
*	Osd상에 MD Menu가 떠있는지를 확인한다.
*************************************************************************************************************/
uint08 IFU_Osd_MDOn()
{
	return Osd_md_flg;
}
/*********************************************************************************************************//**
* @param[in] cursor
* @retval none
* @brief
*	OSD메뉴에서 해당 라인의 ITEM을 다시 그린다.
*************************************************************************************************************/
void IFU_Osd_ItemRefresh(uint08 cursor)
{
	IF_OsdItemRefresh(cursor);
}

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
* === 9. GLOBAL FUNCTION : MAIN TASK	  ===
*************************************************************************************************************/
void IFU_Osd_TASK()
{
	static uint08 f_osd_state;
	gOsd_key_code = IFU_Osd_KeyOut();
	/***************************************************************/
	//  Osd Priority
	//  0. Osd Menu  : Normal Menu,Hidden Menu
	//	1. Trace Osd : Debug Osd
	//	2. Tilte	 : VISCA Tilt Display
	//  3. Display   : VISCA Display
	//  4. Func Osd  : CNB Func Osd
	/***************************************************************/
	//  0. Osd Menu  : Hidden Menu
	if(IF_IsOsdMode() == OSD_HIDE)
	{
		f_osd_state = 5;
		switch(osd_hide_mode)
		{
			case OSD_HIDE_HALL_ADJ :
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Hall Adj end");
				}
				else
				{
					static uint08 i;
					IF_Trace(16,18,"Tr %d",i++);
				}
			break;
			case OSD_HIDE_LENS_ADJ :
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Lens Adj end");
				}
				else
				{
					static uint08 i;
					IF_Trace(16,18,"Tr %d",i++);
				}
			break;
			case OSD_HIDE_DEFECT_ADJ :
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Defect Adj end");
				}
				else
				{
					static uint08 i;
					IF_Trace(25,18,"Tr %d",i++);
				}
			break;
			case OSD_HIDE_SHADE_ADJ :
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Shade Adj end");
				}
				else
				{
					static uint08 i;
					IF_Trace(16,18,"Tr %d",i++);
				}
			break;
			case OSD_HIDE_DEFECTLOAD :
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Defect Load end");
				}
				else
				{
					static uint08 i;
					IF_Trace(16,18,"Tr %d",i++);
				}
			break;
			case OSD_HIDE_SHADELOAD:
				if(gOsd_key_code == OSD_CKEYDOWN)
				{
					IF_OsdShow();
					IF_Trace(16,17,"Osd Show by Shade Load end");
				}
				else
				{
					static uint08 i;
					IF_Trace(16,18,"Tr %d",i++);
				}
			break;

			default:
			break;
		}
		gOsd_key_code = 0;
		gOsd_key_flg = 0;
	}
	else if(IF_IsOsdOn() == OSD_STATEOFF)
	{
		//	1. Trace Osd : Debug Osd
		if(g_UserEepData.FLD.OSD_DEBUG_STATE != 0)
		{
			f_osd_state = 4;
			switch(g_UserEepData.FLD.OSD_DEBUG_STATE)
			{
				case OSD_TRACE_COMM :
					IF_Trace(1,1,"[TRACE OSD_TRACE_COMM]     ");
					//PRIV_Dbg_Osd();
					//Prtcl_dbg();
					break;
#ifndef WIN32
				//case OSD_TRACE_COLORSTAT:		IF_Trace(1,1,"[TRACE OSD_TRACE_COLORSTAT] "); 	TRACE_Awb(); break;
				//case OSD_TRACE_MOTION : 		IF_Trace(1,1,"[TRACE OSD_TRACE_MOTION]    "); 	break;
				//case OSD_TRACE_DNR :			IF_Trace(1,1,"[TRACE OSD_TRACE_DNR]	      ");	break;
				//case OSD_TRACE_WDR :			IF_Trace(1,1,"[TRACE OSD_TRACE_WDR]       ");	break;
				//case OSD_TRACE_PGAGAIN :		IF_Trace(1,1,"[TRACE OSD_TRACE_PGAGAIN]   ");	break;
				case OSD_TRACE_AESTAT : 		TRACE_Ae();break;
				//case OSD_TRACE_FOCUSSTAT :		IF_Trace(1,1,"[TRACE OSD_TRACE_FOCUSSTAT] ");	break;
				//case OSD_TRACE_HALLADJUST : 	IF_Trace(1,1,"[TRACE OSD_TRACE_HALLADJUST]");	break;
				case OSD_TRACE_FOCUS1 : 		IF_Trace(1,1,"[TRACE OSD_TRACE_FOCUS1]    "); 	AF_trace_debug_OSD(0);break;
				//case OSD_TRACE_FOCUS2 : 		IF_Trace(1,1,"[TRACE OSD_TRACE_FOCUS2]    "); 	AF_trace_debug_OSD(1);break;
				//case OSD_TRACE_ZOOMTRACK :		IF_Trace(1,1,"[TRACE OSD_TRACE_ZOOMTRACK] ");	break;
				//case OSD_TRACE_DZOOM :			IF_Trace(1,1,"[TRACE OSD_TRACE_DZOOM]     ");		break;
				//case OSD_TRACE_KEYCONTROL : 	IF_Trace(1,1,"[TRACE OSD_TRACE_KEYCONTROL]"); 	break;
				//case OSD_TRACE_PARE3 :			IF_Trace(1,1,"[TRACE OSD_TRACE_PARE3]     ");		break;
#endif
			}
		}
		else
		{
			Init_Title_Print();
			//	2. Tilte	 : VISCA Tilt Display
			if(display_flg[DISPLAY_ACT])
			{
				if(f_osd_state != 1)
				{
					User_Clear_Osd();
				}

				if(title_change)
				{
					User_Title_Print();
					title_change = 0;
					f_osd_state = 1;
				}
			}
			//  3. Display   : VISCA Display
			else if(g_ViscaData.FLD.DISP_ON)
			{
				if(f_osd_state != 2)
				{
					User_Clear_Osd();
					Init_Display_Print();
				}
				User_Display_Print();
				f_osd_state = 2;
			}
			//  4. Func Osd  : CNB Func Osd
			else
			{
				if(f_osd_state != 0)
				{
					User_Clear_Osd();
				}
				f_osd_state = 0;
				Trace_Func_OSD(gOsd_key_code);
			}
		}
	}
	/***************************************************************/
	//	Hidden Osd : Privacy Mask Adjust
	/***************************************************************/
	if(gOsd_key_flg) // Key가 눌림
	{
		if((gOsd_key_code == OSD_CKEYDOWN) && (f_osd_state != 6))
		{
			f_osd_state = 6;
			User_Clear_Osd();
		}
		IF_Task(gOsd_key_code);

		if(_3d_adj_zm_flg == 1)
		{
			//IF_Trace(16,18,"Tr %d",gOsd_key_code);
			if(gOsd_key_code == OSD_KEYNULL)
			{
			#ifndef WIN32
				ZT_set_tw_mode(ZOOM_TRK_DRV_STOP);
			#endif
				_3d_adj_zm_flg = 0;
			}
			else
			{
			#ifndef WIN32
				ZT_set_tw_mode(ZOOM_TRK_DRV_WIDE);
			#endif
			}
		}
		else if(_3d_adj_zm_flg == 2)
		{
			//IF_Trace(16,18,"Tr %d",gOsd_key_code);
		#ifndef	WIN32
			ZT_set_tw_mode(ZOOM_TRK_DRV_TELE);
		#endif
		}

		gOsd_key_code = 0;
		gOsd_key_flg = 0;
	}
	else
	{
		if(_3d_adj_zm_flg)
		{
			if(gOsd_key_code == OSD_KEYNULL)
			{
			#ifndef	WIN32
				ZT_set_tw_mode(ZOOM_TRK_DRV_STOP);
			#endif
				_3d_adj_zm_flg = 0;
			}
		}
	}

	/***************************************************************/
	//	exception handling
	//	1. Osd Menu의 Item은 2가지로만 Display할 수 있다.
	//	 a. 프로그래시브와 정수.
	//	 b. 지정된 문자열
	//	따라서 음수,소수점등을 표현 하려면 별도로 처리해야 한다.
	/***************************************************************/
	if(dzoom_osd_flg)
	{
	#ifndef	WIN32
		IF_Trace(43,4,"X%d.%d  ",Dzoom_get_magnitude() / 10,Dzoom_get_magnitude() % 10);
	#endif
		dzoom_osd_flg--;
	}
	else if(wb_manual_osd_flg)
	{
		const uint16 CTemp[41] = {14900,	15300,	12600,	10900,	9580,
								  8460,		7450,	6700,	6230,	6120,
								  5610,		5260,	4880,	4660,	4400,
								  4130,		3910,	3710,	3550,	3370,
								  3200,		3090,	2930,	2850,	2750,
								  2680,		2590,	2520,	2480,	2420,
								  2340,		2290,	2290,	2230,	2170,
								  2120,		2100,	2070,	2020,	1980,
								  1930
								  };
		IF_Trace(43,7,"%dK   ",CTemp[40-g_UserEepData.FLD.COLOR_TEMP]);
		wb_manual_osd_flg--;
	}
	else if(Osd_pri_adj_flg)
	{
		if(g_UserEepData.FLD.PRI_ADJ_X < 100)
		{
			if(g_UserEepData.FLD.PRI_ADJ_X > 0)
				IF_Trace(43,4," -%d",  ~((int08)g_CamData.FLD.MADJ_3D_PAN_NT)+1);
			else if(g_UserEepData.FLD.PRI_ADJ_X > 90)
				IF_Trace(43,4,"  -%d", ~((int08)g_CamData.FLD.MADJ_3D_PAN_NT)+1);
			else
				IF_Trace(43,4,"-%d", ~((int08)g_CamData.FLD.MADJ_3D_PAN_NT)+1);
		}
		else
		{
			if(g_UserEepData.FLD.PRI_ADJ_X > 109)
				IF_Trace(43,4," %d", g_CamData.FLD.MADJ_3D_PAN_NT);
			else if(g_UserEepData.FLD.PRI_ADJ_X > 199)
				IF_Trace(43,4,"%d", g_CamData.FLD.MADJ_3D_PAN_NT);
			else
				IF_Trace(43,4,"  %d", g_CamData.FLD.MADJ_3D_PAN_NT);
		}

		if(g_UserEepData.FLD.PRI_ADJ_Y < 100)
		{
			if(g_UserEepData.FLD.PRI_ADJ_Y > 0)
				IF_Trace(43,5," -%d",  ~((int08)g_CamData.FLD.MADJ_3D_TILT_NT)+1);
			else if(g_UserEepData.FLD.PRI_ADJ_Y > 90)
				IF_Trace(43,5,"  -%d", ~((int08)g_CamData.FLD.MADJ_3D_TILT_NT)+1);
			else
				IF_Trace(43,5,"-%d", ~((int08)g_CamData.FLD.MADJ_3D_TILT_NT)+1);
		}
		else
		{
			if(g_UserEepData.FLD.PRI_ADJ_Y > 109)
				IF_Trace(43,5," %d", g_CamData.FLD.MADJ_3D_TILT_NT);
			else if(g_UserEepData.FLD.PRI_ADJ_Y > 199)
				IF_Trace(43,5,"%d", g_CamData.FLD.MADJ_3D_TILT_NT);
			else
				IF_Trace(43,5,"  %d", g_CamData.FLD.MADJ_3D_TILT_NT);
		}
		Osd_pri_adj_flg = 0;
	}
}

/****************************************************************************************************************************************************************
* OSD 모듈 종료 - OSD 코드 영역
****************************************************************************************************************************************************************/

/*************************************************************************************************************
* OSD 초기화 - OSD 코드 영역
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
* === 8. GLOBAL FUNCTION : INITIAL		  ===
*************************************************************************************************************/
void IFU_OSD_User_Init()
{
	/***************************************************************/
	//If_User의 내부변수 초기화
	/***************************************************************/
	Key_Que.head = 0;
	Key_Que.tail = 0;

	g_UserEepData.FLD.PRI_ADJ_X = g_CamData.FLD.MADJ_3D_PAN_NT + 100;
	g_UserEepData.FLD.PRI_ADJ_Y = g_CamData.FLD.MADJ_3D_TILT_NT + 100;

	dzoom_osd_flg = 0;	 //Dzoom On에 들어갈때, Dzoom배율이 바뀔때
	wb_manual_osd_flg = 0;
	_3d_adj_zm_flg = 0;
	Osd_pri_adj_flg = 0;
	osd_off_flg = 1;

	Osd_md_flg = 0;
	Osd_pri_flg = 0;
	osd_defect_adj_flg = 0; //defect adj에 집입함을 알리는 변수
	osd_tune_exp_flg = 0;
	motion_detect = 0;
	title_change = 1;	//타이틀 체인지

	Reset_r_gain = g_ViscaData.FLD.R_GAIN;
	Reset_b_gain = g_ViscaData.FLD.B_GAIN;
	Reset_bright = g_ViscaData.FLD.BRIGHT_STEP;
	pass_cnt = 0;

#ifndef WIN32
	DebugPrintf("IFU_OSD_User_Init...\n\r");
	/***************************************************************/
	//If_mw 초기화
	/***************************************************************/
	IF_Initial();

	/***************************************************************/
	//If_mw OSD initialize
	/***************************************************************/
	IF_OsdWindowSize(58,22);							// OSD : SIZE
	IF_OsdPrintCallbackRegister(SetFont);				// OSD : OSD에 문자를 띄우는 함수 등록
	IF_OsdMapRegister(OSD_gMap,OSD_gHiddenMap);			// OSD : OSD 맵 등록 일반, 히든

	/***************************************************************/
	//If_mw VISCA initialize
	/***************************************************************/
	InitUartDriverComm(9600,IF_PTC_SetRxQue,IF_PTC_GetTxQue); 	// VISCA Rx/Tx Que 함수 등록
#endif
	/***************************************************************/
	//If_mw EEP initialize
	/***************************************************************/
	IF_EventCallbackRegister(IFU_Event_Callback);		// 이벤트 발생시 Callback 되는 함수
	IF_UEepUpdateCallbackRegister(User_Update);			// User_Eep Data Update 함수 등록

	IFU_After_Load();									//if_user_mw에서 EEP READ가 끝난 후 Call 해줄 함수
	g_UserEepData.FLD.INITIAL_CAM_RES = g_ViscaData.FLD.MONITORING_MODE;

}

/****************************************************************************************************************************************************************
* Event 모듈 시작
****************************************************************************************************************************************************************/

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
* === 10. GLOBAL FUNCTION : EVENT CALLBACK ===
*************************************************************************************************************/
IFER IFU_Event_Callback(IFEVT evt, IFEVT_PARAM *param)
{
	const uint16 pass[4] = {OSD_RKEYDOWN,OSD_RKEYDOWN,OSD_RKEYDOWN,OSD_RKEYDOWN};
	IFER err = IF_ERNO;
	/***************************************************************/
	// initialize Event Processing
	/***************************************************************/
	if(evt == IFEVT_INITIAL)
	{
		User_EepInitial(param->eepidx);
		if(param->eepidx == IDX_ZOOM_MODE)
		{
			if(g_OsdData.FLD.DZOOM_MODE == 0)		OSD_DZModeItem[1].pdep = 0; //DZoom Combine
			else if(g_OsdData.FLD.DZOOM_MODE == 1)	OSD_DZModeItem[1].pdep = (OSD_MAP *)OSD_DZoomMap;
			IF_OsdRefresh();
		}
	}
	/***************************************************************/
	// OSD Event Processing
	/***************************************************************/
	//OSD값이 변경되었다. 이벤트가 일어났다.
	else if(evt == IFEVT_OSD)
	{
		//HIDDEN 메뉴 진입조건
		if(param->eepidx == UIDX_PASS)
		{
			if(pass_cnt > 4)
			{
				pass_cnt = 0;
			}
			if(param->key == OSD_CKEYDOWN && pass_cnt == 4)
			{
				IF_OsdHiddenMenuOn();
				param->key = 0;
				pass_cnt = 0;
			}
			else if(pass[pass_cnt] == param->key)
			{
				pass_cnt++;
			}
			else
			{
				if(param->key == OSD_KEYNULL);
				else if(param->key == -1);
				else
					pass_cnt = 0;
			}
		}
		//MASK REDRAW FLG ON
		else if((param->eepidx >IDX_PRI_STT && param->eepidx <IDX_PRI_END ) || (param->eepidx >= IDX_MASK_ON&& param->eepidx <= IDX_MASK8_ZOOM))
		{
#ifndef WIN32
			PRV_Redraw();
#endif
		}
		//USER EVENT : Define if_user_mw.h
		else if(param->eepidx >= (IDX_USER + 1000)	)
		{
			IFU_UEvent_Call(evt,param);		//6000~의 User가 생성한 이벤트를 처리한다.(Lens Adj...)
		}
		//USER DATA CHG
		else if(param->eepidx >= (IDX_USER))
		{
			IFU_UEep_Call(evt,param);
		}
		else
		{
			//EEP DATA CHG
			IFU_Eep_Call(evt,param);			//Eep값 선택 변경
			//EVENT : Define if_mw.h
			IFU_Event_Call(evt,param);
		}
	}
	/***************************************************************/
	// VISCA CMD Event Processing
	/***************************************************************/
	//VISCA값이 변경되었다. 이벤트가 일어났다.
	else if(evt == IFEVT_VISCA_CMD)
	{
		err = IF_ERNOPROC;
		//값이 변하면 DISP의 내용도 변해야 한다.
		if(g_ViscaData.FLD.DISP_ON)
		{
			Visca_Display_Check(param);
		}
		//MOTION REDRAW FLG ON
		if(param->eepidx > VDX_MD_STT && param->eepidx < VDX_MD_END)
		{
#ifndef WIN32
			MD_osdRefresh();
#endif
		}
		//MASK REDRAW FLG ON
		else if((param->eepidx > VDX_MASK_STT && param->eepidx < VDX_MASK_END) || param->eepidx == VDX_CAM_PAN || param->eepidx == VDX_CAM_TILT )
		{
#ifndef WIN32
			PRV_Redraw();
#endif
		}
		//TITLE REDRAW FLG ON
		else if((param->eepidx > VDX_TITLE_STT && param->eepidx < VDX_TITLE_END))
		{
			title_change = 1;
		}
		else if(param->eepidx >= 4600)
		{	//VISCA CMD ETC
			err = Visca_Evt_Proc_Move(param);
		}
		else
		{	//VISCA CMD EEP DATA
			err = Visca_Evt_Proc_Cmd(param);
		}
	}
	/***************************************************************/
	// VISCA INQ Event Processing
	/***************************************************************/
	else if(evt == IFEVT_VISCA_INQ)
	{
		err = IF_ERNOPROC;
		if(param->eepidx > 4700)
		{	//VISCA INQ ETC
			err = Visca_Evt_Proc_Inq(param);
		}
	}
	/***************************************************************/
	// Debuging Code
	/***************************************************************/
#ifdef WIN32
	printf("IFEVT:%d, param:%d key:%X Data:%d err : %d)\n", evt, param->eepidx, param->key,IF_EEPUpdate(IFEVT_GETVAL, param->eepidx,0),err);
#else
	#if EVENT_TRACE == 1
	static uint08 i = EVENT_LINE;
	uint08 y = 21 - EVENT_LINE +1 ;

	DebugScrPrintf(y+i,5," ");
	i++;
	i %= EVENT_LINE;
	DebugScrPrintf(y+i,6," IF (%d),Prm (%d),Key (%d),Data (%d)", evt, param->eepidx, param->key,IF_EEPUpdate(IFEVT_GETVAL, param->eepidx,0));
	DebugScrPrintf(y+i,5,"*");
	#endif
	#if EVENT_TRACE == 2
	DebugPrintf(" IF (%d),Prm (%d),Key (%d),Data (%d)\n", evt, param->eepidx, param->key,IF_EEPUpdate(IFEVT_GETVAL, param->eepidx,0));
	#endif
#endif
	return err;
}

