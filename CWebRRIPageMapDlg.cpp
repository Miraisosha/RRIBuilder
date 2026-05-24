// CWebRRIPageMapDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "CWebRRIPageMapDlg.h"
#include "afxdialogex.h"
#include "WebRRIInputDlg.h"


// CWebRRIPageMapDlg ダイアログ

IMPLEMENT_DYNAMIC(CWebRRIPageMapDlg, CDialogEx)

CWebRRIPageMapDlg::CWebRRIPageMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBRRI_PAGE_MAP, pParent)
{

}

CWebRRIPageMapDlg::~CWebRRIPageMapDlg()
{
}

void CWebRRIPageMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebRRIPageMapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GRIDAREA_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnGridareaMap)
	ON_BN_CLICKED(IDC_BTN_ELEVATION_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnElevationMap)
	ON_BN_CLICKED(IDC_BTN_DIRECTION_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnDirectionMap)
	ON_BN_CLICKED(IDC_BTN_ACCUMULATION_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnAccumulationMap)
	ON_BN_CLICKED(IDC_BTN_WIDTH_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnWidthMap)
	ON_BN_CLICKED(IDC_BTN_DEPTH_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnDepthMap)
	ON_BN_CLICKED(IDC_BTN_LEVEE_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnLeveeMap)
	ON_BN_CLICKED(IDC_BTN_SLOPELENGTH_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnSlopelengthMap)
	ON_BN_CLICKED(IDC_BTN_SLOPEANGLE_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnSlopeangleMap)
	ON_BN_CLICKED(IDC_BTN_SOILDEPTH_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnSoildepthMap)
	ON_BN_CLICKED(IDC_BTN_ACQUIFERDEPTH_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnAcquiferdepthMap)
	ON_BN_CLICKED(IDC_BTN_ZREF_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnZrefMap)
	ON_BN_CLICKED(IDC_BTN_MET_ALT_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnMetAltMap)
	ON_BN_CLICKED(IDC_BTN_LAND_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnLandMap)
	ON_BN_CLICKED(IDC_BTN_SOILMAP, &CWebRRIPageMapDlg::OnBnClickedBtnSoilmap)
	ON_BN_CLICKED(IDC_BTN_SOIL_CODE, &CWebRRIPageMapDlg::OnBnClickedBtnSoilCode)
	ON_BN_CLICKED(IDC_BTN_SOIL_TABLE, &CWebRRIPageMapDlg::OnBnClickedBtnSoilTable)
	ON_BN_CLICKED(IDC_BTN_MET_MAP, &CWebRRIPageMapDlg::OnBnClickedBtnMetMap)
END_MESSAGE_MAP()


// CWebRRIPageMapDlg メッセージ ハンドラー


void CWebRRIPageMapDlg::OnBnClickedBtnGridareaMap()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_GRIDAREA_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnElevationMap()
{
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_ELEVATION_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnDirectionMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_DIRECTION_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnAccumulationMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_ACCUMULATION_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnWidthMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_WIDTH_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnDepthMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_DEPTH_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnLeveeMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_LEVEE_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSlopelengthMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SLOPELENGTH_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSlopeangleMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SLOPEANGLE_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSoildepthMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SOILDEPTH_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnAcquiferdepthMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_ACQUIFERDEPTH_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnZrefMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_ZREF_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnMetAltMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_MET_ALT_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnLandMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_LAND_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSoilmap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SOIL_MAP);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSoilCode()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SOIL_CODE);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnSoilTable()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_SOIL_TABLE);
	}
}


void CWebRRIPageMapDlg::OnBnClickedBtnMetMap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd* pMain = GetParent()->GetParent();
	if (pMain) {
		pMain->GetParent()->SendMessage(
			WM_WEBRRI_EVENT,
			WEBRRI_EVT_SELECT_FILE,
			IDC_EDIT_MET_MAP);
	}
}
