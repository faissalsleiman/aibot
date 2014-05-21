#
# Configuration file for the gnumake 
# build system for RebeccaAIML.
# 
# Author: Frank Hassanabad : foreverlinux@yahoo.com 
# Drop me a line if you're having troubles or if 
# this does not work correctly and I'll fix it.
#

#
# Xerces 2.6 and Boost 3.2 should be installed.
# Use these variables to setup their location
#
# They should point to their include directories if 
# XERCES_INCLUDE or BOOST_INCLUDE 
# and to their release library directory if
# XERCES_LIB or BOOST_LIB 
# and to their debug library directory if 
# XERCES_LIBD or BOOST_LIBD


XERCES_INCLUDE=/usr/local/include
XERCES_LIB=/usr/local/lib 
XERCES_LIBD=/usr/local/lib
 
BOOST_INCLUDE=/usr/include
BOOST_LIB=/usr/lib
BOOST_LIBD=/usr/lib

#
# Different installs of boost yield 
# different archive names.  Choose the 
# one you want to use and set it here.
# 
# These are for the release build
#
BOOST_LIB_FILESYS=libboost_filesystem.a
BOOST_LIB_REGEX=libboost_regex.a
BOOST_LIB_DATE=libboost_date_time.a


#
# These are for the debug build
# 
BOOST_LIB_FILESYSD=libboost_filesystem.a
BOOST_LIB_REGEXD=libboost_regex.a
BOOST_LIB_DATED=libboost_date_time.a

#
# These are the C++ flags for Release
#
CXXFLAGS_RELEASE=-O2 -fPIC -Wall

#
# These are the C++ flags for Debug
#
CXXFLAGS_DEBUG=-ggdb -fPIC -Wall

#
# Location of doxygen
#
DOXYGEN=/usr/bin/doxygen

#
# Location of where to put the distrubtion
# if you call "make dist"
#
REBECCA_DIST_LOC=${HOME}



