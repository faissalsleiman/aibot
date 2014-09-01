//Environment Variables that need to be created
//BOOST_INCLUDE
//BOOST_LIB
//BOOST_LIBD
//DYNAMIXEL
//OPENCV_DIR
//XERCES_INCLUDE
//XERCES_LIB
//XERCES_LIBD

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

//OpenCV includes, this is for face recognition to work
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Windows Socket Includes for the server
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

//Microsoft Speech API (for Text-To-Speech (TTS) Engine)
#include <sapi.h>

//Rebecca AIML Parser
#include "rebecca.h"

//CMU PocketSphinx
#include "continuous.h"

//Arguement classes used to handle RebeccaAIML and Pocketsphinx
#include "AIPUArguments.h"

//AIPU Structures
#include "ShortTermMemory.h"
#include "RobotStructure.h"
#include "TTSTcpClient.h"


using namespace std;
using namespace std::chrono;
using namespace cv;

//Comment out "#define DEBUGGING_ENABLED" to disable debugging
#define DEBUGGING_ENABLED
#ifdef DEBUGGING_ENABLED //if variable "#define DEBUGGING_ENABLED" is defined, then enable debugging
#define DEBUG_MSG(str) do { cout << str ; } while( false )
#else
#define DEBUG_MSG(str) do { } while( false )
#endif

#pragma region VARIABLES DECLARATION

ShortTermMemory *AIPU_STM;
RobotStructure * robot;

//Global Variables for Face Recognition Functional Block
const int CAPTUREWIDTH = 640; //in pixels
const int CAPTUREHEIGHT = 480; //in pixels
const double XCAPTUREVIEWINGANGLE = 78;
const double YCAPTUREVIEWINGANGLE = 45;
//

//Global Variables defining App Communicator socket server parameters
#define DEFAULT_APP_COMMUNICATOR_PORT 27005
#define DEFAULT_APP_COMMUNICATOR_BUFFER_LENGTH    512
//

//Global Variable for Text-To-Speech TTS Engine
//Why are we running TTS as a server so it wont hang the main program, and becuase it might run on a diff. machine in the future
#define DEFAULT_TTS_ENGINE_PORT 27006
#define DEFAULT_TTS_ENGINE_BUFFER_LENGTH    512

//Global Variable for RebeccaAIML
GraphBuilder *builder_ptr;


#pragma endregion VARIABLES DECLARATION

#pragma region STM FUNCTIONS DECLARATION

void printSTMRecordType(STMRecord * inputRecord) //This is a test function that simply prints the type of Record
{
	if (inputRecord == NULL)
	{
		DEBUG_MSG("**POINTER TO NULL**" << endl);
		return;
	}
	else
	{
		DEBUG_MSG(inputRecord->getRecordTypeString() << endl);
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

#pragma endregion STM FUNTIONS DECLARATION

#pragma region FACE RECOGNITION Engine
double getFaceDistance(int faceWidth, int faceHeight)
{
	return ((double)CAPTUREWIDTH / faceWidth) * (double)18;

	//NOTE: if a new camera is used, the formula must be re-calibrated
	//FORMULA: f = d*Z / D
	//d = faceWidth in Pixels
	//Z = Distance to Face
	//D = Actual Face Width
	//f = Capture Width in Pixels
}

void faceRecognizer()
{
	//create the cascade classifier object used for the face detection
	CascadeClassifier face_cascade;
	//use the haarcascade_frontalface_alt.xml library
	face_cascade.load("..\\..\\..\\config\\Opencv\\haarcascade_frontalface_alt.xml");

	//setup video capture device and link it to the first capture device
	VideoCapture captureDevice;

	captureDevice.open(0);
	//Set Dimensions
	captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, CAPTUREHEIGHT);
	captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, CAPTUREWIDTH);

	//setup image files used in the capture process
	Mat captureFrame;
	Mat grayscaleFrame;

	//create a window to present the results
	namedWindow("outputCapture", 1);

	//create a loop to capture and find faces
	while (true)
	{
		//Why capture multiple frames, testing revealed that if this is not done, we do not get the current capture from the cam
		//capture a new image frame
		captureDevice >> captureFrame;
		//capture a new image frame
		captureDevice >> captureFrame;
		//capture a new image frame
		captureDevice >> captureFrame;
		//capture a new image frame
		captureDevice >> captureFrame;
		//capture a new image frame
		captureDevice >> captureFrame;
		//capture a new image frame
		captureDevice >> captureFrame;

		//convert captured image to gray scale and equalize
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		//create a vector array to store the face found
		std::vector<Rect> faces;

		//find faces and store them in the vector array
		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(35, 35));


		//draw a rectangle for all found faces in the vector array on the original image
		for (int i = 0; i < faces.size(); i++)
		{
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		
			FaceDetectionRecord *recognizedFace = new FaceDetectionRecord(faces[i].width, faces[i].height, faces[i].x + (faces[i].width / 2), faces[i].y + (faces[i].height / 2));
			AIPU_STM->inputRecord(static_cast<STMRecord*>(recognizedFace));

		}

		//print the output
		imshow("outputCapture", captureFrame);

		//pause for X-ms
		waitKey(10);
	}
}
#pragma endregion FACE RECOGNITION Engine

