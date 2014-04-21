
//Custom tags include
#include "WebPage.h"

#include <map>
using namespace std;

namespace customTag
{
namespace impl
{

bool operator<(WebPage lfs, WebPage rhs)
{
	return lfs.getFileName() < rhs.getFileName();
}

} //end of namespace impl
} //end namespace customTag
