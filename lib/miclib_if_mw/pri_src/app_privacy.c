/*********************************************************************************************************//**
* @file App_pricavy.c
* @author
*  Seahan Kim
* @date 2014.01.10
* @brief
*  Source file of Cannon x10 preset service source
*************************************************************************************************************/
/*************************************************************************************************************
* INCLUDE FILES
*************************************************************************************************************/
#include "kernel.h"
#include "App_privacy.h"
#include "miclib_if_mw.h"
#include "if_user_mw.h"

#include "Lens_mw.h"
#include "Zoom_mw.h"
#include "etcFunc_mw.h"

/*************************************************************************************************************
* LOCAL DEFINES
*************************************************************************************************************/
#define MD_DXr    (ValSft_R00(_rd32(0x30020dc0))&BitMask_19)
#define MD_DYr    (ValSft_R00(_rd32(0x30020dc4))&BitMask_19)


#if	(USE_CNB_OSD_HEX)
#define PRI_Update_ON(evt,zone,dat) 		IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_STATE		,dat)
#define PRI_Update_DISP(evt,zone,dat) 		0
#define PRI_Update_I(evt,zone,dat) 			0
#define PRI_Update_ZONE(evt,zone,dat) 		IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_ZONE		,dat)
#define PRI_Update_MODIFY(evt,zone,dat)		0
#define PRI_Update_TRANS(evt,zone,dat) 		IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_TRANS		,dat)
#define PRI_Update_CR_ON(evt,zone,dat) 		IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_COLOR		,dat)
#define PRI_Update_CR_OFF(evt,zone,dat) 	IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_COLOR		,dat)
#define PRI_Update_X(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_X			,dat)
#define PRI_Update_Y(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_Y			,dat)
#define PRI_Update_W(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_W			,dat)
#define PRI_Update_H(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_H			,dat)
#define PRI_Update_P(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_P			,dat)
#define PRI_Update_T(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_T			,dat)
#define PRI_Update_Z(evt,zone,dat) 			IF_EEPPrivacyUpdate(evt,zone,IDX_PRI_Z			,dat)

#elif	(USE_VISCA_ONLY_PT)

#define PRI_Update_ON(evt,zone,dat) 		IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_ON		,dat)
#define PRI_Update_DISP(evt,zone,dat) 		IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_DISP	,dat)
#define PRI_Update_I(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_I		,dat)
#define PRI_Update_ZONE(evt,zone,dat) 		IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_ZONE	,dat)
#define PRI_Update_MODIFY(evt,zone,dat)		IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_MODIFY	,dat)
#define PRI_Update_TRANS(evt,zone,dat) 		(!IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_TRANS	,dat) ? (3) : (0))
#define PRI_Update_CR_ON(evt,zone,dat) 		IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_COLOR_ON,dat)
#define PRI_Update_CR_OFF(evt,zone,dat) 	IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_COLOR_OFF,dat)
#define PRI_Update_X(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_X_POS	,dat)
#define PRI_Update_Y(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_Y_POS	,dat)
#define PRI_Update_W(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_WIDTH	,dat)
#define PRI_Update_H(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_HEIGHT	,dat)
#define PRI_Update_P(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_P		,dat)
#define PRI_Update_T(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_T		,dat)
#define PRI_Update_Z(evt,zone,dat) 			IF_EEPViscaMaskUpdate(evt,zone,VDX_MASK_Z		,dat)

#endif

/*************************************************************************************************************
* LOCAL CONSTANTS
*************************************************************************************************************/
/*************************************************************************************************************
* LOCAL DATA TYPES
*************************************************************************************************************/
/*************************************************************************************************************
* LOCAL TABLES
*************************************************************************************************************/
/**********************************************************************************
* Table Name : 구면 수차 보정 테이블
* 렌즈는 구면 오차를 가진다.
* 화면 양끝의 화각은 화면 중심부의 화각보다 크다.
* 화면의 끝으로 갈수록 마스크를 강제로 평행이동한다.
**********************************************************************************/
const int08 Tb_Sector_h[13][13] =
{
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//0
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//1
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//2
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//3
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//4
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//5
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//6
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//7
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//8
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//9
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//10
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//11
	{-36,-20,-7,-2,-1,-1,0,1,1,2,7,20,36},	//12
};

const int08 Tb_Sector_v[13][13] =
{
	{-20,-12,-8,-7,-6,-6,0,6,6,7,8,12,20},	//0
	{-19,-11,-7,-6,-5,-5,0,5,5,6,7,11,19},	//1
	{-18,-10,-6,-5,-4,-4,0,4,4,5,6,10,18},	//2
	{-17,-9 ,-5,-4,-3,-3,0,3,3,4,5,9,17},	//3
	{-16,-8 ,-4,-3,-2,-2,0,2,2,3,4,8,16},	//4
	{-15,-7 ,-3,-2,-1,-1,0,1,1,2,3,7,15},	//5
	{-15,-7 ,-3,-2,-1,-1,0,1,1,2,3,7,15},	//6
	{-15,-7 ,-3,-2,-1,-1,0,1,1,2,3,7,15},	//7
	{-16,-8 ,-4,-3,-2,-2,0,2,2,3,4,8,16},	//8
	{-17,-9 ,-5,-4,-3,-3,0,3,3,4,5,9,17},	//9
	{-18,-10,-6,-5,-4,-4,0,4,4,5,6,10,18},	//10
	{-19,-11,-7,-6,-5,-5,0,5,5,2,7,11,19},	//11
	{-20,-12,-8,-7,-6,-6,0,6,6,7,8,12,20},	//12
};


/**********************************************************************************
 식 ArcTan(a)에서
 y가 -90도 < y < 90도

 1. 아크 탄젠트의 입력 a는 -inf < a < +inf (-90도 ~ +90도)까지의 입력을 갖는다.
 >> 테이블이나 수식으로 결과값 표현 불가.
 2.  -1 < a < 1 까지는 (-90도 ~ +90도) 이므로

 a > 1  	이면 90도  - ArcTan(1/a)
 a < -1 	이면 360도 - ArcTan(1/a)
 -1 < a < 1 이면 ArcTan(a)

 가된다.
 따라서 0 <= a <= 1값의 ArcTan값만 가지면 된다.
**********************************************************************************/
const uint16 Tb_ATan[] = {
	0	,1	 ,3   ,4   ,5	,6	 ,8   ,9   ,10	,11  ,
	13	,14  ,15  ,17  ,18	,19  ,20  ,22  ,23	,24  ,
	25	,27  ,28  ,29  ,31	,32  ,33  ,34  ,36	,37  ,
	38	,39  ,41  ,42  ,43	,44  ,46  ,47  ,48	,50  ,
	51	,52  ,53  ,55  ,56	,57  ,58  ,60  ,61	,62  ,
	63	,65  ,66  ,67  ,69	,70  ,71  ,72  ,74	,75  ,
	76	,77  ,79  ,80  ,81	,82  ,84  ,85  ,86	,87  ,
	89	,90  ,91  ,92  ,94	,95  ,96  ,97  ,99	,100 ,
	101 ,102 ,104 ,105 ,106 ,107 ,108 ,110 ,111 ,112 ,
	113 ,115 ,116 ,117 ,118 ,120 ,121 ,122 ,123 ,125 ,
	126 ,127 ,128 ,129 ,131 ,132 ,133 ,134 ,136 ,137 ,
	138 ,139 ,140 ,142 ,143 ,144 ,145 ,146 ,148 ,149 ,
	150 ,151 ,152 ,154 ,155 ,156 ,157 ,159 ,160 ,161 ,
	162 ,163 ,164 ,166 ,167 ,168 ,169 ,170 ,172 ,173 ,
	174 ,175 ,176 ,178 ,179 ,180 ,181 ,182 ,183 ,185 ,
	186 ,187 ,188 ,189 ,190 ,192 ,193 ,194 ,195 ,196 ,
	197 ,199 ,200 ,201 ,202 ,203 ,204 ,206 ,207 ,208 ,
	209 ,210 ,211 ,212 ,214 ,215 ,216 ,217 ,218 ,219 ,
	220 ,222 ,223 ,224 ,225 ,226 ,227 ,228 ,229 ,231 ,
	232 ,233 ,234 ,235 ,236 ,237 ,238 ,239 ,241 ,242 ,
	243 ,244 ,245 ,246 ,247 ,248 ,249 ,250 ,252 ,253 ,
	254 ,255 ,256 ,257 ,258 ,259 ,260 ,261 ,262 ,263 ,
	265 ,266 ,267 ,268 ,269 ,270 ,271 ,272 ,273 ,274 ,
	275 ,276 ,277 ,278 ,279 ,281 ,282 ,283 ,284 ,285 ,
	286 ,287 ,288 ,289 ,290 ,291 ,292 ,293 ,294 ,295 ,
	296 ,297 ,298 ,299 ,300 ,301 ,302 ,303 ,304 ,305 ,
	306 ,307 ,308 ,309 ,310 ,311 ,312 ,313 ,314 ,315 ,
	316 ,317 ,318 ,319 ,320 ,321 ,322 ,323 ,324 ,325 ,
	326 ,327 ,328 ,329 ,330 ,331 ,332 ,333 ,334 ,335 ,
	336 ,337 ,338 ,339 ,340 ,341 ,342 ,343 ,344 ,345 ,
	346 ,346 ,347 ,348 ,349 ,350 ,351 ,352 ,353 ,354 ,
	355 ,356 ,357 ,358 ,359 ,360 ,360 ,361 ,362 ,363 ,
	364 ,365 ,366 ,367 ,368 ,369 ,370 ,371 ,371 ,372 ,
	373 ,374 ,375 ,376 ,377 ,378 ,379 ,379 ,380 ,381 ,
	382 ,383 ,384 ,385 ,386 ,387 ,387 ,388 ,389 ,390 ,
	391 ,392 ,393 ,393 ,394 ,395 ,396 ,397 ,398 ,399 ,
	399 ,400 ,401 ,402 ,403 ,404 ,405 ,405 ,406 ,407 ,
	408 ,409 ,410 ,410 ,411 ,412 ,413 ,414 ,415 ,415 ,
	416 ,417 ,418 ,419 ,419 ,420 ,421 ,422 ,423 ,424 ,
	424 ,425 ,426 ,427 ,428 ,428 ,429 ,430 ,431 ,432 ,
	432 ,433 ,434 ,435 ,435 ,436 ,437 ,438 ,439 ,439 ,
	440 ,441 ,442 ,442 ,443 ,444 ,445 ,446 ,446 ,447 ,
	448 ,449 ,449 ,450 ,451 ,452 ,452 ,453 ,454 ,455 ,
	455 ,456 ,457 ,458 ,458 ,459 ,460 ,461 ,461 ,462 ,
	463 ,464 ,464 ,465 ,466 ,466 ,467 ,468 ,469 ,469 ,
	470 ,471 ,471 ,472 ,473 ,474 ,474 ,475 ,476 ,476 ,
	477 ,478 ,479 ,479 ,480 ,481 ,481 ,482 ,483 ,483 ,
	484 ,485 ,486 ,486 ,487 ,488 ,488 ,489 ,490 ,490 ,
	491 ,492 ,492 ,493 ,494 ,494 ,495 ,496 ,496 ,497 ,
	498 ,498 ,499 ,500 ,500 ,501 ,502 ,502 ,503 ,504 ,
	504 ,505 ,506 ,506 ,507 ,508 ,508 ,509 ,509 ,510 ,
	511 ,511 ,512
};//0~512 : 513 개

