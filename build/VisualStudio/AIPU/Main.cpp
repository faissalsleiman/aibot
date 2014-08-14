// pointers to base class
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <vector>

#include "ShortTermMemory.h"
#include "RobotStructure.h"


using namespace std;
using namespace std::chrono;

//Comment out "#define DEBUGGING_ENABLED" to disable debugging
#define DEBUGGING_ENABLED
#ifdef DEBUGGING_ENABLED //if variable "#define DEBUGGING_ENABLED" is defined, then enable debugging
#define DEBUG_MSG(str) do { cout << str ; } while( false )
#else
#define DEBUG_MSG(str) do { } while( false )
#endif


#pragma region FUNCTIONS DECLARATION

void printSTMRecordType(STMRecord * inputRecord) //This is a test function that simply prints the type of Record
{
	if (inputRecord == NULL)
	{
		DEBUG_MSG("**POINTER TO NULL**" << endl);
		return;
	}
	switch (inputRecord->getRecordType())
	{
	case STMRecordType::SPEECH_INPUT:
		DEBUG_MSG("SPEECH_INPUT" << endl);
		break;
	case STMRecordType::FACE_DETECTION:
		DEBUG_MSG("FACE_DETECTION" << endl);
		break;
	case STMRecordType::SOUND_DETECTION:
		DEBUG_MSG("SOUND_DETECTION" << endl);
		break;
	case STMRecordType::SKELETAL_DETECTION:
		DEBUG_MSG("SKELETAL_DETECTION" << endl);
		break;
	case STMRecordType::THERMAL_DETECTION:
		DEBUG_MSG("THERMAL_DETECTION" << endl);
		break;
	case STMRecordType::HAND_GESTURE:
		DEBUG_MSG("HAND_GESTURE" << endl);
		break;
	case STMRecordType::APP_COMMANDER:
		DEBUG_MSG("APP_COMMANDER" << endl);
		break;
	case STMRecordType::SLAM:
		DEBUG_MSG("SLAM" << endl);
		break;
	case STMRecordType::OBJECTIVE:
		DEBUG_MSG("OBJECTIVE" << endl);
		break;
	case STMRecordType::OBSTACLE_DETECTION:
		DEBUG_MSG("OBSTACLE_DETECTION" << endl);
		break;
	case STMRecordType::OBJECT_RECOGNITION:
		DEBUG_MSG("OBJECT_RECOGNITION" << endl);
		break;
	case STMRecordType::FACE_RECOGNITION:
		DEBUG_MSG("FACE_RECOGNITION" << endl);
		break;
	default:
		DEBUG_MSG("UNRECOGNIZED STM RECORD TYPE" << endl);
		break;

	}
}

vector<string> getSubStrings(string input , char delimiter) //Returns a vector of substrings from the input string based on a delimter, for example to separate Hello,1,1 by the delimiter ","
{
	istringstream ss(input);
	string token;
	vector<string> returnedVectorofStrings; // Empty on creation
	while (std::getline(ss, token, delimiter)) {
		returnedVectorofStrings.push_back(token);
	}

	return returnedVectorofStrings;
}



#pragma endregion FUNTIONS DECLARATION

#pragma region VARIABLES DECLARATION

enum AIPUSTATE { //State of the AIPU is kept in this variable
	IDLE = 0,
	SOUND_DETECTED,
	LOCATING_SPEAKER,
	AWAITING_KICKOFF_PHRASE,
	ENGAGED_IN_COVERSATION,
	CHARGING_BATTERY,
	PROCESSING_DATA
};
AIPUSTATE currentAIPUState;
ShortTermMemory *AIPU_STM;
RobotStructure * robot;

#pragma endregion VARIABLES DECLARATION





