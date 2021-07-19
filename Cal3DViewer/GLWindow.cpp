//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


// GLWindow.cpp : implementation file

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "MemberData.h"
#include "GLWindow.h"
#include "OpenGL.h"
#include "CommonGL.h"
// GLWindow

IMPLEMENT_DYNAMIC(GLWindow, CWnd)

GLWindow::GLWindow()
: m_modelIndex(0)
, m_enableRotation(false)
, m_PrevPoint(0)
, m_DeltaMouse(0)
, m_IsLMouseDown(false)
, m_IsMouseMoving(false)
, m_IsInteractive(true)
, m_IsMultiSampling(false)
, m_IsRMouseDown(false)
, m_distance(0.0f)
, m_isLighting(true)
, m_IsMMouseDown(false)
, m_array(NULL)
, m_numberOfDataElements(0)
, m_elapsedTime(0.01f)
, m_isTextured(true)
, m_nPos(1)
, m_drawBone(false)
, m_drawGrid(true)
{
	m_Rotation.i = m_Rotation.j = m_Rotation.k = 0.0f;
	m_camera.i = m_camera.j = m_camera.k = 0.0f;

	//{ 0.0f, 0.0f, 1.0f, 0.0f }
	m_plane[0] = m_plane[1] = m_plane[3] = 0.0f;
	m_plane[2] = 1.0f;
}

GLWindow::~GLWindow()
{
}

BEGIN_MESSAGE_MAP(GLWindow, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// GLWindow message handlers

int GLWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// Can we put this in the constructor?
    
	int PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	m_pDC = new CClientDC(this);

	if( m_IsMultiSampling )
	{
		if( WGLEW_ARB_pixel_format )
		{
			float fAttributes[] = {0,0};
			UINT numFormats;
			int attributes[] = {
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 0,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_SAMPLE_BUFFERS_ARB, 1,
				WGL_SAMPLES_ARB, 4,						// Check For m_numSamplesX Multisampling
				0, 0
			};

			wglChoosePixelFormatARB( m_pDC->GetSafeHdc(), attributes, fAttributes, 1, &PixelFormat, &numFormats );
			if( numFormats == 0 )
			{
				MessageBoxA( NULL, "Couldn't initialize your window with 4 samples", "Engine Error", MB_OK | MB_ICONERROR );
				//Test for 2 samples
				attributes[19] = 2;
				wglChoosePixelFormatARB( m_pDC->GetSafeHdc(), attributes, fAttributes, 1, &PixelFormat, &numFormats );
				if( numFormats == 0 )
				{
					MessageBoxA( NULL, "Couldn't initialize your window with 2 samples", "Engine Error", MB_OK | MB_ICONERROR );
					m_IsMultiSampling = false;
				}
			}
		}
		else
		{
			MessageBoxA( NULL, "Couldn't support multisampling", "Engine Error", MB_OK | MB_ICONERROR );
			m_IsMultiSampling = false;
		}

	}//if( multisampling )

	memset (&pfd, 0, sizeof(pfd));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits	= 24;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits	= 32;
	pfd.cStencilBits = 0;

	if (!m_IsMultiSampling)
	{
		PixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
		if (PixelFormat == 0)
		{	
			MessageBoxA(NULL, "Couldn't choose the pixel format.", "Engine Error", MB_OK | MB_ICONERROR);
			delete m_pDC;
			m_pDC = NULL;
			return (false);							
		}
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), PixelFormat, &pfd ) == FALSE)	
	{
		MessageBoxA(NULL, "Couldn't set the pixel format.", "Engine Error", MB_OK | MB_ICONERROR);
		delete m_pDC;
		m_pDC = NULL;
		return (false);							
	}
	m_hRC = wglCreateContext( m_pDC->GetSafeHdc() );
	if ( m_hRC == NULL)
	{
		MessageBoxA(NULL, "Couldn't create the OpenGL context.", "Engine Error", MB_OK | MB_ICONERROR);
		delete m_pDC;
		m_pDC = NULL;
		return (false);								
	}

	if (!wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))					
	{
		MessageBoxA(NULL, "Couldn't make a stream between HDC and HRC.", "Engine Error", MB_OK | MB_ICONERROR);
		wglDeleteContext(m_hRC);
		delete m_pDC;
		m_pDC = NULL;
		m_hRC = NULL;
		return (false);								
	}
	return (true);
}

void GLWindow::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	SetupPerspective( 54.0f, cx, cy);
}

void GLWindow::OnDestroy()
{
	wglMakeCurrent(NULL, NULL);
	if( m_hRC )
		wglDeleteContext(m_hRC);
	if (m_pDC)
		delete m_pDC;
	RemoveAll();
	CWnd::OnDestroy();
}

void GLWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderWindow();
	SwapBuffers(m_pDC->m_hDC);
}

// Init OpenGL
//============================================================================================
bool GLWindow::InitAll()
{
	glShadeModel(GL_SMOOTH);										// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							// Black Background
	glClearDepth(1.0f);												// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);										// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);											// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Really Nice Perspective Calculations
	glPointSize( 1.5f );
	glEnable( GL_POINT_SMOOTH );

	if( !InitializeModels() )
	{
		return false;
	}

	SetTimer( 1, 1 , 0 );
	m_timer = new Timer();
	if( !m_timer->Init() )
	{
        //Report an error message
		MessageBoxA( NULL, "Cannot initialize the timer", "Engine Error", MB_OK | MB_ICONINFORMATION );
		return 0; 
	}

	initializeLights();

	commonGL.SetShadowMatrix( m_shadowMatrix, m_lightPos0, m_plane );

	Redraw();
	return true;
}


// Setup perspective
//============================================================================================
void GLWindow::SetupPerspective( GLfloat theta, int cx, int cy)
{
	m_width  = cx;
	m_height = cy;

	glViewport(0, 0, m_width, m_height);// resets the viewport to new dimensions.
    glMatrixMode(GL_PROJECTION);    // Sets the projection matrix.
    glLoadIdentity();               // Reset the modelview matrix.

    // calculate the aspect ratio of the window.
    gluPerspective(theta, (double)m_width/(float)m_height, 1.0, 10000 );

    glMatrixMode(GL_MODELVIEW);     // Sets the projection matrix.
    glLoadIdentity();               // Reset the modelview matrix.
}


// Setup perspective
//============================================================================================
void GLWindow::SetupPerspective( GLfloat theta )
{
	// Now that the dimensions are set up, we can set up the projection
	// matrix. Since we've overridden OnSize(), we need to do it ourselves
	CRect rect;
	GetClientRect(&rect);

	// OK, now save the dimensions of the window, cutting the width in half
	m_width  = rect.Width();
	m_height = rect.Height();

	SetupPerspective( theta, rect.Width(), rect.Height());
}

// Setup ViewPort
//============================================================================================
bool GLWindow::SetupViewport( int cx, int cy )
{
	// select the full client area
    glViewport(0, 0, cx, cy);
	return true;
}



