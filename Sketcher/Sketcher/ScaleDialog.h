#pragma once
#include "afxcmn.h"


// CScaleDialog 對話方塊

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CScaleDialog();

// 對話方塊資料
	enum { IDD = IDD_SCLAE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	int m_Scale;
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
};
