#ifndef QTGUI_CUSTOMTEXTEDIT_H
#define QTGUI_CUSTOMTEXTEDIT_H

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

//qt includes
#include <QTextEdit>
#include <QPixmap>

namespace qtgui
{

	/**
	 * Custom QTextEdit to prevent 
	 * the regular QTextEdit from 
	 * ruining the background picture
	 */
	class CustomTextEdit : public QTextEdit
	{
		public: 
			
			/**
			 * Override to keep the regular
			 * QTextEdit from ruining the 
			 * background picture.
			 *
			 * By scrolling by the entire view
			 * port and not just the minimum
			 * viewport, we tell Qt that it should
			 * update the entire viewport and thus
			 * updating the background picture.
			 *
			 * Otherwise we wind up with "artifacts"
			 * on the background picture.
			 * 
			 * \param dx the X to scroll by
			 * \param dy the Y to scroll by
			 */
			void scrollContentsBy (int dx, int dy)
			{
				QSize size = maximumViewportSize();
				QTextEdit::scrollContentsBy(size.height(), size.width());
			}
		
		private:
	};
}

#endif
