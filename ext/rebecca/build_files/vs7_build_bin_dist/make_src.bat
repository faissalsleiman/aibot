@echo OFF

REM =========================================================
REM Creates the source directory of Rebecca

REM Call the enviornment variables script to setup the environment variables.
call environment_variables.cmd

REM Copy the common files that are the same between this batch file and build_dist batch file
set REBECCA_COMMON_ROOT=%REBECCA_SOURCE_DIR%
call copy_common_files.bat

REM Copy the remaining root files for a source distribution release
xcopy %REBECCA_ROOT%\INSTALL.txt %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\rebecca.spec %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\dev-todo.txt %REBECCA_COMMON_ROOT% /y

REM Copy the WindowsINSTALL.txt and the LinuxInstall.txt files
xcopy %REBECCA_ROOT%\doc\*.txt %REBECCA_COMMON_ROOT%\doc /y

REM Copy the remainder of the doxygen files
mkdir %REBECCA_COMMON_ROOT%\doc\doxygen
xcopy %REBECCA_ROOT%\doc\doxygen\*.bat %REBECCA_COMMON_ROOT%\doc\doxygen /y
xcopy %REBECCA_ROOT%\doc\doxygen\Doxyfile_* %REBECCA_COMMON_ROOT%\doc\doxygen /y
xcopy %REBECCA_ROOT%\doc\doxygen\README.txt %REBECCA_COMMON_ROOT%\doc\doxygen /y 

REM Copy all the build_files since they will be needed for a source distribution
mkdir %REBECCA_COMMON_ROOT%\build_files
xcopy %REBECCA_ROOT%\build_files %REBECCA_COMMON_ROOT%\build_files /y /E /exclude:excluded_files.txt

REM Copy implementation header files
mkdir %REBECCA_COMMON_ROOT%\include\rebecca\adt
mkdir %REBECCA_COMMON_ROOT%\include\rebecca\impl
mkdir %REBECCA_COMMON_ROOT%\include\rebecca\impl\utils
xcopy %REBECCA_ROOT%\include\rebecca\adt\*.h %REBECCA_COMMON_ROOT%\include\rebecca\adt /y
xcopy %REBECCA_ROOT%\include\rebecca\impl\*.h %REBECCA_COMMON_ROOT%\include\rebecca\impl /y
xcopy %REBECCA_ROOT%\include\rebecca\impl\utils\*.h %REBECCA_COMMON_ROOT%\include\rebecca\impl\utils /y

REM Copy remainder of the testing files
mkdir %REBECCA_COMMON_ROOT%\resources\testing
xcopy %REBECCA_ROOT%\resources\testing\*.* %REBECCA_COMMON_ROOT%\resources\testing /y

REM Copy remainder of the source files
mkdir %REBECCA_COMMON_ROOT%\src\rebecca
mkdir %REBECCA_COMMON_ROOT%\src\tests
xcopy %REBECCA_ROOT%\src\rebecca %REBECCA_COMMON_ROOT%\src\rebecca /y /E /exclude:excluded_files.txt
xcopy %REBECCA_ROOT%\src\tests %REBECCA_COMMON_ROOT%\src\tests /y /E /exclude:excluded_files.txt

REM Dos2unix the autoconf files so they will build on Linux systems
for /r %REBECCA_COMMON_ROOT%\build_files\autoconf %%i in (*.*) do %DOS_TO_UNIX_BIN% "%%i"


REM Finally let us zip everything up with 7zip
%SEVEN_ZIP_BIN% a -tzip %REBECCA_COMMON_ROOT%.zip %REBECCA_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -ttar %REBECCA_COMMON_ROOT%.tar %REBECCA_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -tgzip %REBECCA_COMMON_ROOT%.tar.gz %REBECCA_COMMON_ROOT%.tar
del %REBECCA_COMMON_ROOT%.tar


