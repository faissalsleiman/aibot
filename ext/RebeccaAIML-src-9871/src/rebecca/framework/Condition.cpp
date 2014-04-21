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
#include <rebecca/framework/Condition.h>
#include <rebecca/framework/Set.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/framework/Li.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/getStringFromSentence.h>
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

class ConditionImpl
{
	public:
		ConditionImpl(GraphBuilderFramework &builder) 
			: m_builder(builder),
			  m_name(false),
			  m_value(false)
		{ } 

		GraphBuilderFramework &m_builder;
		ListSharedPtrInnerTemplate m_sentence;
		String m_predicateName;
		String m_aimlPattern;
		bool m_value;
		bool m_name;
};


Condition::Condition(GraphBuilderFramework &builder) 
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new ConditionImpl(builder))
{
	LOG_BOT_METHOD("Condition::Condition(GraphBuilderFramework &builder)");
	addInstanceOf("Condition");
}

void Condition::setAttribute(const StringPimpl &name, const StringPimpl &value) 
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Condition::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());

	if(nameString == "name")
	{
		m_pimpl->m_name = true;
		logging("Setting the m_predicateName to:" + nameString);
		m_pimpl->m_predicateName = valueString;
	}
	else if(nameString == "value")
	{
		m_pimpl->m_value = true;
		logging("Setting the m_aimlPattern to:" + valueString);
		m_pimpl->m_aimlPattern = valueString;
	}
	else
	{
		logging("Warning, empty name and/or empty value given or invalid values given");
	}
}

void Condition::addCharacters(const StringPimpl &characters) 
	throw(InternalProgrammerErrorException &)
{
	logging("<Input> characters:" + String(characters.c_str()));
	add(shared_ptr<PlainWord>(new PlainWord(characters)));
}


void Condition::add(const shared_ptr<InnerTemplate> &tag) 
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Condition::add(const shared_ptr<InnerTemplate> &tag)");
	m_pimpl->m_sentence.push_back(tag);
}

StringPimpl Condition::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Condition::getString() const");
	if(this->isBlockCondition())
	{
		logging("This is a block condition");
		if(m_pimpl->m_builder.predicateMatch(m_pimpl->m_predicateName.c_str(), m_pimpl->m_aimlPattern.c_str()))
		{
			logging("Matched the aimlpattern to the predicate's pattern");
			logging("Returning the string");
			return getStringFromSentence(m_pimpl->m_sentence);
		}
		else
		{
			logging("Did not match the aimlpattern, returning empty string");
			return StringPimpl();
		}
	}
	else 
	{
		logging("This is either a single or multi-predicate condition");		
		
		typedef ListSharedPtrInnerTemplate::const_iterator CI;

		for(CI it = m_pimpl->m_sentence.begin(); it != m_pimpl->m_sentence.end(); ++it) 
		{
			if((*it)->instanceOf("Li"))
			{
				shared_ptr<Li> li = static_pointer_cast<Li>(*it);
				StringPimpl liPredicateName = li->getPredicateName();
				StringPimpl liAimlPattern = li->getAimlPattern();

				if(li->isDefaultListItem())
				{
					logging("Encountered default list item.  Returning its string");
					String s = li->getString().c_str();
					trim(s);
					return s.c_str();
				}
				else if(this->isSinglePredicateCondition())
				{
					logging("This is a single Predicate condition");
					if(m_pimpl->m_builder.predicateMatch(m_pimpl->m_predicateName.c_str(), liAimlPattern.c_str()))
					{
						String s = (*it)->getString().c_str();
						trim(s);
						return s.c_str();
					}
				}
				else if(isMutliPredicateCondition())
				{
					logging("This is a multi-predicate condition");
					if(m_pimpl->m_builder.predicateMatch(liPredicateName.c_str(), liAimlPattern.c_str()))
					{
						String s = (*it)->getString().c_str();
						trim(s);
						return s.c_str();
					}
				}
				else
				{
					logging("Inernal programmer Error, the condition block code is corrupted.");
					throw InternalProgrammerErrorExceptionImpl("[StringPimpl Condition::getString()] Condition block code is corrupted.");
					return StringPimpl();
				}
			}
			else if((*it)->instanceOf("PlainWord"))
			{
				//Check for plain word.  If it is a plain word skip to the next
				continue;	
			}
			else
			{
				//Not a plain word, something else.  Throw a bad cast.
				logging("Internal programmer error.  Bad cast, was expecting a Li");
				throw InternalProgrammerErrorExceptionImpl("[StringPimpl Condition::getString() const].  Bad cast, was expecting a Li");
				return StringPimpl();
			}
		}
			
		logging("Nothing matched. Returning empty string");
		return StringPimpl();

	}
}

bool Condition::isBlockCondition() const
	throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_name && m_pimpl->m_value;
}

bool Condition::isSinglePredicateCondition() const
	throw(InternalProgrammerErrorException &)
{
	return ( m_pimpl->m_name && (!m_pimpl->m_value) );
}

bool Condition::isMutliPredicateCondition() const
	throw(InternalProgrammerErrorException &)
{
	return ( (!m_pimpl->m_name) && (!m_pimpl->m_value) );
}

Condition::~Condition()
{
	LOG_BOT_METHOD("Condition::~Condition()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
