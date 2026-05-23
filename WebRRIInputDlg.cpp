#include "stdafx.h"
#include "RRI_GUI.h"
#include "WebRRIInputDlg.h"

#include "CWebRRIPageGeneralDlg.h"
#include "CWebRRIPageGridDlg.h"
#include "CWebRRIPageMapDlg.h"
#include "CWebRRIPageBoundaryDlg.h"
#include "CWebRRIPageOutputDlg.h"
#include "CWebRRIPageLandDlg.h"
#include "CWebRRIPageCalibrationDlg.h"
#include "CWebRRIPageDamDlg.h"

IMPLEMENT_DYNAMIC(CWebRRIInputDlg, CDialogEx)

CWebRRIInputDlg::CWebRRIInputDlg(CWnd* pParent)
	: CDialogEx(IDD_WEBRRI_INPUT_DIALOG, pParent)
{
}

CWebRRIInputDlg::~CWebRRIInputDlg()
{
}

void CWebRRIInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebRRIInputDlg, CDialogEx)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CWebRRIInputDlg::OnTcnSelchangeTabMain)

    ON_MESSAGE(WM_WEBRRI_EVENT,
        &CWebRRIInputDlg::OnWebRRIEvent)

END_MESSAGE_MAP()

BOOL CWebRRIInputDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // attach tab
    m_tab.SubclassDlgItem(IDC_TAB_MAIN, this);

    // tab add
    m_tab.InsertItem(0, _T("General"));
    m_tab.InsertItem(1, _T("Grid"));
    m_tab.InsertItem(2, _T("Map"));
    m_tab.InsertItem(3, _T("Boundary"));
    m_tab.InsertItem(4, _T("Output"));
    m_tab.InsertItem(5, _T("Land"));
    m_tab.InsertItem(6, _T("Calibration"));
    m_tab.InsertItem(7, _T("Dam"));

    // get area
    CRect rc;
    m_tab.GetClientRect(&rc);

    rc.top += 15;

    // create pages
    m_pageGeneral.Create(IDD_WEBRRI_PAGE_GENERAL, &m_tab);
    m_pageGrid.Create(IDD_WEBRRI_PAGE_GRID, &m_tab);
    m_pageMap.Create(IDD_WEBRRI_PAGE_MAP, &m_tab);
    m_pageBoundary.Create(IDD_WEBRRI_PAGE_BOUNDARY, &m_tab);
    m_pageOutput.Create(IDD_WEBRRI_PAGE_OUTPUT, &m_tab);
    m_pageLand.Create(IDD_WEBRRI_PAGE_LAND, &m_tab);
    m_pageCalibration.Create(IDD_WEBRRI_PAGE_CALIBRATION, &m_tab);
    m_pageDam.Create(IDD_WEBRRI_PAGE_DAM, &m_tab);

    // resize
    rc.DeflateRect(5, 5);
    m_pageGeneral.MoveWindow(&rc);
    m_pageGrid.MoveWindow(&rc);
    m_pageMap.MoveWindow(&rc);
    m_pageBoundary.MoveWindow(&rc);
    m_pageOutput.MoveWindow(&rc);
    m_pageLand.MoveWindow(&rc);
    m_pageCalibration.MoveWindow(&rc);
    m_pageDam.MoveWindow(&rc);

    // first page
    m_pageGeneral.ShowWindow(SW_SHOW);

    m_pageGrid.ShowWindow(SW_HIDE);
    m_pageMap.ShowWindow(SW_HIDE);
    m_pageBoundary.ShowWindow(SW_HIDE);
    m_pageOutput.ShowWindow(SW_HIDE);
    m_pageLand.ShowWindow(SW_HIDE);
    m_pageCalibration.ShowWindow(SW_HIDE);
    m_pageDam.ShowWindow(SW_HIDE);

    return TRUE;
}

void CWebRRIInputDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
    int sel = m_tab.GetCurSel();

    // hide all
    m_pageGeneral.ShowWindow(SW_HIDE);
    m_pageGrid.ShowWindow(SW_HIDE);
    m_pageMap.ShowWindow(SW_HIDE);
    m_pageBoundary.ShowWindow(SW_HIDE);
    m_pageOutput.ShowWindow(SW_HIDE);
    m_pageLand.ShowWindow(SW_HIDE);
    m_pageCalibration.ShowWindow(SW_HIDE);
    m_pageDam.ShowWindow(SW_HIDE);

    // show selected
    switch (sel)
    {
    case 0:
        m_pageGeneral.ShowWindow(SW_SHOW);
        break;

    case 1:
        m_pageGrid.ShowWindow(SW_SHOW);
        break;

    case 2:
        m_pageMap.ShowWindow(SW_SHOW);
        break;

    case 3:
        m_pageBoundary.ShowWindow(SW_SHOW);
        break;

    case 4:
        m_pageOutput.ShowWindow(SW_SHOW);
        break;

    case 5:
        m_pageLand.ShowWindow(SW_SHOW);
        break;

    case 6:
        m_pageCalibration.ShowWindow(SW_SHOW);
        break;

    case 7:
        m_pageDam.ShowWindow(SW_SHOW);
        break;
    }

    *pResult = 0;
}
LRESULT CWebRRIInputDlg::OnWebRRIEvent(
    WPARAM wParam,
    LPARAM lParam)
{
    UINT editId = (UINT)lParam;

    switch (wParam)
    {
		case WEBRRI_EVT_SELECT_FOLDER:
		{
			CFolderPickerDialog dlg;

			if (dlg.DoModal() == IDOK)
			{
				CString path = dlg.GetPathName();

				CWnd* pEdit =
					m_pageGeneral.GetDlgItem(editId);

				if (pEdit)
				{
					pEdit->SetWindowText(path);
				}
			}

			break;
		}
		case WEBRRI_EVT_SELECT_FILE:
		{
			CFileDialog dlg(
				TRUE,               // open
				NULL,
				NULL,
				OFN_FILEMUSTEXIST,
				_T("All Files (*.*)|*.*||"));

			if (dlg.DoModal() == IDOK)
			{
				CString path = dlg.GetPathName();
				CString fileName = dlg.GetFileName();

				CWnd* pEdit =
					m_pageGeneral.GetDlgItem(editId);

				if (pEdit)
				{
					pEdit->SetWindowText(fileName);
				}
			}

			break;
		}
    }

    return 0;
}
