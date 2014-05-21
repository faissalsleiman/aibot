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
#include <rebecca/framework/Srai.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

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
namespace framework
{
namespace impl
{

class SraiImpl
{
	public:
		SraiImpl(GraphBuilderFramework &builder) 
			: m_builder(builder) { }
		~SraiImpl() { } 
		GraphBuilderFramework &m_builder;
};

Srai::Srai(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new SraiImpl(builder))
{
	LOG_BOT_METHOD("Srai::Srai()");
	addInstanceOf("Srai");
}	

StringPimpl Srai::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Srai::getString()");

	try
	{
		StringPimpl sentence = InnerTemplateListImpl::getString();	
		StringPimpl returnString;

		if(sentence.empty())
		{
			logging("Warning returning empty string");
		}
		else
		{
			m_pimpl->m_builder.getCallBacks().symbolicReduction(sentence.c_str());
			returnString = m_pimpl->m_builder.checkedInfiniteLoopGetResponse(sentence, false);
		}

		return returnString;
	}
	catch(RecursionException &e)
	{
		logging(String("Infinite Symbolic Recursion detected: ") + e.what());
		m_pimpl->m_builder.getCallBacks().infiniteSymbolicReduction();
		return StringPimpl();
	}
	catch(Exception &e)
	{
		logging(String("Fatal exception occured:") + e.what());
		return StringPimpl();
	}
}
Srai::~Srai()
{
	LOG_BOT_METHOD("Srai::~Srai()");
}


} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
