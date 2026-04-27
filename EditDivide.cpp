// EditDivide.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "EditDivide.h"
#include "afxdialogex.h"

extern		DATASET			DSET;
extern		PARAMS			PM;
extern		MINFO**			MESH;

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int  CONV_ID[10][6] = { { IDC_NO_1, IDC_LNG_1, IDC_LAT_1, IDC_LNG_11, IDC_LAT_11, IDC_EDIT_RATE_1 },
				{ IDC_NO_2, IDC_LNG_2, IDC_LAT_2, IDC_LNG_12, IDC_LAT_12, IDC_EDIT_RATE_2 },
				{ IDC_NO_3, IDC_LNG_3, IDC_LAT_3, IDC_LNG_13, IDC_LAT_13, IDC_EDIT_RATE_3 },
				{ IDC_NO_4, IDC_LNG_4, IDC_LAT_4, IDC_LNG_14, IDC_LAT_14, IDC_EDIT_RATE_4 },
				{ IDC_NO_5, IDC_LNG_5, IDC_LAT_5, IDC_LNG_15, IDC_LAT_15, IDC_EDIT_RATE_5 },
				{ IDC_NO_6, IDC_LNG_6, IDC_LAT_6, IDC_LNG_16, IDC_LAT_16, IDC_EDIT_RATE_6 },
				{ IDC_NO_7, IDC_LNG_7, IDC_LAT_7, IDC_LNG_17, IDC_LAT_17, IDC_EDIT_RATE_7 },
				{ IDC_NO_8, IDC_LNG_8, IDC_LAT_8, IDC_LNG_18, IDC_LAT_18, IDC_EDIT_RATE_8 },
				{ IDC_NO_9, IDC_LNG_9, IDC_LAT_9, IDC_LNG_19, IDC_LAT_19, IDC_EDIT_RATE_9 },
				{ IDC_NO_10, IDC_LNG_10, IDC_LAT_10, IDC_LNG_20, IDC_LAT_20, IDC_EDIT_RATE_10 } };
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//


// CEditDivide ダイアログ

IMPLEMENT_DYNAMIC(CEditDivide, CDialogEx)

CEditDivide::CEditDivide(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDivide::IDD, pParent)
{

}

CEditDivide::~CEditDivide()
{
}

void CEditDivide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK2, c_BBack);
	DDX_Control(pDX, IDC_BUTTON_NEXT2, c_BNext);
}


