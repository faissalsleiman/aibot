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
#include <rebecca/framework/Li.h>
#include <rebecca/framework/PlainWord.h>
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

class LiImpl
{
	public:

		LiImpl()
			: m_name(false),
			  m_value(false)
		{ }

		StringPimpl m_predicateName;
		StringPimpl m_aimlPattern;
		bool m_name;
		bool m_value;
};

Li::Li() throw(InternalProgrammerErrorException &)
	: m_pimpl(new LiImpl)
{
	LOG_BOT_METHOD("Li::Li()");
	addInstanceOf("Li");
}

StringPimpl Li::getPredicateName() const
	throw(InternalProgrammerErrorException &)
{ 
	return m_pimpl->m_predicateName; 
}

StringPimpl Li::getAimlPattern() const
	throw(InternalProgrammerErrorException &)
{ 
	return m_pimpl->m_aimlPattern; 
}

bool Li::isDefaultListItem() const
	throw(InternalProgrammerErrorException &)
{
	return ((!m_pimpl->m_name) && (!m_pimpl->m_value));
}

bool Li::isValueOnlyListItem() const
	throw(InternalProgrammerErrorException &)
{
	return (m_pimpl->m_value && !m_pimpl->m_name);
}

bool Li::isNameAndValueListItem() const
	throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_value && m_pimpl->m_name;
}

void Li::setAttribute(const StringPimpl &name, const StringPimpl &value) 
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Li::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	
	String nameString(name.c_str());
	String valueString(value.c_str());

	if(nameString == "name" && !valueString.empty())
	{
		//It has a name attribute so mark that true
		m_pimpl->m_name = true;
		logging("Setting the m_predicateName to:" + nameString);
		m_pimpl->m_predicateName = value;
	}
	else if(nameString == "value")
	{
		//It has a value attribute so mark that true
		m_pimpl->m_value = true;
		logging("Setting the m_aimlPattern to:" + valueString);
		m_pimpl->m_aimlPattern = value;
	}
	else
	{
		logging("Warning, empty name and/or empty value given or invalid values given");
	}
}

Li::~Li()
{
	LOG_BOT_METHOD("Li::~Li()");
}



} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
