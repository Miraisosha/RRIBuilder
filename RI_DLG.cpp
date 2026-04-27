// RI_DLG.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "RI_DLG.h"
#include "afxdialogex.h"

#include "RRI_Common.h"
#include "Tab_Param.h"
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//
extern			char			m_RecentPath[];
extern			DATASET		DSET;
extern			MINFO**		MESH;
extern			int			File_Format[];
extern			PARAMS		PM;
extern			int			File_Order[];


DATASET			DS;			// 編集用のデータセット
int				CLAND;


// 上下流ファイルセット
//_______________________________________________________________________________________________
/////////////////////////////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNAMIC(CRI_DLG, CDialogEx)

CRI_DLG::CRI_DLG(CRRI_GUIView* pParent /*=NULL*/)
	: CDialogEx(CRI_DLG::IDD, pParent), m_pParent(pParent)
	//, b_exchange(FALSE)
{
	CTAB = UNDEF;
}

CRI_DLG::~CRI_DLG()
{
}

void CRI_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Check(pDX, IDC_CHECK_CHANGE, b_exchange);
}


BEGIN_MESSAGE_MAP(CRI_DLG, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FILES, &CRI_DLG::OnTcnSelchangeTabFiles)
	ON_BN_CLICKED(ID_SAVE_RRI, &CRI_DLG::OnBnClickedSaveRri)
	ON_BN_CLICKED(ID_SAVE_AS_RRI, &CRI_DLG::OnBnClickedSaveAsRri)
	//ON_BN_CLICKED(IDC_CHECK_CHANGE, &CRI_DLG::OnBnClickedCheckChange)
	ON_BN_CLICKED(IDCANCEL, &CRI_DLG::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRI_DLG メッセージ ハンドラー


BOOL CRI_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//----------------------------------------------------------------------データセットのコピー
	Copy_DSET(&DS, DSET);
	//----------------------------------------------------------------------
	CTAB = 0;
	COLD = 0;
	CLAND = 0;		// 土地利用番号
	Init_Tab();

	Change_Nums = 0;
	//----------------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
void CRI_DLG::Init_Tab()
{
	//
	int        err = 0;
	CSize		Cs, Cret;
	CRect		Trect, rect; 
	//
	CTabCtrl*	 CTab = (CTabCtrl*)GetDlgItem(IDC_TAB_FILES);
	CTab->GetWindowRect(&Trect);
	//b_exchange = FALSE;
	//
	// 子ダイアログ作成
	if (!err) if (!Dlg_Param.Create(CTab_Param::IDD, this)) err = 1;
	if (!err) if (!Dlg_InFile.Create(CTab_InFile::IDD, this)) err = 1;
	if (!err) if (!Dlg_OutFile.Create(CTab_OutFile::IDD, this)) err = 1;
	// 子ダイアログ移動
	if (!err)
	{
		Dlg_Param.GetClientRect(&rect);
		rect.OffsetRect(15, 36);
		Dlg_Param.MoveWindow(&rect, FALSE);
		Dlg_InFile.MoveWindow(&rect, FALSE);
		Dlg_OutFile.MoveWindow(&rect, FALSE);
	}
	if (err) exit(-1);
	//
	Dlg_InFile.IMnum = 0;			// インポート名の数
	//
	TAB.mask = TCIF_PARAM;
	Cs.cx = 182;	Cs.cy = 24;
	Cret = CTab->SetItemSize(Cs);
	//
	TAB.mask = TCIF_TEXT;
	TAB.pszText = "Parameter";
	CTab->InsertItem(0, &TAB);
	TAB.pszText = "Input";
	CTab->InsertItem(1, &TAB);
	TAB.pszText = "Output";
	CTab->InsertItem(2, &TAB);
	//
	CTab->ShowWindow(SW_SHOW);
	CTab->HighlightItem(0, TRUE);
	//
	CTAB = 0;
//	
	Dlg_Param.ShowWindow(SW_SHOW);
	Dlg_InFile.ShowWindow(SW_HIDE);
	Dlg_OutFile.ShowWindow(SW_HIDE);
	//
}


void CRI_DLG::OnTcnSelchangeTabFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl*	 CTab = (CTabCtrl*)GetDlgItem(IDC_TAB_FILES);
	COLD = CTAB;
	if (COLD == 0) Dlg_Param.Get_Data();
	//
	CTAB = CTab->GetCurSel();
	CTab->HighlightItem(COLD, FALSE);
	CTab->HighlightItem(CTAB, TRUE);
	//

	Dlg_Param.ShowWindow(CTAB == 0 ? SW_SHOW : SW_HIDE);
	//
	if (CTAB == 1) Dlg_InFile.Disp_Data();
	Dlg_InFile.ShowWindow(CTAB == 1 ? SW_SHOW : SW_HIDE);
	//
	Dlg_OutFile.ShowWindow(CTAB == 2 ? SW_SHOW : SW_HIDE);
	//
	*pResult = 0;
}


//
///////////////////////////////////////////////////////////////////////////////////
// 
//  I/O
//
///////////////////////////////////////////////////////////////////////////////////
//


