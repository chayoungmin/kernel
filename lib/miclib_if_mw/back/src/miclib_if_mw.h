/*********************************************************************************************************//**
* @file miclib_if_mw.h
* @author
*  KWNAM, SHKIM
* @date
*  2012.08.20
* @version
*  0.1
* @brief
*  if_mw.c의 헤더
*************************************************************************************************************/
#ifndef _MICLIB_IF_MW_H_
#define _MICLIB_IF_MW_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#ifdef WIN32	// for VS9.0
#include "miclib_type.h"
#else			// for gcc
#include "miclib_type.h"
#endif

#ifndef MICLIB_IF_MW_EXT
#define MICLIB_IF_MW_EXT	extern
#endif

/*************************************************************************************************************
* TYPE DEFINE
*************************************************************************************************************/
/************************************************************************************************************/
/* Event의 종류 */
typedef enum _IFEVT {
	/* EEPRom Event */
	IFEVT_SETVAL,			// Get EEPRom(EEP, PRI, 3D-PRI, USER-EEP) Value, use EEP_IDX
	IFEVT_GETVAL,			// Set EEPRom(EEP, PRI, 3D-PRI, USER-EEP) Value, use EEP_IDX

	/* CAMERA(Middle -> App) Event */
	IFEVT_OSD,				// OSD Event
	IFEVT_INITIAL,			// EEPRom Value Initial Evnet
	IFEVT_VISCA_CMD,		// PROTOCOL VISCA
	IFEVT_VISCA_INQ,		// PROTOCOL VISCA
	IFEVT_CNBH_TECH,		// PROTOCOL CNBH TECHICAL
/*	IFEVT_EEP,				// EEPRom Event
	IFEVT_USER,				// User Event*/
} IFEVT;

/* Return Code */
typedef enum _IFER {
	IF_ERNO = 0x0,			// 정상
	IF_ERFPNULL = 0x1,		// 함수 포인트가 없슴
	IF_INVALIDVAL = 0x2,	// 처리할 수 없는 값임(App -> OSD, Protocol)
	IF_ERNOPROC = 0x4,		// 처리하지 않음
} IFER;

typedef enum _IFER_VISCA {
	IF_COMPLETE = 0x0,		// 정상
	IF_SYNTEX	= 0x1,		// 함수 포인트가 없슴
	IF_LENGTH	= 0x2,		// 처리할 수 없는 값임(App -> OSD, Protocol)
	IF_NOEXCUTE = 0x4,		// 처리하지 않음
	IF_PASS = 0x8,			// PASS
	IF_SOCKET_FULL = 0x10,	// Socket이 가득참
} _IFER_VISCA;

typedef enum _IFER_CNBH {
	IFH_COMPLETE = 0x0,		// 정상
	IFH_SYNTEX	= 0x1,		// 함수 포인트가 없슴
	IFH_LENGTH	= 0x2,		// 처리할 수 없는 값임(App -> OSD, Protocol)
	IFH_NOEXCUTE = 0x4,		// 처리하지 않음
} _IFER_CNBH;
/************************************************************************************************************/
/* EEPRom */
/* EEPRom 데이터 Get, Set 하기 위한 Index */
typedef uint32			EEP_IDX;

#define IF_MAX_QUEUE 256;

#define ALL_IDX_USE		1
#define VAL_TUNE(eep)	(evt == IFEVT_SETVAL ? eep = val : eep)

/* do not delete */
/* EEPRom 데이터의 인덱스, 수정하지 말것 */
#define IDX_NULL				0

/* Header 0x0000 ~ 0x000F */
#define IDX_MEM_STATUS			1
#define IDX_CAM_TYPE			2
#define IDX_CAM_CLASS			3
#define IDX_MEM_VER				4
#define IDX_CCD_TYPE			5
#define IDX_CLIENT_OPT			6
#define IDX_HALL_ADJ			7
#define IDX_LENS_ADJ			8
#define IDX_MASK_ADJ			9
#define IDX_DEFECT_ADJ			10
#define IDX_SHADE_ADJ			11
#define IDX_COLOR_ADJ			12
#define IDX_COMM_SET			13
#define IDX_MENU_USE			14
#define IDX_LENS_INIT_TYPE		15
#define IDX_HOME_USE			16
/* FOCUS 0x0010 ~ 0x0025 */
#define IDX_FOCUS_MODE			101
#define IDX_AF_MODE				102
#define IDX_AF_MOVE_TIME		103
#define IDX_AF_INTERVAL_TIME	104
#define IDX_FOCUS_DIST			105
#define IDX_ZOOM_MODE			106
#define IDX_DZOOM_MODE			107
#define IDX_ZTRK_MODE			108
#define IDX_ZOOM_SPEED			109
#define IDX_LENS_REFRESH_MODE	110
#define IDX_LENS_REFRESH_DAYS	111
#define IDX_ZSRT_MAG			112
#define IDX_ZEND_MAG			113
#define IDX_Z_HOME_POS			114
#define IDX_F_HOME_POS			115
#define IDX_DZ_HOME_POS			116
#define IDX_DZOOM_MAG			117
#define IDX_HOME_MODE			118
#define IDX_HOME_TIME			119
/* EXPOSURE 0x0026 ~ 0x002E */
#define IDX_AE_TGT_BRIGHT		201
#define IDX_AE_MODE				202
#define IDX_AE_AGC_LIMIT		203
#define IDX_AEM_IRIS_STEP		204
#define IDX_AEM_SHUT_STEP		205
#define IDX_AEM_BRIGHT_STEP		206
#define IDX_AE_DSS_STEP			207
#define IDX_AEM_GAIN_STEP		208
#define IDX_AE_FLK_MODE			209
/* WB 0x002F ~ 0x003C */
#define IDX_WB_MODE				301
#define IDX_WB_ENV				302
#define IDX_WB_RED_GAIN			303
#define IDX_WB_BLUE_GAIN		304
#define IDX_WB_COLOR_TEMP		305
#define IDX_ATW_SPEED			306
#define IDX_ATW_FRAME			307
#define IDX_ATW_DELAY			308
#define IDX_USER1_RGAIN			309
#define IDX_USER1_BGAIN			310
#define IDX_USER2_RGAIN			311
#define IDX_USER2_BGAIN			312
/* D/N 0x003D ~ 0x0043 */
#define IDX_DN_MODE				401
#define IDX_DN_ALARM_ON			402
#define IDX_DN_CHG_STEP			403
#define IDX_DN_CDS_STEP			404
#define IDX_DN_CHG_TIME			405
#define IDX_DN_MIN				406
#define IDX_DN_CDS_CHG_TIME		407
#define IDX_DN_CDS_MIN			408
/* IMAGE 0x0044 ~ 0x0050 */
#define IDX_IMG_BRIGHT			501
#define IDX_IMG_CONTRAST		502
#define IDX_IMG_SHARPNESS		503
#define IDX_IMG_CHROMA			504
#define IDX_IMG_HUE				505
#define IDX_IMG_FLIP			506
#define IDX_IMG_FREEZE			507
#define IDX_IMG_EFFECT			508
#define IDX_IMG_COLOR			509
#define IDX_IMG_SHADING			510
#define IDX_IMG_DEFECT			511
#define IDX_IMG_GAMMA_STEP		512
#define IDX_IMG_GAM_MODE		513
#define IDX_IMG_RGAIN			514
#define IDX_IMG_BGAIN			515
#define IDX_HR_MODE				516
/* BACKLIGHT 0x0051 ~ 0x005F */
#define IDX_BL_MODE				601
#define IDX_BLC_MODE			602
#define IDX_BLC_DISP			603
#define IDX_BLC_LEVEL			604
#define IDX_BLC_AREA_X_SRT		605
#define IDX_BLC_AREA_Y_SRT		606
#define IDX_BLC_AREA_WIDTH		607
#define IDX_BLC_AREA_HEIGHT		608
#define IDX_WDR_MODE			609
#define IDX_WDR_LEVEL			610
#define IDX_HLC_MODE			611
#define IDX_HLC_MASK_COLOR		612
#define IDX_HLC_LEVEL			613
#define IDX_HLC_SCALE			614
/* DNR 0x0060 ~ 0x0064 */
#define IDX_DNR_MODE			701
#define IDX_DNR_GLB_MOT			702
#define IDX_DNR_LEVEL			703
#define IDX_3DNR_LEVEL			704
#define IDX_2DNR_LEVEL			705
/* SPECIAL/MOTION 0x0065 ~ 0x007D */
#define IDX_MD_ON				801
#define IDX_MD1_STATE			802
#define IDX_MD1_DISP			803
#define IDX_MD1_ALARM			804
#define IDX_MD1_SENS			805
#define IDX_MD1_X_SRT			806
#define IDX_MD1_Y_SRT			807
#define IDX_MD1_WIDTH			808
#define IDX_MD1_HEIGHT			809
#define IDX_MD2_STATE			810
#define IDX_MD2_DISP			811
#define IDX_MD2_ALARM			812
#define IDX_MD2_SENS			813
#define IDX_MD2_X_SRT			814
#define IDX_MD2_Y_SRT			815
#define IDX_MD2_WIDTH			816
#define IDX_MD2_HEIGHT			817
#define IDX_MD3_STATE			818
#define IDX_MD3_DISP			819
#define IDX_MD3_ALARM			820
#define IDX_MD3_SENS			821
#define IDX_MD3_X_SRT			822
#define IDX_MD3_Y_SRT			823
#define IDX_MD3_WIDTH			824
#define IDX_MD3_HEIGHT			825
#define IDX_MD4_STATE			826
#define IDX_MD4_DISP			827
#define IDX_MD4_ALARM			828
#define IDX_MD4_SENS			829
#define IDX_MD4_X_SRT			830
#define IDX_MD4_Y_SRT			831
#define IDX_MD4_WIDTH			832
#define IDX_MD4_HEIGHT			833
/* SPECIAL/PRIVACY MASK 0x007E ~ 0x00D6 */
#define IDX_MASK_ON				901
#define IDX_MASK_I				902
#define IDX_MASK1_STATE			903
#define IDX_MASK1_TRANS			904
#define IDX_MASK1_COLOR			905
#define IDX_MASK1_MOSAIC		906
#define IDX_MASK1_X_SRT			907
#define IDX_MASK1_Y_SRT			908
#define IDX_MASK1_WIDTH			909
#define IDX_MASK1_HEIGHT		910
#define IDX_MASK1_PAN			911
#define IDX_MASK1_TILT			912
#define IDX_MASK1_ZOOM			913
#define IDX_MASK2_STATE			914
#define IDX_MASK2_TRANS			915
#define IDX_MASK2_COLOR			916
#define IDX_MASK2_MOSAIC		917
#define IDX_MASK2_X_SRT			918
#define IDX_MASK2_Y_SRT			919
#define IDX_MASK2_WIDTH			920
#define IDX_MASK2_HEIGHT		921
#define IDX_MASK2_PAN			922
#define IDX_MASK2_TILT			923
#define IDX_MASK2_ZOOM			924
#define IDX_MASK3_STATE			925
#define IDX_MASK3_TRANS			926
#define IDX_MASK3_COLOR			927
#define IDX_MASK3_MOSAIC		928
#define IDX_MASK3_X_SRT			929
#define IDX_MASK3_Y_SRT			930
#define IDX_MASK3_WIDTH			931
#define IDX_MASK3_HEIGHT		932
#define IDX_MASK3_PAN			933
#define IDX_MASK3_TILT			934
#define IDX_MASK3_ZOOM			935
#define IDX_MASK4_STATE			936
#define IDX_MASK4_TRANS			937
#define IDX_MASK4_COLOR			938
#define IDX_MASK4_MOSAIC		939
#define IDX_MASK4_X_SRT			940
#define IDX_MASK4_Y_SRT			941
#define IDX_MASK4_WIDTH			942
#define IDX_MASK4_HEIGHT		943
#define IDX_MASK4_PAN			944
#define IDX_MASK4_TILT			945
#define IDX_MASK4_ZOOM			946
#define IDX_MASK5_STATE			947
#define IDX_MASK5_TRANS			948
#define IDX_MASK5_COLOR			949
#define IDX_MASK5_MOSAIC		950
#define IDX_MASK5_X_SRT			951
#define IDX_MASK5_Y_SRT			952
#define IDX_MASK5_WIDTH			953
#define IDX_MASK5_HEIGHT		954
#define IDX_MASK5_PAN			955
#define IDX_MASK5_TILT			956
#define IDX_MASK5_ZOOM			957
#define IDX_MASK6_STATE			958
#define IDX_MASK6_TRANS			959
#define IDX_MASK6_COLOR			960
#define IDX_MASK6_MOSAIC		961
#define IDX_MASK6_X_SRT			962
#define IDX_MASK6_Y_SRT			963
#define IDX_MASK6_WIDTH			964
#define IDX_MASK6_HEIGHT		965
#define IDX_MASK6_PAN			966
#define IDX_MASK6_TILT			967
#define IDX_MASK6_ZOOM			968
#define IDX_MASK7_STATE			969
#define IDX_MASK7_TRANS			970
#define IDX_MASK7_COLOR			971
#define IDX_MASK7_MOSAIC		972
#define IDX_MASK7_X_SRT			973
#define IDX_MASK7_Y_SRT			974
#define IDX_MASK7_WIDTH			975
#define IDX_MASK7_HEIGHT		976
#define IDX_MASK7_PAN			977
#define IDX_MASK7_TILT			978
#define IDX_MASK7_ZOOM			979
#define IDX_MASK8_STATE			980
#define IDX_MASK8_TRANS			981
#define IDX_MASK8_COLOR			982
#define IDX_MASK8_MOSAIC		983
#define IDX_MASK8_X_SRT			984
#define IDX_MASK8_Y_SRT			985
#define IDX_MASK8_WIDTH			986
#define IDX_MASK8_HEIGHT		987
#define IDX_MASK8_PAN			988
#define IDX_MASK8_TILT			989
#define IDX_MASK8_ZOOM			990
/* SPECIAL 0x00D7 ~ 0x00DB */
#define IDX_DEFOG_ON			1001
#define IDX_DIS_ON				1002
#define IDX_SYNC				1003
#define IDX_SHADE_ON			1004
#define IDX_SYNC_PHASE			1005
/* SYSTEM 0x00DC ~ 0x00FF */
#define IDX_CAM_ID				1101
#define IDX_CAMID_X_POS			1102
#define IDX_CAMID_Y_POS			1103
#define IDX_BAUDRATE			1104
#define IDX_PROTOCOL			1105
#define IDX_OSD_LANGUAGE		1106
#define IDX_ID_ON				1107
#define IDX_TITLE_ON			1108
#define IDX_ZMAG_ON				1109
#define IDX_FUNC_ON				1110
#define IDX_ALL_ON				1111
#define IDX_TITLE_BLK			1112
#define IDX_TITLE_COLOR			1113
#define IDX_TITLE_X_POS			1114
#define IDX_TITLE_Y_POS			1115
#define IDX_CAM_TITLE_CH1		1116
#define IDX_CAM_TITLE_CH2		1117
#define IDX_CAM_TITLE_CH3		1118
#define IDX_CAM_TITLE_CH4		1119
#define IDX_CAM_TITLE_CH5		1120
#define IDX_CAM_TITLE_CH6		1121
#define IDX_CAM_TITLE_CH7		1122
#define IDX_CAM_TITLE_CH8		1123
#define IDX_CAM_TITLE_CH9		1124
#define IDX_CAM_TITLE_CH10		1125
#define IDX_CAM_TITLE_CH11		1126
#define IDX_CAM_TITLE_CH12		1127
#define IDX_CAM_TITLE_CH13		1128
#define IDX_CAM_TITLE_CH14		1129
#define IDX_CAM_TITLE_CH15		1130
#define IDX_CAM_TITLE_CH16		1131
#define IDX_CAM_TITLE_CH17		1132
#define IDX_CAM_TITLE_CH18		1133
#define IDX_CAM_TITLE_CH19		1134
#define IDX_CAM_TITLE_CH20		1135
#define IDX_CAM_TITLE_CH21		1136
#define IDX_CAM_TITLE_CH22		1137
#define IDX_CAM_TITLE_CH23		1138
#define IDX_CAM_TITLE_CH24		1139
#define IDX_VOUT_FORMAT			1140
#define IDX_LVDS_D				1141
#define IDX_DOUT_FULL			1142
#define IDX_DOUT_ON				1143
#define IDX_CVBS_ON				1144


/* HALL 0x0500 ~ 0x050F */
#define IDX_TGT_HALL_MAX		2001
#define IDX_TGT_HALL_MIN		2002
#define IDX_HADJ_MAX			2003
#define IDX_HADJ_MIN			2004
#define IDX_HO_ZERO				2005
#define IDX_HG_ZERO				2006
#define IDX_HB_ZERO				2007
#define IDX_HADJ_DIFF_OFF		2008
#define IDX_HADJ_MEAN_OFF		2009
#define IDX_HADJ_HG				2010
#define IDX_HADJ_HO				2011
#define IDX_HADJ_HB				2012
/* LENS OFFSET 0x0510 ~ 0x051D */
#define IDX_OADJ_ZADD			2101
#define IDX_OADJ_FADD			2102
#define IDX_OADJ_ZOFF			2103
#define IDX_OADJ_FOFF			2104
#define IDX_OADJ_PD_SRT			2105
#define IDX_OADJ_ZD_SRT			2106
#define IDX_OADJ_FD_SRT			2107
#define IDX_OADJ_P2DEC_R		2108
#define IDX_OADJ_T2DEC_R		2109
#define IDX_OADJ_PD				2110
#define IDX_OADJ_ZD				2111
#define IDX_OADJ_FD				2112
#define IDX_OADJ_WEND_S			2113
#define IDX_OADJ_TEND_S			2114
/* PRIVACY MASK 0x051E ~ 0x0512 */
#define IDX_MADJ_3D_PAN_NT		2201
#define IDX_MADJ_3D_TILT_NT		2202
#define IDX_MADJ_3D_PAN_PA		2203
#define IDX_MADJ_3D_TILT_PA		2204
/* DEFECT 0x0522 ~ 0x0525 */
#define IDX_DADJ_THRESHOLD		2301
/* SHADING 0x0526 ~ 0x0529 */
#define IDX_SADJ_GAIN			2401
#define IDX_SADJ_OFFSET			2402
/* COLOR 0x052A ~ 0x053F */
/* LOGO 0x0540 ~ 0x055F */
#define IDX_LOGO_CH1			2601
#define IDX_LOGO_CH2			2602
#define IDX_LOGO_CH3			2603
#define IDX_LOGO_CH4			2604
#define IDX_LOGO_CH5			2605
#define IDX_LOGO_CH6			2606
#define IDX_LOGO_CH7			2607
#define IDX_LOGO_CH8			2608
#define IDX_LOGO_CH9			2609
#define IDX_LOGO_CH10			2610
#define IDX_LOGO_CH11			2611
#define IDX_LOGO_CH12			2612
#define IDX_LOGO_CH13			2613
#define IDX_LOGO_CH14			2614
#define IDX_LOGO_CH15			2615
#define IDX_LOGO_CH16			2616
#define IDX_LOGO_CH17			2617
#define IDX_LOGO_CH18			2618
#define IDX_LOGO_CH19			2619
#define IDX_LOGO_CH20			2620
#define IDX_LOGO_CH21			2621
#define IDX_LOGO_CH22			2622
#define IDX_LOGO_CH23			2623
#define IDX_LOGO_CH24			2624
#define IDX_LOGO_CH25			2625
#define IDX_LOGO_CH26			2626
#define IDX_LOGO_CH27			2627
#define IDX_LOGO_CH28			2628
#define IDX_LOGO_CH29			2629
#define IDX_LOGO_CH30			2630
#define IDX_LOGO_CH31			2631
#define IDX_LOGO_CH32			2632
/* ADKEY 0x0560 ~ 0x056F */
#define IDX_ADKEY00				2701
#define IDX_ADKEY01				2702
#define IDX_ADKEY02				2703
#define IDX_ADKEY03				2704
#define IDX_ADKEY04				2705
#define IDX_ADKEY05				2706
#define IDX_ADKEY06				2707
#define IDX_ADKEY07				2708
#define IDX_ADKEY10				2709
#define IDX_ADKEY11				2710
#define IDX_ADKEY12				2711
#define IDX_ADKEY13				2712
#define IDX_ADKEY14				2713
#define IDX_ADKEY15				2714
#define IDX_ADKEY16				2715
#define IDX_ADKEY17				2716

