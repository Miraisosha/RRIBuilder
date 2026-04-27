// TimeVal.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "TimeVal.h"
#include "afxdialogex.h"

extern		SELECT_INFO		SI;
extern		PARAMS			PM;							// 基本情報

int  CON_ID[20][3] = { { IDC_EDIT_DAY_1, IDC_EDIT_SEC_1, IDC_EDIT_VAL_1 },
{ IDC_EDIT_DAY_2, IDC_EDIT_SEC_2, IDC_EDIT_VAL_2 },
{ IDC_EDIT_DAY_3, IDC_EDIT_SEC_3, IDC_EDIT_VAL_3 },
{ IDC_EDIT_DAY_4, IDC_EDIT_SEC_4, IDC_EDIT_VAL_4 },
{ IDC_EDIT_DAY_5, IDC_EDIT_SEC_5, IDC_EDIT_VAL_5 },
{ IDC_EDIT_DAY_6, IDC_EDIT_SEC_6, IDC_EDIT_VAL_6 },
{ IDC_EDIT_DAY_7, IDC_EDIT_SEC_7, IDC_EDIT_VAL_7 },
{ IDC_EDIT_DAY_8, IDC_EDIT_SEC_8, IDC_EDIT_VAL_8 },
{ IDC_EDIT_DAY_9, IDC_EDIT_SEC_9, IDC_EDIT_VAL_9 },
{ IDC_EDIT_DAY_10, IDC_EDIT_SEC_10, IDC_EDIT_VAL_10 },
{ IDC_EDIT_DAY_11, IDC_EDIT_SEC_11, IDC_EDIT_VAL_11 },
{ IDC_EDIT_DAY_12, IDC_EDIT_SEC_12, IDC_EDIT_VAL_12 },
{ IDC_EDIT_DAY_13, IDC_EDIT_SEC_13, IDC_EDIT_VAL_13 },
{ IDC_EDIT_DAY_14, IDC_EDIT_SEC_14, IDC_EDIT_VAL_14 },
{ IDC_EDIT_DAY_15, IDC_EDIT_SEC_15, IDC_EDIT_VAL_15 },
{ IDC_EDIT_DAY_16, IDC_EDIT_SEC_16, IDC_EDIT_VAL_16 },
{ IDC_EDIT_DAY_17, IDC_EDIT_SEC_17, IDC_EDIT_VAL_17 },
{ IDC_EDIT_DAY_18, IDC_EDIT_SEC_18, IDC_EDIT_VAL_18 },
{ IDC_EDIT_DAY_19, IDC_EDIT_SEC_19, IDC_EDIT_VAL_19 },
{ IDC_EDIT_DAY_20, IDC_EDIT_SEC_20, IDC_EDIT_VAL_20 } };

// CTimeVal ダイアログ

IMPLEMENT_DYNAMIC(CTimeVal, CDialogEx)

CTimeVal::CTimeVal(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeVal::IDD, pParent)
	, s_Num(_T(""))
	, s_Subttl(_T(""))
	, s_Title(_T(""))
	, s_Mv(_T(""))
	, s_Mh(_T(""))
	, s_Name(_T(""))
{

}

CTimeVal::~CTimeVal()
{
}

void CTimeVal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, c_BBack);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, c_Import);
	DDX_Control(pDX, IDC_BUTTON_DAILY, c_Daily);
	DDX_Control(pDX, IDC_BUTTON_NEXT, c_BNext);
	DDX_Text(pDX, IDC_STATIC_NUM, s_Num);
	DDX_Text(pDX, IDC_STATIC_SUBTTL, s_Subttl);
	DDX_Text(pDX, IDC_STATIC_TITLE, s_Title);
	DDX_Text(pDX, IDC_EDIT_V, s_Mv);
	DDX_Text(pDX, IDC_EDIT_H, s_Mh);
	DDX_Text(pDX, IDC_EDIT_NAME, s_Name);
}


