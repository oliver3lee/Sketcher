#pragma once
#include "afxcmn.h"


// CScaleDialog ��ܤ��

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CScaleDialog();

// ��ܤ�����
	enum { IDD = IDD_SCLAE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	int m_Scale;
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
};
