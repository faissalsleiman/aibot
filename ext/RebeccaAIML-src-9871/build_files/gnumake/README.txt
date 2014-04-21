This is how you conduct a build for Linux for RebeccaAIML

Author:  Frank Hassanabad : foreverlinux@yahoo.com

If you run into any problems drop me a line
and I'll fix it.



Edit the file config.mk to setup a small handful
of variables.


Then, run "gmake" to build in release. For debug run 
"gmake debug=true"


If you want to create a distribution of aiml without 
any of the sourcefiles you can run 
"gmake dist" This creates a seperate directory with
just the needed files and runs doxygen for the 
documentation


