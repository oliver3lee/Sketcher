#pragma once
#include "Element.h"
class CLine: public CElement
{
DECLARE_SERIAL(CLine)
public:
	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int penWidth);

	virtual ~CLine(void);
	virtual void Draw(CDC* pDC) override;	// Function to display a line
	virtual void ChangeSecondPoint(const CPoint& secondPoint) override;
	virtual void Serialize(CArchive& ar) override;


protected:
	CPoint m_EndPoint;	// End point of line
	CLine(void);	// Default constructor should not be used
	CPen m_aPen;
	bool m_bCreatePen = false;
};

