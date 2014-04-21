//Rebecca includes
#include <rebecca/TestCases.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/all.h>
#include <rebecca/TestCasesHandler.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/Arguments.h>
#include <iostream>
using namespace std;

//Boost includes
#include <boost/filesystem/operations.hpp>
using namespace boost::filesystem;

namespace rebecca
{
namespace impl
{



TestCases::TestCases(const String &outputFile)
: m_testValidation(false),
  m_outputFile(outputFile),
  m_testFileAdded(false),
  m_aimlFileAdded(false),
  m_aimlGraphCreated(false),
  m_builder(m_aimlFacade.getGraphBuilder())
{

   /* Give the address to Rebecca for usesage.
	* Rebecca DOES NOT delete it.  
	*/
	m_builder.setCallBacks(&m_callback);

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
    m_builder.setAIMLSchema(arguments->getAimlSchemaPath().c_str());
    m_builder.setCommonTypesSchema(arguments->getCommonTypesSchemaPath().c_str());
    m_builder.setBotConfigurationSchema(arguments->getBotConfigurationSchemaPath().c_str());

   /* 
	* Set that "yes" we do want to do XML validation on
	* both the AIML XML and Rebecca's own configuration 
	* files.
	*/
	m_builder.setAIMLValidation();
	m_builder.setBotConfigurationValidation();

   /*
	* Parse Rebecca's configuration files to setup 
	* Rebecca's ability to handle input subsitutions, 
	* what a sentence splitter is, and what bot properties
	* she should have.
	*/
    string substitutions_xml = arguments->getConfigurationDirectory() + "/substitutions.xml";
    m_builder.parseSubstitutionFile(substitutions_xml.c_str());

    string sentence_splitters_xml = arguments->getConfigurationDirectory() + "/sentence-splitters.xml";
    m_builder.parseSentenceSplitterFile(sentence_splitters_xml.c_str());

    string properties_xml = arguments->getConfigurationDirectory() + "/properties.xml";
    m_builder.parsePropertiesFile(properties_xml.c_str());

	m_testParser.reset(new SAXParser);
	m_testDocumentHandler.reset(new TestCasesHandler(m_outputFile, m_builder));
	
///@todo make this into its own error class
//	m_testErrorHandler.reset(new TestCasesHandler(m_outputFile, m_builder));
//	m_testParser->setErrorHandler(m_testErrorHandler.get());

	m_testParser->setDocumentHandler(m_testDocumentHandler.get());
}

void TestCases::setTestSchema(const String &schemaFile)
{
	m_testSchema = schemaFile;	
}

void TestCases::setTestValidation(bool trueOrFalse)
{
	m_testValidation = trueOrFalse;
}

void TestCases::addTestFile(const String &testFile)
{
	if(!exists(testFile))
	{
		cout << "USER ERROR, is not a file" << endl;
		String fileNotFoundMsg("File:" + testFile + " was not found");
		throw FileNotFoundExceptionImpl(fileNotFoundMsg.c_str());
	}
	else
	{
		m_filesGraphed.insert(pair<String, bool>(testFile, false));
		m_testFileAdded = true;
	}
}

void TestCases::addAimlFile(const String &aimlFile)
{
	m_builder.addFile(aimlFile.c_str());
	m_aimlFileAdded = true;
}

void TestCases::addAimlDirectory(const String &aimlDirectory)
{
	m_builder.addDirectory(aimlDirectory.c_str());
	m_aimlFileAdded = true;
}

void TestCases::createAimlGraph()
{
	m_builder.createGraph();
	m_aimlGraphCreated = true;
}

void TestCases::conductTesting()
{
	if(m_testFileAdded && m_aimlFileAdded && m_aimlGraphCreated)
	{
		try 
		{
			if(m_testValidation && (!m_testSchema.empty()))
			{
				String SchemaLoc = "http://alicebot.org/2001/AIML-1.0.1 " + m_testSchema;

				m_testParser->setDoSchema(true);
				m_testParser->setDoValidation(true);    // optional.
				m_testParser->setDoNamespaces(true);    // optional
				m_testParser->setExternalSchemaLocation(SchemaLoc.c_str());
			}
			else
			{
				m_testParser->setDoSchema(false);
				m_testParser->setDoValidation(false);    // optional.
				m_testParser->setDoNamespaces(false);    // optional
			}

			typedef MapStringBool::iterator I;

			for(I i = m_filesGraphed.begin(); i != m_filesGraphed.end(); ++i)
			{
				if(i->second == false)
				{
					cout << i->first << " has not been added to graph yet"; 
					m_testParser->parse((i->first).c_str());
					i->second = true;
				}
				else
				{	//Do nothing
					cout << i->first << " has been added to the graph already";
					cout << "Just returning, without doing anything";
				}
			}
		}
		catch (const XMLException& toCatch) 
		{
			Transcode message(toCatch.getMessage());
			String msg("XMLException: " + message.getString());
			cout << msg << endl;
			throw ExceptionImpl(msg.c_str());
		}
		catch (const SAXParseException& toCatch) 
		{
			Transcode message(toCatch.getMessage());
			String msg("SAXParseException: " + message.getString());
			cout << msg << endl;
			throw ExceptionImpl(msg.c_str());
		}
		
	}
	else
	{
		throw ExceptionImpl("You need to add a test file, at least one aiml File,"
			                " and create the aiml graph");
	}

}

TestCases::~TestCases()
{

}


} //end of impl namespace
} //end of rebecca namespace 