const uint16 Tb_SIN[] = {
		0		,		101 	,		201 	,		302 	,		402 	,		503 	,		603 	,		704 	,
		804 	,		905 	,		1005	,		1106	,		1206	,		1307	,		1407	,		1508	,		1608	,
		1709	,		1809	,		1910	,		2010	,		2111	,		2211	,		2312	,		2412	,		2513	,
		2613	,		2714	,		2814	,		2914	,		3015	,		3115	,		3216	,		3316	,		3417	,
		3517	,		3617	,		3718	,		3818	,		3918	,		4019	,		4119	,		4219	,		4320	,
		4420	,		4520	,		4621	,		4721	,		4821	,		4921	,		5022	,		5122	,		5222	,
		5322	,		5422	,		5523	,		5623	,		5723	,		5823	,		5923	,		6023	,		6123	,
		6224	,		6324	,		6424	,		6524	,		6624	,		6724	,		6824	,		6924	,		7024	,
		7124	,		7224	,		7323	,		7423	,		7523	,		7623	,		7723	,		7823	,		7923	,
		8022	,		8122	,		8222	,		8322	,		8421	,		8521	,		8621	,		8720	,		8820	,
		8919	,		9019	,		9119	,		9218	,		9318	,		9417	,		9517	,		9616	,		9716	,
		9815	,		9914	,		10014	,		10113	,		10212	,		10312	,		10411	,		10510	,		10609	,
		10709	,		10808	,		10907	,		11006	,		11105	,		11204	,		11303	,		11402	,		11501	,
		11600	,		11699	,		11798	,		11897	,		11996	,		12095	,		12193	,		12292	,		12391	,
		12490	,		12158	,		12687	,		12785	,		12884	,		12983	,		13081	,		13180	,		13278	,
		13376	,		13475	,		13573	,		13672	,		13770	,		13868	,		13966	,		14065	,		14163	,
		14261	,		14359	,		14457	,		14555	,		14653	,		14751	,		14849	,		14947	,		15045	,
		15143	,		15240	,		15338	,		15436	,		15534	,		15631	,		15729	,		15826	,		15924	,
		16021	,		16119	,		16216	,		16314	,		16411	,		16508	,		16606	,		16703	,		16800	,
		16897	,		16994	,		17091	,		17188	,		17285	,		17382	,		17479	,		17576	,		17673	,
		17770	,		17867	,		17963	,		18060	,		18156	,		18253	,		18350	,		18446	,		18543	,
		18639	,		18735	,		18832	,		18928	,		19024	,		19120	,		19216	,		19313	,		19409	,
		19505	,		19600	,		19696	,		19792	,		19888	,		19984	,		20080	,		20175	,		20271	,
		20366	,		20462	,		20557	,		20653	,		20748	,		20844	,		20939	,		21034	,		21129	,
		21224	,		21320	,		21415	,		21510	,		21604	,		21699	,		21794	,		21889	,		21984	,
		22078	,		22173	,		22268	,		22362	,		22457	,		22551	,		22645	,		22740	,		22834	,
		22928	,		23022	,		23116	,		23210	,		23304	,		23398	,		23492	,		23586	,		23680	,
		23774	,		23867	,		23961	,		24054	,		24148	,		24241	,		24335	,		24428	,		24521	,
		24614	,		24708	,		24801	,		24894	,		24987	,		25080	,		25172	,		25265	,		25358	,
		25451	,		25543	,		25636	,		25728	,		25821	,		25913	,		26005	,		26098	,		26190	,
		26282	,		26374	,		26466	,		26558	,		26650	,		26742	,		26833	,		26925	,		27017	,
		27108	,		27200	,		27291	,		27382	,		27474	,		27565	,		27656	,		27747	,		27838	,
		27929	,		28020	,		28111	,		28202	,		28293	,		28383	,		28474	,		28564	,		28655	,
		28745	,		28835	,		28926	,		29016	,		29106	,		29196	,		29286	,		29376	,		29466	,
		29555	,		29645	,		29735	,		29824	,		29914	,		30003	,		30093	,		30182	,		30271	,
		30360	,		30449	,		30538	,		30627	,		30716	,		30805	,		30893	,		30982	,		31071	,
		31159	,		31248	,		31336	,		31424	,		31512	,		31600	,		31688	,		31776	,		31864	,
		31952	,		32040	,		32127	,		32215	,		32303	,		32390	,		32477	,		32565	,		32652	,
		32739	,		32826	,		32913	,		33000	,		33087	,		33173	,		33260	,		33347	,		33433	,
		33520	,		33606	,		33692	,		33778	,		33865	,		33951	,		34037	,		34122	,		34208	,
		34294	,		34380	,		34465	,		34551	,		34636	,		34721	,		34806	,		34892	,		34977	,
		35062	,		35146	,		35231	,		35316	,		35401	,		35485	,		35570	,		35654	,		35738	,
		35823	,		35907	,		35991	,		36075	,		36159	,		36243	,		36326	,		36410	,		36493	,
		36577	,		36660	,		36744	,		36827	,		36910	,		36993	,		37076	,		37159	,		37241	,
		37324	,		37407	,		37489	,		37572	,		37654	,		37736	,		37818	,		37900	,		37982	,
		38064	,		38146	,		38228	,		38309	,		38391	,		38472	,		38554	,		38635	,		38716	,
		38797	,		38878	,		38959	,		39040	,		39120	,		39201	,		39282	,		39362	,		39442	,
		39523	,		39603	,		39683	,		39763	,		39843	,		39922	,		40002	,		40082	,		40161	,
		40241	,		40320	,		40399	,		40478	,		40557	,		40636	,		40715	,		40794	,		40872	,
		40951	,		41029	,		41108	,		41186	,		41264	,		41342	,		41420	,		41498	,		41576	,
		41653	,		41731	,		41808	,		41886	,		41963	,		42040	,		42117	,		42194	,		42271	,
		42348	,		42424	,		42501	,		42578	,		42654	,		42730	,		42806	,		42882	,		42958	,
		43034	,		43110	,		43186	,		43261	,		43337	,		43412	,		43487	,		43562	,		43638	,
		43713	,		43787	,		43862	,		43937	,		44011	,		44086	,		44160	,		44234	,		44308	,
		44382	,		44456	,		44530	,		44604	,		44677	,		44751	,		44824	,		44898	,		44971	,
		45044	,		45117	,		45190	,		45262	,		45335	,		45408	,		45480	,		45552	,		45625	,
		45697	,		45769	,		45841	,		45912	,		45984	,		46056	,		46127	,		46199	,		46270	,
		46341	,		46412	,		46483	,		46554	,		46624	,		46695	,		46765	,		46836	,		46906	,
		46976	,		47046	,		47116	,		47186	,		47256	,		47325	,		47395	,		47464	,		47534	,
		47603	,		47672	,		47741	,		47809	,		47878	,		47947	,		48015	,		48084	,		48152	,
		48220	,		48288	,		48356	,		48424	,		48491	,		48559	,		48626	,		48694	,		48761	,
		48828	,		48895	,		48962	,		49029	,		49095	,		49162	,		49228	,		49295	,		49361	,
		49427	,		49493	,		49559	,		49624	,		49690	,		49756	,		49821	,		49886	,		49951	,
		50016	,		50081	,		50146	,		50211	,		50275	,		50340	,		50404	,		50468	,		50532	,
		50596	,		50660	,		50724	,		50787	,		50851	,		50914	,		50977	,		51041	,		51104	,
		51166	,		51229	,		51292	,		51354	,		51417	,		51479	,		51541	,		51603	,		51665	,
		51727	,		51789	,		51850	,		51911	,		51973	,		52034	,		52095	,		52156	,		52217	,
		52277	,		52338	,		52398	,		52459	,		52519	,		52579	,		52639	,		52699	,		52759	,
		52818	,		52878	,		52937	,		52996	,		53055	,		53114	,		53173	,		53232	,		53290	,
		53349	,		53407	,		53465	,		53523	,		53581	,		53639	,		53697	,		53754	,		53812	,
		53869	,		53926	,		53983	,		54040	,		54097	,		54154	,		54210	,		54267	,		54323	,
		54379	,		54435	,		54491	,		54547	,		54603	,		54658	,		54714	,		54769	,		54824	,
		54879	,		54934	,		54989	,		55043	,		55098	,		55152	,		55206	,		55260	,		55314	,
		55368	,		55422	,		55476	,		55529	,		55582	,		55636	,		55689	,		55742	,		55794	,
		55847	,		55900	,		55952	,		56004	,		56056	,		56108	,		56160	,		56212	,		56264	,
		56315	,		56367	,		56418	,		56469	,		56520	,		56571	,		56621	,		56672	,		56722	,
		56773	,		56823	,		56873	,		56923	,		56972	,		57022	,		57072	,		57121	,		57170	,
		57219	,		57268	,		57317	,		57366	,		57414	,		57463	,		57511	,		57559	,		57607	,
		57655	,		57703	,		57750	,		57798	,		57845	,		57892	,		57939	,		57986	,		58033	,
		58079	,		58126	,		58172	,		58219	,		58265	,		58311	,		58356	,		58402	,		58448	,
		58493	,		58538	,		58583	,		58628	,		58673	,		58718	,		58763	,		58807	,		58851	,
		58896	,		58940	,		58983	,		59027	,		59071	,		59114	,		59158	,		59201	,		59244	,
		59287	,		59330	,		59372	,		59415	,		59457	,		59499	,		59541	,		59583	,		59625	,
		59667	,		59708	,		59750	,		59791	,		59832	,		59873	,		59914	,		59954	,		59995	,
		60035	,		60075	,		60116	,		60156	,		60195	,		60235	,		60275	,		60314	,		60353	,
		60392	,		60431	,		60470	,		60509	,		60547	,		60586	,		60624	,		60662	,		60700	,
		60738	,		60776	,		60813	,		60851	,		60888	,		60925	,		60962	,		60999	,		61035	,
		61072	,		61108	,		61145	,		61181	,		61217	,		61253	,		61288	,		61324	,		61359	,
		61394	,		61429	,		61464	,		61499	,		61534	,		61568	,		61603	,		61637	,		61671	,
		61705	,		61739	,		61772	,		61806	,		61839	,		61873	,		61906	,		61939	,		61971	,
		62004	,		62036	,		62069	,		62101	,		62133	,		62165	,		62197	,		62228	,		62260	,
		62291	,		62322	,		62353	,		62384	,		62415	,		62445	,		62476	,		62506	,		62536	,
		62566	,		62596	,		62626	,		62655	,		62685	,		62714	,		62743	,		62772	,		62801	,
		62830	,		62858	,		62886	,		62915	,		62943	,		62971	,		62998	,		63026	,		63054	,
		63081	,		63108	,		63135	,		63162	,		63189	,		63215	,		63242	,		63268	,		63294	,
		63320	,		63346	,		63372	,		63397	,		63423	,		63448	,		63473	,		63498	,		63523	,
		63547	,		63572	,		63596	,		63621	,		63645	,		63668	,		63692	,		63716	,		63739	,
		63763	,		63786	,		63809	,		63832	,		63854	,		63877	,		63899	,		63922	,		63944	,
		63966	,		63987	,		64009	,		64031	,		64052	,		64073	,		64094	,		64115	,		64136	,
		64156	,		64177	,		64197	,		64217	,		64237	,		64257	,		64277	,		64296	,		64316	,
		64335	,		64354	,		64373	,		64392	,		64410	,		64429	,		64447	,		64465	,		64483	,
		64501	,		64519	,		64536	,		64554	,		64571	,		64588	,		64605	,		64622	,		64639	,
		64655	,		64672	,		64688	,		64704	,		64720	,		64735	,		64751	,		64766	,		64782	,
		64797	,		64812	,		64827	,		64841	,		64856	,		64870	,		64884	,		64899	,		64912	,
		64926	,		64940	,		64953	,		64967	,		64980	,		64993	,		65006	,		65018	,		65031	,
		65043	,		65055	,		65067	,		65079	,		65091	,		65103	,		65114	,		65126	,		65137	,
		65148	,		65159	,		65169	,		65180	,		65190	,		65200	,		65210	,		65220	,		65230	,
		65240	,		65249	,		65259	,		65268	,		65277	,		65286	,		65294	,		65303	,		65311	,
		65320	,		65328	,		65336	,		65343	,		65351	,		65358	,		65366	,		65373	,		65380	,
		65387	,		65393	,		65400	,		65406	,		65413	,		65419	,		65425	,		65430	,		65436	,
		65442	,		65447	,		65452	,		65457	,		65462	,		65467	,		65471	,		65476	,		65480	,
		65484	,		65488	,		65492	,		65495	,		65499	,		65502	,		65505	,		65508	,		65511	,
		65514	,		65516	,		65519	,		65521	,		65523	,		65525	,		65527	,		65528	,		65530	,
		65531	,		65532	,		65533	,		65534	,		65535	,		65535	,		65535	,		65535	,		65535	,
};

