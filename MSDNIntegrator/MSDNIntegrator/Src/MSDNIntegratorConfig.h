// MSDNIntegratorConfig.h: interface for the CMSDNIntegratorConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSDNINTEGRATORCONFIG_H__0F92F17D_A374_4F62_AD25_4E57662A01BD__INCLUDED_)
#define AFX_MSDNINTEGRATORCONFIG_H__0F92F17D_A374_4F62_AD25_4E57662A01BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMSDNIntegratorConfig  
{
public:
	CMSDNIntegratorConfig();
	virtual ~CMSDNIntegratorConfig();

  BOOL IsValid() const;

  CString m_strChi;
  CString m_strChm;
  CString m_strTitle;
  CString m_strGUID;
  CString m_strVersion;
};

#endif // !defined(AFX_MSDNINTEGRATORCONFIG_H__0F92F17D_A374_4F62_AD25_4E57662A01BD__INCLUDED_)
