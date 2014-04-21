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
#include <rebecca/StringPimpl.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/Exceptions.h>

//Std includes
#include <exception>
using namespace std;

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

namespace rebecca
{
namespace impl
{

class StringPrivate
{
public:
	String proxy;
};
StringPimpl::StringPimpl() throw(Exception &)
	: m_pimpl(0)
{
	try
	{
		m_pimpl = new StringPrivate;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl::StringPimpl(const char * const stringPimpl) throw(Exception &)
	: m_pimpl(0)
{
	try
	{
		init(stringPimpl);
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void StringPimpl::init(const char * const stringPimpl)
{
	if(stringPimpl == 0)
	{
		logging("Error trying to put 0 into a string");
		throw ExceptionImpl("Error in StringPimpl::init, trying to put 0 into a string");
	}
	else
	{
		delete m_pimpl;
		m_pimpl = new StringPrivate;
		m_pimpl->proxy = stringPimpl;
	}
}


StringPimpl::StringPimpl(const StringPimpl& stringPimpl)
	: m_pimpl(0)
{	
	try
	{
		init(stringPimpl.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

bool StringPimpl::empty() const throw(Exception &) 
{
	try
	{
		return m_pimpl->proxy.empty();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl &StringPimpl::operator=(const StringPimpl &stringPimpl)
{
	if(this !=&stringPimpl)
	{
		init(stringPimpl.c_str());
	}
	return *this;

}

void * StringPimpl::operator new(size_t size)
{
	return ::operator new(size);
}

void StringPimpl::operator delete(void* p) 
{
    ::operator delete(p);
}

const char *StringPimpl::c_str() const throw(Exception &)
{
	try
	{
		return m_pimpl->proxy.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl::~StringPimpl()
{
	delete m_pimpl;
}

} //end of namespace impl
} //end of namespace rebecca

