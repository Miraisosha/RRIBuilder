#pragma once
#include "afxwin.h"


// CRThiessen ダイアログ

class CRThiessen : public CDialogEx
{
	DECLARE_DYNAMIC(CRThiessen)

public:
	CRThiessen(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CRThiessen();

// ダイアログ データ
	enum { IDD = IDD_RTHIESSEN };
//--------------------------------------------------------------------
	CString		Dtitle;

	int			kind;	// 0: Rain  1:Evapo

	CString		Rfile, Rtemp,RainF, RainMap;
	double		lat, lng, unit;
	int			Hnum, Vnum;
	int			Return_Val;
//--------------------------------------------------------------------
	void			Set_Dlg();
	int			Make_Rain_Data();
//--------------------------------------------------------------------

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString s_ncol;
	CString s_nlow;
	CString s_size;
	CString s_xll;
	CString s_yll;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditXll();
	afx_msg void OnEnChangeEditNcol();
	afx_msg void OnEnChangeEditSize();
	afx_msg void OnEnChangeEditYll();
	afx_msg void OnEnChangeEditNlow();
	afx_msg void OnBnClickedButton1();
	CButton c_Button_1;
	//CButton c_Button_2;
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	CString m_Comment;
	CString s_MapName;
	CString m_Rainfile;
	CString s_Cell;
	afx_msg void OnStnClickedRainfile();
};
