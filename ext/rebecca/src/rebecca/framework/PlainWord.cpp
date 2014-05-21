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
#include <rebecca/framework/PlainWord.h>
#include <rebecca/impl/utils/Logging.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/tokenizer.hpp>
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

class PlainWordImpl
{
	public:
		PlainWordImpl() { }
		~PlainWordImpl() { } 
		String m_word;
		void trimToOneSpace(const StringPimpl &word);
};

PlainWord::PlainWord() 
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new PlainWordImpl)
{
	LOG_BOT_METHOD("PlainWord::PlainWord()");
	addInstanceOf("PlainWord");
}

PlainWord::PlainWord(const StringPimpl &word)
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new PlainWordImpl)
{
	LOG_BOT_METHOD("PlainWord::PlainWord(const StringPimpl &word)");	 
	addInstanceOf("PlainWord");
	m_pimpl->trimToOneSpace(word);
}


void PlainWordImpl::trimToOneSpace(const StringPimpl &word)
{
	if(word.empty())
	{
		return;
	}

	String copyWord(word.c_str());
	erase_all(copyWord, "\n");

	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	char_separator<char> sep(" ");
	String stringToTok(copyWord);
	tokenize pathTokens(stringToTok, sep);
	logging("String to tokenize" + stringToTok);	
	String returnString;
	
	bool spaceOnLeft  = false;
	bool spaceOnRight = false;

	if(copyWord.size() > 0 && copyWord[0] == ' ')
	{
		logging("The left side has at least one space");
		spaceOnLeft = true;
	}

	if(copyWord.size() > 0 && copyWord[copyWord.size() - 1] == ' ')
	{
		logging("The right side has at least one space");
		spaceOnRight = true;
	}

	CI itLookAhead = pathTokens.begin();
	if(itLookAhead != pathTokens.end())
	{
		++itLookAhead;
	}

	for(CI it = pathTokens.begin(); it != pathTokens.end(); ++it)
	{
		returnString += *it;

		if(itLookAhead != pathTokens.end()) 
		{
			returnString += " ";
			++itLookAhead;
		}
	}	
	
	trim(returnString);

	if(returnString.empty())
	{
		m_word = " ";
		logging("Warning now empty word");
		return;
	}

	if(spaceOnLeft)
	{
		m_word = " ";
	}

	m_word += returnString;

	if(spaceOnRight)
	{
		m_word += " ";
	}

	//Cannot have new line's within <template>.  
	erase_all(m_word, "\n");
	logging("The final m_word is:" + m_word);
}

StringPimpl PlainWord::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl PlainWord::getString()");
	
	if(m_pimpl->m_word.empty())
	{
		logging("WARNING, returning empty string");
	}
	
	return m_pimpl->m_word.c_str();
}

PlainWord::~PlainWord()
{
	LOG_BOT_METHOD("PlainWord::~PlainWord()");
}


} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
