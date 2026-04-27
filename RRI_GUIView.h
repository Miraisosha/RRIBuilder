
#pragma once
#include		"stdafx.h"
#include		<string>
#include		<vector>

#include		"resource.h"
#include		"RRI_GUIDoc.h"
#include		"afxwin.h"
#include		"RRI_Common.h"
//
#include		"EDITDLG.h"

//----------------------------------------------------------------------------　TAB
#include		"afxcmn.h"
#include        <CommFuncs.h>
//----------------------------------------------------------------------------　TAB
#define		TAB_1				0
#define		TAB_2				1
#define		TAB_3				2

#define		GUIDE_TEXTURE			100
#define		GUIDE_NUM			10

#define		ONE_DEGREE_DISTANCE	1.
#define		ACC_LIMIT			20
#define		EL_LIMIT				-10.

#define		MESH_MARGIN			5

#define		MAX_RIVER_NUM			20

#define		ARROW_LIMIT			120		// 横の表示メッシュの数、小さければ矢印の表示

#define		DIR_E			1
#define		DIR_SE			2
#define		DIR_S			4
#define		DIR_SW			8
#define		DIR_W			16
#define		DIR_NW			32
#define		DIR_N			64
#define		DIR_NE			128

#define		ARROW_COLOR		RGB(80,150,210)

//----------------------------------------------------------------------------
#define		RRI_TEMPLATE_FILE		"./RRI_CONTENTS/RRI_Input_Template.txt"
#define		RRI_SCREEN_TOOL_IMAGE   "./RRI_CONTENTS/COMMON/TOOL.bmp"

#define		RRI_PROGRAM   "0_rri_1_4_2.exe"


//----------------------------------------------------------------- 3B42RT
#define		RT3B_ST_LNG	0.125
#define		RT3B_ST_LAT	60.
#define		RT3B_HNUM	1440
#define		RT3B_VNUM	480
#define		RT3B_SIZE	0.25
#define		RT3B_HEAD	2880
#define		I2MISSING	-31999
#define		SCALE		100

#define		GSMAP_ST_LAT	60.
#define		GSMAP_HNUM	3600
#define		GSMAP_VNUM	1200
#define		GSMAP_SIZE	0.1

#define		TOOL_DEFAULT_X	50.
#define		TOOL_DEFAULT_Y	100.

class CRRI_GUIView : public CFormView
{
protected: // シリアル化からのみ作成します。
	CRRI_GUIView();
	DECLARE_DYNCREATE(CRRI_GUIView)

public:
	enum{ IDD = IDD_RRI_GUI_FORM };

// 属性
public:
	CRRI_GUIDoc* GetDocument() const;
///-----------------------------------------------------------------------------------------------------------
// Class  Members  表示 Common
///----------------------------------------------------------------------------------------------------------  
	CString			m_InFileName,m_OutFileName,m_InDirName;
	CString			m_ProjName;
	CString			Bin_Folder,Bin_File;

	BOOL				B_FirstStep;
	int				Cnt_CArea;
	//
	BOOL				B_UndoFirstSave;
	CString			Undo_Temp_Name[3];  // Adem, Acc, Adir
	CString			Undo_Org_Name[3];  // Adem, Acc, Adir
	double			Undo_Org_Deg_Unit;
// ---------------------------------------------------------------------------------------------------------- -
// Class  Members   COMMON
//-----------------------------------------------------------------------------------------------------------  
	CToolTipCtrl		m_ToolTip;
	//
	TC_ITEM			tc_TAB[5];		// タブ情報
	int				MENU_WIDTH;		// メニュー幅
//-----------------------------------------------------------------------------------------------------------
	int				fdir,MeshCnt;
	int				AreaYmin, AreaYmax, AreaXmin, AreaXmax;
	int				BXmin, BXmax, BYmin, BYmax;	// 古い領域 Area**のコピー
//-----------------------------------------------------------------------------------------------------------
// Class  Members  
//-----------------------------------------------------------------------------------------------------------  
	int				Menu_Margin,TAB_Offset;
	//
	int				RIVnum;
	RIV_INFO			RIVinfo[MAX_RIVER_NUM];	// X,Y 緯度経度、Ｚ ACC
	BOOL				RivEX;					// 河川除外領域があるかどうか
	RIV_INFO			RivEXpos;
	//
	int				Xnum;

