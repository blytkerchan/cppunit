// MSDNIntegratorConfig.cpp: implementation of the CMSDNIntegratorConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSDNIntegratorConfig.h"
#include "Utility.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSDNIntegratorConfig::CMSDNIntegratorConfig()
{
  CString section( "MSDNIntegrator" );
  m_strChi = GetFullPath( AfxGetApp()->GetProfileString( section, "Chi" ) );
  m_strChm = GetFullPath( AfxGetApp()->GetProfileString( section, "Chm" ) );
  m_strTitle = AfxGetApp()->GetProfileString( section, "Title" );
  m_strGUID = AfxGetApp()->GetProfileString( section, "GUID" );
  m_strVersion = AfxGetApp()->GetProfileString( section, "Version", "1" );
}

CMSDNIntegratorConfig::~CMSDNIntegratorConfig()
{

}

BOOL CMSDNIntegratorConfig::IsValid() const
{
  return !m_strChi.IsEmpty()  &&
         !m_strChm.IsEmpty()  &&
         !m_strTitle.IsEmpty()  &&
         !m_strGUID.IsEmpty();
}
