#pragma once
#include "afxwin.h"

#define		PROG_FLOW_PROG		"RRI_CONTENTS\\bin\\FlowDirection\\FlowDirection.exe"   //  ./なしに注意
#define		PROG_FLOW_DATA		"RRI_CONTENTS\\bin\\FlowDirection\\FlowDirection.txt"
#define		PROG_FLOW_PROG_32		"RRI_CONTENTS\\bin32\\FlowDirection\\FlowDirection.exe"   //  ./なしに注意
#define		PROG_FLOW_DATA_32		"RRI_CONTENTS\\bin32\\FlowDirection\\FlowDirection.txt"

// CFDirect ダイアログ

class CFDirect : public CDialogEx
{
	DECLARE_DYNAMIC(CFDirect)

public:
	CFDirect(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CFDirect();
	//
	int		Proc;
	CString	Title;
	CString	DemF;
	CString	AccF, DirF;
	CString	RivF;

// ダイアログ データ
	enum { IDD = IDD_FDIRECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString LABEL_1;
	CString LABEL_2;
	CString LABEL_3;
	CString LABEL_4;
	CButton c_Button1;
	CButton c_Button2;
	CButton c_Button3;
	CButton c_Button4;
	CString m_Comment;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
};
