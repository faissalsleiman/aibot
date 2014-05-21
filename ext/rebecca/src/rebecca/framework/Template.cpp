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
#include <rebecca/framework/Template.h>
#include <rebecca/framework/Category.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/getStringFromSentence.h>
using namespace rebecca::impl;

//Std includes
#include <iostream>
using namespace std;

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

class TemplateImpl
{
	public:
		ListSharedPtrInnerTemplate m_sentence;
};

Template::Template() throw(InternalProgrammerErrorException &)
	: m_pimpl(new TemplateImpl)
{
	addInstanceOf("Template");
}

void Template::add(const shared_ptr<InnerTemplate> &tag) throw(InternalProgrammerErrorException &)
{ 	
	LOG_BOT_METHOD("Template::add(const shared_ptr<InnerTemplate> &tag)");
	
	m_pimpl->m_sentence.push_back(tag);
}

void Template::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Template::addCharacters(const StringPimpl &characters)");
	logging("<Input> characters:" + String(characters.c_str()));

	add(shared_ptr<PlainWord>(new PlainWord(characters)));
}

void Template::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Template::handleInnerTag(const shared_ptr<Tag> &tag)");
	
	if(tag->instanceOf("InnerTemplate"))
	{
		shared_ptr<InnerTemplate> it = static_pointer_cast<InnerTemplate>(tag);
		add(it);
	}
	else
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerTemplate");
		throw InternalProgrammerErrorExceptionImpl(
			"[void InnerTemplate::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not an InnerTemplate"
				                                  );
	}
}

StringPimpl Template::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Template::getString()");
	return getStringFromSentence(m_pimpl->m_sentence);
}

Template::~Template()
{
	LOG_BOT_METHOD("Template::~Template()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
