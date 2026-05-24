#pragma once
///////////////////////////////////////////////////////////////////////////////////
// RRI 共通の変数・関数
//
//
///////////////////////////////////////////////////////////////////////////////////
#include		"RRI_GUI.h"
#include		"CommFuncs.h"
#include		<map>
#include		<vector>

#define		WM_ASEDIT_ENCHANGE	0x8888		// 0-WM_APP(0x8000) Reserved  
#define		WM_ASEDIT_FOCUS       0x8889   	// 0-WM_APP(0x8000) Reserved  
// Application Message Area  0x8000-0xBFFF
// Application String Message  Area  0xC000 - 0xFFFF  0x10000- Reserved
// after define  Register with [RegisterWindowMessage関数]

// ° ′ ″


#define		RRI_FILE_TOP				"RRI_Input_Format_Ver1_4_2"
#define		FAO_FILE					".\\RRI_CONTENTS\\LANDUSE\\FAO_CODE_DATA.csv"
#define		FAO_PARAM				".\\RRI_CONTENTS\\LANDUSE\\FAO_PARAM.csv"
#define		MANNING_FILE				".\\RRI_CONTENTS\\LANDUSE\\MANNING.csv"
#define		MANNING_FILE_JA				".\\RRI_CONTENTS\\LANDUSE\\MANNING_JA.csv"

#define		COVER_TITLE				"\\INPUTS\\parameters\\Cover.txt"
#define		SOIL_TITLE				"\\INPUTS\\parameters\\Soil.txt"

#define		GLC_PATH					".\\RRI_CONTENTS\\LANDUSE\\GLCNMO"
#define		EXTRACT_PATH				".\\RRI_CONTENTS\\LANDUSE\\GLCNMO\\EXDIR"
#ifdef VER_64
	#define		UNZIP_PROGRAM				".\\Tools\\UNZIP64\\7Z.EXE e -o"
#else
	#define		UNZIP_PROGRAM				".\\Tools\\UNZIP32\\7Z.EXE e -o"
#endif 

//----------------------------------------------------------------------------　TIMER
#define		INIT_TIMER				1
#define		RENDER_TIMER			2
#define		MODELING_TIMER			3
#define		ANIMATION_TIMER			4
#define		EDITTERM_TIMER			5

#define		SECTION_RENDER_TIMER	7
#define		PROFILE_RENDER_TIMER	8

#define		SEARCH_TIMER			10

#define		FORCUS_SEARCH_TIMER		11
#define		FORCUS_SEARCH_TIMER_BT	12

#define		GB_RENDER_TIMER			13

#define		TEMP_TIMER				20
//----------------------------------------------------------------------------　モード定義
#define		MODE_VIEW			0
#define		MODE_MODEL			1

#define		UPPER				0
#define		LOWER				1

#define		AREA				0
#define		RIVER				1
//
#define		CAM_DIR_UP			0
#define		CAM_DIR_LEFT		1
#define		CAM_DIR_RIGHT		2
//
//
#define		BOUND_OFFSET			30.f
#define		RIVPATH_OFFSET			20.f
#define		RIVER_OFFSET			10.f

#define		LINE_OFFSET				3.		// メッシュの高さ
#define		WL_OFFSET				5.
#define		DATA_OFFSET				30.

#define		BAND_HEIGHT				20.

#define		ORTHO_SCALE				0.01
#define		BACKGROUND_OFFY			50.
//
#define		ANIM_TIME_BASE			100
//
#define		VAL_INFINIT				9999999.
//
#define		DEFAULT_ACC				20
#define		NODATA					-9999
//----------------------------------------------------------------------------　COLOR
//
#define		DEFAULT_COL_MESH			RGB(130,130,50)
#define		DEFAULT_COL_MESHR			RGB(30,0,255)
#define		DEFAULT_COL_MESHB			RGB(255,0,0)
//
//----------------------------------------------------------------------------　パラメータ定義
#define		FILE_ALL_NUM		26
#define		FILE_IN_NUM			24
#define		FILE_IN_USE			21
#define		FILE_OUT_NUM		10
#define		FILE_GIS_NUM		6

