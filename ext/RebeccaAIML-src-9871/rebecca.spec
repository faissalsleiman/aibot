#Query the RPM database to find which release we are running.
################################################################

#Try to keep all platform-specific definitions up here instead of putting
#them in the body of the spec file.

%if %(rpmquery fedora-release | grep -cv 'not installed$')
    #Fedora Core - http://fedora.redhat.com
    %define VER %(rpmquery --qf '%{VERSION}' fedora-release)
    %define DISTTAG fc
    %if %{VER} >= 3
      %define RBROWSER firefox
    %endif
    %if %{VER} >= 4
      %define GCC4 1
      %define RPDFVIEWER evince
    %endif
    %if %{VER} >= 5
      %define XORG 1
    %endif
%endif

%if %(rpmquery redhat-release | grep -v 'not installed$' | grep -c -e '-[0-9][AEW]S')
    #Red Hat Enterprise Linux - http://www.redhat.com
    %define VER %(rpmquery --qf '%{VERSION}' redhat-release)	
    %define DISTTAG rh
%endif

%if %(rpmquery centos-release | grep -v 'not installed$' | grep -c -e '-[0-9]-[0-9].[0-9]')
    #CENTOS Linux - http://www.centos.org/ and ROCKS-Linux Cluster Installation
    %define VER %(rpmquery --qf '%{VERSION}' centos-release)	
    %define DISTTAG centos.
%endif

%if %(rpmquery sl-release | grep -cv 'not installed$')
    #Scientific Linux. A RHEL work-alike -  http://www.scientificlinux.org
    # note nasty use of \\. here grr!
    %define VER %(rpmquery --qf '%{VERSION}' sl-release | sed 's/\\.//g')
    %define DISTTAG SL
%endif

Summary: Windows/Linux Object Oriented C++ chatter bot api/interpreter for AIML 
Name: RebeccaAIML
Version: 9871
License: LGPL
Release: 1.%{DISTTAG}%{VER}
Group: Development/Libraries
Source: http://prdownloads.sourceforge.net/rebecca-aiml/RebeccaAIML-src-9871.tar.gz
BuildRoot: %{_tmppath}/%{name}-root
Prefix: /usr

%description
RebeccaAIML is an object-oriented C++ chatter bot API 
and interpreter for AIML (Artificial Intelligence Markup Language) 
the ALICE project. It includes comprehensive documentation and samples.

%prep
%setup -q -n rebecca

%build
cd build_files/autoconf 
./configure --prefix=%{_tmppath}/%{name}-root%{prefix} --with-build_prefix=%{prefix} --with-build_exec_prefix=%{prefix}
make 

%install
cd build_files/autoconf
make install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
/usr/lib
/usr/include
/usr/bin
/usr/share/Rebecca/aiml
/usr/share/Rebecca/bin
/usr/share/Rebecca/conf
/usr/share/Rebecca/resources
/usr/share/Rebecca/src
%doc /usr/share/Rebecca/doc

%changelog

* Thu Sep 07 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- I now include the executable, regression, in both the Windows and Linux prebuilt packages.  This is for downloaders to be able to verify the quality of Rebecca for the version they download.
- I also added the regression test suite to the autoconf build system where it builds it by default.
- Updated the code for the regression testing. It now uses header and footer html files in resources/testing instead of having the html hard coded.
- Fixed regression to output <br/> instead of the incorrect <br> for html page breaks.
- I also improved regression to be dll boundary safe by having it use Tag::instanceOf() instead of dynamically casting through
dynamic_cast<>().
- I also added an Arguments class to regression to enable a smooth transition over to autoconf

* Fri Sep 01 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- Condition and Li were not handling empty string cases correctly.  See the latest regression tests in the documentation for the exact case.
- Li::getPredicateName() and Li::getAimlPattern() are now const methods.  This change will break abi compatiblity with anyone using the framework but not api compatibility with the framework.  Those using the framework will have to recompile and relink against this new version.
- Added the method bool Li::isDefaultListItem(). It returns true if the Li is a default list item or not.
- Added the method bool Li::isValueOnlyListItem().  It returns true if the Li is a value only list item.
- Added the method bool Li::isNameAndValueListItem().  It returns true if the Li is a name and value list.
- Added the method bool Condition::isBlockCondition().  It returns true if this Condition is a block condition otherwise it will return false.
- Added the method bool Condition::isSinglePredicateCondition().  It returns true if this Condition is a single predicate condition otherwise it will return false.
- Added the method bool Condition::isMutliPredicateCondition().  It returns true if this Condition is a multi-predicate condition otherwise it will return false.
- Updated documentation for GraphBuilder::callSystemCommand()
- Removed the bug documentation aboug xsd not being validated.  I really should have removed this a long time ago, but it's removed now.


