//////////////////////////////////////////////////////////////////////////////////////////
// 
//      Art&Science  Standerd Main Library Header 
//
//													Update  2011/6
//
//////////////////////////////////////////////////////////////////////////////////////////
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
#pragma once

#include	"stdafx.h"
#include	"stdlib.h"
#include	"stdio.h"
#include	"io.h"
#include	"fcntl.h"
#include	"io.h"
#include	"SYS\STAT.H "
#include	"math.h"
//
//  プログラムの性格定義
//
#define		_USE_SDI			////   ＳＤＩ使用
//#define		_USE_DIALOG			////   ダイアログ使用
// ボタン色の変更
//#define		_USE_COLOR_DIALOG	//// カラーダイアログを使用
//
#define		_USE_CDC			//// ＣＤＣコントロールを使用
//
//
#define		_USE_IMAGE			////   イメージ操作を使用
#define		_USE_JPEG			////   ＪＰＥＧライブラリーを使用
//
//
//#define		_USE_OBJECT
//
//#define		_USE_DX				////   ＤＩＲＥＣＴ＿Ｘを使用
//
#define		_USE_OPENGL			////   ＯＰＥＮ＿ＧＬを使用
//
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//////////////////////////////////////////////////////////////////////////////////////////
// ド	440
// レ	494	
// ミ	554
// ファ	587
// ソ	659
// ラ	740
// シ	830
// ド	880
//
#ifdef  _USE_SDI
#define		RETURN(x)		{SB->SetPaneText(0,x,TRUE);return;}
#define		ERR_RETURN(x)		{Beep(494,100);Beep(850,100);SB->SetPaneText(0,x,TRUE);return;}
#define		COMMENT(x)			SB->SetPaneText(0,x,TRUE)
#define		ERR_COMMENT(x)	{Beep(494,100);Beep(850,100);SB->SetPaneText(0,x,TRUE);}
#define		NON_COMMENT(x)	;
//

#else

#define		RETURN(x)		m_Comment=x;UDF;return;
#define		COMMENT(x)		m_Comment=x;UDF;
#define		NON_COMMENT(x)		;
#endif
////
////□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
////////////////////////////////////////////////////////////////////////////////////////////
/////    オブジェクトレイヤー
//#define		MAX_OBJECT				15
//#define		OBJID_SEARCH_AREA			8
////------------------------------------------------------------- for APPLICATION LAYER
//#define		OBJID_BACK				0			// ガイドのＡＣＣ図、バックイメージ
//#define		OBJID_MESH				2			// メイン Make_Mesh_Modelで作成
//#define		OBJID_LINE				6			// メッシュライン
//#define		OBJID_AREA				1			// 矩形領域
//#define		OBJID_EDIT				3			// エディタのデータ表示
/////
//#define		OBJID_TS					7			// 降雨、蒸発散量の累加値 メッシュが異なるため
//#define		OBJID_SELECT				5			// Selected Lines or Meshes
////
//#define		OBJID_GROUND_OBS			4			//　地上観測所
////
//#define		OBJID_COPYRIGHT			8
///// --------------------------------------------------- 2Dim
////
//#define		OBJID_TOOL				10			// SCREEN TOOL 2_DIM
//#define		OBJID_LEGEND				11
///// ------------------------------------------------------------- for Time Char & Legend
////
//#define		OBJID_WORK				12			// 川の赤メッシュ、
//#define		OBJID_PROG_WORK			13
//#define		OBJID_MOUSE_BAND			14
////------------------------------------------------------------- for Csection or Cprofile
/////
//// ////////////////////////////////////////////////////////////////////////////////////////
/////========================================================================================
////
/////   ＢＯＯＬＩＡＮ
//#define		MAX_BOOLEAN				50				// 指定
////
//// Reserved for Mouse & KeyBoard
////
//#define		IS_READY					0
//#define		MS_LB_DOWN				1
//#define		MS_RB_DOWN				2
////
//#define		MS_MOVE_START				4
//#define		MS_RUBBER_START			5
////
//#define		KEY_CTRL_DOWN				7
//#define		KEY_SHIFT_DOWN			8
//#define		KEY_ALT_DOWN				9
////
//// Reserved for Viewing
////
//#define		SET_WORLD_VIEW			10
//#define		IS_PERSPECTIVE			11
////
//// Render Contorol
//#define		REDRAW					12
//#define		RELIST					13		// GLobj ごとに指定
//#define		REVIEW					14
//#define		RESET_ATTR				15
////
//// Reserved for Setting
////
//#define		USE_FONT					18
//#define		USE_LIGHT				19
////---------------------------------------------------------- Program Setting
//// 
//#define		ON_SCREEN				20
////---------------------------------------------------------- PROCESS STEP
//#define		PROC_INDICATE_RIVMESH		22		// 河川メッシュの指示
//#define		PROC_DISPLAY_MESH			23		// 範囲の表示
//#define		PROC_CONFIRM_MESH			24		// 範囲の確定、メッシュ作成
//
//#define		USE_EXTERNAL_DEM			25		// 
//#define		READ_ADEM_ONLY			26		// MAKE DIR and ACC の前
//#define		DEFINE_BASIN				27		// ADEMを読み、３ファイルを決定した後、
//
//#define		EDIT_RIV_MODE				29		// RIV.txt の編集モード
//
//#define		AREA_DECIDE_MODE			30		// メッシュ範囲の決定
//#define		ADD_MESH_MODE				31		// メッシュ範囲の追加モード
//#define		DEL_MESH_MODE				32		// メッシュ範囲の削除モード
//
//#define		RIVER_SELECT_MODE			33
//
//#define		SET_PERIOD				34
////
////---------------------------------------------------------- Display Windows
//#define		DISP_EDITWIN				40
//#define		DISP_BREAKTIME			41
////
////----------------------------------------------------------  
//#define		USE_OSM_IMAGE				44
////
////---------------------------------------------------------- 
//#define		MOVE_SCREEN_TOOL			45
//#define		MOVE_LEGEND				46
//
//#define		SHOW_COLORDATA			48

