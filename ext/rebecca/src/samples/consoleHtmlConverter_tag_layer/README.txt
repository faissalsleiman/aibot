* [consoleHtmlConverter_tag_layer] sample

In this directory is a complete program that converts AIML XML files
into html pages with links.  The html pages provide a way to "cruise" 
through the AIML brain and see how the brain would look like in memory.

This example is to show how to override the AIML tags and provide your
own functionality.  You can use this complete example to see how to 
add your own custom tag layers.  A tag layer is a layer in which you
can either extend from the normal AIML XML set and add your own 
specialized AIML XML tags or you can override the current existing
AIML XML tags and add your own custom behvaior for the tags.

How to compile this under Windows:

For this sample to compile, you have to install the C++ boost library and
define a few variables.  You can get the most current boost library from
http://www.boost.org/.  The variables you have to define are:

BOOST_INCLUDE -- Point this to the location of your boost header files.
BOOST_LIB     -- Point this to the location of your boost release library.
BOOST_LIBD    -- Point this to the location of your boost debug library.

For example, on a fresh install on the Windows platform I have them set
to:

BOOST_INCLUDE : C:\Boost\include\boost_1_32
BOOST_LIB     : C:\Boost\lib
BOOST_LIBD    : C:\Boost\lib

Notice how I have BOOST_LIB and BOOST_LIBD pointing to the same directory.
That's because by default Boost installs its debug and release library into
the same directory.

How to compile this under Linux:

Simply ensure you have installed the boost libary and that the headers and 
libs are available.  For example, I have /usr/include/boost with the headers
and I have /usr/lib/<boost_libs> boost library files.