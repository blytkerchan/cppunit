// Utility.cpp: implementation of the Utility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Utility.h"


CString GetFullPath( CString path )
{
  try
  {
    return CFile( path, CFile::modeRead ).GetFilePath();
  }
  catch ( CFileException *e )
  {
    e->Delete();
  }
  return "";
}
