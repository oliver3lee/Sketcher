// PenDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "Sketcher.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// CPenDialog 對話方塊

IMPLEMENT_DYNAMIC(CPenDialog, CDialogEx)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/) : CDialogEx(CPenDialog::IDD, pParent), m_PenWidth(0)
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
	ON_BN_CLICKED(IDC_PENWIDTH0, &CPenDialog::OnPenwidth0)
	ON_BN_CLICKED(IDC_PENWIDTH1, &CPenDialog::OnPenwidth1)
	ON_BN_CLICKED(IDC_PENWIDTH2, &CPenDialog::OnPenwidth2)
	ON_BN_CLICKED(IDC_PENWIDTH3, &CPenDialog::OnPenwidth3)
	ON_BN_CLICKED(IDC_PENWIDTH4, &CPenDialog::OnPenwidth4)
	ON_BN_CLICKED(IDC_PENWIDTH5, &CPenDialog::OnPenwidth5)
END_MESSAGE_MAP()


// CPenDialog 訊息處理常式


BOOL CPenDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	switch (m_PenWidth)
	{
	case 1:
	{
		CheckDlgButton(IDC_PENWIDTH1, 1);
		break;
	}
	case 2:
	{
		CheckDlgButton(IDC_PENWIDTH2, 1);
		break;
	}
	case 3:
	{
		CheckDlgButton(IDC_PENWIDTH3, 1);
		break;
	}
	case 4:
	{
		CheckDlgButton(IDC_PENWIDTH4, 1);
		break;
	}
	case 5:
	{
		CheckDlgButton(IDC_PENWIDTH5, 1);
		break;
	}
	default:
	{
		CheckDlgButton(IDC_PENWIDTH0, 1);
		break;
	}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION:  OCX 屬性頁應傳回 FALSE
}


void CPenDialog::OnPenwidth0()
{
	m_PenWidth = 0;
}


void CPenDialog::OnPenwidth1()
{
	m_PenWidth = 1;
}


void CPenDialog::OnPenwidth2()
{
	m_PenWidth = 2;
}


void CPenDialog::OnPenwidth3()
{
	m_PenWidth = 3;
}


void CPenDialog::OnPenwidth4()
{
	m_PenWidth = 4;
}


void CPenDialog::OnPenwidth5()
{
	m_PenWidth = 5;
}
