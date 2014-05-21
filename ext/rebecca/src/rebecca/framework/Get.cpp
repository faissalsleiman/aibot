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
#include <rebecca/framework/Get.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/Exceptions.h>
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

class GetImpl
{
	public:
		GetImpl(GraphBuilderFramework &builder) 
			: m_builder(builder) { } 

		GraphBuilderFramework &m_builder;
		String m_predicateName;


};

Get::Get(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new GetImpl(builder))
{
	LOG_BOT_METHOD("Get::Get(GraphBuilderFramwork &builder)");
	addInstanceOf("Get");
}

StringPimpl Get::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Get::getString() const");
	
	return m_pimpl->m_builder.getPredicate(m_pimpl->m_predicateName.c_str()).c_str();
}

Get::~Get()
{
	LOG_BOT_METHOD("Get::~Get()");
}

void Get::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void handleInnerTag(const shared_ptr<Tag> &tag)");
	String nameString(name.c_str());
	String valueString(value.c_str());
	logging("<Input> name:" + nameString);
	logging("<Input> value:" + valueString);

	if(nameString == "name" && (!valueString.empty()))
	{
		m_pimpl->m_predicateName = valueString;		
	}

}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
