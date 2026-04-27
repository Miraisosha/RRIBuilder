// Tab_OutFile.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Tab_OutFile.h"
#include "afxdialogex.h"

//////////////////////////////////////////////////////////////////////////////////////////////
extern		DATASET			DS;
extern		char			m_RecentPath[SIZE_05K];

BOOL	INITIAL = TRUE;

// TAB OUTFILE

int				OUTPUT_LABELS_ID[] = { IDC_OUTLABEL_0, IDC_OUTLABEL_1, IDC_OUTLABEL_2, IDC_OUTLABEL_3, IDC_OUTLABEL_4,
									IDC_OUTLABEL_5, IDC_OUTLABEL_6, IDC_OUTLABEL_7, IDC_OUTLABEL_8, IDC_OUTLABEL_9};

int				BOUT_Num = FILE_OUT_NUM;
int				BGIS_Num = FILE_GIS_NUM;

int				BOUT_EDIT_ID[] = { IDC_EDIT_HEAD_0, IDC_EDIT_HEAD_1, IDC_EDIT_HEAD_2, IDC_EDIT_HEAD_3, IDC_EDIT_HEAD_4,
									IDC_EDIT_HEAD_5, IDC_EDIT_HEAD_6, IDC_EDIT_HEAD_7, IDC_EDIT_HEAD_8, IDC_EDIT_HEAD_9};
CString			BOUT_Text[FILE_OUT_NUM];
int				BOUT_LABEL_ID[] = {
						IDC_OUTLABEL_0, IDC_OUTLABEL_1, IDC_OUTLABEL_2, IDC_OUTLABEL_3, IDC_OUTLABEL_4,
						IDC_OUTLABEL_5, IDC_OUTLABEL_6, IDC_OUTLABEL_7, IDC_OUTLABEL_8, IDC_OUTLABEL_9};
extern          CString		OutFile_Title[];
//_______________________________________________________________________________________________

// CTab_OutFile ダイアログ

IMPLEMENT_DYNAMIC(CTab_OutFile, CDialogEx)

CTab_OutFile::CTab_OutFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab_OutFile::IDD, pParent)
{

}

CTab_OutFile::~CTab_OutFile()
{
}

void CTab_OutFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab_OutFile, CDialogEx)
	ON_STN_CLICKED(IDC_OUTLABEL_0, &CTab_OutFile::OnStnClickedOutlabel0)
	ON_STN_CLICKED(IDC_OUTLABEL_1, &CTab_OutFile::OnStnClickedOutlabel1)
	ON_STN_CLICKED(IDC_OUTLABEL_2, &CTab_OutFile::OnStnClickedOutlabel2)
	ON_STN_CLICKED(IDC_OUTLABEL_3, &CTab_OutFile::OnStnClickedOutlabel3)
	ON_STN_CLICKED(IDC_OUTLABEL_4, &CTab_OutFile::OnStnClickedOutlabel4)
	ON_STN_CLICKED(IDC_OUTLABEL_5, &CTab_OutFile::OnStnClickedOutlabel5)
	ON_STN_CLICKED(IDC_OUTLABEL_6, &CTab_OutFile::OnStnClickedOutlabel6)
	ON_STN_CLICKED(IDC_OUTLABEL_7, &CTab_OutFile::OnStnClickedOutlabel7)
	ON_STN_CLICKED(IDC_OUTLABEL_8, &CTab_OutFile::OnStnClickedOutlabel8)
	ON_STN_CLICKED(IDC_OUTLABEL_9, &CTab_OutFile::OnStnClickedOutlabel9)
	ON_EN_CHANGE(IDC_EDIT_HEAD_0, &CTab_OutFile::OnEnChangeEditHead0)
	ON_EN_CHANGE(IDC_EDIT_HEAD_1, &CTab_OutFile::OnEnChangeEditHead1)
	ON_EN_CHANGE(IDC_EDIT_HEAD_2, &CTab_OutFile::OnEnChangeEditHead2)
	ON_EN_CHANGE(IDC_EDIT_HEAD_3, &CTab_OutFile::OnEnChangeEditHead3)
	ON_EN_CHANGE(IDC_EDIT_HEAD_4, &CTab_OutFile::OnEnChangeEditHead4)
	ON_EN_CHANGE(IDC_EDIT_HEAD_5, &CTab_OutFile::OnEnChangeEditHead5)
	ON_EN_CHANGE(IDC_EDIT_HEAD_6, &CTab_OutFile::OnEnChangeEditHead6)
	ON_EN_CHANGE(IDC_EDIT_HEAD_7, &CTab_OutFile::OnEnChangeEditHead7)
	ON_EN_CHANGE(IDC_EDIT_HEAD_8, &CTab_OutFile::OnEnChangeEditHead8)
	ON_EN_CHANGE(IDC_EDIT_HEAD_9, &CTab_OutFile::OnEnChangeEditHead9)
