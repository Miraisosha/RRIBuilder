// Tab_Param.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Tab_Param.h"
#include "RRI_Common.h"

#include "afxdialogex.h"
#include "BUSY.h"

extern		PARAMS			PM;							// 基本情報
extern		DATASET			DS;
extern		int				CLAND;
extern		MINFO**			MESH;
extern		char				m_RecentPath[];
extern		char				m_BootPath[];
extern		char				Cover_Name[20][48];
extern		char				Soil_Name[13][48];

extern		LUINFO			CODE_TABLE[13][20];		// マニング係数別
// TAB PARAM
int				BP_EDIT_NUM = 37;
int				BP_EDIT_ID[] = { IDC_PARAM_EDIT_0, IDC_PARAM_EDIT_1, IDC_PARAM_EDIT_2, IDC_PARAM_EDIT_3, IDC_PARAM_EDIT_4,
								IDC_PARAM_EDIT_5, IDC_PARAM_EDIT_6, IDC_PARAM_EDIT_7, IDC_PARAM_EDIT_8, IDC_PARAM_EDIT_9,
								IDC_PARAM_EDIT_10, IDC_PARAM_EDIT_11, IDC_PARAM_EDIT_12, IDC_PARAM_EDIT_13, IDC_PARAM_EDIT_14,
								IDC_PARAM_EDIT_15, IDC_PARAM_EDIT_16, IDC_PARAM_EDIT_17, IDC_PARAM_EDIT_18, IDC_PARAM_EDIT_19,
								IDC_PARAM_EDIT_20, IDC_PARAM_EDIT_21, IDC_PARAM_EDIT_22, IDC_PARAM_EDIT_23, IDC_PARAM_EDIT_24,
								IDC_PARAM_EDIT_25, IDC_PARAM_EDIT_26, IDC_PARAM_EDIT_27, IDC_PARAM_EDIT_28, IDC_PARAM_EDIT_29,
								IDC_PARAM_EDIT_30, IDC_PARAM_EDIT_31, IDC_PARAM_EDIT_32, IDC_PARAM_EDIT_34, IDC_PARAM_EDIT_38,
								IDC_PARAM_EDIT_39,IDC_PARAM_EDIT_40 };

int				PARAM_FORM[] = {	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,1,1,  1 };


// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
// CRRI_GUIView コンストラクション/デストラクション
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNAMIC(CTab_Param, CDialogEx)

CTab_Param::CTab_Param(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab_Param::IDD, pParent)
	, s_NameRRI(_T(""))
	, s_MeshNum(_T(""))
{

}

CTab_Param::~CTab_Param()
{
}

void CTab_Param::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo_LU);
	DDX_Text(pDX, IDC_PLABEL_RRI, s_NameRRI);
	DDX_Text(pDX, IDC_PLABEL_MESHNUM, s_MeshNum);
	DDX_Control(pDX, IDC_BUTTON_FAO, c_BFAO);
}


