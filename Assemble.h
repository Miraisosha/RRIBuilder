#pragma once

#include		"AsEdit.h"
#include		"afxwin.h"
#define		EDIT_FRAME_H		20
// CAssemble ダイアログ
#define		ID_INIT_ASM		3000

class CAssemble : public CDialogEx
{
	DECLARE_DYNAMIC(CAssemble)

public:
	CAssemble(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CAssemble();

// ダイアログ データ
	enum { IDD = IDD_ASSEMBLE };
//--------------------------------------------------------------------------
	CAsEdit		Cae;
	int			Anum, Amem;		// 最初の設定　変えない
	int*			Assign;

	int			Enum, Emem;		// 変えてゆく
	int*			Ntemp;
	int*			param;

	BOOL			REMAIN;
	//
	CAsEdit**	Nlabel;
	CAsEdit**	RowAsm;
	CAsEdit**	ParamNo;
	int*			ID_Name;
	int*			ID_Row;
	int*			ID_Pno;

//--------------------------------------------------------------------------
	BOOL			Make_Dlg_Frame();
	void			Disp_Stat();
	void			Relist_No();
	//
	void			Free_All();
//--------------------------------------------------------------------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
public:
	CStatic stc_NLabel;
	CStatic stc_ASLabels;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic stc_Remains;
protected:
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
};
