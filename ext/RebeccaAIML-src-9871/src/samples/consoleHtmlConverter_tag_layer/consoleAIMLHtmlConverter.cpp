
//Rebecca includes
#include <rebecca/all.h>
using namespace rebecca;

//Std includes
#include <iostream>
#include <string>
using namespace std;

/**
 * Prints the usage of the program.
 *
 * This is printed if the incorrect 
 * number of arguments are given.
 *
 */
void printUsage()
{
	cout << endl << "Usage:" << endl << endl	
	     << "consoleAIMLHtmlConverter [directory of aiml files]" << endl << endl << endl
	
	     << "At least one argument should be given." << endl
	     << "That one argument is the directory of your aiml files." << endl
	     << "All AIML files in this directory must end with the" << endl
	     << "extension .aiml  If you are using directory seperators" << endl
	     << "in your argument they must be \"/\" and *not* \"\\\"" << endl << endl << endl
	
	     << "Your output will be in your current working directory in the" << endl
		 << "newly created folder htmlAiml" << endl
	     << "The root index web page will be htmlAiml/[root].html" << endl << endl << endl

	     << "Example:" << endl << endl
	     << "consoleAIMLHtmlConverter -aimlDirectory ../../aiml/annotated_alice" << endl
	     << endl << endl

	     << "------------------" << endl << endl
	     << "Other Available switches and their defaults:" << endl << endl
  	     << "[-aimlSchema or -as]" << endl 
	     << "    AIML Schema Path (default is ../../resources/schema/AIML.xsd)" << endl << endl
	     << "[-botSchema or -bs] " << endl 
	     << "    Bot Schema Path (default is ../resources/schema/bot-configuration.xsd)" << endl << endl
	     << "[-commonSchema or -cs] " << endl
	     << "    Common Schema Path (default is ../resources/schema/common-types.xsd)" << endl << endl
	     << "[-configurationDirectory or -cd] " << endl
	     << "    Configuration directory (default is ../../conf)" << endl << endl
	     << "[-aimlDirectory or -ad] " << endl
	     << "    AIML directory with *.aiml files (default is ../../aiml/annotated_alice)" << endl << endl
	     << endl;

}

/**
 * My Custom CallBacks class.
 * 
 * This class inherits from Rebecca's 
 * CallBacks class and implements the 
 * callbacks for error reporting and 
 * informational reporting purposes.
 */
class consoleAIMLHtmlConverterCallBacks : public CallBacks
{
	public:

		/**
		 * This is called for each AIML 
		 * "Gossip" tag.
		 *
		 * \param gossip The gossip to be 
		 * stored
		 *
		 * I am just printing out the gossip.
		 * You can do other things like store it 
		 * in a file and then reload the file at 
		 * startup as a type of persistance.
		 */
		void storeGossip(const char * const gossip) 
		{ 
			cout << "[Gossip: " << gossip << " ]" << endl;
		}

		/**
		 * This is called for each AIML 
		 * category that is loaded into 
		 * memory.  
		 *
		 * Loadtime occurs whenver the call 
		 * GraphBuilder::createGraph() is made.
		 * For every 5000 categories loaded into
		 * Rebecca's internal data structure 
		 * this prints a output message about it.
		 */
		void categoryLoaded()
		{
			static int i = 0;
			const int numberOfCategories = 5000;
			
			/*
			 * Clever way to say if "i" is a multiple 
			 * of 5000 then print out the number of 
			 * categories loaded so far.
			 */
			if(++i % numberOfCategories == 0)
			{
				cout << "[" << i << " categories loaded]" << endl;
			}
		}

		/**
		 * Before each AIML file is parsed this method is called.
         *
		 * \param fileName The name of the file about to be parsed.
		 */
		void filePreLoad(const char *const fileName)
		{
			cout << "[Loading      " << fileName << "]" << endl;
		}
		
		/**
		 * After each AIML file is parsed, this method is called.
         *
		 * \param fileName The name of the file just parsed.
		 */
		void filePostLoad(const char *const fileName)
		{
			cout << "[Done loading " << fileName << "]" << endl;
		}

