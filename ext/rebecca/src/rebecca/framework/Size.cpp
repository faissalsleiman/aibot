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
#include <rebecca/framework/Size.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/lexical_cast.hpp>
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

class SizeImpl
{
	public:
		SizeImpl(const GraphBuilderFramework &builder) 
			: m_builder(builder) { }
		~SizeImpl() { } 
		const GraphBuilderFramework &m_builder;
};



Size::Size(const GraphBuilderFramework &builder)
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new SizeImpl(builder))
{
	addInstanceOf("Size");
}

StringPimpl Size::getString() const
	throw(InternalProgrammerErrorException &)
{
	try
	{
		return lexical_cast<String>(m_pimpl->m_builder.getSize()).c_str();
	}
	catch(bad_lexical_cast &)
	{
		logging("Error, Bad lexical cast");
		throw InternalProgrammerErrorExceptionImpl("[StringPimpl Size::getString() const], bad lexical cast");
		return StringPimpl();
	}
}

Size::~Size()
{

}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
