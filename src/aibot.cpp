#include <iostream>
#include <sapi.h>
using namespace std;

#include "aibot.h"
#include "continuous.h"
#include "rebecca.h"

//Pocketsphinx options declared here
static const arg_t cont_args_def[] = {
	POCKETSPHINX_OPTIONS,
	/* Argument file. */
	{ "-argfile",
	ARG_STRING,
	NULL,
	"Argument file giving extra arguments." },
	{ "-adcdev",
	ARG_STRING,
	NULL,
	"Name of audio device to use for input." },
	{ "-infile",
	ARG_STRING,
	NULL,
	"Audio file to transcribe." },
	{ "-time",
	ARG_BOOLEAN,
	"no",
	"Print word times in file transcription." },
	CMDLN_EMPTY_OPTION
};

//Arguments constructor implementation
//Parses options for both Rebecca and Pocketsphinx
Arguments::Arguments(int argc, char* argv[])
: m_exeName(string(argv[0])),
m_aimlSchemaPath("../../../../config/rebecca/resources/schema/AIML.xsd"),
m_commonTypesSchemaPath("../../../config/rebecca/resources/schema/common-types.xsd"),
m_botConfigurationSchemaPath("../../../config/rebecca/resources/schema/bot-configuration.xsd"),
m_configurationDirectory("../../../../config/rebecca/conf"),
m_aimlDirectory("../../../../config/rebecca/aiml/annotated_aibot"),
m_currentArgument(NO_ARG)
{
	/*
	* Will iterate over args to extract Rebecca args
	* and pass the rest of the args to Pocketsphinx
	*/

	//Variables to store Pocketsphinx args
	int ps_argc = 1; //Start with 0 args for Pocketsphinx (1 for program name)
	char **ps_argv = new char*[argc]; //Enough space to hold all args
	ps_argv[0] = argv[0]; //Program name is always passed on

	/*
	* Iterate over the arguments
	* and set them
	*/
	for (int i = 1; i < argc; ++i)
	{
		//get string of the argument
		string argument(argv[i]);

		if (m_currentArgument == NO_ARG)
		{
			if (argument == "-aimlSchema" ||
				argument == "-as")
			{
				m_currentArgument = AIML_SCHEMA;
			}
			else if (argument == "-botSchema" ||
				argument == "-bs")
			{
				m_currentArgument = BOT_SCHEMA;
			}
			else if (argument == "-commonSchema" ||
				argument == "-cs")
			{
				m_currentArgument = COMMON_SCHEMA;
			}
			else if (argument == "-configurationDirectory" ||
				argument == "-cd")
			{
				m_currentArgument = CONFIGURATION;
			}
			else if (argument == "-aimlDirectory" ||
				argument == "-ad")
			{
				m_currentArgument = AIML;
			}
			else if (argument == "-help" ||
				argument == "-h" ||
				argument == "/?" ||
				argument == "--help")
			{
				/*
				* Display help and exit
				*/
				cout << endl << endl
					<< "[aibot.exe help]" << endl
					<< "------------------" << endl << endl
					<< "Available Rebecca switches:" << endl << endl
					<< "[-aimlSchema or -as]" << endl
					<< "    AIML Schema Path (default is ../../resources/schema/AIML.xsd)" << endl << endl
					<< "[-botSchema or -bs] " << endl
					<< "    Bot Schema Path (default is ../resources/schema/bot-configuration.xsd)" << endl << endl
					<< "[-commonSchema or -cs] " << endl
					<< "    Common Schema Path (default is ../resources/schema/common-types.xsd)" << endl << endl
					<< "[-configurationDirectory or -cd] " << endl
					<< "    Configuration directory (default is ../../conf)" << endl << endl
					<< "[-aimlDirectory or -ad] " << endl
					<< "    AIML directory with *.aiml files (default is ../../aiml/annotated_aibot)" << endl << endl
					<< endl;
				exit(0);
			}
			else
			{
				//Aggregate this arg for pocketsphinx
				ps_argv[ps_argc] = argv[i];
				ps_argc++;
			}
		}
		else
		{
			/*
			* We already encountered the switch,
			* now we just need to set the argument
			*/
			if (m_currentArgument == AIML)
			{
				m_aimlDirectory = argument;
			}
			else if (m_currentArgument == AIML_SCHEMA)
			{
				m_aimlSchemaPath = argument;
			}
			else if (m_currentArgument == BOT_SCHEMA)
			{
				m_botConfigurationSchemaPath = argument;
			}
			else if (m_currentArgument == COMMON_SCHEMA)
			{
				m_commonTypesSchemaPath = argument;
			}
			else if (m_currentArgument == CONFIGURATION)
			{
				m_configurationDirectory = argument;
			}
			else
			{
				cout << "Programmer error "
					"this should not be reached"
					<< endl;
			}

			m_currentArgument = NO_ARG;
		}
	}

	//Pass remaining arguments to Pocketsphinx
	char const *cfg;

	if (ps_argc == 2) {
		ps_config = cmd_ln_parse_file_r(NULL, cont_args_def, ps_argv[1], TRUE);
	}
	else {
		ps_config = cmd_ln_parse_r(NULL, cont_args_def, ps_argc, ps_argv, TRUE);
	}
	/* Handle argument file as -argfile. */
	if (ps_config && (cfg = cmd_ln_str_r(ps_config, "-argfile")) != NULL) {
		ps_config = cmd_ln_parse_file_r(ps_config, cont_args_def, cfg, FALSE);
	}
	if (ps_config == NULL)
		exit(1);
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

int main(int argc, char* argv[])
{
	Arguments arguments(argc, argv);

	//Initialize Pocketsphinx
	mic_data_t mic;

	continuous_init(arguments, mic);

	//Initialize Voice
	ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

	if (SUCCEEDED(hr))
		std::cout << "Speech Initialized" << std::endl;

	//Initialize Rebecca
	AimlFacade aiml;
	GraphBuilder &builder = aiml.getGraphBuilder();
	myCallBacks callback;
	builder.setCallBacks(&callback);
	
	rebecca_init(arguments, builder);

	//Main code
	try
	{
		/*
		* Send a initial conversation of "connect" to
		* annotated alice and get the response.
		*/
		StringPimpl response = builder.getResponse("connect");

		/*
		* Get the botName which should be Rebecca since that is
		* the name give in the configuration file properties.xml
		* which we parsed above.
		*/
		string botName = builder.getBotPredicate("name").c_str();

		//Send the initial opening line of the bot
		cout << botName << " says: " << response.c_str() << endl;
		hr = pVoice->Speak(s2ws(response.c_str()).c_str(), 0, NULL);
		pVoice->WaitUntilDone(15000);

		/*
		* The main loop to get the input
		* from the user until the user types '/exit'
		*/
		while (true)
		{
			getUtterance(mic);
			string input = string(mic.hyp);
			//string input;
			//getline(cin, input);

			if (input == "/exit" || input == "GOOD NIGHT")
			{
				/*
				* The user wants to exit so break
				* out of the while(true) loop
				*/
				continuous_exit(mic);
				pVoice->Release();
				pVoice = NULL;
				::CoUninitialize();
				break;
			}
			else //The user gave an input to the bot
			{
				//Here we get some internal Rebecca information.
				cout << endl
					<< "Internal information:" << endl
					<< "=====================" << endl
					<< input << " : "
					<< builder.getThat().c_str() << " : "
					<< builder.getTopic().c_str() << endl;

				/*
				* Ahhh finally.  We give the user input to Rebecca Aiml's loaded
				* AIML and get the response back.
				*/
				StringPimpl response = builder.getResponse(input.c_str());

				cout << "=====================" << endl << endl;

				//Print out what Rebecca says.
				cout << botName << " says: " << response.c_str() << endl;
				hr = pVoice->Speak(s2ws(response.c_str()).c_str(), 0, NULL);
				pVoice->WaitUntilDone(15000);
			}
		}
	}
	catch (Exception &e)
	{
		cout << "[An unknown exception occured, Terminating program]" << endl;
		cout << "[" << e.what() << "]";
		return 1;
	}

	//Everything smooth.  Exit normally.
	return 0;
}
