AUTOMAKE_OPTS = gnu
bin_PROGRAMS = regression

INCLUDES=-I../../../include -I../../../src/tests/regression/include

regression_LDADD=../lib/librebecca-mt.la

regression_SOURCES = ../../../src/tests/regression/main.cpp \
					 ../../../src/tests/regression/TestCases.cpp \
					 ../../../src/tests/regression/TestCasesHandler.cpp

