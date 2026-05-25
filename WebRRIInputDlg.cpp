#include "stdafx.h"
#include "RRI_GUI.h"
#include "WebRRIInputDlg.h"
#include "Global.h"
#include "WebRRIInput.h"

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

    ON_BN_CLICKED(BTN_OK, &CWebRRIInputDlg::OnBnClickedOk)
    ON_BN_CLICKED(BTN_CANCEL, &CWebRRIInputDlg::OnBnClickedCancel)
    ON_BN_CLICKED(BTN_SAVE, &CWebRRIInputDlg::OnBnClickedSave)
    ON_BN_CLICKED(BTN_SAVE_AS, &CWebRRIInputDlg::OnBnClickedSaveAs)
END_MESSAGE_MAP()

BOOL CWebRRIInputDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ------------------------------------------------------
    // WEB_RRI_INPUT
	CWebRRIInputDlg dlg;
    dlg.m_input = g_WebRRIInput;

    // ------------------------------------------------------
    // TAB
    m_tab.SubclassDlgItem(IDC_TAB_MAIN, this);

    m_tab.InsertItem(0, _T("General"));
    m_tab.InsertItem(1, _T("Grid"));
    m_tab.InsertItem(2, _T("Map"));
    m_tab.InsertItem(3, _T("Boundary"));
    m_tab.InsertItem(4, _T("Output"));
    m_tab.InsertItem(5, _T("Land"));
    m_tab.InsertItem(6, _T("Calibration"));
    m_tab.InsertItem(7, _T("Dam"));

    CRect rc;
    m_tab.GetClientRect(&rc);
    rc.top += 15;
    m_pageGeneral.Create(IDD_WEBRRI_PAGE_GENERAL, &m_tab);
    m_pageGrid.Create(IDD_WEBRRI_PAGE_GRID, &m_tab);
    m_pageMap.Create(IDD_WEBRRI_PAGE_MAP, &m_tab);
    m_pageBoundary.Create(IDD_WEBRRI_PAGE_BOUNDARY, &m_tab);
    m_pageOutput.Create(IDD_WEBRRI_PAGE_OUTPUT, &m_tab);
    m_pageLand.Create(IDD_WEBRRI_PAGE_LAND, &m_tab);
    m_pageCalibration.Create(IDD_WEBRRI_PAGE_CALIBRATION, &m_tab);
    m_pageDam.Create(IDD_WEBRRI_PAGE_DAM, &m_tab);

    rc.DeflateRect(5, 5);
    m_pageGeneral.MoveWindow(&rc);
    m_pageGrid.MoveWindow(&rc);
    m_pageMap.MoveWindow(&rc);
    m_pageBoundary.MoveWindow(&rc);
    m_pageOutput.MoveWindow(&rc);
    m_pageLand.MoveWindow(&rc);
    m_pageCalibration.MoveWindow(&rc);
    m_pageDam.MoveWindow(&rc);

    m_pageGeneral.ShowWindow(SW_SHOW);
    m_pageGrid.ShowWindow(SW_HIDE);
    m_pageMap.ShowWindow(SW_HIDE);
    m_pageBoundary.ShowWindow(SW_HIDE);
    m_pageOutput.ShowWindow(SW_HIDE);
    m_pageLand.ShowWindow(SW_HIDE);
    m_pageCalibration.ShowWindow(SW_HIDE);
    m_pageDam.ShowWindow(SW_HIDE);


    // ------------------------------------------------------
    // ‰æ–Ê•\Ž¦
    LoadInputToScreen();

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


void CWebRRIInputDlg::OnBnClickedOk()
{
    SaveScreenToInput();
	CDialogEx::OnOK();
}


void CWebRRIInputDlg::OnBnClickedCancel()
{
    CDialogEx::OnCancel();
}


void CWebRRIInputDlg::OnBnClickedSave()
{
    SaveScreenToInput();

    // ‚Ü‚¾•Û‘¶æ‚ª‚È‚¢
    if (m_inputPath.IsEmpty())
    {
        OnBnClickedSaveAs();
        return;
    }

    if (!SaveWebRRIInput( m_inputPath, m_input))
    {
        AfxMessageBox(_T("Save failed"));
        return;
    }
    else {
		CDialogEx::OnOK();
    }
}


void CWebRRIInputDlg::OnBnClickedSaveAs()
{
    SaveScreenToInput();

    CFileDialog dlg(
        FALSE,
        _T("txt"),
        _T("input.txt"),
        OFN_OVERWRITEPROMPT,
        _T("Text Files (*.txt)|*.txt||"));

    if (dlg.DoModal() != IDOK)
    {
        return;
    }

    m_inputPath = dlg.GetPathName();

    if (!SaveWebRRIInput(
        m_inputPath,
        m_input))
    {
        AfxMessageBox(_T("Save failed"));
        return;
    }
    else {
		CDialogEx::OnOK();
    }
}

