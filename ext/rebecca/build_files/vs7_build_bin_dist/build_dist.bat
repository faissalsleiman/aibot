@echo OFF

REM =========================================================
REM Makes a distribution from RebeccaAIML source files.

REM Prereq's:
REM Make sure you have installed both BOOST and XERCES 
REM as well as defined environment variables for them.
REM See [doc\windowsInstall.txt] for details of this.

REM Also, make sure that you have put the xerces-c_2_6.dll
REM in the bin\release directory of this source distribution
REM before running this script.

REM Also, you will need doxygen installed and in your path
REM for the doxygen'ation to work
REM =========================================================

REM Call the enviornment variables script to setup the environment variables.
call environment_variables.cmd

REM Copy the common files that are the same between this batch file and build_dist batch file
set REBECCA_COMMON_ROOT=%REBECCA_DIST_DIR%
call copy_common_files.bat

echo compiling Rebecca AIML source code and samples and regression test suite.  
echo This takes a while please be patient...
echo Compiling core and regression test suite...
%DOT_NET_HOME%\devenv.exe ..\..\build_files\vs7_tests\regression\regression.sln /rebuild release 
echo Compiling console sample...
%DOT_NET_HOME%\devenv.exe ..\..\src\samples\console\console.sln /rebuild release
echo Compiling console AIML HTML converter...
%DOT_NET_HOME%\devenv.exe ..\..\src\samples\consoleHtmlConverter_tag_layer\consoleAIMLHtmlConverter.sln /rebuild release
echo Compiling Qt GUI...
qmake ..\..\src\samples\qtgui\qtgui.pro -o ..\..\src\samples\qtgui\qtgui
%DOT_NET_HOME%\devenv.exe ..\..\src\samples\qtgui\qtgui.vcproj /rebuild release

echo copying all binaries to distro
xcopy %LIBS_BIN_DIR%\console.exe %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\rebecca-mt.dll %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\rebecca-mt.lib %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\xerces-c_2_6.dll %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\consoleAIMLHtmlConverter.exe %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\qtgui.exe %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\customHtmlTagLayer.dll %REBECCA_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\regression.exe %REBECCA_DIST_DIR%\bin\release /y

xcopy %MSVCRT71_DLL% %REBECCA_DIST_DIR%\bin\release /y
xcopy %QTDIR%\lib\QtCore4.dll %REBECCA_DIST_DIR%\bin\release /y
xcopy %QTDIR%\lib\QtGui4.dll %REBECCA_DIST_DIR%\bin\release /y

REM Finally let us zip everything up with 7zip
%SEVEN_ZIP_BIN% a -tzip %REBECCA_COMMON_ROOT%.zip %REBECCA_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -ttar %REBECCA_COMMON_ROOT%.tar %REBECCA_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -tgzip %REBECCA_COMMON_ROOT%.tar.gz %REBECCA_COMMON_ROOT%.tar
del %REBECCA_COMMON_ROOT%.tar