/* Visca 0x1000 ~ 0x137F */
#define VDX_PWR_ON							3001
#define VDX_ZOOM_POS                        3002
#define VDX_DZOOM_ON                        3003
#define VDX_DZOOM_MODE                      3004
#define VDX_DZOOM_POS                       3005
#define VDX_FOCUS_POS                       3006
#define VDX_F_MODE                          3007
#define VDX_NEAR_LIMIT                      3008
#define VDX_AF_SENS                         3009
#define VDX_AF_MODE                         3010
#define VDX_AF_MOVE_TIME                    3011
#define VDX_AF_INTERVAL_TIME                3012
#define VDX_IR_COR                          3013
#define VDX_WB_MODE                         3014
#define VDX_PUSH_WB_RGAIN                   3015
#define VDX_PUSH_WB_BGAIN                   3016
#define VDX_R_GAIN                          3017
#define VDX_B_GAIN                          3018
#define VDX_AE_MODE                         3019
#define VDX_ASS_ON                          3020
#define VDX_SHUTTER_STEP                    3021
#define VDX_IRIS_STEP                       3022
#define VDX_GAIN_STEP                       3023
#define VDX_BRIGHT_STEP                     3024
#define VDX_COMP_ON                         3025
#define VDX_EXP_COMP_VAL                    3026
#define VDX_BLC_ON                          3027
#define VDX_SPOT_AE_ON                      3028
#define VDX_SPOT_AE_X_POS                   3029
#define VDX_SPOT_AE_Y_POS                   3030
#define VDX_AE_RESPONSE                     3031
#define VDX_WD_MODE                         3032
#define VDX_WD_BRT_L                        3033
#define VDX_WD_BRT_COMP                     3034
#define VDX_WD_COMP_L                       3035
#define VDX_DEFOG_ON                        3036
#define VDX_APER_GAIN                       3037
#define VDX_HR_ON                           3038
#define VDX_NR_SET                          3039
#define VDX_GAM_SET                         3040
#define VDX_HIGH_SENS_ON                    3041
#define VDX_LR_ON                           3042
#define VDX_FREEZE_ON                       3043
#define VDX_P_EFFECT                        3044
#define VDX_FLIP_ON                         3045
#define VDX_ICR_ON                          3046
#define VDX_AICR_ON                         3047
#define VDX_AICR_THRS_L                     3048
#define VDX_AICR_ALARM_ON                   3049
#define VDX_DISP_ON                         3050
#define VDX_TITLE_H_POS0                    3051
#define VDX_TITLE_ON0                       3052
#define VDX_TITLE_LINE0                     3053
#define VDX_TITLE_BLINK0                    3054
#define VDX_TITLE_COLOR0                    3055
#define VDX_TITLE_LINE0_CH1                 3056
#define VDX_TITLE_LINE0_CH2                 3057
#define VDX_TITLE_LINE0_CH3                 3058
#define VDX_TITLE_LINE0_CH4                 3059
#define VDX_TITLE_LINE0_CH5                 3060
#define VDX_TITLE_LINE0_CH6                 3061
#define VDX_TITLE_LINE0_CH7                 3062
#define VDX_TITLE_LINE0_CH8                 3063
#define VDX_TITLE_LINE0_CH9                 3064
#define VDX_TITLE_LINE0_CH10                3065
#define VDX_TITLE_LINE0_CH11                3066
#define VDX_TITLE_LINE0_CH12                3067
#define VDX_TITLE_LINE0_CH13                3068
#define VDX_TITLE_LINE0_CH14                3069
#define VDX_TITLE_LINE0_CH15                3070
#define VDX_TITLE_LINE0_CH16                3071
#define VDX_TITLE_LINE0_CH17                3072
#define VDX_TITLE_LINE0_CH18                3073
#define VDX_TITLE_LINE0_CH19                3074
#define VDX_TITLE_LINE0_CH20                3075
#define VDX_TITLE_H_POS1                    3076
#define VDX_TITLE_ON1                       3077
#define VDX_TITLE_LINE1                     3078
#define VDX_TITLE_BLINK1                    3079
#define VDX_TITLE_COLOR1                    3080
#define VDX_TITLE_LINE1_CH1                 3081
#define VDX_TITLE_LINE1_CH2                 3082
#define VDX_TITLE_LINE1_CH3                 3083
#define VDX_TITLE_LINE1_CH4                 3084
#define VDX_TITLE_LINE1_CH5                 3085
#define VDX_TITLE_LINE1_CH6                 3086
#define VDX_TITLE_LINE1_CH7                 3087
#define VDX_TITLE_LINE1_CH8                 3088
#define VDX_TITLE_LINE1_CH9                 3089
#define VDX_TITLE_LINE1_CH10                3090
#define VDX_TITLE_LINE1_CH11                3091
#define VDX_TITLE_LINE1_CH12                3092
#define VDX_TITLE_LINE1_CH13                3093
#define VDX_TITLE_LINE1_CH14                3094
#define VDX_TITLE_LINE1_CH15                3095
#define VDX_TITLE_LINE1_CH16                3096
#define VDX_TITLE_LINE1_CH17                3097
#define VDX_TITLE_LINE1_CH18                3098
#define VDX_TITLE_LINE1_CH19                3099
#define VDX_TITLE_LINE1_CH20                3100
#define VDX_TITLE_H_POS2                    3101
#define VDX_TITLE_ON2                       3102
#define VDX_TITLE_LINE2                     3103
#define VDX_TITLE_BLINK2                    3104
#define VDX_TITLE_COLOR2                    3105
#define VDX_TITLE_LINE2_CH1                 3106
#define VDX_TITLE_LINE2_CH2                 3107
#define VDX_TITLE_LINE2_CH3                 3108
#define VDX_TITLE_LINE2_CH4                 3109
#define VDX_TITLE_LINE2_CH5                 3110
#define VDX_TITLE_LINE2_CH6                 3111
#define VDX_TITLE_LINE2_CH7                 3112
#define VDX_TITLE_LINE2_CH8                 3113
#define VDX_TITLE_LINE2_CH9                 3114
#define VDX_TITLE_LINE2_CH10                3115
#define VDX_TITLE_LINE2_CH11                3116
#define VDX_TITLE_LINE2_CH12                3117
#define VDX_TITLE_LINE2_CH13                3118
#define VDX_TITLE_LINE2_CH14                3119
#define VDX_TITLE_LINE2_CH15                3120
#define VDX_TITLE_LINE2_CH16                3121
#define VDX_TITLE_LINE2_CH17                3122
#define VDX_TITLE_LINE2_CH18                3123
#define VDX_TITLE_LINE2_CH19                3124
#define VDX_TITLE_LINE2_CH20                3125
#define VDX_TITLE_H_POS3                    3126
#define VDX_TITLE_ON3                       3127
#define VDX_TITLE_LINE3                     3128
#define VDX_TITLE_BLINK3                    3129
#define VDX_TITLE_COLOR3                    3130
#define VDX_TITLE_LINE3_CH1                 3131
#define VDX_TITLE_LINE3_CH2                 3132
#define VDX_TITLE_LINE3_CH3                 3133
#define VDX_TITLE_LINE3_CH4                 3134
#define VDX_TITLE_LINE3_CH5                 3135
#define VDX_TITLE_LINE3_CH6                 3136
#define VDX_TITLE_LINE3_CH7                 3137
#define VDX_TITLE_LINE3_CH8                 3138
#define VDX_TITLE_LINE3_CH9                 3139
#define VDX_TITLE_LINE3_CH10                3140
#define VDX_TITLE_LINE3_CH11                3141
#define VDX_TITLE_LINE3_CH12                3142
#define VDX_TITLE_LINE3_CH13                3143
#define VDX_TITLE_LINE3_CH14                3144
#define VDX_TITLE_LINE3_CH15                3145
#define VDX_TITLE_LINE3_CH16                3146
#define VDX_TITLE_LINE3_CH17                3147
#define VDX_TITLE_LINE3_CH18                3148
#define VDX_TITLE_LINE3_CH19                3149
#define VDX_TITLE_LINE3_CH20                3150
#define VDX_TITLE_H_POS4                    3151
#define VDX_TITLE_ON4                       3152
#define VDX_TITLE_LINE4                     3153
#define VDX_TITLE_BLINK4                    3154
#define VDX_TITLE_COLOR4                    3155
#define VDX_TITLE_LINE4_CH1                 3156
#define VDX_TITLE_LINE4_CH2                 3157
#define VDX_TITLE_LINE4_CH3                 3158
#define VDX_TITLE_LINE4_CH4                 3159
#define VDX_TITLE_LINE4_CH5                 3160
#define VDX_TITLE_LINE4_CH6                 3161
#define VDX_TITLE_LINE4_CH7                 3162
#define VDX_TITLE_LINE4_CH8                 3163
#define VDX_TITLE_LINE4_CH9                 3164
#define VDX_TITLE_LINE4_CH10                3165
#define VDX_TITLE_LINE4_CH11                3166
#define VDX_TITLE_LINE4_CH12                3167
#define VDX_TITLE_LINE4_CH13                3168
#define VDX_TITLE_LINE4_CH14                3169
#define VDX_TITLE_LINE4_CH15                3170
#define VDX_TITLE_LINE4_CH16                3171
#define VDX_TITLE_LINE4_CH17                3172
#define VDX_TITLE_LINE4_CH18                3173
#define VDX_TITLE_LINE4_CH19                3174
#define VDX_TITLE_LINE4_CH20                3175
#define VDX_TITLE_H_POS5                    3176
#define VDX_TITLE_ON5                       3177
#define VDX_TITLE_LINE5                     3178
#define VDX_TITLE_BLINK5                    3179
#define VDX_TITLE_COLOR5                    3180
#define VDX_TITLE_LINE5_CH1                 3181
#define VDX_TITLE_LINE5_CH2                 3182
#define VDX_TITLE_LINE5_CH3                 3183
#define VDX_TITLE_LINE5_CH4                 3184
#define VDX_TITLE_LINE5_CH5                 3185
#define VDX_TITLE_LINE5_CH6                 3186
#define VDX_TITLE_LINE5_CH7                 3187
#define VDX_TITLE_LINE5_CH8                 3188
#define VDX_TITLE_LINE5_CH9                 3189
#define VDX_TITLE_LINE5_CH10                3190
#define VDX_TITLE_LINE5_CH11                3191
#define VDX_TITLE_LINE5_CH12                3192
#define VDX_TITLE_LINE5_CH13                3193
#define VDX_TITLE_LINE5_CH14                3194
#define VDX_TITLE_LINE5_CH15                3195
#define VDX_TITLE_LINE5_CH16                3196
#define VDX_TITLE_LINE5_CH17                3197
#define VDX_TITLE_LINE5_CH18                3198
#define VDX_TITLE_LINE5_CH19                3199
#define VDX_TITLE_LINE5_CH20                3200
#define VDX_TITLE_H_POS6                    3201
#define VDX_TITLE_ON6                       3202
#define VDX_TITLE_LINE6                     3203
#define VDX_TITLE_BLINK6                    3204
#define VDX_TITLE_COLOR6                    3205
#define VDX_TITLE_LINE6_CH1                 3206
#define VDX_TITLE_LINE6_CH2                 3207
#define VDX_TITLE_LINE6_CH3                 3208
#define VDX_TITLE_LINE6_CH4                 3209
#define VDX_TITLE_LINE6_CH5                 3210
#define VDX_TITLE_LINE6_CH6                 3211
#define VDX_TITLE_LINE6_CH7                 3212
#define VDX_TITLE_LINE6_CH8                 3213
#define VDX_TITLE_LINE6_CH9                 3214
#define VDX_TITLE_LINE6_CH10                3215
#define VDX_TITLE_LINE6_CH11                3216
#define VDX_TITLE_LINE6_CH12                3217
#define VDX_TITLE_LINE6_CH13                3218
#define VDX_TITLE_LINE6_CH14                3219
#define VDX_TITLE_LINE6_CH15                3220
#define VDX_TITLE_LINE6_CH16                3221
#define VDX_TITLE_LINE6_CH17                3222
#define VDX_TITLE_LINE6_CH18                3223
#define VDX_TITLE_LINE6_CH19                3224
#define VDX_TITLE_LINE6_CH20                3225
#define VDX_TITLE_H_POS7                    3226
#define VDX_TITLE_ON7                       3227
#define VDX_TITLE_LINE7                     3228
#define VDX_TITLE_BLINK7                    3229
#define VDX_TITLE_COLOR7                    3230
#define VDX_TITLE_LINE7_CH1                 3231
#define VDX_TITLE_LINE7_CH2                 3232
#define VDX_TITLE_LINE7_CH3                 3233
#define VDX_TITLE_LINE7_CH4                 3234
#define VDX_TITLE_LINE7_CH5                 3235
#define VDX_TITLE_LINE7_CH6                 3236
#define VDX_TITLE_LINE7_CH7                 3237
#define VDX_TITLE_LINE7_CH8                 3238
#define VDX_TITLE_LINE7_CH9                 3239
#define VDX_TITLE_LINE7_CH10                3240
#define VDX_TITLE_LINE7_CH11                3241
#define VDX_TITLE_LINE7_CH12                3242
#define VDX_TITLE_LINE7_CH13                3243
#define VDX_TITLE_LINE7_CH14                3244
#define VDX_TITLE_LINE7_CH15                3245
#define VDX_TITLE_LINE7_CH16                3246
#define VDX_TITLE_LINE7_CH17                3247
#define VDX_TITLE_LINE7_CH18                3248
#define VDX_TITLE_LINE7_CH19                3249
#define VDX_TITLE_LINE7_CH20                3250
#define VDX_TITLE_H_POS8                    3251
#define VDX_TITLE_ON8                       3252
#define VDX_TITLE_LINE8                     3253
#define VDX_TITLE_BLINK8                    3254
#define VDX_TITLE_COLOR8                    3255
#define VDX_TITLE_LINE8_CH1                 3256
#define VDX_TITLE_LINE8_CH2                 3257
#define VDX_TITLE_LINE8_CH3                 3258
#define VDX_TITLE_LINE8_CH4                 3259
#define VDX_TITLE_LINE8_CH5                 3260
#define VDX_TITLE_LINE8_CH6                 3261
#define VDX_TITLE_LINE8_CH7                 3262
#define VDX_TITLE_LINE8_CH8                 3263
#define VDX_TITLE_LINE8_CH9                 3264
#define VDX_TITLE_LINE8_CH10                3265
#define VDX_TITLE_LINE8_CH11                3266
#define VDX_TITLE_LINE8_CH12                3267
#define VDX_TITLE_LINE8_CH13                3268
#define VDX_TITLE_LINE8_CH14                3269
#define VDX_TITLE_LINE8_CH15                3270
#define VDX_TITLE_LINE8_CH16                3271
#define VDX_TITLE_LINE8_CH17                3272
#define VDX_TITLE_LINE8_CH18                3273
#define VDX_TITLE_LINE8_CH19                3274
#define VDX_TITLE_LINE8_CH20                3275
#define VDX_TITLE_H_POS9                    3276
#define VDX_TITLE_ON9                       3277
#define VDX_TITLE_LINE9                     3278
#define VDX_TITLE_BLINK9                    3279
#define VDX_TITLE_COLOR9                    3280
#define VDX_TITLE_LINE9_CH1                 3281
#define VDX_TITLE_LINE9_CH2                 3282
#define VDX_TITLE_LINE9_CH3                 3283
#define VDX_TITLE_LINE9_CH4                 3284
#define VDX_TITLE_LINE9_CH5                 3285
#define VDX_TITLE_LINE9_CH6                 3286
#define VDX_TITLE_LINE9_CH7                 3287
#define VDX_TITLE_LINE9_CH8                 3288
#define VDX_TITLE_LINE9_CH9                 3289
#define VDX_TITLE_LINE9_CH10                3290
#define VDX_TITLE_LINE9_CH11                3291
#define VDX_TITLE_LINE9_CH12                3292
#define VDX_TITLE_LINE9_CH13                3293
#define VDX_TITLE_LINE9_CH14                3294
#define VDX_TITLE_LINE9_CH15                3295
#define VDX_TITLE_LINE9_CH16                3296
#define VDX_TITLE_LINE9_CH17                3297
#define VDX_TITLE_LINE9_CH18                3298
#define VDX_TITLE_LINE9_CH19                3299
#define VDX_TITLE_LINE9_CH20                3300
#define VDX_TITLE_H_POS10                   3301
#define VDX_TITLE_ON10                      3302
#define VDX_TITLE_LINE10                    3303
#define VDX_TITLE_BLINK10                   3304
#define VDX_TITLE_COLOR10                   3305
#define VDX_TITLE_LINE10_CH1                3306
#define VDX_TITLE_LINE10_CH2                3307
#define VDX_TITLE_LINE10_CH3                3308
#define VDX_TITLE_LINE10_CH4                3309
#define VDX_TITLE_LINE10_CH5                3310
#define VDX_TITLE_LINE10_CH6                3311
#define VDX_TITLE_LINE10_CH7                3312
#define VDX_TITLE_LINE10_CH8                3313
#define VDX_TITLE_LINE10_CH9                3314
#define VDX_TITLE_LINE10_CH10               3315
#define VDX_TITLE_LINE10_CH11               3316
#define VDX_TITLE_LINE10_CH12               3317
#define VDX_TITLE_LINE10_CH13               3318
#define VDX_TITLE_LINE10_CH14               3319
#define VDX_TITLE_LINE10_CH15               3320
#define VDX_TITLE_LINE10_CH16               3321
#define VDX_TITLE_LINE10_CH17               3322
#define VDX_TITLE_LINE10_CH18               3323
#define VDX_TITLE_LINE10_CH19               3324
#define VDX_TITLE_LINE10_CH20               3325
#define VDX_MUTE_ON                         3326
#define VDX_MASK_CL_ON                      3327
#define VDX_MASK_ON01                       3328
#define VDX_MASK_DISP_ON01                  3329
#define VDX_MASK_I01                        3330
#define VDX_MASK_TRANS01                    3331
#define VDX_MASK_MOSAIC01                   3332
#define VDX_MASK_COLOR_ON01                 3333
#define VDX_MASK_COLOR_OFF01                3334
#define VDX_MASK_X_POS01                    3335
#define VDX_MASK_Y_POS01                    3336
#define VDX_MASK_WIDTH01                    3337
#define VDX_MASK_HEIGHT01                   3338
#define VDX_MASK_PAN_ANGLE01                3339
#define VDX_MASK_TILT_ANGLE01               3340
#define VDX_MASK_ZOOM01                     3341
#define VDX_MASK_ON02                       3342
#define VDX_MASK_DISP_ON02                  3343
#define VDX_MASK_I02                        3344
#define VDX_MASK_TRANS02                    3345
#define VDX_MASK_MOSAIC02                   3346
#define VDX_MASK_COLOR_ON02                 3347
#define VDX_MASK_COLOR_OFF02                3348
#define VDX_MASK_X_POS02                    3349
#define VDX_MASK_Y_POS02                    3350
#define VDX_MASK_WIDTH02                    3351
#define VDX_MASK_HEIGHT02                   3352
#define VDX_MASK_PAN_ANGLE02                3353
#define VDX_MASK_TILT_ANGLE02               3354
#define VDX_MASK_ZOOM02                     3355
#define VDX_MASK_ON03                       3356
#define VDX_MASK_DISP_ON03                  3357
#define VDX_MASK_I03                        3358
#define VDX_MASK_TRANS03                    3359
#define VDX_MASK_MOSAIC03                   3360
#define VDX_MASK_COLOR_ON03                 3361
#define VDX_MASK_COLOR_OFF03                3362
#define VDX_MASK_X_POS03                    3363
#define VDX_MASK_Y_POS03                    3364
#define VDX_MASK_WIDTH03                    3365
#define VDX_MASK_HEIGHT03                   3366
#define VDX_MASK_PAN_ANGLE03                3367
#define VDX_MASK_TILT_ANGLE03               3368
#define VDX_MASK_ZOOM03                     3369
#define VDX_MASK_ON04                       3370
#define VDX_MASK_DISP_ON04                  3371
#define VDX_MASK_I04                        3372
#define VDX_MASK_TRANS04                    3373
#define VDX_MASK_MOSAIC04                   3374
#define VDX_MASK_COLOR_ON04                 3375
#define VDX_MASK_COLOR_OFF04                3376
#define VDX_MASK_X_POS04                    3377
#define VDX_MASK_Y_POS04                    3378
#define VDX_MASK_WIDTH04                    3379
#define VDX_MASK_HEIGHT04                   3380
#define VDX_MASK_PAN_ANGLE04                3381
#define VDX_MASK_TILT_ANGLE04               3382
#define VDX_MASK_ZOOM04                     3383
#define VDX_MASK_ON05                       3384
#define VDX_MASK_DISP_ON05                  3385
#define VDX_MASK_I05                        3386
#define VDX_MASK_TRANS05                    3387
#define VDX_MASK_MOSAIC05                   3388
#define VDX_MASK_COLOR_ON05                 3389
#define VDX_MASK_COLOR_OFF05                3390
#define VDX_MASK_X_POS05                    3391
#define VDX_MASK_Y_POS05                    3392
#define VDX_MASK_WIDTH05                    3393
#define VDX_MASK_HEIGHT05                   3394
#define VDX_MASK_PAN_ANGLE05                3395
#define VDX_MASK_TILT_ANGLE05               3396
#define VDX_MASK_ZOOM05                     3397
#define VDX_MASK_ON06                       3398
#define VDX_MASK_DISP_ON06                  3399
#define VDX_MASK_I06                        3400
#define VDX_MASK_TRANS06                    3401
#define VDX_MASK_MOSAIC06                   3402
#define VDX_MASK_COLOR_ON06                 3403
#define VDX_MASK_COLOR_OFF06                3404
#define VDX_MASK_X_POS06                    3405
#define VDX_MASK_Y_POS06                    3406
#define VDX_MASK_WIDTH06                    3407
#define VDX_MASK_HEIGHT06                   3408
#define VDX_MASK_PAN_ANGLE06                3409
#define VDX_MASK_TILT_ANGLE06               3410
#define VDX_MASK_ZOOM06                     3411
#define VDX_MASK_ON07                       3412
#define VDX_MASK_DISP_ON07                  3413
#define VDX_MASK_I07                        3414
#define VDX_MASK_TRANS07                    3415
#define VDX_MASK_MOSAIC07                   3416
#define VDX_MASK_COLOR_ON07                 3417
#define VDX_MASK_COLOR_OFF07                3418
#define VDX_MASK_X_POS07                    3419
#define VDX_MASK_Y_POS07                    3420
#define VDX_MASK_WIDTH07                    3421
#define VDX_MASK_HEIGHT07                   3422
#define VDX_MASK_PAN_ANGLE07                3423
#define VDX_MASK_TILT_ANGLE07               3424
#define VDX_MASK_ZOOM07                     3425
#define VDX_MASK_ON08                       3426
#define VDX_MASK_DISP_ON08                  3427
#define VDX_MASK_I08                        3428
#define VDX_MASK_TRANS08                    3429
#define VDX_MASK_MOSAIC08                   3430
#define VDX_MASK_COLOR_ON08                 3431
#define VDX_MASK_COLOR_OFF08                3432
#define VDX_MASK_X_POS08                    3433
#define VDX_MASK_Y_POS08                    3434
#define VDX_MASK_WIDTH08                    3435
#define VDX_MASK_HEIGHT08                   3436
#define VDX_MASK_PAN_ANGLE08                3437
#define VDX_MASK_TILT_ANGLE08               3438
#define VDX_MASK_ZOOM08                     3439
#define VDX_MASK_ON11                       3440
#define VDX_MASK_DISP_ON11                  3441
#define VDX_MASK_I11                        3442
#define VDX_MASK_TRANS11                    3443
#define VDX_MASK_MOSAIC11                   3444
#define VDX_MASK_COLOR_ON11                 3445
#define VDX_MASK_COLOR_OFF11                3446
#define VDX_MASK_X_POS11                    3447
#define VDX_MASK_Y_POS11                    3448
#define VDX_MASK_WIDTH11                    3449
#define VDX_MASK_HEIGHT11                   3450
#define VDX_MASK_PAN_ANGLE11                3451
#define VDX_MASK_TILT_ANGLE11               3452
#define VDX_MASK_ZOOM11                     3453
#define VDX_MASK_ON12                       3454
#define VDX_MASK_DISP_ON12                  3455
#define VDX_MASK_I12                        3456
#define VDX_MASK_TRANS12                    3457
#define VDX_MASK_MOSAIC12                   3458
#define VDX_MASK_COLOR_ON12                 3459
#define VDX_MASK_COLOR_OFF12                3460
#define VDX_MASK_X_POS12                    3461
#define VDX_MASK_Y_POS12                    3462
#define VDX_MASK_WIDTH12                    3463
#define VDX_MASK_HEIGHT12                   3464
#define VDX_MASK_PAN_ANGLE12                3465
#define VDX_MASK_TILT_ANGLE12               3466
#define VDX_MASK_ZOOM12                     3467
#define VDX_MASK_ON13                       3468
#define VDX_MASK_DISP_ON13                  3469
#define VDX_MASK_I13                        3470
#define VDX_MASK_TRANS13                    3471
#define VDX_MASK_MOSAIC13                   3472
#define VDX_MASK_COLOR_ON13                 3473
#define VDX_MASK_COLOR_OFF13                3474
#define VDX_MASK_X_POS13                    3475
#define VDX_MASK_Y_POS13                    3476
#define VDX_MASK_WIDTH13                    3477
#define VDX_MASK_HEIGHT13                   3478
#define VDX_MASK_PAN_ANGLE13                3479
#define VDX_MASK_TILT_ANGLE13               3480
#define VDX_MASK_ZOOM13                     3481
#define VDX_MASK_ON14                       3482
#define VDX_MASK_DISP_ON14                  3483
#define VDX_MASK_I14                        3484
#define VDX_MASK_TRANS14                    3485
#define VDX_MASK_MOSAIC14                   3486
#define VDX_MASK_COLOR_ON14                 3487
#define VDX_MASK_COLOR_OFF14                3488
#define VDX_MASK_X_POS14                    3489
#define VDX_MASK_Y_POS14                    3490
#define VDX_MASK_WIDTH14                    3491
#define VDX_MASK_HEIGHT14                   3492
#define VDX_MASK_PAN_ANGLE14                3493
#define VDX_MASK_TILT_ANGLE14               3494
#define VDX_MASK_ZOOM14                     3495
#define VDX_MASK_ON15                       3496
#define VDX_MASK_DISP_ON15                  3497
#define VDX_MASK_I15                        3498
#define VDX_MASK_TRANS15                    3499
#define VDX_MASK_MOSAIC15                   3500
#define VDX_MASK_COLOR_ON15                 3501
#define VDX_MASK_COLOR_OFF15                3502
#define VDX_MASK_X_POS15                    3503
#define VDX_MASK_Y_POS15                    3504
#define VDX_MASK_WIDTH15                    3505
#define VDX_MASK_HEIGHT15                   3506
#define VDX_MASK_PAN_ANGLE15                3507
#define VDX_MASK_TILT_ANGLE15               3508
#define VDX_MASK_ZOOM15                     3509
#define VDX_MASK_ON16                       3510
#define VDX_MASK_DISP_ON16                  3511
#define VDX_MASK_I16                        3512
#define VDX_MASK_TRANS16                    3513
#define VDX_MASK_MOSAIC16                   3514
#define VDX_MASK_COLOR_ON16                 3515
#define VDX_MASK_COLOR_OFF16                3516
#define VDX_MASK_X_POS16                    3517
#define VDX_MASK_Y_POS16                    3518
#define VDX_MASK_WIDTH16                    3519
#define VDX_MASK_HEIGHT16                   3520
#define VDX_MASK_PAN_ANGLE16                3521
#define VDX_MASK_TILT_ANGLE16               3522
#define VDX_MASK_ZOOM16                     3523
#define VDX_MASK_ON17                       3524
#define VDX_MASK_DISP_ON17                  3525
#define VDX_MASK_I17                        3526
#define VDX_MASK_TRANS17                    3527
#define VDX_MASK_MOSAIC17                   3528
#define VDX_MASK_COLOR_ON17                 3529
#define VDX_MASK_COLOR_OFF17                3530
#define VDX_MASK_X_POS17                    3531
#define VDX_MASK_Y_POS17                    3532
#define VDX_MASK_WIDTH17                    3533
#define VDX_MASK_HEIGHT17                   3534
#define VDX_MASK_PAN_ANGLE17                3535
#define VDX_MASK_TILT_ANGLE17               3536
#define VDX_MASK_ZOOM17                     3537
#define VDX_MASK_ON18                       3538
#define VDX_MASK_DISP_ON18                  3539
#define VDX_MASK_I18                        3540
#define VDX_MASK_TRANS18                    3541
#define VDX_MASK_MOSAIC18                   3542
#define VDX_MASK_COLOR_ON18                 3543
#define VDX_MASK_COLOR_OFF18                3544
#define VDX_MASK_X_POS18                    3545
#define VDX_MASK_Y_POS18                    3546
#define VDX_MASK_WIDTH18                    3547
#define VDX_MASK_HEIGHT18                   3548
#define VDX_MASK_PAN_ANGLE18                3549
#define VDX_MASK_TILT_ANGLE18               3550
#define VDX_MASK_ZOOM18                     3551
#define VDX_MASK_ON21                       3552
#define VDX_MASK_DISP_ON21                  3553
#define VDX_MASK_I21                        3554
#define VDX_MASK_TRANS21                    3555
#define VDX_MASK_MOSAIC21                   3556
#define VDX_MASK_COLOR_ON21                 3557
#define VDX_MASK_COLOR_OFF21                3558
#define VDX_MASK_X_POS21                    3559
#define VDX_MASK_Y_POS21                    3560
#define VDX_MASK_WIDTH21                    3561
#define VDX_MASK_HEIGHT21                   3562
#define VDX_MASK_PAN_ANGLE21                3563
#define VDX_MASK_TILT_ANGLE21               3564
#define VDX_MASK_ZOOM21                     3565
#define VDX_MASK_ON22                       3566
#define VDX_MASK_DISP_ON22                  3567
#define VDX_MASK_I22                        3568
#define VDX_MASK_TRANS22                    3569
#define VDX_MASK_MOSAIC22                   3570
#define VDX_MASK_COLOR_ON22                 3571
#define VDX_MASK_COLOR_OFF22                3572
#define VDX_MASK_X_POS22                    3573
#define VDX_MASK_Y_POS22                    3574
#define VDX_MASK_WIDTH22                    3575
#define VDX_MASK_HEIGHT22                   3576
#define VDX_MASK_PAN_ANGLE22                3577
#define VDX_MASK_TILT_ANGLE22               3578
#define VDX_MASK_ZOOM22                     3579
#define VDX_MASK_ON23                       3580
#define VDX_MASK_DISP_ON23                  3581
#define VDX_MASK_I23                        3582
#define VDX_MASK_TRANS23                    3583
#define VDX_MASK_MOSAIC23                   3584
#define VDX_MASK_COLOR_ON23                 3585
#define VDX_MASK_COLOR_OFF23                3586
#define VDX_MASK_X_POS23                    3587
#define VDX_MASK_Y_POS23                    3588
#define VDX_MASK_WIDTH23                    3589
#define VDX_MASK_HEIGHT23                   3590
#define VDX_MASK_PAN_ANGLE23                3591
#define VDX_MASK_TILT_ANGLE23               3592
#define VDX_MASK_ZOOM23                     3593
#define VDX_MASK_ON24                       3594
#define VDX_MASK_DISP_ON24                  3595
#define VDX_MASK_I24                        3596
#define VDX_MASK_TRANS24                    3597
#define VDX_MASK_MOSAIC24                   3598
#define VDX_MASK_COLOR_ON24                 3599
#define VDX_MASK_COLOR_OFF24                3600
#define VDX_MASK_X_POS24                    3601
#define VDX_MASK_Y_POS24                    3602
#define VDX_MASK_WIDTH24                    3603
#define VDX_MASK_HEIGHT24                   3604
#define VDX_MASK_PAN_ANGLE24                3605
#define VDX_MASK_TILT_ANGLE24               3606
#define VDX_MASK_ZOOM24                     3607
#define VDX_MASK_ON25                       3608
#define VDX_MASK_DISP_ON25                  3609
#define VDX_MASK_I25                        3610
#define VDX_MASK_TRANS25                    3611
#define VDX_MASK_MOSAIC25                   3612
#define VDX_MASK_COLOR_ON25                 3613
#define VDX_MASK_COLOR_OFF25                3614
#define VDX_MASK_X_POS25                    3615
#define VDX_MASK_Y_POS25                    3616
#define VDX_MASK_WIDTH25                    3617
#define VDX_MASK_HEIGHT25                   3618
#define VDX_MASK_PAN_ANGLE25                3619
#define VDX_MASK_TILT_ANGLE25               3620
#define VDX_MASK_ZOOM25                     3621
#define VDX_MASK_ON26                       3622
#define VDX_MASK_DISP_ON26                  3623
#define VDX_MASK_I26                        3624
#define VDX_MASK_TRANS26                    3625
#define VDX_MASK_MOSAIC26                   3626
#define VDX_MASK_COLOR_ON26                 3627
#define VDX_MASK_COLOR_OFF26                3628
#define VDX_MASK_X_POS26                    3629
#define VDX_MASK_Y_POS26                    3630
#define VDX_MASK_WIDTH26                    3631
#define VDX_MASK_HEIGHT26                   3632
#define VDX_MASK_PAN_ANGLE26                3633
#define VDX_MASK_TILT_ANGLE26               3634
#define VDX_MASK_ZOOM26                     3635
#define VDX_MASK_ON27                       3636
#define VDX_MASK_DISP_ON27                  3637
#define VDX_MASK_I27                        3638
#define VDX_MASK_TRANS27                    3639
#define VDX_MASK_MOSAIC27                   3640
#define VDX_MASK_COLOR_ON27                 3641
#define VDX_MASK_COLOR_OFF27                3642
#define VDX_MASK_X_POS27                    3643
#define VDX_MASK_Y_POS27                    3644
#define VDX_MASK_WIDTH27                    3645
#define VDX_MASK_HEIGHT27                   3646
#define VDX_MASK_PAN_ANGLE27                3647
#define VDX_MASK_TILT_ANGLE27               3648
#define VDX_MASK_ZOOM27                     3649
#define VDX_MASK_ON28                       3650
#define VDX_MASK_DISP_ON28                  3651
#define VDX_MASK_I28                        3652
#define VDX_MASK_TRANS28                    3653
#define VDX_MASK_MOSAIC28                   3654
#define VDX_MASK_COLOR_ON28                 3655
#define VDX_MASK_COLOR_OFF28                3656
#define VDX_MASK_X_POS28                    3657
#define VDX_MASK_Y_POS28                    3658
#define VDX_MASK_WIDTH28                    3659
#define VDX_MASK_HEIGHT28                   3660
#define VDX_MASK_PAN_ANGLE28                3661
#define VDX_MASK_TILT_ANGLE28               3662
#define VDX_MASK_ZOOM28                     3663
#define VDX_CAM_ID_H                        3664
#define VDX_CAM_ID_L                        3665
#define VDX_MD_ON                           3666
#define VDX_MD_DISP                         3667
#define VDX_MD_FRAME                        3668
#define VDX_MD_THRS_VAL                     3669
#define VDX_MD_INTERVAL_TIME                3670
#define VDX_MD_SRT_H_POS1                   3671
#define VDX_MD_SRT_V_POS1                   3672
#define VDX_MD_END_H_POS1                   3673
#define VDX_MD_END_V_POS1                   3674
#define VDX_MD_SRT_H_POS2                   3675
#define VDX_MD_SRT_V_POS2                   3676
#define VDX_MD_STP_H_POS2                   3677
#define VDX_MD_STP_V_POS2                   3678
#define VDX_MD_SRT_H_POS3                   3679
#define VDX_MD_SRT_V_POS3                   3680
#define VDX_MD_STP_H_POS3                   3681
#define VDX_MD_STP_V_POS3                   3682
#define VDX_MD_SRT_H_POS4                   3683
#define VDX_MD_SRT_V_POS4                   3684
#define VDX_MD_STP_H_POS4                   3685
#define VDX_MD_STP_V_POS4                   3686
#define VDX_CZP_ON                          3687
#define VDX_CZP_INTERVAL_TIME               3688
#define VDX_CFP_ON                          3689
#define VDX_CFP_INTERVAL_TIME               3690
#define VDX_CE_ON                           3691