/*************************************************************************************************************
* LOCAL GLOBAL VARIABLES
*************************************************************************************************************/
uint08 draw_flag_H = 0;
uint08 draw_flag_V = 0;
uint16 gTILT_Old;
uint16 gPAN_Old;

uint08 pricacy_flag  = 1;
uint08 pricacy_flag2 = 0;

//Temp 데이터
static uint08 Mask_Dbg_flg = 0;
static uint08 Mask_Dbg_State = 0;
static uint08 Mask_Dbg_I = 0;
static uint08 Mask_Dbg_disp = 0;
static uint16 Mask_Dbg_Pan = 0;
static uint16 Mask_Dbg_Tilt = 0;
static uint16 Mask_Dbg_Zoom = 0;
static uint16 Mask_Dbg_x = 0;
static uint16 Mask_Dbg_y = 0;
static uint16 Mask_Dbg_cr = 0;
static uint08 Mask_Dbg_Widht = 0;
static uint08 Mask_Dbg_Height = 0;
static uint08 Mask_Dbg_Line = 0;


static int32  nScrXCenterAdj;
static int32  nScrYCenterAdj;
static uint16 nFov_H_Max;
static uint16 nFov_H_Min;
static uint16 nFov_V_Max;
static uint16 nFov_V_Min;

static uint16 nScrTopEnd;
static uint16 nScrBottomEnd;
static uint16 nScrLeftEnd;
static uint16 nScrRightEnd;
static int32 nScrXCenter;
static int32 nScrYCenter;
static int32 nScrWidht;
static int32 nScrHeight;

static uint16 gPAN_Curr ;
static uint16 gTILT_Curr;
static uint16 gZOOM_Curr;
static uint16 gCurr_FOV_V;
static uint16 gCurr_FOV_H;

static int32 gAdjX[MAX_PRIVACYZONE];
static int32 gAdjY[MAX_PRIVACYZONE];

static int16 PAN_Tab ;
static int16 TILT_Tab;

int32 dbg_data[25];
PRIVACY_ZONE_       PrivZone[MAX_PRIVACYZONE];
volatile MASK_EVENT MaskEvent;

int32 Panmove[MAX_PRIVACYZONE][5];
int32 Tiltmove[MAX_PRIVACYZONE][5];

/*************************************************************************************************************
* LOCAL FUNCTION PROTOTYPES
*************************************************************************************************************/
static int32 mzapi_sin_16fp(int16 s_angle);
static int32 mzapi_cos_16fp(int16 s_angle);
#if (POLYGON_TYPE == 0)
static int32 _mzapi_sin_16fp_(int16 s_angle);
static int32 _mzapi_cos_16fp_(int16 s_angle);
#endif

static void SetNonInterlockPrivacyMask(uint08 index);
static void SetInterlockPrivacyMask(uint08 index);
static void SetPrivacyMask(void);
static void SetInterlockPrivacyMask(uint08 index);
static void SetPrivacyNullMask(uint08 index);
//static void LensUpdate(void);
/*************************************************************************************************************
* LOCAL CONFIGURATION ERRORS
*************************************************************************************************************/

