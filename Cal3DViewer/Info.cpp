// Info.cpp : implementation file
//

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "Info.h"
#include "OpenGL.h"

// CInfo dialog

IMPLEMENT_DYNAMIC(CInfo, CDialog)

CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
   , m_strVendor(_T(""))
   , m_strRenderer(_T(""))
   , m_strVersion(_T(""))
   , m_strShadingVersion(_T(""))
   , m_strExtensions( _T("") )
   , m_strNumFaces(_T(""))
   , m_strNumVertices(_T(""))
   , m_strNumAnimations(_T(""))
   , m_pTo_m_view(NULL)
{
}

CInfo::~CInfo()
{
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VENDOR, m_strVendor);
	DDX_Text(pDX, IDC_RENDERER, m_strRenderer);
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_SHADINGVERSION, m_strShadingVersion);
	DDX_Text(pDX, IDC_NUMFACES, m_strNumFaces);
	DDX_Text(pDX, IDC_NUMVERTICES, m_strNumVertices);
	DDX_Text(pDX, IDC_NUMANIMATIONS, m_strNumAnimations);
	DDX_Text(pDX, IDC_NUMMATERIALS, m_strNumMaterials);
	DDX_Text(pDX, IDC_NUMMESHES, m_strNumMeshes);
	DDX_Text(pDX, IDC_LODLEVEL, m_strLODLevel);
	DDX_Text(pDX, IDC_EXTENSIONS, m_strExtensions);
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
END_MESSAGE_MAP()


// CInfo message handlers

void CInfo::SetInfo(void)
{
	m_strVendor = _T("");
    m_strRenderer = _T("");
    m_strVersion = _T("");
    m_strShadingVersion = _T("");
    m_strExtensions = _T("") ;
    m_strNumFaces = _T("");
    m_strNumVertices = _T("");
    m_strNumAnimations = _T("");

	m_strVendor =(char*)glGetString(GL_VENDOR);
	m_strRenderer =(char*)glGetString(GL_RENDERER);
	m_strVersion =(char*)glGetString(GL_VERSION);
	m_strShadingVersion =(char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	m_strExtensions =(char*)glGetString(GL_EXTENSIONS);
	m_strExtensions.Replace( _T(" "), _T("\r\n" ) );

	//We access the m_view members via the m_pTo_m_view pointer
		int num_vertices = 0, num_faces = 0, num_animations = 0,
		num_meshes = 0, num_materials = 0;
	float LODLevel = 1.0f;
	bool isValid = false;
	if( isValid = m_pTo_m_view->GetModelInfo( num_faces, num_animations, num_vertices,
		                        num_meshes, num_materials, LODLevel ) )
	{
		m_strNumFaces.Format( _T("%d"), num_faces );
		m_strNumAnimations.Format( _T("%d"), num_animations );
		m_strNumMeshes.Format( _T("%d"), num_meshes );
		m_strNumMaterials.Format(  _T("%d"), num_materials );
		m_strNumVertices.Format( _T("%d"), num_vertices );
		m_strLODLevel.Format( _T("%f"), LODLevel );
	}
	else
	{
		CStringW temp = _T( "Unavailable" );
		m_strNumFaces = temp;
		m_strNumAnimations = temp;
		m_strNumMeshes = temp;
		m_strNumMaterials = temp;
		m_strNumVertices = temp;
		m_strLODLevel = temp;
	}
}
