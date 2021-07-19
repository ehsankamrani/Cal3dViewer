//Copyright (C) 2021 Ehsan Kamrani
//This program is distributed under the terms of the GNU Lesser General Public License.


#pragma once

// CMemberData command target
// This class is used to hold the data of each member
//for more information, search for the "serialization" in VC++ 
class CMemberData : public CObject
{
	DECLARE_SERIAL( CMemberData ); 
public:
	CMemberData();
	CMemberData(CStringW modelPath , CStringW bitmapPath , CStringW m_nameInList);
	virtual ~CMemberData();

	void Serialize(CArchive& ar);
	CStringW m_modelPath;
	CStringW m_bitmapPath;
	CStringW m_nameInList;
};