#define		TS_ADD_MEM			20
#define		TS_MIN_WIDTH		500
#define		TS_MIN_HEIGHT		500

//----------------------------------------------------------------------------　WINDOW
#define		WIN_HYDRO		0
#define		WIN_R_PROF		1
#define		WIN_A_PROF		2
//----------------------------------------------------------------------------　ファイル
#define		RAIN_FILE		0		// Time Series
////
#define		GROUP1_START	1
#define		ADEM_FILE		GROUP1_START		// Mesh Param
#define		ACC_FILE		GROUP1_START+1		// Mesh Param
#define		ADIR_FILE		GROUP1_START+2		// Mesh Param
#define		SED_FILE		GROUP1_START+3		// Mesh 粒度   2021.09
////
#define		GROUP2_START	5
#define		LU_FILE			GROUP2_START		// Mesh Param
#define		WIDTH_FILE		GROUP2_START+1		// Mesh Param
#define		DEPTH_FILE		GROUP2_START+2		// Mesh Param
#define		HEIGHT_FILE		GROUP2_START+3		// Mesh Param
	////
#define		GROUP3_START	9
#define		HS_FILE			GROUP3_START		// Mesh
#define		HR_FILE			GROUP3_START+1		// Mesh
#define		HG_FILE			GROUP3_START+2		// Mesh Add 14
#define		GAMPT_FILE		GROUP3_START+3		// Mesh

////
#define		GROUP4_START	13
#define		HS_WLEV_FILE		GROUP4_START			// TimeSet
#define		HR_WLEV_FILE		GROUP4_START+1		// TimeSet
#define		QS_WLEV_FILE		GROUP4_START+2		// TimeSet
#define		QR_WLEV_FILE		GROUP4_START+3		// TimeSet
////
#define		DAM_CNT_FILE		GROUP4_START+4		// List
////
#define		DIV_FILE			GROUP4_START+5		// TimeSet
//
#define		POTENT_FILE			GROUP4_START+6		// Time Series
#define		LOCATION_FILE		GROUP4_START+7		// List

//
#define		NOT_IN_USE_START	FILE_IN_USE
#define		LENGTH_FILE			NOT_IN_USE_START		// Mesh Param
#define		SEC_MAP_FILE		NOT_IN_USE_START+1		// Mesh Param
#define		SEC_HEADER			NOT_IN_USE_START+2		// Each 

//
#define		NOT_IN_NUM_START	FILE_IN_NUM
#define		LAND_COVER		NOT_IN_NUM_START			// Land topo/Cover.txt
#define		LAND_SOIL		NOT_IN_NUM_START + 1		// Land topo/Soil.txt
// 2019.06.02
#define		LU_FILE_JP		NOT_IN_NUM_START + 2		// LandUse JP

/*
*/
#define		OUT_HS			0
#define		OUT_HR			1
#define		OUT_HG			2
#define		OUT_QR			3
#define		OUT_QU			4
#define		OUT_QV			5
#define		OUT_GU			6
#define		OUT_GV			7
#define		OUT_GAMPUT		8
#define		OUT_STORAGE		9
//#define		OUT_TECPLOT		10
//----------------------------------------------------------------------------　MESH COLOR

#define		ID_MESH			1
#define		ID_MESH_R		2
#define		ID_MESH_HS		3
#define		ID_MESH_HR		4
#define		ID_MESH_QS		5
#define		ID_MESH_QR		6
#define		ID_MESH_DAM		7
#define		ID_MESH_DIV		8
#define		ID_MESH_LOC		9

//----------------------------------------------------------------------------　HydroSHIELD
#ifndef		_EX_DATA
#define		_EX_DATA

#define		EX_DEM  0
#define     EX_ACC  1
#define     EX_DIR  2

