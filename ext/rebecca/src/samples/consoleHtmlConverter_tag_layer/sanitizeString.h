#ifndef CUSTOMHTML_SANITIZESTRING_H
#define CUSTOMHTML_SANITIZESTRING_H

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


//Std includes
#include <string>

namespace customTag
{
namespace impl
{
using namespace std;

/**
 * Function to remove replace or 
 * remove all characters that cannot
 * be in a file name.
 *
 * \param dirtyString the string to remove
 * or replace all characters that cannot be 
 * in a file name.
 *
 * \return The string that now has removed
 * or replaced all characters that cannot be 
 * in a file name.
 */
string sanitizeString(const string dirtyString);

} //end of namespace impl
} //end of namespace customTag


#endif
