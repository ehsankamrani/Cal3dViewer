//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.

// Cal3DViewerDlg.h : header file

#pragma once
#include <vector>
#include "afxext.h"
#include "afxwin.h"
#include "GLWindow.h"
#include "afxcmn.h"
#include "AddModel.h"
#include "afxcoll.h"
#include "memberData.h"
#include "vector.h"
#include "bitmapslider.h"
#include "info.h"
using namespace std;
// CCal3DViewerDlg dialog
class CCal3DViewerDlg : public CDialog
{
// Construction
public:
	CCal3DViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYCal3DViewer_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	/////////////////////
	//afx messages
	/////////////////////

	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedInteractive();
	afx_msg void OnBnClickedRotate();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedWhitepoints();
	afx_msg void OnBnClickedBone();
	afx_msg void OnBnClickedWhitelines();
	afx_msg void OnBnClickedTexturedlines();
	afx_msg void OnBnClickedSolid();
	afx_msg void OnBnClickedAddModel();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedHome();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedInfo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMinimize();
	afx_msg void OnBnClickedRemovemodel();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveData();
	afx_msg void OnBnClickedMyhelp();
	afx_msg void OnBnClickedNextanimation();
	afx_msg void OnBnClickedPrevanimation();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam);


	//functions to deal with database
	bool LoadDataBase(void);
	void SaveDataBase(void);
	virtual void Serialize(CArchive& ar);

	void LoadBitmapButtons(void);

	void ChangeBitmaps(void);
	void ChangeModels(void);


    /////////////////////////// 
	//Bitmp buttons
	///////////////////////////

	CBitmapButton m_btnSaveData;
	CBitmapSlider m_slider;
	CBitmapButton m_btnNextAnim;
	CBitmapButton m_btnPrevAnim;
	CBitmapButton m_btnRemoveModel;
	// It opens a new window. It's used to load the models
	CBitmapButton m_btnAddModel;
	// To draw the objects in solid mode( fill them with polygons )
	CBitmapButton m_btnSolid;
	// To show the model with white points
	CBitmapButton m_btnWhitePoints;
	// To show the model with textured points
	CBitmapButton m_btnTexturedPoints;
	// To show the model with white lines
	CBitmapButton m_btnWhiteLines;
	// To show the model with textured lines
	CBitmapButton m_btnTexturedLines;
	// Closes the application
	CBitmapButton m_btnClose;
	// Next Scene
	CBitmapButton m_btnNext;
	// Previous Scene
	CBitmapButton m_btnPrev;
	// To stop the automatic rotation
	CBitmapButton m_btnStop;
	// To rotate the scene and model
	CBitmapButton m_btnRotate;
	// To rotate the scene with the mouse
	CBitmapButton m_btnInteractive;
	//information( programmer and 2D arts )	
	CBitmapButton m_btnInfo;
	//To show the help dialog
	CBitmapButton m_btnHelp;
	// default values for rotatiion, translation and so on
	CBitmapButton m_btnHome;
	//To minimize the window
	CBitmapButton m_btnMinimize;
    
	//////////////////
	//other variables
	//////////////////

	//cursor and brush
	HCURSOR m_hCurrentCursor;
	CBrush m_bkBrush;

	//number of the elements on the list
	int m_numberOfDataElements;

	// When we delete or add a model, we set to true, when we save the changes, set it to false
	bool m_isDraft;

	//it's used in serializations( database with serialization )
	CObArray m_array;

	// To hold the number of the models whenever we want to add/remove/load/save the items
	LVITEM lvItem;

	//And instance of a dialod to add the models
	CAddModel* m_addModel;

	//An instance of OpenGL class--GLWindow is used to render the scene and models
	GLWindow m_view;

	// To show the list of the objects
	CListCtrl m_lstCtrlNames;

	// To insert the names insed the list control, we don't get them from a dialog box, so we hardcode them
	int InsertItemNames(void);

	//To load and show the images in the list control
	CImageList m_SmallImage;

	// To load the Bitmap photos
	std::vector<CBitmap*> m_imgPhoto;

	// If we have no model, we use the default image
	CBitmap m_defaultImg;

	// To show the photos
	CStatic m_imgCtrl;
	afx_msg void OnPaint();

protected:
	virtual void OnCancel();

	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CBitmapButton m_btnAbout;
public:
	afx_msg void OnBnClickedAbout();
public:
	CInfo infoDlg;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
