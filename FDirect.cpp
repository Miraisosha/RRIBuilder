// FDirect.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "FDirect.h"
#include "afxdialogex.h"

#include "RRI_Common.h"

extern DATASET			DSET;
extern PARAMS				PM;							// 基本情報
extern   char				m_RecentPath[];
extern   char				m_BootPath[];

// CFDirect ダイアログ


IMPLEMENT_DYNAMIC(CFDirect, CDialogEx)

CFDirect::CFDirect(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFDirect::IDD, pParent)
	, LABEL_1(_T("Dem file"))
	, LABEL_2(_T("Dir file"))
	, LABEL_3(_T("Acc file"))
	, LABEL_4(_T("Riv txt"))
	, m_Comment(_T(""))
{

}

CFDirect::~CFDirect()
{
}

void CFDirect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LABEL_1, LABEL_1);
	DDX_Text(pDX, IDC_LABEL_2, LABEL_2);
	DDX_Text(pDX, IDC_LABEL_3, LABEL_3);
	DDX_Text(pDX, IDC_LABEL_4, LABEL_4);
	DDX_Control(pDX, IDC_BUTTON1, c_Button1);
	DDX_Control(pDX, IDC_BUTTON2, c_Button2);
	DDX_Control(pDX, IDC_BUTTON3, c_Button3);
	DDX_Control(pDX, IDC_BUTTON4, c_Button4);
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
}


BEGIN_MESSAGE_MAP(CFDirect, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFDirect::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFDirect::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFDirect::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFDirect::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CFDirect::OnBnClickedOk)
END_MESSAGE_MAP()


// CFDirect メッセージ ハンドラー


BOOL CFDirect::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	this->SetWindowTextA(Title);
	c_Button1.SetWindowTextA(DemF);
	c_Button2.SetWindowTextA(DirF);
	c_Button3.SetWindowTextA(AccF);
	//
	CWnd*	cw = GetDlgItem(IDC_LABEL_4);
	if (Proc == 1) {
		c_Button4.ShowWindow(SW_HIDE);
		cw->ShowWindow(SW_HIDE);
	}
	else {
		c_Button4.SetWindowTextA(RivF);
		cw->ShowWindow(SW_SHOW);
	}
//
	return TRUE; 
}


void CFDirect::OnBnClickedButton1()
{
	if (!Button_File(TRUE, &DemF, m_RecentPath, "Dem file", "txt")) return;
	//
	c_Button1.SetWindowTextA(DemF);
}


void CFDirect::OnBnClickedButton3()
{
	if (!Button_File(TRUE, &AccF, m_RecentPath, "Acc file", "txt")) return;
	//
	c_Button3.SetWindowTextA(AccF);
}


void CFDirect::OnBnClickedButton2()
{
	if (!Button_File(TRUE, &DirF, m_RecentPath, "Dir file", "txt")) return;
	//
	c_Button2.SetWindowTextA(DirF);
}


void CFDirect::OnBnClickedButton4()
{
	if (!Button_File(TRUE, &RivF, m_RecentPath, "Riv.txt", "txt")) return;
	//
	c_Button4.SetWindowTextA(RivF);
}


void CFDirect::OnBnClickedOk()
{
	CString	Fname,Dir;
	//
#ifdef  VER_64
	Fname.Format("%s/%s", m_BootPath, PROG_FLOW_DATA);
#else
	Fname.Format("%s/%s", m_BootPath, PROG_FLOW_DATA_32);
#endif

	FILE*	fp = fopen(Fname, "w");
	if (fp == NULL) {
		m_Comment = "* Error * Cannot Open FlowDirect.txt"; UDF; return;
	}
	//
	fprintf(fp, "%s\n", DemF);
	fprintf(fp, "%s\n", DirF);
	fprintf(fp, "%s\n", AccF);
	if (Proc == 1) 	fprintf(fp, "0\ndummy\n");
	else            fprintf(fp, "1\n%s\n", RivF);
	//
	fclose(fp);
	//---------------------------------------------
	Get_Dir(Fname,&Dir);
	::SetCurrentDirectory(Dir);
	int ret = system("FlowDirection.exe");
	// --------------------------------END
	//
	if (ret == 0)		CDialogEx::OnOK();
	else				CDialogEx::OnCancel();
}
