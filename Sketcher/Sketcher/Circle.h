#pragma once
#include "Element.h"
class CCircle: public CElement
{
DECLARE_SERIAL(CCircle)
public:
	// Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, int style, int penWidth);

	virtual ~CCircle(void);
	virtual void Draw(CDC* pDC) override;	// Function to display a circle
	virtual void ChangeSecondPoint(const CPoint& secondPoint) override;
	virtual void Serialize(CArchive& ar) override;

protected:
	CPoint m_BottomRight;	// Bottom-right point for defining rectangle
	CPen m_aPen;
	bool m_bCreatePen = false;
	CBrush m_aBrush;
	bool m_bReturn;
	CCircle(void);			// Default constructor
};

