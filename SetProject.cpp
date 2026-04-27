// SetProject.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "SetProject.h"
#include "afxdialogex.h"

//#include "RRI_DLG.h"
#include "RI_DLG.h"
#include "RRI_Common.h"
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
extern char			m_RecentPath[];
extern char			m_BootPath[];

extern DATASET		DSET;
extern PARAMS			PM;							// 基本情報
extern int			CEX;							// 外部データ番号　< EXnum

extern int			File_Folder_Num;
extern CString		File_Folder_Name[];
extern int			File_Folder_ID[];
//
int		GuideID[3] = { IDC_COMBO_EXDATA, IDC_STATIC_MESH, IDC_MESH_SIZE };
int		NonGuideID[5] = { IDC_RADIO_20, IDC_RADIO_21, IDC_BUTTON_READEX, IDC_BUTTON_READACC, IDC_BUTTON_READDIR };
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

IMPLEMENT_DYNAMIC(CSetProject, CDialogEx)

CSetProject::CSetProject(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetProject::IDD, pParent)
	, s_ProjTitle(_T(""))
//	, m_Comment(_T("Ready !"))
{

}

CSetProject::~CSetProject()
{
}

void CSetProject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROJTITLE, s_ProjTitle);
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	DDX_Control(pDX, IDC_COMBO_EXDATA, c_ExCombo);
	DDX_Control(pDX, IDC_BUTTON_READEX, c_EXDEM);
	DDX_Control(pDX, IDC_BUTTON_READACC, c_EXACC);
	DDX_Control(pDX, IDC_BUTTON_READDIR, c_EXDIR);
}

BEGIN_MESSAGE_MAP(CSetProject, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetProject::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_PROJTITLE, &CSetProject::OnEnChangeEditProjtitle)
	ON_CBN_SELCHANGE(IDC_COMBO_EXDATA, &CSetProject::OnCbnSelchangeComboExdata)
	ON_BN_CLICKED(IDC_RADIO_10, &CSetProject::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO_11, &CSetProject::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO_12, &CSetProject::OnBnClickedRadio12)	// 20190201 Add
	ON_BN_CLICKED(IDC_RADIO_21, &CSetProject::OnBnClickedRadio21)
	ON_BN_CLICKED(IDC_RADIO_20, &CSetProject::OnBnClickedRadio20)
	ON_BN_CLICKED(IDC_BUTTON_READEX, &CSetProject::OnBnClickedButtonReadex)
	ON_BN_CLICKED(IDC_BUTTON_READACC, &CSetProject::OnBnClickedButtonReadacc)
	ON_BN_CLICKED(IDC_BUTTON_READDIR, &CSetProject::OnBnClickedButtonReaddir)
END_MESSAGE_MAP()
//_______________________________________________________________________________________
/// /////////////////////////////////////////////////////////////////////////////////////
//   FIX FUNCTIONS
/// /////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int AFXAPI CSetProject::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED && lpData)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	return 0;
}
//   BUTTON_DIR
BOOL	CSetProject::Button_Dir(CString* m_DirName, char* m_RecentPath)
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
		Info.pidlRoot = 0;
		Info.pszDisplayName = cRetPath;
		Info.lpszTitle = _T("Select folder");
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
		*m_DirName = pszRetPath;
		strcpy(m_RecentPath, *m_DirName);
		pMalloc->Release();
		//
	}
	return TRUE;
}

