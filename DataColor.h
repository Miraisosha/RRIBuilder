#pragma once


// CDataColor ダイアログ

#pragma once
#include		"CommFuncs.h"
#include		"RRI_Common.h"
//#include		"CColWin.h"

#define	ColorNumber	9

class CDataColor : public CDialog
{
	DECLARE_DYNAMIC(CDataColor)

public:
	CDataColor(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDataColor();

// ダイアログ データ
	enum { IDD = IDD_DATACOLOR };
//---------------------------------------------------------------
	CString		Title;

	COLVAL_FIX	CV;
	BOOL			B_DataMosaic;

	COLORREF	TEMP_COL[ColorNumber];

	CString		Boot;

	BOOL			Ready;
//---------------------------------------------------------------
	void	Set_Dialog();
	double	Get_EditRect( int ID );

//---------------------------------------------------------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedDradioCont();
	afx_msg void OnBnClickedDradioMosaic();
	afx_msg void OnBnClickedDradioEq();
	afx_msg void OnBnClickedDradioGr();
	afx_msg void OnEnChangeEditD0();
	afx_msg void OnEnChangeEditD1();
	afx_msg void OnEnChangeEditD2();
	afx_msg void OnEnChangeEditD3();
	afx_msg void OnEnChangeEditD4();
	afx_msg void OnEnChangeEditD5();
	afx_msg void OnEnChangeEditD6();
	afx_msg void OnEnChangeEditD7();
	afx_msg void OnEnChangeEditD8();
	afx_msg void OnEnChangeEditD9();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonColsave();
	CSliderCtrl m_Slider_Alpha;
	afx_msg void OnNMCustomdrawSliderAlpha(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
};
