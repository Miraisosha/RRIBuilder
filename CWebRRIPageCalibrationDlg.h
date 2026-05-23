#pragma once


// CWebRRIPageCalibrationDlg ダイアログ

class CWebRRIPageCalibrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageCalibrationDlg)

public:
	CWebRRIPageCalibrationDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageCalibrationDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
};
