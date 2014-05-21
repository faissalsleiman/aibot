#ifndef REBECCA_FRAMEWORK_INNERAIML_H
#define REBECCA_FRAMEWORK_INNERAIML_H

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
#include <rebecca/framework/Tag.h>

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
class InnerAIMLImpl;


/**
 * AIML XML abstract class for all the InnerAIML XML Tag 
 * classes inside of the AIML XML "aiml" to inherit from.
 *
 * If you write a AIML XML tag class such as Li, Srai, 
 * LowerCase, etc... which reside inside of <aiml>
 * you should either inherit from this class or from another
 * class which already inherits from this class.
 *
 * This is a do-nothing class.  It's purpose is to "tag"
 * other inheriting classes so that if they are indeed inside
 * of a <aiml> tag then they will have inherited from this 
 * class and you can call instanceOf("InnerAIML") and get 
 * back a boolean true.
 */
class REBECCA_EXPORT InnerAIML : public Tag
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
		InnerAIML() 
			throw(InternalProgrammerErrorException &);

		/** 
		 * Default virtual destructor.  Destroys the private implementation
		 * (m_pimpl) data.
		 */
		virtual ~InnerAIML();

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
		shared_ptr<InnerAIMLImpl> m_pimpl;
};


} //end of namespace impl

//Expose just the class name to the framework namespace
using rebecca::framework::impl::InnerAIML;

} //end of namespace framework
} //end of namespace rebecca

#ifdef _WIN32
#    pragma warning ( pop )
#endif

#endif