void STMServerThread()
{
	//Wait for incoming connections from Functional Blocks
	STMRecordType incomingConnection = STMRecordType::SPEECH_INPUT; //these are temp until actual code is written
	string inputFromFunctionalBlock;  //these are temp until actual code is written

	switch (incomingConnection)
	{
		case STMRecordType::SPEECH_INPUT:
		{
			DEBUG_MSG("SPEECH_INPUT" << endl);
			vector<string> serverInputSubStrings = getSubStrings(inputFromFunctionalBlock, ','); //convert comma separated input into usable substrings
			if (serverInputSubStrings.size() != 3)
			{
				DEBUG_MSG("SYNTAX RECEIVED FROM FUNCTIONAL BLOCK IS INCORRECT!" << endl);
				break;
			}
			string transcriptionText = serverInputSubStrings[0]; 
			int transcriptionAccuracy = atoi(serverInputSubStrings[1].c_str());
			int transcriptionLoudness = atoi(serverInputSubStrings[2].c_str());
			SpeechRecord *incomingSpeech = new SpeechRecord(transcriptionText, transcriptionAccuracy, transcriptionLoudness); // get input and create 
			AIPU_STM->inputRecord(static_cast<STMRecord*>(incomingSpeech));
			
			break;
		}
		case STMRecordType::FACE_DETECTION:
			DEBUG_MSG("FACE_DETECTION" << endl);
			break;
		case STMRecordType::SOUND_DETECTION:
			DEBUG_MSG("SOUND_DETECTION" << endl);
			break;
		case STMRecordType::SKELETAL_DETECTION:
			DEBUG_MSG("SKELETAL_DETECTION" << endl);
			break;
		case STMRecordType::THERMAL_DETECTION:
			DEBUG_MSG("THERMAL_DETECTION" << endl);
			break;
		case STMRecordType::HAND_GESTURE:
			DEBUG_MSG("HAND_GESTURE" << endl);
			break;
		case STMRecordType::APP_COMMANDER:
			DEBUG_MSG("APP_COMMANDER" << endl);
			break;
		case STMRecordType::SLAM:
			DEBUG_MSG("SLAM" << endl);
			break;
		case STMRecordType::OBJECTIVE:
			DEBUG_MSG("OBJECTIVE" << endl);
			break;
		case STMRecordType::OBSTACLE_DETECTION:
			DEBUG_MSG("OBSTACLE_DETECTION" << endl);
			break;
		case STMRecordType::OBJECT_RECOGNITION:
			DEBUG_MSG("OBJECT_RECOGNITION" << endl);
			break;
		case STMRecordType::FACE_RECOGNITION:
			DEBUG_MSG("FACE_RECOGNITION" << endl);
			break;
		default:
			DEBUG_MSG("UNRECOGNIZED STM RECORD TYPE" << endl);
			break;
	}
	

	//Process Data and Put into STM

}


int main() {
	//Initialize Functional Blocks, Represented in Code as Threads

	AIPU_STM = new ShortTermMemory(); // Initialize Short Term Memory Structure

	currentAIPUState = AIPUSTATE::IDLE; //Initialize the state of the AIPU to IDLE

	robot = new RobotStructure();
	

	//Read Data from STM (Short-Term-Memory) based on State
	//Process STM Data
	//Take Action

	switch (currentAIPUState)
	{
		case AIPUSTATE::IDLE:
			{
				/*
				if a face is detected move to engaged in convo within 1-2 sec
				if kcikoff phrase received in good accuracy then go to engaged in convo
				*/
				break;
			}
		case AIPUSTATE::SOUND_DETECTED:
			{
				break;
			}
		case AIPUSTATE::LOCATING_SPEAKER:
			{
				/*
				
				if a face is detected move to engaged in convo

				*/
				break;
			}
		case AIPUSTATE::AWAITING_KICKOFF_PHRASE:
			{
				/*
				if a face is detected move to engaged in convo within 1-2 sec
				if a hand gesture is detected within 1-2 sec then move to in convo
				if kcikoff phrase received in good accuracy then go to engaged in convo
				*/
				break;
			}
		case AIPUSTATE::ENGAGED_IN_COVERSATION:
			{
				/*
				no speech input in 5 seconds then go back to idle
				if no eye contact in the last 5 seconds then go back to idle
				if sound is detected from another source then ignore it
				keep track of face and maintain eye contact with it

				*/
				break;
			}
		case AIPUSTATE::CHARGING_BATTERY:
			{
				break;
			}
		case AIPUSTATE::PROCESSING_DATA:
			{
				 break;
			}
		default:
			{
				break;
			}

	}
	

	//Clean STM
	
	
	
	//THE BELOW CODE IS ALL FOR TESTING WHILE CODING (TO BE DELETED LATER)
	
	DEBUG_MSG("*******************" << endl);

	//TEST CREATION AND RETREIVAL OF TIMESTAMP
	SpeechRecord *temp = new SpeechRecord("hello", 0, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(22));
	DEBUG_MSG("time: " << temp->getTimeRelativeToNowInMilliSeconds() << endl);

	DEBUG_MSG("*******************" << endl);

	
	//Short Term Memory Handling Tests

	ShortTermMemory *AIPU_STM = new ShortTermMemory();

	DEBUG_MSG("TEST 1 - Creating STM Records " << endl);
	for (int i = 0; i < AIPU_STM->getSTMSize(); i++)
	{
		SpeechRecord *incomingSpeech = new SpeechRecord("hello", i, i);
		AIPU_STM->inputRecord(static_cast<STMRecord*>(incomingSpeech));
	}

	for (int i = 0; i < AIPU_STM->getSTMSize(); i++) //overwrite them all
	{
		SpeechRecord *incomingSpeech = new SpeechRecord("hi there!!", i, i);
		AIPU_STM->inputRecord(static_cast<STMRecord*>(incomingSpeech));
	}

	DEBUG_MSG("TEST 2 -Printing " << endl);
	for (int i = 0; i < AIPU_STM->getSTMSize(); i++)
	{
		DEBUG_MSG(i << " : ");
		printSTMRecordType(AIPU_STM->getSTMRecord(i));
	}
	


	DEBUG_MSG("*******************" << endl);
	//STM TESTING TRIALS casting pointers
	SpeechRecord *speech1 = new SpeechRecord("hello", 0, 0);
	SpeechRecord * speech2  = NULL;

	STMRecord * record1 = speech1;
	
	switch (record1->getRecordType())
	{
		case STMRecordType::SPEECH_INPUT:
			DEBUG_MSG("SPEECH INPUT" << endl);
			speech2 = static_cast<SpeechRecord*>(record1);
			break;
		default:
			DEBUG_MSG("DEFAULT" << endl);
			break;
			
	}
	
	switch (speech2->getRecordType())
	{
	case STMRecordType::SPEECH_INPUT:
		DEBUG_MSG("SPEECH INPUT" << endl);
		speech2 = static_cast<SpeechRecord*>(record1);
		break;
	default:
		DEBUG_MSG("DEFAULT" << endl);
		break;

	}

	
	DEBUG_MSG("Press any Key to Exit" << endl);
	int x;
	std::cin >> x;

	return 0;
}












