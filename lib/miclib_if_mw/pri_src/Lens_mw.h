/*********************************************************************************************************//**
* @file Lens_mw.h
* @author 
*  Jinsoo Kim
* @date 2013.08.10 
* @brief 
*  Header file of Cannon x10 Zoom Lens Middleware
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef LENS_MW_H_
#define LENS_MW_H_

#ifdef FOCUS_FREE
#include "Remote_mw.h"
#endif

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef LENS_MW_EXTERN 
#define LENS_MW_EXT 
#else 
#define LENS_MW_EXT extern
#endif
/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/
/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
#ifdef SUNNY_X20
#define IR_CORR_DATA_SIZE	20

#define LENS_MAX_OPTICAL_MAG	200
#define LENS_MIN_OPTICAL_MAG	10

#define	FOCUS_SELECT			0x1
#define ZOOM_SELECT				0x2

#define FOCUS_LED_ON			0x1
#define FOCUS_LED_OFF			0x0
#define ZOOM_LED_ON				0x1
#define ZOOM_LED_OFF			0x0

//#define FOCUS_DIRECTION_NEAR	0x1
//#define FOCUS_DIRECTION_FAR		0x0
//#define ZOOM_DIRECTION_WIDE		0x1
//#define ZOOM_DIRECTION_TELE		0x0

#define MOTOR_DRVING_ON			2
#define MOTOR_DRVING_OFF		3

#define DIRECTION_NEAR			2
#define DIRECTION_FAR			3

#define DIRECTION_TELE			2
#define DIRECTION_WIDE			3

#define ZOOM_INTCT_OFFSET_60HZ	2344
#define ZOOM_INTCT_OFFSET_50HZ	2344

#define FOCUS_INTCT_OFFSET_60HZ	4688
#define FOCUS_INTCT_OFFSET_50HZ	4688

#define ZOOM_INTCT_OFFSET_30HZ	4688
#define ZOOM_INTCT_OFFSET_25HZ	4688

#define FOCUS_INTCT_OFFSET_30HZ	9375
#define FOCUS_INTCT_OFFSET_25HZ	9375


#define ZOOM_PSUM_STEP 8
#define FOCUS_PSUM_STEP 4


//
#define ZOOM_INF_PEAK_POSITION		961
#define FOCUS_INF_PEAK_POSITION		1526

#define FOCUS_INF_TELE_POSITION		352

#define ZOOM_WIDE_LIMIT_POSITION	0
#define ZOOM_TELE_LIMIT_POSITION	1311

#define	ZOOM_ORIGIN_POSITION		0
#define	FOCUS_ORIGIN_POSITION		1024

#define DEF_FOCUS_DIFF				0x00
#define DEF_ZOOM_DIFF				0x00
#define DEF_PEAK_DIFF				0x00

#define FOCUS_RESET_POSITION		(FOCUS_ORIGIN_POSITION - 104)	//920
#define ZOOM_RESET_POSITION			1209





//#define FLANGE_BACK_OFFSET		(0)	// +:FAR OFFSET -:NEAR OFFSET





//#define ZOOM_INF_TELE_POSITION	1232
//#define ZOOM_INF_WIDE_POSITION	60

#define	ZOOM_INF_PEAK_POSITION_OFFSET	(-248)
//#define FOCUS_INF_WIDE_POSITION_OFFSET	1070
#define FOCUS_INF_WIDE_POSITION_OFFSET	1174

//#define FOCUS_INF_TELE_POSITION	456

#define FOCUS_INF_WIDE_POSITION		1024

#define FOCUS_NEAR_LIMIT_POSITION	1733
#define FOCUS_FAR_LIMIT_POSITION	259



//#define ZOOM_TELE_LIMIT_POSITION_OFFSET	(7)
#define ZOOM_TELE_LIMIT_POSITION_OFFSET	(0)

#define ZOOM_TELE_HW_LIMIT_POSITION	1318

#define FOCUS_SPEED_MAX		20
#define ZOOM_SPEED_MAX 		10

#define FOCUS_SENSOR_LOW_TRIGGER	100
#define FOCUS_SENSOR_HIGH_TRIGGER	400
#define ZOOM_SENSOR_LOW_TRIGGER		100
#define ZOOM_SENSOR_HIGH_TRIGGER	400



#define ZOOM_LOGI_MIN_POSITION	0x0000
#define ZOOM_LOGI_MAX_POSITION	0x7AC0
#define FOCUS_LOGI_MAX_POSITION 0xF000	// ICM
#define FOCUS_LOGI_MIN_POSITION 0x1000	// OVER INF

#define FOCUS_IDLE_POSITION		0x3000

#define AF_AGING_INTERVAL			600		// VD

#else	// NOT SUNNY_X20

#define IR_CORR_DATA_SIZE	10

#define LENS_MAX_OPTICAL_MAG	100
#define LENS_MIN_OPTICAL_MAG	10

#define	FOCUS_SELECT			0x1
#define ZOOM_SELECT				0x2

#define FOCUS_LED_ON			0x1
#define FOCUS_LED_OFF			0x0
#define ZOOM_LED_ON				0x1
#define ZOOM_LED_OFF			0x0

//#define FOCUS_DIRECTION_NEAR	0x1
//#define FOCUS_DIRECTION_FAR		0x0
//#define ZOOM_DIRECTION_WIDE		0x1
//#define ZOOM_DIRECTION_TELE		0x0

#define MOTOR_DRVING_ON			2
#define MOTOR_DRVING_OFF		3

#define DIRECTION_NEAR			2
#define DIRECTION_FAR			3

#define DIRECTION_TELE			2
#define DIRECTION_WIDE			3


#define ZOOM_INTCT_OFFSET_60HZ	4688
#define ZOOM_INTCT_OFFSET_50HZ	5625

#define FOCUS_INTCT_OFFSET_60HZ	4688
#define FOCUS_INTCT_OFFSET_50HZ	5625


#define ZOOM_INTCT_OFFSET_30HZ	9375
#define ZOOM_INTCT_OFFSET_25HZ	11250

#define FOCUS_INTCT_OFFSET_30HZ	9375
#define FOCUS_INTCT_OFFSET_25HZ	11250


#define ZOOM_PSUM_STEP 4
#define FOCUS_PSUM_STEP 4

#define	FOCUS_ORIGIN_POSITION	768
#define	ZOOM_ORIGIN_POSITION	0

#define FLANGE_BACK_OFFSET		(22)		// +:FAR OFFSET -:NEAR OFFSET
#define FOCUS_RESET_POSITION	(FOCUS_ORIGIN_POSITION + 100 + FLANGE_BACK_OFFSET)
#define ZOOM_RESET_POSITION		493

#define ZOOM_INF_PEAK_POSITION			856
#define	ZOOM_INF_PEAK_POSITION_OFFSET	363

#define FOCUS_INF_PEAK_POSITION	1134

#define FOCUS_INF_WIDE_POSITION_OFFSET	394

//#define ZOOM_INF_TELE_POSITION	1107
//#define ZOOM_INF_WIDE_POSITION	184
#define FOCUS_INF_TELE_POSITION		740
//#define FOCUS_INF_WIDE_POSITION	851

#define FOCUS_NEAR_LIMIT_POSITION	1286
#define FOCUS_FAR_LIMIT_POSITION	647

#define ZOOM_WIDE_LIMIT_POSITION	ZOOM_ORIGIN_POSITION
#define ZOOM_TELE_LIMIT_POSITION	1136

#define ZOOM_TELE_HW_LIMIT_POSITION	1162

#define FOCUS_SPEED_MAX		42
#define ZOOM_SPEED_MAX 		42

#define FOCUS_SENSOR_LOW_TRIGGER	100
#define FOCUS_SENSOR_HIGH_TRIGGER	400
#define ZOOM_SENSOR_LOW_TRIGGER		100
#define ZOOM_SENSOR_HIGH_TRIGGER	400

#define DEF_FOCUS_DIFF				0x28
#define DEF_ZOOM_DIFF				0x00
#define DEF_PEAK_DIFF				0x00

#define ZOOM_LOGI_MIN_POSITION	0x0000
#define ZOOM_LOGI_MAX_POSITION	0x7AC0
#define FOCUS_LOGI_MAX_POSITION 0xF000	// ICM
#define FOCUS_LOGI_MIN_POSITION 0x1000	// OVER INF

#define FOCUS_IDLE_POSITION		0x3000
#endif

#define CRV_INDEX_INF		0
#define CRV_INDEX_10M		1
#define CRV_INDEX_5M		2
#define CRV_INDEX_3M		3
#define CRV_INDEX_1M		4
#define CRV_INDEX_50CM		5
#define CRV_INDEX_32CM		6
#define CRV_INDEX_19CM		7
#define CRV_INDEX_12CM		8
#define CRV_INDEX_8CM		9
#define CRV_INDEX_5p2CM		10
#define CRV_INDEX_3p4CM		11
#define CRV_INDEX_2p2CM		12
#define CRV_INDEX_1p5CM		13
#define CRV_INDEX_1CM		14

#ifdef SUNNY_X20
#define DEF_HALL_MAX                        961     // 상온 : 3.5V 이하 = 3.1V = 961 : Open
#define DEF_HALL_MIN                      	217     // 상온 : 0.5V 이상 = 0.7V = 217 : Close

#define	HALL_MAX_LIMIT							760     // ?????
#define HALL_MIN_LIMIT							210     // ?????

#define HALL_OFFSET_ZERO                 		0x6A    // Default hall offset
#define HALL_BIAS_DAC_ZERO                      0xC0
#define HALL_BIAS_DAC_THRS                      0x2D    // 0x2D = Isens * (Rref * 8) / Vref
                                                        // Vref  = 1.26v
                                                        // Rref  = 10K
                                                        // Isens = 0.71mA
														// Diff와 긴밀히 연관이 있음
#define HALL_GAIN_ZERO                          0x06    // Default hall gain
#else
#define DEF_HALL_MAX                        678    // 0x3FF - 0x34B (2.7V) - OPEN		//x35
#define DEF_HALL_MIN                        219   // 0x3FF - 0x09C (0.5V) - CLOSE		//x35

#define HALL_OFFSET_ZERO                  		0x7C    // Default hall offset				//x35
#define HALL_BIAS_DAC_ZERO                      0x22    // 0x2D = Isens * (Rref * 8) / Vref	//x35
                                                        // Vref  = 1.26v
                                                        // Rref  = 10K
                                                        // Isens = 0.71mA
														// Diff와 긴밀히 연관이 있음
#define HALL_GAIN_ZERO                          0x08    // Default hall gain				//x35
#endif

#define HALL_BIAS_DAC_MIN						0x20    // 0x28 Variation : +10% : 1.39[V]/0.71[mA]	//x35
#define HALL_BIAS_DAC_MAX                       0x40    // 0x32 Variation : -10% : 1.13[V]/0.71[mA]	//x35
#define HALL_OFFSET_ERROR_MAX                   (HALL_OFFSET_ZERO + 0x30)
#define HALL_OFFSET_ERROR_MIN                   (HALL_OFFSET_ZERO - 0x30)

#define IRSTGT_FULL_OPEN						0x0
#define IRSTGT_FULL_CLOSE						0x3FF

#define MAX_HALLADJ_COUNT                         200    // Max. Adjust Count
#define HALL_DIFF_STABLE                          48     // 48 Stable Hall Gain Difference
#define HALL_MEAN_STABLE                          10     // Stable Hall Offset Difference
#define HALL_FINE_STABLE                          10     // Stable Hall Bias Dac Difference

#define IR_CORRECTION_STANDARD		0
#define IR_CORRECTION_IR_LIGHT		1

#define LOW_FRAME_RATE_SYSTEM		0
#define HIGH_FRAME_RATE_SYSTEM		1






typedef enum _HALL_FNUM{
	HALL_CLOSE= 0x00,
	HALL_F22  = 0x01,	
	HALL_F20  = 0x02,
	HALL_F18  = 0x03,
	HALL_F16  = 0x04,
	HALL_F14  = 0x05,
	HALL_F11  = 0x06,
	HALL_F9c6 = 0x07,	
	HALL_F8   = 0x08,
	HALL_F6c8 = 0x09,
	HALL_F5c6 = 0x0A,
	HALL_F4c8 = 0x0B,
	HALL_F4   = 0x0C,
	HALL_F3c4 = 0x0D,
	HALL_F2c8 = 0x0E,
	HALL_F2c4 = 0x0F,
	HALL_F2   = 0x10,
	HALL_F1c8 = 0x11,	
} HALL_FNUM;
#define HALL_FNUM_MAX_NUM		0x12
#ifdef SUNNY_X20
#define HALL_STEP_POL			0
#else
#define HALL_STEP_POL			1
#endif
LENS_MW_EXT uint16 HallFTB[HALL_FNUM_MAX_NUM];



/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/
/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/
typedef enum _HALL_ADJ_STATE {
	ADJ_HALL_GAIN,
	ADJ_HALL_OFFSET,
	ADJ_HALL_FINETUNE,
	ADJ_HALL_END
} HALL_ADJ_STATE;

typedef enum _LENS_ADJ_STATUS {
	ADJUSTING,
	ADJ_ERROR,
	ADJ_OK
} LENS_ADJ_STATUS;

typedef enum _FOV_TYPE {
	FOV_TYPE_H,
	FOV_TYPE_V,
	FOV_TYPE_MAX
} FOV_TYPE;


/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/
LENS_MW_EXT const uint16 CrvData[][15];
LENS_MW_EXT const uint32 Deg2FOV[][2];

LENS_MW_EXT const uint16	ZmLogiPosTable[][3];
LENS_MW_EXT const uint16	DZmLogiPosTable[][3];

#if 0
LENS_MW_EXT const uint16	FcsLogiPosTable[][2];	
#endif

LENS_MW_EXT const int08 Ir_Corr_Data[][15];

typedef union _UNION_HALL_PARAM 
{
	uint16 Data[6];

	struct
	{
		uint16 HallAdj		:2;
		uint16 IrisLvl		:12;
		uint16				:4;

		uint16 HallMax		:16;           /* Maximum Hall Data */
		uint16 HallMin		:16;           /* Minimum Hall Data */

		uint16 HallOffset	:16;
		uint16 HallGain		:8;
		uint16 HallBiasDac	:8;
	} FLD;
	
} UNION_HALL_ADJ_PARAM;
LENS_MW_EXT volatile UNION_HALL_ADJ_PARAM HallParam;

