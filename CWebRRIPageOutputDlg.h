#pragma once


// CWebRRIPageOutputDlg ダイアログ

class CWebRRIPageOutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageOutputDlg)

public:
	CWebRRIPageOutputDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageOutputDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
};
