#pragma once


// CMake_Dynamic ダイアログ

class CMake_Dynamic : public CDialogEx
{
	DECLARE_DYNAMIC(CMake_Dynamic)

public:
	CMake_Dynamic(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMake_Dynamic();

// ダイアログ データ
	enum { IDD = IDD_MAKE_DYNAMIC };
//--------------------------------------------------------------------

//--------------------------------------------------------------------
	void CMake_Dynamic::Get_File_Name(int No);
	void CMake_Dynamic::Display_State();
	void	 CMake_Dynamic::Edit_TimeSet(int FN);
//--------------------------------------------------------------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDfile1();
	afx_msg void OnBnClickedButtonDfile2();
	afx_msg void OnBnClickedButtonDfile3();
	afx_msg void OnBnClickedButtonDfile4();
	afx_msg void OnBnClickedButtonDfile5();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioD22();
};
