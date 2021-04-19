#pragma once
#include "ElementStyle.h"
#include "Define.h"
// CElement ©R¥O¥Ø¼Ð
static const UINT VERSION_NUMBER = 1001;
class CElement : public CObject
{
DECLARE_SERIAL(CElement)
protected:
	CPoint m_StartPoint;		// Element position
	int m_PenWidth;				// Pen width
	COLORREF m_Color;			// Color of an element
	CRect m_EnclosingRect;		// Rectangle enclosing an element
	int m_Style;

public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC) {}	// Virtual draw operation
	virtual void ChangeSecondPoint(const CPoint& secondPoint) {}
	virtual void Serialize(CArchive& ar) override;


	// Get the element enclosing rectangle
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	// Constructors protected so they cannot be called outside the class
	CElement();
	CElement(const CPoint& start, COLORREF color, int style, int penWidth = 1);

	void CreatePen(CPen& m_aPen)
	{
		if (!m_aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
		{
			// Pen creation failed
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}

	bool CreateBrush(CBrush& m_aBrush)
	{
		switch (m_Style)
		{
		case NOFILL:
		{
			return false;
		}
		case FILL:
		{
			m_aBrush.CreateSolidBrush(m_Color);
			return true;
		}
		case CROSS:
		{
			m_aBrush.CreateHatchBrush(HS_DIAGCROSS, m_Color);
			return true;
		}
		case FDIAGONAL:
		{
			m_aBrush.CreateHatchBrush(HS_FDIAGONAL, m_Color);
			return true;
		}
		default:
		{
			m_aBrush.CreateHatchBrush(HS_VERTICAL, m_Color);
			return true;
		}
		}
	}
};


