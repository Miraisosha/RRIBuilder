// CWebRRIPageGeneralDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "CWebRRIPageGeneralDlg.h"
#include "afxdialogex.h"
#include "WebRRIInputDlg.h"

// CWebRRIPageGeneralDlg ダイアログ

IMPLEMENT_DYNAMIC(CWebRRIPageGeneralDlg, CDialogEx)

CWebRRIPageGeneralDlg::CWebRRIPageGeneralDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBRRI_PAGE_GENERAL, pParent)
{

}

CWebRRIPageGeneralDlg::~CWebRRIPageGeneralDlg()
{
}

void CWebRRIPageGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebRRIPageGeneralDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PARA_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnParaDir)
	ON_BN_CLICKED(IDC_BTN_DATA_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnDataDir)
	ON_BN_CLICKED(IDC_BTN_RESULT1_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnResult1Dir)
	ON_BN_CLICKED(IDC_BTN_RESULT2_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnResult2Dir)
	ON_BN_CLICKED(IDC_BTN_SIMULATION_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnSimulationDir)
	ON_BN_CLICKED(IDC_BTN_RECV_DIR, &CWebRRIPageGeneralDlg::OnBnClickedBtnRecvDir)
END_MESSAGE_MAP()

BOOL CWebRRIPageGeneralDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

	//
	// recv_mode
	//
	CComboBox* pRecvMode =
		(CComboBox*)GetDlgItem(IDC_CMB_RECV_MODE);

	pRecvMode->AddString(_T("0"));
	pRecvMode->AddString(_T("1"));

	pRecvMode->SetCurSel(0);

    return TRUE;
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnParaDir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FOLDER,
			IDC_EDIT_PARA_DIR);
	}
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnDataDir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FOLDER,
			IDC_EDIT_DATA_DIR);
	}
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnResult1Dir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FOLDER,
			IDC_EDIT_RESULT1_DIR);
	}
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnResult2Dir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FOLDER,
			IDC_EDIT_RESULT2_DIR);
	}
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnSimulationDir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FOLDER,
			IDC_EDIT_SIMULATION_DIR);
	}
}


void CWebRRIPageGeneralDlg::OnBnClickedBtnRecvDir()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
//		pMain->SendMessage(
//			WM_WEBRRI_EVENT,
//			WEBRRI_EVT_SELECT_FOLDER,
//			IDC_EDIT_RECV_DIR);
	}
}
