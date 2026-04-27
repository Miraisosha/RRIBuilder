// EditDamCnt.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "EditDamCnt.h"
#include "afxdialogex.h"

extern		DATASET			DSET;
extern		PARAMS			PM;
extern		MINFO**			MESH;

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int  CON_ID[10][6] = { { IDC_NO_1, IDC_EDIT_NAME_1, IDC_LNG_1, IDC_LAT_1, IDC_EDIT_STRAGE_1, IDC_EDIT_STARTQ_1 },
					{ IDC_NO_2, IDC_EDIT_NAME_2, IDC_LNG_2, IDC_LAT_2, IDC_EDIT_STRAGE_2, IDC_EDIT_STARTQ_2 },
					{ IDC_NO_3, IDC_EDIT_NAME_3, IDC_LNG_3, IDC_LAT_3, IDC_EDIT_STRAGE_3, IDC_EDIT_STARTQ_3 },
					{ IDC_NO_4, IDC_EDIT_NAME_4, IDC_LNG_4, IDC_LAT_4, IDC_EDIT_STRAGE_4, IDC_EDIT_STARTQ_4 },
					{ IDC_NO_5, IDC_EDIT_NAME_5, IDC_LNG_5, IDC_LAT_5, IDC_EDIT_STRAGE_5, IDC_EDIT_STARTQ_5 },
					{ IDC_NO_6, IDC_EDIT_NAME_6, IDC_LNG_6, IDC_LAT_6, IDC_EDIT_STRAGE_6, IDC_EDIT_STARTQ_6 },
					{ IDC_NO_7, IDC_EDIT_NAME_7, IDC_LNG_7, IDC_LAT_7, IDC_EDIT_STRAGE_7, IDC_EDIT_STARTQ_7 },
					{ IDC_NO_8, IDC_EDIT_NAME_8, IDC_LNG_8, IDC_LAT_8, IDC_EDIT_STRAGE_8, IDC_EDIT_STARTQ_8 },
					{ IDC_NO_9, IDC_EDIT_NAME_9, IDC_LNG_9, IDC_LAT_9, IDC_EDIT_STRAGE_9, IDC_EDIT_STARTQ_9 },
					{ IDC_NO_10, IDC_EDIT_NAME_10, IDC_LNG_10, IDC_LAT_10, IDC_EDIT_STRAGE_10, IDC_EDIT_STARTQ_10 } };
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CEditDamCnt ダイアログ

IMPLEMENT_DYNAMIC(CEditDamCnt, CDialogEx)

CEditDamCnt::CEditDamCnt(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDamCnt::IDD, pParent)
{
	stNo = 0;
}

CEditDamCnt::~CEditDamCnt()
{
}

void CEditDamCnt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, c_BBack);
	DDX_Control(pDX, IDC_BUTTON_NEXT, c_BNext);
}


