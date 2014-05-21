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
#include <rebecca/framework/Tag.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/adt/String.h>

//Std includes
#include <map>
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

using namespace rebecca::impl;

class TagImpl
{
	public:
		///@todo put this into the adt
		map<String, bool> m_instances;
};


Tag::Tag() throw(InternalProgrammerErrorException &)
	: m_pimpl(new TagImpl)
{
	LOG_BOT_METHOD("Tag::Tag()");
	addInstanceOf("Tag");
}

void Tag::addInstanceOf(const char * const instance) throw(InternalProgrammerErrorException &)
{
	m_pimpl->m_instances.insert(pair<String, bool>(instance, true));
}



void Tag::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("virtual void Tag::addCharacters(const StringPimpl &characters)");
}

void Tag::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("virtual void Tag::handleInnerTag(const shared_ptr<Tag> &tag");
}

void Tag::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("virtual void Tag::setAttribute(const StringPimpl &name, const StringPimpl &value)");
}

bool Tag::instanceOf(const char * const instance) throw(InternalProgrammerErrorException &)
{
	typedef map<String, bool>::const_iterator CI;
	CI it = m_pimpl->m_instances.find(instance);
	if(it != m_pimpl->m_instances.end())
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


Tag::~Tag() { }

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
