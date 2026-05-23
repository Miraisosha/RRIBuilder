#pragma once


// CWebRRIPageGridDlg ダイアログ

class CWebRRIPageGridDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageGridDlg)

public:
	CWebRRIPageGridDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageGridDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_GRID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