//EV-7100 , EV-7500
#define VDX_CE_THRS_VAL                     3692
#define VDX_CE_Y_HI                         3693
#define VDX_CE_CR_HI                        3694
#define VDX_CE_CB_HI                        3695
#define VDX_CE_Y_LI                         3696

//EH6300
#define VDX_CE_THRS_HIGH                    3692
#define VDX_CE_THRS_MID						3693
#define VDX_CE_THRS_LOW	                    3694
#define VDX_CE_COLOR_HIGH                   3695
#define VDX_CE_COLOR_LOW                    3696

#define VDX_CE_CR_LI                        3697
#define VDX_CE_CB_LI                        3698
#define VDX_CS_LEVEL                        3699
#define VDX_CS_SET_VAL                      3700
#define VDX_COLOR_GAIN                      3701
#define VDX_COLOR_HUE                       3702
#define VDX_GAM_OFFSET                      3703
#define VDX_GAM_OFFSET_S                    3704
#define VDX_EX_EXPCOMP_RESET                3705
#define VDX_EX_EXPCOMP_DIRECT               3706
#define VDX_EX_EXPAP_RESET                  3707
#define VDX_EX_EXPAP_DIRECT                 3708
#define VDX_EX_AICR_ON2OFF                  3709
#define VDX_EX_AICR_OFF2ON                  3710
#define VDX_EX_COLOR_GAIN                   3711
#define VDX_EX_COLOR_HUE                    3712
#define VDX_ZOOM_POS01                      3713
#define VDX_DZOOM_ON01                      3714
#define VDX_F_MODE01                        3715
#define VDX_AF_MODE01                       3716
#define VDX_COMP_ON01                       3717
#define VDX_BLC_ON01                        3718
#define VDX_ASS_ON01                        3719
#define VDX_FOCUS_POS01                     3720
#define VDX_SHUTTER_STEP01                  3721
#define VDX_BRIGHT_STEP01                   3722
#define VDX_IRIS_STEP01                     3723
#define VDX_GAIN_STEP01                     3724
#define VDX_EXP_COMP_VAL01                  3725
#define VDX_WB_MODE01                       3726
#define VDX_ICR_ON01                        3727
#define VDX_WD_MODE01                       3728
#define VDX_DEFOG_ON01                      3729
#define VDX_R_GAIN01                        3730
#define VDX_B_GAIN01                        3731
#define VDX_APER_GAIN01                     3732
#define VDX_WD_BRT_L01                      3733
#define VDX_WD_BRT_COMP01                   3734
#define VDX_WD_COMP_L01						3735
#define VDX_AE_MODE01                       3736
#define VDX_ZOOM_POS02                      3737
#define VDX_DZOOM_ON02                      3738
#define VDX_F_MODE02                        3739
#define VDX_AF_MODE02                       3740
#define VDX_COMP_ON02                       3741
#define VDX_BLC_ON02                        3742
#define VDX_ASS_ON02                        3743
#define VDX_FOCUS_POS02                     3744
#define VDX_SHUTTER_STEP02                  3745
#define VDX_BRIGHT_STEP02                   3746
#define VDX_IRIS_STEP02                     3747
#define VDX_GAIN_STEP02                     3748
#define VDX_EXP_COMP_VAL02                  3749
#define VDX_WB_MODE02                       3750
#define VDX_ICR_ON02                        3751
#define VDX_WD_MODE02                       3752
#define VDX_DEFOG_ON02                      3753
#define VDX_R_GAIN02                        3754
#define VDX_B_GAIN02                        3755
#define VDX_APER_GAIN02                     3756
#define VDX_WD_BRT_L02                      3757
#define VDX_WD_BRT_COMP02                   3758
#define VDX_WD_COMP_L02                     3759
#define VDX_AE_MODE02                       3760
#define VDX_ZOOM_POS03                      3761
#define VDX_DZOOM_ON03                      3762
#define VDX_F_MODE03                        3763
#define VDX_AF_MODE03                       3764
#define VDX_COMP_ON03                       3765
#define VDX_BLC_ON03                        3766
#define VDX_ASS_ON03                        3767
#define VDX_FOCUS_POS03                     3768
#define VDX_SHUTTER_STEP03                  3769
#define VDX_BRIGHT_STEP03                   3770
#define VDX_IRIS_STEP03                     3771
#define VDX_GAIN_STEP03                     3772
#define VDX_EXP_COMP_VAL03                  3773
#define VDX_WB_MODE03                       3774
#define VDX_ICR_ON03                        3775
#define VDX_WD_MODE03                       3776
#define VDX_DEFOG_ON03                      3777
#define VDX_R_GAIN03                        3778
#define VDX_B_GAIN03                        3779
#define VDX_APER_GAIN03                     3780
#define VDX_WD_BRT_L03                      3781
#define VDX_WD_BRT_COMP03                   3782
#define VDX_WD_COMP_L03	                    3783
#define VDX_AE_MODE03		                3784
#define VDX_ZOOM_POS04                      3785
#define VDX_DZOOM_ON04                      3786
#define VDX_F_MODE04                        3787
#define VDX_AF_MODE04                       3788
#define VDX_COMP_ON04                       3789
#define VDX_BLC_ON04                        3790
#define VDX_ASS_ON04                        3791
#define VDX_FOCUS_POS04                     3792
#define VDX_SHUTTER_STEP04                  3793
#define VDX_BRIGHT_STEP04                   3794
#define VDX_IRIS_STEP04                     3795
#define VDX_GAIN_STEP04                     3796
#define VDX_EXP_COMP_VAL04                  3797
#define VDX_WB_MODE04                       3798
#define VDX_ICR_ON04                        3799
#define VDX_WD_MODE04                       3800
#define VDX_DEFOG_ON04                      3801
#define VDX_R_GAIN04                        3802
#define VDX_B_GAIN04                        3803
#define VDX_APER_GAIN04                     3804
#define VDX_WD_BRT_L04                      3805
#define VDX_WD_BRT_COMP04                   3806
#define VDX_WD_COMP_L04                     3807
#define VDX_AE_MODE04	                    3808
#define VDX_ZOOM_POS05                      3809
#define VDX_DZOOM_ON05                      3810
#define VDX_F_MODE05                        3811
#define VDX_AF_MODE05                       3812
#define VDX_COMP_ON05                       3813
#define VDX_BLC_ON05                        3814
#define VDX_ASS_ON05                        3815
#define VDX_FOCUS_POS05                     3816
#define VDX_SHUTTER_STEP05                  3817
#define VDX_BRIGHT_STEP05                   3818
#define VDX_IRIS_STEP05                     3819
#define VDX_GAIN_STEP05                     3820
#define VDX_EXP_COMP_VAL05                  3821
#define VDX_WB_MODE05                       3822
#define VDX_ICR_ON05                        3823
#define VDX_WD_MODE05                       3824
#define VDX_DEFOG_ON05                      3825
#define VDX_R_GAIN05                        3826
#define VDX_B_GAIN05                        3827
#define VDX_APER_GAIN05                     3828
#define VDX_WD_BRT_L05                      3829
#define VDX_WD_BRT_COMP05                   3830
#define VDX_WD_COMP_L05                     3831
#define VDX_AE_MODE05	                    3832
#define VDX_ZOOM_POS06                      3833
#define VDX_DZOOM_ON06                      3834
#define VDX_F_MODE06                        3835
#define VDX_AF_MODE06                       3836
#define VDX_COMP_ON06                       3837
#define VDX_BLC_ON06                        3838
#define VDX_ASS_ON06                        3839
#define VDX_FOCUS_POS06                     3840
#define VDX_SHUTTER_STEP06                  3841
#define VDX_BRIGHT_STEP06                   3842
#define VDX_IRIS_STEP06                     3843
#define VDX_GAIN_STEP06                     3844
#define VDX_EXP_COMP_VAL06                  3845
#define VDX_WB_MODE06                       3846
#define VDX_ICR_ON06                        3847
#define VDX_WD_MODE06                       3848
#define VDX_DEFOG_ON06                      3849
#define VDX_R_GAIN06                        3850
#define VDX_B_GAIN06                        3851
#define VDX_APER_GAIN06                     3852
#define VDX_WD_BRT_L06                      3853
#define VDX_WD_BRT_COMP06                   3854
#define VDX_WD_COMP_L06                     3855
#define VDX_AE_MODE06                       3856
#define VDX_ZOOM_POS07                      3857
#define VDX_DZOOM_ON07                      3858
#define VDX_F_MODE07                        3859
#define VDX_AF_MODE07                       3860
#define VDX_COMP_ON07                       3861
#define VDX_BLC_ON07                        3862
#define VDX_ASS_ON07                        3863
#define VDX_FOCUS_POS07                     3864
#define VDX_SHUTTER_STEP07                  3865
#define VDX_BRIGHT_STEP07                   3866
#define VDX_IRIS_STEP07                     3867
#define VDX_GAIN_STEP07                     3868
#define VDX_EXP_COMP_VAL07                  3869
#define VDX_WB_MODE07                       3870
#define VDX_ICR_ON07                        3871
#define VDX_WD_MODE07                       3872
#define VDX_DEFOG_ON07                      3873
#define VDX_R_GAIN07                        3874
#define VDX_B_GAIN07                        3875
#define VDX_APER_GAIN07                     3876
#define VDX_WD_BRT_L07                      3877
#define VDX_WD_BRT_COMP07                   3878
#define VDX_WD_COMP_L07                     3879
#define VDX_AE_MODE07	                    3880
#define VDX_ZOOM_POS08                      3881
#define VDX_DZOOM_ON08                      3882
#define VDX_F_MODE08                        3883
#define VDX_AF_MODE08                       3884
#define VDX_COMP_ON08                       3885
#define VDX_BLC_ON08                        3886
#define VDX_ASS_ON08                        3887
#define VDX_FOCUS_POS08                     3888
#define VDX_SHUTTER_STEP08                  3889
#define VDX_BRIGHT_STEP08                   3890
#define VDX_IRIS_STEP08                     3891
#define VDX_GAIN_STEP08                     3892
#define VDX_EXP_COMP_VAL08                  3893
#define VDX_WB_MODE08                       3894
#define VDX_ICR_ON08                        3895
#define VDX_WD_MODE08                       3896
#define VDX_DEFOG_ON08                      3897
#define VDX_R_GAIN08                        3898
#define VDX_B_GAIN08                        3899
#define VDX_APER_GAIN08                     3900
#define VDX_WD_BRT_L08                      3901
#define VDX_WD_BRT_COMP08                   3902
#define VDX_WD_COMP_L08                     3903
#define VDX_AE_MODE08	                    3904
#define VDX_ZOOM_POS09                      3905
#define VDX_DZOOM_ON09                      3906
#define VDX_F_MODE09                        3907
#define VDX_AF_MODE09                       3908
#define VDX_COMP_ON09                       3909
#define VDX_BLC_ON09                        3910
#define VDX_ASS_ON09                        3911
#define VDX_FOCUS_POS09                     3912
#define VDX_SHUTTER_STEP09                  3913
#define VDX_BRIGHT_STEP09                   3914
#define VDX_IRIS_STEP09                     3915
#define VDX_GAIN_STEP09                     3916
#define VDX_EXP_COMP_VAL09                  3917
#define VDX_WB_MODE09                       3918
#define VDX_ICR_ON09                        3919
#define VDX_WD_MODE09                       3920
#define VDX_DEFOG_ON09                      3921
#define VDX_R_GAIN09                        3922
#define VDX_B_GAIN09                        3923
#define VDX_APER_GAIN09                     3924
#define VDX_WD_BRT_L09                      3925
#define VDX_WD_BRT_COMP09                   3926
#define VDX_WD_COMP_L09                     3927
#define VDX_AE_MODE09	                    3928
#define VDX_ZOOM_POS10                      3929
#define VDX_DZOOM_ON10                      3930
#define VDX_F_MODE10                        3931
#define VDX_AF_MODE10                       3932
#define VDX_COMP_ON10                       3933
#define VDX_BLC_ON10                        3934
#define VDX_ASS_ON10                        3935
#define VDX_FOCUS_POS10                     3936
#define VDX_SHUTTER_STEP10                  3937
#define VDX_BRIGHT_STEP10                   3938
#define VDX_IRIS_STEP10                     3939
#define VDX_GAIN_STEP10                     3940
#define VDX_EXP_COMP_VAL10                  3941
#define VDX_WB_MODE10                       3942
#define VDX_ICR_ON10                        3943
#define VDX_WD_MODE10                       3944
#define VDX_DEFOG_ON10                      3945
#define VDX_R_GAIN10                        3946
#define VDX_B_GAIN10                        3947
#define VDX_APER_GAIN10                     3948
#define VDX_WD_BRT_L10                      3949
#define VDX_WD_BRT_COMP10                   3950
#define VDX_WD_COMP_L10                     3951
#define VDX_AE_MODE10	                    3952
#define VDX_ZOOM_POS11                      3953
#define VDX_DZOOM_ON11                      3954
#define VDX_F_MODE11                        3955
#define VDX_AF_MODE11                       3956
#define VDX_COMP_ON11                       3957
#define VDX_BLC_ON11                        3958
#define VDX_ASS_ON11                        3959
#define VDX_FOCUS_POS11                     3960
#define VDX_SHUTTER_STEP11                  3961
#define VDX_BRIGHT_STEP11                   3962
#define VDX_IRIS_STEP11                     3963
#define VDX_GAIN_STEP11                     3964
#define VDX_EXP_COMP_VAL11                  3965
#define VDX_WB_MODE11                       3966
#define VDX_ICR_ON11                        3967
#define VDX_WD_MODE11                       3968
#define VDX_DEFOG_ON11                      3969
#define VDX_R_GAIN11                        3970
#define VDX_B_GAIN11                        3971
#define VDX_APER_GAIN11                     3972
#define VDX_WD_BRT_L11                      3973
#define VDX_WD_BRT_COMP11                   3974
#define VDX_WD_COMP_L11                     3975
#define VDX_AE_MODE11	                    3976
#define VDX_ZOOM_POS12                      3977
#define VDX_DZOOM_ON12                      3978
#define VDX_F_MODE12                        3979
#define VDX_AF_MODE12                       3980
#define VDX_COMP_ON12                       3981
#define VDX_BLC_ON12                        3982
#define VDX_ASS_ON12                        3983
#define VDX_FOCUS_POS12                     3984
#define VDX_SHUTTER_STEP12                  3985
#define VDX_BRIGHT_STEP12                   3986
#define VDX_IRIS_STEP12                     3987
#define VDX_GAIN_STEP12                     3988
#define VDX_EXP_COMP_VAL12                  3989
#define VDX_WB_MODE12                       3990
#define VDX_ICR_ON12                        3991
#define VDX_WD_MODE12                       3992
#define VDX_DEFOG_ON12                      3993
#define VDX_R_GAIN12                        3994
#define VDX_B_GAIN12                        3995
#define VDX_APER_GAIN12                     3996
#define VDX_WD_BRT_L12                      3997
#define VDX_WD_BRT_COMP12                   3998
#define VDX_WD_COMP_L12                     3999
#define VDX_AE_MODE12	                    4000
#define VDX_ZOOM_POS13                      4001
#define VDX_DZOOM_ON13                      4002
#define VDX_F_MODE13                        4003
#define VDX_AF_MODE13                       4004
#define VDX_COMP_ON13                       4005
#define VDX_BLC_ON13                        4006
#define VDX_ASS_ON13                        4007
#define VDX_FOCUS_POS13                     4008
#define VDX_SHUTTER_STEP13                  4009
#define VDX_BRIGHT_STEP13                   4010
#define VDX_IRIS_STEP13                     4011
#define VDX_GAIN_STEP13                     4012
#define VDX_EXP_COMP_VAL13                  4013
#define VDX_WB_MODE13                       4014
#define VDX_ICR_ON13                        4015
#define VDX_WD_MODE13                       4016
#define VDX_DEFOG_ON13                      4017
#define VDX_R_GAIN13                        4018
#define VDX_B_GAIN13                        4019
#define VDX_APER_GAIN13                     4020
#define VDX_WD_BRT_L13                      4021
#define VDX_WD_BRT_COMP13                   4022
#define VDX_WD_COMP_L13                     4023
#define VDX_AE_MODE13	                    4024
#define VDX_ZOOM_POS14                      4025
#define VDX_DZOOM_ON14                      4026
#define VDX_F_MODE14                        4027
#define VDX_AF_MODE14                       4028
#define VDX_COMP_ON14                       4029
#define VDX_BLC_ON14                        4030
#define VDX_ASS_ON14                        4031
#define VDX_FOCUS_POS14                     4032
#define VDX_SHUTTER_STEP14                  4033
#define VDX_BRIGHT_STEP14                   4034
#define VDX_IRIS_STEP14                     4035
#define VDX_GAIN_STEP14                     4036
#define VDX_EXP_COMP_VAL14                  4037
#define VDX_WB_MODE14                       4038
#define VDX_ICR_ON14                        4039
#define VDX_WD_MODE14                       4040
#define VDX_DEFOG_ON14                      4041
#define VDX_R_GAIN14                        4042
#define VDX_B_GAIN14                        4043
#define VDX_APER_GAIN14                     4044
#define VDX_WD_BRT_L14                      4045
#define VDX_WD_BRT_COMP14                   4046
#define VDX_WD_COMP_L14                     4047
#define VDX_AE_MODE14	                    4048
#define VDX_ZOOM_POS15                      4049
#define VDX_DZOOM_ON15                      4050
#define VDX_F_MODE15                        4051
#define VDX_AF_MODE15                       4052
#define VDX_COMP_ON15                       4053
#define VDX_BLC_ON15                        4054
#define VDX_ASS_ON15                        4055
#define VDX_FOCUS_POS15                     4056
#define VDX_SHUTTER_STEP15                  4057
#define VDX_BRIGHT_STEP15                   4058
#define VDX_IRIS_STEP15                     4059
#define VDX_GAIN_STEP15                     4060
#define VDX_EXP_COMP_VAL15                  4061
#define VDX_WB_MODE15                       4062
#define VDX_ICR_ON15                        4063
#define VDX_WD_MODE15                       4064
#define VDX_DEFOG_ON15                      4065
#define VDX_R_GAIN15                        4066
#define VDX_B_GAIN15                        4067
#define VDX_APER_GAIN15                     4068
#define VDX_WD_BRT_L15                      4069
#define VDX_WD_BRT_COMP15                   4070
#define VDX_WD_COMP_L15                     4071
#define VDX_AE_MODE15	                    4072
#define VDX_ZOOM_POS16                      4073
#define VDX_DZOOM_ON16                      4074
#define VDX_F_MODE16                        4075
#define VDX_AF_MODE16                       4076
#define VDX_COMP_ON16                       4077
#define VDX_BLC_ON16                        4078
#define VDX_ASS_ON16                        4079
#define VDX_FOCUS_POS16                     4080
#define VDX_SHUTTER_STEP16                  4081
#define VDX_BRIGHT_STEP16                   4082
#define VDX_IRIS_STEP16                     4083
#define VDX_GAIN_STEP16                     4084
#define VDX_EXP_COMP_VAL16                  4085
#define VDX_WB_MODE16                       4086
#define VDX_ICR_ON16                        4087
#define VDX_WD_MODE16                       4088
#define VDX_DEFOG_ON16                      4089
#define VDX_R_GAIN16                        4090
#define VDX_B_GAIN16                        4091
#define VDX_APER_GAIN16                     4092
#define VDX_WD_BRT_L16                      4093
#define VDX_WD_BRT_COMP16                   4094
#define VDX_WD_COMP_L16                     4095
#define VDX_AE_MODE16	                    4096
#define VDX_COMM_BAUDRATE                   4097
#define VDX_MONITORING_MODE                 4098
#define VDX_AO_ON                           4099
#define VDX_DO_ON                           4100
#define VDX_LVDS_OUT                        4101
#define VDX_ZWIDE_LIMIT                     4102
#define VDX_ZTELE_LIMIT                     4103
#define VDX_DZ_MAX                          4104
#define VDX_SZOOM_ON                        4105
#define VDX_FTRACE_ON                       4106
#define VDX_FCS_OFFSET_DOME                 4107
#define VDX_EX_EXPC_ON                      4108
#define VDX_EX_EXPAP_ON                     4109
#define VDX_EX_CGCH_ON                      4110
#define VDX_EX_AICR_F2O_ON                  4111
#define VDX_GAIN_LIMIT                      4112	// 20131212 추가
#define VDX_STB_ON                          4113	// 20131212 추가
#define VDX_STB_HOLD                        4114	// 20131212 추가
#define VDX_CAM_USERMEMORYSET01             4115	//
#define VDX_CAM_USERMEMORYSET02             4116	//
#define VDX_CAM_USERMEMORYSET03             4117	//
#define VDX_CAM_USERMEMORYSET04             4118	//
#define VDX_CAM_USERMEMORYSET05             4119	//
#define VDX_CAM_USERMEMORYSET06             4120	//
#define VDX_CAM_USERMEMORYSET07             4121	//
#define VDX_CAM_USERMEMORYSET08             4122	//
#define VDX_CAM_USERMEMORYSET09             4123	//
#define VDX_CAM_USERMEMORYSET10             4124	//
#define VDX_CAM_USERMEMORYSET11             4125	//
#define VDX_CAM_USERMEMORYSET12             4126	//
#define VDX_CAM_USERMEMORYSET13             4127	//
#define VDX_CAM_USERMEMORYSET14             4128	//
#define VDX_CAM_USERMEMORYSET15             4129	//
#define VDX_CAM_USERMEMORYSET16             4130	//
#define VDX_WD_SCR_DISP						4131	//
#define VDX_WD_DET_SENS						4132	//
#define VDX_WD_BUCORR_LV					4133	//
#define VDX_WD_BOCORR_LV					4134	// 20140320 추가
#define VDX_WD_SHORT_EXPR					4135	//
#define VDX_WD_ALARM						4136	//


