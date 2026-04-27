// MultiColor.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "MultiColor.h"
#include "afxdialogex.h"
#include "RRI_Common.h"
//
extern      PARAMS		PM;							// 基本情報
extern      int			CDATA;
extern      char			m_BootPath[SIZE_05K];
extern      DATASET		DSET;						// ファイルセット

/////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int			NUM_ID[21] = {	IDC_VAL_0,
							IDC_VAL_1, IDC_VAL_2, IDC_VAL_3, IDC_VAL_4, IDC_VAL_5,
							IDC_VAL_6, IDC_VAL_7, IDC_VAL_8, IDC_VAL_9, IDC_VAL_10,
							IDC_VAL_11, IDC_VAL_12 ,IDC_VAL_13, IDC_VAL_14, IDC_VAL_15,
							IDC_VAL_16, IDC_VAL_17, IDC_VAL_18, IDC_VAL_19, IDC_VAL_20 };
int			COLOR_ID[21] = {  IDC_COLOR_0,
							IDC_COLOR_1, IDC_COLOR_2, IDC_COLOR_3, IDC_COLOR_4, IDC_COLOR_5,
							IDC_COLOR_6, IDC_COLOR_7, IDC_COLOR_8, IDC_COLOR_9, IDC_COLOR_10,
							IDC_COLOR_11, IDC_COLOR_12 ,IDC_COLOR_13, IDC_COLOR_14, IDC_COLOR_15,
							IDC_COLOR_16, IDC_COLOR_17, IDC_COLOR_18, IDC_COLOR_19, IDC_COLOR_20 };

// CMultiColor ダイアログ

IMPLEMENT_DYNAMIC(CMultiColor, CDialogEx)

CMultiColor::CMultiColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiColor::IDD, pParent)
{

}

CMultiColor::~CMultiColor()
{
}

void CMultiColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMultiColor, CDialogEx)
	ON_WM_TIMER()
	ON_STN_DBLCLK(IDC_COLOR_0, &CMultiColor::OnStnDblclickColor0)
	ON_STN_DBLCLK(IDC_COLOR_1, &CMultiColor::OnStnDblclickColor1)
	ON_STN_DBLCLK(IDC_COLOR_2, &CMultiColor::OnStnDblclickColor2)
	ON_STN_DBLCLK(IDC_COLOR_3, &CMultiColor::OnStnDblclickColor3)
	ON_STN_DBLCLK(IDC_COLOR_4, &CMultiColor::OnStnDblclickColor4)
	ON_STN_DBLCLK(IDC_COLOR_5, &CMultiColor::OnStnDblclickColor5)
	ON_STN_DBLCLK(IDC_COLOR_6, &CMultiColor::OnStnDblclickColor6)
	ON_STN_DBLCLK(IDC_COLOR_7, &CMultiColor::OnStnDblclickColor7)
	ON_STN_DBLCLK(IDC_COLOR_8, &CMultiColor::OnStnDblclickColor8)
	ON_STN_DBLCLK(IDC_COLOR_9, &CMultiColor::OnStnDblclickColor9)
	ON_STN_DBLCLK(IDC_COLOR_10, &CMultiColor::OnStnDblclickColor10)
	ON_STN_DBLCLK(IDC_COLOR_11, &CMultiColor::OnStnDblclickColor11)
	ON_STN_DBLCLK(IDC_COLOR_12, &CMultiColor::OnStnDblclickColor12)
	ON_STN_DBLCLK(IDC_COLOR_13, &CMultiColor::OnStnDblclickColor13)
	ON_STN_DBLCLK(IDC_COLOR_14, &CMultiColor::OnStnDblclickColor14)
	ON_STN_DBLCLK(IDC_COLOR_15, &CMultiColor::OnStnDblclickColor15)
	ON_STN_DBLCLK(IDC_COLOR_16, &CMultiColor::OnStnDblclickColor16)
	ON_STN_DBLCLK(IDC_COLOR_17, &CMultiColor::OnStnDblclickColor17)
	ON_STN_DBLCLK(IDC_COLOR_18, &CMultiColor::OnStnDblclickColor18)
	ON_STN_DBLCLK(IDC_COLOR_19, &CMultiColor::OnStnDblclickColor19)
	ON_STN_DBLCLK(IDC_COLOR_20, &CMultiColor::OnStnDblclickColor20)
	ON_BN_CLICKED(IDCANCEL, &CMultiColor::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMultiColor::OnBnClickedOk)
END_MESSAGE_MAP()


// CMultiColor メッセージ ハンドラー


