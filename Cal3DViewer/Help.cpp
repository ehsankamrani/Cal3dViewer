//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


// Help.cpp : implementation file

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "Help.h"


// CHelp dialog

IMPLEMENT_DYNAMIC(CHelp, CDialog)

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOSEHELP, m_btnClose);
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
	ON_BN_CLICKED(IDC_CLOSEHELP, &CHelp::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CHelp message handlers

void CHelp::OnBnClickedButton1()
{
	OnOK();
	// TODO: Add your control notification handler code here
}

int CHelp::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_btnClose.LoadBitmaps( IDB_CLOSEUP, IDB_CLOSEDOWN );
	m_btnClose.SizeToContent();

	return 0;
}

void CHelp::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
  				  MAKEINTRESOURCE(IDC_MOVE));
	SetCursor( m_hCurrentCursor );
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );

	CDialog::OnLButtonDown(nFlags, point);
}
