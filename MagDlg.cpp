// MagDlg.cpp : é¿ëïÉtÉ@ÉCÉã
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "MagDlg.h"
#include "afxdialogex.h"
#include "RRI_Common.h"

extern   char				m_RecentPath[];
extern   char				m_BootPath[];
extern   PARAMS			PM;							// äÓñ{èÓïÒ
extern   DATASET			DSET;						// ÉtÉ@ÉCÉãÉZÉbÉg

// CMagDlg É_ÉCÉAÉçÉO

IMPLEMENT_DYNAMIC(CMagDlg, CDialogEx)

CMagDlg::CMagDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMagDlg::IDD, pParent)
	, s_Mag(_T(""))
	, s_COMorg(_T(""))
	, s_OrgACC(_T(""))
	, s_OrgADIR(_T(""))
	, s_OrgADEM(_T(""))
	, m_Memo(_T(""))
{

}

CMagDlg::~CMagDlg()
{
}

void CMagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MAG, s_Mag);
	DDX_Control(pDX, IDC_BUTTON_ACC, b_ACC);
	DDX_Control(pDX, IDC_BUTTON_ADEM, b_ADEM);
	DDX_Control(pDX, IDC_BUTTON_ADIR, b_ADIR);
	DDX_Text(pDX, IDC_COM_ORG, s_COMorg);
	DDX_Text(pDX, IDC_ACC_FILE, s_OrgACC);
	DDX_Text(pDX, IDC_ADIR_FILE, s_OrgADIR);
	DDX_Text(pDX, IDC_DEM_FILE, s_OrgADEM);
	DDX_Text(pDX, IDC_MEMO, m_Memo);
	DDX_Control(pDX, IDC_STATIC_LABEL, c_Label);
	DDX_Control(pDX, IDC_EDIT_MAG, c_Mag);
}


