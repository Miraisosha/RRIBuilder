// CWebRRIPageDamDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "CWebRRIPageDamDlg.h"
#include "afxdialogex.h"
#include "WebRRIInputDlg.h"


// CWebRRIPageDamDlg ダイアログ

IMPLEMENT_DYNAMIC(CWebRRIPageDamDlg, CDialogEx)

CWebRRIPageDamDlg::CWebRRIPageDamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBRRI_PAGE_DAM, pParent)
{

}

CWebRRIPageDamDlg::~CWebRRIPageDamDlg()
{
}

void CWebRRIPageDamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebRRIPageDamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DAMFILE, &CWebRRIPageDamDlg::OnBnClickedBtnDamfile)
END_MESSAGE_MAP()


// CWebRRIPageDamDlg メッセージ ハンドラー
BOOL CWebRRIPageDamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//
	// dam_switch
	//
	CComboBox* pDamSwitch =
		(CComboBox*)GetDlgItem(IDC_CMB_DAM_SWITCH);

	pDamSwitch->AddString(_T("0"));
	pDamSwitch->AddString(_T("1"));

	pDamSwitch->SetCurSel(0);

	return true;
}


void CWebRRIPageDamDlg::OnBnClickedBtnDamfile()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_DAMFILE);
	}
}
