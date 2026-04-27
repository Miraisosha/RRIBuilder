// DataColor.cpp : 実装ファイル
//

#include		"stdafx.h"
#include		"RRI_GUI.h"
#include		"DataColor.h"
#include		"afxdialogex.h"


#include		"CColWin.h"
#include		"CommFuncs.h"

//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
extern      char			m_BootPath[SIZE_05K];
extern      int			CDATA;							// 現在対象のデータ
extern      PARAMS		PM;						// 上下流基本情報
//
//
CColWin		CWW[ColorNumber];


int			CAP_NUM = ColorNumber;
int			CAP_ID[ColorNumber]={IDC_D_LABEL_0,IDC_D_LABEL_1,IDC_D_LABEL_2,IDC_D_LABEL_3,
						IDC_D_LABEL_4,IDC_D_LABEL_5,IDC_D_LABEL_6,IDC_D_LABEL_7,
						IDC_D_LABEL_8};
int			DCOL_NUM= ColorNumber;
int			DCOL_ID[ColorNumber]={IDC_COL_D_0,IDC_COL_D_1,IDC_COL_D_2,IDC_COL_D_3,
						IDC_COL_D_4,IDC_COL_D_5,IDC_COL_D_6,IDC_COL_D_7,IDC_COL_D_8};

int			DEDIT_NUM= 10;
int			DEDIT_ID[10]={IDC_EDIT_D_0,IDC_EDIT_D_1,IDC_EDIT_D_2,IDC_EDIT_D_3,
	IDC_EDIT_D_4,IDC_EDIT_D_5,IDC_EDIT_D_6,IDC_EDIT_D_7,IDC_EDIT_D_8,IDC_EDIT_D_9};

int			DRADIO_NUM = 4;
int			DRADIO_ID[4]={IDC_DRADIO_CONT,IDC_DRADIO_MOSAIC,IDC_DRADIO_EQ,IDC_DRADIO_GR};

// CDataColor ダイアログ

IMPLEMENT_DYNAMIC(CDataColor, CDialog)

CDataColor::CDataColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDataColor::IDD, pParent)
{
	Ready = FALSE;
}

CDataColor::~CDataColor()
{
}

void CDataColor::OnDestroy()
{
	CDialog::OnDestroy();
}

void CDataColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_ALPHA, m_Slider_Alpha);
}


BEGIN_MESSAGE_MAP(CDataColor, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DRADIO_CONT, &CDataColor::OnBnClickedDradioCont)
	ON_BN_CLICKED(IDC_DRADIO_MOSAIC, &CDataColor::OnBnClickedDradioMosaic)
	ON_BN_CLICKED(IDC_DRADIO_EQ, &CDataColor::OnBnClickedDradioEq)
	ON_BN_CLICKED(IDC_DRADIO_GR, &CDataColor::OnBnClickedDradioGr)
	ON_EN_CHANGE(IDC_EDIT_D_0, &CDataColor::OnEnChangeEditD0)
	ON_EN_CHANGE(IDC_EDIT_D_1, &CDataColor::OnEnChangeEditD1)
	ON_EN_CHANGE(IDC_EDIT_D_2, &CDataColor::OnEnChangeEditD2)
	ON_EN_CHANGE(IDC_EDIT_D_3, &CDataColor::OnEnChangeEditD3)
	ON_EN_CHANGE(IDC_EDIT_D_4, &CDataColor::OnEnChangeEditD4)
	ON_EN_CHANGE(IDC_EDIT_D_5, &CDataColor::OnEnChangeEditD5)
	ON_EN_CHANGE(IDC_EDIT_D_6, &CDataColor::OnEnChangeEditD6)
	ON_EN_CHANGE(IDC_EDIT_D_7, &CDataColor::OnEnChangeEditD7)
	ON_EN_CHANGE(IDC_EDIT_D_8, &CDataColor::OnEnChangeEditD8)
	ON_EN_CHANGE(IDC_EDIT_D_9, &CDataColor::OnEnChangeEditD9)
	ON_BN_CLICKED(IDOK, &CDataColor::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COLSAVE, &CDataColor::OnBnClickedButtonColsave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALPHA, &CDataColor::OnNMCustomdrawSliderAlpha)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDataColor メッセージ ハンドラー

void CDataColor::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Set_Dialog();
}

