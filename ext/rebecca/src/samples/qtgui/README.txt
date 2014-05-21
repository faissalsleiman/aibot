* [qtgui] sample

In this directory is a QT GUI application.  This sample shows you 
how to integrate the Rebecca engine into your QT GUI applications.  
If you are new to QT you can find more out about it at
http://www.trolltech.com/

A few notes about building this sample for Linux and Windows.  You need 
at least QT 4.1.x.  For Linux, install this version of QT normally as per 
their LINUX instructions.  Then build your makefile by calling "qmake" 
in the directory [src\samples\qtgui].  Finally, call "gmake" and it should 
build correctly.

For Windows, you have two options.  You can either buy the commercial 
supported version, or follow these instructions to patch the GPL
version to work with Visual Studio .NET.  

To Patch Qt4/OpenSource using Qt/Win:
Go to the site: http://prdownloads.sourceforge.net/qtwin/ and download
the latest acs4qt.zip file.  They'll have several named 
acs4qt${version}.zip, get the latest dated version.  Unzip that file
into your Qt/OpenSource installation directory. Read the readme inside
of the zip and follow the instructions.

For example, following the instructions I:
* copied the patch into C:\Qt\4.1.0 and unziped it there
* ran installpatch41.bat
* Opened Microsoft Visual C++ .NET development console by running 
      Start|Programs|Microsoft Visual .NET 2003|Visual Studio .NET Tools|Visual Studio .NET 2003 Command Prompt.
* From that console typed: "cd c:\qt\4.1.0"
* Then from that same console typed: "qconfigure msvc.net"
* Finally from that same console typed "nmake" to build it.

Under Windows after getting QT installed, ensure that you change your environment 
variable QMAKESPEC to win32-msvc.net before trying to build this sample.  Lastly, open
a command prompt in the directory [src\samples\qtgui] and run "qmake".  Now, open
the resulting project file with Visual Studio .NET and you should be able to 
build it.