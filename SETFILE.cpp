////////////////////////////////////////////////////////////////////////////////////////
//
//	FILE SET Input Dialog   実装ファイル
//
////////////////////////////////////////////////////////////////////////////////////////
//

#include "stdafx.h"
#include "RRI_GUIView.h"
#include "SETFILE.h"
#include "afxdialogex.h"
//#include "AS_Library\As_Common.h"

#include "Tab_Param.h"
//CTab_Param		Dlg_Param;


//#include  "CommFuncs.h"
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
extern      char		m_RecentPath[SIZE_1K];
extern      int			CLABEL;								// 現在対象のデータ
extern      PARAMS		PM;									// 上下流基本情報
extern      DATASET		DSET;								// 上下流ファイルセット
extern      int			File_Format[  ]; 
extern      CString		File_Title[];
extern      CString		OutFile_Title[];
extern      CString		GISFile_Title[];

CBrush		m_OnY,m_OffG;

//
// TAB COMMON
//
// TAB PARAM
int				BP_LABEL_NUM = 47;
int				BP_EDIT_NUM = 38;
int				BP_LABEL_ID[] = {   IDC_GB_0,
									IDC_PLABEL_0,IDC_PLABEL_1,IDC_PLABEL_2,IDC_PLABEL_3,IDC_PLABEL_4,
									IDC_PLABEL_5,IDC_PLABEL_6,IDC_PLABEL_7,IDC_PLABEL_8,IDC_PLABEL_9,
									IDC_PLABEL_10,IDC_PLABEL_11,IDC_PLABEL_12,IDC_PLABEL_13,IDC_PLABEL_14,
									IDC_PLABEL_15,IDC_PLABEL_16,IDC_PLABEL_17,IDC_PLABEL_18,IDC_PLABEL_19,
									IDC_PLABEL_20,IDC_PLABEL_21,IDC_PLABEL_22,IDC_PLABEL_23,IDC_PLABEL_24,
									IDC_PLABEL_25,IDC_PLABEL_26,IDC_PLABEL_27,IDC_PLABEL_28,IDC_PLABEL_29,
									IDC_PLABEL_30,IDC_PLABEL_31,IDC_PLABEL_32,IDC_PLABEL_33,IDC_PLABEL_34,
									IDC_PLABEL_35,IDC_PLABEL_36,IDC_PLABEL_37,IDC_PLABEL_38,IDC_PLABEL_39,
									IDC_PLABEL_40,IDC_PLABEL_41,IDC_PLABEL_42,IDC_PLABEL_43,IDC_PLABEL_44,
									IDC_PLABEL_45,};
int				BP_EDIT_ID[] ={	IDC_PARAM_EDIT_0,IDC_PARAM_EDIT_1,IDC_PARAM_EDIT_2,IDC_PARAM_EDIT_3,IDC_PARAM_EDIT_4,
									IDC_PARAM_EDIT_5,IDC_PARAM_EDIT_6,IDC_PARAM_EDIT_7,IDC_PARAM_EDIT_8,IDC_PARAM_EDIT_9,
									IDC_PARAM_EDIT_10,IDC_PARAM_EDIT_11,IDC_PARAM_EDIT_12,IDC_PARAM_EDIT_13,IDC_PARAM_EDIT_14,
									IDC_PARAM_EDIT_15,IDC_PARAM_EDIT_16,IDC_PARAM_EDIT_17,IDC_PARAM_EDIT_18,IDC_PARAM_EDIT_19,
									IDC_PARAM_EDIT_20,IDC_PARAM_EDIT_21,IDC_PARAM_EDIT_22,IDC_PARAM_EDIT_23,IDC_PARAM_EDIT_24,
									IDC_PARAM_EDIT_25,IDC_PARAM_EDIT_26,IDC_PARAM_EDIT_27,IDC_PARAM_EDIT_28,IDC_PARAM_EDIT_29,
									IDC_PARAM_EDIT_30,IDC_PARAM_EDIT_31,IDC_PARAM_EDIT_32,IDC_PARAM_EDIT_33,IDC_PARAM_EDIT_35,
									IDC_PARAM_EDIT_36,IDC_PARAM_EDIT_37,IDC_PARAM_EDIT_34};			

//
// TAB INFILE
CWnd*	BFin[FILE_IN_NUM];
CWnd*	BFout[FILE_OUT_NUM];
CWnd*	BFgis[FILE_GIS_NUM];
//

CButton			BIN[FILE_IN_NUM];
int				BIN_Num = FILE_IN_NUM;
int				BIN_ID[] = {
					IDC_BUTTON_FILE_0, IDC_BUTTON_FILE_1, IDC_BUTTON_FILE_2, IDC_BUTTON_FILE_3, IDC_BUTTON_FILE_4,
					IDC_BUTTON_FILE_5, IDC_BUTTON_FILE_6, IDC_BUTTON_FILE_7, IDC_BUTTON_FILE_8, IDC_BUTTON_FILE_9,
					IDC_BUTTON_FILE_10, IDC_BUTTON_FILE_11, IDC_BUTTON_FILE_12, IDC_BUTTON_FILE_13, IDC_BUTTON_FILE_14,
					IDC_BUTTON_FILE_15, IDC_BUTTON_FILE_16, IDC_BUTTON_FILE_17, IDC_BUTTON_FILE_18, IDC_BUTTON_FILE_19, 
					IDC_BUTTON_FILE_20,	IDC_BUTTON_FILE_21, IDC_BUTTON_FILE_22, IDC_BUTTON_FILE_23, IDC_BUTTON_FILE_24, 
					IDC_BUTTON_FILE_25, IDC_BUTTON_FILE_26, IDC_BUTTON_FILE_27};
CString			BIN_Text[FILE_IN_NUM];
int				BIN_LABEL_ID[] = {
					IDC_FILELABEL_1, IDC_FILELABEL_2, IDC_FILELABEL_3, IDC_FILELABEL_4, IDC_FILELABEL_5,
					IDC_FILELABEL_6, IDC_FILELABEL_7, IDC_FILELABEL_8, IDC_FILELABEL_9, IDC_FILELABEL_10,
					IDC_FILELABEL_11, IDC_FILELABEL_12, IDC_FILELABEL_13, IDC_FILELABEL_14, IDC_FILELABEL_15,
					IDC_FILELABEL_16, IDC_FILELABEL_17, IDC_FILELABEL_18, IDC_FILELABEL_19, IDC_FILELABEL_20, 
					IDC_FILELABEL_21, IDC_FILELABEL_22, IDC_FILELABEL_23, IDC_FILELABEL_24, IDC_FILELABEL_25, 
					IDC_FILELABEL_26, IDC_FILELABEL_27, IDC_FILELABEL_28 };
int				BIN_SAVE_ID[] = {
					IDC_SAVE_0, IDC_SAVE_1, IDC_SAVE_2, IDC_SAVE_3, IDC_SAVE_4,
					IDC_SAVE_5, IDC_SAVE_6, IDC_SAVE_7, IDC_SAVE_8, IDC_SAVE_9,
					IDC_SAVE_10, IDC_SAVE_11, IDC_SAVE_12, IDC_SAVE_13, IDC_SAVE_14,
					IDC_SAVE_15, IDC_SAVE_16, IDC_SAVE_17, IDC_SAVE_18, IDC_SAVE_19,
					IDC_SAVE_20, IDC_SAVE_21, IDC_SAVE_22, IDC_SAVE_23, IDC_SAVE_24,
					IDC_SAVE_25, IDC_SAVE_26, IDC_SAVE_27 };
int				BIN_SAVEAS_ID[] = {
					IDC_SAVEAS_0, IDC_SAVEAS_1, IDC_SAVEAS_2, IDC_SAVEAS_3, IDC_SAVEAS_4,
					IDC_SAVEAS_5, IDC_SAVEAS_6, IDC_SAVEAS_7, IDC_SAVEAS_8, IDC_SAVEAS_9,
					IDC_SAVEAS_10, IDC_SAVEAS_11, IDC_SAVEAS_12, IDC_SAVEAS_13, IDC_SAVEAS_14,
					IDC_SAVEAS_15, IDC_SAVEAS_16, IDC_SAVEAS_17, IDC_SAVEAS_18, IDC_SAVEAS_19,
					IDC_SAVEAS_20, IDC_SAVEAS_21, IDC_SAVEAS_22, IDC_SAVEAS_23, IDC_SAVEAS_24,
					IDC_SAVEAS_25, IDC_SAVEAS_26, IDC_SAVEAS_27};


