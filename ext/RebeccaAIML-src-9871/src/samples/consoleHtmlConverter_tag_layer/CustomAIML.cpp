//Custom tag includes
#include "CustomAIML.h"
#include "typedefs.h"

namespace customTag
{
namespace impl
{

CustomAiml::CustomAiml(GraphBuilderFramework &builder, Html &htmlPage)
	throw(InternalProgrammerErrorException &)
	: AIML(builder), m_defaultStarTopic(builder, htmlPage)

{
	/*
	 * Add the name of this class.  Otherwise if I 
	 * didn't do this I could not call Tag::instanceOf("CustomAiml")
	 * on a CustomAiml object and get a true back.
	 */
	addInstanceOf("CustomAiml");

}

void CustomAiml::handleInnerTag(const shared_ptr<Tag> &tag)
	throw(InternalProgrammerErrorException &)
{
	if(tag->instanceOf("Topic"))
	{
		/*
		 * Found instance of topic and am ignoring it.
		 */
	}
	else
	{
       /*
		* Send the tag to our CustomTopic class
		*/
		m_defaultStarTopic.handleInnerTag(tag);
	}
}

} //end of namespace impl
} //end namespace customTag

