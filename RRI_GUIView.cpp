
///_______________________________________________________________________________________
// //////////////////////////////////////////////////////////////////////////////////////
/// COMMON_LIBRALY
//

#include		"RRI_GUIView.h"
///
#include		"InitProj.h"
#include		"SetProject.h"
#include		<time.h>
///
#include		"RI_DLG.h"
#include		"DataColor.h"
#include		"DataColorSed.h"
#include		"MakeData.h"
#include		"Make_Dynamic.h"
#include		"MagDlg.h"
#include		"RThiessen.h"
#include		"SetRivCof.h"
#include		"BUSY.h"

#include		"EditLocation.h"
#include		"EditDamCnt.h"
#include		"EditDivide.h"

#include		"TSEDITDLG.h"
#include		"TimeVal.h"
#include		"Assemble.h"

#include		"Period.h"
#include		"Group.h"
#include		"FDirect.h"

#include		"MultiColor.h"
#include        "OutputSelectionDlg.h"

#include		"Assemble.h"

#include		<map>			// 20190201 Add
#include		<iostream>		// 20190201 Add
#include		<fstream>		// 20211022 Add
#include		<sstream>
#include		<string>		// 20190201 Add
#include		<vector>		// 20190201 Add
#include		"gdal_priv.h"	// 20190201 Add
#include		"cpl_conv.h"	// 20190201 Add
#include		"gdal.h"		// 20190201 Add
#include		"cpl_string.h"	// 20190201 Add
#include		"ogr_spatialref.h"	// 20190201 Add
#include		"cpl_minixml.h"	// 20190201 Add
#include		"commonutils.h"	// 20190201 Add

#include		"CSetSedNo.h"   //20211004 Add
#include		<algorithm>		//20211004 Add

//#define		WM_ASEDIT_ENCHANGE	0x8888	// 0-WM_APP(0x8000) Reserved  
											// Application Message Area  0x8000-0xBFFF
											// Application String Message  Area  0xC000 - 0xFFFF  0x10000- Reserved
											// after define  Register with [RegisterWindowMessage関数]

//  //////////////////////////////////////////////////////////////////////////////////////
/// AS_LIBRALY
//
#include		"As_Mode.h"
#include		"Proj_Conf.h"
#include		"CommGL.h"

//
///----------------------------------------------------------------------------------------



#include	<io.h>
#include	<fcntl.h>
#include	<list>

// ///////////////////////////////////////////////////////////////////////////////////////
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern					CStatusBar*		SB;	
extern					COLORREF		Dcolor[];
//
FILE*					ff;
int						B_Change_RRI;				// RRI_INPUT が更新された数
GL_PARAMETER				Gp;
CPoint					LastPoint;
CPoint					LastSelectPoint;
XYCOORD					Band_Area[4];
int						Fanum, Famem;
XYCOORD*					Free_Area;
IXYCOORD					Prof_ST[2],Oldid;
int						CellKind[10];

///----------------------------------------------------------------------------------------------
//
CString					Fonts[12]={	"Arial","Calibri","Candara","Corbel","Impact","Lucida Sans","Vrinda",
								"Cambria","Garamond","Georgia","Minion","Times New Roman"};
//
char						m_RecentPath[SIZE_05K];
char						m_BootPath[SIZE_05K];
/// //////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PARAMS					PM;							// 基本情報
DATASET					DSET;						// ファイルセット

MINFO**					MESH;
SELECT_INFO				SI;							// 選択メッシュ情報

char**					AllDir;
BYTE**					mark;
BYTE**					EXmark;

char						Cover_Name[20][48];
char						Soil_Name[13][48];
LUINFO					CODE_TABLE[13][20];			// マニング係数別

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   スクリーンツール
int						SCHnum, SCVnum;
double					NOWX, NOWY;					// スクリーンツール横縦、現在位置
BYTE*					Tool_Image;					// スクリーンイメージ

int						Line_Counter=0;				// メッシュラインの評価。Ontimerで評価

long						Histcnt;
int						offx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int						offy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
double					MESH_LATLNG_WIDTH_5S = 0.00138889;
double					offx_jflw[] = { MESH_LATLNG_WIDTH_5S, MESH_LATLNG_WIDTH_5S, 0, -1 * MESH_LATLNG_WIDTH_5S, -1 * MESH_LATLNG_WIDTH_5S, -1 * MESH_LATLNG_WIDTH_5S, 0, MESH_LATLNG_WIDTH_5S };
double					offy_jflw[] = { 0, -1 * MESH_LATLNG_WIDTH_5S, -1 * MESH_LATLNG_WIDTH_5S, -1 * MESH_LATLNG_WIDTH_5S, 0, MESH_LATLNG_WIDTH_5S, MESH_LATLNG_WIDTH_5S, MESH_LATLNG_WIDTH_5S };
int						direct[] = { 16, 32, 64, 128, 1, 2, 4, 8 };		// 流入方向
int						Ddirect[] = { 1, 2, 4, 8, 16, 32, 64, 128 };	// 流下方向

///
//----------------------------------------------------------------------------------------------
int						CREAT;
int						CVIEW = 0;					// GL のカメラ諸元に必要 ORTHO だけを使用
int						CID;							// 現在選択されているメッシュ
int						CTAB,COLD;					// どのタブか 
int						CEX;							// 外部データ番号　< EXnum
int						CEX_LABEL;					// コンボ表示用  <＝EXnum
int						CDATA;						// 現在選択しているデータ　旧CDATA

// Common Counter for HARD_COPY
int				Cnt_Prof,Cnt_MProf,Cnt_Hydro;
///																			
/////////////////////////////////////////////////////////////////////////////  コントロール定義
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int			TAB_NUM = 3;
int			TAB_1_NUM = 36;

int			OFFSET_MODEL,  OFFSET_TIMESERIES,   OFFSET_VALUE,   OFFSET_EXEC;

/////////////////////////////////////////////////////////////////////////////  TAB 1
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
//
int			TAB_1_ID[] = {
				IDC_STATIC_GB_10, IDC_STATIC_GB_11, IDC_STATIC_GB_22, IDC_STATIC_GB_13,	// Add 201601

				IDC_STATIC_114, IDC_STATIC_122,IDC_STATIC_112, IDC_STATIC_113, IDC_STATIC_129,
				IDC_PROJECT_NAME, IDC_MESH_SUBDEV, IDC_MESH_H, IDC_MESH_V, 

				IDC_EDIT_105, IDC_EDIT_106, IDC_EDIT_107, IDC_EDIT_108, IDC_EDIT_109,
				IDC_EDIT_110, IDC_EDIT_111, IDC_EDIT_112, IDC_EDIT_113, IDC_EDIT_114,
				IDC_EDIT_115, IDC_EDIT_116,

				IDC_BUTTON_104, IDC_BUTTON_105, IDC_BUTTON_103, IDC_BUTTON_111, IDC_BUTTON_CSPARAM,	// Add 201601
				IDC_BUTTON_112, IDC_BUTTON_113, IDC_BUTTON_UNDO, IDC_BUTTON_114, IDC_BUTTON_LANDUSE_JP, IDC_BUTTON_LANDUSE_JP2 };		// 20190201 Add

int				Disp_LatLng_NUM = 13, Disp_UTM_NUM = 5;
int				Disp_LatLng_ID[] = { IDC_EDIT_105, IDC_EDIT_106, IDC_EDIT_107,
									IDC_EDIT_108, IDC_EDIT_109, IDC_EDIT_110,
									IDC_EDIT_111, IDC_EDIT_112, IDC_EDIT_113,
									IDC_EDIT_114, IDC_EDIT_115, IDC_EDIT_116,
									IDC_STATIC_114 };
int				Disp_UTM_ID[] = { IDC_EDIT_10, IDC_EDIT_11, IDC_EDIT_12, IDC_EDIT_13, IDC_STATIC_114 };
///
// Add 1410 AREA EDIT_BOX
int			AREA_ID_NUM = 12;
int			AREA_ID[] = {		IDC_EDIT_105, IDC_EDIT_106, IDC_EDIT_107,
							IDC_EDIT_108, IDC_EDIT_109, IDC_EDIT_110,
							IDC_EDIT_111, IDC_EDIT_112, IDC_EDIT_113,
							IDC_EDIT_114, IDC_EDIT_115, IDC_EDIT_116 };

/////////////////////////////////////////////////////////////////////////////  TAB 2
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
//
int			TAB_2_NUM = 45;

int			TAB_2_ID[] = {
				IDC_STATIC_GB_15,IDC_STATIC_GB_21,

				IDC_STATIC_209,                IDC_STATIC_201, IDC_STATIC_202, IDC_STATIC_205,
				IDC_STATIC_203, IDC_STATIC_204, IDC_STATIC_206, IDC_STATIC_207, IDC_STATIC_208, 
				IDC_STATIC_213, IDC_STATIC_214, IDC_STATIC_211, IDC_STATIC_212, IDC_STATIC_SELINFO, IDC_STATIC_OUTLOC,

				IDC_EDIT_201, IDC_EDIT_202, IDC_EDIT_203, IDC_EDIT_204,IDC_EDIT_206, 
				IDC_EDIT_207, IDC_EDIT_208,              IDC_EDIT_209,IDC_EDIT_212, 

				IDC_BUTTON_201, IDC_BUTTON_206, IDC_BUTTON_220,IDC_BUTTON_207, IDC_BUTTON_208, 		
				IDC_BUTTON_210,
				IDC_BUTTON_B_201, IDC_BUTTON_B_202, IDC_BUTTON_B_203,IDC_BUTTON_B_204, IDC_BUTTON_B_205 ,
				IDC_BUTTON_B_206, IDC_BUTTON_B_207,
				IDC_BUTTON_212, IDC_BUTTON_EACC,
				IDC_BUTTON_214,   // 20190201 Add IDC_BUTTON_214
				IDC_CHECK_10MIN,  // 20200603 Add
				IDC_GRP_SETSEDIM, IDC_BTN_SETSEDIM    //20210929 Add
};	

int			BOUND_ID[] = { IDC_BUTTON_B_201, IDC_BUTTON_B_202, IDC_BUTTON_B_203, IDC_BUTTON_B_204, IDC_BUTTON_B_205,
						  IDC_BUTTON_B_206, IDC_BUTTON_B_207 };
///
/////////////////////////////////////////////////////////////////////////////  TAB 3
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
int			TAB_3_NUM = 68;

int			TAB_3_ID[] = {
	IDC_STATIC_GB_30, IDC_STATIC_GB_31,IDC_STATIC_GB_41, IDC_STATIC_GB_43,

	IDC_STATIC_401, IDC_STATIC_511, IDC_STATIC_502, IDC_STATIC_509,
	IDC_STATIC_506, IDC_STATIC_507, IDC_STATIC_510, 
	IDC_STATIC_513, IDC_STATIC_514, IDC_STATIC_515, IDC_STATIC_516, IDC_STATIC_517,
	IDC_STATIC_518, IDC_STATIC_519,

	IDC_STATIC_402, IDC_STATIC_403, IDC_STATIC_404, IDC_STATIC_405,
	IDC_MESHINFO_1, IDC_MESHINFO_2, IDC_MESHINFO_3, IDC_MESHINFO_4, IDC_MESHINFO_5,

	IDC_BUTTON_401, IDC_BUTTON_404, IDC_BUTTON_LIST, IDC_BUTTON_BACK,

	IDC_BUTTON_RESET, IDC_BUTTON_CANCEL, IDC_BUTTON_DIR_UNDO,

	IDC_CHECK_OP_1, IDC_CHECK_OP_2, IDC_CHECK_OP_3, IDC_CHECK_OP_4, IDC_CHECK_OP_5,
	IDC_CHECK_OP_6, IDC_CHECK_OP_7, IDC_CHECK_DISPARROW, IDC_ARROWINFO,

	IDC_RADIO_NW, IDC_RADIO_N, IDC_RADIO_NE,
	IDC_RADIO_W, IDC_RADIO_E,
	IDC_RADIO_SW, IDC_RADIO_S, IDC_RADIO_SE, IDC_RADIO_TERM,

	IDC_MESHCOLOR_1, IDC_MESHCOLOR_2, IDC_MESHCOLOR_3, IDC_MESHCOLOR_4, IDC_MESHCOLOR_5,
	IDC_MESHCOLOR_6, IDC_MESHCOLOR_7, IDC_MESHCOLOR_8, IDC_MESHCOLOR_9, IDC_MESHCOLOR_10,
	IDC_MESHCOLOR_11, 

	IDC_SLIDER_TRANS,  IDC_SLIDER_TRANS2,
	IDC_COMBO_DATA,
	IDC_STATIC_GB_REMAIN, IDC_BUTTON_RRI };
//
int			MESH_COLOR_ID[] = { IDC_MESHCOLOR_1, IDC_MESHCOLOR_2, IDC_MESHCOLOR_3, IDC_MESHCOLOR_6,
				IDC_MESHCOLOR_7, IDC_MESHCOLOR_8, IDC_MESHCOLOR_9, IDC_MESHCOLOR_10, IDC_MESHCOLOR_11 };

int			DIRECT_ID[] = {	IDC_RADIO_E,IDC_RADIO_SE,IDC_RADIO_S,
							IDC_RADIO_SW,IDC_RADIO_W,IDC_RADIO_NW, 
							IDC_RADIO_N, IDC_RADIO_NE,IDC_RADIO_TERM};

///------------------------------------------------------------------------------- Avail Buttons
int		AVAIL_NUM[3]		= { 6, 6, 9 };
int		TAB_1_AVAIL[6] = { IDC_BUTTON_104, IDC_BUTTON_105, IDC_BUTTON_UNDO, IDC_BUTTON_CSPARAM,	// Add 201601 20190201 Modify [4] -> [5]
							IDC_BUTTON_LANDUSE_JP, IDC_BUTTON_LANDUSE_JP2};	// 20190201 Add
int		TAB_2_AVAIL[6] = { IDC_BUTTON_201, IDC_BUTTON_206,IDC_BUTTON_207, IDC_BUTTON_208, IDC_BUTTON_210 ,IDC_BUTTON_214}; 
int		TAB_3_AVAIL[9]	= { IDC_BUTTON_401, IDC_BUTTON_404, 
							IDC_CHECK_OP_1, IDC_CHECK_OP_2, IDC_CHECK_OP_3, IDC_CHECK_OP_6, IDC_CHECK_OP_7,
							IDC_SLIDER_TRANS,IDC_SLIDER_TRANS2 };
int		UTM_INAVAIL[3] = { IDC_BUTTON_207, IDC_BUTTON_208, IDC_BUTTON_212 };
///------------------------------------------------------------------------------- Avail Buttons
// FILE_IN_NUM = 21  -> 29   2014/12     FILE_OUT_NUM  -> 10
//
CString		MODEL_EDIT_NAME[FILE_ALL_NUM] = {
						"Rain ",
						"DEM",
						"ACC",
						"DIR",
						"SED",

						"Land-use",
						"River width (m)",
						"River depth (m)",
						"Bank height(m)",

						"hs_initial(m)",
						"hr_initial(m)",
						"hg_initial(m)",
						"gampt_ff_initial",
						"hs_boundary(m)",

						"hr_boundary(m)",
						"qs_boundary",
						"qr_boundary",
						"Dam",

						"Diversion (m3/s)",
						"Evaporation (Display Only)",
						"Out Location",

						"Length",
						"Section Map",
						"Section Head",
						"Land cover",
						"Soil"};

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
int			File_Folder_Num = 7;
CString		File_Folder_Name[7] = { "", "rain", "topo", "riv", "init", "bound", "out" };
CString		File_Extention[FILE_IN_USE] = {	"dat", 
								"txt", "txt", "txt", "txt",
								"txt", "txt", "txt","txt", 
								"out", "out", "out", "out", 
								"txt", "txt", "txt", "txt", "txt", "txt", "dat", "txt" };
int			File_Format[ FILE_IN_NUM ] = {	5, 0,0,0,0, 0,0,0,0, 1,1,1,1, 2,2,2,2, 3, 4, 6,8, 9999,9999,9999}; 
int			File_Order[FILE_IN_NUM] =   { -1, 2,0,0,0, 0,2,2,2, 3,3,3,4, 1,1,1,1, 0, 0, 1,0, 2,0,-1};
int			File_Folder_ID[] = { 1,  2,2,2,2,  2,3,3,3, 4,4,4,4, 5,5,5,5, 0, 0, 1,0, 3,3,3 };
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
CString		File_Title[FILE_IN_NUM] = { "Rain",
										"DEM",
										"ACC",
										"DIR",
										"SED",

										"Land-use",
										"River width",
										"River depth",
										"Bank height",

										"hs_Initial",
										"hr_Initial",
										"hg_Initial",		// Add
										"fampt_ff_initial",

										"hs_boundary",	// Add Dev
										"hr_boundary",	// Add Dev
										"qs_boundary",	// Add
										"qr_boundary",	// Add

										"Dam",

										"Diversion",

										"Evaporation",
										"Output location",

										"Length",
										"Section Map",
										"Section Head"};
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   OUT FILES
CString		OutFile_Title[FILE_OUT_NUM] = { "hs(inundation)", "hr(river water depth)", "hg(groundwater depth)",
						"qr(river discharge)", "qu", "qv", 	"gu", "gv","gampt_ff", "Storage"};
int			TIME_ID_NUM = 8, TIME_ID[] = { IDC_EDIT_201, IDC_EDIT_202, IDC_EDIT_203, IDC_EDIT_204,// IDC_EDIT_205,
							IDC_EDIT_206, IDC_EDIT_207, IDC_EDIT_208, IDC_EDIT_209 };// , IDC_EDIT_210};

IXYCOORD		Tool_Frame[4] = { { (BYTE)1, 0, 0 }, { (BYTE)1, 0, 161 }, { (BYTE)1, 60, 161 }, { (BYTE)1, 60, 0 } };

IXYCOORD		Tool_Func[6][4] = { { { (BYTE)1, 14, 6 }, { (BYTE)1, 14, 34 }, { (BYTE)1, 46, 34 }, { (BYTE)1, 46, 6 } },
							{ { (BYTE)1, 14, 41 }, { (BYTE)1, 14, 60 }, { (BYTE)1, 46, 60 }, { (BYTE)1, 46, 41 } },
							{ { (BYTE)1, 5, 64 }, { (BYTE)1, 5, 98 }, { (BYTE)1, 23, 98 }, { (BYTE)1, 23, 64 } },
							{ { (BYTE)1, 36, 64 }, { (BYTE)1, 36, 98 }, { (BYTE)1, 54, 98 }, { (BYTE)1, 54, 64 } },
							{ { (BYTE)1, 14, 103 }, { (BYTE)1, 14, 121 }, { (BYTE)1, 46, 121 }, { (BYTE)1, 46, 103 } },
							{ { (BYTE)1, 14, 128 }, { (BYTE)1, 14, 156 }, { (BYTE)1, 46, 156 }, { (BYTE)1, 46, 128 } } };

CString		MESH_FEATURE[] = { "", "Slope", "River", "HS_Cond", "HR_Cond", "QS_Cond", "QR_Cond",
"DAM_Cond", "Diversion_Cond", "Locate Position" };
// //////////////////////////////////////////////////////////////////////////////////
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Sed -----------------------------------------------
int CRRI_GUIView::ms_SubBasinDataVal = 1;
// END -----------------------------------------------

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "RRI_GUI.h"
#endif

#include "RRI_GUIDoc.h"
#include "RRI_GUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <CommFuncs.h>

// CRRI_GUIView

IMPLEMENT_DYNCREATE(CRRI_GUIView, CFormView)

BEGIN_MESSAGE_MAP(CRRI_GUIView, CFormView)
	ON_WM_TIMER()
	ON_WM_DRAWITEM()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CRRI_GUIView::OnTcnSelchangeTabMain)
	ON_EN_CHANGE(IDC_EDIT_105, &CRRI_GUIView::OnEnChangeEdit105)
	ON_EN_CHANGE(IDC_EDIT_106, &CRRI_GUIView::OnEnChangeEdit106)
	ON_EN_CHANGE(IDC_EDIT_107, &CRRI_GUIView::OnEnChangeEdit107)
	ON_EN_CHANGE(IDC_EDIT_108, &CRRI_GUIView::OnEnChangeEdit108)
	ON_EN_CHANGE(IDC_EDIT_109, &CRRI_GUIView::OnEnChangeEdit109)
	ON_EN_CHANGE(IDC_EDIT_110, &CRRI_GUIView::OnEnChangeEdit110)
	ON_EN_CHANGE(IDC_EDIT_111, &CRRI_GUIView::OnEnChangeEdit111)
	ON_EN_CHANGE(IDC_EDIT_112, &CRRI_GUIView::OnEnChangeEdit112)
	ON_EN_CHANGE(IDC_EDIT_113, &CRRI_GUIView::OnEnChangeEdit113)
	ON_EN_CHANGE(IDC_EDIT_114, &CRRI_GUIView::OnEnChangeEdit114)
	ON_EN_CHANGE(IDC_EDIT_115, &CRRI_GUIView::OnEnChangeEdit115)
	ON_EN_CHANGE(IDC_EDIT_116, &CRRI_GUIView::OnEnChangeEdit116)
	ON_BN_CLICKED(IDC_BUTTON_103, &CRRI_GUIView::OnBnClickedButton103)
//
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_111, &CRRI_GUIView::OnBnClickedButton111)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, &CRRI_GUIView::OnCbnSelchangeComboData)
	ON_BN_CLICKED(IDC_BUTTON_401, &CRRI_GUIView::OnBnClickedButton401)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_201, &CRRI_GUIView::OnBnClickedButton201)
	ON_STN_DBLCLK(IDC_MESHCOLOR_1, &CRRI_GUIView::OnStnDblclickMeshcolor1)
	ON_STN_DBLCLK(IDC_MESHCOLOR_2, &CRRI_GUIView::OnStnDblclickMeshcolor2)
	ON_STN_DBLCLK(IDC_MESHCOLOR_3, &CRRI_GUIView::OnStnDblclickMeshcolor3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRANS2, &CRRI_GUIView::OnNMCustomdrawSliderTrans2)
	ON_BN_CLICKED(IDC_CHECK_OP_3, &CRRI_GUIView::OnBnClickedCheckOp3)
	ON_BN_CLICKED(IDC_CHECK_OP_2, &CRRI_GUIView::OnBnClickedCheckOp2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRANS, &CRRI_GUIView::OnNMCustomdrawSliderTrans)
	ON_BN_CLICKED(IDC_CHECK_OP_1, &CRRI_GUIView::OnBnClickedCheckOp1)
	ON_BN_CLICKED(IDC_BUTTON_104, &CRRI_GUIView::OnBnClickedButton104)
	ON_BN_CLICKED(IDC_BUTTON_206, &CRRI_GUIView::OnBnClickedButton206)
	ON_EN_CHANGE(IDC_EDIT_201, &CRRI_GUIView::OnEnChangeEdit201)
	ON_EN_CHANGE(IDC_EDIT_202, &CRRI_GUIView::OnEnChangeEdit202)
	ON_EN_CHANGE(IDC_EDIT_203, &CRRI_GUIView::OnEnChangeEdit203)
	ON_EN_CHANGE(IDC_EDIT_204, &CRRI_GUIView::OnEnChangeEdit204)
	ON_EN_CHANGE(IDC_EDIT_206, &CRRI_GUIView::OnEnChangeEdit206)
	ON_EN_CHANGE(IDC_EDIT_207, &CRRI_GUIView::OnEnChangeEdit207)
	ON_EN_CHANGE(IDC_EDIT_208, &CRRI_GUIView::OnEnChangeEdit208)
	ON_EN_CHANGE(IDC_EDIT_209, &CRRI_GUIView::OnEnChangeEdit209)
	ON_EN_CHANGE(IDC_EDIT_212, &CRRI_GUIView::OnEnChangeEdit212)
	ON_BN_CLICKED(IDC_BUTTON_208, &CRRI_GUIView::OnBnClickedButton208)
	ON_BN_CLICKED(IDC_BUTTON_207, &CRRI_GUIView::OnBnClickedButton207)
	ON_BN_CLICKED(IDC_BUTTON_112, &CRRI_GUIView::OnBnClickedButton112)
	ON_BN_CLICKED(IDC_BUTTON_113, &CRRI_GUIView::OnBnClickedButton113)
	ON_BN_CLICKED(IDC_CHECK_OP_4, &CRRI_GUIView::OnBnClickedCheckOp4)
	ON_BN_CLICKED(IDC_BUTTON_404, &CRRI_GUIView::OnBnClickedButton404)
	ON_STN_DBLCLK(IDC_MESHCOLOR_4, &CRRI_GUIView::OnStnDblclickMeshcolor4)
	ON_BN_CLICKED(IDC_CHECK_OP_6, &CRRI_GUIView::OnBnClickedCheckOp6)
	ON_BN_CLICKED(IDC_CHECK_OP_5, &CRRI_GUIView::OnBnClickedCheckOp5)
	ON_BN_CLICKED(IDC_CHECK_OP_7, &CRRI_GUIView::OnBnClickedCheckOp7)
	ON_STN_DBLCLK(IDC_MESHCOLOR_5, &CRRI_GUIView::OnStnDblclickMeshcolor5)
	ON_BN_CLICKED(IDC_BUTTON_220, &CRRI_GUIView::OnBnClickedButton220)
	ON_STN_DBLCLK(IDC_MESHCOLOR_6, &CRRI_GUIView::OnStnDblclickMeshcolor6)
	ON_STN_DBLCLK(IDC_MESHCOLOR_7, &CRRI_GUIView::OnStnDblclickMeshcolor7)
	ON_STN_DBLCLK(IDC_MESHCOLOR_8, &CRRI_GUIView::OnStnDblclickMeshcolor8)
	ON_STN_DBLCLK(IDC_MESHCOLOR_9, &CRRI_GUIView::OnStnDblclickMeshcolor9)
	ON_STN_DBLCLK(IDC_MESHCOLOR_10, &CRRI_GUIView::OnStnDblclickMeshcolor10)
	ON_STN_DBLCLK(IDC_MESHCOLOR_11, &CRRI_GUIView::OnStnDblclickMeshcolor11)
	ON_COMMAND(IDS_CHANGE_BACKCOLOR, &CRRI_GUIView::OnIdsChangeBackcolor)
	ON_COMMAND(IDS_SET_RIV_PARAMETER, &CRRI_GUIView::OnIdsSetRivParameter)
	ON_COMMAND(IDS_BOUNDARY_POS, &CRRI_GUIView::OnIdsBoundaryPos)
	ON_COMMAND(IDS_EXTARCT_SED, &CRRI_GUIView::OnIdsExtractSed)
	ON_COMMAND(IDS_BOUNDARY_DAM, &CRRI_GUIView::OnIdsBoundaryDam)
	ON_BN_CLICKED(IDC_BUTTON_LIST, &CRRI_GUIView::OnBnClickedButtonList)
	ON_COMMAND(IDS_BOUNDARY_DIV, &CRRI_GUIView::OnIdsBoundaryDiv)
	ON_COMMAND(IDS_BOUNDARY_HS, &CRRI_GUIView::OnIdsBoundaryHs)
	ON_COMMAND(IDS_BOUNDARY_HR, &CRRI_GUIView::OnIdsBoundaryHr)
	ON_COMMAND(IDS_BOUNDARY_QS, &CRRI_GUIView::OnIdsBoundaryQs)
	ON_COMMAND(IDS_BOUNDARY_QR, &CRRI_GUIView::OnIdsBoundaryQr)
	ON_BN_CLICKED(IDC_BUTTON_B_201, &CRRI_GUIView::OnBnClickedButtonB201)
	ON_BN_CLICKED(IDC_BUTTON_B_202, &CRRI_GUIView::OnBnClickedButtonB202)
	ON_BN_CLICKED(IDC_BUTTON_B_203, &CRRI_GUIView::OnBnClickedButtonB203)
	ON_BN_CLICKED(IDC_BUTTON_B_204, &CRRI_GUIView::OnBnClickedButtonB204)
	ON_BN_CLICKED(IDC_BUTTON_B_205, &CRRI_GUIView::OnBnClickedButtonB205)
	ON_BN_CLICKED(IDC_BUTTON_B_206, &CRRI_GUIView::OnBnClickedButtonB206)
	ON_BN_CLICKED(IDC_BUTTON_B_207, &CRRI_GUIView::OnBnClickedButtonB207)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CRRI_GUIView::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_105, &CRRI_GUIView::OnBnClickedButton105)
	ON_BN_CLICKED(IDC_BUTTON_114, &CRRI_GUIView::OnBnClickedButton114)
	ON_BN_CLICKED(IDC_BUTTON_210, &CRRI_GUIView::OnBnClickedButton210)
	ON_BN_CLICKED(IDC_BUTTON_EACC, &CRRI_GUIView::OnBnClickedButtonEacc)
	ON_BN_CLICKED(IDC_BUTTON_214, &CRRI_GUIView::OnBnClickedButton214)	// 20190201 Add
	ON_BN_CLICKED(IDC_BUTTON_RRI, &CRRI_GUIView::OnBnClickedButtonRri)
	ON_BN_CLICKED(IDC_BUTTON_212, &CRRI_GUIView::OnBnClickedButton212)
	ON_COMMAND(IDS_DELETE_RIV, &CRRI_GUIView::OnIdsDeleteRiv)
	ON_COMMAND(IDS_SET_RIV, &CRRI_GUIView::OnIdsSetRiv)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CRRI_GUIView::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_CSPARAM, &CRRI_GUIView::OnBnClickedButtonLuparam)
	ON_BN_CLICKED(IDC_RADIO_NW, &CRRI_GUIView::OnBnClickedRadioNw)
	ON_BN_CLICKED(IDC_RADIO_N, &CRRI_GUIView::OnBnClickedRadioN)
	ON_BN_CLICKED(IDC_RADIO_E, &CRRI_GUIView::OnBnClickedRadioE)
	ON_BN_CLICKED(IDC_RADIO_SE, &CRRI_GUIView::OnBnClickedRadioSe)
	ON_BN_CLICKED(IDC_RADIO_S, &CRRI_GUIView::OnBnClickedRadioS)
	ON_BN_CLICKED(IDC_RADIO_SW, &CRRI_GUIView::OnBnClickedRadioSw)
	ON_BN_CLICKED(IDC_RADIO_W, &CRRI_GUIView::OnBnClickedRadioW)
	ON_BN_CLICKED(IDC_RADIO_NE, &CRRI_GUIView::OnBnClickedRadioNe)
	ON_BN_CLICKED(IDC_RADIO_TERM, &CRRI_GUIView::OnBnClickedRadioTerm)
	ON_BN_CLICKED(IDC_CHECK_DISPARROW, &CRRI_GUIView::OnBnClickedCheckDisparrow)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CRRI_GUIView::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CRRI_GUIView::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_DIR_UNDO, &CRRI_GUIView::OnBnClickedButtonDirUndo)
	ON_BN_CLICKED(IDC_BUTTON_LANDUSE_JP, &CRRI_GUIView::OnBnClickedButtonLanduseJp)
	ON_BN_CLICKED(IDC_BUTTON_LANDUSE_JP2, &CRRI_GUIView::OnBnClickedButtonLanduseJp2)
	ON_STN_CLICKED(IDC_STATIC_214, &CRRI_GUIView::OnStnClickedStatic214)
	ON_BN_CLICKED(IDC_BTN_SETSEDIM, &CRRI_GUIView::OnBnClickedBtnSetsedim)
END_MESSAGE_MAP()


std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
// CRRI_GUIView コンストラクション/デストラクション
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRRI_GUIView::CRRI_GUIView()
	: CFormView(CRRI_GUIView::IDD)
	, s_ProjName(_T(""))
	//, m_sRIVnum(_T(""))
	, s_MeshSubdev(_T(""))
	, s_stLNG_deg(_T(""))
	, s_stLNG_min(_T(""))
	, s_stLNG_sec(_T(""))
	, s_endLNG_deg(_T(""))
	, s_endLNG_min(_T(""))
	, s_endLNG_sec(_T(""))
	, s_stLAT_deg(_T(""))
	, s_stLAT_min(_T(""))
	, s_stLAT_sec(_T(""))
	, s_endLAT_deg(_T(""))
	, s_endLAT_min(_T(""))
	, s_endLAT_sec(_T(""))
	, s_MeshH(_T(""))
	, s_MeshV(_T(""))
//	, s_AccLimit(_T(""))
	, s_Select(_T(""))
	, s_OutLocation(_T(""))
	, s_Location(_T(""))
	, s_H(_T(""))
	, s_CurrentD(_T(""))
	, s_Kind(_T(""))
	, s_Acc(_T(""))
	, s_ArrowInfo(_T(""))
{
	// TODO: 構築コードをここに追加します。

}

CRRI_GUIView::~CRRI_GUIView()
{
}
///---------------------------------------------
// システムメッセージ
///---------------------------------------------

void CRRI_GUIView::OnDestroy()
{
	if (MessageBox("Save edited data file ?", "warning", MB_YESNO | MB_ICONQUESTION) == IDYES) {
		int		FFormat, FOrder;
		Write_RRI_INPUT(DSET);
		//
		for (int i = 0; i < FILE_ALL_NUM; i++) {
			if (DSET.need_save[i]) {
				if (i < FILE_IN_NUM) { FFormat = File_Format[i]; FOrder = File_Order[i]; }
				else                     FFormat = FOrder = 0;		/// Cover Soil
				//
				Write_Data_File(i, FFormat, FOrder, DSET, PM, MESH);
			}
		}
	}
	//
	SAFE_FREE(SI.HV);
	SAFE_FREE(SI.ID);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	Global
	if(mark != NULL )  Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, mark);
	if(EXmark != NULL) Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, EXmark);
	if(AllDir != NULL) Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, AllDir);

	if (Tool_Image != NULL) SAFE_FREE(Tool_Image);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    MESH
	if (MESH != NULL) {	
		for (int v = 0; v < PM.MVnum; v++) 	SAFE_FREE(MESH[v]);
		SAFE_FREE(MESH);
	}
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	PM
	if (PM.BVnum)			Free_Matrix(PM.BVnum, PM.Back_TexNo);
	if (PM.EXmem != 0) 	free(PM.EXDATA);
	if (PM.Values != 0)	Free_Matrix(PM.MVnum, PM.Values);
	if (PM.OBmem != 0)	free(PM.OBpos);
	if (NoexitMem > 0)	SAFE_FREE(NoexitPos);

	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	DSET
	Delete_DSET(&DSET);

	SAFE_FREE(UH);
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	UNDO
	if (Free_Area != NULL) SAFE_FREE(Free_Area);
	if (B_UndoFirstSave){
		for (int i = 0; i < 3; i++) DeleteFile(Undo_Temp_Name[i]);
	}
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	GL
	GL_Term(&Gp);
	//
	CFormView::OnDestroy();
}

void CRRI_GUIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROJECT_NAME, s_ProjName);
	DDX_Control(pDX, IDC_BUTTON_103, m_cConfirm);
	DDX_Control(pDX, IDC_BUTTON_111, B_cDelete);
	DDX_Text(pDX, IDC_MESH_SUBDEV, s_MeshSubdev);
	DDX_Text(pDX, IDC_EDIT_105, s_stLNG_deg);
	DDX_Text(pDX, IDC_EDIT_106, s_stLNG_min);
	DDX_Text(pDX, IDC_EDIT_107, s_stLNG_sec);
	DDX_Text(pDX, IDC_EDIT_108, s_endLNG_deg);
	DDX_Text(pDX, IDC_EDIT_109, s_endLNG_min);
	DDX_Text(pDX, IDC_EDIT_110, s_endLNG_sec);
	DDX_Text(pDX, IDC_EDIT_111, s_stLAT_deg);
	DDX_Text(pDX, IDC_EDIT_112, s_stLAT_min);
	DDX_Text(pDX, IDC_EDIT_113, s_stLAT_sec);
	DDX_Text(pDX, IDC_EDIT_114, s_endLAT_deg);
	DDX_Text(pDX, IDC_EDIT_115, s_endLAT_min);
	DDX_Text(pDX, IDC_EDIT_116, s_endLAT_sec);
	DDX_Text(pDX, IDC_MESH_H, s_MeshH);
	DDX_Text(pDX, IDC_MESH_V, s_MeshV);
	DDX_Control(pDX, IDC_COMBO_DATA, c_ComboData);
	DDX_Control(pDX, IDC_TAB_MAIN, c_TabMain);
	DDX_Control(pDX, IDC_SLIDER_TRANS, c_SliderBackT);
	DDX_Control(pDX, IDC_SLIDER_TRANS2, c_SliderDataT);
	DDX_Control(pDX, IDC_BUTTON_112, c_Badd);
	DDX_Control(pDX, IDC_BUTTON_113, c_Bdel);
	DDX_Control(pDX, IDC_BUTTON_LIST, c_BoundList);
	DDX_Control(pDX, IDC_BUTTON_401, c_Bcolor);
	DDX_Control(pDX, IDC_BUTTON_220, c_Racc);
	DDX_Text(pDX, IDC_STATIC_SELINFO, s_Select);
	DDX_Control(pDX, IDC_BUTTON_UNDO, c_Undo);
	DDX_Control(pDX, IDC_BUTTON_114, b_Breset);
	DDX_Text(pDX, IDC_STATIC_OUTLOC, s_OutLocation);
	DDX_Control(pDX, IDC_BUTTON_EACC, c_BEacc);
	DDX_Control(pDX, IDC_BUTTON_CSPARAM, c_LandCoverSoil);
	DDX_Control(pDX, IDC_BUTTON_LANDUSE_JP, c_LandCoverSoilJp);
	DDX_Control(pDX, IDC_BUTTON_LANDUSE_JP2, c_LandCoverSoilJp2);
	DDX_Text(pDX, IDC_MESHINFO_1, s_Location);
	DDX_Text(pDX, IDC_MESHINFO_2, s_H);
	//  DDX_Control(pDX, IDC_MESHINFO_3, s_Acc);
	DDX_Text(pDX, IDC_MESHINFO_4, s_CurrentD);
	DDX_Text(pDX, IDC_MESHINFO_5, s_Kind);
	DDX_Text(pDX, IDC_MESHINFO_3, s_Acc);
	DDX_Control(pDX, IDC_BUTTON_RESET, c_Reset);
	DDX_Control(pDX, IDC_BUTTON_DIR_UNDO, c_DirUndo);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, c_Cancel);
	DDX_Control(pDX, IDC_CHECK_DISPARROW, c_DispArrow);
	DDX_Text(pDX, IDC_ARROWINFO, s_ArrowInfo);
}
///-----------------------------------------------------------------------------------------------------------
// PreCreateWindow
///-----------------------------------------------------------------------------------------------------------  
BOOL CRRI_GUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
// :OnInitialUpdate
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CRRI_GUIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
// Resister Application Custom Message 
///_______________________________________________________________
//  各種パラメータの初期化
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	::GetCurrentDirectoryA(SIZE_05K, m_BootPath);
	strcpy(m_RecentPath, m_BootPath);
//_______________________________________________________________
///  各種パラメータの初期化
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Init_Params();
//
	c_SliderDataT.SetRange(0, 10, FALSE);
	c_SliderDataT.SetPos((int)((1. - PM.Data_Alpha)*10.));
	c_SliderBackT.SetRange(0, 10, FALSE);
	c_SliderBackT.SetPos((int)((1. - PM.Back_Alpha)*10.));

///_______________________________________________________________
//  モードタブの表示 
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CRect		Crect;					// メニューのマージンと移動量
	CWnd*		cw;
	///
	//--------------------------------- タブメニューコントロールの移動
	/// Menu Margin
	Menu_Margin = MENU_MARGIN;
	//
	B_Change_RRI = 0;					// RRI_INPUT が更新された数
	Init_Controls();
	Change_Tab();						// コントロールの移動 と　タブの表示
///_______________________________________________________________
//  Cover Soil データの作成
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (!Set_LU_CodeTable()) exit(1);
///_______________________________________________________________
//  開始
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetTimer(INIT_TIMER,50,NULL);
}


// CRRI_GUIView 診断

#ifdef _DEBUG
void CRRI_GUIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRRI_GUIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRRI_GUIDoc* CRRI_GUIView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRRI_GUIDoc)));
	return (CRRI_GUIDoc*)m_pDocument;
}
#endif //_DEBUG
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//   コントロールの移動と　初期ＴＡＢ 表示
/////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// 初期化 ---------------------------------------------------------------------------
void CRRI_GUIView::Init_Controls()
{
	CRect		Crect;
	CWnd*		cw;
	int			Ypos = 30;
//_____________________________________________________
//  Move
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for(int i=0;i<TAB_1_NUM;i++) {
		cw = GetDlgItem( TAB_1_ID[i] );
		cw->GetWindowRect( &Crect );

		if( i == 0 ) OFFSET_MODEL = Crect.left -20; // グループボックス
		//
		Crect.left -= OFFSET_MODEL;
		Crect.right -= OFFSET_MODEL;
		Crect.top -= Ypos;
		Crect.bottom -= Ypos;
		//
		cw->MoveWindow(&Crect,TRUE);
		cw->RedrawWindow();
		cw->GetWindowRect( &Crect );
	}
	//
	for(int i=0;i<TAB_2_NUM;i++) {
		cw = GetDlgItem( TAB_2_ID[i] );
		cw->GetWindowRect( &Crect );

		if( i == 0 ) OFFSET_TIMESERIES = Crect.left -17;
		//
		Crect.left	-= OFFSET_TIMESERIES;
		Crect.right  -= OFFSET_TIMESERIES;
		Crect.top -= Ypos;
		Crect.bottom -= Ypos;
		//
		cw->MoveWindow(&Crect,TRUE);
		cw->RedrawWindow();
	}
	for (int i = 0; i<TAB_3_NUM; i++) {
		cw = GetDlgItem(TAB_3_ID[i]);
		cw->GetWindowRect(&Crect);
		if (i == 0) OFFSET_TIMESERIES = Crect.left - 17; // グループボックス
		//
		Crect.left -= OFFSET_TIMESERIES;
		Crect.right -= OFFSET_TIMESERIES;
		Crect.top -= Ypos;
		Crect.bottom -= Ypos;
		//
		cw->MoveWindow(&Crect, TRUE);
		cw->RedrawWindow();
	}
	//
//___________________________________________________________________________________
//  コントロール内の文字列表示 
//    hydroSHEDS が定義されていれば、Mesh Size と データグループが定義される。     
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CEX = UNDEF;
	//if (PM.EXnum > 0) {
	//	for (int i = 0; i < PM.EXnum; i++){
	//		c_EXLIST.AddString(PM.EXDATA[i].Gname);
	//	}
	//}	
//_____________________________________________________
//  Display Tab Strings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CTabCtrl*	 CTab = (CTabCtrl*)GetDlgItem(IDC_TAB_MAIN);
	//
	CSize		Cs;
	CRect		Trect, UDrect;
	CTab->GetWindowRect(&Trect);
	//
	for (int i = 0; i < TAB_NUM; i++) {
		tc_TAB[i].mask = TCIF_TEXT;
		if (i == 0)		tc_TAB[i].pszText = " BASIN  ";
		else if (i == 1) tc_TAB[i].pszText = " DATA   ";
		else if (i == 2) tc_TAB[i].pszText = " EDIT   ";
		CTab->InsertItem(i, &tc_TAB[i]);
	}
///_____________________________________________________
//  Set Data Combo Box Strings
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	c_ComboData.Clear();
	for (int i = 0; i < FILE_IN_USE; i++) 	c_ComboData.AddString(MODEL_EDIT_NAME[i]);
	//
	for (int i = 0; i < Disp_UTM_NUM; i++) {
		cw = GetDlgItem(Disp_UTM_ID[i]);
		cw->ShowWindow(SW_HIDE);
	}
	//
	return;
}
//________________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//   パラメータの初期化
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// パラメータの初期化 ---------------------------------------------------------------------------
void CRRI_GUIView::Init_Params()
{
	//----------------------------------------------------- Init MEMBER VALUE
	COLD = UNDEF;
	CTAB = 0;
	CDATA = UNDEF;		// 現在データをUNDEFにする。
	EDDlg = NULL;

	RIVnum = 0;
	RivEX = FALSE;

	Cnt_CArea = 0;

	B_UndoFirstSave = FALSE;

	B_FirstStep		= TRUE;
	mark = EXmark		= NULL;
	AllDir			= NULL;
	//
	Arrow_Ang = 50.;
	Arrow_Head = 0.4;
	Col_Arrow = CREF_FCOL(ARROW_COLOR);
	//
	Famem = Fanum = 0;
	Free_Area		= NULL;
	//
	NoexitMem = NoexitNum = 0;
	///
	//----------------------------------------------------- Init DSET, MINFO,Param
	memset(&DSET, 0, sizeof(DATASET));
	///_______________________________________________________________
	//  選択の初期化
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	memset(&SI, 0, sizeof(SELECT_INFO));
	SI.Mem = 100;
	SI.ID = (IXYCOORD*)calloc(SI.Mem, sizeof(IXYCOORD));
	SI.HV = (IXYCOORD*)calloc(SI.Mem, sizeof(IXYCOORD));
	///_______________________________________________________________
	//  ツールチップの初期化
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	m_ToolTip.Create(this);
	m_ToolTip.AddTool(this, "");
	///
	// 変更ヒストリー用のメモリー確保
	UHmem = 200;
	UHnum = 0;
	if ((UH = (UndoHist*)calloc(UHmem, sizeof(UndoHist))) == NULL) {
		MessageBox("** Error **\n Cannot alloc history memory", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	///_______________________________________________________________
	//  テンプレートの読み込み
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (Read_RRI_Template())	{			// 
		MessageBox("** Error ** RRI_Input_Template.txt is not found in RRI_CONTENTS", "Alerm", MB_OK);
		DestroyWindow(); exit(1);
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// DSET 追加データの補足
	DSET.Init_Gamp = -0.1;
	DSET.Init_HG = -0.1;
	///
	//------------------------------------------PM
	MESH = (MINFO**)NULL;
	for (int i = 0; i < FILE_ALL_NUM; i++) {
		if (i < FILE_IN_NUM) DSET.Data_From[i] = UNDEF;
		DSET.need_save[i] = FALSE;
	}
	//--------------------------------------------------------Init PM
	memset(&PM, 0, sizeof(PARAMS));
	//
	PM.B_MeshLine= PM.B_Back = PM.B_ColorMesh = TRUE;
	PM.B_UseGuide = PM.B_LatLng = TRUE;
	PM.B_Disp_Frame = PM.B_Disp_Ground = PM.B_Disp_Legend = TRUE;
	//
	PM.Mesh_Thresh = 1;
	//
	PM.Tool_Rate = 0.05;
	//
	PM.Col_Frame = RGB(200, 0, 200);
	PM.Col_LegendChar = COLOR_BLACK;
	PM.Col_Observatory = COLOR_BLUE;
	//
	PM.Lw = 8;
	PM.Lh = 18;
	PM.Lfont = 0;					// Arial
	PM.Lstyle = FONT_REGULAR;		// FONT_REGULAR=1, 2, 3
	//
	PM.stLAT = PM.stLNG = PM.Size = DUNDEF;
	PM.TSDLG_minH = PM.TSDLG_minV = UNDEF;
	//
	PM.Pos_Legend.x = 50.;
	PM.Pos_Legend.y = 400.;
	PM.Lsize = 20;
	//
	PM.Data_Alpha = PM.Back_Alpha = 1.;
	//
	PM.SizeID = 5;
	PM.B_CHECK_10MINS = false;
	//
	//----------------------------------------------------- Init Param
	RIVnum = 0;
	//
	//----------------------------------------------------- RRI_ENV Initial file
	//
	FILE*	fp = fopen("./RRI_CONTENTS/RRI.env","r");
	if (fp == NULL) {
		MessageBox("Cannot open RRI.env file", "Exit", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(); exit(1);
	}
	PM.EXnum = PM.EXmem = 0;
	PM.Cam_Dir = CAM_DIR_UP;
	//
	int		pos,Did;
	char		buf[SIZE_1K], head[SIZE_1K], value[SIZE_1K],gp[SIZE_1K];
	CString	oldGN, GN;		// Group Name;
	oldGN = GN = _T("");
	//
	MENU_WIDTH = MENU_MARGIN;
	//
	while (fgets(buf, SIZE_1K, fp) != NULL) {
		pos = 0; getstr(buf, &pos, head, SIZE_1K);
		if (strcmp(head, "[IMAGE_FOLDER]") == 0) {
			getstr(buf, &pos, PM.IM_Folder, 256);
		}
		else if (strcmp(head, "[BUILDER_MENU_WIDTH]") == 0) {
			getstr(buf, &pos, value,SIZE_1K);
			MENU_WIDTH = atoi(value);
		}
		else if (strcmp(head, "[TIME_DIFFERENCE]") == 0) {
			getstr(buf, &pos, value, SIZE_1K);
			PM.TimeDiff = atof(value);
		}
		else if (strcmp(head, "[ADD_HYDROSHEDS]") == 0 || strcmp(head, "[ADD_JFLOW]") == 0) {
			getstr(buf, &pos, gp, SIZE_1K);
			GN = gp;
			///
			// Alloc
			if (PM.EXmem <= 0) {
				PM.EXmem = 30;
				if ((PM.EXDATA = (EX_DATA*)malloc(PM.EXmem*sizeof(EX_DATA))) == NULL ) {
					MessageBox("Cannot allocate external data file", "Exit", MB_OK | MB_ICONEXCLAMATION);
					fclose(fp); DestroyWindow(); exit(1);
				}
				for (int i = 0; i < PM.EXmem; i++) memset(&PM.EXDATA[i], 0x00, sizeof(EX_DATA));
			}
			///
			// Set グループ名がない、もしくは、グループ名が同じであれば　PM.EXnum のグループに加える。
			strcpy(PM.EXDATA[PM.EXnum].Gname, gp); // グループ名のコピー

			// ファイル種別
			getstr(buf, &pos, value, SIZE_1K);
			if (strcmp(value, "DEM") == 0)			Did = EX_DEM;
			else if (strcmp(value, "ACC") == 0)		Did = EX_ACC;
			else if (strcmp(value, "DIR") == 0)		Did = EX_DIR;

			// ファイル名
			getstr(buf, &pos, PM.EXDATA[PM.EXnum].Files[Did].fname, SIZE_02K);

			// 諸元
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].span = atoi(value);
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].byte = atoi(value);
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].stlng = atoi(value);
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].endlng = atoi(value);
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].Highlat = atoi(value);
			getstr(buf, &pos, value, SIZE_1K); PM.EXDATA[PM.EXnum].Files[Did].Lowlat = atoi(value);
			//
			PM.EXDATA[PM.EXnum].Files[Did].subdev = 60 * (60 / PM.EXDATA[PM.EXnum].Files[Did].span);
			PM.EXDATA[PM.EXnum].Files[Did].Htotal =
				(PM.EXDATA[PM.EXnum].Files[Did].endlng - PM.EXDATA[PM.EXnum].Files[Did].stlng) * PM.EXDATA[PM.EXnum].Files[Did].subdev;
			PM.EXDATA[PM.EXnum].Files[Did].Vtotal =
				(PM.EXDATA[PM.EXnum].Files[Did].Highlat - PM.EXDATA[PM.EXnum].Files[Did].Lowlat) * PM.EXDATA[PM.EXnum].Files[Did].subdev;
			// set
			PM.EXDATA[PM.EXnum].Files[Did].Bset = TRUE;

			// EXnum Increment
			if (PM.EXDATA[PM.EXnum].Files[0].Bset && PM.EXDATA[PM.EXnum].Files[1].Bset &&
				PM.EXDATA[PM.EXnum].Files[2].Bset) {
				PM.EXDATA[PM.EXnum].kind = 0;			// hydroSHEDS を　０とする。
				PM.EXDATA[PM.EXnum].Allset = TRUE; 
				PM.EXnum++;
			}
			oldGN = GN;
		}
	}
	if (!PM.EXDATA[0].Allset) PM.EXnum = 0;
	//
	fclose(fp);
	//_____________________________________________________
	///  READ INI FILE 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// color data

	//FILE*			fp;
	char				inchar[64];
	int				ID,num;
	int				No, r, g, b;
	COLVAL_FIX		*C0;
	if ((fp = fopen("./RRI_CONTENTS/COLOR_DATA_B.DAT", "r")) == NULL) {
		MessageBox("** Error **\nCannot find [ /RRI_CONTENTS/COLOR_DATA_B.DAT ]..", "Error", MB_OK);
		DestroyWindow(); exit(1);
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  追加 メッシュカラー
	fgets(buf, 128, fp); pos = 0;
	getstr(buf, &pos, inchar, 64);	// [MESH_COLOR]
	getstr(buf, &pos, inchar, 64); num = atoi(inchar);	// 10
	for (int i = 0; i < num; i++) {
		fgets(buf, 128, fp); pos = 0;
		getstr(buf, &pos, inchar, 64); ID = atoi(inchar);
		getstr(buf, &pos, inchar, 64); r = atoi(inchar);
		getstr(buf, &pos, inchar, 64); g = atoi(inchar);
		getstr(buf, &pos, inchar, 64); b = atoi(inchar);
		PM.COL_MESH[ID] = RGB(r, g, b);
	}
	//
	for (int i = 0; i < FILE_ALL_NUM; i++) memset(&PM.Dcol[i], 0, sizeof(COLVAL_FIX));
	//
	while (fgets(buf, 128, fp) != NULL) {
		pos = 0;
		getstr(buf, &pos, inchar, 64);	No = atoi(inchar);
		if (No < 100) { C0 = &PM.Dcol[No];}
		else if (No >  LU_FILE_JP) break;
		//
		getstr(buf, &pos, inchar, 64);   C0->num = atoi(inchar);
		//
		getstr(buf, &pos, inchar, 64);   C0->Equal =  (BOOL)atoi(inchar);
		//
		getstr(buf, &pos, inchar, 64);   C0->Mos =  (BOOL)atoi(inchar);
		//
		getstr(buf, &pos, inchar, 64);   C0->alpha = (float)atof(inchar);
		//
		for (int n = 0; n<C0->num; n++) {
			fgets(buf, 256, fp); pos = 0;
			getstr(buf, &pos, inchar, 64); C0->val[n] = atof(inchar);
			getstr(buf, &pos, inchar, 64); r = atoi(inchar);
			getstr(buf, &pos, inchar, 64); g = atoi(inchar);
			getstr(buf, &pos, inchar, 64); b = atoi(inchar);
			C0->Rcol[n] = RGB(r, g, b);
			C0->Fcol[n] = F_COLOR(r, g, b);
		}
		C0->set = TRUE;
	}
	fclose(fp);
	//_____________________________________________________
	///  スクリーンツールイメージの読み込みと透明処理
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int		cnt,id,iplane;
	BYTE*	image;
	BYTE		rr, gg, bb;
	image = Get_Image_File(RRI_SCREEN_TOOL_IMAGE, &SCHnum, &SCVnum, &iplane);
	//
	if ((Tool_Image = (BYTE*)malloc(4 * SCHnum*SCVnum)) == NULL) {
		MessageBox("** Error **\nCannot allocate tool image.....", "Error", MB_OK);	
		DestroyWindow(); exit(1);
	}
	id = cnt = 0;
	for (int v = 0; v < SCVnum; v++) {
		for (int h = 0; h < SCHnum; h++) {
			rr = Tool_Image[cnt++] = image[id++];
			gg = Tool_Image[cnt++] = image[id++];
			bb = Tool_Image[cnt++] = image[id++];
			if (rr == 0 && gg == 0 && bb == 0)  Tool_Image[cnt++] = 0;
			else                            Tool_Image[cnt++] =255;
		}
	}
	SAFE_FREE(image);
}
///________________________________________________________________________________________
// / /////////////////////////////////////////////////////////////////////////////////////
///   RRI_INPUT_TEMPLATE の読み込み
// /////////////////////////////////////////////////////////////////////////////////////
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int	 CRRI_GUIView::Read_RRI_Template()
{
	FILE*		fp;
	if ((fp = fopen(RRI_TEMPLATE_FILE, "r")) == NULL) return UNDEF;
	//
	strcpy(DSET.Proj_Folder, "");
	strcpy(DSET.InputFile, "");
	//
	int ret = Read_RRI_INPUT(&DSET,fp);
	memcpy(&DSET.LU_Model, &DSET.LUdata[0], sizeof(LUINFO));
	//
	return 0;
}
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//   FIX FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   CALL BACK
int AFXAPI CRRI_GUIView::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED && lpData)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	return 0;
}
//   BUTTON_DIR
BOOL	CRRI_GUIView::Button_Dir(CString* m_DirName,char* m_RecentPath,CString ttl,BOOL New)
{
	CWnd			*pWnd;
	static char		pszRetPath[CHARSIZE];
	LPMALLOC		pMalloc;
	//--------------------------------------
	//	ディレクトリ選択ダイアログの表示
	//--------------------------------------
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{ 
		char		cRetPath[CHARSIZE];
		ITEMIDLIST	*pList;
		BROWSEINFO	Info;

		pWnd = (CWnd*)AfxGetApp()->m_pMainWnd;
		HWND hWnd = pWnd->m_hWnd; 
		Info.hwndOwner = hWnd;
		Info. pidlRoot = 0;
		Info.pszDisplayName = cRetPath;
		Info.lpszTitle =  ttl;
		Info.lpfn   = BrowseCallbackProc;
		Info.lParam = (LPARAM)m_RecentPath;
		if (New) Info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;	//フォルダの選択,作成
		else     Info.ulFlags = BIF_RETURNONLYFSDIRS;
		

		pWnd->ModifyStyle(WS_CHILD,WS_POPUP,0);
		//---  ダイアログ表示  -------------
		if( (pList = (ITEMIDLIST*)SHBrowseForFolder(&Info)) == NULL ) {pMalloc->Release();return FALSE;}
		// ITEMIDLIST からフルパスを得る
		SHGetPathFromIDList(pList,pszRetPath);
		//ITEMIDLIST の開放
		pMalloc->Free(pList);
		//選択ディレクトリ表示
		*m_DirName = pszRetPath;
		strcpy(m_RecentPath,*m_DirName);
		pMalloc->Release();
		//
	}
	return TRUE;
}
BOOL	CRRI_GUIView::Button_Dir(char* m_DirName, char* m_RecentPath)
{
	CWnd			*pWnd;
	static char		pszRetPath[SIZE_02K];
	LPMALLOC		pMalloc;
	//--------------------------------------
	//	ディレクトリ選択ダイアログの表示
	//--------------------------------------
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		char		cRetPath[SIZE_02K];
		ITEMIDLIST	*pList;
		BROWSEINFO	Info;

		pWnd = (CWnd*)AfxGetApp()->m_pMainWnd;
		HWND hWnd = pWnd->m_hWnd;
		Info.hwndOwner = hWnd;
		Info.pidlRoot = 0;
		Info.pszDisplayName = cRetPath;
		Info.lpszTitle = _T("フォルダを選択してください");
		Info.lpfn = BrowseCallbackProc;
		Info.lParam = (LPARAM)m_RecentPath;
		Info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;	//フォルダの選択,作成


		pWnd->ModifyStyle(WS_CHILD, WS_POPUP, 0);

		//---  ダイアログ表示  -------------
		if ((pList = (ITEMIDLIST*)SHBrowseForFolder(&Info)) == NULL) { pMalloc->Release(); return FALSE; }
		// ITEMIDLIST からフルパスを得る
		SHGetPathFromIDList(pList, pszRetPath);
		//ITEMIDLIST の開放
		pMalloc->Free(pList);
		//選択ディレクトリ表示
		strcpy(m_DirName,pszRetPath);
		strcpy(m_RecentPath, m_DirName);
		pMalloc->Release();
		//
	}
	return TRUE;
}
//   RENDER SCENE
void	CRRI_GUIView::Render_Scene() {
	if( FAILED( GL_Render_Scene( &Gp)) ) {RETURN( "Failed !");}
//	RETURN("Ready....");
}
//______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//
//   ＭＯＵＳＥ and ＫＥＹＢＯＡＲＤ
//
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   Ｐｒｅｔｒａｎｓｌａｔｅ　Ｍｅｓｓａｇｅ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL CRRI_GUIView::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message){
	case WM_MOUSEMOVE: m_ToolTip.RelayEvent(pMsg); break;
	case WM_QUERYENDSESSION:

		MessageBox("終了させないよ", "", MB_OK);
		return FALSE;
		break;
	case WM_ENDSESSION:
		if (pMsg->wParam == FALSE) MessageBox("俺の言ったとおりだろう", "", MB_OK);
		break;
	}
		///---------------------------------------------
	// システムキー　ダウン
	///---------------------------------------------
	if (pMsg->message == WM_SYSKEYDOWN) {
		if (pMsg->wParam == VK_ALTKEY) STAT(KEY_ALT_DOWN) = TRUE;
	}
	else if (pMsg->message == WM_SYSKEYUP) {
		if (pMsg->wParam == VK_ALTKEY) STAT(KEY_ALT_DOWN) = FALSE;
	}
	///---------------------------------------------
	// キー　ダウン
	///---------------------------------------------
	else if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_RETURN:	return TRUE;

		case VK_CONTROL:	STAT(KEY_CTRL_DOWN) = TRUE;
			break;
		case VK_SHIFT:	STAT(KEY_SHIFT_DOWN) = TRUE;
			break;
		case 'A':   IF_STAT(KEY_CTRL_DOWN) {		// 全画面表示
						if (PM.B_MeshLine)  Gp.Gobj[OBJID_LINE].display = FALSE;
						GL_Redraw(&Gp, TRUE, TRUE, FALSE, ALL_OBJECTS, TRUE);
					}
					break;

		}
	}
	///---------------------------------------------
	// キー　アップ
	///---------------------------------------------
	else if (pMsg->message == WM_KEYUP) {
		switch (pMsg->wParam) {
		case VK_RETURN:	return TRUE;

		case VK_ESCAPE:  IF_STAT(AREA_DECIDE_MODE) {
							STAT(AREA_DECIDE_MODE) = FALSE;
							STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;
							GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
							SAFE_FREE(Free_Area); Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
						}
						break;

		case VK_CONTROL:	STAT(KEY_CTRL_DOWN) = FALSE;break;

		case VK_SHIFT:	STAT(KEY_SHIFT_DOWN) = FALSE;break;

		case VK_SNAPSHOT:   IF_STAT(IS_READY) {
								{ COMMENT("Now capturing....."); }
								CString fname;
								if (DSET.set) fname.Format("%s/Hard_Copy_%d.bmp", DSET.Proj_Folder, Gp.Hcopy_cnt++);
								else         fname.Format("%s/Hard_Copy_%d.bmp", m_BootPath, Gp.Hcopy_cnt++);
								//
								if (FAILED(GL_Save_Window(&Gp,fname))) {
									COMMENT("** Error ** Memory allocate error"); break;
								}
							}
								{COMMENT("Capture completed.....!"); }
							//
							break;
		}
	}
	//// 

	return CFormView::PreTranslateMessage(pMsg);
}

void CRRI_GUIView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (PM.Model && Gp.cam[0].set ) 
		GL_Redraw(&Gp, FALSE, FALSE, FALSE,ALL_OBJECTS, TRUE);
}
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//
//   MOUSE

/// MOUSE ---------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CRRI_GUIView::OnMouseMove(UINT nFlags, CPoint point)
{
	IFNOT_STAT(ON_SCREEN) { CFormView::OnMouseMove(nFlags, point); return; }
	//---------------------------------------------------------------------------------		
	if (point.x == LastPoint.x && point.y == LastPoint.y) return;
	//--------------------------------------------------------------------------------- 基本定数
	double		mx, my, aH, aV, Rxz;
	CString		str;
	CRect		rect;
	Gp.win.cw->GetWindowRect(&rect);
	int		id, xid, yid;
	int		No[4];
	//
	if (!rect.PtInRect(point)) {							// 領域を外れた場合
		//STAT(MS_LB_DOWN) = FALSE;
		//STAT(MS_RB_DOWN) = FALSE;
		//
		//IF_STAT(AREA_DECIDE_MODE) {
		//	GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
		//	STAT(AREA_DECIDE_MODE) = FALSE;
		//	STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;
		//	SAFE_FREE(Free_Area); Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
		//}
		::ReleaseCapture(); return;
	}
	//
	double  xspan = (double)rect.Width();
	double  yspan = (double)rect.Height();
	//
	double	movex = (double)(point.x - LastPoint.x) / xspan * Gp.cam[CVIEW].Dw;
	double	movey = (double)(point.y - LastPoint.y) / yspan * Gp.cam[CVIEW].Dh;
	//
	GL_Trans_Pos(&Gp, point, &mx, &my);
	//
	xid = (int)mx;	// xid yid は増分
	yid = (int)my;
	//____________________________________________________________________
	/// 　マウス移動のみ　ツールチップの表示
	//--------------------------------------------------------------------
	IF_STAT(PROC_CONFIRM_MESH) {
		if ((xid >= 0 && xid < PM.MHnum) && (yid >= 0 && yid < PM.MVnum)) {
			if (strlen(MESH[yid][xid].name) != 0 && MESH[yid][xid].flag > 0) {
				m_ToolTip.UpdateTipText(MESH[yid][xid].name, this);
				m_ToolTip.Update();
				m_ToolTip.Pop();
			}
			else  {
				m_ToolTip.UpdateTipText("", this);
				m_ToolTip.Update();
				m_ToolTip.Pop();
			}
		}
	}
	if (PM.B_Disp_Ground && DSET.RGnum != 0) {		// 地上観測所
		for (int i = 0; i<DSET.RGnum; i++) {
			if (DSET.RGpos[i].X == DUNDEF) continue;
			if (mx > DSET.RGpos[i].X - 0.5 && mx <DSET.RGpos[i].X + 0.5) {
				if (my > DSET.RGpos[i].Z - 0.5 && my < DSET.RGpos[i].Z + 0.5) {
					if (strlen(DSET.RGpos[i].name) != 0) {
						m_ToolTip.UpdateTipText(DSET.RGpos[i].name, this);
						m_ToolTip.Update();
						m_ToolTip.Pop();
					}
				}
			}
		}
	}

	//____________________________________________________________________
	/// 　左マウス操作
	//--------------------------------------------------------------------
	///
	//
	xid = (int)(mx + 0.5);	// xid yid は増分
	yid = (int)(my + 0.5);
	// コントロールキーを押していない。
	IFNOT_STAT(KEY_CTRL_DOWN) {
		if (STAT(MS_LB_DOWN)) {
			//_______________________________________________________
			/// 　エディットウィンドウの移動
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (STAT(DISP_EDITWIN) && STAT(MS_RUBBER_START)) {
				// Safety
				if (xid < 0 || xid >(PM.MHnum + PM.SizeID) || yid < 0 || yid >(PM.MVnum + PM.SizeID)) goto EndProc;
				PM.CX = xid;
				if (PM.CX - PM.SizeID < 0)		PM.CX = PM.SizeID;
				if (PM.CX + PM.SizeID >= PM.MHnum)	PM.CX = PM.MHnum - PM.SizeID - 1;
				PM.CY = yid;
				if (PM.CY - PM.SizeID < 0)		PM.CY = PM.SizeID;
				if (PM.CY + PM.SizeID >= PM.MVnum)	PM.CY = PM.MVnum - PM.SizeID - 1;
				//
				mx = PM.CX;
				my = PM.CY;
				Draw_Band_Area(mx, my);
				//
				EDDlg->Reflesh_Data();
				if (PM.Move_Cnt != 0) Edit_Mesh_Model();	// この段階で表示
				//
				EDDlg->Set_Values();
			}
			//_______________________________________________________
			/// 　メッシュ追加・削除の範囲指示
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (STAT(AREA_DECIDE_MODE)) {
				if (Free_Area[Fanum - 1].x != mx && Free_Area[Fanum - 1].y != my) {
					Free_Area[Fanum].x = mx;
					Free_Area[Fanum].y = my;
					Fanum++;
					//
					if (Fanum == Famem) {
						Famem += 500;
						if ((Free_Area = (XYCOORD*)realloc(Free_Area, Famem*sizeof(XYCOORD))) == NULL){
							STAT(AREA_DECIDE_MODE) = FALSE;
							STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;
							Free_Area = NULL; Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
							RETURN("** Error ** Cannot ReAlloc Free Area");
						}
					}
					//
					if (Fanum > 2) Draw_Free_Area(FALSE);
					Change_Cursor(&Gp, IDC_CROSS);
				}
			}
		}
		else if (nFlags&MK_RBUTTON) {
			if (PM.B_ScreenTool && STAT(MOVE_SCREEN_TOOL)){
				movex = (double)(point.x - LastPoint.x);
				movey = (double)(point.y - LastPoint.y);
				NOWX += movex;
				NOWY -= movey;
				Make_Screen_Tool(FALSE);
			}
			else if (STAT(MOVE_LEGEND)) {
				movex = (double)(point.x - LastPoint.x);
				movey = (double)(LastPoint.y - point.y);
				//
				PM.Pos_Legend.x += movex;
				PM.Pos_Legend.y += movey;
				PM.Change_Data = TRUE;
				Make_LEGEND();
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LEGEND, TRUE);
			}
		}
	}
	//_______________________________________________________
	/// 　移動
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// コントロールキーが押されている。移動　カメラ視点移動  コントロールキー有効
	else {	
		if (STAT(MS_LB_DOWN) && !STAT(KEY_SHIFT_DOWN)) {
			if (CVIEW == ORTHO) {						// ＯＲＴＨＯの場合　カメラ位置を変えない
				Gp.cam[CVIEW].endH -= movex;  Gp.cam[CVIEW].stH -= movex;
				Gp.cam[CVIEW].endV += movey;  Gp.cam[CVIEW].stV += movey;
				Gp.cam[CVIEW].set = FALSE;
			}
			else {
				Gp.cam[CVIEW].tx -= movex;  Gp.cam[CVIEW].cx -= movex;
				Gp.cam[CVIEW].tz += movey;  Gp.cam[CVIEW].cz += movey;
				Gp.cam[CVIEW].set = FALSE;
			}
			//
			GL_Redraw(&Gp, FALSE, TRUE, FALSE, UNDEF, TRUE);
		}
	}
EndProc:
	//
	LastPoint = point;
	CFormView::OnMouseMove(nFlags, point);
}
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Ｍｏｕｓｅ　Ｗｈｅｅｌ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL CRRI_GUIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags&MK_CONTROL) {	// コントロールキー有効
		double	ang;
		double	Hspan, Vspan, CT;
		int		Pixel;
		//
		CT = (Gp.cam[CVIEW].stV + Gp.cam[CVIEW].endV) / 2.;
		Vspan = (Gp.cam[CVIEW].endV - Gp.cam[CVIEW].stV) / 2.;
		if (zDelta < 0)		Vspan *= 1.05;
		else				Vspan *= 0.95;
		//
		Gp.cam[CVIEW].endV = Vspan + CT;
		Gp.cam[CVIEW].stV = CT - Vspan;
		//
		Gp.cam[CVIEW].Dh = fabs((Gp.cam[CVIEW].endV - Gp.cam[CVIEW].stV));
		Gp.cam[CVIEW].Dw = Gp.cam[CVIEW].Dh*Gp.cam[CVIEW].aspect;
		//
		Hspan = Gp.cam[CVIEW].Dw / 2.;
		CT = (Gp.cam[CVIEW].stH + Gp.cam[CVIEW].endH) / 2.;
		Gp.cam[CVIEW].endH = CT + Hspan;
		Gp.cam[CVIEW].stH = CT - Hspan;
		//
		Gp.cam[CVIEW].set = FALSE;
		//
		
		if ((Gp.cam[CVIEW].endH - Gp.cam[CVIEW].stH) <= ARROW_LIMIT) {
			STAT(ENABLE_DRAW_ARROW) = TRUE;
			s_ArrowInfo = "Arrow visible"; UDF;
			Gp.Gobj[OBJID_ARROW].display = TRUE;
			STAT(DISP_ARROW) = TRUE;
		}
		else	 {
			STAT(ENABLE_DRAW_ARROW) = FALSE;
			s_ArrowInfo = "Arrow invisible"; UDF;
			Gp.Gobj[OBJID_ARROW].display = FALSE;
			STAT(DISP_ARROW) = FALSE;
		}
		//
		if (PM.B_MeshLine) {
			Pixel = (int)(Gp.win.cWidth / (Hspan * 2));
			if (Pixel > PM.Mesh_Thresh) Gp.Gobj[OBJID_LINE].display = TRUE;
			else                      Gp.Gobj[OBJID_LINE].display = FALSE;
		}
		//
		GL_Redraw(&Gp, FALSE, TRUE, FALSE, UNDEF, TRUE);
	}
	//
	// 編集画面の拡大・縮小
	//
	else if (STAT(DISP_EDITWIN)) {
		int		OldID = PM.SizeID;
		if (zDelta > 0) {
			PM.SizeID -= 3;
			if (PM.SizeID < 3) PM.SizeID = 3;
		}
		else   {
			PM.SizeID += 3;
			if (PM.SizeID > 10) PM.SizeID = 10;
		}
		if (OldID != PM.SizeID) {
			EDDlg->Reflesh_Data();
			EDDlg->Change_Frame_Size();
			Draw_Band_Area(DUNDEF, DUNDEF);
		}
	}
	//
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}

//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＬＢｕｔｔｏｎ　Ｄｏｗｎ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	STAT(MS_LB_DOWN) = TRUE;
	Gp.win.cw->GetWindowRect(&rect);
	if (!rect.PtInRect(point)) { CFormView::OnLButtonDown(nFlags, point); return; }// 領域を外れた場合
	///
	//	Tool_Frame;
	int		ret;
	if( STAT(SET_WORLD_VIEW) && PM.B_ScreenTool ) {
		if ((ret = Decide_Tool(point)) > 0) { EX_Tool(ret); return; }
	}
	//
	LastPoint = point;
	//
	double		mx, my;
	int			xid, yid;
	//
	GL_Trans_Pos(&Gp, point, &mx, &my);
	xid = (int)mx;
	yid = (int)my;
	CID = yid*PM.MHnum + xid;
	//
	IF_STAT(AREA_DECIDE_MODE) {
		Fanum = 0;
		Free_Area[Fanum].x = mx;
		Free_Area[Fanum].y = my;
		Fanum++;
		//
		Change_Cursor(&Gp, IDC_CROSS);
	}
	else {
		if (!(nFlags&MK_CONTROL) && !(nFlags&MK_SHIFT)) 	STAT(MS_RUBBER_START) = TRUE;
	}
	//
	CFormView::OnLButtonDown(nFlags, point);
}

//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＬＢｕｔｔｏｎ　Ｕｐ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	STAT(MS_LB_DOWN) = FALSE;
	//
	Gp.win.cw->GetWindowRect(&rect);
	if (!rect.PtInRect(point)) {   // 領域を外れた場合, すべてのモードをクリヤーする。 マウス移動が効かない対処
		IFNOT_STAT(DISP_EDITWIN) {
			Clear_Mode();
			Clear_Select();
		}
		return; 
	}
	//
	double		mx, my,lng,lat,val;
	int			xid, yid,acc,D,M,S;
	CString		str1, str2, str3,str,DD;
	BOOL			DISPLAY;
	///
	//  マウスアップしたときツールのエリアであれば抜ける
	int		ret;
	if (STAT(SET_WORLD_VIEW) && PM.B_ScreenTool) {
		if ((ret = Decide_Tool(point)) > 0) return;
	}
	//
	COMMENT("");
	GL_Trans_Pos(&Gp, point, &mx, &my);
	if (mx < 0. || my < 0.) return;			// -0.* -> 0
	xid = (int)(mx + EPS8);
	yid = (int)(my + EPS8);
	//
	if (STAT(PROC_CONFIRM_MESH) || STAT(USE_EXTERNAL_DEM)) {
		if ((xid < 0 || xid >= PM.MHnum) || (yid < 0 || yid >= PM.MVnum)) {
			Clear_Select(); return;
		}
	}
	LastSelectPoint.x = xid;
	LastSelectPoint.y = yid;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//   河川の最下流端の指定

	IF_STAT(PROC_INDICATE_RIVMESH) {					// 下流端の指定 
		Trans_COORD_LATLNG(EX_ACC, mx, my, &lng, &lat);				// 注意 ＡＣＣを対象とする。
		if ((!STAT(KEY_CTRL_DOWN) && !STAT(KEY_SHIFT_DOWN) && RIVnum == 0 ) ||			// 何も押されていない時
			(!STAT(KEY_CTRL_DOWN) && STAT(KEY_SHIFT_DOWN) && (RIVnum > 0))) {			// 複数が選択

			if (PM.B_UseJFlow) {
				acc = Get_JFlwMesh_Value(lng, lat, EX_ACC);
			}
			else {
				acc = Get_HYDROSHEDS_Value(lng, lat, EX_ACC);
			}
			if (acc >= DSET.Riv_Thresh)  {
				//
				RIVinfo[RIVnum].lng = lng + EPS8;		// 抑えたポイント
				RIVinfo[RIVnum].lat = lat + EPS8;
				RIVinfo[RIVnum].x = xid;
				RIVinfo[RIVnum].y = yid;
				RIVnum++;
				//
				Disp_River_Pos(TRUE);
				//
				DD.Format("xid = %d yid = %d lng=%lf, lat=%lf", xid, yid, lng, lat);
				COMMENT(DD);
				//
				DegtoDeg3(lng, &D, &M, &S);
				str1.Format("Longitude %d:%2d'%2d\"\n", D, M, S);
				if (lat >= 0.) {
					DegtoDeg3(lat, &D, &M, &S);
					str2.Format("Latitude(north) %d:%2d'%2d\"\n", D, M, S);
				}
				else   {
					DegtoDeg3(-lat, &D, &M, &S);
					str2.Format("Latitude(south) %d:%2d'%2d\"\n", D, M, S);
				}
				str3.Format("Acc %d", acc);
				str.Format("Is this outlet ? \n%s%s%s", str1, str2, str3);
				//
				if (MessageBox(str, "confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
					Del_River_Pos(TRUE);		// STAT はそのまま
				}
			}
			else {
				str.Format("The cell [ACC=%d ] is not ｒiver cell", acc);
				COMMENT(str);
			}
		}
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//   下流端指定の除外、追加・削除領域指定終了

	IF_STAT(PROC_DISPLAY_MESH) {

		// 河川のポイントをとらえて　除外する。
		IFNOT_STAT(AREA_DECIDE_MODE) {
			Trans_COORD_LATLNG(EX_ACC, mx, my, &lng, &lat);				// 注意 ＡＣＣを対象とする。
			COMMENT("!...");
			if (mark[yid][xid]) {
				if ((!STAT(KEY_CTRL_DOWN) && !STAT(KEY_SHIFT_DOWN)) && (!RivEX)) {			// 単独のみ
					if (PM.B_UseJFlow) {
						acc = Get_JFlwMesh_Value(lng, lat, EX_ACC);
					}
					else {
						acc = Get_HYDROSHEDS_Value(lng, lat, EX_ACC);
					}
					if (acc >= DSET.Riv_Thresh)  {
						//
						COMMENT("Select end cell of excluded area...Push exclude button");
						RivEXpos.lng = lng + EPS8;
						RivEXpos.lat = lat + EPS8;
						RivEXpos.x = (double)xid;
						RivEXpos.y = (double)yid;
						RIVinfo[RIVnum].x = xid;
						RIVinfo[RIVnum].y = yid;
						RivEX = TRUE;
						//
						Disp_River_Pos(FALSE);
						//
						DegtoDeg3(lng, &D, &M, &S);
						str1.Format("Longitude %d:%d:%d\n", D, M, S);
						if (lat >= 0.) {
							DegtoDeg3(lat, &D, &M, &S);
							str2.Format("Latitude(north) %d:%d:%d\n", D, M, S);
						}
						else   {
							DegtoDeg3(-lat, &D, &M, &S);
							str2.Format("Latitude(south) %d:%d:%d\n", D, M, S);
						}
						str3.Format("Acc %d", acc);
						str.Format("Exclude upper area ? \n%s%s%s", str1, str2, str3);
						//
						if (MessageBox(str, "confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
							Del_River_Pos(FALSE);		// STAT はそのまま
							//Show_Command(ON, "Confirm or Change Mesh Area or Reset");
						}
						else {		// ここでEXCLUDE を実行する。ボタンは不要？
							Exclude_Basin();
						}
					}
					else {
						str.Format("The cell [ACC=%d ] is not river cell", acc);
						COMMENT(str);
					}
				}
			}
		}

		// 領域を指定して　追加・除外する。
		else {
			Draw_Free_Area(TRUE);		// 閉曲線にする。
			if (STAT(ADD_MESH_MODE))		str = "Add this area ?";
			else  if (STAT(DEL_MESH_MODE))	str = "Delete this area ?";
			//
			if (MessageBox(str, "confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
				GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
				STAT(AREA_DECIDE_MODE) = FALSE;
				STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;

				SAFE_FREE(Free_Area); Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
				//Show_Command(ON, "Confirm or Change Mesh Area or Reset");
			}
			else {
				if (STAT(ADD_MESH_MODE))			Add_Mesh();
				else  if (STAT(DEL_MESH_MODE))		Del_Mesh();
				//
				GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MOUSE_BAND, TRUE);
				STAT(AREA_DECIDE_MODE) = FALSE;
				STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;

				SAFE_FREE(Free_Area); Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
				//Show_Command(ON, "Confirm or Change Mesh Area or Reset");
			}
		}
	}

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//   編集モードにおける河川指定
	if ((STAT(PROC_CONFIRM_MESH) && !STAT(DISP_EDITWIN)) || STAT(DEFINE_BASIN)) {
		int		Avcnt = 0;
		xid = (int)mx;
		yid = (int)my;
		//
		if (!(nFlags&MK_CONTROL)) {
			if (MESH[yid][xid].flag == 0) {
				Clear_Select();
				return;
			}
//
			if (!(nFlags&MK_SHIFT)) Clear_Select();
			//
			BOOL		exist = FALSE;
			int		rip,cnt = 0;
			CString  valform;
			//
			if (SI.Num != 0) {
				for (int i = 0; i < SI.Num; i++) {
					if (SI.HV[i].x == xid && SI.HV[i].y == yid) {
						exist = TRUE;
						SI.Nums[MESH[yid][xid].flag%ID_MESH_LOC]--;
						if (MESH[yid][xid].flag >= ID_MESH_LOC)  SI.Nums[ID_MESH_LOC]--;
					}
					else { 
						SI.HV[cnt].x = SI.HV[i].x;
						SI.HV[cnt].y = SI.HV[i].y;
						SI.ID[cnt].x = SI.ID[i].x;
						SI.ID[cnt].y = SI.ID[i].y;
						cnt++;
					}
				}
			}
			SI.Num = cnt;
			//
			if (!exist) {
				//
				SI.HV[SI.Num].x = xid; SI.ID[SI.Num].x = xid + 1;
				SI.HV[SI.Num].y = yid; SI.ID[SI.Num].y = PM.MVnum - yid;
				SI.Num++;
				// 注意）
				SI.Nums[MESH[yid][xid].flag%ID_MESH_LOC]++;
				if (MESH[yid][xid].flag >= ID_MESH_LOC)  SI.Nums[ID_MESH_LOC]++;
			}
			//
			Disp_Controls();
			Make_Select_Pos();
			///
			// ステータス欄にデータを表示
			val = DUNDEF;
			if ((CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE) || CDATA >= LAND_COVER) {
				CopyDataFromMesh(CDATA, yid, xid, val, MESH, PM);
				if (CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE) rip = File_Order[CDATA];
				else                                       rip = 0;

			}
			/// TAB3　の時はメッシュ情報を知らせる　流下方向編集の布石
			// 
			if (!exist) {
				if (!(val == NODATA || val == DUNDEF)) {
					valform.Format("Select cell %%s [%%d,%%d] Current data = %%.%dlf   ", rip);
					str1.Format(valform, MESH[yid][xid].name, xid + 1, PM.MVnum - yid, val);
					//
					if (CTAB == TAB_3) {
						if (strlen(MESH[yid][xid].name) != 0)
							s_Kind.Format("%s:%s", MESH[yid][xid].name, MESH_FEATURE[MESH[yid][xid].flag%ID_MESH_LOC]);
						else s_Kind.Format("%s", MESH_FEATURE[MESH[yid][xid].flag%ID_MESH_LOC]);
						//
						Show_Mesh_Info(xid, yid);
						Disp_Direction_Radio(xid,yid);
					}
				}
				else {
					str1.Format("Select cell %s [%d,%d]", MESH[yid][xid].name, xid + 1, PM.MVnum - yid);
					if (CTAB == TAB_3) {
						if (strlen(MESH[yid][xid].name) != 0)
							s_Kind.Format("%s:%s", MESH[yid][xid].name, MESH_FEATURE[MESH[yid][xid].flag]);
						else s_Kind.Format("%s", MESH_FEATURE[MESH[yid][xid].flag]);
						//
						Show_Mesh_Info(xid, yid);
						Disp_Direction_Radio(xid, yid);
					}
				}
			}
			else  str1.Format("Release cell %s [%d,%d]", MESH[yid][xid].name, xid + 1, PM.MVnum - yid);
			//
			if (MESH[yid][xid].flag > ID_MESH_LOC) {
				str2 = MESH_FEATURE[MESH[yid][xid].flag%ID_MESH_LOC] + "　Out Location";
			}
			else str2 = MESH_FEATURE[MESH[yid][xid].flag];
			str = str1 + str2;
			COMMENT(str);
		}
	}
	//
	CFormView::OnLButtonUp(nFlags, point);
}
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   ＲＢｕｔｔｏｎ　Ｄｏｗｎ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	Gp.win.cw->GetWindowRect(&rect);
	if (!rect.PtInRect(point)) { CFormView::OnRButtonDown(nFlags, point); return; }// 領域を外れた場合
	//
	STAT(MS_RB_DOWN) = TRUE;
	LastPoint = point;
	///---------------------------------------------------------------------
	// スクリーンツールの移動
	///---------------------------------------------------------------------
	if (PM.B_ScreenTool){
		double		cx, cy;
		XYCOORD		Area[4];
		//
		cx = (double)(point.x - Gp.win.Wrect.left);
		cy = (double)(Gp.win.Wrect.bottom - point.y);
		for (int i = 0; i < 4; i++) {
			Area[i].x = (double)(Tool_Frame[i].x + NOWX);
			Area[i].y = (double)(Tool_Frame[i].y + NOWY);
		}
		if (Is_InRegion(cx, cy, 4,Area)>0) STAT(MOVE_SCREEN_TOOL) = TRUE;
	}
	//
	///---------------------------------------------------------------------
	// 凡例の移動
	///---------------------------------------------------------------------
	//
	int		px, py;
	px = point.x - Gp.win.Wrect.left;
	py = Gp.win.cHeight - (point.y - Gp.win.Wrect.top);
	if (PM.B_Disp_Legend ) {
		if (px >= PM.Area_Legend.left && px <= PM.Area_Legend.right) {
			if (py >= PM.Area_Legend.bottom && py <= PM.Area_Legend.top) {
				STAT(MOVE_LEGEND) = TRUE;
			}
		}
	}
	///---------------------------------------------------------------------
	// Menu
/*	"Boundary Slope WL ",	// Add Dev
		"Boundary River WL ",	// Add Dev
		"Boundary Slope Q",	// Add
		"Boundary River Q",	// Add

		"Dam Count List",

		"Divided Discharge",*/
		///---------------------------------------------------------------------
	if (!(STAT(MOVE_SCREEN_TOOL) || STAT(MOVE_LEGEND)) ) {
		CMenu menu;
		menu.CreatePopupMenu();
		int   cnt = 0;
		//
		if (SI.Num != 0) {
			if (!STAT(EDIT_RIV_MODE)) {
				if (SI.Num == (SI.Nums[ID_MESH])){
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_HS, "set Slope hs"); cnt++;
				}
				if (SI.Num == (SI.Nums[ID_MESH_R])) {
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_HR, "set River hr"); cnt++;
				}
				if (cnt != 0) {
					menu.AppendMenu(MF_SEPARATOR); cnt = 0;
				}
				//
				if (SI.Num == (SI.Nums[ID_MESH])){
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_QS, "set Slope qs"); cnt++;
				}
				if (SI.Num == (SI.Nums[ID_MESH_R])) {
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_QR, "set River qr"); cnt++;
				}
				if (cnt != 0) {
					menu.AppendMenu(MF_SEPARATOR); cnt = 0;
				}
				//
				if (SI.Num == SI.Nums[ID_MESH_R]) {
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_DAM, "set Dam ");
					menu.AppendMenu(MF_SEPARATOR);
				}
				//
				if (SI.Num == 2){
					if (abs(SI.HV[0].x - SI.HV[1].x) <= 1 && abs(SI.HV[0].y - SI.HV[1].y) <= 1) {
						menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_DIV, "set Diversion");
						menu.AppendMenu(MF_SEPARATOR); cnt = 0;
					}
				}
				//
				if (SI.Num == 2 &&
					(SI.Nums[ID_MESH_R] + SI.Nums[ID_MESH_HR] + SI.Nums[ID_MESH_QR] + SI.Nums[ID_MESH_DAM]) == 2) {
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_SET_RIV_PARAMETER, "set River Parameters");
					menu.AppendMenu(MF_SEPARATOR);
				}
				// -------------------------------------enter FLOWMODE 
				if (SI.Num == SI.Nums[ID_MESH_R]) {
					if(STAT(PROC_CONFIRM_MESH)) {
						menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_DELETE_RIV, "* Delete River Cell *");
						menu.AppendMenu(MF_SEPARATOR);
					}
					else if (STAT(DEFINE_BASIN)) {
						menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_DEFINE_BASIN, "* Define Basin *");
						menu.AppendMenu(MF_SEPARATOR);
					}
				}
				//
				menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_BOUNDARY_POS, "add Location");
#if APP_VERSION == FULL_VER
				if (CDATA == SED_FILE && IsSedEnabled()) {
					menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_EXTARCT_SED, "Extract Sed");
				}
#endif
			}
			else  {
				menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_SET_RIV, "Add River Cell");
				menu.AppendMenu(MF_SEPARATOR);
				menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_DELETE_RIV, "Delete River Cell");
			}
		}
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING | MF_ENABLED, IDS_CHANGE_BACKCOLOR, "change Back_color");
		ClientToScreen(&point);
		menu.TrackPopupMenu(
			TPM_LEFTALIGN |	//クリック時のX座標をメニューの左辺にする
			TPM_RIGHTBUTTON,	//右クリックでメニュー選択可能とする
			point.x, point.y,	//メニューの表示位置
			this            	//このメニューを所有するウィンドウ
			);
		menu.DestroyMenu();
	}
	//
	CFormView::OnRButtonDown(nFlags, point);
}

//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＲＢｕｔｔｏｎ　Ｕｐ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	Gp.win.cw->GetWindowRect(&rect);
	if (!rect.PtInRect(point)) { CFormView::OnRButtonUp(nFlags, point); return; }// 領域を外れた場合

	STAT(MS_RB_DOWN) = STAT(MOVE_LEGEND) = FALSE;
	::ReleaseCapture();
	//
	if (PM.B_ScreenTool) STAT(MOVE_SCREEN_TOOL) = FALSE;
	//
	CFormView::OnRButtonUp(nFlags, point);
}
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＲＵＢＢＥＲ　ＢＡＮＤ
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::Draw_Band_Area(double cx, double cy)
{
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_MOUSE_BAND];
	GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
	GLobj_Init(&Gp.Gobj[OBJID_MOUSE_BAND], 5, 2);
	//
	if (cx == DUNDEF) {
		cx = PM.Band_Center.x;
		cy = PM.Band_Center.y;
	}
	//
	double  xst, xend, yst, yend;
	int		No[4];
	xst = cx - PM.SizeID;
	xend = cx + (PM.SizeID + 1);
	yst = cy - PM.SizeID;
	yend = cy + (PM.SizeID + 1);
	//
	No[0] = GLobj_Add_Vert(obj, xst, yst,BAND_HEIGHT,  FALSE);
	No[1] = GLobj_Add_Vert(obj, xend, yst,BAND_HEIGHT, FALSE);
	No[2] = GLobj_Add_Vert(obj, xend, yend,BAND_HEIGHT, FALSE);
	No[3] = GLobj_Add_Vert(obj, xst, yend,BAND_HEIGHT,  FALSE);
	//
	GLobj_Add_Poly(obj, 4, No, GL_LINE_LOOP, 1.5f, F_COLOR(255, 0, 0));
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MOUSE_BAND, TRUE);
	//
	PM.Band_Area[0].x = xst;
	PM.Band_Area[0].y = yst;
	PM.Band_Area[1].x = xend;
	PM.Band_Area[1].y = yend;
	PM.Band_Center.x = cx;
	PM.Band_Center.y = cy;
}
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＰＩＣＴ画面上でのダブルクリック
//_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRect rect;
	Gp.win.cw->GetWindowRect(&rect);
	if (!rect.PtInRect(point)) { CFormView::OnLButtonDblClk(nFlags, point); return; }// 領域を外れた場合
	//
	int		ret;
	if (STAT(SET_WORLD_VIEW) && PM.B_ScreenTool) {
		if ((ret = Decide_Tool(point)) > 0) { EX_Tool(ret); return; }
	}
	//
	double		mx, my;
	int			xid, yid,FFormat;
	//
	if (CDATA < FILE_IN_NUM) FFormat = File_Format[CDATA];
	else                   FFormat = 0;
	//
	IF_STAT(PROC_CONFIRM_MESH) {
		if (!STAT(EDIT_RIV_MODE) && !(nFlags&MK_SHIFT)) {
			if (FFormat < 2 && CDATA != ADIR_FILE) {
				if (GL_Trans_Pos(&Gp, point, &mx, &my)) {
					xid = (int)mx;
					yid = (int)my;
					if ((xid >= 0 && xid < PM.MHnum) && (yid >= 0 && yid < PM.MVnum)) {
						///
						// 編集ダイアログ発生のための処理
						IFNOT_STAT(DISP_EDITWIN) {
//							if (DSET.in_avail[CDATA]) {
								if (xid - PM.SizeID < 0)					xid = PM.SizeID;
								if (xid + PM.SizeID >= PM.MHnum)	xid = PM.MHnum - PM.SizeID - 1;
								if (yid - PM.SizeID < 0)					yid = PM.SizeID;
								if (yid + PM.SizeID >= PM.MVnum)	yid = PM.MVnum - PM.SizeID - 1;
								//
								Draw_Band_Area((double)xid, (double)yid);
								//
								Display_EditWindow(xid, yid);
//							}
						}
					}
				}
			}
			else if (FFormat == 2) {		// 境界条件のみ
				GLobj_Delete(&Gp, OBJID_MESH);
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
				//
				CTSEditDlg	CTD;
				CTD.Data_ID = CDATA;
				CTD.BT = DSET.BT;
				ret = CTD.DoModal(); //201905
				//
				ret = IDOK;
				if (ret == IDOK) {
					DSET.in_avail[CDATA] = DSET.in_use[CDATA] = TRUE;
					Write_Data_File(CDATA, File_Format[CDATA], File_Order[CDATA], DSET, PM, MESH);
					Write_RRI_INPUT(DSET);
					B_Change_RRI = 0;
					//
					Clear_Select();
					PM.Data_Alpha = 1.;
					Make_Mesh_Line();
					GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
				}
			}
		}
	}
	//
	CFormView::OnLButtonDblClk(nFlags, point);
}

void CRRI_GUIView::Clear_Mode()  // マウス移動、ズームが効かないため設ける。
{
	STAT(KEY_CTRL_DOWN) = STAT(KEY_SHIFT_DOWN) = STAT(KEY_ALT_DOWN) = FALSE;
	STAT(MS_LB_DOWN) = STAT(MS_RB_DOWN) = STAT(MS_MOVE_START) = FALSE;
	//
	IF_STAT(MS_RUBBER_START) {
		GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
		STAT(MS_RUBBER_START) = FALSE;
	}
	IF_STAT(AREA_DECIDE_MODE) {
		STAT(AREA_DECIDE_MODE) = STAT(ADD_MESH_MODE) = STAT(DEL_MESH_MODE) = FALSE;
		GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
		SAFE_FREE(Free_Area); Famem = Fanum = 0; Change_Cursor(&Gp, IDC_ARROW);
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MOUSE_BAND, TRUE);
	//
	CWnd*	cw = GetDlgItem(ID_PICT);
	cw->SetFocus();
}
void CRRI_GUIView::Clear_Select()
{
	if (SI.Num == 0) return;
	//
	SI.Num = 0;
	for (int i = 0; i < 10; i++) SI.Nums[i] = 0;
	for (int i = 0; i < SI.Mem; i++) {		
		SI.ID[i].x = SI.ID[i].y = 0;
		SI.HV[i].x = SI.HV[i].y = 0;
	}
	//
	Disp_Controls();
	GLobj_Delete(&Gp, OBJID_SELECT);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SELECT, TRUE);
}
// //////////////////////////////////////////////////////////////////////////////////////////////////////

///==================  Ｏｎ　Ｔｉｍｅｒ =================================================================

// //////////////////////////////////////////////////////////////////////////////////////////////////////

void CRRI_GUIView::OnTimer(UINT_PTR nIDEvent)
{
///_____________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///  INIT TIMER 
//_____________________________________________________
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if( nIDEvent == INIT_TIMER ) {
		KillTimer( INIT_TIMER );
		//
		COMMENT("Now initializing...");
//_____________________________________________________
///  表示領域の確保
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		CRect		m_ARect;
		CWnd*		cw=(this);
		int			Xspan,Yspan;
		//
		cw->GetWindowRect( &Gp.win.WinRect );
		cw->GetClientRect( &m_ARect );
		Gp.win.WinCRect = m_ARect;
		//
		Gp.win.wWidth = m_ARect.Width();
		Gp.win.wHeight= m_ARect.Height();
		//
		m_ARect.left	+= (MENU_WIDTH+FRAME_MARGIN);
		m_ARect.right	-= FRAME_MARGIN;
		m_ARect.top		+= FRAME_MARGIN;
		m_ARect.bottom	-= FRAME_MARGIN;
		Xspan = m_ARect.Width(); Yspan = m_ARect.Height();
		Gp.win.Cpict.Create(NULL,WS_VISIBLE|SS_SUNKEN,m_ARect,cw,ID_PICT);
		//
		// Get Information
		Gp.win.cw		= GetDlgItem( ID_PICT );
		Gp.win.hWnd		= Gp.win.cw->m_hWnd;
		//
		Gp.win.cw->GetClientRect( &Gp.win.Crect );
		Gp.win.cw->GetClientRect( &Gp.win.MAXrect );
		Gp.win.cWidth	= Gp.win.Crect.Width();
		Gp.win.cHeight	= Gp.win.Crect.Height();
		//
		//  マウス信号にあった領域の変更
		Gp.win.cw->GetWindowRect( &Gp.win.Wrect );
		Gp.win.Wrect.left -=( Gp.win.WinRect.left + ( Gp.win.WinRect.Width() - Gp.win.wWidth )/2 -1);
		Gp.win.Wrect.top  -=( Gp.win.WinRect.top + ( Gp.win.WinRect.Height() - Gp.win.wHeight )/2 -1);
		Gp.win.Wrect.right = Gp.win.Wrect.left + Gp.win.Crect.Width();
		Gp.win.Wrect.bottom = Gp.win.Wrect.top + Gp.win.Crect.Height();
		//
		//----------------------------------------------------
		::ValidateRect(Gp.win.hWnd,&Gp.win.Crect );			// WM_PAINT の無効化
//_____________________________________________________
//  ＯＰＥＮＧＬ　初期化
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		Gp.Gmax		= MAX_OBJECT;
		if( FAILED( GL_Init( &Gp ) ) ) {RETURN("****  ERROR **** ＯＰＥＮ ＧＬの初期化に失敗しました");}
		for(int i=0;i<Gp.Gmax;i++) Gp.Gobj[i].set = FALSE;

		//  Font   -------------------------------------
		GL_Init_Font(&Gp);

		// Attribute          --------------------------
		FCOLOR	bcol=F_COLOR( 0, 0, 0 );
		if (FAILED(GL_Attrib(&Gp, DIM_3D, ORTHO, VIEW_XY,bcol, 0))) return;

		GL_Clear(&Gp);

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// プロジェクトの初期化　もしくはリロード の選択 
///_____________________________________________________________________________________________________
		CInitProj	CP;
		CREAT = 0;
		if (CP.DoModal() == IDCANCEL) {
			DestroyWindow(); exit(1);
		}
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//  ツール/ 凡例の初期化
		NOWX = TOOL_DEFAULT_X; NOWY = TOOL_DEFAULT_Y;
		Make_Screen_Tool(TRUE);				// ツールの作成とテックスの初期化
		///_____________________________________________________
		//  Set Parameter after decided GP.win
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		CDATA = ACC_FILE;
		Make_LEGEND();

		///==========================================================================
		//  プロジェクトの新規作成　
		///==========================================================================

		if (CREAT == 1) {	
			///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//  フォルダの作成
			///___________________________________________________________________
			if (FAILED(Define_Folder())) {
				DestroyWindow(); exit(1);
			}
			for (int i = 0; i < 7; i++)
				sprintf(DSET.Folder_Name[i], "%s\\%s", DSET.Proj_Folder, File_Folder_Name[i]);
			///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//  ガイド画面からの作成
			///___________________________________________________________________
			if (PM.B_UseGuide) {
				sprintf(DSET.InputFile, "%s/RRI_Input.txt", DSET.Proj_Folder);
				B_Change_RRI = TRUE;
				//
				Show_Init_Guide();		// テクスチャー登録、OBJID_BACK にガイドを表示
				STAT(ON_SCREEN) = TRUE;
				STAT(PROC_INDICATE_RIVMESH) = TRUE;
				Disp_Controls();
			}
			///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//  外部　DEM ACC DIR データの読み込み DEM_EDITORを通したデータを読み込むため
			/// DEMだけではなく、ACC DIRを読み込むこととし、土研のプログラムを使用しないこととした。2016/2
			//___________________________________________________________________
			else {
				//Read_Dem();	// Read_3_Files　を使用するため、使用停止 
				///　基本的な設定　　EX_** をDSET.File_namesにセット
				CString		Target;
				char			Title[SIZE_01K];
				// 
				sprintf(DSET.InputFile, "%s/RRI_Input.txt", DSET.Proj_Folder);
				// DEM
				Get_Title(DSET.EX_Dem_File, Title);
				sprintf(DSET.File_names[ADEM_FILE], "%s/topo/%s", DSET.Proj_Folder,Title);
				CopyFile( DSET.EX_Dem_File,DSET.File_names[ADEM_FILE],TRUE);
				// ACC
				Get_Title(DSET.EX_Acc_File, Title);
				sprintf(DSET.File_names[ACC_FILE], "%s/topo/%s", DSET.Proj_Folder, Title);
				CopyFile( DSET.EX_Acc_File, DSET.File_names[ACC_FILE],TRUE);
				// DIR
				Get_Title(DSET.EX_Dir_File, Title);
				sprintf(DSET.File_names[ADIR_FILE], "%s/topo/%s", DSET.Proj_Folder, Title);
				CopyFile(DSET.EX_Dir_File, DSET.File_names[ADIR_FILE], TRUE);

				flushall();
				//--------------------------
				Read_3_Files(TRUE);
				//--------------------------

				CDATA = ACC_FILE;
				STAT(USE_EXTERNAL_DEM) = TRUE;
				STAT(PROC_CONFIRM_MESH) = TRUE;
				STAT(READ_ADEM_ONLY) = FALSE;  // FALSE 変更　2016/2

				DSET.in_use[ADEM_FILE] = DSET.in_avail[ADEM_FILE] = TRUE;
				DSET.in_use[ACC_FILE] = DSET.in_avail[ACC_FILE] = TRUE;
				DSET.in_use[ADIR_FILE] = DSET.in_avail[ADIR_FILE] = TRUE;
				//
				if (PM.B_LatLng) {
					PM.endLAT = PM.stLAT + PM.MVnum*PM.Size;
					PM.endLNG = PM.stLNG + PM.MHnum*PM.Size;
					Set_RectArea();
				}
				else {	// UTM
					PM.endUTM_Y = PM.stUTM_Y + PM.MVnum*PM.UTMsize;
					PM.endUTM_X = PM.stUTM_X + PM.MHnum*PM.UTMsize;
					Set_UTMArea();
				}
				//
				Calc_Unit_Area();
				Disp_Controls();
				//
				if (PM.B_LatLng) {
					Make_Back_Image();
					Make_Mesh_Model();
					Make_Mesh_Line();
					Make_Mesh_Area();
					Make_LEGEND();		// 作り直し
					GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
				}
				else {
					Make_Mesh_Model();
					Make_Mesh_Area();
					Make_LEGEND();		// 作り直し
					GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
				}
				//
				PM.set = PM.Model = TRUE;
				PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);	/// 2016/3 追加
			}
			// 降雨データメッシュサイズの仮設定
			DSET.Rain_dx = DSET.Rain_dy = 1. / PM.Deg_Unit;
		}
		///==========================================================================
		//  既存プロジェクトの読み込み　	 CREAT = 2	
		///==========================================================================
		else {
			CString	file_RRI;					//***  ファイル読込
			if (!Button_File(TRUE, &file_RRI, m_RecentPath,"RRI_Input","txt")) {
				DestroyWindow(); exit(1);
			}
			strcpy(DSET.InputFile, file_RRI);
			Get_Dir(DSET.InputFile, DSET.Proj_Folder);
			//
			for (int i = 0; i < 7; i++)
				sprintf(DSET.Folder_Name[i], "%s\\%s", DSET.Proj_Folder, File_Folder_Name[i]);
			//
			int ret;
			//
			Change_Cursor(&Gp, IDC_WAIT);			//***  リロード
			if ((ret=Reload_Project()) ){			// 通常 RETURN=０
				Change_Cursor(&Gp, IDC_ARROW);
				DestroyWindow(); exit(1);
			}
			//
			CEX_LABEL = CEX = PM.EXnum;
			Disp_Controls();
			//
			GLobj_Delete(&Gp, OBJID_BACK);
			GLobj_Delete(&Gp, OBJID_AREA);
			GLobj_Delete(&Gp, OBJID_MESH);
			GLobj_Delete(&Gp, OBJID_WORK);

			///  メッシュの表示
			CDATA = ACC_FILE;
			STAT(PROC_CONFIRM_MESH) = TRUE;
			//
			if (PM.B_LatLng) {
				PM.endLNG = PM.stLNG + PM.MHnum *1. / PM.Coord_Unit;
				PM.endLAT = PM.stLAT + PM.MVnum *1. / PM.Coord_Unit;
			}
			else {
				PM.endUTM_X = PM.stUTM_X + PM.MHnum*PM.UTMsize;
				PM.endUTM_Y = PM.stUTM_Y + PM.MVnum*PM.UTMsize;
			}
			//
			Calc_Unit_Area();
			if (PM.B_LatLng)	Set_RectArea();
			else				Set_UTMArea();
			//
			if(PM.B_LatLng ) Make_Back_Image();
			//
			Make_Mesh_Line();
			Make_Mesh_Model();
			RefreshSedRectLine();
			Make_Mesh_Area();
			Make_LEGEND();		/// 作り直し
			//
			PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
			//
			GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
			PM.set = PM.Model = TRUE;

			// 2019.07.08 JFlow時のMESH.AtLng,ATLat 情報復元
			if (PM.B_UseJFlow) {
				double lat, lng;
				int h, v;

				lat = PM.endLAT;
				lng = PM.stLNG;

				h = 0;
				v = 0;

				while (lng < PM.endLNG)
				{
					if (h + 1 > PM.MHnum)
					{
						break;
					}
					while (lat > PM.stLAT)
					{
						if (v + 1 > PM.MVnum)
						{
							break;
						}

						MESH[PM.MVnum - v - 1][h].AtLng = lng;
						MESH[PM.MVnum - v - 1][h].AtLat = lat;

						lat -= PM.Size;
						v++;

					}

					lat = PM.endLAT;
					lng += PM.Size;
					h++;
					v = 0;
				}
			}

			// MANNING_JAファイル読み込み
			//
			//--------------------------------------------------
			/*
			必要なファイル　　Manning係数  Manning.csv   ->  Darcy = 1 GreenAmpt = 0 by Kswitch to appno
			Darcy　適用の場合(山地）		ka = 0.
			GreenAmpt 適用の場合(平地）	ksv =0.
			*/
			::SetCurrentDirectory(m_BootPath);
			/*
			マニング係数　　 Manning.csvの読み込み　２０種類コード
			*/
			//--------------------------------------------------
			char	buf[SIZE_16K], inchar[SIZE_01K];
			int		pos;
			double	Manning[20] = { 0 };	// マニング係数
			int		Kswitch[20] = { 0 };	// Darcy(1) or GAmpt(0)
			int		MNnum = 20;
			FILE* fp;

			if (PM.B_UseJFlow) {
				MNnum = 5;

				if ((fp = fopen(MANNING_FILE_JA, "r")) == NULL) {
					MessageBox("** Error ** Manning file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
					RETURN("** Error ** Manning file not exist");
				}

				fgets(buf, SIZE_16K, fp);  // Terms
				for (int m = 0; m < MNnum; m++) {
					fgets(buf, SIZE_16K, fp); pos = 0;
					getstr(buf, &pos, inchar, SIZE_01K); // NO;
					getstr(buf, &pos, inchar, SIZE_01K); Manning[m] = atof(inchar);
					getstr(buf, &pos, inchar, SIZE_01K); Kswitch[m] = atoi(inchar);
					strcpy(Cover_Name[m], &buf[pos]);
				}
				fclose(fp);
			}
			//
			CWnd*	cw = GetDlgItem(ID_PICT);
			cw->SetFocus();

		}
		//
		STAT(ON_SCREEN) = TRUE;
		//
		CString		str;
		str.Format("Ready.....OpenGL [ GPU::: %s ( %s ), ver %s ::: Max Res  %d ]",
								Gp.renderer,Gp.vendor,Gp.version,Gp.Max_Res);
		COMMENT(str);
		//
		Disp_Controls();
		//
		SetTimer( RENDER_TIMER,100,NULL);
	}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   RENDER TIMER

	else if( nIDEvent == RENDER_TIMER ) {
		IF_STAT(REDRAW) {
			IFNOT_STAT(AREA_DECIDE_MODE) Change_Cursor(&Gp, IDC_WAIT);
			Render_Scene();
			IFNOT_STAT(AREA_DECIDE_MODE ) Change_Cursor(&Gp, IDC_ARROW);
			//
			if (B_FirstStep && Gp.Gobj[OBJID_LINE].set) {
				if (PM.B_MeshLine) {
					int Pixel = (int)(Gp.win.cWidth / Gp.cam[CVIEW].Dw);
					if (Pixel > PM.Mesh_Thresh) Gp.Gobj[OBJID_LINE].display = TRUE;
					else                      Gp.Gobj[OBJID_LINE].display = FALSE;
				}
				GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_LINE, TRUE);
				//
				B_FirstStep = FALSE;
			}
		}
		if ((Gp.cam[CVIEW].endH - Gp.cam[CVIEW].stH) <= ARROW_LIMIT) {
			STAT(ENABLE_DRAW_ARROW) = TRUE;
			s_ArrowInfo = "Arrow visible"; UDF;
		}
		else {
			STAT(ENABLE_DRAW_ARROW) = FALSE;
			s_ArrowInfo = "Arrow invisible"; UDF;
		}
			//
		/// LINE の再判断
		//if (Gp.Gobj[OBJID_LINE].set ) {
		//	int Pixel = (int)(Gp.win.cWidth / Gp.cam[CVIEW].Dw);
		//	if (Pixel > PM.Mesh_Thresh && Gp.Gobj[OBJID_LINE].display == FALSE) {
		//		if (PM.B_DispLine) {
		//			Gp.Gobj[OBJID_LINE].display = TRUE;
		//			GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_LINE, TRUE);
		//		}
		//	}
		//}
	}
	CFormView::OnTimer(nIDEvent);
}
//
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// コントロールの表示 ---------------------------------------------------------

void CRRI_GUIView::Disp_Controls()
{
	CWnd*		cw;
	CButton*		cc;
	BOOL			DISPLAY;
	int				LL_mode, UTM_mode;
	CString		str;
	//
///______________
//  TAB_1
///~~~~~~~~~~~~~~~
	if (CTAB == TAB_1) {
		if (strlen(DSET.Proj_Title) != 0) {
			s_ProjName = DSET.Proj_Title; UDF;
		}
		LL_mode = UTM_mode = SW_HIDE;
		if (CEX_LABEL != UNDEF) {
			///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//    表示内容を変える
			if (PM.B_LatLng) {
				s_MeshSubdev.Format("%d\" ( = 1/%d degree)", (int)(3600 / (int)PM.Deg_Unit),(int)PM.Deg_Unit);
				LL_mode = SW_SHOW;
			}
			else		{
				s_MeshSubdev.Format("%.2lf m", PM.Deg_Unit);
				UTM_mode = SW_SHOW;
			}
			UDF;
		}
		for (int i = 0; i < Disp_LatLng_NUM-1; i++) {
			cw = GetDlgItem(Disp_LatLng_ID[i]);
			cw->ShowWindow(LL_mode);
		}
		for (int i = 0; i < Disp_UTM_NUM-1; i++) {  // Static 114 (EXTENT ）を除く
			cw = GetDlgItem(Disp_UTM_ID[i]);
			cw->ShowWindow(UTM_mode);
		}
		//
		b_Breset.EnableWindow(FALSE);
		// 新規作成　リロードモード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		///___________________________________________
		//  PROC_INDICATE_RIVMESH  河道下流端の指示
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		IF_STAT(PROC_INDICATE_RIVMESH) {
			B_cDelete.EnableWindow(FALSE);
			m_cConfirm.SetWindowTextA("Confirm");
			if (RIVnum == 0) {
				m_cConfirm.EnableWindow(FALSE);
				s_MeshH = s_MeshV = _T("");
				UDF;
			}
			else     {
				m_cConfirm.EnableWindow(TRUE);
			}
			B_cDelete.EnableWindow(FALSE);
			//
			for (int i = 0; i < AVAIL_NUM[0]; i++){
				cw = GetDlgItem(TAB_1_AVAIL[i]);
				cw->EnableWindow(FALSE);
			}
			c_Badd.EnableWindow(FALSE);
			c_Bdel.EnableWindow(FALSE);
			c_LandCoverSoil.EnableWindow(FALSE);
			c_LandCoverSoilJp.EnableWindow(FALSE);
			c_LandCoverSoilJp2.EnableWindow(FALSE);
		}
		///___________________________________________
		//  PROC_DISPLAY_MESH  流域表示 メッシュ確定を待つ
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		IF_STAT(PROC_DISPLAY_MESH) {
			c_Badd.EnableWindow(TRUE);
			c_Bdel.EnableWindow(TRUE);
			//
			B_cDelete.EnableWindow(TRUE);
			m_cConfirm.SetWindowTextA("Extract Basin");
			//
			int num;
			num = (int)(AreaXmax - AreaXmin); s_MeshH.Format("%d", num);
			num = (int)(AreaYmax - AreaYmin); s_MeshV.Format("%d", num); UDF;
			//
			for (int i = 0; i < AVAIL_NUM[0]; i++){
				cw = GetDlgItem(TAB_1_AVAIL[i]);
				cw->EnableWindow(FALSE);
			}
			//
			if (Cnt_CArea != 0) b_Breset.EnableWindow(TRUE); // Reset Area Button
			else              b_Breset.EnableWindow(FALSE);
		}

		///___________________________________________
		//  PROC_CONFIRM_MESH  流域モデルが確定、編集可能、モデル作成機能を消す
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		IF_STAT(PROC_CONFIRM_MESH) {
			c_Badd.EnableWindow(FALSE);
			c_Bdel.EnableWindow(FALSE);
			B_cDelete.EnableWindow(FALSE);
			b_Breset.EnableWindow(FALSE);
			//
			if (DSET.b_CSexist) {
				c_LandCoverSoil.EnableWindow(FALSE);
				//c_LandCoverSoilJp.EnableWindow(FALSE);
				//c_LandCoverSoilJp2.EnableWindow(FALSE);
			}
			else {
				if (!PM.B_UseJFlow) {
					c_LandCoverSoil.EnableWindow(TRUE);
				}
				else {
					c_LandCoverSoilJp.EnableWindow(TRUE);
					c_LandCoverSoilJp2.EnableWindow(TRUE);
				}
			}
			//
			m_cConfirm.SetWindowTextA("Confirmed");
			m_cConfirm.EnableWindow(FALSE);
			for (int i = 0; i < AREA_ID_NUM; i++) {
				cw = GetDlgItem(AREA_ID[i]);
				cw->EnableWindow(FALSE);
			}
			//
			s_MeshH.Format("%d", PM.MHnum);
			s_MeshV.Format("%d", PM.MVnum); UDF;
			//
			for (int i = 0; i < AVAIL_NUM[0]-1; i++){  // 注意　 AVAIL_NUM[0]-1　はＵＮＤＯ
				cw = GetDlgItem(TAB_1_AVAIL[i]);
				cw->EnableWindow(TRUE);
			}
			if (B_UndoFirstSave) c_Undo.EnableWindow(TRUE);
			else               c_Undo.EnableWindow(FALSE);
			//
			if (DSET.b_CSexist) {
				c_LandCoverSoil.EnableWindow(FALSE);
				//c_LandCoverSoilJp.EnableWindow(FALSE);
				//c_LandCoverSoilJp2.EnableWindow(FALSE);
			}
			else {
				if (!PM.B_UseJFlow) {
					c_LandCoverSoil.EnableWindow(TRUE);
					c_LandCoverSoilJp.EnableWindow(FALSE);
					c_LandCoverSoilJp2.EnableWindow(FALSE);
				}
				else {
					c_LandCoverSoil.EnableWindow(FALSE);
					c_LandCoverSoilJp.EnableWindow(TRUE);
					c_LandCoverSoilJp2.EnableWindow(TRUE);
				}
			}
		}
	}
	else if (CTAB == TAB_2){
		//
		Set_Period();
		if (STAT(PROC_CONFIRM_MESH)) DISPLAY = TRUE;
		else {
			if (!STAT(READ_ADEM_ONLY)) DISPLAY = TRUE;
			else                       DISPLAY = FALSE;
		}
		//

		for (int i = 0; i < AVAIL_NUM[1]; i++){
			cw = GetDlgItem(TAB_2_AVAIL[i]);
			if (DISPLAY)  cw->EnableWindow(TRUE);
			else         cw->EnableWindow(FALSE);
		}
		//
		if (DSET.in_avail[RAIN_FILE])	c_Racc.EnableWindow(TRUE);
		else							c_Racc.EnableWindow(FALSE);
		if (DSET.in_avail[POTENT_FILE])	c_BEacc.EnableWindow(TRUE);
		else							c_BEacc.EnableWindow(FALSE);

		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Boundary Conditions
		cw = GetDlgItem(BOUND_ID[0]);		// HS
		if (SI.Num != 0) 
			if (SI.Num == SI.Nums[ID_MESH] )	 	cw->EnableWindow(TRUE);
			else									cw->EnableWindow(FALSE);
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[1]);		// HR
		if (SI.Num != 0)
			if (SI.Num == SI.Nums[ID_MESH_R]  )  	cw->EnableWindow(TRUE);
			else									cw->EnableWindow(FALSE);
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[2]);		// QS
		if (SI.Num != 0)
			if (SI.Num == SI.Nums[ID_MESH] )		cw->EnableWindow(TRUE);
			else									cw->EnableWindow(FALSE);
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[3]);		// QR
		if (SI.Num != 0)
			if (SI.Num == SI.Nums[ID_MESH_R])	    cw->EnableWindow(TRUE);
			else									cw->EnableWindow(FALSE);
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[4]);		// DAM
		if (SI.Num != 0)
			if (SI.Num == SI.Nums[ID_MESH_R])	cw->EnableWindow(TRUE);
			else								cw->EnableWindow(FALSE);			
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[5]);		// DIV
		if (SI.Num != 0) {
			if (SI.Num == SI.Nums[ID_MESH_R]) {
				if (abs(SI.HV[0].x - SI.HV[1].x) <= 1 && abs(SI.HV[0].y - SI.HV[1].y) <= 1) 	cw->EnableWindow(TRUE);
				else								cw->EnableWindow(FALSE);
			}
		}
		else								cw->EnableWindow(FALSE);
		//
		cw = GetDlgItem(BOUND_ID[6]);		// LOCATION
		if (SI.Num != 0) 	cw->EnableWindow(TRUE);
		else				cw->EnableWindow(FALSE);
		//
		for (int i = 0; i < 10; i++) CellKind[i] = 0;
		for (int v = 0; v < PM.MVnum; v++) {
			// Location　は ID_MESH_LOC とID_MESH_*の足し算となる。
			for (int h = 0; h < PM.MHnum; h++) {
				if (MESH[v][h].flag >= ID_MESH_LOC) {
					CellKind[9]++;
					CellKind[MESH[v][h].flag%ID_MESH_LOC]++;
				}
				else 
					CellKind[MESH[v][h].flag]++;
			}
		}
		//
		s_Select.Format("S [ %d - %d ]  R [ %d - %d ]  dam %d,  div %d ",CellKind[ID_MESH_HS],CellKind[ID_MESH_QS],  CellKind[ID_MESH_HR],
			CellKind[ID_MESH_QR], CellKind[ID_MESH_DAM], CellKind[ID_MESH_DIV]);
		//
		s_OutLocation.Format("[ %d ]", DSET.Lnum);
		//
		if (!PM.B_LatLng) {	// UTM の場合、衛星雨量は無効
			for (int i = 0; i < 3; i++) {
				cw = GetDlgItem(UTM_INAVAIL[i]);
				cw->EnableWindow(FALSE);
			}
		}
		//
		IF_STAT(EDIT_RIV_MODE) {
			for (int i = 17; i < TAB_2_NUM; i++){  
				cw = GetDlgItem(TAB_2_ID[i]);
				cw->EnableWindow(FALSE);
			}
		}
		UDF;
	}
	else if (CTAB == TAB_3){
		///  ----------------------------------------------- Combo Data
		PM.DataNum = 0;
		int			current = UNDEF;
		//
		c_ComboData.ResetContent();
		for (int i = 0; i < FILE_IN_USE; i++) {
			if (i == LU_FILE && PM.B_UseJFlow && DSET.in_avail[LU_FILE]) {
				DSET.in_use[LAND_COVER] = DSET.in_avail[LAND_COVER] = DSET.in_exist[LAND_COVER] = TRUE;
				c_ComboData.AddString(MODEL_EDIT_NAME[LAND_COVER]);
				if (CDATA == LAND_COVER) current = PM.DDISP = PM.DataNum;
				PM.Data_Order[PM.DataNum++] = LAND_COVER;
				continue;

			}
			if (DSET.in_avail[i]) {
				
				c_ComboData.AddString(MODEL_EDIT_NAME[i]);
				if (i == CDATA) current = PM.DDISP = PM.DataNum;
				PM.Data_Order[PM.DataNum++] = i;
			}
		}
		///
		// Cover or SOil
		if (DSET.b_CSexist && !PM.B_UseJFlow) {
			c_ComboData.AddString(MODEL_EDIT_NAME[LAND_COVER]);
			if (CDATA == LAND_COVER) current = PM.DDISP = PM.DataNum;
			PM.Data_Order[PM.DataNum++] = LAND_COVER;
			//
			c_ComboData.AddString(MODEL_EDIT_NAME[LAND_SOIL]);
			if (CDATA == LAND_SOIL) current = PM.DDISP = PM.DataNum;
			PM.Data_Order[PM.DataNum++] = LAND_SOIL;
		}
		//
		if (current != UNDEF) c_ComboData.SetCurSel(PM.DDISP);
		//
		if ((CDATA >= HS_WLEV_FILE && CDATA <= DIV_FILE) || CDATA == LOCATION_FILE) {
			c_BoundList.EnableWindow(TRUE);
			c_Bcolor.EnableWindow(FALSE);
		}
		else		{
			c_BoundList.EnableWindow(FALSE);
		}

		///  ----------------------------------------------- Display Check
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_1);
		if (PM.B_Back) cc->SetCheck(1);
		else          cc->SetCheck(0);
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_2);
		if (PM.B_MeshLine) cc->SetCheck(1);
		else          cc->SetCheck(0);
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_3);
		if (PM.B_ColorMesh)	cc->SetCheck(1);
		else					cc->SetCheck(0);
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_4);
		if (PM.B_ScreenTool)	cc->SetCheck(1);
		else					cc->SetCheck(0);
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_5);
		if (DSET.RGnum != 0) {
			cc->EnableWindow(TRUE);
			if (PM.B_Disp_Ground)	cc->SetCheck(1);
			else                cc->SetCheck(0);
		}
		else	 {
			cc->SetCheck(0); cc->EnableWindow(FALSE);
		}
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_6);
		if (PM.B_Disp_Frame)	cc->SetCheck(1);
		else					cc->SetCheck(0);
		//
		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_7);
		if (PM.B_Disp_Legend)	cc->SetCheck(1);
		else					cc->SetCheck(0);
		///  ----------------------------------------------- Direction Radio & reset CDATA = ADIR_FILE
		if (CDATA == ADIR_FILE) {
			cw = GetDlgItem(IDC_BUTTON_RESET);
			if (STAT(AVAIL_RESET)) {
				Static_Format(cw, "Set", 6, 14, DT_CENTER | DT_BOTTOM, RGB(0, 0, 0), RGB(255, 180, 180));
				c_Reset.EnableWindow(TRUE);
				c_Cancel.EnableWindow(TRUE);
			}
			else  {
				Static_Format(cw, "Set", 6, 14, DT_CENTER | DT_BOTTOM, RGB(0, 0, 0), RGB(240, 240, 240));
				c_Cancel.EnableWindow(FALSE);
				c_Reset.EnableWindow(FALSE);
			}   
			if (STAT(AVAIL_UNDO)) c_DirUndo.EnableWindow(TRUE);
			else                c_DirUndo.EnableWindow(FALSE);
			//
			c_DispArrow.SetCheck(1);
			c_DispArrow.EnableWindow(FALSE);
			c_Bcolor.EnableWindow(FALSE);
		}
		else {
			c_DirUndo.EnableWindow(FALSE);
			c_Reset.EnableWindow(FALSE);
			c_Cancel.EnableWindow(FALSE);
			//
			c_DispArrow.EnableWindow(TRUE);
			if (STAT(DISP_ARROW)) 	c_DispArrow.SetCheck(1);
			else					c_DispArrow.SetCheck(0);
		}

		///  ----------------------------------------------- Mesh Line Color
		CRect   crect;
		for (int i = 0; i < 9; i++) {
			cw = GetDlgItem(MESH_COLOR_ID[i]);
			cw->GetClientRect(&crect);
			Fill_Color(cw, PM.COL_MESH[i + 1]); // flag の関連から１から始まる
			cw->ValidateRect(&crect);
		}
		//
		//
		cw = GetDlgItem(IDC_MESHCOLOR_4);
		cw->GetClientRect(&crect);
		Fill_Color(cw, PM.Col_Frame);
		cw->ValidateRect(&crect);
		//
		cw = GetDlgItem(IDC_MESHCOLOR_5);
		cw->GetClientRect(&crect);
		Fill_Color(cw, PM.Col_Observatory);
		cw->ValidateRect(&crect);
		//
		///  ----------------------------------------------- Valid or Invalid
		if (STAT(PROC_CONFIRM_MESH)) DISPLAY = TRUE;
		else {
			if (!STAT(READ_ADEM_ONLY)) DISPLAY = TRUE;
			else                       DISPLAY = FALSE;
		}
		//
		for (int i = 0; i < AVAIL_NUM[2]; i++){		// この中にｃ＿BCOLORが含まれる
			cw = GetDlgItem(TAB_3_AVAIL[i]);
			if (DISPLAY)  cw->EnableWindow(TRUE);
			else          cw->EnableWindow(FALSE);
		}
		if (CDATA != ADIR_FILE) c_Bcolor.EnableWindow(TRUE);
		else                  c_Bcolor.EnableWindow(FALSE);
		//
		IF_STAT(DISP_EDITWIN) { c_ComboData.EnableWindow(FALSE); }
		else                { c_ComboData.EnableWindow(TRUE); }
		//
		IF_STAT(EDIT_RIV_MODE) {
			for (int i = 17; i < TAB_3_NUM; i++){
				cw = GetDlgItem(TAB_3_ID[i]);
				cw->EnableWindow(FALSE);
			}
		}
	}
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　タブの変更
void CRRI_GUIView::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl*	 MTab = (CTabCtrl*)GetDlgItem( IDC_TAB_MAIN );
	//
	COLD = CTAB;
	CTAB = MTab->GetCurSel();
	//if
	if (STAT(PROC_INDICATE_RIVMESH) || STAT(PROC_DISPLAY_MESH)  || STAT(DEFINE_BASIN)) {
		c_TabMain.SetCurSel(0);
		MessageBox("** Error ** Cannot select other tab in this stage.", "Warning", MB_OK | MB_ICONHAND);
		CTAB = COLD; return;
	}
	//
	Change_Tab();
	if (SI.Num != 0) Clear_Select();
	Disp_Direction_Radio(UNDEF, UNDEF);
	//
	Disp_Controls();
	*pResult = 0;
}
void CRRI_GUIView::Change_Tab()
{
	CWnd*	cw;
	//
	if (COLD != CTAB) {
		c_TabMain.HighlightItem(COLD, FALSE);
		c_TabMain.HighlightItem(CTAB, TRUE);
	}
	///_____________________________________________________
	//  Common Controls  すべてのコントロールの表示・非表示
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < TAB_1_NUM; i++) {
		cw = GetDlgItem(TAB_1_ID[i]);
		if (CTAB == 0) 	cw->ShowWindow(SW_SHOW);
		else				cw->ShowWindow(SW_HIDE);
		//cw->RedrawWindow();
	}
	if (CTAB == 0) {
		if (!PM.B_LatLng) {	// 通常表示は上の定義でよい。
			for (int i = 0; i < Disp_LatLng_NUM; i++) {
				cw = GetDlgItem(Disp_LatLng_ID[i]);
				cw->ShowWindow(SW_HIDE);
			}
			for (int i = 0; i < Disp_UTM_NUM; i++) {  //Disp_UTM_NUM-1 Ｃｅｎｔｅｒ　Ｓｔａｔｉｃ
				cw = GetDlgItem(Disp_UTM_ID[i]);
				cw->ShowWindow(SW_SHOW);
			}
		}
	}
	else {
		for (int i = 0; i < Disp_UTM_NUM; i++) {  //Disp_UTM_NUM-1 Ｃｅｎｔｅｒ　Ｓｔａｔｉｃ
			cw = GetDlgItem(Disp_UTM_ID[i]);
			cw->ShowWindow(SW_HIDE);
		}
	}
	//
	for (int i = 0; i<TAB_2_NUM; i++) {
		auto itemID = TAB_2_ID[i];
		cw = GetDlgItem(itemID);
		if (CTAB == 1) {
	#if APP_VERSION == FULL_VER
			cw->ShowWindow(SW_SHOW);
	#else
			if(IDC_BTN_SETSEDIM == itemID || IDC_GRP_SETSEDIM == itemID) cw->ShowWindow(SW_HIDE);
			else cw->ShowWindow(SW_SHOW);
	#endif
		}
		else			cw->ShowWindow(SW_HIDE);
		//cw->RedrawWindow();
	}
	for (int i = 0; i<TAB_3_NUM; i++) {
		cw = GetDlgItem(TAB_3_ID[i]);
		if (CTAB == 2)	cw->ShowWindow(SW_SHOW);
		else			cw->ShowWindow(SW_HIDE);
		//cw->RedrawWindow();
	}
}
// //////////////////////////////////////////////////////////////////////////////////////////////////////

///==================  ＴＡＢ １ =================================================================

// //////////////////////////////////////////////////////////////////////////////////////////////////////
//  スクリーンツール機能

void CRRI_GUIView::Make_Screen_Tool(BOOL  Tex)
{
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_TOOL];
	GLobj_Delete(&Gp, OBJID_TOOL);
	FXYCOORD		uv[4];
	//  
	/// Init TEXTURE
	if (Tex) {
		GL_Tex_Init(&Gp, 105);
		GL_Set_Bitmap(0, &Gp, SCHnum, SCVnum, 4, 1, Tool_Image, FALSE);
	}
	//
	GLobj_Init(obj, 10, 5);
	int			no[4];
//						反時計まわり
	no[0] = GLobj_Add_Vert(obj, NOWX, NOWY, DUNDEF, FALSE);
	uv[0].x = 0.; uv[0].y = 1.;
	no[3] = GLobj_Add_Vert(obj, NOWX, NOWY+SCVnum, DUNDEF, FALSE);
	uv[3].x = 0.; uv[3].y = 0.;
	no[2] = GLobj_Add_Vert(obj, NOWX + SCHnum, NOWY + SCVnum, DUNDEF, FALSE);
	uv[2].x = 1.; uv[2].y = 0.;
	no[1] = GLobj_Add_Vert(obj, NOWX + SCHnum, NOWY, DUNDEF, FALSE);
	uv[1].x = 1.; uv[1].y = 1.;
	//
	GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 0, uv);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TOOL, TRUE);
	//
	PM.B_ScreenTool = TRUE;
}

int	 CRRI_GUIView::Decide_Tool(CPoint cp)
{
	double		cx, cy;
	XYCOORD		Area[4];
	//
	cx = (double)(cp.x - Gp.win.Wrect.left);
	cy = (double)(Gp.win.Wrect.bottom - cp.y );
	for (int i = 0; i < 4; i++) {
		Area[i].x = (double)(Tool_Frame[i].x + NOWX);
		Area[i].y = (double)(Tool_Frame[i].y + NOWY);
	}
	if (Is_InRegion(cx, cy, 4,Area) <= 0) return 0;
	//
	/// Function
	for (int f = 0; f < 6; f++) {
		for (int i = 0; i < 4; i++) {
			Area[i].x = (double)(Tool_Func[f][i].x + NOWX);
			Area[i].y = (double)(Tool_Func[f][i].y + NOWY);
		}
		if (Is_InRegion(cx, cy, 4, Area) <= 0) continue;
		return f + 1;
	}
	//
	return 0;
}

void	 CRRI_GUIView::EX_Tool(int id)
{
	switch (id) {
		case 1:Tool_Scale(FALSE); break;
		case 2:Tool_Move(64); break;
		case 3:Tool_Move(1); break;
		case 4:Tool_Move(16); break;
		case 5:Tool_Move(4); break;
		case 6:Tool_Scale(TRUE); break;
	}
}

void  CRRI_GUIView::Tool_Scale(BOOL inc)
{
	double	ang;
	double	Hspan, Vspan, CT;
	int		Pixel;
	//
	CT = (Gp.cam[CVIEW].stV + Gp.cam[CVIEW].endV) / 2.;
	Vspan = (Gp.cam[CVIEW].endV - Gp.cam[CVIEW].stV) / 2.;
	if (inc)		Vspan *= (1.-PM.Tool_Rate);
	else			Vspan *= (1. + PM.Tool_Rate);
	//
	Gp.cam[CVIEW].endV = Vspan + CT;
	Gp.cam[CVIEW].stV = CT - Vspan;
	//
	Gp.cam[CVIEW].Dh = fabs((Gp.cam[CVIEW].endV - Gp.cam[CVIEW].stV));
	Gp.cam[CVIEW].Dw = Gp.cam[CVIEW].Dh*Gp.cam[CVIEW].aspect;
	Hspan = Gp.cam[CVIEW].Dw / 2.;
	//
	//
	CT = (Gp.cam[CVIEW].stH + Gp.cam[CVIEW].endH) / 2.;
	Gp.cam[CVIEW].endH = CT + Hspan;
	Gp.cam[CVIEW].stH = CT - Hspan;
	//
	Gp.cam[CVIEW].set = FALSE;
	//
	if (PM.B_MeshLine) {
		Pixel = (int)(Gp.win.cWidth / (Hspan * 2));
		if (Pixel > PM.Mesh_Thresh) Gp.Gobj[OBJID_LINE].display = TRUE;
		else                      Gp.Gobj[OBJID_LINE].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, TRUE, FALSE, UNDEF, TRUE);

}

void  CRRI_GUIView::Tool_Move(int dir)
{
	CRect rect;
	Gp.win.cw->GetWindowRect(&rect);
	//
	double	movex = PM.Tool_Rate * Gp.cam[CVIEW].Dw;
	double	movey = PM.Tool_Rate * Gp.cam[CVIEW].Dh;
	//
	if (dir == 1)			{ movey = 0.; }
	else if (dir == 4)	{ movex = 0.;  }
	else if (dir == 16)	{ movex *= -1.; movey = 0.; }
	else if (dir == 64)	{ movex = 0.; movey *= -1.; }
	//
	Gp.cam[CVIEW].endH -= movex;  Gp.cam[CVIEW].stH -= movex;
	Gp.cam[CVIEW].endV += movey;  Gp.cam[CVIEW].stV += movey;
	Gp.cam[CVIEW].set = FALSE;
	//
	GL_Redraw(&Gp, FALSE, TRUE, FALSE, UNDEF, TRUE);
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  既存プロジェクトの読み込み
int CRRI_GUIView::Reload_Project()
{
	CString		fname,str,title;
	FILE*		fp;
	int			ret;
	//
	fname=DSET.InputFile;
	if (!File_Exist(fname)) {
		MessageBox("RRI_Input.txt does not exist...!\nExit...", "Abend", MB_OK | MB_ICONASTERISK); return 1;
	}
	if ((fp = fopen(fname, "r")) == NULL){
		MessageBox("Cannot open RRI_Input.txt...!\nExit...", "Abend", MB_OK | MB_ICONASTERISK); return 2;
	}
	if ((ret = Read_RRI_INPUT(&DSET, fp)))	{
		str.Format("Error in reading RRI_Input.txt...![Code %d]\nExit...", ret);
		MessageBox(str, "Abend", MB_OK | MB_ICONASTERISK); return ret;
	}

#if APP_VERSION == FULL_VER
	//load sed input file
	if (!LoadSedInputFile()) return 3;
#endif

	PM.B_LatLng = !DSET.SW_LatLong;
	///
	// 存在確認 ＡＤＥＭから基本情報の読み込み
	for (int i = 0; i < FILE_IN_NUM; i++) {
		DSET.in_exist[i] = DSET.in_avail[i] = FALSE;
		if (DSET.in_use[i]) {
			if (File_Exist(DSET.File_names[i])) {
				DSET.in_avail[i] = DSET.in_exist[i] = TRUE;

				//  モデル情報をADEMから得る
				if (i == ADEM_FILE) {
					Get_ArcGIS_Info(DSET.File_names[i], &PM.MHnum, &PM.MVnum, &PM.stLAT, &PM.stLNG, &PM.Size);
					if (PM.B_LatLng) PM.Deg_Unit = PM.Coord_Unit = (int)(1. / PM.Size + 0.05);
					else       {
						PM.stUTM_X = PM.stLNG;
						PM.stUTM_Y = PM.stLAT;
						PM.Deg_Unit = PM.UTMsize = PM.Size;
						PM.Coord_Unit = 1. / PM.Size;
					}
				}
			}
			else    {
				DSET.in_exist[i] = FALSE;
				if (i == RAIN_FILE) continue;
				if (i > ADIR_FILE) { DSET.in_use[i] = FALSE; continue; }
				//
				str.Format("%s file does not exist !\nExit...", File_Title[i]);
				MessageBox(str, "Abend", MB_OK | MB_ICONASTERISK); 
				DestroyWindow(); exit(1);
			}
		}
	}
	//
	AreaXmax = PM.MHnum;
	AreaXmin = 0;
	AreaYmax = PM.MVnum;
	AreaYmin = 0;
	//
	///  ＭＥＳＨのメモリーセット
	if ((MESH = (MINFO**)malloc(PM.MVnum*sizeof(void*))) == NULL) {
		MessageBox("** Error ** Cannot allocate memory", "Abend", MB_OK | MB_ICONASTERISK);
		DestroyWindow(); exit(1);
	}
	for (int v = 0; v < PM.MVnum; v++) {
		if ((MESH[v] = (MINFO*)malloc(PM.MHnum*sizeof(MINFO))) == NULL) {
			v--;
			while (v >= 0) free(MESH[v--]); free(MESH);
			MessageBox("** Error ** Cannot allocate memory", "Abend", MB_OK | MB_ICONASTERISK);
			DestroyWindow(); exit(1);
		}
		for(int h=0;h<PM.MHnum;h++) memset(&MESH[v][h],0, sizeof(MINFO));
	}
	//
	///  データ読み込み
	for (int f = 0; f < FILE_IN_USE; f++) {
		if (DSET.in_use[f] && DSET.in_exist[f]) {
			fname = DSET.File_names[f];
			if ((ret = Read_Data_File(f,fname ,&DSET, MESH))) {
				str.Format("Read error in %s\nExit...", File_Title[f]);
				MessageBox(str, "Abend", MB_OK | MB_ICONASTERISK); DestroyWindow(); exit(1);
			}
			DSET.in_avail[f] = TRUE;
		}
	}
	DSET.set = TRUE;
	///
	//  Cover  Soil データの読み込み
	::SetCurrentDirectory(DSET.Proj_Folder);
	fname = DSET.CoverFile;
	//
	DSET.b_CSexist = FALSE;
	if (File_Exist(fname)) {
		if (!Read_Data_File(LAND_COVER, fname, &DSET, MESH)) {	// 211: Not Match Hnum or Vnum
			fname = DSET.SoilFile;
			if (File_Exist(fname)) {
				if (!Read_Data_File(LAND_SOIL, fname, &DSET, MESH)) {
					DSET.b_CSexist = TRUE;
				}
			}
		}
	}
	else DSET.b_CSexist = FALSE;

	//
	/// 日時の読み込み
	char		buf[SIZE_1K];
	int		year, mon, day, hour, min;
	fname.Format("%s/time.dat", DSET.Proj_Folder);
	if (File_Exist(fname)) {
		fp = fopen(fname, "r"); if (fp == NULL) return 1;
		fgets(buf, SIZE_1K, fp);
		if (sscanf(buf, "%d/%d/%d %d:%d", &year, &mon, &day, &hour, &min) != 5){
			fclose(fp); return 11;
		}
		str.Format("Load start time [ %d/%d/%d %d:%02d ] --> Total time span %d ?", year, mon, day, hour, min, DSET.Hours); 
		//
		PM.StTime = DSET.BT = ::CTime(year, mon, day, hour, min, 0, -1);
		PM.EndTime = DSET.BT + CTimeSpan(0l, DSET.Hours, 0, 0);
		fclose(fp);
	}

	///  
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  全ファイルの書き出し    in_use && in_Avail のみ

int  CRRI_GUIView::Save_All_Files()
{
	CString	fname;
	::SetCurrentDirectory(DSET.Proj_Folder);
	//
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Write_All_Files(File_Format, File_Order, DSET, MESH, PM);
	//
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  緯度・経度　メッシュ範囲のセット・ゲット
int CRRI_GUIView::Get_RectArea()
{
	CWnd*		cw;
	int			ival;
	double*		val;
	CString		Sdeg, Smin, Ssec;
	//
	BXmin = AreaXmin;
	BXmax = AreaXmax;
	BYmin = AreaYmin;
	BYmax = AreaYmax;
	//
	for (int i = 0; i < AREA_ID_NUM; i += 3) {
		if (i == 0)		val = &PM.stLNG;
		else if (i == 3)	val = &PM.endLNG;
		else if (i == 6)	val = &PM.stLAT;
		else if (i == 9)	val = &PM.endLAT;
		//
		*val = 0.;
		cw = GetDlgItem(AREA_ID[i]); cw->GetWindowTextA(Sdeg);
		cw = GetDlgItem(AREA_ID[i + 1]); cw->GetWindowTextA(Smin);
		cw = GetDlgItem(AREA_ID[i + 2]); cw->GetWindowTextA(Ssec);

		if (atof(Sdeg) > 0.) {
			*val = atof(Sdeg) + atof(Smin) / 60. + atof(Ssec) / 3600.;
		}
		else  {
			*val = fabs(atof(Sdeg)) + atof(Smin) / 60. + atof(Ssec) / 3600.;
			*val *= -1.;
		}
		ival = (int)((*val)*PM.Coord_Unit);
		*val = ((double)ival) / PM.Coord_Unit;
	}
	//
	Set_RectArea();
	return 0;
}
//_______________________________________________
//|||||||||||||||||||||||||||||||||||||||||||||||
//   範囲のガイド
//|||||||||||||||||||||||||||||||||||||||||||||||
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int CRRI_GUIView::Set_RectArea()
{
	CWnd*		cw;
	CString		str;
	double		val,odd;
	int			deg, min, sec;
	//
	odd = 5.*EPS10;
	PLtoDMS(PM.stLNG + odd, &deg, &min, &sec);
	s_stLNG_deg.Format("%d", deg);
	s_stLNG_min.Format("%d", min);
	s_stLNG_sec.Format("%d", sec);
	//
	PLtoDMS(PM.endLNG + odd, &deg, &min, &sec);
	s_endLNG_deg.Format("%d", deg);
	s_endLNG_min.Format("%d", min);
	s_endLNG_sec.Format("%d", sec);
	//
	PLtoDMS(PM.stLAT + odd, &deg, &min, &sec);
	s_stLAT_deg.Format("%d", deg);
	s_stLAT_min.Format("%d", min);
	s_stLAT_sec.Format("%d", sec);
	//
	PLtoDMS(PM.endLAT + odd, &deg, &min, &sec);
	s_endLAT_deg.Format("%d", deg);
	s_endLAT_min.Format("%d", min);
	s_endLAT_sec.Format("%d", sec);
	//
	UDF;
	return 0;
}
//
void CRRI_GUIView::Set_UTMArea()
{
	CWnd*		cw;
	CString		str;
	//
	for (int i = 0; i < Disp_UTM_NUM-1; i++) {  // Disp_UTM_NUM-1 はSTATIC
		cw = GetDlgItem(Disp_UTM_ID[i]);
		if (i == 0)		str.Format("%.1lf", PM.stUTM_X);
		else if (i == 1)	str.Format("%.1lf", PM.endUTM_X);
		else if (i == 2)	str.Format("%.1lf", PM.stUTM_Y);
		else if (i == 3)	str.Format("%.1lf", PM.endUTM_Y);
		cw->SetWindowTextA(str);
	}
	//
	UDF;
	return;
}
//
void CRRI_GUIView::Clear_RectArea()
{
	s_stLNG_deg = _T("");
	s_stLNG_min = _T("");
	s_stLNG_sec = _T("");
	//
	s_endLNG_deg = _T("");
	s_endLNG_min = _T("");
	s_endLNG_sec = _T("");
	//
	s_stLAT_deg = _T("");
	s_stLAT_min = _T("");
	s_stLAT_sec = _T("");
	//
	s_endLAT_deg = _T("");
	s_endLAT_min = _T("");
	s_endLAT_sec = _T("");
	//
	UDF;
	return;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  緯度・経度　メッシュ範囲編集
void CRRI_GUIView::OnEnChangeEdit105(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG Low Deg
void CRRI_GUIView::OnEnChangeEdit106(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG Low min
void CRRI_GUIView::OnEnChangeEdit107(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG Low sec
void CRRI_GUIView::OnEnChangeEdit108(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG High Deg
void CRRI_GUIView::OnEnChangeEdit109(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG High min
void CRRI_GUIView::OnEnChangeEdit110(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LNG High sec
void CRRI_GUIView::OnEnChangeEdit111(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT Low Deg
void CRRI_GUIView::OnEnChangeEdit112(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT Low min
void CRRI_GUIView::OnEnChangeEdit113(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT Low sec
void CRRI_GUIView::OnEnChangeEdit114(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT High Deg
void CRRI_GUIView::OnEnChangeEdit115(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT High min
void CRRI_GUIView::OnEnChangeEdit116(){ UDT; Cnt_CArea++; Disp_Controls(); }		// LAT High sec

void CRRI_GUIView::OnBnClickedButton114() { Change_Area(); }


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  初期ガイド
///------------------------------------------------------------------------
HRESULT	CRRI_GUIView::Show_Init_Guide()
{
//	 初期化 スクリーンツールの分も含む
	//
	int		UX, UY, id, cnt;
	double	spanX, spanY;
	double		X, Y, Z = 0.;
	GL_OBJECT* Gobj = &Gp.Gobj[OBJID_GUIDE];
	GLobj_Delete(&Gp, OBJID_GUIDE);

	if (PM.B_UseJFlow) {
		EX_FILE upgInfo = PM.EXDATA[CEX].Files[EX_ACC];
		if (FAILED(Set_Guide_TEX_JFLOW(upgInfo))) { COMMENT("Error: Failed to load guide image"); return E_FAIL; }
		int rows = upgInfo.Highlat - upgInfo.Lowlat;//JFlowInfo[0];
		int columns = upgInfo.endlng - upgInfo.stlng;//JFlowInfo[1];
		int count = rows * columns;
		CEX_LABEL = CEX;
		GLobj_Init(Gobj, count+10, count+5);
		for (int v = 0; v <= rows; v++) {
			for (int h = 0; h <= columns; h++) {
				X = h * upgInfo.subdev;
				Y = (rows - v) * upgInfo.subdev;
				GLobj_Add_Vert(Gobj, X, Y, Z, FALSE);
			}
		}
		// poly
		int			no[4], pno;
		FXYCOORD	uv[4];
		uv[0].x = 0.0f;
		uv[1].x = 0.0f;
		uv[2].x = 1.f;
		uv[3].x = 1.f;
		uv[0].y = 0.0f;
		uv[1].y = 1.0f;
		uv[2].y = 1.0f;
		uv[3].y = 0.f;
		//
		for (int v = 0; v < rows; v++) {
			for (int h = 0; h < columns; h++) {
				id = v * columns + h + 1;				// ツール分　＋１
				cnt = v * (columns + 1) + h;
				no[0] = cnt;
				no[1] = cnt + columns + 1;
				no[2] = no[1] + 1;
				no[3] = no[2] - (columns + 1);
				pno = GLobj_Add_Poly(Gobj, 4, no, GL_POLYGON, id, uv);
				Gobj->poly[pno].both = TRUE;
			}
		}
	}
	else {
		if (FAILED(Set_Guide_TEX())) { COMMENT("Error: Failed to load guide image"); return E_FAIL; }
		//**************************
			//UX = ((PM.EXDATA[CEX].Files[EX_ACC].endlng - PM.EXDATA[CEX].Files[EX_ACC].stlng)*
			//	PM.EXDATA[CEX].Files[EX_ACC].subdev) / 10;
			//UY = ((PM.EXDATA[CEX].Files[EX_ACC].Highlat - PM.EXDATA[CEX].Files[EX_ACC].Lowlat)*
			//	PM.EXDATA[CEX].Files[EX_ACC].subdev) / 10;
		spanX = ((PM.EXDATA[CEX].Files[EX_ACC].endlng - PM.EXDATA[CEX].Files[EX_ACC].stlng) *
			PM.EXDATA[CEX].Files[EX_ACC].subdev) / 10.;
		spanY = ((PM.EXDATA[CEX].Files[EX_ACC].Highlat - PM.EXDATA[CEX].Files[EX_ACC].Lowlat) *
			PM.EXDATA[CEX].Files[EX_ACC].subdev) / 10.;
		CEX_LABEL = CEX;

		//
	//	spanX = (double)UX; spanY = (double)UY;
		//
		// 20190201 Start
		//if (PM.UseGuide == 3) {
		//	GLobj_Init(Gobj, 729+10, 729+5);
		//}
		//else {
		GLobj_Init(Gobj, 110, 105);
		//}
		// 20190201 End
		//
		for (int v = 0; v <= GUIDE_NUM; v++) {
			for (int h = 0; h <= GUIDE_NUM; h++) {
				X = h * spanX;
				Y = (GUIDE_NUM - v) * spanY;
				GLobj_Add_Vert(Gobj, X, Y, Z, FALSE);
			}
		}
		// poly
		int			no[4], pno;
		FXYCOORD	uv[4];
		uv[0].x = 0.0f;
		uv[1].x = 0.0f;
		uv[2].x = 1.f;
		uv[3].x = 1.f;
		uv[0].y = 0.0f;
		uv[1].y = 1.0f;
		uv[2].y = 1.0f;
		uv[3].y = 0.f;
		//
		for (int v = 0; v < GUIDE_NUM; v++) {
			for (int h = 0; h < GUIDE_NUM; h++) {
				id = v * GUIDE_NUM + h + 1;				// ツール分　＋１
				cnt = v * (GUIDE_NUM + 1) + h;
				no[0] = cnt;
				no[1] = cnt + GUIDE_NUM + 1;
				no[2] = no[1] + 1;
				no[3] = no[2] - (GUIDE_NUM + 1);
				pno = GLobj_Add_Poly(Gobj, 4, no, GL_POLYGON, id, uv);
				Gobj->poly[pno].both = TRUE;
			}
		}
	}
	
	//
	GL_Redraw(&Gp, TRUE, TRUE, TRUE, OBJID_GUIDE, TRUE);
	PM.Model = TRUE;
	return S_OK;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//  ガイド用テクスチャー作成
HRESULT CRRI_GUIView::Set_Guide_TEX()
{
	int			id, ResH, ResV, imbyte, Resmax;
	CString		path, fname, cmd;
	BYTE* pImage;
	CBUSY* CB;
	char		Cname[128], Title[128];

	//
	// for ReEntrance
	//
	Change_Cursor(&Gp, IDC_WAIT);
	//
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	//
	if (Gp.Texnum > 0) {
		CB->Set_Title("Release Current Texture");
		CB->Set_Prog(0, 10);
		CB->ShowWindow(SW_SHOW);
		for (int i = 1; i < Gp.Texnum + 1; i++) {		// 最初の０はスクリーンツールなので削除しない
			SAFE_FREE(Gp.Tex[i].image);
			if (i % 10 == 0) CB->Set_Pos((int)(i / 10) + 1);
		}
		//		SAFE_FREE(Gp.Tex);   領域自体は削除しない。
		Gp.Texnum = 1;
	}
	CB->Set_Title("Set & Make Guide Image");
	CB->Set_Prog(0, 10);
	CB->ShowWindow(SW_SHOW);
	//
	Get_Title(PM.EXDATA[CEX].Files[EX_ACC].fname, Title);
	Title[strlen(Title) - 4] = 0x0;
	CString work;	// 20190201 Add
	work = Title;	// 20190201 Add
	work = work.Right(work.GetLength() - work.ReverseFind('/') - 1);	// 20190201 Add
	strcpy(Title, work);	// 20190201 Add
	path.Format("%s\\RRI_CONTENTS\\HydroSHEDS\\%s_IMAGE\\%s", m_BootPath, Title, Title);
	
	//
	for (int v = 0; v < GUIDE_NUM; v++) {
		cmd.Format("Set & Make guide image %d", v + 1);
		CB->Set_Title(cmd);
		for (int h = 0; h < GUIDE_NUM; h++) {
			id = v * GUIDE_NUM + h + 1;			// ツールの分１だけずらす
			fname.Format("%s_%1d%1d.bmp", path, v, h);
			//
			strcpy(Cname, fname);
			if (!File_Exist(Cname)) {
				CB->Close();
				cmd.Format("** Error ** File not exist...\n   file=%s", Cname);
				MessageBox(cmd, "Missed", MB_OK | MB_ICONASTERISK);
				return E_FAIL;
			}
			//
			if (!Get_Image_Size(fname, &ResH, &ResV, &imbyte)) {
				cmd.Format("** Error ** Get information error...   file=%s", fname);
				COMMENT(cmd);
				return E_FAIL;
			}
			//
			Gp.Disp_Size = 1;
			pImage = Get_BMP_File(fname, &ResH, &ResV, &imbyte, TRUE);		// ＢＭＰファイルのみ ＩＮＤＥＸ取得
			if (pImage == NULL) {
				cmd.Format("** Error ** Get image data error...   file=%s", fname);
				COMMENT(cmd);
				return E_FAIL;
			}
			//
			GL_Set_Bitmap(id, &Gp, ResH, ResV, imbyte, Gp.Disp_Size, pImage, FALSE);			// カラー登録
			//
			SAFE_FREE(pImage);
		}
		CB->Set_Pos(v + 1);
	}
	CB->Close();
	//
	Gp.SetTex = TRUE;
	Change_Cursor(&Gp, IDC_ARROW);
	//
	return S_OK;
}
#include <ppl.h>
//  ガイド用テクスチャー作成
HRESULT CRRI_GUIView::Set_Guide_TEX_JFLOW(EX_FILE upgInfo)
{
	int			ResH, ResV, imbyte, Resmax;
	CBUSY* CB;
	char		Cname[128], Title[128];
	WIN32_FIND_DATA     upgFiles[150];
	//
	// for ReEntrance
	//
	Change_Cursor(&Gp, IDC_WAIT);
	//
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	//
	if (Gp.Texnum > 0) {
		CB->Set_Title("Release Current Texture");
		CB->Set_Prog(0, 10);
		CB->ShowWindow(SW_SHOW);
		for (int i = 1; i < Gp.Texnum + 1; i++) {		// 最初の０はスクリーンツールなので削除しない
			SAFE_FREE(Gp.Tex[i].image);
			if (i % 10 == 0) CB->Set_Pos((int)(i / 10) + 1);
		}
		//		SAFE_FREE(Gp.Tex);   領域自体は削除しない。
		Gp.Texnum = 1;
	}
	CB->Set_Title("Set & Make Guide Image");
	CB->Set_Prog(0, 10);
	CB->ShowWindow(SW_SHOW);
	int rows = upgInfo.Highlat - upgInfo.Lowlat;
	int columns = upgInfo.endlng - upgInfo.stlng;
	CB->Set_Prog(0, rows * columns);
	CB->ShowWindow(SW_SHOW);

	Color_Val Ctable[6];
	// 0xFF << 24 mean opacity 1
	Ctable[0].ival = 0;  Ctable[0].col = RGB(53, 86, 255) | 0xFF << 24;
	Ctable[1].ival = 20;  Ctable[1].col = RGB(216, 250, 200) | 0xFF << 24;
	Ctable[2].ival = 1000;  Ctable[2].col = RGB(60, 220, 255) | 0xFF << 24;
	Ctable[3].ival = 10000;  Ctable[3].col = RGB(60, 150, 255) | 0xFF << 24;
	Ctable[4].ival = 100000;  Ctable[4].col = RGB(0, 0, 250) | 0xFF << 24;
	Ctable[5].ival = 9999999;  Ctable[5].col = RGB(255, 0, 0) | 0xFF << 24;

	//set emptyImg
	int emptySize = upgInfo.subdev * upgInfo.subdev * sizeof(COLORREF);
	COLORREF* emptyImg = (COLORREF*)malloc(emptySize);
	for (int i = 0; i < upgInfo.subdev * upgInfo.subdev; i++) {
		emptyImg[i] = Ctable[0].col;
	}

	CString key;
	std::map<CString, JFlowTifCache> mapCache;
	std::map<CString, JFlowTifCache>::iterator l_it;

	CString		path, fname, cmd;
	COLORREF* pImage;
	int width, height;
	path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\upg\\", m_BootPath);
	for (int n = upgInfo.Highlat - 1; n >= upgInfo.Lowlat; n--) {
		for (int e = upgInfo.stlng; e < upgInfo.endlng; e++) {
			fname.Format("%sn%de%d_upg.tif", path, n, e);
			strcpy(Cname, fname);
			if (File_Exist(Cname)) {
				key.Format("%d,%d", (int)e, (int)n);
				JFlowTifCache tifCache;
				tifCache.filepath = Cname;
				mapCache.insert(std::pair<CString, JFlowTifCache>(key, tifCache));
			}
		}
	}
	GDALAllRegister();
	Concurrency::parallel_for_each(begin(mapCache), end(mapCache), [&](std::pair<const CString, JFlowTifCache> &el) {
		Get_GeoTiff_Bytes(el.second.filepath, &el.second, Ctable);
	});
	GDALDestroyDriverManager();
	int count = 0;
	for (int n = upgInfo.Highlat - 1; n >= upgInfo.Lowlat; n--) {
		for (int e = upgInfo.stlng; e < upgInfo.endlng; e++) {
			int id = (upgInfo.Highlat - 1 - n) * columns + (e - upgInfo.stlng) + 1;
			key.Format("%d,%d", e, n);
			l_it = mapCache.find(key);
			cmd.Format("Set & Make guide image N%dE%d", n, e);
			CB->Set_Title(cmd);
			if (l_it == mapCache.end()) {
				pImage = (COLORREF*)malloc(emptySize);
				memcpy(pImage, emptyImg, emptySize);
			}
			else {
				pImage = l_it->second.datas;
				if (pImage == NULL) {
					cmd.Format("** Error ** Get image data error...   file=%s", l_it->second.filepath);
					COMMENT(cmd);
					return E_FAIL;
				}
			}
			Gp.Disp_Size = 1;
			GL_Set_Bitmap(id, &Gp, upgInfo.subdev, upgInfo.subdev, upgInfo.byte, Gp.Disp_Size, (BYTE*)pImage, FALSE);			// カラー登録
			SAFE_FREE(pImage);
			count++;
			CB->Set_Pos(count);
		}
	}
	SAFE_FREE(emptyImg);
	//
	CB->Close();
	//
	Gp.SetTex = TRUE;
	Change_Cursor(&Gp, IDC_ARROW);
	//
	return S_OK;
}

bool CRRI_GUIView::Get_GeoTiff_Bytes(CString fname, JFlowTifCache* tifCache, Color_Val* Ctable)
{
	char* pszSourceSRS = nullptr;
	BYTE* Lpdata = NULL;
	COLORREF* Lpcol = NULL;
	CPLFree(pszSourceSRS);
	pszSourceSRS = SanitizeSRS("WGS84");

	char** papszOpenOptions = nullptr;
	GDALDatasetH hSrcDS
		= GDALOpenEx(fname, GDAL_OF_RASTER, nullptr,
			(const char* const*)papszOpenOptions, nullptr);
	if (hSrcDS == NULL) return false;

	int bandCount = GDALGetRasterCount(hSrcDS);
	if (bandCount > 1)
	{
		return false;
	}

	if (pszSourceSRS != nullptr)
	{
		if (GDALGetGeoTransform(hSrcDS, tifCache->adfGeoTransform) != CE_None)
		{
			return false;
		}

		if (!GDALInvGeoTransform(tifCache->adfGeoTransform, tifCache->adfInvGeoTransform))
		{
			return false;
		}
	}
	GDALRasterBandH hBand = GDALGetRasterBand(hSrcDS, GDALGetRasterCount(hSrcDS));

	if (hBand == nullptr) return false;
	tifCache->xsize = GDALGetRasterXSize(hSrcDS);
	tifCache->ysize = GDALGetRasterYSize(hSrcDS);
	Lpdata = (BYTE*)CPLMalloc(sizeof(int) * tifCache->xsize * tifCache->ysize);
	if (GDALRasterIO(hBand, GF_Read, 0, 0, tifCache->xsize, tifCache->ysize, Lpdata, tifCache->xsize, tifCache->ysize, GDT_Int32, 0, 0) != CE_None)
	{
		return false;
	}
	if (hSrcDS) GDALClose(hSrcDS);
	if ((Lpcol = (COLORREF*)calloc(tifCache->xsize * tifCache->ysize, sizeof(COLORREF))) == NULL) {
		free(Lpdata); return false;
	}
	GDALDumpOpenDatasets(stderr);
	CPLFree(pszSourceSRS);
	CSLDestroy(papszOpenOptions);
	//---------------------------------------------------データ定義
	int* pint, val, id;
	BYTE* pbyte;
	float* pfloat, fval;
	pint = (int*)Lpdata;
	for (int v = 0; v < tifCache->ysize; v++) {
		for (int h = 0; h < tifCache->xsize; h++) {
			id = (v * tifCache->xsize + h);			// カラーメモリーの位置
			val = *((int*)pint);		pint++;
			Lpcol[id] = Get_Col_Val(val, COLOR_STEP, 6, Ctable);
		}
	}
	
	//
	//---------------------------------------------------終了処理
	CPLFree(Lpdata);
	tifCache->datas = Lpcol;
	return true;
}

//  フォルダーの作成　新規作成
HRESULT CRRI_GUIView::Define_Folder()
{
	CSetProject  CS;
	if (CS.DoModal() == IDCANCEL) return E_FAIL;
	CEX_LABEL = CEX;

	// 確認の意味でＰｒｏｊｅｃｔフォルダの存在を調べる
	CString		Proot;
	Proot.Format("%s/Project", m_BootPath);
	if (!Folder_Exist(Proot)) CreateDirectory(Proot, NULL);

	//
	if (!Folder_Exist(DSET.Proj_Folder)) CreateDirectory(DSET.Proj_Folder, NULL);
	//
	// infile output
	CString		dirname;
	for (int i = 1; i < 8; i++) {
		if (!Folder_Exist(DSET.Folder_Name[i])) CreateDirectory(DSET.Folder_Name[i], NULL);
	}
	//
	s_ProjName.Format("%s", DSET.Proj_Title); UDF;
	DSET.set = TRUE;
	//
	return S_OK;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  河川最下流端の指定
HRESULT CRRI_GUIView::Disp_River_Pos(BOOL  Add)
{
	int				no[4];
	double			lat, lng;
	GL_OBJECT*		obj = &Gp.Gobj[OBJID_WORK];
	FCOLOR			Fcol;
	GLobj_Delete(&Gp, OBJID_WORK);
	//
	// 河川追加
	double  Rect_Margin=1.0;		// RIVinfo を参照　STAT(PROC_INDICATE_RIVMESH）時
	if (Add) {
		Fcol = F_COLOR(255, 0, 0);
		for (int i = 0; i < RIVnum; i++) {		// 
			no[0] = GLobj_Add_Vert(obj, RIVinfo[i].x, RIVinfo[i].y, 5., FALSE);
			no[1] = GLobj_Add_Vert(obj, RIVinfo[i].x + Rect_Margin, RIVinfo[i].y, 5., FALSE);
			no[2] = GLobj_Add_Vert(obj, RIVinfo[i].x + Rect_Margin, RIVinfo[i].y + Rect_Margin, 5., FALSE);
			no[3] = GLobj_Add_Vert(obj, RIVinfo[i].x, RIVinfo[i].y + Rect_Margin, 5., FALSE);
			GLobj_Add_Poly(obj, 4, no, GL_POLYGON, Fcol);
		}
	}
	//
	// 除外ポイント　　		//RivEXpos を参照　STAT(PROC_DISPLAY_MESH）時
	else {
		Fcol = F_COLOR(0, 0, 255);
		no[0] = GLobj_Add_Vert(obj, RivEXpos.x, RivEXpos.y, 5., FALSE);
		no[1] = GLobj_Add_Vert(obj, RivEXpos.x + Rect_Margin, RivEXpos.y, 5., FALSE);
		no[2] = GLobj_Add_Vert(obj, RivEXpos.x + Rect_Margin, RivEXpos.y + Rect_Margin, 5., FALSE);
		no[3] = GLobj_Add_Vert(obj, RivEXpos.x, RivEXpos.y + Rect_Margin, 5., FALSE);
		GLobj_Add_Poly(obj, 4, no, GL_POLYGON, Fcol);
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_WORK, TRUE);
	//
	Disp_Controls();
	//
	return S_OK;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  河川最下流端の取り消し
HRESULT CRRI_GUIView::Del_River_Pos(BOOL Add)
{
	int				no[4];
	GL_OBJECT*		obj = &Gp.Gobj[OBJID_WORK];
	FCOLOR			Fcol = F_COLOR(255, 0, 0);
	GLobj_Delete(&Gp, OBJID_WORK);
	//
	if (Add) {
		if (RIVnum == 0) return S_OK;
		else if (RIVnum == 1)  RIVnum = 0;			// Redraw
		else {
			RIVnum--;
			for (int i = 0; i < RIVnum; i++) {		// 既存のポイント 現在値はＲＩＶｎｕｍに加えない。
				no[0] = GLobj_Add_Vert(obj, RIVinfo[i].x, RIVinfo[i].y, 5., FALSE);
				no[1] = GLobj_Add_Vert(obj, RIVinfo[i].x + 1., RIVinfo[i].y, 5., FALSE);
				no[2] = GLobj_Add_Vert(obj, RIVinfo[i].x + 1., RIVinfo[i].y + 1., 5., FALSE);
				no[3] = GLobj_Add_Vert(obj, RIVinfo[i].x, RIVinfo[i].y + 1., 5., FALSE);
				GLobj_Add_Poly(obj, 4, no, GL_POLYGON, Fcol);
			}
			//
		}
	}
	else RivEX = FALSE;
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_WORK, TRUE);
	//
	Disp_Controls();
	return S_OK;
}
///
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 	CRRI_GUIView::Trans_COORD_LATLNG(int kind,double x, double y, double* lng, double* lat)
{
	//*lng = PM.EXDATA[CEX].Files[kind].stlng + (x + unit) / PM.EXDATA[CEX].Files[kind].subdev;
	//*lat = PM.EXDATA[CEX].Files[kind].Lowlat + (y - unit) / PM.EXDATA[CEX].Files[kind].subdev;
	*lng = PM.EXDATA[CEX].Files[kind].stlng + x  / PM.EXDATA[CEX].Files[kind].subdev;
	*lat = PM.EXDATA[CEX].Files[kind].Lowlat + y / PM.EXDATA[CEX].Files[kind].subdev;
}
void 	CRRI_GUIView::Trans_LATLNG_COORD(int kind, double lng, double lat, double* x, double* y)
{
	//*x = (lng - unit - PM.EXDATA[CEX].Files[kind].stlng) / (1. / PM.EXDATA[CEX].Files[kind].subdev);
	//*y = (lat+unit - PM.EXDATA[CEX].Files[kind].Lowlat) / (1. / PM.EXDATA[CEX].Files[kind].subdev);
	*x = (lng  - PM.EXDATA[CEX].Files[kind].stlng) * PM.EXDATA[CEX].Files[kind].subdev ;
	*y = (lat  - PM.EXDATA[CEX].Files[kind].Lowlat) * PM.EXDATA[CEX].Files[kind].subdev;
}

//-----------------------------------------------------------------------------------------
//   HYDROSHEDS の１メッシュデータ取得
//-----------------------------------------------------------------------------------------
//
int		CRRI_GUIView::Get_HYDROSHEDS_Value(double lng, double  lat, int kind)
{
	int		ret,px,py;		// 注意　左上からのデータ
	BYTE	val[5];

////	lat += (1. / PM.EXDATA[CEX].Files[kind].subdev);
	px = (int)((lng - PM.EXDATA[CEX].Files[kind].stlng) * PM.EXDATA[CEX].Files[kind].subdev);
	py = (int)((PM.EXDATA[CEX].Files[kind].Highlat - lat)* PM.EXDATA[CEX].Files[kind].subdev);
	//
	::SetCurrentDirectory(m_BootPath);
	int		fi;
	if ((fi = _open(PM.EXDATA[CEX].Files[kind].fname, _O_BINARY | _O_RDONLY, _S_IREAD)) == -1)return UNDEF;
	//
	memset(val, 0x0, 5);
	long	Lpos;
	Lpos = (long)((py*PM.EXDATA[CEX].Files[kind].Htotal + px)*PM.EXDATA[CEX].Files[kind].byte);
	lseek(fi, Lpos, SEEK_SET); 
	read(fi, val, PM.EXDATA[CEX].Files[kind].byte);
	close(fi);
	//
	if(kind == EX_ACC )			ret = *(int*)val;
	else if (kind == EX_DIR)	ret = (int)val[0];
	else if (kind == EX_DEM)	ret = *(short*)val;
	//
	return ret;
}

//-----------------------------------------------------------------------------------------
//   HYDROSHEDS の１メッシュデータ取得
//-----------------------------------------------------------------------------------------
//
int		CRRI_GUIView::Get_JFlwMesh_Value(double lng, double  lat, int kind)
{
	int acc;
	CString path, fname;

	if (kind == EX_ACC) {
		path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\upg\\", m_BootPath);
		fname.Format("%sn%2de%3d_upg.tif", path, (int)lat, (int)lng);
	}
	else if (kind == EX_DIR) {
		path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\dir\\", m_BootPath);
		fname.Format("%sn%2de%3d_dir.tif", path, (int)lat, (int)lng);
	}
	else if (kind == EX_DEM) {
		path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\elv\\", m_BootPath);
		fname.Format("%sn%2de%3d_elv.tif", path, (int)lat, (int)lng);
	}
	else {
		MessageBox("**Error** \n", "Cancel", MB_OK | MB_ICONERROR);
		return 0;
	}
	acc = Get_J_Flw_Value(fname, lng, lat);
	return acc;
}

//-----------------------------------------------------------------------------------------
//   Japan Flow Direction Map データ取得 20190201
//-----------------------------------------------------------------------------------------
//
bool	CRRI_GUIView::Create_J_Flw_Cache(CString fname, JFlowCache* areaCache)
{
	char* pszSourceSRS = nullptr;
	CPLFree(pszSourceSRS);
	pszSourceSRS = SanitizeSRS("WGS84");

	char** papszOpenOptions = nullptr;
	GDALDatasetH hSrcDS
		= GDALOpenEx(fname, GDAL_OF_RASTER, nullptr,
			(const char* const*)papszOpenOptions, nullptr);
	if (hSrcDS == NULL) return false;

	int bandCount = GDALGetRasterCount(hSrcDS);
	if (bandCount > 1)
	{
		return false;
	}

	if (pszSourceSRS != nullptr)
	{
		if (GDALGetGeoTransform(hSrcDS, areaCache->adfGeoTransform) != CE_None)
		{
			return false;
		}

		if (!GDALInvGeoTransform(areaCache->adfGeoTransform, areaCache->adfInvGeoTransform))
		{
			return false;
		}
	}
	GDALRasterBandH hBand = GDALGetRasterBand(hSrcDS, GDALGetRasterCount(hSrcDS));

	if (hBand == nullptr) return false;
	areaCache->xsize = GDALGetRasterXSize(hSrcDS);
	areaCache->ysize = GDALGetRasterYSize(hSrcDS);
	areaCache->datas = (double*)CPLMalloc(sizeof(double) * areaCache->xsize * areaCache->ysize * 2);
	if (GDALRasterIO(hBand, GF_Read, 0, 0, areaCache->xsize, areaCache->ysize, areaCache->datas, areaCache->xsize, areaCache->ysize, GDT_CFloat64, 0, 0) != CE_None)
	{
		return false;
	}
	if (hSrcDS) GDALClose(hSrcDS);

	GDALDumpOpenDatasets(stderr);
	CPLFree(pszSourceSRS);
	CSLDestroy(papszOpenOptions);
	return true;
}
double CRRI_GUIView::Get_J_Flw_Value_From_Cache( double lng, double lat, JFlowCache* areaCache)
{
	
	int iPixel = static_cast<int>(floor(
		areaCache->adfInvGeoTransform[0]
		+ areaCache->adfInvGeoTransform[1] * lng
		+ areaCache->adfInvGeoTransform[2] * lat));
	int iLine = static_cast<int>(floor(
		areaCache->adfInvGeoTransform[3]
		+ areaCache->adfInvGeoTransform[4] * lng
		+ areaCache->adfInvGeoTransform[5] * lat));
	//
	return areaCache->datas[2*(iLine * areaCache->xsize + iPixel)];
}

double		CRRI_GUIView::Get_J_Flw_Value(CString fname, double lng, double lat)
{
	double		ret = 0;		// 注意　左上からのデータ
	BYTE	val[5];
	GDALDataset  *poDataset;
	
	::SetCurrentDirectory(m_BootPath);
	int		fi;

	char	*pszSourceSRS = nullptr;
	CPLFree(pszSourceSRS);
	pszSourceSRS = SanitizeSRS("WGS84");
	//pszSourceSRS = nullptr;

	GDALAllRegister();
	
	char             **papszOpenOptions = nullptr;
	GDALDatasetH hSrcDS
		= GDALOpenEx(fname, GDAL_OF_RASTER, nullptr,
		(const char* const*)papszOpenOptions, nullptr);
	if (hSrcDS == NULL) return UNDEF;

	OGRSpatialReferenceH hSrcSRS = nullptr, hTrgSRS = nullptr;
	OGRCoordinateTransformationH hCT = nullptr;
	if (pszSourceSRS != nullptr && !EQUAL(pszSourceSRS, "-geoloc"))
	{

		hSrcSRS = OSRNewSpatialReference(pszSourceSRS);
		hTrgSRS = OSRNewSpatialReference(GDALGetProjectionRef(hSrcDS));

		hCT = OCTNewCoordinateTransformation(hSrcSRS, hTrgSRS);
		if (hCT == nullptr)
			return UNDEF;
	}
	
	std::vector<int>   anBandList;
	if (anBandList.empty())
	{
		for (int i = 0; i < GDALGetRasterCount(hSrcDS); i++)
			anBandList.push_back(i + 1);
	}

	double dfGeoX = lng;
	double dfGeoY = lat;
	int iPixel, iLine;

	if (hCT)
	{
		if (!OCTTransform(hCT, 1, &dfGeoX, &dfGeoY, nullptr))
			exit(1);
	}

	if (pszSourceSRS != nullptr)
	{
		double adfGeoTransform[6] = {};
		if (GDALGetGeoTransform(hSrcDS, adfGeoTransform) != CE_None)
		{
			return UNDEF;
		}

		double adfInvGeoTransform[6] = {};
		if (!GDALInvGeoTransform(adfGeoTransform, adfInvGeoTransform))
		{
			return UNDEF;
		}

		iPixel = static_cast<int>(floor(
			adfInvGeoTransform[0]
			+ adfInvGeoTransform[1] * dfGeoX
			+ adfInvGeoTransform[2] * dfGeoY));
		iLine = static_cast<int>(floor(
			adfInvGeoTransform[3]
			+ adfInvGeoTransform[4] * dfGeoX
			+ adfInvGeoTransform[5] * dfGeoY));
	}
	else
	{
		iPixel = static_cast<int>(floor(dfGeoX));
		iLine = static_cast<int>(floor(dfGeoY));
	}

	CPLString osLine;

	bool bPixelReport = true; 
	for (int i = 0; bPixelReport && i < static_cast<int>(anBandList.size()); i++)
	{
		GDALRasterBandH hBand = GDALGetRasterBand(hSrcDS, anBandList[i]);

		int iPixelToQuery = iPixel;
		int iLineToQuery = iLine;

		int	nOverview = -1;
		if (nOverview >= 0 && hBand != nullptr)
		{
			GDALRasterBandH hOvrBand = GDALGetOverview(hBand, nOverview);
			if (hOvrBand != nullptr)
			{
				int nOvrXSize = GDALGetRasterBandXSize(hOvrBand);
				int nOvrYSize = GDALGetRasterBandYSize(hOvrBand);
				iPixelToQuery = static_cast<int>(
					0.5 +
					1.0 * iPixel / GDALGetRasterXSize(hSrcDS) * nOvrXSize);
				iLineToQuery = static_cast<int>(
					0.5 +
					1.0 * iLine / GDALGetRasterYSize(hSrcDS) * nOvrYSize);
				if (iPixelToQuery >= nOvrXSize)
					iPixelToQuery = nOvrXSize - 1;
				if (iLineToQuery >= nOvrYSize)
					iLineToQuery = nOvrYSize - 1;
			}
			else
			{
				//
			}
			hBand = hOvrBand;
		}

		if (hBand == nullptr)
			continue;

		double adfPixel[2];
		if (GDALRasterIO(hBand, GF_Read, iPixelToQuery, iLineToQuery, 1, 1, adfPixel, 1, 1, GDT_CFloat64, 0, 0) == CE_None)
		{
			ret = (double)adfPixel[0];
			break;
		}
	}

	//

	if (hCT) {
		OSRDestroySpatialReference(hSrcSRS);
		OSRDestroySpatialReference(hTrgSRS);
		OCTDestroyCoordinateTransformation(hCT);
	}

	if (hSrcDS)
		GDALClose(hSrcDS);

	GDALDumpOpenDatasets(stderr);
	GDALDestroyDriverManager();
	CPLFree(pszSourceSRS);
	CSLDestroy(papszOpenOptions);//
	
	//
	return ret;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//       ==========  Ｍａｉｎ　Ｆｌｏｗ ========
///______________________________________________________________________________________
void		CRRI_GUIView::OnBnClickedButton103()
{
	///___________________________________________
	// 入力チェック
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (!DSET.set) { RETURN("** ERROR ** Cannot define project......"); }
	if (CEX == UNDEF) { RETURN("** Error ** Select external DEM data......"); }
	if (RIVnum <= 0) { RETURN("** Error ** Select river grid cell......"); }

	// cccccccccccccccccccccccccc
	Change_Cursor(&Gp, IDC_WAIT);
	///___________________________________________
	//  PROC_INDICATE_RIVMESH  モードでは流域表示
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(STAT(PROC_INDICATE_RIVMESH)) {
		Histcnt = 0;
		//
		Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, mark);
		Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, EXmark);
		Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, AllDir);
		mark = Make_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Htotal, PM.EXDATA[CEX].Files[EX_DIR].Vtotal, (BYTE)0);
		EXmark = Make_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Htotal, PM.EXDATA[CEX].Files[EX_DIR].Vtotal, (BYTE)0);
		AllDir = Make_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Htotal, PM.EXDATA[CEX].Files[EX_DIR].Vtotal, (char)0);
		// STAT
		STAT(PROC_INDICATE_RIVMESH) = FALSE;
		STAT(PROC_DISPLAY_MESH) = TRUE;
		//
		Display_Basin();
		GLobj_Delete(&Gp, OBJID_WORK);

		Disp_Controls();
	}
	///____________________________________________________________
	//  PROC_DISPLAY_MESH  流域確定モードではメッシュモデルの作成
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	else if(STAT(PROC_DISPLAY_MESH)) {
		// STAT
		STAT(PROC_INDICATE_RIVMESH) = FALSE;
		STAT(PROC_DISPLAY_MESH) = FALSE;
		STAT(PROC_CONFIRM_MESH) = TRUE;
		//
		Change_Cursor(&Gp, IDC_WAIT);
		Set_MESH_MODEL();	
		//
		// 20190201 Start
		if (PM.B_UseJFlow) {
			Read_J_Flw();	// dem acc,dir の読み込み
		}
		else {
			Read_HYDROSHEDS();	// dem acc,dir の読み込み
		}
		// 20190201 End
		DSET.in_avail[ADEM_FILE] = DSET.in_avail[ACC_FILE] = DSET.in_avail[ADIR_FILE] = TRUE;
		//
		Write_Data_File(ADEM_FILE, File_Format[ADEM_FILE], File_Order[ADEM_FILE], DSET, PM, MESH);
		Write_Data_File(ACC_FILE, File_Format[ACC_FILE], File_Order[ACC_FILE], DSET, PM, MESH);
		Write_Data_File(ADIR_FILE, File_Format[ADIR_FILE], File_Order[ADIR_FILE], DSET, PM, MESH);
		//
		GLobj_Delete(&Gp, OBJID_GUIDE);
		GLobj_Delete(&Gp, OBJID_AREA);
		GLobj_Delete(&Gp, OBJID_MESH);
		GLobj_Delete(&Gp, OBJID_WORK);
		///
		//  1セル当たりの面積を計算   PM.Unit_Area
		Calc_Unit_Area();
		///
		// MESHとLINEを作成
		CDATA = ACC_FILE;
		Make_Mesh_Model();
		Make_Mesh_Area();
		//
		Make_Mesh_Line();		// 作っておくが、ON_Timer で最初は消しておく。
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		///
		// TEX リソースの解放		ガイドＡＣＣ画像の破棄
		if (Gp.Texnum > 0) {
			for (int i = 1; i < Gp.Texnum+1; i++)  {
				SAFE_FREE(Gp.Tex[i].image);
			}
			Gp.Texmem = GUIDE_TEXTURE + 5;
			Gp.Texnum = 1;
		}
		if (PM.B_LatLng)  Make_Back_Image();	// リソース解放後に作成
		//
		PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
		PM.set = TRUE;		// Add 2015/12
		//
		GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);

		//
		Disp_Controls();
		CWnd*	cw = GetDlgItem(ID_PICT);
		cw->SetFocus();
	}
	Change_Cursor(&Gp, IDC_ARROW);
	//
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  流域の表示
void		CRRI_GUIView::Display_Basin()
{
	///___________________________________________
	//  範囲の抽出
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int				px, py;
	long				cur;
	double			lat, lng, X, Y;
	///
	//
	if (!PM.B_UseJFlow) {
		Read_AllDir();	/// ＤＩＲ　の全体読み込み
	}
	//
	::SetCurrentDirectory(m_BootPath);
	//
	AreaYmin = AreaXmin = -UNDEF;
	AreaYmax = AreaXmax = UNDEF;
	//
	MeshCnt = 0;

	for (int r = 0; r < RIVnum; r++){
		px = (int)RIVinfo[r].x;			// ※　修正位置
		py = (int)RIVinfo[r].y;
		if (PM.B_UseJFlow)
		{
			//Get_Recursive_Area_J_Flw(RIVinfo[r].lng, RIVinfo[r].lat, px, py, mark);
			Get_J_Flw_Area_Hight_Perf(RIVinfo[r].lng, RIVinfo[r].lat, px, py, mark);
		}
		else
		{
			Get_Recursive_Area(px, py, mark);
		}
	}
	///
	//  メッシュ範囲の表示
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AreaXmax += 1;
	AreaYmax += 1;
	AreaXmin -= MESH_MARGIN;
	AreaYmin -= MESH_MARGIN;
	AreaXmax += MESH_MARGIN;
	AreaYmax += MESH_MARGIN;

	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmin, (double)AreaYmin, &PM.stLNG, &PM.stLAT);
	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmax, (double)AreaYmax, &PM.endLNG, &PM.endLAT);
	PM.MHnum = (int)(AreaXmax - AreaXmin);
	PM.MVnum = (int)(AreaYmax - AreaYmin);
	///
	// 画面への表示
	Set_RectArea();
	//
	Make_Mesh_Area();		// OBJID_AREA に表示
	///
	//  OBJID_MESH に作成
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Make_Mesh_Model_Init(F_COLOR(255,0,0), 0.5);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
	//
	RETURN("Render grid cells...");

}
void 	CRRI_GUIView::Read_AllDir()
{
	int				fi,TH, TV;
	char			val[2];
	//
	// DEM,ACC,DIR でループ読み込み
	//
	::SetCurrentDirectory(m_BootPath);
	//
	if ((fi = _open(PM.EXDATA[CEX].Files[EX_DIR].fname, _O_RDONLY | _O_BINARY, _S_IREAD)) == -1) return;
	TH = PM.EXDATA[CEX].Files[EX_DIR].Htotal;
	TV = PM.EXDATA[CEX].Files[EX_DIR].Vtotal;
	// 
	for (int v = 0; v < TV; v++) {
		_read(fi, AllDir[TV - v - 1], TH);
	}
	_close(fi);
	//
	return;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  除外流域の計算
void		CRRI_GUIView::Exclude_Basin()
{
	if (!RivEX) return;
	//
	int				px, py;
	double			lat, lng, X, Y;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	//Trans_COORD_LATLNG(EX_ACC, RivEXpos.x, RivEXpos.y, &lng, &lat);  // 注意 ｘ、ｙは中央０．５の位置
	//Trans_LATLNG_COORD(EX_DIR, lng, lat, &X, &Y);
	px = (int)RivEXpos.x;
	py = (int)RivEXpos.y;
	Get_Recursive_Area(px, py, EXmark);
	//
	AreaYmin = AreaXmin = -UNDEF;
	AreaYmax = AreaXmax = UNDEF;
	//
	MeshCnt = 0;
	for (int v = 0; v < PM.EXDATA[CEX].Files[EX_DIR].Vtotal; v++) {
		for (int h = 0; h < PM.EXDATA[CEX].Files[EX_DIR].Htotal; h++) {
			if (!mark[v][h]) continue;
			else {
				if (EXmark[v][h]) mark[v][h] = FALSE;
				else {
					if (AreaXmin > h) AreaXmin = h;
					if (AreaYmin > v) AreaYmin = v;
					if (AreaXmax < h) AreaXmax = h;
					if (AreaYmax < v) AreaYmax = v;
				}
			}
		}
	}
	AreaXmax++;
	AreaYmax++;
	//
	AreaXmin -= MESH_MARGIN;
	AreaYmin -= MESH_MARGIN;
	AreaXmax += MESH_MARGIN;
	AreaYmax += MESH_MARGIN;
	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmin, (double)AreaYmin, &PM.stLNG, &PM.stLAT);
	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmax, (double)AreaYmax, &PM.endLNG, &PM.endLAT);
	PM.MHnum = (int)(AreaXmax - AreaXmin) ;
	PM.MVnum = (int)(AreaYmax - AreaYmin);
	//
	// 画面への表示
	Set_RectArea();
	//
	Make_Mesh_Area();		/// OBJID_FRAME に表示
	//
	Make_Mesh_Model_Init(F_COLOR(255, 0, 0), 0.5);
	//
	GLobj_Delete(&Gp, OBJID_WORK);	// 青色ポイントの消去
	RivEX = FALSE;
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
}
/// 領域の再帰的検索
void 	CRRI_GUIView::Get_Recursive_Area(int px, int py, BYTE** mark)
{
	int		dir;
	mark[py][px] = ON; 
	MeshCnt++;
	Histcnt++;
	if (py < AreaYmin)	AreaYmin = py;
	if (py > AreaYmax)	AreaYmax = py;
	if (px < AreaXmin)	AreaXmin = px;
	if (px > AreaXmax)	AreaXmax = px;

	for (int i = 0; i < 8; i++){
		if ((dir = (int)AllDir[py + offy[i]][px + offx[i]]) == -9) continue;
		if (dir == -128) dir = 128;
		if (mark[py + offy[i]][px + offx[i]] != ON && dir == direct[i]) {
			Get_Recursive_Area(px + offx[i], py + offy[i], mark);
		}
	}
}

void 	CRRI_GUIView::Get_J_Flw_Area_Hight_Perf(double lng, double lat, int px, int py, BYTE** mark)
{
	int		dir;
	double locLng, locLat;
	int loopCount = 1;
	std::map<CString, JFlowCache> mapCache;
	GDALAllRegister();
	CString	path, fname, key;
	path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\dir\\", m_BootPath);

	struct TargetLocation {
		double targetLng, targetlat;
		int targetX, targetY;
	};
	std::list<TargetLocation> targetList = {{lng,lat,px,py}};
	for (std::list<TargetLocation>::iterator iter = targetList.begin(); iter != targetList.end(); iter++)
	{
		mark[iter->targetY][iter->targetX] = ON;
		MeshCnt++;
		Histcnt++;
		if (iter->targetY < AreaYmin)	AreaYmin = iter->targetY;
		if (iter->targetY > AreaYmax)	AreaYmax = iter->targetY;
		if (iter->targetX < AreaXmin)	AreaXmin = iter->targetX;
		if (iter->targetX > AreaXmax)	AreaXmax = iter->targetX;
		for (int i = 0; i < 8; i++) {
			locLng = iter->targetLng + offx_jflw[i];
			locLat = iter->targetlat + offy_jflw[i];
			std::map<CString, JFlowCache>::iterator l_it;
			key.Format("%d,%d", (int)locLng, (int)locLat);
			l_it = mapCache.find(key);
			if (l_it == mapCache.end()) {
				fname.Format("%sn%2de%3d_dir.tif", path, (int)locLat, (int)locLng);
				JFlowCache areaCache;
				Create_J_Flw_Cache(fname, &areaCache);
				mapCache.insert(std::pair<CString, JFlowCache>(key, areaCache));
			}

			dir = Get_J_Flw_Value_From_Cache(locLng, locLat, &mapCache.find(key)->second);

			if (dir == -9) continue;
			if (dir == -128) dir = 128;
			if (mark[iter->targetY + offy[i]][iter->targetX + offx[i]] != ON && dir == direct[i]) {
				targetList.push_back({ locLng, locLat,iter->targetX + offx[i] ,iter->targetY + offy[i] });
			}
		}
	}

	for (std::map<CString, JFlowCache>::iterator mapIter = mapCache.begin(); mapIter != mapCache.end(); mapIter++) {
		CPLFree(mapIter->second.datas);
	};

	GDALDestroyDriverManager();
}

/// 領域の再帰的検索
void 	CRRI_GUIView::Get_Recursive_Area_J_Flw(double lng, double lat, int px, int py, BYTE** mark)
{
	int		dir;

	double locLng, locLat;

	mark[py][px] = ON;

	MeshCnt++;
	Histcnt++;
	if (py < AreaYmin)	AreaYmin = py;
	if (py > AreaYmax)	AreaYmax = py;
	if (px < AreaXmin)	AreaXmin = px;
	if (px > AreaXmax)	AreaXmax = px;

	CString	path, fname;
	path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\dir\\", m_BootPath);
	for (int i = 0; i < 8; i++) {
		
		locLng = lng + offx_jflw[i];
		locLat = lat + offy_jflw[i];
		
		fname.Format("%sn%2de%3d_dir.tif", path, (int)locLat, (int)locLng);

		dir = Get_J_Flw_Value(fname, locLng, locLat);
		
		if (dir == -9) continue;
		if (dir == -128) dir = 128;
		if (mark[py + offy[i]][px + offx[i]] != ON && dir == direct[i]) {
				Get_Recursive_Area_J_Flw(locLng, locLat, px + offx[i], py + offy[i], mark);
		}
	}
	int b;
	b = 1;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  選択領域のクリヤー
void		CRRI_GUIView::OnBnClickedButton111() // Delete
{
	IFNOT_STAT(PROC_DISPLAY_MESH) return;
	// cccccccccccccccccccccccccc
	//
	Change_Cursor(&Gp, IDC_WAIT);
	COMMENT("Delete river basin");
	//
	GLobj_Delete(&Gp, OBJID_MESH);
	GLobj_Delete(&Gp, OBJID_AREA);
	GLobj_Delete(&Gp, OBJID_WORK);		// メッシュポイント
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	//
	STAT(PROC_INDICATE_RIVMESH) = TRUE;
	STAT(PROC_DISPLAY_MESH) = FALSE;
	Disp_Controls();
	Clear_RectArea();
	//
	RIVnum = 0;
	// cccccccccccccccccccccccccc
	Change_Cursor(&Gp, IDC_ARROW);
	COMMENT("");
	//
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MESH メモリーの確保
int 		CRRI_GUIView::Set_MESH_MODEL()
{
	//  メッシュ範囲のアロケートとデータ読み込み
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmin, (double)AreaYmin, &PM.stLNG, &PM.stLAT);
	Trans_COORD_LATLNG(EX_DIR, (double)AreaXmax, (double)AreaYmax, &PM.endLNG, &PM.endLAT);
	PM.MHnum = (int)(AreaXmax - AreaXmin);
	PM.MVnum = (int)(AreaYmax - AreaYmin);
	//
	if ((MESH = (MINFO**)malloc(PM.MVnum*sizeof(void*))) == NULL) {
		Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, mark);
		Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, EXmark);
		COMMENT("** Error ** Cannot allocate memory"); return -1;
	}
	for (int v = 0; v < PM.MVnum; v++) {
		if ((MESH[v] = (MINFO*)malloc(PM.MHnum*sizeof(MINFO))) == NULL) {
			v--;
			while (v >= 0) free(MESH[v--]); free(MESH);
			Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, mark);
			Free_Matrix(PM.EXDATA[CEX].Files[EX_DIR].Vtotal, EXmark);
			COMMENT("** Error ** Cannot allocate memory"); return -1;
		}
		for (int h = 0; h<PM.MHnum; h++) memset(&MESH[v][h], 0, sizeof(MINFO));
	}
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  HYDROSHEDS　から　DEM ACC　ADIR の読み込み
int		CRRI_GUIView::Read_HYDROSHEDS()
{
	int				fex;
	long				jump;
	int				ival, byte, ret;
	int				XVpos, XHpos, cnt;			// 外部データの参照位置
	int				markH, markV;
	double			dval,Size;
	char				val[5];
	//
	// DEM,ACC,DIR でループ読み込み
	//
	::SetCurrentDirectory(m_BootPath);
	for (int i = 0; i < 3; i++) {
		Size = 1. / PM.EXDATA[CEX].Files[i].subdev;
		XHpos = (int)((PM.stLNG - PM.EXDATA[CEX].Files[i].stlng) * PM.EXDATA[CEX].Files[i].subdev);
//		XHpos++;
		XVpos = (int)((PM.EXDATA[CEX].Files[i].Highlat - PM.endLAT)* PM.EXDATA[CEX].Files[i].subdev);
//		XVpos++;
		//
		if ((fex = _open(PM.EXDATA[CEX].Files[i].fname, _O_RDONLY | _O_BINARY, _S_IREAD)) == -1) return -1;
		//
		byte = PM.EXDATA[CEX].Files[i].byte;
		//
		// データ頭出し　　読み飛ばし分		左上からデータが入っている。
		jump = (long)((XVpos*PM.EXDATA[CEX].Files[i].Htotal)*byte);
		_lseek(fex, jump, SEEK_SET);
		//
		for (int v = 0; v < PM.MVnum; v++) {
			if (v == 0)		jump = XHpos*byte;
			else				jump = (PM.EXDATA[CEX].Files[i].Htotal - PM.MHnum)*byte;
			_lseek(fex, jump, SEEK_CUR);		// 現在位置から
			for (int h = 0; h < PM.MHnum; h++) {
				memset(val, 0x0, 5); read(fex, val, byte);
				if (i == 0)			{
					dval = (double)(*(short*)val);
					MESH[PM.MVnum - v - 1][h].Adem = dval;
				}
				else if (i == 1)	{
					dval = (double)(*(int*)val);
					MESH[PM.MVnum - v - 1][h].Acc = dval;
				}
				else if (i == 2)	{				// メッシュの有効無効は　MARKで決定する markはDIRで作成
					ival = (int)(*(char*)val);
					MESH[PM.MVnum - v - 1][h].Adir = ival;
					// 
					markH = XHpos + h;
					markV = PM.EXDATA[CEX].Files[EX_DIR].Vtotal - XVpos - v - 1;
					if (mark[markV][markH] == FLAG_ON) {
						if (MESH[PM.MVnum - v - 1][h].Adem == -9999.)        MESH[PM.MVnum - v - 1][h].flag = 0;
						else if (MESH[PM.MVnum - v - 1][h].Acc > DSET.Riv_Thresh && DSET.Riv_Avail) 
											MESH[PM.MVnum - v - 1][h].flag = ID_MESH_R;
						else                MESH[PM.MVnum - v - 1][h].flag = ID_MESH;                             
					}
					else                            MESH[PM.MVnum - v - 1][h].flag = 0;
				}
			}
			//  -128 の反転
			if (i == EX_DIR){
				for (int h = 0; h < PM.MHnum; h++) {
					if (MESH[PM.MVnum - v - 1][h].Adir == -128) MESH[PM.MVnum - v - 1][h].Adir = (short)128;
				}
			}
		}
		_close(fex);
	}
///
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Japan Flow Direction MAP　から　DEM ACC　ADIR の読み込み
int		CRRI_GUIView::Read_J_Flw()
{
	CString	path;
	CString	fname;
	double	lat;
	double	lng;
	CString	type[] = { "elv", "upg", "dir" };
	int	v = 0;
	int	h = 0;
	int				XVpos, XHpos, cnt;			// 外部データの参照位置
	int				markH = 0, markV = 0;
	//
	// DEM,ACC,DIR でループ読み込み
	//
	::SetCurrentDirectory(m_BootPath);
	CString key;
	std::map<CString, JFlowCache> mapCache;
	GDALAllRegister();
	for (int i = 0; i < 3; i++) {
		lat = PM.endLAT;
		lng = PM.stLNG;

		h = 0;
		v = 0;

		XHpos = (int)((PM.stLNG + (MESH_LATLNG_WIDTH_5S / 2) - PM.EXDATA[CEX].Files[i].stlng) * PM.EXDATA[CEX].Files[i].subdev);

		XVpos = (int)((PM.EXDATA[CEX].Files[i].Highlat + (MESH_LATLNG_WIDTH_5S / 2) - PM.endLAT)* PM.EXDATA[CEX].Files[i].subdev);

		while (lng < PM.endLNG)
		{
			if (h + 1 > PM.MHnum)
			{
				break;
			}
			while (lat > PM.stLAT)
			{
				if (v + 1 > PM.MVnum)
				{
					break;
				}

				std::map<CString, JFlowCache>::iterator l_it;
				key.Format("%s,%d,%d", type[i],(int)lng, (int)lat);
				l_it = mapCache.find(key);
				if (l_it == mapCache.end()) {
					path.Format("%s\\RRI_CONTENTS\\J_FlwDir\\%s\\", m_BootPath, type[i]);
					fname.Format("%sn%2de%3d_%s.tif", path, (int)lat, (int)lng, type[i]);
					JFlowCache areaCache;
					Create_J_Flw_Cache(fname, &areaCache);
					mapCache.insert(std::pair<CString, JFlowCache>(key, areaCache));
				}
				
				if (i == 0) {
					MESH[PM.MVnum - v - 1][h].Adem = Get_J_Flw_Value_From_Cache(lng, lat, &mapCache.find(key)->second);
					MESH[PM.MVnum - v - 1][h].AtLng = lng;
					MESH[PM.MVnum - v - 1][h].AtLat = lat;
				}
				else if (i == 1) {
					MESH[PM.MVnum - v - 1][h].Acc = Get_J_Flw_Value_From_Cache(lng, lat, &mapCache.find(key)->second);
				}
				else if (i == 2) {				// メッシュの有効無効は　MARKで決定する markはDIRで作成
					MESH[PM.MVnum - v - 1][h].Adir = Get_J_Flw_Value_From_Cache(lng, lat, &mapCache.find(key)->second);

					if (MESH[PM.MVnum - v - 1][h].Adir == -128) {
						MESH[PM.MVnum - v - 1][h].Adir = 128;
					}

					markH = XHpos + h;
					markV = PM.EXDATA[CEX].Files[EX_DIR].Vtotal - XVpos - v - 1;
					if (mark[markV][markH] == FLAG_ON) {
						if (MESH[PM.MVnum - v - 1][h].Adem == -9999.) {
							MESH[PM.MVnum - v - 1][h].flag = 0;
						}
						else if (MESH[PM.MVnum - v - 1][h].Acc > DSET.Riv_Thresh && DSET.Riv_Avail) {
							MESH[PM.MVnum - v - 1][h].flag = ID_MESH_R;
						}
						else {
							MESH[PM.MVnum - v - 1][h].flag = ID_MESH;
						}
					}
					else {
						MESH[PM.MVnum - v - 1][h].flag = 0;
					}

				}

				lat -= MESH_LATLNG_WIDTH_5S;
				v++;

			}

			lat = PM.endLAT;
			lng += MESH_LATLNG_WIDTH_5S;
			h++;
			v = 0;
		}
	}

	for (std::map<CString, JFlowCache>::iterator mapIter = mapCache.begin(); mapIter != mapCache.end(); mapIter++) {
		CPLFree(mapIter->second.datas);
	};
	GDALDestroyDriverManager();
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  矩形範囲の表示
int		CRRI_GUIView::Make_Mesh_Area()
{
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_AREA];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_AREA);
	//
	GLobj_Init(Mobj, 4, 5);
	//
	int no[4], id, pno;
	//
	IF_STAT(PROC_DISPLAY_MESH)  {
		// VERT
		no[0] = GLobj_Add_Vert(Mobj, AreaXmin, AreaYmin, 5., FALSE);
		no[1] = GLobj_Add_Vert(Mobj, AreaXmax, AreaYmin, 5., FALSE);
		no[2] = GLobj_Add_Vert(Mobj, AreaXmax, AreaYmax, 5., FALSE);
		no[3] = GLobj_Add_Vert(Mobj, AreaXmin, AreaYmax, 5., FALSE);
		///
		// Line
		pno = GLobj_Add_Poly(Mobj, 4, no, GL_LINE_LOOP, 2.f, F_COLOR(128, 0, 128));
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//
		PM.Xmin = AreaXmin;
		PM.Xmax = AreaXmax;
		PM.Ymin = AreaYmin;
		PM.Ymax = AreaYmax;
	}
	else {
		double dX, dY;
		if (PM.B_LatLng) {
			dX = (PM.endLNG - PM.stLNG)*PM.Coord_Unit;
			dY = (PM.endLAT - PM.stLAT)*PM.Coord_Unit;
		}
		else {
			dX = (PM.endUTM_X - PM.stUTM_X)*PM.Coord_Unit;
			dY = (PM.endUTM_Y - PM.stUTM_Y)*PM.Coord_Unit;
		}
		no[0] = GLobj_Add_Vert(Mobj, 0., 0., BOUNDARY_Z, FALSE);
		no[1] = GLobj_Add_Vert(Mobj, dX, 0., BOUNDARY_Z, FALSE);
		no[2] = GLobj_Add_Vert(Mobj, dX, dY, BOUNDARY_Z, FALSE);
		no[3] = GLobj_Add_Vert(Mobj, 0., dY, BOUNDARY_Z, FALSE);
		// Line
		pno = GLobj_Add_Poly(Mobj, 4, no, GL_LINE_LOOP, 2.f, 
			F_COLOR(GetRValue(PM.Col_Frame), GetGValue(PM.Col_Frame), GetBValue(PM.Col_Frame)));
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_AREA, TRUE);
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  矩形範囲の変更
int 		CRRI_GUIView::Change_Area()
{
	Get_RectArea();		// stLAT,stLNG etc
	double	CX, CY;
	CRect	TArea;

	Trans_LATLNG_COORD(EX_DIR, PM.stLNG, PM.stLAT, &CX, &CY);
	AreaXmin = (int)CX;
	AreaYmin = (int)CY;

	Trans_LATLNG_COORD(EX_DIR, PM.endLNG, PM.endLAT, &CX, &CY);
	AreaXmax = (int)CX;
	AreaYmax = (int)CY;
	//
	TArea.left = Imin(AreaXmin, BXmin);
	TArea.right = Imax(AreaXmax, BXmax);
	TArea.top = Imax(AreaYmax, BYmax);
	TArea.bottom = Imin(AreaYmin, BYmin);
	//
	int cnt = 0;
	for (int v = TArea.bottom; v <= TArea.top; v++) {		// 範囲外を消すだけ
		for (int h = TArea.left; h <= TArea.right; h++) {
			if (mark[v][h] == FLAG_ON) {
				//if ((v >= AreaYmin && v <= AreaYmax) && (h >= AreaXmin && h <= AreaXmax)) continue;
				//else    { mark[v][h] = FLAG_OFF; cnt++; continue; }
				if ((v >= AreaYmin && v < AreaYmax) && (h >= AreaXmin && h < AreaXmax)) continue;
				else    { mark[v][h] = FLAG_OFF; cnt++; continue; }
			}
		}
	}
	if (cnt) {
		Make_Mesh_Model_Init(F_COLOR(255, 0, 0), 0.5);
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
	}
	//
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_AREA];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_AREA);
	//
	GLobj_Init(Mobj, 4, 5);
	//
	int no[4], id, pno;
	// VERT
	no[0] = GLobj_Add_Vert(Mobj, AreaXmin, AreaYmin, 5., FALSE);
	no[1] = GLobj_Add_Vert(Mobj, AreaXmax, AreaYmin, 5., FALSE);
	no[2] = GLobj_Add_Vert(Mobj, AreaXmax, AreaYmax, 5., FALSE);
	no[3] = GLobj_Add_Vert(Mobj, AreaXmin, AreaYmax, 5., FALSE);
	//
	// Line
	pno = GLobj_Add_Poly(Mobj, 4, no, GL_LINE_LOOP, 2.f, F_COLOR(128, 0, 128));
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_AREA, TRUE);
	//	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	PM.MHnum = AreaXmax - AreaXmin;
	PM.MVnum = AreaYmax - AreaYmin;
	PM.Xmin = AreaXmin;
	PM.Xmax = AreaXmax;
	PM.Ymin = AreaYmin;
	PM.Ymax = AreaYmax;
	//
	Cnt_CArea = 0;
	Disp_Controls();
	//
	return 0;
}
// メッシュの追加
void		CRRI_GUIView::OnBnClickedButton112()	
{
	STAT(KEY_CTRL_DOWN) = FALSE;
	STAT(KEY_SHIFT_DOWN) = FALSE;

	STAT(AREA_DECIDE_MODE) = TRUE;
	STAT(ADD_MESH_MODE) = TRUE;
	//
	if (Free_Area != NULL) SAFE_FREE(Free_Area);
	Famem = 200; Fanum = 0;
	if ((Free_Area = (XYCOORD*)malloc(Famem*sizeof(XYCOORD))) == NULL) {
		RETURN("** Error ** Cannot allocate free area memory");
	}
	//
	Change_Cursor(&Gp, IDC_CROSS);
	RETURN("Add cells mode: specify the area to be added -> Left mouse drag .  ESC:Cancel");
}
void		CRRI_GUIView::OnBnClickedButton113()
{
	STAT(KEY_CTRL_DOWN) = FALSE;
	STAT(KEY_SHIFT_DOWN) = FALSE;

	STAT(AREA_DECIDE_MODE) = TRUE;
	STAT(DEL_MESH_MODE) = TRUE;
	//
	if (Free_Area != NULL) SAFE_FREE(Free_Area);
	Famem = 200; Fanum = 0;
	if ((Free_Area = (XYCOORD*)malloc(Famem*sizeof(XYCOORD))) == NULL) {
		RETURN("** Error ** Cannot allocate free area memory");
	}
	//
	Change_Cursor(&Gp, IDC_CROSS);
	RETURN("Delete cells mode: specify the area to be deleted -> Left mouse drag .  ESC:Cancel");
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DRAW MESH & LINE
int		CRRI_GUIView::Make_Mesh_Model_Init(FCOLOR DefaultCol,double Alpha)
{
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_MESH];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_MESH);
	//
	GLobj_Init(Mobj, (PM.MHnum + 1)*(PM.MVnum + 1), PM.MHnum*PM.MVnum);
	//
	// VERT
	for (int v = PM.Ymin; v <= PM.Ymax; v++) {
		for (int h = PM.Xmin; h <= PM.Xmax; h++) {
			GLobj_Add_Vert(Mobj, (double)h, (double)v, MESH_Z, FALSE);
		}
	}
	//
	// Polygon
	int no[4], id, pno;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (mark[v + PM.Ymin][h + PM.Xmin] == ON) {
				id = v*(PM.Xmax - PM.Xmin + 1) + h;
				no[0] = id;
				no[1] = id + 1;
				no[2] = no[1] + (int)(PM.Xmax - PM.Xmin + 1);
				no[3] = no[2] - 1;
				//
				pno = GLobj_Add_Poly(Mobj, 4, no, GL_POLYGON, DefaultCol);
				Mobj->poly[pno].Alpha = (float)Alpha;
			}
		}
	}
	//
	return 0;
}
int		CRRI_GUIView::Make_Mesh_Line()
{
	if (!(STAT(PROC_CONFIRM_MESH) ))   return -1;
	//
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_LINE];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_LINE);
	//
	GLobj_Init(Mobj, (PM.MHnum + 1)*(PM.MVnum + 1), PM.MHnum*PM.MVnum);
	//
	// VERT
	for (int v = 0; v <= PM.MVnum; v++) {
		for (int h = 0; h <= PM.MHnum; h++) {
			GLobj_Add_Vert(Mobj, (double)h, (double)v, LINE_Z, FALSE);
		}
	}
	//
	// Polygon
	int no[4],	id, pno;
	FCOLOR		fcol;
	//
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;
			//
			id = v*(PM.MHnum + 1) + h;
			no[0] = id;
			no[1] = id + 1;
			no[2] = no[1] + (int)(PM.MHnum + 1);
			no[3] = no[2] - 1;
			//
			if (!STAT(EDIT_RIV_MODE)) {
				if (MESH[v][h].flag <= ID_MESH_DIV) {
					fcol = CREF_FCOL(PM.COL_MESH[(int)MESH[v][h].flag]);
				}
				else fcol = CREF_FCOL(PM.COL_MESH[9]); // HR もしくはＱＲが入っているかもしれない
			}
			else fcol = F_COLOR(200, 180, 90);
			//
			pno = GLobj_Add_Poly(Mobj,DIM_3D, 4, no, GL_LINE_LOOP,1.f,fcol);
			// offset
			if (MESH[v][h].flag == ID_MESH_R)		{
				Mobj->poly[pno].local.set = TRUE;
				Mobj->poly[pno].local.offz = RIVER_Z;
			}
			else if (MESH[v][h].flag > ID_MESH_R) {
				Mobj->poly[pno].local.set = TRUE;
				Mobj->poly[pno].local.offz = BOUNDARY_Z;
			}
		}
	}
	//
	return 0;
}
int		CRRI_GUIView::Make_Mesh_Model()
{
	if (CDATA == UNDEF) { COMMENT("Error:CDATA is UNDEF"); return -1; }
	//
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_MESH];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_MESH);
	//
	GLobj_Init(Mobj, (PM.MHnum + 1)*(PM.MVnum + 1), PM.MHnum*PM.MVnum);
	//
	// VERT
	for (int v = 0; v <= PM.MVnum; v++) {
		for (int h = 0; h <= PM.MHnum; h++) {
			GLobj_Add_Vert(Mobj, (double)h, (double)v, MESH_Z, FALSE);
		}
	}
	//
	// Polygon
	int			no[4], id, pno;
	FCOLOR		fcol, Gcol = F_COLOR(80, 80, 80);
	//
	PM.Dcol[CDATA].alpha = PM.Data_Alpha;
	//

	auto dataType = (CDATA == SED_FILE) ? ACC_FILE : CDATA;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;

			id = v*(PM.MHnum + 1) + h;
			no[0] = id;
			no[1] = id + 1;
			no[2] = no[1] + (int)(PM.MHnum + 1);
			no[3] = no[2] - 1;
			//
			if (Get_Data_Color(TRUE,v, h,0., &fcol, dataType)) {
				pno = GLobj_Add_Poly(Mobj, 4, no, GL_POLYGON, fcol);
				Mobj->poly[pno].Alpha = (float)PM.Data_Alpha;
			}
		}
	}
	//
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DISP MODEL for EDIT_DLG
int		CRRI_GUIView::Edit_Mesh_Model()		// EDITDLGからのコール
{
	if (CDATA == UNDEF) { COMMENT("Error:CDATA is UNDEF"); return -1; }
	//
	Change_Cursor(&Gp, IDC_WAIT);
	Gp.Gobj[OBJID_MESH].display = FALSE;		/// 元データを消す。
	//
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_EDIT];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_EDIT);
	//
	GLobj_Init(Mobj, (PM.MHnum + 1)*(PM.MVnum + 1), PM.MHnum*PM.MVnum);
	///
	// VERT
	for (int v = 0; v <= PM.MVnum; v++) {
		for (int h = 0; h <= PM.MHnum; h++) {
			GLobj_Add_Vert(Mobj, (double)h, (double)v, MESH_Z, FALSE);
		}
	}
	///
	// Polygon
	double		val;
	int no[4], id, pno;
	FCOLOR		fcol, Gcol = F_COLOR(80, 80, 80);
	//

	auto dataType = (CDATA == SED_FILE) ? ACC_FILE : CDATA;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;

			id = v*(PM.MHnum + 1) + h;
			no[0] = id;
			no[1] = id + 1;
			no[2] = no[1] + (int)(PM.MHnum + 1);
			no[3] = no[2] - 1;
			//
			auto val = (CDATA == SED_FILE) ? MESH[v][h].Acc : PM.Values[v][h];
			if (Get_Data_Color(FALSE,v, h, val, &fcol, dataType)) {
				pno = GLobj_Add_Poly(Mobj, 4, no, GL_POLYGON, fcol);
				Mobj->poly[pno].Alpha = (float)PM.Data_Alpha;
			}
		}
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_EDIT, TRUE);
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	//
	return 0;
}
int CRRI_GUIView::Make_Select_Pos()
{
	if (!(STAT(PROC_CONFIRM_MESH) || STAT(DEFINE_BASIN)) ) return -1;
	//
	int				no[4];
	double			x, y,v,h;
	GL_OBJECT*		obj = &Gp.Gobj[OBJID_SELECT];
	FCOLOR			Fcol;
	GLobj_Delete(&Gp, OBJID_SELECT);
	///
	// 河川追加
	double  Rect_Margin = 1.0;		// 
	Fcol = F_COLOR(220, 0, 0);
	for (int i = 0; i < SI.Num; i++) {		// 
		h = (double)SI.HV[i].x;
		v = (double)SI.HV[i].y;
		//
		no[0] = GLobj_Add_Vert(obj, (double)(h + 0.01), (double)(v + 0.01), SELECT_Z, FALSE);
		no[1] = GLobj_Add_Vert(obj, (double)(h + 0.99), (double)(v + 0.01), SELECT_Z, FALSE);
		no[2] = GLobj_Add_Vert(obj, (double)(h + 0.99), (double)(v + 0.99), SELECT_Z, FALSE);
		no[3] = GLobj_Add_Vert(obj, (double)(h + 0.01), (double)(v + 0.99), SELECT_Z, FALSE);
		//
		GLobj_Add_Poly(obj, DIM_3D, 4, no, GL_LINE_LOOP, 2.f, CREF_FCOL(COL_MAZENTA));
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SELECT, TRUE);
	//
	Disp_Controls();
	//
	return S_OK;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Draw Free Area                           for  Add, Delete MESH  Area
void		CRRI_GUIView::Draw_Free_Area(BOOL Circle)
{
	if (Fanum < 3) return;
	//
	int*			no = (int*)malloc(Fanum*sizeof(int));
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_MOUSE_BAND];
	GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
	//
	GLobj_Init(obj, Fanum + 5, 5);
	for (int i = 0; i < Fanum; i++) no[i] = GLobj_Add_Vert(obj, Free_Area[i].x, Free_Area[i].y, MOUSE_Z, FALSE);
	//
	FCOLOR	fcol;
	if (STAT(ADD_MESH_MODE)) fcol = F_COLOR(255, 0, 0);
	else                   fcol = F_COLOR(0, 0, 255);
	if(Circle)  GLobj_Add_Poly(obj, Fanum, no, GL_LINE_LOOP, fcol);
	else       GLobj_Add_Poly(obj, Fanum, no, GL_LINE_STRIP, fcol);
	free(no);
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MOUSE_BAND, TRUE);
}

void		CRRI_GUIView::Add_Mesh()
{
	if (Fanum < 3) return;
	//
	double		Axmin, Axmax, Aymin, Aymax;
	double		cx,cy;
	//
	Axmin = Aymin = -UNDEF;
	Axmax = Aymax = UNDEF;
	for (int p = 0; p < Fanum; p++) {
		if (Axmin > Free_Area[p].x) Axmin = Free_Area[p].x;
		if (Axmax < Free_Area[p].x) Axmax = Free_Area[p].x;
		if (Aymin > Free_Area[p].y) Aymin = Free_Area[p].y;
		if (Aymax < Free_Area[p].y) Aymax = Free_Area[p].y;
	}
	if (Axmin < 0 || Axmax > PM.EXDATA[CEX].Files[1].Htotal ||
		Aymin < 0 || Aymax > PM.EXDATA[CEX].Files[1].Vtotal) {
		Fanum = 0; return;
	}
	int			Sxmin, Sxmax, Symin, Symax;	// Search範囲
	Sxmin = (int)Fmin(Axmin, AreaXmin);		// 確実にエリア範囲の変更を反映していること
	Sxmax = (int)Fmax(Axmax, AreaXmax);
	Symin = (int)Fmin(Aymin, AreaYmin);
	Symax = (int)Fmax(Aymax, AreaYmax);
	//
	for (int v = Symin; v <= Symax; v++) {
		cy = v;
		for (int h = Sxmin; h <= Sxmax; h++){
			if (mark[v][h]) {		// 範囲外であれば取り消す
				if ((v >= PM.Ymin && v <= PM.Ymax) && (h >= PM.Xmin && h <= PM.Xmax)) continue;
				else     { mark[v][h] = FLAG_OFF; continue; }
			}
			if (AllDir[v][h] <= 0 && !PM.B_UseJFlow) {
				if (AllDir[v][h] != -128) continue;
			}
			cx = h;
			if (Is_InRegion(cx, cy, Fanum, Free_Area)) mark[v][h] = FLAG_ON;
		}
	}
	//
	Make_Mesh_Model_Init(F_COLOR(255, 0, 0), 0.5);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
//
}
void		CRRI_GUIView::Del_Mesh()
{
	if (Fanum < 3) return;
	//
	int			Axmin, Axmax, Aymin, Aymax;
	double		cx, cy;
	//
	Axmin = Aymin = -UNDEF;
	Axmax = Aymax = UNDEF;
	for (int p = 0; p < Fanum; p++) {
		if (Axmin >(int)Free_Area[p].x) Axmin = (int)Free_Area[p].x;
		if (Axmax < (int)Free_Area[p].x) Axmax = (int)Free_Area[p].x;
		if (Aymin >(int)Free_Area[p].y) Aymin = (int)Free_Area[p].y;
		if (Aymax < (int)Free_Area[p].y) Aymax = (int)Free_Area[p].y;
	}
	if (Axmin < PM.Xmin) Axmin = PM.Xmin;
	if (Axmax > PM.Xmax) Axmax = PM.Xmax;
	if (Aymin < PM.Ymin) Aymin = PM.Ymin;
	if (Aymax > PM.Ymax) Aymax = PM.Ymax;
	//
	for (int v = Aymin; v <= Aymax; v++) {
		cy = v + 0.5;
		for (int h = Axmin; h < Axmax; h++){
			if (mark[v][h] == FLAG_OFF) continue;
			cx = h + 0.5;
			if (Is_InRegion(cx, cy, Fanum, Free_Area))
				mark[v][h] = FLAG_OFF;
		}
	}
	//
	Make_Mesh_Model_Init(F_COLOR(255, 0, 0), 0.5);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DRAW BACK IMAGE
int		CRRI_GUIView::Make_Back_Image()		// 一度だけなのに注意
{
	PM.Back_stLat = (int)PM.stLAT;			// ※　注意　負の場合も考慮
	PM.Back_stLng = (int)PM.stLNG;
	PM.Back_endLat = (int)PM.endLAT;
	PM.Back_endLng = (int)PM.endLNG;
	//
	if (PM.stLAT < 0)		PM.Back_stLat--;		// 南半球対応
	if (PM.endLAT < 0)	PM.Back_endLat--;
	//
	if (PM.stLNG < 0)		PM.Back_stLng--;		// 西経対応
	if (PM.endLNG < 0)	PM.Back_endLng--;
	//
	PM.BVnum = PM.Back_endLat - PM.Back_stLat + 1;
	PM.BHnum = PM.Back_endLng - PM.Back_stLng + 1;
	//
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_BACK];
	GL_OBJECT*	Cobj = &Gp.Gobj[OBJID_COPYRIGHT];
	int			lat, lng, no[4];
	CString		Iname;
	double		Ex, Ey,Unit;		// 原点位置
	double		bx, by;
	FXYCOORD		uv[4];
	int			ResH, ResV, imbyte;
	BYTE*		pImage;
	//
	GLobj_Delete(&Gp, OBJID_BACK);
	GLobj_Init(obj, (PM.BVnum + 1)*(PM.BHnum + 1), PM.BVnum*PM.BHnum);
	//
	if (PM.stLNG >= 0.) Ex = -fmod(PM.stLNG, 1.)* PM.Coord_Unit;		// UTM の場合はここに来ない。
	else               Ex = -(PM.stLNG - PM.Back_stLng)*PM.Coord_Unit;
	//
	if (PM.stLAT >= 0.) Ey = -fmod(PM.stLAT, 1.)* PM.Coord_Unit;
	else                Ey = -(1. - fmod(fabs(PM.stLAT), 1.))* PM.Coord_Unit;
	//
	::SetCurrentDirectory(m_BootPath);
	PM.Back_TexNo = Make_Matrix(PM.BHnum, PM.BVnum, UNDEF);
	for (int v = 0; v < PM.BVnum; v++){
		lat = PM.Back_stLat + v;
		by = Ey + PM.Coord_Unit*v;
		for (int h = 0; h < PM.BHnum; h++) {
			lng = PM.Back_stLng + h;

			if (lat >= 0) {
				if (lng >= 0.) Iname.Format("%s\\N%02dE%03d.bmp", PM.IM_Folder, lat, lng);
				else         Iname.Format("%s\\N%02dW%03d.bmp", PM.IM_Folder, lat, abs(lng));
			}
			else   {
				if (lng >= 0.) Iname.Format("%s\\S%02dE%03d.bmp", PM.IM_Folder, -lat, lng);
				else          Iname.Format("%s\\S%02dW%03d.bmp", PM.IM_Folder, -lat, abs(lng));
			}
				//
			if (!File_Exist(Iname)) continue;
			//---------------------------------------------------------------------------
			PM.Back_TexNo[v][h] = GL_Set_Texture(&Gp, Iname, 3);
			//
			bx = Ex + PM.Coord_Unit*h;
			no[0] = GLobj_Add_Vert(obj, bx, by, BACK_Z, FALSE);
			no[1] = GLobj_Add_Vert(obj, bx + PM.Coord_Unit, by, BACK_Z, FALSE);
			uv[1].x = 1.; uv[1].y = 1.;
			uv[0].x = 0.; uv[0].y = 1.;
			no[2] = GLobj_Add_Vert(obj, bx + PM.Coord_Unit, by + PM.Coord_Unit, BACK_Z, FALSE);
			uv[2].x = 1.; uv[2].y = 0.;
			no[3] = GLobj_Add_Vert(obj, bx, by + PM.Coord_Unit, BACK_Z, FALSE);
			uv[3].x = 0.; uv[3].y = 0.;
			//
			GLobj_Add_Poly(obj, 4, no, GL_POLYGON, PM.Back_TexNo[v][h], uv);
		}
	}
	STAT(USE_OSM_IMAGE) = TRUE;
	GLobj_Delete(&Gp, OBJID_COPYRIGHT);
	GLobj_Init(Cobj, 10, 3);
	GLobj_Add_Text(&Gp, OBJID_COPYRIGHT, DIM_2D, "Map data (c) OpenStreetMap contributors",
		"Lucida Sans", FONT_BOLD, 18, 7,
		Gp.win.cWidth - 320., 12., -1., F_COLOR(125, 155, 200));

	::SetCurrentDirectory(m_RecentPath);
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  SELECT COLOR 
BOOL  CRRI_GUIView::Get_Data_Color(BOOL Dsel,int v, int h, double val,FCOLOR* Fcol, int dataType)
{
//	double	val;
	//
	auto curDataType = dataType >= 0 ? dataType : CDATA;
	if (curDataType < 0 || (curDataType < LAND_COVER && curDataType >= HS_WLEV_FILE)) return FALSE;
	if (Dsel) {
		if (!CopyDataFromMesh(curDataType, v, h, val, MESH, PM, 0.0)) return FALSE;
	}
//	if (val == NODATA) return FALSE;
	//
	*Fcol = F_COLOR(GetRValue(Dcolor[0]), GetGValue(Dcolor[0]), GetBValue(Dcolor[0]));
	//
	// LU_FILEの日本対応（LU_FILE_JPに一旦置き換え）
	if (curDataType == LU_FILE && PM.B_UseJFlow) {
		curDataType = LU_FILE_JP;
	}
	if (!(curDataType == LU_FILE && DSET.LUnum > 20)) {
		if (PM.Dcol[curDataType].Equal) {
			if (val < PM.Dcol[curDataType].val[0]) return FALSE;
		}
		else {
			if (val <= PM.Dcol[curDataType].val[0]) return FALSE;
		}
		//
		if (!RRI_Color_Picker(val, PM.Dcol[curDataType].Mos, PM.Dcol[curDataType].Equal,
			PM.Dcol[curDataType].num, PM.Dcol[curDataType].val, PM.Dcol[curDataType].Rcol, Fcol)) return FALSE;
	}
	else {
		*Fcol = F_COLOR(GetRValue(Dcolor[(int)val]), GetGValue(Dcolor[(int)val]), GetBValue(Dcolor[(int)val]));
	}

	// LU_FILEの日本対応（LU_FILE_JPに一旦置き換えたものを基に戻す）
	//if (CDATA == LU_FILE_JP && PM.B_UseJFlow) {
	//	CDATA = LU_FILE;
	//}

	return TRUE;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RRI 用カラーピッカー
BOOL  CRRI_GUIView::RRI_Color_Picker(double value, BOOL Mosaic, BOOL Equal, int num, double* vm, COLORREF* col, FCOLOR* Fcol)
{
	double	span, R, G, B;
	BOOL	ex;
	//
	if (value < vm[0]) return FALSE;
	if (value == vm[0]) {
		if (Equal) {
			*Fcol = F_COLOR(GetRValue(col[0]), GetGValue(col[0]), GetBValue(col[0]));
			return TRUE;
		}
		else		return FALSE;
	}
	else if (value > vm[num - 1]) {
		*Fcol = F_COLOR(GetRValue(col[num - 1]), GetGValue(col[num - 1]), GetBValue(col[num - 1]));
		return TRUE;
	}
	else if (value == vm[num - 1]) {
		if (Equal) *Fcol = F_COLOR(GetRValue(col[num - 1]), GetGValue(col[num - 1]), GetBValue(col[num - 1]));
		else	*Fcol = F_COLOR(GetRValue(col[num - 2]), GetGValue(col[num - 2]), GetBValue(col[num - 2]));
		return TRUE;
	}
	//
	for (int i = 1; i<num; i++) {
		ex = FALSE;
		if (Equal) { if (value >= vm[i - 1] && value < vm[i]) ex = TRUE; }
		else		 { if (value > vm[i - 1] && value <= vm[i]) ex = TRUE; }
		if (ex) {
			if (Mosaic) *Fcol = F_COLOR(GetRValue(col[i - 1]), GetGValue(col[i - 1]), GetBValue(col[i - 1]));
			else {
				if (value < vm[1]) *Fcol = F_COLOR(GetRValue(col[0]), GetGValue(col[0]), GetBValue(col[0]));
				else {
					span = (vm[i] - vm[i - 1]);
					R = (double)(GetRValue(col[i - 1]) - GetRValue(col[i - 2]))*(value - vm[i - 1]) / span + GetRValue(col[i - 2]);
					G = (double)(GetGValue(col[i - 1]) - GetGValue(col[i - 2]))*(value - vm[i - 1]) / span + GetGValue(col[i - 2]);
					B = (double)(GetBValue(col[i - 1]) - GetBValue(col[i - 2]))*(value - vm[i - 1]) / span + GetBValue(col[i - 2]);
					*Fcol = F_COLOR(R, G, B);
				}
			}
		}
	}
	return TRUE;
}
///========================================================================
// 土研プログラム  　RESIZE
///========================================================================
void CRRI_GUIView::OnBnClickedButton104()
{
	int			cnt = 0;
	CString		sfiles, ss,str;
	sfiles = _T("");
	for (int i = LU_FILE; i <= LOCATION_FILE; i++) {
		if (i == POTENT_FILE)continue;
		if (DSET.in_avail[i]) {
			ss = "[  " + File_Title[i] + " File  ] \n";
			sfiles += ss; cnt++;
		}
	}
	if (cnt != 0) {
		if(cnt > 1 ) ss.Format("Following %d files will be cleared...OK ?\n", cnt);
		else        ss.Format("Following file will be cleared...OK ?\n");
		str = ss + sfiles;
		if (MessageBox(str, "warning", MB_YESNO | MB_ICONQUESTION) == IDNO) return;
	}
	//
	for (int i = LU_FILE; i <= LOCATION_FILE; i++) {
		if (i == POTENT_FILE)continue;
		DSET.in_use[i] = DSET.in_avail[i] = FALSE;
	}
	///____________________________________________________________________
	CMagDlg	MD;
	//
	Write_Data_File(ADEM_FILE, File_Format[ADEM_FILE], File_Order[ADEM_FILE], DSET,PM,MESH);
	Write_Data_File(ACC_FILE, File_Format[ACC_FILE], File_Order[ACC_FILE], DSET, PM, MESH);
	Write_Data_File(ADIR_FILE, File_Format[ADIR_FILE], File_Order[ADIR_FILE], DSET, PM, MESH);
	//
	if (!B_UndoFirstSave) Save_Undo_File();		// UNDO 用ファイルの保存　B_UndoFirstSaveは中で変更
	//
	MD.kind = 0;		// ダイアログを使いまわすため、拡大の設定であることを示す。
	if (MD.DoModal()== IDCANCEL) return;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	PM.Coord_Unit /= (int)MD.Mag;
	strcpy(DSET.File_names[ADEM_FILE],MD.DemF);
	strcpy(DSET.File_names[ACC_FILE], MD.AccF);
	strcpy(DSET.File_names[ADIR_FILE], MD.AdirF);
	//
	// Free MESH
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Change_Cursor(&Gp, IDC_WAIT);
	if (MESH != NULL) {
		for (int i = 0; i < PM.MVnum; i++) SAFE_FREE(MESH[i]);
		SAFE_FREE(MESH);
	}
	if (PM.Values != 0)	Free_Matrix(PM.MVnum, PM.Values);


	if (FAILED(Read_3_Files(TRUE))) { Change_Cursor(&Gp, IDC_ARROW); RETURN("** Failed ** Cannot ｒead converted ｆiles ");}

	//reset lng lat
	double lat, lng;
	int h, v;

	lat = PM.endLAT;
	lng = PM.stLNG;

	h = 0;
	v = 0;

	while (lng < PM.endLNG)
	{
		if (h + 1 > PM.MHnum)
		{
			break;
		}
		while (lat > PM.stLAT)
		{
			if (v + 1 > PM.MVnum)
			{
				break;
			}

			MESH[PM.MVnum - v - 1][h].AtLng = lng;
			MESH[PM.MVnum - v - 1][h].AtLat = lat;

			lat -= PM.Size;
			v++;

		}

		lat = PM.endLAT;
		lng += PM.Size;
		h++;
		v = 0;
	}
	//
	PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
	//
	Calc_Unit_Area();
	//
	//Back Image
	if (Gp.Texnum > 0) {
		for (int i = 1; i < Gp.Texnum+1; i++)  {
			SAFE_FREE(Gp.Tex[i].image);
		}
		Gp.Texnum = 1;
	}


	if(PM.B_LatLng ) Make_Back_Image();						// リソース解放後に作成
	//
	Make_Mesh_Model();
	RefreshSedRectLine();
	Make_Mesh_Line();
	Make_Mesh_Area();
	//
	GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
	//
	DSET.b_CSexist = FALSE;
	//
	Disp_Controls();
	//
	c_Undo.EnableWindow(TRUE);
	CWnd*  cw = GetDlgItem(IDC_BUTTON_104);
	cw->EnableWindow(FALSE);
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　ＤｅｍＡｄｊｕｓｔ   
void CRRI_GUIView::OnBnClickedButton105()
{
	CMagDlg	MD;
	//
	Write_Data_File(ADEM_FILE, File_Format[ADEM_FILE], File_Order[ADEM_FILE], DSET, PM, MESH);
	Write_Data_File(ADIR_FILE, File_Format[ADIR_FILE], File_Order[ADIR_FILE], DSET, PM, MESH);
	//
	if (!B_UndoFirstSave) Save_Undo_File();		// UNDO 用ファイルの保存　B_UndoFirstSaveは中で変更
	//
	MD.kind = 1;		// ダイアログを使いまわすため、拡大の設定であることを示す。
	if (MD.DoModal() == IDCANCEL) return;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	strcpy(DSET.File_names[ADEM_FILE], MD.DemF);
	Get_Relative_Path(MD.DemF, DSET.Proj_Folder, DSET.Input_names[ADEM_FILE]);
	strcpy(DSET.File_names[ADIR_FILE], MD.AdirF);
	Get_Relative_Path(MD.AdirF, DSET.Proj_Folder, DSET.Input_names[ADIR_FILE]);
	//
	// Free MESH
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Change_Cursor(&Gp, IDC_WAIT);
	//if (MESH != NULL) {
	//	for (int i = 0; i < PM.MVnum; i++) SAFE_FREE(MESH[i]);
	//	SAFE_FREE(MESH);
	//}
	//if (PM.Values != 0)	Free_Matrix(PM.MVnum, PM.Values);

	/// Read & Set
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (FAILED(Read_3_Files(FALSE))) { Change_Cursor(&Gp, IDC_ARROW); RETURN("** Failed ** Cannot ｒead converted ｆiles "); }
	//
//	PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
	//
	//Back Image
	if (Gp.Texnum > 0) {
		for (int i = 1; i < Gp.Texnum + 1; i++)  {
			SAFE_FREE(Gp.Tex[i].image);
		}
		Gp.Texnum = 1;
	}
	//
	Calc_Unit_Area();

	if (PM.B_LatLng) Make_Back_Image();						// リソース解放後に作成
	//
	Make_Mesh_Model();
	RefreshSedRectLine();
	Make_Mesh_Line();
	Make_Mesh_Area();
	//
	GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
	//
	//CEX_LABEL = PM.EXnum;						// 土研プログラム用　これ以降はCEXは使えない
	//c_EXLIST.AddString("Adjust Dems.");
	//Disp_Controls();
	////
	CWnd*  cw = GetDlgItem(IDC_BUTTON_105);
	cw->EnableWindow(FALSE);
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　Read ＤＥＭ ＡＣＣ　ＡＤＩＲ　FILE
HRESULT CRRI_GUIView::Read_3_Files(BOOL RELEASE)
{
	int		fid;
	char		buf[SIZE_16K], inchar[SIZE_01K], name[SIZE_01K];
	int		pos;
	FILE*	fp;
	double	val;
	short	sval;
	//
	PM.Anum = 0;
	for (int f = 0; f < 3; f++) {
		if (f == 0)			fid = ADEM_FILE;
		else if (f == 1)		fid = ACC_FILE;
		else if (f == 2)		fid = ADIR_FILE;
		//
		if ((fp = fopen(DSET.File_names[fid], "r")) == NULL) return E_FAIL;
		// -------------------------------------------------------------------------Setting
		if (f == 0) {
			fscanf(fp, "%*s %d", &PM.MHnum);						// 諸元の読込
			fscanf(fp, "%*s %d", &PM.MVnum);
			if (PM.B_LatLng) {
				fscanf(fp, "%*s %lf", &PM.stLNG);
				fscanf(fp, "%*s %lf", &PM.stLAT);
				fscanf(fp, "%*s %lf", &PM.Size);
				PM.Deg_Unit = PM.Coord_Unit = (int)(1. / PM.Size + 0.05);

			}
			else {
				fscanf(fp, "%*s %lf", &PM.stUTM_X);
				fscanf(fp, "%*s %lf", &PM.stUTM_Y);
				fscanf(fp, "%*s %lf", &PM.UTMsize);	
				PM.Deg_Unit = PM.UTMsize;
				PM.Coord_Unit = 1. / PM.UTMsize;
			}
			fscanf(fp, "%*s %*s");
			///
			// MESH Memory
			if (RELEASE) {	// DemAdjust ではメモリーの解放をしない。

				if ((MESH = (MINFO**)malloc(PM.MVnum*sizeof(void*))) == NULL) {
					COMMENT("** Error ** Cannot allocate memory"); return -1;
				}
				int  size = sizeof(MINFO);
				for (int v = 0; v < PM.MVnum; v++) {
					if ((MESH[v] = (MINFO*)malloc(PM.MHnum*sizeof(MINFO))) == NULL) {
						v--;
						while (v >= 0) free(MESH[v--]); free(MESH);
						COMMENT("** Error ** Cannot allocate memory"); return -1;
					}
					for (int h = 0; h < PM.MHnum; h++) memset(&MESH[v][h], 0, sizeof(MINFO));
				}
			}
			//
			fseek(fp, 0, SEEK_SET);
		}
		/// -------------------------------------------------------------------------Setting
		//
		for (int i = 0; i < 6; i++) fgets(buf, SIZE_16K, fp);	// Param + mesh
		for (int v = 0; v < PM.MVnum; v++) {
			if (fgets(buf, SIZE_16K, fp) == NULL) { fclose(fp); return E_FAIL; }
			pos = 0;
			for (int h = 0; h<PM.MHnum; h++)  {
				if (getstr(buf, &pos, inchar, SIZE_01K) == EOF)  { fclose(fp); return E_FAIL; }
				switch (f) {
				case 0: val = MESH[PM.MVnum - v - 1][h].Adem = atof(inchar); break;
				case 1: val = MESH[PM.MVnum - v - 1][h].Acc = atof(inchar); break;
				case 2: sval = MESH[PM.MVnum - v - 1][h].Adir = (short)atoi(inchar); break;
				}
				// メッシュ有効・無効の識別　Adem ファイルによる
				if (fid == ACC_FILE) {
					if (MESH[PM.MVnum - v - 1][h].Acc  >= 0.)	{
						if (MESH[PM.MVnum - v - 1][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[PM.MVnum - v - 1][h].flag = ID_MESH_R;
						else   MESH[PM.MVnum - v - 1][h].flag = ID_MESH;
						PM.Anum++;
					}
					else		MESH[PM.MVnum - v - 1][h].flag = 0;
				}
			}
		}
		fclose(fp);
		//
		DSET.in_avail[fid] = TRUE;		// Add 150308
	}
	//
	return S_OK;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　Read Outer DEM　File
int		CRRI_GUIView::Read_Dem()
{
	int		fid;
	char		buf[SIZE_12K], inchar[SIZE_01K], name[SIZE_01K];
	int		pos;
	FILE*	fp;
	double	val;
	short	sval;
	//
	PM.Anum = 0;
	fid = ADEM_FILE;
	//
	if ((fp = fopen(DSET.EX_Dem_File, "r")) == NULL) return E_FAIL;
	// -------------------------------------------------------------------------Setting
	fscanf(fp, "%*s %d", &PM.MHnum);						// 諸元の読込
	fscanf(fp, "%*s %d", &PM.MVnum);
	if (PM.B_LatLng) {
		fscanf(fp, "%*s %lf", &PM.stLNG);		// 
		fscanf(fp, "%*s %lf", &PM.stLAT);
		fscanf(fp, "%*s %lf", &PM.Size);		// 
		PM.Deg_Unit = PM.Coord_Unit = (double)((int)(1. / PM.Size + EPS5));
	}
	else {
		fscanf(fp, "%*s %lf", &PM.stUTM_X);		// UTM 専用
		fscanf(fp, "%*s %lf", &PM.stUTM_Y);
		fscanf(fp, "%*s %lf", &PM.UTMsize);		// 
		PM.Deg_Unit =PM.UTMsize;
		PM.Coord_Unit = 1. / PM.UTMsize;
	}
	fscanf(fp, "%*s %lf",&DSET.Dem_nodata);					// NODATA
	///
	// MESH Memory
	///
	if ((MESH = (MINFO**)malloc(PM.MVnum*sizeof(void*))) == NULL) {
		COMMENT("** Error ** Cannot allocate memory"); return -1;
	}
	for (int v = 0; v < PM.MVnum; v++) {
		if ((MESH[v] = (MINFO*)malloc(PM.MHnum*sizeof(MINFO))) == NULL) {
			v--;
			while (v >= 0) free(MESH[v--]); free(MESH);
			COMMENT("** Error ** Cannot allocate memory"); return -1;
		}
		for (int h = 0; h<PM.MHnum; h++) memset(&MESH[v][h], 0, sizeof(MINFO));
	}
	//
	fseek(fp, 0, SEEK_SET);
	/// -------------------------------------------------------------------------Setting
	//
	for (int i = 0; i < 6; i++) fgets(buf, SIZE_12K, fp);	// Param + mesh
	for (int v = 0; v < PM.MVnum; v++) {
		if (fgets(buf, SIZE_12K, fp) == NULL) { fclose(fp); return E_FAIL; }
		pos = 0;
		for (int h = 0; h<PM.MHnum; h++)  {
			if (getstr(buf, &pos, inchar, SIZE_01K) == EOF)  { fclose(fp); return E_FAIL; }
			MESH[PM.MVnum - v - 1][h].flag = 1;
			MESH[PM.MVnum - v - 1][h].Adem = atof(inchar);
		}
	}
	fclose(fp);
//
	return S_OK;
}
// 　Extract Landuse (Japan)
void CRRI_GUIView::OnBnClickedButton106()
{
	/* ＦＡＯファイルの存在　*/
	::SetCurrentDirectory(m_BootPath);

	FILE *f1, *f2;
	int c;

	char from[1024] = "tmp\\landuse.txt";
	char to[1024] = "";

	sprintf(to, "%s\\topo\\landuse.txt", DSET.Proj_Folder);

	f1 = fopen(from, "r");

	f2 = fopen(to, "w");
	
	while ((c = fgetc(f1)) != EOF) {
		fputc(c, f2);
	}

	fclose(f2);
	fclose(f1);

}
// //////////////////////////////////////////////////////////////////////////////////////////////////////
///==================  TAB 2 ============================================================================
// //////////////////////////////////////////////////////////////////////////////////////////////////////
///  Static File
void CRRI_GUIView::OnBnClickedButton201()
{
	IFNOT_STAT(PROC_CONFIRM_MESH){ return; }
	//
	CMakeData  CM;
	//
	if( CM.DoModal() == IDCANCEL ) return;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	if (CDATA == ACC_FILE) {
		Make_Mesh_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
		Make_LEGEND();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LEGEND, TRUE);
	}
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
} 
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　時間エディター　
void CRRI_GUIView::OnEnChangeEdit201() { UDT;}
void CRRI_GUIView::OnEnChangeEdit202() { UDT;}
void CRRI_GUIView::OnEnChangeEdit203() { UDT;}
void CRRI_GUIView::OnEnChangeEdit204() { UDT;}
void CRRI_GUIView::OnEnChangeEdit206() { UDT;}
void CRRI_GUIView::OnEnChangeEdit207() { UDT;}
void CRRI_GUIView::OnEnChangeEdit208() { UDT;}
void CRRI_GUIView::OnEnChangeEdit209() { UDT;}

void CRRI_GUIView::OnEnChangeEdit212() { UDT; Get_Period(); }	// 時差

void CRRI_GUIView::Set_Period()
{
	CEdit*		ce;
	CString		str;
	for (int i = 0; i < 4; i++) {
		ce = (CEdit*)GetDlgItem(TIME_ID[i]);
		if (PM.StTime == NULL) ce->SetWindowTextA("");
		else {
			switch (i) {
			case 0: str.Format("%d", PM.StTime.GetYear()); break;
			case 1: str.Format("%d", PM.StTime.GetMonth()); break;
			case 2: str.Format("%d", PM.StTime.GetDay()); break;
			case 3: str.Format("%d", PM.StTime.GetHour()); break;
			}
			ce->SetWindowTextA(str);
		}
	}
	for (int i = 4; i < 8; i++) {
		ce = (CEdit*)GetDlgItem(TIME_ID[i]);
		if (PM.EndTime == NULL) ce->SetWindowTextA("");
		else {
			switch (i) {
			case 4: str.Format("%d", PM.EndTime.GetYear()); break;
			case 5: str.Format("%d", PM.EndTime.GetMonth()); break;
			case 6: str.Format("%d", PM.EndTime.GetDay()); break;
			case 7: str.Format("%d", PM.EndTime.GetHour()); break;
			}
			ce->SetWindowTextA(str);
		}
	}
	//
	ce = (CEdit*)GetDlgItem(IDC_EDIT_212);	// 時差
	str.Format("%.1lf", PM.TimeDiff);
	ce->SetWindowTextA(str);
	//
	STAT(SET_PERIOD) = TRUE;
}
void CRRI_GUIView::Get_Period()
{
	IFNOT_STAT(SET_PERIOD) return;
	//
	CEdit*		ce;
	CString		str, year, mon, day, hour,min;
	BOOL			go;
	CTime		tt;
	int			iyear,imon, iday, ihour, imin;
	//
	ce = (CEdit*)GetDlgItem(IDC_EDIT_212);	// 時差
	ce->GetWindowTextA(str);
	PM.TimeDiff = atof(str);
	//
	go = FALSE;
	PM.StTime = PM.EndTime = NULL;
	for (int i = 0; i < 4; i++) {
		ce = (CEdit*)GetDlgItem(TIME_ID[i]);
		ce->GetWindowTextA(str);
		if (str.GetLength() == 0) return;
		//
		if (i == 0 && str.GetLength() == 0) { break; }
		else {
			switch (i) {
			case 0: iyear = atoi(str); break;
			case 1: imon = atoi(str); break;
			case 2: iday = atoi(str); break;
			case 3: ihour = atoi(str);
				if (ihour == 24) {
					tt = CTime(iyear,imon,iday, 0, 0, 0, -1) + CTimeSpan(1l, 0, 0, 0);
					iyear = tt.GetYear(); imon = tt.GetMonth(); iday = tt.GetDay(); ihour = 0;
				}
				go = TRUE; break;
			}
		}
	}
	if (go) PM.StTime = ::CTime(iyear,imon,iday,ihour, 0, 0, -1);
	//
	go = FALSE;
	for (int i = 4; i < 8; i++) {
		ce = (CEdit*)GetDlgItem(TIME_ID[i]);
		ce->GetWindowTextA(str);
		if (i == 0 && str.GetLength() == 0) { break; }
		else {
			switch (i) {
			case 4: iyear = atoi(str); break;
			case 5: imon = atoi(str); break;
			case 6: iday = atoi(str); break;
			case 7: ihour = atoi(str);
				if (ihour == 24) {
					tt = CTime(iyear, imon, iday, 0, 0, 0, -1) + CTimeSpan(1l, 0, 0, 0);
					iyear = tt.GetYear(); imon = tt.GetMonth(); iday = tt.GetDay(); ihour = 0;
				}
				go = TRUE; break;
			}
		}
	}
	if (go){
		PM.EndTime = ::CTime(iyear, imon, iday, ihour, 0, 0, -1);
	}
}

void CRRI_GUIView::Get_Checks()
{
	CButton* ctl10minsCheck = (CButton*)GetDlgItem(IDC_CHECK_10MIN);
	int ChkBox = ctl10minsCheck->GetCheck();
	if (ChkBox == BST_CHECKED) {
		PM.B_CHECK_10MINS = true;
	}
	else {
		PM.B_CHECK_10MINS = false;
	}
	//CButton* ctlRainOnly = (CButton*)GetDlgItem(IDC_CHECK_RAINONLY);
	//ChkBox = ctlRainOnly->GetCheck();
	//if (ChkBox == BST_CHECKED) {
	//	PM.B_CHECK_RainOnly = true;
	//}
	//else {
	//	PM.B_CHECK_RainOnly = false;
	//}
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　降雨データの作成　　ＲＡＩＮ
void CRRI_GUIView::OnBnClickedButton206()
{
	CRThiessen   CRAIN;
	CString		fname;
	int			ret;
	FILE*		fp;
	int			oldRV = DSET.RV;
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("**Error** \nStart time or end time is not found\nNeed specific period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
		return;
	}
	//  Check
	CString		str;
	CTimeSpan	CHK = PM.EndTime - PM.StTime;
	int			ttime = CHK.GetTotalHours();
	if ((ret = Culc_Out_Hour(ttime)) < 0) {
		str.Format("**Error** \nSet the simulation period which can be divided by %d hrs", -ret);
		MessageBox(str, "warning", MB_OK | MB_ICONASTERISK); return;
	}
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	CRAIN.Dtitle = "Make  rain data from ground gauged rainfall";
	CRAIN.kind = 0;
	if ((ret = CRAIN.DoModal()) == IDCANCEL) return;
	if (CRAIN.Return_Val != 0) {
		str.Format("**Error** Error occured in [rainThiessen.exe] code is %d", CRAIN.Return_Val);
		MessageBox(str, "Error", MB_OK | MB_ICONERROR);
		return;
	}
	//
	if (ret == IDOK) {			
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//  Free
		if (oldRV != 0 && DSET.RAcc != NULL) 	Free_Matrix(oldRV, DSET.RAcc);
		if (DSET.Rmem != 0) {
			for (int i = 0; i < DSET.Rmem; i++) Free_Matrix(oldRV, DSET.Rdata[i].data);
			SAFE_FREE(DSET.Rdata);
		}
		DSET.Rmem = 0;
		oldRV = DSET.RV;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//// 降雨データの読込
		//
		strcpy(DSET.File_names[RAIN_FILE], CRAIN.RainF);
		Get_Relative_Path(DSET.File_names[RAIN_FILE], DSET.Proj_Folder, DSET.Input_names[RAIN_FILE]);
		fname = DSET.File_names[RAIN_FILE];
		Read_Data_File(RAIN_FILE, fname, &DSET, MESH);		// 累加雨量も読み込まれる。

		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//// Time.dat への書き込み
		fname.Format("%s/time.dat", DSET.Proj_Folder);
		if ((fp = fopen(fname, "w")) == NULL) {
			MessageBox("Cannot open time.dat", "Cancel", MB_OK | MB_ICONERROR);
			return;
		}
		fprintf(fp, "%d/%d/%02d  %02d:00:00", PM.StTime.GetYear(),
			PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour()); //2013/5/05  06:00:00
		fclose(fp);
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//// 降雨データの有効化

		DSET.in_avail[RAIN_FILE] = DSET.in_use[RAIN_FILE] = TRUE;
		//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
		DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
		DSET.RH = PM.MHnum;
		DSET.RV = PM.MVnum;
		DSET.Rain_Lng = CRAIN.lng;
		DSET.Rain_Lat = CRAIN.lat;
		DSET.Rain_dx = DSET.Rain_dy = 1. / CRAIN.unit;
		//
		if (CDATA == RAIN_FILE) {	// 現在表示設定がされている
			Change_Cursor(&Gp, IDC_WAIT);
			Make_TS_Model();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
		}
		MessageBox("Make rain data...done !", "Ready", MB_OK | MB_ICONASTERISK);
	}
	else    { COMMENT("Failed in Making rain data"); }
	//
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Disp_Controls();
}
int CRRI_GUIView::Culc_Out_Hour(int Hours)
{
	if (Hours <= 96) return Hours;
	else if (Hours <= 240)  {
		if (Hours % 3 != 0) return -3;
		else               return Hours / 3;
	}
	else if (Hours <= 480)  {
		if (Hours % 6 != 0) return -6;
		else               return Hours / 6;
	}
	else if (Hours <= 960)  {
		if (Hours % 12 != 0) return -12;
		else               return Hours / 12;
	}
	else {
		if (Hours % 24 != 0) return -24;
		else               return Hours / 24;
	}
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　降雨データの作成　　ＧＳＭＡＰ　ＨＯＵＲＬＹ

void		CRRI_GUIView::OnBnClickedButton207()
{
	CString			str, rname;
	CRect			Rrect;
	CTime			stUTC, endUTC, CT;
	CTimeSpan		ts = ::CTimeSpan(0l, 0, (int)(PM.TimeDiff * 60), 0);
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed specific period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	//  Check
	CTimeSpan  CHK = PM.EndTime - PM.StTime;
	int ret, ttime = ts.GetTotalHours();
	if ((ret = Culc_Out_Hour(ttime)) < 0) {
		str.Format("**Error** \nSet the simulation period which can be divided by %d hrs", -ret);
		MessageBox(str, "warning", MB_OK | MB_ICONASTERISK); return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Check
	stUTC = PM.StTime - ts;
	endUTC = PM.EndTime - ts;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Data Folder
	CString		DataDir;
	if (!Button_Dir(&DataDir, m_RecentPath, "Select GSMaP File Folder\ninclude [gsmap_***yyyymmdd.hhmm***]", FALSE)) return;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Save File
	CString	RainF;

	RainF = DSET.File_names[RAIN_FILE];
	//
	str.Format("Output rain_file_name is %s... OK?", DSET.Input_names[RAIN_FILE]);
	if (MessageBox(str, "comfirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		str.Format("%s\\rain", DSET.Proj_Folder);
		::SetCurrentDirectory(str);
		RainF = "Rain.dat";
		if (!Button_File(FALSE, &RainF, m_RecentPath, "Rain data file", "dat")) return;
	}
	//
	strcpy(DSET.File_names[RAIN_FILE], RainF);
	Get_Relative_Path(DSET.File_names[RAIN_FILE], DSET.Proj_Folder, DSET.Input_names[RAIN_FILE]);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 範囲　Ｒｒｅｃｔに格納
	Change_Cursor(&Gp, IDC_WAIT);
	//
	double	dev;
	DSET.Rain_dx = DSET.Rain_dy = GSMAP_SIZE;					// DSET
	//
	Rrect.left = (int)(PM.stLNG / GSMAP_SIZE + EPS5);
	DSET.Rain_Lng = Rrect.left*GSMAP_SIZE;			// DSET
	//
	dev = PM.endLNG / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.right = (int)dev;
	else                   Rrect.right = (int)dev + 1;
	//
	dev = (GSMAP_ST_LAT - PM.endLAT) / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.top = (int)dev;
	else                   Rrect.top = (int)dev;
	dev = (GSMAP_ST_LAT - PM.stLAT) / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.bottom = (int)dev;
	else                   Rrect.bottom = (int)dev + 1;
	DSET.Rain_Lat = (GSMAP_ST_LAT - Rrect.bottom*GSMAP_SIZE);		// DSET
	///
	//
	int			Hnum, Vnum;
	float**		rain;
	int			oldRV = DSET.RV;
	//
	DSET.RH = Hnum = Rrect.Width();
	DSET.RV = Vnum = Rrect.Height();
	rain = Make_Matrix(Hnum, Vnum, 0.f);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Start Read
	//
	//
	FILE*	fp = fopen(RainF, "w");		// for OUTPUT
	if (fp == NULL) {
		MessageBox("** Error ** Cannot open rain data file", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}

	/*
		gsmap_mvk.20070708.0000.v5.222.1.dat
		gsmap_mvk.20140402.0000.v6.0000.0.dat
		gsmap_mvk.20150102.0000.v6.2123.0.dat

		gsmap_nrt.20140402.0000.dat

		gsmap_gauge.20060202.0000.v5.222.1.40.dat
		gsmap_gauge.20140402.0100.v6.0000.0.dat */

	int			FileID;
	int			NameNum = 6;
	CString		fH[] = { "gsmap_mvk.", "gsmap_mvk.", "gsmap_mvk.", "gsmap_nrt.", "gsmap_gauge.", "gsmap_gauge." };
	CString		fT[] = { ".v5.222.1.dat", ".v6.0000.0.dat", ".v6.2123.0.dat", ".dat", ".v5.222.1.40.dat", ".v6.0000.0.dat" };
	// 
	int				times=0;
	CTimeSpan		cts = endUTC - stUTC;
	int				tth = cts.GetDays();
	//

	CTime	Ftime,STtime;
	CT = stUTC;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  ファイル名のパターンを探る。 gsmap_mvk.20040401.0000.v5.222.1.dat）
	FileID = UNDEF;
	for (int i = 0; i < NameNum; i++) {
		rname.Format("%s/%s%4d%02d%02d.%02d00%s", DataDir,
			fH[i], CT.GetYear(), CT.GetMonth(), CT.GetDay(), CT.GetHour(), fT[i]);
		if (File_Exist(rname)) { FileID = i; break; }
	}
	if (FileID == UNDEF) 	{
		MessageBox("** Error ** Any type of GSMaP file does not exist ", "Cancel", MB_OK | MB_ICONERROR);
		Free_Matrix(Vnum, rain); fclose(fp); return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//   Start
	//
	CBUSY*		CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	CB->Set_Title("Read GsMAP rainfall data");
	//
	CB->Set_Prog(0, tth);
	CB->ShowWindow(SW_SHOW);
	while (TRUE) {
		Ftime = ::CTime(CT.GetYear(), CT.GetMonth(), CT.GetDay(), CT.GetHour(), 0, 0, -1);

		rname.Format("%s/%s%4d%02d%02d.%02d00%s",DataDir,
			fH[FileID], Ftime.GetYear(), Ftime.GetMonth(), Ftime.GetDay(), Ftime.GetHour(), fT[FileID]);
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//  
		if (Read_GSMap(rname, Rrect, rain)){
			MessageBox("** Error ** Read GSMap rain data", "Cancel", MB_OK | MB_ICONERROR);
			fclose(fp); Free_Matrix(Vnum, rain); CB->Close(); return;
		}
		//
		if (CT >= endUTC) CT = endUTC;
		//
		if(CT == Ftime ) ts = CT - stUTC;
		else {
			if (CT == endUTC) ts = endUTC - stUTC;	// 最後
			else             ts = CT - stUTC;		// 最初
		}
		//
		fprintf(fp, "%12ld", ts.GetTotalSeconds());
		fprintf(fp, "  %5d  %5d\n", Hnum, Vnum);
		for (int v = Vnum - 1; v >= 0; v--) {
			for (int h = 0; h < Hnum; h++) {
				if (rain[v][h] <= 0.) fprintf(fp, "  0.00");
				else                fprintf(fp, "  %.2f", rain[v][h]);
			}
			CR;
		}
		//
		if (CT >= endUTC) break;
		//
		if (CT == Ftime) CT += CTimeSpan(0l, 1, 0, 0);
		else            CT = Ftime + CTimeSpan(0l, 1, 0, 0);
		//
		times++;
		//
		if(times%24 == 0) CB->Set_Pos(times/24 + 1);
	}
	CB->Close();
	//
	fclose(fp);
	Free_Matrix(Vnum, rain);
	DSET.RT = times;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Free
	if (oldRV != 0 && DSET.RAcc != NULL) 	Free_Matrix(oldRV, DSET.RAcc);
	if (DSET.Rmem != 0) {
		for (int i = 0; i < DSET.Rmem; i++) Free_Matrix(oldRV, DSET.Rdata[i].data);
		SAFE_FREE(DSET.Rdata);
	}
	DSET.Rmem = 0;
	oldRV = DSET.RV;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  降雨データの有効化と表示

	Read_Data_File(RAIN_FILE, RainF, &DSET, MESH);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//// Time.dat への書き込み
	CString	fname;
	fname.Format("%s/time.dat", DSET.Proj_Folder);
	if ((fp = fopen(fname, "w")) == NULL) {
		MessageBox("Cannot open time.dat", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	fprintf(fp, "%d/%d/%02d  %02d:00:00", PM.StTime.GetYear(),
		PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour()); //2013/5/05  06:00:00
	fclose(fp);
	//
	DSET.in_avail[RAIN_FILE] = DSET.in_use[RAIN_FILE] = TRUE;
	//
	ts = PM.EndTime - PM.StTime;
	DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
	DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	//
	if (CDATA == RAIN_FILE) {	// 現在表示設定がされている
		Change_Cursor(&Gp, IDC_WAIT);
		Make_TS_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
	}
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
	Change_Cursor(&Gp, IDC_ARROW);
	MessageBox("Make rain data...Done !", "ready", MB_OK | MB_ICONASTERISK);
	return;
}
int		CRRI_GUIView::Read_GSMap(CString fname, CRect Area, float** rain)
{
	int		fi;
	float	val[GSMAP_HNUM];
	int		ret, nv, nh,size=sizeof(float);
	//
	if ((fi = _open(fname, _O_RDONLY | _O_BINARY)) == -1) {
		COMMENT("** Error ** Open error"); return 1;
	}
	//
	nv = Area.Height() - 1;
	for (int i = 0; i < GSMAP_VNUM; i++) {
		if ((ret = _read(fi, val, GSMAP_HNUM*sizeof(float))) != GSMAP_HNUM*sizeof(float)) {
			if (ret < GSMAP_HNUM*sizeof(float)) {
				COMMENT("** Error ** Insufficient ｒain ｄata");
				_close(fi); return 2;
			}
		}
		if (i > Area.top && i <= Area.bottom) {
			nh = 0;
			for (int h = Area.left; h< Area.right; h++) {
				if (val[h] < 0.f)  rain[nv][nh] = -9999.;
				else 			  rain[nv][nh] = val[h];
				nh++;
			}
			nv--;
		}
	}
	//
	_close(fi);
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　降雨データの作成　　ＧＳＭＡＰ　ＤＡＩＬＹ

void CRRI_GUIView::OnBnClickedButton212()
{
	CString			str, rname;
	CRect			Rrect;
	CTime			stUTC, endUTC, CT;
	CTimeSpan		ts = ::CTimeSpan(0l, 0, (int)(PM.TimeDiff * 60), 0);
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed Period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	//  Check
	CTimeSpan  CHK = PM.EndTime - PM.StTime;
	int ret, ttime = ts.GetTotalHours();
	if ((ret = Culc_Out_Hour(ttime)) < 0) {
		str.Format("**Error** \nSet the simulation period which can be divided by %d hrs", -ret);
		MessageBox(str, "warning", MB_OK | MB_ICONASTERISK); return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Check
	stUTC = PM.StTime - ts;
	endUTC = PM.EndTime - ts;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Data Folder
	CString		DataDir;
	if (!Button_Dir(&DataDir, m_RecentPath, "Select GSMaP File Folder\ninclude [gsmap_***yyyymmdd***]", FALSE)) return;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Save File
	CString	RainF;

	RainF = DSET.File_names[RAIN_FILE];
	//
	str.Format("Output rain_file_name is %s... OK?", DSET.Input_names[RAIN_FILE]);
	if (MessageBox(str, "comfirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		str.Format("%s\\rain", DSET.Proj_Folder);
		::SetCurrentDirectory(str);
		RainF = "Rain.dat";
		if (!Button_File(FALSE, &RainF, m_RecentPath, "Rain data file", "dat")) return;
	}
	//
	strcpy(DSET.File_names[RAIN_FILE], RainF);
	Get_Relative_Path(DSET.File_names[RAIN_FILE], DSET.Proj_Folder, DSET.Input_names[RAIN_FILE]);

	// 範囲　Ｒｒｅｃｔに格納
	Change_Cursor(&Gp, IDC_WAIT);
	//
	double	dev;
	DSET.Rain_dx = DSET.Rain_dy = GSMAP_SIZE;					// DSET
	//
	Rrect.left = (int)(PM.stLNG / GSMAP_SIZE + EPS5);
	DSET.Rain_Lng = Rrect.left*GSMAP_SIZE;			// DSET
	//
	dev = PM.endLNG / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.right = (int)dev;
	else                   Rrect.right = (int)dev + 1;
	//
	dev = (GSMAP_ST_LAT - PM.endLAT) / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.top = (int)dev;
	else                   Rrect.top = (int)dev;
	dev = (GSMAP_ST_LAT - PM.stLAT) / GSMAP_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.bottom = (int)dev;
	else                   Rrect.bottom = (int)dev + 1;
	DSET.Rain_Lat = (GSMAP_ST_LAT - Rrect.bottom*GSMAP_SIZE);		// DSET
	///
	//
	int			Hnum, Vnum;
	float**		rain;
	int			oldRV = DSET.RV;
	//
	DSET.RH = Hnum = Rrect.Width();
	DSET.RV = Vnum = Rrect.Height();
	rain = Make_Matrix(Hnum, Vnum, 0.f);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Start Read
	//
	//
	FILE*	fp = fopen(RainF, "w");		// for OUTPUT
	if (fp == NULL) {
		MessageBox("** Error ** Cannot open rain data file", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}

/*
gsmap_mvk.20140301.0.1d.daily.00Z-23Z.v6.0000.0.dat
gsmap_mvk.20150101.0.1d.daily.00Z-23Z.v6.2123.0.dat
gsmap_mvk.20070624.0.1d.daily.00Z-23Z.v5.222.1.dat
gsmap_mvk.20150502.0.1d.daily.00Z-23Z.v6.4133.0.dat
*/

	int			FileID;
	int			NameNum = 4; 

	CString		fH[] = { "gsmap_mvk.", "gsmap_mvk.", "gsmap_mvk.", "gsmap_mvk." };
	CString		fT[] = { ".0.1d.daily.00Z-23Z.v6.0000.0.dat", ".0.1d.daily.00Z-23Z.v6.2123.0.dat", 
		".0.1d.daily.00Z-23Z.v5.222.1.dat", ".0.1d.daily.00Z-23Z.v6.4133.0.dat"};
	// 
	int			times = 0;
	CTimeSpan	cts = endUTC - stUTC;
	int			tth = cts.GetDays();
	//

	CTime	Ftime, STtime,Lasttime;
	CT = stUTC;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  ファイル名のパターンを探る。 gsmap_mvk.20040401.0000.v5.222.1.dat）
	FileID = UNDEF;
	for (int i = 0; i < NameNum; i++) {
		rname.Format("%s/%s%4d%02d%02d%s", DataDir,fH[i], CT.GetYear(), CT.GetMonth(), CT.GetDay(),  fT[i]);
		if (File_Exist(rname)) { FileID = i; break; }
	}
	if (FileID == UNDEF) 	{
		MessageBox("** Error ** Any type of GSMaP file does not exist ", "Cancel", MB_OK | MB_ICONERROR);
		Free_Matrix(Vnum, rain); fclose(fp); return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//   Start
	//
	CBUSY*		CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	CB->Set_Title("Read GsMAP rainfall data");
	//
	CB->Set_Prog(0, tth);
	CB->ShowWindow(SW_SHOW);
	//  20** /** / ** のGSMAPのデータは ＊＊日の雨量(mm/h)　**-1日の雨量ではない点に注意
	//
	while (TRUE) {
		if (CT > stUTC)  {
			Ftime = ::CTime(CT.GetYear(), CT.GetMonth(), CT.GetDay(), 0, 0, 0, -1)-CTimeSpan(1l,0,0,0);
			//
			rname.Format("%s/%s%4d%02d%02d%s", DataDir,
			fH[FileID], Ftime.GetYear(), Ftime.GetMonth(), Ftime.GetDay(), fT[FileID]);
			//  
			if (Read_GSMap(rname, Rrect, rain)){
				MessageBox("** Error ** Read GSMap rain data", "Cancel", MB_OK | MB_ICONERROR);
				fclose(fp); Free_Matrix(Vnum, rain); CB->Close(); return;
			}
			// 
			if (CT >= endUTC) CT = endUTC;
			//
			ts = CT - stUTC;	// 最後

			fprintf(fp, "%12ld", ts.GetTotalSeconds());
		}
		else {
			fprintf(fp, "       0");
		}
		//
		fprintf(fp, "  %5d  %5d\n", Hnum, Vnum);
		for (int v = Vnum - 1; v >= 0; v--) {
			for (int h = 0; h < Hnum; h++) {
				if (stUTC < CT) {
					if (rain[v][h] <= 0.) fprintf(fp, "  0.00");
					else                fprintf(fp, "  %.2f", rain[v][h]);
				}
				else  fprintf(fp, "  0.00");
			}
			CR;
		}
		//
		if (CT >= endUTC) break;
		//
		if (CT.GetHour() == 0) CT += CTimeSpan(1l, 0, 0, 0);
		else            CT = ::CTime(CT.GetYear(), CT.GetMonth(), CT.GetDay() + 1, 0, 0, 0, -1); 
		//
		times++;
		//
		CB->Set_Pos(times);
	}
	CB->Close();
	//
	fclose(fp);
	Free_Matrix(Vnum, rain);
	DSET.RT = times;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Free
	if (oldRV != 0 && DSET.RAcc != NULL) 	Free_Matrix(oldRV, DSET.RAcc);
	if (DSET.Rmem != 0) {
		for (int i = 0; i < DSET.Rmem; i++) Free_Matrix(oldRV, DSET.Rdata[i].data);
		SAFE_FREE(DSET.Rdata);
	}
	DSET.Rmem = 0;
	oldRV = DSET.RV;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  降雨データの有効化と表示

	Read_Data_File(RAIN_FILE, RainF, &DSET, MESH);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//// Time.dat への書き込み
	CString	fname;
	fname.Format("%s/time.dat", DSET.Proj_Folder);
	if ((fp = fopen(fname, "w")) == NULL) {
		MessageBox("Cannot open time.dat", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	fprintf(fp, "%d/%d/%02d  %02d:00:00", PM.StTime.GetYear(),
		PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour()); //2013/5/05  06:00:00
	fclose(fp);
	//
	DSET.in_avail[RAIN_FILE] = DSET.in_use[RAIN_FILE] = TRUE;
	//
	ts = PM.EndTime - PM.StTime;
	DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
	DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	//
	if (CDATA == RAIN_FILE) {	// 現在表示設定がされている
		Change_Cursor(&Gp, IDC_WAIT);
		Make_TS_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
	}
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
	Change_Cursor(&Gp, IDC_ARROW);
	MessageBox("Make Rain Data...Done !", "Ready", MB_OK | MB_ICONASTERISK);
	return;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　降雨データの作成　　３Ｂ４２ＲＴ
void CRRI_GUIView::OnBnClickedButton208()
{
	CString			str,rname;
	CRect			Rrect;
	CTime			stUTC, endUTC,CT,FTime;
	CTimeSpan		ts = ::CTimeSpan(0l, 0, (int)(PM.TimeDiff * 60), 0);
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed specific period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	//  Check
	CTimeSpan  CHK = PM.EndTime - PM.StTime;
	int ret, ttime = ts.GetTotalHours();		
	if ((ret = Culc_Out_Hour(ttime)) < 0) {
		str.Format("**Error** \nSet the simulation period which can be divided by %d hrs", -ret);
		MessageBox(str, "warning", MB_OK | MB_ICONASTERISK); return;
	}
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Data Folder
	CString		DataDir;
	if (!Button_Dir(&DataDir, m_RecentPath,"Select 3B42RT File Folder\ninclude [3B42RT.yyyymmddhh*]",FALSE)) return;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Save File
	CString	RainF;

	RainF = DSET.File_names[RAIN_FILE];
	//
	str.Format("Output rain_file_name is %s... OK?", DSET.Input_names[RAIN_FILE]);
	if (MessageBox(str, "comfirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		str.Format("%s\\rain", DSET.Proj_Folder);
		::SetCurrentDirectory(str);
		RainF = "Rain.dat";
		if (!Button_File(FALSE, &RainF, m_RecentPath, "Rain data file", "dat")) return;
	}
	//
	strcpy(DSET.File_names[RAIN_FILE], RainF);
	Get_Relative_Path(DSET.File_names[RAIN_FILE], DSET.Proj_Folder, DSET.Input_names[RAIN_FILE]);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 3時間間隔か？  Check
	stUTC	= PM.StTime - ts;
	endUTC	= PM.EndTime - ts;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 範囲　Ｒｒｅｃｔに格納
	Change_Cursor(&Gp, IDC_WAIT);
	//
	double	dev;
	DSET.Rain_dx = DSET.Rain_dy = RT3B_SIZE;					// DSET
	//
	Rrect.left = (int)(PM.stLNG / RT3B_SIZE + EPS5);

	DSET.Rain_Lng = Rrect.left*RT3B_SIZE;			// DSET
	//
	dev = PM.endLNG / RT3B_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.right = (int)dev;
	else                   Rrect.right = (int)dev + 1;
	//
	dev = (RT3B_ST_LAT - PM.endLAT) / RT3B_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.top = (int)dev;
	else                   Rrect.top = (int)dev;
	dev = (RT3B_ST_LAT - PM.stLAT) / RT3B_SIZE;
	if (fmod(dev, 1.) == 0.) Rrect.bottom = (int)dev;
	else                   Rrect.bottom = (int)dev + 1;

	DSET.Rain_Lat = (RT3B_ST_LAT - Rrect.bottom*RT3B_SIZE);		// DSET
	//
	//
	int			Hnum, Vnum;
	double**		rain;
	int			oldRV = DSET.RV;
	//
	DSET.RH = Hnum = Rrect.Width();
	DSET.RV = Vnum = Rrect.Height();
	rain = Make_Matrix(Hnum, Vnum, 0.);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Start Read
	//
	int       HH,times;
	//
	FILE*	fp = fopen(RainF, "w");		// for OUTPUT
	if (fp == NULL) {
		MessageBox("** Error ** Cannot open rain data file", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	CBUSY*		CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	CB->Set_Title("Read 3B42RT data");
	// 
	CTimeSpan   cts = endUTC - stUTC;
	int			tth = (int)(cts.GetTotalHours() / 3);
	//
	int			FileID,timetmp;
	int			NameNum = 2;
	CString		fH[] = { "3B42RT.", "3B42RT." };
	CString		fT[] = { ".7R2.bin", ".7.bin"};
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  ファイル名のパターンを探る。 gsmap_mvk.20040401.0000.v5.222.1.dat）
	CT = stUTC;
	FileID = UNDEF;
	for (int i = 0; i < NameNum; i++) {
		timetmp = (int)CT.GetHour();
		if (CT.GetHour() % 3 != 0) timetmp = (int)(CT.GetHour() / 3) *3;
		//
		rname.Format("%s/%s%4d%02d%02d%02d%s", DataDir,
			fH[i], CT.GetYear(), CT.GetMonth(), CT.GetDay(), timetmp, fT[i]);
		if (File_Exist(rname)) { FileID = i; break; }
	}
	if (FileID == UNDEF) 	{
		MessageBox("** Error ** Any type of 3B42RT file does not exist ", "Cancel", MB_OK | MB_ICONERROR);
		Free_Matrix(Vnum, rain); fclose(fp); CB->Close(); return;
	}
	//
	CB->Set_Prog(0, tth);
	CB->ShowWindow(SW_SHOW);
	//  
	times = 0;
	while (TRUE) {
		if (CT >= endUTC) CT = endUTC;
		if (CT.GetHour() % 3 != 0 || CT.GetMinute() != 0) {
			if (CT == stUTC) {
				HH = (int)(CT.GetHour() / 3) * 3;
				FTime = ::CTime(CT.GetYear(), CT.GetMonth(), CT.GetDay(), HH, 0, 0, -1);
			}
			else  {
				HH = ((int)(CT.GetHour() / 3) + 1) * 3;
				if (HH == 24) {
					HH = 0;
					CT += CTimeSpan(1l, 0, 0, 0);
				}
				FTime = ::CTime(CT.GetYear(), CT.GetMonth(), CT.GetDay(), HH, 0, 0, -1);
			}
		}
		//if (CT.GetHour() % 3 != 0 ) rname.Format("%s\\3B42RT.%4d%02d%02d%02d.7.bin",
		//		DataDir, FTime.GetYear(), FTime.GetMonth(), FTime.GetDay(), FTime.GetHour());
		//else  rname.Format("%s\\3B42RT.%4d%02d%02d%02d.7.bin",
		//	DataDir, CT.GetYear(), CT.GetMonth(), CT.GetDay(), CT.GetHour());
		if (CT.GetHour() % 3 != 0) rname.Format("%s\\%s%4d%02d%02d%02d%s", DataDir, fH[FileID],
			FTime.GetYear(), FTime.GetMonth(), FTime.GetDay(), FTime.GetHour(), fT[FileID]);
		else  rname.Format("%s\\%s%4d%02d%02d%02d%s", DataDir, fH[FileID],
			CT.GetYear(), CT.GetMonth(), CT.GetDay(), CT.GetHour(), fT[FileID]);
		//
		if (!File_Exist(rname)) {
			str.Format("** Error ** 3B42RT ｆile does not exist [%s]", rname);
			MessageBox(str, "Cancel", MB_OK | MB_ICONERROR);
			Free_Matrix(Vnum, rain); fclose(fp); CB->Close(); return;
		}
		if (Read_3B42RT(rname, Rrect, rain)){
			MessageBox("** Error ** Read 3B42RT rain data", "Cancel", MB_OK | MB_ICONERROR);
			fclose(fp); Free_Matrix(Vnum, rain); CB->Close(); return;
		}
		//
		ts = CT - stUTC;
		fprintf(fp, "%12ld", ts.GetTotalSeconds());
		fprintf(fp, "  %5d  %5d\n", Hnum, Vnum);
		for (int v = Vnum - 1; v >= 0; v--) {
			for (int h = 0; h < Hnum; h++) {
				if (rain[v][h] <= 0.) fprintf(fp, "  0.00");
				else                fprintf(fp, "  %.2lf", rain[v][h]);
			}
			CR;
		}
		//
		times++;
		if (CT >= endUTC) break;
		//
		if (CT.GetHour() % 3 != 0) CT = FTime + CTimeSpan(0l, 3, 0, 0);
		else                     CT += CTimeSpan(0l, 3, 0, 0);
		//
		 CB->Set_Pos(times + 1);
	}
	CB->Close();
	//
	DSET.RT = times;
	fclose(fp);
	Free_Matrix(Vnum, rain);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Free
	if (oldRV != 0 && DSET.RAcc != NULL) 	Free_Matrix(oldRV, DSET.RAcc);
	if (DSET.Rmem != 0) {
		for (int i = 0; i < DSET.Rmem; i++) Free_Matrix(oldRV, DSET.Rdata[i].data);
		SAFE_FREE(DSET.Rdata);
	}
	DSET.Rmem = 0;
	oldRV = DSET.RV;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  降雨データの有効化と表示

	Read_Data_File(RAIN_FILE, RainF, &DSET, MESH);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//// Time.dat への書き込み
	CString	fname;
	fname.Format("%s/time.dat", DSET.Proj_Folder);
	if ((fp = fopen(fname, "w")) == NULL) {
		MessageBox("Cannot open time.dat", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	fprintf(fp, "%d/%d/%02d  %02d:00:00", PM.StTime.GetYear(),
		PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour());
	fclose(fp);
	//
	DSET.in_avail[RAIN_FILE] = DSET.in_use[RAIN_FILE] = TRUE;
	//
	ts = PM.EndTime - PM.StTime;
	DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
	DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	//
	if (CDATA == RAIN_FILE) {	// 現在表示設定がされている
		Change_Cursor(&Gp, IDC_WAIT);
		Make_TS_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
	}
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
	MessageBox("Make rain data...done !", "Ready", MB_OK | MB_ICONASTERISK);
	Change_Cursor(&Gp, IDC_ARROW);
	return;
}
int		CRRI_GUIView::Read_3B42RT(CString fname,CRect Area,double** rain)
{
	int		fi;
	BYTE		head[RT3B_HEAD];
	short	val;
	char		buf[2880], sv[2];
	int		ret,nv,nh;
	//
	if ((fi = _open(fname, _O_RDONLY | _O_BINARY)) == -1) { 
		COMMENT("** Error ** Open error"); return 1;
	}
	//
	_read(fi, head, RT3B_HEAD);
	nv = Area.Height()-1;
	for (int i = 0; i < 480; i++) {
		if ((ret = _read(fi, buf, 2880)) != 2880) {
			if (ret < 2880) {
				COMMENT("** Error ** Insufficient ｒain ｄata");
				_close(fi); return 2;
			}
		}
		if (i > Area.top && i <= Area.bottom) {
			nh = 0;
			for (int h = Area.left; h< Area.right; h++) {
				sv[0] = buf[h * 2];
				sv[1] = buf[h * 2 + 1];
				val = *(short*)sv;
				if (val == I2MISSING)  rain[nv][nh] = -9999.;
				else {
					//
					sv[1] = buf[h * 2];
					sv[0] = buf[h * 2 + 1];
					val = (*(short*)sv);
					rain[nv][nh] = (double)val / 100.;
				}
				nh++;
			}
			nv--;
		}
	}
	//
	_close(fi);
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　降雨累加
void CRRI_GUIView::OnBnClickedButton220()
{
	CString		fname,str;
	fname.Format("%s/total_rain.dat", DSET.Folder_Name[RAIN_FILE]);
	str.Format("Accumulative rainfall file name is [ %s ]...OK!", fname);
	if (MessageBox(str, "file name", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		fname = _T("");
		if(!Button_File(FALSE, &fname, m_RecentPath, "Accumulative rainfall file", "dat")) return;
	}
	//
	FILE*	fp = fopen(fname, "w");
	if (fp == NULL) { RETURN("** Error ** Cannot open save file"); }
	//
	fprintf(fp, "ncols	 %d \n",DSET.RH);
	fprintf(fp, "nrows	 %d \n", DSET.RV);
	fprintf(fp, "xllcorner	 %.1lf\n", DSET.Rain_Lng);
	fprintf(fp, "yllcorner	 %.1lf\n", DSET.Rain_Lat);
	fprintf(fp, "cellsize	 %.14lf\n", DSET.Rain_dx);
	fprintf(fp, "NODATA_value  -9999 \n");
	//
	for (int v = DSET.RV-1; v >=0; v--) {		// RAcc は降雨累加が北から入っている。
		for (int h = 0; h < DSET.RH; h++) {
			if (h == 0) fprintf(fp, "%.2lf", DSET.RAcc[v][h]);
			else        fprintf(fp, "  %.2lf", DSET.RAcc[v][h]);
		}
		CR;
	}
	fclose(fp);
}

//void CRRI_GUIView::OnBnClickedButton213()			// Merge CELLS
//{
//	//
//	CAssemble   CAS;
//	if (CAS.DoModal() == IDCANCEL) return;
//}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　RRI-GUI 雨量変換プログラム　処理
void CRRI_GUIView::OnBnClickedButton210()
{
	CString			str, rname;
	CRect			Rrect;
	CTime			stUTC, endUTC, CT, FTime;
	CTimeSpan		ts = ::CTimeSpan(0l, 0, (int)(PM.TimeDiff * 60), 0);

	CTimeSpan   cts = endUTC - stUTC;
	stUTC = PM.StTime - ts;
	endUTC = PM.EndTime - ts;
	int				tth = (int)(cts.GetTotalHours() / 3);

	//
	Get_Period();
	Get_Checks();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed specific period....",
			"Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	//  Check
	CTimeSpan  CHK = PM.EndTime - PM.StTime;
	int ret, ttime = ts.GetTotalHours();
	if ((ret = Culc_Out_Hour(ttime)) < 0) {
		str.Format("**Error** \nSet the simulation period which can be divided by %d hrs", -ret);
		MessageBox(str, "warning", MB_OK | MB_ICONASTERISK); return;
	}

	static std::vector<std::map<std::string, std::string>> strInfos
	{
		{
			{"TypeName", "JmbscRadar"},
			{"FolderName", "GetJmbscRadar"},
			{"IniFile", "GetJmbscRadar.ini"},
			{"ExeFile", "GetJmbscRadar.exe"}
		},
		{
			{"TypeName", "NowCast"},
			{"FolderName", "ConvHRNowcast2RRI"},
			{"IniFile", "config.ini"},
			{"ExeFile", "ConvHRNowcast2RRI.exe"}
		}
	};

	//select output files
	OutputSelectionDlg selectDlg;
	if (selectDlg.DoModal() == IDCANCEL) {
		return;
	}

	int nToolExeType = static_cast<int>(selectDlg.GetToolExeType());
	if (nToolExeType > strInfos.size()-1) {
		CString msg;
		msg.Format("Invalid tool exe type: %d!", nToolExeType);
		RETURN(msg);
	}

	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Data Folder
	CString csTitle;
	auto pTypeName = strInfos[nToolExeType].find("TypeName");
	csTitle.Format("Select %s Data Folder", pTypeName->second.c_str());
	CString		DataDir;
	if (!Button_Dir(&DataDir, m_RecentPath, csTitle, FALSE)) return;

	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  OutPut Folder
	// CString		OutDataDir;
	// if (!Button_Dir(&OutDataDir, m_RecentPath, "Select Out put Data Folder.", FALSE)) return;
	char OutDataDir[SIZE_1K];
	sprintf(OutDataDir, "%s/rain", DSET.Proj_Folder);

	Set_RectArea();
	char KdoLeftUpper[256] = { '\0' };
	char IdoLeftUpper[256] = { '\0' };
	char KdoRightLower[256] = { '\0' };
	char IdoRightLower[256] = { '\0' };
	sprintf(KdoLeftUpper, "%f", atof(s_stLNG_deg) + (atof(s_stLNG_min) / 60) + (atof(s_stLNG_sec) / 60 / 60));
	sprintf(IdoLeftUpper, "%f", atof(s_endLAT_deg) + (atof(s_endLAT_min) / 60) + (atof(s_endLAT_sec) / 60 / 60));
	sprintf(KdoRightLower, "%f", atof(s_endLNG_deg) + (atof(s_endLNG_min) / 60) + (atof(s_endLNG_sec) / 60 / 60));
	sprintf(IdoRightLower, "%f", atof(s_stLAT_deg) + (atof(s_stLAT_min) / 60) + (atof(s_stLAT_sec) / 60 / 60));

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Exe & Iniファイル
	CString exePath;
	CString iniPath;
	auto pFolderName = strInfos[nToolExeType].find("FolderName");
	auto pIniFile = strInfos[nToolExeType].find("IniFile");
	auto pExeFile = strInfos[nToolExeType].find("ExeFile");
	iniPath.Format("%s/%s/%s", m_BootPath, pFolderName->second.c_str(), pIniFile->second.c_str());
	exePath.Format("%s/%s/%s", m_BootPath, pFolderName->second.c_str(), pExeFile->second.c_str());

	if (!File_Exist(exePath)) {
		csTitle.Format("** Error ** Tool %s does not exist!", pExeFile->second.c_str());
		MessageBox(csTitle.GetString(), "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	FILE* fp = fopen(iniPath, "w");
	if (fp == NULL) {
		csTitle.Format("** Error ** Cannot open ini config file %s !", pIniFile->second.c_str());
		RETURN(csTitle.GetString());
	}

	if (nToolExeType == static_cast<int>(ToolExeType::Radar)) {
		fprintf(fp, "[RADAR]\n");
		fprintf(fp, "CM_RiverName = 全国\n");
		if (PM.B_CHECK_10MINS) {
			fprintf(fp, "RD_Kind_ID = 31, 32\n");
		} else {
			fprintf(fp, "RD_Kind_ID = 25, 27\n");
		}
	} else {
		fprintf(fp, "Enable_Info_Log = 1\n");
		auto dataType = selectDlg.GetDataType();
		int nDataType = static_cast<int>(dataType) + 1;
		fprintf(fp, "raintype = %d\n", nDataType);

		CString cfgDataFilePtn;
		//Prr05lv: 雨量；　Pri60lv: 降水強度
		cfgDataFilePtn.Format("PathNameInp = Z__C_RJTD_*_NOWC_GPV_Ggis0p25km_%s_Aper5min_FH0000-0030_grib2.bin.gz\n", dataType==DataType::Rainfall?"Prr05lv":"Pri60lv");
		fprintf(fp, cfgDataFilePtn);
	}
	
	fprintf(fp, "MeshRootDir_org = %s\n", DataDir.GetString());
	fprintf(fp, "MeshOutputDir = %s\n", OutDataDir);
	fprintf(fp, "StartDateTime = %d/%d/%02d %02d:00:00\n", PM.StTime.GetYear(),
		PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour());
	fprintf(fp, "EndDateTime = %d/%d/%02d %02d:00:00\n", PM.EndTime.GetYear(),
		PM.EndTime.GetMonth(), PM.EndTime.GetDay(), PM.EndTime.GetHour());
	fprintf(fp, "Kdo_LeftUpper = %s\n", KdoLeftUpper);
	fprintf(fp, "Ido_LeftUpper = %s\n", IdoLeftUpper);
	fprintf(fp, "Kdo_RightLower = %s\n", KdoRightLower);
	fprintf(fp, "Ido_RightLower = %s\n", IdoRightLower);
	fprintf(fp, "rain_dat = %d\n", static_cast<int>(selectDlg.GetFlgRain()));
	fprintf(fp, "JMAJ_dat = %d\n", static_cast<int>(selectDlg.GetFlgJmaJ()));
	fprintf(fp, "JMAY_dat = %d\n", static_cast<int>(selectDlg.GetFlgJmaY()));
	fclose(fp);

	// Process Dialog
	CBUSY* CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	csTitle.Format("Read %s data", pTypeName->second.c_str());
	CB->Set_Title(csTitle);
	CB->Set_Prog(0, tth);
	CB->ShowWindow(SW_SHOW);
	CB->Set_Pos(1);

	// Process 実行
	// プロセスを起動
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	LPTSTR pszFName = exePath.GetBuffer();
	::CreateProcess(NULL, pszFName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// 終了まで待機
	::WaitForSingleObject(pi.hProcess, INFINITE);

	// 終了を告知
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);

	CB->Close();

	FILE *exFile;
	char	exFpath[512];
	CString exFpathCstr;
	char paramb[3][256];
	char buf[128];

	GetCurrentDirectory(512, exFpath);
	exFpathCstr.Format("%s/%s/extent.txt", exFpath, pFolderName->second.c_str());
	if (PathFileExists(exFpathCstr)) {
		exFile = fopen(exFpathCstr, "r");
		for (int i = 0; i < 3; i++) {
			fgets(paramb[i], 256, exFile);
		}
		DSET.Rain_Lng = atof(paramb[0]);
		DSET.Rain_Lat = atof(paramb[1]);
		sscanf(paramb[2], "%lf %lf %s", &DSET.Rain_dx, &DSET.Rain_dy, &buf);
		fclose(exFile);
	}

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  降雨データの有効化と表示
	CString	RainF;
	
	RainF = DSET.File_names[RAIN_FILE];
	str.Format("Output rain_file_name is %s... OK?", DSET.Input_names[RAIN_FILE]);
	if (MessageBox(str, "comfirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		str.Format("%s\\rain", DSET.Proj_Folder);
		::SetCurrentDirectory(str);
		RainF = "Rain.dat";
		if (!Button_File(FALSE, &RainF, m_RecentPath, "Rain data file", "dat")) return;
	}
	Read_Data_File(RAIN_FILE, RainF, &DSET, MESH);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//// Time.dat への書き込み
	CString	fname;
	fname.Format("%s/time.dat", DSET.Proj_Folder);
	if ((fp = fopen(fname, "w")) == NULL) {
		MessageBox("Cannot open time.dat", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	fprintf(fp, "%d/%d/%02d  %02d:00:00", PM.StTime.GetYear(),
		PM.StTime.GetMonth(), PM.StTime.GetDay(), PM.StTime.GetHour());
	fclose(fp);
	//
	DSET.in_avail[RAIN_FILE] = DSET.in_use[RAIN_FILE] = TRUE;
	//
	ts = PM.EndTime - PM.StTime;
	DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
	DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	//
	if (CDATA == RAIN_FILE) {	// 現在表示設定がされている
		Change_Cursor(&Gp, IDC_WAIT);
		Make_TS_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
	}
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
	MessageBox("Make rain data...done !", "Ready", MB_OK | MB_ICONASTERISK);
	Change_Cursor(&Gp, IDC_ARROW);
	return;
}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//// 累加ファイルの作成
	//
void CRRI_GUIView::OnBnClickedButtonEacc()
{
	CString	fname;

	if (!Button_File(FALSE, &fname, m_RecentPath, "Save Accmulate Evp", "dat")) return;
	//
	FILE*	fp = fopen(fname, "w");
	if (fp == NULL) {
		RETURN("** Error ** Cannot open save file");
	}
	//
	fprintf(fp, "ncols	 %d\n", DSET.EH);
	fprintf(fp, "nrows	 %d\n", DSET.EV);
	fprintf(fp, "xllcorner	 %.1lf\n", DSET.Evp_Lng);
	fprintf(fp, "yllcorner	 %.1lf\n", DSET.Evp_Lat);
	fprintf(fp, "cellsize	 %.14lf\n", DSET.Evp_DX);
	fprintf(fp, "NODATA_value  -9999 \n");
	//
	for (int v = DSET.EV - 1; v >= 0; v--) {		// RAcc は降雨累加が北から入っている。
		for (int h = 0; h < DSET.EH; h++) {
			if (h == 0) fprintf(fp, "%.3lf", DSET.EAcc[v][h]);
			else        fprintf(fp, "  %.3lf", DSET.EAcc[v][h]);
		}
		CR;
	}
	fclose(fp);
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 　蒸発散量の作成
void CRRI_GUIView::OnBnClickedButton214()
{
	CRThiessen   CRAIN;
	CString		fname;
	int			ret;
	FILE*		fp;
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed specific period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Free
	if (DSET.EV != 0 && DSET.EAcc != NULL)
		Free_Matrix(DSET.EV, DSET.EAcc);
	if (DSET.Emem != 0) {
		for (int i = 0; i < DSET.Emem; i++) Free_Matrix(DSET.EV, DSET.Edata[i].data);
		SAFE_FREE(DSET.Edata);
		DSET.Emem = 0;
	}
	//
	CRAIN.Dtitle = "Make  evaporation data ";
	CRAIN.kind = 1;
	if ((ret = CRAIN.DoModal()) == IDCANCEL) return;
	//
	if (CRAIN.Return_Val == 0) {
		strcpy(DSET.File_names[POTENT_FILE], CRAIN.RainF);
		Get_Relative_Path(DSET.File_names[POTENT_FILE], DSET.Proj_Folder, DSET.Input_names[POTENT_FILE]);
		fname = DSET.File_names[POTENT_FILE];
		Read_Data_File(POTENT_FILE, fname, &DSET, MESH);		// 累加蒸発散も読み込まれる。

																///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Evp = ts.GetTotalHours();
		DSET.in_avail[POTENT_FILE] = DSET.in_use[POTENT_FILE] = TRUE;
		//
		//
		if (CDATA == POTENT_FILE) {	// 現在表示設定がされている
			Change_Cursor(&Gp, IDC_WAIT);
			Make_TS_Model();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
		}
		//
		COMMENT("Succeeded in making evaporation data");
	}
	else { COMMENT("** Failed in making evaporation data"); }
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
}
// 　解析雨量のみ出力用 20190201
void CRRI_GUIView::OnBnClickedButton215()
{
	//
}
//  //////////////////////////////////////////////////////////////////////////////////////////////////////
/// ==================  TAB 3 ============================================================================
//  //////////////////////////////////////////////////////////////////////////////////////////////////////

void		CRRI_GUIView::OnCbnSelchangeComboData()
{
	if (STAT(DISP_EDITWIN)) {
		c_ComboData.SetCurSel(CDATA); return;
	}
	//
	UDT;
	int		ret, old = PM.DDISP, id = c_ComboData.GetCurSel();
	CWnd* cw;
	//
	COLD = CDATA;
	CDATA = PM.Data_Order[id];
	//
	if (CDATA != COLD) {
		// 凡例
		if (CDATA <= GAMPT_FILE || CDATA == POTENT_FILE || CDATA >= LAND_COVER) {
			PM.B_Disp_Legend = TRUE;
			Make_LEGEND();		//***************** 注意
		}
		else {
			PM.B_Disp_Legend = FALSE;
			GLobj_Delete(&Gp, OBJID_LEGEND);
		}
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_LEGEND, TRUE);
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 矢印を消しておく。
		Gp.Gobj[OBJID_ARROW].display = FALSE;
		STAT(DISP_ARROW) = FALSE;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_ARROW, TRUE);
		c_DispArrow.SetCheck(0);
		///
		// 方向編集矢印を消しておく。
		Gp.Gobj[OBJID_EDIT_ARROW].display = FALSE;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_EDIT_ARROW, TRUE);
		UHnum = 0;
		//		STAT(AVAIL_UNDO) = FALSE;
		STAT(AVAIL_RESET) = FALSE;
		Show_Mesh_Info(UNDEF, UNDEF);
		///
		//  同時に編集用の選択メッシュがある場合は選択を消しておく。
		GLobj_Delete(&Gp, OBJID_SELECT);
		SI.Num = 0;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_SELECT, TRUE);

		Disp_Direction_Radio(UNDEF, UNDEF);
		Disp_Controls();
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// データ書き出し
		if (COLD == RAIN_FILE || COLD == POTENT_FILE) 	GLobj_Delete(&Gp, OBJID_TS);
		else                                         GLobj_Delete(&Gp, OBJID_MESH);
		//
		if (CDATA == RAIN_FILE || CDATA == POTENT_FILE) {		// 時間に関係なく累積値を表示
			PM.Data_Alpha = 0.5;
			Change_Cursor(&Gp, IDC_WAIT);
			Make_TS_Model();
			if (Gp.Gobj[OBJID_TS].pnum != 0) GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
			else { Gp.Gobj[OBJID_TS].display = FALSE; GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE); }
			//
			if (DSET.RGnum != 0) {
				Make_GROUND_OBS();
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_GROUND_OBS, TRUE);
			}
			if (!PM.B_ColorMesh) Gp.Gobj[OBJID_TS].display = FALSE;
		}
		if ((CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE && CDATA != ADIR_FILE) || CDATA >= LAND_COVER) {
			PM.Data_Alpha = 1.;
			Change_Cursor(&Gp, IDC_WAIT);
			Make_Mesh_Model();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			if (!PM.B_ColorMesh) Gp.Gobj[OBJID_MESH].display = FALSE;
		}
		//
		if (CDATA == ADIR_FILE) { 	/// ーーーーーーーーーーーーーーーーーーーーーーー通常矢印描画
			if (!STAT(SET_ARROW)) {
				Change_Cursor(&Gp, IDC_WAIT);
				Disp_Arrow();
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_ARROW, TRUE);
			}
			if (STAT(ENABLE_DRAW_ARROW)) {
				Gp.Gobj[OBJID_ARROW].display = TRUE;
				STAT(DISP_ARROW) = TRUE;
			}
			else {
				Gp.Gobj[OBJID_ARROW].display = FALSE;
				STAT(DISP_ARROW) = FALSE;
			}
			GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_ARROW, TRUE);
			c_DispArrow.SetCheck(1);
			//
			if (NoexitMem == 0) {
				NoexitMem = 100;
				if ((NoexitPos = (CPoint*)calloc(NoexitMem, sizeof(CPoint))) == NULL) {
					NoexitMem = 0; return;
				}
			}
		}
		//
		if (CDATA >= HS_WLEV_FILE && CDATA <= QR_WLEV_FILE) {
			GLobj_Delete(&Gp, OBJID_MESH);
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			//
			CTSEditDlg	CTD;
			CTD.Data_ID = CDATA;
			CTD.BT = DSET.BT;
			ret = CTD.DoModal(); //201905
			//ret = IDOK;
			//
			if (ret == IDOK) {
				DSET.in_avail[CDATA] = DSET.in_use[CDATA] = TRUE;
				Write_Data_File(CDATA, File_Format[CDATA], File_Order[CDATA], DSET, PM, MESH);
				Write_RRI_INPUT(DSET);
				B_Change_RRI = 0;
				//
				Clear_Select();
				PM.Data_Alpha = 1.;
				Make_Mesh_Line();
				GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
			}

		}
		//
		if (CDATA == DAM_CNT_FILE) {
			GLobj_Delete(&Gp, OBJID_MESH);
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			//
			OnIdsBoundaryDam();
		}
		if (CDATA == DIV_FILE) {
			Clear_Select();
			//
			GLobj_Delete(&Gp, OBJID_MESH);
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			//
//			OnIdsBoundaryDiv();
			Make_Mesh_Line();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		}
		if (CDATA == LOCATION_FILE) {
			GLobj_Delete(&Gp, OBJID_MESH);
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			//
			OnIdsBoundaryPos();
		}
	}

	RefreshSedRectLine();
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	//
	Disp_Controls();
	c_SliderDataT.SetPos((int)((1. - PM.Data_Alpha) * 10));
	cw = GetDlgItem(ID_PICT);
	cw->SetFocus();

}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Show List
void CRRI_GUIView::OnBnClickedButtonList()
{
	if (CDATA >= HS_WLEV_FILE && CDATA <= QR_WLEV_FILE) {		// TimeSet
		GLobj_Delete(&Gp, OBJID_MESH);
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
		//
		CTSEditDlg	CTD;
		CTD.Data_ID = CDATA;
		CTD.BT = DSET.BT;

		int ret = CTD.DoModal(); //201905
		//int ret = IDOK;
	}
	if (CDATA == DAM_CNT_FILE) {
		OnIdsBoundaryDam();
	}
	if (CDATA == LOCATION_FILE) {
		GLobj_Delete(&Gp, OBJID_MESH);
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
		//
		OnIdsBoundaryPos();
	}
	if (CDATA == DIV_FILE) {
		OnIdsBoundaryDiv();
	}
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DRAW Time Series Mesh
int		CRRI_GUIView::Make_TS_Model()
{
	double		Ox, Oy, MsclX, MsclY,val;
	int			Hnum, Vnum, no[4];
	//
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_TS];
	int			id, pno;
	FCOLOR		fcol;
	//
	if (CDATA == RAIN_FILE) {
		MsclX = DSET.Rain_dx / PM.Size;
		MsclY = DSET.Rain_dy / PM.Size;
		Ox = (DSET.Rain_Lng - PM.stLNG) / PM.Size;
		Oy = (DSET.Rain_Lat - PM.stLAT) / PM.Size;
		Hnum = DSET.RH;
		Vnum = DSET.RV;
	}
	else if (CDATA == POTENT_FILE) {
		MsclX = DSET.Evp_DX / PM.Size;
		MsclY = DSET.Evp_DY / PM.Size;
		Ox = (DSET.Evp_Lng - PM.stLNG) / PM.Size;
		Oy = (DSET.Evp_Lat - PM.stLAT) / PM.Size;
		Hnum = DSET.EH;
		Vnum = DSET.EV;
	}
	//
	GLobj_Delete(&Gp, OBJID_TS);
	GLobj_Init(obj, (Vnum + 1)*(Hnum + 1), Vnum*Hnum);
	//
	for (int v = 0; v <= Vnum; v++) {
		for (int h = 0; h <= Hnum; h++) {
			GLobj_Add_Vert(obj, Ox + h*MsclX, Oy + v*MsclY, TS_Z, FALSE);
		}
	}
	//
	// Polygon
	PM.Data_Alpha = PM.Dcol[CDATA].alpha;
	for (int v = 0; v < Vnum; v++) {
		for (int h = 0; h < Hnum; h++) {
			if (CDATA == RAIN_FILE) val = DSET.RAcc[v][h];
			else                  val = DSET.EAcc[v][h];
			//
			id = v*(Hnum + 1) + h;
			no[0] = id;
			no[1] = id + 1;
			no[2] = no[1] + (int)(Hnum + 1);
			no[3] = no[2] - 1;
			//
			if (Get_Data_Color(TRUE,v, h,0., &fcol)) {
				pno = GLobj_Add_Poly(obj, 4, no, GL_POLYGON, fcol);
				obj->poly[pno].Alpha = PM.Data_Alpha;
			}
		}
	}
	//
	c_SliderDataT.SetPos((int)(10 * (1. - PM.Data_Alpha)));
	//
	return 0;
}
int		CRRI_GUIView::Make_GROUND_OBS()
{
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_GROUND_OBS];
	int			id, pno,no[300],Num;
	FCOLOR		fcol;
	double		X, Z;
	//
	GLobj_Delete(&Gp, OBJID_GROUND_OBS);
	GLobj_Init(obj, (DSET.RGnum + 10), (DSET.RGnum + 10));
	//
	Num = 0;
	for (int v = 0; v <DSET.RGnum; v++) {
		if (DSET.RGpos[v].lng < -999. || DSET.RGpos[v].lat < -999.) {
			DSET.RGpos[v].X = DSET.RGpos[v].Z = DUNDEF;
			continue;
		}
		DSET.RGpos[v].X = X = (DSET.RGpos[v].lng - PM.stLNG)*PM.Coord_Unit;
		DSET.RGpos[v].Z = Z = (DSET.RGpos[v].lat - PM.stLAT)*PM.Coord_Unit;
		no[Num++] = GLobj_Add_Vert(obj, X, Z, SELECT_Z, FALSE);
	}
	GLobj_Add_Poly(obj, Num, no, GL_POINTS,5.f,
		F_COLOR(GetRValue(PM.Col_Observatory), GetGValue(PM.Col_Observatory), GetBValue(PM.Col_Observatory)));
	//
	return 0;
}
int		CRRI_GUIView::Make_LEGEND()
{
	int				Bid = OBJID_LEGEND;
	GL_OBJECT*		obj = &Gp.Gobj[Bid];
	//
	GLobj_Delete(&Gp, Bid);
	//
	if (!(CDATA <= GAMPT_FILE || CDATA >= LAND_COVER)) return 1;				// ガンプト以上は凡例表示しない。

	if (CDATA == ADIR_FILE) return 2;			// 矢印表示に変更

	if (CDATA == LU_FILE || CDATA == LAND_COVER || CDATA == LAND_SOIL) {		// 土地利用の場合は凡例表示しない。
		Make_Decimal_Legend();
		return 0;
	}
	//
	FCOLOR			Fcol;
	// --------------------------------------------------------------------------------------------
	// 開始時、連続・離散表示の指示、閾値の変更等
	//
	char			str[128], cfont[64];
	double		X = PM.Pos_Legend.x, Y = PM.Pos_Legend.y;
	int			Span = PM.Lsize;
	double		cv, dx, dy, DX, DY,len;
	int			no[4], lno[2];
	CString		strnum;
	char			sunit[32];

	// Change Variable
	int			NUM;
	COLORREF*	COL;
	double*		VAL;
	//
	NUM = PM.Dcol[CDATA].num;
	COL = PM.Dcol[CDATA].Rcol;
	VAL = PM.Dcol[CDATA].val;
	//
	PM.Area_Legend.bottom = (LONG)PM.Pos_Legend.y;
	PM.Area_Legend.left = (LONG)PM.Pos_Legend.x;
	//
	strcpy(sunit, "( m )");
	if (CDATA == 0) strcpy(sunit, "( mm )");
	else if (CDATA == ACC_FILE) strcpy(sunit, " cells");
	else if (CDATA == ADIR_FILE && CDATA == LU_FILE) strcpy(sunit, " ");
	else if (CDATA == SED_FILE) strcpy(sunit, " ");
	//
	GLobj_Init(obj, 100, 100);
	DX = DX = DUNDEF;
	//
	strcpy(cfont, Fonts[PM.Lfont]);

	cv = 0; // 2019.02 初期化エラーで落ちるため追加

	if (TRUE) {			// 横置きは考えない
		dx = dy = Span;
		//
		if (PM.Dcol[CDATA].Mos) {
			for (int i = 0; i<NUM; i++) {
				cv = Y + dy*i;
				if (i == 0) {
					no[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, TRUE);
					no[1] = GLobj_Add_Vert(obj, X + dx, Y, DUNDEF, TRUE);
					GLobj_Add_Text(&Gp, Bid, DIM_2D, sunit, "Times New Roman", FONT_REGULAR,
						(int)(Span*0.8), (int)(Span*0.3), X + dx / 2, cv - dy*0.8, DUNDEF,
						F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
						GetBValue(PM.Col_LegendChar)));
				}
				no[2] = GLobj_Add_Vert(obj, X + dx, cv+dy, DUNDEF, TRUE);
				no[3] = GLobj_Add_Vert(obj, X, cv+dy, DUNDEF, TRUE);
				//
				Fcol = F_COLOR(GetRValue(COL[i]), GetGValue(COL[i]), GetBValue(COL[i]));
				GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 1., Fcol);
				//
				if (i == 0) {
					if (CDATA == SED_FILE) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " = %s", strnum);
					}
					else if (PM.Dcol[CDATA].Equal) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " >= %s", strnum);
					}
					else {
						Set_Double_Str(VAL[i + 1], &strnum, 0);
						sprintf(str, " <= %s", strnum);
					}
				}
				else if (i < NUM - 1) {
					if (CDATA == SED_FILE) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " = %s", strnum);
					}
					else if (PM.Dcol[CDATA].Equal) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " >= %s", strnum);
					}
					else {
						Set_Double_Str(VAL[i+1], &strnum, 0);
						sprintf(str, " <= %s", strnum);
					}
				}
				else  {
					if (CDATA == SED_FILE) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " = %s", strnum);
					}
					else if (PM.Dcol[CDATA].Equal) {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " >= %s", strnum);
					}
					else {
						Set_Double_Str(VAL[i], &strnum, 0);
						sprintf(str, " > %s", strnum);
					}
				}
				GLobj_Add_Text(&Gp, Bid, DIM_2D, str, cfont, PM.Lstyle,
					(int)(Span*0.8), (int)(Span*0.3), X + dx, cv + Span*0.2 , DUNDEF,
					F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
					GetBValue(PM.Col_LegendChar)));

				len = (strlen(str)+1.5)*Span*0.4 + 10;
				if (DX < len) DX = len;
				//
				no[0] = no[3];
				no[1] = no[2];
			}
			//GLobj_Add_Text(&Gp, Bid, DIM_2D, "Legend ", "Times New Roman", FONT_REGULAR,
			//	(int)Span, (int)(Span*0.3), X + 0.1*dx, cv + 1.2*dy, DUNDEF,
			//	F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
			//	GetBValue(PM.Col_LegendChar)));
		}	DY = cv+1.2*dy;
		//else {
		//	for (int i = 0; i<NUM; i++) {
		//		cv = Y + dy*i;
		//		if (i == 0) {
		//			lno[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, FALSE, F_COLOR(0, 0, 0), 1.);
		//			lno[1] = GLobj_Add_Vert(obj, X + dx + 2., Y, DUNDEF, FALSE, F_COLOR(0, 0, 0), 1.);
		//			GLobj_Add_Poly(obj, DIM_2D, 2, lno, GL_LINE_STRIP, 0.5f);
		//			//
		//			Fcol = F_COLOR(GetRValue(COL[0]), GetGValue(COL[0]), GetBValue(COL[0]));
		//			no[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, FALSE, Fcol, 1.);
		//			no[1] = GLobj_Add_Vert(obj, X + dx, Y, DUNDEF, FALSE, Fcol, 1.);
		//			GLobj_Add_Text(&Gp, Bid, DIM_2D, sunit, "Times New Roman", FONT_REGULAR,
		//				PM.Lh, PM.Lw, X + dx, Y - PM.Lh, DUNDEF,
		//				F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
		//				GetBValue(PM.Col_LegendChar)));
		//			//
		//			Set_Double_Str(VAL[0], &strnum, 1);
		//			strcpy(str, strnum);
		//			GLobj_Add_Text(&Gp, Bid, DIM_2D, str, cfont, PM.Lstyle,
		//				PM.Lh, PM.Lw, X + dx + 4., Y - 0.2*PM.Lh, DUNDEF,
		//				F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
		//				GetBValue(PM.Col_LegendChar)));
		//		}
		//		lno[0] = GLobj_Add_Vert(obj, X, cv, DUNDEF, FALSE, F_COLOR(0, 0, 0), 1.);
		//		lno[1] = GLobj_Add_Vert(obj, X + dx + 2., cv, DUNDEF, FALSE, F_COLOR(0, 0, 0), 1.);
		//		GLobj_Add_Poly(obj, DIM_2D, 2, lno, GL_LINE_STRIP, 0.5f);
		//		//
		//		if (i < NUM - 1) {	// 数値
		//			Set_Double_Str(VAL[i], &strnum, 1);
		//			strcpy(str, strnum);
		//			GLobj_Add_Text(&Gp, Bid, DIM_2D, str, cfont, PM.Lstyle,
		//				PM.Lh, PM.Lw, X + dx + 4., cv - 0.2*PM.Lh, DUNDEF,
		//				F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
		//				GetBValue(PM.Col_LegendChar)));
		//		}
		//		//
		//		Fcol = F_COLOR(GetRValue(COL[i]), GetGValue(COL[i]), GetBValue(COL[i]));
		//		no[2] = GLobj_Add_Vert(obj, X + dx, cv, DUNDEF, FALSE, Fcol, 1.);
		//		no[3] = GLobj_Add_Vert(obj, X, cv, DUNDEF, FALSE, Fcol, 1.);
		//		//
		//		GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 1.f);
		//		//
		//		no[0] = no[3];
		//		no[1] = no[2];
		//		//
		//	}
		//	GLobj_Add_Text(&Gp, Bid, DIM_2D, "Legend ", "Times New Roman", FONT_REGULAR,
		//		(int)(dy / 1.5), (int)(dy / 4), X + 0.1*dx, cv + 0.5*dy, DUNDEF,
		//		F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
		//		GetBValue(PM.Col_LegendChar)));
		//}
		//
	}
	//-------------------------------------------------------------------------
	Fcol = F_COLOR(240,240,240);
	X -=10.;
	Y -= Span;
	//
	no[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, FALSE);
	no[1] = GLobj_Add_Vert(obj, X+DX, Y, DUNDEF, FALSE);
	no[2] = GLobj_Add_Vert(obj, X+DX, DY, DUNDEF, FALSE);
	no[3] = GLobj_Add_Vert(obj, X, DY, DUNDEF, FALSE);
	//
	GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 1., Fcol);
	//---------------------------------------------------------------------
	PM.Area_Legend.top   = (LONG)(cv+Span);
	PM.Area_Legend.right = (LONG)(PM.Pos_Legend.x + 2 * Span);
	//
	PM.Change_Legend = FALSE;
	PM.B_Disp_Legend = TRUE;
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, Bid, TRUE);
	//
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   LAND USE  LEGEND
/// 201602  SOILとCOVERに名前を入れる。

int		CRRI_GUIView::Make_Decimal_Legend()
{
	int				Bid = OBJID_LEGEND;
	GL_OBJECT*		obj = &Gp.Gobj[Bid];

	// --------------------------------------------------------------------------------------------
	// 開始時、連続・離散表示の指示、閾値の変更等
	//
	FCOLOR		Fcol;
	char			str[128], cfont[64];
	double		X = PM.Pos_Legend.x, Y = PM.Pos_Legend.y;
	int			Span = PM.Lsize;
	double		cv, dx, dy, DX, DY, len;
	int			no[4], lno[2];
	CString		strnum;
	char			sunit[32];
	CString label = "";

	// Change Variable
	int			NUM;
	COLORREF*	COL;
	//
	NUM = PM.Dcol[CDATA].num;

	if (CDATA == LU_FILE) NUM = DSET.LUnum + 1;

	if (PM.B_UseJFlow && CDATA == LU_FILE) {
		COL = PM.Dcol[LU_FILE_JP].Rcol;
	}
	else {
		COL = PM.Dcol[CDATA].Rcol;
		if (PM.B_UseJFlow && CDATA == LAND_COVER) {
			NUM = 6;
		}
	}

	//
	PM.Area_Legend.bottom = (LONG)PM.Pos_Legend.y;
	PM.Area_Legend.left = (LONG)PM.Pos_Legend.x;
	//
	GLobj_Init(obj, 200, 100);
	DX = DY = DUNDEF;
	//
	strcpy(cfont, Fonts[PM.Lfont]);

	if (TRUE) {			// 横置きは考えない
		dx = dy = Span;	// Default 18
		//
			for (int i = 0; i<NUM; i++) {		// 0 はNODATA
				cv = Y + dy*i;
				if (i == 0) {
					switch (CDATA) {
						case LU_FILE: strcpy(sunit, "Land use"); break;
						case LAND_COVER: strcpy(sunit, "Land cover"); break;
						case LAND_SOIL: strcpy(sunit, "Soil"); break;
					}
					//
					no[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, TRUE);
					no[1] = GLobj_Add_Vert(obj, X + dx, Y, DUNDEF, TRUE);
					GLobj_Add_Text(&Gp, Bid, DIM_2D, sunit, "Times New Roman", FONT_REGULAR,
						(int)(Span*0.8), (int)(Span*0.3), X, cv - dy*0.8, DUNDEF,
						F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
						GetBValue(PM.Col_LegendChar)));
				}
				no[2] = GLobj_Add_Vert(obj, X + dx, cv + dy, DUNDEF, TRUE);
				no[3] = GLobj_Add_Vert(obj, X, cv + dy, DUNDEF, TRUE);
				//
				if (i < NUM) {
					Fcol = F_COLOR(GetRValue(COL[i]), GetGValue(COL[i]), GetBValue(COL[i]));
					GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 1., Fcol);
				}
				//
				if (i == 0) strnum = "ND";
				else	 {
					if (CDATA == LU_FILE && !PM.B_UseJFlow) {
						if (i <= NUM) strnum.Format("%d", i);
						else			strnum = _T("");
					}
					else if (CDATA == LU_FILE && PM.B_UseJFlow) {
						if (i < NUM) {
							switch (i) {
								case 1: 
									label = "Paddy field";
									break;
								case 2: 
									label = "Plowed field";
									break;
								case 3: 
									label = "Mountainous region";
									break;
								case 4: 
									label = "Urban";
									break;
								case 5: 
									label = "Water area";
									break;
							}
							strnum.Format("%d %s", i, label);
						} else {
							strnum = _T("");
						}
					}
					else if (CDATA == LAND_COVER) {
						if (i < NUM) {
							strnum.Format("%d:%s", i, Cover_Name[i - 1]);
						}
						else {
							strnum = _T("");
						}
					}
					else if (CDATA == LAND_SOIL) strnum.Format("%d:%s", i,Soil_Name[i - 1]);
				}
				//
				strcpy(str, strnum);
				GLobj_Add_Text(&Gp, Bid, DIM_2D, str, cfont, PM.Lstyle,
					(int)(Span*0.8), (int)(Span*0.3), X + dx+Span/2, cv + Span*0.2, DUNDEF,
					F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
					GetBValue(PM.Col_LegendChar)));

				len = strlen(str)*Span*0.3 + dx;
				if (DX < len) DX = len;
				//
				no[0] = no[3];
				no[1] = no[2];
			}
			//GLobj_Add_Text(&Gp, Bid, DIM_2D, "Legend ", "Times New Roman", FONT_REGULAR,
			//	(int)Span, (int)(Span*0.3), X + 0.1*dx, cv + 1.2*dy, DUNDEF,
			//	F_COLOR(GetRValue(PM.Col_LegendChar), GetGValue(PM.Col_LegendChar),
			//	GetBValue(PM.Col_LegendChar)));
		DY = cv + 1.2*dy;
	}
	//-------------------------------------------------------------------------
	Fcol = F_COLOR(240, 240, 240);
	X -= 10.;
	Y -= Span;
	//DY -= dy;
	if (CDATA == LAND_SOIL) DX = 150.;
	else if (CDATA == LU_FILE) DX = 80.;
	if ((CDATA == LU_FILE || CDATA == LAND_COVER) && PM.B_UseJFlow) {
		DY = 525;
		DX = 220;
	}

	//
	no[0] = GLobj_Add_Vert(obj, X, Y, DUNDEF, FALSE);
	no[1] = GLobj_Add_Vert(obj, X + DX, Y, DUNDEF, FALSE);
	no[2] = GLobj_Add_Vert(obj, X + DX, DY, DUNDEF, FALSE);
	no[3] = GLobj_Add_Vert(obj, X, DY, DUNDEF, FALSE);
	//
	GLobj_Add_Poly(obj, DIM_2D, 4, no, GL_POLYGON, 1., Fcol);
	//---------------------------------------------------------------------
	PM.Area_Legend.top = (LONG)(cv + Span);
	PM.Area_Legend.right = (LONG)(PM.Pos_Legend.x + 2 * Span);
	//
	PM.Change_Legend = FALSE;
	PM.B_Disp_Legend = TRUE;
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, Bid, TRUE);
	//
	return 0;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  COLOR DLG
void		CRRI_GUIView::OnBnClickedButton401()
{
	COMMENT(" ");
	if (!PM.Model) return;
	//
	if (CDATA == LU_FILE && DSET.LUnum > 21)  {
		MessageBox("The explanatory notes editing is not made that there many data.\n  Automatic color sequence", "Alarm", MB_OK | MB_ICONASTERISK);
		ERR_RETURN("Sorry");
	}
	if ((CDATA >= HS_WLEV_FILE && CDATA <= DIV_FILE) || CDATA == LOCATION_FILE) return;
	///----------------------------------------------------------------------------------
	//
	PM.Change_DCOL = FALSE;
	if (CDATA == LAND_COVER || CDATA == LAND_SOIL || CDATA == LU_FILE) {
		CMultiColor   CMDlg;
		if (CMDlg.DoModal() == IDCANCEL) return;
	}
	else if (CDATA == SED_FILE) {
		CDataColorSed dlgDataColor(m_BootPath, &PM);
		dlgDataColor.SetTitle(std::string("Data Color [ SED ]"));

		int ret = dlgDataColor.DoModal();
		if (ret == IDCANCEL) return;
		else if (ret == IDRETRY) {
			ERR_RETURN("** Error ** Boot failure... Please retry..!");
		}
	}
	else {
		CDataColor	COLdlg;
		int			ret;

		COLdlg.Title.Format("Data Color [ %s ]", MODEL_EDIT_NAME[CDATA]);
		COLdlg.Boot = Gp.m_CurrentPath;
		//
		ret = COLdlg.DoModal();
		if (ret == IDCANCEL) return;
		else if (ret == IDRETRY) {
			ERR_RETURN("** Error ** Boot failure... Please retry..!");
		}
	}
	//
	if (!PM.Change_DCOL) return;
	///----------------------------------------------------------------------------------
	//
	Change_Cursor(&Gp, IDC_WAIT);
	//
	if (CDATA <= GAMPT_FILE || CDATA == POTENT_FILE) {
		PM.B_Disp_Legend = TRUE;
		Make_LEGEND();
	}
	else {
		PM.B_Disp_Legend = FALSE;
		GLobj_Delete(&Gp, OBJID_LEGEND);
	}
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_LEGEND, TRUE);
	//
	if (CDATA == RAIN_FILE || CDATA == POTENT_FILE) {		// 時間に関係なく累積値を表示
		Make_TS_Model();
		if (Gp.Gobj[OBJID_TS].pnum != 0) GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
		else { Gp.Gobj[OBJID_TS].display = FALSE; GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE); }
		//
		if (DSET.RGnum != 0) {
			Make_GROUND_OBS();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_GROUND_OBS, TRUE);
		}
	}
	if ((CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE) || CDATA >= LAND_COVER){
		Change_Cursor(&Gp, IDC_WAIT);
		Make_Mesh_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
		RefreshSedRectLine();
	}
	//
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  EDIT WINDOW 
void		CRRI_GUIView::Display_EditWindow(int xid, int yid)
{
	IF_STAT(DISP_EDITWIN) {
		EDDlg->OnCancel();
		STAT(DISP_EDITWIN) = TRUE;
	}
	// Data Set
	PM.Cam_Dir = CAM_DIR_UP;
	//
	if (xid != UNDEF) PM.CX = xid;
	if (yid != UNDEF) PM.CY = yid;
	
	if (!CopyDataFromMesh(CDATA, PM.Values, MESH, PM, std::vector<int>{RAIN_FILE, ADIR_FILE})) return;

	EDDlg = new CEDITDLG;
	EDDlg->Create(IDD_EDITDLG, this);
	//
	EDDlg->m_Parent = this;
	//
	PM.Data_Change_Cnt = 0;	/// 変更の全体数
	//
	Edit_Mesh_Model();		/// 編集用
	//
	EDDlg->ShowWindow(SW_SHOW);
	STAT(DISP_EDITWIN) = TRUE;
}
//_____________________________________________________
//  編集終了処理
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		CRRI_GUIView::Save_Manager()
{
	int		FFormat, FOrder;
	//
	if (PM.Edit_Result == 0) {			// IDCANCEL
		GLobj_Delete(&Gp, OBJID_EDIT);
		Gp.Gobj[OBJID_MESH].display = TRUE;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	}
	if (PM.Edit_Result == 1) {	//	Save -> DSET にコピー　上書き保存については DSET.Need_Save 
		//
		CopyDataToMesh(CDATA, PM.Values, MESH, PM);

		//
		if (CDATA < FILE_IN_NUM) { FFormat = File_Format[CDATA]; FOrder = File_Order[CDATA]; }
		else                     FFormat = FOrder = 0;		/// Cover Soil
		//
		Write_Data_File(CDATA, FFormat, FOrder, DSET, PM, MESH);
		GLobj_Delete(&Gp, OBJID_EDIT);
		//
		if (PM.Data_Change_Cnt != 0) {
			Make_Mesh_Model();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
			RefreshSedRectLine();
		}
		else   {
			Gp.Gobj[OBJID_MESH].display = TRUE;
			GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_MESH, TRUE);
		}
	}
	else if (PM.Edit_Result == 2) {	//	Save as 別名保存
		if (CDATA < FILE_IN_NUM) { FFormat = File_Format[CDATA]; FOrder = File_Order[CDATA]; }
		else                     FFormat = FOrder = 0;		// Cover Soil
		//
		WriteAs_Data_File(CDATA, FFormat, FOrder, DSET, PM, MESH);
		//
		GLobj_Delete(&Gp, OBJID_EDIT);
		Gp.Gobj[OBJID_MESH].display = TRUE;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	}

	PM.Save_Proc = FALSE;
	PM.Edit_Result = 0;
}
void		CRRI_GUIView::Term_Manager()
{
	Save_Manager();
	//
	GLobj_Delete(&Gp, OBJID_MOUSE_BAND);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MOUSE_BAND, TRUE);
	//
	STAT(DISP_EDITWIN) = FALSE;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///  CHANGE MESH_LINE COLOR 
// Slope Mesh
void CRRI_GUIView::Get_MESH_COLOR(int id)
{
	CColorDialog CC;
	if (CC.DoModal() == IDCANCEL) return;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	PM.COL_MESH[id] = CC.GetColor();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}
void CRRI_GUIView::OnStnDblclickMeshcolor1(){ Get_MESH_COLOR(ID_MESH); }
// River Mesh
void CRRI_GUIView::OnStnDblclickMeshcolor2(){ Get_MESH_COLOR(ID_MESH_R); }
// HS Mesh
void CRRI_GUIView::OnStnDblclickMeshcolor3(){ Get_MESH_COLOR(ID_MESH_HS); }
// Model Frame
void CRRI_GUIView::OnStnDblclickMeshcolor4()
{
	CColorDialog CC;
	if (CC.DoModal() == IDCANCEL) return;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	PM.Col_Frame = CC.GetColor();
	Make_Mesh_Area();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_AREA, TRUE);
}
// Observatory
void CRRI_GUIView::OnStnDblclickMeshcolor5()
{
	CColorDialog CC;
	if (CC.DoModal() == IDCANCEL) return;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	PM.Col_Observatory = CC.GetColor();
	Make_GROUND_OBS();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_GROUND_OBS, TRUE);
}
// HR MESH
void CRRI_GUIView::OnStnDblclickMeshcolor6(){ Get_MESH_COLOR(ID_MESH_HR); }
// Slope Discharge Mesh
void CRRI_GUIView::OnStnDblclickMeshcolor7(){ Get_MESH_COLOR(ID_MESH_QS); }
// River Discharge Mesh
void CRRI_GUIView::OnStnDblclickMeshcolor8(){ Get_MESH_COLOR(ID_MESH_QR); }
// DAM Mesh
void CRRI_GUIView::OnStnDblclickMeshcolor9(){ Get_MESH_COLOR(ID_MESH_DAM); }
// DIVIDED MESH
void CRRI_GUIView::OnStnDblclickMeshcolor10(){ Get_MESH_COLOR(ID_MESH_DIV); }
// LOCATION MESH
void CRRI_GUIView::OnStnDblclickMeshcolor11(){ Get_MESH_COLOR(ID_MESH_LOC); }
//
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CHANGE MESH ALPHA
void CRRI_GUIView::OnNMCustomdrawSliderTrans2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//
	UDT;
	PM.Data_Alpha = (10 - c_SliderDataT.GetPos()) / 10.;
	PM.Dcol[CDATA].alpha = PM.Data_Alpha;
	//
	if (CDATA == RAIN_FILE || CDATA == POTENT_FILE) {
		for (int i = 0; i < Gp.Gobj[OBJID_TS].pnum; i++) {
			Gp.Gobj[OBJID_TS].poly[i].Alpha = PM.Data_Alpha;
		}
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
	}
	else {
		for (int i = 0; i < Gp.Gobj[OBJID_MESH].pnum; i++) {
			Gp.Gobj[OBJID_MESH].poly[i].Alpha = PM.Data_Alpha;
		}
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
	}
	//
	CWnd*	cw = GetDlgItem(ID_PICT);
	cw->SetFocus();
//
	*pResult = 0;
}
void CRRI_GUIView::OnNMCustomdrawSliderTrans(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//
	UDT;
	PM.Back_Alpha = (10 - c_SliderBackT.GetPos()) / 10.;
	for (int i = 0; i < Gp.Gobj[OBJID_BACK].pnum; i++) {
		Gp.Gobj[OBJID_BACK].poly[i].Alpha = PM.Back_Alpha;
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_BACK, TRUE);
	//
	CWnd*	cw = GetDlgItem(ID_PICT);
	cw->SetFocus();
	*pResult = 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  表示のＯＮ，ＯＦＦ

void CRRI_GUIView::OnBnClickedCheckOp1()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_1);
	if (cc->GetCheck()) 	{
		PM.B_Back = TRUE;
		Gp.Gobj[OBJID_BACK].display = TRUE;
	}
	else {
		PM.B_Back = FALSE;
		Gp.Gobj[OBJID_BACK].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp3()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_3);
	if (cc->GetCheck()) 	{
		PM.B_ColorMesh = TRUE;
		if (CDATA == RAIN_FILE || CDATA == POTENT_FILE) Gp.Gobj[OBJID_TS].display = TRUE;
		else                                        Gp.Gobj[OBJID_MESH].display = TRUE;
	}
	else {
		PM.B_ColorMesh = FALSE;
		if (CDATA == RAIN_FILE || CDATA == POTENT_FILE) Gp.Gobj[OBJID_TS].display = FALSE;
		else                                        Gp.Gobj[OBJID_MESH].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp2()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_2);
	if (cc->GetCheck()) 	{
		PM.B_MeshLine = TRUE;
		Gp.Gobj[OBJID_LINE].display = TRUE;
	}
	else {
		PM.B_MeshLine = FALSE;
		Gp.Gobj[OBJID_LINE].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp4()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_4);
	if (cc->GetCheck()) 	{
		PM.B_ScreenTool = TRUE;
		Gp.Gobj[OBJID_TOOL].display = TRUE;
	}
	else {
		PM.B_ScreenTool = FALSE;
		Gp.Gobj[OBJID_TOOL].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_TOOL, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp5()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_5);
	if (cc->GetCheck()) 	{
		PM.B_Disp_Ground = TRUE;
		Gp.Gobj[OBJID_GROUND_OBS].display = TRUE;
	}
	else {
		PM.B_Disp_Ground = FALSE;
		Gp.Gobj[OBJID_GROUND_OBS].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_GROUND_OBS, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp6()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_6);
	if (cc->GetCheck()) 	{
		PM.B_Disp_Frame = TRUE;
		Gp.Gobj[OBJID_AREA].display = TRUE;
	}
	else {
		PM.B_Disp_Frame = FALSE;
		Gp.Gobj[OBJID_AREA].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_AREA, TRUE);
}
void CRRI_GUIView::OnBnClickedCheckOp7()
{
	CButton*		cc = (CButton*)GetDlgItem(IDC_CHECK_OP_7);
	if (cc->GetCheck()) 	{
		PM.B_Disp_Legend = TRUE;
		Gp.Gobj[OBJID_LEGEND].display = TRUE;
	}
	else {
		PM.B_Disp_Legend = FALSE;
		Gp.Gobj[OBJID_LEGEND].display = FALSE;
	}
	//
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_LEGEND, TRUE);
}


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RIVER SELECT EDIT MODE TOOL

void CRRI_GUIView::Disp_Select_RivMesh()
{
	GL_OBJECT*		obj = &Gp.Gobj[OBJID_SELECT];
	GLobj_Delete(&Gp, OBJID_SELECT);
	GLobj_Init(obj, SI.Num * 5, SI.Num + 5);		// 余裕
	//
	int		no[4];
	double	x, y;
	for (int m = 0; m < SI.Num; m++){
		x = (double)SI.HV[m].x;
		y = (double)SI.HV[m].y;
		no[0] = GLobj_Add_Vert(obj, x, y, SELECT_Z, FALSE);
		no[1] = GLobj_Add_Vert(obj, x + 1., y, SELECT_Z, FALSE);
		no[2] = GLobj_Add_Vert(obj, x + 1., y + 1., SELECT_Z, FALSE);
		no[3] = GLobj_Add_Vert(obj, x , y + 1., SELECT_Z, FALSE);
		//
		GLobj_Add_Poly(obj, 4, no, GL_POLYGON, F_COLOR(255, 0, 180));
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SELECT, TRUE);
}

BOOL	CRRI_GUIView::Search_River_Path()
{
	int			Hx, Hy, Lx, Ly,dir;
	int			idx, idy;
	int			oldNum = SI.Num;
	IXYCOORD		pos[2];
	BOOL			ORDER = FALSE;
	//
	pos[0].x = SI.HV[0].x;			// 見つからなかった場合の保存
	pos[0].y = SI.HV[0].y;
	pos[1].x = SI.HV[1].x;
	pos[1].y = SI.HV[1].y;

	if (MESH[SI.HV[0].y][SI.HV[0].x].Adem >= MESH[SI.HV[1].y][SI.HV[1].x].Adem) {
		Hx = SI.HV[0].x; Hy = SI.HV[0].y; Lx = SI.HV[1].x; Ly = SI.HV[1].y;
	}
	else { Hx = SI.HV[1].x; Hy = SI.HV[1].y; Lx = SI.HV[0].x; Ly = SI.HV[0].y; }
	//
RETRY:
	if (!ORDER) {			// 最初
		SI.Num = 0;
		idx = SI.HV[SI.Num].x = Hx;
		idy = SI.HV[SI.Num++].y = Hy;
	}
	else {
		idx = Lx;
		idy = Ly;
		Lx = Hx;
		Ly = Hy;
		Hx = idx;
		Hy = idy;
		//
		SI.Num = 0;
		SI.HV[SI.Num].x = Hx;
		SI.HV[SI.Num++].y = Hy;
	}
	//							標高の高いほうから、流下方向を探っていく。
	while (TRUE){
		dir = UNDEF;
		for (int d = 0; d < 8; d++) {
			if (MESH[idy][idx].Adir == Ddirect[d]) { dir = d; break; }
		}
		if (dir == UNDEF) {	// 方向が定義されていない　or dem が反対
			if (ORDER) {
				SI.HV[0].x = pos[0].x;
				SI.HV[0].y = pos[0].y;
				SI.HV[1].x = pos[1].x;
				SI.HV[1].y = pos[1].y;
				SI.Num = 2;
				return FALSE;
			}
			ORDER = TRUE; goto RETRY;
		}
		//
		idx += offx[dir];
		idy += offy[dir];
		//
		SI.HV[SI.Num].x  = idx;
		SI.HV[SI.Num++].y = idy;
		if (idx == Lx && idy == Ly) break;
		//
		if (SI.Num == SI.Mem) {
			SI.Mem += 50;
			if ((SI.HV = (IXYCOORD*)realloc(SI.HV, SI.Mem*sizeof(IXYCOORD))) == NULL ||
				(SI.ID = (IXYCOORD*)realloc(SI.ID, SI.Mem*sizeof(IXYCOORD))) == NULL  ) return FALSE;
		}
	}
	// 
	return TRUE;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 土研ＲＲＩの実行
void CRRI_GUIView::OnBnClickedButton404()
{
//	CString	Org, Tar;
	int			ret;
	char		Org[SIZE_1K], Tar[SIZE_1K];
	//
	if(MessageBox("Run RRI Program ... OK ?", "confirm", MB_YESNO | MB_ICONQUESTION) == IDNO ) return;
	//
#ifdef   VER_64
	sprintf(Org, "%s\\RRI_CONTENTS\\BIN\\0_rri_1_4_2.exe", m_BootPath);
	sprintf(Tar, "%s\\0_rri_1_4_2.exe", DSET.Proj_Folder);
#else
	sprintf(Org, "%s\\RRI_CONTENTS\\BIN32\\0_rri_1_4_2.exe", m_BootPath);
	sprintf(Tar, "%s\\0_rri_1_4_2.exe", DSET.Proj_Folder);
#endif
	//
	if (!(ret=CopyFile(Org, Tar, FALSE)) )	{			// ﾌｧｲﾙコピー
		LPVOID	lpMessageBuffer;
		CString	str;
		//
//		What_Is_Error(lpMessageBuffer);
		//void		What_Is_Error(LPVOID lpMessageBuffer)
		//{
		//	//... 文字列が表示されます。
		//	// システムによって確保されたバッファを開放します。
		//	FormatMessage(
		//		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		//		FORMAT_MESSAGE_FROM_SYSTEM,
		//		NULL,
		//		GetLastError(),
		//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト ユーザー言語 
		//		(LPTSTR)&lpMessageBuffer,
		//		0,
		//		NULL);
		//}

//		str.Format("** Error ** Missed copy Program File\n-->[ %d ] %s", GetLastError(), lpMessageBuffer);

		MessageBox(str, "Alerm", MB_OK|MB_ICONERROR);
//		LocalFree(lpMessageBuffer);
		return;
	}
	//
	::SetCurrentDirectory(DSET.Proj_Folder);
	system(RRI_PROGRAM);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRRI_GUIView::OnBnClickedButtonRri()
{
	CRI_DLG		CS(this);
	if (CS.DoModal() == IDCANCEL) return;
	//
	int		ID=UNDEF;
	PM.DataNum = 0;
	c_ComboData.ResetContent();
	for (int i = 0; i < FILE_IN_USE; i++) {
		if (i == LU_FILE && DSET.in_avail[LU_FILE] && DSET.in_avail[LAND_COVER]) {
			c_ComboData.AddString(MODEL_EDIT_NAME[LAND_COVER]);
			if (CDATA == LAND_COVER) ID = PM.DataNum;
			PM.Data_Order[PM.DataNum++] = LAND_COVER;
			continue;
		}

		if (DSET.in_avail[i]) {
			c_ComboData.AddString(MODEL_EDIT_NAME[i]);
			if (i == CDATA) ID = PM.DataNum;
			PM.Data_Order[PM.DataNum++] = i;
		}
	}
	///
	// Cover or SOil
	if (DSET.b_CSexist) {
		c_ComboData.AddString(MODEL_EDIT_NAME[LAND_COVER]);
		if (CDATA == LAND_COVER) ID = PM.DataNum;
		PM.Data_Order[PM.DataNum++] = LAND_COVER;
		//
		c_ComboData.AddString(MODEL_EDIT_NAME[LAND_SOIL]);
		if (CDATA == LAND_SOIL) ID = PM.DataNum;
		PM.Data_Order[PM.DataNum++] = LAND_SOIL;
	}
	//
//	if (!DSET.in_avail[CDATA]) 	CDATA = ACC_FILE;
	for (int i = 0; i < PM.DataNum; i++) 
			if (CDATA == PM.Data_Order[i]){ ID = i; break; }

	c_ComboData.SetCurSel(ID);
	//
	Make_Mesh_Line();
	Make_Mesh_Model();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);

	RefreshSedRectLine();
}
///==================  ＩＤＳ 応答関数 ================================================

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  BACK COLOR
void CRRI_GUIView::OnIdsChangeBackcolor()
{
	CColorDialog	cdlg;
	COLORREF		cref;
	//
	if (cdlg.DoModal() == IDCANCEL) return;
	//
	cref = cdlg.GetColor();
	Gp.Bcolor = F_COLOR(GetRValue(cref), GetGValue(cref), GetBValue(cref));
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, ALL_OBJECTS, TRUE);
	//
	return;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RIVER PARAMETER
void CRRI_GUIView::OnIdsSetRivParameter()
{
	IFNOT_STAT(PROC_CONFIRM_MESH){ return; }
	//
	int Avcnt = 0;
	CString		str1, str2, str3, str;
	//
	if (DSET.in_use[WIDTH_FILE]) {
		str1.Format("Valid Width File [%s]\n", DSET.File_names[WIDTH_FILE]);
		Avcnt++;
	}
	else str1 = "Invalid Width File [ - Undefined- ] Unable to set Width value\n";
	if (DSET.in_use[DEPTH_FILE]) {
		str2.Format("Valid Depth File [%s]\n", DSET.File_names[DEPTH_FILE]);
		Avcnt++;
	}
	else str2 = "Invalid Depth File [ - Undefined- ] Unable to set Depth value\n";
	if (DSET.in_use[HEIGHT_FILE]) {
		str3.Format("Valid Depth File [%s]\n", DSET.File_names[HEIGHT_FILE]);
		Avcnt++;
	}
	else str3 = "Invalid Height File [ - Undefined- ] Unable to set Height value\n";
	//
	if (Avcnt != 0) {
		str = str1 + str2 + str3 + "Continue ?";
		if (MessageBox(str, "Ask", MB_YESNO | MB_ICONQUESTION) == IDNO) {
			Clear_Select();
			return;
		}
	}
	else {
		str = str1 + str2 + str3 + "Unable to Set River parameter..... !";
		MessageBox(str, "Invalid Operation", MB_OK | MB_ICONHAND);
		Clear_Select();
		return;
	}
	///
	//
	CSetRivCof		CSR;
	int				xid, yid;
	//
	if (Search_River_Path()) {
		Disp_Select_RivMesh();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SELECT, TRUE);
		//
		if (CSR.DoModal() == IDOK) {
			for (int m = 0; m < SI.Num; m++) {
				xid = SI.HV[m].x;
				yid = SI.HV[m].y;
				if (DSET.in_use[WIDTH_FILE]) {
					if (CSR.HowtoW == 0) MESH[yid][xid].Rwidth = CSR.Wid;
					else  MESH[yid][xid].Rwidth = CSR.Cw*pow((MESH[yid][xid].Acc*PM.Unit_Area), CSR.Sw);
				}
				if (DSET.in_use[DEPTH_FILE]) {
					if (CSR.HowtoD == 0) MESH[yid][xid].Rdepth = CSR.Dep;
					else  MESH[yid][xid].Rdepth = CSR.Cd*pow((MESH[yid][xid].Acc*PM.Unit_Area), CSR.Sd);
				}
				if (DSET.in_use[HEIGHT_FILE]) {
					MESH[yid][xid].Bheight = CSR.H;
				}
			}
		}
	}
	else {
		str1 = "** Error ** cannot find river path. Check dem\n";
		str2.Format("  Cell 1 dem = %.2lf\n", MESH[SI.HV[0].y][SI.HV[0].x].Adem);
		str3.Format("  Cell 2 dem = %.2lf\n", MESH[SI.HV[1].y][SI.HV[1].x].Adem);
		str = str1 + str2 + str3;
		MessageBox(str, "warning", MB_OK | MB_ICONHAND);
		Clear_Select();
		return;
	}
	Clear_Select();
	Disp_Controls();
	//
	//
	if (DSET.in_use[WIDTH_FILE]) {
		DSET.in_use[WIDTH_FILE] = DSET.in_avail[WIDTH_FILE] = TRUE;
		Write_Data_File(WIDTH_FILE, File_Format[WIDTH_FILE], File_Order[WIDTH_FILE], DSET, PM, MESH);
	}
	if (DSET.in_use[DEPTH_FILE]) {
		DSET.in_use[DEPTH_FILE] = DSET.in_avail[DEPTH_FILE] = TRUE;
		Write_Data_File(DEPTH_FILE, File_Format[DEPTH_FILE], File_Order[DEPTH_FILE], DSET, PM, MESH);
	}
	if (DSET.in_use[HEIGHT_FILE]) {
		DSET.in_use[HEIGHT_FILE] = DSET.in_avail[HEIGHT_FILE] = TRUE;
		Write_Data_File(HEIGHT_FILE, File_Format[HEIGHT_FILE], File_Order[HEIGHT_FILE], DSET, PM, MESH);
	}
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
	Make_Mesh_Model();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);
	RefreshSedRectLine();

}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  LOCATION MAP

void CRRI_GUIView::OnIdsBoundaryPos()
{
	int		old,base = DSET.Lnum;
	BOOL		exist;
	//
	if (DSET.Lmem == 0) {
		DSET.Lnum = 0;
		DSET.Lmem = 50;
		if ((DSET.LCpos = (LOCATE_INFO*)calloc(DSET.Lmem, sizeof(LOCATE_INFO))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
	}
	else if ((base + SI.Num) > DSET.Lmem) {
		old = DSET.Lmem;
		DSET.Lmem += 50;
		if ((DSET.LCpos = (LOCATE_INFO*)realloc(DSET.LCpos, DSET.Lmem*sizeof(LOCATE_INFO))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
	}
	//
	int  cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (base != 0) {
			for (int k = 0; k < base; k++) {
				if (DSET.LCpos[k].mx == SI.ID[i].x && DSET.LCpos[k].mz == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		DSET.LCpos[base + i].mx = SI.ID[i].x;
		DSET.LCpos[base + i].mz = SI.ID[i].y;
		DSET.LCpos[base + i].X = SI.HV[i].x;
		DSET.LCpos[base + i].Z = SI.HV[i].y;
		DSET.LCpos[base + i].Hid = (int)SI.HV[i].x;
		DSET.LCpos[base + i].Vid = (int)SI.HV[i].y;
		cnt++;
	}
	DSET.Lnum += cnt;
	//
	//
	CEditLocation    CEL;
	if (CEL.DoModal() == IDCANCEL) {
		for (int i = base; i < DSET.Lnum; i++) memset(&DSET.LCpos[i], 0, sizeof(LOCATE_INFO));
		DSET.Lnum = base; 
		Clear_Select();
		return;
	}
	if (DSET.Lnum <= 0 && DSET.Damc_Mem == 0) {	// 内部で削除されて、アウトポジションが0になった
		Clear_Select();
		DSET.in_use[LOCATION_FILE] = DSET.in_avail[LOCATION_FILE] = FALSE;
		Write_RRI_INPUT(DSET);
		//
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	//
	CString		fname;
	int			ret;
	if (!DSET.in_use[LOCATION_FILE]) {
		fname.Format("File Name of Location [ %s ] is OK ?", DSET.Input_names[LOCATION_FILE]);
		ret = MessageBox(fname, "Ask", MB_YESNO | MB_ICONQUESTION);
		if (ret == IDNO) {
			if (!Button_File(FALSE, &fname, m_RecentPath, "Location", "txt")) {
				for (int i = base; i < DSET.Damc_Num; i++) memset(&DSET.DAMC[i], 0, sizeof(DAMCNT));
				DSET.Damc_Num = base;
				Clear_Select();
				return;
			}
			strcpy(DSET.File_names[LOCATION_FILE], fname);
			Get_Relative_Path(DSET.File_names[LOCATION_FILE], DSET.Proj_Folder, DSET.Input_names[LOCATION_FILE]);
		}
	}
	//
	for (int i = 0; i < DSET.Lnum; i++) {
		if (MESH[DSET.LCpos[i].Vid][DSET.LCpos[i].Hid].flag < ID_MESH_LOC)
			MESH[DSET.LCpos[i].Vid][DSET.LCpos[i].Hid].flag += ID_MESH_LOC;
		strcpy(MESH[DSET.LCpos[i].Vid][DSET.LCpos[i].Hid].name, DSET.LCpos[i].name);
	}
	//
	DSET.in_use[LOCATION_FILE] = DSET.in_avail[LOCATION_FILE] = TRUE;
	Write_Data_File(LOCATION_FILE, File_Format[LOCATION_FILE], File_Order[LOCATION_FILE], DSET, PM, MESH);
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}

void CRRI_GUIView::OnIdsExtractSed() {
	auto dataIdX = LastSelectPoint.x, dataIdY = LastSelectPoint.y;
	auto pIdX = dataIdX + 1, pIdY = PM.MVnum - dataIdY;

	Change_Cursor(&Gp, IDC_WAIT);

	std::string fPath;
	do {
		if (!ExtractSubBasin(fPath, pIdX, pIdY))  break;

		//display temp sub basin data
		MeshDataHeader subBDHeader;
		CPoint ofstSet;
		if (!LoadSubBasinHeader(fPath, &subBDHeader, &ofstSet)) break;

		int** data = Make_Matrix(subBDHeader.ncols, subBDHeader.nrows, 0);

		do {
			if (!LoadSubBasinData(fPath, subBDHeader, data)) break;
			if (!DrawTempSubBasinData(ofstSet, subBDHeader, data)) break;

			auto val = MESH[dataIdY][dataIdX].Sed;
			CSetSedNo    dSetSedNo(val >= 0 ? val : 0, &PM.Dcol[SED_FILE], this);
			if (dSetSedNo.DoModal() == IDOK) {
				auto sedNo = dSetSedNo.SelectedSedNo();

				//backup data
				int** oriData = Make_Matrix(PM.MHnum, PM.MVnum, 0);
				for (int v = 0; v < PM.MVnum; v++) {
					for (int h = 0; h < PM.MHnum; h++) {
						oriData[v][h] = MESH[v][h].Sed;
					}
				}

				for (int y = 0; y < subBDHeader.nrows; y++) {
					auto v = PM.MVnum - 1 - (y + ofstSet.y);
					for (int x = 0; x < subBDHeader.ncols; x++) {
						if (data[y][x] == ms_SubBasinDataVal) MESH[v][x + ofstSet.x].Sed = sedNo;
					}
				}

				if (!UpdateSedFile()) {
					//rollback data
					for (int v = 0; v < PM.MVnum; v++) {
						for (int h = 0; h < PM.MHnum; h++) {
							MESH[v][h].Sed = oriData[v][h];
						}
					}
				}
				Free_Matrix(PM.MVnum, oriData);
			}
		} while (0);
		
		Free_Matrix(subBDHeader.nrows, data);
	} while (0);

	RefreshSedRectLine();
	DeleteFileWithPath(fPath.c_str());
	Change_Cursor(&Gp, IDC_ARROW);
}

void CRRI_GUIView::OnIdsBoundaryDam()
{
	int		old, base = DSET.Damc_Num;
	//
	if (DSET.Damc_Mem == 0) {
		DSET.Damc_Mem = 50;
		if ((DSET.DAMC = (DAMCNT*)calloc(DSET.Damc_Mem, sizeof(DAMCNT))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
	}
	else if ((base + SI.Num) > DSET.Damc_Mem) {
		old = DSET.Damc_Mem;
		DSET.Damc_Mem += 50;
		if ((DSET.DAMC = (DAMCNT*)realloc(DSET.DAMC, DSET.Damc_Mem*sizeof(DAMCNT))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
		for (int i = base; i < DSET.Damc_Mem; i++) memset(&DSET.DAMC[i], 0, sizeof(DAMCNT));
	}
	//
	//
	BOOL		exist = FALSE;
	int		cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (base != 0) {
			for (int k = 0; k < base; k++) {
				if (DSET.DAMC[k].x == SI.ID[i].x && DSET.DAMC[k].y == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		DSET.DAMC[base + i].x = SI.HV[i].x;
		DSET.DAMC[base + i].y = SI.HV[i].y;
		cnt++;
	}
	DSET.Damc_Num += cnt;
	//
	//
	CEditDamCnt    CED;
	if (CED.DoModal() == IDCANCEL) {	// 選択されたダム候補がキャンセルされた
		for (int i = base; i < DSET.Damc_Num; i++) memset(&DSET.DAMC[i], 0, sizeof(DAMCNT));
		DSET.Damc_Num = base;
		Clear_Select();
		return;
	}
	//
	if (DSET.Damc_Num <= 0 && DSET.Damc_Mem == 0) {	// 内部で削除されて、ダムが0になった
		Clear_Select();
		DSET.in_use[DAM_CNT_FILE] = DSET.in_avail[DAM_CNT_FILE] = FALSE;
		Write_RRI_INPUT(DSET);
		//
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	//
	CString		fname;
	int			ret;
	if (!DSET.in_use[DAM_CNT_FILE]) {
		fname.Format("File Name of Dam  [ %s ] is OK ?", DSET.Input_names[DAM_CNT_FILE]);
		ret = MessageBox(fname, "Ask", MB_YESNO | MB_ICONQUESTION);
		if (ret == IDNO) {
			if (!Button_File(FALSE, &fname, m_RecentPath, "Dam", "txt")) {
				for (int i = base; i < DSET.Damc_Num; i++) memset(&DSET.DAMC[i], 0, sizeof(DAMCNT));
				DSET.Damc_Num = base;
				Clear_Select();
				return;
			}
			strcpy(DSET.File_names[DAM_CNT_FILE], fname);
			Get_Relative_Path(DSET.File_names[DAM_CNT_FILE], DSET.Proj_Folder, DSET.Input_names[DAM_CNT_FILE]);
		}		
	}
	//
	for (int i = 0; i < DSET.Damc_Num; i++) {
		if (MESH[DSET.DAMC[i].y][DSET.DAMC[i].x].flag >= ID_MESH_LOC) 
				MESH[DSET.DAMC[i].y][DSET.DAMC[i].x].flag = ID_MESH_DAM + ID_MESH_LOC;
		else     MESH[DSET.DAMC[i].y][DSET.DAMC[i].x].flag = ID_MESH_DAM;
		strcpy(MESH[DSET.DAMC[i].y][DSET.DAMC[i].x].name, DSET.DAMC[i].name);
	}
	DSET.in_use[DAM_CNT_FILE] = DSET.in_avail[DAM_CNT_FILE] = TRUE;
	//
	Write_Data_File(DAM_CNT_FILE, File_Format[DAM_CNT_FILE], File_Order[DAM_CNT_FILE], DSET, PM, MESH);
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
	//
}
void CRRI_GUIView::OnIdsBoundaryDiv()
{
	if (SI.Num != 2) return;
	//
	int		old, base = DSET.Div_Num;
	//
	if (DSET.Div_Mem == 0) {
		DSET.Div_Mem = 50;
		if ((DSET.DIVID = (DIVISION*)calloc(DSET.Div_Mem, sizeof(DIVISION))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
	}
	else if ((base + 1) >= DSET.Div_Mem) {
		old = DSET.Div_Mem;
		DSET.Div_Mem += 50;
		if ((DSET.DIVID = (DIVISION*)realloc(DSET.DIVID, DSET.Div_Mem*sizeof(DIVISION))) == NULL) {
			RETURN("** Error ** Cannot allocate memory");
		}
		for (int i = base; i < DSET.Div_Mem; i++) memset(&DSET.DIVID[i], 0, sizeof(DIVISION));
	}
	//
	//
	DSET.DIVID[base ].ox = SI.HV[0].x;
	DSET.DIVID[base ].oy = SI.HV[0].y;
	DSET.DIVID[base].tx = SI.HV[1].x;
	DSET.DIVID[base].ty = SI.HV[1].y;

	DSET.Div_Num ++;
	//
	//
	CEditDivide    CED;
	if (CED.DoModal() == IDCANCEL) {
		for (int i = base; i < DSET.Div_Num; i++) memset(&DSET.DIVID[i], 0, sizeof(DIVISION));
		DSET.Div_Num = base;
		Clear_Select();
		return;
	}
	if (DSET.Div_Num <= 0 && DSET.Div_Mem == 0) {	// 内部で削除されて、Diversionが0になった
		Clear_Select();
		DSET.in_use[DIV_FILE] = DSET.in_avail[DIV_FILE] = FALSE;
		Write_RRI_INPUT(DSET);
		//
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	//
	//
	CString		fname;
	int			ret;
	if (!DSET.in_use[DIV_FILE]) {
		fname.Format("File Name of Diversion [ %s ] is OK ?", DSET.Input_names[DIV_FILE]);
		ret = MessageBox(fname, "Ask", MB_YESNO | MB_ICONQUESTION);
		if (ret == IDNO) {
			if (!Button_File(FALSE, &fname, m_RecentPath, "Diversion", "txt")) {
				for (int i = base; i < DSET.Div_Num; i++) memset(&DSET.DIVID[i], 0, sizeof(DIVISION));
				DSET.Div_Num = base;
				Clear_Select();
				return;
			}
			strcpy(DSET.File_names[DIV_FILE], fname);
			Get_Relative_Path(DSET.File_names[DIV_FILE], DSET.Proj_Folder, DSET.Input_names[DIV_FILE]);
		}
	}
	//
	for (int i = 0; i < DSET.Div_Num; i++) {
		if (MESH[SI.HV[i].y][SI.HV[i].x].flag >= ID_MESH_LOC) MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_DIV + ID_MESH_LOC;
		else                                             MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_DIV;
	}
	DSET.in_use[DIV_FILE] = DSET.in_avail[DIV_FILE] = TRUE;
	//
	Write_Data_File(DIV_FILE, File_Format[DIV_FILE], File_Order[DIV_FILE], DSET, PM, MESH);
	Write_RRI_INPUT(DSET); B_Change_RRI = 0;
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}
void CRRI_GUIView::OnIdsBoundaryHs()
{
	if (PM.StTime == NULL || PM.EndTime == NULL) {	//シミュレーション時刻を設定
		CPeriod   CPD;
		if (CPD.DoModal() == IDCANCEL) return;
		//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
		DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
		//
		if (DSET.HSWLEV.set) {			// 既存の時間設定があった場合は、無効とする。
			SAFE_FREE(DSET.HSWLEV.time);
			for (int v = 0; v < DSET.HSWLEV.Smem; v++) SAFE_FREE(DSET.HSWLEV.val[v]);
			SAFE_FREE(DSET.HSWLEV.val);
			DSET.HSWLEV.Smem = DSET.HSWLEV.Span = 0;
		}
	}
	else Get_Period();

	CGroup   CG;
	int		ret;
	ret = CG.DoModal();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (ret == IDCANCEL ) {
		Clear_Select();
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (!DSET.HSWLEV.set) {
		DSET.HSWLEV.Smem = (60 > ((int)(DSET.Hours / 24) + 2)) ? 60 : ((int)(DSET.Hours / 24) + 2);
		DSET.HSWLEV.Mem = SI.Num * 2;
		Alloc_TIMESET(&DSET.HSWLEV);
	}
	else if (DSET.HSWLEV.Mem < DSET.HSWLEV.Num + SI.Num) {
		int oldmem = DSET.HSWLEV.Mem;
		int oldstep = DSET.HSWLEV.Smem;
		DSET.HSWLEV.Mem = DSET.HSWLEV.Num + SI.Num + 20;
		Realloc_TIMESET(oldmem, oldstep, &DSET.HSWLEV);
	}
	//
	int		id = DSET.HSWLEV.Num;
	//
	BOOL		exist = FALSE;
	int		cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (id != 0) {
			for (int k = 0; k < id; k++) {
				if (DSET.HSWLEV.pos[k].x == SI.ID[i].x && DSET.HSWLEV.pos[k].y == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		strcpy(DSET.HSWLEV.name[id], CG.s_Name);
		DSET.HSWLEV.pos[id].x = SI.HV[i].x;
		DSET.HSWLEV.pos[id].y = SI.HV[i].y;
		if (MESH[SI.HV[i].y][SI.HV[i].x].flag >= ID_MESH_LOC) MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_HS + ID_MESH_LOC;
		else                                             MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_HS;
		strcpy(MESH[SI.HV[i].y][SI.HV[i].x].name, CG.s_Name);
		//
		id++;
	}
	DSET.HSWLEV.Num = id;
	//
	DSET.in_avail[HS_WLEV_FILE] = DSET.in_use[HS_WLEV_FILE] = TRUE;
	//Write_RRI_INPUT(DSET); 
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}
void CRRI_GUIView::OnIdsBoundaryHr()
{
	if (PM.StTime == NULL || PM.EndTime == NULL) {	//シミュレーション時刻を設定
		CPeriod   CPD;
		if (CPD.DoModal() == IDCANCEL) return;
		//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
		DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	}
	else Get_Period();

	CGroup   CG;
	int		ret;
	ret = CG.DoModal();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (ret == IDCANCEL) {
		Clear_Select();
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (!DSET.HRWLEV.set) {
		DSET.HRWLEV.Smem = (60 > ((int)(DSET.Hours / 24) + 2)) ? 60 : ((int)(DSET.Hours / 24) + 2);
		DSET.HRWLEV.Mem = SI.Num * 2;
		Alloc_TIMESET(&DSET.HRWLEV);
	}
	else if (DSET.HRWLEV.Mem < DSET.HRWLEV.Num + SI.Num) {
		int oldmem = DSET.HRWLEV.Mem;
		int oldstep = DSET.HRWLEV.Smem;
		DSET.HRWLEV.Mem = DSET.HRWLEV.Num + SI.Num + 20;
		Realloc_TIMESET(oldmem, oldstep, &DSET.HRWLEV);
	}
	//
	int		id = DSET.HRWLEV.Num;
	//
	BOOL		exist = FALSE;
	int		cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (id != 0) {
			for (int k = 0; k < id; k++) {
				if (DSET.HRWLEV.pos[k].x == SI.ID[i].x && DSET.HRWLEV.pos[k].y == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		strcpy(DSET.HRWLEV.name[id], CG.s_Name);
		DSET.HRWLEV.pos[id].x = SI.HV[i].x;
		DSET.HRWLEV.pos[id].y = SI.HV[i].y;
		if (MESH[SI.HV[i].y][SI.HV[i].x].flag >= ID_MESH_LOC) MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_HR + ID_MESH_LOC;
		else                                             MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_HR;
		strcpy(MESH[SI.HV[i].y][SI.HV[i].x].name, CG.s_Name);
		//
		id++;
	}
	DSET.HRWLEV.Num = id;
	//
	DSET.in_avail[HR_WLEV_FILE] = DSET.in_use[HR_WLEV_FILE] = TRUE;
	//Write_RRI_INPUT(DSET); 
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}
void CRRI_GUIView::OnIdsBoundaryQs()
{
	if (PM.StTime == NULL || PM.EndTime == NULL) {	//シミュレーション時刻を設定
		CPeriod   CPD;
		if (CPD.DoModal() == IDCANCEL) return;
		//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
		DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	}
	else Get_Period();

	//
	CGroup   CG;
	int		ret;
	ret = CG.DoModal();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (ret == IDCANCEL) {
		Clear_Select();
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (!DSET.QSWLEV.set) {
		DSET.QSWLEV.Smem = (60 > ((int)(DSET.Hours / 24) + 2)) ? 60 : ((int)(DSET.Hours / 24) + 2);
		DSET.QSWLEV.Mem = SI.Num * 2;
		Alloc_TIMESET(&DSET.QSWLEV);
	}
	else if (DSET.QSWLEV.Mem < DSET.QSWLEV.Num + SI.Num) {
		int oldmem = DSET.QSWLEV.Mem;
		int oldstep = DSET.QSWLEV.Smem;
		DSET.QSWLEV.Mem = DSET.QSWLEV.Num + SI.Num + 20;
		Realloc_TIMESET(oldmem, oldstep, &DSET.QSWLEV);
	}
	//
	int		id = DSET.QSWLEV.Num;
	//
	BOOL		exist = FALSE;
	int		cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (id != 0) {
			for (int k = 0; k < id; k++) {
				if (DSET.QSWLEV.pos[k].x == SI.ID[i].x && DSET.QSWLEV.pos[k].y == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		strcpy(DSET.QSWLEV.name[id], CG.s_Name);
		DSET.QSWLEV.pos[id].x = SI.HV[i].x;
		DSET.QSWLEV.pos[id].y = SI.HV[i].y;
		if (MESH[SI.HV[i].y][SI.HV[i].x].flag >= ID_MESH_LOC) MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_QS + ID_MESH_LOC;
		else                                             MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_QS;
		strcpy(MESH[SI.HV[i].y][SI.HV[i].x].name, CG.s_Name);
		//
		id++;
	}
	DSET.QSWLEV.Num = id;
	//
	DSET.in_avail[QS_WLEV_FILE] = DSET.in_use[QS_WLEV_FILE] = TRUE;
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}
void CRRI_GUIView::OnIdsBoundaryQr()
{
	if (PM.StTime == NULL || PM.EndTime == NULL) {	//シミュレーション時刻を設定
		CPeriod   CPD;
		if (CPD.DoModal() == IDCANCEL) return;
		//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Rain = ts.GetTotalHours();		// RRI_Input.txt  Total Hours への反映
		DSET.Out_Num = Culc_Out_Hour(DSET.Hours);
	}
	else Get_Period();

	//
	CGroup   CG;
	int		ret;
	ret = CG.DoModal();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (ret == IDCANCEL) {
		Clear_Select();
		Make_Mesh_Line();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (!DSET.QRWLEV.set) {
		DSET.QRWLEV.Smem = (60 > ((int)(DSET.Hours / 24) + 2)) ? 60 : ((int)(DSET.Hours / 24) + 2);
		DSET.QRWLEV.Mem = SI.Num * 2;
		Alloc_TIMESET(&DSET.QRWLEV);
	}
	else if (DSET.QRWLEV.Mem < DSET.QRWLEV.Num + SI.Num) {
		int oldmem = DSET.QRWLEV.Mem;
		int oldstep = DSET.QRWLEV.Smem;
		DSET.QRWLEV.Mem = DSET.QRWLEV.Num + SI.Num + 20;
		Realloc_TIMESET(oldmem, oldstep, &DSET.QRWLEV);
	}
	//
	int		id = DSET.QRWLEV.Num;
	//
	BOOL		exist = FALSE;
	int		cnt = 0;
	for (int i = 0; i < SI.Num; i++) {
		// 重複の除去
		exist = FALSE;
		if (id != 0) {
			for (int k = 0; k < id; k++) {
				if (DSET.QRWLEV.pos[k].x == SI.ID[i].x && DSET.QRWLEV.pos[k].y == SI.ID[i].y){ exist = TRUE; break; }
			}
			if (exist) continue;
		}
		strcpy(DSET.QRWLEV.name[id], CG.s_Name);
		DSET.QRWLEV.pos[id].x = SI.HV[i].x;
		DSET.QRWLEV.pos[id].y = SI.HV[i].y;
		if (MESH[SI.HV[i].y][SI.HV[i].x].flag >= ID_MESH_LOC) MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_QR + ID_MESH_LOC;
		else                                             MESH[SI.HV[i].y][SI.HV[i].x].flag = ID_MESH_QR;
		strcpy(MESH[SI.HV[i].y][SI.HV[i].x].name, CG.s_Name);
		//
		id++;
	}
	DSET.QRWLEV.Num = id;
	//
	DSET.in_avail[QR_WLEV_FILE] = DSET.in_use[QR_WLEV_FILE] = TRUE;
	//Write_RRI_INPUT(DSET); 
	//
	Clear_Select();
	Make_Mesh_Line();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
}

//  LOCATION MAP Button Contorol

void CRRI_GUIView::OnBnClickedButtonB201() { OnIdsBoundaryHs(); }
void CRRI_GUIView::OnBnClickedButtonB202() { OnIdsBoundaryHr(); }
void CRRI_GUIView::OnBnClickedButtonB203(){ OnIdsBoundaryQs(); }
void CRRI_GUIView::OnBnClickedButtonB204(){ OnIdsBoundaryQr();}
void CRRI_GUIView::OnBnClickedButtonB205(){ OnIdsBoundaryDam();}
void CRRI_GUIView::OnBnClickedButtonB206(){ OnIdsBoundaryDiv();}
void CRRI_GUIView::OnBnClickedButtonB207(){ OnIdsBoundaryPos(); }

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  UNDO and Util
void CRRI_GUIView::Save_Undo_File()
{
	CString		Add, Head, tail;
	//
	Undo_Org_Deg_Unit = PM.Deg_Unit;
	//
	Undo_Org_Name[0] = DSET.File_names[ADEM_FILE];
	Undo_Org_Name[1] = DSET.File_names[ACC_FILE];
	Undo_Org_Name[2] = DSET.File_names[ADIR_FILE];
	//
	Add = "_Undo";
	//
	Head = Undo_Org_Name[0].Left(Undo_Org_Name[0].GetLength() - 4);
	tail = Undo_Org_Name[0].Right(4);
	Undo_Temp_Name[0] = Head + Add + tail;
	//
	Head = Undo_Org_Name[1].Left(Undo_Org_Name[1].GetLength() - 4);
	tail = Undo_Org_Name[1].Right(4);
	Undo_Temp_Name[1] = Head + Add + tail;
	//
	Head = Undo_Org_Name[2].Left(Undo_Org_Name[2].GetLength() - 4);
	tail = Undo_Org_Name[2].Right(4);
	Undo_Temp_Name[2] = Head + Add + tail;
	//
	CopyFile(Undo_Org_Name[0], Undo_Temp_Name[0], FALSE);
	CopyFile(Undo_Org_Name[1], Undo_Temp_Name[1], FALSE);
	CopyFile(Undo_Org_Name[2], Undo_Temp_Name[2], FALSE);
	//
	B_UndoFirstSave = TRUE;
}

void CRRI_GUIView::OnBnClickedButtonUndo()
{
	if (!B_UndoFirstSave) return;
	//
	for (int i = 0; i < 3; i++) CopyFile(Undo_Temp_Name[i], Undo_Org_Name[i], FALSE);
	//
	strcpy(DSET.File_names[ADEM_FILE], Undo_Org_Name[0]);
	strcpy(DSET.File_names[ACC_FILE], Undo_Org_Name[1]);
	strcpy(DSET.File_names[ADIR_FILE], Undo_Org_Name[2]);
	//
	Get_Relative_Path(DSET.File_names[ADEM_FILE], DSET.Proj_Folder, DSET.Input_names[ADEM_FILE]);
	Get_Relative_Path(DSET.File_names[ACC_FILE], DSET.Proj_Folder, DSET.Input_names[ACC_FILE]);
	Get_Relative_Path(DSET.File_names[ADIR_FILE], DSET.Proj_Folder, DSET.Input_names[ADIR_FILE]);
	///Free MESH
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Change_Cursor(&Gp, IDC_WAIT);
	if (MESH != NULL) {
		for (int i = 0; i < PM.MVnum; i++) SAFE_FREE(MESH[i]);
		SAFE_FREE(MESH);
	}
	if (PM.Values != 0)	Free_Matrix(PM.MVnum, PM.Values);
	if (FAILED(Read_3_Files(TRUE))) { Change_Cursor(&Gp, IDC_ARROW); RETURN("** Failed ** Cannot read converted files "); }
	//
	PM.Values = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
	///
	//Back Image
	if (Gp.Texnum > 0) {
		for (int i = 1; i < Gp.Texnum + 1; i++)  {
			SAFE_FREE(Gp.Tex[i].image);
		}
		Gp.Texnum = 1;
	}
	//
	PM.Deg_Unit = Undo_Org_Deg_Unit;
	Calc_Unit_Area();

	if(PM.B_LatLng ) Make_Back_Image();						// リソース解放後に作成
	//
	Make_Mesh_Model();
	RefreshSedRectLine();
	Make_Mesh_Line();
	Make_Mesh_Area();
	//
	GL_Redraw(&Gp, TRUE, TRUE, TRUE, ALL_OBJECTS, TRUE);
	//
	CEX_LABEL = PM.EXnum;						// 土研プログラム用　これ以降はCEXは使えない
	//c_EXLIST.AddString("Scale Changed..");
	//c_EXLIST.DeleteString(PM.EXnum);
	//c_EXLIST.AddString("Undo Org Scale");
	Disp_Controls();
	c_Undo.EnableWindow(FALSE);
}

void CRRI_GUIView::Calc_Unit_Area()
{
	double  dx, dy;
	if (PM.B_LatLng) {
		double  H1,H2,V1,V2;
		H1 = Get_GCS_Distance(PM.stLNG, PM.stLAT, PM.endLNG, PM.stLAT);
		H2 = Get_GCS_Distance(PM.stLNG, PM.endLAT, PM.endLNG, PM.endLAT);
		V1 = Get_GCS_Distance(PM.stLNG, PM.stLAT, PM.stLNG, PM.endLAT);
		V2 = Get_GCS_Distance(PM.endLNG, PM.stLAT, PM.endLNG, PM.endLAT);
		// 
		dx = (H1 + H2) / 2. / PM.MHnum;
		dy = (V1 + V2) / 2. / PM.MVnum;
	}
	else {
		dx = dy = PM.Deg_Unit;
	}
	//
	PM.Unit_Area = dx * dy/1000000.;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DRAW EDITTING RIV_TXT 
int 	CRRI_GUIView::Get_Recursive_Basin(int px, int py, BYTE** mark)
{
	int			dir;
	CString		str;
	mark[py][px] = ON;
	MeshCnt++;
	Histcnt++;
	//
	str.Format("Search basin trial %d", MeshCnt); COMMENT(str);
	//
	if (py < AreaYmin)	AreaYmin = py;
	if (py > AreaYmax)	AreaYmax = py;
	if (px < AreaXmin)	AreaXmin = px;
	if (px > AreaXmax)	AreaXmax = px;

	for (int i = 0; i < 8; i++){
		if ((dir = MESH[py + offy[i]][px + offx[i]].Adir) <= 0) continue;
		if (dir == -128) dir = 128;
		if (mark[py + offy[i]][px + offx[i]] != ON && dir == direct[i]) {
			Get_Recursive_Basin(px + offx[i], py + offy[i], mark);
		}
	}
	return MeshCnt;
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  DRAW EDITTING RIV_TXT 
int		CRRI_GUIView::Make_Edit_Riv()
{
	GL_OBJECT*	Mobj = &Gp.Gobj[OBJID_EDIT];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_EDIT);
	//
	GLobj_Init(Mobj, (PM.MHnum + 1)*(PM.MVnum + 1), PM.MHnum*PM.MVnum);
	//
	// VERT
	for (int v = 0; v <= PM.MVnum; v++) {
		for (int h = 0; h <= PM.MHnum; h++) {
			GLobj_Add_Vert(Mobj, (double)h, (double)v, MESH_Z, FALSE);
		}
	}
	//
	// Polygon
	int			no[4], id, pno;
	FCOLOR		Rcol = F_COLOR(40, 110, 255), Gcol = F_COLOR(230, 230, 160);
	//
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (DSET.RIVTXT[v][h] == 0 || DSET.RIVTXT[v][h] == -9999) continue;

			id = v*(PM.MHnum + 1) + h;
			no[0] = id;
			no[1] = id + 1;
			no[2] = no[1] + (int)(PM.MHnum + 1);
			no[3] = no[2] - 1;
			//
			if (DSET.RIVTXT[v][h] == -1)	GLobj_Add_Poly(Mobj, 4, no, GL_POLYGON, Gcol);
			else							GLobj_Add_Poly(Mobj, 4, no, GL_POLYGON, Rcol);
		}
	}
	//
	return 0;
}

void CRRI_GUIView::OnIdsDeleteRiv()
{
	Change_Cursor(&Gp, IDC_WAIT);
	if (!STAT(EDIT_RIV_MODE)) {	
		/* 河川編集モード　MESH(acc) を１００、－１に変換し,RIV.txt（メモリー） に配置
		　RIV.txtの内容を　OBJID_EDITで表示・編集する。
		 １．データ選択機能をOFF ＝データ コンボボックス
		 ２．他の機能の無効化
		*/
		//
		if (DSET.RIVTXT == NULL) {
			DSET.RIVTXT = Make_Matrix(PM.MHnum, PM.MVnum, 0);
			for (int v = 0; v < PM.MVnum; v++) {
				for (int h = 0; h < PM.MHnum; h++) {
					if (MESH[v][h].flag == 0)	DSET.RIVTXT[v][h] = -9999;
					else if (MESH[v][h].flag == ID_MESH)	DSET.RIVTXT[v][h] = -1;
					else if (MESH[v][h].flag == ID_MESH_R) {
						if (MESH[v][h].Adir == 0)  DSET.RIVTXT[v][h] = 0;
						else                      DSET.RIVTXT[v][h] = 100;
					}
				}
			}
		}
		//
		GLobj_Delete(&Gp, OBJID_LEGEND);
		GLobj_Delete(&Gp, OBJID_MESH);
		GLobj_Delete(&Gp, OBJID_LINE);
		//
		STAT(EDIT_RIV_MODE) = TRUE;

		Make_Mesh_Line();			// EDIT_RIV_MODE モードでは単一色	
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, ALL_OBJECTS, TRUE);
		//
	}
	//
	for (int i = 0; i < SI.Num; i++) 	DSET.RIVTXT[SI.HV[i].y][SI.HV[i].x] = -1;
	//
	Clear_Select();
	Make_Edit_Riv();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_EDIT, TRUE);
}


void CRRI_GUIView::OnIdsSetRiv()
{
	for (int i = 0; i < SI.Num; i++) 	DSET.RIVTXT[SI.HV[i].y][SI.HV[i].x] = 100;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	Clear_Select();
	Make_Edit_Riv();
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_EDIT, TRUE);
}

///========================================================================
// BACK IMAGE
///========================================================================

void CRRI_GUIView::OnBnClickedButtonBack()
{
	char		InDir[SIZE_1K];
	//
	if (!Button_Dir(InDir, m_RecentPath)) return;
	//
	struct _finddata_t	c_file;	// time_write が作成時間を示す
	long					hFile;
	//
	CString				Fname,str;
	FILE*				fp;
	char					inchar[SIZE_01K], IMname[SIZE_01K];
	int					Texno,no[4];
	double				x1, y1, x2, y2;
	double				minx, miny, maxx, maxy;
	//
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_BACK];
	FXYCOORD		uv[4];
	//
	// TEX リソースの解放		ガイドＡＣＣ画像の破棄
	if (Gp.Texnum > 0) {
		for (int i = 1; i < Gp.Texnum + 1; i++)  {
			SAFE_FREE(Gp.Tex[i].image);
		}
		//	
		Gp.Texmem = GUIDE_TEXTURE + 5;
		Gp.Texnum = 1;
	}
	GLobj_Delete(&Gp, OBJID_BACK);
	GLobj_Init(obj, 100,100);
	//
	::SetCurrentDirectory( InDir );
	if( (hFile = _findfirst( "*.loc", &c_file )) == -1L ) {
		RETURN("** Error ** : Cannot find loc file......");
	}
	//
	do {
		str.Format("[%s] is found ", c_file.name); UDF;
		fp = fopen(c_file.name,"r");
		fgets(inchar, SIZE_01K, fp);	// UTM or GCS
		if (PM.B_LatLng && strcmp(inchar, "UTM") == 0) { fclose(fp); continue; }
		if (!PM.B_LatLng && strcmp(inchar, "LATLON") == 0)  { fclose(fp); continue; }
		//
		fgets(IMname, SIZE_01K, fp); IMname[strlen(IMname)-1] = 0x00;
		Fname = IMname;
		
		Texno = GL_Set_Texture(&Gp, Fname, 3);
		//
		fgets(inchar, SIZE_01K, fp);
		sscanf(inchar, "%lf,%lf", &x1, &y1);
		fgets(inchar, SIZE_01K, fp);
		sscanf(inchar, "%lf,%lf", &x2, &y2);
		fclose(fp);
		//
		if (PM.B_LatLng) {
			minx = (x1 - PM.stLNG)*PM.Coord_Unit;
			miny = (y1 - PM.stLAT)*PM.Coord_Unit;
			maxx = (x2 - PM.stLNG)*PM.Coord_Unit;
			maxy = (y2 - PM.stLAT)*PM.Coord_Unit;
		}
		else {
			minx = (x1 - PM.stUTM_X)*PM.Coord_Unit;
			miny = (y1 - PM.stUTM_Y)*PM.Coord_Unit;
			maxx = (x2 - PM.stUTM_X)*PM.Coord_Unit;
			maxy = (y2 - PM.stUTM_Y)*PM.Coord_Unit;
		}
		//
		no[0] = GLobj_Add_Vert(obj, minx, miny, BACK_Z, FALSE);
		uv[0].x = 0.; uv[0].y = 1.;
		no[1] = GLobj_Add_Vert(obj, maxx,miny, BACK_Z, FALSE);
		uv[1].x = 1.; uv[1].y = 1.;
		no[2] = GLobj_Add_Vert(obj, maxx, maxy, BACK_Z, FALSE);
		uv[2].x = 1.; uv[2].y = 0.;
		no[3] = GLobj_Add_Vert(obj, minx, maxy, BACK_Z, FALSE);
		uv[3].x = 0.; uv[3].y = 0.;
		//
		GLobj_Add_Poly(obj, 4, no, GL_POLYGON,Texno, uv);


	} while (_findnext(hFile, &c_file) == 0L);
	_findclose( hFile );
	//
	/// Delete CopyRight
	GLobj_Delete(&Gp, OBJID_COPYRIGHT);
	//
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_COPYRIGHT, TRUE);
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_BACK, TRUE);
}
///========================================================================
//  Cover, Soil.txt の作成
///========================================================================
void CRRI_GUIView::OnBnClickedButtonLuparam()
{
	/* 範囲が限定されていることが前提 UTMは除外  MESH == NULLは除外*/
	if (!PM.set || !PM.B_LatLng || MESH == NULL) {
		MessageBox("** Error ** Making conditions are not enough", "error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	/* ＦＡＯファイルの存在　*/
	::SetCurrentDirectory(m_BootPath);
	//
	if (!File_Exist(FAO_FILE))	{
		MessageBox("** Error ** FAO file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	//--------------------------------------------------
	/* 基本的なセッティング　*/
	//--------------------------------------------------
	FILE*		fp;
	double		FAO_unit = 1. / 12.;				// 300 sec = 5 minutes
	int			FAO_Hnum = 4320, FAO_Vnum = 2160;	// 1 file number
	char**		FC;		/// 4320×2160
	//
	char			buf[SIZE_16K], inchar[SIZE_01K];
	int			pos,Ncnt;
	//
	double		H, V, H0, V0;
	//
	CBUSY*		CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	CB->Set_Prog(0, 5);
	CB->ShowWindow(SW_SHOW);
	//--------------------------------------------------
	/*
	必要なファイル　　Manning係数  Manning.csv   ->1-7=0.06 Darcy  8-17=0.025,18=0.04  GreenAmpt
	土壌係数　　 FAO_PARAM.csv ->ksv ka, etc
	世界のデータ FAO_CODE_DATA.csv

	Darcy　適用の場合(山地）		ka = 0.
	GreenAmpt 適用の場合(平地）	ksv =0.
	*/
	//--------------------------------------------------
	///  世界のデータ FAO_CODE_DATA.csv の読み込み
	//
	CB->Set_Title("Read FAO_DATA");
	CB->Set_Pos(1);
	if ((fp = fopen(FAO_FILE, "r")) == NULL) 	{
		MessageBox("** Error ** FAO CODE  file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
		CB->Close();	return;
	}
	//
	FC = Make_Matrix(FAO_Hnum, FAO_Vnum, (char)0xff);
	//
	for (int v = FAO_Vnum - 1; v >= 0; v--) {
		fgets(buf, SIZE_16K, fp); pos = 0;
		for (int h = 0; h < FAO_Hnum; h++) {
			getstr(buf, &pos, inchar, SIZE_01K); FC[v][h] = (char)atoi(inchar);
		}
	}
	fclose(fp);
	//------------------------  コード分類
	Ncnt = 0;
	if (PM.Size <= FAO_unit) {		// MESH の中心がＦＡＯのどのメッシュ範囲にあるか
		for (int v = 0; v < PM.MVnum; v++) {	// 西経180　南緯90を原点とする座標系に変換
			V = (90. + PM.stLAT + (v + 0.5)*PM.Size) / FAO_unit;
			for (int h = 0; h < PM.MHnum; h++) {
				H = (180. + PM.stLNG + (h + 0.5)*PM.Size) / FAO_unit;
				MESH[v][h].Soil = (short)FC[(int)V][(int)H];
				if (MESH[v][h].Soil == 0) Ncnt++;
			}
		}
	}
	else {
		MessageBox("** Error ** Model mesh size is too large > 5minite", "error", MB_OK | MB_ICONEXCLAMATION);
		Free_Matrix(FAO_Vnum, FC);
		CB->Close(); return;
	}
	Free_Matrix(FAO_Vnum, FC);
	//--------------------------------------------------
	///  ＦＡＯ のデータ０を補間 最近隣のデータを代入
	//
	if (Ncnt != 0) {
		int		eh, ev;
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h < PM.MHnum; h++) {
				if (MESH[v][h].flag == 0) continue;
				if (MESH[v][h].Soil != 0) continue;		// ０だけを対象とする。
				//
				eh = ev = 1;
				while (TRUE) {
					if (h + eh < PM.MHnum){
						if (!(MESH[v][h + eh].Soil == 0 || MESH[v][h + eh].Soil > 100)) {
							MESH[v][h].Soil = MESH[v][h + eh].Soil + 100;
							break;
						}
					}
					if (h - eh >= 0){
						if (!(MESH[v][h - eh].Soil == 0 || MESH[v][h - eh].Soil > 100)) {
							MESH[v][h].Soil = MESH[v][h - eh].Soil + 100;
							break;
						}
					}
					if (v + ev < PM.MVnum){
						if (!(MESH[v + ev][h].Soil == 0 || MESH[v + ev][h].Soil > 100)) {
							MESH[v][h].Soil = MESH[v + ev][h].Soil + 100;
							break;
						}
					}
					if (v - ev >= 0){
						if (!(MESH[v - ev][h].Soil == 0 || MESH[v - ev][h].Soil > 100)) {
							MESH[v][h].Soil = MESH[v - ev][h].Soil + 100;
							break;
						}
					}
					eh++;
					ev++;
				}
			}
		}
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h < PM.MHnum; h++) {
				if (MESH[v][h].flag == 0) continue;
				if (MESH[v][h].Soil >100) MESH[v][h].Soil -= 100;
			}
		}
	}
	//--------------------------------------------------
	/* メッシュ範囲に必要な、GLUNMOを抽出　南北緯、東西経 計算式は同じ　*/
	/*
	GLCNMO のチェック、Darcy か GreenAmpt 適用かを決定 1-20 までの数値

	メッシュサイズが１/240より小さければ一意に決まる。　
	大きい場合は平均はできないので、多いものとする。 MeshInfo の　Dcnt Gcnt Wcnt
	*/
	//--------------------------------------------------
	double		GLC_unit = 1. / 240., GLC_Span = 30;	// 30 deg  15sec 
	double		GstLAT, GendLAT, GstLNG, GendLNG;	// LNG は0-360、　LAT は 0-180
	int			GLC_Hnum = 7200, GLC_Vnum = 7200;  // 1 byte  7200*7200* 1 byte
	int			nn = 0, Nlat[4], Nlng[4], id;
	CString		exname, zipname, order;
	short**		GLC;
	/// 
	// 西経180　北緯90を原点とする座標系に変換
	nn = 0;
	Nlat[nn] = (int)((90. - PM.stLAT) / GLC_Span);
	Nlng[nn] = (int)((180. + PM.stLNG) / GLC_Span) + 1;
	nn = 3;
	Nlat[nn] = (int)((90. - PM.endLAT) / GLC_Span);
	Nlng[nn] = (int)((180 + PM.endLNG) / GLC_Span) + 1;
	//
	if ((Nlat[3] != Nlat[0]) && (Nlng[3] != Nlng[0])) {  // ４ページにまたがる
		nn = 4;
		Nlat[1] = Nlat[0]; Nlng[1] = Nlng[0] + 1;
		Nlat[2] = Nlat[0] + 1; Nlng[2] = Nlng[0];
	}
	else if ((Nlat[3] == Nlat[0]) && (Nlng[3] != Nlng[0])) {  // ２ページにまたがる
		nn = 2;
		Nlat[1] = Nlat[0]; Nlng[1] = Nlng[0] + 1;
	}
	else if ((Nlat[3] != Nlat[0]) && (Nlng[3] == Nlng[0])) {  // ２ページにまたがる
		nn = 2;
		Nlat[1] = Nlat[0] + 1; Nlng[1] = Nlng[0];
	}
	else  nn = 1;
	//--------------------------------------------------
	::GetCurrentDirectory(SIZE_05K, m_BootPath);		// 正確にブートフォルダでなければならない
	//---------------------------------------------------
	GLC = Make_Matrix(GLC_Hnum, GLC_Vnum, (short)0);
	//---------------------------------------------------
	CB->Set_Title("Set landuse data");
	CB->Set_Pos(3);
	///
	// GLCメッシュがモデルメッシュより小さい カウントクリヤー
	if (PM.Size > GLC_unit){
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h < PM.MHnum; h++) memset(MESH[v][h].LUCNT, 0, 21);
		}
	}
	//
	for (int i = 0; i < nn; i++) {
		id = Nlat[i] * 12 + Nlng[i];
		exname.Format("%s\\gm_lc%d_v2.bil", EXTRACT_PATH, id);
		GstLAT = (2 - Nlat[i]) * GLC_Span; GendLAT = GstLAT + GLC_Span;
		GstLNG = (Nlng[i] - 1) * GLC_Span - 180.; GendLNG = GstLNG + GLC_Span;
		//
		if (!File_Exist(exname))	{	// zip の展開
			zipname.Format("%s\\gm_lc%d_v2.zip", GLC_PATH, id);
			if (!File_Exist(zipname))	{
				MessageBox("** Error ** GLC file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
				Free_Matrix(GLC_Vnum, GLC); CB->Close(); 	return;
			}
			///
			// Unzip
			order.Format("%s%s  %s", UNZIP_PROGRAM, EXTRACT_PATH, zipname);
			system(order);
		}
		//------------------------------------------------------
		int		fi;
		if ((fi = _open(exname, _O_BINARY | O_RDONLY, 0)) == -1) {
			MessageBox("** Error ** GLC file cannot open", "error", MB_OK | MB_ICONEXCLAMATION);
			Free_Matrix(GLC_Vnum, GLC); CB->Close(); 	return;
		}
		for (int v = 0; v < GLC_Vnum; v++) 	{
			if (read(fi, buf, GLC_Hnum) != GLC_Hnum) {
				MessageBox("** Error ** Cannot read GLCNMO data", "error", MB_OK | MB_ICONEXCLAMATION);
				CB->Close(); 	Free_Matrix(GLC_Vnum, GLC); close(fi); return;
			}
			for (int h = 0; h < GLC_Hnum; h++) 	GLC[GLC_Vnum - v - 1][h] = (short)buf[h];
		}
		close(fi);
		//------------------------------------------------------
		/*
		GLCメッシュがモデルメッシュより大きい　モデルメッシュからＧＬＣメッシュを探る　
		*/
		short	id;
		if (PM.Size <= GLC_unit || fabs(PM.Size - GLC_unit) < EPS6)  {		// MESH の中心がＧＬＣのどのメッシュ範囲にあるか
			for (int v = 0; v < PM.MVnum; v++) {
				V0 = PM.stLAT + (v + 0.5)*PM.Size;
				if (V0 < GstLAT || V0 >= GendLAT) continue;
				//
				V0 = fmod((90. + PM.stLAT + (v + 0.5)*PM.Size), GLC_Span);
				V = V0 / GLC_unit;
				for (int h = 0; h < PM.MHnum; h++) {
					MESH[v][h].Cover = 0;
					if (MESH[v][h].flag == 0) continue;
					//
					H0 = PM.stLNG + (h + 0.5)*PM.Size;
					if (H0 < GstLNG || H0 > GendLNG) continue;
					H0 = fmod((180. + PM.stLNG + (h + 0.5)*PM.Size), GLC_Span);
					H = H0 / GLC_unit;
					MESH[v][h].Cover = (short)GLC[(int)V][(int)H];
					//
				}
			}
		}
		/*
		GLCメッシュがモデルメッシュより小さい　GLCメッシュをカウントする。MESH のLUCNTに計上
		*/
		else {
			for (int v = 0; v < GLC_Vnum; v++) {
				V = GstLAT + (v + 0.5)*GLC_unit;
				if (V <PM.stLAT || V > PM.endLAT) continue;
				for (int h = 0; h < GLC_Hnum; h++) {
					H = GstLNG + (h + 0.5)*GLC_unit;
					if (H <PM.stLNG || H > PM.endLNG) continue;
					//
					V0 = (V - PM.stLAT) / PM.Size;
					H0 = (H - PM.stLNG) / PM.Size;
					id = GLC[v][h];
					if (MESH[(int)V0][(int)H0].flag == 0) continue;
					MESH[(int)V0][(int)H0].LUCNT[id] += (BYTE)1;
				}
			}
		}
	}
	//
	Free_Matrix(GLC_Vnum, GLC);
	//
	/*
	GLCメッシュがモデルメッシュより小さい場合の、ＬＵ決定
	*/
	int		cntmax;
	if (PM.Size > GLC_unit){
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h < PM.MHnum; h++) {
				if (MESH[v][h].flag == 0) continue;
				//
				cntmax = 0; id = UNDEF;
				for (int i = 1; i < 21; i++) {
					if (MESH[v][h].LUCNT[i] != 0){
						if (cntmax < (int)MESH[v][h].LUCNT[i]) { cntmax = (int)MESH[v][h].LUCNT[i]; id = i; }
					}
				}
				if (id != UNDEF) MESH[v][h].Cover = id;
			}
		}
	}
	///
	// Ｏｕｔｐｕｔ
	DSET.b_CSexist = TRUE;
	//
	Write_Data_File(LAND_COVER, 0, 0, DSET, PM, MESH);		// 
	Write_Data_File(LAND_SOIL, 0, 0, DSET, PM, MESH);
	//
	CB->DestroyWindow();
}
///========================================================================
//  CODE_TABLE の作成
///========================================================================
BOOL CRRI_GUIView::Set_LU_CodeTable()
{
	//--------------------------------------------------
	/* 基本的なセッティング　*/
	//--------------------------------------------------
	FILE*		fp;
	//
	char			buf[SIZE_16K], inchar[SIZE_01K];
	int			pos;
	//
	//--------------------------------------------------
	/*
	必要なファイル　　Manning係数  Manning.csv   ->  Darcy = 1 GreenAmpt = 0 by Kswitch to appno
	Darcy　適用の場合(山地）		ka = 0.
	GreenAmpt 適用の場合(平地）	ksv =0.
	*/
	::SetCurrentDirectory(m_BootPath);
	/*
	マニング係数　　 Manning.csvの読み込み　２０種類コード
	*/
	//--------------------------------------------------
	double	Manning[20] = { 0 };	// マニング係数
	int		Kswitch[20] = { 0 };	// Darcy(1) or GAmpt(0)
	int		MNnum = 20;

	if (PM.B_UseJFlow) {
		MNnum = 20; //201911
	}
	if (!PM.B_UseJFlow) {
		if ((fp = fopen(MANNING_FILE, "r")) == NULL) {
			MessageBox("** Error ** Manning file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	else {
		if ((fp = fopen(MANNING_FILE_JA, "r")) == NULL) {
			MessageBox("** Error ** Manning file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	fgets(buf, SIZE_16K, fp);  // Terms
	for (int m = 0; m < MNnum; m++) {
		fgets(buf, SIZE_16K, fp); pos = 0;
		getstr(buf, &pos, inchar, SIZE_01K); // NO;
		getstr(buf, &pos, inchar, SIZE_01K); Manning[m] = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); Kswitch[m] = atoi(inchar);
		strcpy(Cover_Name[m], &buf[pos]);
	}
	fclose(fp);
	//--------------------------------------------------
	/*
	土壌係数　　 FAO_PARAM.csv ->ksv ka, etc の読み込み　１３種類コード
	読込以外はデフォルト設定
	SW_kinema(1),soildepth(1.0) kgv(0), gammag(0.4), tg(0.0005), fpg(0.03), init_cond_gw(0.5);
	*/
	//--------------------------------------------------
	int		CODE_num = 13, cnt;
	//
	if ((fp = fopen(FAO_PARAM, "r")) == NULL) {
		MessageBox("** Error ** FAO_PARAM.csv file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	cnt = 0;
	fgets(buf, SIZE_16K, fp);  // Terms
	while (fgets(buf, SIZE_16K, fp) != NULL) {
		pos = 0;
		CODE_TABLE[cnt][0].renumber = CODE_TABLE[cnt][0].refcnt = 0;
		CODE_TABLE[cnt][0].ns_slope = Manning[0];
		CODE_TABLE[cnt][0].SW_kinema = 1;				// 常に１であるようにする。
		CODE_TABLE[cnt][0].soildepth = 1.0;
		CODE_TABLE[cnt][0].kgv = 0.;
		CODE_TABLE[cnt][0].gammag = 0.4;
		CODE_TABLE[cnt][0].tg = 0.0005;
		CODE_TABLE[cnt][0].fpg = 0.03;
		CODE_TABLE[cnt][0].init_cond_gw = 0.5;
		//
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].NO = atoi(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].ksv = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].gammaa = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].faif = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].ka = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].gammam = atof(inchar);
		getstr(buf, &pos, inchar, SIZE_01K); CODE_TABLE[cnt][0].beta = atof(inchar);
		strcpy(Soil_Name[cnt], &buf[pos]);
		//

		for (int i = 1; i < MNnum; i++) {
			Copy_Luinfo(&CODE_TABLE[cnt][i], CODE_TABLE[cnt][0]);	// 平地用

			CODE_TABLE[cnt][i].ns_slope = Manning[i];
			CODE_TABLE[cnt][i].renumber = CODE_TABLE[cnt][i].refcnt = 0;
			//
			if (Kswitch[i] == 1)	{
				CODE_TABLE[cnt][i].ksv = 0.;
				CODE_TABLE[cnt][i].appflag = 1;
			}
			else	 {
				CODE_TABLE[cnt][i].ka = 0.;
				CODE_TABLE[cnt][i].appflag = 0;
			}
			if (i >= 18) {
				CODE_TABLE[cnt][i].ksv = 0.;
				CODE_TABLE[cnt][i].ka = 0.;
			}
		}
		if (Kswitch[0] == 1) CODE_TABLE[cnt][0].ksv = 0.;	// Manning[０]の値、全セットをコピーしてから検討
		else                 CODE_TABLE[cnt][0].ka = 0.;
		//
		cnt++;
	}
	fclose(fp);
	return TRUE;
}
// //////////////////////////////////////////////////////////////////////////////////////////////////////
///    流下方向　編集 コントロール
// //////////////////////////////////////////////////////////////////////////////////////////////////////
void CRRI_GUIView::Disp_Direction_Radio(int xid, int yid)
{
	CWnd*		cw;
	int			id,Direc[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	BOOL			fix = FALSE;
	CButton*		cb;
	//
	if (CDATA == ADIR_FILE) {
		if (xid != UNDEF) {
			for (int i = 0; i < 8; i++) {
				if (MESH[yid][xid].Adir == Direc[i]) { id = i; fix = TRUE; break; }
			}
			if (!fix) id = 8;
			//
			for (int i = 0; i < 9; i++) {
				cb = (CButton*)GetDlgItem(DIRECT_ID[i]);
				if (i == id) cb->SetCheck(1);
				else         cb->SetCheck(0);
				//
				if (CDATA == ADIR_FILE) cb->EnableWindow(TRUE);
				else                  cb->EnableWindow(FALSE);
			}
		}
		else {
			for (int i = 0; i < 9; i++) {
				cb = (CButton*)GetDlgItem(DIRECT_ID[i]);
				cb->SetCheck(0);
				cb->EnableWindow(TRUE);
			}
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			cb = (CButton*)GetDlgItem(DIRECT_ID[i]);
			cb->SetCheck(0);
			cb->EnableWindow(FALSE);
		}
	}
	//
	cw = GetDlgItem(IDC_BUTTON_RESET);
	if (CDATA == ADIR_FILE) {
		if (STAT(AVAIL_RESET)) {
			Static_Format(cw, "Set", 6, 14, DT_CENTER | DT_BOTTOM, RGB(0, 0, 0), RGB(255, 180, 180));
			c_Reset.EnableWindow(TRUE);
		}
		else  {
			Static_Format(cw, "Set", 6, 14, DT_CENTER | DT_BOTTOM, RGB(200,200,200), RGB(240, 240, 240));
			c_Reset.EnableWindow(FALSE);
		}
		c_Cancel.EnableWindow(TRUE);
		c_DirUndo.EnableWindow(FALSE);
		//
		c_DispArrow.SetCheck(1);
		c_DispArrow.EnableWindow(FALSE);
	}
	else {
		if (STAT(AVAIL_UNDO))		c_DirUndo.EnableWindow(TRUE);
		else						c_DirUndo.EnableWindow(FALSE);
		c_Reset.EnableWindow(FALSE);
		c_Cancel.EnableWindow(FALSE);
		//
		c_DispArrow.EnableWindow(TRUE);
		if (STAT(DISP_ARROW)) 	c_DispArrow.SetCheck(1);
		else					c_DispArrow.SetCheck(0);
	}
}
///--------------------------------------------------
//	ＤＩＳＰ＿ＡＲＲＯＷ
///--------------------------------------------------
void CRRI_GUIView::Disp_Arrow()
{
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_ARROW];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_ARROW);
	//
	if (FAILED(GLobj_Init(obj, PM.MHnum * PM.MVnum * 4 + 100, PM.MHnum * PM.MVnum * 2))) return;
	//
	double	ang, x, y, xc, yc, rot, X, Y, Z, xt, yt;
	int		NO[2], no[3];
	double	ROT[8] = { 0., PAI / 4., PAI / 2., PAI*3. / 4., PAI, -PAI*3. / 4., -PAI / 2., -PAI / 4. };
	double	PosX[8] = { 1., 1., 0., -1., -1., -1., 0., 1. };
	double	PosY[8] = { 0., -1., -1., -1., 0., 1., 1., 1. };
	//
	ang = Arrow_Ang*PI / 180. / 2.;
	ang = atan(Arrow_Head*tan(ang) / (1. - Arrow_Head));
	//
	int	id;
	//
	for (int v = 0; v<PM.MVnum; v++) {
		for (int h = 0; h<PM.MHnum; h++) {
			if (!MESH[v][h].flag)		continue;
			if ((int)MESH[v][h].Adir == 0)		continue;	/// NOEXITを０に設定
			//
			switch ((int)MESH[v][h].Adir) {
			case DIR_E:		id = 0; break;
			case DIR_SE:		id = 1; break;
			case DIR_S:		id = 2; break;
			case DIR_SW:		id = 3; break;
			case DIR_W:		id = 4; break;
			case DIR_NW:		id = 5; break;
			case DIR_N:		id = 6; break;
			case DIR_NE:		id = 7; break;
			default: id = UNDEF; break;
			}
			//
			if (id == UNDEF) continue;
			//
			xc = h + 0.5;
			yc = v + 0.5;
			NO[0] = GLobj_Add_Vert(obj, xc, yc, ARROW_Z, FALSE);
			X = xc + PosX[id];
			Y = yc + PosY[id];
			NO[1] = GLobj_Add_Vert(obj, X, Y, ARROW_Z, FALSE);
			xt = X; yt = Y;
			///
			// Head				水平右向きの矢印を回転
			///
			rot = ROT[id];
			no[0] = NO[1];
			x = -Arrow_Head;
			y = x*tan(ang);

			X = x*cos(rot) + y*sin(rot) + xt;
			Y = -x*sin(rot) + y*cos(rot) + yt;
			no[2] = GLobj_Add_Vert(obj, X, Y, ARROW_Z, FALSE);

			y = -y;
			X = x*cos(rot) + y*sin(rot) + xt;
			Y = -x*sin(rot) + y*cos(rot) + yt;
			no[1] = GLobj_Add_Vert(obj, X, Y, ARROW_Z, FALSE);
			//
			GLobj_Add_Poly(obj, 2, NO, GL_LINE_STRIP, 1.5f, Col_Arrow);
			GLobj_Add_Poly(obj, 3, no, GL_TRIANGLE_STRIP, Col_Arrow);
		}
	}
	STAT(SET_ARROW) = TRUE;
	//
	return;
}
///--------------------------------------------------
//	ＤＩＳＰ＿ＥＤＩＴ＿ＡＲＲＯＷ
///--------------------------------------------------
void CRRI_GUIView::Disp_Edit_Arrow()
{
	GL_OBJECT*	obj = &Gp.Gobj[OBJID_EDIT_ARROW];	// 全体座標で表示
	GLobj_Delete(&Gp, OBJID_EDIT_ARROW);
	//
	if (FAILED(GLobj_Init(obj, 500, 300))) return;
	//
	double	ang, x, y, xc, yc, rot, X, Y, Z, xt, yt;
	int		NO[4], no[3];
	double	ROT[8] = { 0., PAI / 4., PAI / 2., PAI*3. / 4., PAI, -PAI*3. / 4., -PAI / 2., -PAI / 4. };
	double	PosX[8] = { 1., 1., 0., -1., -1., -1., 0., 1. };
	double	PosY[8] = { 0., -1., -1., -1., 0., 1., 1., 1. };
	//
	ang = Arrow_Ang*PI / 180. / 2.;
	ang = atan(Arrow_Head*tan(ang) / (1. - Arrow_Head));
	//
	int	id, v, h, dir;
	//
	for (int i = 0; i < UHnum; i++) {				// 履歴リストに変更　UNDOのため
		v = UH[i].v;
		h = UH[i].h;
		//
		if (!MESH[v][h].flag)		continue;

		switch (UH[i].dir) {
		case DIR_E:		id = 0; break;
		case DIR_SE:		id = 1; break;
		case DIR_S:		id = 2; break;
		case DIR_SW:		id = 3; break;
		case DIR_W:		id = 4; break;
		case DIR_NW:		id = 5; break;
		case DIR_N:		id = 6; break;
		case DIR_NE:		id = 7; break;
		default: id = UNDEF; break;					// 0
		}
		//
		if (id == UNDEF) {	// 四角
			xc = h + 0.05;
			yc = v + 0.05;
			NO[0] = GLobj_Add_Vert(obj, xc, yc, SELECT_Z, FALSE);
			xc = h + 0.95;
			yc = v + 0.05;
			NO[1] = GLobj_Add_Vert(obj, xc, yc, SELECT_Z, FALSE);
			xc = h + 0.95;
			yc = v + 0.95;
			NO[2] = GLobj_Add_Vert(obj, xc, yc, SELECT_Z, FALSE);
			xc = h + 0.05;
			yc = v + 0.95;
			NO[3] = GLobj_Add_Vert(obj, xc, yc, SELECT_Z, FALSE);
			GLobj_Add_Poly(obj, 4, NO, GL_LINE_LOOP, 1.5f, CREF_FCOL(COL_RED));
		}
		else {				/// 矢印
			//
			xc = h + 0.5;
			yc = v + 0.5;
			NO[0] = GLobj_Add_Vert(obj, xc, yc, SELECT_Z, FALSE);
			X = xc + PosX[id];
			Y = yc + PosY[id];
			NO[1] = GLobj_Add_Vert(obj, X, Y, SELECT_Z, FALSE);
			xt = X; yt = Y;
			///
			// Head				水平右向きの矢印を回転
			///
			rot = ROT[id];
			no[0] = NO[1];
			x = -Arrow_Head;
			y = x*tan(ang);

			X = x*cos(rot) + y*sin(rot) + xt;
			Y = -x*sin(rot) + y*cos(rot) + yt;
			no[2] = GLobj_Add_Vert(obj, X, Y, SELECT_Z, FALSE);

			y = -y;
			X = x*cos(rot) + y*sin(rot) + xt;
			Y = -x*sin(rot) + y*cos(rot) + yt;
			no[1] = GLobj_Add_Vert(obj, X, Y, SELECT_Z, FALSE);
			//
			GLobj_Add_Poly(obj, 2, NO, GL_LINE_STRIP, 1.5f, CREF_FCOL(COL_RED));
			GLobj_Add_Poly(obj, 3, no, GL_TRIANGLE_STRIP, CREF_FCOL(COL_RED));
		}
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_EDIT_ARROW, TRUE);
	//
	return;
}

void CRRI_GUIView::OnBnClickedRadioE()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_E);
}


void CRRI_GUIView::OnBnClickedRadioSe()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_SE);
}


void CRRI_GUIView::OnBnClickedRadioS()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_S);
}


void CRRI_GUIView::OnBnClickedRadioSw()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_SW);
}


void CRRI_GUIView::OnBnClickedRadioW()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_W);
}
void CRRI_GUIView::OnBnClickedRadioNw()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_NW);
}


void CRRI_GUIView::OnBnClickedRadioN()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_N);
}


void CRRI_GUIView::OnBnClickedRadioNe()
{
	if (SI.Num != 1) return;
	Resist_Dir(DIR_NE);
}


void CRRI_GUIView::OnBnClickedRadioTerm()
{
	if (SI.Num != 1) return;
	MESH[SI.HV[0].y][SI.HV[0].x].Adir = 0;
	//	Reset_Times++;
	//
	Disp_Edit_Arrow();
}
BOOL CRRI_GUIView::Resist_Dir(int Dir)
{
	int v, h;
	v = SI.HV[0].y;
	h = SI.HV[0].x;
//	if (MESH[v][h].Adir == Dir) return FALSE;
	//
	int id = UHnum;
	STAT(CHANGE_DIRECTION) = TRUE;
	//
	if (UHnum > 0) {
		id = UNDEF;
		for (int i = 0; i < UHnum; i++) {
			if (UH[i].v == v && UH[i].h == h) { id = i; break; }
		}
		if (id == UNDEF) id = UHnum;
	}
	UH[id].v = v;
	UH[id].h = h;
	UH[id].dir0 = MESH[v][h].Adir;
	UH[id].dir = Dir;
	if (id == UHnum) UHnum++;
	//
	Disp_Edit_Arrow();		//***************
	///
	//  選択メッシュの移動
	int x, y;
	x = h;
	y = v;

	switch (Dir){
	case DIR_E: x += 1; break;
	case DIR_SE: x += 1; y -= 1; break;
	case DIR_S: y -= 1; break;
	case DIR_SW: x -= 1; y -= 1; break;
	case DIR_W: x -= 1; break;
	case DIR_NW: x -= 1; y += 1; break;
	case DIR_N: y += 1; break;
	case DIR_NE: x += 1; y += 1; break;
	default: Dir = 8;
	}
	//
	if (!(x >= 0 && x < PM.MHnum && y >= 0 && y < PM.MVnum)) return TRUE;
	if (MESH[y][x].Adem < EL_LIMIT) return TRUE;

	STAT(AVAIL_UNDO) = FALSE;
	STAT(AVAIL_RESET) = TRUE;
	//  表示
	Disp_Direction_Radio(x, y);
	//
	SI.HV[0].x = x; SI.ID[0].x = x + 1;
	SI.HV[0].y = y; SI.ID[0].y = PM.MVnum - y;
	SI.Num = 1;
	//
	Make_Select_Pos();
	GL_Redraw(&Gp, FALSE, TRUE, TRUE, OBJID_SELECT, TRUE);
	//
	return TRUE;
}


void CRRI_GUIView::OnBnClickedCheckDisparrow()
{
	if (c_DispArrow.GetCheck()) {
		if (!STAT(SET_ARROW))  {
			Change_Cursor(&Gp, IDC_WAIT);
			Disp_Arrow();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_ARROW, TRUE);
		}
		if (STAT(ENABLE_DRAW_ARROW)){
			Gp.Gobj[OBJID_ARROW].display = TRUE;
			STAT(DISP_ARROW) = TRUE;
		}
		else {
			Gp.Gobj[OBJID_ARROW].display = FALSE;
			STAT(DISP_ARROW) = FALSE;
		}
	}
	else {
		Gp.Gobj[OBJID_ARROW].display = FALSE;
		STAT(DISP_ARROW) = FALSE;
	}
	GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_ARROW, TRUE);
}
void CRRI_GUIView::Show_Mesh_Info(int xid, int yid)
{
	CString	valform;
	int		rip;
	//
	if (xid == UNDEF) {
		s_Location = _T("");
		s_H = _T("");
		s_Acc = _T("");
		s_CurrentD = _T("");
		s_Kind = _T("");
		UDF;
		return;
	}
	//
	double	val = DUNDEF;
	if ((CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE) || CDATA >= LAND_COVER) {
		CopyDataFromMesh(CDATA, yid, xid, val, MESH, PM);
		if (CDATA >= ADEM_FILE && CDATA <= GAMPT_FILE) rip = File_Order[CDATA];
		else                                       rip = 0;

	}
	//
	s_Location.Format("%d,%d", xid + 1, PM.MVnum - yid);
	s_H.Format("%.3lf", MESH[yid][xid].Adem);
	s_Acc.Format("%d", (int)MESH[yid][xid].Acc);
	//valform.Format("%%.%dlf", rip);
	//s_CurrentD.Format(valform, val);
	if (val != DUNDEF) {
		valform.Format("%%.%dlf", rip);
		s_CurrentD.Format(valform, val);
	}
	else {
		s_CurrentD = "Diversion";
	}
	
	UDF;
	return;
}

///--------------------------------------------------
//	ＲＥＳＥＴ
///--------------------------------------------------

void CRRI_GUIView::OnBnClickedButtonReset()
{
	if (CDATA != ADIR_FILE || UHnum == 0) {
		STAT(AVAIL_RESET) = FALSE; 
		Disp_Direction_Radio(UNDEF, UNDEF);
		return;
	}
	//
	int		v, h, minid, V, H, id, odd;
	int			Bno = 0;
	BOOL			Bret;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	///----------------------------------------------------------
	// 　河道編集モード　
	///----------------------------------------------------------
	for (int i = 0; i < UHnum; i++) {
		MESH[UH[i].v][UH[i].h].Adir = UH[i].dir;
	}
	STAT(AVAIL_UNDO) = TRUE;
	UHnum0 = UHnum;
	///----------------------------------------------------------
	// 流域の定義を再度行う。
	///----------------------------------------------------------
	Reset_Flow_Direction();		// ACC の再計算も行われている。
	//  flag は変更しない。　2016/3/1
	//for (int v = 0; v < PM.MVnum; v++) {
	//	for (int h = 0; h < PM.MHnum; h++) {
	//		if (MESH[v][h].flag == 0) continue;
	//		if (MESH[v][h].Acc >= 0.)	{
	//			if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[v][h].flag = ID_MESH_R;
	//			else   MESH[v][h].flag = ID_MESH;
	//			PM.Anum++;
	//		}
	//		else		MESH[v][h].flag = 0;
	//	}
	//}
	//Make_Mesh_Line();
	//
	/// ーーーーーーーーーーーーーーーーーーーーーーー矢印消去 選択消去
	GLobj_Delete(&Gp, OBJID_EDIT_ARROW);
	GLobj_Delete(&Gp, OBJID_SELECT);
	SI.Num = 0;
	//
	/// ーーーーーーーーーーーーーーーーーーーーーーー通常矢印描画
	Disp_Arrow();
	if (STAT(ENABLE_DRAW_ARROW)){
		Gp.Gobj[OBJID_ARROW].display = TRUE;
		STAT(DISP_ARROW) = TRUE;
	}
	else {
		Gp.Gobj[OBJID_ARROW].display = FALSE;
		STAT(DISP_ARROW) = FALSE;
	}
	///----------------------------------------------------------
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, ALL_OBJECTS, TRUE);
	///----------------------------------------------------------
	//   編集のため流下方向を保存しておく。
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) MESH[v][h].Adir0 = MESH[v][h].Adir;
	}
	//
	STAT(AVAIL_RESET) = FALSE;
	STAT(AVAIL_UNDO) = TRUE;
	Disp_Direction_Radio(UNDEF, UNDEF);
	Show_Mesh_Info(UNDEF, UNDEF);
	Disp_Controls();
	//
	DSET.need_save[ADIR_FILE] = TRUE;
}
///--------------------------------------------------
//		Noexitpos位置から流域を探索、流域番号とＡｃｃを調査
///--------------------------------------------------
void CRRI_GUIView::Get_Basin_Acc()
{
	int		v, h, ret;
	//
	for (int i = 0; i < NoexitNum; i++) {
		v = NoexitPos[i].y;
		h = NoexitPos[i].x;
		ret = Find_Mesh(i + 1, h, v);
	}
	return;
}
///--------------------------------------------------
//		FIND  ＢＡＳＩＮ　　　					
///--------------------------------------------------
int CRRI_GUIView::Find_Mesh(int Bno, int h, int v)
{
	int		InDir[8] = { 16, 32, 64, 128, 1, 2, 4, 8 };
	int		posH[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int		posV[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	int		ret, acc = 0;
	//
	for (int i = 0; i < 8; i++) {
		if (v + posV[i] < 0 || v + posV[i] >= PM.MVnum) continue;
		if (h + posH[i] < 0 || h + posH[i] >= PM.MHnum) continue;
		//
		if ((int)MESH[v + posV[i]][h + posH[i]].Adir == InDir[i]) {
			acc += Find_Mesh(Bno, h + posH[i], v + posV[i]);
			acc++;
		}
	}
	if (Bno != UNDEF) {
		MESH[v][h].Bno = Bno;
		MESH[v][h].Acc = acc;
	}
	//
	return acc;
}
///--------------------------------------------------
//		ＲＥＳＥＴ ＦＬＯＷ Ｄｉｒｅｃｔｉｏｎ　　		標高をみないで、方向のみでリセットする。　編集後
///--------------------------------------------------
void CRRI_GUIView::Reset_Flow_Direction()
{
	int      ret, V, H;
	int		InDir[8] = { 16, 32, 64, 128, 1, 2, 4, 8 };
	int		posH[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int		posV[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	//
	NoexitNum = 0;
	//
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			MESH[v][h].Bno = 0;
			if (MESH[v][h].flag == 0) continue;
			if (MESH[v][h].H == NODATA){ MESH[v][h].flag = FLAG_OFF; continue; } // 万一のため
			///
			// 流入数のカウント
			MESH[v][h].In = 0;
			for (int k = 0; k < 8; k++) {
				if (v + posV[k] < 0 || v + posV[k] >= PM.Vnum) continue;
				if (h + posH[k] < 0 || h + posH[k] >= PM.Hnum) continue;
				if (MESH[v + posV[k]][h + posH[k]].Adir == InDir[k]) MESH[v][h].In++;
			}
			///
			if (MESH[v][h].Adir == 0) {
				NoexitPos[NoexitNum].x = h;
				NoexitPos[NoexitNum++].y = v;
			}
		}
	}

	//
	Get_Basin_Acc();
	///
	return;
}

///--------------------------------------------------
//		CANCEL　編集操作のキャンセル
///--------------------------------------------------
void CRRI_GUIView::OnBnClickedButtonCancel()
{
	CButton*		cw;
	Change_Cursor(&Gp, IDC_WAIT);
	//
	if (STAT(CHANGE_DIRECTION)) {
		Show_Mesh_Info(UNDEF, UNDEF);
		//
		GLobj_Delete(&Gp, OBJID_EDIT_ARROW);
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_EDIT_ARROW, TRUE);
		//
		UHnum = 0;
		STAT(CHANGE_DIRECTION) = FALSE;
		STAT(AVAIL_RESET) = FALSE;
		STAT(AVAIL_UNDO) = FALSE;
		//
		GLobj_Delete(&Gp, OBJID_SELECT);
		SI.Num = 0;
		GL_Redraw(&Gp, FALSE, FALSE, FALSE, OBJID_SELECT, TRUE);
	}
	//
	Disp_Direction_Radio(UNDEF, UNDEF);
	Show_Mesh_Info(UNDEF, UNDEF);
	Disp_Controls();
}

///--------------------------------------------------
//		ＵＮＤＯ　編集操作のUNDO
///--------------------------------------------------

void CRRI_GUIView::OnBnClickedButtonDirUndo()
{
	if (UHnum0 == 0) return;
	//
	for (int i = 0; i < UHnum0; i++) MESH[UH[i].v][UH[i].h].Adir = UH[i].dir0;
	//
	UHnum = UHnum0 = 0;
	//
	Change_Cursor(&Gp, IDC_WAIT);
	///----------------------------------------------------------
	// 流域の定義を再度行う。
	///----------------------------------------------------------
	Reset_Flow_Direction();		// ACC の再計算も行われている。
	///
	//  flag は変更しない。   
	//for (int v = 0; v < PM.MVnum; v++) {
	//	for (int h = 0; h < PM.MHnum; h++) {
	//		if (MESH[v][h].flag == 0) continue;
	//		if (MESH[v][h].Acc >= 0.)	{
	//			if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[v][h].flag = ID_MESH_R;
	//			else   MESH[v][h].flag = ID_MESH;
	//			PM.Anum++;
	//		}
	//		else		MESH[v][h].flag = 0;
	//	}
	//}
	/////
	//Make_Mesh_Line();
	//GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_LINE, TRUE);
	//
	/// ーーーーーーーーーーーーーーーーーーーーーーー矢印消去 選択消去
	GLobj_Delete(&Gp, OBJID_EDIT_ARROW);
	GLobj_Delete(&Gp, OBJID_SELECT);
	SI.Num = 0;
	//
	/// ーーーーーーーーーーーーーーーーーーーーーーー通常矢印描画
	Disp_Arrow();
	if (STAT(ENABLE_DRAW_ARROW)){
		Gp.Gobj[OBJID_ARROW].display = TRUE;
		STAT(DISP_ARROW) = TRUE;
	}
	else {
		Gp.Gobj[OBJID_ARROW].display = FALSE;
		STAT(DISP_ARROW) = FALSE;
	}
	///----------------------------------------------------------
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, ALL_OBJECTS, TRUE);
	///----------------------------------------------------------
	//   編集のため流下方向を保存しておく。
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) MESH[v][h].Adir0 = MESH[v][h].Adir;
	}
	//
	STAT(AVAIL_RESET) = FALSE;
	STAT(AVAIL_UNDO) = FALSE;
	Disp_Direction_Radio(UNDEF, UNDEF);
	Show_Mesh_Info(UNDEF, UNDEF);
	Disp_Controls();
}

std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;//defined at Windwos.h
	std::vector<std::string> file_names;

	//拡張子の設定
	std::string search_name = dir_name + "\\*." + extension;

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			file_names.push_back(win32fd.cFileName);
			printf("%s\n", file_names.back().c_str());

		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return file_names;
}


///========================================================================
//  Cover.txt(JP) の作成
///========================================================================
	void CRRI_GUIView::OnBnClickedButtonLanduseJp()
{
		/* 範囲が限定されていることが前提 UTMは除外  MESH == NULLは除外*/
		if (!PM.set || !PM.B_LatLng || MESH == NULL) {
			MessageBox("** Error ** Making conditions are not enough", "error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		/* ＦＡＯファイルの存在　*/
		::SetCurrentDirectory(m_BootPath);
		//
		if (!File_Exist(FAO_FILE)) {
			MessageBox("** Error ** FAO file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		CRRI_GUIView::Set_LU_CodeTable();

		//--------------------------------------------------
		/* 基本的なセッティング　*/
		//--------------------------------------------------
		FILE*		fp;
		double		FAO_unit = 1. / 12.;				// 300 sec = 5 minutes
		int			FAO_Hnum = 4320, FAO_Vnum = 2160;	// 1 file number
		char**		FC;		/// 4320×2160
							//
		char			buf[SIZE_16K], inchar[SIZE_01K];
		int			pos, Ncnt;
		//
		double		H, V, H0, V0;
		//
		CBUSY*		CB;
		CB = new CBUSY;
		CB->Create(IDD_BUSY);
		CB->Set_Prog(0, 5);
		CB->ShowWindow(SW_SHOW);
		//--------------------------------------------------
		/*
		必要なファイル　　Manning係数  Manning.csv   ->1-7=0.06 Darcy  8-17=0.025,18=0.04  GreenAmpt
		土壌係数　　 FAO_PARAM.csv ->ksv ka, etc
		世界のデータ FAO_CODE_DATA.csv

		Darcy　適用の場合(山地）		ka = 0.
		GreenAmpt 適用の場合(平地）	ksv =0.
		*/
		//--------------------------------------------------
		///  世界のデータ FAO_CODE_DATA.csv の読み込み
		//
		CB->Set_Title("Read FAO_DATA");
		CB->Set_Pos(1);
		if ((fp = fopen(FAO_FILE, "r")) == NULL) {
			MessageBox("** Error ** FAO CODE  file not exist", "error", MB_OK | MB_ICONEXCLAMATION);
			CB->Close();	return;
		}
		//
		FC = Make_Matrix(FAO_Hnum, FAO_Vnum, (char)0xff);
		//
		for (int v = FAO_Vnum - 1; v >= 0; v--) {
			fgets(buf, SIZE_16K, fp); pos = 0;
			for (int h = 0; h < FAO_Hnum; h++) {
				getstr(buf, &pos, inchar, SIZE_01K); FC[v][h] = (char)atoi(inchar);
			}
		}
		fclose(fp);
		//------------------------  コード分類
		Ncnt = 0;
		if (PM.Size <= FAO_unit) {		// MESH の中心がＦＡＯのどのメッシュ範囲にあるか
			for (int v = 0; v < PM.MVnum; v++) {	// 西経180　南緯90を原点とする座標系に変換
				V = (90. + PM.stLAT + (v + 0.5)*PM.Size) / FAO_unit;
				for (int h = 0; h < PM.MHnum; h++) {
					H = (180. + PM.stLNG + (h + 0.5)*PM.Size) / FAO_unit;
					MESH[v][h].Soil = (short)FC[(int)V][(int)H];
					if (MESH[v][h].Soil == 0) Ncnt++;
				}
			}
		}
		else {
			MessageBox("** Error ** Model mesh size is too large > 5minite", "error", MB_OK | MB_ICONEXCLAMATION);
			Free_Matrix(FAO_Vnum, FC);
			CB->Close(); return;
		}
		Free_Matrix(FAO_Vnum, FC);
		//--------------------------------------------------
		///  ＦＡＯ のデータ０を補間 最近隣のデータを代入
		//
		if (Ncnt != 0) {
			int		eh, ev;
			for (int v = 0; v < PM.MVnum; v++) {
				for (int h = 0; h < PM.MHnum; h++) {
					if (MESH[v][h].flag == 0) continue;
					if (MESH[v][h].Soil != 0) continue;		// ０だけを対象とする。
															//
					eh = ev = 1;
					while (TRUE) {
						/*					if (PM.MHnum < h + eh) {
												MESH[v][h].Soil = 9;
												break;
											}
											if (PM.MVnum < v + ev) {
												MESH[v][h].Soil = 9;
												break;
											}*/
						if (eh > PM.MHnum) break;
						if (ev > PM.MVnum) break;
						if (h + eh < PM.MHnum) {
							if (!(MESH[v][h + eh].Soil == 0 || MESH[v][h + eh].Soil > 100)) {
								MESH[v][h].Soil = MESH[v][h + eh].Soil + 100;
								break;
							}
						}
						if (h - eh >= 0) {
							if (!(MESH[v][h - eh].Soil == 0 || MESH[v][h - eh].Soil > 100)) {
								MESH[v][h].Soil = MESH[v][h - eh].Soil + 100;
								break;
							}
						}
						if (v + ev < PM.MVnum) {
							if (!(MESH[v + ev][h].Soil == 0 || MESH[v + ev][h].Soil > 100)) {
								MESH[v][h].Soil = MESH[v + ev][h].Soil + 100;
								break;
							}
						}
						if (v - ev >= 0) {
							if (!(MESH[v - ev][h].Soil == 0 || MESH[v - ev][h].Soil > 100)) {
								MESH[v][h].Soil = MESH[v - ev][h].Soil + 100;
								break;
							}
						}
						eh++;
						ev++;
					}
					if (MESH[v][h].Soil == 0) {  	//20190905
					
						MESH[v][h].Soil = 12 + 100;
					}
					
				}
			}
			for (int v = 0; v < PM.MVnum; v++) {
				for (int h = 0; h < PM.MHnum; h++) {
					if (MESH[v][h].flag == 0) continue;
					if (MESH[v][h].Soil > 100) MESH[v][h].Soil -= 100;
				}
			}
		}

		//
		CB->Set_Title("Read Cover_DATA");
		CB->Set_Pos(1);

		CString	path;
		CString	fname;
		double	lat;
		double	lng;
		CString	type[] = { "elv", "upg", "dir" };
		int	v = 0;
		int	h = 0;
		int	cnt, fnmLng, fnmLat;
		//
		// DEM,ACC,DIR でループ読み込み
		//
		::SetCurrentDirectory(m_BootPath);

		lat = 0;
		lng = 0;

		h = 0;
		v = 0;
		CB->Set_Pos(3);
		int ludat = 0;

		int code[999], chcode[999], lpcnt = 0;
		char name[256], area[256];

		FILE *reclassify;
		reclassify = fopen("./RRI_CONTENTS/LandUse/J_lnd_reclassify.csv", "r");
		if (reclassify == NULL) {
			MessageBox("Cannot open J_lnd_reclassify.csv file", "Exit", MB_OK | MB_ICONEXCLAMATION);
			DestroyWindow(); exit(1);
		}
		fgets(buf, SIZE_1K, reclassify);// 1行目　タイトル
		fgets(buf, SIZE_1K, reclassify);// 2行目　ヘッダ
		while (fgets(buf, SIZE_1K, reclassify) != NULL) {

			sscanf(buf, "%d,%[^,],%d,%[^,]", &code[lpcnt], &name, &chcode[lpcnt], &area);
			lpcnt++;

		}
		code[lpcnt] = 0;
		chcode[lpcnt] = 0;

		fclose(reclassify);

		for (h = 0; h < PM.MHnum; h++) {

			for (v = 0; v < PM.MVnum; v++) {

				if (MESH[PM.MVnum - v - 1][h].flag == 0) {
					continue;
				}

				//lat = MESH[PM.MVnum - v - 1][h].AtLat - (MESH_LATLNG_WIDTH_5S / 2);
				//lng = MESH[PM.MVnum - v - 1][h].AtLng + (MESH_LATLNG_WIDTH_5S / 2); 
				lat = MESH[PM.MVnum - v - 1][h].AtLat - (PM.Size / 2);
				lng = MESH[PM.MVnum - v - 1][h].AtLng + (PM.Size / 2); 

				fnmLat = floor(lat*1.5);
				fnmLng = lng - 100;

				path.Format("%s\\RRI_CONTENTS\\LandUse\\LanduseSubdivisionMesh", m_BootPath);
				fname.Format("%s\\L03-b-14_%d%d.tif", path, fnmLat, fnmLng);

				MESH[PM.MVnum - v - 1][h].Cover = Get_J_Flw_Value(fname, lng, lat);

				for (int i = 0; i <= lpcnt; i++) {
					if (i == lpcnt) {
						MESH[PM.MVnum - v - 1][h].Cover = -9999;
						break;
					}
					if (code[i] == (int)MESH[PM.MVnum - v - 1][h].Cover) {
						MESH[PM.MVnum - v - 1][h].Cover = chcode[i];
						break;
					}
				}

				if (MESH[PM.MVnum - v - 1][h].Cover == 0) {
					continue;
				}

			}

		}

		///
		// Ｏｕｔｐｕｔ
		DSET.b_CSexist = TRUE;
		//
		//Write_Data_File(LAND_COVER, 0, 0, DSET, PM, MESH);
		DSET.in_use[LAND_SOIL] = DSET.in_avail[LAND_SOIL] = DSET.in_exist[LAND_SOIL] = DSET.need_save[LAND_SOIL] = TRUE;
		Write_Data_File(LAND_SOIL, 0, 0, DSET, PM, MESH);

		DSET.in_use[LAND_COVER] = DSET.in_avail[LAND_COVER] = DSET.in_exist[LAND_COVER] = DSET.need_save[LAND_COVER] = TRUE;
		//DSET.LUnum = 5;
		Write_Data_File(LAND_COVER, 0, 0, DSET, PM, MESH);

		//
		CB->DestroyWindow();
		MessageBox("Make Cover and Soil data...done !", "Ready", MB_OK | MB_ICONASTERISK);

}


///========================================================================
//  Cover.txt(JP) の作成
///========================================================================
void CRRI_GUIView::OnBnClickedButtonLanduseJp2()
{
	/* 範囲が限定されていることが前提 UTMは除外  MESH == NULLは除外*/
	if (!PM.set || !PM.B_LatLng || MESH == NULL) {
		MessageBox("** Error ** Making conditions are not enough", "error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CRRI_GUIView::Set_LU_CodeTable();
	//--------------------------------------------------
	/* 基本的なセッティング　*/
	//--------------------------------------------------
	FILE*		fp;
	double		FAO_unit = 1. / 12.;				// 300 sec = 5 minutes
	int			FAO_Hnum = 4320, FAO_Vnum = 2160;	// 1 file number
	char**		FC;		/// 4320×2160
						//
	char			buf[SIZE_16K], inchar[SIZE_01K];
	int			pos, Ncnt;
	//
	double		H, V, H0, V0;
	//
	CBUSY*		CB;
	CB = new CBUSY;
	CB->Create(IDD_BUSY);
	CB->Set_Prog(0, 5);
	CB->ShowWindow(SW_SHOW);

	//
	CB->Set_Title("Read Cover_DATA");
	CB->Set_Pos(1);

	CString	path;
	CString	fname;
	double	lat;
	double	lng;
	CString	type[] = { "elv", "upg", "dir" };
	int	v = 0;
	int	h = 0;
	int	cnt, fnmLng, fnmLat;
	//
	// DEM,ACC,DIR でループ読み込み
	//
	::SetCurrentDirectory(m_BootPath);

	lat = 0;
	lng = 0;

	h = 0;
	v = 0;
	CB->Set_Pos(3);
	int ludat = 0;

	int code[999], chcode[999], lpcnt = 0;
	char name[256], area[256];

	FILE *reclassify;
	reclassify = fopen("./RRI_CONTENTS/LandUse/J_lnd_reclassify.csv", "r");
	if (reclassify == NULL) {
		MessageBox("Cannot open J_lnd_reclassify.csv file", "Exit", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(); exit(1);
	}
	fgets(buf, SIZE_1K, reclassify);// 1行目　タイトル
	fgets(buf, SIZE_1K, reclassify);// 2行目　ヘッダ
	while (fgets(buf, SIZE_1K, reclassify) != NULL) {
		sscanf(buf, "%d,%[^,],%d,%[^,]", &code[lpcnt], &name, &chcode[lpcnt], &area);
		lpcnt++;

	}
	code[lpcnt] = 0;
	chcode[lpcnt] = 0;

	fclose(reclassify);
	CString key;
	path.Format("%s\\RRI_CONTENTS\\LandUse\\LanduseSubdivisionMesh", m_BootPath);
	std::map<CString, JFlowCache> mapCache;
	GDALAllRegister();
	for (h = 0; h < PM.MHnum; h++) {
		for (v = 0; v < PM.MVnum; v++) {
			if (MESH[PM.MVnum - v - 1][h].flag == 0) {
				continue;
			}

			//lat = MESH[PM.MVnum - v - 1][h].AtLat - (MESH_LATLNG_WIDTH_5S / 2);
			//lng = MESH[PM.MVnum - v - 1][h].AtLng + (MESH_LATLNG_WIDTH_5S / 2);
			lat = MESH[PM.MVnum - v - 1][h].AtLat - (PM.Size / 2);
			lng = MESH[PM.MVnum - v - 1][h].AtLng + (PM.Size / 2);

			fnmLat = floor(lat*1.5);
			fnmLng = lng - 100;

			std::map<CString, JFlowCache>::iterator l_it;
			key.Format("%d,%d", (int)fnmLng, (int)fnmLat);
			l_it = mapCache.find(key);
			if (l_it == mapCache.end()) {
				fname.Format("%s\\L03-b-14_%d%d.tif", path, fnmLat, fnmLng);
				JFlowCache areaCache;
				if (Create_J_Flw_Cache(fname, &areaCache)) {
					mapCache.insert(std::pair<CString, JFlowCache>(key, areaCache));
				};
			}

			if (mapCache.find(key) != mapCache.end()) {
				MESH[PM.MVnum - v - 1][h].Lu = Get_J_Flw_Value_From_Cache(lng, lat, &mapCache.find(key)->second);
			}

			for (int i = 0; i <= lpcnt; i++) {
				if (i == lpcnt) {
					MESH[PM.MVnum - v - 1][h].Lu = -9999;
					MESH[PM.MVnum - v - 1][h].Cover = -9999;
					break;
				}
				if (code[i] == (int) MESH[PM.MVnum - v - 1][h].Lu) {
					MESH[PM.MVnum - v - 1][h].Lu = chcode[i];
					MESH[PM.MVnum - v - 1][h].Cover = chcode[i];
					break;
				}
			}

			if (MESH[PM.MVnum - v - 1][h].Lu == 0) {
				continue;
			}
		}
	}

	for (std::map<CString, JFlowCache>::iterator mapIter = mapCache.begin(); mapIter != mapCache.end(); mapIter++) {
		CPLFree(mapIter->second.datas);
	};
	GDALDestroyDriverManager();

    int lunum = 0;

	//  land usage elements
	FILE *jlndparam;
	jlndparam = fopen("./RRI_CONTENTS/LandUse/J_lnd_PARAM.txt", "r");
	if (jlndparam == NULL) {
		MessageBox("Cannot open J_lnd_PARAM.txt file", "Exit", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(); exit(1);
	}

	fgets(buf, SIZE_1K, jlndparam);// 1行目　LU_NUM

	sscanf(buf, "%d", &lunum);

	DSET.LUnum = lunum;
	DSET.LUmem = lunum + 1;

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K);
		DSET.LUdata[i].SW_kinema = (BYTE)atoi(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].ns_slope = Get_DecodedVal_Exponent(inchar);
	}
	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K);
		DSET.LUdata[i].soildepth = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K);
		DSET.LUdata[i].gammaa = Get_DecodedVal_Exponent(inchar);
	}

	fgets(buf, SIZE_1K, jlndparam); // 空行

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].ksv = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].faif = Get_DecodedVal_Exponent(inchar);
	}
	
	fgets(buf, SIZE_1K, jlndparam); // 空行

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].ka = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].gammam = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].beta = Get_DecodedVal_Exponent(inchar);
	}

	fgets(buf, SIZE_1K, jlndparam); // 空行

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].kgv = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].gammag = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].tg = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].fpg = Get_DecodedVal_Exponent(inchar);
	}

	pos = 0;
	fgets(buf, SIZE_1K, jlndparam);
	for (int i = 0; i < lunum; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		DSET.LUdata[i].init_cond_gw = Get_DecodedVal_Exponent(inchar);
	}
	fclose(jlndparam);
	///
	// Ｏｕｔｐｕｔ




	DSET.b_CSexist = TRUE;
	//
	//Write_Data_File(LAND_COVER, 0, 0, DSET, PM, MESH);
/*	DSET.in_use[LAND_SOIL] = DSET.in_avail[LAND_SOIL] = DSET.in_exist[LAND_SOIL] = DSET.need_save[LAND_SOIL] = TRUE;
	Write_Data_File(LAND_SOIL, 0, 0, DSET, PM, MESH);*/

	//DSET.in_use[LAND_COVER] = DSET.in_avail[LAND_COVER] = DSET.in_exist[LAND_COVER] = DSET.need_save[LAND_COVER] = TRUE;
	//DSET.LUnum = 5;
	Write_Data_File(LAND_COVER, 0, 0, DSET, PM, MESH);
	PM.B_UseJFlow = TRUE;

	DSET.in_use[LU_FILE] = DSET.in_avail[LU_FILE] = DSET.in_exist[LU_FILE] = DSET.need_save[LU_FILE] = TRUE;
	//DSET.LUnum = 5;
	Write_Data_File(LU_FILE, 0, 0, DSET, PM, MESH);

	//

	CB->DestroyWindow();
	MessageBox("Make landuse data...done !", "Ready", MB_OK | MB_ICONASTERISK);
}


void CRRI_GUIView::OnStnClickedStatic214()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CRThiessen   CRAIN;
	CString		fname;
	int			ret;
	FILE* fp;
	//
	Get_Period();
	if (PM.StTime == NULL || PM.EndTime == NULL) {
		MessageBox("Start time or end time is not found\nNeed specific period....", "Cancel", MB_OK | MB_ICONERROR);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Free
	if (DSET.EV != 0 && DSET.EAcc != NULL)
		Free_Matrix(DSET.EV, DSET.EAcc);
	if (DSET.Emem != 0) {
		for (int i = 0; i < DSET.Emem; i++) Free_Matrix(DSET.EV, DSET.Edata[i].data);
		SAFE_FREE(DSET.Edata);
		DSET.Emem = 0;
	}
	//
	CRAIN.Dtitle = "Make  evaporation data ";
	CRAIN.kind = 1;
	if ((ret = CRAIN.DoModal()) == IDCANCEL) return;
	//
	if (CRAIN.Return_Val == 0) {
		strcpy(DSET.File_names[POTENT_FILE], CRAIN.RainF);
		Get_Relative_Path(DSET.File_names[POTENT_FILE], DSET.Proj_Folder, DSET.Input_names[POTENT_FILE]);
		fname = DSET.File_names[POTENT_FILE];
		Read_Data_File(POTENT_FILE, fname, &DSET, MESH);		// 累加蒸発散も読み込まれる。

																///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																//
		CTimeSpan  ts = PM.EndTime - PM.StTime;
		DSET.Hours = DSET.CT_Evp = ts.GetTotalHours();
		DSET.in_avail[POTENT_FILE] = DSET.in_use[POTENT_FILE] = TRUE;
		//
		//
		if (CDATA == POTENT_FILE) {	// 現在表示設定がされている
			Change_Cursor(&Gp, IDC_WAIT);
			Make_TS_Model();
			GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_TS, TRUE);
		}
		//
		COMMENT("Succeeded in making evaporation data");
	}
	else { COMMENT("** Failed in making evaporation data"); }
	//
	Write_RRI_INPUT(DSET);
	//
	Disp_Controls();
}

void CRRI_GUIView::OnBnClickedBtnSetsedim()
{
	DSET.in_avail[SED_FILE] = FALSE;
	DSET.in_use[SED_FILE] = FALSE;

	if (!InitSedFile()) RETURN("** Error ** init sed file failed!");
	
	Change_Cursor(&Gp, IDC_WAIT);
	DSET.in_avail[SED_FILE] = TRUE;
	DSET.in_use[SED_FILE] = TRUE;

	if (SaveSedInputFile()) {
		Get_Relative_Path(DSET.File_names[SED_FILE], DSET.Proj_Folder, DSET.Input_names[SED_FILE]);

		CDATA = SED_FILE;
		Make_Mesh_Model();
		GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_MESH, TRUE);

		RefreshSedRectLine();
		Make_LEGEND();
	}
	else {
		PopupMessage({ "Save sed data file path to sed_input file failed!" });
		DSET.in_avail[SED_FILE] = FALSE;
		DSET.in_use[SED_FILE] = FALSE;
		DeleteFileWithPath(DSET.File_names[SED_FILE]);
	}
	Change_Cursor(&Gp, IDC_ARROW);
}

bool CRRI_GUIView::IsSedEnabled() {
	std::string fSed(DSET.File_names[SED_FILE]);
	return !fSed.empty();
}

bool CRRI_GUIView::LoadSedInputFile() {
	fSedInputPath = DSET.Proj_Folder;
	fSedInputPath += "\\sed_input.txt";
	if (!File_Exist(fSedInputPath.c_str())) {
		std::string fSeedSedInputPath(m_BootPath);
		fSeedSedInputPath += "\\RRI_CONTENTS\\sed_input.txt";
		if (0 == CopyFile(fSeedSedInputPath.c_str(), fSedInputPath.c_str(), FALSE)) {
			MessageBox("copy template sed_input.txt failed...!\nExit...", "Abend", MB_OK | MB_ICONASTERISK);
			return false;
		}
	}
	std::ifstream reader(fSedInputPath);
	if (!reader) {
		MessageBox("Cannot open sed_input.txt...!\nExit...", "Abend", MB_OK | MB_ICONASTERISK);
		return false;
	}
	std::string			line;
	int					nl = 0;
	bool				rs = false;
	constexpr size_t	nFileInUseFlag = 69;
	constexpr size_t	nFilePathLine = nFileInUseFlag + 1;

	fSedInputLines.clear();
	while (nl++, std::getline(reader, line)) {
		fSedInputLines.push_back(line);

		if (nl == nFileInUseFlag) {
			std::istringstream iss(line);
			if (!(iss >> DSET.in_use[SED_FILE])) break;
		}
		else if (nl == nFilePathLine) {
			std::string fSedPath(line);
			if (fSedPath.size() <= 1) break;
			strcpy(DSET.Input_names[SED_FILE], fSedPath.c_str());
			sprintf(DSET.File_names[SED_FILE], "%s%s", DSET.Proj_Folder, fSedPath.substr(1).c_str());

			//if there is no sed file at the set file path, disable the in_use flag
			if (!File_Exist(DSET.File_names[SED_FILE])) DSET.in_use[SED_FILE] = FALSE;
			rs = true;
		}
	}
	reader.close();

	if (!rs) fSedInputLines.clear();
	return rs;
}

bool CRRI_GUIView::InitSedFile() {
	std::string fname;
	std::string rootPath;
	std::string fSedPath(DSET.File_names[SED_FILE]);
	if (fSedPath.empty()) {
		std::stringstream f;
		f << m_BootPath << "\\Project\\" << DSET.Proj_Title << "\\topo";
		rootPath = f.str();
		fname = "sed.txt";
	} else {
		std::replace(fSedPath.begin(), fSedPath.end(), '/', '\\');
		auto lenSedPath = fSedPath.length();
		auto index = fSedPath.rfind('\\', lenSedPath);
		if (index != std::string::npos) {
			rootPath = fSedPath.substr(0, index);
			fname = fSedPath.substr(index + 1, lenSedPath - index);
			RightTrim(fname, std::string(" "));
		}
	}
	const TCHAR szFilter[] = _T("Sed Data File  (*.txt)|*.txt||");
	CFileDialog	fDlg(FALSE, _T("txt"), fname.c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)szFilter, NULL);
	fDlg.m_ofn.lpstrInitialDir = rootPath.c_str();

	if (fDlg.DoModal() != IDOK) {
		return false;
	}

	fname = fDlg.GetPathName().GetString();
	UpdateDsWithFFullPath(fname.c_str(), SED_FILE);

	FILE* fp;
	if ((fp = fopen(fname.c_str(), "w")) == NULL) {
		return false;
	}

	fprintf(fp, "ncols	 %d\n", PM.MHnum);
	fprintf(fp, "nrows	 %d\n", PM.MVnum);
	fprintf(fp, "xllcorner	 %.1lf\n", PM.stLNG);
	fprintf(fp, "yllcorner	 %.1lf\n", PM.stLAT);
	fprintf(fp, "cellsize	 %.14lf\n", PM.Size);
	fprintf(fp, "NODATA_value  -9999 \n");

	for (int y = 0; y < PM.MVnum; y++) {
		auto v = PM.MVnum - 1 - y;
		MESH[v][0].Sed = 0;
		if (MESH[v][0].flag >= 1) {		// ＭＥＳＨは下から上　ＤＡＴＡは上から下
			fprintf(fp, "%5d", 0);
		}
		else {
			fprintf(fp, " -9999");
		}
		for (int h = 1; h < PM.MHnum; h++) {
			MESH[v][h].Sed = 0;
			if (MESH[v][h].flag >= 1) {		// ＭＥＳＨは下から上　ＤＡＴＡは上から下
				fprintf(fp, "   %5d", 0);
			}
			else {
				fprintf(fp, "   -9999");
			}
		}
		fprintf(fp, "\n");
	}
	return true;
}

bool CRRI_GUIView::ExtractSubBasin(std::string& fPath, UINT32 pIdX, UINT32 pIdY) {
	if (!ExtractSubBasin(pIdX, pIdY)) return false;

	fPath = DSET.Proj_Folder;
	fPath += "\\topo\\dir.txt_basin.txt";
	if (!File_Exist(fPath.c_str())) {
		PopupMessage({ "** Error ** Cannot find extracted sub basin data file! Point: ", std::to_string(pIdX), ", ", std::to_string(pIdY) });
		return false;
	}
	return true;
}

bool CRRI_GUIView::ExtractSubBasin(UINT32 pIdX, UINT32 pIdY) {
	std::string wsDir(DSET.Proj_Folder);
	wsDir += "\\topo";
	::SetCurrentDirectory(wsDir.c_str());

	std::string exePath(m_BootPath);
	exePath += "\\Tools\\extract_basin.exe";
	if (!File_Exist(exePath.c_str())) {
		PopupMessage({ "** Error ** extract_basin.exe does not exist " });
		return false;
	}

	// プロセスを起動
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	std::stringstream cmdLine;
	cmdLine << exePath.c_str() << " dir.txt " << pIdY << " " << pIdX;
	char cCmdLine[SIZE_05K] = {0};
	sprintf(cCmdLine, "%s", cmdLine.str().c_str());
	::CreateProcess(NULL, cCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// 終了まで待機
	::WaitForSingleObject(pi.hProcess, INFINITE);

	// 終了を告知
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
	return true;
}

bool CRRI_GUIView::LoadSubBasinHeader(const std::string& fPath, MeshDataHeader* headerInfo, CPoint* offsetSet)
{
	if (nullptr == headerInfo || nullptr == offsetSet) {
		PopupMessage({ "** Error ** Invalid point!" });
		return false;
	}
	if (!File_Exist(fPath.c_str())) {
		PopupMessage({ "** Error ** sub basin data file does not exist!" });
		return false;
	}
	if (0 != Get_ArcGIS_Info(fPath.c_str(), &headerInfo->ncols, &headerInfo->nrows,
		&headerInfo->yllcorner, &headerInfo->xllcorner, &headerInfo->cellsize)) {
		PopupMessage({ "** Error ** read sub basin data file failed! " });
		return false;
	}
	if (headerInfo->nrows <= 0 || headerInfo->ncols <= 0) {
		PopupMessage({ "** Error ** row or column of sub basin data file is empty!" });
		return false;
	}
	
	//get index of left top point
	auto cellsize = 1.0 / PM.Coord_Unit;
	auto ltX = headerInfo->xllcorner;
	auto ltY = headerInfo->yllcorner + (headerInfo->nrows - 1) * cellsize;
	auto baseLtX = PM.stLNG;
	auto baseLtY = PM.stLAT + (PM.MVnum - 1) * cellsize;

	//mapping index to base mesh
	int ofstX = static_cast<int>(std::round((ltX - baseLtX) * PM.Coord_Unit));
	int ofstY = static_cast<int>(std::round((baseLtY - ltY) * PM.Coord_Unit));

	if (ofstX < 0 || ofstY < 0) {
		PopupMessage({ "** Error ** offset in sub basin data must not lower than 0. ofstX: ",
			std::to_string(ofstX), ", ofstY: ", std::to_string(ofstY) });
		return false;
	}
	if (ofstX + headerInfo->ncols > PM.MHnum || ofstY + headerInfo->nrows > PM.MVnum) {
		PopupMessage({ "** Error ** offset in sub basin data must not higher than base max values. ofstX + cols: ",
			std::to_string(ofstX + headerInfo->ncols), ", ofstY + rows: ", std::to_string(ofstY + headerInfo->nrows) });
		return false;
	}

	offsetSet->x = ofstX;
	offsetSet->y = ofstY;
	return true;
}

bool CRRI_GUIView::LoadSubBasinData(const std::string& fPath, const MeshDataHeader& headerInfo, int** data) {
	if (data == nullptr) {
		PopupMessage({ "** Error ** data point is empty!" });
		return false;
	}
	FILE* fp;
	if ((fp = fopen(fPath.c_str(), "r")) == NULL) {
		PopupMessage({ "** Error ** read sub basin data file failed!" });
		return false;
	}

	char	buf[SIZE_12K], inchar[SIZE_003K];
	for (int i = 0; i < 6; i++) { 
		if (fgets(buf, SIZE_12K, fp) == NULL) { fclose(fp); return false; };
	}

	for (int y = 0; y < headerInfo.nrows; y++) {
		if (fgets(buf, SIZE_12K, fp) == NULL) { fclose(fp); return false; }
		for (int x = 0, pos = 0; x < headerInfo.ncols; x++) {
			if (getstr(buf, &pos, inchar, SIZE_01K) == EOF) { fclose(fp); return false; }
			data[y][x] = atoi(inchar);
		}
	}
	fclose(fp);
	return true;
}

bool CRRI_GUIView::DrawTempSubBasinData(const CPoint& offsetSet, const MeshDataHeader& headerInfo, int** data)
{
	GLobj_Delete(&Gp, OBJID_SED);
	if (CDATA != SED_FILE) return false;

	FCOLOR						fcol;
	bool						vValid = false;
	std::vector<DrawPolyInfo>	vPointInfos;
	for (int y = 0; y < PM.MVnum; y++) {    //position index:  top -> bottom
		auto vMesh = PM.MVnum - 1 - y;
		auto vTemp = y - offsetSet.y;
		vValid = vTemp >= 0 && vTemp < headerInfo.nrows;
		for (int h = 0; h < PM.MHnum; h++) {
			fcol.set = FALSE;
			
			auto hTemp = h - offsetSet.x;
			if (vValid && hTemp >= 0 && hTemp < headerInfo.ncols && data[vTemp][hTemp] == ms_SubBasinDataVal) {
				fcol = F_COLOR(50, 50, 50);
				fcol.set = TRUE;
			}
			else if (MESH[vMesh][h].Sed > 0) {
				Get_Data_Color(TRUE, vMesh, h, 0., &fcol, SED_FILE);   //mesh sed data color
				fcol.set = TRUE;
			}

			if(fcol.set) vPointInfos.push_back(DrawPolyInfo(CPoint(h, vMesh), fcol));
		}
	}

	auto drawPoints = vPointInfos.size();
	GL_OBJECT* obj = &Gp.Gobj[OBJID_SED];
	GLobj_Init(obj, drawPoints * 4, drawPoints);   //init GL object for points to draw

	int no[4];
	constexpr int lz = BOUNDARY_Z;
	for (const DrawPolyInfo& pi : vPointInfos)
	{
		auto lbx = static_cast<double>(pi.point.x + 0.01);
		auto lby = static_cast<double>(pi.point.y + 0.01);
		auto rtx = static_cast<double>(pi.point.x + 0.99);
		auto rty = static_cast<double>(pi.point.y + 0.99);
		no[0] = GLobj_Add_Vert(obj, lbx, lby, lz, FALSE);
		no[1] = GLobj_Add_Vert(obj, rtx, lby, lz, FALSE);
		no[2] = GLobj_Add_Vert(obj, rtx, rty, lz, FALSE);
		no[3] = GLobj_Add_Vert(obj, lbx, rty, lz, FALSE);
		GLobj_Add_Poly(obj, DIM_3D, 4, no, GL_LINE_LOOP, 2.f, pi.col);
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SED, TRUE);
	return true;
}

bool CRRI_GUIView::DrawSubBasinRect() {
	GLobj_Delete(&Gp, OBJID_SED);
	if (CDATA != SED_FILE) return false;

	//get points to draw
	std::vector<CPoint> vPoints;
	for (int v = 0; v < PM.MVnum; v++) {      //data index: bottom -> top
		for (int h = 0; h < PM.MHnum; h++)
		{
			if (MESH[v][h].Sed > 0) {
				vPoints.push_back(CPoint(h, v));
			}
		}
	}

	auto drawPoints = vPoints.size();
	GL_OBJECT* obj = &Gp.Gobj[OBJID_SED];
	GLobj_Init(obj, drawPoints * 4, drawPoints);   //init GL object for points to draw

	int			no[4];
	FCOLOR		fcol;
	constexpr	int lz = BOUNDARY_Z;
	for (auto p : vPoints) {
		auto lbx = static_cast<double>(p.x + 0.01);
		auto lby = static_cast<double>(p.y + 0.01);
		auto rtx = static_cast<double>(p.x + 0.99);
		auto rty = static_cast<double>(p.y + 0.99);
		no[0] = GLobj_Add_Vert(obj, lbx, lby, lz, FALSE);
		no[1] = GLobj_Add_Vert(obj, rtx, lby, lz, FALSE);
		no[2] = GLobj_Add_Vert(obj, rtx, rty, lz, FALSE);
		no[3] = GLobj_Add_Vert(obj, lbx, rty, lz, FALSE);

		Get_Data_Color(TRUE, p.y, p.x, 0., &fcol, SED_FILE);
		GLobj_Add_Poly(obj, DIM_3D, 4, no, GL_LINE_LOOP, 2.f, fcol);
	}
	GL_Redraw(&Gp, FALSE, FALSE, TRUE, OBJID_SED, TRUE);
	return true;
}

bool CRRI_GUIView::UpdateSedFile() 
{
	std::string fPath(DSET.File_names[SED_FILE]);

	FILE* fp;
	if ((fp = fopen(fPath.c_str(), "w")) == NULL) {
		PopupMessage({ "update sed file failed!" });
		return false;
	}

	fprintf(fp, "ncols	 %d\n", PM.MHnum);
	fprintf(fp, "nrows	 %d\n", PM.MVnum);
	fprintf(fp, "xllcorner	 %.1lf\n", PM.stLNG);
	fprintf(fp, "yllcorner	 %.1lf\n", PM.stLAT);
	fprintf(fp, "cellsize	 %.14lf\n", PM.Size);
	fprintf(fp, "NODATA_value  -9999 \n");

	for (int y = 0; y < PM.MVnum; y++) {
		auto v = PM.MVnum - 1 - y;
		if (MESH[v][0].flag >= 1) {
			fprintf(fp, "%5d", MESH[v][0].Sed);
		} else {
			fprintf(fp, " -9999");
		}
		
		for (int h = 1; h < PM.MHnum; h++) {
			if (MESH[v][h].flag >= 1) {
				fprintf(fp, "   %5d", MESH[v][h].Sed);
			} else {
				fprintf(fp, "   -9999");
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return true;
}

void CRRI_GUIView::RefreshSedRectLine() {
	DrawSubBasinRect();
}

//public functions
void CRRI_GUIView::PopupMessage(std::vector<std::string> msgItems, std::string title, bool isError)
{
	std::stringstream msg;
	for (auto item : msgItems) {
		msg << item;
	}
	auto flag = MB_OK;
	if (isError) flag |= MB_ICONERROR;
	MessageBox(_T(msg.str().c_str()), title.c_str(), flag);
}

std::string& CRRI_GUIView::RightTrim(std::string& str, std::string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

bool CRRI_GUIView::DeleteFileWithPath(LPCSTR fPath)
{
	if (File_Exist(_T(fPath))) DeleteFile(fPath);
	return true;
}

bool CRRI_GUIView::UpdateDsWithFFullPath(const char* csfPath, const size_t id) {
	if (id > FILE_IN_NUM) return false;
	strcpy(DSET.File_names[id], csfPath);
	Get_Relative_Path(DSET.File_names[id], DSET.Proj_Folder, DSET.Input_names[id]);
	return true;
}

bool CRRI_GUIView::SaveSedInputFile() {
	constexpr size_t nFileInUseFlag = 69;
	constexpr size_t nFilePathLine = nFileInUseFlag + 1;
	
	if (fSedInputLines.size() < nFilePathLine && !LoadSedInputFile()) {
		PopupMessage({ "loaded sed_input file contents are invalid!" });
		return false;
	}

	try {
		std::ofstream file(fSedInputPath);
		for (size_t i = 0; i < fSedInputLines.size(); i++) {
			auto nl = i + 1;
			std::string line(fSedInputLines[i]);
			if (nl == nFileInUseFlag) {
				line = std::to_string(DSET.in_use[SED_FILE]);
			} else if (nl == nFilePathLine) {
				line = DSET.Input_names[SED_FILE];
			}
			file << line << std::endl;
		}
	} catch (const std::exception& e) {
		return false;
	}

	return true;
}