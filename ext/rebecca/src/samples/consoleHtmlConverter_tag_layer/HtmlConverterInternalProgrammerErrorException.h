#ifndef CUSTOMHTML_WEBPAGE_H
#define CUSTOMHTML_WEBPAGE_H

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

namespace customTag
{
namespace impl
{

/**
 * The custom generic exception for use by
 * the HtmlConverterProgrammerErrorException
 * internally.
 */
class HtmlConverterException : public Exception
{
	public: 
		
		/**
		 * By default have an unknown exception
		 * string.
		 *
		 * \param msg The message of what went wrong
		 */
		HtmlConverterException(const char * const msg = "Unknown exception")
			: m_msg(msg)
		{ }
		
		/**
		 * Send the const char of the string
		 * as the message of what happened.
		 */
		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}	

	private:

		/**
		 * String to hold the message
		 * of what went wrong 
		 */
		std::string m_msg;		
};


/**
 * The custom InternalProgrammerErrorException to throw
 * when the error is so grave the entire AIML engine has 
 * be shut down
 */
class HtmlConverterProgrammerErrorException : public InternalProgrammerErrorException
{
	public:
		
		/**
		 * Initialize the shared_ptr of the exception
		 * with the default message of 
		 * HtmlConverterException
		 */
		HtmlConverterProgrammerErrorException() 
			: m_exception(new HtmlConverterException) { } 
		
		/**
		 * Initialize the shared_ptr of the exception
		 * with our message of what went wrong.
		 *
		 * \param e The message of what went wrong
		 */
		HtmlConverterProgrammerErrorException(const char * const e)
			: m_exception(new HtmlConverterException(e))
		{ }
		
		/**
		 * Send the message of what went wrong
		 */
		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:

		/**
		 * Our internal generic exception
		 */
		shared_ptr<Exception> m_exception;
};

} //end of namespace impl
} //end of namespace customTag


#endif

