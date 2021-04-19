#pragma once
#include "Element.h"
class CRectangle :public CElement
{
DECLARE_SERIAL(CRectangle)
public:
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int style, int penWidth);

	virtual ~CRectangle(void);
	virtual void Draw(CDC* pDC) override;	//Function to display a rectangle
	virtual void ChangeSecondPoint(const CPoint& secondPoint);
	// Constructor for a rectangle object
	virtual void Serialize(CArchive& ar) override;

protected:
	CPoint m_BottomRight;	// Bottom-right point for the rectangle
	CPen m_aPen;
	bool m_bCreatePen = false;
	CBrush m_aBrush;
	bool m_bReturn;
	CRectangle(void);		// Default constructor - should not be used
};

