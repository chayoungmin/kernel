/*********************************************************************************************************//**
* @mainpage
*  MiCLiB IF_MW
* @section 소개
*  인터페이스에 대한 공용화
*  OSD/PROTOCOL
* @section 작성일
*  2014.04.01 ~
* @section 저작권
*  Copyright(c) 2014 by CNBTec co.ltd, All right reserved
*************************************************************************************************************/
/*********************************************************************************************************//**
* @file miclib_if_mw.c
* @author
*  KWNAM, SHKIM
* @date
*  2012.08.20\n
* @version
*  0.1
* @brief
*  이 파일은 MICLIB의 모든 데이터 타입과 ERROR CODE를 정의한다.\n
*  Compiler		: VS9.0 & GCC \n
*  Debugger		: VS9.0
*************************************************************************************************************/
/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#ifdef WIN32	// for VS9.0
#include <stdio.h>
#include "main.h"
#endif

#ifdef WIN32	// for VS9.0
#include <stdarg.h>
#include "miclib_type.h"
#include "miclib_if_mw.h"
#else			// for gcc
#include <stdarg.h>
#include "miclib_type.h"
#include "miclib_if_mw.h"
#endif
/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/
typedef enum _VISCA_TYPE {
	VSC_TYPE_EH6300 = 0,
	VSC_TYPE_EV7100 = 1,
	VSC_TYPE_EV7500
}VISCA_TYPE;

#define VISCA_COMPILE		0
/* Interface */
#define IF_NULL					0x00
/* OSD */
#define OSD_NULL				0x00
#ifdef WIN32	// for VS
#define OSD_HEIGHT				17
#define OSD_MENU_LEN			16
#define OSD_ITEM_LEN			16
#define OSD_TITLE_TOP			1
#define OSD_TITLE_LEFT			2
#define OSD_CURSOR_TOP			(OSD_TITLE_TOP + 2)
#define OSD_CURSOR_LEFT			(1)
#define OSD_MENU_TOP			(OSD_CURSOR_TOP)
#define OSD_MENU_LEFT			(OSD_TITLE_LEFT)
#define OSD_ITEM_TOP			(OSD_CURSOR_TOP)
#define OSD_ITEM_LEFT			(OSD_MENU_LEFT + 15)
#define TITLEMAP_CNT			37

#define OSD_STATEON_DELAY		2
#define OSD_FONTHAND			62
#define OSD_FONTSPACE			0x20
#define OSD_SLIDER				0x2D
#define OSD_FONTENTER			60
#define OSD_FONTPUSH			60
#define OSD_FONTULINE			0x5f
#define OSD_ARROWUP				0x21
#define SLIDER_TYPE 			3
#define OSD_ZERO				0x30
#else
#define OSD_HEIGHT				15
#define OSD_MENU_LEN			16
#define OSD_ITEM_LEN			18
#define OSD_TITLE_TOP			2
#define OSD_TITLE_LEFT			OSD_HEIGHT - 1
#define OSD_CURSOR_TOP			(OSD_TITLE_TOP + 2)
#define OSD_CURSOR_LEFT			(OSD_MENU_LEN - 2)
#define OSD_MENU_TOP			(OSD_CURSOR_TOP)
#define OSD_MENU_LEFT			(OSD_MENU_LEN)
#define OSD_ITEM_TOP			(OSD_CURSOR_TOP)
#define OSD_ITEM_LEFT			(OSD_MENU_LEFT + OSD_MENU_LEN)
#define TITLEMAP_CNT			37

#define OSD_STATEON_DELAY		1
#define OSD_FONTHAND			1
#define OSD_FONTSPACE			0x20
#define OSD_SLIDER				14
#define OSD_FONTENTER			2
#define OSD_FONTPUSH			20
#define OSD_FONTULINE			0x5F
#define OSD_ARROWUP				27
#define SLIDER_TYPE 			4
#define OSD_ZERO				0x30
#endif

/* PROTOCOL */
//HEX
#define MAX_PTCBUF			256
#define PTC_CNBH_USERHEADER	0xB0
#define PTC_CNBH_TECHHEADER	0xC9
#define PTC_VISCA_STX		0x80
#define PTC_CNBH_SENDHEADER	2

#define IF_QUEUE_MASK (0xff)
//VISCA
#define MAX_VISCA_CMD 87
#define MAX_VISCA_INQ 70
#define MAX_CONDITION 45

typedef enum _COMPOSE_DATA
{
	COMPOSE_D_HALF,
	COMPOSE_D_FULL,
	COMPOSE_D_MAX
} COMPOSE_DATA;
typedef enum _DECODE_TYPE {
	DECODE_MAPING,
	DECODE_DIRECT,
	DECODE_PLURAL,
	DECODE_EXCEPTION,
	DECODE_MAX,
} DECODE_TYPE;
typedef enum _VISCA_MSG {
	VISCA_ERROR_MSG_LENGTH,
	VISCA_ERROR_SYNTEX,
	VISCA_ERROR_COMMAND_BUF_FULL,
	VISCA_ERROR_COMMAND_CANCEL,
	VISCA_ERROR_NO_SOCKET,
	VISCA_ERROR_COMMAND_EXCUTABLE,
	VISCA_MSG_ACKNOWLEDGE,
	VISCA_MSG_COMPETE_CMD,
	VISCA_MSG_COMPETE_INQ,
	VISCA_MSG_REPLY,
	VISCA_MSG_GLB_ADDSET,
	VISCA_MSG_GLB_IFCLEAR,
	VISCA_MSG_NETWORK_CHANGE,
	VISCA_MSG_MAX
} VISCA_MSG;
typedef enum _COMPLETE_MSG_TYPE {
	COMPLETE_MSG_NONE,
	COMPLETE_MSG_CMD,
	COMPLETE_MSG_STOP_CMD,
	COMPLETE_MSG_INQ,
	COMPLETE_MSG_BLOCK_INQ,
	COMPLETE_MSG_VER_INQ,
	COMPLETE_MSG_MAX
} COMPLETE_MSG_TYPE;

/*************************************************************************************************************
* LOCAL CONSTANTS
*************************************************************************************************************/

/*************************************************************************************************************
* LOCAL DATA TYPES
*************************************************************************************************************/
/*********************************************************************************************************//**
* @brief
*	PROTOCOL PACKET 공용체. \n
*	USER_PTC	: CNB HEX \n
*	TECH_PTC	: CNB HEX TECHNICAL \n
*	VISCA_PTC	: VISCA \n
*************************************************************************************************************/
typedef union _CNBH_PACKET
{
	uint08 data[263];

	struct{
		unsigned HEADER		:8;
		unsigned PG			:8;
		unsigned ID			:8;
		unsigned CMD_TYPE	:4;	// Config
		unsigned MSG_LEN	:4;
		unsigned CMD1		:8;
		unsigned CMD2		:8;	// 6

		unsigned MSG1		:8;		unsigned MSG2		:8;		unsigned MSG3		:8;		unsigned MSG4		:8;
		unsigned MSG5		:8;		unsigned MSG6		:8;		unsigned MSG7		:8;		unsigned MSG8		:8;
		unsigned MSG9		:8;		unsigned MSG10		:8;		unsigned MSG11		:8;		unsigned MSG12		:8;
		unsigned MSG13		:8;		unsigned MSG14		:8;		unsigned MSG15		:8;	// 21

		unsigned CS			:8;	// 22

		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;
		unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:32;	unsigned	:8;
	} USER_PTC;

	struct{
		unsigned HEADER		:8;
		unsigned CAM_ID		:8;
		unsigned CMD		:8;	// Config
		unsigned PARAM1_1	:8;
		unsigned PARAM1_2	:8;
		unsigned PARAM2		:8;
		unsigned LEN		:8;	// 7

		unsigned MSG1  		:8;	unsigned MSG2  		:8;	unsigned MSG3  		:8;	unsigned MSG4  		:8;	unsigned MSG5  		:8;	unsigned MSG6  		:8;	unsigned MSG7  		:8;	unsigned MSG8  		:8;
		unsigned MSG9  		:8;	unsigned MSG10 		:8;	unsigned MSG11 		:8;	unsigned MSG12 		:8;	unsigned MSG13 		:8;	unsigned MSG14 		:8;	unsigned MSG15 		:8;	unsigned MSG16 		:8;
		unsigned MSG17 		:8;	unsigned MSG18 		:8;	unsigned MSG19 		:8;	unsigned MSG20 		:8;	unsigned MSG21 		:8;	unsigned MSG22 		:8;	unsigned MSG23 		:8;	unsigned MSG24 		:8;
		unsigned MSG25 		:8;	unsigned MSG26 		:8;	unsigned MSG27 		:8;	unsigned MSG28 		:8;	unsigned MSG29 		:8;	unsigned MSG30 		:8;	unsigned MSG31 		:8;	unsigned MSG32 		:8;
		unsigned MSG33 		:8;	unsigned MSG34 		:8;	unsigned MSG35 		:8;	unsigned MSG36 		:8;	unsigned MSG37 		:8;	unsigned MSG38 		:8;	unsigned MSG39 		:8;	unsigned MSG40 		:8;
		unsigned MSG41 		:8;	unsigned MSG42 		:8;	unsigned MSG43 		:8;	unsigned MSG44 		:8;	unsigned MSG45 		:8;	unsigned MSG46 		:8;	unsigned MSG47 		:8;	unsigned MSG48 		:8;
		unsigned MSG49 		:8;	unsigned MSG50 		:8;	unsigned MSG51 		:8;	unsigned MSG52 		:8;	unsigned MSG53 		:8;	unsigned MSG54 		:8;	unsigned MSG55 		:8;	unsigned MSG56 		:8;
		unsigned MSG57 		:8;	unsigned MSG58 		:8;	unsigned MSG59 		:8;	unsigned MSG60 		:8;	unsigned MSG61 		:8;	unsigned MSG62 		:8;	unsigned MSG63 		:8;	unsigned MSG64 		:8;
		unsigned MSG65 		:8;	unsigned MSG66 		:8;	unsigned MSG67 		:8;	unsigned MSG68 		:8;	unsigned MSG69 		:8;	unsigned MSG70 		:8;	unsigned MSG71 		:8;	unsigned MSG72 		:8;
		unsigned MSG73 		:8;	unsigned MSG74 		:8;	unsigned MSG75 		:8;	unsigned MSG76 		:8;	unsigned MSG77 		:8;	unsigned MSG78 		:8;	unsigned MSG79 		:8;	unsigned MSG80 		:8;
		unsigned MSG81 		:8;	unsigned MSG82 		:8;	unsigned MSG83 		:8;	unsigned MSG84 		:8;	unsigned MSG85 		:8;	unsigned MSG86 		:8;	unsigned MSG87 		:8;	unsigned MSG88 		:8;
		unsigned MSG89 		:8;	unsigned MSG90 		:8;	unsigned MSG91 		:8;	unsigned MSG92 		:8;	unsigned MSG93 		:8;	unsigned MSG94 		:8;	unsigned MSG95 		:8;	unsigned MSG96 		:8;
		unsigned MSG97 		:8;	unsigned MSG98 		:8;	unsigned MSG99 		:8;	unsigned MSG100		:8;	unsigned MSG101		:8;	unsigned MSG102		:8;	unsigned MSG103		:8;	unsigned MSG104		:8;
		unsigned MSG105		:8;	unsigned MSG106		:8;	unsigned MSG107		:8;	unsigned MSG108		:8;	unsigned MSG109		:8;	unsigned MSG110		:8;	unsigned MSG111		:8;	unsigned MSG112		:8;
		unsigned MSG113		:8;	unsigned MSG114		:8;	unsigned MSG115		:8;	unsigned MSG116		:8;	unsigned MSG117		:8;	unsigned MSG118		:8;	unsigned MSG119		:8;	unsigned MSG120		:8;
		unsigned MSG121		:8;	unsigned MSG122		:8;	unsigned MSG123		:8;	unsigned MSG124		:8;	unsigned MSG125		:8;	unsigned MSG126		:8;	unsigned MSG127		:8;	unsigned MSG128		:8;
		unsigned MSG129		:8;	unsigned MSG130		:8;	unsigned MSG131		:8;	unsigned MSG132		:8;	unsigned MSG133		:8;	unsigned MSG134		:8;	unsigned MSG135		:8;	unsigned MSG136		:8;
		unsigned MSG137		:8;	unsigned MSG138		:8;	unsigned MSG139		:8;	unsigned MSG140		:8;	unsigned MSG141		:8;	unsigned MSG142		:8;	unsigned MSG143		:8;	unsigned MSG144		:8;
		unsigned MSG145		:8;	unsigned MSG146		:8;	unsigned MSG147		:8;	unsigned MSG148		:8;	unsigned MSG149		:8;	unsigned MSG150		:8;	unsigned MSG151		:8;	unsigned MSG152		:8;
		unsigned MSG153		:8;	unsigned MSG154		:8;	unsigned MSG155		:8;	unsigned MSG156		:8;	unsigned MSG157		:8;	unsigned MSG158		:8;	unsigned MSG159		:8;	unsigned MSG160		:8;
		unsigned MSG161		:8;	unsigned MSG162		:8;	unsigned MSG163		:8;	unsigned MSG164		:8;	unsigned MSG165		:8;	unsigned MSG166		:8;	unsigned MSG167		:8;	unsigned MSG168		:8;
		unsigned MSG169		:8;	unsigned MSG170		:8;	unsigned MSG171		:8;	unsigned MSG172		:8;	unsigned MSG173		:8;	unsigned MSG174		:8;	unsigned MSG175		:8;	unsigned MSG176		:8;
		unsigned MSG177		:8;	unsigned MSG178		:8;	unsigned MSG179		:8;	unsigned MSG180		:8;	unsigned MSG181		:8;	unsigned MSG182		:8;	unsigned MSG183		:8;	unsigned MSG184		:8;
		unsigned MSG185		:8;	unsigned MSG186		:8;	unsigned MSG187		:8;	unsigned MSG188		:8;	unsigned MSG189		:8;	unsigned MSG190		:8;	unsigned MSG191		:8;	unsigned MSG192		:8;
		unsigned MSG193		:8;	unsigned MSG194		:8;	unsigned MSG195		:8;	unsigned MSG196		:8;	unsigned MSG197		:8;	unsigned MSG198		:8;	unsigned MSG199		:8;	unsigned MSG200		:8;
		unsigned MSG201		:8;	unsigned MSG202		:8;	unsigned MSG203		:8;	unsigned MSG204		:8;	unsigned MSG205		:8;	unsigned MSG206		:8;	unsigned MSG207		:8;	unsigned MSG208		:8;
		unsigned MSG209		:8;	unsigned MSG210		:8;	unsigned MSG211		:8;	unsigned MSG212		:8;	unsigned MSG213		:8;	unsigned MSG214		:8;	unsigned MSG215		:8;	unsigned MSG216		:8;
		unsigned MSG217		:8;	unsigned MSG218		:8;	unsigned MSG219		:8;	unsigned MSG220		:8;	unsigned MSG221		:8;	unsigned MSG222		:8;	unsigned MSG223		:8;	unsigned MSG224		:8;
		unsigned MSG225		:8;	unsigned MSG226		:8;	unsigned MSG227		:8;	unsigned MSG228		:8;	unsigned MSG229		:8;	unsigned MSG230		:8;	unsigned MSG231		:8;	unsigned MSG232		:8;
		unsigned MSG233		:8;	unsigned MSG234		:8;	unsigned MSG235		:8;	unsigned MSG236		:8;	unsigned MSG237		:8;	unsigned MSG238		:8;	unsigned MSG239		:8;	unsigned MSG240		:8;
		unsigned MSG241		:8;	unsigned MSG242		:8;	unsigned MSG243		:8;	unsigned MSG244		:8;	unsigned MSG245		:8;	unsigned MSG246		:8;	unsigned MSG247		:8;	unsigned MSG248		:8;
		unsigned MSG249		:8;	unsigned MSG250		:8;	unsigned MSG251		:8;	unsigned MSG252		:8;	unsigned MSG253		:8;	unsigned MSG254		:8;	unsigned MSG255		:8;

		unsigned CS			:8;	//
	} TECH_PTC;

	struct{
		unsigned HEADER		:8;
		unsigned TYPE1		:8;
		unsigned TYPE2		:8;
		unsigned CMD		:8;	//4

		unsigned MSG1  		:8;	unsigned MSG2  		:8;	unsigned MSG3  		:8;	unsigned MSG4  		:8;	unsigned MSG5  		:8;	unsigned MSG6  		:8;	unsigned MSG7  		:8;	unsigned MSG8  		:8;
		unsigned MSG9  		:8;	unsigned MSG10 		:8;	unsigned MSG11 		:8;	unsigned MSG12 		:8;	unsigned MSG13 		:8;	unsigned MSG14 		:8;	unsigned MSG15 		:8;	unsigned MSG16 		:8;
		unsigned MSG17 		:8;	unsigned MSG18 		:8;	unsigned MSG19 		:8;	unsigned MSG20 		:8;	unsigned MSG21 		:8;	unsigned MSG22 		:8;	unsigned MSG23 		:8;	unsigned MSG24 		:8;
		unsigned MSG25 		:8;	unsigned MSG26 		:8;	unsigned MSG27 		:8;	unsigned MSG28 		:8;	unsigned MSG29 		:8;	unsigned MSG30 		:8;	unsigned MSG31 		:8;	unsigned MSG32 		:8;
		unsigned MSG33 		:8;	unsigned MSG34 		:8;	unsigned MSG35 		:8;	unsigned MSG36 		:8;	unsigned MSG37 		:8;	unsigned MSG38 		:8;	unsigned MSG39 		:8;	unsigned MSG40 		:8;
		unsigned MSG41 		:8;	unsigned MSG42 		:8;	unsigned MSG43 		:8;	unsigned MSG44 		:8;	unsigned MSG45 		:8;	unsigned MSG46 		:8;	unsigned MSG47 		:8;	unsigned MSG48 		:8;
		unsigned MSG49 		:8;	unsigned MSG50 		:8;	unsigned MSG51 		:8;	unsigned MSG52 		:8;	unsigned MSG53 		:8;	unsigned MSG54 		:8;	unsigned MSG55 		:8;	unsigned MSG56 		:8;
		unsigned MSG57 		:8;	unsigned MSG58 		:8;	unsigned MSG59 		:8;	unsigned MSG60 		:8;	unsigned MSG61 		:8;	unsigned MSG62 		:8;	unsigned MSG63 		:8;	unsigned MSG64 		:8;
		unsigned MSG65 		:8;	unsigned MSG66 		:8;	unsigned MSG67 		:8;	unsigned MSG68 		:8;	unsigned MSG69 		:8;	unsigned MSG70 		:8;	unsigned MSG71 		:8;	unsigned MSG72 		:8;
		unsigned MSG73 		:8;	unsigned MSG74 		:8;	unsigned MSG75 		:8;	unsigned MSG76 		:8;	unsigned MSG77 		:8;	unsigned MSG78 		:8;	unsigned MSG79 		:8;	unsigned MSG80 		:8;
		unsigned MSG81 		:8;	unsigned MSG82 		:8;	unsigned MSG83 		:8;	unsigned MSG84 		:8;	unsigned MSG85 		:8;	unsigned MSG86 		:8;	unsigned MSG87 		:8;	unsigned MSG88 		:8;
		unsigned MSG89 		:8;	unsigned MSG90 		:8;	unsigned MSG91 		:8;	unsigned MSG92 		:8;	unsigned MSG93 		:8;	unsigned MSG94 		:8;	unsigned MSG95 		:8;	unsigned MSG96 		:8;
		unsigned MSG97 		:8;	unsigned MSG98 		:8;	unsigned MSG99 		:8;	unsigned MSG100		:8;	unsigned MSG101		:8;	unsigned MSG102		:8;	unsigned MSG103		:8;	unsigned MSG104		:8;
		unsigned MSG105		:8;	unsigned MSG106		:8;	unsigned MSG107		:8;	unsigned MSG108		:8;	unsigned MSG109		:8;	unsigned MSG110		:8;	unsigned MSG111		:8;	unsigned MSG112		:8;
		unsigned MSG113		:8;	unsigned MSG114		:8;	unsigned MSG115		:8;	unsigned MSG116		:8;	unsigned MSG117		:8;	unsigned MSG118		:8;	unsigned MSG119		:8;	unsigned MSG120		:8;
		unsigned MSG121		:8;	unsigned MSG122		:8;	unsigned MSG123		:8;	unsigned MSG124		:8;	unsigned MSG125		:8;	unsigned MSG126		:8;	unsigned MSG127		:8;	unsigned MSG128		:8;
		unsigned MSG129		:8;	unsigned MSG130		:8;	unsigned MSG131		:8;	unsigned MSG132		:8;	unsigned MSG133		:8;	unsigned MSG134		:8;	unsigned MSG135		:8;	unsigned MSG136		:8;
		unsigned MSG137		:8;	unsigned MSG138		:8;	unsigned MSG139		:8;	unsigned MSG140		:8;	unsigned MSG141		:8;	unsigned MSG142		:8;	unsigned MSG143		:8;	unsigned MSG144		:8;
		unsigned MSG145		:8;	unsigned MSG146		:8;	unsigned MSG147		:8;	unsigned MSG148		:8;	unsigned MSG149		:8;	unsigned MSG150		:8;	unsigned MSG151		:8;	unsigned MSG152		:8;
		unsigned MSG153		:8;	unsigned MSG154		:8;	unsigned MSG155		:8;	unsigned MSG156		:8;	unsigned MSG157		:8;	unsigned MSG158		:8;	unsigned MSG159		:8;	unsigned MSG160		:8;
		unsigned MSG161		:8;	unsigned MSG162		:8;	unsigned MSG163		:8;	unsigned MSG164		:8;	unsigned MSG165		:8;	unsigned MSG166		:8;	unsigned MSG167		:8;	unsigned MSG168		:8;
		unsigned MSG169		:8;	unsigned MSG170		:8;	unsigned MSG171		:8;	unsigned MSG172		:8;	unsigned MSG173		:8;	unsigned MSG174		:8;	unsigned MSG175		:8;	unsigned MSG176		:8;
		unsigned MSG177		:8;	unsigned MSG178		:8;	unsigned MSG179		:8;	unsigned MSG180		:8;	unsigned MSG181		:8;	unsigned MSG182		:8;	unsigned MSG183		:8;	unsigned MSG184		:8;
		unsigned MSG185		:8;	unsigned MSG186		:8;	unsigned MSG187		:8;	unsigned MSG188		:8;	unsigned MSG189		:8;	unsigned MSG190		:8;	unsigned MSG191		:8;	unsigned MSG192		:8;
		unsigned MSG193		:8;	unsigned MSG194		:8;	unsigned MSG195		:8;	unsigned MSG196		:8;	unsigned MSG197		:8;	unsigned MSG198		:8;	unsigned MSG199		:8;	unsigned MSG200		:8;
		unsigned MSG201		:8;	unsigned MSG202		:8;	unsigned MSG203		:8;	unsigned MSG204		:8;	unsigned MSG205		:8;	unsigned MSG206		:8;	unsigned MSG207		:8;	unsigned MSG208		:8;
		unsigned MSG209		:8;	unsigned MSG210		:8;	unsigned MSG211		:8;	unsigned MSG212		:8;	unsigned MSG213		:8;	unsigned MSG214		:8;	unsigned MSG215		:8;	unsigned MSG216		:8;
		unsigned MSG217		:8;	unsigned MSG218		:8;	unsigned MSG219		:8;	unsigned MSG220		:8;	unsigned MSG221		:8;	unsigned MSG222		:8;	unsigned MSG223		:8;	unsigned MSG224		:8;
		unsigned MSG225		:8;	unsigned MSG226		:8;	unsigned MSG227		:8;	unsigned MSG228		:8;	unsigned MSG229		:8;	unsigned MSG230		:8;	unsigned MSG231		:8;	unsigned MSG232		:8;
		unsigned MSG233		:8;	unsigned MSG234		:8;	unsigned MSG235		:8;	unsigned MSG236		:8;	unsigned MSG237		:8;	unsigned MSG238		:8;	unsigned MSG239		:8;	unsigned MSG240		:8;
		unsigned MSG241		:8;	unsigned MSG242		:8;	unsigned MSG243		:8;	unsigned MSG244		:8;	unsigned MSG245		:8;	unsigned MSG246		:8;	unsigned MSG247		:8;	unsigned MSG248		:8;
		unsigned MSG249		:8;	unsigned MSG250		:8;	unsigned MSG251		:8;	unsigned MSG252		:8;	unsigned MSG253		:8;
		unsigned SOCKET		:8;	unsigned ADDRESS	:8; unsigned LENGTH		:32;
	} VISCA_PTC;
} CNBH_PACKET;

typedef struct _PTC_CNBH_CODEC {
	uint16 cmd;
	EEP_IDX eepidx;
} PTC_CNBH_CODEC;

typedef struct _PTC_CNBT_CB_FUNC
{	//CNB_HEX_TECH_FUNTIONS
	uint32 (*getfunc)(uint32);
	void (*setfunc)(uint32 ,uint32 );
	DAT_TYPE dat_size;
} PTC_CNBT_CB_FUNC;

typedef struct _PLURAL_EVT {
	EEP_IDX eepidx;	//Send Msg
	uint08 length;	//데이터 길이
	COMPOSE_DATA type;
	const DECODE_TYPE 	decode_type;
	const void *evts;
}PLURAL_EVT;

typedef struct _IFU_DECODE_MAPING {
	const uint16 Visca_dat;
	const uint16 dat;
} IFU_DECODE_MAPING;

typedef struct _IFU_DECODE_DIRECT {
	const uint16 min;
	const uint16 max;
} IFU_DECODE_DIRECT;

typedef struct _IFU_DECODE_INTERP {
	const uint16 Visca_min;
	const uint16 Visca_max;
	const uint16 min;
	const uint16 max;
} IFU_DECODE_INTERP;

typedef IFER (*EXPT_FNC)(IFEVT ,EEP_IDX ,uint32 *);

typedef struct _PTC_VISCA_CODEC {
	const uint08 cmd;
	const EEP_IDX eepidx;
	const uint08 length;
	const DECODE_TYPE 	decode_type;
	const void *evts;
} PTC_VISCA_CODEC;

typedef struct _IF_PTC_QUEUE {
	uint08 RxQueue[256];
	uint08 TxQueue[256];
	uint16 RxHead;
	uint16 RxTail;
	uint16 TxHead;
	uint16 TxTail;
} IF_PTC_QUEUE;

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/
/* Interface */
static uint32 GetfuncNull(uint32 addr);
static void SetfuncNull(uint32 addr,uint32 dat);
static IFER EventCallNull(IFEVT evt, IFEVT_PARAM *param);
void PrintCallNull(uint08 x, uint08 y, uint32 ch);
int32 UEepCallNull(IFEVT evt, EEP_IDX idx, int32 val);
void PtcSendCallNull(uint08 buf);

/* Event */
IFER (*EventCall)(IFEVT, IFEVT_PARAM *) = EventCallNull;

/* EEPRom */
int32 (*UEepUpdateCall)(IFEVT, EEP_IDX, int32) = UEepCallNull;

/* OSD */
void (*PrintCall)(uint08, uint08, uint32) = PrintCallNull;
static void PrintItem(uint08 y, const OSD_MAP *pMap);
/* PROTOCOL */
void (*PtcSendCall)(uint08) = PtcSendCallNull;
static IFER Except_Privacy(IFEVT evt ,EEP_IDX idx ,uint32 *data);
static IFER Except_Motion(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Mode_Change(IFEVT evt ,EEP_IDX idx ,uint32 *data);
static IFER Except_Move(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Title(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Mem_Save(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Gamma(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Reg_Set(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Ext_Move(IFEVT evt,EEP_IDX idx,uint32 *data);
static IFER Except_Cant_Handle(IFEVT evt,EEP_IDX idx,uint32 *data);
static void PtcVisca_SendPacket(VISCA_MSG err,uint08 *pack,uint08 size);

/*************************************************************************************************************
* LOCAL TABLES
*************************************************************************************************************/
/***********************************CNBH_TECH CALLBACK FUNCTIONS*********************************************/
PTC_CNBT_CB_FUNC CNBT_Callback[CNBT_MAX+1] = {
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//ISP
	{GetfuncNull, SetfuncNull,	TYPE_8BITS	},	//EEP
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//MOTOR
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//SENSOR
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//VIDEO 1
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//VIDEO 2
	{GetfuncNull, SetfuncNull,	TYPE_32BITS	},	//VIDEO 3
	{GetfuncNull, SetfuncNull,	TYPE_8BITS	},	//Eep Skip
	{GetfuncNull, SetfuncNull,	0			}	//NULL
};

/*************************************MAPING DATA*************************************************/
IFU_DECODE_MAPING Map_dat_On_Off[]		= {	{2		,1		},	{3		,0		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_Off_On[]		= {	{2		,0		},	{3		,1		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING _Map_dat_On_Off[]		= {	{0		,0		},	{1		,1		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING _Map_dat_Off_On[]		= {	{0		,1		},	{1		,0		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_WD_Mode[]		= {	{2		,0		},	{3		,1		},	{6		,2		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING _Map_dat_WD_Mode[]	= {	{1		,0		},	{0		,1		},	{1		,2		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_On_Off2[]		= {	{0x20	,1		},	{0x30	,0		},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_Ae_mode[]		= {	{0x0	,0		},	{0x3	,0x1	},	{0xA	,0x2	},	{0xB	,0x3	},	{0xD	,0x4	},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_Af_Mode[]		= {	{0x0	,0		},	{0x1	,0x1	},	{0x2	,0x2	},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_P_Mode[]		= {	{0x0	,0		},	{0x2	,0x2	},	{0x4	,0x4	},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_Cl_on[]		= {	{0x3	,0		},	{0x4	,0x1	},	{0xffff	,0xffff	}	};
IFU_DECODE_MAPING Map_dat_Wd_ScrDisp[]  = {	{0x0	,0		},	{0x2	,0x2	},	{0x3	,0x3	},	{0xffff	,0xffff	}	};

/*************************************DATA SCALE*************************************************/
IFU_DECODE_DIRECT Drt_dat_NearLmt		= {0x1000	,0xF000};
IFU_DECODE_DIRECT Drt_dat_ZoomPos		= {0x0000	,0x7AC0};
IFU_DECODE_DIRECT Drt_dat_DZmPos		= {0x0000	,0x00EB};
IFU_DECODE_DIRECT Drt_dat_12bits		= {0x0000	,0x0FFF};
IFU_DECODE_DIRECT Drt_dat_1Byte			= {0x0000	,0x00FF};
IFU_DECODE_DIRECT Drt_dat_2Bits			= {0x0000	,0x0003};
IFU_DECODE_DIRECT Drt_dat_4Bits			= {0x0000	,0x000F};
IFU_DECODE_DIRECT Drt_dat_5Bits			= {0x0000	,0x001F};
IFU_DECODE_DIRECT Drt_dat_AE_Rsp		= {0x0001	,0x0030};
IFU_DECODE_DIRECT Drt_dat_Aicr_Thrs_l	= {0x0000	,0x001C};
IFU_DECODE_DIRECT Drt_dat_Gain_lmt		= {0x0004	,0x000F};
#if (VISCA_COMPILE == VSC_TYPE_EH6300)
IFU_DECODE_DIRECT Drt_dat_Wb_Mode		= {0x0000	,0x0008};
IFU_DECODE_DIRECT Drt_dat_Wd_Mode		= {0x0000	,0x0004};
IFU_DECODE_DIRECT Drt_dat_Det_Sens		= {0x0000	,0x0002};
IFU_DECODE_DIRECT Drt_dat_Bucorr_Lv		= {0x0000	,0x0003};
IFU_DECODE_DIRECT Drt_dat_Bocorr_Lv		= {0x0000	,0x0002};
IFU_DECODE_DIRECT Drt_dat_Short_Expr	= {0x0000	,0x00FF};
#else
IFU_DECODE_DIRECT Drt_dat_Wb_Mode		= {0x0000	,0x0009};
IFU_DECODE_DIRECT Drt_dat_WD_Brt		= {0x0000	,0x0006};
IFU_DECODE_DIRECT Drt_dat_WD_BrtComp	= {0x0000	,0x0003};
IFU_DECODE_DIRECT Drt_dat_WD_CompLv		= {0x0000	,0x0002};
#endif
IFU_DECODE_DIRECT Drt_dat_Ae_ExpComp	= {0x0000	,0x000E};
IFU_DECODE_DIRECT Drt_dat_Aem_Shutter	= {0x0000	,0x0015};
IFU_DECODE_DIRECT Drt_dat_Aem_Iris		= {0x0000	,0x0011};
IFU_DECODE_DIRECT Drt_dat_Hue			= {0x0000	,0x000E};
IFU_DECODE_DIRECT Drt_dat_Gamma			= {0x0000	,0x0004};
IFU_DECODE_DIRECT Drt_dat_Crmsprs		= {0x0000	,0x0003};
IFU_DECODE_DIRECT Drt_dat_DZoomLv		= {0x0000	,0x00EB};
IFU_DECODE_DIRECT Drt_dat_Color_Gain	= {0x0000	,0x000E};
IFU_DECODE_DIRECT Drt_dat_TitlePos_X	= {0x0000	,0x001F};
IFU_DECODE_DIRECT Drt_dat_TitlePos_Y	= {0x0000	,0x000A};
IFU_DECODE_DIRECT Drt_dat_Title_CR		= {0x0000	,0x0006};
IFU_DECODE_DIRECT Drt_dat_Color_Enhance	= {0x0000	,0x007F};
IFU_DECODE_DIRECT Drt_dat_CE_Color		= {0x0000	,0x0008};
IFU_DECODE_DIRECT Drt_dat_GammaOfst0	= {0x0000	,0x0040};
IFU_DECODE_DIRECT Drt_dat_GammaOfst1	= {0x0000	,0x0010};
IFU_DECODE_DIRECT Drt_dat_Nr_Lv			= {0x0000	,0x0005};

/*************************************Plural Command Matrix***************************************/
const PLURAL_EVT PluralEvt_Version[] = //IDX_AF_TIME
{
	{VDX_MODEL_CODE			,2	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0					},
	{VDX_ROM_VERSION		,2	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0					},
	{VDX_SOCKET_NUM			,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0					},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_AfTime[] = //IDX_AF_TIME
{
	{VDX_AF_MOVE_TIME		,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{VDX_AF_INTERVAL_TIME	,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_CS_Preset[] = //IDX_AF_TIME
{
	{VDX_CAM_MEMCUS    		,2	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Cant_Handle	},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_SpotAePos[] =
{
	{VDX_SPOT_AE_X_POS		,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{VDX_SPOT_AE_Y_POS		,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_Cam_ID[] =
{
	{VDX_CAM_ID_H			,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{VDX_CAM_ID_L			,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MemSave[] =
{
	{VDX_MEM_SAVE_ADDR		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Mem_Save	},
	{VDX_MEM_SAVE_DAT		,4	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Mem_Save	},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MemLoad[] =
{
	{VDX_RECIEVE_DATA		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0					},//받은 데이터에 대한 언급
	{VDX_MEM_SAVE_DAT		,4	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Mem_Save	},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_TitleSet1[] =
{
	{VDX_TITLE_LINE    		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_H_POS 		,2	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_COLOR   		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_BLINK 		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_TitleSet2[] =
{
	{VDX_TITLE_LINE			,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH1		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH2		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH3		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH4		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH5		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH6		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH7		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH8		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH9		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH10	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_TitleSet3[] =
{
	{VDX_TITLE_LINE			,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH11	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH12	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH13	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH14	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH15	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH16	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH17	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH18	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH19	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{VDX_TITLE_LINE_CH20	,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Title		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_SetMask[] =
{
	{VDX_MASK_ZONE			,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_MODIFY		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_WIDTH			,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_HEIGHT		,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MaskDisplay[] =
{
	{VDX_MASK_ON			,4	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_SetMaskColor[] =
{
	{VDX_MASK_DISP			,4	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_COLOR_ON		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_COLOR_OFF		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,DECODE_EXCEPTION	,0					}
};
const PLURAL_EVT PluralEvt_SetPanTilt[] =
{
	{VDX_CAM_PAN			,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_CAM_TILT			,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MaksPTZ[] =
{
	{VDX_MASK_ZONE			,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_P				,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_T				,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_Z				,4	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_GetMaksPTZ[] =
{
	{VDX_RECIEVE_DATA		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0					},
	{VDX_MASK_P				,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_T				,3	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_Z				,4	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MDFunc[] =
{
	{VDX_MD_DISP			,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_2Bits		},
	{VDX_MD_FRAME			,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{VDX_MD_THRS_VAL		,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{VDX_MD_INTERVAL_TIME	,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_1Byte		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_MDWindow[] =
{
	{VDX_MD_ZONE			,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_SRT_H_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_SRT_V_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_STP_H_POS		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_STP_V_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{IDX_NULL				,0	,0				,0					,0					}
};
const PLURAL_EVT PluralEvt_GetMDWindow[] =
{
	{VDX_RECIEVE_DATA		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,0					},
	{VDX_MD_SRT_H_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_SRT_V_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_STP_H_POS		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Motion		},
	{VDX_MD_STP_V_POS		,1	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Motion		},
	{IDX_NULL				,0	,0				,0					,0					},
};
const PLURAL_EVT PluralEvt_ViscaREG[] =
{
	{VDX_VSC_REG_ADDR		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Reg_Set		},
	{VDX_VSC_REG_DAT		,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Reg_Set		},
	{IDX_NULL				,0	,0				,0					,0		}
};
const PLURAL_EVT PluralEvt_GetViscaREG[] =
{
	{VDX_RECIEVE_DATA		,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,0		},
	{VDX_VSC_REG_DAT		,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Reg_Set		},
	{IDX_NULL				,0	,0				,0					,0		}
};
#if VISCA_COMPILE == VSC_TYPE_EH6300
const PLURAL_EVT PluralEvt_CrEnhance[] =
{
	{VDX_CE_THRS_HIGH		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{VDX_CE_THRS_MID		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{VDX_CE_THRS_LOW		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_4Bits		},
	{VDX_CE_COLOR_HIGH		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_CE_Color	},
	{VDX_CE_COLOR_LOW		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_CE_Color	},
	{IDX_NULL				,0	,0				,0					,0		}
};
#else
const PLURAL_EVT PluralEvt_CrEnhance[] =
{
	{VDX_CE_THRS_VAL		,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_Y_HI			,2	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_CR_HI			,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_CB_HI			,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_Y_LI			,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_CR_LI			,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{VDX_CE_CB_LI			,1	,COMPOSE_D_FULL	,DECODE_DIRECT		,&Drt_dat_Color_Enhance	},
	{IDX_NULL				,0	,0				,0					,0		}
};
#endif
const PLURAL_EVT PluralEvt_GammaOffset[] =
{
	{VDX_GAM_OFFSET_S		,4	,COMPOSE_D_HALF	,DECODE_MAPING		,_Map_dat_On_Off		},
	{VDX_GAM_OFFSET			,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Gamma			},
	{IDX_NULL				,0	,0				,0					,0		}
};
#if VISCA_COMPILE == VSC_TYPE_EH6300
const PLURAL_EVT PluralEvt_WdParam[] =
{
	{VDX_WD_SCR_DISP		,1	,COMPOSE_D_HALF	,DECODE_MAPING		,Map_dat_Wd_ScrDisp		},
	{VDX_WD_DET_SENS		,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_Det_Sens		},
	{VDX_WD_BUCORR_LV		,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_Bucorr_Lv		},
	{VDX_WD_BOCORR_LV		,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_Bocorr_Lv		},
	{VDX_WD_SHORT_EXPR		,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_Short_Expr	},
	{IDX_NULL				,0	,0				,0					,0		}
};
#else
const PLURAL_EVT PluralEvt_WdParam[] =
{
	{VDX_WD_BRT_L			,2	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_WD_Brt		},
	{VDX_WD_BRT_COMP		,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_WD_BrtComp	},
	{VDX_WD_COMP_L			,1	,COMPOSE_D_HALF	,DECODE_DIRECT		,&Drt_dat_WD_CompLv		},
	{IDX_NULL				,0	,0				,0					,0		}
};
#endif
const PLURAL_EVT PluralEvt_NonInterLock[] =
{
	{VDX_MASK_I				,1	,COMPOSE_D_FULL	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_X_POS			,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_Y_POS			,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_WIDTH			,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{VDX_MASK_HEIGHT		,2	,COMPOSE_D_HALF	,DECODE_EXCEPTION	,Except_Privacy		},
	{IDX_NULL				,0	,0				,0					,0		}
};

/*************************************Structure for Decoding CMD *****************************************/
const PTC_VISCA_CODEC gPtcVisca_Ext_Cmd[]= {
	{	0x02	,VDX_EX_EXPAP_RESET		,2 	,DECODE_EXCEPTION	,Except_Ext_Move		},
	{	0x0E	,VDX_EX_EXPCOMP_RESET	,2 	,DECODE_EXCEPTION	,Except_Ext_Move		},
	{	0x21	,VDX_EX_AICR_ON2OFF		,4 	,DECODE_EXCEPTION	,Except_Ext_Move		},
	{	0x42	,VDX_EX_EXPAP_DIRECT	,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x49	,VDX_EX_COLOR_GAIN		,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x4E	,VDX_EX_EXPCOMP_DIRECT	,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x4F	,VDX_EX_COLOR_HUE		,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x00	,IDX_NULL				,0 	,0					,0						}
};
const PTC_VISCA_CODEC gPtcVisca_Ext_Inq[]= {
	{	0x21	,VDX_EX_AICR_ON2OFF		,4 	,DECODE_EXCEPTION	,Except_Ext_Move		},
	{	0x42	,VDX_EX_EXPAP_DIRECT	,4 	,DECODE_DIRECT		,0						},
	{	0x49	,VDX_EX_COLOR_GAIN		,2 	,DECODE_DIRECT		,0						},
	{	0x4E	,VDX_EX_EXPCOMP_DIRECT	,4 	,DECODE_DIRECT		,0						},
	{	0x4F	,VDX_EX_COLOR_HUE		,2 	,DECODE_DIRECT		,0						},
	{	0x00	,IDX_NULL				,0 	,0					,0						}
};
const PTC_VISCA_CODEC gPtcVisca_Cmd[]= {
	//{	0x0001	,VDX_IF_CLEAR     		,1 	,DECODE_EXCEPTION	,0						},
	{	0x00	,VDX_PWR_ON     		,1 	,DECODE_MAPING		,Map_dat_Off_On			},
	{	0x01	,VDX_ICR_ON				,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x02	,VDX_MOVE_APERTURE		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x03	,VDX_MOVE_RGAIN    		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x04	,VDX_MOVE_BGAIN    		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x06	,VDX_MOVE_DZOOM    		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x07	,VDX_MOVE_ZOOM     		,1 	,DECODE_EXCEPTION	,Except_Cant_Handle		},
	{	0x08	,VDX_MOVE_FOCUS    		,1 	,DECODE_EXCEPTION	,Except_Cant_Handle		},
	{	0x0A	,VDX_MOVE_SHUT     		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x0B	,VDX_MOVE_IRIS     		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x0C	,VDX_MOVE_GAIN     		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x0D	,VDX_MOVE_BRIGHT   		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x0E	,VDX_MOVE_EXPCOMP  		,1 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x10	,VDX_PUSH_WB       		,1 	,DECODE_EXCEPTION	,Except_Cant_Handle		},
	{	0x11	,VDX_IR_COR		 		,1 	,DECODE_MAPING		,_Map_dat_On_Off		},
	{	0x15	,VDX_DISP_ON     		,1 	,DECODE_EXCEPTION	,Except_Mode_Change		},
	{	0x16	,VDX_CFP_ON				,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x18	,VDX_FCS_PUSH			,1 	,DECODE_EXCEPTION	,Except_Cant_Handle		},
	{	0x19	,VDX_INIT_CAM      		,1 	,DECODE_EXCEPTION	,Except_Cant_Handle		},
	{	0x1A	,VDX_CFP_INTERVAL_TIME	,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x1B	,VDX_MD_ON        		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x1C	,IDX_NULL				,6 	,DECODE_PLURAL		,PluralEvt_MDFunc		},
	{	0x1D	,IDX_NULL				,5 	,DECODE_PLURAL		,PluralEvt_MDWindow		},
#if VISCA_COMPILE != VSC_TYPE_EH6300
	{	0x1E	,IDX_NULL				,6 	,DECODE_PLURAL		,PluralEvt_GammaOffset	},
#endif
	{	0x1F	,VDX_EXTEND        		,3 	,DECODE_EXCEPTION	,0						},
#if VISCA_COMPILE == VSC_TYPE_EH6300
	{	0x20	,IDX_NULL				,5 	,DECODE_PLURAL		,PluralEvt_CrEnhance	},
#else
	{	0x20	,IDX_NULL				,8 	,DECODE_PLURAL		,PluralEvt_CrEnhance	},
#endif
	{	0x21	,VDX_AICR_THRS_L   		,4 	,DECODE_DIRECT		,&Drt_dat_Aicr_Thrs_l	},
	{	0x22	,IDX_NULL       		,4 	,DECODE_PLURAL		,PluralEvt_Cam_ID		},
	{	0x23	,IDX_NULL       		,5 	,DECODE_PLURAL		,PluralEvt_MemSave		},
	{	0x24	,IDX_NULL       		,3 	,DECODE_PLURAL		,PluralEvt_ViscaREG		},
	{	0x27	,IDX_NULL       		,4 	,DECODE_PLURAL		,PluralEvt_AfTime		},
	{	0x28	,VDX_NEAR_LIMIT    		,4 	,DECODE_DIRECT		,&Drt_dat_NearLmt		},
	{	0x29	,IDX_NULL		   		,4 	,DECODE_PLURAL		,PluralEvt_SpotAePos	},
	{	0x2C	,VDX_GAIN_LIMIT			,1 	,DECODE_DIRECT		,&Drt_dat_Gain_lmt		},
	{	0x2D	,IDX_NULL				,8 	,DECODE_PLURAL		,PluralEvt_WdParam		},
	{	0x31	,VDX_AICR_ALARM_ON		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x33	,VDX_BLC_ON      		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x34	,VDX_STB_ON      		,1 	,DECODE_EXCEPTION	,Except_Mode_Change		},
	{	0x35	,VDX_WB_MODE      		,1 	,DECODE_DIRECT		,&Drt_dat_Wb_Mode		},
	{	0x36	,VDX_DZOOM_MODE    		,1 	,DECODE_MAPING		,_Map_dat_On_Off		},
	{	0x37	,VDX_DEFOG_ON      		,2 	,DECODE_MAPING		,Map_dat_On_Off2		},
	{	0x38	,VDX_F_MODE	    		,1 	,DECODE_EXCEPTION	,Except_Mode_Change		},
	{	0x39	,VDX_AE_MODE       		,1 	,DECODE_MAPING		,Map_dat_Ae_mode		},
#if VISCA_COMPILE == VSC_TYPE_EH6300
	{	0x3B	,VDX_WD_ALARM      		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x3D	,VDX_WD_MODE       		,1 	,DECODE_DIRECT		,&Drt_dat_Wd_Mode		},
#else
	{	0x3D	,VDX_WD_MODE       		,1 	,DECODE_MAPING		,Map_dat_WD_Mode		},
#endif
	{	0x3E	,VDX_COMP_ON	  		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x3F	,IDX_NULL				,2 	,DECODE_PLURAL		,PluralEvt_CS_Preset	},
	{	0x42	,VDX_APER_GAIN     		,4 	,DECODE_DIRECT		,&Drt_dat_4Bits			},
	{	0x43	,VDX_R_GAIN     		,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x44	,VDX_B_GAIN     		,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x46	,VDX_DZOOM_POS			,4 	,DECODE_DIRECT		,&Drt_dat_DZmPos		},
	{	0x47	,VDX_ZOOM_POS      		,4 	,DECODE_DIRECT		,&Drt_dat_ZoomPos		},
	{	0x48	,VDX_FOCUS_POS     		,4 	,DECODE_DIRECT		,&Drt_dat_NearLmt		},
	{	0x49	,VDX_COLOR_GAIN    		,4 	,DECODE_DIRECT		,&Drt_dat_Color_Gain	},
	{	0x4A	,VDX_SHUTTER_STEP  		,4 	,DECODE_DIRECT		,&Drt_dat_Aem_Shutter	},
	{	0x4B	,VDX_IRIS_STEP     		,4 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x4C	,VDX_GAIN_STEP 			,4 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x4D	,VDX_BRIGHT_STEP   		,4 	,DECODE_EXCEPTION	,Except_Move			},
	{	0x4E	,VDX_EXP_COMP_VAL  		,4 	,DECODE_DIRECT		,&Drt_dat_Ae_ExpComp	},
	{	0x4F	,VDX_COLOR_HUE     		,4 	,DECODE_DIRECT		,&Drt_dat_Hue			},
	{	0x50	,VDX_CE_ON				,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x51	,VDX_AICR_ON      		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x52	,VDX_HR_ON				,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x53	,VDX_NR_SET      		,1 	,DECODE_DIRECT		,&Drt_dat_Nr_Lv			},
	{	0x57	,VDX_AF_MODE       		,1 	,DECODE_MAPING		,Map_dat_Af_Mode		},
	{	0x58	,VDX_AF_SENS      		,1 	,DECODE_MAPING		,Map_dat_Off_On			},
	{	0x59	,VDX_SPOT_AE_ON    		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x5A	,VDX_ASS_ON        		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
#if (VISCA_COMPILE == VSC_TYPE_EH6300)
	{	0x5B	,VDX_GAM_SET       		,1 	,DECODE_DIRECT		,&Drt_dat_Gamma			},
#else
	{	0x5B	,VDX_GAM_SET       		,1 	,DECODE_MAPING		,_Map_dat_On_Off		},
#endif
	{	0x5D	,VDX_AE_RESPONSE   		,1 	,DECODE_DIRECT		,&Drt_dat_AE_Rsp		},
	{	0x5E	,VDX_HIGH_SENS_ON		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x5F	,VDX_CS_LEVEL			,1 	,DECODE_DIRECT		,&Drt_dat_Crmsprs		},
	{	0x61	,VDX_LR_ON        		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x62	,VDX_FREEZE_ON     		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x63	,VDX_P_EFFECT     		,1 	,DECODE_MAPING		,Map_dat_P_Mode			},
	{	0x66	,VDX_FLIP_ON       		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x69	,VDX_CZP_ON		   		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x6A	,VDX_CZP_INTERVAL_TIME	,4 	,DECODE_DIRECT		,&Drt_dat_1Byte			},
	{	0x6F	,IDX_NULL				,9 	,DECODE_PLURAL		,PluralEvt_NonInterLock	},// Non Inter lock mode
	{	0x73	,VDX_TITLE_SET    		,11	,DECODE_PLURAL		,PluralEvt_TitleSet1	},
	{	0x74	,VDX_TITLE_ON         	,1 	,DECODE_EXCEPTION	,Except_Title			},//동작
	{	0x75	,VDX_MUTE_ON       		,1 	,DECODE_EXCEPTION	,Except_Mode_Change		},
	{	0x76	,IDX_NULL				,6 	,DECODE_PLURAL		,PluralEvt_SetMask		},
	{	0x77	,IDX_NULL				,4 	,DECODE_PLURAL		,PluralEvt_MaskDisplay	},
	{	0x78	,IDX_NULL				,6 	,DECODE_PLURAL		,PluralEvt_SetMaskColor	},
	{	0x79	,IDX_NULL				,6	,DECODE_PLURAL		,PluralEvt_SetPanTilt	},
	{	0x7B	,IDX_NULL				,11	,DECODE_PLURAL		,PluralEvt_MaksPTZ		},
	{	0x7C	,VDX_MASK_CL_ON			,1	,DECODE_MAPING		,Map_dat_Cl_on			}
};

/*************************************Structure for Decoding INQ *****************************************/
const PTC_VISCA_CODEC gPtcVisca_Inq[]= {
	{	0x00	,VDX_PWR_ON           	,1	,DECODE_MAPING		,Map_dat_Off_On			},
	//{	0x0002	,VDX_VERSION          	,5	,DECODE_PLURAL		,PluralEvt_Version		},
	{	0x01	,VDX_ICR_ON           	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x06	,VDX_DZOOM_ON       	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x11	,VDX_IR_COR           	,1	,DECODE_MAPING		,_Map_dat_On_Off		},
	{	0x15	,VDX_DISP_ON          	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x16	,VDX_CFP_ON           	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x1A	,VDX_CFP_INTERVAL_TIME	,4	,DECODE_DIRECT		,0						},
	{	0x1B	,VDX_MD_ON            	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x1C	,IDX_NULL				,6 	,DECODE_PLURAL		,PluralEvt_MDFunc		},
	{	0x1D	,IDX_NULL             	,4	,DECODE_PLURAL		,PluralEvt_GetMDWindow	},
#if VISCA_COMPILE != VSC_TYPE_EH6300
	{	0x1E	,IDX_NULL             	,6	,DECODE_PLURAL		,PluralEvt_GammaOffset	},
#endif
	{	0x1F	,VDX_EXTEND             ,4	,DECODE_EXCEPTION	,0						},
#if VISCA_COMPILE == VSC_TYPE_EH6300
	{	0x20	,IDX_NULL           	,5	,DECODE_PLURAL		,PluralEvt_CrEnhance	},
#else
	{	0x20	,IDX_NULL           	,8	,DECODE_PLURAL		,PluralEvt_CrEnhance	},
#endif
	{	0x21	,VDX_AICR_THRS_L       	,4	,DECODE_DIRECT		,0						},
	{	0x22	,IDX_NULL       		,4 	,DECODE_PLURAL		,PluralEvt_Cam_ID		},
	{	0x23	,IDX_NULL             	,4	,DECODE_PLURAL		,PluralEvt_MemLoad		},
	{	0x24	,IDX_NULL             	,2	,DECODE_PLURAL		,PluralEvt_GetViscaREG	},
	{	0x27	,IDX_NULL             	,4	,DECODE_PLURAL		,PluralEvt_AfTime		},
	{	0x28	,VDX_NEAR_LIMIT        	,4	,DECODE_DIRECT		,0						},
	{	0x29	,IDX_NULL             	,4	,DECODE_PLURAL		,PluralEvt_SpotAePos	},
	{	0x2C	,VDX_GAIN_LIMIT        	,1	,DECODE_DIRECT		,0						},
	{	0x2D	,IDX_NULL             	,8	,DECODE_PLURAL		,PluralEvt_WdParam		},
	{	0x31	,VDX_AICR_ALARM_ON    	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x33	,VDX_BLC_ON           	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x34	,VDX_STB_ON      		,1 	,DECODE_MAPING		,Map_dat_Off_On			},
	{	0x35	,VDX_WB_MODE          	,1	,DECODE_DIRECT		,0						},
	{	0x36	,VDX_DZOOM_MODE       	,1	,DECODE_MAPING		,_Map_dat_On_Off		},
	{	0x37	,VDX_DEFOG_ON         	,2	,DECODE_MAPING		,Map_dat_On_Off2		},
	{	0x38	,VDX_F_MODE           	,1	,DECODE_MAPING		,Map_dat_Off_On			},
	{	0x39	,VDX_AE_MODE          	,1	,DECODE_MAPING		,Map_dat_Ae_mode		},
#if VISCA_COMPILE == VSC_TYPE_EH6300
	{	0x3B	,VDX_WD_ALARM      		,1 	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x3D	,VDX_WD_MODE       		,1 	,DECODE_DIRECT		,&Drt_dat_Wd_Mode		},
#else
	{	0x3D	,VDX_WD_MODE          	,1	,DECODE_MAPING		,Map_dat_WD_Mode		},
#endif
	{	0x3E	,VDX_COMP_ON          	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x3F	,VDX_CAM_MEMCUS        	,1	,DECODE_EXCEPTION	,0						},
	{	0x42	,VDX_APER_GAIN        	,4	,DECODE_DIRECT		,0						},
	{	0x43	,VDX_R_GAIN           	,4	,DECODE_DIRECT		,0						},
	{	0x44	,VDX_B_GAIN           	,4	,DECODE_DIRECT		,0						},
	{	0x46	,VDX_DZOOM_POS        	,4	,DECODE_DIRECT		,0						},
	{	0x47	,VDX_ZOOM_POS         	,4	,DECODE_DIRECT		,0						},
	{	0x48	,VDX_FOCUS_POS        	,4	,DECODE_DIRECT		,0						},
	{	0x49	,VDX_COLOR_GAIN       	,4	,DECODE_DIRECT		,0						},
	{	0x4A	,VDX_SHUTTER_STEP     	,4	,DECODE_DIRECT		,0						},
	{	0x4B	,VDX_IRIS_STEP        	,4	,DECODE_DIRECT		,0						},
	{	0x4C	,VDX_GAIN_STEP        	,4	,DECODE_DIRECT		,0						},
	{	0x4D	,VDX_BRIGHT_STEP      	,4	,DECODE_DIRECT		,0						},
	{	0x4E	,VDX_EXP_COMP_VAL     	,4	,DECODE_DIRECT		,0						},
	{	0x4F	,VDX_COLOR_HUE        	,4	,DECODE_DIRECT		,0						},
	{	0x50	,VDX_CE_ON            	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x51	,VDX_AICR_ON          	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x52	,VDX_HR_ON            	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x53	,VDX_NR_SET           	,1	,DECODE_DIRECT		,						},
	{	0x57	,VDX_AF_MODE          	,1	,DECODE_MAPING		,Map_dat_Af_Mode		},
	{	0x58	,VDX_AF_SENS          	,1	,DECODE_MAPING		,Map_dat_Off_On			},
	{	0x59	,VDX_SPOT_AE_ON       	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x5A	,VDX_ASS_ON           	,1	,DECODE_MAPING		,Map_dat_On_Off			},
#if (VISCA_COMPILE == VSC_TYPE_EH6300)
	{	0x5B	,VDX_GAM_SET          	,1	,DECODE_DIRECT		,0						},
#else
	{	0x5B	,VDX_GAM_SET          	,1	,DECODE_MAPING		,_Map_dat_On_Off		},
#endif
	{	0x5D	,VDX_AE_RESPONSE      	,1	,DECODE_DIRECT		,0						},
	{	0x5E	,VDX_HIGH_SENS_ON     	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x5F	,VDX_CS_LEVEL	     	,1	,DECODE_DIRECT		,0						},
	{	0x61	,VDX_LR_ON            	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x62	,VDX_FREEZE_ON         	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x63	,VDX_P_EFFECT         	,1	,DECODE_MAPING		,Map_dat_P_Mode			},
	{	0x66	,VDX_FLIP_ON          	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x68	,VDX_TEMPERATURE      	,4	,DECODE_EXCEPTION	,0						},
	{	0x69	,VDX_CZP_ON           	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x6A	,VDX_CZP_INTERVAL_TIME	,4	,DECODE_DIRECT		,0						},
	{	0x6F	,IDX_MASK_ON           	,4	,DECODE_EXCEPTION	,0						},
	{	0x75	,VDX_MUTE_ON          	,1	,DECODE_MAPING		,Map_dat_On_Off			},
	{	0x77	,IDX_NULL             	,4	,DECODE_PLURAL		,PluralEvt_MaskDisplay	},
	{	0x79	,IDX_NULL             	,6	,DECODE_PLURAL		,PluralEvt_SetPanTilt	},
	{	0x7B	,IDX_NULL             	,10	,DECODE_PLURAL		,PluralEvt_GetMaksPTZ	},
	{	0x7C	,VDX_MASK_CL_ON			,1	,DECODE_MAPING		,Map_dat_Cl_on			}
};

const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ0[] =
{
	{VDX_ZOOM_POS			,2	,0	,16	},
	{VDX_NEAR_LIMIT			,6	,0	,8	},
	{VDX_FOCUS_POS			,8	,0	,16	},
	{VDX_F_MODE				,13	,0	,1	},
	{VDX_DZOOM_ON			,13	,1	,1	},
	{VDX_AF_SENS			,13	,2	,1	},
	{VDX_AF_MODE			,13	,3	,2	},
	{VDX_DZOOM_MODE			,13	,5	,1	},
	{VDX_ZOOM_COMMAND		,14	,0	,1	},
	{VDX_FOCUS_COMMAND		,14	,1	,1	},
	{VDX_CAMERA_RECALL		,14	,2	,1	},
	{VDX_LOW_CONT_DETECTED 	,14	,3	,1	},
	{IDX_NULL				,0	,0	,0	},
};
const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ1[] =
{
	{VDX_R_GAIN			,2	,0	,8	},
	{VDX_B_GAIN			,4	,0	,8	},
	{VDX_WB_MODE		,6	,0	,4	},
	{VDX_APER_GAIN		,7	,0	,4	},
	{VDX_AE_MODE		,8	,0	,5	},
	{VDX_ASS_ON			,9	,0	,1	},
	{VDX_COMP_ON		,9	,1	,1	},
	{VDX_BLC_ON			,9	,2	,1	},
	{VDX_SPOT_AE_ON		,9	,3	,1	},
	{VDX_WD_MODE		,9	,4	,1	},
	{VDX_HR_ON			,9	,5	,1	},
	{VDX_SHUTTER_STEP	,10	,0	,5	},
	{VDX_IRIS_STEP		,11	,0	,5	},
	{VDX_GAIN_STEP		,12	,0	,5	},
	{VDX_BRIGHT_STEP	,13	,0	,5	},
	{VDX_EXP_COMP_VAL	,14	,0	,4	},
	{IDX_NULL			,0	,0	,0	},
};
const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ2[] =
{
	{VDX_PWR_ON			,2	,0	,1	},
	{VDX_AICR_ON		,2	,2	,1	},
	{VDX_AICR_ALARM_ON	,2	,3	,1	},
	{VDX_LR_ON			,3	,2	,1	},
	{VDX_FREEZE_ON		,3	,3	,1	},
	{VDX_ICR_ON			,3	,4	,1	},
	{VDX_STB_HOLD		,3	,5	,1	},
	{VDX_STB_ON			,3	,6	,1	},
	{VDX_DISP_ON		,4	,2	,1	},
	{VDX_TITLE_DISP		,4	,3	,1	}, //전체
	{VDX_MUTE_ON		,4	,4	,1	},
	{VDX_PRI_ON			,4	,5	,1	}, //전체
	{VDX_P_EFFECT		,5	,0	,4	},
	{VDX_CAM_ID_H		,8	,0	,8	},
	{VDX_CAM_ID_L		,10	,0	,8	},
	{VDX_SYS_PROVIDED	,12	,0	,1	},
	{VDX_ICR_PROVIDED	,12	,1	,1	},
	{VDX_STAB_PROVIDED	,12	,2	,1	},
	{VDX_MEM_PROVIDED	,12	,4	,1	},
	{IDX_NULL			,0	,0	,0	},
};
const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ3[] =
{
	{VDX_DZOOM_POS		,2	,0	,8	},
	{VDX_AF_MOVE_TIME	,4	,0	,8	},
	{VDX_AF_INTERVAL_TIME,6	,0	,8	},
	{VDX_SPOT_AE_X_POS	,8	,0	,4	},
	{VDX_SPOT_AE_Y_POS	,9	,0	,4	},
	{VDX_FLIP_ON		,10	,0	,1	},
	{VDX_WD_ALARM		,10	,1	,1	},
	{VDX_MD_ON			,10	,2	,1	},
	{VDX_EFLP_PROVIDED	,11	,0	,1	},
	{VDX_AMASK_PROVIDED ,11	,2	,1	},
	{VDX_COLOR_GAIN		,11	,3	,4	},
	{VDX_AE_RESPONSE	,12	,0	,6	},
	{VDX_NR_SET			,13	,0	,3	},
	{VDX_HIGH_SENS_ON	,13	,3	,1	},
	{VDX_GAM_SET		,13	,4	,3	},
	{VDX_GAIN_LIMIT		,14	,0	,4	},
	{VDX_CS_LEVEL		,14	,4	,3	},
	{IDX_NULL			,0	,0	,0	},
};
const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ4[] =
{
	{VDX_WD_MODE		,2	,0	,3	},
#if VISCA_COMPILE == VSC_TYPE_EH6300
	{VDX_WD_DET_SENS	,3	,0	,2	},
	{VDX_WD_SCR_DISP	,3	,2	,2	},
	{VDX_WD_BOCORR_LV	,4	,0	,2	},
	{VDX_WD_BUCORR_LV	,4	,2	,2	},
	{VDX_WD_SHORT_EXPR	,5	,0	,8	},
#else
	{VDX_WD_BRT_L		,4	,0	,3	},
	{VDX_WD_BRT_COMP	,5	,0	,2	},
	{VDX_WD_COMP_L		,6	,0	,2	},
#endif
	{VDX_DEFOG_ON		,7	,0	,1	},
	{IDX_NULL			,0	,0	,0	},
};
const IFEVT_BLOCK_INQ PTC_VSC_BLOCK_INQ5[] =
{
	{VDX_COLOR_HUE		,2	,0	,4	},
	{IDX_NULL			,0	,0	,0	},
};
/************************************* Condition Data *****************************************/
IF_CONDITION Cndtn_ZmFcs_Mov[]	= {{VDX_F_MODE	,	0},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Fcs_Mov[]	= {{VDX_F_MODE	,	0},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Wb_Push[]	= {
									{VDX_WB_MODE	,	0}, {VDX_WB_MODE	,	1}, {VDX_WB_MODE	,	2}, {VDX_WB_MODE	,	4}, {VDX_WB_MODE	,	5},
									{VDX_WB_MODE	,	6}, {VDX_WB_MODE	,	7},	{IDX_NULL		,	0}
								  };
IF_CONDITION Cndtn_Wb_Gain[]	= {
									{VDX_WB_MODE	,	0}, {VDX_WB_MODE	,	1}, {VDX_WB_MODE	,	2}, {VDX_WB_MODE	,	3}, {VDX_WB_MODE	,	4},
									{VDX_WB_MODE	,	6}, {VDX_WB_MODE	,	7},	{IDX_NULL		,	0}
								  };
#if	VISCA_COMPILE == VSC_TYPE_EV6300
IF_CONDITION Cndtn_Shutter[]	= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	3},	{VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	1}, {VDX_WD_MODE	,	2}, {VDX_WD_MODE	,	4},
									{VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Iris[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	2},	{VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	1}, {VDX_WD_MODE	,	2}, {VDX_WD_MODE	,	4},
									{VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Gain[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	2},	{VDX_AE_MODE	,	3}, {VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	1}, {VDX_WD_MODE	,	2}, {VDX_WD_MODE	,	4},
									{VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Bright[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	1},	{VDX_AE_MODE	,	2}, {VDX_AE_MODE	,	3},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	1}, {VDX_WD_MODE	,	2}, {VDX_WD_MODE	,	4},
									{VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
#else
IF_CONDITION Cndtn_Shutter[]	= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	3},	{VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	2}, {VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Iris[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	2},	{VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	2}, {VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Gain[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	2},	{VDX_AE_MODE	,	3}, {VDX_AE_MODE	,	4},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	2}, {VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
IF_CONDITION Cndtn_Bright[]		= {
									{VDX_AE_MODE	,	0},	{VDX_AE_MODE	,	1},	{VDX_AE_MODE	,	2}, {VDX_AE_MODE	,	3},
									{VDX_WD_MODE	,	0}, {VDX_WD_MODE	,	2}, {VDX_DEFOG_ON	,	1}, {IDX_NULL ,	0}
								  };
#endif
IF_CONDITION Cndtn_AE_Auto[]	= {{VDX_AE_MODE		,	1}, {VDX_AE_MODE	,	2}, {VDX_AE_MODE	,	3}, {VDX_AE_MODE	,	4},{IDX_NULL	,	0}};
IF_CONDITION Cndtn_Freeze_off[]	= {{VDX_FREEZE_ON	,	1},	{IDX_NULL ,	0}};

IF_CONDITION Cndtn_Ext_ExComp[]		= {{VDX_EX_EXPC_ON		,	0},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Ext_Icr_F2O[]	= {{VDX_EX_AICR_F2O_ON	,	0},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Ext_Aperture[]	= {{VDX_EX_EXPAP_ON		,	0},	{VDX_FREEZE_ON	,	1}, {IDX_NULL ,	0}};
IF_CONDITION Cndtn_Ext_Cr_CGCH[]	= {{VDX_EX_CGCH_ON		,	0},	{VDX_FREEZE_ON	,	1}, {IDX_NULL ,	0}};
IF_CONDITION Cndtn_Nrm_ExComp[]		= {{VDX_EX_EXPC_ON		,	1},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Nrm_Icr_Thres[]	= {{VDX_EX_AICR_F2O_ON	,	1},	{IDX_NULL ,	0}};
IF_CONDITION Cndtn_Nrm_Aperture[]	= {{VDX_EX_EXPAP_ON		,	1},	{VDX_FREEZE_ON	,	1}, {IDX_NULL ,	0}};
IF_CONDITION Cndtn_Nrm_CGCH[]		= {{VDX_EX_CGCH_ON		,	1},	{VDX_FREEZE_ON	,	1}, {IDX_NULL ,	0}};
/************************************* Structure for VISCA Condition *****************************************/
IF_CONDITIONS IFU_Cndtn[MAX_CONDITION] =
{
	{IDX_NULL 				,IDX_NULL				},//!!!!!반드시 포함되야 됨
	{VDX_FOCUS_POS 			,Cndtn_Fcs_Mov			},
	{VDX_R_GAIN 			,Cndtn_Wb_Gain			},
	{VDX_B_GAIN 			,Cndtn_Wb_Gain			},
	{VDX_SHUTTER_STEP  		,Cndtn_Shutter			},
	{VDX_IRIS_STEP 			,Cndtn_Iris				},
	{VDX_GAIN_STEP 			,Cndtn_Gain				},
	{VDX_BRIGHT_STEP 		,Cndtn_Bright			},
	{VDX_EXP_COMP_VAL  		,Cndtn_Nrm_ExComp		},
	{VDX_BLC_ON 			,Cndtn_AE_Auto			},
	{VDX_WD_MODE 			,Cndtn_AE_Auto			},
	{VDX_DEFOG_ON 			,Cndtn_AE_Auto			},
	{VDX_APER_GAIN 			,Cndtn_Nrm_Aperture		},
	{VDX_LR_ON 				,Cndtn_Freeze_off		},
	{VDX_P_EFFECT			,Cndtn_Freeze_off		},
	{VDX_FLIP_ON			,Cndtn_Freeze_off		},
	{VDX_ICR_ON 			,Cndtn_Freeze_off		},
	{VDX_AICR_ON 			,Cndtn_Freeze_off		},
	{VDX_AICR_THRS_L 		,Cndtn_Nrm_Icr_Thres	},
	{VDX_AICR_ALARM_ON 		,Cndtn_Freeze_off		},
	{VDX_CE_ON 				,Cndtn_Freeze_off		},
	{VDX_CS_LEVEL 			,Cndtn_Freeze_off		},
	{VDX_COLOR_GAIN 		,Cndtn_Nrm_CGCH			},
	{VDX_COLOR_HUE 			,Cndtn_Nrm_CGCH			},
	{VDX_EX_EXPCOMP_RESET 	,Cndtn_Ext_ExComp		},
	{VDX_EX_EXPCOMP_DIRECT 	,Cndtn_Ext_ExComp		},
	{VDX_EX_EXPAP_RESET 	,Cndtn_Ext_Aperture		},
	{VDX_EX_EXPAP_DIRECT 	,Cndtn_Ext_Aperture		},
	{VDX_EX_AICR_ON2OFF 	,Cndtn_Ext_Icr_F2O		},
	{VDX_EX_COLOR_GAIN 		,Cndtn_Ext_Cr_CGCH		},
	{VDX_EX_COLOR_HUE 		,Cndtn_Ext_Cr_CGCH		},
	{VDX_MOVE_RGAIN 		,Cndtn_Wb_Gain			},
	{VDX_MOVE_BGAIN 		,Cndtn_Wb_Gain			},
	{VDX_MOVE_FOCUS 		,Cndtn_Fcs_Mov			},
	{VDX_MOVE_SHUT 			,Cndtn_Shutter			},
	{VDX_MOVE_IRIS 			,Cndtn_Iris				},
	{VDX_MOVE_GAIN 			,Cndtn_Gain				},
	{VDX_MOVE_BRIGHT 		,Cndtn_Bright			},
	{VDX_MOVE_EXPCOMP 		,Cndtn_Nrm_ExComp		},
	{VDX_MOVE_APERTURE 		,Cndtn_Nrm_Aperture		},
	{VDX_PUSH_WB 			,Cndtn_Wb_Push			},
	{VDX_FCS_PUSH 			,Cndtn_Fcs_Mov			},
	{VDX_ZM_FCS_POS 		,Cndtn_Fcs_Mov			},
	{0xffff 				,IDX_NULL				}//!!!!!반드시 포함되야 됨
};

/*************************************************************************************************************
* LOCAL VARIABLE
*************************************************************************************************************/
/* OSD */
uint08 Pri_Zone = 0;
uint08 Md_Zone = 0;
uint08 FReset = 0;
uint08 Reboot = 0;
uint08 Return = 0;
uint08 Exit = 0;
volatile uint08 gKeyCnt = 0;
uint08 gCursor = 0;
uint08 gTitleCursor = 0;
uint08 gLineLimit = 0;
OSD_MAP *gpCurMap = 0;
uint08 gOsdMode = OSD_NORMAL;
uint32 gWinSize[2] = {OSD_MENU_LEN + OSD_ITEM_LEN, OSD_HEIGHT};

#define PRIVACY_ZONE	Pri_Zone
#define MOTION_ZONE		Md_Zone
#define FRESET_VAL		FReset
#define REBOOT_VAL		Reboot
#define RETURN_VAL		Return
#define EXIT_VAL		Exit

/* PRTCL */
uint32 CAM_Pan = 0;
uint32 CAM_Tilt = 0;
uint08 gPtcl_init_flg = 0;
uint08 gPtc_CNBH_Flg = 0;
uint08 gPtc_Visca_Addr = 1;
uint08 gPtc_Visca_Socket = 1;
uint08 Vsc_cam_add;
uint08 Tx_Packet[256];
uint32 key_tmp;
uint08 Mem_Add;
IF_PTC_QUEUE Ptc_Que;
/* Protocol */
PTC_TYPE gPtcType = PTC_CNBH;
CNBH_PACKET gPtcBuf;
uint16 gPtcCursor = 0;
uint32 gDecode = 0;

IF_CONDITION Cndtn_Null = {IDX_NULL ,	0};
IF_CONDITIONS IF_Cndtn = {IDX_NULL ,	&Cndtn_Null};

/* OSD 모듈에서 자체 처리하는 아이템 */
const OSD_STR gFResetItem[] = {OSD_STR_NO, OSD_STR_YES};
const OSD_STR gRebootItem[] = {OSD_STR_SAVE_YES, OSD_STR_SAVE_NO};
const OSD_STR gInitialItem[] = {OSD_STR_SAVE_YES, OSD_STR_SAVE_NO};
const OSD_STR gReturnItem[] = {OSD_STR_NULL, OSD_STR_EXIT_SAVE_YES, OSD_STR_EXIT_SAVE_NO};
const OSD_STR gExitItem[] = {OSD_STR_SAVE_YES, OSD_STR_SAVE_NO};

//uint32 Trace_Pass[5] = {OSD_RKEYDOWN,OSD_RKEYDOWN,OSD_RKEYDOWN,OSD_RKEYDOWN,0x00};
const uint08 OsdTitleMap[TITLEMAP_CNT] = {
	OSD_FONTSPACE,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A,
	0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
	0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
};

#ifdef WIN32	// for VS
	const uint08 gOsdTitlePosition[2][2] = {{0, 1}, {16, 15}};
	const uint08 gOsdIdPosition[2][2] = {{0, 0}, {16, 16}};
#else
	uint08 gOsdTitlePosition[2][2] = {{3, 1}, {15, 16}};
	uint08 gOsdIdPosition[2][2] = {{3, 2}, {16, 16}};
#endif
/*************************************************************************************************************
* GLOBAL VARIABLE
*************************************************************************************************************/
/* EEPRom */
EEP_OSD_DATA		g_OsdData;			// EEPRom ADDRESS 0x0000 ~ 0x00FF
EEP_CAM_OP_DATA		g_CamData;			// EEPRom ADDRESS 0x0500 ~ 0x056F
EEP_VISCA_DATA		g_ViscaData;		// EEPRom ADDRESS 0x1000 ~ 0x13FF
EEP_VISCA_USER		g_ViscaUser;		// EEPRom ADDRESS 0x13F0 ~ 0x13FF

/* OSD */
const OSD_MAP *gpOsdMap;			// OSD Map
const OSD_MAP *gpOsdHiddenMap;	// OSD Hidden Map

/* OSD 상태와 Key 정보 */
OSD_KEY gKeyPrev = OSD_KEYNULL;
OSD_STATE gOsdState = OSD_STATEOFF;

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/
/*************************************************************************************************************
* FUNCTION
*************************************************************************************************************/
/*************************************************************************************************************
* LOCAL FUNCTION
*************************************************************************************************************/
/************************************************************************************************************/

/*************************************************************************************************************
* LOCAL VARIABLE - OSD Font(English) 정의
*************************************************************************************************************/
const uint08 OSD_ALL_NULL[]			         = {""};
const uint08 OSD_ENG_0_30[]	                 = {"0.30"};
const uint08 OSD_ENG_0_35[]	                 = {"0.35"};
const uint08 OSD_ENG_0_40[]	                 = {"0.40"};
const uint08 OSD_ENG_0_45[]	                 = {"0.45"};
const uint08 OSD_ENG_0_50[]	                 = {"0.50"};
const uint08 OSD_ENG_0_55[]	                 = {"0.55"};
const uint08 OSD_ENG_0_60[]	                 = {"0.60"};
const uint08 OSD_ENG_0_65[]	                 = {"0.65"};
const uint08 OSD_ENG_0_70[]	                 = {"0.70"};
const uint08 OSD_ENG_0_75[]	                 = {"0.75"};
const uint08 OSD_ENG_0_80[]	                 = {"0.80"};
const uint08 OSD_ENG_0_85[]	                 = {"0.85"};
const uint08 OSD_ENG_100PER[]			   	 = "100%";
const uint08 OSD_ENG_1080_25P[]			     = {'1','0','8','0','/','2','5','P',OSD_FONTENTER,0};
const uint08 OSD_ENG_1080_30P[]			     = {'1','0','8','0','/','3','0','P',OSD_FONTENTER,0};
const uint08 OSD_ENG_1080_50I[]			     = {'1','0','8','0','/','5','0','I',OSD_FONTENTER,0}; //add KSH 131104
const uint08 OSD_ENG_1080_50P[]			     = {'1','0','8','0','/','5','0','P',OSD_FONTENTER,0}; //add KSH 131104
const uint08 OSD_ENG_1080_60I[]			     = {'1','0','8','0','/','6','0','I',OSD_FONTENTER,0};	//add KSH 131104
const uint08 OSD_ENG_1080_60P[]			     = {'1','0','8','0','/','6','0','P',OSD_FONTENTER,0};	//add KSH 131104
const uint08 OSD_ENG_10CM[]                  = {"10CM"};
const uint08 OSD_ENG_10MIN[]                 = {"10MIN"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_10SEC[]                 = {"10SEC"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_115200[]                = {"115200"};
const uint08 OSD_ENG_11M[]                   = {"11M"};
const uint08 OSD_ENG_19200[]                 = {"19200"};
const uint08 OSD_ENG_1CM[]                   = {"1CM"};
const uint08 OSD_ENG_1M[]                    = {"1M"};
const uint08 OSD_ENG_1SEC[]                  = {"1SEC"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_1_10000[]               = {"1/10000"};
const uint08 OSD_ENG_1_1000[]                = {"1/1000"};
const uint08 OSD_ENG_1_100[]                 = {"1/100"};
const uint08 OSD_ENG_1_120[]                 = {"1/120"};
const uint08 OSD_ENG_1_1250[]                = {"1/1250"};
const uint08 OSD_ENG_1_125[]                 = {"1/125"};
const uint08 OSD_ENG_1_12[]                  = {"1/12"};
const uint08 OSD_ENG_1_1500[]                = {"1/1500"};
const uint08 OSD_ENG_1_150[]                 = {"1/150"};
const uint08 OSD_ENG_1_15[]                  = {"1/15"};
const uint08 OSD_ENG_1_1600[]                = {"1/1600"};
const uint08 OSD_ENG_1_1750[]                = {"1/1750"};
const uint08 OSD_ENG_1_180[]                 = {"1/180"};
const uint08 OSD_ENG_1_1[]                   = {"1/1"};
const uint08 OSD_ENG_1_20000[]               = {"1/20000"};
const uint08 OSD_ENG_1_2000[]                = {"1/2000"};
const uint08 OSD_ENG_1_200[]                 = {"1/200"};
const uint08 OSD_ENG_1_215[]                 = {"1/215"};
const uint08 OSD_ENG_1_23M[]                 = {"1.23M"};
const uint08 OSD_ENG_1_240[]                 = {"1/240"};
const uint08 OSD_ENG_1_2500[]                = {"1/2500"};
const uint08 OSD_ENG_1_250[]                 = {"1/250"};
const uint08 OSD_ENG_1_25[]                  = {"1/25"};
const uint08 OSD_ENG_1_2[]                   = {"1/2"};
const uint08 OSD_ENG_1_3000[]                = {"1/3000"};
const uint08 OSD_ENG_1_300[]                 = {"1/300"};
const uint08 OSD_ENG_1_30[]                  = {"1/30"};
const uint08 OSD_ENG_1_3200[]                = {"1/3200"};
const uint08 OSD_ENG_1_3500[]                = {"1/3500"};
const uint08 OSD_ENG_1_350[]                 = {"1/350"};
const uint08 OSD_ENG_1_3[]                   = {"1/3"};
const uint08 OSD_ENG_1_40000[]               = {"1/40000"};
const uint08 OSD_ENG_1_4000[]                = {"1/4000"};
const uint08 OSD_ENG_1_400[]                 = {"1/400"};
const uint08 OSD_ENG_1_425[]                 = {"1/425"};
const uint08 OSD_ENG_1_480[]                 = {"1/480"};
const uint08 OSD_ENG_1_4[]                   = {"1/4"};
const uint08 OSD_ENG_1_500[]                 = {"1/500"};
const uint08 OSD_ENG_1_50[]                  = {"1/50"};
const uint08 OSD_ENG_1_5M[]                  = {"1.5M"};
const uint08 OSD_ENG_1_6000[]                = {"1/6400"};
const uint08 OSD_ENG_1_600[]                 = {"1/600"};
const uint08 OSD_ENG_1_60[]                  = {"1/60"};
const uint08 OSD_ENG_1_6400[]                = {"1/6400"};
const uint08 OSD_ENG_1_6[]                   = {"1/6"};
const uint08 OSD_ENG_1_725[]                 = {"1/725"};
const uint08 OSD_ENG_1_75[]                  = {"1/75"};
const uint08 OSD_ENG_1_80000[]               = {"1/80000"};
const uint08 OSD_ENG_1_8000[]                = {"1/8000"};
const uint08 OSD_ENG_1_800[]                 = {"1/800"};
const uint08 OSD_ENG_1_85M[]                 = {"1.85M"};
const uint08 OSD_ENG_1_8[]                   = {"1/8"};
const uint08 OSD_ENG_1_90[]                  = {"1/90"};
const uint08 OSD_ENG_1_960[]                 = {"1/960"};
const uint08 OSD_ENG_20SEC[]                 = {"20SEC"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_2400[]                  = {"2400"};
const uint08 OSD_ENG_25M[]                   = {"25M"};
const uint08 OSD_ENG_25PER[]			   	 = "25%";
const uint08 OSD_ENG_2M[]                    = {"2M"};
const uint08 OSD_ENG_30CM[]                  = {"30CM"};
const uint08 OSD_ENG_30SEC[]                 = {"30SEC"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_38400[]                 = {"38400"};
const uint08 OSD_ENG_3M[]                    = {"3M"};
const uint08 OSD_ENG_4800[]                  = {"4800"};
const uint08 OSD_ENG_50CM[]                  = {"50CM"};
const uint08 OSD_ENG_50PER[]			   	 = "50%";
const uint08 OSD_ENG_57600[]                 = {"57600"};
const uint08 OSD_ENG_5M[]                    = {"5M"};
const uint08 OSD_ENG_5SEC[]                  = {"5SEC"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_60SEC[]                 = {"60SEC"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_720_50P[]			     = {'7','2','0','/','5','0','P',OSD_FONTENTER,0};
const uint08 OSD_ENG_720_60P[]			     = {'7','2','0','/','6','0','P',OSD_FONTENTER,0};
const uint08 OSD_ENG_75PER[]			   	 = "75%";
const uint08 OSD_ENG_7M[]                    = {"7M"};
const uint08 OSD_ENG_8CM[]                   = {"8CM"};
const uint08 OSD_ENG_9600[]                  = {"9600"};
const uint08 OSD_ENG_ACE[]                   = {"ACE"};
const uint08 OSD_ENG_ADJUST[]                = {"ADJUST"};
const uint08 OSD_ENG_ADJUST_AE_AF[]          = {"ADJUST AE/AF"};      // 130927 SHKIM ADD
const uint08 OSD_ENG_ADJUST_AF_AE[]          = {"ADJUST AF/AE"};
const uint08 OSD_ENG_ADJUST_COLOR[]          = {"ADJUST COLOR"};      // 130927 SHKIM ADD
const uint08 OSD_ENG_AE_MODE[]               = {"AE MODE"};
const uint08 OSD_ENG_AE_RESPONSE_SPEED[]     = {"RESPONSE SPEED"};
const uint08 OSD_ENG_AE_SPOT_MODE[] 		 = {"AE SPOT MODE"};
const uint08 OSD_ENG_AE_SPOT_X[]    		 = {"SPOT X"};
const uint08 OSD_ENG_AE_SPOT_Y[]    		 = {"SPOT Y"};
const uint08 OSD_ENG_AFLK[]                  = {"AFLK"};
const uint08 OSD_ENG_AF_MODE[]			     = {"AF MODE"};		//add KSH 131104
const uint08 OSD_ENG_AF_SENS[]               = {"AF SENS"};
const uint08 OSD_ENG_AGC_LIMIT[]             = {"AGC LIMIT"};
const uint08 OSD_ENG_AGING[]		         = {"AGING"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_ALARM[]                 = {"ALARM"};
const uint08 OSD_ENG_ALL_ON[]                = {"ALL ON"};
const uint08 OSD_ENG_ANTI_ROLLING[]          = {"ANTI ROLLING"};
const uint08 OSD_ENG_ATW[]                   = {"ATW"};
const uint08 OSD_ENG_AUTO[]                  = {"AUTO"};
const uint08 OSD_ENG_AUTO_PUSH[]			 = {'A','U','T','O',OSD_FONTPUSH,0};			//add KSH 131104
const uint08 OSD_ENG_AUX_OUT[]               = {"AUX OUT"};
const uint08 OSD_ENG_AWB[]                   = {"AWB"};
const uint08 OSD_ENG_BACKLIGHT[]             = {"BACKLIGHT"};
const uint08 OSD_ENG_BAUDRATE[]              = {"BAUDRATE"};
const uint08 OSD_ENG_BLACK[]                 = {"BLACK"};
const uint08 OSD_ENG_BLC[]                   = {"BLC"};
const uint08 OSD_ENG_BLUE[]                  = {"BLUE"};
const uint08 OSD_ENG_BLUE_GAIN[]             = {"BLUE GAIN"};
const uint08 OSD_ENG_BRIGHTNESS[]            = {"BRIGHTNESS"};
const uint08 OSD_ENG_BRIGHT[]                = {"BRIGHT"};
const uint08 OSD_ENG_BURST[]                 = {"BURST"};
const uint08 OSD_ENG_B_GAIN_N[]              = {"B GAIN N"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_B_GAIN_P[]              = {"B GAIN P"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_B_HUE_N[]               = {"B HUE N"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_B_HUE_P[]               = {"B HUE P"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_B_W[]                   = {"B/W"};
const uint08 OSD_ENG_CAMCLASS[]			     = {"CAM CLASS"};
const uint08 OSD_ENG_CAMERA_ID[]             = {"CAMERA ID"};
const uint08 OSD_ENG_CAMERA_TITLE[]          = {"CAMERA TITLE"};
const uint08 OSD_ENG_CBCR_SWAP[]             = {"CBCR_SWAP"};         // 130927 SHKIM ADD
const uint08 OSD_ENG_CDS[]                   = {"CDS"};
const uint08 OSD_ENG_CHANGE_LEVEL[]          = {"CHANGE LEVEL"};
const uint08 OSD_ENG_CHANGE_TEXT[]           = {"CHANGE TEXT"};
const uint08 OSD_ENG_CHROMA[]                = {"CHROMA"};
const uint08 OSD_ENG_CNB_H[]                 = {"CNB-H"};
const uint08 OSD_ENG_COLORBAR[]              = {"COLORBAR"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_COLOR[]                 = {"COLOR"};
const uint08 OSD_ENG_COLOR_BAR[]             = {"COLOR BAR"};
const uint08 OSD_ENG_COLOR_TEMP[]			 = "COLOR TEMP"; 								//add KSH 131104
const uint08 OSD_ENG_COMBINE[]               = {"COMBINE"};
const uint08 OSD_ENG_COMM_ON[]               = {"COMM ON"};		// 131017 SHKIM ADD 추가 까지 <-
const uint08 OSD_ENG_CONTRAST[]              = {"CONTRAST"};
const uint08 OSD_ENG_CRT[]                   = {"CRT"};
const uint08 OSD_ENG_CVBS_MODE[]             = {"CVBS_MODE"};         // 130927 SHKIM ADD
const uint08 OSD_ENG_CYAN[]                  = {"CYAN"};
const uint08 OSD_ENG_DATE[]                  = {"DATE"};
const uint08 OSD_ENG_DAY1[]                  = {"DAY1"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY2[]                  = {"DAY2"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY3[]                  = {"DAY3"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY4[]                  = {"DAY4"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY5[]                  = {"DAY5"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY6[]                  = {"DAY6"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY7[]                  = {"DAY7"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_DAY[]                   = {"DAY"};
const uint08 OSD_ENG_DAY_NIGHT[]             = {"DAY/NIGHT"};
const uint08 OSD_ENG_DEFECT_ADJ[]            = {"DEFECT ADJ"};        // 130927 SHKIM ADD
const uint08 OSD_ENG_DEFOG[]                 = {"DEFOG"};
const uint08 OSD_ENG_DELAY_TIME[]            = {"DELAY TIME"};
const uint08 OSD_ENG_DETECT_DBDR[]           = {"DETECT DBDR"};       // 130927 SHKIM ADD
const uint08 OSD_ENG_DISPLAY[]               = {"DISPLAY"};
const uint08 OSD_ENG_DIST[]                  = {"DIST"};
const uint08 OSD_ENG_DIS[]                   = {"DIS"};
const uint08 OSD_ENG_DNR[]                   = {"DNR"};
const uint08 OSD_ENG_DSS[]                   = {"DSS"};
const uint08 OSD_ENG_DZOOM[]                 = {"DZOOM"};
const uint08 OSD_ENG_DZOOM_MODE[]            = {"DZOOM MODE"};
const uint08 OSD_ENG_ENG[]                   = {"ENG"};
const uint08 OSD_ENG_EXIT[]                  = {"EXIT"};
const uint08 OSD_ENG_EXIT_SAVE_NO[]          = {"EXIT SAVE NO"};
const uint08 OSD_ENG_EXIT_SAVE_YES[]         = {"EXIT SAVE YES"};
const uint08 OSD_ENG_EXPOSURE[]              = {"EXPOSURE"};
const uint08 OSD_ENG_EXT[]                   = {"EXT"};
const uint08 OSD_ENG_EXT_H[]                 = {"EXT-H"};
const uint08 OSD_ENG_EXT_L[]                 = {"EXT-L"};
const uint08 OSD_ENG_FACTORY_RESET[]         = {"FACTORY RESET"};
const uint08 OSD_ENG_FIRMWARE_UPDATE[]       = {"FIRMWARE UPDATE"};
const uint08 OSD_ENG_FLIP[]                  = {"FLIP"};
const uint08 OSD_ENG_FOCUS[]                 = {"FOCUS"};
const uint08 OSD_ENG_FOCUS_MODE[] 		   = {"FOCUS MODE"};	//add KSH 131104
const uint08 OSD_ENG_FREEZE[]                = {"FREEZE"};
const uint08 OSD_ENG_FUNCTION[]              = {"FUNCTION"};
const uint08 OSD_ENG_GAIN_LEVEL[]            = {"GAIN LEVEL"};
const uint08 OSD_ENG_GAMMA1[]                = {"GAMMA1"};
const uint08 OSD_ENG_GAMMA2[]                = {"GAMMA2"};
const uint08 OSD_ENG_GAMMA[]                 = {"GAMMA"};
const uint08 OSD_ENG_GLOBAL_MOTION[]         = {"GLOBAL MOTION"};
const uint08 OSD_ENG_GO_OSD_MENU_SPACETRACE[]= {"GO OSD_MENU_SPACETRACE"};
const uint08 OSD_ENG_GO_TRACE[]              = {"GO TRACE"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_GRAY[]                  = {"GRAY"};
const uint08 OSD_ENG_GREEN[]                 = {"GREEN"};
const uint08 OSD_ENG_HALL_ADJ[]              = {"HALL ADJ"};			// 130927 SHKIM ADD 추가 시작 ->>>>>>>>>>
const uint08 OSD_ENG_HALL_MAX[]			   	 = {"HALL MAX"};       	// 131002 SHKIM ADD
const uint08 OSD_ENG_HALL_MIN[]			   	 = {"HALL MIN"};       	// 131002 SHKIM ADD 추가 까지 <<<<<<<<<<-
const uint08 OSD_ENG_HDTV[]                  = {"HDTV"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_HEIGHT[]                = {"HEIGHT"};
const uint08 OSD_ENG_HIGH[]                  = {"HIGH"};
const uint08 OSD_ENG_HITACHI[]               = {"HITACHI"};
const uint08 OSD_ENG_HLC[]                   = {"HLC"};
const uint08 OSD_ENG_HUE[]                   = {"HUE"};
const uint08 OSD_ENG_H_END[]                 = {"H END"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_H_FLIP[]                = {"H-FLIP"};
const uint08 OSD_ENG_H_SIZE[]                = {"H SIZE"};            // 130927 SHKIM ADD
const uint08 OSD_ENG_H_START[]               = {"H START"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_ID_DISPLAY[]            = {"ID DISPLAY"};
const uint08 OSD_ENG_IMAGE[]                 = {"IMAGE"};
const uint08 OSD_ENG_IMG[]                   = {"IMG"};			// 131017 SHKIM ADD
const uint08 OSD_ENG_INDOOR[]                = {"INDOOR"};
const uint08 OSD_ENG_INF[]                   = {"INF"};
const uint08 OSD_ENG_INITIAL[]               = {"INITIAL"};
const uint08 OSD_ENG_INTERVAL[]		   	     = {"INTERVAL"};		//add KSH 131104
const uint08 OSD_ENG_INT[]                   = {"INT"};
const uint08 OSD_ENG_IRIS_ADJ_AE_DISBLE[]	 = {"AE DISABLE"};
const uint08 OSD_ENG_IRIS_ADJ_GAIN_VAL[]	 = {"GAIN VAL"};
const uint08 OSD_ENG_IRIS_ADJ_IRIS_VAL[]	 = {"IRIS VAL"};
const uint08 OSD_ENG_IRIS_ADJ_ON[]		     = {"ADJ ON"};
const uint08 OSD_ENG_IRIS_ADJ_RESET[]		 = {"RESET"};
const uint08 OSD_ENG_IRIS_ADJ_SHUT_VAL[]	 = {"SHUT VAL"};
const uint08 OSD_ENG_IRIS_ADJ_SUM[]		     = {"AE SUM"};
const uint08 OSD_ENG_IRIS_ADJ_SW2[]		     = {"SW2"};
const uint08 OSD_ENG_IRIS_JUMP[]             = {"IRIS JUMP"};
const uint08 OSD_ENG_IRIS_LEVEL[]            = {"IRIS LEVEL"};
const uint08 OSD_ENG_IRIS_PRIORITY[]         = {"IRIS PRIORITY"};
const uint08 OSD_ENG_LANGUAGE[]              = {"LANGUAGE"};
const uint08 OSD_ENG_LAST_CGAIN[]			 = {"LAST_CGAIN"};
const uint08 OSD_ENG_LAST_YGAIN[]			 = {"LAST_YGAIN"};
const uint08 OSD_ENG_LCD[]                   = {"LCD"};
const uint08 OSD_ENG_LENS_ADJ[]              = {"LENS ADJ"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_LENS_REFRESH[]          = {"LENS REFRESH"};
const uint08 OSD_ENG_LEVEL[]                 = {"LEVEL"};
const uint08 OSD_ENG_LOAD[]                  = {"LOAD"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_LOW[]                   = {"LOW"};
const uint08 OSD_ENG_LOW_ILLUMINATION[]	     = {"LOW_ILLUMINATION"};
const uint08 OSD_ENG_MAGENTA[]               = {"MAGENTA"};
const uint08 OSD_ENG_MAIN_IN[]               = {"MAIN IN"};
const uint08 OSD_ENG_MAIN_OUT[]              = {"MAIN OUT"};
const uint08 OSD_ENG_MANUAL[]                = {"MANUAL"};
const uint08 OSD_ENG_MANUAL_PUSH[]		     = {'M','A','N','U','A','L',OSD_FONTPUSH,0};	//add KSH 131104
const uint08 OSD_ENG_MASK_CENTER[]           = {"MASK CENTER"};
const uint08 OSD_ENG_MAX_SHUTTER[]           = {"MAX SHUTTER"};
const uint08 OSD_ENG_MENU[]                  = {"MENU"};
const uint08 OSD_ENG_MIDDLE[]                = {"MIDDLE"};
const uint08 OSD_ENG_MIN_SHUTTER[]           = {"MIN SHUTTER"};
const uint08 OSD_ENG_MIN[]                   = {"MIN"};
const uint08 OSD_ENG_MODE[]                  = {"MODE"};
const uint08 OSD_ENG_MODULE[]				 = {"MODULE"};
const uint08 OSD_ENG_MOSAIC[]                = {"MOSAIC"};
const uint08 OSD_ENG_MOTION[]                = {"MOTION"};
const uint08 OSD_ENG_MOVE_POSITION[]         = {"MOVE POSITION"};
const uint08 OSD_ENG_NIGHT[]                 = {"NIGHT"};
const uint08 OSD_ENG_NORMAL[]                = {"NORMAL"};
const uint08 OSD_ENG_NO[]                    = {"NO"};
const uint08 OSD_ENG_OFFSET[]                = {"OFFSET"};            // 130927 SHKIM ADD
const uint08 OSD_ENG_OFF[]                   = {"OFF"};
const uint08 OSD_ENG_ONEPUSH[]			     ={"ONEPUSH"};
const uint08 OSD_ENG_ON[]                    = {"ON"};
const uint08 OSD_ENG_OUTDOORAUTO[]		     ={"OUTDOOR AUTO"};
const uint08 OSD_ENG_OUTDOOR[]               = {"OUTDOOR"};
const uint08 OSD_ENG_OUTPUT_FORMAT[]         = {"OUTPUT FORMAT"};
const uint08 OSD_ENG_PELCO_D[]               = {"PELCO-D"};
const uint08 OSD_ENG_PELCO_P[]               = {"PELCO-P"};
const uint08 OSD_ENG_POLICE[]				 = {"POLICE"};
const uint08 OSD_ENG_PORT_ON[]               = {"PORT ON"};
const uint08 OSD_ENG_POS[]                   = {"POS"};
const uint08 OSD_ENG_PRIVACY[]               = {"PRIVACY"};
const uint08 OSD_ENG_PRIVACY_ADJ[]           = {"PRIVACY ADJ"};       // 130927 SHKIM ADD
const uint08 OSD_ENG_PRODUCT_CFG[]           = {"PRODUCT_CFG"};       // 130927 SHKIM ADD
const uint08 OSD_ENG_PROTOCOL[]              = {"PROTOCOL"};
const uint08 OSD_ENG_PUSH[]                  = {"PUSH"};
const uint08 OSD_ENG_QUICK[]                 = {"QUICK"};
const uint08 OSD_ENG_REBOOT[]                = {"REBOOT"};
const uint08 OSD_ENG_RED[]                   = {"RED"};
const uint08 OSD_ENG_RED_GAIN[]              = {"RED GAIN"};
const uint08 OSD_ENG_RESET_ZONE[]            = {"RESET ZONE"};
const uint08 OSD_ENG_RETURN[]                = {"RETURN"};
const uint08 OSD_ENG_RUN[]                   = {"RUN"};               // 130927 SHKIM ADD
const uint08 OSD_ENG_R_GAIN_N[]              = {"R GAIN N"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_R_GAIN_P[]              = {"R GAIN P"};          // 130927 SHKIM ADD
const uint08 OSD_ENG_R_HUE_N[]               = {"R HUE N"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_R_HUE_P[]               = {"R HUE P"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_SAVE_NO[]               = {"SAVE NO"};
const uint08 OSD_ENG_SAVE_YES[]              = {"SAVE YES"};
const uint08 OSD_ENG_SDTV[]                  = {"SDTV"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_SEC[]                   = {"SEC"};
const uint08 OSD_ENG_SENSITIVITY[]           = {"SENSITIVITY"};
const uint08 OSD_ENG_SEPARATE[]              = {"SEPARATE"};
const uint08 OSD_ENG_SERIAL_ON[]             = {"SERIAL ON"};
const uint08 OSD_ENG_SET[]				     = {"SET"};
const uint08 OSD_ENG_SHADE_ADJ[]             = {"SHADE ADJ"};         // 130927 SHKIM ADD
const uint08 OSD_ENG_SHADING[]               = {"SHADING"};
const uint08 OSD_ENG_SHARPNESS[]             = {"SHARPNESS"};
const uint08 OSD_ENG_SHUT_PRIORITY[]         = {"SHUT PRIORITY"};
const uint08 OSD_ENG_SHUT_SPEED[]            = {"SHUT SPEED"};
const uint08 OSD_ENG_SLOW[]                  = {"SLOW"};
const uint08 OSD_ENG_SODIUMVAPORLAMPAUTO[]	 = {"SODIUM LAMP AUTO"};
const uint08 OSD_ENG_SODIUMVAPORLAMPOUTDOORAUTO[] ={"S LAMP OUT AUTO"};
const uint08 OSD_ENG_SODIUMVAPORLAMP[]		 ={"SODIUM LAMP"};
const uint08 OSD_ENG_SPECIAL[]               = {"SPECIAL"};
const uint08 OSD_ENG_START[]				 = {"START"};
const uint08 OSD_ENG_STATE[]                 = {"STATE"};
const uint08 OSD_ENG_STOP[]				     = {"STOP"};
const uint08 OSD_ENG_SYNC[]                  = {"SYNC"};
const uint08 OSD_ENG_SYSTEM[]                = {"SYSTEM"};
const uint08 OSD_ENG_SYSTEM_ADJ[]		     = {"SYSTEM_ADJ"};        // 130927 SHKIM ADD
const uint08 OSD_ENG_SYSTEM_INFO[]           = {"SYSTEM_INFO"};       // 130927 SHKIM ADD 추가 까지 <<<<<<<<<<-
const uint08 OSD_ENG_TEST_IMAGE[]            = {"TEST IMAGE"};        // 130927 SHKIM ADD
const uint08 OSD_ENG_TEXT[]                  = {"TEXT"};			// 131017 SHKIM ADD
const uint08 OSD_ENG_THRESHOLD[]             = {"THRESHOLD"};         // 130927 SHKIM ADD
const uint08 OSD_ENG_TIME[]                  = {"TIME"};
const uint08 OSD_ENG_TRACE[]		         = {"TRACE"};             // 130927 SHKIM ADD
const uint08 OSD_ENG_TRANS[]                 = {"TRANS"};
const uint08 OSD_ENG_TRIGER[]         	     = {"ZOOM TRIGGER"};	//add KSH 131104
const uint08 OSD_ENG_TR_AESTAT[]     	     = {"TR_AESTAT"};	        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_CHOISE[]	         = {"TR_CHOISE"};         // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_COLOR_STATE[]	     = {"TR_COLOR_STATE"};    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_COMM[]		         = {"TR_COMM"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_DBDR[]       	     = {"TR_DBDR"};           // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_DNR[]        	     = {"TR_DNR"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_DZOOM[]      	     = {"TR_DZOOM"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_FOCUS1[]     	     = {"TR_FOCUS1"};	        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_FOCUS2[]     	     = {"TR_FOCUS2"};	        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_FOCUSSTAT[]  	     = {"TR_FOCUSSTAT"};	    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_HALLADJUST[] 	     = {"TR_HALLADJUST"};     // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_ICR[]        	     = {"TR_ICR"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_KEYCONTROL[] 	     = {"TR_KEYCONTROL"};     // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_LENSPARAM[]  	     = {"TR_LENSPARAM"};	    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_MOTION[]     	     = {"TR_MOTION"};	        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_NONE[]		       	 = {"TR_NONE"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PARE1[]      	     = {"TR_PARE1"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PARE2[]      	     = {"TR_PARE2"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PARE3[]      	     = {"TR_PARE3"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PARE4[]      	     = {"TR_PARE4"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PARE5[]      	     = {"TR_PARE5"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PGAGAIN[]    	     = {"TR_PGAGAIN"};	    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PROCNBA[]    	     = {"TR_PROCNBA"};        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PROCNBH[]    	     = {"TR_PROCNBH"};        // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PROPRLCO[]   	     = {"TR_PROPRLCO"};       // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_PROVISCA[]   	     = {"TR_PROVISCA"};       // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_STABILIZER[] 	     = {"TR_STABILIZER"};     // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_WDR[]        	     = {"TR_WDR"};		    // 130927 SHKIM ADD
const uint08 OSD_ENG_TR_ZOOMTRACK[]  	     = {"TR_ZOOMTRACK"};	    // 130927 SHKIM ADD
const uint08 OSD_ENG_TUNNIG[]		         = {"TUNNIG"};            // 130927 SHKIM ADD
const uint08 OSD_ENG_UPDATE_MODE1[]          = {"UPDATE MODE1"};
const uint08 OSD_ENG_UPDATE_MODE2[]          = {"UPDATE MODE2"};
const uint08 OSD_ENG_UPDATE_MODE3[]          = {"UPDATE MODE3"};
const uint08 OSD_ENG_UPDATE_START[]          = {"UPDATE START"};
const uint08 OSD_ENG_USER[]                  = {"USER"};
const uint08 OSD_ENG_USER_ADJUST[]           = {"USER ADJUST"};
const uint08 OSD_ENG_VERSION[]               = {"VERSION"};
const uint08 OSD_ENG_VH_FLIP[]               = {"VH-FLIP"};
const uint08 OSD_ENG_VIDEO_ENCODER[]         = {"VIDEO ENCODER"};
const uint08 OSD_ENG_VIDEO_POSITION[]        = {"VIDEO POSITION"};    // 130927 SHKIM ADD
const uint08 OSD_ENG_VISCA[]                 = {"VISCA"};
const uint08 OSD_ENG_VISCA_OSD_TYPE[]		 = {"VISCA OSD TYPE"};
const uint08 OSD_ENG_V_ACT_END[]             = {"V ACT END"};
const uint08 OSD_ENG_V_ACT_END_BOT[]         = {"V ACT END BOT"};
const uint08 OSD_ENG_V_ACT_START[]           = {"V ACT START"};
const uint08 OSD_ENG_V_ACT_START_BOT[]       = {"V ACT START BOT"};
const uint08 OSD_ENG_V_FLIP[]                = {"V-FLIP"};
const uint08 OSD_ENG_V_TOTAL_SIZE[]          = {"V TOTAL SIZE"};
const uint08 OSD_ENG_WDR[]                   = {"WDR"};
const uint08 OSD_ENG_WHITE[]                 = {"WHITE"};
const uint08 OSD_ENG_WHITE_BALANCE[]         = {"WHITE BALANCE"};
const uint08 OSD_ENG_WIDTH[]                 = {"WIDTH"};
const uint08 OSD_ENG_X10[]                   = {"X10"};
const uint08 OSD_ENG_X128[]                  = {"X128"};
const uint08 OSD_ENG_X12[]                   = {"X12"};
const uint08 OSD_ENG_X16[]                   = {"X16"};
const uint08 OSD_ENG_X20[]                   = {"X20"};
const uint08 OSD_ENG_X24[]                   = {"X24"};
const uint08 OSD_ENG_X256[]                  = {"X256"};
const uint08 OSD_ENG_X2[]                    = {"X2"};
const uint08 OSD_ENG_X32[]                   = {"X32"};
const uint08 OSD_ENG_X3[]                    = {"X3"};
const uint08 OSD_ENG_X4[]                    = {"X4"};
const uint08 OSD_ENG_X512[]                  = {"X512"};
const uint08 OSD_ENG_X5[]                    = {"X5"};
const uint08 OSD_ENG_X64[]                   = {"X64"};
const uint08 OSD_ENG_X6[]                    = {"X6"};
const uint08 OSD_ENG_X8[]                    = {"X8"};
const uint08 OSD_ENG_X_AXIS[]                = {"X AXIS"};            // 130927 SHKIM ADD
const uint08 OSD_ENG_X_POS[]                 = {"X POS"};
const uint08 OSD_ENG_YELLOW[]                = {"YELLOW"};
const uint08 OSD_ENG_YES[]                   = {"YES"};
const uint08 OSD_ENG_Y_AXIS[]                = {"Y AXIS"};            // 130927 SHKIM ADD
const uint08 OSD_ENG_Y_POS[]                 = {"Y POS"};
const uint08 OSD_ENG_ZONE[]                  = {"ZONE"};
const uint08 OSD_ENG_ZOOM[]                  = {"ZOOM"};              // 130927 SHKIM ADD
const uint08 OSD_ENG_ZOOM_END[]              = {"ZOOM END"};
const uint08 OSD_ENG_ZOOM_IN_OUT[]		     = {"ZOOM IN/OUT"};		// 131021 SHKIM ADD 추가 까지 <<<<<<<<<<-
const uint08 OSD_ENG_ZOOM_MAG[]              = {"ZOOM MAG"};
const uint08 OSD_ENG_ZOOM_MODE[]             = {"ZOOM MODE"};
const uint08 OSD_ENG_ZOOM_SPEED[]            = {"ZOOM SPEED"};
const uint08 OSD_ENG_ZOOM_START[]            = {"ZOOM START"};
const uint08 OSD_ENG_ZOOM_TRK_MODE[]         = {"ZOOM TRK MODE"};
const uint08 OSD_ENG__PUSH[]			   	 = {OSD_FONTPUSH,0};		//add KSH 131104

/* 영문 폰트 배열화 */
const uint08 *OSD_ENG[] = {
					OSD_ALL_NULL,
					OSD_ENG_0_30,
					OSD_ENG_0_35,
					OSD_ENG_0_40,
					OSD_ENG_0_45,
					OSD_ENG_0_50,
					OSD_ENG_0_55,
					OSD_ENG_0_60,
					OSD_ENG_0_65,
					OSD_ENG_0_70,
					OSD_ENG_0_75,
					OSD_ENG_0_80,
					OSD_ENG_0_85,
					OSD_ENG_100PER,
					OSD_ENG_1080_25P,
					OSD_ENG_1080_30P,
					OSD_ENG_1080_50I,
					OSD_ENG_1080_50P,
					OSD_ENG_1080_60I,
					OSD_ENG_1080_60P,
					OSD_ENG_10CM,
					OSD_ENG_10MIN,
					OSD_ENG_10SEC,
					OSD_ENG_115200,
					OSD_ENG_11M,
					OSD_ENG_19200,
					OSD_ENG_1CM,
					OSD_ENG_1M,
					OSD_ENG_1SEC,
					OSD_ENG_1_1,
					OSD_ENG_1_100,
					OSD_ENG_1_1000,
					OSD_ENG_1_10000,
					OSD_ENG_1_12,
					OSD_ENG_1_120,
					OSD_ENG_1_125,
					OSD_ENG_1_1250,
					OSD_ENG_1_15,
					OSD_ENG_1_150,
					OSD_ENG_1_1500,
					OSD_ENG_1_1600,
					OSD_ENG_1_1750,
					OSD_ENG_1_180,
					OSD_ENG_1_2,
					OSD_ENG_1_200,
					OSD_ENG_1_2000,
					OSD_ENG_1_20000,
					OSD_ENG_1_215,
					OSD_ENG_1_23M,
					OSD_ENG_1_240,
					OSD_ENG_1_25,
					OSD_ENG_1_250,
					OSD_ENG_1_2500,
					OSD_ENG_1_3,
					OSD_ENG_1_30,
					OSD_ENG_1_300,
					OSD_ENG_1_3000,
					OSD_ENG_1_3200,
					OSD_ENG_1_350,
					OSD_ENG_1_3500,
					OSD_ENG_1_4,
					OSD_ENG_1_400,
					OSD_ENG_1_4000,
					OSD_ENG_1_40000,
					OSD_ENG_1_425,
					OSD_ENG_1_480,
					OSD_ENG_1_50,
					OSD_ENG_1_500,
					OSD_ENG_1_5M,
					OSD_ENG_1_6,
					OSD_ENG_1_60,
					OSD_ENG_1_600,
					OSD_ENG_1_6000,
					OSD_ENG_1_6400,
					OSD_ENG_1_725,
					OSD_ENG_1_75,
					OSD_ENG_1_8,
					OSD_ENG_1_800,
					OSD_ENG_1_8000,
					OSD_ENG_1_80000,
					OSD_ENG_1_85M,
					OSD_ENG_1_90,
					OSD_ENG_1_960,
					OSD_ENG_20SEC,
					OSD_ENG_2400,
					OSD_ENG_25M,
					OSD_ENG_25PER,
					OSD_ENG_2M,
					OSD_ENG_30CM,
					OSD_ENG_30SEC,
					OSD_ENG_38400,
					OSD_ENG_3M,
					OSD_ENG_4800,
					OSD_ENG_50CM,
					OSD_ENG_50PER,
					OSD_ENG_57600,
					OSD_ENG_5M,
					OSD_ENG_5SEC,
					OSD_ENG_60SEC,
					OSD_ENG_720_50P,
					OSD_ENG_720_60P,
					OSD_ENG_75PER,
					OSD_ENG_7M,
					OSD_ENG_8CM,
					OSD_ENG_9600,
					OSD_ENG_ACE,
					OSD_ENG_ADJUST,
					OSD_ENG_ADJUST_AE_AF,
					OSD_ENG_ADJUST_AF_AE,
					OSD_ENG_ADJUST_COLOR,
					OSD_ENG_AE_MODE,
					OSD_ENG_AE_RESPONSE_SPEED,
					OSD_ENG_AE_SPOT_MODE,
					OSD_ENG_AE_SPOT_X,
					OSD_ENG_AE_SPOT_Y,
					OSD_ENG_AFLK,
					OSD_ENG_AF_MODE,
					OSD_ENG_AF_SENS,
					OSD_ENG_AGC_LIMIT,
					OSD_ENG_AGING,
					OSD_ENG_ALARM,
					OSD_ENG_ALL_ON,
					OSD_ENG_ANTI_ROLLING,
					OSD_ENG_ATW,
					OSD_ENG_AUTO,
					OSD_ENG_AUTO_PUSH,
					OSD_ENG_AUX_OUT,
					OSD_ENG_AWB,
					OSD_ENG_BACKLIGHT,
					OSD_ENG_BAUDRATE,
					OSD_ENG_BLACK,
					OSD_ENG_BLC,
					OSD_ENG_BLUE,
					OSD_ENG_BLUE_GAIN,
					OSD_ENG_BRIGHT,
					OSD_ENG_BRIGHTNESS,
					OSD_ENG_BURST,
					OSD_ENG_B_GAIN_N,
					OSD_ENG_B_GAIN_P,
					OSD_ENG_B_HUE_N,
					OSD_ENG_B_HUE_P,
					OSD_ENG_B_W,
					OSD_ENG_CAMCLASS,
					OSD_ENG_CAMERA_ID,
					OSD_ENG_CAMERA_TITLE,
					OSD_ENG_CBCR_SWAP,
					OSD_ENG_CDS,
					OSD_ENG_CHANGE_LEVEL,
					OSD_ENG_CHANGE_TEXT,
					OSD_ENG_CHROMA,
					OSD_ENG_CNB_H,
					OSD_ENG_COLOR,
					OSD_ENG_COLORBAR,
					OSD_ENG_COLOR_BAR,
					OSD_ENG_COLOR_TEMP,
					OSD_ENG_COMBINE,
					OSD_ENG_COMM_ON,
					OSD_ENG_CONTRAST,
					OSD_ENG_CRT,
					OSD_ENG_CVBS_MODE,
					OSD_ENG_CYAN,
					OSD_ENG_DATE,
					OSD_ENG_DAY,
					OSD_ENG_DAY1,
					OSD_ENG_DAY2,
					OSD_ENG_DAY3,
					OSD_ENG_DAY4,
					OSD_ENG_DAY5,
					OSD_ENG_DAY6,
					OSD_ENG_DAY7,
					OSD_ENG_DAY_NIGHT,
					OSD_ENG_DEFECT_ADJ,
					OSD_ENG_DEFOG,
					OSD_ENG_DELAY_TIME,
					OSD_ENG_DETECT_DBDR,
					OSD_ENG_DIS,
					OSD_ENG_DISPLAY,
					OSD_ENG_DIST,
					OSD_ENG_DNR,
					OSD_ENG_DSS,
					OSD_ENG_DZOOM,
					OSD_ENG_DZOOM_MODE,
					OSD_ENG_ENG,
					OSD_ENG_EXIT,
					OSD_ENG_EXIT_SAVE_NO,
					OSD_ENG_EXIT_SAVE_YES,
					OSD_ENG_EXPOSURE,
					OSD_ENG_EXT,
					OSD_ENG_EXT_H,
					OSD_ENG_EXT_L,
					OSD_ENG_FACTORY_RESET,
					OSD_ENG_FIRMWARE_UPDATE,
					OSD_ENG_FLIP,
					OSD_ENG_FOCUS,
					OSD_ENG_FOCUS_MODE,
					OSD_ENG_FREEZE,
					OSD_ENG_FUNCTION,
					OSD_ENG_GAIN_LEVEL,
					OSD_ENG_GAMMA,
					OSD_ENG_GAMMA1,
					OSD_ENG_GAMMA2,
					OSD_ENG_GLOBAL_MOTION,
					OSD_ENG_GO_OSD_MENU_SPACETRACE,
					OSD_ENG_GO_TRACE,
					OSD_ENG_GRAY,
					OSD_ENG_GREEN,
					OSD_ENG_HALL_ADJ,
					OSD_ENG_HALL_MAX,
					OSD_ENG_HALL_MIN,
					OSD_ENG_HDTV,
					OSD_ENG_HEIGHT,
					OSD_ENG_HIGH,
					OSD_ENG_HITACHI,
					OSD_ENG_HLC,
					OSD_ENG_HUE,
					OSD_ENG_H_END,
					OSD_ENG_H_FLIP,
					OSD_ENG_H_SIZE,
					OSD_ENG_H_START,
					OSD_ENG_ID_DISPLAY,
					OSD_ENG_IMAGE,
					OSD_ENG_IMG,
					OSD_ENG_INDOOR,
					OSD_ENG_INF,
					OSD_ENG_INITIAL,
					OSD_ENG_INT,
					OSD_ENG_INTERVAL,
					OSD_ENG_IRIS_ADJ_AE_DISBLE,
					OSD_ENG_IRIS_ADJ_GAIN_VAL,
					OSD_ENG_IRIS_ADJ_IRIS_VAL,
					OSD_ENG_IRIS_ADJ_ON,
					OSD_ENG_IRIS_ADJ_RESET,
					OSD_ENG_IRIS_ADJ_SHUT_VAL,
					OSD_ENG_IRIS_ADJ_SUM,
					OSD_ENG_IRIS_ADJ_SW2,
					OSD_ENG_IRIS_JUMP,
					OSD_ENG_IRIS_LEVEL,
					OSD_ENG_IRIS_PRIORITY,
					OSD_ENG_LANGUAGE,
					OSD_ENG_LAST_CGAIN,
					OSD_ENG_LAST_YGAIN,
					OSD_ENG_LCD,
					OSD_ENG_LENS_ADJ,
					OSD_ENG_LENS_REFRESH,
					OSD_ENG_LEVEL,
					OSD_ENG_LOAD,
					OSD_ENG_LOW,
					OSD_ENG_LOW_ILLUMINATION,
					OSD_ENG_MAGENTA,
					OSD_ENG_MAIN_IN,
					OSD_ENG_MAIN_OUT,
					OSD_ENG_MANUAL,
					OSD_ENG_MANUAL_PUSH,
					OSD_ENG_MASK_CENTER,
					OSD_ENG_MAX_SHUTTER,
					OSD_ENG_MENU,
					OSD_ENG_MIDDLE,
					OSD_ENG_MIN,
					OSD_ENG_MIN_SHUTTER,
					OSD_ENG_MODE,
					OSD_ENG_MODULE,
					OSD_ENG_MOSAIC,
					OSD_ENG_MOTION,
					OSD_ENG_MOVE_POSITION,
					OSD_ENG_NIGHT,
					OSD_ENG_NO,
					OSD_ENG_NORMAL,
					OSD_ENG_OFF,
					OSD_ENG_OFFSET,
					OSD_ENG_ON,
					OSD_ENG_ONEPUSH,
					OSD_ENG_OUTDOOR,
					OSD_ENG_OUTDOORAUTO,
					OSD_ENG_OUTPUT_FORMAT,
					OSD_ENG_PELCO_D,
					OSD_ENG_PELCO_P,
					OSD_ENG_POLICE,
					OSD_ENG_PORT_ON,
					OSD_ENG_POS,
					OSD_ENG_PRIVACY,
					OSD_ENG_PRIVACY_ADJ,
					OSD_ENG_PRODUCT_CFG,
					OSD_ENG_PROTOCOL,
					OSD_ENG_PUSH,
					OSD_ENG_QUICK,
					OSD_ENG_REBOOT,
					OSD_ENG_RED,
					OSD_ENG_RED_GAIN,
					OSD_ENG_RESET_ZONE,
					OSD_ENG_RETURN,
					OSD_ENG_RUN,
					OSD_ENG_R_GAIN_N,
					OSD_ENG_R_GAIN_P,
					OSD_ENG_R_HUE_N,
					OSD_ENG_R_HUE_P,
					OSD_ENG_SAVE_NO,
					OSD_ENG_SAVE_YES,
					OSD_ENG_SDTV,
					OSD_ENG_SEC,
					OSD_ENG_SENSITIVITY,
					OSD_ENG_SEPARATE,
					OSD_ENG_SERIAL_ON,
					OSD_ENG_SET,
					OSD_ENG_SHADE_ADJ,
					OSD_ENG_SHADING,
					OSD_ENG_SHARPNESS,
					OSD_ENG_SHUT_PRIORITY,
					OSD_ENG_SHUT_SPEED,
					OSD_ENG_SLOW,
					OSD_ENG_SODIUMVAPORLAMP,
					OSD_ENG_SODIUMVAPORLAMPAUTO,
					OSD_ENG_SODIUMVAPORLAMPOUTDOORAUTO,
					OSD_ENG_SPECIAL,
					OSD_ENG_START,
					OSD_ENG_STATE,
					OSD_ENG_STOP,
					OSD_ENG_SYNC,
					OSD_ENG_SYSTEM,
					OSD_ENG_SYSTEM_ADJ,
					OSD_ENG_SYSTEM_INFO,
					OSD_ENG_TEST_IMAGE,
					OSD_ENG_TEXT,
					OSD_ENG_THRESHOLD,
					OSD_ENG_TIME,
					OSD_ENG_TRACE,
					OSD_ENG_TRANS,
					OSD_ENG_TRIGER,
					OSD_ENG_TR_AESTAT,
					OSD_ENG_TR_CHOISE,
					OSD_ENG_TR_COLOR_STATE,
					OSD_ENG_TR_COMM,
					OSD_ENG_TR_DBDR,
					OSD_ENG_TR_DNR,
					OSD_ENG_TR_DZOOM,
					OSD_ENG_TR_FOCUS1,
					OSD_ENG_TR_FOCUS2,
					OSD_ENG_TR_FOCUSSTAT,
					OSD_ENG_TR_HALLADJUST,
					OSD_ENG_TR_ICR,
					OSD_ENG_TR_KEYCONTROL,
					OSD_ENG_TR_LENSPARAM,
					OSD_ENG_TR_MOTION,
					OSD_ENG_TR_NONE,
					OSD_ENG_TR_PARE1,
					OSD_ENG_TR_PARE2,
					OSD_ENG_TR_PARE3,
					OSD_ENG_TR_PARE4,
					OSD_ENG_TR_PARE5,
					OSD_ENG_TR_PGAGAIN,
					OSD_ENG_TR_PROCNBA,
					OSD_ENG_TR_PROCNBH,
					OSD_ENG_TR_PROPRLCO,
					OSD_ENG_TR_PROVISCA,
					OSD_ENG_TR_STABILIZER,
					OSD_ENG_TR_WDR,
					OSD_ENG_TR_ZOOMTRACK,
					OSD_ENG_TUNNIG,
					OSD_ENG_UPDATE_MODE1,
					OSD_ENG_UPDATE_MODE2,
					OSD_ENG_UPDATE_MODE3,
					OSD_ENG_UPDATE_START,
					OSD_ENG_USER,
					OSD_ENG_USER_ADJUST,
					OSD_ENG_VERSION,
					OSD_ENG_VH_FLIP,
					OSD_ENG_VIDEO_ENCODER,
					OSD_ENG_VIDEO_POSITION,
					OSD_ENG_VISCA,
					OSD_ENG_VISCA_OSD_TYPE,
					OSD_ENG_V_ACT_END,
					OSD_ENG_V_ACT_END_BOT,
					OSD_ENG_V_ACT_START,
					OSD_ENG_V_ACT_START_BOT,
					OSD_ENG_V_FLIP,
					OSD_ENG_V_TOTAL_SIZE,
					OSD_ENG_WDR,
					OSD_ENG_WHITE,
					OSD_ENG_WHITE_BALANCE,
					OSD_ENG_WIDTH,
					OSD_ENG_X10,
					OSD_ENG_X12,
					OSD_ENG_X128,
					OSD_ENG_X16,
					OSD_ENG_X2,
					OSD_ENG_X20,
					OSD_ENG_X24,
					OSD_ENG_X256,
					OSD_ENG_X3,
					OSD_ENG_X32,
					OSD_ENG_X4,
					OSD_ENG_X5,
					OSD_ENG_X512,
					OSD_ENG_X6,
					OSD_ENG_X64,
					OSD_ENG_X8,
					OSD_ENG_X_AXIS,
					OSD_ENG_X_POS,
					OSD_ENG_YELLOW,
					OSD_ENG_YES,
					OSD_ENG_Y_AXIS,
					OSD_ENG_Y_POS,
					OSD_ENG_ZONE,
					OSD_ENG_ZOOM,
					OSD_ENG_ZOOM_END,
					OSD_ENG_ZOOM_IN_OUT,
					OSD_ENG_ZOOM_MAG,
					OSD_ENG_ZOOM_MODE,
					OSD_ENG_ZOOM_SPEED,
					OSD_ENG_ZOOM_START,
					OSD_ENG_ZOOM_TRK_MODE,
					OSD_ENG__PUSH,
};

// const PTC_CNBH_CODEC gPtcCNBHCodec[] = {
// 	{0x0101, IDX_EEP_STATUS},		{0x0102, IDX_CAM_TYPE},			{0x0103, IDX_CAM_CLASS},		{0x0104, IDX_EEP_VER},			{0x0105, IDX_CCD_TYPE},			{0x0106, IDX_CAM_RES},			{0x0107, IDX_ZOOM_RATIO},			{0x0201, IDX_HALL_ADJ},
// 	{0x0202, IDX_LENS_ADJ},			{0x0203, IDX_DEFECT_ADJ},		{0x0204, IDX_PRI_3D_ADJ},		{0x0205, IDX_COLOR_ADJ},		{0x0206, IDX_SHADE_ADJ},		{0x0301, IDX_USER_PRESET},		{0x0401, IDX_FRESET},				{0x0501, IDX_CAM_POWER},
// 	{0x0502, IDX_REBOOT},			/*{0x0A01, },					{0x0A02, },						{0x0A03, },						{0x0A04, },						{0x0A05, },*/					{0x1001, IDX_LENS_MODE},			{0x1002, IDX_ESC_BRIGHT},
// 	{0x1003, IDX_DC_BRIGHT},		{0x1101, IDX_AE_MODE},			{0x1201, IDX_IRIS_MODE},		{0x1202, IDX_IRIS_LV},			{0x1301, IDX_SHUTTER_MODE},		{0x1302, IDX_SHUTTER_SPD},		{0x1303, IDX_DSS},					{0x1401, IDX_AGC_MODE},
// 	{0x1402, IDX_AGC_AUTO_LV},		{0x1403, IDX_AGC_LV},			{0x1501, IDX_AE_SPD},			{0x1601, IDX_FLK},				{0x2001, IDX_WB_MODE},			{0x2101, IDX_ATW_MODE},			{0x2201, IDX_WB_RGAIN1},			{0x2202, IDX_WB_BGAIN1},
// 	{0x2203, IDX_WB_RGAIN2},		{0x2204, IDX_WB_BGAIN2},		{0x2301, IDX_CR_SUP},			{0x3001, IDX_DN_MODE},			{0x3101, IDX_DN_DLY},			{0x3201, IDX_CHANGE_LV},		{0x3202, IDX_DN_CHANGE_LV},			{0x3203, IDX_ND_CHANGE_LV},
// 	{0x3301, IDX_BURST},			{0x3401, IDX_IR_MODE},			{0x3402, IDX_IR_CHANGE_LV},		{0x3403, IDX_IR_ZONE_USE},		{0x3404, IDX_LED_OUT},			{0x3405, IDX_IR_BRIGHT},		{0x3406, IDX_IR_DELAY_TIME},		{0x3407, IDX_IR_DN_CHANGE_LV},
// 	{0x3408, IDX_IR_ND_CHANGE_LV},	{0x3409, IDX_IR_X},				{0x340A, IDX_IR_Y},				{0x340B, IDX_IR_W},				{0x340C, IDX_IR_H},				{0x4001, IDX_WDR_MODE},			{0x4002, IDX_WDR_LV},				{0x4003, IDX_LONG_LV},
// 	{0x4004, IDX_SHORT_LV},			{0x4005, IDX_WDR_CONTRAST},		{0x4101, IDX_BLC_MODE},			{0x4102, IDX_BLC_LV},			{0x4103, IDX_BLC_X},			{0x4104, IDX_BLC_Y},			{0x4105, IDX_BLC_W},				{0x4106, IDX_BLC_H},
// 	{0x4201, IDX_HLC_MODE},			{0x4202, IDX_HLC_CR},			{0x4203, IDX_HLC_EFCT},			{0x4204, IDX_HLC_CLIP},			{0x4205, IDX_HLC_SCALE},		{0x4301, IDX_DNR_MODE},			{0x4302, IDX_2DNR_LV},				{0x4303, IDX_3DNR_LV},
// 	{0x4304, IDX_G_MOTION},			{0x5001, IDX_MIRROR},			{0x5002, IDX_FREEZE},			{0x5003, IDX_POSI_NEGA},		{0x5004, IDX_IMG_CR_ON},		{0x5101, IDX_DIS},				{0x5201, IDX_HR_MODE},				{0x5301, IDX_SBLC},
// 	{0x5401, IDX_GAMMA},			{0x5402, IDX_GAMMA_MODE},		{0x5501, IDX_SHARP_NIGHT},		{0x5502, IDX_SHARP_DAY},		{0x5601, IDX_CR_RGAIN},			{0x5602, IDX_CR_BGAIN},			{0x5701, IDX_CONTRAST},				{0x5702, IDX_PED_LV},
// 	{0x5703, IDX_CHROMA},			{0x5704, IDX_APERTURE},			{0x5705, IDX_HUE},				{0x5706, IDX_GAMMA_BRIGHT},		{0x5801, IDX_SHADE},			{0x6001, IDX_MD_ALL},			{0x6002, IDX_MD_BLOCK},				{0x6003, IDX_MD_OSD},
// 	{0x6004, IDX_MD_ALARM},			{0x6005, IDX_MD_ZOOM},			{0x6006, IDX_MD_SENS},			{0x6007, IDX_MD_ZOOM_MAG},		{0x6008, IDX_MD_ZOOM_DWELL},	{0x6101, IDX_PRI_ALL_ON},		{0x6102, IDX_PRI_3D_ADJ_X_NT},		{0x6103, IDX_PRI_3D_ADJ_Y_NT},
// 	{0x6104, IDX_PRI_3D_ADJ_X_PAL},	{0x6105, IDX_PRI_3D_ADJ_Y_PAL},	{0x6201, IDX_ALL_DISP},			{0x6202, IDX_ID_DISP},			{0x6203, IDX_TITLE_DISP},		{0x6204, IDX_TIME_DISP},		{0x6205, IDX_MAG_DISP},				{0x6206, IDX_FUNC_DISP},
// 	{0x6301, IDX_ID_X_POS},			{0x6302, IDX_ID_Y_POS},			{0x6303, IDX_TITLE_X_POS},		{0x6304, IDX_TITLE_Y_POS},		{0x6400, IDX_CAM_TITLE1},		{0x6401, IDX_CAM_TITLE2},		{0x6402, IDX_CAM_TITLE3},			{0x6403, IDX_CAM_TITLE4},
// 	{0x6404, IDX_CAM_TITLE5},		{0x6405, IDX_CAM_TITLE6},		{0x6406, IDX_CAM_TITLE7},		{0x6407, IDX_CAM_TITLE8},		{0x6408, IDX_CAM_TITLE9},		{0x6409, IDX_CAM_TITLE10},		{0x640A, IDX_CAM_TITLE11},			{0x640B, IDX_CAM_TITLE12},
// 	{0x640C, IDX_CAM_TITLE13},		{0x640D, IDX_CAM_TITLE14},		{0x640E, IDX_CAM_TITLE15},		{0x640F, IDX_CAM_TITLE16},		{0x6501, IDX_PROTOCOL_TYPE},	{0x6502, IDX_CAM_ID},			{0x6503, IDX_BAUD},					{0x6504, IDX_ID_CHK},
// 	{0x6601, IDX_FONT_SIZE},		{0x6701, IDX_LANGUAGE},			{0x6801, IDX_SYNC},				{0x6802, IDX_LL_PHASE},			{0x6901, IDX_CVBS_OUT},			{0x6902, IDX_CAM_TYPE},			{0x6A01, IDX_DEFOG},				{0x7001, IDX_FOCUS_MODE},
// 	{0x7100, IDX_FOCUS_STOP},		{0x7101, IDX_FOCUS_POS},		{0x7102, IDX_FOCUS_FAR},		{0x7103, IDX_FOCUS_NEAR},		{0x7104, IDX_FOCUS_FAR_VAR},	{0x7105, IDX_FOCUS_NEAR_VAR},	{0x7106, IDX_FOCUS_MODE_SWITCH},	{0x7107, IDX_FOCUS_ONE_PUSH},
// 	{0x7108, IDX_FOCUS_INFINITY},	{0x7201, IDX_FCS_DIST},			{0x7301, IDX_AF_SENSI},			{0x7401, IDX_SCH_AF_TIME},		{0x7501, IDX_LENS_INIT_MODE},	{0x7502, IDX_LENS_REFRESH_DAYS},	{0x7601, IDX_SPOT_MODE},			{0x8001, IDX_DZOOM},
// 	{0x8100, IDX_DZOOM_STOP},		{0x8101, IDX_DZOOM_LV},			{0x8102, IDX_DZOOM_TELE},		{0x8103, IDX_DZOOM_WIDE},		{0x8104, IDX_DZOOM_LMT},		{0x8105, IDX_DZOOM_MODE},		{0x8201, IDX_TRACK_MODE},			{0x8301, IDX_ZOOM_SPD},
// 	{0x8400, IDX_ZOOM_STOP},		{0x8401, IDX_ZOOM_POS},			{0x8401, IDX_ZOOM_FOCUS_POS/*뭥미*/},	{0x8402, IDX_ZOOM_TELE},	{0x8403, IDX_ZOOM_WIDE},	{0x8404, IDX_ZOOM_TELE_VAR},	{0x8405, IDX_ZOOM_WIDE_VAR},		{0x8406, IDX_ZOOM_START},
// 	{0x8407, IDX_ZOOM_END},			{0x8501, IDX_STELE_STEP},		{0x8502, IDX_SWIDE_STEP},		{0x8503, IDX_DEFAULT_STEP},		{0xA001, IDX_MD1_ON},			{0xA002, IDX_MD1_X},			{0xA003, IDX_MD1_Y},				{0xA004, IDX_MD1_W},
// 	{0xA005, IDX_MD1_H},			{0xA006, IDX_MD1_ALARM_ON},		{0xA101, IDX_MD_ON},			{0xA102, IDX_MD_X},				{0xA103, IDX_MD_Y},				{0xA104, IDX_MD_W},				{0xA105, IDX_MD_H},					{0xA106, IDX_MD_ALARM_ON},
// 	{0xA201, IDX_MD_ON},			{0xA202, IDX_MD_X},				{0xA203, IDX_MD_Y},				{0xA204, IDX_MD_W},				{0xA205, IDX_MD_H},				{0xA206, IDX_MD_ALARM_ON},		{0xA301, IDX_MD_ON},				{0xA302, IDX_MD_X},
// 	{0xA303, IDX_MD_Y},				{0xA304, IDX_MD_W},				{0xA305, IDX_MD_H},				{0xA306, IDX_MD_ALARM_ON},		{0xA701, IDX_CAM_PAN_TILT},		{0xA702, IDX_CAM_PAN},			{0xA703, IDX_CAM_TILT},				{0xA801, IDX_PRI_3D1_P},
// 	{0xA802, IDX_PRI_3D1_T},		{0xA803, IDX_PRI_3D1_Z},		{0xA804, IDX_3DPRI_SAVE},		{0xA901, IDX_PRI_3D2_P},		{0xA902, IDX_PRI_3D2_T},		{0xA903, IDX_PRI_3D2_Z},		{0xA904, IDX_3DPRI_SAVE},			{0xAA01, IDX_PRI_3D3_P},
// 	{0xAA02, IDX_PRI_3D3_T},		{0xAA03, IDX_PRI_3D3_Z},		{0xAA04, IDX_3DPRI_SAVE},		{0xAB01, IDX_PRI_3D4_P},		{0xAB02, IDX_PRI_3D4_T},		{0xAB03, IDX_PRI_3D4_Z},		{0xAB04, IDX_3DPRI_SAVE},			{0xAC01, IDX_PRI_3D5_P},
// 	{0xAC02, IDX_PRI_3D5_T},		{0xAC03, IDX_PRI_3D5_Z},		{0xAC04, IDX_3DPRI_SAVE},		{0xAD01, IDX_PRI_3D6_P},		{0xAD02, IDX_PRI_3D6_T},		{0xAD03, IDX_PRI_3D6_Z},		{0xAD04, IDX_3DPRI_SAVE},			{0xAE01, IDX_PRI_3D7_P},
// 	{0xAE02, IDX_PRI_3D7_T},		{0xAE03, IDX_PRI_3D7_Z},		{0xAE04, IDX_3DPRI_SAVE},		{0xAF01, IDX_PRI_3D8_P},		{0xAF02, IDX_PRI_3D8_T},		{0xAF03, IDX_PRI_3D8_Z},		{0xAF04, IDX_3DPRI_SAVE},			{0xB001, IDX_PRI1_ON},
// 	{0xB002, IDX_PRI1_CR},			{0xB003, IDX_PRI1_TRANS},		{0xB004, IDX_PRI1_MOSAIC},		{0xB005, IDX_PRI1_X},			{0xB006, IDX_PRI1_Y},			{0xB007, IDX_PRI1_W},			{0xB008, IDX_PRI1_H},				{0xB101, IDX_PRI2_ON},
// 	{0xB102, IDX_PRI2_CR},			{0xB103, IDX_PRI2_TRANS},		{0xB104, IDX_PRI2_MOSAIC},		{0xB105, IDX_PRI2_X},			{0xB106, IDX_PRI2_Y},			{0xB107, IDX_PRI2_W},			{0xB108, IDX_PRI2_H},				{0xB201, IDX_PRI3_ON},
// 	{0xB202, IDX_PRI3_CR},			{0xB203, IDX_PRI3_TRANS},		{0xB204, IDX_PRI3_MOSAIC},		{0xB205, IDX_PRI3_X},			{0xB206, IDX_PRI3_Y},			{0xB207, IDX_PRI3_W},			{0xB208, IDX_PRI3_H},				{0xB301, IDX_PRI4_ON},
// 	{0xB302, IDX_PRI4_CR},			{0xB303, IDX_PRI4_TRANS},		{0xB304, IDX_PRI4_MOSAIC},		{0xB305, IDX_PRI4_X},			{0xB306, IDX_PRI4_Y},			{0xB307, IDX_PRI4_W},			{0xB308, IDX_PRI4_H},				{0xB401, IDX_PRI5_ON},
// 	{0xB402, IDX_PRI5_CR},			{0xB403, IDX_PRI5_TRANS},		{0xB404, IDX_PRI5_MOSAIC},		{0xB405, IDX_PRI5_X},			{0xB406, IDX_PRI5_Y},			{0xB407, IDX_PRI5_W},			{0xB408, IDX_PRI5_H},				{0xB501, IDX_PRI6_ON},
// 	{0xB502, IDX_PRI6_CR},			{0xB503, IDX_PRI6_TRANS},		{0xB504, IDX_PRI6_MOSAIC},		{0xB505, IDX_PRI6_X},			{0xB506, IDX_PRI6_Y},			{0xB507, IDX_PRI6_W},			{0xB508, IDX_PRI6_H},				{0xB601, IDX_PRI7_ON},
// 	{0xB602, IDX_PRI7_CR},			{0xB603, IDX_PRI7_TRANS},		{0xB604, IDX_PRI7_MOSAIC},		{0xB605, IDX_PRI7_X},			{0xB606, IDX_PRI7_Y},			{0xB607, IDX_PRI7_W},			{0xB608, IDX_PRI7_H},				{0xB701, IDX_PRI8_ON},
// 	{0xB702, IDX_PRI8_CR},			{0xB703, IDX_PRI8_TRANS},		{0xB704, IDX_PRI8_MOSAIC},		{0xB705, IDX_PRI8_X},			{0xB706, IDX_PRI8_Y},			{0xB707, IDX_PRI8_W},			{0xB708, IDX_PRI8_H},				{0xB801, IDX_PRI9_ON},
// 	{0xB802, IDX_PRI9_CR},			{0xB803, IDX_PRI9_TRANS},		{0xB804, IDX_PRI9_MOSAIC},		{0xB805, IDX_PRI9_X},			{0xB806, IDX_PRI9_Y},			{0xB807, IDX_PRI9_W},			{0xB808, IDX_PRI9_H},				{0xB901, IDX_PRI10_ON},
// 	{0xB902, IDX_PRI10_CR},			{0xB903, IDX_PRI10_TRANS},		{0xB904, IDX_PRI10_MOSAIC},		{0xB905, IDX_PRI10_X},			{0xB906, IDX_PRI10_Y},			{0xB907, IDX_PRI10_W},			{0xB908, IDX_PRI10_H},				{0xBA01, IDX_PRI11_ON},
// 	{0xBA02, IDX_PRI11_CR},			{0xBA03, IDX_PRI11_TRANS},		{0xBA04, IDX_PRI11_MOSAIC},		{0xBA05, IDX_PRI11_X},			{0xBA06, IDX_PRI11_Y},			{0xBA07, IDX_PRI11_W},			{0xBA08, IDX_PRI11_H},				{0xBB01, IDX_PRI12_ON},
// 	{0xBB02, IDX_PRI12_CR},			{0xBB03, IDX_PRI12_TRANS},		{0xBB04, IDX_PRI12_MOSAIC},		{0xBB05, IDX_PRI12_X},			{0xBB06, IDX_PRI12_Y},			{0xBB07, IDX_PRI12_W},			{0xBB08, IDX_PRI12_H},				{0xBC01, IDX_PRI13_ON},
// 	{0xBC02, IDX_PRI13_CR},			{0xBC03, IDX_PRI13_TRANS},		{0xBC04, IDX_PRI13_MOSAIC},		{0xBC05, IDX_PRI13_X},			{0xBC06, IDX_PRI13_Y},			{0xBC07, IDX_PRI13_W},			{0xBC08, IDX_PRI13_H},				{0xBD01, IDX_PRI14_ON},
// 	{0xBD02, IDX_PRI14_CR},			{0xBD03, IDX_PRI14_TRANS},		{0xBD04, IDX_PRI14_MOSAIC},		{0xBD05, IDX_PRI14_X},			{0xBD06, IDX_PRI14_Y},			{0xBD07, IDX_PRI14_W},			{0xBD08, IDX_PRI14_H},				{0xBE01, IDX_PRI15_ON},
// 	{0xBE02, IDX_PRI15_CR},			{0xBE03, IDX_PRI15_TRANS},		{0xBE04, IDX_PRI15_MOSAIC},		{0xBE05, IDX_PRI15_X},			{0xBE06, IDX_PRI15_Y},			{0xBE07, IDX_PRI15_W},			{0xBE08, IDX_PRI15_H},				{0xBF01, IDX_PRI16_ON},
// 	{0xBF02, IDX_PRI16_CR},			{0xBF03, IDX_PRI16_TRANS},		{0xBF04, IDX_PRI16_MOSAIC},		{0xBF05, IDX_PRI16_X},			{0xBF06, IDX_PRI16_Y},			{0xBF07, IDX_PRI16_W},			{0xBF08, IDX_PRI16_H},				{0xC001, IDX_OLPF},
// 	{0xC101, IDX_PROTOCOL_RSP},		{0xC201, IDX_TRACE_MODE},		{0xC301, IDX_IRIS_TEST},		{0xC302, IDX_ZOOM_TEST},		{0xC303, IDX_ICR_TEST},			{0xC304, IDX_TEST_DLY},			{0xC401, IDX_DEFECT_TH},			{0xC402, IDX_DEFECT_CNT},
// 	{0xC501, IDX_HALL_TGT_MAX},		{0xC502, IDX_HALL_TGT_MIN},		{0xC503, IDX_HALL_MAX},			{0xC504, IDX_HALL_MIN},			{0xC505, IDX_HALL_OFFSET},		{0xC506, IDX_HALL_GAIN},		{0xC507, IDX_HALL_DAC},				{0xC601, IDX_PEAK_DIFF},
// 	{0xC602, IDX_FOCUS_DIFF},		{0xC603, IDX_ZOOM_DIFF},		{0xC604, IDX_ADJ_DIFF_STEP},	{0xC701, IDX_AF_FACTOR},		{0xC801, IDX_FOCUS_AF_DLY},		{0xC802, IDX_FOCUS_PER},		{0xC803, IDX_FOCUS_TH_LMT},			{0xC804, IDX_FOCUS_ERR_TH},
// 	{0xC805, IDX_FOCUS_BOUNDARY},	{0xC901, IDX_HLIGHT_TH},		{0xCA01, IDX_SCENE_DIV},		{0xCB01, IDX_TIMING1},			{0xCB02, IDX_TIMING2},			{0xCB03, IDX_TIMING3},			{0xCB04, IDX_TIMING4},				{0xCB05, IDX_TIMING5},
// 	{0xCB06, IDX_TIMING6},			{0xCB07, IDX_TIMING7},			{0xCB08, IDX_TIMING8},			{0xCB09, IDX_TIMING9},			{0xCB0A, IDX_TIMING10},			{0xCB0B, IDX_TIMING11},			{0xCB0C, IDX_SAVE_TO_EEP},			{0xCC00, IDX_AD_KEY1_0},
// 	{0xCC01, IDX_AD_KEY1_1},		{0xCC02, IDX_AD_KEY1_2},		{0xCC03, IDX_AD_KEY1_3},		{0xCC04, IDX_AD_KEY1_4},		{0xCC05, IDX_AD_KEY1_5},		{0xCC06, IDX_AD_KEY1_6},		{0xCC07, IDX_AD_KEY1_7},			{0xCC08, IDX_AD_KEY2_0},
// 	{0xCC09, IDX_AD_KEY2_1},		{0xCC0A, IDX_AD_KEY2_2},		{0xCC0B, IDX_AD_KEY2_3},		{0xCC0C, IDX_AD_KEY2_4},		{0xCC0D, IDX_AD_KEY2_5},		{0xCC0E, IDX_AD_KEY2_6},		{0xCC0F, IDX_AD_KEY2_7},			{0xCD00, IDX_CAM_LOGO1},
// 	{0xCD01, IDX_CAM_LOGO2},		{0xCD02, IDX_CAM_LOGO3},		{0xCD03, IDX_CAM_LOGO4},		{0xCD04, IDX_CAM_LOGO5},		{0xCD05, IDX_CAM_LOGO6},		{0xCD06, IDX_CAM_LOGO7},		{0xCD07, IDX_CAM_LOGO8},			{0xCD08, IDX_CAM_LOGO9},
// 	{0xCD09, IDX_CAM_LOGO10},		{0xCD0A, IDX_CAM_LOGO11},		{0xCD0B, IDX_CAM_LOGO12},		{0xCD0C, IDX_CAM_LOGO13},		{0xCD0D, IDX_CAM_LOGO14},		{0xCD0E, IDX_CAM_LOGO15},		{0xCD0F, IDX_CAM_LOGO16},			{0xCD10, IDX_CAM_LOGO17},
// 	{0xCD11, IDX_CAM_LOGO18},		{0xCD12, IDX_CAM_LOGO19},		{0xCD13, IDX_CAM_LOGO20},		{0xCD14, IDX_CAM_LOGO21},		{0xCD15, IDX_CAM_LOGO22},		{0xCD16, IDX_CAM_LOGO23},		{0xCD17, IDX_CAM_LOGO24},			{0xCD18, IDX_CAM_LOGO25},
// 	{0xCD19, IDX_CAM_LOGO26},		{0xCD1A, IDX_CAM_LOGO27},		{0xCD1B, IDX_CAM_LOGO28},		{0xCD1C, IDX_CAM_LOGO29},		{0xCD1D, IDX_CAM_LOGO30},		{0xCD1E, IDX_CAM_LOGO31},		{0xCD1F, IDX_CAM_LOGO32}
// };
/* Kind of send packet */


/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/* Interface */
/*********************************************************************************************************//**
* @param[in] addr	: don't care
* @retval
*	return : -1
* @brief
*   Null 함수 ,아무것도 하지 않는다.
*************************************************************************************************************/
static uint32 GetfuncNull(uint32 addr)
{
	return -1;
}
/*********************************************************************************************************//**
* @param[in] addr	: don't care
* @param[in] dat	: don't care
* @retval
* @brief
*   Null 함수 ,아무것도 하지 않는다.
*************************************************************************************************************/
static void SetfuncNull(uint32 addr,uint32 dat)
{
	addr = dat;	//
}

/*********************************************************************************************************//**
* @param[in] evt : don't care
* @param[in] param : don't care
* @retval
* @brief
*   Null 함수 ,아무것도 하지	\n
*	VDX 명령어 처리 : 3001 ~ 4800\n
*************************************************************************************************************/
static IFER EventCallNull(IFEVT evt, IFEVT_PARAM *param)
{
	volatile uint08 tmp = 0;
	tmp = 1;
	return IF_ERFPNULL;
}

IFER SendEvent(IFEVT evt, EEP_IDX eepidx, uint32 *key)
{
	IFER er = IF_ERNOPROC;
	IFEVT_PARAM param;

	if(EventCall == OSD_NULL)
	{
		er = IF_ERFPNULL;
	}
	else
	{
		param.eepidx = eepidx;
		param.key = *key;
		er = EventCall(evt, &param);
		*key = param.key;
	}

	return er;
}

/* EEPRom */
int32 UEepCallNull(IFEVT evt, EEP_IDX idx, int32 val)
{
	volatile uint08 tmp = 0;
	tmp = 1;
	return -1;
}

int32 IF_EEPUpdate(IFEVT evt, EEP_IDX idx, int32 val)
{
	int32 ret = -1;

	if(idx < IDX_USER)
	{
		switch(idx)
		{
			/* Header 0x0000 ~ 0x000F */
			case IDX_MEM_STATUS:                      ret = VAL_TUNE(g_OsdData.FLD.MEM_STATUS);              break;
			case IDX_CAM_TYPE:                        ret = VAL_TUNE(g_OsdData.FLD.CAM_TYPE);                break;
			case IDX_CAM_CLASS:                       ret = VAL_TUNE(g_OsdData.FLD.CAM_CLASS);               break;
			case IDX_MEM_VER:                         ret = VAL_TUNE(g_OsdData.FLD.MEM_VER);                 break;
			case IDX_CCD_TYPE:                        ret = VAL_TUNE(g_OsdData.FLD.CCD_TYPE);                break;
			case IDX_CLIENT_OPT:                      ret = VAL_TUNE(g_OsdData.FLD.CLIENT_OPT);              break;
			case IDX_HALL_ADJ:                        ret = VAL_TUNE(g_OsdData.FLD.HALL_ADJ);                break;
			case IDX_LENS_ADJ:                        ret = VAL_TUNE(g_OsdData.FLD.LENS_ADJ);                break;
			case IDX_MASK_ADJ:                        ret = VAL_TUNE(g_OsdData.FLD.MASK_ADJ);                break;
			case IDX_DEFECT_ADJ:                      ret = VAL_TUNE(g_OsdData.FLD.DEFECT_ADJ);              break;
			case IDX_SHADE_ADJ:                       ret = VAL_TUNE(g_OsdData.FLD.SHADE_ADJ);               break;
			case IDX_COLOR_ADJ:                       ret = VAL_TUNE(g_OsdData.FLD.COLOR_ADJ);               break;
			case IDX_COMM_SET:                        ret = VAL_TUNE(g_OsdData.FLD.COMM_SET);                break;
			case IDX_MENU_USE:                        ret = VAL_TUNE(g_OsdData.FLD.MENU_USE);                break;
			case IDX_LENS_INIT_TYPE:                  ret = VAL_TUNE(g_OsdData.FLD.LENS_INIT_TYPE);          break;
			case IDX_HOME_USE:                        ret = VAL_TUNE(g_OsdData.FLD.HOME_USE);                break;
			/* FOCUS 0x0010 ~ 0x0025 */
			case IDX_FOCUS_MODE:                      ret = VAL_TUNE(g_OsdData.FLD.FOCUS_MODE);              break;
			case IDX_AF_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.AF_MODE);                 break;
			case IDX_AF_MOVE_TIME:                    ret = VAL_TUNE(g_OsdData.FLD.AF_MOVE_TIME);            break;
			case IDX_AF_INTERVAL_TIME:                ret = VAL_TUNE(g_OsdData.FLD.AF_INTERVAL_TIME);        break;
			case IDX_FOCUS_DIST:                      ret = VAL_TUNE(g_OsdData.FLD.FOCUS_DIST);              break;
			case IDX_ZOOM_MODE:                       ret = VAL_TUNE(g_OsdData.FLD.ZOOM_MODE);               break;
			case IDX_DZOOM_MODE:                      ret = VAL_TUNE(g_OsdData.FLD.DZOOM_MODE);              break;
			case IDX_ZTRK_MODE:                       ret = VAL_TUNE(g_OsdData.FLD.ZTRK_MODE);               break;
			case IDX_ZOOM_SPEED:                      ret = VAL_TUNE(g_OsdData.FLD.ZOOM_SPEED);              break;
			case IDX_LENS_REFRESH_MODE:               ret = VAL_TUNE(g_OsdData.FLD.LENS_REFRESH_MODE);       break;
			case IDX_LENS_REFRESH_DAYS:               ret = VAL_TUNE(g_OsdData.FLD.LENS_REFRESH_DAYS);       break;
			case IDX_ZSRT_MAG:                        ret = VAL_TUNE(g_OsdData.FLD.ZSRT_MAG);                break;
			case IDX_ZEND_MAG:                        ret = VAL_TUNE(g_OsdData.FLD.ZEND_MAG);                break;
			case IDX_DZOOM_MAG:                       ret = VAL_TUNE(g_OsdData.FLD.DZOOM_MAG);               break;
			case IDX_HOME_MODE:                       ret = VAL_TUNE(g_OsdData.FLD.HOME_MODE);               break;
			case IDX_HOME_TIME:                       ret = VAL_TUNE(g_OsdData.FLD.HOME_TIME);               break;
			case IDX_Z_HOME_POS:                      ret = VAL_TUNE(g_OsdData.FLD.Z_HOME_POS);              break;
			case IDX_F_HOME_POS:                      ret = VAL_TUNE(g_OsdData.FLD.F_HOME_POS);              break;
			case IDX_DZ_HOME_POS:                     ret = VAL_TUNE(g_OsdData.FLD.DZ_HOME_POS);             break;
			/* EXPOSURE 0x0026 ~ 0x002E */
			case IDX_AE_TGT_BRIGHT:                   ret = VAL_TUNE(g_OsdData.FLD.AE_TGT_BRIGHT);           break;
			case IDX_AE_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.AE_MODE);                 break;
			case IDX_AE_AGC_LIMIT:                    ret = VAL_TUNE(g_OsdData.FLD.AE_AGC_LIMIT);            break;
			case IDX_AEM_IRIS_STEP:                   ret = VAL_TUNE(g_OsdData.FLD.AEM_IRIS_STEP);           break;
			case IDX_AEM_SHUT_STEP:                   ret = VAL_TUNE(g_OsdData.FLD.AEM_SHUT_STEP);           break;
			case IDX_AEM_BRIGHT_STEP:                 ret = VAL_TUNE(g_OsdData.FLD.AEM_BRIGHT_STEP);         break;
			case IDX_AEM_GAIN_STEP:                   ret = VAL_TUNE(g_OsdData.FLD.AEM_GAIN_STEP);           break;
			case IDX_AE_DSS_STEP:                     ret = VAL_TUNE(g_OsdData.FLD.AE_DSS_STEP);             break;
			case IDX_AE_FLK_MODE:                     ret = VAL_TUNE(g_OsdData.FLD.AE_FLK_MODE);             break;
			/* WB 0x002F ~ 0x003C */
			case IDX_WB_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.WB_MODE);                 break;
			case IDX_WB_ENV:                          ret = VAL_TUNE(g_OsdData.FLD.WB_ENV);                  break;
			case IDX_WB_RED_GAIN:                     ret = VAL_TUNE(g_OsdData.FLD.WB_RED_GAIN);             break;
			case IDX_WB_BLUE_GAIN:                    ret = VAL_TUNE(g_OsdData.FLD.WB_BLUE_GAIN);            break;
			case IDX_WB_COLOR_TEMP:                   ret = VAL_TUNE(g_OsdData.FLD.WB_COLOR_TEMP);           break;
			case IDX_ATW_SPEED:                       ret = VAL_TUNE(g_OsdData.FLD.ATW_SPEED);               break;
			case IDX_ATW_FRAME:                       ret = VAL_TUNE(g_OsdData.FLD.ATW_FRAME);               break;
			case IDX_ATW_DELAY:                       ret = VAL_TUNE(g_OsdData.FLD.ATW_DELAY);               break;
			case IDX_USER1_RGAIN:                     ret = VAL_TUNE(g_OsdData.FLD.USER1_RGAIN);             break;
			case IDX_USER1_BGAIN:                     ret = VAL_TUNE(g_OsdData.FLD.USER1_BGAIN);             break;
			case IDX_USER2_RGAIN:                     ret = VAL_TUNE(g_OsdData.FLD.USER2_RGAIN);             break;
			case IDX_USER2_BGAIN:                     ret = VAL_TUNE(g_OsdData.FLD.USER2_BGAIN);             break;
			/* D/N 0x003D ~ 0x0043 */
			case IDX_DN_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.DN_MODE);                 break;
			case IDX_DN_ALARM_ON:                     ret = VAL_TUNE(g_OsdData.FLD.DN_ALARM_ON);             break;
			case IDX_DN_CHG_STEP:                     ret = VAL_TUNE(g_OsdData.FLD.DN_CHG_STEP);             break;
			case IDX_DN_CDS_STEP:                     ret = VAL_TUNE(g_OsdData.FLD.DN_CDS_STEP);             break;
			case IDX_DN_CHG_TIME:                     ret = VAL_TUNE(g_OsdData.FLD.DN_CHG_TIME);             break;
			case IDX_DN_MIN:                          ret = VAL_TUNE(g_OsdData.FLD.DN_MIN);                  break;
			case IDX_DN_CDS_CHG_TIME:                 ret = VAL_TUNE(g_OsdData.FLD.DN_CDS_CHG_TIME);         break;
			case IDX_DN_CDS_MIN:                      ret = VAL_TUNE(g_OsdData.FLD.DN_CDS_MIN);              break;
			/* IMAGE 0x0044 ~ 0x0050 */
			case IDX_IMG_BRIGHT:                      ret = VAL_TUNE(g_OsdData.FLD.IMG_BRIGHT);              break;
			case IDX_IMG_CONTRAST:                    ret = VAL_TUNE(g_OsdData.FLD.IMG_CONTRAST);            break;
			case IDX_IMG_SHARPNESS:                   ret = VAL_TUNE(g_OsdData.FLD.IMG_SHARPNESS);           break;
			case IDX_IMG_CHROMA:                      ret = VAL_TUNE(g_OsdData.FLD.IMG_CHROMA);              break;
			case IDX_IMG_HUE:                         ret = VAL_TUNE(g_OsdData.FLD.IMG_HUE);                 break;
			case IDX_IMG_FLIP:                        ret = VAL_TUNE(g_OsdData.FLD.IMG_FLIP);                break;
			case IDX_IMG_FREEZE:                      ret = VAL_TUNE(g_OsdData.FLD.IMG_FREEZE);              break;
			case IDX_IMG_EFFECT:                      ret = VAL_TUNE(g_OsdData.FLD.IMG_EFFECT);              break;
			case IDX_IMG_COLOR:                       ret = VAL_TUNE(g_OsdData.FLD.IMG_COLOR);               break;
			case IDX_IMG_SHADING:                     ret = VAL_TUNE(g_OsdData.FLD.IMG_SHADING);             break;
			case IDX_IMG_DEFECT:                      ret = VAL_TUNE(g_OsdData.FLD.IMG_DEFECT);              break;
			case IDX_IMG_GAMMA_STEP:                  ret = VAL_TUNE(g_OsdData.FLD.IMG_GAMMA_STEP);          break;
			case IDX_IMG_GAM_MODE:                    ret = VAL_TUNE(g_OsdData.FLD.IMG_GAM_MODE);            break;
			case IDX_IMG_RGAIN:                       ret = VAL_TUNE(g_OsdData.FLD.IMG_RGAIN);               break;
			case IDX_IMG_BGAIN:                       ret = VAL_TUNE(g_OsdData.FLD.IMG_BGAIN);               break;
			case IDX_HR_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.HR_MODE);                 break;
			/* BACKLIGHT 0x0051 ~ 0x005F */
			case IDX_BL_MODE:                         ret = VAL_TUNE(g_OsdData.FLD.BL_MODE);                 break;
			case IDX_BLC_MODE:                        ret = VAL_TUNE(g_OsdData.FLD.BLC_MODE);                break;
			case IDX_BLC_DISP:                        ret = VAL_TUNE(g_OsdData.FLD.BLC_DISP);                break;
			case IDX_BLC_LEVEL:                       ret = VAL_TUNE(g_OsdData.FLD.BLC_LEVEL);               break;
			case IDX_BLC_AREA_X_SRT:                  ret = VAL_TUNE(g_OsdData.FLD.BLC_AREA_X_SRT);          break;
			case IDX_BLC_AREA_Y_SRT:                  ret = VAL_TUNE(g_OsdData.FLD.BLC_AREA_Y_SRT);          break;
			case IDX_BLC_AREA_WIDTH:                  ret = VAL_TUNE(g_OsdData.FLD.BLC_AREA_WIDTH);          break;
			case IDX_BLC_AREA_HEIGHT:                 ret = VAL_TUNE(g_OsdData.FLD.BLC_AREA_HEIGHT);         break;
			case IDX_WDR_MODE:                        ret = VAL_TUNE(g_OsdData.FLD.WDR_MODE);                break;
			case IDX_WDR_LEVEL:                       ret = VAL_TUNE(g_OsdData.FLD.WDR_LEVEL);               break;
			case IDX_HLC_MODE:                        ret = VAL_TUNE(g_OsdData.FLD.HLC_MODE);                break;
			case IDX_HLC_MASK_COLOR:                  ret = VAL_TUNE(g_OsdData.FLD.HLC_MASK_COLOR);          break;
			case IDX_HLC_LEVEL:                       ret = VAL_TUNE(g_OsdData.FLD.HLC_LEVEL);               break;
			case IDX_HLC_SCALE:                       ret = VAL_TUNE(g_OsdData.FLD.HLC_SCALE);               break;
			/* DNR 0x0060 ~ 0x0064 */
			case IDX_DNR_MODE:                        ret = VAL_TUNE(g_OsdData.FLD.DNR_MODE);                break;
			case IDX_DNR_GLB_MOT:                     ret = VAL_TUNE(g_OsdData.FLD.DNR_GLB_MOT);             break;
			case IDX_DNR_LEVEL:                       ret = VAL_TUNE(g_OsdData.FLD.DNR_LEVEL);               break;
			case IDX_3DNR_LEVEL:                      ret = VAL_TUNE(g_OsdData.FLD._3DNR_LEVEL);              break;
			case IDX_2DNR_LEVEL:                      ret = VAL_TUNE(g_OsdData.FLD._2DNR_LEVEL);              break;
			/* SPECIAL/MOTION 0x0065 ~ 0x007D */
			case IDX_MD_ON:                           ret = VAL_TUNE(g_OsdData.FLD.MD_ON);                   break;
#if ALL_IDX_USE	// use IF_EEPMotionUpdate
			case IDX_MD1_STATE:                       ret = VAL_TUNE(g_OsdData.FLD.MD1_STATE);               break;
			case IDX_MD1_DISP:                        ret = VAL_TUNE(g_OsdData.FLD.MD1_DISP);                break;
			case IDX_MD1_ALARM:                       ret = VAL_TUNE(g_OsdData.FLD.MD1_ALARM);               break;
			case IDX_MD1_SENS:                        ret = VAL_TUNE(g_OsdData.FLD.MD1_SENS);                break;
			case IDX_MD1_X_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD1_X_SRT);               break;
			case IDX_MD1_Y_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD1_Y_SRT);               break;
			case IDX_MD1_WIDTH:                       ret = VAL_TUNE(g_OsdData.FLD.MD1_WIDTH);               break;
			case IDX_MD1_HEIGHT:                      ret = VAL_TUNE(g_OsdData.FLD.MD1_HEIGHT);              break;
			case IDX_MD2_STATE:                       ret = VAL_TUNE(g_OsdData.FLD.MD2_STATE);               break;
			case IDX_MD2_DISP:                        ret = VAL_TUNE(g_OsdData.FLD.MD2_DISP);                break;
			case IDX_MD2_ALARM:                       ret = VAL_TUNE(g_OsdData.FLD.MD2_ALARM);               break;
			case IDX_MD2_SENS:                        ret = VAL_TUNE(g_OsdData.FLD.MD2_SENS);                break;
			case IDX_MD2_X_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD2_X_SRT);               break;
			case IDX_MD2_Y_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD2_Y_SRT);               break;
			case IDX_MD2_WIDTH:                       ret = VAL_TUNE(g_OsdData.FLD.MD2_WIDTH);               break;
			case IDX_MD2_HEIGHT:                      ret = VAL_TUNE(g_OsdData.FLD.MD2_HEIGHT);              break;
			case IDX_MD3_STATE:                       ret = VAL_TUNE(g_OsdData.FLD.MD3_STATE);               break;
			case IDX_MD3_DISP:                        ret = VAL_TUNE(g_OsdData.FLD.MD3_DISP);                break;
			case IDX_MD3_ALARM:                       ret = VAL_TUNE(g_OsdData.FLD.MD3_ALARM);               break;
			case IDX_MD3_SENS:                        ret = VAL_TUNE(g_OsdData.FLD.MD3_SENS);                break;
			case IDX_MD3_X_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD3_X_SRT);               break;
			case IDX_MD3_Y_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD3_Y_SRT);               break;
			case IDX_MD3_WIDTH:                       ret = VAL_TUNE(g_OsdData.FLD.MD3_WIDTH);               break;
			case IDX_MD3_HEIGHT:                      ret = VAL_TUNE(g_OsdData.FLD.MD3_HEIGHT);              break;
			case IDX_MD4_STATE:                       ret = VAL_TUNE(g_OsdData.FLD.MD4_STATE);               break;
			case IDX_MD4_DISP:                        ret = VAL_TUNE(g_OsdData.FLD.MD4_DISP);                break;
			case IDX_MD4_ALARM:                       ret = VAL_TUNE(g_OsdData.FLD.MD4_ALARM);               break;
			case IDX_MD4_SENS:                        ret = VAL_TUNE(g_OsdData.FLD.MD4_SENS);                break;
			case IDX_MD4_X_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD4_X_SRT);               break;
			case IDX_MD4_Y_SRT:                       ret = VAL_TUNE(g_OsdData.FLD.MD4_Y_SRT);               break;
			case IDX_MD4_WIDTH:                       ret = VAL_TUNE(g_OsdData.FLD.MD4_WIDTH);               break;
			case IDX_MD4_HEIGHT:                      ret = VAL_TUNE(g_OsdData.FLD.MD4_HEIGHT);              break;
#endif
			/* SPECIAL/PRIVACY MASK 0x007E ~ 0x00D6 */
			case IDX_MASK_ON:                         ret = VAL_TUNE(g_OsdData.FLD.MASK_ON);                 break;
			case IDX_MASK_I:                          ret = VAL_TUNE(g_OsdData.FLD.MASK_I);                  break;
#if ALL_IDX_USE	// use IF_EEPPrivacyUpdate
			case IDX_MASK1_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_STATE);             break;
			case IDX_MASK1_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_TRANS);             break;
			case IDX_MASK1_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_COLOR);             break;
			case IDX_MASK1_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK1_MOSAIC);            break;
			case IDX_MASK1_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_X_SRT);             break;
			case IDX_MASK1_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_Y_SRT);             break;
			case IDX_MASK1_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK1_WIDTH);             break;
			case IDX_MASK1_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK1_HEIGHT);            break;
			case IDX_MASK1_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK1_PAN);               break;
			case IDX_MASK1_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK1_TILT);              break;
			case IDX_MASK1_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK1_ZOOM);              break;
			case IDX_MASK2_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_STATE);             break;
			case IDX_MASK2_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_TRANS);             break;
			case IDX_MASK2_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_COLOR);             break;
			case IDX_MASK2_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK2_MOSAIC);            break;
			case IDX_MASK2_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_X_SRT);             break;
			case IDX_MASK2_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_Y_SRT);             break;
			case IDX_MASK2_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK2_WIDTH);             break;
			case IDX_MASK2_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK2_HEIGHT);            break;
			case IDX_MASK2_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK2_PAN);               break;
			case IDX_MASK2_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK2_TILT);              break;
			case IDX_MASK2_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK2_ZOOM);              break;
			case IDX_MASK3_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_STATE);             break;
			case IDX_MASK3_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_TRANS);             break;
			case IDX_MASK3_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_COLOR);             break;
			case IDX_MASK3_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK3_MOSAIC);            break;
			case IDX_MASK3_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_X_SRT);             break;
			case IDX_MASK3_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_Y_SRT);             break;
			case IDX_MASK3_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK3_WIDTH);             break;
			case IDX_MASK3_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK3_HEIGHT);            break;
			case IDX_MASK3_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK3_PAN);               break;
			case IDX_MASK3_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK3_TILT);              break;
			case IDX_MASK3_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK3_ZOOM);              break;
			case IDX_MASK4_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_STATE);             break;
			case IDX_MASK4_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_TRANS);             break;
			case IDX_MASK4_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_COLOR);             break;
			case IDX_MASK4_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK4_MOSAIC);            break;
			case IDX_MASK4_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_X_SRT);             break;
			case IDX_MASK4_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_Y_SRT);             break;
			case IDX_MASK4_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK4_WIDTH);             break;
			case IDX_MASK4_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK4_HEIGHT);            break;
			case IDX_MASK4_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK4_PAN);               break;
			case IDX_MASK4_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK4_TILT);              break;
			case IDX_MASK4_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK4_ZOOM);              break;
			case IDX_MASK5_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_STATE);             break;
			case IDX_MASK5_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_TRANS);             break;
			case IDX_MASK5_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_COLOR);             break;
			case IDX_MASK5_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK5_MOSAIC);            break;
			case IDX_MASK5_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_X_SRT);             break;
			case IDX_MASK5_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_Y_SRT);             break;
			case IDX_MASK5_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK5_WIDTH);             break;
			case IDX_MASK5_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK5_HEIGHT);            break;
			case IDX_MASK5_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK5_PAN);               break;
			case IDX_MASK5_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK5_TILT);              break;
			case IDX_MASK5_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK5_ZOOM);              break;
			case IDX_MASK6_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_STATE);             break;
			case IDX_MASK6_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_TRANS);             break;
			case IDX_MASK6_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_COLOR);             break;
			case IDX_MASK6_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK6_MOSAIC);            break;
			case IDX_MASK6_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_X_SRT);             break;
			case IDX_MASK6_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_Y_SRT);             break;
			case IDX_MASK6_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK6_WIDTH);             break;
			case IDX_MASK6_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK6_HEIGHT);            break;
			case IDX_MASK6_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK6_PAN);               break;
			case IDX_MASK6_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK6_TILT);              break;
			case IDX_MASK6_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK6_ZOOM);              break;
			case IDX_MASK7_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_STATE);             break;
			case IDX_MASK7_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_TRANS);             break;
			case IDX_MASK7_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_COLOR);             break;
			case IDX_MASK7_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK7_MOSAIC);            break;
			case IDX_MASK7_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_X_SRT);             break;
			case IDX_MASK7_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_Y_SRT);             break;
			case IDX_MASK7_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK7_WIDTH);             break;
			case IDX_MASK7_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK7_HEIGHT);            break;
			case IDX_MASK7_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK7_PAN);               break;
			case IDX_MASK7_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK7_TILT);              break;
			case IDX_MASK7_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK7_ZOOM);              break;
			case IDX_MASK8_STATE:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_STATE);             break;
			case IDX_MASK8_TRANS:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_TRANS);             break;
			case IDX_MASK8_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_COLOR);             break;
			case IDX_MASK8_MOSAIC:                    ret = VAL_TUNE(g_OsdData.FLD.MASK8_MOSAIC);            break;
			case IDX_MASK8_X_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_X_SRT);             break;
			case IDX_MASK8_Y_SRT:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_Y_SRT);             break;
			case IDX_MASK8_WIDTH:                     ret = VAL_TUNE(g_OsdData.FLD.MASK8_WIDTH);             break;
			case IDX_MASK8_HEIGHT:                    ret = VAL_TUNE(g_OsdData.FLD.MASK8_HEIGHT);            break;
			case IDX_MASK8_PAN:                       ret = VAL_TUNE(g_OsdData.FLD.MASK8_PAN);               break;
			case IDX_MASK8_TILT:                      ret = VAL_TUNE(g_OsdData.FLD.MASK8_TILT);              break;
			case IDX_MASK8_ZOOM:                      ret = VAL_TUNE(g_OsdData.FLD.MASK8_ZOOM);              break;
#endif
			/* SPECIAL 0x00D7 ~ 0x00DB */
			case IDX_DEFOG_ON:                        ret = VAL_TUNE(g_OsdData.FLD.DEFOG_ON);                break;
			case IDX_DIS_ON:                          ret = VAL_TUNE(g_OsdData.FLD.DIS_ON);                  break;
			case IDX_SYNC:                            ret = VAL_TUNE(g_OsdData.FLD.SYNC);                    break;
			case IDX_SHADE_ON:                        ret = VAL_TUNE(g_OsdData.FLD.SHADE_ON);                break;
			case IDX_SYNC_PHASE:                      ret = VAL_TUNE(g_OsdData.FLD.SYNC_PHASE);              break;
			/* SYSTEM 0x00DC ~ 0x00FF */
			case IDX_CAM_ID:                          ret = VAL_TUNE(g_OsdData.FLD.CAM_ID);                  break;
			case IDX_CAMID_X_POS:                     ret = VAL_TUNE(g_OsdData.FLD.CAMID_X_POS);             break;
			case IDX_CAMID_Y_POS:                     ret = VAL_TUNE(g_OsdData.FLD.CAMID_Y_POS);             break;
			case IDX_BAUDRATE:                        ret = VAL_TUNE(g_OsdData.FLD.BAUDRATE);                break;
			case IDX_PROTOCOL:                        ret = VAL_TUNE(g_OsdData.FLD.PROTOCOL);                break;
			case IDX_OSD_LANGUAGE:                    ret = VAL_TUNE(g_OsdData.FLD.OSD_LANGUAGE);            break;
			case IDX_ID_ON:                           ret = VAL_TUNE(g_OsdData.FLD.ID_ON);                   break;
			case IDX_TITLE_ON:                        ret = VAL_TUNE(g_OsdData.FLD.TITLE_ON);                break;
			case IDX_ZMAG_ON:                         ret = VAL_TUNE(g_OsdData.FLD.ZMAG_ON);                 break;
			case IDX_FUNC_ON:                         ret = VAL_TUNE(g_OsdData.FLD.FUNC_ON);                 break;
			case IDX_ALL_ON:                          ret = VAL_TUNE(g_OsdData.FLD.ALL_ON);                  break;
			case IDX_TITLE_BLK:                       ret = VAL_TUNE(g_OsdData.FLD.TITLE_BLK);               break;
			case IDX_TITLE_COLOR:                     ret = VAL_TUNE(g_OsdData.FLD.TITLE_COLOR);             break;
			case IDX_TITLE_X_POS:                     ret = VAL_TUNE(g_OsdData.FLD.TITLE_X_POS);             break;
			case IDX_TITLE_Y_POS:                     ret = VAL_TUNE(g_OsdData.FLD.TITLE_Y_POS);             break;
			case IDX_CAM_TITLE_CH1:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH1);           break;
			case IDX_CAM_TITLE_CH2:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH2);           break;
			case IDX_CAM_TITLE_CH3:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH3);           break;
			case IDX_CAM_TITLE_CH4:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH4);           break;
			case IDX_CAM_TITLE_CH5:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH5);           break;
			case IDX_CAM_TITLE_CH6:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH6);           break;
			case IDX_CAM_TITLE_CH7:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH7);           break;
			case IDX_CAM_TITLE_CH8:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH8);           break;
			case IDX_CAM_TITLE_CH9:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH9);           break;
			case IDX_CAM_TITLE_CH10:                   ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH1);           break;
			case IDX_CAM_TITLE_CH11:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH11);          break;
			case IDX_CAM_TITLE_CH12:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH12);          break;
			case IDX_CAM_TITLE_CH13:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH13);          break;
			case IDX_CAM_TITLE_CH14:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH14);          break;
			case IDX_CAM_TITLE_CH15:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH15);          break;
			case IDX_CAM_TITLE_CH16:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH16);          break;
			case IDX_CAM_TITLE_CH17:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH17);          break;
			case IDX_CAM_TITLE_CH18:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH18);          break;
			case IDX_CAM_TITLE_CH19:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH19);          break;
			case IDX_CAM_TITLE_CH20:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH20);          break;
			case IDX_CAM_TITLE_CH21:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH21);          break;
			case IDX_CAM_TITLE_CH22:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH22);          break;
			case IDX_CAM_TITLE_CH23:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH23);          break;
			case IDX_CAM_TITLE_CH24:                  ret = VAL_TUNE(g_OsdData.FLD.CAM_TITLE_CH24);          break;
			case IDX_VOUT_FORMAT:                     ret = VAL_TUNE(g_OsdData.FLD.VOUT_FORMAT);             break;
			case IDX_LVDS_D:                          ret = VAL_TUNE(g_OsdData.FLD.LVDS_D);                  break;
			case IDX_DOUT_FULL:                       ret = VAL_TUNE(g_OsdData.FLD.DOUT_FULL);               break;
			case IDX_DOUT_ON:                         ret = VAL_TUNE(g_OsdData.FLD.DOUT_ON);                 break;
			case IDX_CVBS_ON:                         ret = VAL_TUNE(g_OsdData.FLD.CVBS_ON);                 break;

			/* HALL 0x0500 ~ 0x050F */
			case IDX_TGT_HALL_MAX:                    ret = VAL_TUNE(g_CamData.FLD.TGT_HALL_MAX);            break;
			case IDX_TGT_HALL_MIN:                    ret = VAL_TUNE(g_CamData.FLD.TGT_HALL_MIN);            break;
			case IDX_HO_ZERO:                         ret = VAL_TUNE(g_CamData.FLD.HO_ZERO);                 break;
			case IDX_HG_ZERO:                         ret = VAL_TUNE(g_CamData.FLD.HG_ZERO);                 break;
			case IDX_HB_ZERO:                         ret = VAL_TUNE(g_CamData.FLD.HB_ZERO);                 break;
			case IDX_HADJ_DIFF_OFF:                   ret = VAL_TUNE(g_CamData.FLD.HADJ_DIFF_OFF);           break;
			case IDX_HADJ_MEAN_OFF:                   ret = VAL_TUNE(g_CamData.FLD.HADJ_MEAN_OFF);           break;
			case IDX_HADJ_MAX:                        ret = VAL_TUNE(g_CamData.FLD.HADJ_MAX);                break;
			case IDX_HADJ_MIN:                        ret = VAL_TUNE(g_CamData.FLD.HADJ_MIN);                break;
			case IDX_HADJ_HG:                         ret = VAL_TUNE(g_CamData.FLD.HADJ_HG);                 break;
			case IDX_HADJ_HO:                         ret = VAL_TUNE(g_CamData.FLD.HADJ_HO);                 break;
			case IDX_HADJ_HB:                         ret = VAL_TUNE(g_CamData.FLD.HADJ_HB);                 break;
			/* LENS OFFSET 0x0510 ~ 0x051D */
			case IDX_OADJ_ZADD:                       ret = VAL_TUNE(g_CamData.FLD.OADJ_ZADD);               break;
			case IDX_OADJ_FADD:                       ret = VAL_TUNE(g_CamData.FLD.OADJ_FADD);               break;
			case IDX_OADJ_ZOFF:                       ret = VAL_TUNE(g_CamData.FLD.OADJ_ZOFF);               break;
			case IDX_OADJ_FOFF:                       ret = VAL_TUNE(g_CamData.FLD.OADJ_FOFF);               break;
			case IDX_OADJ_PD_SRT:                     ret = VAL_TUNE(g_CamData.FLD.OADJ_PD_SRT);             break;
			case IDX_OADJ_ZD_SRT:                     ret = VAL_TUNE(g_CamData.FLD.OADJ_ZD_SRT);             break;
			case IDX_OADJ_FD_SRT:                     ret = VAL_TUNE(g_CamData.FLD.OADJ_FD_SRT);             break;
			case IDX_OADJ_P2DEC_R:                    ret = VAL_TUNE(g_CamData.FLD.OADJ_P2DEC_R);            break;
			case IDX_OADJ_T2DEC_R:                    ret = VAL_TUNE(g_CamData.FLD.OADJ_T2DEC_R);            break;
			case IDX_OADJ_PD:                         ret = VAL_TUNE(g_CamData.FLD.OADJ_PD);                 break;
			case IDX_OADJ_ZD:                         ret = VAL_TUNE(g_CamData.FLD.OADJ_ZD);                 break;
			case IDX_OADJ_FD:                         ret = VAL_TUNE(g_CamData.FLD.OADJ_FD);                 break;
			case IDX_OADJ_WEND_S:                     ret = VAL_TUNE(g_CamData.FLD.OADJ_WEND_S);             break;
			case IDX_OADJ_TEND_S:                     ret = VAL_TUNE(g_CamData.FLD.OADJ_TEND_S);             break;
			/* PRIVACY MASK 0x051E ~ 0x0512 */
			case IDX_MADJ_3D_PAN_NT:                  ret = VAL_TUNE(g_CamData.FLD.MADJ_3D_PAN_NT);          break;
			case IDX_MADJ_3D_TILT_NT:                 ret = VAL_TUNE(g_CamData.FLD.MADJ_3D_TILT_NT);         break;
			case IDX_MADJ_3D_PAN_PA:                  ret = VAL_TUNE(g_CamData.FLD.MADJ_3D_PAN_PA);          break;
			case IDX_MADJ_3D_TILT_PA:                 ret = VAL_TUNE(g_CamData.FLD.MADJ_3D_TILT_PA);         break;
			/* DEFECT 0x0522 ~ 0x0525 */
			case IDX_DADJ_THRESHOLD:                  ret = VAL_TUNE(g_CamData.FLD.DADJ_THRESHOLD);          break;
			/* SHADING 0x0526 ~ 0x0529 */
			case IDX_SADJ_GAIN:                       ret = VAL_TUNE(g_CamData.FLD.SADJ_GAIN);               break;
			case IDX_SADJ_OFFSET:                     ret = VAL_TUNE(g_CamData.FLD.SADJ_OFFSET);             break;
			/* COLOR 0x052A ~ 0x053F */
			/* LOGO 0x0540 ~ 0x055F */
			case IDX_LOGO_CH1:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH1);                break;
			case IDX_LOGO_CH2:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH2);                break;
			case IDX_LOGO_CH3:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH3);                break;
			case IDX_LOGO_CH4:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH4);                break;
			case IDX_LOGO_CH5:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH5);                break;
			case IDX_LOGO_CH6:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH6);                break;
			case IDX_LOGO_CH7:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH7);                break;
			case IDX_LOGO_CH8:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH8);                break;
			case IDX_LOGO_CH9:                        ret = VAL_TUNE(g_CamData.FLD.LOGO_CH9);                break;
			case IDX_LOGO_CH10:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH10);               break;
			case IDX_LOGO_CH11:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH11);               break;
			case IDX_LOGO_CH12:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH12);               break;
			case IDX_LOGO_CH13:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH13);               break;
			case IDX_LOGO_CH14:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH14);               break;
			case IDX_LOGO_CH15:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH15);               break;
			case IDX_LOGO_CH16:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH16);               break;
			case IDX_LOGO_CH17:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH17);               break;
			case IDX_LOGO_CH18:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH18);               break;
			case IDX_LOGO_CH19:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH19);               break;
			case IDX_LOGO_CH20:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH20);               break;
			case IDX_LOGO_CH21:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH21);               break;
			case IDX_LOGO_CH22:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH22);               break;
			case IDX_LOGO_CH23:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH23);               break;
			case IDX_LOGO_CH24:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH24);               break;
			case IDX_LOGO_CH25:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH25);               break;
			case IDX_LOGO_CH26:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH26);               break;
			case IDX_LOGO_CH27:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH27);               break;
			case IDX_LOGO_CH28:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH28);               break;
			case IDX_LOGO_CH29:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH29);               break;
			case IDX_LOGO_CH30:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH30);               break;
			case IDX_LOGO_CH31:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH31);               break;
			case IDX_LOGO_CH32:                       ret = VAL_TUNE(g_CamData.FLD.LOGO_CH32);               break;
			/* ADKEY 0x0560 ~ 0x056F */
			case IDX_ADKEY00:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY00);                 break;
			case IDX_ADKEY01:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY01);                 break;
			case IDX_ADKEY02:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY02);                 break;
			case IDX_ADKEY03:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY03);                 break;
			case IDX_ADKEY04:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY04);                 break;
			case IDX_ADKEY05:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY05);                 break;
			case IDX_ADKEY06:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY06);                 break;
			case IDX_ADKEY07:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY07);                 break;
			case IDX_ADKEY10:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY10);                 break;
			case IDX_ADKEY11:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY11);                 break;
			case IDX_ADKEY12:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY12);                 break;
			case IDX_ADKEY13:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY13);                 break;
			case IDX_ADKEY14:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY14);                 break;
			case IDX_ADKEY15:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY15);                 break;
			case IDX_ADKEY16:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY16);                 break;
			case IDX_ADKEY17:                         ret = VAL_TUNE(g_CamData.FLD.ADKEY17);                 break;
		}
	}
	else
	{
		ret = UEepUpdateCall(evt, idx, val);
	}

	return ret;
}

int32 IF_EEPViscaUpdate(IFEVT evt, EEP_IDX idx, int32 val)
{
	int32 ret = -1;

	if(idx < IDX_USER)
	{
		switch(idx)
		{
			case VDX_PWR_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.PWR_ON);                break;
			case VDX_ZOOM_POS:                 ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS);              break;
			case VDX_DZOOM_ON:                 ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON);              break;
			case VDX_DZOOM_MODE:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_MODE);            break;
			case VDX_DZOOM_POS:                ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_POS);             break;
			case VDX_FOCUS_POS:                ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS);             break;
			case VDX_F_MODE:                   ret = VAL_TUNE(g_ViscaData.FLD.F_MODE);                break;
			case VDX_NEAR_LIMIT:               ret = VAL_TUNE(g_ViscaData.FLD.NEAR_LIMIT);            break;
			case VDX_AF_SENS:                  ret = VAL_TUNE(g_ViscaData.FLD.AF_SENS);               break;
			case VDX_AF_MODE:                  ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE);               break;
			case VDX_AF_MOVE_TIME:             ret = VAL_TUNE(g_ViscaData.FLD.AF_MOVE_TIME);          break;
			case VDX_AF_INTERVAL_TIME:         ret = VAL_TUNE(g_ViscaData.FLD.AF_INTERVAL_TIME);      break;
			case VDX_IR_COR:                   ret = VAL_TUNE(g_ViscaData.FLD.IR_COR);                break;
			case VDX_WB_MODE:                  ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE);               break;
			case VDX_PUSH_WB_RGAIN:            ret = VAL_TUNE(g_ViscaData.FLD.PUSH_WB_RGAIN);         break;
			case VDX_PUSH_WB_BGAIN:            ret = VAL_TUNE(g_ViscaData.FLD.PUSH_WB_BGAIN);         break;
			case VDX_R_GAIN:                   ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN);                break;
			case VDX_B_GAIN:                   ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN);                break;
			case VDX_AE_MODE:                  ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE);               break;
			case VDX_ASS_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON);                break;
			case VDX_SHUTTER_STEP:             ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP);          break;
			case VDX_IRIS_STEP:                ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP);             break;
			case VDX_GAIN_STEP:				   val = val & 0xf;
											   ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP)&0xf;		  break;
			case VDX_BRIGHT_STEP:              ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP);           break;
			case VDX_COMP_ON:                  ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON);               break;
			case VDX_EXP_COMP_VAL:             ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL);          break;
			case VDX_BLC_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON);                break;
			case VDX_SPOT_AE_ON:               ret = VAL_TUNE(g_ViscaData.FLD.SPOT_AE_ON);            break;
			case VDX_SPOT_AE_X_POS:            ret = VAL_TUNE(g_ViscaData.FLD.SPOT_AE_X_POS);         break;
			case VDX_SPOT_AE_Y_POS:            ret = VAL_TUNE(g_ViscaData.FLD.SPOT_AE_Y_POS);         break;
			case VDX_AE_RESPONSE:              ret = VAL_TUNE(g_ViscaData.FLD.AE_RESPONSE);           break;
			case VDX_WD_MODE:                  ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE);               break;
			case VDX_WD_BRT_L:                 ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L);              break;
			case VDX_WD_BRT_COMP:              ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP);           break;
			case VDX_WD_COMP_L:                ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L);             break;
			case VDX_DEFOG_ON:                 ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON);              break;
			case VDX_APER_GAIN:                ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN);             break;
			case VDX_HR_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.HR_ON);                 break;
			case VDX_NR_SET:                   ret = VAL_TUNE(g_ViscaData.FLD.NR_SET);                break;
			case VDX_GAM_SET:                  ret = VAL_TUNE(g_ViscaData.FLD.GAM_SET);               break;
			case VDX_HIGH_SENS_ON:             ret = VAL_TUNE(g_ViscaData.FLD.HIGH_SENS_ON);          break;
			case VDX_LR_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.LR_ON);                 break;
			case VDX_FREEZE_ON:                ret = VAL_TUNE(g_ViscaData.FLD.FREEZE_ON);             break;
			case VDX_P_EFFECT:                 ret = VAL_TUNE(g_ViscaData.FLD.P_EFFECT);              break;
			case VDX_FLIP_ON:                  ret = VAL_TUNE(g_ViscaData.FLD.FLIP_ON);               break;
			case VDX_ICR_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON);                break;
			case VDX_AICR_ON:                  ret = VAL_TUNE(g_ViscaData.FLD.AICR_ON);               break;
			case VDX_AICR_THRS_L:              ret = VAL_TUNE(g_ViscaData.FLD.AICR_THRS_L);           break;
			case VDX_AICR_ALARM_ON:            ret = VAL_TUNE(g_ViscaData.FLD.AICR_ALARM_ON);         break;
			case VDX_DISP_ON:                  ret = VAL_TUNE(g_ViscaData.FLD.DISP_ON);               break;
#if ALL_IDX_USE	// use IF_EEPViscaTitleUpdate
			case VDX_TITLE_H_POS0:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS0);          break;
			case VDX_TITLE_ON0:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON0);             break;
			case VDX_TITLE_LINE0:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0);           break;
			case VDX_TITLE_BLINK0:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK0);          break;
			case VDX_TITLE_COLOR0:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR0);          break;
			case VDX_TITLE_LINE0_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH1);       break;
			case VDX_TITLE_LINE0_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH2);       break;
			case VDX_TITLE_LINE0_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH3);       break;
			case VDX_TITLE_LINE0_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH4);       break;
			case VDX_TITLE_LINE0_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH5);       break;
			case VDX_TITLE_LINE0_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH6);       break;
			case VDX_TITLE_LINE0_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH7);       break;
			case VDX_TITLE_LINE0_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH8);       break;
			case VDX_TITLE_LINE0_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH9);       break;
			case VDX_TITLE_LINE0_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH10);      break;
			case VDX_TITLE_LINE0_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH11);      break;
			case VDX_TITLE_LINE0_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH12);      break;
			case VDX_TITLE_LINE0_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH13);      break;
			case VDX_TITLE_LINE0_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH14);      break;
			case VDX_TITLE_LINE0_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH15);      break;
			case VDX_TITLE_LINE0_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH16);      break;
			case VDX_TITLE_LINE0_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH17);      break;
			case VDX_TITLE_LINE0_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH18);      break;
			case VDX_TITLE_LINE0_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH19);      break;
			case VDX_TITLE_LINE0_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE0_CH20);      break;
			case VDX_TITLE_H_POS1:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS1);          break;
			case VDX_TITLE_ON1:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON1);             break;
			case VDX_TITLE_LINE1:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1);           break;
			case VDX_TITLE_BLINK1:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK1);          break;
			case VDX_TITLE_COLOR1:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR1);          break;
			case VDX_TITLE_LINE1_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH1);       break;
			case VDX_TITLE_LINE1_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH2);       break;
			case VDX_TITLE_LINE1_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH3);       break;
			case VDX_TITLE_LINE1_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH4);       break;
			case VDX_TITLE_LINE1_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH5);       break;
			case VDX_TITLE_LINE1_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH6);       break;
			case VDX_TITLE_LINE1_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH7);       break;
			case VDX_TITLE_LINE1_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH8);       break;
			case VDX_TITLE_LINE1_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH9);       break;
			case VDX_TITLE_LINE1_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH10);      break;
			case VDX_TITLE_LINE1_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH11);      break;
			case VDX_TITLE_LINE1_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH12);      break;
			case VDX_TITLE_LINE1_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH13);      break;
			case VDX_TITLE_LINE1_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH14);      break;
			case VDX_TITLE_LINE1_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH15);      break;
			case VDX_TITLE_LINE1_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH16);      break;
			case VDX_TITLE_LINE1_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH17);      break;
			case VDX_TITLE_LINE1_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH18);      break;
			case VDX_TITLE_LINE1_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH19);      break;
			case VDX_TITLE_LINE1_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE1_CH20);      break;
			case VDX_TITLE_H_POS2:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS2);          break;
			case VDX_TITLE_ON2:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON2);             break;
			case VDX_TITLE_LINE2:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2);           break;
			case VDX_TITLE_BLINK2:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK2);          break;
			case VDX_TITLE_COLOR2:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR2);          break;
			case VDX_TITLE_LINE2_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH1);       break;
			case VDX_TITLE_LINE2_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH2);       break;
			case VDX_TITLE_LINE2_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH3);       break;
			case VDX_TITLE_LINE2_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH4);       break;
			case VDX_TITLE_LINE2_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH5);       break;
			case VDX_TITLE_LINE2_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH6);       break;
			case VDX_TITLE_LINE2_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH7);       break;
			case VDX_TITLE_LINE2_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH8);       break;
			case VDX_TITLE_LINE2_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH9);       break;
			case VDX_TITLE_LINE2_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH10);      break;
			case VDX_TITLE_LINE2_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH11);      break;
			case VDX_TITLE_LINE2_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH12);      break;
			case VDX_TITLE_LINE2_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH13);      break;
			case VDX_TITLE_LINE2_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH14);      break;
			case VDX_TITLE_LINE2_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH15);      break;
			case VDX_TITLE_LINE2_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH16);      break;
			case VDX_TITLE_LINE2_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH17);      break;
			case VDX_TITLE_LINE2_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH18);      break;
			case VDX_TITLE_LINE2_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH19);      break;
			case VDX_TITLE_LINE2_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE2_CH20);      break;
			case VDX_TITLE_H_POS3:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS3);          break;
			case VDX_TITLE_ON3:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON3);             break;
			case VDX_TITLE_LINE3:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3);           break;
			case VDX_TITLE_BLINK3:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK3);          break;
			case VDX_TITLE_COLOR3:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR3);          break;
			case VDX_TITLE_LINE3_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH1);       break;
			case VDX_TITLE_LINE3_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH2);       break;
			case VDX_TITLE_LINE3_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH3);       break;
			case VDX_TITLE_LINE3_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH4);       break;
			case VDX_TITLE_LINE3_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH5);       break;
			case VDX_TITLE_LINE3_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH6);       break;
			case VDX_TITLE_LINE3_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH7);       break;
			case VDX_TITLE_LINE3_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH8);       break;
			case VDX_TITLE_LINE3_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH9);       break;
			case VDX_TITLE_LINE3_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH10);      break;
			case VDX_TITLE_LINE3_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH11);      break;
			case VDX_TITLE_LINE3_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH12);      break;
			case VDX_TITLE_LINE3_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH13);      break;
			case VDX_TITLE_LINE3_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH14);      break;
			case VDX_TITLE_LINE3_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH15);      break;
			case VDX_TITLE_LINE3_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH16);      break;
			case VDX_TITLE_LINE3_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH17);      break;
			case VDX_TITLE_LINE3_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH18);      break;
			case VDX_TITLE_LINE3_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH19);      break;
			case VDX_TITLE_LINE3_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE3_CH20);      break;
			case VDX_TITLE_H_POS4:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS4);          break;
			case VDX_TITLE_ON4:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON4);             break;
			case VDX_TITLE_LINE4:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4);           break;
			case VDX_TITLE_BLINK4:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK4);          break;
			case VDX_TITLE_COLOR4:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR4);          break;
			case VDX_TITLE_LINE4_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH1);       break;
			case VDX_TITLE_LINE4_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH2);       break;
			case VDX_TITLE_LINE4_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH3);       break;
			case VDX_TITLE_LINE4_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH4);       break;
			case VDX_TITLE_LINE4_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH5);       break;
			case VDX_TITLE_LINE4_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH6);       break;
			case VDX_TITLE_LINE4_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH7);       break;
			case VDX_TITLE_LINE4_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH8);       break;
			case VDX_TITLE_LINE4_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH9);       break;
			case VDX_TITLE_LINE4_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH10);      break;
			case VDX_TITLE_LINE4_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH11);      break;
			case VDX_TITLE_LINE4_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH12);      break;
			case VDX_TITLE_LINE4_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH13);      break;
			case VDX_TITLE_LINE4_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH14);      break;
			case VDX_TITLE_LINE4_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH15);      break;
			case VDX_TITLE_LINE4_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH16);      break;
			case VDX_TITLE_LINE4_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH17);      break;
			case VDX_TITLE_LINE4_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH18);      break;
			case VDX_TITLE_LINE4_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH19);      break;
			case VDX_TITLE_LINE4_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE4_CH20);      break;
			case VDX_TITLE_H_POS5:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS5);          break;
			case VDX_TITLE_ON5:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON5);             break;
			case VDX_TITLE_LINE5:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5);           break;
			case VDX_TITLE_BLINK5:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK5);          break;
			case VDX_TITLE_COLOR5:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR5);          break;
			case VDX_TITLE_LINE5_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH1);       break;
			case VDX_TITLE_LINE5_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH2);       break;
			case VDX_TITLE_LINE5_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH3);       break;
			case VDX_TITLE_LINE5_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH4);       break;
			case VDX_TITLE_LINE5_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH5);       break;
			case VDX_TITLE_LINE5_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH6);       break;
			case VDX_TITLE_LINE5_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH7);       break;
			case VDX_TITLE_LINE5_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH8);       break;
			case VDX_TITLE_LINE5_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH9);       break;
			case VDX_TITLE_LINE5_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH10);      break;
			case VDX_TITLE_LINE5_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH11);      break;
			case VDX_TITLE_LINE5_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH12);      break;
			case VDX_TITLE_LINE5_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH13);      break;
			case VDX_TITLE_LINE5_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH14);      break;
			case VDX_TITLE_LINE5_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH15);      break;
			case VDX_TITLE_LINE5_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH16);      break;
			case VDX_TITLE_LINE5_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH17);      break;
			case VDX_TITLE_LINE5_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH18);      break;
			case VDX_TITLE_LINE5_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH19);      break;
			case VDX_TITLE_LINE5_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE5_CH20);      break;
			case VDX_TITLE_H_POS6:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS6);          break;
			case VDX_TITLE_ON6:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON6);             break;
			case VDX_TITLE_LINE6:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6);           break;
			case VDX_TITLE_BLINK6:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK6);          break;
			case VDX_TITLE_COLOR6:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR6);          break;
			case VDX_TITLE_LINE6_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH1);       break;
			case VDX_TITLE_LINE6_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH2);       break;
			case VDX_TITLE_LINE6_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH3);       break;
			case VDX_TITLE_LINE6_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH4);       break;
			case VDX_TITLE_LINE6_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH5);       break;
			case VDX_TITLE_LINE6_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH6);       break;
			case VDX_TITLE_LINE6_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH7);       break;
			case VDX_TITLE_LINE6_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH8);       break;
			case VDX_TITLE_LINE6_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH9);       break;
			case VDX_TITLE_LINE6_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH10);      break;
			case VDX_TITLE_LINE6_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH11);      break;
			case VDX_TITLE_LINE6_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH12);      break;
			case VDX_TITLE_LINE6_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH13);      break;
			case VDX_TITLE_LINE6_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH14);      break;
			case VDX_TITLE_LINE6_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH15);      break;
			case VDX_TITLE_LINE6_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH16);      break;
			case VDX_TITLE_LINE6_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH17);      break;
			case VDX_TITLE_LINE6_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH18);      break;
			case VDX_TITLE_LINE6_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH19);      break;
			case VDX_TITLE_LINE6_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE6_CH20);      break;
			case VDX_TITLE_H_POS7:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS7);          break;
			case VDX_TITLE_ON7:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON7);             break;
			case VDX_TITLE_LINE7:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7);           break;
			case VDX_TITLE_BLINK7:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK7);          break;
			case VDX_TITLE_COLOR7:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR7);          break;
			case VDX_TITLE_LINE7_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH1);       break;
			case VDX_TITLE_LINE7_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH2);       break;
			case VDX_TITLE_LINE7_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH3);       break;
			case VDX_TITLE_LINE7_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH4);       break;
			case VDX_TITLE_LINE7_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH5);       break;
			case VDX_TITLE_LINE7_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH6);       break;
			case VDX_TITLE_LINE7_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH7);       break;
			case VDX_TITLE_LINE7_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH8);       break;
			case VDX_TITLE_LINE7_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH9);       break;
			case VDX_TITLE_LINE7_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH10);      break;
			case VDX_TITLE_LINE7_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH11);      break;
			case VDX_TITLE_LINE7_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH12);      break;
			case VDX_TITLE_LINE7_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH13);      break;
			case VDX_TITLE_LINE7_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH14);      break;
			case VDX_TITLE_LINE7_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH15);      break;
			case VDX_TITLE_LINE7_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH16);      break;
			case VDX_TITLE_LINE7_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH17);      break;
			case VDX_TITLE_LINE7_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH18);      break;
			case VDX_TITLE_LINE7_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH19);      break;
			case VDX_TITLE_LINE7_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE7_CH20);      break;
			case VDX_TITLE_H_POS8:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS8);          break;
			case VDX_TITLE_ON8:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON8);             break;
			case VDX_TITLE_LINE8:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8);           break;
			case VDX_TITLE_BLINK8:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK8);          break;
			case VDX_TITLE_COLOR8:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR8);          break;
			case VDX_TITLE_LINE8_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH1);       break;
			case VDX_TITLE_LINE8_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH2);       break;
			case VDX_TITLE_LINE8_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH3);       break;
			case VDX_TITLE_LINE8_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH4);       break;
			case VDX_TITLE_LINE8_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH5);       break;
			case VDX_TITLE_LINE8_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH6);       break;
			case VDX_TITLE_LINE8_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH7);       break;
			case VDX_TITLE_LINE8_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH8);       break;
			case VDX_TITLE_LINE8_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH9);       break;
			case VDX_TITLE_LINE8_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH10);      break;
			case VDX_TITLE_LINE8_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH11);      break;
			case VDX_TITLE_LINE8_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH12);      break;
			case VDX_TITLE_LINE8_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH13);      break;
			case VDX_TITLE_LINE8_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH14);      break;
			case VDX_TITLE_LINE8_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH15);      break;
			case VDX_TITLE_LINE8_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH16);      break;
			case VDX_TITLE_LINE8_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH17);      break;
			case VDX_TITLE_LINE8_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH18);      break;
			case VDX_TITLE_LINE8_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH19);      break;
			case VDX_TITLE_LINE8_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE8_CH20);      break;
			case VDX_TITLE_H_POS9:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS9);          break;
			case VDX_TITLE_ON9:                ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON9);             break;
			case VDX_TITLE_LINE9:              ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9);           break;
			case VDX_TITLE_BLINK9:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK9);          break;
			case VDX_TITLE_COLOR9:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR9);          break;
			case VDX_TITLE_LINE9_CH1:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH1);       break;
			case VDX_TITLE_LINE9_CH2:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH2);       break;
			case VDX_TITLE_LINE9_CH3:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH3);       break;
			case VDX_TITLE_LINE9_CH4:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH4);       break;
			case VDX_TITLE_LINE9_CH5:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH5);       break;
			case VDX_TITLE_LINE9_CH6:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH6);       break;
			case VDX_TITLE_LINE9_CH7:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH7);       break;
			case VDX_TITLE_LINE9_CH8:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH8);       break;
			case VDX_TITLE_LINE9_CH9:          ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH9);       break;
			case VDX_TITLE_LINE9_CH10:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH10);      break;
			case VDX_TITLE_LINE9_CH11:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH11);      break;
			case VDX_TITLE_LINE9_CH12:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH12);      break;
			case VDX_TITLE_LINE9_CH13:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH13);      break;
			case VDX_TITLE_LINE9_CH14:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH14);      break;
			case VDX_TITLE_LINE9_CH15:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH15);      break;
			case VDX_TITLE_LINE9_CH16:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH16);      break;
			case VDX_TITLE_LINE9_CH17:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH17);      break;
			case VDX_TITLE_LINE9_CH18:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH18);      break;
			case VDX_TITLE_LINE9_CH19:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH19);      break;
			case VDX_TITLE_LINE9_CH20:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE9_CH20);      break;
			case VDX_TITLE_H_POS10:            ret = VAL_TUNE(g_ViscaData.FLD.TITLE_H_POS10);         break;
			case VDX_TITLE_ON10:               ret = VAL_TUNE(g_ViscaData.FLD.TITLE_ON10);            break;
			case VDX_TITLE_LINE10:             ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10);          break;
			case VDX_TITLE_BLINK10:            ret = VAL_TUNE(g_ViscaData.FLD.TITLE_BLINK10);         break;
			case VDX_TITLE_COLOR10:            ret = VAL_TUNE(g_ViscaData.FLD.TITLE_COLOR10);         break;
			case VDX_TITLE_LINE10_CH1:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH1);      break;
			case VDX_TITLE_LINE10_CH2:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH2);      break;
			case VDX_TITLE_LINE10_CH3:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH3);      break;
			case VDX_TITLE_LINE10_CH4:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH4);      break;
			case VDX_TITLE_LINE10_CH5:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH5);      break;
			case VDX_TITLE_LINE10_CH6:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH6);      break;
			case VDX_TITLE_LINE10_CH7:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH7);      break;
			case VDX_TITLE_LINE10_CH8:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH8);      break;
			case VDX_TITLE_LINE10_CH9:         ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH9);      break;
			case VDX_TITLE_LINE10_CH10:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH10);     break;
			case VDX_TITLE_LINE10_CH11:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH11);     break;
			case VDX_TITLE_LINE10_CH12:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH12);     break;
			case VDX_TITLE_LINE10_CH13:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH13);     break;
			case VDX_TITLE_LINE10_CH14:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH14);     break;
			case VDX_TITLE_LINE10_CH15:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH15);     break;
			case VDX_TITLE_LINE10_CH16:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH16);     break;
			case VDX_TITLE_LINE10_CH17:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH17);     break;
			case VDX_TITLE_LINE10_CH18:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH18);     break;
			case VDX_TITLE_LINE10_CH19:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH19);     break;
			case VDX_TITLE_LINE10_CH20:        ret = VAL_TUNE(g_ViscaData.FLD.TITLE_LINE10_CH20);     break;
			case VDX_MUTE_ON:                  ret = VAL_TUNE(g_ViscaData.FLD.MUTE_ON);               break;
			case VDX_MASK_CL_ON:               ret = VAL_TUNE(g_ViscaData.FLD.MASK_CL_ON);            break;
/* use IF_EEPViscaMaskUpdate*/
			case VDX_MASK_ON01:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON01);             break;
			case VDX_MASK_DISP_ON01:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON01);        break;
			case VDX_MASK_I01:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I01);              break;
			case VDX_MASK_TRANS01:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS01);          break;
			case VDX_MASK_MOSAIC01:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC01);         break;
			case VDX_MASK_COLOR_ON01:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON01);       break;
			case VDX_MASK_COLOR_OFF01:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF01);      break;
			case VDX_MASK_X_POS01:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS01);          break;
			case VDX_MASK_Y_POS01:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS01);          break;
			case VDX_MASK_WIDTH01:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH01);          break;
			case VDX_MASK_HEIGHT01:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT01);         break;
			case VDX_MASK_PAN_ANGLE01:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE01);      break;
			case VDX_MASK_TILT_ANGLE01:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE01);     break;
			case VDX_MASK_ZOOM01:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM01);           break;
			case VDX_MASK_ON02:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON02);             break;
			case VDX_MASK_DISP_ON02:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON02);        break;
			case VDX_MASK_I02:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I02);              break;
			case VDX_MASK_TRANS02:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS02);          break;
			case VDX_MASK_MOSAIC02:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC02);         break;
			case VDX_MASK_COLOR_ON02:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON02);       break;
			case VDX_MASK_COLOR_OFF02:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF02);      break;
			case VDX_MASK_X_POS02:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS02);          break;
			case VDX_MASK_Y_POS02:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS02);          break;
			case VDX_MASK_WIDTH02:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH02);          break;
			case VDX_MASK_HEIGHT02:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT02);         break;
			case VDX_MASK_PAN_ANGLE02:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE02);      break;
			case VDX_MASK_TILT_ANGLE02:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE02);     break;
			case VDX_MASK_ZOOM02:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM02);           break;
			case VDX_MASK_ON03:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON03);             break;
			case VDX_MASK_DISP_ON03:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON03);        break;
			case VDX_MASK_I03:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I03);              break;
			case VDX_MASK_TRANS03:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS03);          break;
			case VDX_MASK_MOSAIC03:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC03);         break;
			case VDX_MASK_COLOR_ON03:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON03);       break;
			case VDX_MASK_COLOR_OFF03:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF03);      break;
			case VDX_MASK_X_POS03:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS03);          break;
			case VDX_MASK_Y_POS03:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS03);          break;
			case VDX_MASK_WIDTH03:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH03);          break;
			case VDX_MASK_HEIGHT03:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT03);         break;
			case VDX_MASK_PAN_ANGLE03:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE03);      break;
			case VDX_MASK_TILT_ANGLE03:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE03);     break;
			case VDX_MASK_ZOOM03:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM03);           break;
			case VDX_MASK_ON04:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON04);             break;
			case VDX_MASK_DISP_ON04:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON04);        break;
			case VDX_MASK_I04:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I04);              break;
			case VDX_MASK_TRANS04:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS04);          break;
			case VDX_MASK_MOSAIC04:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC04);         break;
			case VDX_MASK_COLOR_ON04:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON04);       break;
			case VDX_MASK_COLOR_OFF04:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF04);      break;
			case VDX_MASK_X_POS04:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS04);          break;
			case VDX_MASK_Y_POS04:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS04);          break;
			case VDX_MASK_WIDTH04:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH04);          break;
			case VDX_MASK_HEIGHT04:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT04);         break;
			case VDX_MASK_PAN_ANGLE04:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE04);      break;
			case VDX_MASK_TILT_ANGLE04:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE04);     break;
			case VDX_MASK_ZOOM04:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM04);           break;
			case VDX_MASK_ON05:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON05);             break;
			case VDX_MASK_DISP_ON05:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON05);        break;
			case VDX_MASK_I05:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I05);              break;
			case VDX_MASK_TRANS05:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS05);          break;
			case VDX_MASK_MOSAIC05:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC05);         break;
			case VDX_MASK_COLOR_ON05:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON05);       break;
			case VDX_MASK_COLOR_OFF05:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF05);      break;
			case VDX_MASK_X_POS05:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS05);          break;
			case VDX_MASK_Y_POS05:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS05);          break;
			case VDX_MASK_WIDTH05:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH05);          break;
			case VDX_MASK_HEIGHT05:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT05);         break;
			case VDX_MASK_PAN_ANGLE05:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE05);      break;
			case VDX_MASK_TILT_ANGLE05:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE05);     break;
			case VDX_MASK_ZOOM05:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM05);           break;
			case VDX_MASK_ON06:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON06);             break;
			case VDX_MASK_DISP_ON06:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON06);        break;
			case VDX_MASK_I06:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I06);              break;
			case VDX_MASK_TRANS06:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS06);          break;
			case VDX_MASK_MOSAIC06:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC06);         break;
			case VDX_MASK_COLOR_ON06:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON06);       break;
			case VDX_MASK_COLOR_OFF06:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF06);      break;
			case VDX_MASK_X_POS06:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS06);          break;
			case VDX_MASK_Y_POS06:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS06);          break;
			case VDX_MASK_WIDTH06:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH06);          break;
			case VDX_MASK_HEIGHT06:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT06);         break;
			case VDX_MASK_PAN_ANGLE06:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE06);      break;
			case VDX_MASK_TILT_ANGLE06:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE06);     break;
			case VDX_MASK_ZOOM06:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM06);           break;
			case VDX_MASK_ON07:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON07);             break;
			case VDX_MASK_DISP_ON07:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON07);        break;
			case VDX_MASK_I07:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I07);              break;
			case VDX_MASK_TRANS07:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS07);          break;
			case VDX_MASK_MOSAIC07:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC07);         break;
			case VDX_MASK_COLOR_ON07:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON07);       break;
			case VDX_MASK_COLOR_OFF07:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF01);      break;
			case VDX_MASK_X_POS07:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS07);          break;
			case VDX_MASK_Y_POS07:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS07);          break;
			case VDX_MASK_WIDTH07:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH07);          break;
			case VDX_MASK_HEIGHT07:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT07);         break;
			case VDX_MASK_PAN_ANGLE07:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE07);      break;
			case VDX_MASK_TILT_ANGLE07:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE07);     break;
			case VDX_MASK_ZOOM07:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM07);           break;
			case VDX_MASK_ON08:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON08);             break;
			case VDX_MASK_DISP_ON08:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON08);        break;
			case VDX_MASK_I08:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I08);              break;
			case VDX_MASK_TRANS08:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS08);          break;
			case VDX_MASK_MOSAIC08:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC08);         break;
			case VDX_MASK_COLOR_ON08:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON08);       break;
			case VDX_MASK_COLOR_OFF08:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF08);      break;
			case VDX_MASK_X_POS08:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS08);          break;
			case VDX_MASK_Y_POS08:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS08);          break;
			case VDX_MASK_WIDTH08:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH08);          break;
			case VDX_MASK_HEIGHT08:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT08);         break;
			case VDX_MASK_PAN_ANGLE08:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE08);      break;
			case VDX_MASK_TILT_ANGLE08:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE08);     break;
			case VDX_MASK_ZOOM08:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM08);           break;
			case VDX_MASK_ON11:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON11);             break;
			case VDX_MASK_DISP_ON11:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON11);        break;
			case VDX_MASK_I11:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I11);              break;
			case VDX_MASK_TRANS11:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS11);          break;
			case VDX_MASK_MOSAIC11:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC11);         break;
			case VDX_MASK_COLOR_ON11:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON11);       break;
			case VDX_MASK_COLOR_OFF11:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF11);      break;
			case VDX_MASK_X_POS11:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS11);          break;
			case VDX_MASK_Y_POS11:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS11);          break;
			case VDX_MASK_WIDTH11:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH11);          break;
			case VDX_MASK_HEIGHT11:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT11);         break;
			case VDX_MASK_PAN_ANGLE11:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE11);      break;
			case VDX_MASK_TILT_ANGLE11:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE11);     break;
			case VDX_MASK_ZOOM11:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM11);           break;
			case VDX_MASK_ON12:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON12);             break;
			case VDX_MASK_DISP_ON12:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON12);        break;
			case VDX_MASK_I12:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I12);              break;
			case VDX_MASK_TRANS12:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS12);          break;
			case VDX_MASK_MOSAIC12:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC12);         break;
			case VDX_MASK_COLOR_ON12:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON12);       break;
			case VDX_MASK_COLOR_OFF12:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF12);      break;
			case VDX_MASK_X_POS12:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS12);          break;
			case VDX_MASK_Y_POS12:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS12);          break;
			case VDX_MASK_WIDTH12:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH12);          break;
			case VDX_MASK_HEIGHT12:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT12);         break;
			case VDX_MASK_PAN_ANGLE12:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE12);      break;
			case VDX_MASK_TILT_ANGLE12:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE12);     break;
			case VDX_MASK_ZOOM12:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM12);           break;
			case VDX_MASK_ON13:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON13);             break;
			case VDX_MASK_DISP_ON13:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON13);        break;
			case VDX_MASK_I13:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I13);              break;
			case VDX_MASK_TRANS13:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS13);          break;
			case VDX_MASK_MOSAIC13:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC13);         break;
			case VDX_MASK_COLOR_ON13:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON13);       break;
			case VDX_MASK_COLOR_OFF13:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF13);      break;
			case VDX_MASK_X_POS13:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS13);          break;
			case VDX_MASK_Y_POS13:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS13);          break;
			case VDX_MASK_WIDTH13:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH13);          break;
			case VDX_MASK_HEIGHT13:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT13);         break;
			case VDX_MASK_PAN_ANGLE13:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE13);      break;
			case VDX_MASK_TILT_ANGLE13:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE13);     break;
			case VDX_MASK_ZOOM13:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM13);           break;
			case VDX_MASK_ON14:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON14);             break;
			case VDX_MASK_DISP_ON14:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON14);        break;
			case VDX_MASK_I14:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I14);              break;
			case VDX_MASK_TRANS14:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS14);          break;
			case VDX_MASK_MOSAIC14:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC14);         break;
			case VDX_MASK_COLOR_ON14:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON14);       break;
			case VDX_MASK_COLOR_OFF14:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF14);      break;
			case VDX_MASK_X_POS14:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS14);          break;
			case VDX_MASK_Y_POS14:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS14);          break;
			case VDX_MASK_WIDTH14:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH14);          break;
			case VDX_MASK_HEIGHT14:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT14);         break;
			case VDX_MASK_PAN_ANGLE14:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE14);      break;
			case VDX_MASK_TILT_ANGLE14:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE14);     break;
			case VDX_MASK_ZOOM14:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM14);           break;
			case VDX_MASK_ON15:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON15);             break;
			case VDX_MASK_DISP_ON15:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON15);        break;
			case VDX_MASK_I15:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I15);              break;
			case VDX_MASK_TRANS15:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS15);          break;
			case VDX_MASK_MOSAIC15:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC15);         break;
			case VDX_MASK_COLOR_ON15:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON15);       break;
			case VDX_MASK_COLOR_OFF15:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF15);      break;
			case VDX_MASK_X_POS15:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS15);          break;
			case VDX_MASK_Y_POS15:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS15);          break;
			case VDX_MASK_WIDTH15:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH15);          break;
			case VDX_MASK_HEIGHT15:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT15);         break;
			case VDX_MASK_PAN_ANGLE15:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE15);      break;
			case VDX_MASK_TILT_ANGLE15:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE15);     break;
			case VDX_MASK_ZOOM15:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM15);           break;
			case VDX_MASK_ON16:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON16);             break;
			case VDX_MASK_DISP_ON16:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON16);        break;
			case VDX_MASK_I16:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I16);              break;
			case VDX_MASK_TRANS16:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS16);          break;
			case VDX_MASK_MOSAIC16:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC16);         break;
			case VDX_MASK_COLOR_ON16:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON16);       break;
			case VDX_MASK_COLOR_OFF16:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF16);      break;
			case VDX_MASK_X_POS16:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS16);          break;
			case VDX_MASK_Y_POS16:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS16);          break;
			case VDX_MASK_WIDTH16:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH16);          break;
			case VDX_MASK_HEIGHT16:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT16);         break;
			case VDX_MASK_PAN_ANGLE16:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE16);      break;
			case VDX_MASK_TILT_ANGLE16:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE16);     break;
			case VDX_MASK_ZOOM16:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM16);           break;
			case VDX_MASK_ON17:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON17);             break;
			case VDX_MASK_DISP_ON17:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON17);        break;
			case VDX_MASK_I17:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I17);              break;
			case VDX_MASK_TRANS17:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS17);          break;
			case VDX_MASK_MOSAIC17:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC17);         break;
			case VDX_MASK_COLOR_ON17:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON17);       break;
			case VDX_MASK_COLOR_OFF17:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF17);      break;
			case VDX_MASK_X_POS17:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS17);          break;
			case VDX_MASK_Y_POS17:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS17);          break;
			case VDX_MASK_WIDTH17:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH17);          break;
			case VDX_MASK_HEIGHT17:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT17);         break;
			case VDX_MASK_PAN_ANGLE17:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE17);      break;
			case VDX_MASK_TILT_ANGLE17:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE17);     break;
			case VDX_MASK_ZOOM17:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM17);           break;
			case VDX_MASK_ON18:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON18);             break;
			case VDX_MASK_DISP_ON18:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON18);        break;
			case VDX_MASK_I18:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I18);              break;
			case VDX_MASK_TRANS18:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS18);          break;
			case VDX_MASK_MOSAIC18:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC18);         break;
			case VDX_MASK_COLOR_ON18:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON18);       break;
			case VDX_MASK_COLOR_OFF18:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF18);      break;
			case VDX_MASK_X_POS18:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS18);          break;
			case VDX_MASK_Y_POS18:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS18);          break;
			case VDX_MASK_WIDTH18:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH18);          break;
			case VDX_MASK_HEIGHT18:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT18);         break;
			case VDX_MASK_PAN_ANGLE18:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE18);      break;
			case VDX_MASK_TILT_ANGLE18:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE18);     break;
			case VDX_MASK_ZOOM18:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM18);           break;
			case VDX_MASK_ON21:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON21);             break;
			case VDX_MASK_DISP_ON21:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON21);        break;
			case VDX_MASK_I21:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I21);              break;
			case VDX_MASK_TRANS21:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS21);          break;
			case VDX_MASK_MOSAIC21:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC21);         break;
			case VDX_MASK_COLOR_ON21:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON21);       break;
			case VDX_MASK_COLOR_OFF21:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF21);      break;
			case VDX_MASK_X_POS21:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS21);          break;
			case VDX_MASK_Y_POS21:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS21);          break;
			case VDX_MASK_WIDTH21:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH21);          break;
			case VDX_MASK_HEIGHT21:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT21);         break;
			case VDX_MASK_PAN_ANGLE21:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE21);      break;
			case VDX_MASK_TILT_ANGLE21:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE21);     break;
			case VDX_MASK_ZOOM21:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM21);           break;
			case VDX_MASK_ON22:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON22);             break;
			case VDX_MASK_DISP_ON22:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON22);        break;
			case VDX_MASK_I22:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I22);              break;
			case VDX_MASK_TRANS22:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS22);          break;
			case VDX_MASK_MOSAIC22:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC22);         break;
			case VDX_MASK_COLOR_ON22:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON22);       break;
			case VDX_MASK_COLOR_OFF22:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF22);      break;
			case VDX_MASK_X_POS22:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS22);          break;
			case VDX_MASK_Y_POS22:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS22);          break;
			case VDX_MASK_WIDTH22:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH22);          break;
			case VDX_MASK_HEIGHT22:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT22);         break;
			case VDX_MASK_PAN_ANGLE22:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE22);      break;
			case VDX_MASK_TILT_ANGLE22:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE22);     break;
			case VDX_MASK_ZOOM22:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM22);           break;
			case VDX_MASK_ON23:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON23);             break;
			case VDX_MASK_DISP_ON23:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON23);        break;
			case VDX_MASK_I23:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I23);              break;
			case VDX_MASK_TRANS23:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS23);          break;
			case VDX_MASK_MOSAIC23:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC23);         break;
			case VDX_MASK_COLOR_ON23:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON23);       break;
			case VDX_MASK_COLOR_OFF23:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF23);      break;
			case VDX_MASK_X_POS23:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS23);          break;
			case VDX_MASK_Y_POS23:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS23);          break;
			case VDX_MASK_WIDTH23:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH23);          break;
			case VDX_MASK_HEIGHT23:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT23);         break;
			case VDX_MASK_PAN_ANGLE23:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE23);      break;
			case VDX_MASK_TILT_ANGLE23:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE23);     break;
			case VDX_MASK_ZOOM23:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM23);           break;
			case VDX_MASK_ON24:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON24);             break;
			case VDX_MASK_DISP_ON24:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON24);        break;
			case VDX_MASK_I24:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I24);              break;
			case VDX_MASK_TRANS24:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS24);          break;
			case VDX_MASK_MOSAIC24:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC24);         break;
			case VDX_MASK_COLOR_ON24:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON24);       break;
			case VDX_MASK_COLOR_OFF24:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF24);      break;
			case VDX_MASK_X_POS24:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS24);          break;
			case VDX_MASK_Y_POS24:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS24);          break;
			case VDX_MASK_WIDTH24:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH24);          break;
			case VDX_MASK_HEIGHT24:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT24);         break;
			case VDX_MASK_PAN_ANGLE24:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE24);      break;
			case VDX_MASK_TILT_ANGLE24:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE24);     break;
			case VDX_MASK_ZOOM24:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM24);           break;
			case VDX_MASK_ON25:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON25);             break;
			case VDX_MASK_DISP_ON25:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON25);        break;
			case VDX_MASK_I25:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I25);              break;
			case VDX_MASK_TRANS25:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS25);          break;
			case VDX_MASK_MOSAIC25:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC25);         break;
			case VDX_MASK_COLOR_ON25:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON25);       break;
			case VDX_MASK_COLOR_OFF25:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF25);      break;
			case VDX_MASK_X_POS25:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS25);          break;
			case VDX_MASK_Y_POS25:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS25);          break;
			case VDX_MASK_WIDTH25:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH25);          break;
			case VDX_MASK_HEIGHT25:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT25);         break;
			case VDX_MASK_PAN_ANGLE25:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE25);      break;
			case VDX_MASK_TILT_ANGLE25:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE25);     break;
			case VDX_MASK_ZOOM25:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM25);           break;
			case VDX_MASK_ON26:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON26);             break;
			case VDX_MASK_DISP_ON26:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON26);        break;
			case VDX_MASK_I26:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I26);              break;
			case VDX_MASK_TRANS26:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS26);          break;
			case VDX_MASK_MOSAIC26:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC26);         break;
			case VDX_MASK_COLOR_ON26:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON26);       break;
			case VDX_MASK_COLOR_OFF26:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF26);      break;
			case VDX_MASK_X_POS26:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS26);          break;
			case VDX_MASK_Y_POS26:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS26);          break;
			case VDX_MASK_WIDTH26:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH26);          break;
			case VDX_MASK_HEIGHT26:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT26);         break;
			case VDX_MASK_PAN_ANGLE26:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE26);      break;
			case VDX_MASK_TILT_ANGLE26:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE26);     break;
			case VDX_MASK_ZOOM26:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM26);           break;
			case VDX_MASK_ON27:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON27);             break;
			case VDX_MASK_DISP_ON27:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON27);        break;
			case VDX_MASK_I27:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I27);              break;
			case VDX_MASK_TRANS27:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS27);          break;
			case VDX_MASK_MOSAIC27:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC27);         break;
			case VDX_MASK_COLOR_ON27:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON27);       break;
			case VDX_MASK_COLOR_OFF27:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF27);      break;
			case VDX_MASK_X_POS27:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS27);          break;
			case VDX_MASK_Y_POS27:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS27);          break;
			case VDX_MASK_WIDTH27:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH27);          break;
			case VDX_MASK_HEIGHT27:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT27);         break;
			case VDX_MASK_PAN_ANGLE27:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE27);      break;
			case VDX_MASK_TILT_ANGLE27:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE27);     break;
			case VDX_MASK_ZOOM27:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM27);           break;
			case VDX_MASK_ON28:                ret = VAL_TUNE(g_ViscaData.FLD.MASK_ON28);             break;
			case VDX_MASK_DISP_ON28:           ret = VAL_TUNE(g_ViscaData.FLD.MASK_DISP_ON28);        break;
			case VDX_MASK_I28:                 ret = VAL_TUNE(g_ViscaData.FLD.MASK_I28);              break;
			case VDX_MASK_TRANS28:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_TRANS28);          break;
			case VDX_MASK_MOSAIC28:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_MOSAIC28);         break;
			case VDX_MASK_COLOR_ON28:          ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_ON28);       break;
			case VDX_MASK_COLOR_OFF28:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_COLOR_OFF28);      break;
			case VDX_MASK_X_POS28:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_X_POS28);          break;
			case VDX_MASK_Y_POS28:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_Y_POS28);          break;
			case VDX_MASK_WIDTH28:             ret = VAL_TUNE(g_ViscaData.FLD.MASK_WIDTH28);          break;
			case VDX_MASK_HEIGHT28:            ret = VAL_TUNE(g_ViscaData.FLD.MASK_HEIGHT28);         break;
			case VDX_MASK_PAN_ANGLE28:         ret = VAL_TUNE(g_ViscaData.FLD.MASK_PAN_ANGLE28);      break;
			case VDX_MASK_TILT_ANGLE28:        ret = VAL_TUNE(g_ViscaData.FLD.MASK_TILT_ANGLE28);     break;
			case VDX_MASK_ZOOM28:              ret = VAL_TUNE(g_ViscaData.FLD.MASK_ZOOM28);           break;
#endif
			case VDX_CAM_ID_H:                 ret = VAL_TUNE(g_ViscaData.FLD.CAM_ID_H);              break;
			case VDX_CAM_ID_L:                 ret = VAL_TUNE(g_ViscaData.FLD.CAM_ID_L);              break;
			case VDX_MD_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.MD_ON);                 break;
			case VDX_MD_DISP:                  ret = VAL_TUNE(g_ViscaData.FLD.MD_DISP);              break;
			case VDX_MD_FRAME:                 ret = VAL_TUNE(g_ViscaData.FLD.MD_FRAME);              break;
			case VDX_MD_THRS_VAL:              ret = VAL_TUNE(g_ViscaData.FLD.MD_THRS_VAL);           break;
			case VDX_MD_INTERVAL_TIME:         ret = VAL_TUNE(g_ViscaData.FLD.MD_INTERVAL_TIME);      break;
/* use IF_EEPViscaMDUpdate*/
			case VDX_MD_SRT_H_POS1:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_H_POS1);         break;
			case VDX_MD_SRT_V_POS1:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_V_POS1);         break;
			case VDX_MD_END_H_POS1:            ret = VAL_TUNE(g_ViscaData.FLD.MD_END_H_POS1);         break;
			case VDX_MD_END_V_POS1:            ret = VAL_TUNE(g_ViscaData.FLD.MD_END_V_POS1);         break;
			case VDX_MD_SRT_H_POS2:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_H_POS2);         break;
			case VDX_MD_SRT_V_POS2:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_V_POS2);         break;
			case VDX_MD_STP_H_POS2:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_H_POS2);         break;
			case VDX_MD_STP_V_POS2:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_V_POS2);         break;
			case VDX_MD_SRT_H_POS3:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_H_POS3);         break;
			case VDX_MD_SRT_V_POS3:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_V_POS3);         break;
			case VDX_MD_STP_H_POS3:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_H_POS3);         break;
			case VDX_MD_STP_V_POS3:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_V_POS3);         break;
			case VDX_MD_SRT_H_POS4:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_H_POS4);         break;
			case VDX_MD_SRT_V_POS4:            ret = VAL_TUNE(g_ViscaData.FLD.MD_SRT_V_POS4);         break;
			case VDX_MD_STP_H_POS4:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_H_POS4);         break;
			case VDX_MD_STP_V_POS4:            ret = VAL_TUNE(g_ViscaData.FLD.MD_STP_V_POS4);         break;
			case VDX_CZP_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.CZP_ON);                break;
			case VDX_CZP_INTERVAL_TIME:        ret = VAL_TUNE(g_ViscaData.FLD.CZP_INTERVAL_TIME);     break;
			case VDX_CFP_ON:                   ret = VAL_TUNE(g_ViscaData.FLD.CFP_ON);                break;
			case VDX_CFP_INTERVAL_TIME:        ret = VAL_TUNE(g_ViscaData.FLD.CFP_INTERVAL_TIME);     break;
			case VDX_CE_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.CE_ON);                 break;
			case VDX_CE_THRS_VAL:              ret = VAL_TUNE(g_ViscaData.FLD.CE_THRS_VAL);           break;
			case VDX_CE_Y_HI:                  ret = VAL_TUNE(g_ViscaData.FLD.CE_Y_HI);               break;
			case VDX_CE_CR_HI:                 ret = VAL_TUNE(g_ViscaData.FLD.CE_CR_HI);              break;
			case VDX_CE_CB_HI:                 ret = VAL_TUNE(g_ViscaData.FLD.CE_CB_HI);              break;
			case VDX_CE_Y_LI:                  ret = VAL_TUNE(g_ViscaData.FLD.CE_Y_LI);               break;
			case VDX_CE_CR_LI:                 ret = VAL_TUNE(g_ViscaData.FLD.CE_CR_LI);              break;
			case VDX_CE_CB_LI:                 ret = VAL_TUNE(g_ViscaData.FLD.CE_CB_LI);              break;
			case VDX_CS_LEVEL:                 ret = VAL_TUNE(g_ViscaData.FLD.CS_LEVEL);              break;
			case VDX_CS_SET_VAL:               ret = VAL_TUNE(g_ViscaData.FLD.CS_SET_VAL);            break;
			case VDX_COLOR_GAIN:               ret = VAL_TUNE(g_ViscaData.FLD.COLOR_GAIN);            break;
			case VDX_COLOR_HUE:                ret = VAL_TUNE(g_ViscaData.FLD.COLOR_HUE);             break;
			case VDX_GAM_OFFSET:               ret = VAL_TUNE(g_ViscaData.FLD.GAM_OFFSET);			  break;
			case VDX_GAM_OFFSET_S:             ret = VAL_TUNE(g_ViscaData.FLD.GAM_OFFSET_S);          break;
			case VDX_EX_EXPCOMP_RESET:         ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPCOMP_RESET);      break;
			case VDX_EX_EXPCOMP_DIRECT:        ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPCOMP_DIRECT);     break;
			case VDX_EX_EXPAP_RESET:           ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPAP_RESET);        break;
			case VDX_EX_EXPAP_DIRECT:          ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPAP_DIRECT);       break;
			case VDX_EX_AICR_ON2OFF:           ret = VAL_TUNE(g_ViscaData.FLD.EX_AICR_ON2OFF);        break;
			case VDX_EX_AICR_OFF2ON:           ret = VAL_TUNE(g_ViscaData.FLD.EX_AICR_OFF2ON);        break;
			case VDX_EX_COLOR_GAIN:            ret = VAL_TUNE(g_ViscaData.FLD.EX_COLOR_GAIN);         break;
			case VDX_EX_COLOR_HUE:             ret = VAL_TUNE(g_ViscaData.FLD.EX_COLOR_HUE);          break;
/* use IF_EEPViscaCMemUpdate*/
			case VDX_ZOOM_POS01:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS01);            break;
			case VDX_DZOOM_ON01:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON01);            break;
			case VDX_F_MODE01:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE01);              break;
			case VDX_AF_MODE01:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE01);             break;
			case VDX_COMP_ON01:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON01);             break;
			case VDX_BLC_ON01:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON01);              break;
			case VDX_ASS_ON01:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON01);              break;
			case VDX_FOCUS_POS01:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS01);           break;
			case VDX_SHUTTER_STEP01:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP01);        break;
			case VDX_BRIGHT_STEP01:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP01);         break;
			case VDX_IRIS_STEP01:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP01);           break;
			case VDX_GAIN_STEP01:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP01);           break;
			case VDX_EXP_COMP_VAL01:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL01);        break;
			case VDX_WB_MODE01:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE01);             break;
			case VDX_ICR_ON01:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON01);              break;
			case VDX_WD_MODE01:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE01);             break;
			case VDX_DEFOG_ON01:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON01);            break;
			case VDX_R_GAIN01:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN01);              break;
			case VDX_B_GAIN01:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN01);              break;
			case VDX_APER_GAIN01:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN01);           break;
			case VDX_WD_BRT_L01:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L01);            break;
			case VDX_WD_BRT_COMP01:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP01);         break;
			case VDX_WD_COMP_L01:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L01);           break;
			case VDX_AE_MODE01 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE01);	          break;
			case VDX_ZOOM_POS02:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS02);            break;
			case VDX_DZOOM_ON02:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON02);            break;
			case VDX_F_MODE02:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE02);              break;
			case VDX_AF_MODE02:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE02);             break;
			case VDX_COMP_ON02:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON02);             break;
			case VDX_BLC_ON02:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON02);              break;
			case VDX_ASS_ON02:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON02);              break;
			case VDX_FOCUS_POS02:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS02);           break;
			case VDX_SHUTTER_STEP02:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP02);        break;
			case VDX_BRIGHT_STEP02:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP02);         break;
			case VDX_IRIS_STEP02:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP02);           break;
			case VDX_GAIN_STEP02:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP02);           break;
			case VDX_EXP_COMP_VAL02:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL02);        break;
			case VDX_WB_MODE02:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE02);             break;
			case VDX_ICR_ON02:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON02);              break;
			case VDX_WD_MODE02:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE02);             break;
			case VDX_DEFOG_ON02:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON02);            break;
			case VDX_R_GAIN02:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN02);              break;
			case VDX_B_GAIN02:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN02);              break;
			case VDX_APER_GAIN02:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN02);           break;
			case VDX_WD_BRT_L02:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L02);            break;
			case VDX_WD_BRT_COMP02:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP02);         break;
			case VDX_WD_COMP_L02:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L02);           break;
			case VDX_AE_MODE02 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE02);	          break;
			case VDX_ZOOM_POS03:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS03);            break;
			case VDX_DZOOM_ON03:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON03);            break;
			case VDX_F_MODE03:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE03);              break;
			case VDX_AF_MODE03:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE03);             break;
			case VDX_COMP_ON03:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON03);             break;
			case VDX_BLC_ON03:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON03);              break;
			case VDX_ASS_ON03:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON03);              break;
			case VDX_FOCUS_POS03:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS03);           break;
			case VDX_SHUTTER_STEP03:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP03);        break;
			case VDX_BRIGHT_STEP03:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP03);         break;
			case VDX_IRIS_STEP03:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP03);           break;
			case VDX_GAIN_STEP03:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP03);           break;
			case VDX_EXP_COMP_VAL03:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL03);        break;
			case VDX_WB_MODE03:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE03);             break;
			case VDX_ICR_ON03:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON03);              break;
			case VDX_WD_MODE03:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE03);             break;
			case VDX_DEFOG_ON03:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON03);            break;
			case VDX_R_GAIN03:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN03);              break;
			case VDX_B_GAIN03:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN03);              break;
			case VDX_APER_GAIN03:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN03);           break;
			case VDX_WD_BRT_L03:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L03);            break;
			case VDX_WD_BRT_COMP03:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP03);         break;
			case VDX_WD_COMP_L03:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L03);           break;
			case VDX_AE_MODE03 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE03);	          break;
			case VDX_ZOOM_POS04:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS04);            break;
			case VDX_DZOOM_ON04:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON04);            break;
			case VDX_F_MODE04:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE04);              break;
			case VDX_AF_MODE04:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE04);             break;
			case VDX_COMP_ON04:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON04);             break;
			case VDX_BLC_ON04:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON04);              break;
			case VDX_ASS_ON04:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON04);              break;
			case VDX_FOCUS_POS04:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS04);           break;
			case VDX_SHUTTER_STEP04:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP04);        break;
			case VDX_BRIGHT_STEP04:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP04);         break;
			case VDX_IRIS_STEP04:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP04);           break;
			case VDX_GAIN_STEP04:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP04);           break;
			case VDX_EXP_COMP_VAL04:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL04);        break;
			case VDX_WB_MODE04:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE04);             break;
			case VDX_ICR_ON04:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON04);              break;
			case VDX_WD_MODE04:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE04);             break;
			case VDX_DEFOG_ON04:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON04);            break;
			case VDX_R_GAIN04:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN04);              break;
			case VDX_B_GAIN04:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN04);              break;
			case VDX_APER_GAIN04:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN04);           break;
			case VDX_WD_BRT_L04:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L04);            break;
			case VDX_WD_BRT_COMP04:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP04);         break;
			case VDX_WD_COMP_L04:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L04);           break;
			case VDX_AE_MODE04 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE04);	          break;
			case VDX_ZOOM_POS05:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS05);            break;
			case VDX_DZOOM_ON05:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON05);            break;
			case VDX_F_MODE05:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE05);              break;
			case VDX_AF_MODE05:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE05);             break;
			case VDX_COMP_ON05:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON05);             break;
			case VDX_BLC_ON05:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON05);              break;
			case VDX_ASS_ON05:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON05);              break;
			case VDX_FOCUS_POS05:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS05);           break;
			case VDX_SHUTTER_STEP05:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP05);        break;
			case VDX_BRIGHT_STEP05:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP05);         break;
			case VDX_IRIS_STEP05:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP05);           break;
			case VDX_GAIN_STEP05:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP05);           break;
			case VDX_EXP_COMP_VAL05:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL05);        break;
			case VDX_WB_MODE05:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE05);             break;
			case VDX_ICR_ON05:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON05);              break;
			case VDX_WD_MODE05:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE05);             break;
			case VDX_DEFOG_ON05:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON05);            break;
			case VDX_R_GAIN05:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN05);              break;
			case VDX_B_GAIN05:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN05);              break;
			case VDX_APER_GAIN05:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN05);           break;
			case VDX_WD_BRT_L05:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L05);            break;
			case VDX_WD_BRT_COMP05:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP05);         break;
			case VDX_WD_COMP_L05:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L05);           break;
			case VDX_AE_MODE05 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE05);	          break;
			case VDX_ZOOM_POS06:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS06);            break;
			case VDX_DZOOM_ON06:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON06);            break;
			case VDX_F_MODE06:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE06);              break;
			case VDX_AF_MODE06:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE06);             break;
			case VDX_COMP_ON06:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON06);             break;
			case VDX_BLC_ON06:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON06);              break;
			case VDX_ASS_ON06:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON06);              break;
			case VDX_FOCUS_POS06:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS06);           break;
			case VDX_SHUTTER_STEP06:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP06);        break;
			case VDX_BRIGHT_STEP06:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP06);         break;
			case VDX_IRIS_STEP06:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP06);           break;
			case VDX_GAIN_STEP06:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP06);           break;
			case VDX_EXP_COMP_VAL06:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL06);        break;
			case VDX_WB_MODE06:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE06);             break;
			case VDX_ICR_ON06:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON06);              break;
			case VDX_WD_MODE06:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE06);             break;
			case VDX_DEFOG_ON06:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON06);            break;
			case VDX_R_GAIN06:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN06);              break;
			case VDX_B_GAIN06:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN06);              break;
			case VDX_APER_GAIN06:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN06);           break;
			case VDX_WD_BRT_L06:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L06);            break;
			case VDX_WD_BRT_COMP06:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP06);         break;
			case VDX_WD_COMP_L06:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L06);           break;
			case VDX_AE_MODE06 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE06);	          break;
			case VDX_ZOOM_POS07:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS07);            break;
			case VDX_DZOOM_ON07:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON07);            break;
			case VDX_F_MODE07:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE07);              break;
			case VDX_AF_MODE07:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE07);             break;
			case VDX_COMP_ON07:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON07);             break;
			case VDX_BLC_ON07:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON07);              break;
			case VDX_ASS_ON07:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON07);              break;
			case VDX_FOCUS_POS07:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS07);           break;
			case VDX_SHUTTER_STEP07:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP07);        break;
			case VDX_BRIGHT_STEP07:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP07);         break;
			case VDX_IRIS_STEP07:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP07);           break;
			case VDX_GAIN_STEP07:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP07);           break;
			case VDX_EXP_COMP_VAL07:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL07);        break;
			case VDX_WB_MODE07:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE07);             break;
			case VDX_ICR_ON07:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON07);              break;
			case VDX_WD_MODE07:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE07);             break;
			case VDX_DEFOG_ON07:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON07);            break;
			case VDX_R_GAIN07:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN07);              break;
			case VDX_B_GAIN07:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN07);              break;
			case VDX_APER_GAIN07:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN07);           break;
			case VDX_WD_BRT_L07:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L07);            break;
			case VDX_WD_BRT_COMP07:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP07);         break;
			case VDX_WD_COMP_L07:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L07);           break;
			case VDX_AE_MODE07 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE07);	          break;
			case VDX_ZOOM_POS08:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS08);            break;
			case VDX_DZOOM_ON08:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON08);            break;
			case VDX_F_MODE08:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE08);              break;
			case VDX_AF_MODE08:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE08);             break;
			case VDX_COMP_ON08:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON08);             break;
			case VDX_BLC_ON08:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON08);              break;
			case VDX_ASS_ON08:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON08);              break;
			case VDX_FOCUS_POS08:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS08);           break;
			case VDX_SHUTTER_STEP08:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP08);        break;
			case VDX_BRIGHT_STEP08:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP08);         break;
			case VDX_IRIS_STEP08:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP08);           break;
			case VDX_GAIN_STEP08:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP08);           break;
			case VDX_EXP_COMP_VAL08:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL08);        break;
			case VDX_WB_MODE08:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE08);             break;
			case VDX_ICR_ON08:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON08);              break;
			case VDX_WD_MODE08:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE08);             break;
			case VDX_DEFOG_ON08:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON08);            break;
			case VDX_R_GAIN08:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN08);              break;
			case VDX_B_GAIN08:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN08);              break;
			case VDX_APER_GAIN08:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN08);           break;
			case VDX_WD_BRT_L08:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L08);            break;
			case VDX_WD_BRT_COMP08:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP08);         break;
			case VDX_WD_COMP_L08:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L08);           break;
			case VDX_AE_MODE08 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE08);	          break;
			case VDX_ZOOM_POS09:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS09);            break;
			case VDX_DZOOM_ON09:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON09);            break;
			case VDX_F_MODE09:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE09);              break;
			case VDX_AF_MODE09:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE09);             break;
			case VDX_COMP_ON09:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON09);             break;
			case VDX_BLC_ON09:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON09);              break;
			case VDX_ASS_ON09:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON09);              break;
			case VDX_FOCUS_POS09:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS09);           break;
			case VDX_SHUTTER_STEP09:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP09);        break;
			case VDX_BRIGHT_STEP09:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP09);         break;
			case VDX_IRIS_STEP09:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP09);           break;
			case VDX_GAIN_STEP09:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP09);           break;
			case VDX_EXP_COMP_VAL09:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL09);        break;
			case VDX_WB_MODE09:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE09);             break;
			case VDX_ICR_ON09:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON09);              break;
			case VDX_WD_MODE09:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE09);             break;
			case VDX_DEFOG_ON09:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON09);            break;
			case VDX_R_GAIN09:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN09);              break;
			case VDX_B_GAIN09:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN09);              break;
			case VDX_APER_GAIN09:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN09);           break;
			case VDX_WD_BRT_L09:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L09);            break;
			case VDX_WD_BRT_COMP09:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP09);         break;
			case VDX_WD_COMP_L09:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L09);           break;
			case VDX_AE_MODE09 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE09);	          break;
			case VDX_ZOOM_POS10:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS10);            break;
			case VDX_DZOOM_ON10:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON10);            break;
			case VDX_F_MODE10:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE10);              break;
			case VDX_AF_MODE10:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE10);             break;
			case VDX_COMP_ON10:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON10);             break;
			case VDX_BLC_ON10:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON10);              break;
			case VDX_ASS_ON10:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON10);              break;
			case VDX_FOCUS_POS10:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS10);           break;
			case VDX_SHUTTER_STEP10:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP10);        break;
			case VDX_BRIGHT_STEP10:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP10);         break;
			case VDX_IRIS_STEP10:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP10);           break;
			case VDX_GAIN_STEP10:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP10);           break;
			case VDX_EXP_COMP_VAL10:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL10);        break;
			case VDX_WB_MODE10:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE10);             break;
			case VDX_ICR_ON10:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON10);              break;
			case VDX_WD_MODE10:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE10);             break;
			case VDX_DEFOG_ON10:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON10);            break;
			case VDX_R_GAIN10:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN10);              break;
			case VDX_B_GAIN10:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN10);              break;
			case VDX_APER_GAIN10:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN10);           break;
			case VDX_WD_BRT_L10:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L10);            break;
			case VDX_WD_BRT_COMP10:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP10);         break;
			case VDX_WD_COMP_L10:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L10);           break;
			case VDX_AE_MODE10 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE10);	          break;
			case VDX_ZOOM_POS11:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS11);            break;
			case VDX_DZOOM_ON11:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON11);            break;
			case VDX_F_MODE11:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE11);              break;
			case VDX_AF_MODE11:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE11);             break;
			case VDX_COMP_ON11:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON11);             break;
			case VDX_BLC_ON11:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON11);              break;
			case VDX_ASS_ON11:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON11);              break;
			case VDX_FOCUS_POS11:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS11);           break;
			case VDX_SHUTTER_STEP11:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP11);        break;
			case VDX_BRIGHT_STEP11:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP11);         break;
			case VDX_IRIS_STEP11:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP11);           break;
			case VDX_GAIN_STEP11:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP11);           break;
			case VDX_EXP_COMP_VAL11:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL11);        break;
			case VDX_WB_MODE11:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE11);             break;
			case VDX_ICR_ON11:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON11);              break;
			case VDX_WD_MODE11:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE11);             break;
			case VDX_DEFOG_ON11:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON11);            break;
			case VDX_R_GAIN11:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN11);              break;
			case VDX_B_GAIN11:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN11);              break;
			case VDX_APER_GAIN11:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN11);           break;
			case VDX_WD_BRT_L11:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L11);            break;
			case VDX_WD_BRT_COMP11:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP11);         break;
			case VDX_WD_COMP_L11:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L11);           break;
			case VDX_AE_MODE11 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE11);	          break;
			case VDX_ZOOM_POS12:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS12);            break;
			case VDX_DZOOM_ON12:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON12);            break;
			case VDX_F_MODE12:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE12);              break;
			case VDX_AF_MODE12:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE12);             break;
			case VDX_COMP_ON12:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON12);             break;
			case VDX_BLC_ON12:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON12);              break;
			case VDX_ASS_ON12:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON12);              break;
			case VDX_FOCUS_POS12:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS12);           break;
			case VDX_SHUTTER_STEP12:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP12);        break;
			case VDX_BRIGHT_STEP12:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP12);         break;
			case VDX_IRIS_STEP12:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP12);           break;
			case VDX_GAIN_STEP12:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP12);           break;
			case VDX_EXP_COMP_VAL12:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL12);        break;
			case VDX_WB_MODE12:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE12);             break;
			case VDX_ICR_ON12:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON12);              break;
			case VDX_WD_MODE12:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE12);             break;
			case VDX_DEFOG_ON12:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON12);            break;
			case VDX_R_GAIN12:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN12);              break;
			case VDX_B_GAIN12:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN12);              break;
			case VDX_APER_GAIN12:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN12);           break;
			case VDX_WD_BRT_L12:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L12);            break;
			case VDX_WD_BRT_COMP12:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP12);         break;
			case VDX_WD_COMP_L12:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L12);           break;
			case VDX_AE_MODE12 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE12);	          break;
			case VDX_ZOOM_POS13:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS13);            break;
			case VDX_DZOOM_ON13:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON13);            break;
			case VDX_F_MODE13:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE13);              break;
			case VDX_AF_MODE13:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE13);             break;
			case VDX_COMP_ON13:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON13);             break;
			case VDX_BLC_ON13:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON13);              break;
			case VDX_ASS_ON13:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON13);              break;
			case VDX_FOCUS_POS13:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS13);           break;
			case VDX_SHUTTER_STEP13:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP13);        break;
			case VDX_BRIGHT_STEP13:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP13);         break;
			case VDX_IRIS_STEP13:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP13);           break;
			case VDX_GAIN_STEP13:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP13);           break;
			case VDX_EXP_COMP_VAL13:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL13);        break;
			case VDX_WB_MODE13:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE13);             break;
			case VDX_ICR_ON13:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON13);              break;
			case VDX_WD_MODE13:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE13);             break;
			case VDX_DEFOG_ON13:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON13);            break;
			case VDX_R_GAIN13:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN13);              break;
			case VDX_B_GAIN13:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN13);              break;
			case VDX_APER_GAIN13:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN13);           break;
			case VDX_WD_BRT_L13:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L13);            break;
			case VDX_WD_BRT_COMP13:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP13);         break;
			case VDX_WD_COMP_L13:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L13);           break;
			case VDX_AE_MODE13 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE13);	          break;
			case VDX_ZOOM_POS14:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS14);            break;
			case VDX_DZOOM_ON14:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON14);            break;
			case VDX_F_MODE14:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE14);              break;
			case VDX_AF_MODE14:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE14);             break;
			case VDX_COMP_ON14:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON14);             break;
			case VDX_BLC_ON14:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON14);              break;
			case VDX_ASS_ON14:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON14);              break;
			case VDX_FOCUS_POS14:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS14);           break;
			case VDX_SHUTTER_STEP14:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP14);        break;
			case VDX_BRIGHT_STEP14:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP14);         break;
			case VDX_IRIS_STEP14:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP14);           break;
			case VDX_GAIN_STEP14:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP14);           break;
			case VDX_EXP_COMP_VAL14:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL14);        break;
			case VDX_WB_MODE14:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE14);             break;
			case VDX_ICR_ON14:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON14);              break;
			case VDX_WD_MODE14:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE14);             break;
			case VDX_DEFOG_ON14:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON14);            break;
			case VDX_R_GAIN14:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN14);              break;
			case VDX_B_GAIN14:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN14);              break;
			case VDX_APER_GAIN14:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN14);           break;
			case VDX_WD_BRT_L14:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L14);            break;
			case VDX_WD_BRT_COMP14:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP14);         break;
			case VDX_WD_COMP_L14:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L14);           break;
			case VDX_AE_MODE14 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE14);	          break;
			case VDX_ZOOM_POS15:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS15);            break;
			case VDX_DZOOM_ON15:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON15);            break;
			case VDX_F_MODE15:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE15);              break;
			case VDX_AF_MODE15:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE15);             break;
			case VDX_COMP_ON15:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON15);             break;
			case VDX_BLC_ON15:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON15);              break;
			case VDX_ASS_ON15:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON15);              break;
			case VDX_FOCUS_POS15:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS15);           break;
			case VDX_SHUTTER_STEP15:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP15);        break;
			case VDX_BRIGHT_STEP15:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP15);         break;
			case VDX_IRIS_STEP15:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP15);           break;
			case VDX_GAIN_STEP15:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP15);           break;
			case VDX_EXP_COMP_VAL15:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL15);        break;
			case VDX_WB_MODE15:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE15);             break;
			case VDX_ICR_ON15:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON15);              break;
			case VDX_WD_MODE15:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE15);             break;
			case VDX_DEFOG_ON15:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON15);            break;
			case VDX_R_GAIN15:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN15);              break;
			case VDX_B_GAIN15:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN15);              break;
			case VDX_APER_GAIN15:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN15);           break;
			case VDX_WD_BRT_L15:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L15);            break;
			case VDX_WD_BRT_COMP15:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP15);         break;
			case VDX_WD_COMP_L15:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L15);           break;
			case VDX_AE_MODE15 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE15);	          break;
			case VDX_ZOOM_POS16:               ret = VAL_TUNE(g_ViscaData.FLD.ZOOM_POS16);            break;
			case VDX_DZOOM_ON16:               ret = VAL_TUNE(g_ViscaData.FLD.DZOOM_ON16);            break;
			case VDX_F_MODE16:                 ret = VAL_TUNE(g_ViscaData.FLD.F_MODE16);              break;
			case VDX_AF_MODE16:                ret = VAL_TUNE(g_ViscaData.FLD.AF_MODE16);             break;
			case VDX_COMP_ON16:                ret = VAL_TUNE(g_ViscaData.FLD.COMP_ON16);             break;
			case VDX_BLC_ON16:                 ret = VAL_TUNE(g_ViscaData.FLD.BLC_ON16);              break;
			case VDX_ASS_ON16:                 ret = VAL_TUNE(g_ViscaData.FLD.ASS_ON16);              break;
			case VDX_FOCUS_POS16:              ret = VAL_TUNE(g_ViscaData.FLD.FOCUS_POS16);           break;
			case VDX_SHUTTER_STEP16:           ret = VAL_TUNE(g_ViscaData.FLD.SHUTTER_STEP16);        break;
			case VDX_BRIGHT_STEP16:            ret = VAL_TUNE(g_ViscaData.FLD.BRIGHT_STEP16);         break;
			case VDX_IRIS_STEP16:              ret = VAL_TUNE(g_ViscaData.FLD.IRIS_STEP16);           break;
			case VDX_GAIN_STEP16:              ret = VAL_TUNE(g_ViscaData.FLD.GAIN_STEP16);           break;
			case VDX_EXP_COMP_VAL16:           ret = VAL_TUNE(g_ViscaData.FLD.EXP_COMP_VAL16);        break;
			case VDX_WB_MODE16:                ret = VAL_TUNE(g_ViscaData.FLD.WB_MODE16);             break;
			case VDX_ICR_ON16:                 ret = VAL_TUNE(g_ViscaData.FLD.ICR_ON16);              break;
			case VDX_WD_MODE16:                ret = VAL_TUNE(g_ViscaData.FLD.WD_MODE16);             break;
			case VDX_DEFOG_ON16:               ret = VAL_TUNE(g_ViscaData.FLD.DEFOG_ON16);            break;
			case VDX_R_GAIN16:                 ret = VAL_TUNE(g_ViscaData.FLD.R_GAIN16);              break;
			case VDX_B_GAIN16:                 ret = VAL_TUNE(g_ViscaData.FLD.B_GAIN16);              break;
			case VDX_APER_GAIN16:              ret = VAL_TUNE(g_ViscaData.FLD.APER_GAIN16);           break;
			case VDX_WD_BRT_L16:               ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_L16);            break;
			case VDX_WD_BRT_COMP16:            ret = VAL_TUNE(g_ViscaData.FLD.WD_BRT_COMP16);         break;
			case VDX_WD_COMP_L16:              ret = VAL_TUNE(g_ViscaData.FLD.WD_COMP_L16);           break;
			case VDX_AE_MODE16 :			   ret = VAL_TUNE(g_ViscaData.FLD.AE_MODE16);	          break;
			case VDX_COMM_BAUDRATE:            ret = VAL_TUNE(g_ViscaData.FLD.COMM_BAUDRATE);         break;
			case VDX_MONITORING_MODE:          ret = VAL_TUNE(g_ViscaData.FLD.MONITORING_MODE);       break;
			case VDX_AO_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.AO_ON);                 break;
			case VDX_DO_ON:                    ret = VAL_TUNE(g_ViscaData.FLD.DO_ON);                 break;
			case VDX_LVDS_OUT:                 ret = VAL_TUNE(g_ViscaData.FLD.LVDS_OUT);              break;
			case VDX_ZWIDE_LIMIT:              ret = VAL_TUNE(g_ViscaData.FLD.ZWIDE_LIMIT);           break;
			case VDX_ZTELE_LIMIT:              ret = VAL_TUNE(g_ViscaData.FLD.ZTELE_LIMIT);           break;
			case VDX_DZ_MAX:                   ret = VAL_TUNE(g_ViscaData.FLD.DZ_MAX);                break;
			case VDX_SZOOM_ON:                 ret = VAL_TUNE(g_ViscaData.FLD.SZOOM_ON);              break;
			case VDX_FTRACE_ON:                ret = VAL_TUNE(g_ViscaData.FLD.FTRACE_ON);             break;
			case VDX_FCS_OFFSET_DOME:          ret = VAL_TUNE(g_ViscaData.FLD.FCS_OFFSET_DOME);       break;
			case VDX_EX_EXPC_ON:               ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPC_ON);            break;
			case VDX_EX_EXPAP_ON:              ret = VAL_TUNE(g_ViscaData.FLD.EX_EXPAP_ON);           break;
			case VDX_EX_CGCH_ON:               ret = VAL_TUNE(g_ViscaData.FLD.EX_CGCH_ON);            break;
			case VDX_EX_AICR_F2O_ON:           ret = VAL_TUNE(g_ViscaData.FLD.EX_AICR_F2O_ON);        break;
			case VDX_GAIN_LIMIT:			   ret = VAL_TUNE(g_ViscaData.FLD.GAIN_LIMIT);            break;
			case VDX_STB_ON:				   ret = VAL_TUNE(g_ViscaData.FLD.STB_ON);                break;
			case VDX_STB_HOLD:				   ret = VAL_TUNE(g_ViscaData.FLD.STB_HOLD);              break;
			case VDX_WD_SCR_DISP:			   ret = VAL_TUNE(g_ViscaData.FLD.WD_SCR_DISP);           break;
			case VDX_WD_DET_SENS:			   ret = VAL_TUNE(g_ViscaData.FLD.WD_DET_SENS);           break;
			case VDX_WD_BUCORR_LV:			   ret = VAL_TUNE(g_ViscaData.FLD.WD_BUCORR_LV);          break;
			case VDX_WD_BOCORR_LV:			   ret = VAL_TUNE(g_ViscaData.FLD.WD_BOCORR_LV);          break;
			case VDX_WD_SHORT_EXPR:			   ret = VAL_TUNE(g_ViscaData.FLD.WD_SHORT_EXPR);         break;
			case VDX_WD_ALARM:				   ret = VAL_TUNE(g_ViscaData.FLD.WD_ALARM);              break;
			default:
				ret = -1;
				break;
		}
	}

	return ret;
}

int32 IF_EEPMotionUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val)
{
	int32 ret = -1;

	switch(idx)
	{
		case IDX_MD_STATE:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_STATE);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_STATE);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_STATE);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_STATE);	break;
				}
			}break;
		case IDX_MD_DISP:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_DISP);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_DISP);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_DISP);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_DISP);	break;
				}
			}break;
		case IDX_MD_ALARM:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_ALARM);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_ALARM);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_ALARM);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_ALARM);	break;
				}
			}break;
		case IDX_MD_SENS:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_SENS);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_SENS);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_SENS);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_SENS);	break;
				}
			}break;
		case IDX_MD_X:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_X_SRT);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_X_SRT);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_X_SRT);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_X_SRT);	break;
				}
			}break;
		case IDX_MD_Y:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_Y_SRT);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_Y_SRT);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_Y_SRT);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_Y_SRT);	break;
				}
			}break;
		case IDX_MD_W:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_WIDTH);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_WIDTH);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_WIDTH);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_WIDTH);	break;
				}
			}break;
		case IDX_MD_H:
			{
				switch(zone)
				{
					case 0:	ret = VAL_TUNE(g_OsdData.FLD.MD1_HEIGHT);	break;
					case 1:	ret = VAL_TUNE(g_OsdData.FLD.MD2_HEIGHT);	break;
					case 2:	ret = VAL_TUNE(g_OsdData.FLD.MD3_HEIGHT);	break;
					case 3:	ret = VAL_TUNE(g_OsdData.FLD.MD4_HEIGHT);	break;
				}
			}break;
	}

	return ret;
}

int32 IF_EEPPrivacyUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val)
{
	int32 ret = -1, priAddr = 0x7F;

	priAddr = 0x7F + (zone * 11);

	if(evt == IFEVT_GETVAL)
	{
		switch(idx)
		{
			case IDX_PRI_STATE:		ret = (g_OsdData.Data[priAddr] & 0x1);				break;
			case IDX_PRI_TRANS:		ret = ((g_OsdData.Data[priAddr] >> 1) & 0x2);		break;
			case IDX_PRI_COLOR:		ret = ((g_OsdData.Data[priAddr] >> 3) & 0x3);		break;
			case IDX_PRI_MOSAIC:	ret = ((g_OsdData.Data[priAddr] >> 6) & 0x2);		break;
			case IDX_PRI_X:			ret = g_OsdData.Data[priAddr + 1];					break;
			case IDX_PRI_Y:			ret = g_OsdData.Data[priAddr + 2];					break;
			case IDX_PRI_W:			ret = g_OsdData.Data[priAddr + 3];					break;
			case IDX_PRI_H:			ret = g_OsdData.Data[priAddr + 4];					break;
			case IDX_PRI_P:			ret = (g_OsdData.Data[priAddr + 5] << 8) | g_OsdData.Data[priAddr + 6];		break;
			case IDX_PRI_T:			ret = (g_OsdData.Data[priAddr + 7] << 8) | g_OsdData.Data[priAddr + 8];		break;
			case IDX_PRI_Z:			ret = (g_OsdData.Data[priAddr + 9] << 8) | g_OsdData.Data[priAddr + 10];	break;
			default:
				ret = -1;
				break;
		}
	}
	else
	{
		ret = 0;

		switch(idx)
		{
			case IDX_PRI_STATE:		g_OsdData.Data[priAddr] = (g_OsdData.Data[priAddr] & 0xfe) | (val & 0x1);			break;
			case IDX_PRI_TRANS:		g_OsdData.Data[priAddr] = (g_OsdData.Data[priAddr] & 0xf9) | ((val & 0x4) << 1);	break;
			case IDX_PRI_COLOR:		g_OsdData.Data[priAddr] = (g_OsdData.Data[priAddr] & 0xfe) | ((val & 0xc7) << 3);	break;
			case IDX_PRI_MOSAIC:	g_OsdData.Data[priAddr] = (g_OsdData.Data[priAddr] & 0xfe) | ((val & 0xc0) << 6);	break;
			case IDX_PRI_X:			g_OsdData.Data[priAddr + 1] = val;						break;
			case IDX_PRI_Y:			g_OsdData.Data[priAddr + 2] = val;						break;
			case IDX_PRI_W:			g_OsdData.Data[priAddr + 3] = val;						break;
			case IDX_PRI_H:			g_OsdData.Data[priAddr + 4] = val;						break;
			case IDX_PRI_P:
				g_OsdData.Data[priAddr + 5] = (val >> 8);
				g_OsdData.Data[priAddr + 6] = (val & 0xff);
				break;
			case IDX_PRI_T:
				g_OsdData.Data[priAddr + 7] = (val >> 8);
				g_OsdData.Data[priAddr + 8] = (val & 0xff);
				break;
			case IDX_PRI_Z:
				g_OsdData.Data[priAddr + 9] = (val >> 8);
				g_OsdData.Data[priAddr + 10] = (val & 0xff);
				break;
			default:
				ret = -1;
				break;
		}
	}

	return ret;
}
int32 IF_EEPViscaMdUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val)
{
	int32 ret = -1, addr = 0x24D;
	addr = 0x24D + (zone * 4);

	if(evt == IFEVT_GETVAL)
	{
		switch(idx)
		{
			case VDX_MD_SRT_H_POS :		ret = g_ViscaData.Data[addr];						break;
			case VDX_MD_SRT_V_POS :		ret = g_ViscaData.Data[addr+1];						break;
			case VDX_MD_STP_H_POS :		ret = g_ViscaData.Data[addr+2];						break;
			case VDX_MD_STP_V_POS :		ret = g_ViscaData.Data[addr+3];						break;
		}
	}
	else
	{
		ret = 0;
		switch(idx)
		{
			case VDX_MD_SRT_H_POS :		g_ViscaData.Data[addr] = val;						break;
			case VDX_MD_SRT_V_POS :		g_ViscaData.Data[addr+1] = val;						break;
			case VDX_MD_STP_H_POS :		g_ViscaData.Data[addr+2] = val;						break;
			case VDX_MD_STP_V_POS :		g_ViscaData.Data[addr+3] = val;						break;
			default:
				ret = -1;
				break;
		}
	}

	return ret;

}
int32 IF_EEPViscaMaskUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val)
{
	int32 ret = -1, addr = 0x128;
	addr = 0x128 + (zone * 0x0C);

	if(evt == IFEVT_GETVAL)
	{
		switch(idx)
		{
			case VDX_MASK_ON :			ret = (g_ViscaData.Data[addr] & 0x01);				break;
			case VDX_MASK_DISP :		ret = ((g_ViscaData.Data[addr]>>1) & 0x01);			break;
			case VDX_MASK_I :			ret = ((g_ViscaData.Data[addr]>>5) & 0x01);			break;
			case VDX_MASK_TRANS : 		ret = ((g_ViscaData.Data[addr]>>6) & 0x01);			break;
			case VDX_MASK_MOSAIC : 		ret = ((g_ViscaData.Data[addr]>>7) & 0x01);			break;
			case VDX_MASK_COLOR_ON :	ret = (g_ViscaData.Data[addr+1] & 0x0f);			break;
			case VDX_MASK_COLOR_OFF :	ret = ((g_ViscaData.Data[addr+1]>>4) & 0x0f);		break;
			case VDX_MASK_X_POS :		ret = g_ViscaData.Data[addr+2];						break;
			case VDX_MASK_Y_POS :		ret = g_ViscaData.Data[addr+3];						break;
			case VDX_MASK_WIDTH :		ret = g_ViscaData.Data[addr+4];						break;
			case VDX_MASK_HEIGHT :		ret = g_ViscaData.Data[addr+5];						break;
			case VDX_MASK_P :			ret = g_ViscaData.Data[addr+6];
										ret = (ret<<8) | g_ViscaData.Data[addr+7];		break;
			case VDX_MASK_T :			ret = g_ViscaData.Data[addr+8];
										ret = (ret<<8) | g_ViscaData.Data[addr+9];		break;
			case VDX_MASK_Z :			ret = g_ViscaData.Data[addr+10];
										ret = (ret<<8) | g_ViscaData.Data[addr+11];		break;
		}
	}
	else
	{
		ret = 0;
		switch(idx)
		{
			case VDX_MASK_ON :			g_ViscaData.Data[addr] = (g_ViscaData.Data[addr  ] & 0xFE) | (val & 0x01);		break;
			case VDX_MASK_DISP :		g_ViscaData.Data[addr] = (g_ViscaData.Data[addr  ] & 0xFD) | ((val & 0x01)<<1);	break;
			case VDX_MASK_I :			g_ViscaData.Data[addr] = (g_ViscaData.Data[addr  ] & 0xDF) | ((val & 0x01)<<5);	break;
			case VDX_MASK_TRANS : 		g_ViscaData.Data[addr] = (g_ViscaData.Data[addr  ] & 0xBF) | ((val & 0x01)<<6);	break;
			case VDX_MASK_MOSAIC : 		g_ViscaData.Data[addr] = (g_ViscaData.Data[addr  ] & 0x7F) | ((val & 0x01)<<7);	break;
			case VDX_MASK_COLOR_ON :	g_ViscaData.Data[addr+1] = (g_ViscaData.Data[addr+1] & 0xF0) | (val & 0x0F);		break;
			case VDX_MASK_COLOR_OFF :	g_ViscaData.Data[addr+1] = (g_ViscaData.Data[addr+1] & 0x0F) | ((val & 0x0F)<<4);	break;
			case VDX_MASK_X_POS :		g_ViscaData.Data[addr+2] = val;						break;
			case VDX_MASK_Y_POS :		g_ViscaData.Data[addr+3] = val;						break;
			case VDX_MASK_WIDTH :		g_ViscaData.Data[addr+4] = val;						break;
			case VDX_MASK_HEIGHT :		g_ViscaData.Data[addr+5] = val;						break;
			case VDX_MASK_P :			g_ViscaData.Data[addr+6] = (val>>8)&0xff;
										g_ViscaData.Data[addr+7] = val&0xff;
										break;
			case VDX_MASK_T :			g_ViscaData.Data[addr+8] = (val>>8)&0xff;
										g_ViscaData.Data[addr+9] = val&0xff;
										break;
			case VDX_MASK_Z :			g_ViscaData.Data[addr+10] = (val>>8)&0xff;
										g_ViscaData.Data[addr+11] = val&0xff;
										break;
			default:
				ret = -1;
				break;
		}
	}

	return ret;
}
int32 IF_EEPViscaTitleUpdate(IFEVT evt, uint08 zone, EEP_IDX idx, int32 val)
{
	int32 ret = -1, addr = 0x33;

	addr = 0x33 + (zone * 22);

	if(evt == IFEVT_GETVAL)
	{
		switch(idx)
		{
			case VDX_TITLE_H_POS:	ret = (g_ViscaData.Data[addr] & 0x1f);				break;
			case VDX_TITLE_ON:		ret = ((g_ViscaData.Data[addr] & 0x80) >> 7);		break;
			case VDX_TITLE_LINE:	ret = (g_ViscaData.Data[addr + 1] & 0xf);			break;
			case VDX_TITLE_BLINK:	ret = ((g_ViscaData.Data[addr + 1] & 0x10) >> 4);	break;
			case VDX_TITLE_COLOR:	ret = ((g_ViscaData.Data[addr + 1] & 0xe0) >> 5);	break;
			case VDX_TITLE_LINE_CH1:
			case VDX_TITLE_LINE_CH2:
			case VDX_TITLE_LINE_CH3:
			case VDX_TITLE_LINE_CH4:
			case VDX_TITLE_LINE_CH5:
			case VDX_TITLE_LINE_CH6:
			case VDX_TITLE_LINE_CH7:
			case VDX_TITLE_LINE_CH8:
			case VDX_TITLE_LINE_CH9:
			case VDX_TITLE_LINE_CH10:
			case VDX_TITLE_LINE_CH11:
			case VDX_TITLE_LINE_CH12:
			case VDX_TITLE_LINE_CH13:
			case VDX_TITLE_LINE_CH14:
			case VDX_TITLE_LINE_CH15:
			case VDX_TITLE_LINE_CH16:
			case VDX_TITLE_LINE_CH17:
			case VDX_TITLE_LINE_CH18:
			case VDX_TITLE_LINE_CH19:
			case VDX_TITLE_LINE_CH20:
				ret = (g_ViscaData.Data[addr + (2+idx - VDX_TITLE_LINE_CH1)]);// & 0x1f);
				break;
		}
	}
	else
	{
		ret = 0;

		switch(idx)
		{
			case VDX_TITLE_H_POS:	g_ViscaData.Data[addr] = (g_ViscaData.Data[addr] & 0x80) | (val & 0x1f);				break;
			case VDX_TITLE_ON:		g_ViscaData.Data[addr] = (g_ViscaData.Data[addr] & 0x1f) | ((val<<7) & 0x80);			break;
			case VDX_TITLE_LINE:	g_ViscaData.Data[addr + 1] = (g_ViscaData.Data[addr + 1] & 0xf0) | (val & 0x0f);		break;
			case VDX_TITLE_BLINK:	g_ViscaData.Data[addr + 1] = (g_ViscaData.Data[addr + 1] & 0xef) | ((val<<4) & 0x10);	break;
			case VDX_TITLE_COLOR:	g_ViscaData.Data[addr + 1] = (g_ViscaData.Data[addr + 1] & 0x1f) | ((val<<5) & 0xe0);	break;
			case VDX_TITLE_LINE_CH1:
			case VDX_TITLE_LINE_CH2:
			case VDX_TITLE_LINE_CH3:
			case VDX_TITLE_LINE_CH4:
			case VDX_TITLE_LINE_CH5:
			case VDX_TITLE_LINE_CH6:
			case VDX_TITLE_LINE_CH7:
			case VDX_TITLE_LINE_CH8:
			case VDX_TITLE_LINE_CH9:
			case VDX_TITLE_LINE_CH10:
			case VDX_TITLE_LINE_CH11:
			case VDX_TITLE_LINE_CH12:
			case VDX_TITLE_LINE_CH13:
			case VDX_TITLE_LINE_CH14:
			case VDX_TITLE_LINE_CH15:
			case VDX_TITLE_LINE_CH16:
			case VDX_TITLE_LINE_CH17:
			case VDX_TITLE_LINE_CH18:
			case VDX_TITLE_LINE_CH19:
			case VDX_TITLE_LINE_CH20:
				g_ViscaData.Data[addr + (2 + idx - VDX_TITLE_LINE_CH1)] = (uint08)val;
				break;
			default:
				ret = -1;
				break;
		}
	}

	return ret;
}


/* OSD */
OSD_MAP * FindParant(OSD_MAP *pMap, uint08 *cursor)
{
	uint08 i = 0, j = 0;

	OSD_MAP *pParant = OSD_NULL;

	while(pParant == OSD_NULL)
	{
		if(pMap[i].name == OSD_STR_GAMMA)
		{
			int a = 0;
			a=1;
		}

		if(pMap[i].name == OSD_STR_FINISH)
		{
			return OSD_NULL;
		}

		if(pMap[i].pdep == gpCurMap)
		{
			*cursor = i;
			pParant = pMap;
		}
		else
		{
			if(pMap[i].pdep != OSD_NULL)
			{
				pParant = FindParant((OSD_MAP *)pMap[i].pdep, cursor);
			}

			if(pMap[i].pitem != OSD_NULL)
			{
				j = 0;

				while(pParant == OSD_NULL)
				{

					if(pMap[i].pitem[j].name == OSD_STR_FINISH)
//					if(pMap[i].eepmax == j)
					{
						break;//return OSD_NULL;
					}

					if(pMap[i].pitem[j].pdep == gpCurMap)
					{
						*cursor = i;
						pParant = pMap;
					}
					else if(pMap[i].pitem[j].pdep != OSD_NULL)
					{
						pParant = FindParant((OSD_MAP *)pMap[i].pitem[j].pdep, cursor);
					}

					j++;
				}
			}
		}

		i++;
	}

	return (OSD_MAP *)pParant;
}


uint32 FindItemEnd(OSD_MAP *pMap, uint08 cursor)
{
	uint32 i = 0;

	if(pMap[cursor].pitem == OSD_NULL)
	{
		i = pMap[cursor].eepmax;
	}
	else
	{
		for(i = 0; pMap[cursor].pitem[i].name != OSD_STR_FINISH; i++);
		i--;
	}

	return i;
}


void MotionValChange(OSD_KEY key)
{
	uint32 i = 0;
	uint32 val = 0, maxval = 0;

	if(gpCurMap[gCursor].eep == IDX_MD_ZONE)
	{
		val = MOTION_ZONE;
		maxval = 3;
	}
	else
	{
		val = IF_EEPMotionUpdate(IFEVT_GETVAL, MOTION_ZONE, gpCurMap[gCursor].eep, 0);

		if(gpCurMap[gCursor].pitem != OSD_NULL)
		{
			for(maxval = 0; gpCurMap[gCursor].pitem[maxval].name != OSD_STR_FINISH; maxval++);
			maxval--;
		}
		else
		{
			maxval = gpCurMap[gCursor].eepmax;
		}
	}

	if(key == OSD_LKEYDOWN)
	{
		if(val == 0)
		{
			val = maxval;
		}
		else
		{
			--val;
		}
	}
	else if(key == OSD_RKEYDOWN)
	{
		if(val == maxval)
		{
			val = 0;
		}
		else
		{
			++val;
		}
	}

	if(gpCurMap[gCursor].eep == IDX_MD_ZONE)
	{
		MOTION_ZONE = (uint08)val;

		for(i = 0; gpCurMap[i].name != OSD_STR_FINISH; i++)
		{
			PrintItem((uint08)i, &gpCurMap[i]);
		}
	}
	else
	{
		IF_EEPMotionUpdate(IFEVT_SETVAL, MOTION_ZONE, gpCurMap[gCursor].eep, val);
		PrintItem(gCursor, &gpCurMap[gCursor]);
	}
}

void PrivacyValChange(OSD_KEY key)
{
	uint32 i = 0;
	uint32 val = 0, maxval = 0;

	if(gpCurMap[gCursor].eep == IDX_PRI_ZONE)
	{
		val = PRIVACY_ZONE;
		maxval = 7;
	}
	else
	{
		val = IF_EEPPrivacyUpdate(IFEVT_GETVAL, PRIVACY_ZONE, gpCurMap[gCursor].eep, 0);

		if(gpCurMap[gCursor].pitem != OSD_NULL)
		{
			for(maxval = 0; gpCurMap[gCursor].pitem[maxval].name != OSD_STR_FINISH; maxval++);
			maxval--;
		}
		else
		{
			maxval = gpCurMap[gCursor].eepmax;
		}
	}

	if(key == OSD_LKEYDOWN)
	{
		if(val == 0)
		{
			val = maxval;
		}
		else
		{
			--val;
		}
	}
	else if(key == OSD_RKEYDOWN)
	{
		if(val == maxval)
		{
			val = 0;
		}
		else
		{
			++val;
		}
	}

	if(gpCurMap[gCursor].eep == IDX_PRI_ZONE)
	{
		PRIVACY_ZONE = (uint08)val;

		for(i = 0; gpCurMap[i].name != OSD_STR_FINISH; i++)
		{
			PrintItem((uint08)i, &gpCurMap[i]);
		}
	}
	else
	{
		IF_EEPPrivacyUpdate(IFEVT_SETVAL, PRIVACY_ZONE, gpCurMap[gCursor].eep, val);
		PrintItem(gCursor, &gpCurMap[gCursor]);
	}
}



uint32 __strlen(uint08 *str)
{
	int32 i = 0;

	while(*str++ != '\0')
		i++;

	return i;
}

uint32 __itoa(uint08 x, uint08 y, uint32 val)
{
	uint32 i = 0;
	uint32 sign = 0;
	uint08 buf[16], *ptr;

	ptr = buf;

	// zero then return
	if(val)
	{
		// make string in reverse form
		if(val < 0)
		{
			val = ~val + 1;
			sign++;
		}

		while(val)
		{
			*ptr++ = (val % 10) + OSD_ZERO;
			val = val / 10;
		}

		if(sign)
			*ptr++ = '-';

		*ptr = '\0';

		// copy reverse order
		for(i = 0; i < __strlen(buf); i++)
		{
			PrintCall(x++, y, buf[__strlen(buf) - i - 1]);
		}
	}
	else
	{
		PrintCall(x, y, OSD_ZERO);
		i++;// KSH 131016 : 0값이 표시가 안됐음
	}

	return i;
}

uint32 __xtoa(uint08 x, uint08 y, uint32 val, uint32 opt)
{
	uint32 i = 0;
	uint08 buf[16], *ptr;

	ptr = buf;

	// zero then return
	if(val)
	{
		// make string in reverse form
		while(val)
		{
			*ptr++ = (int08)((val & 0x0f) < 10 ? (val & 0x0f) + '0' : (val & 0x0f) - 10 + opt);
			val >>= 4;
		}

		*ptr = '\0';

		// copy reverse order
		for(i = 0; i < __strlen(buf); i++)
		{
			PrintCall(x++, y, buf[__strlen(buf) - i - 1]);
		}
	}
	else
	{
		PrintCall(x, y, OSD_ZERO);
		i++;// KSH 131226 : 0값이 표시가 안됐음
	}

	return i;
}


void ClearOsdMap()
{
	int x = 0, y = 0;

	for(x = 0; x < gWinSize[0]; x++)
	{
		for(y = 0; y < gWinSize[1]; y++)
		{
			PrintCall(x, y, OSD_FONTSPACE);
		}
	}
}

void ClearCursor(uint08 cursor)
{
	PrintCall(OSD_CURSOR_LEFT, OSD_CURSOR_TOP + cursor, OSD_FONTSPACE);
}


void PrintCallNull(uint08 x, uint08 y, uint32 ch)
{
	volatile uint08 tmp = 0;
	tmp = 1;
}

void PrintTitle(const uint08 *pTtitle,const uint08 *pSubTtitle)
{
	uint08 i = 0,j = 0;

	if(pTtitle != 0)
	{
		PrintCall(OSD_TITLE_LEFT, OSD_TITLE_TOP,'[');
		for(i = 1; pTtitle[i-1] != OSD_NULL; i++)
		{
			PrintCall(OSD_TITLE_LEFT + i, OSD_TITLE_TOP, pTtitle[i-1]);
		}
	}
	if(pSubTtitle != 0)
	{
		PrintCall(OSD_TITLE_LEFT + (i++), OSD_TITLE_TOP, '/');
		for(j = 0;pSubTtitle[j] != OSD_NULL;j++)
		{
			PrintCall(OSD_TITLE_LEFT + i + j, OSD_TITLE_TOP, pSubTtitle[j]);
		}
	}
	PrintCall(OSD_TITLE_LEFT + i + (j++), OSD_TITLE_TOP, ']');
	for(;i + j < 25;i++)
	{
		PrintCall(OSD_TITLE_LEFT + i + j, OSD_TITLE_TOP, OSD_FONTSPACE);
	}
}

void PrintIdTitle()
{
	uint08 i = 0;
	uint08 x = 0;
	uint08 y = 0;
	uint08 cam[] = "CAM ";

	if(gOsdState == OSD_STATEOFF)
	{
		if(g_OsdData.FLD.ID_ON == 1)
		{
			x = g_OsdData.FLD.CAMID_X_POS;
			y = g_OsdData.FLD.CAMID_Y_POS;

			for(i = 0; i < 4; i++)
			{
				PrintCall(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], cam[i]);
			}

			//__itoa(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], g_OsdData.FLD.CAM_ID);
		}

		if(g_OsdData.FLD.ID_ON == 1)
		{
			x = g_OsdData.FLD.CAMID_X_POS;
			y = g_OsdData.FLD.CAMID_Y_POS;

			for(i = 0; i < 16; i++)
			{
				PrintCall(gOsdTitlePosition[x][0] + i, gOsdTitlePosition[y][1], g_OsdData.Data[0xE5 + i]);
			}
		}
	}
}

void PrintCursor(uint08 cursor)
{
	ClearCursor(gCursor);

	gCursor = cursor;

	PrintCall(OSD_CURSOR_LEFT, OSD_CURSOR_TOP + gCursor, OSD_FONTHAND);
}

void PrintMenu(uint08 y, const uint08 *pMenu)
{
	uint08 i = 0;

	for(i = 0; pMenu[i] != OSD_NULL; i++)
	{
		PrintCall(OSD_MENU_LEFT + i, OSD_MENU_TOP + y, pMenu[i]);
	}

	for(; i < OSD_MENU_LEN; i++)
	{
		PrintCall(OSD_MENU_LEFT + i, OSD_MENU_TOP + y, OSD_FONTSPACE);
	}
}

uint32 PrintDec(uint08 x, uint08 y, uint32 val)
{
	uint32 tmp_val;
	uint08 i = 0 ,size = 0;
	uint08 buf[10] = {OSD_ZERO, OSD_NULL, };

	tmp_val = val;
	for( ; tmp_val > 0; )
	{
		tmp_val /= 10;
		size++;
	}

	for(i=1; i < size+1;i++)
	{
		buf[size-i] = OSD_ZERO + val%10;
		val /= 10;
	}

	for(i = 0; i<10; i++)
	{
		PrintCall(OSD_ITEM_LEFT + x + i, OSD_ITEM_TOP + y,  buf[i]);
	}

	return x + i;
}

uint32 PrintSlider(uint08 y, uint32 val, uint32 valmax)
{
	fp32 pos, stp;
	uint08 i = 0;
	uint08 slider[11] = {OSD_SLIDER, OSD_SLIDER, OSD_SLIDER, OSD_SLIDER, OSD_SLIDER,
						 OSD_SLIDER, OSD_SLIDER, OSD_SLIDER, OSD_SLIDER, OSD_SLIDER,
						 OSD_FONTSPACE};
	if(valmax > 0xffff)
	{
		i = (uint08)PrintDec(i, y, val);
	}
	else
	{
#if SLIDER_TYPE == 4
		stp = (fp32)39 / (fp32)(valmax);

		pos = stp * val;

		slider[(uint08)(pos / 4)] = (uint08)pos % 4 + OSD_SLIDER +1;
#else
		stp = (fp32)29 / (fp32)(valmax);

		pos = stp * val;

		slider[(uint08)(pos / 3)] = (uint08)pos % 3 + 0x31;
#endif
		for(i = 0; i < 10; i++)
		{
			PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y,  slider[i]);
		}
		if(valmax < val)	PrintCall(OSD_ITEM_LEFT + i -1, OSD_ITEM_TOP + y,  OSD_SLIDER+4);
		i++;
		i = (uint08)PrintDec(i, y, val);
	}

	return i;
}

uint32 PrintMotion(uint08 y, const OSD_MAP *pMap)
{
	uint08 i = 0;
	uint32 val = 0;
	const uint08 *pName;

	if(pMap->eep == IDX_MD_ZONE)
	{
		i = (uint08)PrintDec(0, y, MOTION_ZONE + 1);
	}
	else
	{
		val = IF_EEPMotionUpdate(IFEVT_GETVAL, MOTION_ZONE, pMap->eep, 0);

		if(pMap->pitem != OSD_NULL)
		{
			pName = OSD_ENG[pMap->pitem[val].name];

			for(i = 0; pName[i] != OSD_NULL; i++)
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, pName[i]);
			}
		}
		else
		{
			i = (uint08)PrintSlider(y, val, pMap->eepmax);
		}
	}

	return i;
}

uint32 PrintPrivacy(uint08 y, const OSD_MAP *pMap)
{
	uint08 i = 0;
	uint32 val = 0;
	const uint08 *pName;

	if(pMap->eep == IDX_PRI_ZONE)
	{
		i = (uint08)PrintDec(0, y, PRIVACY_ZONE + 1);
	}
	else
	{
		val = IF_EEPPrivacyUpdate(IFEVT_GETVAL, PRIVACY_ZONE, pMap->eep, 0);

		if(pMap->pitem != OSD_NULL)
		{
			pName = OSD_ENG[pMap->pitem[val].name];

			for(i = 0; pName[i] != OSD_NULL; i++)
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, pName[i]);
			}
		}
		else
		{
			i = (uint08)PrintSlider(y, val, pMap->eepmax);
		}
	}

	return i;
}

void PrintItem(uint08 y, const OSD_MAP *pMap)
{
	uint08 i = 0;
	uint08 cnt = 0;
	uint32 val = 0;
	const uint08 *pName;

	// Motion
	if(pMap->eep > IDX_MD_STT && pMap->eep < IDX_MD_END)
	{
		i = (uint08)PrintMotion(y, pMap);
	}
	else if(pMap->eep > IDX_PRI_STT && pMap->eep < IDX_PRI_END)
	{
		i = (uint08)PrintPrivacy(y, pMap);
	}
	/* 하위메뉴가 존재하면 */
	else if(pMap->pdep != OSD_NULL)
	{
		PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTENTER);
		i++;
	}
	/* 하위메뉴가 아이템의 상태에 따라 존재하면 */
	else if(pMap->pitem != OSD_NULL)
	{
		for(cnt = 0;pMap->pitem[cnt].name != OSD_STR_FINISH;)
		{
			cnt++;	//OSD_STR_FINISH를 찾는다.
		}
		val = IF_EEPUpdate(IFEVT_GETVAL, pMap->eep, 0);
		if((val >= cnt) && (val != -1))
		{
			IF_EEPUpdate(IFEVT_SETVAL, pMap->eep, 0);;	//OSD_STR_FINISH에 위치하거나 Finish 보다 크면 '0'으로 만든다
			val = 0;
		}

		if(val != -1)
		{
			pName = OSD_ENG[pMap->pitem[val].name];

			for(i = 0; pName[i] != OSD_NULL; i++)
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, pName[i]);
			}

			if(pMap->pitem[val].pdep != 0 ||
				(pMap->eep == IDX_TITLE_ON && val == 1/*pMap->pitem[val].name == OSD_STR_ON*/) ||
			   (pMap->eep == IDX_ID_ON && val == 1/*pMap->pitem[val].name == OSD_STR_ON*/))
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTENTER);
				i++;
			}
			else if(pMap->pitem[val].name == OSD_STR_PUSH)
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTPUSH);
				i++;
			}
		}
	}
	else
	{
		if(pMap->eep > IDX_NULL && (pMap->eep < IDX_EXIT || pMap->eep > IDX_REBOOT))
		{
			if(IF_EEPUpdate(IFEVT_GETVAL, pMap->eep, 0) != -1)
			{
				if(pMap->eep == IDX_CAM_ID)
				{
					i = (uint08)PrintDec(i, y, IF_EEPUpdate(IFEVT_GETVAL, pMap->eep, 0));
				}
				else
				{
					i = (uint08)PrintSlider(y, IF_EEPUpdate(IFEVT_GETVAL, pMap->eep, 0), pMap->eepmax);
				}
			}
			else
			{
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTENTER);
				i++;
			}
		}
		/* 예외처리 */
		else
		{
			pName = OSD_NULL;

			switch(pMap->eep)
			{
				case IDX_RETURN:	pName = OSD_ENG[gReturnItem[RETURN_VAL]];	break;
				case IDX_EXIT:		pName = OSD_ENG[gExitItem[EXIT_VAL]];		break;
				case IDX_FRESET:	pName = OSD_ENG[gFResetItem[FRESET_VAL]];	break;
				case IDX_REBOOT:	pName = OSD_ENG[gRebootItem[REBOOT_VAL]];	break;
				case IDX_INITIAL:
				case IDX_TITLE:
					{
						PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTENTER);
						i++;
					}break;
			}

			if(pName != OSD_NULL)
			{
				for(i = 0; pName[i] != OSD_NULL; i++)
				{
					PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, pName[i]);
				}

				if(pName != OSD_ENG[OSD_STR_NO])
				PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTENTER);
				else
					PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTSPACE);
				i++;
			}
		}
	}

	for(; i < OSD_ITEM_LEN; i++)
	{
		PrintCall(OSD_ITEM_LEFT + i, OSD_ITEM_TOP + y, OSD_FONTSPACE);
	}
}

void PrintOsdMap(const OSD_MAP *pMap, uint08 cursor)
{
	uint08 i = 0, j = 0;
	OSD_MAP *tempMap =0;
	uint08 tempCursor;
	uint32 tmpeEepVal;
	//PrintTitle(OSD_ENG[OSD_STR_MENU]);//Title을 그리는 것은
	gpCurMap = (OSD_MAP *)pMap;

	if(pMap == gpOsdMap)			PrintTitle(OSD_ENG[OSD_STR_MENU],OSD_NULL);
	else if(pMap == gpOsdHiddenMap)	PrintTitle(OSD_ENG[OSD_STR_MENU],OSD_NULL);
	else
	{
		if(gOsdState == OSD_STATEON)
		{
			tempMap = FindParant((OSD_MAP *)gpOsdMap, &tempCursor);
		}
		else if(gOsdState == OSD_STATEHIDDEN)
		{
			tempMap = FindParant((OSD_MAP *)gpOsdHiddenMap, &tempCursor);
		}

		if(tempMap[tempCursor].pitem != 0)
		{
			tmpeEepVal = IF_EEPUpdate(IFEVT_GETVAL, tempMap[tempCursor].eep, 0);

			if(tempMap[tempCursor].pitem[tmpeEepVal].name == OSD_STR_ON)
				PrintTitle(OSD_ENG[tempMap[tempCursor].name],OSD_NULL);
			else
				PrintTitle(OSD_ENG[tempMap[tempCursor].name] , OSD_ENG[tempMap[tempCursor].pitem[tmpeEepVal].name]);
		}
		else
		{
			PrintTitle(OSD_ENG[tempMap[tempCursor].name],OSD_NULL);
		}
	}

	PrintCursor(cursor);

	for(i = 0; pMap[i].name != OSD_STR_FINISH; i++)
	{
		PrintMenu(i, OSD_ENG[pMap[i].name]);
		PrintItem(i, &pMap[i]);
	}

	gLineLimit = i - 1;

	for(; i < OSD_HEIGHT; i++)
	{
		for(j = 0; j < (OSD_MENU_LEN + OSD_ITEM_LEN); j++)
		{
			PrintCall(OSD_MENU_LEFT + j, OSD_MENU_TOP + i, OSD_FONTSPACE);
		}
	}
}


void OsdReprint()
{
	uint08 i = 0;

	// 아이템 부분만 다시 그리면 됨
//	PrintOsdMap(gpCurMap, gCursor);
	for(i = 0; gpCurMap[i].name != OSD_STR_FINISH; i++)
	{
		PrintItem(i, &gpCurMap[i]);
	}
}


IFER OsdOff2On()
{
	IFER er = IF_ERNO;

	gKeyCnt = 0;
	gOsdState = OSD_STATEON;

	FRESET_VAL = 0;
	REBOOT_VAL = 0;
	RETURN_VAL = 0;
	EXIT_VAL = 0;

	ClearOsdMap();
	PrintOsdMap(gpOsdMap, 0);

	key_tmp = OSD_KEYNULL;
	er = SendEvent(IFEVT_OSD, IDX_OSDON, &key_tmp);

	return er;
}

IFER OsdIOn2Off()
{
	IFER er = IF_ERNO;

	gCursor = 0;
	gKeyCnt = 0;
	gpCurMap = OSD_NULL;
	gOsdState = OSD_STATEOFF;

	ClearOsdMap();
//	PrintIdTitle();

	key_tmp = OSD_KEYNULL;
	er = SendEvent(IFEVT_OSD, IDX_OSDOFF, &key_tmp);

	return er;
}

IFER OsdIdDispMode(OSD_KEY key)
{
	IFER er = IF_ERNOPROC;
	uint08 i = 0;
	uint08 x = g_OsdData.FLD.CAMID_X_POS;
	uint08 y = g_OsdData.FLD.CAMID_Y_POS;
	uint08 cam[] = "CAM ";

	if(g_OsdData.FLD.ID_ON == 0)
	{
		return er;
	}

	if(gOsdMode != OSD_ID_DISP)
	{
		if(x > 1)
		{
			g_OsdData.FLD.CAMID_X_POS = 0;
			x = 0;
		}

		if(y > 1)
		{
			g_OsdData.FLD.CAMID_Y_POS = 0;
			y = 0;
		}

		ClearOsdMap();

		for(i = 0; i < 4; i++)
		{
			PrintCall(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], cam[i]);
		}

		__itoa(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], g_OsdData.FLD.CAM_ID);

		gOsdMode = OSD_ID_DISP;
		er = IF_ERNO;
	}
	else
	{
		er = IF_ERNO;

		switch(key)
		{
			case OSD_CKEYDOWN:
				{
					ClearOsdMap();
					PrintOsdMap(gpCurMap, gCursor);
					gOsdMode = OSD_NORMAL;
					return er;
				}break;
			case OSD_LKEYDOWN:	x = (x == 0 ? 1 : 0);	break;
			case OSD_RKEYDOWN:	x = (x == 0 ? 1 : 0);	break;
			case OSD_UKEYDOWN:	y = (y == 0 ? 1 : 0);	break;
			case OSD_DKEYDOWN:	y = (y == 0 ? 1 : 0);	break;

			default:
				return IF_ERNOPROC;
				break;
		}

		for(i = 0; i < 7; i++)
		{
			PrintCall(gOsdIdPosition[g_OsdData.FLD.CAMID_X_POS][0] + i, gOsdIdPosition[g_OsdData.FLD.CAMID_Y_POS][1], OSD_FONTSPACE);
		}

		for(i = 0; i < 4; i++)
		{
			PrintCall(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], cam[i]);
		}

		__itoa(gOsdIdPosition[x][0] + i, gOsdIdPosition[y][1], g_OsdData.FLD.CAM_ID);

		g_OsdData.FLD.CAMID_X_POS = x;
		g_OsdData.FLD.CAMID_Y_POS = y;
	}

	return er;
}

IFER OsdTitleDispMode(OSD_KEY key)
{
	IFER er = IF_ERNOPROC;
	uint08 i = 0;
	uint08 x = g_OsdData.FLD.TITLE_X_POS;
	uint08 y = g_OsdData.FLD.TITLE_Y_POS;

	if(g_OsdData.FLD.TITLE_ON == 0)
	{
		return er;
	}

	if(gOsdMode != OSD_TITLE_DISP)
	{
		if(x > 1)
		{
			g_OsdData.FLD.TITLE_X_POS = 0;
			x = 0;
		}

		if(y > 1)
		{
			g_OsdData.FLD.TITLE_Y_POS = 0;
			y = 0;
		}

		ClearOsdMap();

		for(i = 0; i < 16; i++)
		{
			PrintCall(gOsdTitlePosition[x][0] + i, gOsdTitlePosition[y][1], g_OsdData.Data[0xE5 + i]);
		}

		gOsdMode = OSD_TITLE_DISP;
		er = IF_ERNO;
	}
	else
	{
		er = IF_ERNO;

		switch(key)
		{
			case OSD_CKEYDOWN:
				{
					ClearOsdMap();
					PrintOsdMap(gpCurMap, gCursor);
					gOsdMode = OSD_NORMAL;
					return er;
				}break;
			case OSD_LKEYDOWN:	x = (x == 0 ? 1 : 0);	break;
			case OSD_RKEYDOWN:	x = (x == 0 ? 1 : 0);	break;
			case OSD_UKEYDOWN:	y = (y == 0 ? 1 : 0);	break;
			case OSD_DKEYDOWN:	y = (y == 0 ? 1 : 0);	break;

			default:
				return IF_ERNOPROC;
				break;
		}

		for(i = 0; i < 16; i++)
		{
			PrintCall(gOsdTitlePosition[g_OsdData.FLD.TITLE_X_POS][0] + i, gOsdTitlePosition[g_OsdData.FLD.TITLE_Y_POS][1], OSD_FONTSPACE);
		}

		for(i = 0; i < 16; i++)
		{
			PrintCall(gOsdTitlePosition[x][0] + i, gOsdTitlePosition[y][1], g_OsdData.Data[0xA0 + i]);
		}

		g_OsdData.FLD.TITLE_X_POS = x;
		g_OsdData.FLD.TITLE_Y_POS = y;
	}

	return er;
}

IFER OsdTitleMode(OSD_KEY key)
{
	IFER er = IF_ERNOPROC;
	uint08 i = 0;
	uint08 x = (OSD_MENU_LEN + OSD_ITEM_LEN - 21) / 2;
	uint08 y = OSD_HEIGHT / 2;
	uint08 val = 0x20, pos = 0;
	pos = 1;

	if(gOsdMode != OSD_TITLE)
	{
		ClearOsdMap();

		for(i = 0; i < 16; i++)
		{
			if((g_OsdData.Data[0xE5 + i] >= OSD_ZERO && g_OsdData.Data[0xE5 + i] <= 0x39)
				|| (g_OsdData.Data[0xE5 + i] >= 0x41 && g_OsdData.Data[0xA0 + i] <= 0x5A))
			{
				PrintCall(x + i, y, g_OsdData.Data[0xA0 + i]);
			}
			else
			{
				g_OsdData.Data[0xA0 + i] = OSD_FONTSPACE;
				PrintCall(x + i, y, OSD_FONTULINE);
			}
		}

		for(i = 0; OSD_ENG[OSD_STR_EXIT][i] != OSD_NULL; i++)
		{
			PrintCall(x + 17 + i, y, OSD_ENG[OSD_STR_EXIT][i]);
		}

		PrintCall(x, y + 1, OSD_ARROWUP);

		gTitleCursor = 0;
		gOsdMode = OSD_TITLE;
		er = IF_ERNO;
	}
	else
	{
		er = IF_ERNO;

		switch(key)
		{
			case OSD_CKEYDOWN:
				{
					if(gTitleCursor == 17)
					{
						ClearOsdMap();
						PrintOsdMap(gpCurMap, gCursor);
						gOsdMode = OSD_NORMAL;
					}
				}break;
			case OSD_LKEYDOWN:
			case OSD_RKEYDOWN:
				{
					PrintCall(x + gTitleCursor, y + 1, OSD_FONTSPACE);
					if(key == OSD_LKEYDOWN)
					{
						if(gTitleCursor == 0)
						{
							gTitleCursor = 17;
						}
						else if(gTitleCursor == 17)
						{
							gTitleCursor = 15;
						}
						else (--gTitleCursor);
						//gTitleCursor = ((gTitleCursor == 0) ? 17 : ((gTitleCursor == 17) ? 15 : (--gTitleCursor)));
					}
					else
					{
						if(gTitleCursor == 17)
						{
							gTitleCursor = 0;
						}
						else if(gTitleCursor == 15)
						{
							gTitleCursor = 17;
						}
						else (++gTitleCursor);
						//gTitleCursor = ((gTitleCursor == 17) ? 0 : ((gTitleCursor == 15) ? 17 : (++gTitleCursor)));
					}
					PrintCall(x + gTitleCursor, y + 1, OSD_ARROWUP);
				}break;
			case OSD_UKEYDOWN:
			case OSD_DKEYDOWN:
				{
					if(gTitleCursor != 17)
					{
						val = g_OsdData.Data[0xA0 + gTitleCursor];

						for(i = 0; i < TITLEMAP_CNT; i++)
						{
							if(OsdTitleMap[i] == val)
							{
								if(key == OSD_UKEYDOWN)
								{
									val = (i == (TITLEMAP_CNT - 1) ? OsdTitleMap[0] : OsdTitleMap[++i]);
								}
								else
								{
									val = (i == 0 ? OsdTitleMap[TITLEMAP_CNT - 1] : OsdTitleMap[--i]);
								}

								break;
							}
						}

						g_OsdData.Data[0xA0 + gTitleCursor] = val;
						PrintCall(x + gTitleCursor, y, (val == OSD_FONTSPACE ? OSD_FONTULINE : val));
					}
				}break;

			default:
				return IF_ERNOPROC;
				break;
		}
	}

	return er;
}


IFER SelfProc()
{
	IFER er = IF_ERNOPROC;
	uint32 i = 0;
	uint08 cursor;
	const OSD_MAP *pMap = 0;

	switch(gpCurMap[gCursor].eep)
	{
		case IDX_FRESET:
			{
				if(FRESET_VAL == 1)
				{
					key_tmp = OSD_KEYNULL;
					er = SendEvent(IFEVT_OSD, IDX_FRESET, &key_tmp);
				}
			}break;
		case IDX_REBOOT:
			key_tmp = OSD_KEYNULL;
			er = SendEvent(IFEVT_OSD, (REBOOT_VAL == 0 ? IDX_CAMREBOOTSAVE : IDX_CAMREBOOTNOTSAVE), &key_tmp);
			break;
		case IDX_INITIAL:
			{
				for(i = 0; gpCurMap[i].name != OSD_STR_FINISH; i++)
				{
					if((gpCurMap[i].eep > IDX_MD_STT && gpCurMap[i].eep < IDX_MD_END) || (gpCurMap[i].eep > IDX_PRI_STT && gpCurMap[i].eep < IDX_PRI_END))
					{
							key_tmp = OSD_KEYNULL;
							er = SendEvent(IFEVT_INITIAL, gpCurMap[i].eep, &key_tmp);
						}
					else if(gpCurMap[i].eep > IDX_NULL)
					{
						if(IF_EEPUpdate(IFEVT_GETVAL, gpCurMap[i].eep, 0) != -1)
					{
						key_tmp = OSD_KEYNULL;
						er = SendEvent(IFEVT_INITIAL, gpCurMap[i].eep, &key_tmp);
						}
					}

				}

				OsdReprint();
			}break;
		case IDX_RETURN:
			{
				if(RETURN_VAL == 0)
				{
					if(gOsdState == OSD_STATEON)
						pMap = FindParant((OSD_MAP *)gpOsdMap, &cursor);
					else if(gOsdState == OSD_STATEHIDDEN)
						pMap = FindParant((OSD_MAP *)gpOsdHiddenMap, &cursor);
					if(pMap != OSD_NULL)
					{
						PrintOsdMap(pMap, cursor);

						er = IF_ERNO;
					}
				}
				else if(RETURN_VAL == 1)
				{
					key_tmp = OSD_KEYNULL;
					er = SendEvent(IFEVT_OSD, IDX_OSDEXITSAVE, &key_tmp);
					er = OsdIOn2Off();
				}
				else if(RETURN_VAL == 2)
				{
					key_tmp = OSD_KEYNULL;
					er = SendEvent(IFEVT_OSD, IDX_OSDEXITNOTSAVE, &key_tmp);
					er = OsdIOn2Off();
				}
			}break;
		case IDX_EXIT:
			{
//				if(gpCurMap == OSD_gMap/* || gpCurMap == OSD_gHiddenMap*/)
				{
					key_tmp = OSD_KEYNULL;
					er = SendEvent(IFEVT_OSD, (EXIT_VAL == 0 ? IDX_OSDEXITSAVE : IDX_OSDEXITNOTSAVE), &key_tmp);
					er = OsdIOn2Off();
				}
			}break;
		case IDX_TITLE:		er = OsdTitleMode(OSD_KEYNULL);			break;
		case IDX_TITLE_ON:	er = OsdTitleDispMode(OSD_KEYNULL);		break;
		case IDX_ID_ON:		er = OsdIdDispMode(OSD_KEYNULL);		break;
	}

	return er;
}

IFER OsdOn()
{
	IFER er = IF_ERNOPROC;
	uint32 val = 0;
	const OSD_MAP *pMap;

	/* 하위 메뉴가 존재하는 경우 */
	if(gpCurMap[gCursor].pdep != OSD_NULL)
	{
		PrintOsdMap(gpCurMap[gCursor].pdep, 0);
		er = IF_ERNO;
	}
	else if(gpCurMap[gCursor].pitem != OSD_NULL)
	{
		val = IF_EEPUpdate(IFEVT_GETVAL, gpCurMap[gCursor].eep, 0);

		if(val != -1)
		{
			pMap = gpCurMap[gCursor].pitem[val].pdep;

			/* 아이템에 따라 하위 메뉴가 존재할 수도 있다 */
			if(pMap != OSD_NULL)
			{
				PrintOsdMap(pMap, 0);
				er = IF_ERNO;
			}
		}
	}

	/* 별다른 액션이 없는 경우 해당 메뉴의 타입(예외처리) 분석 */
	if(er == IF_ERNOPROC)
	{
//		if(IF_EEPUpdate(IFEVT_GETVAL, gpCurMap[gCursor].eep, 0) == -1)
		{
			er = SelfProc();
		}
	}

	return er;
}


IFER CKeyFunc()
{
	IFER er = IF_ERNO;

	if(gOsdState == OSD_STATEOFF)
	{
		if(gKeyPrev == OSD_KEYNULL || gKeyPrev == OSD_CKEYDOWN)
		{
			gKeyCnt++;
		}
		else
		{
			gKeyCnt = 0;
		}

		if(gKeyCnt == OSD_STATEON_DELAY)
		{
			er = OsdOff2On();
		}
	}
	else if(gOsdState == OSD_STATEON || gOsdState == OSD_STATEHIDDEN)
	{
		er = OsdOn();
	}

	return er;
}

IFER UKeyFunc()
{
	uint08 cursor = gCursor;

	if(gOsdState != OSD_STATEOFF)
	{
		if(cursor == 0)
		{
			cursor = gLineLimit;
		}
		else
		{
			cursor--;
		}

		if(gpCurMap[cursor].name == OSD_STR_NULL)
		{
			if(cursor == 0)
			{
				cursor = gLineLimit;
			}
			else
			{
				cursor--;
			}
		}
		PrintCursor(cursor);
	}

	return IF_ERNO;
}

IFER DKeyFunc()
{
	uint08 cursor = gCursor;

	if(gOsdState != OSD_STATEOFF)
	{
		if(cursor == gLineLimit)
		{
			cursor = 0;
		}
		else
		{
			cursor++;
		}
		if(gpCurMap[cursor].name == OSD_STR_NULL)
		{
			if(cursor == gLineLimit)
			{
				cursor = 0;
			}
			else
			{
				cursor++;
			}
		}

		PrintCursor(cursor);
	}

	return IF_ERNO;
}

IFER LKeyFunc()
{
	IFER er = IF_ERNO;
	uint32 val = 0, maxval = 0;

	if(gOsdState != OSD_STATEOFF)
	{
		// Motion
		if(gpCurMap[gCursor].eep > IDX_MD_STT && gpCurMap[gCursor].eep < IDX_MD_END)
		{
			 MotionValChange(OSD_LKEYDOWN);
		}
		else if(gpCurMap[gCursor].eep > IDX_PRI_STT && gpCurMap[gCursor].eep < IDX_PRI_END)
		{
			PrivacyValChange(OSD_LKEYDOWN);
		}
		else
		{
			val = IF_EEPUpdate(IFEVT_GETVAL, gpCurMap[gCursor].eep, 0);

			if(val != -1)
			{
				maxval = FindItemEnd(gpCurMap, gCursor);

				if(val == 0)
				{
					val = maxval;
				}
				else
				{
					--val;
				}

				IF_EEPUpdate(IFEVT_SETVAL, gpCurMap[gCursor].eep, val);
				PrintItem(gCursor, &gpCurMap[gCursor]);
			}
			else if(gpCurMap[gCursor].eep == IDX_RETURN || gpCurMap[gCursor].eep == IDX_EXIT ||
					gpCurMap[gCursor].eep == IDX_FRESET || gpCurMap[gCursor].eep == IDX_REBOOT)
			{
				switch(gpCurMap[gCursor].eep)
				{
					case IDX_RETURN:	RETURN_VAL = RETURN_VAL == 0 ? 2 : RETURN_VAL - 1;	break;
					case IDX_EXIT:		EXIT_VAL = EXIT_VAL == 0 ? 1 : EXIT_VAL - 1;		break;
					case IDX_FRESET:	FRESET_VAL = FRESET_VAL == 0 ? 1 : FRESET_VAL - 1;	break;
					case IDX_REBOOT:	REBOOT_VAL = REBOOT_VAL == 0 ? 1 : REBOOT_VAL - 1;	break;
				}

				PrintItem(gCursor, &gpCurMap[gCursor]);
			}
		}
	}

	return er;
}

IFER RKeyFunc()
{
	IFER er = IF_ERNO;
	uint32 val = 0, maxval = 0;

	if(gOsdState != OSD_STATEOFF)
	{
		// Motion
		if(gpCurMap[gCursor].eep > IDX_MD_STT && gpCurMap[gCursor].eep <= IDX_MD_END)
		{
			MotionValChange(OSD_RKEYDOWN);
		}
		else if(gpCurMap[gCursor].eep > IDX_PRI_STT && gpCurMap[gCursor].eep < IDX_PRI_END)
		{
			PrivacyValChange(OSD_RKEYDOWN);
		}
		else
		{
			val = IF_EEPUpdate(IFEVT_GETVAL, gpCurMap[gCursor].eep, 0);

			if(val != -1)
			{
				maxval = FindItemEnd(gpCurMap, gCursor);

				if(val == maxval)
				{
					val = 0;
				}
				else
				{
					++val;
				}

				IF_EEPUpdate(IFEVT_SETVAL, gpCurMap[gCursor].eep, val);
				PrintItem(gCursor, &gpCurMap[gCursor]);
			}
			else if(gpCurMap[gCursor].eep == IDX_RETURN || gpCurMap[gCursor].eep == IDX_EXIT ||
					gpCurMap[gCursor].eep == IDX_FRESET || gpCurMap[gCursor].eep == IDX_REBOOT)
			{
				switch(gpCurMap[gCursor].eep)
				{
					case IDX_RETURN:	RETURN_VAL = RETURN_VAL == 2 ? 0 : RETURN_VAL + 1;	break;
					case IDX_EXIT:		EXIT_VAL = EXIT_VAL == 1 ? 0 : EXIT_VAL + 1;		break;
					case IDX_FRESET:	FRESET_VAL = FRESET_VAL == 1 ? 0 : FRESET_VAL + 1;	break;
					case IDX_REBOOT:	REBOOT_VAL = REBOOT_VAL == 1 ? 0 : REBOOT_VAL + 1;	break;
				}

				PrintItem(gCursor, &gpCurMap[gCursor]);
			}
		}
	}

	return er;
}


IFER OsdTask(uint32 key)
{
	IFER er = IF_ERNO;
	EEP_IDX tempEep = 0;
	OSD_MAP *ptempMap = gpCurMap;

	if(gOsdMode == OSD_TITLE)
	{
		er = OsdTitleMode(key);
	}
	else if(gOsdMode == OSD_TITLE_DISP)
	{
		er = OsdTitleDispMode(key);
	}
	else if(gOsdMode == OSD_ID_DISP)
	{
		er = OsdIdDispMode(key);
	}
	else if(gOsdMode == OSD_HIDE)
	{

	}
	else
	{
		if(gpCurMap != OSD_NULL)
		{
			tempEep = gpCurMap[gCursor].eep;
			ptempMap = gpCurMap;
		}

		switch(key)
		{
/*			case OSD_KEYNULL:	break;
			case OSD_CKEYUP:	break;
			case OSD_LKEYUP:	break;
			case OSD_RKEYUP:	break;
			case OSD_UKEYUP:	break;
			case OSD_DKEYUP:	break;*/

			case OSD_CKEYDOWN:	er = CKeyFunc();	break;
			case OSD_LKEYDOWN:	er = LKeyFunc();	break;
			case OSD_RKEYDOWN:	er = RKeyFunc();	break;
			case OSD_UKEYDOWN:	er = UKeyFunc();	break;
			case OSD_DKEYDOWN:	er = DKeyFunc();	break;

			default:
				return IF_ERNOPROC;
				break;
		}

		if(key == OSD_CKEYDOWN)
		{
			if(ptempMap != OSD_NULL && tempEep != IDX_NULL)
			{
				er = SendEvent(IFEVT_OSD, tempEep, &key);
			}
		}

		if(key == OSD_LKEYDOWN || key == OSD_RKEYDOWN)
		{
			if(gpCurMap != OSD_NULL && gpCurMap[gCursor].eep != IDX_NULL)
			{
				er = SendEvent(IFEVT_OSD, gpCurMap[gCursor].eep, &key);
			}
		}
	}

#ifdef WIN32
	if(er == IF_ERNO)
		Osd_Update_Flg(1);
#endif

	return er;
}

/*************************************************************************************************************
* Protocol
*************************************************************************************************************/
/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	프로토콜 버퍼 클리어
*************************************************************************************************************/
void PtcBufClear()
{
	uint16 i;

	for(i = 0; i < MAX_PTCBUF; i++)
	{
		gPtcBuf.data[i] = 0x00;
	}

	gPtcCursor = 0;
}

/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Mem_Save(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;

	uint08 tmp;
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_MEM_SAVE_ADDR:
				if(*data > 0x07)
					err = IF_SYNTEX;
			break;

			case VDX_MEM_SAVE_DAT:
				if(*data > 0xffff)
					err = IF_SYNTEX;
			break;
		}
	}
	else if(evt == IFEVT_GETVAL)
	{
		switch(idx)
		{
			case VDX_MEM_SAVE_DAT:
				if(*data > 0x07)
					return IF_SYNTEX;
				tmp = *data;
				*data = g_ViscaUser.Data[tmp<<1];
				*data |= g_ViscaUser.Data[(tmp<<1)+1]<<8;
			break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_MEM_SAVE_ADDR:
				Mem_Add = *data;
			break;
			case VDX_MEM_SAVE_DAT:
				g_ViscaUser.Data[Mem_Add<<1]     = (*data)&0xff;
				g_ViscaUser.Data[(Mem_Add<<1)+1] = (*data>>8)&0xff;
			break;
		}
	}

	//DebugPrintf("Add Print\n%X\n",g_ViscaUser.Data[Mem_Add<<1]|(g_ViscaUser.Data[(Mem_Add<<1)+1]<<8));

	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Reg_Set(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	static uint08 add = 0;
	if(evt == IFEVT_VISCA_CMD)
	{
		if(idx == VDX_VSC_REG_ADDR)
		{
			if(*data > 0x7F)
				err = IF_SYNTEX;
		}
		else if(idx == VDX_VSC_REG_DAT)
		{
			switch(add)
			{
				case 0x00:	if(*data > 3)		{	err = IF_SYNTEX;	}		break;
				case 0x50:	if(*data > 0xFF)	{	err = IF_SYNTEX;	}		break;
				case 0x51:	if(*data > 0xFF)	{	err = IF_SYNTEX;	}		break;
				case 0x52:	if(*data > 0xEB)	{	err = IF_SYNTEX;	}		break;
				case 0x53:	if(*data > 0x1)		{	err = IF_SYNTEX;	}		break;
				case 0x54:	if(*data > 0x1)		{	err = IF_SYNTEX;	}		break;
				case 0x55:	if(*data > 0xFF)	{	err = IF_SYNTEX;	}		break;
				case 0x5F:	if(*data > 0x0F)	{	err = IF_SYNTEX;	}		break;
				case 0x72:
#if VISCA_COMPILE == VSC_TYPE_EH6300
					if(*data > 0x14 || *data == 0)
					{
						return IF_SYNTEX;
					}
#else
					if(*data > 0x14 || *data == 0)
					{
						return IF_SYNTEX;
					}
					else if(*data == 0x02 || *data == 0x07 || *data == 0x0A || *data == 0x0B)
					{
						return IF_SYNTEX;
					}
					else if(*data == 0x0F || *data == 0x10 || *data == 0x12)
					{
						return IF_SYNTEX;
					}
#endif
				case 0x73:	if(*data > 0x03 || *data == 0)	{	err = IF_SYNTEX;	}		break;
				case 0x74:	if(*data > 0x01)	{	err = IF_SYNTEX;	} 		break;
				default:	err = IF_SYNTEX;	break;
			}
		}
	}
	else if(evt == IFEVT_SETVAL)
	{
		if(idx == VDX_VSC_REG_ADDR)
		{
			if(*data > 0x7F)
				return IF_SYNTEX;
			else
				add = *data;
		}
		else if(idx == VDX_VSC_REG_DAT)
		{
			switch(add)
			{
				case 0x00:	g_ViscaData.FLD.COMM_BAUDRATE = *data;		break;
				case 0x50:	g_ViscaData.FLD.ZWIDE_LIMIT = *data;		break;
				case 0x51:	g_ViscaData.FLD.ZTELE_LIMIT = *data;		break;
				case 0x52:	g_ViscaData.FLD.DZ_MAX = *data;				break;
				case 0x53:	g_ViscaData.FLD.SZOOM_ON = *data;			break;
				case 0x54:	g_ViscaData.FLD.FTRACE_ON = *data;			break;
				case 0x55:	g_ViscaData.FLD.FCS_OFFSET_DOME = *data;	break;
				case 0x5F:
					g_ViscaData.FLD.EX_EXPC_ON = *data & 0x01;
					g_ViscaData.FLD.EX_EXPAP_ON = (*data>>1) & 0x01;
					g_ViscaData.FLD.EX_CGCH_ON = (*data>>2) & 0x01;
					g_ViscaData.FLD.EX_AICR_F2O_ON = (*data>>3) & 0x01;
				break;
				case 0x72:	g_ViscaData.FLD.MONITORING_MODE = *data;	break;
				case 0x73:
					g_ViscaData.FLD.AO_ON = *data & 0x01;
					g_ViscaData.FLD.DO_ON = *data >> 1;
				break;

				case 0x74:	g_ViscaData.FLD.LVDS_OUT = *data;			break;
			}
			*data = (add<<8)|*data;
			SendEvent(IFEVT_VISCA_CMD,VDX_REGITER_SET,data);
		}
	}
	else
	{
		switch(*data)
		{
			case 0x00:	*data = g_ViscaData.FLD.COMM_BAUDRATE;		break;
			case 0x50:	*data = g_ViscaData.FLD.ZWIDE_LIMIT;		break;
			case 0x51:	*data = g_ViscaData.FLD.ZTELE_LIMIT;		break;
			case 0x52:	*data = g_ViscaData.FLD.DZ_MAX;				break;
			case 0x53:	*data = g_ViscaData.FLD.SZOOM_ON;			break;
			case 0x54:	*data = g_ViscaData.FLD.FTRACE_ON;			break;
			case 0x55:	*data = g_ViscaData.FLD.FCS_OFFSET_DOME;	break;
			case 0x5F:
				*data = g_ViscaData.FLD.EX_EXPC_ON;
				*data |= g_ViscaData.FLD.EX_EXPAP_ON<<1;
				*data |= g_ViscaData.FLD.EX_CGCH_ON<<2;
				*data |= g_ViscaData.FLD.EX_AICR_F2O_ON<<3;
				break;
			case 0x72:	*data = g_ViscaData.FLD.MONITORING_MODE;	break;
			case 0x73:
				*data = g_ViscaData.FLD.AO_ON;
				*data |= g_ViscaData.FLD.DO_ON<<1;
			break;
			case 0x74:	*data = g_ViscaData.FLD.LVDS_OUT;			break;
			default:
				return IF_SYNTEX;
			break;
		}
	}
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Motion(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	static uint08 zone = 0;
#ifdef WIN32
	uint08 i;
#endif
	if(evt == IFEVT_GETVAL)
	{
		if(*data > 3)	return IF_SYNTEX;
		zone = *data;
		*data = 1;
	}

	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_MD_ZONE :		{	if(*data > 0x03)	err = IF_SYNTEX;	}		break;
			case VDX_MD_SRT_H_POS :	{	if(*data > 0x0F)	err = IF_SYNTEX;	}		break;
			case VDX_MD_SRT_V_POS :	{	if(*data > 0x07)	err = IF_SYNTEX;	}		break;
			case VDX_MD_STP_H_POS :	{	if(*data == 0 || *data > 0x10)	err = IF_SYNTEX;	}		break;
			case VDX_MD_STP_V_POS :	{	if(*data == 0 || *data > 0x08)	err = IF_SYNTEX;	}		break;
			default :	err = IF_SYNTEX;		break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_MD_ZONE :
				zone = *data;
				break;
			case VDX_MD_SRT_H_POS :
			case VDX_MD_SRT_V_POS :
			case VDX_MD_STP_H_POS :
			case VDX_MD_STP_V_POS :
				*data = IF_EEPViscaMdUpdate(evt,zone,idx,*data);
				break;
			default :
				err = IF_SYNTEX;
				break;
		}
	}
#ifdef WIN32
	for(i=0;i < 4 ;i++)
	{
		printf("[%03d] SH[%X]",i,IF_EEPViscaMdUpdate(IFEVT_GETVAL,i,VDX_MD_SRT_H_POS,0));
		printf(" SV[%02X]",IF_EEPViscaMdUpdate(IFEVT_GETVAL,i,VDX_MD_SRT_V_POS,0));
		printf(" EH[%02X]",IF_EEPViscaMdUpdate(IFEVT_GETVAL,i,VDX_MD_STP_H_POS,0));
		printf(" EV[%02X]",IF_EEPViscaMdUpdate(IFEVT_GETVAL,i,VDX_MD_STP_V_POS,0));
		printf("\n");
	}
	printf("FRAME[%X] ON[%X] DISP[%X] S[%X] T[%X]\n",g_ViscaData.FLD.MD_FRAME,g_ViscaData.FLD.MD_ON,g_ViscaData.FLD.MD_DISP,g_ViscaData.FLD.MD_THRS_VAL,g_ViscaData.FLD.MD_INTERVAL_TIME);
#endif
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Privacy(IFEVT evt ,EEP_IDX idx ,uint32 *data)
{
	IFER err = IF_ERNO;
	static uint08 zone = 0;
	uint16 i;
	uint32 tmps[4];
	uint08 j;
#ifdef WIN32
	uint32 tmp;
#endif
	if(evt == IFEVT_GETVAL)
	{
		if(idx == VDX_MASK_ON);
		else if(idx == VDX_CAM_PAN);
		else if(idx == VDX_CAM_TILT);
		else if(*data > 0x17)
			return IF_SYNTEX;
		else
			zone = *data;
	}
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_MASK_ON :
				for(i=0;i<4;i++)
				{
					tmps[i] = (*data>>(i<<3))&0xff;
					if(tmps[i] > 0x3f)	err = IF_SYNTEX;
				}
			break;

			case VDX_MASK_DISP :
				for(i=0;i<4;i++)
				{
					tmps[i] = (*data>>(i<<3))&0xff;
					if(tmps[i] > 0x3f)	err = IF_SYNTEX;
				}
			break;

			case VDX_MASK_I :		if(*data > 0x17)	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_ZONE :	if(*data > 0x17)	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_MODIFY :	if(*data > 0x01)	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_COLOR_ON :	if( ((*data & 0xE0) && ((*data&0x0F) > 0x0D)) || (*data == 0x7F))	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_COLOR_OFF :	if( ((*data & 0xE0) && ((*data&0x0F) > 0x0D)) || (*data == 0x7F))	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_X_POS :		if( (*data > 0x50 && *data < 0x70) || *data > 0xff)		{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_Y_POS :		if( (*data > 0x2D && *data < 0xD3) || *data > 0xff)		{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_WIDTH :		if( (*data > 0x50 && *data < 0x70) || *data > 0xff)		{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_HEIGHT :		if( (*data > 0x2D && *data < 0xD3) || *data > 0xff)		{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_P :		if(*data > 0x0FFF)	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_T :		if(*data > 0x0FFF)	{	err = IF_SYNTEX;	}		break;
			case VDX_MASK_Z :		if(*data > 0x04000)	{	err = IF_SYNTEX;	}		break;
			case VDX_CAM_PAN :		if(*data>0xfff)		{	err = IF_SYNTEX;	}		break;
			case VDX_CAM_TILT :		if(*data>0xfff)		{	err = IF_SYNTEX;	}		break;
			default:
				err = IF_SYNTEX;
			break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_MASK_ON :
				if(evt == IFEVT_SETVAL)
				{
					for(i=0;i<4;i++)
					{
						tmps[i] = (*data>>(i<<3))&0xff;
					}
					for(i=0 ; i < 4 ; i++)
					{
						for(j = 0;j<6;j++)
						{
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i*6+j,VDX_MASK_ON,(tmps[i] >> j)&0x1);
						}
					}
				}
				else
				{
					*data = 0;
					for(i=0 ; i < 0x18 ; i++)
					{
						tmps[0] = (i/6)<<3;
						tmps[0] += i%6;
						*data |= (IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_ON,0)<<(tmps[0]));
					}
				}
			break;

			case VDX_MASK_DISP :
				for(i=0;i<4;i++)
				{
					tmps[i] = (*data>>(i<<3))&0xff;
				}

				for(i=0 ; i < 4 ; i++)
				{
					for(j = 0;j<6;j++)
					{
						IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i*6+j,VDX_MASK_DISP,(tmps[i] >> j)&0x1);
					}
				}

			break;

			case VDX_MASK_I :
				IF_EEPViscaMaskUpdate(evt,*data,VDX_MASK_I,1);
				zone = *data;
			break;

			case VDX_MASK_ZONE :
				zone = *data;
			break;
			case VDX_MASK_MODIFY :
				IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_I,0);
				if(*data)
				{
					IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_P,CAM_Pan);
					IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_T,CAM_Tilt);
					IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_Z,g_ViscaData.FLD.ZOOM_POS);
				}
				else			*data = 0;//Modify
			break;

			case VDX_MASK_COLOR_ON :
				for(i=0 ; i < 0x18 ; i++)
				{
					if(IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_DISP,*data) == 0);
					else
					{
						if(*data == 0x7F)
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_MOSAIC,1);
						else if(*data & 0x10 )
						{
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_TRANS,1);
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_COLOR_ON,*data);
						}
						else
						{
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_TRANS,0);
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_COLOR_ON,*data);
						}
					}
				}
			break;
			case VDX_MASK_COLOR_OFF :
				for(i=0 ; i < 0x18 ; i++)
				{
					if(IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_DISP,*data));
					else
					{
						if(*data == 0x7F)
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_MOSAIC,1);
						else if(*data & 0x10 )
						{
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_TRANS,1);
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_COLOR_OFF,*data);
						}
						else
						{
							IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_TRANS,0);
						IF_EEPViscaMaskUpdate(IFEVT_SETVAL,i,VDX_MASK_COLOR_OFF,*data);
						}
					}
				}
			break;
			case VDX_MASK_X_POS :	IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_X_POS,*data);		break;
			case VDX_MASK_Y_POS :	IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_Y_POS,*data);		break;
			case VDX_MASK_WIDTH :	IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_WIDTH,*data);		break;
			case VDX_MASK_HEIGHT :	IF_EEPViscaMaskUpdate(IFEVT_SETVAL,zone,VDX_MASK_HEIGHT,*data);		break;
			case VDX_MASK_P :		*data = IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_P,*data);			break;
			case VDX_MASK_T :		*data = IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_T,*data);			break;
			case VDX_MASK_Z :		*data = IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_Z,*data);			break;
			case VDX_CAM_PAN :		(evt == IFEVT_SETVAL) ? (CAM_Pan = *data) : (*data = CAM_Pan);		break;
			case VDX_CAM_TILT :		(evt == IFEVT_SETVAL) ? (CAM_Tilt = *data) : (*data = CAM_Tilt);	break;
			default:				err = IF_SYNTEX;													break;
		}
	}
#ifdef WIN32

	for(i=0;i < 0x18 ;i++)
	{
		printf("[%03d]ON[%X]",i,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_ON,0));
		printf(",D[%X]"  ,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_DISP,0));
		printf(",I[%X]"  ,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_I		,0));
		printf(",T[%X]"  ,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_TRANS	,0));
		printf(",C[%X]"	 ,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_COLOR_ON,0));
		printf(",C[%X]"	 ,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_COLOR_OFF,0));
		printf(",X[%02X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_X_POS,0));
		printf(",Y[%02X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_Y_POS,0));
		printf(",W[%02X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_WIDTH,0));
		printf(",H[%02X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_HEIGHT,0));
		printf(",P[%03X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_P,0));
		printf(",T[%03X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_T,0));
		printf(",Z[%04X]",IF_EEPViscaMaskUpdate(IFEVT_GETVAL,i,VDX_MASK_Z,0));
		printf("\n");
	}
	printf("mask p[%X],t[%X]\n",CAM_Pan,CAM_Tilt);
#endif
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Mode_Change(IFEVT evt ,EEP_IDX idx ,uint32 *data)
{
	IFER err = IF_ERNO;
	//VISCA_CMD : TOGLE 시키는 함수여서 조건이 없다.
	switch(idx)
	{
		case VDX_STB_ON:
			switch(*data)
			{
				case 0x00 :
					if(g_ViscaData.FLD.STB_ON == 0)
						g_ViscaData.FLD.STB_HOLD = 1;
				break;
				case 0x02 :
					g_ViscaData.FLD.STB_ON = 0;
					g_ViscaData.FLD.STB_HOLD = 0;
				break;
				case 0x03 :
					g_ViscaData.FLD.STB_ON = 1;
					g_ViscaData.FLD.STB_HOLD = 0;
				break;
				default:
					err = IF_SYNTEX;
				break;
			}
		break;
		default:
			switch(*data)
			{
				case 0x02:
					if(idx == VDX_F_MODE)
						g_ViscaData.FLD.F_MODE = 0;
					else
						IF_EEPViscaUpdate(evt,idx,1);
					break;
				case 0x03:
					if(idx == VDX_F_MODE)
						g_ViscaData.FLD.F_MODE = 1;
					else
						IF_EEPViscaUpdate(evt,idx,0);
				break;
				case 0x10:
					if(IF_EEPViscaUpdate(IFEVT_GETVAL,idx,0) == 1)
						IF_EEPViscaUpdate(IFEVT_SETVAL,idx,0);
					else
						IF_EEPViscaUpdate(IFEVT_SETVAL,idx,1);
				break;

				default:
					err = IF_SYNTEX;
				break;
			}
		break;
	}
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Title(IFEVT evt ,EEP_IDX idx ,uint32 *data)
{
	IFER err = IF_ERNO;
	static uint08 line;
	uint32 tmp;
	uint16 i,j;
#ifdef WIN32
#endif
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_TITLE_H_POS:	if(*data > 0x1F)	{	err = IF_NOEXCUTE;	}		break;
			case VDX_TITLE_ON:
				tmp = *data>>4;
				if(tmp == 0x01)
				{
					tmp = *data&0xf;
					if(tmp > 0xA && tmp != 0xf)
						err = IF_SYNTEX;
				}
				else if(tmp == 0x02)
				{
					tmp = *data&0xf;
					if(tmp > 0xA && tmp != 0xf)
						err = IF_SYNTEX;
				}
				else if(tmp == 0x03)
				{
					tmp = *data&0xf;
					if(tmp > 0xA && tmp != 0xf)
						err = IF_SYNTEX;
				}
				else	err = IF_SYNTEX;
			break;
			case VDX_TITLE_LINE:	if(*data > 0x0A)	{	err = IF_SYNTEX;	}		break;
			case VDX_TITLE_BLINK:	if(*data > 0x01)	{	err = IF_SYNTEX;	}		break;
			case VDX_TITLE_COLOR:	if(*data > 0x06)	{	err = IF_SYNTEX;	}		break;

			case VDX_TITLE_LINE_CH1:
			case VDX_TITLE_LINE_CH2:
			case VDX_TITLE_LINE_CH3:
			case VDX_TITLE_LINE_CH4:
			case VDX_TITLE_LINE_CH5:
			case VDX_TITLE_LINE_CH6:
			case VDX_TITLE_LINE_CH7:
			case VDX_TITLE_LINE_CH8:
			case VDX_TITLE_LINE_CH9:
			case VDX_TITLE_LINE_CH10:
			case VDX_TITLE_LINE_CH11:
			case VDX_TITLE_LINE_CH12:
			case VDX_TITLE_LINE_CH13:
			case VDX_TITLE_LINE_CH14:
			case VDX_TITLE_LINE_CH15:
			case VDX_TITLE_LINE_CH16:
			case VDX_TITLE_LINE_CH17:
			case VDX_TITLE_LINE_CH18:
			case VDX_TITLE_LINE_CH19:
			case VDX_TITLE_LINE_CH20:
				if(*data > 0x4F)	err = IF_SYNTEX;
			break;
			default:
				err = IF_SYNTEX;
			break;
		}
	}
	//TILTLE은 INQ가 없다
	else
	{
		switch(idx)
		{
			case VDX_TITLE_H_POS:
				if(*data > 0x1F)	err = IF_NOEXCUTE;
				IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,line ,idx, *data);
			break;
			case VDX_TITLE_ON:
				tmp = *data>>4;
				if(tmp == 0x01)
				{
					tmp = *data&0xf;
					if(tmp == 0xf)
					{
						for(i = 0 ; i < 11; i++)
							for(j = 0 ; j < 20; j++)
								IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,i ,VDX_TITLE_LINE_CH1 + j, 0x1B);
					}
					else
					{
						tmp = 0x33+22*line;
						for(j = 0 ; j < 20; j++)
							IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,line ,VDX_TITLE_LINE_CH1 + j, 0x1B);
					}
				}
				else if(tmp == 0x02)
				{
					tmp = *data&0xf;
					if((tmp) == 0xf)
					{
						for(i=0;i < 12;i++)
							IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,i ,idx, 1);
					}
					else
						IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,*data&0x0f ,idx, 1);
				}
				else if(tmp == 0x03)
				{
					tmp = *data&0xf;
					if((tmp) == 0xf)
					{
						for(i=0;i < 12;i++)
							IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,i ,idx, 0);
					}
					else
						IF_EEPViscaTitleUpdate(IFEVT_SETVAL ,*data&0x0f ,idx, 0);
				}
				else	err = IF_NOEXCUTE;
			break;
			case VDX_TITLE_LINE:	line = *data;		break;
			case VDX_TITLE_BLINK:	IF_EEPViscaTitleUpdate(IFEVT_SETVAL,line ,idx, *data);		break;
			case VDX_TITLE_COLOR:	IF_EEPViscaTitleUpdate(IFEVT_SETVAL,line ,idx, *data);		break;
			case VDX_TITLE_LINE_CH1:
			case VDX_TITLE_LINE_CH2:
			case VDX_TITLE_LINE_CH3:
			case VDX_TITLE_LINE_CH4:
			case VDX_TITLE_LINE_CH5:
			case VDX_TITLE_LINE_CH6:
			case VDX_TITLE_LINE_CH7:
			case VDX_TITLE_LINE_CH8:
			case VDX_TITLE_LINE_CH9:
			case VDX_TITLE_LINE_CH10:
			case VDX_TITLE_LINE_CH11:
			case VDX_TITLE_LINE_CH12:
			case VDX_TITLE_LINE_CH13:
			case VDX_TITLE_LINE_CH14:
			case VDX_TITLE_LINE_CH15:
			case VDX_TITLE_LINE_CH16:
			case VDX_TITLE_LINE_CH17:
			case VDX_TITLE_LINE_CH18:
			case VDX_TITLE_LINE_CH19:
			case VDX_TITLE_LINE_CH20:
				IF_EEPViscaTitleUpdate(evt ,line ,idx, *data);
			break;
			default:
				err = IF_SYNTEX;
			break;
		}
	}
#ifdef WIN32
	printf("Line [%d] data[%d] err[%d]\n",line,*data,err);
	for(i=0;i<0x0B;i++)
	{
		for(j=0;j<20;j++)
		{
			tmp = IF_EEPViscaTitleUpdate(IFEVT_GETVAL, i,VDX_TITLE_LINE_CH1+j, 0);
			printf("%02X",tmp);
		}
		printf("~H:%02d ",IF_EEPViscaTitleUpdate(IFEVT_GETVAL, i,VDX_TITLE_H_POS, 0));
		printf("C:%02d ",IF_EEPViscaTitleUpdate(IFEVT_GETVAL, i,VDX_TITLE_COLOR, 0));
		printf("B:%02d ",IF_EEPViscaTitleUpdate(IFEVT_GETVAL, i,VDX_TITLE_BLINK, 0));
		printf("O:%02d ",IF_EEPViscaTitleUpdate(IFEVT_GETVAL, i,VDX_TITLE_ON, 0));
		printf("\n");
	}
#endif
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Gamma(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_GAM_OFFSET:
				if(g_ViscaData.FLD.GAM_OFFSET_S == 1)
				{
					if(*data > 0x10)	err = IF_SYNTEX;
				}
				else
				{
					if(*data > 0x40)	err = IF_SYNTEX;
				}
			break;
			default:
				err = IF_SYNTEX;
			break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_GAM_OFFSET:
				g_ViscaData.FLD.GAM_OFFSET = *data;
			break;
			default:
				err = IF_SYNTEX;
			break;
		}
	}


	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Ext_Move(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	uint32 tmp;
	uint32 add;
	uint32 val;
	tmp = *data >>8;
	add = *data & 0xff;
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_EX_EXPAP_RESET:
				switch(tmp)
				{
					case 0x00:	err = IF_ERNO;		break;
					case 0x02:	if(add > 0x7f)	{	err = IF_SYNTEX;	}	break;
					case 0x03:	if(add > 0x7f)	{	err = IF_SYNTEX;	}	break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_EX_EXPCOMP_RESET:
				switch(tmp)
				{
					case 0x00:	err = IF_ERNO;		break;
					case 0x02:	if(add > 0x7f)	{	err = IF_SYNTEX;	}	break;
					case 0x03:	if(add > 0x7f)	{	err = IF_SYNTEX;	}	break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_EX_AICR_ON2OFF:
				if(evt == IFEVT_SETVAL)
				{
					switch(tmp)
					{
						case 0x00:	if(add > 0xff)	{	err = IF_SYNTEX;	}	break;
						case 0x10:	if(add > 0x1C)	{	err = IF_SYNTEX;	}	break;
						default:	err = IF_SYNTEX;	break;
					}
				}
			break;
			default : err = IF_SYNTEX; break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_EX_EXPAP_RESET:
				switch(tmp)
				{
					case 0x00:
						g_ViscaData.FLD.EX_EXPAP_DIRECT = 0xA0;
					break;
					case 0x02:
						val = g_ViscaData.FLD.EX_EXPAP_DIRECT;
						if(val < 0xff)
						{
							if(add)
								if(val + add > 0xff)
									g_ViscaData.FLD.EX_EXPAP_DIRECT = 0xFF;
								else
									g_ViscaData.FLD.EX_EXPAP_DIRECT += add;
							else
								g_ViscaData.FLD.EX_EXPAP_DIRECT++;
						}
					break;
					case 0x03:
						val = g_ViscaData.FLD.EX_EXPAP_DIRECT;
						if(val)
						{
							if(add)
								if(val - add > 0xff)
									g_ViscaData.FLD.EX_EXPAP_DIRECT = 0x00;
								else
									g_ViscaData.FLD.EX_EXPAP_DIRECT -= add;
							else
								g_ViscaData.FLD.EX_EXPAP_DIRECT--;
						}
					break;
					default:	err = IF_SYNTEX;	break;
				}
			break;

			case VDX_EX_EXPCOMP_RESET:
				switch(tmp)
				{
					case 0x00:
						g_ViscaData.FLD.EX_EXPCOMP_DIRECT = 0x80;
					break;
					case 0x02:
						val = g_ViscaData.FLD.EX_EXPCOMP_DIRECT;
						if(val < 0xff)
						{
							if(add)
							{
								if(val + add > 0xff)
									g_ViscaData.FLD.EX_EXPCOMP_DIRECT = 0xFF;
								else
									g_ViscaData.FLD.EX_EXPCOMP_DIRECT += add;
							}
							else
								g_ViscaData.FLD.EX_EXPCOMP_DIRECT++;
						}
					break;
					case 0x03:
						val = g_ViscaData.FLD.EX_EXPCOMP_DIRECT;
						if(val)
						{
							if(*data)
								if(val - add > 0xff)
									g_ViscaData.FLD.EX_EXPCOMP_DIRECT = 0x00;
								else
									g_ViscaData.FLD.EX_EXPCOMP_DIRECT -= add;
							else
								g_ViscaData.FLD.EX_EXPCOMP_DIRECT--;
						}
					break;
					default:	err = IF_SYNTEX;	break;
				}
			break;

			case VDX_EX_AICR_ON2OFF:
				if(evt == IFEVT_SETVAL)
				{
					switch(tmp)
					{
						case 0x00:	g_ViscaData.FLD.EX_AICR_ON2OFF = *data;		break;
						case 0x10:	g_ViscaData.FLD.EX_AICR_OFF2ON = *data;		break;
						default:	err = IF_SYNTEX;	break;
					}
				}
				else
				{
					switch(*data)
					{
						case 0x00:	*data = g_ViscaData.FLD.EX_AICR_ON2OFF;	break;
						case 0x01:	*data = g_ViscaData.FLD.EX_AICR_OFF2ON; break;
						default:	err = IF_SYNTEX;	break;
					}
				}
			break;

			default : err = IF_SYNTEX; break;
		}
	}
	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Cant_Handle(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	uint08 tmp;
	uint08 tmp2;
	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_MOVE_ZOOM :
			case VDX_MOVE_FOCUS :
				tmp = *data>>4;
				tmp2 = *data&0x0F;
				switch(tmp)
				{
					case 0x00:
						switch(*data)
						{
							case 0:
							case 2:
							case 3:		err = IF_ERNO;	break;
							default:	err = IF_SYNTEX;	break;
						}
						break;
					case 0x02:	if(tmp2 > 0x7)	{	err = IF_SYNTEX;	}	break;
					case 0x03:	if(tmp2 > 0x7)	{	err = IF_SYNTEX;	}	break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_PUSH_WB :	if(*data != 0x05)	{	err = IF_SYNTEX;	}	break;
			case VDX_FCS_PUSH :
				switch(*data)
				{
					case 1:
					case 2:		err = IF_ERNO;	break;
					default:	err = IF_SYNTEX;	break;
				}
				break;
			case VDX_INIT_CAM :
				switch(*data)
				{
					case 1:
					case 3:		err = IF_ERNO;	break;
					default:	err = IF_SYNTEX;	break;
				}
				break;
			case VDX_CAM_MEMCUS :
				tmp  = *data>>8;
				tmp2 = *data&0xFF;
				if(tmp < 3)
				{
					if(tmp2 == 0x7F)	err = IF_ERNO;
#if VISCA_COMPILE == VSC_TYPE_EH6300
					else if(tmp2 > 0x05)	err = IF_SYNTEX;
#else
					else if(tmp2 > 0x0F)	err = IF_SYNTEX;
#endif
				}
				else
					err = IF_SYNTEX;

				break;
			default : err = IF_SYNTEX; break;
		}
	}

	return err;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	구조체에서 만으로 표현할수 없는 처리를 한다.\n
*	IFEVT_SETVAL	: CMD 데이터\n
*	IFEVT_GETVAL	: INQ 데이터\n
*	IFEVT_VISCA_CMD : 데이터를 검증\n
*************************************************************************************************************/
static IFER Except_Move(IFEVT evt,EEP_IDX idx,uint32 *data)
{
	IFER err = IF_ERNO;
	uint32 tmp;

	tmp = (*data & 0xf0);

	if(evt == IFEVT_VISCA_CMD)
	{
		switch(idx)
		{
			case VDX_BRIGHT_STEP :
#if (VISCA_COMPILE == VSC_TYPE_EH6300)
				if((*data < 0x05 || *data > 0x1F) && (*data != 0))
#elif (VISCA_COMPILE == VSC_TYPE_EV7100)
				if((*data < 0x07 || *data > 0x1F) && (*data != 0))
#else
				if((*data < 0x07 || *data > 0x1F) && (*data != 0))
#endif
					err = IF_SYNTEX;
			break;
			case VDX_IRIS_STEP :
#if (VISCA_COMPILE == VSC_TYPE_EH6300)
				if((*data < 0x05 || *data > 0x11) && (*data != 0))
#elif (VISCA_COMPILE == VSC_TYPE_EV7100)
				if((*data < 0x07 || *data > 0x11) && (*data != 0))
#else
				if((*data < 0x07 || *data > 0x11) && (*data != 0))
#endif
					err = IF_SYNTEX;
			break;
			case VDX_GAIN_STEP :
#if VISCA_COMPILE == VSC_TYPE_EH6300
				if(*data > 0x0F)
#else
				if(*data < 0x01 || *data > 0x0F)
#endif
					err = IF_SYNTEX;
				else if(*data > g_ViscaData.FLD.GAIN_LIMIT)
					err = IF_NOEXCUTE;

			break;
			case VDX_MOVE_RGAIN :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_BGAIN :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_DZOOM :
				switch(*data)
				{
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_SHUT :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_IRIS :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_GAIN :

				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_BRIGHT :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_EXPCOMP :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
			case VDX_MOVE_APERTURE :
				switch(*data)
				{
					case 0:
					case 2:
					case 3:		err = IF_ERNO;		break;
					default:	err = IF_SYNTEX;	break;
				}
			break;
		}
	}
	else
	{
		switch(idx)
		{
			case VDX_BRIGHT_STEP :		g_ViscaData.FLD.BRIGHT_STEP = *data;		break;
			case VDX_IRIS_STEP :		g_ViscaData.FLD.IRIS_STEP = *data;			break;
			case VDX_GAIN_STEP :		g_ViscaData.FLD.GAIN_STEP = *data;			break;
			case VDX_MOVE_RGAIN :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.R_GAIN = 0x7f;		break;
					case 2:		if(g_ViscaData.FLD.R_GAIN<0xff)	{	g_ViscaData.FLD.R_GAIN++;	}	break;
					case 3:		if(g_ViscaData.FLD.R_GAIN)		{	g_ViscaData.FLD.R_GAIN--;	}	break;
				}
			break;
			case VDX_MOVE_BGAIN :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.B_GAIN = 0x7f;		break;
					case 2:		if(g_ViscaData.FLD.B_GAIN<0xff)	{	g_ViscaData.FLD.B_GAIN++;	}	break;
					case 3:		if(g_ViscaData.FLD.B_GAIN)		{	g_ViscaData.FLD.B_GAIN--;	}	break;
				}
			break;
			case VDX_MOVE_DZOOM :
				switch(*data)
				{
					case 2:		g_ViscaData.FLD.DZOOM_ON = 1;		break;
					case 3:		g_ViscaData.FLD.DZOOM_ON = 0;		break;
				}
			break;
			case VDX_MOVE_SHUT :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.SHUTTER_STEP = 0x06;	break;
					case 2:		if(g_ViscaData.FLD.SHUTTER_STEP<0x0015)	{	g_ViscaData.FLD.SHUTTER_STEP++;	}	break;
					case 3:		if(g_ViscaData.FLD.SHUTTER_STEP)		{	g_ViscaData.FLD.SHUTTER_STEP--;	}	break;
				}
			break;
			case VDX_MOVE_IRIS :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.IRIS_STEP = 0x11;		break;
					case 2:
						if(g_ViscaData.FLD.IRIS_STEP == 0x00)
	#if VISCA_COMPILE == VSC_TYPE_EV6300
							g_ViscaData.FLD.IRIS_STEP = 0x05;
	#else
							g_ViscaData.FLD.IRIS_STEP = 0x07;
	#endif
						else if(g_ViscaData.FLD.IRIS_STEP < 0x0011)
							g_ViscaData.FLD.IRIS_STEP++;
					break;
					case 3:
	#if VISCA_COMPILE == VSC_TYPE_EV6300
						if(g_ViscaData.FLD.IRIS_STEP == 0x05)
	#else
						if(g_ViscaData.FLD.IRIS_STEP == 0x07)
	#endif
							g_ViscaData.FLD.IRIS_STEP = 0x00;
						else if(g_ViscaData.FLD.IRIS_STEP)
							g_ViscaData.FLD.IRIS_STEP--;
					break;
				}
			break;
			case VDX_MOVE_GAIN :

				switch(*data)
				{
					case 0:		g_ViscaData.FLD.GAIN_STEP = 0x01;	break;
					case 2:
						if(g_ViscaData.FLD.GAIN_STEP < g_ViscaData.FLD.GAIN_LIMIT && g_ViscaData.FLD.GAIN_STEP < 0x000f)
							g_ViscaData.FLD.GAIN_STEP++;
						break;
					case 3:
	#if VISCA_COMPILE == VSC_TYPE_EV6300
						if(g_ViscaData.FLD.GAIN_STEP > 0)
	#else
						if(g_ViscaData.FLD.GAIN_STEP > 1)
	#endif
							g_ViscaData.FLD.GAIN_STEP--;
						break;
				}
			break;
			case VDX_MOVE_BRIGHT :
				switch(*data)
				{
					case 0:
						g_ViscaData.FLD.BRIGHT_STEP = 0x0B;
					break;
					case 2:
						if(g_ViscaData.FLD.BRIGHT_STEP == 0)
#if VISCA_COMPILE == VSC_TYPE_EV6300
							g_ViscaData.FLD.BRIGHT_STEP = 0x05;
#else
							g_ViscaData.FLD.BRIGHT_STEP = 0x07;
#endif
						else if(g_ViscaData.FLD.BRIGHT_STEP < 0x001F)
							g_ViscaData.FLD.BRIGHT_STEP++;
					break;
					case 3:
#if VISCA_COMPILE == VSC_TYPE_EV6300
						if(g_ViscaData.FLD.BRIGHT_STEP == 0x05)
#else
						if(g_ViscaData.FLD.BRIGHT_STEP == 0x07)
#endif
							g_ViscaData.FLD.BRIGHT_STEP = 0x00;
						else if(g_ViscaData.FLD.BRIGHT_STEP)
							g_ViscaData.FLD.BRIGHT_STEP--;
					break;
				}
			break;
			case VDX_MOVE_EXPCOMP :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.EXP_COMP_VAL = 0x07;	break;
					case 2:		if(g_ViscaData.FLD.EXP_COMP_VAL< 0x000E){	g_ViscaData.FLD.EXP_COMP_VAL++;	}	break;
					case 3:		if(g_ViscaData.FLD.EXP_COMP_VAL)		{	g_ViscaData.FLD.EXP_COMP_VAL--;	}	break;
				}
			break;
			case VDX_MOVE_APERTURE :
				switch(*data)
				{
					case 0:		g_ViscaData.FLD.APER_GAIN = 0x0A;		break;
					case 2:		if(g_ViscaData.FLD.APER_GAIN< 0x000F)	{	g_ViscaData.FLD.APER_GAIN++;	}	break;
					case 3:		if(g_ViscaData.FLD.APER_GAIN)			{	g_ViscaData.FLD.APER_GAIN--;	}	break;
				}
			break;
		}
	}

	return err;
}

/*********************************************************************************************************//**
* @param[in] mode	: 8bit 데이터를 버퍼에 4bit씩 저장할지,8bit씩 저장할지
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @param[in] buf	: 버퍼
* @param[in] dat	: 데이터
* @retval
*	return IFER
* @brief
*	데이터를 합친다.\n
*	COMPOSE_D_FULL : 8bit*4\n -> 32bit \n
*	COMPOSE_D_HALF : 4bit*8\n -> 32bit \n
*************************************************************************************************************/
IFER Compose_data(COMPOSE_DATA mode,uint08 size,uint08 *pdat,uint32 *dat)
{
	uint08 i;
	*dat = 0;

	if(size == 0)	return IF_ERNO;
	else if(size > 8)	return IF_INVALIDVAL;

	if(mode == COMPOSE_D_HALF)
	{
		for(i=0;i<size;i++)
		{
			*dat |= (pdat[i]&0xf)<<((size-1-i)<<2);
		}
	}
	else if(mode == COMPOSE_D_FULL)
	{
		for(i=0;i<size;i++)
		{
			*dat |= pdat[i]<<((size-1-i)<<3);
		}
	}

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @param[in] mode	: 8bit 데이터를 버퍼에 4bit씩 저장할지,8bit씩 저장할지
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @param[in] buf	: 버퍼
* @param[in] dat	: 데이터
* @retval
*	return IFER
* @brief
*	데이터를 나눈다.\n
*	COMPOSE_D_FULL : 32bit -> 8bit*4\n
*	COMPOSE_D_HALF : 32bit -> 4bit*8\n
*************************************************************************************************************/
IFER Relieve_data(COMPOSE_DATA mode,uint08 size,uint08 *pdat,uint32 dat)
{
	uint08 i;

	if(size == 0)	return IF_ERNO;
	else if(size > 4)	return IF_INVALIDVAL;

	if(mode == COMPOSE_D_HALF)
	{
		for(i=0;i<size;i++)
		{
			pdat[i] = (dat>>((size-1-i)<<2)) & 0x0f;
		}
	}
	else if(mode == COMPOSE_D_FULL)
	{
		for(i=0;i<size;i++)
		{
			pdat[i] = (dat>>((size-1-i)<<3)) & 0xff;
		}
	}

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @param[in] buf	: 버퍼 포인터
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @retval
*	return IFER
* @brief
*	Tx buf -> Que
*************************************************************************************************************/
IFER PtcSendBuf(uint08* buf,uint16 size)
{
	uint16 i;
	if(IF_PTC_TxQueSize()+size > 255)
	{
		/* Buffer Full */
		Ptc_Que.TxHead = 0;
		Ptc_Que.TxTail = 0;
		if(g_OsdData.FLD.PROTOCOL == 3)
			PtcVisca_SendPacket(VISCA_ERROR_COMMAND_BUF_FULL,0,0);

		return 0;
	}

	for(i=0;i<size;i++)
	{
		IF_PTC_SetTxQue(buf[i]);
	}

	return 0;
}
/*********************************************************************************************************//**
* @param[in] buf	: 버퍼 포인터
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @retval
*	return 0xFF Position
* @brief
*	버퍼에서 Visca Protocol의 0xFF를 가지고 있는 지	\n
*	버퍼의 몇번째 변수에서 0xFF를 가지고 있는지 검출\n
*************************************************************************************************************/
uint32 PtcVisca_FndFF(uint08* buf,uint16 size)
{
	uint16 i;

	for(i=0;i<size+1;i++)
	{
		if(buf[i] == 0xff)
		{
			return i;
		}
	}

	return -1;
}
/*********************************************************************************************************//**
* @param[in] buf	: 버퍼 포인터
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @retval
*	return Header Position
* @brief
*	버퍼에서 Visca Protocol의 헤더를 가지고 있는 지 \n
*	버퍼의 몇번째 변수에서 헤더를 가지고 있는지 검출\n
*************************************************************************************************************/
uint32 PtcVisca_FndHD(uint08* buf,uint16 size)
{
	uint16 i;
//	uint08 tmp;
	for(i=0;i<size+1;i++)
	{
		if(buf[i]&0x80 && buf[i] != 0xFF)
		{
			//if	(((buf[i]&0x07) == 0x00) && ((buf[i]&0x70) <= 0x70))	return i;
			//else if	(((buf[i]&0x70) == 0x00) && ((buf[i]&0xF) < 0x09))	return i;

			switch(buf[i])
			{
				case 0x81 :
				case 0x82 :
				case 0x83 :
				case 0x84 :
				case 0x85 :
				case 0x86 :
				case 0x87 :
				case 0x88 :
				case 0x90 :
				case 0xA0 :
				case 0xB0 :
				case 0xC0 :
				case 0xD0 :
				case 0xE0 :
				case 0xF0 :
					return i;
			}
		}
	}

	return -1;
}
/*********************************************************************************************************//**
* @param[in] err	: 패킷의 종류
* @param[in] pack	: 버퍼 포인터
* @param[in] size	: 버퍼에 쌓인 데이터의 크기
* @retval
*	none
* @brief
*	VISCA Protocol에서 전송 패킷을 만들고 보낸다.
*************************************************************************************************************/
void PtcVisca_SendPacket(VISCA_MSG err,uint08 *pack,uint08 size)
{
	uint08 err_pack[16];
	uint08 i;
	uint08 err_pack_size = 0;
	err_pack[0] = 0x80 | (gPtc_Visca_Addr<<4);
	err_pack[1] = 0x60 + gPtc_Visca_Socket;
	err_pack_size = 4;
	switch(err)
	{
		case  VISCA_ERROR_MSG_LENGTH:			err_pack[2] = 0x01;		break;
		case  VISCA_ERROR_SYNTEX:
			err_pack[2] = 0x02;
		break;
		case  VISCA_ERROR_COMMAND_BUF_FULL:
			err_pack[1] = 0x60;
			err_pack[2] = 0x03;
			break;
		case  VISCA_ERROR_COMMAND_CANCEL:		err_pack[2] = 0x04;		break;
		case  VISCA_ERROR_NO_SOCKET:			err_pack[2] = 0x05;		break;
		case  VISCA_ERROR_COMMAND_EXCUTABLE:	err_pack[2] = 0x41;		break;

		case VISCA_MSG_ACKNOWLEDGE:
			err_pack[1] = 0x40 + gPtc_Visca_Socket;
			err_pack_size = 3;
			break;
		case VISCA_MSG_COMPETE_CMD:
			err_pack[1] = 0x50 + gPtc_Visca_Socket;
			err_pack_size = 3;
			break;
		case VISCA_MSG_COMPETE_INQ:
			err_pack[1] = 0x50;
			err_pack_size = 3+size;
			for(i=0;i<size;i++)
				err_pack[2+i] = pack[i];
			break;
		case VISCA_MSG_REPLY:
			err_pack[1] = 0x07;
			err_pack[2] = 0x04;
			err_pack_size = 4+size;
			for(i=0;i<size;i++)
				err_pack[3+i] = pack[i];
			break;
		case VISCA_MSG_GLB_ADDSET:
			err_pack[0] = 0x88;
			err_pack[1] = 0x30;
			err_pack[2] = gPtc_Visca_Addr + 1;
			err_pack_size = 4;
			break;
		case VISCA_MSG_GLB_IFCLEAR:
			err_pack[0] = 0x88;
			err_pack[1] = 0x01;
			err_pack[2] = 0x00;
			err_pack[3] = 0x01;
			err_pack_size = 5;
			break;
		case VISCA_MSG_NETWORK_CHANGE:
			err_pack[1] = 0x38;
			err_pack_size = 3;
		break;
		default:

		break;
	}
	err_pack[err_pack_size - 1] = 0xFF;
	PtcSendBuf(err_pack,err_pack_size);
}
/*********************************************************************************************************//**
* @param[in] cmd	: cmd
* @retval
*	return : "gPtcVisca_Cmd" idx
* @brief
*	패킷의 커맨드가 CMD 커맨드가 맞는지 검색
*************************************************************************************************************/
uint32 Find_Visca_CMD_Idx(uint16 cmd)
{
	uint16 max = MAX_VISCA_CMD;
	uint16 min = 0;
	uint16 mid = 0;
	//uint08 i = 0;
	while(max >= min)
	{
		mid = (max+min)>>1;

		if(gPtcVisca_Cmd[mid].cmd == cmd)
		{
			//printf("find cnt[%d %05d %03d,%03d]\n",i,gPtcVisca_Cmd[mid].eepidx,gPtcVisca_Cmd[mid].length,gPtcVisca_Cmd[mid].evts);
			return mid;
		}
		else
		{
			//printf("[%d] == [%d]\n",gPtcVisca_Cmd[mid].cmd,cmd);
			if(gPtcVisca_Cmd[mid].cmd > cmd)
				max = mid -1;
			else
				min = mid +1;
		}
		//i++;
	}
	return -1;
}
/*********************************************************************************************************//**
* @param[in] inq	: cmd
* @retval
*	return : "gPtcVisca_Inq" idx
* @brief
*	패킷의 커맨드가 INQ 커맨드가 맞는지 검색
*************************************************************************************************************/
uint32 Find_Visca_INQ_Idx(uint16 inq)
{
	uint16 max = MAX_VISCA_INQ;
	uint16 min = 0;
	uint16 mid = 0;
	uint08 i = 0;
	while(max >= min)
	{
		mid = (max+min)>>1;

		if(gPtcVisca_Inq[mid].cmd == inq)
		{
			//printf("find inq[%d %05d %03d,%03d]\n",i,gPtcVisca_Inq[mid].eepidx,gPtcVisca_Inq[mid].length,gPtcBuf.VISCA_PTC.LENGTH);
			return mid;
		}
		else
		{
			//printf("[%d] == [%d]\n",gPtcVisca_Inq[mid].cmd,cmd);
			if(gPtcVisca_Inq[mid].cmd > inq)
				max = mid -1;
			else
				min = mid +1;
		}
		i++;
	}
	return -1;
}
/*********************************************************************************************************//**
* @param[in] vdx	: id
* @retval
*	return : "IFU_Cndtn" idx
* @brief
*	컨디션 구조체 검색
*************************************************************************************************************/
int32 Find_Visca_Cndtn(uint16 vdx)
{
	uint16 max = MAX_CONDITION-1;
	uint16 min = 0;
	uint16 mid = 0;

	while(max >= min)
	{
		mid = (max+min)>>1;

		if(IFU_Cndtn[mid].idx == vdx)
		{
			//printf("CONDITION FIND [%d] == [%d]\n",gpCndtn[mid].idx,vdx);
			return mid;
		}
		else
		{
			if(IFU_Cndtn[mid].idx > vdx)
				max = mid -1;
			else
				min = mid +1;
		}
	}
	//printf("NOT FIND CONDITION\n");
	return -1;
}
/*********************************************************************************************************//**
* @param[in] idx	: id
* @retval
*	return 구조체 Read 값
* @brief
*	컨디션 체크 전용 구조체 Update 함수
*************************************************************************************************************/
static int32 User_Codition_Update(EEP_IDX idx)
{
	int32 ret = -1;

	switch(idx)
	{
		case VDX_F_MODE :        		ret=(g_ViscaData.FLD.F_MODE);     			break;
		case VDX_WB_MODE :              ret=(g_ViscaData.FLD.WB_MODE);        		break;
		case VDX_AE_MODE :              ret=(g_ViscaData.FLD.AE_MODE);        		break;
		case VDX_DEFOG_ON :             ret=(g_ViscaData.FLD.DEFOG_ON);        		break;
		case VDX_FREEZE_ON :			ret=(g_ViscaData.FLD.FREEZE_ON);			break;
		case VDX_WD_MODE :				ret=(g_ViscaData.FLD.WD_MODE);        		break;
		case VDX_EX_EXPC_ON :			ret=(g_ViscaData.FLD.EX_EXPC_ON);      		break;
		case VDX_EX_EXPAP_ON :			ret=(g_ViscaData.FLD.EX_EXPAP_ON);     		break;
		case VDX_EX_CGCH_ON :			ret=(g_ViscaData.FLD.EX_CGCH_ON);      		break;
		case VDX_EX_AICR_F2O_ON :		ret=(g_ViscaData.FLD.EX_AICR_F2O_ON);  		break;
		//case IDX_ZOOM_DIRECT :        ret=(g_OsdData.FLD.IDX_ZOOM_DIRECT);    	break;
		//case IDX_FOCUS_DIRECT :       ret=(g_OsdData.FLD.IDX_FOCUS_DIRECT);   	break;
		//case IDX_ZMFCS_DIRECT :       ret=(g_OsdData.FLD.IDX_ZMFCS_DIRECT);   	break;
		//case IDX_MEMSAVE :			ret=(g_OsdData.FLD.IDX_ZMFCS_DIRECT);   	break;
		default:
			ret = -1;
		break;
	}

	return ret;
}

/*********************************************************************************************************//**
* @param[in] vdx	: ID
* @param[in] data	: 데이터
* @retval
*	return IFER
* @brief
*	컨디션 체크 함수
*************************************************************************************************************/
static IFER Visca_Condition_Check(uint16 vdx,uint32 data)
{
	IFER err = IF_ERNO;
	IF_CONDITION *condition_chk = 0;
	uint08 i;
	uint32 tmp = -1;

	tmp = Find_Visca_Cndtn(vdx);

	if(tmp != -1)
	{
		condition_chk = (IF_CONDITION *)IFU_Cndtn[tmp].cndtn;
		for(i=0;(condition_chk[i].idx != IDX_NULL); i++)
		{
			tmp = User_Codition_Update(condition_chk[i].idx);
			if(condition_chk[i].dat == tmp) //같으면 넘어감
			{
				return IF_ERNOPROC;//Excutable Error
			}
		}
	}
	else
	{
		switch(vdx)
		{
			case VDX_AE_MODE :
				//printf("SET AE MODE : %d->%d\n",g_ViscaData.FLD.AE_MODE,data);
				if(((g_ViscaData.FLD.AE_MODE == 1) || (g_ViscaData.FLD.AE_MODE == 3)) && (data == 0x0D))
					err = IF_ERNOPROC;
#if VISCA_COMPILE == VSC_TYPE_EH6300
				if((data > 0) && ((g_ViscaData.FLD.WD_MODE != 3) || (g_ViscaData.FLD.DEFOG_ON)))
#else
				if((data > 0) && ((g_ViscaData.FLD.WD_MODE != 1) || (g_ViscaData.FLD.DEFOG_ON)))
#endif
					err = IF_ERNOPROC;
				//printf("ERR %d, WD: %d, DEFOG :%d \n",err,g_ViscaData.FLD.WD_MODE,g_ViscaData.FLD.DEFOG_ON);
			break;
		}
	}
	return err;
}
#if 0
IFER PtcCNBHUserProc()
{
	IFER er = IF_ERNOPROC;

#ifdef WIN32
	printf("RECVUSER[%d]:\nHD:%X, PG:%X, ID:%X, TYPE:%X, LEN:%x\nCMD1:%X, CMD2:%X, MSG:%X %X %X %X \t%X %X %X %X \t%X %X %X %X \t%X %X %X\n",
		gPtcCursor,
		gPtcBuf.USER_PTC.HEADER, gPtcBuf.USER_PTC.PG, gPtcBuf.USER_PTC.ID, gPtcBuf.USER_PTC.CMD_TYPE, gPtcBuf.USER_PTC.MSG_LEN, gPtcBuf.USER_PTC.CMD1, gPtcBuf.USER_PTC.CMD2,
		gPtcBuf.USER_PTC.MSG1, gPtcBuf.USER_PTC.MSG2, gPtcBuf.USER_PTC.MSG3, gPtcBuf.USER_PTC.MSG4, gPtcBuf.USER_PTC.MSG5, gPtcBuf.USER_PTC.MSG6, gPtcBuf.USER_PTC.MSG7, gPtcBuf.USER_PTC.MSG8,
		gPtcBuf.USER_PTC.MSG9, gPtcBuf.USER_PTC.MSG10, gPtcBuf.USER_PTC.MSG11, gPtcBuf.USER_PTC.MSG12, gPtcBuf.USER_PTC.MSG13, gPtcBuf.USER_PTC.MSG14, gPtcBuf.USER_PTC.MSG15);
#endif

	if(gPtcBuf.USER_PTC.HEADER == PTC_CNBH_USERHEADER)
	{
		if((gPtcCursor > 7) && ((gPtcCursor - gPtcBuf.USER_PTC.MSG_LEN) > 7))
		{
			/* CAM ID Check */
			if(g_OsdData.FLD.ID_CHK == 1)
			{
				if(g_OsdData.FLD.CAM_ID != gPtcBuf.USER_PTC.ID)
				{
//					ID ERROR
				}
			}

			switch(gPtcBuf.USER_PTC.CMD_TYPE)
			{
				/* SET DIRECT VALUE */
				case 1:
					{
						if(gPtcBuf.USER_PTC.MSG_LEN <= (gPtcCursor - 7))
						{

						}
					}break;
				case 2:	break;	/* SET INCREASE */
				case 3:	break;	/* SET DECREASE */
				case 4:	break;	/* GET */
				default:
//					CMD TYPE ERROR
					break;
			}
			gPtcBuf.USER_PTC.MSG_LEN = 0;

			gPtcCursor = 0;
		}
	}

	return er;
}
#endif
/*********************************************************************************************************//**
* @param[in] cmd	: 명령
* @retval
*	return IFER
* @brief
*	CNB HEX Technical Protocol에서 \n
*	디코더 및 CallBack함수를 호출한다.
*************************************************************************************************************/
IFER PrcCNBT_Dec_CallBack(uint08 cmd)
{
	uint08 i;
	uint08 rw_flg = 0;
	uint08 length = 1;
	uint08 add = 1;
	uint32 addr = gPtcBuf.TECH_PTC.PARAM1_1<<8 | gPtcBuf.TECH_PTC.PARAM1_2;
	uint32_b Dat;
	PTC_CNBT_CB_FUNC* ext_func = &CNBT_Callback[CNBT_MAX];

	IFER er = IF_ERNO;

	switch(cmd)
	{
		case 0x01 :	// DSP Reg	R
		case 0x02 : // DSP Reg	W
			rw_flg = (gPtcBuf.TECH_PTC.CMD + 1)&0x01;
			ext_func = &CNBT_Callback[CNBT_ISP];
			length = gPtcBuf.TECH_PTC.PARAM2;
			break;
		case 0x03 : // EEP		R
		case 0x04 : // EEP		W
			rw_flg = (gPtcBuf.TECH_PTC.CMD + 1)&0x01;
			ext_func = &CNBT_Callback[CNBT_EEP];
			length = gPtcBuf.TECH_PTC.PARAM2;
			break;
		case 0x05 : // Motor	R/W(AN41908)
			if(gPtcBuf.TECH_PTC.PARAM2 == 0 || gPtcBuf.TECH_PTC.PARAM2 > 2)
			{
				er = IF_SYNTEX;
			}
			else
			{
				rw_flg = (gPtcBuf.TECH_PTC.PARAM2+1) & 0x01;
				ext_func = &CNBT_Callback[CNBT_MOTOR_IC];
			}
			break;
		case 0x06 : // Video	R/W(AD7393)
			if(gPtcBuf.TECH_PTC.PARAM2 == 0 || gPtcBuf.TECH_PTC.PARAM2 > 2)
			{
				er = IF_SYNTEX;
			}
			else
			{
				rw_flg = (gPtcBuf.TECH_PTC.PARAM2+1) & 0x01;
				ext_func = &CNBT_Callback[CNBT_VIDEO_IC];
			}
			break;
		case 0x07 : // Sensor	R/W(MN34041)
			if(gPtcBuf.TECH_PTC.PARAM2 == 0 || gPtcBuf.TECH_PTC.PARAM2 > 2)
			{
				er = IF_SYNTEX;
			}
			else
			{
				rw_flg = (gPtcBuf.TECH_PTC.PARAM2+1) & 0x01;
				ext_func = &CNBT_Callback[CNBT_SENSOR_IC];
			}

			break;
		case 0x08 :
		case 0x09 :
		case 0x0A :
		case 0x0B :
			break;
		case 0x0C : // Video Encoder IC
			if(gPtcBuf.TECH_PTC.PARAM2 == 0 || gPtcBuf.TECH_PTC.PARAM2 > 4)
			{
				er = IF_SYNTEX;
			}
			else
			{
				rw_flg = ((gPtcBuf.TECH_PTC.PARAM2-1) >> 1) & 0x01;
				ext_func = &CNBT_Callback[CNBT_VIDEO_IC2 + rw_flg];
				rw_flg = (gPtcBuf.TECH_PTC.PARAM2+1) & 0x01;
			}
			break;
		case 0x0D : // Skip EEP	W
			rw_flg = 1;//Write
			ext_func = &CNBT_Callback[CNBT_EEP_SKIP];
			length = gPtcBuf.TECH_PTC.PARAM2;
			break;

		default :
			er = IF_ERNOPROC;	//처리하지 않음
			break;
	}
	Tx_Packet[6] = 0;//length
	if(ext_func != &CNBT_Callback[CNBT_MAX])
	{
		add = ext_func->dat_size >> 1;

		if(!rw_flg)
		{
			for(i=0;i < length ;i++)
			{
				Dat.dword = ext_func->getfunc(addr + i);
				Tx_Packet[6] += ext_func->dat_size;	//length

				switch(ext_func->dat_size)
				{
					case TYPE_32BITS:
						Tx_Packet[7 +(i<<add)] = Dat.byte[3];
						Tx_Packet[8 +(i<<add)] = Dat.byte[2];
						Tx_Packet[9 +(i<<add)] = Dat.byte[1];
						Tx_Packet[10+(i<<add)] = Dat.byte[0];
					break;
					case TYPE_16BITS:
						Tx_Packet[7 +(i<<add)] = Dat.byte[1];
						Tx_Packet[8 +(i<<add)] = Dat.byte[0];
					case TYPE_8BITS:
						Tx_Packet[7 +(i<<add)] = Dat.byte[0];
					break;
				}
			}
		}
		else
		{
			for(i=0;i < length ;i++)
			{
				switch(ext_func->dat_size)
				{
					case TYPE_32BITS:
						Dat.byte[3] = gPtcBuf.data[7 +(i<<add)];
						Dat.byte[2] = gPtcBuf.data[8 +(i<<add)];
						Dat.byte[1] = gPtcBuf.data[9 +(i<<add)];
						Dat.byte[0] = gPtcBuf.data[10+(i<<add)];
						break;
					case TYPE_16BITS:
						Dat.byte[1] = gPtcBuf.data[7 + (i<<add)];
						Dat.byte[0] = gPtcBuf.data[8 + (i<<add)];
					case TYPE_8BITS:
						Dat.byte[0] = gPtcBuf.data[7 + (i<<add)];
					break;
				}
				ext_func->setfunc(addr + i,Dat.dword);
			}
		}
	}

	return er;
}
/*********************************************************************************************************//**
* @param[in] err	: 에러코드
* @retval
*	return IFER
* @brief
*	CNB_H Tech 에러에 따라서 TX Packet을 만들고 전송한다.
*	아직 에러에 대한 정의가 되지 않았다.
*************************************************************************************************************/
void CNBT_SendPacket(IFER err)
{
	uint08 chksum;
	uint16 i,size = Tx_Packet[6] + 7;

	chksum = 0;

	Tx_Packet[0] = 0xCA;					//Header
	Tx_Packet[1] = g_OsdData.FLD.CAM_ID;	//CAM_ID
	Tx_Packet[2] = gPtcBuf.data[2];			//CMD
	Tx_Packet[3] = gPtcBuf.data[3];			//P1
	Tx_Packet[4] = gPtcBuf.data[4];			//P1
	Tx_Packet[5] = gPtcBuf.data[5];			//P2

	switch(err)
	{
		case IF_ERNO :
		break;
		case IF_INVALIDVAL :		//Error에 대한 정의가 없다.
			Tx_Packet[6] = 0;
		break;
		default:
			Tx_Packet[6] = 0;
		break;
	}

	for(i=1;i < size;i++)
	{
		chksum += Tx_Packet[i];
	}
	Tx_Packet[size] = 0;
	//printf("=== %s \n",Tx_Packet);
	Tx_Packet[size] = chksum;

	PtcSendBuf(Tx_Packet,size+1);
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	CNB HEX의 Technical PROTOCOL의 Main Process
*************************************************************************************************************/
IFER PtcCNBHTeckProc()
{
	IFER er = IF_ERNO;
	uint08 chksum = 0;
	uint16	i;
	uint32 dat;
#ifdef WIN32
	printf("RECVTECK[%d]:\nHD:%X, ID:%X, CMD:%X, PARAM1:%X, PARAM2:%x \n\Leng:%X, MSG:%X %X %X %X \t%X %X %X %X \t%X %X %X %X \t%X %X %X\n",
			gPtcCursor,
			gPtcBuf.TECH_PTC.HEADER , gPtcBuf.TECH_PTC.CAM_ID, gPtcBuf.TECH_PTC.CMD, gPtcBuf.TECH_PTC.PARAM1_1<<8 | gPtcBuf.TECH_PTC.PARAM1_2, gPtcBuf.TECH_PTC.PARAM2,
			gPtcBuf.TECH_PTC.LEN, gPtcBuf.TECH_PTC.MSG1, gPtcBuf.TECH_PTC.MSG2, gPtcBuf.TECH_PTC.MSG3, gPtcBuf.TECH_PTC.MSG4, gPtcBuf.TECH_PTC.MSG5,
			gPtcBuf.TECH_PTC.MSG6, gPtcBuf.TECH_PTC.MSG7, gPtcBuf.TECH_PTC.MSG8, gPtcBuf.TECH_PTC.MSG9, gPtcBuf.TECH_PTC.MSG10, gPtcBuf.TECH_PTC.MSG11,
			gPtcBuf.TECH_PTC.MSG12, gPtcBuf.TECH_PTC.MSG13, gPtcBuf.TECH_PTC.MSG14, gPtcBuf.TECH_PTC.MSG15, gPtcBuf.TECH_PTC.MSG16, gPtcBuf.TECH_PTC.MSG17
		);
#endif

	if(gPtcBuf.TECH_PTC.HEADER == PTC_CNBH_TECHHEADER)
	{
		if((gPtcCursor > 7) && ((int16)(gPtcCursor - gPtcBuf.TECH_PTC.LEN) >6))
		{
			/* CAM ID Check */
			if(g_OsdData.FLD.CAM_ID != gPtcBuf.TECH_PTC.CAM_ID)
			{
				er = IF_SYNTEX;//ID ERROR
#ifdef WIN32
				printf("ID ERROR\n");
#endif
			}
			/* Check Sum */
			for(i=1;i < gPtcBuf.TECH_PTC.LEN + 7;i++)
			{
				chksum += gPtcBuf.data[i];
			}

			if(chksum != gPtcBuf.data[gPtcBuf.TECH_PTC.LEN + 7])
			{
				er = IF_SYNTEX;//CHKSUM ERROR
#ifdef WIN32
				printf("CHK SUM ERROR\n");
#endif
			}

			if(!er)
			{
				/* Check Decoding */
				//CallBack Proc
				er = PrcCNBT_Dec_CallBack(gPtcBuf.TECH_PTC.CMD);
				dat = gPtcBuf.data[5];
				if(gPtcBuf.data[6] < 4)
				{
					switch(gPtcBuf.data[6])
					{
						case 1:
							dat |= gPtcBuf.data[7]<<4;
						break;
						case 2:
							dat |= gPtcBuf.data[8]<<4;
							dat |= gPtcBuf.data[7]<<8;
						break;
						case 3:
							dat |= gPtcBuf.data[9]<<4;
							dat |= gPtcBuf.data[8]<<8;
							dat |= gPtcBuf.data[7]<<12;
						break;
					}
				}
				/* Check Sending */
				SendEvent(IFEVT_CNBH_TECH,gPtcBuf.TECH_PTC.CMD + CHDX_DSP_REG_READ - 1, &dat);
			}

			switch(er)
			{
				case IF_ERNO:
					CNBT_SendPacket(IF_ERNO);
				break;
				default:
					CNBT_SendPacket(IF_INVALIDVAL);
				break;
			}
			gPtcBuf.TECH_PTC.LEN = 0;
			gPtcCursor = 0;
			gPtc_CNBH_Flg = 0;
		}
	}

	return er;
}
/*********************************************************************************************************//**
* @param[in] decode_type	: 디코딩 타입
* @param[in] idx			: VDX
* @param[in] data			: 통신으로부터 입력된 값
* @param[in] evts			: 이벤트 정보
* @retval
*	return IFER
* @brief
*	통신으로부터 입력된 값의 범위 검증
*************************************************************************************************************/
IFER Processong_CMD_Value_Chk(DECODE_TYPE decode_type ,EEP_IDX idx ,uint32 data ,void *evts)
{
	IFER err = IF_ERNO;
	uint32 tmp = 0;
	uint08 i;
	IFU_DECODE_MAPING *def_map;
	IFU_DECODE_DIRECT *def_drt;
	EXPT_FNC def_fnc;

#ifdef WIN32
			printf("PROC[%04d][%04d][%04d]\n",decode_type,idx,data);
#endif
	switch(decode_type)
	{
		case DECODE_DIRECT:
			if(evts)
			{
				def_drt = (IFU_DECODE_DIRECT *)evts;

				if((data > def_drt->max) || (data < def_drt->min))
					err = IF_SYNTEX;
			}
			else
				err = IF_SYNTEX;
		break;

		case DECODE_MAPING:
			if(evts)
			{
				def_map = (IFU_DECODE_MAPING *)evts;
				tmp = -1;
				for(i=0; (def_map[i].Visca_dat != 0xffff);i++)
				{
					if(def_map[i].Visca_dat == data)
					{
						tmp = 1;
						break;
					}
				}

				if(tmp == -1)	err = IF_SYNTEX;
			}
			else	err = IF_SYNTEX;
		break;
		case DECODE_EXCEPTION:
			if(evts)
			{
				def_fnc = evts;
				if(def_fnc)
					err = def_fnc(IFEVT_VISCA_CMD,idx,&data);
			}
			else err = IF_SYNTEX;
		break;
		default:
		break;
	}

#ifdef WIN32
			printf("err(%04d)\n",err);
#endif
	return err;
}
/*********************************************************************************************************//**
* @param[in] decode_type	: 디코딩 타입
* @param[in] idx			: VDX
* @param[in] data			: 통신으로부터 입력된 값
* @param[in] evts			: 이벤트 정보
* @retval
*	return IFER
* @brief
*	Packet의 입력과 ID에 따라서 Eep 구조체이 넣어줄 값을 정의한다.
*************************************************************************************************************/
IFER Processong_CMD(DECODE_TYPE decode_type,EEP_IDX	idx,uint32 data,void *evts)
{
	IFER err = IF_ERNO;
	uint32 tmp = 0;
	uint08 i;
	IFU_DECODE_MAPING *def_map;
	IFU_DECODE_DIRECT *def_drt;
	EXPT_FNC def_fnc;
#ifdef WIN32
			printf("PROC[%04d][%04d][%04d]\n",decode_type,idx,data);
#endif
	switch(decode_type)
	{
		case DECODE_DIRECT:
			if(evts)
			{
				def_drt = (IFU_DECODE_DIRECT *)evts;
				tmp = data;
			}
#ifdef WIN32
			printf("DRT(%04d~%04d)\n",def_drt->max,def_drt->min);
			printf("DRT(%04d)\n",tmp);
#endif
		break;

		case DECODE_MAPING:
			if(evts)
			{
				def_map = (IFU_DECODE_MAPING *)evts;

				for(i=0; (def_map[i].Visca_dat != 0xffff);i++)
				{
					if(def_map[i].Visca_dat == data)
					{
						tmp = def_map[i].dat;
						break;
					}
				}
			}
#ifdef WIN32
			printf("MAP[%d]\n",tmp);
#endif
		break;
		case DECODE_EXCEPTION:
			if(evts)
			{
				def_fnc = evts;
				if(def_fnc)	err = def_fnc(IFEVT_SETVAL,idx,&data);
			}
#ifdef WIN32
			printf("EXCUTE(%04d)\n",data);
#endif
			return err;
		break;
		default:
		break;
	}

	if(err == 0)
	{
		if(IF_EEPViscaUpdate(IFEVT_SETVAL,idx,tmp) == -1) err = IF_SYNTEX;
		#ifdef WIN32
			printf("Check [%d]\n",IF_EEPViscaUpdate(IFEVT_GETVAL,idx,0));
		#endif
	}
#ifdef err
			printf("err(%04d)\n",err);
#endif
	return err;
}
/*********************************************************************************************************//**
* @param[in] decode_type	: 디코딩 타입
* @param[in] idx			: VDX
* @param[out] data			: 출력될 값의 포인터
* @param[in] evts			: 이벤트 정보
* @retval
*	return IFER
* @brief
*	Packet의 입력과 ID에 따라서 Tx데이터를 작성할 값을 불러온다.
*************************************************************************************************************/
IFER Processong_INQ(DECODE_TYPE decode_type,EEP_IDX	idx,uint32 *data,void *evts)
{
	IFER err = IF_ERNO;
	uint32 tmp;
	uint08 i;
	IFU_DECODE_MAPING *def_map;
	EXPT_FNC def_fnc;
#ifdef WIN32
	printf("PROCINQ[%04d][%04d][%04d]\n",decode_type,idx,*data);
#endif

	switch(decode_type)
	{
		case DECODE_DIRECT:
			tmp = IF_EEPViscaUpdate(IFEVT_GETVAL,idx,0);
			if(tmp == -1)	return IF_SYNTEX;

			*data = tmp;
#ifdef WIN32
			printf("DRT(%04d)\n",tmp);
#endif
		break;

		case DECODE_MAPING:
			tmp = IF_EEPViscaUpdate(IFEVT_GETVAL,idx,0);
			if(tmp == -1)	return IF_SYNTEX;

			def_map = (IFU_DECODE_MAPING *)evts;
			for(i=0;def_map[i].dat != 0xffff;i++)
			{
				if(def_map[i].dat == tmp)
				{
					*data = def_map[i].Visca_dat;
					break;
				}
			}
#ifdef WIN32
			printf("MAP[%d]\n",tmp);
#endif
		break;

		case DECODE_EXCEPTION:
			def_fnc = (EXPT_FNC)evts;
			if(def_fnc)
				err = def_fnc(IFEVT_GETVAL,idx,data);
			else
				err = IF_SYNTEX;
#ifdef WIN32
			printf("EXCUTE(%04d)\n",*data);
#endif
		break;

		default:
		break;
	}

	return err;
}
/*********************************************************************************************************//**
* @param[in] num	: Block inq number
* @retval
*	return IFER
* @brief
*	Block Inq 구조체에 정의된 것에 따라서 Tx Packet을 만든다.
*************************************************************************************************************/
IFER PtcViscaBlckInq(uint08 num)
{
	IFEVT_BLOCK_INQ *block_inq;
	uint08 i = 0,j = 0;
	uint16 lng = 0;
	uint32 data = 0;
	uint16 bits1fill[9] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
	IFU_DECODE_MAPING *evts;
	IFER err = IF_ERNO;

	switch(num)
	{
		case 0:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ0;		break;
		case 1:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ1;		break;
		case 2:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ2;		break;
		case 3:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ3;		break;
		case 4:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ4;		break;
		case 5:		block_inq = (IFEVT_BLOCK_INQ *)PTC_VSC_BLOCK_INQ5;		break;
		default:
			return IF_SYNTEX;
		break;
	}
	for(i=0;i<16;i++)	//Claer buf
		Tx_Packet[i] = 0;

	for(i=0 ; block_inq[i].eepidx != IDX_NULL;i++)
	{
		err = IF_ERNO;
		data = IF_EEPViscaUpdate(IFEVT_GETVAL,block_inq[i].eepidx,0);
		if(data == -1)
			err = SendEvent(IFEVT_VISCA_INQ,block_inq[i].eepidx,&data);

		if(block_inq[i].length < 8)
		{
			if(err == IF_ERNO)
			{	//Eep 구조체에 저장되는 값과 출력해주는 값이 다를 경우.
				switch(block_inq[i].eepidx)
				{
					case VDX_PWR_ON:
					case VDX_F_MODE:
					case VDX_AF_SENS:
					case VDX_STB_ON:
						evts = _Map_dat_Off_On;
						break;
					case VDX_WD_MODE :
						evts = 0;
#if VISCA_COMPILE == VSC_TYPE_EH6300
						switch(data)
						{
							case 0://Auto
								data = 2;
							break;
							case 1://Ratio Fix
								data = 3;
							break;
							case 2://On
								data = 1;
							break;
							case 3://Off
								data = 0;
							break;
							case 4://Dver Compati
								data = 4;
							break;
						}
#else
						switch(data)
						{
							case 0://Auto
								data = 1;
							break;
							case 1://Ratio Fix
								data = 0;
							break;
							case 2://On
								data = 2;
							break;
						}
#endif
						break;
					default : evts = 0;	break;
				}
				if(evts)	Processong_INQ(DECODE_MAPING,block_inq[i].eepidx,&data,evts);

				Tx_Packet[block_inq[i].stt_byte] |= (data & bits1fill[block_inq[i].length]) << block_inq[i].stt_bit;

			}
#ifdef WIN32
			printf("Packet[%2d]bit[%d] = %4d ",block_inq[i].stt_byte,block_inq[i].stt_bit,data);
			printf("Packet[%2d] = %4X err[%d]\n",block_inq[i].stt_byte,(data & bits1fill[block_inq[i].length]) << block_inq[i].stt_bit,err);
#endif
		}
		else
		{
			switch(block_inq[i].eepidx)
			{
				case VDX_NEAR_LIMIT :
					data >>= 8;
				break;
			}
			lng = (block_inq[i].length - 1)/4;
			if(err == IF_ERNO)
			{
				for(j=0;j<lng + 1;j++)
				{
					Tx_Packet[block_inq[i].stt_byte + lng - j] = (data>>(j<<2))&0x0f;
				}
			}
		}
	}

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Visca ZmFcs의 명령의 \n 데이터 검증(값, 범위) 및 이벤트 처리
*************************************************************************************************************/
IFER Vsc_DecodeDat_CMDZmFcs()
{
	IFER er = IF_ERNO;
	IFER evt_result = IF_ERNOPROC;
	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Cmd[gDecode];

	uint32 data;
	uint32 data_lng;

	data = 0;
	data_lng = gPtcBuf.VISCA_PTC.LENGTH - 4;

	Compose_data(COMPOSE_D_HALF,8,&gPtcBuf.data[4],&data);//zoom Fcs

	if(!Visca_Condition_Check(pCodec->eepidx,data))
	{
		if(!g_ViscaData.FLD.PWR_ON)
			evt_result = SendEvent(IFEVT_VISCA_CMD, VDX_ZM_FCS_POS,&data);
		else
			er = IF_INVALIDVAL;

		switch(evt_result)
		{
			case IF_ERNOPROC :	//처리하지 않음 : 내부적으로 처리할수 없다.
				er |= IF_NOEXCUTE;
			break;
			case IF_INVALIDVAL : //처리할수 없는 값임
				er |= IF_NOEXCUTE;
			break;
			default:
				//Syntex Error Chk
			break;
		}
	}
	else
		er = IF_NOEXCUTE;

	return er;
}

/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Visca 복수의 이벤트를 갖는 명령의 데이터들의 \n 검증(값, 범위) 및 이벤트 처리\n
*	예외적 처리\n
*		Title 명령어 : 같은 명령임에도 발생되는 이벤트 몇 변경시키는 구조체의 위치가 달라진다.\n
*************************************************************************************************************/
IFER Vsc_DecodeDat_CMDs()
{
	IFER er = IF_ERNO;
	IFER evt_result = IF_ERNOPROC;
	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Cmd[gDecode];

	uint32 data = 0;
	uint08 acc = 4;

	uint08 txt_cmd;
	uint08 cnt;		//계수

	PLURAL_EVT *plu_evt;

	if(pCodec->evts)
	{
		/********** Exception!! : Title CMD ******************/
		if(pCodec->eepidx == VDX_TITLE_SET)
		{
			txt_cmd = gPtcBuf.VISCA_PTC.MSG1>>4;
			switch(txt_cmd)
			{
				case 1:
					plu_evt = (PLURAL_EVT *)PluralEvt_TitleSet1;
				break;
				case 2:
					plu_evt = (PLURAL_EVT *)PluralEvt_TitleSet2;
				break;
				case 3:
					plu_evt = (PLURAL_EVT *)PluralEvt_TitleSet3;
				break;
				default:
					return IF_NOEXCUTE;
				break;
			}
		}
		else
			plu_evt = (PLURAL_EVT *)pCodec->evts;
		/********** Exception End ***************************/
		for(cnt = 0; plu_evt[cnt].eepidx != IDX_NULL ;cnt++)
		{
			Compose_data(plu_evt[cnt].type, plu_evt[cnt].length, &gPtcBuf.data[acc], &data);

			if(!Visca_Condition_Check(plu_evt[cnt].eepidx,data))
			{
				if(!g_ViscaData.FLD.PWR_ON)	//PWR_ON : ON(1) ,OFF(0)
				{
					evt_result = SendEvent(IFEVT_VISCA_CMD, plu_evt[cnt].eepidx,&data);
				}
				else
				{
					evt_result = IF_ERNO;
					er |= Processong_CMD_Value_Chk(plu_evt[cnt].decode_type ,plu_evt[cnt].eepidx ,data ,(void *)plu_evt[cnt].evts);
					if(!er)
						er = IF_NOEXCUTE;
				}
				switch(evt_result)
				{
					case IF_ERNOPROC :	 // 처리하지 않음
						er |= Processong_CMD_Value_Chk(plu_evt[cnt].decode_type ,plu_evt[cnt].eepidx ,data ,(void *)plu_evt[cnt].evts);
						if(!er)
							er |= Processong_CMD(plu_evt[cnt].decode_type ,plu_evt[cnt].eepidx ,data ,(void *)plu_evt[cnt].evts);
					break;
					case IF_INVALIDVAL : // 처리할수 없음
						er |= IF_NOEXCUTE;
					break;
					default:
					break;
				}
			}
			else
				er = IF_NOEXCUTE;
			acc += plu_evt[cnt].length;
		}
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Visca 단수의 이벤트를 갖는 명령의 데이터들의 검증(값, 범위) 및 이벤트 처리	\n
*	예외적 처리\n
*		Extent 명령어 : 하나의 CMD(0x1F)에서 서로다른 이벤트가 발생됨(다른 변수를 바꿈).
*************************************************************************************************************/
IFER Vsc_DecodeDat_CMD()
{
	IFER er = IF_ERNO;
	IFER evt_result = IF_ERNOPROC;
	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Cmd[gDecode];

	uint32 data = 0;
	uint32 data_lng = gPtcBuf.VISCA_PTC.LENGTH - 4;
	uint08 cnt;

	/********** Exception!! : Expend CMD ******************/
	if(gPtcBuf.VISCA_PTC.CMD == 0x1F)
	{
		for(cnt = 0; gPtcVisca_Ext_Cmd[cnt].eepidx != IDX_NULL;cnt++)
		{	//복수의 명령처리
			if(gPtcVisca_Ext_Cmd[cnt].cmd == gPtcBuf.VISCA_PTC.MSG1)
			{
				pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Ext_Cmd[cnt];
				data_lng--;
				break;
			}
		}
		if(data_lng == 2)
			Compose_data(COMPOSE_D_FULL,data_lng,&gPtcBuf.data[5],&data);
		else
			Compose_data(COMPOSE_D_HALF,data_lng,&gPtcBuf.data[5],&data);
	}
	/********** Exception End ***************************/
	else
	{	//Normal CMD
		if(data_lng == 1)
			Compose_data(COMPOSE_D_FULL,data_lng,&gPtcBuf.data[4],&data);
		else
			Compose_data(COMPOSE_D_HALF,data_lng,&gPtcBuf.data[4],&data);
	}

	if(!Visca_Condition_Check(pCodec->eepidx,data))
	{
		if((!g_ViscaData.FLD.PWR_ON) || pCodec->eepidx == VDX_PWR_ON)
			evt_result = SendEvent(IFEVT_VISCA_CMD, pCodec->eepidx,&data);
		else
		{
			evt_result = IF_ERNO;
			er = Processong_CMD_Value_Chk(pCodec->decode_type ,pCodec->eepidx ,data ,(void *)pCodec->evts);
			if(!er)
				er = IF_NOEXCUTE;
		}

		switch(evt_result)
		{
			case IF_ERNOPROC :  //처리하지 않음
				er |= Processong_CMD_Value_Chk(pCodec->decode_type ,pCodec->eepidx ,data ,(void *)pCodec->evts);
				if(!er)
					er |= Processong_CMD(pCodec->decode_type ,pCodec->eepidx ,data ,(void *)pCodec->evts);
			break;
			case IF_INVALIDVAL : //처리할수 없음
				er |= IF_NOEXCUTE;
			break;
			default:
			break;
		}
	}
	else
		er = IF_NOEXCUTE;
	return er;
}

/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Packet의 검증이 끝났을 경우 \n
*	Visca 명령의 데이터들의 검증(값, 범위) 및 이벤트 처리	\n
*************************************************************************************************************/
IFER PtcViscaCMDProc()
{
	IFER er = IF_ERNOPROC;
	uint32 data_lng = gPtcBuf.VISCA_PTC.LENGTH - 4;

	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Cmd[gDecode];

#ifdef WIN32
	uint08 cnt;

	printf("\nHD:%02X, TYPE:%02X%02X, CMD:%02X\n",gPtcBuf.VISCA_PTC.HEADER , gPtcBuf.VISCA_PTC.TYPE1,gPtcBuf.VISCA_PTC.TYPE2, gPtcBuf.VISCA_PTC.CMD);
	for(cnt = 0;cnt<16;cnt++)	printf("%02x ",gPtcBuf.data[cnt]);
	printf("%\n ");
#else
	#if 0
	DebugScrPrintf(1,1,"\nHD:%02X, TYPE:%02X%02X, CMD:%02X\n",gPtcBuf.VISCA_PTC.HEADER , gPtcBuf.VISCA_PTC.TYPE1,gPtcBuf.VISCA_PTC.TYPE2, gPtcBuf.VISCA_PTC.CMD);
	for(cnt = 0;cnt<16;cnt++)	DebugScrPrintf(2,3*cnt,"%02x ",gPtcBuf.data[cnt]);
	#endif
#endif
	/********************************CMD TYPE***********************************/
	//  에러처리 방침
	//	1. Command		-> Syntex
	//	2. Condition	-> Not Excute
	//	3. Value Chk	-> Syntex
	//	4. Event		-> 	IF_ERNOPROC		: Syntex
	//						IF_INVALIDVAL	: Not Excute

	if((pCodec->eepidx == VDX_ZOOM_POS) && (data_lng == 8))
	{
		er = Vsc_DecodeDat_CMDZmFcs();	//예외적인 처리 Zoom/Focus CMS
	}
	else if(pCodec->decode_type == DECODE_PLURAL)
	{	//복수의 변수 처리
		er = Vsc_DecodeDat_CMDs();
	}
	else
	{
		er = Vsc_DecodeDat_CMD();
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Visca 복수의 이벤트를 갖는 명령의 데이터들의 검증(값, 범위) 및 이벤트 처리	\n
*************************************************************************************************************/
IFER Vsc_DecodeDat_INQs()
{
	IFER er = IF_ERNO;
	IFER evt_result = IF_ERNOPROC;

	uint32 data;
	uint32 inq_data;

	uint08 cnt;		//계수
	uint08 acc = 2;
	PLURAL_EVT *plu_evt;
	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Inq[gDecode];

	data = gPtcBuf.data[4];

	if(pCodec->evts)
	{
		plu_evt = (PLURAL_EVT *)pCodec->evts;

		if(plu_evt[0].eepidx == VDX_RECIEVE_DATA)
			//입력이 있음
			cnt = 1;
		else
			cnt = 0;

		for(; plu_evt[cnt].eepidx != IDX_NULL ;cnt++)
		{
			inq_data = data;

			evt_result = SendEvent(IFEVT_VISCA_INQ ,plu_evt[cnt].eepidx ,&inq_data);
			switch(evt_result)
			{
				case IF_ERNOPROC :   //처리하지 않음
					er |= Processong_INQ(plu_evt[cnt].decode_type ,plu_evt[cnt].eepidx,&inq_data ,(void *)plu_evt[cnt].evts);
				break;
				case IF_INVALIDVAL : //처리할수 없음
					er |= IF_NOEXCUTE;
				break;
				default:
				break;
			}
			Relieve_data(plu_evt[cnt].type ,plu_evt[cnt].length ,&Tx_Packet[acc] ,inq_data);
			acc += plu_evt[cnt].length;
		}
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Visca 단수의 이벤트를 갖는 명령의 데이터들의 검증(값, 범위) 및 이벤트 처리	\n
*	예외적 처리\n
*		Extent 명령어 : 하나의 CMD(0x1F)에서 서로다른 이벤트가 발생됨(다른 변수를 바꿈).
*************************************************************************************************************/
IFER Vsc_DecodeDat_INQ()
{
	IFER er = IF_ERNO;
	IFER evt_result = IF_ERNOPROC;

	uint32 inq_data;
	uint08 cnt;
	uint08 acc = 2;

	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Inq[gDecode];

	if(gPtcBuf.VISCA_PTC.CMD == 0x1F)
	{
		for(cnt = 0; gPtcVisca_Ext_Inq[cnt].eepidx != IDX_NULL;cnt++)
		{
			if(gPtcVisca_Ext_Inq[cnt].cmd == gPtcBuf.VISCA_PTC.MSG1)
			{
				pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Ext_Inq[cnt];
				gPtcBuf.VISCA_PTC.LENGTH = pCodec->length;
				break;
			}
		}
		inq_data = gPtcBuf.VISCA_PTC.MSG2;
	}

	evt_result = SendEvent(IFEVT_VISCA_INQ,pCodec->eepidx,&inq_data);
	switch(evt_result)
	{
		case IF_ERNOPROC :	 //처리하지 않음
			er |= Processong_INQ(pCodec->decode_type,pCodec->eepidx,&inq_data ,(void *)pCodec->evts);
		break;
		case IF_INVALIDVAL : //처리할수 없음
			er |= IF_NOEXCUTE;
		break;
		default:
		break;
	}

	if(pCodec->length == 1)
		Relieve_data(COMPOSE_D_FULL, 1,&Tx_Packet[acc],inq_data);
	else
		Relieve_data(COMPOSE_D_HALF, pCodec->length, &Tx_Packet[acc], inq_data);

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result IFER
* @brief
*	Packet의 검증이 끝났을 경우 \n
*	Visca INQ 명령의 데이터들의 검증(값, 범위) 및 이벤트 처리	\n
*************************************************************************************************************/
IFER PtcViscaINQProc()
{
	IFER er = IF_ERNO;

	PTC_VISCA_CODEC *pCodec = (PTC_VISCA_CODEC *)&gPtcVisca_Inq[gDecode];
	/********************************INQ TYPE***********************************/

	if(pCodec->decode_type == DECODE_PLURAL)
	{	//복수의 데이터
		er = Vsc_DecodeDat_INQs();
	}
	else
	{
		er = Vsc_DecodeDat_INQ();
	}

	return er;
}
/*********************************************************************************************************//**
* @param[in] buf	: 버퍼 포인터
* @param[in] shft	: 크기
* @param[in] size	: 커서 포인터
* @retval
*	none
* @brief
*	버퍼 포인터의 1Byte 배열에 값을 Shift 시칸다. \n
*	아래 배열을(*은 현제 커서)\n
*	[01][02][00][04][27][00]...[00][01][*04]\n
*	3칸 shift 시키면 \n
*	[04][27][00]...[00][01][*04][00][00][00]\n
*************************************************************************************************************/
IFER PtcShiftBuf(uint08* buf,uint08 shft,uint16 *size)
{
	uint16 i;
	if(shft==0)	return 0;

	for(i=shft;i<(*size+shft);i++)
	{
		buf[i-shft] = buf[i];
		buf[i] = 0;
	}
	*size -= shft;

	if(*size > MAX_PTCBUF) *size = 0;
	return 0;
}
/*********************************************************************************************************//**
* @param[in] end_size : 패킷의 FF 위치
* @retval
*	return IFER
* @brief
*	패킷의 지원 여부 및 크기가 올바른지 검출한다.
*	예외 처리
*		1. Extend Cmd		: Packet size가 바뀐다.
*		2. Zoom Focus Cmd	: Packet size가 바뀐다.
*************************************************************************************************************/
IFER Vsc_Decode_CMD_Size(uint32 end_size)
{
	IFER er = IF_ERNO;
	uint32 end_chk_pos = 0;

	gDecode = Find_Visca_CMD_Idx(gPtcBuf.VISCA_PTC.CMD);

	if(gDecode == -1)
	{
		er = IF_SYNTEX;
	}
	else
	{
		if(end_size - 4 == gPtcVisca_Cmd[gDecode].length)
			end_chk_pos = gPtcVisca_Cmd[gDecode].length + 4;
		//Exception : EXTEND 명령어 ( 8x 01 04 1F 4F ~//~ FF)
		else if(gPtcBuf.VISCA_PTC.CMD == 0x1F)
		{
			er = IF_ERNO;
			switch(gPtcBuf.VISCA_PTC.MSG1)
			{
				case 0x02 : end_chk_pos = 7;	break;
				case 0x0E : end_chk_pos = 7;	break;
				case 0x21 : end_chk_pos = 9;	break;
				case 0x42 : end_chk_pos = 9;	break;
				case 0x49 : end_chk_pos = 9;	break;
				case 0x4E : end_chk_pos = 9;	break;
				case 0x4F : end_chk_pos = 9;	break;
				default:
					er = IF_SYNTEX;
				break;
			}
		}//Exception end
		else
			end_chk_pos = 0;

		if(gPtcBuf.data[end_chk_pos] != 0xff)
		{	//0xFF 위치 검사
			if(gPtcVisca_Cmd[gDecode].eepidx == VDX_ZOOM_POS)
			{	//Exception : Zoom/Focus 명령어
				if((gPtcBuf.data[12] == 0xFF) && (end_size == 12))
				{
					end_chk_pos = 12;
					er = IF_ERNO;
				}
				else
				{
					end_chk_pos = 0;
					er = IF_SYNTEX;
				}
			}//Exception end
			else
			{
				end_chk_pos = 0;
				er = IF_SYNTEX;
			}
		}
		else
		{
			er = IF_ERNO;
		}
	}

	gPtcBuf.VISCA_PTC.LENGTH = end_chk_pos;	//Size

	return er;
}
/*********************************************************************************************************//**
* @param[in] end_size : 패킷의 FF 위치
* @retval
*	return IFER
* @brief
*	패킷의 지원 여부 및 크기가 올바른지 검출한다.
*	예외 처리
*		1. Extend Cmd		: Packet size가 바뀐다.
*************************************************************************************************************/
IFER Vsc_Decode_INQ_Size(uint32 end_size)
{
	IFER er = IF_ERNO;
	uint32 end_chk_pos = 0;

	gDecode = Find_Visca_INQ_Idx(gPtcBuf.VISCA_PTC.CMD);

	if(gDecode == -1)
	{
		er = IF_SYNTEX;
	}
	else
	{//Size 검사
		if(gPtcVisca_Inq[gDecode].decode_type == DECODE_PLURAL)
		{
			PLURAL_EVT *plu_evt;
			if(gPtcVisca_Inq[gDecode].evts)
			{
				plu_evt = (PLURAL_EVT *)gPtcVisca_Inq[gDecode].evts;
				if(plu_evt[0].eepidx == VDX_RECIEVE_DATA)
					end_chk_pos = 5; //입력에 따른 INQ
				else
					end_chk_pos = 4; //Datas INQ
			}
		}
		else
			end_chk_pos = 4;	//a Data INQ

		if(gPtcBuf.VISCA_PTC.CMD == 0x1F)
		{	//Exception : Extend 인쿼리
			switch(gPtcBuf.VISCA_PTC.MSG1)
			{
				case 0x21:	end_chk_pos = 6;	break;
				case 0x42:	end_chk_pos = 5;	break;
				case 0x49:	end_chk_pos = 6;	break;
				case 0x4E:	end_chk_pos = 5;	break;
				case 0x4F:	end_chk_pos = 6;	break;
				default :	end_chk_pos = 0;	break;
			}
		}//Exception end

		if(gPtcBuf.data[end_chk_pos] == 0xff)
		{
			er = IF_ERNO;
		}
		else
		{
			er = IF_SYNTEX;
		}
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	Version Inq에 대한 패킷 검사, 데이터 및 이벤트 처리를 해준다.
*************************************************************************************************************/
IFER Vsc_Decode_VerINQ_Size()
{
	IFER er = IF_ERNO;
	uint32 data = 0;

	if(gPtcBuf.VISCA_PTC.CMD == 0x02 && gPtcBuf.VISCA_PTC.MSG1 == 0xff)
	{
		data = 0x0020;
		Relieve_data(COMPOSE_D_FULL,2 ,&Tx_Packet[2] ,0x0020);

	#if (VISCA_COMPILE == VSC_TYPE_EH6300)
		data = 0x045F;
	#elif (VISCA_COMPILE == VSC_TYPE_EV7100)
		data = 0x0468;
	#else
		data = 0x0468;
	#endif
		SendEvent(IFEVT_VISCA_INQ,VDX_MODEL_CODE,&data);
		Relieve_data(COMPOSE_D_FULL,2 ,&Tx_Packet[4] ,data);
		data = 0x0200;
		SendEvent(IFEVT_VISCA_INQ,VDX_ROM_VERSION,&data);
		Relieve_data(COMPOSE_D_FULL,2 ,&Tx_Packet[6] ,data);
		data = 0x02;
		SendEvent(IFEVT_VISCA_INQ,VDX_SOCKET_NUM,&data);
		Relieve_data(COMPOSE_D_FULL,1 ,&Tx_Packet[8] ,data);
	}
	else
	{
		er = IF_SYNTEX;
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	Block Inq에 대한 패킷 검사.
*************************************************************************************************************/
IFER Vsc_Decode_Block_INQ_Size()
{
	IFER er = IF_ERNO;

	if(gPtcBuf.VISCA_PTC.CMD == 0x7E && gPtcBuf.VISCA_PTC.MSG2 == 0xff)
	{
		if(gPtcBuf.VISCA_PTC.MSG1>5)
		{
			er = IF_SYNTEX;
		}
		else
		{
			er = IF_ERNO;
		}
	}
	else
	{
		er = IF_SYNTEX;
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	return IFER
* @brief
*	Visca Protocol의 Main Process
*************************************************************************************************************/
IFER PtcViscaProc()
{
	IFER er = IF_ERNO;
	uint08 stx;
	COMPLETE_MSG_TYPE complete_type = COMPLETE_MSG_NONE;

	uint32 end_size = 0;
	uint32 hd_size = 0;
	uint32 hd_size_tmp = 0;
	uint32 send_size = 0;
	uint16 shft = 0;

	uint08 flg = 1; // 처음 1회만 함수에 진입함.
#ifdef WIN32
	uint08 i = 0;
	uint08 j = 0;
#endif

	/* Send */
	hd_size = PtcVisca_FndHD(gPtcBuf.data,gPtcCursor);

	if(hd_size != -1)
	{
		end_size = PtcVisca_FndFF(gPtcBuf.data,gPtcCursor);
 		hd_size_tmp = PtcVisca_FndHD(&gPtcBuf.data[hd_size+1],gPtcCursor - (hd_size+1));

		while((hd_size_tmp != -1) /*&& (end_size != -1)*/ && ((hd_size+hd_size_tmp+1) < end_size))
		{
			hd_size += hd_size_tmp+1;
			hd_size_tmp = PtcVisca_FndHD(&gPtcBuf.data[hd_size+1],gPtcCursor - (hd_size+1));
		}
		PtcShiftBuf(gPtcBuf.data,hd_size,&gPtcCursor);
		if(end_size != -1)
			end_size -= hd_size;
		hd_size = 0;
	}

	//if(hd_size != -1 && end_size != -1)
	while(hd_size != -1 && end_size != -1 && flg) // 1vd에 1패킷을 처리하지만 반송되는 명령어는 여러 패킷을 처리한다.
	{
		er = IF_ERNO;
		flg = 0;		//clear

		if(gPtcBuf.data[hd_size]&0x80)
		{
#ifdef WIN32
	#if 1
				printf("Cur[%d]",gPtcCursor);
				for(j = 0;j<16;j++)	printf("%02x ",gPtcBuf.data[j]);
				printf("\n ");
	#endif
#else
	#if 0
				static uint16 cnt_func = 0;
				cnt_func++;
				DebugPrintf("Cur[%d %d %d]",gPtcCursor,cnt_func,end_size);
				for(j = 0;j<16;j++)
					DebugPrintf("%02x ",gPtcBuf.data[j]);
				DebugPrintf("\n");
	#endif
#endif
			//명령어 처리
			stx = gPtcBuf.data[0]&0x0F;

			if(gPtc_Visca_Addr == stx)	//어드레스 일치
			{
				if(gPtcBuf.VISCA_PTC.TYPE1 == 0x38 && end_size == 2)
				{
					//NetWork Change -> 무시 (Sony FCB-EH6300과 비교)
					PtcShiftBuf(gPtcBuf.data,2,&gPtcCursor);
					return IF_ERNO;
				}
				else if(gPtcBuf.VISCA_PTC.TYPE2 == 0x06 && gPtcBuf.VISCA_PTC.CMD == 0x06)
				{
					if(g_ViscaData.FLD.PWR_ON)
					{
						gPtcBuf.VISCA_PTC.TYPE2 = 0x04;
						gPtcBuf.VISCA_PTC.CMD = 0x15;
					}
				}

				/*** DECODING ******************************CMD DECODING**********************************/
				if(gPtcBuf.VISCA_PTC.TYPE1 == 0x01  && gPtcBuf.VISCA_PTC.TYPE2 == 0x04)
				{
					er = Vsc_Decode_CMD_Size(end_size);

					complete_type = COMPLETE_MSG_CMD;
					shft = gPtcBuf.VISCA_PTC.LENGTH + 1;
					end_size = 0;
				}
				/*** DECODING ******************************INQ DECODING**********************************/
				else if(gPtcBuf.VISCA_PTC.TYPE1 == 0x09 && gPtcBuf.VISCA_PTC.TYPE2 == 0x04)
				{
					er = Vsc_Decode_INQ_Size(end_size);

					complete_type = COMPLETE_MSG_INQ;
					shft = gPtcBuf.VISCA_PTC.LENGTH + 1;
					end_size = 0;
				}
				/*** DECODING ******************************BLCOK INQ DECODING******************************/
				else if(gPtcBuf.VISCA_PTC.TYPE1 == 0x09 && gPtcBuf.VISCA_PTC.TYPE2 == 0x7E)
				{
					er = Vsc_Decode_Block_INQ_Size();

					complete_type = COMPLETE_MSG_BLOCK_INQ;
					send_size = 13;
					shft = 6;
				}
				/*** DECODING ****************************** 기타 예외처리 **********************************/
				else if(gPtcBuf.VISCA_PTC.TYPE1 == 0x09 && gPtcBuf.VISCA_PTC.TYPE2 == 0x00)
				{	//Exception : Version INQ
					er = Vsc_Decode_VerINQ_Size();

					shft = 5;
					complete_type = COMPLETE_MSG_VER_INQ;
					send_size = 7;
				}//Exception End
				else if(gPtcBuf.VISCA_PTC.TYPE1 == 0x01 && gPtcBuf.VISCA_PTC.TYPE2 == 0x00)
				{	//Exception : IF_Clear (실행중인 명령 중지.)
					if(gPtcBuf.VISCA_PTC.CMD == 0x01 && gPtcBuf.VISCA_PTC.MSG1 == 0xff)
					{
						er = IF_ERNO;
					}
					else
					{
						er = IF_SYNTEX;
					}

					shft = 5;
					send_size = 0;
					end_size = 0;
					complete_type = COMPLETE_MSG_VER_INQ;
				}//Exception End
				else
				{
					shft = 4;
					er = IF_SYNTEX;
				}

				if(er)
				{
					complete_type = COMPLETE_MSG_NONE;
					gPtcBuf.VISCA_PTC.LENGTH = 0;
					shft = 4;
					end_size = 0;
				}

				/*************************************PROCESSING**********************************/
				if(er == IF_ERNO)
				{	//처리 : 이벤트 발생,저장,전송 패킷 생성
					switch(complete_type)
					{
						case COMPLETE_MSG_CMD:
							er = PtcViscaCMDProc();
							if(!er)
								PtcVisca_SendPacket(VISCA_MSG_ACKNOWLEDGE,0,0);	//데이터가 써졌을 때
						break;
						case COMPLETE_MSG_INQ:
							er = PtcViscaINQProc();
						break;
						case COMPLETE_MSG_BLOCK_INQ:
							er = PtcViscaBlckInq(gPtcBuf.VISCA_PTC.MSG1);
						break;
						default:
						break;
					}
				}
				/*************************************RESPONSE***********************************/
				if((er & 0x7) == IF_ERNO)
				{	//Respons Packet 전송
					switch(complete_type)
					{
						case COMPLETE_MSG_CMD:
							PtcVisca_SendPacket(VISCA_MSG_COMPETE_CMD,0,0);
						break;
						case COMPLETE_MSG_INQ:
							if(gPtcBuf.VISCA_PTC.CMD == 0x1F)
								send_size = gPtcBuf.VISCA_PTC.LENGTH;
							else
								send_size = gPtcVisca_Inq[gDecode].length;
						case COMPLETE_MSG_BLOCK_INQ:
						case COMPLETE_MSG_VER_INQ :
							PtcVisca_SendPacket(VISCA_MSG_COMPETE_INQ,&Tx_Packet[2],send_size);
						break;
						default:
						break;
					}
				}
				else if((er & 0x1) == IF_SYNTEX)
					PtcVisca_SendPacket(VISCA_ERROR_SYNTEX,0,0);
				else if((er & 0x2) == IF_LENGTH)
					PtcVisca_SendPacket(VISCA_ERROR_SYNTEX,0,0);
				else if((er & 0x4) == IF_NOEXCUTE)
					PtcVisca_SendPacket(VISCA_ERROR_COMMAND_EXCUTABLE,0,0);
				/***********************************Packet Claer********************************/
				if(shft)
					PtcShiftBuf(gPtcBuf.data,shft,&gPtcCursor);
			}
			else if(gPtcBuf.data[0] == 0x88)//broad cast
			{	//Header 0x88 : Global Packet
				if(gPtcBuf.VISCA_PTC.TYPE1 == 0x30)
				{
					if(gPtcBuf.data[3] == 0xFF)
					{
						if(gPtcBuf.data[2] !=0 && gPtcBuf.data[2] <= 7)
						{
							shft = 4;
							gPtc_Visca_Addr = gPtcBuf.data[2];
							PtcVisca_SendPacket(VISCA_MSG_GLB_ADDSET,0,0);
						}
						else if(gPtcBuf.data[2] < 0x7F)
						{
							shft = gPtc_Visca_Addr;
							gPtc_Visca_Addr = gPtcBuf.data[2];
							PtcVisca_SendPacket(VISCA_MSG_GLB_ADDSET,0,0);
							gPtc_Visca_Addr = shft;
							shft = 3;
						}
						else if(gPtcBuf.data[2] == 0x7F)
						{
							shft = gPtc_Visca_Addr;
							gPtc_Visca_Addr = 0x7E;
							PtcVisca_SendPacket(VISCA_MSG_GLB_ADDSET,0,0);
							gPtc_Visca_Addr = shft;
							shft = 3;
						}
						else
						{
							shft = 3;
						}
					}
					else
					{
						er = IF_ERNOPROC;
						shft = 3;
					}
				}
				else
				{
					er = IF_ERNOPROC;
				}

				if(er != IF_ERNO)
				{
					flg = 1;
					if(end_size < 16)
					{
						PtcSendBuf(gPtcBuf.data,end_size+1);
						shft = end_size+1;
					}
					else
					{
						shft = 16;
					}
				}
				PtcShiftBuf(gPtcBuf.data,shft,&gPtcCursor);
			}
			else
			{	//헤더가 다르면 반송시킴
				if(end_size < 16)
				{
					PtcSendBuf(gPtcBuf.data,end_size+1);
					PtcShiftBuf(gPtcBuf.data,end_size+1,&gPtcCursor);
				}
				else
				{
					PtcShiftBuf(gPtcBuf.data,16,&gPtcCursor);
				}
			}
		}

		hd_size = PtcVisca_FndHD(gPtcBuf.data,gPtcCursor);

		if(hd_size != -1)
		{
			end_size = PtcVisca_FndFF(gPtcBuf.data,gPtcCursor);
	 		hd_size_tmp = PtcVisca_FndHD(&gPtcBuf.data[hd_size+1],gPtcCursor - (hd_size+1));

			while((hd_size_tmp != -1) /*&& (end_size != -1)*/ && ((hd_size+hd_size_tmp+1) < end_size))
			{
				hd_size += hd_size_tmp+1;
				hd_size_tmp = PtcVisca_FndHD(&gPtcBuf.data[hd_size+1],gPtcCursor - (hd_size+1));
			}
			PtcShiftBuf(gPtcBuf.data,hd_size,&gPtcCursor);
			if(end_size != -1)
				end_size -= hd_size;
			hd_size = 0;
		}
	}

	if(hd_size == -1)	PtcShiftBuf(gPtcBuf.data,gPtcCursor,&gPtcCursor);

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @retval
*	Return : IFER
* @brief
*	프로토콜 함수의 메인 테스크
*	어떤 Protocol Process에 들어갈지 결정해준다.
*************************************************************************************************************/
IFER PtcTask()
{
	IFER er = IF_ERNO;
	if((g_OsdData.FLD.PROTOCOL == 3) &&(gPtcl_init_flg))
	{
		PtcVisca_SendPacket(VISCA_MSG_NETWORK_CHANGE,0,0);
		gPtcl_init_flg = 0;
	}

	if(gPtcCursor > 0)
	{
		if(gPtc_CNBH_Flg)
		{
			PtcCNBHTeckProc();
		}
		else
		{
			switch(g_OsdData.FLD.PROTOCOL)
			{
				case 3:	//Visca
					er = PtcViscaProc();
				break;
			}
		}
	}

	return er;
}

/*********************************************************************************************************//**
* @param[in] buf : 의미없다
* @retval
*	none
* @brief
*	Null 함수 : 함수를 초기화 하는 데 사용한다.
*	CallBack 함수로 등록하지 않으면 이 함수를 Call한다.
*************************************************************************************************************/
void PtcSendCallNull(uint08 buf)
{
	volatile uint08 tmp = 0;
	tmp = 1;
}

/*********************************************************************************************************//**
* @param[in] md : 0(On->off) , 1(off->on)
* @retval
*	none
* @brief
*	MD Reply\n
*	Visca Reply를 전송하는 함수\n
*	함수를 콜하면 바로 Reply Tx가 나가게 된다.\n
*************************************************************************************************************/
IFER IF_Send_Reply_MD(uint08 md)
{

	if(!g_ViscaData.FLD.MD_ON) return IF_INVALIDVAL;
	if(md > 0x0f)	return IF_INVALIDVAL;
	Tx_Packet[3] = 0x1B;
	Tx_Packet[4] = md;

	PtcVisca_SendPacket(VISCA_MSG_REPLY,&Tx_Packet[3],2);
	return IF_ERNO;
}
/*********************************************************************************************************//**
* @param[in] icr : 0(On->off) , 1(off->on)
* @retval
*	none
* @brief
*	ICR Reply\n
*	Visca Reply를 전송하는 함수\n
*	함수를 콜하면 바로 Reply Tx가 나가게 된다.\n
*************************************************************************************************************/
IFER IF_Send_Reply_ICR(uint08 icr)
{
	Tx_Packet[3] = 0x31;
	if(!g_ViscaData.FLD.AICR_ALARM_ON) return IF_INVALIDVAL;

	if(icr > 1)	return IF_INVALIDVAL;
	else if(icr == 0)	Tx_Packet[4] = 3;
	else if(icr == 1)	Tx_Packet[4] = 2;

	PtcVisca_SendPacket(VISCA_MSG_REPLY,&Tx_Packet[3],2);

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @param[in] wd : 0(On->off) , 1(off->on)
* @retval
*	none
* @brief
*	WD Reply\n
*	Visca Reply를 전송하는 함수\n
*	함수를 콜하면 바로 Reply Tx가 나가게 된다.\n
*************************************************************************************************************/
IFER IF_Send_Reply_WD(uint08 wd)
{
	Tx_Packet[3] = 0x3B;
	if(!g_ViscaData.FLD.WD_ALARM) return IF_INVALIDVAL;

	if(wd > 1)	return IF_INVALIDVAL;
	else if(wd == 1)	Tx_Packet[4] = 2;	//Off -> On
	else if(wd == 0)	Tx_Packet[4] = 3;	//On -> Off

	PtcVisca_SendPacket(VISCA_MSG_REPLY,&Tx_Packet[3],2);

	return IF_ERNO;
}
/*********************************************************************************************************//**
* @param[in] Zoom
* @param[in] dzoom
* @retval
*	none
* @brief
*	Zoom Reply\n
*	Visca Reply를 전송하는 함수\n
*	함수를 콜하면 바로 Reply Tx가 나가게 된다.\n
*************************************************************************************************************/
void IF_Send_Reply_Zoom(uint16 zoom,uint16 dzoom)
{
	if(!g_ViscaData.FLD.CZP_ON) return;
	Tx_Packet[3] = 0x69;

	Relieve_data(COMPOSE_D_HALF,2,&Tx_Packet[4],dzoom);
	Relieve_data(COMPOSE_D_HALF,4,&Tx_Packet[6],zoom);

	PtcVisca_SendPacket(VISCA_MSG_REPLY,&Tx_Packet[3],7);
}
/*********************************************************************************************************//**
* @param[in] focus : focus
* @retval
*	none
* @brief
*	Focus Reply\n
*	Visca Reply를 전송하는 함수\n
*	함수를 콜하면 바로 Reply Tx가 나가게 된다.\n
*************************************************************************************************************/
void IF_Send_Reply_Focus(uint16 focus)
{
	if(!g_ViscaData.FLD.CFP_ON) return;
	Tx_Packet[3] = 0x16;

	Relieve_data(COMPOSE_D_HALF,4,&Tx_Packet[4],focus);

	PtcVisca_SendPacket(VISCA_MSG_REPLY,&Tx_Packet[3],5);
}
/*********************************************************************************************************//**
* @param[in] bufsize : 버퍼의 크기
* @retval
*	none
* @brief
*	버퍼(Que) -> PRTCL 구조체(gPtcBuf) 로 데이터를 옮긴다.
*************************************************************************************************************/
void IF_PtcRecvBuf(uint08 bufsize)
{
	uint16 i = 0;
	uint16 j = 0;
	uint08 dat;

	for(i = 0; i < bufsize; i++)
	{
		if(gPtcCursor < MAX_PTCBUF)
		{
			dat = IF_PTC_GetRxQue();
			if((dat == 0xC9) && (!gPtc_CNBH_Flg))
			{
				//Ptc_Que.RxTail = ((Ptc_Que.RxTail + 255 - i) & IF_QUEUE_MASK);
				//gPtcCursor = 1;// 오동작을 일으킬수 있음.
				gPtcCursor = 0;
				gPtc_CNBH_Flg = 1;
				//return;
			}
			gPtcBuf.data[gPtcCursor++] = dat;
		}
		else
		{
			for(j=0; j < MAX_PTCBUF;j++)
				gPtcBuf.data[j] = 0;
			gPtcCursor = 0;
			if(g_OsdData.FLD.PROTOCOL == 3)
				PtcVisca_SendPacket(VISCA_ERROR_COMMAND_BUF_FULL,0,0);

			return;
		}
	}

}
/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/*********************************************************************************************************//**
* @param[in] none
* @retval none
* @brief
*   IF_MW 초기화
*************************************************************************************************************/
void IF_Initial()
{
	/* OSD */
	gKeyPrev = OSD_KEYNULL;
	gOsdMode = OSD_NORMAL;
	gOsdState = OSD_STATEOFF;
	gKeyCnt = 0;
	gTitleCursor = 0;
	gLineLimit = 0;
	MOTION_ZONE = 0;
	PRIVACY_ZONE = 0;

	/* Protocol */
	gPtcType = PTC_CNBH;
	gPtc_Visca_Addr = 1;
	gPtc_Visca_Socket = 1;
	gPtcl_init_flg = 1;//Network Change
	gPtc_CNBH_Flg = 0;
	Ptc_Que.RxHead = 0;
	Ptc_Que.RxTail = 0;
	Ptc_Que.TxHead = 0;
	Ptc_Que.TxTail = 0;

#ifdef WIN32
	printf("VISCA TYPE %s \n",VISCA_COMPILE == VSC_TYPE_EH6300 ? "EH6300":"EV7100");
#endif
}

/*********************************************************************************************************//**
* @param[in] key : 입력된 Key 값
* @retval
*	Result Error
* @brief
*   IF_OSD_TASK
*************************************************************************************************************/
IFER IF_Task(OSD_KEY key)
{
	IFER er = IF_ERNO;

	er = OsdTask(key);
#ifdef WIN32
	er = PtcTask();
#endif
	return er;
}

/*********************************************************************************************************//**
* @param[in] x : x
* @param[in] y : y
* @param[in] *arg : 문자열..
* @retval
*	Result Error
* @brief
*   Osd상에 x,y 지점에 해당 문자열을 Print해준다.
*************************************************************************************************************/
IFER IF_Trace(uint08 x, uint08 y, const char *arg,...)
{
	int08 ch;
	int08 *pstr = '\0';
	int32 d;
	va_list list;
/*
	if(IF_IsOsdOn() == OSD_STATEON && gOsdMode != OSD_HIDE)
	{
#ifdef WIN32
		return IF_ERNOPROC;
#endif
	}
*/
	va_start(list, arg);

	while(*arg)
	{
		if(*arg != '%')
		{
			PrintCall(x++, y, *arg++);
			continue;
		}
		else// if(arg[i] == '%')
		{
			arg++;

			switch(*arg)
			{
			case 'c':
				ch = (int)va_arg(list, int);
				PrintCall(x++, y, ch);
				break;

			case 'd':
				d = (int)va_arg(list, int);
				x += __itoa(x, y, d);
				break;

			case 'x':
				d = (int)va_arg(list, int);
				x += __xtoa(x, y, d, 'a');
				break;

			case 'X':
				d = (int)va_arg(list, int);
				x += __xtoa(x, y, d, 'A');
				break;

			case 's':
				pstr = (int08*)va_arg(list, int08 *);
				while((pstr != '\0') && *pstr)
					PrintCall(x++, y, *pstr++);
				pstr = '\0';
				break;

			default :
				PrintCall(x++, y, *arg);
				break;
			}

			arg++;
		}
	}

	va_end(list);

#ifdef WIN32
	Osd_Update_Flg(1);
#endif

	return IF_ERNO;
}

/*********************************************************************************************************//**
* @param[in] *EventCallback : 이벤트가 발생할 때 마다 CallBack 할 함수의 주소
* @retval
*	None
* @brief
*   이벤트가 발생할 시, CallBack 할 함수의 주소를 등록해 준다.
*	이벤트는 IF_Task(),IF_Task_Ptc()에 의해서 발생한다.
*************************************************************************************************************/
void IF_EventCallbackRegister(IFER (*EventCallback)(IFEVT, IFEVT_PARAM *))
{
	if(EventCallback != IF_NULL)
	{
		EventCall = EventCallback;
	}
}

/*********************************************************************************************************//**
* @param[in] *UEepUpdateCallback : User Eep R/W 할 함수 등록
* @retval
*	None
* @brief
*	User 변수를 R/W할 수 있는 함수를 등록한다
*	Task상에서 존재하지 않는 EEP_IDX의 값은 이 함수를 콜백해서 R/W하려는 시도를 한다.
*************************************************************************************************************/
void IF_UEepUpdateCallbackRegister(int32 (*UEepUpdateCallback)(IFEVT, EEP_IDX, int32))
{
	if(UEepUpdateCallback != IF_NULL)
	{
		UEepUpdateCall = UEepUpdateCallback;
	}
}

/*********************************************************************************************************//**
* @retval
*	return PRIVACY_ZONE
* @brief
*	OSD상에 선택된 Privacy Zone의 번호를 반환
*************************************************************************************************************/
int32 IF_EEPGetPrivZone()
{
	return PRIVACY_ZONE;
}
/*********************************************************************************************************//**
* @param[in] zone : PRIVACY_ZONE
* @retval
*	None
* @brief
*	OSD상에 선택된 Privacy Zone의 번호를 변경
*************************************************************************************************************/
void IF_EEPSetPrivZone(uint32 zone)
{
	PRIVACY_ZONE = zone;
}
/*********************************************************************************************************//**
* @retval
*	return MD_ZONE
* @brief
*	OSD상에 선택된 MD Zone의 번호를 반환
*************************************************************************************************************/
int32 IF_EEPGetMotionZone()
{
	return MOTION_ZONE;
}
/*********************************************************************************************************//**
* @param[in] zone : MD_ZONE
* @retval
*	None
* @brief
*	OSD상에 선택된 MD Zone의 번호를 변경
*************************************************************************************************************/
void IF_EEPSetMotionZone(uint32 zone)
{
	MOTION_ZONE = zone;
}
/*********************************************************************************************************//**
* @retval
*	return Pan
* @brief
*	현제 Pan값 반환
*	IF_Task_Ptc()에 의해서 변경됨.
*************************************************************************************************************/
int32 IF_GetCurPan()
{
	return CAM_Pan;
}
/*********************************************************************************************************//**
* @retval
*	return Tilt
* @brief
*	현제 Tilt값 반환
*	IF_Task_Ptc()에 의해서 변경됨.
*************************************************************************************************************/
int32 IF_GetCurTilt()
{
	return CAM_Tilt;
}

/*********************************************************************************************************//**
* @param[in] PrintCallback : Osd Putchar Funtion
* @retval
*	None
* @brief
*	x,y 지점에 1바이트의 Osd Font를 Print할 수 있게 해줌
*************************************************************************************************************/
void IF_OsdPrintCallbackRegister(void (*PrintCallback)(uint08, uint08, uint32))
{
	if(PrintCallback != OSD_NULL)
	{
		PrintCall = PrintCallback;
	}
}

/*********************************************************************************************************//**
* @param[in] map		: Normal Menu
* @param[in] hiddenmap	: hidden Menu
* @retval
*	None
* @brief
*	OSD_MAP등록
*************************************************************************************************************/
void IF_OsdMapRegister(const OSD_MAP *map, const OSD_MAP *hiddenmap)
{
	if(map != OSD_NULL)
	{
		gpOsdMap = map;
	}

	if(hiddenmap != OSD_NULL)
	{
		gpOsdHiddenMap = hiddenmap;
	}
}
/*********************************************************************************************************//**
* @param[in] width		: 넓이
* @param[in] height		: 높이
* @retval
*	None
* @brief
*	OSD의 Size
*************************************************************************************************************/
void IF_OsdWindowSize(uint32 width, uint32 height)
{
	gWinSize[0] = width;
	gWinSize[1] = height;
#ifndef WIN32
	gOsdIdPosition[1][0]    = width -8;
	gOsdIdPosition[1][1]    = height-4;
	gOsdTitlePosition[1][0] = width - 17;
	gOsdTitlePosition[1][1] = height- 5;
#endif
}

/*********************************************************************************************************//**
* @retval
*	return OSD_STATE
* @brief
*	현제 OSD의 State를 리턴\n
*	OSD_STATE_OFF		: OSD 메뉴 표시안됨\n
*	OSD_STATE_ON		: Normal 메뉴\n
*	OSD_STATE_HIDDEN	: Hidden 메뉴\n
*************************************************************************************************************/
OSD_STATE IF_IsOsdOn()
{
	return gOsdState;
}

/*********************************************************************************************************//**
* @retval
*	return OSD_Mode
* @brief
*	현제 OSD의 Mode를 리턴\n
*	OSD_NORMAL		: IDLE\n
*	OSD_TITLE		: 특수한 모드\n
*	OSD_TITLE_DISP	: 특수한 모드\n
*	OSD_ID_DISP		: 특수한 모드\n
*	OSD_HIDE		: 숨겨짐\n
*************************************************************************************************************/
OSD_MODE IF_IsOsdMode()
{
	return gOsdMode;
}
/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	Osd Menu를 강제로 종료
*************************************************************************************************************/
void IF_OsdOff()
{
	OsdIOn2Off();
}

/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	Osd Menu를 전체 다시그리기
*************************************************************************************************************/
void IF_OsdRefresh()
{
	if(gOsdState != OSD_STATEOFF && gOsdMode != OSD_HIDE)
	{
		ClearOsdMap();
		PrintOsdMap(gpCurMap, gCursor);
		gOsdMode = OSD_NORMAL;

#ifdef WIN32
		Osd_Update_Flg(1);
#endif
	}
}
/*********************************************************************************************************//**
* @param[in] cursor	: 라인위치
* @retval
*	none
* @brief
*	Osd Menu 중에 해당 라인의 아이템을 다시 그림
*************************************************************************************************************/
void IF_OsdItemRefresh(uint08 cursor)
{
	if(gOsdState != OSD_STATEOFF && gOsdMode != OSD_HIDE)
	{
		PrintItem(cursor , &gpCurMap[cursor]);
	}
#ifdef WIN32
		Osd_Update_Flg(1);
#endif

}
/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	Osd Menu 전체 아이템을 다시 그림
*************************************************************************************************************/
void IF_OsdAllItemRefresh(void)
{
	uint08 i;
	uint32 key;
	key = -1;
	if(gOsdState != OSD_STATEOFF && gOsdMode != OSD_HIDE)
	{
		for(i = 0; gpCurMap[i].name != OSD_STR_FINISH; i++)
		{
			PrintItem(i, &gpCurMap[i]);
			SendEvent(IFEVT_OSD, gpCurMap[i].eep, &key);
		}
	}
#ifdef WIN32
	Osd_Update_Flg(1);
#endif
}

void IF_OsdHide()
{
	if(gOsdState != OSD_STATEOFF)
	{
		ClearOsdMap();
		gOsdMode = OSD_HIDE;

#ifdef WIN32
		Osd_Update_Flg(1);
#endif
	}
}
/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	원래상태로 되돌림
*************************************************************************************************************/
void IF_OsdShow()
{
	if(gOsdState != OSD_STATEOFF && gOsdMode == OSD_HIDE)
	{
		gOsdMode = OSD_NORMAL;
		IF_OsdRefresh();
	}
}
/*********************************************************************************************************//**
* @retval
*	none
* @brief
*	이전 상태(메뉴/커서위치)를 기억하고 OSD만 지운다\n
*	IF_OsdShow()를 통해서 원래상태로 되돌림
*************************************************************************************************************/
IFER IF_OsdHiddenMenuOn()
{
	IFER er = IF_ERNO;
	uint32 key = OSD_KEYNULL;

	gKeyCnt = 0;
	gOsdState = OSD_STATEHIDDEN;

	FRESET_VAL = 0;
	REBOOT_VAL = 0;
	RETURN_VAL = 0;
	EXIT_VAL = 0;

	ClearOsdMap();
	PrintOsdMap(gpOsdHiddenMap, 0);

	er = SendEvent(IFEVT_OSD, IDX_OSDHIDDENON, &key);

#ifdef WIN32
	Osd_Update_Flg(1);
#endif

	return er;
}

/**************************************************************************************************************/
/* Protocol */

/*********************************************************************************************************//**
* @retval
*	Result Error
* @brief
*	프로토콜의 메인 테스크
*************************************************************************************************************/
IFER IF_Task_Ptc(void)
{
	IFER er = IF_ERNO;
	uint08 size = IF_PTC_RxQueSize();
	//if(size > 32)
	//	size = 32;

	IF_PtcRecvBuf(size);

	er = PtcTask();

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result 선택된 프로토콜의 종류 리턴
* @brief
*	프로토콜의 종류
*************************************************************************************************************/
void IF_PtcDecodingType(PTC_TYPE type)
{
	gPtcType = type;
}

/*********************************************************************************************************//**
* @param[in] reply : 타입
* @param[in] dat : 입력데이터
* @retval
*	Result Error
* @brief
*	Visca Protocol의 Reply 기능\n
*	타입			: 입력 데이터\n
*   VSC_REPLY_MD	: 0bit : MD1, 1bit : MD2, 2bit : MD3, 3bit : MD4\n
*	VSC_REPLY_ICR	: 1 (Off->On ),  0(On -> OFF)\n
*	VSC_REPLY_ZOOM	: Zoom Position\n
*	VSC_REPLY_FOCUS	: Focus Position\n
*	VSC_REPLY_WD	: 1 (WD On) , 0(WD off)\n
*************************************************************************************************************/
IFER IF_Send_Reply_Packet(VISCA_REPLY_TYPE reply ,uint32 dat)
{
	IFER er = IF_ERNO;
	switch(reply)
	{
		case VSC_REPLY_MD :
			er = IF_Send_Reply_MD(dat);
		break;
		case VSC_REPLY_ICR :
			er = IF_Send_Reply_ICR(dat);
		break;
		case VSC_REPLY_ZOOM :
			IF_Send_Reply_Zoom(dat&0xffff,dat>>16);
		break;
		case VSC_REPLY_FOCUS :
			IF_Send_Reply_Focus(dat);
		break;
		case VSC_REPLY_WD :
			IF_Send_Reply_WD(dat);
		break;
		default:
			er = IF_INVALIDVAL;
		break;
	}

	return er;
}
/*********************************************************************************************************//**
* @retval
*	Result Rx Que에 쌓여있는 데이터의 Byte 크기
* @brief
*   Rx Que에 쌓여있는 데이터의 Byte 크기.
*************************************************************************************************************/
uint08 IF_PTC_RxQueSize(void)
{
	return ((Ptc_Que.RxHead - Ptc_Que.RxTail + 256) & IF_QUEUE_MASK);
}
/*********************************************************************************************************//**
* @retval
*	Result Tx Que에 쌓여있는 데이터의 Byte 크기
* @brief
*   Tx Que에 쌓여있는 데이터의 Byte 크기.
*************************************************************************************************************/
uint08 IF_PTC_TxQueSize(void)
{
	return ((Ptc_Que.TxHead - Ptc_Que.TxTail + 256) & IF_QUEUE_MASK);
}

/*********************************************************************************************************//**
* @retval
*	Result Tx Que에 가장 이전에 들어간 데이터를 리턴한다.
* @brief
*   Tx Que데이터를 빼온다. \n
*	Que는 FIFO의 데이터이다.
*************************************************************************************************************/
uint08 IF_PTC_GetTxQue(void)
{
	volatile uint08 bf_Queue;

	bf_Queue = Ptc_Que.TxQueue[Ptc_Que.TxTail];

	Ptc_Que.TxTail++;
	Ptc_Que.TxTail &= IF_QUEUE_MASK;

	return bf_Queue;
}
/*********************************************************************************************************//**
* @retval
*	Result Rx Que에 가장 이전에 들어간 데이터를 리턴한다.
* @brief
*   Rx Que데이터를 빼온다. \n
*	Que는 FIFO의 데이터이다.
*************************************************************************************************************/
uint08 IF_PTC_GetRxQue(void)
{
	volatile uint08 rxData = 0;

	rxData = Ptc_Que.RxQueue[Ptc_Que.RxTail];

	Ptc_Que.RxTail++;
	Ptc_Que.RxTail &= IF_QUEUE_MASK;

	return rxData;
}
/*********************************************************************************************************//**
* @param[in] rxData : TxQue에 들어갈 1byte 데이터
* @brief
*   Tx Que에 데이터를 넣는다. \n
*	Que는 FIFO의 데이터이다.
*************************************************************************************************************/
void IF_PTC_SetTxQue(uint08 txData)
{
	volatile uint08 bf_head = Ptc_Que.TxHead++;
	Ptc_Que.TxHead &= IF_QUEUE_MASK;

	if(Ptc_Que.TxHead == Ptc_Que.TxTail)
	{
		Ptc_Que.RxHead = 0;
		Ptc_Que.RxTail = 0;
		if(g_OsdData.FLD.PROTOCOL == 3)
			PtcVisca_SendPacket(VISCA_ERROR_COMMAND_BUF_FULL,0,0);
	}
	else
	{
		Ptc_Que.TxQueue[bf_head] = txData;
		//UartEiTx;
	}

	return;
}

/*********************************************************************************************************//**
* @param[in] rxData : RxQue에 들어갈 1byte 데이터
* @brief
*   Rx Que에 데이터를 넣는다. \n
*	Que는 FIFO의 데이터이다.
*
*************************************************************************************************************/
void IF_PTC_SetRxQue(uint08 rxData)
{
	volatile uint08 bf_head = Ptc_Que.RxHead++;
	Ptc_Que.RxHead &= IF_QUEUE_MASK;

	if(Ptc_Que.RxHead == Ptc_Que.RxTail)
	{
		Ptc_Que.RxHead = 1;
		Ptc_Que.RxTail = 0;
		Ptc_Que.RxQueue[0] = 0xff;
		PtcBufClear();
		if(g_OsdData.FLD.PROTOCOL == 3)
			PtcVisca_SendPacket(VISCA_ERROR_COMMAND_BUF_FULL,0,0);
	}
	else
	{
		Ptc_Que.RxQueue[bf_head] = rxData;
	}

	return;
}

/*********************************************************************************************************//**
* @param[in] type	:
* @param[in] getfnc	:
* @param[in] setfnc	:
* @param[in] size	:
* @brief
*	return IFER
*************************************************************************************************************/
IFER IF_CNBT_Regist_Callbeck(CNBT_CALLBACK_FUNC type,uint32 (*getfnc)(uint32 addr),void (*setfnc)(uint32 addr,uint32 dat))
{
	IFER er = IF_ERNO;
	if(type >= CNBT_MAX)
	{
		return IF_INVALIDVAL;
	}

	if(getfnc != 0)
	{
		CNBT_Callback[type].getfunc = getfnc;
	}
	else
	{
		CNBT_Callback[type].getfunc = GetfuncNull;
	}

	if(setfnc != 0)
	{
		CNBT_Callback[type].setfunc = setfnc;
	}
	else
	{
		CNBT_Callback[type].setfunc = SetfuncNull;
	}

	return er;
}

