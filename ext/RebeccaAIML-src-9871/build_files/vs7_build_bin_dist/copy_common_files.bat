@echo off
REM =========================================================
REM Copies common files for both distribution and source 
REM Set the variable REBECCA_COMMON_ROOT before calling this script

echo creating dist directory
mkdir %REBECCA_COMMON_ROOT%

echo creating aiml directory
mkdir %REBECCA_COMMON_ROOT%\aiml

echo creating bin directory
mkdir %REBECCA_COMMON_ROOT%\bin

echo creating doc directories
mkdir %REBECCA_COMMON_ROOT%\doc
mkdir %REBECCA_COMMON_ROOT%\doc\api
mkdir %REBECCA_COMMON_ROOT%\doc\api+framework
mkdir %REBECCA_COMMON_ROOT%\doc\api+framework+samples
mkdir %REBECCA_COMMON_ROOT%\doc\api+samples

echo creating include directory
mkdir %REBECCA_COMMON_ROOT%\include

echo creating include\rebecca directory
mkdir %REBECCA_COMMON_ROOT%\include\rebecca

echo creating include\rebecca\framework directory
mkdir %REBECCA_COMMON_ROOT%\include\rebecca\framework

echo creating resources directory
mkdir %REBECCA_COMMON_ROOT%\resources\schema

echo creating the pictures directory
mkdir %REBECCA_COMMON_ROOT%\resources\pictures

echo creating the testing directory
mkdir %REBECCA_COMMON_ROOT%\resources\testing

echo creating src directory
mkdir %REBECCA_COMMON_ROOT%\src

echo creating src\samples directory
mkdir %REBECCA_COMMON_ROOT%\src\samples

echo creating src\samples\console directory
mkdir %REBECCA_COMMON_ROOT%\src\samples\console

echo creating src\samples\consoleHtmlConverter_tag_layer directory
mkdir %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer

echo creating src\samples\qtgui directory
mkdir %REBECCA_COMMON_ROOT%\src\samples\qtgui

echo creating annotated_alice directory
mkdir %REBECCA_COMMON_ROOT%\aiml\annotated_alice

echo creating release directory
mkdir %REBECCA_COMMON_ROOT%\bin\release

echo creating conf directory
mkdir %REBECCA_COMMON_ROOT%\conf

echo copying annotated alice files to distro
xcopy %ANNOTATED_ALICE_DIR%\*.aiml %REBECCA_COMMON_ROOT%\aiml\annotated_alice /y

echo copying header files
xcopy %REBECCA_ROOT%\include\rebecca\*.h %REBECCA_COMMON_ROOT%\include\rebecca /y
xcopy %REBECCA_ROOT%\include\rebecca\framework\*.h %REBECCA_COMMON_ROOT%\include\rebecca\framework /y

echo copying schemas
xcopy %REBECCA_ROOT%\resources\schema\*.xsd %REBECCA_COMMON_ROOT%\resources\schema /y

echo copying the pictures for qtgui
xcopy %REBECCA_ROOT%\resources\pictures\*.* %REBECCA_COMMON_ROOT%\resources\pictures /y

echo copying sample xsd's
xcopy %REBECCA_ROOT%\conf\*.xml %REBECCA_COMMON_ROOT%\conf /y

echo creating doxygen of source code
cd %REBECCA_ROOT%\doc\doxygen
call doxy_it.bat
cd %REBECCA_ROOT%\build_files\vs7_build_bin_dist 

echo copying doxygen to distro
xcopy %REBECCA_ROOT%\doc\doxygen\api %REBECCA_COMMON_ROOT%\doc\api /y /E
xcopy %REBECCA_ROOT%\doc\doxygen\api+framework %REBECCA_COMMON_ROOT%\doc\api+framework /y /E
xcopy %REBECCA_ROOT%\doc\doxygen\api+framework+samples %REBECCA_COMMON_ROOT%\doc\api+framework+samples /y /E
xcopy %REBECCA_ROOT%\doc\doxygen\api+samples %REBECCA_COMMON_ROOT%\doc\api+samples /y /E

echo copying the Readme's and other relivant files
xcopy %REBECCA_ROOT%\Authors.txt %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\license.txt %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\README.txt %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\ReleaseNotes.txt %REBECCA_COMMON_ROOT% /y
xcopy %REBECCA_ROOT%\aiml\README.txt %REBECCA_COMMON_ROOT%\aiml /y
xcopy %REBECCA_ROOT%\bin\release\README.txt %REBECCA_COMMON_ROOT%\bin\release /y
xcopy %REBECCA_ROOT%\conf\README.txt %REBECCA_COMMON_ROOT%\conf /y
xcopy %REBECCA_ROOT%\resources\schema\README.txt %REBECCA_COMMON_ROOT%\resources\schema /y
xcopy %REBECCA_ROOT%\resources\testing\footer.htm %REBECCA_COMMON_ROOT%\resources\testing /y
xcopy %REBECCA_ROOT%\resources\testing\header.htm %REBECCA_COMMON_ROOT%\resources\testing /y
xcopy %REBECCA_ROOT%\resources\testing\AIML.aiml %REBECCA_COMMON_ROOT%\resources\testing /y
xcopy %REBECCA_ROOT%\resources\testing\AIML.xml %REBECCA_COMMON_ROOT%\resources\testing /y
xcopy %REBECCA_ROOT%\src\samples\README.txt %REBECCA_COMMON_ROOT%\src\samples /y
xcopy %REBECCA_ROOT%\src\samples\console\README.txt %REBECCA_COMMON_ROOT%\src\samples\console /y
xcopy %REBECCA_ROOT%\src\samples\consoleHtmlConverter_tag_layer\README.txt %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer /y
xcopy %REBECCA_ROOT%\src\samples\qtgui\README.txt %REBECCA_COMMON_ROOT%\src\samples\qtgui /y
xcopy %REBECCA_ROOT%\include\README.txt %REBECCA_COMMON_ROOT%\include /y
xcopy %REBECCA_ROOT%\doc\doxygen\README.txt %REBECCA_COMMON_ROOT%\doc /y

echo copying console sample
xcopy %REBECCA_ROOT%\src\samples\console\console.cpp %REBECCA_COMMON_ROOT%\src\samples\console /y
xcopy %REBECCA_ROOT%\src\samples\console\console.sln %REBECCA_COMMON_ROOT%\src\samples\console /y
xcopy %REBECCA_ROOT%\src\samples\console\console.vcproj %REBECCA_COMMON_ROOT%\src\samples\console /y

echo copying consoleHtmlConverter_tag_layer sample
xcopy %REBECCA_ROOT%\src\samples\consoleHtmlConverter_tag_layer\*.cpp %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer /y
xcopy %REBECCA_ROOT%\src\samples\consoleHtmlConverter_tag_layer\*.h %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer /y
xcopy %REBECCA_ROOT%\src\samples\consoleHtmlConverter_tag_layer\*.sln %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer /y
xcopy %REBECCA_ROOT%\src\samples\consoleHtmlConverter_tag_layer\*.vcproj %REBECCA_COMMON_ROOT%\src\samples\consoleHtmlConverter_tag_layer /y

echo copying the qtgui sample
xcopy %REBECCA_ROOT%\src\samples\qtgui\*.cpp %REBECCA_COMMON_ROOT%\src\samples\qtgui /y
xcopy %REBECCA_ROOT%\src\samples\qtgui\*.h %REBECCA_COMMON_ROOT%\src\samples\qtgui /y
xcopy %REBECCA_ROOT%\src\samples\qtgui\*.pro %REBECCA_COMMON_ROOT%\src\samples\qtgui /y