BEGIN_MESSAGE_MAP(CEditDamCnt, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL_1, &CEditDamCnt::OnBnClickedButtonDel1)
	ON_BN_CLICKED(IDC_BUTTON_DEL_2, &CEditDamCnt::OnBnClickedButtonDel2)
	ON_BN_CLICKED(IDC_BUTTON_DEL_3, &CEditDamCnt::OnBnClickedButtonDel3)
	ON_BN_CLICKED(IDC_BUTTON_DEL_4, &CEditDamCnt::OnBnClickedButtonDel4)
	ON_BN_CLICKED(IDC_BUTTON_DEL_5, &CEditDamCnt::OnBnClickedButtonDel5)
	ON_BN_CLICKED(IDC_BUTTON_DEL_6, &CEditDamCnt::OnBnClickedButtonDel6)
	ON_BN_CLICKED(IDC_BUTTON_DEL_7, &CEditDamCnt::OnBnClickedButtonDel7)
	ON_BN_CLICKED(IDC_BUTTON_DEL_8, &CEditDamCnt::OnBnClickedButtonDel8)
	ON_BN_CLICKED(IDC_BUTTON_DEL_9, &CEditDamCnt::OnBnClickedButtonDel9)
	ON_BN_CLICKED(IDC_BUTTON_DEL_10, &CEditDamCnt::OnBnClickedButtonDel10)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CEditDamCnt::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CEditDamCnt::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDOK, &CEditDamCnt::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NAME_1, &CEditDamCnt::OnEnChangeEditName1)
	ON_EN_CHANGE(IDC_EDIT_NAME_2, &CEditDamCnt::OnEnChangeEditName2)
	ON_EN_CHANGE(IDC_EDIT_NAME_3, &CEditDamCnt::OnEnChangeEditName3)
	ON_EN_CHANGE(IDC_EDIT_NAME_4, &CEditDamCnt::OnEnChangeEditName4)
	ON_EN_CHANGE(IDC_EDIT_NAME_5, &CEditDamCnt::OnEnChangeEditName5)
	ON_EN_CHANGE(IDC_EDIT_NAME_6, &CEditDamCnt::OnEnChangeEditName6)
	ON_EN_CHANGE(IDC_EDIT_NAME_7, &CEditDamCnt::OnEnChangeEditName7)
	ON_EN_CHANGE(IDC_EDIT_NAME_8, &CEditDamCnt::OnEnChangeEditName8)
	ON_EN_CHANGE(IDC_EDIT_NAME_9, &CEditDamCnt::OnEnChangeEditName9)
	ON_EN_CHANGE(IDC_EDIT_NAME_10, &CEditDamCnt::OnEnChangeEditName10)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_1, &CEditDamCnt::OnEnChangeEditStrage1)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_2, &CEditDamCnt::OnEnChangeEditStrage2)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_3, &CEditDamCnt::OnEnChangeEditStrage3)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_4, &CEditDamCnt::OnEnChangeEditStrage4)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_5, &CEditDamCnt::OnEnChangeEditStrage5)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_6, &CEditDamCnt::OnEnChangeEditStrage6)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_7, &CEditDamCnt::OnEnChangeEditStrage7)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_8, &CEditDamCnt::OnEnChangeEditStrage8)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_9, &CEditDamCnt::OnEnChangeEditStrage9)
	ON_EN_CHANGE(IDC_EDIT_STRAGE_10, &CEditDamCnt::OnEnChangeEditStrage10)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_1, &CEditDamCnt::OnEnChangeEditStartq1)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_2, &CEditDamCnt::OnEnChangeEditStartq2)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_3, &CEditDamCnt::OnEnChangeEditStartq3)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_4, &CEditDamCnt::OnEnChangeEditStartq4)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_5, &CEditDamCnt::OnEnChangeEditStartq5)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_6, &CEditDamCnt::OnEnChangeEditStartq6)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_7, &CEditDamCnt::OnEnChangeEditStartq7)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_8, &CEditDamCnt::OnEnChangeEditStartq8)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_9, &CEditDamCnt::OnEnChangeEditStartq9)
	ON_EN_CHANGE(IDC_EDIT_STARTQ_10, &CEditDamCnt::OnEnChangeEditStartq10)
END_MESSAGE_MAP()


// CEditDamCnt メッセージ ハンドラー
BOOL CEditDamCnt::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	for (int i = 0; i < DSET.Damc_Num;i++)
		if (strlen(DSET.DAMC[i].name) == 0) strcpy(DSET.DAMC[i].name, "-");
	stNo = 0;
	Set_Data();

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  End
	return TRUE;
}

void CEditDamCnt::Del_this(int id)
{
	int  cnt = 0;
	//
	id += stNo;
	//
	if (id >= DSET.Damc_Num) return;
	//
	if (DSET.Damc_Num == 1) {
		if (MessageBox("Invalidate dam condition ? ", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) return;
		if(DSET.Riv_Avail ) MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].flag = ID_MESH_R;
		else               MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].flag = ID_MESH;
		MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].name[0] = 0x00;