void CWebRRIInputDlg::LoadInputToScreen()
{
	// =====================================================
	// General - JOBNAME

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_RUNNAME,
		m_input.JOBNAME.runname);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_PARA_DIR,
		m_input.JOBNAME.para_dir);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_DATA_DIR,
		m_input.JOBNAME.data_dir);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_RESULT1_DIR,
		m_input.JOBNAME.result1_dir);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_RESULT2_DIR,
		m_input.JOBNAME.result2_dir);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_SIMULATION_DIR,
		m_input.JOBNAME.simulation_dir);

	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_RECV_DIR,
		m_input.JOBNAME.recv_dir);

	// =====================================================
	// General - MODEL_MODE

	((CButton*)m_pageGeneral.GetDlgItem(IDC_CHK_RRI))
		->SetCheck(m_input.MODEL_MODE.RRI);

	((CButton*)m_pageGeneral.GetDlgItem(IDC_CHK_MIXED))
		->SetCheck(m_input.MODEL_MODE.MIXED);

	// =====================================================
	// General - TIMESTEP

	SYSTEMTIME st = { 0 };

	_stscanf_s(
		m_input.TIMESTEP.initime,
		_T("%hu/%hu/%hu %hu:%hu"),
		&st.wYear,
		&st.wMonth,
		&st.wDay,
		&st.wHour,
		&st.wMinute);

	CWnd* p1 =
		m_pageGeneral.GetDlgItem(IDC_DPIC_INITIME);

	CWnd* p2 =
		m_pageGeneral.GetDlgItem(IDC_TPIC_INITIME);

	if (p1 == NULL)
	{
		AfxMessageBox(_T("DPIC NULL"));
	}

	if (p2 == NULL)
	{
		AfxMessageBox(_T("TPIC NULL"));
	}
	//	((CDateTimeCtrl*)m_pageGeneral.GetDlgItem(IDC_DPIC_INITIME))
	//		->SetTime(&st);
	//
	//	((CDateTimeCtrl*)m_pageGeneral.GetDlgItem(IDC_TPIC_INITIME))
	//		->SetTime(&st);

	CString str;

	str.Format(_T("%d"), m_input.TIMESTEP.tstart);
	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_TSTART,
		str);

	str.Format(_T("%d"), m_input.TIMESTEP.tstop);
	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_TSTOP,
		str);

	str.Format(_T("%d"), m_input.TIMESTEP.dt_couple);
	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_DT_COUPLE,
		str);

	str.Format(_T("%d"), m_input.TIMESTEP.dtlsm);
	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_DTLSM,
		str);

	str.Format(_T("%d"), m_input.TIMESTEP.dthydro);
	m_pageGeneral.SetDlgItemText(
		IDC_EDIT_DTHYDRO,
		str);

	((CComboBox*)m_pageGeneral.GetDlgItem(IDC_CMB_RECV_MODE))
		->SetCurSel(m_input.TIMESTEP.recv_mode);

	// =====================================================
	// Grid - POSITION

	str.Format(_T("%.6f"), m_input.POSITION.latsw);
	m_pageGrid.SetDlgItemText(IDC_EDIT_LATSW, str);

	str.Format(_T("%.6f"), m_input.POSITION.latne);
	m_pageGrid.SetDlgItemText(IDC_EDIT_LATNE, str);

	str.Format(_T("%.6f"), m_input.POSITION.lonsw);
	m_pageGrid.SetDlgItemText(IDC_EDIT_LONSW, str);

	str.Format(_T("%.6f"), m_input.POSITION.lonne);
	m_pageGrid.SetDlgItemText(IDC_EDIT_LONNE, str);

	str.Format(_T("%.6f"), m_input.POSITION.xsw);
	m_pageGrid.SetDlgItemText(IDC_EDIT_XSW, str);

	str.Format(_T("%.6f"), m_input.POSITION.xne);
	m_pageGrid.SetDlgItemText(IDC_EDIT_XNE, str);

	str.Format(_T("%.6f"), m_input.POSITION.ysw);
	m_pageGrid.SetDlgItemText(IDC_EDIT_YSW, str);

	str.Format(_T("%.6f"), m_input.POSITION.yne);
	m_pageGrid.SetDlgItemText(IDC_EDIT_YNE, str);

	// =====================================================
	// Grid - GRID

	str.Format(_T("%.6f"), m_input.GRID.dx);
	m_pageGrid.SetDlgItemText(IDC_EDIT_DX, str);

	str.Format(_T("%.6f"), m_input.GRID.dy);
	m_pageGrid.SetDlgItemText(IDC_EDIT_DY, str);

	str.Format(_T("%.6f"), m_input.GRID.dzroot);
	m_pageGrid.SetDlgItemText(IDC_EDIT_DZROOT, str);

	str.Format(_T("%.6f"), m_input.GRID.dzdeep);
	m_pageGrid.SetDlgItemText(IDC_EDIT_DZDEEP, str);

	// =====================================================
	// Map - MAPFILE

	m_pageMap.SetDlgItemText(
		IDC_EDIT_GRIDAREA_MAP,
		m_input.MAPFILE.gridarea_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_ELEVATION_MAP,
		m_input.MAPFILE.elevation_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_DIRECTION_MAP,
		m_input.MAPFILE.direction_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_ACCUMULATION_MAP,
		m_input.MAPFILE.accumulation_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_WIDTH_MAP,
		m_input.MAPFILE.width_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_DEPTH_MAP,
		m_input.MAPFILE.depth_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_LEVEE_MAP,
		m_input.MAPFILE.levee_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SLOPELENGTH_MAP,
		m_input.MAPFILE.slopelength_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SLOPEANGLE_MAP,
		m_input.MAPFILE.slopeangle_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SOILDEPTH_MAP,
		m_input.MAPFILE.soildepth_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_ACQUIFERDEPTH_MAP,
		m_input.MAPFILE.acquiferdepth_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_ZREF_MAP,
		m_input.MAPFILE.zref_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_MET_ALT_MAP,
		m_input.MAPFILE.met_alt_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_LAND_MAP,
		m_input.MAPFILE.land_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SOIL_MAP,
		m_input.MAPFILE.soil_map);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SOIL_CODE,
		m_input.MAPFILE.soil_code);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_SOIL_TABLE,
		m_input.MAPFILE.soil_table);

	m_pageMap.SetDlgItemText(
		IDC_EDIT_MET_MAP,
		m_input.MAPFILE.met_map);

	// =====================================================
	// Map - TOPOGRAPHY

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.ele0);
	m_pageMap.SetDlgItemText(IDC_EDIT_ELE0, str);

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.slope0);
	m_pageMap.SetDlgItemText(IDC_EDIT_SLOPE0, str);

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.length0);
	m_pageMap.SetDlgItemText(IDC_EDIT_LENGTH0, str);

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.Ds0);
	m_pageMap.SetDlgItemText(IDC_EDIT_DS0, str);

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.deldpth);
	m_pageMap.SetDlgItemText(IDC_EDIT_DELDPTH, str);

	str.Format(_T("%.6f"), m_input.TOPOGRAPHY.zwind0);
	m_pageMap.SetDlgItemText(IDC_EDIT_ZWIND0, str);

	// =====================================================
	// Boundary

	((CButton*)m_pageBoundary.GetDlgItem(IDC_CHK_IN_BOUND))
		->SetCheck(m_input.IN_BOUNDARY.IN_BOUND);

	m_pageBoundary.SetDlgItemText(
		IDC_EDIT_IN_FILE,
		m_input.IN_BOUNDARY.IN_FILE);

	str.Format(_T("%d"), m_input.IN_BOUNDARY.X_GRID);
	m_pageBoundary.SetDlgItemText(IDC_EDIT_X_GRID, str);

	str.Format(_T("%d"), m_input.IN_BOUNDARY.Y_GRID);
	m_pageBoundary.SetDlgItemText(IDC_EDIT_Y_GRID, str);

	// =====================================================
	// Output

	str.Format(_T("%d"), m_input.OUTPUT.OUT1_CODESTART);
	m_pageOutput.SetDlgItemText(IDC_EDIT_OUT1_CODESTART, str);

	str.Format(_T("%d"), m_input.OUTPUT.OUT1_CODEEND);
	m_pageOutput.SetDlgItemText(IDC_EDIT_OUT1_CODEEND, str);

	str.Format(_T("%d"), m_input.OUTPUT.OUT1_FLOWINT);
	m_pageOutput.SetDlgItemText(IDC_EDIT_OUT1_FLOWINT, str);

	// =====================================================
	// Land - INITSOIL

	str.Format(_T("%d"), m_input.INITSOIL.sfcdat);
	m_pageLand.SetDlgItemText(IDC_EDIT_SFCDAT, str);

	str.Format(_T("%d"), m_input.INITSOIL.vegfromtype);
	m_pageLand.SetDlgItemText(IDC_EDIT_VEGFROMTYPE, str);

	str.Format(_T("%d"), m_input.INITSOIL.styp);
	m_pageLand.SetDlgItemText(IDC_EDIT_STYP, str);

	str.Format(_T("%d"), m_input.INITSOIL.vtyp);
	m_pageLand.SetDlgItemText(IDC_EDIT_VTYP, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.lai0);
	m_pageLand.SetDlgItemText(IDC_EDIT_LAI0, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.veg0);
	m_pageLand.SetDlgItemText(IDC_EDIT_VEG0, str);

	str.Format(_T("%d"), m_input.INITSOIL.soilinit);
	m_pageLand.SetDlgItemText(IDC_EDIT_SOILINIT, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.tslnd0);
	m_pageLand.SetDlgItemText(IDC_EDIT_TSLND0, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.tscanp0);
	m_pageLand.SetDlgItemText(IDC_EDIT_TSCANP0, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.tswtr0);
	m_pageLand.SetDlgItemText(IDC_EDIT_TSWTR0, str);

	str.Format(_T("%.6f"), m_input.INITSOIL.tsoil0);
	m_pageLand.SetDlgItemText(IDC_EDIT_TSOIL0, str);

	// =====================================================
	// Land - LSMMODEL

	str.Format(_T("%d"), m_input.LSMMODEL.rstopt);
	m_pageLand.SetDlgItemText(IDC_EDIT_RSTOPT, str);

	// =====================================================
	// Calibration - MISC

	str.Format(_T("%.6f"), m_input.MISC.SSTMAX_CALIB);
	m_pageCalibration.SetDlgItemText(IDC_EDIT_SSTMAX_CALIB, str);

	str.Format(_T("%.6f"), m_input.MISC.KSAT1_CALIB);
	m_pageCalibration.SetDlgItemText(IDC_EDIT_KSAT1_CALIB, str);

	str.Format(_T("%.6f"), m_input.MISC.KSAT2_CALIB);
	m_pageCalibration.SetDlgItemText(IDC_EDIT_KSAT2_CALIB, str);

	// =====================================================
	// Calibration - INPUT

	((CButton*)m_pageCalibration.GetDlgItem(IDC_CHK_READ_REL_HUM))
		->SetCheck(m_input.INPUT.READ_REL_HUM);

	((CButton*)m_pageCalibration.GetDlgItem(IDC_CHK_UPD_PSFC))
		->SetCheck(m_input.INPUT.UPD_PSFC);

	((CButton*)m_pageCalibration.GetDlgItem(IDC_CHK_UPD_TAIR))
		->SetCheck(m_input.INPUT.UPD_TAIR);

	((CButton*)m_pageCalibration.GetDlgItem(IDC_CHK_READ_SEPARATE_U_V))
		->SetCheck(m_input.INPUT.READ_SEPARATE_U_V);

	m_pageCalibration.SetDlgItemText(
		IDC_EDIT_PREFIXES,
		m_input.INPUT.PREFIXES);

	m_pageCalibration.SetDlgItemText(
		IDC_EDIT_PREFIX_RAIN,
		m_input.INPUT.PREFIX_RAIN);

	((CComboBox*)m_pageCalibration.GetDlgItem(IDC_CMB_METEO_INPUT_TYPE))
		->SetCurSel(m_input.INPUT.METEO_INPUT_TYPE);

	((CComboBox*)m_pageCalibration.GetDlgItem(IDC_CMB_RAINFALL_INPUT_TYPE))
		->SetCurSel(m_input.INPUT.RAINFALL_INPUT_TYPE);

	((CButton*)m_pageCalibration.GetDlgItem(IDC_CHK_MONTHLY_LAIFPAR))
		->SetCheck(m_input.INPUT.MONTHLY_LAIFPAR);

	// =====================================================
	// Dam

	((CComboBox*)m_pageDam.GetDlgItem(IDC_CMB_DAM_SWITCH))
		->SetCurSel(m_input.DAM_CONTROL.dam_switch);

	m_pageDam.SetDlgItemText(
		IDC_EDIT_DAMFILE,
		m_input.DAM_CONTROL.damfile);
}