/*************************************************************************************************************
**************************************************************************************************************
* LOCAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/
/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  SetPrivacyMask
*************************************************************************************************************/
void SetPrivacyMask(void)
{
	uint08 i =0;

	for (i = 0; i < MAX_PRIVACYZONE; i++)
	{
		if(((PRI_Update_I(IFEVT_GETVAL,i,0) == STATE_ON)))
			SetNonInterlockPrivacyMask(i);
		else
			SetInterlockPrivacyMask(i);
	}
}
/*********************************************************************************************************//**
* @param[in] param_a
* @param[in] param_b
* @param[in] spot_x
* @param[in] spot_y
* @param[out] none
* @retval Arctan(a)
* @brief
*  SetPrivacyMask
*************************************************************************************************************/
uint16 ArcTan_Privacy(int32 param_a,int32 param_b,int32 spot_x,int32 spot_y)
{
	//	a,b값과 x,y값을 이용해서 타원의 접선을 구하고
	//	접선의 기율기를 구한다.(0~1 사이로)

	float x1,y1;
	uint08 flgX,flgY,flgA,flgs;

	int32 a;

	x1 = (float)param_a*(float)param_a*(float)spot_y;
	y1 = (float)param_b*(float)param_b*(float)spot_x;
	//사분면 찾기
	flgX = (spot_x == 0) ?  0 : (spot_x 	< 0		);
	flgY = (spot_y == 0) ?  0 : (spot_y 	< 0		);
	//음수 -> 양수
	if(x1<0)	x1 *= -1;
	if(y1<0)	y1 *= -1;

	flgA = (x1	>=	y1);
	//기울기 -> 각도

	if(flgA)
	{
		a = Tb_ATan[(uint16)(y1*512/x1)];
	}
	else
	{
		a = Tb_ATan[(uint16)(x1*512/y1)];
	}

	flgs = (flgY<<1)|(flgX);

	switch(flgs)
	{
		case 0x00://4사분면		000~090
			if(!flgA)	//a>0 , 90	~ 45
				a = 1024 - a;
			//else		//a<0 , 0	~ 45
			//	a = a;
		break;

		case 0x01://3사분면		270~360
			if(flgA)	//a<0 , 360 ~ 315
				a = 4096 - a;
			else		//a>0 , 270 ~ 315
				a = 3072 + a;
		break;

		case 0x02://1사분면
			if(flgA)	//a<0 , 180 ~ 135
				a = 2048 - a;
			else		//a>0 , 090 ~ 135
				a = 1024 + a;
		break;

		case 0x03://2사분면
			if(flgA)	//a<0 , 180 ~ 215
				a = 2048 + a;
			else		//a>0 , 270 ~ 215
				a = 3072 - a;
		break;
	}

	return a;
}
/*********************************************************************************************************//**
* @param[in] input : x^2
* @retval x
* @brief
*  x^2의 제곱근을 구한다.\n
*  초기값이 해에 가까울수록 계산속도가 빨라진다.\n
*  따라서 Sin Table의 평균값인 41713의 제곱근은 초기갑 x로 뒀다.
*************************************************************************************************************/
uint32 Sqrt_Privacy(uint32 input)
{
	uint08 i;
	uint32 x = 204;//Sin값의 전체 평균(41713)의 Sqrt값.

	for(i=0;i<11;i++)
	{
		x = (x+(input/x))/2;
	}

	return x;
}

/*********************************************************************************************************//**
* @param[in] index : Mask index
* @param[out] none
* @retval none
* @brief
*	Creat a Privacy Mask (Non inter lock)
*************************************************************************************************************/
void SetNonInterlockPrivacyMask(uint08 index)
{
#if 1
	if ((PRI_Update_ON(IFEVT_GETVAL,index,0) != STATE_ON))//||(g_OsdData.FLD.MASK_ON!= STATE_ON))
	{
		SetPrivacyNullMask(index);
		if(index == 1) dbg_data[0]++;
		return;
	}
	int32 tmp_x = PRI_Update_X(IFEVT_GETVAL,index,0);
	int32 tmp_y = PRI_Update_Y(IFEVT_GETVAL,index,0);
	int32 tmp_w = PRI_Update_W(IFEVT_GETVAL,index,0);
	int32 tmp_h = PRI_Update_H(IFEVT_GETVAL,index,0);
	uint08 color = 0;
	uint08 trans = 0;

	if(tmp_x & 0x80)	tmp_x |= 0xffffff00;
	if(tmp_y & 0x80)	tmp_y |= 0xffffff00;
	if(tmp_w & 0x80)	tmp_w = ~(tmp_w|0xffffff00) + 1;	//음수 -> 양수
	if(tmp_h & 0x80)	tmp_h = ~(tmp_h|0xffffff00) + 1;

	tmp_x += 0x50;
	tmp_y += 0x2d;

	dbg_data[1] = tmp_x;
	dbg_data[2] = tmp_y;
	dbg_data[3] = tmp_w;
	dbg_data[4] = tmp_h;

	PrivZone[index].MaskArea.left  = 0x7000 + nScrLeftEnd + ((tmp_x - tmp_w) * nScrWidht) / 0xA0;
	PrivZone[index].MaskArea.right = 0x7000 + nScrLeftEnd + ((tmp_x + tmp_w) * nScrWidht) / 0xA0;
	PrivZone[index].MaskArea.top   = 0x7000 + nScrTopEnd + ((tmp_y + tmp_h) * nScrHeight) / 0x5A;
	PrivZone[index].MaskArea.bottom= 0x7000 + nScrTopEnd + ((tmp_y - tmp_h) * nScrHeight) / 0x5A;

	if(PRI_Update_DISP(IFEVT_GETVAL,index,0))
		color = PRI_Update_CR_ON(IFEVT_GETVAL,index,0);
	else
		color = PRI_Update_CR_OFF(IFEVT_GETVAL,index,0);

	PRM_On(index,1);
	PRM_Pos_Pol(index,
				PrivZone[index].MaskArea.left,PrivZone[index].MaskArea.top,
				PrivZone[index].MaskArea.right,PrivZone[index].MaskArea.top,
				PrivZone[index].MaskArea.right,PrivZone[index].MaskArea.bottom,
				PrivZone[index].MaskArea.left,PrivZone[index].MaskArea.bottom);
	Panmove[index][0] = PrivZone[index].MaskArea.left;
	Panmove[index][1] = PrivZone[index].MaskArea.right;
	Panmove[index][2] = PrivZone[index].MaskArea.right;
	Panmove[index][3] = PrivZone[index].MaskArea.left;
	Tiltmove[index][0] = PrivZone[index].MaskArea.top;
	Tiltmove[index][1] = PrivZone[index].MaskArea.top;
	Tiltmove[index][2] = PrivZone[index].MaskArea.bottom;
	Tiltmove[index][3] = PrivZone[index].MaskArea.bottom;

	trans = PRI_Update_TRANS(IFEVT_GETVAL,index,0);

	color &= 0xf;

	PRM_Attr(index,color,trans);
#endif

}

