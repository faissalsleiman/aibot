If you have the binary distribution you should see 
several files here.  If you have the source distribution 
you will see several files here if the build builds 
correctly.

[rebecca-mt.dll] or [rebecca-mt.so]
               
               This is the built dll or shared object in which
               all the executables above rely on.  This is the 
               RebeccaAIML core engine.  When you build programs
               you link to this dll or shared object.  
			   
			   Under Linux this will be in [/usr/lib]



[rebecca-mt.lib] 
               
               This is only on Windows.  Use this to link your
               applications to that are going to be using the
               rebecca-mt.dll for developing applications against
               the RebeccaAIML api.  See your Visual Studio 7.1
               guide on linking against libs for using dll's for
               further information.



[regression.exe] or [regression]
               
               The regression test suite.  This runs against a 
               set of tests located at [resources\testing].  It
               reads in [AIML.xml] for input and expected output
               of the AIML file [AIML.aiml] and outputs an html
               page in this directory of which tests passed and
               which have failed.  Note, that the webpage outputed
               will be incomplete and ugly without the style sheet 
			   and images commonly found on the RebeccaAIML web 
			   page but it will still be readable.
               
[console.exe] or [console]

               This is built from the sample at 
               [src\samples\console] This is a bare bones 
               simple console example.  In a few lines of code 
               it shows how to integrate the Rebecca engine 
               into your C++ code.  Run this to start up a 
               console session connected to the AIML engine.
			   
			   Under Linux this will be in 
			   [/usr/share/Rebecca/bin/release] and a shell 
			   script that executes it will be in
			   [/usr/bin].
			   
			   

			   
			   
[qtgui.exe] or [qtgui]

			   This is built from the sample at 
			   [src\samples\qtgui].  This sample shows how to 
			   use a QT GUI to hook up to RebeccaAIML.
			   
			   Under Linux this will be in 
			   [/usr/share/Rebecca/bin/release] and a shell
			   script that executes it will be in [/usr/bin]
               

			   
[consoleAIMLHtmlConverter.exe]  or [consoleAIMLHtmlConverter]
               
               This is built from the sample at 
               [src\samples\consoleHtmlConverter_tag_layer].
               It is a complete program that converts AIML XML files
               into html pages with links.  The html pages provide 
               a way to "cruise" through the AIML brain and see how 
               the brain would look like in memory.

			   Under Linux this will be in 
			   [/usr/share/Rebecca/bin/release] and a shell
			   script that executes it will be in [/usr/bin]
	       
               
[customHtmlTagLayer.dll] or [customHtmlTagLayer.so]
               
               This is built from the sample at
               [src\samples\consoleHtmlConverter_tag_layer].
               It is the dll or shared object "layer" which 
               redefines the AIML XML Tags to write out html
               pages. consoleAIMLHtmlConverter registers this
               dll or shared object with rebecca-mt

			   Under Linux this will be in [/usr/lib]

			   
[xerces-c_2_6.dll]
               
               Provided for Windows users for convience.  For 
               Linux users this is probably included in your 
               distribution already.  Under the covers in the 
               rebecca-mt.dll engine it uses xerces for parsing
               the xml files.

			   Under Linux this will be in [/usr/lib]

               
[msvcr71.dll]  

               This is the Visual Studio 7.1 dll that is used
               by all executables and dlls here since they are 
               built using Visual Studio 7.1.  This only exists
               on Windows.


			   
[QtCore4.dll]
			   This is a QT dll that is used by the qtgui executable


			   
[QtGui4.dll]   This is a QT dll that is used by the qtgui executable
              

			  