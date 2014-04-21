AUTOMAKE_OPTS = gnu

# Hand create the qtgui sample
all:
	cd ../../../src/samples/qtgui/ && ${MYQMAKE} "LIBS += -Wl,-rpath=${prefix}/lib" && make

clean:
	cd ../../../src/samples/qtgui/ && ${MYQMAKE} && make clean

# Copy the binary hand created
bin_SCRIPTS=../../../bin/release/qtgui

# Copy the qtgui.pro into the samples
qtguiMakefiledir=${datadir}/Rebecca/src/samples/qtgui
qtguiMakefile_DATA=scripts/qtgui.pro

qtguidir=${datadir}/Rebecca/src/samples/qtgui
qtgui_DATA=../../../src/samples/qtgui/*.cpp\
           ../../../src/samples/qtgui/*.txt\
           ../../../src/samples/qtgui/*.pro\
           ../../../src/samples/qtgui/*.h