/*********************************************************************************************************//**
* @param[in] index : Mask index
* @param[out] none
* @retval none
* @brief
*	Creat a Privacy Mask (inter lock)
*************************************************************************************************************/
void SetInterlockPrivacyMask(uint08 index)
{
	if ((PRI_Update_ON(IFEVT_GETVAL,index,0) != STATE_ON))
	{
		SetPrivacyNullMask(index);
		if(index == 1) dbg_data[0]++;
		return;
	}
	static uint08 flg1;//,flg2,flg3;
	uint08 i = index;
	uint08 j = 0;
	uint16 nDrowFlag = 0;
	int32 idwVal;
	uint08 color = 0;
	uint08 trans = 0;

	if(PRI_Update_DISP(IFEVT_GETVAL,index,0))
		color = PRI_Update_CR_ON(IFEVT_GETVAL,index,0);
	else
		color = PRI_Update_CR_OFF(IFEVT_GETVAL,index,0);

	int16 curPan   = IF_GetCurPan();
	int16 curTilt  = IF_GetCurTilt();

	int16 maskPan  = PRI_Update_P(IFEVT_GETVAL,index,0);
	int16 maskTilt = PRI_Update_T(IFEVT_GETVAL,index,0);

	uint16 curPanOri   = curPan;// + gAdjX[index])&0xfff;
	uint16 maskPanOri  = maskPan;
	uint16 curTiltOri  = curTilt;// + gAdjY[index])&0xfff;
	uint16 maskTiltOri = maskTilt;

	int32 sFOVPan     = 0;
	int32 sFOVPanOri  = 0;
	int32 sFOVTilt    = 0;
	int32 sFOVTiltOri = 0;
	int32 deltaTilt = 0;

	int32 fovh = Lens_get_current_FOV(FOV_TYPE_H)/100;
	int32 fovv = Lens_get_current_FOV(FOV_TYPE_V)/100;

	int16 PanDis  = PrivZone[index].Width;
	int16 TiltDis = PrivZone[index].Height;

	int32 cal_param_a =0;
	int32 cal_param_b =0;
	int32 cal_param_c =0;

	int32 cal_param_r = 0;
	int32 cal_param_rx = 0;
	int32 cal_param_ry = 0;
	int32 cal_param_rz = 0;
	int32 cal_param_rx_ = 0;
	int32 cal_param_ry_ = 0;
	int32 cal_param_sqrtx = 0;
	int32 cal_param_sqrty = 0;
	int32 cal_param_width = 0;
	int32 cal_param_height = 0;
	//사각형의 x,y 축 회전에 대한...
	int32 cal_param_z1 = 0;
	int32 cal_param_z2 = 0;
	int32 cal_param_zx_pos = 0;
	int32 cal_param_zy_pos = 0;
	int32 cal_param_z_pos1 = 0;
	int32 cal_param_z_pos2 = 0;

	int32 cal_Lens_dx;
	int32 cal_Lens_dy;

	if(Mask_Dbg_flg && (index ==0))
	{
		curPan  = 0;
		curTilt = 0;
	}

	int32 cal_dZoom_x = ZHSP_KXr;
	int32 cal_dZoom_y = ZVSP_KYr;

	if(PanDis==0||TiltDis==0)
	{
		SetPrivacyNullMask(index);
		if(index == 1) dbg_data[1]++;
		return;
	}

	maskPan  = maskPanOri;
	maskTilt = maskTiltOri;

	maskPanOri	 = maskPan;
	maskTiltOri  = maskTilt;

	sFOVPanOri  = ((int32)maskPanOri  - (int32)curPanOri  )&(int32)0x00000fff;
	sFOVTiltOri = ((int32)maskTiltOri - (int32)curTiltOri )&(int32)0x00000fff;

	cal_param_r = 0x0fff;
	//디폴트 값으로 설정함.
	//원의 반지름 : 임의의 값으로 설정해도 무방하다.
	/************************************************************/
	//															//
	// 															//
	// 															//
	/************************************************************/
	/**********************************************************************
		마스크가 ZY면의 기울기에 따라서 XY면에 주사될때의 Height 변화량
	**********************************************************************/
	cal_param_rz = cal_param_r * mzapi_cos_16fp(maskTiltOri);
	cal_param_rz >>= 15;
	cal_param_rz *= mzapi_cos_16fp(curTiltOri);
	cal_param_rz >>= 15;

	cal_param_z1 = cal_param_r * mzapi_sin_16fp(maskTiltOri);
	cal_param_z1 >>= 15;
	cal_param_z1 *= mzapi_sin_16fp(curTiltOri);
	cal_param_z1 >>= 15;

	cal_param_ry_ = cal_param_r * mzapi_cos_16fp(maskTiltOri);
	cal_param_ry_ >>= 15;
	cal_param_ry_ *= mzapi_sin_16fp(curTiltOri);
	cal_param_ry_ >>= 15;

	cal_param_z2 = cal_param_r * mzapi_sin_16fp(maskTiltOri);
	cal_param_z2 >>= 15;
	cal_param_z2 *= mzapi_cos_16fp(curTiltOri);
	cal_param_z2 >>= 15;

	cal_param_z_pos1 = cal_param_z1 + ((cal_param_rz  * mzapi_cos_16fp(sFOVPanOri))>>15);
	cal_param_zy_pos = cal_param_z2 - ((cal_param_ry_ * mzapi_cos_16fp(sFOVPanOri))>>15);

	cal_param_sqrty = Sqrt_Privacy(cal_param_z_pos1*cal_param_z_pos1 + cal_param_zy_pos*cal_param_zy_pos);
	cal_param_height = PrivZone[index].Height * cal_param_z_pos1 / cal_param_sqrty;

	/**********************************************************************
		마스크가 ZX면의 기울기에 따라서 XY면에 주사될때의 Width 변화량
	**********************************************************************/
	cal_param_rz = cal_param_r * mzapi_cos_16fp(maskPanOri);
	cal_param_rz >>= 15;
	cal_param_rz *= mzapi_cos_16fp(curPanOri);
	cal_param_rz >>= 15;

	cal_param_z1 = cal_param_r * mzapi_sin_16fp(maskPanOri);
	cal_param_z1 >>= 15;
	cal_param_z1 *= mzapi_sin_16fp(curPanOri);
	cal_param_z1 >>= 15;

	cal_param_rx_ = cal_param_r * mzapi_cos_16fp(maskPanOri);
	cal_param_rx_ >>= 15;
	cal_param_rx_ *= mzapi_sin_16fp(curPanOri);
	cal_param_rx_ >>= 15;

	cal_param_z2 = cal_param_r * mzapi_sin_16fp(maskPanOri);
	cal_param_z2 >>= 15;
	cal_param_z2 *= mzapi_cos_16fp(curPanOri);
	cal_param_z2 >>= 15;

	cal_param_z_pos2 = cal_param_z1 + ((cal_param_rz  * mzapi_cos_16fp(sFOVTiltOri))>>15);
	cal_param_zx_pos = cal_param_z2 - ((cal_param_rx_ * mzapi_cos_16fp(sFOVTiltOri))>>15);

	cal_param_sqrtx = Sqrt_Privacy(cal_param_z_pos2*cal_param_z_pos2 + cal_param_zx_pos*cal_param_zx_pos);
	cal_param_width = PrivZone[index].Width * cal_param_z_pos2 / cal_param_sqrtx;
	cal_param_width = (PrivZone[index].Width + cal_param_width)/2;

	if(cal_param_z_pos1 >= 0 && cal_param_z_pos2 >= 0)
	{
		nDrowFlag = 1;
	}
	else
	{
		deltaTilt = sFOVTiltOri;
		if(deltaTilt & 0x800)
		{
			deltaTilt = (~deltaTilt + 1) & 0xFFF;
		}
		if(index==0)
		{
			flg1 &= 1;
		}

		if(deltaTilt > 1023)
			nDrowFlag = 1;
	}
	if(nDrowFlag)
	{
		cal_param_rx = nScrWidht;
		cal_param_rx <<= 16;
		cal_param_rx /= mzapi_sin_16fp((fovh+1)>>1);
		cal_param_rx *= mzapi_cos_16fp((fovh+1)>>1)>>1;
		cal_param_rx >>= 14;

		cal_param_ry = nScrHeight;
		cal_param_ry <<= 16;
		cal_param_ry /= mzapi_sin_16fp((fovv+1)>>1);
		cal_param_ry *= mzapi_cos_16fp((fovv+1)>>1)>>1;
		cal_param_ry >>= 14;
		/************************************************************
			Mask의 이동경로가 타원이라는 가정하에 만든 식이다.
		************************************************************/
		idwVal 		= (0x00000400 -(curTiltOri + sFOVTiltOri))&0x00000fff;

		cal_param_a = mzapi_cos_16fp(idwVal)*mzapi_cos_16fp(curTiltOri);
		cal_param_a >>= 15;
		cal_param_b = mzapi_sin_16fp(sFOVTiltOri);
		cal_param_c = mzapi_sin_16fp(idwVal);

		sFOVTilt =	(cal_param_a-cal_param_b)*mzapi_cos_16fp(sFOVPanOri) + (1<<14);
		sFOVTilt >>= 15;

		sFOVPan  =	cal_param_c * mzapi_sin_16fp(sFOVPanOri) + (1<<14);
		sFOVPan  >>= 15;

		sFOVPan  =	cal_param_rx * sFOVPan + (1<<16);
		sFOVPan  >>= 17;

		if(mzapi_cos_16fp(curTiltOri) == 0)
			idwVal = sFOVPanOri;
		else
			idwVal = ArcTan_Privacy((cal_param_rx*(cal_param_c)+ (1<<16))>>17,(cal_param_ry*(cal_param_a-cal_param_b) + (1<<16))>>17,sFOVPan,(cal_param_ry*sFOVTilt+ (1<<16))>>17);

		sFOVTilt =	cal_param_ry*(cal_param_a - sFOVTilt)  + (1<<16);
		sFOVTilt >>= 17;

		sFOVPan  += gAdjX[index];
		sFOVTilt += gAdjY[index];

		if(g_ViscaData.FLD.FLIP_ON)
		{
			sFOVTilt = ~sFOVTilt + 1;// + 5;
		}

		if(g_ViscaData.FLD.LR_ON)
		{
			sFOVPan = ~sFOVPan + 1;// + 12;
		}

		sFOVPan  += 3;
		sFOVTilt += 2;

		// 렌즈의 구면 오차를 보정해준다.
		// 중심에서 멀어질수록 마스크의 중심점을 더 바깥으로 빼준다.
		cal_Lens_dx = (7*sFOVPan)/(nScrWidht>>1);
		cal_Lens_dy = (7*sFOVTilt)/(nScrHeight>>1);
		if(cal_Lens_dx > 6)			cal_Lens_dx = 6;
		else if(cal_Lens_dx < -6)	cal_Lens_dx = -6;

		if(cal_Lens_dy > 6)			cal_Lens_dy = 6;
		else if(cal_Lens_dy < -6)	cal_Lens_dy = -6;

		sFOVPan += Tb_Sector_h[6 + cal_Lens_dy][6 + cal_Lens_dx];
		sFOVTilt += Tb_Sector_v[6 + cal_Lens_dx][6 + cal_Lens_dy];

#if POLYGON_TYPE		// To Poligon
		Panmove[index][0]  = (cal_param_width >>1);
		Tiltmove[index][0] = (cal_param_height >>1);

		Panmove[index][1]  = - (cal_param_width >>1);
		Tiltmove[index][1] = (cal_param_height >>1);

		Panmove[index][2]  = -(cal_param_width >>1);
		Tiltmove[index][2] = - (cal_param_height >>1);

		Panmove[index][3]  = (cal_param_width >>1);
		Tiltmove[index][3] = -(cal_param_height >>1);

		for(j = 0;j<4;j++)
		{
			//사각형의 중심을 기준으로 회전 : '타원접선의 기울기'의 각도만큼
			Panmove[index][4] = Panmove[index][j]*mzapi_cos_16fp(idwVal) - Tiltmove[index][j]*mzapi_sin_16fp(idwVal);
			Panmove[index][4] >>= 15;
			Tiltmove[index][4]= Panmove[index][j]*mzapi_sin_16fp(idwVal) + Tiltmove[index][j]*mzapi_cos_16fp(idwVal);
			Tiltmove[index][4] >>= 15;

			Panmove[index][j] = (sFOVPan  + ((Panmove[index][4]  * nScrWidht  + 0x7f)>>8));
			Tiltmove[index][j] = ( sFOVTilt + ((Tiltmove[index][4] * nScrHeight + 0x7f)>>8));
		}

#else
		// 직사각형 확장
		Panmove[index][4]  = (cal_param_width >>1)*_mzapi_cos_16fp_(idwVal) + (cal_param_height>>1)*_mzapi_sin_16fp_(idwVal);
		Tiltmove[index][4] = (cal_param_height>>1)*_mzapi_cos_16fp_(idwVal) + (cal_param_width>>1)*_mzapi_sin_16fp_(idwVal);
		Panmove[index][4]  >>= 15;
		Tiltmove[index][4] >>= 15;

		Panmove[index][4]	= ((Panmove[index][4]	* nScrWidht + 0x7f)>>8);
		Tiltmove[index][4] = ((Tiltmove[index][4] * nScrHeight+ 0x7f)>>8);

		Panmove[index][0] = sFOVPan + Panmove[index][4];
		Tiltmove[index][0] = sFOVTilt + Tiltmove[index][4];

		Panmove[index][1] = sFOVPan - Panmove[index][4];
		Tiltmove[index][1] = sFOVTilt + Tiltmove[index][4];

		Panmove[index][2] = sFOVPan - Panmove[index][4];
		Tiltmove[index][2] = sFOVTilt - Tiltmove[index][4];

		Panmove[index][3] = sFOVPan + Panmove[index][4];
		Tiltmove[index][3] = sFOVTilt - Tiltmove[index][4];
#endif

		if(PZAUTO_ONr)
		{	//일반 중심 적용
			for(j=0;j<4;j++)
			{
				Panmove[index][j] += nScrXCenter;
				Tiltmove[index][j] += nScrYCenter;
			}
		}
		else
		{	//Dzoom Manual 적용
			for(j=0;j<4;j++)
			{
				Panmove[index][j] = ((Panmove[index][j] * 4096) + (cal_dZoom_x/2))/ cal_dZoom_x;
				Tiltmove[index][j] = ((Tiltmove[index][j] * 4096) + (cal_dZoom_y/2)) / cal_dZoom_y;

				//실험값 적용
				Tiltmove[index][j] += nScrYCenter;
				Panmove[index][j] += nScrXCenter;

				if(Panmove[index][j] < 0)
				{
					Panmove[index][j] = 0;
				}
				else if(Panmove[index][j] > 65535)
				{
					Panmove[index][j] = 0xffff;
				}

				if(Tiltmove[index][j] < 0)
				{
					Tiltmove[index][j] = 0;
				}
				else if(Tiltmove[index][j] > 65535)
				{
					Tiltmove[index][j] = 0xffff;
				}
			}
		}

		PRM_On(index,1);
		PRM_Pos_Pol(index,
					Panmove[index][0],Tiltmove[index][0],
					Panmove[index][1],Tiltmove[index][1],
					Panmove[index][2],Tiltmove[index][2],
					Panmove[index][3],Tiltmove[index][3]
					);
		//KSH 131207 주석처리
		trans = PRI_Update_TRANS(IFEVT_GETVAL,index,0);

		color &= 0xf;

		PRM_Attr(index,color,trans);
	}
	else
	{
		SetPrivacyNullMask(i);
	}
}