// Render Scene
//============================================================================================
void GLWindow::RenderWindow()
{
	//if we have any models in our list
	
	glLoadIdentity();
	GetDefaultDrawMode();
	DrawBackground();

	if( m_numberOfDataElements )
	{
		if( baseModel[m_modelIndex] )
		{
			//Check the rotation boundry if it's enabled
			if( m_enableRotation )
			{
				if( m_Rotation.i >= 360.0f )
					m_Rotation.i -= 360.0f;
			}
			else if( m_IsMouseMoving && m_IsLMouseDown && m_IsInteractive )
			{
				m_Rotation.i += m_DeltaMouse.x;
				m_Rotation.j += m_DeltaMouse.y;
			}

			else if( m_IsMouseMoving && m_IsMMouseDown && m_IsInteractive )
			{
				m_camera.i -= m_DeltaMouse.x;
				m_camera.j += m_DeltaMouse.y;
			}

			if( m_IsRMouseDown && m_IsMouseMoving && m_IsInteractive )
				m_distance += m_DeltaMouse.y * 0.5f;

			GetDrawMode();
			
			glLoadIdentity();
			gluLookAt( m_camera.i, m_camera.j, 0.0f, m_camera.i, m_camera.j, -200.0f, 0.0f, 1.0f, 0.0f );
				glTranslatef(0.0f,-80.0f * baseModel[m_modelIndex]->m_scale,-210.0f * baseModel[m_modelIndex]->m_scale + m_distance );						// Move Right 1.5 Units And Into The Screen 7.0

			glRotatef(-90.0f,1.0f,0.0f,0.0f);					// Rotate The Quad On The X axis ( NEW )
			glRotatef(m_Rotation.j, 1.0f, 0.0f, 0.0f );
			glRotatef(m_Rotation.i,0.0f,0.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
			
			if( !m_isLighting )
				glDisable( GL_LIGHTING );
			else 
				glEnable( GL_LIGHTING );

			Light0.Position( LightPos0 );
			Light1.Position( LightPos1 );
			Light2.Position( LightPos2 );

			if( m_drawGrid )
			{
				DrawShadow();
				DrawGrid();
			}
			m_elapsedTime = m_timer->GetElapsedSeconds() ;

			//Draw the model or draw its skeleton?
			childModel[m_modelIndex]->RenderModel( m_elapsedTime, m_isTextured );
			if( m_drawBone )
				childModel[m_modelIndex]->RenderSkeleton();

			//Increment the rotation if it's enabled 
			if( m_enableRotation )
				m_Rotation.i += m_elapsedTime * 20.0f;
			m_IsMouseMoving = false;
		}
	}//if(numberOfDataElements)

}


// Redrawre
//============================================================================================
void GLWindow::Redraw()
{
	OnPaint();
}

// //Initializes and sets all the lights of the scene
void GLWindow::initializeLights(void)
{
		glEnable( GL_LIGHTING );
		//Key light
		GLfloat diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat ambient[] = {0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		LightPos0[0] = 1.0f;
		LightPos0[1] = -1.0f;
		LightPos0[2] = 1.0f;
		LightPos0[3] = 0.0f;
		//to compute the shadow matrix, note that we don't move our light in this application
		m_lightPos0[0] = 0.3f;
		m_lightPos0[1] = -0.3f;
		m_lightPos0[2] = 1.0f;
		m_lightPos0[3] = 0.0f;

		Light0.Ambient( ambient );
		Light0.Diffuse( diffuse );
		Light0.Specular( specular );
		Light0.Enable();

		//Fill light
		GLfloat diffuse1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat ambient1[] = {0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat specular1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		LightPos1[0] = -1.0f;
		LightPos1[1] = -1.0f;
		LightPos1[2] = -1.0f;
		LightPos1[3] = 0.0f;
		
		Light1.Ambient( ambient1 );
		Light1.Diffuse( diffuse1 );
		Light1.Specular( specular1 );
		Light1.Enable();

		//Back light
		GLfloat diffuse2[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat ambient2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat specular2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		LightPos2[0] = 0.0f;
		LightPos2[1] = 1.0f;
		LightPos2[2] = 0.0f;
		LightPos2[3] = 0.0f;
		

		Light2.Ambient( ambient2 );
		Light2.Diffuse( diffuse2 );
		Light2.Specular( specular2 );
		Light2.Enable();
}

// To initialize the 3D models
bool GLWindow::InitializeModels(void)
{
	if( m_numberOfDataElements )
	{
		CMemberData* currentData = NULL;
		for( int index = 0; index < m_numberOfDataElements; index++ )
		{
			currentData = reinterpret_cast<CMemberData*>((*m_array)[index]);
			Cal3DBase* pToBase = new Cal3DBase();
			baseModel.push_back( pToBase );
			//Initialize 3D models here
			bool loaded = baseModel[ index ]->Init( currentData->m_modelPath );
			if( !loaded )
			{
				AfxMessageBox( _T("Couldn't load some files\nHave you removed these files manually?\nplease correct your data, you might not see some models") );
				baseModel[ index ]->Release();
				delete pToBase;
				baseModel[index] = 0;
			}

			if( loaded )
			{
				Cal3DChild* pToChild = new Cal3DChild();
				childModel.push_back( pToChild );

				if( !childModel[ index ]->Init( baseModel[ index ]->GetCore() ) )
				{
					childModel[ index ]->Release();
					baseModel[ index ]->Release();
					delete pToChild;
					delete pToBase;
					//I hold the index( I don't use baseModel.pop_back() or childModel.pop_back() )
					//to grow the index of the STL objects with the list name,
					//A pointer in an STL object has a sizeof(DWORD), so it doesn't require noticable memory
					//However if the user remove the name from the list, I also remove that pointer from the STL object
					//with the erase function.
					baseModel[index] = 0;
					childModel[index] = 0;
				}
			}
			else
			{
				//I hold the index( I don't use baseModel.pop_back() or childModel.pop_back() )
				//to grow the index of the STL objects with the list name,
				//A pointer in an STL object has a sizeof(DWORD), so it doesn't require noticable memory
				//However if the user remove the name from the list, I also remove that pointer from the STL object
				//with the erase function.
				childModel.push_back( 0 );
			}
		}
	}
	return true;
}

void GLWindow::ReleaseModels(void)
{
	if( m_numberOfDataElements )
	{
		//First we delete the childs
		for( vector<Cal3DChild*>::iterator it = childModel.begin(); it != childModel.end(); it++ )
		{
			if( *it )
			{
				(*it)->Release();
				delete (*it);
			}
		}
		//Then we delete the parents
		for( vector<Cal3DBase*>::iterator it = baseModel.begin(); it != baseModel.end(); it++ )
		{
			if( *it )
			{
				(*it)->Release();
				delete (*it);
			}
		}
		//Clear the vctor objects
		childModel.clear();
		baseModel.clear();
	}
}

bool GLWindow::NextObject(void)
{
	if( ++m_modelIndex >= m_numberOfDataElements - 1 )
	{
		m_modelIndex = m_numberOfDataElements - 1;
		return false;
	}

	return true;
}

bool GLWindow::PrevObject(void)
{

	if( --m_modelIndex <= 0 )
	{
		m_modelIndex = 0;
		return false;
	}

	return true;
}

void GLWindow::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnTimer(nIDEvent);
	OnPaint();
}

void GLWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	if( m_IsInteractive && m_numberOfDataElements)
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
  					  MAKEINTRESOURCE(IDC_ROTATE));
	}
	else
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
 					  MAKEINTRESOURCE(IDC_INVALID));
	}
	
	SetCursor( m_hCurrentCursor );

	m_IsLMouseDown = true;
	m_PrevPoint = point;
	
	CWnd::OnLButtonDown(nFlags, point);

}

void GLWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if( GetCapture() == this )
		ReleaseCapture();
	//Load the default cursor
	CWnd::OnLButtonUp(nFlags, point);
	m_IsLMouseDown = false;
	m_DeltaMouse.x = m_DeltaMouse.y = 0;
}

void GLWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	if( m_IsInteractive && m_numberOfDataElements)
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
  					  MAKEINTRESOURCE(IDC_ZOOM));
	}
	else
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
 					  MAKEINTRESOURCE(IDC_INVALID));
	}
	SetCursor( m_hCurrentCursor );

	m_IsRMouseDown = true;
	m_PrevPoint = point;

	m_DeltaMouse.x = m_DeltaMouse.y = 0;

	CWnd::OnRButtonDown(nFlags, point);
}

void GLWindow::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if( GetCapture() == this )
		ReleaseCapture();
	m_IsRMouseDown = false;
	m_DeltaMouse.x = m_DeltaMouse.y = 0;

	CWnd::OnRButtonUp(nFlags, point);
}

void GLWindow::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	if( m_IsInteractive && m_numberOfDataElements )
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
  					  MAKEINTRESOURCE(IDC_PAN));
	}
	else
	{
		m_hCurrentCursor = LoadCursor(AfxGetInstanceHandle(),
 					  MAKEINTRESOURCE(IDC_INVALID));
	}
	SetCursor( m_hCurrentCursor );

	m_PrevPoint = point;
	m_IsMMouseDown = true;

	CWnd::OnMButtonDown(nFlags, point);
}

void GLWindow::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if( GetCapture() == this )
		ReleaseCapture();
	m_IsMMouseDown = false;

	CWnd::OnMButtonUp(nFlags, point);
}

void GLWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_IsMouseMoving = true;
	CWnd::OnMouseMove(nFlags, point);

	if( m_IsLMouseDown || m_IsRMouseDown || m_IsMMouseDown)
	{
		if( GetCapture() == this )
		{
			m_DeltaMouse.x = point.x - m_PrevPoint.x;
			m_DeltaMouse.y = point.y - m_PrevPoint.y;
			m_PrevPoint = point;
		}
	}
}

// To remove all the model and texture data
bool GLWindow::RemoveAll(void)
{
	KillTimer( 1 );
	if( m_timer )
	{
		delete m_timer;
		m_timer = NULL;
	}
	//Release all the 3D models
	ReleaseModels();

	return true;
}

// //Draw the background image
void GLWindow::DrawBackground(void)
{
	CommonGL m_CGL;
	static float p[] = { 0.8f, 0.8f, 0.8f, -5000.f, -5000.f, -5000.f,
		                 0.1f, 0.1f, 0.3f, -5000.f, 5000.f, -5000.0f,
						 0.1f, 0.1f, 0.3f, 5000.f, 5000.f, -5000.f,
						 0.8f, 0.8f, 0.8f, 5000.f, -5000.f, -5000.f };
	m_CGL.DrawQuad( p, false ); //color mode
}

void GLWindow::GetDrawMode(void)
{
	glPolygonMode( GL_FRONT_AND_BACK, m_DrawMode );
}

// Default mode, I use fill mode
void GLWindow::GetDefaultDrawMode(void)
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

