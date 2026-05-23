// CWebRRIPageOutputDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "CWebRRIPageOutputDlg.h"
#include "afxdialogex.h"


// CWebRRIPageOutputDlg ダイアログ

IMPLEMENT_DYNAMIC(CWebRRIPageOutputDlg, CDialogEx)

CWebRRIPageOutputDlg::CWebRRIPageOutputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBRRI_PAGE_OUTPUT, pParent)
{

}

CWebRRIPageOutputDlg::~CWebRRIPageOutputDlg()
{
}

void CWebRRIPageOutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebRRIPageOutputDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL CWebRRIPageOutputDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CListCtrl* pList =
        (CListCtrl*)GetDlgItem(IDC_LST_STION);

    // Report Style
    pList->ModifyStyle(0, LVS_REPORT);

    // Full Row Select
    pList->SetExtendedStyle(
        LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES);

    // Columns
    pList->InsertColumn(0, _T("No"), LVCFMT_CENTER, 70);
    pList->InsertColumn(1, _T("NAME"), LVCFMT_LEFT, 200);
    pList->InsertColumn(2, _T("LOC_I"), LVCFMT_CENTER, 100);
    pList->InsertColumn(3, _T("LOC_J"), LVCFMT_CENTER, 100);

    // Dummy Data
    pList->InsertItem(0, _T("1"));
    pList->SetItemText(0, 1, _T("OUT"));
    pList->SetItemText(0, 2, _T("120"));
    pList->SetItemText(0, 3, _T("85"));

    pList->InsertItem(1, _T("2"));
    pList->SetItemText(1, 1, _T("Right"));
    pList->SetItemText(1, 2, _T("220"));
    pList->SetItemText(1, 3, _T("140"));

    pList->InsertItem(2, _T("3"));
    pList->SetItemText(2, 1, _T("Left"));
    pList->SetItemText(2, 2, _T("350"));
    pList->SetItemText(2, 3, _T("210"));

    return TRUE;
}
