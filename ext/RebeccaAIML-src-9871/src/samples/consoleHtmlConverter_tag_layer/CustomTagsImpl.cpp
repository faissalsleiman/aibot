
//Custom tag includes
#include "CustomTagsImpl.h"
#include "CustomTopic.h"
#include "CustomAIML.h"
#include "Links.h"
#include "Html.h"
#include "WebPage.h"
#include "InnerTemplateAIMLTags.h"

//Std includes
#include <fstream>


namespace customTag
{
namespace impl
{

CustomTagsImpl::CustomTagsImpl() 
	throw(InternalProgrammerErrorException &)
	: m_templateSideThat(false)
{
 /*
  * Do nothing other than set the 
  * m_templateSideThat to false.
  */
}


shared_ptr<Tag> CustomTagsImpl::createTagClass(const char * const className, GraphBuilderFramework &builder)
	throw(InternalProgrammerErrorException &)
{
	/*
	 * Copy the className to a real string
	 * so we can use the "==" operator
	 */
	string classNameString(className);

	if(classNameString == "topic")
	{
		/*
		 * Found the tag <topic> so now return an 
		 * instance of the class.
		 */
		return shared_ptr<Tag>(new CustomTopic(builder, m_htmlPage));
	}
	else if(classNameString == "aiml")
	{
		/*
		 * Found the tag <aiml> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomAiml(builder, m_htmlPage));
	}
	else if(classNameString == "gender")
	{
		/*
		 * Found the tag <gender> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomGender(builder));
	}
	else if(classNameString == "bot")
	{
		/*
		 * Found the tag <bot> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomBot(builder));
	}
	else if(classNameString == "condition")
	{
		/*
		 * Found the tag <condition> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomCondition(builder));
	}
	else if(classNameString == "li")
	{
		/*
		 * Found the tag <li> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomLi);
	}
	else if(classNameString == "date")
	{
		/*
		 * Found the tag <date> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomDate);
	}
	else if(classNameString == "formal")
	{
		/*
		 * Found the tag <formal> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomFormal);
	}
	else if(classNameString == "gossip")
	{
		/*
		 * Found the tag <gossip> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomGossip(builder));
	}
	else if(classNameString == "get")
	{
		/*
		 * Found the tag <get> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomGet(builder));
	}
	else if(classNameString == "id")
	{
		/*
		 * Found the tag <id> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomId(builder));
	}
	else if(classNameString == "input")
	{
		/*
		 * Found the tag <input> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomInput(builder));
	}
	else if(classNameString == "lowercase")
	{
		/*
		 * Found the tag <lowercase> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomLowerCase);
	}
	else if(classNameString == "person")
	{
		/*
		 * Found the tag <person> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomPerson(builder));
	}
	else if(classNameString == "person2")
	{
		/*
		 * Found the tag <person2> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomPerson2(builder));
	}
	else if(classNameString == "random")
	{
		/*
		 * Found the tag <random> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomRandom);
	}
	else if(classNameString == "sentence")
	{
		/*
		 * Found the tag <sentence> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomSentence);
	}
	else if(classNameString == "set")
	{
		/*
		 * Found the tag <set> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomSet(builder));
	}
	else if(classNameString == "size")
	{
		/*
		 * Found the tag <size> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomSize(builder));
	}
	else if(classNameString == "srai")
	{
		/*
		 * Found the tag <srai> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomSrai(builder));
	}
	else if(classNameString == "star")
	{
		/*
		 * Found the tag <star> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomStar(builder));
	}
	else if(classNameString == "system")
	{
		/*
		 * Found the tag <system> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomSystem);
	}
	else if(classNameString == "thatstar")
	{
		/*
		 * Found the tag <thatstar> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomThatStar(builder));
	}
	else if(classNameString == "think")
	{
		/*
		 * Found the tag <think> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomThink);
	}
	else if(classNameString == "topicstar")
	{
		/*
		 * Found the tag <topicstar> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomTopicStar(builder));
	}
	else if(classNameString == "uppercase")
	{
		/*
		 * Found the tag <uppercase> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomUpperCase);
	}
	else if(classNameString == "version")
	{
		/*
		 * Found the tag <version> so now return an 
		 * instance of our overriden class 
		 */
		return shared_ptr<Tag>(new CustomVersion(builder));
	}
	else if(classNameString == "sr")
	{
		/*
		 * sr is a AIML shortcut for <srai><star/></srai>
		 * In order to expand this shortcut we create a 
		 * NonImplemented tag and add to the NonImplemented 
		 * tag a srai which has a star added to it.
		 *
		 * So now, on the Rebecca engine will be 
		 * <nonImplemented><srai><star/></srai><nonimplemented>
		 * This is okay, because when nonimplemented is taken
		 * apart by the engine it will in turn call the 
		 * <srai> and <star> tags.
		 * 
		 * The desired functionality will occur.
		 */
		shared_ptr<Tag> nonImplemented(new NonImplemented);
		shared_ptr<Tag> srai(new CustomSrai(builder));
		shared_ptr<Tag> star(new CustomStar(builder));
		srai->handleInnerTag(star);
		nonImplemented->handleInnerTag(srai);
		return nonImplemented;		
	}
	else if(classNameString == "template")
	{
		/*
		 * We use this to figure out that we are now 
		 * within a template and thus should use
		 * a templateSideThat when we see the string "template"
		 */
		m_templateSideThat = true;
		return shared_ptr<Tag>();
	} 
	else if(classNameString == "category")
	{
		/*
		 * We use this to figure out that we are now 
		 * not within a template and thus should not use
		 * a templateSideThat when we see the string "template"
		 */
		m_templateSideThat = false;

	   /*
		* Let rebecca use her default Category.  We do this by
		* returning an empty shared_ptr.  When rebecca sees an
		* empty shared_ptr, she will then use her default 
		* implementation of the category.
		*/
		return shared_ptr<Tag>();
	}
	else if(classNameString == "that")
	{
		if(m_templateSideThat)
		{
			/*
			 * It is a template side that so return
			 * our version of it
			 */
			return shared_ptr<Tag>(new CustomTemplateSideThat(builder));
		}
		else
		{
			/*
			 * Let rebecca use her default Template.  We only 
			 * provide the template side that.  We do this by
			 * returning an empty shared_ptr.  When rebecca sees an
			 * empty shared_ptr, she will then use her default 
			 * implementation of the template.
			 */
			return shared_ptr<Tag>();
		}
	}
	else 
	{
		/*
		 * If you cannot find your custom tag class you 
		 * *must* return an empty shared_ptr.
		 */
		return shared_ptr<Tag>();
	}
}

CustomTagsImpl::~CustomTagsImpl()
{
	/*
	 * Write out the entire web pages
	 * We are about to be destroyed 
	 * so this will complete us
	 */
	m_htmlPage.writeWebPages();	
}

} //end of namespace impl
} //end namespace customTag
