/* **************************************************************************
 File Name	: 	dev_reg_isp.h
 Description:	EN777 - ISP Reg macro define
 Designer	:	Lee, Hoon
 Date		:	12. 2. 8
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */


//*************************************************************************************************
// ISP (EN773A)
//-------------------------------------------------------------------------------------------------

#define	ISP_BASE				0x30020000	// Normal reg start addr.
#define POREG_ENw(val)			VLOCKS_UPDATE_EN773Aw(val)		// Post reg update flag (Hidden )
//-------------------------------------------------------------------------------------------------
#define LVDS_CKSEL_EN773Ar				(ValSft_R30(_rd32(0x30020000))&BitMask_02)
#define LVDS_CKSEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define LVDS_RXON_EN773Ar				(ValSft_R29(_rd32(0x30020000))&BitMask_01)
#define LVDS_RXON_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define PCKI_SEL_EN773Ar				(ValSft_R28(_rd32(0x30020000))&BitMask_01)
#define PCKI_SEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define GPIO30_CON_EN773Ar				(ValSft_R26(_rd32(0x30020000))&BitMask_02)
#define GPIO30_CON_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define MASTER_EN773Ar					(ValSft_R25(_rd32(0x30020000))&BitMask_01)
#define MASTER_EN773Aw(val)				_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define VHSO_DIR_EN773Ar				(ValSft_R24(_rd32(0x30020000))&BitMask_01)
#define VHSO_DIR_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define GPIO31_CON_EN773Ar				(ValSft_R22(_rd32(0x30020000))&BitMask_02)
#define GPIO31_CON_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define HDSDI_PD_EN773Ar				(ValSft_R21(_rd32(0x30020000))&BitMask_01)
#define HDSDI_PD_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define DAC_PD_EN773Ar					(ValSft_R20(_rd32(0x30020000))&BitMask_01)
#define DAC_PD_EN773Aw(val)				_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define SCKO_DLY_EN773Ar				(ValSft_R16(_rd32(0x30020000))&BitMask_04)
#define SCKO_DLY_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define LSPI_RSTN_EN773Ar				(ValSft_R15(_rd32(0x30020000))&BitMask_01)
#define LSPI_RSTN_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define LCK_DLY1_EN773Ar				(ValSft_R12(_rd32(0x30020000))&BitMask_03)
#define LCK_DLY1_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define LCK_DLY2_EN773Ar				(ValSft_R09(_rd32(0x30020000))&BitMask_03)
#define LCK_DLY2_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L09(BitMask_03)))|ValSft_L09((val)&BitMask_03)))

#define ECKO_INV_EN773Ar				(ValSft_R08(_rd32(0x30020000))&BitMask_01)
#define ECKO_INV_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define DCKO_INV_EN773Ar				(ValSft_R07(_rd32(0x30020000))&BitMask_01)
#define DCKO_INV_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define MCKO_SEL_EN773Ar				(ValSft_R05(_rd32(0x30020000))&BitMask_02)
#define MCKO_SEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L05(BitMask_02)))|ValSft_L05((val)&BitMask_02)))

#define ECK_SEL_EN773Ar					(ValSft_R03(_rd32(0x30020000))&BitMask_02)
#define ECK_SEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L03(BitMask_02)))|ValSft_L03((val)&BitMask_02)))

#define SCKO_INV_EN773Ar				(ValSft_R02(_rd32(0x30020000))&BitMask_01)
#define SCKO_INV_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define DCK_SEL_EN773Ar					(ValSft_R01(_rd32(0x30020000))&BitMask_01)
#define DCK_SEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define PCK_SEL_EN773Ar					(ValSft_R00(_rd32(0x30020000))&BitMask_01)
#define PCK_SEL_EN773Aw(val)			_wr32(0x30020000,(UINT)((_rd32(0x30020000)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define DQSO3_DLY_EN773Ar				(ValSft_R28(_rd32(0x30020004))&BitMask_04)
#define DQSO3_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define DQSO2_DLY_EN773Ar				(ValSft_R24(_rd32(0x30020004))&BitMask_04)
#define DQSO2_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define DQSO1_DLY_EN773Ar				(ValSft_R20(_rd32(0x30020004))&BitMask_04)
#define DQSO1_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define DQSO0_DLY_EN773Ar				(ValSft_R16(_rd32(0x30020004))&BitMask_04)
#define DQSO0_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define DQSI3_DLY_EN773Ar				(ValSft_R12(_rd32(0x30020004))&BitMask_04)
#define DQSI3_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define DQSI2_DLY_EN773Ar				(ValSft_R08(_rd32(0x30020004))&BitMask_04)
#define DQSI2_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define DQSI1_DLY_EN773Ar				(ValSft_R04(_rd32(0x30020004))&BitMask_04)
#define DQSI1_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define DQSI0_DLY_EN773Ar				(ValSft_R00(_rd32(0x30020004))&BitMask_04)
#define DQSI0_DLY_EN773Aw(val)			_wr32(0x30020004,(UINT)((_rd32(0x30020004)&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define PLLO_PD_EN773Ar					(ValSft_R31(_rd32(0x30020008))&BitMask_01)
#define PLLO_PD_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define PLLO_JIT_EN773Ar				(ValSft_R30(_rd32(0x30020008))&BitMask_01)
#define PLLO_JIT_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define PLLO_RES_EN773Ar				(ValSft_R28(_rd32(0x30020008))&BitMask_02)
#define PLLO_RES_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define PLLO_RATE_EN773Ar				(ValSft_R27(_rd32(0x30020008))&BitMask_01)
#define PLLO_RATE_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define PLLO_BW_EN773Ar					(ValSft_R24(_rd32(0x30020008))&BitMask_03)
#define PLLO_BW_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define PLLO_EMP_EN773Ar				(ValSft_R23(_rd32(0x30020008))&BitMask_01)
#define PLLO_EMP_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define PLLI_PD_EN773Ar					(ValSft_R22(_rd32(0x30020008))&BitMask_01)
#define PLLI_PD_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define PLLI_HS_EN773Ar					(ValSft_R21(_rd32(0x30020008))&BitMask_01)
#define PLLI_HS_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define PLLI_LFSEL_EN773Ar				(ValSft_R20(_rd32(0x30020008))&BitMask_01)
#define PLLI_LFSEL_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define PLLI_S_EN773Ar					(ValSft_R18(_rd32(0x30020008))&BitMask_02)
#define PLLI_S_EN773Aw(val)				_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define PLLI_OS_EN773Ar					(ValSft_R16(_rd32(0x30020008))&BitMask_02)
#define PLLI_OS_EN773Aw(val)			_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L16(BitMask_02)))|ValSft_L16((val)&BitMask_02)))

#define PLLI_P_EN773Ar					(ValSft_R08(_rd32(0x30020008))&BitMask_08)
#define PLLI_P_EN773Aw(val)				_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define PLLI_M_EN773Ar					(ValSft_R00(_rd32(0x30020008))&BitMask_08)
#define PLLI_M_EN773Aw(val)				_wr32(0x30020008,(UINT)((_rd32(0x30020008)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define PLLI_VG_EN773Ar					(ValSft_R28(_rd32(0x3002000c))&BitMask_03)
#define PLLI_VG_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define PLLI_VB_EN773Ar					(ValSft_R24(_rd32(0x3002000c))&BitMask_03)
#define PLLI_VB_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define PLLI_VI_EN773Ar					(ValSft_R20(_rd32(0x3002000c))&BitMask_03)
#define PLLI_VI_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define HD_SDI_SWG_EN773Ar				(ValSft_R16(_rd32(0x3002000c))&BitMask_03)
#define HD_SDI_SWG_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L16(BitMask_03)))|ValSft_L16((val)&BitMask_03)))

#define SWR_ID_EN773Ar					(ValSft_R08(_rd32(0x3002000c))&BitMask_08)
#define SWR_ID_EN773Aw(val)				_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define SSTYPE_SEL_EN773Ar				(ValSft_R07(_rd32(0x3002000c))&BitMask_01)
#define SSTYPE_SEL_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define SSCNTL_SEL_EN773Ar				(ValSft_R06(_rd32(0x3002000c))&BitMask_01)
#define SSCNTL_SEL_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define LVDS_PD_EN773Ar					(ValSft_R00(_rd32(0x3002000c))&BitMask_06)
#define LVDS_PD_EN773Aw(val)			_wr32(0x3002000c,(UINT)((_rd32(0x3002000c)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define ADC_EN_EN773Ar					(ValSft_R31(_rd32(0x30020010))&BitMask_01)
#define ADC_EN_EN773Aw(val)				_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ADC_INT_EN_EN773Ar				(ValSft_R30(_rd32(0x30020010))&BitMask_01)
#define ADC_INT_EN_EN773Aw(val)			_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define ADC_STC_WIDTH_EN773Ar			(ValSft_R29(_rd32(0x30020010))&BitMask_01)
#define ADC_STC_WIDTH_EN773Aw(val)		_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define ADC_CAP_POS_EN773Ar				(ValSft_R27(_rd32(0x30020010))&BitMask_02)
#define ADC_CAP_POS_EN773Aw(val)		_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L27(BitMask_02)))|ValSft_L27((val)&BitMask_02)))

#define ADC_INT_WIDTH_EN773Ar			(ValSft_R24(_rd32(0x30020010))&BitMask_02)
#define ADC_INT_WIDTH_EN773Aw(val)		_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define ADC_MODE_EN773Ar				(ValSft_R20(_rd32(0x30020010))&BitMask_04)
#define ADC_MODE_EN773Aw(val)			_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define ADC_SRATE_EN773Ar				(ValSft_R00(_rd32(0x30020010))&BitMask_10)
#define ADC_SRATE_EN773Aw(val)			_wr32(0x30020010,(UINT)((_rd32(0x30020010)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define PANA_MOD_EN773Ar				(ValSft_R31(_rd32(0x30020014))&BitMask_01)
#define PANA_MOD_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LVDS_RST_EN773Ar				(ValSft_R30(_rd32(0x30020014))&BitMask_01)
#define LVDS_RST_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define LVDS_LSB_EN773Ar				(ValSft_R29(_rd32(0x30020014))&BitMask_01)
#define LVDS_LSB_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define APTI_SM_ON_EN773Ar				(ValSft_R28(_rd32(0x30020014))&BitMask_01)
#define APTI_SM_ON_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define LVDS_TYPE_EN773Ar				(ValSft_R24(_rd32(0x30020014))&BitMask_03)
#define LVDS_TYPE_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define LDIDLY4_EN773Ar					(ValSft_R20(_rd32(0x30020014))&BitMask_03)
#define LDIDLY4_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define LDIDLY3_EN773Ar					(ValSft_R16(_rd32(0x30020014))&BitMask_03)
#define LDIDLY3_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L16(BitMask_03)))|ValSft_L16((val)&BitMask_03)))

#define LDIDLY1_EN773Ar					(ValSft_R08(_rd32(0x30020014))&BitMask_03)
#define LDIDLY1_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define LDIDLY0_EN773Ar					(ValSft_R04(_rd32(0x30020014))&BitMask_03)
#define LDIDLY0_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define DAT_CPOS_EN773Ar				(ValSft_R02(_rd32(0x30020014))&BitMask_02)
#define DAT_CPOS_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define LDI_POL_EN773Ar					(ValSft_R01(_rd32(0x30020014))&BitMask_01)
#define LDI_POL_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define LDI_PNSEL_EN773Ar				(ValSft_R00(_rd32(0x30020014))&BitMask_01)
#define LDI_PNSEL_EN773Aw(val)			_wr32(0x30020014,(UINT)((_rd32(0x30020014)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define LDO3_SEL_EN773Ar				(ValSft_R30(_rd32(0x30020018))&BitMask_02)
#define LDO3_SEL_EN773Aw(val)			_wr32(0x30020018,(UINT)((_rd32(0x30020018)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define LDO2_SEL_EN773Ar				(ValSft_R28(_rd32(0x30020018))&BitMask_02)
#define LDO2_SEL_EN773Aw(val)			_wr32(0x30020018,(UINT)((_rd32(0x30020018)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define LDO1_SEL_EN773Ar				(ValSft_R26(_rd32(0x30020018))&BitMask_02)
#define LDO1_SEL_EN773Aw(val)			_wr32(0x30020018,(UINT)((_rd32(0x30020018)&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define LDO0_SEL_EN773Ar				(ValSft_R24(_rd32(0x30020018))&BitMask_02)
#define LDO0_SEL_EN773Aw(val)			_wr32(0x30020018,(UINT)((_rd32(0x30020018)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define SYNC_COD0_EN773Ar				(ValSft_R00(_rd32(0x30020018))&BitMask_16)
#define SYNC_COD0_EN773Aw(val)			_wr32(0x30020018,(UINT)((_rd32(0x30020018)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SYNC_COD1_EN773Ar				(ValSft_R16(_rd32(0x3002001c))&BitMask_16)
#define SYNC_COD1_EN773Aw(val)			_wr32(0x3002001c,(UINT)((_rd32(0x3002001c)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SYNC_COD2_EN773Ar				(ValSft_R00(_rd32(0x3002001c))&BitMask_16)
#define SYNC_COD2_EN773Aw(val)			_wr32(0x3002001c,(UINT)((_rd32(0x3002001c)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SYNC_COD3_0_EN773Ar				(ValSft_R16(_rd32(0x30020020))&BitMask_16)
#define SYNC_COD3_0_EN773Aw(val)		_wr32(0x30020020,(UINT)((_rd32(0x30020020)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SYNC_COD3_1_EN773Ar				(ValSft_R00(_rd32(0x30020020))&BitMask_16)
#define SYNC_COD3_1_EN773Aw(val)		_wr32(0x30020020,(UINT)((_rd32(0x30020020)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SYNC_COD3_2_EN773Ar				(ValSft_R16(_rd32(0x30020024))&BitMask_12)
#define SYNC_COD3_2_EN773Aw(val)		_wr32(0x30020024,(UINT)((_rd32(0x30020024)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define SYNC_COD3_3_EN773Ar				(ValSft_R00(_rd32(0x30020024))&BitMask_08)
#define SYNC_COD3_3_EN773Aw(val)		_wr32(0x30020024,(UINT)((_rd32(0x30020024)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define SYNC_COD3_4_EN773Ar				(ValSft_R16(_rd32(0x30020028))&BitMask_08)
#define SYNC_COD3_4_EN773Aw(val)		_wr32(0x30020028,(UINT)((_rd32(0x30020028)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define SYNC_COD3_5_EN773Ar				(ValSft_R00(_rd32(0x30020028))&BitMask_08)
#define SYNC_COD3_5_EN773Aw(val)		_wr32(0x30020028,(UINT)((_rd32(0x30020028)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define PLLI_SLD_EN773Ar				(ValSft_R30(_rd32(0x30020030))&BitMask_02)
#define PLLI_SLD_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define PLLI_MON_EN773Ar				(ValSft_R28(_rd32(0x30020030))&BitMask_02)
#define PLLI_MON_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define PLLI_TEN_EN773Ar				(ValSft_R27(_rd32(0x30020030))&BitMask_01)
#define PLLI_TEN_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define PLLI_TPD_EN773Ar				(ValSft_R26(_rd32(0x30020030))&BitMask_01)
#define PLLI_TPD_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define PLLI_TPU_EN773Ar				(ValSft_R25(_rd32(0x30020030))&BitMask_01)
#define PLLI_TPU_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define PLLI_BS_EN773Ar					(ValSft_R24(_rd32(0x30020030))&BitMask_01)
#define PLLI_BS_EN773Aw(val)			_wr32(0x30020030,(UINT)((_rd32(0x30020030)&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define VLOCKS_UPDATE_EN773Ar			(ValSft_R00(_rd32(0x3002003c))&BitMask_01)
#define VLOCKS_UPDATE_EN773Aw(val)		_wr32(0x3002003c,(UINT)((_rd32(0x3002003c)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define GPIO_IOPW_EN773Ar				(ValSft_R00(_rd32(0x30020040))&BitMask_32)
#define GPIO_IOPW_EN773Aw(val)			_wr32(0x30020040,(UINT)((_rd32(0x30020040)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define GPIO_IOPW1_EN773Ar				(ValSft_R00(_rd32(0x30020044))&BitMask_32)
#define GPIO_IOPW1_EN773Aw(val)			_wr32(0x30020044,(UINT)((_rd32(0x30020044)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define SF_IOPW_EN773Ar					(ValSft_R24(_rd32(0x30020048))&BitMask_06)
#define SF_IOPW_EN773Aw(val)			_wr32(0x30020048,(UINT)((_rd32(0x30020048)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define ITU_IOPW_EN773Ar				(ValSft_R00(_rd32(0x30020048))&BitMask_24)
#define ITU_IOPW_EN773Aw(val)			_wr32(0x30020048,(UINT)((_rd32(0x30020048)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define SF_IOPW1_EN773Ar				(ValSft_R24(_rd32(0x3002004c))&BitMask_06)
#define SF_IOPW1_EN773Aw(val)			_wr32(0x3002004c,(UINT)((_rd32(0x3002004c)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define ITU_IOPW1_EN773Ar				(ValSft_R00(_rd32(0x3002004c))&BitMask_24)
#define ITU_IOPW1_EN773Aw(val)			_wr32(0x3002004c,(UINT)((_rd32(0x3002004c)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define MCKO_IOPW_EN773Ar				(ValSft_R30(_rd32(0x30020050))&BitMask_02)
#define MCKO_IOPW_EN773Aw(val)			_wr32(0x30020050,(UINT)((_rd32(0x30020050)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define SDR_IOPW_EN773Ar				(ValSft_R28(_rd32(0x30020050))&BitMask_02)
#define SDR_IOPW_EN773Aw(val)			_wr32(0x30020050,(UINT)((_rd32(0x30020050)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define HSI_IOPW_EN773Ar				(ValSft_R26(_rd32(0x30020050))&BitMask_02)
#define HSI_IOPW_EN773Aw(val)			_wr32(0x30020050,(UINT)((_rd32(0x30020050)&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define VSI_IOPW_EN773Ar				(ValSft_R24(_rd32(0x30020050))&BitMask_02)
#define VSI_IOPW_EN773Aw(val)			_wr32(0x30020050,(UINT)((_rd32(0x30020050)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define VTWI_EN773Ar					(ValSft_R16(_rd32(0x30020080))&BitMask_16)
#define VTWI_EN773Aw(val)				_wr32(0x30020080,(UINT)((_rd32(0x30020080)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define HTWI_EN773Ar					(ValSft_R00(_rd32(0x30020080))&BitMask_16)
#define HTWI_EN773Aw(val)				_wr32(0x30020080,(UINT)((_rd32(0x30020080)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SHSO_RP_EN773Ar					(ValSft_R16(_rd32(0x30020084))&BitMask_16)
#define SHSO_RP_EN773Aw(val)			_wr32(0x30020084,(UINT)((_rd32(0x30020084)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SHSO_FP_EN773Ar					(ValSft_R00(_rd32(0x30020084))&BitMask_16)
#define SHSO_FP_EN773Aw(val)			_wr32(0x30020084,(UINT)((_rd32(0x30020084)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SVSO_RP_EN773Ar					(ValSft_R16(_rd32(0x30020088))&BitMask_16)
#define SVSO_RP_EN773Aw(val)			_wr32(0x30020088,(UINT)((_rd32(0x30020088)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SVSO_FP_EN773Ar					(ValSft_R00(_rd32(0x30020088))&BitMask_16)
#define SVSO_FP_EN773Aw(val)			_wr32(0x30020088,(UINT)((_rd32(0x30020088)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SHSO_INV_EN773Ar				(ValSft_R31(_rd32(0x3002008c))&BitMask_01)
#define SHSO_INV_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SVSO_INV_EN773Ar				(ValSft_R30(_rd32(0x3002008c))&BitMask_01)
#define SVSO_INV_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SHSO_TRG_EN773Ar				(ValSft_R29(_rd32(0x3002008c))&BitMask_01)
#define SHSO_TRG_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define SVSO_TRG_EN773Ar				(ValSft_R28(_rd32(0x3002008c))&BitMask_01)
#define SVSO_TRG_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define HSO_OENp_EN773Ar				(ValSft_R27(_rd32(0x3002008c))&BitMask_01)
#define HSO_OENp_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define VSO_OENp_EN773Ar				(ValSft_R26(_rd32(0x3002008c))&BitMask_01)
#define VSO_OENp_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define DCKO_OEN_EN773Ar				(ValSft_R25(_rd32(0x3002008c))&BitMask_01)
#define DCKO_OEN_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define DENO_OEN_EN773Ar				(ValSft_R24(_rd32(0x3002008c))&BitMask_01)
#define DENO_OEN_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define YCO_OEN_EN773Ar					(ValSft_R23(_rd32(0x3002008c))&BitMask_01)
#define YCO_OEN_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define ADC_CKPH_EN773Ar				(ValSft_R08(_rd32(0x3002008c))&BitMask_08)
#define ADC_CKPH_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ADC_CKSEL_EN773Ar				(ValSft_R00(_rd32(0x3002008c))&BitMask_08)
#define ADC_CKSEL_EN773Aw(val)			_wr32(0x3002008c,(UINT)((_rd32(0x3002008c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define MIRR_ON_EN773Ar					(ValSft_R31(_rd32(0x30020090))&BitMask_01)
#define MIRR_ON_EN773Aw(val)			_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define FLIP_ON_EN773Ar					(ValSft_R30(_rd32(0x30020090))&BitMask_01)
#define FLIP_ON_EN773Aw(val)			_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define STILL_EN773Ar					(ValSft_R29(_rd32(0x30020090))&BitMask_01)
#define STILL_EN773Aw(val)				_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define SD_BYPASS_EN773Ar				(ValSft_R28(_rd32(0x30020090))&BitMask_01)
#define SD_BYPASS_EN773Aw(val)			_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define SD_HWI_EN773Ar					(ValSft_R16(_rd32(0x30020090))&BitMask_12)
#define SD_HWI_EN773Aw(val)				_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define SD_MODE_EN773Ar					(ValSft_R12(_rd32(0x30020090))&BitMask_04)
#define SD_MODE_EN773Aw(val)			_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define WDR_12BIT_EN773Ar				(ValSft_R11(_rd32(0x30020090))&BitMask_01)
#define WDR_12BIT_EN773Aw(val)			_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define SD_VWI_EN773Ar					(ValSft_R00(_rd32(0x30020090))&BitMask_11)
#define SD_VWI_EN773Aw(val)				_wr32(0x30020090,(UINT)((_rd32(0x30020090)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define REF_CNT_EN773Ar					(ValSft_R30(_rd32(0x30020094))&BitMask_02)
#define REF_CNT_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define SD_DRST_EN773Ar					(ValSft_R28(_rd32(0x30020094))&BitMask_02)
#define SD_DRST_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define SD_PTON_EN773Ar					(ValSft_R27(_rd32(0x30020094))&BitMask_01)
#define SD_PTON_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define SD_MRSA_EN773Ar					(ValSft_R26(_rd32(0x30020094))&BitMask_01)
#define SD_MRSA_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define DQSI_STEP_EN773Ar				(ValSft_R24(_rd32(0x30020094))&BitMask_02)
#define DQSI_STEP_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define DQSO_STEP_EN773Ar				(ValSft_R22(_rd32(0x30020094))&BitMask_02)
#define DQSO_STEP_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define SD_VDOFAST_EN773Ar				(ValSft_R21(_rd32(0x30020094))&BitMask_01)
#define SD_VDOFAST_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define SD_PWON_EN773Ar					(ValSft_R20(_rd32(0x30020094))&BitMask_01)
#define SD_PWON_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define OCSEL_EN773Ar					(ValSft_R13(_rd32(0x30020094))&BitMask_02)
#define OCSEL_EN773Aw(val)				_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L13(BitMask_02)))|ValSft_L13((val)&BitMask_02)))

#define ZHSP_OFS_EN773Ar				(ValSft_R00(_rd32(0x30020094))&BitMask_13)
#define ZHSP_OFS_EN773Aw(val)			_wr32(0x30020094,(UINT)((_rd32(0x30020094)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ZHSP_POS_EN773Ar				(ValSft_R00(_rd32(0x30020098))&BitMask_24)
#define ZHSP_POS_EN773Aw(val)			_wr32(0x30020098,(UINT)((_rd32(0x30020098)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define ZVSP_POS_EN773Ar				(ValSft_R00(_rd32(0x3002009c))&BitMask_23)
#define ZVSP_POS_EN773Aw(val)			_wr32(0x3002009c,(UINT)((_rd32(0x3002009c)&(~ValSft_L00(BitMask_23)))|ValSft_L00((val)&BitMask_23)))

#define ZVSP_KY_EN773Ar					(ValSft_R16(_rd32(0x300200a0))&BitMask_13)
#define ZVSP_KY_EN773Aw(val)			_wr32(0x300200a0,(UINT)((_rd32(0x300200a0)&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define ZHSP_KX_EN773Ar					(ValSft_R00(_rd32(0x300200a0))&BitMask_13)
#define ZHSP_KX_EN773Aw(val)			_wr32(0x300200a0,(UINT)((_rd32(0x300200a0)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WDR_ON_EN773Ar					(ValSft_R31(_rd32(0x300200a4))&BitMask_01)
#define WDR_ON_EN773Aw(val)				_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INSEL_EN773Ar					(ValSft_R28(_rd32(0x300200a4))&BitMask_03)
#define INSEL_EN773Aw(val)				_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define ICSEL_EN773Ar					(ValSft_R26(_rd32(0x300200a4))&BitMask_02)
#define ICSEL_EN773Aw(val)				_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define POL_VSI_EN773Ar					(ValSft_R25(_rd32(0x300200a4))&BitMask_01)
#define POL_VSI_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define POL_HSI_EN773Ar					(ValSft_R24(_rd32(0x300200a4))&BitMask_01)
#define POL_HSI_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define TRG_VSI_EN773Ar					(ValSft_R23(_rd32(0x300200a4))&BitMask_01)
#define TRG_VSI_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define TRG_HSI_EN773Ar					(ValSft_R22(_rd32(0x300200a4))&BitMask_01)
#define TRG_HSI_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define TRG_DIN_EN773Ar					(ValSft_R21(_rd32(0x300200a4))&BitMask_01)
#define TRG_DIN_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define CH_SSEL_EN773Ar					(ValSft_R20(_rd32(0x300200a4))&BitMask_01)
#define CH_SSEL_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define CH_DSEL_EN773Ar					(ValSft_R19(_rd32(0x300200a4))&BitMask_01)
#define CH_DSEL_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define PRE_OSEL_EN773Ar				(ValSft_R12(_rd32(0x300200a4))&BitMask_04)
#define PRE_OSEL_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define PREGAIN_EN773Ar					(ValSft_R00(_rd32(0x300200a4))&BitMask_10)
#define PREGAIN_EN773Aw(val)			_wr32(0x300200a4,(UINT)((_rd32(0x300200a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define VLOCKI_POS_EN773Ar				(ValSft_R27(_rd32(0x300200a8))&BitMask_05)
#define VLOCKI_POS_EN773Aw(val)			_wr32(0x300200a8,(UINT)((_rd32(0x300200a8)&(~ValSft_L27(BitMask_05)))|ValSft_L27((val)&BitMask_05)))

#define VSPI_EN773Ar					(ValSft_R16(_rd32(0x300200a8))&BitMask_11)
#define VSPI_EN773Aw(val)				_wr32(0x300200a8,(UINT)((_rd32(0x300200a8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HSPI_EN773Ar					(ValSft_R00(_rd32(0x300200a8))&BitMask_12)
#define HSPI_EN773Aw(val)				_wr32(0x300200a8,(UINT)((_rd32(0x300200a8)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VWI_EN773Ar						(ValSft_R16(_rd32(0x300200ac))&BitMask_11)
#define VWI_EN773Aw(val)				_wr32(0x300200ac,(UINT)((_rd32(0x300200ac)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HWI_EN773Ar						(ValSft_R00(_rd32(0x300200ac))&BitMask_12)
#define HWI_EN773Aw(val)				_wr32(0x300200ac,(UINT)((_rd32(0x300200ac)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CLAMP_ON_EN773Ar				(ValSft_R31(_rd32(0x300200b0))&BitMask_01)
#define CLAMP_ON_EN773Aw(val)			_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CLAMP_OSD_ON_EN773Ar			(ValSft_R30(_rd32(0x300200b0))&BitMask_01)
#define CLAMP_OSD_ON_EN773Aw(val)		_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CLAMP_RBINV_EN773Ar				(ValSft_R29(_rd32(0x300200b0))&BitMask_01)
#define CLAMP_RBINV_EN773Aw(val)		_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define CLAMP_YGINV_EN773Ar				(ValSft_R28(_rd32(0x300200b0))&BitMask_01)
#define CLAMP_YGINV_EN773Aw(val)		_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define CLAMP_GROFFSET_EN773Ar			(ValSft_R16(_rd32(0x300200b0))&BitMask_10)
#define CLAMP_GROFFSET_EN773Aw(val)		_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CLAMP_GBOFFSET_EN773Ar			(ValSft_R00(_rd32(0x300200b0))&BitMask_10)
#define CLAMP_GBOFFSET_EN773Aw(val)		_wr32(0x300200b0,(UINT)((_rd32(0x300200b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CLAMP_ROFFSET_EN773Ar			(ValSft_R16(_rd32(0x300200b4))&BitMask_10)
#define CLAMP_ROFFSET_EN773Aw(val)		_wr32(0x300200b4,(UINT)((_rd32(0x300200b4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CLAMP_BOFFSET_EN773Ar			(ValSft_R00(_rd32(0x300200b4))&BitMask_10)
#define CLAMP_BOFFSET_EN773Aw(val)		_wr32(0x300200b4,(UINT)((_rd32(0x300200b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CLAMP_HW_EN773Ar				(ValSft_R28(_rd32(0x300200b8))&BitMask_03)
#define CLAMP_HW_EN773Aw(val)			_wr32(0x300200b8,(UINT)((_rd32(0x300200b8)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define CLAMP_HSP_EN773Ar				(ValSft_R16(_rd32(0x300200b8))&BitMask_12)
#define CLAMP_HSP_EN773Aw(val)			_wr32(0x300200b8,(UINT)((_rd32(0x300200b8)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define CLAMP_VW_EN773Ar				(ValSft_R12(_rd32(0x300200b8))&BitMask_03)
#define CLAMP_VW_EN773Aw(val)			_wr32(0x300200b8,(UINT)((_rd32(0x300200b8)&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define CLAMP_VSP_EN773Ar				(ValSft_R00(_rd32(0x300200b8))&BitMask_11)
#define CLAMP_VSP_EN773Aw(val)			_wr32(0x300200b8,(UINT)((_rd32(0x300200b8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define SHADE_ON_EN773Ar				(ValSft_R31(_rd32(0x300200c8))&BitMask_01)
#define SHADE_ON_EN773Aw(val)			_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SHADE_VER_EN773Ar				(ValSft_R30(_rd32(0x300200c8))&BitMask_01)
#define SHADE_VER_EN773Aw(val)			_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SHADE_BILINEARY_EN773Ar			(ValSft_R24(_rd32(0x300200c8))&BitMask_05)
#define SHADE_BILINEARY_EN773Aw(val)	_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))

#define SHADE_OSDON_EN773Ar				(ValSft_R22(_rd32(0x300200c8))&BitMask_02)
#define SHADE_OSDON_EN773Aw(val)		_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define SHADE_BILINEARX_EN773Ar			(ValSft_R16(_rd32(0x300200c8))&BitMask_05)
#define SHADE_BILINEARX_EN773Aw(val)	_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))

#define SHADE_SGAIN_EN773Ar				(ValSft_R08(_rd32(0x300200c8))&BitMask_08)
#define SHADE_SGAIN_EN773Aw(val)		_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define SHADE_LGAIN_EN773Ar				(ValSft_R00(_rd32(0x300200c8))&BitMask_08)
#define SHADE_LGAIN_EN773Aw(val)		_wr32(0x300200c8,(UINT)((_rd32(0x300200c8)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_CWEGHT_EN773Ar				(ValSft_R30(_rd32(0x300200cc))&BitMask_02)
#define DF_CWEGHT_EN773Aw(val)			_wr32(0x300200cc,(UINT)((_rd32(0x300200cc)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define DF_ALPHA_EN773Ar				(ValSft_R24(_rd32(0x300200cc))&BitMask_06)
#define DF_ALPHA_EN773Aw(val)			_wr32(0x300200cc,(UINT)((_rd32(0x300200cc)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define DF_BETA_EN773Ar					(ValSft_R16(_rd32(0x300200cc))&BitMask_08)
#define DF_BETA_EN773Aw(val)			_wr32(0x300200cc,(UINT)((_rd32(0x300200cc)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DF_DIFGA_EN773Ar				(ValSft_R08(_rd32(0x300200cc))&BitMask_08)
#define DF_DIFGA_EN773Aw(val)			_wr32(0x300200cc,(UINT)((_rd32(0x300200cc)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DF_DIFTH_EN773Ar				(ValSft_R00(_rd32(0x300200cc))&BitMask_08)
#define DF_DIFTH_EN773Aw(val)			_wr32(0x300200cc,(UINT)((_rd32(0x300200cc)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_TSEL_EN773Ar					(ValSft_R24(_rd32(0x300200d0))&BitMask_03)
#define DF_TSEL_EN773Aw(val)			_wr32(0x300200d0,(UINT)((_rd32(0x300200d0)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define DFS_RBG_SEL_EN773Ar				(ValSft_R15(_rd32(0x300200d0))&BitMask_01)
#define DFS_RBG_SEL_EN773Aw(val)		_wr32(0x300200d0,(UINT)((_rd32(0x300200d0)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define DFS_DIFGA_EN773Ar				(ValSft_R08(_rd32(0x300200d0))&BitMask_07)
#define DFS_DIFGA_EN773Aw(val)			_wr32(0x300200d0,(UINT)((_rd32(0x300200d0)&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define DFS_DIFTH_EN773Ar				(ValSft_R00(_rd32(0x300200d0))&BitMask_08)
#define DFS_DIFTH_EN773Aw(val)			_wr32(0x300200d0,(UINT)((_rd32(0x300200d0)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_CMD_EN773Ar					(ValSft_R28(_rd32(0x300200d4))&BitMask_03)
#define DF_CMD_EN773Aw(val)				_wr32(0x300200d4,(UINT)((_rd32(0x300200d4)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define DF_OSDON_EN773Ar				(ValSft_R24(_rd32(0x300200d4))&BitMask_03)
#define DF_OSDON_EN773Aw(val)			_wr32(0x300200d4,(UINT)((_rd32(0x300200d4)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define DF_DTHRES_EN773Ar				(ValSft_R08(_rd32(0x300200d4))&BitMask_08)
#define DF_DTHRES_EN773Aw(val)			_wr32(0x300200d4,(UINT)((_rd32(0x300200d4)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RGB_DIR_THR_EN773Ar				(ValSft_R00(_rd32(0x300200d4))&BitMask_08)
#define RGB_DIR_THR_EN773Aw(val)		_wr32(0x300200d4,(UINT)((_rd32(0x300200d4)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_DETHEP_EN773Ar				(ValSft_R16(_rd32(0x300200d8))&BitMask_12)
#define DF_DETHEP_EN773Aw(val)			_wr32(0x300200d8,(UINT)((_rd32(0x300200d8)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_DETHSP_EN773Ar				(ValSft_R00(_rd32(0x300200d8))&BitMask_12)
#define DF_DETHSP_EN773Aw(val)			_wr32(0x300200d8,(UINT)((_rd32(0x300200d8)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DF_DETVEP_EN773Ar				(ValSft_R16(_rd32(0x300200dc))&BitMask_11)
#define DF_DETVEP_EN773Aw(val)			_wr32(0x300200dc,(UINT)((_rd32(0x300200dc)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define DF_DETVSP_EN773Ar				(ValSft_R00(_rd32(0x300200dc))&BitMask_11)
#define DF_DETVSP_EN773Aw(val)			_wr32(0x300200dc,(UINT)((_rd32(0x300200dc)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define DF_TESTON_EN773Ar				(ValSft_R31(_rd32(0x300200e0))&BitMask_01)
#define DF_TESTON_EN773Aw(val)			_wr32(0x300200e0,(UINT)((_rd32(0x300200e0)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DF_TESTPH1_EN773Ar				(ValSft_R16(_rd32(0x300200e0))&BitMask_12)
#define DF_TESTPH1_EN773Aw(val)			_wr32(0x300200e0,(UINT)((_rd32(0x300200e0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV1_EN773Ar				(ValSft_R00(_rd32(0x300200e0))&BitMask_11)
#define DF_TESTPV1_EN773Aw(val)			_wr32(0x300200e0,(UINT)((_rd32(0x300200e0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define DF_TESTPH2_EN773Ar				(ValSft_R16(_rd32(0x300200e4))&BitMask_12)
#define DF_TESTPH2_EN773Aw(val)			_wr32(0x300200e4,(UINT)((_rd32(0x300200e4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV2_EN773Ar				(ValSft_R00(_rd32(0x300200e4))&BitMask_11)
#define DF_TESTPV2_EN773Aw(val)			_wr32(0x300200e4,(UINT)((_rd32(0x300200e4)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define DF_TESTPH3_EN773Ar				(ValSft_R16(_rd32(0x300200e8))&BitMask_12)
#define DF_TESTPH3_EN773Aw(val)			_wr32(0x300200e8,(UINT)((_rd32(0x300200e8)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV3_EN773Ar				(ValSft_R00(_rd32(0x300200e8))&BitMask_11)
#define DF_TESTPV3_EN773Aw(val)			_wr32(0x300200e8,(UINT)((_rd32(0x300200e8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define DF_TESTPH4_EN773Ar				(ValSft_R16(_rd32(0x300200ec))&BitMask_12)
#define DF_TESTPH4_EN773Aw(val)			_wr32(0x300200ec,(UINT)((_rd32(0x300200ec)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV4_EN773Ar				(ValSft_R00(_rd32(0x300200ec))&BitMask_11)
#define DF_TESTPV4_EN773Aw(val)			_wr32(0x300200ec,(UINT)((_rd32(0x300200ec)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define DF_TESTPLV_EN773Ar				(ValSft_R16(_rd32(0x300200f0))&BitMask_12)
#define DF_TESTPLV_EN773Aw(val)			_wr32(0x300200f0,(UINT)((_rd32(0x300200f0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define PRR_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300200f4))&BitMask_11)
#define PRR_GAIN_EN773Aw(val)			_wr32(0x300200f4,(UINT)((_rd32(0x300200f4)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define PRG_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300200f4))&BitMask_12)
#define PRG_GAIN_EN773Aw(val)			_wr32(0x300200f4,(UINT)((_rd32(0x300200f4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PRB_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300200f8))&BitMask_12)
#define PRB_GAIN_EN773Aw(val)			_wr32(0x300200f8,(UINT)((_rd32(0x300200f8)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define PGR_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300200f8))&BitMask_12)
#define PGR_GAIN_EN773Aw(val)			_wr32(0x300200f8,(UINT)((_rd32(0x300200f8)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PGG_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300200fc))&BitMask_11)
#define PGG_GAIN_EN773Aw(val)			_wr32(0x300200fc,(UINT)((_rd32(0x300200fc)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define PGB_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300200fc))&BitMask_12)
#define PGB_GAIN_EN773Aw(val)			_wr32(0x300200fc,(UINT)((_rd32(0x300200fc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PBR_GAIN_EN773Ar				(ValSft_R16(_rd32(0x30020100))&BitMask_12)
#define PBR_GAIN_EN773Aw(val)			_wr32(0x30020100,(UINT)((_rd32(0x30020100)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define PBG_GAIN_EN773Ar				(ValSft_R00(_rd32(0x30020100))&BitMask_12)
#define PBG_GAIN_EN773Aw(val)			_wr32(0x30020100,(UINT)((_rd32(0x30020100)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PBB_GAIN_EN773Ar				(ValSft_R00(_rd32(0x30020104))&BitMask_11)
#define PBB_GAIN_EN773Aw(val)			_wr32(0x30020104,(UINT)((_rd32(0x30020104)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define PYR_GAIN_EN773Ar				(ValSft_R24(_rd32(0x30020108))&BitMask_08)
#define PYR_GAIN_EN773Aw(val)			_wr32(0x30020108,(UINT)((_rd32(0x30020108)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define PYG_GAIN_EN773Ar				(ValSft_R16(_rd32(0x30020108))&BitMask_08)
#define PYG_GAIN_EN773Aw(val)			_wr32(0x30020108,(UINT)((_rd32(0x30020108)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define PYB_GAIN_EN773Ar				(ValSft_R08(_rd32(0x30020108))&BitMask_08)
#define PYB_GAIN_EN773Aw(val)			_wr32(0x30020108,(UINT)((_rd32(0x30020108)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define OZONE_SEL_EN773Ar				(ValSft_R00(_rd32(0x30020108))&BitMask_03)
#define OZONE_SEL_EN773Aw(val)			_wr32(0x30020108,(UINT)((_rd32(0x30020108)&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define AE_LOCK_SEL_EN773Ar				(ValSft_R31(_rd32(0x3002010c))&BitMask_01)
#define AE_LOCK_SEL_EN773Aw(val)		_wr32(0x3002010c,(UINT)((_rd32(0x3002010c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AE_WIN_SEL_EN773Ar				(ValSft_R16(_rd32(0x3002010c))&BitMask_06)
#define AE_WIN_SEL_EN773Aw(val)			_wr32(0x3002010c,(UINT)((_rd32(0x3002010c)&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define AE1_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020110))&BitMask_11)
#define AE1_HSP_EN773Aw(val)			_wr32(0x30020110,(UINT)((_rd32(0x30020110)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE1_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020110))&BitMask_11)
#define AE1_HEP_EN773Aw(val)			_wr32(0x30020110,(UINT)((_rd32(0x30020110)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE1_VSP_EN773Ar					(ValSft_R16(_rd32(0x30020114))&BitMask_11)
#define AE1_VSP_EN773Aw(val)			_wr32(0x30020114,(UINT)((_rd32(0x30020114)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE1_VEP_EN773Ar					(ValSft_R00(_rd32(0x30020114))&BitMask_11)
#define AE1_VEP_EN773Aw(val)			_wr32(0x30020114,(UINT)((_rd32(0x30020114)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE2_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020118))&BitMask_11)
#define AE2_HSP_EN773Aw(val)			_wr32(0x30020118,(UINT)((_rd32(0x30020118)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE2_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020118))&BitMask_11)
#define AE2_HEP_EN773Aw(val)			_wr32(0x30020118,(UINT)((_rd32(0x30020118)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE2_VSP_EN773Ar					(ValSft_R16(_rd32(0x3002011c))&BitMask_11)
#define AE2_VSP_EN773Aw(val)			_wr32(0x3002011c,(UINT)((_rd32(0x3002011c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE2_VEP_EN773Ar					(ValSft_R00(_rd32(0x3002011c))&BitMask_11)
#define AE2_VEP_EN773Aw(val)			_wr32(0x3002011c,(UINT)((_rd32(0x3002011c)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE3_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020120))&BitMask_11)
#define AE3_HSP_EN773Aw(val)			_wr32(0x30020120,(UINT)((_rd32(0x30020120)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE3_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020120))&BitMask_11)
#define AE3_HEP_EN773Aw(val)			_wr32(0x30020120,(UINT)((_rd32(0x30020120)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE3_VSP_EN773Ar					(ValSft_R16(_rd32(0x30020124))&BitMask_11)
#define AE3_VSP_EN773Aw(val)			_wr32(0x30020124,(UINT)((_rd32(0x30020124)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE3_VEP_EN773Ar					(ValSft_R00(_rd32(0x30020124))&BitMask_11)
#define AE3_VEP_EN773Aw(val)			_wr32(0x30020124,(UINT)((_rd32(0x30020124)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE4_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020128))&BitMask_11)
#define AE4_HSP_EN773Aw(val)			_wr32(0x30020128,(UINT)((_rd32(0x30020128)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE4_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020128))&BitMask_11)
#define AE4_HEP_EN773Aw(val)			_wr32(0x30020128,(UINT)((_rd32(0x30020128)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE4_VSP_EN773Ar					(ValSft_R16(_rd32(0x3002012c))&BitMask_11)
#define AE4_VSP_EN773Aw(val)			_wr32(0x3002012c,(UINT)((_rd32(0x3002012c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE4_VEP_EN773Ar					(ValSft_R00(_rd32(0x3002012c))&BitMask_11)
#define AE4_VEP_EN773Aw(val)			_wr32(0x3002012c,(UINT)((_rd32(0x3002012c)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE5_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020130))&BitMask_11)
#define AE5_HSP_EN773Aw(val)			_wr32(0x30020130,(UINT)((_rd32(0x30020130)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE5_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020130))&BitMask_11)
#define AE5_HEP_EN773Aw(val)			_wr32(0x30020130,(UINT)((_rd32(0x30020130)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE5_VSP_EN773Ar					(ValSft_R16(_rd32(0x30020134))&BitMask_11)
#define AE5_VSP_EN773Aw(val)			_wr32(0x30020134,(UINT)((_rd32(0x30020134)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE5_VEP_EN773Ar					(ValSft_R00(_rd32(0x30020134))&BitMask_11)
#define AE5_VEP_EN773Aw(val)			_wr32(0x30020134,(UINT)((_rd32(0x30020134)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE6_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020138))&BitMask_11)
#define AE6_HSP_EN773Aw(val)			_wr32(0x30020138,(UINT)((_rd32(0x30020138)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE6_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020138))&BitMask_11)
#define AE6_HEP_EN773Aw(val)			_wr32(0x30020138,(UINT)((_rd32(0x30020138)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE6_VSP_EN773Ar					(ValSft_R16(_rd32(0x3002013c))&BitMask_11)
#define AE6_VSP_EN773Aw(val)			_wr32(0x3002013c,(UINT)((_rd32(0x3002013c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AE6_VEP_EN773Ar					(ValSft_R00(_rd32(0x3002013c))&BitMask_11)
#define AE6_VEP_EN773Aw(val)			_wr32(0x3002013c,(UINT)((_rd32(0x3002013c)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE1_SLICE_EN773Ar				(ValSft_R16(_rd32(0x30020140))&BitMask_10)
#define AE1_SLICE_EN773Aw(val)			_wr32(0x30020140,(UINT)((_rd32(0x30020140)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE1_CLIP_EN773Ar				(ValSft_R00(_rd32(0x30020140))&BitMask_10)
#define AE1_CLIP_EN773Aw(val)			_wr32(0x30020140,(UINT)((_rd32(0x30020140)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE2_SLICE_EN773Ar				(ValSft_R16(_rd32(0x30020144))&BitMask_10)
#define AE2_SLICE_EN773Aw(val)			_wr32(0x30020144,(UINT)((_rd32(0x30020144)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE2_CLIP_EN773Ar				(ValSft_R00(_rd32(0x30020144))&BitMask_10)
#define AE2_CLIP_EN773Aw(val)			_wr32(0x30020144,(UINT)((_rd32(0x30020144)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE3_SLICE_EN773Ar				(ValSft_R16(_rd32(0x30020148))&BitMask_10)
#define AE3_SLICE_EN773Aw(val)			_wr32(0x30020148,(UINT)((_rd32(0x30020148)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE3_CLIP_EN773Ar				(ValSft_R00(_rd32(0x30020148))&BitMask_10)
#define AE3_CLIP_EN773Aw(val)			_wr32(0x30020148,(UINT)((_rd32(0x30020148)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE4_SLICE_EN773Ar				(ValSft_R16(_rd32(0x3002014c))&BitMask_10)
#define AE4_SLICE_EN773Aw(val)			_wr32(0x3002014c,(UINT)((_rd32(0x3002014c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE4_CLIP_EN773Ar				(ValSft_R00(_rd32(0x3002014c))&BitMask_10)
#define AE4_CLIP_EN773Aw(val)			_wr32(0x3002014c,(UINT)((_rd32(0x3002014c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE5_SLICE_EN773Ar				(ValSft_R16(_rd32(0x30020150))&BitMask_10)
#define AE5_SLICE_EN773Aw(val)			_wr32(0x30020150,(UINT)((_rd32(0x30020150)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE5_CLIP_EN773Ar				(ValSft_R00(_rd32(0x30020150))&BitMask_10)
#define AE5_CLIP_EN773Aw(val)			_wr32(0x30020150,(UINT)((_rd32(0x30020150)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE6_SLICE_EN773Ar				(ValSft_R16(_rd32(0x30020154))&BitMask_10)
#define AE6_SLICE_EN773Aw(val)			_wr32(0x30020154,(UINT)((_rd32(0x30020154)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE6_CLIP_EN773Ar				(ValSft_R00(_rd32(0x30020154))&BitMask_10)
#define AE6_CLIP_EN773Aw(val)			_wr32(0x30020154,(UINT)((_rd32(0x30020154)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define HISTO0_MAX_EN773Ar				(ValSft_R24(_rd32(0x30020158))&BitMask_08)
#define HISTO0_MAX_EN773Aw(val)			_wr32(0x30020158,(UINT)((_rd32(0x30020158)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define HISTO1_MAX_EN773Ar				(ValSft_R16(_rd32(0x30020158))&BitMask_08)
#define HISTO1_MAX_EN773Aw(val)			_wr32(0x30020158,(UINT)((_rd32(0x30020158)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define HISTO2_MAX_EN773Ar				(ValSft_R08(_rd32(0x30020158))&BitMask_08)
#define HISTO2_MAX_EN773Aw(val)			_wr32(0x30020158,(UINT)((_rd32(0x30020158)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define HISTO3_MAX_EN773Ar				(ValSft_R00(_rd32(0x30020158))&BitMask_08)
#define HISTO3_MAX_EN773Aw(val)			_wr32(0x30020158,(UINT)((_rd32(0x30020158)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HISTO4_MAX_EN773Ar				(ValSft_R24(_rd32(0x3002015c))&BitMask_08)
#define HISTO4_MAX_EN773Aw(val)			_wr32(0x3002015c,(UINT)((_rd32(0x3002015c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define HISTO5_MAX_EN773Ar				(ValSft_R16(_rd32(0x3002015c))&BitMask_08)
#define HISTO5_MAX_EN773Aw(val)			_wr32(0x3002015c,(UINT)((_rd32(0x3002015c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define HISTO6_MAX_EN773Ar				(ValSft_R08(_rd32(0x3002015c))&BitMask_08)
#define HISTO6_MAX_EN773Aw(val)			_wr32(0x3002015c,(UINT)((_rd32(0x3002015c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define HISTO7_MAX_EN773Ar				(ValSft_R00(_rd32(0x3002015c))&BitMask_08)
#define HISTO7_MAX_EN773Aw(val)			_wr32(0x3002015c,(UINT)((_rd32(0x3002015c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HISTO8_MAX_EN773Ar				(ValSft_R08(_rd32(0x30020160))&BitMask_08)
#define HISTO8_MAX_EN773Aw(val)			_wr32(0x30020160,(UINT)((_rd32(0x30020160)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define HISTO9_MAX_EN773Ar				(ValSft_R00(_rd32(0x30020160))&BitMask_08)
#define HISTO9_MAX_EN773Aw(val)			_wr32(0x30020160,(UINT)((_rd32(0x30020160)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AF1_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020164))&BitMask_11)
#define AF1_HSP_EN773Aw(val)			_wr32(0x30020164,(UINT)((_rd32(0x30020164)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AF1_HEP_EN773Ar					(ValSft_R00(_rd32(0x30020164))&BitMask_11)
#define AF1_HEP_EN773Aw(val)			_wr32(0x30020164,(UINT)((_rd32(0x30020164)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AF1_VSP_EN773Ar					(ValSft_R16(_rd32(0x30020168))&BitMask_11)
#define AF1_VSP_EN773Aw(val)			_wr32(0x30020168,(UINT)((_rd32(0x30020168)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AF1_VEP_EN773Ar					(ValSft_R00(_rd32(0x30020168))&BitMask_11)
#define AF1_VEP_EN773Aw(val)			_wr32(0x30020168,(UINT)((_rd32(0x30020168)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AF2_HSP_EN773Ar					(ValSft_R16(_rd32(0x3002016c))&BitMask_11)
#define AF2_HSP_EN773Aw(val)			_wr32(0x3002016c,(UINT)((_rd32(0x3002016c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AF2_HEP_EN773Ar					(ValSft_R00(_rd32(0x3002016c))&BitMask_11)
#define AF2_HEP_EN773Aw(val)			_wr32(0x3002016c,(UINT)((_rd32(0x3002016c)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AF2_VSP_EN773Ar					(ValSft_R16(_rd32(0x30020170))&BitMask_11)
#define AF2_VSP_EN773Aw(val)			_wr32(0x30020170,(UINT)((_rd32(0x30020170)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AF2_VEP_EN773Ar					(ValSft_R00(_rd32(0x30020170))&BitMask_11)
#define AF2_VEP_EN773Aw(val)			_wr32(0x30020170,(UINT)((_rd32(0x30020170)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AF_CLIP_EN773Ar					(ValSft_R16(_rd32(0x30020174))&BitMask_10)
#define AF_CLIP_EN773Aw(val)			_wr32(0x30020174,(UINT)((_rd32(0x30020174)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AF_SLICE_EN773Ar				(ValSft_R00(_rd32(0x30020174))&BitMask_10)
#define AF_SLICE_EN773Aw(val)			_wr32(0x30020174,(UINT)((_rd32(0x30020174)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AF_ON_EN773Ar					(ValSft_R31(_rd32(0x30020178))&BitMask_01)
#define AF_ON_EN773Aw(val)				_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AF_CLIP_ON_EN773Ar				(ValSft_R30(_rd32(0x30020178))&BitMask_01)
#define AF_CLIP_ON_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define AF_SSMPL_EN773Ar				(ValSft_R29(_rd32(0x30020178))&BitMask_01)
#define AF_SSMPL_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define AF2_HTAB_EN773Ar				(ValSft_R12(_rd32(0x30020178))&BitMask_03)
#define AF2_HTAB_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define AF1_HTAB_EN773Ar				(ValSft_R08(_rd32(0x30020178))&BitMask_03)
#define AF1_HTAB_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define AF_WIN_SEL_EN773Ar				(ValSft_R04(_rd32(0x30020178))&BitMask_02)
#define AF_WIN_SEL_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define AF_DSEL_EN773Ar					(ValSft_R01(_rd32(0x30020178))&BitMask_02)
#define AF_DSEL_EN773Aw(val)			_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L01(BitMask_02)))|ValSft_L01((val)&BitMask_02)))

#define AF_LOCK_SEL_EN773Ar				(ValSft_R00(_rd32(0x30020178))&BitMask_01)
#define AF_LOCK_SEL_EN773Aw(val)		_wr32(0x30020178,(UINT)((_rd32(0x30020178)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define ODM_M1_EN773Ar					(ValSft_R16(_rd32(0x3002017c))&BitMask_10)
#define ODM_M1_EN773Aw(val)				_wr32(0x3002017c,(UINT)((_rd32(0x3002017c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ODM_M2_EN773Ar					(ValSft_R00(_rd32(0x3002017c))&BitMask_10)
#define ODM_M2_EN773Aw(val)				_wr32(0x3002017c,(UINT)((_rd32(0x3002017c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M3_EN773Ar					(ValSft_R16(_rd32(0x30020180))&BitMask_10)
#define ODM_M3_EN773Aw(val)				_wr32(0x30020180,(UINT)((_rd32(0x30020180)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ODM_M4_EN773Ar					(ValSft_R00(_rd32(0x30020180))&BitMask_10)
#define ODM_M4_EN773Aw(val)				_wr32(0x30020180,(UINT)((_rd32(0x30020180)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M5_EN773Ar					(ValSft_R16(_rd32(0x30020184))&BitMask_10)
#define ODM_M5_EN773Aw(val)				_wr32(0x30020184,(UINT)((_rd32(0x30020184)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ODM_M6_EN773Ar					(ValSft_R00(_rd32(0x30020184))&BitMask_10)
#define ODM_M6_EN773Aw(val)				_wr32(0x30020184,(UINT)((_rd32(0x30020184)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M7_EN773Ar					(ValSft_R16(_rd32(0x30020188))&BitMask_10)
#define ODM_M7_EN773Aw(val)				_wr32(0x30020188,(UINT)((_rd32(0x30020188)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ODM_M8_EN773Ar					(ValSft_R00(_rd32(0x30020188))&BitMask_10)
#define ODM_M8_EN773Aw(val)				_wr32(0x30020188,(UINT)((_rd32(0x30020188)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M9_EN773Ar					(ValSft_R00(_rd32(0x3002018c))&BitMask_10)
#define ODM_M9_EN773Aw(val)				_wr32(0x3002018c,(UINT)((_rd32(0x3002018c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWB_WIN1_HSP_EN773Ar			(ValSft_R16(_rd32(0x30020190))&BitMask_11)
#define AWB_WIN1_HSP_EN773Aw(val)		_wr32(0x30020190,(UINT)((_rd32(0x30020190)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AWB_WIN1_HW_EN773Ar				(ValSft_R00(_rd32(0x30020190))&BitMask_11)
#define AWB_WIN1_HW_EN773Aw(val)		_wr32(0x30020190,(UINT)((_rd32(0x30020190)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AWB_WIN1_VSP_EN773Ar			(ValSft_R16(_rd32(0x30020194))&BitMask_11)
#define AWB_WIN1_VSP_EN773Aw(val)		_wr32(0x30020194,(UINT)((_rd32(0x30020194)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AWB_WIN1_VW_EN773Ar				(ValSft_R00(_rd32(0x30020194))&BitMask_11)
#define AWB_WIN1_VW_EN773Aw(val)		_wr32(0x30020194,(UINT)((_rd32(0x30020194)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AWBL0_DROFFSET_EN773Ar			(ValSft_R16(_rd32(0x30020198))&BitMask_10)
#define AWBL0_DROFFSET_EN773Aw(val)		_wr32(0x30020198,(UINT)((_rd32(0x30020198)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL0_DBOFFSET_EN773Ar			(ValSft_R00(_rd32(0x30020198))&BitMask_10)
#define AWBL0_DBOFFSET_EN773Aw(val)		_wr32(0x30020198,(UINT)((_rd32(0x30020198)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_HTAB_SEL_EN773Ar			(ValSft_R30(_rd32(0x3002019c))&BitMask_02)
#define AWBL_HTAB_SEL_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define AWB_LOCK_SEL_EN773Ar			(ValSft_R29(_rd32(0x3002019c))&BitMask_01)
#define AWB_LOCK_SEL_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define AWBLNOR_SEL_EN773Ar				(ValSft_R28(_rd32(0x3002019c))&BitMask_01)
#define AWBLNOR_SEL_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define AWBLCBCRO_SEL_EN773Ar			(ValSft_R27(_rd32(0x3002019c))&BitMask_01)
#define AWBLCBCRO_SEL_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define AWBLYEDGE_TH_EN773Ar			(ValSft_R16(_rd32(0x3002019c))&BitMask_10)
#define AWBLYEDGE_TH_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_DBGAIN0_EN773Ar			(ValSft_R08(_rd32(0x3002019c))&BitMask_08)
#define AWBL_DBGAIN0_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define AWBL_DRGAIN0_EN773Ar			(ValSft_R00(_rd32(0x3002019c))&BitMask_08)
#define AWBL_DRGAIN0_EN773Aw(val)		_wr32(0x3002019c,(UINT)((_rd32(0x3002019c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AWBL_CLSL_ISEL_EN773Ar			(ValSft_R31(_rd32(0x300201a0))&BitMask_01)
#define AWBL_CLSL_ISEL_EN773Aw(val)		_wr32(0x300201a0,(UINT)((_rd32(0x300201a0)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AWBL_CYCLIP_EN773Ar				(ValSft_R16(_rd32(0x300201a0))&BitMask_10)
#define AWBL_CYCLIP_EN773Aw(val)		_wr32(0x300201a0,(UINT)((_rd32(0x300201a0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_OSD_SEL_EN773Ar			(ValSft_R00(_rd32(0x300201a0))&BitMask_08)
#define AWBL_OSD_SEL_EN773Aw(val)		_wr32(0x300201a0,(UINT)((_rd32(0x300201a0)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AWBLOSD_ON_EN773Ar				(ValSft_R31(_rd32(0x300201a4))&BitMask_01)
#define AWBLOSD_ON_EN773Aw(val)			_wr32(0x300201a4,(UINT)((_rd32(0x300201a4)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AWBL_CYSLICE_EN773Ar			(ValSft_R00(_rd32(0x300201a4))&BitMask_10)
#define AWBL_CYSLICE_EN773Aw(val)		_wr32(0x300201a4,(UINT)((_rd32(0x300201a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CRSLICE_EN773Ar			(ValSft_R16(_rd32(0x300201a8))&BitMask_10)
#define AWBL_CRSLICE_EN773Aw(val)		_wr32(0x300201a8,(UINT)((_rd32(0x300201a8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CRCLIP_EN773Ar				(ValSft_R00(_rd32(0x300201a8))&BitMask_10)
#define AWBL_CRCLIP_EN773Aw(val)		_wr32(0x300201a8,(UINT)((_rd32(0x300201a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CGSLICE_EN773Ar			(ValSft_R16(_rd32(0x300201ac))&BitMask_10)
#define AWBL_CGSLICE_EN773Aw(val)		_wr32(0x300201ac,(UINT)((_rd32(0x300201ac)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CGCLIP_EN773Ar				(ValSft_R00(_rd32(0x300201ac))&BitMask_10)
#define AWBL_CGCLIP_EN773Aw(val)		_wr32(0x300201ac,(UINT)((_rd32(0x300201ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CBSLICE_EN773Ar			(ValSft_R16(_rd32(0x300201b0))&BitMask_10)
#define AWBL_CBSLICE_EN773Aw(val)		_wr32(0x300201b0,(UINT)((_rd32(0x300201b0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CBCLIP_EN773Ar				(ValSft_R00(_rd32(0x300201b0))&BitMask_10)
#define AWBL_CBCLIP_EN773Aw(val)		_wr32(0x300201b0,(UINT)((_rd32(0x300201b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CM_VSP_EN773Ar				(ValSft_R16(_rd32(0x300201b4))&BitMask_11)
#define AWBL_CM_VSP_EN773Aw(val)		_wr32(0x300201b4,(UINT)((_rd32(0x300201b4)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define AWBL_CM_HSP_EN773Ar				(ValSft_R00(_rd32(0x300201b4))&BitMask_11)
#define AWBL_CM_HSP_EN773Aw(val)		_wr32(0x300201b4,(UINT)((_rd32(0x300201b4)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AWBL_CM000_EN773Ar				(ValSft_R00(_rd32(0x300201c0))&BitMask_32)
#define AWBL_CM000_EN773Aw(val)			_wr32(0x300201c0,(UINT)((_rd32(0x300201c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM001_EN773Ar				(ValSft_R00(_rd32(0x300201c4))&BitMask_32)
#define AWBL_CM001_EN773Aw(val)			_wr32(0x300201c4,(UINT)((_rd32(0x300201c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM002_EN773Ar				(ValSft_R00(_rd32(0x300201c8))&BitMask_32)
#define AWBL_CM002_EN773Aw(val)			_wr32(0x300201c8,(UINT)((_rd32(0x300201c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM003_EN773Ar				(ValSft_R00(_rd32(0x300201cc))&BitMask_32)
#define AWBL_CM003_EN773Aw(val)			_wr32(0x300201cc,(UINT)((_rd32(0x300201cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM004_EN773Ar				(ValSft_R00(_rd32(0x300201d0))&BitMask_32)
#define AWBL_CM004_EN773Aw(val)			_wr32(0x300201d0,(UINT)((_rd32(0x300201d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM005_EN773Ar				(ValSft_R00(_rd32(0x300201d4))&BitMask_32)
#define AWBL_CM005_EN773Aw(val)			_wr32(0x300201d4,(UINT)((_rd32(0x300201d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM006_EN773Ar				(ValSft_R00(_rd32(0x300201d8))&BitMask_32)
#define AWBL_CM006_EN773Aw(val)			_wr32(0x300201d8,(UINT)((_rd32(0x300201d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM007_EN773Ar				(ValSft_R00(_rd32(0x300201dc))&BitMask_32)
#define AWBL_CM007_EN773Aw(val)			_wr32(0x300201dc,(UINT)((_rd32(0x300201dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM008_EN773Ar				(ValSft_R00(_rd32(0x300201e0))&BitMask_32)
#define AWBL_CM008_EN773Aw(val)			_wr32(0x300201e0,(UINT)((_rd32(0x300201e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM009_EN773Ar				(ValSft_R00(_rd32(0x300201e4))&BitMask_32)
#define AWBL_CM009_EN773Aw(val)			_wr32(0x300201e4,(UINT)((_rd32(0x300201e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM010_EN773Ar				(ValSft_R00(_rd32(0x300201e8))&BitMask_32)
#define AWBL_CM010_EN773Aw(val)			_wr32(0x300201e8,(UINT)((_rd32(0x300201e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM011_EN773Ar				(ValSft_R00(_rd32(0x300201ec))&BitMask_32)
#define AWBL_CM011_EN773Aw(val)			_wr32(0x300201ec,(UINT)((_rd32(0x300201ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM012_EN773Ar				(ValSft_R00(_rd32(0x300201f0))&BitMask_32)
#define AWBL_CM012_EN773Aw(val)			_wr32(0x300201f0,(UINT)((_rd32(0x300201f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM013_EN773Ar				(ValSft_R00(_rd32(0x300201f4))&BitMask_32)
#define AWBL_CM013_EN773Aw(val)			_wr32(0x300201f4,(UINT)((_rd32(0x300201f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM014_EN773Ar				(ValSft_R00(_rd32(0x300201f8))&BitMask_32)
#define AWBL_CM014_EN773Aw(val)			_wr32(0x300201f8,(UINT)((_rd32(0x300201f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM015_EN773Ar				(ValSft_R00(_rd32(0x300201fc))&BitMask_32)
#define AWBL_CM015_EN773Aw(val)			_wr32(0x300201fc,(UINT)((_rd32(0x300201fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM016_EN773Ar				(ValSft_R00(_rd32(0x30020200))&BitMask_32)
#define AWBL_CM016_EN773Aw(val)			_wr32(0x30020200,(UINT)((_rd32(0x30020200)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM017_EN773Ar				(ValSft_R00(_rd32(0x30020204))&BitMask_32)
#define AWBL_CM017_EN773Aw(val)			_wr32(0x30020204,(UINT)((_rd32(0x30020204)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM018_EN773Ar				(ValSft_R00(_rd32(0x30020208))&BitMask_32)
#define AWBL_CM018_EN773Aw(val)			_wr32(0x30020208,(UINT)((_rd32(0x30020208)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM019_EN773Ar				(ValSft_R00(_rd32(0x3002020c))&BitMask_32)
#define AWBL_CM019_EN773Aw(val)			_wr32(0x3002020c,(UINT)((_rd32(0x3002020c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM020_EN773Ar				(ValSft_R00(_rd32(0x30020210))&BitMask_32)
#define AWBL_CM020_EN773Aw(val)			_wr32(0x30020210,(UINT)((_rd32(0x30020210)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM021_EN773Ar				(ValSft_R00(_rd32(0x30020214))&BitMask_32)
#define AWBL_CM021_EN773Aw(val)			_wr32(0x30020214,(UINT)((_rd32(0x30020214)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM022_EN773Ar				(ValSft_R00(_rd32(0x30020218))&BitMask_32)
#define AWBL_CM022_EN773Aw(val)			_wr32(0x30020218,(UINT)((_rd32(0x30020218)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM023_EN773Ar				(ValSft_R00(_rd32(0x3002021c))&BitMask_32)
#define AWBL_CM023_EN773Aw(val)			_wr32(0x3002021c,(UINT)((_rd32(0x3002021c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM024_EN773Ar				(ValSft_R00(_rd32(0x30020220))&BitMask_32)
#define AWBL_CM024_EN773Aw(val)			_wr32(0x30020220,(UINT)((_rd32(0x30020220)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM025_EN773Ar				(ValSft_R00(_rd32(0x30020224))&BitMask_32)
#define AWBL_CM025_EN773Aw(val)			_wr32(0x30020224,(UINT)((_rd32(0x30020224)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM026_EN773Ar				(ValSft_R00(_rd32(0x30020228))&BitMask_32)
#define AWBL_CM026_EN773Aw(val)			_wr32(0x30020228,(UINT)((_rd32(0x30020228)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM027_EN773Ar				(ValSft_R00(_rd32(0x3002022c))&BitMask_32)
#define AWBL_CM027_EN773Aw(val)			_wr32(0x3002022c,(UINT)((_rd32(0x3002022c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM028_EN773Ar				(ValSft_R00(_rd32(0x30020230))&BitMask_32)
#define AWBL_CM028_EN773Aw(val)			_wr32(0x30020230,(UINT)((_rd32(0x30020230)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM029_EN773Ar				(ValSft_R00(_rd32(0x30020234))&BitMask_32)
#define AWBL_CM029_EN773Aw(val)			_wr32(0x30020234,(UINT)((_rd32(0x30020234)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM030_EN773Ar				(ValSft_R00(_rd32(0x30020238))&BitMask_32)
#define AWBL_CM030_EN773Aw(val)			_wr32(0x30020238,(UINT)((_rd32(0x30020238)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM031_EN773Ar				(ValSft_R00(_rd32(0x3002023c))&BitMask_32)
#define AWBL_CM031_EN773Aw(val)			_wr32(0x3002023c,(UINT)((_rd32(0x3002023c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM032_EN773Ar				(ValSft_R00(_rd32(0x30020240))&BitMask_32)
#define AWBL_CM032_EN773Aw(val)			_wr32(0x30020240,(UINT)((_rd32(0x30020240)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM033_EN773Ar				(ValSft_R00(_rd32(0x30020244))&BitMask_32)
#define AWBL_CM033_EN773Aw(val)			_wr32(0x30020244,(UINT)((_rd32(0x30020244)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM034_EN773Ar				(ValSft_R00(_rd32(0x30020248))&BitMask_32)
#define AWBL_CM034_EN773Aw(val)			_wr32(0x30020248,(UINT)((_rd32(0x30020248)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM035_EN773Ar				(ValSft_R00(_rd32(0x3002024c))&BitMask_32)
#define AWBL_CM035_EN773Aw(val)			_wr32(0x3002024c,(UINT)((_rd32(0x3002024c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM036_EN773Ar				(ValSft_R00(_rd32(0x30020250))&BitMask_32)
#define AWBL_CM036_EN773Aw(val)			_wr32(0x30020250,(UINT)((_rd32(0x30020250)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM037_EN773Ar				(ValSft_R00(_rd32(0x30020254))&BitMask_32)
#define AWBL_CM037_EN773Aw(val)			_wr32(0x30020254,(UINT)((_rd32(0x30020254)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM038_EN773Ar				(ValSft_R00(_rd32(0x30020258))&BitMask_32)
#define AWBL_CM038_EN773Aw(val)			_wr32(0x30020258,(UINT)((_rd32(0x30020258)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM039_EN773Ar				(ValSft_R00(_rd32(0x3002025c))&BitMask_32)
#define AWBL_CM039_EN773Aw(val)			_wr32(0x3002025c,(UINT)((_rd32(0x3002025c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM040_EN773Ar				(ValSft_R00(_rd32(0x30020260))&BitMask_32)
#define AWBL_CM040_EN773Aw(val)			_wr32(0x30020260,(UINT)((_rd32(0x30020260)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM041_EN773Ar				(ValSft_R00(_rd32(0x30020264))&BitMask_32)
#define AWBL_CM041_EN773Aw(val)			_wr32(0x30020264,(UINT)((_rd32(0x30020264)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM042_EN773Ar				(ValSft_R00(_rd32(0x30020268))&BitMask_32)
#define AWBL_CM042_EN773Aw(val)			_wr32(0x30020268,(UINT)((_rd32(0x30020268)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM043_EN773Ar				(ValSft_R00(_rd32(0x3002026c))&BitMask_32)
#define AWBL_CM043_EN773Aw(val)			_wr32(0x3002026c,(UINT)((_rd32(0x3002026c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM044_EN773Ar				(ValSft_R00(_rd32(0x30020270))&BitMask_32)
#define AWBL_CM044_EN773Aw(val)			_wr32(0x30020270,(UINT)((_rd32(0x30020270)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM045_EN773Ar				(ValSft_R00(_rd32(0x30020274))&BitMask_32)
#define AWBL_CM045_EN773Aw(val)			_wr32(0x30020274,(UINT)((_rd32(0x30020274)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM046_EN773Ar				(ValSft_R00(_rd32(0x30020278))&BitMask_32)
#define AWBL_CM046_EN773Aw(val)			_wr32(0x30020278,(UINT)((_rd32(0x30020278)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM047_EN773Ar				(ValSft_R00(_rd32(0x3002027c))&BitMask_32)
#define AWBL_CM047_EN773Aw(val)			_wr32(0x3002027c,(UINT)((_rd32(0x3002027c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM048_EN773Ar				(ValSft_R00(_rd32(0x30020280))&BitMask_32)
#define AWBL_CM048_EN773Aw(val)			_wr32(0x30020280,(UINT)((_rd32(0x30020280)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM049_EN773Ar				(ValSft_R00(_rd32(0x30020284))&BitMask_32)
#define AWBL_CM049_EN773Aw(val)			_wr32(0x30020284,(UINT)((_rd32(0x30020284)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM050_EN773Ar				(ValSft_R00(_rd32(0x30020288))&BitMask_32)
#define AWBL_CM050_EN773Aw(val)			_wr32(0x30020288,(UINT)((_rd32(0x30020288)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM051_EN773Ar				(ValSft_R00(_rd32(0x3002028c))&BitMask_32)
#define AWBL_CM051_EN773Aw(val)			_wr32(0x3002028c,(UINT)((_rd32(0x3002028c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM052_EN773Ar				(ValSft_R00(_rd32(0x30020290))&BitMask_32)
#define AWBL_CM052_EN773Aw(val)			_wr32(0x30020290,(UINT)((_rd32(0x30020290)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM053_EN773Ar				(ValSft_R00(_rd32(0x30020294))&BitMask_32)
#define AWBL_CM053_EN773Aw(val)			_wr32(0x30020294,(UINT)((_rd32(0x30020294)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM054_EN773Ar				(ValSft_R00(_rd32(0x30020298))&BitMask_32)
#define AWBL_CM054_EN773Aw(val)			_wr32(0x30020298,(UINT)((_rd32(0x30020298)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM055_EN773Ar				(ValSft_R00(_rd32(0x3002029c))&BitMask_32)
#define AWBL_CM055_EN773Aw(val)			_wr32(0x3002029c,(UINT)((_rd32(0x3002029c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM056_EN773Ar				(ValSft_R00(_rd32(0x300202a0))&BitMask_32)
#define AWBL_CM056_EN773Aw(val)			_wr32(0x300202a0,(UINT)((_rd32(0x300202a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM057_EN773Ar				(ValSft_R00(_rd32(0x300202a4))&BitMask_32)
#define AWBL_CM057_EN773Aw(val)			_wr32(0x300202a4,(UINT)((_rd32(0x300202a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM058_EN773Ar				(ValSft_R00(_rd32(0x300202a8))&BitMask_32)
#define AWBL_CM058_EN773Aw(val)			_wr32(0x300202a8,(UINT)((_rd32(0x300202a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM059_EN773Ar				(ValSft_R00(_rd32(0x300202ac))&BitMask_32)
#define AWBL_CM059_EN773Aw(val)			_wr32(0x300202ac,(UINT)((_rd32(0x300202ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM060_EN773Ar				(ValSft_R00(_rd32(0x300202b0))&BitMask_32)
#define AWBL_CM060_EN773Aw(val)			_wr32(0x300202b0,(UINT)((_rd32(0x300202b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM061_EN773Ar				(ValSft_R00(_rd32(0x300202b4))&BitMask_32)
#define AWBL_CM061_EN773Aw(val)			_wr32(0x300202b4,(UINT)((_rd32(0x300202b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM062_EN773Ar				(ValSft_R00(_rd32(0x300202b8))&BitMask_32)
#define AWBL_CM062_EN773Aw(val)			_wr32(0x300202b8,(UINT)((_rd32(0x300202b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM063_EN773Ar				(ValSft_R00(_rd32(0x300202bc))&BitMask_32)
#define AWBL_CM063_EN773Aw(val)			_wr32(0x300202bc,(UINT)((_rd32(0x300202bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM064_EN773Ar				(ValSft_R00(_rd32(0x300202c0))&BitMask_32)
#define AWBL_CM064_EN773Aw(val)			_wr32(0x300202c0,(UINT)((_rd32(0x300202c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM065_EN773Ar				(ValSft_R00(_rd32(0x300202c4))&BitMask_32)
#define AWBL_CM065_EN773Aw(val)			_wr32(0x300202c4,(UINT)((_rd32(0x300202c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM066_EN773Ar				(ValSft_R00(_rd32(0x300202c8))&BitMask_32)
#define AWBL_CM066_EN773Aw(val)			_wr32(0x300202c8,(UINT)((_rd32(0x300202c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM067_EN773Ar				(ValSft_R00(_rd32(0x300202cc))&BitMask_32)
#define AWBL_CM067_EN773Aw(val)			_wr32(0x300202cc,(UINT)((_rd32(0x300202cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM068_EN773Ar				(ValSft_R00(_rd32(0x300202d0))&BitMask_32)
#define AWBL_CM068_EN773Aw(val)			_wr32(0x300202d0,(UINT)((_rd32(0x300202d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM069_EN773Ar				(ValSft_R00(_rd32(0x300202d4))&BitMask_32)
#define AWBL_CM069_EN773Aw(val)			_wr32(0x300202d4,(UINT)((_rd32(0x300202d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM070_EN773Ar				(ValSft_R00(_rd32(0x300202d8))&BitMask_32)
#define AWBL_CM070_EN773Aw(val)			_wr32(0x300202d8,(UINT)((_rd32(0x300202d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM071_EN773Ar				(ValSft_R00(_rd32(0x300202dc))&BitMask_32)
#define AWBL_CM071_EN773Aw(val)			_wr32(0x300202dc,(UINT)((_rd32(0x300202dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM072_EN773Ar				(ValSft_R00(_rd32(0x300202e0))&BitMask_32)
#define AWBL_CM072_EN773Aw(val)			_wr32(0x300202e0,(UINT)((_rd32(0x300202e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM073_EN773Ar				(ValSft_R00(_rd32(0x300202e4))&BitMask_32)
#define AWBL_CM073_EN773Aw(val)			_wr32(0x300202e4,(UINT)((_rd32(0x300202e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM074_EN773Ar				(ValSft_R00(_rd32(0x300202e8))&BitMask_32)
#define AWBL_CM074_EN773Aw(val)			_wr32(0x300202e8,(UINT)((_rd32(0x300202e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM075_EN773Ar				(ValSft_R00(_rd32(0x300202ec))&BitMask_32)
#define AWBL_CM075_EN773Aw(val)			_wr32(0x300202ec,(UINT)((_rd32(0x300202ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM076_EN773Ar				(ValSft_R00(_rd32(0x300202f0))&BitMask_32)
#define AWBL_CM076_EN773Aw(val)			_wr32(0x300202f0,(UINT)((_rd32(0x300202f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM077_EN773Ar				(ValSft_R00(_rd32(0x300202f4))&BitMask_32)
#define AWBL_CM077_EN773Aw(val)			_wr32(0x300202f4,(UINT)((_rd32(0x300202f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM078_EN773Ar				(ValSft_R00(_rd32(0x300202f8))&BitMask_32)
#define AWBL_CM078_EN773Aw(val)			_wr32(0x300202f8,(UINT)((_rd32(0x300202f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM079_EN773Ar				(ValSft_R00(_rd32(0x300202fc))&BitMask_32)
#define AWBL_CM079_EN773Aw(val)			_wr32(0x300202fc,(UINT)((_rd32(0x300202fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM080_EN773Ar				(ValSft_R00(_rd32(0x30020300))&BitMask_32)
#define AWBL_CM080_EN773Aw(val)			_wr32(0x30020300,(UINT)((_rd32(0x30020300)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM081_EN773Ar				(ValSft_R00(_rd32(0x30020304))&BitMask_32)
#define AWBL_CM081_EN773Aw(val)			_wr32(0x30020304,(UINT)((_rd32(0x30020304)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM082_EN773Ar				(ValSft_R00(_rd32(0x30020308))&BitMask_32)
#define AWBL_CM082_EN773Aw(val)			_wr32(0x30020308,(UINT)((_rd32(0x30020308)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM083_EN773Ar				(ValSft_R00(_rd32(0x3002030c))&BitMask_32)
#define AWBL_CM083_EN773Aw(val)			_wr32(0x3002030c,(UINT)((_rd32(0x3002030c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM084_EN773Ar				(ValSft_R00(_rd32(0x30020310))&BitMask_32)
#define AWBL_CM084_EN773Aw(val)			_wr32(0x30020310,(UINT)((_rd32(0x30020310)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM085_EN773Ar				(ValSft_R00(_rd32(0x30020314))&BitMask_32)
#define AWBL_CM085_EN773Aw(val)			_wr32(0x30020314,(UINT)((_rd32(0x30020314)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM086_EN773Ar				(ValSft_R00(_rd32(0x30020318))&BitMask_32)
#define AWBL_CM086_EN773Aw(val)			_wr32(0x30020318,(UINT)((_rd32(0x30020318)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM087_EN773Ar				(ValSft_R00(_rd32(0x3002031c))&BitMask_32)
#define AWBL_CM087_EN773Aw(val)			_wr32(0x3002031c,(UINT)((_rd32(0x3002031c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM088_EN773Ar				(ValSft_R00(_rd32(0x30020320))&BitMask_32)
#define AWBL_CM088_EN773Aw(val)			_wr32(0x30020320,(UINT)((_rd32(0x30020320)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM089_EN773Ar				(ValSft_R00(_rd32(0x30020324))&BitMask_32)
#define AWBL_CM089_EN773Aw(val)			_wr32(0x30020324,(UINT)((_rd32(0x30020324)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM090_EN773Ar				(ValSft_R00(_rd32(0x30020328))&BitMask_32)
#define AWBL_CM090_EN773Aw(val)			_wr32(0x30020328,(UINT)((_rd32(0x30020328)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM091_EN773Ar				(ValSft_R00(_rd32(0x3002032c))&BitMask_32)
#define AWBL_CM091_EN773Aw(val)			_wr32(0x3002032c,(UINT)((_rd32(0x3002032c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM092_EN773Ar				(ValSft_R00(_rd32(0x30020330))&BitMask_32)
#define AWBL_CM092_EN773Aw(val)			_wr32(0x30020330,(UINT)((_rd32(0x30020330)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM093_EN773Ar				(ValSft_R00(_rd32(0x30020334))&BitMask_32)
#define AWBL_CM093_EN773Aw(val)			_wr32(0x30020334,(UINT)((_rd32(0x30020334)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM094_EN773Ar				(ValSft_R00(_rd32(0x30020338))&BitMask_32)
#define AWBL_CM094_EN773Aw(val)			_wr32(0x30020338,(UINT)((_rd32(0x30020338)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM095_EN773Ar				(ValSft_R00(_rd32(0x3002033c))&BitMask_32)
#define AWBL_CM095_EN773Aw(val)			_wr32(0x3002033c,(UINT)((_rd32(0x3002033c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM096_EN773Ar				(ValSft_R00(_rd32(0x30020340))&BitMask_32)
#define AWBL_CM096_EN773Aw(val)			_wr32(0x30020340,(UINT)((_rd32(0x30020340)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM097_EN773Ar				(ValSft_R00(_rd32(0x30020344))&BitMask_32)
#define AWBL_CM097_EN773Aw(val)			_wr32(0x30020344,(UINT)((_rd32(0x30020344)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM098_EN773Ar				(ValSft_R00(_rd32(0x30020348))&BitMask_32)
#define AWBL_CM098_EN773Aw(val)			_wr32(0x30020348,(UINT)((_rd32(0x30020348)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM099_EN773Ar				(ValSft_R00(_rd32(0x3002034c))&BitMask_32)
#define AWBL_CM099_EN773Aw(val)			_wr32(0x3002034c,(UINT)((_rd32(0x3002034c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM100_EN773Ar				(ValSft_R00(_rd32(0x30020350))&BitMask_32)
#define AWBL_CM100_EN773Aw(val)			_wr32(0x30020350,(UINT)((_rd32(0x30020350)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM101_EN773Ar				(ValSft_R00(_rd32(0x30020354))&BitMask_32)
#define AWBL_CM101_EN773Aw(val)			_wr32(0x30020354,(UINT)((_rd32(0x30020354)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM102_EN773Ar				(ValSft_R00(_rd32(0x30020358))&BitMask_32)
#define AWBL_CM102_EN773Aw(val)			_wr32(0x30020358,(UINT)((_rd32(0x30020358)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM103_EN773Ar				(ValSft_R00(_rd32(0x3002035c))&BitMask_32)
#define AWBL_CM103_EN773Aw(val)			_wr32(0x3002035c,(UINT)((_rd32(0x3002035c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM104_EN773Ar				(ValSft_R00(_rd32(0x30020360))&BitMask_32)
#define AWBL_CM104_EN773Aw(val)			_wr32(0x30020360,(UINT)((_rd32(0x30020360)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM105_EN773Ar				(ValSft_R00(_rd32(0x30020364))&BitMask_32)
#define AWBL_CM105_EN773Aw(val)			_wr32(0x30020364,(UINT)((_rd32(0x30020364)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM106_EN773Ar				(ValSft_R00(_rd32(0x30020368))&BitMask_32)
#define AWBL_CM106_EN773Aw(val)			_wr32(0x30020368,(UINT)((_rd32(0x30020368)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM107_EN773Ar				(ValSft_R00(_rd32(0x3002036c))&BitMask_32)
#define AWBL_CM107_EN773Aw(val)			_wr32(0x3002036c,(UINT)((_rd32(0x3002036c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM108_EN773Ar				(ValSft_R00(_rd32(0x30020370))&BitMask_32)
#define AWBL_CM108_EN773Aw(val)			_wr32(0x30020370,(UINT)((_rd32(0x30020370)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM109_EN773Ar				(ValSft_R00(_rd32(0x30020374))&BitMask_32)
#define AWBL_CM109_EN773Aw(val)			_wr32(0x30020374,(UINT)((_rd32(0x30020374)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM110_EN773Ar				(ValSft_R00(_rd32(0x30020378))&BitMask_32)
#define AWBL_CM110_EN773Aw(val)			_wr32(0x30020378,(UINT)((_rd32(0x30020378)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM111_EN773Ar				(ValSft_R00(_rd32(0x3002037c))&BitMask_32)
#define AWBL_CM111_EN773Aw(val)			_wr32(0x3002037c,(UINT)((_rd32(0x3002037c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM112_EN773Ar				(ValSft_R00(_rd32(0x30020380))&BitMask_32)
#define AWBL_CM112_EN773Aw(val)			_wr32(0x30020380,(UINT)((_rd32(0x30020380)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM113_EN773Ar				(ValSft_R00(_rd32(0x30020384))&BitMask_32)
#define AWBL_CM113_EN773Aw(val)			_wr32(0x30020384,(UINT)((_rd32(0x30020384)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM114_EN773Ar				(ValSft_R00(_rd32(0x30020388))&BitMask_32)
#define AWBL_CM114_EN773Aw(val)			_wr32(0x30020388,(UINT)((_rd32(0x30020388)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM115_EN773Ar				(ValSft_R00(_rd32(0x3002038c))&BitMask_32)
#define AWBL_CM115_EN773Aw(val)			_wr32(0x3002038c,(UINT)((_rd32(0x3002038c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM116_EN773Ar				(ValSft_R00(_rd32(0x30020390))&BitMask_32)
#define AWBL_CM116_EN773Aw(val)			_wr32(0x30020390,(UINT)((_rd32(0x30020390)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM117_EN773Ar				(ValSft_R00(_rd32(0x30020394))&BitMask_32)
#define AWBL_CM117_EN773Aw(val)			_wr32(0x30020394,(UINT)((_rd32(0x30020394)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM118_EN773Ar				(ValSft_R00(_rd32(0x30020398))&BitMask_32)
#define AWBL_CM118_EN773Aw(val)			_wr32(0x30020398,(UINT)((_rd32(0x30020398)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM119_EN773Ar				(ValSft_R00(_rd32(0x3002039c))&BitMask_32)
#define AWBL_CM119_EN773Aw(val)			_wr32(0x3002039c,(UINT)((_rd32(0x3002039c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM120_EN773Ar				(ValSft_R00(_rd32(0x300203a0))&BitMask_32)
#define AWBL_CM120_EN773Aw(val)			_wr32(0x300203a0,(UINT)((_rd32(0x300203a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM121_EN773Ar				(ValSft_R00(_rd32(0x300203a4))&BitMask_32)
#define AWBL_CM121_EN773Aw(val)			_wr32(0x300203a4,(UINT)((_rd32(0x300203a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM122_EN773Ar				(ValSft_R00(_rd32(0x300203a8))&BitMask_32)
#define AWBL_CM122_EN773Aw(val)			_wr32(0x300203a8,(UINT)((_rd32(0x300203a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM123_EN773Ar				(ValSft_R00(_rd32(0x300203ac))&BitMask_32)
#define AWBL_CM123_EN773Aw(val)			_wr32(0x300203ac,(UINT)((_rd32(0x300203ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM124_EN773Ar				(ValSft_R00(_rd32(0x300203b0))&BitMask_32)
#define AWBL_CM124_EN773Aw(val)			_wr32(0x300203b0,(UINT)((_rd32(0x300203b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM125_EN773Ar				(ValSft_R00(_rd32(0x300203b4))&BitMask_32)
#define AWBL_CM125_EN773Aw(val)			_wr32(0x300203b4,(UINT)((_rd32(0x300203b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM126_EN773Ar				(ValSft_R00(_rd32(0x300203b8))&BitMask_32)
#define AWBL_CM126_EN773Aw(val)			_wr32(0x300203b8,(UINT)((_rd32(0x300203b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define AWBL_CM127_EN773Ar				(ValSft_R00(_rd32(0x300203bc))&BitMask_32)
#define AWBL_CM127_EN773Aw(val)			_wr32(0x300203bc,(UINT)((_rd32(0x300203bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IRIS1_ON_EN773Ar				(ValSft_R31(_rd32(0x300203c0))&BitMask_01)
#define IRIS1_ON_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IRIS1_INV_EN773Ar				(ValSft_R30(_rd32(0x300203c0))&BitMask_01)
#define IRIS1_INV_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define IRIS1_MOD_EN773Ar				(ValSft_R28(_rd32(0x300203c0))&BitMask_02)
#define IRIS1_MOD_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define IRIS1_SW_EN773Ar				(ValSft_R27(_rd32(0x300203c0))&BitMask_01)
#define IRIS1_SW_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define IRIS1_WSEL_EN773Ar				(ValSft_R24(_rd32(0x300203c0))&BitMask_03)
#define IRIS1_WSEL_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define IRIS1_FBK_EN773Ar				(ValSft_R16(_rd32(0x300203c0))&BitMask_08)
#define IRIS1_FBK_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define IRIS1_TLV_EN773Ar				(ValSft_R00(_rd32(0x300203c0))&BitMask_10)
#define IRIS1_TLV_EN773Aw(val)			_wr32(0x300203c0,(UINT)((_rd32(0x300203c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define IRIS1_TGA_EN773Ar				(ValSft_R16(_rd32(0x300203c4))&BitMask_10)
#define IRIS1_TGA_EN773Aw(val)			_wr32(0x300203c4,(UINT)((_rd32(0x300203c4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define IRIS1_OFS_EN773Ar				(ValSft_R00(_rd32(0x300203c4))&BitMask_16)
#define IRIS1_OFS_EN773Aw(val)			_wr32(0x300203c4,(UINT)((_rd32(0x300203c4)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS1_CLPL_EN773Ar				(ValSft_R16(_rd32(0x300203c8))&BitMask_16)
#define IRIS1_CLPL_EN773Aw(val)			_wr32(0x300203c8,(UINT)((_rd32(0x300203c8)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS1_CLPH_EN773Ar				(ValSft_R00(_rd32(0x300203c8))&BitMask_16)
#define IRIS1_CLPH_EN773Aw(val)			_wr32(0x300203c8,(UINT)((_rd32(0x300203c8)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS1_VSP_EN773Ar				(ValSft_R16(_rd32(0x300203cc))&BitMask_16)
#define IRIS1_VSP_EN773Aw(val)			_wr32(0x300203cc,(UINT)((_rd32(0x300203cc)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS1_VEP_EN773Ar				(ValSft_R00(_rd32(0x300203cc))&BitMask_16)
#define IRIS1_VEP_EN773Aw(val)			_wr32(0x300203cc,(UINT)((_rd32(0x300203cc)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS1_HSP_EN773Ar				(ValSft_R16(_rd32(0x300203d0))&BitMask_16)
#define IRIS1_HSP_EN773Aw(val)			_wr32(0x300203d0,(UINT)((_rd32(0x300203d0)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS1_HEP_EN773Ar				(ValSft_R00(_rd32(0x300203d0))&BitMask_16)
#define IRIS1_HEP_EN773Aw(val)			_wr32(0x300203d0,(UINT)((_rd32(0x300203d0)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS2_ON_EN773Ar				(ValSft_R31(_rd32(0x300203d4))&BitMask_01)
#define IRIS2_ON_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IRIS2_INV_EN773Ar				(ValSft_R30(_rd32(0x300203d4))&BitMask_01)
#define IRIS2_INV_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define IRIS2_MOD_EN773Ar				(ValSft_R28(_rd32(0x300203d4))&BitMask_02)
#define IRIS2_MOD_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define IRIS2_WSEL_EN773Ar				(ValSft_R24(_rd32(0x300203d4))&BitMask_03)
#define IRIS2_WSEL_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define IRIS2_FBK_EN773Ar				(ValSft_R16(_rd32(0x300203d4))&BitMask_08)
#define IRIS2_FBK_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define IRIS2_TLV_EN773Ar				(ValSft_R00(_rd32(0x300203d4))&BitMask_10)
#define IRIS2_TLV_EN773Aw(val)			_wr32(0x300203d4,(UINT)((_rd32(0x300203d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define IRIS2_TGA_EN773Ar				(ValSft_R16(_rd32(0x300203d8))&BitMask_10)
#define IRIS2_TGA_EN773Aw(val)			_wr32(0x300203d8,(UINT)((_rd32(0x300203d8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define IRIS2_OFS_EN773Ar				(ValSft_R00(_rd32(0x300203d8))&BitMask_16)
#define IRIS2_OFS_EN773Aw(val)			_wr32(0x300203d8,(UINT)((_rd32(0x300203d8)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS2_CLPL_EN773Ar				(ValSft_R16(_rd32(0x300203dc))&BitMask_16)
#define IRIS2_CLPL_EN773Aw(val)			_wr32(0x300203dc,(UINT)((_rd32(0x300203dc)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS2_CLPH_EN773Ar				(ValSft_R00(_rd32(0x300203dc))&BitMask_16)
#define IRIS2_CLPH_EN773Aw(val)			_wr32(0x300203dc,(UINT)((_rd32(0x300203dc)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS2_VSP_EN773Ar				(ValSft_R16(_rd32(0x300203e0))&BitMask_16)
#define IRIS2_VSP_EN773Aw(val)			_wr32(0x300203e0,(UINT)((_rd32(0x300203e0)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS2_VEP_EN773Ar				(ValSft_R00(_rd32(0x300203e0))&BitMask_16)
#define IRIS2_VEP_EN773Aw(val)			_wr32(0x300203e0,(UINT)((_rd32(0x300203e0)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS2_HSP_EN773Ar				(ValSft_R16(_rd32(0x300203e4))&BitMask_16)
#define IRIS2_HSP_EN773Aw(val)			_wr32(0x300203e4,(UINT)((_rd32(0x300203e4)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS2_HEP_EN773Ar				(ValSft_R00(_rd32(0x300203e4))&BitMask_16)
#define IRIS2_HEP_EN773Aw(val)			_wr32(0x300203e4,(UINT)((_rd32(0x300203e4)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RAND_PWMON_EN773Ar				(ValSft_R31(_rd32(0x300203e8))&BitMask_01)
#define RAND_PWMON_EN773Aw(val)			_wr32(0x300203e8,(UINT)((_rd32(0x300203e8)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RAND_PWMINV_EN773Ar				(ValSft_R30(_rd32(0x300203e8))&BitMask_01)
#define RAND_PWMINV_EN773Aw(val)		_wr32(0x300203e8,(UINT)((_rd32(0x300203e8)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define RAND_VEND_0_EN773Ar				(ValSft_R16(_rd32(0x300203ec))&BitMask_12)
#define RAND_VEND_0_EN773Aw(val)		_wr32(0x300203ec,(UINT)((_rd32(0x300203ec)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define RAND_VSTR_0_EN773Ar				(ValSft_R00(_rd32(0x300203ec))&BitMask_12)
#define RAND_VSTR_0_EN773Aw(val)		_wr32(0x300203ec,(UINT)((_rd32(0x300203ec)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define RAND_VEND_1_EN773Ar				(ValSft_R16(_rd32(0x300203f0))&BitMask_12)
#define RAND_VEND_1_EN773Aw(val)		_wr32(0x300203f0,(UINT)((_rd32(0x300203f0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define RAND_VSTR_1_EN773Ar				(ValSft_R00(_rd32(0x300203f0))&BitMask_12)
#define RAND_VSTR_1_EN773Aw(val)		_wr32(0x300203f0,(UINT)((_rd32(0x300203f0)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define GRID_0_EN773Ar					(ValSft_R24(_rd32(0x300203f4))&BitMask_08)
#define GRID_0_EN773Aw(val)				_wr32(0x300203f4,(UINT)((_rd32(0x300203f4)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define GRID_1_EN773Ar					(ValSft_R16(_rd32(0x300203f4))&BitMask_08)
#define GRID_1_EN773Aw(val)				_wr32(0x300203f4,(UINT)((_rd32(0x300203f4)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define FREE_RUN_0_EN773Ar				(ValSft_R15(_rd32(0x300203f4))&BitMask_01)
#define FREE_RUN_0_EN773Aw(val)			_wr32(0x300203f4,(UINT)((_rd32(0x300203f4)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define FREE_RUN_1_EN773Ar				(ValSft_R14(_rd32(0x300203f4))&BitMask_01)
#define FREE_RUN_1_EN773Aw(val)			_wr32(0x300203f4,(UINT)((_rd32(0x300203f4)&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define RAND_AREA_EN773Ar				(ValSft_R00(_rd32(0x300203f4))&BitMask_10)
#define RAND_AREA_EN773Aw(val)			_wr32(0x300203f4,(UINT)((_rd32(0x300203f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define THRES_0_EN773Ar					(ValSft_R16(_rd32(0x30020400))&BitMask_16)
#define THRES_0_EN773Aw(val)			_wr32(0x30020400,(UINT)((_rd32(0x30020400)&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define THRES_1_EN773Ar					(ValSft_R00(_rd32(0x30020400))&BitMask_16)
#define THRES_1_EN773Aw(val)			_wr32(0x30020400,(UINT)((_rd32(0x30020400)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define F_REG_0_EN773Ar					(ValSft_R16(_rd32(0x30020404))&BitMask_09)
#define F_REG_0_EN773Aw(val)			_wr32(0x30020404,(UINT)((_rd32(0x30020404)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define F_REG_1_EN773Ar					(ValSft_R00(_rd32(0x30020404))&BitMask_09)
#define F_REG_1_EN773Aw(val)			_wr32(0x30020404,(UINT)((_rd32(0x30020404)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define DNR3D_ON_EN773Ar				(ValSft_R31(_rd32(0x30020408))&BitMask_01)
#define DNR3D_ON_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DNR2D_ON_EN773Ar				(ValSft_R30(_rd32(0x30020408))&BitMask_01)
#define DNR2D_ON_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define DNROUT_SEL_EN773Ar				(ValSft_R24(_rd32(0x30020408))&BitMask_02)
#define DNROUT_SEL_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define DNR3D_GA_EN773Ar				(ValSft_R16(_rd32(0x30020408))&BitMask_06)
#define DNR3D_GA_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define DNR3D_TH_EN773Ar				(ValSft_R08(_rd32(0x30020408))&BitMask_08)
#define DNR3D_TH_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DNR3D_FK_EN773Ar				(ValSft_R00(_rd32(0x30020408))&BitMask_08)
#define DNR3D_FK_EN773Aw(val)			_wr32(0x30020408,(UINT)((_rd32(0x30020408)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DNR2D_WGTH_EN773Ar				(ValSft_R24(_rd32(0x3002040c))&BitMask_08)
#define DNR2D_WGTH_EN773Aw(val)			_wr32(0x3002040c,(UINT)((_rd32(0x3002040c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define DNR2D_WGTL_EN773Ar				(ValSft_R16(_rd32(0x3002040c))&BitMask_08)
#define DNR2D_WGTL_EN773Aw(val)			_wr32(0x3002040c,(UINT)((_rd32(0x3002040c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DNR2D_WGA_EN773Ar				(ValSft_R08(_rd32(0x3002040c))&BitMask_06)
#define DNR2D_WGA_EN773Aw(val)			_wr32(0x3002040c,(UINT)((_rd32(0x3002040c)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define DNR2D_WTH_EN773Ar				(ValSft_R00(_rd32(0x3002040c))&BitMask_08)
#define DNR2D_WTH_EN773Aw(val)			_wr32(0x3002040c,(UINT)((_rd32(0x3002040c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DNR2D_DTH_EN773Ar				(ValSft_R00(_rd32(0x30020410))&BitMask_08)
#define DNR2D_DTH_EN773Aw(val)			_wr32(0x30020410,(UINT)((_rd32(0x30020410)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define VLOCKO_START_EN773Ar			(ValSft_R00(_rd32(0x3002043c))&BitMask_01)
#define VLOCKO_START_EN773Aw(val)		_wr32(0x3002043c,(UINT)((_rd32(0x3002043c)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define REG_UPMODE_EN773Ar				(ValSft_R31(_rd32(0x30020440))&BitMask_01)
#define REG_UPMODE_EN773Aw(val)			_wr32(0x30020440,(UINT)((_rd32(0x30020440)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define OSYNC_MOD_EN773Ar				(ValSft_R30(_rd32(0x30020440))&BitMask_01)
#define OSYNC_MOD_EN773Aw(val)			_wr32(0x30020440,(UINT)((_rd32(0x30020440)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define OSYNC_POL_EN773Ar				(ValSft_R29(_rd32(0x30020440))&BitMask_01)
#define OSYNC_POL_EN773Aw(val)			_wr32(0x30020440,(UINT)((_rd32(0x30020440)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define OSYNC_TRG_EN773Ar				(ValSft_R28(_rd32(0x30020440))&BitMask_01)
#define OSYNC_TRG_EN773Aw(val)			_wr32(0x30020440,(UINT)((_rd32(0x30020440)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define HSPO2_EN773Ar					(ValSft_R00(_rd32(0x30020440))&BitMask_12)
#define HSPO2_EN773Aw(val)				_wr32(0x30020440,(UINT)((_rd32(0x30020440)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VTWO_EN773Ar					(ValSft_R16(_rd32(0x30020444))&BitMask_11)
#define VTWO_EN773Aw(val)				_wr32(0x30020444,(UINT)((_rd32(0x30020444)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HTWO_EN773Ar					(ValSft_R00(_rd32(0x30020444))&BitMask_12)
#define HTWO_EN773Aw(val)				_wr32(0x30020444,(UINT)((_rd32(0x30020444)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VSPO_EN773Ar					(ValSft_R16(_rd32(0x30020448))&BitMask_11)
#define VSPO_EN773Aw(val)				_wr32(0x30020448,(UINT)((_rd32(0x30020448)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HSPO_EN773Ar					(ValSft_R00(_rd32(0x30020448))&BitMask_12)
#define HSPO_EN773Aw(val)				_wr32(0x30020448,(UINT)((_rd32(0x30020448)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VWO_EN773Ar						(ValSft_R16(_rd32(0x3002044c))&BitMask_11)
#define VWO_EN773Aw(val)				_wr32(0x3002044c,(UINT)((_rd32(0x3002044c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HWO_EN773Ar						(ValSft_R00(_rd32(0x3002044c))&BitMask_12)
#define HWO_EN773Aw(val)				_wr32(0x3002044c,(UINT)((_rd32(0x3002044c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VSPC_EN773Ar					(ValSft_R16(_rd32(0x30020450))&BitMask_11)
#define VSPC_EN773Aw(val)				_wr32(0x30020450,(UINT)((_rd32(0x30020450)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HSPC_EN773Ar					(ValSft_R00(_rd32(0x30020450))&BitMask_12)
#define HSPC_EN773Aw(val)				_wr32(0x30020450,(UINT)((_rd32(0x30020450)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VWC_EN773Ar						(ValSft_R16(_rd32(0x30020454))&BitMask_11)
#define VWC_EN773Aw(val)				_wr32(0x30020454,(UINT)((_rd32(0x30020454)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HWC_EN773Ar						(ValSft_R00(_rd32(0x30020454))&BitMask_12)
#define HWC_EN773Aw(val)				_wr32(0x30020454,(UINT)((_rd32(0x30020454)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VACTO_ADJ_EN773Ar				(ValSft_R16(_rd32(0x30020458))&BitMask_11)
#define VACTO_ADJ_EN773Aw(val)			_wr32(0x30020458,(UINT)((_rd32(0x30020458)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HACTO_ADJ_EN773Ar				(ValSft_R00(_rd32(0x30020458))&BitMask_12)
#define HACTO_ADJ_EN773Aw(val)			_wr32(0x30020458,(UINT)((_rd32(0x30020458)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VLOCKO_POS_EN773Ar				(ValSft_R16(_rd32(0x3002045c))&BitMask_11)
#define VLOCKO_POS_EN773Aw(val)			_wr32(0x3002045c,(UINT)((_rd32(0x3002045c)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define HLOCKO_POS_EN773Ar				(ValSft_R00(_rd32(0x3002045c))&BitMask_12)
#define HLOCKO_POS_EN773Aw(val)			_wr32(0x3002045c,(UINT)((_rd32(0x3002045c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HSFP_EN773Ar					(ValSft_R16(_rd32(0x30020460))&BitMask_12)
#define HSFP_EN773Aw(val)				_wr32(0x30020460,(UINT)((_rd32(0x30020460)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define HSRP_EN773Ar					(ValSft_R00(_rd32(0x30020460))&BitMask_12)
#define HSRP_EN773Aw(val)				_wr32(0x30020460,(UINT)((_rd32(0x30020460)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VSFP_EN773Ar					(ValSft_R16(_rd32(0x30020464))&BitMask_11)
#define VSFP_EN773Aw(val)				_wr32(0x30020464,(UINT)((_rd32(0x30020464)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define VSRP_EN773Ar					(ValSft_R00(_rd32(0x30020464))&BitMask_11)
#define VSRP_EN773Aw(val)				_wr32(0x30020464,(UINT)((_rd32(0x30020464)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define FLDE_OFF_EN773Ar				(ValSft_R06(_rd32(0x30020468))&BitMask_01)
#define FLDE_OFF_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define FLDE_INV_EN773Ar				(ValSft_R05(_rd32(0x30020468))&BitMask_01)
#define FLDE_INV_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define VSO_TRG_EN773Ar					(ValSft_R04(_rd32(0x30020468))&BitMask_01)
#define VSO_TRG_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define VSO_OEN_EN773Ar					(ValSft_R03(_rd32(0x30020468))&BitMask_01)
#define VSO_OEN_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define HSO_OEN_EN773Ar					(ValSft_R02(_rd32(0x30020468))&BitMask_01)
#define HSO_OEN_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define VSO_INV_EN773Ar					(ValSft_R01(_rd32(0x30020468))&BitMask_01)
#define VSO_INV_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define HSO_INV_EN773Ar					(ValSft_R00(_rd32(0x30020468))&BitMask_01)
#define HSO_INV_EN773Aw(val)			_wr32(0x30020468,(UINT)((_rd32(0x30020468)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define VTWE_EN773Ar					(ValSft_R16(_rd32(0x3002046c))&BitMask_10)
#define VTWE_EN773Aw(val)				_wr32(0x3002046c,(UINT)((_rd32(0x3002046c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define HTWE_EN773Ar					(ValSft_R00(_rd32(0x3002046c))&BitMask_12)
#define HTWE_EN773Aw(val)				_wr32(0x3002046c,(UINT)((_rd32(0x3002046c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VSPE_EN773Ar					(ValSft_R16(_rd32(0x30020470))&BitMask_09)
#define VSPE_EN773Aw(val)				_wr32(0x30020470,(UINT)((_rd32(0x30020470)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define HSPE_EN773Ar					(ValSft_R00(_rd32(0x30020470))&BitMask_11)
#define HSPE_EN773Aw(val)				_wr32(0x30020470,(UINT)((_rd32(0x30020470)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define VWE_EN773Ar						(ValSft_R16(_rd32(0x30020474))&BitMask_09)
#define VWE_EN773Aw(val)				_wr32(0x30020474,(UINT)((_rd32(0x30020474)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define HWE_EN773Ar						(ValSft_R00(_rd32(0x30020474))&BitMask_10)
#define HWE_EN773Aw(val)				_wr32(0x30020474,(UINT)((_rd32(0x30020474)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YC_OSEL_EN773Ar					(ValSft_R28(_rd32(0x30020478))&BitMask_04)
#define YC_OSEL_EN773Aw(val)			_wr32(0x30020478,(UINT)((_rd32(0x30020478)&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define DS_VOFF_EN773Ar					(ValSft_R16(_rd32(0x30020478))&BitMask_11)
#define DS_VOFF_EN773Aw(val)			_wr32(0x30020478,(UINT)((_rd32(0x30020478)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define DS_HOFF_EN773Ar					(ValSft_R00(_rd32(0x30020478))&BitMask_12)
#define DS_HOFF_EN773Aw(val)			_wr32(0x30020478,(UINT)((_rd32(0x30020478)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define INTP_BGAIN_EN773Ar				(ValSft_R24(_rd32(0x3002047c))&BitMask_08)
#define INTP_BGAIN_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define INTP_RGAIN_EN773Ar				(ValSft_R16(_rd32(0x3002047c))&BitMask_08)
#define INTP_RGAIN_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RGB_DWGT_EN773Ar				(ValSft_R12(_rd32(0x3002047c))&BitMask_02)
#define RGB_DWGT_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define RGB_KCOFF3_EN773Ar				(ValSft_R08(_rd32(0x3002047c))&BitMask_04)
#define RGB_KCOFF3_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define RGB_KCOFF2_EN773Ar				(ValSft_R04(_rd32(0x3002047c))&BitMask_04)
#define RGB_KCOFF2_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define RGB_KCOFF1_EN773Ar				(ValSft_R00(_rd32(0x3002047c))&BitMask_04)
#define RGB_KCOFF1_EN773Aw(val)			_wr32(0x3002047c,(UINT)((_rd32(0x3002047c)&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define POST_YBGAIN_EN773Ar				(ValSft_R16(_rd32(0x30020480))&BitMask_08)
#define POST_YBGAIN_EN773Aw(val)		_wr32(0x30020480,(UINT)((_rd32(0x30020480)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define POST_YGGAIN_EN773Ar				(ValSft_R08(_rd32(0x30020480))&BitMask_08)
#define POST_YGGAIN_EN773Aw(val)		_wr32(0x30020480,(UINT)((_rd32(0x30020480)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define POST_YRGAIN_EN773Ar				(ValSft_R00(_rd32(0x30020480))&BitMask_08)
#define POST_YRGAIN_EN773Aw(val)		_wr32(0x30020480,(UINT)((_rd32(0x30020480)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define APT_ON_EN773Ar					(ValSft_R31(_rd32(0x30020484))&BitMask_01)
#define APT_ON_EN773Aw(val)				_wr32(0x30020484,(UINT)((_rd32(0x30020484)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define APT_GAIN_ON_EN773Ar				(ValSft_R30(_rd32(0x30020484))&BitMask_01)
#define APT_GAIN_ON_EN773Aw(val)		_wr32(0x30020484,(UINT)((_rd32(0x30020484)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define APT_TEST_EN773Ar				(ValSft_R28(_rd32(0x30020484))&BitMask_02)
#define APT_TEST_EN773Aw(val)			_wr32(0x30020484,(UINT)((_rd32(0x30020484)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define APT_TH2_EN773Ar					(ValSft_R16(_rd32(0x30020484))&BitMask_12)
#define APT_TH2_EN773Aw(val)			_wr32(0x30020484,(UINT)((_rd32(0x30020484)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define APT_TH1_EN773Ar					(ValSft_R00(_rd32(0x30020484))&BitMask_12)
#define APT_TH1_EN773Aw(val)			_wr32(0x30020484,(UINT)((_rd32(0x30020484)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define APT_TH3_EN773Ar					(ValSft_R00(_rd32(0x30020488))&BitMask_10)
#define APT_TH3_EN773Aw(val)			_wr32(0x30020488,(UINT)((_rd32(0x30020488)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define APT_GAIN2_NEG_EN773Ar			(ValSft_R24(_rd32(0x3002048c))&BitMask_08)
#define APT_GAIN2_NEG_EN773Aw(val)		_wr32(0x3002048c,(UINT)((_rd32(0x3002048c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define APT_GAIN1_NEG_EN773Ar			(ValSft_R16(_rd32(0x3002048c))&BitMask_08)
#define APT_GAIN1_NEG_EN773Aw(val)		_wr32(0x3002048c,(UINT)((_rd32(0x3002048c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define APT_GAIN2_POS_EN773Ar			(ValSft_R08(_rd32(0x3002048c))&BitMask_08)
#define APT_GAIN2_POS_EN773Aw(val)		_wr32(0x3002048c,(UINT)((_rd32(0x3002048c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define APT_GAIN1_POS_EN773Ar			(ValSft_R00(_rd32(0x3002048c))&BitMask_08)
#define APT_GAIN1_POS_EN773Aw(val)		_wr32(0x3002048c,(UINT)((_rd32(0x3002048c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define APT_SLIC3_EN773Ar				(ValSft_R16(_rd32(0x30020490))&BitMask_10)
#define APT_SLIC3_EN773Aw(val)			_wr32(0x30020490,(UINT)((_rd32(0x30020490)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define APT_CLIP3_EN773Ar				(ValSft_R00(_rd32(0x30020490))&BitMask_10)
#define APT_CLIP3_EN773Aw(val)			_wr32(0x30020490,(UINT)((_rd32(0x30020490)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YCGMK_EN773Ar					(ValSft_R16(_rd32(0x30020494))&BitMask_08)
#define YCGMK_EN773Aw(val)				_wr32(0x30020494,(UINT)((_rd32(0x30020494)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define APT_GAIN3_EN773Ar				(ValSft_R00(_rd32(0x30020494))&BitMask_08)
#define APT_GAIN3_EN773Aw(val)			_wr32(0x30020494,(UINT)((_rd32(0x30020494)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define APT_LPFK_EN773Ar				(ValSft_R24(_rd32(0x30020498))&BitMask_08)
#define APT_LPFK_EN773Aw(val)			_wr32(0x30020498,(UINT)((_rd32(0x30020498)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define APT_LPFGA_EN773Ar				(ValSft_R16(_rd32(0x30020498))&BitMask_08)
#define APT_LPFGA_EN773Aw(val)			_wr32(0x30020498,(UINT)((_rd32(0x30020498)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define APT_LPFTH_EN773Ar				(ValSft_R00(_rd32(0x30020498))&BitMask_10)
#define APT_LPFTH_EN773Aw(val)			_wr32(0x30020498,(UINT)((_rd32(0x30020498)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMA_ON_EN773Ar					(ValSft_R31(_rd32(0x3002049c))&BitMask_01)
#define YGMA_ON_EN773Aw(val)			_wr32(0x3002049c,(UINT)((_rd32(0x3002049c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CGMA_ON_EN773Ar					(ValSft_R30(_rd32(0x3002049c))&BitMask_01)
#define CGMA_ON_EN773Aw(val)			_wr32(0x3002049c,(UINT)((_rd32(0x3002049c)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define YGMY1_01_EN773Ar				(ValSft_R16(_rd32(0x3002049c))&BitMask_10)
#define YGMY1_01_EN773Aw(val)			_wr32(0x3002049c,(UINT)((_rd32(0x3002049c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_02_EN773Ar				(ValSft_R00(_rd32(0x3002049c))&BitMask_10)
#define YGMY1_02_EN773Aw(val)			_wr32(0x3002049c,(UINT)((_rd32(0x3002049c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_03_EN773Ar				(ValSft_R16(_rd32(0x300204a0))&BitMask_10)
#define YGMY1_03_EN773Aw(val)			_wr32(0x300204a0,(UINT)((_rd32(0x300204a0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_04_EN773Ar				(ValSft_R00(_rd32(0x300204a0))&BitMask_10)
#define YGMY1_04_EN773Aw(val)			_wr32(0x300204a0,(UINT)((_rd32(0x300204a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_05_EN773Ar				(ValSft_R16(_rd32(0x300204a4))&BitMask_10)
#define YGMY1_05_EN773Aw(val)			_wr32(0x300204a4,(UINT)((_rd32(0x300204a4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_06_EN773Ar				(ValSft_R00(_rd32(0x300204a4))&BitMask_10)
#define YGMY1_06_EN773Aw(val)			_wr32(0x300204a4,(UINT)((_rd32(0x300204a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_07_EN773Ar				(ValSft_R16(_rd32(0x300204a8))&BitMask_10)
#define YGMY1_07_EN773Aw(val)			_wr32(0x300204a8,(UINT)((_rd32(0x300204a8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_08_EN773Ar				(ValSft_R00(_rd32(0x300204a8))&BitMask_10)
#define YGMY1_08_EN773Aw(val)			_wr32(0x300204a8,(UINT)((_rd32(0x300204a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_09_EN773Ar				(ValSft_R16(_rd32(0x300204ac))&BitMask_10)
#define YGMY1_09_EN773Aw(val)			_wr32(0x300204ac,(UINT)((_rd32(0x300204ac)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_10_EN773Ar				(ValSft_R00(_rd32(0x300204ac))&BitMask_10)
#define YGMY1_10_EN773Aw(val)			_wr32(0x300204ac,(UINT)((_rd32(0x300204ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_11_EN773Ar				(ValSft_R16(_rd32(0x300204b0))&BitMask_10)
#define YGMY1_11_EN773Aw(val)			_wr32(0x300204b0,(UINT)((_rd32(0x300204b0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_12_EN773Ar				(ValSft_R00(_rd32(0x300204b0))&BitMask_10)
#define YGMY1_12_EN773Aw(val)			_wr32(0x300204b0,(UINT)((_rd32(0x300204b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_13_EN773Ar				(ValSft_R16(_rd32(0x300204b4))&BitMask_10)
#define YGMY1_13_EN773Aw(val)			_wr32(0x300204b4,(UINT)((_rd32(0x300204b4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_14_EN773Ar				(ValSft_R00(_rd32(0x300204b4))&BitMask_10)
#define YGMY1_14_EN773Aw(val)			_wr32(0x300204b4,(UINT)((_rd32(0x300204b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_01_EN773Ar				(ValSft_R16(_rd32(0x300204b8))&BitMask_10)
#define YGMY2_01_EN773Aw(val)			_wr32(0x300204b8,(UINT)((_rd32(0x300204b8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_02_EN773Ar				(ValSft_R00(_rd32(0x300204b8))&BitMask_10)
#define YGMY2_02_EN773Aw(val)			_wr32(0x300204b8,(UINT)((_rd32(0x300204b8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_03_EN773Ar				(ValSft_R16(_rd32(0x300204bc))&BitMask_10)
#define YGMY2_03_EN773Aw(val)			_wr32(0x300204bc,(UINT)((_rd32(0x300204bc)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_04_EN773Ar				(ValSft_R00(_rd32(0x300204bc))&BitMask_10)
#define YGMY2_04_EN773Aw(val)			_wr32(0x300204bc,(UINT)((_rd32(0x300204bc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_05_EN773Ar				(ValSft_R16(_rd32(0x300204c0))&BitMask_10)
#define YGMY2_05_EN773Aw(val)			_wr32(0x300204c0,(UINT)((_rd32(0x300204c0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_06_EN773Ar				(ValSft_R00(_rd32(0x300204c0))&BitMask_10)
#define YGMY2_06_EN773Aw(val)			_wr32(0x300204c0,(UINT)((_rd32(0x300204c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_07_EN773Ar				(ValSft_R16(_rd32(0x300204c4))&BitMask_10)
#define YGMY2_07_EN773Aw(val)			_wr32(0x300204c4,(UINT)((_rd32(0x300204c4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_08_EN773Ar				(ValSft_R00(_rd32(0x300204c4))&BitMask_10)
#define YGMY2_08_EN773Aw(val)			_wr32(0x300204c4,(UINT)((_rd32(0x300204c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_09_EN773Ar				(ValSft_R16(_rd32(0x300204c8))&BitMask_10)
#define YGMY2_09_EN773Aw(val)			_wr32(0x300204c8,(UINT)((_rd32(0x300204c8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_10_EN773Ar				(ValSft_R00(_rd32(0x300204c8))&BitMask_10)
#define YGMY2_10_EN773Aw(val)			_wr32(0x300204c8,(UINT)((_rd32(0x300204c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_11_EN773Ar				(ValSft_R16(_rd32(0x300204cc))&BitMask_10)
#define YGMY2_11_EN773Aw(val)			_wr32(0x300204cc,(UINT)((_rd32(0x300204cc)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_12_EN773Ar				(ValSft_R00(_rd32(0x300204cc))&BitMask_10)
#define YGMY2_12_EN773Aw(val)			_wr32(0x300204cc,(UINT)((_rd32(0x300204cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_13_EN773Ar				(ValSft_R16(_rd32(0x300204d0))&BitMask_10)
#define YGMY2_13_EN773Aw(val)			_wr32(0x300204d0,(UINT)((_rd32(0x300204d0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_14_EN773Ar				(ValSft_R00(_rd32(0x300204d0))&BitMask_10)
#define YGMY2_14_EN773Aw(val)			_wr32(0x300204d0,(UINT)((_rd32(0x300204d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WPRG_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300204d4))&BitMask_13)
#define WPRG_GAIN_EN773Aw(val)			_wr32(0x300204d4,(UINT)((_rd32(0x300204d4)&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPRR_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300204d4))&BitMask_13)
#define WPRR_GAIN_EN773Aw(val)			_wr32(0x300204d4,(UINT)((_rd32(0x300204d4)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPGR_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300204d8))&BitMask_13)
#define WPGR_GAIN_EN773Aw(val)			_wr32(0x300204d8,(UINT)((_rd32(0x300204d8)&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPRB_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300204d8))&BitMask_13)
#define WPRB_GAIN_EN773Aw(val)			_wr32(0x300204d8,(UINT)((_rd32(0x300204d8)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPGB_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300204dc))&BitMask_13)
#define WPGB_GAIN_EN773Aw(val)			_wr32(0x300204dc,(UINT)((_rd32(0x300204dc)&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPGG_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300204dc))&BitMask_13)
#define WPGG_GAIN_EN773Aw(val)			_wr32(0x300204dc,(UINT)((_rd32(0x300204dc)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPBG_GAIN_EN773Ar				(ValSft_R16(_rd32(0x300204e0))&BitMask_13)
#define WPBG_GAIN_EN773Aw(val)			_wr32(0x300204e0,(UINT)((_rd32(0x300204e0)&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPBR_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300204e0))&BitMask_13)
#define WPBR_GAIN_EN773Aw(val)			_wr32(0x300204e0,(UINT)((_rd32(0x300204e0)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPBB_GAIN_EN773Ar				(ValSft_R00(_rd32(0x300204e4))&BitMask_13)
#define WPBB_GAIN_EN773Aw(val)			_wr32(0x300204e4,(UINT)((_rd32(0x300204e4)&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CGMY1_01_EN773Ar				(ValSft_R16(_rd32(0x300204e8))&BitMask_10)
#define CGMY1_01_EN773Aw(val)			_wr32(0x300204e8,(UINT)((_rd32(0x300204e8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_02_EN773Ar				(ValSft_R00(_rd32(0x300204e8))&BitMask_10)
#define CGMY1_02_EN773Aw(val)			_wr32(0x300204e8,(UINT)((_rd32(0x300204e8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_03_EN773Ar				(ValSft_R16(_rd32(0x300204ec))&BitMask_10)
#define CGMY1_03_EN773Aw(val)			_wr32(0x300204ec,(UINT)((_rd32(0x300204ec)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_04_EN773Ar				(ValSft_R00(_rd32(0x300204ec))&BitMask_10)
#define CGMY1_04_EN773Aw(val)			_wr32(0x300204ec,(UINT)((_rd32(0x300204ec)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_05_EN773Ar				(ValSft_R16(_rd32(0x300204f0))&BitMask_10)
#define CGMY1_05_EN773Aw(val)			_wr32(0x300204f0,(UINT)((_rd32(0x300204f0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_06_EN773Ar				(ValSft_R00(_rd32(0x300204f0))&BitMask_10)
#define CGMY1_06_EN773Aw(val)			_wr32(0x300204f0,(UINT)((_rd32(0x300204f0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_07_EN773Ar				(ValSft_R16(_rd32(0x300204f4))&BitMask_10)
#define CGMY1_07_EN773Aw(val)			_wr32(0x300204f4,(UINT)((_rd32(0x300204f4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_08_EN773Ar				(ValSft_R00(_rd32(0x300204f4))&BitMask_10)
#define CGMY1_08_EN773Aw(val)			_wr32(0x300204f4,(UINT)((_rd32(0x300204f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_09_EN773Ar				(ValSft_R16(_rd32(0x300204f8))&BitMask_10)
#define CGMY1_09_EN773Aw(val)			_wr32(0x300204f8,(UINT)((_rd32(0x300204f8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_10_EN773Ar				(ValSft_R00(_rd32(0x300204f8))&BitMask_10)
#define CGMY1_10_EN773Aw(val)			_wr32(0x300204f8,(UINT)((_rd32(0x300204f8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_11_EN773Ar				(ValSft_R16(_rd32(0x300204fc))&BitMask_10)
#define CGMY1_11_EN773Aw(val)			_wr32(0x300204fc,(UINT)((_rd32(0x300204fc)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_12_EN773Ar				(ValSft_R00(_rd32(0x300204fc))&BitMask_10)
#define CGMY1_12_EN773Aw(val)			_wr32(0x300204fc,(UINT)((_rd32(0x300204fc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_13_EN773Ar				(ValSft_R16(_rd32(0x30020500))&BitMask_10)
#define CGMY1_13_EN773Aw(val)			_wr32(0x30020500,(UINT)((_rd32(0x30020500)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_14_EN773Ar				(ValSft_R00(_rd32(0x30020500))&BitMask_10)
#define CGMY1_14_EN773Aw(val)			_wr32(0x30020500,(UINT)((_rd32(0x30020500)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_01_EN773Ar				(ValSft_R16(_rd32(0x30020504))&BitMask_10)
#define CGMY2_01_EN773Aw(val)			_wr32(0x30020504,(UINT)((_rd32(0x30020504)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_02_EN773Ar				(ValSft_R00(_rd32(0x30020504))&BitMask_10)
#define CGMY2_02_EN773Aw(val)			_wr32(0x30020504,(UINT)((_rd32(0x30020504)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_03_EN773Ar				(ValSft_R16(_rd32(0x30020508))&BitMask_10)
#define CGMY2_03_EN773Aw(val)			_wr32(0x30020508,(UINT)((_rd32(0x30020508)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_04_EN773Ar				(ValSft_R00(_rd32(0x30020508))&BitMask_10)
#define CGMY2_04_EN773Aw(val)			_wr32(0x30020508,(UINT)((_rd32(0x30020508)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_05_EN773Ar				(ValSft_R16(_rd32(0x3002050c))&BitMask_10)
#define CGMY2_05_EN773Aw(val)			_wr32(0x3002050c,(UINT)((_rd32(0x3002050c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_06_EN773Ar				(ValSft_R00(_rd32(0x3002050c))&BitMask_10)
#define CGMY2_06_EN773Aw(val)			_wr32(0x3002050c,(UINT)((_rd32(0x3002050c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_07_EN773Ar				(ValSft_R16(_rd32(0x30020510))&BitMask_10)
#define CGMY2_07_EN773Aw(val)			_wr32(0x30020510,(UINT)((_rd32(0x30020510)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_08_EN773Ar				(ValSft_R00(_rd32(0x30020510))&BitMask_10)
#define CGMY2_08_EN773Aw(val)			_wr32(0x30020510,(UINT)((_rd32(0x30020510)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_09_EN773Ar				(ValSft_R16(_rd32(0x30020514))&BitMask_10)
#define CGMY2_09_EN773Aw(val)			_wr32(0x30020514,(UINT)((_rd32(0x30020514)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_10_EN773Ar				(ValSft_R00(_rd32(0x30020514))&BitMask_10)
#define CGMY2_10_EN773Aw(val)			_wr32(0x30020514,(UINT)((_rd32(0x30020514)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_11_EN773Ar				(ValSft_R16(_rd32(0x30020518))&BitMask_10)
#define CGMY2_11_EN773Aw(val)			_wr32(0x30020518,(UINT)((_rd32(0x30020518)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_12_EN773Ar				(ValSft_R00(_rd32(0x30020518))&BitMask_10)
#define CGMY2_12_EN773Aw(val)			_wr32(0x30020518,(UINT)((_rd32(0x30020518)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_13_EN773Ar				(ValSft_R16(_rd32(0x3002051c))&BitMask_10)
#define CGMY2_13_EN773Aw(val)			_wr32(0x3002051c,(UINT)((_rd32(0x3002051c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_14_EN773Ar				(ValSft_R00(_rd32(0x3002051c))&BitMask_10)
#define CGMY2_14_EN773Aw(val)			_wr32(0x3002051c,(UINT)((_rd32(0x3002051c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define RMYG_EN773Ar					(ValSft_R16(_rd32(0x30020520))&BitMask_10)
#define RMYG_EN773Aw(val)				_wr32(0x30020520,(UINT)((_rd32(0x30020520)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define RMYR_EN773Ar					(ValSft_R00(_rd32(0x30020520))&BitMask_10)
#define RMYR_EN773Aw(val)				_wr32(0x30020520,(UINT)((_rd32(0x30020520)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BMYR_EN773Ar					(ValSft_R16(_rd32(0x30020524))&BitMask_10)
#define BMYR_EN773Aw(val)				_wr32(0x30020524,(UINT)((_rd32(0x30020524)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define RMYB_EN773Ar					(ValSft_R00(_rd32(0x30020524))&BitMask_10)
#define RMYB_EN773Aw(val)				_wr32(0x30020524,(UINT)((_rd32(0x30020524)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BMYB_EN773Ar					(ValSft_R16(_rd32(0x30020528))&BitMask_10)
#define BMYB_EN773Aw(val)				_wr32(0x30020528,(UINT)((_rd32(0x30020528)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BMYG_EN773Ar					(ValSft_R00(_rd32(0x30020528))&BitMask_10)
#define BMYG_EN773Aw(val)				_wr32(0x30020528,(UINT)((_rd32(0x30020528)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BYGAINN_EN773Ar					(ValSft_R24(_rd32(0x3002052c))&BitMask_08)
#define BYGAINN_EN773Aw(val)			_wr32(0x3002052c,(UINT)((_rd32(0x3002052c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define BYGAINP_EN773Ar					(ValSft_R16(_rd32(0x3002052c))&BitMask_08)
#define BYGAINP_EN773Aw(val)			_wr32(0x3002052c,(UINT)((_rd32(0x3002052c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RYGAINN_EN773Ar					(ValSft_R08(_rd32(0x3002052c))&BitMask_08)
#define RYGAINN_EN773Aw(val)			_wr32(0x3002052c,(UINT)((_rd32(0x3002052c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RYGAINP_EN773Ar					(ValSft_R00(_rd32(0x3002052c))&BitMask_08)
#define RYGAINP_EN773Aw(val)			_wr32(0x3002052c,(UINT)((_rd32(0x3002052c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define BYHUEN_EN773Ar					(ValSft_R24(_rd32(0x30020530))&BitMask_08)
#define BYHUEN_EN773Aw(val)				_wr32(0x30020530,(UINT)((_rd32(0x30020530)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define BYHUEP_EN773Ar					(ValSft_R16(_rd32(0x30020530))&BitMask_08)
#define BYHUEP_EN773Aw(val)				_wr32(0x30020530,(UINT)((_rd32(0x30020530)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RYHUEN_EN773Ar					(ValSft_R08(_rd32(0x30020530))&BitMask_08)
#define RYHUEN_EN773Aw(val)				_wr32(0x30020530,(UINT)((_rd32(0x30020530)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RYHUEP_EN773Ar					(ValSft_R00(_rd32(0x30020530))&BitMask_08)
#define RYHUEP_EN773Aw(val)				_wr32(0x30020530,(UINT)((_rd32(0x30020530)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define LSUP_ON_EN773Ar					(ValSft_R31(_rd32(0x30020538))&BitMask_01)
#define LSUP_ON_EN773Aw(val)			_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LSUP_GA_EN773Ar					(ValSft_R24(_rd32(0x30020538))&BitMask_06)
#define LSUP_GA_EN773Aw(val)			_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define LSUP_TH_EN773Ar					(ValSft_R16(_rd32(0x30020538))&BitMask_08)
#define LSUP_TH_EN773Aw(val)			_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define CES_ON_EN773Ar					(ValSft_R15(_rd32(0x30020538))&BitMask_01)
#define CES_ON_EN773Aw(val)				_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define CES_GAIN_EN773Ar				(ValSft_R08(_rd32(0x30020538))&BitMask_06)
#define CES_GAIN_EN773Aw(val)			_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define CES_LCLIP_EN773Ar				(ValSft_R00(_rd32(0x30020538))&BitMask_08)
#define CES_LCLIP_EN773Aw(val)			_wr32(0x30020538,(UINT)((_rd32(0x30020538)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define CSUP_ON_EN773Ar					(ValSft_R30(_rd32(0x3002053c))&BitMask_01)
#define CSUP_ON_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CSUP_GA_EN773Ar					(ValSft_R24(_rd32(0x3002053c))&BitMask_06)
#define CSUP_GA_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define CSUP_TH_EN773Ar					(ValSft_R16(_rd32(0x3002053c))&BitMask_08)
#define CSUP_TH_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define CVLPF_ON_EN773Ar				(ValSft_R06(_rd32(0x3002053c))&BitMask_01)
#define CVLPF_ON_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define CHLPF_SEL_EN773Ar				(ValSft_R05(_rd32(0x3002053c))&BitMask_01)
#define CHLPF_SEL_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define CHLPF_ON_EN773Ar				(ValSft_R04(_rd32(0x3002053c))&BitMask_01)
#define CHLPF_ON_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define HSUP_GA_EN773Ar					(ValSft_R01(_rd32(0x3002053c))&BitMask_02)
#define HSUP_GA_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L01(BitMask_02)))|ValSft_L01((val)&BitMask_02)))

#define HSUP_ON_EN773Ar					(ValSft_R00(_rd32(0x3002053c))&BitMask_01)
#define HSUP_ON_EN773Aw(val)			_wr32(0x3002053c,(UINT)((_rd32(0x3002053c)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define ACE_BP_EN773Ar					(ValSft_R31(_rd32(0x30020540))&BitMask_01)
#define ACE_BP_EN773Aw(val)				_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ACE_ON_EN773Ar					(ValSft_R30(_rd32(0x30020540))&BitMask_01)
#define ACE_ON_EN773Aw(val)				_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define ACE_IIR_EN773Ar					(ValSft_R24(_rd32(0x30020540))&BitMask_06)
#define ACE_IIR_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define ACE_TEST_EN773Ar				(ValSft_R23(_rd32(0x30020540))&BitMask_01)
#define ACE_TEST_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define ACE_LPF_EN773Ar					(ValSft_R22(_rd32(0x30020540))&BitMask_01)
#define ACE_LPF_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define ACE_DTH_EN773Ar					(ValSft_R16(_rd32(0x30020540))&BitMask_04)
#define ACE_DTH_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define ACE_TH2_EN773Ar					(ValSft_R08(_rd32(0x30020540))&BitMask_08)
#define ACE_TH2_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_TH1_EN773Ar					(ValSft_R00(_rd32(0x30020540))&BitMask_08)
#define ACE_TH1_EN773Aw(val)			_wr32(0x30020540,(UINT)((_rd32(0x30020540)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020544))&BitMask_12)
#define ACE_HSP_EN773Aw(val)			_wr32(0x30020544,(UINT)((_rd32(0x30020544)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACE_VSP_EN773Ar					(ValSft_R00(_rd32(0x30020544))&BitMask_11)
#define ACE_VSP_EN773Aw(val)			_wr32(0x30020544,(UINT)((_rd32(0x30020544)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define ACE_HBK_EN773Ar					(ValSft_R20(_rd32(0x30020548))&BitMask_05)
#define ACE_HBK_EN773Aw(val)			_wr32(0x30020548,(UINT)((_rd32(0x30020548)&(~ValSft_L20(BitMask_05)))|ValSft_L20((val)&BitMask_05)))

#define ACE_VBK_EN773Ar					(ValSft_R16(_rd32(0x30020548))&BitMask_04)
#define ACE_VBK_EN773Aw(val)			_wr32(0x30020548,(UINT)((_rd32(0x30020548)&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define ACE_GMGN_EN773Ar				(ValSft_R00(_rd32(0x30020548))&BitMask_06)
#define ACE_GMGN_EN773Aw(val)			_wr32(0x30020548,(UINT)((_rd32(0x30020548)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define ACE_GM00_EN773Ar				(ValSft_R24(_rd32(0x3002054c))&BitMask_08)
#define ACE_GM00_EN773Aw(val)			_wr32(0x3002054c,(UINT)((_rd32(0x3002054c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM01_EN773Ar				(ValSft_R16(_rd32(0x3002054c))&BitMask_08)
#define ACE_GM01_EN773Aw(val)			_wr32(0x3002054c,(UINT)((_rd32(0x3002054c)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM02_EN773Ar				(ValSft_R08(_rd32(0x3002054c))&BitMask_08)
#define ACE_GM02_EN773Aw(val)			_wr32(0x3002054c,(UINT)((_rd32(0x3002054c)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM03_EN773Ar				(ValSft_R00(_rd32(0x3002054c))&BitMask_08)
#define ACE_GM03_EN773Aw(val)			_wr32(0x3002054c,(UINT)((_rd32(0x3002054c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM04_EN773Ar				(ValSft_R24(_rd32(0x30020550))&BitMask_08)
#define ACE_GM04_EN773Aw(val)			_wr32(0x30020550,(UINT)((_rd32(0x30020550)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM05_EN773Ar				(ValSft_R16(_rd32(0x30020550))&BitMask_08)
#define ACE_GM05_EN773Aw(val)			_wr32(0x30020550,(UINT)((_rd32(0x30020550)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM06_EN773Ar				(ValSft_R08(_rd32(0x30020550))&BitMask_08)
#define ACE_GM06_EN773Aw(val)			_wr32(0x30020550,(UINT)((_rd32(0x30020550)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM07_EN773Ar				(ValSft_R00(_rd32(0x30020550))&BitMask_08)
#define ACE_GM07_EN773Aw(val)			_wr32(0x30020550,(UINT)((_rd32(0x30020550)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM08_EN773Ar				(ValSft_R24(_rd32(0x30020554))&BitMask_08)
#define ACE_GM08_EN773Aw(val)			_wr32(0x30020554,(UINT)((_rd32(0x30020554)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM09_EN773Ar				(ValSft_R16(_rd32(0x30020554))&BitMask_08)
#define ACE_GM09_EN773Aw(val)			_wr32(0x30020554,(UINT)((_rd32(0x30020554)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM10_EN773Ar				(ValSft_R08(_rd32(0x30020554))&BitMask_08)
#define ACE_GM10_EN773Aw(val)			_wr32(0x30020554,(UINT)((_rd32(0x30020554)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM11_EN773Ar				(ValSft_R00(_rd32(0x30020554))&BitMask_08)
#define ACE_GM11_EN773Aw(val)			_wr32(0x30020554,(UINT)((_rd32(0x30020554)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM12_EN773Ar				(ValSft_R24(_rd32(0x30020558))&BitMask_08)
#define ACE_GM12_EN773Aw(val)			_wr32(0x30020558,(UINT)((_rd32(0x30020558)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM13_EN773Ar				(ValSft_R16(_rd32(0x30020558))&BitMask_08)
#define ACE_GM13_EN773Aw(val)			_wr32(0x30020558,(UINT)((_rd32(0x30020558)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM14_EN773Ar				(ValSft_R08(_rd32(0x30020558))&BitMask_08)
#define ACE_GM14_EN773Aw(val)			_wr32(0x30020558,(UINT)((_rd32(0x30020558)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM15_EN773Ar				(ValSft_R00(_rd32(0x30020558))&BitMask_08)
#define ACE_GM15_EN773Aw(val)			_wr32(0x30020558,(UINT)((_rd32(0x30020558)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HEQ_ON_EN773Ar					(ValSft_R31(_rd32(0x3002055c))&BitMask_01)
#define HEQ_ON_EN773Aw(val)				_wr32(0x3002055c,(UINT)((_rd32(0x3002055c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define HEQ_TH_EN773Ar					(ValSft_R16(_rd32(0x3002055c))&BitMask_15)
#define HEQ_TH_EN773Aw(val)				_wr32(0x3002055c,(UINT)((_rd32(0x3002055c)&(~ValSft_L16(BitMask_15)))|ValSft_L16((val)&BitMask_15)))

#define HEQ_OSD_EN773Ar					(ValSft_R15(_rd32(0x3002055c))&BitMask_01)
#define HEQ_OSD_EN773Aw(val)			_wr32(0x3002055c,(UINT)((_rd32(0x3002055c)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define HEQ_WG_EN773Ar					(ValSft_R12(_rd32(0x3002055c))&BitMask_03)
#define HEQ_WG_EN773Aw(val)				_wr32(0x3002055c,(UINT)((_rd32(0x3002055c)&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define HEQ_HSP_EN773Ar					(ValSft_R00(_rd32(0x3002055c))&BitMask_12)
#define HEQ_HSP_EN773Aw(val)			_wr32(0x3002055c,(UINT)((_rd32(0x3002055c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HEQ_HW_EN773Ar					(ValSft_R28(_rd32(0x30020560))&BitMask_04)
#define HEQ_HW_EN773Aw(val)				_wr32(0x30020560,(UINT)((_rd32(0x30020560)&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define HEQ_VW_EN773Ar					(ValSft_R24(_rd32(0x30020560))&BitMask_04)
#define HEQ_VW_EN773Aw(val)				_wr32(0x30020560,(UINT)((_rd32(0x30020560)&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define HEQ_IIRK_EN773Ar				(ValSft_R16(_rd32(0x30020560))&BitMask_08)
#define HEQ_IIRK_EN773Aw(val)			_wr32(0x30020560,(UINT)((_rd32(0x30020560)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define HEQ_VSP_EN773Ar					(ValSft_R00(_rd32(0x30020560))&BitMask_11)
#define HEQ_VSP_EN773Aw(val)			_wr32(0x30020560,(UINT)((_rd32(0x30020560)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define HLMASK_ON_EN773Ar				(ValSft_R31(_rd32(0x30020564))&BitMask_01)
#define HLMASK_ON_EN773Aw(val)			_wr32(0x30020564,(UINT)((_rd32(0x30020564)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define HLMASK_BLV_EN773Ar				(ValSft_R24(_rd32(0x30020568))&BitMask_08)
#define HLMASK_BLV_EN773Aw(val)			_wr32(0x30020568,(UINT)((_rd32(0x30020568)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define HLMASK_RLV_EN773Ar				(ValSft_R16(_rd32(0x30020568))&BitMask_08)
#define HLMASK_RLV_EN773Aw(val)			_wr32(0x30020568,(UINT)((_rd32(0x30020568)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define HLMASK_YLV_EN773Ar				(ValSft_R08(_rd32(0x30020568))&BitMask_08)
#define HLMASK_YLV_EN773Aw(val)			_wr32(0x30020568,(UINT)((_rd32(0x30020568)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define HLMASK_TH_EN773Ar				(ValSft_R00(_rd32(0x30020568))&BitMask_08)
#define HLMASK_TH_EN773Aw(val)			_wr32(0x30020568,(UINT)((_rd32(0x30020568)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define BOX_ON_EN773Ar					(ValSft_R00(_rd32(0x3002057c))&BitMask_32)
#define BOX_ON_EN773Aw(val)				_wr32(0x3002057c,(UINT)((_rd32(0x3002057c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX00_EY_EN773Ar				(ValSft_R16(_rd32(0x30020580))&BitMask_11)
#define BOX00_EY_EN773Aw(val)			_wr32(0x30020580,(UINT)((_rd32(0x30020580)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX00_SY_EN773Ar				(ValSft_R00(_rd32(0x30020580))&BitMask_11)
#define BOX00_SY_EN773Aw(val)			_wr32(0x30020580,(UINT)((_rd32(0x30020580)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX00_EX_EN773Ar				(ValSft_R16(_rd32(0x30020584))&BitMask_12)
#define BOX00_EX_EN773Aw(val)			_wr32(0x30020584,(UINT)((_rd32(0x30020584)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX00_SX_EN773Ar				(ValSft_R00(_rd32(0x30020584))&BitMask_12)
#define BOX00_SX_EN773Aw(val)			_wr32(0x30020584,(UINT)((_rd32(0x30020584)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX01_EY_EN773Ar				(ValSft_R16(_rd32(0x30020588))&BitMask_11)
#define BOX01_EY_EN773Aw(val)			_wr32(0x30020588,(UINT)((_rd32(0x30020588)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX01_SY_EN773Ar				(ValSft_R00(_rd32(0x30020588))&BitMask_11)
#define BOX01_SY_EN773Aw(val)			_wr32(0x30020588,(UINT)((_rd32(0x30020588)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX01_EX_EN773Ar				(ValSft_R16(_rd32(0x3002058c))&BitMask_12)
#define BOX01_EX_EN773Aw(val)			_wr32(0x3002058c,(UINT)((_rd32(0x3002058c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX01_SX_EN773Ar				(ValSft_R00(_rd32(0x3002058c))&BitMask_12)
#define BOX01_SX_EN773Aw(val)			_wr32(0x3002058c,(UINT)((_rd32(0x3002058c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX02_EY_EN773Ar				(ValSft_R16(_rd32(0x30020590))&BitMask_11)
#define BOX02_EY_EN773Aw(val)			_wr32(0x30020590,(UINT)((_rd32(0x30020590)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX02_SY_EN773Ar				(ValSft_R00(_rd32(0x30020590))&BitMask_11)
#define BOX02_SY_EN773Aw(val)			_wr32(0x30020590,(UINT)((_rd32(0x30020590)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX02_EX_EN773Ar				(ValSft_R16(_rd32(0x30020594))&BitMask_12)
#define BOX02_EX_EN773Aw(val)			_wr32(0x30020594,(UINT)((_rd32(0x30020594)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX02_SX_EN773Ar				(ValSft_R00(_rd32(0x30020594))&BitMask_12)
#define BOX02_SX_EN773Aw(val)			_wr32(0x30020594,(UINT)((_rd32(0x30020594)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX03_EY_EN773Ar				(ValSft_R16(_rd32(0x30020598))&BitMask_11)
#define BOX03_EY_EN773Aw(val)			_wr32(0x30020598,(UINT)((_rd32(0x30020598)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX03_SY_EN773Ar				(ValSft_R00(_rd32(0x30020598))&BitMask_11)
#define BOX03_SY_EN773Aw(val)			_wr32(0x30020598,(UINT)((_rd32(0x30020598)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX03_EX_EN773Ar				(ValSft_R16(_rd32(0x3002059c))&BitMask_12)
#define BOX03_EX_EN773Aw(val)			_wr32(0x3002059c,(UINT)((_rd32(0x3002059c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX03_SX_EN773Ar				(ValSft_R00(_rd32(0x3002059c))&BitMask_12)
#define BOX03_SX_EN773Aw(val)			_wr32(0x3002059c,(UINT)((_rd32(0x3002059c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX04_EY_EN773Ar				(ValSft_R16(_rd32(0x300205a0))&BitMask_11)
#define BOX04_EY_EN773Aw(val)			_wr32(0x300205a0,(UINT)((_rd32(0x300205a0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX04_SY_EN773Ar				(ValSft_R00(_rd32(0x300205a0))&BitMask_11)
#define BOX04_SY_EN773Aw(val)			_wr32(0x300205a0,(UINT)((_rd32(0x300205a0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX04_EX_EN773Ar				(ValSft_R16(_rd32(0x300205a4))&BitMask_12)
#define BOX04_EX_EN773Aw(val)			_wr32(0x300205a4,(UINT)((_rd32(0x300205a4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX04_SX_EN773Ar				(ValSft_R00(_rd32(0x300205a4))&BitMask_12)
#define BOX04_SX_EN773Aw(val)			_wr32(0x300205a4,(UINT)((_rd32(0x300205a4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX05_EY_EN773Ar				(ValSft_R16(_rd32(0x300205a8))&BitMask_11)
#define BOX05_EY_EN773Aw(val)			_wr32(0x300205a8,(UINT)((_rd32(0x300205a8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX05_SY_EN773Ar				(ValSft_R00(_rd32(0x300205a8))&BitMask_11)
#define BOX05_SY_EN773Aw(val)			_wr32(0x300205a8,(UINT)((_rd32(0x300205a8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX05_EX_EN773Ar				(ValSft_R16(_rd32(0x300205ac))&BitMask_12)
#define BOX05_EX_EN773Aw(val)			_wr32(0x300205ac,(UINT)((_rd32(0x300205ac)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX05_SX_EN773Ar				(ValSft_R00(_rd32(0x300205ac))&BitMask_12)
#define BOX05_SX_EN773Aw(val)			_wr32(0x300205ac,(UINT)((_rd32(0x300205ac)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX06_EY_EN773Ar				(ValSft_R16(_rd32(0x300205b0))&BitMask_11)
#define BOX06_EY_EN773Aw(val)			_wr32(0x300205b0,(UINT)((_rd32(0x300205b0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX06_SY_EN773Ar				(ValSft_R00(_rd32(0x300205b0))&BitMask_11)
#define BOX06_SY_EN773Aw(val)			_wr32(0x300205b0,(UINT)((_rd32(0x300205b0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX06_EX_EN773Ar				(ValSft_R16(_rd32(0x300205b4))&BitMask_12)
#define BOX06_EX_EN773Aw(val)			_wr32(0x300205b4,(UINT)((_rd32(0x300205b4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX06_SX_EN773Ar				(ValSft_R00(_rd32(0x300205b4))&BitMask_12)
#define BOX06_SX_EN773Aw(val)			_wr32(0x300205b4,(UINT)((_rd32(0x300205b4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX07_EY_EN773Ar				(ValSft_R16(_rd32(0x300205b8))&BitMask_11)
#define BOX07_EY_EN773Aw(val)			_wr32(0x300205b8,(UINT)((_rd32(0x300205b8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX07_SY_EN773Ar				(ValSft_R00(_rd32(0x300205b8))&BitMask_11)
#define BOX07_SY_EN773Aw(val)			_wr32(0x300205b8,(UINT)((_rd32(0x300205b8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX07_EX_EN773Ar				(ValSft_R16(_rd32(0x300205bc))&BitMask_12)
#define BOX07_EX_EN773Aw(val)			_wr32(0x300205bc,(UINT)((_rd32(0x300205bc)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX07_SX_EN773Ar				(ValSft_R00(_rd32(0x300205bc))&BitMask_12)
#define BOX07_SX_EN773Aw(val)			_wr32(0x300205bc,(UINT)((_rd32(0x300205bc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX08_EY_EN773Ar				(ValSft_R16(_rd32(0x300205c0))&BitMask_11)
#define BOX08_EY_EN773Aw(val)			_wr32(0x300205c0,(UINT)((_rd32(0x300205c0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX08_SY_EN773Ar				(ValSft_R00(_rd32(0x300205c0))&BitMask_11)
#define BOX08_SY_EN773Aw(val)			_wr32(0x300205c0,(UINT)((_rd32(0x300205c0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX08_EX_EN773Ar				(ValSft_R16(_rd32(0x300205c4))&BitMask_12)
#define BOX08_EX_EN773Aw(val)			_wr32(0x300205c4,(UINT)((_rd32(0x300205c4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX08_SX_EN773Ar				(ValSft_R00(_rd32(0x300205c4))&BitMask_12)
#define BOX08_SX_EN773Aw(val)			_wr32(0x300205c4,(UINT)((_rd32(0x300205c4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX09_EY_EN773Ar				(ValSft_R16(_rd32(0x300205c8))&BitMask_11)
#define BOX09_EY_EN773Aw(val)			_wr32(0x300205c8,(UINT)((_rd32(0x300205c8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX09_SY_EN773Ar				(ValSft_R00(_rd32(0x300205c8))&BitMask_11)
#define BOX09_SY_EN773Aw(val)			_wr32(0x300205c8,(UINT)((_rd32(0x300205c8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX09_EX_EN773Ar				(ValSft_R16(_rd32(0x300205cc))&BitMask_12)
#define BOX09_EX_EN773Aw(val)			_wr32(0x300205cc,(UINT)((_rd32(0x300205cc)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX09_SX_EN773Ar				(ValSft_R00(_rd32(0x300205cc))&BitMask_12)
#define BOX09_SX_EN773Aw(val)			_wr32(0x300205cc,(UINT)((_rd32(0x300205cc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX10_EY_EN773Ar				(ValSft_R16(_rd32(0x300205d0))&BitMask_11)
#define BOX10_EY_EN773Aw(val)			_wr32(0x300205d0,(UINT)((_rd32(0x300205d0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX10_SY_EN773Ar				(ValSft_R00(_rd32(0x300205d0))&BitMask_11)
#define BOX10_SY_EN773Aw(val)			_wr32(0x300205d0,(UINT)((_rd32(0x300205d0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX10_EX_EN773Ar				(ValSft_R16(_rd32(0x300205d4))&BitMask_12)
#define BOX10_EX_EN773Aw(val)			_wr32(0x300205d4,(UINT)((_rd32(0x300205d4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX10_SX_EN773Ar				(ValSft_R00(_rd32(0x300205d4))&BitMask_12)
#define BOX10_SX_EN773Aw(val)			_wr32(0x300205d4,(UINT)((_rd32(0x300205d4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX11_EY_EN773Ar				(ValSft_R16(_rd32(0x300205d8))&BitMask_11)
#define BOX11_EY_EN773Aw(val)			_wr32(0x300205d8,(UINT)((_rd32(0x300205d8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX11_SY_EN773Ar				(ValSft_R00(_rd32(0x300205d8))&BitMask_11)
#define BOX11_SY_EN773Aw(val)			_wr32(0x300205d8,(UINT)((_rd32(0x300205d8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX11_EX_EN773Ar				(ValSft_R16(_rd32(0x300205dc))&BitMask_12)
#define BOX11_EX_EN773Aw(val)			_wr32(0x300205dc,(UINT)((_rd32(0x300205dc)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX11_SX_EN773Ar				(ValSft_R00(_rd32(0x300205dc))&BitMask_12)
#define BOX11_SX_EN773Aw(val)			_wr32(0x300205dc,(UINT)((_rd32(0x300205dc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX12_EY_EN773Ar				(ValSft_R16(_rd32(0x300205e0))&BitMask_11)
#define BOX12_EY_EN773Aw(val)			_wr32(0x300205e0,(UINT)((_rd32(0x300205e0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX12_SY_EN773Ar				(ValSft_R00(_rd32(0x300205e0))&BitMask_11)
#define BOX12_SY_EN773Aw(val)			_wr32(0x300205e0,(UINT)((_rd32(0x300205e0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX12_EX_EN773Ar				(ValSft_R16(_rd32(0x300205e4))&BitMask_12)
#define BOX12_EX_EN773Aw(val)			_wr32(0x300205e4,(UINT)((_rd32(0x300205e4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX12_SX_EN773Ar				(ValSft_R00(_rd32(0x300205e4))&BitMask_12)
#define BOX12_SX_EN773Aw(val)			_wr32(0x300205e4,(UINT)((_rd32(0x300205e4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX13_EY_EN773Ar				(ValSft_R16(_rd32(0x300205e8))&BitMask_11)
#define BOX13_EY_EN773Aw(val)			_wr32(0x300205e8,(UINT)((_rd32(0x300205e8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX13_SY_EN773Ar				(ValSft_R00(_rd32(0x300205e8))&BitMask_11)
#define BOX13_SY_EN773Aw(val)			_wr32(0x300205e8,(UINT)((_rd32(0x300205e8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX13_EX_EN773Ar				(ValSft_R16(_rd32(0x300205ec))&BitMask_12)
#define BOX13_EX_EN773Aw(val)			_wr32(0x300205ec,(UINT)((_rd32(0x300205ec)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX13_SX_EN773Ar				(ValSft_R00(_rd32(0x300205ec))&BitMask_12)
#define BOX13_SX_EN773Aw(val)			_wr32(0x300205ec,(UINT)((_rd32(0x300205ec)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX14_EY_EN773Ar				(ValSft_R16(_rd32(0x300205f0))&BitMask_11)
#define BOX14_EY_EN773Aw(val)			_wr32(0x300205f0,(UINT)((_rd32(0x300205f0)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX14_SY_EN773Ar				(ValSft_R00(_rd32(0x300205f0))&BitMask_11)
#define BOX14_SY_EN773Aw(val)			_wr32(0x300205f0,(UINT)((_rd32(0x300205f0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX14_EX_EN773Ar				(ValSft_R16(_rd32(0x300205f4))&BitMask_12)
#define BOX14_EX_EN773Aw(val)			_wr32(0x300205f4,(UINT)((_rd32(0x300205f4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX14_SX_EN773Ar				(ValSft_R00(_rd32(0x300205f4))&BitMask_12)
#define BOX14_SX_EN773Aw(val)			_wr32(0x300205f4,(UINT)((_rd32(0x300205f4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX15_EY_EN773Ar				(ValSft_R16(_rd32(0x300205f8))&BitMask_11)
#define BOX15_EY_EN773Aw(val)			_wr32(0x300205f8,(UINT)((_rd32(0x300205f8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX15_SY_EN773Ar				(ValSft_R00(_rd32(0x300205f8))&BitMask_11)
#define BOX15_SY_EN773Aw(val)			_wr32(0x300205f8,(UINT)((_rd32(0x300205f8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX15_EX_EN773Ar				(ValSft_R16(_rd32(0x300205fc))&BitMask_12)
#define BOX15_EX_EN773Aw(val)			_wr32(0x300205fc,(UINT)((_rd32(0x300205fc)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX15_SX_EN773Ar				(ValSft_R00(_rd32(0x300205fc))&BitMask_12)
#define BOX15_SX_EN773Aw(val)			_wr32(0x300205fc,(UINT)((_rd32(0x300205fc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX16_EY_EN773Ar				(ValSft_R16(_rd32(0x30020600))&BitMask_11)
#define BOX16_EY_EN773Aw(val)			_wr32(0x30020600,(UINT)((_rd32(0x30020600)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX16_SY_EN773Ar				(ValSft_R00(_rd32(0x30020600))&BitMask_11)
#define BOX16_SY_EN773Aw(val)			_wr32(0x30020600,(UINT)((_rd32(0x30020600)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX16_EX_EN773Ar				(ValSft_R16(_rd32(0x30020604))&BitMask_12)
#define BOX16_EX_EN773Aw(val)			_wr32(0x30020604,(UINT)((_rd32(0x30020604)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX16_SX_EN773Ar				(ValSft_R00(_rd32(0x30020604))&BitMask_12)
#define BOX16_SX_EN773Aw(val)			_wr32(0x30020604,(UINT)((_rd32(0x30020604)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX17_EY_EN773Ar				(ValSft_R16(_rd32(0x30020608))&BitMask_11)
#define BOX17_EY_EN773Aw(val)			_wr32(0x30020608,(UINT)((_rd32(0x30020608)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX17_SY_EN773Ar				(ValSft_R00(_rd32(0x30020608))&BitMask_11)
#define BOX17_SY_EN773Aw(val)			_wr32(0x30020608,(UINT)((_rd32(0x30020608)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX17_EX_EN773Ar				(ValSft_R16(_rd32(0x3002060c))&BitMask_12)
#define BOX17_EX_EN773Aw(val)			_wr32(0x3002060c,(UINT)((_rd32(0x3002060c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX17_SX_EN773Ar				(ValSft_R00(_rd32(0x3002060c))&BitMask_12)
#define BOX17_SX_EN773Aw(val)			_wr32(0x3002060c,(UINT)((_rd32(0x3002060c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX18_EY_EN773Ar				(ValSft_R16(_rd32(0x30020610))&BitMask_11)
#define BOX18_EY_EN773Aw(val)			_wr32(0x30020610,(UINT)((_rd32(0x30020610)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX18_SY_EN773Ar				(ValSft_R00(_rd32(0x30020610))&BitMask_11)
#define BOX18_SY_EN773Aw(val)			_wr32(0x30020610,(UINT)((_rd32(0x30020610)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX18_EX_EN773Ar				(ValSft_R16(_rd32(0x30020614))&BitMask_12)
#define BOX18_EX_EN773Aw(val)			_wr32(0x30020614,(UINT)((_rd32(0x30020614)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX18_SX_EN773Ar				(ValSft_R00(_rd32(0x30020614))&BitMask_12)
#define BOX18_SX_EN773Aw(val)			_wr32(0x30020614,(UINT)((_rd32(0x30020614)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX19_EY_EN773Ar				(ValSft_R16(_rd32(0x30020618))&BitMask_11)
#define BOX19_EY_EN773Aw(val)			_wr32(0x30020618,(UINT)((_rd32(0x30020618)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX19_SY_EN773Ar				(ValSft_R00(_rd32(0x30020618))&BitMask_11)
#define BOX19_SY_EN773Aw(val)			_wr32(0x30020618,(UINT)((_rd32(0x30020618)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX19_EX_EN773Ar				(ValSft_R16(_rd32(0x3002061c))&BitMask_12)
#define BOX19_EX_EN773Aw(val)			_wr32(0x3002061c,(UINT)((_rd32(0x3002061c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX19_SX_EN773Ar				(ValSft_R00(_rd32(0x3002061c))&BitMask_12)
#define BOX19_SX_EN773Aw(val)			_wr32(0x3002061c,(UINT)((_rd32(0x3002061c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX20_EY_EN773Ar				(ValSft_R16(_rd32(0x30020620))&BitMask_11)
#define BOX20_EY_EN773Aw(val)			_wr32(0x30020620,(UINT)((_rd32(0x30020620)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX20_SY_EN773Ar				(ValSft_R00(_rd32(0x30020620))&BitMask_11)
#define BOX20_SY_EN773Aw(val)			_wr32(0x30020620,(UINT)((_rd32(0x30020620)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX20_EX_EN773Ar				(ValSft_R16(_rd32(0x30020624))&BitMask_12)
#define BOX20_EX_EN773Aw(val)			_wr32(0x30020624,(UINT)((_rd32(0x30020624)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX20_SX_EN773Ar				(ValSft_R00(_rd32(0x30020624))&BitMask_12)
#define BOX20_SX_EN773Aw(val)			_wr32(0x30020624,(UINT)((_rd32(0x30020624)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX21_EY_EN773Ar				(ValSft_R16(_rd32(0x30020628))&BitMask_11)
#define BOX21_EY_EN773Aw(val)			_wr32(0x30020628,(UINT)((_rd32(0x30020628)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX21_SY_EN773Ar				(ValSft_R00(_rd32(0x30020628))&BitMask_11)
#define BOX21_SY_EN773Aw(val)			_wr32(0x30020628,(UINT)((_rd32(0x30020628)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX21_EX_EN773Ar				(ValSft_R16(_rd32(0x3002062c))&BitMask_12)
#define BOX21_EX_EN773Aw(val)			_wr32(0x3002062c,(UINT)((_rd32(0x3002062c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX21_SX_EN773Ar				(ValSft_R00(_rd32(0x3002062c))&BitMask_12)
#define BOX21_SX_EN773Aw(val)			_wr32(0x3002062c,(UINT)((_rd32(0x3002062c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX22_EY_EN773Ar				(ValSft_R16(_rd32(0x30020630))&BitMask_11)
#define BOX22_EY_EN773Aw(val)			_wr32(0x30020630,(UINT)((_rd32(0x30020630)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX22_SY_EN773Ar				(ValSft_R00(_rd32(0x30020630))&BitMask_11)
#define BOX22_SY_EN773Aw(val)			_wr32(0x30020630,(UINT)((_rd32(0x30020630)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX22_EX_EN773Ar				(ValSft_R16(_rd32(0x30020634))&BitMask_12)
#define BOX22_EX_EN773Aw(val)			_wr32(0x30020634,(UINT)((_rd32(0x30020634)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX22_SX_EN773Ar				(ValSft_R00(_rd32(0x30020634))&BitMask_12)
#define BOX22_SX_EN773Aw(val)			_wr32(0x30020634,(UINT)((_rd32(0x30020634)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX23_EY_EN773Ar				(ValSft_R16(_rd32(0x30020638))&BitMask_11)
#define BOX23_EY_EN773Aw(val)			_wr32(0x30020638,(UINT)((_rd32(0x30020638)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX23_SY_EN773Ar				(ValSft_R00(_rd32(0x30020638))&BitMask_11)
#define BOX23_SY_EN773Aw(val)			_wr32(0x30020638,(UINT)((_rd32(0x30020638)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX23_EX_EN773Ar				(ValSft_R16(_rd32(0x3002063c))&BitMask_12)
#define BOX23_EX_EN773Aw(val)			_wr32(0x3002063c,(UINT)((_rd32(0x3002063c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX23_SX_EN773Ar				(ValSft_R00(_rd32(0x3002063c))&BitMask_12)
#define BOX23_SX_EN773Aw(val)			_wr32(0x3002063c,(UINT)((_rd32(0x3002063c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX24_EY_EN773Ar				(ValSft_R16(_rd32(0x30020640))&BitMask_11)
#define BOX24_EY_EN773Aw(val)			_wr32(0x30020640,(UINT)((_rd32(0x30020640)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX24_SY_EN773Ar				(ValSft_R00(_rd32(0x30020640))&BitMask_11)
#define BOX24_SY_EN773Aw(val)			_wr32(0x30020640,(UINT)((_rd32(0x30020640)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX24_EX_EN773Ar				(ValSft_R16(_rd32(0x30020644))&BitMask_12)
#define BOX24_EX_EN773Aw(val)			_wr32(0x30020644,(UINT)((_rd32(0x30020644)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX24_SX_EN773Ar				(ValSft_R00(_rd32(0x30020644))&BitMask_12)
#define BOX24_SX_EN773Aw(val)			_wr32(0x30020644,(UINT)((_rd32(0x30020644)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX25_EY_EN773Ar				(ValSft_R16(_rd32(0x30020648))&BitMask_11)
#define BOX25_EY_EN773Aw(val)			_wr32(0x30020648,(UINT)((_rd32(0x30020648)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX25_SY_EN773Ar				(ValSft_R00(_rd32(0x30020648))&BitMask_11)
#define BOX25_SY_EN773Aw(val)			_wr32(0x30020648,(UINT)((_rd32(0x30020648)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX25_EX_EN773Ar				(ValSft_R16(_rd32(0x3002064c))&BitMask_12)
#define BOX25_EX_EN773Aw(val)			_wr32(0x3002064c,(UINT)((_rd32(0x3002064c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX25_SX_EN773Ar				(ValSft_R00(_rd32(0x3002064c))&BitMask_12)
#define BOX25_SX_EN773Aw(val)			_wr32(0x3002064c,(UINT)((_rd32(0x3002064c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX26_EY_EN773Ar				(ValSft_R16(_rd32(0x30020650))&BitMask_11)
#define BOX26_EY_EN773Aw(val)			_wr32(0x30020650,(UINT)((_rd32(0x30020650)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX26_SY_EN773Ar				(ValSft_R00(_rd32(0x30020650))&BitMask_11)
#define BOX26_SY_EN773Aw(val)			_wr32(0x30020650,(UINT)((_rd32(0x30020650)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX26_EX_EN773Ar				(ValSft_R16(_rd32(0x30020654))&BitMask_12)
#define BOX26_EX_EN773Aw(val)			_wr32(0x30020654,(UINT)((_rd32(0x30020654)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX26_SX_EN773Ar				(ValSft_R00(_rd32(0x30020654))&BitMask_12)
#define BOX26_SX_EN773Aw(val)			_wr32(0x30020654,(UINT)((_rd32(0x30020654)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX27_EY_EN773Ar				(ValSft_R16(_rd32(0x30020658))&BitMask_11)
#define BOX27_EY_EN773Aw(val)			_wr32(0x30020658,(UINT)((_rd32(0x30020658)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX27_SY_EN773Ar				(ValSft_R00(_rd32(0x30020658))&BitMask_11)
#define BOX27_SY_EN773Aw(val)			_wr32(0x30020658,(UINT)((_rd32(0x30020658)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX27_EX_EN773Ar				(ValSft_R16(_rd32(0x3002065c))&BitMask_12)
#define BOX27_EX_EN773Aw(val)			_wr32(0x3002065c,(UINT)((_rd32(0x3002065c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX27_SX_EN773Ar				(ValSft_R00(_rd32(0x3002065c))&BitMask_12)
#define BOX27_SX_EN773Aw(val)			_wr32(0x3002065c,(UINT)((_rd32(0x3002065c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX28_EY_EN773Ar				(ValSft_R16(_rd32(0x30020660))&BitMask_11)
#define BOX28_EY_EN773Aw(val)			_wr32(0x30020660,(UINT)((_rd32(0x30020660)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX28_SY_EN773Ar				(ValSft_R00(_rd32(0x30020660))&BitMask_11)
#define BOX28_SY_EN773Aw(val)			_wr32(0x30020660,(UINT)((_rd32(0x30020660)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX28_EX_EN773Ar				(ValSft_R16(_rd32(0x30020664))&BitMask_12)
#define BOX28_EX_EN773Aw(val)			_wr32(0x30020664,(UINT)((_rd32(0x30020664)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX28_SX_EN773Ar				(ValSft_R00(_rd32(0x30020664))&BitMask_12)
#define BOX28_SX_EN773Aw(val)			_wr32(0x30020664,(UINT)((_rd32(0x30020664)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX29_EY_EN773Ar				(ValSft_R16(_rd32(0x30020668))&BitMask_11)
#define BOX29_EY_EN773Aw(val)			_wr32(0x30020668,(UINT)((_rd32(0x30020668)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX29_SY_EN773Ar				(ValSft_R00(_rd32(0x30020668))&BitMask_11)
#define BOX29_SY_EN773Aw(val)			_wr32(0x30020668,(UINT)((_rd32(0x30020668)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX29_EX_EN773Ar				(ValSft_R16(_rd32(0x3002066c))&BitMask_12)
#define BOX29_EX_EN773Aw(val)			_wr32(0x3002066c,(UINT)((_rd32(0x3002066c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX29_SX_EN773Ar				(ValSft_R00(_rd32(0x3002066c))&BitMask_12)
#define BOX29_SX_EN773Aw(val)			_wr32(0x3002066c,(UINT)((_rd32(0x3002066c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX30_EY_EN773Ar				(ValSft_R16(_rd32(0x30020670))&BitMask_11)
#define BOX30_EY_EN773Aw(val)			_wr32(0x30020670,(UINT)((_rd32(0x30020670)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX30_SY_EN773Ar				(ValSft_R00(_rd32(0x30020670))&BitMask_11)
#define BOX30_SY_EN773Aw(val)			_wr32(0x30020670,(UINT)((_rd32(0x30020670)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX30_EX_EN773Ar				(ValSft_R16(_rd32(0x30020674))&BitMask_12)
#define BOX30_EX_EN773Aw(val)			_wr32(0x30020674,(UINT)((_rd32(0x30020674)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX30_SX_EN773Ar				(ValSft_R00(_rd32(0x30020674))&BitMask_12)
#define BOX30_SX_EN773Aw(val)			_wr32(0x30020674,(UINT)((_rd32(0x30020674)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX31_EY_EN773Ar				(ValSft_R16(_rd32(0x30020678))&BitMask_11)
#define BOX31_EY_EN773Aw(val)			_wr32(0x30020678,(UINT)((_rd32(0x30020678)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define BOX31_SY_EN773Ar				(ValSft_R00(_rd32(0x30020678))&BitMask_11)
#define BOX31_SY_EN773Aw(val)			_wr32(0x30020678,(UINT)((_rd32(0x30020678)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BOX31_EX_EN773Ar				(ValSft_R16(_rd32(0x3002067c))&BitMask_12)
#define BOX31_EX_EN773Aw(val)			_wr32(0x3002067c,(UINT)((_rd32(0x3002067c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX31_SX_EN773Ar				(ValSft_R00(_rd32(0x3002067c))&BitMask_12)
#define BOX31_SX_EN773Aw(val)			_wr32(0x3002067c,(UINT)((_rd32(0x3002067c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX00_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020680))&BitMask_32)
#define BOX00_LATT_EN773Aw(val)			_wr32(0x30020680,(UINT)((_rd32(0x30020680)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX01_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020684))&BitMask_32)
#define BOX01_LATT_EN773Aw(val)			_wr32(0x30020684,(UINT)((_rd32(0x30020684)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX02_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020688))&BitMask_32)
#define BOX02_LATT_EN773Aw(val)			_wr32(0x30020688,(UINT)((_rd32(0x30020688)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX03_LATT_EN773Ar				(ValSft_R00(_rd32(0x3002068c))&BitMask_32)
#define BOX03_LATT_EN773Aw(val)			_wr32(0x3002068c,(UINT)((_rd32(0x3002068c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX04_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020690))&BitMask_32)
#define BOX04_LATT_EN773Aw(val)			_wr32(0x30020690,(UINT)((_rd32(0x30020690)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX05_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020694))&BitMask_32)
#define BOX05_LATT_EN773Aw(val)			_wr32(0x30020694,(UINT)((_rd32(0x30020694)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX06_LATT_EN773Ar				(ValSft_R00(_rd32(0x30020698))&BitMask_32)
#define BOX06_LATT_EN773Aw(val)			_wr32(0x30020698,(UINT)((_rd32(0x30020698)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX07_LATT_EN773Ar				(ValSft_R00(_rd32(0x3002069c))&BitMask_32)
#define BOX07_LATT_EN773Aw(val)			_wr32(0x3002069c,(UINT)((_rd32(0x3002069c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX08_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206a0))&BitMask_32)
#define BOX08_LATT_EN773Aw(val)			_wr32(0x300206a0,(UINT)((_rd32(0x300206a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX09_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206a4))&BitMask_32)
#define BOX09_LATT_EN773Aw(val)			_wr32(0x300206a4,(UINT)((_rd32(0x300206a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX10_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206a8))&BitMask_32)
#define BOX10_LATT_EN773Aw(val)			_wr32(0x300206a8,(UINT)((_rd32(0x300206a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX11_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206ac))&BitMask_32)
#define BOX11_LATT_EN773Aw(val)			_wr32(0x300206ac,(UINT)((_rd32(0x300206ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX12_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206b0))&BitMask_32)
#define BOX12_LATT_EN773Aw(val)			_wr32(0x300206b0,(UINT)((_rd32(0x300206b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX13_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206b4))&BitMask_32)
#define BOX13_LATT_EN773Aw(val)			_wr32(0x300206b4,(UINT)((_rd32(0x300206b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX14_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206b8))&BitMask_32)
#define BOX14_LATT_EN773Aw(val)			_wr32(0x300206b8,(UINT)((_rd32(0x300206b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX15_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206bc))&BitMask_32)
#define BOX15_LATT_EN773Aw(val)			_wr32(0x300206bc,(UINT)((_rd32(0x300206bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX16_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206c0))&BitMask_32)
#define BOX16_LATT_EN773Aw(val)			_wr32(0x300206c0,(UINT)((_rd32(0x300206c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX17_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206c4))&BitMask_32)
#define BOX17_LATT_EN773Aw(val)			_wr32(0x300206c4,(UINT)((_rd32(0x300206c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX18_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206c8))&BitMask_32)
#define BOX18_LATT_EN773Aw(val)			_wr32(0x300206c8,(UINT)((_rd32(0x300206c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX19_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206cc))&BitMask_32)
#define BOX19_LATT_EN773Aw(val)			_wr32(0x300206cc,(UINT)((_rd32(0x300206cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX20_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206d0))&BitMask_32)
#define BOX20_LATT_EN773Aw(val)			_wr32(0x300206d0,(UINT)((_rd32(0x300206d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX21_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206d4))&BitMask_32)
#define BOX21_LATT_EN773Aw(val)			_wr32(0x300206d4,(UINT)((_rd32(0x300206d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX22_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206d8))&BitMask_32)
#define BOX22_LATT_EN773Aw(val)			_wr32(0x300206d8,(UINT)((_rd32(0x300206d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX23_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206dc))&BitMask_32)
#define BOX23_LATT_EN773Aw(val)			_wr32(0x300206dc,(UINT)((_rd32(0x300206dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX24_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206e0))&BitMask_32)
#define BOX24_LATT_EN773Aw(val)			_wr32(0x300206e0,(UINT)((_rd32(0x300206e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX25_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206e4))&BitMask_32)
#define BOX25_LATT_EN773Aw(val)			_wr32(0x300206e4,(UINT)((_rd32(0x300206e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX26_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206e8))&BitMask_32)
#define BOX26_LATT_EN773Aw(val)			_wr32(0x300206e8,(UINT)((_rd32(0x300206e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX27_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206ec))&BitMask_32)
#define BOX27_LATT_EN773Aw(val)			_wr32(0x300206ec,(UINT)((_rd32(0x300206ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX28_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206f0))&BitMask_32)
#define BOX28_LATT_EN773Aw(val)			_wr32(0x300206f0,(UINT)((_rd32(0x300206f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX29_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206f4))&BitMask_32)
#define BOX29_LATT_EN773Aw(val)			_wr32(0x300206f4,(UINT)((_rd32(0x300206f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX30_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206f8))&BitMask_32)
#define BOX30_LATT_EN773Aw(val)			_wr32(0x300206f8,(UINT)((_rd32(0x300206f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX31_LATT_EN773Ar				(ValSft_R00(_rd32(0x300206fc))&BitMask_32)
#define BOX31_LATT_EN773Aw(val)			_wr32(0x300206fc,(UINT)((_rd32(0x300206fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX00_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020700))&BitMask_27)
#define BOX00_AATT_EN773Aw(val)			_wr32(0x30020700,(UINT)((_rd32(0x30020700)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX01_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020704))&BitMask_27)
#define BOX01_AATT_EN773Aw(val)			_wr32(0x30020704,(UINT)((_rd32(0x30020704)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX02_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020708))&BitMask_27)
#define BOX02_AATT_EN773Aw(val)			_wr32(0x30020708,(UINT)((_rd32(0x30020708)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX03_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002070c))&BitMask_27)
#define BOX03_AATT_EN773Aw(val)			_wr32(0x3002070c,(UINT)((_rd32(0x3002070c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX04_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020710))&BitMask_27)
#define BOX04_AATT_EN773Aw(val)			_wr32(0x30020710,(UINT)((_rd32(0x30020710)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX05_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020714))&BitMask_27)
#define BOX05_AATT_EN773Aw(val)			_wr32(0x30020714,(UINT)((_rd32(0x30020714)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX06_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020718))&BitMask_27)
#define BOX06_AATT_EN773Aw(val)			_wr32(0x30020718,(UINT)((_rd32(0x30020718)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX07_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002071c))&BitMask_27)
#define BOX07_AATT_EN773Aw(val)			_wr32(0x3002071c,(UINT)((_rd32(0x3002071c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX08_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020720))&BitMask_27)
#define BOX08_AATT_EN773Aw(val)			_wr32(0x30020720,(UINT)((_rd32(0x30020720)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX09_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020724))&BitMask_27)
#define BOX09_AATT_EN773Aw(val)			_wr32(0x30020724,(UINT)((_rd32(0x30020724)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX10_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020728))&BitMask_27)
#define BOX10_AATT_EN773Aw(val)			_wr32(0x30020728,(UINT)((_rd32(0x30020728)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX11_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002072c))&BitMask_27)
#define BOX11_AATT_EN773Aw(val)			_wr32(0x3002072c,(UINT)((_rd32(0x3002072c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX12_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020730))&BitMask_27)
#define BOX12_AATT_EN773Aw(val)			_wr32(0x30020730,(UINT)((_rd32(0x30020730)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX13_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020734))&BitMask_27)
#define BOX13_AATT_EN773Aw(val)			_wr32(0x30020734,(UINT)((_rd32(0x30020734)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX14_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020738))&BitMask_27)
#define BOX14_AATT_EN773Aw(val)			_wr32(0x30020738,(UINT)((_rd32(0x30020738)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX15_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002073c))&BitMask_27)
#define BOX15_AATT_EN773Aw(val)			_wr32(0x3002073c,(UINT)((_rd32(0x3002073c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX16_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020740))&BitMask_27)
#define BOX16_AATT_EN773Aw(val)			_wr32(0x30020740,(UINT)((_rd32(0x30020740)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX17_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020744))&BitMask_27)
#define BOX17_AATT_EN773Aw(val)			_wr32(0x30020744,(UINT)((_rd32(0x30020744)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX18_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020748))&BitMask_27)
#define BOX18_AATT_EN773Aw(val)			_wr32(0x30020748,(UINT)((_rd32(0x30020748)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX19_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002074c))&BitMask_27)
#define BOX19_AATT_EN773Aw(val)			_wr32(0x3002074c,(UINT)((_rd32(0x3002074c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX20_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020750))&BitMask_27)
#define BOX20_AATT_EN773Aw(val)			_wr32(0x30020750,(UINT)((_rd32(0x30020750)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX21_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020754))&BitMask_27)
#define BOX21_AATT_EN773Aw(val)			_wr32(0x30020754,(UINT)((_rd32(0x30020754)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX22_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020758))&BitMask_27)
#define BOX22_AATT_EN773Aw(val)			_wr32(0x30020758,(UINT)((_rd32(0x30020758)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX23_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002075c))&BitMask_27)
#define BOX23_AATT_EN773Aw(val)			_wr32(0x3002075c,(UINT)((_rd32(0x3002075c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX24_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020760))&BitMask_27)
#define BOX24_AATT_EN773Aw(val)			_wr32(0x30020760,(UINT)((_rd32(0x30020760)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX25_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020764))&BitMask_27)
#define BOX25_AATT_EN773Aw(val)			_wr32(0x30020764,(UINT)((_rd32(0x30020764)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX26_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020768))&BitMask_27)
#define BOX26_AATT_EN773Aw(val)			_wr32(0x30020768,(UINT)((_rd32(0x30020768)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX27_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002076c))&BitMask_27)
#define BOX27_AATT_EN773Aw(val)			_wr32(0x3002076c,(UINT)((_rd32(0x3002076c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX28_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020770))&BitMask_27)
#define BOX28_AATT_EN773Aw(val)			_wr32(0x30020770,(UINT)((_rd32(0x30020770)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX29_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020774))&BitMask_27)
#define BOX29_AATT_EN773Aw(val)			_wr32(0x30020774,(UINT)((_rd32(0x30020774)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX30_AATT_EN773Ar				(ValSft_R00(_rd32(0x30020778))&BitMask_27)
#define BOX30_AATT_EN773Aw(val)			_wr32(0x30020778,(UINT)((_rd32(0x30020778)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define BOX31_AATT_EN773Ar				(ValSft_R00(_rd32(0x3002077c))&BitMask_27)
#define BOX31_AATT_EN773Aw(val)			_wr32(0x3002077c,(UINT)((_rd32(0x3002077c)&(~ValSft_L00(BitMask_27)))|ValSft_L00((val)&BitMask_27)))

#define FONT_ON_EN773Ar					(ValSft_R31(_rd32(0x30020780))&BitMask_01)
#define FONT_ON_EN773Aw(val)			_wr32(0x30020780,(UINT)((_rd32(0x30020780)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define BOAD_ON_EN773Ar					(ValSft_R30(_rd32(0x30020780))&BitMask_01)
#define BOAD_ON_EN773Aw(val)			_wr32(0x30020780,(UINT)((_rd32(0x30020780)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define BOAD_MODE_EN773Ar				(ValSft_R29(_rd32(0x30020780))&BitMask_01)
#define BOAD_MODE_EN773Aw(val)			_wr32(0x30020780,(UINT)((_rd32(0x30020780)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define FONT_OFY_EN773Ar				(ValSft_R16(_rd32(0x30020780))&BitMask_11)
#define FONT_OFY_EN773Aw(val)			_wr32(0x30020780,(UINT)((_rd32(0x30020780)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define FONT_OFX_EN773Ar				(ValSft_R00(_rd32(0x30020780))&BitMask_12)
#define FONT_OFX_EN773Aw(val)			_wr32(0x30020780,(UINT)((_rd32(0x30020780)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define FONT_LV0_EN773Ar				(ValSft_R00(_rd32(0x30020784))&BitMask_24)
#define FONT_LV0_EN773Aw(val)			_wr32(0x30020784,(UINT)((_rd32(0x30020784)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV1_EN773Ar				(ValSft_R00(_rd32(0x30020788))&BitMask_24)
#define FONT_LV1_EN773Aw(val)			_wr32(0x30020788,(UINT)((_rd32(0x30020788)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV2_EN773Ar				(ValSft_R00(_rd32(0x3002078c))&BitMask_24)
#define FONT_LV2_EN773Aw(val)			_wr32(0x3002078c,(UINT)((_rd32(0x3002078c)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV3_EN773Ar				(ValSft_R00(_rd32(0x30020790))&BitMask_24)
#define FONT_LV3_EN773Aw(val)			_wr32(0x30020790,(UINT)((_rd32(0x30020790)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOAD_LV0_EN773Ar				(ValSft_R00(_rd32(0x30020794))&BitMask_24)
#define BOAD_LV0_EN773Aw(val)			_wr32(0x30020794,(UINT)((_rd32(0x30020794)&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_VBLK_EN773Ar				(ValSft_R16(_rd32(0x30020798))&BitMask_08)
#define FONT_VBLK_EN773Aw(val)			_wr32(0x30020798,(UINT)((_rd32(0x30020798)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define FONT_HBLK_EN773Ar				(ValSft_R08(_rd32(0x30020798))&BitMask_08)
#define FONT_HBLK_EN773Aw(val)			_wr32(0x30020798,(UINT)((_rd32(0x30020798)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define FONT_VSIZ_EN773Ar				(ValSft_R04(_rd32(0x30020798))&BitMask_04)
#define FONT_VSIZ_EN773Aw(val)			_wr32(0x30020798,(UINT)((_rd32(0x30020798)&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define FONT_HSIZ_EN773Ar				(ValSft_R00(_rd32(0x30020798))&BitMask_04)
#define FONT_HSIZ_EN773Aw(val)			_wr32(0x30020798,(UINT)((_rd32(0x30020798)&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define MASK_CHAD_EN773Ar				(ValSft_R16(_rd32(0x3002079c))&BitMask_09)
#define MASK_CHAD_EN773Aw(val)			_wr32(0x3002079c,(UINT)((_rd32(0x3002079c)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define HALF_CHAD_EN773Ar				(ValSft_R00(_rd32(0x3002079c))&BitMask_09)
#define HALF_CHAD_EN773Aw(val)			_wr32(0x3002079c,(UINT)((_rd32(0x3002079c)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define LAST_YCLIP_EN773Ar				(ValSft_R24(_rd32(0x300207a0))&BitMask_08)
#define LAST_YCLIP_EN773Aw(val)			_wr32(0x300207a0,(UINT)((_rd32(0x300207a0)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define LAST_YOFFS_EN773Ar				(ValSft_R16(_rd32(0x300207a0))&BitMask_08)
#define LAST_YOFFS_EN773Aw(val)			_wr32(0x300207a0,(UINT)((_rd32(0x300207a0)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define LAST_CGAIN_EN773Ar				(ValSft_R08(_rd32(0x300207a0))&BitMask_08)
#define LAST_CGAIN_EN773Aw(val)			_wr32(0x300207a0,(UINT)((_rd32(0x300207a0)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define LAST_YGAIN_EN773Ar				(ValSft_R00(_rd32(0x300207a0))&BitMask_08)
#define LAST_YGAIN_EN773Aw(val)			_wr32(0x300207a0,(UINT)((_rd32(0x300207a0)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define LAST_CCLIP_EN773Ar				(ValSft_R08(_rd32(0x300207a4))&BitMask_08)
#define LAST_CCLIP_EN773Aw(val)			_wr32(0x300207a4,(UINT)((_rd32(0x300207a4)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define LAST_YSLIC_EN773Ar				(ValSft_R00(_rd32(0x300207a4))&BitMask_08)
#define LAST_YSLIC_EN773Aw(val)			_wr32(0x300207a4,(UINT)((_rd32(0x300207a4)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DS_ON_EN773Ar					(ValSft_R31(_rd32(0x300207a8))&BitMask_01)
#define DS_ON_EN773Aw(val)				_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DS_VLPF_EN773Ar					(ValSft_R26(_rd32(0x300207a8))&BitMask_02)
#define DS_VLPF_EN773Aw(val)			_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define DS_HLPF_EN773Ar					(ValSft_R24(_rd32(0x300207a8))&BitMask_02)
#define DS_HLPF_EN773Aw(val)			_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define DKY_ST_EN773Ar					(ValSft_R16(_rd32(0x300207a8))&BitMask_06)
#define DKY_ST_EN773Aw(val)				_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define DKY_EN773Ar						(ValSft_R08(_rd32(0x300207a8))&BitMask_08)
#define DKY_EN773Aw(val)				_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DKX_EN773Ar						(ValSft_R00(_rd32(0x300207a8))&BitMask_08)
#define DKX_EN773Aw(val)				_wr32(0x300207a8,(UINT)((_rd32(0x300207a8)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DS_APTON_EN773Ar				(ValSft_R31(_rd32(0x300207ac))&BitMask_01)
#define DS_APTON_EN773Aw(val)			_wr32(0x300207ac,(UINT)((_rd32(0x300207ac)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DS_APTGA_EN773Ar				(ValSft_R16(_rd32(0x300207ac))&BitMask_08)
#define DS_APTGA_EN773Aw(val)			_wr32(0x300207ac,(UINT)((_rd32(0x300207ac)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DS_APTSL_EN773Ar				(ValSft_R08(_rd32(0x300207ac))&BitMask_08)
#define DS_APTSL_EN773Aw(val)			_wr32(0x300207ac,(UINT)((_rd32(0x300207ac)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DS_APTCL_EN773Ar				(ValSft_R00(_rd32(0x300207ac))&BitMask_08)
#define DS_APTCL_EN773Aw(val)			_wr32(0x300207ac,(UINT)((_rd32(0x300207ac)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DS_HW_EN773Ar					(ValSft_R16(_rd32(0x300207b0))&BitMask_12)
#define DS_HW_EN773Aw(val)				_wr32(0x300207b0,(UINT)((_rd32(0x300207b0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DS_VW_EN773Ar					(ValSft_R00(_rd32(0x300207b0))&BitMask_11)
#define DS_VW_EN773Aw(val)				_wr32(0x300207b0,(UINT)((_rd32(0x300207b0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define BNC_IRQ_ON_EN773Ar				(ValSft_R16(_rd32(0x300207b4))&BitMask_01)
#define BNC_IRQ_ON_EN773Aw(val)			_wr32(0x300207b4,(UINT)((_rd32(0x300207b4)&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define CXIN_FILD_EN773Ar				(ValSft_R00(_rd32(0x300207b4))&BitMask_16)
#define CXIN_FILD_EN773Aw(val)			_wr32(0x300207b4,(UINT)((_rd32(0x300207b4)&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IHDVD_GEN_EN773Ar				(ValSft_R31(_rd32(0x300207b8))&BitMask_01)
#define IHDVD_GEN_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define BURST_FREE_EN773Ar				(ValSft_R30(_rd32(0x300207b8))&BitMask_01)
#define BURST_FREE_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define EFLD_INV_EN773Ar				(ValSft_R29(_rd32(0x300207b8))&BitMask_01)
#define EFLD_INV_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define NTSC_EN773Ar					(ValSft_R28(_rd32(0x300207b8))&BitMask_01)
#define NTSC_EN773Aw(val)				_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define ESYNC_POL_EN773Ar				(ValSft_R27(_rd32(0x300207b8))&BitMask_01)
#define ESYNC_POL_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define ENC_CBR_INV_R_EN773Ar			(ValSft_R26(_rd32(0x300207b8))&BitMask_01)
#define ENC_CBR_INV_R_EN773Aw(val)		_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define ENC_TIMG_ON_EN773Ar				(ValSft_R25(_rd32(0x300207b8))&BitMask_01)
#define ENC_TIMG_ON_EN773Aw(val)		_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define ENC_TIMG_SEL_EN773Ar			(ValSft_R23(_rd32(0x300207b8))&BitMask_02)
#define ENC_TIMG_SEL_EN773Aw(val)		_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L23(BitMask_02)))|ValSft_L23((val)&BitMask_02)))

#define Y_DLY_ADJ_EN773Ar				(ValSft_R05(_rd32(0x300207b8))&BitMask_04)
#define Y_DLY_ADJ_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L05(BitMask_04)))|ValSft_L05((val)&BitMask_04)))

#define SIG_SEL_EN773Ar					(ValSft_R00(_rd32(0x300207b8))&BitMask_05)
#define SIG_SEL_EN773Aw(val)			_wr32(0x300207b8,(UINT)((_rd32(0x300207b8)&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))

#define ICNT_CLIP_EN773Ar				(ValSft_R16(_rd32(0x300207bc))&BitMask_12)
#define ICNT_CLIP_EN773Aw(val)			_wr32(0x300207bc,(UINT)((_rd32(0x300207bc)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define HLOCK_CAT_EN773Ar				(ValSft_R00(_rd32(0x300207bc))&BitMask_12)
#define HLOCK_CAT_EN773Aw(val)			_wr32(0x300207bc,(UINT)((_rd32(0x300207bc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define VLOCK_CAT_EV_EN773Ar			(ValSft_R16(_rd32(0x300207c0))&BitMask_10)
#define VLOCK_CAT_EV_EN773Aw(val)		_wr32(0x300207c0,(UINT)((_rd32(0x300207c0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define VLOCK_CAT_OD_EN773Ar			(ValSft_R00(_rd32(0x300207c0))&BitMask_10)
#define VLOCK_CAT_OD_EN773Aw(val)		_wr32(0x300207c0,(UINT)((_rd32(0x300207c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SERR_VSP_EV_EN773Ar				(ValSft_R16(_rd32(0x300207c4))&BitMask_10)
#define SERR_VSP_EV_EN773Aw(val)		_wr32(0x300207c4,(UINT)((_rd32(0x300207c4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define SERR_VEP_EV_EN773Ar				(ValSft_R00(_rd32(0x300207c4))&BitMask_10)
#define SERR_VEP_EV_EN773Aw(val)		_wr32(0x300207c4,(UINT)((_rd32(0x300207c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BLANK_VEP_EV_EN773Ar			(ValSft_R16(_rd32(0x300207c8))&BitMask_10)
#define BLANK_VEP_EV_EN773Aw(val)		_wr32(0x300207c8,(UINT)((_rd32(0x300207c8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BURST_VSP_EV_EN773Ar			(ValSft_R00(_rd32(0x300207c8))&BitMask_10)
#define BURST_VSP_EV_EN773Aw(val)		_wr32(0x300207c8,(UINT)((_rd32(0x300207c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ACT_VSP_EV_EN773Ar				(ValSft_R16(_rd32(0x300207cc))&BitMask_10)
#define ACT_VSP_EV_EN773Aw(val)			_wr32(0x300207cc,(UINT)((_rd32(0x300207cc)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ACT_VEP_EV_EN773Ar				(ValSft_R00(_rd32(0x300207cc))&BitMask_10)
#define ACT_VEP_EV_EN773Aw(val)			_wr32(0x300207cc,(UINT)((_rd32(0x300207cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BURST_VEP_EV_EN773Ar			(ValSft_R16(_rd32(0x300207d0))&BitMask_10)
#define BURST_VEP_EV_EN773Aw(val)		_wr32(0x300207d0,(UINT)((_rd32(0x300207d0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BLANK_VSP_EV_EN773Ar			(ValSft_R00(_rd32(0x300207d0))&BitMask_10)
#define BLANK_VSP_EV_EN773Aw(val)		_wr32(0x300207d0,(UINT)((_rd32(0x300207d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SERR_VSP_OD_EN773Ar				(ValSft_R16(_rd32(0x300207d4))&BitMask_10)
#define SERR_VSP_OD_EN773Aw(val)		_wr32(0x300207d4,(UINT)((_rd32(0x300207d4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define SERR_VEP_OD_EN773Ar				(ValSft_R00(_rd32(0x300207d4))&BitMask_10)
#define SERR_VEP_OD_EN773Aw(val)		_wr32(0x300207d4,(UINT)((_rd32(0x300207d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BLANK_VEP_OD_EN773Ar			(ValSft_R16(_rd32(0x300207d8))&BitMask_10)
#define BLANK_VEP_OD_EN773Aw(val)		_wr32(0x300207d8,(UINT)((_rd32(0x300207d8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BURST_VSP_OD_EN773Ar			(ValSft_R00(_rd32(0x300207d8))&BitMask_10)
#define BURST_VSP_OD_EN773Aw(val)		_wr32(0x300207d8,(UINT)((_rd32(0x300207d8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ACT_VSP_OD_EN773Ar				(ValSft_R16(_rd32(0x300207dc))&BitMask_10)
#define ACT_VSP_OD_EN773Aw(val)			_wr32(0x300207dc,(UINT)((_rd32(0x300207dc)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ACT_VEP_OD_EN773Ar				(ValSft_R00(_rd32(0x300207dc))&BitMask_10)
#define ACT_VEP_OD_EN773Aw(val)			_wr32(0x300207dc,(UINT)((_rd32(0x300207dc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BURST_VEP_OD_EN773Ar			(ValSft_R16(_rd32(0x300207e0))&BitMask_10)
#define BURST_VEP_OD_EN773Aw(val)		_wr32(0x300207e0,(UINT)((_rd32(0x300207e0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BLANK_VSP_OD_EN773Ar			(ValSft_R00(_rd32(0x300207e0))&BitMask_10)
#define BLANK_VSP_OD_EN773Aw(val)		_wr32(0x300207e0,(UINT)((_rd32(0x300207e0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ACT_BLANK_HW_EN773Ar			(ValSft_R16(_rd32(0x300207e4))&BitMask_12)
#define ACT_BLANK_HW_EN773Aw(val)		_wr32(0x300207e4,(UINT)((_rd32(0x300207e4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACT_BLANK_HSP_EN773Ar			(ValSft_R00(_rd32(0x300207e4))&BitMask_12)
#define ACT_BLANK_HSP_EN773Aw(val)		_wr32(0x300207e4,(UINT)((_rd32(0x300207e4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define SERR_SYNC_HW_EN773Ar			(ValSft_R16(_rd32(0x300207e8))&BitMask_11)
#define SERR_SYNC_HW_EN773Aw(val)		_wr32(0x300207e8,(UINT)((_rd32(0x300207e8)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define SERR_SYNC_HSP_EN773Ar			(ValSft_R00(_rd32(0x300207e8))&BitMask_11)
#define SERR_SYNC_HSP_EN773Aw(val)		_wr32(0x300207e8,(UINT)((_rd32(0x300207e8)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define EQUAL_SYNC_HW_EN773Ar			(ValSft_R16(_rd32(0x300207ec))&BitMask_11)
#define EQUAL_SYNC_HW_EN773Aw(val)		_wr32(0x300207ec,(UINT)((_rd32(0x300207ec)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define EQUAL_SYNC_HSP_EN773Ar			(ValSft_R00(_rd32(0x300207ec))&BitMask_11)
#define EQUAL_SYNC_HSP_EN773Aw(val)		_wr32(0x300207ec,(UINT)((_rd32(0x300207ec)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define ACT_SYNC_HW_EN773Ar				(ValSft_R16(_rd32(0x300207f0))&BitMask_12)
#define ACT_SYNC_HW_EN773Aw(val)		_wr32(0x300207f0,(UINT)((_rd32(0x300207f0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACT_SYNC_HSP_EN773Ar			(ValSft_R00(_rd32(0x300207f0))&BitMask_12)
#define ACT_SYNC_HSP_EN773Aw(val)		_wr32(0x300207f0,(UINT)((_rd32(0x300207f0)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ACT_BURST_HW_EN773Ar			(ValSft_R16(_rd32(0x300207f4))&BitMask_12)
#define ACT_BURST_HW_EN773Aw(val)		_wr32(0x300207f4,(UINT)((_rd32(0x300207f4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACT_BURST_HSP_EN773Ar			(ValSft_R00(_rd32(0x300207f4))&BitMask_12)
#define ACT_BURST_HSP_EN773Aw(val)		_wr32(0x300207f4,(UINT)((_rd32(0x300207f4)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ACT_ACT_HW_EN773Ar				(ValSft_R16(_rd32(0x300207f8))&BitMask_12)
#define ACT_ACT_HW_EN773Aw(val)			_wr32(0x300207f8,(UINT)((_rd32(0x300207f8)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACT_ACT_HSP_EN773Ar				(ValSft_R00(_rd32(0x300207f8))&BitMask_12)
#define ACT_ACT_HSP_EN773Aw(val)		_wr32(0x300207f8,(UINT)((_rd32(0x300207f8)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CBAR_ON_EN773Ar					(ValSft_R31(_rd32(0x300207fc))&BitMask_01)
#define CBAR_ON_EN773Aw(val)			_wr32(0x300207fc,(UINT)((_rd32(0x300207fc)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CBAR_IRE_SEL_EN773Ar			(ValSft_R28(_rd32(0x300207fc))&BitMask_02)
#define CBAR_IRE_SEL_EN773Aw(val)		_wr32(0x300207fc,(UINT)((_rd32(0x300207fc)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define CBAR_HTW_EN773Ar				(ValSft_R16(_rd32(0x300207fc))&BitMask_09)
#define CBAR_HTW_EN773Aw(val)			_wr32(0x300207fc,(UINT)((_rd32(0x300207fc)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define CBAR_HSP_EN773Ar				(ValSft_R00(_rd32(0x300207fc))&BitMask_12)
#define CBAR_HSP_EN773Aw(val)			_wr32(0x300207fc,(UINT)((_rd32(0x300207fc)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define Y_MGAIN_EN773Ar					(ValSft_R00(_rd32(0x30020800))&BitMask_12)
#define Y_MGAIN_EN773Aw(val)			_wr32(0x30020800,(UINT)((_rd32(0x30020800)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WHITE_LV_EN773Ar				(ValSft_R16(_rd32(0x30020804))&BitMask_09)
#define WHITE_LV_EN773Aw(val)			_wr32(0x30020804,(UINT)((_rd32(0x30020804)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define BLANK_LV_EN773Ar				(ValSft_R00(_rd32(0x30020804))&BitMask_09)
#define BLANK_LV_EN773Aw(val)			_wr32(0x30020804,(UINT)((_rd32(0x30020804)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define PEDESTAL_LV_EN773Ar				(ValSft_R16(_rd32(0x30020808))&BitMask_09)
#define PEDESTAL_LV_EN773Aw(val)		_wr32(0x30020808,(UINT)((_rd32(0x30020808)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define Y_LPF_ON_EN773Ar				(ValSft_R14(_rd32(0x30020808))&BitMask_02)
#define Y_LPF_ON_EN773Aw(val)			_wr32(0x30020808,(UINT)((_rd32(0x30020808)&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define Y_SLEW_SEL_EN773Ar				(ValSft_R12(_rd32(0x30020808))&BitMask_02)
#define Y_SLEW_SEL_EN773Aw(val)			_wr32(0x30020808,(UINT)((_rd32(0x30020808)&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define SYNC_LV_EN773Ar					(ValSft_R00(_rd32(0x30020808))&BitMask_09)
#define SYNC_LV_EN773Aw(val)			_wr32(0x30020808,(UINT)((_rd32(0x30020808)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define CB_MGAIN_EN773Ar				(ValSft_R16(_rd32(0x3002080c))&BitMask_12)
#define CB_MGAIN_EN773Aw(val)			_wr32(0x3002080c,(UINT)((_rd32(0x3002080c)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define CR_MGAIN_EN773Ar				(ValSft_R00(_rd32(0x3002080c))&BitMask_12)
#define CR_MGAIN_EN773Aw(val)			_wr32(0x3002080c,(UINT)((_rd32(0x3002080c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define C_SLEW_SEL_EN773Ar				(ValSft_R08(_rd32(0x30020810))&BitMask_02)
#define C_SLEW_SEL_EN773Aw(val)			_wr32(0x30020810,(UINT)((_rd32(0x30020810)&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define EDGE_LPF_SEL_EN773Ar			(ValSft_R04(_rd32(0x30020810))&BitMask_04)
#define EDGE_LPF_SEL_EN773Aw(val)		_wr32(0x30020810,(UINT)((_rd32(0x30020810)&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define EDGE_LPF_ON_EN773Ar				(ValSft_R03(_rd32(0x30020810))&BitMask_01)
#define EDGE_LPF_ON_EN773Aw(val)		_wr32(0x30020810,(UINT)((_rd32(0x30020810)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define C_LPF_ON_EN773Ar				(ValSft_R00(_rd32(0x30020810))&BitMask_03)
#define C_LPF_ON_EN773Aw(val)			_wr32(0x30020810,(UINT)((_rd32(0x30020810)&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define FSC_TGT_EN773Ar					(ValSft_R00(_rd32(0x30020814))&BitMask_32)
#define FSC_TGT_EN773Aw(val)			_wr32(0x30020814,(UINT)((_rd32(0x30020814)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define YCOUT_POL_EN773Ar				(ValSft_R31(_rd32(0x30020818))&BitMask_01)
#define YCOUT_POL_EN773Aw(val)			_wr32(0x30020818,(UINT)((_rd32(0x30020818)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AY_OSEL_EN773Ar					(ValSft_R28(_rd32(0x30020818))&BitMask_03)
#define AY_OSEL_EN773Aw(val)			_wr32(0x30020818,(UINT)((_rd32(0x30020818)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define CB_BST_EN773Ar					(ValSft_R16(_rd32(0x30020818))&BitMask_09)
#define CB_BST_EN773Aw(val)				_wr32(0x30020818,(UINT)((_rd32(0x30020818)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define CR_BST_EN773Ar					(ValSft_R00(_rd32(0x30020818))&BitMask_09)
#define CR_BST_EN773Aw(val)				_wr32(0x30020818,(UINT)((_rd32(0x30020818)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define CTX_EN_EN773Ar					(ValSft_R15(_rd32(0x3002081c))&BitMask_01)
#define CTX_EN_EN773Aw(val)				_wr32(0x3002081c,(UINT)((_rd32(0x3002081c)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define CTX_ON_EN773Ar					(ValSft_R14(_rd32(0x3002081c))&BitMask_01)
#define CTX_ON_EN773Aw(val)				_wr32(0x3002081c,(UINT)((_rd32(0x3002081c)&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define CTX_SEL_EN773Ar					(ValSft_R13(_rd32(0x3002081c))&BitMask_01)
#define CTX_SEL_EN773Aw(val)			_wr32(0x3002081c,(UINT)((_rd32(0x3002081c)&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define CTX_LVL_EN773Ar					(ValSft_R00(_rd32(0x3002081c))&BitMask_08)
#define CTX_LVL_EN773Aw(val)			_wr32(0x3002081c,(UINT)((_rd32(0x3002081c)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define CXALMCU_RD0EN_EN773Ar			(ValSft_R31(_rd32(0x30020820))&BitMask_01)
#define CXALMCU_RD0EN_EN773Aw(val)		_wr32(0x30020820,(UINT)((_rd32(0x30020820)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CXALMCU_RDVPOSE0_EN773Ar		(ValSft_R16(_rd32(0x30020820))&BitMask_09)
#define CXALMCU_RDVPOSE0_EN773Aw(val)	_wr32(0x30020820,(UINT)((_rd32(0x30020820)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define CXALMCU_RDVPOSE1_EN773Ar		(ValSft_R00(_rd32(0x30020820))&BitMask_09)
#define CXALMCU_RDVPOSE1_EN773Aw(val)	_wr32(0x30020820,(UINT)((_rd32(0x30020820)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define CXALMCU_RD1EN_EN773Ar			(ValSft_R31(_rd32(0x30020824))&BitMask_01)
#define CXALMCU_RD1EN_EN773Aw(val)		_wr32(0x30020824,(UINT)((_rd32(0x30020824)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CXALMCU_RDVPOSO0_EN773Ar		(ValSft_R16(_rd32(0x30020824))&BitMask_09)
#define CXALMCU_RDVPOSO0_EN773Aw(val)	_wr32(0x30020824,(UINT)((_rd32(0x30020824)&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define CXALMCU_RDVPOSO1_EN773Ar		(ValSft_R00(_rd32(0x30020824))&BitMask_09)
#define CXALMCU_RDVPOSO1_EN773Aw(val)	_wr32(0x30020824,(UINT)((_rd32(0x30020824)&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define INT2_EN0_EN773Ar				(ValSft_R31(_rd32(0x30020828))&BitMask_01)
#define INT2_EN0_EN773Aw(val)			_wr32(0x30020828,(UINT)((_rd32(0x30020828)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT2_HSP0_EN773Ar				(ValSft_R20(_rd32(0x30020828))&BitMask_11)
#define INT2_HSP0_EN773Aw(val)			_wr32(0x30020828,(UINT)((_rd32(0x30020828)&(~ValSft_L20(BitMask_11)))|ValSft_L20((val)&BitMask_11)))

#define INT2_VSP0_E_EN773Ar				(ValSft_R10(_rd32(0x30020828))&BitMask_10)
#define INT2_VSP0_E_EN773Aw(val)		_wr32(0x30020828,(UINT)((_rd32(0x30020828)&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define INT2_VSP0_O_EN773Ar				(ValSft_R00(_rd32(0x30020828))&BitMask_10)
#define INT2_VSP0_O_EN773Aw(val)		_wr32(0x30020828,(UINT)((_rd32(0x30020828)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define INT2_EN1_EN773Ar				(ValSft_R31(_rd32(0x3002082c))&BitMask_01)
#define INT2_EN1_EN773Aw(val)			_wr32(0x3002082c,(UINT)((_rd32(0x3002082c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT2_HSP1_EN773Ar				(ValSft_R20(_rd32(0x3002082c))&BitMask_11)
#define INT2_HSP1_EN773Aw(val)			_wr32(0x3002082c,(UINT)((_rd32(0x3002082c)&(~ValSft_L20(BitMask_11)))|ValSft_L20((val)&BitMask_11)))

#define INT2_VSP1_E_EN773Ar				(ValSft_R10(_rd32(0x3002082c))&BitMask_10)
#define INT2_VSP1_E_EN773Aw(val)		_wr32(0x3002082c,(UINT)((_rd32(0x3002082c)&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define INT2_VSP1_O_EN773Ar				(ValSft_R00(_rd32(0x3002082c))&BitMask_10)
#define INT2_VSP1_O_EN773Aw(val)		_wr32(0x3002082c,(UINT)((_rd32(0x3002082c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define INT2_EN2_EN773Ar				(ValSft_R31(_rd32(0x30020830))&BitMask_01)
#define INT2_EN2_EN773Aw(val)			_wr32(0x30020830,(UINT)((_rd32(0x30020830)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT2_HSP2_EN773Ar				(ValSft_R20(_rd32(0x30020830))&BitMask_11)
#define INT2_HSP2_EN773Aw(val)			_wr32(0x30020830,(UINT)((_rd32(0x30020830)&(~ValSft_L20(BitMask_11)))|ValSft_L20((val)&BitMask_11)))

#define INT2_VSP2_E_EN773Ar				(ValSft_R10(_rd32(0x30020830))&BitMask_10)
#define INT2_VSP2_E_EN773Aw(val)		_wr32(0x30020830,(UINT)((_rd32(0x30020830)&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define INT2_VSP2_O_EN773Ar				(ValSft_R00(_rd32(0x30020830))&BitMask_10)
#define INT2_VSP2_O_EN773Aw(val)		_wr32(0x30020830,(UINT)((_rd32(0x30020830)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define INT2_EN3_EN773Ar				(ValSft_R31(_rd32(0x30020834))&BitMask_01)
#define INT2_EN3_EN773Aw(val)			_wr32(0x30020834,(UINT)((_rd32(0x30020834)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT2_HSP3_EN773Ar				(ValSft_R20(_rd32(0x30020834))&BitMask_11)
#define INT2_HSP3_EN773Aw(val)			_wr32(0x30020834,(UINT)((_rd32(0x30020834)&(~ValSft_L20(BitMask_11)))|ValSft_L20((val)&BitMask_11)))

#define INT2_VSP3_E_EN773Ar				(ValSft_R10(_rd32(0x30020834))&BitMask_10)
#define INT2_VSP3_E_EN773Aw(val)		_wr32(0x30020834,(UINT)((_rd32(0x30020834)&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define INT2_VSP3_O_EN773Ar				(ValSft_R00(_rd32(0x30020834))&BitMask_10)
#define INT2_VSP3_O_EN773Aw(val)		_wr32(0x30020834,(UINT)((_rd32(0x30020834)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LL_DETON_EN773Ar				(ValSft_R00(_rd32(0x3002083c))&BitMask_01)
#define LL_DETON_EN773Aw(val)			_wr32(0x3002083c,(UINT)((_rd32(0x3002083c)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define LL_SYNPOL_EN773Ar				(ValSft_R01(_rd32(0x3002083c))&BitMask_01)
#define LL_SYNPOL_EN773Aw(val)			_wr32(0x3002083c,(UINT)((_rd32(0x3002083c)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define WDR_OSD_ON_EN773Ar				(ValSft_R31(_rd32(0x30020840))&BitMask_01)
#define WDR_OSD_ON_EN773Aw(val)			_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define WDR_SCH_MON_EN773Ar				(ValSft_R30(_rd32(0x30020840))&BitMask_01)
#define WDR_SCH_MON_EN773Aw(val)		_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SGAMMA_ON_EN773Ar				(ValSft_R29(_rd32(0x30020840))&BitMask_01)
#define SGAMMA_ON_EN773Aw(val)			_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define SWGT_LIMT_ON_EN773Ar			(ValSft_R28(_rd32(0x30020840))&BitMask_01)
#define SWGT_LIMT_ON_EN773Aw(val)		_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define WDR_LSCHG_EN773Ar				(ValSft_R27(_rd32(0x30020840))&BitMask_01)
#define WDR_LSCHG_EN773Aw(val)			_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define WDR_TSEL_EN773Ar				(ValSft_R16(_rd32(0x30020840))&BitMask_05)
#define WDR_TSEL_EN773Aw(val)			_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))

#define WDR_SATV_EN773Ar				(ValSft_R00(_rd32(0x30020840))&BitMask_12)
#define WDR_SATV_EN773Aw(val)			_wr32(0x30020840,(UINT)((_rd32(0x30020840)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CO_UPPOS_EN773Ar				(ValSft_R16(_rd32(0x30020844))&BitMask_08)
#define CO_UPPOS_EN773Aw(val)			_wr32(0x30020844,(UINT)((_rd32(0x30020844)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define WDR_SWGT_EN773Ar				(ValSft_R00(_rd32(0x30020844))&BitMask_12)
#define WDR_SWGT_EN773Aw(val)			_wr32(0x30020844,(UINT)((_rd32(0x30020844)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_LSHUT_EN773Ar				(ValSft_R16(_rd32(0x30020848))&BitMask_12)
#define WDR_LSHUT_EN773Aw(val)			_wr32(0x30020848,(UINT)((_rd32(0x30020848)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_SSHUT_EN773Ar				(ValSft_R00(_rd32(0x30020848))&BitMask_12)
#define WDR_SSHUT_EN773Aw(val)			_wr32(0x30020848,(UINT)((_rd32(0x30020848)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_SGM_RANGE_EN773Ar			(ValSft_R16(_rd32(0x3002084c))&BitMask_10)
#define WDR_SGM_RANGE_EN773Aw(val)		_wr32(0x3002084c,(UINT)((_rd32(0x3002084c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define WDR_SCH_MAX_EN773Ar				(ValSft_R00(_rd32(0x3002084c))&BitMask_12)
#define WDR_SCH_MAX_EN773Aw(val)		_wr32(0x3002084c,(UINT)((_rd32(0x3002084c)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_MVTH_EN773Ar				(ValSft_R24(_rd32(0x30020850))&BitMask_08)
#define WDR_MVTH_EN773Aw(val)			_wr32(0x30020850,(UINT)((_rd32(0x30020850)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define YR_GAIN_EN773Ar					(ValSft_R16(_rd32(0x30020850))&BitMask_08)
#define YR_GAIN_EN773Aw(val)			_wr32(0x30020850,(UINT)((_rd32(0x30020850)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define MV_ON_EN773Ar					(ValSft_R15(_rd32(0x30020850))&BitMask_01)
#define MV_ON_EN773Aw(val)				_wr32(0x30020850,(UINT)((_rd32(0x30020850)&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define BIT_MAX_EN773Ar					(ValSft_R00(_rd32(0x30020850))&BitMask_12)
#define BIT_MAX_EN773Aw(val)			_wr32(0x30020850,(UINT)((_rd32(0x30020850)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define IMD_ON_EN773Ar					(ValSft_R31(_rd32(0x30020854))&BitMask_01)
#define IMD_ON_EN773Aw(val)				_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IMD_FLT_EN773Ar					(ValSft_R30(_rd32(0x30020854))&BitMask_01)
#define IMD_FLT_EN773Aw(val)			_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define IMD_TEST_EN773Ar				(ValSft_R28(_rd32(0x30020854))&BitMask_02)
#define IMD_TEST_EN773Aw(val)			_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define IMD_COLOR_EN773Ar				(ValSft_R25(_rd32(0x30020854))&BitMask_03)
#define IMD_COLOR_EN773Aw(val)			_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L25(BitMask_03)))|ValSft_L25((val)&BitMask_03)))

#define IMD_TH_EN773Ar					(ValSft_R16(_rd32(0x30020854))&BitMask_08)
#define IMD_TH_EN773Aw(val)				_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define IMD_HW_EN773Ar					(ValSft_R08(_rd32(0x30020854))&BitMask_07)
#define IMD_HW_EN773Aw(val)				_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define IMD_VW_EN773Ar					(ValSft_R00(_rd32(0x30020854))&BitMask_06)
#define IMD_VW_EN773Aw(val)				_wr32(0x30020854,(UINT)((_rd32(0x30020854)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define IMD_HSP_EN773Ar					(ValSft_R16(_rd32(0x30020858))&BitMask_12)
#define IMD_HSP_EN773Aw(val)			_wr32(0x30020858,(UINT)((_rd32(0x30020858)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define IMD_VSP_EN773Ar					(ValSft_R00(_rd32(0x30020858))&BitMask_11)
#define IMD_VSP_EN773Aw(val)			_wr32(0x30020858,(UINT)((_rd32(0x30020858)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define IMD_BUPC_EN773Ar				(ValSft_R24(_rd32(0x3002085c))&BitMask_08)
#define IMD_BUPC_EN773Aw(val)			_wr32(0x3002085c,(UINT)((_rd32(0x3002085c)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define IMD_BDW_EN773Ar					(ValSft_R23(_rd32(0x3002085c))&BitMask_01)
#define IMD_BDW_EN773Aw(val)			_wr32(0x3002085c,(UINT)((_rd32(0x3002085c)&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define IMD_GMA_EN773Ar					(ValSft_R22(_rd32(0x3002085c))&BitMask_01)
#define IMD_GMA_EN773Aw(val)			_wr32(0x3002085c,(UINT)((_rd32(0x3002085c)&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define IMD_OSDON_EN773Ar				(ValSft_R16(_rd32(0x3002085c))&BitMask_06)
#define IMD_OSDON_EN773Aw(val)			_wr32(0x3002085c,(UINT)((_rd32(0x3002085c)&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define IMD_OSDLV_EN773Ar				(ValSft_R00(_rd32(0x3002085c))&BitMask_10)
#define IMD_OSDLV_EN773Aw(val)			_wr32(0x3002085c,(UINT)((_rd32(0x3002085c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define IMD_KMAX_EN773Ar				(ValSft_R24(_rd32(0x30020860))&BitMask_08)
#define IMD_KMAX_EN773Aw(val)			_wr32(0x30020860,(UINT)((_rd32(0x30020860)&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define IMD_KMIN_EN773Ar				(ValSft_R16(_rd32(0x30020860))&BitMask_08)
#define IMD_KMIN_EN773Aw(val)			_wr32(0x30020860,(UINT)((_rd32(0x30020860)&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define IMD_KGA_EN773Ar					(ValSft_R08(_rd32(0x30020860))&BitMask_08)
#define IMD_KGA_EN773Aw(val)			_wr32(0x30020860,(UINT)((_rd32(0x30020860)&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define IMD_KTH_EN773Ar					(ValSft_R00(_rd32(0x30020860))&BitMask_08)
#define IMD_KTH_EN773Aw(val)			_wr32(0x30020860,(UINT)((_rd32(0x30020860)&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define IMD_WON1_EN773Ar				(ValSft_R31(_rd32(0x30020864))&BitMask_01)
#define IMD_WON1_EN773Aw(val)			_wr32(0x30020864,(UINT)((_rd32(0x30020864)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IMD_WHSP1_EN773Ar				(ValSft_R24(_rd32(0x30020864))&BitMask_07)
#define IMD_WHSP1_EN773Aw(val)			_wr32(0x30020864,(UINT)((_rd32(0x30020864)&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define IMD_WHEP1_EN773Ar				(ValSft_R16(_rd32(0x30020864))&BitMask_07)
#define IMD_WHEP1_EN773Aw(val)			_wr32(0x30020864,(UINT)((_rd32(0x30020864)&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define IMD_WVSP1_EN773Ar				(ValSft_R08(_rd32(0x30020864))&BitMask_06)
#define IMD_WVSP1_EN773Aw(val)			_wr32(0x30020864,(UINT)((_rd32(0x30020864)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define IMD_WVEP1_EN773Ar				(ValSft_R00(_rd32(0x30020864))&BitMask_06)
#define IMD_WVEP1_EN773Aw(val)			_wr32(0x30020864,(UINT)((_rd32(0x30020864)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define IMD_WON2_EN773Ar				(ValSft_R31(_rd32(0x30020868))&BitMask_01)
#define IMD_WON2_EN773Aw(val)			_wr32(0x30020868,(UINT)((_rd32(0x30020868)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IMD_WHSP2_EN773Ar				(ValSft_R24(_rd32(0x30020868))&BitMask_07)
#define IMD_WHSP2_EN773Aw(val)			_wr32(0x30020868,(UINT)((_rd32(0x30020868)&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define IMD_WHEP2_EN773Ar				(ValSft_R16(_rd32(0x30020868))&BitMask_07)
#define IMD_WHEP2_EN773Aw(val)			_wr32(0x30020868,(UINT)((_rd32(0x30020868)&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define IMD_WVSP2_EN773Ar				(ValSft_R08(_rd32(0x30020868))&BitMask_06)
#define IMD_WVSP2_EN773Aw(val)			_wr32(0x30020868,(UINT)((_rd32(0x30020868)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define IMD_WVEP2_EN773Ar				(ValSft_R00(_rd32(0x30020868))&BitMask_06)
#define IMD_WVEP2_EN773Aw(val)			_wr32(0x30020868,(UINT)((_rd32(0x30020868)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define IMD_WON3_EN773Ar				(ValSft_R31(_rd32(0x3002086c))&BitMask_01)
#define IMD_WON3_EN773Aw(val)			_wr32(0x3002086c,(UINT)((_rd32(0x3002086c)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IMD_WHSP3_EN773Ar				(ValSft_R24(_rd32(0x3002086c))&BitMask_07)
#define IMD_WHSP3_EN773Aw(val)			_wr32(0x3002086c,(UINT)((_rd32(0x3002086c)&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define IMD_WHEP3_EN773Ar				(ValSft_R16(_rd32(0x3002086c))&BitMask_07)
#define IMD_WHEP3_EN773Aw(val)			_wr32(0x3002086c,(UINT)((_rd32(0x3002086c)&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define IMD_WVSP3_EN773Ar				(ValSft_R08(_rd32(0x3002086c))&BitMask_06)
#define IMD_WVSP3_EN773Aw(val)			_wr32(0x3002086c,(UINT)((_rd32(0x3002086c)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define IMD_WVEP3_EN773Ar				(ValSft_R00(_rd32(0x3002086c))&BitMask_06)
#define IMD_WVEP3_EN773Aw(val)			_wr32(0x3002086c,(UINT)((_rd32(0x3002086c)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define IMD_WON4_EN773Ar				(ValSft_R31(_rd32(0x30020870))&BitMask_01)
#define IMD_WON4_EN773Aw(val)			_wr32(0x30020870,(UINT)((_rd32(0x30020870)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IMD_WHSP4_EN773Ar				(ValSft_R24(_rd32(0x30020870))&BitMask_07)
#define IMD_WHSP4_EN773Aw(val)			_wr32(0x30020870,(UINT)((_rd32(0x30020870)&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define IMD_WHEP4_EN773Ar				(ValSft_R16(_rd32(0x30020870))&BitMask_07)
#define IMD_WHEP4_EN773Aw(val)			_wr32(0x30020870,(UINT)((_rd32(0x30020870)&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define IMD_WVSP4_EN773Ar				(ValSft_R08(_rd32(0x30020870))&BitMask_06)
#define IMD_WVSP4_EN773Aw(val)			_wr32(0x30020870,(UINT)((_rd32(0x30020870)&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define IMD_WVEP4_EN773Ar				(ValSft_R00(_rd32(0x30020870))&BitMask_06)
#define IMD_WVEP4_EN773Aw(val)			_wr32(0x30020870,(UINT)((_rd32(0x30020870)&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define VDS_SDI_EN773Ar					(ValSft_R11(_rd32(0x3002088c))&BitMask_01)
#define VDS_SDI_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define VDS_ITU_EN773Ar					(ValSft_R10(_rd32(0x3002088c))&BitMask_01)
#define VDS_ITU_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L10(BitMask_01)))|ValSft_L10((val)&BitMask_01)))

#define ITU_INDI_EN773Ar				(ValSft_R09(_rd32(0x3002088c))&BitMask_01)
#define ITU_INDI_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define ITU_SCON_EN773Ar				(ValSft_R08(_rd32(0x3002088c))&BitMask_01)
#define ITU_SCON_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define ORDR_TEST_EN773Ar				(ValSft_R06(_rd32(0x3002088c))&BitMask_01)
#define ORDR_TEST_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define ITU_ORDR_EN773Ar				(ValSft_R05(_rd32(0x3002088c))&BitMask_01)
#define ITU_ORDR_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define ITU_VID_EN773Ar					(ValSft_R04(_rd32(0x3002088c))&BitMask_01)
#define ITU_VID_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define ITU_FID_EN773Ar					(ValSft_R03(_rd32(0x3002088c))&BitMask_01)
#define ITU_FID_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define SDI_YCCH_EN773Ar				(ValSft_R02(_rd32(0x3002088c))&BitMask_01)
#define SDI_YCCH_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define SDI_OPOL_EN773Ar				(ValSft_R01(_rd32(0x3002088c))&BitMask_01)
#define SDI_OPOL_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define YCBR_INV_EN773Ar				(ValSft_R00(_rd32(0x3002088c))&BitMask_01)
#define YCBR_INV_EN773Aw(val)			_wr32(0x3002088c,(UINT)((_rd32(0x3002088c)&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define HD10_BYPASS_EN773Ar				(ValSft_R31(_rd32(0x30020890))&BitMask_01)
#define HD10_BYPASS_EN773Aw(val)		_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CRC_REON_EN773Ar				(ValSft_R30(_rd32(0x30020890))&BitMask_01)
#define CRC_REON_EN773Aw(val)			_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define LNO_REON_EN773Ar				(ValSft_R29(_rd32(0x30020890))&BitMask_01)
#define LNO_REON_EN773Aw(val)			_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define BLK_REON_EN773Ar				(ValSft_R28(_rd32(0x30020890))&BitMask_01)
#define BLK_REON_EN773Aw(val)			_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define ANC_ON_EN773Ar					(ValSft_R27(_rd32(0x30020890))&BitMask_01)
#define ANC_ON_EN773Aw(val)				_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define PATHO_ON_EN773Ar				(ValSft_R26(_rd32(0x30020890))&BitMask_01)
#define PATHO_ON_EN773Aw(val)			_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define PATHO_TOG_ON_EN773Ar			(ValSft_R25(_rd32(0x30020890))&BitMask_01)
#define PATHO_TOG_ON_EN773Aw(val)		_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define PATHO_LINE_EN773Ar				(ValSft_R00(_rd32(0x30020890))&BitMask_10)
#define PATHO_LINE_EN773Aw(val)			_wr32(0x30020890,(UINT)((_rd32(0x30020890)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI_LN_EN773Ar					(ValSft_R16(_rd32(0x30020894))&BitMask_11)
#define ANCI_LN_EN773Aw(val)			_wr32(0x30020894,(UINT)((_rd32(0x30020894)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define ANCI_PN_EN773Ar					(ValSft_R00(_rd32(0x30020894))&BitMask_12)
#define ANCI_PN_EN773Aw(val)			_wr32(0x30020894,(UINT)((_rd32(0x30020894)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ANCI00_EN773Ar					(ValSft_R16(_rd32(0x30020898))&BitMask_10)
#define ANCI00_EN773Aw(val)				_wr32(0x30020898,(UINT)((_rd32(0x30020898)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI01_EN773Ar					(ValSft_R00(_rd32(0x30020898))&BitMask_10)
#define ANCI01_EN773Aw(val)				_wr32(0x30020898,(UINT)((_rd32(0x30020898)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI02_EN773Ar					(ValSft_R16(_rd32(0x3002089c))&BitMask_10)
#define ANCI02_EN773Aw(val)				_wr32(0x3002089c,(UINT)((_rd32(0x3002089c)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI03_EN773Ar					(ValSft_R00(_rd32(0x3002089c))&BitMask_10)
#define ANCI03_EN773Aw(val)				_wr32(0x3002089c,(UINT)((_rd32(0x3002089c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI04_EN773Ar					(ValSft_R16(_rd32(0x300208a0))&BitMask_10)
#define ANCI04_EN773Aw(val)				_wr32(0x300208a0,(UINT)((_rd32(0x300208a0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI05_EN773Ar					(ValSft_R00(_rd32(0x300208a0))&BitMask_10)
#define ANCI05_EN773Aw(val)				_wr32(0x300208a0,(UINT)((_rd32(0x300208a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI06_EN773Ar					(ValSft_R16(_rd32(0x300208a4))&BitMask_10)
#define ANCI06_EN773Aw(val)				_wr32(0x300208a4,(UINT)((_rd32(0x300208a4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI07_EN773Ar					(ValSft_R00(_rd32(0x300208a4))&BitMask_10)
#define ANCI07_EN773Aw(val)				_wr32(0x300208a4,(UINT)((_rd32(0x300208a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI08_EN773Ar					(ValSft_R16(_rd32(0x300208a8))&BitMask_10)
#define ANCI08_EN773Aw(val)				_wr32(0x300208a8,(UINT)((_rd32(0x300208a8)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI09_EN773Ar					(ValSft_R00(_rd32(0x300208a8))&BitMask_10)
#define ANCI09_EN773Aw(val)				_wr32(0x300208a8,(UINT)((_rd32(0x300208a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI10_EN773Ar					(ValSft_R16(_rd32(0x300208ac))&BitMask_10)
#define ANCI10_EN773Aw(val)				_wr32(0x300208ac,(UINT)((_rd32(0x300208ac)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI11_EN773Ar					(ValSft_R00(_rd32(0x300208ac))&BitMask_10)
#define ANCI11_EN773Aw(val)				_wr32(0x300208ac,(UINT)((_rd32(0x300208ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI12_EN773Ar					(ValSft_R16(_rd32(0x300208b0))&BitMask_10)
#define ANCI12_EN773Aw(val)				_wr32(0x300208b0,(UINT)((_rd32(0x300208b0)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI13_EN773Ar					(ValSft_R00(_rd32(0x300208b0))&BitMask_10)
#define ANCI13_EN773Aw(val)				_wr32(0x300208b0,(UINT)((_rd32(0x300208b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ANCI14_EN773Ar					(ValSft_R16(_rd32(0x300208b4))&BitMask_10)
#define ANCI14_EN773Aw(val)				_wr32(0x300208b4,(UINT)((_rd32(0x300208b4)&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define ANCI15_EN773Ar					(ValSft_R00(_rd32(0x300208b4))&BitMask_10)
#define ANCI15_EN773Aw(val)				_wr32(0x300208b4,(UINT)((_rd32(0x300208b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define VDS_MODE_EN773Ar				(ValSft_R28(_rd32(0x300208c0))&BitMask_03)
#define VDS_MODE_EN773Aw(val)			_wr32(0x300208c0,(UINT)((_rd32(0x300208c0)&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define VDS_HSPC_EN773Ar				(ValSft_R16(_rd32(0x300208c0))&BitMask_12)
#define VDS_HSPC_EN773Aw(val)			_wr32(0x300208c0,(UINT)((_rd32(0x300208c0)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define VDS_VSPC_EN773Ar				(ValSft_R00(_rd32(0x300208c0))&BitMask_11)
#define VDS_VSPC_EN773Aw(val)			_wr32(0x300208c0,(UINT)((_rd32(0x300208c0)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define VDS_HWC_EN773Ar					(ValSft_R16(_rd32(0x300208c4))&BitMask_12)
#define VDS_HWC_EN773Aw(val)			_wr32(0x300208c4,(UINT)((_rd32(0x300208c4)&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define VDS_VWC_EN773Ar					(ValSft_R00(_rd32(0x300208c4))&BitMask_11)
#define VDS_VWC_EN773Aw(val)			_wr32(0x300208c4,(UINT)((_rd32(0x300208c4)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define VDS_HSRP_EN773Ar				(ValSft_R16(_rd32(0x300208c8))&BitMask_14)
#define VDS_HSRP_EN773Aw(val)			_wr32(0x300208c8,(UINT)((_rd32(0x300208c8)&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define VDS_HSFP_EN773Ar				(ValSft_R00(_rd32(0x300208c8))&BitMask_14)
#define VDS_HSFP_EN773Aw(val)			_wr32(0x300208c8,(UINT)((_rd32(0x300208c8)&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define VDS_VSRP_EN773Ar				(ValSft_R16(_rd32(0x300208cc))&BitMask_11)
#define VDS_VSRP_EN773Aw(val)			_wr32(0x300208cc,(UINT)((_rd32(0x300208cc)&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define VDS_VSFP_EN773Ar				(ValSft_R00(_rd32(0x300208cc))&BitMask_11)
#define VDS_VSFP_EN773Aw(val)			_wr32(0x300208cc,(UINT)((_rd32(0x300208cc)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define VDS_VSTRG_EN773Ar				(ValSft_R31(_rd32(0x300208d0))&BitMask_01)
#define VDS_VSTRG_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define VDS_HSINV_EN773Ar				(ValSft_R30(_rd32(0x300208d0))&BitMask_01)
#define VDS_HSINV_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define VDS_VSINV_EN773Ar				(ValSft_R29(_rd32(0x300208d0))&BitMask_01)
#define VDS_VSINV_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define VDS_HSOEN_EN773Ar				(ValSft_R28(_rd32(0x300208d0))&BitMask_01)
#define VDS_HSOEN_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define VDS_VSOEN_EN773Ar				(ValSft_R27(_rd32(0x300208d0))&BitMask_01)
#define VDS_VSOEN_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define VDS_VFINV_EN773Ar				(ValSft_R26(_rd32(0x300208d0))&BitMask_01)
#define VDS_VFINV_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define VDS_HSP_EN773Ar					(ValSft_R00(_rd32(0x300208d0))&BitMask_14)
#define VDS_HSP_EN773Aw(val)			_wr32(0x300208d0,(UINT)((_rd32(0x300208d0)&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define EXL_SDI_EN773Ar					(ValSft_R31(_rd32(0x300208d4))&BitMask_01)
#define EXL_SDI_EN773Aw(val)			_wr32(0x300208d4,(UINT)((_rd32(0x300208d4)&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXL_ITU_EN773Ar					(ValSft_R30(_rd32(0x300208d4))&BitMask_01)
#define EXL_ITU_EN773Aw(val)			_wr32(0x300208d4,(UINT)((_rd32(0x300208d4)&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define DCKO_13P5_EN773Ar				(ValSft_R29(_rd32(0x300208d4))&BitMask_01)
#define DCKO_13P5_EN773Aw(val)			_wr32(0x300208d4,(UINT)((_rd32(0x300208d4)&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define SHADIG000_EN773Ar				(ValSft_R00(_rd32(0x30021000))&BitMask_10)
#define SHADIG000_EN773Aw(val)			_wr32(0x30021000,(UINT)((_rd32(0x30021000)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG001_EN773Ar				(ValSft_R00(_rd32(0x30021004))&BitMask_10)
#define SHADIG001_EN773Aw(val)			_wr32(0x30021004,(UINT)((_rd32(0x30021004)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG002_EN773Ar				(ValSft_R00(_rd32(0x30021008))&BitMask_10)
#define SHADIG002_EN773Aw(val)			_wr32(0x30021008,(UINT)((_rd32(0x30021008)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG003_EN773Ar				(ValSft_R00(_rd32(0x3002100c))&BitMask_10)
#define SHADIG003_EN773Aw(val)			_wr32(0x3002100c,(UINT)((_rd32(0x3002100c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG004_EN773Ar				(ValSft_R00(_rd32(0x30021010))&BitMask_10)
#define SHADIG004_EN773Aw(val)			_wr32(0x30021010,(UINT)((_rd32(0x30021010)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG005_EN773Ar				(ValSft_R00(_rd32(0x30021014))&BitMask_10)
#define SHADIG005_EN773Aw(val)			_wr32(0x30021014,(UINT)((_rd32(0x30021014)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG006_EN773Ar				(ValSft_R00(_rd32(0x30021018))&BitMask_10)
#define SHADIG006_EN773Aw(val)			_wr32(0x30021018,(UINT)((_rd32(0x30021018)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG007_EN773Ar				(ValSft_R00(_rd32(0x3002101c))&BitMask_10)
#define SHADIG007_EN773Aw(val)			_wr32(0x3002101c,(UINT)((_rd32(0x3002101c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG008_EN773Ar				(ValSft_R00(_rd32(0x30021020))&BitMask_10)
#define SHADIG008_EN773Aw(val)			_wr32(0x30021020,(UINT)((_rd32(0x30021020)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG009_EN773Ar				(ValSft_R00(_rd32(0x30021024))&BitMask_10)
#define SHADIG009_EN773Aw(val)			_wr32(0x30021024,(UINT)((_rd32(0x30021024)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00a_EN773Ar				(ValSft_R00(_rd32(0x30021028))&BitMask_10)
#define SHADIG00a_EN773Aw(val)			_wr32(0x30021028,(UINT)((_rd32(0x30021028)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00b_EN773Ar				(ValSft_R00(_rd32(0x3002102c))&BitMask_10)
#define SHADIG00b_EN773Aw(val)			_wr32(0x3002102c,(UINT)((_rd32(0x3002102c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00c_EN773Ar				(ValSft_R00(_rd32(0x30021030))&BitMask_10)
#define SHADIG00c_EN773Aw(val)			_wr32(0x30021030,(UINT)((_rd32(0x30021030)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00d_EN773Ar				(ValSft_R00(_rd32(0x30021034))&BitMask_10)
#define SHADIG00d_EN773Aw(val)			_wr32(0x30021034,(UINT)((_rd32(0x30021034)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00e_EN773Ar				(ValSft_R00(_rd32(0x30021038))&BitMask_10)
#define SHADIG00e_EN773Aw(val)			_wr32(0x30021038,(UINT)((_rd32(0x30021038)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG00f_EN773Ar				(ValSft_R00(_rd32(0x3002103c))&BitMask_10)
#define SHADIG00f_EN773Aw(val)			_wr32(0x3002103c,(UINT)((_rd32(0x3002103c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG010_EN773Ar				(ValSft_R00(_rd32(0x30021040))&BitMask_10)
#define SHADIG010_EN773Aw(val)			_wr32(0x30021040,(UINT)((_rd32(0x30021040)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG011_EN773Ar				(ValSft_R00(_rd32(0x30021044))&BitMask_10)
#define SHADIG011_EN773Aw(val)			_wr32(0x30021044,(UINT)((_rd32(0x30021044)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG012_EN773Ar				(ValSft_R00(_rd32(0x30021048))&BitMask_10)
#define SHADIG012_EN773Aw(val)			_wr32(0x30021048,(UINT)((_rd32(0x30021048)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG013_EN773Ar				(ValSft_R00(_rd32(0x3002104c))&BitMask_10)
#define SHADIG013_EN773Aw(val)			_wr32(0x3002104c,(UINT)((_rd32(0x3002104c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG014_EN773Ar				(ValSft_R00(_rd32(0x30021050))&BitMask_10)
#define SHADIG014_EN773Aw(val)			_wr32(0x30021050,(UINT)((_rd32(0x30021050)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG015_EN773Ar				(ValSft_R00(_rd32(0x30021054))&BitMask_10)
#define SHADIG015_EN773Aw(val)			_wr32(0x30021054,(UINT)((_rd32(0x30021054)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG016_EN773Ar				(ValSft_R00(_rd32(0x30021058))&BitMask_10)
#define SHADIG016_EN773Aw(val)			_wr32(0x30021058,(UINT)((_rd32(0x30021058)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG017_EN773Ar				(ValSft_R00(_rd32(0x3002105c))&BitMask_10)
#define SHADIG017_EN773Aw(val)			_wr32(0x3002105c,(UINT)((_rd32(0x3002105c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG018_EN773Ar				(ValSft_R00(_rd32(0x30021060))&BitMask_10)
#define SHADIG018_EN773Aw(val)			_wr32(0x30021060,(UINT)((_rd32(0x30021060)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG019_EN773Ar				(ValSft_R00(_rd32(0x30021064))&BitMask_10)
#define SHADIG019_EN773Aw(val)			_wr32(0x30021064,(UINT)((_rd32(0x30021064)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01a_EN773Ar				(ValSft_R00(_rd32(0x30021068))&BitMask_10)
#define SHADIG01a_EN773Aw(val)			_wr32(0x30021068,(UINT)((_rd32(0x30021068)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01b_EN773Ar				(ValSft_R00(_rd32(0x3002106c))&BitMask_10)
#define SHADIG01b_EN773Aw(val)			_wr32(0x3002106c,(UINT)((_rd32(0x3002106c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01c_EN773Ar				(ValSft_R00(_rd32(0x30021070))&BitMask_10)
#define SHADIG01c_EN773Aw(val)			_wr32(0x30021070,(UINT)((_rd32(0x30021070)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01d_EN773Ar				(ValSft_R00(_rd32(0x30021074))&BitMask_10)
#define SHADIG01d_EN773Aw(val)			_wr32(0x30021074,(UINT)((_rd32(0x30021074)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01e_EN773Ar				(ValSft_R00(_rd32(0x30021078))&BitMask_10)
#define SHADIG01e_EN773Aw(val)			_wr32(0x30021078,(UINT)((_rd32(0x30021078)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG01f_EN773Ar				(ValSft_R00(_rd32(0x3002107c))&BitMask_10)
#define SHADIG01f_EN773Aw(val)			_wr32(0x3002107c,(UINT)((_rd32(0x3002107c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG020_EN773Ar				(ValSft_R00(_rd32(0x30021080))&BitMask_10)
#define SHADIG020_EN773Aw(val)			_wr32(0x30021080,(UINT)((_rd32(0x30021080)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG021_EN773Ar				(ValSft_R00(_rd32(0x30021084))&BitMask_10)
#define SHADIG021_EN773Aw(val)			_wr32(0x30021084,(UINT)((_rd32(0x30021084)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG022_EN773Ar				(ValSft_R00(_rd32(0x30021088))&BitMask_10)
#define SHADIG022_EN773Aw(val)			_wr32(0x30021088,(UINT)((_rd32(0x30021088)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG023_EN773Ar				(ValSft_R00(_rd32(0x3002108c))&BitMask_10)
#define SHADIG023_EN773Aw(val)			_wr32(0x3002108c,(UINT)((_rd32(0x3002108c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG024_EN773Ar				(ValSft_R00(_rd32(0x30021090))&BitMask_10)
#define SHADIG024_EN773Aw(val)			_wr32(0x30021090,(UINT)((_rd32(0x30021090)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG025_EN773Ar				(ValSft_R00(_rd32(0x30021094))&BitMask_10)
#define SHADIG025_EN773Aw(val)			_wr32(0x30021094,(UINT)((_rd32(0x30021094)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG026_EN773Ar				(ValSft_R00(_rd32(0x30021098))&BitMask_10)
#define SHADIG026_EN773Aw(val)			_wr32(0x30021098,(UINT)((_rd32(0x30021098)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG027_EN773Ar				(ValSft_R00(_rd32(0x3002109c))&BitMask_10)
#define SHADIG027_EN773Aw(val)			_wr32(0x3002109c,(UINT)((_rd32(0x3002109c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG028_EN773Ar				(ValSft_R00(_rd32(0x300210a0))&BitMask_10)
#define SHADIG028_EN773Aw(val)			_wr32(0x300210a0,(UINT)((_rd32(0x300210a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG029_EN773Ar				(ValSft_R00(_rd32(0x300210a4))&BitMask_10)
#define SHADIG029_EN773Aw(val)			_wr32(0x300210a4,(UINT)((_rd32(0x300210a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02a_EN773Ar				(ValSft_R00(_rd32(0x300210a8))&BitMask_10)
#define SHADIG02a_EN773Aw(val)			_wr32(0x300210a8,(UINT)((_rd32(0x300210a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02b_EN773Ar				(ValSft_R00(_rd32(0x300210ac))&BitMask_10)
#define SHADIG02b_EN773Aw(val)			_wr32(0x300210ac,(UINT)((_rd32(0x300210ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02c_EN773Ar				(ValSft_R00(_rd32(0x300210b0))&BitMask_10)
#define SHADIG02c_EN773Aw(val)			_wr32(0x300210b0,(UINT)((_rd32(0x300210b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02d_EN773Ar				(ValSft_R00(_rd32(0x300210b4))&BitMask_10)
#define SHADIG02d_EN773Aw(val)			_wr32(0x300210b4,(UINT)((_rd32(0x300210b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02e_EN773Ar				(ValSft_R00(_rd32(0x300210b8))&BitMask_10)
#define SHADIG02e_EN773Aw(val)			_wr32(0x300210b8,(UINT)((_rd32(0x300210b8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG02f_EN773Ar				(ValSft_R00(_rd32(0x300210bc))&BitMask_10)
#define SHADIG02f_EN773Aw(val)			_wr32(0x300210bc,(UINT)((_rd32(0x300210bc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG030_EN773Ar				(ValSft_R00(_rd32(0x300210c0))&BitMask_10)
#define SHADIG030_EN773Aw(val)			_wr32(0x300210c0,(UINT)((_rd32(0x300210c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG031_EN773Ar				(ValSft_R00(_rd32(0x300210c4))&BitMask_10)
#define SHADIG031_EN773Aw(val)			_wr32(0x300210c4,(UINT)((_rd32(0x300210c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG032_EN773Ar				(ValSft_R00(_rd32(0x300210c8))&BitMask_10)
#define SHADIG032_EN773Aw(val)			_wr32(0x300210c8,(UINT)((_rd32(0x300210c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG033_EN773Ar				(ValSft_R00(_rd32(0x300210cc))&BitMask_10)
#define SHADIG033_EN773Aw(val)			_wr32(0x300210cc,(UINT)((_rd32(0x300210cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG034_EN773Ar				(ValSft_R00(_rd32(0x300210d0))&BitMask_10)
#define SHADIG034_EN773Aw(val)			_wr32(0x300210d0,(UINT)((_rd32(0x300210d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG035_EN773Ar				(ValSft_R00(_rd32(0x300210d4))&BitMask_10)
#define SHADIG035_EN773Aw(val)			_wr32(0x300210d4,(UINT)((_rd32(0x300210d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG036_EN773Ar				(ValSft_R00(_rd32(0x300210d8))&BitMask_10)
#define SHADIG036_EN773Aw(val)			_wr32(0x300210d8,(UINT)((_rd32(0x300210d8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG037_EN773Ar				(ValSft_R00(_rd32(0x300210dc))&BitMask_10)
#define SHADIG037_EN773Aw(val)			_wr32(0x300210dc,(UINT)((_rd32(0x300210dc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG038_EN773Ar				(ValSft_R00(_rd32(0x300210e0))&BitMask_10)
#define SHADIG038_EN773Aw(val)			_wr32(0x300210e0,(UINT)((_rd32(0x300210e0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG039_EN773Ar				(ValSft_R00(_rd32(0x300210e4))&BitMask_10)
#define SHADIG039_EN773Aw(val)			_wr32(0x300210e4,(UINT)((_rd32(0x300210e4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03a_EN773Ar				(ValSft_R00(_rd32(0x300210e8))&BitMask_10)
#define SHADIG03a_EN773Aw(val)			_wr32(0x300210e8,(UINT)((_rd32(0x300210e8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03b_EN773Ar				(ValSft_R00(_rd32(0x300210ec))&BitMask_10)
#define SHADIG03b_EN773Aw(val)			_wr32(0x300210ec,(UINT)((_rd32(0x300210ec)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03c_EN773Ar				(ValSft_R00(_rd32(0x300210f0))&BitMask_10)
#define SHADIG03c_EN773Aw(val)			_wr32(0x300210f0,(UINT)((_rd32(0x300210f0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03d_EN773Ar				(ValSft_R00(_rd32(0x300210f4))&BitMask_10)
#define SHADIG03d_EN773Aw(val)			_wr32(0x300210f4,(UINT)((_rd32(0x300210f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03e_EN773Ar				(ValSft_R00(_rd32(0x300210f8))&BitMask_10)
#define SHADIG03e_EN773Aw(val)			_wr32(0x300210f8,(UINT)((_rd32(0x300210f8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG03f_EN773Ar				(ValSft_R00(_rd32(0x300210fc))&BitMask_10)
#define SHADIG03f_EN773Aw(val)			_wr32(0x300210fc,(UINT)((_rd32(0x300210fc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG040_EN773Ar				(ValSft_R00(_rd32(0x30021100))&BitMask_10)
#define SHADIG040_EN773Aw(val)			_wr32(0x30021100,(UINT)((_rd32(0x30021100)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG041_EN773Ar				(ValSft_R00(_rd32(0x30021104))&BitMask_10)
#define SHADIG041_EN773Aw(val)			_wr32(0x30021104,(UINT)((_rd32(0x30021104)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG042_EN773Ar				(ValSft_R00(_rd32(0x30021108))&BitMask_10)
#define SHADIG042_EN773Aw(val)			_wr32(0x30021108,(UINT)((_rd32(0x30021108)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG043_EN773Ar				(ValSft_R00(_rd32(0x3002110c))&BitMask_10)
#define SHADIG043_EN773Aw(val)			_wr32(0x3002110c,(UINT)((_rd32(0x3002110c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG044_EN773Ar				(ValSft_R00(_rd32(0x30021110))&BitMask_10)
#define SHADIG044_EN773Aw(val)			_wr32(0x30021110,(UINT)((_rd32(0x30021110)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG045_EN773Ar				(ValSft_R00(_rd32(0x30021114))&BitMask_10)
#define SHADIG045_EN773Aw(val)			_wr32(0x30021114,(UINT)((_rd32(0x30021114)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG046_EN773Ar				(ValSft_R00(_rd32(0x30021118))&BitMask_10)
#define SHADIG046_EN773Aw(val)			_wr32(0x30021118,(UINT)((_rd32(0x30021118)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG047_EN773Ar				(ValSft_R00(_rd32(0x3002111c))&BitMask_10)
#define SHADIG047_EN773Aw(val)			_wr32(0x3002111c,(UINT)((_rd32(0x3002111c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG048_EN773Ar				(ValSft_R00(_rd32(0x30021120))&BitMask_10)
#define SHADIG048_EN773Aw(val)			_wr32(0x30021120,(UINT)((_rd32(0x30021120)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG049_EN773Ar				(ValSft_R00(_rd32(0x30021124))&BitMask_10)
#define SHADIG049_EN773Aw(val)			_wr32(0x30021124,(UINT)((_rd32(0x30021124)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04a_EN773Ar				(ValSft_R00(_rd32(0x30021128))&BitMask_10)
#define SHADIG04a_EN773Aw(val)			_wr32(0x30021128,(UINT)((_rd32(0x30021128)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04b_EN773Ar				(ValSft_R00(_rd32(0x3002112c))&BitMask_10)
#define SHADIG04b_EN773Aw(val)			_wr32(0x3002112c,(UINT)((_rd32(0x3002112c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04c_EN773Ar				(ValSft_R00(_rd32(0x30021130))&BitMask_10)
#define SHADIG04c_EN773Aw(val)			_wr32(0x30021130,(UINT)((_rd32(0x30021130)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04d_EN773Ar				(ValSft_R00(_rd32(0x30021134))&BitMask_10)
#define SHADIG04d_EN773Aw(val)			_wr32(0x30021134,(UINT)((_rd32(0x30021134)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04e_EN773Ar				(ValSft_R00(_rd32(0x30021138))&BitMask_10)
#define SHADIG04e_EN773Aw(val)			_wr32(0x30021138,(UINT)((_rd32(0x30021138)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG04f_EN773Ar				(ValSft_R00(_rd32(0x3002113c))&BitMask_10)
#define SHADIG04f_EN773Aw(val)			_wr32(0x3002113c,(UINT)((_rd32(0x3002113c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG050_EN773Ar				(ValSft_R00(_rd32(0x30021140))&BitMask_10)
#define SHADIG050_EN773Aw(val)			_wr32(0x30021140,(UINT)((_rd32(0x30021140)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG051_EN773Ar				(ValSft_R00(_rd32(0x30021144))&BitMask_10)
#define SHADIG051_EN773Aw(val)			_wr32(0x30021144,(UINT)((_rd32(0x30021144)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG052_EN773Ar				(ValSft_R00(_rd32(0x30021148))&BitMask_10)
#define SHADIG052_EN773Aw(val)			_wr32(0x30021148,(UINT)((_rd32(0x30021148)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG053_EN773Ar				(ValSft_R00(_rd32(0x3002114c))&BitMask_10)
#define SHADIG053_EN773Aw(val)			_wr32(0x3002114c,(UINT)((_rd32(0x3002114c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG054_EN773Ar				(ValSft_R00(_rd32(0x30021150))&BitMask_10)
#define SHADIG054_EN773Aw(val)			_wr32(0x30021150,(UINT)((_rd32(0x30021150)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG055_EN773Ar				(ValSft_R00(_rd32(0x30021154))&BitMask_10)
#define SHADIG055_EN773Aw(val)			_wr32(0x30021154,(UINT)((_rd32(0x30021154)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG056_EN773Ar				(ValSft_R00(_rd32(0x30021158))&BitMask_10)
#define SHADIG056_EN773Aw(val)			_wr32(0x30021158,(UINT)((_rd32(0x30021158)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG057_EN773Ar				(ValSft_R00(_rd32(0x3002115c))&BitMask_10)
#define SHADIG057_EN773Aw(val)			_wr32(0x3002115c,(UINT)((_rd32(0x3002115c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG058_EN773Ar				(ValSft_R00(_rd32(0x30021160))&BitMask_10)
#define SHADIG058_EN773Aw(val)			_wr32(0x30021160,(UINT)((_rd32(0x30021160)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG059_EN773Ar				(ValSft_R00(_rd32(0x30021164))&BitMask_10)
#define SHADIG059_EN773Aw(val)			_wr32(0x30021164,(UINT)((_rd32(0x30021164)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05a_EN773Ar				(ValSft_R00(_rd32(0x30021168))&BitMask_10)
#define SHADIG05a_EN773Aw(val)			_wr32(0x30021168,(UINT)((_rd32(0x30021168)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05b_EN773Ar				(ValSft_R00(_rd32(0x3002116c))&BitMask_10)
#define SHADIG05b_EN773Aw(val)			_wr32(0x3002116c,(UINT)((_rd32(0x3002116c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05c_EN773Ar				(ValSft_R00(_rd32(0x30021170))&BitMask_10)
#define SHADIG05c_EN773Aw(val)			_wr32(0x30021170,(UINT)((_rd32(0x30021170)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05d_EN773Ar				(ValSft_R00(_rd32(0x30021174))&BitMask_10)
#define SHADIG05d_EN773Aw(val)			_wr32(0x30021174,(UINT)((_rd32(0x30021174)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05e_EN773Ar				(ValSft_R00(_rd32(0x30021178))&BitMask_10)
#define SHADIG05e_EN773Aw(val)			_wr32(0x30021178,(UINT)((_rd32(0x30021178)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG05f_EN773Ar				(ValSft_R00(_rd32(0x3002117c))&BitMask_10)
#define SHADIG05f_EN773Aw(val)			_wr32(0x3002117c,(UINT)((_rd32(0x3002117c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG060_EN773Ar				(ValSft_R00(_rd32(0x30021180))&BitMask_10)
#define SHADIG060_EN773Aw(val)			_wr32(0x30021180,(UINT)((_rd32(0x30021180)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG061_EN773Ar				(ValSft_R00(_rd32(0x30021184))&BitMask_10)
#define SHADIG061_EN773Aw(val)			_wr32(0x30021184,(UINT)((_rd32(0x30021184)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG062_EN773Ar				(ValSft_R00(_rd32(0x30021188))&BitMask_10)
#define SHADIG062_EN773Aw(val)			_wr32(0x30021188,(UINT)((_rd32(0x30021188)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG063_EN773Ar				(ValSft_R00(_rd32(0x3002118c))&BitMask_10)
#define SHADIG063_EN773Aw(val)			_wr32(0x3002118c,(UINT)((_rd32(0x3002118c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG064_EN773Ar				(ValSft_R00(_rd32(0x30021190))&BitMask_10)
#define SHADIG064_EN773Aw(val)			_wr32(0x30021190,(UINT)((_rd32(0x30021190)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG065_EN773Ar				(ValSft_R00(_rd32(0x30021194))&BitMask_10)
#define SHADIG065_EN773Aw(val)			_wr32(0x30021194,(UINT)((_rd32(0x30021194)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG066_EN773Ar				(ValSft_R00(_rd32(0x30021198))&BitMask_10)
#define SHADIG066_EN773Aw(val)			_wr32(0x30021198,(UINT)((_rd32(0x30021198)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG067_EN773Ar				(ValSft_R00(_rd32(0x3002119c))&BitMask_10)
#define SHADIG067_EN773Aw(val)			_wr32(0x3002119c,(UINT)((_rd32(0x3002119c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG068_EN773Ar				(ValSft_R00(_rd32(0x300211a0))&BitMask_10)
#define SHADIG068_EN773Aw(val)			_wr32(0x300211a0,(UINT)((_rd32(0x300211a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG069_EN773Ar				(ValSft_R00(_rd32(0x300211a4))&BitMask_10)
#define SHADIG069_EN773Aw(val)			_wr32(0x300211a4,(UINT)((_rd32(0x300211a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06a_EN773Ar				(ValSft_R00(_rd32(0x300211a8))&BitMask_10)
#define SHADIG06a_EN773Aw(val)			_wr32(0x300211a8,(UINT)((_rd32(0x300211a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06b_EN773Ar				(ValSft_R00(_rd32(0x300211ac))&BitMask_10)
#define SHADIG06b_EN773Aw(val)			_wr32(0x300211ac,(UINT)((_rd32(0x300211ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06c_EN773Ar				(ValSft_R00(_rd32(0x300211b0))&BitMask_10)
#define SHADIG06c_EN773Aw(val)			_wr32(0x300211b0,(UINT)((_rd32(0x300211b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06d_EN773Ar				(ValSft_R00(_rd32(0x300211b4))&BitMask_10)
#define SHADIG06d_EN773Aw(val)			_wr32(0x300211b4,(UINT)((_rd32(0x300211b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06e_EN773Ar				(ValSft_R00(_rd32(0x300211b8))&BitMask_10)
#define SHADIG06e_EN773Aw(val)			_wr32(0x300211b8,(UINT)((_rd32(0x300211b8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG06f_EN773Ar				(ValSft_R00(_rd32(0x300211bc))&BitMask_10)
#define SHADIG06f_EN773Aw(val)			_wr32(0x300211bc,(UINT)((_rd32(0x300211bc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG070_EN773Ar				(ValSft_R00(_rd32(0x300211c0))&BitMask_10)
#define SHADIG070_EN773Aw(val)			_wr32(0x300211c0,(UINT)((_rd32(0x300211c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG071_EN773Ar				(ValSft_R00(_rd32(0x300211c4))&BitMask_10)
#define SHADIG071_EN773Aw(val)			_wr32(0x300211c4,(UINT)((_rd32(0x300211c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG072_EN773Ar				(ValSft_R00(_rd32(0x300211c8))&BitMask_10)
#define SHADIG072_EN773Aw(val)			_wr32(0x300211c8,(UINT)((_rd32(0x300211c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG073_EN773Ar				(ValSft_R00(_rd32(0x300211cc))&BitMask_10)
#define SHADIG073_EN773Aw(val)			_wr32(0x300211cc,(UINT)((_rd32(0x300211cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG074_EN773Ar				(ValSft_R00(_rd32(0x300211d0))&BitMask_10)
#define SHADIG074_EN773Aw(val)			_wr32(0x300211d0,(UINT)((_rd32(0x300211d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG075_EN773Ar				(ValSft_R00(_rd32(0x300211d4))&BitMask_10)
#define SHADIG075_EN773Aw(val)			_wr32(0x300211d4,(UINT)((_rd32(0x300211d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG076_EN773Ar				(ValSft_R00(_rd32(0x300211d8))&BitMask_10)
#define SHADIG076_EN773Aw(val)			_wr32(0x300211d8,(UINT)((_rd32(0x300211d8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG077_EN773Ar				(ValSft_R00(_rd32(0x300211dc))&BitMask_10)
#define SHADIG077_EN773Aw(val)			_wr32(0x300211dc,(UINT)((_rd32(0x300211dc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG078_EN773Ar				(ValSft_R00(_rd32(0x300211e0))&BitMask_10)
#define SHADIG078_EN773Aw(val)			_wr32(0x300211e0,(UINT)((_rd32(0x300211e0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG079_EN773Ar				(ValSft_R00(_rd32(0x300211e4))&BitMask_10)
#define SHADIG079_EN773Aw(val)			_wr32(0x300211e4,(UINT)((_rd32(0x300211e4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07a_EN773Ar				(ValSft_R00(_rd32(0x300211e8))&BitMask_10)
#define SHADIG07a_EN773Aw(val)			_wr32(0x300211e8,(UINT)((_rd32(0x300211e8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07b_EN773Ar				(ValSft_R00(_rd32(0x300211ec))&BitMask_10)
#define SHADIG07b_EN773Aw(val)			_wr32(0x300211ec,(UINT)((_rd32(0x300211ec)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07c_EN773Ar				(ValSft_R00(_rd32(0x300211f0))&BitMask_10)
#define SHADIG07c_EN773Aw(val)			_wr32(0x300211f0,(UINT)((_rd32(0x300211f0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07d_EN773Ar				(ValSft_R00(_rd32(0x300211f4))&BitMask_10)
#define SHADIG07d_EN773Aw(val)			_wr32(0x300211f4,(UINT)((_rd32(0x300211f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07e_EN773Ar				(ValSft_R00(_rd32(0x300211f8))&BitMask_10)
#define SHADIG07e_EN773Aw(val)			_wr32(0x300211f8,(UINT)((_rd32(0x300211f8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG07f_EN773Ar				(ValSft_R00(_rd32(0x300211fc))&BitMask_10)
#define SHADIG07f_EN773Aw(val)			_wr32(0x300211fc,(UINT)((_rd32(0x300211fc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG080_EN773Ar				(ValSft_R00(_rd32(0x30021200))&BitMask_10)
#define SHADIG080_EN773Aw(val)			_wr32(0x30021200,(UINT)((_rd32(0x30021200)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG081_EN773Ar				(ValSft_R00(_rd32(0x30021204))&BitMask_10)
#define SHADIG081_EN773Aw(val)			_wr32(0x30021204,(UINT)((_rd32(0x30021204)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG082_EN773Ar				(ValSft_R00(_rd32(0x30021208))&BitMask_10)
#define SHADIG082_EN773Aw(val)			_wr32(0x30021208,(UINT)((_rd32(0x30021208)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG083_EN773Ar				(ValSft_R00(_rd32(0x3002120c))&BitMask_10)
#define SHADIG083_EN773Aw(val)			_wr32(0x3002120c,(UINT)((_rd32(0x3002120c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG084_EN773Ar				(ValSft_R00(_rd32(0x30021210))&BitMask_10)
#define SHADIG084_EN773Aw(val)			_wr32(0x30021210,(UINT)((_rd32(0x30021210)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG085_EN773Ar				(ValSft_R00(_rd32(0x30021214))&BitMask_10)
#define SHADIG085_EN773Aw(val)			_wr32(0x30021214,(UINT)((_rd32(0x30021214)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG086_EN773Ar				(ValSft_R00(_rd32(0x30021218))&BitMask_10)
#define SHADIG086_EN773Aw(val)			_wr32(0x30021218,(UINT)((_rd32(0x30021218)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG087_EN773Ar				(ValSft_R00(_rd32(0x3002121c))&BitMask_10)
#define SHADIG087_EN773Aw(val)			_wr32(0x3002121c,(UINT)((_rd32(0x3002121c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG088_EN773Ar				(ValSft_R00(_rd32(0x30021220))&BitMask_10)
#define SHADIG088_EN773Aw(val)			_wr32(0x30021220,(UINT)((_rd32(0x30021220)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG089_EN773Ar				(ValSft_R00(_rd32(0x30021224))&BitMask_10)
#define SHADIG089_EN773Aw(val)			_wr32(0x30021224,(UINT)((_rd32(0x30021224)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08a_EN773Ar				(ValSft_R00(_rd32(0x30021228))&BitMask_10)
#define SHADIG08a_EN773Aw(val)			_wr32(0x30021228,(UINT)((_rd32(0x30021228)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08b_EN773Ar				(ValSft_R00(_rd32(0x3002122c))&BitMask_10)
#define SHADIG08b_EN773Aw(val)			_wr32(0x3002122c,(UINT)((_rd32(0x3002122c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08c_EN773Ar				(ValSft_R00(_rd32(0x30021230))&BitMask_10)
#define SHADIG08c_EN773Aw(val)			_wr32(0x30021230,(UINT)((_rd32(0x30021230)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08d_EN773Ar				(ValSft_R00(_rd32(0x30021234))&BitMask_10)
#define SHADIG08d_EN773Aw(val)			_wr32(0x30021234,(UINT)((_rd32(0x30021234)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08e_EN773Ar				(ValSft_R00(_rd32(0x30021238))&BitMask_10)
#define SHADIG08e_EN773Aw(val)			_wr32(0x30021238,(UINT)((_rd32(0x30021238)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG08f_EN773Ar				(ValSft_R00(_rd32(0x3002123c))&BitMask_10)
#define SHADIG08f_EN773Aw(val)			_wr32(0x3002123c,(UINT)((_rd32(0x3002123c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG090_EN773Ar				(ValSft_R00(_rd32(0x30021240))&BitMask_10)
#define SHADIG090_EN773Aw(val)			_wr32(0x30021240,(UINT)((_rd32(0x30021240)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG091_EN773Ar				(ValSft_R00(_rd32(0x30021244))&BitMask_10)
#define SHADIG091_EN773Aw(val)			_wr32(0x30021244,(UINT)((_rd32(0x30021244)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG092_EN773Ar				(ValSft_R00(_rd32(0x30021248))&BitMask_10)
#define SHADIG092_EN773Aw(val)			_wr32(0x30021248,(UINT)((_rd32(0x30021248)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG093_EN773Ar				(ValSft_R00(_rd32(0x3002124c))&BitMask_10)
#define SHADIG093_EN773Aw(val)			_wr32(0x3002124c,(UINT)((_rd32(0x3002124c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG094_EN773Ar				(ValSft_R00(_rd32(0x30021250))&BitMask_10)
#define SHADIG094_EN773Aw(val)			_wr32(0x30021250,(UINT)((_rd32(0x30021250)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG095_EN773Ar				(ValSft_R00(_rd32(0x30021254))&BitMask_10)
#define SHADIG095_EN773Aw(val)			_wr32(0x30021254,(UINT)((_rd32(0x30021254)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG096_EN773Ar				(ValSft_R00(_rd32(0x30021258))&BitMask_10)
#define SHADIG096_EN773Aw(val)			_wr32(0x30021258,(UINT)((_rd32(0x30021258)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG097_EN773Ar				(ValSft_R00(_rd32(0x3002125c))&BitMask_10)
#define SHADIG097_EN773Aw(val)			_wr32(0x3002125c,(UINT)((_rd32(0x3002125c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG098_EN773Ar				(ValSft_R00(_rd32(0x30021260))&BitMask_10)
#define SHADIG098_EN773Aw(val)			_wr32(0x30021260,(UINT)((_rd32(0x30021260)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG099_EN773Ar				(ValSft_R00(_rd32(0x30021264))&BitMask_10)
#define SHADIG099_EN773Aw(val)			_wr32(0x30021264,(UINT)((_rd32(0x30021264)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09a_EN773Ar				(ValSft_R00(_rd32(0x30021268))&BitMask_10)
#define SHADIG09a_EN773Aw(val)			_wr32(0x30021268,(UINT)((_rd32(0x30021268)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09b_EN773Ar				(ValSft_R00(_rd32(0x3002126c))&BitMask_10)
#define SHADIG09b_EN773Aw(val)			_wr32(0x3002126c,(UINT)((_rd32(0x3002126c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09c_EN773Ar				(ValSft_R00(_rd32(0x30021270))&BitMask_10)
#define SHADIG09c_EN773Aw(val)			_wr32(0x30021270,(UINT)((_rd32(0x30021270)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09d_EN773Ar				(ValSft_R00(_rd32(0x30021274))&BitMask_10)
#define SHADIG09d_EN773Aw(val)			_wr32(0x30021274,(UINT)((_rd32(0x30021274)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09e_EN773Ar				(ValSft_R00(_rd32(0x30021278))&BitMask_10)
#define SHADIG09e_EN773Aw(val)			_wr32(0x30021278,(UINT)((_rd32(0x30021278)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG09f_EN773Ar				(ValSft_R00(_rd32(0x3002127c))&BitMask_10)
#define SHADIG09f_EN773Aw(val)			_wr32(0x3002127c,(UINT)((_rd32(0x3002127c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a0_EN773Ar				(ValSft_R00(_rd32(0x30021280))&BitMask_10)
#define SHADIG0a0_EN773Aw(val)			_wr32(0x30021280,(UINT)((_rd32(0x30021280)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a1_EN773Ar				(ValSft_R00(_rd32(0x30021284))&BitMask_10)
#define SHADIG0a1_EN773Aw(val)			_wr32(0x30021284,(UINT)((_rd32(0x30021284)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a2_EN773Ar				(ValSft_R00(_rd32(0x30021288))&BitMask_10)
#define SHADIG0a2_EN773Aw(val)			_wr32(0x30021288,(UINT)((_rd32(0x30021288)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a3_EN773Ar				(ValSft_R00(_rd32(0x3002128c))&BitMask_10)
#define SHADIG0a3_EN773Aw(val)			_wr32(0x3002128c,(UINT)((_rd32(0x3002128c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a4_EN773Ar				(ValSft_R00(_rd32(0x30021290))&BitMask_10)
#define SHADIG0a4_EN773Aw(val)			_wr32(0x30021290,(UINT)((_rd32(0x30021290)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a5_EN773Ar				(ValSft_R00(_rd32(0x30021294))&BitMask_10)
#define SHADIG0a5_EN773Aw(val)			_wr32(0x30021294,(UINT)((_rd32(0x30021294)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a6_EN773Ar				(ValSft_R00(_rd32(0x30021298))&BitMask_10)
#define SHADIG0a6_EN773Aw(val)			_wr32(0x30021298,(UINT)((_rd32(0x30021298)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a7_EN773Ar				(ValSft_R00(_rd32(0x3002129c))&BitMask_10)
#define SHADIG0a7_EN773Aw(val)			_wr32(0x3002129c,(UINT)((_rd32(0x3002129c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a8_EN773Ar				(ValSft_R00(_rd32(0x300212a0))&BitMask_10)
#define SHADIG0a8_EN773Aw(val)			_wr32(0x300212a0,(UINT)((_rd32(0x300212a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0a9_EN773Ar				(ValSft_R00(_rd32(0x300212a4))&BitMask_10)
#define SHADIG0a9_EN773Aw(val)			_wr32(0x300212a4,(UINT)((_rd32(0x300212a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0aa_EN773Ar				(ValSft_R00(_rd32(0x300212a8))&BitMask_10)
#define SHADIG0aa_EN773Aw(val)			_wr32(0x300212a8,(UINT)((_rd32(0x300212a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ab_EN773Ar				(ValSft_R00(_rd32(0x300212ac))&BitMask_10)
#define SHADIG0ab_EN773Aw(val)			_wr32(0x300212ac,(UINT)((_rd32(0x300212ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ac_EN773Ar				(ValSft_R00(_rd32(0x300212b0))&BitMask_10)
#define SHADIG0ac_EN773Aw(val)			_wr32(0x300212b0,(UINT)((_rd32(0x300212b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ad_EN773Ar				(ValSft_R00(_rd32(0x300212b4))&BitMask_10)
#define SHADIG0ad_EN773Aw(val)			_wr32(0x300212b4,(UINT)((_rd32(0x300212b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ae_EN773Ar				(ValSft_R00(_rd32(0x300212b8))&BitMask_10)
#define SHADIG0ae_EN773Aw(val)			_wr32(0x300212b8,(UINT)((_rd32(0x300212b8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0af_EN773Ar				(ValSft_R00(_rd32(0x300212bc))&BitMask_10)
#define SHADIG0af_EN773Aw(val)			_wr32(0x300212bc,(UINT)((_rd32(0x300212bc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b0_EN773Ar				(ValSft_R00(_rd32(0x300212c0))&BitMask_10)
#define SHADIG0b0_EN773Aw(val)			_wr32(0x300212c0,(UINT)((_rd32(0x300212c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b1_EN773Ar				(ValSft_R00(_rd32(0x300212c4))&BitMask_10)
#define SHADIG0b1_EN773Aw(val)			_wr32(0x300212c4,(UINT)((_rd32(0x300212c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b2_EN773Ar				(ValSft_R00(_rd32(0x300212c8))&BitMask_10)
#define SHADIG0b2_EN773Aw(val)			_wr32(0x300212c8,(UINT)((_rd32(0x300212c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b3_EN773Ar				(ValSft_R00(_rd32(0x300212cc))&BitMask_10)
#define SHADIG0b3_EN773Aw(val)			_wr32(0x300212cc,(UINT)((_rd32(0x300212cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b4_EN773Ar				(ValSft_R00(_rd32(0x300212d0))&BitMask_10)
#define SHADIG0b4_EN773Aw(val)			_wr32(0x300212d0,(UINT)((_rd32(0x300212d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b5_EN773Ar				(ValSft_R00(_rd32(0x300212d4))&BitMask_10)
#define SHADIG0b5_EN773Aw(val)			_wr32(0x300212d4,(UINT)((_rd32(0x300212d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b6_EN773Ar				(ValSft_R00(_rd32(0x300212d8))&BitMask_10)
#define SHADIG0b6_EN773Aw(val)			_wr32(0x300212d8,(UINT)((_rd32(0x300212d8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b7_EN773Ar				(ValSft_R00(_rd32(0x300212dc))&BitMask_10)
#define SHADIG0b7_EN773Aw(val)			_wr32(0x300212dc,(UINT)((_rd32(0x300212dc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b8_EN773Ar				(ValSft_R00(_rd32(0x300212e0))&BitMask_10)
#define SHADIG0b8_EN773Aw(val)			_wr32(0x300212e0,(UINT)((_rd32(0x300212e0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0b9_EN773Ar				(ValSft_R00(_rd32(0x300212e4))&BitMask_10)
#define SHADIG0b9_EN773Aw(val)			_wr32(0x300212e4,(UINT)((_rd32(0x300212e4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ba_EN773Ar				(ValSft_R00(_rd32(0x300212e8))&BitMask_10)
#define SHADIG0ba_EN773Aw(val)			_wr32(0x300212e8,(UINT)((_rd32(0x300212e8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0bb_EN773Ar				(ValSft_R00(_rd32(0x300212ec))&BitMask_10)
#define SHADIG0bb_EN773Aw(val)			_wr32(0x300212ec,(UINT)((_rd32(0x300212ec)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0bc_EN773Ar				(ValSft_R00(_rd32(0x300212f0))&BitMask_10)
#define SHADIG0bc_EN773Aw(val)			_wr32(0x300212f0,(UINT)((_rd32(0x300212f0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0bd_EN773Ar				(ValSft_R00(_rd32(0x300212f4))&BitMask_10)
#define SHADIG0bd_EN773Aw(val)			_wr32(0x300212f4,(UINT)((_rd32(0x300212f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0be_EN773Ar				(ValSft_R00(_rd32(0x300212f8))&BitMask_10)
#define SHADIG0be_EN773Aw(val)			_wr32(0x300212f8,(UINT)((_rd32(0x300212f8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0bf_EN773Ar				(ValSft_R00(_rd32(0x300212fc))&BitMask_10)
#define SHADIG0bf_EN773Aw(val)			_wr32(0x300212fc,(UINT)((_rd32(0x300212fc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c0_EN773Ar				(ValSft_R00(_rd32(0x30021300))&BitMask_10)
#define SHADIG0c0_EN773Aw(val)			_wr32(0x30021300,(UINT)((_rd32(0x30021300)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c1_EN773Ar				(ValSft_R00(_rd32(0x30021304))&BitMask_10)
#define SHADIG0c1_EN773Aw(val)			_wr32(0x30021304,(UINT)((_rd32(0x30021304)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c2_EN773Ar				(ValSft_R00(_rd32(0x30021308))&BitMask_10)
#define SHADIG0c2_EN773Aw(val)			_wr32(0x30021308,(UINT)((_rd32(0x30021308)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c3_EN773Ar				(ValSft_R00(_rd32(0x3002130c))&BitMask_10)
#define SHADIG0c3_EN773Aw(val)			_wr32(0x3002130c,(UINT)((_rd32(0x3002130c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c4_EN773Ar				(ValSft_R00(_rd32(0x30021310))&BitMask_10)
#define SHADIG0c4_EN773Aw(val)			_wr32(0x30021310,(UINT)((_rd32(0x30021310)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c5_EN773Ar				(ValSft_R00(_rd32(0x30021314))&BitMask_10)
#define SHADIG0c5_EN773Aw(val)			_wr32(0x30021314,(UINT)((_rd32(0x30021314)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c6_EN773Ar				(ValSft_R00(_rd32(0x30021318))&BitMask_10)
#define SHADIG0c6_EN773Aw(val)			_wr32(0x30021318,(UINT)((_rd32(0x30021318)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c7_EN773Ar				(ValSft_R00(_rd32(0x3002131c))&BitMask_10)
#define SHADIG0c7_EN773Aw(val)			_wr32(0x3002131c,(UINT)((_rd32(0x3002131c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c8_EN773Ar				(ValSft_R00(_rd32(0x30021320))&BitMask_10)
#define SHADIG0c8_EN773Aw(val)			_wr32(0x30021320,(UINT)((_rd32(0x30021320)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0c9_EN773Ar				(ValSft_R00(_rd32(0x30021324))&BitMask_10)
#define SHADIG0c9_EN773Aw(val)			_wr32(0x30021324,(UINT)((_rd32(0x30021324)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ca_EN773Ar				(ValSft_R00(_rd32(0x30021328))&BitMask_10)
#define SHADIG0ca_EN773Aw(val)			_wr32(0x30021328,(UINT)((_rd32(0x30021328)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0cb_EN773Ar				(ValSft_R00(_rd32(0x3002132c))&BitMask_10)
#define SHADIG0cb_EN773Aw(val)			_wr32(0x3002132c,(UINT)((_rd32(0x3002132c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0cc_EN773Ar				(ValSft_R00(_rd32(0x30021330))&BitMask_10)
#define SHADIG0cc_EN773Aw(val)			_wr32(0x30021330,(UINT)((_rd32(0x30021330)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0cd_EN773Ar				(ValSft_R00(_rd32(0x30021334))&BitMask_10)
#define SHADIG0cd_EN773Aw(val)			_wr32(0x30021334,(UINT)((_rd32(0x30021334)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ce_EN773Ar				(ValSft_R00(_rd32(0x30021338))&BitMask_10)
#define SHADIG0ce_EN773Aw(val)			_wr32(0x30021338,(UINT)((_rd32(0x30021338)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0cf_EN773Ar				(ValSft_R00(_rd32(0x3002133c))&BitMask_10)
#define SHADIG0cf_EN773Aw(val)			_wr32(0x3002133c,(UINT)((_rd32(0x3002133c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d0_EN773Ar				(ValSft_R00(_rd32(0x30021340))&BitMask_10)
#define SHADIG0d0_EN773Aw(val)			_wr32(0x30021340,(UINT)((_rd32(0x30021340)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d1_EN773Ar				(ValSft_R00(_rd32(0x30021344))&BitMask_10)
#define SHADIG0d1_EN773Aw(val)			_wr32(0x30021344,(UINT)((_rd32(0x30021344)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d2_EN773Ar				(ValSft_R00(_rd32(0x30021348))&BitMask_10)
#define SHADIG0d2_EN773Aw(val)			_wr32(0x30021348,(UINT)((_rd32(0x30021348)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d3_EN773Ar				(ValSft_R00(_rd32(0x3002134c))&BitMask_10)
#define SHADIG0d3_EN773Aw(val)			_wr32(0x3002134c,(UINT)((_rd32(0x3002134c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d4_EN773Ar				(ValSft_R00(_rd32(0x30021350))&BitMask_10)
#define SHADIG0d4_EN773Aw(val)			_wr32(0x30021350,(UINT)((_rd32(0x30021350)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d5_EN773Ar				(ValSft_R00(_rd32(0x30021354))&BitMask_10)
#define SHADIG0d5_EN773Aw(val)			_wr32(0x30021354,(UINT)((_rd32(0x30021354)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d6_EN773Ar				(ValSft_R00(_rd32(0x30021358))&BitMask_10)
#define SHADIG0d6_EN773Aw(val)			_wr32(0x30021358,(UINT)((_rd32(0x30021358)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d7_EN773Ar				(ValSft_R00(_rd32(0x3002135c))&BitMask_10)
#define SHADIG0d7_EN773Aw(val)			_wr32(0x3002135c,(UINT)((_rd32(0x3002135c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d8_EN773Ar				(ValSft_R00(_rd32(0x30021360))&BitMask_10)
#define SHADIG0d8_EN773Aw(val)			_wr32(0x30021360,(UINT)((_rd32(0x30021360)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0d9_EN773Ar				(ValSft_R00(_rd32(0x30021364))&BitMask_10)
#define SHADIG0d9_EN773Aw(val)			_wr32(0x30021364,(UINT)((_rd32(0x30021364)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0da_EN773Ar				(ValSft_R00(_rd32(0x30021368))&BitMask_10)
#define SHADIG0da_EN773Aw(val)			_wr32(0x30021368,(UINT)((_rd32(0x30021368)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0db_EN773Ar				(ValSft_R00(_rd32(0x3002136c))&BitMask_10)
#define SHADIG0db_EN773Aw(val)			_wr32(0x3002136c,(UINT)((_rd32(0x3002136c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0dc_EN773Ar				(ValSft_R00(_rd32(0x30021370))&BitMask_10)
#define SHADIG0dc_EN773Aw(val)			_wr32(0x30021370,(UINT)((_rd32(0x30021370)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0dd_EN773Ar				(ValSft_R00(_rd32(0x30021374))&BitMask_10)
#define SHADIG0dd_EN773Aw(val)			_wr32(0x30021374,(UINT)((_rd32(0x30021374)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0de_EN773Ar				(ValSft_R00(_rd32(0x30021378))&BitMask_10)
#define SHADIG0de_EN773Aw(val)			_wr32(0x30021378,(UINT)((_rd32(0x30021378)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0df_EN773Ar				(ValSft_R00(_rd32(0x3002137c))&BitMask_10)
#define SHADIG0df_EN773Aw(val)			_wr32(0x3002137c,(UINT)((_rd32(0x3002137c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e0_EN773Ar				(ValSft_R00(_rd32(0x30021380))&BitMask_10)
#define SHADIG0e0_EN773Aw(val)			_wr32(0x30021380,(UINT)((_rd32(0x30021380)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e1_EN773Ar				(ValSft_R00(_rd32(0x30021384))&BitMask_10)
#define SHADIG0e1_EN773Aw(val)			_wr32(0x30021384,(UINT)((_rd32(0x30021384)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e2_EN773Ar				(ValSft_R00(_rd32(0x30021388))&BitMask_10)
#define SHADIG0e2_EN773Aw(val)			_wr32(0x30021388,(UINT)((_rd32(0x30021388)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e3_EN773Ar				(ValSft_R00(_rd32(0x3002138c))&BitMask_10)
#define SHADIG0e3_EN773Aw(val)			_wr32(0x3002138c,(UINT)((_rd32(0x3002138c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e4_EN773Ar				(ValSft_R00(_rd32(0x30021390))&BitMask_10)
#define SHADIG0e4_EN773Aw(val)			_wr32(0x30021390,(UINT)((_rd32(0x30021390)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e5_EN773Ar				(ValSft_R00(_rd32(0x30021394))&BitMask_10)
#define SHADIG0e5_EN773Aw(val)			_wr32(0x30021394,(UINT)((_rd32(0x30021394)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e6_EN773Ar				(ValSft_R00(_rd32(0x30021398))&BitMask_10)
#define SHADIG0e6_EN773Aw(val)			_wr32(0x30021398,(UINT)((_rd32(0x30021398)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e7_EN773Ar				(ValSft_R00(_rd32(0x3002139c))&BitMask_10)
#define SHADIG0e7_EN773Aw(val)			_wr32(0x3002139c,(UINT)((_rd32(0x3002139c)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e8_EN773Ar				(ValSft_R00(_rd32(0x300213a0))&BitMask_10)
#define SHADIG0e8_EN773Aw(val)			_wr32(0x300213a0,(UINT)((_rd32(0x300213a0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0e9_EN773Ar				(ValSft_R00(_rd32(0x300213a4))&BitMask_10)
#define SHADIG0e9_EN773Aw(val)			_wr32(0x300213a4,(UINT)((_rd32(0x300213a4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ea_EN773Ar				(ValSft_R00(_rd32(0x300213a8))&BitMask_10)
#define SHADIG0ea_EN773Aw(val)			_wr32(0x300213a8,(UINT)((_rd32(0x300213a8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0eb_EN773Ar				(ValSft_R00(_rd32(0x300213ac))&BitMask_10)
#define SHADIG0eb_EN773Aw(val)			_wr32(0x300213ac,(UINT)((_rd32(0x300213ac)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ec_EN773Ar				(ValSft_R00(_rd32(0x300213b0))&BitMask_10)
#define SHADIG0ec_EN773Aw(val)			_wr32(0x300213b0,(UINT)((_rd32(0x300213b0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ed_EN773Ar				(ValSft_R00(_rd32(0x300213b4))&BitMask_10)
#define SHADIG0ed_EN773Aw(val)			_wr32(0x300213b4,(UINT)((_rd32(0x300213b4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ee_EN773Ar				(ValSft_R00(_rd32(0x300213b8))&BitMask_10)
#define SHADIG0ee_EN773Aw(val)			_wr32(0x300213b8,(UINT)((_rd32(0x300213b8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ef_EN773Ar				(ValSft_R00(_rd32(0x300213bc))&BitMask_10)
#define SHADIG0ef_EN773Aw(val)			_wr32(0x300213bc,(UINT)((_rd32(0x300213bc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f0_EN773Ar				(ValSft_R00(_rd32(0x300213c0))&BitMask_10)
#define SHADIG0f0_EN773Aw(val)			_wr32(0x300213c0,(UINT)((_rd32(0x300213c0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f1_EN773Ar				(ValSft_R00(_rd32(0x300213c4))&BitMask_10)
#define SHADIG0f1_EN773Aw(val)			_wr32(0x300213c4,(UINT)((_rd32(0x300213c4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f2_EN773Ar				(ValSft_R00(_rd32(0x300213c8))&BitMask_10)
#define SHADIG0f2_EN773Aw(val)			_wr32(0x300213c8,(UINT)((_rd32(0x300213c8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f3_EN773Ar				(ValSft_R00(_rd32(0x300213cc))&BitMask_10)
#define SHADIG0f3_EN773Aw(val)			_wr32(0x300213cc,(UINT)((_rd32(0x300213cc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f4_EN773Ar				(ValSft_R00(_rd32(0x300213d0))&BitMask_10)
#define SHADIG0f4_EN773Aw(val)			_wr32(0x300213d0,(UINT)((_rd32(0x300213d0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f5_EN773Ar				(ValSft_R00(_rd32(0x300213d4))&BitMask_10)
#define SHADIG0f5_EN773Aw(val)			_wr32(0x300213d4,(UINT)((_rd32(0x300213d4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f6_EN773Ar				(ValSft_R00(_rd32(0x300213d8))&BitMask_10)
#define SHADIG0f6_EN773Aw(val)			_wr32(0x300213d8,(UINT)((_rd32(0x300213d8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f7_EN773Ar				(ValSft_R00(_rd32(0x300213dc))&BitMask_10)
#define SHADIG0f7_EN773Aw(val)			_wr32(0x300213dc,(UINT)((_rd32(0x300213dc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f8_EN773Ar				(ValSft_R00(_rd32(0x300213e0))&BitMask_10)
#define SHADIG0f8_EN773Aw(val)			_wr32(0x300213e0,(UINT)((_rd32(0x300213e0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0f9_EN773Ar				(ValSft_R00(_rd32(0x300213e4))&BitMask_10)
#define SHADIG0f9_EN773Aw(val)			_wr32(0x300213e4,(UINT)((_rd32(0x300213e4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0fa_EN773Ar				(ValSft_R00(_rd32(0x300213e8))&BitMask_10)
#define SHADIG0fa_EN773Aw(val)			_wr32(0x300213e8,(UINT)((_rd32(0x300213e8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0fb_EN773Ar				(ValSft_R00(_rd32(0x300213ec))&BitMask_10)
#define SHADIG0fb_EN773Aw(val)			_wr32(0x300213ec,(UINT)((_rd32(0x300213ec)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0fc_EN773Ar				(ValSft_R00(_rd32(0x300213f0))&BitMask_10)
#define SHADIG0fc_EN773Aw(val)			_wr32(0x300213f0,(UINT)((_rd32(0x300213f0)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0fd_EN773Ar				(ValSft_R00(_rd32(0x300213f4))&BitMask_10)
#define SHADIG0fd_EN773Aw(val)			_wr32(0x300213f4,(UINT)((_rd32(0x300213f4)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0fe_EN773Ar				(ValSft_R00(_rd32(0x300213f8))&BitMask_10)
#define SHADIG0fe_EN773Aw(val)			_wr32(0x300213f8,(UINT)((_rd32(0x300213f8)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHADIG0ff_EN773Ar				(ValSft_R00(_rd32(0x300213fc))&BitMask_10)
#define SHADIG0ff_EN773Aw(val)			_wr32(0x300213fc,(UINT)((_rd32(0x300213fc)&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define DEFECT000_EN773Ar				(ValSft_R00(_rd32(0x30021400))&BitMask_32)
#define DEFECT000_EN773Aw(val)			_wr32(0x30021400,(UINT)((_rd32(0x30021400)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT001_EN773Ar				(ValSft_R00(_rd32(0x30021404))&BitMask_32)
#define DEFECT001_EN773Aw(val)			_wr32(0x30021404,(UINT)((_rd32(0x30021404)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT002_EN773Ar				(ValSft_R00(_rd32(0x30021408))&BitMask_32)
#define DEFECT002_EN773Aw(val)			_wr32(0x30021408,(UINT)((_rd32(0x30021408)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT003_EN773Ar				(ValSft_R00(_rd32(0x3002140c))&BitMask_32)
#define DEFECT003_EN773Aw(val)			_wr32(0x3002140c,(UINT)((_rd32(0x3002140c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT004_EN773Ar				(ValSft_R00(_rd32(0x30021410))&BitMask_32)
#define DEFECT004_EN773Aw(val)			_wr32(0x30021410,(UINT)((_rd32(0x30021410)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT005_EN773Ar				(ValSft_R00(_rd32(0x30021414))&BitMask_32)
#define DEFECT005_EN773Aw(val)			_wr32(0x30021414,(UINT)((_rd32(0x30021414)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT006_EN773Ar				(ValSft_R00(_rd32(0x30021418))&BitMask_32)
#define DEFECT006_EN773Aw(val)			_wr32(0x30021418,(UINT)((_rd32(0x30021418)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT007_EN773Ar				(ValSft_R00(_rd32(0x3002141c))&BitMask_32)
#define DEFECT007_EN773Aw(val)			_wr32(0x3002141c,(UINT)((_rd32(0x3002141c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT008_EN773Ar				(ValSft_R00(_rd32(0x30021420))&BitMask_32)
#define DEFECT008_EN773Aw(val)			_wr32(0x30021420,(UINT)((_rd32(0x30021420)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT009_EN773Ar				(ValSft_R00(_rd32(0x30021424))&BitMask_32)
#define DEFECT009_EN773Aw(val)			_wr32(0x30021424,(UINT)((_rd32(0x30021424)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00a_EN773Ar				(ValSft_R00(_rd32(0x30021428))&BitMask_32)
#define DEFECT00a_EN773Aw(val)			_wr32(0x30021428,(UINT)((_rd32(0x30021428)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00b_EN773Ar				(ValSft_R00(_rd32(0x3002142c))&BitMask_32)
#define DEFECT00b_EN773Aw(val)			_wr32(0x3002142c,(UINT)((_rd32(0x3002142c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00c_EN773Ar				(ValSft_R00(_rd32(0x30021430))&BitMask_32)
#define DEFECT00c_EN773Aw(val)			_wr32(0x30021430,(UINT)((_rd32(0x30021430)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00d_EN773Ar				(ValSft_R00(_rd32(0x30021434))&BitMask_32)
#define DEFECT00d_EN773Aw(val)			_wr32(0x30021434,(UINT)((_rd32(0x30021434)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00e_EN773Ar				(ValSft_R00(_rd32(0x30021438))&BitMask_32)
#define DEFECT00e_EN773Aw(val)			_wr32(0x30021438,(UINT)((_rd32(0x30021438)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT00f_EN773Ar				(ValSft_R00(_rd32(0x3002143c))&BitMask_32)
#define DEFECT00f_EN773Aw(val)			_wr32(0x3002143c,(UINT)((_rd32(0x3002143c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT010_EN773Ar				(ValSft_R00(_rd32(0x30021440))&BitMask_32)
#define DEFECT010_EN773Aw(val)			_wr32(0x30021440,(UINT)((_rd32(0x30021440)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT011_EN773Ar				(ValSft_R00(_rd32(0x30021444))&BitMask_32)
#define DEFECT011_EN773Aw(val)			_wr32(0x30021444,(UINT)((_rd32(0x30021444)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT012_EN773Ar				(ValSft_R00(_rd32(0x30021448))&BitMask_32)
#define DEFECT012_EN773Aw(val)			_wr32(0x30021448,(UINT)((_rd32(0x30021448)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT013_EN773Ar				(ValSft_R00(_rd32(0x3002144c))&BitMask_32)
#define DEFECT013_EN773Aw(val)			_wr32(0x3002144c,(UINT)((_rd32(0x3002144c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT014_EN773Ar				(ValSft_R00(_rd32(0x30021450))&BitMask_32)
#define DEFECT014_EN773Aw(val)			_wr32(0x30021450,(UINT)((_rd32(0x30021450)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT015_EN773Ar				(ValSft_R00(_rd32(0x30021454))&BitMask_32)
#define DEFECT015_EN773Aw(val)			_wr32(0x30021454,(UINT)((_rd32(0x30021454)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT016_EN773Ar				(ValSft_R00(_rd32(0x30021458))&BitMask_32)
#define DEFECT016_EN773Aw(val)			_wr32(0x30021458,(UINT)((_rd32(0x30021458)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT017_EN773Ar				(ValSft_R00(_rd32(0x3002145c))&BitMask_32)
#define DEFECT017_EN773Aw(val)			_wr32(0x3002145c,(UINT)((_rd32(0x3002145c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT018_EN773Ar				(ValSft_R00(_rd32(0x30021460))&BitMask_32)
#define DEFECT018_EN773Aw(val)			_wr32(0x30021460,(UINT)((_rd32(0x30021460)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT019_EN773Ar				(ValSft_R00(_rd32(0x30021464))&BitMask_32)
#define DEFECT019_EN773Aw(val)			_wr32(0x30021464,(UINT)((_rd32(0x30021464)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01a_EN773Ar				(ValSft_R00(_rd32(0x30021468))&BitMask_32)
#define DEFECT01a_EN773Aw(val)			_wr32(0x30021468,(UINT)((_rd32(0x30021468)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01b_EN773Ar				(ValSft_R00(_rd32(0x3002146c))&BitMask_32)
#define DEFECT01b_EN773Aw(val)			_wr32(0x3002146c,(UINT)((_rd32(0x3002146c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01c_EN773Ar				(ValSft_R00(_rd32(0x30021470))&BitMask_32)
#define DEFECT01c_EN773Aw(val)			_wr32(0x30021470,(UINT)((_rd32(0x30021470)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01d_EN773Ar				(ValSft_R00(_rd32(0x30021474))&BitMask_32)
#define DEFECT01d_EN773Aw(val)			_wr32(0x30021474,(UINT)((_rd32(0x30021474)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01e_EN773Ar				(ValSft_R00(_rd32(0x30021478))&BitMask_32)
#define DEFECT01e_EN773Aw(val)			_wr32(0x30021478,(UINT)((_rd32(0x30021478)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT01f_EN773Ar				(ValSft_R00(_rd32(0x3002147c))&BitMask_32)
#define DEFECT01f_EN773Aw(val)			_wr32(0x3002147c,(UINT)((_rd32(0x3002147c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT020_EN773Ar				(ValSft_R00(_rd32(0x30021480))&BitMask_32)
#define DEFECT020_EN773Aw(val)			_wr32(0x30021480,(UINT)((_rd32(0x30021480)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT021_EN773Ar				(ValSft_R00(_rd32(0x30021484))&BitMask_32)
#define DEFECT021_EN773Aw(val)			_wr32(0x30021484,(UINT)((_rd32(0x30021484)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT022_EN773Ar				(ValSft_R00(_rd32(0x30021488))&BitMask_32)
#define DEFECT022_EN773Aw(val)			_wr32(0x30021488,(UINT)((_rd32(0x30021488)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT023_EN773Ar				(ValSft_R00(_rd32(0x3002148c))&BitMask_32)
#define DEFECT023_EN773Aw(val)			_wr32(0x3002148c,(UINT)((_rd32(0x3002148c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT024_EN773Ar				(ValSft_R00(_rd32(0x30021490))&BitMask_32)
#define DEFECT024_EN773Aw(val)			_wr32(0x30021490,(UINT)((_rd32(0x30021490)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT025_EN773Ar				(ValSft_R00(_rd32(0x30021494))&BitMask_32)
#define DEFECT025_EN773Aw(val)			_wr32(0x30021494,(UINT)((_rd32(0x30021494)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT026_EN773Ar				(ValSft_R00(_rd32(0x30021498))&BitMask_32)
#define DEFECT026_EN773Aw(val)			_wr32(0x30021498,(UINT)((_rd32(0x30021498)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT027_EN773Ar				(ValSft_R00(_rd32(0x3002149c))&BitMask_32)
#define DEFECT027_EN773Aw(val)			_wr32(0x3002149c,(UINT)((_rd32(0x3002149c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT028_EN773Ar				(ValSft_R00(_rd32(0x300214a0))&BitMask_32)
#define DEFECT028_EN773Aw(val)			_wr32(0x300214a0,(UINT)((_rd32(0x300214a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT029_EN773Ar				(ValSft_R00(_rd32(0x300214a4))&BitMask_32)
#define DEFECT029_EN773Aw(val)			_wr32(0x300214a4,(UINT)((_rd32(0x300214a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02a_EN773Ar				(ValSft_R00(_rd32(0x300214a8))&BitMask_32)
#define DEFECT02a_EN773Aw(val)			_wr32(0x300214a8,(UINT)((_rd32(0x300214a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02b_EN773Ar				(ValSft_R00(_rd32(0x300214ac))&BitMask_32)
#define DEFECT02b_EN773Aw(val)			_wr32(0x300214ac,(UINT)((_rd32(0x300214ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02c_EN773Ar				(ValSft_R00(_rd32(0x300214b0))&BitMask_32)
#define DEFECT02c_EN773Aw(val)			_wr32(0x300214b0,(UINT)((_rd32(0x300214b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02d_EN773Ar				(ValSft_R00(_rd32(0x300214b4))&BitMask_32)
#define DEFECT02d_EN773Aw(val)			_wr32(0x300214b4,(UINT)((_rd32(0x300214b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02e_EN773Ar				(ValSft_R00(_rd32(0x300214b8))&BitMask_32)
#define DEFECT02e_EN773Aw(val)			_wr32(0x300214b8,(UINT)((_rd32(0x300214b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT02f_EN773Ar				(ValSft_R00(_rd32(0x300214bc))&BitMask_32)
#define DEFECT02f_EN773Aw(val)			_wr32(0x300214bc,(UINT)((_rd32(0x300214bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT030_EN773Ar				(ValSft_R00(_rd32(0x300214c0))&BitMask_32)
#define DEFECT030_EN773Aw(val)			_wr32(0x300214c0,(UINT)((_rd32(0x300214c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT031_EN773Ar				(ValSft_R00(_rd32(0x300214c4))&BitMask_32)
#define DEFECT031_EN773Aw(val)			_wr32(0x300214c4,(UINT)((_rd32(0x300214c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT032_EN773Ar				(ValSft_R00(_rd32(0x300214c8))&BitMask_32)
#define DEFECT032_EN773Aw(val)			_wr32(0x300214c8,(UINT)((_rd32(0x300214c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT033_EN773Ar				(ValSft_R00(_rd32(0x300214cc))&BitMask_32)
#define DEFECT033_EN773Aw(val)			_wr32(0x300214cc,(UINT)((_rd32(0x300214cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT034_EN773Ar				(ValSft_R00(_rd32(0x300214d0))&BitMask_32)
#define DEFECT034_EN773Aw(val)			_wr32(0x300214d0,(UINT)((_rd32(0x300214d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT035_EN773Ar				(ValSft_R00(_rd32(0x300214d4))&BitMask_32)
#define DEFECT035_EN773Aw(val)			_wr32(0x300214d4,(UINT)((_rd32(0x300214d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT036_EN773Ar				(ValSft_R00(_rd32(0x300214d8))&BitMask_32)
#define DEFECT036_EN773Aw(val)			_wr32(0x300214d8,(UINT)((_rd32(0x300214d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT037_EN773Ar				(ValSft_R00(_rd32(0x300214dc))&BitMask_32)
#define DEFECT037_EN773Aw(val)			_wr32(0x300214dc,(UINT)((_rd32(0x300214dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT038_EN773Ar				(ValSft_R00(_rd32(0x300214e0))&BitMask_32)
#define DEFECT038_EN773Aw(val)			_wr32(0x300214e0,(UINT)((_rd32(0x300214e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT039_EN773Ar				(ValSft_R00(_rd32(0x300214e4))&BitMask_32)
#define DEFECT039_EN773Aw(val)			_wr32(0x300214e4,(UINT)((_rd32(0x300214e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03a_EN773Ar				(ValSft_R00(_rd32(0x300214e8))&BitMask_32)
#define DEFECT03a_EN773Aw(val)			_wr32(0x300214e8,(UINT)((_rd32(0x300214e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03b_EN773Ar				(ValSft_R00(_rd32(0x300214ec))&BitMask_32)
#define DEFECT03b_EN773Aw(val)			_wr32(0x300214ec,(UINT)((_rd32(0x300214ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03c_EN773Ar				(ValSft_R00(_rd32(0x300214f0))&BitMask_32)
#define DEFECT03c_EN773Aw(val)			_wr32(0x300214f0,(UINT)((_rd32(0x300214f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03d_EN773Ar				(ValSft_R00(_rd32(0x300214f4))&BitMask_32)
#define DEFECT03d_EN773Aw(val)			_wr32(0x300214f4,(UINT)((_rd32(0x300214f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03e_EN773Ar				(ValSft_R00(_rd32(0x300214f8))&BitMask_32)
#define DEFECT03e_EN773Aw(val)			_wr32(0x300214f8,(UINT)((_rd32(0x300214f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT03f_EN773Ar				(ValSft_R00(_rd32(0x300214fc))&BitMask_32)
#define DEFECT03f_EN773Aw(val)			_wr32(0x300214fc,(UINT)((_rd32(0x300214fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT040_EN773Ar				(ValSft_R00(_rd32(0x30021500))&BitMask_32)
#define DEFECT040_EN773Aw(val)			_wr32(0x30021500,(UINT)((_rd32(0x30021500)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT041_EN773Ar				(ValSft_R00(_rd32(0x30021504))&BitMask_32)
#define DEFECT041_EN773Aw(val)			_wr32(0x30021504,(UINT)((_rd32(0x30021504)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT042_EN773Ar				(ValSft_R00(_rd32(0x30021508))&BitMask_32)
#define DEFECT042_EN773Aw(val)			_wr32(0x30021508,(UINT)((_rd32(0x30021508)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT043_EN773Ar				(ValSft_R00(_rd32(0x3002150c))&BitMask_32)
#define DEFECT043_EN773Aw(val)			_wr32(0x3002150c,(UINT)((_rd32(0x3002150c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT044_EN773Ar				(ValSft_R00(_rd32(0x30021510))&BitMask_32)
#define DEFECT044_EN773Aw(val)			_wr32(0x30021510,(UINT)((_rd32(0x30021510)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT045_EN773Ar				(ValSft_R00(_rd32(0x30021514))&BitMask_32)
#define DEFECT045_EN773Aw(val)			_wr32(0x30021514,(UINT)((_rd32(0x30021514)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT046_EN773Ar				(ValSft_R00(_rd32(0x30021518))&BitMask_32)
#define DEFECT046_EN773Aw(val)			_wr32(0x30021518,(UINT)((_rd32(0x30021518)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT047_EN773Ar				(ValSft_R00(_rd32(0x3002151c))&BitMask_32)
#define DEFECT047_EN773Aw(val)			_wr32(0x3002151c,(UINT)((_rd32(0x3002151c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT048_EN773Ar				(ValSft_R00(_rd32(0x30021520))&BitMask_32)
#define DEFECT048_EN773Aw(val)			_wr32(0x30021520,(UINT)((_rd32(0x30021520)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT049_EN773Ar				(ValSft_R00(_rd32(0x30021524))&BitMask_32)
#define DEFECT049_EN773Aw(val)			_wr32(0x30021524,(UINT)((_rd32(0x30021524)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04a_EN773Ar				(ValSft_R00(_rd32(0x30021528))&BitMask_32)
#define DEFECT04a_EN773Aw(val)			_wr32(0x30021528,(UINT)((_rd32(0x30021528)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04b_EN773Ar				(ValSft_R00(_rd32(0x3002152c))&BitMask_32)
#define DEFECT04b_EN773Aw(val)			_wr32(0x3002152c,(UINT)((_rd32(0x3002152c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04c_EN773Ar				(ValSft_R00(_rd32(0x30021530))&BitMask_32)
#define DEFECT04c_EN773Aw(val)			_wr32(0x30021530,(UINT)((_rd32(0x30021530)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04d_EN773Ar				(ValSft_R00(_rd32(0x30021534))&BitMask_32)
#define DEFECT04d_EN773Aw(val)			_wr32(0x30021534,(UINT)((_rd32(0x30021534)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04e_EN773Ar				(ValSft_R00(_rd32(0x30021538))&BitMask_32)
#define DEFECT04e_EN773Aw(val)			_wr32(0x30021538,(UINT)((_rd32(0x30021538)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT04f_EN773Ar				(ValSft_R00(_rd32(0x3002153c))&BitMask_32)
#define DEFECT04f_EN773Aw(val)			_wr32(0x3002153c,(UINT)((_rd32(0x3002153c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT050_EN773Ar				(ValSft_R00(_rd32(0x30021540))&BitMask_32)
#define DEFECT050_EN773Aw(val)			_wr32(0x30021540,(UINT)((_rd32(0x30021540)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT051_EN773Ar				(ValSft_R00(_rd32(0x30021544))&BitMask_32)
#define DEFECT051_EN773Aw(val)			_wr32(0x30021544,(UINT)((_rd32(0x30021544)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT052_EN773Ar				(ValSft_R00(_rd32(0x30021548))&BitMask_32)
#define DEFECT052_EN773Aw(val)			_wr32(0x30021548,(UINT)((_rd32(0x30021548)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT053_EN773Ar				(ValSft_R00(_rd32(0x3002154c))&BitMask_32)
#define DEFECT053_EN773Aw(val)			_wr32(0x3002154c,(UINT)((_rd32(0x3002154c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT054_EN773Ar				(ValSft_R00(_rd32(0x30021550))&BitMask_32)
#define DEFECT054_EN773Aw(val)			_wr32(0x30021550,(UINT)((_rd32(0x30021550)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT055_EN773Ar				(ValSft_R00(_rd32(0x30021554))&BitMask_32)
#define DEFECT055_EN773Aw(val)			_wr32(0x30021554,(UINT)((_rd32(0x30021554)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT056_EN773Ar				(ValSft_R00(_rd32(0x30021558))&BitMask_32)
#define DEFECT056_EN773Aw(val)			_wr32(0x30021558,(UINT)((_rd32(0x30021558)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT057_EN773Ar				(ValSft_R00(_rd32(0x3002155c))&BitMask_32)
#define DEFECT057_EN773Aw(val)			_wr32(0x3002155c,(UINT)((_rd32(0x3002155c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT058_EN773Ar				(ValSft_R00(_rd32(0x30021560))&BitMask_32)
#define DEFECT058_EN773Aw(val)			_wr32(0x30021560,(UINT)((_rd32(0x30021560)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT059_EN773Ar				(ValSft_R00(_rd32(0x30021564))&BitMask_32)
#define DEFECT059_EN773Aw(val)			_wr32(0x30021564,(UINT)((_rd32(0x30021564)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05a_EN773Ar				(ValSft_R00(_rd32(0x30021568))&BitMask_32)
#define DEFECT05a_EN773Aw(val)			_wr32(0x30021568,(UINT)((_rd32(0x30021568)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05b_EN773Ar				(ValSft_R00(_rd32(0x3002156c))&BitMask_32)
#define DEFECT05b_EN773Aw(val)			_wr32(0x3002156c,(UINT)((_rd32(0x3002156c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05c_EN773Ar				(ValSft_R00(_rd32(0x30021570))&BitMask_32)
#define DEFECT05c_EN773Aw(val)			_wr32(0x30021570,(UINT)((_rd32(0x30021570)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05d_EN773Ar				(ValSft_R00(_rd32(0x30021574))&BitMask_32)
#define DEFECT05d_EN773Aw(val)			_wr32(0x30021574,(UINT)((_rd32(0x30021574)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05e_EN773Ar				(ValSft_R00(_rd32(0x30021578))&BitMask_32)
#define DEFECT05e_EN773Aw(val)			_wr32(0x30021578,(UINT)((_rd32(0x30021578)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT05f_EN773Ar				(ValSft_R00(_rd32(0x3002157c))&BitMask_32)
#define DEFECT05f_EN773Aw(val)			_wr32(0x3002157c,(UINT)((_rd32(0x3002157c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT060_EN773Ar				(ValSft_R00(_rd32(0x30021580))&BitMask_32)
#define DEFECT060_EN773Aw(val)			_wr32(0x30021580,(UINT)((_rd32(0x30021580)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT061_EN773Ar				(ValSft_R00(_rd32(0x30021584))&BitMask_32)
#define DEFECT061_EN773Aw(val)			_wr32(0x30021584,(UINT)((_rd32(0x30021584)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT062_EN773Ar				(ValSft_R00(_rd32(0x30021588))&BitMask_32)
#define DEFECT062_EN773Aw(val)			_wr32(0x30021588,(UINT)((_rd32(0x30021588)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT063_EN773Ar				(ValSft_R00(_rd32(0x3002158c))&BitMask_32)
#define DEFECT063_EN773Aw(val)			_wr32(0x3002158c,(UINT)((_rd32(0x3002158c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT064_EN773Ar				(ValSft_R00(_rd32(0x30021590))&BitMask_32)
#define DEFECT064_EN773Aw(val)			_wr32(0x30021590,(UINT)((_rd32(0x30021590)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT065_EN773Ar				(ValSft_R00(_rd32(0x30021594))&BitMask_32)
#define DEFECT065_EN773Aw(val)			_wr32(0x30021594,(UINT)((_rd32(0x30021594)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT066_EN773Ar				(ValSft_R00(_rd32(0x30021598))&BitMask_32)
#define DEFECT066_EN773Aw(val)			_wr32(0x30021598,(UINT)((_rd32(0x30021598)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT067_EN773Ar				(ValSft_R00(_rd32(0x3002159c))&BitMask_32)
#define DEFECT067_EN773Aw(val)			_wr32(0x3002159c,(UINT)((_rd32(0x3002159c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT068_EN773Ar				(ValSft_R00(_rd32(0x300215a0))&BitMask_32)
#define DEFECT068_EN773Aw(val)			_wr32(0x300215a0,(UINT)((_rd32(0x300215a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT069_EN773Ar				(ValSft_R00(_rd32(0x300215a4))&BitMask_32)
#define DEFECT069_EN773Aw(val)			_wr32(0x300215a4,(UINT)((_rd32(0x300215a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06a_EN773Ar				(ValSft_R00(_rd32(0x300215a8))&BitMask_32)
#define DEFECT06a_EN773Aw(val)			_wr32(0x300215a8,(UINT)((_rd32(0x300215a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06b_EN773Ar				(ValSft_R00(_rd32(0x300215ac))&BitMask_32)
#define DEFECT06b_EN773Aw(val)			_wr32(0x300215ac,(UINT)((_rd32(0x300215ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06c_EN773Ar				(ValSft_R00(_rd32(0x300215b0))&BitMask_32)
#define DEFECT06c_EN773Aw(val)			_wr32(0x300215b0,(UINT)((_rd32(0x300215b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06d_EN773Ar				(ValSft_R00(_rd32(0x300215b4))&BitMask_32)
#define DEFECT06d_EN773Aw(val)			_wr32(0x300215b4,(UINT)((_rd32(0x300215b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06e_EN773Ar				(ValSft_R00(_rd32(0x300215b8))&BitMask_32)
#define DEFECT06e_EN773Aw(val)			_wr32(0x300215b8,(UINT)((_rd32(0x300215b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT06f_EN773Ar				(ValSft_R00(_rd32(0x300215bc))&BitMask_32)
#define DEFECT06f_EN773Aw(val)			_wr32(0x300215bc,(UINT)((_rd32(0x300215bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT070_EN773Ar				(ValSft_R00(_rd32(0x300215c0))&BitMask_32)
#define DEFECT070_EN773Aw(val)			_wr32(0x300215c0,(UINT)((_rd32(0x300215c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT071_EN773Ar				(ValSft_R00(_rd32(0x300215c4))&BitMask_32)
#define DEFECT071_EN773Aw(val)			_wr32(0x300215c4,(UINT)((_rd32(0x300215c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT072_EN773Ar				(ValSft_R00(_rd32(0x300215c8))&BitMask_32)
#define DEFECT072_EN773Aw(val)			_wr32(0x300215c8,(UINT)((_rd32(0x300215c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT073_EN773Ar				(ValSft_R00(_rd32(0x300215cc))&BitMask_32)
#define DEFECT073_EN773Aw(val)			_wr32(0x300215cc,(UINT)((_rd32(0x300215cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT074_EN773Ar				(ValSft_R00(_rd32(0x300215d0))&BitMask_32)
#define DEFECT074_EN773Aw(val)			_wr32(0x300215d0,(UINT)((_rd32(0x300215d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT075_EN773Ar				(ValSft_R00(_rd32(0x300215d4))&BitMask_32)
#define DEFECT075_EN773Aw(val)			_wr32(0x300215d4,(UINT)((_rd32(0x300215d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT076_EN773Ar				(ValSft_R00(_rd32(0x300215d8))&BitMask_32)
#define DEFECT076_EN773Aw(val)			_wr32(0x300215d8,(UINT)((_rd32(0x300215d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT077_EN773Ar				(ValSft_R00(_rd32(0x300215dc))&BitMask_32)
#define DEFECT077_EN773Aw(val)			_wr32(0x300215dc,(UINT)((_rd32(0x300215dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT078_EN773Ar				(ValSft_R00(_rd32(0x300215e0))&BitMask_32)
#define DEFECT078_EN773Aw(val)			_wr32(0x300215e0,(UINT)((_rd32(0x300215e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT079_EN773Ar				(ValSft_R00(_rd32(0x300215e4))&BitMask_32)
#define DEFECT079_EN773Aw(val)			_wr32(0x300215e4,(UINT)((_rd32(0x300215e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07a_EN773Ar				(ValSft_R00(_rd32(0x300215e8))&BitMask_32)
#define DEFECT07a_EN773Aw(val)			_wr32(0x300215e8,(UINT)((_rd32(0x300215e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07b_EN773Ar				(ValSft_R00(_rd32(0x300215ec))&BitMask_32)
#define DEFECT07b_EN773Aw(val)			_wr32(0x300215ec,(UINT)((_rd32(0x300215ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07c_EN773Ar				(ValSft_R00(_rd32(0x300215f0))&BitMask_32)
#define DEFECT07c_EN773Aw(val)			_wr32(0x300215f0,(UINT)((_rd32(0x300215f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07d_EN773Ar				(ValSft_R00(_rd32(0x300215f4))&BitMask_32)
#define DEFECT07d_EN773Aw(val)			_wr32(0x300215f4,(UINT)((_rd32(0x300215f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07e_EN773Ar				(ValSft_R00(_rd32(0x300215f8))&BitMask_32)
#define DEFECT07e_EN773Aw(val)			_wr32(0x300215f8,(UINT)((_rd32(0x300215f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT07f_EN773Ar				(ValSft_R00(_rd32(0x300215fc))&BitMask_32)
#define DEFECT07f_EN773Aw(val)			_wr32(0x300215fc,(UINT)((_rd32(0x300215fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT080_EN773Ar				(ValSft_R00(_rd32(0x30021600))&BitMask_32)
#define DEFECT080_EN773Aw(val)			_wr32(0x30021600,(UINT)((_rd32(0x30021600)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT081_EN773Ar				(ValSft_R00(_rd32(0x30021604))&BitMask_32)
#define DEFECT081_EN773Aw(val)			_wr32(0x30021604,(UINT)((_rd32(0x30021604)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT082_EN773Ar				(ValSft_R00(_rd32(0x30021608))&BitMask_32)
#define DEFECT082_EN773Aw(val)			_wr32(0x30021608,(UINT)((_rd32(0x30021608)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT083_EN773Ar				(ValSft_R00(_rd32(0x3002160c))&BitMask_32)
#define DEFECT083_EN773Aw(val)			_wr32(0x3002160c,(UINT)((_rd32(0x3002160c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT084_EN773Ar				(ValSft_R00(_rd32(0x30021610))&BitMask_32)
#define DEFECT084_EN773Aw(val)			_wr32(0x30021610,(UINT)((_rd32(0x30021610)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT085_EN773Ar				(ValSft_R00(_rd32(0x30021614))&BitMask_32)
#define DEFECT085_EN773Aw(val)			_wr32(0x30021614,(UINT)((_rd32(0x30021614)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT086_EN773Ar				(ValSft_R00(_rd32(0x30021618))&BitMask_32)
#define DEFECT086_EN773Aw(val)			_wr32(0x30021618,(UINT)((_rd32(0x30021618)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT087_EN773Ar				(ValSft_R00(_rd32(0x3002161c))&BitMask_32)
#define DEFECT087_EN773Aw(val)			_wr32(0x3002161c,(UINT)((_rd32(0x3002161c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT088_EN773Ar				(ValSft_R00(_rd32(0x30021620))&BitMask_32)
#define DEFECT088_EN773Aw(val)			_wr32(0x30021620,(UINT)((_rd32(0x30021620)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT089_EN773Ar				(ValSft_R00(_rd32(0x30021624))&BitMask_32)
#define DEFECT089_EN773Aw(val)			_wr32(0x30021624,(UINT)((_rd32(0x30021624)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08a_EN773Ar				(ValSft_R00(_rd32(0x30021628))&BitMask_32)
#define DEFECT08a_EN773Aw(val)			_wr32(0x30021628,(UINT)((_rd32(0x30021628)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08b_EN773Ar				(ValSft_R00(_rd32(0x3002162c))&BitMask_32)
#define DEFECT08b_EN773Aw(val)			_wr32(0x3002162c,(UINT)((_rd32(0x3002162c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08c_EN773Ar				(ValSft_R00(_rd32(0x30021630))&BitMask_32)
#define DEFECT08c_EN773Aw(val)			_wr32(0x30021630,(UINT)((_rd32(0x30021630)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08d_EN773Ar				(ValSft_R00(_rd32(0x30021634))&BitMask_32)
#define DEFECT08d_EN773Aw(val)			_wr32(0x30021634,(UINT)((_rd32(0x30021634)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08e_EN773Ar				(ValSft_R00(_rd32(0x30021638))&BitMask_32)
#define DEFECT08e_EN773Aw(val)			_wr32(0x30021638,(UINT)((_rd32(0x30021638)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT08f_EN773Ar				(ValSft_R00(_rd32(0x3002163c))&BitMask_32)
#define DEFECT08f_EN773Aw(val)			_wr32(0x3002163c,(UINT)((_rd32(0x3002163c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT090_EN773Ar				(ValSft_R00(_rd32(0x30021640))&BitMask_32)
#define DEFECT090_EN773Aw(val)			_wr32(0x30021640,(UINT)((_rd32(0x30021640)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT091_EN773Ar				(ValSft_R00(_rd32(0x30021644))&BitMask_32)
#define DEFECT091_EN773Aw(val)			_wr32(0x30021644,(UINT)((_rd32(0x30021644)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT092_EN773Ar				(ValSft_R00(_rd32(0x30021648))&BitMask_32)
#define DEFECT092_EN773Aw(val)			_wr32(0x30021648,(UINT)((_rd32(0x30021648)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT093_EN773Ar				(ValSft_R00(_rd32(0x3002164c))&BitMask_32)
#define DEFECT093_EN773Aw(val)			_wr32(0x3002164c,(UINT)((_rd32(0x3002164c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT094_EN773Ar				(ValSft_R00(_rd32(0x30021650))&BitMask_32)
#define DEFECT094_EN773Aw(val)			_wr32(0x30021650,(UINT)((_rd32(0x30021650)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT095_EN773Ar				(ValSft_R00(_rd32(0x30021654))&BitMask_32)
#define DEFECT095_EN773Aw(val)			_wr32(0x30021654,(UINT)((_rd32(0x30021654)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT096_EN773Ar				(ValSft_R00(_rd32(0x30021658))&BitMask_32)
#define DEFECT096_EN773Aw(val)			_wr32(0x30021658,(UINT)((_rd32(0x30021658)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT097_EN773Ar				(ValSft_R00(_rd32(0x3002165c))&BitMask_32)
#define DEFECT097_EN773Aw(val)			_wr32(0x3002165c,(UINT)((_rd32(0x3002165c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT098_EN773Ar				(ValSft_R00(_rd32(0x30021660))&BitMask_32)
#define DEFECT098_EN773Aw(val)			_wr32(0x30021660,(UINT)((_rd32(0x30021660)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT099_EN773Ar				(ValSft_R00(_rd32(0x30021664))&BitMask_32)
#define DEFECT099_EN773Aw(val)			_wr32(0x30021664,(UINT)((_rd32(0x30021664)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09a_EN773Ar				(ValSft_R00(_rd32(0x30021668))&BitMask_32)
#define DEFECT09a_EN773Aw(val)			_wr32(0x30021668,(UINT)((_rd32(0x30021668)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09b_EN773Ar				(ValSft_R00(_rd32(0x3002166c))&BitMask_32)
#define DEFECT09b_EN773Aw(val)			_wr32(0x3002166c,(UINT)((_rd32(0x3002166c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09c_EN773Ar				(ValSft_R00(_rd32(0x30021670))&BitMask_32)
#define DEFECT09c_EN773Aw(val)			_wr32(0x30021670,(UINT)((_rd32(0x30021670)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09d_EN773Ar				(ValSft_R00(_rd32(0x30021674))&BitMask_32)
#define DEFECT09d_EN773Aw(val)			_wr32(0x30021674,(UINT)((_rd32(0x30021674)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09e_EN773Ar				(ValSft_R00(_rd32(0x30021678))&BitMask_32)
#define DEFECT09e_EN773Aw(val)			_wr32(0x30021678,(UINT)((_rd32(0x30021678)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT09f_EN773Ar				(ValSft_R00(_rd32(0x3002167c))&BitMask_32)
#define DEFECT09f_EN773Aw(val)			_wr32(0x3002167c,(UINT)((_rd32(0x3002167c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a0_EN773Ar				(ValSft_R00(_rd32(0x30021680))&BitMask_32)
#define DEFECT0a0_EN773Aw(val)			_wr32(0x30021680,(UINT)((_rd32(0x30021680)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a1_EN773Ar				(ValSft_R00(_rd32(0x30021684))&BitMask_32)
#define DEFECT0a1_EN773Aw(val)			_wr32(0x30021684,(UINT)((_rd32(0x30021684)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a2_EN773Ar				(ValSft_R00(_rd32(0x30021688))&BitMask_32)
#define DEFECT0a2_EN773Aw(val)			_wr32(0x30021688,(UINT)((_rd32(0x30021688)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a3_EN773Ar				(ValSft_R00(_rd32(0x3002168c))&BitMask_32)
#define DEFECT0a3_EN773Aw(val)			_wr32(0x3002168c,(UINT)((_rd32(0x3002168c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a4_EN773Ar				(ValSft_R00(_rd32(0x30021690))&BitMask_32)
#define DEFECT0a4_EN773Aw(val)			_wr32(0x30021690,(UINT)((_rd32(0x30021690)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a5_EN773Ar				(ValSft_R00(_rd32(0x30021694))&BitMask_32)
#define DEFECT0a5_EN773Aw(val)			_wr32(0x30021694,(UINT)((_rd32(0x30021694)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a6_EN773Ar				(ValSft_R00(_rd32(0x30021698))&BitMask_32)
#define DEFECT0a6_EN773Aw(val)			_wr32(0x30021698,(UINT)((_rd32(0x30021698)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a7_EN773Ar				(ValSft_R00(_rd32(0x3002169c))&BitMask_32)
#define DEFECT0a7_EN773Aw(val)			_wr32(0x3002169c,(UINT)((_rd32(0x3002169c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a8_EN773Ar				(ValSft_R00(_rd32(0x300216a0))&BitMask_32)
#define DEFECT0a8_EN773Aw(val)			_wr32(0x300216a0,(UINT)((_rd32(0x300216a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0a9_EN773Ar				(ValSft_R00(_rd32(0x300216a4))&BitMask_32)
#define DEFECT0a9_EN773Aw(val)			_wr32(0x300216a4,(UINT)((_rd32(0x300216a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0aa_EN773Ar				(ValSft_R00(_rd32(0x300216a8))&BitMask_32)
#define DEFECT0aa_EN773Aw(val)			_wr32(0x300216a8,(UINT)((_rd32(0x300216a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ab_EN773Ar				(ValSft_R00(_rd32(0x300216ac))&BitMask_32)
#define DEFECT0ab_EN773Aw(val)			_wr32(0x300216ac,(UINT)((_rd32(0x300216ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ac_EN773Ar				(ValSft_R00(_rd32(0x300216b0))&BitMask_32)
#define DEFECT0ac_EN773Aw(val)			_wr32(0x300216b0,(UINT)((_rd32(0x300216b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ad_EN773Ar				(ValSft_R00(_rd32(0x300216b4))&BitMask_32)
#define DEFECT0ad_EN773Aw(val)			_wr32(0x300216b4,(UINT)((_rd32(0x300216b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ae_EN773Ar				(ValSft_R00(_rd32(0x300216b8))&BitMask_32)
#define DEFECT0ae_EN773Aw(val)			_wr32(0x300216b8,(UINT)((_rd32(0x300216b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0af_EN773Ar				(ValSft_R00(_rd32(0x300216bc))&BitMask_32)
#define DEFECT0af_EN773Aw(val)			_wr32(0x300216bc,(UINT)((_rd32(0x300216bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b0_EN773Ar				(ValSft_R00(_rd32(0x300216c0))&BitMask_32)
#define DEFECT0b0_EN773Aw(val)			_wr32(0x300216c0,(UINT)((_rd32(0x300216c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b1_EN773Ar				(ValSft_R00(_rd32(0x300216c4))&BitMask_32)
#define DEFECT0b1_EN773Aw(val)			_wr32(0x300216c4,(UINT)((_rd32(0x300216c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b2_EN773Ar				(ValSft_R00(_rd32(0x300216c8))&BitMask_32)
#define DEFECT0b2_EN773Aw(val)			_wr32(0x300216c8,(UINT)((_rd32(0x300216c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b3_EN773Ar				(ValSft_R00(_rd32(0x300216cc))&BitMask_32)
#define DEFECT0b3_EN773Aw(val)			_wr32(0x300216cc,(UINT)((_rd32(0x300216cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b4_EN773Ar				(ValSft_R00(_rd32(0x300216d0))&BitMask_32)
#define DEFECT0b4_EN773Aw(val)			_wr32(0x300216d0,(UINT)((_rd32(0x300216d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b5_EN773Ar				(ValSft_R00(_rd32(0x300216d4))&BitMask_32)
#define DEFECT0b5_EN773Aw(val)			_wr32(0x300216d4,(UINT)((_rd32(0x300216d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b6_EN773Ar				(ValSft_R00(_rd32(0x300216d8))&BitMask_32)
#define DEFECT0b6_EN773Aw(val)			_wr32(0x300216d8,(UINT)((_rd32(0x300216d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b7_EN773Ar				(ValSft_R00(_rd32(0x300216dc))&BitMask_32)
#define DEFECT0b7_EN773Aw(val)			_wr32(0x300216dc,(UINT)((_rd32(0x300216dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b8_EN773Ar				(ValSft_R00(_rd32(0x300216e0))&BitMask_32)
#define DEFECT0b8_EN773Aw(val)			_wr32(0x300216e0,(UINT)((_rd32(0x300216e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0b9_EN773Ar				(ValSft_R00(_rd32(0x300216e4))&BitMask_32)
#define DEFECT0b9_EN773Aw(val)			_wr32(0x300216e4,(UINT)((_rd32(0x300216e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ba_EN773Ar				(ValSft_R00(_rd32(0x300216e8))&BitMask_32)
#define DEFECT0ba_EN773Aw(val)			_wr32(0x300216e8,(UINT)((_rd32(0x300216e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0bb_EN773Ar				(ValSft_R00(_rd32(0x300216ec))&BitMask_32)
#define DEFECT0bb_EN773Aw(val)			_wr32(0x300216ec,(UINT)((_rd32(0x300216ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0bc_EN773Ar				(ValSft_R00(_rd32(0x300216f0))&BitMask_32)
#define DEFECT0bc_EN773Aw(val)			_wr32(0x300216f0,(UINT)((_rd32(0x300216f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0bd_EN773Ar				(ValSft_R00(_rd32(0x300216f4))&BitMask_32)
#define DEFECT0bd_EN773Aw(val)			_wr32(0x300216f4,(UINT)((_rd32(0x300216f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0be_EN773Ar				(ValSft_R00(_rd32(0x300216f8))&BitMask_32)
#define DEFECT0be_EN773Aw(val)			_wr32(0x300216f8,(UINT)((_rd32(0x300216f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0bf_EN773Ar				(ValSft_R00(_rd32(0x300216fc))&BitMask_32)
#define DEFECT0bf_EN773Aw(val)			_wr32(0x300216fc,(UINT)((_rd32(0x300216fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c0_EN773Ar				(ValSft_R00(_rd32(0x30021700))&BitMask_32)
#define DEFECT0c0_EN773Aw(val)			_wr32(0x30021700,(UINT)((_rd32(0x30021700)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c1_EN773Ar				(ValSft_R00(_rd32(0x30021704))&BitMask_32)
#define DEFECT0c1_EN773Aw(val)			_wr32(0x30021704,(UINT)((_rd32(0x30021704)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c2_EN773Ar				(ValSft_R00(_rd32(0x30021708))&BitMask_32)
#define DEFECT0c2_EN773Aw(val)			_wr32(0x30021708,(UINT)((_rd32(0x30021708)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c3_EN773Ar				(ValSft_R00(_rd32(0x3002170c))&BitMask_32)
#define DEFECT0c3_EN773Aw(val)			_wr32(0x3002170c,(UINT)((_rd32(0x3002170c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c4_EN773Ar				(ValSft_R00(_rd32(0x30021710))&BitMask_32)
#define DEFECT0c4_EN773Aw(val)			_wr32(0x30021710,(UINT)((_rd32(0x30021710)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c5_EN773Ar				(ValSft_R00(_rd32(0x30021714))&BitMask_32)
#define DEFECT0c5_EN773Aw(val)			_wr32(0x30021714,(UINT)((_rd32(0x30021714)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c6_EN773Ar				(ValSft_R00(_rd32(0x30021718))&BitMask_32)
#define DEFECT0c6_EN773Aw(val)			_wr32(0x30021718,(UINT)((_rd32(0x30021718)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c7_EN773Ar				(ValSft_R00(_rd32(0x3002171c))&BitMask_32)
#define DEFECT0c7_EN773Aw(val)			_wr32(0x3002171c,(UINT)((_rd32(0x3002171c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c8_EN773Ar				(ValSft_R00(_rd32(0x30021720))&BitMask_32)
#define DEFECT0c8_EN773Aw(val)			_wr32(0x30021720,(UINT)((_rd32(0x30021720)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0c9_EN773Ar				(ValSft_R00(_rd32(0x30021724))&BitMask_32)
#define DEFECT0c9_EN773Aw(val)			_wr32(0x30021724,(UINT)((_rd32(0x30021724)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ca_EN773Ar				(ValSft_R00(_rd32(0x30021728))&BitMask_32)
#define DEFECT0ca_EN773Aw(val)			_wr32(0x30021728,(UINT)((_rd32(0x30021728)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0cb_EN773Ar				(ValSft_R00(_rd32(0x3002172c))&BitMask_32)
#define DEFECT0cb_EN773Aw(val)			_wr32(0x3002172c,(UINT)((_rd32(0x3002172c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0cc_EN773Ar				(ValSft_R00(_rd32(0x30021730))&BitMask_32)
#define DEFECT0cc_EN773Aw(val)			_wr32(0x30021730,(UINT)((_rd32(0x30021730)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0cd_EN773Ar				(ValSft_R00(_rd32(0x30021734))&BitMask_32)
#define DEFECT0cd_EN773Aw(val)			_wr32(0x30021734,(UINT)((_rd32(0x30021734)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ce_EN773Ar				(ValSft_R00(_rd32(0x30021738))&BitMask_32)
#define DEFECT0ce_EN773Aw(val)			_wr32(0x30021738,(UINT)((_rd32(0x30021738)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0cf_EN773Ar				(ValSft_R00(_rd32(0x3002173c))&BitMask_32)
#define DEFECT0cf_EN773Aw(val)			_wr32(0x3002173c,(UINT)((_rd32(0x3002173c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d0_EN773Ar				(ValSft_R00(_rd32(0x30021740))&BitMask_32)
#define DEFECT0d0_EN773Aw(val)			_wr32(0x30021740,(UINT)((_rd32(0x30021740)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d1_EN773Ar				(ValSft_R00(_rd32(0x30021744))&BitMask_32)
#define DEFECT0d1_EN773Aw(val)			_wr32(0x30021744,(UINT)((_rd32(0x30021744)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d2_EN773Ar				(ValSft_R00(_rd32(0x30021748))&BitMask_32)
#define DEFECT0d2_EN773Aw(val)			_wr32(0x30021748,(UINT)((_rd32(0x30021748)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d3_EN773Ar				(ValSft_R00(_rd32(0x3002174c))&BitMask_32)
#define DEFECT0d3_EN773Aw(val)			_wr32(0x3002174c,(UINT)((_rd32(0x3002174c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d4_EN773Ar				(ValSft_R00(_rd32(0x30021750))&BitMask_32)
#define DEFECT0d4_EN773Aw(val)			_wr32(0x30021750,(UINT)((_rd32(0x30021750)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d5_EN773Ar				(ValSft_R00(_rd32(0x30021754))&BitMask_32)
#define DEFECT0d5_EN773Aw(val)			_wr32(0x30021754,(UINT)((_rd32(0x30021754)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d6_EN773Ar				(ValSft_R00(_rd32(0x30021758))&BitMask_32)
#define DEFECT0d6_EN773Aw(val)			_wr32(0x30021758,(UINT)((_rd32(0x30021758)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d7_EN773Ar				(ValSft_R00(_rd32(0x3002175c))&BitMask_32)
#define DEFECT0d7_EN773Aw(val)			_wr32(0x3002175c,(UINT)((_rd32(0x3002175c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d8_EN773Ar				(ValSft_R00(_rd32(0x30021760))&BitMask_32)
#define DEFECT0d8_EN773Aw(val)			_wr32(0x30021760,(UINT)((_rd32(0x30021760)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0d9_EN773Ar				(ValSft_R00(_rd32(0x30021764))&BitMask_32)
#define DEFECT0d9_EN773Aw(val)			_wr32(0x30021764,(UINT)((_rd32(0x30021764)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0da_EN773Ar				(ValSft_R00(_rd32(0x30021768))&BitMask_32)
#define DEFECT0da_EN773Aw(val)			_wr32(0x30021768,(UINT)((_rd32(0x30021768)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0db_EN773Ar				(ValSft_R00(_rd32(0x3002176c))&BitMask_32)
#define DEFECT0db_EN773Aw(val)			_wr32(0x3002176c,(UINT)((_rd32(0x3002176c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0dc_EN773Ar				(ValSft_R00(_rd32(0x30021770))&BitMask_32)
#define DEFECT0dc_EN773Aw(val)			_wr32(0x30021770,(UINT)((_rd32(0x30021770)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0dd_EN773Ar				(ValSft_R00(_rd32(0x30021774))&BitMask_32)
#define DEFECT0dd_EN773Aw(val)			_wr32(0x30021774,(UINT)((_rd32(0x30021774)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0de_EN773Ar				(ValSft_R00(_rd32(0x30021778))&BitMask_32)
#define DEFECT0de_EN773Aw(val)			_wr32(0x30021778,(UINT)((_rd32(0x30021778)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0df_EN773Ar				(ValSft_R00(_rd32(0x3002177c))&BitMask_32)
#define DEFECT0df_EN773Aw(val)			_wr32(0x3002177c,(UINT)((_rd32(0x3002177c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e0_EN773Ar				(ValSft_R00(_rd32(0x30021780))&BitMask_32)
#define DEFECT0e0_EN773Aw(val)			_wr32(0x30021780,(UINT)((_rd32(0x30021780)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e1_EN773Ar				(ValSft_R00(_rd32(0x30021784))&BitMask_32)
#define DEFECT0e1_EN773Aw(val)			_wr32(0x30021784,(UINT)((_rd32(0x30021784)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e2_EN773Ar				(ValSft_R00(_rd32(0x30021788))&BitMask_32)
#define DEFECT0e2_EN773Aw(val)			_wr32(0x30021788,(UINT)((_rd32(0x30021788)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e3_EN773Ar				(ValSft_R00(_rd32(0x3002178c))&BitMask_32)
#define DEFECT0e3_EN773Aw(val)			_wr32(0x3002178c,(UINT)((_rd32(0x3002178c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e4_EN773Ar				(ValSft_R00(_rd32(0x30021790))&BitMask_32)
#define DEFECT0e4_EN773Aw(val)			_wr32(0x30021790,(UINT)((_rd32(0x30021790)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e5_EN773Ar				(ValSft_R00(_rd32(0x30021794))&BitMask_32)
#define DEFECT0e5_EN773Aw(val)			_wr32(0x30021794,(UINT)((_rd32(0x30021794)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e6_EN773Ar				(ValSft_R00(_rd32(0x30021798))&BitMask_32)
#define DEFECT0e6_EN773Aw(val)			_wr32(0x30021798,(UINT)((_rd32(0x30021798)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e7_EN773Ar				(ValSft_R00(_rd32(0x3002179c))&BitMask_32)
#define DEFECT0e7_EN773Aw(val)			_wr32(0x3002179c,(UINT)((_rd32(0x3002179c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e8_EN773Ar				(ValSft_R00(_rd32(0x300217a0))&BitMask_32)
#define DEFECT0e8_EN773Aw(val)			_wr32(0x300217a0,(UINT)((_rd32(0x300217a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0e9_EN773Ar				(ValSft_R00(_rd32(0x300217a4))&BitMask_32)
#define DEFECT0e9_EN773Aw(val)			_wr32(0x300217a4,(UINT)((_rd32(0x300217a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ea_EN773Ar				(ValSft_R00(_rd32(0x300217a8))&BitMask_32)
#define DEFECT0ea_EN773Aw(val)			_wr32(0x300217a8,(UINT)((_rd32(0x300217a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0eb_EN773Ar				(ValSft_R00(_rd32(0x300217ac))&BitMask_32)
#define DEFECT0eb_EN773Aw(val)			_wr32(0x300217ac,(UINT)((_rd32(0x300217ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ec_EN773Ar				(ValSft_R00(_rd32(0x300217b0))&BitMask_32)
#define DEFECT0ec_EN773Aw(val)			_wr32(0x300217b0,(UINT)((_rd32(0x300217b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ed_EN773Ar				(ValSft_R00(_rd32(0x300217b4))&BitMask_32)
#define DEFECT0ed_EN773Aw(val)			_wr32(0x300217b4,(UINT)((_rd32(0x300217b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ee_EN773Ar				(ValSft_R00(_rd32(0x300217b8))&BitMask_32)
#define DEFECT0ee_EN773Aw(val)			_wr32(0x300217b8,(UINT)((_rd32(0x300217b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ef_EN773Ar				(ValSft_R00(_rd32(0x300217bc))&BitMask_32)
#define DEFECT0ef_EN773Aw(val)			_wr32(0x300217bc,(UINT)((_rd32(0x300217bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f0_EN773Ar				(ValSft_R00(_rd32(0x300217c0))&BitMask_32)
#define DEFECT0f0_EN773Aw(val)			_wr32(0x300217c0,(UINT)((_rd32(0x300217c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f1_EN773Ar				(ValSft_R00(_rd32(0x300217c4))&BitMask_32)
#define DEFECT0f1_EN773Aw(val)			_wr32(0x300217c4,(UINT)((_rd32(0x300217c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f2_EN773Ar				(ValSft_R00(_rd32(0x300217c8))&BitMask_32)
#define DEFECT0f2_EN773Aw(val)			_wr32(0x300217c8,(UINT)((_rd32(0x300217c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f3_EN773Ar				(ValSft_R00(_rd32(0x300217cc))&BitMask_32)
#define DEFECT0f3_EN773Aw(val)			_wr32(0x300217cc,(UINT)((_rd32(0x300217cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f4_EN773Ar				(ValSft_R00(_rd32(0x300217d0))&BitMask_32)
#define DEFECT0f4_EN773Aw(val)			_wr32(0x300217d0,(UINT)((_rd32(0x300217d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f5_EN773Ar				(ValSft_R00(_rd32(0x300217d4))&BitMask_32)
#define DEFECT0f5_EN773Aw(val)			_wr32(0x300217d4,(UINT)((_rd32(0x300217d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f6_EN773Ar				(ValSft_R00(_rd32(0x300217d8))&BitMask_32)
#define DEFECT0f6_EN773Aw(val)			_wr32(0x300217d8,(UINT)((_rd32(0x300217d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f7_EN773Ar				(ValSft_R00(_rd32(0x300217dc))&BitMask_32)
#define DEFECT0f7_EN773Aw(val)			_wr32(0x300217dc,(UINT)((_rd32(0x300217dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f8_EN773Ar				(ValSft_R00(_rd32(0x300217e0))&BitMask_32)
#define DEFECT0f8_EN773Aw(val)			_wr32(0x300217e0,(UINT)((_rd32(0x300217e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0f9_EN773Ar				(ValSft_R00(_rd32(0x300217e4))&BitMask_32)
#define DEFECT0f9_EN773Aw(val)			_wr32(0x300217e4,(UINT)((_rd32(0x300217e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0fa_EN773Ar				(ValSft_R00(_rd32(0x300217e8))&BitMask_32)
#define DEFECT0fa_EN773Aw(val)			_wr32(0x300217e8,(UINT)((_rd32(0x300217e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0fb_EN773Ar				(ValSft_R00(_rd32(0x300217ec))&BitMask_32)
#define DEFECT0fb_EN773Aw(val)			_wr32(0x300217ec,(UINT)((_rd32(0x300217ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0fc_EN773Ar				(ValSft_R00(_rd32(0x300217f0))&BitMask_32)
#define DEFECT0fc_EN773Aw(val)			_wr32(0x300217f0,(UINT)((_rd32(0x300217f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0fd_EN773Ar				(ValSft_R00(_rd32(0x300217f4))&BitMask_32)
#define DEFECT0fd_EN773Aw(val)			_wr32(0x300217f4,(UINT)((_rd32(0x300217f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0fe_EN773Ar				(ValSft_R00(_rd32(0x300217f8))&BitMask_32)
#define DEFECT0fe_EN773Aw(val)			_wr32(0x300217f8,(UINT)((_rd32(0x300217f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define DEFECT0ff_EN773Ar				(ValSft_R00(_rd32(0x300217fc))&BitMask_32)
#define DEFECT0ff_EN773Aw(val)			_wr32(0x300217fc,(UINT)((_rd32(0x300217fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD000_EN773Ar					(ValSft_R00(_rd32(0x30022400))&BitMask_32)
#define IMD000_EN773Aw(val)				_wr32(0x30022400,(UINT)((_rd32(0x30022400)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD001_EN773Ar					(ValSft_R00(_rd32(0x30022404))&BitMask_32)
#define IMD001_EN773Aw(val)				_wr32(0x30022404,(UINT)((_rd32(0x30022404)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD002_EN773Ar					(ValSft_R00(_rd32(0x30022408))&BitMask_32)
#define IMD002_EN773Aw(val)				_wr32(0x30022408,(UINT)((_rd32(0x30022408)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD003_EN773Ar					(ValSft_R00(_rd32(0x3002240c))&BitMask_32)
#define IMD003_EN773Aw(val)				_wr32(0x3002240c,(UINT)((_rd32(0x3002240c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD004_EN773Ar					(ValSft_R00(_rd32(0x30022410))&BitMask_32)
#define IMD004_EN773Aw(val)				_wr32(0x30022410,(UINT)((_rd32(0x30022410)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD005_EN773Ar					(ValSft_R00(_rd32(0x30022414))&BitMask_32)
#define IMD005_EN773Aw(val)				_wr32(0x30022414,(UINT)((_rd32(0x30022414)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD006_EN773Ar					(ValSft_R00(_rd32(0x30022418))&BitMask_32)
#define IMD006_EN773Aw(val)				_wr32(0x30022418,(UINT)((_rd32(0x30022418)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD007_EN773Ar					(ValSft_R00(_rd32(0x3002241c))&BitMask_32)
#define IMD007_EN773Aw(val)				_wr32(0x3002241c,(UINT)((_rd32(0x3002241c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD008_EN773Ar					(ValSft_R00(_rd32(0x30022420))&BitMask_32)
#define IMD008_EN773Aw(val)				_wr32(0x30022420,(UINT)((_rd32(0x30022420)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD009_EN773Ar					(ValSft_R00(_rd32(0x30022424))&BitMask_32)
#define IMD009_EN773Aw(val)				_wr32(0x30022424,(UINT)((_rd32(0x30022424)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00a_EN773Ar					(ValSft_R00(_rd32(0x30022428))&BitMask_32)
#define IMD00a_EN773Aw(val)				_wr32(0x30022428,(UINT)((_rd32(0x30022428)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00b_EN773Ar					(ValSft_R00(_rd32(0x3002242c))&BitMask_32)
#define IMD00b_EN773Aw(val)				_wr32(0x3002242c,(UINT)((_rd32(0x3002242c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00c_EN773Ar					(ValSft_R00(_rd32(0x30022430))&BitMask_32)
#define IMD00c_EN773Aw(val)				_wr32(0x30022430,(UINT)((_rd32(0x30022430)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00d_EN773Ar					(ValSft_R00(_rd32(0x30022434))&BitMask_32)
#define IMD00d_EN773Aw(val)				_wr32(0x30022434,(UINT)((_rd32(0x30022434)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00e_EN773Ar					(ValSft_R00(_rd32(0x30022438))&BitMask_32)
#define IMD00e_EN773Aw(val)				_wr32(0x30022438,(UINT)((_rd32(0x30022438)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD00f_EN773Ar					(ValSft_R00(_rd32(0x3002243c))&BitMask_32)
#define IMD00f_EN773Aw(val)				_wr32(0x3002243c,(UINT)((_rd32(0x3002243c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD010_EN773Ar					(ValSft_R00(_rd32(0x30022440))&BitMask_32)
#define IMD010_EN773Aw(val)				_wr32(0x30022440,(UINT)((_rd32(0x30022440)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD011_EN773Ar					(ValSft_R00(_rd32(0x30022444))&BitMask_32)
#define IMD011_EN773Aw(val)				_wr32(0x30022444,(UINT)((_rd32(0x30022444)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD012_EN773Ar					(ValSft_R00(_rd32(0x30022448))&BitMask_32)
#define IMD012_EN773Aw(val)				_wr32(0x30022448,(UINT)((_rd32(0x30022448)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD013_EN773Ar					(ValSft_R00(_rd32(0x3002244c))&BitMask_32)
#define IMD013_EN773Aw(val)				_wr32(0x3002244c,(UINT)((_rd32(0x3002244c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD014_EN773Ar					(ValSft_R00(_rd32(0x30022450))&BitMask_32)
#define IMD014_EN773Aw(val)				_wr32(0x30022450,(UINT)((_rd32(0x30022450)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD015_EN773Ar					(ValSft_R00(_rd32(0x30022454))&BitMask_32)
#define IMD015_EN773Aw(val)				_wr32(0x30022454,(UINT)((_rd32(0x30022454)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD016_EN773Ar					(ValSft_R00(_rd32(0x30022458))&BitMask_32)
#define IMD016_EN773Aw(val)				_wr32(0x30022458,(UINT)((_rd32(0x30022458)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD017_EN773Ar					(ValSft_R00(_rd32(0x3002245c))&BitMask_32)
#define IMD017_EN773Aw(val)				_wr32(0x3002245c,(UINT)((_rd32(0x3002245c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD018_EN773Ar					(ValSft_R00(_rd32(0x30022460))&BitMask_32)
#define IMD018_EN773Aw(val)				_wr32(0x30022460,(UINT)((_rd32(0x30022460)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD019_EN773Ar					(ValSft_R00(_rd32(0x30022464))&BitMask_32)
#define IMD019_EN773Aw(val)				_wr32(0x30022464,(UINT)((_rd32(0x30022464)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01a_EN773Ar					(ValSft_R00(_rd32(0x30022468))&BitMask_32)
#define IMD01a_EN773Aw(val)				_wr32(0x30022468,(UINT)((_rd32(0x30022468)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01b_EN773Ar					(ValSft_R00(_rd32(0x3002246c))&BitMask_32)
#define IMD01b_EN773Aw(val)				_wr32(0x3002246c,(UINT)((_rd32(0x3002246c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01c_EN773Ar					(ValSft_R00(_rd32(0x30022470))&BitMask_32)
#define IMD01c_EN773Aw(val)				_wr32(0x30022470,(UINT)((_rd32(0x30022470)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01d_EN773Ar					(ValSft_R00(_rd32(0x30022474))&BitMask_32)
#define IMD01d_EN773Aw(val)				_wr32(0x30022474,(UINT)((_rd32(0x30022474)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01e_EN773Ar					(ValSft_R00(_rd32(0x30022478))&BitMask_32)
#define IMD01e_EN773Aw(val)				_wr32(0x30022478,(UINT)((_rd32(0x30022478)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD01f_EN773Ar					(ValSft_R00(_rd32(0x3002247c))&BitMask_32)
#define IMD01f_EN773Aw(val)				_wr32(0x3002247c,(UINT)((_rd32(0x3002247c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD020_EN773Ar					(ValSft_R00(_rd32(0x30022480))&BitMask_32)
#define IMD020_EN773Aw(val)				_wr32(0x30022480,(UINT)((_rd32(0x30022480)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD021_EN773Ar					(ValSft_R00(_rd32(0x30022484))&BitMask_32)
#define IMD021_EN773Aw(val)				_wr32(0x30022484,(UINT)((_rd32(0x30022484)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD022_EN773Ar					(ValSft_R00(_rd32(0x30022488))&BitMask_32)
#define IMD022_EN773Aw(val)				_wr32(0x30022488,(UINT)((_rd32(0x30022488)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD023_EN773Ar					(ValSft_R00(_rd32(0x3002248c))&BitMask_32)
#define IMD023_EN773Aw(val)				_wr32(0x3002248c,(UINT)((_rd32(0x3002248c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD024_EN773Ar					(ValSft_R00(_rd32(0x30022490))&BitMask_32)
#define IMD024_EN773Aw(val)				_wr32(0x30022490,(UINT)((_rd32(0x30022490)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD025_EN773Ar					(ValSft_R00(_rd32(0x30022494))&BitMask_32)
#define IMD025_EN773Aw(val)				_wr32(0x30022494,(UINT)((_rd32(0x30022494)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD026_EN773Ar					(ValSft_R00(_rd32(0x30022498))&BitMask_32)
#define IMD026_EN773Aw(val)				_wr32(0x30022498,(UINT)((_rd32(0x30022498)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD027_EN773Ar					(ValSft_R00(_rd32(0x3002249c))&BitMask_32)
#define IMD027_EN773Aw(val)				_wr32(0x3002249c,(UINT)((_rd32(0x3002249c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD028_EN773Ar					(ValSft_R00(_rd32(0x300224a0))&BitMask_32)
#define IMD028_EN773Aw(val)				_wr32(0x300224a0,(UINT)((_rd32(0x300224a0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD029_EN773Ar					(ValSft_R00(_rd32(0x300224a4))&BitMask_32)
#define IMD029_EN773Aw(val)				_wr32(0x300224a4,(UINT)((_rd32(0x300224a4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02a_EN773Ar					(ValSft_R00(_rd32(0x300224a8))&BitMask_32)
#define IMD02a_EN773Aw(val)				_wr32(0x300224a8,(UINT)((_rd32(0x300224a8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02b_EN773Ar					(ValSft_R00(_rd32(0x300224ac))&BitMask_32)
#define IMD02b_EN773Aw(val)				_wr32(0x300224ac,(UINT)((_rd32(0x300224ac)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02c_EN773Ar					(ValSft_R00(_rd32(0x300224b0))&BitMask_32)
#define IMD02c_EN773Aw(val)				_wr32(0x300224b0,(UINT)((_rd32(0x300224b0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02d_EN773Ar					(ValSft_R00(_rd32(0x300224b4))&BitMask_32)
#define IMD02d_EN773Aw(val)				_wr32(0x300224b4,(UINT)((_rd32(0x300224b4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02e_EN773Ar					(ValSft_R00(_rd32(0x300224b8))&BitMask_32)
#define IMD02e_EN773Aw(val)				_wr32(0x300224b8,(UINT)((_rd32(0x300224b8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD02f_EN773Ar					(ValSft_R00(_rd32(0x300224bc))&BitMask_32)
#define IMD02f_EN773Aw(val)				_wr32(0x300224bc,(UINT)((_rd32(0x300224bc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD030_EN773Ar					(ValSft_R00(_rd32(0x300224c0))&BitMask_32)
#define IMD030_EN773Aw(val)				_wr32(0x300224c0,(UINT)((_rd32(0x300224c0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD031_EN773Ar					(ValSft_R00(_rd32(0x300224c4))&BitMask_32)
#define IMD031_EN773Aw(val)				_wr32(0x300224c4,(UINT)((_rd32(0x300224c4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD032_EN773Ar					(ValSft_R00(_rd32(0x300224c8))&BitMask_32)
#define IMD032_EN773Aw(val)				_wr32(0x300224c8,(UINT)((_rd32(0x300224c8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD033_EN773Ar					(ValSft_R00(_rd32(0x300224cc))&BitMask_32)
#define IMD033_EN773Aw(val)				_wr32(0x300224cc,(UINT)((_rd32(0x300224cc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD034_EN773Ar					(ValSft_R00(_rd32(0x300224d0))&BitMask_32)
#define IMD034_EN773Aw(val)				_wr32(0x300224d0,(UINT)((_rd32(0x300224d0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD035_EN773Ar					(ValSft_R00(_rd32(0x300224d4))&BitMask_32)
#define IMD035_EN773Aw(val)				_wr32(0x300224d4,(UINT)((_rd32(0x300224d4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD036_EN773Ar					(ValSft_R00(_rd32(0x300224d8))&BitMask_32)
#define IMD036_EN773Aw(val)				_wr32(0x300224d8,(UINT)((_rd32(0x300224d8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD037_EN773Ar					(ValSft_R00(_rd32(0x300224dc))&BitMask_32)
#define IMD037_EN773Aw(val)				_wr32(0x300224dc,(UINT)((_rd32(0x300224dc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD038_EN773Ar					(ValSft_R00(_rd32(0x300224e0))&BitMask_32)
#define IMD038_EN773Aw(val)				_wr32(0x300224e0,(UINT)((_rd32(0x300224e0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD039_EN773Ar					(ValSft_R00(_rd32(0x300224e4))&BitMask_32)
#define IMD039_EN773Aw(val)				_wr32(0x300224e4,(UINT)((_rd32(0x300224e4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03a_EN773Ar					(ValSft_R00(_rd32(0x300224e8))&BitMask_32)
#define IMD03a_EN773Aw(val)				_wr32(0x300224e8,(UINT)((_rd32(0x300224e8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03b_EN773Ar					(ValSft_R00(_rd32(0x300224ec))&BitMask_32)
#define IMD03b_EN773Aw(val)				_wr32(0x300224ec,(UINT)((_rd32(0x300224ec)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03c_EN773Ar					(ValSft_R00(_rd32(0x300224f0))&BitMask_32)
#define IMD03c_EN773Aw(val)				_wr32(0x300224f0,(UINT)((_rd32(0x300224f0)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03d_EN773Ar					(ValSft_R00(_rd32(0x300224f4))&BitMask_32)
#define IMD03d_EN773Aw(val)				_wr32(0x300224f4,(UINT)((_rd32(0x300224f4)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03e_EN773Ar					(ValSft_R00(_rd32(0x300224f8))&BitMask_32)
#define IMD03e_EN773Aw(val)				_wr32(0x300224f8,(UINT)((_rd32(0x300224f8)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD03f_EN773Ar					(ValSft_R00(_rd32(0x300224fc))&BitMask_32)
#define IMD03f_EN773Aw(val)				_wr32(0x300224fc,(UINT)((_rd32(0x300224fc)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD040_EN773Ar					(ValSft_R00(_rd32(0x30022500))&BitMask_32)
#define IMD040_EN773Aw(val)				_wr32(0x30022500,(UINT)((_rd32(0x30022500)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD041_EN773Ar					(ValSft_R00(_rd32(0x30022504))&BitMask_32)
#define IMD041_EN773Aw(val)				_wr32(0x30022504,(UINT)((_rd32(0x30022504)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD042_EN773Ar					(ValSft_R00(_rd32(0x30022508))&BitMask_32)
#define IMD042_EN773Aw(val)				_wr32(0x30022508,(UINT)((_rd32(0x30022508)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD043_EN773Ar					(ValSft_R00(_rd32(0x3002250c))&BitMask_32)
#define IMD043_EN773Aw(val)				_wr32(0x3002250c,(UINT)((_rd32(0x3002250c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD044_EN773Ar					(ValSft_R00(_rd32(0x30022510))&BitMask_32)
#define IMD044_EN773Aw(val)				_wr32(0x30022510,(UINT)((_rd32(0x30022510)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD045_EN773Ar					(ValSft_R00(_rd32(0x30022514))&BitMask_32)
#define IMD045_EN773Aw(val)				_wr32(0x30022514,(UINT)((_rd32(0x30022514)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD046_EN773Ar					(ValSft_R00(_rd32(0x30022518))&BitMask_32)
#define IMD046_EN773Aw(val)				_wr32(0x30022518,(UINT)((_rd32(0x30022518)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD047_EN773Ar					(ValSft_R00(_rd32(0x3002251c))&BitMask_32)
#define IMD047_EN773Aw(val)				_wr32(0x3002251c,(UINT)((_rd32(0x3002251c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD048_EN773Ar					(ValSft_R00(_rd32(0x30022520))&BitMask_32)
#define IMD048_EN773Aw(val)				_wr32(0x30022520,(UINT)((_rd32(0x30022520)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD049_EN773Ar					(ValSft_R00(_rd32(0x30022524))&BitMask_32)
#define IMD049_EN773Aw(val)				_wr32(0x30022524,(UINT)((_rd32(0x30022524)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04a_EN773Ar					(ValSft_R00(_rd32(0x30022528))&BitMask_32)
#define IMD04a_EN773Aw(val)				_wr32(0x30022528,(UINT)((_rd32(0x30022528)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04b_EN773Ar					(ValSft_R00(_rd32(0x3002252c))&BitMask_32)
#define IMD04b_EN773Aw(val)				_wr32(0x3002252c,(UINT)((_rd32(0x3002252c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04c_EN773Ar					(ValSft_R00(_rd32(0x30022530))&BitMask_32)
#define IMD04c_EN773Aw(val)				_wr32(0x30022530,(UINT)((_rd32(0x30022530)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04d_EN773Ar					(ValSft_R00(_rd32(0x30022534))&BitMask_32)
#define IMD04d_EN773Aw(val)				_wr32(0x30022534,(UINT)((_rd32(0x30022534)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04e_EN773Ar					(ValSft_R00(_rd32(0x30022538))&BitMask_32)
#define IMD04e_EN773Aw(val)				_wr32(0x30022538,(UINT)((_rd32(0x30022538)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD04f_EN773Ar					(ValSft_R00(_rd32(0x3002253c))&BitMask_32)
#define IMD04f_EN773Aw(val)				_wr32(0x3002253c,(UINT)((_rd32(0x3002253c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD050_EN773Ar					(ValSft_R00(_rd32(0x30022540))&BitMask_32)
#define IMD050_EN773Aw(val)				_wr32(0x30022540,(UINT)((_rd32(0x30022540)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD051_EN773Ar					(ValSft_R00(_rd32(0x30022544))&BitMask_32)
#define IMD051_EN773Aw(val)				_wr32(0x30022544,(UINT)((_rd32(0x30022544)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD052_EN773Ar					(ValSft_R00(_rd32(0x30022548))&BitMask_32)
#define IMD052_EN773Aw(val)				_wr32(0x30022548,(UINT)((_rd32(0x30022548)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD053_EN773Ar					(ValSft_R00(_rd32(0x3002254c))&BitMask_32)
#define IMD053_EN773Aw(val)				_wr32(0x3002254c,(UINT)((_rd32(0x3002254c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD054_EN773Ar					(ValSft_R00(_rd32(0x30022550))&BitMask_32)
#define IMD054_EN773Aw(val)				_wr32(0x30022550,(UINT)((_rd32(0x30022550)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD055_EN773Ar					(ValSft_R00(_rd32(0x30022554))&BitMask_32)
#define IMD055_EN773Aw(val)				_wr32(0x30022554,(UINT)((_rd32(0x30022554)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD056_EN773Ar					(ValSft_R00(_rd32(0x30022558))&BitMask_32)
#define IMD056_EN773Aw(val)				_wr32(0x30022558,(UINT)((_rd32(0x30022558)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD057_EN773Ar					(ValSft_R00(_rd32(0x3002255c))&BitMask_32)
#define IMD057_EN773Aw(val)				_wr32(0x3002255c,(UINT)((_rd32(0x3002255c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD058_EN773Ar					(ValSft_R00(_rd32(0x30022560))&BitMask_32)
#define IMD058_EN773Aw(val)				_wr32(0x30022560,(UINT)((_rd32(0x30022560)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD059_EN773Ar					(ValSft_R00(_rd32(0x30022564))&BitMask_32)
#define IMD059_EN773Aw(val)				_wr32(0x30022564,(UINT)((_rd32(0x30022564)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05a_EN773Ar					(ValSft_R00(_rd32(0x30022568))&BitMask_32)
#define IMD05a_EN773Aw(val)				_wr32(0x30022568,(UINT)((_rd32(0x30022568)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05b_EN773Ar					(ValSft_R00(_rd32(0x3002256c))&BitMask_32)
#define IMD05b_EN773Aw(val)				_wr32(0x3002256c,(UINT)((_rd32(0x3002256c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05c_EN773Ar					(ValSft_R00(_rd32(0x30022570))&BitMask_32)
#define IMD05c_EN773Aw(val)				_wr32(0x30022570,(UINT)((_rd32(0x30022570)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05d_EN773Ar					(ValSft_R00(_rd32(0x30022574))&BitMask_32)
#define IMD05d_EN773Aw(val)				_wr32(0x30022574,(UINT)((_rd32(0x30022574)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05e_EN773Ar					(ValSft_R00(_rd32(0x30022578))&BitMask_32)
#define IMD05e_EN773Aw(val)				_wr32(0x30022578,(UINT)((_rd32(0x30022578)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define IMD05f_EN773Ar					(ValSft_R00(_rd32(0x3002257c))&BitMask_32)
#define IMD05f_EN773Aw(val)				_wr32(0x3002257c,(UINT)((_rd32(0x3002257c)&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define USB_HWI_EN773Ar					(ValSft_R00(_rd32(0x3002fc04))&BitMask_12)
#define USB_HWI_EN773Aw(val)			_wr32(0x3002fc04,(UINT)((_rd32(0x3002fc04)&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define USB_VWI_EN773Ar					(ValSft_R00(_rd32(0x3002fc08))&BitMask_11)
#define USB_VWI_EN773Aw(val)			_wr32(0x3002fc08,(UINT)((_rd32(0x3002fc08)&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define AE1_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c00))&BitMask_31)
#define AE1_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c04))&BitMask_31)
#define AE2_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c08))&BitMask_31)
#define AE2_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c0c))&BitMask_31)
#define AE3_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c10))&BitMask_31)
#define AE3_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c14))&BitMask_31)
#define AE4_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c18))&BitMask_31)
#define AE4_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c1c))&BitMask_31)
#define AE5_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c20))&BitMask_31)
#define AE5_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c24))&BitMask_31)
#define AE6_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c28))&BitMask_31)
#define AE6_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c2c))&BitMask_31)
#define AE1_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c30))&BitMask_21)
#define AE2_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c34))&BitMask_21)
#define AE3_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c38))&BitMask_21)
#define AE4_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c3c))&BitMask_21)
#define AE5_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c40))&BitMask_21)
#define AE6_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c44))&BitMask_21)
#define AE1_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c48))&BitMask_21)
#define AE2_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c4c))&BitMask_21)
#define AE3_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c50))&BitMask_21)
#define AE4_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c54))&BitMask_21)
#define AE5_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c58))&BitMask_21)
#define AE6_SLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c5c))&BitMask_21)
#define HISTO0_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c60))&BitMask_21)
#define HISTO1_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c64))&BitMask_21)
#define HISTO2_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c68))&BitMask_21)
#define HISTO3_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c6c))&BitMask_21)
#define HISTO4_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c70))&BitMask_21)
#define HISTO5_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c74))&BitMask_21)
#define HISTO6_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c78))&BitMask_21)
#define HISTO7_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c7c))&BitMask_21)
#define HISTO8_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c80))&BitMask_21)
#define HISTO9_LOCK_EN773Ar				(ValSft_R00(_rd32(0x30020c84))&BitMask_21)
#define AF1_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c88))&BitMask_31)
#define AF1_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c8c))&BitMask_31)
#define AF2_SUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c90))&BitMask_31)
#define AF2_SUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c94))&BitMask_31)
#define AF1_LPSUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c98))&BitMask_21)
#define AF1_LPSUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020c9c))&BitMask_21)
#define AF2_LPSUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020ca0))&BitMask_21)
#define AF2_LPSUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020ca4))&BitMask_21)
#define AF1_CLP_SUM1_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020ca8))&BitMask_31)
#define AF1_CLP_SUM2_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cac))&BitMask_31)
#define AF2_CLP_SUM1_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cb0))&BitMask_31)
#define AF2_CLP_SUM2_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cb4))&BitMask_31)
#define AF1_YSUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cb8))&BitMask_31)
#define AF1_YSUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cbc))&BitMask_31)
#define AF2_YSUM1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cc0))&BitMask_31)
#define AF2_YSUM2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cc4))&BitMask_31)
#define AF1_YLPSUM1_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cc8))&BitMask_21)
#define AF1_YLPSUM2_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020ccc))&BitMask_21)
#define AF2_YLPSUM1_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cd0))&BitMask_21)
#define AF2_YLPSUM2_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cd4))&BitMask_21)
#define AF1_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cd8))&BitMask_21)
#define AF2_CLCNT_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020cdc))&BitMask_21)
#define AWBL_CCR_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020ce0))&BitMask_31)
#define AWBL_CCG_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020ce4))&BitMask_31)
#define AWBL_CCB_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020ce8))&BitMask_31)
#define AWBL_CCT_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cec))&BitMask_21)
#define AWBL_CY_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cf0))&BitMask_31)
#define AWBL_CBDB_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cf4))&BitMask_32)
#define AWBL_CRDR_SUM_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cf8))&BitMask_32)
#define AWBL_R_CLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020cfc))&BitMask_21)
#define AWBL_G_CLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020d00))&BitMask_21)
#define AWBL_B_CLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020d04))&BitMask_21)
#define AWBL_R_SLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020d08))&BitMask_21)
#define AWBL_G_SLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020d0c))&BitMask_21)
#define AWBL_B_SLCNT_LOCK_EN773Ar		(ValSft_R00(_rd32(0x30020d10))&BitMask_21)
#define MPOINT_ADJ_EN773Ar				(ValSft_R00(_rd32(0x30020d14))&BitMask_12)
#define SWGT_ADJ_EN773Ar				(ValSft_R00(_rd32(0x30020d18))&BitMask_12)
#define S1_EN773Ar						(ValSft_R00(_rd32(0x30020d1c))&BitMask_12)
#define S2_EN773Ar						(ValSft_R00(_rd32(0x30020d20))&BitMask_12)
#define SL_RATIO_EN773Ar				(ValSft_R00(_rd32(0x30020d24))&BitMask_12)
#define SGF_SLOPE_EN773Ar				(ValSft_R00(_rd32(0x30020d28))&BitMask_08)
#define SC_EN773Ar						(ValSft_R00(_rd32(0x30020d2c))&BitMask_12)
#define LS_SM_EN773Ar					(ValSft_R00(_rd32(0x30020d30))&BitMask_12)
#define SATV_SUB_MAX_EN773Ar			(ValSft_R00(_rd32(0x30020d34))&BitMask_12)
#define MPOINT_EN773Ar					(ValSft_R00(_rd32(0x30020d38))&BitMask_12)
#define YCRC_ERR_CNT_EN773Ar			(ValSft_R00(_rd32(0x30020d40))&BitMask_11)
#define CCRC_ERR_CNT_EN773Ar			(ValSft_R00(_rd32(0x30020d44))&BitMask_11)
#define CXALMCU_RD08_1_EN773Ar			(ValSft_R00(_rd32(0x30020d4c))&BitMask_32)
#define CXALMCU_RD07_1_EN773Ar			(ValSft_R00(_rd32(0x30020d50))&BitMask_32)
#define CXALMCU_RD06_1_EN773Ar			(ValSft_R00(_rd32(0x30020d54))&BitMask_32)
#define CXALMCU_RD05_1_EN773Ar			(ValSft_R00(_rd32(0x30020d58))&BitMask_32)
#define CXALMCU_RD04_1_EN773Ar			(ValSft_R00(_rd32(0x30020d5c))&BitMask_32)
#define CXALMCU_RD03_1_EN773Ar			(ValSft_R00(_rd32(0x30020d60))&BitMask_32)
#define CXALMCU_RD02_1_EN773Ar			(ValSft_R00(_rd32(0x30020d64))&BitMask_32)
#define CXALMCU_RD01_1_EN773Ar			(ValSft_R00(_rd32(0x30020d68))&BitMask_32)
#define CXALMCU_RD00_1_EN773Ar			(ValSft_R00(_rd32(0x30020d6c))&BitMask_32)
#define CXALMCU_RD08_0_EN773Ar			(ValSft_R00(_rd32(0x30020d80))&BitMask_32)
#define CXALMCU_RD07_0_EN773Ar			(ValSft_R00(_rd32(0x30020d84))&BitMask_32)
#define CXALMCU_RD06_0_EN773Ar			(ValSft_R00(_rd32(0x30020d88))&BitMask_32)
#define CXALMCU_RD05_0_EN773Ar			(ValSft_R00(_rd32(0x30020d8c))&BitMask_32)
#define CXALMCU_RD04_0_EN773Ar			(ValSft_R00(_rd32(0x30020d90))&BitMask_32)
#define CXALMCU_RD03_0_EN773Ar			(ValSft_R00(_rd32(0x30020d94))&BitMask_32)
#define CXALMCU_RD02_0_EN773Ar			(ValSft_R00(_rd32(0x30020d98))&BitMask_32)
#define CXALMCU_RD01_0_EN773Ar			(ValSft_R00(_rd32(0x30020d9c))&BitMask_32)
#define CXALMCU_RD00_0_EN773Ar			(ValSft_R00(_rd32(0x30020da0))&BitMask_32)
#define TX_NR_LOCK_EN773Ar				(ValSft_R31(_rd32(0x30020da8))&BitMask_01)
#define TX_YNEAR_EN773Ar				(ValSft_R08(_rd32(0x30020da8))&BitMask_07)
#define TX_CNEAR_EN773Ar				(ValSft_R00(_rd32(0x30020da8))&BitMask_07)
#define IMD_DEND_EN773Ar				(ValSft_R31(_rd32(0x30020dc0))&BitMask_01)
#define IMD_WCNT1_EN773Ar				(ValSft_R16(_rd32(0x30020dc0))&BitMask_12)
#define IMD_WCNT2_EN773Ar				(ValSft_R00(_rd32(0x30020dc0))&BitMask_12)
#define IMD_WCNT3_EN773Ar				(ValSft_R16(_rd32(0x30020dc4))&BitMask_12)
#define IMD_WCNT4_EN773Ar				(ValSft_R00(_rd32(0x30020dc4))&BitMask_12)
#define SD_MODER_EN773Ar				(ValSft_R00(_rd32(0x30020e00))&BitMask_04)
#define SD_USEPAGE_EN773Ar				(ValSft_R00(_rd32(0x30020e04))&BitMask_21)
#define SD_RDATA0_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e08))&BitMask_32)
#define SD_RDATA1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e0c))&BitMask_32)
#define SD_RDATA2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e10))&BitMask_32)
#define SD_RDATA3_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e14))&BitMask_32)
#define DATA_ECNT0_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e18))&BitMask_10)
#define DATA_ECNT1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e1c))&BitMask_10)
#define DATA_ECNT2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e20))&BitMask_10)
#define DATA_ECNT3_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e24))&BitMask_10)
#define DATA_EDAT0_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e28))&BitMask_08)
#define DATA_EDAT1_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e2c))&BitMask_08)
#define DATA_EDAT2_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e30))&BitMask_08)
#define DATA_EDAT3_LOCK_EN773Ar			(ValSft_R00(_rd32(0x30020e34))&BitMask_08)
#define ADC0_RDAT_EN773Ar				(ValSft_R00(_rd32(0x30020e40))&BitMask_09)
#define ADC1_RDAT_EN773Ar				(ValSft_R00(_rd32(0x30020e44))&BitMask_09)
#define ADC2_RDAT_EN773Ar				(ValSft_R00(_rd32(0x30020e48))&BitMask_09)
#define ADC3_RDAT_EN773Ar				(ValSft_R00(_rd32(0x30020e4c))&BitMask_09)
#define LL_EXMAX_EN773Ar				(ValSft_R00(_rd32(0x30020fc0))&BitMask_24)
#define LL_INMAX_EN773Ar				(ValSft_R00(_rd32(0x30020fc4))&BitMask_24)
#define LL_DIF_EN773Ar					(ValSft_R00(_rd32(0x30020fc8))&BitMask_24)
#define RTRG_ST_EN773Ar					(ValSft_R00(_rd32(0x30020fd0))&BitMask_03)
#define DF_COUNT_EN773Ar				(ValSft_R00(_rd32(0x30020ff8))&BitMask_11)
#define LS_FLAG_TMP_EN773Ar				(ValSft_R00(_rd32(0x30020ffc))&BitMask_01)