		/**
		 * When the "srai" AIML tag is called, the text 
		 * is sent to this method.
		 *
		 * Usually refered to as symbolic reduction, you 
		 * can see what text is being re-fed back into the 
		 * AIML GraphBuilder::getResponse() by AIML its self.
		 *
		 * \param symbol The text which is being sent back
		 * into GraphBuilder::getResponse().
		 */
		void symbolicReduction(const char *const symbol)
		{
			cout << "Symbolic reduction: " << symbol << endl;
		}

		/**
		 * A infinite symbolic reduction has occured and 
		 * has been terminated.
		 *
		 * This method is called when symbolic reduction ends
		 * up in a infinite loop and has been terminated.  This
		 * is just to alert you to the fact.
		 */
		void infiniteSymbolicReduction()
		{
			cout << "[Infinite Symbolic reduction detected]" << endl;
		}
		
		/**
		 * Sends you a message about a XMLParseError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseError(const char * const message) 
		{ 
			cout << message << endl;
		} 

		/**
		 * Sends you a message about a XMLParseWarning. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseWarning(const char * const message)
		{ 
			cout << message << endl;
		} 

		/**
		 * Sends you a message about a XMLParseFatalError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseFatalError(const char * const message) 
		{ 
			cout << message << endl;
		} 
		
		/**
		 * During runtime, the "thatStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatStarTagSizeExceeded() 
		{ 
			cout << "[Warning thatStar Tag Size Exceeded]" << endl;
		}
		
		/**
		 * During runtime, the "topicStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void topicStarTagSizeExceeded() 
		{ 
			cout << "[Warning topicStar Tag Size Exceeded]" << endl;		
		}

		/**
		 * During runtime, the "star" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void starTagSizeExceeded() 
		{ 
			cout << "[Warning star Tag Size Exceeded]" << endl;
		}

		/**
		 * A AIML "Input" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void inputTagNumericConversionError(const char * const message) 
		{ 
			cout << "inputTagNuermicConversionError:" << message << endl;		
		}

		/**
		 * During runtime, the "input" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void inputTagSizeExceeded() 
		{ 
			cout << "[Warning input Tag Size Exceeded]" << endl;
		} 

		/**
		 * A AIML "Star" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void starTagNumericConversionError(const char * const message) 
		{ 
			cout << "starTagNuermicConversionError:" << message << endl;				
		} 

		/**
		 * During runtime, the "that" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatTagSizeExceeded() 
		{ 
		
		}

		/**
		 * A AIML "That" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatTagNumericConversionError(const char * const message) 
		{ 
			cout << "thatTagNumericConversionError:" << message << endl;
		} 

		/**
		 * A AIML "TopicStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void topicStarTagNumericConversionError(const char * const message) 
		{ 
			cout << "topicStarTagNumericConversionError:" << message << endl;
		} 
		
		/**
		 * A AIML "thatStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatStarTagNumericConversionError(const char * const message) 
		{ 
			cout << "thatStarTagNumericConversionError" << message << endl;
		}
};


/**
 * Parses and sets the 
 * arguments for main().
 */
class Arguments
{
	public:
		
