#ifndef REBECCA_FRAMEWORK_INNERCATEGORY_H
#define REBECCA_FRAMEWORK_INNERCATEGORY_H

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
#include <rebecca/framework/InnerTopic.h>

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
class InnerCategoryImpl;
class Category;

/**
 * AIML XML abstract class for all the InnerCategory XML Tag 
 * classes inside of the AIML XML "category" to inherit from.
 *
 * If you write a AIML XML tag class such as Li, Srai, 
 * LowerCase, etc... which reside inside of <category>
 * you should either inherit from this class or from another
 * class which already inherits from this class.
 */
class REBECCA_EXPORT InnerCategory : public InnerTopic
{
	public:

		/** 
		 * Default constructor to initalize 
		 * the private implementation (m_pimpl)
		 * data.
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		InnerCategory() 
			throw(InternalProgrammerErrorException &);

		/**
		 * Contract to make all inner category XML Tags 
		 * return a string representing their internal 
		 * structure.
		 *
		 * See the inner category Tags to understand what 
		 * they will return.
		 *
		 * \return The string representation of the XML 
		 * Tag.
		 * 
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual StringPimpl getString() const 
			throw(InternalProgrammerErrorException &) = 0;
		
		/**
		 * The same as InnerCategory::getString() only it 
		 * returns a reference to the string and not the 
		 * string its self.
		 *
		 * It is a no-ops (no operations) method.  It does 
		 * not have to be implemented by all InnerCategory
		 * Tags.  It's provided for high efficiency.  Be
		 * careful if implementing this in your InnerCategory
		 * subclass.  You have to ensure that the object stays in
		 * memory until a copy of the string is made since the 
		 * object has ownership of the string.
		 *
		 * \return Returns a reference to the string
		 *
		 * \exception InternalProgrammerErrorException is thrown 
		 * only if the error is so grave that the entire AIML 
		 * engine has to be shut down.
		 */
		virtual const StringPimpl &getStringConstRef() const
			throw(InternalProgrammerErrorException &);

		/** 
		 * Default virtual destructor.  Destroys the private implementation
		 * (m_pimpl) data.
		 */
		virtual ~InnerCategory();

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
		shared_ptr<InnerCategoryImpl> m_pimpl;
};


} //end of namespace impl

//Expose just the class name to the framework namespace
using rebecca::framework::impl::InnerCategory;

} //end of namespace framework
} //end of namespace rebecca

#ifdef _WIN32
#    pragma warning ( pop )
#endif

#endif

