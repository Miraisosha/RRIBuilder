// MakeData.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "MakeData.h"
#include "afxdialogex.h"


#include "RRI_Common.h"
//
extern      DATASET		DSET;						// ファイルセット
extern      char			m_RecentPath[];
extern      PARAMS		PM;							// 基本情報
extern      MINFO**		MESH;

extern      int			File_Format[];
extern      int			File_Order[];

//---------------------------------------------------------------------------------------
int		ItemNum = 3;
int		DataNo[] = { WIDTH_FILE, DEPTH_FILE, HEIGHT_FILE};
int		ContID[][4] = { { IDC_BUTTON_IMPORT_1, IDC_EDIT3, IDC_EDIT4, IDC_BUTTON_GO_3 },
						{ IDC_BUTTON_IMPORT_2, IDC_EDIT5, IDC_EDIT6, IDC_BUTTON_GO_4 },
						{ IDC_BUTTON_IMPORT_3, IDC_EDIT7, IDC_EDIT8, IDC_BUTTON_GO_5 } };
int		EditID[][2] = { { IDC_EDIT3, IDC_EDIT4},
						{ IDC_EDIT5, IDC_EDIT6},
						{ IDC_EDIT7, IDC_EDIT8} };
int		SIGNAL_ID[8] = { IDC_SIGNAL_1, IDC_SIGNAL_2, IDC_SIGNAL_3 };
//
//---------------------------------------------------------------------------------------
// CMakeData ダイアログ

IMPLEMENT_DYNAMIC(CMakeData, CDialogEx)

CMakeData::CMakeData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMakeData::IDD, pParent)
	, s_AccLimit(_T(""))
{

}

CMakeData::~CMakeData()
{
}

void CMakeData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RIV, s_AccLimit);
}


BEGIN_MESSAGE_MAP(CMakeData, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &CMakeData::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMakeData::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CMakeData::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMakeData::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CMakeData::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON_GO_3, &CMakeData::OnBnClickedButtonGo3)
	ON_BN_CLICKED(IDC_BUTTON_GO_4, &CMakeData::OnBnClickedButtonGo4)
	ON_BN_CLICKED(IDC_BUTTON_GO_5, &CMakeData::OnBnClickedButtonGo5)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT8, &CMakeData::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT_RIV, &CMakeData::OnEnChangeEditRiv)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CMakeData::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CMakeData::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CMakeData メッセージ ハンドラー