//
		SAFE_FREE(DSET.DAMC);
		DSET.Damc_Mem = DSET.Damc_Num = 0;
		//
		CDialogEx::OnOK(); return;
	}
	//
	cnt = 0;
	for (int i = 0; i < DSET.Damc_Num; i++) {
		if (i == id) {
			if (DSET.Riv_Avail)		MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].flag = ID_MESH_R;
			else						MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].flag = ID_MESH;
			MESH[DSET.DAMC[id].y][DSET.DAMC[id].x].name[0] = 0x00;
		}
		else {
			DSET.DAMC[cnt].x = DSET.DAMC[i].x;
			DSET.DAMC[cnt].y = DSET.DAMC[i].y;
			DSET.DAMC[cnt].vol = DSET.DAMC[i].vol;
			DSET.DAMC[cnt].startq = DSET.DAMC[i].startq;
			strcpy(DSET.DAMC[cnt].name, DSET.DAMC[i].name);
			cnt++;
		}
	}
	DSET.Damc_Num = DSET.Damc_Num - 1;
	if (DSET.Damc_Num == stNo) stNo -= 10;
	//
	Set_Data();
}

void CEditDamCnt::OnBnClickedButtonDel1(){ Del_this(0); }
void CEditDamCnt::OnBnClickedButtonDel2(){ Del_this(1); }
void CEditDamCnt::OnBnClickedButtonDel3(){ Del_this(2); }
void CEditDamCnt::OnBnClickedButtonDel4(){ Del_this(3); }
void CEditDamCnt::OnBnClickedButtonDel5(){ Del_this(4); }
void CEditDamCnt::OnBnClickedButtonDel6(){ Del_this(5); }
void CEditDamCnt::OnBnClickedButtonDel7(){ Del_this(6); }
void CEditDamCnt::OnBnClickedButtonDel8(){ Del_this(7); }
void CEditDamCnt::OnBnClickedButtonDel9(){ Del_this(8); }
void CEditDamCnt::OnBnClickedButtonDel10(){ Del_this(9); }

void CEditDamCnt::OnBnClickedButtonBack()
{
	stNo -= 10;
	Set_Data();
}
void CEditDamCnt::OnBnClickedButtonNext()
{
	stNo += 10;
	Set_Data();
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CEditDamCnt::Get_Name(int no)
{
	CWnd*		cw = GetDlgItem(CON_ID[no][1]);
	char			name[64];
	cw->GetWindowTextA(name, 64);
	//
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] == ' ') name[i] = '_';
	}
	strcpy(DSET.DAMC[stNo + no].name, name);
}

void CEditDamCnt::OnEnChangeEditName1(){ UDT; Get_Name(0); }
void CEditDamCnt::OnEnChangeEditName2(){ UDT; Get_Name(1); }
void CEditDamCnt::OnEnChangeEditName3(){ UDT; Get_Name(2); }
void CEditDamCnt::OnEnChangeEditName4(){ UDT; Get_Name(3); }
void CEditDamCnt::OnEnChangeEditName5(){ UDT; Get_Name(4); }
void CEditDamCnt::OnEnChangeEditName6(){ UDT; Get_Name(5); }
void CEditDamCnt::OnEnChangeEditName7(){ UDT; Get_Name(6); }
void CEditDamCnt::OnEnChangeEditName8(){ UDT; Get_Name(7); }
void CEditDamCnt::OnEnChangeEditName9(){ UDT; Get_Name(8); }
void CEditDamCnt::OnEnChangeEditName10(){ UDT; Get_Name(9); }

void CEditDamCnt::Get_Value(int frame,int no)
{
	CWnd*		cw = GetDlgItem(CON_ID[no][frame]);
	char			cvalue[64];
	cw->GetWindowTextA(cvalue, 64);
	//
	if (frame == 4) DSET.DAMC[stNo + no].vol	= atof(cvalue);
	else           DSET.DAMC[stNo + no].startq	= atof(cvalue);
}

