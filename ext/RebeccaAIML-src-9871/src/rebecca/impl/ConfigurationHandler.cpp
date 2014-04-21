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

//Rebecca includes
#include <rebecca/impl/ConfigurationHandler.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/utils/Transcode.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/impl/GraphBuilderInternal.h>

//Xerces includes
#include <xercesc/parsers/SAXParser.hpp>

//Stl includes
#include <iostream>
using namespace std;

#include <boost/shared_ptr.hpp>
using namespace boost;

namespace rebecca
{
namespace impl
{

ConfigurationHandler::ConfigurationHandler(GraphBuilderInternal &builder)
: m_builder(builder)
{ 
	LOG_BOT_METHOD("ConfigurationHandler::ConfigurationHandler()");
}

void ConfigurationHandler::characters(const XMLCh *const chars, const unsigned int length)
{
	LOG_BOT_METHOD("void ConfigurationHandler::characters(const XMLCh *const chars, const unsigned int length)");
	logging("Warning, This should not be called");
}

void ConfigurationHandler::startElement(const XMLCh* const name, AttributeList& attributes)
{
	LOG_BOT_METHOD("void ConfigurationHandler::startElement(const XMLCh* const, AttributeList&)");

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

void ConfigurationHandler::endElement(const XMLCh *const name)
{
	LOG_BOT_METHOD("void ConfigurationHandler::endElement(const XMLCh *const name)");

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
				logging("Tag stack empty, not doing anything");
			}
		}
		else
		{
			logging("Internal programmer Error the stack is empty");
			throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::endElement(const XMLCh *const name)] the stack is empty)");
		}
	}	
	catch(nullString &)
	{
		//Do nothing
		logging("caught nullString on someChars.getChar()");
	}

}

void ConfigurationHandler::endDocument()
{

}


shared_ptr<Tag> ConfigurationHandler::createTagClass(const String &className)
{
	LOG_BOT_METHOD("shared_ptr<Tag> ConfigurationHandler::createTagClass(const String &className)");

	if(className == "input")
	{
		return shared_ptr<Tag>(new Input(m_builder));
	}
	else if(className == "substitute")
	{
		return shared_ptr<Substitute>(new Substitute);
	}
	else if(className == "gender")
	{
		return shared_ptr<Gender>(new Gender(m_builder));
	}
	else if(className == "person")
	{
		return shared_ptr<Person>(new Person(m_builder));
	}
	else if(className == "person2")
	{
		return shared_ptr<Person2>(new Person2(m_builder));
	}
	else if(className == "substitutions")
	{
		return shared_ptr<Substitutions>(new Substitutions);
	}
	else if(className == "sentence-splitters")
	{
		return shared_ptr<SentenceSplitters>(new SentenceSplitters(m_builder));
	}
	else if(className == "splitter")
	{
		return shared_ptr<Splitter>(new Splitter);
	}
	else if(className == "properties")
	{
		return shared_ptr<Properties>(new Properties);
	}
	else if(className == "property")
	{
		return shared_ptr<Property>(new Property(m_builder));
	}
	else
	{
		logging("Warning, unknown className of: " + className);
		return shared_ptr<Substitutions>(new Substitutions);
	}
}

ConfigurationHandler::Input::Input(GraphBuilderInternal &builder)
	: m_builder(builder)
{ }

void ConfigurationHandler::Input::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void ConfigurationHandler::Input::handleInnerTag(const shared_ptr<Tag> &tag)");

	try
	{
		shared_ptr<Substitute> substitute = dynamic_pointer_cast<Substitute>(tag);
		if(substitute.get() == 0)
		{
			throw bad_cast();
		}
		else
		{
			m_builder.setInputSubstitution(substitute->getFind().c_str(), substitute->getReplace().c_str());
		}
	}
	catch(bad_cast &)
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerCategory");
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Input::handleInnerTag(const shared_ptr<Tag> &tag)] Bad cast, this is not a InnerCategory"); 
	}
}
ConfigurationHandler::Gender::Gender(GraphBuilderInternal &builder)
	: m_builder(builder)
{

}

ConfigurationHandler::Person::Person(GraphBuilderInternal &builder)
	: m_builder(builder)
{

}

ConfigurationHandler::Person2::Person2(GraphBuilderInternal &builder)
	: m_builder(builder)
{

}

void ConfigurationHandler::Gender::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	try
	{
		shared_ptr<Substitute> substitute = dynamic_pointer_cast<Substitute>(tag);
		if(substitute.get() == 0)
		{
			throw bad_cast();
		}
		else
		{
			m_builder.setGenderSubstitution(substitute->getFind().c_str(), substitute->getReplace().c_str());
		}
	}
	catch(bad_cast &)
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerCategory");
	throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Gender::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not a InnerCategory");
	}
}

