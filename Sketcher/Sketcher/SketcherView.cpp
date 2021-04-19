
// SketcherView.cpp : CSketcherView ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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
	// �зǦC�L�R�O
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_SCALE, &CSketcherView::OnViewScale)
END_MESSAGE_MAP()

// CSketcherView �غc/�Ѻc

CSketcherView::CSketcherView() : m_FirstPoint(CPoint(0, 0)), m_SecondPoint(CPoint(0, 0))
{
	m_Scale = 1;
}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CSketcherView �yø

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();	// pDoc��Ъ�l��
	ASSERT_VALID(pDoc);	// ���Ҵ�ЬO���T��
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

// CSketcherView �C�L

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  �[�J�C�L�e�B�~����l�]�w
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  �[�J�C�L�᪺�M���{���X
}


// CSketcherView �E�_

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView �T���B�z�`��


void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);	//�إ�CClientDC����Ө��o�ثeview��device context
	OnPrepareDC(&aDC);		//�]�w�޿�y�Э��I
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
		SetCapture();			//�����ƹ�
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
		InvalidateRect(aRect);	// �ǵ�������x�Τ����
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