/* 4501 ~ 4599 is reserved - Special Index for Event*/
#define IDX_OSDON				   4501
#define IDX_OSDOFF				   4502
#define IDX_OSDHIDDENON			   4503
#define IDX_OSDEXITSAVE			   4504
#define IDX_OSDEXITNOTSAVE		   4505
#define IDX_CAMREBOOTSAVE		   4506
#define IDX_CAMREBOOTNOTSAVE	   4507

/* 4508 ~ 4529 is reserved - Special Index for OSD Map*/
#define IDX_NOT_USE				   4508	// *OSD, Protocol
#define IDX_EXIT                   4509	// *OSD
#define IDX_RETURN                 4510	// *OSD
#define IDX_INITIAL                4511	// *OSD
#define IDX_TITLE                  4512	// *OSD
#define IDX_FRESET                 4513	// *OSD
#define IDX_REBOOT                 4514	// *OSD

/* 4531 ~ 4549 is reserved - MD for OSD Map*/
#define IDX_MD_STT				   4531	// *OSD, Motion Detection
#define IDX_MD_ZONE				   4532
#define IDX_MD_STATE               4533
#define IDX_MD_DISP                4534
#define IDX_MD_ALARM               4535
#define IDX_MD_SENS                4536
#define IDX_MD_X                   4537
#define IDX_MD_Y                   4538
#define IDX_MD_W                   4539
#define IDX_MD_H                   4540
#define IDX_MD_END				   4541

/* 4551 ~ 4569 is reserved - Privacy Mask for OSD Map*/
#define IDX_PRI_STT				   4551	// *OSD, Privacy
#define IDX_PRI_ZONE			   4552
#define IDX_PRI_STATE			   4553
#define IDX_PRI_TRANS			   4554
#define IDX_PRI_COLOR			   4555
#define IDX_PRI_MOSAIC			   4556
#define IDX_PRI_X				   4557
#define IDX_PRI_Y				   4558
#define IDX_PRI_W				   4559
#define IDX_PRI_H				   4560
#define IDX_PRI_P			   	   4561
#define IDX_PRI_T			   	   4562
#define IDX_PRI_Z			   	   4563
#define IDX_PRI_END				   4564

/* 4651 ~ 4668 is reserved - Privacy Mask for Visca*/
#define VDX_MASK_STT	    		4651
#define VDX_MASK_ON	    			4652
#define VDX_MASK_DISP    			4653
#define VDX_MASK_I	    			4654
#define VDX_MASK_ZONE	    		4655
#define VDX_MASK_MODIFY	    		4656
#define VDX_MASK_TRANS	    		4657
#define VDX_MASK_MOSAIC	    		4658
#define VDX_MASK_COLOR_ON    		4659
#define VDX_MASK_COLOR_OFF	    	4660
#define VDX_MASK_X_POS	    		4661
#define VDX_MASK_Y_POS	    		4662
#define VDX_MASK_WIDTH	    		4663
#define VDX_MASK_HEIGHT	    		4664
#define VDX_MASK_P		    		4665
#define VDX_MASK_T		    		4666
#define VDX_MASK_Z		    		4667
#define VDX_MASK_END	    		4668

/* 4681 ~ 4689 is reserved - Motion for Visca*/
#define VDX_MD_STT	    			4681
#define VDX_MD_ZONE					4682
#define VDX_MD_SRT_H_POS            4683
#define VDX_MD_SRT_V_POS            4684
#define VDX_MD_STP_H_POS            4685
#define VDX_MD_STP_V_POS            4686
#define VDX_MD_END	    			4687

/*4701 ~ 4799 is reserved - for VISCA */
#define VDX_TITLE_STT                      4701
#define VDX_TITLE_H_POS                    4702
#define VDX_TITLE_ON                       4703
#define VDX_TITLE_LINE                     4704
#define VDX_TITLE_BLINK                    4705
#define VDX_TITLE_COLOR                    4706
#define VDX_TITLE_LINE_CH1                 4707
#define VDX_TITLE_LINE_CH2                 4708
#define VDX_TITLE_LINE_CH3                 4709
#define VDX_TITLE_LINE_CH4                 4710
#define VDX_TITLE_LINE_CH5                 4711
#define VDX_TITLE_LINE_CH6                 4712
#define VDX_TITLE_LINE_CH7                 4713
#define VDX_TITLE_LINE_CH8                 4714
#define VDX_TITLE_LINE_CH9                 4715
#define VDX_TITLE_LINE_CH10                4716
#define VDX_TITLE_LINE_CH11                4717
#define VDX_TITLE_LINE_CH12                4718
#define VDX_TITLE_LINE_CH13                4719
#define VDX_TITLE_LINE_CH14                4720
#define VDX_TITLE_LINE_CH15                4721
#define VDX_TITLE_LINE_CH16                4722
#define VDX_TITLE_LINE_CH17                4723
#define VDX_TITLE_LINE_CH18                4724
#define VDX_TITLE_LINE_CH19                4725
#define VDX_TITLE_LINE_CH20                4726
#define VDX_TITLE_END                      4727

/*4751 ~ 4766  is reserved - send envnt for any act */
#define VDX_MOVE_RGAIN				4751
#define VDX_MOVE_BGAIN				4752
#define VDX_MOVE_DZOOM    			4753
#define VDX_MOVE_ZOOM     			4754
#define VDX_MOVE_FOCUS    			4755
#define VDX_MOVE_SHUT     			4756
#define VDX_MOVE_IRIS     			4757
#define VDX_MOVE_GAIN     			4758
#define VDX_MOVE_BRIGHT   			4759
#define VDX_MOVE_EXPCOMP  			4760
#define VDX_MOVE_APERTURE  			4761
#define VDX_PUSH_WB       			4762
#define VDX_INIT_CAM				4763
#define VDX_CAM_MEMCUS				4764
#define VDX_FCS_PUSH				4765
#define VDX_TITLE_SET				4766

/*4781 ~ 4783  is reserved - Version inq */
#define VDX_MODEL_CODE				4781
#define VDX_ROM_VERSION				4782
#define VDX_SOCKET_NUM				4783

/*4784 ~ 4786  is reserved - 내부변수 참조 */
#define VDX_CAM_PAN					4784	//구조체에 없음,if_mw에 지역변수로 할당됨
#define VDX_CAM_TILT				4785	//구조체에 없음,if_mw에 지역변수로 할당됨
#define VDX_TEMPERATURE				4786	//Temp

/*4791 ~ 4898  is reserved - Variable set */
#define VDX_VSC_REG_ADDR			4791
#define VDX_VSC_REG_DAT				4792
#define VDX_MEM_SAVE_ADDR			4793
#define VDX_MEM_SAVE_DAT			4794
#define VDX_EXTEND					4795
#define VDX_REGITER_SET				4796
#define VDX_RECIEVE_DATA			4797
#define VDX_ZM_FCS_POS				4798

/*4801 ~ 4809  is reserved - block inquiry */
#define VDX_CAM_ACTIV				4801
#define VDX_TITLE_DISP				4802
#define VDX_PRI_ON					4803
#define VDX_MEM_PROVIDED			4804
#define VDX_ICR_PROVIDED			4805
#define VDX_SYS_PROVIDED			4806
#define VDX_EFLP_PROVIDED			4807
#define VDX_AMASK_PROVIDED			4808
#define VDX_STAB_PROVIDED			4809
#define VDX_LOW_CONT_DETECTED		4810

/*4821 ~ 4826  is reserved - Socket Control */
#define VDX_FOCUS_COMMAND			4821
#define VDX_ZOOM_COMMAND			4822
#define VDX_ZMFCS_COMMAND			4823
#define VDX_CAMERA_SET				4824
#define VDX_CAMERA_RESET			4825
#define VDX_CAMERA_RECALL			4826

/*4901 ~ 49xx  is reserved - CNBH Protocol */
#define CHDX_DSP_REG_READ			4901
#define CHDX_DSP_REG_WRITE			4902
#define CHDX_EEPROM_READ			4903
#define CHDX_EEPROM_WRITE			4904
#define CHDX_MOTOR_DRV_ACCESS		4905	//AD41908
#define CHDX_VIDEO_ENC_ACCESS		4906	//AD7393
#define CHDX_SENSOR_IC_ACCESS		4907	//MN34041
#define CHDX_FREE_BUF_READ			4908
#define CHDX_STATISTICS_DAT_READ	4909
#define CHDX_AUTO_ADJ				4910
#define CHDX_ALGORISM_RUN			4911
#define CHDX_VIDEO_ENC_ACCESS2		4912	//MDIN325
#define CHDX_SKIP_EEP_WRITE			4913

/* 사용자 EEPRom 데이터 제공을 위한 인덱스 시작 값 */
#define IDX_USER                   5000

/************************************************************************************************************/
/* OSD */
/* OSD_KeyProc 에서 사용하는 Key 값 */
typedef enum _OSD_KEY {
	OSD_KEYNULL		= 0,
	OSD_CKEYUP		= 0x1,
	OSD_CKEYDOWN	= 0x2,
	OSD_LKEYUP		= 0x4,
	OSD_LKEYDOWN	= 0x8,
	OSD_RKEYUP		= 0x10,
	OSD_RKEYDOWN	= 0x20,
	OSD_UKEYUP		= 0x40,
	OSD_UKEYDOWN	= 0x80,
	OSD_DKEYUP		= 0x100,
	OSD_DKEYDOWN	= 0x200,
} OSD_KEY;

/* 현재 OSD 상태 */
typedef enum _OSD_STATE {
	OSD_STATEOFF,
	OSD_STATEON,
	OSD_STATEHIDDEN,
} OSD_STATE;

typedef enum _OSD_MODE {
	OSD_NORMAL,
	OSD_TITLE,
	OSD_TITLE_DISP,
	OSD_ID_DISP,
	OSD_HIDE,
} OSD_MODE;

/* OSD Font에 대한 인덱스 - !! 절대 순서가 바뀌면 안됨 !! */
typedef enum _OSD_STR {
	OSD_STR_NULL,					    // "" 아무것도 출력하지 않음*/
	OSD_STR_0_30,                       // "0_30"
	OSD_STR_0_35,                       // "0_35"
	OSD_STR_0_40,                       // "0_40"
	OSD_STR_0_45,                       // "0_45"
	OSD_STR_0_50,                       // "0_50"
	OSD_STR_0_55,                       // "0_55"
	OSD_STR_0_60,                       // "0_60"
	OSD_STR_0_65,                       // "0_65"
	OSD_STR_0_70,                       // "0_70"
	OSD_STR_0_75,                       // "0_75"
	OSD_STR_0_80,                       // "0_80"
	OSD_STR_0_85,                       // "0_85"
	OSD_STR_100PER,                     // "100PER"
	OSD_STR_1080_25P,                   // "1080_25P"
	OSD_STR_1080_30P,                   // "1080_30P"
	OSD_STR_1080_50I,                   // "1080_50I"
	OSD_STR_1080_50P,                   // "1080_50P"
	OSD_STR_1080_60I,                   // "1080_60I"
	OSD_STR_1080_60P,                   // "1080_60P"
	OSD_STR_10CM,                       // "10CM"
	OSD_STR_10MIN,                      // "10MIN"
	OSD_STR_10SEC,                      // "10SEC"
	OSD_STR_115200,                     // "115200"
	OSD_STR_11M,                        // "11M"
	OSD_STR_19200,                      // "19200"
	OSD_STR_1CM,                        // "1CM"
	OSD_STR_1M,                         // "1M"
	OSD_STR_1SEC,                       // "1SEC"
	OSD_STR_1_1,                        // "1_1"
	OSD_STR_1_100,                      // "1_100"
	OSD_STR_1_1000,                     // "1_1000"
	OSD_STR_1_10000,                    // "1_10000"
	OSD_STR_1_12,                       // "1_12"
	OSD_STR_1_120,                      // "1_120"
	OSD_STR_1_125,                      // "1_125"
	OSD_STR_1_1250,                     // "1_1250"
	OSD_STR_1_15,                       // "1_15"
	OSD_STR_1_150,                      // "1_150"
	OSD_STR_1_1500,                     // "1_1500"
	OSD_STR_1_1600,                     // "1_1600"
	OSD_STR_1_1750,                     // "1_1750"
	OSD_STR_1_180,                      // "1_180"
	OSD_STR_1_2,                        // "1_2"
	OSD_STR_1_200,                      // "1_200"
	OSD_STR_1_2000,                     // "1_2000"
	OSD_STR_1_20000,                    // "1_20000	"
	OSD_STR_1_215,                      // "1_215"
	OSD_STR_1_23M,                      // "1_23M"
	OSD_STR_1_240,                      // "1_240"
	OSD_STR_1_25,                       // "1_25"
	OSD_STR_1_250,                      // "1_250"
	OSD_STR_1_2500,                     // "1_2500"
	OSD_STR_1_3,                        // "1_3"
	OSD_STR_1_30,                       // "1_30"
	OSD_STR_1_300,                      // "1_300"
	OSD_STR_1_3000,                     // "1_3000"
	OSD_STR_1_3200,                     // "1_3200"
	OSD_STR_1_350,                      // "1_350"
	OSD_STR_1_3500,                     // "1_3500"
	OSD_STR_1_4,                        // "1_4"
	OSD_STR_1_400,                      // "1_400"
	OSD_STR_1_4000,                     // "1_4000"
	OSD_STR_1_40000,                    // "1_40000"
	OSD_STR_1_425,                      // "1_425"
	OSD_STR_1_480,                      // "1_480"
	OSD_STR_1_50,                       // "1_50"
	OSD_STR_1_500,                      // "1_500"
	OSD_STR_1_5M,                       // "1_5M"
	OSD_STR_1_6,                        // "1_6"
	OSD_STR_1_60,                       // "1_60"
	OSD_STR_1_600,                      // "1_600"
	OSD_STR_1_6000,                     // "1_6000"
	OSD_STR_1_6400,                     // "1_6400"
	OSD_STR_1_725,                      // "1_725"
	OSD_STR_1_75,                       // "1_75"
	OSD_STR_1_8,                        // "1_8"
	OSD_STR_1_800,                      // "1_800"
	OSD_STR_1_8000,                     // "1_8000"
	OSD_STR_1_80000,                    // "1_80000"
	OSD_STR_1_85M,                      // "1_85M"
	OSD_STR_1_90,                       // "1_90"
	OSD_STR_1_960,                      // "1_960"
	OSD_STR_20SEC,                      // "20SEC"
	OSD_STR_2400,                       // "2400"
	OSD_STR_25M,                        // "25M"
	OSD_STR_25PER,                      // "25PER"
	OSD_STR_2M,                         // "2M"
	OSD_STR_30CM,                       // "30CM"
	OSD_STR_30SEC,                      // "30SEC"
	OSD_STR_38400,                      // "38400"
	OSD_STR_3M,                         // "3M"
	OSD_STR_4800,                       // "4800"
	OSD_STR_50CM,                       // "50CM"
	OSD_STR_50PER,                      // "50PER"
	OSD_STR_57600,                      // "57600"
	OSD_STR_5M,                         // "5M"
	OSD_STR_5SEC,                       // "5SEC"
	OSD_STR_60SEC,                      // "60SEC"
	OSD_STR_720_50P,                    // "720_50P"
	OSD_STR_720_60P,                    // "720_60P"
	OSD_STR_75PER,                      // "75PER"
	OSD_STR_7M,                         // "7M"
	OSD_STR_8CM,                        // "8CM"
	OSD_STR_9600,                       // "9600"
	OSD_STR_ACE,                        // "ACE"
	OSD_STR_ADJUST,                     // "ADJUST"
	OSD_STR_ADJUST_AE_AF,               // "ADJUST_AE_AF"
	OSD_STR_ADJUST_AF_AE,               // "ADJUST_AF_AE"
	OSD_STR_ADJUST_COLOR,               // "ADJUST_COLOR"
	OSD_STR_AE_MODE,                    // "AE_MODE"
	OSD_STR_AE_RESPONSE_SPEED,          // "AE_RESPONSE_SPEED"
	OSD_STR_AE_SPOT_MODE,               // "AE_SPOT_MODE"
	OSD_STR_AE_SPOT_X,                  // "AE_SPOT_X"
	OSD_STR_AE_SPOT_Y,                  // "AE_SPOT_Y"
	OSD_STR_AFLK,                       // "AFLK"
	OSD_STR_AF_MODE,                    // "AF_MODE"
	OSD_STR_AF_SENS,                    // "AF_SENS"
	OSD_STR_AGC_LIMIT,                  // "AGC_LIMIT"
	OSD_STR_AGING,                      // "AGING"
	OSD_STR_ALARM,                      // "ALARM"
	OSD_STR_ALL_ON,                     // "ALL_ON"
	OSD_STR_ANTI_ROLLING,               // "ANTI_ROLLING"
	OSD_STR_ATW,                        // "ATW"
	OSD_STR_AUTO,                       // "AUTO"
	OSD_STR_AUTO_PUSH,                  // "AUTO_PUSH"
	OSD_STR_AUX_OUT,                    // "AUX_OUT"
	OSD_STR_AWB,                        // "AWB"
	OSD_STR_BACKLIGHT,                  // "BACKLIGHT"
	OSD_STR_BAUDRATE,                   // "BAUDRATE"
	OSD_STR_BLACK,                      // "BLACK"
	OSD_STR_BLC,                        // "BLC"
	OSD_STR_BLUE,                       // "BLUE"
	OSD_STR_BLUE_GAIN,                  // "BLUE_GAIN"
	OSD_STR_BRIGHT,                     // "BRIGHT"
	OSD_STR_BRIGHTNESS,                 // "BRIGHTNESS"
	OSD_STR_BURST,                      // "BURST"
	OSD_STR_B_GAIN_N,                   // "B_GAIN_N"
	OSD_STR_B_GAIN_P,                   // "B_GAIN_P"
	OSD_STR_B_HUE_N,                    // "B_HUE_N"
	OSD_STR_B_HUE_P,                    // "B_HUE_P"
	OSD_STR_B_W,                        // "B_W"
	OSD_STR_CAMCLASS,                   // "CAMCLASS"
	OSD_STR_CAMERA_ID,                  // "CAMERA_ID"
	OSD_STR_CAMERA_TITLE,               // "CAMERA_TITLE"
	OSD_STR_CBCR_SWAP,                  // "CBCR_SWAP"
	OSD_STR_CDS,                        // "CDS"
	OSD_STR_CHANGE_LEVEL,               // "CHANGE_LEVEL"
	OSD_STR_CHANGE_TEXT,                // "CHANGE_TEXT"
	OSD_STR_CHROMA,                     // "CHROMA"
	OSD_STR_CNB_H,                      // "CNB_H"
	OSD_STR_COLOR,                      // "COLOR"
	OSD_STR_COLORBAR,                   // "COLORBAR"
	OSD_STR_COLOR_BAR,                  // "COLOR_BAR"
	OSD_STR_COLOR_TEMP,                 // "COLOR_TEMP"
	OSD_STR_COMBINE,                    // "COMBINE"
	OSD_STR_COMM_ON,                    // "COMM_ON"
	OSD_STR_CONTRAST,                   // "CONTRAST"
	OSD_STR_CRT,                        // "CRT"
	OSD_STR_CVBS_MODE,                  // "CVBS_MODE"
	OSD_STR_CYAN,                       // "CYAN"
	OSD_STR_DATE,                       // "DATE"
	OSD_STR_DAY,                        // "DAY"
	OSD_STR_DAY1,                       // "DAY1"
	OSD_STR_DAY2,                       // "DAY2"
	OSD_STR_DAY3,                       // "DAY3"
	OSD_STR_DAY4,                       // "DAY4"
	OSD_STR_DAY5,                       // "DAY5"
	OSD_STR_DAY6,                       // "DAY6"
	OSD_STR_DAY7,                       // "DAY7"
	OSD_STR_DAY_NIGHT,                  // "DAY_NIGHT"
	OSD_STR_DEFECT_ADJ,                 // "DEFECT_ADJ"
	OSD_STR_DEFOG,                      // "DEFOG"
	OSD_STR_DELAY_TIME,                 // "DELAY_TIME"
	OSD_STR_DETECT_DBDR,                // "DETECT_DBDR"
	OSD_STR_DIS,                        // "DIS"
	OSD_STR_DISPLAY,                    // "DISPLAY"
	OSD_STR_DIST,                       // "DIST"
	OSD_STR_DNR,                        // "DNR"
	OSD_STR_DSS,                        // "DSS"
	OSD_STR_DZOOM,                      // "DZOOM"
	OSD_STR_DZOOM_MODE,                 // "DZOOM_MODE"
	OSD_STR_ENG,                        // "ENG"
	OSD_STR_EXIT,                       // "EXIT"
	OSD_STR_EXIT_SAVE_NO,               // "EXIT_SAVE_NO"
	OSD_STR_EXIT_SAVE_YES,              // "EXIT_SAVE_YES"
	OSD_STR_EXPOSURE,                   // "EXPOSURE"
	OSD_STR_EXT,                        // "EXT"
	OSD_STR_EXT_H,                      // "EXT_H"
	OSD_STR_EXT_L,                      // "EXT_L"
	OSD_STR_FACTORY_RESET,              // "FACTORY_RESET"
	OSD_STR_FIRMWARE_UPDATE,            // "FIRMWARE_UPDATE"
	OSD_STR_FLIP,                       // "FLIP"
	OSD_STR_FOCUS,                      // "FOCUS"
	OSD_STR_FOCUS_MODE,                 // "FOCUS_MODE"
	OSD_STR_FREEZE,                     // "FREEZE"
	OSD_STR_FUNCTION,                   // "FUNCTION"
	OSD_STR_GAIN_LEVEL,                 // "GAIN_LEVEL"
	OSD_STR_GAMMA,                      // "GAMMA"
	OSD_STR_GAMMA1,                     // "GAMMA1"
	OSD_STR_GAMMA2,                     // "GAMMA2"
	OSD_STR_GLOBAL_MOTION,              // "GLOBAL_MOTION"
	OSD_STR_GO_OSD_MENU_SPACETRACE,     // "GO_OSD_MENU_SPACETRA"CE
	OSD_STR_GO_TRACE,                   // "GO_TRACE"
	OSD_STR_GRAY,                       // "GRAY"
	OSD_STR_GREEN,                      // "GREEN"
	OSD_STR_HALL_ADJ,                   // "HALL_ADJ"
	OSD_STR_HALL_MAX,                   // "HALL_MAX"
	OSD_STR_HALL_MIN,                   // "HALL_MIN"
	OSD_STR_HDTV,                       // "HDTV"
	OSD_STR_HEIGHT,                     // "HEIGHT"
	OSD_STR_HIGH,                       // "HIGH"
	OSD_STR_HITACHI,                    // "HITACHI"
	OSD_STR_HLC,                        // "HLC"
	OSD_STR_HUE,                        // "HUE"
	OSD_STR_H_END,                      // "H_END"
	OSD_STR_H_FLIP,                     // "H_FLIP"
	OSD_STR_H_SIZE,                     // "H_SIZE"
	OSD_STR_H_START,                    // "H_START"
	OSD_STR_ID_DISPLAY,                 // "ID_DISPLAY"
	OSD_STR_IMAGE,                      // "IMAGE"
	OSD_STR_IMG,                        // "IMG"
	OSD_STR_INDOOR,                     // "INDOOR"
	OSD_STR_INF,                        // "INF"
	OSD_STR_INITIAL,                    // "INITIAL"
	OSD_STR_INT,                        // "INT"
	OSD_STR_INTERVAL,                   // "INTERVAL"
	OSD_STR_IRIS_ADJ_AE_DISBLE,         // "IRIS_ADJ_AE_DISBLE"
	OSD_STR_IRIS_ADJ_GAIN_VAL,          // "IRIS_ADJ_GAIN_VAL"
	OSD_STR_IRIS_ADJ_IRIS_VAL,          // "IRIS_ADJ_IRIS_VAL"
	OSD_STR_IRIS_ADJ_ON,                // "IRIS_ADJ_ON"
	OSD_STR_IRIS_ADJ_RESET,             // "IRIS_ADJ_RESET"
	OSD_STR_IRIS_ADJ_SHUT_VAL,          // "IRIS_ADJ_SHUT_VAL"
	OSD_STR_IRIS_ADJ_SUM,               // "IRIS_ADJ_SUM"
	OSD_STR_IRIS_ADJ_SW2,               // "IRIS_ADJ_SW2"
	OSD_STR_IRIS_JUMP,                  // "IRIS_JUMP"
	OSD_STR_IRIS_LEVEL,                 // "IRIS_LEVEL"
	OSD_STR_IRIS_PRIORITY,              // "IRIS_PRIORITY"
	OSD_STR_LANGUAGE,                   // "LANGUAGE"
	OSD_STR_LAST_CGAIN,                 // "LAST_CGAIN"
	OSD_STR_LAST_YGAIN,                 // "LAST_YGAIN"
	OSD_STR_LCD,                        // "LCD"
	OSD_STR_LENS_ADJ,                   // "LENS_ADJ"
	OSD_STR_LENS_REFRESH,               // "LENS_REFRESH"
	OSD_STR_LEVEL,                      // "LEVEL"
	OSD_STR_LOAD,                       // "LOAD"
	OSD_STR_LOW,                        // "LOW"
	OSD_STR_LOW_ILLUMINATION,           // "LOW_ILLUMINATION"
	OSD_STR_MAGENTA,                    // "MAGENTA"
	OSD_STR_MAIN_IN,                    // "MAIN_IN"
	OSD_STR_MAIN_OUT,                   // "MAIN_OUT"
	OSD_STR_MANUAL,                     // "MANUAL"
	OSD_STR_MANUAL_PUSH,                // "MANUAL_PUSH"
	OSD_STR_MASK_CENTER,                // "MASK_CENTER"
	OSD_STR_MAX_SHUTTER,                // "MAXS_HUTTER"
	OSD_STR_MENU,                       // "MENU"
	OSD_STR_MIDDLE,                     // "MIDDLE"
	OSD_STR_MIN,                        // "MIN"
	OSD_STR_MIN_SHUTTER,                // "MINS_HUTTER"
	OSD_STR_MODE,                       // "MODE"
	OSD_STR_MODULE,                     // "MODULE"
	OSD_STR_MOSAIC,                     // "MOSAIC"
	OSD_STR_MOTION,                     // "MOTION"
	OSD_STR_MOVE_POSITION,              // "MOVE_POSITION"
	OSD_STR_NIGHT,                      // "NIGHT"
	OSD_STR_NO,                         // "NO"
	OSD_STR_NORMAL,                     // "NORMAL"
	OSD_STR_OFF,                        // "OFF"
	OSD_STR_OFFSET,                     // "OFFSET"
	OSD_STR_ON,                         // "ON"
	OSD_STR_ONEPUSH,                    // "ONEPUSH"
	OSD_STR_OUTDOOR,                    // "OUTDOOR"
	OSD_STR_OUTDOORAUTO,                // "OUTDOORAUTO"
	OSD_STR_OUTPUT_FORMAT,              // "OUTPUT_FORMAT"
	OSD_STR_PELCO_D,                    // "PELCO_D"
	OSD_STR_PELCO_P,                    // "PELCO_P"
	OSD_STR_POLICE,                     // "POLICE"
	OSD_STR_PORT_ON,                    // "PORT_ON"
	OSD_STR_POS,                        // "POS"
	OSD_STR_PRIVACY,                    // "PRIVACY"
	OSD_STR_PRIVACY_ADJ,                // "PRIVACY_ADJ"
	OSD_STR_PRODUCT_CFG,                // "PRODUCT_CFG"
	OSD_STR_PROTOCOL,                   // "PROTOCOL"
	OSD_STR_PUSH,                       // "PUSH"
	OSD_STR_QUICK,                      // "QUICK"
	OSD_STR_REBOOT,                     // "REBOOT"
	OSD_STR_RED,                        // "RED"
	OSD_STR_RED_GAIN,                   // "RED_GAIN"
	OSD_STR_RESET_ZONE,                 // "RESET_ZONE"
	OSD_STR_RETURN,                     // "RETURN"
	OSD_STR_RUN,                        // "RUN"
	OSD_STR_R_GAIN_N,                   // "R_GAIN_N"
	OSD_STR_R_GAIN_P,                   // "R_GAIN_P"
	OSD_STR_R_HUE_N,                    // "R_HUE_N"
	OSD_STR_R_HUE_P,                    // "R_HUE_P"
	OSD_STR_SAVE_NO,                    // "SAVE_NO"
	OSD_STR_SAVE_YES,                   // "SAVE_YES"
	OSD_STR_SDTV,                       // "SDTV"
	OSD_STR_SEC,                        // "SEC"
	OSD_STR_SENSITIVITY,                // "SENSITIVITY"
	OSD_STR_SEPARATE,                   // "SEPARATE"
	OSD_STR_SERIAL_ON,                  // "SERIAL_ON"
	OSD_STR_SET,                        // "SET"
	OSD_STR_SHADE_ADJ,                  // "SHADE_ADJ"
	OSD_STR_SHADING,                    // "SHADING"
	OSD_STR_SHARPNESS,                  // "SHARPNESS"
	OSD_STR_SHUT_PRIORITY,              // "SHUT_PRIORITY"
	OSD_STR_SHUT_SPEED,                 // "SHUT_SPEED"
	OSD_STR_SLOW,                       // "SLOW"
	OSD_STR_SODIUMVAPORLAMP,            // "SODIUMVAPORLAMP"
	OSD_STR_SODIUMVAPORLAMPAUTO,        // "SODIUMVAPORLAMPAUTO"
	OSD_STR_SODIUMVAPORLAMPOUTDOORAUTO,	// "SODIUMVAPORLAMPOUTDO"ORA
	OSD_STR_SPECIAL,                    // "SPECIAL"
	OSD_STR_START,                      // "START"
	OSD_STR_STATE,                      // "STATE"
	OSD_STR_STOP,                       // "STOP"
	OSD_STR_SYNC,                       // "SYNC"
	OSD_STR_SYSTEM,                     // "SYSTEM"
	OSD_STR_SYSTEM_ADJ,                 // "SYSTEM_ADJ"
	OSD_STR_SYSTEM_INFO,                // "SYSTEM_INFO"
	OSD_STR_TEST_IMAGE,                 // "TEST_IMAGE"
	OSD_STR_TEXT,                       // "TEXT"
	OSD_STR_THRESHOLD,                  // "THRESHOLD"
	OSD_STR_TIME,                       // "TIME"
	OSD_STR_TRACE,                      // "TRACE"
	OSD_STR_TRANS,                      // "TRANS"
	OSD_STR_TRIGER,                     // "TRIGER"
	OSD_STR_TR_AESTAT,                  // "TR_AESTAT"
	OSD_STR_TR_CHOISE,                  // "TR_CHOISE"
	OSD_STR_TR_COLOR_STATE,             // "TR_COLOR_STATE"
	OSD_STR_TR_COMM,                    // "TR_COMM"
	OSD_STR_TR_DBDR,                    // "TR_DBDR"
	OSD_STR_TR_DNR,                     // "TR_DNR"
	OSD_STR_TR_DZOOM,                   // "TR_DZOOM"
	OSD_STR_TR_FOCUS1,                  // "TR_FOCUS1"
	OSD_STR_TR_FOCUS2,                  // "TR_FOCUS2"
	OSD_STR_TR_FOCUSSTAT,               // "TR_FOCUSSTAT"
	OSD_STR_TR_HALLADJUST,              // "TR_HALLADJUST"
	OSD_STR_TR_ICR,                     // "TR_ICR"
	OSD_STR_TR_KEYCONTROL,              // "TR_KEYCONTROL"
	OSD_STR_TR_LENSPARAM,               // "TR_LENSPARAM"
	OSD_STR_TR_MOTION,                  // "TR_MOTION"
	OSD_STR_TR_NONE,                    // "TR_NONE"
	OSD_STR_TR_PARE1,                   // "TR_PARE1"
	OSD_STR_TR_PARE2,                   // "TR_PARE2"
	OSD_STR_TR_PARE3,                   // "TR_PARE3"
	OSD_STR_TR_PARE4,                   // "TR_PARE4"
	OSD_STR_TR_PARE5,                   // "TR_PARE5"
	OSD_STR_TR_PGAGAIN,                 // "TR_PGAGAIN"
	OSD_STR_TR_PROCNBA,                 // "TR_PROCNBA"
	OSD_STR_TR_PROCNBH,                 // "TR_PROCNBH"
	OSD_STR_TR_PROPRLCO,                // "TR_PROPRLCO"
	OSD_STR_TR_PROVISCA,                // "TR_PROVISCA"
	OSD_STR_TR_STABILIZER,              // "TR_STABILIZER"
	OSD_STR_TR_WDR,                     // "TR_WDR"
	OSD_STR_TR_ZOOMTRACK,               // "TR_ZOOMTRACK"
	OSD_STR_TUNNIG,                     // "TUNNIG"
	OSD_STR_UPDATE_MODE1,               // "UPDATE_MODE1"
	OSD_STR_UPDATE_MODE2,               // "UPDATE_MODE2"
	OSD_STR_UPDATE_MODE3,               // "UPDATE_MODE3"
	OSD_STR_UPDATE_START,               // "UPDATE_START"
	OSD_STR_USER,                       // "USER"
	OSD_STR_USER_ADJUST,                // "USER_ADJUST"
	OSD_STR_VERSION,                    // "VERSION"
	OSD_STR_VH_FLIP,                    // "VH_FLIP"
	OSD_STR_VIDEO_ENCODER,              // "VIDEO_ENCODER"
	OSD_STR_VIDEO_POSITION,             // "VIDEO_POSITION"
	OSD_STR_VISCA,                      // "VISCA"
	OSD_STR_VISCA_OSD_TYPE,             // "VISCA_OSD_TYPE"
	OSD_STR_V_ACT_END,                  // "V_ACT_END"
	OSD_STR_V_ACT_END_BOT,              // "V_ACT_END_BOT"
	OSD_STR_V_ACT_START,                // "V_ACT_START"
	OSD_STR_V_ACT_START_BOT,            // "V_ACT_START_BOT"
	OSD_STR_V_FLIP,                     // "V_FLIP"
	OSD_STR_V_TOTAL_SIZE,               // "V_TOTAL_SIZE"
	OSD_STR_WDR,                        // "WDR"
	OSD_STR_WHITE,                      // "WHITE"
	OSD_STR_WHITE_BALANCE,              // "WHITE_BALANCE"
	OSD_STR_WIDTH,                      // "WIDTH"
	OSD_STR_X10,                        // "X10"
	OSD_STR_X12,                        // "X12"
	OSD_STR_X128,                       // "X128"
	OSD_STR_X16,                        // "X16"
	OSD_STR_X2,                         // "X2"
	OSD_STR_X20,                        // "X20"
	OSD_STR_X24,                        // "X24"
	OSD_STR_X256,                       // "X256"
	OSD_STR_X3,                         // "X3"
	OSD_STR_X32,                        // "X32"
	OSD_STR_X4,                         // "X4"
	OSD_STR_X5,                         // "X5"
	OSD_STR_X512,                       // "X512"
	OSD_STR_X6,                         // "X6"
	OSD_STR_X64,                        // "X64"
	OSD_STR_X8,                         // "X8"
	OSD_STR_X_AXIS,                     // "X_AXIS"
	OSD_STR_X_POS,                      // "X_POS"
	OSD_STR_YELLOW,                     // "YELLOW"
	OSD_STR_YES,                        // "YES"
	OSD_STR_Y_AXIS,                     // "Y_AXIS"
	OSD_STR_Y_POS,                      // "Y_POS"
	OSD_STR_ZONE,                       // "ZONE"
	OSD_STR_ZOOM,                       // "ZOOM"
	OSD_STR_ZOOM_END,                   // "ZOOM_END"
	OSD_STR_ZOOM_IN_OUT,                // "ZOOM_IN_OUT"
	OSD_STR_ZOOM_MAG,                   // "ZOOM_MAG"
	OSD_STR_ZOOM_MODE,                  // "ZOOM_MODE"
	OSD_STR_ZOOM_SPEED,                 // "ZOOM_SPEED"
	OSD_STR_ZOOM_START,                 // "ZOOM_START"
	OSD_STR_ZOOM_TRK_MODE,              // "ZOOM_TRK_MODE"
	OSD_STR__PUSH,                      // "PUSH"

	OSD_STR_FINISH                    // OSD Map의 마지막을 의미
} OSD_STR;

