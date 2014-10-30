/*********************************************************************************************************//**
* @file miclib_misc.h
* @author
*  JangHo, Yoo
* @date
*  2012.08.20
* @brief
*  이 파일은 MICLIB의 공용 매크로들과 공용기능들에 대해 정의한다.
*************************************************************************************************************/
/*************************************************************************************************************
* MODULE START
*************************************************************************************************************/
#ifndef _MICLIB_MISC_H_
#define _MICLIB_MISC_H_

/*************************************************************************************************************
* CONFIGURATION 
*************************************************************************************************************/
#define USE_MICLIB_MAXV                      1           
#define USE_MICLIB_MINV                      1
#define USE_MICLIB_LIMIT2MAX                 1
#define USE_MICLIB_LIMIT2MIN                 1
#define USE_MICLIB_LIMIT                     1
#define USE_MICLIB_DIFFV                     1
#define USE_MICLIB_ABSV                      1
#define USE_MICLIB_ARRAYSZ                   1
#define USE_MICLIB_SWAPV                     1
#define USE_MICLIB_ASC2BIN                   1
#define USE_MICLIB_BIN2ASC                   1
#define USE_MICLIB_ASC2BYTES                 1
#define USE_MICLIB_BYTES2ASC                 1
#define USE_MICLIB_GETNEXTVAL                1
#define USE_MICLIB_ASSERT_VAL                1
#define USE_MICLIB_ASSERT_PARAM              1
#define USE_MICLIB_ABS_DIFF					 1

#define USE_MICLIB_LINEARINTERP              1  
#define USE_MICLIB_SMA                       1
#define USE_MICLIB_WMA                       1
#define USE_MICLIB_MAF                       1
#define USE_MICLIB_ASCENDSORT                1
#define USE_MICLIB_DESCNDSORT                1
#define USE_MICLIB_MEMCPY					 0


/*************************************************************************************************************
* MACRO'S
*************************************************************************************************************/
#if USE_MICLIB_MAXV > 0
#define MAXV(a, b)                            ((a >= b) ? a : b)
#endif

#if USE_MICLIB_MINV > 0
#define MINV(a, b)                            ((a <= b) ? a : b)
#endif

#if USE_MICLIB_LIMIT2MAX > 0
#define LIMIT2MAX(a, b)                       (a = ((a > b) ? b : a))
#endif

#if USE_MICLIB_LIMIT2MIN > 0
#define LIMIT2MIN(a, b)                       (a = ((a < b) ? b : a))
#endif

#if USE_MICLIB_LIMIT > 0
#define LIMIT(a, b, c)                        (a = ((a > b) ? b : ((a < b) ? b : a))
#endif

#if USE_MICLIB_DIFFV > 0
#define DIFFV(a, b)                           ((a > b) ? (a - b) : (b - a))
#endif

#if USE_MICLIB_ABSV > 0
#define ABSV(a)                               ((a < 0) ? (a * (-1)) : a)
#endif

#if USE_MICLIB_ARRAYSZ > 0
#define ARRAYSZ(a)                            (sizeof(a) / sizeof(*a))
#endif

#if USE_MICLIB_ASSERT_VAL > 0
#define ASSERT_VAL(a, min, max)               ((a < min) ? 0 : ((a > max) ? 0 : 1))
#endif

#define LIMIT_CHK(val, minV, maxV)	((val > maxV) ? FALSE : ((val < minV) ? FALSE : TRUE))
#define LIMIT_CHK_MAX(val, minV, maxV)	((val > maxV) ? FALSE : TRUE)

#if USE_MICLIB_ASSERT_PARAM > 0
#define ASSERT_PARAM(a, min, max)\
{\
	if ((a < min) || (a > max))\
	{\
		return;\
	}\
}
#endif

#if USE_MICLIB_ABS_DIFF > 0
#define ABS_DIFF(a,b)                           ((a >= b) ? (a - b) : (b - a)) //$ Rev 207 YMCA
#endif


#if USE_MICLIB_SWAPV > 0
#define SWAPV(a, b)\
{\
	a ^= b;\
	b ^= a;\
	a ^= b;\
}
#endif


/*************************************************************************************************************
* CONSTANTS
*************************************************************************************************************/
#if USE_MICLIB_GETNEXTVAL > 0
enum _NEXT_VAL_OPT {
	NEXT_VAL_INC        = 0x01,
	NEXT_VAL_DEC        = 0x02,
	NEXT_VAL_ROTATE     = 0x80,
	NEXT_VAL_LIMIT_INC  = NEXT_VAL_INC,
	NEXT_VAL_LIMIT_DEC  = NEXT_VAL_DEC,
	NEXT_VAL_ROTATE_INC = NEXT_VAL_INC | NEXT_VAL_ROTATE,
	NEXT_VAL_ROTATE_DEC = NEXT_VAL_DEC | NEXT_VAL_ROTATE
}; 
#endif

/*************************************************************************************************************
* EXTERNAL FUNCTIONS
*************************************************************************************************************/
#if USE_MICLIB_ASC2BIN > 0
uint08 asc2bin(uint08 arga);
#endif

#if USE_MICLIB_BIN2ASC > 0
uint08 bin2asc(uint08 arga);
#endif

#if USE_MICLIB_ASC2BYTES > 0
uint32 asc2bytes(uint08* asc_src, uint08 idx, uint08 len);
#endif

#if USE_MICLIB_BYTES2ASC > 0
void bytes2asc(uint32 new, uint08* asc_dest, uint08 idx, uint08 len);
#endif

#if USE_MICLIB_GETNEXTVAL > 0
int16 GetNextValue(int16 cur, int16 min, int16 max, uint08 opt);
#endif

#if USE_MICLIB_LINEARINTERP > 0
int32 CalcLinearInterpolation(int32 xp, int32 x0, int32 x1, int32 y0, int32 y1);
#endif

#if USE_MICLIB_SMA > 0
uint32 CalcSimpleMovingAvg(uint32 new_val, uint32 *pb, uint32 n);
#endif

#if USE_MICLIB_WMA > 0
uint32 CalcWeightedMovingAvg(uint32 new_val, uint32 *pb, uint32 n);
#endif

#if USE_MICLIB_MAF > 0
void MovingAvgFilter(uint32 *pb_s, uint32 n, uint32 tap, uint32 *pb_avg);
#endif

#if USE_MICLIB_ASCENDSORT > 0
void AscendSort(uint32 *pb, uint32 n);
#endif

#if USE_MICLIB_DESCNDSORT > 0
void DescendSort(uint32 *pb, uint32 n);
#endif

#if USE_MICLIB_MEMCPY > 0
void * memcpy2(void *dst, void *src, int n);
#endif

/*************************************************************************************************************
* MODULE END
*************************************************************************************************************/
#endif /* _MICLIB_MISC_H_ */
/********************************************* END OF FILE **************************************************/
