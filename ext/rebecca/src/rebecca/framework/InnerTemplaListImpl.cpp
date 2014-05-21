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

//rebecca includes
#include <rebecca/framework/InnerTemplateListImpl.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/getStringFromSentence.h>
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

class InnerTemplateListImplImpl
{
	public:
		ListSharedPtrInnerTemplate m_sentence;
};

InnerTemplateListImpl::InnerTemplateListImpl() throw(InternalProgrammerErrorException &)
	: m_pimpl(new InnerTemplateListImplImpl)
{
	LOG_BOT_METHOD("InnerTemplateListImpl::InnerTemplateListImpl()");
	addInstanceOf("InnerTemplateListImpl");
}
void InnerTemplateListImpl::add(const shared_ptr<InnerTemplate> &tag) throw(InternalProgrammerErrorException &)
{
	m_pimpl->m_sentence.push_back(tag);
}

StringPimpl InnerTemplateListImpl::getString() const
	throw(InternalProgrammerErrorException &)
{
	return getStringFromSentence(m_pimpl->m_sentence);
}

void InnerTemplateListImpl::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	logging("<Input> characters:" + String(characters.c_str()));
	add(shared_ptr<PlainWord>(new PlainWord(characters)));
}

InnerTemplateListImpl::~InnerTemplateListImpl()
{

}


} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