BEGIN_MESSAGE_MAP(CMagDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADEM, &CMagDlg::OnBnClickedButtonAdem)
	ON_BN_CLICKED(IDC_BUTTON_ACC, &CMagDlg::OnBnClickedButtonAcc)
	ON_BN_CLICKED(IDC_BUTTON_ADIR, &CMagDlg::OnBnClickedButtonAdir)
	ON_EN_CHANGE(IDC_EDIT_MAG, &CMagDlg::OnEnChangeEditMag)
	ON_BN_CLICKED(IDOK, &CMagDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CMagDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMagDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()

///  èâä˙âªÅ@Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|

BOOL CMagDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString		Add, Head, tail;
	char			Dir[SIZE_1K], Title[SIZE_1K];
	char			SN_org[SIZE_1K];	// SN : Show Name
	//
	s_OrgADEM = s_OrgADIR = s_OrgACC = _T("");
	// ----------------------------------------------------------------
	if (kind == 0) {		// Normal Magnifier
		c_Label.ShowWindow(SW_SHOW);
		c_Mag.ShowWindow(SW_SHOW);
		//
		SaveID = 0;	// OverWrite  ScaleUp
		CButton*		cb = (CButton*)GetDlgItem(IDC_RADIO1);
		cb->SetCheck(1);
		b_ADEM.EnableWindow(FALSE);
		b_ACC.EnableWindow(FALSE);
		b_ADIR.EnableWindow(FALSE);
	}
	else {	// DemAdjust
		c_Label.ShowWindow(SW_HIDE);
		c_Mag.ShowWindow(SW_HIDE);
		//
		SaveID = 1;	// Save As
		CWnd*		cw = GetDlgItem(IDC_STATIC_ACC);
		cw->EnableWindow(FALSE);
		//
		CButton*		cb = (CButton*)GetDlgItem(IDC_RADIO1);
		cb->SetCheck(0);
		cb = (CButton*)GetDlgItem(IDC_RADIO2);
		cb->SetCheck(1);
		b_ADEM.EnableWindow(TRUE);
		b_ACC.EnableWindow(FALSE);
		b_ADIR.EnableWindow(TRUE);
	}
	//
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	s_COMorg.Format("Original files   cells [ %d, %d]", PM.MHnum, PM.MVnum);
	//
	s_OrgADEM.Format("%s", DSET.File_names[ADEM_FILE]);
	if (kind == 0) s_OrgACC.Format("%s", DSET.File_names[ACC_FILE]);
	s_OrgADIR.Format("%s", DSET.File_names[ADIR_FILE]);
	if (kind == 1) s_OrgACC.Format("%s", DSET.File_names[ACC_FILE]);

	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	if (kind == 1) {
		//Get_Dir(DSET.File_names[ADEM_FILE], Dir); Get_Dirä÷êîïsãÔçáÅFopw
		sprintf(Dir, "%s/topo/adem.txt", DSET.Proj_Folder);
		Get_Title(DSET.File_names[ADEM_FILE], Title);
		DemF.Format("%s/a%s", Dir, Title);
		DemF = Dir;
		DemF.Replace("/", "\\");

		Get_Relative_Path(DemF, DSET.Proj_Folder, SN_org);
		b_ADEM.SetWindowTextA(SN_org);
		//
		//Get_Dir(DSET.File_names[ADIR_FILE], Dir); Get_Dirä÷êîïsãÔçáÅFopw
		sprintf(Dir, "%s/topo/adir.txt", DSET.Proj_Folder);
		Get_Title(DSET.File_names[ADIR_FILE], Title);
		AdirF.Format("%s/a%s", Dir, Title);
		AdirF = Dir;
		AdirF.Replace("/", "\\");

		Get_Relative_Path(AdirF, DSET.Proj_Folder, SN_org);
		b_ADIR.SetWindowTextA(SN_org);
	}
	if (SaveID == 0) {			// ÉfÉtÉHÉãÉgÇÃè„èëÇ´ï€ë∂ÇÃèÍçá
		//
		Add = "_Temp";
		CString		longN;
		//
		longN = DSET.File_names[ADEM_FILE];
		Head = longN.Left(longN.GetLength() - 4);
		tail = longN.Right(4);
		DemF = Head + Add + tail;
		b_ADEM.SetWindowTextA("File Name");
		//
		if (kind == 0) {
			longN = DSET.File_names[ACC_FILE];
			Head = longN.Left(longN.GetLength() - 4);
			tail = longN.Right(4);
			AccF = Head + Add + tail;

			b_ACC.SetWindowTextA("File Name");
		}
		//
		longN = DSET.File_names[ADIR_FILE];
		Head = longN.Left(longN.GetLength() - 4);
		tail = longN.Right(4);
		AdirF = Head + Add + tail;
		b_ADIR.SetWindowTextA("File Name");
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//

	UDF;
	// ----------------------------------------------------------------
	//
//	if (!PM.B_UseJFlow) { 2019.7.8 DLLïsãÔçáëŒâû owashi
//		Get_Dir(DSET.File_names[ADEM_FILE], m_RecentPath);
//	}
	::SetCurrentDirectory(m_RecentPath);
	//
	return TRUE;
}

///  ÉtÉ@ÉCÉãéwíËÅ@Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|

void CMagDlg::OnBnClickedButtonAdem()
{
	::SetCurrentDirectory(m_RecentPath);
	if (!Button_File(FALSE, &DemF, m_RecentPath, "DEM File", "txt")) return;
	//
	char		SN_org[SIZE_1K];	// SN : Show Name
	Get_Relative_Path(DemF, DSET.Proj_Folder, SN_org);
	b_ADEM.SetWindowTextA(SN_org);
}

void CMagDlg::OnBnClickedButtonAcc()
{
	if (kind > 0) return;
	::SetCurrentDirectory(m_RecentPath);
	if (!Button_File(FALSE, &AccF, m_RecentPath, "ACC File", "txt")) return;
	//
	char		SN_org[SIZE_1K];	// SN : Show Name
	Get_Relative_Path(AccF, DSET.Proj_Folder, SN_org);
	b_ACC.SetWindowTextA(SN_org);
}

void CMagDlg::OnBnClickedButtonAdir()
{
	::SetCurrentDirectory(m_RecentPath);
	if (!Button_File(FALSE, &AdirF, m_RecentPath, "DIR File", "txt")) return;
	//
	char		SN_org[SIZE_1K];	// SN : Show Name
	Get_Relative_Path(AdirF, DSET.Proj_Folder, SN_org);
	b_ADIR.SetWindowTextA(SN_org);
}

///  ÉtÉ@ÉCÉãéwíËÅ@Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|

void CMagDlg::OnEnChangeEditMag() 
{ 
	UDT; 
	if (SaveID == 0) return;
	//
	CString		Lname,Add, Head, tail;
	char			SN_org[SIZE_1K];	// SN : Show Name
	//
	if (s_Mag.IsEmpty()) Add = "_N";
	else               Add = s_Mag;
	//
	b_ADEM.EnableWindow(TRUE);
	b_ACC.EnableWindow(TRUE);
	b_ADIR.EnableWindow(TRUE);
	//
	Lname = DSET.File_names[ADEM_FILE];
	Head = Lname.Left(Lname.GetLength() - 4);
	tail = Lname.Right(4);
	DemF = Head + Add + tail;
	//
	Get_Relative_Path(DemF, DSET.Proj_Folder, SN_org);
	b_ADEM.SetWindowTextA(SN_org);
	//
	Lname = DSET.File_names[ACC_FILE];
	Head = Lname.Left(Lname.GetLength() - 4);
	tail = Lname.Right(4);
	AccF = Head + Add + tail;
	//
	Get_Relative_Path(AccF, DSET.Proj_Folder, SN_org);
	b_ACC.SetWindowTextA(SN_org);
	//
	Lname = DSET.File_names[ADIR_FILE];
	Head = Lname.Left(Lname.GetLength() - 4);
	tail = Lname.Right(4);
	AdirF = Head + Add + tail;
	//
	Get_Relative_Path(AdirF, DSET.Proj_Folder, SN_org);
	b_ADIR.SetWindowTextA(SN_org);
}


void CMagDlg::OnBnClickedOk()
{
	// ì¸óÕì‡óeÇÃämîF
	if (DemF.GetLength() == 0 ||  AdirF.GetLength() == 0) {
		m_Memo = "** Error ** Insufficient File Name"; UDF; return;
	}
	if (kind == 0) {
		if (AccF.GetLength() == 0) {
			m_Memo = "** Error ** Insufficient File Name"; UDF; return;
		}
	}
	///=============================================================================
	//    Magnification
	int ret = 0;
	// -------------------------------- ScaleUP
	if (kind == 0) {		
		if (s_Mag.GetLength() == 0) {
			m_Memo = "** Error ** specify Magnification"; UDF; return;
		}
		Mag = atof(s_Mag);
		if (Mag > 10.) {
			MessageBox("**Error** Scale factor must be less than 10", "Void", MB_OK | MB_ICONHAND);
			return;
		}
		//
		CString		Dname, Dat;

#ifdef   VER_64
		Dat = PROG_MAGNIFY_DAT;
#else
		Dat = PROG_MAGNIFY_DAT_32;
#endif
		
		Dname.Format("%s\\%s", m_BootPath, Dat);
		FILE*		fp = fopen(Dname, "w");
		//
		fprintf(fp, "%s\n", DSET.File_names[ADEM_FILE]);
		fprintf(fp, "%s\n", DSET.File_names[ADIR_FILE]);
		fprintf(fp, "%s\n", DSET.File_names[ACC_FILE]);
		Mag = atof(s_Mag);
		fprintf(fp, "%d\n", (int)Mag);
		fprintf(fp, "%s\n", DemF);
		fprintf(fp, "%s\n", AdirF);
		fprintf(fp, "%s\n", AccF);
		//
		fclose(fp);
		// --------------------------------EXCUTE
		CString		Dir;
		Get_Dir(Dname, &Dir);
		::SetCurrentDirectory(Dir);
		ret = system("scaleUP.exe");
	}
	// -------------------------------- DemAdjust
	else if (kind == 1) {
		CString		Dname, Dat;
#ifdef   VER_64
		Dat = PROG_DEMADJUST_DAT;
#else
		Dat = PROG_DEMADJUST_DAT_32;
#endif
		Dname.Format("%s\\%s", m_BootPath, Dat);
		FILE*		fp = fopen(Dname, "w");
		//
		fprintf(fp, "%s\n", DSET.File_names[ADEM_FILE]);
		fprintf(fp, "%s\n", DSET.File_names[ADIR_FILE]);
		fprintf(fp, "%s\n", DSET.File_names[ACC_FILE]);
		fprintf(fp, "%s\n", DemF);
		fprintf(fp, "%s\n", AdirF);
		//
		fclose(fp);
		// --------------------------------EXCUTE
		CString		Dir;
		Get_Dir(Dname, &Dir);
		::SetCurrentDirectory(Dir);
		ret = system("DemAdjust2.exe");
	}
	_flushall();
	// --------------------------------FILEÅ@OVERWRITE
	if (SaveID == 0){	// OverWrite
		CopyFile(DemF, DSET.File_names[ADEM_FILE], FALSE);
		CopyFile(AdirF, DSET.File_names[ADIR_FILE], FALSE);
		if (kind == 0) CopyFile(AccF, DSET.File_names[ACC_FILE], FALSE);
		//
		DeleteFile(DemF);
		DeleteFile(AdirF);
		if (kind == 0) DeleteFile(AccF);
		//
		DemF  =DSET.File_names[ADEM_FILE];
		AdirF = DSET.File_names[ADIR_FILE];
		if (kind == 0) AccF = DSET.File_names[ACC_FILE];
	}
	// --------------------------------END
	//
	if (ret == 0)		CDialogEx::OnOK();
	else				CDialogEx::OnCancel();
}


void CMagDlg::OnBnClickedRadio1()
{
	UDT;
	SaveID = 0;
	b_ADEM.EnableWindow(FALSE);
	b_ACC.EnableWindow(FALSE);
	b_ADIR.EnableWindow(FALSE);

	CString		Add, Head, tail;
	//
	Add = "_Temp";
	//
	if (strcmp(DemF, DSET.File_names[ADEM_FILE]) == 0) {
		Head = s_OrgADEM.Left(s_OrgADEM.GetLength() - 4);
		tail = s_OrgADEM.Right(4);
		DemF = Head + Add + tail;
	}
	b_ADEM.SetWindowTextA("File Name");
	//
	if (kind == 0) {
		if (strcmp(AccF, DSET.File_names[ACC_FILE]) == 0) {
			Head = s_OrgACC.Left(s_OrgACC.GetLength() - 4);
			tail = s_OrgACC.Right(4);
			AccF = Head + Add + tail;
		}
		b_ACC.SetWindowTextA("File Name");
	}
	//
	if (strcmp(AdirF, DSET.File_names[ADIR_FILE]) == 0) {
		Head = s_OrgADIR.Left(s_OrgADIR.GetLength() - 4);
		tail = s_OrgADIR.Right(4);
		AdirF = Head + Add + tail;
	}
	b_ADIR.SetWindowTextA("File Name");
}


void CMagDlg::OnBnClickedRadio2()
{
	UDT;
	SaveID = 1;
	//
	CString		Add,Head, tail;
	char			SN_org[SIZE_1K];	// SN : Show Name
	//
	b_ADEM.EnableWindow(TRUE);
	if (kind == 0) b_ACC.EnableWindow(TRUE);	
	b_ADIR.EnableWindow(TRUE);
	//
	if (kind == 0 && !s_Mag.IsEmpty()) {
		Add = s_Mag;
		//
		Head = s_OrgADEM.Left(s_OrgADEM.GetLength() - 4);
		tail = s_OrgADEM.Right(4);
		DemF = Head + Add + tail;
		//
		////
		Head = s_OrgACC.Left(s_OrgACC.GetLength() - 4);
		tail = s_OrgACC.Right(4);
		AccF = Head + Add + tail;
		//
		Head = s_OrgADIR.Left(s_OrgADIR.GetLength() - 4);
		tail = s_OrgADIR.Right(4);
		AdirF = Head + Add + tail;
		//
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	Get_Relative_Path(DemF, DSET.Proj_Folder, SN_org);
	b_ADEM.SetWindowTextA(SN_org);
	//
	if (kind == 0) {
		b_ACC.EnableWindow(TRUE);
		Get_Relative_Path(AccF, DSET.Proj_Folder, SN_org);
		b_ACC.SetWindowTextA(SN_org);
	}
	//
	Get_Relative_Path(AdirF, DSET.Proj_Folder, SN_org);
	b_ADIR.SetWindowTextA(SN_org);
	//
}
