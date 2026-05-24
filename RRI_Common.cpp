#include		<afxwin.h>
#include		<strsafe.h>
#include		"RRI_Common.h"

#include		<map>			// 20190201 Add

#include		<vector>		// 20190201 Add
#include		"gdal_priv.h"	// 20190201 Add
#include		"cpl_conv.h"	// 20190201 Add
#include		"gdal.h"		// 20190201 Add
#include		"cpl_string.h"	// 20190201 Add
#include		"ogr_spatialref.h"	// 20190201 Add
#include		"cpl_minixml.h"	// 20190201 Add
#include		"commonutils.h"	// 20190201 Add
#include		"vectorUtil.h"

//-----------------------------------------------------------------------------------------------------------
//  GLOBAL 
extern		char			m_RecentPath[];
extern      int			File_Format[];
extern      int			File_Order[];
extern      CString		File_Title[];
extern      DATASET		DSET;						// ファイルセット
extern      PARAMS		PM;	
extern      	int			CellKind[];
// 基本情報

//-----------------------------------------------------------------------------------------------------------
//  ALLOC TIMESET 

BOOL	 Alloc_TIMESET(TIMESET* TS )
{
	if( (TS->name = Make_Matrix(SIZE_01K,TS->Mem,(char)0x00)) == NULL ) return FALSE;
	if ((TS->pos = (CPoint*)calloc(TS->Mem,sizeof(CPoint))) == NULL) {
												SAFE_FREE( TS->name ); return FALSE;}
	//
	if (TS->Smem != 0) {
		if ((TS->time = (int*)calloc(TS->Smem, sizeof(int))) == NULL) {
			SAFE_FREE(TS->name); SAFE_FREE(TS->pos); return FALSE;
		}
		//
		if ((TS->val = Make_Matrix(TS->Mem, TS->Smem, 0.)) == NULL){
			SAFE_FREE(TS->name); SAFE_FREE(TS->pos); SAFE_FREE(TS->time); return FALSE;
		}
	}
	//
	TS->Span = 0;
	TS->set = TRUE;
	return TRUE;
}
BOOL	 Realloc_TIMESET(int oldmem,int oldstep,TIMESET* TS)
{
	if ((TS->name = Resize_Matrix(TS->name, SIZE_01K, TS->Mem, SIZE_01K, oldmem, (char)0x00)) == NULL) return FALSE;
	if ((TS->pos = (CPoint*)realloc(TS->pos,TS->Mem*sizeof(CPoint))) == NULL) {
		Free_Matrix(TS->Mem, TS->name); return FALSE;
	}
	//
	if (oldstep == 0) {
		if ((TS->time = (int*)calloc(TS->Smem, sizeof(int))) == NULL) {
			Free_Matrix(TS->Mem,TS->name); SAFE_FREE(TS->pos); return FALSE;
		}
		//
		if ((TS->val = Make_Matrix(TS->Mem, TS->Smem, 0.)) == NULL){
			Free_Matrix(TS->Mem, TS->name); SAFE_FREE(TS->pos); SAFE_FREE(TS->time); return FALSE;
		}
	}
	else {
		if ((TS->time = (int*)realloc(TS->time,TS->Smem*sizeof(int))) == NULL) {
			Free_Matrix(TS->Mem, TS->name); SAFE_FREE(TS->pos); return FALSE;
		}
		//
		if ((TS->val = Resize_Matrix(TS->val,TS->Mem, TS->Smem, oldmem,oldstep,0.)) == NULL){
			Free_Matrix(TS->Mem, TS->name); SAFE_FREE(TS->pos); SAFE_FREE(TS->time); return FALSE;
		}
	}
	return TRUE;
}
void	 Free_TIMESET(TIMESET* TS)
{
	if( TS->set <= 0 ) return;
	//
	if (TS->name != NULL) Free_Matrix(TS->Mem, TS->name);
	//
	if( TS->pos  != NULL ) SAFE_FREE( TS->pos );
	//
	if( TS->time != NULL ) SAFE_FREE( TS->time );
	//
	if( TS->val != NULL )   Free_Matrix(TS->Smem,TS->val );
	//
	TS->Num = TS->Mem = TS->Smem = TS->Span = 0;
	TS->set = FALSE;

}
//
//-----------------------------------------------------------------------------------------------------------
//  ALLOC TIMESET  HANDLE
//
void	 Copy_TIMESET( TIMESET* TS, TIMESET* TT )
{
	if( TS->set ) Free_TIMESET( TS );
	TS->Num = TT->Num ;
	TS->Mem = TT->Mem;
	TS->Fid = TT->Fid;
	TS->Smem = TT->Smem;
	Alloc_TIMESET( TS );
	//
	TS->Span = TT->Span;
	for(int i=0;i<TS->Num;i++) {
		strcpy(TS->name[i],TT->name[i]);
		memcpy(&TS->pos[i],&TT->pos[i],sizeof( CPoint ));
		for(int v=0;v<TT->Span;v++) TS->val[v][i] = TT->val[v][i];
	}
	for(int i=0;i<TS->Span;i++) TS->time[i] = TT->time[i];
}
//
//-----------------------------------------------------------------------------------------------------------
//  COPY DAMCNT
//
void	 Copy_DAMCNT( DAMCNT* tar,DAMCNT org)
{
	memset( tar,0,sizeof( DAMCNT ));
	strcpy(tar->name,org.name);
	tar->x = org.x;
	tar->y = org.y;
	tar->vol = org.vol;
	tar->startq = org.startq;
}
//
//-----------------------------------------------------------------------------------------------------------
//  Relative Path
//
void		Get_Relative_Path(CString Fname, char* Dir, CString Rname)
{
	char		Cname[SIZE_1K],Rtemp[SIZE_1K];
	strcpy(Cname, Fname);
	strcpy(Rtemp, Rname);
	Get_Relative_Path(Cname, Dir, Rtemp);
	//
	Rname = Rtemp;
}

void	Get_Relative_Path(CString Fname, char* Dir, char* Rname)
{
	char		Cname[SIZE_1K];
	strcpy(Cname, Fname);
	Get_Relative_Path(Cname, Dir, Rname);
}
	void	Get_Relative_Path(char* Fname, char* Dir, char* Rname)
{
	int		flen,len,cnt;
	char		LongName[SIZE_1K];
	char		DirName[SIZE_1K];
	len = (int)strlen( Dir );
	strcpy(DirName, Dir);
	for (int i = 0; i < len; i++) if (DirName[i] == 0x5c) DirName[i] = 0x2f;
	//
	flen = (int)strlen(Fname);
	strcpy( LongName,Fname);
	for (int i = 0; i < flen; i++) if (LongName[i] == 0x5c) LongName[i] = 0x2f;
	//

	if (len == 0) {
		strcpy(Rname, LongName); return;
	}
	if (LongName[len] == 0x2f) {	// 通常処理
		LongName[len-1] = '.'; LongName[len] = 0x2f;
		cnt = 0;
		for(int i=len-1;i<flen;i++) Rname[cnt++] = LongName[i];
		Rname[cnt] = 0x00;
	}
	else strcpy(Rname, LongName);
	//
	return;
}
/////////////////////////////////////////////////////////////////////////////
//
void	Get_SuitScale(int scaleid,int num,double* x,double* vmin,double* vmax,int* rips,double* unit,int* fm)
{
	int		i,base1,cnt;
	double	drift,val;
	double	maxval,minval;
	double	vspan;

// 最大・最小値
	*vmin = *vmax = DUNDEF;
	for(i=0;i<num;i++) {
		if( i == 0 ) { maxval = minval = x[i];}
		else {
			if( maxval < x[i] )  maxval = x[i];
			if( minval > x[i] )  minval = x[i];
		}
	}
	//if( *vmax != DUNDEF ) maxval = *vmax;
	//else                  *vmax  = maxval;
	//if( *vmin != DUNDEF ) minval = *vmin;
	//else                  *vmin  = minval;
	*vmin = minval;
	*vmax = maxval;
	vspan = maxval - minval;
// 最大・最小値範囲
	val    = log10( vspan );
	if( val >= 0. ) 	base1  = (int)log10( vspan );
	else				base1  = (int)(log10( vspan )-1.);
	drift  = pow(10.,(log10(vspan)-(double)base1));

// 最大値範囲
	if( scaleid == AXIS_SMOLL ) {
		if( drift <= 1.0001 )		{*rips = 3; *unit = 1.*pow(10.,base1)/2.;if( val >= 0. ) base1--;}
		else if( drift <= 1.50001 )	{*rips = 4; *unit = 1.5*pow(10.,base1)/3.;if( val >= 0. ) base1--;}
		else if( drift <= 2.0001 )	{*rips = 3; *unit = 2.*pow(10.,base1)/2.;if( val >= 0. ) base1--;}
		else if( drift <= 3.0001 )	{*rips = 4; *unit = 3.*pow(10.,base1)/3.;}
		else if( drift <= 4.0001 )	{*rips = 3; *unit = 4.*pow(10.,base1)/2.;}
		else if( drift <= 5.0001 )	{*rips = 3; *unit = 5.*pow(10.,base1)/2.5;}
		else if( drift <= 6.0001 )	{*rips = 4; *unit = 6.*pow(10.,base1)/3.;}
		else if( drift <= 8.0001 )	{*rips = 5; *unit = 8.*pow(10.,base1)/4.;}
		else					{*rips = 6; *unit =10.*pow(10.,base1)/5.;}
	} else if(  scaleid == AXIS_MIDDLE ) {
		if( drift <= 1.0001 )		{*rips = 6; *unit = 1.*pow(10.,base1)/5.;if( val >= 0. ) base1--;}
		else if( drift <= 1.50001 )	{*rips = 4; *unit = 1.5*pow(10.,base1)/3.;if( val >= 0. ) base1--;}
		else if( drift <= 2.0001 )	{*rips = 5; *unit = 2.*pow(10.,base1)/4.;if( val >= 0. ) base1--;}
		else if( drift <= 3.0001 )	{*rips = 4; *unit = 3.*pow(10.,base1)/3.;}
		else if( drift <= 4.0001 )	{*rips = 5; *unit = 4.*pow(10.,base1)/4.;}
		else if( drift <= 5.0001 )	{*rips = 6; *unit = 5.*pow(10.,base1)/5.;}
		else if( drift <= 6.0001 )	{*rips = 4; *unit = 6.*pow(10.,base1)/3.;}
		else if( drift <= 8.0001 )	{*rips = 5; *unit = 8.*pow(10.,base1)/4.;}
		else					{*rips = 6; *unit =10.*pow(10.,base1)/5.;}
	} else if(  scaleid == AXIS_LARGE ) {
		if( drift <= 1.0001 )		{*rips =11; *unit = 1.*pow(10.,base1)/10.;if( val >= 0. ) base1--;}
		else if( drift <= 1.20001 )	{*rips = 7; *unit = 1.2*pow(10.,base1)/6.;if( val >= 0. ) base1--;}
		else if( drift <= 1.40001 )	{*rips = 8; *unit = 1.4*pow(10.,base1)/7.;if( val >= 0. ) base1--;}
		else if( drift <= 1.60001 )	{*rips = 9; *unit = 1.6*pow(10.,base1)/8.;if( val >= 0. ) base1--;}
		else if( drift <= 1.80001 )	{*rips =10; *unit = 1.8*pow(10.,base1)/9.;if( val >= 0. ) base1--;}
		else if( drift <= 2.0001 )	{*rips =11; *unit = 2.*pow(10.,base1)/10.;if( val >= 0. ) base1--;}
		else if( drift <= 4.0001 )	{*rips = 9; *unit = 4.*pow(10.,base1)/8.;if( val >= 0. ) base1--;}
		else if( drift <= 5.0001 )	{*rips =11; *unit = 5.*pow(10.,base1)/10.;}
		else if( drift <= 6.0001 )	{*rips = 7; *unit = 6.*pow(10.,base1)/6.;}
		else if( drift <= 8.0001 )	{*rips = 9; *unit = 8.*pow(10.,base1)/8.;}
		else					{*rips =11; *unit =10.*pow(10.,base1)/10.;}
	}
	if(*vmin == DUNDEF ) {
		cnt = (int)(minval/(*unit));
		if( minval >= 0. ) *vmin = (*unit)*cnt;
		else               *vmin = (*unit)*(cnt-1);
	}
	if( base1 >= 0 ) *fm = 0;
	else             *fm =  -base1;
	return;
}
///////////////////////////////////////////////////////////////////////////////////
// RRI 共通 関数
//
//
///////////////////////////////////////////////////////////////////////////////////
void	Get_Scale_Axis(double* Hmin,double*  Hmax,int* rips,double* unit,int* fm)
{
	double	vspan,val,drift;
	int		base1;
	//
	vspan = *Hmax - *Hmin;
// 最大・最小値範囲
	val    = log10( vspan );
	if( val >= 0. ) 	base1  = (int)log10( vspan );
	else				base1  = (int)(log10( vspan )-1.);
	drift  = pow(10.,(log10(vspan)-(double)base1));

// 範囲検索
	if( drift <= 1.0001 )			{*rips = 3; *unit = 1.*pow(10.,base1)/2.;if( val >= 0. ) base1--;}
	else if( drift <= 1.50001 )	{*rips = 4; *unit = 1.5*pow(10.,base1)/3.;if( val >= 0. ) base1--;}
	else if( drift <= 2.0001 )	{*rips = 3; *unit = 2.*pow(10.,base1)/2.;if( val >= 0. ) base1--;}
	else if( drift <= 2.5001 )	{*rips = 6; *unit = 2.5*pow(10.,base1)/5.;if( val >= 0. ) base1--;}
	else if( drift <= 3.0001 )	{*rips = 4; *unit = 3.*pow(10.,base1)/3.;}
	else if( drift <= 4.0001 )	{*rips = 3; *unit = 4.*pow(10.,base1)/2.;}
	else if( drift <= 5.0001 )	{*rips = 3; *unit = 5.*pow(10.,base1)/2.;}
	else if( drift <= 6.0001 )	{*rips = 4; *unit = 6.*pow(10.,base1)/3.;}
	else if( drift <= 7.0001 )	{*rips = 3; *unit = 7.*pow(10.,base1)/2.;}
	else if( drift <= 7.5001 )	{*rips = 4; *unit = 7.5*pow(10.,base1)/3.;}
	else if( drift <= 8.0001 )	{*rips = 5; *unit = 8.*pow(10.,base1)/4.;}
	else if( drift <= 9.0001 )	{*rips = 4; *unit = 9.*pow(10.,base1)/3.;}
	else					{*rips = 6; *unit =10.*pow(10.,base1)/5.;}
//
//  もし ｜最小値 負値 ｜　＜ UNIT
	if( *Hmin < 0. ) {
		if( fabs( *Hmin ) < *unit ) { *Hmin = -(*unit);}
	}
//
	*fm = 0;
	while( fmod( ((*unit)*pow(10.,(double)(*fm))),1.) > EPS4 ) {
		(*fm)++;
		if( (*fm) > 7 ) break;
	}
//
	return;
}

