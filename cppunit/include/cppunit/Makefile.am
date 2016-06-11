SUBDIRS = extensions ui plugin config tools portability

DISTCLEANFILES = config-auto.h

libcppunitincludedir = $(includedir)/cppunit
libcppunitinclude_HEADERS =  \
	config-auto.h \
	version.h \
	AdditionalMessage.h \
	Asserter.h \
	BriefTestProgressListener.h \
	CompilerOutputter.h \
	Exception.h \
	Message.h \
	Outputter.h \
	Portability.h \
	Protector.h \
	SourceLine.h \
	SynchronizedObject.h \
	TestAssert.h \
	TestCaller.h \
	TestCase.h \
	TestComposite.h \
	TestFailure.h \
	TestFixture.h \
	Test.h \
	TestLeaf.h \
	TestListener.h \
	TestPath.h \
	TestResultCollector.h \
	TestResult.h \
	TestRunner.h \
	TestSuccessListener.h \
	TestSuite.h \
	TextOutputter.h \
	TextTestProgressListener.h \
	TextTestResult.h \
	TextTestRunner.h \
	XmlOutputter.h \
	XmlOutputterHook.h

dist-hook:
	rm -f $(distdir)/config-auto.h
