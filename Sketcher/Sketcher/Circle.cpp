#include "stdafx.h"
#include "Circle.h"
#include <cmath>

IMPLEMENT_SERIAL(CCircle, CElement, VERSION_NUMBER)

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color, int style, int penWidth) : CElement(start, color, style, penWidth)
{
	long radius = static_cast<long> (sqrt(static_cast<double>((end.x - start.x)*(end.x - start.x) + (end.y - start.y)*(end.y - start.y))));
	if (radius < 1L)
	{
		radius = 1L;
	}

	m_StartPoint = CPoint(start.x - radius, start.y - radius);
	m_BottomRight = CPoint(start.x + radius, start.y + radius);

	m_EnclosingRect = CRect(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	int width(0 == penWidth ? 1 : penWidth);
	m_EnclosingRect.InflateRect(width, width);
	
}

CCircle::CCircle()
{
}

CCircle::~CCircle()
{
}

void CCircle::ChangeSecondPoint(const CPoint& secondPoint)
{
	m_BottomRight = secondPoint;
}

// Draw a circle
void CCircle::Draw(CDC* pDC)
{
	if (false == m_bCreatePen)
	{
		CreatePen(m_aPen);
		m_bCreatePen = true;
		m_bReturn = CreateBrush(m_aBrush);
	}

	CPen* pOldPen;
	// Select the pen and the null brush
	 pOldPen = pDC->SelectObject(&m_aPen);

	CBrush* pOldBrush;
	if (false == m_bReturn)
	{
		pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	}
	else
	{
		pOldBrush = pDC->SelectObject(&m_aBrush);
	}

	// Now draw the circle
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldPen);		// Restore the old pen
	pDC->SelectObject(pOldBrush);	// Restore the old brush
}

void CCircle::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_BottomRight;
	}
	else
	{
		ar >> m_BottomRight;
	}
}