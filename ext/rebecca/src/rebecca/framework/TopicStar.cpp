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
#include <rebecca/framework/TopicStar.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/lexical_cast.hpp>
using namespace boost;

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

class TopicStarImpl
{
	public:
		TopicStarImpl(GraphBuilderFramework &builder) 
			: m_builder(builder), 
			  m_index(1) { }

		GraphBuilderFramework &m_builder;
		int m_index;
		~TopicStarImpl() { } 


};

TopicStar::TopicStar(GraphBuilderFramework &builder)
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new TopicStarImpl(builder))
{
	LOG_BOT_METHOD("TopicStar::TopicStar(GraphBuilderFramework &builder)");
	addInstanceOf("TopicStar");
}

void TopicStar::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void TopicStar::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name:" + nameString);
	logging("<Input> value:" + valueString);

	try
	{
		if(nameString == "index" && (!valueString.empty()))
		{
			m_pimpl->m_index = lexical_cast<int>(valueString);				
		}
	}
	catch(bad_lexical_cast &)
	{
		String msg("Index string is not numeric");
		msg += valueString;
		m_pimpl->m_builder.getCallBacks().topicStarTagNumericConversionError(msg.c_str());
		logging("Error, the cast to a numeric value failed");
	}
}

StringPimpl TopicStar::getString() const
	throw(InternalProgrammerErrorException &)
{
	try
	{
		return m_pimpl->m_builder.getTopicStar(m_pimpl->m_index);
	}
	catch(IllegalArgumentException &e)
	{
		logging(String("Size Exceeded: ") + e.what());
		m_pimpl->m_builder.getCallBacks().topicStarTagSizeExceeded();
		return StringPimpl();
	}
	catch(Exception &e)
	{
		logging(String("Another exception occured, returning empty string:") + e.what());
		return StringPimpl();
	}
}

TopicStar::~TopicStar()
{

}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
