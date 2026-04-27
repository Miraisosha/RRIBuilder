// OutputSelectionDlg.cpp : implementation file
//
#include "stdafx.h"
#include "RRI_GUI.h"
#include "RRI_Common.h"
#include "OutputSelectionDlg.h"
#include "afxdialogex.h"

// OutputSelectionDlg dialog

IMPLEMENT_DYNAMIC(OutputSelectionDlg, CDialogEx)

OutputSelectionDlg::OutputSelectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_OUTPUT, pParent)
{
}

OutputSelectionDlg::~OutputSelectionDlg()
{
}

void OutputSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EXE, m_combToolExe);
	DDX_Control(pDX, IDC_COMBO_DATA_TYPE, m_combDataType);
}

BEGIN_MESSAGE_MAP(OutputSelectionDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_EXE, &OutputSelectionDlg::OnSelchangeComboExe)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA_TYPE, &OutputSelectionDlg::OnSelchangeComboDataType)
END_MESSAGE_MAP()


BOOL OutputSelectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
#if APP_VERSION != SIMP_VER
	m_combToolExe.AddString("ANAL{FH01-06");
	m_combToolExe.AddString("HRNowcast");
#else
	m_combToolExe.AddString("Radar/Raingauge-Analyzed Precipitation");
	m_combToolExe.AddString("High-resolution Precipitation Nowcasts");
#endif
	m_combToolExe.SetCurSel(0);
	m_nToolExe = ToolExeType::Radar;

	m_nDataType = DataType::Rainfall;
	m_combDataType.EnableWindow(FALSE);

#if APP_VERSION != SIMP_VER
	CButton* cb_rain = (CButton*)GetDlgItem(IDC_CHECK_RAIN);
	CButton* cb_jmaj = (CButton*)GetDlgItem(IDC_CHECK_JMAJ);
	CButton* cb_jmay = (CButton*)GetDlgItem(IDC_CHECK_JMAY);
	cb_rain->SetCheck(BST_CHECKED);
	cb_jmaj->SetCheck(BST_CHECKED);
	cb_jmay->SetCheck(BST_CHECKED);
#else
	const int up_offset_hide = -60;
	ResetCtrl(IDC_OUTPUT_TYPE_GROUP, 0, up_offset_hide);
	ResetCtrl(IDC_CHECK_RAIN, 0, up_offset_hide);
	ResetCtrl(IDC_CHECK_JMAJ, 0, up_offset_hide);
	ResetCtrl(IDC_CHECK_JMAY, 0, up_offset_hide);

	const int up_offset_show = -80;
	MoveCtrl(IDOK, 0, up_offset_show);
	MoveCtrl(IDCANCEL, 0, up_offset_show);
	this->SetWindowPos(NULL, 0, 0, 360, 200, SWP_NOMOVE | SWP_NOZORDER);
#endif

	return TRUE;  
}


void OutputSelectionDlg::OnOK()
{
#if APP_VERSION != SIMP_VER
	CButton* cb_rain = (CButton*)GetDlgItem(IDC_CHECK_RAIN);
	CButton* cb_jmaj = (CButton*)GetDlgItem(IDC_CHECK_JMAJ);
	CButton* cb_jmay = (CButton*)GetDlgItem(IDC_CHECK_JMAY);
	create_rain = cb_rain->GetCheck();
	create_jmaj = cb_jmaj->GetCheck();
	create_jmay = cb_jmay->GetCheck();
#else
	create_rain = true;
	create_jmaj = false;
	create_jmay = false;
#endif
	CDialogEx::OnOK();
}


void OutputSelectionDlg::OnSelchangeComboExe()
{
	auto curToolExe = m_combToolExe.GetCurSel();
	auto nCurToolExe = static_cast<ToolExeType>(curToolExe);

	if (nCurToolExe == m_nToolExe) return;

	m_nToolExe = nCurToolExe;
	if (m_nToolExe == ToolExeType::NowCast) {
		m_combDataType.AddString("Rainfall");
		m_combDataType.AddString("Precipitation Intensity");
		m_combDataType.SetCurSel(0);
		m_combDataType.EnableWindow(TRUE);
	} else {
		for (int i = m_combDataType.GetCount() - 1; i >= 0; i--){
			m_combDataType.DeleteString(i);
		}
		m_combDataType.EnableWindow(FALSE);
		m_nDataType = DataType::Rainfall;
	}
}


void OutputSelectionDlg::OnSelchangeComboDataType()
{
	auto curDataType = m_combDataType.GetCurSel();
	m_nDataType = static_cast<DataType>(curDataType);
}

void OutputSelectionDlg::ResetCtrl(int srcID, int x_offset, int y_offset)
{
	MoveCtrl(srcID, x_offset, y_offset);
	GetDlgItem(srcID)->SetWindowPos(NULL, 0, 0, 5, 5, SWP_NOMOVE | SWP_NOZORDER);
	HideCtrl(srcID);
}

void OutputSelectionDlg::MoveCtrl(int srcID, int x_offset, int y_offset)
{
	RECT rect;
	GetDlgItem(srcID)->GetWindowRect(&rect);
	rect.top += y_offset;
	rect.bottom += y_offset;
	rect.left += x_offset;
	rect.right += x_offset;
	ScreenToClient(&rect);
	GetDlgItem(srcID)->MoveWindow(&rect);
}

void OutputSelectionDlg::HideCtrl(int srcID)
{
	GetDlgItem(srcID)->ShowWindow(SW_HIDE);
}