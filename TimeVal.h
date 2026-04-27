#pragma once
#include "RRI_Common.h"
#include "afxwin.h"
//
// CTimeVal ダイアログ
#define			EDIT_TVNUM    20

///-----------------------------------------------------------------------------------------------------------
// Class  Members  表示 Common
///----------------------------------------------------------------------------------------------------------  
class CTimeVal : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeVal)

public:
	CTimeVal(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTimeVal();
	//
	int			Fid;
	int			stNo;
	CString		Title, Subttl;
	CString		SI_Name;
	BOOL			Decided;
	//
	int			Tnum, Tmem;			// Tnum VALが入力された分だけ
	int			MaxDay;
	int*			Tsec;
	double*		Tday;
	double*		Val;
	//
	int			Start,End;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void		Set_Data();
	void		Get_SelValue(int kind, int no);
	void		Get_Data();
	void		Research_Data();
	void		Time_Delete(int no); 

// ダイアログ データ
	enum { IDD = IDD_TIMEVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton c_BBack;
	CButton c_Import;
	CButton c_Daily;
	CButton c_BNext;
	CString s_Num;
	CString s_Subttl;
	CString s_Title;
	CString s_Mv;
	CString s_Mh;
	afx_msg void OnBnClickedButtonDaily();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedOk();
	CString s_Name;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnBnClickedButtonDelete1();
	afx_msg void OnBnClickedButtonDelete2();
	afx_msg void OnBnClickedButtonDelete3();
	afx_msg void OnBnClickedButtonDelete4();
	afx_msg void OnBnClickedButtonDelete5();
	afx_msg void OnBnClickedButtonDelete6();
	afx_msg void OnBnClickedButtonDelete7();
	afx_msg void OnBnClickedButtonDelete8();
	afx_msg void OnBnClickedButtonDelete9();
	afx_msg void OnBnClickedButtonDelete10();
	afx_msg void OnBnClickedButtonDelete11();
	afx_msg void OnBnClickedButtonDelete12();
	afx_msg void OnBnClickedButtonDelete13();
	afx_msg void OnBnClickedButtonDelete14();
	afx_msg void OnBnClickedButtonDelete15();
	afx_msg void OnBnClickedButtonDelete16();
	afx_msg void OnBnClickedButtonDelete17();
	afx_msg void OnBnClickedButtonDelete18();
	afx_msg void OnBnClickedButtonDelete19();
	afx_msg void OnBnClickedButtonDelete20();
};
