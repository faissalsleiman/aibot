#ifndef REBECCA_IMPL_GRAPHBUILDERINTERNALNOOPS_H
#define REBECCA_IMPL_GRAPHBUILDERINTERNALNOOPS_H

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

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4290 )
#endif

#include <rebecca/impl/GraphBuilderInternal.h>
#include <rebecca/impl/NodeMapper.h>

namespace rebecca
{

namespace framework
{
namespace impl
{
//Forward decleration
class CustomTags;
}
using rebecca::framework::impl::CustomTags;
}

namespace impl
{

using namespace rebecca::framework;

class GraphBuilderInternalNoOps : public GraphBuilderInternal
{
	public:

		inline virtual void createGraph() throw(XMLErrorException &, Exception &) { } 
		inline virtual void clearStars() { } 
		inline virtual void addStar(const StringPimpl &star) { } 
		inline virtual void setUseThatStar() { } 
		inline virtual void setUseTopicStar() { } 
		inline virtual void setUseDefaultStar() { } 

		inline virtual StringPimpl getStar(const unsigned int &index) const 
			throw(IllegalArgumentException &, Exception &) 
			{ return StringPimpl(""); }

		inline virtual StringPimpl getThatStar(const unsigned int &index) const
			throw(IllegalArgumentException &, Exception &)
			{ return StringPimpl(""); } 

		inline virtual StringPimpl getTopicStar(const unsigned int &index) const 
			throw(IllegalArgumentException &, Exception &)
			{ return StringPimpl(""); } 
	
		inline virtual StringPimpl inputSubstitute(const StringPimpl &input) { return StringPimpl(""); } 
		
		inline virtual StringPimpl genderSubstitute(const StringPimpl &input) const 
			throw(Exception &) 
			{ return StringPimpl(""); }

		inline virtual StringPimpl personSubstitute(const StringPimpl &input) const 
			throw(Exception &) 
			{ return StringPimpl(""); } 

		inline virtual StringPimpl person2Substitute(const StringPimpl &input) const 
			throw(Exception &) 
			{ return StringPimpl(""); } 

		inline virtual StringPimpl checkedInfiniteLoopGetResponse(const StringPimpl &userInput, bool keepPreviousUserInput = true) 
			throw(RecursionException &, Exception &) 			
			{ return false; }

		inline virtual map<String, CustomTagWithDelete> &getCustomTagsMapRef()
		{
			map<String, CustomTagWithDelete> someMap;
			return someMap;
		}

		virtual void addString(const char * const stringContainingAIML)
			throw(Exception &) { }

		virtual void setAddStringAIMLHeader(const char * const aimlHeader)
			throw(Exception &) { } 

		virtual void setAddStringAIMLFooter(const char * const aimlFooter)
			throw(Exception &) { } 

		inline virtual CallBacks &getCallBacks() throw(Exception &)
		{	
			//calling this no operations is going to result in leaked memory.
			CallBacks *b = new CallBacks;
			return *b;
		}
		inline virtual void setSize(const unsigned int newSize) { } 


		inline virtual void addFile(const char * const file) 
			throw(FileNotFoundException &, Exception &){ }

		inline virtual void addDirectory(const char * const directory, const char * const regularExpression = ".*\\.aiml") 
			throw(IllegalArgumentException &, DirectoryNotFoundException &, Exception &) { } 

		inline virtual void setAIMLSchema(const char * const schema) 
			throw(Exception &) { }

		inline virtual void setCommonTypesSchema(const char * const schema) 
			throw(Exception &) { }

		inline virtual void setAIMLValidation(bool trueOrFalse = true) 
			throw(Exception &) { } 

		inline virtual StringPimpl getResponse(const char * const input) 
			throw(Exception &) { return StringPimpl(""); }

		inline virtual void setThat(const char * const that) 
			throw(Exception &) { } 

		inline virtual void setTopic(const char * const topic) 
			throw(Exception &) { } 

		inline virtual StringPimpl getThat() const
			throw(Exception &) { return StringPimpl("*"); }

