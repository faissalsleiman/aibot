#ifndef REBECCA_GRAPHBUILDER_H
#define REBECCA_GRAPHBUILDER_H

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
#include <rebecca/exports.h>
#include <rebecca/StringPimpl.h>
#include <rebecca/CallBacks.h>
#include <rebecca/Exceptions.h>

namespace rebecca 
{
namespace impl 
{

/** 
 * This is the interface from which all 
 * AIML action operations will take place.
 * 
 * This class provides all the operations 
 * from loading the AIML tag data from files 
 * into memory to querying the AIML data in 
 * memory with user input to get back the 
 * response.
 *
 * Use AimlFacade to create the concrete 
 * representation of this interface and 
 * AimlFacade for getting a handle to this 
 * interface.  ALWAYS let AimlFacade manage 
 * the memory to this interface. Never try to 
 * delete this interface directly.
 *
 * How to use this interface:
 * 
 * Instantiate a AimlFacade object.  Call 
 * AimlFacade::getGraphBuilder() to get a 
 * reference to this interface.
 *
 * Now, using that reference to this interface:
 *  
 * Create an instance of your CallBacks subclass 
 * and call GraphBuilder::setCallBacks() with the 
 * address of your subclass.  GraphBuilder WILL NOT 
 * manage the memory of your CallBacks subclass.  
 * You are responsible for managing the memory of 
 * your subclass.  You can ommit this step if you 
 * do not wish to log the AIML gossip tags and if 
 * you do not want informative or error handling 
 * routines during the load and runtime of 
 * RebeccaAIML.
 *
 * Setup any xsd's for validation of AIML tags 
 * through GraphBuilder::setAIMLSchema().  
 * Activate validation by calling 
 * GraphBuilder::setAIMLValidation(). 
 * Optionally if you are sure that your AIML files 
 * are AIML XML compliant/correct you can ommit this 
 * step.  However, if you do ommit this step and have 
 * illegal AIML tags in your files, then the illegal AIML 
 * XML tags will cause RebeccaAIML to abort through an 
 * exception or crash altogether.  Or in C++ terms, the
 * behaviour of RebeccaAIML is undefined.
 *
 * Setup any xsd's for validation of configuration 
 * files for Substitution, Sentence Splitters, and Bot 
 * properites.  Those methods would be
 * GraphBuilder::setCommonTypesSchema() and 
 * GraphBuilder::setBotConfigurationSchema().  The provided
 * xsd's that should be used are bot-configuration.xsd and 
 * common-types.xsd.  At this time if you use your own custom
 * version, it will result in undefined behavior (a.k.a crashing 
 * or exception throwing by Rebecca AIML).  Activate both 
 * schema's through GraphBuilder::setBotConfigurationValidation().
 *
 * Parse RebeccaAIML configuration files through the methods 
 * GraphBuilder::parseSubstitutionFile(),
 * GraphBuilder::parsePropertiesFile(), 
 * and GraphBuilder::parseSentenceSplitterFile() 
 * with their respective XML files. Provided sample 
 * configuration files are bots.xml, properties.xml,
 * sentence-splitters.xml, and substitutions.xml.
 * Optionally, you can ommit this step or augment it 
 * by directly calling 
 * GraphBuilder::setSentenceSplitter(), 
 * GraphBuilder::setPersonSubstitution(),
 * GraphBuilder::setPerson2Substitution(),
 * GraphBuilder::setGenderSubstitution(),
 * GraphBuilder::setBotPredicate()
 * with the appropriate values.  
 * 
 * Call GraphBuilder::setId() to setup the Id 
 * to be returned by the AIML tag "Id".  If you 
 * ommit this step, an empty string for the AIML
 * tag "Id" will always be returned.
 * 
 * Call GraphBuilder::addFile() to add one file
 * at a time or call GraphBuilder::addDirectory() to
 * add an entire directory with AIML tag files.
 * 
 * Call GraphBuilder::createGraph() to begin the 
 * parsing of the AIML files which creates the 
 * internal data structures. 
 *
 * Call GraphBuilder::getResponse() to query the
 * AIML data structures with input to
 * get RebeccaAIML's bot response back.
 */
class REBECCA_EXPORT GraphBuilder
{
	public:

		/**
		 * Add one AIML file to the internal queue for 
		 * latter processing by GraphBuilder::createGraph().
		 *
		 * Once all the the files you want to be parsed 
		 * have been added to the internal queue by 
		 * GraphBuilder::addFile() and/or GraphBuilder::addDirectory()
		 * and/or GraphBuilder::addString(), 
		 * call GraphBuilder::createGraph() to parse and build
		 * the RebeccaAIML in-memory data structures.
		 * 
		 * Since parsing and building the in-memory data
		 * structures is expensive, it's best to keep the 
		 * functionality for queueing files and the 
		 * functionality for actually creating the internal 
		 * data structures seperate for convience.
         *
		 * Both relative and absolute paths are allowed.  Although
		 * you can use Windows paths it's recommended to only use
		 * unix paths to be cross plaform.  Windows paths will only 
		 * work on Windows.  Unix paths will work both on unix's and
		 * under Windows.
		 * 
		 * Examples that work under both Unix and Windows:
		 * <pre>
		   builder.addFile("/someDir/someFile.aiml");
		   builder.addFile("../../someDir/someFile.aiml");
		   </pre>
	     *
		 * Some examples that <b>only</b> work under Windows.
		 * <pre>
		   builder.addFile("C:\\someDir\\someFile.aiml");
		   builder.addFile("C:/someDir/someFile.aiml");
		   builder.addFile("..\\..\\someDir\\someFile.aiml");
		   </pre>
		 * 
		 *
		 * \param file The AIML file to add to the internal 
		 * queue.
		 *
		 * \exception If the file is not found, this method 
		 * will throw a FileNotFoundException.  If an underlying
		 * method throws an exception, it will be wrapped and 
		 * thrown as a Exception.
		 * 
		 */
		virtual void addFile(const char * const file) 
			throw(FileNotFoundException &, Exception &) = 0;		

		/**
		 * Add entire directory of AIML files to the internal 
		 * queue for latter processing by GraphBuilder::createGraph().
		 *
		 * Once all the the files you want to be parsed 
		 * have been added to the internal queue by 
		 * GraphBuilder::addFile() and/or GraphBuilder::addDirectory()
		 * and/or GraphBuilder::addString(), 
		 * call GraphBuilder::createGraph() to parse and build
		 * the RebeccaAIML in-memory data structures.
		 * 
		 * Since parsing and building the in-memory data
		 * structures is expensive, it's best to keep the 
		 * functionality for queueing files and the 
		 * functionality for actually creating the internal 
		 * data structures seperate for convience.
		 *
		 * Both relative and absolute paths are allowed.  Although
		 * you can use Windows paths it's recommended to only use
		 * unix paths to be cross plaform.  Windows paths will only 
		 * work on Windows.  Unix paths will work both on unix's and
		 * under Windows.
		 *
		 * Examples that work under both Unix and Windows:
		 * <pre>
		   builder.addDirectory("/someDir");
		   builder.addDirectory("../../someDir");
		   </pre>
	     *
		 * Some examples that <b>only</b> work under Windows.
		 * <pre>
		   builder.addDirectory("C:\\someDir");
		   builder.addDirectory("C:/someDir");
		   builder.addDirectory("..\\..\\someDir");
		   </pre>
		 * 
		 *
		 * \param directory The AIML directory to add to the internal 
		 * queue.
		 *
		 * \param regularExpression The regular expression which defines
		 * what a AIML file is within the directory. The default is all
		 * files which end in ".aiml".
		 *
		 * \exception If the directory is not found, this method 
		 * will throw a DirectoryNotFoundException.  If an underlying
		 * method throws an exception, it will be wrapped and 
		 * thrown as a Exception.  If the regular expression is an 
		 * invalid regular expression, IllegalArgumentException will be
		 * thrown.
		 * 
		 */
		virtual void addDirectory(const char * const directory, const char * const regularExpression = ".*\\.aiml") 
			throw(IllegalArgumentException &, DirectoryNotFoundException &, Exception &) = 0;
		
		/**
		 * Add a string containing AIML to the internal queue
		 * for latter processing by GraphBuilder::createGraph().
		 *
		 * Once all the the files you want to be parsed 
		 * have been added to the internal queue by 
		 * GraphBuilder::addFile() and/or GraphBuilder::addDirectory()
		 * and/or GraphBuilder::addString(), 
		 * call GraphBuilder::createGraph() to parse and build
		 * the RebeccaAIML in-memory data structures.
         *
		 * Since parsing and building the in-memory data
		 * structures is expensive, it's best to keep the 
		 * functionality for queueing files and the 
		 * functionality for actually creating the internal 
		 * data structures seperate for convience.
		 * 
		 * A quick example would be:
		 * <pre>
           builder.addString
           (
             "<category>"
             "<pattern>test aiml string</pattern>"
             "<template>it simply works!</template>"
             "</category>"
           );
		 </pre>
		 *
		 * By default a AIML Header attached to the begining of your 
		 * string is:
		 * <pre>
         <?xml version="1.0" encoding="ISO-8859-1"?>
         <aiml version="1.0.1" xmlns="http://alicebot.org/2001/AIML-1.0.1"
              xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
              xsi:schemaLocation="http://alicebot.org/2001/AIML-1.0.1 http://aitools.org/aiml/schema/AIML.xsd">
	     </pre>
		 *
		 * and a AIML Footer attached to the end of your string is:
		 * <pre>
		 </aiml>
		 </pre>
		 *
		 * These are automatically attached to the begining and end of 
		 * your string for you to form a correct XML document in memory.
		 * If you want to change either of these two values use
         * GraphBuilder::setAddStringAIMLHeader() and 
		 * GraphBuilder::setAddStringAIMLFooter()
		 * 
		 * \param stringContainingAIML The string that contains the 
		 * AIML to add to the internal queue.
		 *
		 * \exception If an underlying method throws an exception, it will 
		 * be wrapped and thrown as a Exception.
		 */
		virtual void addString(const char * const stringContainingAIML)
			throw(Exception &) = 0;

