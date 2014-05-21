
//Rebecca includes
#include <rebecca/TestCasesHandler.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/Arguments.h>

//Xerces includes
#include <xercesc/parsers/SAXParser.hpp>
XERCES_CPP_NAMESPACE_USE;

//Boost includes
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "boost/filesystem/operations.hpp" // includes boost/filesystem/path.hpp
#include "boost/filesystem/fstream.hpp"    // ditto
#include "boost/filesystem/path.hpp"
using namespace boost;
using namespace boost::filesystem;

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

namespace rebecca
{
namespace impl
{

TestCasesHandler::TestCasesHandler(const String outputFileName, GraphBuilder &builder)
	: m_outputFileName(outputFileName), 
	  m_builder(builder)
{

   /*
    * Get a handle to our global instance
    * of our arguments
    */
    Arguments *arguments = Arguments::getInstance();
	m_output.open(m_outputFileName.c_str());
    path filePath(arguments->getResourcesDirectory() + "/testing/header.htm");
	boost::filesystem::ifstream inputFile(filePath);
	
	//Write the header
	string line;
	while (inputFile.is_open() && !inputFile.eof())
    {
      getline (inputFile,line);
	  output(line);
    }    
}

TestCasesHandler::~TestCasesHandler()
{
   /*
    * Get a handle to our global instance
    * of our arguments
    */
    Arguments *arguments = Arguments::getInstance();

	//Write the footer
    path filePath(arguments->getResourcesDirectory() + "/testing/footer.htm");
	boost::filesystem::ifstream inputFile(filePath);
	
	//Write the header
	string line;
	while (inputFile.is_open() && !inputFile.eof())
    {
      getline (inputFile,line);
	  output(line);
    }    
}


shared_ptr<Tag> TestCasesHandler::createTagClass(const String &className)
{
	if(className == "TestCase")
	{
		return shared_ptr<Tag>(new TestCase(*this));
	}
	else if(className == "Description")
	{
		return shared_ptr<Tag>(new Description(*this));
	}
	else if(className == "Input")
	{
		return shared_ptr<Tag>(new TestCaseInput(*this));
	}
	else if(className == "ExpectedAnswer")
	{
		return shared_ptr<Tag>(new ExpectedAnswer(*this));
	}
	else if(className == "ExpectedKeywords")
	{
		return shared_ptr<Tag>(new ExpectedKeyWords(*this));
	}
	else if(className == "TestSuite")
	{
		return shared_ptr<Tag>(new TestSuite(*this));
	}
	else
	{
		cout << "Unknown className of:" << className << endl;
		return shared_ptr<Tag>(new NoOps(*this));
	}


}
void TestCasesHandler::getResponse()
{
	String response = m_builder.getResponse(m_input.c_str()).c_str();
	outputln("Response:       " + response);
	
	if(!m_expectedAnswer.empty())
	{
		if(response == m_expectedAnswer)
		{
			outputln("<p style=\"color:green\">[OK]</p>");
		}
		else
		{
			outputln("<p style=\"color:red\">[FAILED]</p>");
		}
	}
	else if(!m_keyWords.empty())
	{
		typedef VectorString::const_iterator VCI;
		bool allFound = true;
		for(VCI it = m_keyWords.begin(); it != m_keyWords.end(); ++it)
		{
			typedef tokenizer<char_separator<char> > tokenize;
			typedef tokenizer<char_separator<char> >::const_iterator CI;

			char_separator<char> sep(",");
			tokenize keyWordsToken((*it), sep);
			bool oneFound = false;
			for(CI it = keyWordsToken.begin(); it != keyWordsToken.end(); ++it)
			{	
				String toLookFor = trim_copy(*it);
				if(find_first(response, toLookFor))
				{
					erase_first(response, toLookFor);
					oneFound = true;
					break;
				}
			}

			if(oneFound == false)
			{
				allFound = false;
			}
		}

		if(allFound)
		{
			outputln("<p style=\"color:green\">[OK]</p>");
		}
		else
		{
			outputln("<p style=\"color:red\">[FAILED]</p>");
		}
	}
	else
	{
		outputln("[No expected answer or keywords given, ERROR]");
	}

	outputln("");
}

void TestCasesHandler::startElement(const XMLCh* const name, AttributeList& attributes)
{
	Transcode attributeName;
	Transcode attributeType;
	Transcode attributeValue;
	Transcode message;

	try 
	{
		message.translate(name);		
		cout << "<" << message.getString() << ">" << endl;
		const String messageString(message.getChar());

		m_currentStartElement = createTagClass(messageString);
		m_tagStack.push(m_currentStartElement);
	}
	catch(nullString &)
	{

		//Do nothing	
		cout << "caught nullString on message.getChar()" << endl;
	}

	for(unsigned int i = 0; i < attributes.getLength(); i++)
	{
		try
		{
			attributeName.translate(attributes.getName(static_cast<unsigned int>(i)));
			cout << "Attribute name:" << attributeName.getString() << endl;

			attributeValue.translate(attributes.getValue(static_cast<unsigned int>(i)));
			cout << "Attribute Value:" + attributeValue.getString() << endl;
			m_currentStartElement->setAttribute(attributeName.getStringPimpl(), attributeValue.getStringPimpl());
		}
		catch(nullString &)
		{
			//Do nothing	
			cout << "caught nullString on attributeValue.getChar()" << endl;
		}
	}
}

void TestCasesHandler::characters(const XMLCh * const chars, 
                                  const XMLSize_t length)
{
	try
	{
		Transcode someChars(chars);
		m_currentStartElement->addCharacters(someChars.getStringPimpl());
	}
	catch(nullString &)
	{
		//Do nothing
		cout << "caught nullString on someChars.getChar()" << endl;
	}
}

void TestCasesHandler::endElement(const XMLCh *const name)
{

	/*
	 * Important note. No error handling needs to take place and match up end tags
	 * with the begining tags.
     *
	 * The reason is that the SAX parser is going to handle all the endElement
	 * Errors.
	 */

	try
	{
		Transcode element(name);
		cout << "</" << element.getString() << ">" << endl;
		const String messageString(element.getChar());

		if(!m_tagStack.empty())
		{
			shared_ptr<Tag> tag = m_tagStack.top();
			m_tagStack.pop();

			if(!m_tagStack.empty())
			{
				m_tagStack.top()->handleInnerTag(tag);
				m_currentStartElement = m_tagStack.top();
			}
			else
			{
				cout << "Tag stack empty, not doing anything" << endl;
			}
		}
		else
		{
			cout << "Internal programmer Error the stack is empty" << endl;
			throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::endElement(const XMLCh *const name)] the stack is empty)");
		}
	}	
	catch(nullString &)
	{
		//Do nothing
		cout << "caught nullString on someChars.getChar()" << endl;
	}
}