void CRI_DLG::OnBnClickedSaveRri()
{
	Dlg_Param.Get_Data();
	//
	if (Dlg_OutFile.Change_Nums < 0) Dlg_OutFile.Change_Nums = 0;
	if (Dlg_InFile.Change_Nums < 0)Dlg_InFile.Change_Nums = 0;

	Change_Nums = Dlg_Param.Change_Nums + Dlg_InFile.Change_Nums + Dlg_OutFile.Change_Nums;
	//
	if (Change_Nums) {
		Delete_DSET(&DSET);
		Copy_DSET(&DSET, DS);
		Delete_DSET(&DS);
		//
		Set_Relative_Name(&DSET);
		Write_RRI_INPUT(DSET);
#if APP_VERSION == FULL_VER
		m_pParent->SaveSedInputFile();
#endif
		//		インポート
		int no;
		if (Dlg_InFile.IMnum != 0) {
			for (int i = 0; i < Dlg_InFile.IMnum; i++) {
				no = Dlg_InFile.IMkind[i];
				if (Read_Data_File(no, Dlg_InFile.IMname[i], &DSET, MESH)) {
					MessageBox("** Error ** Failure in reading import file", "Error", MB_OK | MB_ICONASTERISK);
					return;
				}
				//
				DSET.in_avail[no] = DSET.in_use[no] = TRUE;
				if (Write_Data_File(no, File_Format[no], File_Order[no], DSET, PM, MESH)) {
					MessageBox("** Error ** Failure in writing imported data", "Error", MB_OK | MB_ICONASTERISK);
					return;
				}
				Change_Nums++;
			}
		}
	}
	else  Delete_DSET(&DS);
	//
	//
	if (Dlg_InFile.INVnum != 0) {			// 無効化の処理
		int		no,flagID = UNDEF;
		for (int f = 0; f < Dlg_InFile.INVnum; f++) {
			no = Dlg_InFile.INV[f];

			switch (no) {
			case HS_WLEV_FILE: Free_TIMESET(&DSET.HSWLEV);
				DSET.in_avail[HS_WLEV_FILE] = DSET.in_use[HS_WLEV_FILE] = FALSE; flagID = ID_MESH_HS; break;

			case HR_WLEV_FILE: Free_TIMESET(&DSET.HRWLEV);
				DSET.in_avail[HR_WLEV_FILE] = DSET.in_use[HR_WLEV_FILE] = FALSE; flagID = ID_MESH_HR; break;

			case QS_WLEV_FILE:  Free_TIMESET(&DSET.QSWLEV);
				DSET.in_avail[QS_WLEV_FILE] = DSET.in_use[QS_WLEV_FILE] = FALSE; flagID = ID_MESH_QS; break;

			case QR_WLEV_FILE: Free_TIMESET(&DSET.QRWLEV);
				DSET.in_avail[QR_WLEV_FILE] = DSET.in_use[QR_WLEV_FILE] = FALSE; flagID = ID_MESH_QR; break;

			case DAM_CNT_FILE: SAFE_FREE(DSET.DAMC); DSET.Damc_Mem = DSET.Damc_Num = 0; SAFE_FREE(DSET.DAMC);
				DSET.in_avail[DAM_CNT_FILE] = DSET.in_use[DAM_CNT_FILE] = FALSE; flagID = ID_MESH_DAM; break;

			case DIV_FILE: SAFE_FREE(DSET.DIVID); DSET.Div_Num = DSET.Div_Mem = 0; SAFE_FREE(DSET.DIVID);
				DSET.in_avail[DIV_FILE] = DSET.in_use[DIV_FILE] = FALSE; flagID = ID_MESH_DIV; break;

			case LOCATION_FILE: SAFE_FREE(DSET.LCpos); DSET.Lnum = DSET.Lmem = 0; SAFE_FREE(DSET.LCpos);
				DSET.in_avail[LOCATION_FILE] = DSET.in_use[LOCATION_FILE] = FALSE; flagID = ID_MESH_LOC; break;

			}
			///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
			//  flagID で設定されたメッシュをもとに戻す。

			for (int v = 0; v < PM.MVnum; v++) {
				for (int h = 0; h < PM.MHnum; h++) {
					if (MESH[v][h].flag == 0) continue;
					if (flagID != ID_MESH_LOC) {
						if (MESH[v][h].flag == flagID || MESH[v][h].flag == flagID + ID_MESH_LOC){
							if (MESH[v][h].flag < ID_MESH_LOC) {
								if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[v][h].flag = ID_MESH_R;
								else                               MESH[v][h].flag = ID_MESH;
							}
							else {
								if (MESH[v][h].Acc >= DSET.Riv_Thresh && DSET.Riv_Avail) MESH[v][h].flag = ID_MESH_R + ID_MESH_LOC;
								else                               MESH[v][h].flag = ID_MESH + ID_MESH_LOC;
							}
						}
					}
					else MESH[v][h].flag = MESH[v][h].flag%ID_MESH_LOC;
				}
			}
		}
	}
	//
	//
	CDialogEx::OnOK();
}


void CRI_DLG::OnBnClickedSaveAsRri()
{
	CString		fname;
	if (!Button_File(FALSE, &fname, m_RecentPath, "RRI_Input", "txt")) return;
	//
	Write_RRI_INPUT(DS);
#if APP_VERSION == FULL_VER
	m_pParent->SaveSedInputFile();
#endif
	//
	//
	CDialogEx::OnOK();
}


void CRI_DLG::OnBnClickedCancel()
{
	Delete_DSET(&DS);
	CDialogEx::OnCancel();
}
