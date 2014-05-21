#ifndef REBECCA_ADT_STACK_H
#define REBECCA_ADT_STACK_H

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

//Rebecca includes
#include <rebecca/adt/String.h>

//Std includes
#include <stack>

//Boost includes
#include <boost/shared_ptr.hpp>

namespace rebecca
{

namespace framework
{
namespace impl
{
	class Tag;
}

}

namespace impl
{
using rebecca::framework::impl::Tag;
}

namespace adt
{
using namespace rebecca::impl;
using namespace boost;

template< typename T >
struct Stack
{ 
	typedef std::stack<T> type;
};

typedef Stack<String>::type StackString;
typedef Stack<Tag>::type StackTag;
typedef Stack<shared_ptr<Tag> >::type SharedPtrStackTag;
} //end of namespace adt

//Expose to the rebecca namespace
using adt::Stack;
using adt::StackString;
using adt::StackTag;
using adt::SharedPtrStackTag;

} //end of namespace rebecca



#endif

