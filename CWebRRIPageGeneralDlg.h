#pragma once


// CWebRRIPageGeneralDlg ダイアログ

class CWebRRIPageGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageGeneralDlg)

public:
	CWebRRIPageGeneralDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageGeneralDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_GENERAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedBtnParaDir();
	afx_msg void OnBnClickedBtnDataDir();
	afx_msg void OnBnClickedBtnResult1Dir();
	afx_msg void OnBnClickedBtnResult2Dir();
	afx_msg void OnBnClickedBtnSimulationDir();
	afx_msg void OnBnClickedBtnRecvDir();
};

