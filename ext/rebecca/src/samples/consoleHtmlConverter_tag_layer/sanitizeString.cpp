
//custom tag includes
#include "sanitizeString.h"

//Boost includes
#include <boost/algorithm/string.hpp>
using namespace boost;


namespace customTag
{
namespace impl
{


string sanitizeString(const string dirtyString)
{
	return replace_all_copy(dirtyString, "*", "[dot]");
}


} //end of namespace impl
} //end namespace customTag

