#pragma once
#include "GLWindow.h"

// CInfo dialog

class CInfo : public CDialog
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInfo();

// Dialog Data
	enum { IDD = IDD_INFO };

	// //To get the information of the current model
	GLWindow* m_pTo_m_view;

public:
	void SetInfo(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CStringW m_strVendor;
	CStringW m_strVersion;
	CStringW m_strShadingVersion;
	CStringW m_strRenderer;
	CStringW m_strNumFaces;
	CStringW m_strNumVertices;
	CStringW m_strNumAnimations;
	CStringW m_strNumMeshes;
	CStringW m_strNumMaterials;
	CStringW m_strLODLevel;
	CStringW m_strExtensions;
};