/*
robot->RightArm->Shoulder->enabletorque(false);
robot->RightArm->armTwist->enabletorque(false);
robot->RightArm->Elbow->enabletorque(false);
robot->RightArm->Gripper->enabletorque(false);

while (true)
{


robot->RightArm->Shoulder->setPosition(512, 256);
robot->RightArm->armTwist->setPosition(512, 256);
robot->RightArm->Elbow->setPosition(512, 256);
robot->RightArm->Gripper->setPosition(512, 256);

for (int i = 0; i < 10; i++)
{

int flag = 0;
while (robot->RightArm->Elbow->isMoving())
{
robot->RightArm->Elbow->setCurrentParameters();
if (flag == 0)
{
if (robot->RightArm->Elbow->position < 825)
{
robot->RightArm->Elbow->setPosition(725, 125);
flag = 1;
}
}
}


robot->RightArm->Shoulder->setPosition(512, 256);
robot->RightArm->armTwist->setPosition(815, 256);
robot->RightArm->Elbow->setPosition(845, 256);
robot->RightArm->Gripper->setPosition(722, 256);

flag = 0;
while (robot->RightArm->Elbow->isMoving())
{
robot->RightArm->Elbow->setCurrentParameters();
if (flag == 0)
{
if (robot->RightArm->Elbow->position > 750)
{
robot->RightArm->Elbow->setPosition(845, 125);
flag = 1;
}
}
}

robot->RightArm->Shoulder->setPosition(512, 256);
robot->RightArm->armTwist->setPosition(815, 256);
robot->RightArm->Elbow->setPosition(725, 256);
robot->RightArm->Gripper->setPosition(395, 256);
}

while (robot->RightArm->isMoving())
{
}

robot->RightArm->Shoulder->setPosition(512, 256);
robot->RightArm->armTwist->setPosition(512, 256);
robot->RightArm->Elbow->setPosition(512, 256);
robot->RightArm->Gripper->setPosition(512, 256);

//robot->RightArm->setCurrentParameters();
//cout << robot->RightArm->Shoulder->position << ",";
//cout << robot->RightArm->armTwist->position << ",";
//cout << robot->RightArm->Elbow->position << ",";
//cout << robot->RightArm->Gripper->position << endl;


std::this_thread::sleep_for(std::chrono::milliseconds(2000));

}
*/
