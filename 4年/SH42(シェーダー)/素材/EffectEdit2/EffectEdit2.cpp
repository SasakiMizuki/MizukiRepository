// EffectEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EffectEdit2.h"

#include "MainFrm.h"
#include "EffectDoc.h"
#include "UIElements.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	NOREG

/////////////////////////////////////////////////////////////////////////////
// CEffectEditCommandLineInfo

CEffectEditCommandLineInfo::CEffectEditCommandLineInfo()
{
	m_bUseExternalEditor = FALSE;
	m_WaitingForSearchPath = FALSE;
}

void CEffectEditCommandLineInfo::ParseParam(const TCHAR* pszParam,BOOL bFlag, BOOL bLast)
{
	if (bFlag && CompareString(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, pszParam, -1, _T("ee"), -1) == CSTR_EQUAL)
		m_bUseExternalEditor = TRUE;
	else if (bFlag && CompareString(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, pszParam, -1, _T("mp"), -1) == CSTR_EQUAL)
		m_WaitingForSearchPath = TRUE;
	else if (!bFlag && m_WaitingForSearchPath)
	{
		m_WaitingForSearchPath = FALSE;
		m_MediaSearchPath = pszParam;
	}
	else
		CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

BOOL GetMediaPath(TCHAR* strMedia, size_t MaxCch, bool EffectEditSubDir)
{
	GetModuleFileName(NULL, strMedia, MaxCch);
	strMedia[MaxCch - 1] = 0;

	WCHAR* LastSlash = wcsrchr(strMedia, _T('\\'));
	if (LastSlash)
	{
		*LastSlash = 0;
	}

//	StringCchCat(strMedia, MaxCch, _T("\\..\\..\\..\\Samples\\Media\\"));
	StringCchCat(strMedia, MaxCch, _T("\\Media\\"));

	DWORD Attribs = GetFileAttributes(strMedia);

	if (Attribs != ((DWORD)-1) && (Attribs & FILE_ATTRIBUTE_DIRECTORY) != 0)
	{
		if (EffectEditSubDir)
		{
			TCHAR strMedia2[MAX_PATH];
			StringCchCopy(strMedia2, MAX_PATH, strMedia);
			StringCchCat(strMedia2, MAX_PATH, _T("EffectEdit2"));

			Attribs = GetFileAttributes(strMedia2);
			if (Attribs != ((DWORD)-1) && (Attribs & FILE_ATTRIBUTE_DIRECTORY) != 0)
				StringCchCopy(strMedia, MaxCch, strMedia2);
		}

		return TRUE;
	}

	return FALSE;
}

void CEffectEditDocManager::SetMediaPath(const CString& MediaPath)
{
	m_MediaPath = MediaPath;

	DWORD Attribs = GetFileAttributes(m_MediaPath);
	m_MediaPathIsValid = (Attribs != ((DWORD)-1) && (Attribs & FILE_ATTRIBUTE_DIRECTORY) != 0);
}

/////////////////////////////////////////////////////////////////////////////
// CEffectEditDocManager::DoPromptFileName - overridden to allow modification
// of initial dir
BOOL CEffectEditDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
	CFileDialog dlgFile(bOpenFileDialog);

	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

	BOOL bDefaultToMediaDir = AfxGetApp()->GetProfileInt(_T("Settings"),
		_T("DefaultToDXSDKMediaDir"), TRUE);
	if (bDefaultToMediaDir && m_MediaPathIsValid)
	{
		dlgFile.m_ofn.lpstrInitialDir = m_MediaPath;
	}

	CString strFilter;

	// Can't do the usual _AfxAppendFilterSuffix thing because that function
	// is local to docmgr.cpp
	strFilter += _T("エフェクト ファイル (*.fx)");
	strFilter += (TCHAR)'\0';	// next string please
	strFilter += _T("*.fx");
	strFilter += (TCHAR)'\0';	// last string
	dlgFile.m_ofn.nMaxCustFilter++;

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';	// next string please
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';	// last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	INT_PTR nResult = dlgFile.DoModal();
	fileName.ReleaseBuffer();
	return nResult == IDOK;
};


/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp

BEGIN_MESSAGE_MAP(CEffectEditApp, CWinApp)
	//{{AFX_MSG_MAP(CEffectEditApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_CHOOSEFONT, OnViewChooseFont)
	ON_COMMAND(ID_VIEW_TABS, OnViewTabOptions)
	ON_COMMAND(ID_FILE_DEFAULTTODXSDKMEDIAFOLDER, OnFileDefaultToDxsdkMediaFolder)
	ON_UPDATE_COMMAND_UI(ID_FILE_DEFAULTTODXSDKMEDIAFOLDER, OnUpdateFileDefaultToDxsdkMediaFolder)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp construction