void	Get_GoodScale(int Num,double* val,double* Vmin,double* Vmax,int* Rip,double* Unit,int* Fm)
{
	*Vmin = -DUNDEF; *Vmax = DUNDEF;			// とりあえず距離の寸法
	for(int i=0;i<Num;i++) {
		if( *Vmin > val[i] ) *Vmin = val[i];
		if( *Vmax < val[i] ) *Vmax = val[i];
	}
	//
	int		rank,rip,Brip;
	double	Multi,Tunit,Bunit,Trate,Brate;
	
	rank = (int)log10( *Vmax );
	Multi = pow(10.,rank);
	//
	Bunit = DUNDEF;
	for(int i=1;i<=5;i++) {				// 1***, 4***,8***, を 1000,2000,3000,... で探る
		Tunit = i*Multi;
		if( Tunit > *Vmax ) break;
		if( fmod(*Vmax,Tunit) == 0. ) rip = (int)(*Vmax/Tunit );
		else                          rip = (int)(*Vmax/Tunit )+1;
		if(  rip < 2 || rip > 8 ) continue;
		//
		if( Bunit == DUNDEF ) {
			Bunit = Tunit;
			Brip  = rip;
			Brate = Trate = (Tunit - fmod((*Vmax),Tunit))/Tunit;
		}
		else {
			Trate = (Tunit - fmod((*Vmax),Tunit))/Tunit;
			if( Trate < Brate ) {Bunit = Tunit;Brate = Trate;Brip = rip;}
		}
	}
	//
	Multi = pow(10.,rank-1);			// 1***, 4***,8***, を 100,200,300,... で探る
	for(int i=1;i<=5;i++) {
		Tunit = i*Multi;
		if( fmod(*Vmax,Tunit) == 0. ) rip = (int)(*Vmax/Tunit );
		else                          rip = (int)(*Vmax/Tunit )+1;
		if(  rip < 2 || rip > 8 ) continue;
		//
		Trate = (Tunit - fmod((*Vmax),Tunit))/Tunit;
		if( Trate < Brate ) {Bunit = Tunit;Brate = Trate;Brip = rip;}
	}

	//
	*Rip = Brip;
	*Unit = Bunit;
	//
	if( Bunit > 1. ) *Fm = 0;
	else {
		rank = 1;
		while( fmod( Bunit*pow(10.,rank),1.) != 0. ) rank++;
		*Fm = rank;
	}
}
BOOL	Save_Color_Data(CString Boot,PARAMS* PM )
{
	CString		fname;
	//
	fname.Format("%s\\RRI_CONTENTS\\Color_Data_B.dat",Boot);
	FILE*		fp = fopen(fname,"w");
	if( fp == NULL ) return FALSE;
	//
	fprintf(fp, "[MESH_COLOR] 10\n");
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%d  %d  %d  %d\n", i, GetRValue(PM->COL_MESH[i]), GetGValue(PM->COL_MESH[i]), GetBValue(PM->COL_MESH[i]));
	}
	for (int i = 0; i<26; i++) {
		if( PM->Dcol[i].set ) {
			fprintf(fp,"%d  %d %d %d %.2lf\n",i,PM->Dcol[i].num,
				(int)PM->Dcol[i].Equal,(int)PM->Dcol[i].Mos,PM->Dcol[i].alpha);
			for(int k=0;k<PM->Dcol[i].num;k++) {
				fprintf(fp,"%lf %d %d %d\n",PM->Dcol[i].val[k],
					GetRValue(PM->Dcol[i].Rcol[k]),GetGValue(PM->Dcol[i].Rcol[k]),GetBValue(PM->Dcol[i].Rcol[k]));
			}
		}
	}
	fclose( fp );
	return TRUE;
}


CTime	StrDate_Time( char*  buf )
{
	char		cstr[SIZE_1K];
	int			pos,stg,len;
	int			val,year,month,day,hour,min,sec;
	//
	len = (int)strlen( buf );
	pos = stg = 0;
	year = month = day = hour = min = sec = UNDEF;
	//
	for(int k=0;k<SIZE_1K;k++) cstr[k] = 0x00;
	for(int i=0;i<len;i++) {
		if( buf[i] == '/' || buf[i] == ':' || (stg == 2 && pos != 0 && buf[i] == ' ') ) {	// day と時間の間
			val = atoi( cstr );
			switch ( stg ) {
				case 0: year = val;stg++;break;
				case 1: month = val;stg++;break;
				case 2: day = val;stg++;break;
				case 3: hour = val;stg++;break;
				case 4: min = val;stg++;break;
				case 5: sec = val;stg++;break;
			}
			for(int k=0;k<SIZE_1K;k++) cstr[k] = 0x00;
			pos = 0;
		}
		else 	cstr[ pos++ ] = buf[i];
	}
	if( pos > 0 )  {
		if( stg == 4 )				{min = atoi( cstr );stg++;}
		else if( stg == 5 )		{sec = atoi( cstr );stg++;}
		else                        return  NULL;
	}
	if( stg <= 4 ) return NULL;
	//
	if( stg == 5 ) return ::CTime(year,month,day,hour,min,0,-1);
	else             return ::CTime(year,month,day,hour,min,sec,-1);
}
void		Copy_DSET(DATASET* DT, DATASET DD)
{
	DT->set = DD.set;
	//
	strcpy(DT->Proj_Folder, DD.Proj_Folder);
	strcpy(DT->Proj_Title, DD.Proj_Title);
	strcpy(DT->InputFile, DD.InputFile);
	strcpy(DT->EX_Dem_File, DD.EX_Dem_File);
	//
	for (int i = 0; i < 8; i++) {
		strcpy(DT->Folder_Name[i], DD.Folder_Name[i]);
	}
	//
	DT->Cin_Need = DD.Cin_Need;
	DT->Cin_Exist = DD.Cin_Exist;
	DT->Cout_Need = DD.Cout_Need;
	DT->Cout_Exist = DD.Cout_Exist;
	//
	for (int i = 0; i<FILE_IN_NUM; i++) {
		DT->in_exist[i] = DD.in_exist[i];
		DT->in_avail[i] = DD.in_avail[i];
		DT->in_use[i] = DD.in_use[i];
		
		strcpy(DT->File_names[i], DD.File_names[i]);
		strcpy(DT->Input_names[i], DD.Input_names[i]);
	}
	for (int i = 0; i<FILE_ALL_NUM; i++) DT->need_save[i] = DD.need_save[i];
		///
	// OUTPUT file
	for (int i = 0; i<FILE_OUT_NUM; i++) {
		DT->out_exist[i] = DD.out_exist[i];
		DT->out_use[i] = DD.out_use[i];
		strcpy(DT->Out_names[i], DD.Out_names[i]);
	}
	//
	DT->SW_Dir = DD.SW_Dir;
	DT->SW_LatLong = DD.SW_LatLong;
	DT->Hours = DD.Hours;
	DT->DT = DD.DT;
	DT->DT_Riv = DD.DT_Riv;
	DT->Out_Num = DD.Out_Num;
	//
	DT->Rain_Lng = DD.Rain_Lng;
	DT->Rain_Lat = DD.Rain_Lat;
	DT->Rain_dx = DD.Rain_dx;
	DT->Rain_dy = DD.Rain_dy;
	//
	if (DT->LUmem > 0) SAFE_FREE(DT->LUdata);
	DT->b_CSexist = DD.b_CSexist;
	DT->b_CSrenumber = DD.b_CSrenumber;
	strcpy(DT->CoverFile, DD.CoverFile);
	strcpy(DT->SoilFile, DD.SoilFile);
	//
	DT->LUmem = DD.LUmem;
	DT->LUnum = DD.LUnum;
	if (DD.LUmem != 0) {
		DT->LUdata = (LUINFO*)malloc(DD.LUmem*sizeof(LUINFO));
		for (int i = 0; i<DD.LUmem; i++) {
			if (i < DD.LUnum)  memcpy(&DT->LUdata[i], &DD.LUdata[i], sizeof(LUINFO));
			else              memset(&DT->LUdata[i], 0, sizeof(LUINFO));
		}
	}
	memcpy(&DT->LU_Model, &DD.LU_Model, sizeof(LUINFO));
	//
	DT->Damc_Mem = DD.Damc_Mem;
	DT->Damc_Num = DD.Damc_Num;
	if (DT->DAMC != NULL) SAFE_FREE(DT->DAMC);
	if (DD.Damc_Mem != 0) {
		DT->DAMC = (DAMCNT*)malloc(DD.Damc_Mem*sizeof(DAMCNT));
		for (int i = 0; i < DD.Damc_Mem; i++) {
			if (i < DD.Damc_Num)  memcpy(&DT->DAMC[i], &DD.DAMC[i], sizeof(DAMCNT));
			else                 memset(&DT->DAMC[i], 0, sizeof(DAMCNT));
		}
	}
	//
	DT->Div_Num = DD.Div_Num;
	DT->Div_Mem = DD.Div_Mem;
	if (DT->DIVID != NULL) SAFE_FREE(DT->DIVID);
	if (DD.Div_Mem != 0) {
		DT->DIVID = (DIVISION*)malloc(DD.Div_Mem*sizeof(DIVISION));
		for (int i = 0; i < DD.Div_Mem; i++) {
			if (i < DD.Div_Num)  memcpy(&DT->DIVID[i], &DD.DIVID[i], sizeof(DIVISION));
			else                 memset(&DT->DIVID[i], 0, sizeof(DIVISION));
		}
	}

	//    上限 ３０ 固定
	//
	DT->Ns_River = DD.Ns_River;
	DT->Riv_Thresh = DD.Riv_Thresh;
	DT->Cof_WC = DD.Cof_WC;
	DT->Cof_WS = DD.Cof_WS;
	DT->Cof_DC = DD.Cof_DC;
	DT->Cof_DS = DD.Cof_DS;
	DT->Cof_H = DD.Cof_H;
	DT->Cof_Hlim = DD.Cof_Hlim;
	DT->Init_HS = DD.Init_HS;
	DT->Init_HR = DD.Init_HR;
	DT->Init_HG = DD.Init_HG;
	DT->Init_Gamp = DD.Init_Gamp;

	DT->CT_Rain = DD.CT_Rain;
	DT->CT_Evp = DD.CT_Evp;
	//
	DT->Lnum = DD.Lnum;
	DT->Lmem = DD.Lmem;
	if (DT->LCpos != NULL) SAFE_FREE(DT->LCpos);
	if (DD.Lmem != 0) {
		DT->LCpos = (LOCATE_INFO*)calloc(DD.Lmem,sizeof(LOCATE_INFO));
		for (int i = 0; i < DD.Lmem; i++) {
			if (i < DD.Lnum)  memcpy(&DT->LCpos[i], &DD.LCpos[i], sizeof(LOCATE_INFO));
			else             memset(&DT->LCpos[i], 0, sizeof(LOCATE_INFO));
		}
	}
	//
	DT->RGmem = DD.RGmem;
	DT->RGnum = DD.RGnum;
	if (DT->RGpos != NULL) SAFE_FREE(DT->RGpos);
	if (DD.RGmem != 0) {
		DT->RGpos = (LOCATE_INFO*)calloc(DD.RGmem,sizeof(LOCATE_INFO));
		for (int i = 0; i < DD.RGmem; i++) {
			if (i < DD.RGnum)  memcpy(&DT->RGpos[i], &DD.RGpos[i], sizeof(LOCATE_INFO));
			else              memset(&DT->RGpos[i], 0, sizeof(LOCATE_INFO));
		}
	}
	//
	if (DT->RAcc != NULL) SAFE_FREE(DT->RAcc);
	if (DT->Rdata != NULL) {
		for (int i = 0; i < DT->Rmem; i++) Free_Matrix(DT->RV, DT->Rdata[i].data);
		SAFE_FREE(DT->Rdata);
	}
	DT->Rmem = DD.Rmem;
	DT->RT = DD.RT;
	DT->RH = DD.RH;
	DT->RV = DD.RV;
	if (DD.Rmem != 0) {
		DT->Rdata = (TDIM2_DATA*)malloc(DD.Rmem*sizeof(TDIM2_DATA));
		for (int i = 0; i < DD.Rmem; i++) {
			DT->Rdata[i].data = Make_Matrix(DD.RH, DD.RV, 0.);
			for (int v = 0; v < DD.RV; v++) {
				for (int h = 0; h < DD.RH; h++) DT->Rdata[i].data[v][h] = DD.Rdata[i].data[v][h];
			}
		}
	}
	if (DD.RAcc != NULL) {
		DT->RAcc = Make_Matrix(DD.RH, DD.RV, 0.);
		for (int v = 0; v < DD.RV; v++) {
			for (int h = 0; h < DD.RH; h++) DT->RAcc[v][h] = DD.RAcc[v][h];
		}
	}
	//
	if (DT->EAcc != NULL) SAFE_FREE(DT->EAcc);
	if (DT->Edata != NULL) {
		for (int i = 0; i < DT->Emem; i++) Free_Matrix(DT->EV, DT->Edata[i].data);
		SAFE_FREE(DT->Edata);
	}
	DT->Emem = DD.Emem;
	DT->ET = DD.ET;
	DT->EH = DD.EH;
	DT->EV = DD.EV;
	if (DD.Emem != 0) {
		DT->Edata = (TDIM2_DATA*)malloc(DD.Emem*sizeof(TDIM2_DATA));
		for (int i = 0; i < DD.Emem; i++) {
			DT->Edata[i].data = Make_Matrix(DD.EH, DD.EV, 0.);
			for (int v = 0; v < DD.EV; v++) {
				for (int h = 0; h < DD.EH; h++) DT->Edata[i].data[v][h] = DD.Edata[i].data[v][h];
			}
		}
	}
	if (DD.EAcc != NULL) {
		DT->EAcc = Make_Matrix(DD.EH, DD.EV, 0.);
		for (int v = 0; v < DD.EV; v++) {
			for (int h = 0; h < DD.EH; h++) DT->EAcc[v][h] = DD.EAcc[v][h];
		}
	}



	DT->Evp_Lng = DD.Evp_Lng;
	DT->Evp_Lat = DD.Evp_Lat;
	DT->Evp_DX = DD.Evp_DX;
	DT->Evp_DY = DD.Evp_DY;
	//
	//
	if (DD.HSWLEV.set) Copy_TIMESET(&DT->HSWLEV, &DD.HSWLEV);
	if (DD.HRWLEV.set) Copy_TIMESET(&DT->HRWLEV, &DD.HRWLEV);
	if (DD.QSWLEV.set) Copy_TIMESET(&DT->QSWLEV, &DD.QSWLEV);
	if (DD.QRWLEV.set) Copy_TIMESET(&DT->QRWLEV, &DD.QRWLEV);
	//
}
void		Delete_DSET(DATASET* DT)
{
	if(! DT->set ) return;
	//	
	//
	if (DT->LUdata != NULL) 		SAFE_FREE(DT->LUdata);
	if (DT->LUmem != 0)  SAFE_FREE(DT->LUdata);
	//
	if (DT->DAMC != NULL) SAFE_FREE(DT->DAMC);
	if (DT->Damc_Mem != 0) SAFE_FREE(DT->DAMC);
	//
	if (DT->DIVID != NULL) SAFE_FREE(DT->DIVID);
	if (DT->Div_Mem != 0) SAFE_FREE(DT->DIVID);

	if (DT->LCpos != NULL) SAFE_FREE(DT->LCpos);
	if (DT->Lmem != 0) SAFE_FREE(DT->LCpos);

	if (DT->RAcc != NULL) Free_Matrix(DT->RV, DT->RAcc);
	if (DT->RGpos != NULL) SAFE_FREE(DT->RGpos);
	if (DT->RGmem != 0) SAFE_FREE(DT->RGpos);
	//
	if (DT->Rdata != NULL) {
		for (int i = 0; i < DT->Rmem; i++) Free_Matrix(DT->RV, DT->Rdata[i].data);
		SAFE_FREE(DT->Rdata);
	}
	//
	Free_Matrix(DT->EV, DT->EAcc);
//
	if (DT->Edata != NULL) {
		for (int i = 0; i < DT->Emem; i++) Free_Matrix(DT->EV, DT->Edata[i].data);
		SAFE_FREE(DT->Edata);
	}
	//
	Free_TIMESET(&DT->HSWLEV);
	Free_TIMESET(&DT->HRWLEV);
	Free_TIMESET(&DT->QSWLEV);
	Free_TIMESET(&DT->QRWLEV);
	//
	Free_Matrix(PM.MVnum, DT->RIVTXT);
	//
	memset(DT, 0, sizeof(DATASET));
}

