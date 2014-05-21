#ifndef REBECCA_IMPL_GRAPHBUILDERAIML_H
#define REBECCA_IMPL_GRAPHBUILDERAIML_H

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

//Rebecca includes
#include <rebecca/adt/String.h>
#include <rebecca/adt/Map.h>
#include <rebecca/adt/Vector.h>
#include <rebecca/adt/Deque.h>
#include <rebecca/impl/NodeMapper.h>
#include <rebecca/impl/GraphBuilderInternal.h>
#include <rebecca/impl/GraphBuilderInternalNoOps.h>

//Boost includes
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>

//Xerces includes
#include <xercesc/parsers/SAXParser.hpp>


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
XERCES_CPP_NAMESPACE_USE
using namespace boost;
using namespace std;

class GraphBuilderAIML : public GraphBuilderInternal
{
	public:

		GraphBuilderAIML() 
			throw(InitializationException &, Exception &);

		GraphBuilderAIML(const GraphBuilderAIML &builder)
			throw(InitializationException &, Exception &);

		//These are methods from GraphBuilderInternal

		virtual void createGraph() throw(XMLErrorException &, Exception &);
		virtual void clearStars();
		virtual void addStar(const StringPimpl &star);
		virtual void setUseThatStar();
		virtual void removePunctuation(String &stringToRemove);
		virtual void setUseTopicStar();
		virtual void setUseDefaultStar();

		virtual StringPimpl getStar(const unsigned int &index) const
			throw(IllegalArgumentException &, Exception &);

		virtual StringPimpl getThatStar(const unsigned int &index) const
			throw(IllegalArgumentException &, Exception &);

		virtual StringPimpl getTopicStar(const unsigned int &index) const
			throw(IllegalArgumentException &, Exception &);

		virtual StringPimpl genderSubstitute(const StringPimpl &input) const
			throw(Exception &);

		virtual StringPimpl inputSubstitute(const StringPimpl &input);


		virtual StringPimpl personSubstitute(const StringPimpl &input) const
			throw(Exception &);

		virtual StringPimpl person2Substitute(const StringPimpl &input) const
			throw(Exception &);

		virtual CallBacks &getCallBacks()
			throw(Exception &);

		virtual StringPimpl checkedInfiniteLoopGetResponse(const StringPimpl &userInput, bool keepPreviousUserInput = true)
			throw(RecursionException &, Exception &);

		virtual void setSize(const unsigned int newSize);

		virtual void addFile(const char * const file)
			throw(FileNotFoundException &, Exception &);	

		virtual void addDirectory(const char * const directory, const char * const regularExpression = ".*\\.aiml")
			throw(IllegalArgumentException &, DirectoryNotFoundException &, Exception &);

		virtual void addString(const char * const stringContainingAIML)
			throw(Exception &);

		virtual void setAddStringAIMLHeader(const char * const aimlHeader)
			throw(Exception &);

		virtual void setAddStringAIMLFooter(const char * const aimlFooter)
			throw(Exception &);

		virtual void setAIMLSchema(const char * const schema)
			throw(Exception &);

		virtual void setCommonTypesSchema(const char * const schema)
			throw(Exception &);

		virtual void setAIMLValidation(bool trueOrFalse = true)
			throw(Exception &);

		virtual StringPimpl getResponse(const char * const input)
			throw(Exception &);

		virtual void setThat(const char * const that)
			throw(Exception &);

		virtual void setTopic(const char * const topic)
			throw(Exception &);

		virtual ~GraphBuilderAIML();

		virtual GraphBuilder *clone();

		virtual StringPimpl getThat() const
			throw(Exception &);

		virtual StringPimpl getTopic() const
			throw(Exception &);

		virtual void setPredicate(const char * const name, const char * const value)
			throw(Exception &);

		virtual StringPimpl getPredicate(const char * const name) const
			throw(Exception &);

		virtual bool predicateMatch(const char * const predicateName, const char * const aimlPattern) const
			throw(Exception &);

		virtual StringPimpl getPreviousBotResponse(const unsigned int &previousBotResponse, const unsigned int &sentence) const
				throw(IllegalArgumentException &, Exception &);

		virtual StringPimpl getPreviousUserInput(const unsigned int &previousUserInput, const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &);

		virtual StringPimpl getBotPredicate(const char * const name) const
			throw(Exception &);

		virtual void setBotPredicate(const char * const name, const char * const value)
			throw(Exception &);

		virtual void setBotConfigurationSchema(const char *const schema)
			throw(Exception &);

		virtual void setBotConfigurationValidation(const bool trueOrFalse = true)
			throw(Exception &);

		virtual void parseSubstitutionFile(const char *const fileName)
			throw(XMLErrorException &, FileNotFoundException &, Exception &);

		virtual void setInputSubstitution(const char *const find, const char *const replace)
			throw(IllegalArgumentException &, Exception &);