	/// Arrow
	CEDITDLG*		EDDlg;
	double			Arrow_Ang;
	double			Arrow_Head;
	FCOLOR			Col_Arrow;

	/// UNDO
	int				UHmem, UHnum,UHnum0;
	UndoHist*		UH;
	int				NoexitMem,NoexitNum;
	CPoint*			NoexitPos;
//-----------------------------------------------------------------------------------------------------------
// Class  Functions    初期化・共通
//-----------------------------------------------------------------------------------------------------------  
// for CALLBACK
	static int AFXAPI BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	BOOL			Button_Dir(CString* m_DirName, char* m_RecentPath, CString ttl, BOOL New);
	BOOL			Button_Dir(char* m_DirName, char* m_RecentPath);
	void			Render_Scene();
	void			Draw_Band_Area(double cx, double cy);
// 初期化-------------------------------------------------------------
	void			Init_Params();
	void			Init_Controls();
	int			Read_RRI_Template();		// 正式な　Read Write RRI_Input は RRi_Common
	void			Clear_Select();
	void			Clear_Mode();

	BOOL			Set_LU_CodeTable();		// Code_Table の作成

// メニューコントロール　ツール機能-----------------------------------------
	void			Change_Tab();
	void			Disp_Controls();
	void			Show_Command(int level, CString str);

	void			Make_Screen_Tool(BOOL  Tex);
	int			Decide_Tool(CPoint cp);
	void			EX_Tool(int id);
	void			Tool_Scale(BOOL inc);
	void			Tool_Move(int dir);

	void			Disp_Select_RivMesh();
	BOOL			Search_River_Path();
	// 既存プロジェクトの読み込み------------------------------------------
	int			Reload_Project();
//	int			Read_Data_File(int f, CString fname, MINFO** Data);

// すべてのファイルの書き出し　------------------------------------------
	int			Save_All_Files();

// エディタのセットと読み込み　----------------------------------------------
	int			Get_RectArea();
	int			Set_RectArea();
	void			Clear_RectArea();
	//
	void			Set_UTMArea();
	//
	int			Change_Area();

// 雨データ・ＥＶＰデータの読み込み　----------------------------------------------
	void			Set_Period();
	void			Get_Period();

	void			Get_Checks();
	int			Read_3B42RT(CString fname, CRect Area, double** val);
	int			Read_GSMap(CString fname, CRect Area, float** rain);
	int			Culc_Out_Hour(int Hours);
// プロセスコントロール　-----------------------------------------------
// セッション初期化
	HRESULT		Show_Init_Guide();
	HRESULT		Define_Folder();
	HRESULT		Set_Guide_TEX();
	HRESULT		Set_Guide_TEX_JFLOW(EX_FILE upgInfo);
	//
	//
// 流下方向　編集 コントロール　-----------------------------------------------
	void			Disp_Direction_Radio(int xid,int yid);
	void			Disp_Edit_Arrow();
	void			Disp_Arrow();
	BOOL			Resist_Dir(int Dir);
	void			Show_Mesh_Info(int x, int y);

	void			Reset_Flow_Direction();
	void			Get_Basin_Acc();
	int			Find_Mesh(int Bno, int h, int v);

// 外部データの読み込み------------------------------------------
	int 			Get_HYDROSHEDS_Value(double lng, double  lat, int kind);
	int 			Get_JFlwMesh_Value(double lng, double  lat, int kind);

