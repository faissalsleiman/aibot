#ifndef REBECCA_ADT_VECTOR_H
#define REBECCA_ADT_VECTOR_H

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
#include <vector>

//Rebecca includes
#include <rebecca/adt/String.h>

//Boost includes
#include <boost/shared_ptr.hpp>

namespace rebecca
{

namespace framework
{
namespace impl
{

/*
 * Forward declerations
 */
class InnerTemplate;

} //end of namespace impl
} //end of namespace framework

namespace impl
{
using framework::impl::InnerTemplate;
}

namespace adt
{
using namespace boost;
using rebecca::impl::InnerTemplate;

template< typename T >
struct Vector
{ 
	typedef std::vector<T> type;
};

/**
 * Vector that is used for both the public 
 * interfaces and the implementation.
 * 
 * This is a vector of integers
 */
typedef Vector<int>::type VectorInt;

/**
 * Vector that is used for both the public 
 * interfaces and the implementation.
 * 
 * This is a vector of strings
 */
typedef Vector<String>::type VectorString;

typedef Vector<shared_ptr<InnerTemplate> >::type VectorSharedPtrInnerTemplate;

} //end of adt namespace




namespace impl
{

//Make vectors available
//to implementation by default
using adt::Vector;
using adt::VectorInt;
using adt::VectorString;
using adt::VectorSharedPtrInnerTemplate;
} //end of impl namespace
} //end of rebecca namespace

#endif
