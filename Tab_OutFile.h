#pragma once

#include "RRI_Common.h"

// CTab_OutFile ダイアログ

class CTab_OutFile : public CDialogEx
{
	DECLARE_DYNAMIC(CTab_OutFile)

public:
	CTab_OutFile(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTab_OutFile();
//-------------------------------------------------------------------
//-------------------------------------------------------------------
	int		Change_Nums;
	//
	void		Tab_Init();
	void		Disp_Data();

	void		Switch_File(int kind, int no);
	void		Search_Edit(int no);
	void		Get_FileName(int no);
//-------------------------------------------------------------------

// ダイアログ データ
	enum { IDD = IDD_TAB_OUTFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedOutlabel0();
	afx_msg void OnStnClickedOutlabel1();
	afx_msg void OnStnClickedOutlabel2();
	afx_msg void OnStnClickedOutlabel3();
	afx_msg void OnStnClickedOutlabel4();
	afx_msg void OnStnClickedOutlabel5();
	afx_msg void OnStnClickedOutlabel6();
	afx_msg void OnStnClickedOutlabel7();
	afx_msg void OnStnClickedOutlabel8();
	afx_msg void OnStnClickedOutlabel9();
	afx_msg void OnEnChangeEditHead0();
	afx_msg void OnEnChangeEditHead1();
	afx_msg void OnEnChangeEditHead2();
	afx_msg void OnEnChangeEditHead3();
	afx_msg void OnEnChangeEditHead4();
	afx_msg void OnEnChangeEditHead5();
	afx_msg void OnEnChangeEditHead6();
	afx_msg void OnEnChangeEditHead7();
	afx_msg void OnEnChangeEditHead8();
	afx_msg void OnEnChangeEditHead9();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
