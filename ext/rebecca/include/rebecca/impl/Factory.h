#ifndef REBECCA_IMPL_FACTORY_H
#define REBECCA_IMPL_FACTORY_H

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

namespace rebecca
{
namespace impl
{

/*
 * Forward declerations 
 */
class GraphBuilder;

class Factory
{

	public:	
		static Factory *createFactory();
		virtual GraphBuilder *createGraphBuilder()  = 0; 
		
		virtual ~Factory() { };

};

} //end namespace impl
} //end namespace rebecca





#endif