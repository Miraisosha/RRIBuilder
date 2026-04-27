// AsEdit.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RRI_GUI.h"
#include "AsEdit.h"
#include "RRI_Common.h"


// CAsEdit

IMPLEMENT_DYNAMIC(CAsEdit, CEdit)

CAsEdit::CAsEdit()
{

}

CAsEdit::~CAsEdit()
{
}


BEGIN_MESSAGE_MAP(CAsEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CAsEdit::OnEnChange)
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// ボタンをCCOLButtonアタッチにする
//---------------------------------------------------------------
BOOL CAsEdit::AutoLoad(const UINT nID, CWnd* pParent)
{
	if (!SubclassDlgItem(nID, pParent)) return false;
	return true;
}
//---------------------------------------------------------------
void CAsEdit::OnEnChange()
{
		UDT; memset((void*)Text, 0, 512);
		this->GetWindowTextA(Text, 512);
		return;
}


void CAsEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	WPARAM  wptr = (UINT_PTR)&finfo;
	pP->SendMessage(WM_ASEDIT_FOCUS, wptr, NULL);
	//

}
void		CAsEdit::Set_Value(CString str, int flag)
{
	Col_Flag = flag;
	this->SetWindowTextA(str);
}



HBRUSH CAsEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);

	if (Col_Flag == 0) return hbr;
	else if (Col_Flag == 1) pDC->SetBkColor(RGB(255, 255, 255));
	else if (Col_Flag == 2) pDC->SetBkColor(RGB(200, 255, 255));
	else                  pDC->SetBkColor(RGB(255, 200, 200));
	return hbr;
}
