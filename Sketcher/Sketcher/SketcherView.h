
// SketcherView.h : CSketcherView 類別的介面
//

#pragma once
#include "atltypes.h"
#include "Element.h" //
#include <memory>	//

class CSketcherView : public CScrollView
{
protected: // 僅從序列化建立
	CSketcherView();
	DECLARE_DYNCREATE(CSketcherView)

// 屬性
public:
	CSketcherDoc* GetDocument() const;

// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CSketcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	// First point recorded for an element
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	std::shared_ptr<CElement> m_pTempElement;
protected:
	CElement* CreateElement(void) const;	// Create a new element on the heap
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnViewScale();
	int m_Scale;
};

#ifndef _DEBUG  // SketcherView.cpp 中的偵錯版本
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

