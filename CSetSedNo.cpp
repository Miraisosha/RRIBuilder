// CSetSedNo.cpp : 実装ファイル
//
#include "stdafx.h"
#include "RRI_GUI.h"
#include "CSetSedNo.h"
#include "afxdialogex.h"


short CSetSedNo::ms_SedMin = 1;
short CSetSedNo::ms_SedMax = 20;


// CSetSedNo ダイアログ
IMPLEMENT_DYNAMIC(CSetSedNo, CDialogEx)

CSetSedNo::CSetSedNo(short oriSedNo, COLVAL_FIX* colorSet, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_SED_NO, pParent), 
	m_selSedNo(oriSedNo), m_colorSet(colorSet)
{
}

CSetSedNo::~CSetSedNo()
{
}

void CSetSedNo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetSedNo, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSetSedNo::OnSedNoChanged)
END_MESSAGE_MAP()


BOOL CSetSedNo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DisplayColorForSelSedNo();

	return TRUE;
}


void CSetSedNo::DisplayColorForSelSedNo() {
	if (m_colorSet == nullptr) return;
	if (m_selSedNo < ms_SedMin || m_selSedNo > min(ms_SedMax, sizeof(m_colorSet->Rcol) / sizeof(COLORREF))) return;

	Fill_Color(GetDlgItem(IDC_LBL_COLOR), m_colorSet->Rcol[m_selSedNo - 1]);
}

// CSetSedNo メッセージ ハンドラー
void CSetSedNo::OnSedNoChanged()
{
	char		buf[3];
	CEdit* cw = (CEdit*)GetDlgItem(IDC_EDIT1);
	cw->GetWindowTextA(buf, 3);

	if (strlen(buf) == 0) return;
	try {
		auto valNo = static_cast<short>(atoi(buf));
		if (valNo > ms_SedMax) valNo = ms_SedMax;
		if (valNo < ms_SedMin) valNo = ms_SedMin;
		if (valNo == m_selSedNo) return;
		m_selSedNo = valNo;
	}
	catch (...) {
		MessageBox("Input Number value should be integer number from 1 to 20!");
		return;
	}

	DisplayColorForSelSedNo();
}