		virtual void setGenderSubstitution(const char *const find, const char *const replace)
			throw(IllegalArgumentException &, Exception &);

		virtual void setPersonSubstitution(const char *const find, const char *const replace)
			throw(IllegalArgumentException &, Exception &);

		virtual void setPerson2Substitution(const char *const find, const char *const replace)
			throw(IllegalArgumentException &, Exception &);

		virtual void parseSentenceSplitterFile(const char *const fileName)
			throw(XMLErrorException &, FileNotFoundException &, Exception &);

		virtual void parsePropertiesFile(const char *const fileName)
			throw(XMLErrorException &, FileNotFoundException &, Exception &);

		virtual void setCallBacks(CallBacks *callBacks)
			throw(Exception &);

		virtual void setSentenceSplitter(const char *const splitter)
			throw(Exception &);

		virtual int getSize() const
			throw(Exception &);


		virtual StringPimpl getVersion() const
			throw(Exception &);

		virtual void storeGossip(const char * const gossip)
			throw(Exception &);

		virtual StringPimpl getId() const
			throw(Exception &);

		virtual void setId(const char * const id) 
			throw(Exception &);

		virtual StringPimpl getPreviousBotResponsePunctuation(const unsigned int &previousBotResponse, 
			                                                  const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &);

		virtual void addCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &);

		virtual void removeCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &);

		virtual NodeMapper &getRootNodeMapper()
		{
			return m_NodeMapperRoot;
		}

		virtual map<String, CustomTagWithDelete> &getCustomTagsMapRef()
		{
			return m_customTags;
		}

		virtual StringPimpl callSystemCommand(const char * const command)
			throw(Exception &);


	private:
		virtual void makeGraph(const InputSource &source, const String &file); 		
		virtual void initializeXerces();
		virtual void parseConfigurationFile(const String &fileName);
		virtual StringPimpl getResponseInternal(const char * const input, bool keepPreviousUserInput = true);
		virtual void init()
			throw(XMLException &, Exception &);

		class SubstitutionRegEx
		{
			public:
				SubstitutionRegEx(const regex &find, const String &replace)
					: m_find(find),
					  m_replace(replace)
				{ }

				regex m_find;
				String m_replace;
		};

		virtual StringPimpl substitute(const StringPimpl &input, const std::vector<SubstitutionRegEx> &substitution) const;
		MapStringBool m_filesGraphed;
		MapStringBool m_stringsGraphed;

		String m_aimlHeader;
		String m_aimlFooter;

		bool m_setAIMLValidation;
		bool m_doConfigurationValidation;

		String m_aimlSchema;
		String m_configurationSchema;
		String m_commonTypesSchema;
		
		String m_thatString;

		VectorString m_previousSrai;

		/**
		 * Root of the NodeMapper tree.
		 *
		 */
		NodeMapper m_NodeMapperRoot;
		MapStringString m_predicates;
		MapStringString m_botPredicates;

		///@todo For multi-threading this has to be thread specific storage (TSS)
		VectorString m_star; 
		VectorString m_thatStar;
		VectorString m_topicStar;
		bool m_useThatStar;
		bool m_useTopicStar;
		//End of what needs to be put into TSS 
		
		DequeDequeString m_previousBotResponse;
		DequeDequeString m_previousBotResponseWithPunct;
		DequeString m_previousUserInput;
		
		typedef Vector<SubstitutionRegEx>::type VectorSubstitutionRegEx;
		VectorSubstitutionRegEx m_inputSubstitutions;
		VectorSubstitutionRegEx m_genderSubstitutions;
		VectorSubstitutionRegEx m_personSubstitutions;
		VectorSubstitutionRegEx m_person2Substitutions;

		shared_ptr<SAXParser> m_AIMLparser;
		shared_ptr<SAXParser> m_configurationParser;
		shared_ptr<DocumentHandler> m_AIMLDocumentHandler;
		shared_ptr<DocumentHandler> m_configurationDocumentHandler;
		shared_ptr<ErrorHandler> m_AIMLErrorHandler;
		shared_ptr<ErrorHandler> m_configurationErrorHandler;

		String m_sentenceSplitters;
		
		///Number of categories loaded
		int m_size;

		CallBacks m_defaultCallBacks;

		///CallBack pointer.  It will NOT be deleted internally.
		CallBacks *m_callBacks;
		
		String m_id;

		typedef CustomTags *(*EntryPointfuncPtr)(void);  
		typedef void(*ExitPointfuncPtr)(CustomTags *);  


		///@todo put this into the adt
		map<String, CustomTagWithDelete> m_customTags;
		//vector<CustomTagWithDelete> m_customTags;

};


} //end of impl namespace
} //end of rebecca namespace

#ifdef _WIN32
#    pragma warning ( pop )
#endif


#endif

