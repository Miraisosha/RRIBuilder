#pragma once


// CSetProject ダイアログ


#include		"CommFuncs.h"
#include		"afxwin.h"


class CSetProject : public CDialogEx
{
	DECLARE_DYNAMIC(CSetProject)

public:
	CSetProject(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetProject();

// ダイアログ データ
	enum { IDD = IDD_SETPROJECT };
	// for CALLBACK
	static int AFXAPI BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	BOOL			Button_Dir(CString* m_ProjName, char* Path);
//
	CString		ProjDir;
	//
	BOOL		Set_DSET();
	void		Disp_Radio();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButtonProjFolder();
	CString s_ProjTitle;
	CString m_Comment;
//	CButton c_ProjDir;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditProjtitle();
	//CString s_MeshSize;
	virtual BOOL OnInitDialog();
	CComboBox c_ExCombo;
	afx_msg void OnCbnSelchangeComboExdata();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();	// 20190201 Add
	afx_msg void OnBnClickedRadio21();
	afx_msg void OnBnClickedRadio20();
	afx_msg void OnBnClickedButtonReadex();
	CButton c_EXDEM;
	CButton c_EXACC;
	CButton c_EXDIR;
	afx_msg void OnBnClickedButtonReadacc();
	afx_msg void OnBnClickedButtonReaddir();
};
