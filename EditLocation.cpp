// EditLocation.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "RRI_GUIView.h"
#include "EditLocation.h"
#include "afxdialogex.h"

extern		DATASET			DSET;
extern		PARAMS			PM;
extern		MINFO**			MESH;
// CEditLocation ダイアログ

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
int  CON_ID[10][4] = { { IDC_NO_1, IDC_EDIT_NAME_1, IDC_LNG_1, IDC_LAT_1 },
{ IDC_NO_2, IDC_EDIT_NAME_2, IDC_LNG_2, IDC_LAT_2 },
{ IDC_NO_3, IDC_EDIT_NAME_3, IDC_LNG_3, IDC_LAT_3 },
{ IDC_NO_4, IDC_EDIT_NAME_4, IDC_LNG_4, IDC_LAT_4 },
{ IDC_NO_5, IDC_EDIT_NAME_5, IDC_LNG_5, IDC_LAT_5 },
{ IDC_NO_6, IDC_EDIT_NAME_6, IDC_LNG_6, IDC_LAT_6 },
{ IDC_NO_7, IDC_EDIT_NAME_7, IDC_LNG_7, IDC_LAT_7 },
{ IDC_NO_8, IDC_EDIT_NAME_8, IDC_LNG_8, IDC_LAT_8 },
{ IDC_NO_9, IDC_EDIT_NAME_9, IDC_LNG_9, IDC_LAT_9 },
{ IDC_NO_10, IDC_EDIT_NAME_10, IDC_LNG_10, IDC_LAT_10 } };
//
IMPLEMENT_DYNAMIC(CEditLocation, CDialogEx)

CEditLocation::CEditLocation(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditLocation::IDD, pParent)
{

}

CEditLocation::~CEditLocation()
{
}

void CEditLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, c_BBack);
	DDX_Control(pDX, IDC_BUTTON_NEXT, c_BNext);
}


BEGIN_MESSAGE_MAP(CEditLocation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL_1, &CEditLocation::OnBnClickedButtonDel1)
	ON_BN_CLICKED(IDC_BUTTON_DEL_2, &CEditLocation::OnBnClickedButtonDel2)
	ON_BN_CLICKED(IDC_BUTTON_DEL_3, &CEditLocation::OnBnClickedButtonDel3)
	ON_BN_CLICKED(IDC_BUTTON_DEL_4, &CEditLocation::OnBnClickedButtonDel4)
	ON_BN_CLICKED(IDC_BUTTON_DEL_5, &CEditLocation::OnBnClickedButtonDel5)
	ON_BN_CLICKED(IDC_BUTTON_DEL_6, &CEditLocation::OnBnClickedButtonDel6)
	ON_BN_CLICKED(IDC_BUTTON_DEL_7, &CEditLocation::OnBnClickedButtonDel7)
	ON_BN_CLICKED(IDC_BUTTON_DEL_8, &CEditLocation::OnBnClickedButtonDel8)
	ON_BN_CLICKED(IDC_BUTTON_DEL_9, &CEditLocation::OnBnClickedButtonDel9)
	ON_BN_CLICKED(IDC_BUTTON_DEL_10, &CEditLocation::OnBnClickedButtonDel10)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CEditLocation::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CEditLocation::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDOK, &CEditLocation::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NAME_1, &CEditLocation::OnEnChangeEditName1)
	ON_EN_CHANGE(IDC_EDIT_NAME_2, &CEditLocation::OnEnChangeEditName2)
	ON_EN_CHANGE(IDC_EDIT_NAME_3, &CEditLocation::OnEnChangeEditName3)
	ON_EN_CHANGE(IDC_EDIT_NAME_4, &CEditLocation::OnEnChangeEditName4)
	ON_EN_CHANGE(IDC_EDIT_NAME_5, &CEditLocation::OnEnChangeEditName5)
	ON_EN_CHANGE(IDC_EDIT_NAME_6, &CEditLocation::OnEnChangeEditName6)
	ON_EN_CHANGE(IDC_EDIT_NAME_7, &CEditLocation::OnEnChangeEditName7)
	ON_EN_CHANGE(IDC_EDIT_NAME_8, &CEditLocation::OnEnChangeEditName8)
	ON_EN_CHANGE(IDC_EDIT_NAME_9, &CEditLocation::OnEnChangeEditName9)
	ON_EN_CHANGE(IDC_EDIT_NAME_10, &CEditLocation::OnEnChangeEditName10)
	ON_BN_CLICKED(IDCANCEL, &CEditLocation::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEditLocation メッセージ ハンドラー


BOOL CEditLocation::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	stNo = 0;
	Set_Data();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  End
	return TRUE;
}

