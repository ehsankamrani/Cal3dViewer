#pragma once
#include "afxwin.h"


// CRecommendedSoftware dialog

class CRecommendedSoftware : public CDialog
{
	DECLARE_DYNAMIC(CRecommendedSoftware)

public:
	CRecommendedSoftware(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecommendedSoftware();

// Dialog Data
	enum { IDD = IDD_DIALOG_REOMMENDED_SOFTWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkBox;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
