#include "rebecca/TestCases.h"
#include "rebecca/Arguments.h"
using namespace rebecca;

#include <iostream>
using namespace std;

/*
 * Initialize our static variable that
 * holds our singleton instance for Arguments.h.
 */
Arguments *Arguments::m_instance = 0;

int main (int argc, char* argv[]) 
{
	try
	{
        Arguments::setArguments(argc, argv);
		Arguments *arguments = Arguments::getInstance();
		TestCases test("regressionTest.htm");
		test.addAimlFile(arguments->getResourcesDirectory() + "/testing/AIML.aiml");
		test.addTestFile(arguments->getResourcesDirectory() + "/testing/AIML.xml");
		test.createAimlGraph();
		test.conductTesting();
	}
	catch(Exception &e)
	{
		cout << e.what() << endl;
	}	
	return 0;
}

