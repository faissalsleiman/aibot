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
#include <rebecca/framework/Category.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/Exceptions.h>
using namespace rebecca::impl;

#include <rebecca/framework/Pattern.h>
#include <rebecca/framework/PatternSideThat.h>
#include <rebecca/framework/Template.h>

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

//Boost includes
#include <boost/cast.hpp>
using namespace boost;

namespace rebecca
{
namespace framework
{
namespace impl
{

class CategoryImpl
{
	public:
		CategoryImpl(GraphBuilderFramework &builder)
			: m_builder(builder) { }

		GraphBuilderFramework &m_builder;
		shared_ptr<PatternSideThat> m_that;
		shared_ptr<Template> m_template;
		shared_ptr<Pattern> m_pattern;
	
		//A const string to the default star of "*"
		static const StringPimpl m_defaultStar;
};

const StringPimpl CategoryImpl::m_defaultStar("*");

Category::Category(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new CategoryImpl(builder))
{
	LOG_BOT_METHOD("Category::Category()");
	addInstanceOf("Category");
	m_pimpl->m_builder.getCallBacks().categoryLoaded();

}


void Category::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Category::handleInnerTag(const shared_ptr<Tag> &tag)");
	
	if(tag->instanceOf("PatternSideThat"))
	{
		shared_ptr<PatternSideThat> ic = static_pointer_cast<PatternSideThat>(tag);
		m_pimpl->m_that = ic;
	}
	else if(tag->instanceOf("Template"))
	{
		shared_ptr<Template> ic = static_pointer_cast<Template>(tag);
		m_pimpl->m_template = ic;

	}
	else if(tag->instanceOf("Pattern"))
	{
		shared_ptr<Pattern> ic = static_pointer_cast<Pattern>(tag);
		m_pimpl->m_pattern = ic;
	}
	else 
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerCategory");
		throw InternalProgrammerErrorExceptionImpl("[Category::handleInnerTag] Bad cast, this is not a InnerCategory");
	}
}

const StringPimpl &Category::getPatternString() throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_pattern->getStringConstRef();
}

const StringPimpl Category::getTemplateString() throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_template->getString();
}

const StringPimpl &Category::getThatString() throw(InternalProgrammerErrorException &)
{
	if(m_pimpl->m_that.get() == 0)
	{	
		return m_pimpl->m_defaultStar;
	}
	else
	{
		return m_pimpl->m_that->getStringConstRef();
	}
}

const shared_ptr<Template> &Category::getTemplate() throw(InternalProgrammerErrorException &)
{
	return m_pimpl->m_template;
}

Category::~Category()
{

}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