typedef		struct _EX_FILE {
	BOOL		Bset;
	char		fname[SIZE_1K];
	int		span,byte,subdev;
	int		Vtotal, Htotal;
	int		stlng,endlng,Highlat,Lowlat;
} EX_FILE;
typedef		struct _EX_DATA {
	BOOL		Allset;
	int			kind;			// hydroSHEDS:0, arcGIS:1
	char		Gname[SIZE_01K];
	EX_FILE		Files[3];
}EX_DATA;
#endif

//----------------------------------------------------------------------------　RIV_INFO
#ifndef		_RIV_INFO
#define		_RIV_INFO

typedef		struct _RIV_INFO {
	double		x, y;
	double		lat, lng;
	int			acc;
} RIV_INFO;
#endif

//----------------------------------------------------------------------------　End
#ifndef		_TIMESET
#define		_TIMESET
typedef		struct  _TIMESET {
	BOOL			set;
	int			Fid;				// Fid == DIV_FILE の時、Tpos rate を設定
	int			Num,Mem,Span,Smem;
	//
	char**		name;
	CPoint*		pos;
	int*			time;
	double**		val;
//	double*		rate;
} TIMESET;
#endif
//
//
#ifndef		_LUINFO
#define		_LUINFO
typedef		struct  _LUINFO {
	int			NO,renumber,refcnt,appmesh;	// 使用される場合の番号、参照された数 
	int			appflag;						// パラメータ決定のための山地平地の区分　2016/02
	BYTE			SW_kinema;					// 常に１
	double		ns_slope,soildepth;
	double		ksv,gammaa, faif;
	double		ka, gammam, beta;;
	// 
	double		kgv, gammag, tg, fpg, init_cond_gw; // Add
} LUINFO;
#endif
//
#ifndef		_LOCATE_INFO
#define		_LOCATE_INFO
typedef		struct  _LOCATE_INFO {
	char			name[48];
	int			mx,mz;		// 上から座標
	int			Hid, Vid;	// 通常座標
	double		lat, lng;
	double		X, Z;		// 下からの通常位置
} LOCATE_INFO;
#endif
//
#ifndef		_DAMCNT
#define		_DAMCNT
typedef		struct  _DAMCNT {
	char		name[32];
	int			x,y;
	double		vol,startq;
} DAMCNT;
#endif
//
#ifndef		_DIVISION
#define		_DIVISION
typedef		struct  _DIVISION {
	char			name[32];
	int			ox, oy,tx,ty;
	double		rate;
} DIVISION;
#endif
//
#ifndef _COLVAL_FIX
#define _COLVAL_FIX
typedef	struct	_COLVAL_FIX {
	BOOL		set,Equal,Mos;
	float		alpha;
	int			num;
	double		val[21];		// 201601 Cover.txt の追加によるメモリー拡張
	COLORREF	Rcol[21];
	FCOLOR		Fcol[21];
} COLVAL_FIX;
#endif
//
#ifndef _SHAPE_BOX
#define _SHAPE_BOX
typedef	struct	_SHAPE_BOX {
	BOOL		set;
	int			ListID;
	char		name[64],info[32];
	int			Vnum,Mnum;
	XYCOORD*	XZ;
	int*		MID;
	double		Area;
	COLORREF	Col;
} SHAPE_BOX;
#endif

#ifndef _TDIM2_DATA
#define _TDIM2_DATA
typedef	struct	_TDIM2_DATA {
	CTime		time;
	double**	data;
} TDIM2_DATA;
#endif

#ifndef _CHANNEL_SEC
#define _CHANNEL_SEC
typedef	struct	_CHANNEL_SEC {
	double		h,R,B,nn;
} CHANNEL_SEC;
#endif

#ifndef _SELECT_INFO
#define _SELECT_INFO
typedef	struct	_SELECT_INFO {
	int			Num, Mem;	// ID,HVの大きさ、定義
	int			Nums[10];	// MESHの種類別、SLOPE,RIVER,等
	IXYCOORD*		ID;		// 表示座標
	IXYCOORD*		HV;		// 実座標
} SELECT_INFO;
#endif
///
//  UNDO

