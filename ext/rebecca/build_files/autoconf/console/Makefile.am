AUTOMAKE_OPTS = gnu
bin_PROGRAMS = console

INCLUDES=-I../../../include
console_LDADD=../lib/librebecca-mt.la

console_SOURCES = ../../../src/samples/console/console.cpp

consoleMakefiledir=${datadir}/Rebecca/src/samples/console
consoleMakefile_DATA=scripts/Makefile

consoleSampledir=${datadir}/Rebecca/src/samples/console
consoleSample_DATA=../../../src/samples/console/*.cpp\
                   ../../../src/samples/console/*.txt