extern			CString		File_Title[];
//
// TAB OUTFILE
int				OUT_MOVE_NUM = 58;
int				OUT_MOVE_IDS[]={
					IDC_OUTLABEL_0, IDC_OUTLABEL_1, IDC_OUTLABEL_2, IDC_OUTLABEL_3, IDC_OUTLABEL_4,
					IDC_OUTLABEL_5, IDC_OUTLABEL_6, IDC_OUTLABEL_7, IDC_OUTLABEL_8, IDC_OUTLABEL_9, 
					IDC_OUTLABEL_10,

					IDC_BUTTON_OUTFILE_0, IDC_BUTTON_OUTFILE_1, IDC_BUTTON_OUTFILE_2, IDC_BUTTON_OUTFILE_3, IDC_BUTTON_OUTFILE_4,
					IDC_BUTTON_OUTFILE_5, IDC_BUTTON_OUTFILE_6, IDC_BUTTON_OUTFILE_7, IDC_BUTTON_OUTFILE_8, IDC_BUTTON_OUTFILE_9,
					IDC_BUTTON_OUTFILE_10,

					IDC_BUTTON_GISFILE_0, IDC_BUTTON_GISFILE_1, IDC_BUTTON_GISFILE_2,IDC_BUTTON_GISFILE_3, IDC_BUTTON_GISFILE_4, 
					IDC_BUTTON_GISFILE_5,

					IDC_GISLABEL_0, IDC_GISLABEL_1, IDC_GISLABEL_2,IDC_GISLABEL_3, IDC_GISLABEL_4, 
					IDC_GISLABEL_5,

					IDC_O_LABEL_1,IDC_O_LABEL_2,IDC_O_LABEL_3,IDC_O_LABEL_4,IDC_O_LABEL_5,
					IDC_O_LABEL_6,IDC_O_LABEL_7,IDC_O_LABEL_8,IDC_O_LABEL_9,IDC_O_LABEL_10,
					IDC_O_LABEL_11, IDC_O_LABEL_12, IDC_O_LABEL_13, IDC_O_LABEL_14,
					
					IDC_EDIT_HEAD_0,IDC_EDIT_HEAD_1,IDC_EDIT_HEAD_2,IDC_EDIT_HEAD_3,IDC_EDIT_HEAD_4,
					IDC_EDIT_HEAD_5,IDC_EDIT_HEAD_6, IDC_EDIT_HEAD_7, IDC_EDIT_HEAD_8, IDC_EDIT_HEAD_9 };

int				OUTPUT_LABELS_ID[]={IDC_OUTLABEL_0,IDC_OUTLABEL_1,IDC_OUTLABEL_2,IDC_OUTLABEL_3,IDC_OUTLABEL_4,
					IDC_OUTLABEL_5, IDC_OUTLABEL_6, IDC_OUTLABEL_7, IDC_OUTLABEL_8, IDC_OUTLABEL_9,IDC_OUTLABEL_10};
int				D2GIS_LABELS_ID[]={IDC_GISLABEL_0,IDC_GISLABEL_1,IDC_GISLABEL_2,IDC_GISLABEL_3,
									IDC_GISLABEL_4,IDC_GISLABEL_5};

CButton			BOUT[FILE_OUT_NUM],BGIS[FILE_GIS_NUM];
int				BOUT_Num = FILE_OUT_NUM;
int				BGIS_Num = FILE_GIS_NUM;
int				BOUT_ID[] = {
					IDC_BUTTON_OUTFILE_0, IDC_BUTTON_OUTFILE_1, IDC_BUTTON_OUTFILE_2, IDC_BUTTON_OUTFILE_3,IDC_BUTTON_OUTFILE_4, 
					IDC_BUTTON_OUTFILE_5, IDC_BUTTON_OUTFILE_6, IDC_BUTTON_OUTFILE_7, IDC_BUTTON_OUTFILE_8, IDC_BUTTON_OUTFILE_9, IDC_BUTTON_OUTFILE_10 };

int				BOUT_EDIT_ID[]={IDC_EDIT_HEAD_0,IDC_EDIT_HEAD_1,IDC_EDIT_HEAD_2,IDC_EDIT_HEAD_3,IDC_EDIT_HEAD_4,
								IDC_EDIT_HEAD_5, IDC_EDIT_HEAD_6, IDC_EDIT_HEAD_7, IDC_EDIT_HEAD_8, IDC_EDIT_HEAD_9, IDC_EDIT_HEAD_6};
int				BGIS_ID[]={	
					IDC_BUTTON_GISFILE_0, IDC_BUTTON_GISFILE_1, IDC_BUTTON_GISFILE_2, 
					IDC_BUTTON_GISFILE_3, IDC_BUTTON_GISFILE_4, IDC_BUTTON_GISFILE_5};
CString			BOUT_Text[FILE_OUT_NUM];
CString			BGIS_Text[FILE_GIS_NUM];
int				BOUT_LABEL_ID[]={
					IDC_OUTLABEL_0, IDC_OUTLABEL_1, IDC_OUTLABEL_2, IDC_OUTLABEL_3,	IDC_OUTLABEL_4, 
					IDC_OUTLABEL_5, IDC_OUTLABEL_6, IDC_OUTLABEL_7, IDC_OUTLABEL_8, IDC_OUTLABEL_9, IDC_OUTLABEL_10 };
int				BGIS_LABEL_ID[]={
					IDC_GISLABEL_0, IDC_GISLABEL_1, IDC_GISLABEL_2, IDC_GISLABEL_3, IDC_GISLABEL_4, IDC_GISLABEL_5};
extern          CString		OutFile_Title[];
extern          CString		GISFile_Title[];
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSETFILE, CDialogEx)

CSETFILE::CSETFILE(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSETFILE::IDD, pParent)
{
}

CSETFILE::~CSETFILE()
{
}
void CSETFILE::OnDestroy()
{
	//
	m_OnY.DeleteObject();
	m_OffG.DeleteObject();
	//
	CDialogEx::OnDestroy();
}

void CSETFILE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_TAB_FILES, c_TabFile);
}

BOOL CSETFILE::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN ) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CSETFILE, CDialogEx)
//	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CSETFILE::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CSETFILE::OnBnClickedCancel)
//	ON_WM_DRAWITEM()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FILES, &CSETFILE::OnTcnSelchangeTabFiles)
	ON_BN_CLICKED(IDC_BUTTON_FILE_1, &CSETFILE::OnClickedButtonFile1)
	ON_BN_CLICKED(IDC_BUTTON_FILE_2, &CSETFILE::OnClickedButtonFile2)
	ON_BN_CLICKED(IDC_BUTTON_FILE_3, &CSETFILE::OnClickedButtonFile3)
	ON_BN_CLICKED(IDC_BUTTON_FILE_4, &CSETFILE::OnClickedButtonFile4)
	ON_BN_CLICKED(IDC_BUTTON_FILE_5, &CSETFILE::OnClickedButtonFile5)
	ON_BN_CLICKED(IDC_BUTTON_FILE_6, &CSETFILE::OnClickedButtonFile6)
	ON_BN_CLICKED(IDC_BUTTON_FILE_7, &CSETFILE::OnClickedButtonFile7)
	ON_BN_CLICKED(IDC_BUTTON_FILE_8, &CSETFILE::OnClickedButtonFile8)
	ON_BN_CLICKED(IDC_BUTTON_FILE_9, &CSETFILE::OnClickedButtonFile9)
	ON_BN_CLICKED(IDC_BUTTON_FILE_10, &CSETFILE::OnClickedButtonFile10)
	ON_BN_CLICKED(IDC_BUTTON_FILE_11, &CSETFILE::OnClickedButtonFile11)
	ON_BN_CLICKED(IDC_BUTTON_FILE_12, &CSETFILE::OnClickedButtonFile12)
	ON_BN_CLICKED(IDC_BUTTON_FILE_13, &CSETFILE::OnClickedButtonFile13)
	ON_BN_CLICKED(IDC_BUTTON_FILE_14, &CSETFILE::OnClickedButtonFile14)
	ON_BN_CLICKED(IDC_BUTTON_FILE_15, &CSETFILE::OnClickedButtonFile15)
	ON_BN_CLICKED(IDC_BUTTON_FILE_16, &CSETFILE::OnClickedButtonFile16)
	ON_BN_CLICKED(IDC_BUTTON_FILE_17, &CSETFILE::OnClickedButtonFile17)
	ON_BN_CLICKED(IDC_BUTTON_FILE_18, &CSETFILE::OnClickedButtonFile18)
	ON_BN_CLICKED(IDC_BUTTON_FILE_19, &CSETFILE::OnClickedButtonFile19)
	ON_BN_CLICKED(IDC_BUTTON_FILE_20, &CSETFILE::OnClickedButtonFile20)
	ON_BN_CLICKED(IDC_BUTTON_FILE_0, &CSETFILE::OnClickedButtonFile0)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_0, &CSETFILE::OnClickedButtonOutfile0)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_1, &CSETFILE::OnClickedButtonOutfile1)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_2, &CSETFILE::OnClickedButtonOutfile2)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_3, &CSETFILE::OnClickedButtonOutfile3)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_4, &CSETFILE::OnClickedButtonOutfile4)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_5, &CSETFILE::OnClickedButtonOutfile5)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_6, &CSETFILE::OnClickedButtonOutfile6)
	ON_BN_CLICKED(IDC_BUTTON_OUTFILE_7, &CSETFILE::OnClickedButtonOutfile7)
	ON_STN_DBLCLK(IDC_FILELABEL_1, &CSETFILE::OnDblclkFilelabel1)
	ON_STN_DBLCLK(IDC_FILELABEL_2, &CSETFILE::OnDblclkFilelabel2)
	ON_STN_DBLCLK(IDC_FILELABEL_3, &CSETFILE::OnDblclkFilelabel3)
	ON_STN_DBLCLK(IDC_FILELABEL_4, &CSETFILE::OnDblclkFilelabel4)
	ON_STN_DBLCLK(IDC_FILELABEL_5, &CSETFILE::OnDblclkFilelabel5)
	ON_STN_DBLCLK(IDC_FILELABEL_6, &CSETFILE::OnDblclkFilelabel6)
	ON_STN_DBLCLK(IDC_FILELABEL_7, &CSETFILE::OnDblclkFilelabel7)
	ON_STN_DBLCLK(IDC_FILELABEL_8, &CSETFILE::OnDblclkFilelabel8)
	ON_STN_DBLCLK(IDC_FILELABEL_9, &CSETFILE::OnDblclkFilelabel9)
	ON_STN_DBLCLK(IDC_FILELABEL_10, &CSETFILE::OnDblclkFilelabel10)
	ON_STN_DBLCLK(IDC_FILELABEL_11, &CSETFILE::OnDblclkFilelabel11)
	ON_STN_DBLCLK(IDC_FILELABEL_12, &CSETFILE::OnDblclkFilelabel12)
	ON_STN_DBLCLK(IDC_FILELABEL_13, &CSETFILE::OnDblclkFilelabel13)
	ON_STN_DBLCLK(IDC_FILELABEL_14, &CSETFILE::OnDblclkFilelabel14)
	ON_STN_DBLCLK(IDC_FILELABEL_15, &CSETFILE::OnDblclkFilelabel15)
	ON_STN_DBLCLK(IDC_FILELABEL_16, &CSETFILE::OnDblclkFilelabel16)
	ON_STN_DBLCLK(IDC_FILELABEL_17, &CSETFILE::OnDblclkFilelabel17)
	ON_STN_DBLCLK(IDC_FILELABEL_18, &CSETFILE::OnDblclkFilelabel18)
	ON_STN_DBLCLK(IDC_FILELABEL_19, &CSETFILE::OnDblclkFilelabel19)
	ON_STN_DBLCLK(IDC_FILELABEL_20, &CSETFILE::OnDblclkFilelabel20)
	ON_STN_DBLCLK(IDC_FILELABEL_21, &CSETFILE::OnDblclkFilelabel21)
	ON_STN_DBLCLK(IDC_OUTLABEL_0, &CSETFILE::OnDblclkOutlabel0)
	ON_STN_DBLCLK(IDC_OUTLABEL_1, &CSETFILE::OnDblclkOutlabel1)
	ON_STN_DBLCLK(IDC_OUTLABEL_2, &CSETFILE::OnDblclkOutlabel2)
	ON_STN_DBLCLK(IDC_OUTLABEL_3, &CSETFILE::OnDblclkOutlabel3)
	ON_STN_DBLCLK(IDC_OUTLABEL_4, &CSETFILE::OnDblclkOutlabel4)
	ON_STN_DBLCLK(IDC_OUTLABEL_5, &CSETFILE::OnDblclkOutlabel5)
	ON_STN_DBLCLK(IDC_OUTLABEL_6, &CSETFILE::OnDblclkOutlabel6)
	ON_STN_DBLCLK(IDC_OUTLABEL_7, &CSETFILE::OnDblclkOutlabel7)
