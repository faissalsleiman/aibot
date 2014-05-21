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

//Boost includes
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>    
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <sstream>
using namespace boost;
using namespace boost::filesystem;

//Stl includes
#include <iostream>
using namespace std;


//Xerces includes
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
XERCES_CPP_NAMESPACE_USE

//Rebecca includes
#include <rebecca/impl/GraphBuilderAIML.h>
#include <rebecca/impl/utils/StackTrace.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/GraphHandler.h>
#include <rebecca/impl/ConfigurationHandler.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/GraphHandlerError.h>
#include <rebecca/impl/ConfigurationHandlerError.h>
#include <rebecca/framework/CustomTags.h>
using namespace rebecca;
using namespace rebecca::framework;

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 *
 * The extra includes under Windows is 
 * for the callCommand() method to 
 * operate under Windows
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#    include <windows.h>
#    include <errno.h>
#    include <io.h>
#    include <fcntl.h> 
#    include <ctype.h>
#else 
#   include <dlfcn.h>	
#endif

namespace rebecca
{
namespace impl
{

GraphBuilderAIML::GraphBuilderAIML()
	throw(InitializationException &, Exception &)
	: m_setAIMLValidation(false), 
	  m_NodeMapperRoot(*this),
	  m_useThatStar(false),
	  m_useTopicStar(false),
	  m_doConfigurationValidation(false),
	  m_size(0),
	  m_aimlHeader("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> "
						"<aiml version=\"1.0.1\" xmlns=\"http://alicebot.org/2001/AIML-1.0.1\" "
						"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
						"xsi:schemaLocation=\"http://alicebot.org/2001/AIML-1.0.1 http://aitools.org/aiml/schema/AIML.xsd\">"
	               ),
	  m_aimlFooter("</aiml>")
{
	try 
	{
		LOG_BOT_METHOD("GraphBuilderAIML::GraphBuilderAIML()");

		initializeXerces();
		init();
	}
	catch(const XMLException &toCatch) 
	{
		logging("ERROR, Caught XMLXMLException exception");
		Transcode message(toCatch.getMessage());
		String msg("XMLException during initalization: " + message.getString());
		throw InitializationExceptionImpl(msg.c_str());
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

GraphBuilderAIML::GraphBuilderAIML(const GraphBuilderAIML &builder)
	throw(InitializationException &, Exception &)
	: m_setAIMLValidation(false),
	  m_NodeMapperRoot(*this),
	  m_useThatStar(false),
	  m_useTopicStar(false),
	  m_doConfigurationValidation(false),
	  m_size(0),
	  m_aimlHeader("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> "
						"<aiml version=\"1.0.1\" xmlns=\"http://alicebot.org/2001/AIML-1.0.1\" "
						"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
						"xsi:schemaLocation=\"http://alicebot.org/2001/AIML-1.0.1 http://aitools.org/aiml/schema/AIML.xsd\">"
	               ),
	  m_aimlFooter("</aiml>")
{
	try
	{
		LOG_BOT_METHOD("GraphBuilderAIML::GraphBuilderAIML(const GraphBuilderAIML &builder)");	
		init();
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::init()
	throw(XMLException &, Exception &)
{
	try
	{
		//defaultCallBacks does nothing.
		m_callBacks = &m_defaultCallBacks;

		setThat("*");
		setTopic("*");
		logging("Allocating the parsers for various XML files");
		m_AIMLparser.reset(new SAXParser);
		m_configurationParser.reset(new SAXParser);

		logging("Allocating the document handlers for the respective parsers");
		m_AIMLDocumentHandler.reset(new GraphHandler(m_NodeMapperRoot, *this));
		m_configurationDocumentHandler.reset(new ConfigurationHandler(*this));
		
		logging("Allocating the Error handling routines for the respective parsers");
		m_AIMLErrorHandler.reset(new GraphHandlerError(*this));
		m_configurationErrorHandler.reset(new ConfigurationHandlerError(*this));

		logging("Setting the document handlers for the respective parsers");
		m_AIMLparser->setDocumentHandler(m_AIMLDocumentHandler.get());
		m_configurationParser->setDocumentHandler(m_configurationDocumentHandler.get());

		logging("Setting up the error handlers for the respective parsers");
		m_AIMLparser->setErrorHandler(m_AIMLErrorHandler.get());
		m_configurationParser->setErrorHandler(m_configurationErrorHandler.get());
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::addFile(const char * const file) 
	throw(FileNotFoundException &, Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::addFile(const String &file)");

		logging("<Input> file: " + String(file));

		//Get the file format in the native string for Xerces
		path nativeFileFormat(file);
		
		//Get the complete path to the file
		path completePath = complete(nativeFileFormat);
		if(!exists(nativeFileFormat))
		{
			logging("USER ERROR, is not a file");
			String fileNotFoundMsg = "File:" + String(file) + " was not found";
			throw FileNotFoundExceptionImpl(fileNotFoundMsg.c_str());
		}
		else
		{
			logging("file exists, adding to filesNotGraphed");
			//Get the native file system's string to pass to xerces
			string nativeFile = completePath.string();
			m_filesGraphed.insert(pair<String, bool>(nativeFile, false));
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::addDirectory(const char * const directory, const char * const regularExpression) 
	throw(IllegalArgumentException &, DirectoryNotFoundException &, Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::addDirectory(const String &directory, const char * const regularExpression)");
		logging("<Input> directory: " + String(directory));
		logging("<Input> regular expression: " + String(regularExpression));

		regex rx1(regularExpression, boost::regex::icase);
		smatch what;

		//Get the file format in the native string for Xerces
		path nativeDirFormat(directory);
		
		//Get the complete path to the file
		path completePath = complete(nativeDirFormat);
		if (!exists(nativeDirFormat))
		{
			logging("ERROR, Exception Directory does not exist");
			String directoryNotFoundmsg("Directory:" + String(directory) + " was not found");
			throw DirectoryNotFoundExceptionImpl(directoryNotFoundmsg.c_str());
		}
		
		// default construction yields past-the-end
		directory_iterator end_itr; 

		//Get the native file system's string to pass to xerces
		string nativeDir = completePath.string();
		for ( directory_iterator itr(completePath); itr != end_itr; ++itr )
		{
			const string leaf = itr->path().filename().string();
			if ( !is_directory( *itr ) && regex_match(leaf, what, rx1))
			{
				logging("Found file of:" + leaf);
				String fileLocation(nativeDir);
				fileLocation += "/" + leaf;
				addFile(fileLocation.c_str());
			}
		}	
	}
	catch(filesystem_error &)
	{
		logging("ERROR, filesystem error");
		throw IllegalArgumentExceptionImpl("File system error");
	}
	catch(bad_expression &)
	{
		logging("ERROR, bad expression");
		throw IllegalArgumentExceptionImpl("Bad expression with the regular expression argument");
	}
	catch(runtime_error &)
	{
		logging("ERROR, Runtime error");
		throw IllegalArgumentExceptionImpl("Run time error occured, more than likely with the regular expression");
	}
	catch(FileNotFoundException &)
	{
		logging("FileNotFoundException, you should not be here.");
		throw IllegalArgumentExceptionImpl("File not found exception occured.  You must have passed a bad directory in.");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::addString(const char * const stringContainingAIML)
	throw(Exception &)
{
	try
	{
		String stringToInsert = m_aimlHeader + stringContainingAIML + m_aimlFooter;
		m_stringsGraphed.insert(pair<String, bool>(stringToInsert, false));
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setAddStringAIMLHeader(const char * const aimlHeader)
	throw(Exception &)
{
	try
	{
		m_aimlHeader = aimlHeader;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setAddStringAIMLFooter(const char * const aimlFooter)
	throw(Exception &)
{
	try
	{
		m_aimlFooter = aimlFooter;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


void GraphBuilderAIML::setAIMLSchema(const char * const schema)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setAIMLSchema(const char * const schema)");
		logging("<Input> schema:" + String(schema));
		m_aimlSchema = schema;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setCommonTypesSchema(const char * const schema)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setCommonTypesSchema(const char * const schema)");
		logging("<Input> schema:" + String(schema));
		m_commonTypesSchema = schema;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getResponseInternal(const char * const input, bool keepPreviousUserInput)
{
	/*
	 * Create a tokenizer to tokenize the words.
	 */
	typedef tokenizer<char_separator<char> > tokenize;
	//const iterator to iterate over the tokens
	typedef tokenize::const_iterator CI; 	

	//Create a string from the input
	String stringInput = inputSubstitute(input).c_str();
	
	//Create a "seperator" based on the sentence splitters
	char_separator<char> sep(m_sentenceSplitters.c_str());
	
	/*
	 * Create a "seperator" based on the sentence splitters but 
	 * when the sentence is split with this seperator the splitters 
	 * will be kept.
	 */
	char_separator<char> sepWithKeptDel("", m_sentenceSplitters.c_str());
	
	//Create a tokenizer from the sentences.
	tokenize tokens(stringInput, sep);

	//The response we are going to return
	String returnResponse;
	
	//Iterate over the senteces one sentence at a time.
	for(CI it = tokens.begin(); it != tokens.end(); ++it)
	{
		//Only Srai::getString() disables this
		if(keepPreviousUserInput)
		{
			//Keep the input for the <input index=""> aiml tag
			m_previousUserInput.push_front(stringInput);
		}
		
		//Get the bot response based upon the string 
		String response = m_NodeMapperRoot.getTemplateString(*it);

		if(!response.empty())
		{	
			/* 
			 * We want to tokenize the returned response but keep the 
			 * seperators such as punctiation and semicolons intact.
			 */
			tokenize responseTokens(response, sepWithKeptDel);
			int i = 1;
			DequeString sentencePunct(1);
			DequeString sentence;
			
			//Iterate over the response output one sentence at a time.
			for(CI jit = responseTokens.begin(); jit != responseTokens.end(); ++jit, ++i)
			{
				/*
				 * Create a modifiable string 
				 * version of it and trim the spaces from it.
				 */
				String that(*jit);
				trim(that);
				
				//Fancy way of checking every other sentence
				if(i % 2) 
				{ 
					//boolean for checking if it's just punctuation.
					bool isPunct = false;
					if(that.size() == 1)
					{
					   /*
						* It has a size of 1.  Check if it is a sentence splitter.
						* This can happen when you have a sentece of the
						* form "hi.?" with two punctiations next to each
						* other.
						*/
						for(unsigned int k = 0; k < m_sentenceSplitters.size(); ++k)
						{
							if(that.at(0) == m_sentenceSplitters.at(k))
							{
								sentencePunct.at(0) += that;
								--i;
								isPunct = true;
								break;
							}
						}
					}
					
					if(!isPunct)
					{
					   /*
						* Not punctiation, so add
						* it as that
						*/
						setThat(that.c_str());
						sentence.push_front(that);
						sentencePunct.push_front(that);
					}
				}
				else 
				{
					/*
					 * It is the punctionation by its self.
					 * So tack on the punctionation to the end of the 
					 * previous sentence.
					 */
					if(!sentencePunct.empty()) 
					{
						sentencePunct.at(0) += that;
					}
				}
			}
			
			//Add this response as a previous bot response
			m_previousBotResponse.push_front(sentence);
			
			/*
			 * Add this response as a previous bot response but with the 
			 * added punctiation.
			 */ 
			m_previousBotResponseWithPunct.push_front(sentencePunct);

			/*
			 * If we don't have a return response let's at least return 
             * a seperating space so if we have more sentences to add to
			 * the return response they'll be seperated by a space.
			 */
			if(!returnResponse.empty())
			{
				returnResponse += " ";
			}
			
			//Add the sentence to the returnResponse string
			returnResponse += response;
		}
		else
		{
			logging("Warning empty response being returned");
		}
	} //end of iterating over the sentences one sentence at a time

	//Trim any remaining spaces at the begining or end of the sentence
	trim(returnResponse);

	//Return a StringPimpl version of the string
	return StringPimpl(returnResponse.c_str());
}

StringPimpl GraphBuilderAIML::getResponse(const char * const input)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("StringPimpl GraphBuilderAIML::getResponse(const char * const input)");
		logging("<Input> input:" + String(input));

		m_previousSrai.clear();
		StringPimpl s = getResponseInternal(input);

		/*
		 * We have to call this in case a learn
		 * tag was encountered and it added files
		 * to the internal queue's.  The reason that
		 * a learn tag cannot directly call this is that
		 * it would invalidate iterators and cause a crash.
		 * Thus we have to create the graph here.
		 */
		createGraph();
		return s;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setAIMLValidation(bool trueOrFalse)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setAIMLValidation(bool trueOrFalse)");

		if(trueOrFalse == true)
		{
			logging(String("<Input> trueOrFalse:") + "true");
			m_setAIMLValidation= true;
		}
		else
		{
			logging(String("<Input> trueOrFalse:") + "false");
			m_setAIMLValidation = false;
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::removePunctuation(String &stringToRemove)
//	throw(Exception &)
{

	//I use this to set reserve big enough for one character
	String s("x");
	for(unsigned int i = 0; i < m_sentenceSplitters.size(); ++i)
	{
		s[0] = m_sentenceSplitters.at(i);
		erase_all(stringToRemove, s);
	}

	const String comma(",");
	erase_all(stringToRemove, comma);
}

void GraphBuilderAIML::setThat(const char * const that)
	throw(Exception &)
{
	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenize::const_iterator CI;

	try
	{	
		String stringOfThat(that);
		if(!stringOfThat.empty() && stringOfThat != "")
		{
			m_thatString = that;

			if(!(m_sentenceSplitters.empty()))
			{
				char_separator<char> sep(m_sentenceSplitters.c_str());
				String temp(that);
				tokenize tokens(temp, sep);
				
				for(CI it = tokens.begin(); it != tokens.end(); ++it)
				{
					m_thatString = *it;
				}

				removePunctuation(m_thatString);
			}
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setTopic(const char * const topic)
	throw(Exception &)
{
	try
	{
		String topicToStore(topic);
		removePunctuation(topicToStore);
		setPredicate("TOPIC", topicToStore.c_str());
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getThat() const
	throw(Exception &)
{
	try
	{
		return StringPimpl(m_thatString.c_str());
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getTopic() const
	throw(Exception &)
{
	try
	{
		return getPredicate("topic");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getThatStar(const unsigned int &index) const
	throw(IllegalArgumentException &, Exception &)
{
	if(index > m_thatStar.size())
	{
		throw IllegalArgumentExceptionImpl("The index is greater than thatStar's size");
	}
	else
	{
		try
		{
			//To be on the safe side let us still use the exception throwing "at"
			return m_thatStar.at(m_thatStar.size() - index).c_str();
		}
		catch(std::exception &e)
		{
			throw ExceptionImpl(e.what());
		}
	}
}

StringPimpl GraphBuilderAIML::getTopicStar(const unsigned int &index) const
	throw(IllegalArgumentException &, Exception &)
{
	if(index > m_topicStar.size())
	{
		throw IllegalArgumentExceptionImpl("The index is greater than topicStar's size");
	}
	else
	{   
		try
		{
			//To be on the safe side let us still use the exception throwing "at"
			return m_topicStar.at(m_topicStar.size() - index).c_str();
		}
		catch(std::exception &e)
		{
			throw ExceptionImpl(e.what());
		}
	}
}

void GraphBuilderAIML::setUseThatStar()
//	throw(Exception &)
{
	m_useTopicStar = false;
	m_useThatStar = true;
}

void GraphBuilderAIML::setUseTopicStar()
//	throw(Exception &)
{
	m_useThatStar = false;
	m_useTopicStar = true;
}

void GraphBuilderAIML::setUseDefaultStar()
//	throw(Exception &)
{
	m_useThatStar = false;
	m_useTopicStar = false;
}

void GraphBuilderAIML::setPredicate(const char * const name, const char * const value)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setPredicate(String name, String value)");
		logging("<Input> name: " + String(name));
		logging("<Input> value: " + String(value));
		
		String upperCaseName(name);
		to_upper(upperCaseName);

		if(upperCaseName == "TOPIC")
		{
			logging("Detected a change in topic");
			String tempValue(value);
			trim(tempValue);

			if(tempValue == "")
			{
				logging("The value is empty, defaulting to * for topic");	
				m_predicates[upperCaseName] = "*";
			}
			else
			{
				logging("Normal textual change in topic");
				m_predicates[upperCaseName] = tempValue;
			}
		}
		else
		{
			logging("There is no change in topic.  This is just a normal predicate");
			m_predicates[upperCaseName] = value;
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

bool GraphBuilderAIML::predicateMatch(const char * const predicateName, const char * const aimlPattern) const
	throw(Exception &) 
{
	try
	{
		LOG_BOT_METHOD("bool GraphBuilderAIML::predicateMatch(const char * const predicateName, const char * const aimlPattern)");
		logging("<Input> predicateName:" + String(predicateName));
		logging("<Input> aimlPattern:" + String(aimlPattern));

		StringPimpl predicateValue = getPredicate(predicateName);

		if(!predicateValue.empty())
		{
			logging("predicate Value:" + String(predicateValue.c_str()));	
			typedef tokenizer<char_separator<char> > tokenize;
			typedef tokenizer<char_separator<char> >::const_iterator CI;

			shared_ptr<Template> templateToAdd(new Template);
			templateToAdd->addCharacters(predicateName);
			QueueString wordStack;

			char_separator<char> sep(" ");
			String stringToTok(aimlPattern);
			tokenize pathTokens(stringToTok, sep);

			CI it;
			for(it = pathTokens.begin(); it != pathTokens.end(); ++it)
			{
				logging("Pushing onto word stack: " + *it);
				wordStack.push(*it);
			}	

			wordStack.push("<THAT>");
			wordStack.push("*");
			wordStack.push("<TOPIC>");
			wordStack.push("*");

			GraphBuilderInternalNoOps noOpsGraphBuilder;
			NodeMapper predicateNodeMapper(noOpsGraphBuilder);
			predicateNodeMapper.add(templateToAdd, wordStack);
			String s = predicateNodeMapper.getTemplateString(String(predicateValue.c_str()));

			if(!s.empty())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			logging("Warning, returned empty string on the predicate Name.  The name does not exist");
			return false;
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getPredicate(const char * const name) const
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("String GraphBuilderAIML::getPredicate(String name)");
		logging("<Input>:" + String(name));
		typedef MapStringString::const_iterator CI;

		String upperCaseName(name);
		to_upper(upperCaseName);

		CI it = m_predicates.find(upperCaseName); 

		if(it != m_predicates.end())
		{
			logging("Predicate was Found and it's value is:" + it->second);
			return it->second.c_str();
		}
		else
		{
			logging("Predicate was not found");
			return String().c_str();
		}	
	}
	catch(std::exception &e)
	{	
		throw ExceptionImpl(e.what());
	}
}


void GraphBuilderAIML::createGraph()
	throw(XMLErrorException &, Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::createGraph()");
		
		/*
		 * Iterate and add all the files in the file queue
		 */
		typedef MapStringBool::iterator I;
		for(I i = m_filesGraphed.begin(); i != m_filesGraphed.end(); ++i)
		{
			if(i->second == false)
			{
				logging(i->first + " has not been added to graph yet"); 
				Transcode transcodedString(i->first.c_str());
				LocalFileInputSource lfi(transcodedString.getXmlChar());
				makeGraph(lfi, i->first);
				i->second = true;
			}
			else
			{	//Do nothing
				logging(i->first + " has been added to the graph already");
				logging("Just returning, without doing anything");
			}
		}
		
		/*
		 * Iterate and all the strings from the string queue
		 */
		for(I i = m_stringsGraphed.begin(); i != m_stringsGraphed.end(); ++i)
		{
			if(i->second == false)
			{
				logging(i->first + " has not been added to the graph yet");
				MemBufInputSource mis((const XMLByte*)i->first.c_str(), i->first.size(), "StringInMemory", false);
				makeGraph(mis, "AIML String in memory");
				i->second = true;
			}
			else
			{	//Do nothing
				logging("AIML string has been added to the graph already");
				logging("Just returning, without doing anything");
			}
		}

		/*
		 * Clear the AIML caches now that we fully loaded 
		 * everything available.
		 */
		m_stringsGraphed.clear();
		m_filesGraphed.clear();
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::makeGraph(const InputSource &source, const String &file)
//	throw(XMLErrorException &, Exception &)
{
	LOG_BOT_METHOD("void makeGraph(const String &file)");
	logging("adding file:" + file + " to graph");
	
	try 
	{
		if(m_setAIMLValidation && (!m_aimlSchema.empty()))
		{
			String SchemaLoc = "http://alicebot.org/2001/AIML-1.0.1 " + m_aimlSchema;

			m_AIMLparser->setDoSchema(true);
			m_AIMLparser->setValidationScheme(SAXParser::Val_Always);    // optional.
			m_AIMLparser->setDoNamespaces(true);    // optional
			m_AIMLparser->setExternalSchemaLocation(SchemaLoc.c_str());
		}
	
		logging("Beginging parsing of file");
		m_callBacks->filePreLoad(file.c_str());
		m_AIMLparser->parse(source);
		
		m_callBacks->filePostLoad(file.c_str());
		logging("done parsing file");
	}
	catch (const XMLException& toCatch) 
	{
		Transcode message(toCatch.getMessage());
		String msg("XML Exception from within the parser:" + message.getString());
		logging(msg);
		throw XMLErrorExceptionImpl(msg.c_str());

	}
	catch (const SAXParseException& toCatch) 
	{
		Transcode message(toCatch.getMessage());
		String msg("XML Exception from within the parser:" + message.getString());
		logging(msg);	
		throw XMLErrorExceptionImpl(msg.c_str());
	}

}

void GraphBuilderAIML::initializeXerces()
//	throw(XMLException &, Exception &)
{
	LOG_BOT_METHOD("GraphBuilderAIML::initializeXerces()");
	
	logging("calling XMLPlaformUtils::Initialize");
	XMLPlatformUtils::Initialize();
}

void GraphBuilderAIML::clearStars()
//	throw(Exception &)
{
	m_star.clear();
	m_topicStar.clear();
	m_thatStar.clear();
}

StringPimpl GraphBuilderAIML::getStar(unsigned const int &index) const
throw(IllegalArgumentException &, Exception &)
{
	LOG_BOT_METHOD("StringPimpl GraphBuilderAIML::getStar(const int &index) const");

	if(index > m_star.size() || index < 0)
	{		
		logging("index is greater than star size");
		throw IllegalArgumentExceptionImpl("index is greater than star size");
	}
	else
	{	
		try
		{
			return m_star.at(m_star.size() - index).c_str();
		}
		catch(std::exception &e)
		{
			throw ExceptionImpl(e.what());
		}
	}
}

void GraphBuilderAIML::addStar(const StringPimpl &star)
//	throw(Exception &)
{
	LOG_BOT_METHOD("void GraphBuilderAIML::addStar(const StringPimpl &star)");

	if(star.empty())
	{
		logging("Warning star is empty");
	}
	else
	{	
		String starString(star.c_str());

		logging("<Input>:" + starString);
		if(m_useThatStar)
		{
			logging("Putting the input into That Star");
			m_thatStar.push_back(starString);
		}
		else if(m_useTopicStar)
		{
			logging("Putting the input into topic Star");
			m_topicStar.push_back(starString);
		}
		else
		{
			logging("Putting the input into default/regular star");
			m_star.push_back(starString);
		}
	}
}

GraphBuilderAIML::~GraphBuilderAIML()
{
	LOG_BOT_METHOD("GraphBuilderAIML::~GraphBuilderAIML()");
	
	///@todo put this into the adt
	typedef map<String, CustomTagWithDelete>::iterator I;

	for(I it = m_customTags.begin(); it != m_customTags.end(); ++it)
	{
		/* 
		 * Use the custom tag to delete its self
		 */
		CustomTagWithDelete &tag = it->second;
		(tag.m_deleteFunc)(tag.m_customTags);
		
		///@todo figure out why this can't be free'd.
		///@todo This can't be freed because of a dependency
		//There's a dep where GraphBuilderAIML has a shared_ptr
		//to the guts of the dll.  
		//FreeLibrary(tag.m_dllHandle);
	}
}

GraphBuilder *GraphBuilderAIML::clone()
//	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("GraphBuilder *GraphBuilderAIML::clone()");
		return new GraphBuilderAIML(*this);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getPreviousBotResponse(const unsigned int &previousBotResponse, const unsigned int &sentence) const
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		///@todo Finish this with the sentence integer index.
		if(previousBotResponse - 1 >= m_previousBotResponse.size())
		{
			logging("Error the index is wrong");
			throw IllegalArgumentExceptionImpl("previousBotResponse is greater than the number of bot responses");
			return StringPimpl("");
		}
		else
		{
			DequeString sentencePunct = m_previousBotResponse.at(previousBotResponse - 1);
			if(sentence - 1 >= sentencePunct.size())
			{
				logging("Error the sentence index is wrong");
				throw IllegalArgumentExceptionImpl("previousBotResponse's sentence is greater than the number of bot responses");
				return StringPimpl("");
			}
			else 
			{
				//Still use the "at" for safety checks
				return sentencePunct.at(sentence - 1).c_str();
			}
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getPreviousBotResponsePunctuation(const unsigned int &previousBotResponse, 
																const unsigned int &sentence) const
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		///@todo Finish this with the sentence integer index.
		if(previousBotResponse - 1 >= m_previousBotResponseWithPunct.size())
		{
			logging("Error the index is wrong");
			throw IllegalArgumentExceptionImpl("previousBotResponse is greater than the number of bot responses");
			return StringPimpl();
		}
		else
		{
			DequeString sentencePunct = m_previousBotResponseWithPunct.at(previousBotResponse - 1);
			if(sentence - 1 >= sentencePunct.size())
			{
				logging("Error the sentence index is wrong");
				throw IllegalArgumentExceptionImpl("previousBotResponse's sentence is greater than the number of bot responses");
				return StringPimpl();
			}
			else 
			{
				//Still use the "at" for safety checks
				return sentencePunct.at(sentence - 1).c_str();
			}
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


StringPimpl GraphBuilderAIML::getPreviousUserInput(const unsigned int &previousUserInput, const unsigned int &sentence) const
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		///@todo Finish this with the sentence integer index.

		if(previousUserInput - 1 >= m_previousUserInput.size())
		{
			logging("Error the index is wrong");
			throw IllegalArgumentExceptionImpl("previousUserInput is greater than the number of previous user inputs");
		}
		else
		{
			//Still use the "at" for safety checks
			return StringPimpl(m_previousUserInput.at(previousUserInput - 1).c_str());
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

StringPimpl GraphBuilderAIML::getBotPredicate(const char * const name) const
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("String GraphBuilderAIML::getBotPredicate(String name)");
		logging("<Input>:" + String(name));
		typedef MapStringString::const_iterator CI;

		String upperCaseName(name);
		to_upper(upperCaseName);

		CI it = m_botPredicates.find(upperCaseName); 

		if(it != m_botPredicates.end())
		{
			logging("Predicate was Found and it's value is:" + it->second);
			return it->second.c_str();
		}
		else
		{
			logging("Predicate was not found");
			return String().c_str();
		}	
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setBotPredicate(const char * const name, const char * const value)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setBotPredicate(String name, String value)");
		logging("<Input> name: " + String(name));
		logging("<Input> value: " + String(value));
		
		String upperCaseName(name);
		to_upper(upperCaseName);

		m_botPredicates[upperCaseName] = value;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setBotConfigurationSchema(const char *const schema)
	throw(Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::setBotConfigurationSchema(const char *const schema)");

		logging("<Input> schema:" + String(schema));

		logging("file exists, using it as the schema");
		m_configurationSchema = schema;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setBotConfigurationValidation(const bool trueOrFalse)
	throw(Exception &)
{	
	try
	{
		if(trueOrFalse == true)
		{
			logging(String("<Input> trueOrFalse:") + "true");
			m_doConfigurationValidation = true;
		}
		else
		{
			logging(String("<Input> trueOrFalse:") + "false");
			m_doConfigurationValidation = false;
		}
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

void GraphBuilderAIML::parseSubstitutionFile(const char *const fileName)
	throw(XMLErrorException &, FileNotFoundException &, Exception &)
{

	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::parseSubstitutionFile(const char *const fileName)");
		logging("<Input> file: " + String(fileName));
		
		parseConfigurationFile(fileName);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setInputSubstitution(const char *const find, const char *const replace)
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		m_inputSubstitutions.push_back(SubstitutionRegEx(regex(find, boost::regex::icase), replace));
	}
	catch(bad_expression &)
	{		
		throw IllegalArgumentExceptionImpl("Bad expression in the find regular expression");
	}
	catch(runtime_error &)
	{		
		throw IllegalArgumentExceptionImpl("Run time error in the find regular expression");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::inputSubstitute(const StringPimpl &input)
//	throw(Exception &)
{
	LOG_BOT_METHOD("StringPimpl GraphBuilderAIML::inputSubstitute(const String &input)");
	typedef vector<SubstitutionRegEx>::const_iterator CI;
	
	String returnResponse(input.c_str());

	for(CI it = m_inputSubstitutions.begin(); it != m_inputSubstitutions.end(); ++it)
	{
		replace_all_regex(returnResponse, (*it).m_find, (*it).m_replace);
	}

	return returnResponse.c_str();
}

void GraphBuilderAIML::setGenderSubstitution(const char *const find, const char *const replace)
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		m_genderSubstitutions.push_back(SubstitutionRegEx(regex(find, boost::regex::icase), replace));
	}
	catch(bad_expression &)
	{
		throw IllegalArgumentExceptionImpl("Bad expression in the find regular expression");
	}
	catch(runtime_error &)
	{
		throw IllegalArgumentExceptionImpl("Run time error in the find regular expression");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setPersonSubstitution(const char *const find, const char *const replace)
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		m_personSubstitutions.push_back(SubstitutionRegEx(regex(find, boost::regex::icase), replace));
	}
	catch(bad_expression &)
	{
		throw IllegalArgumentExceptionImpl("Bad expression in the find regular expression");
	}
	catch(runtime_error &)
	{
		throw IllegalArgumentExceptionImpl("Run time error in the find regular expression");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setPerson2Substitution(const char *const find, const char *const replace)
	throw(IllegalArgumentException &, Exception &)
{
	try
	{
		m_person2Substitutions.push_back(SubstitutionRegEx(regex(find, boost::regex::icase), replace));
	}
	catch(bad_expression &)
	{
		throw IllegalArgumentExceptionImpl("Bad expression in the find regular expression");
	}
	catch(runtime_error &)
	{
		throw IllegalArgumentExceptionImpl("Run time error in the find regular expression");
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::genderSubstitute(const StringPimpl &input) const
	throw(Exception &)
{
	LOG_BOT_METHOD("String GraphBuilderAIML::genderSubstitute(const String &input) const");

	try
	{
		return substitute(input, m_genderSubstitutions);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::personSubstitute(const StringPimpl &input) const
	throw(Exception &)
{
	LOG_BOT_METHOD("String GraphBuilderAIML::personSubstitute(const StringPimpl &input) const");

	try
	{
		return substitute(input, m_personSubstitutions);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}


}

StringPimpl GraphBuilderAIML::person2Substitute(const StringPimpl &input) const
	throw(Exception &)
{
	LOG_BOT_METHOD("String GraphBuilderAIML::person2Substitute(const StringPimpl &input) const");

	try
	{
		return substitute(input, m_person2Substitutions);
	} 
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::substitute(const StringPimpl &input, const std::vector<SubstitutionRegEx> &substitution) const
//	throw(Exception &)
{
	LOG_BOT_METHOD("GraphBuilderAIML::substitute(const char * const input, const std::vector<SubstitutionRegEx> &substitution)");

	String inputString(input.c_str());

	///@todo put this into the adt
	map<int, pair<String, String> > mapIntegerMapStringString;
    typedef find_iterator<string::iterator> string_find_iterator;
	typedef vector<SubstitutionRegEx>::const_iterator CI;

	try
	{
		for(CI it = substitution.begin(); it != substitution.end(); ++it)
		{
			for(string_find_iterator ij=
				make_find_iterator(inputString, regex_finder(it->m_find));
				ij!=string_find_iterator();
				++ij)
			{
			   /*
				* Get the index of where the iterator is 
				* at in the string
				*/
				String::difference_type stringIndex;
				stringIndex = distance(inputString.begin(), ij->begin()); 
				
               /*
				* Store the string to be replaced
				* along with the string that will
				* be replacing it.  Store as the key
				* the actual placement of where the 
				* string to be replaced is located at.
				* This way we can iterate over the
				* string and replace the strings in
				* order.
				*
				* Only insert into the map if it already does 
				* not have a replacement for that exact part of 
				* the string.  This gives the replacements at the 
				* begining of the substitutions higher precedence 
				* then any that are lower.
				*/
				if(mapIntegerMapStringString.find(stringIndex) == mapIntegerMapStringString.end())
				{
					stringstream ss;
					ss << *ij;
					mapIntegerMapStringString[stringIndex] = 
						pair<String, String>(ss.str(), it->m_replace);
				}
			}
		}

		///@todo put this into the adt
		typedef map<int, pair<String, String> >::const_iterator CIM;

		/*
		* Iterate over the string in order and replace the strings
		* in order.  Keep track using "diff" how much extra room 
		* to make or to subtract from the string as we replace the
		* olds substrings with our new strings.
		*/
		int diff = 0;
		int stringIndex = 0;
		for(CIM it = mapIntegerMapStringString.begin(); it != mapIntegerMapStringString.end(); ++it)
		{
			int positionInTheString = it->first;

			/*
			 * Check if the replacement string overrlaps with the 
			 * current replacement.  If it does then continue, 
			 * otherwise we'd be stepping on the toes of the previous
			 * replacement.
			 */
			if(positionInTheString < stringIndex)
			{
				continue;
			}
			pair<String, String> wordToReplaceAndBeReplaced = it->second;
			String wordToReplaceWith(wordToReplaceAndBeReplaced.second);
			int sizeOfWordToReplace = wordToReplaceAndBeReplaced.first.size();
			int diffBeforeReplacing = inputString.size();
			inputString.replace(positionInTheString + diff, sizeOfWordToReplace, wordToReplaceWith);
			diff += inputString.size() - diffBeforeReplacing;
			stringIndex = positionInTheString + wordToReplaceWith.size();
			logging("Word right now is:" + inputString);
		}
		
		logging("Word all finished replacing and returning" + inputString);
		return inputString.c_str();
	}
	catch(bad_expression &)
	{
		throw ExceptionImpl("Bad expression with regular expression in GraphBuilderAIML::substitute");
	}
	catch(runtime_error &)
	{
		throw ExceptionImpl("RunTime error with regular expression in GraphBuilderAIML::substitute");
	}
}

void GraphBuilderAIML::parseConfigurationFile(const String &fileName)
//	throw(XMLErrorException &, FileNotFoundException &, Exception &)
{
	LOG_BOT_METHOD("void GraphBuilderAIML::parseConfigurationFile(const String &fileName)");
	logging("<Input> file: " + String(fileName));
	
	if(!exists(fileName))
	{
		String fileNotFoundMsg = "File:" + fileName + " was not found";
		throw FileNotFoundExceptionImpl(fileNotFoundMsg.c_str());
	}

	try 
	{
		if(m_doConfigurationValidation && (!m_configurationSchema.empty()) && !(m_commonTypesSchema.empty()))
		{
			String SchemaLoc = "http://aitools.org/programd/4.5 " + m_commonTypesSchema + 
					            " http://aitools.org/programd/4.5/bot-configuration " + m_configurationSchema;

			m_configurationParser->setDoSchema(true);
			m_configurationParser->setValidationScheme(SAXParser::Val_Always);    // optional.
			m_configurationParser->setDoNamespaces(true);    // optional
			m_configurationParser->setExternalSchemaLocation(SchemaLoc.c_str());
		}
		else
		{
			m_configurationParser->setDoSchema(false);
			m_configurationParser->setValidationScheme(SAXParser::Val_Always);    // optional.
			m_configurationParser->setDoNamespaces(false);    // optional
		}
	
		m_configurationParser->parse(fileName.c_str());
	}
	catch (const XMLException& toCatch) 
	{
		Transcode message(toCatch.getMessage());
		String msg("XMLException: " + message.getString());
		logging(msg);
		throw ExceptionImpl(msg.c_str());
	}
	catch (const SAXParseException& toCatch) 
	{
		Transcode message(toCatch.getMessage());
		String msg("SAXParseException: " + message.getString());
		logging(msg);
		throw ExceptionImpl(msg.c_str());
	}
}

void GraphBuilderAIML::parsePropertiesFile(const char *const fileName)
	throw(XMLErrorException &, FileNotFoundException &, Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::parsePropertiesFile(const char *const fileName)");
		logging("<Input> file: " + String(fileName));

		parseConfigurationFile(fileName);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::parseSentenceSplitterFile(const char *const fileName)
	throw(XMLErrorException &, FileNotFoundException &, Exception &)
{
	try
	{
		LOG_BOT_METHOD("void GraphBuilderAIML::parseSentenceSplitterFile(const char *const fileName)");
		logging("<Input> file: " + String(fileName));

		parseConfigurationFile(fileName);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setSentenceSplitter(const char *const splitter)
	throw(Exception &)
{
	try
	{
		m_sentenceSplitters += splitter;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

int GraphBuilderAIML::getSize() const
	throw(Exception &)
{
	try
	{
		return m_size;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

void GraphBuilderAIML::setSize(const unsigned int newSize)
//	throw(Exception &)
{
	m_size = newSize;
}

StringPimpl GraphBuilderAIML::getVersion() const
	throw(Exception &)
{
	try
	{
		return ".9871";
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setCallBacks(CallBacks *callBacks)
	throw(Exception &)
{
	try
	{
		m_callBacks = callBacks;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::storeGossip(const char * const gossip)
	throw(Exception &)
{
	try
	{
		m_callBacks->storeGossip(gossip);
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

CallBacks &GraphBuilderAIML::getCallBacks()
	throw(Exception &)
{
	try
	{
		return *m_callBacks;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::getId() const
	throw(Exception &)
{
	try
	{
		return m_id.c_str();
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::setId(const char * const id)
	throw(Exception &)
{
	try
	{
		m_id = id;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

StringPimpl GraphBuilderAIML::checkedInfiniteLoopGetResponse(const StringPimpl &userInput, bool keepPreviousUserInput)
	throw(RecursionException &, Exception &)
{
	try
	{
		String userInputString(userInput.c_str());
		typedef VectorString::const_iterator CI;

		for(CI it = m_previousSrai.begin(); it != m_previousSrai.end(); ++it)
		{
			if(userInputString == *it)
			{
				logging("Infinite Recursion detected");
				throw RecursionExceptionImpl("Infinite Recursion detected");
			}
		}

		m_previousSrai.push_back(userInputString);

		/*
		 * Save the stars and then restore them
		 * after the call.  The reason is that 
		 * this can be called recursively through
		 * srai and we want to restore the stars 
		 * after each of those calls.
		 */
		VectorString m_tempStar = m_star; 
		VectorString m_tempThatStar = m_thatStar;
		VectorString m_tempTopicStar = m_topicStar;
		
		StringPimpl response = getResponseInternal(userInputString.c_str(), keepPreviousUserInput);
		
		/*
		 * Now restore the stars to before us 
		 * calling getrepsonse.
		 */
		m_star = m_tempStar;
		m_thatStar = m_tempThatStar;
		m_topicStar = m_tempTopicStar;

		return response;
	}
	catch(std::exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void GraphBuilderAIML::removeCustomTagLibrary(const char * const library)
	throw(FileNotFoundException &, Exception &)
{
	///@todo put this into the adt
	typedef map<String, CustomTagWithDelete>::iterator I;
	I it = m_customTags.find(library);

	if(it != m_customTags.end())
	{
		CustomTagWithDelete &tag = it->second;
		(tag.m_deleteFunc)(tag.m_customTags);

		///@todo fix this, cannot remove the lib right now.
		//There's a dep on the GraphBuilder shared_ptr to 
		//the dll
		//FreeLibrary(tag.m_dllHandle);

		m_customTags.erase(library);
	}
	else
	{
		String msg("Cannot find library to remove:" + String(library));
		throw ExceptionImpl(msg.c_str());
	}
}

void GraphBuilderAIML::addCustomTagLibrary(const char * const library)
	throw(FileNotFoundException &, Exception &)
{
#ifdef _WIN32
	HINSTANCE hinstLib; 
	EntryPointfuncPtr func;
	ExitPointfuncPtr deleteFunc;	
	BOOL fRunTimeLinkSuccess = FALSE; 
 
    // Get a handle to the DLL module. 
	String lib(library);
	lib += ".dll";
    hinstLib = LoadLibrary(lib.c_str()); 
 
    // If the handle is valid, try to get the function address.
    if (hinstLib != NULL) 
    { 
        func = (EntryPointfuncPtr)GetProcAddress(hinstLib, "rebeccaAIMLLoadCustomTags"); 
        deleteFunc = (ExitPointfuncPtr)GetProcAddress(hinstLib, "rebeccaAIMLRemoveCustomTags"); 
		
		if(func == NULL)
		{
			throw ExceptionImpl("rebeccaAIMLLoadCustomTags C function not found in the library");
		}

		if(deleteFunc == NULL)
		{
			throw ExceptionImpl("rebeccaAIMLRemoveCustomTags C function not found in the library");
		}

        // The addresses are valid, call the function.
        fRunTimeLinkSuccess = TRUE;
		
		//Add the tag to the vector of custom tags
		CustomTagWithDelete tag;
		tag.m_customTags = (func) ();
		tag.m_deleteFunc = deleteFunc;
		tag.m_dllHandle = hinstLib;
		m_customTags[library] = tag;
		//m_customTags.push_back(tag); 
    }
   	else 
	{
		throw ExceptionImpl("The library is not a valid dll or shared object");
	}	
#else 
	
	//I am assuming Unix or Linux by default
	//if not windows
	void *handle;
	String lib("lib");
    lib	+= library;
	lib += ".so";	
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	EntryPointfuncPtr func;
	ExitPointfuncPtr deleteFunc;
	char * error;
	if(handle)
	{
		func = (EntryPointfuncPtr)dlsym(handle, "rebeccaAIMLLoadCustomTags");	
		error = dlerror();

		if(error != NULL)
		{
			throw ExceptionImpl("rebeccaAIMLLoadCustomTags C function not found in the library");
		}

		deleteFunc = (ExitPointfuncPtr)dlsym(handle, "rebeccaAIMLRemoveCustomTags");
		error = dlerror();

		if(error != NULL)
		{
			throw ExceptionImpl("rebeccaAIMLRemoveCustomTags C function not found in the library");
		}

		CustomTagWithDelete tag;
		tag.m_customTags = (func) ();
		tag.m_deleteFunc = deleteFunc;
		tag.m_dllHandle = handle;
		m_customTags[library] = tag;
	}
	else
	{
		throw ExceptionImpl("The library is not a valid dll or shared object");		
	}
	
#endif

}

StringPimpl GraphBuilderAIML::callSystemCommand(const char * const command)
	throw(Exception &)
{
	LOG_BOT_METHOD("GraphBuilderAIML::callSystemCommand(const char * const command)");
	String commandString(command);
#ifdef _WIN32

	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	PROCESS_INFORMATION pi;
	HANDLE read_pipe, write_pipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	int fd, create;
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(osv);
	
	GetVersionEx(&osv);

	if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
		SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
		sa.lpSecurityDescriptor = &sd;
	}
	else
	{
		/* Pipe will use ACLs from default descriptor */
		sa.lpSecurityDescriptor = NULL;
	}

	/* Create a new pipe with system's default buffer size */
	if (!CreatePipe(&read_pipe, &write_pipe, &sa, 0))
	{
		//error 
		return StringPimpl();
	}
	

	GetStartupInfo(&si);

	/* Sets the standard output handle for the process to the
	   handle specified in hStdOutput */
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	si.hStdOutput = write_pipe;
	si.hStdError  = (HANDLE) _get_osfhandle (2);
	si.wShowWindow = SW_HIDE;
	string cmd("cmd.exe /c \"");
	cmd += commandString;
	cmd += "\"";
	char *commandLine = strdup(cmd.c_str());
	create = CreateProcess(
		NULL,				// The full path of app to launch
		commandLine, // Command line parameters
		NULL,					// Default process security attributes
		NULL,					// Default thread security attributes
		TRUE,					// Inherit handles from the parent
		0,						// Normal priority
		NULL,					// Use the same environment as the parent
		NULL,					// Use app's directory as current
		&si,					// Startup Information
		&pi);					// Process information stored upon return

	if (!create)
	{
		//error
		return StringPimpl();
	}

	/* Associates a file descriptor with the stdout pipe */
	fd = _open_osfhandle((intptr_t)read_pipe, _O_BINARY);

	/* Close the handle that we're not going to use */
	CloseHandle(write_pipe);

	if (!fd)
	{
		//error
		return StringPimpl();
	}
	
	FILE *file = 0;

	/* Open the pipe stream using its file descriptor */
	file = fdopen(fd, "r");

	if(!file)
	{
		//error
		return StringPimpl();
	}

	if (commandLine)
		free(commandLine);

	int pid = (int)pi.hProcess;
	char c = 0;
	string returnString;
	while (c != EOF)
	{
		c = (char)getc(file);
		
		if(isascii(c))
		{
			returnString += c;
		}
	}

	/* Close the pipe once it's not needed anymore */
	fclose(file);
	return returnString.c_str();

#else

	FILE *file;
	file = popen(commandString.c_str(), "r");
	char c = 0;
	string returnString;
	while (c != EOF)
	{
		c = (char)getc(file);

		if(isascii(c))
		{
			returnString += c;
		}
	}

	fclose(file);
	return returnString.c_str();
#endif

}





} //end of namespace impl
} //end of namespace rebecca