	struct JFlowCache
	{
		double adfGeoTransform[6];
		double adfInvGeoTransform[6];
		int xsize;
		int ysize;
		double* datas;
	};
	struct JFlowTifCache
	{
		CString filepath;
		double adfGeoTransform[6];
		double adfInvGeoTransform[6];
		int xsize;
		int ysize;
		COLORREF* datas;
	};
	bool            Create_J_Flw_Cache(CString fname, JFlowCache* areaCache);
	bool            Get_GeoTiff_Bytes(CString fname, JFlowTifCache* tifCache, Color_Val* Ctable);
	double          Get_J_Flw_Value_From_Cache(double lng, double lat, JFlowCache* areaCache);
	double 			Get_J_Flw_Value(CString fname, double lng, double  lat);	// 20190201 Add
	int 			Read_HYDROSHEDS();
	int 			Read_J_Flw();	// 20190201 Add
	void			Trans_COORD_LATLNG(int kind, double x, double y, double* lng, double* lat);
	void 		Trans_LATLNG_COORD(int kind, double x, double y, double* lng, double* lat);
//
// 外部データの読み込み------------------------------------------
	HRESULT		Read_3_Files(BOOL RELEASE);
	int			Read_Dem();
// モデルの作成　-----------------------------------------------
	void			Display_Basin();
	void			Exclude_Basin();
	int 			Make_Mesh_Area();
	int			Make_Mesh_Model_Init(FCOLOR  DefaultCol, double Alpha);
	int			Make_Mesh_Model();
	int 			Make_Mesh_Line();
	int			Make_Back_Image();
	int			Make_TS_Model();
	int			Make_GROUND_OBS();
	int			Make_LEGEND();
	int			Edit_Mesh_Model();
	int			Make_Select_Pos();
	int			Make_Edit_Riv();
	//
	int			Make_Decimal_Legend();
	//
	// 河川最下流端の指定表示
	HRESULT		Disp_River_Pos(BOOL  Add);  // 河川データの追加か、除外か？
	HRESULT		Del_River_Pos(BOOL  Add);
	//
	void			Draw_Free_Area(BOOL Circle);
	void			Add_Mesh();
	void			Del_Mesh();
	//
	BOOL			Get_Data_Color(BOOL Dsel, int v, int h, double val, FCOLOR* Fcol, int dataType = -1);
	BOOL			RRI_Color_Picker(double value, BOOL Mosaic, BOOL Equal, int num, double* vm, COLORREF* col, FCOLOR* Fcol);

	void 		Get_Recursive_Area(int px, int py, BYTE** mark);
	void        Get_J_Flw_Area_Hight_Perf(double lng, double lat, int px, int py, BYTE** mark);
	void 		Get_Recursive_Area_J_Flw(double lng, double lat, int px, int py, BYTE** mark);
	void			Read_AllDir();
	// メッシュ範囲が決定してからＭＥＳＨをＡＬＬＯＣする。
	int			Set_MESH_MODEL();

	void			Get_MESH_COLOR(int id);
	int 			Get_Recursive_Basin(int px, int py, BYTE** mark); // Dem data のみの場合の流域探し
///
// 編集　-----------------------------------------------
	void			Display_EditWindow(int xid, int yid);
	void			Save_Manager();
	void			Term_Manager();
///
// ETC　-----------------------------------------------
	void			Save_Undo_File();
	void			Calc_Unit_Area();		// 追加機能 セルの面積計算
///
// Sed -----------------------------------------------
private:
	struct MeshDataHeader {
		int ncols;
		int nrows;
		double xllcorner;
		double yllcorner;
		double cellsize;
	};

	struct DrawPolyInfo {
		DrawPolyInfo(CPoint _p, FCOLOR _c) { point = _p; col = _c; }
		CPoint	point;
		FCOLOR	col;
	};

	static			int ms_SubBasinDataVal;

