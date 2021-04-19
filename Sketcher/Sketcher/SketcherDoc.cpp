
// SketcherDoc.cpp : CSketcherDoc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#include "PenDialog.h"
#endif

#include "SketcherDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
	ON_COMMAND(ID_STYLE_CROSS, &CSketcherDoc::OnStyleCross)
	ON_COMMAND(ID_STYLE_FDIAGONAL, &CSketcherDoc::OnStyleFdiagonal)
	ON_COMMAND(ID_STYLE_VERTICAL, &CSketcherDoc::OnStyleVertical)
	ON_COMMAND(ID_STYLE_NULL, &CSketcherDoc::OnStyleNull)
	ON_COMMAND(ID_STYLE_FILL, &CSketcherDoc::OnStyleFill)
	ON_UPDATE_COMMAND_UI(ID_STYLE_NULL, &CSketcherDoc::OnUpdateStyleNull)
	ON_UPDATE_COMMAND_UI(ID_STYLE_FILL, &CSketcherDoc::OnUpdateStyleFill)
	ON_UPDATE_COMMAND_UI(ID_STYLE_CROSS, &CSketcherDoc::OnUpdateStyleCross)
	ON_UPDATE_COMMAND_UI(ID_STYLE_FDIAGONAL, &CSketcherDoc::OnUpdateStyleFdiagonal)
	ON_UPDATE_COMMAND_UI(ID_STYLE_VERTICAL, &CSketcherDoc::OnUpdateStyleVertical)
	ON_COMMAND(ID_PEN_WIDTH, &CSketcherDoc::OnPenWidth)
	ON_COMMAND(ID_ELEMENT_TEXT, &CSketcherDoc::OnElementText)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CSketcherDoc::OnUpdateElementText)
END_MESSAGE_MAP()


// CSketcherDoc 建構/解構

CSketcherDoc::CSketcherDoc() :m_Element(ElementType::LINE), m_Color(ElementColor::BLACK), m_Style(ElementStyle::NOFILL)	// 初始化
{
	m_PenWidth = 1;
}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)

	return TRUE;
}




// CSketcherDoc 序列化

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << static_cast<COLORREF>(m_Color)
			<< static_cast<int>(m_Element)
			<< static_cast<int>(m_Style)
			<< m_PenWidth;

		ar << m_Sketch.size();

		for (auto& pElement : m_Sketch)
		{
			ar << pElement.get();
		}
	}
	else
	{
		COLORREF color(0);
		int elementType(0);
		int elementStyle(0);
		ar >> color
			>> elementType
			>> elementStyle
			>> m_PenWidth;

		m_Color = static_cast<ElementColor>(color);
		m_Element = static_cast<ElementType>(elementType);
		m_Style = static_cast<ElementStyle>(elementStyle);

		size_t elementCount(0);
		ar >> elementCount;
		CElement* pElement;
		for (size_t i = 0; i < elementCount; ++i)
		{
			ar >> pElement;
			m_Sketch.push_back(std::shared_ptr<CElement>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketcherDoc 診斷

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc 命令

void CSketcherDoc::OnColorBlack()
{
	if (ElementColor::BLACK != m_Color)
	{
		m_Color = ElementColor::BLACK;	// set the drawing color to green
		SetModifiedFlag();				// Set the modified flag
	}
}


void CSketcherDoc::OnColorRed()
{
	if (ElementColor::RED != m_Color)
	{
		m_Color = ElementColor::RED;	// set the drawing color to green
		SetModifiedFlag();				// Set the modified flag
	}
}


void CSketcherDoc::OnColorGreen()
{
	if (ElementColor::GREEN != m_Color)
	{
		m_Color = ElementColor::GREEN;	// set the drawing color to green
		SetModifiedFlag();				// Set the modified flag
	}
}


void CSketcherDoc::OnColorBlue()
{
	if (ElementColor::BLUE != m_Color)
	{
		m_Color = ElementColor::BLUE;	// set the drawing color to blue
		SetModifiedFlag();				// Set the modified flag
	}
}


void CSketcherDoc::OnElementLine()
{
	if (ElementType::LINE != m_Element)
	{
		m_Element = ElementType::LINE;	// Set element type as a line
		SetModifiedFlag();				// Set the modified flag
	}
}


void CSketcherDoc::OnElementRectangle()
{
	if (ElementType::RECTANGLE != m_Element)
	{
		m_Element = ElementType::RECTANGLE;	// Set element type as a Rectangle
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnElementCircle()
{
	if (ElementType::CIRCLE != m_Element)
	{
		m_Element = ElementType::CIRCLE;	// Set element type as a Circle
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnElementText()
{
	m_Element = ElementType::TEXT;
}


/////
void CSketcherDoc::OnStyleNull()
{
	if (ElementStyle::NOFILL != m_Style)
	{
		m_Style = ElementStyle::NOFILL;
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnStyleFill()
{
	if (ElementStyle::FILL != m_Style)
	{
		m_Style = ElementStyle::FILL;
		SetModifiedFlag();					// Set the modified flag
	}
}

void CSketcherDoc::OnStyleCross()
{
	if (ElementStyle::CROSS != m_Style)
	{
		m_Style = ElementStyle::CROSS;
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnStyleFdiagonal()
{
	if (ElementStyle::FDIAGONAL != m_Style)
	{
		m_Style = ElementStyle::FDIAGONAL;
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnStyleVertical()
{
	if (ElementStyle::VERTICAL != m_Style)
	{
		m_Style = ElementStyle::VERTICAL;
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnPenWidth()
{
	CPenDialog aDlg;
	aDlg.m_PenWidth = m_PenWidth;

	if (IDOK == aDlg.DoModal())
	{
		m_PenWidth = aDlg.m_PenWidth;
		SetModifiedFlag();					// Set the modified flag
	}
}


void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is black
	pCmdUI->SetCheck(ElementColor::BLACK == m_Color);
}

void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is red
	pCmdUI->SetCheck(ElementColor::RED == m_Color);
}


void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is green
	pCmdUI->SetCheck(ElementColor::GREEN == m_Color);
}


void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is blue
	pCmdUI->SetCheck(ElementColor::BLUE == m_Color);
}


void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a line
	pCmdUI->SetCheck(ElementType::LINE == m_Element);
}


void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a Rectangle
	pCmdUI->SetCheck(ElementType::RECTANGLE == m_Element);
}


void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a circle
	pCmdUI->SetCheck(ElementType::CIRCLE == m_Element);
}


void CSketcherDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(ElementType::TEXT == m_Element);
}


////////////
void CSketcherDoc::OnUpdateStyleNull(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a
	pCmdUI->SetCheck(ElementStyle::NOFILL == m_Style);
}


void CSketcherDoc::OnUpdateStyleFill(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a
	pCmdUI->SetCheck(ElementStyle::FILL == m_Style);
}


void CSketcherDoc::OnUpdateStyleCross(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a
	pCmdUI->SetCheck(ElementStyle::CROSS == m_Style);
}


void CSketcherDoc::OnUpdateStyleFdiagonal(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a
	pCmdUI->SetCheck(ElementStyle::FDIAGONAL == m_Style);
}


void CSketcherDoc::OnUpdateStyleVertical(CCmdUI *pCmdUI)
{
	// Set the check if the current element is a
	pCmdUI->SetCheck(ElementStyle::VERTICAL == m_Style);
}