/*********************************************************************************************************//**
* @param[in] s_angle : angle
* @param[out] none
* @retval sin(s_angle) Value
* @brief
*	Calulate sin(s_angle) Value
*	Use a sin Table
*************************************************************************************************************/
int32 mzapi_sin_16fp(int16 s_angle)
{
	s_angle = s_angle & 0xfff;
	if(s_angle <= 1024)		return (int32)((Tb_SIN[s_angle])/2);
	else if(s_angle <= 2048)return (int32)((Tb_SIN[((int16)2048) - s_angle])/2);
	else if(s_angle <= 3072)return (int32)((-Tb_SIN[s_angle - ((int16)2048)])/2);
	else 					return (int32)((-Tb_SIN[((int16)4096) - s_angle])/2);
}

/*********************************************************************************************************//**
* @param[in] s_angle : angle
* @param[out] none
* @retval cos(s_angle) Value
* @brief
*	Calulate cos(s_angle) Value
*	Use a sin Table
*************************************************************************************************************/
int32 mzapi_cos_16fp(int16 s_angle)
{
	s_angle = s_angle & 0xfff;
	if(s_angle <= 1024)		 return (int32)(( Tb_SIN[((int16)1024) - s_angle]>>1));
	else if(s_angle <= 2048) return (int32)((-Tb_SIN[s_angle - (int16)1024]>>1));
	else if(s_angle <= 3072) return (int32)((-Tb_SIN[((int16)3072) - s_angle]>>1));
	else 					 return (int32)(( Tb_SIN[s_angle - ((int16)3072)]>>1));
}

#if (POLYGON_TYPE == 0)
/*********************************************************************************************************//**
* @param[in] s_angle : angle
* @param[out] none
* @retval sin(s_angle) Value
* @brief
*	Calulate |sin(s_angle)| Value
*	Use a sin Table
*************************************************************************************************************/
int32 _mzapi_sin_16fp_(int16 s_angle)
{
	s_angle = s_angle & 0xfff;
	if(s_angle <= 1024)		return (int32)((Tb_SIN[s_angle])/2);
	else if(s_angle <= 2048)return (int32)((Tb_SIN[((int16)2048) - s_angle])/2);
	else if(s_angle <= 3072)return (int32)((Tb_SIN[s_angle - ((int16)2048)])/2);
	else 					return (int32)((Tb_SIN[((int16)4096) - s_angle])/2);
}
/*********************************************************************************************************//**
* @param[in] s_angle : angle
* @param[out] none
* @retval cos(s_angle) Value
* @brief
*	Calulate |cos(s_angle)| Value
*	Use a sin Table
*************************************************************************************************************/
int32 _mzapi_cos_16fp_(int16 s_angle)
{
	s_angle = s_angle & 0xfff;
	if(s_angle <= 1024)		 return (int32)((Tb_SIN[((int16)1024) - s_angle]>>1));
	else if(s_angle <= 2048) return (int32)((Tb_SIN[s_angle - (int16)1024]>>1));
	else if(s_angle <= 3072) return (int32)((Tb_SIN[((int16)3072) - s_angle]>>1));
	else 					 return (int32)((Tb_SIN[s_angle - ((int16)3072)]>>1));
}
#endif

/*********************************************************************************************************//**
* @param[in] index : Mask index
* @param[out] none
* @retval none
* @brief
*	Clear a mask
*************************************************************************************************************/

void SetPrivacyNullMask(uint08 index)
{
	PRM_On(index,0);
	PRM_Pos_Pol(index,0x8000,0x8000,0x8001,0x8000,0x8001,0x8001,0x8000,0x8001);
}

/*************************************************************************************************************
**************************************************************************************************************
* GLOBAL FUNCTIONS
**************************************************************************************************************
*************************************************************************************************************/

