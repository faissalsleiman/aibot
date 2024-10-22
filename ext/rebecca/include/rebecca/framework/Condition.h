#ifndef REBECCA_FRAMEWORK_CONDITION_H
#define REBECCA_FRAMEWORK_CONDITION_H

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

/* Disable Windows VC 7.x warning about 
 * shared_ptr needing dll-interface and
 * about it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4251 )
#    pragma warning( disable : 4290 )
#endif

//Rebecca includes
#include <rebecca/framework/InnerTemplateListImpl.h>

namespace rebecca
{
namespace framework
{
namespace impl
{

/*
 * Forward declerations
 */

/**
 * The private implementation in which
 * you cannot get access to.
 *
 * This class holds the private methods
 * and private attributes of this class.  This 
 * makes ABI (Application Binary Interface) more
 * resilient to change. See the private implementation
 * idiom on the internet for more information about this.
 */
class ConditionImpl;
class GraphBuilderFramework;

/**
 * AIML class that represents the 
 * AIML XML tag "condition".  
 *
 * Every time a XML Tag of AIML is 
 * encountered, an instance of 
 * this class will be created.  All text
 * inbetween the begin and end tag, all
 * attributes, and all inner Tags will
 * go through methods of this class.
 */
class REBECCA_EXPORT Condition : public InnerTemplate
{
	public:

		/** 
		 * Initalizes the private 
		 * implementation (m_pimpl) data and 
		 * sets the private implementation 
		 * with a reference to the 
		 * GraphBuilderFramework.  
         *
		 * \param builder A reference 
		 * to the graph builder framework that 
		 * can be used to set and get information 
		 * from the AIML engine.
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		Condition(GraphBuilderFramework &builder) 
			throw(InternalProgrammerErrorException &);

		/**
		 * Calls GraphBuilderFramework::predicateMatch() with
		 * calculated data from Condition::setAttribute() and
		 * returns the result.
		 *
		 * \return The appropriate result from calling 
		 * GraphBuilderFramework::predicateMatch()
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual StringPimpl getString() const
			throw(InternalProgrammerErrorException &);

        /**
		 * Adds the InnerTemplate AIML XML Tag object to the 
		 * underlying data structure.
		 *
		 * \param tag The InnerTemplate AIML XML Tag that is inside this AIML XML 
		 * Tag and is to be added to this AIMl XML's underlying data structure for 
		 * latter retrievel through Condition::getString()
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual void add(const shared_ptr<InnerTemplate> &tag) 
			throw(InternalProgrammerErrorException &);
		
		/**
		 * Creates a PlainWord object with the characters and adds 
		 * it to the end of the underlying data structure.
		 *
		 * \param characters The characters to insert into the 
		 * PlainWord object.
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual void addCharacters(const StringPimpl &characters) 
			throw(InternalProgrammerErrorException &);
		
		/**
		 * Sets its attribute of "name" or "value"
         *
		 * \param name The name of the AIML XML attribute
		 *
		 * \param value The value of the AIML XML attribute
         *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual void setAttribute(const StringPimpl &name, const StringPimpl &value) 
			throw(InternalProgrammerErrorException &);
		
		/**
		 * Returns true if this is a block condition 
		 * otherwise it will return false.
		 * 
		 * The blockCondition type of condition has a 
		 * required attribute name, which specifies an 
		 * AIML predicate, and a required attribute 
		 * value, which contains a simple pattern expression.
		 *
		 * \return true if this is a block condition
		 * otherwise false
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual bool isBlockCondition() const
			throw(InternalProgrammerErrorException &);

		/**
		 * Returns true if this is a single predicate
		 * condition otherwise it will return false.
		 * 
         * The singlePredicateCondition type of condition 
		 * has a required attribute name, which specifies 
		 * an AIML predicate. This form of condition must 
		 * contain at least one li element. Zero or more of 
		 * these li elements may be of the valueOnlyListItem type. 
		 * Zero or one of these li elements may be of the 
		 * defaultListItem type.
		 *
		 * \return true if this is a single predicate
		 * condition otherwise false
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual bool isSinglePredicateCondition() const
			throw(InternalProgrammerErrorException &);

		/**
		 * Returns true if this is a multi-predicate
		 * condition otherwise it will return false.
		 * 
         * The multiPredicateCondition type of condition 
		 * has no attributes. This form of condition must 
		 * contain at least one li element. Zero or more 
		 * of these li elements may be of the nameValueListItem 
		 * type. Zero or one of these li elements may be of the 
		 * defaultListItem type.
		 * 
		 * \return true if this is a multi-predicate
		 * condition otherwise false
		 * 
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual bool isMutliPredicateCondition() const
			throw(InternalProgrammerErrorException &);

		/** 
		 * Default virtual destructor.  Destroys the private implementation
		 * (m_pimpl) data.
		 */
		virtual ~Condition();
	
	private:

       /**
		* The private implementation in which
		* you cannot get access to.
		*
		* This shared_ptr holds the private methods 
		* and private member variables of this class.  This 
		* makes ABI (Application Binary Interface) more
		* resilient to change. See the private implementation
		* idiom on the internet for more information about this.
		*/
		shared_ptr<ConditionImpl> m_pimpl;
};

} //end of namespace impl

//Expose just the class name to the framework namespace
using rebecca::framework::impl::Condition;

} //end of namespace framework
} //end of namespace rebecca

#ifdef _WIN32
#    pragma warning ( pop )
#endif

#endif