END_MESSAGE_MAP()

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  タブの初期化・変更
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

BOOL CTab_OutFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Tab_Init();
	Disp_Data();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
void CTab_OutFile::Tab_Init()
{
	char		Rpath[SIZE_01K], Fullname[SIZE_01K];
	CString		Rname;
	CWnd		*cw;
	CWnd		*ce;
	//
	for (int i = 0; i < FILE_OUT_NUM; i++) {
		cw = GetDlgItem(BOUT_LABEL_ID[i]);
		cw->SetWindowTextA(OutFile_Title[i]);
	}
	return;
}
void CTab_OutFile::Disp_Data()
{
	CWnd	*cl, *cf;
	CEdit*	ce;
	//
	for (int i = 0; i < FILE_OUT_NUM; i++) {
		cl = GetDlgItem(BOUT_LABEL_ID[i]);
		ce = (CEdit*)GetDlgItem(BOUT_EDIT_ID[i]);
		//
		if (DS.out_use[i]) {
			cl->EnableWindow(TRUE);
			ce->SetWindowTextA(DS.Out_names[i]);
		}
		else {
			cl->EnableWindow(FALSE);
			ce->SetWindowTextA(_T(""));
		}
	}
	//
	if (INITIAL) INITIAL = FALSE;
	return;
}
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  ラベルコントロール
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_OutFile::Switch_File(int kind, int no)
{
	if (kind == 0) {
		DS.out_use[no] = FALSE;
		DS.Out_names[no][0] = 0x00;
		Change_Nums++;
	}
	//
	Disp_Data();
}

void CTab_OutFile::OnStnClickedOutlabel0() { Switch_File(0, 0); }
void CTab_OutFile::OnStnClickedOutlabel1() { Switch_File(0, 1); }
void CTab_OutFile::OnStnClickedOutlabel2() { Switch_File(0, 2); }
void CTab_OutFile::OnStnClickedOutlabel3() { Switch_File(0, 3); }
void CTab_OutFile::OnStnClickedOutlabel4() { Switch_File(0, 4); }
void CTab_OutFile::OnStnClickedOutlabel5() { Switch_File(0, 5); }
void CTab_OutFile::OnStnClickedOutlabel6() { Switch_File(0, 6); }
void CTab_OutFile::OnStnClickedOutlabel7() { Switch_File(0, 7); }
void CTab_OutFile::OnStnClickedOutlabel8() { Switch_File(0, 8); }
void CTab_OutFile::OnStnClickedOutlabel9() { Switch_File(0, 9); }

// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//  ヘッダー
//-----------------------------------------------------------------------------------------------------------  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CTab_OutFile::Search_Edit(int no)
{
	if (INITIAL) return;
	//
	CEdit*	ce = (CEdit*)GetDlgItem(BOUT_EDIT_ID[no]);
	CWnd*	cw = GetDlgItem(OUTPUT_LABELS_ID[no]);
	if (!ce || !cw ) return;
	//
	CString	head;

	ce->GetWindowTextA(head);
	if (head.GetLength() != 0) {
		strcpy(DS.Out_names[no], head);
		DS.out_use[no] = TRUE;
		cw->EnableWindow(TRUE);
	}
	else {
		DS.out_use[no] = FALSE;
		cw->EnableWindow(FALSE);
	}
	Change_Nums++;
	//
}
void CTab_OutFile::OnEnChangeEditHead0() { UDT; Search_Edit(0); }
void CTab_OutFile::OnEnChangeEditHead1() { UDT; Search_Edit(1); }
void CTab_OutFile::OnEnChangeEditHead2() { UDT; Search_Edit(2); }
void CTab_OutFile::OnEnChangeEditHead3() { UDT; Search_Edit(3); }
void CTab_OutFile::OnEnChangeEditHead4() { UDT; Search_Edit(4); }
void CTab_OutFile::OnEnChangeEditHead5() { UDT; Search_Edit(5); }
void CTab_OutFile::OnEnChangeEditHead6() { UDT; Search_Edit(6); }
void CTab_OutFile::OnEnChangeEditHead7() { UDT; Search_Edit(7); }
void CTab_OutFile::OnEnChangeEditHead8() { UDT; Search_Edit(8); }
void CTab_OutFile::OnEnChangeEditHead9() { UDT; Search_Edit(9); }


BOOL CTab_OutFile::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN) { return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}
