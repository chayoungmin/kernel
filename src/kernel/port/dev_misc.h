/* **************************************************************************
 File Name	: 	dev_misc.h
 Description:	EN777 - miscellaneous define
 Designer	:	Lee Hoon
 Date		:	12. 9. 20
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

//-------------------------------------------------------------------------------------------------
// System definition

#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val1 //YMCA

#if (model_Par==1)
#define		DFSEL_Par(par, def)		par
#else
#define		DFSEL_Par(par, def)		def
#endif

#define 	DFSEL_ParSens(par, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		DFSEL_Par(par, DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9))


#if 	(model_TgtBd==0)
	#define DFSEL_TgtBd(val0, val1, val2)	val0
#elif	(model_TgtBd==1)
	#define DFSEL_TgtBd(val0, val1, val2)	val1
#else 	
	#define DFSEL_TgtBd(val0, val1, val2)	val2	
#endif

#if 	(model_Iris==0)
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val0
#elif	(model_Iris==1)
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val1
#elif	(model_Iris==2)
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val2
#elif	(model_Iris==3)
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val3
#elif	(model_Iris==4)
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val4
#else 	
	#define DFSEL_Irs(val0, val1, val2, val3, val4, val5)		val5
#endif


// -----------------------------------------------------------------------------------------------
// Clock & Frame info (reserved)


	//#define HCLK		74250000		// AHB clock (core) //
	#define HCLK			108000000		//
	#define FR			60				// Frame pre sec
	#define FR_DUTY		16				// Frame duty time (msec)
	#define FR_HW		1920			// Active H width
	#define FR_VW		1080			// Active V width
	#define FR_HTW		2200			// Total  H width
	#define FR_VTW		1125			// Total  V width

	#define PCLK		(HCLK/2)		// APB clock (Peri)


//-------------------------------------------------------------------------------------------------
// Type definition
#if model_CharMax == 1
	#define EXCH		WORD
	#define EXCH_ADD	1
#else
	#define EXCH		BYTE
	#define EXCH_ADD	0
#endif

#define ISPM				__attribute__((section(".ispmtext")))

//-------------------------------------------------------------------------------------------------
// Macro
#define	_wr8(a,d)			*((volatile BYTE *)(a)) = (d)		// Write to peripheral
#define	_wr16(a,d)			*((volatile WORD *)(a)) = (d)		//			"
#define	_wr32(a,d)			*((volatile UINT *)(a)) = (d)		//			"

#define	_rd8(a)				*((volatile BYTE *)(a))				// Read from peripheral
#define	_rd16(a)			*((volatile WORD *)(a))				//			"
#define	_rd32(a)			*((volatile UINT *)(a))				//			"

#define ABS(x)				( (x) >= 0  ? (x) : -(x) )
#define MIN(x,y)			( (x) < (y) ? (x) :  (y) )
#define MAX(x,y)			( (x) > (y) ? (x) :  (y) )
#define MINMAX(x,min,max)	MIN(MAX(x, min), max)


//-------------------------------------------------------------------------------------------------
// Misc
//#define	NULL		0
#define	OK			1
#define	NG			0
#define YES			OK
#define	NO			NG

#define	BIT0 		(1<<0 )
#define	BIT1 		(1<<1 )
#define	BIT2 		(1<<2 )
#define	BIT3 		(1<<3 )
#define	BIT4 		(1<<4 )
#define	BIT5 		(1<<5 )
#define	BIT6 		(1<<6 )
#define	BIT7 		(1<<7 )
#define	BIT8 		(1<<8 )
#define	BIT9 		(1<<9 )
#define	BIT10		(1<<10)
#define	BIT11		(1<<11)
#define	BIT12		(1<<12)
#define	BIT13		(1<<13)
#define	BIT14		(1<<14)
#define	BIT15		(1<<15)
#define	BIT16		(1<<16)
#define	BIT17		(1<<17)
#define	BIT18		(1<<18)
#define	BIT19		(1<<19)
#define	BIT20		(1<<20)
#define	BIT21		(1<<21)
#define	BIT22		(1<<22)
#define	BIT23		(1<<23)
#define	BIT24		(1<<24)
#define	BIT25		(1<<25)
#define	BIT26		(1<<26)
#define	BIT27		(1<<27)
#define	BIT28		(1<<28)
#define	BIT29		(1<<29)
#define	BIT30		(1<<30)
#define	BIT31		(1<<31)

#define	SetBit0(d)			(d |=  (1<<0 ))
#define	SetBit1(d) 			(d |=  (1<<1 ))
#define	SetBit2(d) 			(d |=  (1<<2 ))
#define	SetBit3(d) 			(d |=  (1<<3 ))
#define	SetBit4(d) 			(d |=  (1<<4 ))
#define	SetBit5(d) 			(d |=  (1<<5 ))
#define	SetBit6(d) 			(d |=  (1<<6 ))
#define	SetBit7(d) 			(d |=  (1<<7 ))
#define	SetBit8(d) 			(d |=  (1<<8 ))
#define	SetBit9(d) 			(d |=  (1<<9 ))
#define	SetBit10(d)			(d |=  (1<<10))
#define	SetBit11(d)			(d |=  (1<<11))
#define	SetBit12(d)			(d |=  (1<<12))
#define	SetBit13(d)			(d |=  (1<<13))
#define	SetBit14(d)			(d |=  (1<<14))
#define	SetBit15(d)			(d |=  (1<<15))
#define	SetBit16(d)			(d |=  (1<<16))
#define	SetBit17(d)			(d |=  (1<<17))
#define	SetBit18(d)			(d |=  (1<<18))
#define	SetBit19(d)			(d |=  (1<<19))
#define	SetBit20(d)			(d |=  (1<<20))
#define	SetBit21(d)			(d |=  (1<<21))
#define	SetBit22(d)			(d |=  (1<<22))
#define	SetBit23(d)			(d |=  (1<<23))
#define	SetBit24(d)			(d |=  (1<<24))
#define	SetBit25(d)			(d |=  (1<<25))
#define	SetBit26(d)			(d |=  (1<<26))
#define	SetBit27(d)			(d |=  (1<<27))
#define	SetBit28(d)			(d |=  (1<<28))
#define	SetBit29(d)			(d |=  (1<<29))
#define	SetBit30(d)			(d |=  (1<<30))
#define	SetBit31(d)			(d |=  (1<<31))

#define	ClrBit0(d)			(d &= ~(1<<0 ))
#define	ClrBit1(d) 			(d &= ~(1<<1 ))
#define	ClrBit2(d) 			(d &= ~(1<<2 ))
#define	ClrBit3(d) 			(d &= ~(1<<3 ))
#define	ClrBit4(d) 			(d &= ~(1<<4 ))
#define	ClrBit5(d) 			(d &= ~(1<<5 ))
#define	ClrBit6(d) 			(d &= ~(1<<6 ))
#define	ClrBit7(d) 			(d &= ~(1<<7 ))
#define	ClrBit8(d) 			(d &= ~(1<<8 ))
#define	ClrBit9(d) 			(d &= ~(1<<9 ))
#define	ClrBit10(d)			(d &= ~(1<<10))
#define	ClrBit11(d)			(d &= ~(1<<11))
#define	ClrBit12(d)			(d &= ~(1<<12))
#define	ClrBit13(d)			(d &= ~(1<<13))
#define	ClrBit14(d)			(d &= ~(1<<14))
#define	ClrBit15(d)			(d &= ~(1<<15))
#define	ClrBit16(d)			(d &= ~(1<<16))
#define	ClrBit17(d)			(d &= ~(1<<17))
#define	ClrBit18(d)			(d &= ~(1<<18))
#define	ClrBit19(d)			(d &= ~(1<<19))
#define	ClrBit20(d)			(d &= ~(1<<20))
#define	ClrBit21(d)			(d &= ~(1<<21))
#define	ClrBit22(d)			(d &= ~(1<<22))
#define	ClrBit23(d)			(d &= ~(1<<23))
#define	ClrBit24(d)			(d &= ~(1<<24))
#define	ClrBit25(d)			(d &= ~(1<<25))
#define	ClrBit26(d)			(d &= ~(1<<26))
#define	ClrBit27(d)			(d &= ~(1<<27))
#define	ClrBit28(d)			(d &= ~(1<<28))
#define	ClrBit29(d)			(d &= ~(1<<29))
#define	ClrBit30(d)			(d &= ~(1<<30))
#define	ClrBit31(d)			(d &= ~(1<<31))

#define	ChkBit0(d)			((d>>0 ) & 1)
#define	ChkBit1(d) 			((d>>1 ) & 1)
#define	ChkBit2(d) 			((d>>2 ) & 1)
#define	ChkBit3(d) 			((d>>3 ) & 1)
#define	ChkBit4(d) 			((d>>4 ) & 1)
#define	ChkBit5(d) 			((d>>5 ) & 1)
#define	ChkBit6(d) 			((d>>6 ) & 1)
#define	ChkBit7(d) 			((d>>7 ) & 1)
#define	ChkBit8(d) 			((d>>8 ) & 1)
#define	ChkBit9(d) 			((d>>9 ) & 1)
#define	ChkBit10(d)			((d>>10) & 1)
#define	ChkBit11(d)			((d>>11) & 1)
#define	ChkBit12(d)			((d>>12) & 1)
#define	ChkBit13(d)			((d>>13) & 1)
#define	ChkBit14(d)			((d>>14) & 1)
#define	ChkBit15(d)			((d>>15) & 1)
#define	ChkBit16(d)			((d>>16) & 1)
#define	ChkBit17(d)			((d>>17) & 1)
#define	ChkBit18(d)			((d>>18) & 1)
#define	ChkBit19(d)			((d>>19) & 1)
#define	ChkBit20(d)			((d>>20) & 1)
#define	ChkBit21(d)			((d>>21) & 1)
#define	ChkBit22(d)			((d>>22) & 1)
#define	ChkBit23(d)			((d>>23) & 1)
#define	ChkBit24(d)			((d>>24) & 1)
#define	ChkBit25(d)			((d>>25) & 1)
#define	ChkBit26(d)			((d>>26) & 1)
#define	ChkBit27(d)			((d>>27) & 1)
#define	ChkBit28(d)			((d>>28) & 1)
#define	ChkBit29(d)			((d>>29) & 1)
#define	ChkBit30(d)			((d>>30) & 1)
#define	ChkBit31(d)			((d>>31) & 1)

#define BitMask_01			0x1
#define BitMask_02			0x3
#define BitMask_03			0x7
#define BitMask_04			0xf
#define BitMask_05			0x1f
#define BitMask_06			0x3f
#define BitMask_07			0x7f
#define BitMask_08			0xff
#define BitMask_09			0x1ff
#define BitMask_10			0x3ff
#define BitMask_11			0x7ff
#define BitMask_12			0xfff
#define BitMask_13			0x1fff
#define BitMask_14			0x3fff
#define BitMask_15			0x7fff
#define BitMask_16			0xffff
#define BitMask_17			0x1ffff
#define BitMask_18			0x3ffff
#define BitMask_19			0x7ffff
#define BitMask_20			0xfffff
#define BitMask_21			0x1fffff
#define BitMask_22			0x3fffff
#define BitMask_23			0x7fffff
#define BitMask_24			0xffffff
#define BitMask_25			0x1ffffff
#define BitMask_26			0x3ffffff
#define BitMask_27			0x7ffffff
#define BitMask_28			0xfffffff
#define BitMask_29			0x1fffffff
#define BitMask_30			0x3fffffff
#define BitMask_31			0x7fffffff
#define BitMask_32			0xffffffff

#define ValSft_R00(val)		((val)>> 0)
#define ValSft_R01(val)		((val)>> 1)
#define ValSft_R02(val)		((val)>> 2)
#define ValSft_R03(val)		((val)>> 3)
#define ValSft_R04(val)		((val)>> 4)
#define ValSft_R05(val)		((val)>> 5)
#define ValSft_R06(val)		((val)>> 6)
#define ValSft_R07(val)		((val)>> 7)
#define ValSft_R08(val)		((val)>> 8)
#define ValSft_R09(val)		((val)>> 9)
#define ValSft_R10(val)		((val)>>10)
#define ValSft_R11(val)		((val)>>11)
#define ValSft_R12(val)		((val)>>12)
#define ValSft_R13(val)		((val)>>13)
#define ValSft_R14(val)		((val)>>14)
#define ValSft_R15(val)		((val)>>15)
#define ValSft_R16(val)		((val)>>16)
#define ValSft_R17(val)		((val)>>17)
#define ValSft_R18(val)		((val)>>18)
#define ValSft_R19(val)		((val)>>19)
#define ValSft_R20(val)		((val)>>20)
#define ValSft_R21(val)		((val)>>21)
#define ValSft_R22(val)		((val)>>22)
#define ValSft_R23(val)		((val)>>23)
#define ValSft_R24(val)		((val)>>24)
#define ValSft_R25(val)		((val)>>25)
#define ValSft_R26(val)		((val)>>26)
#define ValSft_R27(val)		((val)>>27)
#define ValSft_R28(val)		((val)>>28)
#define ValSft_R29(val)		((val)>>29)
#define ValSft_R30(val)		((val)>>30)
#define ValSft_R31(val)		((val)>>31)

#define ValSft_L00(val)		((val)<< 0)
#define ValSft_L01(val)		((val)<< 1)
#define ValSft_L02(val)		((val)<< 2)
#define ValSft_L03(val)		((val)<< 3)
#define ValSft_L04(val)		((val)<< 4)
#define ValSft_L05(val)		((val)<< 5)
#define ValSft_L06(val)		((val)<< 6)
#define ValSft_L07(val)		((val)<< 7)
#define ValSft_L08(val)		((val)<< 8)
#define ValSft_L09(val)		((val)<< 9)
#define ValSft_L10(val)		((val)<<10)
#define ValSft_L11(val)		((val)<<11)
#define ValSft_L12(val)		((val)<<12)
#define ValSft_L13(val)		((val)<<13)
#define ValSft_L14(val)		((val)<<14)
#define ValSft_L15(val)		((val)<<15)
#define ValSft_L16(val)		((val)<<16)
#define ValSft_L17(val)		((val)<<17)
#define ValSft_L18(val)		((val)<<18)
#define ValSft_L19(val)		((val)<<19)
#define ValSft_L20(val)		((val)<<20)
#define ValSft_L21(val)		((val)<<21)
#define ValSft_L22(val)		((val)<<22)
#define ValSft_L23(val)		((val)<<23)
#define ValSft_L24(val)		((val)<<24)
#define ValSft_L25(val)		((val)<<25)
#define ValSft_L26(val)		((val)<<26)
#define ValSft_L27(val)		((val)<<27)
#define ValSft_L28(val)		((val)<<28)
#define ValSft_L29(val)		((val)<<29)
#define ValSft_L30(val)		((val)<<30)
#define ValSft_L31(val)		((val)<<31)