BOOL CDataColor::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN  && pMsg->wParam == VK_RETURN ) {
		Set_Dialog();return TRUE;}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDataColor::OnInitDialog()
{
//
	CDialog::OnInitDialog();
//
	if( Title.GetLength() != 0 ) this->SetWindowTextA( Title );
	else                         this->SetWindowTextA( "Data Color Dialog" );
//----------------------------------------------------------------------
// Data Copy
	memset(&CV,0,sizeof( COLVAL_FIX ) );
	CV.num = PM.Dcol[CDATA].num;
	CV.Equal = PM.Dcol[CDATA].Equal;
	CV.alpha = PM.Dcol[CDATA].alpha;
	CV.Mos = B_DataMosaic = PM.Dcol[CDATA].Mos;
	//
	m_Slider_Alpha.SetRange(0,10,0);
	m_Slider_Alpha.SetPos( (int)(PM.Dcol[CDATA].alpha*10 ) );
//---------------------------------------------------------------------

	for(int i=0;i<11;i++) CV.val[i] = DUNDEF;
	for(int i=0;i<CV.num;i++) {
		CV.val[i] = PM.Dcol[CDATA].val[i];
		CV.Rcol[i] = PM.Dcol[CDATA].Rcol[i];
		Copy_FCOLOR(&CV.Fcol[i],PM.Dcol[CDATA].Fcol[i]);
		//
		TEMP_COL[i] = PM.Dcol[CDATA].Rcol[i];
	}
	for(int i=CV.num;i<ColorNumber;i++) TEMP_COL[i] =  RGB(100,100,100 );
//---------------------------------------------------------------------
	for(int i=0;i<ColorNumber;i++) {
		if( ! CWW[i].AutoLoad( DCOL_ID[i],this) ) {
			MessageBox("** Error ** Failed to set subclass... Please retry.", "Missed", MB_OK | MB_ICONHAND);
			CDialog::OnCancel();
		}
		CWW[i].colground = TEMP_COL[i];
		CWW[i].ChangeColor( TEMP_COL[i] );
	}
//---------------------------------------------------------------------
//
	SetTimer(0,10,NULL);

	return TRUE; 
}
//////////////////////////////////////////////////////////////////////
/*-------------------------------------------*
**  TIMER          
**-------------------------------------------*/
//////////////////////////////////////////////////////////////////////

