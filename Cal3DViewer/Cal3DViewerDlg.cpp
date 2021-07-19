//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.

// Cal3DViewerDlg.cpp : implementation file


#include "stdafx.h"
#include "Cal3DViewer.h"
#include "Cal3DViewerDlg.h"
#include <afxstr.h>
#include "afxext.h"
#include "afxwin.h"
#include "help.h"
#include "info.h"
#include "RecommendedSoftware.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()

// CCal3DViewerDlg dialog
CCal3DViewerDlg::CCal3DViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCal3DViewerDlg::IDD, pParent)
	, m_addModel(NULL)
	, m_numberOfDataElements(0)
	, m_isDraft(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_addModel = new CAddModel;
}

void CCal3DViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_ROTATE, m_btnRotate);
	DDX_Control(pDX, IDC_INTERACTIVE, m_btnInteractive);
	DDX_Control(pDX, IDC_INFO, m_btnInfo);
	DDX_Control(pDX, IDC_MYHELP, m_btnHelp);
	DDX_Control(pDX, IDC_LIST1, m_lstCtrlNames);
	DDX_Control(pDX, IDC_PHOTO, m_imgCtrl);
	DDX_Control(pDX, IDC_WHITEPOINTS, m_btnWhitePoints);
	DDX_Control(pDX, IDC_BONE, m_btnTexturedPoints);
	DDX_Control(pDX, IDC_WHITELINES, m_btnWhiteLines);
	DDX_Control(pDX, IDC_TEXTUREDLINES, m_btnTexturedLines);
	DDX_Control(pDX, IDC_SOLID, m_btnSolid);
	DDX_Control(pDX, IDC_ADDMODEL, m_btnAddModel);
	DDX_Control(pDX, IDC_HOME, m_btnHome);
	DDX_Control(pDX, IDC_REMOVEMODEL, m_btnRemoveModel);
	DDX_Control(pDX, IDC_MINIMIZE, m_btnMinimize);
	DDX_Control(pDX, IDC_SAVELIST, m_btnSaveData);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_NEXTANIMATION, m_btnNextAnim);
	DDX_Control(pDX, IDC_PREVANIMATION, m_btnPrevAnim);
	DDX_Control(pDX, IDC_ABOUT, m_btnAbout);
}

BEGIN_MESSAGE_MAP(CCal3DViewerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CLOSE, &CCal3DViewerDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_NEXT, &CCal3DViewerDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREV, &CCal3DViewerDlg::OnBnClickedPrev)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CCal3DViewerDlg::OnLvnKeydownList1)
	ON_BN_CLICKED(IDC_INTERACTIVE, &CCal3DViewerDlg::OnBnClickedInteractive)
	ON_BN_CLICKED(IDC_ROTATE, &CCal3DViewerDlg::OnBnClickedRotate)
	ON_BN_CLICKED(IDC_STOP, &CCal3DViewerDlg::OnBnClickedStop)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_WHITEPOINTS, &CCal3DViewerDlg::OnBnClickedWhitepoints)
	ON_BN_CLICKED(IDC_BONE, &CCal3DViewerDlg::OnBnClickedBone)
	ON_BN_CLICKED(IDC_WHITELINES, &CCal3DViewerDlg::OnBnClickedWhitelines)
	ON_BN_CLICKED(IDC_TEXTUREDLINES, &CCal3DViewerDlg::OnBnClickedTexturedlines)
	ON_BN_CLICKED(IDC_SOLID, &CCal3DViewerDlg::OnBnClickedSolid)
	ON_BN_CLICKED(IDC_ADDMODEL, &CCal3DViewerDlg::OnBnClickedAddModel )
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_HOME, &CCal3DViewerDlg::OnBnClickedHome)
	ON_BN_CLICKED(IDC_CLOSEHELP, &CCal3DViewerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_INFO, &CCal3DViewerDlg::OnBnClickedInfo)
	ON_WM_MBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_MINIMIZE, &CCal3DViewerDlg::OnBnClickedMinimize)
	ON_BN_CLICKED(IDC_REMOVEMODEL, &CCal3DViewerDlg::OnBnClickedRemovemodel)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCal3DViewerDlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCal3DViewerDlg::OnNMDblclkList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCal3DViewerDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_SAVELIST, &CCal3DViewerDlg::OnBnClickedSaveData)
	ON_BN_CLICKED(IDC_MYHELP, &CCal3DViewerDlg::OnBnClickedMyhelp)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)

	ON_BN_CLICKED(IDC_NEXTANIMATION, &CCal3DViewerDlg::OnBnClickedNextanimation)
	ON_BN_CLICKED(IDC_PREVANIMATION, &CCal3DViewerDlg::OnBnClickedPrevanimation)
	ON_BN_CLICKED(IDC_ABOUT, &CCal3DViewerDlg::OnBnClickedAbout)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CCal3DViewerDlg message handlers

