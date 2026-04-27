// Tab_InFile.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Tab_InFile.h"
#include "afxdialogex.h"
//
extern		DATASET			DS;
extern		int				CLAND;
extern		char				m_RecentPath[];
extern		MINFO**			MESH;
extern		PARAMS			PM;
extern		DATASET			DSET;
extern		int				File_Format[];
extern		int				File_Order[];
extern		CString			File_Extention[];
extern       CString		MODEL_EDIT_NAME[];

//
int				BIN_Num = FILE_IN_USE;
int				BIN_ID[] = {
	IDC_BUTTON_FILE_0, IDC_BUTTON_FILE_1, IDC_BUTTON_FILE_2, IDC_BUTTON_FILE_3, IDC_BUTTON_FILE_4,
	IDC_BUTTON_FILE_5, IDC_BUTTON_FILE_6, IDC_BUTTON_FILE_7, IDC_BUTTON_FILE_8, IDC_BUTTON_FILE_9,
	IDC_BUTTON_FILE_10, IDC_BUTTON_FILE_11, IDC_BUTTON_FILE_12, IDC_BUTTON_FILE_13, IDC_BUTTON_FILE_14,
	IDC_BUTTON_FILE_15, IDC_BUTTON_FILE_16, IDC_BUTTON_FILE_17, IDC_BUTTON_FILE_18, IDC_BUTTON_FILE_19,
	IDC_BUTTON_FILE_20 };
CString			BIN_Text[FILE_IN_USE];
int				BIN_LABEL_ID[] = {
	IDC_FILELABEL_1, IDC_FILELABEL_2, IDC_FILELABEL_3, IDC_FILELABEL_4, IDC_FILELABEL_5,
	IDC_FILELABEL_6, IDC_FILELABEL_7, IDC_FILELABEL_8, IDC_FILELABEL_9, IDC_FILELABEL_10,
	IDC_FILELABEL_11, IDC_FILELABEL_12, IDC_FILELABEL_13, IDC_FILELABEL_14, IDC_FILELABEL_15,
	IDC_FILELABEL_16, IDC_FILELABEL_17, IDC_FILELABEL_18, IDC_FILELABEL_19, IDC_FILELABEL_20,
	IDC_FILELABEL_21 };

int				IMPORT_ID[] = {
	IDC_BUTTON_IMPORT_1, IDC_BUTTON_IMPORT_9, IDC_BUTTON_IMPORT_10, IDC_BUTTON_IMPORT_11, IDC_BUTTON_IMPORT_12,
	IDC_BUTTON_IMPORT_13, IDC_BUTTON_IMPORT_14, IDC_BUTTON_IMPORT_15, IDC_BUTTON_IMPORT_16, IDC_BUTTON_IMPORT_17,
	IDC_BUTTON_IMPORT_18, IDC_BUTTON_IMPORT_19, IDC_BUTTON_IMPORT_20, IDC_BUTTON_IMPORT_21, IDC_BUTTON_IMPORT_22,
	IDC_BUTTON_IMPORT_23, IDC_BUTTON_IMPORT_24, IDC_BUTTON_IMPORT_25, IDC_BUTTON_IMPORT_26, IDC_BUTTON_IMPORT_27,
	IDC_BUTTON_IMPORT_28 };

int				DELETE_ID[] = {
	IDC_BUTTON_DELETE_1, IDC_BUTTON_DELETE_2, IDC_BUTTON_DELETE_3, IDC_BUTTON_DELETE_4, IDC_BUTTON_DELETE_5,
	IDC_BUTTON_DELETE_6, IDC_BUTTON_DELETE_7, IDC_BUTTON_DELETE_8, IDC_BUTTON_DELETE_9, IDC_BUTTON_DELETE_10,
	IDC_BUTTON_DELETE_11, IDC_BUTTON_DELETE_12, IDC_BUTTON_DELETE_13, IDC_BUTTON_DELETE_14, IDC_BUTTON_DELETE_15,
	IDC_BUTTON_DELETE_16, IDC_BUTTON_DELETE_17, IDC_BUTTON_DELETE_18, IDC_BUTTON_DELETE_19, IDC_BUTTON_DELETE_20,
	IDC_BUTTON_DELETE_21 };


extern			CString		File_Title[];

// CTab_InFile ダイアログ

IMPLEMENT_DYNAMIC(CTab_InFile, CDialogEx)