* Sun Aug 06 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- Whenever topic was being set it was not calling srai's correctly. This was due to a bad logging call.


* Tue Jul 25 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION .986
- Fixed bug with PlainWordImpl::trimToOneSpace where I was not checking if the size of a string was greater than zero before using it.
- Fixed a bug with srai where the star indexes were not being calculated right during srai.
- Fixed a bug where rebecca would not let go of her internal AIML file and string caching system.
- Upgraded the qtgui and tested it underneath QT 4.1.4 
- Added the Callback method Callbacks::learnTagFileNotFound() for when the AIML XML learn tag cannot find a file it will call this callback.  This will allow the programmer to handle file not founds for AIML XML programmatically.
- Added a new method GraphBuilder::callSystemCommand() which acts the same as calling the AIML XML tag "System" by sending the command to the operating system and returning the output of the command.


* Sun May 07 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION .985
- Added autoconf support for Unix'es and Linux.
- Added an Arguments class to each sample.
- Added RPM support 
- Added RPM's for Fedora Core 3, 4, and 5 on the website
- Tweaked the sourcefiles to work with gcc 4.1.0

* Mon Apr 04 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.984 
- Added method GraphBuilder.addString() to add AIML strings programatically. 
- Added the learn tag per AIML 1.0.1 specification.
- Fixed the gender, person, and person2 tag implementations to pass all of the regression tests.
- Fixed the addFile and addDirectory to be tolerant of adding files which are native to the file system.
- Under the covers updated and changed the Transcode to translate both from xerces xml strings and to xerces xml strings.

* Tue Apr 04 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.983
- Fixed a bug where when srai is called the input AIML tags behaved incorrectly.
- I had to alter the signature of GraphBuilderFramework.checkedInfiniteLoopGetResponse()
- Fixed a bug where when punctuation is at the begining of a Rebecca Response it would cause her to crash.
- Fixed a one-off error where I incorrectly indexed some of the internal data structures and this would cause a crash.
- Made the stack operational by adding a missing predicate
- Put in more bot properties (the most common ones)

* Sun Mar 19 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.982 
- Fixed GraphBuilder::addCustomTagLibrary method.
- addCustomTagLibrary would load the string given as soname.so when it should have loaded it as libsoname.so.
- Fixed a bug where Rebecca was not erasing commas before storing strings into her internal "that" variable.
- Added a regression test case for the comma bug
- Fixed the "System" AIML tag to be able to return the string now under both Windows and Linux.
- The regression test for the "System" tag works now

* Sat Mar 03 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.981 
- Added a new cross platform simple QT GUI to the samples section to showcase how you would program a GUI with the RebeccaAIML engine.
- Fixed a bug where when you call new and delete on AIMLFacade or StringPimpl it would crash under Windows if you were mixing and matching Debug and Release.
- Fixed that in this version, it will say .981 when the <version> tag is encountered.

* Tue Feb 14 2006 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.98
- I opened up the RebeccaAIML framework in which you can inherit from AIML XML Tag classes to add or modify the current working set.
- The framework is fully documented
- I provide a sample which overrides all the AIML XML Tags to provide a Html converter.

* Sun Nov 27 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.972
- Fixed a bug where the Copy constructor of StringPimpl was crashing the engine.
- I also changed the default precompiled windows binary to be multithreaded dll instead of just multithreaded.

* Sun Nov 20 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERISION 0.971 
- Enabled true multi-lined that's.
- Now Rebecca can pass another regression test involving multi-lined that's.
- Also now the that index's involving previous input's and previous sentences works correctly.

* Sun Nov 6 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.97
- A new regression testing system has been put into place.
- This release fixes yet another bug with the condition

* Thu Oct 20 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.96
- Fixes a bug in which the AIML tag "Condition" did not work at all.
- Also this release fixes the AIML.xsd

* Tue Oct 18 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.951
- Fixed the "muliti-lined that" bug.

* Wed Oct 12 2005 Frank Hassanabad <foreverlinux@yahoo.com>
- VERSION 0.95
- Initial release.  
- All AIML tags are implemented except for <learn> and the java script.
- There is currently a bug with the AIML.xsd that does not allow the AIML tag <set> to validate correctly. 


