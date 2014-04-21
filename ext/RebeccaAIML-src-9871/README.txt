------------------------------------------------------------------

* WELCOME!

What's this all about?  This is the RebeccaAIML Project.  

RebeccaAIML is a Windows/Linux Object Oriented C++ chatter 
bot api/interpreter for AIML (Artificial Intelligence Markup 
Language) from the ALICE project. It includes comprehensive 
documentation and samples as well as showcases/teaches popular 
and recent C++ practices.  For more information on AIML see
the AIML web site http://www.alicebot.org/ and the RebeccaAIML
web site http://rebecca-aiml.sourceforge.net/index.htm

------------------------------------------------------------------

* AUTHOR and LICENSE

Who wrote this?  Frank Hassanabad : foreverlinux@yahoo.com
Drop me an email if you have any problems.
See license.txt about the LGPL licence in which 
this project is covered.

------------------------------------------------------------------

* RUNNING THE PRECOMPILED SAMPLES

Want to see what RebeccaAIML can do?  If you downloaded a 
binary distribution you can run the precompiled 
samples that show off RebeccaAIML's API cabilities.  

Under Windows you can find and run the samples from 
[bin\release].  Under Linux you can find and run the samples 
from [/usr/bin]

Note for Linux:  The samples in [/usr/bin] are shell scripts 
that execute the binaries in [/usr/share/Rebecca/bin/release].
This is so you can execute the binaries from anywhere in the 
system and don't have to be in the actual binary's directory.

For more information see the README.txt in [bin\release] 
under Windows and [/usr/share/Rebecca/bin/release] under Linux.

------------------------------------------------------------------

* PROGRAMMING WITH THE API AND FRAMEWORK

So how do you start programming with the API and/or framework?  
For a quick start check out the source code of the samples.  
Under Windows you'll find them under [src\samples].  Under Linux 
you'll find them under [/usr/share/Rebecca/src/samples].  Each 
sample has a build file for both Windows and Linux.

See the README.txt in the samples directory for more information 
about the samples.

------------------------------------------------------------------

* THE DOCUMENTATION OF THE API AND FRAMEWORK

Where's the full documentation of the API and FRAMEWORK at?  You can 
find the documentation of the api and framework in the [doc] directory.
Under Windows that's [doc] and under Linux that's  
[/usr/share/Rebecca/doc]

You can also find more documentation at the RebeccaAIML website: 
http://rebecca-aiml.sourceforge.net/documentation.htm

------------------------------------------------------------------

* COMPILING THE SOURCE CODE OF THE ENGINE

I want to compile the complete source code of the engine and not 
just the samples.  How do I do that?

See [doc\windowsInstall.txt] for Windows and 
[/usr/share/Rebecca/doc/linuxInstall.txt] for Linux.

------------------------------------------------------------------

* DESCRIPTION OF ALL THE DIRECTORIES AND FILES

Can you give me an overview of all the files and directories of 
RebeccaAIML?  Under Windows these files are located at 
[<wherever_you_unzipped>\...] and under Linux these files are 
located at [/usr/share/Rebecca]

If you have the source or binary distribution you
have the following directories of:

[aiml]      Varoius AIML data sets that are included 
            with the RebeccaAIML distribution and used 
			by the samples.

[bin]       Where Rebecca's dll is located at underneath 
            Windows.  Also where the prebuild sample(s) 
			and executables are built into. 

[conf]      Various configuration files that the samples
            use when they load.

[doc]       Where all the documentation is located. 
            Everything from the API documentation to how to 
            install Rebecca from full source code is here.

[include]   All the include files for building against 
            RebeccaAIML.  
            			
[resources] Various resource files needed by every sample 
            is located here.  
			
[src]       Source code of samples and the RebeccaAIML 
            engine if you downloaded the source code.

If you have the source code distribution you have 
a few extra added directories of:

[build_files]           Where the various visual studio 
                        build files and Linux build files 
						are.

[src/rebecca]           Source code of the engine			  

[include/rebecca/impl]  Header files only needed for building
                        the engine.			  

[rebecca.spec]          The RPM spec file in which to build 
                        an RPM of Rebecca for your platform.  
						See  [/usr/share/Rebecca/doc/linuxInstall.txt] 
						for more details on how to utilize this.
			   
------------------------------------------------------------------
			   
ENJOY and don't hesitate to email with questions, problems, or
suggestions on how to improve this project!
			   