//	ON_BN_CLICKED(IDOK2, &CSETFILE::OnBnClickedOk2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSETFILE::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_0, &CSETFILE::OnBnClickedButtonGisfile0)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_1, &CSETFILE::OnBnClickedButtonGisfile1)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_2, &CSETFILE::OnBnClickedButtonGisfile2)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_3, &CSETFILE::OnBnClickedButtonGisfile3)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_4, &CSETFILE::OnBnClickedButtonGisfile4)
	ON_BN_CLICKED(IDC_BUTTON_GISFILE_5, &CSETFILE::OnBnClickedButtonGisfile5)
	ON_STN_DBLCLK(IDC_GISLABEL_0, &CSETFILE::OnStnDblclickGislabel0)
	ON_STN_DBLCLK(IDC_GISLABEL_1, &CSETFILE::OnStnDblclickGislabel1)
	ON_STN_DBLCLK(IDC_GISLABEL_2, &CSETFILE::OnStnDblclickGislabel2)
	ON_STN_DBLCLK(IDC_GISLABEL_3, &CSETFILE::OnStnDblclickGislabel3)
	ON_STN_DBLCLK(IDC_GISLABEL_4, &CSETFILE::OnStnDblclickGislabel4)
	ON_STN_DBLCLK(IDC_GISLABEL_5, &CSETFILE::OnStnDblclickGislabel5)
	ON_STN_CLICKED(IDC_SAVE_0, &CSETFILE::OnStnClickedSave0)
	ON_STN_CLICKED(IDC_SAVEAS_0, &CSETFILE::OnStnClickedSaveas0)
