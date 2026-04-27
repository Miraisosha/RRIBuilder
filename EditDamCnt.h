#pragma once
#include   "RRI_Common.h"
#include "afxwin.h"

#define			EDIT_DAMNUM    10

// CEditDamCnt ダイアログ

class CEditDamCnt : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDamCnt)

public:
	CEditDamCnt(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CEditDamCnt();

// ダイアログ データ
	enum { IDD = IDD_EDITDAMCNT };
	//
	int			stNo;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	void		Del_this(int id);
	void		Set_Data();
	void		Get_Name(int no);
	void		Get_Value(int frame, int no);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDel1();
	afx_msg void OnBnClickedButtonDel2();
	afx_msg void OnBnClickedButtonDel3();
	afx_msg void OnBnClickedButtonDel4();
	afx_msg void OnBnClickedButtonDel5();
	afx_msg void OnBnClickedButtonDel6();
	afx_msg void OnBnClickedButtonDel7();
	afx_msg void OnBnClickedButtonDel8();
	afx_msg void OnBnClickedButtonDel9();
	afx_msg void OnBnClickedButtonDel10();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonNext();
	CButton c_BBack;
	CButton c_BNext;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditName1();
	afx_msg void OnEnChangeEditName2();
	afx_msg void OnEnChangeEditName3();
	afx_msg void OnEnChangeEditName4();
	afx_msg void OnEnChangeEditName5();
	afx_msg void OnEnChangeEditName6();
	afx_msg void OnEnChangeEditName7();
	afx_msg void OnEnChangeEditName8();
	afx_msg void OnEnChangeEditName9();
	afx_msg void OnEnChangeEditName10();
	afx_msg void OnEnChangeEditStrage1();
	afx_msg void OnEnChangeEditStrage2();
	afx_msg void OnEnChangeEditStrage3();
	afx_msg void OnEnChangeEditStrage4();
	afx_msg void OnEnChangeEditStrage5();
	afx_msg void OnEnChangeEditStrage6();
	afx_msg void OnEnChangeEditStrage7();
	afx_msg void OnEnChangeEditStrage8();
	afx_msg void OnEnChangeEditStrage9();
	afx_msg void OnEnChangeEditStrage10();
	afx_msg void OnEnChangeEditStartq1();
	afx_msg void OnEnChangeEditStartq2();
	afx_msg void OnEnChangeEditStartq3();
	afx_msg void OnEnChangeEditStartq4();
	afx_msg void OnEnChangeEditStartq5();
	afx_msg void OnEnChangeEditStartq6();
	afx_msg void OnEnChangeEditStartq7();
	afx_msg void OnEnChangeEditStartq8();
	afx_msg void OnEnChangeEditStartq9();
	afx_msg void OnEnChangeEditStartq10();
	virtual BOOL OnInitDialog();
};