BOOL CMultiColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//
	Title = "Set color for Land use data";
	if (CDATA == LAND_COVER)		Title = "Set color for Cover data";
	else if (CDATA == LAND_SOIL)   Title = "Set color for Soil data";
	this->SetWindowTextA(Title);
	//
	///
	// データに変更があった場合は、PM.Change_DCOL に記述
	PM.Change_DCOL = FALSE;

	for (int i = 0; i < 21; i++) COPY_COLOR[i] = PM.Dcol[CDATA].Rcol[i];	// Cancel の場合の保存
	SetTimer(10, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
///=============================================================================================
//
///  ON TIMER

void CMultiColor::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(10);
	//
	Draw_Color();
}
void CMultiColor::Draw_Color()
{
	CWnd		*cv, *cc;
	CRect	crect;
	int		NUM;
	//
	if (CDATA == LU_FILE) NUM = DSET.LUnum+1;
	else    NUM = PM.Dcol[CDATA].num;

	/*if (CDATA == LU_FILE && PM.B_UseJFlow) {
		CDATA = LU_FILE_JP;
	}*/
	for (int i = 0; i < 21; i++){
		cc = GetDlgItem(COLOR_ID[i]);
		if (i < NUM) {
			cc->GetClientRect(&crect);
			Fill_Color(cc, PM.Dcol[CDATA].Rcol[i]); // flag の関連から１から始まる
			cc->ValidateRect(&crect);
		}
		else {
			cc->EnableWindow(FALSE);
			cv = GetDlgItem(NUM_ID[i]);
			cv->EnableWindow(FALSE);
		}
	}

	if (CDATA == LU_FILE_JP && PM.B_UseJFlow) {
		CDATA = LU_FILE;
	}

}
void CMultiColor::GetColorDlg(int id)
{
	CColorDialog CC;
	if (CC.DoModal() == IDCANCEL) return;
	//
	if (CDATA == LU_FILE && PM.B_UseJFlow) {
		CDATA = LU_FILE_JP;
	}
	PM.Dcol[CDATA].Rcol[id] = CC.GetColor();
	PM.Change_DCOL = TRUE;
	if (CDATA == LU_FILE_JP && PM.B_UseJFlow) {
		CDATA = LU_FILE;
	}
	//
	Draw_Color();

}


void CMultiColor::OnStnDblclickColor0() { GetColorDlg(0); }
void CMultiColor::OnStnDblclickColor1() { GetColorDlg(1); }
void CMultiColor::OnStnDblclickColor2() { GetColorDlg(2); }
void CMultiColor::OnStnDblclickColor3() { GetColorDlg(3); }
void CMultiColor::OnStnDblclickColor4() { GetColorDlg(4); }
void CMultiColor::OnStnDblclickColor5() { GetColorDlg(5); }
void CMultiColor::OnStnDblclickColor6() { GetColorDlg(6); }
void CMultiColor::OnStnDblclickColor7() { GetColorDlg(7); }
void CMultiColor::OnStnDblclickColor8() { GetColorDlg(8); }
void CMultiColor::OnStnDblclickColor9() { GetColorDlg(9); }
void CMultiColor::OnStnDblclickColor10() { GetColorDlg(10); }
void CMultiColor::OnStnDblclickColor11() { GetColorDlg(11); }
void CMultiColor::OnStnDblclickColor12() { GetColorDlg(12); }
void CMultiColor::OnStnDblclickColor13() { GetColorDlg(13); }
void CMultiColor::OnStnDblclickColor14() { GetColorDlg(14); }
void CMultiColor::OnStnDblclickColor15() { GetColorDlg(15); }
void CMultiColor::OnStnDblclickColor16() { GetColorDlg(16); }
void CMultiColor::OnStnDblclickColor17() { GetColorDlg(17); }
void CMultiColor::OnStnDblclickColor18() { GetColorDlg(18); }
void CMultiColor::OnStnDblclickColor19() { GetColorDlg(19); }
void CMultiColor::OnStnDblclickColor20() { GetColorDlg(20); }

void CMultiColor::OnBnClickedCancel()
{
	PM.Change_DCOL = FALSE;
	//
	for (int i = 0; i < 21; i++) PM.Dcol[CDATA].Rcol[i] = COPY_COLOR[i];	// Cancel の場合の保存
	//
	CDialogEx::OnCancel();
}


void CMultiColor::OnBnClickedOk()
{
	if (PM.Change_DCOL) {
		if (MessageBox("Do you save the changes to the default color file.?\nDefault file = ./RRI_CONTENTS/Color_Data_B.dat",
			"Save", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			CString	path = m_BootPath;
			Save_Color_Data(path, &PM);
		}
	}
	//
	CDialogEx::OnOK();
}
