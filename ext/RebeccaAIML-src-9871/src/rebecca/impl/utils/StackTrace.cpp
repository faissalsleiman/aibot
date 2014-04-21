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

#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/StackTrace.h>

namespace rebecca
{

namespace impl
{

namespace utils
{

#if defined(BOT_USE_STACK_TRACE) || defined(BOT_USE_LOGGING)

OutputDirection *OutputDirection::m_instance = 0;

#endif 

//Only define this if we are going 
//to actually use it
#ifdef BOT_USE_STACK_TRACE

int StackTrace::m_spaces = 0;

StackTrace::StackTrace(const String &methodName) 
	: m_methodName(methodName)
{
	indent();
	OutputDirection *myOutput = OutputDirection::getInstance();
	myOutput->outputTextEndl("[" + m_methodName + " <--> Entering]");
	m_spaces += 4;
}

StackTrace::~StackTrace()
{
	m_spaces -= 4;
	indent();
	OutputDirection *myOutput = OutputDirection::getInstance();
	myOutput->outputTextEndl("[" + 	m_methodName + " <-->  Exiting]");
}

int StackTrace::getSpaces()
{
	return m_spaces;
}

void StackTrace::indent()
{
	int i;
	for(i = 0; i < m_spaces; ++i)
	{
		OutputDirection *myOutput = OutputDirection::getInstance();
		myOutput->outputText(" ");
	}

}

#endif

} //end of namespace utils

} //end of namespace impl

} //end of namespace rebecca


