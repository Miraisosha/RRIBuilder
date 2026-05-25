
#include <string>
#include <tchar.h>
#include "stdafx.h"
#include "WebRRIInput.h"
#include <fstream>

//=========================================================
// helper
//=========================================================

static CString TrimQuote(CString str)
{
    str.Trim();

    if (str.GetLength() >= 2)
    {
        if (str[0] == '\'' &&
            str[str.GetLength() - 1] == '\'')
        {
            str =
                str.Mid(
                    1,
                    str.GetLength() - 2);
        }
    }

    return str;
}

//---------------------------------------------------------

static BOOL ParseBool(CString str)
{
    str.Trim();
    str.MakeLower();

    return
        str == ".true." ||
        str == "true" ||
        str == "1";
}

//=========================================================
// Load WEB-RRI input.txt
//=========================================================

BOOL LoadWebRRIInput(
    const CString& path,
    WEB_RRI_INPUT& input)
{
    std::ifstream ifs((LPCTSTR)path);

    if (!ifs)
    {
        return FALSE;
    }

    std::string line;

    CString section;

    while (std::getline(ifs, line))
    {
        CString str(line.c_str());

        str.Trim();

        // inline comment remove
        int commentPos = str.Find(_T('!'));

        if (commentPos >= 0)
        {
            str = str.Left(commentPos);
            str.Trim();
        }


        if (str.IsEmpty())
        {
            continue;
        }

        //-------------------------------------------------
        // section start
        //-------------------------------------------------

        if (str[0] == '&')
        {
            section = str.Mid(1);

            section.Trim();

            continue;
        }

        //-------------------------------------------------
        // section end
        //-------------------------------------------------

        if (str == "/")
        {
            section.Empty();

            continue;
        }

        //-------------------------------------------------
        // key = value
        //-------------------------------------------------

        int pos = str.Find('=');

        if (pos < 0)
        {
            continue;
        }

        CString key =
            str.Left(pos);

        CString value =
            str.Mid(pos + 1);

        key.Trim();
        value.Trim();

        //=================================================
        // JOBNAME
        //=================================================

        if (section.CompareNoCase(_T("JOBNAME")) == 0)
        {
            if (key == "runname")
            {
                input.JOBNAME.runname =
                    TrimQuote(value);
            }
            else if (key == "para_dir")
            {
                input.JOBNAME.para_dir =
                    TrimQuote(value);
            }
            else if (key == "data_dir")
            {
                input.JOBNAME.data_dir =
                    TrimQuote(value);
            }
            else if (key == "result1_dir")
            {
                input.JOBNAME.result1_dir =
                    TrimQuote(value);
            }
            else if (key == "result2_dir")
            {
                input.JOBNAME.result2_dir =
                    TrimQuote(value);
            }
            else if (key == "simulation_dir")
            {
                input.JOBNAME.simulation_dir =
                    TrimQuote(value);
            }
            else if (key == "recv_dir")
            {
                input.JOBNAME.recv_dir =
                    TrimQuote(value);
            }
        }

        //=================================================
        // MODEL_MODE
        //=================================================

        else if (section.CompareNoCase(_T("MODEL_MODE")) == 0)
        {
            if (key == "RRI")
            {
                input.MODEL_MODE.RRI =
                    ParseBool(value);
            }
            else if (key == "MIXED")
            {
                input.MODEL_MODE.MIXED =
                    ParseBool(value);
            }
        }

        //=================================================
        // IN_BOUNDARY
        //=================================================

        else if (section.CompareNoCase(_T("IN_BOUNDARY")) == 0)
        {
            if (key == "IN_BOUND")
            {
                input.IN_BOUNDARY.IN_BOUND =
                    ParseBool(value);
            }
            else if (key == "IN_FILE")
            {
                input.IN_BOUNDARY.IN_FILE =
                    TrimQuote(value);
            }
            else if (key == "X_GRID")
            {
                input.IN_BOUNDARY.X_GRID =
                    _ttoi(value);
            }
            else if (key == "Y_GRID")
            {
                input.IN_BOUNDARY.Y_GRID =
                    _ttoi(value);
            }
        }

        //=================================================
        // TIMESTEP
        //=================================================

        else if (section.CompareNoCase(_T("TIMESTEP")) == 0)
        {
            if (key == "initime")
            {
                input.TIMESTEP.initime =
                    TrimQuote(value);
            }
            else if (key == "tstart")
            {
                input.TIMESTEP.tstart =
                    _ttoi(value);
            }
            else if (key == "tstop")
            {
                input.TIMESTEP.tstop =
                    _ttoi(value);
            }
            else if (key == "dt_couple")
            {
                input.TIMESTEP.dt_couple =
                    _ttoi(value);
            }
            else if (key == "dtlsm")
            {
                input.TIMESTEP.dtlsm =
                    _ttoi(value);
            }
            else if (key == "dthydro")
            {
                input.TIMESTEP.dthydro =
                    _ttoi(value);
            }
            else if (key == "recv_mode")
            {
                input.TIMESTEP.recv_mode =
                    _ttoi(value);
            }
        }

        //=================================================
        // POSITION
        //=================================================

        else if (section.CompareNoCase(_T("POSITION")) == 0)
        {
            if (key == "latsw")
            {
                input.POSITION.latsw =
                    _ttof(value);
            }
            else if (key == "latne")
            {
                input.POSITION.latne =
                    _ttof(value);
            }
            else if (key == "lonsw")
            {
                input.POSITION.lonsw =
                    _ttof(value);
            }
            else if (key == "lonne")
            {
                input.POSITION.lonne =
                    _ttof(value);
            }
            else if (key == "xsw")
            {
                input.POSITION.xsw =
                    _ttof(value);
            }
            else if (key == "xne")
            {
                input.POSITION.xne =
                    _ttof(value);
            }
            else if (key == "ysw")
            {
                input.POSITION.ysw =
                    _ttof(value);
            }
            else if (key == "yne")
            {
                input.POSITION.yne =
                    _ttof(value);
            }
        }

        //=================================================
        // GRID
        //=================================================

        else if (section.CompareNoCase(_T("GRID")) == 0)
        {
            if (key == "dx")
            {
                input.GRID.dx =
                    _ttof(value);
            }
            else if (key == "dy")
            {
                input.GRID.dy =
                    _ttof(value);
            }
            else if (key == "dzroot")
            {
                input.GRID.dzroot =
                    _ttof(value);
            }
            else if (key == "dzdeep")
            {
                input.GRID.dzdeep =
                    _ttof(value);
            }
        }

        //=================================================
        // MAPFILE
        //=================================================

        else if (section.CompareNoCase(_T("MAPFILE")) == 0)
        {
            if (key == "gridarea_map")
            {
                input.MAPFILE.gridarea_map =
                    TrimQuote(value);
            }
            else if (key == "elevation_map")
            {
                input.MAPFILE.elevation_map =
                    TrimQuote(value);
            }
            else if (key == "direction_map")
            {
                input.MAPFILE.direction_map =
                    TrimQuote(value);
            }
            else if (key == "accumulation_map")
            {
                input.MAPFILE.accumulation_map =
                    TrimQuote(value);
            }
            else if (key == "width_map")
            {
                input.MAPFILE.width_map =
                    TrimQuote(value);
            }
            else if (key == "depth_map")
            {
                input.MAPFILE.depth_map =
                    TrimQuote(value);
            }
            else if (key == "levee_map")
            {
                input.MAPFILE.levee_map =
                    TrimQuote(value);
            }
            else if (key == "slopelength_map")
            {
                input.MAPFILE.slopelength_map =
                    TrimQuote(value);
            }
            else if (key == "slopeangle_map")
            {
                input.MAPFILE.slopeangle_map =
                    TrimQuote(value);
            }
            else if (key == "soildepth_map")
            {
                input.MAPFILE.soildepth_map =
                    TrimQuote(value);
            }
            else if (key == "acquiferdepth_map")
            {
                input.MAPFILE.acquiferdepth_map =
                    TrimQuote(value);
            }
            else if (key == "zref_map")
            {
                input.MAPFILE.zref_map =
                    TrimQuote(value);
            }
            else if (key == "met_alt_map")
            {
                input.MAPFILE.met_alt_map =
                    TrimQuote(value);
            }
            else if (key == "land_map")
            {
                input.MAPFILE.land_map =
                    TrimQuote(value);
            }
            else if (key == "soil_map")
            {
                input.MAPFILE.soil_map =
                    TrimQuote(value);
            }
            else if (key == "soil_code")
            {
                input.MAPFILE.soil_code =
                    TrimQuote(value);
            }
            else if (key == "soil_table")
            {
                input.MAPFILE.soil_table =
                    TrimQuote(value);
            }
            else if (key == "met_map")
            {
                input.MAPFILE.met_map =
                    TrimQuote(value);
            }
        }

        //=================================================
        // TOPOGRAPHY
        //=================================================

        else if (section.CompareNoCase(_T("TOPOGRAPHY")) == 0)
        {
            if (key == "ele0")
            {
                input.TOPOGRAPHY.ele0 =
                    _ttof(value);
            }
            else if (key == "slope0")
            {
                input.TOPOGRAPHY.slope0 =
                    _ttof(value);
            }
            else if (key == "length0")
            {
                input.TOPOGRAPHY.length0 =
                    _ttof(value);
            }
            else if (key == "Ds0")
            {
                input.TOPOGRAPHY.Ds0 =
                    _ttof(value);
            }
            else if (key == "deldpth")
            {
                input.TOPOGRAPHY.deldpth =
                    _ttof(value);
            }
            else if (key == "zwind0")
            {
                input.TOPOGRAPHY.zwind0 =
                    _ttof(value);
            }
        }

        //=================================================
        // INITSOIL
        //=================================================

        else if (section.CompareNoCase(_T("INITSOIL")) == 0)
        {
            if (key == "sfcdat")
            {
                input.INITSOIL.sfcdat =
                    _ttoi(value);
            }
            else if (key == "vegfromtype")
            {
                input.INITSOIL.vegfromtype =
                    _ttoi(value);
            }
            else if (key == "styp")
            {
                input.INITSOIL.styp =
                    _ttoi(value);
            }
            else if (key == "vtyp")
            {
                input.INITSOIL.vtyp =
                    _ttoi(value);
            }
        }

        //=================================================
        // LSMMODEL
        //=================================================

        else if (section.CompareNoCase(_T("LSMMODEL")) == 0)
        {
            if (key == "rstopt")
            {
                input.LSMMODEL.rstopt =
                    _ttoi(value);
            }
        }

        //=================================================
        // MISC
        //=================================================

        else if (section.CompareNoCase(_T("MISC")) == 0)
        {
            if (key == "SSTMAX_CALIB")
            {
                input.MISC.SSTMAX_CALIB =
                    _ttof(value);
            }
            else if (key == "KSAT1_CALIB")
            {
                input.MISC.KSAT1_CALIB =
                    _ttof(value);
            }
            else if (key == "KSAT2_CALIB")
            {
                input.MISC.KSAT2_CALIB =
                    _ttof(value);
            }
        }

        //=================================================
        // INPUT
        //=================================================

        else if (section.CompareNoCase(_T("INPUT")) == 0)
        {
            if (key == "READ_REL_HUM")
            {
                input.INPUT.READ_REL_HUM =
                    ParseBool(value);
            }
            else if (key == "UPD_PSFC")
            {
                input.INPUT.UPD_PSFC =
                    ParseBool(value);
            }
            else if (key == "UPD_TAIR")
            {
                input.INPUT.UPD_TAIR =
                    ParseBool(value);
            }
            else if (key == "READ_SEPARATE_U_V")
            {
                input.INPUT.READ_SEPARATE_U_V =
                    ParseBool(value);
            }
            else if (key == "PREFIXES")
            {
                input.INPUT.PREFIXES =
                    TrimQuote(value);
            }
            else if (key == "PREFIX_RAIN")
            {
                input.INPUT.PREFIX_RAIN =
                    TrimQuote(value);
            }
            else if (key == "METEO_INPUT_TYPE")
            {
                input.INPUT.METEO_INPUT_TYPE =
                    _ttoi(value);
            }
            else if (key == "RAINFALL_INPUT_TYPE")
            {
                input.INPUT.RAINFALL_INPUT_TYPE =
                    _ttoi(value);
            }
            else if (key == "MONTHLY_LAIFPAR")
            {
                input.INPUT.MONTHLY_LAIFPAR =
                    ParseBool(value);
            }
        }

        //=================================================
        // OUTPUT
        //=================================================

        else if (section.CompareNoCase(_T("OUTPUT")) == 0)
        {
            if (key == "OUT1_CODESTART")
            {
                input.OUTPUT.OUT1_CODESTART =
                    _ttoi(value);
            }
            else if (key == "OUT1_CODEEND")
            {
                input.OUTPUT.OUT1_CODEEND =
                    _ttoi(value);
            }
            else if (key == "OUT1_FLOWINT")
            {
                input.OUTPUT.OUT1_FLOWINT =
                    _ttoi(value);
            }
        }

        //=================================================
        // debugging
        //=================================================

        else if (section.CompareNoCase(_T("debugging")) == 0)
        {
            if (key == "POINTSCALE_I")
            {
                input.DEBUGGING.POINTSCALE_I =
                    _ttoi(value);
            }
            else if (key == "POINTSCALE_J")
            {
                input.DEBUGGING.POINTSCALE_J =
                    _ttoi(value);
            }
        }

        //=================================================
        // snow
        //=================================================

        else if (section.CompareNoCase(_T("snow")) == 0)
        {
            if (key == "TH_SNOW")
            {
                input.SNOW.TH_SNOW =
                    _ttof(value);
            }
        }

        //=================================================
        // bats
        //=================================================

        else if (section.CompareNoCase(_T("bats")) == 0)
        {
            if (key == "TH_SNOW")
            {
                input.BATS.TH_SNOW =
                    _ttof(value);
            }
            else if (key == "visalbedo")
            {
                input.BATS.visalbedo =
                    _ttof(value);
            }
            else if (key == "niralbedo")
            {
                input.BATS.niralbedo =
                    _ttof(value);
            }
        }

        //=================================================
        // dam_control
        //=================================================

        else if (section.CompareNoCase(_T("dam_control")) == 0)
        {
            if (key == "dam_switch")
            {
                input.DAM_CONTROL.dam_switch =
                    _ttoi(value);
            }
            else if (key == "damfile")
            {
                input.DAM_CONTROL.damfile =
                    TrimQuote(value);
            }
        }
    }

    return TRUE;
}
