// Group.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Group.h"
#include "afxdialogex.h"

#include		"CommFuncs.h"

// CGroup ダイアログ

IMPLEMENT_DYNAMIC(CGroup, CDialogEx)

CGroup::CGroup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGroup::IDD, pParent)
	, s_Name(_T(""))
{

}

CGroup::~CGroup()
{
}

void CGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, s_Name);
}


BEGIN_MESSAGE_MAP(CGroup, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGroup::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CGroup::OnEnChangeEditName)
END_MESSAGE_MAP()


// CGroup メッセージ ハンドラー


BOOL CGroup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	s_Name = "-";
	UDF;
	return TRUE; 
}

void CGroup::OnEnChangeEditName() { UDT; }

void CGroup::OnBnClickedOk()
{
	if (s_Name.IsEmpty()) {
		MessageBox("Group name is not found ... Please input or cancel", "Warning", MB_OK | MB_ICONASTERISK);
		return;
	}
	CDialogEx::OnOK();
}


