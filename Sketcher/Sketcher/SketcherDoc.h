
// SketcherDoc.h : CSketcherDoc 類別的介面
//


#pragma once

#include "ElementType.h"
#include "ElementColor.h"
#include "ElementStyle.h"
#include "Element.h"
#include <list>
#include <memory>
typedef std::list<std::shared_ptr<CElement>>::const_iterator SketchIterator;


class CSketcherDoc : public CDocument
{
protected: // 僅從序列化建立
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// 屬性
public:

// 作業
public:

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 程式碼實作
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 為搜尋處理常式設定搜尋內容的 Helper 函式
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	
protected:
	ElementType m_Element;	// Current element type
	ElementColor m_Color;	// Current element color
	ElementStyle m_Style;	// Current element style
	int m_PenWidth;
	std::list<std::shared_ptr<CElement>> m_Sketch; // A list contaning the sketch

public:
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();

	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementCircle();
	afx_msg void OnElementText();

	afx_msg void OnStyleCross();
	afx_msg void OnStyleFdiagonal();
	afx_msg void OnStyleVertical();
	afx_msg void OnStyleNull();
	afx_msg void OnStyleFill();

	afx_msg void OnUpdateStyleNull(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStyleFill(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStyleCross(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStyleFdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStyleVertical(CCmdUI *pCmdUI);
	afx_msg void OnPenWidth();

	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);

	ElementType GetElementType() const
	{
		return m_Element;
	}
	
	ElementColor GetElementColor() const
	{
		return m_Color;
	}

	ElementStyle GetElementStyle() const
	{
		return m_Style;
	}

	// Add a sketch element
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.push_back(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());	// Tell all the view
		SetModifiedFlag();	// Set the modified flag
	}

	//Delete a sketch element
	void DeleteElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.remove(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();	// Set the modified flag
	}

	SketchIterator begin() const
	{
		return std::begin(m_Sketch);
	}
	SketchIterator end() const
	{
		return std::end(m_Sketch);
	}

	int GetPenWidth() const
	{
		return m_PenWidth;
	}
};