void CWebRRIInputDlg::SaveScreenToInput()
{
    CString str;

    // =====================================================
    // General - JOBNAME

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_RUNNAME,
        m_input.JOBNAME.runname);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_PARA_DIR,
        m_input.JOBNAME.para_dir);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_DATA_DIR,
        m_input.JOBNAME.data_dir);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_RESULT1_DIR,
        m_input.JOBNAME.result1_dir);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_RESULT2_DIR,
        m_input.JOBNAME.result2_dir);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_SIMULATION_DIR,
        m_input.JOBNAME.simulation_dir);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_RECV_DIR,
        m_input.JOBNAME.recv_dir);

    // =====================================================
    // General - MODEL_MODE

    m_input.MODEL_MODE.RRI =
        ((CButton*)m_pageGeneral.GetDlgItem(IDC_CHK_RRI))
        ->GetCheck();

    m_input.MODEL_MODE.MIXED =
        ((CButton*)m_pageGeneral.GetDlgItem(IDC_CHK_MIXED))
        ->GetCheck();

    // =====================================================
    // General - TIMESTEP

    CDateTimeCtrl* pDate =
        (CDateTimeCtrl*)m_pageGeneral.GetDlgItem(IDC_DPIC_INITIME);

    CDateTimeCtrl* pTime =
        (CDateTimeCtrl*)m_pageGeneral.GetDlgItem(IDC_TPIC_INITIME);

    if (pDate && pTime)
    {
        SYSTEMTIME stDate = { 0 };
        SYSTEMTIME stTime = { 0 };

        pDate->GetTime(&stDate);
        pTime->GetTime(&stTime);

        str.Format(
            _T("%04d/%02d/%02d %02d:%02d"),
            stDate.wYear,
            stDate.wMonth,
            stDate.wDay,
            stTime.wHour,
            stTime.wMinute);

        m_input.TIMESTEP.initime = str;
    }

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_TSTART,
        str);
    m_input.TIMESTEP.tstart = _ttoi(str);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_TSTOP,
        str);
    m_input.TIMESTEP.tstop = _ttoi(str);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_DT_COUPLE,
        str);
    m_input.TIMESTEP.dt_couple = _ttoi(str);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_DTLSM,
        str);
    m_input.TIMESTEP.dtlsm = _ttoi(str);

    m_pageGeneral.GetDlgItemText(
        IDC_EDIT_DTHYDRO,
        str);
    m_input.TIMESTEP.dthydro = _ttoi(str);

    m_input.TIMESTEP.recv_mode =
        ((CComboBox*)m_pageGeneral.GetDlgItem(IDC_CMB_RECV_MODE))
        ->GetCurSel();

    // =====================================================
    // Grid - POSITION

    m_pageGrid.GetDlgItemText(IDC_EDIT_LATSW, str);
    m_input.POSITION.latsw = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_LATNE, str);
    m_input.POSITION.latne = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_LONSW, str);
    m_input.POSITION.lonsw = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_LONNE, str);
    m_input.POSITION.lonne = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_XSW, str);
    m_input.POSITION.xsw = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_XNE, str);
    m_input.POSITION.xne = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_YSW, str);
    m_input.POSITION.ysw = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_YNE, str);
    m_input.POSITION.yne = _ttof(str);

    // =====================================================
    // Grid - GRID

    m_pageGrid.GetDlgItemText(IDC_EDIT_DX, str);
    m_input.GRID.dx = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_DY, str);
    m_input.GRID.dy = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_DZROOT, str);
    m_input.GRID.dzroot = _ttof(str);

    m_pageGrid.GetDlgItemText(IDC_EDIT_DZDEEP, str);
    m_input.GRID.dzdeep = _ttof(str);

    // =====================================================
    // Map - MAPFILE

    m_pageMap.GetDlgItemText(
        IDC_EDIT_GRIDAREA_MAP,
        m_input.MAPFILE.gridarea_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_ELEVATION_MAP,
        m_input.MAPFILE.elevation_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_DIRECTION_MAP,
        m_input.MAPFILE.direction_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_ACCUMULATION_MAP,
        m_input.MAPFILE.accumulation_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_WIDTH_MAP,
        m_input.MAPFILE.width_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_DEPTH_MAP,
        m_input.MAPFILE.depth_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_LEVEE_MAP,
        m_input.MAPFILE.levee_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SLOPELENGTH_MAP,
        m_input.MAPFILE.slopelength_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SLOPEANGLE_MAP,
        m_input.MAPFILE.slopeangle_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SOILDEPTH_MAP,
        m_input.MAPFILE.soildepth_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_ACQUIFERDEPTH_MAP,
        m_input.MAPFILE.acquiferdepth_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_ZREF_MAP,
        m_input.MAPFILE.zref_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_MET_ALT_MAP,
        m_input.MAPFILE.met_alt_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_LAND_MAP,
        m_input.MAPFILE.land_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SOIL_MAP,
        m_input.MAPFILE.soil_map);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SOIL_CODE,
        m_input.MAPFILE.soil_code);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_SOIL_TABLE,
        m_input.MAPFILE.soil_table);

    m_pageMap.GetDlgItemText(
        IDC_EDIT_MET_MAP,
        m_input.MAPFILE.met_map);

    // =====================================================
    // Map - TOPOGRAPHY

    m_pageMap.GetDlgItemText(IDC_EDIT_ELE0, str);
    m_input.TOPOGRAPHY.ele0 = _ttof(str);

    m_pageMap.GetDlgItemText(IDC_EDIT_SLOPE0, str);
    m_input.TOPOGRAPHY.slope0 = _ttof(str);

    m_pageMap.GetDlgItemText(IDC_EDIT_LENGTH0, str);
    m_input.TOPOGRAPHY.length0 = _ttof(str);

    m_pageMap.GetDlgItemText(IDC_EDIT_DS0, str);
    m_input.TOPOGRAPHY.Ds0 = _ttof(str);

    m_pageMap.GetDlgItemText(IDC_EDIT_DELDPTH, str);
    m_input.TOPOGRAPHY.deldpth = _ttof(str);

    m_pageMap.GetDlgItemText(IDC_EDIT_ZWIND0, str);
    m_input.TOPOGRAPHY.zwind0 = _ttof(str);

    // =====================================================
    // Boundary

    m_input.IN_BOUNDARY.IN_BOUND =
        ((CButton*)m_pageBoundary.GetDlgItem(IDC_CHK_IN_BOUND))
        ->GetCheck();

    m_pageBoundary.GetDlgItemText(
        IDC_EDIT_IN_FILE,
        m_input.IN_BOUNDARY.IN_FILE);

    m_pageBoundary.GetDlgItemText(IDC_EDIT_X_GRID, str);
    m_input.IN_BOUNDARY.X_GRID = _ttoi(str);

    m_pageBoundary.GetDlgItemText(IDC_EDIT_Y_GRID, str);
    m_input.IN_BOUNDARY.Y_GRID = _ttoi(str);

    // =====================================================
    // Output

    m_pageOutput.GetDlgItemText(IDC_EDIT_OUT1_CODESTART, str);
    m_input.OUTPUT.OUT1_CODESTART = _ttoi(str);

    m_pageOutput.GetDlgItemText(IDC_EDIT_OUT1_CODEEND, str);
    m_input.OUTPUT.OUT1_CODEEND = _ttoi(str);

    m_pageOutput.GetDlgItemText(IDC_EDIT_OUT1_FLOWINT, str);
    m_input.OUTPUT.OUT1_FLOWINT = _ttoi(str);

    // =====================================================
    // Land - INITSOIL

    m_pageLand.GetDlgItemText(IDC_EDIT_SFCDAT, str);
    m_input.INITSOIL.sfcdat = _ttoi(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_VEGFROMTYPE, str);
    m_input.INITSOIL.vegfromtype = _ttoi(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_STYP, str);
    m_input.INITSOIL.styp = _ttoi(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_VTYP, str);
    m_input.INITSOIL.vtyp = _ttoi(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_LAI0, str);
    m_input.INITSOIL.lai0 = _ttof(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_VEG0, str);
    m_input.INITSOIL.veg0 = _ttof(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_SOILINIT, str);
    m_input.INITSOIL.soilinit = _ttoi(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_TSLND0, str);
    m_input.INITSOIL.tslnd0 = _ttof(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_TSCANP0, str);
    m_input.INITSOIL.tscanp0 = _ttof(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_TSWTR0, str);
    m_input.INITSOIL.tswtr0 = _ttof(str);

    m_pageLand.GetDlgItemText(IDC_EDIT_TSOIL0, str);
    m_input.INITSOIL.tsoil0 = _ttof(str);

    // =====================================================
    // Land - LSMMODEL

    m_pageLand.GetDlgItemText(IDC_EDIT_RSTOPT, str);
    m_input.LSMMODEL.rstopt = _ttoi(str);

    // =====================================================
    // Dam

    m_input.DAM_CONTROL.dam_switch =
        ((CComboBox*)m_pageDam.GetDlgItem(IDC_CMB_DAM_SWITCH))
        ->GetCurSel();

    m_pageDam.GetDlgItemText(
        IDC_EDIT_DAMFILE,
        m_input.DAM_CONTROL.damfile);
}

