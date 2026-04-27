#pragma once


////______________________________________________________________________
#include   "RRI_Common.h"
#include "afxwin.h"

#define			EDIT_NUM    10

class CEditDivide : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDivide)

public:
	CEditDivide(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CEditDivide();

// ダイアログ データ
	enum { IDD = IDD_EDITDIVIDE };
	int			stNo;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	void		Del_this(int id);
	void		Set_Data();
	void		Get_Value(int no);
	void		Exchange(int no);

	////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDel7();
	afx_msg void OnBnClickedButtonDel8();
	afx_msg void OnBnClickedButtonDel9();
	afx_msg void OnBnClickedButtonDel10();
	afx_msg void OnBnClickedButtonDel11();
	afx_msg void OnBnClickedButtonDel12();
	afx_msg void OnBnClickedButtonDel13();
	afx_msg void OnBnClickedButtonDel14();
	afx_msg void OnBnClickedButtonDel15();
	afx_msg void OnBnClickedButtonDel16();
	afx_msg void OnBnClickedButtonBack2();
	afx_msg void OnBnClickedButtonNext2();
	CButton c_BBack;
	CButton c_BNext;
	afx_msg void OnEnChangeEditRate1();
	afx_msg void OnEnChangeEditRate2();
	afx_msg void OnEnChangeEditRate3();
	afx_msg void OnEnChangeEditRate4();
	afx_msg void OnEnChangeEditRate5();
	afx_msg void OnEnChangeEditRate6();
	afx_msg void OnEnChangeEditRate7();
	afx_msg void OnEnChangeEditRate8();
	afx_msg void OnEnChangeEditRate9();
	afx_msg void OnEnChangeEditRate10();
	afx_msg void OnBnClickedButtonExchange1();
	afx_msg void OnBnClickedButtonExchange2();
	afx_msg void OnBnClickedButtonExchange3();
	afx_msg void OnBnClickedButtonExchange4();
	afx_msg void OnBnClickedButtonExchange5();
	afx_msg void OnBnClickedButtonExchange6();
	afx_msg void OnBnClickedButtonExchange7();
	afx_msg void OnBnClickedButtonExchange8();
	afx_msg void OnBnClickedButtonExchange9();
	afx_msg void OnBnClickedButtonExchange10();
	afx_msg void OnBnClickedOk();
};