///////////////////////////////////////////////////////////////////////////////////
// 
//  FILE I/O
//
///////////////////////////////////////////////////////////////////////////////////

int		Read_RRI_INPUT(DATASET* DS, FILE*  fp)
{
	char		buf[SIZE_1K], inchar[SIZE_01K];
	int			pos, ival, fileno = 0, Lowno = 0, id;
	CString		checkname;
	//_______________________________________________________________
	//  諸元のコピー
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i<FILE_IN_NUM; i++) {
		DS->in_exist[i] = DS->in_use[i] = FALSE;
		DS->File_names[i][0] = 0x00;
		DS->Input_names[i][0] = 0x00;
		if (i < FILE_OUT_NUM) {
			DS->Out_names[i][0] = 0x00;
			DS->out_exist[i] = DS->out_use[i] = FALSE;
		}
	}
	//_______________________________________________________________
	//	読込開始
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Lowno = 1;
	char JFLOW_BUF[SIZE_01K];
	char JFLOW_FLG[SIZE_01K];

	while (fgets(buf, SIZE_1K, fp) != NULL) {
		if (Lowno > 100 && strlen(buf) == 0) break;	// １００行目の改行

		pos = 0; getstr(buf, &pos, inchar, SIZE_01K);
		switch (Lowno) {
			//_______________________________________________________________
			//		1 基本ファイル
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 2: strcpy(DS->Proj_Title, inchar);  break;
		case 3: strcpy(DS->Input_names[RAIN_FILE], inchar); DS->in_use[RAIN_FILE] = TRUE;
			DS->Cin_Need++; break;
		case 4: strcpy(DS->Input_names[ADEM_FILE], inchar); DS->in_use[ADEM_FILE] = TRUE;
			DS->Cin_Need++; break;
		case 5: strcpy(DS->Input_names[ACC_FILE], inchar); DS->in_use[ACC_FILE] = TRUE;
			DS->Cin_Need++; break;
		case 6: strcpy(DS->Input_names[ADIR_FILE], inchar); DS->in_use[ADIR_FILE] = TRUE;
			DS->Cin_Need++; break;
			//_______________________________________________________________
			//		2 [simulation]諸元
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 8: sscanf(buf, "%d", &ival); DS->SW_LatLong = (BYTE)ival; PM.B_LatLng = !DS->SW_LatLong; break;
		case 9: sscanf(buf, "%d", &ival); DS->SW_Dir = (BYTE)ival; break;
		case 10: sscanf(buf, "%d", &DS->Hours); break;
		case 11: sscanf(buf, "%d", &DS->DT); break;
		case 12: sscanf(buf, "%d", &DS->DT_Riv); break;
		case 13: sscanf(buf, "%d", &DS->Out_Num); break;
		case 14: sscanf(buf, "%lf", &DS->Rain_Lng); break;
		case 15: sscanf(buf, "%lf", &DS->Rain_Lat); break;
		case 16: pos = 0; getstr(buf, &pos, inchar, SIZE_01K); DS->Rain_dx = atof(inchar);
			getstr(buf, &pos, inchar, SIZE_01K); DS->Rain_dy = atof(inchar); break;
			//_______________________________________________________________
			//		3 [landuse]諸元
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 18: pos = 0; getstr(buf, &pos, inchar, SIZE_01K); DS->Ns_River = Get_DecodedVal_Exponent(inchar); break;
		case 19: sscanf(buf, "%d", &DS->LUnum);
			DS->LUmem = DS->LUnum+1;
			DS->LUdata = NULL;
			if ((DS->LUdata = (LUINFO*)malloc(DS->LUmem*sizeof(LUINFO))) == NULL  )  {
				fclose(fp); return UNDEF + 100;
			}
			for (int i = 0; i < DS->LUmem; i++) {
				memset(&DS->LUdata[i], 0, sizeof(LUINFO));
				DS->LUdata[i].NO = i + 1;
			}

			break;
			//
		case 20:  pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].SW_kinema = (BYTE)atoi(inchar);
			}
			break;
			//
		case 21: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].ns_slope = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 22: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].soildepth = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 23: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].gammaa = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 25: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].ksv = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 26: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].faif = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 28: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].ka = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 29: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].gammam = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//
		case 30: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].beta = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//_______________________________________________________________
			//		 最終バージョン での追加
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 32: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].kgv = Get_DecodedVal_Exponent(inchar);
			}
			break;
		case 33: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].gammag = Get_DecodedVal_Exponent(inchar);
			}
			break;
		case 34: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].tg = Get_DecodedVal_Exponent(inchar);
			}
			break;
		case 35: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].fpg = Get_DecodedVal_Exponent(inchar);
			}
			break;
		case 36: pos = 0;
			for (int i = 0; i < DS->LUnum; i++) {
				getstr(buf, &pos, inchar, SIZE_01K); DS->LUdata[i].init_cond_gw = Get_DecodedVal_Exponent(inchar);
			}
			break;
			//_______________________________________________________________
			//		 河川の幅、深さの決定
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 38: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Riv_Thresh = atof(inchar); 
//				PM.Dcol[ACC_FILE].val[1] = DS->Riv_Thresh;		// カラーデータの書き換え
				break;
		case 39: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_WC = Get_DecodedVal_Exponent(inchar);break;
		case 40: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_WS = Get_DecodedVal_Exponent(inchar); break;
		case 41: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_DC = Get_DecodedVal_Exponent(inchar);  break;
		case 42: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_DS = Get_DecodedVal_Exponent(inchar); break;
		case 43: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_H = Get_DecodedVal_Exponent(inchar); break;
		case 44: pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K); DS->Cof_Hlim = atof(inchar); break;

			//_______________________________________________________________
			//		6 河川ファイルの設定
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 46: sscanf(buf, "%d", &ival);	
			DS->in_use[WIDTH_FILE] = DS->in_use[DEPTH_FILE] = DS->in_use[HEIGHT_FILE] = (BOOL)ival; 
			DS->Riv_Avail = (BOOL)ival;  break;
		case 47: strcpy(DS->Input_names[WIDTH_FILE], inchar); break;
		case 48: strcpy(DS->Input_names[DEPTH_FILE], inchar); break;
		case 49: strcpy(DS->Input_names[HEIGHT_FILE], inchar); break;

			//_______________________________________________________________
			//		 初期水深
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 51: pos = 0; id = 0;
			for (int i = 0; i < 4; i++) {
				if (i < 2) id = i;
				else if (i == 3) id = id - 1;
				getstr(buf, &pos, inchar, SIZE_01K);
				if (i != 2) DS->in_use[i + HS_FILE] = atoi(inchar);
			}
			break;
		case 52: strcpy(DS->Input_names[HS_FILE], inchar); break;
		case 53: strcpy(DS->Input_names[HR_FILE], inchar); break;
		case 54: strcpy(DS->Input_names[HG_FILE], inchar); break; 
		case 55: strcpy(DS->Input_names[GAMPT_FILE], inchar); break;

			//_______________________________________________________________
			//		初期設定ファイル
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case 57: pos = 0;
			for (int i = 0; i < 2; i++) {
				getstr(buf, &pos, inchar, SIZE_01K);
				DS->in_use[i + HS_WLEV_FILE] = atoi(inchar);
			}
			break;
		case 58: strcpy(DS->Input_names[HS_WLEV_FILE], inchar); break;
		case 59: strcpy(DS->Input_names[HR_WLEV_FILE], inchar); break;
			//
		case 61: pos = 0;
			for (int i = 0; i < 2; i++) {
				getstr(buf, &pos, inchar, SIZE_01K);
				DS->in_use[i + QS_WLEV_FILE] = atoi(inchar);
			}
			break;
		case 62: strcpy(DS->Input_names[QS_WLEV_FILE], inchar); break;
		case 63: strcpy(DS->Input_names[QR_WLEV_FILE], inchar); break;
			//
		case 65: DS->in_use[LU_FILE] = atoi(inchar); break;
		case 66: strcpy(DS->Input_names[LU_FILE], inchar); break;
			//
		case 68: DS->in_use[DAM_CNT_FILE] = atoi(inchar); break;
		case 69: strcpy(DS->Input_names[DAM_CNT_FILE], inchar); break;
			//
		case 71: DS->in_use[DIV_FILE] = atoi(inchar); break;
		case 72: strcpy(DS->Input_names[DIV_FILE], inchar); break;
			//
		case 74: DS->in_use[POTENT_FILE] = atoi(inchar); break;
		case 75: strcpy(DS->Input_names[POTENT_FILE], inchar); break;
		case 76: sscanf(buf, "%lf", &DS->Evp_Lng); break;
		case 77: sscanf(buf, "%lf", &DS->Evp_Lat); break;
		case 78: pos = 0;
			getstr(buf, &pos, inchar, SIZE_01K); DS->Evp_DX = atof(inchar);
			getstr(buf, &pos, inchar, SIZE_01K); DS->Evp_DY = atof(inchar);
			break;
			//
		case 80: DS->in_use[LENGTH_FILE] = atoi(inchar); break;
		case 81: strcpy(DS->Input_names[LENGTH_FILE], inchar); break;
			//
		case 83: DS->in_use[SEC_MAP_FILE] = atoi(inchar); break;
		case 84: strcpy(DS->Input_names[SEC_MAP_FILE], inchar); break;
		case 85: strcpy(DS->Input_names[SEC_HEADER], inchar); break;

			//_______________________________________________________________
			//		16 D2GIS設定ファイル
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		case 87: pos = 0;
			for (int i = 0; i < FILE_OUT_NUM; i++) {		// OUT_TECPLOT を除く
				getstr(buf, &pos, inchar, SIZE_01K);
				DS->out_use[i] = (BOOL)atoi(inchar);
			}
			break;
		case 88: strcpy(DS->Out_names[OUT_HS], inchar); break;
		case 89: strcpy(DS->Out_names[OUT_HR], inchar); break;
		case 90: strcpy(DS->Out_names[OUT_HG], inchar); break;
		case 91: strcpy(DS->Out_names[OUT_QR], inchar); break;
		case 92: strcpy(DS->Out_names[OUT_QU], inchar); break;
		case 93: strcpy(DS->Out_names[OUT_QV], inchar); break;
		case 94: strcpy(DS->Out_names[OUT_GU], inchar); break;
		case 95: strcpy(DS->Out_names[OUT_GV], inchar); break;
		case 96: strcpy(DS->Out_names[OUT_GAMPUT], inchar); break;
		case 97: strcpy(DS->Out_names[OUT_STORAGE], inchar); break;
			//
		case 99: DS->in_use[LOCATION_FILE] = (BOOL)atoi(inchar); break;
		case 100: strcpy(DS->Input_names[LOCATION_FILE], inchar); break;
		case 101: sscanf(inchar, "%s %s", JFLOW_BUF, JFLOW_FLG); 
			if (strcmp(JFLOW_BUF, "1") == 0) {
				PM.B_UseJFlow = true;
			}
			else {
				PM.B_UseJFlow = false;
			}
			break;
		default: break;
		}
		Lowno++;
	}
	if (Lowno < 101) return 101;
	fclose(fp);

	//
	Set_File_FullName(DS);
	//
	return 0;
}

