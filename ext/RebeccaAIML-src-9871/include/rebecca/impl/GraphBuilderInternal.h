#ifndef REBECCA_IMPL_GRAPHBUILDERINTERNAL_H
#define REBECCA_IMPL_GRAPHBUILDERINTERNAL_H

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
#include <rebecca/framework/GraphBuilderFramework.h>
#include <rebecca/impl/CustomTagWithDelete.h>
#include <rebecca/adt/String.h>

//Std includes
#include <map>
namespace rebecca
{
namespace impl
{

/*
 * Forward declerations
 */
class NodeMapper;
using namespace rebecca::framework;
using namespace std;

class GraphBuilderInternal : public GraphBuilderFramework
{
	public:
		virtual GraphBuilder *clone() = 0;
		virtual NodeMapper &getRootNodeMapper() = 0;
		virtual void setUseThatStar() = 0;
		virtual void setUseTopicStar() = 0;
		virtual void setUseDefaultStar() = 0;
		virtual StringPimpl inputSubstitute(const StringPimpl &input) = 0;
		virtual void clearStars() = 0;
		virtual void addStar(const StringPimpl &star) = 0;
		virtual void setSize(const unsigned int newSize) = 0;

		///@todo put this into the adt
		virtual map<String, CustomTagWithDelete> &getCustomTagsMapRef() = 0;
};

} //end of namespace impl
} //end of namespace rebecca

#endif

