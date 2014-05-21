#
# Gnumakefile for 
# the AIML C++ project Rebecca
# By: Frank Hassanabad : foreverlinux@yahoo.com
# Drop me a line if anything is messed up

#
# Version for the "make dist"
#
REBECCA_VER=984

# # Config file to control this build
#
#
include config.mk

# 
# The object variable 
# which holds all objects to
# compile
# 
include sourceFiles.mk

#
# Check to make sure all prerequiste 
# environment variables are defined
#
include prerequistesTest.mk



ifdef debug
    LIB_DIR ?= debug
	# D suffix is to reference either a release or a debuggable variable above 
	D_SUFFIX = D
	BOOST_LINK_LIB=${BOOST_LIBD}/${BOOST_LIB_FILESYSD}\
	               ${BOOST_LIBD}/${BOOST_LIB_REGEXD}\
				   ${BOOST_LIBD}/${BOOST_LIB_DATED}
else
    LIB_DIR ?= release
	BOOST_LINK_LIB=${BOOST_LIB}/${BOOST_LIB_FILESYS}\
	               ${BOOST_LIB}/${BOOST_LIB_REGEX}\
				   ${BOOST_LIBD}/${BOOST_LIB_DATE}
endif

ifdef debug
	DEFINES += -DBOT_USE_STACK_TRACE
	DEFINES += -DBOT_USE_LOGGING
endif

ROOT_DIR    ?= ../..
BIN_DIR     ?= ${ROOT_DIR}/bin
BIN_LIB_DIR ?= ${BIN_DIR}/${LIB_DIR}

#
# All source directories
#
SRC_DIR   ?= ${ROOT_DIR}/src
TESTS_DIR ?= ${SRC_DIR}/tests
BOT_DIR   ?= ${SRC_DIR}/rebecca
ADT_DIR   ?= ${BOT_DIR}/adt
IMPL_DIR  ?= ${BOT_DIR}/impl
UTILS_DIR ?= ${IMPL_DIR}/utils
FRAMEWORK_DIR ?= ${BOT_DIR}/framework
#
# All test source directories
#
#
GRAPH_BUILD_DIR ?= ${TESTS_DIR}/graph-building
GRAPH_BUILD_EXE ?= ${BIN_LIB_DIR}/graph-building

REGRESSION_BUILD_DIR ?= ${TESTS_DIR}/regression
REGRESSION_BUILD_EXE ?= ${BIN_LIB_DIR}/regression


#
# All include directories
#
BASE_INCLUDE  ?= ${ROOT_DIR}/include
BOT_INCLUDE   ?= ${BASE_INCLUDE}/rebecca
IMPL_INCLUDE  ?= ${BOT_INCLUDE}/impl
UTILS_INCLUDE ?= ${IMPL_INCLUDE}/utils
ADT_INCLUDE   ?= ${BASE_INCLUDE}/adt

#
# Flags for rebecca
#
ifdef debug
    CXXFLAGS = ${CXXFLAGS_DEBUG}
else
	CXXFLAGS = ${CXXFLAGS_RELEASE}
endif

#
# Flags for the test modules
#
TESTCXXFLAGS = ${CXXFLAGS}
TESTCXXFLAGS -= -fPIC

#
# Xerces
#
XERCES_INC     ?= -I${XERCES_INCLUDE}
XERCES_LINK    ?= -L${XERCES_LIB${D_SUFFIX}} -lxerces-c
XERCES_RPATH   ?= -Wl,-rpath=${XERCES_LIB${D_SUFFIX}}

#
# Boost
#
BOOST_INC ?= -I${BOOST_INCLUDE}

# 
# Includes
# 
INCLUDES += -I${ROOT_DIR}/include 
INCLUDES += -I${UTILS_INCLUDE}
INCLUDES += ${XERCES_INC}
INCLUDES += ${BOOST_INC}

#
# Linker lines
#
#
LINK     += ${XERCES_LINK}
LINK     += ${BOOST_LINK_LIB}
LINK     += -ldl 
TEST_LINK += -Wl,-rpath=./

