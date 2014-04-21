#ifndef REBECCA_IMPL_NODEMAPPER_H
#define REBECCA_IMPL_NODEMAPPER_H

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

//Boost includes
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

//Rebecca includes
#include <rebecca/framework/Template.h>
#include <rebecca/adt/String.h>
#include <rebecca/adt/Queue.h>
#include <rebecca/adt/Map.h>
#include <rebecca/impl/utils/Logging.h>

namespace rebecca
{
namespace impl
{
/*
 * Forward declerations
 */
class GraphBuilderInternal;

using namespace boost;
using namespace rebecca::framework;
	
class NodeMapper : public enable_shared_from_this<NodeMapper>
{	
	/** 
	 * Keeps track of all the operations you can 
	 * provide to the NodeMapper's links to other
	 * NodeMappers.
	 */
	class Links
	{

		public:
			Links(GraphBuilderInternal &builder);
			/**
			 * It checks if the link already exists 
			 * and adds it if it does, otherwise does 
			 * not add anything since that node is 
			 * already there.
			 */
			shared_ptr<NodeMapper> &add(String &word);
			shared_ptr<NodeMapper> getUnderScoreNode();
			shared_ptr<NodeMapper> getWordNode(const String &word);
			shared_ptr<NodeMapper> getStarNode();
		private:
			/** 
			 * This is the underlying data structure
			 * we are wrapping.
			 * 
			 * We map between the String of either a 
			 * word, a asterisk "*", or an underscore "_"
			 * and then return the node link.
			 */
			MapStringSharedPtrNodeMapper m_nodeLink;
			GraphBuilderInternal &m_builder;
	};

	class ThatHelper
	{
		public:
			ThatHelper(GraphBuilderInternal &builder);
			~ThatHelper();
		private:
			GraphBuilderInternal &m_builder;
	};


	class TopicHelper
	{
		public:
			TopicHelper(GraphBuilderInternal &builder);
			~TopicHelper();
		private:
			GraphBuilderInternal &m_builder;
		
	};

	public:

		/**
		 * Recursively addes the node to the node mapper.
         * Creates the other nodes along the way if they do 
		 * not already exist along the way.
		 */
		void add(const shared_ptr<Template> &templateToAdd, QueueString &wordStack);
		
		shared_ptr<NodeMapper> getNode(QueueString wordStack);
		NodeMapper(GraphBuilderInternal &builder);
		~NodeMapper();

		String getTemplateString(const String &path);
		String getTemplateString();
	private:
		bool hasTemplate() const;
        /**
		 *  The links of the NodeMapper to the other
		 *  nodes.
		 */
		Links m_links;

		/**
		 * The template composite.
		 */
		shared_ptr<Template> m_template;

		GraphBuilderInternal &m_builder;

		static void patternFittingNormalization(String &input)
		{
			/* 
			* At this point, the input should have been through the substitution normalization
			* and the sentence splitting stages.
			*/
			trim(input);
			to_upper(input);
			logging("Returing this string after normalization: " + input);
		}


};





} //end of namespace impl


} //end of namespace rebecca



#endif