/************************************************************************************************************/
/* Protocol */
typedef enum _PTC_TYPE {
	PTC_CNBH = 0x01,
	PTC_CNBA = 0x02,
	PTC_PELCOD = 0x04,
	PTC_PELCOP = 0x08,
	PTC_VISCA = 0x10,
	PTC_HITACHI = 0x20
} PTC_TYPE;

typedef enum _VISCA_REPLY_TYPE{
	VSC_REPLY_MD,		// Data : Detected Mask Number
	VSC_REPLY_ICR,		// Data : ICR OFF->ON(NIGHT) :1 , ICR ON->OFF(DAY) :0
	VSC_REPLY_ZOOM,		// Data : [0:15] Zoom , [16:31] DZoom
	VSC_REPLY_FOCUS,	// Data : Focus
	VSC_REPLY_WD,
	VSC_REPLY_MAX,
} VISCA_REPLY_TYPE;
/*************************************************************************************************************
* STRUCTURE
*************************************************************************************************************/
/************************************************************************************************************/
/* Event 발생시 전달되는 값 */
typedef struct _IFEVT_PARAM {
	EEP_IDX eepidx;
	uint32 key;
} IFEVT_PARAM;

typedef struct _IFEVT_BLOCK_INQ {
	EEP_IDX eepidx;
	uint32 stt_byte;
	uint32 stt_bit;
	uint32 length;
} IFEVT_BLOCK_INQ;
/************************************************************************************************************/
/* EEPRom */
/* EEPRom Map 주소 */
#define EEP_ADDR_S0_STT		(0x0000)	// Header(16Bytes) + OSD Menu Structure
#define EEP_ADDR_S0_END		(0x00FF)	// "
#define EEP_ADDR_S1_STT		(0x0100)	// Extended OSD Menu Structure
#define EEP_ADDR_S1_END		(0x01FF)	// "
#define EEP_ADDR_S2_STT		(0x0200)	// Initial Value OSD Menu Structure
#define EEP_ADDR_S2_END 	(0x02FF)	// "
#define EEP_ADDR_S3_STT 	(0x0300)	// Initial Value Extended OSD Menu Structure
#define EEP_ADDR_S3_END 	(0x03FF)	// "
#define EEP_ADDR_S4_STT 	(0x0400)	// Technical Parameters
#define EEP_ADDR_S4_END 	(0x04FF)	// "
#define EEP_ADDR_S5_STT 	(0x0500)	// Camera Operation Data
#define EEP_ADDR_S5_END 	(0x05FF)	// "
#define EEP_ADDR_S6_STT 	(0x0600)	// Reserved
#define EEP_ADDR_S6_END 	(0x06FF)	// "
#define EEP_ADDR_S7_STT 	(0x0700)	// "
#define EEP_ADDR_S7_END 	(0x07FF)	// "
#define EEP_ADDR_S8_STT 	(0x0800)	// Custom Preset Memory
#define EEP_ADDR_S8_END 	(0x08FF)	// "
#define EEP_ADDR_S9_STT 	(0x0900)	// "
#define EEP_ADDR_S9_END 	(0x09FF)	// "
#define EEP_ADDR_S10_STT	(0x0A00)	// "
#define EEP_ADDR_S10_END	(0x0AFF)	// "
#define EEP_ADDR_S11_STT	(0x0B00)	// "
#define EEP_ADDR_S11_END	(0x0BFF)	// "
#define EEP_ADDR_S12_STT	(0x0C00)	// "
#define EEP_ADDR_S12_END	(0x0CFF)	// "
#define EEP_ADDR_S13_STT	(0x0D00)	// "
#define EEP_ADDR_S13_END	(0x0DFF)	// "
#define EEP_ADDR_S14_STT	(0x0E00)	// Extended Custom Preset Memory
#define EEP_ADDR_S14_END	(0x0EFF)	// "
#define EEP_ADDR_S15_STT	(0x0F00)	// "
#define EEP_ADDR_S15_END	(0x0FFF)	// "
#define EEP_ADDR_S16_STT	(0x1000)	// VISCA Section
#define EEP_ADDR_S16_END	(0x10FF)	// "
#define EEP_ADDR_S17_STT	(0x1100)	// "
#define EEP_ADDR_S17_END	(0x11FF)	// "
#define EEP_ADDR_S18_STT	(0x1200)	// "
#define EEP_ADDR_S18_END	(0x12FF)	// "
#define EEP_ADDR_S19_STT	(0x1300)	// "
#define EEP_ADDR_S19_END	(0x13FF)	// "
#define EEP_ADDR_S20_STT	(0x1400)	// Reserved
#define EEP_ADDR_S20_END	(0x14FF)	// "
#define EEP_ADDR_S21_STT	(0x1500)	// "
#define EEP_ADDR_S21_END	(0x15FF)	// "
#define EEP_ADDR_S22_STT	(0x1600)	// "
#define EEP_ADDR_S22_END	(0x16FF)	// "
#define EEP_ADDR_S23_STT	(0x1700)	// "
#define EEP_ADDR_S23_END	(0x17FF)	// "
#define EEP_ADDR_S24_STT	(0x1800)	// Shading Compensation Table
#define EEP_ADDR_S24_END	(0x18FF)	// "
#define EEP_ADDR_S25_STT	(0x1900)	// "
#define EEP_ADDR_S25_END	(0x19FF)	// "
#define EEP_ADDR_S26_STT	(0x1A00)	// Reserved (Extended Shading Compensation Table)
#define EEP_ADDR_S26_END	(0x1AFF)	// "
#define EEP_ADDR_S27_STT	(0x1B00)	// "
#define EEP_ADDR_S27_END	(0x1BFF)	// "
#define EEP_ADDR_S28_STT	(0x1C00)	// White Pixel Position (Defect Position) (128ea/32Bits)
#define EEP_ADDR_S28_END	(0x1CFF)	// "
#define EEP_ADDR_S29_STT	(0x1D00)	// "
#define EEP_ADDR_S29_END	(0x1DFF)	// "
#define EEP_ADDR_S30_STT	(0x1E00)	// Reserved (Extended White Pixel Position (Defect Position))
#define EEP_ADDR_S30_END	(0x1EFF)	// "
#define EEP_ADDR_S31_STT	(0x1F00)	// "
#define EEP_ADDR_S31_END	(0x1FFF)	// "

#define EEP_SECTION_MAX		(0x100)

#define EEP_OSD_MAX			(0xF4)
/* 0Page : EEPRom Header + OSD = 0x0000 ~ 0x00FF */
typedef union _EEP_OSD_DATA
{
	uint08 Data[EEP_OSD_MAX];

	struct
	{
		/* Header 0x0000 ~ 0x000F */
		unsigned MEM_STATUS : 3;	unsigned CAM_TYPE : 2;	unsigned CAM_CLASS : 3;
		unsigned MEM_VER : 8;
		unsigned CCD_TYPE : 4;	unsigned CLIENT_OPT : 4;
		unsigned HALL_ADJ : 4;	unsigned LENS_ADJ : 4;
		unsigned MASK_ADJ : 4;	unsigned DEFECT_ADJ : 4;
		unsigned SHADE_ADJ : 4;	unsigned COLOR_ADJ : 4;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned COMM_SET : 1;	unsigned MENU_USE : 1;	unsigned LENS_INIT_TYPE : 2;	unsigned HOME_USE : 1;	unsigned : 3;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		/* FOCUS 0x0010 ~ 0x0025 */
		unsigned FOCUS_MODE : 4;	unsigned AF_MODE : 4;
		unsigned AF_MOVE_TIME : 8;
		unsigned AF_INTERVAL_TIME : 8;
		unsigned FOCUS_DIST : 4;	unsigned ZOOM_MODE : 2;	unsigned DZOOM_MODE : 2;
		unsigned ZTRK_MODE : 2;	unsigned ZOOM_SPEED : 4;	unsigned LENS_REFRESH_MODE : 2;
		unsigned LENS_REFRESH_DAYS : 8;
		unsigned ZSRT_MAG : 16;
		unsigned ZEND_MAG : 16;
		unsigned Z_HOME_POS : 16;
		unsigned F_HOME_POS : 16;
		unsigned DZ_HOME_POS : 16;
		unsigned DZOOM_MAG : 8;
		unsigned HOME_MODE : 2;	unsigned : 6;
		unsigned HOME_TIME : 8;
		/* EXPOSURE 0x0023 ~ 0x0029 */
		unsigned AE_TGT_BRIGHT : 8;
		unsigned AE_MODE : 4;	unsigned AE_AGC_LIMIT : 4;
		unsigned AEM_IRIS_STEP : 8;
		unsigned AEM_SHUT_STEP : 8;
		unsigned AEM_BRIGHT_STEP : 8;
		unsigned AEM_GAIN_STEP: 8;
		unsigned AE_DSS_STEP : 4;	unsigned AE_FLK_MODE : 4;
		/* WB 0x002A ~ 0x0033 */
		unsigned WB_MODE : 4;	unsigned WB_ENV : 4;
		unsigned WB_RED_GAIN : 8;
		unsigned WB_BLUE_GAIN : 8;
		unsigned WB_COLOR_TEMP : 8;
		unsigned ATW_SPEED : 5;	unsigned ATW_FRAME : 3;
		unsigned ATW_DELAY : 5;	unsigned : 3;
		unsigned USER1_RGAIN : 8;
		unsigned USER1_BGAIN : 8;
		unsigned USER2_RGAIN : 8;
		unsigned USER2_BGAIN : 8;
		/* D/N 0x0034 ~ 0x0038 */
		unsigned DN_MODE : 4;	unsigned DN_ALARM_ON : 1;	unsigned : 3;
		unsigned DN_CHG_STEP : 8;
		unsigned DN_CDS_STEP : 8;
		unsigned DN_CHG_TIME : 7;	unsigned DN_MIN : 1;
		unsigned DN_CDS_CHG_TIME : 7;	unsigned DN_CDS_MIN : 1;
		/* IMAGE 0x0039 ~ 0x0042 */
		unsigned IMG_BRIGHT : 8;
		unsigned IMG_CONTRAST : 8;
		unsigned IMG_SHARPNESS : 8;
		unsigned IMG_CHROMA : 8;
		unsigned IMG_HUE : 8;
		unsigned IMG_FLIP : 2;	unsigned IMG_FREEZE : 1;	unsigned IMG_EFFECT : 2;	unsigned IMG_COLOR : 1;	unsigned IMG_SHADING : 1;	unsigned IMG_DEFECT : 1;
		unsigned IMG_GAMMA_STEP : 6;	unsigned IMG_GAM_MODE : 2;
		unsigned IMG_RGAIN : 8;
		unsigned IMG_BGAIN : 8;
		unsigned HR_MODE : 4;	unsigned : 4;
		/* BACKLIGHT 0x0043 ~ 0x004E */
		unsigned BL_MODE : 4;	unsigned : 4;
		unsigned BLC_MODE : 2;	unsigned BLC_DISP : 1;	unsigned : 5;
		unsigned BLC_LEVEL : 8;
		unsigned BLC_AREA_X_SRT : 8;
		unsigned BLC_AREA_Y_SRT : 8;
		unsigned BLC_AREA_WIDTH : 8;
		unsigned BLC_AREA_HEIGHT : 8;
		unsigned WDR_MODE : 2;	unsigned : 6;
		unsigned WDR_LEVEL : 8;
		unsigned HLC_MODE : 2;	unsigned HLC_MASK_COLOR : 4;	unsigned : 2;
		unsigned HLC_LEVEL : 8;
		unsigned HLC_SCALE : 8;
		/* DNR 0x004F ~ 0x0051 */
		unsigned DNR_MODE : 4;	unsigned DNR_GLB_MOT : 1;	unsigned : 3;
		unsigned DNR_LEVEL : 8;
		unsigned _3DNR_LEVEL : 4;	unsigned _2DNR_LEVEL : 4;
		/* SPECIAL/MOTION 0x0052 ~ 0x006A */
		unsigned MD_ON : 1;	unsigned : 7;
		unsigned MD1_STATE : 1;	unsigned MD1_DISP : 2;	unsigned MD1_ALARM : 2;	unsigned : 3;
		unsigned MD1_SENS : 8;
		unsigned MD1_X_SRT : 8;
		unsigned MD1_Y_SRT : 8;
		unsigned MD1_WIDTH : 8;
		unsigned MD1_HEIGHT : 8;
		unsigned MD2_STATE : 1;	unsigned MD2_DISP : 2;	unsigned MD2_ALARM : 2;	unsigned : 3;
		unsigned MD2_SENS : 8;
		unsigned MD2_X_SRT : 8;
		unsigned MD2_Y_SRT : 8;
		unsigned MD2_WIDTH : 8;
		unsigned MD2_HEIGHT : 8;
		unsigned MD3_STATE : 1;	unsigned MD3_DISP : 2;	unsigned MD3_ALARM : 2;	unsigned : 3;
		unsigned MD3_SENS : 8;
		unsigned MD3_X_SRT : 8;
		unsigned MD3_Y_SRT : 8;
		unsigned MD3_WIDTH : 8;
		unsigned MD3_HEIGHT : 8;
		unsigned MD4_STATE : 1;	unsigned MD4_DISP : 2;	unsigned MD4_ALARM : 2;	unsigned : 3;
		unsigned MD4_SENS : 8;
		unsigned MD4_X_SRT : 8;
		unsigned MD4_Y_SRT : 8;
		unsigned MD4_WIDTH : 8;
		unsigned MD4_HEIGHT : 8;
		/* SPECIAL/PRIVACY MASK 0x006B ~ 0x00CB */
		unsigned MASK_ON : 1;	unsigned MASK_I : 1;	unsigned : 6;
		unsigned : 8;
		unsigned MASK1_STATE : 1;	unsigned MASK1_TRANS : 2;	unsigned MASK1_COLOR : 3;	unsigned MASK1_MOSAIC : 2;
		unsigned MASK1_X_SRT : 8;
		unsigned MASK1_Y_SRT : 8;
		unsigned MASK1_WIDTH : 8;
		unsigned MASK1_HEIGHT : 8;
		unsigned MASK1_PAN : 16;
		unsigned MASK1_TILT : 16;
		unsigned MASK1_ZOOM : 16;
		unsigned : 8;
		unsigned MASK2_STATE : 1;	unsigned MASK2_TRANS : 2;	unsigned MASK2_COLOR : 3;	unsigned MASK2_MOSAIC : 2;
		unsigned MASK2_X_SRT : 8;
		unsigned MASK2_Y_SRT : 8;
		unsigned MASK2_WIDTH : 8;
		unsigned MASK2_HEIGHT : 8;
		unsigned MASK2_PAN : 16;
		unsigned MASK2_TILT : 16;
		unsigned MASK2_ZOOM : 16;
		unsigned : 8;
		unsigned MASK3_STATE : 1;	unsigned MASK3_TRANS : 2;	unsigned MASK3_COLOR : 3;	unsigned MASK3_MOSAIC : 2;
		unsigned MASK3_X_SRT : 8;
		unsigned MASK3_Y_SRT : 8;
		unsigned MASK3_WIDTH : 8;
		unsigned MASK3_HEIGHT : 8;
		unsigned MASK3_PAN : 16;
		unsigned MASK3_TILT : 16;
		unsigned MASK3_ZOOM : 16;
		unsigned : 8;
		unsigned MASK4_STATE : 1;	unsigned MASK4_TRANS : 2;	unsigned MASK4_COLOR : 3;	unsigned MASK4_MOSAIC : 2;
		unsigned MASK4_X_SRT : 8;
		unsigned MASK4_Y_SRT : 8;
		unsigned MASK4_WIDTH : 8;
		unsigned MASK4_HEIGHT : 8;
		unsigned MASK4_PAN : 16;
		unsigned MASK4_TILT : 16;
		unsigned MASK4_ZOOM : 16;
		unsigned : 8;
		unsigned MASK5_STATE : 1;	unsigned MASK5_TRANS : 2;	unsigned MASK5_COLOR : 3;	unsigned MASK5_MOSAIC : 2;
		unsigned MASK5_X_SRT : 8;
		unsigned MASK5_Y_SRT : 8;
		unsigned MASK5_WIDTH : 8;
		unsigned MASK5_HEIGHT : 8;
		unsigned MASK5_PAN : 16;
		unsigned MASK5_TILT : 16;
		unsigned MASK5_ZOOM : 16;
		unsigned : 8;
		unsigned MASK6_STATE : 1;	unsigned MASK6_TRANS : 2;	unsigned MASK6_COLOR : 3;	unsigned MASK6_MOSAIC : 2;
		unsigned MASK6_X_SRT : 8;
		unsigned MASK6_Y_SRT : 8;
		unsigned MASK6_WIDTH : 8;
		unsigned MASK6_HEIGHT : 8;
		unsigned MASK6_PAN : 16;
		unsigned MASK6_TILT : 16;
		unsigned MASK6_ZOOM : 16;
		unsigned : 8;
		unsigned MASK7_STATE : 1;	unsigned MASK7_TRANS : 2;	unsigned MASK7_COLOR : 3;	unsigned MASK7_MOSAIC : 2;
		unsigned MASK7_X_SRT : 8;
		unsigned MASK7_Y_SRT : 8;
		unsigned MASK7_WIDTH : 8;
		unsigned MASK7_HEIGHT : 8;
		unsigned MASK7_PAN : 16;
		unsigned MASK7_TILT : 16;
		unsigned MASK7_ZOOM : 16;
		unsigned : 8;
		unsigned MASK8_STATE : 1;	unsigned MASK8_TRANS : 2;	unsigned MASK8_COLOR : 3;	unsigned MASK8_MOSAIC : 2;
		unsigned MASK8_X_SRT : 8;
		unsigned MASK8_Y_SRT : 8;
		unsigned MASK8_WIDTH : 8;
		unsigned MASK8_HEIGHT : 8;
		unsigned MASK8_PAN : 16;
		unsigned MASK8_TILT : 16;
		unsigned MASK8_ZOOM : 16;
		/* SPECIAL 0x00CC ~ 0x00CE */
		unsigned DEFOG_ON : 1;	unsigned DIS_ON : 1;	unsigned SYNC : 2;	unsigned SHADE_ON : 1;	unsigned : 3;
		unsigned SYNC_PHASE : 16;
		/* SYSTEM 0x00CF ~ 0x00F0 */
		unsigned CAM_ID : 8;
		unsigned CAMID_X_POS : 8;
		unsigned CAMID_Y_POS : 8;
		unsigned BAUDRATE : 4;	unsigned PROTOCOL : 4;
		unsigned OSD_LANGUAGE : 8;
		unsigned ID_ON : 1;	unsigned TITLE_ON : 1;	unsigned ZMAG_ON : 1;	unsigned FUNC_ON : 1;	unsigned : 3;	unsigned ALL_ON : 1;
		unsigned TITLE_BLK : 1;	unsigned TITLE_COLOR : 3;	unsigned : 4;
		unsigned TITLE_X_POS : 8;
		unsigned TITLE_Y_POS : 8;
		unsigned CAM_TITLE_CH1 : 8;
		unsigned CAM_TITLE_CH2 : 8;
		unsigned CAM_TITLE_CH3 : 8;
		unsigned CAM_TITLE_CH4 : 8;
		unsigned CAM_TITLE_CH5 : 8;
		unsigned CAM_TITLE_CH6 : 8;
		unsigned CAM_TITLE_CH7 : 8;
		unsigned CAM_TITLE_CH8 : 8;
		unsigned CAM_TITLE_CH9 : 8;
		unsigned CAM_TITLE_CH10 : 8;
		unsigned CAM_TITLE_CH11 : 8;
		unsigned CAM_TITLE_CH12 : 8;
		unsigned CAM_TITLE_CH13 : 8;
		unsigned CAM_TITLE_CH14 : 8;
		unsigned CAM_TITLE_CH15 : 8;
		unsigned CAM_TITLE_CH16 : 8;
		unsigned CAM_TITLE_CH17 : 8;
		unsigned CAM_TITLE_CH18 : 8;
		unsigned CAM_TITLE_CH19 : 8;
		unsigned CAM_TITLE_CH20 : 8;
		unsigned CAM_TITLE_CH21 : 8;
		unsigned CAM_TITLE_CH22 : 8;
		unsigned CAM_TITLE_CH23 : 8;
		unsigned CAM_TITLE_CH24 : 8;
		unsigned VOUT_FORMAT : 4;	unsigned LVDS_D : 1;	unsigned DOUT_FULL : 1;	unsigned DOUT_ON : 1;	unsigned CVBS_ON : 1;
		unsigned :8;
		unsigned :8;
		unsigned :8;
	} FLD;
} EEP_OSD_DATA;

