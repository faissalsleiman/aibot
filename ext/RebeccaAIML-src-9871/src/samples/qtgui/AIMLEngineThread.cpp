
//qtgui includes
#include "AIMLEngineThread.h"
#include "CustomTextEdit.h"
#include "AIMLEngine.h"
#include "Arguments.h"

namespace qtgui
{

void AIMLEngineThread::run()
{
	/*
	 * Create the aimlEngine in the
	 * thread on the local stack.  It'll
	 * be destroyed when the thread is.
	 */
	AIMLEngine aimlEngine;

	/*
	 * Make all the signal to signal and 
	 * signal to slot connections from the 
	 * AIMLEngineThread object to the AIMLEngine
	 * object.  This will be the only way to 
	 * communicate to the AIMLEngine object is 
	 * through signals and slots.
	 */
	bool b;
	b = connect(&aimlEngine, SIGNAL(addText(const QString &)),
		        this, SIGNAL(addText(const QString &)));

	b = connect(&aimlEngine, SIGNAL(addBotText(const QString &)),
		        this, SIGNAL(addBotText(const QString &)));

	b = connect(&aimlEngine, SIGNAL(addBotName(const QString &)),
		        this, SIGNAL(addBotName(const QString &)));

    b = connect(&aimlEngine, SIGNAL(loading()),
		        this, SIGNAL(loading()));

	b = connect(&aimlEngine, SIGNAL(doneLoading()),
		        this, SIGNAL(doneLoading()));

	b = connect(this, SIGNAL(userInput(const QString &)),
		        &aimlEngine, SLOT(userInput(const QString &)));

	b = connect(this, SIGNAL(clearAIML()),
		        &aimlEngine, SLOT(clearAIML()));

	b = connect(this, SIGNAL(addFile(const QString &)),
		        &aimlEngine, SLOT(addFile(const QString &)));

	b = connect(this, SIGNAL(addDirectory(const QString &)),
		        &aimlEngine, SLOT(addDirectory(const QString &)));

	/*
	 * Load the default annotated alice initially 
	 * so we don't have a GUI with nothing loaded 
	 * to start with.
	 */
	Arguments *arguments = Arguments::getInstance();
	emit addDirectory(arguments->getAimlDirectory().c_str());

	/*
	 * Input into the bot the word, "connect" to 
	 * start it out with.
	 */
	emit userInput("connect"); 
	
	//start the QT event loop on this thread.
	exec();
}

} //end of qtgui namespace 
