#pragma once


// CWebRRIPageBoundaryDlg ダイアログ

class CWebRRIPageBoundaryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageBoundaryDlg)

public:
	CWebRRIPageBoundaryDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageBoundaryDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_BOUNDARY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
