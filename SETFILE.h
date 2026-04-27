#pragma once
#include  "RRI_GUIView.h"
//#include  "CommFuncs.h"

#include "RRI_Common.h"
#include "afxcmn.h"

// CSETFILE ダイアログ

////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE SET Input Dialog
//
////////////////////////////////////////////////////////////////////////////////////////
//__________________________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------　パラメータ定義

#define		INIT_BUTTON_ID		1230
#define		INIT_LABEL_ID		1250
#define		BUTTON_SPACE		7

#define		TAB_PARAM			0
#define		TAB_INFILE			1
#define		TAB_OUTFILE			2

#define		Comment(x)			m_Comment=x;UDF;
//__________________________________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////////////////////////
class CSETFILE : public CDialogEx
{
	DECLARE_DYNAMIC(CSETFILE)

public:
	CSETFILE(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSETFILE();

// ダイアログ データ
	enum { IDD = IDD_SETFILE };
//-----------------------------------------------------------------------------------------------------------
//  Store Data 
//-----------------------------------------------------------------------------------------------------------  
	MINFO*		MESH;	// 上下流どちらかわからないので呼び出す際にアドレスを入れておく
//-----------------------------------------------------------------------------------------------------------
// Class  Members   COMMON
//-----------------------------------------------------------------------------------------------------------  
	//
	TC_ITEM		TAB;
	TC_ITEM		tc_PARAM, tc_INFILE, tc_OUTFILE;		// タブ情報
	//
	int			CTAB,COLD;
	//
	DATASET		DS;
	//
	int			CLAND;
//-----------------------------------------------------------------------------------------------------------
// Class  Function
//-----------------------------------------------------------------------------------------------------------  
	static int AFXAPI BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	BOOL		Button_Dir(CString* m_DirName,char* m_RecentPath );
	//
	void		Init_Tab();
	int			Get_Set_File_Name(int no);
	int			Get_D2GIS_File_Name(int no);
	void		Switch_File(int no);
	void		Change_Control();
	//
	void		Set_Data();
	void		Set_Param_Data();
	void		Data_Update();
	//
	void		FileOut_RRI_Input(DATASET  DS );
	//
	void		Copy_DSET( DATASET* DT,DATASET DD );
	void		Delete_DSET( DATASET* DS );
	BOOL		Move_Resize_Dialog();


	HRESULT		Read_D2gis_File(int Fid,char* fname,MINFO* data);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	
//	CString m_Comment;
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnTcnSelchangeTabFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonFile1();
	afx_msg void OnClickedButtonFile2();
	afx_msg void OnClickedButtonFile3();
	afx_msg void OnClickedButtonFile4();
	afx_msg void OnClickedButtonFile5();
	afx_msg void OnClickedButtonFile6();
	afx_msg void OnClickedButtonFile7();
	afx_msg void OnClickedButtonFile8();
	afx_msg void OnClickedButtonFile9();
	afx_msg void OnClickedButtonFile10();
	afx_msg void OnClickedButtonFile11();
	afx_msg void OnClickedButtonFile12();
	afx_msg void OnClickedButtonFile13();
	afx_msg void OnClickedButtonFile14();
	afx_msg void OnClickedButtonFile15();
	afx_msg void OnClickedButtonFile16();
	afx_msg void OnClickedButtonFile17();
	afx_msg void OnClickedButtonFile18();
	afx_msg void OnClickedButtonFile19();
	afx_msg void OnClickedButtonFile20();
	afx_msg void OnClickedButtonFile0();
	afx_msg void OnClickedButtonOutfile0();
	afx_msg void OnClickedButtonOutfile1();
	afx_msg void OnClickedButtonOutfile2();
	afx_msg void OnClickedButtonOutfile3();
	afx_msg void OnClickedButtonOutfile4();
	afx_msg void OnClickedButtonOutfile5();
	afx_msg void OnClickedButtonOutfile6();
	afx_msg void OnClickedButtonOutfile7();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDblclkFilelabel1();
	afx_msg void OnDblclkFilelabel2();
	afx_msg void OnDblclkFilelabel3();
	afx_msg void OnDblclkFilelabel4();
	afx_msg void OnDblclkFilelabel6();
	afx_msg void OnDblclkFilelabel7();
	afx_msg void OnDblclkFilelabel8();
	afx_msg void OnDblclkFilelabel9();
	afx_msg void OnDblclkFilelabel10();
	afx_msg void OnDblclkFilelabel11();
	afx_msg void OnDblclkFilelabel12();
	afx_msg void OnDblclkFilelabel13();
	afx_msg void OnDblclkFilelabel14();
	afx_msg void OnDblclkFilelabel15();
	afx_msg void OnDblclkFilelabel16();
	afx_msg void OnDblclkFilelabel17();
	afx_msg void OnDblclkFilelabel18();
	afx_msg void OnDblclkFilelabel19();
	afx_msg void OnDblclkFilelabel20();
	afx_msg void OnDblclkFilelabel21();
	afx_msg void OnDblclkOutlabel0();
	afx_msg void OnDblclkOutlabel1();
	afx_msg void OnDblclkOutlabel2();
	afx_msg void OnDblclkOutlabel3();
	afx_msg void OnDblclkOutlabel4();
	afx_msg void OnDblclkOutlabel5();
	afx_msg void OnDblclkOutlabel6();
	afx_msg void OnDblclkOutlabel7();
	afx_msg void OnDblclkFilelabel5();
//	afx_msg void OnBnClickedOk2();
	CComboBox m_Combo;
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedButtonGisfile0();
	afx_msg void OnBnClickedButtonGisfile1();
	afx_msg void OnBnClickedButtonGisfile2();
	afx_msg void OnBnClickedButtonGisfile3();
	afx_msg void OnBnClickedButtonGisfile4();
	afx_msg void OnBnClickedButtonGisfile5();
	afx_msg void OnStnDblclickGislabel0();
	afx_msg void OnStnDblclickGislabel1();
	afx_msg void OnStnDblclickGislabel2();
	afx_msg void OnStnDblclickGislabel3();
	afx_msg void OnStnDblclickGislabel4();
	afx_msg void OnStnDblclickGislabel5();
	CTabCtrl c_TabFile;
	afx_msg void OnStnClickedSave0();
	afx_msg void OnStnClickedSaveas0();
};
