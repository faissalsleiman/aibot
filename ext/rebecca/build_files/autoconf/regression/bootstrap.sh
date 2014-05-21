#!/bin/sh

echo Calling autoheader
autoheader

echo Calling aclocal
aclocal 

echo Calling libtoolize
libtoolize --force --copy

echo Calling autoconf
autoconf

echo Calling automake
automake

