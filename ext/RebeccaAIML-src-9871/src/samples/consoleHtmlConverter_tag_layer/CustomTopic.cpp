//Rebecca includes
#include <rebecca/framework/Category.h>

//Custom tag includes
#include "CustomTopic.h"
#include "Links.h"
#include "Html.h"
#include "HtmlConverterInternalProgrammerErrorException.h"

//Boost includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

//std includes
#include <sstream>

namespace customTag
{
namespace impl
{

/*
 * Initialize the default topic to "*".
 * The default topic in AIML XML is always a "*"
 */
CustomTopic::CustomTopic(GraphBuilderFramework &builder, Html &htmlPage)
	throw(InternalProgrammerErrorException &)
	: Topic(builder), m_topic("*"), 
	  m_builder(builder), 
	  m_htmlPage(htmlPage)
{ 
	/*
	 * Add the name of this class.  Otherwise if I 
	 * didn't do this I could not call Tag::instanceOf("CustomTopic")
	 * on a CustomTopic object and get a true back.
	 */
	addInstanceOf("CustomTopic");
} 

void CustomTopic::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	/*
	 * Check if the tag object inherits from the
	 * Category class 
	 */
	if(tag->instanceOf("Category"))
	{
		/*
		 * Create a tokenizer type for char's and a 
		 * const iterator type to that tokenizer
		 */
		typedef tokenizer<char_separator<char> > tokenize;
		typedef tokenizer<char_separator<char> >::const_iterator CI;

		/*
		 * Downcast the tag to the category it is.
		 * Get the pattern string from it.
		 * Erase all newline characters if any from the
		 * string.
		 */
		shared_ptr<Category> category = static_pointer_cast<Category>(tag);
		const StringPimpl &patternString = category->getPatternString();
		string patternTokenString(patternString.c_str());
		erase_all(patternTokenString, "\n");

		/*
		 * Break up the pattern string into individual words.
		 */
		char_separator<char> seperator(" ");
		tokenize tokens(patternTokenString, seperator);
		tokens.assign(patternTokenString);

		/*
		 * leftNode is the word on the left side of "->" 
		 * when writing the webpages out.  For example, 
		 * [root] is the first web page and will be the
		 * left node when making the second web page when
		 * the second web page has the title string
		 * of "[root]->blah"
		 */
		string leftNode = "[root]";
		string savedString = leftNode;
		
		/*
		 * Iterate over the invidivual words of the 
		 * pattern string.  Create the web page and 
		 * its links to the words of the pattern string.
		 */
		for(CI it = tokens.begin(); it != tokens.end(); ++it)
		{
			string tokName = *it;
			savedString += " " + tokName;
			m_htmlPage.createLink(savedString, tokName, leftNode);		
			leftNode = savedString;			
		}
		
		/*
		 * Get the "that" string.  Create the link to the 
		 * that words.  Remove all newline characters
		 * from the "that" string. Break up the "that" string 
		 * into invidiual words.  
		 */
		const StringPimpl &thatString = category->getThatString();
		savedString += string(" ") + "[that]";
		m_htmlPage.createLink(savedString, "[that]", leftNode);
		leftNode = savedString;
		string thatTokenString(thatString.c_str());
		erase_all(thatTokenString, "\n");
		tokens.assign(thatTokenString);			
		
		/*
		 * Iterate over the invidivual words of the 
		 * "that" string.  Create the web page and 
		 * its links to the words of the pattern string.
		 */
		for(CI it = tokens.begin(); it != tokens.end(); ++it)
		{
			string tokName = *it;
			savedString += " " + tokName;
			m_htmlPage.createLink(savedString, tokName, leftNode);
			leftNode = savedString;			
		}
		
		/*
		 * Create a link to the topic words.  Break up the 
		 * topic string into invidiual words.  
		 */
		savedString += string(" ") + "[topic]";
		m_htmlPage.createLink(savedString, "[topic]", leftNode);
		leftNode = savedString;
		tokens.assign(m_topic);
		
		/*
		 * Iterate over the invidivual words of the 
		 * topic string.  Create the web page and 
		 * its links to the words of the pattern string.
		 *
		 * However, when the last topic string is encountered
		 * we have to create a template string and store that 
		 * on the final web page.  So a general for loop will
		 * not work here.  Instead we use a look ahead token
		 * to find the last web page.
		 */
		CI itLookAhead = tokens.begin();
		if(itLookAhead != tokens.end())
		{
			++itLookAhead;
		}
		
		string tokName;
		for(CI it = tokens.begin(); it != tokens.end(); ++it)
		{
			tokName = *it;
			savedString += " " + tokName;
			m_htmlPage.createLink(savedString, tokName, leftNode);
			leftNode = savedString;			
		}
		
		/*
		 * Store the template string for the final link
		 */
		const StringPimpl templateString = category->getTemplateString();
		m_htmlPage.createTemplateLink("nowhere", templateString.c_str(), leftNode);

	}
	else if(tag->instanceOf("Topic"))
	{
		/*
		 * We have encountered another topic tag.  Just ignore it, it's not fatal.
		 */
	}
	else
	{   
		/*
		 * Invalid Tag object, shut down the AIML engine
		 */
		throw HtmlConverterProgrammerErrorException("Internal programmer error."
			                                        "Bad cast, this is not a Category or Topic");
	}
}

void CustomTopic::setAttribute(const StringPimpl &name, const StringPimpl &value) 
	throw(InternalProgrammerErrorException &)
{
	/*
	 * Put the name and value
	 * into easier to use strings
	 */
	string nameString(name.c_str());
	string valueString(value.c_str());

	if(nameString == "name")
	{
		/*
		 * Store the value of the name attribute
		 */
		m_topic = valueString;
	}
	else
	{
		/*
		 * Invalid attribute and invalid CustomTopic.  Shut down the AIML engine.
		 */
		throw HtmlConverterProgrammerErrorException("Invalid setAttribute on CustomTopic::setAttribute()");
	}
}

} //end of namespace impl
} //end namespace customTag

