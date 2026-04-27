// RThiessen.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "RThiessen.h"
#include "afxdialogex.h"

//
#include		"CommFuncs.h"
#include		"RRI_Common.h"
//
extern char			m_RecentPath[SIZE_05K];
extern char			m_BootPath[SIZE_05K];

extern DATASET		DSET;
extern PARAMS			PM;							// 基本情報

// CRThiessen ダイアログ

IMPLEMENT_DYNAMIC(CRThiessen, CDialogEx)

CRThiessen::CRThiessen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRThiessen::IDD, pParent)
	, s_ncol(_T(""))
	, s_nlow(_T(""))
	, s_size(_T(""))
	, s_xll(_T(""))
	, s_yll(_T(""))
	, m_Comment(_T(""))
	, s_MapName(_T(""))
	, m_Rainfile(_T(""))
	, s_Cell(_T(""))
{

}

CRThiessen::~CRThiessen()
{
}

void CRThiessen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NCOL, s_ncol);
	DDX_Text(pDX, IDC_EDIT_NLOW, s_nlow);
	DDX_Text(pDX, IDC_EDIT_SIZE, s_size);
	DDX_Text(pDX, IDC_EDIT_XLL, s_xll);
	DDX_Text(pDX, IDC_EDIT_YLL, s_yll);
	DDX_Control(pDX, IDC_BUTTON1, c_Button_1);
	//DDX_Control(pDX, IDC_BUTTON2, c_Button_2);
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	DDX_Text(pDX, IDC_STATIC_MAP, s_MapName);
	DDX_Text(pDX, IDC_RAINFILE, m_Rainfile);
	DDX_Text(pDX, IDC_STAT_CELL, s_Cell);
}


BEGIN_MESSAGE_MAP(CRThiessen, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_XLL, &CRThiessen::OnEnChangeEditXll)
	ON_EN_CHANGE(IDC_EDIT_NCOL, &CRThiessen::OnEnChangeEditNcol)
	ON_EN_CHANGE(IDC_EDIT_SIZE, &CRThiessen::OnEnChangeEditSize)
	ON_EN_CHANGE(IDC_EDIT_YLL, &CRThiessen::OnEnChangeEditYll)
	ON_EN_CHANGE(IDC_EDIT_NLOW, &CRThiessen::OnEnChangeEditNlow)
	ON_BN_CLICKED(IDC_BUTTON1, &CRThiessen::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CRThiessen::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CRThiessen::OnBnClickedOk)
	ON_STN_CLICKED(IDC_RAINFILE, &CRThiessen::OnStnClickedRainfile)
END_MESSAGE_MAP()
//_______________________________________________________________________________________
/// /////////////////////////////////////////////////////////////////////////////////////
//   MESSAGE HANDLER
/// /////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BOOL CRThiessen::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	if (PM.B_LatLng) {
		lat = PM.stLAT;
		lng = PM.stLNG;
		unit = PM.Coord_Unit;
	}
	else {
		lat = PM.stUTM_Y;
		lng = PM.stUTM_X;
		unit = PM.Coord_Unit;
	}
	//
	Hnum = PM.MHnum;
	Vnum = PM.MVnum;
	//
	Rfile = RainF = RainMap = _T("");
	Set_Dlg();
	//
	return TRUE;  // return TRUE unless you set the focus to a control
}
void CRThiessen::Set_Dlg()
{
	CWnd*		cw;
	char			temp[SIZE_1K];
	//
	this->SetWindowTextA(Dtitle);
	//
	if (!Rfile.IsEmpty()){
		Get_Relative_Path(Rfile, DSET.Proj_Folder, temp);
		cw = GetDlgItem(IDC_BUTTON1);
		cw->SetWindowTextA(temp);
	}
	//
	s_xll.Format("%.2lf", lng);
	s_yll.Format("%.2lf", lat);
	s_ncol.Format("%d", Hnum);
	s_nlow.Format("%d", Vnum);
	if (PM.B_LatLng) {
		s_Cell = "Cellsize    1 /";
		s_size.Format("%.1lf", unit);
	}
	else {
		s_Cell = "Cellsize    ";
		s_size.Format("%.2lf", unit);
	}
	UDF;
	//
	return;
}
//_______________________________________________________________________________________
/// /////////////////////////////////////////////////////////////////////////////////////
//  CONTROL HANDLER
/// /////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CRThiessen::OnEnChangeEditXll() { UDT; lng = atof(s_xll); Set_Dlg(); }
void CRThiessen::OnEnChangeEditNcol() { UDT;Hnum = atoi(s_ncol); Set_Dlg(); }
void CRThiessen::OnEnChangeEditSize() { UDT; unit = atof(s_size); Set_Dlg(); }
void CRThiessen::OnEnChangeEditYll() { UDT; lat = atof(s_yll); Set_Dlg(); }
void CRThiessen::OnEnChangeEditNlow() { UDT; Vnum = atoi(s_nlow); Set_Dlg(); }


