#ifndef REBECCA_IMPL_CONFIGURATIONHANDLER_H
#define REBECCA_IMPL_CONFIGURATIONHANDLER_H

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
#include <rebecca/framework/Tag.h>
#include <rebecca/adt/Stack.h>

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4290 )
#endif

namespace rebecca
{
namespace impl
{

XERCES_CPP_NAMESPACE_USE;
using namespace rebecca::framework;
using namespace boost;

/*
 * Forward declerations
 */
class GraphBuilderInternal;

class ConfigurationHandler : public HandlerBase
{
	public:

		class Input : public Tag
		{
			public:
				Input(GraphBuilderInternal &builder);
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &);
		
			private:
				GraphBuilderInternal &m_builder;
		};

		class Substitute : public Tag
		{
			public:
				Substitute();
				virtual void setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &);
				virtual String getFind();
				virtual String getReplace();
			private:
				String m_find;
				String m_replace;
		};
		
		class Gender : public Tag
		{
			public:
				Gender(GraphBuilderInternal &builder);
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &);
			private:
				GraphBuilderInternal &m_builder;

		};

		class Person : public Tag
		{
			public:
				Person(GraphBuilderInternal &builder);
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &);
			private:
				GraphBuilderInternal &m_builder;

		};

		class Person2 : public Tag
		{
			public:
				Person2(GraphBuilderInternal &builder);
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &);
			private:
				GraphBuilderInternal &m_builder;
		};

		class Substitutions : public Tag
		{
			public:
				Substitutions();
		};

		class SentenceSplitters : public Tag
		{
			public:
				SentenceSplitters(GraphBuilderInternal &builder);
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) throw(InternalProgrammerErrorException &);

			private:
				GraphBuilderInternal &m_builder;
		};

		class Splitter : public Tag
		{
			public:
				Splitter();
				virtual void setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &);
				virtual String getValue() { return m_value; }
			
			private:
				String m_value;
		};

		class Properties : public Tag
		{
			//Do nothing class.  
			//Needed however to just return when a 
			//<Property> tag is encountered.			
			public:
				Properties();
		};
		
		class Property : public Tag
		{
			public: 
				Property(GraphBuilderInternal &builder)
					: m_builder(builder) { }
				virtual void setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &);
			
			private:
				String m_name;
				GraphBuilderInternal &m_builder;


		};

		ConfigurationHandler(GraphBuilderInternal &builder);

		//Call back's from the sax parser
		virtual void characters(const XMLCh *const chars, const unsigned int length);
		virtual void startElement(const XMLCh* const, AttributeList&);
		virtual void endElement(const XMLCh *const name);
		virtual void endDocument();

		shared_ptr<Tag> createTagClass(const String &className);

	private:
		SharedPtrStackTag m_tagStack;
		shared_ptr<Tag> m_currentStartElement;
		GraphBuilderInternal &m_builder;
};


} // end of impl namespace
} // end of rebecca namespace

#ifdef _WIN32
#    pragma warning ( pop )
#endif

#endif