		inline virtual StringPimpl getTopic() const
			throw(Exception &) { return StringPimpl("*"); }

		inline virtual GraphBuilder *clone() 
		//	throw(Exception &) 
		{ return 0; } 

		inline virtual void setPredicate(const char * const name, const char * const value) 
			throw(Exception &) { } 

		inline virtual StringPimpl getPredicate(const char * const name) const
			throw(Exception &) { return StringPimpl(""); } 

		inline virtual bool predicateMatch(const char * const predicateName, const char * const aimlPattern) const
			throw(Exception &) { return false; } 

		inline virtual StringPimpl getPreviousBotResponse(const unsigned int &previousBotResponse, const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &) { return StringPimpl(""); } 

		inline virtual StringPimpl getPreviousUserInput(const unsigned int &previousUserInput, const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &) { return StringPimpl(""); } 

		inline virtual StringPimpl getBotPredicate(const char * const name) const
			throw(Exception &) { return StringPimpl(""); } 

		inline virtual void setBotPredicate(const char * const name, const char * const value) 
			throw(Exception &) { } 

		inline virtual void setBotConfigurationSchema(const char *const schema) 
			throw(Exception &) { } 
		
		inline virtual void setBotConfigurationValidation(const bool trueOrFalse = true) 
			throw(Exception &) { } 
		
		inline virtual void parseSubstitutionFile(const char *const fileName)
			throw(XMLErrorException &, FileNotFoundException &, Exception &) { } 

		inline virtual void setInputSubstitution(const char *const find, const char *const replace)
			throw(IllegalArgumentException &, Exception &) { } 

		inline virtual void setGenderSubstitution(const char *const find, const char *const replace)
		throw(IllegalArgumentException &, Exception &) { } 

		inline virtual void setPersonSubstitution(const char *const find, const char *const replace)
		throw(IllegalArgumentException &, Exception &) { } 

		inline virtual void setPerson2Substitution(const char *const find, const char *const replace) 
			throw(IllegalArgumentException &, Exception &) { } 

		inline virtual void parseSentenceSplitterFile(const char *const fileName) 
			throw(XMLErrorException &, FileNotFoundException &, Exception &) { } 

		inline virtual void parsePropertiesFile(const char *const fileName) 
			throw(XMLErrorException &, FileNotFoundException &, Exception &) { }

		inline virtual void setSentenceSplitter(const char *const splitter) 
			throw(Exception &) { } 
		
		inline virtual StringPimpl getVersion() const 
			throw(Exception &) { return StringPimpl(""); }
		
		inline virtual void setCallBacks(CallBacks *callBacks) 
			throw(Exception &) { }
		
		inline virtual int getSize() const 
			throw(Exception &) { return 0; }
		
		
		inline virtual void storeGossip(const char * const gossip) 
			throw(Exception &) { }

		inline virtual StringPimpl getId() const
			throw(Exception &) { return 0; }

		inline virtual void setId(const char * const)
			throw(Exception &) { } 

		inline virtual StringPimpl getPreviousBotResponsePunctuation(const unsigned int &previousBotResponse, 
															  const unsigned int &sentence) const 
			throw(IllegalArgumentException &, Exception &)
			
			{ return StringPimpl(); } 
			
		inline virtual void addCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &) { }

		inline virtual void removeCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &) { } 

		inline virtual CustomTags *getCustomTags(unsigned int index) { return 0; }
		inline virtual unsigned int getCustomTagsSize() { return 0; }

		inline virtual NodeMapper &getRootNodeMapper() 
		{
			NodeMapper n(*this);	
			return n;
		} 

		inline virtual StringPimpl callSystemCommand(const char * const command)
			throw(Exception &)
		{
			return StringPimpl("");
		}

		inline virtual ~GraphBuilderInternalNoOps() { }

};


} //end of impl namespace
} //end of rebecca namespace

#ifdef _WIN32
#    pragma warning ( pop )
#endif


#endif