#define EEP_CAM_OP_MAX			(0x70)

/* 5Page : Camera Operation Data = 0x0500 ~ 0x056F */
typedef union _EEP_CAM_OP_DATA
{
	uint08 Data[EEP_CAM_OP_MAX];

	struct
	{
		/* HALL 0x0500 ~ 0x050F */
		unsigned TGT_HALL_MAX : 16;
		unsigned TGT_HALL_MIN : 16;
		unsigned HADJ_MAX : 16;
		unsigned HADJ_MIN : 16;
		unsigned HO_ZERO : 8;
		unsigned HG_ZERO : 8;
		unsigned HB_ZERO : 8;
		unsigned HADJ_DIFF_OFF : 8;
		unsigned HADJ_MEAN_OFF : 8;
		unsigned HADJ_HG : 8;
		unsigned HADJ_HO : 8;
		unsigned HADJ_HB : 8;
		/* LENS OFFSET 0x0510 ~ 0x051D */
		unsigned OADJ_ZADD : 8;
		unsigned OADJ_FADD : 8;
		unsigned OADJ_ZOFF : 8;
		unsigned OADJ_FOFF : 8;
		unsigned OADJ_PD_SRT : 8;
		unsigned OADJ_ZD_SRT : 8;
		unsigned OADJ_FD_SRT : 8;
		unsigned OADJ_P2DEC_R : 8;
		unsigned OADJ_T2DEC_R : 8;
		unsigned OADJ_PD : 8;
		unsigned OADJ_ZD : 8;
		unsigned OADJ_FD : 8;
		unsigned OADJ_WEND_S : 8;
		unsigned OADJ_TEND_S : 8;
		/* PRIVACY MASK 0x051E ~ 0x0512 */
		unsigned MADJ_3D_PAN_NT : 8;
		unsigned MADJ_3D_TILT_NT : 8;
		unsigned MADJ_3D_PAN_PA : 8;
		unsigned MADJ_3D_TILT_PA : 8;
		/* DEFECT 0x0522 ~ 0x0525 */
		unsigned DADJ_THRESHOLD : 8;
		unsigned DADJ_CNT		: 8;
		unsigned : 8;
		unsigned : 8;
		/* SHADING 0x0526 ~ 0x0529 */
		unsigned SADJ_GAIN : 8;
		unsigned SADJ_OFFSET : 8;
		unsigned : 8;
		unsigned : 8;
		/* COLOR 0x052A ~ 0x053F */
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		unsigned : 8;
		/* LOGO 0x0540 ~ 0x055F */
		unsigned LOGO_CH1 : 8;
		unsigned LOGO_CH2 : 8;
		unsigned LOGO_CH3 : 8;
		unsigned LOGO_CH4 : 8;
		unsigned LOGO_CH5 : 8;
		unsigned LOGO_CH6 : 8;
		unsigned LOGO_CH7 : 8;
		unsigned LOGO_CH8 : 8;
		unsigned LOGO_CH9 : 8;
		unsigned LOGO_CH10 : 8;
		unsigned LOGO_CH11 : 8;
		unsigned LOGO_CH12 : 8;
		unsigned LOGO_CH13 : 8;
		unsigned LOGO_CH14 : 8;
		unsigned LOGO_CH15 : 8;
		unsigned LOGO_CH16 : 8;
		unsigned LOGO_CH17 : 8;
		unsigned LOGO_CH18 : 8;
		unsigned LOGO_CH19 : 8;
		unsigned LOGO_CH20 : 8;
		unsigned LOGO_CH21 : 8;
		unsigned LOGO_CH22 : 8;
		unsigned LOGO_CH23 : 8;
		unsigned LOGO_CH24 : 8;
		unsigned LOGO_CH25 : 8;
		unsigned LOGO_CH26 : 8;
		unsigned LOGO_CH27 : 8;
		unsigned LOGO_CH28 : 8;
		unsigned LOGO_CH29 : 8;
		unsigned LOGO_CH30 : 8;
		unsigned LOGO_CH31 : 8;
		unsigned LOGO_CH32 : 8;
		/* ADKEY 0x0560 ~ 0x056F */
		unsigned ADKEY00 : 8;
		unsigned ADKEY01 : 8;
		unsigned ADKEY02 : 8;
		unsigned ADKEY03 : 8;
		unsigned ADKEY04 : 8;
		unsigned ADKEY05 : 8;
		unsigned ADKEY06 : 8;
		unsigned ADKEY07 : 8;
		unsigned ADKEY10 : 8;
		unsigned ADKEY11 : 8;
		unsigned ADKEY12 : 8;
		unsigned ADKEY13 : 8;
		unsigned ADKEY14 : 8;
		unsigned ADKEY15 : 8;
		unsigned ADKEY16 : 8;
		unsigned ADKEY17 : 8;
	} FLD;
} EEP_CAM_OP_DATA;

#define EEP_VISCA_MAX			(0x387)

