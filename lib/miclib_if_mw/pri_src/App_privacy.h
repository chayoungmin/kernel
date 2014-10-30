
/************************************************************************************************************
* MODULE
*************************************************************************************************************/
#ifndef _PRIVACY_H_
#define _PRIVACY_H_

/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/

/*************************************************************************************************************
* EXTERNS 
*************************************************************************************************************/
#ifdef PRIVACY_EXTERN
#define	PRIVACY_EXT	extern
#else
#define	PRIVACY_EXT	extern
#endif
/*************************************************************************************************************
* DEFAULT CONFIGURATION 
*************************************************************************************************************/

/*************************************************************************************************************
* DEFINES 
*************************************************************************************************************/
#define POLYGON_TYPE		0

#define MAX_PRIVACYZONE     8


#define PRI_WIDTH_MIN		0x0FFB
#define PRI_WIDTH_MAX		0x176D
#define PRI_HEIGHT_MIN		0x0FFF
#define PRI_HEIGHT_MAX		0x1431

#define PRI_WIDTH_MIN_		0x1009
#define PRI_WIDTH_MAX_		0x1787
#define PRI_HEIGHT_MIN_		0x100B
#define PRI_HEIGHT_MAX_		0x143E

/*************************************************************************************************************
* MACRO'S 
*************************************************************************************************************/

/*************************************************************************************************************
* DATA TYPES
*************************************************************************************************************/
typedef enum _PRIVACY_ZONE_COLOR {
	MASK_WHITE = 0,
	MASK_GRAY,
	MASK_YELLOW,
	MASK_GREEN,
	MASK_RED,
	MASK_BLUE,
	MASK_BLACK,
	MASK_COLORS
} PRIVACY_ZONE_COLOR;

typedef struct _PRIVACY_ZONE {
	uint08 Color;
	uint16 LeftParam;
	uint16 RightParam;
	uint16 TopParam;
	uint16 BottomParam;
	uint16 Width_Angle;		//Width에 의해 설정되는 마스크의 가로 각
	uint16 Height_Angle;		//Height에 의해 설정되는 마스크의 세로 각
	uint16 Width_Fov;	//
	uint16 Height_Fov;	//
	uint16 regOffset;
	uint16 Width;
	uint16 Height;
	struct {

		int32 left;
		int32 right;
		int32 top;
		int32 bottom;
	} MaskArea;
} PRIVACY_ZONE_;

typedef union _MASK_EVENT {
	uint08 byte;

	struct {
		unsigned update              :1;     // Mask Update [0] : Normal [1] : Update
		unsigned b1                  :1;
		unsigned b2                  :1;
		unsigned b3                  :1;
		unsigned b4                  :1;
		unsigned b5                  :1;
		unsigned b6                  :1;
		unsigned b7                  :1;
	} b;
} MASK_EVENT;

/*************************************************************************************************************
* GLOBAL VARIABLES
*************************************************************************************************************/
PRIVACY_EXT PRIVACY_ZONE_ PrivZone[MAX_PRIVACYZONE];
PRIVACY_EXT volatile MASK_EVENT   MaskEvent;
/*************************************************************************************************************
* FUNCTION PROTOTYPES 
*************************************************************************************************************/
PRIVACY_EXT void PRI3D_Set_Y2Tilt(uint08 index,int32 Yval);
PRIVACY_EXT void PRI3D_Set_Tilt2Y(uint08 index,int32 Tval);
PRIVACY_EXT void PRI3D_Set_X2Pan(uint08 index,int32 Xval);
PRIVACY_EXT void PRI3D_Set_Pan2X(uint08 index,int32 Pval);

PRIVACY_EXT void InitPrivacyMask(void);
PRIVACY_EXT void PrivacyMaskProcess(void);
PRIVACY_EXT void PRV_Redraw();
PRIVACY_EXT void Set_Mask_Debug();
PRIVACY_EXT void Set_Mask_Normal();
PRIVACY_EXT void PRIV_Dbg_Osd();
PRIVACY_EXT void LensUpdate(void);

/*************************************************************************************************************
* CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/

#endif /* _PRIVACY_H_ */
/********************** END OF FILE *************************/
