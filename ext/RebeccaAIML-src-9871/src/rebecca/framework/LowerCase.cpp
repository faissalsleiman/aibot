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
#include <rebecca/framework/LowerCase.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/framework/Star.h>
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

class LowerCaseImpl
{
	public:
		LowerCaseImpl() { }
		~LowerCaseImpl() { } 

};

LowerCase::LowerCase()
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("LowerCase::LowerCase()");
	addInstanceOf("LowerCase");
}

StringPimpl LowerCase::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl LowerCase::getString() const");
	String s(InnerTemplateListImpl::getString().c_str());
	return to_lower_copy(s).c_str();
}

LowerCase::~LowerCase()
{
	LOG_BOT_METHOD("LowerCase::~LowerCase()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
