@rem generate doc
@rem %1 : cppunit directory full path

@rem set DIST_DIR to current directory (NT/2000) only
SET DIST_DIR=%~f1
echo Dist dir: %DIST_DIR%

@echo generating documentation
@rem change drive then change directory
%~d1
cd %1\doc
call makedox.bat

@echo **********************************************
@echo PLEASE, CLICK ON THE COMPILE BUTTON
@echo **********************************************
%HELPWORKSHOP% %1\doc\html\index.hhp

@rem change drive then change directory
%~d0
cd %~p0

