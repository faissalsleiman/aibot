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
#include <rebecca/framework/InnerTemplate.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/getStringFromSentence.h>
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

class InnerTemplateImpl
{
	public:

};

InnerTemplate::InnerTemplate() throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("InnerTemplate::InnerTemplate()");
	addInstanceOf("InnerTemplate");
}

void InnerTemplate::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void InnerTemplate::handleInnerTag(const shared_ptr<Tag> &tag)");

	if(tag->instanceOf("InnerTemplate"))
	{
		shared_ptr<InnerTemplate> it = static_pointer_cast<InnerTemplate>(tag);
		add(it);
	}
	else
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerCategory");
		throw InternalProgrammerErrorExceptionImpl(
			"[void InnerTemplate::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not an InnerTemplate"
				                                  );
	}
}

StringPimpl InnerTemplate::getString() const 
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl InnerTemplate::getString()");
	logging("No operations happen within this.  Empty string being returned");
	return StringPimpl();
}

void InnerTemplate::add(const shared_ptr<InnerTemplate> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("virtual void InnerTemplate::add(const shared_ptr<InnerTemplate> &tag)");
	logging("No operations happen within this");
}

InnerTemplate::~InnerTemplate() 
{ 
	LOG_BOT_METHOD("virtual InnerTemplate::~InnerTemplate()");
}



} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
