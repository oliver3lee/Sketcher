#pragma once
#include <memory>
#include "Element.h"
class CText: public CElement
{
DECLARE_SERIAL(CText)
public:
	CText(const CPoint& start, const CPoint& end, const CString& aString, const LOGFONT& lf, COLORREF color);

	//virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	virtual void Draw(CDC* pDC) override;
	virtual ~CText(void);
	virtual void Serialize(CArchive& ar) override;
protected:
	CString m_String;
	LOGFONT m_Logfont;
	CText(void);
};