// 
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//
//   CSetProject メッセージ ハンドラー
//
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL CSetProject::OnInitDialog()
{
	CDialogEx::OnInitDialog();
// 表示はすべて表示させる。
	CEX = 0;
	// JFlow = 0: BIL = 1から
	for (int i = 1; i < PM.EXnum; i++) 	c_ExCombo.AddString(PM.EXDATA[i].Gname);
	//
	c_ExCombo.SetCurSel(CEX);
	UDF;
	//
	s_ProjTitle = _T("");
	strcpy(DSET.Proj_Title, s_ProjTitle);
	//
	Disp_Radio();
	//
	UDF;
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
void CSetProject::Disp_Radio()
{
	CButton		*cb1, *cb2;
	CButton		*cb3;	// 20190201 Add
	CWnd*		cw;
	//
	cb1 = (CButton*)GetDlgItem(IDC_RADIO_10);
	cb2 = (CButton*)GetDlgItem(IDC_RADIO_11);
	cb3 = (CButton*)GetDlgItem(IDC_RADIO_12);
	if (PM.B_UseJFlow) {
		cb1->SetCheck(FALSE);
		cb2->SetCheck(FALSE);
		cb3->SetCheck(TRUE);
	}
	else if (PM.B_UseGuide) {
		cb1->SetCheck(TRUE);
		cb2->SetCheck(FALSE);
		cb3->SetCheck(FALSE);
	}
	else  {
		cb1->SetCheck(FALSE);
		cb2->SetCheck(TRUE);
		cb3->SetCheck(FALSE);
	}
	cb1 = (CButton*)GetDlgItem(IDC_RADIO_20);
	cb2 = (CButton*)GetDlgItem(IDC_RADIO_21);
	if (PM.B_LatLng) {
		cb1->SetCheck(TRUE);
		cb2->SetCheck(FALSE);
	}
	else  {
		cb1->SetCheck(FALSE);
		cb2->SetCheck(TRUE);
	}
	// Window
	if (PM.B_UseJFlow) {
		for (int i = 0; i < 5; i++) {
			if (i == 0) { cw = GetDlgItem(GuideID[i]); cw->EnableWindow(TRUE); }
			cw = GetDlgItem(NonGuideID[i]); cw->EnableWindow(FALSE);
		}
	}
	else if (PM.B_UseGuide) {
		for (int i = 0; i < 5; i++) {
			if (i == 0) { cw = GetDlgItem(GuideID[i]); cw->EnableWindow(TRUE); }
			cw = GetDlgItem(NonGuideID[i]); cw->EnableWindow(FALSE);
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			if (i == 0) {cw = GetDlgItem(GuideID[i]); cw->EnableWindow(FALSE);	}
			cw = GetDlgItem(NonGuideID[i]); cw->EnableWindow(TRUE);
		}
	}

}

void CSetProject::OnEnChangeEditProjtitle() { UDT;}
//
BOOL CSetProject::Set_DSET()
{
	// check
	strcpy(DSET.Proj_Title, s_ProjTitle);
	for (int i = 0; i < strlen(DSET.Proj_Title); i++){
		if (DSET.Proj_Title[i] == ' ') {
			MessageBox("** Error ** The project name should not contain spaces.", "Alarm", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}
	//  外部読み込みの場合　ファイルの確認
	if (!PM.B_UseGuide) {
		if (strlen(DSET.EX_Dem_File) == 0) {
			MessageBox("** Error ** DEM file is not found", "Alarm", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		if (strlen(DSET.EX_Acc_File) == 0) {
			MessageBox("** Error ** ACC file is not found", "Alarm", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		if (strlen(DSET.EX_Dir_File) == 0) {
			MessageBox("** Error ** DIR file is not found", "Alarm", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}
	//
	CString		cmd;
	ProjDir.Format("%s/Project/%s", m_BootPath, DSET.Proj_Title);
	Shift_Unix(&ProjDir);
	//
	cmd.Format("Project Folder is created at following folder...OK ?\n [ %s ]", ProjDir);
	if (MessageBox(cmd, "ask", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		if (!Button_Dir(&ProjDir, m_RecentPath)) return FALSE;
	}
	strcpy(DSET.Proj_Folder, ProjDir);
	if (Folder_Exist(ProjDir) ) {	// 既存
		if (MessageBox("Folder already exists. Delete all files ?", "Alarm", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			Delete_Folder(DSET.Proj_Folder);
			CreateDirectory(DSET.Proj_Folder, NULL);
		}
	}
	else  CreateDirectory(DSET.Proj_Folder, NULL);
	//
	/// フォルダー内に作るサブフォルダの名前
	for (int i = 0; i < File_Folder_Num; i++) {
		if (i == 0) strcpy(DSET.Folder_Name[i], DSET.Proj_Folder);
		else  sprintf(DSET.Folder_Name[i],"%s\\%s", DSET.Proj_Folder, File_Folder_Name[i]);		
	}
//
// Set File Name
	Set_File_FullName(&DSET);
	DSET.in_use[ADEM_FILE] = TRUE;
	DSET.in_use[ACC_FILE] = TRUE;
	DSET.in_use[ADIR_FILE] = TRUE;
//
	return TRUE;
}
void CSetProject::OnBnClickedRadio10()  { UDT; PM.B_UseGuide = TRUE; PM.B_UseJFlow = FALSE; Disp_Radio(); }
void CSetProject::OnBnClickedRadio11()	{ UDT; PM.B_UseGuide = FALSE; PM.B_UseJFlow = FALSE; Disp_Radio(); }
void CSetProject::OnBnClickedRadio12()	{ UDT; PM.B_UseGuide = TRUE; PM.B_UseJFlow = TRUE; Disp_Radio(); }	// 20190201 Add
void CSetProject::OnBnClickedRadio20()  { UDT; PM.B_LatLng = TRUE; DSET.SW_LatLong = !PM.B_LatLng; Disp_Radio(); }
void CSetProject::OnBnClickedRadio21()  { UDT; PM.B_LatLng = FALSE; DSET.SW_LatLong = !PM.B_LatLng;  Disp_Radio(); }

// 
//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
//
//   プロジェクト確定
//
////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CSetProject::OnBnClickedOk()
{
	if (s_ProjTitle.IsEmpty()){
		MessageBox("** Error ** Set new project name", "Alarm", MB_OK | MB_ICONERROR);
		return;
	}
	//
	if (!Set_DSET()) return;
	//
	if (!PM.B_UseJFlow) {
		CEX = CEX + 1; // J_FLWが配列１つ目なので、１＋する。
	}
	if (PM.B_UseGuide) {
		PM.Deg_Unit = PM.Coord_Unit =  PM.EXDATA[CEX].Files[EX_ACC].subdev;
		PM.Size = 1. / PM.Deg_Unit;
	}
	//
	CDialogEx::OnOK();
}

void CSetProject::OnCbnSelchangeComboExdata()
{
	CEX = c_ExCombo.GetCurSel();
}

//__________________________________________________________
///   外部DEMデータファイルの指定

void CSetProject::OnBnClickedButtonReadex()
{
	CString		fname;
	if (!Button_File(TRUE, &fname, m_RecentPath, "ArcGIS Format DEM", "*")) return;
	//
	strcpy(DSET.EX_Dem_File, fname);
	c_EXDEM.SetWindowTextA(fname);
}


void CSetProject::OnBnClickedButtonReadacc()
{
	CString		fname;
	if (!Button_File(TRUE, &fname, m_RecentPath, "ArcGIS Format ACC", "*")) return;
	//
	strcpy(DSET.EX_Acc_File, fname);
	c_EXACC.SetWindowTextA(fname);
}


void CSetProject::OnBnClickedButtonReaddir()
{
	CString		fname;
	if (!Button_File(TRUE, &fname, m_RecentPath, "ArcGIS Format DIR", "*")) return;
	//
	strcpy(DSET.EX_Dir_File, fname);
	c_EXDIR.SetWindowTextA(fname);
}
