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

#include <rebecca/impl/PrototypeFactory.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/impl/GraphBuilderInternal.h>

namespace rebecca
{
namespace impl
{

PrototypeFactory::PrototypeFactory(GraphBuilderInternal *gb)
	: m_prototypeGraphBuilder(gb)
{
	LOG_BOT_METHOD("PrototypeFactory::PrototypeFactory(GraphBuilder *gb)");
}

GraphBuilder *PrototypeFactory::createGraphBuilder()
{
	LOG_BOT_METHOD("GraphBuilder *PrototypeFactory::createGraphBuilder()");

	return m_prototypeGraphBuilder->clone();
}



} //end of namespace impl
} //end of namespace rebecca
