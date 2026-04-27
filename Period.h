#pragma once


// CPeriod ダイアログ

class CPeriod : public CDialogEx
{
	DECLARE_DYNAMIC(CPeriod)

public:
	CPeriod(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CPeriod();

// ダイアログ データ
	enum { IDD = IDD_PERIOD };
	//
	CTime	stTM, endTM;
	void		Get_Period();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit201();
	afx_msg void OnEnChangeEdit202();
	afx_msg void OnEnChangeEdit203();
	afx_msg void OnEnChangeEdit204();
	afx_msg void OnEnChangeEdit206();
	afx_msg void OnEnChangeEdit207();
	afx_msg void OnEnChangeEdit208();
	afx_msg void OnEnChangeEdit209();
	afx_msg void OnBnClickedOk();
};
