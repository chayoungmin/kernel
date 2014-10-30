/*********************************************************************************************************//**
* @file etcFunc_mw.h
* @author 
*  Chan
* @date 2013.10.15 
* @brief 
*  Header file of etcFunc Middleware
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef ETCFUNC_MW_H_
#define ETCFUNC_MW_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "param_mw.h"
/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef ETCFUNC_MW_EXTERN 
#define ETCFUNC_MW_EXT 
#else 
#define ETCFUNC_MW_EXT extern
#endif
/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/


/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/

typedef enum _MD_DISPLAY_TYPE {
			MD_DP_OFF,
			MD_DP_TEXT,
			MD_DP_IMG,
			MD_DP_ALL,
			MD_DP_TYPE_MAX
} MD_DISPLAY_TYPE;
#define	MD_DISPLAY_TYPE_DEF		MD_DP_OFF

typedef enum _MD_ALARM_TYPE {
			MD_AL_OFF,
			MD_AL_PORT,
			MD_AL_COMM,
			MD_AL_ALL,
			MD_AL_TYPE_MAX
} MD_ALARM_TYPE;
#define	MD_ALARM_TYPE_DEF		MD_AL_OFF

#define	COLOR_PLT_TYPE_DEF		CP_MAX

typedef enum _COLOR_ALPHA_TYPE {
			COLOR_ALPHA_0_P = 0,
			COLOR_ALPHA_25_P = 1,
			COLOR_ALPHA_50_P = 2,
			COLOR_ALPHA_75_P = 3,
			COLOR_ALPHA_MAX
} COLOR_ALPHA_TYPE;


typedef enum _BOX_USE_NO {
	/*
	0 ~ 15  MD USE IT 
	*/
	BOX_NO_MD_0 =0,
	BOX_NO_MD_1 =1,
	BOX_NO_MD_2 =2,
	BOX_NO_MD_3 =3,
	BOX_NO_MD_4 =4,
	BOX_NO_MD_5 =5,
	BOX_NO_MD_6 =6,
	BOX_NO_MD_7 =7,
	BOX_NO_MD_8 =8,
	BOX_NO_MD_9 =9,
	BOX_NO_MD_10 =10,
	BOX_NO_MD_11 =11,
	BOX_NO_MD_12 =12,
	BOX_NO_MD_13 =13,
	BOX_NO_MD_14 =14,
	BOX_NO_MD_15 =15,
	BOX_NO_16 =16,
	BOX_NO_17 =17,
	BOX_NO_18 =18,
	BOX_NO_19 =19,
	BOX_NO_MD_OSD_NO1 = 20,

	BOX_NO_MD_OSD_NO2 = 21,

	BOX_NO_MD_OSD_NO3 = 22,

	BOX_NO_MD_OSD_NO4 = 23,

	BOX_NO_SCREEN_MODE = 24,

	BOX_NO_BLK_SCREEN  = 25,

	BOX_NO_C_LINE_H =26,
	BOX_NO_C_LINE_V =27,
	BOX_NO_28 =28,
	BOX_NO_29 =29,
	BOX_NO_30 =30,
	BOX_NO_31 =31
} BOX_USE_NO;


typedef enum _COLOR_PLT_TYPE {
			CP_WHT,
			CP_YEL,
			CP_CYN,
			CP_GRN,
			CP_MAG,
			CP_RED,
			CP_BLU,
			CP_BLK,
			CP_GRY,
			CP_MAX
} COLOR_PLT_TYPE;
#define	COLOR_PLT_TYPE_DEF		CP_MAX




/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/
/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/



/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
ETCFUNC_MW_EXT void InitEtcFuncMw();
ETCFUNC_MW_EXT void EtcFuncMw_Task();

void MD_Init();
void Privacy_Init();
			   
ETCFUNC_MW_EXT void MD_On(bool state);
ETCFUNC_MW_EXT void MDM_On(uint08 mNum,bool state);
ETCFUNC_MW_EXT void MDM_Pos(uint08 mNum,uint16 left,uint16 right,uint16 top,uint16 bottom);

ETCFUNC_MW_EXT void MDM_Sens(uint08 Sens);
ETCFUNC_MW_EXT void MDM_Time(uint08 Time);


ETCFUNC_MW_EXT void MDM_Output(MD_DISPLAY_TYPE display,MD_ALARM_TYPE alarm);
ETCFUNC_MW_EXT void MD_osdOn();
ETCFUNC_MW_EXT void MD_osdRefresh();


ETCFUNC_MW_EXT void PR_On(bool state);
ETCFUNC_MW_EXT void PRM_On(uint08 mNum,bool state);
ETCFUNC_MW_EXT void PRM_Pos_Pol(uint08 mNum,uint16 P0_x,uint16 P0_y,uint16 P1_x,uint16 P1_y,uint16 P2_x,uint16 P2_y,uint16 P3_x,uint16 P3_y);
//LRTP = 0~100
//12
//43
ETCFUNC_MW_EXT void PRM_Pos(uint08 mNum,uint16 left,uint16 right,uint16 top,uint16 bottom);
ETCFUNC_MW_EXT void PRM_Attr(uint08 mNum,uint32 color,uint08 mAlpha);
			   void PR_UtilOsd();

ETCFUNC_MW_EXT void Box_On(BOX_USE_NO mNum,bool state);
ETCFUNC_MW_EXT void Box_Pos(BOX_USE_NO mNum,uint16 left,uint16 right,uint16 top,uint16 bottom);
ETCFUNC_MW_EXT void Box_Attr(BOX_USE_NO mNum,COLOR_PLT_TYPE color,COLOR_ALPHA_TYPE mAlpha);

ETCFUNC_MW_EXT void DisTask();
ETCFUNC_MW_EXT void etcMw_DisHold(uint08 on); // 1: hOLH , 0: Run


ETCFUNC_MW_EXT int Interp1D (int aiXCur, int aiXPos1, int aiXPos2, int aiYPos1, int aiYPos2);

ETCFUNC_MW_EXT void AdcExtTask();
ETCFUNC_MW_EXT void ExtOutTask();

ETCFUNC_MW_EXT int32 FoucsLensSensGet();
ETCFUNC_MW_EXT int32 ZoomLensSensGet();
ETCFUNC_MW_EXT int32 LensTempGet();		

ETCFUNC_MW_EXT int32 ADKey1Get();	
ETCFUNC_MW_EXT int32 ADKey2Get();	
ETCFUNC_MW_EXT int32 CDS_EXTGet();	


ETCFUNC_MW_EXT void Icr2Day();	
ETCFUNC_MW_EXT void Icr2Night();	
ETCFUNC_MW_EXT uint08 IcrGetState();
ETCFUNC_MW_EXT uint08 IsIcrDay();
ETCFUNC_MW_EXT uint08 IsIcrNight();



ETCFUNC_MW_EXT void IRLed2Day();	
ETCFUNC_MW_EXT void IRLed2Night();	
ETCFUNC_MW_EXT uint08 IRLedGetState();		

ETCFUNC_MW_EXT int08 etcFunc_get_temperature(void);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/

#endif /* ETCFUNC_MW_H_ */

