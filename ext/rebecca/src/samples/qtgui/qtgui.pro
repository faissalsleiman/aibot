######################################################################
# Automatically generated by qmake (2.00a) Sat Feb 18 12:53:51 2006
######################################################################

win32:TEMPLATE = vcapp

!win32:TEMPLATE = app

TARGET = qtgui
DEPENDPATH += .

release {
    DESTDIR = ../../../bin/release
}

debug {
    DESTDIR = ../../../bin/release
}
# Includes
INCLUDEPATH += .
INCLUDEPATH += ../../../include

# Input
HEADERS += MainWindow.h
HEADERS += QtGuiCallBacks.h CustomTextEdit.h AIMLEngineThread.h AIMLEngine.h Arguments.h
SOURCES += main.cpp MainWindow.cpp AIMLEngineThread.cpp AIMLEngine.cpp


# Libs

win32:debug {
	LIBS += ../../../bin/release/rebecca-mt.lib
}

win32:release {
	LIBS += ../../../bin/release/rebecca-mt.lib
}

!win32 {
	LIBS += -L../../../bin/release/
    LIBS += -L../../../build_files/autoconf/lib/.libs
    LIBS += -lrebecca-mt
    LIBS += -Wl,-rpath=./
}

