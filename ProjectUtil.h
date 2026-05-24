#pragma once

#define CREATE_RRI_NEW      1
#define CREATE_RRI_LOAD     2
#define CREATE_WEB_RRI_NEW      3
#define CREATE_WEB_RRI_LOAD     4

BOOL CopyTemplateFolder(
	const CString& src,
	const CString& dst
);

BOOL CheckProjectStructure(
	const CString& templatePath,
	const CString& projectPath,
	CString& errorMsg
);

CString GetExeFolder();

BOOL CheckInputFile(
	const CString& projectPath,
	CString& inputPath
);