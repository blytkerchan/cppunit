// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSDNIntegrator.h"
#include "MSDNIntegratorDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorDlg dialog

CMSDNIntegratorDlg::CMSDNIntegratorDlg( const CMSDNIntegratorConfig &config,
                                        CWnd* pParent /*=NULL*/)
	: CDialog(CMSDNIntegratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSDNIntegratorDlg)
	m_strCol       = _T("");
	m_strColNum    = _T("");
	m_strLangId    = _T("");
	m_strEditChm   = _T("");
	m_strEditChi   = _T("");
	m_strEditID    = _T("");
	m_strEditDat   = _T("");
	m_strEditCol   = _T("");
	m_strEditVer   = _T("1");
	m_strEditTitle = _T("");
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Initialize our edit fields based on the MSDN
	// collection data...
	m_strCol     = m_MSDNIntegrate.GetCollectionName();
	m_strLangId  = m_MSDNIntegrate.GetLanguageID();
	m_strColNum  = m_MSDNIntegrate.GetCollectionNumber();
	m_strEditDat = m_MSDNIntegrate.GetRegistryFile();
	m_strEditCol = m_MSDNIntegrate.GetCollectionFile();

  if ( config.IsValid() )
  {
    m_strEditChm = config.m_strChm;
    m_strEditChi = config.m_strChi;
    m_strEditTitle = config.m_strTitle;
    m_strEditID = config.m_strGUID;
    m_strEditVer = config.m_strVersion;

    m_MSDNIntegrate.SetChiFile( config.m_strChi );
    m_MSDNIntegrate.SetChmFile( config.m_strChm );
    m_MSDNIntegrate.SetTitleString( config.m_strTitle );
    m_MSDNIntegrate.SetUniqueID( config.m_strGUID );
    m_MSDNIntegrate.SetHelpVer( config.m_strVersion );
  }
}

void CMSDNIntegratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSDNIntegratorDlg)
	DDX_Control(pDX, IDC_BTN_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Text(pDX, IDC_TXT_COL, m_strCol);
	DDX_Text(pDX, IDC_TXT_NO, m_strColNum);
	DDX_Text(pDX, IDC_TXT_ID, m_strLangId);
	DDX_Text(pDX, IDC_EDIT_CHM, m_strEditChm);
	DDX_Text(pDX, IDC_EDIT_CHI, m_strEditChi);
	DDX_Text(pDX, IDC_EDIT_ID, m_strEditID);
	DDX_Text(pDX, IDC_EDIT_DAT, m_strEditDat);
	DDX_Text(pDX, IDC_EDIT_COL, m_strEditCol);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strEditTitle);
	DDX_Text(pDX, IDC_EDIT_VER, m_strEditVer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSDNIntegratorDlg, CDialog)
	//{{AFX_MSG_MAP(CMSDNIntegratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CHM, OnBtnChm)
	ON_BN_CLICKED(IDC_BTN_CHI, OnBtnChi)
	ON_BN_CLICKED(IDC_BTN_ID, OnBtnId)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_EN_CHANGE(IDC_EDIT_TITLE, OnChangeEditTitle)
	ON_EN_CHANGE(IDC_EDIT_ID, OnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_VER, OnChangeEditVer)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_EN_CHANGE(IDC_EDIT_CHI, OnChangeEditChi)
	ON_EN_CHANGE(IDC_EDIT_CHM, OnChangeEditChm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorDlg message handlers

BOOL CMSDNIntegratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Since we are using a progress control, set the progress
	// control for the integration.
	m_MSDNIntegrate.SetProgressCtrl(&m_progress);

  if ( m_strEditTitle.IsEmpty() )
	  m_strEditTitle = _T("<Enter a title for your collection>");

  if ( m_strEditID.IsEmpty() )
	  m_strEditID    = _T("<Enter a unique ID for your collection>");

	// Set the integrator defaults.
	m_MSDNIntegrate.SetTitleString(m_strEditTitle);
	m_MSDNIntegrate.SetUniqueID(m_strEditID);
	m_MSDNIntegrate.SetHelpVer(m_strEditVer);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMSDNIntegratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMSDNIntegratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMSDNIntegratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMSDNIntegratorDlg::OnChangeEditChi() 
{
	UpdateData();
}

void CMSDNIntegratorDlg::OnChangeEditChm() 
{
	UpdateData();
}

void CMSDNIntegratorDlg::OnChangeEditTitle() 
{
	UpdateData();
	m_MSDNIntegrate.SetTitleString(m_strEditTitle);
}

void CMSDNIntegratorDlg::OnChangeEditId() 
{
	UpdateData();
	m_MSDNIntegrate.SetUniqueID(m_strEditID);
}

void CMSDNIntegratorDlg::OnChangeEditVer() 
{
	UpdateData();
	m_MSDNIntegrate.SetHelpVer(m_strEditVer);
}

void CMSDNIntegratorDlg::OnBtnChm() 
{
	m_strEditChm = m_MSDNIntegrate.FindChmFile(this);
	UpdateData(FALSE);
}

void CMSDNIntegratorDlg::OnBtnChi() 
{
	m_strEditChi = m_MSDNIntegrate.FindChiFile(this);
	UpdateData(FALSE);
}

void CMSDNIntegratorDlg::OnBtnId() 
{
	m_strEditID = m_MSDNIntegrate.GenerateGUID();
	UpdateData(FALSE);
}

void CMSDNIntegratorDlg::OnBtnAdd() 
{
	UpdateData();

	if (m_MSDNIntegrate.CanIntegrate() == true)
	{
		if (m_MSDNIntegrate.Integrate())
		{

		}
	}
}

void CMSDNIntegratorDlg::OnBtnRemove() 
{
	UpdateData();

	if (m_MSDNIntegrate.CanIntegrate(false) == false)
	{
		if (!m_MSDNIntegrate.GetUniqueID().IsEmpty())
		{
			if (m_MSDNIntegrate.Clean())
			{
				
			}
		}
	}
}

void CMSDNIntegratorDlg::OnBtnHelp() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
