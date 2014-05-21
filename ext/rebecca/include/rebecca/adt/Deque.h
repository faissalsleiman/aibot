#ifndef REBECCA_ADT_DEQUE_H
#define REBECCA_ADT_DEQUE_H

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

//Stl includes
#include <deque>

//Adt includes
#include <rebecca/adt/Deque.h>

namespace rebecca
{
namespace adt
{

template< typename T >
struct Deque
{ 
	typedef std::deque<T> type;
};

typedef Deque<String>::type DequeString;

typedef Deque<DequeString>::type DequeDequeString;

} //end of adt namespace



namespace impl
{

//Expose Deque to impl namespace
using adt::DequeString;
using adt::DequeDequeString;

} //end of impl namespace
} //end of rebecca namespace 

#endif