//-----------------------------------------------------------------------------------------------------------
//   OUTPUT RRI_INPUT.txt
//-----------------------------------------------------------------------------------------------------------
int		Write_RRI_INPUT(DATASET DS)
{
	FILE*	fp;
	char		Rname[SIZE_1K],Sval[SIZE_01K];
	if ((fp = fopen(DS.InputFile, "w")) == NULL) return -1;	// 
	//
	fprintf(fp, "RRI_Input_Format_Ver1_4_2\n%s\n", DS.Proj_Title);
	//_______________________________________________________________
	//		1 基本ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i<4; i++) {
		Get_Relative_Path(DS.File_names[i], DS.Proj_Folder, Rname);
		fprintf(fp, "%s\n", DS.Input_names[i]);
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
	fprintf(fp, "%lf   # xllcorner_rain\n", DS.Rain_Lng);
	fprintf(fp, "%lf    # yllcorner_rain\n", DS.Rain_Lat);
	fprintf(fp, "%.10lf %.10lf    # cellsize_rain\n\n", DS.Rain_dx, DS.Rain_dy);

	//_______________________________________________________________
	//		3 [landuse]諸元
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//if (!PM.B_UseJFlow) {

		Get_Val_Exponent(DS.Ns_River, 3, Sval);
		fprintf(fp, "%s     # ns_river\n", Sval);
		fprintf(fp, "%d    # num_of_landuse\n", DS.LUnum);
		//
		for (int i = 0; i < DS.LUnum; i++) {
			if (i == 0) fprintf(fp, "%d", DS.LUdata[i].SW_kinema);
			else         fprintf(fp, "   %d", DS.LUdata[i].SW_kinema);
		}
		fprintf(fp, "    # diffusion(1) orr kinematic(0)\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].ns_slope, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # ns_slope\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].soildepth, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # soildepth\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].gammaa, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # gammaa\n\n");
		//---------------------------------------------------------------------------
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].ksv, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # ksv\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].faif, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # faif\n\n");
		//---------------------------------------------------------------------------
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].ka, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # ka\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].gammam, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # gammam\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].beta, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # beta\n\n");
		//---------------------------------------------------------------------------
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].kgv, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # kgv\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].gammag, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # gammag\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].tg, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # tg\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].fpg, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # fpg\n");
		//
		for (int i = 0; i < DS.LUnum; i++) {
			Get_Val_Exponent(DS.LUdata[i].init_cond_gw, 3, Sval);
			if (i == 0) fprintf(fp, "%s", Sval);
			else         fprintf(fp, "   %s", Sval);
		}
		fprintf(fp, "     # init_cond_gw\n\n");

	/*} else {
		FILE *jplndFp;
		CString	path;
		char bootPath[SIZE_05K];
		::GetCurrentDirectoryA(SIZE_05K, bootPath);
		char param[18][256];

		path.Format("%s\\RRI_CONTENTS\\LandUse\\J_lnd_PARAM.txt", bootPath);
		jplndFp = fopen(path, "r");
		for (int i = 0; i < 19; i++) {
			fgets(param[i], 256, jplndFp);
		}
		fprintf(fp, "%s", param[0]); // # ns_river
		fprintf(fp, "%s", param[1]); // # num_of_landuse
		fprintf(fp, "%s", param[2]); // # diffusion(1) orr kinematic(0)
		fprintf(fp, "%s", param[3]); // # ns_slope
		fprintf(fp, "%s", param[4]); // # soildepth
		fprintf(fp, "%s", param[5]); // # gammaa
		fprintf(fp, "%s", param[6]); // # (blank)
		fprintf(fp, "%s", param[7]); // # ksv
		fprintf(fp, "%s", param[8]); // # faif
		fprintf(fp, "%s", param[9]); // # (blank)
		fprintf(fp, "%s", param[10]); // # ka
		fprintf(fp, "%s", param[11]); // # gammam
		fprintf(fp, "%s", param[12]); // # beta
		fprintf(fp, "%s", param[13]); // # (blank)
		fprintf(fp, "%s", param[14]); // # kgv
		fprintf(fp, "%s", param[15]); // # gammag
		fprintf(fp, "%s", param[16]); // # tg
		fprintf(fp, "%s", param[17]); // # fpg
		fprintf(fp, "%s", param[18]); // # init_cond_gw
		fprintf(fp, "\n");
		fprintf(fp, "\n");
	}*/
	//_______________________________________________________________
	//		河道諸元
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d      # riv_thresh\n", (int)DS.Riv_Thresh);
	Get_Val_Exponent(DS.Cof_WC, 2, Sval);
	fprintf(fp, "%s      # width_param_c (2.5)\n", Sval);
	Get_Val_Exponent(DS.Cof_WS, 2, Sval);
	fprintf(fp, "%s      # width_param_s (0.4)\n", Sval);
	Get_Val_Exponent(DS.Cof_DC, 2, Sval);
	fprintf(fp, "%s      # depth_param_c (0.1)\n", Sval);
	Get_Val_Exponent(DS.Cof_DS, 2, Sval);
	fprintf(fp, "%s      # depth_param_s (0.4)\n", Sval);
	Get_Val_Exponent(DS.Cof_H, 2, Sval);
	fprintf(fp, "%s      # height_param\n", Sval);
	fprintf(fp, "%d       # height_limit_param\n\n", (int)DS.Cof_Hlim);
	//_______________________________________________________________
	//		河川ファイルの設定
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (DS.in_use[WIDTH_FILE] && DS.in_use[DEPTH_FILE] && DS.in_use[HEIGHT_FILE]) {
		fprintf(fp, "1\n");
		fprintf(fp, "%s\n", DS.Input_names[WIDTH_FILE]);
		fprintf(fp, "%s\n", DS.Input_names[DEPTH_FILE]);
		fprintf(fp, "%s\n", DS.Input_names[HEIGHT_FILE]);
	}
	else      {
		fprintf(fp, "0 \n");
		fprintf(fp, "%s\n", DS.Input_names[WIDTH_FILE]);
		fprintf(fp, "%s\n", DS.Input_names[DEPTH_FILE]);
		fprintf(fp, "%s\n", DS.Input_names[HEIGHT_FILE]);
	}
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		初期値ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 4; i++) {
		if (i == 0)  fprintf(fp, "%d", (int)DS.in_use[HS_FILE + i]);
		else         fprintf(fp, "  %d", (int)DS.in_use[HS_FILE + i]);
	}
	CR;
	fprintf(fp, "%s\n", DS.Input_names[HS_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[HR_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[HG_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[GAMPT_FILE]);
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		境界条件設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[HS_WLEV_FILE]);
	fprintf(fp, "  %d\n", (int)DS.in_use[HR_WLEV_FILE]);
	//
//	Get_Relative_Path(DS.File_names[HS_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", DS.Input_names[HS_WLEV_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[HR_WLEV_FILE]);
	//_______________________________________________________________
	//		流量境界条件ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d", (int)DS.in_use[QS_WLEV_FILE]);
	fprintf(fp, "  %d\n", (int)DS.in_use[QR_WLEV_FILE]);
	//
//	Get_Relative_Path(DS.File_names[QS_WLEV_FILE], DS.Proj_Folder, Rname);
	fprintf(fp, "%s\n", DS.Input_names[QS_WLEV_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[QR_WLEV_FILE]);
	//_______________________________________________________________
	//		土地利用ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[LU_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[LU_FILE]);
	//_______________________________________________________________
	//		ダム設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[DAM_CNT_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[DAM_CNT_FILE]);
	//_______________________________________________________________
	//		分流設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[DIV_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[DIV_FILE]);
	//_______________________________________________________________
	//		PotentialET  ?
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[POTENT_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[POTENT_FILE]);
	fprintf(fp, "%.1lf      # xllcorner_evp\n", DS.Evp_Lng);
	fprintf(fp, "%.1lf      # yllcorner_evp\n", DS.Evp_Lat);
	fprintf(fp, "%.10lf  %.10lf     # cellsize\n\n", DS.Evp_DX, DS.Evp_DY);
	//_______________________________________________________________
	//		? Add 2014/11
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[LENGTH_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[LENGTH_FILE]);
	//_______________________________________________________________
	//		? Add 2014/11 No 2 SEC_MAP
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[SEC_MAP_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[SEC_MAP_FILE]);
	fprintf(fp, "%s\n\n", DS.Input_names[SEC_HEADER]);
	//_______________________________________________________________
	//		出力設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i<FILE_OUT_NUM; i++) {
		if (i == 0) fprintf(fp, "%d", (int)(DS.out_use[i]));
		else         fprintf(fp, "  %d", (int)(DS.out_use[i]));
	} CR;
	for (int i = 0; i<FILE_OUT_NUM; i++) {
		fprintf(fp, "%s\n", DS.Out_names[i]);
	}
	fprintf(fp, "\n");
	//_______________________________________________________________
	//		LOCATION_FILE 設定ファイル
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fprintf(fp, "%d\n", (int)DS.in_use[LOCATION_FILE]);
	fprintf(fp, "%s\n", DS.Input_names[LOCATION_FILE]);
	//_______________________________________________________________
	//		JFLOW フラグ
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (PM.B_UseJFlow) {
		fprintf(fp, "1 #JFOW");
	}
	else {
		fprintf(fp, "0 #HYDROSHEDS");
	}
	fprintf(fp, "\n");
	// End
	fclose(fp);
	return 0;
}

int		Write_All_Files(int* Fform, int* Forder, DATASET DS, MINFO**	MESH, PARAMS PM)
{
	for (int i = 0; i < FILE_IN_USE; i++) {
		if (DS.in_use[i] && DS.in_avail[i]) 
			Write_Data_File(i, Fform[i],Forder[i],DS,PM, MESH);
	}
	return 0;
}


//-------------------------------------------------------------------------
//   Save File
//  ＊data は 1<= Did <= 12 まで使用　他は DSETに注意
//-------------------------------------------------------------------------
int		Write_Data_File(int Did, int Fform,int Forder, DATASET DS, PARAMS PM, MINFO** MESH)
{
	if (Fform == 9 || Forder == -1)			return -1;		// 書式なし
	if (Did < FILE_IN_NUM) if(!DS.in_avail[Did])	return -1;						// データなし
	//
	if (Did >= LAND_COVER && !DS.b_CSexist) return -1;
	//
	double**	data;
	if (Did <= GAMPT_FILE || Did == LAND_COVER || Did == LAND_SOIL) {
		data = Make_Matrix(PM.MHnum, PM.MVnum, 0.);
		//
		for (int v = 0; v < PM.MVnum; v++) {				// 注意）ここで天地ぎゃくにしてある。
			for (int h = 0; h < PM.MHnum; h++) {
				switch (Did) {

				case ADEM_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Adem;	break;
				case ACC_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Acc;		break;
				case ADIR_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Adir;	break;
				case SED_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Sed;		break;

				case LU_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Lu;			break;
				case WIDTH_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Rwidth;		break;
				case DEPTH_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Rdepth;		break;
				case HEIGHT_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Bheight;	break;

				case HS_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].HSinit;	break;
				case HR_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].HRinit;	break;
				case HG_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].HGinit;	break;
				case GAMPT_FILE: data[PM.MVnum - v - 1][h] = MESH[v][h].Gampt;	break;
				//
				case LAND_COVER: data[PM.MVnum - v - 1][h] = (double)MESH[v][h].Cover;break;
				case LAND_SOIL: data[PM.MVnum - v - 1][h] = (double)MESH[v][h].Soil;	break;
				//
				default: Free_Matrix(PM.MVnum, data);  return -1;
				}
			}
		}
	}

	FILE*		fp;
	CString		str, form, FORM,fname;
	//
	if (Did < LAND_COVER) {
		if ((fp = fopen(DS.File_names[Did], "w")) == NULL) {
			str.Format("Cannot open the file [ %s ]", DS.File_names[Did]);
			Free_Matrix(PM.MVnum, data); return -1;
		}
	}
	else {
		if (Did == LAND_COVER)			fp = fopen(DS.CoverFile, "w");
		else if (Did == LAND_SOIL)		fp = fopen(DS.SoilFile, "w");
		//
		if (fp == NULL) {
			str="Cannot open Cover or Soil.txt  file";
			Free_Matrix(PM.MVnum, data); return -1;
		}
	}
	///----------------------------------------------------------------------------------------------------*/
	//  File Format 0,1
	
	int			id,PV;
	//
	if (Fform <= 1)  {	// Param+Mesh  or Mesh
		if (Fform == 0) {
			fprintf(fp, "ncols	 %d\n", PM.MHnum);
			fprintf(fp, "nrows	 %d\n", PM.MVnum);
			if (PM.B_LatLng) {
				fprintf(fp, "xllcorner	 %.10lf\n", PM.stLNG);
				fprintf(fp, "yllcorner	 %.10lf\n", PM.stLAT);
				fprintf(fp, "cellsize	 %.14lf\n", PM.Size);
			}
			else {
				fprintf(fp, "xllcorner	 %.10lf\n", PM.stUTM_X);
				fprintf(fp, "yllcorner	 %.10lf\n", PM.stUTM_Y);
				fprintf(fp, "cellsize	 %.14lf\n", PM.UTMsize);
			}
			fprintf(fp, "NODATA_value  -9999 \n");
		}

		form.Format("%%.%dlf", Forder);
		FORM.Format("   %%.%dlf", Forder);
		//
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h<PM.MHnum; h++)  {
				if (MESH[PM.MVnum-v-1][h].flag >= 1) {		// ＭＥＳＨは下から上　ＤＡＴＡは上から下
					if (h == 0) fprintf(fp, form, data[v][h]);
					else         fprintf(fp, FORM, data[v][h]);
				}
				else {
					if (h == 0) fprintf(fp, " -9999");
					else         fprintf(fp, "   -9999");
				}

			}
			fprintf(fp, "\n");
		}
		//
	}
	///-----------------------------------------------------------------------------------------------------
	//  File Format == 2  　Place＆Series
	
	else if (Fform == 2) {		// TimeSet
		TIMESET*	TS;
		//
		switch (Did) {
		case HS_WLEV_FILE: TS = &DS.HSWLEV; TS->Fid = HS_WLEV_FILE; break;
		case HR_WLEV_FILE: TS = &DS.HRWLEV; TS->Fid = HR_WLEV_FILE; break;
		case QS_WLEV_FILE: TS = &DS.QSWLEV; TS->Fid = QS_WLEV_FILE; break;
		case QR_WLEV_FILE: TS = &DS.QRWLEV; TS->Fid = QR_WLEV_FILE; break;
		}
		//
		fprintf(fp, "   %d", TS->Num);
		for (int i = 0; i < TS->Num; i++) fprintf(fp, "  %s", TS->name[i]);
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
	// 0:param+mesh,1:mesh,2:TimeSet Place&Value  > 3:DAM_CNT_FILE 4:DIV_FILE,5:BREAK_FILE,6:EVP_FILE
	///-----------------------------------------------------------------------------------------------------
	//  File Format == 3  　DAM_CNT_FILE
	
	else if (Fform == 3) {
		fprintf(fp, "%10d\n", DS.Damc_Num);
		for (int i = 0; i<DS.Damc_Num; i++) {
			fprintf(fp, "%s  %5d   %5d   %.0lf   %.0lf\n", DS.DAMC[i].name,
				PM.MVnum - DS.DAMC[i].y, DS.DAMC[i].x + 1, DS.DAMC[i].vol, DS.DAMC[i].startq);
		}
	}
	///-----------------------------------------------------------------------------------------------------
	//  File Format == 4  　DIV_FILE

	else if (Fform == 4) {
		fprintf(fp, "%10d", DS.Div_Num);
		for (int i = 0; i<DS.Div_Num; i++) fprintf(fp, "  %s", DS.DIVID[i].name);
		CR;
		for (int i = 0; i<DS.Div_Num; i++) {
			fprintf(fp, "%d   %d   %d   %d   %.3lf\n", PM.MVnum - DS.DIVID[i].oy,DS.DIVID[i].ox + 1,
				 PM.MVnum - DS.DIVID[i].ty,DS.DIVID[i].tx + 1, DS.DIVID[i].rate);
		}
	}

	///-----------------------------------------------------------------------------------------------------
	//  File Format == 8  　LOCATION
	
	else if (Fform == 8) {
		for (int t = 0; t < DSET.Lnum; t++) {
			fprintf(fp, "%s  %d  %d\n", DSET.LCpos[t].name, DSET.LCpos[t].mz, DSET.LCpos[t].mx);
		}
	}
	//
	//-----------------------------------------------------------------------------------------------------
	//  End
	fclose(fp);
	if (Did <= GAMPT_FILE|| Did == LAND_COVER || Did == LAND_SOIL)  Free_Matrix(PM.MVnum, data);
	//
	return 0;
}

