#ifndef REBECCA_IMPL_GRAPHHANDLER_H
#define REBECCA_IMPL_GRAPHHANDLER_H

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

//Xerces includes
#include <xercesc/sax/HandlerBase.hpp>

//Rebecca includes
#include <rebecca/adt/String.h>
#include <rebecca/adt/Stack.h>
#include <rebecca/adt/Map.h>
#include <rebecca/impl/NodeMapper.h>
#include <rebecca/framework/Tag.h>

//Boost includes
#include <boost/shared_ptr.hpp>


namespace rebecca
{
namespace impl
{

XERCES_CPP_NAMESPACE_USE
using namespace boost;
using namespace rebecca;
using namespace std;

//forward declarations
class Tag;

class GraphHandler : public HandlerBase
{
	public:

		//Call back's from the sax parser

		GraphHandler(NodeMapper &root, GraphBuilderInternal &builder);
		void characters(const XMLCh *const chars, const unsigned int length);
		void startElement(const XMLCh* const, AttributeList&);
		void endElement(const XMLCh *const name);
		void endDocument();

		//Regular additional public members.

		void setAIMLVersion(const String &version);
		String getAIMLVersion();



	private:


		shared_ptr<Tag> createTagClass(const String &className);

		SharedPtrStackTag m_tagStack;
		String m_aimlVersion;

		/**
		 * Reference to the root of the 
		 * NodeMapper tree. As the parser 
		 * encounters <category>
		 * tags, it will begin construction of a 
		 * new node and latter when it encounters a 
		 * </category> tag it will add it to the rootNode.
		 * This is just a reference.  It's location should
		 * reside within a GraphBuilderInternal instance.
		 */
		NodeMapper &m_rootNodeMapper;
		
		GraphBuilderInternal &m_builder;

		/**
		 * Current node being constructed.
		 *
		 */		
		shared_ptr<NodeMapper> m_currentNode;
		shared_ptr<Tag> m_currentStartElement;

		int m_size;

		bool m_templateSideThat;

/* Commented out.  Not fast enough to justify use
		shared_ptr<Tag> createTagClassFromMap(const String &className);
		typedef shared_ptr<Tag> (GraphHandler::*createTagMethod)();
		map<String, createTagMethod> m_tagLookup;
		void init();

		//All the function pointers
		shared_ptr<Tag> createCategoryTag(); //1
		shared_ptr<Tag> createPatternTag(); //2
		shared_ptr<Tag> createTemplateTag(); //3
		shared_ptr<Tag> createTopicTag(); //4
		shared_ptr<Tag> createSraiTag();//5
		shared_ptr<Tag> createThatTag();//6
		shared_ptr<Tag> createStarTag();//7
		shared_ptr<Tag> createSetTag();//8
		shared_ptr<Tag> createGetTag();//9
		shared_ptr<Tag> createThinkTag();//10
		shared_ptr<Tag> createPersonTag();//11
		shared_ptr<Tag> createBotTag();//12
		shared_ptr<Tag> createConditionTag();//13
		shared_ptr<Tag> createLiTag();//14
		shared_ptr<Tag> createRandomTag();//15
		shared_ptr<Tag> createSrTag();//16
		shared_ptr<Tag> createInputTag();//17
		shared_ptr<Tag> createThatStarTag();//18
		shared_ptr<Tag> createTopicStarTag();//19
		shared_ptr<Tag> createPerson2Tag();//20
		shared_ptr<Tag> createGenderTag();//21
		shared_ptr<Tag> createLowerCaseTag();//22
		shared_ptr<Tag> createUpperCaseTag();//23
		shared_ptr<Tag> createSentenceTag();//24
		shared_ptr<Tag> createFormalTag();//25
		shared_ptr<Tag> createDateTag();//26
		shared_ptr<Tag> createIdTag();//27
		shared_ptr<Tag> createSizeTag();//28
		shared_ptr<Tag> createVersionTag();//29
		shared_ptr<Tag> createSystemTag();//30
		shared_ptr<Tag> createGossipTag();//31
		shared_ptr<Tag> createAimlTag();//32
*/
};


} // end of impl namespace
} // end of rebecca namespace
#endif
