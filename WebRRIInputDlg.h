#pragma once

#include <map>

#include "CWebRRIPageGeneralDlg.h"
#include "CWebRRIPageGridDlg.h"
#include "CWebRRIPageMapDlg.h"
#include "CWebRRIPageBoundaryDlg.h"
#include "CWebRRIPageOutputDlg.h"
#include "CWebRRIPageLandDlg.h"
#include "CWebRRIPageCalibrationDlg.h"
#include "CWebRRIPageDamDlg.h"

#define WM_WEBRRI_EVENT   (WM_USER + 100)
#define WEBRRI_EVT_SELECT_FOLDER   100
#define WEBRRI_EVT_SELECT_FILE     101

class CWebRRIInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebRRIInputDlg)

public:
	CWebRRIInputDlg(CWnd* pParent = nullptr);
	virtual ~CWebRRIInputDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBRRI_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

private:

	CTabCtrl m_tab;

	CWebRRIPageGeneralDlg     m_pageGeneral;
	CWebRRIPageGridDlg        m_pageGrid;
	CWebRRIPageMapDlg         m_pageMap;
	CWebRRIPageBoundaryDlg    m_pageBoundary;
	CWebRRIPageOutputDlg      m_pageOutput;
	CWebRRIPageLandDlg        m_pageLand;
	CWebRRIPageCalibrationDlg m_pageCalibration;
	CWebRRIPageDamDlg         m_pageDam;

	// parameter map
	std::map<CString, CString> m_values;

	// load template
	BOOL LoadTemplate(CString path);

	// helper
	CString GetValue(CString key);
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg LRESULT OnWebRRIEvent(WPARAM wParam, LPARAM lParam);
};