#ifndef _UndoHist
#define _UndoHist
typedef	struct _UndoHist {
	BYTE	dir, dir0;		// 変化方向　旧方向
	int		v, h;
} UndoHist;
#endif


///
// DATASET はメッシュデータに関する数値をまとめたもの
//
#ifndef		_DATASET
#define		_DATASET
typedef		struct  _DATASET {
	BOOL		set;
	BOOL		set_ProjDir;
	//
	CTime	BT;
	//--------------------------------------------- Basic Folder & File
	char		Proj_Folder[SIZE_02K];
	char		Proj_WebRRIFolder[SIZE_02K];	// 2026/05/24 Add
	char		Proj_Title[SIZE_02K];
	char		Folder_Name[8][SIZE_02K];
	char		EX_Dem_File[SIZE_02K];			// 外部のDEMデータファイル
	char		EX_Acc_File[SIZE_02K];			// 外部のACCデータファイル
	char		EX_Dir_File[SIZE_02K];			// 外部のDIRデータファイル
	char		Riv_File_Name[SIZE_02K];		// Riv.txt データファイル
	//
	int		Cin_Need,Cin_Exist;
	int		Cout_Need,Cout_Exist;
	//
	BOOL		in_use[ FILE_ALL_NUM];		// ＲＲＩ_ＩＮＰＵＴに指示されている。
	BOOL		in_exist[FILE_ALL_NUM];		// ファイルが存在する。
	BOOL		in_avail[FILE_ALL_NUM];		// プログラム内にメッシュデータがある。
	int		    Data_From[FILE_ALL_NUM];

	BOOL		need_save[FILE_ALL_NUM];	// 変更されている。 2016/03/01

	BOOL		out_exist[ FILE_OUT_NUM ],out_use[ FILE_OUT_NUM ];
//
	char		InputFile[SIZE_02K];
	char		InputWebRRIFile[SIZE_02K];		// 2026/05/24 Add
	//
	char		File_names[FILE_ALL_NUM][SIZE_02K], Input_names[FILE_ALL_NUM][SIZE_02K];
	char		Out_names[FILE_OUT_NUM][SIZE_02K];
	//
	//--------------------------------------------- Parameters
	BYTE			SW_LatLong,SW_Dir;
	int			Hours,DT,DT_Riv,Out_Num;
	//
	BOOL			b_CSexist;			// Cover,Soil の存在	// Add 201601
	BOOL			b_CSrenumber;			// 実行したかどうか
	int			LUnum,LUmem;
	LUINFO*		LUdata;
	LUINFO		LU_Model;			// 土地利用が１の場合のデフォルトのパラメータ
	char			CoverFile[SIZE_02K];	// Add 201601
	char			SoilFile[SIZE_02K];	// Add 201601
	//
	int			Damc_Num,Damc_Mem;
	DAMCNT*		DAMC;
	//
	int			Div_Num, Div_Mem;
	DIVISION*	DIVID;
	//
	BOOL		Riv_Avail;				// 201601
	double		Ns_River;
	double		Riv_Thresh;				// = Acc_Limit
	double		Cof_WC,Cof_WS,Cof_DC,Cof_DS;
	double		Cof_H,Cof_Hlim;
	//
	double		Init_HS,Init_HR,Init_HG,Init_Gamp;
	//
	double		Dem_nodata;
	///--------------------------------------------- RAIN EVP 
	//
	int			CT_Rain,CT_Evp;			// 現在時刻
	//
	double		Rain_Lng,Rain_Lat,Rain_dx,Rain_dy;
	int			Rmem,RT,RH,RV;			// 時間総数、雨量Hnum、Vnum
	TDIM2_DATA*	Rdata;					// MESH に関係なくここに記録する
	double**		RAcc;					// 累加雨量
	//
	int			RGmem, RGnum;				// 地上雨量観測点
	LOCATE_INFO*	RGpos;

	//-----------
	double		Evp_Lng, Evp_Lat, Evp_DX, Evp_DY;
	int			Emem,ET,EH,EV;
	TDIM2_DATA*	Edata;
	double**		EAcc;					// 累加蒸発散量
	//

	//--------------------------------------------- TimeSet
	TIMESET		HSWLEV,HRWLEV,QSWLEV,QRWLEV;

	//--------------------------------------------- Out Location
	int			Lnum,Lmem;
	LOCATE_INFO*	LCpos;

	//--------------------------------------------- RIV_TXT
	int**		RIVTXT;
	//
} DATASET;
#endif