void ConfigurationHandler::Person::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	try
	{
		shared_ptr<Substitute> substitute = dynamic_pointer_cast<Substitute>(tag);
		if(substitute.get() == 0)
		{
			throw bad_cast();
		}
		else
		{
			m_builder.setPersonSubstitution(substitute->getFind().c_str(), substitute->getReplace().c_str());
		}
	}
	catch(bad_cast &)
	{
		logging("Internal programmer error.  Bad cast, this is not a InnerCategory");
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Person::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not a InnerCategory");
	}
}

void ConfigurationHandler::Person2::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &) 
{
	try
	{
		shared_ptr<Substitute> substitute = dynamic_pointer_cast<Substitute>(tag);

		if(substitute.get() == 0)
		{
			throw bad_cast();
		}
		else
		{
			m_builder.setPerson2Substitution(substitute->getFind().c_str(), substitute->getReplace().c_str());
		}
	}
	catch(bad_cast &)
	{
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Person2::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not a InnerCategory");
	}
}

ConfigurationHandler::Substitute::Substitute()
{

}

void ConfigurationHandler::Substitute::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void ConfigurationHandler::Substitute::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name: " + nameString);
	logging("<Input> value: " + valueString);

	if((nameString == "find") && (!valueString.empty()))
	{
		logging("This is a find attribute and its value is: " + valueString);
		m_find = valueString;
	}
	else if(nameString == "replace")
	{
		logging("This is a replace attribute and its value is: " + valueString);
		m_replace = valueString;
	}
	else
	{
		logging("Internal programmer Error, unknown name type");
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Substitute::setAttribute(const StringPimpl &name, const StringPimpl &value)], unknown name type");
	}
}

String ConfigurationHandler::Substitute::getFind()
{
	return m_find;
}

String ConfigurationHandler::Substitute::getReplace()
{
	return m_replace;
}

ConfigurationHandler::SentenceSplitters::SentenceSplitters(GraphBuilderInternal &builder)
	: m_builder(builder)
{

}

void ConfigurationHandler::SentenceSplitters::handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &)
{
	try
	{
		shared_ptr<Splitter> splitter = dynamic_pointer_cast<Splitter>(tag);

		if(splitter.get() == 0)
		{
			throw bad_cast();
		}
		else
		{
			m_builder.setSentenceSplitter(splitter->getValue().c_str());
		}
	}
	catch(bad_cast &)
	{
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::SentenceSplitters::handleInnerTag(const shared_ptr<Tag> &tag)], Bad cast, this is not a Splitter");
	}
}

void ConfigurationHandler::Splitter::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void ConfigurationHandler::Splitter::setAttribute(const StringPimpl &name, const StringPimpl &value)");	
	String nameString(name.c_str());
	String valueString(value.c_str());

	logging("<Input> name: " + nameString);
	logging("<Input> value: " + valueString);

	if(nameString == "value")
	{
		if(!valueString.empty())
		{
			m_value = valueString;
		}
		else
		{
			logging("The value is empty");
		}
	}
	else if(nameString != "value")
	{
		logging("Internal programmer Error, unknown name type");
		throw InternalProgrammerErrorExceptionImpl("[void ConfigurationHandler::Splitter::setAttribute(const StringPimpl &name, const StringPimpl &value)], unknown name type");
	}
}

void ConfigurationHandler::Property::setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void ConfigurationHandler::Property::setAttribute(const StringPimpl &name, const StringPimpl &value)");
	String nameString(name.c_str());
	String valueString(value.c_str());
	logging("<Input> name: " + nameString);
	logging("<Input> value: " + valueString);

	if(nameString == "name")
	{
		if(!valueString.empty())
		{
			m_name = valueString;
		}
		else
		{
			logging("Name is empty");
		}
	}
	else if(nameString == "value")
	{		
		if(!value.empty() && !nameString.empty())
		{
			logging("Setting bot predicate name:" + m_name + " value:" + valueString);
			m_builder.setBotPredicate(m_name.c_str(), value.c_str());
		}
		else
		{
			logging("value or name is empty");
		}
	}
	else
	{
		logging("Internal programmer Error, unknown name type");
		throw InternalProgrammerErrorExceptionImpl("void ConfigurationHandler::Property::setAttribute(const StringPimpl &name, const StringPimpl &value), unknown name type");
	}

}

ConfigurationHandler::Properties::Properties()
{

}

ConfigurationHandler::Substitutions::Substitutions()
{

}

ConfigurationHandler::Splitter::Splitter()
{

}


} // end of namespace impl
} // end of namespace rebecca
