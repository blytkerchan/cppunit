// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegratorDlg.h : header file
//

#if !defined(AFX_MSDNINTEGRATORDLG_H__4835228D_60A4_4841_A3F2_5D104521350D__INCLUDED_)
#define AFX_MSDNINTEGRATORDLG_H__4835228D_60A4_4841_A3F2_5D104521350D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MSDNIntegration.h"
#include "MSDNIntegratorConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegratorDlg dialog

class CMSDNIntegratorDlg : public CDialog
{
// Construction
public:
	CMSDNIntegratorDlg( const CMSDNIntegratorConfig &config,
                      CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMSDNIntegratorDlg)
	enum { IDD = IDD_MSDNINTEGRATOR_DIALOG };
	CButton	m_btnRemove;
	CProgressCtrl	m_progress;
	CButton	m_btnAdd;
	CString	m_strCol;
	CString	m_strColNum;
	CString	m_strLangId;
	CString	m_strEditChm;
	CString	m_strEditChi;
	CString	m_strEditID;
	CString	m_strEditDat;
	CString	m_strEditCol;
	CString	m_strEditTitle;
	CString	m_strEditVer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDNIntegratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CMSDNIntegration m_MSDNIntegrate;

	// Generated message map functions
	//{{AFX_MSG(CMSDNIntegratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnChm();
	afx_msg void OnBtnChi();
	afx_msg void OnBtnId();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnHelp();
	afx_msg void OnChangeEditTitle();
	afx_msg void OnChangeEditId();
	afx_msg void OnChangeEditVer();
	afx_msg void OnBtnRemove();
	afx_msg void OnChangeEditChi();
	afx_msg void OnChangeEditChm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDNINTEGRATORDLG_H__4835228D_60A4_4841_A3F2_5D104521350D__INCLUDED_)