enum class TarFlag {
	NotRead = 0,		//break directly
	Read = 1,
	CheckMore = 2		//check more
};
using VTarFlag = std::vector<TarFlag>;

//Read mesh data of target ids
bool CopyDataToMesh(int Did, double** data, MINFO** MESH, const PARAMS& PM) {
	if (data == nullptr || MESH == nullptr) return false;

	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			switch (Did) {
				case RAIN_FILE:		DSET.Rdata[DSET.CT_Rain].data[v][h] = data[v][h]; break;	//  Rain 
				case ADEM_FILE:		MESH[v][h].Adem = data[v][h]; break;
				case ACC_FILE:		MESH[v][h].Acc	= data[v][h]; break;
				case ADIR_FILE:		MESH[v][h].Adir = static_cast<short>(data[v][h]); break;
				case SED_FILE:		MESH[v][h].Sed	= static_cast<short>(data[v][h]); break;

				case LU_FILE:		MESH[v][h].Lu		= static_cast<short>(data[v][h]); break;
				case WIDTH_FILE:	MESH[v][h].Rwidth	= data[v][h]; break;
				case DEPTH_FILE:	MESH[v][h].Rdepth	= data[v][h]; break;
				case HEIGHT_FILE:	MESH[v][h].Bheight	= data[v][h]; break;

				case HS_FILE:		MESH[v][h].HSinit	= data[v][h]; break;
				case HR_FILE:		MESH[v][h].HRinit	= data[v][h]; break;
				case HG_FILE:		MESH[v][h].HGinit	= data[v][h]; break;
				case GAMPT_FILE:	MESH[v][h].Gampt	= data[v][h]; break;

				case POTENT_FILE:	DSET.Edata[DSET.CT_Evp].data[v][h] = data[v][h]; break;
				case LAND_COVER:	MESH[v][h].Cover	= static_cast<short>(data[v][h]); break;
				case LAND_SOIL:		MESH[v][h].Soil		= static_cast<short>(data[v][h]); break;
				default:break;
			}
		}
	}

	return true;
}

bool CopyDataFromMesh(int Did, double** data, MINFO** MESH, const PARAMS& PM, const std::vector<int>& vExcludeIds) {
	if (data == nullptr || MESH == nullptr) return false;

	if (vectorUtil::contains<int>(vExcludeIds, Did)) return false;

	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			data[v][h] = NODATA;

			if (MESH[v][h].flag == 0) continue;

			switch (Did) {
				case RAIN_FILE:		data[v][h] = DSET.Rdata[DSET.CT_Rain].data[v][h]; break;	//  Rain 
				case ADEM_FILE:		data[v][h] = MESH[v][h].Adem; break;
				case ACC_FILE:		data[v][h] = MESH[v][h].Acc; break;
				case ADIR_FILE:		data[v][h] = static_cast<double>(MESH[v][h].Adir); break;
				case SED_FILE:		data[v][h] = static_cast<double>(MESH[v][h].Sed); break;
				case LU_FILE:		data[v][h] = static_cast<double>(MESH[v][h].Lu); break;
				case WIDTH_FILE:	data[v][h] = MESH[v][h].Rwidth; break;
				case DEPTH_FILE:	data[v][h] = MESH[v][h].Rdepth; break;
				case HEIGHT_FILE:	data[v][h] = MESH[v][h].Bheight; break;
				case HS_FILE:		data[v][h] = MESH[v][h].HSinit; break;
				case HR_FILE:		data[v][h] = MESH[v][h].HRinit; break;
				case HG_FILE:		data[v][h] = MESH[v][h].HGinit; break;
				case GAMPT_FILE:	data[v][h] = MESH[v][h].Gampt; break;
				case LENGTH_FILE:	data[v][h] = MESH[v][h].length; break;
				case SEC_MAP_FILE:	data[v][h] = MESH[v][h].sec_ID; break;
				case LAND_COVER:	data[v][h] = static_cast<double>(MESH[v][h].Cover);
					if (data[v][h] == NODATA) data[v][h] = 0.;
					break;
				case LAND_SOIL:  data[v][h] = static_cast<double>(MESH[v][h].Soil);
					if (data[v][h] == NODATA) data[v][h] = 0.;
					break;
				default: return false;
			}
		}
	}
	return true;
}

bool CopyDataFromMesh(int Did, int v, int h, double& value, MINFO** MESH, const PARAMS& PM, double defaultVal) {
	if (MESH == nullptr) return false;

	switch (Did) {
		case RAIN_FILE:     value = DSET.RAcc[v][h];	break;
		case ADEM_FILE:		value = MESH[v][h].Adem;		break;
		case ACC_FILE:		value = MESH[v][h].Acc;		break;
		case ADIR_FILE:		value = static_cast<double>(MESH[v][h].Adir);		break;
		case SED_FILE:		value = static_cast<double>(MESH[v][h].Sed);		break;  //
		case LU_FILE:		value = static_cast<double>(MESH[v][h].Lu);		break;
		case WIDTH_FILE:	value = MESH[v][h].Rwidth;		break;
		case DEPTH_FILE:	value = MESH[v][h].Rdepth;		break;
		case HEIGHT_FILE:	value = MESH[v][h].Bheight;	break;  //
		case HS_FILE:		value = MESH[v][h].HSinit;		break;
		case HR_FILE:		value = MESH[v][h].HRinit;		break;
		case HG_FILE:		value = MESH[v][h].HGinit;		break;
		case GAMPT_FILE:	value = MESH[v][h].Gampt;		break;  //
		case POTENT_FILE:	value = DSET.EAcc[v][h];	break;
		case LAND_COVER:	value = (MESH[v][h].Cover >= 0) ? static_cast<double>(MESH[v][h].Cover): defaultVal;	break;
		case LAND_SOIL:		value = (MESH[v][h].Soil >= 0) ? static_cast<double>(MESH[v][h].Soil): defaultVal;	break;
		default:			return  false;
	}
	return true;
}


