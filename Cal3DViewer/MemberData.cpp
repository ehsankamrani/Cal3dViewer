//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.



// MemberData.cpp : implementation file

#include "stdafx.h"
#include "Cal3DViewer.h"
#include "MemberData.h"

IMPLEMENT_SERIAL( CMemberData, CObject, 1 );
// CMemberData

CMemberData::CMemberData()
: m_modelPath(_T(""))
, m_bitmapPath(_T(""))
, m_nameInList(_T(""))
{
}

CMemberData::~CMemberData()
{
}


// CMemberData member functions

void CMemberData::Serialize(CArchive& ar)
{

	if( ar.IsLoading() )
		ar >> m_modelPath >> m_bitmapPath >> m_nameInList;
	else
		if( ar.IsStoring() )
		{
			ar << m_modelPath << m_bitmapPath << m_nameInList;
		}
}

CMemberData::CMemberData(CStringW modelPath , CStringW bitmapPath , CStringW nameInList)
{
	m_modelPath = modelPath;
	m_bitmapPath = bitmapPath;
	m_nameInList = nameInList;
}
