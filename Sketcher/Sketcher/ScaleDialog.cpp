// ScaleDialog.cpp : ��@��
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// CScaleDialog ��ܤ��

IMPLEMENT_DYNAMIC(CScaleDialog, CDialogEx)

CScaleDialog::CScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScaleDialog::IDD, pParent)
	, m_Scale(0)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCALE, m_Scale);
	DDV_MinMaxInt(pDX, m_Scale, 1, 8);
	DDX_Control(pDX, IDC_SPIN_SCALE, m_Spin);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialogEx)
END_MESSAGE_MAP()


// CScaleDialog �T���B�z�`��


BOOL CScaleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Spin.SetRange(1, 8);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION:  OCX �ݩʭ����Ǧ^ FALSE
}
