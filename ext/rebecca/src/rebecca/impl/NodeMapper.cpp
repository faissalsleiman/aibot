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
#include <rebecca/impl/NodeMapper.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/GraphBuilderInternal.h>
#include <rebecca/adt/Map.h>

//Boost includes
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace boost;

//Std includes
#include <iostream>
using namespace std;

namespace rebecca
{
namespace impl
{


NodeMapper::NodeMapper(GraphBuilderInternal &builder)
	: m_builder(builder), 
	  m_links(builder)
{
	LOG_BOT_METHOD("NodeMapper::NodeMapper(GraphBuilderInternal &builder)");
}

void NodeMapper::add(const shared_ptr<Template> &templateToAdd, QueueString &wordStack)
{
	LOG_BOT_METHOD("void NodeMapper::add(const shared_ptr<Template> &templateToAdd, StackString &wordStack)");

	if(wordStack.empty())
	{
		logging("Stack is completely empty, I am adding the template and returning.");
		m_template = templateToAdd;
	}
	else
	{
		//This is actually a reference to a node inside of the map.
		//It is faster to use a reference inside of the map and change the reference
		//inside of the map directly then to be making tons of copies.
		shared_ptr<NodeMapper> &node = m_links.add(wordStack.front());
		wordStack.pop();
		
		node->add(templateToAdd, wordStack);
	}
}

bool NodeMapper::hasTemplate() const
{
	if(m_template.get() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

String NodeMapper::getTemplateString(const String &path)
{
	LOG_BOT_METHOD("String NodeMapper::getTemplateString(const String &path)");

	QueueString wordStack;
	typedef tokenizer<char_separator<char> > tokenize;
	typedef tokenizer<char_separator<char> >::const_iterator CI;

	m_builder.clearStars();
	char_separator<char> sep(" ");
	tokenize pathTokens(path, sep);

	CI it;
	for(it = pathTokens.begin(); it != pathTokens.end(); ++it)
	{
		logging("Pushing onto word stack: " + *it);
		wordStack.push(*it);
	}	
	
	logging("Pushing onto word stack: <THAT>");
	wordStack.push("<THAT>");
	String that = m_builder.getThat().c_str();
	tokenize thatTokens(that, sep);

	for(it = thatTokens.begin(); it != thatTokens.end(); ++it)
	{
		logging("Pushing onto word stack: " + *it);
		wordStack.push(*it);
	}
	
	logging("Pushing onto word stack: <TOPIC>");
	wordStack.push("<TOPIC>");
	String topic = m_builder.getTopic().c_str();
	tokenize topicTokens(topic, sep);

	for(it = topicTokens.begin(); it != topicTokens.end(); ++it)
	{
		logging("Pushing onto word stack: " + *it);
		wordStack.push(*it);
	}

	shared_ptr<NodeMapper> node = getNode(wordStack);

	if(node.get())
	{
		return node->getTemplateString();
	}
	else
	{
		return String();
	}
}

String NodeMapper::getTemplateString()
{
	LOG_BOT_METHOD("String NodeMapper::getTemplateString() const");

	return m_template->getString().c_str();
}


NodeMapper::ThatHelper::ThatHelper(GraphBuilderInternal &builder)
	: m_builder(builder)
{
	m_builder.setUseThatStar();
}

NodeMapper::ThatHelper::~ThatHelper()
{
	m_builder.setUseDefaultStar();
}



NodeMapper::TopicHelper::TopicHelper(GraphBuilderInternal &builder)
	: m_builder(builder)
{
	m_builder.setUseTopicStar();
}

NodeMapper::TopicHelper::~TopicHelper()
{
	m_builder.setUseThatStar();
}

shared_ptr<NodeMapper> NodeMapper::getNode(QueueString wordStack)
{
	LOG_BOT_METHOD("NodeMapper &NodeMapper::Links::getNode(QueueString wordStack)");
	String star;
	scoped_ptr<ThatHelper> scopedThat;
	scoped_ptr<TopicHelper> scopedTopic;

	if(wordStack.empty())
	{
		logging("wordStack is empty.");
		if(this->hasTemplate())
		{
			return shared_from_this();
		}
		else
		{
			return shared_ptr<NodeMapper>();
		}
	}
	else
	{
		String word = wordStack.front();

		if(word == "<THAT>")
		{	
			scopedThat.reset(new ThatHelper(m_builder));
		}
		else if(word == "<TOPIC>")
		{
			scopedTopic.reset(new TopicHelper(m_builder));
		}		

		wordStack.pop();

		shared_ptr<NodeMapper> node = m_links.getUnderScoreNode();

		if(node.get())
		{	
			QueueString tempStack = wordStack;
			star += word;

			while(!tempStack.empty())
			{	
				shared_ptr<NodeMapper> returnNode = node->getNode(tempStack);

				if(returnNode.get())
				{	
					m_builder.addStar(star.c_str());
					return returnNode;					
				}
				else
				{	
					star += " " + tempStack.front();
					tempStack.pop();
				}
			}

			if(node->hasTemplate())
			{	
				m_builder.addStar(star.c_str());
				return node;
			}
		}
		
		star = "";

		if(word != "*")
		{			
			node = m_links.getWordNode(word);

			if(node.get())
			{
				node = node->getNode(wordStack);

				if(node.get())
				{
					return node;
				}
			}
		}

		node = m_links.getStarNode();

		if(node.get())
		{
			QueueString tempStack = wordStack;

			if(word != "*")
			{
				star += word;
			}

			while(!tempStack.empty())
			{   
				shared_ptr<NodeMapper> returnNode = node->getNode(tempStack);
				
				if(returnNode.get())
				{
					m_builder.addStar(star.c_str());
					return returnNode;
				}
				else
				{
					star += " " + tempStack.front();
					tempStack.pop();
				}
			}

			if(node->hasTemplate())
			{	
				m_builder.addStar(star.c_str());
				return node;
			}
			else
			{
				return shared_ptr<NodeMapper>();
			}
		}
		else
		{
			//Doesn't match _, word, or star
			return shared_ptr<NodeMapper>();
		}
	}
}
NodeMapper::Links::Links(GraphBuilderInternal &builder)
	: m_builder(builder)
{
	LOG_BOT_METHOD("Links::Links(GraphBuilderInternal &builder)");
}

shared_ptr<NodeMapper> NodeMapper::Links::getWordNode(const String &word)
{
	LOG_BOT_METHOD("shared_ptr<NodeMapper> NodeMapper::getWordNode(const String &word)");
	logging("<Input>: " + word);

	//match using case insensitiviy.
	String caseInsensitiveWord(trim_copy(word));
	to_upper(caseInsensitiveWord);
	
	MapStringSharedPtrNodeMapper::iterator i;
	
	i = m_nodeLink.find(caseInsensitiveWord);

	if(i != m_nodeLink.end())
	{
		logging("Found the node associated with this word");
		return i->second;
	}
	else
	{
		logging("Did not find the node associated with this word");
		return shared_ptr<NodeMapper>();
	}
}

shared_ptr<NodeMapper> &NodeMapper::Links::add(String &word)
{
	LOG_BOT_METHOD("shared_ptr<NodeMapper> NodeMapper::Links::add(String word)");
	logging("<Input>: " + word);

	/*
	 *	
	 * Big performance bottle neck right here.
	 * Normalizing words is *extremely* costly
	 */
	patternFittingNormalization(word);
	
	MapStringSharedPtrNodeMapper::iterator i;

	i = m_nodeLink.find(word);
	
	if(i != m_nodeLink.end())
	{
		logging("Word is already represented as a node.  Returning that node");
		return i->second;
	}
	else
	{
		logging("Word is not already a node.  Creating a node for it."); 
		logging("returning the reference to that node.");
		return m_nodeLink[word] = shared_ptr<NodeMapper>(new NodeMapper(m_builder));
	}
}

shared_ptr<NodeMapper> NodeMapper::Links::getUnderScoreNode()
{
	LOG_BOT_METHOD("shared_ptr<NodeMapper> NodeMapper::Links::getUnderScore()");
	return getWordNode("_");
}

shared_ptr<NodeMapper> NodeMapper::Links::getStarNode()
{
	LOG_BOT_METHOD("shared_ptr<NodeMapper> NodeMapper::Links::getUnderScore()");
	return getWordNode("*");
}


NodeMapper::~NodeMapper()
{
	LOG_BOT_METHOD("NodeMapper::~NodeMapper()");
}


} //end of namespace impl
} //end of namespace rebecca
