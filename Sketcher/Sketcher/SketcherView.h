
// SketcherView.h : CSketcherView ���O������
//

#pragma once
#include "atltypes.h"
#include "Element.h" //
#include <memory>	//

class CSketcherView : public CScrollView
{
protected: // �ȱq�ǦC�ƫإ�
	CSketcherView();
	DECLARE_DYNCREATE(CSketcherView)

// �ݩ�
public:
	CSketcherDoc* GetDocument() const;

// �@�~
public:

// �мg
public:
	virtual void OnDraw(CDC* pDC);  // �мg�H�yø���˵�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �{���X��@
public:
	virtual ~CSketcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
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

#ifndef _DEBUG  // SketcherView.cpp ������������
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