	std::string					fSedInputPath;
	std::vector<std::string>	fSedInputLines;

private:
	bool			IsSedEnabled();
	bool			LoadSedInputFile();
	bool			InitSedFile();
	bool			ExtractSubBasin(std::string& fPath, UINT32 idX, UINT32 idY);
	bool			ExtractSubBasin(UINT32 idX, UINT32 idY);
	bool			LoadSubBasinHeader(const std::string& fPath, MeshDataHeader* headerInfo, CPoint* offsetSet);
	bool			LoadSubBasinData(const std::string& fPath, const MeshDataHeader& headerInfo, int** data);
	bool			DrawTempSubBasinData(const CPoint& offsetSet, const MeshDataHeader& headerInfo, int** data);
	bool			DrawSubBasinRect();
	bool			UpdateSedFile();
	void			RefreshSedRectLine();
public:
	void			PopupMessage(std::vector<std::string> msgItems, std::string title = "Error Msg", bool isError = true);
	std::string&	RightTrim(std::string& str, std::string& chars);
	bool			DeleteFileWithPath(LPCSTR fPath);
	bool			UpdateDsWithFFullPath(const char* csfPath, const size_t id);
	bool			SaveSedInputFile();
// END　-----------------------------------------------

public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CRRI_GUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CButton		m_cButton_Pdir;
	//
	CString		s_ProjName;
	afx_msg void OnEnChangeEdit105();
	afx_msg void OnEnChangeEdit106();
	afx_msg void OnEnChangeEdit107();
	afx_msg void OnEnChangeEdit108();
	afx_msg void OnEnChangeEdit109();
	afx_msg void OnEnChangeEdit110();
	afx_msg void OnEnChangeEdit111();
	afx_msg void OnEnChangeEdit112();
	afx_msg void OnEnChangeEdit113();
	afx_msg void OnEnChangeEdit114();
	afx_msg void OnEnChangeEdit115();
	afx_msg void OnEnChangeEdit116();
	afx_msg void OnBnClickedButton103();		// Confirm
	afx_msg void OnBnClickedButton111();		// Del Basin
	//	
	// Standard Response
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//
	// Member
	CButton		m_cConfirm;
	CButton		B_cDelete;
	CString		s_MeshSubdev;
	CString		s_stLNG_deg;
	CString		s_stLNG_min;
	CString		s_stLNG_sec;
	CString		s_endLNG_deg;
	CString		s_endLNG_min;
	CString		s_endLNG_sec;
	CString		s_stLAT_deg;
	CString		s_stLAT_min;
	CString		s_stLAT_sec;
	CString		s_endLAT_deg;
	CString		s_endLAT_min;
	CString		s_endLAT_sec;
	CString		s_MeshH;
	CString		s_MeshV;
	CComboBox	c_ComboData;
	CTabCtrl		c_TabMain;
//	CButton		c_DataInvalid;
	CSliderCtrl	c_SliderBackT;
	CSliderCtrl	c_SliderDataT;
	CButton c_Badd;
	CButton c_Bdel;
	CButton c_BoundList;
	CButton c_Bcolor;
	CButton c_Racc;
	CString s_Select;
	CButton c_Undo;
	CButton b_Breset;
//	CButton c_BFlow;
	CString s_OutLocation;

	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboData();
	afx_msg void OnBnClickedButton401();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton201();
	afx_msg void OnStnDblclickMeshcolor1();
	afx_msg void OnStnDblclickMeshcolor2();
	afx_msg void OnStnDblclickMeshcolor3();
	afx_msg void OnNMCustomdrawSliderTrans2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckOp3();
	afx_msg void OnBnClickedCheckOp2();
	afx_msg void OnNMCustomdrawSliderTrans(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckOp1();
	afx_msg void OnBnClickedButton104();
	afx_msg void OnBnClickedButton206();
	afx_msg void OnEnChangeEdit201();
	afx_msg void OnEnChangeEdit202();
	afx_msg void OnEnChangeEdit203();
	afx_msg void OnEnChangeEdit204();
	afx_msg void OnEnChangeEdit206();
	afx_msg void OnEnChangeEdit207();
	afx_msg void OnEnChangeEdit208();
	afx_msg void OnEnChangeEdit209();
	afx_msg void OnEnChangeEdit212();
	afx_msg void OnBnClickedButton208();
	afx_msg void OnBnClickedButton207();
	afx_msg void OnBnClickedButton112();
	afx_msg void OnBnClickedButton113();
	afx_msg void OnBnClickedCheckOp4();
	afx_msg void OnNMCustomdrawSliderTool(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton404();
	afx_msg void OnStnDblclickMeshcolor4();
	afx_msg void OnBnClickedCheckOp6();
	afx_msg void OnBnClickedCheckOp5();
	afx_msg void OnBnClickedCheckOp7();
	afx_msg void OnStnDblclickMeshcolor5();
	afx_msg void OnBnClickedButton220();
	afx_msg void OnStnDblclickMeshcolor6();
	afx_msg void OnStnDblclickMeshcolor7();
	afx_msg void OnStnDblclickMeshcolor8();
	afx_msg void OnStnDblclickMeshcolor9();
	afx_msg void OnStnDblclickMeshcolor10();
	afx_msg void OnStnDblclickMeshcolor11();
	afx_msg void OnIdsChangeBackcolor();
	afx_msg void OnIdsSetRivParameter();
	afx_msg void OnIdsBoundaryPos();
	afx_msg void OnIdsExtractSed();
	afx_msg void OnIdsBoundaryDam();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnIdsBoundaryDiv();
	afx_msg void OnIdsBoundaryHs();
	afx_msg void OnIdsBoundaryHr();
	afx_msg void OnIdsBoundaryQs();
	afx_msg void OnIdsBoundaryQr();
	afx_msg void OnBnClickedButtonB201();
	afx_msg void OnBnClickedButtonB202();
	afx_msg void OnBnClickedButtonB203();
	afx_msg void OnBnClickedButtonB204();
	afx_msg void OnBnClickedButtonB205();
	afx_msg void OnBnClickedButtonB206();
	afx_msg void OnBnClickedButtonB207();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButton105();
	afx_msg void OnBnClickedButton106();	// 20190201
	afx_msg void OnBnClickedButton114();
	afx_msg void OnBnClickedButton210();
	CButton c_BEacc;
	afx_msg void OnBnClickedButtonEacc();
	afx_msg void OnBnClickedButton214();	// 20190201
	afx_msg void OnBnClickedButton215();	// 20190201
	afx_msg void OnBnClickedButtonRri();
	afx_msg void OnBnClickedButton212();
	afx_msg void OnIdsDeleteRiv();
	afx_msg void OnIdsSetRiv();
//	afx_msg void OnIdsExecFlow();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedButtonLuparam();
	CButton c_LandCoverSoil;
	CButton c_LandCoverSoilJp;
	CButton c_LandCoverSoilJp2;
	CString s_Location;
	CString s_H;
	CString s_CurrentD;
	CString s_Kind;
	CString s_Acc;
	afx_msg void OnBnClickedRadioNw();
	afx_msg void OnBnClickedRadioN();
	afx_msg void OnBnClickedRadioE();
	afx_msg void OnBnClickedRadioSe();
	afx_msg void OnBnClickedRadioS();
	afx_msg void OnBnClickedRadioSw();
	afx_msg void OnBnClickedRadioW();
	afx_msg void OnBnClickedRadioNe();
	afx_msg void OnBnClickedRadioTerm();
	CButton c_Reset;
	CButton c_DirUndo;
	CButton c_Cancel;
	CButton c_DispArrow;
	afx_msg void OnBnClickedCheckDisparrow();
	CString s_ArrowInfo;
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonDirUndo();
	afx_msg void OnBnClickedButtonLanduseJp();
	afx_msg void OnBnClickedButtonLanduseJp2();
	afx_msg void OnStnClickedStatic214();
	afx_msg void OnBnClickedBtnSetsedim();
};

#ifndef _DEBUG  // RRI_GUIView.cpp のデバッグ バージョン
inline CRRI_GUIDoc* CRRI_GUIView::GetDocument() const
   { return reinterpret_cast<CRRI_GUIDoc*>(m_pDocument); }
#endif