BOOL CCal3DViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	
	SetWindowText(_T("Cal3D Viewer for windows"));

	//First of all load the data base
	bool isDatabase = LoadDataBase();
 	m_view.m_numberOfDataElements = m_numberOfDataElements = (int)m_array.GetSize();
	if( isDatabase )
	{
		//Insert the item names inside the list control
		InsertItemNames();
	}
	
	//Load the bitmaps of the buttons
	LoadBitmapButtons();

	//Initialize slider here
    m_slider.SetBitmapChannel( IDB_CHANNEL, IDB_CHANNEL_ACTIVE, FALSE );
    m_slider.SetBitmapThumb( IDB_THUMB, IDB_THUMB_ACTIVE, TRUE );
	m_slider.DrawFocusRect( FALSE );
    m_slider.SetRange( 0, 20 );
    m_slider.SetPos( 20 );

	//Intitialize OpenGL window
	CRect rcClient;
	GetClientRect( &rcClient );
	rcClient.DeflateRect( 7, 32, 207 , 46 );

	//Create the OpenGLw window here
	if (!m_view.Create(NULL, NULL, WS_BORDER | WS_VISIBLE | WS_CHILD , rcClient, this, 0))
	{
		PostQuitMessage(0);
		return FALSE;
	}
	GLenum err = glewInit();
	if( err != GLEW_OK )
		AfxMessageBox( _T("Couldn't initialize GLEW!") );
	
	else
	{
		m_view.DestroyWindow();
		m_view.m_IsMultiSampling = true;
		if (!m_view.Create(NULL, NULL, WS_BORDER | WS_VISIBLE | WS_CHILD , rcClient, this, 0))
		{
			m_view.DestroyWindow();
			m_view.m_IsMultiSampling = false;
			if (!m_view.Create(NULL, NULL, WS_BORDER | WS_VISIBLE | WS_CHILD  , rcClient, this, 0))
			{
				PostQuitMessage(0);
				return FALSE;
			}
		}
	}
	

	m_view.InitAll();

	//To get the information of the current model
	//I'm no sure that it's a correct way to access a member in another class
	//via a pointer,but it does work.
	//Initialize GLEW after we made the window
	infoDlg.m_pTo_m_view = &m_view;

	if( m_numberOfDataElements )
	{
		switch( m_view.GetAnimationCount() )
		{
		case 0:
		case 1:
			break;
		default:
			m_btnNextAnim.EnableWindow( TRUE );
			break;
		}
	}
	m_view.ShowWindow( SW_SHOW );

	FILE* file;
	file = fopen("recommendedSoftware.rsf", "rb");
	if (file)
	{
		bool check;
		fread(&check, sizeof(bool), 1, file);
		if (!check)
		{
			CRecommendedSoftware m_recommendedSoftware;
			m_recommendedSoftware.DoModal();
		}
	}
	else
	{
		file = fopen("recommendedSoftware.rsf", "wb");
		bool check = false;
		fwrite(&check, sizeof(bool), 1, file);
		CRecommendedSoftware m_recommendedSoftware;
		m_recommendedSoftware.DoModal();
	}



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCal3DViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCal3DViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCal3DViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCal3DViewerDlg::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here
	//If we haven't saved the changes
	if( m_isDraft )
	{
		int result;
		if( result = MessageBoxW( _T("Save changes?"), _T("Save..."), MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1 ) )
		{
			if( result == IDYES )
			{
				SaveDataBase();
				OnOK();
			}
			else if( result == IDNO )
					OnOK();
		}
	}
	else
		OnOK();
}

