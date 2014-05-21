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
#include <rebecca/adt/String.h>
#include <rebecca/adt/List.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/getStringFromSentence.h>
#include <rebecca/framework/InnerTemplate.h>

#include <boost/algorithm/string.hpp>
using namespace boost;

namespace rebecca
{
namespace impl
{

//Not connected to any particular class  Does not need to be.
StringPimpl getStringFromSentence(const ListSharedPtrInnerTemplate &sentence) 
{
	if(sentence.size() == 0)
	{
		logging("WARNING.  No sentence to be had.  Returning empty String");
		StringPimpl s;
		return s;
	}
	else
	{
		logging("Sentece exists.  Constructing sentence");
		String returnSentence;
		typedef ListSharedPtrInnerTemplate::const_iterator CI;

		for(CI it = sentence.begin(); it != sentence.end(); ++it) 
		{
			String sentenceToAppend = (*it)->getString().c_str();
			if(sentenceToAppend.empty())
			{
				logging("Warning, sentence empty, not adding it");
			}
			else
			{
				if((!(returnSentence.empty())) && 
					returnSentence.at(returnSentence.size() - 1) == ' ' && 
				    sentenceToAppend.at(0) == ' ')
				{
					trim_left(sentenceToAppend);
				}
				returnSentence += sentenceToAppend;
			}
			
		} 
		
		return returnSentence.c_str();
	}

}


} //end of namespace impl
} //end of namespace rebecca
