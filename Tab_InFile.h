#pragma once

#include "RRI_Common.h"

// CTab_InFile ダイアログ

class CTab_InFile : public CDialogEx
{
	DECLARE_DYNAMIC(CTab_InFile)

public:
	CTab_InFile(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTab_InFile();
//-------------------------------------------------------------------
	int			Change_Nums;
	int			IMnum;					// Import 数
	int			IMkind[FILE_IN_USE];		// ファイル種類
	CString		IMname[FILE_IN_USE];		// ファイル名
	//
	int			INV[FILE_IN_NUM], INVnum;	// 無効化ファイルの数と番号
//-------------------------------------------------------------------
	void			Tab_Init();
	void			Disp_Data();
	//
	void			Switch_File(int no);
	void			Get_FileName(int no);
	void			Save_Data_File(int no);
	void			SaveAs_Data_File(int no);
	//
	void			File_Import(int no);
	BOOL			Match_Model(CString  imname);
	void			SetCtrlPosition();
	void			MoveCtrl(int srcID, int tarID);
	//-------------------------------------------------------------------
	// ダイアログ データ
	enum { IDD = IDD_TAB_INFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnStnClickedFilelabel1();
	//afx_msg void OnStnClickedFilelabel2();
	//afx_msg void OnStnClickedFilelabel3();
	//afx_msg void OnStnClickedFilelabel4();
	//afx_msg void OnStnClickedFilelabel5();
	//afx_msg void OnStnClickedFilelabel6();
	//afx_msg void OnStnClickedFilelabel7();
	//afx_msg void OnStnClickedFilelabel8();
	//afx_msg void OnStnClickedFilelabel9();
	//afx_msg void OnStnClickedFilelabel10();
	//afx_msg void OnStnClickedFilelabel11();
	//afx_msg void OnStnClickedFilelabel12();
	//afx_msg void OnStnClickedFilelabel13();
	//afx_msg void OnStnClickedFilelabel14();
	//afx_msg void OnStnClickedFilelabel15();
	//afx_msg void OnStnClickedFilelabel16();
	//afx_msg void OnStnClickedFilelabel17();
	//afx_msg void OnStnClickedFilelabel18();
	//afx_msg void OnStnClickedFilelabel19();
	//afx_msg void OnStnClickedFilelabel20();
	//
	afx_msg void OnBnClickedButtonFile0();
	afx_msg void OnBnClickedButtonFile1();
	afx_msg void OnBnClickedButtonFile2();
	afx_msg void OnBnClickedButtonFile3();
	afx_msg void OnBnClickedButtonFile4();
	afx_msg void OnBnClickedButtonFile5();
	afx_msg void OnBnClickedButtonFile6();
	afx_msg void OnBnClickedButtonFile7();
	afx_msg void OnBnClickedButtonFile8();
	afx_msg void OnBnClickedButtonFile9();
	afx_msg void OnBnClickedButtonFile10();
	afx_msg void OnBnClickedButtonFile11();
	afx_msg void OnBnClickedButtonFile12();
	afx_msg void OnBnClickedButtonFile13();
	afx_msg void OnBnClickedButtonFile14();
	afx_msg void OnBnClickedButtonFile15();
	afx_msg void OnBnClickedButtonFile16();
	afx_msg void OnBnClickedButtonFile17();
	afx_msg void OnBnClickedButtonFile18();
	afx_msg void OnBnClickedButtonFile19();
	afx_msg void OnBnClickedButtonFile20();
	afx_msg void OnBnClickedButtonImport1();
	afx_msg void OnBnClickedButtonImport9();
	afx_msg void OnBnClickedButtonImport10();
	afx_msg void OnBnClickedButtonImport11();
	afx_msg void OnBnClickedButtonImport12();
	afx_msg void OnBnClickedButtonImport13();
	afx_msg void OnBnClickedButtonImport14();
	afx_msg void OnBnClickedButtonImport15();
	afx_msg void OnBnClickedButtonImport16();
	afx_msg void OnBnClickedButtonImport17();
	afx_msg void OnBnClickedButtonImport18();
	afx_msg void OnBnClickedButtonImport19();
	afx_msg void OnBnClickedButtonImport20();
	afx_msg void OnBnClickedButtonImport21();
	afx_msg void OnBnClickedButtonImport22();
	afx_msg void OnBnClickedButtonImport23();
	afx_msg void OnBnClickedButtonImport24();
	afx_msg void OnBnClickedButtonImport25();
	afx_msg void OnBnClickedButtonImport26();
	afx_msg void OnBnClickedButtonImport27();
	afx_msg void OnBnClickedButtonImport28();
	afx_msg void OnBnClickedButtonDelete1();
	afx_msg void OnBnClickedButtonDelete2();
	afx_msg void OnBnClickedButtonDelete3();
	afx_msg void OnBnClickedButtonDelete4();
	afx_msg void OnBnClickedButtonDelete5();
	afx_msg void OnBnClickedButtonDelete6();
	afx_msg void OnBnClickedButtonDelete7();
	afx_msg void OnBnClickedButtonDelete8();
	afx_msg void OnBnClickedButtonDelete9();
	afx_msg void OnBnClickedButtonDelete10();
	afx_msg void OnBnClickedButtonDelete11();
	afx_msg void OnBnClickedButtonDelete12();
	afx_msg void OnBnClickedButtonDelete13();
	afx_msg void OnBnClickedButtonDelete14();
	afx_msg void OnBnClickedButtonDelete15();
	afx_msg void OnBnClickedButtonDelete16();
	afx_msg void OnBnClickedButtonDelete17();
	afx_msg void OnBnClickedButtonDelete18();
	afx_msg void OnBnClickedButtonDelete19();
	afx_msg void OnBnClickedButtonDelete20();
	afx_msg void OnBnClickedButtonDelete21();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
