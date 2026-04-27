#pragma once


#include "Tab_Param.h"
#include "Tab_InFile.h"
#include "Tab_OutFile.h"
#include "afxcmn.h"
#include "RRI_GUIView.h"


#define		RRI_INIT	10
#define		TABMARGIN_X  51
#define		TABMARGIN_Y  107

class CRI_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(CRI_DLG)

public:
	CRI_DLG(CRRI_GUIView* pParent = NULL);   // 標準コンストラクター
	virtual ~CRI_DLG();

// ダイアログ データ
	enum { IDD = IDD_RI_DLG };
	//--------------------------------------------------------------------
	CTab_Param		Dlg_Param;
	CTab_InFile		Dlg_InFile;
	CTab_OutFile		Dlg_OutFile;
	TC_ITEM			TAB;
	//
	int			Change_Nums;

	int			CTAB,COLD;
	//--------------------------------------------------------------------
	void			Init_Tab();

private:
	CRRI_GUIView* m_pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveRri();
	afx_msg void OnBnClickedSaveAsRri();
	//afx_msg void OnBnClickedCheckChange();
//	BOOL b_exchange;
	afx_msg void OnBnClickedCancel();
};