void CRThiessen::OnBnClickedButton1()
{
	if (!Button_File(TRUE, &Rfile, m_RecentPath, "Input org data", "csv")) return;
	//
	if (kind == 0) RainF = DSET.File_names[RAIN_FILE];
	else           RainF = DSET.File_names[POTENT_FILE];
	//
	CString	str;
	char	title[SIZE_01K];
	if (kind == 0)	str.Format("Output rain_file_name is %s... OK?", DSET.Input_names[RAIN_FILE]);
	else			str.Format("Output evaporation_file_name is %s... OK?", DSET.Input_names[POTENT_FILE]);

	if (MessageBox(str, "comfirm", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		str.Format("%s\\rain", DSET.Proj_Folder);
		::SetCurrentDirectory(str);
		if (kind == 0) {
			RainF = "Rain.dat";
			strcpy(title, "Rain data file");
		}
		else {
			RainF = "Evp.dat";
			strcpy(title, "Evaporation data file");
		}
		if (!Button_File(FALSE, &RainF, m_RecentPath, title, "dat")) return;
	}
	//
	CString		Head, tail;
	char		MapPath[SIZE_1K], RRname[SIZE_1K];
	//
	strcpy(MapPath, RainF);
	Get_Relative_Path(MapPath, DSET.Proj_Folder, RRname);
	if (kind == 0)	 m_Rainfile.Format("Output Rain file ->  %s", RRname);
	else           m_Rainfile.Format("Output Evp file ->  %s", RRname);
	//
	Head = RainF.Left(RainF.GetLength() - 4);
	tail = RainF.Right(4);
	RainMap = Head + "_Map" + tail;
	strcpy(MapPath, RainMap);
	Get_Relative_Path(MapPath, DSET.Proj_Folder, RRname);
	//
	s_MapName.Format("Output Map file    ->   %s", RRname);
	UDF;
	//
	Set_Dlg();
}

//_______________________________________________________________________________________
/// /////////////////////////////////////////////////////////////////////////////////////
//  START
/// /////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void CRThiessen::OnBnClickedOk()
{
	if (Rfile.IsEmpty() || RainF.IsEmpty() || RainMap.IsEmpty()) {
		m_Comment = "** Error ** Specify essential Files"; UDF; return;
	}


	CString		Dir;
	Get_Dir(RainF, &Dir);
	Rtemp.Format("%s/Temp_Gauge.txt", Dir);
	//

	//
	CString	fdir,fname;
	FILE*	fp;
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 元データの作成

	int			ret;
	if ((ret=Make_Rain_Data())) {
		fdir = "Unknown Error";
		if (ret == 1)			fdir.Format("** Error ** Cannot open [%s]", Rfile);
		else if (ret == 2)	fdir.Format("** Error ** Cannot allocate memory [Num = %d]", DSET.RGnum);
		else if (ret == 3)	fdir="** Error ** Out of data range or missmatching of time";
		else if (ret == 4)	fdir.Format("** Error ** Cannot open temprary file [%s]", Rtemp);
		else if (ret == 5)	fdir.Format("** Error ** Cannot allocate temporary memory");
		MessageBox(fdir, "alarm", MB_OK | MB_ICONERROR);
		CDialogEx::EndDialog(IDCANCEL);
		return;
	}
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// rainThiessen への書き込み
#ifdef   VER_64
	fdir.Format("%s\\RRI_CONTENTS\\BIN\\rainThiessen",m_BootPath);
#else
	fdir.Format("%s\\RRI_CONTENTS\\BIN32\\rainThiessen", m_BootPath);
#endif

	::SetCurrentDirectory(fdir);

	fname.Format("%s\\rainThiessen.txt",fdir);
	fp = fopen(fname, "w"); 
	if (fp == NULL) {
		m_Comment = "** Error ** rainThiessen.txt Open error"; UDF; return;
	}
	fprintf(fp, "%s\n", Rtemp);
	fprintf(fp, "%s\n", RainF);
	fprintf(fp, "%s\n", RainMap);
	//
	//
	fprintf(fp, "ncols  %d\n", Hnum);				
	fprintf(fp, "nrows  %d\n", Vnum);				
	fprintf(fp, "xll  %.2lf\n", lng);				
	fprintf(fp, "yll  %.2lf\n", lat);				
	fprintf(fp, "cellsize %.16lf\n", 1. / unit);		
	fclose(fp);
	if (kind == 0) {
		DSET.RH = Hnum;
		DSET.RV = Vnum;
		DSET.Rain_Lng = lng;
		DSET.Rain_Lat = lat;
		DSET.Rain_dx = DSET.Rain_dy = 1. / unit;
	}
	else if (kind == 1) {
		DSET.EH = Hnum;
		DSET.EV = Vnum;
		DSET.Evp_Lng = lng;
		DSET.Evp_Lat = lat;
		DSET.Evp_DX = DSET.Evp_DY = 1. / unit;
	}
	//
	/// --------------------------------EXCUTE
	if (kind == 0) m_Comment = "Start  rainThiessen program";
	else          m_Comment = "Start  evaporation program";
	UDF;
	Return_Val = system("rainThiessen.exe");
	if (!Return_Val) { //	SUCCEEDED
		if (kind == 0) strcpy(DSET.File_names[RAIN_FILE], RainF);
		else          strcpy(DSET.File_names[POTENT_FILE], RainF);
	}

	//
	CDialogEx::OnOK();
}
int CRThiessen::Make_Rain_Data()
{
	FILE*			fp = fopen(Rfile,"r");
	FILE*			fout;
	//
	char				buf[SIZE_16K], inchar[SIZE_01K];
	int				pos,Num,year,mon,day,hour,min;
	CTime			stT, endT,CT;
	CTimeSpan		TS;
	int*				val;
	//
	if (fp == NULL) return 1;
	//
	fgets(buf, SIZE_16K, fp); pos = 0;
	getstr(buf, &pos, inchar, SIZE_01K); DSET.RGmem = DSET.RGnum = Num = atoi(inchar);
	if ((DSET.RGpos = (LOCATE_INFO*)calloc(Num, sizeof(LOCATE_INFO))) == NULL) return 2;
	if ((val = (int*)calloc(Num, sizeof(int))) == NULL) {
		SAFE_FREE(DSET.RGpos);
		DSET.RGmem = DSET.RGnum = 0;
		fclose(fp); return 5;
	}
	//
	for (int i = 0; i < Num; i++) getstr(buf, &pos, DSET.RGpos[i].name, 48);
	//
	fgets(buf, SIZE_16K, fp); pos = 0;	getstr(buf, &pos, inchar, SIZE_01K);	// LAT
	for (int i = 0; i < Num; i++) {
		getstr(buf, &pos, inchar, SIZE_1K);
		DSET.RGpos[i].lat = atof(inchar);
	}
	//
	fgets(buf, SIZE_16K, fp); pos = 0;	getstr(buf, &pos, inchar, SIZE_01K);	// LNG
	for (int i = 0; i < Num; i++) {
		getstr(buf, &pos, inchar, SIZE_1K);
		DSET.RGpos[i].lng = atof(inchar);
	}
	//
	// Check
	int		cnt = 0, stcnt,Match_cnt = 0;
	while (fgets(buf, SIZE_16K, fp) != NULL) {
		pos = 0;	getstr(buf, &pos, inchar, SIZE_01K);
		sscanf(inchar, "%d/%d/%d", &year, &mon, &day);
		getstr(buf, &pos, inchar, SIZE_01K);
		sscanf(inchar, "%d:%d", &hour, &min);
		CT = ::CTime(year, mon, day, hour, min, 0, -1);
		//
		if (cnt == 0) stT = CT;
		else         endT = CT;
		//
		if (CT == PM.StTime)  {
			Match_cnt++; stcnt = cnt;
		}
		if (CT == PM.EndTime) Match_cnt++;
		cnt++;
	}
	if (	(Match_cnt != 2 )						||
		(PM.StTime < stT && PM.StTime > endT)	||
		(PM.EndTime < stT && PM.EndTime > endT)	)  {
		SAFE_FREE(DSET.RGpos); free(val);
		DSET.RGmem = DSET.RGnum = 0;
		fclose(fp); return 3;
	}
	//
	fclose(fp);
	fp = fopen(Rfile, "r");
	///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Write
	if ((fout = fopen(Rtemp, "w")) == NULL)  {
		SAFE_FREE(DSET.RGpos); free(val);
		DSET.RGmem = DSET.RGnum = 0;
		fclose(fp); return 4;
	}
	fprintf(fout, "%d", Num);
	for (int i = 0; i < Num; i++) fprintf(fout, "  %s", DSET.RGpos[i].name);
	fprintf(fout, "\n");
	fprintf(fout, "lat");
	for (int i = 0; i < Num; i++) fprintf(fout, "  %10.5lf", DSET.RGpos[i].lat);
	fprintf(fout, "\n");
	fprintf(fout, "lon");
	for (int i = 0; i < Num; i++) fprintf(fout, "  %10.5lf", DSET.RGpos[i].lng);
	fprintf(fout, "\n");
	//
	for (int i = 0; i < 3 + stcnt; i++)	fgets(buf, SIZE_16K, fp);	// 頭出し
	//
	while (fgets(buf, SIZE_16K, fp) != NULL) {		// 開始時刻に位置している
		pos = 0;	getstr(buf, &pos, inchar, SIZE_01K);
		sscanf(inchar, "%d/%d/%d", &year, &mon, &day);
		getstr(buf, &pos, inchar, SIZE_01K);
		sscanf(inchar, "%d:%d", &hour, &min);
		CT = ::CTime(year, mon, day, hour, min, 0, -1);
		for (int i = 0; i < Num; i++) {
			getstr(buf, &pos, inchar, SIZE_01K);
			val[i] = atoi(inchar);
		}
		//
		TS = CT - PM.StTime;
		fprintf(fout, "%d", TS.GetTotalSeconds());
		for (int i = 0; i < Num; i++) fprintf(fout, "  %6d", val[i]);
		fprintf(fout, "\n");
		////
		if (CT == PM.EndTime) break;
	}
	fclose(fp);
	fclose(fout);
	//
	free(val);
	return 0;
}



void CRThiessen::OnStnClickedRainfile()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
