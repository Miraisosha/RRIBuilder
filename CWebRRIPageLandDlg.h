#pragma once


// CWebRRIPageLandDlg ダイアログ

class CWebRRIPageLandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageLandDlg)

public:
	CWebRRIPageLandDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageLandDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_LAND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
