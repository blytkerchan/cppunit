// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegration.cpp: implementation of the CMSDNIntegration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resource.h"
#include "MSDNIntegration.h"

// used for DLLVERSIONINFO
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef VERSION_IE5
#define VERSION_IE5             MAKELONG(0, 5)
#endif // VERSION_IE5

#ifndef CSIDL_COMMON_APPDATA
#define CSIDL_COMMON_APPDATA    0x0023      // All Users\Application Data
#endif // CSIDL_COMMON_APPDATA

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegration construction/destruction

CMSDNIntegration::CMSDNIntegration()
{
	m_pProgress = NULL;

	m_strMSDNRegistry   = _T("");
	m_strMSDNCollection = _T("");
	m_strColName        = _T("");
	m_strColNum         = _T("");
	m_strLangId         = _T("");
	m_strUniqueID       = _T("");
	m_strTitleString    = _T("");
	m_strChmFile        = _T("");
	m_strChiFile        = _T("");
	m_strHelpVer        = _T("1");

	::ZeroMemory(m_szDrive, sizeof(m_szDrive));
	::ZeroMemory(m_szDir, sizeof(m_szDir));
	::ZeroMemory(m_szFilename, sizeof(m_szFilename));
	::ZeroMemory(m_szExt, sizeof(m_szExt));

	::GetWindowsDirectory(m_szWinDir, _MAX_DIR);

	GetMSDNCollection();
	GetMSDNRegistry();
}

CMSDNIntegration::~CMSDNIntegration()
{

}

bool CMSDNIntegration::GetRegKeyValue(LPCTSTR lpszKey, TCHAR *szName, TCHAR *szValue)
{
	HKEY  hkKey=NULL;
	DWORD dwDisposition;
	DWORD dwValueType;
	DWORD dwBufferLength;
	SECURITY_ATTRIBUTES saSecurityAttributes;
	CFileStatus FileStatus;
	BOOL bKeyOpenOk;

	saSecurityAttributes.nLength = sizeof(saSecurityAttributes);
	saSecurityAttributes.lpSecurityDescriptor=NULL;
	saSecurityAttributes.bInheritHandle=TRUE;

	bKeyOpenOk = ::RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpszKey,
		NULL,"",REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
		&saSecurityAttributes, &hkKey, &dwDisposition);

	// check results
	if (bKeyOpenOk != ERROR_SUCCESS) {
		return false;
	}

	if (dwDisposition == REG_OPENED_EXISTING_KEY)
	{
		dwBufferLength=_MAX_PATH;
		
		if (::RegQueryValueEx(hkKey, szName, (LPDWORD)NULL, &dwValueType,
			(LPBYTE)szValue, &dwBufferLength) != ERROR_SUCCESS)
		{
			return false;
		}
	}

	return true;
}

