// ©2001 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. http://www.codejock.com
//
// MSDNIntegration.h: interface for the CMSDNIntegration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__MSDNINTEGRATION_H__)
#define __MSDNINTEGRATION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CMSDNIntegration:
// Used to integrate HTML help files with the MSDN collection.
//

class CMSDNIntegration  
{
public:

    // -> Remarks: Constructs a CMSDNIntegration object.
	CMSDNIntegration();

    // -> Remarks:  Destroys a CMSDNIntegration object, handles cleanup and de-allocation.
	virtual ~CMSDNIntegration();

    // -> Input:   lpszKey - Pointer to a null-terminated string specifying the registry subkey
	//                       to get the value for.
	//             szName  - Pointer to a null-terminated string containing the name of the 
	//                       value to query. 
	//             szValue - Pointer to a buffer that receives the value's data.
	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function is used to query the system registry and retrieve
	//             the value for the specified key.
	bool GetRegKeyValue(LPCTSTR lpszKey, TCHAR *szName, TCHAR *szValue);

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will initialize the language id and collection 
	//             collection number data.
	bool GetCollectionInfo();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function querys the system registry for the name
	//             and file location of the MSDN collection.
	bool GetMSDNCollection();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function determines the correct location of the
	//             hhcolreg.dat file that is used by the MSDN collection.
	bool GetMSDNRegistry();

    // -> Input:   bCheckData - true to verify all input data has been initialized.
	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function is used to determine if all of the
	//             input data has been initialized, and if the new title can
	//             be safely added to the collection. Will return false if the
	//             title is already found.
	bool CanIntegrate(bool bCheckData=true);

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will integrate the initialized data into 
	//             the MSDN collection file.
	bool IntegrateMSDNCollection();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will integrate the initialized data into 
	//             the hhcolreg.dat file.
	bool IntegrateMSDNRegistry();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will integrate the initialized data into
	//             with the MSDN collection. This member will call both the
	//             IntegrateMSDNCollection() and IntegrateMSDNRegistry() methods.
	bool Integrate();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will remove the help item specified by the
	//             unique identifier from the MSDN collection file.
	bool CleanMSDNCollection();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will remove the help item specified by the
	//             unique identifier from the hhcolreg.dat file.
	bool CleanMSDNRegistry();

	// -> Returns: true if successful, otherwise false.
	// -> Remarks: This member function will remove the help item specified by the
	//             unique identifier form the MSDN collection. This member will call
	//             both the CleanMSDNCollection() and CleanMSDNRegistry() methods.
	bool Clean();

	// -> Returns: A CString object that represents the newly created GUID if successful.
	// -> Remarks: This member function will create a new GUID and initialize the
	//             unique identifier for this object.
	CString GenerateGUID();

	// -> Returns: A CString object that represents the full path to hhcolreg.dat.
	// -> Remarks: This member function will return the current location for the
	//             hhcolreg.dat file used by the MSDN collection.
	CString GetRegistryFile() const;

	// -> Returns: A CString object that represents the full path to the MSDN collection file.
	// -> Remarks: This member function will return the current location for the
	//             MSDN collection file that was specified in the systems registry.
	CString GetCollectionFile() const;

	// -> Returns: A CString object that represents the MSDN collection file name.
	// -> Remarks: This member function will return the current MSDN collection name
	//             minus the path.
	CString GetCollectionName() const;

	// -> Returns: A CString object that represents the MSDN collection number.
	// -> Remarks: This member function will return the current MSDN collection number.
	CString GetCollectionNumber() const;

	// -> Returns: A CString object that represents the current language ID settings.
	// -> Remarks: This member function will return the current language ID settings
	//             for the MSDN collection.
	CString GetLanguageID() const;

	// -> Returns: A CString object that represents the current identifier for the
	//             newly added help file.
	// -> Remarks: This member function will return unique identifier for the
	//             help file that is to be added to the MSDN collection.
	CString GetUniqueID() const;

    // -> Input:   lpszUniqueID - A NULL terminated string that represents the new
	//                            value for the help file unique identifier.
	// -> Remarks: This member function will set the value of the unique identifier
	//             for the help file that is to be added to the MSDN collection.
	void SetUniqueID(LPCTSTR lpszUniqueID=NULL);

	// -> Returns: A CString object that represents the title string for the help file.
	// -> Remarks: This member function will return the title string for the help
	//             file that is to be added to the MSDN collection.
	CString GetTitleString() const;
	
