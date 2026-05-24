//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
// INIT PROJECT
//
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "InitProj.h"
#include "afxdialogex.h"

#include "ProjectUtil.h"

extern  int		CREAT;

// CInitProj ダイアログ

IMPLEMENT_DYNAMIC(CInitProj, CDialogEx)

CInitProj::CInitProj(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitProj::IDD, pParent)
{

}

CInitProj::~CInitProj()
{
}

void CInitProj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInitProj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInitProj::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInitProj::OnBnClickedOk)
END_MESSAGE_MAP()


// CInitProj メッセージ ハンドラー


void CInitProj::OnBnClickedButton1()
{
	CREAT = CREATE_WEB_RRI_LOAD;
	CDialogEx::OnOK();
}


void CInitProj::OnBnClickedOk()
{
	CREAT = CREATE_WEB_RRI_NEW;
	CDialogEx::OnOK();
}
