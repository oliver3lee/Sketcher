#include "stdafx.h"
#include "Text.h"
#include <algorithm>

IMPLEMENT_SERIAL(CText, CElement, VERSION_NUMBER)
CText::CText(const CPoint& start, const CPoint& end, const CString& aString, const LOGFONT& logfont, COLORREF color) : CElement(start, color, 0, 0)
{
	m_String = aString;
	m_Logfont = logfont;
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(0, 20);
}

CText::~CText()
{
}

CText::CText()
{

}

void CText::Draw(CDC* pDC)
{
	//CFont Font;
	//VERIFY(Font.CreateFontIndirect(&m_Logfont));
	//pDC->SelectObject(&m_Font);
	pDC->SetTextColor(m_Color);
	pDC->SetBkMode(TRANSPARENT);
	pDC->ExtTextOut(m_StartPoint.x, m_StartPoint.y, 0, nullptr, m_String, nullptr);

	//Font.DeleteObject();
}

void CText::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_String;
	}
	else
	{
		ar >> m_String;
	}
}