CEffectEditApp::CEffectEditApp()
{
	m_bRenderContinuously = true;
	m_bAppActivated = false;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEffectEditApp object

CEffectEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp initialization

BOOL CEffectEditApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//	of your final executable, you should remove from the following
	//	the specific initialization routines you do not need.

#if(_MFC_VER < 0x0700)
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	// Change the registry key under which our settings are stored.
#ifdef NOREG
	{
		TCHAR szPath[_MAX_PATH];
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szFName[_MAX_FNAME];
		_tsplitpath(__targv[0], szDrive, szDir, szFName, NULL);
		_tmakepath(szPath, szDrive, szDir, szFName, _T(".ini"));
		if (m_pszProfileName)
			free((void*)m_pszProfileName);
		m_pszProfileName = _tcsdup(szPath);
	}
#else
	SetRegistryKey(_T("Microsoft"));
#endif

	LoadStdProfileSettings(8);	// Load standard INI file options (including MRU)

	if (!AfxInitRichEdit())
		return FALSE;

	// Register the application's document templates.  Document templates
	//	serve as the connection between documents, frame windows and views.

	CEffectEditDocManager* DocMgr = new CEffectEditDocManager;
	m_pDocManager = DocMgr;

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEffectDoc),
		RUNTIME_CLASS(CMainFrame),		// main SDI frame window
		RUNTIME_CLASS(CRenderView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CEffectEditCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	TCHAR strMedia[MAX_PATH];
	if (!cmdInfo.MediaSearchPath().IsEmpty())
	{
		DocMgr->SetMediaPath(cmdInfo.MediaSearchPath());
		StringCchCopy(strMedia, MAX_PATH, cmdInfo.MediaSearchPath());
		DXUTSetMediaSearchPath(strMedia);
	}
	else if (GetMediaPath(strMedia, MAX_PATH, false))
	{
		DocMgr->SetMediaPath(strMedia);
		DXUTSetMediaSearchPath(strMedia);
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	if (cmdInfo.UseExternalEditor())
		m_pMainWnd->PostMessage(WM_COMMAND, ID_EDIT_USEEXTERNALEDITOR);

	return TRUE;
}

void CEffectEditApp::OnFileDefaultToDxsdkMediaFolder()
{
	BOOL bDefaultToMediaDir = GetProfileInt(_T("Settings"), _T("DefaultToDXSDKMediaDir"), TRUE);
	bDefaultToMediaDir = !bDefaultToMediaDir;
	WriteProfileInt(_T("Settings"), _T("DefaultToDXSDKMediaDir"), bDefaultToMediaDir);
}

void CEffectEditApp::OnUpdateFileDefaultToDxsdkMediaFolder(CCmdUI* pCmdUI)
{
	BOOL bDefaultToMediaDir = GetProfileInt(_T("Settings"), _T("DefaultToDXSDKMediaDir"), TRUE);
	pCmdUI->SetCheck(bDefaultToMediaDir);
	pCmdUI->Enable(static_cast<CEffectEditDocManager*>(m_pDocManager)->IsMediaPathValid());
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CEdit	m_edtHelp;
	CString m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	TCHAR szFile[MAX_PATH];
	CString strVersion;
	UINT cb;
	DWORD dwHandle;
	BYTE FileVersionBuffer[1024];
	VS_FIXEDFILEINFO* pVersion = NULL;

	GetModuleFileName(NULL, szFile, MAX_PATH);

	cb = GetFileVersionInfoSize(szFile, &dwHandle/*ignored*/);
	if (cb > 0)
	{
		if (cb > sizeof(FileVersionBuffer))
			cb = sizeof(FileVersionBuffer);

		if (GetFileVersionInfo(szFile, 0, cb, FileVersionBuffer))
		{
			pVersion = NULL;
			if (VerQueryValue(FileVersionBuffer, L"\\", (VOID**)&pVersion, &cb)
				&& pVersion != NULL) 
			{
				strVersion.Format(L"Version %d.%02d.%02d.%04d",
					HIWORD(pVersion->dwFileVersionMS),
					LOWORD(pVersion->dwFileVersionMS),
					HIWORD(pVersion->dwFileVersionLS),
					LOWORD(pVersion->dwFileVersionLS));
			}
		}
	}

	//{{AFX_DATA_INIT(CAboutDlg)
	m_strVersion = _T("EffectEdit2 ") + strVersion;
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HELP_EDITBOX, m_edtHelp);
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CEffectEditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp message handlers


BOOL CEffectEditApp::OnIdle(LONG lCount)
{
	if (m_bRenderContinuously)
	{
		CWinApp::OnIdle(lCount);
		if (!m_bAppActivated)
			Sleep(50);
		m_pMainWnd->SendMessage(WM_COMMAND, ID_VIEW_RENDER);
		return TRUE;	// always request more time
	}
	else
	{
		return CWinApp::OnIdle(lCount);
	}
}

void CEffectEditApp::ActivateTextView()
{
	((CMainFrame*)m_pMainWnd)->ActivateTextView();
}

void CEffectEditApp::ActivateErrorsView()
{
	((CMainFrame*)m_pMainWnd)->ActivateErrorsView();
}

void CEffectEditApp::ActivateOptionsView()
{
	((CMainFrame*)m_pMainWnd)->ActivateOptionsView();
}

void CEffectEditApp::Locate(int nCol, int nRow)
{
	((CMainFrame*)m_pMainWnd)->Locate(nCol, nRow);
}

void CEffectEditApp::SelectLine(int iLine)
{
	((CMainFrame*)m_pMainWnd)->SelectLine(iLine);
}

void CEffectEditApp::OnViewChooseFont()
{
	CFontDialog fontDialog;
	DWORD dwFontSize = GetProfileInt(_T("Settings"), _T("FontSize"), 10);
	CString strFontName = GetProfileString(_T("Settings"), _T("FontName"), _T("ＭＳ ゴシック"));

	HDC hdc = GetDC(NULL);
	fontDialog.m_lf.lfHeight = -MulDiv(dwFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(NULL, hdc);
	fontDialog.m_lf.lfWeight = FW_NORMAL;
	StringCchCopy(fontDialog.m_lf.lfFaceName, 32, strFontName);
	fontDialog.m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
	fontDialog.m_cf.Flags &= ~CF_EFFECTS;

	if (IDOK == fontDialog.DoModal())
	{
		CFont font;
		if (NULL != font.CreateFontIndirect(&fontDialog.m_lf))
		{
			font.DeleteObject();
			int newSize = fontDialog.GetSize() / 10;
			CString strNewFontName = fontDialog.GetFaceName();
			WriteProfileInt(_T("Settings"), _T("FontSize"), newSize);
			WriteProfileString(_T("Settings"), _T("FontName"), strNewFontName);

			((CMainFrame*)m_pMainWnd)->TextViewUpdateFont();
		}
	}
}

void CEffectEditApp::OnViewTabOptions()
{
	CTabOptionsDialog tabDialog;

	BOOL bKeepTabs = GetProfileInt(_T("Settings"), _T("Keep Tabs"), FALSE);
	INT numSpaces = GetProfileInt(_T("Settings"), _T("Num Spaces"), 4);

	tabDialog.m_numSpaces = numSpaces;

	if (bKeepTabs)
		tabDialog.m_TabsOrSpacesRadio = 0;
	else
		tabDialog.m_TabsOrSpacesRadio = 1;

	if (IDOK == tabDialog.DoModal())
	{
		numSpaces = tabDialog.m_numSpaces;
		if (tabDialog.m_TabsOrSpacesRadio == 0)
			bKeepTabs = TRUE;
		else
			bKeepTabs = FALSE;

		WriteProfileInt(_T("Settings"), _T("Keep Tabs"), bKeepTabs);
		WriteProfileInt(_T("Settings"), _T("Num Spaces"), numSpaces);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabOptionsDialog dialog


CTabOptionsDialog::CTabOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTabOptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabOptionsDialog)
	m_numSpaces = 0;
	m_TabsOrSpacesRadio = -1;
	//}}AFX_DATA_INIT
}


void CTabOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabOptionsDialog)
	DDX_Text(pDX, IDC_NUMSPACES, m_numSpaces);
	DDV_MinMaxUInt(pDX, m_numSpaces, 1, 8);
	DDX_Radio(pDX, IDC_TABS, m_TabsOrSpacesRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabOptionsDialog, CDialog)
	//{{AFX_MSG_MAP(CTabOptionsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabOptionsDialog message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	bool bSuccess = false;

	HMODULE hModule = NULL;
	HRSRC rsrc;
	HGLOBAL hgData;
	LPVOID pvData;
	DWORD cbData;

	rsrc = FindResource(hModule, MAKEINTRESOURCE(IDR_HELP_TXT), L"TEXT");
	if (rsrc != NULL)
	{
		cbData = SizeofResource(hModule, rsrc);
		if (cbData > 0)
		{
			hgData = LoadResource(hModule, rsrc);
			if (hgData != NULL)
			{
				pvData = LockResource(hgData);
				if (pvData != NULL)
				{
					TCHAR* strBuffer = (TCHAR*)pvData;
					strBuffer[cbData / sizeof(TCHAR)] = _T('\0');

					m_edtHelp.SetWindowText(strBuffer);
					bSuccess = true;
				}
			}
		}
	}

	if (!bSuccess)
	{
		m_edtHelp.SetWindowText(_T("エラー: help.txt がオープンできません。"));
	}

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}
