#ifndef REBECCA_IMPL_CONFIGURATIONHANDLERERROR_H
#define REBECCA_IMPL_CONFIGURATIONHANDLERERROR_H

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

//Xerces includes
#include <xercesc/sax/HandlerBase.hpp>

namespace rebecca
{	
namespace impl
{

XERCES_CPP_NAMESPACE_USE

/*
 * Forward declerations
 */ 
class GraphBuilderInternal;


class ConfigurationHandlerError : public HandlerBase
{
	public:
		ConfigurationHandlerError(GraphBuilderInternal &builder)
			: m_builder(builder) { }
		void warning(const SAXParseException &exc);
		void error(const SAXParseException &exc);
		void fatalError(const SAXParseException &exc);
	private:

		GraphBuilderInternal &m_builder;
};




} // end of impl namespace
} // end of rebecca namespace
#endif


