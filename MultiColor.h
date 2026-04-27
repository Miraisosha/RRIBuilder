#pragma once


// CMultiColor ダイアログ

class CMultiColor : public CDialogEx
{
	DECLARE_DYNAMIC(CMultiColor)

public:
	CMultiColor(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMultiColor();

// ダイアログ データ
	enum { IDD = IDD_MULTICOLOR };

//-----------------------------------------------
	CString		Title;
	COLORREF		COPY_COLOR[21];

	void			GetColorDlg(int id);
	void			Draw_Color();
//-----------------------------------------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnDblclickColor0();
	afx_msg void OnStnDblclickColor1();
	afx_msg void OnStnDblclickColor2();
	afx_msg void OnStnDblclickColor3();
	afx_msg void OnStnDblclickColor4();
	afx_msg void OnStnDblclickColor5();
	afx_msg void OnStnDblclickColor6();
	afx_msg void OnStnDblclickColor7();
	afx_msg void OnStnDblclickColor8();
	afx_msg void OnStnDblclickColor9();
	afx_msg void OnStnDblclickColor10();
	afx_msg void OnStnDblclickColor11();
	afx_msg void OnStnDblclickColor12();
	afx_msg void OnStnDblclickColor13();
	afx_msg void OnStnDblclickColor14();
	afx_msg void OnStnDblclickColor15();
	afx_msg void OnStnDblclickColor16();
	afx_msg void OnStnDblclickColor17();
	afx_msg void OnStnDblclickColor18();
	afx_msg void OnStnDblclickColor19();
	afx_msg void OnStnDblclickColor20();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
