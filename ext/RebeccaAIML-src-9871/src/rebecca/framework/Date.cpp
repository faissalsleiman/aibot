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
#include <rebecca/framework/Date.h>
#include <rebecca/impl/utils/Logging.h>

//Boost includes
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace boost::posix_time;

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

class DateImpl
{
	public:
};

Date::Date() throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("Date::Date()");
	addInstanceOf("Date");
}

StringPimpl Date::getString() const
	throw(InternalProgrammerErrorException &)
{
	ptime t(second_clock::local_time());
	return to_simple_string(t).c_str();
}

Date::~Date()
{
	LOG_BOT_METHOD("Date::~Date()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