// To insert the names insed the list control, we don't get them from a dialog box, so we hardcode them
int CCal3DViewerDlg::InsertItemNames(void)
{
	if( m_numberOfDataElements )
	{
		m_SmallImage.Create(IDB_SMALLIMG, 16, 1, RGB(255, 255, 255)); 
		m_lstCtrlNames.SetImageList( &m_SmallImage, LVSIL_SMALL );

		CMemberData* m_currentData;
		for( int index = 0; index < m_numberOfDataElements; index++ )
		{
			m_currentData = reinterpret_cast<CMemberData*>(m_array[index]);

			lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
			lvItem.iItem = index;
			lvItem.iSubItem = 0;
			lvItem.iImage = 0;
			lvItem.pszText = (LPWSTR)(LPCWSTR)(m_currentData->m_nameInList);
			m_lstCtrlNames.InsertItem(&lvItem);
			m_lstCtrlNames.SetExtendedStyle( LVS_EX_INFOTIP
				| LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP | LVS_EX_GRIDLINES  );
			//load and Add the bitmaps here
			//Add a new bitmap
			CStringW s;
			HBITMAP hBitmap;
			bool m_failed = false;
			if( (m_currentData->m_bitmapPath) != _T("") )
			{
				s = _T("data/bitmaps/") + m_currentData->m_bitmapPath;
				hBitmap = (HBITMAP)LoadImage( NULL, s, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
				if( !hBitmap )
				{
	 				s = _T("data/bitmaps/default.bmp") ;
					m_failed = true;
				}
			}
			//if we failed to load the specified image or if the string hasn't been specified
			else if( m_failed ||  m_currentData->m_bitmapPath == _T("") )
			{
				s = _T("data/bitmaps/default.bmp") ;
				hBitmap = (HBITMAP)LoadImage( NULL, s, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
			}
			CBitmap* bmp = CBitmap::FromHandle( hBitmap );
			m_imgPhoto.push_back( bmp );
		}
	}
	//load the default image
	m_defaultImg.LoadBitmapW( IDB_DFLTIMG );
	return 0;
}

void CCal3DViewerDlg::LoadBitmapButtons(void)
{
	//Intialize the bitmap buttons here

	//Disable some windows 
	m_btnPrev.EnableWindow( FALSE );
	m_btnNext.EnableWindow( FALSE );
	m_btnStop.EnableWindow( FALSE );
	m_btnRotate.EnableWindow( FALSE );
	m_btnInteractive.EnableWindow( FALSE );
	m_btnNextAnim.EnableWindow( FALSE );
	m_btnPrevAnim.EnableWindow( FALSE );

	m_btnWhitePoints.EnableWindow( FALSE );
	m_btnTexturedPoints.EnableWindow( FALSE );
	m_btnWhiteLines.EnableWindow( FALSE );
	m_btnTexturedLines.EnableWindow( FALSE );
	m_btnSolid.EnableWindow( FALSE );
	m_btnHome.EnableWindow( FALSE );
	m_btnRemoveModel.EnableWindow( FALSE );
	m_btnSaveData.EnableWindow( FALSE );
	m_slider.ShowWindow( FALSE );

	if( m_numberOfDataElements >= 1 )
	{
		m_lstCtrlNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
		m_lstCtrlNames.EnsureVisible(0, FALSE);
		m_view.m_modelIndex = 0;

		m_view.m_IsInteractive = true;
		m_btnInteractive.EnableWindow( true );
		m_btnInteractive.SetFocus();

		if( m_numberOfDataElements != 1 )
			m_btnNext.EnableWindow( TRUE );

		m_btnRotate.EnableWindow( TRUE );

		m_btnWhitePoints.EnableWindow( TRUE );
		m_btnTexturedPoints.EnableWindow( TRUE );
		m_btnWhiteLines.EnableWindow( TRUE );
		m_btnTexturedLines.EnableWindow( TRUE );
		m_btnSolid.EnableWindow( TRUE );
		m_btnHome.EnableWindow( TRUE );
		m_btnRemoveModel.EnableWindow( TRUE );
		m_slider.ShowWindow( TRUE );
	}

	m_btnClose.LoadBitmaps( IDB_CLOSEUP, IDB_CLOSEDOWN );
	m_btnClose.SizeToContent();

	m_btnMinimize.LoadBitmaps(  IDB_MINIMIZEUP, IDB_MINIMIZEDOWN);
	m_btnMinimize.SizeToContent();

	m_btnNext.LoadBitmaps( IDB_NEXTUP, IDB_NEXTDOWN, IDB_NEXTF, IDB_NEXTDISABLE );
	m_btnNext.SizeToContent();

	m_btnPrev.LoadBitmaps( IDB_PREVUP, IDB_PREVDOWN, IDB_PREVF, IDB_PREVDISABLE );
	m_btnPrev.SizeToContent();

	m_btnStop.LoadBitmaps( IDB_STOPUP, IDB_STOPDOWN, IDB_STOPF, IDB_STOPDISABLE );
	m_btnStop.SizeToContent();

	m_btnRotate.LoadBitmaps( IDB_ROTATEUP, IDB_ROTATEDOWN, IDB_ROTATEF, IDB_ROTATEDISABLE );
	m_btnRotate.SizeToContent();

	m_btnInteractive.LoadBitmaps( IDB_INTERACTIVEUP, IDB_INTERACTIVEDOWN, IDB_INTERACTIVEF, IDB_INTERACTIVEDISABLE );
	m_btnInteractive.SizeToContent();
	if( m_numberOfDataElements )
		m_btnInteractive.SetFocus();

	m_btnHelp.LoadBitmaps( IDB_HELPUP, IDB_HELPDOWN, IDB_HELPDOWN );
	m_btnHelp.SizeToContent();

	m_btnInfo.LoadBitmaps( IDB_INFOUP, IDB_INFODOWN, IDB_INFODOWN );
	m_btnInfo.SizeToContent();

	m_btnAbout.LoadBitmaps( IDB_ABOUTUP, IDB_ABOUTDOWN, IDB_ABOUTDOWN );
	m_btnAbout.SizeToContent();

	//TODO----------------------------
	//Change the shape of these buttons later
	m_btnWhitePoints.LoadBitmaps(  IDB_WHITEPOINTUP, IDB_WHITEPOINTDOWN, IDB_WHITEPOINTF, IDB_WHITEPOINTDISABLE );
	m_btnWhitePoints.SizeToContent();

	m_btnTexturedPoints.LoadBitmaps(  IDB_TEXTUREDPOINTUP, IDB_TEXTUREDPOINTDOWN, IDB_TEXTUREDPOINTF, IDB_TEXTUREDPOINTDISABLE );
	m_btnTexturedPoints.SizeToContent();

	m_btnWhiteLines.LoadBitmaps(  IDB_WHITELINEUP, IDB_WHITELINEDOWN, IDB_WHITELINEF, IDB_WHITELINEDISABLE );
	m_btnWhiteLines.SizeToContent();

	m_btnTexturedLines.LoadBitmaps(  IDB_TEXTUREDLINEUP, IDB_TEXTUREDLINEDOWN, IDB_TEXTUREDLINEF,  IDB_TEXTUREDLINEDISABLE );
	m_btnTexturedLines.SizeToContent();

	m_btnSolid.LoadBitmaps(  IDB_SOLIDUP, IDB_SOLIDDOWN, IDB_SOLIDF, IDB_SOLIDDISABLE );
	m_btnSolid.SizeToContent();

	m_btnHome.LoadBitmaps(  IDB_HOMEUP, IDB_HOMEDOWN, IDB_HOMEF, IDB_HOMEDISABLE  );
	m_btnHome.SizeToContent();

	m_btnAddModel.LoadBitmaps(  IDB_ADDUP, IDB_ADDDOWN, IDB_ADDF );
	m_btnAddModel.SizeToContent();

	m_btnRemoveModel.LoadBitmaps(  IDB_DELETEUP, IDB_DELETEDOWN, IDB_DELETEF, IDB_DELETEDISABLE );
	m_btnRemoveModel.SizeToContent();

	m_btnSaveData.LoadBitmaps(  IDB_SAVEUP, IDB_SAVEDOWN, IDB_SAVEF, IDB_SAVEDISABLE );
	m_btnSaveData.SizeToContent();

	m_btnNextAnim.LoadBitmaps(  IDB_NEXTANIM_UP, IDB_NEXTANIM_DOWN, IDB_NEXTANIM_F, IDB_NEXTANIM_DISABLE );
	m_btnNextAnim.SizeToContent();

	m_btnPrevAnim.LoadBitmaps(  IDB_PREVANIM_UP, IDB_PREVANIM_DOWN, IDB_PREVANIM_F, IDB_PREVANIM_DISABLE );
	m_btnPrevAnim.SizeToContent();

	//-----------------------------------------------------------------
}

void CCal3DViewerDlg::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here
	if( ! m_view.NextObject() )
	{
		m_btnNext.EnableWindow( FALSE );

	}
	else
	{
		m_btnNext.EnableWindow( TRUE );
		//reset the object rotation
		m_view.m_Rotation.i = 0.0f;
	}

	if( m_view.IsModelValid( m_view.m_modelIndex ) )
	{
		m_view.m_nPos = 20;
		m_view.setLodLevel( (float)m_view.m_nPos / 20.0f );
		m_slider.SetPos( m_view.m_nPos );
		//prevAnim and NextAnim buttons
		switch ( m_view.GetAnimationCount() )
		{
		case 0: case 1:
			m_btnNextAnim.EnableWindow( FALSE );
			m_btnPrevAnim.EnableWindow( FALSE );
			break;
		default:
			m_btnNextAnim.EnableWindow( TRUE );
			m_btnPrevAnim.EnableWindow( FALSE );
		}
		//Reset the animation
		if( m_view.childModel[m_view.m_modelIndex]->GetAnimationCount() )
		{
			m_view.childModel[m_view.m_modelIndex]->clearCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 0.0f );
			m_view.childModel[m_view.m_modelIndex]->SetCurrentAnimationId( 0 );
			m_view.childModel[m_view.m_modelIndex]->blendCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 1.0f, 0.0f );
		}
	}
	else
	{
		//this model is not valid, so we can't show it and we can't show its animations and set its lod level
		m_slider.ShowWindow( FALSE );
		m_btnNextAnim.EnableWindow( FALSE );
		m_btnPrevAnim.EnableWindow( FALSE );
	}
	//Enable the Prev button
	m_btnPrev.EnableWindow( TRUE );
	m_lstCtrlNames.SetItemState(m_view.m_modelIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
	m_lstCtrlNames.EnsureVisible( m_view.m_modelIndex, FALSE );
}