CTab_InFile::CTab_InFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab_InFile::IDD, pParent)
{

}

CTab_InFile::~CTab_InFile()
{
}

void CTab_InFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab_InFile, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE_0, &CTab_InFile::OnBnClickedButtonFile0)
	ON_BN_CLICKED(IDC_BUTTON_FILE_1, &CTab_InFile::OnBnClickedButtonFile1)
	ON_BN_CLICKED(IDC_BUTTON_FILE_2, &CTab_InFile::OnBnClickedButtonFile2)
	ON_BN_CLICKED(IDC_BUTTON_FILE_3, &CTab_InFile::OnBnClickedButtonFile3)
	ON_BN_CLICKED(IDC_BUTTON_FILE_4, &CTab_InFile::OnBnClickedButtonFile4)
	ON_BN_CLICKED(IDC_BUTTON_FILE_5, &CTab_InFile::OnBnClickedButtonFile5)
	ON_BN_CLICKED(IDC_BUTTON_FILE_6, &CTab_InFile::OnBnClickedButtonFile6)
	ON_BN_CLICKED(IDC_BUTTON_FILE_7, &CTab_InFile::OnBnClickedButtonFile7)
	ON_BN_CLICKED(IDC_BUTTON_FILE_8, &CTab_InFile::OnBnClickedButtonFile8)
	ON_BN_CLICKED(IDC_BUTTON_FILE_9, &CTab_InFile::OnBnClickedButtonFile9)
	ON_BN_CLICKED(IDC_BUTTON_FILE_10, &CTab_InFile::OnBnClickedButtonFile10)
	ON_BN_CLICKED(IDC_BUTTON_FILE_11, &CTab_InFile::OnBnClickedButtonFile11)
	ON_BN_CLICKED(IDC_BUTTON_FILE_12, &CTab_InFile::OnBnClickedButtonFile12)
	ON_BN_CLICKED(IDC_BUTTON_FILE_13, &CTab_InFile::OnBnClickedButtonFile13)
	ON_BN_CLICKED(IDC_BUTTON_FILE_14, &CTab_InFile::OnBnClickedButtonFile14)
	ON_BN_CLICKED(IDC_BUTTON_FILE_15, &CTab_InFile::OnBnClickedButtonFile15)
	ON_BN_CLICKED(IDC_BUTTON_FILE_16, &CTab_InFile::OnBnClickedButtonFile16)
	ON_BN_CLICKED(IDC_BUTTON_FILE_17, &CTab_InFile::OnBnClickedButtonFile17)
	ON_BN_CLICKED(IDC_BUTTON_FILE_18, &CTab_InFile::OnBnClickedButtonFile18)
	ON_BN_CLICKED(IDC_BUTTON_FILE_19, &CTab_InFile::OnBnClickedButtonFile19)
	ON_BN_CLICKED(IDC_BUTTON_FILE_20, &CTab_InFile::OnBnClickedButtonFile20)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_1, &CTab_InFile::OnBnClickedButtonImport1)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_9, &CTab_InFile::OnBnClickedButtonImport9)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_10, &CTab_InFile::OnBnClickedButtonImport10)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_11, &CTab_InFile::OnBnClickedButtonImport11)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_12, &CTab_InFile::OnBnClickedButtonImport12)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_13, &CTab_InFile::OnBnClickedButtonImport13)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_14, &CTab_InFile::OnBnClickedButtonImport14)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_15, &CTab_InFile::OnBnClickedButtonImport15)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_16, &CTab_InFile::OnBnClickedButtonImport16)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_17, &CTab_InFile::OnBnClickedButtonImport17)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_18, &CTab_InFile::OnBnClickedButtonImport18)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_19, &CTab_InFile::OnBnClickedButtonImport19)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_20, &CTab_InFile::OnBnClickedButtonImport20)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_21, &CTab_InFile::OnBnClickedButtonImport21)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_22, &CTab_InFile::OnBnClickedButtonImport22)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_23, &CTab_InFile::OnBnClickedButtonImport23)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_24, &CTab_InFile::OnBnClickedButtonImport24)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_25, &CTab_InFile::OnBnClickedButtonImport25)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_26, &CTab_InFile::OnBnClickedButtonImport26)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_27, &CTab_InFile::OnBnClickedButtonImport27)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_28, &CTab_InFile::OnBnClickedButtonImport28)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_1, &CTab_InFile::OnBnClickedButtonDelete1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_2, &CTab_InFile::OnBnClickedButtonDelete2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_3, &CTab_InFile::OnBnClickedButtonDelete3)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_4, &CTab_InFile::OnBnClickedButtonDelete4)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_5, &CTab_InFile::OnBnClickedButtonDelete5)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_6, &CTab_InFile::OnBnClickedButtonDelete6)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_7, &CTab_InFile::OnBnClickedButtonDelete7)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_8, &CTab_InFile::OnBnClickedButtonDelete8)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_9, &CTab_InFile::OnBnClickedButtonDelete9)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_10, &CTab_InFile::OnBnClickedButtonDelete10)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_11, &CTab_InFile::OnBnClickedButtonDelete11)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_12, &CTab_InFile::OnBnClickedButtonDelete12)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_13, &CTab_InFile::OnBnClickedButtonDelete13)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_14, &CTab_InFile::OnBnClickedButtonDelete14)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_15, &CTab_InFile::OnBnClickedButtonDelete15)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_16, &CTab_InFile::OnBnClickedButtonDelete16)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_17, &CTab_InFile::OnBnClickedButtonDelete17)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_18, &CTab_InFile::OnBnClickedButtonDelete18)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_19, &CTab_InFile::OnBnClickedButtonDelete19)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_20, &CTab_InFile::OnBnClickedButtonDelete20)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_21, &CTab_InFile::OnBnClickedButtonDelete21)
