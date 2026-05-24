#include "stdafx.h"
#include "ProjectUtil.h"

#include <filesystem>

namespace fs = std::filesystem;

BOOL CopyTemplateFolder(
	const CString& src,
	const CString& dst
)
{
	try
	{
		fs::path srcPath((LPCTSTR)src);
		fs::path dstPath((LPCTSTR)dst);

		fs::create_directories(dstPath);

		fs::copy(
			srcPath,
			dstPath,
			fs::copy_options::recursive |
			fs::copy_options::overwrite_existing
		);

		return TRUE;
	}
	catch (std::exception& e)
	{
		AfxMessageBox(CString(e.what()));

		return FALSE;
	}
}

CString GetExeFolder()
{
	TCHAR path[MAX_PATH];

	GetModuleFileName(NULL, path, MAX_PATH);

	CString exePath = path;

	int pos = exePath.ReverseFind('\\');

	if (pos >= 0)
	{
		exePath = exePath.Left(pos);
	}

	return exePath;
}

BOOL CheckProjectStructure(
	const CString& templatePath,
	const CString& projectPath,
	CString& errorMsg
)
{
	try
	{
		fs::path templateRoot((LPCTSTR)templatePath);
		fs::path projectRoot((LPCTSTR)projectPath);

		for (const auto& entry :
			fs::recursive_directory_iterator(templateRoot))
		{
			if (!entry.is_directory())
			{
				continue;
			}

			fs::path relPath =
				fs::relative(entry.path(), templateRoot);

			fs::path targetPath =
				projectRoot / relPath;

			if (!fs::exists(targetPath))
			{
				errorMsg +=
					CString(targetPath.wstring().c_str());

				errorMsg += _T("\r\n");
			}
		}

		return errorMsg.IsEmpty();
	}
	catch (std::exception& e)
	{
		errorMsg = e.what();

		return FALSE;
	}
}

BOOL CheckInputFile(
	const CString& projectPath,
	CString& inputPath
)
{
	fs::path proj((LPCTSTR)projectPath);

	fs::path input =
		proj /
		"SIMU" /
		"input.txt";

	if (!fs::exists(input))
	{
		return FALSE;
	}

	inputPath =
		CString(input.wstring().c_str());

	return TRUE;
}