BOOL CMakeData::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//
	CWnd*		cw;
	CRect		rect;
	for (int i = 0; i < 3; i++) {
		cw = GetDlgItem(SIGNAL_ID[i]);
		cw->GetClientRect(&rect);
		cw->ValidateRect(&rect);
	}
	Display_State();
	SetTimer(MODELING_TIMER, 50,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CMakeData::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(MODELING_TIMER);
	Display_State();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CMakeData::Display_State()
{
	CButton	*Bfile,*Bgo;
	CEdit	*ce1,*ce2;
	CString	str;
	int		fno;
	//
	s_AccLimit.Format("%.0lf", DSET.Riv_Thresh); UDF;
	for (int i = 0; i < ItemNum; i++) {	
		Bgo = (CButton*)GetDlgItem(ContID[i][3]);
		ce1 = (CEdit*)GetDlgItem(EditID[i][0]);
		ce2 = (CEdit*)GetDlgItem(EditID[i][1]);
		///
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/// 数値入力
		switch (i) {
			case 0:	Make_String(DSET.Cof_WC, &str,UNDEF); ce1->SetWindowTextA(str);
				Make_String(DSET.Cof_WS, &str, UNDEF); ce2->SetWindowTextA(str);
				break;
			case 1:	Make_String(DSET.Cof_DC, &str, UNDEF); ce1->SetWindowTextA(str);
				Make_String(DSET.Cof_DS, &str, UNDEF); ce2->SetWindowTextA(str);
				break;
			case 2:	Make_String(DSET.Cof_H, &str, UNDEF); ce1->SetWindowTextA(str);
				Make_String(DSET.Cof_Hlim, &str, UNDEF); ce2->SetWindowTextA(str);
				break;
			default:break;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 無効・有効  in_avail で判断　
	}
	UDF;
	//
	CWnd*	cw;
	CRect	rect;
	for (int i = 0; i < 3; i++) {
		fno = DataNo[i];
		cw = GetDlgItem(SIGNAL_ID[i]);
		cw->GetClientRect(&rect);
		if (DSET.in_avail[fno])		Fill_Color(cw, RGB(0, 255, 0));
		else if (DSET.in_use[fno])		Fill_Color(cw, RGB(255, 255, 0));
		cw->ValidateRect(&rect);
	}
	//
	//cw = GetDlgItem(IDC_BUTTON_ASSENBLE);
	//if (DSET.in_avail[LU_FILE] && DSET.LUnum > 1)	cw->EnableWindow(TRUE);
	//else											cw->EnableWindow(FALSE);
}

/// Edit Control ----------------------------------------------------------------

void CMakeData::OnEnChangeEdit3() { UDT; }
void CMakeData::OnEnChangeEdit4() { UDT; }
void CMakeData::OnEnChangeEdit5() { UDT; }
void CMakeData::OnEnChangeEdit6() { UDT; }
void CMakeData::OnEnChangeEdit7() { UDT; }
void CMakeData::OnEnChangeEdit8() { UDT; }

/// Make File-------------------------------------------------------------------
void CMakeData::Make_File(int no)
{
	CString		cmf,fname;
	int			ret;
	cmf.Format("Save file name : %s  Yes/No ?", DSET.File_names[DataNo[no]]);
	if ((ret = MessageBox(cmf, "Save file", MB_YESNOCANCEL | MB_ICONQUESTION)) == IDCANCEL) return;
	else if ( ret == IDNO) {
		if (!Button_File(FALSE, &fname, m_RecentPath, "Save file", "*")) return;
		strcpy(DSET.File_names[DataNo[no]], fname);
	}
	//
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++){
			switch (no) {
				case 0:	if (MESH[v][h].Acc >= DSET.Riv_Thresh)  
							MESH[v][h].Rwidth = DSET.Cof_WC*pow((MESH[v][h].Acc*PM.Unit_Area), DSET.Cof_WS);
						else MESH[v][h].Rwidth = NODATA;
						break;
				case 1:if (MESH[v][h].Acc >= DSET.Riv_Thresh)  MESH[v][h].Rdepth = DSET.Cof_DC*pow((MESH[v][h].Acc*PM.Unit_Area), DSET.Cof_DS);
					   else MESH[v][h].Rdepth = NODATA;
					   break;
				case 2:if ((MESH[v][h].Acc*PM.Unit_Area) >= DSET.Cof_Hlim)  MESH[v][h].Bheight = DSET.Cof_H;
					   else MESH[v][h].Bheight = NODATA;
					   break;
			}
		}
	}
	//
	::SetCurrentDirectory(DSET.Proj_Folder);
	DSET.in_avail[DataNo[no]] = DSET.in_use[DataNo[no]] =  TRUE;
	Write_Data_File(DataNo[no], File_Format[DataNo[no]], File_Order[DataNo[no]], DSET, PM, MESH);
	DSET.Data_From[DataNo[no]] = 0;
	//
	if (DSET.in_avail[DataNo[0]] && DSET.in_avail[DataNo[1]] && DSET.in_avail[DataNo[2]]) DSET.Riv_Avail = TRUE;
	else       DSET.Riv_Avail = FALSE;
	//
	Display_State();
}
void CMakeData::OnBnClickedButtonGo3()
{
	CEdit*		ce = (CEdit*)GetDlgItem(EditID[0][0]);
	CString		str;
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_WC = atof(str);
	}
	ce = (CEdit*)GetDlgItem(EditID[0][1]);
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_WS = atof(str);
	}
	//
	Make_File(0);
}

void CMakeData::OnBnClickedButtonGo4()
{
	CEdit*		ce = (CEdit*)GetDlgItem(EditID[1][0]);
	CString		str;
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_DC = atof(str);
	}
	ce = (CEdit*)GetDlgItem(EditID[1][1]);
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_DS = atof(str);
	}
	//
	Make_File(1);
}

void CMakeData::OnBnClickedButtonGo5()
{
	CEdit*		ce = (CEdit*)GetDlgItem(EditID[2][0]);
	CString		str;
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_H = atof(str);
	}
	ce = (CEdit*)GetDlgItem(EditID[2][1]);
	if (ce->GetModify()) {
		ce->GetWindowTextA(str);
		DSET.Cof_Hlim = atof(str);
	}
	//
	Make_File(2);
}



void CMakeData::OnEnChangeEditRiv()
{
	UDT;
	DSET.Riv_Thresh = atof(s_AccLimit);
}


void CMakeData::OnBnClickedButtonSet()
{
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0 || MESH[v][h].flag > ID_MESH_R) continue;	// 他の設定はスルー
			if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)	MESH[v][h].flag = ID_MESH_R;
			else													MESH[v][h].flag = ID_MESH;
		}
	}
	//
	CDialogEx::OnOK();
}


void CMakeData::OnBnClickedButtonCancel()
{
	DSET.in_avail[DataNo[0]] = DSET.in_avail[DataNo[1]] = DSET.in_avail[DataNo[2]] = FALSE;
	DSET.in_use[DataNo[0]] = DSET.in_use[DataNo[1]] = DSET.in_use[DataNo[2]] = FALSE;
	DSET.Riv_Avail = FALSE;
	//
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0 || MESH[v][h].flag > ID_MESH_R) continue;	// 他の設定はスルー
			if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)	MESH[v][h].flag = ID_MESH_R;
			else													MESH[v][h].flag = ID_MESH;
		}
	}
	//
	CDialogEx::OnCancel();
}