void CCal3DViewerDlg::OnBnClickedPrev()
{
	// TODO: Add your control notification handler code here
	if( !m_view.PrevObject() )
	{
		m_btnPrev.EnableWindow( FALSE );
	}

	else
	{
		m_btnPrev.EnableWindow( TRUE );
		//reset the object rotation
		m_view.m_Rotation.i = 0.0f;
	}

	if( m_view.IsModelValid( m_view.m_modelIndex ) )
	{
		m_view.m_nPos = 20;
		m_view.setLodLevel( (float)m_view.m_nPos / 20.0f );
		m_slider.SetPos( m_view.m_nPos );
		m_slider.ShowWindow( TRUE );

		//prevAnim and NextAnim buttons
		switch ( m_view.GetAnimationCount() )
		{
		case 0: case 1:

			m_btnNextAnim.EnableWindow( FALSE );
			m_btnPrevAnim.EnableWindow( FALSE );
			break;
		default:
			m_btnNextAnim.EnableWindow( TRUE );
			m_btnPrevAnim.EnableWindow( FALSE );
		}
		//Reset the animation
		if( m_view.childModel[m_view.m_modelIndex]->GetAnimationCount() )
		{
			m_view.childModel[m_view.m_modelIndex]->clearCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 0.0f );
			m_view.childModel[m_view.m_modelIndex]->SetCurrentAnimationId( 0 );
			m_view.childModel[m_view.m_modelIndex]->blendCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 1.0f, 0.0f );
		}
	}
	else
	{
		//this model is not valid, so we can't show it and we can't show its animations and set its lod level
		m_slider.ShowWindow( FALSE );
		m_btnNextAnim.EnableWindow( FALSE );
		m_btnPrevAnim.EnableWindow( FALSE );
	}
	//Enable the next button
	m_btnNext.EnableWindow( TRUE );
	m_lstCtrlNames.SetItemState(m_view.m_modelIndex, LVIS_SELECTED, LVIS_SELECTED );
	m_lstCtrlNames.EnsureVisible( m_view.m_modelIndex, FALSE );
}