#define LENS_PARAM_SZ			26

typedef union _UNION_LENS_PARAM 
{
	uint16 Data[LENS_PARAM_SZ];

	struct
	{
		// 0
		uint16 FcsStatus		:2;
		uint16 ZmStatus			:2;
		uint16 FcsDir			:2;
		uint16 ZmDir			:2;
		uint16 LED				:2;
		uint16 EndSensing		:2;
		uint16 OffsetAdj		:2;
		uint16 EndSensingStart	:2;

		// 1
		uint16 FcsSpd		:8;
		uint16 ZmSpd		:8;
		// 2
		uint16 FcsPosPhy	:16;
		// 3
		uint16 ZmPosPhy		:16;
		// 4
		uint16 FcsPosLogi	:16;
		// 5
		uint16 ZmPosLogi	:16;

		// 6
		uint16 FcsTgtPosPhy	:16;

		// 7
		uint16 ZmTgtPosPhy	:16;
		
		// 8
		uint16 FcsTgtPosLogi:16;
		
		// 9
		uint16 ZmTgtPosLogi	:16;
		
		// 10
		uint16 NearLimit	:16;
		
		// 11
		uint16 FarLimit		:16;
		
		// 12
		uint16 o_zoom_mag		:8;
		uint16 sch_initial_time	:8;
		
		// 13
		uint16 sch_elapsed_time	:8;
		uint16 ir_correct_on_off:2;
		uint16 frame_rate		:1;
		uint16 :5;
		
		//14
		uint16 FcsDiff		:8;
		uint16 ZmDiff		:8;

		
		//15
		uint16 MotDrv24_bk	:16;
		//16
		uint16 MotDrv25_bk	:16;
		//17
		uint16 MotDrv29_bk	:16;
		//18
		uint16 MotDrv2A_bk	:16;

		//19
		uint16 max_fcs_spd	:8;
		uint16 max_zm_spd	:8;

		//20
		uint16 offset_dom	:8;
		uint16 WEND_S		:8;
		
		//21
		uint16 offset_logi_pos	:16;

		//22
		uint16 ZmCurPosLogi		:16;
		//23
		uint16 ZmCurPosLogi_old	:16;

		//24
		uint16 ZmCurPosPhy			:16;
		//25
		uint16 ZmCurPosPhy1			:16;

	}FLD;
} UNION_LENS_PARAM;

