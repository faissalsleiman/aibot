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

#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/utils/StackTrace.h>

#include <xercesc/util/XMLString.hpp>
XERCES_CPP_NAMESPACE_USE

namespace rebecca
{

namespace impl
{

namespace utils
{
/*
Transcode::scopedXMLCh::scopedXMLCh(const XMLCh * const chars)
	: m_char(XMLString::transcode(chars))
{
//	LOG_BOT_METHOD("Transcode::scopedXMLCh::scopedXMLCh(const XMLCh * const chars)");
}
*/

/*
void Transcode::scopedXMLCh::translate(const XMLCh * const chars)
{
//	LOG_BOT_METHOD("void Transcode::scopedXMLCh::translate(const XMLCh * const chars)");
	
	if(m_char)
	{
		XMLString::release(&m_char);
	}

	m_char = XMLString::transcode(chars);
}
*/

/*
Transcode::scopedXMLCh::scopedXMLCh() : m_char(0)
{
//	LOG_BOT_METHOD("Transcode::scopedXMLCh::scopedXMLCh()");
}
*/

/*
Transcode::scopedXMLCh::~scopedXMLCh()
{
//	LOG_BOT_METHOD("Transcode::scopedXMLCh::~scopedXMLCh()");
	XMLString::release(&m_char);
}
*/

/*
bool Transcode::scopedXMLCh::isEmpty() const
{
//	LOG_BOT_METHOD("bool Transcode::scopedXMLCh::isEmpty() const");
	return m_char == 0;
}
*/

/*
const char *Transcode::scopedXMLCh::getChar() const
{
//	LOG_BOT_METHOD("const char *Transcode::scopedXMLCh::getChar() const");
	if(m_char)
	{
		return m_char;
	}
	else
	{
		throw nullString();
	}
}
*/

/*
Transcode::Transcode()
{
//	LOG_BOT_METHOD("Transcode::Transcode()");
}
*/

/*
Transcode::Transcode(const XMLCh * const chars) 
	: m_XMLch(chars)
{
	
//	LOG_BOT_METHOD("Transcode::Transcode(const XMLCh * const chars)");
	if(m_XMLch.isEmpty())
	{
		throw nullString();
	}
}
*/

/*
bool Transcode::isEmpty() const
{
//	LOG_BOT_METHOD("bool Transcode::isEmpty() const");
	return m_XMLch.isEmpty();
}
*/

/*
void Transcode::translate(const XMLCh * const chars)
{
//	LOG_BOT_METHOD("void Transcode::translate(const XMLCh * const chars)");
	m_XMLch.translate(chars);	

	if (m_XMLch.isEmpty())
	{
		throw nullString();
	}		
}
*/

/*
const char *Transcode::getChar() const
{
//	LOG_BOT_METHOD("const char *Transcode::getChar() const");
	return m_XMLch.getChar();
}
*/

/*
const String Transcode::getString() const
{
//	LOG_BOT_METHOD("const String Transcode::getString() const");
	return String(m_XMLch.getChar());
}
*/

/*
Transcode::~Transcode()
{
//	LOG_BOT_METHOD("Transcode::~Transcode()");
}
*/

} //End of namespace utils

} //End of namespace impl

} //End of namespace rebecca