void CCal3DViewerDlg::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CCal3DViewerDlg::ChangeBitmaps(void)
{
	if( m_numberOfDataElements )
	{
		int nSelected = -1; 
		POSITION p = m_lstCtrlNames.GetFirstSelectedItemPosition();
		while(p)
		{
			nSelected = m_lstCtrlNames.GetNextSelectedItem(p);
		}
		if( nSelected >= 0 )
			m_imgCtrl.SetBitmap( (HBITMAP)*m_imgPhoto[nSelected] );
	}
	else
	{
		m_imgCtrl.SetBitmap( (HBITMAP)m_defaultImg );
	}
}

void CCal3DViewerDlg::ChangeModels(void)
{
	if( m_numberOfDataElements )
	{
		int nSelected = -1; 
		POSITION p = m_lstCtrlNames.GetFirstSelectedItemPosition();
		while( p )
		{
			nSelected = m_lstCtrlNames.GetNextSelectedItem(p);
		}

		if( nSelected >= 0 )
		{
			if( nSelected != m_numberOfDataElements - 1 )
				m_btnNext.EnableWindow( TRUE );
			else
				if( nSelected == m_numberOfDataElements - 1 )
					m_btnNext.EnableWindow( FALSE );
			if( nSelected != 0 )
				m_btnPrev.EnableWindow( TRUE );
			else
				if( nSelected == 0 )
					m_btnPrev.EnableWindow( FALSE );

			m_view.m_modelIndex = nSelected;
			if( m_view.IsModelValid(m_view.m_modelIndex) )
			{
				m_view.m_nPos = 20;
				m_slider.SetPos( m_view.m_nPos );
				m_slider.ShowWindow( TRUE );
		
				m_view.setLodLevel( float(m_view.m_nPos) / 20.0f );
				switch ( m_view.GetAnimationCount() )
				{
				case 0: case 1:
					m_btnNextAnim.EnableWindow( FALSE );
					m_btnPrevAnim.EnableWindow( FALSE );
					break;
				default:
					m_btnNextAnim.EnableWindow( TRUE );
					m_btnPrevAnim.EnableWindow( FALSE );
				}
				if( m_view.childModel[m_view.m_modelIndex]->GetAnimationCount() )
				{
					m_view.childModel[m_view.m_modelIndex]->clearCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 0.0f );
					m_view.childModel[m_view.m_modelIndex]->SetCurrentAnimationId( 0 );
					m_view.childModel[m_view.m_modelIndex]->blendCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 1.0f, 0.0f );
				}
			}
			else
			{
				//this model is not valid, so we can't get its animations and we can't set its lod level
				m_btnNextAnim.EnableWindow( FALSE );
				m_btnPrevAnim.EnableWindow( FALSE );
				m_slider.ShowWindow( FALSE );
			}
		}
	}
}

void CCal3DViewerDlg::OnBnClickedInteractive()
{
	// TODO: Add your control notification handler code here
	//Interactive button diables the roation and stop button
	m_view.m_enableRotation = false;
	m_view.m_IsInteractive = true;
	m_btnStop.EnableWindow( FALSE );
}

void CCal3DViewerDlg::OnBnClickedRotate()
{
	// TODO: Add your control notification handler code here
	//Enable rotation, reset the angle and enable the stop button
	m_view.m_enableRotation = true;
	m_view.m_IsInteractive = false;
	m_btnStop.EnableWindow( TRUE );
}

void CCal3DViewerDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	//Disable rotation here
	m_view.m_enableRotation = false;
}