typedef struct _LENS_AGING
{
	uint32 aging_cnt;
	uint16 aging_interval;
	uint08 af_aging;
} LENS_AGING;

//LENS_MW_EXT volatile UNION_LENS_PARAM LensParam;

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
LENS_MW_EXT void	Lens_drv_isr(void);

LENS_MW_EXT uint08	Lens_Init(void);
LENS_MW_EXT uint08 Lens_OffsetAdjust(void);
LENS_MW_EXT uint08 Lens_HallAdjust(void);

LENS_MW_EXT uint08	Lens_get_fcs_status(void);

LENS_MW_EXT uint16 Lens_get_optMag(void);
LENS_MW_EXT uint32 Lens_get_current_FOV(FOV_TYPE type);
LENS_MW_EXT uint32 Lens_get_target_FOV(FOV_TYPE type, uint16 tgt_zoom_pos);

LENS_MW_EXT uint16 Lens_get_zoom_pos_phy(void);
LENS_MW_EXT uint16 Lens_get_focus_pos_phy(void);

LENS_MW_EXT uint16 Lens_get_zoom_pos_logi(void);
LENS_MW_EXT uint16 Lens_get_cur_zoom_pos_logi(void);

LENS_MW_EXT uint16 Lens_get_focus_pos_logi(void);