BEGIN_MESSAGE_MAP(CEditDivide, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL_7, &CEditDivide::OnBnClickedButtonDel7)
	ON_BN_CLICKED(IDC_BUTTON_DEL_8, &CEditDivide::OnBnClickedButtonDel8)
	ON_BN_CLICKED(IDC_BUTTON_DEL_9, &CEditDivide::OnBnClickedButtonDel9)
	ON_BN_CLICKED(IDC_BUTTON_DEL_10, &CEditDivide::OnBnClickedButtonDel10)
	ON_BN_CLICKED(IDC_BUTTON_DEL_11, &CEditDivide::OnBnClickedButtonDel11)
	ON_BN_CLICKED(IDC_BUTTON_DEL_12, &CEditDivide::OnBnClickedButtonDel12)
	ON_BN_CLICKED(IDC_BUTTON_DEL_13, &CEditDivide::OnBnClickedButtonDel13)
	ON_BN_CLICKED(IDC_BUTTON_DEL_14, &CEditDivide::OnBnClickedButtonDel14)
	ON_BN_CLICKED(IDC_BUTTON_DEL_15, &CEditDivide::OnBnClickedButtonDel15)
	ON_BN_CLICKED(IDC_BUTTON_DEL_16, &CEditDivide::OnBnClickedButtonDel16)
	ON_BN_CLICKED(IDC_BUTTON_BACK2, &CEditDivide::OnBnClickedButtonBack2)
	ON_BN_CLICKED(IDC_BUTTON_NEXT2, &CEditDivide::OnBnClickedButtonNext2)
	ON_EN_CHANGE(IDC_EDIT_RATE_1, &CEditDivide::OnEnChangeEditRate1)
	ON_EN_CHANGE(IDC_EDIT_RATE_2, &CEditDivide::OnEnChangeEditRate2)
	ON_EN_CHANGE(IDC_EDIT_RATE_3, &CEditDivide::OnEnChangeEditRate3)
	ON_EN_CHANGE(IDC_EDIT_RATE_4, &CEditDivide::OnEnChangeEditRate4)
	ON_EN_CHANGE(IDC_EDIT_RATE_5, &CEditDivide::OnEnChangeEditRate5)
	ON_EN_CHANGE(IDC_EDIT_RATE_6, &CEditDivide::OnEnChangeEditRate6)
	ON_EN_CHANGE(IDC_EDIT_RATE_7, &CEditDivide::OnEnChangeEditRate7)
	ON_EN_CHANGE(IDC_EDIT_RATE_8, &CEditDivide::OnEnChangeEditRate8)
	ON_EN_CHANGE(IDC_EDIT_RATE_9, &CEditDivide::OnEnChangeEditRate9)
	ON_EN_CHANGE(IDC_EDIT_RATE_10, &CEditDivide::OnEnChangeEditRate10)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_1, &CEditDivide::OnBnClickedButtonExchange1)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_2, &CEditDivide::OnBnClickedButtonExchange2)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_3, &CEditDivide::OnBnClickedButtonExchange3)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_4, &CEditDivide::OnBnClickedButtonExchange4)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_5, &CEditDivide::OnBnClickedButtonExchange5)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_6, &CEditDivide::OnBnClickedButtonExchange6)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_7, &CEditDivide::OnBnClickedButtonExchange7)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_8, &CEditDivide::OnBnClickedButtonExchange8)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_9, &CEditDivide::OnBnClickedButtonExchange9)
	ON_BN_CLICKED(IDC_BUTTON_EXCHANGE_10, &CEditDivide::OnBnClickedButtonExchange10)
	ON_BN_CLICKED(IDOK, &CEditDivide::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditDivide メッセージ ハンドラー


BOOL CEditDivide::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	stNo = 0;
	Set_Data();

	return TRUE; 
}
void CEditDivide::Del_this(int id)
{
	int  cnt = 0;
	//
	id += stNo;
	//
	if (id >= DSET.Div_Num) return;

	if (DSET.Div_Num == 1) {
		if (MessageBox("Invalidate diversion condition ? ", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDNO) return;
		if (MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)
			MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].flag = ID_MESH_R;
		else		MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].flag = ID_MESH;
		//
		MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].name[0] = 0x00;
		//
		if (MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)
			MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].flag = ID_MESH_R;
		else		MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].flag = ID_MESH;
		//
		SAFE_FREE(DSET.DIVID);
		DSET.Div_Num = DSET.Div_Mem = 0;
		//
		CDialogEx::OnOK(); return;
	}
	for (int i = 0; i < DSET.Div_Num; i++) {
		if (i == id) {
			if (MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)
					MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].flag = ID_MESH_R;
			else		MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].flag = ID_MESH;
			MESH[DSET.DIVID[id].oy][DSET.DIVID[id].ox].name[0] = 0x00;
			if (MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)
				MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].flag = ID_MESH_R;
			else		MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].flag = ID_MESH;
			MESH[DSET.DIVID[id].ty][DSET.DIVID[id].tx].name[0] = 0x00;
			continue;
		}
		else {
			memcpy(&DSET.DIVID[cnt], &DSET.DIVID[i], sizeof(DIVISION));
			cnt++;
		}
	}
	DSET.Div_Num = cnt;
	//
	if (DSET.Div_Num != 0 && DSET.Div_Num == stNo) stNo -= 10;
	//
	Set_Data();
}

void CEditDivide::OnBnClickedButtonDel7() { Del_this(0); }
void CEditDivide::OnBnClickedButtonDel8() { Del_this(1); }
void CEditDivide::OnBnClickedButtonDel9() { Del_this(2); }
void CEditDivide::OnBnClickedButtonDel10() { Del_this(3); }
void CEditDivide::OnBnClickedButtonDel11() { Del_this(4); }
void CEditDivide::OnBnClickedButtonDel12() { Del_this(5); }
void CEditDivide::OnBnClickedButtonDel13() { Del_this(6); }
void CEditDivide::OnBnClickedButtonDel14() { Del_this(7); }
void CEditDivide::OnBnClickedButtonDel15() { Del_this(8); }
void CEditDivide::OnBnClickedButtonDel16() { Del_this(9); }

