#pragma once


// CPenDialog ��ܤ��

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CPenDialog();

// ��ܤ�����
	enum { IDD = IDD_PENWIDTH_DLG };

	int m_PenWidth; //���e

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPenwidth0();
	afx_msg void OnPenwidth1();
	afx_msg void OnPenwidth2();
	afx_msg void OnPenwidth3();
	afx_msg void OnPenwidth4();
	afx_msg void OnPenwidth5();
};