LENS_MW_EXT uint08 Lens_set_zoom_tgt_pos_logi(uint16 position);
LENS_MW_EXT uint16 Lens_get_zoom_tgt_pos_logi(void);

LENS_MW_EXT uint08 Lens_set_focus_tgt_pos_logi(uint16 position);
LENS_MW_EXT uint16 Lens_get_focus_tgt_pos_logi(void);

LENS_MW_EXT uint08 Lens_get_opt_zoom_magitude(void);

LENS_MW_EXT void Lens_start_end_sensing(void);
LENS_MW_EXT void Lens_app_task(void);

LENS_MW_EXT uint08 Lens_sch_initial_task(uint08 mode, uint08 day);
LENS_MW_EXT uint08 Lens_get_sch_init_time(void);
LENS_MW_EXT uint08 Lens_get_sch_elap_time(void);

LENS_MW_EXT	uint08	Lens_get_speed_zm(void);
LENS_MW_EXT uint08	Lens_get_speed_fcs(void);

LENS_MW_EXT uint08 Lens_set_ir_corr_mode(uint08 mode);
LENS_MW_EXT uint08 Lens_get_ir_corr_mode(void);

LENS_MW_EXT uint08 Lens_Control(void);

LENS_MW_EXT uint08 Lens_set_offset_dom(uint08 offset);
LENS_MW_EXT uint08 Lens_get_offset_dom(void);
LENS_MW_EXT uint16 Lens_get_offset_dom_pos(void);



LENS_MW_EXT uint16 Lens_get_HallMin(void);
LENS_MW_EXT uint16 Lens_get_HallMax(void);
LENS_MW_EXT void   Lens_Set_HallTgtVal(uint16 val);
LENS_MW_EXT uint16 Lens_get_HallVal(void);

#ifdef FOCUS_FREE
LENS_MW_EXT void Lens_Fcs_Debug(KEY_CODE code);
#endif

LENS_MW_EXT void Lens_AF_Aging();
/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/

#endif /* LENS_MW_H_ */

