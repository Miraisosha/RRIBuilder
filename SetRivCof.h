#pragma once


// CSetRivCof ダイアログ

class CSetRivCof : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRivCof)

public:
	CSetRivCof(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetRivCof();

	int		HowtoW, HowtoD;
	double	Cw, Sw, Cd, Sd;
	double	Wid, Dep, H;
// ダイアログ データ
	enum { IDD = IDD_SETRIVCOF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString s_H;
	CString s_W;
	CString s_D;
	afx_msg void OnEnChangeEditW();
	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditH();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString s_CD;
	CString s_CW;
	CString s_SD;
	CString s_SW;
	afx_msg void OnEnChangeEditCw();
	afx_msg void OnEnChangeEditSw();
	afx_msg void OnEnChangeEditCd();
	afx_msg void OnEnChangeEditSd();
	afx_msg void OnBnClickedRadioWu();
	afx_msg void OnBnClickedRadioWc();
	afx_msg void OnBnClickedRadioDu();
	afx_msg void OnBnClickedRadioDc();
//	afx_msg void OnEnChangeEditRiv();
//	CString s_AccLimit;
};
