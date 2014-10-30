/*********************************************************************************************************//**
* @file miclib_type.h
* @author
*  JangHo, Yoo
* @date
*  2012.08.20
* @brief
*  이 파일은 MICLIB의 모든 데이터 타입과 ERROR CODE를 정의한다.
*************************************************************************************************************/
/*************************************************************************************************************
* MODULE START
*************************************************************************************************************/
#ifndef _MICLIB_TYPE_H_
#define _MICLIB_TYPE_H_

/*************************************************************************************************************
* CONFIGURATION 
*************************************************************************************************************/
#define USE_BASIC_TYPE                                      1
#define USE_FLOATING_TYPE                                   1
#define USE_BYTE_TYPE                                       1
#define USE_EXTENSION_TYPE                                  1
	#define USE_BOOLEAN_TYPE                                1
	#define USE_VARSTAT_TYPE                                1
	#define USE_VARFUNC_TYPE                                1
	#define USE_VARRESULT_TYPE                              1
	#define USE_VARFLAG_TYPE                                1
#define USE_GLOBAL_ERR_CODE                                 1
#define USE_BITMASK_VALUE                                   1
#define USE_OVER_THAN_32BIT_TYPE                            0

/*************************************************************************************************************
* BASIC TYPE
*************************************************************************************************************/
#if USE_BASIC_TYPE > 0
typedef signed char              int08;
typedef unsigned char            uint08;
typedef signed short             int16;
typedef unsigned short           uint16;
typedef signed long              int32;
typedef unsigned long            uint32;
#endif

#if USE_OVER_THAN_32BIT_TYPE > 0
typedef long long signed int     int64;
typedef long long unsigned int   uint64;
#endif

#if USE_FLOATING_TYPE > 0
typedef float                    fp32;
typedef double                   fp64;
#endif

/*************************************************************************************************************
* BYTE TYPES
*************************************************************************************************************/
#if USE_BYTE_TYPE > 0
typedef union _U16_BYTE {
    uint16 word;
	uint08 byte[2];
} uint16_b;

typedef union _S16_BYTE {
	int16 word;
	int08 byte[2];
} int16_b;

typedef union _U32_BYTE {
	uint32 dword;
	uint16 word[2];
	uint08 byte[4];
} uint32_b;

typedef union _S32_BYTE {
	int32 dword;
	int16 word[2];
	int08 byte[4];
} int32_b;
#endif

/*************************************************************************************************************
* EXTENTION TYPES
*************************************************************************************************************/
#if USE_EXTENSION_TYPE > 0
#if USE_BOOLEAN_TYPE > 0
typedef enum _BOOLEAN     { FALSE     = 0, TRUE     = !FALSE     } bool;
#endif

#if USE_VARSTAT_TYPE > 0
typedef enum _VAR_STATUS  { DISABLE   = 0, ENABLE   = !DISABLE   } var_stat;
#endif

#if USE_VARFUNC_TYPE > 0
typedef enum _VAR_FUNC    { STATE_OFF = 0, STATE_ON = !STATE_OFF } var_func;
#endif

#if USE_VARRESULT_TYPE > 0
typedef enum _VAR_RESULT  { ERROR     = 0, SUCCESS  = !ERROR     } var_result;
#endif

#if USE_VARFLAG_TYPE > 0
typedef enum _VAR_FLAG    { CLEAR     = 0, SET      = !CLEAR     } var_flag;
#endif
#endif

/*************************************************************************************************************
* GLOBAL ERROR CODE
*************************************************************************************************************/
#if USE_GLOBAL_ERR_CODE > 0
typedef enum _ERROR_CODE {
    NO_ERROR,
    ERR_CHECKSUM,
    ERR_TIMEOUT,
    ERR_CAM_ID,
    ERR_STX,
    ERR_HALLADJ,
    ERR_HALLADJ_OFFSET,
    ERR_HALLADJ_GAIN,
    ERR_LENSADJ,
    ERR_LENSADJ_FDIFF,
    ERR_LENSADJ_ZDIFF,
    ERR_LENSADJ_PDIFF,
    ERR_DEFADJ,
    ERR_DEFADJ_ODDFLD,
    ERR_DEFADJ_EVEFLD,
    ERR_VD_FAULT,
    ERR_EXTSYNC_FAULT,
    ERR_ZORG_SENSING,
    ERR_FORG_SENSING,
} ERROR_CODE;
#endif

/*************************************************************************************************************
* BIT MASK VALUE
*************************************************************************************************************/
#if USE_BITMASK_VALUE > 0
#define BIT31                      0x80000000
#define BIT30                      0x40000000
#define BIT29                      0x20000000
#define BIT28                      0x10000000
#define BIT27                      0x08000000
#define BIT26                      0x04000000
#define BIT25                      0x02000000
#define BIT24                      0x01000000
#define BIT23                      0x00800000
#define BIT22                      0x00400000
#define BIT21                      0x00200000
#define BIT20                      0x00100000
#define BIT19                      0x00080000
#define BIT18                      0x00040000
#define BIT17                      0x00020000
#define BIT16                      0x00010000
#define BIT15                      0x8000
#define BIT14                      0x4000
#define BIT13                      0x2000
#define BIT12                      0x1000
#define BIT11                      0x0800
#define BIT10                      0x0400
#define BIT9                       0x0200
#define BIT8                       0x0100
#define BIT7                       0x80
#define BIT6                       0x40
#define BIT5                       0x20
#define BIT4                       0x10
#define BIT3                       0x08
#define BIT2                       0x04
#define BIT1                       0x02
#define BIT0                       0x01
#endif

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _MICLIB_TYPE_H_ */
/********************************************* END OF FILE **************************************************/
