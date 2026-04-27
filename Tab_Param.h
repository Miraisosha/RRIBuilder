#pragma once

#include "RRI_Common.h"
#include "afxwin.h"
// CTab_Param ダイアログ

class CTab_Param : public CDialogEx
{
	DECLARE_DYNAMIC(CTab_Param)

public:
	CTab_Param(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTab_Param();
//--------------------------------------------------------------------
	int			Change_Nums;
//--------------------------------------------------------------------
	void	Init_Tab();
	void	Disp_Data();
	//
	void	Get_Data();
	//
	/// 2015/12 追加 FAO -> RRI_COMMON に移動
	//void		Copy_Luinfo(LUINFO* tar, LUINFO org);
	//BOOL		IsSame_Luinfo(LUINFO tar, LUINFO org);

//--------------------------------------------------------------------

// ダイアログ データ
	enum { IDD = IDD_TAB_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combo_LU;
	virtual BOOL OnInitDialog();
	CString s_NameRRI;
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonFao();
	CString s_MeshNum;
	CButton c_BFAO;
};