		/**
		 * Sets the string that is automatically attached to the 
		 * the begining of the string sent to GraphBuilder::addString()
		 * to help form a correct XML document in memory.
		 *
		 * The default string set when Rebecca starts is:
		 * <pre>
         <?xml version="1.0" encoding="ISO-8859-1"?>
         <aiml version="1.0.1" xmlns="http://alicebot.org/2001/AIML-1.0.1"
              xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
              xsi:schemaLocation="http://alicebot.org/2001/AIML-1.0.1 http://aitools.org/aiml/schema/AIML.xsd">
	     </pre>
		 *
		 * \param aimlHeader The string to change which is automatically
		 * attached to the begining of the string sent to 
		 * GraphBuilder::addString()
		 *
		 * \exception If an underlying method throws an exception, it will 
		 * be wrapped and thrown as a Exception.
		 */
		virtual void setAddStringAIMLHeader(const char * const aimlHeader)
			throw(Exception &) = 0;

		/**
		 * Sets the string that is automatically attached to the 
		 * the end of the string sent to GraphBuilder::addString()
		 * to help form a correct XML document in memory.
		 *
		 * The default string set when Rebecca starts is:
		 *
		 * <pre>
		 </aiml>
		 </pre>
		 * \param aimlFooter The string to change which is automatically
		 * attached to the end of the string sent to 
		 * GraphBuilder::addString()
		 *
		 * \exception If an underlying method throws an exception, it will 
		 * be wrapped and thrown as a Exception.
		 *
		 */
		virtual void setAddStringAIMLFooter(const char * const aimlFooter)
			throw(Exception &) = 0;

		/**
		 * Sets the xsd schema for validating AIML tag files.
		 *
		 * \param schema The xsd schema for validating AIML tag files.
		 * The schema path has to be relative to where the files you are 
		 * going to parse are going to be located at.  Use the unix "/" as 
		 * the path seperator and not "\".
		 *
		 * \exception Will not directly throw an exception but if an
		 * underlying method throws an exception, it will be wrapped and
		 * thrown as an Exception.
		 */
		virtual void setAIMLSchema(const char * const schema) 
			throw(Exception &) = 0;