HBRUSH CCal3DViewerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//// TODO:  Change any attributes of the DC here
	m_bkBrush.DeleteObject();
	m_bkBrush.CreateSolidBrush( RGB( 240, 240, 240 ) );

	switch( nCtlColor )
	{
	case CTLCOLOR_DLG:
		return static_cast<HBRUSH> ( m_bkBrush.GetSafeHandle() );
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CCal3DViewerDlg::OnBnClickedWhitepoints()
{
	// TODO: Add your control notification handler code here
	m_view.m_isLighting = false;
	m_view.m_isTextured = false;
	m_view.m_drawBone =false;
	m_view.m_DrawMode = GL_POINT;
}

void CCal3DViewerDlg::OnBnClickedBone()
{
	m_view.m_isLighting = false;
	m_view.m_drawBone =true;
	m_view.m_isTextured = false;
	m_view.m_DrawMode = GL_POINT;
}

void CCal3DViewerDlg::OnBnClickedWhitelines()
{
	// TODO: Add your control notification handler code here
	m_view.m_isLighting = false;
	m_view.m_isTextured = false;
	m_view.m_drawBone =false;
	m_view.m_DrawMode = GL_LINE;
}

void CCal3DViewerDlg::OnBnClickedTexturedlines()
{
	// TODO: Add your control notification handler code here
	m_view.m_isLighting = true;
	m_view.m_isTextured = true;
	m_view.m_drawBone =false;
	m_view.m_DrawMode = GL_LINE;
}

void CCal3DViewerDlg::OnBnClickedSolid()
{
	// TODO: Add your control notification handler code here
	m_view.m_isLighting = true;
	m_view.m_isTextured = true;
	m_view.m_drawBone =false;
	m_view.m_DrawMode = GL_FILL;
}

void CCal3DViewerDlg::OnBnClickedAddModel()
{
	// TODO: Add your control notification handler code here
	if( m_addModel->DoModal() == IDOK )
	{
		CStringW s(	_T("data/models/") + m_addModel->m_strPureModelName + _T("/") + m_addModel->m_strModelName );
		//if we are able to load our model... 
		if( m_view.LoadModel( s ) )
		{
			//...We can add a member to our serializable object
			CMemberData* m_memberData = new CMemberData( s, m_addModel->m_strBitmapName, m_addModel->m_strNameInList );
			//Add the new element to our CObArray member
			m_array.Add( m_memberData );

			//Add the name to the list and assign a value to the new item
			//LVITEM lvItem;
			lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
			lvItem.iItem = m_numberOfDataElements;
			lvItem.iSubItem = 0;
			lvItem.iImage = 0;
			lvItem.pszText = (LPWSTR)(LPCWSTR)(m_addModel->m_strNameInList );
			m_lstCtrlNames.InsertItem(&lvItem);

			//Add a new bitmap
			HBITMAP hBitmap;
			bool m_failed = false;
			if( m_addModel->m_strBitmapName != _T("") )
			{
				s = _T("data/bitmaps/") + m_addModel->m_strBitmapName;
				hBitmap = (HBITMAP)LoadImage( NULL, s, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
				if( !hBitmap )
				{
	 				s = _T("data/bitmaps/default.bmp") ;
					m_failed = true;
				}
			}
			//if we failed to load the specified image or if the string hasn't been specified
			else if( m_failed ||  m_addModel->m_strBitmapName == _T("") )
			{
				s = _T("data/bitmaps/default.bmp") ;
				hBitmap = (HBITMAP)LoadImage( NULL, s, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
			}

			CBitmap* bmp = CBitmap::FromHandle( hBitmap );
			m_imgPhoto.push_back( bmp );

			//We successfully added a model to the list
			//Select the current item
			m_lstCtrlNames.SetItemState(m_numberOfDataElements, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
			m_lstCtrlNames.EnsureVisible( m_numberOfDataElements, FALSE );

			m_view.m_modelIndex = m_numberOfDataElements;

			//if it's the first time we add a model
	        if( ++m_numberOfDataElements == 1 )
			{
				//Set the initial properties of the list control
				m_lstCtrlNames.SetExtendedStyle( LVS_EX_INFOTIP
					| LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP | LVS_EX_GRIDLINES );
				m_SmallImage.Create(IDB_SMALLIMG, 16, 1, RGB(255, 255, 255)); 
				m_lstCtrlNames.SetImageList( &m_SmallImage, LVSIL_SMALL );
				
				ChangeBitmaps();

				//Enable all the required buttons and focuse on the interactive button
				m_view.m_IsInteractive = true;
				m_btnInteractive.EnableWindow( true );
				m_btnInteractive.SetFocus();

				m_btnRotate.EnableWindow( TRUE );

				m_btnWhitePoints.EnableWindow( TRUE );
				m_btnTexturedPoints.EnableWindow( TRUE );
				m_btnWhiteLines.EnableWindow( TRUE );
				m_btnTexturedLines.EnableWindow( TRUE );
				m_btnSolid.EnableWindow( TRUE );
				m_btnHome.EnableWindow( TRUE );
				m_btnRemoveModel.EnableWindow( TRUE );
				m_slider.ShowWindow( TRUE );

			}
			m_view.m_numberOfDataElements = m_numberOfDataElements;

			if( m_numberOfDataElements > 1 )
			{
				m_btnPrev.EnableWindow( TRUE );
			}
			m_btnNext.EnableWindow( FALSE );

			m_btnSaveData.EnableWindow( TRUE );
			m_isDraft = true;

		}
		//if we are not able to load the model
		else
		{
			//We can't load the model, report an errror
			AfxMessageBox( _T("Sorry,We couldn't load the model" ) );
		}
		//reset the names of the m_addModel member
		m_addModel->m_strBitmapName = _T("");
		m_addModel->m_strModelName = _T("");
		m_addModel->m_strNameInList = _T("");
	}
}

void CCal3DViewerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	delete m_addModel;
	m_imgPhoto.clear();
	//Delete the CObArray elements
	for( INT_PTR i = 0; i < m_array.GetSize(); i++ )
	{
		CMemberData* pa = reinterpret_cast<CMemberData*>(m_array.GetAt( i ) );
		if( pa )
			delete pa;
	}
	m_array.RemoveAll();
}

void CCal3DViewerDlg::OnBnClickedHome()
{
	// TODO: Add your control notification handler code here
	m_view.m_Rotation.i = m_view.m_Rotation.j = m_view.m_Rotation.k = 0.0f;
	m_view.m_camera.i = m_view.m_camera.j = m_view.m_camera.k = 0.0f;
	m_view.m_distance = 0.0f;
	m_view.m_isLighting = true;
	m_view.m_isTextured = true;
	m_view.m_drawBone = false;
	m_view.m_DrawMode = GL_FILL;
}

void CCal3DViewerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//It's an unused button
}

void CCal3DViewerDlg::Serialize(CArchive& ar)
{
	m_array.Serialize( ar );
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCal3DViewerDlg::OnBnClickedInfo()
{
	infoDlg.SetInfo();
	infoDlg.DoModal();
}

void CCal3DViewerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
  				  MAKEINTRESOURCE(IDC_MOVE));
	SetCursor( m_hCurrentCursor );
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );
	CDialog::OnLButtonDown(nFlags, point);
}

