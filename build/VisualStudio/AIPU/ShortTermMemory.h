#pragma once

#include <iostream>
#include <time.h>
#include <chrono>

#include "STMRecord.h"

using namespace std;

const int SHORT_TERM_MEMORY_SIZE = 10;


enum AIPUSTATE {
	IDLE = 0,
	SOUND_DETECTED,
	LOCATING_SPEAKER,
	AWAITING_KICKOFF_PHRASE,
	ENGAGED_IN_COVERSATION,
	CHARGING_BATTERY,
	PROCESSING_DATA
};


class ShortTermMemory
{
	STMRecord *STM[SHORT_TERM_MEMORY_SIZE];

	AIPUSTATE currentAIPUState;
	steady_clock::time_point timeStampOfLastAIPUStateSet;

public:
	ShortTermMemory();
	~ShortTermMemory();

	bool inputRecord(STMRecord*);
	bool deleteRecord(int index);
	bool markRecordAsProcessed(int index);
	int getSTMSize();
	STMRecord * getSTMRecord(int index);

	void setCurrentAIPUState(AIPUSTATE stateToSet)
	{
		currentAIPUState = stateToSet;
		timeStampOfLastAIPUStateSet = steady_clock::now();
	}
	AIPUSTATE getCurrentAIPUState()
	{
		return currentAIPUState;
	}
	int getLastAIPUStateChangeTimeRelativeToNowInMilliSeconds()
	{
		steady_clock::time_point currentTime = steady_clock::now(); //currrent time of running this function
		return duration_cast<milliseconds>(currentTime - timeStampOfLastAIPUStateSet).count();
	}

};
