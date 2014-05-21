#ifndef REBECCA_ADT_LIST_H
#define REBECCA_ADT_LIST_H

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
#include <list>

//Boost includes
#include <boost/shared_ptr.hpp>

namespace rebecca
{
namespace framework
{
namespace impl
{
class InnerTemplate;
class Li;
} //end of impl namespace 
}//end of framework namespace 

namespace impl
{
using rebecca::framework::impl::InnerTemplate;
using rebecca::framework::impl::Li;
}

namespace adt
{

using namespace boost; 
using namespace rebecca::impl;

template< typename T >
struct List
{ 
	typedef std::list<T> type;
};

typedef List<shared_ptr<InnerTemplate> >::type ListSharedPtrInnerTemplate;
typedef List<shared_ptr<Li> >::type ListSharedPtrLi;

} //end of adt namespace



namespace impl
{

//Expose list to impl namespace
using adt::ListSharedPtrInnerTemplate;
using adt::ListSharedPtrLi;

} //end of impl namespace
} //end of rebecca namespace 

#endif

