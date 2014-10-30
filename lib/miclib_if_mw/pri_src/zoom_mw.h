/*********************************************************************************************************//**
* @file zoom_mw.h
* @author 
*  Jinsoo Kim
* @date 2013.08.23
* @brief 
*  Header file of Cannon x10 Zoom control Middleware
*************************************************************************************************************/
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef ZOOM_MW_H_
#define ZOOM_MW_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef ZOOM_MW_EXTERN 
#define ZOOM_MW_EXT 
#else 
#define ZOOM_MW_EXT extern
#endif
/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/
/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/
/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/

typedef enum _ZOOM_TRACK_MODE_TYPE {
	ZOOM_TRACK_MODE_AUTO,
	ZOOM_TRACK_MODE_MANUAL,
	ZOOM_TRACK_MODE_MAX,
} ZOOM_TRACK_MODE_TYPE;

typedef enum _ZOOM_DIRECTION_TYPE {
	ZOOM_DIRECTION_TYPE_NEUTRAL,
	ZOOM_DIRECTION_TYPE_TELE,
	ZOOM_DIRECTION_TYPE_WIDE,
	ZOOM_DIRECTION_TYPE_MAX
} ZOOM_DIRECTION_TYPE;


/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/

typedef union _UNION_ZOOM_PARAM 
{
	uint08 Data[20];

	struct
	{
		unsigned 	direct_position	:16;
		
		unsigned 	tot_zoom_mag	:16;
		
		unsigned 	limit_tele_val	:8;
		
		unsigned 	limit_wide_val	:8;
		
		unsigned 	limit_wide_pos	:16;
		
		unsigned 	limit_tele_pos	:16;
		
		unsigned	speed			:4;
		unsigned	direction		:4;
		
		unsigned	TrackMode		:8;

		unsigned	f_busy			:1;
		unsigned	reply_on_off	:1;
		unsigned	:6;

		unsigned	:8;
		
		unsigned	tgt_reply_interval:16;
		
		unsigned	cur_reply_interval:16;

		unsigned	:16;
		
	} FLD;
	
} UNION_ZOOM_PARAM;

//ZOOM_MW_EXT volatile UNION_ZOOM_PARAM ZmParam;

ZOOM_MW_EXT volatile uint32 ZmDebugBuf[16];

/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
ZOOM_MW_EXT void Zoom_init(void);

ZOOM_MW_EXT uint08 Zoom_Control(void);

ZOOM_MW_EXT uint08 Zoom_set_direct_position(uint16 position);
ZOOM_MW_EXT uint16 Zoom_get_direct_position(void);

ZOOM_MW_EXT uint08 Zoom_set_zoom_speed(uint08 speed);

ZOOM_MW_EXT uint08 Zoom_set_limit_tele(uint16 value);	// for visca
ZOOM_MW_EXT uint16 Zoom_get_limit_tele(void);			// for visca
ZOOM_MW_EXT uint16 Zoom_get_limit_tele_opt_pos(void);

ZOOM_MW_EXT uint08 Zoom_set_limit_wide(uint16 value);	// for visca
ZOOM_MW_EXT uint16 Zoom_get_limit_wide(void);			// for visca
ZOOM_MW_EXT uint16 Zoom_get_limit_wide_opt_pos(void);

ZOOM_MW_EXT uint08 Zoom_set_zoom_track_mode(ZOOM_TRACK_MODE_TYPE mode);
ZOOM_MW_EXT ZOOM_TRACK_MODE_TYPE Zoom_get_zoom_track_mode(void);

ZOOM_MW_EXT uint08 Zoom_get_busy_state(void);

ZOOM_MW_EXT uint16 Zoom_get_current_position(void);

ZOOM_MW_EXT uint08 Zoom_set_pos_reply_mode(uint08 mode);
ZOOM_MW_EXT uint08 Zoom_set_pos_reply_interval(uint08 interval);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/

#endif /* ZOOM_MW_H_ */