#pragma region SOCKET SERVER FOR APP COMMUNICATOR
int socketServer()
{
	WSADATA wsa;
	SOCKET serverSocket, clientSocket;
	struct sockaddr_in server, client;
	int c;
	char *message;

	DEBUG_MSG("Initializing App Communicator Socket..." << endl);
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0)
	{
		DEBUG_MSG("Failed. Error Code : " << WSAGetLastError() << endl);
		return 1;
	}

	DEBUG_MSG("App Communicator Socket Initialized" << endl);
	//Create a socket
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		DEBUG_MSG("Could Not Create App Communicator Socket : " << WSAGetLastError() << endl);
	}

	DEBUG_MSG("App Communicator Socket Created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(DEFAULT_APP_COMMUNICATOR_PORT);

	//Bind
	if (::bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		DEBUG_MSG("Bind failed for App Communicator Socket with error code : " << WSAGetLastError() << endl);
		exit(EXIT_FAILURE);
	}

	DEBUG_MSG("Bind App Communicator Socket Done" << endl);

	
	while (true)
	{
		//Listen to incoming connections
		listen(serverSocket, 3);

		//Accept and incoming connection
		DEBUG_MSG("Waiting for incoming connections on App Communicator Socket..." << endl);

		c = sizeof(struct sockaddr_in);
		clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);

		if (clientSocket != INVALID_SOCKET)
		{
			DEBUG_MSG("Connection accepted on App Communicator Socket" << endl;);

			char recvbuf[DEFAULT_APP_COMMUNICATOR_BUFFER_LENGTH];
			int iSendResult;

			// reveice until the client shutdown the connection
			do {
				iResult = recv(clientSocket, recvbuf, DEFAULT_APP_COMMUNICATOR_BUFFER_LENGTH, 0);
				if (iResult > 0)
				{
					char msg[DEFAULT_APP_COMMUNICATOR_BUFFER_LENGTH];
					memset(&msg, 0, sizeof(msg));
					strncpy_s(msg, recvbuf, iResult);

					DEBUG_MSG("Received: " << msg << endl);

					AppCommanderRecord *inputCommand = new AppCommanderRecord(msg);
					AIPU_STM->inputRecord(static_cast<STMRecord*>(inputCommand));

					iSendResult = send(clientSocket, recvbuf, iResult, 0);

					if (iSendResult == SOCKET_ERROR)
					{
						DEBUG_MSG("send failed: " << WSAGetLastError() << endl);
						closesocket(clientSocket);
						WSACleanup();
						return 1;
					}

					DEBUG_MSG("Bytes sent: " << iSendResult << endl);
				}
				else if (iResult == 0)
				{
					DEBUG_MSG("Connection closed\n");
				}
				else
				{
					DEBUG_MSG("recv failed: " << WSAGetLastError() << endl);
					//closesocket(serverSocket);
					//WSACleanup();
				}
			} while (iResult > 0);
		}
	}
	return 1;
}
#pragma endregion SOCKET SERVER FOR APP COMMUNICATOR

#pragma region Text-To-Speech Engine

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