BEGIN_MESSAGE_MAP(CTimeVal, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DAILY, &CTimeVal::OnBnClickedButtonDaily)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CTimeVal::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CTimeVal::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDOK, &CTimeVal::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CTimeVal::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_1, &CTimeVal::OnBnClickedButtonDelete1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_2, &CTimeVal::OnBnClickedButtonDelete2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_3, &CTimeVal::OnBnClickedButtonDelete3)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_4, &CTimeVal::OnBnClickedButtonDelete4)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_5, &CTimeVal::OnBnClickedButtonDelete5)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_6, &CTimeVal::OnBnClickedButtonDelete6)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_7, &CTimeVal::OnBnClickedButtonDelete7)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_8, &CTimeVal::OnBnClickedButtonDelete8)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_9, &CTimeVal::OnBnClickedButtonDelete9)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_10, &CTimeVal::OnBnClickedButtonDelete10)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_11, &CTimeVal::OnBnClickedButtonDelete11)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_12, &CTimeVal::OnBnClickedButtonDelete12)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_13, &CTimeVal::OnBnClickedButtonDelete13)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_14, &CTimeVal::OnBnClickedButtonDelete14)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_15, &CTimeVal::OnBnClickedButtonDelete15)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_16, &CTimeVal::OnBnClickedButtonDelete16)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_17, &CTimeVal::OnBnClickedButtonDelete17)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_18, &CTimeVal::OnBnClickedButtonDelete18)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_19, &CTimeVal::OnBnClickedButtonDelete19)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_20, &CTimeVal::OnBnClickedButtonDelete20)
END_MESSAGE_MAP()

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
BOOL CTimeVal::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	s_Title = Title;
	s_Subttl = Subttl;
	s_Num.Format("%d Points", SI.Num);
	if (SI.Num == 1) {
		s_Mh.Format("%d", SI.ID[0].x);
		s_Mv.Format("%d", SI.ID[0].y);
	}
	else {
		s_Mh = "Multi";
		s_Mv = "Multi";
	}
	CWnd*	cw = GetDlgItem(IDC_EDIT_H);	// メッシュ番号の無効か
	cw->EnableWindow(FALSE);
	cw = GetDlgItem(IDC_EDIT_V);
	cw->EnableWindow(FALSE);
	UDF;
	//
	if (!Decided) {			//　他の制約から時間が決まっていないもの

		CTimeSpan  CT = PM.EndTime - PM.StTime;
		MaxDay = Tnum = (int)(CT.GetTotalHours() / 24) + 1;
		Tmem = Tnum + 50;
		if ((Tsec = (int*)calloc(Tmem, sizeof(int))) == NULL ||
			(Tday = (double*)calloc(Tmem, sizeof(double))) == NULL ||
			(Val = (double*)calloc(Tmem, sizeof(double))) == NULL) return FALSE;
		for (int i = 0; i < Tnum; i++) {
			Tday[i] = (double)i;
			Tsec[i] = (int)(Tday[i] * 86400);
			Val[i] = DUNDEF;
		}
	}
	//
	stNo = 0;
	Set_Data();
	return TRUE;  
}