//-------------------------------------------------------------------------
//   Save File
//  ＊data は 1<= Did <= 12 まで使用　他は DSETに注意
//-------------------------------------------------------------------------
int		WriteAs_Data_File(int Did, int Fform, int Forder, DATASET& DS, PARAMS& PM, MINFO** MESH)
{
	if (Fform == 9 || Forder == -1)			return -1;		// 書式なし
	if (!DS.in_avail[Did])	return -1;						// データなし
	//
	CString fname;
	if (!Button_File(FALSE, &fname, m_RecentPath, "SaveAs file", "*")) return -2;

	//
	double**	data;
	if (Did <= GAMPT_FILE) data = Make_Matrix(PM.MHnum, PM.MVnum, 0.);

	for (int v = 0; v < PM.MVnum; v++) {				// 注意）ここで天地ぎゃくにしてある。
		for (int h = 0; h < PM.MHnum; h++) {
			auto _data = 0;
			switch (Did) {
			case ADEM_FILE:		_data = MESH[v][h].Adem;		break;
			case ACC_FILE:		_data = MESH[v][h].Acc;			break;
			case ADIR_FILE:		_data = MESH[v][h].Adir;		break;
			case SED_FILE:		_data = MESH[v][h].Sed;			break;

			case LU_FILE:		_data = MESH[v][h].Lu;			break;
			case WIDTH_FILE:	_data = MESH[v][h].Rwidth;		break;
			case DEPTH_FILE:	_data = MESH[v][h].Rdepth;		break;
			case HEIGHT_FILE:	_data = MESH[v][h].Bheight;		break;

			case HS_FILE:		_data = MESH[v][h].HSinit;		break;
			case HR_FILE:		_data = MESH[v][h].HRinit;		break;
			case HG_FILE:		_data = MESH[v][h].HGinit;		break;
			case GAMPT_FILE:	_data = MESH[v][h].Gampt;		break;
			case HS_WLEV_FILE:	break;
			case HR_WLEV_FILE:	break;
			case QS_WLEV_FILE:	break;
			case QR_WLEV_FILE:	break;
			case DAM_CNT_FILE:	break;
			case LAND_COVER:
				_data = (MESH[v][h].Cover != 0) ? (double)MESH[v][h].Cover : NODATA;
				break;
			case LAND_SOIL:
				_data = (MESH[v][h].Cover != 0) ? (double)MESH[v][h].Soil : NODATA;
				break;
			default: if (Did <= GAMPT_FILE) Free_Matrix(PM.MVnum, data); return -1;
			}
			data[PM.MVnum - v - 1][h] = _data;
		}
	}

	FILE*		fp;
	CString		str, form, FORM;
	//
	if ((fp = fopen(fname, "w")) == NULL) {
		str.Format("Cannot open the file [ %s ] ", DS.File_names[Did]);
		Free_Matrix(PM.MVnum, data); return -1;
	}
	//
	//
	int			id, PV;
	//
	if (Fform <= 1)  {	// Param+Mesh  or Mesh
		if (Fform == 0) {
			fprintf(fp, "ncols	 %d\n", PM.MHnum);
			fprintf(fp, "nrows	 %d\n", PM.MVnum);
			fprintf(fp, "xllcorner	 %.1lf\n", PM.stLNG);
			fprintf(fp, "yllcorner	 %.1lf\n", PM.stLAT);
			fprintf(fp, "cellsize	 %.14lf\n", PM.Size);
			fprintf(fp, "NODATA_value  -9999 \n");
		}

		form.Format("%%5.%dlf", Forder);
		FORM.Format("   %%5.%dlf", Forder);
		//
		for (int v = 0; v < PM.MVnum; v++) {
			for (int h = 0; h<PM.MHnum; h++)  {
				if (MESH[PM.MVnum - v - 1][h].flag >= 1) {		// ＭＥＳＨは下から上　ＤＡＴＡは上から下
					if (h == 0) fprintf(fp, form, data[v][h]);
					else         fprintf(fp, FORM, data[v][h]);
				}
				else {
					if (h == 0) fprintf(fp, " -9999");
					else         fprintf(fp, "   -9999");
				}

			}
			fprintf(fp, "\n");
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 2  　Place＆Series
	//
	else if (Fform == 2) {		// TimeSet
		TIMESET*	TS;
		//
		switch (Did) {
		case HS_WLEV_FILE: TS = &DS.HSWLEV; TS->Fid = HS_WLEV_FILE; break;
		case HR_WLEV_FILE: TS = &DS.HRWLEV; TS->Fid = HR_WLEV_FILE; break;
		case QS_WLEV_FILE: TS = &DS.QSWLEV; TS->Fid = QS_WLEV_FILE; break;
		case QR_WLEV_FILE: TS = &DS.QRWLEV; TS->Fid = QR_WLEV_FILE; break;
		case DIV_FILE: TS = &DS.QRWLEV; TS->Fid = DIV_FILE; break;
		}
		//
		fprintf(fp, "   %d\n", TS->Num);
		for (int i = 0; i<TS->Num; i++) {
			fprintf(fp, "%s       %d  %d\n", TS->name[i], TS->pos[i].x + 1, PM.MVnum - TS->pos[i].y);
		}
		for (int i = 0; i<TS->Span; i++) {
			fprintf(fp, "%10d", TS->time[i]);
			for (int n = 0; n<TS->Num; n++) fprintf(fp, " %9.2lf", TS->val[i][n]);
			fprintf(fp, "\n");
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 3  　DAM_CNT_FILE
	//
	else if (Fform == 3) {
		fprintf(fp, "%10d\n", DS.Damc_Num);
		for (int i = 0; i<DS.Damc_Num; i++) {
			fprintf(fp, "%s %5d %5d %.0lf %.0lf\n", DS.DAMC[i].name, DS.DAMC[i].x + 1,
				PM.MVnum - DS.DAMC[i].y, DS.DAMC[i].vol, DS.DAMC[i].startq);
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 4  　DIV_FILE
	//
	else if (Fform == 4) {
		fprintf(fp, "%10d\n", DS.Div_Num);
		for (int i = 0; i<DS.Div_Num; i++) {
			fprintf(fp, "%d   %d   %d   %d   %.3lf\n", DS.DIVID[i].ox + 1, PM.MVnum - DS.DIVID[i].oy,
				DS.DIVID[i].tx + 1, PM.MVnum - DS.DIVID[i].ty, DS.DIVID[i].rate);
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 5  　BREAK Time
	//
	//else if (Fform == 5) {
	//	fprintf(fp, "%10d\n", DS.Break_Nums);
	//	for (int i = 0; i<DS.Break_Nums; i++) {
	//		fprintf(fp, "%d\n", DS.BreakTimes[i]);
	//	}
	//	fprintf(fp, "%10d\n", DS.Break_Cells);
	//	for (int i = 0; i<DS.Break_Cells; i++) {
	//		fprintf(fp, "%d,%d,%d\n", DS.BreakSet[i].x + 1, PM.MVnum - DS.BreakSet[i].y,
	//			(int)DS.BreakSet[i].flag);
	//	}
	//}

	//-----------------------------------------------------------------------------------------------------
	//  File Format == 6  　EVP  in_Avail（メッシュ数、始点、サイズが同じ場合しか通過しない。）
	//  DSET の CT_Evp の位置のデータだけを書き換える。
	//
	//else if (Fform == 6) {
	//	for (int t = 0; t<DS.ET; t++) {
	//		fprintf(fp, "%d  %d  %d\n", DS.Time_Evp[t], DS.EH, DS.EV);
	//		for (int v = 0; v<DS.EV; v++) {
	//			for (int h = 0; h<DS.EH; h++) {
	//				id = (DS.EV - 1 - v)*DS.EH + h;
	//				if (t == DS.CT_Evp) {
	//					if (h == 0) {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "%.5lf", PM.Values[id]);
	//						else                             fprintf(fp, "-9999");
	//					}
	//					else  {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "\t%.5lf", PM.Values[id]);
	//						else                             fprintf(fp, "\t-9999");
	//					}
	//				}
	//				else {
	//					if (h == 0) {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Evp[t] >= 0.) fprintf(fp, "%.5lf", MESH[id].Data_Evp[t]);
	//							else                          fprintf(fp, "-9999");
	//						}
	//						else                fprintf(fp, "-9999");
	//					}
	//					else   {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Evp[t] >= 0.) fprintf(fp, "\t%.5lf", MESH[id].Data_Evp[t]);
	//							else                          fprintf(fp, "\t-9999");
	//						}
	//						else                fprintf(fp, "\t-9999");
	//					}
	//				}
	//			}
	//			CR;
	//		}
	//	}
	//}
	//
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 7  　RAIN   基本的にEVPと同じ
	//
	//else if (Fform == 7) {
	//	for (int t = 0; t<DS.RT; t++) {
	//		fprintf(fp, "%d  %d  %d\n", DS.Time_Rain[t], DS.RH, DS.RV);
	//		for (int v = 0; v<DS.RV; v++) {
	//			for (int h = 0; h<DS.RH; h++) {
	//				id = (DS.RV - 1 - v)*DS.RH + h;
	//				if (t == DS.CT_Rain) {
	//					if (h == 0) {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "%.1lf", PM.Values[id]);
	//						else                             fprintf(fp, "-9999");
	//					}
	//					else  {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "\t%.1lf", PM.Values[id]);
	//						else                             fprintf(fp, "\t-9999");
	//					}
	//				}
	//				else {
	//					if (h == 0) {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Rain[t] >= 0.) fprintf(fp, "%.1lf", MESH[id].Data_Rain[t]);
	//							else                          fprintf(fp, "-9999");
	//						}
	//						else                fprintf(fp, "-9999");
	//					}
	//					else   {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Rain[t] >= 0.) fprintf(fp, "\t%.1lf", MESH[id].Data_Rain[t]);
	//							else                          fprintf(fp, "\t-9999");
	//						}
	//						else                fprintf(fp, "\t-9999");
	//					}
	//				}
	//			}
	//			CR;
	//		}
	//	}
	//}
	//
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 8  　DRAIN
	//
	//else if (Fform == 8) {
	//	for (int t = 0; t<DS.DrT; t++) {
	//		fprintf(fp, "%d  %d  %d\n", DS.Time_Drain[t], DS.DrH, DS.DrV);
	//		for (int v = 0; v<DS.DrV; v++) {
	//			for (int h = 0; h<DS.DrH; h++) {
	//				id = (DS.DrV - 1 - v)*DS.DrH + h;
	//				if (t == DS.CT_Drain) {
	//					if (h == 0) {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "%.5lf", PM.Values[id]);
	//						else                             fprintf(fp, "-9999");
	//					}
	//					else  {
	//						if (PM.Values[id] >= 0.) fprintf(fp, "\t%.5lf", data[id]);
	//						else                             fprintf(fp, "\t-9999");
	//					}
	//				}
	//				else {
	//					if (h == 0) {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Drain[t] >= 0.) fprintf(fp, "%.5lf", MESH[id].Data_Drain[t]);
	//							else                          fprintf(fp, "-9999");
	//						}
	//						else                fprintf(fp, "-9999");
	//					}
	//					else   {
	//						if (MESH[id].flag) {
	//							if (MESH[id].Data_Drain[t] >= 0.) fprintf(fp, "\t%.5lf", MESH[id].Data_Drain[t]);
	//							else                          fprintf(fp, "\t-9999");
	//						}
	//						else                fprintf(fp, "\t-9999");
	//					}
	//				}
	//			}
	//			CR;
	//		}
	//	}
	//	}
	//
	//-----------------------------------------------------------------------------------------------------
	//  End
	fclose(fp);
	if (Did <= GAMPT_FILE)  Free_Matrix(PM.MVnum, data);
	//
	return 0;
}
void		Make_String(double val, CString* str,int limit)
{
	CString		form;
	int			rank = 0;
	//
	if (val == 0.) *str = "0";
	else {
		double		aval = fabs(val) + EPS8;
		//
		while (fmod(aval*pow(10., rank), 1.) >= EPS3) { rank++; if (rank > 4) break; }
		//
		if (limit != UNDEF) {
			if (rank > limit) rank = limit;
		}
		//
		if (rank == 0)		str->Format("%d", (int)val);
		else	{
			form.Format("%%.%dlf", rank);
			str->Format(form, val);
		}
	}
}

int		Get_ArcGIS_Info(const char* fname, int* Hnum, int* Vnum, double* stLAT, double* stLNG, double* Size)
{
	FILE*	fp = fopen(fname, "r");
	if (fp == NULL) return 1;
	// -------------------------------------------------------------------------Setting
	fscanf(fp, "%*s %d", Hnum);						// 諸元の読込
	fscanf(fp, "%*s %d", Vnum);
	fscanf(fp, "%*s %lf", stLNG);
	fscanf(fp, "%*s %lf", stLAT);
	fscanf(fp, "%*s %lf", Size);
	fscanf(fp, "%*s %*s");
	//
	fclose(fp);
	return 0;
}

int		Set_File_FullName(DATASET* DS)
{
	if (strlen(DS->Proj_Folder) == 0) return UNDEF;
	//
	for (int f = 0; f < FILE_IN_NUM; f++) {
		if (strlen(DS->Input_names[f]) == 0) continue;
		//
		CString path = DS->Input_names[f];
		int pos = path.ReverseFind('/');
		CString fileName = path.Mid(pos + 1);
		if (path.Find("./riv") == 0) {
			sprintf(DS->File_names[f], "%s/INPUTS/parameters/%s", DS->Proj_WebRRIFolder, fileName);
		} 
		else if (path.Find("./topo") == 0) {
			sprintf(DS->File_names[f], "%s/INPUTS/parameters/%s", DS->Proj_WebRRIFolder, fileName);
		}
		else if (path.Find("./rain") == 0) {
			sprintf(DS->File_names[f], "%s/INPUTS/DIRECT/%s", DS->Proj_WebRRIFolder, fileName);
		}
		else if (path.Find("./out") == 0) {
			sprintf(DS->File_names[f], "%s/SIMU/OUT_RRI/%s", DS->Proj_WebRRIFolder, fileName);
		}
		else {
			sprintf(DS->File_names[f], "%s%s", DS->Proj_Folder, &DS->Input_names[f][1]);
		}
	}
	///
	//  Cover  Soil ファイルの定義
	sprintf(DS->CoverFile, "%s\\%s", DS->Proj_WebRRIFolder, COVER_TITLE);
	sprintf(DS->SoilFile, "%s\\%s", DS->Proj_WebRRIFolder, SOIL_TITLE);
	//
	return 0;
}


int		Set_Relative_Name(DATASET* DS)
{
	for (int f = 0; f < FILE_IN_NUM; f++) {
		if (strlen(DS->File_names[f]) == 0) continue;
		//
		Get_Relative_Path(DS->File_names[f], DS->Proj_Folder, DS->Input_names[f]);
	}
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ファイルの読み込み
int  Read_Data_File(int f, CString fname, DATASET* DS,MINFO** MESH)
{
	FILE*		fp;
	char			buf[SIZE_12K], inchar[SIZE_01K], name[SIZE_01K];
	int			pos, cnt;
	int			ID, vr;
	int			nH, nV, nT;
	//CString		Estr;
	double		val, vmax, vmin;
	short		sval, smax, smin;
	int			Lcnt = 0;		// ファイル行数
	//
	if ((fp = fopen(fname, "r")) == NULL) { return 101; }
	//
	int			FILEFORMAT;
	//
	if (f < FILE_IN_NUM) FILEFORMAT = File_Format[f];
	else {
		if (f == LAND_COVER || f == LAND_SOIL) FILEFORMAT = 0;
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format <= 1  1->12
	//
	if ( FILEFORMAT <= 1)  {	// Param+Mesh  or Mesh
		if (FILEFORMAT == 0) {
			if (f == LAND_COVER || f == LAND_SOIL) {		// メッシュ数のチェック
				fgets(buf, SIZE_12K, fp); pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K);	// cols
				getstr(buf, &pos, inchar, SIZE_01K); nH = atoi(inchar);
				fgets(buf, SIZE_12K, fp); pos = 0;
				getstr(buf, &pos, inchar, SIZE_01K);	//rows
				getstr(buf, &pos, inchar, SIZE_01K); nV = atoi(inchar);
				if (nH != PM.MHnum || nV != PM.MVnum) return 211;
				for (int i = 0; i < 4; i++) fgets(buf, SIZE_12K, fp);
			}
			else for (int i = 0; i < 6; i++) fgets(buf, SIZE_12K, fp);	// Param + mesh
		}
		//		cnt = 0;
		vmax = DUNDEF; vmin = -DUNDEF;
		smax = SUNDEF; smin = -SUNDEF;
		//
		if (f == ADEM_FILE) for (int i = 0; i < 10; i++) CellKind[i] = 0;
		//
		for (int v = 0; v<PM.MVnum; v++) {
			if (fgets(buf, SIZE_12K, fp) == NULL) { fclose(fp); return 1; }
			pos = 0;
			vr = PM.MVnum - v - 1;
			for (int h = 0; h<PM.MHnum; h++)  {
				if (getstr(buf, &pos, inchar, SIZE_01K) == EOF)  {
					fclose(fp);
					return 100;
				}
				//				cnt = (PM.Vnum - v - 1)*PM.Hnum + h;
				val = DUNDEF;
				sval = SUNDEF;
				switch (f) {
					case ADEM_FILE: val = MESH[vr][h].Adem = atof(inchar); break;
					case ACC_FILE: val = MESH[vr][h].Acc = atof(inchar); break;
					case ADIR_FILE: sval = MESH[vr][h].Adir = (short)atoi(inchar); break;
					case SED_FILE: sval = MESH[vr][h].Sed = (short)atoi(inchar); break;

					case LU_FILE: val = MESH[vr][h].Lu = atoi(inchar); break;

					case WIDTH_FILE: val = MESH[vr][h].Rwidth = atof(inchar); break;
					case DEPTH_FILE: val = MESH[vr][h].Rdepth = atof(inchar); break;
					case HEIGHT_FILE: val = MESH[vr][h].Bheight = atof(inchar); break;

					case HS_FILE: val = MESH[vr][h].HSinit = atof(inchar); break;
					case HR_FILE: val = MESH[vr][h].HRinit = atof(inchar); break;
					case HG_FILE: val = MESH[vr][h].HGinit = atof(inchar); break;
					case GAMPT_FILE: val = MESH[vr][h].Gampt = atof(inchar); break;
						//
					case LAND_COVER: sval = MESH[vr][h].Cover = (short)atoi(inchar); break;
					case LAND_SOIL: sval = MESH[vr][h].Soil = (short)atoi(inchar); break;
				}
				if (val != DUNDEF) {
					if (vmax < val) vmax = val; if (val > 0. && vmin > val) vmin = val;
				}
				if (sval != SUNDEF) {
					if (smax < sval) smax = sval; if (sval > 0 && smin > sval) smin = sval;
				}

				//
				// メッシュ有効・無効の識別　Adem ファイルによる
				// 河川フラッグは　ACC ファイルによる。
				if (f == ADEM_FILE) {
					if (MESH[vr][h].Adem  > -900.)	{	// 本来　-9999
						MESH[vr][h].flag = ID_MESH;
						PM.Anum++;
					}
					else	{
						MESH[vr][h].flag = 0;
					}
				}
				else if (f == ACC_FILE) {
					if (MESH[vr][h].flag == ID_MESH && MESH[vr][h].Acc >= DS->Riv_Thresh && DSET.Riv_Avail) 	MESH[vr][h].flag = ID_MESH_R;
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 2  　Place＆Series
	//
	else if (FILEFORMAT == 2) {		// TimeSet
		TIMESET*		TS;
		int			Mno;
		//
		while (fgets(buf, SIZE_12K, fp) != NULL) Lcnt++;
		fseek(fp, 0, SEEK_SET);	// Rewind
		//
		switch (f) {
		case HS_WLEV_FILE: TS = &DS->HSWLEV; TS->Fid = HS_WLEV_FILE; Mno = ID_MESH_HS; break;
		case HR_WLEV_FILE: TS = &DS->HRWLEV; TS->Fid = HR_WLEV_FILE; Mno = ID_MESH_HR; break;
		case QS_WLEV_FILE: TS = &DS->QSWLEV; TS->Fid = QS_WLEV_FILE; Mno = ID_MESH_QS; break;
		case QR_WLEV_FILE: TS = &DS->QRWLEV; TS->Fid = QR_WLEV_FILE; Mno = ID_MESH_QR; break;
		}
		//
		fgets(buf, SIZE_12K, fp); pos = 0;
		getstr(buf, &pos, inchar, SIZE_01K); TS->Num = atoi(inchar);	// セット数
		if (TS->Num <= 0 || TS->Num > 1000) {
			fclose(fp);
			return 1;
		}
		//
		TS->Smem = Lcnt - (TS->Num + 1) + TS_ADD_MEM;		// TS_ADD_MEM:余裕
		TS->Mem = TS->Num + TS_ADD_MEM;
		if (!Alloc_TIMESET(TS)) {
			fclose(fp);
			return 1;
		}
		//
		for (int i = 0; i < TS->Num; i++) {				// 名前の読み込み
			getstr(buf, &pos, inchar, SIZE_01K); 
			strcpy(TS->name[i], inchar);
		}
		//
		fgets(buf, SIZE_12K, fp); pos = 0;
		getstr(buf, &pos, inchar, SIZE_01K);	// Location   y
		for (int i = 0; i<TS->Num; i++) {
			getstr(buf, &pos, inchar, SIZE_01K); nV = atoi(inchar);
			if (nV <= 0 || nV > PM.MVnum) { fclose(fp); return 1; }
			TS->pos[i].y = PM.MVnum - nV;
		}

		fgets(buf, SIZE_12K, fp); pos = 0;
		getstr(buf, &pos, inchar, SIZE_01K);	// Location   x
		for (int i = 0; i<TS->Num; i++) {
			getstr(buf, &pos, inchar, SIZE_01K); nH = atoi(inchar);
			if (nH <= 0 || nH > PM.MHnum) { fclose(fp); return 1; }
			TS->pos[i].x = nH - 1;
		}
		//
		for (int i = 0; i < TS->Num; i++) {
			MESH[TS->pos[i].y][TS->pos[i].x].flag = Mno;
			//
			strcpy(MESH[TS->pos[i].y][TS->pos[i].x].name, TS->name[i]);
		}
		//
		TS->Span = 0;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			pos = 0;
			for (int n = 0; n <= TS->Num; n++) {		// 最初が時間 num + 1
				if (getstr(buf, &pos, inchar, SIZE_01K) == UNDEF) {
					//Estr.Format("** Error ** \n Time Series Invalid in %s", File_Title[f]);
					//MessageBox(Estr, "Error", MB_OK | MB_ICONEXCLAMATION);
					fclose(fp); return 1;
				}
				if (n == 0)		TS->time[TS->Span] = atoi(inchar);
				else   			TS->val[TS->Span][n - 1] = atof(inchar);
			}
			TS->Span++;
			//
		}
		TS->set = TRUE;
	}
	// 0:param+mesh,1:mesh,2:TimeSet Place&Value  > 3:DAM_CNT_FILE 4:DIV_FILE,5:BREAK_FILE,6:EVP_FILE
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 3  　DAM_CNT_FILE
	//
	else if (FILEFORMAT == 3) {
		fgets(buf, SIZE_12K, fp); sscanf(buf, "%d", &DS->Damc_Num);
		if (DS->Damc_Mem == 0) {
			DS->Damc_Mem = (DS->Damc_Num > 50) ? DS->Damc_Num+5:50;
			if ((DS->DAMC = (DAMCNT*)calloc(DS->Damc_Mem, sizeof(DAMCNT))) == NULL){ fclose(fp); return 1; }
		}
		//
		for (int i = 0; i<DS->Damc_Num; i++) {
			if (fgets(buf, SIZE_12K, fp) == NULL) { fclose(fp); return 1; }
			pos = 0;
			getstr(buf, &pos, inchar, SIZE_01K); strcpy(DS->DAMC[i].name, inchar);
			getstr(buf, &pos, inchar, SIZE_01K); nV = atoi(inchar);
			DS->DAMC[i].y = PM.MVnum - nV;
			getstr(buf, &pos, inchar, SIZE_01K);  nH = atoi(inchar);
			DS->DAMC[i].x = nH - 1;
			getstr(buf, &pos, inchar, SIZE_01K);  DS->DAMC[i].vol = atof(inchar);
			getstr(buf, &pos, inchar, SIZE_01K);  DS->DAMC[i].startq = atof(inchar);
			//
			MESH[DS->DAMC[i].y][DS->DAMC[i].x].flag = ID_MESH_DAM;
			strcpy(MESH[DS->DAMC[i].y][DS->DAMC[i].x].name, DS->DAMC[i].name);
		}
	}
	//-----------------------------------------------------------------------------------------------------
	//  File Format == 4  　DIV_FILE
	//
	else if (FILEFORMAT == 4) {
		fgets(buf, SIZE_12K, fp); pos = 0;
		getstr(buf, &pos, inchar, SIZE_01K); DS->Div_Num = atoi(inchar);
		//
		if (DS->Div_Num == 0) {fclose(fp); return 1;}
		if (DS->Div_Mem == 0) {
			DS->Div_Mem = (DS->Div_Mem > 50) ? DS->Damc_Num + 5 : 50;
			if ((DS->DIVID = (DIVISION*)calloc(DS->Damc_Mem, sizeof(DIVISION))) == NULL){ fclose(fp); return 1; }
		}
		// 名前を読む
		for (int i = 0; i < DS->Div_Num; i++) {
			getstr(buf, &pos, inchar, SIZE_01K); strcpy(DS->DIVID[i].name, inchar);
		}			
		//
		for (int i = 0; i < DS->Div_Num;i++) {
			fgets(buf, SIZE_12K, fp);
			pos = 0;
			getstr(buf, &pos, inchar, SIZE_01K); nV = atoi(inchar);
			DS->DIVID[i].oy = PM.MVnum - nV;
			getstr(buf, &pos, inchar, SIZE_01K); nH = atoi(inchar);
			DS->DIVID[i].ox = nH - 1;

			getstr(buf, &pos, inchar, SIZE_01K);   nV = atoi(inchar);
			DS->DIVID[i].ty = PM.MVnum - nV;
			getstr(buf, &pos, inchar, SIZE_01K);nH = atoi(inchar);
			DS->DIVID[i].tx = nH - 1;

			getstr(buf, &pos, inchar, SIZE_01K);  DS->DIVID[i].rate = atof(inchar);
			//
			MESH[DS->DIVID[i].oy][DS->DIVID[i].ox].flag = ID_MESH_DIV;
			MESH[DS->DIVID[i].ty][DS->DIVID[i].tx].flag = ID_MESH_DIV;
			strcpy(MESH[DS->DIVID[i].oy][DS->DIVID[i].ox].name, DS->DIVID[i].name);
			strcpy(MESH[DS->DIVID[i].ty][DS->DIVID[i].tx].name, DS->DIVID[i].name);
		}
		DS->in_use[f] = DS->in_avail[f] = TRUE;

	}
	///-----------------------------------------------------------------------------------------------------
	//  File Format == 5  　RAIN

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	///   RAIN   
	/*  雨や蒸発散はDSの中の TDIM3_DATA の中に読み込み、MESHデータには反映させない。表示も
	　　OBJID_RAINEVP を作成し、メッシュの上に表示する。
	  */
	else if (FILEFORMAT == 5) {
		//------------------------------------------------------------------------------
		Lcnt = 0;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			if (Lcnt == 0) {
				sscanf(buf, "%*s%d%d", &nH, &nV);
				DS->RH = nH;
				DS->RV = nV;
			}
			Lcnt++;
		}
		fseek(fp, 0, SEEK_SET);	// Rewind
		nT = Lcnt / (nV + 1);
		DS->Rmem = nT + 5;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Alloc
		if ((DS->Rdata = (TDIM2_DATA*)malloc(DS->Rmem*sizeof(TDIM2_DATA))) == NULL) {
			fclose(fp); return 511;
		}
		DS->RAcc = Make_Matrix(DS->RH, DS->RV, 0.);

		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Read

		double	tspan;
		int		told=0;	// 前の累加時間
		DS->RT = 0;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			sscanf(buf, "%d %d %d", &nT, &nH, &nV);
			//
			// CNT=0の場合にアロケーション
			if (DS->RT == 0) {
				for (int t = 0; t<DS->Rmem; t++) {
					if ((DS->Rdata[t].data = Make_Matrix(nH, nV, 0.)) == NULL) {
						fclose(fp); 
						return 512;
					}
				}
			}
			//
			DS->Rdata[DS->RT].time = DS->BT + CTimeSpan(0l, 0, 0, nT);
			tspan = (nT - told) / 3600.;
			for (int v = nV - 1; v >= 0; v--) {
				fgets(buf, SIZE_12K, fp);
				pos = 0;
				for (int h = 0; h<nH; h++) {
					if (getstr(buf, &pos, inchar, SIZE_01K) == EOF) {
						if (h < nH - 1) {	fclose(fp); return 513;}
					}
					DS->Rdata[DS->RT].data[v][h] = atof(inchar);
					//
					DS->RAcc[v][h] += (DS->Rdata[DS->RT].data[v][h]*tspan);
				}
			}
			told = nT;
			DS->RT++;
		}
	}
	///-----------------------------------------------------------------------------------------------------
	//  File Format == 6  　EVP
	else if (FILEFORMAT == 6) {
		//------------------------------------------------------------------------------
		Lcnt = 0;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			if (Lcnt == 0) {
				sscanf(buf, "%*s%d%d", &nH, &nV);
				DS->EH = nH;
				DS->EV = nV;
			}
			Lcnt++;
		}
		fseek(fp, 0, SEEK_SET);	// Rewind
		nT = Lcnt / (nV + 1);
		DS->Emem = nT + 5;
		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Alloc
		if ((DS->Edata = (TDIM2_DATA*)malloc(DS->Emem*sizeof(TDIM2_DATA))) == NULL) {
			fclose(fp); return 611;
		}
		DS->EAcc = Make_Matrix(DS->EH, DS->EV, 0.);

		///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Read

		double	tspan;
		int		told = 0;	// 前の累加時間
		DS->ET = 0;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			sscanf(buf, "%d %d %d", &nT, &nH, &nV);
			//
			// CNT=0の場合にアロケーション
			if (DS->ET == 0) {
				for (int t = 0; t<DS->Emem; t++) {
					if ((DS->Edata[t].data = Make_Matrix(nH, nV, 0.)) == NULL) {
						fclose(fp);
						return 512;
					}
				}
			}
			//
			DS->Edata[DS->ET].time = DS->BT + CTimeSpan(0l, 0, 0, nT);
			tspan = (nT - told) / 3600.;
			for (int v = nV - 1; v >= 0; v--) {
				fgets(buf, SIZE_12K, fp);
				pos = 0;
				for (int h = 0; h<nH; h++) {
					if (getstr(buf, &pos, inchar, SIZE_01K) == EOF) {
						if (h < nH - 1) { fclose(fp); return 513; }
					}
					DS->Edata[DS->ET].data[v][h] = atof(inchar);
					//
					DS->EAcc[v][h] += (DS->Edata[DS->ET].data[v][h] * tspan);
				}
			}
			told = nT;
			DS->ET++;
		}
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// File Format == 8  　LOCATION
	else if (FILEFORMAT == 8) {
		if (DS->Lmem == 0) {
			DS->Lnum = 0;
			DS->Lmem = 50;
			if ((DS->LCpos = (LOCATE_INFO*)calloc(DS->Lmem, sizeof(LOCATE_INFO))) == NULL) return 801;
		}

		//
		fseek(fp, 0, SEEK_SET);
		int		xh, yv;
		while (fgets(buf, SIZE_12K, fp) != NULL) {
			sscanf(buf, "%s %d %d", DS->LCpos[DS->Lnum].name, &yv, &xh);
			if (xh < 0 && xh > PM.MHnum) continue;
			if (yv < 0 && yv > PM.MVnum) continue;
			//
			DS->LCpos[DS->Lnum].mx = xh;
			DS->LCpos[DS->Lnum].mz = yv;
			DS->LCpos[DS->Lnum].Hid = xh - 1;
			DS->LCpos[DS->Lnum].Vid = PM.MVnum - yv;
			MESH[DS->LCpos[DS->Lnum].Vid][DS->LCpos[DS->Lnum].Hid].flag += ID_MESH_LOC;
			strcpy(MESH[DS->LCpos[DS->Lnum].Vid][DS->LCpos[DS->Lnum].Hid].name, DS->LCpos[DS->Lnum].name);
			DS->Lnum++;
		}
		DS->in_avail[f] = TRUE;
	}
	fclose(fp);
	//
	fflush(fp);
	//
	return 0;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Land Usage LABLE
BOOL Search_LU_Label_Order(MINFO** MESH)
{
	int			LID;
	int			Lnum, Lmem;
	int*			LABEL;
	BOOL			exist;
	//
	Lmem = 20;
	LABEL = (int*)malloc(Lmem*sizeof(int));
	//
	Lnum = 0;
	for (int v = 0; v < PM.MVnum; v++) {
		for (int h = 0; h < PM.MHnum; h++) {
			if (MESH[v][h].Lu <= 0) continue;
			//
			LID = MESH[v][h].Lu;
			exist = FALSE;
			for (int i = 0; i < Lnum; i++) if (LABEL[i] == LID) { exist = TRUE; break; }
			//
			if (!exist) LABEL[Lnum++] = LID;
			if (Lnum == Lmem) {
				Lmem += 10;
				LABEL = (int*)realloc(LABEL,Lmem*sizeof(int));
			}
		}
	}
	//
	I_Sort(Lnum, LABEL, SORT_INC);
	//
	if (DSET.LUmem < Lnum) {
		int		Lold = DSET.LUnum;
		DSET.LUmem = Lnum + 1;
		if ((DSET.LUdata = (LUINFO*)realloc(DSET.LUdata, DSET.LUmem*sizeof(LUINFO))) == NULL) return FALSE;
		//
		for (int i = Lold; i < DSET.LUmem; i++) memset(&DSET.LUdata[i], 0x0, sizeof(LUINFO));
	}
	//
	DSET.LUnum = Lnum;
	//
	SAFE_FREE(LABEL);
	return TRUE;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Exponent Disp
void		Set_CWnd_Exponent(CWnd* cw, double val, int rank)
{
	char		*cp,temp[SIZE_1K], form[SIZE_1K],exp[10];
	int		cnt,inc,ival;
	//
	sprintf(form, "%%.%de", rank);
	sprintf(temp, form, val);
	cp = temp;
	cnt = 0;
	while (TRUE) {
		if ((*cp) == 'e') { *cp = 'd'; break; }
		cnt++; cp++;
	}
	inc = 0;
	for (int i = cnt + 1; i < strlen(temp); i++) exp[inc++] = temp[i];
	ival = atoi(exp);
	sprintf(&temp[cnt + 1], "%d", ival);
	//
	cw->SetWindowTextA(temp);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Exponent Disp
void		Get_Val_Exponent(double val, int rank, char* Str)
{
	char		*cp, temp[SIZE_1K], form[SIZE_1K], exp[10];
	int		cnt, inc, ival;
	//
	sprintf(form, "%%.%de", rank);
	sprintf(temp, form, val);
	cp = temp;
	cnt = 0;
	while (TRUE) {
		if ((*cp) == 'e') { *cp = 'd'; break; }
		cnt++; cp++;
	}
	inc = 0;
	for (int i = cnt + 1; i < strlen(temp); i++) exp[inc++] = temp[i];
	ival = atoi(exp);
	sprintf(&temp[cnt + 1], "%d", ival);
	//
	strcpy(Str, temp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void		Copy_Luinfo(LUINFO* tar, LUINFO org)
{
	tar->NO = org.NO;
	tar->renumber = org.renumber;

	tar->SW_kinema = org.SW_kinema;
	tar->appflag = org.appflag;
	//
	tar->ns_slope = org.ns_slope;
	tar->soildepth = org.soildepth;
	//
	tar->gammaa = org.gammaa;
	tar->ksv = org.ksv;
	tar->faif = org.faif;
	//
	tar->ka = org.ka;
	tar->gammam = org.gammam;
	tar->beta = org.beta;
	//
	tar->kgv = org.kgv;
	tar->gammag = org.gammag;
	tar->tg = org.tg;
	tar->fpg = org.fpg;
	tar->init_cond_gw = org.init_cond_gw;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL		IsSame_Luinfo(LUINFO tar, LUINFO org)
{
	if (tar.ns_slope != org.ns_slope) return FALSE;

	if (tar.gammaa != org.gammaa) return FALSE;
	if (tar.ksv != org.ksv) return FALSE;
	if (tar.faif != org.faif) return FALSE;
	//
	if (tar.ka != org.ka) return FALSE;
	if (tar.gammam != org.gammam) return FALSE;
	if (tar.beta != org.beta) return FALSE;

	if (tar.kgv != org.kgv) return FALSE;
	if (tar.gammag != org.gammag) return FALSE;
	if (tar.tg != org.tg) return FALSE;
	if (tar.fpg != org.fpg) return FALSE;
	if (tar.init_cond_gw != org.init_cond_gw) return FALSE;
	//
	return TRUE;
}

CString Param_get(CString fname, CString Key, CString Def)
{
	FILE*	fp = fopen(fname, "r");
	char	buff[SIZE_1K];
	CString	cBuf;
	CString	cStr1 = "";
	CString	cStr2 = "";
	if (fp == NULL) return "";
	while (fgets(buff, SIZE_1K, fp) != NULL)
	{
		if (!memcmp(&buff[0], "#", 1))
		{
			continue;
		}
		cBuf.Format("%s", buff);
		int Pos = cBuf.FindOneOf("=");
		cStr1 = cBuf.Mid(0, (Pos - 1)).Trim();
		cStr2 = cBuf.Mid((Pos + 1)).Trim();

		if (cStr1 == Key)
		{
			break;
		}
		cStr1 = "";
		cStr2 = "";
	}

	if (cStr2.GetLength() == 0)
	{
		cStr2 = Def;
	}

	return cStr2;
}

void GetMeshTable(CString fname, std::map<CString, CString> &dic_Area_Directory, std::map<CString, CString> &dic_Area_MeshTable1)
{
}

/************************************************************************/
/*                             SanitizeSRS                              */
/************************************************************************/

char *SanitizeSRS(const char *pszUserInput)

{
	CPLErrorReset();

	OGRSpatialReferenceH hSRS = OSRNewSpatialReference(nullptr);

	char *pszResult = nullptr;
	if (OSRSetFromUserInput(hSRS, pszUserInput) == OGRERR_NONE)
		OSRExportToWkt(hSRS, &pszResult);
	else
	{
		CPLError(CE_Failure, CPLE_AppDefined,
			"Translating source or target SRS failed:\n%s",
			pszUserInput);
		exit(1);
	}

	OSRDestroySpatialReference(hSRS);

	return pszResult;
}

double Get_DecodedVal_Exponent(CString Str)
{
	double ret;
	float val;
	int rank;
	char *tp;
	char inStr[20];

	strcpy(inStr, Str);

	tp = strtok(inStr, "d");
	val = atof(inStr);
	tp = strtok(NULL, "d");
	if (tp != NULL) {
		rank = atoi(tp);
	}
	else {
		rank = 0;
	}

	if (rank < 0) {
		ret = val / pow(10, ((-1) * rank));
	}
	else if (rank == 0) {
		ret = val;
	}
	else {
		ret = val * 10 * rank;
	}

	return ret;
}