bool GLWindow::LoadModel(CStringW modelPath)
{
	Cal3DBase* pToBase = new Cal3DBase();
	baseModel.push_back( pToBase );
	//Initialize a 3D model here
	if( !baseModel[ m_numberOfDataElements ]->Init( modelPath ) )
	{
		baseModel[ m_numberOfDataElements ]->Release();
		delete pToBase;
		baseModel.pop_back();
		return false;
	}
	Cal3DChild* pToChild = new Cal3DChild();
	childModel.push_back( pToChild );
	if( !childModel[ m_numberOfDataElements ]->Init( baseModel[ m_numberOfDataElements ]->GetCore() ) )
	{
		baseModel[ m_numberOfDataElements ]->Release();
		childModel[ m_numberOfDataElements ]->Release();
		delete pToChild;
		delete pToBase;
		baseModel.pop_back();
		childModel.pop_back();
		return false;
	}
	 
	return true;
}

// to remove a model
bool GLWindow::removeModel(int index)
{
	//point to the suggested model
	std::vector<Cal3DBase*>::iterator m_base = baseModel.begin() + index;
	std::vector<Cal3DChild*>::iterator m_child = childModel.begin() + index;
	
	if( *m_child )
	{
		(*m_child)->Release();
		delete (*m_child );
	}
	
	if( *m_base )
	{
		(*m_base)->Release();
		delete (*m_base);
	}
	childModel.erase( m_child );
	baseModel.erase( m_base );

	return true;
}

void GLWindow::DrawGrid(void)
{
	glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT );
	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );

	//Draw the grid here
	glColor3f( 0.8f, 0.8f, 0.8f );
	glBegin( GL_LINES );
	for( int index = -10; index <= 10; index++ )
	{
		glVertex3f( 0.0f + (float)index * 20.0f, -200.0f, 0.0f );
		glVertex3f( 0.0f + (float)index * 20.0f, 200.0f, 0.0f );

		glVertex3f( -200.0f ,(float)index * 20.0f, 0.0f );
		glVertex3f( 200.0f,(float)index * 20.0f,0.0f );
	}
	glEnd();
	glBegin( GL_LINES );
	//Draw the axes here
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 10.0f, 0.0f, 0.0f );
	
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 10.0f, 0.0f );

	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 10.0f );

	glEnd();

	glPopAttrib();
}

void GLWindow::setLodLevel(float LodLevel)
{
	childModel[m_modelIndex]->setLodLevel( LodLevel );
}

int GLWindow::GetAnimationCount(void)
{
	return childModel[m_modelIndex]->GetAnimationCount();
}

void GLWindow::DrawShadow(void)
{
	glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT );
	glPushMatrix();
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	glEnable( GL_CULL_FACE );
	glMultMatrixf( m_shadowMatrix );
	glColor3f( 0.3f, 0.3f, 0.3f );
	//Do not send elapsedTime to the shadow, we have updated the model before
	childModel[m_modelIndex]->RenderModel( 0.0f, false );
	glDisable( GL_CULL_FACE );
	glPopMatrix();
	glPopAttrib();
}

bool GLWindow::NextAnimation(void)
{
	childModel[m_modelIndex]->SetCurrentAnimationId( childModel[m_modelIndex]->GetCurrentAnimationId() + 1 );
	if( childModel[m_modelIndex]->GetCurrentAnimationId() >= childModel[m_modelIndex]->GetAnimationCount() - 1 )
	{
		childModel[m_modelIndex]->SetCurrentAnimationId( childModel[m_modelIndex]->GetAnimationCount() - 1 );
		return false;
	}
	
	return true;
}

bool GLWindow::PrevAnimation(void)
{
	childModel[m_modelIndex]->SetCurrentAnimationId( childModel[m_modelIndex]->GetCurrentAnimationId() - 1 );

	if( childModel[m_modelIndex]->GetCurrentAnimationId() <= 0 )
	{
		childModel[m_modelIndex]->SetCurrentAnimationId( 0 );
		return false;
	}

	return true;
}

bool GLWindow::IsModelValid(int index)
{
	if( childModel[m_modelIndex] )
		return true;
	return false;
}

bool GLWindow::GetModelInfo(int& numberOfFaces, int& numberOfAnimations, int& numberOfVertices
							, int& numberOfMeshes, int& numberOfMaterials, float& LODLevel)
{
	if( m_numberOfDataElements )
	{
		if( childModel[m_modelIndex] )
		{
			numberOfAnimations = childModel[m_modelIndex]->GetAnimationCount();
			numberOfFaces = childModel[m_modelIndex]->GetFaceCount();
			numberOfVertices = childModel[m_modelIndex]->GetVertexCount();
			numberOfMeshes = childModel[m_modelIndex]->GetMeshCount();
			numberOfMaterials = childModel[m_modelIndex]->GetMaterialCount();
			LODLevel = childModel[m_modelIndex]->GetLODLevel();
			return true;
		}
	}
	return false;
}

