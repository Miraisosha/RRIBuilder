#pragma once
#include		<string>
#include		<vector>

#include		"RRI_Common.h"
#include		"CColWin.h"


// CDataColorSed ダイアログ

constexpr	int		MaxColorCount = 20;

class CDataColorSed : public CDialog
{
	DECLARE_DYNAMIC(CDataColorSed)

//-------------------------------------------------------
// Methods 
public:
	CDataColorSed(const std::string& bootPath, PARAMS* params, CWnd* pParent = nullptr);
	virtual ~CDataColorSed();

	void    SetTitle(std::string& title) { m_title.assign(title); };

private:
	void	SetDialog();

//-------------------------------------------------------
// Members 
private:
	std::string		m_title;
	std::string		m_bootPath;
	PARAMS			*m_params;
	COLVAL_FIX		m_cv, *m_sedColObj;

	static  int		ms_CDataId;
	static  int		ms_MaxRange;
	static	CColWin ms_cww[MaxColorCount];
	static	int		ms_SED_COL_IDS[MaxColorCount];
//-------------------------------------------------------
// MFC Items 
// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATACOLOR_SED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_ctrlAlpha;

public:
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMCustomdrawSliderAlpha(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedSave();
};
