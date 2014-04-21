#
# Check to make sure all prerequistes are 
# defined
#

ifndef XERCES_INCLUDE
	$(warning You need to have XERCES_INCLUDE environment variable defined)
	$(error For example, in your .bashrc enter "export XERCES_INCLUDE=<location of xerces headers>")
endif

ifndef XERCES_LIB
	$(warning You need to have XERCES_LIB environment variable defined)
	$(error For example, in your .bashrc enter "export XERCES_LIB=<location of xerces libs>")
endif

ifndef XERCES_LIBD
	$(warning You need to have XERCES_LIBD environment variable defined)
	$(warning For example, in your .bashrc enter "export XERCES_LIBD=<location of xerces deuggable lib>")
	$(warning Notice, since this is linux it can be the same location as your relase version)
	$(error If it is then, in your .bashrc enter "export XERCES_LIBD=${XERCES_LIB}")
endif


ifndef BOOST_INCLUDE
	$(warning You need to have BOOST_INCLUDE environment variable defined)
	$(error For example, in your .bashrc enter "export BOOST_INCLUDE=<location of your boost headers>")
endif

ifndef BOOST_LIB
	$(warning You need to have BOOST_LIB environment variable defined)
	$(error For example, in your .bashrc eneter "export BOOST_LIB=<location of your boost library>")
endif

ifndef BOOST_LIBD
	$(warning You need to have BOOST_LIBD environment variable defined)
	$(warning For example, in your .bashrc eneter "export BOOST_LIBD=<location of your boost debuggable library>")
	$(warning Notice, since this is linux it can be the same location as your relase version)
	$(error If it is then, in your .bashrc enter "export BOOST_LIBD=${BOOST_LIB}")
endif

