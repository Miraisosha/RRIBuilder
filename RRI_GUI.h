
// RRI_GUI.h : RRI_GUI アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include     "As_Mode.h"
#define		VER_64		// 64bit Compile 
///___________________________________________________________________


// CRRI_GUIApp:
// このクラスの実装については、RRI_GUI.cpp を参照してください。
//

class CRRI_GUIApp : public CWinApp
{
public:
	CRRI_GUIApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRRI_GUIApp theApp;
