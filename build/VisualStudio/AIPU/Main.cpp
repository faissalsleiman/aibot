//TODO:
//Create threads and message passing
//Create a face recognition thread that talks to STM Thread
//Write the code in main to read the face detected and track it using the robot structure's neck
//
//
//Create a class called SpeechSynthesizer that intiailzes itself in main
//Speech Synthesizer must have a function Speak(text, volume, speed)
//
//

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


#include "ShortTermMemory.h"
#include "RobotStructure.h"

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
int CAPTUREWIDTH = 640; //in pixels
int CAPTUREHEIGHT = 480; //in pixels
double XCAPTUREVIEWINGANGLE = 78;
double YCAPTUREVIEWINGANGLE = 45;
//

//Global Variables defining socket server parameters
#define DEFAULT_PORT 27005
#define DEFAULT_BUFFER_LENGTH    512
//

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

#pragma region FUNCTIONALBLOCK1 FACE RECOGNITION
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

			//CALCULATIONS STEP 1
			//DEBUG_MSG("FACE DETECTED: " << faces.size() << endl);
			//DEBUG_MSG("Face Size in Pixels: " << faces[i].width << "x" << faces[i].height << endl);
			//DEBUG_MSG("Center of FACE Coordinates: " << faces[i].x + (faces[i].width / 2) << "," << faces[i].y + (faces[i].height / 2) << endl);
			double centerShiftX = -(faces[i].x + (faces[i].width / 2) - (CAPTUREWIDTH / 2));
			double centerShiftY = -(faces[i].y + (faces[i].height / 2) - (CAPTUREHEIGHT / 2));
			//DEBUG_MSG("Shift from Center of Camera: " << centerShiftX << "," << centerShiftY << endl); //assuming 640x480 res. so center of the image is at 320,240. 
			double planarFaceDistance = getFaceDistance(faces[i].width, faces[i].height);
			DEBUG_MSG("Approx. Distance in cm: " << planarFaceDistance << endl);

			FaceDetectionRecord *recognizedFace = new FaceDetectionRecord(faces[i].width, faces[i].height, faces[i].x + (faces[i].width / 2), faces[i].y + (faces[i].height / 2));
			AIPU_STM->inputRecord(static_cast<STMRecord*>(recognizedFace));

		}

		//print the output
		imshow("outputCapture", captureFrame);

		//pause for X-ms
		waitKey(10);
	}
}
#pragma endregion FUNCTIONALBLOCK1 FACE RECOGNITION

#pragma region FUNCTIONALBLOCK2 SPEECH SYNTHESIZER



#pragma endregion FUNCTIONALBLOCK2 SPEECH SYNTHESIZER


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
	server.sin_port = htons(DEFAULT_PORT);

	//Bind
	if (::bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		DEBUG_MSG("Bind failed for App Communicator Socket with error code : " << WSAGetLastError() << endl);
		exit(EXIT_FAILURE);
	}

	DEBUG_MSG("Bind App Communicator Socket Done" << endl);

	//Listen to incoming connections
	listen(serverSocket, 3);

	//Accept and incoming connection
	DEBUG_MSG("Waiting for incoming connections on App Communicator Socket..." << endl);

	c = sizeof(struct sockaddr_in);
	clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);

	if (clientSocket != INVALID_SOCKET)
	{
		DEBUG_MSG("Connection accepted on App Communicator Socket" << endl;);

		char recvbuf[DEFAULT_BUFFER_LENGTH];
		int iSendResult;

		// reveice until the client shutdown the connection
		do {
			iResult = recv(clientSocket, recvbuf, DEFAULT_BUFFER_LENGTH, 0);
			if (iResult > 0)
			{
				char msg[DEFAULT_BUFFER_LENGTH];
				memset(&msg, 0, sizeof(msg));
				strncpy_s(msg, recvbuf, iResult);

				DEBUG_MSG("Received: " << msg << endl);

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
				DEBUG_MSG("Connection closed\n");
			else
			{
				DEBUG_MSG("recv failed: " << WSAGetLastError() << endl);
				closesocket(serverSocket);
				WSACleanup();
				return 1;
			}
		} while (iResult > 0);
	}
	return 1;
}
#pragma endregion SOCKET SERVER FOR APP COMMUNICATOR


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


int main() {

	//Initialize Functional Blocks, Represented in Code as Threads

	AIPU_STM = new ShortTermMemory(); // Initialize Short Term Memory Structure

	//Initialize the state of the AIPU to IDLE
	AIPU_STM->setCurrentAIPUState(AIPUSTATE::IDLE);
    
    //Create robot structure of servos for control
	robot = new RobotStructure();
	
	//Start the Face Recognition functional block
	std::thread t1(faceRecognizer);
	std::thread t2(socketServer);


	//std::this_thread::sleep_for(std::chrono::milliseconds(10000000));
    //Start the Speech Synthesizer

    
    //Start State Machine
    //Read Data from STM (Short-Term-Memory) based on State
	//Process STM Data
	//Take Action
    
   
	while (true)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		switch (AIPU_STM->getCurrentAIPUState())
		{
			case AIPUSTATE::IDLE:
			{
				//DEBUG_MSG("IDLE STATE" << endl);
				/*
				if a face is detected move to engaged in convo within 1-2 sec
				if kickoff phrase received in good accuracy then go to engaged in convo
				*/
				FaceDetectionRecord *detectedFaceRecord = NULL;

				STMRecord *tempReadRecord;
				for (int i = 0; i < AIPU_STM->getSTMSize(); i++)
				{
					tempReadRecord = AIPU_STM->getSTMRecord(i);
					if (tempReadRecord == NULL)
						continue;
					if (tempReadRecord->recordType == STMRecordType::FACE_DETECTION && !tempReadRecord->processed) //code must block here otherwise a combo serial number for record must be created this will conmbine type with record number
					{
						detectedFaceRecord = static_cast<FaceDetectionRecord*>(tempReadRecord);
						break; //this record would be the current state, the reason is that our STM is a stack, Last in First Out
					}
				}
				if (detectedFaceRecord == NULL)
					break;

				//cout << '\a'; 
				detectedFaceRecord->markAsProcessed();
				DEBUG_MSG("READING RECORD: " << detectedFaceRecord->faceXCoordinate << "," << detectedFaceRecord->faceYCoordinate << endl);

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
