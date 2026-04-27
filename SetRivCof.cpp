// SetRivCof.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "SetRivCof.h"
#include "afxdialogex.h"

#include		"CommFuncs.h"
#include		"RRI_Common.h"

// CSetRivCof ダイアログ
extern   PARAMS			PM;							// 基本情報
extern   DATASET			DSET;						// ファイルセット

int		W_RADID[5] = { IDC_RADIO_WU, IDC_RADIO_WC, IDC_EDIT_W, IDC_EDIT_CW, IDC_EDIT_SW };
int		D_RADID[5] = { IDC_RADIO_DU, IDC_RADIO_DC, IDC_EDIT_D, IDC_EDIT_CD, IDC_EDIT_SD };


IMPLEMENT_DYNAMIC(CSetRivCof, CDialogEx)

CSetRivCof::CSetRivCof(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetRivCof::IDD, pParent)
	, s_H(_T(""))
	, s_W(_T(""))
	, s_D(_T(""))
	, s_CD(_T(""))
	, s_CW(_T(""))
	, s_SD(_T(""))
	, s_SW(_T(""))
{

}

CSetRivCof::~CSetRivCof()
{
}

void CSetRivCof::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_D, s_Dep);
	DDX_Text(pDX, IDC_EDIT_H, s_H);
	DDX_Text(pDX, IDC_EDIT_W, s_W);
	DDX_Text(pDX, IDC_EDIT_D, s_D);
	DDX_Text(pDX, IDC_EDIT_CD, s_CD);
	DDX_Text(pDX, IDC_EDIT_CW, s_CW);
	DDX_Text(pDX, IDC_EDIT_SD, s_SD);
	DDX_Text(pDX, IDC_EDIT_SW, s_SW);
}


BEGIN_MESSAGE_MAP(CSetRivCof, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_W, &CSetRivCof::OnEnChangeEditW)
	ON_EN_CHANGE(IDC_EDIT_D, &CSetRivCof::OnEnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_H, &CSetRivCof::OnEnChangeEditH)
	ON_BN_CLICKED(IDOK, &CSetRivCof::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CW, &CSetRivCof::OnEnChangeEditCw)
	ON_EN_CHANGE(IDC_EDIT_SW, &CSetRivCof::OnEnChangeEditSw)
	ON_EN_CHANGE(IDC_EDIT_CD, &CSetRivCof::OnEnChangeEditCd)
	ON_EN_CHANGE(IDC_EDIT_SD, &CSetRivCof::OnEnChangeEditSd)
	ON_BN_CLICKED(IDC_RADIO_WU, &CSetRivCof::OnBnClickedRadioWu)
	ON_BN_CLICKED(IDC_RADIO_WC, &CSetRivCof::OnBnClickedRadioWc)
	ON_BN_CLICKED(IDC_RADIO_DU, &CSetRivCof::OnBnClickedRadioDu)
	ON_BN_CLICKED(IDC_RADIO_DC, &CSetRivCof::OnBnClickedRadioDc)
END_MESSAGE_MAP()

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CSetRivCof メッセージ ハンドラー
BOOL CSetRivCof::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	HowtoW = HowtoD = 1;
	//
	CWnd*		cw;
	CButton*		cb;
	//
	for (int i = 0; i < 5; i++) {
		cw = GetDlgItem(W_RADID[i]);
		if (DSET.in_use[WIDTH_FILE] && DSET.in_avail[WIDTH_FILE]) cw->EnableWindow(TRUE);
		else                                                 cw->EnableWindow(FALSE);
		//
		cb = (CButton*)cw;
		if (i <= 2) {
			if (i == HowtoW) cb->SetCheck(1);
			else				cb->SetCheck(0);
		}
		//
		cw = GetDlgItem(D_RADID[i]);
		if (DSET.in_use[DEPTH_FILE] && DSET.in_avail[DEPTH_FILE]) cw->EnableWindow(TRUE);
		else                                                 cw->EnableWindow(FALSE);
		cb = (CButton*)cw;
		if (i <= 2) {
			if (i == HowtoD) cb->SetCheck(1);
			else				cb->SetCheck(0);
		}
	}
	if (DSET.in_use[WIDTH_FILE] && DSET.in_avail[WIDTH_FILE]) {
		s_CW.Format("%.3lf", DSET.Cof_WC);
		s_SW.Format("%.3lf", DSET.Cof_WS);
	}
	if (DSET.in_use[DEPTH_FILE] && DSET.in_avail[DEPTH_FILE]) {
		s_CD.Format("%.3lf", DSET.Cof_DC);
		s_SD.Format("%.3lf", DSET.Cof_DS);
	}
	UDF;
	//
	cw = GetDlgItem(IDC_EDIT_H);
	if (DSET.in_use[HEIGHT_FILE] && DSET.in_avail[HEIGHT_FILE]) cw->EnableWindow(TRUE);
	else                                                 cw->EnableWindow(FALSE);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSetRivCof::OnEnChangeEditW() { UDT; }
void CSetRivCof::OnEnChangeEditD() { UDT; }
void CSetRivCof::OnEnChangeEditH() { UDT; }
void CSetRivCof::OnEnChangeEditCw() { UDT; }
void CSetRivCof::OnEnChangeEditSw() { UDT; }
void CSetRivCof::OnEnChangeEditCd() { UDT; }
void CSetRivCof::OnEnChangeEditSd() { UDT; }

void CSetRivCof::OnBnClickedRadioWu() { HowtoW = 0; }
void CSetRivCof::OnBnClickedRadioWc() { HowtoW = 1; }

void CSetRivCof::OnBnClickedRadioDu() { HowtoD = 0; }
void CSetRivCof::OnBnClickedRadioDc() { HowtoD = 1; }

void CSetRivCof::OnBnClickedOk()
{
	if (DSET.in_use[WIDTH_FILE] && DSET.in_avail[WIDTH_FILE]) {
		if (HowtoW == 0 && s_W.IsEmpty()) return; 
		if (HowtoW == 1 && (s_CW.IsEmpty() || s_SW.IsEmpty())) return;

		if ( HowtoW == 0 ) Wid = atof(s_W);
		else {
			Cw = atof(s_CW);
			Sw = atof(s_SW);
		}
	}
	//
	if (DSET.in_use[DEPTH_FILE] && DSET.in_avail[DEPTH_FILE]) {
		if (HowtoD == 0 && s_D.IsEmpty()) return;
		if (HowtoD == 1 && (s_CD.IsEmpty() || s_SD.IsEmpty())) return;

		if (HowtoD == 0) Dep = atof(s_D);
		else {
			Cd = atof(s_CD);
			Sd = atof(s_SD);
		}
	}
	//
	if (DSET.in_use[HEIGHT_FILE] && DSET.in_avail[HEIGHT_FILE]) {
		if (s_H.IsEmpty()) return;
		H = atof(s_H);
	}
	//
	CDialogEx::OnOK();
}

