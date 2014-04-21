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
#include <rebecca/framework/Bot.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
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

class BotImpl 
{
	public:
		BotImpl(GraphBuilderFramework &builder)
			: m_builder(builder) { }

	GraphBuilderFramework &m_builder;
	String m_botPredicateName;
	
};


Bot::Bot(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new BotImpl(builder))
{

	LOG_BOT_METHOD("Bot::Bot(GraphBuilderFramework &builder)");
	addInstanceOf("Bot");
}

StringPimpl Bot::getString() const 
	throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_builder.getBotPredicate(m_pimpl->m_botPredicateName.c_str()).c_str();
}

void Bot::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Bot::setAttribute(const StringPimpl &name, const StringPimpl &value)");	
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name:" + nameString);
	logging("<Input> value:" + valueString);
	
	if(nameString == "name" && (!valueString.empty()))
	{
		m_pimpl->m_botPredicateName = valueString;
	}
}

Bot::~Bot()
{
	LOG_BOT_METHOD("Bot::~Bot()");
}


} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
