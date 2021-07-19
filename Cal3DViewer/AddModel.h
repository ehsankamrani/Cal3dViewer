//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.

#pragma once
#include "afxwin.h"
#include "afxext.h"


// CAddModel dialog

class CAddModel : public CDialog
{
	DECLARE_DYNAMIC(CAddModel)

public:
	CAddModel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddModel();

// Dialog Data
	enum { IDD = IDD_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOK();

	// To get the address of the 3D model( We get the cfg file )
	CEdit m_modelName;

	// To open an open/close dialog
	CBitmapButton m_OpenModel;

	afx_msg void OnBnClickedOpenModel();

	// To hold the path of the model
	CStringW m_strModelName;

	afx_msg void OnBnClickedOpenbmp();

	CStringW m_strBitmapName;

	CEdit m_bitmapName;

	CStringW m_strNameInList;

	CEdit m_nameInList;

	afx_msg void OnEnChangeEdit3();

	// To hold the file name without its type( without .*** )
	CStringW m_strPureModelName;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnEnChangeEdit1();

	CButton m_ok;
};
