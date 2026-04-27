#pragma once


// CEditLocation ダイアログ

///______________________________________________________________________
#include   "RRI_Common.h"
#include "afxwin.h"


#define			EDIT_NUM    10


class CEditLocation : public CDialogEx
{
	DECLARE_DYNAMIC(CEditLocation)

public:
	CEditLocation(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CEditLocation();

// ダイアログ データ
	enum { IDD = IDD_EDITLOCATION };
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
	int			stNo;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
	void CEditLocation::Del_this(int id);
	void CEditLocation::Set_Data();
	void CEditLocation::Get_Name(int no);

////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
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
	afx_msg void OnBnClickedCancel();
};
