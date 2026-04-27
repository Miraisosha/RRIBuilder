// TSEditDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "RRI_GUIView.h"
#include "TSEditDlg.h"
#include "afxdialogex.h"

#include		"Period.h"

#include		"CommFuncs.h"
//#include "RRI_Common.h"


//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
extern      char			m_RecentPath[SIZE_1K];
extern      int			CDATA;							// 現在対象のデータ
extern      PARAMS		PM;								// 基本情報
extern      DATASET		DSET;							// ファイルセット
extern      int			File_Format[  ]; 
extern      CString		MODEL_EDIT_NAME[];
extern      CString		File_Title[];
extern		MINFO**		MESH;

int			INFO_ID[] = { IDC_INFO_NO_0, IDC_INFO_NO_1, IDC_INFO_NO_2, IDC_INFO_NO_3, IDC_INFO_NO_4,
						IDC_INFO_NO_5, IDC_INFO_NO_6, IDC_INFO_NO_7, IDC_INFO_NO_8, IDC_INFO_NO_9,
						IDC_INFO_NO_10, IDC_INFO_NO_11, IDC_INFO_NO_12, IDC_INFO_NO_13, IDC_INFO_NO_14,
						IDC_INFO_NO_15, IDC_INFO_NO_16, IDC_INFO_NO_17, IDC_INFO_NO_18, IDC_INFO_NO_19 };
//
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////

// CTSEditDlg ダイアログ

IMPLEMENT_DYNAMIC(CTSEditDlg, CDialogEx)

CTSEditDlg::CTSEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTSEditDlg::IDD, pParent)
{

	m_Num = _T("");
	m_Tspan = _T("");
}

CTSEditDlg::~CTSEditDlg()
{
}
void CTSEditDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	//
	Free_All(TRUE);
}
void CTSEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_MESH_FROM, c_Mfrom);
	DDX_Control(pDX, IDC_INFO_NAME, c_Name);
	DDX_Text(pDX, IDC_INFO_NUM, m_Num);
	DDX_Text(pDX, IDC_INFO_TIME, m_Tspan);
	DDX_Control(pDX, IDC_BUTTON_DOWN, c_Down);
	DDX_Control(pDX, IDC_BUTTON_LEFT, c_Left);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, c_Right);
	DDX_Control(pDX, IDC_CHECK_UP, c_Up);
	DDX_Control(pDX, IDC_BUTTON_SETDAY, c_SetDaily);
}


BEGIN_MESSAGE_MAP(CTSEditDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTSEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SAVE_AS, &CTSEditDlg::OnBnClickedSaveAs)
	ON_BN_CLICKED(IDC_BUTTON_ADD_T, &CTSEditDlg::OnBnClickedButtonAddT)
	ON_BN_CLICKED(IDC_BUTTON_DEL_T, &CTSEditDlg::OnBnClickedButtonDelT)
	ON_BN_CLICKED(IDC_BUTTON_DEL_P, &CTSEditDlg::OnBnClickedButtonDelP)
	ON_WM_PAINT()
	ON_MESSAGE(WM_ASEDIT_FOCUS, &CTSEditDlg::OnAseditFocus)
	ON_BN_CLICKED(IDC_BUTTON_SETDAY, &CTSEditDlg::OnBnClickedButtonSetday)
	ON_BN_CLICKED(IDC_CHECK_UP, &CTSEditDlg::OnBnClickedCheckUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CTSEditDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CTSEditDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CTSEditDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CTSEditDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CTSEditDlg::OnBnClickedButtonImport)
END_MESSAGE_MAP()


///-----------------------------------------------------------------------------------------------------------
//  初期化
///-----------------------------------------------------------------------------------------------------------

BOOL CTSEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//
//  Title
	CString		str;

	Data_ID = CDATA;
	str.Format("Edit..%s",MODEL_EDIT_NAME[ Data_ID ]);
	this->SetWindowTextA(str);

	Result = Data_Change_Cnt = 0;
	//
	Edits_ID = NULL;
	Name_ID = MFX_ID = MFY_ID =  NULL;
	SetTimer(0,10,NULL);
	//
	return TRUE;
}
void CTSEditDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
}

