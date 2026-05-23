#pragma once


// CWebRRIPageMapDlg ダイアログ

class CWebRRIPageMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIPageMapDlg)

public:
	CWebRRIPageMapDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CWebRRIPageMapDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_PAGE_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGridareaMap();
	afx_msg void OnBnClickedBtnElevationMap();
	afx_msg void OnBnClickedBtnDirectionMap();
	afx_msg void OnBnClickedBtnAccumulationMap();
	afx_msg void OnBnClickedBtnWidthMap();
	afx_msg void OnBnClickedBtnDepthMap();
	afx_msg void OnBnClickedBtnLeveeMap();
	afx_msg void OnBnClickedBtnSlopelengthMap();
	afx_msg void OnBnClickedBtnSlopeangleMap();
	afx_msg void OnBnClickedBtnSoildepthMap();
	afx_msg void OnBnClickedBtnAcquiferdepthMap();
	afx_msg void OnBnClickedBtnZrefMap();
	afx_msg void OnBnClickedBtnMetAltMap();
	afx_msg void OnBnClickedBtnLandMap();
	afx_msg void OnBnClickedBtnSoilmap();
	afx_msg void OnBnClickedBtnSoilCode();
	afx_msg void OnBnClickedBtnSoilTable();
	afx_msg void OnBnClickedBtnMetMap();
};
