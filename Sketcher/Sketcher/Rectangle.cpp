#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>

IMPLEMENT_SERIAL(CRectangle, CElement, VERSION_NUMBER)

CRectangle::CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int style, int penWidth) : CElement(start, color, style, penWidth)
{
	// Normalize the rectangle defining points
	m_StartPoint = CPoint((std::min)(start.x, end.x), (std::min)(start.y, end.y));
	m_BottomRight = CPoint((std::max)(start.x, end.x), (std::max)(start.y, end.y));

	// Ensure width and height between the points is at least 2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
	{
		m_BottomRight.x = m_StartPoint.x + 2;
	}
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
	{
		m_BottomRight.y = m_StartPoint.y + 2;
	}

	// Define the enclosing rectangle
	m_EnclosingRect = CRect(m_StartPoint, m_BottomRight);
	int width(0 == penWidth ? 1 : penWidth);
	m_EnclosingRect.InflateRect(width, width);
}


CRectangle::CRectangle()
{

}

CRectangle::~CRectangle()
{
}

void CRectangle::ChangeSecondPoint(const CPoint& secondPoint)
{
	m_BottomRight = secondPoint;
}

// Draw a CRectangle object
void CRectangle::Draw(CDC* pDC)
{
	if (false == m_bCreatePen)
	{
		CreatePen(m_aPen);
		m_bCreatePen = true;
		m_bReturn = CreateBrush(m_aBrush);
		OutputDebugString(_T("false"));
	}

	// Select the pen and the null brush
	CPen* pOldPen;
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

	// Draw the rectangle
	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	// Restore the old pen and brush
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CRectangle::Serialize(CArchive& ar)
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