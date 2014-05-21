This directory has each build system capable of building RebeccaAIML.

See the [doc] directory for instructions on how to build with these.

[autoconf]
The autoconf and automake scripts to build the source code 
underneath Linux.

[vs7_dll] 
The solution in here is for building RebeccaAIML on Windows 
using Visual Studio 2003 (7.x).  Use this solution to just 
build the RebeccaAIML dll (rebecca-mt.dll)

[vs7_tests]
This is going to end up being the regression testing suite.
For right now it just contains a link to a graphBuilder 
playground project.  This is under construction, don't use.

[gnumake]
* THIS IS DEPRECATED!!!! USE autoconf instead *
A gnu makefile to build RebeccaAIML on a Linux based system.
Use this if you're wanting to build RebeccaAIML for Linux.

[vs7_build_bin_dist]
This contains a batch file to automate building a RebeccaAIML 
distribution automatically.  Use this if you have the prerequists
of Boost, Xerces, Doxygen installed, and the enviornment 
variables setup and you just want a one click build.

[vs7_dll_all]
This is what I use for building RebeccaAIML dll and the samples.