void CDataColor::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer( 0 );
	//
	Ready = TRUE;
	Set_Dialog();
}
void CDataColor::Set_Dialog()
{
	if( ! Ready ) return;
	//
	CWnd*		cw;
	CString		vals,str;
	CRect		frect;
	//
	for(int i=0;i<=ColorNumber;i++) {
		if( CV.val[i] == DUNDEF ) {CV.num = i;break;}
	}
	// ラジオ
	CButton*	cb;
	for(int i=0;i<DRADIO_NUM;i++) {
		cb =  (CButton*)GetDlgItem( DRADIO_ID[i] );
		switch( i ) {
			case 0: if( B_DataMosaic ) cb->SetCheck( 0 ); else cb->SetCheck( 1 );break;
			case 1: if( B_DataMosaic ) cb->SetCheck( 1 ); else cb->SetCheck( 0 );break;
			case 2: if( CV.Equal ) cb->SetCheck( 1 ); else cb->SetCheck( 0 );break;
			case 3: if( CV.Equal ) cb->SetCheck( 0 ); else cb->SetCheck( 1 );break;
		}
	}
	//
	for(int i=0;i<=ColorNumber;i++) {
		if( i == 0  ) {
			cw = GetDlgItem( DEDIT_ID[i] );
			Set_CWnd_Text(cw,CV.val[0],6,FALSE);
		}
		//
		else if(i <= CV.num ) {
			cw = GetDlgItem( CAP_ID[i-1] );
			if( i == 1 ) {
				if( CV.Equal ) str="<= h <";
				else           str="< h <=";
			}
			else if( i == CV.num ) {
				Set_Double_Str(CV.val[i-1],&vals,1);
				if( CV.Equal ) str.Format("%s <= h",vals);
				else           str.Format("%s < h",vals);
			}
			else {
				Set_Double_Str(CV.val[i-1],&vals,1);
				if( CV.Equal ) str.Format("%s <= h <",vals);
				else           str.Format("%s < h <=",vals);
				//
			}
			cw->SetWindowTextA( str );
			//
			if( i != CV.num ) {
				cw = GetDlgItem( DEDIT_ID[i] );
				Set_CWnd_Text(cw,CV.val[i],6,FALSE);
			}
			//
			CWW[i-1].ChangeColor( CV.Rcol[i-1] );
			TEMP_COL[i-1] = CV.Rcol[i-1];
			//
		}
		else {	// クリヤー
			cw = GetDlgItem( CAP_ID[i-1] );
			cw->SetWindowTextA("");
			cw = GetDlgItem( DEDIT_ID[i] );
			cw->SetWindowTextA("");
			CWW[i-1].ChangeColor( RGB(100,100,100 ) );
			TEMP_COL[i-1] = RGB(100,100,100 );
		}
		//
		if (i != ColorNumber) {
			cw = GetDlgItem(DCOL_ID[i]);
			cw->GetClientRect(&frect);
			cw->ValidateRect(&frect);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
//   FILL RECT
//-----------------------------------------------------------------------------------------------------------

void CDataColor::OnBnClickedDradioCont() {B_DataMosaic=FALSE;Set_Dialog();}

void CDataColor::OnBnClickedDradioMosaic(){B_DataMosaic=TRUE;Set_Dialog();}

void CDataColor::OnBnClickedDradioEq(){CV.Equal=TRUE;Set_Dialog();}

void CDataColor::OnBnClickedDradioGr(){CV.Equal=FALSE;Set_Dialog();}

//////////////////////////////////////////////////////////////////////
/*-------------------------------------------*
**  EDIT        
**-------------------------------------------*/
//////////////////////////////////////////////////////////////////////
double	 CDataColor::Get_EditRect( int ID )
{
	char		buf[128];
	CEdit*		cw = (CEdit*)GetDlgItem( ID );
	cw->GetWindowTextA(buf,128);
	//
	if( strlen( buf ) != 0 ) return atof( buf );
	else                     return DUNDEF;
}

void CDataColor::OnEnChangeEditD0() {CV.val[0] = Get_EditRect( DEDIT_ID[0] );}
void CDataColor::OnEnChangeEditD1() {CV.val[1] = Get_EditRect( DEDIT_ID[1] );}
void CDataColor::OnEnChangeEditD2() {CV.val[2] = Get_EditRect( DEDIT_ID[2] );}
void CDataColor::OnEnChangeEditD3() {CV.val[3] = Get_EditRect( DEDIT_ID[3] );}
void CDataColor::OnEnChangeEditD4() {CV.val[4] = Get_EditRect( DEDIT_ID[4] );}
void CDataColor::OnEnChangeEditD5() {CV.val[5] = Get_EditRect( DEDIT_ID[5] );}
void CDataColor::OnEnChangeEditD6() {CV.val[6] = Get_EditRect( DEDIT_ID[6] );}
void CDataColor::OnEnChangeEditD7() {CV.val[7] = Get_EditRect( DEDIT_ID[7] );}
void CDataColor::OnEnChangeEditD8() {CV.val[8] = Get_EditRect( DEDIT_ID[8] );}
void CDataColor::OnEnChangeEditD9() {CV.val[9] = Get_EditRect( DEDIT_ID[9] );}

//////////////////////////////////////////////////////////////////////
/*-------------------------------------------*
**  SAVE      
**-------------------------------------------*/
//////////////////////////////////////////////////////////////////////

void CDataColor::OnBnClickedOk()
{
//----------------------------------------------------------------------
// Data Copy
	COLORREF	col;
	PM.Change_DCOL = FALSE;
	//
	if( PM.Dcol[CDATA].num != CV.num )		PM.Change_DCOL=TRUE;
	if( PM.Dcol[CDATA].Equal != CV.Equal ) PM.Change_DCOL=TRUE;
	if (PM.Dcol[CDATA].Mos != B_DataMosaic) PM.Change_DCOL = TRUE;
	if( PM.Dcol[CDATA].alpha  != CV.alpha )PM.Change_DCOL=TRUE;
	//
	PM.Dcol[CDATA].num = CV.num;
	PM.Dcol[CDATA].Equal = CV.Equal;
	PM.Dcol[CDATA].alpha = CV.alpha;
	PM.Dcol[CDATA].Mos = B_DataMosaic;
	//
	for(int i=0;i<CV.num;i++) {
		if( PM.Dcol[CDATA].val[i] != CV.val[i] ) PM.Change_DCOL=TRUE;
		if( PM.Dcol[CDATA].Rcol[i] != CWW[i].colground ) PM.Change_DCOL=TRUE;
		//
		PM.Dcol[CDATA].val[i] = CV.val[i];
		col = CWW[i].colground ;
		PM.Dcol[CDATA].Rcol[i] =  col;
		PM.Dcol[CDATA].Fcol[i] = F_COLOR( GetRValue( col ),	GetGValue( col ),GetBValue( col ) );
	}
//
	CDialog::OnOK();
}


void CDataColor::OnBnClickedButtonColsave()
{
	FILE*			fp;
	CString			fname;
	COLVAL_FIX*		COL;
	//
	fname.Format("%s\\RRI_CONTENTS\\COLOR_DATA_B.DAT", m_BootPath);
	if((fp=fopen(fname,"w")) == NULL ) {
		MessageBox("** Error **\nCannot ｆind [ /RRI_CONTENTS/COLOR_DATA_B.DAT ]..", "Error", MB_OK);
		return;
	}
	//
	fprintf(fp, "[MESH_COLOR]  10\n");
	for (int i = 0; i < 10; i++) {
		fprintf(fp, " %d  %d  %d  %d\n", i, 
			GetRValue(PM.COL_MESH[i]), GetGValue(PM.COL_MESH[i]), GetBValue(PM.COL_MESH[i]));
	}
	CV.set = 1;
	for (int i = 0; i<FILE_IN_USE; i++) {
		if( i == CDATA )   COL = &CV;
		else              COL = &PM.Dcol[i];
		if( COL->set )  {
			fprintf(fp,"%d  %d  %d  %d  %.2lf\n",i,
				COL->num,(int)COL->Equal,(int)COL->Mos,(double)COL->alpha);
			for(int k=0;k<COL->num;k++) {
				fprintf(fp,"%.5lf  %d  %d  %d\n",COL->val[k],
					GetRValue( COL->Rcol[k] ),GetGValue( COL->Rcol[k] ),GetBValue( COL->Rcol[k] ));
			}
		}
	}
	//
	fclose( fp );		
//
	return;
}


void CDataColor::OnNMCustomdrawSliderAlpha(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int		pos = m_Slider_Alpha.GetPos();
	CV.alpha = (float)((double)pos/10.);
	*pResult = 0;
}

