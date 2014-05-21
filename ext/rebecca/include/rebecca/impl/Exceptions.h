#ifndef REBECCA_IMPL_EXCEPTIONS_H
#define REBECCA_IMPL_EXCEPTIONS_H

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
#include <rebecca/Exceptions.h>
#include <rebecca/adt/String.h>

#include <boost/shared_ptr.hpp>
using namespace boost;

//Disable Windows VC 7.x warning about 
//dllinterface with's
#ifdef _WIN32
#    pragma warning( disable : 251)
#endif

namespace rebecca 
{
namespace impl 
{

class ExceptionImpl : public Exception
{
	public: 
		
		ExceptionImpl(const char * const msg = "Unknown exception")
			: m_msg(msg)
		{ }

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}	

	private:
		String m_msg;		
};

class IllegalArgumentExceptionImpl : public IllegalArgumentException
{ 
	public:
		
		IllegalArgumentExceptionImpl() 
			: m_exception(new ExceptionImpl) { }

		IllegalArgumentExceptionImpl(const char  * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class FileNotFoundExceptionImpl : public FileNotFoundException
{ 
	public:
		
		FileNotFoundExceptionImpl() 
			: m_exception(new ExceptionImpl) { }
		
		FileNotFoundExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;

};

class DirectoryNotFoundExceptionImpl : public DirectoryNotFoundException
{ 
	public:
		DirectoryNotFoundExceptionImpl()
			: m_exception(new ExceptionImpl) { }

		DirectoryNotFoundExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class InitializationExceptionImpl : public InitializationException
{
	public:
		InitializationExceptionImpl()
			: m_exception(new ExceptionImpl) { } 

		InitializationExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class XMLErrorExceptionImpl : public XMLErrorException
{
	public:
		XMLErrorExceptionImpl() 
			: m_exception(new ExceptionImpl){ }

		XMLErrorExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class REBECCA_EXPORT RecursionExceptionImpl : public RecursionException
{
	public:
		RecursionExceptionImpl() 
			: m_exception(new ExceptionImpl) { } 
		
		RecursionExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class InternalProgrammerErrorExceptionImpl : public InternalProgrammerErrorException
{
	public:
		InternalProgrammerErrorExceptionImpl() 
			: m_exception(new ExceptionImpl) { } 
		
		InternalProgrammerErrorExceptionImpl(const char * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

} //end of namespace impl
} //end of namespace rebecca

#endif 

