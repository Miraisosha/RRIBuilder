#pragma once


// CInitProj ダイアログ

//_______________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////
// COMMON_LIBRALY
//
class CInitProj : public CDialogEx
{
	DECLARE_DYNAMIC(CInitProj)

public:
	CInitProj(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CInitProj();

// ダイアログ データ
	enum { IDD = IDD_INITPROJ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};
