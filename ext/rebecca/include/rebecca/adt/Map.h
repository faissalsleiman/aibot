#ifndef REBECCA_ADT_MAP_H
#define REBECCA_ADT_MAP_H

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
#include <map>

//Rebecca includes
#include <rebecca/adt/String.h>

//Boost includes
#include <boost/shared_ptr.hpp>

namespace rebecca
{

namespace impl
{
class NodeMapper;
}

namespace adt
{


	
using namespace boost;
using namespace rebecca::impl;

template< typename T, typename U >
struct Map
{ 
	typedef std::map<T, U> type;
};

/**
 * Map that is used for both the public 
 * interfaces and the implementation.
 * 
 * This is a map of strings to integers
 */
typedef Map<String, int>::type MapStringInt;

/**
 * Map that is used for both the public 
 * interfaces and the implementation.
 * 
 * This is a map of strings to integers
 */
typedef Map<String, bool>::type MapStringBool;

typedef Map<String, String>::type MapStringString;

typedef Map<String, shared_ptr<NodeMapper> >::type MapStringSharedPtrNodeMapper;

} //end of adt namespace




namespace impl
{

//expose to implementations 
//by default
using adt::Map;
using adt::MapStringInt;
using adt::MapStringBool;
using adt::MapStringString;
using adt::MapStringSharedPtrNodeMapper;

} //end of impl namespace
} //end of rebecca namespace 

#endif