		/**
		 * Sets the common types schema for validating RebeccaAIML 
		 * configuration files.  This has to be set in conjuction with
		 * GraphBuilder::setBotConfigurationSchema.
		 *
		 * \param schema The schema for validating RebeccaAIML 
		 * configuration files.  The schema path has to be relative 
		 * to where the files you are going to parse are going to be 
		 * located at. Use unix "/" as the path seperator and not "\".
		 *
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual void setCommonTypesSchema(const char * const schema) 
			throw(Exception &) = 0;

		/**
		 * Sets whether to use AIML validation from the 
		 * xsd given at GraphBuilder::setAIMLSchema() or not.
		 * 
		 * By default if this is not called, then the AIML 
		 * validation will not be used even if 
		 * GraphBuilder::setAIMLSchema() has been called with a
		 * valid xsd.
		 * 
		 * \param trueOrFalse By default true.  Set this to true
		 * to use validation and false to not use validation.
		 * 
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual void setAIMLValidation(bool trueOrFalse = true) 
			throw(Exception &) = 0;
		
		/** 
		 * Queries the AIML internal in-memory data structures 
		 * with conversational input and returns the AIML response.
		 * 
		 * This is the method which ultimatly you want to call 
		 * after setup to query the AIML brain/data structure 
		 * and get back a response.
		 *
		 * \param input The human conversational input seperated by 
		 * the sentence splitters you setup from either from 
		 * configuration file or GraphBuilder::setSentenceSplitter().
		 * 
		 * \return Returns the AIML response to the human 
		 * conversation.
		 *
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getResponse(const char * const input) 
			throw(Exception &) = 0;
		
		/**
		 * This allows you to hand set the AIML data structure's 
		 * current that.
		 *
		 * This is a more advanced feature that not a lot of 
		 * people will find useful.  It sets the internal that 
		 * which is done automatically by RebeccaAiml.  However, 
		 * this is provided in case you want to do testing or 
		 * set the internal that yourself.
		 *
		 * \param that The internal AIML that in which you can
		 * set yourself if you really want to.
		 * 
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual void setThat(const char * const that) 
			throw(Exception &) = 0;

		/**
		 * This allows you to hand set the AIML data structure's 
		 * current topic.
		 *
		 * This is a more advanced feature that not a lot of 
		 * people will find useful.  It sets the internal topic
		 * which is done automatically by RebeccaAiml.  However, 
		 * this is provided in case you want to do testing or 
		 * set the internal topic yourself.
		 *
		 * \param topic The internal AIML topic in which you can
		 * set yourself if you really want to.
		 * 
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual void setTopic(const char * const topic) 
			throw(Exception &) = 0;

		/**
		 * This returns the AIML data structure's 
		 * current that.
		 *
		 * This is a more advanced feature that not a lot of 
		 * people will find useful.  It returns the AIML data 
		 * structure's current internal that.
		 * However, this is provided in case you want to do 
		 * testing or get the internal that yourself for debugging
		 * purposes.   
		 *
		 * \exception This will not directly throw an exception but if
		 * an underlying method throws an exception, it will be 
		 * wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getThat() const
			throw(Exception &) = 0;

		/**
		 * This returns the AIML data structure's 
		 * current topic.
		 *
		 * This is a more advanced feature that not a lot of 
		 * people will find useful.   returns the AIML data structure's 
		 * current internal topic.
		 * However, this is provided in case you want to do 
		 * testing or get the internal that yourself for debugging
		 * purposes.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getTopic() const
			throw(Exception &) = 0;

		/**
		 * Creates the internal data structures needed to 
		 * be able to query AIML through GraphBuilder::getResponse().
		 * 
		 * After files from GraphBuilder::addFile() and/or 
		 * GraphBuilder::addDirectory() are queued and other
		 * RebeccaAIML setups have taken place this method 
		 * should be called to create the internal data 
		 * structures needed to perform an AIML query.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.  Also, a possible
		 * XMLErrorException can occur through either illegal 
		 * AIML tags or through a bad initialization of the 
		 * internal XML engine.
		 */
		virtual void createGraph() 
			throw(XMLErrorException &, Exception &) = 0;