BOOL CTimeVal::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN) { Research_Data(); return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CTimeVal::Set_Data()
{
	int			it;
	CWnd 		*cw,*cd,*cv;
	CString		strs,strd,strv;
	//
	if (Tnum != 0) {			// 動かせない。
		for (int t = 0; t < EDIT_TVNUM; t++) {
			it = t + stNo;
			cw = GetDlgItem(CON_ID[t][1]);
			cd = GetDlgItem(CON_ID[t][0]);
			cv = GetDlgItem(CON_ID[t][2]);
			//
			strs = strd = strv = "";
			if (it < Tnum) {
				strs.Format("%d",		Tsec[it]);
				strd.Format("%.1lf",	Tday[it]);

				if (Val[it] != DUNDEF ) strv.Format("%.2lf", Val[it]);
			}
			cv->SetWindowTextA(strv);
			cd->SetWindowTextA(strd);
			cw->SetWindowTextA(strs);
			//
			if(it >= Tnum) {
				cw->EnableWindow(FALSE);
				cd->EnableWindow(FALSE);
				cv->EnableWindow(FALSE);
			}
			else {
				cw->EnableWindow(TRUE);
				cd->EnableWindow(TRUE);
				cv->EnableWindow(TRUE);
			}
		}
	}
	UDF;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Set Daily
void CTimeVal::OnBnClickedButtonDaily()
{
	int			it;
	CWnd			*cd, *cs;
	CString		strd, strs;
	//
	for (int t = 0; t < Tmem; t++) {
		Tday[t] = t;
		Tsec[t] = t * 86400;
	}
	for (int t = 0; t < EDIT_TVNUM;t++){
		it = t + stNo;
		cd = GetDlgItem(CON_ID[t][0]);
		cs = GetDlgItem(CON_ID[t][1]);
		//
		strs.Format("%d", Tsec[it]);
		strd.Format("%.0lf", Tday[it]);
		//
		cd->SetWindowTextA(strd);
		cs->SetWindowTextA(strs);
	}
	UDF;
}

void CTimeVal::OnBnClickedButtonBack()
{
	Get_Data();
	if (stNo != 0 ) stNo -= EDIT_TVNUM;
	Set_Data();
}

void CTimeVal::OnBnClickedButtonNext()
{
	Get_Data();
	if (Tnum >= (stNo + EDIT_TVNUM)) {
		stNo += EDIT_TVNUM;
		Set_Data();
	}
}

void CTimeVal::OnEnChangeEditName() { UDT; }
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Set Daily
void CTimeVal::Get_Data()
{
	int			it;
	CEdit		*ce,*cs;
	CString		str;
	//
	for (int i = 0; i < EDIT_TVNUM; i++) {
		it = i + stNo;
		if (it >= Tnum) continue;
		//
		for (int k = 0; k < 3; k++) {
			ce = (CEdit*)GetDlgItem(CON_ID[i][k]);
			if (ce->GetModify()){
				ce->GetWindowTextA(str);
				switch (k){
				case 0:	if (!Decided) {
							Tday[it] = atof(str);
							Tsec[it] = (int)(Tday[it] * 86400.);
							cs = (CEdit*)GetDlgItem(CON_ID[i][1]);
							str.Format("%d", Tsec[it]); UDF;
						}
						break;
				case 1:	if (!Decided) {
							Tsec[it] = atoi(str);
							Tday[it] = Tsec[it] / 86400.;
							cs = (CEdit*)GetDlgItem(CON_ID[i][0]);
							str.Format("%.1lf", Tday[it]); UDF;
						}
						break;
				case 2: if(str.GetLength() != 0 ) Val[it] = atof(str);
						else  Val[it] = DUNDEF;
						break;
				}
			}
		}
	}
	Set_Data();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RETURN

void CTimeVal::OnBnClickedOk()
{
	Get_Data();
	//
	int		cnt = 0;
	for (int i = 0; i < Tnum; i++) {
		if (Val[i] != DUNDEF) cnt++;
	}
	if (cnt != Tnum) {
		if (MessageBox("**Error** Deficient number of data... Exit ?", "Warning", MB_YESNO | MB_ICONHAND) == IDNO) return;
		CDialogEx::OnCancel();
	}
	//
	else {
		char		buf[SIZE_1K];
		strcpy(buf, s_Name);			// 空白文字を消す。
		for (int i = 0; i < strlen(buf); i++) {
			if (buf[i] == ' ') buf[i] = '_';
		}
		SI_Name = buf;
		//
		CDialogEx::OnOK();
	}
}

void CTimeVal::Research_Data()		// おもに日時に変化があった場合
{
	if (Decided) {
		Set_Data();
		return;
	}
	//
	int			it,insec;
	double		inday;
	CEdit		*cd, *ce;
	CString		str;
	BOOL			change = FALSE;
	//
	for (int i = 0; i < EDIT_TVNUM; i++) {
		cd = (CEdit*)GetDlgItem(CON_ID[i][0]);
		ce = (CEdit*)GetDlgItem(CON_ID[i][1]);
		//
		if (cd->GetModify()) {
			cd->GetWindowTextA(str);
			inday = atof(str);
			//
			if (inday > MaxDay) {
				str.Format(".1lf", Tday[i + stNo]);
				cd->SetWindowTextA(str); break;
			}
			//
			it = i + stNo;
			Tday[it] = inday;
			Tsec[it] = (int)(inday*86400.);
			change = TRUE; break;
		}
		else if (ce->GetModify()) {
			ce->GetWindowTextA(str);
			insec = atoi(str);
			//
			inday = insec/ 86400.;
			if (inday > MaxDay) {
				str.Format("%d", Tsec[i + stNo]);
				ce->SetWindowTextA(str); break;
			}
			//
			it = i + stNo;
			Tday[it] = inday;
			Tsec[it] = insec;
			change = TRUE; break;
		}
	}
	//
	if (!change) return;
	//
	int		times;
	double   Remain = (double)MaxDay - Tday[it];
	//
	if (fmod(Remain, 1.) == 0.) times = (int)Remain;
	else                      times = (int)Remain + 1;
	//
	Tnum = it + times;
	for (int i = 0; i < times; i++) {
		Tday[i + it+1] = (int)(Tday[it] + 1) + i;
		Tsec[i + it+1] = (int)(Tday[i + it+1] * 86400.);
	}
	Set_Data();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ＤＥＬＥＴＥ
void CTimeVal::Time_Delete(int no)
{
	int ID = no + stNo;
	//
	if (ID < Tnum) {
		if (Decided) {
			MessageBox("Time series are already defined.\n-----> Cannot delete...", "Neglect", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		for (int i = ID; i < Tnum-1; i++){
			Tsec[i] = Tsec[i + 1];
			Tday[i] = Tday[i + 1];
			Val[i] = Val[i + 1];
		}
		Tnum--;
		if (stNo != 0){
			if (Tnum%stNo == 0) stNo--;
		}
		Set_Data();
	}
}
void CTimeVal::OnBnClickedButtonDelete1(){ Time_Delete(0); }
void CTimeVal::OnBnClickedButtonDelete2(){ Time_Delete(1); }
void CTimeVal::OnBnClickedButtonDelete3(){ Time_Delete(2); }
void CTimeVal::OnBnClickedButtonDelete4(){ Time_Delete(3); }
void CTimeVal::OnBnClickedButtonDelete5(){ Time_Delete(4); }
void CTimeVal::OnBnClickedButtonDelete6(){ Time_Delete(5); }
void CTimeVal::OnBnClickedButtonDelete7(){ Time_Delete(6); }
void CTimeVal::OnBnClickedButtonDelete8(){ Time_Delete(7); }
void CTimeVal::OnBnClickedButtonDelete9(){ Time_Delete(8); }
void CTimeVal::OnBnClickedButtonDelete10(){ Time_Delete(9); }
void CTimeVal::OnBnClickedButtonDelete11(){ Time_Delete(10); }
void CTimeVal::OnBnClickedButtonDelete12(){ Time_Delete(11); }
void CTimeVal::OnBnClickedButtonDelete13(){ Time_Delete(12); }
void CTimeVal::OnBnClickedButtonDelete14(){ Time_Delete(13); }
void CTimeVal::OnBnClickedButtonDelete15(){ Time_Delete(14); }
void CTimeVal::OnBnClickedButtonDelete16(){ Time_Delete(15); }
void CTimeVal::OnBnClickedButtonDelete17(){ Time_Delete(16); }
void CTimeVal::OnBnClickedButtonDelete18(){ Time_Delete(17); }
void CTimeVal::OnBnClickedButtonDelete19(){ Time_Delete(18); }
void CTimeVal::OnBnClickedButtonDelete20(){ Time_Delete(19); }