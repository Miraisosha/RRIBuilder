#pragma once


// CWebRRIPageDamDlg ダイアログ

class CWebRRIPageDamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageDamDlg)

public:
	CWebRRIPageDamDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageDamDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_DAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedBtnDamfile();
};