		/**
		 * Checks if the predicateName matches the aimlPattern and returns true or 
		 * false accordingly.
		 *
		 * This is mostly for just debugging purposes for the user to check against
		 * condition AIML tags since, internally, the condition AIML tags use this 
		 * same method when encountered at runtime during a GraphBuilder::getResponse().
		 *
		 * \param predicateName The variable name to check a AIML pattern against.
		 *
		 * \param aimlPattern The AIML pattern to check against variable name to see 
		 * if the two match.
		 * 
		 * \return Returns true if the AIML pattern matches the predicateName otherwise
		 * returns false.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual bool predicateMatch(const char * const predicateName, const char * const aimlPattern) const
			throw(Exception &) = 0;
		
		/** 
		 * Sets a predicate inside of the AIML data structure in the same way that a 
		 * AIML "Set" tag does.  
		 * 
		 * This method is called usually whenever the AIML tag "Set" is encountered 
		 * to set a predicate to a value, but it is exposed here so that the user of 
		 * RebeccaAIML api may also set predicates the same way.  After this method is 
		 * called setting up a new predicate with a value, any AIML "Get" tags latter 
		 * encountered querying the predicate name will return the value which was 
		 * set here. 
		 *
		 * \param name The name of the predicate to put into the AIML data structure.
		 * 
		 * \param value The value of the predicate name to put into the AIML data structure.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setPredicate(const char * const name, const char * const value) 
			throw(Exception &) = 0;

		/** 
		 * Gets a predicate inside of the AIML data structure in the same way that a 
		 * AIML "Get" tag does.  
		 * 
		 * This method is called usually whenever the AIML tag "Get" is encountered 
		 * to retrieve a predicate name's value, but it is exposed here so that the user of 
		 * RebeccaAIML api may also get predicates the same way.
		 *
		 * \param name The name of the predicate to get the value of from 
		 * the AIML data structure.
		 * 
		 * \return Returns the value of the predicate's name or empty string if the 
		 * predicate name does not exist in the AIML data structure.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getPredicate(const char * const name) const
			throw(Exception &) = 0;

		/** 
		 * Gets a bot predicate inside of the AIML data structure in the same way that a 
		 * AIML "Bot" tag does.  
		 * 
		 * This method is called usually whenever the AIML tag "Bot" is encountered 
		 * to retrieve a predicate name's value, but it is exposed here so that the user of 
		 * RebeccaAIML api may also get predicates the same way.
		 *
		 * \param name The name of the predicate to get the value of from 
		 * the AIML data structure.
		 * 
		 * \return Returns the value of the predicate's name or empty string if the 
		 * predicate name does not exist in the AIML data structure.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getBotPredicate(const char * const name) const
			throw(Exception &)  = 0;

		/** 
		 * Sets a bot predicate inside of the AIML data structure.  
		 * 
		 * This is the only means to set a bot Predicate so that during a 
		 * GraphBuilder::getResponse() the "Bot" AIML tag returns the predicate
		 * set here.  After this method is called setting up a new predicate 
		 * with a value, any AIML "Bot" tags latter encountered querying the 
		 * predicate name will return the value which was set here. 
		 *
		 * \param name The name of the predicate to put into the AIML data structure.
		 * 
		 * \param value The value of the predicate name to put into the AIML data structure.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setBotPredicate(const char * const name, const char * const value) 
			throw(Exception &) = 0;
		
		/**
		 * Returns a previous RebeccaAIML response.
		 *
		 * Retrives a previous RebeccaAIML bot response returned from 
		 * GraphBuilder::getResponse().  Useful for debugging or informative purposes, 
		 * or to put other AI logic besides just using AIML tags.
		 *
		 * \param previousBotResponse The index of the previous Bot Response to retrieve.
		 *
		 * \param sentence Which sentence of the previous bot response to retrieve.
		 *
		 * \return Returns the pervious Bot Response.
		 *
		 * \exception Throws a IllegalArgumentException if the previousBotResponse or sentence
		 * is out of range.  If an underlying method throws an exception, it will
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getPreviousBotResponse(const unsigned int &previousBotResponse, const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &) = 0;

		/**
		 * Returns a previous RebeccaAIML user input.
		 *
		 * Retrives a previous RebeccaAIML user input fed as an argument into 
		 * GraphBuilder::getResponse().  Useful for debugging or informative purposes, 
		 * or to put other AI logic besides just using AIML tags.
		 *
		 * \param previousUserInput The index of the previous user input to retrieve.
		 *
		 * \param sentence Which sentence of the previous user input to retrieve.
		 *
		 * \return Returns the pervious user input.
		 *
		 * \exception Throws a IllegalArgumentException if the previous user input or sentence
		 * is out of range.  If an underlying method throws an exception, it will
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getPreviousUserInput(const unsigned int &previousUserInput, const unsigned int &sentence) const
			throw(IllegalArgumentException &, Exception &) = 0;
		
		/**
		 * Sets the bot configuration schema to be used with parsing a RebeccaAIML 
		 * configuration file.
		 *
		 * This should be used in conjunction with 
		 * GraphBuilder::setCommonTypesSchema() and one of the 
		 * parseConfiguration methods of: 
         * GraphBuilder::parseSubstitutionFile(),
         * GraphBuilder::parsePropertiesFile(), 
         * and GraphBuilder::parseSentenceSplitterFile() 
         * with their respective XML files. Provided sample 
         * configuration files are bots.xml, properties.xml,
         * sentence-splitters.xml, and substitutions.xml.
		 *
		 * \param schema The schema for validating RebeccaAIML 
		 * configuration files.  The schema path has to be relative 
		 * to where the files you are going to parse are going to be 
		 * located at. Use unix "/" as the path seperator and not "\".
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setBotConfigurationSchema(const char *const schema) 
			throw(Exception &) = 0;

		/** 
		 * Sets XML Validation with the xml schema files from 
		 * GraphBuilder::setBotConfigurationSchema() and 
		 * GraphBuilder::setCommonTypesSchema().
		 *
		 * By default if this is not called, then the 
		 * validation will not be used even if 
		 * GraphBuilder::setBotConfigurationSchema() and 
		 * GraphBuilder::setCommonTypesSchema() has been called 
		 * with a valid xsd.
		 * 
		 * \param trueOrFalse True to turn on validation and false to 
		 * turn off validation.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setBotConfigurationValidation(const bool trueOrFalse = true) 
			throw(Exception &) = 0;

		/**
		 * Parses a substitution file and calls setXXXXSubstitution 
		 * methods for substitutions during runtime.
		 *
		 * Look at the sample xml file substitutions.xml and the xsd 
		 * bot-configuration.xsd for an idea of how to write substitution
		 * files.  More than likely you'll want to just use the sample 
		 * xml file provided.  Feel free to add to it for your own custom
		 * substitutions.
		 * 
		 * Under the covers, as the xml engine parses the substitution
		 * xml file and calls 
		 * GraphBuilder::setInputSubstitution(),
		 * GraphBuilder::setGenderSubstitution(), 
		 * GraphBuilder::setPersonSubstitution(), 
		 * and GraphBuilder::setPerson2Substitution() 
		 * based upon the start tags inside of the xml file.
		 *
		 * \param fileName The name of the substitution file.
		 *
		 * \exception This will throw an XMLErrorException if an XML error 
		 * is encountered.  It will throw a FileNotFoundException if the 
		 * fileName given is incorrect, and it will throw an Exception for 
		 * any underlying exceptions from other methods it might call.
		 */
		virtual void parseSubstitutionFile(const char *const fileName) 
			throw(XMLErrorException &, FileNotFoundException &, Exception &) = 0;

