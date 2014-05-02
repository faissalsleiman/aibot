#ifndef REBECCA_TESTCASESHANDLER_H
#define REBECCA_TESTCASESHANDLER_H

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
#include <rebecca/adt/Vector.h>
#include <rebecca/impl/Exceptions.h>
#include <rebecca/GraphBuilder.h>

//std includes
#include <iostream>
#include <fstream>

//Boost includes
#include <boost/algorithm/string.hpp>

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
class GraphBuilderFramework;
XERCES_CPP_NAMESPACE_USE;
using namespace std;
using namespace boost;

class TestCasesHandler : public HandlerBase
{
	public:
		TestCasesHandler(const String outputFileName, GraphBuilder &builder);
		
		void output(const String &msg)
		{
			m_output << msg << endl;
		}

		void outputln(const String &msg)
		{
			m_output << msg << "<br/>" << endl;
		}

		void setInput(const String &input)
		{
			m_input = input;
		}
		
		void setExpectedKeywords(const String &expectedKeyWord)
		{
			m_keyWords.push_back(expectedKeyWord);
		}
		void setExpectedOutput(const String &expectedOutput)
		{
			m_expectedAnswer = expectedOutput;
		}
		void clear()
		{
			m_expectedAnswer.clear();
			m_input.clear();
			m_keyWords.clear();
		}
		void getResponse();

		class TestSuite : public Tag
		{
			public:
				TestSuite(TestCasesHandler &handler) 
					: m_handler(handler) 
				{ 
					this->addInstanceOf("TestSuite");
				}
				
				virtual void handleInnerTag(const shared_ptr<Tag> &tag) 
					throw(InternalProgrammerErrorException &)
				{
					if(tag->instanceOf("TestSuite"))
					{
						shared_ptr<TestSuite> testSuite = static_pointer_cast<TestSuite>(tag);
						testSuite->endTag();
					}
					else
					{
						throw InternalProgrammerErrorExceptionImpl("[TestSuite::handleInnerTag(const shared_ptr<Tag> &tag)" 
							                                       "tag was not an instance of TestSuite");
					}
				}

				virtual void endTag() { } 

			protected: 
				TestCasesHandler &m_handler;
		};

		class TestCase : public TestSuite
		{
			public:
				TestCase(TestCasesHandler &handler) 
					: TestSuite(handler) 
				{ 
					addInstanceOf("TestCase");
				} 
				
				virtual void setAttribute(const StringPimpl &name, const StringPimpl &value) throw(InternalProgrammerErrorException &);		

				virtual void endTag() 
				{
					m_handler.getResponse();
					m_handler.clear();
				}


		};

		class Description : public TestCase
		{
			public:
				Description(TestCasesHandler &handler)
					: TestCase(handler) 
				{ 
					addInstanceOf("Description");
				} 

				virtual void addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &);
				
				virtual void endTag() 
				{
					String outputMsg("Description:" + m_characters);
					m_handler.outputln(outputMsg.c_str());
				}

			private:	
				String m_characters;


		};

		class TestCaseInput : public TestCase
		{
			public:
				TestCaseInput(TestCasesHandler &handler)
					: TestCase(handler) 
				{ 
					addInstanceOf("TestCaseInput");
				} 

				virtual void addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &);
				virtual void endTag() 
				{
					String msg("Input:" + m_characters);
					m_handler.outputln(msg.c_str());
					m_handler.setInput(m_characters);
				}
			private:
				String m_characters;
		};


		class ExpectedAnswer : public TestCase 
		{
			public:
				ExpectedAnswer(TestCasesHandler &handler)
					: TestCase(handler) 
				{ 
					addInstanceOf("ExpectedAnswer");
				} 

				virtual void addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &);
				virtual void endTag() 
				{
					trim(m_characters);
					String outputMsg("Expected Answer:" + m_characters);
					m_handler.outputln(outputMsg.c_str());
					m_handler.setExpectedOutput(m_characters);
				}

			private:
				String m_characters;

		};

		class ExpectedKeyWords : public TestCase 
		{
			public:
				ExpectedKeyWords(TestCasesHandler &handler)
					: TestCase(handler) 
				{ 
					addInstanceOf("ExpectedKeyWords");
				} 

				virtual void addCharacters(const StringPimpl &characters) throw(InternalProgrammerErrorException &);

				virtual void endTag()
				{
					String msg("Expected keywords:" + m_characters); 
					m_handler.outputln(msg); 
				   	m_handler.setExpectedKeywords(m_characters);	
				}

			private:
				String m_characters;

		};

		class NoOps : public TestCase
		{
			public:
				NoOps(TestCasesHandler &handler)
					: TestCase(handler) 
				{ 
					addInstanceOf("NoOps");
				} 
				
				virtual void endTag() { } 

		};

		void startElement(const XMLCh* const name, AttributeList& attributes);
		void characters(const XMLCh * const chars, const XMLSize_t length);

		void endElement(const XMLCh *const name);

		shared_ptr<Tag> createTagClass(const String &className);
		virtual ~TestCasesHandler();

	private:
		SharedPtrStackTag m_tagStack;
		shared_ptr<Tag> m_currentStartElement;
		String m_outputFileName;
		ofstream m_output;
		ifstream m_inputFile;

		String m_input;
		String m_expectedAnswer;
		GraphBuilder &m_builder;
		VectorString m_keyWords;
};


} // end of impl namespace
} // end of rebecca namespace

#ifdef _WIN32
#    pragma warning ( pop )
#endif

#endif

