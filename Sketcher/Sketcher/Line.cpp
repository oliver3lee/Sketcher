#include "stdafx.h"
#include "Line.h"

IMPLEMENT_SERIAL(CLine, CElement, VERSION_NUMBER)

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color, int penWidth) : CElement(start, color, 0, penWidth), m_EndPoint(end)
{
	// Define the enclosing rectangle
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();	// 正規化，使其符合CRect規範
	int width(0 == penWidth ? 1 : penWidth);
	m_EnclosingRect.InflateRect(width, width);
}

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::ChangeSecondPoint(const CPoint& secondPoint)
{
	m_EndPoint = secondPoint;
}

// Draw a CLine object
void CLine::Draw(CDC* pDC)
{
	if (false == m_bCreatePen)
	{
		CreatePen(m_aPen);
		m_bCreatePen = true;
	}
	CPen* pOldPen;
	pOldPen = pDC->SelectObject(&m_aPen);	// Select the pen

	// Now draw the line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);
	// Restore the old pen
	pDC->SelectObject(pOldPen);	
}

void CLine::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_EndPoint;
	}
	else
	{
		ar >> m_EndPoint;
	}
}