/* 16~19Page :Visca Data = 0x1000 ~ 0x1386 */
typedef union _EEP_VISCA_DATA
{
	uint08 Data[EEP_VISCA_MAX];

	struct
	{
		unsigned PWR_ON : 1;	unsigned : 7;
		unsigned ZOOM_POS : 16;
		unsigned DZOOM_ON : 1;	unsigned DZOOM_MODE : 1;	unsigned : 6;
		unsigned DZOOM_POS : 8;
		unsigned FOCUS_POS : 16;
		unsigned F_MODE : 2;	unsigned : 6;
		unsigned NEAR_LIMIT : 16;
		unsigned AF_SENS : 1;	unsigned : 7;
		unsigned AF_MODE : 2;	unsigned : 6;
		unsigned AF_MOVE_TIME : 8;
		unsigned AF_INTERVAL_TIME : 8;
		unsigned IR_COR : 1;	unsigned : 7;
		unsigned WB_MODE : 4;	unsigned : 4;
		unsigned PUSH_WB_RGAIN : 8;
		unsigned PUSH_WB_BGAIN : 8;
		unsigned R_GAIN : 8;
		unsigned B_GAIN : 8;
		unsigned AE_MODE : 3;	unsigned : 5;
		unsigned ASS_ON : 1;	unsigned : 7;
		unsigned SHUTTER_STEP : 8;
		unsigned IRIS_STEP : 8;
		unsigned GAIN_STEP : 8;
		unsigned GAIN_LIMIT : 4;	unsigned : 4;
		unsigned BRIGHT_STEP :8;
		unsigned COMP_ON : 1;	unsigned : 7;
		unsigned EXP_COMP_VAL : 8;
		unsigned BLC_ON : 1;	unsigned : 7;
		unsigned SPOT_AE_ON : 1;	unsigned : 7;
		unsigned SPOT_AE_X_POS : 8;
		unsigned SPOT_AE_Y_POS : 8;
		unsigned AE_RESPONSE : 8;
		unsigned WD_MODE : 3;	unsigned : 5;
		unsigned WD_BRT_L : 3;	unsigned WD_BRT_COMP : 2;	unsigned WD_COMP_L : 2;	unsigned : 1;
		unsigned DEFOG_ON : 1;	unsigned : 7;
		unsigned APER_GAIN : 8;
		unsigned HR_ON : 1;	unsigned : 7;
		unsigned NR_SET : 8;
		unsigned GAM_SET : 3;	unsigned : 5;
		unsigned HIGH_SENS_ON : 1;	unsigned : 7;
		unsigned LR_ON : 1;	unsigned : 7;
		unsigned FREEZE_ON : 1;	unsigned : 7;
		unsigned P_EFFECT : 3;	unsigned : 5;
		unsigned FLIP_ON : 1;	unsigned : 7;
		unsigned ICR_ON : 1;	unsigned : 7;
		unsigned AICR_ON : 1;	unsigned : 7;
		unsigned AICR_THRS_L : 8;
		unsigned AICR_ALARM_ON : 1;	unsigned : 7;
		unsigned DISP_ON : 1;	unsigned : 7;
		unsigned TITLE_H_POS0 : 5;	unsigned : 2;	unsigned TITLE_ON0 : 1;
		unsigned TITLE_LINE0 : 4;	unsigned TITLE_BLINK0 : 1;	unsigned TITLE_COLOR0 : 3;
		unsigned TITLE_LINE0_CH1 : 8;
		unsigned TITLE_LINE0_CH2 : 8;
		unsigned TITLE_LINE0_CH3 : 8;
		unsigned TITLE_LINE0_CH4 : 8;
		unsigned TITLE_LINE0_CH5 : 8;
		unsigned TITLE_LINE0_CH6 : 8;
		unsigned TITLE_LINE0_CH7 : 8;
		unsigned TITLE_LINE0_CH8 : 8;
		unsigned TITLE_LINE0_CH9 : 8;
		unsigned TITLE_LINE0_CH10 : 8;
		unsigned TITLE_LINE0_CH11 : 8;
		unsigned TITLE_LINE0_CH12 : 8;
		unsigned TITLE_LINE0_CH13 : 8;
		unsigned TITLE_LINE0_CH14 : 8;
		unsigned TITLE_LINE0_CH15 : 8;
		unsigned TITLE_LINE0_CH16 : 8;
		unsigned TITLE_LINE0_CH17 : 8;
		unsigned TITLE_LINE0_CH18 : 8;
		unsigned TITLE_LINE0_CH19 : 8;
		unsigned TITLE_LINE0_CH20 : 8;
		unsigned TITLE_H_POS1 : 5;	unsigned : 2;	unsigned TITLE_ON1 : 1;
		unsigned TITLE_LINE1 : 4;	unsigned TITLE_BLINK1 : 1;	unsigned TITLE_COLOR1 : 3;
		unsigned TITLE_LINE1_CH1 : 8;
		unsigned TITLE_LINE1_CH2 : 8;
		unsigned TITLE_LINE1_CH3 : 8;
		unsigned TITLE_LINE1_CH4 : 8;
		unsigned TITLE_LINE1_CH5 : 8;
		unsigned TITLE_LINE1_CH6 : 8;
		unsigned TITLE_LINE1_CH7 : 8;
		unsigned TITLE_LINE1_CH8 : 8;
		unsigned TITLE_LINE1_CH9 : 8;
		unsigned TITLE_LINE1_CH10 : 8;
		unsigned TITLE_LINE1_CH11 : 8;
		unsigned TITLE_LINE1_CH12 : 8;
		unsigned TITLE_LINE1_CH13 : 8;
		unsigned TITLE_LINE1_CH14 : 8;
		unsigned TITLE_LINE1_CH15 : 8;
		unsigned TITLE_LINE1_CH16 : 8;
		unsigned TITLE_LINE1_CH17 : 8;
		unsigned TITLE_LINE1_CH18 : 8;
		unsigned TITLE_LINE1_CH19 : 8;
		unsigned TITLE_LINE1_CH20 : 8;
		unsigned TITLE_H_POS2 : 5;	unsigned : 2;	unsigned TITLE_ON2 : 1;
		unsigned TITLE_LINE2 : 4;	unsigned TITLE_BLINK2 : 1;	unsigned TITLE_COLOR2 : 3;
		unsigned TITLE_LINE2_CH1 : 8;
		unsigned TITLE_LINE2_CH2 : 8;
		unsigned TITLE_LINE2_CH3 : 8;
		unsigned TITLE_LINE2_CH4 : 8;
		unsigned TITLE_LINE2_CH5 : 8;
		unsigned TITLE_LINE2_CH6 : 8;
		unsigned TITLE_LINE2_CH7 : 8;
		unsigned TITLE_LINE2_CH8 : 8;
		unsigned TITLE_LINE2_CH9 : 8;
		unsigned TITLE_LINE2_CH10 : 8;
		unsigned TITLE_LINE2_CH11 : 8;
		unsigned TITLE_LINE2_CH12 : 8;
		unsigned TITLE_LINE2_CH13 : 8;
		unsigned TITLE_LINE2_CH14 : 8;
		unsigned TITLE_LINE2_CH15 : 8;
		unsigned TITLE_LINE2_CH16 : 8;
		unsigned TITLE_LINE2_CH17 : 8;
		unsigned TITLE_LINE2_CH18 : 8;
		unsigned TITLE_LINE2_CH19 : 8;
		unsigned TITLE_LINE2_CH20 : 8;
		unsigned TITLE_H_POS3 : 5;	unsigned : 2;	unsigned TITLE_ON3 : 1;
		unsigned TITLE_LINE3 : 4;	unsigned TITLE_BLINK3 : 1;	unsigned TITLE_COLOR3 : 3;
		unsigned TITLE_LINE3_CH1 : 8;
		unsigned TITLE_LINE3_CH2 : 8;
		unsigned TITLE_LINE3_CH3 : 8;
		unsigned TITLE_LINE3_CH4 : 8;
		unsigned TITLE_LINE3_CH5 : 8;
		unsigned TITLE_LINE3_CH6 : 8;
		unsigned TITLE_LINE3_CH7 : 8;
		unsigned TITLE_LINE3_CH8 : 8;
		unsigned TITLE_LINE3_CH9 : 8;
		unsigned TITLE_LINE3_CH10 : 8;
		unsigned TITLE_LINE3_CH11 : 8;
		unsigned TITLE_LINE3_CH12 : 8;
		unsigned TITLE_LINE3_CH13 : 8;
		unsigned TITLE_LINE3_CH14 : 8;
		unsigned TITLE_LINE3_CH15 : 8;
		unsigned TITLE_LINE3_CH16 : 8;
		unsigned TITLE_LINE3_CH17 : 8;
		unsigned TITLE_LINE3_CH18 : 8;
		unsigned TITLE_LINE3_CH19 : 8;
		unsigned TITLE_LINE3_CH20 : 8;
		unsigned TITLE_H_POS4 : 5;	unsigned : 2;	unsigned TITLE_ON4 : 1;
		unsigned TITLE_LINE4 : 4;	unsigned TITLE_BLINK4 : 1;	unsigned TITLE_COLOR4 : 3;
		unsigned TITLE_LINE4_CH1 : 8;
		unsigned TITLE_LINE4_CH2 : 8;
		unsigned TITLE_LINE4_CH3 : 8;
		unsigned TITLE_LINE4_CH4 : 8;
		unsigned TITLE_LINE4_CH5 : 8;
		unsigned TITLE_LINE4_CH6 : 8;
		unsigned TITLE_LINE4_CH7 : 8;
		unsigned TITLE_LINE4_CH8 : 8;
		unsigned TITLE_LINE4_CH9 : 8;
		unsigned TITLE_LINE4_CH10 : 8;
		unsigned TITLE_LINE4_CH11 : 8;
		unsigned TITLE_LINE4_CH12 : 8;
		unsigned TITLE_LINE4_CH13 : 8;
		unsigned TITLE_LINE4_CH14 : 8;
		unsigned TITLE_LINE4_CH15 : 8;
		unsigned TITLE_LINE4_CH16 : 8;
		unsigned TITLE_LINE4_CH17 : 8;
		unsigned TITLE_LINE4_CH18 : 8;
		unsigned TITLE_LINE4_CH19 : 8;
		unsigned TITLE_LINE4_CH20 : 8;
		unsigned TITLE_H_POS5 : 5;	unsigned : 2;	unsigned TITLE_ON5 : 1;
		unsigned TITLE_LINE5 : 4;	unsigned TITLE_BLINK5 : 1;	unsigned TITLE_COLOR5 : 3;
		unsigned TITLE_LINE5_CH1 : 8;
		unsigned TITLE_LINE5_CH2 : 8;
		unsigned TITLE_LINE5_CH3 : 8;
		unsigned TITLE_LINE5_CH4 : 8;
		unsigned TITLE_LINE5_CH5 : 8;
		unsigned TITLE_LINE5_CH6 : 8;
		unsigned TITLE_LINE5_CH7 : 8;
		unsigned TITLE_LINE5_CH8 : 8;
		unsigned TITLE_LINE5_CH9 : 8;
		unsigned TITLE_LINE5_CH10 : 8;
		unsigned TITLE_LINE5_CH11 : 8;
		unsigned TITLE_LINE5_CH12 : 8;
		unsigned TITLE_LINE5_CH13 : 8;
		unsigned TITLE_LINE5_CH14 : 8;
		unsigned TITLE_LINE5_CH15 : 8;
		unsigned TITLE_LINE5_CH16 : 8;
		unsigned TITLE_LINE5_CH17 : 8;
		unsigned TITLE_LINE5_CH18 : 8;
		unsigned TITLE_LINE5_CH19 : 8;
		unsigned TITLE_LINE5_CH20 : 8;
		unsigned TITLE_H_POS6 : 5;	unsigned : 2;	unsigned TITLE_ON6 : 1;
		unsigned TITLE_LINE6 : 4;	unsigned TITLE_BLINK6 : 1;	unsigned TITLE_COLOR6 : 3;
		unsigned TITLE_LINE6_CH1 : 8;
		unsigned TITLE_LINE6_CH2 : 8;
		unsigned TITLE_LINE6_CH3 : 8;
		unsigned TITLE_LINE6_CH4 : 8;
		unsigned TITLE_LINE6_CH5 : 8;
		unsigned TITLE_LINE6_CH6 : 8;
		unsigned TITLE_LINE6_CH7 : 8;
		unsigned TITLE_LINE6_CH8 : 8;
		unsigned TITLE_LINE6_CH9 : 8;
		unsigned TITLE_LINE6_CH10 : 8;
		unsigned TITLE_LINE6_CH11 : 8;
		unsigned TITLE_LINE6_CH12 : 8;
		unsigned TITLE_LINE6_CH13 : 8;
		unsigned TITLE_LINE6_CH14 : 8;
		unsigned TITLE_LINE6_CH15 : 8;
		unsigned TITLE_LINE6_CH16 : 8;
		unsigned TITLE_LINE6_CH17 : 8;
		unsigned TITLE_LINE6_CH18 : 8;
		unsigned TITLE_LINE6_CH19 : 8;
		unsigned TITLE_LINE6_CH20 : 8;
		unsigned TITLE_H_POS7 : 5;	unsigned : 2;	unsigned TITLE_ON7 : 1;
		unsigned TITLE_LINE7 : 4;	unsigned TITLE_BLINK7 : 1;	unsigned TITLE_COLOR7 : 3;
		unsigned TITLE_LINE7_CH1 : 8;
		unsigned TITLE_LINE7_CH2 : 8;
		unsigned TITLE_LINE7_CH3 : 8;
		unsigned TITLE_LINE7_CH4 : 8;
		unsigned TITLE_LINE7_CH5 : 8;
		unsigned TITLE_LINE7_CH6 : 8;
		unsigned TITLE_LINE7_CH7 : 8;
		unsigned TITLE_LINE7_CH8 : 8;
		unsigned TITLE_LINE7_CH9 : 8;
		unsigned TITLE_LINE7_CH10 : 8;
		unsigned TITLE_LINE7_CH11 : 8;
		unsigned TITLE_LINE7_CH12 : 8;
		unsigned TITLE_LINE7_CH13 : 8;
		unsigned TITLE_LINE7_CH14 : 8;
		unsigned TITLE_LINE7_CH15 : 8;
		unsigned TITLE_LINE7_CH16 : 8;
		unsigned TITLE_LINE7_CH17 : 8;
		unsigned TITLE_LINE7_CH18 : 8;
		unsigned TITLE_LINE7_CH19 : 8;
		unsigned TITLE_LINE7_CH20 : 8;
		unsigned TITLE_H_POS8 : 5;	unsigned : 2;	unsigned TITLE_ON8 : 1;
		unsigned TITLE_LINE8 : 4;	unsigned TITLE_BLINK8 : 1;	unsigned TITLE_COLOR8 : 3;
		unsigned TITLE_LINE8_CH1 : 8;
		unsigned TITLE_LINE8_CH2 : 8;
		unsigned TITLE_LINE8_CH3 : 8;
		unsigned TITLE_LINE8_CH4 : 8;
		unsigned TITLE_LINE8_CH5 : 8;
		unsigned TITLE_LINE8_CH6 : 8;
		unsigned TITLE_LINE8_CH7 : 8;
		unsigned TITLE_LINE8_CH8 : 8;
		unsigned TITLE_LINE8_CH9 : 8;
		unsigned TITLE_LINE8_CH10 : 8;
		unsigned TITLE_LINE8_CH11 : 8;
		unsigned TITLE_LINE8_CH12 : 8;
		unsigned TITLE_LINE8_CH13 : 8;
		unsigned TITLE_LINE8_CH14 : 8;
		unsigned TITLE_LINE8_CH15 : 8;
		unsigned TITLE_LINE8_CH16 : 8;
		unsigned TITLE_LINE8_CH17 : 8;
		unsigned TITLE_LINE8_CH18 : 8;
		unsigned TITLE_LINE8_CH19 : 8;
		unsigned TITLE_LINE8_CH20 : 8;
		unsigned TITLE_H_POS9 : 5;	unsigned : 2;	unsigned TITLE_ON9 : 1;
		unsigned TITLE_LINE9 : 4;	unsigned TITLE_BLINK9 : 1;	unsigned TITLE_COLOR9 : 3;
		unsigned TITLE_LINE9_CH1 : 8;
		unsigned TITLE_LINE9_CH2 : 8;
		unsigned TITLE_LINE9_CH3 : 8;
		unsigned TITLE_LINE9_CH4 : 8;
		unsigned TITLE_LINE9_CH5 : 8;
		unsigned TITLE_LINE9_CH6 : 8;
		unsigned TITLE_LINE9_CH7 : 8;
		unsigned TITLE_LINE9_CH8 : 8;
		unsigned TITLE_LINE9_CH9 : 8;
		unsigned TITLE_LINE9_CH10 : 8;
		unsigned TITLE_LINE9_CH11 : 8;
		unsigned TITLE_LINE9_CH12 : 8;
		unsigned TITLE_LINE9_CH13 : 8;
		unsigned TITLE_LINE9_CH14 : 8;
		unsigned TITLE_LINE9_CH15 : 8;
		unsigned TITLE_LINE9_CH16 : 8;
		unsigned TITLE_LINE9_CH17 : 8;
		unsigned TITLE_LINE9_CH18 : 8;
		unsigned TITLE_LINE9_CH19 : 8;
		unsigned TITLE_LINE9_CH20 : 8;
		unsigned TITLE_H_POS10 : 5;	unsigned : 2;	unsigned TITLE_ON10 : 1;
		unsigned TITLE_LINE10 : 4;	unsigned TITLE_BLINK10 : 1;	unsigned TITLE_COLOR10 : 3;
		unsigned TITLE_LINE10_CH1 : 8;
		unsigned TITLE_LINE10_CH2 : 8;
		unsigned TITLE_LINE10_CH3 : 8;
		unsigned TITLE_LINE10_CH4 : 8;
		unsigned TITLE_LINE10_CH5 : 8;
		unsigned TITLE_LINE10_CH6 : 8;
		unsigned TITLE_LINE10_CH7 : 8;
		unsigned TITLE_LINE10_CH8 : 8;
		unsigned TITLE_LINE10_CH9 : 8;
		unsigned TITLE_LINE10_CH10 : 8;
		unsigned TITLE_LINE10_CH11 : 8;
		unsigned TITLE_LINE10_CH12 : 8;
		unsigned TITLE_LINE10_CH13 : 8;
		unsigned TITLE_LINE10_CH14 : 8;
		unsigned TITLE_LINE10_CH15 : 8;
		unsigned TITLE_LINE10_CH16 : 8;
		unsigned TITLE_LINE10_CH17 : 8;
		unsigned TITLE_LINE10_CH18 : 8;
		unsigned TITLE_LINE10_CH19 : 8;
		unsigned TITLE_LINE10_CH20 : 8;
		unsigned : 8;
		unsigned MUTE_ON : 1;	unsigned : 7;
		unsigned MASK_CL_ON : 1;	unsigned : 7;
		unsigned MASK_ON01 : 1;	unsigned MASK_DISP_ON01 : 1;	unsigned : 3;	unsigned MASK_I01 : 1;	unsigned MASK_TRANS01 : 1;	unsigned MASK_MOSAIC01 : 1;
		unsigned MASK_COLOR_ON01 : 4;	unsigned MASK_COLOR_OFF01 : 4;
		unsigned MASK_X_POS01 : 8;
		unsigned MASK_Y_POS01 : 8;
		unsigned MASK_WIDTH01 : 8;
		unsigned MASK_HEIGHT01 : 8;
		unsigned MASK_PAN_ANGLE01 : 16;
		unsigned MASK_TILT_ANGLE01 : 16;
		unsigned MASK_ZOOM01 : 16;
		unsigned MASK_ON02 : 1;	unsigned MASK_DISP_ON02 : 1;	unsigned : 3;	unsigned MASK_I02 : 1;	unsigned MASK_TRANS02 : 1;	unsigned MASK_MOSAIC02 : 1;
		unsigned MASK_COLOR_ON02 : 4;	unsigned MASK_COLOR_OFF02 : 4;
		unsigned MASK_X_POS02 : 8;
		unsigned MASK_Y_POS02 : 8;
		unsigned MASK_WIDTH02 : 8;
		unsigned MASK_HEIGHT02 : 8;
		unsigned MASK_PAN_ANGLE02 : 16;
		unsigned MASK_TILT_ANGLE02 : 16;
		unsigned MASK_ZOOM02 : 16;
		unsigned MASK_ON03 : 1;	unsigned MASK_DISP_ON03 : 1;	unsigned : 3;	unsigned MASK_I03 : 1;	unsigned MASK_TRANS03 : 1;	unsigned MASK_MOSAIC03 : 1;
		unsigned MASK_COLOR_ON03 : 4;	unsigned MASK_COLOR_OFF03 : 4;
		unsigned MASK_X_POS03 : 8;
		unsigned MASK_Y_POS03 : 8;
		unsigned MASK_WIDTH03 : 8;
		unsigned MASK_HEIGHT03 : 8;
		unsigned MASK_PAN_ANGLE03 : 16;
		unsigned MASK_TILT_ANGLE03 : 16;
		unsigned MASK_ZOOM03 : 16;
		unsigned MASK_ON04 : 1;	unsigned MASK_DISP_ON04 : 1;	unsigned : 3;	unsigned MASK_I04 : 1;	unsigned MASK_TRANS04 : 1;	unsigned MASK_MOSAIC04 : 1;
		unsigned MASK_COLOR_ON04 : 4;	unsigned MASK_COLOR_OFF04 : 4;
		unsigned MASK_X_POS04 : 8;
		unsigned MASK_Y_POS04 : 8;
		unsigned MASK_WIDTH04 : 8;
		unsigned MASK_HEIGHT04 : 8;
		unsigned MASK_PAN_ANGLE04 : 16;
		unsigned MASK_TILT_ANGLE04 : 16;
		unsigned MASK_ZOOM04 : 16;
		unsigned MASK_ON05 : 1;	unsigned MASK_DISP_ON05 : 1;	unsigned : 3;	unsigned MASK_I05 : 1;	unsigned MASK_TRANS05 : 1;	unsigned MASK_MOSAIC05 : 1;
		unsigned MASK_COLOR_ON05 : 4;	unsigned MASK_COLOR_OFF05 : 4;
		unsigned MASK_X_POS05 : 8;
		unsigned MASK_Y_POS05 : 8;
		unsigned MASK_WIDTH05 : 8;
		unsigned MASK_HEIGHT05 : 8;
		unsigned MASK_PAN_ANGLE05 : 16;
		unsigned MASK_TILT_ANGLE05 : 16;
		unsigned MASK_ZOOM05 : 16;
		unsigned MASK_ON06 : 1;	unsigned MASK_DISP_ON06 : 1;	unsigned : 3;	unsigned MASK_I06 : 1;	unsigned MASK_TRANS06 : 1;	unsigned MASK_MOSAIC06 : 1;
		unsigned MASK_COLOR_ON06 : 4;	unsigned MASK_COLOR_OFF06 : 4;
		unsigned MASK_X_POS06 : 8;
		unsigned MASK_Y_POS06 : 8;
		unsigned MASK_WIDTH06 : 8;
		unsigned MASK_HEIGHT06 : 8;
		unsigned MASK_PAN_ANGLE06 : 16;
		unsigned MASK_TILT_ANGLE06 : 16;
		unsigned MASK_ZOOM06 : 16;
		unsigned MASK_ON07 : 1;	unsigned MASK_DISP_ON07 : 1;	unsigned : 3;	unsigned MASK_I07 : 1;	unsigned MASK_TRANS07 : 1;	unsigned MASK_MOSAIC07 : 1;
		unsigned MASK_COLOR_ON07 : 4;	unsigned MASK_COLOR_OFF07 : 4;
		unsigned MASK_X_POS07 : 8;
		unsigned MASK_Y_POS07 : 8;
		unsigned MASK_WIDTH07 : 8;
		unsigned MASK_HEIGHT07 : 8;
		unsigned MASK_PAN_ANGLE07 : 16;
		unsigned MASK_TILT_ANGLE07 : 16;
		unsigned MASK_ZOOM07 : 16;
		unsigned MASK_ON08 : 1;	unsigned MASK_DISP_ON08 : 1;	unsigned : 3;	unsigned MASK_I08 : 1;	unsigned MASK_TRANS08 : 1;	unsigned MASK_MOSAIC08 : 1;
		unsigned MASK_COLOR_ON08 : 4;	unsigned MASK_COLOR_OFF08 : 4;
		unsigned MASK_X_POS08 : 8;
		unsigned MASK_Y_POS08 : 8;
		unsigned MASK_WIDTH08 : 8;
		unsigned MASK_HEIGHT08 : 8;
		unsigned MASK_PAN_ANGLE08 : 16;
		unsigned MASK_TILT_ANGLE08 : 16;
		unsigned MASK_ZOOM08 : 16;
		unsigned MASK_ON11 : 1;	unsigned MASK_DISP_ON11 : 1;	unsigned : 3;	unsigned MASK_I11 : 1;	unsigned MASK_TRANS11 : 1;	unsigned MASK_MOSAIC11 : 1;
		unsigned MASK_COLOR_ON11 : 4;	unsigned MASK_COLOR_OFF11 : 4;
		unsigned MASK_X_POS11 : 8;
		unsigned MASK_Y_POS11 : 8;
		unsigned MASK_WIDTH11 : 8;
		unsigned MASK_HEIGHT11 : 8;
		unsigned MASK_PAN_ANGLE11 : 16;
		unsigned MASK_TILT_ANGLE11 : 16;
		unsigned MASK_ZOOM11 : 16;
		unsigned MASK_ON12 : 1;	unsigned MASK_DISP_ON12 : 1;	unsigned : 3;	unsigned MASK_I12 : 1;	unsigned MASK_TRANS12 : 1;	unsigned MASK_MOSAIC12 : 1;
		unsigned MASK_COLOR_ON12 : 4;	unsigned MASK_COLOR_OFF12 : 4;
		unsigned MASK_X_POS12 : 8;
		unsigned MASK_Y_POS12 : 8;
		unsigned MASK_WIDTH12 : 8;
		unsigned MASK_HEIGHT12 : 8;
		unsigned MASK_PAN_ANGLE12 : 16;
		unsigned MASK_TILT_ANGLE12 : 16;
		unsigned MASK_ZOOM12 : 16;
		unsigned MASK_ON13 : 1;	unsigned MASK_DISP_ON13 : 1;	unsigned : 3;	unsigned MASK_I13 : 1;	unsigned MASK_TRANS13 : 1;	unsigned MASK_MOSAIC13 : 1;
		unsigned MASK_COLOR_ON13 : 4;	unsigned MASK_COLOR_OFF13 : 4;
		unsigned MASK_X_POS13 : 8;
		unsigned MASK_Y_POS13 : 8;
		unsigned MASK_WIDTH13 : 8;
		unsigned MASK_HEIGHT13 : 8;
		unsigned MASK_PAN_ANGLE13 : 16;
		unsigned MASK_TILT_ANGLE13 : 16;
		unsigned MASK_ZOOM13 : 16;
		unsigned MASK_ON14 : 1;	unsigned MASK_DISP_ON14 : 1;	unsigned : 3;	unsigned MASK_I14 : 1;	unsigned MASK_TRANS14 : 1;	unsigned MASK_MOSAIC14 : 1;
		unsigned MASK_COLOR_ON14 : 4;	unsigned MASK_COLOR_OFF14 : 4;
		unsigned MASK_X_POS14 : 8;
		unsigned MASK_Y_POS14 : 8;
		unsigned MASK_WIDTH14 : 8;
		unsigned MASK_HEIGHT14 : 8;
		unsigned MASK_PAN_ANGLE14 : 16;
		unsigned MASK_TILT_ANGLE14 : 16;
		unsigned MASK_ZOOM14 : 16;
		unsigned MASK_ON15 : 1;	unsigned MASK_DISP_ON15 : 1;	unsigned : 3;	unsigned MASK_I15 : 1;	unsigned MASK_TRANS15 : 1;	unsigned MASK_MOSAIC15 : 1;
		unsigned MASK_COLOR_ON15 : 4;	unsigned MASK_COLOR_OFF15 : 4;
		unsigned MASK_X_POS15 : 8;
		unsigned MASK_Y_POS15 : 8;
		unsigned MASK_WIDTH15 : 8;
		unsigned MASK_HEIGHT15 : 8;
		unsigned MASK_PAN_ANGLE15 : 16;
		unsigned MASK_TILT_ANGLE15 : 16;
		unsigned MASK_ZOOM15 : 16;
		unsigned MASK_ON16 : 1;	unsigned MASK_DISP_ON16 : 1;	unsigned : 3;	unsigned MASK_I16 : 1;	unsigned MASK_TRANS16 : 1;	unsigned MASK_MOSAIC16 : 1;
		unsigned MASK_COLOR_ON16 : 4;	unsigned MASK_COLOR_OFF16 : 4;
		unsigned MASK_X_POS16 : 8;
		unsigned MASK_Y_POS16 : 8;
		unsigned MASK_WIDTH16 : 8;
		unsigned MASK_HEIGHT16 : 8;
		unsigned MASK_PAN_ANGLE16 : 16;
		unsigned MASK_TILT_ANGLE16 : 16;
		unsigned MASK_ZOOM16 : 16;
		unsigned MASK_ON17 : 1;	unsigned MASK_DISP_ON17 : 1;	unsigned : 3;	unsigned MASK_I17 : 1;	unsigned MASK_TRANS17 : 1;	unsigned MASK_MOSAIC17 : 1;
		unsigned MASK_COLOR_ON17 : 4;	unsigned MASK_COLOR_OFF17 : 4;
		unsigned MASK_X_POS17 : 8;
		unsigned MASK_Y_POS17 : 8;
		unsigned MASK_WIDTH17 : 8;
		unsigned MASK_HEIGHT17 : 8;
		unsigned MASK_PAN_ANGLE17 : 16;
		unsigned MASK_TILT_ANGLE17 : 16;
		unsigned MASK_ZOOM17 : 16;
		unsigned MASK_ON18 : 1;	unsigned MASK_DISP_ON18 : 1;	unsigned : 3;	unsigned MASK_I18 : 1;	unsigned MASK_TRANS18 : 1;	unsigned MASK_MOSAIC18 : 1;
		unsigned MASK_COLOR_ON18 : 4;	unsigned MASK_COLOR_OFF18 : 4;
		unsigned MASK_X_POS18 : 8;
		unsigned MASK_Y_POS18 : 8;
		unsigned MASK_WIDTH18 : 8;
		unsigned MASK_HEIGHT18 : 8;
		unsigned MASK_PAN_ANGLE18 : 16;
		unsigned MASK_TILT_ANGLE18 : 16;
		unsigned MASK_ZOOM18 : 16;
		unsigned MASK_ON21 : 1;	unsigned MASK_DISP_ON21 : 1;	unsigned : 3;	unsigned MASK_I21 : 1;	unsigned MASK_TRANS21 : 1;	unsigned MASK_MOSAIC21 : 1;
		unsigned MASK_COLOR_ON21 : 4;	unsigned MASK_COLOR_OFF21 : 4;
		unsigned MASK_X_POS21 : 8;
		unsigned MASK_Y_POS21 : 8;
		unsigned MASK_WIDTH21 : 8;
		unsigned MASK_HEIGHT21 : 8;
		unsigned MASK_PAN_ANGLE21 : 16;
		unsigned MASK_TILT_ANGLE21 : 16;
		unsigned MASK_ZOOM21 : 16;
		unsigned MASK_ON22 : 1;	unsigned MASK_DISP_ON22 : 1;	unsigned : 3;	unsigned MASK_I22 : 1;	unsigned MASK_TRANS22 : 1;	unsigned MASK_MOSAIC22 : 1;
		unsigned MASK_COLOR_ON22 : 4;	unsigned MASK_COLOR_OFF22 : 4;
		unsigned MASK_X_POS22 : 8;
		unsigned MASK_Y_POS22 : 8;
		unsigned MASK_WIDTH22 : 8;
		unsigned MASK_HEIGHT22 : 8;
		unsigned MASK_PAN_ANGLE22 : 16;
		unsigned MASK_TILT_ANGLE22 : 16;
		unsigned MASK_ZOOM22 : 16;
		unsigned MASK_ON23 : 1;	unsigned MASK_DISP_ON23 : 1;	unsigned : 3;	unsigned MASK_I23 : 1;	unsigned MASK_TRANS23 : 1;	unsigned MASK_MOSAIC23 : 1;
		unsigned MASK_COLOR_ON23 : 4;	unsigned MASK_COLOR_OFF23 : 4;
		unsigned MASK_X_POS23 : 8;
		unsigned MASK_Y_POS23 : 8;
		unsigned MASK_WIDTH23 : 8;
		unsigned MASK_HEIGHT23 : 8;
		unsigned MASK_PAN_ANGLE23 : 16;
		unsigned MASK_TILT_ANGLE23 : 16;
		unsigned MASK_ZOOM23 : 16;
		unsigned MASK_ON24 : 1;	unsigned MASK_DISP_ON24 : 1;	unsigned : 3;	unsigned MASK_I24 : 1;	unsigned MASK_TRANS24 : 1;	unsigned MASK_MOSAIC24 : 1;
		unsigned MASK_COLOR_ON24 : 4;	unsigned MASK_COLOR_OFF24 : 4;
		unsigned MASK_X_POS24 : 8;
		unsigned MASK_Y_POS24 : 8;
		unsigned MASK_WIDTH24 : 8;
		unsigned MASK_HEIGHT24 : 8;
		unsigned MASK_PAN_ANGLE24 : 16;
		unsigned MASK_TILT_ANGLE24 : 16;
		unsigned MASK_ZOOM24 : 16;
		unsigned MASK_ON25 : 1;	unsigned MASK_DISP_ON25 : 1;	unsigned : 3;	unsigned MASK_I25 : 1;	unsigned MASK_TRANS25 : 1;	unsigned MASK_MOSAIC25 : 1;
		unsigned MASK_COLOR_ON25 : 4;	unsigned MASK_COLOR_OFF25 : 4;
		unsigned MASK_X_POS25 : 8;
		unsigned MASK_Y_POS25 : 8;
		unsigned MASK_WIDTH25 : 8;
		unsigned MASK_HEIGHT25 : 8;
		unsigned MASK_PAN_ANGLE25 : 16;
		unsigned MASK_TILT_ANGLE25 : 16;
		unsigned MASK_ZOOM25 : 16;
		unsigned MASK_ON26 : 1;	unsigned MASK_DISP_ON26 : 1;	unsigned : 3;	unsigned MASK_I26 : 1;	unsigned MASK_TRANS26 : 1;	unsigned MASK_MOSAIC26 : 1;
		unsigned MASK_COLOR_ON26 : 4;	unsigned MASK_COLOR_OFF26 : 4;
		unsigned MASK_X_POS26 : 8;
		unsigned MASK_Y_POS26 : 8;
		unsigned MASK_WIDTH26 : 8;
		unsigned MASK_HEIGHT26 : 8;
		unsigned MASK_PAN_ANGLE26 : 16;
		unsigned MASK_TILT_ANGLE26 : 16;
		unsigned MASK_ZOOM26 : 16;
		unsigned MASK_ON27 : 1;	unsigned MASK_DISP_ON27 : 1;	unsigned : 3;	unsigned MASK_I27 : 1;	unsigned MASK_TRANS27 : 1;	unsigned MASK_MOSAIC27 : 1;
		unsigned MASK_COLOR_ON27 : 4;	unsigned MASK_COLOR_OFF27 : 4;
		unsigned MASK_X_POS27 : 8;
		unsigned MASK_Y_POS27 : 8;
		unsigned MASK_WIDTH27 : 8;
		unsigned MASK_HEIGHT27 : 8;
		unsigned MASK_PAN_ANGLE27 : 16;
		unsigned MASK_TILT_ANGLE27 : 16;
		unsigned MASK_ZOOM27 : 16;
		unsigned MASK_ON28 : 1;	unsigned MASK_DISP_ON28 : 1;	unsigned : 3;	unsigned MASK_I28 : 1;	unsigned MASK_TRANS28 : 1;	unsigned MASK_MOSAIC28 : 1;
		unsigned MASK_COLOR_ON28 : 4;	unsigned MASK_COLOR_OFF28 : 4;
		unsigned MASK_X_POS28 : 8;
		unsigned MASK_Y_POS28 : 8;
		unsigned MASK_WIDTH28 : 8;
		unsigned MASK_HEIGHT28 : 8;
		unsigned MASK_PAN_ANGLE28 : 16;
		unsigned MASK_TILT_ANGLE28 : 16;
		unsigned MASK_ZOOM28 : 16;
		unsigned CAM_ID_H : 8;
		unsigned CAM_ID_L : 8;
		unsigned MD_ON : 1;	unsigned MD_DISP : 3;	unsigned MD_FRAME : 4;
		unsigned MD_THRS_VAL : 8;
		unsigned MD_INTERVAL_TIME : 8;

		unsigned MD_SRT_H_POS1 : 8;
		unsigned MD_SRT_V_POS1 : 8;
		unsigned MD_END_H_POS1 : 8;
		unsigned MD_END_V_POS1 : 8;

		unsigned MD_SRT_H_POS2 : 8;
		unsigned MD_SRT_V_POS2 : 8;
		unsigned MD_STP_H_POS2 : 8;
		unsigned MD_STP_V_POS2 : 8;

		unsigned MD_SRT_H_POS3 : 8;
		unsigned MD_SRT_V_POS3 : 8;
		unsigned MD_STP_H_POS3 : 8;
		unsigned MD_STP_V_POS3 : 8;

		unsigned MD_SRT_H_POS4 : 8;
		unsigned MD_SRT_V_POS4 : 8;
		unsigned MD_STP_H_POS4 : 8;
		unsigned MD_STP_V_POS4 : 8;

		unsigned CZP_ON : 1;	unsigned : 7;
		unsigned CZP_INTERVAL_TIME : 8;
		unsigned CFP_ON : 1;	unsigned : 7;
		unsigned CFP_INTERVAL_TIME : 8;
		unsigned CE_ON : 1;	unsigned : 7;
		unsigned CE_THRS_VAL : 8;			//CE_THRS_HIGH  : First byte from top threshold value	(Use EH6300)
		unsigned CE_Y_HI : 8;				//CE_THRS_MID   : Second byte from top threshold value	(Use EH6300)
		unsigned CE_CR_HI : 8;				//CE_THRS_LOW   : third byte from top threshold value	(Use EH6300)
		unsigned CE_CB_HI : 8;				//CE_COLOR_HIGH : Color specification for high-intensity(Use EH6300)
		unsigned CE_Y_LI : 8;				//CE_COLOR_LOW  : Color specification for low-intensity	(Use EH6300)
		unsigned CE_CR_LI : 8;
		unsigned CE_CB_LI : 8;
		unsigned CS_LEVEL : 2;	unsigned : 6;
		unsigned CS_SET_VAL : 8;
		unsigned COLOR_GAIN : 8;
		unsigned COLOR_HUE : 8;
		unsigned GAM_OFFSET : 7;
		unsigned GAM_OFFSET_S : 1;
		unsigned : 8;
		unsigned EX_EXPCOMP_RESET : 8;
		unsigned EX_EXPCOMP_DIRECT : 8;
		unsigned EX_EXPAP_RESET : 8;
		unsigned EX_EXPAP_DIRECT : 8;
		unsigned EX_AICR_ON2OFF : 8;
		unsigned EX_AICR_OFF2ON : 8;
		unsigned EX_COLOR_GAIN : 8;
		unsigned EX_COLOR_HUE : 8;
		unsigned STB_ON : 1;	unsigned STB_HOLD : 1;	unsigned : 6;
		unsigned ZOOM_POS01 : 16;
		unsigned FOCUS_POS01 : 16;
		unsigned DZOOM_ON01 : 1;	unsigned F_MODE01 : 2;	unsigned AF_MODE01 : 2;	unsigned COMP_ON01 : 1;	unsigned BLC_ON01 : 1;	unsigned ASS_ON01 : 1;
		unsigned SHUTTER_STEP01 : 8;
		unsigned BRIGHT_STEP01 : 8;
		unsigned IRIS_STEP01 : 8;
		unsigned GAIN_STEP01 : 8;
		unsigned EXP_COMP_VAL01 : 8;
		unsigned WB_MODE01 : 4;	unsigned ICR_ON01 : 1;	unsigned WD_MODE01 : 2;	unsigned DEFOG_ON01 : 1;
		unsigned R_GAIN01 : 8;
		unsigned B_GAIN01 : 8;
		unsigned APER_GAIN01 : 8;
		unsigned WD_BRT_L01 : 3;	unsigned WD_BRT_COMP01 : 2;	unsigned WD_COMP_L01 : 2;	unsigned : 1;
		unsigned AE_MODE01 : 3;		unsigned : 5;
		unsigned ZOOM_POS02 : 16;
		unsigned FOCUS_POS02 : 16;
		unsigned DZOOM_ON02 : 1;	unsigned F_MODE02 : 2;	unsigned AF_MODE02 : 2;	unsigned COMP_ON02 : 1;	unsigned BLC_ON02 : 1;	unsigned ASS_ON02 : 1;
		unsigned SHUTTER_STEP02 : 8;
		unsigned BRIGHT_STEP02 : 8;
		unsigned IRIS_STEP02 : 8;
		unsigned GAIN_STEP02 : 8;
		unsigned EXP_COMP_VAL02 : 8;
		unsigned WB_MODE02 : 4;	unsigned ICR_ON02 : 1;	unsigned WD_MODE02 : 2;	unsigned DEFOG_ON02 : 1;
		unsigned R_GAIN02 : 8;
		unsigned B_GAIN02 : 8;
		unsigned APER_GAIN02 : 8;
		unsigned WD_BRT_L02 : 3;	unsigned WD_BRT_COMP02 : 2;	unsigned WD_COMP_L02 : 2;	unsigned : 1;
		unsigned AE_MODE02 : 3;		unsigned : 5;
		unsigned ZOOM_POS03 : 16;
		unsigned FOCUS_POS03 : 16;
		unsigned DZOOM_ON03 : 1;	unsigned F_MODE03 : 2;	unsigned AF_MODE03 : 2;	unsigned COMP_ON03 : 1;	unsigned BLC_ON03 : 1;	unsigned ASS_ON03 : 1;
		unsigned SHUTTER_STEP03 : 8;
		unsigned BRIGHT_STEP03 : 8;
		unsigned IRIS_STEP03 : 8;
		unsigned GAIN_STEP03 : 8;
		unsigned EXP_COMP_VAL03 : 8;
		unsigned WB_MODE03 : 4;	unsigned ICR_ON03 : 1;	unsigned WD_MODE03 : 2;	unsigned DEFOG_ON03 : 1;
		unsigned R_GAIN03 : 8;
		unsigned B_GAIN03 : 8;
		unsigned APER_GAIN03 : 8;
		unsigned WD_BRT_L03 : 3;	unsigned WD_BRT_COMP03 : 2;	unsigned WD_COMP_L03 : 2;	unsigned : 1;
		unsigned AE_MODE03 : 3;		unsigned : 5;
		unsigned ZOOM_POS04 : 16;
		unsigned FOCUS_POS04 : 16;
		unsigned DZOOM_ON04 : 1;	unsigned F_MODE04 : 2;	unsigned AF_MODE04 : 2;	unsigned COMP_ON04 : 1;	unsigned BLC_ON04 : 1;	unsigned ASS_ON04 : 1;
		unsigned SHUTTER_STEP04 : 8;
		unsigned BRIGHT_STEP04 : 8;
		unsigned IRIS_STEP04 : 8;
		unsigned GAIN_STEP04 : 8;
		unsigned EXP_COMP_VAL04 : 8;
		unsigned WB_MODE04 : 4;	unsigned ICR_ON04 : 1;	unsigned WD_MODE04 : 2;	unsigned DEFOG_ON04 : 1;
		unsigned R_GAIN04 : 8;
		unsigned B_GAIN04 : 8;
		unsigned APER_GAIN04 : 8;
		unsigned WD_BRT_L04 : 3;	unsigned WD_BRT_COMP04 : 2;	unsigned WD_COMP_L04 : 2;	unsigned : 1;
		unsigned AE_MODE04 : 3;		unsigned : 5;
		unsigned ZOOM_POS05 : 16;
		unsigned FOCUS_POS05 : 16;
		unsigned DZOOM_ON05 : 1;	unsigned F_MODE05 : 2;	unsigned AF_MODE05 : 2;	unsigned COMP_ON05 : 1;	unsigned BLC_ON05 : 1;	unsigned ASS_ON05 : 1;
		unsigned SHUTTER_STEP05 : 8;
		unsigned BRIGHT_STEP05 : 8;
		unsigned IRIS_STEP05 : 8;
		unsigned GAIN_STEP05 : 8;
		unsigned EXP_COMP_VAL05 : 8;
		unsigned WB_MODE05 : 4;	unsigned ICR_ON05 : 1;	unsigned WD_MODE05 : 2;	unsigned DEFOG_ON05 : 1;
		unsigned R_GAIN05 : 8;
		unsigned B_GAIN05 : 8;
		unsigned APER_GAIN05 : 8;
		unsigned WD_BRT_L05 : 3;	unsigned WD_BRT_COMP05 : 2;	unsigned WD_COMP_L05 : 2;	unsigned : 1;
		unsigned AE_MODE05 : 3;		unsigned : 5;
		unsigned ZOOM_POS06 : 16;
		unsigned FOCUS_POS06 : 16;
		unsigned DZOOM_ON06 : 1;	unsigned F_MODE06 : 2;	unsigned AF_MODE06 : 2;	unsigned COMP_ON06 : 1;	unsigned BLC_ON06 : 1;	unsigned ASS_ON06 : 1;
		unsigned SHUTTER_STEP06 : 8;
		unsigned BRIGHT_STEP06 : 8;
		unsigned IRIS_STEP06 : 8;
		unsigned GAIN_STEP06 : 8;
		unsigned EXP_COMP_VAL06 : 8;
		unsigned WB_MODE06 : 4;	unsigned ICR_ON06 : 1;	unsigned WD_MODE06 : 2;	unsigned DEFOG_ON06 : 1;
		unsigned R_GAIN06 : 8;
		unsigned B_GAIN06 : 8;
		unsigned APER_GAIN06 : 8;
		unsigned WD_BRT_L06 : 3;	unsigned WD_BRT_COMP06 : 2;	unsigned WD_COMP_L06 : 2;	unsigned : 1;
		unsigned AE_MODE06 : 3;		unsigned : 5;
		unsigned ZOOM_POS07 : 16;
		unsigned FOCUS_POS07 : 16;
		unsigned DZOOM_ON07 : 1;	unsigned F_MODE07 : 2;	unsigned AF_MODE07 : 2;	unsigned COMP_ON07 : 1;	unsigned BLC_ON07 : 1;	unsigned ASS_ON07 : 1;
		unsigned SHUTTER_STEP07 : 8;
		unsigned BRIGHT_STEP07 : 8;
		unsigned IRIS_STEP07 : 8;
		unsigned GAIN_STEP07 : 8;
		unsigned EXP_COMP_VAL07 : 8;
		unsigned WB_MODE07 : 4;	unsigned ICR_ON07 : 1;	unsigned WD_MODE07 : 2;	unsigned DEFOG_ON07 : 1;
		unsigned R_GAIN07 : 8;
		unsigned B_GAIN07 : 8;
		unsigned APER_GAIN07 : 8;
		unsigned WD_BRT_L07 : 3;	unsigned WD_BRT_COMP07 : 2;	unsigned WD_COMP_L07 : 2;	unsigned : 1;
		unsigned AE_MODE07 : 3;		unsigned : 5;
		unsigned ZOOM_POS08 : 16;
		unsigned FOCUS_POS08 : 16;
		unsigned DZOOM_ON08 : 1;	unsigned F_MODE08 : 2;	unsigned AF_MODE08 : 2;	unsigned COMP_ON08 : 1;	unsigned BLC_ON08 : 1;	unsigned ASS_ON08 : 1;
		unsigned SHUTTER_STEP08 : 8;
		unsigned BRIGHT_STEP08 : 8;
		unsigned IRIS_STEP08 : 8;
		unsigned GAIN_STEP08 : 8;
		unsigned EXP_COMP_VAL08 : 8;
		unsigned WB_MODE08 : 4;	unsigned ICR_ON08 : 1;	unsigned WD_MODE08 : 2;	unsigned DEFOG_ON08 : 1;
		unsigned R_GAIN08 : 8;
		unsigned B_GAIN08 : 8;
		unsigned APER_GAIN08 : 8;
		unsigned WD_BRT_L08 : 3;	unsigned WD_BRT_COMP08 : 2;	unsigned WD_COMP_L08 : 2;	unsigned : 1;
		unsigned AE_MODE08 : 3;		unsigned : 5;
		unsigned ZOOM_POS09 : 16;
		unsigned FOCUS_POS09 : 16;
		unsigned DZOOM_ON09 : 1;	unsigned F_MODE09 : 2;	unsigned AF_MODE09 : 2;	unsigned COMP_ON09 : 1;	unsigned BLC_ON09 : 1;	unsigned ASS_ON09 : 1;
		unsigned SHUTTER_STEP09 : 8;
		unsigned BRIGHT_STEP09 : 8;
		unsigned IRIS_STEP09 : 8;
		unsigned GAIN_STEP09 : 8;
		unsigned EXP_COMP_VAL09 : 8;
		unsigned WB_MODE09 : 4;	unsigned ICR_ON09 : 1;	unsigned WD_MODE09 : 2;	unsigned DEFOG_ON09 : 1;
		unsigned R_GAIN09 : 8;
		unsigned B_GAIN09 : 8;
		unsigned APER_GAIN09 : 8;
		unsigned WD_BRT_L09 : 3;	unsigned WD_BRT_COMP09 : 2;	unsigned WD_COMP_L09 : 2;	unsigned : 1;
		unsigned AE_MODE09 : 3;		unsigned : 5;
		unsigned ZOOM_POS10 : 16;
		unsigned FOCUS_POS10 : 16;
		unsigned DZOOM_ON10 : 1;	unsigned F_MODE10 : 2;	unsigned AF_MODE10 : 2;	unsigned COMP_ON10 : 1;	unsigned BLC_ON10 : 1;	unsigned ASS_ON10 : 1;
		unsigned SHUTTER_STEP10 : 8;
		unsigned BRIGHT_STEP10 : 8;
		unsigned IRIS_STEP10 : 8;
		unsigned GAIN_STEP10 : 8;
		unsigned EXP_COMP_VAL10 : 8;
		unsigned WB_MODE10 : 4;	unsigned ICR_ON10 : 1;	unsigned WD_MODE10 : 2;	unsigned DEFOG_ON10 : 1;
		unsigned R_GAIN10 : 8;
		unsigned B_GAIN10 : 8;
		unsigned APER_GAIN10 : 8;
		unsigned WD_BRT_L10 : 3;	unsigned WD_BRT_COMP10 : 2;	unsigned WD_COMP_L10 : 2;	unsigned : 1;
		unsigned AE_MODE10 : 3;		unsigned : 5;
		unsigned ZOOM_POS11 : 16;
		unsigned FOCUS_POS11 : 16;
		unsigned DZOOM_ON11 : 1;	unsigned F_MODE11 : 2;	unsigned AF_MODE11 : 2;	unsigned COMP_ON11 : 1;	unsigned BLC_ON11 : 1;	unsigned ASS_ON11 : 1;
		unsigned SHUTTER_STEP11 : 8;
		unsigned BRIGHT_STEP11 : 8;
		unsigned IRIS_STEP11 : 8;
		unsigned GAIN_STEP11 : 8;
		unsigned EXP_COMP_VAL11 : 8;
		unsigned WB_MODE11 : 4;	unsigned ICR_ON11 : 1;	unsigned WD_MODE11 : 2;	unsigned DEFOG_ON11 : 1;
		unsigned R_GAIN11 : 8;
		unsigned B_GAIN11 : 8;
		unsigned APER_GAIN11 : 8;
		unsigned WD_BRT_L11 : 3;	unsigned WD_BRT_COMP11 : 2;	unsigned WD_COMP_L11 : 2;	unsigned : 1;
		unsigned AE_MODE11 : 3;		unsigned : 5;
		unsigned ZOOM_POS12 : 16;
		unsigned FOCUS_POS12 : 16;
		unsigned DZOOM_ON12 : 1;	unsigned F_MODE12 : 2;	unsigned AF_MODE12 : 2;	unsigned COMP_ON12 : 1;	unsigned BLC_ON12 : 1;	unsigned ASS_ON12 : 1;
		unsigned SHUTTER_STEP12 : 8;
		unsigned BRIGHT_STEP12 : 8;
		unsigned IRIS_STEP12 : 8;
		unsigned GAIN_STEP12 : 8;
		unsigned EXP_COMP_VAL12 : 8;
		unsigned WB_MODE12 : 4;	unsigned ICR_ON12 : 1;	unsigned WD_MODE12 : 2;	unsigned DEFOG_ON12 : 1;
		unsigned R_GAIN12 : 8;
		unsigned B_GAIN12 : 8;
		unsigned APER_GAIN12 : 8;
		unsigned WD_BRT_L12 : 3;	unsigned WD_BRT_COMP12 : 2;	unsigned WD_COMP_L12 : 2;	unsigned : 1;
		unsigned AE_MODE12 : 3;		unsigned : 5;
		unsigned ZOOM_POS13 : 16;
		unsigned FOCUS_POS13 : 16;
		unsigned DZOOM_ON13 : 1;	unsigned F_MODE13 : 2;	unsigned AF_MODE13 : 2;	unsigned COMP_ON13 : 1;	unsigned BLC_ON13 : 1;	unsigned ASS_ON13 : 1;
		unsigned SHUTTER_STEP13 : 8;
		unsigned BRIGHT_STEP13 : 8;
		unsigned IRIS_STEP13 : 8;
		unsigned GAIN_STEP13 : 8;
		unsigned EXP_COMP_VAL13 : 8;
		unsigned WB_MODE13 : 4;	unsigned ICR_ON13 : 1;	unsigned WD_MODE13 : 2;	unsigned DEFOG_ON13 : 1;
		unsigned R_GAIN13 : 8;
		unsigned B_GAIN13 : 8;
		unsigned APER_GAIN13 : 8;
		unsigned WD_BRT_L13 : 3;	unsigned WD_BRT_COMP13 : 2;	unsigned WD_COMP_L13 : 2;	unsigned : 1;
		unsigned AE_MODE13 : 3;		unsigned : 5;
		unsigned ZOOM_POS14 : 16;
		unsigned FOCUS_POS14 : 16;
		unsigned DZOOM_ON14 : 1;	unsigned F_MODE14 : 2;	unsigned AF_MODE14 : 2;	unsigned COMP_ON14 : 1;	unsigned BLC_ON14 : 1;	unsigned ASS_ON14 : 1;
		unsigned SHUTTER_STEP14 : 8;
		unsigned BRIGHT_STEP14 : 8;
		unsigned IRIS_STEP14 : 8;
		unsigned GAIN_STEP14 : 8;
		unsigned EXP_COMP_VAL14 : 8;
		unsigned WB_MODE14 : 4;	unsigned ICR_ON14 : 1;	unsigned WD_MODE14 : 2;	unsigned DEFOG_ON14 : 1;
		unsigned R_GAIN14 : 8;
		unsigned B_GAIN14 : 8;
		unsigned APER_GAIN14 : 8;
		unsigned WD_BRT_L14 : 3;	unsigned WD_BRT_COMP14 : 2;	unsigned WD_COMP_L14 : 2;	unsigned : 1;
		unsigned AE_MODE14 : 3;		unsigned : 5;
		unsigned ZOOM_POS15 : 16;
		unsigned FOCUS_POS15 : 16;
		unsigned DZOOM_ON15 : 1;	unsigned F_MODE15 : 2;	unsigned AF_MODE15 : 2;	unsigned COMP_ON15 : 1;	unsigned BLC_ON15 : 1;	unsigned ASS_ON15 : 1;
		unsigned SHUTTER_STEP15 : 8;
		unsigned BRIGHT_STEP15 : 8;
		unsigned IRIS_STEP15 : 8;
		unsigned GAIN_STEP15 : 8;
		unsigned EXP_COMP_VAL15 : 8;
		unsigned WB_MODE15 : 4;	unsigned ICR_ON15 : 1;	unsigned WD_MODE15 : 2;	unsigned DEFOG_ON15 : 1;
		unsigned R_GAIN15 : 8;
		unsigned B_GAIN15 : 8;
		unsigned APER_GAIN15 : 8;
		unsigned WD_BRT_L15 : 3;	unsigned WD_BRT_COMP15 : 2;	unsigned WD_COMP_L15 : 2;	unsigned : 1;
		unsigned AE_MODE15 : 3;		unsigned : 5;
		unsigned ZOOM_POS16 : 16;
		unsigned FOCUS_POS16 : 16;
		unsigned DZOOM_ON16 : 1;	unsigned F_MODE16 : 2;	unsigned AF_MODE16 : 2;	unsigned COMP_ON16 : 1;	unsigned BLC_ON16 : 1;	unsigned ASS_ON16 : 1;
		unsigned SHUTTER_STEP16 : 8;
		unsigned BRIGHT_STEP16 : 8;
		unsigned IRIS_STEP16 : 8;
		unsigned GAIN_STEP16 : 8;
		unsigned EXP_COMP_VAL16 : 8;
		unsigned WB_MODE16 : 4;	unsigned ICR_ON16 : 1;	unsigned WD_MODE16 : 2;	unsigned DEFOG_ON16 : 1;
		unsigned R_GAIN16 : 8;
		unsigned B_GAIN16 : 8;
		unsigned APER_GAIN16 : 8;
		unsigned WD_BRT_L16 : 3;	unsigned WD_BRT_COMP16 : 2;	unsigned WD_COMP_L16 : 2;	unsigned : 1;
		unsigned AE_MODE16 : 3;		unsigned : 5;
		unsigned COMM_BAUDRATE : 8;
		unsigned MONITORING_MODE : 8;
		unsigned AO_ON : 1;	unsigned DO_ON : 1;	unsigned : 6;
		unsigned LVDS_OUT : 8;
		unsigned ZWIDE_LIMIT : 8;
		unsigned ZTELE_LIMIT : 8;
		unsigned DZ_MAX : 8;
		unsigned SZOOM_ON : 1;	unsigned : 7;
		unsigned FTRACE_ON : 1;	unsigned : 7;
		unsigned FCS_OFFSET_DOME : 8;
		unsigned EX_EXPC_ON : 1;	unsigned EX_EXPAP_ON : 1;	unsigned EX_CGCH_ON : 1;	unsigned EX_AICR_F2O_ON : 1;	unsigned : 4;
		unsigned : 8;
		unsigned WD_SCR_DISP   : 2;	unsigned WD_DET_SENS: 2;	unsigned WD_BUCORR_LV : 2;	unsigned WD_BOCORR_LV	: 2;
		unsigned WD_SHORT_EXPR : 8;
		unsigned WD_ALARM	: 2;	unsigned : 8;
	} FLD;
} EEP_VISCA_DATA;