//
///-----------------------------------------------------------------------------------------------------------
//   タイマー
///-----------------------------------------------------------------------------------------------------------
//
void CTSEditDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0) {
		KillTimer(0);
		//---------------------------------------------------------
		//  数値のセットとデータコピー
		TIMESET*	TT;
		//
		if (Data_ID == HS_WLEV_FILE)				TT = &DSET.HSWLEV;
		else if (Data_ID == HR_WLEV_FILE)			TT = &DSET.HRWLEV;
		else if (Data_ID == QS_WLEV_FILE)			TT = &DSET.QSWLEV;
		else if (Data_ID == QR_WLEV_FILE)			TT = &DSET.QRWLEV;
		else return;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//	時刻設定
		if (PM.StTime == NULL) {
			CPeriod  CP;
			if (CP.DoModal() == IDCANCEL) CDialogEx::OnCancel();	// PM.stTime に設定
		}
		CT = ST = PM.StTime;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// TS にコピーしてキャンセルに備える
		memset(&TS, 0, sizeof(TIMESET));
		Copy_TIMESET(&TS, TT);
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 初期設定

		ShowH = Hnum = TS.Num;
		if (ShowH > POS_MAX) ShowH = POS_MAX;
		ShowV = Vnum = TS.Span;
		if (ShowV > SPAN_MAX) ShowV = SPAN_MAX;
		//
		if (Vnum == 0) c_SetDaily.ShowWindow(SW_SHOW);
		else          c_SetDaily.ShowWindow(SW_HIDE);
		//
		stH = stV = 0;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//  AsEdit フレームを作成
		if (!Init_Set_Edits()) {
			MessageBox("** Error ** Initialize CEdit or memory allocation", "Error", MB_OK); return;
		}
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 値の設定　と編集開始

		if (!Set_Edit_Value()) return;
		Lrow = Lcol = UNDEF;
	}
}
//
//-----------------------------------------------------------------------------------------------------------
//  MAKE EDITS
//
BOOL	 CTSEditDlg::Init_Set_Edits()
{
	CRect	Rwin,Rname,Rfrom,Rto,Rdpos,Rtop,Rrate;
	CRect	Wrect,Mrect;
	CWnd*	cw;
	int		exX,exY,SX,SY;	
	//
	//
	// Window 枠の変更  
	this->GetWindowRect( &Wrect );			// 起動の枠が最少
	//
	PM.TSDLG_minH = Wrect.Width();
	PM.TSDLG_minV = Wrect.Height();

	// ウィンドウの大きさ設定と移動　Cell No 枠を基準とする。
	//
	c_Mfrom.GetWindowRect(&Rdpos);
	//
	SX = Rdpos.right - Wrect.left;
	SY = Rdpos.top - Wrect.top;
	//
	ShowH = TS.Num;
	if (ShowH > POS_MAX) ShowH = POS_MAX;
	exX = SX + ShowH*(X_TS_SIZE + 2) + WINDOW_FRAME;
	if (exX < PM.TSDLG_minH) 	exX = PM.TSDLG_minH;
	//
	// 注意 固定
	exY =  Wrect.Height();

	Wrect.right = Wrect.left + exX;
	if( exY > PM.TSDLG_minV ) Wrect.bottom = Wrect.top + PM.TSDLG_minV;
	else                              Wrect.bottom = Wrect.top + exY;
	this->MoveWindow(&Wrect,TRUE);
	this->RedrawWindow();
	//
	//
	this->GetClientRect( &Wrect );

	// Save Save As Cancel ボタンの移動
	// 
	CRect	BTrect;
	//
	if (ShowH > 3) {
		cw = GetDlgItem(IDOK);
		cw->GetClientRect(&BTrect);
		exX = BTrect.Width();
		Mrect.left = Wrect.right - (int)(3.1*exX);  
		Mrect.right = Mrect.left + exX;
//		Mrect.top = (exY - WINDOW_FRAME) - BTrect.Height() - 1;  
		Mrect.top = Wrect.bottom  - BTrect.Height() - 10;
		Mrect.bottom = Mrect.top + BTrect.Height() ;
		cw->MoveWindow(&Mrect, TRUE);
		cw->RedrawWindow();
		//
		cw = GetDlgItem(IDC_SAVE_AS);
		cw->GetClientRect(&BTrect);
		exX = BTrect.Width();
		Mrect.left = Wrect.right - (int)(2.1*exX);  
		Mrect.right = Mrect.left + exX;
		Mrect.top = Wrect.bottom - BTrect.Height() - 10;
		Mrect.bottom = Mrect.top + BTrect.Height();
		cw->MoveWindow(&Mrect, TRUE);
		cw->RedrawWindow();
		//
		cw = GetDlgItem(IDCANCEL);
		cw->GetClientRect(&BTrect);
		exX = BTrect.Width();
		Mrect.left = Wrect.right - (int)(1.1*exX);  
		Mrect.right = Mrect.left + exX;
		Mrect.top = Wrect.bottom  - BTrect.Height() - 10;
		Mrect.bottom = Mrect.top + BTrect.Height();
		cw->MoveWindow(&Mrect, TRUE);
		cw->RedrawWindow();
	}
	//
	this->GetWindowRect( &Wrect );
	// 
	c_Name.GetWindowRect( &Rname );
	c_Mfrom.GetWindowRect( &Rfrom );
	//
	// Data allocation  ID
	if ((Name_ID = (int*)malloc(ShowH*sizeof(int))) == NULL ||						// ShowH はPOS_MAXが最大
		(MFX_ID = (int*)malloc(ShowH*sizeof(int))) == NULL ||
		(MFY_ID = (int*)malloc(ShowH*sizeof(int))) == NULL) return FALSE;

	if( (Times_ID=(int*)malloc(SPAN_MAX*sizeof( int ) )) == NULL  ) return FALSE;	// 20 まで
	//
	Edits_ID = Make_Matrix(ShowH, SPAN_MAX, 0);
	//
	// ＩＤの埋め込み
	int  cid = ID_TS_INIT;
	for(int i=0;i<ShowH;i++) {Name_ID[i] = cid++; MFX_ID[i] = cid++; MFY_ID[i] = cid++;}
	for (int i = 0; i<SPAN_MAX; i++) Times_ID[i] = cid++;

	for (int v = 0; v<SPAN_MAX; v++) {
		for(int h=0;h<ShowH;h++) Edits_ID[v][h] = cid++;
	}
	// Memory allocation  エディット枠
	//	
	if ((Edits = (CAsEdit***)malloc(ShowH*SPAN_MAX*sizeof(void *))) == NULL ||
		(Names = (CAsEdit**)malloc(ShowH*sizeof(void *))) == NULL ||
		(MFXs = (CAsEdit**)malloc(ShowH*sizeof(void *))) == NULL ||
		(MFYs = (CAsEdit**)malloc(ShowH*sizeof(void *))) == NULL ||
		(Times = (CAsEdit**)malloc(SPAN_MAX*sizeof(void *))) == NULL)  return FALSE;

	for (int i = 0; i<SPAN_MAX; i++) {
		if ((Edits[i] = (CAsEdit**)malloc(ShowH*sizeof(void *))) == NULL) {
			while( i >= 0 ) SAFE_FREE( Edits[i--] ); SAFE_FREE( Edits );  return FALSE;}
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// エディット枠 の作成
	
	int		xst,yst;

	//  name
	xst = Rname.right - Wrect.left + 1;
	yst = Rname.top - Wrect.top - WINDOW_FRAME;
	Name_VP = yst;
	for(int i=0;i<ShowH;i++) {
		Names[i] = new CAsEdit;
		if (!Names[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
							CRect(xst, yst, xst+X_TS_SIZE,yst+Y_TS_SIZE), this, Name_ID[i]) ) return FALSE;
		Names[i]->finfo.kind = 0;
		Names[i]->finfo.x = i;
		Names[i]->finfo.y = 0;
		Names[i]->pP = this;
		xst += (X_TS_SIZE + 2);
	}

	// Mesh Pos (from)
	xst = Rfrom.right - Wrect.left + 1;
	yst = Rfrom.top  - Wrect.top - WINDOW_FRAME;
	MF_VP = yst;
	for (int i = 0; i<ShowH; i++) {
		MFXs[i] = new CAsEdit;
		if (!MFXs[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
							CRect(xst, yst, xst+X_POS_SIZE,yst+Y_TS_SIZE), this, MFX_ID[i]) ) return FALSE;
		MFXs[i]->finfo.kind = 1;
		MFXs[i]->finfo.x = i;
		MFXs[i]->finfo.y = 0;
		MFXs[i]->pP = this;

		xst += (X_POS_SIZE + 2);
		MFYs[i] = new CAsEdit;
		if (!MFYs[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
							CRect(xst, yst, xst+X_POS_SIZE,yst+Y_TS_SIZE), this, MFY_ID[i]) ) return FALSE;
		MFYs[i]->finfo.kind = 1;
		MFYs[i]->finfo.x = i;
		MFYs[i]->finfo.y = 1;
		MFYs[i]->pP = this;

		xst += (X_POS_SIZE + 2);
	}
	// Time
	for (int v = 0; v<SPAN_MAX; v++) {		
		cw = GetDlgItem(INFO_ID[v]);
		cw->GetWindowRect(&Rdpos);
		xst = Rdpos.right - Wrect.left +2;
//		yst = Rdpos.top - Wrect.top - WINDOW_FRAME+6;
		yst = Rdpos.top - Wrect.top - WINDOW_FRAME ;
		Times[v] = new CAsEdit;
		if (!Times[v]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
			CRect(xst, yst, xst + X_TS_SIZE+30, yst + Y_TS_SIZE), this, Times_ID[v])) 
			return FALSE;
		Times[v]->finfo.kind = 2;
		Times[v]->finfo.x = 0;
		Times[v]->finfo.y = v;
		Times[v]->pP = this;
	}
	// Val
	for (int v = 0; v<SPAN_MAX; v++) {
		cw = GetDlgItem(INFO_ID[v]);
		cw->GetWindowRect(&Rdpos);
		xst =  Rname.right - Wrect.left + 1;
//		yst =  Rdpos.top - Wrect.top - WINDOW_FRAME+6;
		yst = Rdpos.top - Wrect.top - WINDOW_FRAME;
		for (int h = 0; h<ShowH; h++) {
			Edits[v][h] = new CAsEdit;
			if(! Edits[v][h]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP  | WS_BORDER | ES_CENTER,
								CRect(xst, yst, xst+X_TS_SIZE,yst+Y_TS_SIZE), this, Edits_ID[v][h]) ) return FALSE;
			Edits[v][h]->finfo.kind = 3;
			Edits[v][h]->finfo.x = h;
			Edits[v][h]->finfo.y = v;
			Edits[v][h]->pP = this;
			//
			xst += (X_TS_SIZE + 2);
		}
		yst += (Y_TS_SIZE +2 );
	}
	//
	return TRUE;
}
BOOL	 CTSEditDlg::Set_Edit_Value()
{
	CWnd*		cw;
	int			ival,id,idv,idh;
	CString		str;
	CTime		ct;

	if( ! TS.set ) return FALSE;
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 基本数値

	m_Num.Format("%d", TS.Num);
	m_Tspan.Format("%d",TS.Span);
	UDF;
	//
	for (int t = 0; t < SPAN_MAX; t++) {
		cw = GetDlgItem(INFO_ID[t]);
		str.Format("%d", stV + t + 1);
		if (t + stV < Vnum) cw->SetWindowTextA(str);
		else               cw->SetWindowTextA("");
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 名前と位置

	for (int i = 0; i<ShowH; i++) {
		id = stH + i;
		if (id < Hnum) {
			cw = GetDlgItem(Name_ID[i]);
			cw->EnableWindow(TRUE);
			if (strlen(TS.name[id]) != 0) cw->SetWindowTextA(TS.name[id]);
			//
			cw = GetDlgItem(MFX_ID[i]);
			cw->EnableWindow(FALSE);
			Set_CWnd_Text(cw, (TS.pos[id].x + 1), TRUE);
			//
			cw = GetDlgItem(MFY_ID[i]);
			cw->EnableWindow(FALSE);
			ival = PM.MVnum - TS.pos[id].y;
			Set_CWnd_Text(cw, ival, TRUE);
		}
		else {
			cw = GetDlgItem(Name_ID[i]);
			cw->SetWindowTextA("");
			cw->EnableWindow(FALSE);

			cw = GetDlgItem(MFX_ID[i]);
			cw->SetWindowTextA("");
			cw->EnableWindow(FALSE);

			cw = GetDlgItem(MFY_ID[i]);
			cw->SetWindowTextA("");
			cw->EnableWindow(FALSE);
		}
		//
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 日付と値
	if (Vnum != 0) {
		for (int v = 0; v < SPAN_MAX; v++) {
			idv = stV + v;
			cw = GetDlgItem(Times_ID[v]);
			if (idv < Vnum) {
				if (v > 0 && (TS.time[idv] < TS.time[idv - 1])) str = _T(""); // 時間追加した場合の特別処理
				else {
					cw->EnableWindow(TRUE);
					CT = ST + CTimeSpan(0l, 0, 0, TS.time[idv]);
					str.Format("%d/%2d/%2d %2d:%02d", CT.GetYear(), CT.GetMonth(),
						CT.GetDay(), CT.GetHour(), CT.GetMinute());
				}
			}
			else {
				cw->EnableWindow(FALSE);
				str = _T("");
			}
			//
			cw->SetWindowTextA(str);
			//
			if (idv < Vnum) {
				for (int h = 0; h < ShowH; h++) {
					idh = stH + h;
					cw = GetDlgItem(Edits_ID[v][h]);
					if (idh < Hnum) {
						cw->EnableWindow(TRUE);
						Set_CWnd_Text(cw, TS.val[idv][idh], 3, TRUE);
					}
					else {
						cw->EnableWindow(FALSE);
						cw->SetWindowTextA("");
					}
				}
			}
			else {
				for (int h = 0; h < ShowH; h++) {
					cw = GetDlgItem(Edits_ID[v][h]);
					cw->SetWindowTextA("");
					cw->EnableWindow(FALSE);
				}
			}
		}
	}
	else {
		str.Format("%d/%2d/%2d %2d:%02d", ST.GetYear(), ST.GetMonth(),
			ST.GetDay(), ST.GetHour(), ST.GetMinute());
		cw = GetDlgItem(Times_ID[0]);
		cw->SetWindowTextA(str);
	}
	//----------------------------------------------------------- ボタン表示
	if (Vnum > stV + SPAN_MAX) c_Down.ShowWindow(SW_SHOW);
	else                     c_Down.ShowWindow(SW_HIDE);
	if (stV != 0)				c_Up.ShowWindow(SW_SHOW);
	else						c_Up.ShowWindow(SW_HIDE);
	if (Hnum > stH + POS_MAX)  c_Right.ShowWindow(SW_SHOW);
	else                     c_Right.ShowWindow(SW_HIDE);
	if (stH != 0)				c_Left.ShowWindow(SW_SHOW);
	else						c_Left.ShowWindow(SW_HIDE);
	//
	return TRUE;
}
//-----------------------------------------------------------------------------------------------------------

void  CTSEditDlg::Free_All(BOOL TSfree)
{
	///  Uniqe
	//
	for(int h=0;h<ShowH;h++) {
		delete  Names[h];
		delete  MFXs[h];
		delete  MFYs[h];
	}
	SAFE_FREE( Name_ID );
	SAFE_FREE( Names );
	SAFE_FREE( MFX_ID );
	SAFE_FREE( MFXs );
	SAFE_FREE( MFY_ID );
	SAFE_FREE( MFYs );
	//
	for (int v = 0; v<SPAN_MAX; v++) {
		for (int h = 0; h<ShowH; h++) 	delete  Edits[v][h];
		SAFE_FREE( Edits[v] );
		//
		delete Times[v];
	}
	Free_Matrix(SPAN_MAX, Edits_ID);
	SAFE_FREE( Edits );
	SAFE_FREE( Times_ID );
	SAFE_FREE( Times );
	//
	if( TSfree ) Free_TIMESET( &TS );
	//
}

void CTSEditDlg::OnBnClickedSaveAs()
{
	Renew_Data();
	//
	CString		fname;
	char		ttl[SIZE_01K];
	strcpy(ttl,File_Title[Data_ID]);
	if(!Button_File(FALSE,&fname,m_RecentPath,ttl,"*.*") ) return;
	//
	Save_TS_File(Data_ID,fname, &TS);
}
BOOL CTSEditDlg::Save_TS_File(int ID,CString fname,TIMESET* TS)
{
	FILE*	fp;
	int		len;
	if((fp=fopen(fname,"w")) == NULL ) return FALSE;
	//
	if(  ID >= HS_WLEV_FILE  ) {
		fprintf(fp, "   %d", TS->Num);
		for (int i = 0; i < TS->Num; i++) {
			len = strlen(TS->name[i]);
			for (int k = 0; k < len; k++) if (TS->name[i][k] == ' ') TS->name[i][k] = '_';
			fprintf(fp, "  %s", TS->name[i]);
		}
		CR;
		fprintf(fp, "Location_i");
		for (int i = 0; i<TS->Num; i++) fprintf(fp, "   %d ", PM.MVnum - TS->pos[i].y);
		CR;
		fprintf(fp, "Location_j");
		for (int i = 0; i<TS->Num; i++) fprintf(fp, "   %d ", TS->pos[i].x + 1);
		CR;
		for (int i = 0; i<TS->Span; i++) {
			fprintf(fp, "%10d", TS->time[i]);
			for (int n = 0; n<TS->Num; n++) fprintf(fp, " %9.2lf", TS->val[i][n]);
			fprintf(fp, "\n");
		}
	}
	//
	fclose( fp );
	return TRUE;
}
///_____________________________________________________
//  時間追加
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CTSEditDlg::OnBnClickedButtonAddT()
{
	int  olds,idv,saveH,saveV;

	if ((TS.Span + 1) >= TS.Smem) {
		olds = TS.Smem;
		TS.Smem += 20;
		Realloc_TIMESET(TS.Mem, olds, &TS);
	}
	//
	if( Lrow == UNDEF ) Lrow = TS.Span-1;
	//
	for(int i=TS.Span-1;i>Lrow+stV;i--)  {
		TS.time[i+1] = TS.time[i];TS.time[i]=0;
		for(int n=0;n<TS.Num;n++) {
			TS.val[i+1][n] = TS.val[i][n];
			TS.val[i][n] = 0.;
		}
	}
	//
	Free_All( FALSE );
	Lrow = Lcol = UNDEF;
	//
	TS.Span ++;
	Hnum = TS.Num;
	Vnum = TS.Span;
	//
	saveH = stH;
	saveV = stV;
	Init_Set_Edits();
	stH = saveH;
	stV = saveV;
	Set_Edit_Value();
}
///_____________________________________________________
//  時間削除
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CTSEditDlg::OnBnClickedButtonDelT()
{
	if( Lrow == UNDEF ) return;
	if( TS.Span - 1 == 0 ) return;
	//
	for(int i=Lrow+stV+1;i<TS.Span;i++)  {
		TS.time[i-1] = TS.time[i];
		for(int n=0;n<TS.Num;n++) 	TS.val[i-1][n] = TS.val[i][n];
	}
	//
	Free_All( FALSE );
	Lrow = Lcol = UNDEF;
	//
	TS.Span --;
	Hnum = TS.Num;
	Vnum = TS.Span;
	//
	int saveH = stH;
	int saveV = stV;
	Init_Set_Edits();
	stH = saveH;
	stV = saveV;
	Set_Edit_Value();
}
//_____________________________________________________
//  地点削除
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CTSEditDlg::OnBnClickedButtonDelP()
{
	if( Lcol == UNDEF ) return;
	int dely = TS.pos[Lcol + stH].y;
	int delx = TS.pos[Lcol + stH].x;
	//
	if (MESH[dely][delx].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[dely][delx].flag = ID_MESH_R;
	else										MESH[dely][delx].flag = ID_MESH;
	//
	int id = Lcol + stH;
	//
	for(int i=id+1;i<TS.Num;i++) {
		strcpy(TS.name[i-1],TS.name[i]);
		TS.pos[i - 1] = TS.pos[i];
		//
		//
		for(int v=0;v<TS.Span;v++) 	TS.val[v][i-1] = TS.val[v][i];
	}
	//
	TS.Num --;
	//
	Free_All( FALSE );
	Lrow = Lcol = UNDEF;
	//
	Hnum = TS.Num;
	Vnum = TS.Span;
	//
	int saveH = stH;
	int saveV = stV;
	Init_Set_Edits();
	stH = saveH;
	stV = saveV;
	Set_Edit_Value();
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   コード修正 150209

BOOL CTSEditDlg::Renew_Data()
{
	int		id,idh,idv;
	char	buf[SIZE_01K],inchar[SIZE_01K];
	//
	for(int h=0;h<ShowH;h++) {
		id = stH + h;
		if (id < Vnum) {
			if (Names[h]->GetModify()) {
				Names[h]->GetWindowTextA(buf, SIZE_01K);
				if (strlen(buf) != 0){
					for (int k = 0; k < strlen(buf); k++) if (buf[k] == ' ') buf[k] = '-';
					strcpy(TS.name[id], buf);
				}
				else                 strcpy(TS.name[id], "-");
			}
			if (MFXs[h]->GetModify()) {
				MFXs[h]->GetWindowTextA(buf, SIZE_01K);
				TS.pos[id].x = atoi(buf) - 1;
			}
			if (MFYs[h]->GetModify()) {
				MFYs[h]->GetWindowTextA(buf, SIZE_01K);
				TS.pos[id].y = PM.MVnum - atoi(buf);
			}
		}
	}
	for (int v = 0; v<SPAN_MAX; v++) {
		idv = stV + v;
		if( Times[v]->GetModify() ) {
			int		y,m,d,h,mn,pos=0;

			Times[v]->GetWindowTextA(buf,SIZE_01K);
			if (idv < Vnum) {
				if (PM.StTime != NULL) {
					CTime		Tin = StrDate_Time(buf);
					CTimeSpan	Span = Tin - PM.StTime;
					TS.time[idv] = (int)Span.GetTotalSeconds();
				}
				else {
					getstr(buf, &pos, inchar, SIZE_01K);
					TS.time[idv] = atoi(inchar);
				}
			}
		}
		for(int h=0;h<ShowH;h++) {
			idh = stH + h;
			if( Edits[v][h]->GetModify() ) {
				Edits[v][h]->GetWindowTextA(buf,SIZE_01K);
				TS.val[idv][idh] = atof(buf);
			}
		}
	}
	//
	return TRUE;
}

afx_msg LRESULT CTSEditDlg::OnAseditFocus(WPARAM wParam, LPARAM lParam)
{
	FOCUSINFO*	pinfo;
	pinfo = (FOCUSINFO*)wParam;
	//
	Lrow = UNDEF;
	if (pinfo->kind == 2 || pinfo->kind == 3) Lrow = pinfo->y;
	//
	Lcol = UNDEF;
	if (pinfo->kind != 2) Lcol = pinfo->x;
	return 0;
}

void CTSEditDlg::OnBnClickedButtonSetday()
{
	if (Vnum != 0) return;
	//
	int     cnt = 0;
	CTime   TT,CT = PM.StTime;
	CTimeSpan ts = PM.EndTime - PM.StTime;
	Vnum = ts.GetDays();
	//
	if (PM.EndTime.GetHour() != 0) Vnum++;
	if (PM.StTime.GetHour() != 0) Vnum++;
	//
	if (TS.Smem == 0) {
		TS.Smem = Vnum * 2;
		Realloc_TIMESET(TS.Mem,0,&TS);
	}
	//
	while (TRUE) {
		ts = CT - PM.StTime;
		TS.time[cnt++] = ts.GetTotalSeconds();
		if (CT == PM.EndTime) break;
		//
		//if (CT.GetHour() != 0) {
		//	TT = CT;
		//	TT = CT + CTimeSpan(1l, 0, 0, 0);
		//	CT = ::CTime(TT.GetYear(), TT.GetMonth(), TT.GetDay(), 0, 0, 0, -1);
		//}
		//else CT += CTimeSpan(1l, 0, 0, 0);
		CT += CTimeSpan(1l, 0, 0, 0);
		//
		if (CT > PM.EndTime) CT = PM.EndTime;
	}
	Vnum = TS.Span = cnt;
	c_SetDaily.ShowWindow(SW_HIDE);
	//
	Set_Edit_Value();
}


void CTSEditDlg::OnBnClickedCheckUp()
{
	Renew_Data();
	stV -= SPAN_MAX;
	Set_Edit_Value();
}


void CTSEditDlg::OnBnClickedButtonDown()
{
	Renew_Data();
	stV += SPAN_MAX;
	Set_Edit_Value();
}


void CTSEditDlg::OnBnClickedButtonLeft()
{
	Renew_Data();
	stH -= POS_MAX;
	Set_Edit_Value();
}


void CTSEditDlg::OnBnClickedButtonRight()
{
	Renew_Data();
	stH += POS_MAX;
	Set_Edit_Value();
}
///_____________________________________________________
//  終了
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CTSEditDlg::OnBnClickedOk()
{
	Renew_Data();
	//
	if (Data_ID == HS_WLEV_FILE)				Copy_TIMESET(&DSET.HSWLEV, &TS);
	else if (Data_ID == HR_WLEV_FILE)			Copy_TIMESET(&DSET.HRWLEV, &TS);
	else if (Data_ID == QS_WLEV_FILE)			Copy_TIMESET(&DSET.QSWLEV, &TS);
	else if (Data_ID == QR_WLEV_FILE)			Copy_TIMESET(&DSET.QRWLEV, &TS);
	else  return;
	//
	Save_TS_File(Data_ID, DSET.File_names[Data_ID], &TS);
	//
	CDialogEx::OnOK();
}

///_____________________________________________________
//  インポート エクスポート
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CTSEditDlg::OnBnClickedButtonExport()
{
	FILE*		fp;
	CString		fname,date;
	char			ttl[SIZE_02K];
	//
	switch (Data_ID) {
	case HS_WLEV_FILE:strcpy(ttl,"Export HS file"); break;
	case HR_WLEV_FILE:strcpy(ttl, "Export HR file"); break;
	case QS_WLEV_FILE:strcpy(ttl, "Export QS file"); break;
	case QR_WLEV_FILE:strcpy(ttl, "Export QR file"); break;
	}
	//
	if (!Button_File(FALSE, &fname, m_RecentPath, ttl, "csv")) return;
	if ((fp = fopen(fname, "w")) == NULL) return;
	//
	fprintf(fp, "%d,,,,// Never Change\n", Data_ID);
	fprintf(fp, "%d,,,,//Cell Number . Change properly\n", TS.Num);
	//
	fprintf(fp, "Name");
	for (int i = 0; i < TS.Num; i++)  fprintf(fp, ",%s", TS.name[i]);
	CR;
	fprintf(fp, "X");
	for (int i = 0; i < TS.Num; i++)  fprintf(fp, ",%d", TS.pos[i].x + 1);
	CR;
	fprintf(fp, "Y");
	for (int i = 0; i < TS.Num; i++)  fprintf(fp, ",%d", PM.MVnum - TS.pos[i].y);
	CR;
	if (Data_ID == HS_WLEV_FILE || Data_ID == HR_WLEV_FILE) {
		fprintf(fp, "elevation");
		for (int i = 0; i < TS.Num; i++)  fprintf(fp, ",%.2lf", MESH[TS.pos[i].y][TS.pos[i].x].Adem);
		CR;
	}
	if (Data_ID == HR_WLEV_FILE) {
		fprintf(fp, "depth");
		for (int i = 0; i < TS.Num; i++)  fprintf(fp, ",%.1lf", MESH[TS.pos[i].y][TS.pos[i].x].Rdepth);
		CR;
	}
	//
	CTime	CT;
	for (int v = 0; v<Vnum; v++) {
		CT = PM.StTime + CTimeSpan(0l, 0, 0, TS.time[v]);
		date.Format("%4d/%2d/%2d %2d:%2d", CT.GetYear(), CT.GetMonth(), CT.GetDay(), CT.GetHour(), CT.GetMinute());
		fprintf(fp, "%s", date);
		for (int h = 0; h<TS.Num; h++) fprintf(fp, ",%.3lf", TS.val[v][h]);
		CR;
	}	//
	fclose(fp);
	return;
}

void CTSEditDlg::OnBnClickedButtonImport()
{
	FILE*		fp;
	CString		fname, date,str,str1,str2;
	char		buf[SIZE_12K],inchar[SIZE_01K],ttl[SIZE_02K];
	int			pos,DID,NH, NV,lcnt;
	BOOL		Replace = FALSE;
	//
	switch (Data_ID) {
		case HS_WLEV_FILE:strcpy(ttl, "Import HS file"); break;
		case HR_WLEV_FILE:strcpy(ttl, "Import HR file"); break;
		case QS_WLEV_FILE:strcpy(ttl, "Import QS file"); break;
		case QR_WLEV_FILE:strcpy(ttl, "Import QR file"); break;
	}
	//
	if (!Button_File(TRUE, &fname, m_RecentPath, ttl, "csv")) return;
	if ((fp = fopen(fname, "r")) == NULL) return;
	//
	lcnt = 0;
	while (fgets(buf, SIZE_12K, fp) != NULL) lcnt++;
	fseek(fp, 0l, SEEK_SET);
	//
	fgets(buf, SIZE_12K, fp); pos = 0;
	getstr(buf, &pos, inchar, SIZE_01K); DID = atoi(inchar);
	//
	if (DID != Data_ID) {
		str.Format("** Error ** Selected file is not %s file", MODEL_EDIT_NAME[Data_ID]);
		MessageBox(str, "error", MB_OK | MB_ICONASTERISK); fclose(fp); return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  入力数を決める
	fgets(buf, SIZE_12K, fp); pos = 0;
	getstr(buf, &pos, inchar, SIZE_01K); NH = atoi(inchar);
	NV = lcnt - 5; // ID , number ,name,idx,idy 
	//
	if (NH != TS.Num || NV != TS.Span) {
		str = "Cell number or Timespan is different from current data\nReplace Data ...?";
		if (MessageBox(str, "error", MB_YESNO | MB_ICONHAND) == IDNO){ fclose(fp); return; }
		//
		Free_All(TRUE);
		//
		TS.Mem = NH + 10;
		TS.Smem = NV + 10;
		Alloc_TIMESET(&TS);
		Replace = TRUE;
	}
	TS.Num = NH;
	TS.Span = NV;
	///____________________________________________
	//  名前、座標
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int   ival;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  名前の数で入力数を判断する　NHを優先する。
	fgets(buf, SIZE_12K, fp); pos = 0; getstr(buf, &pos, inchar, SIZE_01K);// Name
	//
	int		ret;
	NH = 0;
	for (int i = 0; i < TS.Num; i++) {
		sgetcsv(buf, &pos, TS.name[i]);
		if (strlen(TS.name[i]) == 0) break;
		NH++;
	}
	TS.Num = NH;
	//
	fgets(buf, SIZE_12K, fp); pos = 0; getstr(buf, &pos, inchar, SIZE_01K);
	for (int i = 0; i < TS.Num; i++) {
		getstr(buf, &pos, inchar, SIZE_01K);
		TS.pos[i].x = atoi(inchar) - 1;
	}
	fgets(buf, SIZE_12K, fp); pos = 0; getstr(buf, &pos, inchar, SIZE_01K);
	for (int i = 0; i < TS.Num; i++) {
		getstr(buf, &pos, inchar, SIZE_01K); 
		TS.pos[i].y = PM.MVnum - atoi(inchar);
	}
	if (Data_ID == HS_WLEV_FILE || Data_ID == HR_WLEV_FILE) fgets(buf, SIZE_1K, fp);
	if (Data_ID == HR_WLEV_FILE) fgets(buf, SIZE_1K, fp);
	///____________________________________________
	//  時間（日付表示になっているので注意）、値
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CTime		CT;
	CTimeSpan	cts;
	for (int i = 0; i < TS.Span; i++) {
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 時間の読込
		fgets(buf, SIZE_12K, fp); pos = 0;
		sgetcsv(buf, &pos, inchar); 
		CT = StrDate_Time(inchar);   // 20**/**/**  **:**
		//
		cts = CT - PM.StTime; TS.time[i] = cts.GetTotalSeconds();
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 値の読込
		for (int h = 0; h < TS.Num; h++) {
			getstr(buf, &pos, inchar, SIZE_01K); TS.val[i][h] = atof(inchar);
		}
	}
	fclose(fp);
///____________________________________________
//  フラグの変更
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TIMESET*	TT;
	//
	if (Data_ID == HS_WLEV_FILE)				TT = &DSET.HSWLEV;
	else if (Data_ID == HR_WLEV_FILE)			TT = &DSET.HRWLEV;
	else if (Data_ID == QS_WLEV_FILE)			TT = &DSET.QSWLEV;
	else if (Data_ID == QR_WLEV_FILE)			TT = &DSET.QRWLEV;
	//
	for (int i = 0; i < TT->Num; i++) {	// 消去
		if (MESH[TT->pos[i].y][TT->pos[i].x].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail)
			MESH[TT->pos[i].y][TT->pos[i].x].flag = ID_MESH_R;
		else														MESH[TT->pos[i].y][TT->pos[i].x].flag = ID_MESH;
	}
	for (int i = 0; i < TS.Num; i++) {		// 新マーキング
		MESH[TS.pos[i].y][TS.pos[i].x].flag = Data_ID-9; // HS_WLEV_FILE=12		ID_MESH_HS=3
	}
///____________________________________________
//  ウィンドウ表示
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (Replace) {
		if (!Init_Set_Edits()) {
			MessageBox("** Error ** Initialize CEdit or memory allocation", "Error", MB_OK); return;
		}
	}
	//
	ShowH = Hnum = TS.Num;
	if (ShowH > POS_MAX) ShowH = POS_MAX;
	ShowV = Vnum = TS.Span;
	if (ShowV > SPAN_MAX) ShowV = SPAN_MAX;
	stV = stH = 0;
	Set_Edit_Value();
}
