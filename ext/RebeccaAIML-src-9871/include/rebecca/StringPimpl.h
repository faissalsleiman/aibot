#ifndef REBECCA_STRINGPIMPL_H
#define REBECCA_STRINGPIMPL_H

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


//To get the REBECA_EXPORT macro
#include <rebecca/exports.h>

#include <rebecca/Exceptions.h>

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4290 )
#endif


//See AimlFacade for the explanation of this namespace
namespace rebecca
{
//See AimlFacade for the explanation of this namespace
namespace impl
{



/*
 * The private String which I do not expose.
 * 
 * This forward decleration is so that the code will 
 * compile but the true string is kept private within
 * this class.
 */	
class StringPrivate;

/**
 * A String Private Implementation.
 *
 * This Private implementation's purpose (also commonly 
 * known on the internet as pimpl) is to not tie the user
 * of RebeccaAIML to a particular Standard Library by 
 * using a Standard Library string.
 *
 * Also, this private implementation handles the memory
 * management of strings inside the RebeccaAIML dll which 
 * is a requirement for Dll memory boundary safety.  
 * Standard Libraries could and sometimes do break Dll 
 * memory boundary safeties, hence another reason this 
 * class is needed.
 * 
 * Only a few needed methods are provided.  Once you get
 * this string object back, you should copy it into your own
 * standard string container.
 * 
 * Example:  StringPimpl s = someFoo(); std::string myString(s.c_str);
 */
class REBECCA_EXPORT StringPimpl
{
	public:

		/**
		 * Constructor that takes no arguments.
		 *
		 * The private string's empty constructor is called.
		 *
		 * \exception This will not explicitly throw an
		 * exception, but an underlying method might.  More
		 * than likely only a (bad_alloc) will be thrown for
		 * a out of memory exception.  If so, the bad_alloc's 
		 * message will be wrapped in the Exception class.
		 */
		StringPimpl() throw(Exception &);

		/**
		 * Constructor that takes in a const char.
		 *
		 * The char is copied to the private String.
		 *
		 * \param stringPimpl The const char which is
		 * copied to the private String.
		 * 
		 * \exception This will not explicitly throw an
		 * exception, but an underlying method might.  More
		 * than likely only a (bad_alloc) will be thrown for
		 * a out of memory exception.  If so, the bad_alloc's 
		 * message will be wrapped in the Exception class.
		 */
		StringPimpl(const char * const stringPimpl) throw(Exception &);
		
		/**
		 * Just like the Standard String's c_str, this 
		 * returns the internal string in the form of 
		 * a const char.
		 *
		 * Use this to copy the string into whichever type
		 * of String you deem suitable.
		 *
		 * \exception It will not explicitly throw an exception,
		 * but an underlying method might.  More than likely
		 * this will never throw an exception.
		 */
		const char *c_str() const throw(Exception &);

		/**
		 * Predicate which returns true if the internal
		 * string is empty and false if it is not empty.
		 * 
		 * \return True if the internal string is empty, 
		 * false if the internal string is not empty.
		 *
		 * \exception It will not explicitly throw an exception,
		 * but an underlying method might.  More than likely
		 * this will never throw an exception.
		 */
		bool empty() const throw(Exception &);

		/**
		 * Standard copy construtor.
		 * 
		 * \param stringPimpl Standard secondary 
		 * const StringPimpl reference needed for a 
		 * copy constructor.
		 * 
		 * \exception This can throw anything but will not 
		 * explicitly throw an exception.
		 */
		StringPimpl(const StringPimpl& stringPimpl);

		/** 
		 * Standard assignment operator.
		 * 
		 * Performs a deep copy of the internal string.
		 * 
		 * \param stringPimpl Standard secondary reference
		 * 
		 * \exception This can throw anything but will not
		 * explicitly throw an exception.
		 */
		StringPimpl &operator=(const StringPimpl &stringPimpl);

		/**
		 * Standard virtual destructor.
		 *
		 * This destorys the internal memory of the internal 
		 * string private implementation.  The deallocation of the
		 * memory occurs inside of the dll, therefore this 
		 * satisfies the requirement to be dll memory boundary safe.
		 */
		virtual ~StringPimpl();
		
		/**
		 * All delete's will be handled through
		 * this dll.
		 *
		 * This is required for dll boundary safety.
		 * Instead of allowing the compiler to 
		 * choose if it wants to inline this 
		 * we have made it so that it cannot.
		 * If we let the compiler choose to 
		 * inline or not inline this and the 
		 * "new operator" we can run into dll
		 * boundary issues.  The issue would be
		 * that the compiler would inline one 
		 * and not the other.  Thus, your 
		 * executable with its own heap would 
		 * allocate/delete and this dll would 
		 * do the other.  That's a dll boundary
		 * safety violation.
		 * 
         * \param p The pointer to an instance
		 * of this object.
		 */
        void operator delete(void* p);

		/**
		 * All new's will be handled through
		 * this dll.
		 *
		 * This is required for dll boundary safety.
		 * Instead of allowing the compiler to 
		 * choose if it wants to inline this 
		 * we have made it so that it cannot.
		 * If we let the compiler choose to 
		 * inline or not inline this and the 
		 * "delete operator" we can run into dll
		 * boundary issues.  The issue would be
		 * that the compiler would inline one 
		 * and not the other.  Thus, your 
		 * executable with its own heap would 
		 * allocate/delete and this dll would 
		 * do the other.  That's a dll boundary
		 * safety violation.
		 * 
         * \param size The size to allocate 
		 * an instance of this object with.
		 *
		 * \return An instance of this object
		 */
		void *operator new(unsigned int size);

	private:

		/**
		 * Private method to avoid duplicate code between
		 * the constructor and the copy constructor.
		 *
		 * \param stringPimpl The const char which is
		 * copied to the private String.
		 * 
		 * \exception This can throw anything.
		 *
		 */
		void init(const char * const stringPimpl);
		
		/**
		 * The private String which I do not expose.
		 *
		 * The memory for this is handled automatically 
		 * inside of the constructor and destructor of this 
		 * class.
		 */
		StringPrivate *m_pimpl;
};

} //end namespace impl

//expose StringPimpl to Rebecca namespace 
using rebecca::impl::StringPimpl;

} //end namespace rebecca

#ifdef _WIN32
#    pragma warning ( pop )
#endif





#endif
