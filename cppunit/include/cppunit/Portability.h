#ifndef CPPUNIT_PORTABILITY_H
#define CPPUNIT_PORTABILITY_H

/* include platform specific config */
#if defined(__BORLANDC__)
#    include <cppunit/config-bcb5.h>
#elif defined (_MSC_VER)
#    include <cppunit/config-msvc6.h>
#else
#    include <cppunit/config-auto.h>
#endif


/* Options that the library user may switch on or off.
 * If the user has not done so, we chose default values.
 */


/* Define to 1 if you wish to have the old-style macros
   assert(), assertEqual(), assertDoublesEqual(), and assertLongsEqual() */
#ifndef CPPUNIT_ENABLE_NAKED_ASSERT
#define CPPUNIT_ENABLE_NAKED_ASSERT         0
#endif


/* Define to 1 if the preprocessor expands (#foo) to "foo" (quotes incl.) */
#ifndef CPPUNIT_HAVE_CPP_SOURCEANNOTATION
#define CPPUNIT_HAVE_CPP_SOURCEANNOTATION   1
#endif



/* perform portability hacks */


/* Define CPPUNIT_SSTREAM as a stream with a "std::string str()"
 * method.
 */
#include <string>

#if CPPUNIT_HAVE_SSTREAM
#   include <sstream>
    namespace CppUnit {
	typedef std::ostringstream  OStringStream;
    }
#else 
#if CPPUNIT_HAVE_STRSTREAM
#   include <strstream.h>
    namespace CppUnit {
	class OStringStream : public std::ostrstream 
	{
	public:
	    std::string str()
	    {
		(*this) << '\0';
		std::string msg(ostrstream::str());
		ostrstream::freeze(false);
		return msg;
	    }
	};
    }
#else
#   error Cannot define CppUnit::OStringStream.
#endif
#endif


#if _MSC_VER > 1000     // VC++
#pragma once
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000


#endif // CPPUNIT_PORTABILITY_H