#
# Shared object I am creaing
# and the location of it
#
#
bot_sh_obj = ${BIN_DIR}/${LIB_DIR}/librebecca-mt.so


#
# Redefinition rule
#
%.o : %.cpp
	${CXX} ${CXXFLAGS} ${DEFINES} ${INCLUDES} -c $< -o $@

#
# All target to create everything
#
all: ${BIN_LIB_DIR} ${objects} ${bot_sh_obj} 

#
# Create directory if it does not exist
#
${BIN_LIB_DIR}:
	mkdir -p $@

#
# dependencies
#
GraphBuilderAIML.o: ${IMPL_INCLUDE}/GraphBuilder.h

${bot_sh_obj}: ${objects}
	gcc -shared -Wl,-soname,librebecca-mt.so \
    -o $@ ${objects} ${LINK} ${XERCES_RPATH} 

#
# Tests
#
tests: ${GRAPH_BUILD_EXE} ${REGRESSION_BUILD_EXE}

${GRAPH_BUILD_EXE}: ${objects} ${bot_sh_obj} ${GRAPH_BUILD_DIR}/main.cpp
	${CXX} ${GRAPH_BUILD_DIR}/main.cpp \
	${TESTCXXFLAGS} ${DEFINES} ${INCLUDES}\
   	-L${BIN_LIB_DIR} -o $@ ${TEST_LINK} ${XERCES_RPATH} -lrebecca-mt