BEGIN_MESSAGE_MAP(CTab_Param, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTab_Param::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_FAO, &CTab_Param::OnBnClickedButtonFao)
END_MESSAGE_MAP()

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  タブの初期化・変更
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL	CTab_Param::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init_Tab();
	Disp_Data();

	Change_Nums = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
}
void	CTab_Param::Init_Tab()
{
	CWnd*	cw;
	//
	CString	str;
	for (int i = 0; i < DS.LUnum; i++){
		str.Format("%d", i + 1);
		m_Combo_LU.AddString(str);
	}
	//
	cw = GetDlgItem(IDC_PLABEL_13);	// 総数　LUnum
	str.Format(" / %d", DS.LUnum);
	cw->SetWindowTextA(str);
	//
	/// add 2015 12  LUの適用メッシュ数の表示
	int	cnt = 0;
	for (int i = 0; i < DS.LUnum; i++) DS.LUdata[i].appmesh = 0;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;
			if (MESH[v][h].Lu > 0 ) DS.LUdata[MESH[v][h].Lu - 1].appmesh++;
			cnt++;
		}
	}
	s_MeshNum.Format("[ %d ]", DS.LUdata[CLAND].appmesh);

	//
	UDF;
}
void	CTab_Param::Disp_Data()
{
	CWnd*	cw;
	double	val;
	CString	str;
	//
	s_MeshNum.Format("[ %d ]", DS.LUdata[CLAND].appmesh);
	//
	cw = GetDlgItem(IDC_PLABEL_13);	// 総数　LUnum
	str.Format(" / %d", DS.LUnum);
	cw->SetWindowTextA(str);
	//
	for (int i = 0; i < BP_EDIT_NUM; i++) {
		if (DS.LUnum == 0 && (i >= 10 && i <= 20)) continue;
		cw = GetDlgItem(BP_EDIT_ID[i]);
		switch (i) {
		case 0: Set_CWnd_Text(cw, DS.SW_LatLong); break;
		case 1: Set_CWnd_Text(cw, DS.SW_Dir); break;
		case 2: Set_CWnd_Text(cw, DS.Hours, FALSE); break;
		case 3: Set_CWnd_Text(cw, DS.DT, FALSE); break;
		case 4: Set_CWnd_Text(cw, DS.DT_Riv, FALSE); break;
		case 5: Set_CWnd_Text(cw, DS.Out_Num, FALSE); break;
		case 6: Set_CWnd_Text(cw, DS.Rain_Lng, 1, FALSE); break;
		case 7: Set_CWnd_Text(cw, DS.Rain_Lat, 1, FALSE); break;
		case 8: if (DS.Rain_dx != 0.) {
					val = 1. / DS.Rain_dx; Set_CWnd_Text(cw, val, 0, FALSE);
		}
				break;
		case 9: if (DS.Rain_dy != 0.) {
					val = 1. / DS.Rain_dy; Set_CWnd_Text(cw, val, 0, FALSE);
		}
				break;
				// 
				//  land usage elements
		case 10:Set_CWnd_Text(cw, DS.LUdata[CLAND].SW_kinema); break;
		case 11:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].ns_slope, 3); break;
		case 12:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].soildepth, 3); break;
		case 13:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].gammaa, 3); break;
		case 14:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].ksv, 3); break;
		case 15:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].faif, 3); break;
		case 16:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].ka, 3); break;
		case 17:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].gammam, 3); break;
		case 18:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].beta, 3); break;
		case 19:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].kgv, 3); break;
		case 20:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].gammag, 3); break;
		case 34:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].tg, 3); break;
		case 35:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].fpg, 3); break;
		case 36:Set_CWnd_Exponent(cw, DS.LUdata[CLAND].init_cond_gw, 3); break;
			// 
			//  river ns
		case 21:Set_CWnd_Exponent(cw, DS.Ns_River, 3); break;
			// 
			//  river thresh
		case 22:Set_CWnd_Text(cw, DS.Riv_Thresh, 1, TRUE); break;
		case 23:Set_CWnd_Exponent(cw, DS.Cof_WC, 2); break;
		case 24:Set_CWnd_Exponent(cw, DS.Cof_WS, 2); break;
		case 25:Set_CWnd_Exponent(cw, DS.Cof_DC, 2); break;
		case 26:Set_CWnd_Exponent(cw, DS.Cof_DS, 2); break;
		case 27:Set_CWnd_Exponent(cw, DS.Cof_H, 2); break;
		case 28:Set_CWnd_Text(cw, DS.Cof_Hlim, 1, TRUE); break;
			// 
			//  evaporation
		case 29:Set_CWnd_Text(cw, DS.Evp_Lng, 1, TRUE); break;
		case 30:Set_CWnd_Text(cw, DS.Evp_Lat, 1, TRUE); break;
		case 31: if (DS.Evp_DX != 0.) {
					 val = 1. / DS.Evp_DX; Set_CWnd_Text(cw, val, 0, FALSE);
				}
				 break;
		case 32: if (DS.Evp_DY != 0.) {
					 val = 1. / DS.Evp_DY; Set_CWnd_Text(cw, val, 0, FALSE);
				}
				 break;
		case 33:cw->SetWindowTextA(DS.Proj_Title); break;
		}
	}
	//
	if (DS.b_CSexist){
		if (DS.b_CSrenumber) c_BFAO.EnableWindow(FALSE);
		else               c_BFAO.EnableWindow(TRUE);
	}
	else             c_BFAO.EnableWindow(FALSE);

	//2019 set parameter disable

	//
	if (PM.B_UseJFlow) {
		 c_BFAO.EnableWindow(FALSE);
			}

	s_NameRRI = DS.InputFile;
	m_Combo_LU.SetCurSel(CLAND);
	//
	UDF;
	//
	return;
}

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  ＳＡＶＥ
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void	CTab_Param::Get_Data()
{
	CWnd*		cw;
	CEdit*		ce;
	double		val;
	CString		str;
	//
	for (int i = 0; i < BP_EDIT_NUM; i++) {
		if (DS.LUnum == 0 && ((i >= 10 && i <= 20) || (i >= 38 && i <= 40))) continue;
		cw = GetDlgItem(BP_EDIT_ID[i]);
		ce = (CEdit*)cw;
		if (ce->GetModify()) Change_Nums++;
		cw->GetWindowTextA(str);
		switch (i) {
		case 0: DS.SW_LatLong = (BYTE)atoi(str); break;
		case 1: DS.SW_Dir = (BYTE)atoi(str);  break;
		case 2: DS.Hours = atoi(str);  break;
		case 3: DS.DT = atoi(str);  break;
		case 4: DS.DT_Riv = atoi(str);  break;
		case 5: DS.Out_Num = atoi(str);  break;
		case 6: DS.Rain_Lng = atof(str);  break;
		case 7: DS.Rain_Lat = atof(str);  break;
		case 8: if (str.GetLength() != 0.) {val = atof(str); DS.Rain_dx = 1. / val;}
				else                       { DS.Rain_dx = 0.; }
				break;
		case 9: if (str.GetLength() != 0.) { val = atof(str); DS.Rain_dy = 1. / val; }
				else                       { DS.Rain_dy = 0.; }
				break;
				// 
				//  land usage elements
		case 10:DS.LUdata[CLAND].SW_kinema = atoi(str);  break;
		case 11:DS.LUdata[CLAND].ns_slope = Get_DecodedVal_Exponent(str);  break;
		case 12:DS.LUdata[CLAND].soildepth = Get_DecodedVal_Exponent(str);  break;
		case 13:DS.LUdata[CLAND].gammaa = Get_DecodedVal_Exponent(str);  break;
		case 14:DS.LUdata[CLAND].ksv = Get_DecodedVal_Exponent(str);  break;
		case 15:DS.LUdata[CLAND].faif = Get_DecodedVal_Exponent(str);  break;
		case 16:DS.LUdata[CLAND].ka = Get_DecodedVal_Exponent(str);  break;
		case 17:DS.LUdata[CLAND].gammam = Get_DecodedVal_Exponent(str);  break;
		case 18:DS.LUdata[CLAND].beta = Get_DecodedVal_Exponent(str);  break;
		case 19:DS.LUdata[CLAND].kgv = Get_DecodedVal_Exponent(str);  break;
		case 20:DS.LUdata[CLAND].gammag = Get_DecodedVal_Exponent(str);  break;
		case 34:DS.LUdata[CLAND].tg = Get_DecodedVal_Exponent(str);  break;
		case 35:DS.LUdata[CLAND].fpg = Get_DecodedVal_Exponent(str);  break;
		case 36:DS.LUdata[CLAND].init_cond_gw = Get_DecodedVal_Exponent(str);  break;
			// 
			//  river ns
		case 21:DS.Ns_River = Get_DecodedVal_Exponent(str);  break;
			// 
			//  river thresh
		case 22:DS.Riv_Thresh = atof(str);  break;
		case 23:DS.Cof_WC = Get_DecodedVal_Exponent(str);  break;
		case 24:DS.Cof_WS = Get_DecodedVal_Exponent(str);  break;
		case 25:DS.Cof_DC = Get_DecodedVal_Exponent(str);  break;
		case 26:DS.Cof_DS = Get_DecodedVal_Exponent(str);  break;
		case 27:DS.Cof_H = Get_DecodedVal_Exponent(str);  break;
		case 28:DS.Cof_Hlim = atof(str);  break;
			// 
			//  evaporation
		case 29:DS.Evp_Lng = atof(str);  break;
		case 30:DS.Evp_Lat = atof(str);  break;
		case 31: if (str.GetLength() != 0.) {val = atof(str); DS.Evp_DX = 1. / val;}
				 else                  DS.Evp_DX = 0.;
				 break;
		case 32: if (str.GetLength() != 0.) { val = atof(str); DS.Evp_DY = 1. / val; }
				 else                  DS.Evp_DY = 0.;
				 break;
				//  comment
		case 33:strcpy(DS.Proj_Title,str);  break;
		}
	}
	return;
}
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  Contorol
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_Param::OnCbnSelchangeCombo1()
{
	Get_Data();
	CLAND = m_Combo_LU.GetCurSel();
	Disp_Data();
}