void CCal3DViewerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonUp(nFlags, point);
}

void CCal3DViewerDlg::OnBnClickedMinimize()
{
	CloseWindow();
	// TODO: Add your control notification handler code here
}

bool CCal3DViewerDlg::LoadDataBase(void)
{
	CFile DataBaseFile;
	CFileFind fndFile;

	// Look for the Cars.bcr file
	BOOL exists = fndFile.FindFile( _T("dataBase.dbf") );

	if( exists == TRUE )
	{
		// If the file exists, open it and fill the controls with it
		DataBaseFile.Open(_T("DataBase.dbf"), CFile::modeRead);
		CArchive arc(&DataBaseFile, CArchive::load);
		Serialize(arc);

		arc.Close();
		DataBaseFile.Close();

		m_view.m_array = &m_array;
		return true;
	}
	else
	{
		MessageBoxA(NULL,"Couldn't open database.dbf", "Error", MB_OK);
		return false;
	}
}

void CCal3DViewerDlg::SaveDataBase(void)
{
	CFile DataBaseFile;

	DataBaseFile.Open(_T("DataBase.dbf" ), CFile::modeCreate | CFile::modeWrite);
	CArchive arc(&DataBaseFile, CArchive::store);
	Serialize(arc);

	arc.Close();
	DataBaseFile.Close();
}

void CCal3DViewerDlg::OnBnClickedRemovemodel()
{
	// TODO: Add your control notification handler code here
	int nSelected = -1; 
	POSITION p = m_lstCtrlNames.GetFirstSelectedItemPosition();
	while( p )
	{
		nSelected = m_lstCtrlNames.GetNextSelectedItem(p);
	}

	if( nSelected >= 0 )
	{
		//Does she want to remove the item?
		if( IDYES == MessageBox( _T("Are you sure you want to delete the item?"), _T("Delete..."), MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2 ) )
		{
			//erase the 3D model associated with that ID
			m_view.removeModel( nSelected );
			//Remove the bitmap associated with that ID
			std::vector<CBitmap*>::iterator it = m_imgPhoto.begin() + nSelected;
			DeleteObject( m_imgPhoto[nSelected] );
			m_imgPhoto.erase( it );
			//Remove the associated CObArray element 
			CMemberData* pa;
			pa = reinterpret_cast<CMemberData*>( m_array.GetAt( nSelected ) );
			if( pa )
			{
				m_array.RemoveAt( nSelected );
				delete pa;
				m_array.FreeExtra();
			}

			//delete the item from the list
			m_lstCtrlNames.DeleteItem( nSelected );

			//Set the new element of the list as selected
			if( nSelected == m_numberOfDataElements - 1 && m_numberOfDataElements > 1 )
			{
				m_lstCtrlNames.SetItemState( nSelected - 1, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
				m_lstCtrlNames.EnsureVisible( nSelected - 1, FALSE );
			} 
			else if( m_numberOfDataElements > 1 )
			{
				m_lstCtrlNames.SetItemState( nSelected, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
				m_lstCtrlNames.EnsureVisible( nSelected, FALSE );
			}


			//Decrease number of data elements
			m_view.m_numberOfDataElements = --m_numberOfDataElements;

			//Disable some buttons if there's no model to be shown
			if( !m_numberOfDataElements )
			{
				m_btnPrev.EnableWindow( FALSE );
				m_btnNext.EnableWindow( FALSE );
				m_btnPrevAnim.EnableWindow( FALSE );
				m_btnNextAnim.EnableWindow( FALSE );

				m_btnStop.EnableWindow( FALSE );
				m_btnRotate.EnableWindow( FALSE );
				m_btnInteractive.EnableWindow( FALSE );

				m_btnWhitePoints.EnableWindow( FALSE );
				m_btnTexturedPoints.EnableWindow( FALSE );
				m_btnWhiteLines.EnableWindow( FALSE );
				m_btnTexturedLines.EnableWindow( FALSE );
				m_btnSolid.EnableWindow( FALSE );
				m_btnHome.EnableWindow( FALSE );
				m_btnRemoveModel.EnableWindow( FALSE );
				m_slider.ShowWindow( FALSE );

			}

			if( nSelected == m_numberOfDataElements - 1 )
			{
				if( m_numberOfDataElements > 1 )
				{
					m_btnNext.EnableWindow( FALSE );
					m_btnPrev.EnableWindow( TRUE );
				}
				else
				{
					m_btnPrev.EnableWindow( TRUE );
				}
			}
			ChangeBitmaps();
			ChangeModels();
			//We have made some changes, but the user hasn't saved them yet
			m_btnSaveData.EnableWindow( TRUE );
			m_isDraft = true;
		}
	}
	else
	{
		AfxMessageBox( _T("No item has been selected or there's no item on the list") );
	}
}

void CCal3DViewerDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ChangeBitmaps();
	*pResult = 0;
}

void CCal3DViewerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ChangeModels();
	*pResult = 0;
}