		/**
		 * Constructor that
		 * sets the arguments up
		 * from main() as well
		 * as the program name its
		 * self.
		 *
		 * \param argc The number of arguments
		 * sent in.
		 *
		 * \param args The array of arguments 
		 */
		Arguments(int argc, char* args[])
			: m_aimlSchemaPath("../../resources/schema/AIML.xsd"),
			  m_commonTypesSchemaPath("../resources/schema/common-types.xsd"),
			  m_botConfigurationSchemaPath("../resources/schema/bot-configuration.xsd"),
			  m_configurationDirectory("../../conf"),
			  m_aimlDirectory("../../aiml/annotated_alice"),
			  m_currentArgument(NO_ARG)
		{
			/*
			 * Iterate over the arguments
			 * and set them 
			 */
			for(int i = 1; i < argc; ++i)
			{
				//get string of the argument
				string argument(args[i]);
				
				if(m_currentArgument == NO_ARG)
				{
					if(argument == "-aimlSchema" || 
					   argument == "-as")
					{
						m_currentArgument = AIML_SCHEMA;					
					} 
					else if(argument == "-botSchema" ||
				            argument == "-bs")
					{
						m_currentArgument = BOT_SCHEMA;	
					}
					else if(argument == "-commonSchema" || 
						    argument == "-cs")
					{
						m_currentArgument = COMMON_SCHEMA;
					}
					else if(argument == "-configurationDirectory" || 
							argument == "-cd")
					{
						m_currentArgument = CONFIGURATION;
					}
					else if(argument == "-aimlDirectory" || 
						    argument == "-ad")
					{
						m_currentArgument = AIML;	
					}
					else if(argument == "-help" || 
						    argument == "-h" || 
							argument == "/?" ||
							argument == "--help")
					{
						/*
						 * Display help and exit
						 */
						printUsage();
						exit(0);
					}
					else
					{
						cout << 
							"[Illegal argument of " +
							string(args[i]) +
							" found]" 
							<< endl;
					}
				}
				else
				{
					/*
					 * We already encountered the switch, 
					 * now we just need to set the argument
					 */
					if(m_currentArgument == AIML)
					{
						m_aimlDirectory = argument;
					}
					else if(m_currentArgument == AIML_SCHEMA)
					{
						m_aimlSchemaPath = argument;
					}
					else if(m_currentArgument == BOT_SCHEMA)
					{
						m_botConfigurationSchemaPath = argument;
					}
					else if(m_currentArgument == COMMON_SCHEMA)
					{
						m_commonTypesSchemaPath = argument;
					}
					else if(m_currentArgument == CONFIGURATION)
					{
						m_configurationDirectory = argument;
					}
					else
					{
						cout << "Programmer error "
							    "this should not be reached"
							 << endl;
					}

					m_currentArgument = NO_ARG;
				}
			}
		}
		
		/**
		 * Returns the configuration
		 * directory that has been set.
		 *
		 * \return The configuration directory
		 * where needed configuration files 
		 * are stored.
		 */
		string getConfigurationDirectory() const
		{
			return m_configurationDirectory;
		}
		
		/**
		 * Returns the AIML
		 * directory that has been set.
		 *
		 * \return The AIML directory
		 * where aiml files are stored.
		 */
		string getAimlDirectory() const
		{
			return m_aimlDirectory;
		}

		/**
		 * Returns the AIML schema
		 * path that has been set.
		 *
		 * \return The AIML schema 
		 * path that has been set.
		 */
		string getAimlSchemaPath() const
		{
			return m_aimlSchemaPath;
		}

		/**
		 * Returns the common types 
		 * schema path that has been set.
		 *
		 * \return The common types 
		 * schema path that has been set.
		 */
		string getCommonTypesSchemaPath() const
		{
			return m_commonTypesSchemaPath;
		}

		/**
		 * Returns the bot configuration
		 * schema path that has been set.
		 *
		 * \return the bot configuration
		 * schema path that has been set.
		 */
		string getBotConfigurationSchemaPath() const
		{
			return m_botConfigurationSchemaPath;
		}
		
		/** 
		 * Enumeration of possible switches you
		 * can give rebecca
		 */
		enum arguments{ NO_ARG, AIML, AIML_SCHEMA, 
			            COMMON_SCHEMA, BOT_SCHEMA, 
						CONFIGURATION};
		/**
		 * The current argument state.
		 */
		arguments m_currentArgument;

		/**
		 * The location of RebeccaAIML's
		 * configuration directory.  
		 *
		 * If this is not set, it will default 
		 * to the current working directory
		 * + "../../conf".  This is where
		 * needed configuration files are
		 * stored.
		 */
		string m_configurationDirectory;
		
		/**
		 * The location of a AIML directory.
		 *
		 * If this is not set, it will default
		 * to the current working directory 
		 * + "../../aiml/annotated_alice".
		 */
		string m_aimlDirectory;
		
		/**
		 * The path to the aiml xsd file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../../resources/schema/AIML.xsd"
		 */
		string m_aimlSchemaPath;

		/**
		 * The path to the the common types
		 * schema file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../resources/schema/common-types.xsd"
		 */
		string m_commonTypesSchemaPath;
		