BOOL CTab_Param::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN) { Get_Data(); return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  FAO Data Setting
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_Param::OnBnClickedButtonFao()
{
	//--------------------------------------------------
	/* 　確認　*/
	//--------------------------------------------------
	CString		str;
	str.Format("Are you sure to apply new parameter set and save it in the following file? \n[ %s ]", DS.File_names[LU_FILE]);
	if (MessageBox(str, "Confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		CString	fname;
		if (!Button_File(FALSE, &fname, m_RecentPath, "Land use file", "txt")) return;
		strcpy(DS.File_names[LU_FILE], fname);
	}
	///--------------------------------------------------
	/*
	参照するCODE_TABLEの数をカウント　ref_Count
	*/
	///--------------------------------------------------
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;
			if (MESH[v][h].Cover <= 0 || MESH[v][h].Soil <= 0) {
				if (MESH[v][h].Cover <= 0) str = "** Error ** \nCover data include the value that is smaller than 0.\n Cannot continue.";
				else    str = "** Error ** \nSoil data include the value that is smaller than 0.\n Cannot continue.";
				MessageBox(str, "Stop", MB_OK | MB_ICONHAND);
				return;
			}
			//
			CODE_TABLE[MESH[v][h].Soil - 1][MESH[v][h].Cover - 1].refcnt++;
		}
	}
	///--------------------------------------------------
	/*
		使っているパラメータセット[13][20]の同一性を調査し　DATASET ＝DSのLUDATAに整理する。
	*/
	///--------------------------------------------------
	SAFE_FREE(DS.LUdata);
	DS.LUnum = 0;
	DS.LUmem = 10;
	if ((DS.LUdata = (LUINFO*)calloc(DS.LUmem,sizeof(LUINFO))) == NULL) {
		MessageBox("** Error ** Cannot allocate LUINFO ", "error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	//
	int		id = 0;
	int		cnt = 0;
	for (int v = 0; v < 13; v++) {
		for (int m = 0; m < 20; m++) {
			if (CODE_TABLE[v][m].refcnt == 0) continue;
			if (cnt == 0) {
				Copy_Luinfo(&DS.LUdata[cnt], CODE_TABLE[v][m]);
				CODE_TABLE[v][m].renumber = cnt + 1;
				DS.LUdata[cnt].NO = cnt + 1;
				cnt++;
			}
			else {
				id = UNDEF;
				for (int k = 0; k < cnt; k++) {
					if (IsSame_Luinfo(DS.LUdata[k], CODE_TABLE[v][m])){ id = k; break; }
				}
				if (id == UNDEF) {
					Copy_Luinfo(&DS.LUdata[cnt], CODE_TABLE[v][m]);
					CODE_TABLE[v][m].renumber = cnt + 1;
					DS.LUdata[cnt].NO = cnt + 1;
					id = cnt;
					cnt++;
				}
				CODE_TABLE[v][m].renumber = id + 1;
				
			}
			//
			if (cnt == DS.LUmem) {
				DS.LUmem += 10;
				if ((DS.LUdata = (LUINFO*)realloc(DS.LUdata,DS.LUmem*sizeof(LUINFO))) == NULL) {
					MessageBox("** Error ** Cannot reallocate LUINFO ", "error", MB_OK | MB_ICONEXCLAMATION);
					return;
				}
			}
		}
	}
	DS.LUnum = cnt;
	///
	// ＬＵにRENUMBERの値を入れる

	int  zero = 0,ttl=0;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {  //****** MESH[v][h].FAO_CODE == 0 の場合？？？？
			if (MESH[v][h].flag == 0) continue;
			if (MESH[v][h].Soil != 0) {
				MESH[v][h].Lu = CODE_TABLE[MESH[v][h].Soil - 1][MESH[v][h].Cover - 1].renumber;
				if (MESH[v][h].Soil == 13)zero++;
			}
			else {
				MESH[v][h].Lu = CODE_TABLE[12][MESH[v][h].Cover - 1].renumber;
				zero++;
			}
			ttl++;
		}
	}
	///--------------------------------------------------
	/*
		表示入れ替え
	*/
	///--------------------------------------------------
	m_Combo_LU.ResetContent();
	for (int i = 0; i < DS.LUnum; i++){
		str.Format("%d", i + 1);
		m_Combo_LU.AddString(str);
	}
	CLAND = 0;
	//
	CWnd* cw = GetDlgItem(IDC_PLABEL_13);	// 総数　LUnum
	str.Format(" / %d", DS.LUnum);
	cw->SetWindowTextA(str);
	//
	/// add 2015 12  LUの適用メッシュ数の表示
	for (int i = 0; i < DS.LUnum; i++) DS.LUdata[i].appmesh = 0;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;
			DS.LUdata[MESH[v][h].Lu - 1].appmesh++;
		}
	}
	s_MeshNum.Format("[ %d ]", DS.LUdata[CLAND].appmesh);
	//
	DS.b_CSrenumber = TRUE;		// 実行フラグの設定
	//
	Disp_Data();
	UDF;
	///--------------------------------------------------
	/*
		土地利用の有効化　ファイル書き出し
	*/
	///--------------------------------------------------
	DS.in_use[LU_FILE] = DS.in_avail[LU_FILE] = DS.in_exist[LU_FILE] = DS.need_save[LU_FILE] = TRUE;
	Write_Data_File(LU_FILE, 0, 0, DS, PM, MESH);
	//
	Change_Nums++;
	//
}