    // -> Input:   lpszTitleString - A NULL terminated string that represents the title 
	//                               string for the help file
	// -> Remarks: This member function will set the title string for the help file that
	//             is to be added to the MSDN collection.
	void SetTitleString(LPCTSTR lpszTitleString);

	// -> Returns: A CString object that represents the full path to the .chm help file.
	// -> Remarks: This member function will return the full path to the .chm file that
	//             is to be added to the MSDN collection.
	CString GetChmFile() const;
	
    // -> Input:   lpszChmFile - A NULL terminated string that represents the full path 
	//             to the .chm help file.
	// -> Remarks: This member function will set the value for the .chm help file that
	//             is to be added to the MSDN collection.
	void SetChmFile(LPCTSTR lpszChmFile);

	// -> Returns: A CString object that represents the full path to the .chi help index file.
	// -> Remarks: This member function will return the full path to the .chi index file that
	//             is to be added to the MSDN collection.
	CString GetChiFile() const;
	
    // -> Input:   lpszChiFile - A NULL terminated string that represents the full path 
	//             to the .chi help index file.
	// -> Remarks: This member function will set the value for the .chi help index file that
	//             is to be added to the MSDN collection.
	void SetChiFile(LPCTSTR lpszChiFile);

	// -> Returns: A CString object that represents the version number of the help file.
	// -> Remarks: This member function will return the version number of the help file that
	//             is to be added to the MSDN collection.
	CString GetHelpVer() const;
	
    // -> Input:   lpszHelpVer - A NULL terminated string that represents the version number 
	//                           of the help file.
	// -> Remarks: This member function set the value for the version number of the help file
	//             that is to be added to the MSDN collection.
	void SetHelpVer(LPCTSTR lpszHelpVer);

	// -> Returns: A pointer to the progress control to be used during integration.
	// -> Remarks: This member function will return a pointer to the progress control
	//             that is to be used during the integration process.
	CProgressCtrl* GetProgressCtrl() const;
	
    // -> Input:   pProgress - A pointer to a CProgressCtrl object.
	// -> Remarks: This member function will set the progress control object that is to
	//             be used during the integration progress. If set the progress control
	//             will be initialized and updated during the integration process.
	void SetProgressCtrl(CProgressCtrl* pProgress);

    // -> Input:   pWnd - A pointer to the file open dialog-box object’s parent or 
	//                    owner window.
	// -> Returns: A CString object that represents the currently selected .chm file.
	// -> Remarks: This member function will activate a file open dialog to search for
	//             a .chm file to be used when integrating with the MSDN collection.
	CString FindChmFile(CWnd* pWnd);
	
    // -> Input:   pWnd - A pointer to the file open dialog-box object’s parent or 
	//                    owner window.
	// -> Returns: A CString object that represents the currently selected .chi file.
	// -> Remarks: This member function will activate a file open dialog to search for
	//             a .chi file to be used when integrating with the MSDN collection.
	CString FindChiFile(CWnd* pWnd);

	// -> Remarks: This member function will reset all of the data used for integration.
	void ResetData();

    // -> Input:   nMessage - A string resource id that represents the message to display.
	// ->          bError   - true if this is an error message.
	// -> Returns: false if the message displayed is an error, otherwise true.
	// -> Remarks: This member function displays an error message to be used during integration.
	bool DisplayMessage(UINT nMessage, bool bError=true);

    // -> Input:   lpszMessage - A NULL terminated string that represents the message to display.
	// ->          bError      - true if this is an error message.
	// -> Returns: false if the message displayed is an error, otherwise true.
	// -> Remarks: This member function displays an error message to be used during integration.
	bool DisplayMessage(LPCTSTR lpszMessage, bool bError=true);

	// -> Returns: A CString object.
	// -> Remarks: This member function returns a CString object that represents the location
	//             of the Windows directory.
	CString GetWindowsDir() const;

	// -> Returns: A CString object.
	// -> Remarks: This member function returns a CString object that represents the drive 
	//             where the MSDN collection is found.
	CString GetDrive() const;

	// -> Returns: A CString object.
	// -> Remarks: This member function returns a CString object that represents the directory
	//             where the MSDN collection is found.
	CString GetDirectory() const;

protected:

