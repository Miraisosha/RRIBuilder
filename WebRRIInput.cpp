
#include "stdafx.h"

#include "WebRRIInput.h"

#include <fstream>
#include <string>

#include <tchar.h>

//=========================================================
// Utility
//=========================================================

static BOOL ParseBool(CString str)
{
	str.Trim();

	str.MakeLower();

	return
		(str == ".true.") ||
		(str == "true");
}

//---------------------------------------------------------

static CString TrimQuote(CString str)
{
	str.Trim();

	str.Replace("'", "");

	return str;
}

//=========================================================
// Load WEB-RRI input.txt
//=========================================================

BOOL LoadWebRRIInput(
	const CString& path,
	WEB_RRI_INPUT& input
)
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

		if (str.IsEmpty())
		{
			continue;
		}

		//-------------------------------------------------
		// comment
		//-------------------------------------------------

		if (str[0] == '!')
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

		if (section == "JOBNAME")
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

		else if (section == "MODEL_MODE")
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

		else if (section == "IN_BOUNDARY")
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

		else if (section == "TIMESTEP")
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

		else if (section == "POSITION")
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

		else if (section == "GRID")
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

		else if (section == "MAPFILE")
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
		}
	}

	return TRUE;
}
