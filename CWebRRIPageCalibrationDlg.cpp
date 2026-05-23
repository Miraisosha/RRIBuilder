// CWebRRIPageCalibrationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "CWebRRIPageCalibrationDlg.h"
#include "afxdialogex.h"


// CWebRRIPageCalibrationDlg ダイアログ

IMPLEMENT_DYNAMIC(CWebRRIPageCalibrationDlg, CDialogEx)

CWebRRIPageCalibrationDlg::CWebRRIPageCalibrationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBRRI_PAGE_CALIBRATION, pParent)
{

}

CWebRRIPageCalibrationDlg::~CWebRRIPageCalibrationDlg()
{
}

void CWebRRIPageCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebRRIPageCalibrationDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebRRIPageCalibrationDlg メッセージ ハンドラー
BOOL CWebRRIPageCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//
	// meteo_input_type
	//
	CComboBox* pMeteoType =
		(CComboBox*)GetDlgItem(IDC_CMB_METEO_INPUT_TYPE);

	pMeteoType->AddString(_T("0"));
	pMeteoType->AddString(_T("1"));
	pMeteoType->AddString(_T("3"));

	pMeteoType->SetCurSel(0);

	//
	// rainfall_input_type
	//
	CComboBox* pRainType =
		(CComboBox*)GetDlgItem(IDC_CMB_RAINFALL_INPUT_TYPE);

	pRainType->AddString(_T("1"));
	pRainType->AddString(_T("2"));

	pRainType->SetCurSel(0);


	return true;
}
