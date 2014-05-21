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
#include <rebecca/framework/Topic.h>
#include <rebecca/framework/Category.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/GraphBuilderInternal.h>
#include <rebecca/impl/NodeMapper.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace boost;
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

class TopicImpl
{
	public:
		TopicImpl(GraphBuilderFramework &builder)
			: m_rootNodeMapper(static_cast<GraphBuilderInternal &>(builder).getRootNodeMapper()),
			m_topic("*") { } 
		NodeMapper &m_rootNodeMapper;
		String m_topic;

		//This is here for performance reasons.
		//Instead of local to the handleInnerTag method
		//Static so only one time is it initialized.
		//This might have to be changed latter when I 
		//go to a multithreading model.
		static QueueString m_wordStack;

		//This is here for performance reasons.
		//Instead of local to the handleInnerTag method
		//Static so only one time is it initialized.
		//This might have to be changed latter when I 
		//go to a multithreading model.
		static char_separator<char> m_sep;

};

//Statics to improve performance.
//This might have to change when going to 
//multithreading	
char_separator<char> TopicImpl::m_sep(" ");
QueueString TopicImpl::m_wordStack;


Topic::Topic(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new TopicImpl(builder))
{
	LOG_BOT_METHOD("Topic::Topic()");
	addInstanceOf("Topic");
}

void Topic::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Topic::handleInnerTag(const shared_ptr<Tag> &tag)");

	if(tag->instanceOf("Category"))
	{
		logging("Creating the word stack");
		typedef tokenizer<char_separator<char> > tokenize;
		typedef tokenizer<char_separator<char> >::const_iterator CI;

		shared_ptr<Category> category = static_pointer_cast<Category>(tag);
		const StringPimpl &patternString = category->getPatternString();

		//Static to improve startup time.
		//This might have to change when going to multithreading
		String patternTokenString(patternString.c_str());
		static tokenize tokens(patternTokenString, m_pimpl->m_sep);

		tokens.assign(patternTokenString);

		CI it;
		for(it = tokens.begin(); it != tokens.end(); ++it)
		{
			logging("Pushing onto word stack: " + *it);
			m_pimpl->m_wordStack.push(*it);
		}

		logging("Pushing onto word stack: <THAT>");
		m_pimpl->m_wordStack.push("<THAT>");
		const StringPimpl &thatString = category->getThatString();
		String thatTokenString(thatString.c_str());
		tokens.assign(thatTokenString);			

		for(it = tokens.begin(); it != tokens.end(); ++it)
		{
			logging("Pushing onto word stack: " + *it);
			m_pimpl->m_wordStack.push(*it);
		}

		logging("Pushing onto word stack: <TOPIC>");
		m_pimpl->m_wordStack.push("<TOPIC>");
		tokens.assign(m_pimpl->m_topic);

		for(it = tokens.begin(); it != tokens.end(); ++it)
		{
			logging("Pushing onto word stack: " + *it);
			m_pimpl->m_wordStack.push(*it);
		}
		
		logging("Done creating word stack");
		logging("Now, creating nodeMapper and using word stack to add node");

		m_pimpl->m_rootNodeMapper.add(category->getTemplate(), m_pimpl->m_wordStack);
	}
	else if(tag->instanceOf("Topic"))
	{
		logging("We have encountered a topic tag.  Ignoring it.");
	}
	else
	{
		logging("Internal programmer error.  Bad cast, this is not a Category or Topic");
		throw InternalProgrammerErrorExceptionImpl(
			"[void Topic::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not a Category or Topic"
				                                  );
	}
}


void Topic::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Topic::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name: " + nameString + "value:" + valueString);

	if(nameString == "name")
	{
		m_pimpl->m_topic = valueString;
	}
	else
	{
		logging("ERROR, did not match an attribute name");
		throw InternalProgrammerErrorExceptionImpl("void Topic::setAttribute(const StringPimpl &name, const StringPimpl &value), did not match an attribute name");
	}	

}


Topic::~Topic()
{
	LOG_BOT_METHOD("void Topic::~Topic()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
