#ifndef CUSTOMHTML_HTML_H
#define CUSTOMHTML_HTML_H

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


//Custom Tag includes
#include "Links.h"
#include "typedefs.h"
#include "sanitizeString.h"

//Std includes
#include <string>

namespace customTag
{
namespace impl
{

using namespace std;

/**
 * Class responsbile for all operations 
 * that pertain to creating the web pages
 * 
 * This class processes the head of the web page,
 * the foot of the webpage, methods for
 * creating the links on the webpage, writing out
 * the style sheet, and for writing out the entire
 * web page.
 */
class Html
{
	public:

		/** 
		 * Creates the html directory and writes out
		 * the default style sheet if they do not 
		 * exist.
		 */
		Html();
		
		/**
		 * Writes out the html header given the 
		 * file handle to write with.
		 * 
		 * \param file The file to write to
		 * 
		 * Uses m_topicCaption for the top caption
		 * of the web page.
		 */
		void writeHtmlHeader(ofstream &file);
		
		/**
		 * Writes the html footer.
		 *
		 * \param file The file to write to
		 */
		void writeHtmlFooter(ofstream &file);
		
		/**
		 * Creates the html web link on the 
		 * web page.
		 *
		 * \param urlToLinkTo The html link we want 
		 * to add to the web page.
		 *
		 * \param urlDisplayName The name of the link
		 * we want to give it to display on the web page
		 *
		 * \param urlToLinkFrom The web page we are linking
		 * from.
		 */
		void createLink(string urlToLinkTo, string urlDisplayName, string urlToLinkFrom);
		
		/** 
		 * Adds a template string to the web page
		 * instead of a link.
		 *
		 * \param urlToLinkTo The html link we want to add
		 * to the web page that leads to the template string.
		 *
		 * \param templateString the string to display by its self
		 * on the web page.
		 *
		 * \param urlToLinkFrom The web page we are linking from.
		 */
		void createTemplateLink(string urlToLinkTo, string templateString, string urlToLinkFrom);

		/**
		 * Write out all the web pages stored from
		 * the links in m_links
		 */
		void writeWebPages();
		
		/**
		 * Write out the hardcoded default style sheet.
		 *
		 * \param fileName The file to write the style sheet
		 * to.
		 */
		void writeDefaultStyleSheet(const string &fileName);

	private:

		/**
		 * The directory name where all the 
		 * html pages are being written to.
		 */
		string m_directoryName;
		
		/**
		 * The top caption of the web page.
		 */
		string m_topCaption;

		/**
		 * Map of web pages to a map of strings 
		 * to links.  It's a map of web pages 
		 * and their links.  This is the main
		 * data structure of webpages and their
		 * links.
		 */
		MapWebPageMapStringLinks m_links;
};

} //end of namespace impl
} //end of namespace customTag


#endif

