#include "STMRecord.h"


AppCommanderRecord::AppCommanderRecord(string inputCommandFromClient)
{
	timeStamp = steady_clock::now();
	recordType = STMRecordType::APP_COMMANDER;
	processed = false;
	inputCommand = inputCommandFromClient;
}
AppCommanderRecord::~AppCommanderRecord()
{

}


SpeechRecord::SpeechRecord(string inputTranscription, int inputAccuracy, int inputLoudness)
{
	timeStamp = steady_clock::now(); 
	recordType = STMRecordType::SPEECH_INPUT;
	processed = false;
	transcriptionText = inputTranscription;
	transcriptionAccuracy = inputAccuracy;
	transcriptionLoudness = inputLoudness;
}

SpeechRecord::~SpeechRecord()
{
}


FaceDetectionRecord::FaceDetectionRecord(int inputFaceWidth, int inputFaceHeight, int inputFaceXCoordinate, int inputFaceYCoordinate)
{
	timeStamp = steady_clock::now();
	recordType = STMRecordType::FACE_DETECTION;
	processed = false;
	faceWidth = inputFaceWidth;
	faceHeight = inputFaceHeight;
	faceXCoordinate = inputFaceXCoordinate;
	faceYCoordinate = inputFaceYCoordinate;
}

FaceDetectionRecord::~FaceDetectionRecord()
{
}


SoundDetectionRecord::SoundDetectionRecord(int angleOfSoundInput, int loundnessOfSoundInput)
{
	timeStamp = steady_clock::now();
	recordType = STMRecordType::SOUND_DETECTION;
	processed = false;
	angleOfSound = angleOfSoundInput;
	loundnessOfSound = loundnessOfSoundInput;
}

SoundDetectionRecord::~SoundDetectionRecord()
{

}


