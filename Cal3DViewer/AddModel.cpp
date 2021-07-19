//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


// AddModel.cpp : implementation file

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "AddModel.h"


// CAddModel dialog

IMPLEMENT_DYNAMIC(CAddModel, CDialog)

CAddModel::CAddModel(CWnd* pParent /*=NULL*/)
	: CDialog(CAddModel::IDD, pParent)
	, m_strModelName(_T(""))
	, m_strNameInList(_T("") )
	, m_strBitmapName( _T("") )
{

}

CAddModel::~CAddModel()
{
}

void CAddModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_modelName);
	DDX_Control(pDX, IDC_OPENMODEL, m_OpenModel);
	DDX_Control(pDX, IDC_EDIT2, m_bitmapName);
	DDX_Control(pDX, IDC_EDIT3, m_nameInList);
	DDX_Control(pDX, IDC_OK, m_ok);
}


BEGIN_MESSAGE_MAP(CAddModel, CDialog)
	ON_BN_CLICKED(IDC_OK, &CAddModel::OnBnClickedOK)
	ON_BN_CLICKED(IDC_OPENMODEL, &CAddModel::OnBnClickedOpenModel)
	ON_BN_CLICKED(IDC_OPENBMP, &CAddModel::OnBnClickedOpenbmp)
	ON_EN_CHANGE(IDC_EDIT3, &CAddModel::OnEnChangeEdit3)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT1, &CAddModel::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CAddModel message handlers

void CAddModel::OnBnClickedOpenModel()
{
 
   // Create an Open dialog; the default file name extension is ".cfg".
	CFileDialog m_dlgOpen(true, _T("*.cfg"), _T("your cfg file"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("CFG files (*.cfg)|*.cfg||") );

	if( IDOK == m_dlgOpen.DoModal() )
	{
		m_strModelName = (CStringW)m_dlgOpen.GetFileName();
		m_strPureModelName = m_dlgOpen.GetFileTitle();
		m_modelName.SetWindowTextW( m_strModelName );
	}
	
}

void CAddModel::OnBnClickedOK()
{
	if( m_strNameInList != _T("") && m_strModelName != _T("") )
		OnOK();
	else
		AfxMessageBox( _T("Both cfg file and model name are required") );
}


void CAddModel::OnBnClickedOpenbmp()
{
    // Create an Open dialog; the default file name extension is ".bmp".
	CFileDialog m_dlgOpen(TRUE, _T("*.bmp"), _T("your bmp file"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Bitmap files (*.bmp)|*.bmp||"), NULL, NULL);

	if( m_dlgOpen.DoModal() == IDOK )
	{
		m_strBitmapName =  m_dlgOpen.GetFileName();
		m_bitmapName.SetWindowTextW(  m_strBitmapName );
	}
}

void CAddModel::OnEnChangeEdit3()
{
	m_nameInList.GetWindowTextW( m_strNameInList );
	//The bitmap file is not required
}

void CAddModel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );
	CDialog::OnLButtonDown(nFlags, point);
}

void CAddModel::OnEnChangeEdit1()
{
	m_modelName.GetWindowTextW( m_strModelName );
	//The bitmap file is not required
}