#define EEP_VISCA_USER_MAX		(0x10)

/* 19Page :Visca Data = 0x13F0 ~ 0x13FF */
typedef union _EEP_VISCA_USER
{
	uint08 Data[EEP_VISCA_USER_MAX];

	struct
	{
		unsigned CAM_USERMEMORYSET01 : 8;
		unsigned CAM_USERMEMORYSET02 : 8;
		unsigned CAM_USERMEMORYSET03 : 8;
		unsigned CAM_USERMEMORYSET04 : 8;
		unsigned CAM_USERMEMORYSET05 : 8;
		unsigned CAM_USERMEMORYSET06 : 8;
		unsigned CAM_USERMEMORYSET07 : 8;
		unsigned CAM_USERMEMORYSET08 : 8;
		unsigned CAM_USERMEMORYSET09 : 8;
		unsigned CAM_USERMEMORYSET10 : 8;
		unsigned CAM_USERMEMORYSET11 : 8;
		unsigned CAM_USERMEMORYSET12 : 8;
		unsigned CAM_USERMEMORYSET13 : 8;
		unsigned CAM_USERMEMORYSET14 : 8;
		unsigned CAM_USERMEMORYSET15 : 8;
		unsigned CAM_USERMEMORYSET16 : 8;
	} FLD;
} EEP_VISCA_USER;


/************************************************************************************************************/
/* OSD */
/* OSD Item */
typedef struct _OSD_ITEM {
	OSD_STR name;
	struct _OSD_MAP *pdep;
} OSD_ITEM;

/* OSD Map */
typedef struct _OSD_MAP {
	OSD_STR name;

	EEP_IDX eep;
	const uint32 eepmax;

	struct _OSD_MAP *pdep;
	struct _OSD_ITEM *pitem;
} OSD_MAP;

/************************************************************************************************************/
/* Protocol */
typedef struct _IF_CONDITION {
	const EEP_IDX idx;
	const uint16 dat;
} IF_CONDITION;

typedef struct _IF_CONDITIONS {
	const EEP_IDX idx;
	const IF_CONDITION *cndtn;
} IF_CONDITIONS;

typedef enum _DAT_TYPE  {
	TYPE_8BITS  = 1,
	TYPE_16BITS = 2,
	TYPE_32BITS = 4
}DAT_TYPE;

typedef enum _CNBT_CALLBACK_FUNC {
	CNBT_ISP,
	CNBT_EEP,
	CNBT_MOTOR_IC,		// AN41908
	CNBT_SENSOR_IC,		// MN34041
	CNBT_VIDEO_IC,		// AD7393
	CNBT_VIDEO_IC2,		// MDIN325 HOST
	CNBT_VIDEO_IC3,		// MDIN325 LOCAL
	CNBT_EEP_SKIP,		// EEP SKIP
	CNBT_MAX
}CNBT_CALLBACK_FUNC;

typedef enum _VISCA_CAM_STATE {
	VISCA_STT_ZOOM_DIRCT,
	VISCA_STT_FOCUS_DIRCT,
	VISCA_STT_ZMFCS_DIRCT,
	VISCA_STT_RESET,
	VISCA_STT_SET,
	VISCA_STT_RECALL,
	VISCA_STT_MAX
}VISCA_CAM_STATE;

/*************************************************************************************************************
* GLOBAL VARIABLE EXTERNS
*************************************************************************************************************/
/************************************************************************************************************/
/* Event */

/************************************************************************************************************/
/* EEPRom */
MICLIB_IF_MW_EXT EEP_OSD_DATA		g_OsdData;			// EEPRom ADDRESS 0x0000 ~ 0x00FF
MICLIB_IF_MW_EXT EEP_CAM_OP_DATA	g_CamData;			// EEPRom ADDRESS 0x0500 ~ 0x056F
MICLIB_IF_MW_EXT EEP_VISCA_DATA		g_ViscaData;		// EEPRom ADDRESS 0x1000 ~ 0x13FF
MICLIB_IF_MW_EXT EEP_VISCA_USER		g_ViscaUser;		// EEPRom ADDRESS 0x13F0 ~ 0x13FF
/************************************************************************************************************/
/* OSD */

/************************************************************************************************************/
/* Protocol */


/*************************************************************************************************************
* GLOBAL FUNCTION EXTERNS
*************************************************************************************************************/
/************************************************************************************************************/
/* Interface */
MICLIB_IF_MW_EXT void IF_Initial();

MICLIB_IF_MW_EXT void IF_EventCallbackRegister(IFER (*EventCallback)(IFEVT, IFEVT_PARAM *));
MICLIB_IF_MW_EXT void IF_UEepUpdateCallbackRegister(int32 (*UEepUpdateCallback)(IFEVT, EEP_IDX, int32));
//MICLIB_IF_MW_EXT void IF_PtcSendBufCallbackRegister(void (*PtcSendCallback)(uint08));

MICLIB_IF_MW_EXT void IF_OsdPrintCallbackRegister(void (*PrintCallback)(uint08, uint08, uint32));
MICLIB_IF_MW_EXT void IF_OsdMapRegister(const OSD_MAP *map, const OSD_MAP *hiddenmap);
MICLIB_IF_MW_EXT void IF_OsdWindowSize(uint32 width, uint32 height);

MICLIB_IF_MW_EXT IFER IF_Trace(uint08 x,uint08 y,const char *fnt,...);

MICLIB_IF_MW_EXT IFER IF_Task(OSD_KEY key);
MICLIB_IF_MW_EXT IFER IF_Task_Ptc(void);

/************************************************************************************************************/
/* Event */

/************************************************************************************************************/
/* EEPRom */
MICLIB_IF_MW_EXT int32 IF_EEPUpdate(IFEVT evt, EEP_IDX idx, int32 val);
MICLIB_IF_MW_EXT int32 IF_EEPMotionUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val);
MICLIB_IF_MW_EXT int32 IF_EEPPrivacyUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val);

MICLIB_IF_MW_EXT int32 IF_EEPViscaUpdate(IFEVT evt, EEP_IDX idx, int32 val);
MICLIB_IF_MW_EXT int32 IF_EEPViscaTitleUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val);
MICLIB_IF_MW_EXT int32 IF_EEPViscaMaskUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val);

MICLIB_IF_MW_EXT int32 IF_EEPGetPrivZone();				//131016 Get_Privacy_num
MICLIB_IF_MW_EXT void IF_EEPSetPrivZone(uint32 zone);		//131128 add
MICLIB_IF_MW_EXT int32 IF_EEPGetMotionZone();				//131016 Get_Privacy_num
MICLIB_IF_MW_EXT void IF_EEPSetMotionZone(uint32 zone);	//131128 add

MICLIB_IF_MW_EXT int32 IF_GetCurPan();		//131220 add
MICLIB_IF_MW_EXT int32 IF_GetCurTilt();	//131220 add
/************************************************************************************************************/
/* OSD */
MICLIB_IF_MW_EXT OSD_STATE IF_IsOsdOn();
MICLIB_IF_MW_EXT OSD_MODE IF_IsOsdMode();
MICLIB_IF_MW_EXT void IF_OsdOff();
MICLIB_IF_MW_EXT void IF_OsdRefresh();
MICLIB_IF_MW_EXT void IF_OsdItemRefresh(uint08 cursor);
MICLIB_IF_MW_EXT void IF_OsdAllItemRefresh(void);
MICLIB_IF_MW_EXT void IF_OsdHide();
MICLIB_IF_MW_EXT void IF_OsdShow();
MICLIB_IF_MW_EXT IFER IF_OsdHiddenMenuOn();
MICLIB_IF_MW_EXT void PrintIdTitle();

/************************************************************************************************************/
/* Protocol */
MICLIB_IF_MW_EXT void IF_PtcDecodingType(PTC_TYPE type);
MICLIB_IF_MW_EXT IFER IF_Send_Reply_Packet(VISCA_REPLY_TYPE reply ,uint32 dat);

MICLIB_IF_MW_EXT uint08 IF_PTC_RxQueSize(void);
MICLIB_IF_MW_EXT uint08 IF_PTC_TxQueSize(void);
MICLIB_IF_MW_EXT uint08 IF_PTC_GetTxQue(void);			//Uart_drv에 등록
MICLIB_IF_MW_EXT uint08 IF_PTC_GetRxQue(void);			//외부에서 CNB_H를 운용
MICLIB_IF_MW_EXT void IF_PTC_SetTxQue(uint08 txData);	//외부에서 CNB_H를 운용
MICLIB_IF_MW_EXT void IF_PTC_SetRxQue(uint08 rxData);	//Uart_drv에 등록

MICLIB_IF_MW_EXT IFER IF_CNBT_Regist_Callbeck(CNBT_CALLBACK_FUNC type,uint32 (*getfnc)(uint32 addr),void (*setfnc)(uint32 addr,uint32 dat));
MICLIB_IF_MW_EXT IFER IF_VISCA_Regist_CamState(VISCA_CAM_STATE type,uint08 (*getstt)(void));

MICLIB_IF_MW_EXT void Visca_Socket_Clear(uint08 num);
#endif // _MICLIB_IF_MW_H_
