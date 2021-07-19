// RecommendedSoftware.cpp : implementation file
//

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "RecommendedSoftware.h"
#include "afxdialogex.h"


// CRecommendedSoftware dialog

IMPLEMENT_DYNAMIC(CRecommendedSoftware, CDialog)

CRecommendedSoftware::CRecommendedSoftware(CWnd* pParent /*=NULL*/)
	: CDialog(CRecommendedSoftware::IDD, pParent)
{

}

CRecommendedSoftware::~CRecommendedSoftware()
{
}

void CRecommendedSoftware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK, m_checkBox);
}


BEGIN_MESSAGE_MAP(CRecommendedSoftware, CDialog)
	ON_BN_CLICKED(IDOK, &CRecommendedSoftware::OnBnClickedOk)
END_MESSAGE_MAP()


// CRecommendedSoftware message handlers


void CRecommendedSoftware::OnBnClickedOk()
{
	FILE* file;
	file = fopen("recommendedSoftware.rsf", "wb");
	int check = m_checkBox.GetCheck();
	if (check == BST_CHECKED)
	{
		check = true;
	}
	else
	{
		check = false;
	}

	fwrite(&check, sizeof(bool), 1, file);
	fclose(file);

	CDialog::OnOK();
}


BOOL CRecommendedSoftware::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_checkBox.SetCheck(BST_UNCHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