END_MESSAGE_MAP()
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//  ONINIT DIALOG  初期化関数
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL CSETFILE::OnInitDialog()
{
//
//----------------------------------------  コントロールの移動とウィンドウサイズの変更
//
	CDialogEx::OnInitDialog();
	Move_Resize_Dialog();		// コントロールの移動
	//
	m_OnY.CreateSolidBrush(RGB(200,200,0));
	m_OffG.CreateSolidBrush(RGB(80,80,80));
//
//----------------------------------------  データセットのこぴー
//	
	memset(&DS,0,sizeof(DATASET));
	Copy_DSET( &DS, DSET );		// データコピー
//
////----------------------------------------  タブの初期化
	Init_Tab();
	//
	COLD = UNDEF;
	CTAB	= TAB_PARAM;
	CLAND	= 0;
	//
	CString		str;
	for (int i = 0; i < DS.LUnum; i++){
		str.Format("%d", i + 1);
		m_Combo.AddString(str);
	}
//	Set_Data();
	//
	////----------------------------------------  タブの初期化
	SetTimer(0, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
//-----------------------------------------------------------------------------------------------------------
//   MOVE RESIZE WINDOW
//-----------------------------------------------------------------------------------------------------------
BOOL CSETFILE::Move_Resize_Dialog()
{
	CRect	RefR,Crect,Mrect,Wrect;
	CWnd*	cw = GetDlgItem( IDC_GB_0 );
	cw->GetWindowRect( &RefR );
	int		MOVE_V,span,MOVE_H;
	this->GetWindowRect(&Wrect);
	//
	// IN FILE
	for(int i=0;i<BIN_Num;i++) {
		cw = GetDlgItem( BIN_LABEL_ID[i] );	// Label
		cw->GetWindowRect( &Crect );

		if( i == 0 ) {
			span = Crect.Height();			// 子オブジェクトなので相対的な位置
			MOVE_H = Crect.left - 25;
			MOVE_V = 50 - Crect.top ;
		}
		Crect.left -= MOVE_H;
		Crect.right -= MOVE_H;
		Crect.top	+= MOVE_V;
		Crect.bottom = Crect.top + span;
		
		cw->SetWindowTextA(File_Title[i]);
		cw->MoveWindow(&Crect,1);
		cw->RedrawWindow();
		//
		// ボタン
		cw = GetDlgItem( BIN_ID[i] );	// Button
		cw->GetWindowRect( &Crect );
		BFin[i] = cw;

		Crect.left -= MOVE_H;
		Crect.right -= MOVE_H;
		Crect.top	+= MOVE_V;
		Crect.bottom = Crect.top + span;
		
		cw->MoveWindow(&Crect,1);
		//
		// ボタン
		cw = GetDlgItem(BIN_SAVE_ID[i]);	// Button
		cw->GetWindowRect(&Crect);

		Crect.left -= MOVE_H;
		Crect.right -= MOVE_H;
		Crect.top += MOVE_V;
		Crect.bottom = Crect.top + span;

		cw->MoveWindow(&Crect, 1);
		//
		// ボタン
		cw = GetDlgItem(BIN_SAVEAS_ID[i]);	// Button
		cw->GetWindowRect(&Crect);

		Crect.left -= MOVE_H;
		Crect.right -= MOVE_H;
		Crect.top += MOVE_V;
		Crect.bottom = Crect.top + span;

		cw->MoveWindow(&Crect, 1);

	}
	//
	// OUT FILE
	for(int i=0;i<OUT_MOVE_NUM;i++) {
		cw = GetDlgItem( OUT_MOVE_IDS[i] );	// All
		cw->GetWindowRect( &Crect );

		if( i == 0 ) {
			MOVE_H = Crect.left - 45;		// 子オブジェクトなので相対的な位置
			MOVE_V = 80 - Crect.top;
			span = Crect.Height();
		}	

		Crect.left -= MOVE_H;
		Crect.right -= MOVE_H;
		Crect.top	+= MOVE_V;
		Crect.bottom = Crect.top + span;
		
		cw->MoveWindow(&Crect,1);
		cw->RedrawWindow();

	}
	// OUT LABEL
	for(int i=0;i<FILE_OUT_NUM;i++) {
		cw = GetDlgItem( BOUT_LABEL_ID[i] );	// Label
		cw->SetWindowTextA( BOUT_Text[i]);
	}
	for (int i = 0; i < FILE_OUT_NUM; i++) {
		BFout[i] = GetDlgItem(BOUT_ID[i]);	// All
	}

	// GIS LABEL
	for(int i=0;i<FILE_GIS_NUM;i++) {
		cw = GetDlgItem( BGIS_LABEL_ID[i] );	// Label
		cw->SetWindowTextA( BGIS_Text[i]);
	}
	for (int i = 0; i < FILE_GIS_NUM; i++) {
		BFgis[i] = GetDlgItem(BGIS_ID[i]);	// All
	}
	//
	// DIALOG WINDOW SIZE
	//
	this->GetWindowRect( &Crect );
	Crect.right = RefR.right + 15;
	this->MoveWindow(&Crect,1);
	this->RedrawWindow();
//
	return TRUE;
}
//-----------------------------------------------------------------------------------------------------------
//   INITIALIZE   TAB
//-----------------------------------------------------------------------------------------------------------
void CSETFILE::Init_Tab()
{
	CTabCtrl*	 CTab = (CTabCtrl*)GetDlgItem( IDC_TAB_FILES );
	//
	int        err = 0;
	CSize		Cs, Cret;
	CRect		Trect,rect;
	CTab->GetWindowRect( &Trect );
	//
	// 子ダイアログ作成
	//if (!err) if (!Dlg_Param.Create(IDD_DIALOG_PARAM, this)) err = 1;
	//// 子ダイアログ移動
	//if (!err)
	//{
	//	Dlg_Param.GetClientRect(&rect);
	//	rect.OffsetRect(20, 40);
	//	Dlg_Param.MoveWindow(&rect, FALSE);
	//}
	//
	TAB.mask = TCIF_PARAM;
	Cs.cx = 160;	Cs.cy = 24;
	Cret = CTab->SetItemSize( Cs );
	//
	TAB.mask = TCIF_TEXT;
	TAB.pszText = "PARAMS";
	CTab->InsertItem(0, &TAB);
	TAB.pszText = "INFILE";
	CTab->InsertItem(1, &TAB);
	TAB.pszText = "OUTPUT";
	CTab->InsertItem(2, &TAB);
	//
	c_TabFile.HighlightItem(0, TRUE);
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//  ＦＩＸ ＦＵＮＣＴＩＯＮ
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int AFXAPI CSETFILE::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED && lpData)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
//   BUTTON_DIR
//-----------------------------------------------------------------------------------------------------------
BOOL	CSETFILE::Button_Dir(CString* m_DirName,char* m_RecentPath )
{
	CWnd			*pWnd;
	static char		pszRetPath[CHARSIZE];
	LPMALLOC		pMalloc;
	//--------------------------------------
	//	ディレクトリ選択ダイアログの表示
	//--------------------------------------
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{ 
		char		cRetPath[CHARSIZE];
		ITEMIDLIST	*pList;
		BROWSEINFO	Info;

		pWnd = (CWnd*)AfxGetApp()->m_pMainWnd;
		HWND hWnd = pWnd->m_hWnd; 
		Info.hwndOwner = hWnd;
		Info. pidlRoot = 0;
		Info.pszDisplayName = cRetPath;
		Info.lpszTitle =  _T("フォルダを選択してください");
		Info.lpfn   = BrowseCallbackProc;
		Info.lParam = (LPARAM)m_RecentPath;
		Info.ulFlags = BIF_RETURNONLYFSDIRS;	//フォルダの選択のみ
		

		pWnd->ModifyStyle(WS_CHILD,WS_POPUP,0);

		//---  ダイアログ表示  -------------
		if( (pList = (ITEMIDLIST	*)SHBrowseForFolder(&Info)) == NULL ) {pMalloc->Release();return FALSE;}
		// ITEMIDLIST からフルパスを得る
		SHGetPathFromIDList(pList,pszRetPath);
		//ITEMIDLIST の開放
		pMalloc->Free(pList);
		//選択ディレクトリ表示
		*m_DirName = pszRetPath;
		strcpy(m_RecentPath,*m_DirName);
		pMalloc->Release();
		//
	}
	return TRUE;
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
//   ON  TIMER
//-----------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CSETFILE::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer( 0 );
//
	Change_Control();
//	Set_Data();
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//   タブ変更
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CSETFILE::OnTcnSelchangeTabFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
//	if( CTAB == TAB_PARAM ) Data_Update();
	//
	CTabCtrl*	 SFTab = (CTabCtrl*)GetDlgItem( IDC_TAB_FILES );
	//
	COLD = CTAB;
	CTAB = SFTab->GetCurSel();
	Change_Control();
	SFTab->RedrawWindow();
	Change_Control();
	//
	Set_Data();
	//
	*pResult = 0;
}

void  CSETFILE::Change_Control()
{
	CWnd	*ct,*cw;
	CRect	rect;
	//
	if (CTAB != COLD) {
		c_TabFile.HighlightItem(COLD, FALSE);
		c_TabFile.HighlightItem(CTAB, TRUE);
	}
	//
	// TAB PARAM-------------------------------------------------- 
	for(int i=0;i<BP_LABEL_NUM;i++) {
		cw = GetDlgItem( BP_LABEL_ID[i] );
		if( CTAB == TAB_PARAM ) 	cw->ShowWindow( SW_SHOW );
		else    	cw->ShowWindow( SW_HIDE );
	}
	for(int i=0;i<BP_EDIT_NUM;i++) {
		cw = GetDlgItem( BP_EDIT_ID[i] );
		if( CTAB == TAB_PARAM ) 	cw->ShowWindow( SW_SHOW );
		else    					cw->ShowWindow( SW_HIDE );
	}
	if( CTAB == TAB_PARAM ) 	m_Combo.ShowWindow( SW_SHOW );
	else    					m_Combo.ShowWindow( SW_HIDE );

	//
	// TAB INFILE-------------------------------------------------
	CWnd*		cs;
	CWnd*		csa;
	for(int i=0;i<BIN_Num;i++) {
		ct = GetDlgItem( BIN_LABEL_ID[i] );
		ct->SetWindowTextA(File_Title[i]);
		//
		cs = GetDlgItem(BIN_SAVE_ID[i]);
		csa = GetDlgItem(BIN_SAVEAS_ID[i]);
		//
		cw = GetDlgItem(BIN_ID[i]);
		if( CTAB == TAB_INFILE ) {
			cw->ShowWindow(SW_SHOW);
			ct->ShowWindow(SW_SHOW);
			cs->ShowWindow(SW_SHOW);
			csa->ShowWindow(SW_SHOW);
//
			cw->EnableWindow(TRUE);
			ct->EnableWindow(TRUE);
			//
			if (DSET.in_use[i]) {
				if (DSET.in_avail[i]) {
					cs->EnableWindow(TRUE);
					csa->EnableWindow(TRUE);
				}
				else   {
					cs->EnableWindow(FALSE);
					csa->EnableWindow(FALSE);
				}
			}
			else {
				cs->EnableWindow(FALSE);
				csa->EnableWindow(FALSE);
			}
			//
		}
		else    {
			cw->ShowWindow(SW_HIDE);
			ct->ShowWindow(SW_HIDE);
			cs->ShowWindow(SW_HIDE);
			csa->ShowWindow(SW_HIDE);
		}
	}
	//
	// TAB OUTFILE-----------------------------------------------
	for (int i = 0; i < BOUT_Num; i++) {
		cw = GetDlgItem(OUTPUT_LABELS_ID[i]);
		cw->SetWindowTextA(OutFile_Title[i]);
	}
	for (int i = 0; i < BGIS_Num; i++) {
		cw = GetDlgItem(D2GIS_LABELS_ID[i]);
		cw->SetWindowTextA( GISFile_Title[i] );
	}
	for (int i = 0; i<OUT_MOVE_NUM; i++) {
		cw = GetDlgItem( OUT_MOVE_IDS[i] );
		if (CTAB == TAB_OUTFILE) 	cw->ShowWindow(SW_SHOW);
		else						cw->ShowWindow(SW_HIDE);
	}
	//
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//   データ設定・変更
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int  CSETFILE::Get_Set_File_Name(int no)
{
	CString		fname,ttl;
	char		Rpath[SIZE_01K],Title[SIZE_01K];
	//
	if( CTAB == TAB_INFILE ) {
		strcpy(Title,File_Title[no]);
		if(! Button_File(TRUE,&fname,m_RecentPath,Title,"*.*") ) return 0;
		strcpy( DS.File_names[no],fname );
		Get_Relative_Path( DS.File_names[no],DS.Proj_Folder,Rpath);
		ttl = Rpath;
		BFin[no]->SetWindowTextA( ttl );
		//
		DS.in_use[no] = DS.in_exist[no] =  TRUE;
	}
	else     {
		strcpy(Title,OutFile_Title[no]);
		if(! Button_File(TRUE,&fname,m_RecentPath,Title,"*.*") ) return 0;
		strcpy( DS.Out_names[no],fname );
		Get_Relative_Path( DS.Out_names[no],DS.Proj_Folder,Rpath);
		ttl = Rpath;
		BFout[no]->SetWindowTextA(ttl);
		//
		DS.out_use[no] = DS.out_exist[no] = TRUE;
	}
	//
	Set_Data();

	return no;
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int  CSETFILE::Get_D2GIS_File_Name(int no)
{
	CString		fname,ttl;
	char		Rpath[SIZE_01K],Title[SIZE_01K];
	//
	strcpy(Title,GISFile_Title[no]);
	if(! Button_File(TRUE,&fname,m_RecentPath,Title,"*.*") ) return 0;
	//
	strcpy( DS.GIS_names[no],fname );
	Get_Relative_Path( DS.GIS_names[no],DS.Proj_Folder,Rpath);
	ttl = Rpath;
	//
	BFgis[no]->SetWindowTextA(ttl);
	//
	DS.gis_use[no] = DS.gis_exist[no] = TRUE;
	//
	Set_Data();

	return no;
}
void CSETFILE::Switch_File(int no)
{
	CString		fname,ttl;
	//
	if( CTAB == TAB_INFILE ) {
		DS.in_use[no] = FALSE;
		DS.in_use[no] = FALSE;
		DS.File_names[no][0] = 0x00;
	}
	else {
		if( no < 100 ) {
			DS.out_use[no] =  FALSE;
			DS.Out_names[no][0] = 0x00;
		}
		else {
			no -= 100;
			DS.gis_use[no] = FALSE;
			DS.GIS_names[no][0] = 0x00;
		}
	}
	//
	Set_Data();
	return;
}

//-----------------------------------------------------------------------------------------------------------
//   SET DATA
//-----------------------------------------------------------------------------------------------------------
void	CSETFILE::Set_Data()
{
	char		Rpath[SIZE_01K],Fullname[SIZE_01K];
	CString		Rname;
	CWnd		*cw;
	CWnd		*ce;
	//
	if( CTAB == TAB_PARAM ) {
		Set_Param_Data();
	}
	//
	if( CTAB == TAB_INFILE ) {
		for(int i=0;i<FILE_IN_NUM;i++) {
			cw = GetDlgItem( BIN_LABEL_ID[i] );
			if( DS.in_use[i] ) {
				Get_Relative_Path( DS.File_names[i],DS.Proj_Folder,Rpath);
				Rname = Rpath;
				BFin[i]->SetWindowTextA(Rname);
				//
				cw->EnableWindow( TRUE );
			}
			else	{
				BFin[i]->SetWindowTextA("-");
				//
				cw->EnableWindow( FALSE );
			}
		}
	}
	//
	if( CTAB == TAB_OUTFILE ) {
		for(int i=0;i<FILE_OUT_NUM;i++) {
			if( i < FILE_OUT_NUM-1 ) {
				cw = GetDlgItem( BOUT_LABEL_ID[i] );
				ce = GetDlgItem( BOUT_EDIT_ID[i] );
				if( DS.out_use[i] ) {
					Get_Dir( DS.Out_names[i],Fullname);
					Get_Relative_Path( Fullname,DS.Proj_Folder,Rpath);
					Rname = Rpath;
					BFout[i]->SetWindowTextA(Rname);
					Get_Title( DS.Out_names[i],Rpath);
					ce->SetWindowTextA( Rpath );
					//
					cw->EnableWindow( TRUE );
					ce->EnableWindow( TRUE );
				}
				else	{
					BFout[i]->SetWindowTextA("-");
					ce->SetWindowTextA("");
					cw->EnableWindow( FALSE );
					ce->EnableWindow( FALSE );
				}
			}
			else {
				cw = GetDlgItem( BOUT_LABEL_ID[i] );
				if( DS.out_use[i] ) {
					Get_Relative_Path( DS.Out_names[i],DS.Proj_Folder,Rpath);
					Rname = Rpath;
					BFout[i]->SetWindowTextA(Rname);
					//
					cw->EnableWindow( TRUE );
				}
				else	{
					BFout[i]->SetWindowTextA("-");
					cw->EnableWindow( FALSE );
				}
			}
		}
		//
		for(int i=0;i<FILE_GIS_NUM;i++) {
			cw = GetDlgItem( BGIS_LABEL_ID[i] );
			if( DS.gis_exist[i] ) {
				Get_Relative_Path( DS.GIS_names[i],DS.Proj_Folder,Rpath);
				Rname = Rpath;
				BFgis[i]->SetWindowTextA(Rname);
				//
				cw->EnableWindow( TRUE );
			}
			else	{
				BFgis[i]->SetWindowTextA("-");
				cw->EnableWindow( FALSE );
			}
		}
	}
}
void	CSETFILE::Set_Param_Data()
{
	CWnd*	cw;
	double	val;
	//
	for(int i=0;i<BP_EDIT_NUM;i++) {
		if (DS.LUnum == 0 && (i >= 10 && i <= 20)) continue;
		cw = GetDlgItem( BP_EDIT_ID[i] );
		switch ( i ) {
			case 0 : Set_CWnd_Text(cw,DS.SW_LatLong);break;
			case 1 : Set_CWnd_Text(cw,DS.SW_Dir);break;
			case 2 : Set_CWnd_Text(cw,DS.Hours,FALSE);break;
			case 3 : Set_CWnd_Text(cw,DS.DT,FALSE);break;
			case 4 : Set_CWnd_Text(cw,DS.DT_Riv,FALSE);break;
			case 5 : Set_CWnd_Text(cw,DS.DT_Out,FALSE);break;
			case 6 : Set_CWnd_Text(cw,DS.Rain_X,1,FALSE);break;
			case 7 : Set_CWnd_Text(cw,DS.Rain_Y,1,FALSE);break;
			case 8: if (DS.Rain_dx != 0.) {
						val = 1. / DS.Rain_dx; Set_CWnd_Text(cw, val, 0, FALSE);
					}
					break;
			case 9: if (DS.Rain_dy != 0.) {
						val = 1. / DS.Rain_dy; Set_CWnd_Text(cw, val, 0, FALSE);
					}
				    break;
			// 
			//  land usage elements
			case 10 :Set_CWnd_Text(cw,DS.LUdata[CLAND].SW_kinema);break;
			case 11 :Set_CWnd_Text(cw,DS.LUdata[CLAND].dm,3,TRUE);break;
			case 12 :Set_CWnd_Text(cw,DS.LUdata[CLAND].da,3,TRUE);break;
			case 13 :Set_CWnd_Text(cw,DS.LUdata[CLAND].ka,3,TRUE);break;
			case 14 :Set_CWnd_Text(cw,DS.LUdata[CLAND].beta,3,TRUE);break;
			case 15 :Set_CWnd_Text(cw,DS.LUdata[CLAND].soildepth,3,TRUE);break;
			case 16 :Set_CWnd_Text(cw,DS.LUdata[CLAND].ns_slope,3,TRUE);break;
			case 17 :Set_CWnd_Text(cw,DS.LUdata[CLAND].ksv,3,TRUE);break;
			case 18 :Set_CWnd_Text(cw,DS.LUdata[CLAND].delta,3,TRUE);break;
			case 19 :Set_CWnd_Text(cw,DS.LUdata[CLAND].faif,3,TRUE);break;
			case 20 :Set_CWnd_Text(cw,DS.LUdata[CLAND].limit,3,TRUE);break;
			// 
			//  river ns
			case 21 :Set_CWnd_Text(cw,DS.Ns_River,3,TRUE);break;
			// 
			//  river thresh
			case 22 :Set_CWnd_Text(cw,DS.Riv_Thresh,1,TRUE);break;
			case 23 :Set_CWnd_Text(cw,DS.Cof_WC,2,TRUE);break;
			case 24 :Set_CWnd_Text(cw,DS.Cof_WS,2,TRUE);break;
			case 25 :Set_CWnd_Text(cw,DS.Cof_DC,2,TRUE);break;
			case 26 :Set_CWnd_Text(cw,DS.Cof_DS,2,TRUE);break;
			case 27 :Set_CWnd_Text(cw,DS.Cof_H,2,TRUE);break;
			case 28 :Set_CWnd_Text(cw,DS.Cof_Hlim,1,TRUE);break;
			// 
			//  evaporation
			case 29 :Set_CWnd_Text(cw,DS.Evp_X,1,TRUE);break;
			case 30 :Set_CWnd_Text(cw,DS.Evp_Y,1,TRUE);break;
			case 31: if (DS.Evp_DX != 0.) {
						 val = 1. / DS.Evp_DX; Set_CWnd_Text(cw, val, 0, FALSE);
					 }
					 break;
			case 32: if (DS.Evp_DY != 0.) {
						 val = 1. / DS.Evp_DY; Set_CWnd_Text(cw, val, 0, FALSE);
			         }
					 break;
			// 
			//  drain
			case 33 :Set_CWnd_Text(cw,DS.Drn_X,1,TRUE);break;
			case 34 :Set_CWnd_Text(cw,DS.Drn_Y,1,TRUE);break;
			case 35:if (DS.Drn_DX != 0.) {
						val = 1. / DS.Drn_DX; Set_CWnd_Text(cw, val, 0, FALSE);
			        }
					break;
			case 36:if (DS.Drn_DY != 0.) {
						val = 1. / DS.Drn_DY; Set_CWnd_Text(cw, val, 0, FALSE);
					}
					break;
			// 
			//  comment
			case 37:cw->SetWindowTextA(DS.Proj_Title); break;
		}
	}
	//  landuse list num
	//
	char	str[SIZE_01K];
	m_Combo.SetCurSel(CLAND);
	cw = GetDlgItem( IDC_PLABEL_13 );	// LUnum
	sprintf(str," / %d",DS.LUnum);
	cw->SetWindowTextA( str );
	//
	UDF;
}
void	CSETFILE::Data_Update()
{
	CEdit*		ce;
	char		str[SIZE_01K];
	double		val;
	//
	for(int i=0;i<BP_EDIT_NUM;i++) {
		ce = (CEdit*)GetDlgItem( BP_EDIT_ID[i] );
		if( ce->GetModify() ) {
			ce->GetWindowTextA(str,SIZE_01K );
			switch( i ) {
				case 0 : DS.SW_LatLong	= (BYTE)atoi( str );break;
				case 1 : DS.SW_Dir		= (BYTE)atoi( str );break;
				case 2 : DS.Hours		= atoi( str );break;
				case 3 : DS.DT			= atoi( str );break;
				case 4 : DS.DT_Riv		= atoi( str );break;
				case 5 : DS.DT_Out		= atoi( str );break;
				case 6 : DS.Rain_X		= atof( str );break;
				case 7 : DS.Rain_Y		= atof( str );break;
				case 8 : val = 1./atof( str ); DS.Rain_dx = val;break;
				case 9 : val = 1./atof( str ); DS.Rain_dy = val;break;
				//
				case 10 :DS.LUdata[CLAND].SW_kinema = (BYTE)atoi( str );break;
				case 11 :DS.LUdata[CLAND].dm		= atof( str );break;
				case 12 :DS.LUdata[CLAND].da		= atof( str );break;
				case 13 :DS.LUdata[CLAND].ka		= atof( str );break;
				case 14 :DS.LUdata[CLAND].beta		= atof( str );break;
				case 15 :DS.LUdata[CLAND].soildepth = atof( str );break;
				case 16 :DS.LUdata[CLAND].ns_slope	= atof( str );break;
				case 17 :DS.LUdata[CLAND].ksv		= atof( str );break;
				case 18 :DS.LUdata[CLAND].delta		= atof( str );break;
				case 19 :DS.LUdata[CLAND].faif		= atof( str );break;
				case 20 :DS.LUdata[CLAND].limit		= atof( str );break;
				//
				case 21 :DS.Ns_River	= atof( str );break;
				//
				case 22 :DS.Riv_Thresh	= atof( str );break;
				case 23 :DS.Cof_WC		= atof( str );break;
				case 24 :DS.Cof_WS		= atof( str );break;
				case 25 :DS.Cof_DC		= atof( str );break;
				case 26 :DS.Cof_DS		= atof( str );break;
				case 27 :DS.Cof_H		= atof( str );break;
				case 28 :DS.Cof_Hlim	= atof( str );break;
				// 
				case 29 :DS.Evp_X		= atof( str );break;
				case 30 :DS.Evp_Y		= atof( str );break;
				case 31 : val = 1./atof( str );DS.Evp_DX=val;break;
				case 32 : val = 1./atof( str );DS.Evp_DY=val;break;
				// 
				case 33 :DS.Drn_X		= atof( str );break;
				case 34 :DS.Drn_Y		= atof( str );break;
				case 35 : val = 1./atof( str );DS.Drn_DX=val;break;
				case 36 : val = 1./atof( str );DS.Drn_DY=val;break;
				// 
				//  d2gis
				case 37:strcpy(DS.Proj_Title, str); break;
			}
		}
	}
}
void	CSETFILE::OnSelchangeCombo1()
{
	CEdit*		ce;
	char		str[SIZE_01K];
	for(int i=10;i<=20;i++) {
		ce = (CEdit*)GetDlgItem( BP_EDIT_ID[i] );
		if( ce->GetModify() ) {
			ce->GetWindowTextA(str,SIZE_01K );
			switch( i ) {
				case 10 :DS.LUdata[CLAND].SW_kinema = (BYTE)atoi( str );break;
				case 11 :DS.LUdata[CLAND].dm = atof( str );break;
				case 12 :DS.LUdata[CLAND].da = atof( str );break;
				case 13 :DS.LUdata[CLAND].ka = atof( str );break;
				case 14 :DS.LUdata[CLAND].beta = atof( str );break;
				case 15 :DS.LUdata[CLAND].soildepth = atof( str );break;
				case 16 :DS.LUdata[CLAND].ns_slope = atof( str );break;
				case 17 :DS.LUdata[CLAND].ksv = atof( str );break;
				case 18 :DS.LUdata[CLAND].delta = atof( str );break;
				case 19 :DS.LUdata[CLAND].faif = atof( str );break;
				case 20 :DS.LUdata[CLAND].limit = atof( str );break;
			}
		}
	}
	//
	CLAND = m_Combo.GetCurSel();
	Set_Param_Data();
}

	//
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//   終了処理
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CSETFILE::OnBnClickedOk()	// Save
{
	if( CTAB == TAB_PARAM ) Data_Update();
	//
	// D2GIS ファイルが追加された場合は読み込みを開始する。 未実装 
	//CBUSY*		CB;
	//CB = new CBUSY;
	//CB->Create( IDD_BUSY );
	//CB->SetWindowTextA("Check & Read D2GIS data");
	//CB->ShowWindow( SW_SHOW );
	//for(int f=0;f<FILE_GIS_NUM;f++) {
	//	if( ! DS.gis_exist[f]  && DS.gis_exist[f] ) {	// DSET では無くて、今回指示された。
	//		if( FAILED(  Read_D2gis_File( f,DS.GIS_names[f],MESH) ) ) continue;
	//		DS.Cgis_Exist++;
	//		DS.Cgis_Need++;
	//	}
	//}
	////
	Copy_DSET(&DSET,DS);
//	FileOut_RRI_Input( DSET );
	Delete_DSET( &DS );
	//
	CDialogEx::OnOK();
}
//void CSETFILE::OnBnClickedOk2()	// Save As
//{
//	if( CTAB == TAB_PARAM ) Data_Update();
//	//
//	CString	fname;
//	if( ! Button_File(FALSE,&fname,m_RecentPath,"RRI Input File","txt") ) return;
//	//
//	strcpy(DS.InputFile, fname );
//	FileOut_RRI_Input( DS );
//	Delete_DSET( &DS );
//	//
//	CDialogEx::OnOK();
//}

void CSETFILE::OnBnClickedCancel()
{
	Delete_DSET( &DS );
	CDialogEx::OnCancel();
}

void CSETFILE::FileOut_RRI_Input(DATASET  DS )
{
	FILE*	fp;
	char	Rname[SIZE_1K];
	if ((fp = fopen(DS.InputFile, "w")) == NULL) return;	// 
	//
	fprintf(fp, "%s\n\n", DS.Proj_Title);
	//_______________________________________________________________
	//		1 基本ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i<4; i++) {
		Get_Relative_Path(DS.File_names[i], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", Rname);
	}
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		2 [simulation]諸元
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d    # utm(1) or latlon(0)\n", (int)DS.SW_LatLong);
	fprintf(fp, "%d    # 4-direction (0), 8-direction(1)\n", (int)DS.SW_Dir);
	fprintf(fp, "%d    # lasth(hour)\n", DS.Hours);
	fprintf(fp, "%d    # dt(second)\n", DS.DT);
	fprintf(fp, "%d    # dt_riv\n", DS.DT_Riv);
	fprintf(fp, "%d    # outnum [-]\n", DS.Out_Num);
	fprintf(fp, "%lf   # xllcorner_rain\n", DS.Rain_X);
	fprintf(fp, "%lf    # yllcorner_rain\n", DS.Rain_Y);
	fprintf(fp, "%.10lf %.10lf    # cellsize_rain\n\n", DS.Rain_dx, DS.Rain_dy);
	//_______________________________________________________________
	//		3 [landuse]諸元
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%.3lf     # ns_river\n", DS.Ns_River);
	fprintf(fp, "%d    # num_of_landuse\n", DS.LUnum);
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%d", DS.LUdata[i].SW_kinema);
		else         fprintf(fp, "   %d", DS.LUdata[i].SW_kinema);
	}
	fprintf(fp, "    # diffusion(1) orr kinematic(0)\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].ns_slope);
		else         fprintf(fp, "   %.3lf", DS.LUdata[i].ns_slope);
	}
	fprintf(fp, "     # ns_slope\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].soildepth);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].soildepth);
	}
	fprintf(fp, "     # soildepth\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].gammaa);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].gammaa);
	}
	fprintf(fp, "     # gammaa\n\n");
	//---------------------------------------------------------------------------
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].ksv);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].ksv);
	}
	fprintf(fp, "     # ksv\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].faif);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].faif);
	}
	fprintf(fp, "     # faif\n\n");
	//---------------------------------------------------------------------------
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].ka);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].ka);
	}
	fprintf(fp, "     # ka\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].gammam);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].gammam);
	}
	fprintf(fp, "     # gammam\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].beta);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].beta);
	}
	fprintf(fp, "     # beta\n\n");
	//---------------------------------------------------------------------------
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].kgv);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].kgv);
	}
	fprintf(fp, "     # kgv\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].gammag);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].gammag);
	}
	fprintf(fp, "     # gammag\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.5lf", DS.LUdata[i].tg);
		else         fprintf(fp, "    %.5lf", DS.LUdata[i].tg);
	}
	fprintf(fp, "     # tg\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].fpg);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].fpg);
	}
	fprintf(fp, "     # fpg\n");
	//
	for (int i = 0; i<DS.LUnum; i++) {
		if (i == 0) fprintf(fp, "%.3lf", DS.LUdata[i].init_cond_gw);
		else         fprintf(fp, "    %.3lf", DS.LUdata[i].init_cond_gw);
	}
	fprintf(fp, "     # init_cond_gw\n\n");
	//_______________________________________________________________
	//		河道諸元
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%.1lf      # riv_thresh\n", DS.Riv_Thresh);
	fprintf(fp, "%.3lf      # width_param_c (2.5)\n", DS.Cof_WC);
	fprintf(fp, "%.3lf      # width_param_s (0.4)\n", DS.Cof_WS);
	fprintf(fp, "%.3lf      # depth_param_c (0.1)\n", DS.Cof_DC);
	fprintf(fp, "%.3lf      # depth_param_s (0.4)\n", DS.Cof_DS);
	fprintf(fp, "%.3lf      # height_param\n", DS.Cof_H);
	fprintf(fp, "%.1lf       # height_limit_param\n\n", DS.Cof_Hlim);
	//_______________________________________________________________
	//		河川ファイルの設定
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (DS.in_use[WIDTH_FILE]) {
		fprintf(fp, "1\n");
		Get_Relative_Path(DS.File_names[WIDTH_FILE], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", Rname);
		Get_Relative_Path(DS.File_names[DEPTH_FILE], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", Rname);
		Get_Relative_Path(DS.File_names[HEIGHT_FILE], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", Rname);
	}
	else      {
		fprintf(fp, "0 \n");
		fprintf(fp, "./infile/width.txt\n");
		fprintf(fp, "./infile/depth.txt\n");
		fprintf(fp, "./infile/height.txt\n");
	}
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		初期値ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 4; i++) {
		if (i == 0)  fprintf(fp, "%d", (int)DS.in_use[HS_FILE + i]);
		else         fprintf(fp, "  %d", (int)DS.in_use[HS_FILE + i]);
	}
	Get_Relative_Path(DS.File_names[HS_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[HR_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[HG_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[GAMPT_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		境界条件設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[HS_WLEV_FILE]);
	fprintf(fp, "  %d\n", (int)DS.in_use[HR_WLEV_FILE]);
	//
	Get_Relative_Path(DS.File_names[HS_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[HR_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		流量境界条件ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[QS_WLEV_FILE]);
	fprintf(fp, "  %d\n", (int)DS.in_use[QR_WLEV_FILE]);
	//
	Get_Relative_Path(DS.File_names[QS_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[QR_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		土地利用ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[LU_FILE]);
	Get_Relative_Path(DS.File_names[LU_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		ダム設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[DAM_CNT_FILE]);
	Get_Relative_Path(DS.File_names[DAM_CNT_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		分流設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[DIV_FILE]);
	Get_Relative_Path(DS.File_names[DIV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		PotentialET  ?
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[POTENT_FILE]);
	Get_Relative_Path(DS.File_names[POTENT_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	fprintf(fp, "%.1lf      # xllcorner_evp\n", DS.Evp_X);
	fprintf(fp, "%.1lf      # yllcorner_evp\n", DS.Evp_Y);
	fprintf(fp, "%.10lf  %.10lf     # cellsize\n\n", DS.Evp_DX, DS.Evp_DY);
	//_______________________________________________________________
	//		? Add 2014/11
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[LENGTH_FILE]);
	Get_Relative_Path(DS.File_names[LENGTH_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		? Add 2014/11 No 2 SEC_MAP
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[SEC_MAP_FILE]);
	Get_Relative_Path(DS.File_names[SEC_MAP_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", Rname);
	Get_Relative_Path(DS.File_names[SEC_HEADER], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//_______________________________________________________________
	//		出力設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i<FILE_OUT_NUM - 1; i++) {
		if (i == 0) fprintf(fp, "%d", (int)(DS.out_use[i]));
		else         fprintf(fp, "  %d", (int)(DS.out_use[i]));
	} CR;
	for (int i = 0; i<FILE_OUT_NUM - 1; i++) {
		Get_Relative_Path(DS.Out_names[i], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", Rname);
	}
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		TECOUT 設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.out_use[SEC_MAP_FILE]);
	Get_Relative_Path(DS.Out_names[OUT_TECPLOT], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n\n", Rname);
	//
	// End
	fclose(fp);
	return;
	return;
}

void CSETFILE::Copy_DSET( DATASET* DT,DATASET DD )
{
	DT->set = DD.set;
//	DT->Set_CaseDir = DD.Set_CaseDir;
	//
	strcpy(DT->Proj_Folder,DD.Proj_Folder);
	DT->Cin_Need = DD.Cin_Need;
	DT->Cin_Exist = DD.Cin_Exist;
	DT->Cout_Need = DD.Cout_Need;
	DT->Cout_Exist = DD.Cout_Exist;
	DT->Cgis_Need = DD.Cgis_Need;
	DT->Cgis_Exist = DD.Cgis_Exist;
	//
	for(int i=0;i<FILE_IN_NUM;i++) {
		DT->in_exist[i] = DD.in_exist[i];
		DT->in_use[i] = DD.in_use[i];
		DT->need_save[i] = DD.need_save[i];
		strcpy(DT->File_names[i],DD.File_names[i]);
	}
	//
	// OUTPUT file
	for(int i=0;i<FILE_OUT_NUM;i++) {
		DT->out_exist[i] = DD.out_exist[i];
		DT->out_use[i] = DD.out_use[i];
		strcpy(DT->Out_names[i],DD.Out_names[i]);
	}
	//
	// GIS file
	for(int i=0;i<FILE_GIS_NUM;i++) {
		DT->gis_exist[i] = DD.gis_exist[i];
		DT->gis_use[i] = DD.gis_use[i];
		strcpy(DT->GIS_names[i],DD.GIS_names[i]);
	}
	strcpy(DT->Proj_Title, DD.Proj_Title);
	strcpy(DT->Infile_Dir, DD.Infile_Dir);
	strcpy(DT->Output_Dir, DD.Output_Dir);
	//
	DT->SW_Dir = DD.SW_Dir;
	DT->SW_LatLong = DD.SW_LatLong;
	DT->Hours = DD.Hours;
	DT->DT = DD.DT ;
	DT->DT_Out = DD.DT_Out ;
	DT->DT_Riv = DD.DT_Riv ;
	//
	DT->Rain_X = DD.Rain_X ;
	DT->Rain_Y = DD.Rain_Y ;
	DT->Rain_dx = DD.Rain_dx ;
	DT->Rain_dy = DD.Rain_dy ;
	//
	DT->LUnum = DD.LUnum ;
	if( DT->LUdata != NULL ) SAFE_FREE( DT->LUdata );
	if (DD.LUnum != 0) {
		DT->LUdata = (LUINFO*)malloc(DD.LUnum*sizeof( LUINFO )) ;
		for(int i=0;i<DD.LUnum;i++) memcpy(&DT->LUdata[i],&DD.LUdata[i],sizeof( LUINFO ));
	}
	//
	DT->damcnt_Num = DD.damcnt_Num ;
	for(int i=0;i<DD.damcnt_Num;i++) memcpy(&DT->DAMC[i],&DD.DAMC[i],sizeof( DAMCNT ));
	//
	DT->Break_Nums = DD.Break_Nums ;
	DT->Break_Cells = DD.Break_Cells ;
	for(int i=0;i<DD.Break_Nums;i++) DT->BreakTimes[i] = DD.BreakTimes[i] ;
	for(int i=0;i<DD.Break_Cells;i++) memcpy(&DT->BreakSet[i],&DD.BreakSet[i],sizeof( IXYCOORD ));
	//
	DT->Ns_River = DD.Ns_River ;
	DT->Riv_Thresh = DD.Riv_Thresh ;
	DT->Cof_WC = DD.Cof_WC ;
	DT->Cof_WS = DD.Cof_WS ;
	DT->Cof_DC = DD.Cof_DC ;
	DT->Cof_DS = DD.Cof_DS ;
	DT->Cof_H = DD.Cof_H ;
	DT->Cof_Hlim = DD.Cof_Hlim ;
	DT->Init_HS = DD.Init_HS ;
	DT->Init_HR = DD.Init_HR ;
	DT->Evp_X = DD.Evp_X ;
	DT->Evp_Y = DD.Evp_Y ;
	DT->Evp_DX = DD.Evp_DX ;
	DT->Evp_DY = DD.Evp_DY ;
	//
	DT->Drn_X = DD.Drn_X ;
	DT->Drn_Y = DD.Drn_Y ;
	DT->Drn_DX = DD.Drn_DX ;
	DT->Drn_DY = DD.Drn_DY ;
	//
	if( DD.WLEV.set ) Copy_TIMESET( &DT->WLEV,&DD.WLEV);
	//
	if( DD.DISC.set ) Copy_TIMESET( &DT->DISC,&DD.DISC);
	//
	if( DD.DAMREC.set )  Copy_TIMESET( &DT->DAMREC,&DD.DAMREC);
	//
	if( DD.DIV.set )  Copy_TIMESET( &DT->DIV,&DD.DIV);
}

void CSETFILE::Delete_DSET( DATASET* DS )
{
	if(DS->LUnum != 0 )  SAFE_FREE( DS->LUdata );
	Free_TIMESET( &DS->WLEV );
	Free_TIMESET( &DS->DISC );
	Free_TIMESET( &DS->DAMREC );
	Free_TIMESET( &DS->DIV );
}
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//   ファイル変更処理
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CSETFILE::OnClickedButtonFile0() {Get_Set_File_Name(0);}
void CSETFILE::OnClickedButtonFile1() {Get_Set_File_Name(1);}
void CSETFILE::OnClickedButtonFile2() {Get_Set_File_Name(2);}
void CSETFILE::OnClickedButtonFile3() {Get_Set_File_Name(3);}
void CSETFILE::OnClickedButtonFile4() {Get_Set_File_Name(4);}
void CSETFILE::OnClickedButtonFile5() {Get_Set_File_Name(5);}
void CSETFILE::OnClickedButtonFile6() {Get_Set_File_Name(6);}
void CSETFILE::OnClickedButtonFile7() {Get_Set_File_Name(7);}
void CSETFILE::OnClickedButtonFile8() {Get_Set_File_Name(8);}
void CSETFILE::OnClickedButtonFile9() {Get_Set_File_Name(9);}
void CSETFILE::OnClickedButtonFile10() {Get_Set_File_Name(10);}
void CSETFILE::OnClickedButtonFile11() {Get_Set_File_Name(11);}
void CSETFILE::OnClickedButtonFile12() {Get_Set_File_Name(12);}
void CSETFILE::OnClickedButtonFile13() {Get_Set_File_Name(13);}
void CSETFILE::OnClickedButtonFile14() {Get_Set_File_Name(14);}
void CSETFILE::OnClickedButtonFile15() {Get_Set_File_Name(15);}
void CSETFILE::OnClickedButtonFile16() {Get_Set_File_Name(16);}
void CSETFILE::OnClickedButtonFile17() {Get_Set_File_Name(17);}
void CSETFILE::OnClickedButtonFile18() {Get_Set_File_Name(18);}
void CSETFILE::OnClickedButtonFile19() {Get_Set_File_Name(19);}
void CSETFILE::OnClickedButtonFile20() {Get_Set_File_Name(20);}
void CSETFILE::OnClickedButtonOutfile0() {Get_Set_File_Name(0);}
void CSETFILE::OnClickedButtonOutfile1() {Get_Set_File_Name(1);}
void CSETFILE::OnClickedButtonOutfile2() {Get_Set_File_Name(2);}
void CSETFILE::OnClickedButtonOutfile3() {Get_Set_File_Name(3);}
void CSETFILE::OnClickedButtonOutfile4() {Get_Set_File_Name(4);}
void CSETFILE::OnClickedButtonOutfile5() {Get_Set_File_Name(5);}
void CSETFILE::OnClickedButtonOutfile6() {Get_Set_File_Name(6);}
void CSETFILE::OnClickedButtonOutfile7() {Get_Set_File_Name(7);}

void CSETFILE::OnDblclkFilelabel1() {Switch_File( 0 );}
void CSETFILE::OnDblclkFilelabel2() {Switch_File( 1 );}
void CSETFILE::OnDblclkFilelabel3() {Switch_File( 2 );}
void CSETFILE::OnDblclkFilelabel4() {Switch_File( 3 );}
void CSETFILE::OnDblclkFilelabel5() {Switch_File( 4 );}
void CSETFILE::OnDblclkFilelabel6() {Switch_File( 5 );}
void CSETFILE::OnDblclkFilelabel7() {Switch_File( 6 );}
void CSETFILE::OnDblclkFilelabel8() {Switch_File( 7 );}
void CSETFILE::OnDblclkFilelabel9() {Switch_File( 8 );}
void CSETFILE::OnDblclkFilelabel10() {Switch_File( 9 );}
void CSETFILE::OnDblclkFilelabel11() {Switch_File( 10 );}
void CSETFILE::OnDblclkFilelabel12() {Switch_File( 11 );}
void CSETFILE::OnDblclkFilelabel13() {Switch_File( 12 );}
void CSETFILE::OnDblclkFilelabel14() {Switch_File( 13 );}
void CSETFILE::OnDblclkFilelabel15() {Switch_File( 14 );}
void CSETFILE::OnDblclkFilelabel16() {Switch_File( 15 );}
void CSETFILE::OnDblclkFilelabel17() {Switch_File( 16 );}
void CSETFILE::OnDblclkFilelabel18() {Switch_File( 17 );}
void CSETFILE::OnDblclkFilelabel19() {Switch_File( 18 );}
void CSETFILE::OnDblclkFilelabel20() {Switch_File( 19 );}
void CSETFILE::OnDblclkFilelabel21() {Switch_File( 20 );}

void CSETFILE::OnDblclkOutlabel0() {Switch_File( 0 );}
void CSETFILE::OnDblclkOutlabel1() {Switch_File( 1 );}
void CSETFILE::OnDblclkOutlabel2() {Switch_File( 2 );}
void CSETFILE::OnDblclkOutlabel3() {Switch_File( 3 );}
void CSETFILE::OnDblclkOutlabel4() {Switch_File( 4 );}
void CSETFILE::OnDblclkOutlabel5() {Switch_File( 5 );}
void CSETFILE::OnDblclkOutlabel6() {Switch_File( 6 );}
void CSETFILE::OnDblclkOutlabel7() {Switch_File( 7 );}

void CSETFILE::OnBnClickedButtonGisfile0(){Get_D2GIS_File_Name( 0 );}
void CSETFILE::OnBnClickedButtonGisfile1(){Get_D2GIS_File_Name( 1 );}
void CSETFILE::OnBnClickedButtonGisfile2(){Get_D2GIS_File_Name( 2 );}
void CSETFILE::OnBnClickedButtonGisfile3(){Get_D2GIS_File_Name( 3 );}
void CSETFILE::OnBnClickedButtonGisfile4(){Get_D2GIS_File_Name( 4 );}
void CSETFILE::OnBnClickedButtonGisfile5(){Get_D2GIS_File_Name( 5 );}

void CSETFILE::OnStnDblclickGislabel0()  {Switch_File( 100 );}
void CSETFILE::OnStnDblclickGislabel1()  {Switch_File( 101 );}
void CSETFILE::OnStnDblclickGislabel2()  {Switch_File( 102 );}
void CSETFILE::OnStnDblclickGislabel3()  {Switch_File( 103 );}
void CSETFILE::OnStnDblclickGislabel4()  {Switch_File( 104 );}
void CSETFILE::OnStnDblclickGislabel5()  {Switch_File( 105 );}


HRESULT CSETFILE::Read_D2gis_File(int Fid,char* fname,MINFO* data)
{
	if( ! DSET.set )  return E_FAIL;
	//
	//----------------------------------------------- Read
	//FILE*		fp;
	//char		buf[SIZE_16K],inchar[64];
	//int			lcnt=0,FV,FH,pos;
	//int			id;
	//CString		str,str1,str2;

	//if((fp=fopen(fname,"r")) == NULL ) {
	//	pos = errno;
	//	return E_FAIL;
	//}
	////  ヘッダー部
	//for(int i=0;i<9;i++) {			//
	//	fgets( buf,SIZE_16K,fp);
	//	if( i == 2 ) {
	//		pos = 0; 
	//		getstr(buf,&pos,inchar,SIZE_16K);getstr(buf,&pos,inchar,SIZE_16K); FH = atoi(inchar);
	//		getstr(buf,&pos,inchar,SIZE_16K);getstr(buf,&pos,inchar,SIZE_16K); FV = atoi(inchar);

	//		if( Param.Hnum != FH || Param.Vnum != FV ) {
	//			str1.Format("Matrix Size of This Simulation Output  %d - %d\n",FH,FV);
	//			str2.Format("Model Matrix Size                      %d - %d\n",Param.Hnum,Param.Vnum);
	//			str = "** Matrix Size Error \n" + str1 + str2;
	//			MessageBox(str,"Error",MB_OK|MB_ICONEXCLAMATION);
	//			fclose( fp ); return E_FAIL;
	//		}
	//	}
	//}
	////  行数カウント
	//while( fgets(buf,SIZE_16K,fp) != NULL ) lcnt++;
	//Param.GISnum[Fid] = lcnt/(FV+1);
	//Param.GISmem[Fid] = lcnt/(FV+1) + 10;	// シミュレーションケース数　計算結果メモリー量、行数＋日付 １０：余裕
	////
	//if( Param.ct[Fid] == NULL ) {
	//	if( (Param.ct[Fid] = (CTime*)malloc( Param.GISmem[Fid]*sizeof( CTime ))) == NULL ) {
	//		fclose( fp );return E_FAIL;}
	//}
	////----------------------------------------------- MINFO Memory Alloc
	//for(int i=0;i<Param.Hnum*Param.Vnum;i++) {
	//	if( data[i].flag ) {
	//		if( (data[i].Hval[Fid] = (double*)malloc( Param.GISmem[Fid]*sizeof( double ))) == NULL ) {
	//			while( i >= 0 ) SAFE_FREE( data[i--].Hval[Fid] );
	//			fclose( fp );return E_FAIL;}
	//	}
	//}
	////
	////----------------------------------------------- Rewind
	//rewind( fp );
	//for(int i=0;i<9;i++) fgets( buf,SIZE_16K,fp);		// 読み飛ばし
	////
	//if( Fid == 4 ) 	Param.Arrow_Pair.x = Param.Arrow_Pair.y = DUNDEF;	// Velocity max U,V
	////
	//double		Pair = 0.;
	//double		Vmax;
	//int			Overcnt;
	////
	//Vmax = DUNDEF;
	//for(int i=0;i<Param.GISnum[Fid];i++) {
	//	fgets( buf,SIZE_16K,fp);						// Date
	//	Param.ct[Fid][i] = StrDate_Time( buf );
	//	// 
	//	if( Param.GISfirst && i == 0  ) {
	//		Param.ctmin = Param.ct[Fid][i];
	//		Param.GISfirst = FALSE;
	//	}
	//	else if( i == 0 ) {
	//		if( Param.ctmin > Param.ct[Fid][i] ) Param.ctmin = Param.ct[Fid][i];
	//	}
	//	else if( i == Param.GISnum[Fid]-1 ) {
	//		if( Param.ctmax < Param.ct[Fid][i] ) Param.ctmax = Param.ct[Fid][i];
	//	}

	//	//
	//	Overcnt  =0;
	//	for(int v=0;v<FV;v++) {
	//		fgets( buf,SIZE_16K,fp);						// Date
	//		pos = 0;getstr(buf,&pos,inchar,64);		// ,浸水深 部
	//		getstr(buf,&pos,inchar,64);

	//		for(int h=0;h<FH;h++) {
	//			getstr(buf,&pos,inchar,SIZE_16K);
	//			id = v*FH + h;
	//			if( data[id].flag ) {
	//				data[id].Hval[Fid][i] = atof( inchar );
	//				if( ( Fid == 3 || Fid == 4 ) && data[id].Hval[Fid][i] > 10. ) Overcnt++;
	//				//
	//				if( Vmax < data[id].Hval[Fid][i] ) Vmax = data[id].Hval[Fid][i];
	//				// max U V
	//				if( Fid == 4 ) {	// V があることは U（FID＝３）もあるとの前提
	//					if( Pair < ( abs(data[id].Hval[Fid][i]) + abs( data[id].Hval[3][i] ) ) ) {
	//						Pair = abs(data[id].Hval[Fid][i]) + abs( data[id].Hval[3][i] );
	//						Param.Arrow_Pair.x = data[id].Hval[3][i];
	//						Param.Arrow_Pair.y = data[id].Hval[4][i];
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//fclose( fp );
	return S_OK;
}


void CSETFILE::OnStnClickedSave0()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CSETFILE::OnStnClickedSaveas0()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


