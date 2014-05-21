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
#include <rebecca/framework/InnerCategory.h>
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

class InnerCategoryImpl
{

};

InnerCategory::InnerCategory() throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("InnerCategory::InnerCategory()");
	addInstanceOf("InnerCategory");
}

const StringPimpl &InnerCategory::getStringConstRef() const 
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("const StringPimpl &InnerCategory::getStringConstRef() const");
	StringPimpl *s = new StringPimpl;
	return *s; 
}

InnerCategory::~InnerCategory()
{

}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
