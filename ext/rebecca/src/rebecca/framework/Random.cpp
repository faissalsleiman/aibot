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
#include <rebecca/framework/Random.h>
#include <rebecca/impl/utils/Logging.h>
#include <rebecca/adt/Vector.h>
#include <rebecca/framework/InnerTemplate.h>
using namespace rebecca::impl;

//Boost includes
#include <boost/algorithm/string.hpp>
using namespace boost;

//Std includes
#include <exception>
#include <cstdlib>
#include <ctime>
using namespace std;

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

namespace rebecca
{
namespace framework
{
namespace impl
{

class RandomImpl
{
	public:
		RandomImpl() { }
		~RandomImpl() { } 
		VectorSharedPtrInnerTemplate m_sentence;

};

Random::Random()
	throw(InternalProgrammerErrorException &)
	: m_pimpl(new RandomImpl)
{
	LOG_BOT_METHOD("Random::Random()");
	addInstanceOf("Random");
}

void Random::add(const shared_ptr<InnerTemplate> &tag) throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("void Random::add(const shared_ptr<InnerTemplate> &tag)");
	m_pimpl->m_sentence.push_back(tag);
}

StringPimpl Random::getString() const
	throw(InternalProgrammerErrorException &)
{
	LOG_BOT_METHOD("StringPimpl Random::getString() const");

	srand(static_cast<unsigned>(time(0)));
	int randomNumber = (rand() % m_pimpl->m_sentence.size());	
	String s = m_pimpl->m_sentence.at(randomNumber)->getString().c_str();
	trim(s);
	return s.c_str();
}

Random::~Random()
{
	LOG_BOT_METHOD("Random::~Random()");
}

} //end of namespace impl
} //end of namespace framework
} //end of namespace rebecca