//
//　PARAMSは　プログラムの遂行上必要なデータを格納したもの
//

#ifndef		_PARAMS
#define		_PARAMS
typedef		struct _PARAMS {
	BOOL			set,B_Color;						// セットされているか,バックのカラー表示
	BOOL			Model,WLmodel;					// モデル作成、水深モデルの作成
	BOOL			B_Back;							// 背景表示
	BOOL			B_MeshLine,B_DispLine;				// メッシュライン、ピクセル制限からの表示
	BOOL			B_ColorMesh;
	BOOL			B_Disp_Ground;					// 地上観測所の表示
	BOOL			B_Disp_Frame;						// モデル枠の表示
	BOOL			B_Disp_Legend;					// 凡例の表示
	//------------------------------------ Screen Tool
	BOOL			B_ScreenTool;						// スクリーンツールの表示
	double		Tool_Rate;						// 0.05 -0.3

	BOOL			B_LatLng;						// TRUE：緯度経度座標系（Default) FALSE:UTM 座標
	BOOL			B_UseGuide;						// ガイド使用の通常プロジェクト作成
	BOOL			B_UseJFlow;						// JFlowプロジェクト作成

	int			Mesh_Thresh;						// Display MeshLine Limit
	//--------------------------------------------- Data Combo
	int			DataNum,DDISP;					// データコンボの数、現在のインデックス
	int			Data_Order[FILE_IN_NUM];			//　データコンボの内容
	//--------------------------------------------- Observation Points
	int			OBmem,OBnum;						// 流量観測点
	LOCATE_INFO*	OBpos;
	//--------------------------------------------- Base Area
	int			Vnum,Hnum;						// 緯度数、経度数
	int			Tnum,Anum;						// 総メッシュ数、有効メッシュ数
	//
	int			MVnum, MHnum;						// 1410　メッシュ数
	int			PVnum, PHnum;						// 1410  メッシュ数＋１ ポイント数

	double		stLAT,stLNG;						// 緯度・経度であることに注意
	double		endLAT, endLNG;					// 1410 
	double		Size;
	//
	double		stUTM_X, stUTM_Y;
	double		endUTM_X, endUTM_Y;
	double		UTMsize;
	//
	int			Xmin, Xmax, Ymin, Ymax;			// 座標値（１）の範囲
	//
	int			SizeMother;
	//--------------------------------------------- Period
	double		TimeDiff;						// 時差
	CTime		StTime, EndTime;
	CTime		GMTime,LCTime;					// UTC,Local 現在時刻
	BOOL		B_CHECK_10MINS;					// 10mins 速報版 check
	//
	//--------------------------------------------- Display Back Image
	char		IM_Folder[256];
	double		Data_Alpha,Back_Alpha;				// Mesh & Back Image Transparency
	//
	double		Back_Offset;						// Back Ground Image offset +value
	int			Back_stLat, Back_endLat;
	int			Back_stLng, Back_endLng;
	//
	//--------------------------------------------- Color Definition
	COLORREF		Col_Mesh, Col_MeshR, Col_MeshB;
	COLORREF     COL_MESH[10];		// NEW 150118  ref ID_MESH_*
	//
	COLORREF		Col_Frame,Col_Observatory;
	COLORREF		Col_LegendChar,Col_WLframe;
	//
	// Data Color
	/* 201601 Cover(23) Soil(24)を加えた。201411 の追加分の処理が分からないのでとりあえず
	　　２３，２４を使用することとする。*/
	COLVAL_FIX	Dcol[28];						// 201411 追加21->28 Evp Drain を含む
	BOOL			B_Data_Mosaic;					// EDITOR のデータ操作用
	//
	//--------------------------------------------- Change Data
	//
	BOOL			Change_DCOL;						// ダイアログ全体での変更有り無し
	BOOL			Change_Display;
	BOOL			Change_Image;
	BOOL			Change_Mesh;
	BOOL			Change_Data;
	BOOL			Change_Time;
	BOOL			Change_Legend;

	//--------------------------------------------- 連絡用
	int			Cam_Dir;
	int			CX,CY;							// センターメッシュ
	int			SizeID;
	double**		Values;
	//
	XYCOORD		Band_Area[2];
	XYCOORD		Band_Center;
	//
	BOOL			Save_Proc;
	short		Edit_Result;
	int			Data_Change_Cnt,Move_Cnt;		// 編集全体の変更、矩形移動の変更
	//
	BOOL			Break_Proc;
	short		Break_Result;
	//
	int			TSDLG_minH,TSDLG_minV;
	//
	///--------------------------------------------- External Data
	double		Deg_Unit;		// 一度当たりの寸法,UTM の場合は寸法
	double		Coord_Unit;		// 20150313 追加 メッシュを作る際の、１メッシュ当たりの変換値
	double		Unit_Area;		// セル１つ当たりの面積　ｋｍ２　範囲が確定したときに計算
	//
	EX_DATA*		EXDATA;
	int			EXnum, EXmem;
	//
	int			BVnum, BHnum;
	int**		Back_TexNo;
	//--------------------------------------------- Legend
	int			Lw, Lh, Lfont, Lstyle,Lsize;	// フォント幅高さ フォント番号、スタイル 色枠サイズ
	XYCOORD		Pos_Legend;		// 枠の大きさ
	CRect		Area_Legend;		// スクリーンないの範囲
	//
	///--------------------------------------------- UNDO 用 記憶域
	int			UndoH, UndoV;
} PARAMS;
#endif
#ifndef		_MINFO
#define		_MINFO
typedef		struct _MINFO {
	short		flag;			// 有効・無効	 0:Invalid  1:Normal 2:RIver  3:Boundary
	int			H,V;				// メッシュ位置
	int			LinePno;
	int			PolyPno;			// ＷＬ ポリゴンNo
	double		Lat,Lng;			// 開始経緯度
	double		uv[2];			// UV 開始位置　左上
	char			name[SIZE_01K];	// 地点名
	//
	double		Acc;				// 上流面積
	double		Adem;			// 標高データ
	double		AtLng;			// Basin時の緯度 2019/04
	double		AtLat;			// Basin時の経度 2019/04
	short		Adir,Adir0;		// 落水線方向 Adir0 DIR 編集機能のため 2016/2
	short		Sed;			// 粒度  2021/09

	int			Bno,In;				// Add  2016/2

	// 土地被覆・土壌データ
	short		Lu;				// 土地利用区分		<- FAO CODE
	BYTE			LUCNT[21];		// FAO 土地利用
	short		Cover, Soil;
	BYTE			Dcnt, Gcnt, Wcnt; // Dcnt 1-7 , Gcnt 8-20 exp 18, Wcnt 18
	///

	double		Rwidth;			// 河道幅
	double		Rdepth;			// 河道深さ
	double		Bheight;			// 堤防高さ

	double		HSinit;			// 流域水位の初期状態量
	double		HRinit;			// 河道水位の初期状態量
	double		HGinit;			// 地下水位の初期状態量
	double		Gampt;			// グリーンアンプトの初期状態量
	//
	double		Dam_Volume;		// NEED ? ダムカウントファイル Damcnt.txt
	double		Dam_Start_Q;		// NEED ?
	//
	double		length;			//
	int			sec_ID;			// 河道断面ID,0 以外であれば以下の河道データが有効
	//
	int			Snum;			// 断面横断要素数　
	double		Sdepth, Sheight;
	///
	// 境界条件
	int			ID_SWL, ID_RWL, ID_SQ, ID_RQ, ID_DIV;
	//
} MINFO;
#endif