bool CMSDNIntegration::GetCollectionInfo()
{
	TRY
	{
		CString strBuffer;
		CStdioFile stdRead(m_strMSDNCollection, CFile::modeRead | CFile::typeText);

		m_strLangId.Empty();
		m_strColNum.Empty();

		while (stdRead.ReadString(strBuffer))
		{
			if (strBuffer.Find(_T("masterlangid")) != -1)
			{
				int nStart = strBuffer.Find(_T('='))+1;
				int nEnd   = strBuffer.Find(_T('/'));
				m_strLangId = strBuffer.Mid(nStart, (nEnd-nStart));
			}

			if (strBuffer.Find(_T("collectionnum")) != -1)
			{
				int nStart = strBuffer.Find(_T('='))+1;
				int nEnd   = strBuffer.Find(_T('/'));
				m_strColNum = strBuffer.Mid(nStart, (nEnd-nStart));
			}

			if (!m_strLangId.IsEmpty() && 
				!m_strColNum.IsEmpty())
			{
				break;
			}
		}
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		return DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::GetMSDNCollection()
{
	TCHAR szValue[_MAX_PATH];
	
	CString strKey;
	strKey.LoadString(IDS_MSDN_KEY);
	
	if (GetRegKeyValue(strKey, _T("Language"), szValue) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	strKey += _T('\\');
	strKey += szValue;

	if (GetRegKeyValue(strKey, _T("Preferred"), szValue) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	strKey += _T('\\');
	strKey += szValue;

	if (GetRegKeyValue(strKey, _T("Filename"), szValue) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	// Make sure that the collection exists!
	CFileFind ff;
	if (!ff.FindFile(szValue))
		return DisplayMessage(IDS_ERR_COLNOTFOUND);

	_tsplitpath(szValue, m_szDrive, m_szDir, m_szFilename, m_szExt);
	m_strMSDNCollection = szValue;
	m_strColName.Format(_T("%s%s"), m_szFilename, m_szExt);

	return true;
}

#ifdef _UNICODE
static const TCHAR _szSpecialFolderPath[] = _T("SHGetSpecialFolderPathW");
#else
static const TCHAR _szSpecialFolderPath[] = _T("SHGetSpecialFolderPathA");
#endif

AFX_STATIC BOOL AFXAPI _xtAfxGetSpecialFolderPath(HWND hwndOwner, LPTSTR lpszPath, int nFolder, BOOL fCreate)
{
	typedef int (WINAPI* _SHGET)(HWND, LPTSTR, int, BOOL);

	// Get a function pointer to SHGetSpecialFolderPath(...) from
	// Shell32.dll, if this returns NULL then check ShFolder.dll...
	_SHGET pfn = (_SHGET)::GetProcAddress(
		CLoadLibrary(_T("Shell32.dll")), _szSpecialFolderPath);

	if (pfn == NULL)
	{
		// Try to get the function pointer from ShFolder.dll, if pfn is still
		// NULL then we have bigger problems...
		pfn = (_SHGET)::GetProcAddress(
			CLoadLibrary(_T("ShFolder.dll")), _szSpecialFolderPath);

		if (pfn == NULL) {
			return FALSE;
		}
	}

	return pfn(hwndOwner, lpszPath, nFolder, fCreate);
}

bool CMSDNIntegration::GetMSDNRegistry()
{
	// query the collection to get the correct 
	// MSDN version information.
	VERIFY(GetCollectionInfo());

	int nColNum = atoi(m_strColNum);

	// old MSDN collection, hhcolreg.dat is located in the
	// Windows\Help directory...
	if ( nColNum < 10000)
	{
		m_strMSDNRegistry.Format(IDS_OLD_DAT, m_szWinDir);
	}
	else
	{
		// verify that we have version 5.00 or later of Shell32.dll.
		// If so we can use SHGetSpecialFolderPath(...) to get the path
		// where hhcolreg.dat should be located, otherwise we will make
		// an educated guess...
		CLoadLibrary libModule(_T("Shell32.dll"));
		if (libModule.GetModuleVersion() < VERSION_IE5)
		{
			m_strMSDNRegistry.Format(IDS_NEW_DAT, m_szDrive);
		}
		else
		{
			TCHAR lpszFolderPath[_MAX_PATH];
			::ZeroMemory(lpszFolderPath, sizeof(lpszFolderPath));
			
			// Thanks to Michael Kopp [michael.kopp@gmx.at] for pointing this out.
			
			// With later versions of Internet Explorer, Microsoft moved
			// the function 'SHGetSpecialFolderPath' from Shell32.dll into 
			// ShFolder.dll. To handle this we need to write our own version
			// of GetSpecialFolderPath(...), this will return a function pointer
			// from the correct DLL.

			if (_xtAfxGetSpecialFolderPath(NULL, lpszFolderPath,
				CSIDL_COMMON_APPDATA, FALSE) != FALSE) {
				m_strMSDNRegistry.Format(IDS_NEWER_DAT, lpszFolderPath);
			}
			else {
				m_strMSDNRegistry.Format(IDS_NEW_DAT, m_szDrive);
			}
		}
	}

	CFileFind ff;
	if (!ff.FindFile(m_strMSDNRegistry)) {
		return DisplayMessage(IDS_ERR_DATNOTFOUND);
	}

	return true;
}

void CMSDNIntegration::ResetData()
{
	// flush all strings.
	m_strChmFile.Empty();
	m_strChiFile.Empty();
	m_strUniqueID.Empty();
	m_strTitleString.Empty();
}

bool CMSDNIntegration::CanIntegrate(bool bCheckData/*=true*/)
{
	CString strTitle;
	strTitle.LoadString(IDS_ERR_TITLE);
	
	// All data must be completely initialized first...
	if (bCheckData)
	{
		if (GetUniqueID().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_ID);
		
		if (GetChmFile().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_CHM);
		
		if (GetChiFile().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_CHI);
		
		if (GetTitleString().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_TITLE);
		
		if (GetRegistryFile().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_DAT);
		
		if (GetCollectionFile().IsEmpty())
			return DisplayMessage(IDS_ERR_INIT_COL);
	}
	else
	{
		if (GetUniqueID().IsEmpty())
			return !DisplayMessage(IDS_ERR_INIT_ID);
	}

	TRY
	{
		CString strBuffer;

		// see if there is an entry in the MSDN collection...
		CStdioFile msdnCol(m_strMSDNCollection, CFile::modeRead | CFile::typeText);
		while (msdnCol.ReadString(strBuffer))
		{
			if (strBuffer.Find(m_strUniqueID) != -1) {
				return false;
			}
		}

		// if not check the MSDN Registry.
		CStdioFile msdnReg(m_strMSDNRegistry, CFile::modeRead | CFile::typeText);
		while (msdnReg.ReadString(strBuffer))
		{
			if (strBuffer.Find(m_strUniqueID) != -1) {
				return false;
			}
		}
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		return DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::IntegrateMSDNRegistry()
{
	TRY
	{
		ASSERT(!m_strUniqueID.IsEmpty());
		ASSERT(!m_strLangId.IsEmpty());
		ASSERT(!m_strColNum.IsEmpty());
		ASSERT(!m_strChmFile.IsEmpty());
		ASSERT(!m_strChiFile.IsEmpty());
		ASSERT(!m_strHelpVer.IsEmpty());

		CString strBuffer;
		CStringArray strArray;
		CStdioFile stdRead(m_strMSDNRegistry, CFile::modeRead | CFile::typeText);

		while (stdRead.ReadString(strBuffer))
		{
			strArray.Add(strBuffer+_T('\n'));
			if (m_pProgress && m_pProgress->GetSafeHwnd())
				m_pProgress->StepIt();
		}

		stdRead.Close();

		CStdioFile stdWrite(m_strMSDNRegistry,
			CFile::modeWrite | CFile::modeCreate | CFile::typeText);

		for (int nIndex = 0; nIndex < strArray.GetSize(); ++nIndex)
		{
			if (strArray.GetAt(nIndex).Find(_T("</DocCompilations>")) != -1)
			{
				strBuffer.Format(IDS_REGISTRY,
					m_strUniqueID,
					m_strLangId,
					m_strColNum,
					m_strChmFile,
					m_strChiFile,
					m_strHelpVer);

				stdWrite.WriteString(strBuffer);
				stdWrite.WriteString(_T("      </DocCompilations>\n"));
				stdWrite.WriteString(_T("   </HTMLHelpDocInfo>\n"));
				stdWrite.WriteString(_T("</XML>\n"));
				break;
			}

			stdWrite.WriteString(strArray.GetAt(nIndex));
		}

		stdWrite.Close();
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		return DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::IntegrateMSDNCollection()
{
	TRY
	{
		ASSERT(!m_strTitleString.IsEmpty());
		ASSERT(!m_strUniqueID.IsEmpty());
		ASSERT(!m_strLangId.IsEmpty());

		CString strBuffer;
		CStringArray strArray;
		CStdioFile stdRead(m_strMSDNCollection, CFile::modeRead | CFile::typeText);

		while (stdRead.ReadString(strBuffer))
		{
			strArray.Add(strBuffer+_T('\n'));
			if (m_pProgress && m_pProgress->GetSafeHwnd())
				m_pProgress->StepIt();
		}

		stdRead.Close();

		CStdioFile stdWrite(m_strMSDNCollection,
			CFile::modeWrite | CFile::modeCreate | CFile::typeText);

		for (int nIndex = 0; nIndex < strArray.GetSize(); ++nIndex)
		{
			if (strArray.GetAt(nIndex).Find(_T("</Folders>")) != -1)
			{
				strBuffer.Format(IDS_COLLECTION,
					m_strTitleString,
					m_strUniqueID,
					m_strLangId);

				stdWrite.WriteString(strBuffer);
				stdWrite.WriteString(_T("      </Folders>\n"));
				stdWrite.WriteString(_T("   </HTMLHelpCollection>\n"));
				stdWrite.WriteString(_T("</XML>\n"));
				break;
			}

			stdWrite.WriteString(strArray.GetAt(nIndex));
		}
		stdWrite.Close();
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		return DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::Integrate()
{
	if (!IntegrateMSDNRegistry())
		return false;
		
	if (!IntegrateMSDNCollection())
		return false;

	if (m_pProgress && m_pProgress->GetSafeHwnd())
		m_pProgress->SetPos(0);

	return DisplayMessage(IDS_INTEGRATION_COMPLETE, false);
}

bool CMSDNIntegration::CleanMSDNRegistry()
{
	TRY
	{
		CString strBuffer;
		CStringArray strArray;
		CStdioFile stdRead(m_strMSDNRegistry, CFile::modeRead | CFile::typeText);

		while (stdRead.ReadString(strBuffer))
		{
			strArray.Add(strBuffer+_T('\n'));
			if (m_pProgress && m_pProgress->GetSafeHwnd())
				m_pProgress->StepIt();
		}
		
		stdRead.Close();
		
		for (int nIndex = 0; nIndex < strArray.GetSize(); ++nIndex)
		{
			if (strArray.GetAt(nIndex).Find(m_strUniqueID) != -1) {
				strArray.RemoveAt(nIndex-1, 15);
				break;
			}
		}

		CStdioFile stdWrite(m_strMSDNRegistry,
			CFile::modeWrite | CFile::modeCreate | CFile::typeText);

		for (nIndex = 0; nIndex < strArray.GetSize(); ++nIndex) {
			stdWrite.WriteString(strArray.GetAt(nIndex));
		}

		stdWrite.Close();
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::CleanMSDNCollection()
{
	TRY
	{
		CString strBuffer;
		CStringArray strArray;
		CStdioFile stdRead(m_strMSDNCollection, CFile::modeRead | CFile::typeText);

		while (stdRead.ReadString(strBuffer))
		{
			strArray.Add(strBuffer+_T('\n'));
			if (m_pProgress && m_pProgress->GetSafeHwnd())
				m_pProgress->StepIt();
		}

		stdRead.Close();

		for (int nIndex = 0; nIndex < strArray.GetSize(); ++nIndex)
		{
			if (strArray.GetAt(nIndex).Find(m_strUniqueID) != -1) {
				strArray.RemoveAt(nIndex-4, 9);
				break;
			}
		}

		CStdioFile stdWrite(m_strMSDNCollection,
			CFile::modeWrite | CFile::modeCreate | CFile::typeText);

		for (nIndex = 0; nIndex < strArray.GetSize(); ++nIndex) {
			stdWrite.WriteString(strArray.GetAt(nIndex));
		}

		stdWrite.Close();
	}
	CATCH( CFileException, e )
	{
		CString strMessage;
		strMessage.Format(IDS_ERR_OPENFILE, e->m_cause);
		DisplayMessage(strMessage);
	}
	END_CATCH

	return true;
}

bool CMSDNIntegration::Clean()
{
	if (!CleanMSDNRegistry())
		return false;
		
	if (!CleanMSDNCollection())
		return false;

	if (m_pProgress && m_pProgress->GetSafeHwnd())
		m_pProgress->SetPos(0);

	return DisplayMessage(IDS_REMOVAL_COMPLETE, false);
}

CString CMSDNIntegration::GenerateGUID()
{
	// create random GUID
	GUID guid = GUID_NULL;
	::CoCreateGuid(&guid);
	
	if (guid != GUID_NULL)
	{
		m_strUniqueID.Empty();

		// use the formatting string to format into destination.
		m_strUniqueID.Format(IDS_GUID,
			guid.Data1,    guid.Data2,    guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		
		return m_strUniqueID;
	}

	return _T("");
}

void CMSDNIntegration::SetUniqueID(LPCTSTR lpszUniqueID/*=NULL*/)
{
	if (_tcslen(lpszUniqueID) == 0)
		GenerateGUID();
	else
		m_strUniqueID = lpszUniqueID;
}

void CMSDNIntegration::SetProgressCtrl(CProgressCtrl* pProgress)
{
	ASSERT(pProgress != NULL && ::IsWindow(pProgress->GetSafeHwnd()));
	m_pProgress = pProgress;

	int nUpper = 0;
	CString strBuffer;
	CStdioFile stdReg(m_strMSDNRegistry, CFile::modeRead | CFile::typeText);
	
	while (stdReg.ReadString(strBuffer)) {
		++nUpper;
	}
	stdReg.Close();

	CStdioFile stdCol(m_strMSDNCollection, CFile::modeRead | CFile::typeText);
	while (stdCol.ReadString(strBuffer)) {
		++nUpper;
	}
	stdCol.Close();

	m_pProgress->SetRange(0, nUpper);
	m_pProgress->SetStep(1);
	m_pProgress->SetPos(0);
}

// Windows 2000 version of OPENFILENAME.
// The new version has three extra members.
// This is copied from commdlg.h
//
struct OPENFILENAMEEX : public OPENFILENAME { 
  void *        pvReserved;
  DWORD         dwReserved;
  DWORD         FlagsEx;
};

CString CMSDNIntegration::FindChmFile(CWnd* pWnd)
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter.LoadString(IDS_CHM_FILTER);
 
	CFileDialog dlg( TRUE, NULL, NULL, OFN_EXPLORER|
		OFN_ENABLESIZING|OFN_FILEMUSTEXIST, strFilter, pWnd );
	
	// Check to see if this is Windows 2000...if so use the
	// Windows 2000 version of OPENFILENAME.
	DWORD dwWinMajor = (DWORD)(LOBYTE(LOWORD(::GetVersion())));
	if ((BYTE)dwWinMajor >= 5) {
		dlg.m_ofn.lStructSize = sizeof(OPENFILENAMEEX);
	}

	if( dlg.DoModal() == IDOK )
	{
		SetChmFile(dlg.GetPathName());
		return GetChmFile();
	}

	return _T("");
}

CString CMSDNIntegration::FindChiFile(CWnd* pWnd)
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter.LoadString(IDS_CHI_FILTER);
 
	CFileDialog dlg( TRUE, NULL, NULL, OFN_EXPLORER|
		OFN_ENABLESIZING|OFN_FILEMUSTEXIST, strFilter, pWnd );

	// Check to see if this is Windows 2000...if so use the
	// Windows 2000 version of OPENFILENAME.
	DWORD dwWinMajor = (DWORD)(LOBYTE(LOWORD(::GetVersion())));
	if ((BYTE)dwWinMajor >= 5) {
		dlg.m_ofn.lStructSize = sizeof(OPENFILENAMEEX);
	}
	
	if( dlg.DoModal() == IDOK )
	{
		SetChiFile(dlg.GetPathName());
		return GetChiFile();
	}

	return _T("");
}

bool CMSDNIntegration::DisplayMessage(UINT nMessage, bool bError/*=true*/)
{
	CString strMessage;
	strMessage.LoadString(nMessage);

	CString strTitle;
	strTitle.LoadString(IDS_ERR_TITLE);

	::MessageBox(NULL, strMessage, strTitle, MB_OK | bError ? 
		MB_ICONERROR : MB_ICONINFORMATION );
	return !bError;
}

bool CMSDNIntegration::DisplayMessage(LPCTSTR lpszMessage, bool bError/*=true*/)
{
	CString strTitle;
	strTitle.LoadString(IDS_ERR_TITLE);

	::MessageBox(NULL, lpszMessage, strTitle, MB_OK | bError ? 
		MB_ICONERROR : MB_ICONINFORMATION );
	return !bError;
}

/////////////////////////////////////////////////////////////////////////////
// CLoadLibrary construction/destruction

CLoadLibrary::CLoadLibrary(LPCTSTR lpszLibFileName)
{
	m_hLibModule = ::LoadLibrary(lpszLibFileName);
	ASSERT(m_hLibModule != NULL);
}

CLoadLibrary::~CLoadLibrary()
{
	::FreeLibrary(m_hLibModule);
}

CLoadLibrary::operator HINSTANCE()
{
	return m_hLibModule; // cast operator
}

DWORD CLoadLibrary::GetModuleVersion()
{
	typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO*);

	DLLGETVERSIONPROC pDllGetVersion =
		(DLLGETVERSIONPROC)::GetProcAddress(*this, _T("DllGetVersion"));

	DWORD dwVersion = 0L;
	if (pDllGetVersion != NULL)
	{
		DLLVERSIONINFO dvi;
		ZeroMemory(&dvi, sizeof(dvi));
		dvi.cbSize = sizeof(dvi);
		
		HRESULT hr = (*pDllGetVersion)(&dvi);
		if (SUCCEEDED(hr))
		{
			ASSERT(dvi.dwMajorVersion <= 0xFFFF);
			ASSERT(dvi.dwMinorVersion <= 0xFFFF);
			dwVersion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
		}
	}
	
	return dwVersion;
}
