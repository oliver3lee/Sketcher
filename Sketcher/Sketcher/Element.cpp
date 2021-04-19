// Element.cpp : 實作檔
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"

IMPLEMENT_SERIAL(CElement, CObject, VERSION_NUMBER)

// CElement
CElement::CElement(const CPoint& start, COLORREF color, int style, int penWidth) : m_StartPoint(start), m_PenWidth(penWidth), m_Color(color), m_Style(style)
{
}

CElement::CElement()
{
}

CElement::~CElement()
{
}

void CElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_StartPoint 
			<< m_PenWidth 
			<< m_Color 
			<< m_Style
			<< m_EnclosingRect;
	}
	else
	{
		ar >> m_StartPoint
			>> m_PenWidth
			>> m_Color
			>> m_Style
			>> m_EnclosingRect;
	}
}


// CElement 成員函式