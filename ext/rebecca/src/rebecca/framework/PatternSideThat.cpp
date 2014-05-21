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
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;
#include <rebecca/framework/PatternSideThat.h>

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

class PatternSideThatImpl
{
	public:
		PatternSideThatImpl(GraphBuilderFramework &builder) 
			{ }

		~PatternSideThatImpl() { } 
		StringPimpl m_that;
};


PatternSideThat::PatternSideThat(GraphBuilderFramework &builder) throw(InternalProgrammerErrorException &)
	: m_pimpl(new PatternSideThatImpl(builder)) 
{
	LOG_BOT_METHOD("PatternSideThat::PatternSideThat(GraphBuilderFramework &builder)");
	addInstanceOf("PatternSideThat");
}

void PatternSideThat::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void That::addCharacters(const StringPimpl &characters)");
	logging("<Input> characters:" + String(characters.c_str()));
	m_pimpl->m_that = characters.c_str();
}

StringPimpl PatternSideThat::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl That::getString() const");
	return m_pimpl->m_that;
}
const StringPimpl &PatternSideThat::getStringConstRef() const
	throw(InternalProgrammerErrorException &)
{
	logging("It is a patternSideThat");
	return m_pimpl->m_that;
}

PatternSideThat::~PatternSideThat()
{
	LOG_BOT_METHOD("PatternSideThat::~PatternSideThat()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