	TCHAR           m_szDrive[_MAX_DRIVE];    // Drive letter, followed by a colon (:)
	TCHAR           m_szDir[_MAX_DIR];        // Directory path, including trailing slash. Forward slashes ( / ), backslashes ( \ ), or both may be used.
	TCHAR           m_szFilename[_MAX_FNAME]; // Base filename (no extension)
	TCHAR           m_szExt[_MAX_EXT];        // Filename extension, including leading period (.)
	TCHAR			m_szWinDir[_MAX_PATH];    // Full path of the Windows directory.
	CString			m_strMSDNRegistry;	      // Full path to hhcolreg.dat
	CString			m_strMSDNCollection;      // Full path to the MSDN collection file
	CString			m_strColName;             // Name of the MSDN collection file minus path.
	CString			m_strColNum;              // Current collection number
	CString			m_strLangId;              // Current collection language id
	CString			m_strTitleString;         // Title to be displayed in the contents tab of the MSDN collection.
	CString			m_strUniqueID;            // Unique identifier of the help to be added.
	CString			m_strChmFile;             // Full path to the .chm file to be added.
	CString			m_strChiFile;             // Full path to the .chi file to be added.
	CString			m_strHelpVer;             // Current version of the help to be added.
	CProgressCtrl*	m_pProgress;              // Control to display the integration progress, can be NULL.
};

//////////////////////////////////////////////////////////////////////

inline CString CMSDNIntegration::GetRegistryFile() const {
	return m_strMSDNRegistry;
}

inline CString CMSDNIntegration::GetCollectionFile() const {
	return m_strMSDNCollection;
}

inline CString CMSDNIntegration::GetCollectionName() const {
	return m_strColName;
}

inline CString CMSDNIntegration::GetCollectionNumber() const {
	return m_strColNum;
}

inline CString CMSDNIntegration::GetLanguageID() const {
	return m_strLangId;
}

inline CString CMSDNIntegration::GetUniqueID() const {
	return m_strUniqueID;
}

inline CString CMSDNIntegration::GetTitleString() const {
	return m_strTitleString;
}

inline CString CMSDNIntegration::GetChmFile() const {
	return m_strChmFile;
}

inline CString CMSDNIntegration::GetChiFile() const {
	return m_strChiFile;
}

inline CString CMSDNIntegration::GetHelpVer() const {
	return m_strHelpVer;
}

inline CProgressCtrl* CMSDNIntegration::GetProgressCtrl() const {
	return m_pProgress;
}

inline CString CMSDNIntegration::GetWindowsDir() const {
	return m_szWinDir;
}

inline CString CMSDNIntegration::GetDrive() const {
	return m_szDrive;
}

inline CString CMSDNIntegration::GetDirectory() const {
	return m_szDrive;
}

inline void CMSDNIntegration::SetTitleString(LPCTSTR lpszTitleString) {
	ASSERT(_tcslen(lpszTitleString));
	m_strTitleString = lpszTitleString;
}

inline void CMSDNIntegration::SetChmFile(LPCTSTR lpszChmFile) {
	ASSERT(_tcslen(lpszChmFile)); m_strChmFile = lpszChmFile;
}

inline void CMSDNIntegration::SetChiFile(LPCTSTR lpszChiFile) {
	ASSERT(_tcslen(lpszChiFile)); m_strChiFile = lpszChiFile;
}

inline void CMSDNIntegration::SetHelpVer(LPCTSTR lpszHelpVer) {
	ASSERT(_tcslen(lpszHelpVer));
	m_strHelpVer = lpszHelpVer;
}

//////////////////////////////////////////////////////////////////////
// CLoadLibrary:
// Helper class used to load a dll and get the current version.
//

class CLoadLibrary
{
public:

    // -> Input:   lpszLibFileName - Pointer to a null-terminated string 
	//                               that names the executable module (DLL file).
    // -> Remarks: Constructs a CLoadLibrary object.
	CLoadLibrary(LPCTSTR lpszLibFileName);

    // -> Remarks: Destroys a CLoadLibrary object, handles cleanup and de-allocation.
	virtual ~CLoadLibrary();

	// -> Returns: Returns the module handle attached to the CLoadLibrary object.
	// -> Remarks: Use this operator to get the attached module handle of the 
	//             CLoadLibrary object. This operator is a casting operator, which 
	//             supports direct use of an HINSTANCE object.
	operator HINSTANCE();

	// -> Returns: A DWORD value if successful, otherwise 0L.
	// -> Remarks: Use this member function to return the version number of the
	//             module attached to this CLoadLibrary object. The high-order 
	//             word of the return value represents the major version number and
	//             the low-order word of the returned value represents the minor
	//             version number.
	DWORD GetModuleVersion();

protected:

	HINSTANCE m_hLibModule; // Handle of the currently loaded module.

};

#endif // !defined(__MSDNINTEGRATION_H__)
