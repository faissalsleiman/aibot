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
#include <rebecca/framework/Set.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/algorithm/string.hpp>
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

class SetImpl
{
	public:
		SetImpl(GraphBuilderFramework &builder) 
			: m_builder(builder) { }
		~SetImpl() { } 
		GraphBuilderFramework &m_builder;
		String m_predicateName;
};

Set::Set(GraphBuilderFramework &builder)
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new SetImpl(builder)) 
{ 
	LOG_BOT_METHOD("Set::Set(GraphBuilderFramework &builder)");
	addInstanceOf("Set");
}


StringPimpl Set::getString() const
	throw(InternalProgrammerErrorException &)
{
	String sentence = InnerTemplateListImpl::getString().c_str();

	trim(sentence);

	if(sentence.empty() && to_upper_copy(trim_copy(m_pimpl->m_predicateName)) != "TOPIC")
	{		
		logging("Warning returning empty string");
	}
	else
	{
		logging("Setting predicate: " + m_pimpl->m_predicateName + "to value: " + sentence);
		m_pimpl->m_builder.setPredicate(m_pimpl->m_predicateName.c_str(), sentence.c_str());
	}
	return sentence.c_str();
}

void Set::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Set::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name:" + nameString);
	logging("<Input> value:" + valueString);
	
	if(nameString == "name" && (!valueString.empty()))
	{
		m_pimpl->m_predicateName = valueString;
	}
}
Set::~Set()
{
	LOG_BOT_METHOD("Set::~Set()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
