//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


// Cal3DViewer.h : main header file for the "Cal3DViewr for Windows" application


#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Cal3DViewerDlg.h"
// CCal3DViewerApp:
// See Cal3DViewer.cpp for the implementation of this class
//

class CCal3DViewerApp : public CWinApp
{
public:
	CCal3DViewerApp();
	CCal3DViewerDlg dlg;

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

};

extern CCal3DViewerApp theApp;