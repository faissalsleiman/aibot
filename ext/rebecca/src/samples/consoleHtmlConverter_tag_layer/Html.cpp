
//Custom tags includes
#include "Html.h"
#include "WebPage.h"

//Std includes
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//Boost includes
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
using namespace boost;
using namespace boost::filesystem; 

namespace customTag
{
namespace impl
{


Html::Html()
	: m_directoryName("htmlAiml")
{
	/*
	 * Create the directory and the 
	 * default style sheet if they do
	 * not exist
	 */
	create_directory( m_directoryName );
	if (!exists(m_directoryName + "/style.css"))
	{
		writeDefaultStyleSheet(m_directoryName + "/style.css");

	}
}

void Html::writeDefaultStyleSheet(const string &fileName)
{
	/*
	 * Write out a default style sheet with
	 * hardcoded values to the file given.
	 */
	const string styleSheet = "body {  background-color: #D9D9F3; }"
		                      "img {  border-width: 0;  vertical-align: middle;  text-align: center; }"
							  " h1 {  text-align: center; } "
							  " .title {  font-weight: bold;  font-size: larger; } "
							  " .menu {  position: absolute;  width: 7.5em;  top: 1em;  left: 1em;"
							  "  background-color: #E6E8FA;  border-style: inset;  border-width: 1px;  border-color: #000000; "
							  "  padding: 5px; } "
							  " #body {  position: absolute;  left: 10em;  top: 1em;  right: 1em; "
							  "  background-color: #E6E8FA;  border-style: inset;  border-width: 1px;  border-color: #000000;  padding: 5px; } ";

	ofstream file(fileName.c_str());
	file << styleSheet;
}

void Html::createLink(string urlToLinkTo, string urlDisplayName, string urlToLinkFrom)
{
	/*
	 * Make all the links lowercase 
	 * so they are easier on the eyes
	 * to look at.
	 */
	to_lower(urlToLinkTo);
	to_lower(urlDisplayName);
	to_lower(urlToLinkFrom);

	/*
	 * Setup the link to the url
	 * and the name of the url to 
	 * display on the web page
	 */
	Links link;
	link.setUrl(urlToLinkTo);
	link.setDisplayUrl(urlDisplayName);
	
	/*
	 * Create a webpage.  Set the file 
	 * name of the webpage to the name 
	 * of the url we are linking from. 
	 * Add the webpage to our map of url
	 * links if it does not already exist.
	 * 
	 * Take the handle to the web page and 
	 * add our link to it.
	 */
	WebPage webPage;
	webPage.setFileName(sanitizeString(urlToLinkFrom));
	MapStringLinks urlMap = m_links[webPage];
	urlMap[sanitizeString(urlToLinkTo)] = link;
	m_links[webPage] = urlMap;
}

void Html::createTemplateLink(string urlToLinkTo, string templateString, string urlToLinkFrom)
{

	/*
	 * Make all the links lowercase 
	 * so they are easier on the eyes
	 * to look at.
	 */
	to_lower(urlToLinkTo);
	to_lower(templateString);
	to_lower(urlToLinkFrom);

	/*
	 * Setup the link to the url
	 * but set the link to the text
	 * of the template string.
	 * 
	 * Since it is a template string
	 * there is no more links.  Instead
	 * of displaying a link we want to 
	 * display just the text of the template
	 * string.
	 */
	Links link;
	link.setTemplateString(templateString);

	/*
	 * Create a webpage.  Set the file 
	 * name of the webpage to the name 
	 * of the url we are linking from. 
	 * Add the webpage to our map of url
	 * links if it does not already exist.
	 * 
	 * Take the handle to the web page and 
	 * add our template string to it.
	 */
	WebPage webPage;
	webPage.setFileName(sanitizeString(urlToLinkFrom));
	MapStringLinks urlMap = m_links[webPage];
	urlMap[sanitizeString(urlToLinkTo)] = link;
	m_links[webPage] = urlMap;

}

void Html::writeWebPages()
{
	/*
	 * Create our types for iterating over
	 * the links and web pages.
	 */
	typedef MapStringLinks::const_iterator CII;
	typedef MapWebPageMapStringLinks::const_iterator CI;

	/*
	 * Display how many web pages based on the links size
	 */
	int size = m_links.size();
	cout << "Writing out " << size << " html webpages" << endl;

	/*
	 * Iterate over the links.  Each link is a web page.
	 */
	int counter = 0;
	for(CI it = m_links.begin(); it != m_links.end(); ++it, ++counter)
	{
		/*
		 * Friendly counter to let the user
		 * know some progress.
		 */
		if((counter % 1000) == 0)
		{
			if(counter != 0) 
			{
				int count=3, N=100;
				float percentage;
				percentage  = static_cast<float>(counter)/size * 100;
				cout << "[" << counter << " web pages written so far, " <<  setprecision(2) << percentage << "% completed]" << endl;
			}
		}
		
		/*
		 * Grab the webpage from the link.
		 * Derive the file name from it and
		 * create a file stream to our new file
		 * name
		 */
		WebPage webPage = it->first;
		string fileName = m_directoryName + "/" + webPage.getFileName() + ".html";
		ofstream file(fileName.c_str());		

		if(file.is_open())
		{
			/* 
			 * Set the caption of the web page.
			 * Write out the header of the web page.
			 */
			m_topCaption = webPage.getFileName();
			replace_all(m_topCaption, " ", "->");
			writeHtmlHeader(file);

			/*
			 * Write out the links of the web page
			 */
			for(CII iit = (it->second).begin(); iit != (it->second).end(); ++iit)
			{
				Links link = iit->second;
				file << link.getHtmlLink() << endl;
			}
			
			/*
			 * Write out the html footer page of
			 * the web page and we're through with
			 * this web page.
			 */
			writeHtmlFooter(file);

		}
		else
		{
			//Warning the file did not open
			cout << "Warning file did not open" << fileName << endl;
		}

	}
}

void Html::writeHtmlHeader(ofstream &file)
{
	/*
	 * Write out generic html header using 
	 * m_caption member variable as our caption
	 */
	
	file << "<html xmlns=\"http://www.w3.org/1999/xhtml\">" << endl;
	file << "<head>" << endl;
	file << "<title>AIML</title>" << endl;
	file << "<link rel=\"stylesheet\" href=\"style.css\" type=\"text/css\" title=\"default\">" << endl;
	file << "</head>" << endl;
	file << "<body>" << endl;
	file << "<center><h2>" << m_topCaption << "</h2></center>" << endl;
}

void Html::writeHtmlFooter(ofstream &file)
{
	/*
	 * Generic footer
	 */
	file << "</body>" << endl;
	file << "</html>" << endl;
}

} //end of namespace impl
} //end namespace customTag
