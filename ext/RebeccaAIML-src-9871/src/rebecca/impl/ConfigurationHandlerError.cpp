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
#include <rebecca/impl/ConfigurationHandlerError.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/GraphBuilderInternal.h>
using namespace rebecca;

//Xerces includes
#include <xercesc/parsers/SAXParser.hpp>
XERCES_CPP_NAMESPACE_USE;

//Boost includes
#include <boost/lexical_cast.hpp>
using namespace boost;

namespace rebecca
{
namespace impl
{

using namespace std;

void ConfigurationHandlerError::fatalError(const SAXParseException& exc)
{
	try
	{
		Transcode sysId(exc.getSystemId());
		Transcode message(exc.getMessage());
		String msg(message.getChar()); 
		msg += ", System Id: " + sysId.getString();
		msg += " at line: " + lexical_cast<String>(exc.getLineNumber());
		msg += " at column: " + lexical_cast<String>(exc.getColumnNumber());
		m_builder.getCallBacks().XMLParseFatalError(msg.c_str());
	}
	catch(bad_lexical_cast &)
	{
		throw InternalProgrammerErrorExceptionImpl("bad lexical cast within SAXParseException");
	}
}

void ConfigurationHandlerError::warning(const SAXParseException &exc)
{
	try
	{
		Transcode sysId(exc.getSystemId());
		Transcode message(exc.getMessage());
		String msg(message.getChar()); 
		msg += ", System Id: " + sysId.getString();
		msg += " at line: " + lexical_cast<String>(exc.getLineNumber());
		msg += " at column: " + lexical_cast<String>(exc.getColumnNumber());
		m_builder.getCallBacks().XMLParseWarning(msg.c_str());
	}
	catch(bad_lexical_cast &)
	{
		throw InternalProgrammerErrorExceptionImpl("bad lexical cast within SAXParseException");
	}
}

void ConfigurationHandlerError::error(const SAXParseException &exc)
{

	try
	{
		Transcode sysId(exc.getSystemId());
		Transcode message(exc.getMessage());
		String msg(message.getChar()); 
		msg += ", System Id: " + sysId.getString();
		msg += " at line: " + lexical_cast<String>(exc.getLineNumber());
		msg += " at column: " + lexical_cast<String>(exc.getColumnNumber());
		m_builder.getCallBacks().XMLParseError(msg.c_str());
	}
	catch(bad_lexical_cast &)
	{
		throw InternalProgrammerErrorExceptionImpl("bad lexical cast within SAXParseException");
	}
}




} // end of impl namespace
} // end of rebecca namespace