#
# TODO Change this from this hacked shell script like thing 
# to a good build mechanism.
#
${REGRESSION_BUILD_EXE}: ${objects} \
                      	 ${bot_sh_obj} \
						 ${REGRESSION_BUILD_DIR}/main.cpp \
						 ${REGRESSION_BUILD_DIR}/TestCases.cpp \
						 ${REGRESSION_BUILD_DIR}/TestCasesHandler.cpp
	${CXX} ${DEFINES} ${INCLUDES} ${TESTCXXFLAGS} -I${REGRESSION_BUILD_DIR}/include -c ${REGRESSION_BUILD_DIR}/main.cpp -o ${REGRESSION_BUILD_DIR}/main.o
	${CXX} ${DEFINES} ${INCLUDES} ${TESTCXXFLAGS} -I${REGRESSION_BUILD_DIR}/include -c ${REGRESSION_BUILD_DIR}/TestCases.cpp -o ${REGRESSION_BUILD_DIR}/TestCases.o	 
	${CXX} ${DEFINES} ${INCLUDES} ${TESTCXXFLAGS} -I${REGRESSION_BUILD_DIR}/include -c ${REGRESSION_BUILD_DIR}/TestCasesHandler.cpp -o ${REGRESSION_BUILD_DIR}/TestCasesHandler.o
	${CXX} ${DEFINES} ${INCLUDES} ${TESTCXXFLAGS} -I${REGRESSION_BUILD_DIR}/include -L${BIN_LIB_DIR} ${REGRESSION_BUILD_DIR}/*.o -o $@ ${TEST_LINK} ${XERCES_RPATH} -lrebecca-mt


#
# Clean the project
#
clean:
	-rm ${objects}
	-rm ${bot_sh_obj}


#
# All this is just for dist 
#
REBECCA_ROOT=../..
AIML_DIR=${REBECCA_ROOT}/aiml
REBECCA_DIST_DIR=${REBECCA_DIST_LOC}/RebeccaAIML-${REBECCA_VER}
ANNOTATED_ALICE_DIR=${AIML_DIR}/annotated_alice
LIBS_BIN_DIR=${REBECCA_ROOT}/bin/release

dist: all
	-@echo creating dist directory
	-mkdir ${REBECCA_DIST_DIR}

	-@echo creating aiml directory
	-mkdir ${REBECCA_DIST_DIR}/aiml

	-@echo creating bin directory
	-mkdir ${REBECCA_DIST_DIR}/bin

	-@echo creating doc directories
	-mkdir ${REBECCA_DIST_DIR}/doc
	-mkdir ${REBECCA_DIST_DIR}/doc/api
	-mkdir ${REBECCA_DIST_DIR}/doc/api+framework
	-mkdir ${REBECCA_DIST_DIR}/doc/api+framework+samples
	-mkdir ${REBECCA_DIST_DIR}/doc/api+samples

	-@echo creating include directory
	-mkdir ${REBECCA_DIST_DIR}/include

	-@echo creating include/rebecca directory
	-mkdir ${REBECCA_DIST_DIR}/include/rebecca

	-@echo creating include/rebecca/framework directory
	-mkdir ${REBECCA_DIST_DIR}/include/rebecca/framework

	-@echo creating resources directory
	-mkdir ${REBECCA_DIST_DIR}/resources

	-@echo creating the pictures directory
	-mkdir ${REBECCA_DIST_DIR}/resources/pictures

	-@echo creating schema directory
	-mkdir ${REBECCA_DIST_DIR}/resources/schema

	-@echo creating src directory
	-mkdir ${REBECCA_DIST_DIR}/src

	-@echo creating src/samples directory
	-mkdir ${REBECCA_DIST_DIR}/src/samples

	-@echo creating src/samples/console directory
	-mkdir ${REBECCA_DIST_DIR}/src/samples/console

	-@echo creating src/samples/consoleHtmlConverter_tag_layer directory
	-mkdir ${REBECCA_DIST_DIR}/src/samples/consoleHtmlConverter_tag_layer

	-@echo creating src/samples/qtgui directory
	-mkdir ${REBECCA_DIST_DIR}/src/samples/qtgui

	-@echo creating annotated_alice directory
	-mkdir ${REBECCA_DIST_DIR}/aiml/annotated_alice

	-@echo creating release directory
	-mkdir ${REBECCA_DIST_DIR}/bin/release

	-@echo creating conf directory
	-mkdir ${REBECCA_DIST_DIR}/conf

	-@echo copying annotated alice files to distro
	-cp ${ANNOTATED_ALICE_DIR}/*.aiml ${REBECCA_DIST_DIR}/aiml/annotated_alice 

	-@echo creating doxygen of source code
	-cd ${REBECCA_ROOT}/doc/doxygen;doxygen Doxyfile_api;doxygen Doxyfile_api+framework;doxygen Doxyfile_api+framework+samples;doxygen Doxyfile_api+samples 

	-@echo copying doxygen to distro
	-cp -R ${REBECCA_ROOT}/doc/doxygen/api ${REBECCA_DIST_DIR}/doc/api 
	-cp -R ${REBECCA_ROOT}/doc/doxygen/api+framework ${REBECCA_DIST_DIR}/doc/api 
	-cp -R ${REBECCA_ROOT}/doc/doxygen/api+framework+samples ${REBECCA_DIST_DIR}/doc/api 
	-cp -R ${REBECCA_ROOT}/doc/doxygen/api+samples ${REBECCA_DIST_DIR}/doc/api 

	-@echo copying header files
	-cp ${REBECCA_ROOT}/include/rebecca/*.h ${REBECCA_DIST_DIR}/include/rebecca 
	-cp ${REBECCA_ROOT}/include/rebecca/framework/*.h ${REBECCA_DIST_DIR}/include/rebecca/framework

	-@echo copying schemas
	-cp ${REBECCA_ROOT}/resources/schema/*.xsd ${REBECCA_DIST_DIR}/resources/schema

	-@echo copying the pictures for qtgui
	-cp ${REBECCA_ROOT}/resources/pictures/*.* ${REBECCA_DIST_DIR}/resources/pictures

	-@echo copying sample xsds
	-cp ${REBECCA_ROOT}/conf/*.xml ${REBECCA_DIST_DIR}/conf 

	-@echo copying the Readmes and other relivant files
	-cp ${REBECCA_ROOT}/Authors.txt ${REBECCA_DIST_DIR} 
	-cp ${REBECCA_ROOT}/license.txt ${REBECCA_DIST_DIR} 
	-cp ${REBECCA_ROOT}/README.txt ${REBECCA_DIST_DIR} 
	-cp ${REBECCA_ROOT}/ReleaseNotes.txt ${REBECCA_DIST_DIR} 
	-cp ${REBECCA_ROOT}/aiml/README.txt ${REBECCA_DIST_DIR}/aiml
	-cp ${REBECCA_ROOT}/bin/release/README.txt ${REBECCA_DIST_DIR}/bin/release 
	-cp ${REBECCA_ROOT}/conf/README.txt ${REBECCA_DIST_DIR}/conf 
	-cp ${REBECCA_ROOT}/resources/schema/README.txt ${REBECCA_DIST_DIR}/resources/schema 
	-cp ${REBECCA_ROOT}/src/samples/README.txt ${REBECCA_DIST_DIR}/src/samples
	-cp ${REBECCA_ROOT}/src/samples/console/README.txt ${REBECCA_DIST_DIR}/src/samples/console
	-cp ${REBECCA_ROOT}/src/samples/consoleHtmlConverter_tag_layer/README.txt ${REBECCA_DIST_DIR}/src/samples/consoleHtmlConverter_tag_layer
	-cp ${REBECCA_ROOT}/src/samples/qtgui/README.txt ${REBECCA_DIST_DIR}/src/samples/qtgui
	-cp ${REBECCA_ROOT}/doc/doxygen/README.txt ${REBECCA_DIST_DIR}/doc
	-cp ${REBECCA_ROOT}/doc/doxygen/README.txt ${REBECCA_DIST_DIR}/doc

	-echo Creating console app
	-cd ${REBECCA_ROOT}/src/samples/console; make
	
	-echo Creating consoleHtmlConverter app
	-cd ${REBECCA_ROOT}/src/samples/consoleHtmlConverter_tag_layer; make

	-echo Creating qtgui app
	-cd ${REBECCA_ROOT}/src/samples/qtgui; qmake; make

	-echo copying console sample
	-cp ${REBECCA_ROOT}/src/samples/console/console.cpp ${REBECCA_DIST_DIR}/src/samples/console 
	-cp ${REBECCA_ROOT}/src/samples/console/Makefile ${REBECCA_DIST_DIR}/src/samples/console 

	-echo copying consoleHtmlConverter sample
	-cp ${REBECCA_ROOT}/src/samples/consoleHtmlConverter_tag_layer/*.cpp ${REBECCA_DIST_DIR}/src/samples/consoleHtmlConverter_tag_layer
	-cp ${REBECCA_ROOT}/src/samples/consoleHtmlConverter_tag_layer/*.h ${REBECCA_DIST_DIR}/src/samples/consoleHtmlConverter_tag_layer
	-cp ${REBECCA_ROOT}/src/samples/consoleHtmlConverter_tag_layer/Makefile ${REBECCA_DIST_DIR}/src/samples/consoleHtmlConverter_tag_layer

	-echo copying the qtgui sample
	-cp ${REBECCA_ROOT}/src/samples/qtgui/*.cpp ${REBECCA_DIST_DIR}/src/samples/qtgui
	-cp ${REBECCA_ROOT}/src/samples/qtgui/*.h ${REBECCA_DIST_DIR}/src/samples/qtgui
	-cp ${REBECCA_ROOT}/src/samples/qtgui/*.pro ${REBECCA_DIST_DIR}/src/samples/qtgui

	-echo copying all binaries to distro
	-cp ${LIBS_BIN_DIR}/console ${REBECCA_DIST_DIR}/bin/release
	-cp ${LIBS_BIN_DIR}/librebecca-mt.so ${REBECCA_DIST_DIR}/bin/release 
	-cp ${LIBS_BIN_DIR}/consoleAIMLHtmlConverter ${REBECCA_DIST_DIR}/bin/release
	-cp ${LIBS_BIN_DIR}/libcustomHtmlTagLayer.so ${REBECCA_DIST_DIR}/bin/release
	-cp ${LIBS_BIN_DIR}/qtgui ${REBECCA_DIST_DIR}/bin/release

