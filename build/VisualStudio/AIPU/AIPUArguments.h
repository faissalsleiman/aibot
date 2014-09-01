
#include <iostream>

#include <string>
#include "rebecca.h"
#include "continuous.h"

using namespace std;
using std::string;


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



/**
* Parses and sets the
* arguments for main().
*/
class RebeccaArguments
{
public:

	/**
	* Constructor that
	* sets the arguments up
	* from main() as well
	* as the program name its
	* self.
	*
	* \param argc The number of arguments
	* sent in.
	*
	* \param args The array of arguments
	*/
	RebeccaArguments(int argc, char* argv[])
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
	}


	/**
	* Returns binary's name
	*/
	string getExeName() const
	{
		return m_exeName;
	}

	/**
	* Returns the configuration
	* directory that has been set.
	*
	* \return The configuration directory
	* where needed configuration files
	* are stored.
	*/
	string getConfigurationDirectory() const
	{
		return m_configurationDirectory;
	}

	/**
	* Returns the AIML
	* directory that has been set.
	*
	* \return The AIML directory
	* where aiml files are stored.
	*/
	string getAimlDirectory() const
	{
		return m_aimlDirectory;
	}

	/**
	* Returns the AIML schema
	* path that has been set.
	*
	* \return The AIML schema
	* path that has been set.
	*/
	string getAimlSchemaPath() const
	{
		return m_aimlSchemaPath;
	}

	/**
	* Returns the common types
	* schema path that has been set.
	*
	* \return The common types
	* schema path that has been set.
	*/
	string getCommonTypesSchemaPath() const
	{
		return m_commonTypesSchemaPath;
	}

	/**
	* Returns the bot configuration
	* schema path that has been set.
	*
	* \return the bot configuration
	* schema path that has been set.
	*/
	string getBotConfigurationSchemaPath() const
	{
		return m_botConfigurationSchemaPath;
	}

	/**
	* Enumeration of possible switches you
	* can give rebecca
	*/
	enum arguments{
		NO_ARG, AIML, AIML_SCHEMA,
		COMMON_SCHEMA, BOT_SCHEMA,
		CONFIGURATION
	};
	/**
	* The current argument state.
	*/
	arguments m_currentArgument;

	/**
	* This binary's name.
	*/
	string m_exeName;

	/**
	* The location of RebeccaAIML's
	* configuration directory.
	*
	* If this is not set, it will default
	* to the current working directory
	* + "../../conf".  This is where
	* needed configuration files are
	* stored.
	*/
	string m_configurationDirectory;

	/**
	* The location of a AIML directory.
	*
	* If this is not set, it will default
	* to the current working directory
	* + "../../aiml/annotated_alice".
	*/
	string m_aimlDirectory;

	/**
	* The path to the aiml xsd file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../../resources/schema/AIML.xsd"
	*/
	string m_aimlSchemaPath;

	/**
	* The path to the the common types
	* schema file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../resources/schema/common-types.xsd"
	*/
	string m_commonTypesSchemaPath;

	/**
	* The path to the bot configuration
	* schema file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../resources/schema/bot-configuration.xsd"
	*/
	string m_botConfigurationSchemaPath;

	cmd_ln_t *ps_config;
};


class PocketSphinxArguments
{
public:

	/**
	* Constructor that
	* sets the arguments up
	* from main() as well
	* as the program name its
	* self.
	*
	* \param argc The number of arguments
	* sent in.
	*
	* \param args The array of arguments
	*/
	PocketSphinxArguments(int argc, char* argv[])
	{
		//Variables to store Pocketsphinx args
		int ps_argc = 1; //Start with 0 args for Pocketsphinx (1 for program name)
		char **ps_argv = new char*[argc]; //Enough space to hold all args
		ps_argv[0] = argv[0]; //Program name is always passed on

		for (int i = 1; i < argc; ++i)
		{
			//Aggregate this arg for pocketsphinx
			ps_argv[ps_argc] = argv[i];
			ps_argc++;
		}

		//Pass remaining arguments to Pocketsphinx
		char const *cfg;

		if (ps_argc == 2) {
			ps_config = cmd_ln_parse_file_r(NULL, cont_args_def, ps_argv[1], TRUE);
		}
		else {
			ps_config = cmd_ln_parse_r(NULL, cont_args_def, ps_argc, ps_argv, TRUE);
		}
		// Handle argument file as -argfile.
		if (ps_config && (cfg = cmd_ln_str_r(ps_config, "-argfile")) != NULL) {
			ps_config = cmd_ln_parse_file_r(ps_config, cont_args_def, cfg, FALSE);
		}
		if (ps_config == NULL)
			exit(1);
	}


	/**
	* Returns binary's name
	*/
	string getExeName() const
	{
		return m_exeName;
	}

	/**
	* Returns the configuration
	* directory that has been set.
	*
	* \return The configuration directory
	* where needed configuration files
	* are stored.
	*/
	string getConfigurationDirectory() const
	{
		return m_configurationDirectory;
	}

	/**
	* Returns the AIML
	* directory that has been set.
	*
	* \return The AIML directory
	* where aiml files are stored.
	*/
	string getAimlDirectory() const
	{
		return m_aimlDirectory;
	}

	/**
	* Returns the AIML schema
	* path that has been set.
	*
	* \return The AIML schema
	* path that has been set.
	*/
	string getAimlSchemaPath() const
	{
		return m_aimlSchemaPath;
	}

	/**
	* Returns the common types
	* schema path that has been set.
	*
	* \return The common types
	* schema path that has been set.
	*/
	string getCommonTypesSchemaPath() const
	{
		return m_commonTypesSchemaPath;
	}

	/**
	* Returns the bot configuration
	* schema path that has been set.
	*
	* \return the bot configuration
	* schema path that has been set.
	*/
	string getBotConfigurationSchemaPath() const
	{
		return m_botConfigurationSchemaPath;
	}

	/**
	* Enumeration of possible switches you
	* can give rebecca
	*/
	enum arguments{
		NO_ARG, AIML, AIML_SCHEMA,
		COMMON_SCHEMA, BOT_SCHEMA,
		CONFIGURATION
	};
	/**
	* The current argument state.
	*/
	arguments m_currentArgument;

	/**
	* This binary's name.
	*/
	string m_exeName;

	/**
	* The location of RebeccaAIML's
	* configuration directory.
	*
	* If this is not set, it will default
	* to the current working directory
	* + "../../conf".  This is where
	* needed configuration files are
	* stored.
	*/
	string m_configurationDirectory;

	/**
	* The location of a AIML directory.
	*
	* If this is not set, it will default
	* to the current working directory
	* + "../../aiml/annotated_alice".
	*/
	string m_aimlDirectory;

	/**
	* The path to the aiml xsd file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../../resources/schema/AIML.xsd"
	*/
	string m_aimlSchemaPath;

	/**
	* The path to the the common types
	* schema file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../resources/schema/common-types.xsd"
	*/
	string m_commonTypesSchemaPath;

	/**
	* The path to the bot configuration
	* schema file.
	*
	* If this is not set, it will default
	* to the current working directory +
	* "../resources/schema/bot-configuration.xsd"
	*/
	string m_botConfigurationSchemaPath;

	cmd_ln_t *ps_config;
};

