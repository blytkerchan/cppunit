echo Windows NT/2000 only script...

SET CPPUNIT_DIR=G:\prg\vc\Lib\cppunit
SET CPPUNIT_VER=1_9_4
SET DIST_NAME=CppUnitMsdnDoc-%CPPUNIT_VER%
SET HELPWORKSHOP=D:\wut\prg\HTML-Help-Workshop\hhw.exe

deltree /y %DIST_NAME%
md %DIST_NAME%
cd %DIST_NAME%

call ..\GenerateDoc.bat %CPPUNIT_DIR%
cd %DIST_NAME%

@echo generating distribution
xcopy ..\*.txt
md Bin
xcopy ..\Bin Bin
xcopy ..\CppUnit-MsdnIntegrator.bat
xcopy ..\MSDN-CppUnit.INI
md CppUnitDoc
xcopy %CPPUNIT_DIR%\doc\html\index.chi CppUnitDoc
xcopy %CPPUNIT_DIR%\doc\html\index.chm CppUnitDoc

cd ..

@echo generating compressed distribution file
zip -9 -r %DIST_NAME%.zip %DIST_NAME%

deltree /y %DIST_NAME%