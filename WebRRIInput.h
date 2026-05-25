
#pragma once

#include <afx.h>

#include <vector>

//=========================================================
// WEB-RRI INPUT STRUCTURES
//=========================================================

struct JOBNAME_INFO
{
    CString runname;

    CString para_dir;
    CString data_dir;

    CString result1_dir;
    CString result2_dir;

    CString simulation_dir;
    CString recv_dir;
};

//---------------------------------------------------------

struct MODEL_MODE_INFO
{
    BOOL RRI = FALSE;
    BOOL MIXED = FALSE;
};

//---------------------------------------------------------

struct IN_BOUNDARY_INFO
{
    BOOL IN_BOUND = FALSE;

    CString IN_FILE;

    int X_GRID = 0;
    int Y_GRID = 0;
};

//---------------------------------------------------------

struct TIMESTEP_INFO
{
    CString initime;

    int tstart = 0;
    int tstop = 0;

    int dt_couple = 0;
    int dtlsm = 0;
    int dthydro = 0;

    int recv_mode = 0;
};

//---------------------------------------------------------

struct POSITION_INFO
{
    double latsw = 0.0;
    double latne = 0.0;

    double lonsw = 0.0;
    double lonne = 0.0;

    double xsw = 0.0;
    double xne = 0.0;

    double ysw = 0.0;
    double yne = 0.0;
};

//---------------------------------------------------------

struct GRID_INFO
{
    double dx = 0.0;
    double dy = 0.0;

    double dzroot = 0.0;
    double dzdeep = 0.0;
};

//---------------------------------------------------------

struct MAPFILE_INFO
{
    CString gridarea_map;

    CString elevation_map;
    CString direction_map;
    CString accumulation_map;

    CString width_map;
    CString depth_map;

    CString levee_map;

    CString slopelength_map;
    CString slopeangle_map;

    CString soildepth_map;
    CString acquiferdepth_map;

    CString zref_map;
    CString met_alt_map;

    CString land_map;
    CString soil_map;

    CString soil_code;
    CString soil_table;

    CString met_map;
};

//---------------------------------------------------------

struct TOPOGRAPHY_INFO
{
    double ele0 = 0.0;
    double slope0 = 0.0;

    double length0 = 0.0;

    double Ds0 = 0.0;

    double deldpth = 0.0;

    double zwind0 = 0.0;
};

//---------------------------------------------------------

struct INITSOIL_INFO
{
    int sfcdat = 0;

    int vegfromtype = 0;

    int styp = 0;
    int vtyp = 0;

    double lai0 = 0.0;
    double veg0 = 0.0;

    int soilinit = 0;

    double tslnd0 = 0.0;
    double tscanp0 = 0.0;
    double tswtr0 = 0.0;
    double tsoil0 = 0.0;

    double vlcsfc0 = 0.0;
    double vlcrt0 = 0.0;
    double vlcdp0 = 0.0;

    double wetcanp0 = 0.0;
    double wetg0 = 0.0;

    double snowc0 = 0.0;
    double snowg0 = 0.0;

    double tsprt = 0.0;
    double tcprt = 0.0;
    double t2prt = 0.0;

    double wgrat = 0.0;
    double wrtrat = 0.0;
    double w2rat = 0.0;
};

//---------------------------------------------------------

struct LSMMODEL_INFO
{
    int rstopt = 0;
};

//---------------------------------------------------------

struct MISC_INFO
{
    double SSTMAX_CALIB = 0.0;

    double KSAT1_CALIB = 0.0;
    double KSAT2_CALIB = 0.0;

    double ROUGHNESS_N_CALIB = 0.0;

    double RIVER_ROUGHNESS_OVERRIDE = 0.0;

    double ANIK_CALIB = 0.0;

    CString GAUGEPOINT_SUBCATCHMENT;

    int riv_thres_in = 0;

    double width_param_c_in = 0.0;
    double width_param_s_in = 0.0;

    double depth_param_c_in = 0.0;
    double depth_param_s_in = 0.0;

    double height_param_in = 0.0;
    double height_limit_param_in = 0.0;

    int GAUGEPOINT_FLOWINT = 0;

    int OMP_NUM_THREADS = 0;
};

//---------------------------------------------------------

struct INPUT_INFO
{
    int INICON_CFG = 0;

    int fixed_inisub = 0;
    int fixed_finsub = 0;

    BOOL READ_REL_HUM = FALSE;

    BOOL UPD_PSFC = FALSE;
    BOOL UPD_TAIR = FALSE;

    BOOL READ_SEPARATE_U_V = FALSE;

    CString PREFIXES;
    CString PREFIX_RAIN;

    int METEO_INPUT_TYPE = 0;
    int RAINFALL_INPUT_TYPE = 0;

    BOOL MONTHLY_LAIFPAR = FALSE;
};

//---------------------------------------------------------

struct OUTPUT_INFO
{
    int OUT1_CODESTART = 0;
    int OUT1_CODEEND = 0;

    int OUT1_FLOWINT = 0;

    BOOL discharge_single_year = FALSE;
};

//---------------------------------------------------------

struct OUTPUT_DIS_INFO
{
    CString name;

    int LOC_I = 0;
    int LOC_J = 0;
};

//---------------------------------------------------------

struct DEBUGGING_INFO
{
    int POINTSCALE_I = -1;
    int POINTSCALE_J = -1;
};

//---------------------------------------------------------

struct SNOW_INFO
{
    double TH_SNOW = 0.0;
};

//---------------------------------------------------------

struct BATS_INFO
{
    double TH_SNOW = 0.0;

    double visalbedo = 0.0;
    double niralbedo = 0.0;
};

//---------------------------------------------------------

struct DAM_CONTROL_INFO
{
    int dam_switch = 0;

    CString damfile;
};

//=========================================================
// ROOT
//=========================================================

struct WEB_RRI_INPUT
{
    JOBNAME_INFO JOBNAME;

    MODEL_MODE_INFO MODEL_MODE;

    IN_BOUNDARY_INFO IN_BOUNDARY;

    TIMESTEP_INFO TIMESTEP;

    POSITION_INFO POSITION;

    GRID_INFO GRID;

    MAPFILE_INFO MAPFILE;

    TOPOGRAPHY_INFO TOPOGRAPHY;

    INITSOIL_INFO INITSOIL;

    LSMMODEL_INFO LSMMODEL;

    MISC_INFO MISC;

    INPUT_INFO INPUT;

    OUTPUT_INFO OUTPUT;

    std::vector<OUTPUT_DIS_INFO> OUTPUT_DIS;

    DEBUGGING_INFO DEBUGGING;

    SNOW_INFO SNOW;

    BATS_INFO BATS;

    DAM_CONTROL_INFO DAM_CONTROL;
};

//=========================================================
// FUNCTION
//=========================================================

BOOL LoadWebRRIInput(
    const CString& path,
    WEB_RRI_INPUT& input
);

BOOL SaveWebRRIInput(
    const CString& path,
    const WEB_RRI_INPUT& input
);