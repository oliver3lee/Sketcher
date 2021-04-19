
// Sketcher.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Sketcher.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "SketcherDoc.h"
#include "SketcherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherApp

BEGIN_MESSAGE_MAP(CSketcherApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSketcherApp::OnAppAbout)
	// �̾ڤ��R�O���з��ɮ�
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// �зǦC�L�]�w�R�O
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSketcherApp �غc

CSketcherApp::CSketcherApp()
{
	// TODO:  �H�ߤ@�� ID �r����N�U�������ε{�� ID �r��; ��ĳ��
	// �r��榡�� CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Sketcher.AppID.NoVersion"));

	// TODO:  �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}

// �Ȧ����@�� CSketcherApp ����

CSketcherApp theApp;


// CSketcherApp ��l�]�w

BOOL CSketcherApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// �ݭn�� AfxInitRichEdit2() �~��ϥ� RichEdit ���	
	// AfxInitRichEdit2();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO:  �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));
	LoadStdProfileSettings(4);  // ���J�з� INI �ɿﶵ (�]�t MRU)


	// �n�����ε{�������d���C���d���t�d�b���B
	// �ج[�����P�˵����i��s��
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_SketchTYPE,
		RUNTIME_CLASS(CSketcherDoc),
		RUNTIME_CLASS(CChildFrame), // �ۭq MDI �l�ج[
		RUNTIME_CLASS(CSketcherView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �إߥD MDI �ج[����
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// �u���b MDI ���ε{��������m�r���ɡA�~�I�s DragAcceptFiles
	// �o�|�ߧY�o�ͦb�]�w m_pMainWnd ����
	// �ҥΩ��}��
	m_pMainWnd->DragAcceptFiles();

	// ��R�з� Shell �R�O�BDDE�B�ɮ׶}�����ɪ��R�O�C
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �ҥ� DDE ����}��
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// �b�R�O�C�����w�������R�O�C�p�G�w�ϥ� 
	// /RegServer�B/Register�B/Unregserver �� /Unregister �Ұ����ε{���A�N�Ǧ^ FALSE�C
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �w�g��l�]�w�D�����A�ҥH��ܨç�s�ӵ���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSketcherApp::ExitInstance()
{
	// TODO:  �B�z��L�z�w�g�[�J���귽
	return CWinApp::ExitInstance();
}

// CSketcherApp �T���B�z�`��


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �����ܤ�������ε{���R�O
void CSketcherApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSketcherApp �T���B�z�`��



