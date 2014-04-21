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

//Stl includes
#include <iostream>
using namespace std;

//Xerces includes
#include <xercesc/parsers/SAXParser.hpp>
XERCES_CPP_NAMESPACE_USE;

//Rebecca includes
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/GraphBuilderInternal.h>
#include <rebecca/impl/GraphHandler.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/framework/Category.h>
#include <rebecca/framework/Topic.h>
#include <rebecca/framework/AIML.h>
#include <rebecca/framework/Tag.h>
#include <rebecca/framework/Pattern.h>
#include <rebecca/framework/PatternSideThat.h>
#include <rebecca/framework/TemplateSideThat.h>
#include <rebecca/framework/Srai.h>
#include <rebecca/framework/Star.h>
#include <rebecca/framework/Set.h>
#include <rebecca/framework/Get.h>
#include <rebecca/framework/Think.h>
#include <rebecca/framework/PlainWord.h>
#include <rebecca/framework/Random.h>
#include <rebecca/framework/Li.h>
#include <rebecca/framework/Condition.h>
#include <rebecca/framework/NonImplemented.h>
#include <rebecca/framework/Input.h>
#include <rebecca/framework/ThatStar.h>
#include <rebecca/framework/TopicStar.h>
#include <rebecca/framework/Person.h>
#include <rebecca/framework/Person2.h>
#include <rebecca/framework/Gender.h>
#include <rebecca/framework/Formal.h>
#include <rebecca/framework/UpperCase.h>
#include <rebecca/framework/LowerCase.h>
#include <rebecca/framework/Sentence.h>
#include <rebecca/framework/Bot.h>
#include <rebecca/framework/Date.h>
#include <rebecca/framework/Id.h>
#include <rebecca/framework/Size.h>
#include <rebecca/framework/Version.h>
#include <rebecca/framework/System.h>
#include <rebecca/framework/Gossip.h>
#include <rebecca/framework/CustomTags.h>
#include <rebecca/framework/Learn.h>
using namespace rebecca::impl::utils;

namespace rebecca
{
namespace impl
{

void GraphHandler::endDocument()
{
	LOG_BOT_METHOD("void GraphHandler::endDocument()");
}

GraphHandler::GraphHandler(NodeMapper &root, GraphBuilderInternal &builder) 
	: m_rootNodeMapper(root),
	  m_builder(builder),
	  m_size(0)
{
	LOG_BOT_METHOD("GraphHandler::GraphHandler()");

/* Commented out.  Not fast enough to justify use	
	init();
*/
}




shared_ptr<Tag> GraphHandler::createTagClass(const String &className) 
{


		///@todo put this into the adt
	map<String, CustomTagWithDelete> &customTags = m_builder.getCustomTagsMapRef();
	typedef map<String, CustomTagWithDelete>::iterator I;

	for(I it = customTags.begin(); it != customTags.end(); ++it)
	{
		shared_ptr<Tag> tag = (it->second).m_customTags->createTagClass(className.c_str(), m_builder);
		if(tag.get() != 0)
		{
			return tag;
		}
	}

	if(className == "category") //1
	{
		m_templateSideThat = false;
		++m_size;
		m_builder.setSize(m_size);
		return shared_ptr<Tag>(new Category(m_builder));
	}
	else if(className == "pattern") //2
	{
		return shared_ptr<Tag>(new Pattern);
	}
	else if(className == "template") //3
	{
		m_templateSideThat = true;
		return shared_ptr<Tag>(new Template);
	}
	else if(className == "topic") //4
	{
		return shared_ptr<Tag>(new Topic(m_builder));
	}
	else if(className == "srai") //5
	{
		return shared_ptr<Tag>(new Srai(m_builder));
	}
	else if(className == "that") //6
	{
		if(m_templateSideThat)
		{
			return shared_ptr<Tag>(new TemplateSideThat(m_builder));
		}
		else 
		{
			return shared_ptr<Tag>(new PatternSideThat(m_builder));
		}
	}
	else if(className == "star") //7
	{
		return shared_ptr<Tag>(new Star(m_builder));
	}
	else if(className == "set") //8
	{
		return shared_ptr<Tag>(new Set(m_builder));
	}
	else if(className == "get") //9
	{
		return shared_ptr<Tag>(new Get(m_builder));
	}
	else if(className == "think") //10
	{
		return shared_ptr<Tag>(new Think);
	}
	else if(className == "person") //11
	{
		return shared_ptr<Tag>(new Person(m_builder));
	}
	else if(className == "bot") //12
	{
		return shared_ptr<Tag>(new Bot(m_builder));
	}
	else if(className == "condition") //13
	{
		return shared_ptr<Tag>(new Condition(m_builder));
	}
	else if(className == "li") //14
	{
		return shared_ptr<Tag>(new Li); 
	} 
	else if(className == "random") //15
	{
		return shared_ptr<Tag>(new Random);
	}
	else if(className == "sr") //16
	{
		shared_ptr<Tag> nonImplemented(new NonImplemented);
		shared_ptr<Tag> srai(new Srai(m_builder));
		shared_ptr<Tag> star(new Star(m_builder));
		srai->handleInnerTag(star);
		nonImplemented->handleInnerTag(srai);
		return nonImplemented;
	}
	else if(className == "input") //17
	{
		return shared_ptr<Input>(new Input(m_builder));
	}
	else if(className == "thatstar") //18
	{
		return shared_ptr<ThatStar>(new ThatStar(m_builder));
	}
	else if(className == "topicstar") //19
	{
		return shared_ptr<TopicStar>(new TopicStar(m_builder));
	}
	else if(className == "person2") //20
	{
		return shared_ptr<Tag>(new Person2(m_builder));
	}
	else if(className == "gender") //21
	{
		return shared_ptr<Tag>(new Gender(m_builder));
	}
	else if(className == "lowercase") //22
	{
		return shared_ptr<Tag>(new LowerCase);
	}
	else if(className == "uppercase") //23
	{
		return shared_ptr<Tag>(new UpperCase);
	}
	else if(className == "sentence") //24
	{
		return shared_ptr<Tag>(new Sentence);
	}
	else if(className == "formal") //25
	{
		return shared_ptr<Tag>(new Formal);
	}
	else if(className == "date") //26
	{
		return shared_ptr<Tag>(new Date);
	}
	else if(className == "id") //27
	{
		return shared_ptr<Tag>(new Id(m_builder));
	}
	else if(className == "size") //28
	{
		return shared_ptr<Tag>(new Size(m_builder));
	}
	else if(className == "version") //29
	{
		return shared_ptr<Tag>(new Version(m_builder));
	}
	else if(className == "system") //30
	{
		return shared_ptr<Tag>(new System);
	}
	else if(className == "gossip") //31
	{
		return shared_ptr<Tag>(new Gossip(m_builder));
	}
	else if(className == "aiml") //32
	{
		return shared_ptr<Tag>(new AIML(m_builder));
	}
	else if(className == "learn") //33
	{
		return shared_ptr<Tag>(new Learn(m_builder));
	}
	else
	{
		//This tag is not implemented.  More than likely a
		//bogus tag such as HTML:(something).  Just return
		//a non implemented tag that just takes the text 
		//inbetween and returns it.  This way if you have a 
		//tag such as <html:em>some text<html:em>  the 
		//unimplemented tag will return "some text"
		logging("Unimplemeneted tag found.  Name is:" + className);
		return shared_ptr<Tag>(new PlainWord);
	}
}



void GraphHandler::characters(const XMLCh * const chars, 
                              const unsigned int length)
{
	LOG_BOT_METHOD("void GraphHandler::characters(const XMLCh * const chars,"
		                                         "const unsigned int length)");
	try
	{
		Transcode someChars(chars);
		m_currentStartElement->addCharacters(someChars.getStringPimpl());
	}
	catch(nullString &)
	{
		//Do nothing
		logging("caught nullString on someChars.getChar()");
	}
}


void GraphHandler::startElement(const XMLCh* const name, AttributeList& attributes)
{
	LOG_BOT_METHOD("void GraphHandler::startElement(const XMLCh* const name, AttributeList& attributes)");
	
	Transcode attributeName;
	Transcode attributeType;
	Transcode attributeValue;
	Transcode message;
	
	try 
	{
		message.translate(name);		
		logging("<" + message.getString() + ">");
		const String messageString(message.getChar());

		m_currentStartElement = createTagClass(messageString);
		m_tagStack.push(m_currentStartElement);
	}
	catch(nullString &)
	{
		//Do nothing	
		logging("caught nullString on message.getChar()");
	}

	for(unsigned int i = 0; i < attributes.getLength(); i++)
	{
		try
		{
			attributeName.translate(attributes.getName(static_cast<unsigned int>(i)));
			logging("Attribute name:" + attributeName.getString()); 

			attributeValue.translate(attributes.getValue(static_cast<unsigned int>(i)));
			logging("Attribute Value:" + attributeValue.getString());
			m_currentStartElement->setAttribute(attributeName.getStringPimpl(), attributeValue.getStringPimpl());
		}
		catch(nullString &)
		{
			//Do nothing	
			logging("caught nullString on attributeValue.getChar()");
		}
	}
}

void GraphHandler::endElement(const XMLCh *const name)
{
	LOG_BOT_METHOD("void GraphHandler::endElement(const XMLCh *const name)");

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
		logging("</" + element.getString() + ">");
		const String messageString(element.getChar());

		if(m_tagStack.empty())
		{
			logging("Internal programmer Error the stack is empty");
			InternalProgrammerErrorExceptionImpl("[void GraphHandler::endElement(const XMLCh *const name)], Stack is empty");
		}

		shared_ptr<Tag> tag = m_tagStack.top();
		m_tagStack.pop();

		if(!m_tagStack.empty())
		{
			m_tagStack.top()->handleInnerTag(tag);
			m_currentStartElement = m_tagStack.top();
		}
		else
		{
			logging("Tag stack empty, not doing anything");
		}
	}
	catch(nullString &)
	{
		//Do nothing
		logging("caught nullString on someChars.getChar()");
	}
}

///@todo put this somewhere else or just remove this.
void GraphHandler::setAIMLVersion(const String &version)
{
	LOG_BOT_METHOD("void GraphHandler::setAIMLVersion(const String &version)");

	m_aimlVersion = version;

	if(version == "1.0")
	{
		logging("Version of AIML is 1.0");
		m_aimlVersion = "1.0";
	}
	else if(version == "1.0.1")
	{
		logging("Version of AIML is 1.0.1");
		m_aimlVersion = "1.0.1";
	}
	else
	{
		logging("Error, unsupported version of aiml");
		String msg("Unsupported version of aiml.  You are trying to use version:" + version);
		throw ExceptionImpl(msg.c_str());
	}

}

String GraphHandler::getAIMLVersion()
{
	return m_aimlVersion;
}
/* Commented out.  Not fast enough to justify use
shared_ptr<Tag> GraphHandler::createTagClassFromMap(const String &className) 
{
	typedef map<String, createTagMethod>::iterator I;
	I it = m_tagLookup.find(className);
	if(it != m_tagLookup.end())
	{
		logging("Returning the className of:" + className);
		return (*this.*(it->second))();
	}
	else 
	{
		//This tag is not implemented.  More than likely a
		//bogus tag such as HTML:(something).  Just return
		//a non implemented tag that just takes the text 
		//inbetween and returns it.  This way if you have a 
		//tag such as <html:em>some text<html:em>  the 
		//unimplemented tag will return "some text"
		logging("Unimplemeneted tag found.  Name is:" + className);
		return shared_ptr<Tag>(new PlainWord);
	}
}

void GraphHandler::init()
{
	m_tagLookup.insert(pair<String, createTagMethod>("category", &GraphHandler::createCategoryTag)); //1
	m_tagLookup.insert(pair<String, createTagMethod>("pattern", &GraphHandler::createPatternTag)); //2
	m_tagLookup.insert(pair<String, createTagMethod>("template", &GraphHandler::createTemplateTag)); //3
	m_tagLookup.insert(pair<String, createTagMethod>("topic", &GraphHandler::createTopicTag)); //4

	m_tagLookup.insert(pair<String, createTagMethod>("srai", &GraphHandler::createSraiTag)); //5
	m_tagLookup.insert(pair<String, createTagMethod>("that", &GraphHandler::createThatTag)); //6
	m_tagLookup.insert(pair<String, createTagMethod>("star", &GraphHandler::createStarTag)); //7

	m_tagLookup.insert(pair<String, createTagMethod>("set", &GraphHandler::createSetTag)); //8
	m_tagLookup.insert(pair<String, createTagMethod>("get", &GraphHandler::createGetTag)); //9
	m_tagLookup.insert(pair<String, createTagMethod>("think", &GraphHandler::createThinkTag)); //10

	m_tagLookup.insert(pair<String, createTagMethod>("person", &GraphHandler::createPersonTag)); //11
	m_tagLookup.insert(pair<String, createTagMethod>("bot", &GraphHandler::createConditionTag)); //12
	m_tagLookup.insert(pair<String, createTagMethod>("condition", &GraphHandler::createConditionTag)); //13

	m_tagLookup.insert(pair<String, createTagMethod>("li", &GraphHandler::createLiTag)); //14
	m_tagLookup.insert(pair<String, createTagMethod>("random", &GraphHandler::createRandomTag)); //15
	m_tagLookup.insert(pair<String, createTagMethod>("sr", &GraphHandler::createSrTag)); //16

	m_tagLookup.insert(pair<String, createTagMethod>("input", &GraphHandler::createInputTag)); //17
	m_tagLookup.insert(pair<String, createTagMethod>("thatstar", &GraphHandler::createThatStarTag)); //18
	m_tagLookup.insert(pair<String, createTagMethod>("topcstar", &GraphHandler::createTopicStarTag)); //19

	m_tagLookup.insert(pair<String, createTagMethod>("person2", &GraphHandler::createPerson2Tag)); //20
	m_tagLookup.insert(pair<String, createTagMethod>("gender", &GraphHandler::createGenderTag)); //21
	m_tagLookup.insert(pair<String, createTagMethod>("lowercase", &GraphHandler::createLowerCaseTag)); //22

	m_tagLookup.insert(pair<String, createTagMethod>("uppercase", &GraphHandler::createUpperCaseTag)); //23
	m_tagLookup.insert(pair<String, createTagMethod>("sentence", &GraphHandler::createSentenceTag)); //24
	m_tagLookup.insert(pair<String, createTagMethod>("formal", &GraphHandler::createFormalTag)); //25

	m_tagLookup.insert(pair<String, createTagMethod>("date", &GraphHandler::createDateTag)); //26
	m_tagLookup.insert(pair<String, createTagMethod>("id", &GraphHandler::createIdTag)); //27
	m_tagLookup.insert(pair<String, createTagMethod>("size", &GraphHandler::createSizeTag)); //28

	m_tagLookup.insert(pair<String, createTagMethod>("version", &GraphHandler::createVersionTag)); //29
	m_tagLookup.insert(pair<String, createTagMethod>("system", &GraphHandler::createSystemTag)); //30
	m_tagLookup.insert(pair<String, createTagMethod>("gossip", &GraphHandler::createGossipTag)); //31
	m_tagLookup.insert(pair<String, createTagMethod>("aiml", &GraphHandler::createAimlTag)); //32
}

shared_ptr<Tag> GraphHandler::createCategoryTag()
{
		++m_size;
		m_builder.setSize(m_size);
		m_builder.getCallBacks().categoryLoaded();
		return shared_ptr<Tag>(new Category);
}
shared_ptr<Tag> GraphHandler::createPatternTag()
{
		return shared_ptr<Tag>(new Pattern);
}
shared_ptr<Tag> GraphHandler::createTemplateTag()
{
		return shared_ptr<Tag>(new Template);
}
shared_ptr<Tag> GraphHandler::createTopicTag()
{
		return shared_ptr<Tag>(new Topic(m_rootNodeMapper));
}
shared_ptr<Tag> GraphHandler::createSraiTag()
{
		return shared_ptr<Tag>(new Srai(m_builder));
}
shared_ptr<Tag> GraphHandler::createThatTag()
{
		return shared_ptr<Tag>(new That(m_builder));
}
shared_ptr<Tag> GraphHandler::createStarTag()
{
		return shared_ptr<Tag>(new Star(m_builder));
}
shared_ptr<Tag> GraphHandler::createSetTag()
{
		return shared_ptr<Tag>(new Set(m_builder));
}
shared_ptr<Tag> GraphHandler::createGetTag()
{
		return shared_ptr<Tag>(new Get(m_builder));
}
shared_ptr<Tag> GraphHandler::createThinkTag()
{
		return shared_ptr<Tag>(new Think);
}
shared_ptr<Tag> GraphHandler::createPersonTag()
{
		return shared_ptr<Tag>(new Person(m_builder));
}

shared_ptr<Tag> GraphHandler::createBotTag()
{
		return shared_ptr<Tag>(new Bot(m_builder));
}

shared_ptr<Tag> GraphHandler::createConditionTag()
{
		return shared_ptr<Tag>(new Condition(m_builder));
}
shared_ptr<Tag> GraphHandler::createLiTag()
{
		return shared_ptr<Tag>(new Li);
}
shared_ptr<Tag> GraphHandler::createRandomTag()
{
		return shared_ptr<Tag>(new Random);
}
shared_ptr<Tag> GraphHandler::createSrTag()
{
		shared_ptr<Tag> nonImplemented(new NonImplemented);
		shared_ptr<Tag> srai(new Srai(m_builder));
		shared_ptr<Tag> star(new Star(m_builder));
		srai->handleInnerTag(star);
		nonImplemented->handleInnerTag(srai);
		return nonImplemented;
}
shared_ptr<Tag> GraphHandler::createInputTag()
{
		return shared_ptr<Input>(new Input(m_builder));
}
shared_ptr<Tag> GraphHandler::createThatStarTag()
{
		return shared_ptr<ThatStar>(new ThatStar(m_builder));
}
shared_ptr<Tag> GraphHandler::createTopicStarTag()
{
		return shared_ptr<TopicStar>(new TopicStar(m_builder));
}
shared_ptr<Tag> GraphHandler::createPerson2Tag()
{
		return shared_ptr<Tag>(new Person2(m_builder));
}

shared_ptr<Tag> GraphHandler::createGenderTag()
{
		return shared_ptr<Tag>(new Gender(m_builder));
}

shared_ptr<Tag> GraphHandler::createLowerCaseTag()
{
		return shared_ptr<Tag>(new LowerCase);
}
shared_ptr<Tag> GraphHandler::createUpperCaseTag()
{
		return shared_ptr<Tag>(new UpperCase);
}
shared_ptr<Tag> GraphHandler::createSentenceTag()
{
		return shared_ptr<Tag>(new Sentence);
}
shared_ptr<Tag> GraphHandler::createFormalTag()
{
		return shared_ptr<Tag>(new Formal);
}
shared_ptr<Tag> GraphHandler::createDateTag()
{
		return shared_ptr<Tag>(new Date);
}
shared_ptr<Tag> GraphHandler::createIdTag()
{
		return shared_ptr<Tag>(new Id(m_builder));
}
shared_ptr<Tag> GraphHandler::createSizeTag()
{
		return shared_ptr<Tag>(new Size(m_builder));
}
shared_ptr<Tag> GraphHandler::createVersionTag()
{
		return shared_ptr<Tag>(new Version(m_builder));
}
shared_ptr<Tag> GraphHandler::createSystemTag()
{
		return shared_ptr<Tag>(new System);
}
shared_ptr<Tag> GraphHandler::createGossipTag()
{
		return shared_ptr<Tag>(new Gossip(m_builder));
}
shared_ptr<Tag> GraphHandler::createAimlTag()
{
		return shared_ptr<Tag>(new AIML(*this, m_rootNodeMapper));
}

*/

} // end of namespace impl
} // end of namespace rebecca


