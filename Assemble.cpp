// Assemble.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Assemble.h"
#include "afxdialogex.h"
//#include "AsEdit.h"

#include "RRI_Common.h"

extern		DATASET		DSET;
extern		PARAMS		PM;							// 基本情報
extern      MINFO**		MESH;

int			MOVE_ID[4] = { IDC_STATIC_REMLABEL, IDC_STATIC_REMAINS, IDOK, IDCANCEL };

// CAssemble ダイアログ

IMPLEMENT_DYNAMIC(CAssemble, CDialogEx)

CAssemble::CAssemble(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAssemble::IDD, pParent)
{

}

CAssemble::~CAssemble()
{
}

void CAssemble::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NEWLABEL, stc_NLabel);
	DDX_Control(pDX, IDC_STATIC_LABELS, stc_ASLabels);
	DDX_Control(pDX, IDC_STATIC_REMAINS, stc_Remains);
}


BEGIN_MESSAGE_MAP(CAssemble, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CAssemble::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CAssemble::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 
	Amem = Anum = DSET.LUnum;
	Assign = (int*)malloc(Amem*sizeof(int));
	for (int i = 0; i<Anum; i++) Assign[i] = UNDEF;
	param = (int*)malloc(Amem*sizeof(int));
	for (int i = 0; i<Anum; i++) param[i] = UNDEF;
	//
	Enum = 0;
	Emem = DSET.LUnum;
	if (Emem > 20) Emem = 20;
	//
	SetTimer(0, 10, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ENTER 処理
BOOL CAssemble::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		Relist_No(); return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AsEdit からのMessagevoid CAssemble::OnTimer(UINT_PTR nIDEvent)
void CAssemble::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);
	//
	Make_Dlg_Frame();
	//
	Disp_Stat();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AsEdit からのMessage
BOOL CAssemble::Make_Dlg_Frame()
{
	CRect	Rwin, Rname,Rdpos,RMs;
	CRect	Wrect, Mrect;
	CWnd*	cw;
	int		exX, exY, SX, SY;
	int		IDC;
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Window 枠の変更 
	this->GetWindowRect(&Wrect);

	stc_NLabel.GetWindowRect(&Rdpos);
	SX = Rdpos.left - Wrect.left;
	SY = Rdpos.bottom - Wrect.top + 10;
	//
	exY = SY + Emem*(EDIT_FRAME_H + 2) + 80;		// Excute Botton Height
	Wrect.top = Wrect.top - exY / 2;
	Wrect.bottom = Wrect.top + exY;
	this->MoveWindow(&Wrect, TRUE);
	this->RedrawWindow();
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Move Remain disp_Remain OK Cancel
	///
	this->GetClientRect(&Wrect);
	stc_Remains.GetClientRect(&RMs);
	//
	CRect  BTrect;
	for (int m = 0; m < 4; m++) {
		cw = GetDlgItem(MOVE_ID[m]);
		cw->GetClientRect(&BTrect);
		//
		switch (m) {
		case 0:Mrect.left = Wrect.left + 10; break;
		case 1:Mrect.left = Wrect.right - RMs.Width() - 15; break;
		case 2:Mrect.left = Wrect.right - (int)(BTrect.Width()*2.2); break;	// OK
		case 3:Mrect.left = Wrect.right - (int)(BTrect.Width()*1.1); break;	// Cancel
		}
		Mrect.right = Mrect.left + BTrect.Width();
		//
		if (m <2) Mrect.top = Wrect.bottom - 30 - BTrect.Height() - 10;
		else      Mrect.top = Wrect.bottom - 30;

		Mrect.bottom = Mrect.top + BTrect.Height();
		cw->MoveWindow(&Mrect, TRUE);
		cw->RedrawWindow();
	}
	// 
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Memory allocation  エディット枠
	///
	//	
	if ((Nlabel = (CAsEdit**)malloc(Emem*sizeof(void*))) == NULL ||
		(RowAsm = (CAsEdit**)malloc(Emem*sizeof(void*))) == NULL ||
		//(ParamNo = (CAsEdit**)malloc(Emem*sizeof(void*))) == NULL ||
		(ID_Name = (int*)malloc(Emem*sizeof(int))) == NULL ||
		//(ID_Pno = (int*)malloc(Emem*sizeof(int))) == NULL ||
		(ID_Row = (int*)malloc(Emem*sizeof(int))) == NULL )  return FALSE;

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// エディット枠 の作成
	///
	stc_NLabel.GetClientRect(&Rname);
	int		xst, yst,xrst;

	//  Ｆｉｌｌ　ＩＤ
	IDC = ID_INIT_ASM;
	xst = Rname.left + 20 ;
	yst = Rname.bottom + 20;
	for (int i = 0; i<Emem; i++) {
		ID_Name[i] = IDC++;
		Nlabel[i] = new CAsEdit;
		if (!Nlabel[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
			CRect(xst, yst, xst + Rname.Width(), yst + Rname.Height()), this, ID_Name[i])) return FALSE;
		Nlabel[i]->ID = i;
		memset(Nlabel[i]->Text, 0, 512);
		//
		ID_Row[i] = IDC++;
		xrst = Wrect.right - RMs.Width() -15;
		RowAsm[i] = new CAsEdit;
		if (!RowAsm[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
			CRect(xrst, yst, xrst + RMs.Width()-30, yst + Rname.Height()), this, ID_Row[i])) return FALSE;
		RowAsm[i]->ID = 100 + i;
		memset(RowAsm[i]->Text, 0, 512);
		//
		yst += (Rname.Height() + 5);
	}
	////
	return TRUE;
}

void CAssemble::Disp_Stat()	// 自由なところに入力できないように入力制限をかける。
{
	CString	str;
	for (int i = 0; i < Emem; i++) {
		if (i <= Enum) {
			str.Format("%d", i + 1);
			Nlabel[i]->SetWindowTextA(str);
		}
		Nlabel[i]->EnableWindow(FALSE);		// 新ラベルは必ず１、から連番
		//
		if (i <= Enum) {
			RowAsm[i]->EnableWindow(TRUE);
			//ParamNo[i]->EnableWindow(TRUE);
		}
		else {
			RowAsm[i]->EnableWindow(FALSE);
			//ParamNo[i]->EnableWindow(FALSE);
		}
	}
	CString		remain,add;
	int			cnt = 0;
	//
	remain = _T("");
	for (int i = 0; i < Anum; i++) {
		if (Assign[i] == UNDEF) {
			if(cnt != 0 )		add.Format(" ,%d", DSET.LUdata[i].NO);
			else				add.Format("%d", DSET.LUdata[i].NO);
			cnt++;
			remain = remain + add;
			if (cnt>24) { remain = remain + "...."; break; }
		}
	}
	stc_Remains.SetWindowTextA(remain);
	//
	if (remain.GetLength() == 0) REMAIN = FALSE;
	else                       REMAIN = TRUE;
}
void CAssemble::Relist_No()
{
	char*	buf;
	char		inchar[SIZE_01K];
	int		pos,row,cnt;
	int		No,tar,id;
	//
	for (int i = 0; i<Anum; i++) Assign[i] = UNDEF;
	//
	for (int i = 0; i <= Anum; i++) {
		if (strlen(RowAsm[i]->Text) != 0)  {
			buf = RowAsm[i]->Text;
			pos = 0; cnt = 0;
			while (getstr(buf, &pos, inchar, SIZE_01K) != EOF) {
				tar = atoi(inchar);
				Assign[tar-1] = i; 
				cnt++;
			}
		}
		else {
			Enum = i; break;
		}
	}
	//
	Disp_Stat();
}
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EXCUTE

void CAssemble::OnBnClickedOk()
{
	Relist_No();

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// CHECK
	if (REMAIN) {
		MessageBox("** Error ** Label remains...", "Warning", MB_OK | MB_ICONASTERISK);return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// メッシュ書き換え
	int id;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].flag == 0) continue;
			//
			id = (int)MESH[v][h].Lu -1;
			MESH[v][h].Lu = (short)(Assign[id] + 1 );
		}
	}
	//
	LUINFO*		LUback;
	if ((LUback = (LUINFO*)malloc(DSET.LUmem*sizeof(LUINFO))) == NULL) return;
	for (int i = 0; i < DSET.LUnum; i++) memcpy(&LUback[i], &DSET.LUdata[i], sizeof(LUINFO));
	//
	SAFE_FREE(DSET.LUdata);
	DSET.LUmem = DSET.LUnum = Enum;
	if ((DSET.LUdata = (LUINFO*)malloc(DSET.LUmem*sizeof(LUINFO))) == NULL) {
		SAFE_FREE(LUback); return;
	}
	//
	for (int i = 0; i < Enum; i++) {
		memcpy(&DSET.LUdata[i], &DSET.LU_Model, sizeof(LUINFO));
		DSET.LUdata[i].NO = i + 1;
	}
	//
	SAFE_FREE(LUback);
	//
	Free_All();
	CDialogEx::OnOK();
}

void CAssemble::OnCancel()
{
	Free_All();
	CDialogEx::OnCancel();
}
void CAssemble::Free_All()
{
	for (int i = 0; i < Emem; i++) {
		delete Nlabel[i];
		delete RowAsm[i];
		//delete ParamNo[i];
	}
	SAFE_FREE(Nlabel);
	SAFE_FREE(RowAsm);
	//SAFE_FREE(ParamNo);
	//
	SAFE_FREE(ID_Name);
	SAFE_FREE(ID_Row);
	//SAFE_FREE(ID_Pno);
	//
	SAFE_FREE(Assign);
//	SAFE_FREE(Ntemp);
	SAFE_FREE(param);

}