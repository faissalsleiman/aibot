AUTOMAKE_OPTIONS = foreign
SUBDIRS =  lib @samples@ scripts 

readmeaimldir=${datadir}/Rebecca/aiml
readmeaiml_DATA=../../aiml/README.txt

doxygen_apidir=${datadir}/Rebecca/doc/api/html/
doxygen_api_frameworkdir=${datadir}/Rebecca/doc/api+framework/html/
doxygen_api_framework_samplesdir=${datadir}/Rebecca/doc/api+framework+samples/html/
doxygen_api_samplesdir=${datadir}/Rebecca/doc/api+samples/html/

doxygen_api_DATA = @doxygen_api@
doxygen_api_framework_DATA = @doxygen_api_framework@
doxygen_api_framework_samples_DATA = @doxygen_api_framework_samples@
doxygen_api_samples_DATA = @doxygen_api_samples@

all: @doxygenate@

doxygenGen: doxygen

doxygen: ../../doc/doxygen/api/html/index.html \
		 ../../doc/doxygen/api+framework/html/index.html \
		 ../../doc/doxygen/api+framework+samples/html/index.html \
		 ../../doc/doxygen/api+samples/html/index.html

../../doc/doxygen/api/html/index.html: 
	cd ../../doc/doxygen/ && doxygen Doxyfile_api
	
../../doc/doxygen/api+framework/html/index.html:
	cd ../../doc/doxygen/ && doxygen Doxyfile_api+framework

../../doc/doxygen/api+framework+samples/html/index.html:
	cd ../../doc/doxygen/ && doxygen Doxyfile_api+framework+samples

../../doc/doxygen/api+samples/html/index.html:
	cd ../../doc/doxygen/ && doxygen Doxyfile_api+samples

