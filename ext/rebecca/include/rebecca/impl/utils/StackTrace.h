#ifndef REBECCA_IMPL_UTILS_STACKTRACE_H
#define REBECCA_IMPL_UTILS_STACKTRACE_H

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

//Stl includes
#include <iostream> 
#include <fstream>

//Rebecca includes
#include <rebecca/adt/String.h>

namespace rebecca
{

namespace impl
{

namespace utils
{

using adt::String;
using std::cout;
using std::endl;
using std::ofstream;

#if defined(BOT_USE_STACK_TRACE) || defined(BOT_USE_LOGGING)

class OutputDirection
{
	public:
		void outputText(const String &text)
		{
			m_outputFile << text;
		}

		void outputTextEndl(const String &text)
		{
			m_outputFile << text << endl;
		}


		static OutputDirection *getInstance()
		{
			if(m_instance == 0)
			{
				m_instance = new OutputDirection;
			}
			return m_instance;
		}

	protected:
		OutputDirection() 
			: m_outputFile("logging.txt")
		{
		}
	public:
		ofstream m_outputFile;
		static OutputDirection *m_instance;

};

#endif //end of BOT_USE_STACK_TRACE ifdef


#ifdef BOT_USE_STACK_TRACE

class StackTrace
{
	public:	
		StackTrace(const String &methodName);
		static void indent();
		~StackTrace();
		static int getSpaces();
	private:
		String m_methodName;
		static int m_spaces;

};


#define LOG_BOT_METHOD(a) StackTrace bot_impl_utils_stacktrace_private_tracing(a);


#else //BOT_USE_LOGGING

//We do not want logging
#define LOG_BOT_METHOD(a)


#endif //end of BOT_USE_LOGGING

} //end of utils namespace

} //end of impl namespace

#ifdef BOT_USE_STACK_TRACE
using rebecca::impl::utils::StackTrace;
#endif

} //end of bot namespace


#endif