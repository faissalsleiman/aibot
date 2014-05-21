AUTOMAKE_OPTS = gnu
lib_LTLIBRARIES = libcustomHtmlTagLayer.la

bin_PROGRAMS = consoleAIMLHtmlConverter

INCLUDES=-I../../../include
consoleAIMLHtmlConverter_LDADD=../lib/librebecca-mt.la

noinst_HEADERS = ../../../src/samples/consoleHtmlConverter_tag_layer/CustomAIML.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/CustomTagsImpl.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/CustomTopic.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/exports.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/HtmlConverterInternalProgrammerErrorException.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/Html.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/InnerTemplateAIMLTags.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/Links.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/sanitizeString.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/typedefs.h\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/WebPage.h

libcustomHtmlTagLayer_la_SOURCES =  ../../../src/samples/consoleHtmlConverter_tag_layer/CustomAIML.cpp \
								   ../../../src/samples/consoleHtmlConverter_tag_layer/CustomTagsImpl.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/CustomTopic.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/Html.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/InnerTemplateAIMLTags.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/Links.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/sanitizeString.cpp\
								   ../../../src/samples/consoleHtmlConverter_tag_layer/WebPage.cpp

consoleAIMLHtmlConverter_SOURCES = ../../../src/samples/consoleHtmlConverter_tag_layer/consoleAIMLHtmlConverter.cpp

consoleAIMLHtmlConverterMakefiledir=${datadir}/Rebecca/src/samples/consoleHtmlConverter_tag_layer
consoleAIMLHtmlConverterMakefile_DATA=scripts/Makefile

consoleHtmlConverterdir=${datadir}/Rebecca/src/samples/consoleHtmlConverter_tag_layer
consoleHtmlConverter_DATA=../../../src/samples/consoleHtmlConverter_tag_layer/*.cpp\
                          ../../../src/samples/consoleHtmlConverter_tag_layer/*.txt\
                          ../../../src/samples/consoleHtmlConverter_tag_layer/*.h

