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
#include <rebecca/framework/Formal.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/framework/Star.h>
#include <rebecca/adt/String.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <rebecca/impl/utils/Logging.h>
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

class FormalImpl
{
	public:
		
};

Formal::Formal() throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("Formal::Formal()");
	addInstanceOf("Formal");
}

StringPimpl Formal::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Formal::getString() const");

	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	char_separator<char> sep(" ");
	String stringToTok(InnerTemplateListImpl::getString().c_str());
	tokenize pathTokens(stringToTok, sep);
	logging("String to tokenize" + stringToTok);	
	String returnString;

	for(CI it = pathTokens.begin(); it != pathTokens.end(); ++it)
	{
		logging("Tokenized word" + *it);
		String word(*it);
		word[0] = toupper(word[0]);
		logging("Changed the word to:" + word);

		returnString += word + " ";
	}	

	trim_right(returnString);

	return returnString.c_str();
}

Formal::~Formal()
{
	LOG_BOT_METHOD("Formal::~Formal()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
