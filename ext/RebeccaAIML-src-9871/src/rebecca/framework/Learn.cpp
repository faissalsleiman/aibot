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
#include <rebecca/framework/Learn.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/adt/String.h>
#include <rebecca/framework/GraphBuilderFramework.h>
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

class LearnImpl
{
	public:
		LearnImpl(GraphBuilderFramework &builder) 
			: m_builder(builder){ }
		GraphBuilderFramework &m_builder;
		
		~LearnImpl() { } 
};

Learn::Learn(GraphBuilderFramework &builder) 
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new LearnImpl(builder))
{
	LOG_BOT_METHOD("Learn::Learn()");
	addInstanceOf("Learn");
}

StringPimpl Learn::getString() const
	throw(InternalProgrammerErrorException &)
{
	try
	{
		LOG_BOT_METHOD("StringPimpl Learn::getString()");
		StringPimpl fileToLoad = InnerTemplateListImpl::getString();
		logging(String("FileToLoad:") + fileToLoad.c_str());
		m_pimpl->m_builder.addFile(fileToLoad.c_str());
	} 
	catch(FileNotFoundException &e)
	{
		//absorb file not found exception, call the callback and keep going
		logging(String("FileNotFoundException caught:") + e.what());
		m_pimpl->m_builder.getCallBacks().learnTagFileNotFound(e.what());
	}
	catch(XMLErrorException &e)
	{
		//absorb the xml error exception and keep going
		logging(String("XMLErrorException caught:") + e.what());
	}
	catch(Exception &e)
	{
		//absorb the general exception and keep going
		logging(String("Exception caught:") + e.what());
	}

	//learn returns an empty string
	return StringPimpl();
}

Learn::~Learn()
{
	LOG_BOT_METHOD("~Think::Think()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
