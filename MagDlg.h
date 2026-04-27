#pragma once
#include "afxwin.h"


// CMagDlg ダイアログ
#define		PROG_MAGNIFY			"RRI_CONTENTS\\bin\\scaleUp\\scaleUp.exe"   //  ./なしに注意
#define		PROG_MAGNIFY_DAT		"RRI_CONTENTS\\bin\\scaleUp\\scaleUp.txt"
#define		PROG_DEMADJUST_DAT	"RRI_CONTENTS\\bin\\DemAdjust2\\DemAdjust2.txt"
#define		PROG_DEMADJUST		"RRI_CONTENTS\\bin\\DemAdjust2\\DemAdjust2.exe"
#define		PROG_MAGNIFY_32			"RRI_CONTENTS\\bin32\\scaleUp\\scaleUp.exe"   //  ./なしに注意
#define		PROG_MAGNIFY_DAT_32		"RRI_CONTENTS\\bin32\\scaleUp\\scaleUp.txt"
#define		PROG_DEMADJUST_DAT_32		"RRI_CONTENTS\\bin32\\DemAdjust2\\DemAdjust2.txt"
#define		PROG_DEMADJUST_32			"RRI_CONTENTS\\bin32\\DemAdjust2\\DemAdjust2.exe"

class CMagDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagDlg)

public:
	CMagDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMagDlg();

// ダイアログ データ
	enum { IDD = IDD_MAGDLG };
// ----------------------------------------------------------------
	int			kind;		// 指定の内容、ScaleUP,demAjust ...
	CString		DemF, AccF, AdirF;
	int			SaveID;
	double		Mag;
	int			ret;

// ----------------------------------------------------------------

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString s_Mag;
	CButton b_ACC;
	CButton b_ADEM;
	CButton b_ADIR;
	CString s_COMorg;
	CString s_OrgACC;
	CString s_OrgADIR;
	CString s_OrgADEM;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdem();
	afx_msg void OnBnClickedButtonAcc();
	afx_msg void OnBnClickedButtonAdir();
	afx_msg void OnEnChangeEditMag();
	CString m_Memo;
	afx_msg void OnBnClickedOk();
	CStatic c_Label;
	CEdit c_Mag;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
