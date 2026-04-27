#pragma once
#include "RRI_Common.h"


// CSetSedNo ダイアログ
class CSetSedNo : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSedNo)

public:
	CSetSedNo(short oriSedNo, COLVAL_FIX* colorSet, CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CSetSedNo();

//関数
public:
	short SelectedSedNo() { return m_selSedNo; }

private:
	void DisplayColorForSelSedNo();

//変数
private:
	short m_selSedNo;
	COLVAL_FIX* m_colorSet;

	static short ms_SedMin;
	static short ms_SedMax;

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_SED_NO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSedNoChanged();
	virtual BOOL OnInitDialog();
};