void CEditLocation::Del_this(int id)
{
	int  cnt = 0;
	//
	id += stNo;
	if (id >= DSET.Lnum) return;
	//
	//
	if (DSET.Lnum == 1) {
		if (MessageBox("Invalidate out location  ? ", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) return;
		MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].flag = MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].flag%ID_MESH_LOC;
		MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].name[0] = 0x00;
		//
		SAFE_FREE(DSET.LCpos);
		DSET.Lnum = DSET.Lmem = 0;
		//
		CDialogEx::OnOK(); return;
	}
	for (int i = 0; i < DSET.Lnum; i++) {
		if (i == id)  {
			MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].flag = MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].flag%ID_MESH_LOC;
			MESH[DSET.LCpos[id].Vid][DSET.LCpos[id].Hid].name[0] = 0x00;
		}
		else {
			memcpy(&DSET.LCpos[cnt], &DSET.LCpos[i], sizeof(LOCATE_INFO));
			cnt++;
		}
	}
	DSET.Lnum = cnt;
	if (DSET.Lnum == stNo) stNo -= 10;
	//
	Set_Data();
}
void CEditLocation::OnBnClickedButtonDel1() { Del_this(0); }
void CEditLocation::OnBnClickedButtonDel2() { Del_this(1); }
void CEditLocation::OnBnClickedButtonDel3() { Del_this(2); }
void CEditLocation::OnBnClickedButtonDel4() { Del_this(3); }
void CEditLocation::OnBnClickedButtonDel5() { Del_this(4); }
void CEditLocation::OnBnClickedButtonDel6() { Del_this(5); }
void CEditLocation::OnBnClickedButtonDel7() { Del_this(6); }
void CEditLocation::OnBnClickedButtonDel8() { Del_this(7); }
void CEditLocation::OnBnClickedButtonDel9() { Del_this(8); }
void CEditLocation::OnBnClickedButtonDel10() { Del_this(9); }

void CEditLocation::OnBnClickedButtonBack()
{
	stNo -= 10;
	Set_Data();
}

void CEditLocation::OnBnClickedButtonNext()
{
	stNo += 10;
	Set_Data();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CEditLocation::Set_Data()
{
	CWnd*		cw;
	CString		str;
	int			id;
	//
	for (int i = 0; i < EDIT_NUM; i++) {
		id = stNo + i;
		for (int k = 0; k < 4; k++) {
			cw = GetDlgItem(CON_ID[i][k]);
			if (id < DSET.Lnum) {
				if (k == 0)			str.Format("%d", stNo + i+1);
				else if (k == 1)		str.Format("%s", DSET.LCpos[id].name);
				else if (k == 2)		str.Format("%d", DSET.LCpos[id].Hid+1);
				else if (k == 3)		str.Format("%d", PM.MVnum -DSET.LCpos[id].Vid);
				cw->SetWindowTextA(str);
				cw->EnableWindow(TRUE);
			}
			else {
				cw->SetWindowTextA("");
				cw->EnableWindow(FALSE);
			}
		}
	}
	//
	int  EndLim;
	if (DSET.Lnum % 10 == 0) EndLim = DSET.Lnum;
	else                  EndLim = ((int)(DSET.Lnum / 10) + 1) * 10;

	if (DSET.Lnum < 10) {
		c_BBack.EnableWindow(FALSE);
		c_BNext.EnableWindow(FALSE);
	}
	else if (stNo >= EndLim-10 && stNo < EndLim) {
			c_BBack.EnableWindow(TRUE);
			c_BNext.EnableWindow(FALSE);
	}
	else {
		c_BBack.EnableWindow(TRUE);
		c_BNext.EnableWindow(TRUE);
	}
}

void CEditLocation::OnBnClickedOk()
{
	int				id;
	CWnd*			cw;
	//
	for (int i = 0; i < DSET.Lnum; i++) {
		if (strlen(DSET.LCpos[i].name) == 0) strcpy(DSET.LCpos[i].name, "-");
	}
	//
	CDialogEx::OnOK();
}
void CEditLocation::Get_Name(int no)
{
	CWnd*		cw = GetDlgItem(CON_ID[no][1]);
	char			name[64];
	cw->GetWindowTextA(name, 64);
	//
	if (strlen(name) != 0) {
		for (int i = 0; i < strlen(name); i++) {
			if (name[i] == ' ') name[i] = '_';
		}
	}
	else strcpy(name, "-");
	//
	strcpy(DSET.LCpos[stNo + no].name, name);
}

void CEditLocation::OnEnChangeEditName1(){ UDT; Get_Name(0); }
void CEditLocation::OnEnChangeEditName2(){ UDT; Get_Name(1); }
void CEditLocation::OnEnChangeEditName3(){ UDT; Get_Name(2); }
void CEditLocation::OnEnChangeEditName4(){ UDT; Get_Name(3); }
void CEditLocation::OnEnChangeEditName5(){ UDT; Get_Name(4); }
void CEditLocation::OnEnChangeEditName6(){ UDT; Get_Name(5); }
void CEditLocation::OnEnChangeEditName7(){ UDT; Get_Name(6); }
void CEditLocation::OnEnChangeEditName8(){ UDT; Get_Name(7); }
void CEditLocation::OnEnChangeEditName9(){ UDT; Get_Name(8); }
void CEditLocation::OnEnChangeEditName10(){ UDT; Get_Name(9); }

void CEditLocation::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}
