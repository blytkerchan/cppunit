// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegrator.h : main header file for the MSDNINTEGRATOR application
//

#if !defined(AFX_MSDNINTEGRATOR_H__1270958F_3C42_4416_B8B3_F7E52FA42911__INCLUDED_)
#define AFX_MSDNINTEGRATOR_H__1270958F_3C42_4416_B8B3_F7E52FA42911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorApp:
// See MSDNIntegrator.cpp for the implementation of this class
//

class CMSDNIntegratorApp : public CWinApp
{
public:
	CMSDNIntegratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDNIntegratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSDNIntegratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  void SetIniFileName();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDNINTEGRATOR_H__1270958F_3C42_4416_B8B3_F7E52FA42911__INCLUDED_)