void CCal3DViewerDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	ChangeBitmaps();
	*pResult = 0;
}

void CCal3DViewerDlg::OnBnClickedSaveData()
{
	// TODO: Add your control notification handler code here
	SaveDataBase();
	m_btnSaveData.EnableWindow( FALSE );
	m_isDraft = false;
}

void CCal3DViewerDlg::OnBnClickedMyhelp()
{
	// TODO: Add your control notification handler code here
	CHelp m_help;
	m_help.DoModal();
}

void CCal3DViewerDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

LRESULT CCal3DViewerDlg::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// I actually don't use from the m_nPos variable, but I might need it someday!
	if( m_numberOfDataElements )
	{
		m_view.m_nPos = m_slider.GetPos();
		m_view.setLodLevel( float(m_view.m_nPos) / 20.0f ); 
	}
	return 0;
}

void CCal3DViewerDlg::OnBnClickedNextanimation()
{
	// TODO: Add your control notification handler code here
	if( ! m_view.NextAnimation() )
	{
		m_btnNextAnim.EnableWindow( FALSE );

	}
	else
	{
		m_btnNextAnim.EnableWindow( TRUE );
	}
	//Enable the PrevAnim button
	m_view.childModel[m_view.m_modelIndex]->clearCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId() - 1, 0.3f );
	m_view.childModel[m_view.m_modelIndex]->blendCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 1.0f, 0.3f);

	m_btnPrevAnim.EnableWindow( TRUE );
}

void CCal3DViewerDlg::OnBnClickedPrevanimation()
{
	// TODO: Add your control notification handler code here
	if( ! m_view.PrevAnimation() )
	{
		m_btnPrevAnim.EnableWindow( FALSE );

	}
	else
	{
		m_btnPrevAnim.EnableWindow( TRUE );
	}
	//Enable the NextAnim button
	m_btnNextAnim.EnableWindow( TRUE );

	m_view.childModel[m_view.m_modelIndex]->clearCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId() + 1, 0.3f );
	m_view.childModel[m_view.m_modelIndex]->blendCycle( m_view.childModel[m_view.m_modelIndex]->GetCurrentAnimationId(), 1.0f, 0.3f);
}

void CCal3DViewerDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here
	CAboutDlg m_aboutDlg;
	m_aboutDlg.DoModal();
}


BOOL CCal3DViewerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN )

		if( GetKeyState(VK_CONTROL) < 0 )
		{
			if( pMsg->wParam == 'T' )
			{
				OnBnClickedTexturedlines();
				return TRUE;
			}

			if( pMsg->wParam == 'W' )
			{
				OnBnClickedWhitelines();
				return TRUE;
			}


			if( pMsg->wParam == 'V' )
			{
				OnBnClickedWhitepoints();
				return TRUE;
			}

			if( pMsg->wParam == 'F' )
			{
				OnBnClickedSolid();
				return TRUE;
			}

			if( pMsg->wParam == 'M' )
			{
				CloseWindow();
				return TRUE;
			}

			if( pMsg->wParam == 'S' )
			{
				if( GetKeyState(VK_SHIFT) < 0 )
					OnBnClickedStop();
				else
					OnBnClickedSaveData();
				return TRUE;
			}

			if( pMsg->wParam == VK_F1 )
			{
				OnBnClickedAbout();
				return TRUE;
			}

			if( pMsg->wParam == 'I' )
			{
				if( GetKeyState(VK_SHIFT) < 0 )
					OnBnClickedInfo();
				else
					OnBnClickedInteractive();
				return TRUE;
			}

			if( pMsg->wParam == 'C' )
			{
				OnBnClickedClose();
				return TRUE;
			}
			if( pMsg->wParam == 'D' )
			{
				OnBnClickedHome();
				return TRUE;
			}
			if( pMsg->wParam == 'H' )
			{
				OnBnClickedMyhelp();
				return TRUE;
			}

			if( pMsg->wParam == 'A' )
			{
				OnBnClickedAddModel();
				return TRUE;
			}

			if( pMsg->wParam == 'B' )
			{
				OnBnClickedBone();
				return TRUE;
			}

			if( pMsg->wParam == 'R' )
			{
				OnBnClickedRotate();
				return TRUE;
			}

			if( pMsg->wParam == VK_DELETE )
			{
				OnBnClickedRemovemodel();
				return TRUE;
			}
			if( pMsg->wParam == 'N' )
			{
				if( GetKeyState(VK_SHIFT) < 0 )
					OnBnClickedNextanimation();
				else
					OnBnClickedNext();
				return TRUE;
			}
			if( pMsg->wParam == 'P' )
			{
				if( GetKeyState(VK_SHIFT) < 0 )
					OnBnClickedPrevanimation();
				else
					OnBnClickedPrev();
				return TRUE;
			}

			if (pMsg->wParam == 'G' )
			{
				//Draw shadow? 
				m_view.m_drawGrid =! m_view.m_drawGrid;
				return TRUE;
			}

		}
	return CDialog::PreTranslateMessage(pMsg);
}
