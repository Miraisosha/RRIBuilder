// Make_Dynamic.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "Make_Dynamic.h"
#include "afxdialogex.h"
#include "RRI_Common.h"
#include "TSEDITDLG.h"

extern      DATASET		DSET;							// ファイルセット
extern      char			m_RecentPath[];
//---------------------------------------------------------------------------------------
int		ItemDNum = 5;
int		DataDNo[5] = { HS_WLEV_FILE, HR_WLEV_FILE, QS_WLEV_FILE, QR_WLEV_FILE, DIV_FILE};
int		ContDID[5][3] = { { IDC_BUTTON_DFILE_1, IDC_RADIO_D11, IDC_RADIO_D12},
						{ IDC_BUTTON_DFILE_2, IDC_RADIO_D21, IDC_RADIO_D22 },
						{ IDC_BUTTON_DFILE_3, IDC_RADIO_D31, IDC_RADIO_D32 },
						{ IDC_BUTTON_DFILE_4, IDC_RADIO_D41, IDC_RADIO_D42 },
						{ IDC_BUTTON_DFILE_5, IDC_RADIO_D51, IDC_RADIO_D52 }	};
int		RadioDID[5][2] = { { IDC_RADIO_D11, IDC_RADIO_D12 },
						{ IDC_RADIO_D21, IDC_RADIO_D22 },
						{ IDC_RADIO_D31, IDC_RADIO_D32 },
						{ IDC_RADIO_D41, IDC_RADIO_D42 },
						{ IDC_RADIO_D51, IDC_RADIO_D52 }};

// CMake_Dynamic ダイアログ

IMPLEMENT_DYNAMIC(CMake_Dynamic, CDialogEx)

CMake_Dynamic::CMake_Dynamic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMake_Dynamic::IDD, pParent)
{

}

CMake_Dynamic::~CMake_Dynamic()
{
}

void CMake_Dynamic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMake_Dynamic, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DFILE_1, &CMake_Dynamic::OnBnClickedButtonDfile1)
	ON_BN_CLICKED(IDC_BUTTON_DFILE_2, &CMake_Dynamic::OnBnClickedButtonDfile2)
	ON_BN_CLICKED(IDC_BUTTON_DFILE_3, &CMake_Dynamic::OnBnClickedButtonDfile3)
	ON_BN_CLICKED(IDC_BUTTON_DFILE_4, &CMake_Dynamic::OnBnClickedButtonDfile4)
	ON_BN_CLICKED(IDC_BUTTON_DFILE_5, &CMake_Dynamic::OnBnClickedButtonDfile5)
	ON_BN_CLICKED(IDC_RADIO_D22, &CMake_Dynamic::OnBnClickedRadioD22)
END_MESSAGE_MAP()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// 初期化処理
BOOL CMake_Dynamic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

// CMake_Dynamic メッセージ ハンドラー
void CMake_Dynamic::Get_File_Name(int No)
{
	CString  fname = DSET.File_names[DataDNo[No]];
	char		Rname[SIZE_1K];
	//
	if (!Button_File(FALSE, &fname, m_RecentPath, "Boundary Data File", "*")) return;
	strcpy(DSET.File_names[DataDNo[No]], fname);
	Get_Relative_Path(DSET.File_names[DataDNo[No]], DSET.Proj_Folder, Rname);
	//
	CWnd*	cw = GetDlgItem(ContDID[No][0]);
	cw->SetWindowTextA(Rname);
	DSET.in_use[DataDNo[No]] = TRUE;		// 作ってから in_Avail を ON
}
void CMake_Dynamic::OnBnClickedButtonDfile1(){ Get_File_Name(0); }
void CMake_Dynamic::OnBnClickedButtonDfile2(){ Get_File_Name(1); }
void CMake_Dynamic::OnBnClickedButtonDfile3(){ Get_File_Name(2); }
void CMake_Dynamic::OnBnClickedButtonDfile4(){ Get_File_Name(3); }
void CMake_Dynamic::OnBnClickedButtonDfile5(){ Get_File_Name(4); }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// ダイアログ表示
void CMake_Dynamic::Display_State()
{
	CButton	*Bradio1, *Bradio2, *Bfile;
	CString	str;
	//
	for (int i = 0; i < ItemDNum; i++) {
		Bfile = (CButton*)GetDlgItem(ContDID[i][0]);
		Bradio1 = (CButton*)GetDlgItem(ContDID[i][1]);
		Bradio2 = (CButton*)GetDlgItem(ContDID[i][2]);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// データの由来 ラジオボタン   逆　ＩＭＰＯＲＴが０（ON)　Manual作成は１
		if (DSET.Data_From[DataDNo[i]] == UNDEF) {
			Bradio1->SetCheck(0); Bradio2->SetCheck(0);
		}
		else if (DSET.Data_From[DataDNo[i]] == 0) {	// import
			Bradio1->SetCheck(1); Bradio2->SetCheck(0);
		}
		else if (DSET.Data_From[DataDNo[i]] == 1) {	// manual
			Bradio1->SetCheck(0); Bradio2->SetCheck(1);
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 無効・有効  in_avail で判断　
		if (DSET.in_avail[DataDNo[i]]) { // 作成する必要はない
			Bfile->SetWindowTextA(DSET.File_names[DataDNo[i]]);
			Bfile->EnableWindow(FALSE);
			Bradio1->EnableWindow(FALSE);
			Bradio2->EnableWindow(FALSE);
		}
		else {
			Bfile->EnableWindow(TRUE);
			Bradio1->EnableWindow(TRUE);
			Bradio2->EnableWindow(TRUE);
		}
	}
}
//------------------------------------------------------------------------
//  EDIT DIALOG TIME SERIES
//------------------------------------------------------------------------
void	CMake_Dynamic::Edit_TimeSet(int FN)
{
	CTSEditDlg	TSD;
	//
	TSD.Data_ID = FN;
	TSD.BT = DSET.BT;
	if (TSD.DoModal() == IDCANCEL) return;
}



void CMake_Dynamic::OnBnClickedRadioD22()
{
	Edit_TimeSet(HR_WLEV_FILE);
}