		/**
		 * Parses a sentence splitter file and calls 
		 * GraphBuilder::setSentenceSplitter() for sentence splitters 
		 * during run time.
		 *
		 * Look at the sample xml file sentence-splitters.xml and the xsd 
		 * bot-configuration.xsd for an idea of how to write sentence splitter
		 * configuration files.  More than likely you'll want to just use 
		 * the sample xml file provided.  Feel free to add to it for your 
		 * own custom sentence splitters to it.
		 * 
		 * Under the covers, as the xml engine parses the sentence splitter
		 * xml file, it calls GraphBuilder::setSentenceSplitter() for each
		 * sentence splitter it finds.
		 *
		 * \param fileName The name of the sentence splitter file.
		 * 
		 * \exception This will throw an XMLErrorException if an XML error 
		 * is encountered.  It will throw a FileNotFoundException if the 
		 * fileName given is incorrect, and it will throw an Exception for 
		 * any underlying exceptions from other methods it might call.
		 */
		virtual void parseSentenceSplitterFile(const char *const fileName) 
			throw(XMLErrorException &, FileNotFoundException &, Exception &) = 0;

		/**
		 * Parses a properties file and calls GraphBuilder::setBotPredicate() 
		 * for each property encountered.
		 *
		 * Look at the sample xml file properties.xml and the xsd 
		 * bot-configuration.xsd for an idea of how to write bot properties
		 * configuration files.  More than likely you'll want to just use 
		 * the sample xml file provided.  Feel free to add to it for your 
		 * own custom bot properties to it.
		 * 
		 * Under the covers, as the xml engine parses the bot properties 
		 * xml file, it calls GraphBuilder::setBotPredicate() for each
		 * property it finds.
		 *
		 * \param fileName The name of the bot property file.
		 * 
		 * \exception This will throw an XMLErrorException if an XML error 
		 * is encountered.  It will throw a FileNotFoundException if the 
		 * fileName given is incorrect, and it will throw an Exception for 
		 * any underlying exceptions from other methods it might call.
		 *
		 */
		virtual void parsePropertiesFile(const char *const fileName)
			throw(XMLErrorException &, FileNotFoundException &, Exception &) = 0;
		
		/** 
		 * Adds a sentence splitter to distinguish the end of a sentence.
		 *
		 * Each time this is called with a character or string, that character or 
		 * string is added as a sentence splitter. Sentence splitters are used 
		 * internally to distinguish the end of a sentence.  See 
		 * GraphBuilder::parseSentenceSplitterFile() for a convience method for
		 * parsing an example sentence splitter file provided.
		 *
		 * \param splitter The character or string to be added as a splitter.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setSentenceSplitter(const char *const splitter) 
			throw(Exception &) = 0;

		/** 
		 * Sets a input substitution for the input that goes into 
		 * GraphBuilder::getResponse().
		 *
		 * Substitutions are good so as to not write duplicate AIML.  A
		 * simple example would be: 
		 *
		 * setInputSubstitution("it's", "it is");
		 *
		 * Now, if the input is: 
		 * 
		 * GraphBuilder::getResponse("It's a great day");
		 *
		 * The input will be substituted internally for "It is a great day".  
		 * Take note that the first argument to this method accepts regular 
		 * expressions which make this method more robust.  For example, it 
		 * is more robust to use the word boundary "\b" as in:
		 *
		 * setInputSubstitution("\bit's\b", "it is");
		 *
		 * Now, "it's" will only be substituted for "it is" when there is a 
		 * white space character on each side. 
		 *
		 * See GraphBuilder::parseSubstitutionFile(), a convience method for
		 * parsing a provided substitution file.
		 *
		 * \param find A regular expression to search for in the input of 
		 * GraphBuilder::getResponse().
		 *
		 * \param replace The text to replace with.  This is NOT a regular 
		 * expression.
		 *
		 * \exception IllegalArgumentException will be thrown if the first 
		 * argument is a illegal regular expression. it will throw an 
		 * Exception for any underlying exceptions from other methods it might 
		 * call. 
		 */
		virtual void setInputSubstitution(const char *const find, const char *const replace) 
			throw(IllegalArgumentException &, Exception &) = 0;