void CEditDivide::OnBnClickedButtonBack2()
{
	stNo -= 10;
	Set_Data();
}

void CEditDivide::OnBnClickedButtonNext2()
{
	stNo += 10;
	Set_Data();
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CEditDivide::Set_Data()
{
	CWnd*		cw;
	CString		str;
	int			id;
	//
	for (int i = 0; i < EDIT_NUM; i++) {
		id = stNo + i;
		for (int k = 0; k < 6; k++) {
			cw = GetDlgItem(CONV_ID[i][k]);
			if (id < DSET.Div_Num) {
				if (k == 0)			str.Format("%d", stNo + i + 1);
				else if (k == 1)		str.Format("%d", DSET.DIVID[id].ox+1);
				else if (k == 2)		str.Format("%d", PM.MVnum - DSET.DIVID[id].oy);
				else if (k == 3)		str.Format("%d", DSET.DIVID[id].tx + 1);
				else if (k == 4)		str.Format("%d", PM.MVnum - DSET.DIVID[id].ty);
				else if (k == 5)	{
					str = "";
					if (DSET.DIVID[id].rate != 0.) str.Format("%.3lf", DSET.DIVID[id].rate);
				}
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
	if (DSET.Div_Num % 10 == 0) EndLim = DSET.Div_Num;
	else                  EndLim = ((int)(DSET.Div_Num / 10) + 1) * 10;

	if (DSET.Div_Num < 10) {
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


void CEditDivide::Get_Value(int no)
{
	CWnd*		cw = GetDlgItem(CONV_ID[no][5]);
	char			name[64];
	cw->GetWindowTextA(name, 64);
	//
	DSET.DIVID[stNo + no].rate = atof(name);
}


void CEditDivide::OnEnChangeEditRate1() { UDT; Get_Value(0); }
void CEditDivide::OnEnChangeEditRate2(){ UDT; Get_Value(1); }
void CEditDivide::OnEnChangeEditRate3(){ UDT; Get_Value(2); }
void CEditDivide::OnEnChangeEditRate4(){ UDT; Get_Value(3); }
void CEditDivide::OnEnChangeEditRate5(){ UDT; Get_Value(4); }
void CEditDivide::OnEnChangeEditRate6(){ UDT; Get_Value(5); }
void CEditDivide::OnEnChangeEditRate7(){ UDT; Get_Value(6); }
void CEditDivide::OnEnChangeEditRate8(){ UDT; Get_Value(7); }
void CEditDivide::OnEnChangeEditRate9(){ UDT; Get_Value(8); }
void CEditDivide::OnEnChangeEditRate10(){ UDT; Get_Value(9); }

void CEditDivide::Exchange(int no)
{
	int  X, Y,id = stNo+no;
	X = DSET.DIVID[id].ox;
	Y = DSET.DIVID[id].oy;

	DSET.DIVID[id].ox = DSET.DIVID[id].tx;
	DSET.DIVID[id].oy = DSET.DIVID[id].ty;

	DSET.DIVID[id].tx = X;
	DSET.DIVID[id].ty = Y;

	Set_Data();
}

void CEditDivide::OnBnClickedButtonExchange1() { Exchange(0); }
void CEditDivide::OnBnClickedButtonExchange2() { Exchange(1); }
void CEditDivide::OnBnClickedButtonExchange3() { Exchange(2); }
void CEditDivide::OnBnClickedButtonExchange4() { Exchange(3); }
void CEditDivide::OnBnClickedButtonExchange5() { Exchange(4); }
void CEditDivide::OnBnClickedButtonExchange6() { Exchange(5); }
void CEditDivide::OnBnClickedButtonExchange7() { Exchange(6); }
void CEditDivide::OnBnClickedButtonExchange8() { Exchange(7); }
void CEditDivide::OnBnClickedButtonExchange9() { Exchange(8); }
void CEditDivide::OnBnClickedButtonExchange10() { Exchange(9); }




void CEditDivide::OnBnClickedOk()
{
	for (int i = 0; i < DSET.Div_Num; i++) {
		if (strlen(DSET.DIVID[i].name) == 0) strcpy(DSET.DIVID[i].name, "-");
	}
	CDialogEx::OnOK();
}
