#ifndef REBECCA_IMPL_CUSTOMTAGWITHDELETE_H
#define REBECCA_IMPL_CUSTOMTAGWITHDELETE_H

#include <rebecca/framework/CustomTags.h>
using namespace rebecca::framework;

#ifdef _WIN32
#    pragma warning( disable : 4290 )
#    include <windows.h>
#else 
#   include <dlfcn.h>	
#endif

namespace rebecca
{
namespace impl
{

class CustomTagWithDelete
{
	public:
		typedef void(*ExitPointfuncPtr)(CustomTags *);  
		CustomTags *m_customTags;
		ExitPointfuncPtr m_deleteFunc;

	#ifdef _WIN32
		HINSTANCE m_dllHandle;
	#else //Linux
		void *m_dllHandle;
	#endif
};

} //end of namespace impl
} //end of namespace rebecca

#endif


