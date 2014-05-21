#!/bin/sh

echo "[Bootstraping in current directory]"

echo Calling aclocal
aclocal 

echo Calling autoconf
autoconf

echo Calling automake
automake
echo ""

# If we don't have any parameters then don't
# do a recursive bootstrap
if [ $# -eq 0 ]
then
   exit 0
fi

echo "[Booststraping in lib directory]"
cd lib
./bootstrap.sh
cd ..
echo ""

echo "[Boostraping in console directory]"
cd console
./bootstrap.sh
cd ..
echo  ""

echo "[Boostraping in consoleHtmlConverter_tag_layer]"
cd consoleHtmlConverter_tag_layer 
./bootstrap.sh
cd ..
echo ""

echo "[Boostraping in qtgui directory]"
cd qtgui 
./bootstrap.sh
cd ..
echo ""

echo "[Boostraping in scripts directory]"
cd scripts 
./bootstrap.sh
cd ..
echo ""

echo "[Boostraping in regression directory]"
cd regression 
./bootstrap.sh
cd ..