/*********************************************************************************************************//**
* @param[in] index : Mask index
* @param[out] none
* @retval none
* @brief
*  PRI3D_Set_Width
*************************************************************************************************************/
void PRI3D_Set_Width(uint08 index)
{
	uint32 ival;

	uint16 maskZoom = PRI_Update_Z(IFEVT_GETVAL,index,0);
	int16 mask_FOVH   = (Lens_get_target_FOV(FOV_TYPE_H ,maskZoom) + 50)/100;
	//Zoom값을 받아온다
	ival = PRI_Update_Z(IFEVT_GETVAL,index,0);

	//Zoom값 -> 화각 계산
	PrivZone[index].Width_Fov  = (Lens_get_target_FOV(FOV_TYPE_H,ival)+50) / 100;

	//화각, Width -> 넓이 계산
	ival = PRI_Update_W(IFEVT_GETVAL,index,0);
	if(ival&0x80)
	{
		ival |= 0xffffff00;
		ival = ~ival + 1;
	}
	if(ival == 0)
	{
		PrivZone[index].Width = 0;
		return;
	}

	PrivZone[index].Width = (ival << 8) / 0x50;
	ival = Lens_get_current_FOV(FOV_TYPE_H)/100;
	PrivZone[index].Width = PrivZone[index].Width*PrivZone[index].Width_Fov/ival;

	if(PrivZone[index].Width < 3) PrivZone[index].Width = 3;

	gAdjX[index] = (int32)gCurr_FOV_H - mask_FOVH;	// FOV Horizontal Offset Data 제거
	gAdjX[index] = gAdjX[index] * (int32)nScrXCenterAdj;
	gAdjX[index] = gAdjX[index]  / (nFov_H_Max - nFov_H_Min);	// Data Normalize

	gAdjX[index] = (gAdjX[index] * nFov_H_Max) / gCurr_FOV_H;
	gAdjX[index] = (gAdjX[index]+8)/16;
}