END_MESSAGE_MAP()

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  タブの初期化・変更
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


BOOL CTab_InFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	INVnum = 0;		// 無効化数
	Tab_Init();
	SetCtrlPosition();
	Disp_Data();

	Change_Nums = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTab_InFile::SetCtrlPosition() {
#if APP_VERSION != FULL_VER
	for (int i = FILE_IN_USE - 1; i >= 5; i--) {
		this->MoveCtrl(BIN_LABEL_ID[i], BIN_LABEL_ID[i - 1]);
		this->MoveCtrl(DELETE_ID[i], DELETE_ID[i - 1]);
		this->MoveCtrl(BIN_ID[i], BIN_ID[i - 1]);
		this->MoveCtrl(IMPORT_ID[i], IMPORT_ID[i - 1]);
	}
#endif // !SIMP_VER
}

void CTab_InFile::Tab_Init()
{
	CWnd		*cw;
	//
	for (int i = 0; i < FILE_IN_USE; i++) {
		cw = GetDlgItem(BIN_LABEL_ID[i]);
		cw->SetWindowTextA(File_Title[i]);
	}
}

void CTab_InFile::Disp_Data()
{
	CWnd		*cl, *cf,*cd;
	//
	for (int i = 0; i < FILE_IN_USE; i++) {
		cl = GetDlgItem(BIN_LABEL_ID[i]);
		cd = GetDlgItem(DELETE_ID[i]);
		cf = GetDlgItem(BIN_ID[i]);
		cf->EnableWindow(TRUE);
		//
		if (DS.in_use[i]) {
			cl->EnableWindow(TRUE);
			cd->EnableWindow(TRUE);
			Get_Relative_Path(DS.File_names[i], DS.Proj_Folder, DS.Input_names[i]);
			cf->SetWindowTextA(DS.Input_names[i]);
		}
		else {
			cl->EnableWindow(FALSE);
			cd->EnableWindow(FALSE);
			cf->SetWindowTextA("-");
		}
	}
}

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  ファイル 選択
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_InFile::Get_FileName(int no)
{
	CString		fname;
	//
	if (!Button_File(FALSE, &fname, m_RecentPath, "Data File name", "*")) return;
	//
	if (!DS.in_use[no]) DS.in_use[no] = TRUE;
	strcpy(DS.File_names[no], fname);
	Get_Relative_Path(DS.File_names[no], DS.Proj_Folder, DS.Input_names[no]);
	//
	Change_Nums++;
	Disp_Data();
}
//
void CTab_InFile::OnBnClickedButtonFile0() { Get_FileName(RAIN_FILE); }
void CTab_InFile::OnBnClickedButtonFile1() { Get_FileName(ADEM_FILE); }
void CTab_InFile::OnBnClickedButtonFile2() { Get_FileName(ACC_FILE); }
void CTab_InFile::OnBnClickedButtonFile3() { Get_FileName(ADIR_FILE); }
void CTab_InFile::OnBnClickedButtonFile4() { Get_FileName(SED_FILE); }

