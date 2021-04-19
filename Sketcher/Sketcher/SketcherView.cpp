
// SketcherView.cpp : CSketcherView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "TextDialog.h"
#include "Text.h"
#include "ScaleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CScrollView)

BEGIN_MESSAGE_MAP(CSketcherView, CScrollView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_SCALE, &CSketcherView::OnViewScale)
END_MESSAGE_MAP()

// CSketcherView 建構/解構

CSketcherView::CSketcherView() : m_FirstPoint(CPoint(0, 0)), m_SecondPoint(CPoint(0, 0))
{
	m_Scale = 1;
}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CSketcherView 描繪

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();	// pDoc游標初始化
	ASSERT_VALID(pDoc);	// 驗證游標是正確的
	if (!pDoc)
	{
		return;
	}

	// Draw the sketch
	for (auto iter = pDoc->begin(); pDoc->end() != iter; ++iter)
	{
		std::shared_ptr<CElement> pElement(*iter);
		if (pDC->RectVisible(pElement->GetEnclosingRect()))	// Element visible?
		{
			pElement->Draw(pDC);
		}
	}
}

// CSketcherView 列印

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印前額外的初始設定
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印後的清除程式碼
}


// CSketcherView 診斷

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView 訊息處理常式


void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);	//建立CClientDC物件來取得目前view的device context
	OnPrepareDC(&aDC);		//設定邏輯座標原點
	aDC.DPtoLP(&point);		
	CSketcherDoc* pDoc = GetDocument();
	if (ElementType::TEXT == pDoc->GetElementType())
	{
		CTextDialog aDlg;
		if (IDOK == aDlg.DoModal())
		{
			CSize textExtent = aDC.GetOutputTextExtent(aDlg.m_TextString);
			textExtent.cx *= m_Scale;
			textExtent.cy *= m_Scale;
			std::shared_ptr<CElement> pTextElement = std::make_shared<CText>(point, point + textExtent, aDlg.m_TextString, aDlg.m_Logfont, static_cast<COLORREF>(pDoc->GetElementColor()));

			pDoc->AddElement(pTextElement);
			pDoc->UpdateAllViews(nullptr, 0, pTextElement.get());
		}
	}
	else
	{
		m_FirstPoint = point;	// Record the cursor position
		SetCapture();			//捕捉滑鼠
	}
}


void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a Device Context object for the view
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);

	if ((nFlags & MK_LBUTTON) && (GetCapture() == this))
	{
		m_SecondPoint = point;	// Save the current cursor position

		if (m_pTempElement)	// Test for a previous temporary element
		{
			aDC.SetROP2(R2_NOTXORPEN);	// Set the drawing mode
			m_pTempElement->Draw(&aDC);
		}
		if (NULL == m_pTempElement)
		{
			m_pTempElement.reset(CreateElement());
		}
		
		m_pTempElement->ChangeSecondPoint(m_SecondPoint);
		m_pTempElement->Draw(&aDC);
		OutputDebugString(_T("D "));
	}
}



void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture() == this)
	{
		ReleaseCapture();	// Stop capturing mouse messages
		OutputDebugString(_T("R "));
	}

	// Make sure ther is an element
	if (m_pTempElement)
	{
		CRect aRect = m_pTempElement->GetEnclosingRect();
		GetDocument()->AddElement(m_pTempElement);

		CClientDC aDC(this);
		OnPrepareDC(&aDC);
		aDC.LPtoDP(aRect);
		m_pTempElement->Draw(&aDC);
		InvalidateRect(aRect);	// 傳給它指到矩形之游標
		m_pTempElement.reset();
	}
}



CElement* CSketcherView::CreateElement(void) const
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get the current element color
	COLORREF color = static_cast<COLORREF>(pDoc->GetElementColor());
	int style = static_cast<int>(pDoc->GetElementStyle());
	int penWidth(pDoc->GetPenWidth());

	// Select the element using the type stored in the document
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
	{
		return new CRectangle(m_FirstPoint, m_SecondPoint, color, style, penWidth);
	}
	case ElementType::CIRCLE:
	{
		return new CCircle(m_FirstPoint, m_SecondPoint, color, style, penWidth);
	}
	case ElementType::LINE:
	{
		return new CLine(m_FirstPoint, m_SecondPoint, color, penWidth);
	}
	default:
	{
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}
	}
}



void CSketcherView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pHint)
	{
		CClientDC aDC(this);
		OnPrepareDC(&aDC);

		CRect aRect = static_cast<CElement*>(pHint)->GetEnclosingRect();
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
	}
	else
	{
		InvalidateRect(nullptr);
	}
}


void CSketcherView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize DocSize(3000, 3000);	// Document size

	SetScrollSizes(MM_LOENGLISH, DocSize);	//Set mapping mode and document size
}


void CSketcherView::OnViewScale()
{
	CScaleDialog aDlg;
	aDlg.m_Scale = m_Scale;

	if (IDOK == aDlg.DoModal())
	{
		m_Scale = aDlg.m_Scale;
		InvalidateRect(nullptr);
	}
}