void CEditDamCnt::OnEnChangeEditStrage1(){ UDT; Get_Value(4, 0); }
void CEditDamCnt::OnEnChangeEditStrage2(){ UDT; Get_Value(4, 1); }
void CEditDamCnt::OnEnChangeEditStrage3(){ UDT; Get_Value(4, 2); }
void CEditDamCnt::OnEnChangeEditStrage4(){ UDT; Get_Value(4, 3); }
void CEditDamCnt::OnEnChangeEditStrage5(){ UDT; Get_Value(4, 4); }
void CEditDamCnt::OnEnChangeEditStrage6(){ UDT; Get_Value(4, 5); }
void CEditDamCnt::OnEnChangeEditStrage7(){ UDT; Get_Value(4, 6); }
void CEditDamCnt::OnEnChangeEditStrage8(){ UDT; Get_Value(4, 7); }
void CEditDamCnt::OnEnChangeEditStrage9(){ UDT; Get_Value(4, 8); }
void CEditDamCnt::OnEnChangeEditStrage10(){ UDT; Get_Value(4, 9); }

void CEditDamCnt::OnEnChangeEditStartq1(){ UDT; Get_Value(5, 0); }
void CEditDamCnt::OnEnChangeEditStartq2(){ UDT; Get_Value(5, 1); }
void CEditDamCnt::OnEnChangeEditStartq3(){ UDT; Get_Value(5, 2); }
void CEditDamCnt::OnEnChangeEditStartq4(){ UDT; Get_Value(5, 3); }
void CEditDamCnt::OnEnChangeEditStartq5(){ UDT; Get_Value(5, 4); }
void CEditDamCnt::OnEnChangeEditStartq6(){ UDT; Get_Value(5, 5); }
void CEditDamCnt::OnEnChangeEditStartq7(){ UDT; Get_Value(5, 6); }
void CEditDamCnt::OnEnChangeEditStartq8(){ UDT; Get_Value(5, 7); }
void CEditDamCnt::OnEnChangeEditStartq9(){ UDT; Get_Value(5, 8); }
void CEditDamCnt::OnEnChangeEditStartq10(){ UDT; Get_Value(5, 9); }


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CEditDamCnt::Set_Data()
{
	CWnd*		cw;
	CString		str;
	int			id;
	//
	for (int i = 0; i < EDIT_DAMNUM; i++) {
		id = stNo + i;
		for (int k = 0; k < 6; k++) {
			cw = GetDlgItem(CON_ID[i][k]);
			if (id < DSET.Damc_Num) {
				if (k == 0)			str.Format("%d", stNo + i + 1);
				else if (k == 1)		str.Format("%s", DSET.DAMC[id].name);
				else if (k == 2)		str.Format("%d", DSET.DAMC[id].x + 1);
				else if (k == 3)		str.Format("%d", PM.MVnum - DSET.DAMC[id].y);
				else if (k == 4)		str.Format("%.0lf", DSET.DAMC[id].vol);
				else if (k == 5)		str.Format("%.1lf", DSET.DAMC[id].startq);
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
	if (DSET.Damc_Num % 10 == 0) EndLim = DSET.Damc_Num;
	else                  EndLim = ((int)(DSET.Damc_Num / 10) + 1) * 10;

	if (DSET.Damc_Num < 10) {
		c_BBack.EnableWindow(FALSE);
		c_BNext.EnableWindow(FALSE);
	}
	else if (stNo >= EndLim - 10 && stNo < EndLim) {
		c_BBack.EnableWindow(TRUE);
		c_BNext.EnableWindow(FALSE);
	}
	else {
		c_BBack.EnableWindow(TRUE);
		c_BNext.EnableWindow(TRUE);
	}
}

void CEditDamCnt::OnBnClickedOk()
{
	for (int i = 0; i < DSET.Damc_Num; i++) {
		if (strlen(DSET.DAMC[i].name) == 0) strcpy(DSET.DAMC[i].name, "-");
	}
	//
	CDialogEx::OnOK();
}