void CTab_InFile::OnBnClickedButtonFile5() { Get_FileName(LU_FILE); }
void CTab_InFile::OnBnClickedButtonFile6() { Get_FileName(WIDTH_FILE); }
void CTab_InFile::OnBnClickedButtonFile7() { Get_FileName(DEPTH_FILE); }
void CTab_InFile::OnBnClickedButtonFile8() { Get_FileName(HEIGHT_FILE); }

void CTab_InFile::OnBnClickedButtonFile9() { Get_FileName(HS_FILE); }
void CTab_InFile::OnBnClickedButtonFile10() { Get_FileName(HR_FILE); }
void CTab_InFile::OnBnClickedButtonFile11() { Get_FileName(HG_FILE); }
void CTab_InFile::OnBnClickedButtonFile12() { Get_FileName(GAMPT_FILE); }

void CTab_InFile::OnBnClickedButtonFile13() { Get_FileName(HS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonFile14() { Get_FileName(HR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonFile15() { Get_FileName(QS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonFile16() { Get_FileName(QR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonFile17() { Get_FileName(DAM_CNT_FILE); }
void CTab_InFile::OnBnClickedButtonFile18() { Get_FileName(DIV_FILE); }
void CTab_InFile::OnBnClickedButtonFile19() { Get_FileName(POTENT_FILE); }
void CTab_InFile::OnBnClickedButtonFile20() { Get_FileName(LOCATION_FILE); }

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  ファイル インポート
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_InFile::File_Import(int no)
{
	CString		imname, svname,longname,str;
	char			EXT[SIZE_1K];
	int			ret;
	//
	strcpy(EXT, File_Extention[no]);
	if (!Button_File(TRUE, &imname, m_RecentPath, "Import Data File", EXT)) return;
	//
	if (no >= ADEM_FILE && no <= HEIGHT_FILE) {
		if (!Match_Model(imname)) {
			MessageBox("** Error ** Model mismatch...!", "Abort", MB_OK | MB_ICONASTERISK);
			return;
		}
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  READ DATA
	//
	if (Read_Data_File(no, imname, &DSET, MESH)) {
		str.Format("** Error ** Cannot read import data as [%s]", MODEL_EDIT_NAME[no]);
		MessageBox(str, "Abort", MB_OK | MB_ICONASTERISK);
		return;
	}
	//
	svname = DSET.Input_names[no];
	str.Format("Saving this file as [ %s ].... OK? ", svname);
	if ((ret = MessageBox(str, "filename", MB_YESNOCANCEL | MB_ICONASTERISK)) == IDCANCEL) return;
	//
	if (ret == IDNO) {
		if (!Button_File(FALSE, &longname, m_RecentPath, "Save as", EXT)) return;
		strcpy(DSET.File_names[no], longname);
		Get_Relative_Path(DSET.File_names[no], DSET.Proj_Folder, DSET.Input_names[no]);
		svname = DSET.Input_names[no];
	}
	//
	IMkind[IMnum] = no;
	IMname[IMnum] = imname;
//	strcpy(DS.Input_names[no], svname);
	IMnum++;
	Change_Nums++;
	//
	DS.in_use[no] = TRUE;
	//Get_Relative_Path(DS.File_names[no], DS.Proj_Folder, DS.Input_names[no]);
	//
	Disp_Data();
}
BOOL CTab_InFile::Match_Model(CString  imname)
{
	char		fname[SIZE_1K];
	strcpy(fname, imname);
	int		nH, nV;
	double	stLAT, stLNG, Size;
	//
	Get_ArcGIS_Info(fname, &nH, &nV, &stLAT, &stLNG, &Size);
	//
	if (!(nH == PM.MHnum && nV == PM.MVnum)) return FALSE;
	if (stLAT != PM.stLAT || stLNG != PM.stLNG || Size != PM.Size) return FALSE;
	//
	return TRUE;
}
void CTab_InFile::OnBnClickedButtonImport1()  { File_Import(RAIN_FILE); }
void CTab_InFile::OnBnClickedButtonImport9()  { File_Import(ADEM_FILE); }
void CTab_InFile::OnBnClickedButtonImport10() { File_Import(ACC_FILE); }
void CTab_InFile::OnBnClickedButtonImport11() { File_Import(ADIR_FILE); }
void CTab_InFile::OnBnClickedButtonImport12() { File_Import(SED_FILE); }

void CTab_InFile::OnBnClickedButtonImport13() { File_Import(LU_FILE); }
void CTab_InFile::OnBnClickedButtonImport14() { File_Import(WIDTH_FILE); }
void CTab_InFile::OnBnClickedButtonImport15() { File_Import(DEPTH_FILE); }
void CTab_InFile::OnBnClickedButtonImport16() { File_Import(HEIGHT_FILE); }

void CTab_InFile::OnBnClickedButtonImport17() { File_Import(HS_FILE); }
void CTab_InFile::OnBnClickedButtonImport18() { File_Import(HR_FILE); }
void CTab_InFile::OnBnClickedButtonImport19() { File_Import(HG_FILE); }
void CTab_InFile::OnBnClickedButtonImport20() { File_Import(GAMPT_FILE); }

void CTab_InFile::OnBnClickedButtonImport21() { File_Import(HS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonImport22() { File_Import(HR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonImport23() { File_Import(QS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonImport24() { File_Import(QR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonImport25() { File_Import(DAM_CNT_FILE); }
void CTab_InFile::OnBnClickedButtonImport26() { File_Import(DIV_FILE); }
void CTab_InFile::OnBnClickedButtonImport27() { File_Import(POTENT_FILE); }
void CTab_InFile::OnBnClickedButtonImport28() { File_Import(LOCATION_FILE); }

///-----------------------------------------------------------------------------------------------------------
//  ファイルの有効・無効
///-----------------------------------------------------------------------------------------------------------  
//
void CTab_InFile::Switch_File(int no)
{
	CString		fname;
	if (DS.in_use[no]) {
		DS.in_use[no] = DS.in_avail[no] = FALSE;
		Change_Nums++;
		INV[INVnum++] = no;
	}
	//
	Disp_Data();
}

void CTab_InFile::OnBnClickedButtonDelete1() { Switch_File(RAIN_FILE); }
void CTab_InFile::OnBnClickedButtonDelete2(){ Switch_File(ADEM_FILE); }
void CTab_InFile::OnBnClickedButtonDelete3(){ Switch_File(ACC_FILE); }
void CTab_InFile::OnBnClickedButtonDelete4(){ Switch_File(ADIR_FILE); }
void CTab_InFile::OnBnClickedButtonDelete5() { Switch_File(SED_FILE); }

void CTab_InFile::OnBnClickedButtonDelete6(){ Switch_File(LU_FILE); }
void CTab_InFile::OnBnClickedButtonDelete7(){ Switch_File(WIDTH_FILE); }
void CTab_InFile::OnBnClickedButtonDelete8(){ Switch_File(DEPTH_FILE); }
void CTab_InFile::OnBnClickedButtonDelete9(){ Switch_File(HEIGHT_FILE); }

void CTab_InFile::OnBnClickedButtonDelete10(){ Switch_File(HS_FILE); }
void CTab_InFile::OnBnClickedButtonDelete11(){ Switch_File(HR_FILE); }
void CTab_InFile::OnBnClickedButtonDelete12(){ Switch_File(HG_FILE); }
void CTab_InFile::OnBnClickedButtonDelete13(){ Switch_File(GAMPT_FILE); }

void CTab_InFile::OnBnClickedButtonDelete14(){ Switch_File(HS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonDelete15(){ Switch_File(HR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonDelete16(){ Switch_File(QS_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonDelete17(){ Switch_File(QR_WLEV_FILE); }
void CTab_InFile::OnBnClickedButtonDelete18(){ Switch_File(DAM_CNT_FILE); }
void CTab_InFile::OnBnClickedButtonDelete19(){ Switch_File(DIV_FILE); }
void CTab_InFile::OnBnClickedButtonDelete20(){ Switch_File(POTENT_FILE); }
void CTab_InFile::OnBnClickedButtonDelete21(){ Switch_File(LOCATION_FILE); }

BOOL CTab_InFile::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN) { return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTab_InFile::MoveCtrl(int srcID, int tarID)
{
	RECT rect;
	auto pTarWnd = GetDlgItem(tarID);
	if (pTarWnd == nullptr) return;
	pTarWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);

	auto pSrcWnd = GetDlgItem(srcID);
	if (pSrcWnd == nullptr) return;
	pSrcWnd->MoveWindow(&rect);
}
