//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


#pragma once
#include "afxext.h"


// CHelp dialog

class CHelp : public CDialog
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHelp();

// Dialog Data
	enum { IDD = IDD_HELP};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_btnClose;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	HCURSOR m_hCurrentCursor;
};
