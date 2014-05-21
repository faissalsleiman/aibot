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


#include <string>

namespace customTag
{
namespace impl
{

using namespace std;

/**
 * Class that handles 
 * information related to a
 * web page
 */
class WebPage
{
	public:

		/**
		 * Set the file name of the web page.
		 *
		 * \param fileName File name of the 
		 * web page
		 */
		void setFileName(const string &fileName)
		{
			m_fileName = fileName;
		}
		
		/**
		 * Return the name of the web page.
		 *
		 * \return The name of the web page.
		 */
		string getFileName() const
		{
			return m_fileName;
		}
		
		
		/**
		 * Overidden less than operator
		 * so this can be inserted into a
		 * map.
		 *
		 * \param rhs Right hand side of the
		 * less than expression
		 */
		bool operator<(const WebPage &rhs)
		{
			return this->getFileName() < rhs.getFileName();
		}

	private:

		/**
		 * The file name of the web page
		 */
		string m_fileName;
};

/**
 * Overidden less than operator
 * so this can be inserted into a
 * map.
 *
 * \param lfh Left hand side of the
 * less than expression
 *
 * \param rhs Right hand side of the
 * less than expression
 */
bool operator<(WebPage lfh, WebPage rhs);


} //end of namespace impl
} //end of namespace customTag


#endif
