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
#include <rebecca/AimlFacade.h>
#include <rebecca/impl/Factory.h>
#include <rebecca/GraphBuilder.h>
#include <rebecca/impl/Exceptions.h>

//Boost includes
#include <boost/scoped_ptr.hpp>
using namespace boost;

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

AimlFacade::AimlFacade() throw(Exception &)
{
	try
	{
		scoped_ptr<Factory> factory(Factory::createFactory());
		m_graphBuilder = factory->createGraphBuilder();	
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

GraphBuilder &AimlFacade::getGraphBuilder() throw()
{
	return *(m_graphBuilder);
}


AimlFacade &AimlFacade::operator=(const AimlFacade &aimlFacade)
{ 
	///@todo flush this out in the future and expose it as public

	//Do not use this.  It won't work
	return *this;

}

AimlFacade::AimlFacade(const AimlFacade& aimlFacade) 
{ 
	///@todo flush this out in the future and expose it as public
}

void *AimlFacade::operator new(size_t size)
{
	return ::operator new(size);
}

void AimlFacade::operator delete(void* p) 
{
    ::operator delete(p);
}

AimlFacade::~AimlFacade()
{
	delete m_graphBuilder;
}

} //end of namespace impl
} //end of namespace rebecca
