#ifndef AIBOT_MAIN_H
#define AIBOT_MAIN_H

#include <string>

#include "continuous.h"

using std::string;

/**
* Parses and sets the
* arguments for main().
*/
class Arguments
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
	Arguments(int argc, char* args[]);
	
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

#endif