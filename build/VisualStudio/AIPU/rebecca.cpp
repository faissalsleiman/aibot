#include "AIPUArguments.h"
#include "rebecca.h"

/**
* Call this function to initialize the GraphBuilder with AIML files
* indicated in arguments.
*/
void rebecca_init(RebeccaArguments &arguments, GraphBuilder &builder)
{
	try
	{

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

		/*
		* Get the number of AIML categories loaded in total.
		*/
		int size = builder.getSize();

		//Print out the number of categories loaded.
		cout << endl << endl;
		cout << "[Rebecca now fully loaded]" << endl;
		cout << "[Number of categories loaded: " << size << "]" << endl;
		cout << "[Type /exit to exit]" << endl << endl << endl;
	}
	/*
	* All the exceptions are grouped here but you
	* might not want this since it's a bit harder
	* to determine where they came from.
	*/
	catch (DirectoryNotFoundException &e)
	{
		cout << "[A Directory Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		exit(1);
	}
	catch (FileNotFoundException &e)
	{
		cout << "[A File Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		exit(1);
	}
	catch (IllegalArgumentException &e)
	{
		cout << "[IllegalArgument Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		exit(1);
	}
	catch (InitializationException &e)
	{
		cout << "[Initialization Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		exit(1);
	}
	catch (XMLErrorException &e)
	{
		cout << "[XMLError Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		exit(1);
	}
	catch (Exception &e)
	{
		cout << "[An uknown exception occured, Terminating program]" << endl;
		cout << "[" << e.what() << "]";
		exit(1);
	}
}