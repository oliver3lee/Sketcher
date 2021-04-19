// TextDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "Sketcher.h"
#include "TextDialog.h"
#include "afxdialogex.h"


// CTextDialog 對話方塊

IMPLEMENT_DYNAMIC(CTextDialog, CDialogEx)

CTextDialog::CTextDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDialog::IDD, pParent)
	, m_TextString(_T(""))
{

}

CTextDialog::~CTextDialog()
{
}

void CTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_TextString);
	DDV_MaxChars(pDX, m_TextString, 200);
}


BEGIN_MESSAGE_MAP(CTextDialog, CDialogEx)
	ON_BN_CLICKED(IDC_FONT_EDIT, &CTextDialog::OnBnClickedFontEdit)
END_MESSAGE_MAP()


// CTextDialog 訊息處理常式


void CTextDialog::OnBnClickedFontEdit()
{
	CFontDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		// Create the font using the selected font from CFontDialog.
		//LOGFONT lf;
		memcpy(&m_Logfont, dlg.m_cf.lpLogFont, sizeof(LOGFONT));

		/*CFont m_Font;
		VERIFY(m_Font.CreateFontIndirect(&m_Logfont));
		CClientDC dc(this);
		CFont *def_font = dc.SelectObject(&m_Font);
		dc.TextOut(100, 100, m_TextString, m_TextString.GetLength());
		dc.SelectObject(def_font);*/
		
		// Done with the font. Delete the font object.
		//font.DeleteObject();
	}
}