/*********************************************************************************************************//**
* @param[in] index : Mask index
* @param[out] none
* @retval none
* @brief
*  PRI3D_Set_Heigth
*************************************************************************************************************/
void PRI3D_Set_Heigth(uint08 index)
{
	uint32 ival;
	uint16 maskZoom = PRI_Update_Z(IFEVT_GETVAL,index,0);
	int16 mask_FOVV   = (Lens_get_target_FOV(FOV_TYPE_V ,maskZoom) + 50)/100;

	//Zoom값을 받아온다
	ival = PRI_Update_Z(IFEVT_GETVAL,index,0);

	//Zoom값 -> 화각 계산
	PrivZone[index].Height_Fov  = (Lens_get_target_FOV(FOV_TYPE_V,ival)+50)/100;

	//화각, Width -> 마스크의 각도(==크기)
	ival = PRI_Update_H(IFEVT_GETVAL,index,0);

	if(ival&0x80)
	{
		ival |= 0xffffff00;
		ival = ~ival + 1;
	}
	if(ival == 0)
	{
		PrivZone[index].Height = 0;
		return;
	}

	PrivZone[index].Height = (ival << 8) / 0x2D;
	ival = Lens_get_current_FOV(FOV_TYPE_V)/100;
	PrivZone[index].Height= PrivZone[index].Height * PrivZone[index].Height_Fov/ival;
	//PrivZone[index].Height_Angle  = (ival * PrivZone[index].Height_Fov + 0x17) / 0x2D;

	if(PrivZone[index].Height < 5) PrivZone[index].Height = 5;

	gAdjY[index] = (int32)gCurr_FOV_V - mask_FOVV;	// FOV Vertical Offset Data 제거
	gAdjY[index] = gAdjY[index] * (int32)nScrYCenterAdj;
	gAdjY[index] = gAdjY[index] / (nFov_V_Max - nFov_V_Min);	// Data Normalize
	gAdjY[index] = - gAdjY[index];

	gAdjY[index] = (gAdjY[index] * nFov_V_Max) / gCurr_FOV_V;
	gAdjY[index] = (gAdjY[index]+8)/16;
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  SetPrivacyMask
*************************************************************************************************************/
void PRI3D_Set_Y2Tilt(uint08 index,int32 Yval)
{
	int32 ival;

	//Zoom값 -> 화각 계산
	ival = Lens_get_target_FOV(FOV_TYPE_V,0)/100;

	PRI_Update_T(IFEVT_SETVAL,index,((50-Yval)*ival/100)&0xfff);
	//KSH 131207 주석처리
}
void PRI3D_Set_Tilt2Y(uint08 index,int32 Tval)
{
	int32 ival;

	//Zoom값 -> 화각 계산
	ival = Lens_get_target_FOV(FOV_TYPE_V,0)/100;

	PRI_Update_Y(IFEVT_SETVAL,index,Tval*100/ival);
	//KSH 131207 주석처리
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Redraw once
*************************************************************************************************************/
void PRV_Redraw()
{
	MaskEvent.b.update = 1;
}

/***************************************************************************************
* Function Name : InitPrivacyMask
* Parameters    :
* Return Value  : None
* Description   :
***************************************************************************************/
void InitPrivacyMask(void)
{
	/**************************************************************/
	//레지스터 초기화
	PZAUTO_ONw(0);

	/**************************************************************/
	//내부변수 초기화
	MaskEvent.byte = 0;
	MaskEvent.b.update = 1;

	draw_flag_H = 0;
	draw_flag_V = 0;
	pricacy_flag  = 1;
	pricacy_flag2 = 0;
	Mask_Dbg_flg = 0;
	Mask_Dbg_State = 0;
	Mask_Dbg_Pan = 0;
	Mask_Dbg_Tilt = 0;
	Mask_Dbg_Zoom = 0;
	Mask_Dbg_x = 0;
	Mask_Dbg_y = 0;
	Mask_Dbg_cr = 0;
	Mask_Dbg_Widht = 0;
	Mask_Dbg_Height = 0;
	/**************************************************************/
	//
	Box_Attr(BOX_NO_C_LINE_H,CP_BLK,0);
	Box_Pos(BOX_NO_C_LINE_H,0,100,50,50);

	Box_Attr(BOX_NO_C_LINE_V,CP_BLK,0);
	Box_Pos(BOX_NO_C_LINE_V,50,50,0,100);
	/**************************************************************/
	//H/W 초기값 : 화면의 중심 ,넓이 ,높이, 화각등...
	if(!PZAUTO_ONr)
	{
		nScrLeftEnd    =  PRI_WIDTH_MIN_;
		nScrRightEnd   =  PRI_WIDTH_MAX_;
		nScrTopEnd	   =  PRI_HEIGHT_MIN_;
		nScrBottomEnd  =  PRI_HEIGHT_MAX_;
	}
	else
	{
		nScrLeftEnd    =  PRI_WIDTH_MIN;
		nScrRightEnd   =  PRI_WIDTH_MAX;
		nScrTopEnd	   =  PRI_HEIGHT_MIN;
		nScrBottomEnd  =  PRI_HEIGHT_MAX;
	}
	nScrWidht      = (nScrRightEnd-nScrLeftEnd);
	nScrHeight     = (nScrBottomEnd-nScrTopEnd);

	nScrXCenter 	= 0x7000 + (nScrRightEnd+nScrLeftEnd)/2; // 추후에 OFFSET 값을 추가 할 수도 있다.
	nScrYCenter 	= 0x7000 + (nScrBottomEnd+nScrTopEnd)/2;

	nFov_H_Min = (Lens_get_target_FOV(FOV_TYPE_H,0x4000))/100;
	nFov_H_Max = (Lens_get_target_FOV(FOV_TYPE_H,0x0000))/100;
	nFov_V_Min = (Lens_get_target_FOV(FOV_TYPE_V,0x4000))/100;
	nFov_V_Max = (Lens_get_target_FOV(FOV_TYPE_V,0x0000))/100;
	/**************************************************************/
	//조정값

	/**************************************************************/
	//S/W 초기값 : Pan,tilt, 마스크의 ,넓이 계산.

	gPAN_Curr = 0;
	gTILT_Curr = 0;

	LensUpdate();
	PAN_Tab = 0;
	TILT_Tab = 0;

} /* InitPrivacyMask */

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Set MaskA for Privacy adjust
*  Draw small mask on the center of screen
*************************************************************************************************************/
void Set_Mask_Debug()
{
	if(Mask_Dbg_flg == 0)
	{
		draw_flag_V = 1;

		Mask_Dbg_State 	= PRI_Update_ON(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_disp 	= PRI_Update_DISP(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_I 		= PRI_Update_I(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Pan 	= PRI_Update_P(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Tilt 	= PRI_Update_T(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_x		= PRI_Update_X(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_y		= PRI_Update_Y(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Widht 	= PRI_Update_W(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Height = PRI_Update_H(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Zoom	= PRI_Update_Z(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_cr 	= PRI_Update_CR_OFF(IFEVT_GETVAL	,0	,0);
		Mask_Dbg_Line	= g_ViscaData.FLD.MASK_CL_ON;

		PRI_Update_ON(IFEVT_SETVAL	,0	,1	);
		PRI_Update_DISP(IFEVT_SETVAL,0	,0);
		PRI_Update_I(IFEVT_SETVAL	,0	,0);
		PRI_Update_P(IFEVT_SETVAL	,0	,0	);
		PRI_Update_T(IFEVT_SETVAL	,0	,0	);
		PRI_Update_X(IFEVT_SETVAL	,0	,50	);
		PRI_Update_Y(IFEVT_SETVAL	,0	,50	);
		PRI_Update_W(IFEVT_SETVAL	,0	,2	);
		PRI_Update_H(IFEVT_SETVAL	,0	,2	);
		PRI_Update_Z(IFEVT_SETVAL	,0	,0	);
		PRI_Update_CR_OFF(IFEVT_SETVAL	,0	,8);
		g_ViscaData.FLD.MASK_CL_ON = 1;

		LensUpdate();

		Mask_Dbg_flg = 1;
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  Set MaskA for Privacy Normal
*  Restore original Mask
*************************************************************************************************************/
void Set_Mask_Normal()
{
	if(Mask_Dbg_flg == 1)
	{
		draw_flag_V = 1;
		PRI_Update_ON(IFEVT_SETVAL	,0	,Mask_Dbg_State	);
		PRI_Update_DISP(IFEVT_SETVAL,0	,Mask_Dbg_disp);
		PRI_Update_I(IFEVT_SETVAL	,0	,Mask_Dbg_I);
		PRI_Update_P(IFEVT_SETVAL	,0	,Mask_Dbg_Pan	);
		PRI_Update_T(IFEVT_SETVAL	,0	,Mask_Dbg_Tilt	);
		PRI_Update_W(IFEVT_SETVAL	,0	,Mask_Dbg_Widht	);
		PRI_Update_H(IFEVT_SETVAL	,0	,Mask_Dbg_Height);
		PRI_Update_Z(IFEVT_SETVAL	,0	,Mask_Dbg_Zoom	);
		PRI_Update_X(IFEVT_SETVAL	,0	,Mask_Dbg_x		);
		PRI_Update_Y(IFEVT_SETVAL	,0	,Mask_Dbg_y		);
		PRI_Update_CR_OFF(IFEVT_SETVAL	,0	,Mask_Dbg_cr);
		g_ViscaData.FLD.MASK_CL_ON = Mask_Dbg_Line;
		
		LensUpdate();
		Mask_Dbg_flg = 0;
	}
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*  GLOBAL FUNC
*	Task for Draw Privacy Mask
*   Place this func Next to Protocol task
*************************************************************************************************************/
void PrivacyMaskProcess(void)
{
#if 1
	static uint16 Dzoom_mag_x,Dzoom_mag_y;


	if(g_ViscaData.FLD.MASK_CL_ON)
	//if(1)
	{
		Box_On(BOX_NO_C_LINE_H,STATE_ON);
		Box_On(BOX_NO_C_LINE_V,STATE_ON);
	}
	else
	{
		Box_On(BOX_NO_C_LINE_H,STATE_OFF);
		Box_On(BOX_NO_C_LINE_V,STATE_OFF);
	}

	if(gZOOM_Curr != Lens_get_cur_zoom_pos_logi() || ZHSP_KXr != Dzoom_mag_x)
	{
		if(g_ViscaData.FLD.FREEZE_ON == 0)
		{
			LensUpdate();
			Dzoom_mag_x = ZHSP_KXr;
			Dzoom_mag_y = ZVSP_KYr;
			SetPrivacyMask();
			MaskEvent.b.update = 0;
		}
	}
	else if(MaskEvent.b.update == 1)
	{
		LensUpdate();
		if((gTILT_Curr != gTILT_Old) ||(gPAN_Curr != gPAN_Old))
		{
			if(gPAN_Curr != gPAN_Old)
			{
				draw_flag_H = 6;
				gPAN_Old  = gPAN_Curr;
				pricacy_flag2 = 0;
			}

			if(gTILT_Curr != gTILT_Old)
			{
				draw_flag_V = 6;
				gTILT_Old = gTILT_Curr;
				pricacy_flag2 = 0;
			}
		}
		else
		{
			pricacy_flag2 = 0;
		}
		if(g_ViscaData.FLD.FREEZE_ON == 0)
		{
			SetPrivacyMask();
			MaskEvent.b.update = 0;
		}
	}
	else if(MaskEvent.b.update==0)
	{
		if(pricacy_flag2>0){
			pricacy_flag2--;
		}
		else{
			if(draw_flag_H > 0 && draw_flag_V > 0)
			{
				draw_flag_H--;
				draw_flag_V--;
				if(g_ViscaData.FLD.FREEZE_ON == 0)
				{
					SetPrivacyMask();
					MaskEvent.b.update = 0;
				}
			}
			else if(draw_flag_H == 0&&draw_flag_V > 0)
			{
				draw_flag_V--;
				if(g_ViscaData.FLD.FREEZE_ON == 0)
				{
					SetPrivacyMask();
					MaskEvent.b.update = 0;
				}
			}
			else if(draw_flag_H > 0&&draw_flag_V == 0)
			{
				draw_flag_H--;
				if(g_ViscaData.FLD.FREEZE_ON == 0)
				{
					SetPrivacyMask();
					MaskEvent.b.update = 0;
				}
			}
		}
	}
#endif
}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*	Zoom값에 따라 달라지는 값을 구해준다.
*************************************************************************************************************/
void LensUpdate(void)
{
	uint08 index;

	gZOOM_Curr	= Lens_get_cur_zoom_pos_logi();

	gCurr_FOV_H = Lens_get_current_FOV(FOV_TYPE_H)/100;
	gCurr_FOV_V = Lens_get_current_FOV(FOV_TYPE_V)/100;

	if((int08)g_CamData.FLD.MADJ_3D_PAN_NT & 0x80)
		nScrXCenterAdj = g_CamData.FLD.MADJ_3D_PAN_NT | 0xffffff00;
	else
		nScrXCenterAdj = g_CamData.FLD.MADJ_3D_PAN_NT;

	nScrXCenterAdj = ((int32)nScrXCenterAdj * nScrWidht )/100;

	if((int08)g_CamData.FLD.MADJ_3D_TILT_NT & 0x80)
		nScrYCenterAdj = g_CamData.FLD.MADJ_3D_TILT_NT | 0xffffff00;
	else
		nScrYCenterAdj = g_CamData.FLD.MADJ_3D_TILT_NT;

	nScrYCenterAdj = ((int32)nScrYCenterAdj * nScrHeight)/100;

	for (index = 0; index < MAX_PRIVACYZONE; index++)
	{
		if(PRI_Update_ON(IFEVT_GETVAL,index,0))
		{
			PRI3D_Set_Width(index);
			PRI3D_Set_Heigth(index);
		}
	}

}

/*********************************************************************************************************//**
* @param[in] none
* @param[out] none
* @retval none
* @brief
*	Debug Osd Print
*************************************************************************************************************/
void PRIV_Dbg_Osd()
{
#if 1
	DebugScrPrintf(5,3 ,"CP P   :%05d,T   :%05d,Z:%05d"	,IF_GetCurPan(),IF_GetCurTilt(),IF_EEPViscaUpdate(IFEVT_GETVAL,VDX_ZOOM_POS,0));
	DebugScrPrintf(6,3 ,"M1 P   :%05d,T   :%05d,Z:%05d"	,PRI_Update_P(IFEVT_GETVAL,0,0) ,PRI_Update_T(IFEVT_GETVAL,0,0)	,PRI_Update_Z(IFEVT_GETVAL,0,0));
	//DebugScrPrintf(7,3 ,"M1 H   :%05d,V   :%05d"		,PrivZone[0].Width_Fov		,PrivZone[0].Height_Fov);
	//DebugScrPrintf(8,3 ,"M1 FovH:%05d,FovV:%05d"		,PrivZone[0].Width_Angle	,PrivZone[0].Height_Angle);
	//DebugScrPrintf(9,3 ,"M1 R   :%05d,L   :%05d"		,PrivZone[0].MaskArea.left	,PrivZone[0].MaskArea.right);
	//DebugScrPrintf(10,3,"M1 T   :%05d,B   :%05d"		,PrivZone[0].MaskArea.top	,PrivZone[0].MaskArea.bottom);
	DebugScrPrintf(12,3,"M1 St  :%02d,CR  :%02d,C:%d "	,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_ON,0),IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_COLOR_ON,0),IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_TRANS,0));
	//DebugScrPrintf(12,3,"%04d %04d %04d %04d "			,PrivZone[0].MaskArea.left-0x8000,PrivZone[0].MaskArea.right-0x8000,PrivZone[0].MaskArea.top-0x8000,PrivZone[0].MaskArea.bottom-0x8000);
	DebugScrPrintf(13,3,"%04d %04d %04d %04d "			,IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_WIDTH,0),IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_HEIGHT,0),IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_X_POS,0),IF_EEPViscaMaskUpdate(IFEVT_GETVAL,1,VDX_MASK_Y_POS,0));
	//DebugScrPrintf(14,3,"M  %X,%X,%X,%X     "			,dbg_data[0],dbg_data[2],dbg_data[3],dbg_data[4]);
	DebugScrPrintf(16,3,"%04d %04d %04d %04d "			,PrivZone[0].MaskArea.left-0x8000,PrivZone[0].MaskArea.right-0x8000,PrivZone[0].MaskArea.top-0x8000,PrivZone[0].MaskArea.bottom-0x8000);
	//DebugScrPrintf(16,3,"M  %d,%d,%d,%d     "			,dbg_data[13],dbg_data[14],dbg_data[15],dbg_data[16]);
	//DebugScrPrintf(17,3,"M  %d,%d,%d,%d     "			,dbg_data[17]-0x8000,dbg_data[18]-0x8000,dbg_data[19]-0x8000,dbg_data[20]-0x8000);
	//DebugScrPrintf(18,3,"M  %X,%X,%X,%X     "			,dbg_data[17],dbg_data[18],dbg_data[19],dbg_data[20]);
#endif
}


/***************************** END OF FILE ****************************/