int TTSEngineServer()
{
	ISpVoice * pVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

	if (SUCCEEDED(hr))
	{
		DEBUG_MSG("Speech Initialized" << endl);
	}
	else
	{
		return 1;
	}

	string str = "Robot Online";
	pVoice->Speak(s2ws(str).c_str(), SPF_DEFAULT, NULL);
	pVoice->WaitUntilDone(15000);

	WSADATA wsa;
	SOCKET serverSocket, clientSocket;
	struct sockaddr_in server, client;
	int c;
	char *message;

	DEBUG_MSG("Initializing TTS Engine Socket..." << endl);
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0)
	{
		DEBUG_MSG("Failed. Error Code : " << WSAGetLastError() << endl);
		return 1;
	}

	DEBUG_MSG("TTS Engine Socket Initialized" << endl);

	//Create a socket
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		DEBUG_MSG("Could Not Create TTS Engine Socket : " << WSAGetLastError() << endl);
	}

	DEBUG_MSG("TTS Engine Socket Created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(DEFAULT_TTS_ENGINE_PORT);

	//Bind
	if (::bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		DEBUG_MSG("Bind failed for TTS Engine Socket with error code : " << WSAGetLastError() << endl);
		exit(EXIT_FAILURE);
	}

	DEBUG_MSG("Bind TTS Engine Socket Done" << endl);
	while (true)
	{
		//Listen to incoming connections
		listen(serverSocket, 3);

		//Accept and incoming connection
		DEBUG_MSG("Waiting for incoming connections on TTS Engine Socket..." << endl);

		c = sizeof(struct sockaddr_in);
		clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);

		if (clientSocket != INVALID_SOCKET)
		{
			DEBUG_MSG("Connection accepted on TTS Engine Socket" << endl;);

			char recvbuf[DEFAULT_TTS_ENGINE_BUFFER_LENGTH];
			int iSendResult;

			// reveice until the client shutdown the connection
			do {
				iResult = recv(clientSocket, recvbuf, DEFAULT_TTS_ENGINE_BUFFER_LENGTH, 0);
				if (iResult > 0)
				{
					char msg[DEFAULT_TTS_ENGINE_BUFFER_LENGTH];
					memset(&msg, 0, sizeof(msg));
					strncpy_s(msg, recvbuf, iResult);

					DEBUG_MSG("TTS MSG RECEIVED: " << msg << endl);

					string str(msg);
					pVoice->Speak(s2ws(str).c_str(), SPF_DEFAULT, NULL);
					pVoice->WaitUntilDone(15000);
				}
				else if (iResult == 0)
					DEBUG_MSG("Connection closed\n");
				else
				{
					DEBUG_MSG("recv failed: " << WSAGetLastError() << endl);
					//closesocket(serverSocket);
					//WSACleanup();
				}
			} while (iResult > 0);
		}
	}
	return 1;
}

#pragma endregion Text-To-Speech Engine

#pragma region RebeccaAIML Engine

void setupRebeccaAIMLEngine(int argc, char* argv[])
{
	RebeccaArguments arguments(argc, argv);

	GraphBuilder &builder = *builder_ptr;

	rebecca_init(arguments, builder);

	//Main code
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

}

string getRebeccaAIMLresponse(string input)
{
	GraphBuilder &builder = *builder_ptr;
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

	return response.c_str();
}

#pragma endregion RebeccaAIML Engine

#pragma region PocketSphinx Engine

void runPocketSphinxEngine(int argc, char* argv[])
{
	//Initialize Pocketsphinx
	PocketSphinxArguments arguments(argc, argv);

	//Global Variable for PocketSphinx
	mic_data_t mic;

	continuous_init(arguments, mic);

	cout << "POCKETSPHINX ENGINE READY..."  << endl;

	while (true)
	{
		getUtterance(mic);
		string transcription = string(mic.hyp);
		float transcriptionAccuracy = mic.prob;
		if (transcriptionAccuracy > 0.1 && transcription!="")
		{
			SpeechRecord *inputRecord = new SpeechRecord(transcription, transcriptionAccuracy, 100);
			AIPU_STM->inputRecord(static_cast<STMRecord*>(inputRecord));
		}

	}

}


#pragma endregion PocketSphinx Engine


