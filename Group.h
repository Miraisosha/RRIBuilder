#pragma once


// CGroup ダイアログ

class CGroup : public CDialogEx
{
	DECLARE_DYNAMIC(CGroup)

public:
	CGroup(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CGroup();

// ダイアログ データ
	enum { IDD = IDD_GROUP };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString s_Name;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditName();
};
