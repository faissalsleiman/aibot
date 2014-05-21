@echo OFF

REM =========================================================
REM These are the common enviornment variables of RebeccaAIML
REM All dos scripts in this directory should call this first to get the environment variables.
REM Change these to your likeing and to where all your appropriate tools and libraries are.

REM =====================================================================================================================================================================================
REM Change these to the right variables

REM Version of Rebecca you are creating
set REBECCA_VER=9871

REM Where you want the distribution and source code to be prodcued at
set REBECCA_DIST_LOC=C:

REM Location of the Microsoft compiler
set DOT_NET_HOME="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE"

REM Location of the msvcr71.dll to copy
set MSVCRT71_DLL="C:\Program Files\Microsoft Visual Studio .NET 2003\Visual Studio .NET Enterprise Architect 2003 - English\msvcr71.dll"

REM Location of the free zip program, 7Zip
set SEVEN_ZIP_BIN="C:\Program Files\7-Zip\7z"

REM Location of the dos2unix program needed for converting the autoconf files
set DOS_TO_UNIX_BIN="C:\Program Files\uddu\dos2unix.exe"

REM Probably don't need to change these.  These are hardcoded to what the current rebecca directory structure is 
set REBECCA_ROOT=..\..
set AIML_DIR=%REBECCA_ROOT%\aiml
set REBECCA_DIST_DIR=%REBECCA_DIST_LOC%\RebeccaAIML-%REBECCA_VER%
set REBECCA_SOURCE_DIR=%REBECCA_DIST_LOC%\RebeccaAIML-src-%REBECCA_VER%
set ANNOTATED_ALICE_DIR=%AIML_DIR%\annotated_alice
set LIBS_BIN_DIR=%REBECCA_ROOT%\bin\release



REM End of variables
REM =====================================================================================================================================================================================

echo.
echo environment variables
echo ====================
echo REBECCA_ROOT:
echo %REBECCA_ROOT%
echo.
echo AIML_DIR:
echo %AIML_DIR%
echo.
echo LIBS_BIN_DIR:
echo %LIBS_BIN_DIR%
echo.
echo ANNOTATED_ALICE_DIR:
echo %ANNOTATED_ALICE_DIR%
echo.
echo DOT_NET_HOME: 
echo %DOT_NET_HOME%
echo.
echo REBECCA_VER:
echo %REBECCA_VER%
echo.
echo BOOST_INCLUDE:
echo %BOOST_INCLUDE%
echo.
echo XERCES_INCLUE:
echo %XERCES_INCLUDE%
echo.
echo BOOST_LIB:
echo %BOOST_LIB%
echo.
echo BOOST_LIBD:
echo %BOOST_LIBD%
echo.
echo XERCES_LIB:
echo %XERCES_LIB%
echo.
echo XERCES_LIBD:
echo %XERCES_LIBD%
echo.
echo REBECAA_DIST_LOC
echo %REBECCA_DIST_LOC%
echo ====================
echo.