///////////////////////////////////////////////////////////////////////////////////
// RRI 共通 関数
//
//
///////////////////////////////////////////////////////////////////////////////////
BOOL		Alloc_TIMESET(TIMESET*	TS );
BOOL		Realloc_TIMESET(int oldmem, int oldstep, TIMESET* TS);
void		Free_TIMESET(TIMESET*	TS );
void		Copy_TIMESET( TIMESET* TS, TIMESET* TT );

void		Copy_DAMCNT( DAMCNT* tar,DAMCNT org);

void		Get_Relative_Path(char* Fname,char* Dir,char* Rname);
void		Get_Relative_Path(CString Fname,char* Dir, char* Rname);
void		Get_Relative_Path(CString Fname, char* Dir, CString Rname);

void		Get_SuitScale(int scaleid,int num,double* x,double* vmin,double* vmax,int* rips,double* unit,int* fm);

void		Get_Wnd_Value(int No );

void		Get_Scale_Axis(double* Hmin,double*  Hmax,int* rips,double* unit,int* fm);

void		Get_GoodScale(int Num,double* val,double* Vmin,double* Vmax,
							int* Rip,double* Unit,int* Fm);

BOOL		Save_Color_Data( CString Boot,PARAMS* PM );	

CTime	StrDate_Time( char*  buf );

