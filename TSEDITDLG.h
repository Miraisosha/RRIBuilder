#pragma once
#include  "AsEdit.h"

#include "RRI_Common.h"
#include "afxwin.h"


#define		ID_TS_INIT		3000
#define		X_TS_SIZE		90
#define		X_POS_SIZE		44
#define		Y_TS_SIZE		20
#define		WINDOW_FRAME		30

#define		SPAN_MAX			20
#define		POS_MAX			8



// CTSEditDlg ダイアログ

class CTSEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTSEditDlg)

public:
	CTSEditDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTSEditDlg();

// ダイアログ データ
	enum { IDD = IDD_TSEDITDLG };

//
//------------------------------------------------------------------------
	CTime		BT;
	CTime		CT,ST;
	int			Hnum,Vnum,LDH,LDV;	// 左下編集枠の座標と方向増分
	int			ShowV,ShowH,stH, stV;
	int			Data_ID;
	int			Result,Data_Change_Cnt;
	int			Lrow,Lcol;
	BOOL			Change_Mesh;
	//
	int			TS_CONTS_VP[16];
	//
	TIMESET		TS;
	//
	int*			Name_ID;	// Hnum
	int			Name_VP;	//初期位置
	CAsEdit**	Names;
	//
	int*			MFX_ID;		// Hnum
	int			MF_VP;		//初期位置
	CAsEdit**	MFXs;
	//
	int*			MFY_ID;		// Hnum
	CAsEdit**	MFYs;
	//
	int**		Edits_ID;	// Hnum * Vnum
	CAsEdit***	Edits;
	//
	int*			Times_ID;	// Vnum
	int*			Times_VP;	// Vnum
	CAsEdit**	Times;
//
//------------------------------------------------------------------------
	BOOL	 Init_Set_Edits();
	BOOL	 Set_Edit_Value();
//
	void	 Free_All(BOOL TSfree);

	BOOL	Save_TS_File(int ID,CString fname,TIMESET* TS);
	BOOL	Renew_Data();
//------------------------------------------------------------------------
//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic c_Mfrom;
	CStatic c_Name;
	CString m_Num;
	CString m_Tspan;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSaveAs();
	afx_msg void OnBnClickedButtonAddT();
	afx_msg void OnBnClickedButtonDelT();
	afx_msg void OnBnClickedButtonDelP();
	afx_msg void OnPaint();
protected:
	afx_msg LRESULT OnAseditFocus(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonSetday();
	CButton c_Down;
	CButton c_Left;
	CButton c_Right;
	CButton c_Up;
	afx_msg void OnBnClickedCheckUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	CButton c_SetDaily;
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonImport();
};