void TestCasesHandler::TestCase::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	String nameString(name.c_str());
	String valueString(value.c_str());
	if(nameString == "name")
	{
		m_handler.outputln("Test Case name: " + valueString);
	}
	else
	{
		cout << "Error, wrong attribute" << endl;
	}
}

void TestCasesHandler::Description::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	String characterString(characters.c_str());
	m_characters += trim_copy(characterString);
}

void TestCasesHandler::ExpectedAnswer::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	String characterString(characters.c_str());
	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	char_separator<char> sep("\n");
	tokenize expectedAnswerTokens(characterString, sep);

	if(expectedAnswerTokens.begin() != expectedAnswerTokens.end())
	{

		for(CI it = expectedAnswerTokens.begin(); it != expectedAnswerTokens.end(); ++it)
		{		
			m_characters += " " + trim_copy(*it);
		}	
	}
	else
	{
		m_characters += trim_copy(characterString);
	}
}

void TestCasesHandler::TestCaseInput::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	String characterString(characters.c_str());
	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	char_separator<char> sep("\n");
	tokenize expectedAnswerTokens(characterString, sep);

	if(expectedAnswerTokens.begin() != expectedAnswerTokens.end())
	{

		for(CI it = expectedAnswerTokens.begin(); it != expectedAnswerTokens.end(); ++it)
		{		
			m_characters += " " + trim_copy(*it);
		}	
	}
	else
	{
		m_characters += trim_copy(characterString);
	}
}

void TestCasesHandler::ExpectedKeyWords::addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &)
{
	String characterString(characters.c_str());
	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	char_separator<char> sep("\n");
	tokenize expectedAnswerTokens(characterString, sep);

	if(expectedAnswerTokens.begin() != expectedAnswerTokens.end())
	{

		for(CI it = expectedAnswerTokens.begin(); it != expectedAnswerTokens.end(); ++it)
		{		
			m_characters += " " + trim_copy(*it);
		}	
	}
	else
	{
		m_characters += trim_copy(characterString);
	}

}

} // end of impl namespace
} // end of rebecca namespace
