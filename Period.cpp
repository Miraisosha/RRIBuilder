// Period.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Period.h"
#include "afxdialogex.h"
#include "RRI_Common.h"

int			PTIME_ID_NUM = 8;
int			PTIME_ID[] = { IDC_EDIT_201, IDC_EDIT_202, IDC_EDIT_203, IDC_EDIT_204,// IDC_EDIT_205,
				IDC_EDIT_206, IDC_EDIT_207, IDC_EDIT_208, IDC_EDIT_209 };// , IDC_EDIT_210};
extern		PARAMS			PM;

// CPeriod ダイアログ

IMPLEMENT_DYNAMIC(CPeriod, CDialogEx)

CPeriod::CPeriod(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeriod::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CPeriod::~CPeriod()
{
}

void CPeriod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPeriod, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_201, &CPeriod::OnEnChangeEdit201)
	ON_EN_CHANGE(IDC_EDIT_202, &CPeriod::OnEnChangeEdit202)
	ON_EN_CHANGE(IDC_EDIT_203, &CPeriod::OnEnChangeEdit203)
	ON_EN_CHANGE(IDC_EDIT_204, &CPeriod::OnEnChangeEdit204)
	ON_EN_CHANGE(IDC_EDIT_206, &CPeriod::OnEnChangeEdit206)
	ON_EN_CHANGE(IDC_EDIT_207, &CPeriod::OnEnChangeEdit207)
	ON_EN_CHANGE(IDC_EDIT_208, &CPeriod::OnEnChangeEdit208)
	ON_EN_CHANGE(IDC_EDIT_209, &CPeriod::OnEnChangeEdit209)
	ON_BN_CLICKED(IDOK, &CPeriod::OnBnClickedOk)
END_MESSAGE_MAP()


void CPeriod::Get_Period()
{
	CEdit*		ce;
	CString		str, year, mon, day, hour, min;
	BOOL			go;
	CTime		tt;
	int			iyear, imon, iday, ihour, imin;
	//
	go = FALSE;
	PM.StTime = PM.EndTime = NULL;
	for (int i = 0; i < 4; i++) {
		ce = (CEdit*)GetDlgItem(PTIME_ID[i]);
		ce->GetWindowTextA(str);
		if (str.GetLength() == 0) return;
		//
		if (i == 0 && str.GetLength() == 0) { break; }
		else {
			switch (i) {
			case 0: iyear = atoi(str); break;
			case 1: imon = atoi(str); break;
			case 2: iday = atoi(str); break;
			case 3: ihour = atoi(str);
				if (ihour == 24) {
					tt = CTime(iyear, imon, iday, 0, 0, 0, -1) + CTimeSpan(1l, 0, 0, 0);
					iyear = tt.GetYear(); imon = tt.GetMonth(); iday = tt.GetDay(); ihour = 0;
				}
				go = TRUE; break;
			}
		}
	}
	if (go) PM.StTime = ::CTime(iyear, imon, iday, ihour, 0, 0, -1);
	//
	go = FALSE;
	for (int i = 4; i < 8; i++) {
		ce = (CEdit*)GetDlgItem(PTIME_ID[i]);
		ce->GetWindowTextA(str);
		if (i == 0 && str.GetLength() == 0) { break; }
		else {
			switch (i) {
			case 4: iyear = atoi(str); break;
			case 5: imon = atoi(str); break;
			case 6: iday = atoi(str); break;
			case 7: ihour = atoi(str);
				if (ihour == 24) {
					tt = CTime(iyear, imon, iday, 0, 0, 0, -1) + CTimeSpan(1l, 0, 0, 0);
					iyear = tt.GetYear(); imon = tt.GetMonth(); iday = tt.GetDay(); ihour = 0;
				}
				go = TRUE; break;
			}
		}
	}
	if (go){
		PM.EndTime = ::CTime(iyear, imon, iday, ihour, 0, 0, -1);
	}
}


void CPeriod::OnEnChangeEdit201(){ UDT; }
void CPeriod::OnEnChangeEdit202(){ UDT; }
void CPeriod::OnEnChangeEdit203(){ UDT; }
void CPeriod::OnEnChangeEdit204(){ UDT; }
void CPeriod::OnEnChangeEdit206(){ UDT; }
void CPeriod::OnEnChangeEdit207(){ UDT; }
void CPeriod::OnEnChangeEdit208(){ UDT; }
void CPeriod::OnEnChangeEdit209(){ UDT; }

void CPeriod::OnBnClickedOk()
{
	Get_Period();
	CDialogEx::OnOK();
}