int main() {

	//Initialize Functional Blocks, Represented in Code as Threads
	AIPU_STM = new ShortTermMemory(); // Initialize Short Term Memory Structure

	//Initialize the state of the AIPU to IDLE
	AIPU_STM->setCurrentAIPUState(AIPUSTATE::IDLE);
    
    //Create robot structure of servos for control
	robot = new RobotStructure();
	
	//Start RebeccaAIML Engine
	AimlFacade aiml;
	builder_ptr = &aiml.getGraphBuilder();
	myCallBacks callback;
	builder_ptr->setCallBacks(&callback);
	char* RAEarg[] = { "AIPU.exe", NULL };
	setupRebeccaAIMLEngine(1, RAEarg); // this is a synchronous function

	//Start the Face Recognition functional blocks
	std::thread t1(faceRecognizer); //Face Recognition Engine
	std::thread t2(socketServer); //APP Communicator
	std::thread t3(TTSEngineServer); //Text-To-Speech Engine
	char* argv[] = { "AIPU.exe", "-hmm", "hub4wsj_sc_8k", "-dict", "aibot.dic", "-lm", "aibot.lm", NULL };
	std::thread t4(runPocketSphinxEngine,7, argv); //Speech to Text Engine (PocketSphinx) 
	

    
    //Start State Machine
    //Read Data from STM (Short-Term-Memory) based on State
	//Process STM Data
	//Take Action
	//
	//Important Rule for STM, in any state besides IDLE, once a positive record is hit, you will most likely need to
	//re-set the AIPU state, otherwise it could timeout (depending on the code)

	while (true)
	{
		
		switch (AIPU_STM->getCurrentAIPUState())
		{
			case AIPUSTATE::IDLE:
			{
				//DEBUG_MSG("IDLE STATE" << endl);
				/*
				if a face is detected move to engaged in convo within 1-2 sec
				if kickoff phrase received in good accuracy then go to engaged in convo
				*/
				FaceDetectionRecord *detectedFaceRecord = static_cast<FaceDetectionRecord*>(AIPU_STM->getLatestUnprocessedRecord(STMRecordType::FACE_DETECTION));
				if (detectedFaceRecord == NULL)
				{ //do nothing, rest for 10 ms
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
				else 
				{
					detectedFaceRecord->markAsProcessed();
					AIPU_STM->setCurrentAIPUState(AIPUSTATE::ENGAGED_IN_COVERSATION);
					DEBUG_MSG("READ RECORD: " << detectedFaceRecord->faceXCoordinate << "," << detectedFaceRecord->faceYCoordinate << endl);
				}
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
				if kickoff phrase received in good accuracy then go to engaged in convo
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
				FaceDetectionRecord *detectedFaceRecord = static_cast<FaceDetectionRecord*>(AIPU_STM->getLatestUnprocessedRecord(STMRecordType::FACE_DETECTION));
				if (detectedFaceRecord == NULL) //no face detected
				{
					if (AIPU_STM->getLastAIPUStateChangeTimeRelativeToNowInMilliSeconds() > 3000)
					{
						AIPU_STM->setCurrentAIPUState(AIPUSTATE::IDLE); //go back to idle state
						break;
					}
				}
				else
				{
					detectedFaceRecord->markAsProcessed();
					AIPU_STM->setCurrentAIPUState(AIPUSTATE::ENGAGED_IN_COVERSATION); //reset AIPU State
					//DEBUG_MSG("READ RECORD: " << detectedFaceRecord->faceXCoordinate << "," << detectedFaceRecord->faceYCoordinate << endl);
					/*
					STEPS FOR CALCULATING ANGLE SHIFT for Servo Motor
					1-getFaceDistance() function must be calibrated to get an accurate measurement of planar distance to the face
					2-Shift from center camera must be converted to cm using this formula
					Shift in cm = (tan(camera viewing angle/2) x (planar distance to face in cm) ) x Center ShiftX / (CAPTUREWIDTH/2)
					3-atan(Shift from center / planar distance to face) will give us the angle shift
					NOTE: this result will be in radian
					4-position to set the servo to must be set using the following formula (assuming 512 is center position)
					position to set = (angle calculated in step3 / 1.57) x (unsigned additional servo int value at a 90degree angle)
					the value represents 90degrees converted to radian
					*/

					//CALCULATIONS STEP 1
					double centerShiftX = -(detectedFaceRecord->faceXCoordinate + (detectedFaceRecord->faceWidth / 2) - (CAPTUREWIDTH / 2));
					double centerShiftY = -(detectedFaceRecord->faceYCoordinate + (detectedFaceRecord->faceHeight / 2) - (CAPTUREHEIGHT / 2));
					double planarFaceDistance = getFaceDistance(detectedFaceRecord->faceWidth, detectedFaceRecord->faceHeight);
					DEBUG_MSG("Approx. Distance in cm: " << planarFaceDistance << endl);


					//CALCULATIONS STEP 2
					//note we are multiplying the angel by pi and divided by 180 because we need to work in radians
					double centerShiftXinCM = tan((XCAPTUREVIEWINGANGLE / 2) *3.14159265 / 180) * planarFaceDistance * centerShiftX / (CAPTUREWIDTH / 2);
					double centerShiftYinCM = tan((YCAPTUREVIEWINGANGLE / 2) *3.14159265 / 180) * planarFaceDistance * centerShiftY / (CAPTUREHEIGHT / 2);

					//CALCULATIONS STEP 3
					double angleShiftX = atan(centerShiftXinCM / planarFaceDistance);
					double angleShiftY = atan(centerShiftYinCM / planarFaceDistance);

					//CALCULATIONS STEP 4
					int XServoPositiontoSet = ((angleShiftX / 1.57) * 310);
					int YServoPositiontoSet = ((angleShiftY / 1.57) * 310);

					if (-0.07 > angleShiftX && angleShiftX > 0.07)
					{//do nothing
					}
					else
					{
						//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
						robot->Neck->panServo->setPosition(XServoPositiontoSet + robot->Neck->panServo->position, 128); //;1023 will never be achieved, it will only go to the limit.
					}
					if (-0.02 < angleShiftY && angleShiftY < 0.02)
					{//do nothing
					}
					else
					{
						robot->Neck->tiltServo->setPosition(YServoPositiontoSet + robot->Neck->tiltServo->position, 128); //;1023 will never be achieved, it will only go to the limit.
					}
					do
					{
						robot->Neck->panServo->setCurrentParameters();
						//DEBUG_MSG("Current (Position,Speed,Load,Temperature): (");
						//DEBUG_MSG(robot->Neck->panServo->position);
						//DEBUG_MSG("," << robot->Neck->panServo->speed);
						//DEBUG_MSG("," << robot->Neck->panServo->load);
						//DEBUG_MSG("," << robot->Neck->panServo->temperature << ")" << endl);
						//DEBUG_MSG("Comm Status: " << robot->Neck->panServo->checkCommStatus() << endl);
					} while (robot->Neck->panServo->isMoving());

					do
					{
						robot->Neck->tiltServo->setCurrentParameters();
						//DEBUG_MSG("Current (Position,Speed,Load,Temperature): (");
						//DEBUG_MSG(robot->Neck->tiltServo->position);
						//DEBUG_MSG("," << robot->Neck->tiltServo->speed);
						//DEBUG_MSG("," << robot->Neck->tiltServo->load);
						//DEBUG_MSG("," << robot->Neck->tiltServo->temperature << ")" << endl);
						//DEBUG_MSG("Comm Status: " << robot->Neck->tiltServo->checkCommStatus() << endl);
					} while (robot->Neck->tiltServo->isMoving());

				}

				AppCommanderRecord *appCommanderRecord = static_cast<AppCommanderRecord*>(AIPU_STM->getLatestUnprocessedRecord(STMRecordType::APP_COMMANDER));
				if (appCommanderRecord == NULL)
				{
					//do nothing
				}
				else
				{
					appCommanderRecord->markAsProcessed();
					AIPU_STM->setCurrentAIPUState(AIPUSTATE::ENGAGED_IN_COVERSATION); //reset AIPU State

					//Here send the text to AIML engine
					string AIMLEngineResponse = getRebeccaAIMLresponse(appCommanderRecord->inputCommand);

					//Send MSG to TTS Engine to Speak the command

					TcpClient client("127.0.0.1");

					if (!client.Start(DEFAULT_TTS_ENGINE_PORT))
					{
						DEBUG_MSG("Error Communicating with TTS Engine");
						break;
					}

					client.Send((char*)AIMLEngineResponse.c_str());

					client.Stop();
				}

				//NOTE, fetching a speech record might be an issue if faces are detected very quickly, 
				//the reason is the condition
				//"tempReadRecord->getTimeRelativeToNowInMilliSeconds() > getLastAIPUStateChangeTimeRelativeToNowInMilliSeconds())"
				//since the state is reset at every fsce detection event
				
				SpeechRecord *speechRecord = static_cast<SpeechRecord*>(AIPU_STM->getLatestUnprocessedRecord(STMRecordType::SPEECH_INPUT));
				if (speechRecord == NULL)
				{
					//do nothing
				}
				else
				{
					speechRecord->markAsProcessed();
					AIPU_STM->setCurrentAIPUState(AIPUSTATE::ENGAGED_IN_COVERSATION); //reset AIPU State
					//Here send the text to AIML engine
					string AIMLEngineResponse = getRebeccaAIMLresponse(speechRecord->transcriptionText);

					//Send MSG to TTS Engine to Speak the command

					TcpClient client("127.0.0.1");

					if (!client.Start(DEFAULT_TTS_ENGINE_PORT))
					{
						DEBUG_MSG("Error Communicating with TTS Engine");
						break;
					}

					client.Send((char*)AIMLEngineResponse.c_str());

					client.Stop();

				}

				
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
		
	}

	//Clean STM
	
	
	return 0;
}


/*
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
//SpeechRecord *incomingSpeech = new SpeechRecord(transcriptionText, transcriptionAccuracy, transcriptionLoudness); // get input and create
//AIPU_STM->inputRecord(static_cast<STMRecord*>(incomingSpeech));

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
*/