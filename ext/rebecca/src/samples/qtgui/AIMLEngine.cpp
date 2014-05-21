
//qtgui includes
#include "AIMLEngine.h"
#include "Arguments.h"

//Qt includes
#include <QDir>

namespace qtgui
{

void AIMLEngine::userInput(const QString &text)
{
	/*
	 * Check the AIML engine is loaded and 
	 * that the user actually entered 
	 * something
	 */
	if((!text.isEmpty()) && m_aiml)
	{

       /*
		* Get the GraphBuilder concrete class that 
		* was created inside of AimlFacade.
		* DO NOT try to delete GraphBuilder.  Let
		* AimlFacade handle that when it falls out 
		* of scope.
		*/
		GraphBuilder &builder = m_aiml->getGraphBuilder();
		
		/*
		 * Emit the internal bot information.  Get
		 * the bot response and emit all of that 
		 * information to anyone wishing to display
		 * it.
		 */
		emit addText("");
		emit addText("");
		emit addText("Internal information:");
		emit addText("=====================");
		
		//construct the match line and emit it.
		QString matchLine = text + " : " + builder.getThat().c_str() + 
			                QString(" : ") + builder.getTopic().c_str();
		emit addText(matchLine);
		
		//Get the bot response
		StringPimpl response = builder.getResponse(text.toAscii().data());

		emit addText("=====================");
		emit addText("");

		//emit the bot response
		emit addBotText(response.c_str());
	}
}

void AIMLEngine::clearAIML()
{
	/*
	 * Emit to anyone wanting to know that we're
	 * going to be a while loading something
	 */
	emit loading();
	emit addText("[Please wait for a second while AIML unloads]");
	emit addText("[You cannot load AIML until this session is unloaded]");

	delete m_aiml;
	m_aiml = 0;

	emit addText("[AIML done unloading]");
	emit addText("[No bot is loaded]");
	emit addText("[Use the file Menu to add a bot]");

	/*
	 * Emit to anyone wanting to know that we're
	 * done loading 
	 */
	emit doneLoading();
}


void AIMLEngine::addDirectory(const QString &directoryName)
{
	/*
	 * Emit to anyone wanting to know that we're
	 * going to be a while loading something
	 */
	emit loading();
	emit addText("[Rebecca loading]");

	try
	{
		/*
		 * Create and Load a AIML engine 
		 * if we don't have one.
		 */
		if(!m_aiml)
		{
			initAIML();
		}

	   /*
		* Get the GraphBuilder concrete class that 
		* was created inside of AimlFacade.
		* DO NOT try to delete GraphBuilder.  Let
		* AimlFacade handle that when it falls out 
		* of scope.
		*/
		GraphBuilder &builder = m_aiml->getGraphBuilder();

		/*
		 * Add the entire directory by extracting the
		 * "char *" from the QString and passing it to
		 * the AIML api
		 */
		builder.addDirectory(directoryName.toAscii().data());

       /*
		* No other files to add to the internal queue.  
		* So, let's create the AIML graph, the internal 
		* data structures.
		*/
		builder.createGraph();

       /*
		* Get the number of AIML categories loaded in total.
		*/
		int size = builder.getSize();

		//Print out the number of categories loaded.
		emit addText("[Rebecca now fully loaded]");
		QString stringSize;
		stringSize.setNum(size);
		QString outputCategoriesLoaded("[Number of categories loaded: " + stringSize + "]");
		emit addText(outputCategoriesLoaded);

	   /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
		emit doneLoading();
	}
   /* 
	* All the exceptions are grouped here but you 
	* might not want this since it's a bit harder 
	* to determine where they came from.
	*/
	catch(FileNotFoundException &e)
	{
		emit addText("[A File Was Not Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(IllegalArgumentException &e)
	{
		emit addText("[IllegalArgument Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(InitializationException &e)
	{
		emit addText("[Initialization Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(XMLErrorException &e)
	{
		emit addText("[XMLError Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(Exception &e)
	{
		emit addText("[An uknown exception occured, Terminating program]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}

}


void AIMLEngine::addFile(const QString &fileName)
{
	/*
	 * Emit to anyone wanting to know that we're
	 * going to be a while loading something
	 */
	emit loading();
	emit addText("[Rebecca loading]");

	try
	{
		/*
		 * Create and Load a AIML engine 
		 * if we don't have one.
		 */
		if(!m_aiml)
		{
			initAIML();
		}

	   /*
		* Get the GraphBuilder concrete class that 
		* was created inside of AimlFacade.
		* DO NOT try to delete GraphBuilder.  Let
		* AimlFacade handle that when it falls out 
		* of scope.
		*/
		GraphBuilder &builder = m_aiml->getGraphBuilder();

		/*
		 * Add the file by extracting the
		 * "char *" from the QString and passing it to
		 * the AIML api
		 */
		builder.addFile(fileName.toAscii().data());

       /*
		* No other files to add to the internal queue.  
		* So, let's create the AIML graph, the internal 
		* data structures.
		*/
		builder.createGraph();

       /*
		* Get the number of AIML categories loaded in total.
		*/
		int size = builder.getSize();

		//Print out the number of categories loaded.
		emit addText("[Rebecca now fully loaded]");
		QString stringSize;
		stringSize.setNum(size);
		QString outputCategoriesLoaded("[Number of categories loaded: " + stringSize + "]");
		emit addText(outputCategoriesLoaded);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
   /* 
	* All the exceptions are grouped here but you 
	* might not want this since it's a bit harder 
	* to determine where they came from.
	*/
	catch(FileNotFoundException &e)
	{
		emit addText("[A File Was Not Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(IllegalArgumentException &e)
	{
		emit addText("[IllegalArgument Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(InitializationException &e)
	{
		emit addText("[Initialization Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(XMLErrorException &e)
	{
		emit addText("[XMLError Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}
	catch(Exception &e)
	{
		emit addText("[An uknown exception occured, Terminating program]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);

       /*
		* Emit to anyone wanting to know that we're
		* done loading 
		*/
        emit doneLoading();
	}

}

void AIMLEngine::initAIML()
{
	try
	{
		//Create a new AIML engine 
		m_aiml = new AimlFacade;

	   /*
		* Get the GraphBuilder concrete class that 
		* was created inside of AimlFacade.
		* DO NOT try to delete GraphBuilder.  Let
		* AimlFacade handle that when it falls out 
		* of scope.
		*/
		GraphBuilder &builder = m_aiml->getGraphBuilder();

	   /*
        * Give the address to Rebecca for usesage.
		* Rebecca DOES NOT delete it.  
		*/
		builder.setCallBacks(&m_callback);

	   /*
		* Get a handle to our global instance
		* of our arguments
		*/
		Arguments *arguments = Arguments::getInstance();

	   /* 
		* Set the schemas for the AIML XML (AIML.xsd)
		* and for Rebecca's own configuration files.
		* The schema's have to be relative to where the files
		* you are going to parse are going to be at.
		*/
		builder.setAIMLSchema(arguments->getAimlSchemaPath().c_str());
		builder.setCommonTypesSchema(arguments->getCommonTypesSchemaPath().c_str());
		builder.setBotConfigurationSchema(arguments->getBotConfigurationSchemaPath().c_str());

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
		string substitutions_xml = arguments->getConfigurationDirectory() + "/substitutions.xml";
		builder.parseSubstitutionFile(substitutions_xml.c_str());
		
		string sentence_splitters_xml = arguments->getConfigurationDirectory() + "/sentence-splitters.xml";
		builder.parseSentenceSplitterFile(sentence_splitters_xml.c_str());
		
		string properties_xml = arguments->getConfigurationDirectory() + "/properties.xml";
		builder.parsePropertiesFile(properties_xml.c_str());

		/*
		 * Get the botName which should be Rebecca since that is 
		 * the name give in the configuration file properties.xml
		 * which we parsed above.
		 */
		string botName = builder.getBotPredicate("name").c_str();
		
		//Emit what the bot name is
		emit addBotName(botName.c_str());
	}
   /* 
	* All the exceptions are grouped here but you 
	* might not want this since it's a bit harder 
	* to determine where they came from.
	*/
	catch(DirectoryNotFoundException &e)
	{
		emit addText("[A Directory Was Not Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
	catch(FileNotFoundException &e)
	{
		emit addText("[A File Was Not Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
	catch(IllegalArgumentException &e)
	{
		emit addText("[IllegalArgument Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
	catch(InitializationException &e)
	{
		emit addText("[Initialization Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
	catch(XMLErrorException &e)
	{
		emit addText("[XMLError Exception Found Terminating]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
	catch(Exception &e)
	{
		emit addText("[An uknown exception occured, Terminating program]");
		QString exception("[");
		exception += e.what();
		exception += "]";
		emit addText(exception);
	}
}


} //end of qtgui namespace 