void		Make_String(double val, CString* str, int limit);


void		Copy_DSET(DATASET* DT, DATASET DD);
void		Delete_DSET(DATASET* DS);

int		Read_RRI_INPUT(DATASET* DS, FILE*  fp);

int		Write_RRI_INPUT(DATASET DS);

int		Write_All_Files(int* Fform, int* Forder,DATASET DS, MINFO**	MESH, PARAMS PM );

int		Write_Data_File(int Did, int Fform, int Forder, DATASET DS, PARAMS PM, MINFO** MESH);
int		WriteAs_Data_File(int Did, int Fform, int Forder, DATASET& DS, PARAMS& PM, MINFO** MESH);

int		Get_ArcGIS_Info(const char* fname, int* Hnum, int* Vnum, double* stLAT, double* stLNG, double* Size);

int		Set_File_FullName(DATASET* DS);
int		Set_Relative_Name(DATASET* DS);

int		Read_Data_File(int f, CString fname, DATASET* DS, MINFO** MESH);

BOOL		Search_LU_Label_Order(MINFO** MESH);

void		Set_CWnd_Exponent(CWnd* cw, double val, int rank);

void		Get_Val_Exponent(double val, int rank,char* Str);

void		Copy_Luinfo(LUINFO* tar, LUINFO org);

BOOL		IsSame_Luinfo(LUINFO tar, LUINFO org);

CString	Param_get(CString fname, CString Key, CString Def);				// 20190201
void	GetMeshTable(CString fname, std::map<CString, CString> &dic_Area_Directory, std::map<CString, CString> &dic_Area_MeshTable1);	// 20190201
char	*SanitizeSRS(const char *pszUserInput);		// 20190201
double Get_DecodedVal_Exponent(CString Str);

bool CopyDataFromMesh(int Did, double** data, MINFO** MESH, const PARAMS& PM, const std::vector<int>& vExcludeIds);
bool CopyDataFromMesh(int Did, int v, int h, double& value, MINFO** MESH, const PARAMS& PM, double defaultVal = static_cast<double>(NODATA));
bool CopyDataToMesh(int Did, double** data, MINFO** MESH, const PARAMS& PM);


#define SIMP_VER	0		//簡易版（SED機能なし、...）
#define MID_VER		1		//中間版（SED機能なし）
#define FULL_VER	2		//完全版
#define APP_VERSION	SIMP_VER


#define RRI_DIR_NAME "SIMU/old_rri/"
