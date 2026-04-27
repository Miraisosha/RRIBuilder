// DataColorSed.cpp : 実装ファイル
//
#include <sstream>
#include "stdafx.h"
#include "RRI_GUI.h"
#include "DataColorSed.h"
#include "afxdialogex.h"


int		CDataColorSed::ms_MaxRange = 10;
int		CDataColorSed::ms_CDataId = SED_FILE;
int		CDataColorSed::ms_SED_COL_IDS[MaxColorCount] = {
	IDC_COL_1, IDC_COL_2, IDC_COL_3, IDC_COL_4, IDC_COL_5,
	IDC_COL_6, IDC_COL_7, IDC_COL_8, IDC_COL_9, IDC_COL_10,
	IDC_COL_11, IDC_COL_12, IDC_COL_13, IDC_COL_14, IDC_COL_15,
	IDC_COL_16, IDC_COL_17, IDC_COL_18, IDC_COL_19, IDC_COL_20
};
CColWin CDataColorSed::ms_cww[MaxColorCount] = {};

// CDataColorSed ダイアログ
IMPLEMENT_DYNAMIC(CDataColorSed, CDialog)

CDataColorSed::CDataColorSed(const std::string& bootPath, PARAMS* params, CWnd* pParent /*=nullptr*/) 
	: CDialog(IDD_DATACOLOR_SED, pParent),
	m_bootPath(bootPath), m_params(params)
{
	m_sedColObj = &m_params->Dcol[ms_CDataId];

	memset(&m_cv, 0, sizeof(COLVAL_FIX));
	m_cv.num = m_sedColObj->num;
	m_cv.Equal = m_sedColObj->Equal;
	m_cv.alpha = m_sedColObj->alpha;
	m_cv.Mos = m_sedColObj->Mos;

	for (int i = 0;i < m_cv.num;i++) {
		m_cv.val[i] = m_sedColObj->val[i];
		ms_cww[i].colground = m_cv.Rcol[i] = m_sedColObj->Rcol[i];
		Copy_FCOLOR(&m_cv.Fcol[i], m_sedColObj->Fcol[i]);
	}

	for (int i = m_cv.num; i < MaxColorCount; i++) {
		m_cv.val[i] = DUNDEF;
		ms_cww[i].colground = RGB(100, 100, 100);
	}
}

CDataColorSed::~CDataColorSed()
{
	if (m_params) m_params = nullptr;
	if (m_sedColObj) m_sedColObj = nullptr;
}

void CDataColorSed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_ALPHA, m_ctrlAlpha);
}

BEGIN_MESSAGE_MAP(CDataColorSed, CDialog)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALPHA, &CDataColorSed::OnNMCustomdrawSliderAlpha)
	ON_BN_CLICKED(IDC_APPLY, &CDataColorSed::OnBnClickedApply)
	ON_BN_CLICKED(IDC_SAVE, &CDataColorSed::OnBnClickedSave)
END_MESSAGE_MAP()


// CDataColorSed メッセージ ハンドラー
BOOL CDataColorSed::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowTextA(m_title.empty() ? "Set Sed Data Color" : m_title.c_str());

	m_ctrlAlpha.SetRange(0, ms_MaxRange, 0);
	m_ctrlAlpha.SetPos(static_cast<int>(m_sedColObj->alpha * ms_MaxRange));

	if (m_cv.num > MaxColorCount) {
		std::stringstream msg;
		msg << "** Error ** Color set count: " << m_cv.num << " is over max color count: " << MaxColorCount;
		MessageBox(msg.str().c_str(), "Missed", MB_OK | MB_ICONHAND);
		CDialog::OnCancel();
	}
	
	for (int i = 0;i < MaxColorCount;i++) {
		if (!ms_cww[i].AutoLoad(ms_SED_COL_IDS[i], this)) {
			MessageBox("** Error ** Failed to set subclass... Please retry.", "Missed", MB_OK | MB_ICONHAND);
			CDialog::OnCancel();
		}
	}
	return TRUE;
}

HBRUSH CDataColorSed::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	SetDialog();

	return hbr;
}

void CDataColorSed::OnNMCustomdrawSliderAlpha(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	m_cv.alpha = m_ctrlAlpha.GetPos() * 1.0/ms_MaxRange;

	*pResult = 0;
}

void CDataColorSed::OnBnClickedApply()
{
	int changeCount = 0;

	if (m_sedColObj->alpha != m_cv.alpha) {
		m_sedColObj->alpha = m_cv.alpha;
		changeCount++;
	}

	if (m_sedColObj->num != m_cv.num) {
		m_sedColObj->num = m_cv.num;
		changeCount++;
	}

	if (m_sedColObj->Equal != m_cv.Equal) {
		m_sedColObj->Equal = m_cv.Equal;
		changeCount++;
	}
	
	for (int i = 0;i < m_cv.num;i++) {
		if (m_sedColObj->val[i] != m_cv.val[i]) {
			m_sedColObj->val[i] = m_cv.val[i];
			changeCount++;
		}

		if (m_sedColObj->Rcol[i] != ms_cww[i].colground) {
			auto col = ms_cww[i].colground;
			m_sedColObj->Rcol[i] = col;
			m_sedColObj->Fcol[i] = F_COLOR(GetRValue(col), GetGValue(col), GetBValue(col));
			changeCount++;
		}
	}

	m_params->Change_DCOL = changeCount > 0;

	CDialog::OnOK();
}

void CDataColorSed::OnBnClickedSave()
{
	std::string fPath = m_bootPath + "\\RRI_CONTENTS\\COLOR_DATA_B.DAT";
	FILE* fp;
	if ((fp = fopen(fPath.c_str(), "w")) == NULL) {
		MessageBox("** Error **\nCannot ｆind [ /RRI_CONTENTS/COLOR_DATA_B.DAT ]..", "Error", MB_OK);
		return;
	}
	
	fprintf(fp, "[MESH_COLOR]  10\n");
	for (int i = 0; i < 10; i++) {
		fprintf(fp, " %d  %d  %d  %d\n", i, GetRValue(m_params->COL_MESH[i]), GetGValue(m_params->COL_MESH[i]), GetBValue(m_params->COL_MESH[i]));
	}

	m_cv.set = 1;
	COLVAL_FIX* pCol;
	for (int i = 0; i < FILE_IN_USE; i++) {
		pCol = (i == ms_CDataId) ? &m_cv: &m_params->Dcol[i];
		if (pCol->set) {
			fprintf(fp, "%d  %d  %d  %d  %.2lf\n", i, pCol->num, (int)pCol->Equal, (int)pCol->Mos, (double)pCol->alpha);
			for (int k = 0; k < pCol->num; k++) {
				fprintf(fp, "%.5lf  %d  %d  %d\n", pCol->val[k], GetRValue(pCol->Rcol[k]), GetGValue(pCol->Rcol[k]), GetBValue(pCol->Rcol[k]));
			}
		}
	}
	fclose(fp);

	MessageBox("保存成功しました！", "Info", MB_OK);
	return;
}

void CDataColorSed::SetDialog()
{
	for (int i = 0; i < MaxColorCount; i++) {
		if (m_cv.val[i] == DUNDEF) { m_cv.num = i + 1;  break; }
	}

	for (int i = 0; i < MaxColorCount; i++) {
		m_cv.Rcol[i] = (i <= m_cv.num) ? ms_cww[i].colground : RGB(100, 100, 100);
		Fill_Color(GetDlgItem(ms_SED_COL_IDS[i]), m_cv.Rcol[i]);
	}
}