		/** 
		 * Sets a gender substitution for AIML tag "Gender"
		 *
		 * Gender AIML tag is to replace all occurances of one gender 
		 * with that of another.  So, this provided method allows the 
		 * gender substiutions to be set.  None are hardcoded internally
		 * for the "Gender" AIML tag. A simple example to use this would 
		 * be: 
		 *
		 * setGenderSubstitution("he", "she");
		 *
		 * Now, when the gender tag is encountered it will replace all 
		 * occurances of "he" with "she".
		 *
		 * Take note that the first argument to this method accepts regular 
		 * expressions which make this method more robust.  For example, it 
		 * is more robust to use the word boundary "\b" as in:
		 *
		 * setGenderSubstitution("\bhe\b", "she");
		 *
		 * Now, "he" will only be substituted for "she" when there is a 
		 * white space character on each side.
		 *
		 * \param find A regular expression to search for inside of the 
		 * "Gender" AIML tag.
		 *
		 * \param replace The text to replace with.  This is NOT a regular 
		 * expression.
		 *
		 * \exception IllegalArgumentException will be thrown if the first 
		 * argument is a illegal regular expression. it will throw an 
		 * Exception for any underlying exceptions from other methods it might 
		 * call. 
		 */
		virtual void setGenderSubstitution(const char *const find, const char *const replace) 
			throw(IllegalArgumentException &, Exception &) = 0;

		/** 
		 * Sets a person substitution for AIML tag "Person"
		 *
		 * From the AIML specification:
		 * 
		 * The "Person" AIML tag is to replace words with first-person aspect 
		 * in the result of processing the contents of the person element 
		 * with words with the grammatically-corresponding third-person aspect; and
         * replace words with third-person aspect in the result of processing the 
		 * contents of the person element with words with the grammatically-corresponding 
		 * first-person aspect. 
		 *
		 * 
		 * A simple example to use this would be: 
		 *
		 * setPersonSubstitution("he was ", "I was");
		 *
		 * Now when the "Person" tag is encountered it will replace all 
		 * occurances of "he was" with "I was".
		 *
		 * Take note that the first argument to this method accepts regular 
		 * expressions which make this method more robust.  For example, it 
		 * is more robust to use the word boundary "\b" as in:
		 *
		 * setGenderSubstitution("\bhe was\b", "I was");
		 *
		 * Now, "he was" will only be substituted for "I was" when there is a 
		 * white space character on each side.
		 *
		 * \param find A regular expression to search for inside of the 
		 * "Person" AIML tag.
		 *
		 * \param replace The text to replace with.  This is NOT a regular 
		 * expression.
		 *
		 * \exception IllegalArgumentException will be thrown if the first 
		 * argument is a illegal regular expression. it will throw an 
		 * Exception for any underlying exceptions from other methods it might 
		 * call. 
		 */
		virtual void setPersonSubstitution(const char *const find, const char *const replace) 
			throw(IllegalArgumentException &, Exception &) = 0;

		/** 
		 * Sets a person2 substitution for AIML tag "Person2"
		 *
		 * From the AIML specification:
		 * 
		 * The "Person2" AIML tag is to replace words with first-person aspect 
		 * in the result of processing the contents of the person2 element with 
		 * words with the grammatically-corresponding second-person aspect; and
		 * replace words with second-person aspect in the result of processing the 
		 * contents of the person2 element with words with the 
		 * grammatically-corresponding first-person aspect.
		 *
		 * 
		 * A simple example to use this would be: 
		 *
		 * setPersonSubstitution("with you ", "with me");
		 *
		 * Now when the "Person2" tag is encountered it will replace all 
		 * occurances of "with you" with "with me".
		 *
		 * Take note that the first argument to this method accepts regular 
		 * expressions which make this method more robust.  For example, it 
		 * is more robust to use the word boundary "\b" as in:
		 *
		 * setGenderSubstitution("\bwith you\b", "with me");
		 *
		 * Now, "with you" will only be substituted for "with me" when there is a 
		 * white space character on each side.
		 *
		 * \param find A regular expression to search for inside of the 
		 * "Person2" AIML tag.
		 *
		 * \param replace The text to replace with.  This is NOT a regular 
		 * expression.
		 *
		 * \exception IllegalArgumentException will be thrown if the first 
		 * argument is a illegal regular expression. it will throw an 
		 * Exception for any underlying exceptions from other methods it might 
		 * call. 
		 */
		virtual void setPerson2Substitution(const char *const find, const char *const replace) 
			throw(IllegalArgumentException &, Exception &)  = 0;
		
