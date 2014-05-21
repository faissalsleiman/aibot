#ifndef QTGUI_QTGUICALLBACKS_H
#define QTGUI_QTGUICALLBACKS_H

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

//rebecca includes
#include <rebecca/CallBacks.h>

//std includes
#include <iostream>

//Qt includes
#include <QTextEdit>
#include <QScrollBar>
#include <QObject>

namespace qtgui
{

using namespace rebecca;
using namespace std;

/**
 * My Custom CallBacks class.
 * 
 * This class inherits from Rebecca's 
 * CallBacks class and implements the 
 * callbacks for error reporting and 
 * informational reporting purposes.
 *
 *
 * I override the callbacks and put
 * the callbacks into the Qt 
 * MainWindow to display
 */
class QtGuiCallBacks : public QObject, public CallBacks
{
	Q_OBJECT

	public:
		
		/**
		 * This is called for each AIML 
		 * "Gossip" tag.
		 *
		 * I am just printing out the gossip.
		 * You can do other things like store it 
		 * in a file and then reload the file at 
		 * startup as a type of persistance.
		 *
		 * \param gossip The gossip sent to be 
		 * stored as you see fit
		 */
		void storeGossip(const char * const gossip) 
		{ 
			QString output;
			output += "[Gossip: ";
			output += gossip;
			output += " ]";
			emit addText(output);
		}

		/**
		 * This is called for each AIML 
		 * category that is loaded into 
		 * memory.  
		 *
		 * Loadtime occurs whenver the call 
		 * GraphBuilder::createGraph() is made.
		 * For every 5000 categories loaded into
		 * Rebecca's internal data structure 
		 * this prints a output message about it.
		 */
		void categoryLoaded()
		{
			static int i = 0;
			const int numberOfCategories = 5000;
			
			/*
			 * Clever way to say if "i" is a multiple 
			 * of 5000 then print out the number of 
			 * categories loaded so far.
			 */
			if(++i % numberOfCategories == 0)
			{
				QString num;
				num.setNum(i);
				QString output;
				output += "[";
				output += num;
				output += " categories loaded]";
				emit addText(output);
			}
		}

		/**
		 * Before each AIML file is parsed this method is called.
         *
		 * \param fileName The name of the file about to be parsed.
		 */
		void filePreLoad(const char *const fileName)
		{
			QString output;
			output += "[Loading      ";
			output += fileName;
			output += "]";
			emit addText(output);
		}
		
		/**
		 * After each AIML file is parsed, this method is called.
         *
		 * \param fileName The name of the file just parsed.
		 */
		void filePostLoad(const char *const fileName)
		{
			QString output;
			output += "[Done loading ";
			output += fileName;
			output += "]";
			emit addText(output);
		}

		/**
		 * When the "srai" AIML tag is called, the text 
		 * is sent to this method.
		 *
		 * Usually refered to as symbolic reduction, you 
		 * can see what text is being re-fed back into the 
		 * AIML GraphBuilder::getResponse() by AIML its self.
		 *
		 * \param symbol The text which is being sent back
		 * into GraphBuilder::getResponse().
		 */
		void symbolicReduction(const char *const symbol)
		{
			QString output;
			output += "Symbolic reduction: ";
			output += symbol;
			emit addText(output);
		}

		/**
		 * A infinite symbolic reduction has occured and 
		 * has been terminated.
		 *
		 * This method is called when symbolic reduction ends
		 * up in a infinite loop and has been terminated.  This
		 * is just to alert you to the fact.
		 */
		void infiniteSymbolicReduction()
		{
			emit addText("[Infinite Symbolic reduction detected]");
		}
		
		/**
		 * Sends you a message about a XMLParseError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseError(const char * const message) 
		{ 
			emit addText(message);
		} 

		/**
		 * Sends you a message about a XMLParseWarning. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseWarning(const char * const message)
		{ 
			emit addText(message);
		} 

		/**
		 * Sends you a message about a XMLParseFatalError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseFatalError(const char * const message) 
		{ 
			emit addText(message);
		} 
		
		/**
		 * During runtime, the "thatStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatStarTagSizeExceeded() 
		{ 
			emit addText("[Warning thatStar Tag Size Exceeded]");
		}
		
		/**
		 * During runtime, the "topicStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void topicStarTagSizeExceeded() 
		{ 
			emit addText("[Warning topicStar Tag Size Exceeded]");
		}

		/**
		 * During runtime, the "star" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void starTagSizeExceeded() 
		{ 
			emit addText("[Warning star Tag Size Exceeded]");
		}

		/**
		 * A AIML "Input" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void inputTagNumericConversionError(const char * const message) 
		{ 
			QString output("inputTagNuermicConversionError:");
			output += message;
			emit addText(message);
		}

		/**
		 * During runtime, the "input" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void inputTagSizeExceeded() 
		{ 
			emit addText("[Warning input Tag Size Exceeded]");
		} 

		/**
		 * A AIML "Star" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void starTagNumericConversionError(const char * const message) 
		{ 
			QString output("starTagNuermicConversionError:");
			output += message;
			emit addText(message);
		} 

		/**
		 * During runtime, the "that" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatTagSizeExceeded() 
		{ 
			emit addText("thatTag Size exceeded");
		}

		/**
		 * A AIML "That" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatTagNumericConversionError(const char * const message) 
		{ 
			QString output("thatTagNumericConversionError:");
			output += message;
			emit addText(output);
		} 

		/**
		 * A AIML "TopicStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void topicStarTagNumericConversionError(const char * const message) 
		{ 
			QString output("topicStarTagNumericConversionError:");
			output += message;
			emit addText(output);
		}	
		
		/**
		 * A AIML "thatStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatStarTagNumericConversionError(const char * const message) 
		{ 
			QString output("thatStarTagNumericConversionError:");
			output += message;
			emit addText(output);
		}

	signals:

		/**
		 * Signal to emit to anyone interested in
		 * the text we have from our callbacks.
		 *
		 * \param text The text to emit
		 */
		void addText(const QString &text);
};

} //end of qtgui namespace

#endif