		/**
		 * The path to the bot configuration
		 * schema file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../resources/schema/bot-configuration.xsd"
		 */
		string m_botConfigurationSchemaPath;
};

/**
 * Console version to query a AIML set.
 * 
 * I use the annotated alice data set that's 
 * provided as an example.
 */
int main (int argc, char* args[]) 
{
	try
	{ 
		if(argc < 3)
		{   
			/*
			 * Incorrect number of arguments was given.
			 * Print usage and exit the program
			 */
			printUsage();
			exit(1);
		}
		//else
        /* 
         * We have arugments given, extract them
         */
        Arguments arguments(argc, args);

		/*
		 * This is responsible for memory management of 
		 * GraphBuilder.
		 */
		AimlFacade aiml;

		/*
		 * Get the GraphBuilder concrete class that 
		 * was created inside of AimlFacade.
		 * DO NOT try to delete GraphBuilder.  Let
		 * AimlFacade handle that when it falls out 
		 * of scope.
		 */
		GraphBuilder &builder = aiml.getGraphBuilder();

		/*
		 * Create an instantiation of our custom 
		 * callbacks we created above.
		 */
		consoleAIMLHtmlConverterCallBacks callback;

		/* Give the address to Rebecca for usesage.
		 * Rebecca DOES NOT delete it.  
		 */
		builder.setCallBacks(&callback);
		
		/*
		 * Add our custom Tag library that overrides all
		 * the AIML tags.  This library overrides and changes 
		 * the functionality to be the html converter.
		 */
		builder.addCustomTagLibrary("customHtmlTagLayer");

		cout << "[Rebecca loading]" << endl;

		/* 
		 * Set the schemas for the AIML XML (AIML.xsd)
		 * and for Rebecca's own configuration files.
		 * The schema's have to be relative to where the files
		 * you are going to parse are going to be at.
		 */
		builder.setAIMLSchema(arguments.getAimlSchemaPath().c_str());
		builder.setCommonTypesSchema(arguments.getCommonTypesSchemaPath().c_str());
		builder.setBotConfigurationSchema(arguments.getBotConfigurationSchemaPath().c_str());

		/* 
		 * Set that "yes" we do want to do XML validation on
		 * both the AIML XML and Rebecca's own configuration 
		 * files.
		 */
		builder.setAIMLValidation();
		builder.setBotConfigurationValidation();

		/*
		 * Parse Rebecca's configuration files to setup 
		 * Rebecca's ability to handle input subsitutions, 
		 * what a sentence splitter is, and what bot properties
		 * she should have.
		 */
		string substitutions_xml = arguments.getConfigurationDirectory() + "/substitutions.xml";
		builder.parseSubstitutionFile(substitutions_xml.c_str());
		
		string sentence_splitters_xml = arguments.getConfigurationDirectory() + "/sentence-splitters.xml";
		builder.parseSentenceSplitterFile(sentence_splitters_xml.c_str());
		
		string properties_xml = arguments.getConfigurationDirectory() + "/properties.xml";
		builder.parsePropertiesFile(properties_xml.c_str());
		
		/*
		 * Add the entire directory.  Every file that has the 
		 * extension ".aiml" will be added to the internal queue 
		 * for latter processing.
		 */
		builder.addDirectory(arguments.getAimlDirectory().c_str());

		/*
		 * No other files to add to the internal queue.  
		 * So, let's create the AIML graph, the internal 
		 * data structures.
		 */
		builder.createGraph();
	}
	/* 
	 * All the exceptions are grouped here but you 
	 * might not want this since it's a bit harder 
	 * to determine where they came from.
	 */
	catch(DirectoryNotFoundException &e)
	{
		cout << "[A Directory Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(FileNotFoundException &e)
	{
		cout << "[A File Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(IllegalArgumentException &e)
	{
		cout << "[IllegalArgument Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(InitializationException &e)
	{
		cout << "[Initialization Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(XMLErrorException &e)
	{
		cout << "[XMLError Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(Exception &e)
	{
		cout << "[An uknown exception occured, Terminating program]" << endl;
		cout << "[" << e.what() << "]";
		return 1;
	}

	//Everything smooth.  Exit normally.
	return 0;
}
