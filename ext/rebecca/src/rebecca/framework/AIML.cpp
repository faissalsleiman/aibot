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
#include <rebecca/framework/AIML.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/GraphHandler.h>
using namespace rebecca::impl;

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

class AIMLImpl
{
	public:
		AIMLImpl(GraphBuilderFramework &builder)
			: m_defaultStarTopic(builder) { } 

		Topic m_defaultStarTopic;
};

AIML::AIML(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new AIMLImpl(builder))
{
	addInstanceOf("AIML");
	LOG_BOT_METHOD("AIML::AIML(const GraphHandler &parser)");
}

void AIML::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void AIML::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name: " + nameString + "value: " + valueString);

	if(nameString == "version")
	{
	///@todo use something else instead of this or just leave it out.
	//		m_parser.setAIMLVersion(valueString);
	}
	else
	{
		//Ignore all the rest for right now.  I don't care about any other attributes.
	}
}

void AIML::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void AIML::handleInnerTag(const shared_ptr<Tag> &tag)");

	if(tag->instanceOf("Topic"))
	{
		logging("Found instance of topic and am ignoring it");
	}
	else
	{
		m_pimpl->m_defaultStarTopic.handleInnerTag(tag);	
	}
}

AIML::~AIML() 
{ 
	LOG_BOT_METHOD("AIML::~AIML()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
