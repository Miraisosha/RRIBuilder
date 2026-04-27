#pragma once


// CMakeData ダイアログ

class CMakeData : public CDialogEx
{
	DECLARE_DYNAMIC(CMakeData)

public:
	CMakeData(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMakeData();

// ダイアログ データ
	enum { IDD = IDD_MAKEDATA };
//---------------------------------------------------------------------
//---------------------------------------------------------------------
	void		Display_State();
	void		Get_File_Name(int No);
	void		Make_File(int no);


//---------------------------------------------------------------------

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedButtonGo3();
	afx_msg void OnBnClickedButtonGo4();
	afx_msg void OnBnClickedButtonGo5();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString s_AccLimit;
	afx_msg void OnEnChangeEditRiv();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonCancel();
};