#include "stdafx.h"
#include "WebRRIInput.h"

// =====================================================
// helper
// =====================================================

static CString ToFortranBool(BOOL value)
{
    return value
        ? _T(".true.")
        : _T(".false.");
}

static CString QuoteString(const CString& value)
{
    CString str;

    str.Format(
        _T("'%s'"),
        value);

    return str;
}

// =====================================================
// Save
// =====================================================

BOOL SaveWebRRIInput(
    const CString& path,
    const WEB_RRI_INPUT& input)
{
    CStdioFile file;

    if (!file.Open(
        path,
        CFile::modeCreate |
        CFile::modeWrite |
        CFile::typeText))
    {
        return FALSE;
    }

    CString line;

    // =====================================================
    // JOBNAME

    file.WriteString(_T("&JOBNAME\n"));

    line.Format(_T("      runname = %s\n"),
        QuoteString(input.JOBNAME.runname));
    file.WriteString(line);

    line.Format(_T("      para_dir = %s\n"),
        QuoteString(input.JOBNAME.para_dir));
    file.WriteString(line);

    line.Format(_T("      data_dir = %s\n"),
        QuoteString(input.JOBNAME.data_dir));
    file.WriteString(line);

    line.Format(_T("      result1_dir = %s\n"),
        QuoteString(input.JOBNAME.result1_dir));
    file.WriteString(line);

    line.Format(_T("      result2_dir = %s\n"),
        QuoteString(input.JOBNAME.result2_dir));
    file.WriteString(line);

    line.Format(_T("      simulation_dir = %s\n"),
        QuoteString(input.JOBNAME.simulation_dir));
    file.WriteString(line);

    line.Format(_T("      recv_dir = %s\n"),
        QuoteString(input.JOBNAME.recv_dir));
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // MODEL_MODE

    file.WriteString(_T("&MODEL_MODE\n"));

    line.Format(_T("      RRI = %s\n"),
        ToFortranBool(input.MODEL_MODE.RRI));
    file.WriteString(line);

    line.Format(_T("      MIXED = %s\n"),
        ToFortranBool(input.MODEL_MODE.MIXED));
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // IN_BOUNDARY

    file.WriteString(_T("&IN_BOUNDARY\n"));

    line.Format(_T("      IN_BOUND = %s\n"),
        ToFortranBool(input.IN_BOUNDARY.IN_BOUND));
    file.WriteString(line);

    line.Format(_T("      IN_FILE = %s\n"),
        QuoteString(input.IN_BOUNDARY.IN_FILE));
    file.WriteString(line);

    line.Format(_T("      X_GRID = %d\n"),
        input.IN_BOUNDARY.X_GRID);
    file.WriteString(line);

    line.Format(_T("      Y_GRID = %d\n"),
        input.IN_BOUNDARY.Y_GRID);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // TIMESTEP

    file.WriteString(_T("&TIMESTEP\n"));

    line.Format(_T("      initime = %s\n"),
        QuoteString(input.TIMESTEP.initime));
    file.WriteString(line);

    line.Format(_T("      tstart = %d\n"),
        input.TIMESTEP.tstart);
    file.WriteString(line);

    line.Format(_T("      tstop = %d\n"),
        input.TIMESTEP.tstop);
    file.WriteString(line);

    line.Format(_T("      dt_couple = %d\n"),
        input.TIMESTEP.dt_couple);
    file.WriteString(line);

    line.Format(_T("      dtlsm = %d\n"),
        input.TIMESTEP.dtlsm);
    file.WriteString(line);

    line.Format(_T("      dthydro = %d\n"),
        input.TIMESTEP.dthydro);
    file.WriteString(line);

    line.Format(_T("      recv_mode = %d\n"),
        input.TIMESTEP.recv_mode);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // POSITION

    file.WriteString(_T("&POSITION\n"));

    line.Format(_T("      latsw = %.15f\n"),
        input.POSITION.latsw);
    file.WriteString(line);

    line.Format(_T("      latne = %.15f\n"),
        input.POSITION.latne);
    file.WriteString(line);

    line.Format(_T("      lonsw = %.15f\n"),
        input.POSITION.lonsw);
    file.WriteString(line);

    line.Format(_T("      lonne = %.15f\n"),
        input.POSITION.lonne);
    file.WriteString(line);

    line.Format(_T("      xsw = %.15f\n"),
        input.POSITION.xsw);
    file.WriteString(line);

    line.Format(_T("      xne = %.15f\n"),
        input.POSITION.xne);
    file.WriteString(line);

    line.Format(_T("      ysw = %.15f\n"),
        input.POSITION.ysw);
    file.WriteString(line);

    line.Format(_T("      yne = %.15f\n"),
        input.POSITION.yne);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // GRID

    file.WriteString(_T("&GRID\n"));

    line.Format(_T("      dx = %.6f\n"),
        input.GRID.dx);
    file.WriteString(line);

    line.Format(_T("      dy = %.6f\n"),
        input.GRID.dy);
    file.WriteString(line);

    line.Format(_T("      dzroot = %.6f\n"),
        input.GRID.dzroot);
    file.WriteString(line);

    line.Format(_T("      dzdeep = %.6f\n"),
        input.GRID.dzdeep);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // MAPFILE

    file.WriteString(_T("&MAPFILE\n"));

    line.Format(_T("      gridarea_map = %s\n"),
        QuoteString(input.MAPFILE.gridarea_map));
    file.WriteString(line);

    line.Format(_T("      elevation_map = %s\n"),
        QuoteString(input.MAPFILE.elevation_map));
    file.WriteString(line);

    line.Format(_T("      direction_map = %s\n"),
        QuoteString(input.MAPFILE.direction_map));
    file.WriteString(line);

    line.Format(_T("      accumulation_map = %s\n"),
        QuoteString(input.MAPFILE.accumulation_map));
    file.WriteString(line);

    line.Format(_T("      width_map = %s\n"),
        QuoteString(input.MAPFILE.width_map));
    file.WriteString(line);

    line.Format(_T("      depth_map = %s\n"),
        QuoteString(input.MAPFILE.depth_map));
    file.WriteString(line);

    line.Format(_T("      levee_map = %s\n"),
        QuoteString(input.MAPFILE.levee_map));
    file.WriteString(line);

    line.Format(_T("      slopelength_map = %s\n"),
        QuoteString(input.MAPFILE.slopelength_map));
    file.WriteString(line);

    line.Format(_T("      slopeangle_map = %s\n"),
        QuoteString(input.MAPFILE.slopeangle_map));
    file.WriteString(line);

    line.Format(_T("      soildepth_map = %s\n"),
        QuoteString(input.MAPFILE.soildepth_map));
    file.WriteString(line);

    line.Format(_T("      acquiferdepth_map = %s\n"),
        QuoteString(input.MAPFILE.acquiferdepth_map));
    file.WriteString(line);

    line.Format(_T("      zref_map = %s\n"),
        QuoteString(input.MAPFILE.zref_map));
    file.WriteString(line);

    line.Format(_T("      met_alt_map = %s\n"),
        QuoteString(input.MAPFILE.met_alt_map));
    file.WriteString(line);

    line.Format(_T("      land_map = %s\n"),
        QuoteString(input.MAPFILE.land_map));
    file.WriteString(line);

    line.Format(_T("      soil_map = %s\n"),
        QuoteString(input.MAPFILE.soil_map));
    file.WriteString(line);

    line.Format(_T("      soil_code = %s\n"),
        QuoteString(input.MAPFILE.soil_code));
    file.WriteString(line);

    line.Format(_T("      soil_table = %s\n"),
        QuoteString(input.MAPFILE.soil_table));
    file.WriteString(line);

    line.Format(_T("      met_map = %s\n"),
        QuoteString(input.MAPFILE.met_map));
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // TOPOGRAPHY

    file.WriteString(_T("&TOPOGRAPHY\n"));

    line.Format(_T("      ele0 = %.6f\n"),
        input.TOPOGRAPHY.ele0);
    file.WriteString(line);

    line.Format(_T("      slope0 = %.6f\n"),
        input.TOPOGRAPHY.slope0);
    file.WriteString(line);

    line.Format(_T("      length0 = %.6f\n"),
        input.TOPOGRAPHY.length0);
    file.WriteString(line);

    line.Format(_T("      Ds0 = %.6f\n"),
        input.TOPOGRAPHY.Ds0);
    file.WriteString(line);

    line.Format(_T("      deldpth = %.6f\n"),
        input.TOPOGRAPHY.deldpth);
    file.WriteString(line);

    line.Format(_T("      zwind0 = %.6f\n"),
        input.TOPOGRAPHY.zwind0);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // INITSOIL

    file.WriteString(_T("&INITSOIL\n"));

    line.Format(_T("      sfcdat = %d\n"),
        input.INITSOIL.sfcdat);
    file.WriteString(line);

    line.Format(_T("      vegfromtype = %d\n"),
        input.INITSOIL.vegfromtype);
    file.WriteString(line);

    line.Format(_T("      styp = %d\n"),
        input.INITSOIL.styp);
    file.WriteString(line);

    line.Format(_T("      vtyp = %d\n"),
        input.INITSOIL.vtyp);
    file.WriteString(line);

    line.Format(_T("      lai0 = %.6f\n"),
        input.INITSOIL.lai0);
    file.WriteString(line);

    line.Format(_T("      veg0 = %.6f\n"),
        input.INITSOIL.veg0);
    file.WriteString(line);

    line.Format(_T("      soilinit = %d\n"),
        input.INITSOIL.soilinit);
    file.WriteString(line);

    line.Format(_T("      tslnd0 = %.6f\n"),
        input.INITSOIL.tslnd0);
    file.WriteString(line);

    line.Format(_T("      tscanp0 = %.6f\n"),
        input.INITSOIL.tscanp0);
    file.WriteString(line);

    line.Format(_T("      tswtr0 = %.6f\n"),
        input.INITSOIL.tswtr0);
    file.WriteString(line);

    line.Format(_T("      tsoil0 = %.6f\n"),
        input.INITSOIL.tsoil0);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // LSMMODEL

    file.WriteString(_T("&LSMMODEL\n"));

    line.Format(_T("      rstopt = %d\n"),
        input.LSMMODEL.rstopt);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // MISC

    file.WriteString(_T("&MISC\n"));

    line.Format(_T("      SSTMAX_CALIB = %.6f\n"),
        input.MISC.SSTMAX_CALIB);
    file.WriteString(line);

    line.Format(_T("      KSAT1_CALIB = %.6f\n"),
        input.MISC.KSAT1_CALIB);
    file.WriteString(line);

    line.Format(_T("      KSAT2_CALIB = %.6f\n"),
        input.MISC.KSAT2_CALIB);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // INPUT

    file.WriteString(_T("&INPUT\n"));

    line.Format(_T("      READ_REL_HUM = %s\n"),
        ToFortranBool(input.INPUT.READ_REL_HUM));
    file.WriteString(line);

    line.Format(_T("      UPD_PSFC = %s\n"),
        ToFortranBool(input.INPUT.UPD_PSFC));
    file.WriteString(line);

    line.Format(_T("      UPD_TAIR = %s\n"),
        ToFortranBool(input.INPUT.UPD_TAIR));
    file.WriteString(line);

    line.Format(_T("      READ_SEPARATE_U_V = %s\n"),
        ToFortranBool(input.INPUT.READ_SEPARATE_U_V));
    file.WriteString(line);

    line.Format(_T("      PREFIXES = %s\n"),
        QuoteString(input.INPUT.PREFIXES));
    file.WriteString(line);

    line.Format(_T("      PREFIX_RAIN = %s\n"),
        QuoteString(input.INPUT.PREFIX_RAIN));
    file.WriteString(line);

    line.Format(_T("      METEO_INPUT_TYPE = %d\n"),
        input.INPUT.METEO_INPUT_TYPE);
    file.WriteString(line);

    line.Format(_T("      RAINFALL_INPUT_TYPE = %d\n"),
        input.INPUT.RAINFALL_INPUT_TYPE);
    file.WriteString(line);

    line.Format(_T("      MONTHLY_LAIFPAR = %s\n"),
        ToFortranBool(input.INPUT.MONTHLY_LAIFPAR));
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // OUTPUT

    file.WriteString(_T("&OUTPUT\n"));

    line.Format(_T("      OUT1_CODESTART = %d\n"),
        input.OUTPUT.OUT1_CODESTART);
    file.WriteString(line);

    line.Format(_T("      OUT1_CODEEND = %d\n"),
        input.OUTPUT.OUT1_CODEEND);
    file.WriteString(line);

    line.Format(_T("      OUT1_FLOWINT = %d\n"),
        input.OUTPUT.OUT1_FLOWINT);
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    // =====================================================
    // DAM_CONTROL

    file.WriteString(_T("&dam_control\n"));

    line.Format(_T("      dam_switch = %d\n"),
        input.DAM_CONTROL.dam_switch);
    file.WriteString(line);

    line.Format(_T("      damfile = %s\n"),
        QuoteString(input.DAM_CONTROL.damfile));
    file.WriteString(line);

    file.WriteString(_T("/\n\n"));

    file.Close();

    return TRUE;
}
