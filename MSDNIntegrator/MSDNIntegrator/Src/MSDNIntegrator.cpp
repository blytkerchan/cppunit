// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegrator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MSDNIntegrator.h"
#include "MSDNIntegratorDlg.h"
#include "MSDNIntegratorConfig.h"
#include "Utility.h"

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp

BEGIN_MESSAGE_MAP(CMSDNIntegratorApp, CWinApp)
	//{{AFX_MSG_MAP(CMSDNIntegratorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp construction

CMSDNIntegratorApp::CMSDNIntegratorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMSDNIntegratorApp object

CMSDNIntegratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp initialization

BOOL CMSDNIntegratorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  SetIniFileName();
  
  CMSDNIntegratorConfig config;

	CMSDNIntegratorDlg dlg( config );
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


void CMSDNIntegratorApp::SetIniFileName()
{
  CCommandLineInfo commands;
  ParseCommandLine( commands );
  if ( commands.m_strFileName.IsEmpty() )
    return;

  free((void*)m_pszProfileName);

  m_pszProfileName = _tcsdup( GetFullPath( commands.m_strFileName ) );
}
