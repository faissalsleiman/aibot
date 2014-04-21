/*
 * RebeccaAIML, Artificial Intelligence Markup Language 
 * C++ api and engine.
 *
 * Copyright (C) 2005 Frank Hassanabad
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

//Rebecca includes
#include <rebecca/framework/System.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/framework/Star.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Std includes
#include <cstdio>
#include <cstdlib>
#include <cerrno>
using namespace std;

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
# include <windows.h>
#include <errno.h>
#include <io.h>
#include <fcntl.h> 
#include <ctype.h>
#endif

namespace rebecca
{
namespace framework
{
namespace impl
{

class SystemImpl
{
	public:
		SystemImpl() { }
		~SystemImpl() { } 

};

System::System()
	throw(InternalProgrammerErrorException &)

{
	LOG_BOT_METHOD("System::System()");
	addInstanceOf("System");
}

StringPimpl System::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl System::getString() const");
	
	//@todo when the time comes to break api this needs to 
	//call GraphBuilder.callCommand(command) instead of having
	//this code duplicated.

#ifdef _WIN32

	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	PROCESS_INFORMATION pi;
	HANDLE read_pipe, write_pipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	int fd, create;
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(osv);
	
	GetVersionEx(&osv);

	if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
		SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
		sa.lpSecurityDescriptor = &sd;
	}
	else
	{
		/* Pipe will use ACLs from default descriptor */
		sa.lpSecurityDescriptor = NULL;
	}

	/* Create a new pipe with system's default buffer size */
	if (!CreatePipe(&read_pipe, &write_pipe, &sa, 0))
	{
		//error 
		return StringPimpl();
	}
	

	GetStartupInfo(&si);

	/* Sets the standard output handle for the process to the
	   handle specified in hStdOutput */
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	si.hStdOutput = write_pipe;
	si.hStdError  = (HANDLE) _get_osfhandle (2);
	si.wShowWindow = SW_HIDE;
	string cmd("cmd.exe /c \"");
	cmd += InnerTemplateListImpl::getString().c_str();
	cmd += "\"";
	char *command = strdup(cmd.c_str());
	create = CreateProcess(
		NULL,				// The full path of app to launch
		command, // Command line parameters
		NULL,					// Default process security attributes
		NULL,					// Default thread security attributes
		TRUE,					// Inherit handles from the parent
		0,						// Normal priority
		NULL,					// Use the same environment as the parent
		NULL,					// Use app's directory as current
		&si,					// Startup Information
		&pi);					// Process information stored upon return

	if (!create)
	{
		//error
		return StringPimpl();
	}

	/* Associates a file descriptor with the stdout pipe */
	fd = _open_osfhandle((intptr_t)read_pipe, _O_BINARY);

	/* Close the handle that we're not going to use */
	CloseHandle(write_pipe);

	if (!fd)
	{
		//error
		return StringPimpl();
	}
	
	FILE *file = 0;

	/* Open the pipe stream using its file descriptor */
	file = fdopen(fd, "r");

	if(!file)
	{
		//error
		return StringPimpl();
	}

	if (command)
		free(command);

	int pid = (int)pi.hProcess;
	char c = 0;
	string returnString;
	while (c != EOF)
	{
		c = (char)getc(file);
		
		if(isascii(c))
		{
			returnString += c;
		}
	}

	/* Close the pipe once it's not needed anymore */
	fclose(file);
	return returnString.c_str();

#else

	FILE *file;
	file = popen(InnerTemplateListImpl::getString().c_str(), "r");
	char c = 0;
	string returnString;
	while (c != EOF)
	{
		c = (char)getc(file);

		if(isascii(c))
		{
			returnString += c;
		}
	}

	fclose(file);
	return returnString.c_str();
#endif

}

System::~System()
{
	LOG_BOT_METHOD("System::~System()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
