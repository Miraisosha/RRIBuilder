#pragma once
//
//  プログラムの性格定義
//
//　~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define		VER_64					// 64bit Compile 
// """""""""""" 
#define		_USE_SDI							////   ＳＤＩ使用
//　#define		_USE_VIEWER_FUNC			////  VIEWER  用 の拡張関数を使用する。
//__________________________________________________________________
//
#ifdef  _USE_SDI
	#define		RETURN(x)		{SB->SetPaneText(0,x,TRUE);return;}
	#define		ERR_RETURN(x)		{Beep(494,100);Beep(850,100);SB->SetPaneText(0,x,TRUE);return;}
	#define		COMMENT(x)		{SB->SetPaneText(0,x,TRUE);}
	#define		ERR_COMMENT(x)	{Beep(494,100);Beep(850,100);SB->SetPaneText(0,x,TRUE);}
#else
	#define		RETURN(x)		{m_Comment=x;UDF;return;}
	#define		COMMENT(x)		{m_Comment=x;UDF;}
	#define		NON_COMMENT(x)		;
#endif
////
//
#ifndef		_STATMENTG
	#define		_STATMENTG

	#define		STAT(i)					Gp.State[i]
	#define		pSTAT(i)				Gp->State[i]
	#define		IF_STAT(i)				if( Gp.State[i] )
	#define		IF_pSTAT(i)				if( Gp->State[i] )
	#define		IFNOT_STAT(i)			if( !Gp.State[i] )
	#define		IFNOT_pSTAT(i)			if( !Gp->State[i] )
	//

	//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
	//////////////////////////////////////////////////////////////////////////////////////////
	///    オブジェクトレイヤー
	#define		MAX_OBJECT				19
	#define		OBJID_SEARCH_AREA		8
	//------------------------------------------------------------- for APPLICATION LAYER
	#define		OBJID_BACK				0			// バックイメージ Make_Back_Image()

	#define		OBJID_GUIDE				1			// ガイドのＡＣＣ図  Show_Init_Guide()

	#define		OBJID_AREA				2			// 矩形領域 Make_Mesh_Area();Change_Area()

	#define		OBJID_MESH				3			// Make_Mesh_Model();Make_Mesh_Model_Init

	#define		OBJID_ARROW				4			// Adir 編集用

	#define		OBJID_EDIT				5			// エディタのデータ表示 Save_Manager()
													// Make_Edit_Riv();  Edit_Mesh_Model()

	#define		OBJID_GROUND_OBS		6			//　地上観測所 Make_GROUND_OBS();

	#define		OBJID_SELECT			7			// Disp_Select_RivMesh(); Make_Select_Pos()
													// Selected Lines or Meshes

	#define		OBJID_LINE				8			// Make_Mesh_Line(); メッシュライン
	///
	#define		OBJID_TS				9			// 降雨、蒸発散量の累加値 メッシュが異なるため
	//
	#define		OBJID_EDIT_ARROW		10
	/// --------------------------------------------------- 2Dim
	//
	#define		OBJID_COPYRIGHT			12
	#define		OBJID_TOOL				13			// SCREEN TOOL 2_DIM
	#define		OBJID_LEGEND			14
	/// ------------------------------------------------------------- for Time Char & Legend
	//
	#define		OBJID_WORK				15			// 川の赤メッシュ、Disp_River_Pos(BOOL  Add)
													// Del_River_Pos(BOOL Add);OnBnClickedButton103()

	#define		OBJID_PROG_WORK			16
	#define		OBJID_MOUSE_BAND		17
	#define		OBJID_SED				18
	//------------------------------------------------------------- for Csection or Cprofile
	///
	// ////////////////////////////////////////////////////////////////////////////////////////
	///========================================================================================
	//
	///   ＢＯＯＬＩＡＮ
	#define		MAX_BOOLEAN				60				// 指定
	//
	// Reserved for Mouse & KeyBoard
	//
	#define		IS_READY				0
	#define		MS_LB_DOWN				1
	#define		MS_RB_DOWN				2
	//
	#define		MS_MOVE_START			4
	#define		MS_RUBBER_START			5
	//
	#define		KEY_CTRL_DOWN			7
	#define		KEY_SHIFT_DOWN			8
	#define		KEY_ALT_DOWN			9
	//
	// Reserved for Viewing
	//
	#define		SET_WORLD_VIEW			10
	#define		IS_PERSPECTIVE			11
	//
	// Render Contorol
	#define		REDRAW					12
	#define		RELIST					13		// GLobj ごとに指定
	#define		REVIEW					14
	#define		RESET_ATTR				15
	//
	// Reserved for Setting
	//
	#define		USE_FONT				18
	#define		USE_LIGHT				19
	//---------------------------------------------------------- Program Setting
	// 
	#define		ON_SCREEN				20
	//---------------------------------------------------------- PROCESS STEP
	#define		PROC_INDICATE_RIVMESH	22		// 河川メッシュの指示
	#define		PROC_DISPLAY_MESH		23		// 範囲の表示
	#define		PROC_CONFIRM_MESH		24		// 範囲の確定、メッシュ作成

	#define		USE_EXTERNAL_DEM		25		// 
	#define		READ_ADEM_ONLY			26		// MAKE DIR and ACC の前
	#define		DEFINE_BASIN			27		// ADEMを読み、３ファイルを決定した後、

	#define		EDIT_RIV_MODE			29		// RIV.txt の編集モード

	#define		AREA_DECIDE_MODE		30		// メッシュ範囲の決定
	#define		ADD_MESH_MODE			31		// メッシュ範囲の追加モード
	#define		DEL_MESH_MODE			32		// メッシュ範囲の削除モード

	#define		RIVER_SELECT_MODE		33

	#define		SET_PERIOD				34
	//
	//---------------------------------------------------------- Display Windows
	#define		DISP_EDITWIN			40
	#define		DISP_BREAKTIME			41
	//
	//----------------------------------------------------------  
	#define		USE_OSM_IMAGE			44
	//
	//---------------------------------------------------------- 
	#define		MOVE_SCREEN_TOOL		45
	#define		MOVE_LEGEND				46
	#define		SHOW_COLORDATA			48
	//
	//----------------------------------------------------------Arrow
	#define		SET_ARROW				50
	#define		ENABLE_DRAW_ARROW		51
	#define		DISP_ARROW				52
	#define		CHANGE_DIRECTION		53
	#define		AVAIL_UNDO				55
	#define		AVAIL_RESET				56
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////
	//========================================================================================
	//
	//    GB オブジェクトレイヤー		
	//
	#ifdef _USE_VIEWER_FUNC
		#define		GB_MAX_OBJECT				20
		#define     GB_MAX_BOOLEAN				80
		#define		GB_OBJID_SEARCH_AREA		6
		//--------------------------------------

		#define		STATB(i)				GB.State[i]
		#define		pSTATB(i)				Gp->State[i]
		#define		IF_STATB(i)				if( GB.State[i] )
		#define		IF_pSTATB(i)			if( Gp->State[i] )
		#define		IFNOT_STATB(i)			if( !GB.State[i] )
		#define		IFNOT_pSTATB(i)			if( !Gp->State[i] )
			
		#define		STATG(i)				Gp.State[i]
		#define		pSTATG(i)				Gp->State[i]
		#define		IF_STATG(i)				if( Gp.State[i] )
		#define		IF_pSTATG(i)			if( Gp->State[i] )
		#define		IFNOT_STATG(i)			if( !Gp.State[i] )
		#define		IFNOT_pSTATG(i)			if( !Gp->State[i] )
		//
		///
		//
		//------------------------------------------------------------- for APPLICATION LAYER
		#define		OBJID_FIG_0					0
		#define		OBJID_FIG_1					1
		#define		OBJID_FIG_2					2
		#define		OBJID_FIG_3					3
		//------------------------------------------------------------- for PROGRAM
		#define		GB_OBJID_WORK				7
		#define		GB_OBJID_PROG_WORK			8
		#define		GB_OBJID_MOUSE_BAND			9
		//------------------------------------------------------------- for Csection or Cprofile
		//
	#else
		#define     GB_MAX_BOOLEAN				80
	#endif


	//integrate with new lib header
	// Following are the definitions in original CommFunc.h
	//

	///////////////////////////////////////////////////////////////////////////////////////
	//	ボタンコントロールの定義
	// 
	#ifdef		_USE_COLOR_DIALOG
	//
		#define		COLOR_DIALOG			RGB(35,35,40)
		#define		COLOR_DIALOG_TEXT		RGB(220,220,220)
		#define		COLOR_STATIC			RGB(105,105,115)
		#define		COLOR_STATIC_TEXT		RGB(220,220,220)
		#define		COLOR_EDIT				RGB(40,40,50)   //RGB(70,75,80)
		#define		COLOR_EDIT_BLUE			RGB(100,100,150)
		#define		COLOR_EDIT_TEXT			RGB(250,250,100)
		#define		COLOR_BTN				RGB(105,105,115)
		#define		COLOR_BTN_TEXT			RGB(255,255,0)

		#define		COLOR_TEXT_WHITE		RGB(215,215,215)
		#define		COLOR_TEXT_DISABLE		RGB(80,80,80)
		#define		COLOR_TEXT_BACK			RGB(190,190,200)
		//
		#define		COLOR_BUTTON_BK			RGB(70,75,80)
		#define		COLOR_BUTTON_BK_DIS		RGB(70,75,80)
		#define		COLOR_BUTTON_TEXT		RGB(255,255,0)
		#define		COLOR_BUTTON_TEXT_DIS	RGB(100,100,100)
	//
	#endif
#endif