		/**
		 * Returns the version of rebeccaAIML.
		 *
		 * \return The version of rebeccaAIML.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getVersion() const 
			throw(Exception &) = 0;
		
		/** 
		 * Returns the number of AIML categories loaded
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual int getSize() const 
			throw(Exception &) = 0;

		/** 
		 * Sets the subclass of CallBacks to use for 
		 * RebeccaAIML callbacks.
		 *
		 * SubClass CallBacks with your own custom 
		 * subclass and then instantiate it.  Call this
		 * method with the address of your instantiated 
		 * class.  This method *WILL NOT* try to deallocate 
		 * the memory of your instantiated subcalss.  You 
		 * are responsbile for the memory management of it.
		 *
		 * \param callBacks The adress of the instantiation of 
		 * your subclass.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setCallBacks(CallBacks *callBacks) 
			throw(Exception &) = 0;

		/** 
		 * Stores gossip the same way the AIML tag "Gossip" does.
		 *
		 * This under the covers will just call the callback 
		 * CallBacks::storeGossip().  If no callback is set through
		 * GraphBuilder::setCallBacks() this does nothing.
		 *
		 * \param gossip The textual gossip to store.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void storeGossip(const char * const gossip) 
			throw(Exception &) = 0;
		
		/** 
		 * Gets the id the same way the AIML tag "Id" does.
		 *
		 * This will return the Id set by GraphBuilder::setId().
		 * If GraphBuilder::setId has not been called, then this 
		 * will return an empty string.
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl getId() const
			throw(Exception &) = 0;
		
		/**
		 * Sets the id to be returned by the AIML tag "Id".
		 *
		 * Set this to what you want the AIML tag "Id" to return.
		 * If you do not se this, the AIML tag "Id" will just return 
		 * an empty string.
		 *
		 * \param id The id to set for the AIML tag "Id"
		 *
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual void setId(const char * const id)
			throw(Exception &) = 0;

		/**
		 * Adds a custom AIML tag library which should be a 
		 * seperate compiled .dll (Windows) or .so (Linux).
		 *
		 * The .dll or .so that has the custom AIML tags must 
		 * conform to the proper format.  The proper format is 
		 * that the .dll/.so should have a class that inherits 
		 * from CustomTags in it.  Also the two global C functions of 
		 * CustomTags *rebeccaAIMLLoadCustomTags() and 
		 * rebeccaAIMLRemoveCustomTags(CustomTagsImpl *customTags) 
		 * must be present. rebeccaAIMLLoadCustomTags returns a new instance
		 * of the class that inherits from CustomTags and 
		 * rebeccaAIMLRemoveCustomTags takes a CustomTags argument and deletes
		 * the object.  If both of these C functions cannot be found, an 
		 * exception will be thrown.
		 * 
		 * \param library The name of the library without the 
		 * extension of .dll or .so on the end.
		 *
		 * \exception This will throw a FileNotFoundException if 
		 * the .dll or .so does not exist on the file system and it 
		 * will throw a generic Exception if it cannot load the 
		 * .dll or .so
		 */
		virtual void addCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &) = 0;

		/**
		 * Removes a custom AIML tag library which should be a 
		 * seprate compiled .dll (Windows) or .so (Linux)
		 *
		 * The .dll or .so that has the custom AIML tags must 
		 * conform to the proper format.  The proper format is 
		 * that the .dll/.so should have a class that inherits 
		 * from CustomTags in it.  Also the two global C functions of 
		 * CustomTags *rebeccaAIMLLoadCustomTags() and 
		 * rebeccaAIMLRemoveCustomTags(CustomTagsImpl *customTags) 
		 * must be present. rebeccaAIMLLoadCustomTags returns a new instance
		 * of the class that inherits from CustomTags and 
		 * rebeccaAIMLRemoveCustomTags takes a CustomTags argument and deletes
		 * the object.  If both of these C functions cannot be found, an 
		 * exception will be thrown.
		 *
		 * \param library The name of the library without the 
		 * extension of .dll or .so on the end.
         *
		 * \exception This will throw a FileNotFoundException if 
		 * the .dll or .so was never loaded in the first place.  It 
		 * will throw a generic Exception if it cannot unload the 
		 * .dll or .so
		 */
		virtual void removeCustomTagLibrary(const char * const library)
			throw(FileNotFoundException &, Exception &) = 0;
		
		/**
		 *
		 * This method acts the same as calling the AIML XML tag 
		 * "System" by sending the command to the operating 
		 * system and returning the output of the command.
		 *
		 * For example, if under dos you call this method with the
		 * string "dir" it will return a string with the full 
		 * directory listing.  
         *
		 * Likewise if under unix you call this method with the 
		 * string "ls" it will return a string with the full directory 
		 * listing.
		 * 
		 * \param command The string of the command to send to the 
		 * underlying operating system.
		 * 
		 * \return Returns the output of the Operating System after it
		 * exectues the string.
		 * 
		 * \exception This will not directly throw an exception 
		 * but if an underlying method throws an exception, it will 
		 * be wrapped and thrown as an Exception.
		 */
		virtual StringPimpl callSystemCommand(const char * const command)
			throw(Exception &) = 0;

		/**
		 * Empty virtual destructor.
		 */
		virtual ~GraphBuilder() { };
};

} //end of namespace impl

//Expose GraphBuilder to rebecca namespace
using rebecca::impl::GraphBuilder;

} //end of namespace rebecca


#ifdef _WIN32
#    pragma warning ( pop )
#endif




#endif
