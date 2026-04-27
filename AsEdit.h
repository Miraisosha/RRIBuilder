#pragma once
#include  "RRI_Common.h"

#ifndef  _FOCUSINFO
#define	_FOCUSINFO
typedef  struct _FOCUSINFO {
	int		kind;
	int     x, y;
}FOCUSINFO;
#endif

// CAsEdit

class CAsEdit : public CEdit
{
	DECLARE_DYNAMIC(CAsEdit)

public:
	CAsEdit();
	virtual ~CAsEdit();
	//
	int	Col_Flag;
	// ÉÅÉìÉoä÷êî
	BOOL	AutoLoad(const UINT nID, CWnd* pParent);	// 

	void		Set_Value(CString str, int flag);
	//
	CWnd*		pP;
	FOCUSINFO	finfo;
	int			ID;
	// 
	char		Text[512];
protected:
	DECLARE_MESSAGE_MAP()
public:
protected:
public:
	afx_msg void OnEnChange();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


