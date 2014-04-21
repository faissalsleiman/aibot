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
#include <rebecca/framework/TemplateSideThat.h>
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
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

class TemplateSideThatImpl
{
	public:
		TemplateSideThatImpl(GraphBuilderFramework &builder) 
			: m_previousBotResponse(1),
			  m_sentence(1),
			  m_builder(builder) { }

		~TemplateSideThatImpl() { } 

		StringPimpl m_that;
		int m_previousBotResponse;
		int m_sentence;
		GraphBuilderFramework &m_builder;
};


TemplateSideThat::TemplateSideThat(GraphBuilderFramework &builder)
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new TemplateSideThatImpl(builder)) 
{
	LOG_BOT_METHOD("TemplateSideThat::TemplateSideThat(GraphBuilderFramework &builder)");
	addInstanceOf("TemplateSideThat");
}

StringPimpl TemplateSideThat::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl That::getString() const");

	try
	{
		return m_pimpl->m_builder.getPreviousBotResponsePunctuation(m_pimpl->m_previousBotResponse, m_pimpl->m_sentence).c_str();
	}
	catch(IllegalArgumentException &)
	{
		m_pimpl->m_builder.getCallBacks().thatTagSizeExceeded();
		return StringPimpl();
	}
	catch(Exception &e)
	{
		logging(String("Fatal exception occured:") + e.what());
		return StringPimpl();		
	}
}

void TemplateSideThat::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void That::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());
	logging("<Input> name:" + nameString);
	logging("<Input> value:" + valueString);

	if(nameString == "index" && (!valueString.empty()))
	{
		typedef tokenizer<char_separator<char> > tokenize;
		typedef tokenizer<char_separator<char> >::const_iterator CI;
		char_separator<char> sep(",");
		tokenize pathTokens(valueString, sep);
		int i = 0;
		for(CI it = pathTokens.begin(); it != pathTokens.end(); ++it, ++i)
		{
			String s;
			if(i == 0)
			{				
				try
				{
					logging("This is the first index which is a previous bot response");
					s = *it;
					trim(s);
					m_pimpl->m_previousBotResponse = lexical_cast<int>(s);
					logging("Setting the previous bot response to: " + m_pimpl->m_previousBotResponse);					
				}
				catch(bad_lexical_cast &)
				{
					String msg("First index string is not a valid number, ");
					msg += s.c_str();
					m_pimpl->m_builder.getCallBacks().thatTagNumericConversionError(msg.c_str());
					logging("User Error, the cast to a numeric value failed");
				}
			}
			else if(i == 1)
			{
				
				try
				{
					logging("This is the second index which is a sentence");
					s = *it;
					trim(s);
					m_pimpl->m_sentence = lexical_cast<int>(s);
					logging("Setting the sentence to: " + m_pimpl->m_sentence);
				}
				catch(bad_lexical_cast &)
				{
					String msg("Second index string is not a valid number, ");
					msg += s.c_str();
					m_pimpl->m_builder.getCallBacks().thatTagNumericConversionError(msg.c_str());
					logging("User Error, the cast to a numeric value failed");
				}
			}
			else
			{
				m_pimpl->m_builder.getCallBacks().thatTagNumericConversionError("The index is past 2");
				logging("User error, the i index is past 2");
			}
		}	
	}
}

TemplateSideThat::~TemplateSideThat()
{
	LOG_BOT_METHOD("TemplateSideThat::~TemplateSideThat()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
