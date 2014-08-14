
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

enum STMRecordType {
	SPEECH_INPUT = 0,
	FACE_DETECTION,
	SOUND_DETECTION,
	SKELETAL_DETECTION,
	THERMAL_DETECTION,
	HAND_GESTURE,
	APP_COMMANDER,
	SLAM,
	OBJECTIVE,
	OBSTACLE_DETECTION,
	OBJECT_RECOGNITION,
	FACE_RECOGNITION
};


class STMRecord {
public:
	steady_clock::time_point timeStamp;
	STMRecordType recordType;
	bool processed;

	STMRecordType getRecordType()
	{
		return recordType;
	}
	steady_clock::time_point getTimeStamp()
	{
		return timeStamp;
	}
	int getTimeRelativeToNowInMilliSeconds()
	{
		steady_clock::time_point currentTime = steady_clock::now(); //currrent time of running this function
		return duration_cast<milliseconds>(currentTime - timeStamp).count();
	}
};


class SpeechRecord : public STMRecord {

public:
	string transcriptionText;
	int transcriptionAccuracy;
	int transcriptionLoudness;

	SpeechRecord(string inputTranscription, int inputAccuracy, int inputLoudness);
	~SpeechRecord();
	
};



class FaceDetectionRecord : public STMRecord {

public:
	int faceWidth;
	int faceHeight;
	int faceXCoordinate;
	int faceYCoordinate;

	FaceDetectionRecord(int inputFaceWidth, int inputFaceHeight, int inputFaceXCoordinate, int inputFaceYCoordinate);
	~FaceDetectionRecord();

};

class SoundDetectionRecord : public STMRecord {

public:
	int angleOfSound;
	int loundnessOfSound;

	SoundDetectionRecord(int angleOfSoundInput, int loundnessOfSoundInput);
	~SoundDetectionRecord();

};



